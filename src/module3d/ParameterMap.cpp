#include "module3d/ParameterMap.h"

#include "contract/Validate.h"
#include "module3d/SceneModel.h"

#include <cmath>

namespace module3d {

namespace {

namespace lim = contract::limits;

// The default scene (tests/scenes/valid/medium_room.json: 8 x 12 x 4 m, listener (4, 3, 1.7),
// L (3, 9, 2), R (5, 9, 2)) as normalised positions: (p - 0.1) / (side - 0.2).
constexpr double norm(double p, double side) noexcept
{
    return (p - lim::kSurfaceClearanceM) / (side - 2.0 * lim::kSurfaceClearanceM);
}

constexpr double kDefaultW = 8.0;
constexpr double kDefaultD = 12.0;
constexpr double kDefaultH = 4.0;

double clamp01(double v) noexcept
{
    if (!(v >= 0.0)) // also NaN
        return 0.0;
    return v > 1.0 ? 1.0 : v;
}

double axisFromNormalized(double n, double side) noexcept
{
    const double lo = lim::kSurfaceClearanceM;
    return lo + clamp01(n) * (side - 2.0 * lo);
}

double normalizedFromAxis(double p, double side) noexcept
{
    const double lo = lim::kSurfaceClearanceM;
    return clamp01((p - lo) / (side - 2.0 * lo));
}

} // namespace

const std::array<ParameterSpec, kNumParams>& parameterSpecs() noexcept
{
    using K = ParamKind;
    static const std::array<ParameterSpec, kNumParams> specs{{
        {"listener_x", "Listener X", K::Float, 0.0, 1.0, norm(4.0, kDefaultW), "", "linear"},
        {"listener_y", "Listener Y", K::Float, 0.0, 1.0, norm(3.0, kDefaultD), "", "linear"},
        {"listener_z", "Listener Z", K::Float, 0.0, 1.0, norm(1.7, kDefaultH), "", "linear"},
        {"emL_x", "Emitter L X", K::Float, 0.0, 1.0, norm(3.0, kDefaultW), "", "linear"},
        {"emL_y", "Emitter L Y", K::Float, 0.0, 1.0, norm(9.0, kDefaultD), "", "linear"},
        {"emL_z", "Emitter L Z", K::Float, 0.0, 1.0, norm(2.0, kDefaultH), "", "linear"},
        {"emR_x", "Emitter R X", K::Float, 0.0, 1.0, norm(5.0, kDefaultW), "", "linear"},
        {"emR_y", "Emitter R Y", K::Float, 0.0, 1.0, norm(9.0, kDefaultD), "", "linear"},
        {"emR_z", "Emitter R Z", K::Float, 0.0, 1.0, norm(2.0, kDefaultH), "", "linear"},
        {"room_w", "Room width", K::Float, lim::kRoomDimensionMinM, lim::kRoomDimensionMaxM, kDefaultW, "m",
         "room-log"},
        {"room_d", "Room depth", K::Float, lim::kRoomDimensionMinM, lim::kRoomDimensionMaxM, kDefaultD, "m",
         "room-log"},
        {"room_h", "Room height", K::Float, lim::kRoomDimensionMinM, lim::kRoomDimensionMaxM, kDefaultH, "m",
         "room-log"},
        {"output_trim_db", "Output trim", K::Float, -48.0, 24.0, 0.0, "dB", "linear"},
        {"output_mode", "Output mode", K::Choice, 0.0, 1.0, 0.0, "", "choice"},
    }};
    return specs;
}

ParameterValues defaultParameterValues() noexcept
{
    ParameterValues v{};
    const auto& specs = parameterSpecs();
    for (std::size_t i = 0; i < kNumParams; ++i)
        v[i] = specs[i].defaultValue;
    return v;
}

double roomSizeFromNormalized(double x) noexcept
{
    const double lo = lim::kRoomDimensionMinM;
    const double hi = lim::kRoomDimensionMaxM;
    if (!(x > 0.0)) // x <= 0 and NaN
        return lo;
    if (x >= 1.0)
        return hi;
    const double l = lo * std::pow(hi / lo, x);
    return l < lo ? lo : (l > hi ? hi : l);
}

double normalizedFromRoomSize(double metres) noexcept
{
    const double lo = lim::kRoomDimensionMinM;
    const double hi = lim::kRoomDimensionMaxM;
    if (!(metres > lo)) // metres <= 1.5 and NaN
        return 0.0;
    if (metres >= hi)
        return 1.0;
    const double x = std::log(metres / lo) / std::log(hi / lo);
    return x < 0.0 ? 0.0 : (x > 1.0 ? 1.0 : x);
}

contract::Vec3 positionFromNormalized(const contract::Vec3& n, const contract::Vec3& d) noexcept
{
    return {axisFromNormalized(n.x, d.x), axisFromNormalized(n.y, d.y), axisFromNormalized(n.z, d.z)};
}

contract::Vec3 normalizedFromPosition(const contract::Vec3& p, const contract::Vec3& d) noexcept
{
    return {normalizedFromAxis(p.x, d.x), normalizedFromAxis(p.y, d.y), normalizedFromAxis(p.z, d.z)};
}

contract::SceneDescription deriveScene(const ParameterValues& v, const contract::SceneDescription& base)
{
    contract::SceneDescription s = SceneModel::sanitize(base);
    const contract::Vec3 dims{clampRoomDimension(v[kRoomW]), clampRoomDimension(v[kRoomD]),
                              clampRoomDimension(v[kRoomH])};
    s.room.geometry.dimensions = dims;
    const MarginBox box = marginBox(dims);
    s.listener.position = positionFromNormalized({v[kListenerX], v[kListenerY], v[kListenerZ]}, dims);
    // sanitize() put L at index 0 and R at index 1.
    const contract::Vec3 l = positionFromNormalized({v[kEmLX], v[kEmLY], v[kEmLZ]}, dims);
    const contract::Vec3 r = positionFromNormalized({v[kEmRX], v[kEmRY], v[kEmRZ]}, dims);
    s.emitters[0].position = pushAwayFromListener(l, s.listener.position, box);
    s.emitters[1].position = pushAwayFromListener(r, s.listener.position, box);
    // output_mode is not applied in Phase 07 (wired in Phases 08/09): the stored outputMode stays.
    return s;
}

ParameterValues parameterValuesFromScene(const contract::SceneDescription& scene, double outputTrimDb,
                                         double outputModeIndex) noexcept
{
    ParameterValues v{};
    const auto& d = scene.room.geometry.dimensions;
    v[kRoomW] = clampRoomDimension(d.x);
    v[kRoomD] = clampRoomDimension(d.y);
    v[kRoomH] = clampRoomDimension(d.z);
    const contract::Vec3 dims{v[kRoomW], v[kRoomD], v[kRoomH]};
    const auto l = normalizedFromPosition(scene.listener.position, dims);
    v[kListenerX] = l.x;
    v[kListenerY] = l.y;
    v[kListenerZ] = l.z;
    for (const auto& e : scene.emitters)
    {
        const auto n = normalizedFromPosition(e.position, dims);
        const std::size_t base = e.id == "R" ? kEmRX : kEmLX;
        v[base] = n.x;
        v[base + 1] = n.y;
        v[base + 2] = n.z;
    }
    v[kOutputTrimDb] = outputTrimDb;
    v[kOutputMode] = outputModeIndex;
    return v;
}

} // namespace module3d
