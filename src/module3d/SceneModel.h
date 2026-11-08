#pragma once

// The 3D Module's editable scene (Phase 07 scope 1). It holds a contract::SceneDescription plus
// editor-only data (in `extensions`, which the Simulator never reads) and offers typed setters that
// clamp to valid values (AX6 margins), so toContract() always passes contract::validate().
// Pure C++, no JUCE, no Simulator (CLAUDE.md "contract boundary").
#include "contract/SceneDescription.h"

#include <string>

namespace module3d {

// Returns the contract version this 3D Module build produces.
const char* producedContractVersion() noexcept;

// AX6 margin box of a room: every coordinate in [0.1, dimension - 0.1].
struct MarginBox
{
    contract::Vec3 lo;
    contract::Vec3 hi;
};
MarginBox marginBox(const contract::Vec3& roomDimensions) noexcept;

// Clamps to the AX6 room range [1.5, 100] m per side (NaN -> 1.5).
double clampRoomDimension(double metres) noexcept;
// Clamps a point into the margin box (NaN -> the low side).
contract::Vec3 clampToMarginBox(const contract::Vec3& p, const MarginBox& box) noexcept;

// Phase 07 scope 2 (decider D1): the point p of the margin box with |p - l| >= 0.3 m nearest to the
// emitter e; p = e when |e - l| >= 0.3 m. Otherwise p = l + 0.3 u, u the unit vector maximising u . d
// with l + 0.3 u in the box, d = (e - l) / |e - l|, or d = +y (AQ1 forward) when e == l; exact ties are
// broken by the largest u . y, then u . x, then u . z. l and e must lie in the box (the box of a valid
// room always has room for the 0.3 m sphere around any listener: its sides are >= 1.3 m).
contract::Vec3 pushAwayFromListener(const contract::Vec3& emitter, const contract::Vec3& listener,
                                    const MarginBox& box) noexcept;

class SceneModel
{
public:
    // Starts from `initial`, clamped so that it validates (see sanitize()).
    explicit SceneModel(const contract::SceneDescription& initial);

    // Room size, clamped to [1.5, 100] m per side. Positions are re-clamped into the new margin box
    // and the emitters pushed away from the listener (absolute positions; the normalised mapping of
    // host parameters is ParameterMap's job).
    void setRoomDimensions(const contract::Vec3& metres);
    // Clamped into the margin box; the emitters are pushed away from the listener as needed.
    void setListenerPosition(const contract::Vec3& p);
    // emitterIndex 0 = L, 1 = R. Clamped into the margin box, then pushed away from the listener.
    void setEmitterPosition(int emitterIndex, const contract::Vec3& p);
    // Clamped to [-60, +12] dB (NaN -> 0 dB).
    void setEmitterGainDb(int emitterIndex, double gainDb);
    // Clamped to [0.01, 1] per band and [0, 1] (NaN -> the lower limit).
    void setSurfaceMaterial(contract::SurfaceId surface, const contract::SurfaceMaterial& material);
    void setTailSeed(std::uint32_t seed) noexcept;
    void setMaxReflectionOrder(int order) noexcept; // clamped to [0, 60]
    void setOutputMode(contract::OutputMode mode) noexcept;
    // Editor-only data: must be the text of a JSON object; anything else is replaced by "{}".
    void setExtensionsJson(std::string json);

    const contract::SceneDescription& scene() const noexcept { return scene_; }
    // The scene as the contract value. Always passes contract::validate().
    contract::SceneDescription toContract() const { return scene_; }

    // Clamps every field of `scene` to a valid value (AX6 margins, AQ3 ranges, AX7 emitters "L" on
    // channel 0 and "R" on channel 1, the current contract version, hrtfId generic-v1).
    static contract::SceneDescription sanitize(contract::SceneDescription scene);

private:
    SceneModel(contract::SceneDescription scene, int raw); // takes `scene` as is, then enforcePositions()
    void enforcePositions();

    contract::SceneDescription scene_;
};

} // namespace module3d
