#pragma once

// SceneDescription v1: the 3D Module -> Simulator contract (PRD FR-SIM-1, BUILD_PLAN AQ1).
// Plain value types, no behaviour. JSON I/O lives in Json.h, the rules in Validate.h, and the full
// specification in docs/contract/README.md.
//
// Units are SI (metres, dB). Axes are right-handed: x right, y forward, z up (AQ1). A shoebox room
// occupies [0,W] x [0,D] x [0,H] with its origin at a floor corner.
#include "contract/Version.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace contract {

// The one place the octave band set is defined (CLAUDE.md "Code conventions"). Every per-band
// array in the code base (bandsXxx) is indexed like this.
inline constexpr std::size_t kNumOctaveBands = 8;
inline constexpr std::array<double, kNumOctaveBands> kOctaveBandsHz{63.0,   125.0,  250.0,  500.0,
                                                                    1000.0, 2000.0, 4000.0, 8000.0};
using BandArray = std::array<double, kNumOctaveBands>;

struct Vec3
{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    friend bool operator==(const Vec3&, const Vec3&) = default;
};

// Surfaces are named by the plane they lie on, so nothing depends on where the listener faces.
enum class SurfaceId
{
    xMin,   // x = 0
    xMax,   // x = W
    yMin,   // y = 0
    yMax,   // y = D
    floor,  // z = 0
    ceiling // z = H
};

inline constexpr std::size_t kNumSurfaces = 6;
inline constexpr std::array<SurfaceId, kNumSurfaces> kAllSurfaces{
    SurfaceId::xMin, SurfaceId::xMax, SurfaceId::yMin, SurfaceId::yMax, SurfaceId::floor, SurfaceId::ceiling};

constexpr std::size_t surfaceIndex(SurfaceId id) noexcept
{
    return static_cast<std::size_t>(id);
}

// JSON key of a surface ("xMin", ..., "ceiling").
constexpr std::string_view surfaceName(SurfaceId id) noexcept
{
    switch (id)
    {
    case SurfaceId::xMin:
        return "xMin";
    case SurfaceId::xMax:
        return "xMax";
    case SurfaceId::yMin:
        return "yMin";
    case SurfaceId::yMax:
        return "yMax";
    case SurfaceId::floor:
        return "floor";
    case SurfaceId::ceiling:
        return "ceiling";
    }
    return "";
}

// AQ3: absorption per octave band and one broadband scattering coefficient. Reflectivity is 1 - a
// and is not stored. No transmission in v1.
struct SurfaceMaterial
{
    BandArray bandsAbsorption{};
    double scattering = 0.0;

    friend bool operator==(const SurfaceMaterial&, const SurfaceMaterial&) = default;
};

// v1 knows shoeboxes only. A mesh kind is a future major version (AQ1).
enum class GeometryKind
{
    shoebox
};

struct RoomGeometry
{
    GeometryKind kind = GeometryKind::shoebox;
    Vec3 dimensions; // x = width W, y = depth D, z = height H, in metres

    friend bool operator==(const RoomGeometry&, const RoomGeometry&) = default;
};

struct Room
{
    RoomGeometry geometry;
    std::array<SurfaceMaterial, kNumSurfaces> surfaces{}; // indexed by surfaceIndex(SurfaceId)

    SurfaceMaterial& surface(SurfaceId id) noexcept { return surfaces[surfaceIndex(id)]; }
    const SurfaceMaterial& surface(SurfaceId id) const noexcept { return surfaces[surfaceIndex(id)]; }

    friend bool operator==(const Room&, const Room&) = default;
};

struct Listener
{
    Vec3 position;

    friend bool operator==(const Listener&, const Listener&) = default;
};

// AX7: v1 has exactly two emitters, "L" and "R", fed by input channels 0 and 1. AQ8: omnidirectional
// ideal point sources.
struct Emitter
{
    std::string id;
    int channel = 0;
    Vec3 position;
    double gainDb = 0.0;

    friend bool operator==(const Emitter&, const Emitter&) = default;
};

enum class OutputMode
{
    binaural,
    stereoSpeakers
};

// JSON value of an output mode ("binaural", "stereoSpeakers").
constexpr std::string_view outputModeName(OutputMode mode) noexcept
{
    switch (mode)
    {
    case OutputMode::binaural:
        return "binaural";
    case OutputMode::stereoSpeakers:
        return "stereoSpeakers";
    }
    return "";
}

// AQ6: v1 ships one generic HRTF.
inline constexpr std::string_view kHrtfIdGenericV1 = "generic-v1";

struct RenderSettings
{
    OutputMode outputMode = OutputMode::binaural;
    std::string hrtfId{kHrtfIdGenericV1};
    int maxReflectionOrder = 20;
    std::uint32_t tailSeed = 0; // seeds every random process in the render (determinism)

    friend bool operator==(const RenderSettings&, const RenderSettings&) = default;
};

struct SceneDescription
{
    // The version this value conforms to. The reader always sets it to kCurrentContractVersion,
    // because fields of a newer minor version are dropped when the scene is loaded.
    ContractVersion contractVersion = kCurrentContractVersion;
    Room room;
    Listener listener;
    std::vector<Emitter> emitters;
    RenderSettings render;
    // The "extensions" object as compact JSON text, preserved in round trips. Editor-only data
    // (e.g. UI colours) for the 3D Module. The Simulator must never read it. Compared as text, so
    // key order matters for operator==.
    std::string extensionsJson = "{}";

    friend bool operator==(const SceneDescription&, const SceneDescription&) = default;
};

} // namespace contract
