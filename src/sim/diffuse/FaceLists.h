#pragma once

// Gather targets of the next-event estimate (AX39; Kuttruff Eq. 4.29 with transport over specular
// images, Eq. 4.35): the lattice images of a gather point (the listener, or an emitter for the
// listener-started set), split per face into the images that lie on the room side of that face's
// plane, each sorted by distance from the gather point, with its specular factor
// prod_f ((1 - a_f,b)(1 - s_f))^hits_f per band (the §5.2 split: the specular share of every wall
// the route meets). The image with no reflections is the gather point itself.
#include "contract/SceneDescription.h"

#include <array>
#include <cstddef>
#include <vector>

namespace sim::diffuse {

struct GatherImage
{
    double position[3]{};
    double distanceM = 0.0; // from the gather point
    contract::BandArray bandsSpecular{};
};

struct FaceLists
{
    // faces[f]: images in front of face f (surfaceIndex order), sorted by distance (stable).
    std::array<std::vector<GatherImage>, contract::kNumSurfaces> faces;
    std::size_t latticeSize = 0;
};

// Images of `gather` whose distance from it is at most reachM + |dims| (a path segment from a wall
// point to an image is at most reachM long and the wall point lies within |dims| of the gather
// point). bandsSpecularPerFace[f][b] = (1 - a_f,b)(1 - s_f).
FaceLists makeFaceLists(const contract::Vec3& dims, const contract::Vec3& gather, double reachM,
                        const std::array<contract::BandArray, contract::kNumSurfaces>& bandsSpecularPerFace);

} // namespace sim::diffuse
