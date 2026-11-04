#pragma once

// Semantic validation of a SceneDescription (ranges, counts, geometry). Structural checks (types,
// missing and unknown fields) happen while reading JSON (Json.h); validate() checks a value that
// is already well-formed, whether it came from JSON or was built in memory by the 3D Module.
#include "contract/Diagnostics.h"
#include "contract/SceneDescription.h"

#include <vector>

namespace contract {

// Limits of contract v1. Ranges are inclusive.
namespace limits {

// AQ3: material property ranges.
inline constexpr double kAbsorptionMin = 0.01;
inline constexpr double kAbsorptionMax = 1.0;
inline constexpr double kScatteringMin = 0.0;
inline constexpr double kScatteringMax = 1.0;
// AQ3 (render settings) and AX6 (room size and clearances).
inline constexpr double kGainDbMin = -60.0;
inline constexpr double kGainDbMax = 12.0;
inline constexpr int kMaxReflectionOrderMin = 0;
inline constexpr int kMaxReflectionOrderMax = 60;
inline constexpr double kRoomDimensionMinM = 1.5;
inline constexpr double kRoomDimensionMaxM = 100.0;
inline constexpr double kSurfaceClearanceM = 0.1;
inline constexpr double kEmitterListenerMinDistanceM = 0.3;
// AX7: exactly two emitters.
inline constexpr std::size_t kEmitterCount = 2;
// AX9: geometric limits (clearance, distance) are compared with this tolerance so that a value written
// at the limit in decimal (e.g. a distance of exactly 0.3 m, which is 0.29999999999999998 after
// subtracting two doubles) is accepted. 1 nm is far below anything audible.
inline constexpr double kGeometryToleranceM = 1e-9;

} // namespace limits

struct ValidationResult
{
    std::vector<Issue> issues; // errors and warnings, in document order

    bool ok() const noexcept { return !hasErrors(issues); }
};

// Never throws except std::bad_alloc.
ValidationResult validate(const SceneDescription& scene);

} // namespace contract
