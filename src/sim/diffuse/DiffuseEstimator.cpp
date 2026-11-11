#include "sim/diffuse/DiffuseEstimator.h"

#include "sim/diffuse/FaceLists.h"
#include "sim/diffuse/Sampling.h"
#include "sim/diffuse/ThreadPool.h"
#include "sim/ism/ImageSources.h"
#include "sim/tail/NoiseTail.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <numbers>

namespace sim::diffuse {

namespace {

constexpr std::size_t kBands = contract::kNumOctaveBands;
constexpr double kSpeedOfSound = ism::kSpeedOfSoundMps; // AX4
constexpr double kEnergyDecayPerT60 = tail::kEnergyDecayPerT60;
constexpr double kMatchNormalisationS = tail::kMatchNormalisationS;
constexpr double kAxisEpsilon = 1e-15;

using Bands = std::array<double, kBands>;

// One gather target set: an end's face lists with the window of one emitter.
struct Gather
{
    const FaceLists* lists = nullptr;
    double point[3]{};
    double a = 0.0;    // window start
    double b = 0.0;    // t_mix,e
    Bands rate{};      // 13.82 / T60_b
    Bands gamma{};     // m_b - rate_b / c (referral of the last leg plus its air)
    double norm = 0.0; // 10 ms / integral of the window, times the emitter's gain squared
};

struct Prepared
{
    double dims[3]{};
    std::array<Bands, contract::kNumSurfaces> reflect{}; // 1 - a
    std::array<double, contract::kNumSurfaces> scattering{};
    Bands air{};
    std::size_t numEmitters = 0;
    std::vector<double> emitterPos; // 3 per emitter
    double listener[3]{};
    FaceLists listenerLists;             // forward paths gather here
    std::vector<FaceLists> emitterLists; // the listener-started set gathers here
    std::vector<Gather> forward;         // per emitter: listener lists, emitter e's window
    std::vector<Gather> reverse;         // per emitter: emitter e's lists, emitter e's window
    std::vector<double> weight;          // NW-4C w per emitter
    double reverseEndS = 0.0;            // the listener-started trace runs to max_e t_mix,e
};

// Scores of one history: per emitter, forward and reverse per band (unnormalised: weight 4π).
struct HistoryScores
{
    std::array<Bands, 2> fwd{};
    std::array<Bands, 2> rev{};
};

// Traces one path from `start` until `endS`, gathering at each of `targets` (NEE). Returns the
// number of image evaluations; adds the contributions to out[target] and folds the face sequence
// into `hash`.
std::int64_t tracePath(const Prepared& p, const double start[3], double endS, const Gather* targets,
                       std::size_t numTargets, Bands* out, Key key, std::uint64_t& hash)
{
    double x[3]{start[0], start[1], start[2]};
    key.hit = 0;
    const Direction d0 = uniformSphere(key);
    double d[3]{d0.v[0], d0.v[1], d0.v[2]};
    Bands w;
    w.fill(4.0 * std::numbers::pi);
    // Product of (1 - a) without air: decides when the path carries nothing (no libm, D1).
    Bands reflectOnly;
    reflectOnly.fill(1.0);
    double t = 0.0;
    std::int64_t evaluations = 0;
    for (std::uint32_t hit = 1;; ++hit)
    {
        double tb = std::numeric_limits<double>::infinity();
        int face = -1;
        for (int ax = 0; ax < 3; ++ax)
        {
            if (d[ax] > kAxisEpsilon)
            {
                const double tt = (p.dims[ax] - x[ax]) / d[ax];
                if (tt < tb)
                {
                    tb = tt;
                    face = 2 * ax + 1;
                }
            }
            else if (d[ax] < -kAxisEpsilon)
            {
                const double tt = -x[ax] / d[ax];
                if (tt < tb)
                {
                    tb = tt;
                    face = 2 * ax;
                }
            }
        }
        if (face < 0)
            break;
        for (int i = 0; i < 3; ++i)
            x[i] += tb * d[i];
        const int axis = face / 2;
        const bool high = (face % 2) == 1;
        x[axis] = high ? p.dims[axis] : 0.0;
        t += tb / kSpeedOfSound;
        if (!(t < endS))
            break;
        hash = fnvStep(hash, static_cast<std::uint64_t>(face));
        for (std::size_t k = 0; k < kBands; ++k)
            w[k] *= std::exp(-p.air[k] * tb);
        const auto f = static_cast<std::size_t>(face);
        const double s = p.scattering[f];
        if (s > 0.0)
        {
            for (std::size_t g = 0; g < numTargets; ++g)
            {
                const Gather& tg = targets[g];
                if (!(t < tg.b))
                    continue;
                const double rem = kSpeedOfSound * (tg.b - t);
                const double dx0 = x[0] - tg.point[0];
                const double dy0 = x[1] - tg.point[1];
                const double dz0 = x[2] - tg.point[2];
                const double dlr = std::sqrt(dx0 * dx0 + dy0 * dy0 + dz0 * dz0);
                Bands hitf;
                for (std::size_t k = 0; k < kBands; ++k)
                    hitf[k] = w[k] * p.reflect[f][k] * s / std::numbers::pi
                              * std::exp(-tg.rate[k] * (tg.b - t));
                Bands& acc = out[g];
                for (const GatherImage& im : tg.lists->faces[f])
                {
                    if (im.distanceM - dlr > rem)
                        break;
                    ++evaluations;
                    const double dx = im.position[0] - x[0];
                    const double dy = im.position[1] - x[1];
                    const double dz = im.position[2] - x[2];
                    const double r2 = dx * dx + dy * dy + dz * dz;
                    const double r = std::sqrt(r2);
                    const double ta = t + r / kSpeedOfSound;
                    if (ta <= tg.a || ta >= tg.b)
                        continue;
                    double cs = axis == 0 ? dx : (axis == 1 ? dy : dz);
                    if (high)
                        cs = -cs;
                    cs /= r;
                    if (cs <= 0.0)
                        continue;
                    double hw = std::sin(std::numbers::pi * (ta - tg.a) / (tg.b - tg.a));
                    hw *= hw;
                    const double gfac = cs / r2 * hw;
                    for (std::size_t k = 0; k < kBands; ++k)
                        acc[k] += hitf[k] * gfac * im.bandsSpecular[k] * std::exp(-tg.gamma[k] * r);
                }
            }
        }
        bool alive = false;
        for (std::size_t k = 0; k < kBands; ++k)
        {
            w[k] *= p.reflect[f][k];
            reflectOnly[k] *= p.reflect[f][k];
            alive = alive || reflectOnly[k] > 0.0;
        }
        if (!alive)
            break;
        key.hit = hit;
        if (scatterBranch(key, s))
        {
            const Direction nd = lambert(key, axis, high ? -1.0 : 1.0);
            d[0] = nd.v[0];
            d[1] = nd.v[1];
            d[2] = nd.v[2];
        }
        else
        {
            d[axis] = -d[axis];
        }
    }
    return evaluations;
}

// One history (AX41): emitter-started path h per emitter, then the listener-started path h.
std::int64_t runHistory(const Prepared& p, std::int64_t h, HistoryScores& sc, std::uint64_t& hash)
{
    std::int64_t work = 0;
    for (std::size_t e = 0; e < p.numEmitters; ++e)
    {
        Key key{kDiffuseSeed,
                PathEnd::emitter,
                static_cast<std::uint32_t>(e),
                static_cast<std::uint64_t>(h),
                0,
                0};
        work += tracePath(p, &p.emitterPos[3 * e], p.forward[e].b, &p.forward[e], 1, &sc.fwd[e], key, hash);
        hash = fnvStep(hash, 0xF0u + e);
    }
    Key key{kDiffuseSeed, PathEnd::listener, kSharedEmitter, static_cast<std::uint64_t>(h), 0, 0};
    work += tracePath(p, p.listener, p.reverseEndS, p.reverse.data(), p.numEmitters, sc.rev.data(), key,
                      hash);
    hash = fnvStep(hash, 0xFEu);
    return work;
}

Prepared prepare(const DiffuseProblem& problem)
{
    Prepared p;
    const auto& room = problem.room;
    p.dims[0] = room.dimensions.x;
    p.dims[1] = room.dimensions.y;
    p.dims[2] = room.dimensions.z;
    std::array<contract::BandArray, contract::kNumSurfaces> spec{};
    for (std::size_t f = 0; f < contract::kNumSurfaces; ++f)
    {
        p.scattering[f] = room.scattering[f];
        for (std::size_t k = 0; k < kBands; ++k)
        {
            p.reflect[f][k] = 1.0 - room.bandsAbsorption[f][k];
            spec[f][k] = p.reflect[f][k] * (1.0 - room.scattering[f]);
        }
    }
    p.air = room.bandsAirEnergyPerMetre;
    p.numEmitters = std::min<std::size_t>(2, problem.emitters.size());
    p.listener[0] = problem.listener.x;
    p.listener[1] = problem.listener.y;
    p.listener[2] = problem.listener.z;
    double maxMix = 0.0;
    for (std::size_t e = 0; e < p.numEmitters; ++e)
        maxMix = std::max(maxMix, problem.emitters[e].mixS);
    p.reverseEndS = maxMix;
    p.listenerLists = makeFaceLists(room.dimensions, problem.listener, kSpeedOfSound * maxMix, spec);
    p.emitterLists.reserve(p.numEmitters);
    const double dL = nearestSurfaceDistance(room.dimensions, problem.listener);
    for (std::size_t e = 0; e < p.numEmitters; ++e)
    {
        const auto& em = problem.emitters[e];
        p.emitterPos.insert(p.emitterPos.end(), {em.position.x, em.position.y, em.position.z});
        p.emitterLists.push_back(makeFaceLists(room.dimensions, em.position, kSpeedOfSound * em.mixS, spec));
        p.weight.push_back(blendWeight(dL, nearestSurfaceDistance(room.dimensions, em.position)));
    }
    for (std::size_t e = 0; e < p.numEmitters; ++e)
    {
        const auto& em = problem.emitters[e];
        Gather g;
        g.a = em.windowStartS;
        g.b = em.mixS;
        for (std::size_t k = 0; k < kBands; ++k)
        {
            g.rate[k] = em.bandsT60S[k] > 0.0 ? kEnergyDecayPerT60 / em.bandsT60S[k] : 0.0;
            g.gamma[k] = p.air[k] - g.rate[k] / kSpeedOfSound;
        }
        g.norm = (g.b > g.a ? kMatchNormalisationS / (0.5 * (g.b - g.a)) : 0.0) * em.gainSquared;
        Gather fwd = g;
        fwd.lists = &p.listenerLists;
        std::copy(p.listener, p.listener + 3, fwd.point);
        p.forward.push_back(fwd);
        Gather rev = g;
        rev.lists = &p.emitterLists[e];
        std::copy(&p.emitterPos[3 * e], &p.emitterPos[3 * e] + 3, rev.point);
        p.reverse.push_back(rev);
    }
    return p;
}

// Per-history blended scores of a range of histories: x[(i * E + e) * 8 + b] (normalised by the
// window, so their mean is the estimate), plus per-block work and hashes.
struct RangeScores
{
    std::int64_t first = 0;
    std::int64_t blocks = 0;
    std::vector<double> x;  // blended scores
    std::vector<double> fx; // emitter-started part alone (diagnostics, tests)
    std::vector<double> rx; // listener-started part alone
    std::vector<std::int64_t> blockWork;
    std::vector<std::uint64_t> blockHash;
    std::vector<char> blockDone;
};

void runBlock(const Prepared& p, RangeScores& rs, std::int64_t blk)
{
    const std::size_t numE = p.numEmitters;
    std::int64_t work = 0;
    std::uint64_t hash = kFnvOffset;
    for (std::int64_t j = 0; j < kBlockHistories; ++j)
    {
        const std::int64_t local = blk * kBlockHistories + j;
        const std::int64_t h = rs.first + local;
        HistoryScores sc;
        work += runHistory(p, h, sc, hash);
        for (std::size_t e = 0; e < numE; ++e)
        {
            const double we = p.weight[e];
            const double norm = p.forward[e].norm;
            const std::size_t at = (static_cast<std::size_t>(local) * numE + e) * kBands;
            for (std::size_t k = 0; k < kBands; ++k)
            {
                rs.fx[at + k] = sc.fwd[e][k] * norm;
                rs.rx[at + k] = sc.rev[e][k] * norm;
                rs.x[at + k] = we * rs.fx[at + k] + (1.0 - we) * rs.rx[at + k];
            }
        }
    }
    rs.blockWork[static_cast<std::size_t>(blk)] = work;
    rs.blockHash[static_cast<std::size_t>(blk)] = hash;
    rs.blockDone[static_cast<std::size_t>(blk)] = 1;
}

void allocate(RangeScores& rs, std::int64_t first, std::int64_t blocks, std::size_t numE)
{
    rs.first = first;
    rs.blocks = blocks;
    rs.x.assign(static_cast<std::size_t>(blocks * kBlockHistories) * numE * kBands, 0.0);
    rs.fx.assign(rs.x.size(), 0.0);
    rs.rx.assign(rs.x.size(), 0.0);
    rs.blockWork.assign(static_cast<std::size_t>(blocks), 0);
    rs.blockHash.assign(static_cast<std::size_t>(blocks), 0);
    rs.blockDone.assign(static_cast<std::size_t>(blocks), 0);
}

bool stopRequested(const DiffuseRunOptions& o) noexcept
{
    return o.stop != nullptr && o.stop->load(std::memory_order_acquire);
}

// Runs blocks [from, to) of rs on the pool; false if stopped (D6).
bool runBlocks(const Prepared& p, RangeScores& rs, std::int64_t from, std::int64_t to, ThreadPool& pool,
               const DiffuseRunOptions& o)
{
    pool.parallelFor(to - from, [&](std::int64_t i) {
        if (stopRequested(o))
            return false;
        runBlock(p, rs, from + i);
        if (o.onBlock)
            o.onBlock(rs.first / kBlockHistories + from + i);
        return true;
    });
    for (std::int64_t b = from; b < to; ++b)
        if (!rs.blockDone[static_cast<std::size_t>(b)])
            return false;
    return true;
}

Bands column(const std::vector<double>& x, std::size_t n, std::size_t numE, std::size_t e,
             std::array<TallyStats, kBands>& stats)
{
    Bands mean{};
    for (std::size_t k = 0; k < kBands; ++k)
    {
        stats[k] = tallyStats(x.data() + e * kBands + k, n, numE * kBands);
        mean[k] = stats[k].mean;
    }
    return mean;
}

} // namespace

PathCount pathCount(const PathCountInput& in) noexcept
{
    PathCount c;
    const std::int64_t blk = kBlockHistories;
    if (in.wPilot <= 0)
        c.nCap = std::numeric_limits<std::int64_t>::max() / 2 / blk * blk;
    else if (in.wScene <= in.wPilot)
        c.nCap = 0;
    else
    {
        // (W_scene - W_pilot) n* in 64 bits; saturate instead of overflowing for extreme limits.
        const std::int64_t room = in.wScene - in.wPilot;
        const std::int64_t big = std::numeric_limits<std::int64_t>::max() / 2;
        c.nCap = (in.nStar > 0 && room > big / in.nStar) ? big / blk * blk
                                                         : room * in.nStar / in.wPilot / blk * blk;
    }
    const std::int64_t want = std::max(in.nNeed, in.nStar);
    const std::int64_t wantBlocks = (want + blk - 1) / blk * blk;
    c.n = std::min(wantBlocks, c.nCap);
    c.capHit = in.nNeed > c.nCap;
    c.pilotShipped = c.nCap < blk;
    if (c.pilotShipped)
        c.n = 0;
    c.floorTruncated = c.nCap < in.nStar; // N = min(.., N_cap) falls below n*
    c.pilotFloor = in.nStar < kPilotFloor;
    return c;
}

bool pilotStops(std::int64_t n, std::int64_t wPilot, std::int64_t wScene, std::int64_t nStarMax) noexcept
{
    return n >= nStarMax || 2 * wPilot >= wScene;
}

std::int64_t pathsNeeded(std::int64_t nStar, double variance, double total, double seTargetDb) noexcept
{
    if (!(total > 0.0) || !(variance > 0.0) || nStar <= 0)
        return 1;
    // n* (SE_db / target)^2 = k^2 var / (tot^2 target^2), SE_db = k sqrt(var / n*) / tot.
    const double need = kDbPerRelative * kDbPerRelative * variance
                        / (total * total * seTargetDb * seTargetDb);
    if (!(need < 4.0e18))
        return std::numeric_limits<std::int64_t>::max() / 4;
    return std::max<std::int64_t>(1, static_cast<std::int64_t>(std::ceil(need)));
}

TallyStats tallyStats(const double* x, std::size_t n, std::size_t stride)
{
    TallyStats s;
    if (n == 0)
        return s;
    double sum = 0.0;
    for (std::size_t i = 0; i < n; ++i)
        sum += x[i * stride];
    s.mean = sum / static_cast<double>(n);
    double s2 = 0.0;
    double s4 = 0.0;
    for (std::size_t i = 0; i < n; ++i)
    {
        const double d = x[i * stride] - s.mean;
        s2 += d * d;
        s4 += d * d * d * d;
    }
    s.variance = s2 / static_cast<double>(n);
    s.se = std::sqrt(s.variance / static_cast<double>(n));
    s.r = s.mean > 0.0 ? s.se / s.mean : 0.0;
    s.vov = s2 > 0.0 ? s4 / (s2 * s2) - 1.0 / static_cast<double>(n) : 0.0;
    // Slope (reported only): 1 + 1 / Hill over the k largest scores, k = max(10, min(200, 5 %)).
    const std::size_t k = std::max<std::size_t>(10, std::min<std::size_t>(200, n / 20));
    if (n > k)
    {
        std::vector<double> v(n);
        for (std::size_t i = 0; i < n; ++i)
            v[i] = x[i * stride];
        std::nth_element(v.begin(), v.begin() + static_cast<std::ptrdiff_t>(k), v.end(), std::greater<>());
        const double ref = v[k];
        if (ref > 0.0)
        {
            double hill = 0.0;
            for (std::size_t i = 0; i < k; ++i)
                hill += std::log(v[i] / ref);
            hill /= static_cast<double>(k);
            s.slope = std::min(10.0, hill > 0.0 ? 1.0 + 1.0 / hill : 10.0);
        }
    }
    return s;
}

double nearestSurfaceDistance(const contract::Vec3& dims, const contract::Vec3& p) noexcept
{
    return std::min({p.x, dims.x - p.x, p.y, dims.y - p.y, p.z, dims.z - p.z});
}

double blendWeight(double dL, double dE) noexcept
{
    const double den = dL * dL + dE * dE;
    return den > 0.0 ? dL * dL / den : 0.5;
}

bool bothNear(double dL, double dE) noexcept
{
    return dL < kBothNearM && dE < kBothNearM;
}

bool approximateNote(bool near, bool capHit, double vovUnion, double achievedSeDb) noexcept
{
    return (near && (capHit || vovUnion >= kVovLimit)) || (capHit && achievedSeDb > kApproximateSeDb);
}

DiffuseResult estimateDiffuse(const DiffuseProblem& problem, const DiffuseLimits& limits,
                              const DiffuseRunOptions& options)
{
    DiffuseResult res;
    res.wScene = limits.wScene;
    const Prepared p = prepare(problem);
    const std::size_t numE = p.numEmitters;
    res.latticeImages = p.listenerLists.latticeSize;
    res.emitters.resize(numE);
    if (numE == 0)
        return res;
    ThreadPool& pool = options.pool != nullptr ? *options.pool : ThreadPool::process();
    // The pilot must stay below the final range (AX41: pilot [0, n*), final [8 000, ...)).
    const std::int64_t nStarMax = std::clamp<std::int64_t>(limits.nStarMax, kBlockHistories,
                                                           kFinalRangeStart);

    RangeScores pilot;
    RangeScores fin;
    bool shipPilot = false;
    if (limits.fixedHistories > 0)
    {
        // Validation: N histories from history 0, no pilot.
        const std::int64_t blocks = (limits.fixedHistories + kBlockHistories - 1) / kBlockHistories;
        const std::int64_t start = std::max<std::int64_t>(0, limits.fixedStart) / kBlockHistories
                                   * kBlockHistories;
        allocate(fin, start, blocks, numE);
        if (!runBlocks(p, fin, 0, blocks, pool, options))
        {
            res.cancelled = true;
            return res;
        }
        res.count.n = blocks * kBlockHistories;
    }
    else
    {
        // Pilot (AX41): blocks from history 0, run a pool's worth at a time, scanned in order; the stop
        // test is applied at each block boundary, so blocks past the stop are discarded (D4).
        const std::int64_t maxBlocks = (nStarMax + kBlockHistories - 1) / kBlockHistories;
        const std::int64_t offset = std::max<std::int64_t>(0, limits.historyOffset) / kBlockHistories
                                    * kBlockHistories;
        allocate(pilot, offset, maxBlocks, numE);
        std::int64_t used = 0;
        std::int64_t wPilot = 0;
        bool stopped = false;
        const auto batch = static_cast<std::int64_t>(pool.size());
        while (!stopped && used < maxBlocks)
        {
            const std::int64_t to = std::min(maxBlocks, used + batch);
            if (!runBlocks(p, pilot, used, to, pool, options))
            {
                res.cancelled = true;
                return res;
            }
            for (std::int64_t b = used; b < to && !stopped; ++b)
            {
                wPilot += pilot.blockWork[static_cast<std::size_t>(b)];
                used = b + 1;
                stopped = pilotStops(used * kBlockHistories, wPilot, limits.wScene, nStarMax);
            }
        }
        res.nStar = used * kBlockHistories;
        res.wPilot = wPilot;
        std::int64_t need = 1;
        for (std::size_t e = 0; e < numE; ++e)
        {
            std::array<TallyStats, kBands> st{};
            const Bands m = column(pilot.x, static_cast<std::size_t>(res.nStar), numE, e, st);
            for (std::size_t k = 0; k < kBands; ++k)
            {
                const double tot = problem.emitters[e].bandsSpecularTarget[k] + m[k];
                need = std::max(need, pathsNeeded(res.nStar, st[k].variance, tot, limits.seTargetDb));
                res.emitters[e].bandsPilotSeDb[k] = tot > 0.0 ? kDbPerRelative * st[k].se / tot : 0.0;
                res.emitters[e].bandsPilotVov[k] = st[k].vov;
            }
        }
        res.nNeed = need;
        res.count = pathCount({res.nStar, wPilot, limits.wScene, need});
        shipPilot = res.count.pilotShipped;
        if (!shipPilot)
        {
            const std::int64_t blocks = res.count.n / kBlockHistories;
            allocate(fin, offset + kFinalRangeStart, blocks, numE);
            if (!runBlocks(p, fin, 0, blocks, pool, options))
            {
                res.cancelled = true;
                return res;
            }
        }
    }

    // D5: the face-sequence hash of the shipped histories, pilot blocks then final blocks.
    std::uint64_t hash = kFnvOffset;
    for (std::int64_t b = 0; b < res.nStar / kBlockHistories; ++b)
        hash = fnvStep(hash, pilot.blockHash[static_cast<std::size_t>(b)]);
    if (!shipPilot)
        for (std::int64_t b = 0; b < fin.blocks; ++b)
        {
            hash = fnvStep(hash, fin.blockHash[static_cast<std::size_t>(b)]);
            res.wFinal += fin.blockWork[static_cast<std::size_t>(b)];
        }
    hash = fnvStep(hash, static_cast<std::uint64_t>(res.nStar));
    hash = fnvStep(hash, static_cast<std::uint64_t>(res.count.n));
    res.faceHash = hash;

    const RangeScores& ship = shipPilot ? pilot : fin;
    const auto nShip = static_cast<std::size_t>(shipPilot ? res.nStar : res.count.n);
    const double dL = nearestSurfaceDistance(problem.room.dimensions, problem.listener);
    for (std::size_t e = 0; e < numE; ++e)
    {
        auto& er = res.emitters[e];
        std::array<TallyStats, kBands> st{};
        const Bands m = column(ship.x, nShip, numE, e, st);
        // VOV_union over the pilot then the final range, up to the first 8 000 histories (AX44).
        const auto nPilotU = static_cast<std::size_t>(std::min<std::int64_t>(res.nStar, kUnionVovHistories));
        const std::size_t nFinU =
            shipPilot ? 0
                      : static_cast<std::size_t>(std::min<std::int64_t>(
                            res.count.n, kUnionVovHistories - static_cast<std::int64_t>(nPilotU)));
        std::vector<double> uni;
        uni.reserve((nPilotU + nFinU) * kBands);
        for (std::size_t i = 0; i < nPilotU; ++i)
            for (std::size_t k = 0; k < kBands; ++k)
                uni.push_back(pilot.x[(i * numE + e) * kBands + k]);
        for (std::size_t i = 0; i < nFinU; ++i)
            for (std::size_t k = 0; k < kBands; ++k)
                uni.push_back(fin.x[(i * numE + e) * kBands + k]);
        er.achievedSeDb = 0.0;
        er.vovUnion = 0.0;
        for (std::size_t k = 0; k < kBands; ++k)
        {
            er.bandsDiffuse[k] = m[k];
            double f = 0.0, r = 0.0; // history order, as the blended mean
            for (std::size_t i = 0; i < nShip; ++i)
            {
                f += ship.fx[(i * numE + e) * kBands + k];
                r += ship.rx[(i * numE + e) * kBands + k];
            }
            er.bandsForward[k] = nShip > 0 ? f / static_cast<double>(nShip) : 0.0;
            er.bandsReverse[k] = nShip > 0 ? r / static_cast<double>(nShip) : 0.0;
            er.bandsSe[k] = st[k].se;
            const double tot = problem.emitters[e].bandsSpecularTarget[k] + m[k];
            er.bandsSeDb[k] = tot > 0.0 ? kDbPerRelative * st[k].se / tot : 0.0;
            er.bandsR[k] = st[k].r;
            er.bandsVov[k] = st[k].vov;
            er.bandsSlope[k] = st[k].slope;
            er.bandsVovUnion[k] = uni.empty() ? 0.0
                                              : tallyStats(uni.data() + k, uni.size() / kBands, kBands).vov;
            er.achievedSeDb = std::max(er.achievedSeDb, er.bandsSeDb[k]);
            er.vovUnion = std::max(er.vovUnion, er.bandsVovUnion[k]);
        }
        er.weight = p.weight[e];
        er.listenerDistanceM = dL;
        er.emitterDistanceM = nearestSurfaceDistance(problem.room.dimensions, problem.emitters[e].position);
        er.bothNear = bothNear(dL, er.emitterDistanceM);
        er.approximate = approximateNote(er.bothNear, res.count.capHit, er.vovUnion, er.achievedSeDb);
    }
    return res;
}

} // namespace sim::diffuse
