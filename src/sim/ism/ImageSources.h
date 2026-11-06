#pragma once

// Image-source method (ISM) for a shoebox room (AQ2: the exact early part of the hybrid model).
//
// Lattice enumeration (Allen & Berkley 1979): along each axis, with room size L and source
// coordinate s, the images are at 2nL + (1 - 2p)s for n in Z and p in {0, 1}. Such an image has
// |n - p| reflections on the min wall (coordinate 0) and |n| on the max wall (coordinate L). The
// three axes combine freely, and every image of a shoebox is visible from every point inside it,
// so there is no visibility test. The order of an image is its total number of reflections.
#include "contract/SceneDescription.h"

#include <array>
#include <cstddef>
#include <optional>
#include <vector>

namespace sim::ism {

// Speed of sound in air at 20 degC (AX4 atmosphere), m/s.
inline constexpr double kSpeedOfSoundMps = 343.0;

// AQ8 hook for source directivity (backlog B7): per-band pressure gain for a direction of emission,
// given as a unit vector in the source's own frame (x right, y forward, z up). v1 sources are
// omnidirectional; Phase 03 only ever passes omniDirectivity.
using Directivity = contract::BandArray (*)(const contract::Vec3& emissionDirection);
contract::BandArray omniDirectivity(const contract::Vec3& emissionDirection) noexcept;

struct ImageSource
{
    contract::Vec3 position;   // image position in room coordinates (m)
    double distanceM = 0.0;    // |position - listener|
    double arrivalTimeS = 0.0; // distanceM / kSpeedOfSoundMps (not time-aligned, see AX1)
    int order = 0;             // total number of reflections (0 = direct path)
    std::array<int, contract::kNumSurfaces> hits{}; // reflections per surface, by surfaceIndex()
    contract::Vec3 arrivalDirection;  // unit vector from the listener towards the image (Phases 08/09)
    contract::Vec3 emissionDirection; // unit vector, direction the path leaves the real source
    // Pressure amplitude per band at the listener:
    //   gain / r * prod_s (sqrt(1 - a_{s,b}) * sqrt(1 - scat_s))^hits_s * air_b(r) * directivity_b
    // (AQ3: sqrt on pressure, scattering removes (1 - s) of the specular *energy* per reflection;
    // AX2: 1/r with a direct path at 1 m = gain; AX4: air absorption over the path length).
    contract::BandArray bandsAmplitude{};
};

// Energy that scattering removed from one specular path (sum over its reflections), per band, at
// the arrival time of that path (AX16). Same units as bandsAmplitude squared. Phase 04 feeds it into the
// tail; Phase 03 doesn't render it.
struct ScatteredEnergy
{
    double arrivalTimeS = 0.0;
    int order = 0;
    contract::BandArray bandsEnergy{};
    contract::Vec3 arrivalDirection; // the specular path's direction of arrival (AX16: same path)
};

struct ImageSourceSet
{
    std::vector<ImageSource> images;        // sorted by arrival time; images[0] is the direct path
    std::vector<ScatteredEnergy> scattered; // sorted by arrival time; only paths with energy > 0
};

struct ImageSourceOptions
{
    int maxOrder = 0; // reflection orders 0..maxOrder (if maxArrivalTimeS <= 0)
    // AX20 (Phase 04 hybrid IR): when > 0, the list is time-bounded instead: every image of any
    // order whose arrival time is < maxArrivalTimeS, and maxOrder is ignored.
    double maxArrivalTimeS = 0.0;
    double gain = 1.0;         // linear emitter gain (10^(gainDb / 20))
    bool airAbsorption = true; // AX4; false only for validation against references
    // Validation only (AX4 atmosphere override, render_cli --atmosphere): air attenuation per band
    // in dB/m used instead of the AX4 atmosphere when set (and airAbsorption is true).
    std::optional<contract::BandArray> airDbPerMetreOverride;
    Directivity directivity = omniDirectivity; // AQ8
};

// Number of images of order <= maxOrder in a shoebox: (2N + 1)(2N^2 + 2N + 3) / 3.
std::size_t imageCount(int maxOrder) noexcept;

// nu_r(i): the number of image sources of orders 1..i (Kuttruff Eq. 9.23), imageCount(i) - 1:
// nu_r(10) = 1 560, nu_r(30) = 37 880.
std::size_t reflectionImageCount(int maxOrder) noexcept;

// AX22: arrival time (from emission, s) of the n-th reflection image (n >= 1) of `source` at
// `listener` in arrival order, counting every lattice image, pruned or not (as Kuttruff Eq. 9.23
// counts them); the direct path is not counted. Independent of the materials.
double nthReflectionArrivalTimeS(const contract::Room& room, const contract::Vec3& source,
                                 const contract::Vec3& listener, std::size_t n);

// All images of `source` seen from `listener` up to options.maxOrder (or, with
// options.maxArrivalTimeS > 0, every image arriving before that time, AX20). Images whose specular
// amplitude and scattered energy are zero in every band (a reflection off an a = 1 surface) are
// dropped, except the direct path, which is always images[0]. Deterministic: ties in arrival time
// keep the enumeration order. Requires a validated scene (positions inside the room).
ImageSourceSet computeImageSources(const contract::Room& room, const contract::Vec3& source,
                                   const contract::Vec3& listener, const ImageSourceOptions& options);

} // namespace sim::ism
