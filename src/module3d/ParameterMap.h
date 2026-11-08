#pragma once

// Mapping between the host parameters and the scene (Phase 07 scope 2). Pure C++, no JUCE.
//
// Host parameter IDs are FROZEN once released (CLAUDE.md): add new IDs, never rename or re-range.
// tests/state/parameter_ids_v1.json lists them; a test compares the plugin's parameters against it.
//
//   listener_x/y/z, emL_x/y/z, emR_x/y/z   0 .. 1, normalised WITHIN THE ROOM per axis: 0 and 1 are the
//                                           AX6 margins (0.1 m from the walls), so resizing the room
//                                           keeps relative positions (docs/contract/README.md, "3D Module
//                                           behaviour").
//   room_w/d/h                              1.5 .. 100 m, L = 1.5 (100 / 1.5)^x (decider D9)
//   output_trim_db                          -48 .. +24 dB, linear in dB, default 0 (AX2 note, phase-07.md)
//   output_mode                             choice: binaural, stereoSpeakers (wired in Phases 08/09;
//                                           Phase 07 does not apply it to the scene)
//
// The scene is a PURE FUNCTION of (parameter values, non-parameter scene fields): deriveScene(). The
// listener-emitter push-away (pushAwayFromListener, D1) is recomputed on every derivation and never
// written back to a parameter.
#include "contract/SceneDescription.h"

#include <array>
#include <cstddef>
#include <string_view>

namespace module3d {

enum ParamIndex : std::size_t
{
    kListenerX,
    kListenerY,
    kListenerZ,
    kEmLX,
    kEmLY,
    kEmLZ,
    kEmRX,
    kEmRY,
    kEmRZ,
    kRoomW,
    kRoomD,
    kRoomH,
    kOutputTrimDb,
    kOutputMode,
    kNumParams
};

enum class ParamKind
{
    Float,
    Choice
};

struct ParameterSpec
{
    std::string_view id;   // frozen
    std::string_view name; // display name
    ParamKind kind = ParamKind::Float;
    double min = 0.0; // plain value range (a Choice: 0 .. choices - 1)
    double max = 1.0;
    double defaultValue = 0.0;
    std::string_view unit;    // "", "m", "dB"
    std::string_view mapping; // "linear", "room-log", "choice"
};

inline constexpr std::array<std::string_view, 2> kOutputModeChoices{"binaural", "stereoSpeakers"};

// In ParamIndex order.
const std::array<ParameterSpec, kNumParams>& parameterSpecs() noexcept;

// Plain values in ParamIndex order (positions 0..1, room sides in metres, trim in dB, mode index).
using ParameterValues = std::array<double, kNumParams>;

// The defaults: the default scene (tests/scenes/valid/medium_room.json) expressed as parameters,
// trim 0 dB, output_mode binaural.
ParameterValues defaultParameterValues() noexcept;

// D9: L = 1.5 (100 / 1.5)^x, x <= 0 -> exactly 1.5, x >= 1 -> exactly 100, interior clamped to
// [1.5, 100] (NaN -> 1.5).
double roomSizeFromNormalized(double x) noexcept;
// The inverse: L <= 1.5 -> exactly 0, L >= 100 -> exactly 1, interior clamped to [0, 1] (NaN -> 0).
double normalizedFromRoomSize(double metres) noexcept;

// Normalised position (0..1 per axis within the margin box) <-> metres.
contract::Vec3 positionFromNormalized(const contract::Vec3& normalized,
                                      const contract::Vec3& roomDimensions) noexcept;
contract::Vec3 normalizedFromPosition(const contract::Vec3& metres,
                                      const contract::Vec3& roomDimensions) noexcept;

// The scene for these parameter values: the room size and the positions come from `values` (clamped;
// emitters pushed away from the listener), every other field from `base` (sanitised by
// SceneModel::sanitize). Always passes contract::validate(). Deterministic: the same inputs give the
// same scene, bit for bit.
contract::SceneDescription deriveScene(const ParameterValues& values, const contract::SceneDescription& base);

// The parameter values that describe `scene` (room size and normalised positions); trim and mode are
// taken from the arguments.
ParameterValues parameterValuesFromScene(const contract::SceneDescription& scene, double outputTrimDb = 0.0,
                                         double outputModeIndex = 0.0) noexcept;

} // namespace module3d
