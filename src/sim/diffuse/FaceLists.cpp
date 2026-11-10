#include "sim/diffuse/FaceLists.h"

#include <algorithm>
#include <cmath>

namespace sim::diffuse {

namespace {

// One axis of the lattice (Allen & Berkley; src/sim/ism/ImageSources.h): image (n, q) of coordinate
// x is 2nL + (1 - 2q)x, with |n - q| reflections on the min wall and |n| on the max wall.
struct AxisImage
{
    double offset = 0.0;
    double sign = 1.0;
    int hitsMin = 0;
    int hitsMax = 0;
};

std::vector<AxisImage> axisImages(double length, double coordinate, double gather, double reach)
{
    std::vector<AxisImage> out;
    const auto k = static_cast<long>(std::ceil(reach / (2.0 * length))) + 2;
    for (long n = -k; n <= k; ++n)
        for (int q = 0; q < 2; ++q)
        {
            const double pos = 2.0 * static_cast<double>(n) * length + (1 - 2 * q) * coordinate;
            if (std::abs(pos - gather) > reach)
                continue;
            out.push_back({2.0 * static_cast<double>(n) * length, q == 0 ? 1.0 : -1.0,
                           static_cast<int>(std::labs(n - q)), static_cast<int>(std::labs(n))});
        }
    return out;
}

} // namespace

FaceLists makeFaceLists(const contract::Vec3& dims, const contract::Vec3& gather, double reachM,
                        const std::array<contract::BandArray, contract::kNumSurfaces>& bandsSpecularPerFace)
{
    const double d[3]{dims.x, dims.y, dims.z};
    const double g[3]{gather.x, gather.y, gather.z};
    const double reach = reachM + std::sqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
    std::array<std::vector<AxisImage>, 3> axes;
    for (int a = 0; a < 3; ++a)
        axes[static_cast<std::size_t>(a)] = axisImages(d[a], g[a], g[a], reach);

    std::vector<GatherImage> all;
    for (const auto& ix : axes[0])
        for (const auto& iy : axes[1])
            for (const auto& iz : axes[2])
            {
                GatherImage im;
                const AxisImage* per[3]{&ix, &iy, &iz};
                double r2 = 0.0;
                for (int a = 0; a < 3; ++a)
                {
                    im.position[a] = per[a]->offset + per[a]->sign * g[a];
                    const double dd = im.position[a] - g[a];
                    r2 += dd * dd;
                }
                im.distanceM = std::sqrt(r2);
                if (im.distanceM > reach)
                    continue;
                const std::array<int, contract::kNumSurfaces> hits{ix.hitsMin, ix.hitsMax, iy.hitsMin,
                                                                   iy.hitsMax, iz.hitsMin, iz.hitsMax};
                for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
                {
                    double f = 1.0;
                    for (std::size_t s = 0; s < contract::kNumSurfaces; ++s)
                        for (int h = 0; h < hits[s]; ++h)
                            f *= bandsSpecularPerFace[s][b];
                    im.bandsSpecular[b] = f;
                }
                all.push_back(im);
            }

    FaceLists lists;
    lists.latticeSize = all.size();
    for (std::size_t f = 0; f < contract::kNumSurfaces; ++f)
    {
        const std::size_t axis = f / 2;
        const bool high = (f % 2) == 1;
        const double plane = high ? d[axis] : 0.0;
        auto& out = lists.faces[f];
        for (const auto& im : all)
        {
            const bool front = high ? im.position[axis] < plane - 1e-12 : im.position[axis] > plane + 1e-12;
            if (front)
                out.push_back(im);
        }
        std::stable_sort(out.begin(), out.end(), [](const GatherImage& a, const GatherImage& b) {
            return a.distanceM < b.distanceM;
        });
    }
    return lists;
}

} // namespace sim::diffuse
