#include "module3d/SceneModel.h"

#include "contract/Validate.h"
#include "contract/Version.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <utility>

namespace module3d {

namespace {

namespace lim = contract::limits;

using V = std::array<double, 3>;

V toArray(const contract::Vec3& v) noexcept
{
    return {v.x, v.y, v.z};
}

contract::Vec3 toVec(const V& v) noexcept
{
    return {v[0], v[1], v[2]};
}

double dot(const V& a, const V& b) noexcept
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

double clampNan(double v, double lo, double hi) noexcept
{
    if (!(v >= lo)) // also NaN
        return lo;
    return v > hi ? hi : v;
}

bool isJsonObjectText(const std::string& text)
{
    // contract::validate() is the one judge of what an extensions text may be.
    contract::SceneDescription probe;
    probe.extensionsJson = text;
    for (const auto& issue : contract::validate(probe).issues)
        if (issue.code == contract::IssueCode::E_EXTENSIONS)
            return false;
    return true;
}

// Candidate of the push-away maximisation (see pushAwayFromListener()).
struct Candidate
{
    V u{};
    double score = 0.0; // u . d
};

// Lexicographic comparison: larger u . d, then (exact ties) larger u . y, u . x, u . z. Ties in the
// score are judged with a tolerance far below the 1e-9 m geometry tolerance (AX9) but above the
// round-off of the candidate construction, so equal-score points found by different constructions
// (e.g. a circle's maximum and a pair point on that circle) compare as ties.
bool better(const Candidate& a, const Candidate& b) noexcept
{
    constexpr double kTieTolerance = 1e-12;
    if (a.score > b.score + kTieTolerance)
        return true;
    if (a.score < b.score - kTieTolerance)
        return false;
    for (const std::size_t axis : {std::size_t{1}, std::size_t{0}, std::size_t{2}})
    {
        if (a.u[axis] > b.u[axis] + kTieTolerance)
            return true;
        if (a.u[axis] < b.u[axis] - kTieTolerance)
            return false;
    }
    return false;
}

} // namespace

const char* producedContractVersion() noexcept
{
    return contract::contractVersion();
}

MarginBox marginBox(const contract::Vec3& d) noexcept
{
    const double c = lim::kSurfaceClearanceM;
    return {{c, c, c}, {d.x - c, d.y - c, d.z - c}};
}

double clampRoomDimension(double metres) noexcept
{
    return clampNan(metres, lim::kRoomDimensionMinM, lim::kRoomDimensionMaxM);
}

contract::Vec3 clampToMarginBox(const contract::Vec3& p, const MarginBox& box) noexcept
{
    return {clampNan(p.x, box.lo.x, box.hi.x), clampNan(p.y, box.lo.y, box.hi.y),
            clampNan(p.z, box.lo.z, box.hi.z)};
}

contract::Vec3 pushAwayFromListener(const contract::Vec3& emitter, const contract::Vec3& listener,
                                    const MarginBox& box) noexcept
{
    constexpr double r = lim::kEmitterListenerMinDistanceM; // 0.3 m (AX6)
    const V l = toArray(listener);
    const V e = toArray(emitter);
    const V diff{e[0] - l[0], e[1] - l[1], e[2] - l[2]};
    const double dist = std::sqrt(dot(diff, diff));
    if (dist >= r)
        return emitter;
    // d: the listener -> emitter direction, or AQ1 forward (+y) when they coincide.
    const V d = dist > 0.0 ? V{diff[0] / dist, diff[1] / dist, diff[2] / dist} : V{0.0, 1.0, 0.0};

    // u is feasible iff lo_i <= u_i <= hi_i (l + r u in the box).
    const V lo{(box.lo.x - l[0]) / r, (box.lo.y - l[1]) / r, (box.lo.z - l[2]) / r};
    const V hi{(box.hi.x - l[0]) / r, (box.hi.y - l[1]) / r, (box.hi.z - l[2]) / r};
    constexpr double kFeasTol = 1e-12;
    const auto feasible = [&](const V& u) {
        for (std::size_t i = 0; i < 3; ++i)
            if (u[i] < lo[i] - kFeasTol || u[i] > hi[i] + kFeasTol)
                return false;
        return true;
    };

    // The maximum of u . d over (unit sphere) n (box) lies at (1) u = d, (2) the maximum of u . d on
    // the circle where the sphere meets one face plane u_i = c (the relative interior of a feasible
    // arc), or (3) a point where the sphere meets two face planes (an arc's end). Enumerate them all;
    // on a circle where u . d is constant (d normal to the plane) the tie-break direction picks the
    // circle's candidate instead.
    bool have = false;
    Candidate best;
    const auto consider = [&](const V& u) {
        if (!feasible(u))
            return;
        const Candidate c{u, dot(u, d)};
        if (!have || better(c, best))
        {
            best = c;
            have = true;
        }
    };

    consider(d);

    std::array<std::pair<std::size_t, double>, 6> planes{};
    for (std::size_t i = 0; i < 3; ++i)
    {
        planes[2 * i] = {i, lo[i]};
        planes[2 * i + 1] = {i, hi[i]};
    }

    for (const auto& [i, c] : planes)
    {
        if (!(std::fabs(c) <= 1.0))
            continue;
        const double rho = std::sqrt(std::max(0.0, 1.0 - c * c)); // circle radius
        // Direction in the plane: the projection of d, else of the tie-break axes y, x, z.
        const std::array<V, 4> dirs{d, V{0.0, 1.0, 0.0}, V{1.0, 0.0, 0.0}, V{0.0, 0.0, 1.0}};
        for (const V& w : dirs)
        {
            V q = w;
            q[i] = 0.0;
            const double n = std::sqrt(dot(q, q));
            if (n < 1e-9)
                continue;
            V u{q[0] / n * rho, q[1] / n * rho, q[2] / n * rho};
            u[i] = c;
            consider(u);
            break; // only the first usable direction: d's projection, or the tie-break order
        }
    }

    for (std::size_t a = 0; a < planes.size(); ++a)
    {
        for (std::size_t b = a + 1; b < planes.size(); ++b)
        {
            const auto [i, ci] = planes[a];
            const auto [j, cj] = planes[b];
            if (i == j)
                continue;
            const double rest = 1.0 - ci * ci - cj * cj;
            if (rest < 0.0)
                continue;
            const std::size_t k = 3 - i - j;
            for (const double sign : {1.0, -1.0})
            {
                V u{};
                u[i] = ci;
                u[j] = cj;
                u[k] = sign * std::sqrt(rest);
                consider(u);
            }
        }
    }

    if (!have) // cannot happen for a box with sides >= 1.3 m (see the header); stay valid regardless
        best.u = d;
    const V p{l[0] + r * best.u[0], l[1] + r * best.u[1], l[2] + r * best.u[2]};
    return clampToMarginBox(toVec(p), box);
}

SceneModel::SceneModel(const contract::SceneDescription& initial)
    : scene_(sanitize(initial))
{}

contract::SceneDescription SceneModel::sanitize(contract::SceneDescription s)
{
    s.contractVersion = contract::kCurrentContractVersion;
    s.room.geometry.kind = contract::GeometryKind::shoebox;
    auto& dims = s.room.geometry.dimensions;
    dims = {clampRoomDimension(dims.x), clampRoomDimension(dims.y), clampRoomDimension(dims.z)};
    for (auto& m : s.room.surfaces)
    {
        for (auto& a : m.bandsAbsorption)
            a = clampNan(a, lim::kAbsorptionMin, lim::kAbsorptionMax);
        m.scattering = clampNan(m.scattering, lim::kScatteringMin, lim::kScatteringMax);
    }
    // AX7: exactly L on channel 0 and R on channel 1 (positions and gains kept when present).
    std::array<contract::Emitter, 2> emitters{};
    emitters[0].id = "L";
    emitters[1].id = "R";
    emitters[1].channel = 1;
    const auto box = marginBox(dims);
    emitters[0].position = {box.lo.x, box.hi.y, box.hi.z};
    emitters[1].position = {box.hi.x, box.hi.y, box.hi.z};
    for (const auto& e : s.emitters)
    {
        if (e.id == "L" || e.id == "R")
        {
            auto& t = emitters[e.id == "L" ? 0 : 1];
            t.position = e.position;
            t.gainDb = e.gainDb;
        }
    }
    for (auto& e : emitters)
        e.gainDb = std::isnan(e.gainDb) ? 0.0 : clampNan(e.gainDb, lim::kGainDbMin, lim::kGainDbMax);
    s.emitters.assign(emitters.begin(), emitters.end());
    if (s.render.outputMode != contract::OutputMode::binaural
        && s.render.outputMode != contract::OutputMode::stereoSpeakers)
        s.render.outputMode = contract::OutputMode::binaural;
    s.render.hrtfId = std::string{contract::kHrtfIdGenericV1};
    s.render.maxReflectionOrder = std::clamp(s.render.maxReflectionOrder, lim::kMaxReflectionOrderMin,
                                             lim::kMaxReflectionOrderMax);
    if (!isJsonObjectText(s.extensionsJson))
        s.extensionsJson = "{}";

    SceneModel model{s, 0};
    return model.scene_;
}

SceneModel::SceneModel(contract::SceneDescription s, int /*raw*/)
    : scene_(std::move(s))
{
    enforcePositions();
}

void SceneModel::enforcePositions()
{
    const auto box = marginBox(scene_.room.geometry.dimensions);
    scene_.listener.position = clampToMarginBox(scene_.listener.position, box);
    for (auto& e : scene_.emitters)
        e.position = pushAwayFromListener(clampToMarginBox(e.position, box), scene_.listener.position, box);
}

void SceneModel::setRoomDimensions(const contract::Vec3& m)
{
    scene_.room.geometry.dimensions = {clampRoomDimension(m.x), clampRoomDimension(m.y),
                                       clampRoomDimension(m.z)};
    enforcePositions();
}

void SceneModel::setListenerPosition(const contract::Vec3& p)
{
    scene_.listener.position = p;
    enforcePositions();
}

void SceneModel::setEmitterPosition(int emitterIndex, const contract::Vec3& p)
{
    scene_.emitters.at(static_cast<std::size_t>(emitterIndex)).position = p;
    enforcePositions();
}

void SceneModel::setEmitterGainDb(int emitterIndex, double gainDb)
{
    scene_.emitters.at(static_cast<std::size_t>(emitterIndex)).gainDb =
        std::isnan(gainDb) ? 0.0 : clampNan(gainDb, lim::kGainDbMin, lim::kGainDbMax);
}

void SceneModel::setSurfaceMaterial(contract::SurfaceId surface, const contract::SurfaceMaterial& material)
{
    auto& m = scene_.room.surface(surface);
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        m.bandsAbsorption[b] = clampNan(material.bandsAbsorption[b], lim::kAbsorptionMin,
                                        lim::kAbsorptionMax);
    m.scattering = clampNan(material.scattering, lim::kScatteringMin, lim::kScatteringMax);
}

void SceneModel::setTailSeed(std::uint32_t seed) noexcept
{
    scene_.render.tailSeed = seed;
}

void SceneModel::setMaxReflectionOrder(int order) noexcept
{
    scene_.render.maxReflectionOrder = std::clamp(order, lim::kMaxReflectionOrderMin,
                                                  lim::kMaxReflectionOrderMax);
}

void SceneModel::setOutputMode(contract::OutputMode mode) noexcept
{
    if (mode == contract::OutputMode::binaural || mode == contract::OutputMode::stereoSpeakers)
        scene_.render.outputMode = mode;
}

void SceneModel::setExtensionsJson(std::string json)
{
    scene_.extensionsJson = isJsonObjectText(json) ? std::move(json) : std::string{"{}"};
}

} // namespace module3d
