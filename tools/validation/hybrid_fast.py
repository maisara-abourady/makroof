"""Compiled patch-to-patch kernel of the reference hybrid (phase-05b scope 0 ladder, 1.25 m rung).

`tools/acoustics/ref_hybrid.RoomKernel` builds the kernel with numpy, one lattice image at a time over all
N² patch pairs: ≈ 3.3 s per image at ℓ = 1.25 m (1 408 patches), i.e. ≈ 4 h per Table 5.2 layout case
with t_mix,e = 0.38 s (2 917 images). `FastRoomKernel` computes the same kernel, term by term (same pair
tests, same 2 × 2 sample points, same near-field contour integral on 2 × 2 Gauss points, same linear
deposit into 1 ms bins), with numba, parallel over the emitting patch. It is restricted to what the
phase-05b ladder needs: one material variant, one band column, no air (the air is factored out,
`phase05b.hybrid_env_factorised`). Agreement with `RoomKernel` is tested in
`tools/validation/tests/test_hybrid_fast.py` (skipped when numba is not installed).

numba is an offline dependency of this script only: `pip install --require-hashes -r
tools/validation/requirements-offline.txt`. CI does not install it.
"""

from __future__ import annotations

import numpy as np

from tools.acoustics import radiosity
from tools.acoustics import ref_hybrid as rh

try:
    import numba
    from numba import njit, prange
except ImportError:  # pragma: no cover - CI has no numba
    numba = None


if numba is not None:

    @njit(cache=True, fastmath=False)
    def _ff_point_quad(px, py, pz, nx, ny, nz, poly):
        s = 0.0
        for v in range(4):
            w = (v + 1) % 4
            ax, ay, az = poly[v, 0] - px, poly[v, 1] - py, poly[v, 2] - pz
            bx, by, bz = poly[w, 0] - px, poly[w, 1] - py, poly[w, 2] - pz
            cx, cy, cz = ay * bz - az * by, az * bx - ax * bz, ax * by - ay * bx
            ncr = np.sqrt(cx * cx + cy * cy + cz * cz)
            gamma = np.arctan2(ncr, ax * bx + ay * by + az * bz)
            if ncr > 0:
                s += (cx * nx + cy * ny + cz * nz) / ncr * gamma
        return abs(s) / (2 * np.pi)

    @njit(parallel=True, cache=True)
    def _accumulate_image(K, T, off, sg, spec, centers, normals, areas, diag, sub, gauss, gw, corners, reach,
                          inv_cdt, near_factor):
        N = centers.shape[0]
        m = sub.shape[1]
        for k in prange(N):
            ckx = off[0] + sg[0] * centers[k, 0]
            cky = off[1] + sg[1] * centers[k, 1]
            ckz = off[2] + sg[2] * centers[k, 2]
            nkx, nky, nkz = sg[0] * normals[k, 0], sg[1] * normals[k, 1], sg[2] * normals[k, 2]
            vals = np.empty(m * m)
            dists = np.empty(m * m)
            for l in range(N):
                dx = centers[l, 0] - ckx
                dy = centers[l, 1] - cky
                dz = centers[l, 2] - ckz
                if dx * nkx + dy * nky + dz * nkz <= 1e-9:
                    continue
                if -(dx * normals[l, 0] + dy * normals[l, 1] + dz * normals[l, 2]) <= 1e-9:
                    continue
                dc = np.sqrt(dx * dx + dy * dy + dz * dz)
                if dc > reach + diag[k] + diag[l]:
                    continue
                den = 0.0
                for i in range(m):
                    sx = off[0] + sg[0] * sub[k, i, 0]
                    sy = off[1] + sg[1] * sub[k, i, 1]
                    sz = off[2] + sg[2] * sub[k, i, 2]
                    for j in range(m):
                        vx, vy, vz = sub[l, j, 0] - sx, sub[l, j, 1] - sy, sub[l, j, 2] - sz
                        dist = np.sqrt(vx * vx + vy * vy + vz * vz)
                        safe = max(dist, 1e-9)
                        ck_ = max((vx * nkx + vy * nky + vz * nkz) / safe, 0.0)
                        cl_ = max(-(vx * normals[l, 0] + vy * normals[l, 1] + vz * normals[l, 2]) / safe, 0.0)
                        ker = ck_ * cl_ / (safe * safe)
                        vals[i * m + j] = ker
                        dists[i * m + j] = dist
                        den += ker
                if not den > 0:
                    continue
                F = areas[l] / (m * m * np.pi) * den
                if dc < near_factor * max(diag[k], diag[l]):
                    F = 0.0
                    for g in range(gauss.shape[1]):
                        px = off[0] + sg[0] * gauss[k, g, 0]
                        py = off[1] + sg[1] * gauss[k, g, 1]
                        pz = off[2] + sg[2] * gauss[k, g, 2]
                        F += gw[g] * _ff_point_quad(px, py, pz, nkx, nky, nkz, corners[l])
                base = (k * N + l) * T
                for q in range(m * m):
                    val = F * vals[q] / den * spec
                    u = max(dists[q] * inv_cdt, 0.0)
                    i0 = int(np.floor(u))
                    f = u - i0
                    if i0 < T:
                        K[base + i0] += np.float32(val * (1 - f))
                    if i0 + 1 < T:
                        K[base + i0 + 1] += np.float32(val * f)


