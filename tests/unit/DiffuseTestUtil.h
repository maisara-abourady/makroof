#pragma once

// Test support for the diffuse estimator (phase 05h): builds a DiffuseProblem from a scene the way
// src/sim/Engine.cpp planEmitter plans an emitter (t_mix,e, AX20 list, AX22 fallback), with the
// specular window target in the reference's units (no band-filter energy). Session 2 wires the
// estimator into planEmitter itself; until then this mirror is test-only.
#include "contract/SceneDescription.h"
#include "sim/Engine.h"
#include "sim/diffuse/DiffuseEstimator.h"
#include "sim/ism/ImageSources.h"
#include "sim/tail/Decay.h"
#include "sim/tail/MixingTime.h"
#include "sim/tail/NoiseTail.h"

#include <cmath>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace diffuse_test {

inline double dist(const contract::Vec3& a, const contract::Vec3& b)
{
    const double dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

struct PlannedEmitter
{
    sim::diffuse::DiffuseEmitter emitter;
    bool fallback = false;
    contract::BandArray bandsAx16Target{}; // specular + AX16 scattered entries (today's E_target)
};

inline PlannedEmitter planEmitter(const contract::SceneDescription& scene, const contract::Emitter& em,
                                  const sim::tail::RoomDecay& decay)
{
    namespace tail = sim::tail;
    namespace ism = sim::ism;
    contract::BandArray ones{};
    ones.fill(1.0);
    const double lengthS = tail::tailLengthS(decay);
    auto mixing = tail::mixingTime(dist(em.position, scene.listener.position) / ism::kSpeedOfSoundMps,
                                   decay.volumeM3);
    ism::ImageSourceOptions iso;
    iso.gain = std::pow(10.0, em.gainDb / 20.0);
    iso.maxArrivalTimeS = mixing.mixS + tail::kCrossfadeHalfS;
    auto set = ism::computeImageSources(scene.room, em.position, scene.listener.position, iso);
    auto match = tail::matchTail(tail::energyEntries(set, ones), mixing, decay, lengthS);
    PlannedEmitter out;
    if (tail::needsIsmFallback(match))
    {
        out.fallback = true;
        const double cap = ism::nthReflectionArrivalTimeS(scene.room, em.position, scene.listener.position,
                                                          sim::imageCountCap());
        if (cap > mixing.mixS)
        {
            mixing.mixS = cap;
            iso.maxArrivalTimeS = mixing.mixS + tail::kCrossfadeHalfS;
            set = ism::computeImageSources(scene.room, em.position, scene.listener.position, iso);
            match = tail::matchTail(tail::energyEntries(set, ones), mixing, decay, lengthS);
        }
    }
    out.bandsAx16Target = match.bandsTargetEnergy;
    ism::ImageSourceSet specOnly;
    specOnly.images = set.images;
    const auto spec = tail::matchTail(tail::energyEntries(specOnly, ones), mixing, decay, lengthS);
    auto& d = out.emitter;
    d.position = em.position;
    d.windowStartS = mixing.windowStartS;
    d.mixS = mixing.mixS;
    d.bandsT60S = decay.bandsT60S;
    d.gainSquared = iso.gain * iso.gain;
    d.bandsSpecularTarget = spec.bandsTargetEnergy;
    return out;
}

struct Planned
{
    sim::diffuse::DiffuseProblem problem;
    std::vector<PlannedEmitter> emitters;
};

inline Planned plan(const contract::SceneDescription& scene)
{
    Planned p;
    const auto decay = sim::tail::eyringDecay(scene.room);
    auto& r = p.problem.room;
    r.dimensions = scene.room.geometry.dimensions;
    for (std::size_t f = 0; f < contract::kNumSurfaces; ++f)
    {
        r.bandsAbsorption[f] = scene.room.surfaces[f].bandsAbsorption;
        r.scattering[f] = scene.room.surfaces[f].scattering;
    }
    r.bandsAirEnergyPerMetre = decay.bandsAirEnergyPerMetre;
    p.problem.listener = scene.listener.position;
    for (const auto& em : scene.emitters)
    {
        p.emitters.push_back(planEmitter(scene, em, decay));
        p.problem.emitters.push_back(p.emitters.back().emitter);
    }
    return p;
}

// A shoebox scene with per-face broadband absorption alpha (or per band) and scattering s.
inline contract::SceneDescription scene(const contract::Vec3& dims,
                                        const std::array<contract::BandArray, 6>& alpha,
                                        const std::array<double, 6>& s, const contract::Vec3& listener,
                                        const std::vector<contract::Vec3>& emitters)
{
    contract::SceneDescription sc;
    sc.room.geometry.dimensions = dims;
    for (std::size_t f = 0; f < 6; ++f)
    {
        sc.room.surfaces[f].bandsAbsorption = alpha[f];
        sc.room.surfaces[f].scattering = s[f];
    }
    sc.listener.position = listener;
    for (std::size_t e = 0; e < emitters.size(); ++e)
    {
        contract::Emitter em;
        em.id = e == 0 ? "L" : "R";
        em.channel = static_cast<int>(e);
        em.position = emitters[e];
        sc.emitters.push_back(em);
    }
    return sc;
}

inline contract::BandArray flat(double v)
{
    contract::BandArray a{};
    a.fill(v);
    return a;
}

// tests/golden/phase05h_dt1_smoke_reference.json (tools/validation/export_phase05h_smoke.py): the
// "names" strings and the "rows" number lists, read without a JSON library.
struct SmokeReference
{
    std::vector<std::string> columns;
    std::vector<std::string> names;
    std::vector<std::vector<double>> rows;

    std::size_t col(const std::string& name) const
    {
        for (std::size_t i = 0; i < columns.size(); ++i)
            if (columns[i] == name)
                return i;
        return static_cast<std::size_t>(-1);
    }
};

inline std::vector<std::string> readStrings(const std::string& text, const std::string& key)
{
    std::vector<std::string> out;
    auto pos = text.find("\"" + key + "\"");
    if (pos == std::string::npos)
        return out;
    pos = text.find('[', pos);
    const auto end = text.find(']', pos);
    for (auto q = text.find('"', pos); q != std::string::npos && q < end; q = text.find('"', q + 1))
    {
        const auto q2 = text.find('"', q + 1);
        out.push_back(text.substr(q + 1, q2 - q - 1));
        q = q2;
    }
    return out;
}

inline SmokeReference readSmokeReference(const std::string& path)
{
    std::ifstream in(path);
    std::stringstream ss;
    ss << in.rdbuf();
    const std::string text = ss.str();
    SmokeReference ref;
    ref.columns = readStrings(text, "columns");
    ref.names = readStrings(text, "names");
    auto pos = text.find("\"rows\"");
    if (pos == std::string::npos)
        return ref;
    pos = text.find('[', pos) + 1;
    for (;;)
    {
        const auto open = text.find('[', pos);
        if (open == std::string::npos)
            break;
        const auto close = text.find(']', open);
        std::vector<double> row;
        const char* c = text.c_str() + open + 1;
        const char* stop = text.c_str() + close;
        while (c < stop)
        {
            char* e = nullptr;
            const double v = std::strtod(c, &e);
            if (e == c)
            {
                ++c;
                continue;
            }
            row.push_back(v);
            c = e;
        }
        ref.rows.push_back(row);
        pos = close + 1;
    }
    return ref;
}

} // namespace diffuse_test