class FastRoomKernel:
    """Drop-in for `ref_hybrid.RoomKernel` with one variant (no air) and one band (``band``), for
    `ref_hybrid.injection`, `ref_hybrid.gather_kernel` and `phase05b.lean_solve`."""

    def __init__(self, dims, patch_size: float, t_end_s: float, variant: rh.Variant, band: int, dt: float = rh.DT,
                 q_dist: int = 2, near_factor: float = 3.0, log=None):
        if numba is None:
            raise RuntimeError("numba is not installed (tools/validation/requirements-offline.txt)")
        if np.any(variant.m_air != 0):
            raise ValueError("FastRoomKernel computes without air (factor it out)")
        self.dims = tuple(float(x) for x in dims)
        self.dt = dt
        self.T = int(np.ceil(t_end_s / dt))
        self.p = radiosity.box_patches(self.dims, patch_size)
        self.N = len(self.p.areas)
        self.variants = [variant]
        self.bands = (int(band),)
        self.patch_size = patch_size
        self.reach = rh.C_SOUND * t_end_s
        lat = rh.lattice(self.dims, self.reach)
        p = self.p
        diag = np.linalg.norm(p.u + p.v, axis=1)
        spec = rh.specular_factor(lat.hits, variant.spec[[band]])[0]  # (M,)
        sub = np.ascontiguousarray(rh._sub_points(p, q_dist))
        x, w = np.polynomial.legendre.leggauss(2)
        x, w = 0.5 * (x + 1), 0.5 * w
        gu, gv = np.meshgrid(x, x, indexing="ij")
        gw = np.ascontiguousarray(np.outer(w, w).ravel())
        gauss = np.ascontiguousarray(p.corners[:, 0][:, None, :] + gu.ravel()[None, :, None] * p.u[:, None, :]
                                     + gv.ravel()[None, :, None] * p.v[:, None, :])
        K = np.zeros(self.N * self.N * self.T, dtype=np.float32)
        centers, normals = np.ascontiguousarray(p.centers), np.ascontiguousarray(p.normals)
        corners = np.ascontiguousarray(p.corners)
        for mi in range(len(lat.gap)):
            _accumulate_image(K, self.T, lat.offset[mi].astype(np.float64), lat.sign[mi].astype(np.float64),
                              float(spec[mi]), centers, normals, p.areas, diag, sub, gauss, gw, corners, self.reach,
                              1.0 / (rh.C_SOUND * dt), near_factor)
            if log and mi % 500 == 0:
                log(f"fast kernel: image {mi}/{len(lat.gap)}")
        self.K = K[:, None]
        self.lattice_size = len(lat.gap)

    def kernel(self, v: int, b: int) -> np.ndarray:
        return self.K[:, 0].reshape(self.N, self.N, self.T)
