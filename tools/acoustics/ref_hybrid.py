"""Reference hybrid with early Lambert-scattered energy (AX21; phase-05 scope 6; BUILD_PLAN §5 B11).

Reference tool only: nothing here changes `src/sim` or renders audio for the product. It computes,
per octave band, the **diffuse** (Lambert-scattered) energy that the Phase 04 hybrid IR leaves out
before t_mix,e (AX21: Phase 03 renders (1-α)(1-s) per hit and no scattered energy), as an energy
envelope in 1 ms bins at the listener (Kuttruff §9.8: typical class width).

Model (phase-05 scope 6, "Reference hybrid"):

- **Injection** (Kuttruff Eq. 4.24; Gilbert, §4.6): at every specular hit of the source's image
  paths, the fraction s(1-α) of the incident energy enters the Lambert boundary patch hit, at the
  hit time. A source image with hit counts n_f carries Π_f ((1-α_f)(1-s_f))^n_f of the emitted
  energy (the specular part, as Phase 03 renders it); the energy it puts on patch l is the exact
  solid angle of l seen from the image (unit intensity per steradian: a direct path at r gives
  1/r², AX2), distributed in time over q×q points of the patch.
- **Propagation, mixed specular/diffuse** (Joyce's reflection matrix, Kuttruff §4.6 Eq. 4.35,
  with the §5.2 split s(1-α) / (1-s)(1-α)): energy re-radiated per Lambert from patch k reaches
  patch l directly or over specular reflections, i.e. from the **images of patch k** in the
  shoebox lattice (each with its Π((1-α)(1-s))^n factor). On arrival, s_l(1-α_l) is re-radiated
  diffusely from l; the (1-s_l)(1-α_l) part continues specularly and is the next image of k. The
  transfer weight is the form factor from the image patch to l (exact contour integral for
  near pairs, Lambert kernel on 2×2 × 2×2 sample points otherwise), spread in time by the
  kernel-weighted path lengths (as `radiosity.form_factors`).
- **Gathering** (Eq. 4.29): a patch with Lambert exitance sends Φ_k·Ω_k(r)/(π A_k) to the point
  listener r directly and over its images (Ω_k(r): solid angle of the (image) patch at r).
- Air absorption exp(-m·R) on every path (AX4, m = the energy coefficient D/4.343).

The recursion Φ = D·(Inc + K∗Φ), D = diag(s(1-α)), is solved generation by generation with
FFT convolution (linear, truncated to the analysis length each generation, so it is exact in
time up to the binning). Time bins: bin n covers emission time [n·dt, (n+1)·dt); energies are
deposited at bin centres by linear interpolation.

Also here (needed to compare with the simulator): a Python re-implementation of the Phase 04
mixing time (expected k_eff rule, AX22 realised-k fallback) and of the AX16 matching level
E_target, for the X-b bound ΔL_b = 10·log10(E_target(AX16) / E_target(hybrid)) (phase-05
scope 6, AX16). Cross-checked against `render_cli --diagnostics` in the tests.
"""

from __future__ import annotations

from dataclasses import dataclass

import numpy as np

from tools.acoustics import radiosity

C_SOUND = 343.0  # m/s, src/sim/ism kSpeedOfSoundMps (AX4 atmosphere)
DT = 1e-3  # 1 ms time step (phase-05 scope 6: Kuttruff §9.8 typical class width)
ENERGY_DECAY_PER_T60 = np.log(1e6)  # src/sim/tail kEnergyDecayPerT60
MATCH_NORMALISATION_S = 0.010  # kMatchNormalisationS
MIX_MIN_AFTER_DIRECT_S = 0.020  # kMixingMinAfterDirectS
WINDOW_START_AFTER_DIRECT_S = 0.0025  # kMatchWindowStartAfterDirectS
CROSSFADE_HALF_S = 0.0025  # kCrossfadeHalfS
MIX_MIN_KEFF = 19.0  # kMixingMinKeff
REALISED_K_BANDS = (3, 4, 5)  # 500 Hz, 1 kHz, 2 kHz (kRealisedKBands)
IMAGE_COUNT_CAP = 1560  # AX22: N_cap = nu_r(10)
N_BANDS = 8


# ------------------------------------------------------------------------------------------
# Shoebox lattice (Allen & Berkley; src/sim/ism/ImageSources.h)
# ------------------------------------------------------------------------------------------


@dataclass
class Lattice:
    offset: np.ndarray  # (M, 3): image of p is offset + sign * p
    sign: np.ndarray  # (M, 3) +-1
    hits: np.ndarray  # (M, 6) reflections per face (xMin, xMax, yMin, yMax, floor, ceiling)
    gap: np.ndarray  # (M,) distance from the image cell to the room (m)

    def map(self, p: np.ndarray) -> np.ndarray:
        """Images of points p (..., 3) -> (M, ..., 3)."""
        ext = (slice(None),) + (None,) * (p.ndim - 1) + (slice(None),)
        return self.offset[ext] + self.sign[ext] * p[None]


def lattice(dims, reach: float) -> Lattice:
    """Every image cell (n, q per axis) whose cell lies within ``reach`` of the room. Along an
    axis of length L, image (n, q) of coordinate x is 2nL + (1 - 2q)x with |n - q| reflections on
    the min wall and |n| on the max wall (src/sim/ism/ImageSources.h)."""
    per_axis = []
    for L in dims:
        K = int(np.ceil(reach / (2 * L))) + 2
        rows = []
        for n in range(-K, K + 1):
            for q in (0, 1):
                lo = 2 * n * L - q * L
                gap = max(0.0, lo - L, -(lo + L))
                if gap <= reach:
                    rows.append((2 * n * L, 1 - 2 * q, abs(n - q), abs(n), gap))
        per_axis.append(np.array(rows))
    ax, ay, az = per_axis
    I, J, K = np.meshgrid(np.arange(len(ax)), np.arange(len(ay)), np.arange(len(az)), indexing="ij")
    I, J, K = I.ravel(), J.ravel(), K.ravel()
    gap = np.sqrt(ax[I, 4] ** 2 + ay[J, 4] ** 2 + az[K, 4] ** 2)
    keep = gap <= reach
    I, J, K, gap = I[keep], J[keep], K[keep], gap[keep]
    offset = np.stack([ax[I, 0], ay[J, 0], az[K, 0]], axis=1)
    sign = np.stack([ax[I, 1], ay[J, 1], az[K, 1]], axis=1)
    hits = np.stack([ax[I, 2], ax[I, 3], ay[J, 2], ay[J, 3], az[K, 2], az[K, 3]], axis=1).astype(np.int64)
    o = np.argsort(gap, kind="stable")
    return Lattice(offset[o], sign[o], hits[o], gap[o])


def specular_factor(hits: np.ndarray, g: np.ndarray) -> np.ndarray:
    """Π_f g_f^hits_f for hits (M, 6) and per-face factors g (..., 6) -> (..., M); g may be 0."""
    lg = np.log(np.maximum(g, 1e-300))
    return np.exp(np.einsum("mf,...f->...m", hits.astype(np.float64), lg))


# ------------------------------------------------------------------------------------------
# Geometry helpers
# ------------------------------------------------------------------------------------------


def solid_angle_quad(points: np.ndarray, quads: np.ndarray) -> np.ndarray:
    """Solid angle of planar convex quads (Q, 4, 3) seen from points (Q, 3) (Van Oosterom &
    Strackee, two triangles, signed sum). Broadcasts over leading axes."""

    def tri(a, b, c):
        num = np.einsum("...k,...k->...", a, np.cross(b, c))
        la, lb, lc = (np.linalg.norm(x, axis=-1) for x in (a, b, c))
        den = la * lb * lc + np.einsum("...k,...k->...", a, b) * lc + np.einsum("...k,...k->...", a, c) * lb \
            + np.einsum("...k,...k->...", b, c) * la
        return 2 * np.arctan2(num, den)

    r = quads - points[..., None, :]
    return np.abs(tri(r[..., 0, :], r[..., 1, :], r[..., 2, :]) + tri(r[..., 0, :], r[..., 2, :], r[..., 3, :]))


def _sub_points(p: radiosity.Patches, q: int) -> np.ndarray:
    """q×q midpoints of every patch: (N, q*q, 3)."""
    s = (np.arange(q) + 0.5) / q
    su, sv = np.meshgrid(s, s, indexing="ij")
    return p.corners[:, 0][:, None, :] + su.ravel()[None, :, None] * p.u[:, None, :] + sv.ravel()[None, :, None] * p.v[:, None, :]


def _ff_points_to_polygons(points, normals, polys):
    """Form factor from differential areas (P, G, 3) with normals (P, 3) to polygons (P, 4, 3)
    (contour integral, as radiosity._point_to_polygon_ff, vectorised over pairs): (P, G)."""
    r = polys[:, None, :, :] - points[:, :, None, :]  # (P, G, 4, 3)
    r1 = np.roll(r, -1, axis=2)
    cr = np.cross(r, r1)
    ncr = np.linalg.norm(cr, axis=3)
    gamma = np.arctan2(ncr, np.einsum("pgvk,pgvk->pgv", r, r1))
    with np.errstate(invalid="ignore", divide="ignore"):
        g = np.where(ncr[..., None] > 0, cr / ncr[..., None], 0.0)
    s = np.einsum("pgvk,pk->pgv", g, normals) * gamma
    return np.abs(s.sum(axis=2)) / (2 * np.pi)


def _deposit(u: np.ndarray, T: int):
    """Linear interpolation of positions u (in bins, bin centres at integers) -> (i0, w0, i1, w1)
    with indices clipped to [0, T); weights past T - 1 are dropped."""
    u = np.maximum(u, 0.0)
    i0 = np.floor(u).astype(np.int64)
    f = u - i0
    w0, w1 = 1 - f, f
    i1 = i0 + 1
    w0 = np.where(i0 < T, w0, 0.0)
    w1 = np.where(i1 < T, w1, 0.0)
    return np.minimum(i0, T - 1), w0, np.minimum(i1, T - 1), w1


# ------------------------------------------------------------------------------------------
# The room model
# ------------------------------------------------------------------------------------------


@dataclass
class Variant:
    """Materials of one run: alpha and s per face and band (6, 8), air m per band (8,)."""

    alpha: np.ndarray
    scattering: np.ndarray
    m_air: np.ndarray

    @property
    def spec(self) -> np.ndarray:  # (8, 6): (1-α)(1-s) per band and face
        return ((1 - self.alpha) * (1 - self.scattering)).T

    @property
    def diffuse(self) -> np.ndarray:  # (8, 6): s(1-α)
        return (self.scattering * (1 - self.alpha)).T


def variant(alpha, scattering, m_air) -> Variant:
    a = np.asarray(alpha, float).reshape(6, N_BANDS)
    s = np.asarray(scattering, float)
    s = np.repeat(s[:, None], N_BANDS, axis=1) if s.ndim == 1 else s.reshape(6, N_BANDS)
    return Variant(a, s, np.asarray(m_air, float).reshape(N_BANDS))


class RoomKernel:
    """Patch-to-patch transfer of Lambert-emitted energy, direct and over specular images, for
    several material variants at once: K[v, b] (N, N, T), K[k, l, τ] = fraction of the energy
    emitted diffusely by patch k that arrives on patch l after τ bins."""

    def __init__(self, dims, patch_size: float, t_end_s: float, variants: list[Variant], dt: float = DT,
                 q_dist: int = 2, near_factor: float = 3.0, log=None):
        self.dims = tuple(float(x) for x in dims)
        self.dt = dt
        self.T = int(np.ceil(t_end_s / dt))
        self.p = radiosity.box_patches(self.dims, patch_size)
        self.N = len(self.p.areas)
        self.variants = variants
        self.patch_size = patch_size
        N, T, V = self.N, self.T, len(variants)
        reach = C_SOUND * t_end_s
        self.reach = reach
        lat = lattice(self.dims, reach)
        p = self.p
        diag = np.linalg.norm(p.u + p.v, axis=1)
        spec = np.stack([specular_factor(lat.hits, v.spec) for v in variants])  # (V, 8, M)
        m_air = np.stack([v.m_air for v in variants])  # (V, 8)
        Kf = np.zeros((N * N * T, V * N_BANDS), dtype=np.float32)
        sub = _sub_points(p, q_dist)  # (N, m, 3)
        m = q_dist * q_dist
        x, w = np.polynomial.legendre.leggauss(2)
        x, w = 0.5 * (x + 1), 0.5 * w
        gu, gv = np.meshgrid(x, x, indexing="ij")
        gw = np.outer(w, w).ravel()
        gauss = p.corners[:, 0][:, None, :] + gu.ravel()[None, :, None] * p.u[:, None, :] + gv.ravel()[None, :, None] * p.v[:, None, :]
        kl_k, kl_l = np.meshgrid(np.arange(N), np.arange(N), indexing="ij")
        kl_k, kl_l = kl_k.ravel(), kl_l.ravel()
        for mi in range(len(lat.gap)):
            off, sg = lat.offset[mi], lat.sign[mi]
            ck = off + sg * p.centers  # image patch centres (N, 3)
            nk = sg * p.normals
            d = p.centers[kl_l] - ck[kl_k]  # (N², 3) from image k to l
            front_k = np.einsum("ij,ij->i", d, nk[kl_k]) > 1e-9
            front_l = -np.einsum("ij,ij->i", d, p.normals[kl_l]) > 1e-9
            dc = np.linalg.norm(d, axis=1)
            ok = front_k & front_l & (dc <= reach + diag[kl_k] + diag[kl_l])
            if not np.any(ok):
                continue
            kk, ll, dcc = kl_k[ok], kl_l[ok], dc[ok]
            # sample pairs: image-k samples i, l samples j
            sk = off + sg * sub[kk]  # (P, m, 3)
            sl = sub[ll]
            dv = sl[:, None, :, :] - sk[:, :, None, :]  # (P, m, m, 3)
            dist = np.linalg.norm(dv, axis=3)
            safe = np.maximum(dist, 1e-9)
            cos_k = np.clip(np.einsum("pijc,pc->pij", dv, nk[kk]) / safe, 0, None)
            cos_l = np.clip(-np.einsum("pijc,pc->pij", dv, p.normals[ll]) / safe, 0, None)
            ker = cos_k * cos_l / safe**2
            den = ker.sum(axis=(1, 2))
            good = den > 0
            F = p.areas[ll] / (m * m * np.pi) * den  # far-field form factor estimate
            near = dcc < near_factor * np.maximum(diag[kk], diag[ll])
            if np.any(near):
                idx = np.nonzero(near)[0]
                pts = off + sg * gauss[kk[idx]]  # (Pn, 4, 3)
                ff = _ff_points_to_polygons(pts, nk[kk[idx]], p.corners[ll[idx]])
                F[idx] = ff @ gw
            Wt = np.where(good[:, None, None], ker / np.where(good, den, 1)[:, None, None], 0.0)
            val = (F[:, None, None] * Wt).reshape(len(kk), -1)  # (P, m*m)
            u = (dist / (C_SOUND * dt)).reshape(len(kk), -1)
            i0, w0, i1, w1 = _deposit(u, T)
            # local aggregation to unique (pair, bin) keys (bincount on a compact index), then one
            # scatter per image
            imin = i0.min(axis=1)
            W = int((i1.max(axis=1) - imin).max()) + 1
            pid = np.arange(len(kk))[:, None] * W
            loc = np.concatenate([(pid + i0 - imin[:, None]).ravel(), (pid + i1 - imin[:, None]).ravel()])
            vals = np.concatenate([(val * w0).ravel(), (val * w1).ravel()])
            agg = np.bincount(loc, weights=vals, minlength=len(kk) * W)
            nz = np.nonzero(agg)[0]
            agg = agg[nz]
            pair = nz // W
            dly = imin[pair] + nz % W
            uk = (kk[pair] * N + ll[pair]) * T + dly
            air = np.exp(-m_air[:, :, None] * C_SOUND * dt * dly[None, None, :])  # (V, 8, U)
            fac = (spec[:, :, mi][:, :, None] * air).reshape(V * N_BANDS, -1).T  # (U, V*8)
            Kf[uk] += (agg[:, None] * fac).astype(np.float32)
            if log and mi % 50 == 0:
                log(f"kernel: image {mi}/{len(lat.gap)}")
        self.K = Kf  # (N*N*T, V*8)
        self.lattice_size = len(lat.gap)

    def kernel(self, v: int, b: int) -> np.ndarray:
        return self.K[:, v * N_BANDS + b].reshape(self.N, self.N, self.T)


def injection(rk: RoomKernel, src, q: int = 4) -> np.ndarray:
    """Energy incident on every patch from the source's specular paths (direct and images, each
    with its Π((1-α)(1-s))^n and air), per variant and band: (V, 8, N, T)."""
    p, N, T = rk.p, rk.N, rk.T
    lat = lattice(rk.dims, rk.reach)
    src = np.asarray(src, float)
    imgs = lat.map(src)  # (M, 3)
    V = len(rk.variants)
    out = np.zeros((V, N_BANDS, N * T))
    spec = np.stack([specular_factor(lat.hits, v.spec) for v in rk.variants])  # (V, 8, M)
    sub = _sub_points(p, q)  # (N, q², 3)
    for mi, I in enumerate(imgs):
        d = p.centers - I
        front = -np.einsum("ij,ij->i", d, p.normals) > 1e-9
        ok = front & (np.linalg.norm(d, axis=1) <= rk.reach + np.linalg.norm(p.u + p.v, axis=1))
        if not np.any(ok):
            continue
        ll = np.nonzero(ok)[0]
        omega = solid_angle_quad(np.broadcast_to(I, (len(ll), 3)), p.corners[ll])
        dv = sub[ll] - I  # (L, q², 3)
        dist = np.linalg.norm(dv, axis=2)
        cosl = np.clip(-np.einsum("ljc,lc->lj", dv, p.normals[ll]) / dist, 0, None)
        wj = cosl / dist**2
        wj = wj / np.maximum(wj.sum(axis=1, keepdims=True), 1e-300)
        _scatter_bins(out, ll, omega[:, None] * wj, dist, spec[:, :, mi], rk, absolute=True)
    return out.reshape(V, N_BANDS, N, T)


def gather_kernel(rk: RoomKernel, rcv, q: int = 4) -> np.ndarray:
    """Energy at the point listener per unit energy emitted diffusely by each patch, after τ
    bins, direct and over the patch's specular images (Eq. 4.29): (V, 8, N, T)."""
    p, N, T = rk.p, rk.N, rk.T
    lat = lattice(rk.dims, rk.reach)
    rcv = np.asarray(rcv, float)
    V = len(rk.variants)
    out = np.zeros((V, N_BANDS, N * T))
    spec = np.stack([specular_factor(lat.hits, v.spec) for v in rk.variants])
    sub = _sub_points(p, q)
    diag = np.linalg.norm(p.u + p.v, axis=1)
    for mi in range(len(lat.gap)):
        off, sg = lat.offset[mi], lat.sign[mi]
        ck = off + sg * p.centers
        nk = sg * p.normals
        d = rcv - ck
        front = np.einsum("ij,ij->i", d, nk) > 1e-9
        ok = front & (np.linalg.norm(d, axis=1) <= rk.reach + diag)
        if not np.any(ok):
            continue
        kk = np.nonzero(ok)[0]
        quads = off + sg * p.corners[kk]
        omega = solid_angle_quad(np.broadcast_to(rcv, (len(kk), 3)), quads)
        g = omega / (np.pi * p.areas[kk])
        dv = rcv - (off + sg * sub[kk])  # (K, q², 3)
        dist = np.linalg.norm(dv, axis=2)
        cosk = np.clip(np.einsum("kjc,kc->kj", dv, nk[kk]) / dist, 0, None)
        wj = cosk / dist**2
        wj = wj / np.maximum(wj.sum(axis=1, keepdims=True), 1e-300)
        _scatter_bins(out, kk, g[:, None] * wj, dist, spec[:, :, mi], rk, absolute=False)
    return out.reshape(V, N_BANDS, N, T)


def _scatter_bins(out, idx, weight, dist, spec_m, rk: RoomKernel, absolute: bool):
    """out[v, b, idx*T + bin] += weight * spec[v, b] * exp(-m R); ``absolute``: times from
    emission (bin centres at (n + 1/2)dt), else delays (shift by whole bins)."""
    T = rk.T
    u = dist / (C_SOUND * rk.dt) - (0.5 if absolute else 0.0)
    i0, w0, i1, w1 = _deposit(u, T)
    base = idx[:, None] * T
    for v, var in enumerate(rk.variants):
        air = np.exp(-var.m_air[:, None, None] * dist[None])  # (8, L, q²)
        for b in range(N_BANDS):
            x = weight * spec_m[v, b] * air[b]
            out[v, b] += np.bincount((base + i0).ravel(), weights=(x * w0).ravel(), minlength=out.shape[2])
            out[v, b] += np.bincount((base + i1).ravel(), weights=(x * w1).ravel(), minlength=out.shape[2])


def solve(rk: RoomKernel, inc: np.ndarray, gath: np.ndarray, tol: float = 1e-9, max_generations: int = 2000):
    """Diffuse energy at the listener per variant, band and bin: (V, 8, P, T) for P (source,
    listener) pairs; ``inc``/``gath``: (P, V, 8, N, T). Also returns the diffusely emitted
    energy per generation (convergence diagnostics)."""
    P, V, B, N, T = inc.shape
    L = 2 * T
    out = np.zeros((V, B, P, T))
    gens = np.zeros((V, B), dtype=np.int64)
    for v in range(V):
        D = np.stack([rk.variants[v].diffuse[b][rk.p.face] for b in range(B)])  # (8, N)
        for b in range(B):
            Kf = np.fft.rfft(rk.kernel(v, b), n=L, axis=2).astype(np.complex64)  # (N, N, F)
            Kf = np.ascontiguousarray(np.transpose(Kf, (2, 1, 0)))  # (F, l, k)
            phi = D[b][None, :, None] * inc[:, v, b]  # (P, N, T): generation 0
            total = phi.copy()
            e0 = phi.sum()
            g = 0
            while g < max_generations:
                g += 1
                Pf = np.fft.rfft(phi, n=L, axis=2)  # (P, N, F)
                Pf = np.transpose(Pf, (2, 1, 0))  # (F, N, P)
                Yf = np.matmul(Kf, Pf.astype(np.complex64))  # (F, N, P)
                y = np.fft.irfft(np.transpose(Yf, (2, 1, 0)), n=L, axis=2)[:, :, :T]
                phi = D[b][None, :, None] * np.maximum(y, 0.0)
                total += phi
                if phi.sum() <= tol * max(total.sum(), e0, 1e-300):
                    break
            gens[v, b] = g
            Gf = np.fft.rfft(gath[:, v, b], n=L, axis=2)
            Tf = np.fft.rfft(total, n=L, axis=2)
            out[v, b] = np.maximum(np.fft.irfft((Gf * Tf).sum(axis=1), n=L, axis=1)[:, :T], 0.0)
    return out, gens


# ------------------------------------------------------------------------------------------
# Phase 04 mixing time and AX16 matching level, re-implemented for the comparison
# ------------------------------------------------------------------------------------------


def expected_keff(start: float, end: float, volume: float) -> float:
    """src/sim/tail/MixingTime.cpp expectedKeff (Simpson, 4096 intervals)."""
    if not (end > start > 0 and volume > 0):
        return 0.0
    n = 4096
    t = start + (end - start) * np.arange(n + 1) / n
    w = np.sin(np.pi * np.arange(n + 1) / n) ** 2
    f = w * w / t**2
    wt = np.where(np.arange(n + 1) % 2 == 1, 4.0, 2.0)
    wt[0] = wt[-1] = 1.0
    den = (wt * f).sum() * (end - start) / n / 3
    iw = 0.5 * (end - start)
    return 4 * np.pi * C_SOUND**3 / volume * iw * iw / den


def mixing_time(t_dir: float, volume: float, floor_after_direct: float = 0.0) -> dict:
    """src/sim/tail/MixingTime.cpp mixingTime: the smallest t >= t_dir + max(20 ms, √V ms, floor)
    with expected k_eff >= 19 over the Hann window [t_dir + 2.5 ms, t]."""
    lower = t_dir + max(MIX_MIN_AFTER_DIRECT_S, np.sqrt(volume) * 1e-3, floor_after_direct)
    start = t_dir + WINDOW_START_AFTER_DIRECT_S
    if expected_keff(start, lower, volume) >= MIX_MIN_KEFF:
        mix = lower
    else:
        lo = lower
        hi = lo + max(lo - start, 1e-3)
        for _ in range(64):
            if expected_keff(start, hi, volume) >= MIX_MIN_KEFF:
                break
            hi = start + 2 * (hi - start)
        for _ in range(60):
            mid = 0.5 * (lo + hi)
            if expected_keff(start, mid, volume) >= MIX_MIN_KEFF:
                hi = mid
            else:
                lo = mid
        mix = hi
    return {"directS": t_dir, "lowerBoundS": lower, "windowStartS": start, "mixS": mix}


def eyring_t60(dims, var: Variant) -> np.ndarray:
    return np.array([radiosity.eyring_t60(dims, var.alpha[:, b], var.m_air[b]) for b in range(N_BANDS)])


def image_entries(dims, var: Variant, src, rcv, t_max: float) -> dict:
    """Specular and AX16 scattered energy entries (unit gain, omni) of every image arriving before
    t_max: times (M,), specular (8, M) and scattered (8, M) energies (amplitude² units, AX2/AQ3)."""
    lat = lattice(dims, C_SOUND * t_max + 1.0)
    imgs = lat.map(np.asarray(src, float))
    r = np.linalg.norm(imgs - np.asarray(rcv, float), axis=1)
    t = r / C_SOUND
    keep = t < t_max
    hits, r, t = lat.hits[keep], r[keep], t[keep]
    rho = (1 - var.alpha).T  # (8, 6)
    one_minus_s = (1 - var.scattering).T
    e_noscat = specular_factor(hits, rho) * np.exp(-var.m_air[:, None] * r[None]) / r[None] ** 2
    keep_s = specular_factor(hits, one_minus_s)  # Π(1-s)^hits
    spec = e_noscat * keep_s
    scat = e_noscat * (1 - keep_s)
    o = np.argsort(t, kind="stable")
    return {"t": t[o], "spec": spec[:, o], "scat": scat[:, o], "order": hits[o].sum(axis=1)}


def nth_reflection_time(dims, src, rcv, n: int = IMAGE_COUNT_CAP) -> float:
    """AX22: arrival time of the n-th reflection image (every lattice image counted, direct excluded)."""
    reach = 10.0
    while True:
        lat = lattice(dims, reach)
        r = np.linalg.norm(lat.map(np.asarray(src, float)) - np.asarray(rcv, float), axis=1)
        refl = np.sort(r[lat.hits.sum(axis=1) > 0])
        if len(refl) > n and refl[n - 1] < reach:
            return float(refl[n - 1] / C_SOUND)
        reach *= 1.5


def window_target(times, energies, mix: dict, t60: np.ndarray) -> np.ndarray:
    """E_target per band (src/sim/tail/NoiseTail.cpp matchTail): Σ w(t)·E·exp(-rate·(t_mix - t))
    over the Hann window, normalised to 10 ms. ``energies`` (8, M)."""
    a, b = mix["windowStartS"], mix["mixS"]
    t = np.asarray(times)
    w = np.where((t > a) & (t < b), np.sin(np.pi * (t - a) / (b - a)) ** 2, 0.0)
    rate = ENERGY_DECAY_PER_T60 / np.asarray(t60)
    x = w[None] * energies * np.exp(-rate[:, None] * (b - t[None]))
    return MATCH_NORMALISATION_S / (0.5 * (b - a)) * x.sum(axis=1)


def realised_keff(times, energies, mix, t60) -> np.ndarray:
    a, b = mix["windowStartS"], mix["mixS"]
    t = np.asarray(times)
    w = np.where((t > a) & (t < b), np.sin(np.pi * (t - a) / (b - a)) ** 2, 0.0)
    rate = ENERGY_DECAY_PER_T60 / np.asarray(t60)
    x = w[None] * energies * np.exp(-rate[:, None] * (b - t[None]))
    x = np.where(energies > 0, x, 0.0)
    s, s2 = x.sum(axis=1), (x**2).sum(axis=1)
    return np.where(s2 > 0, s * s / np.where(s2 > 0, s2, 1), 0.0)


def phase04_plan(dims, var: Variant, src, rcv, floor_after_direct: float = 0.0) -> dict:
    """t_mix,e with the AX22 fallback, the AX16 entries and E_target(AX16), as src/sim/Engine.cpp
    planEmitter (Python re-implementation; the tests compare it with render_cli --diagnostics)."""
    V = float(np.prod(dims))
    t_dir = float(np.linalg.norm(np.asarray(src, float) - np.asarray(rcv, float)) / C_SOUND)
    mix = mixing_time(t_dir, V, floor_after_direct)
    t60 = eyring_t60(dims, var)
    ent = image_entries(dims, var, src, rcv, mix["mixS"] + CROSSFADE_HALF_S)
    both = np.concatenate([ent["spec"], ent["scat"]], axis=1)
    tt = np.concatenate([ent["t"], ent["t"]])
    k_real = realised_keff(tt, both, mix, t60)
    fallback = bool(np.any(k_real[list(REALISED_K_BANDS)] < MIX_MIN_KEFF))
    expected_mix = mix["mixS"]
    if fallback:
        t_cap = nth_reflection_time(dims, src, rcv)
        if t_cap > mix["mixS"]:
            mix = dict(mix, mixS=t_cap)
            ent = image_entries(dims, var, src, rcv, mix["mixS"] + CROSSFADE_HALF_S)
            both = np.concatenate([ent["spec"], ent["scat"]], axis=1)
            tt = np.concatenate([ent["t"], ent["t"]])
    target = window_target(tt, both, mix, t60)
    target_spec = window_target(ent["t"], ent["spec"], mix, t60)
    return {"mix": mix, "expectedMixS": expected_mix, "fallback": fallback, "t60": t60, "entries": ent,
            "target_ax16": target, "target_specular": target_spec, "k_real": k_real}


def target_hybrid(plan: dict, diffuse_bins: np.ndarray, dt: float = DT) -> np.ndarray:
    """E_target with the hybrid's propagated diffuse energy instead of the AX16 scattered entries:
    specular entries + diffuse bins (8, T) at bin centres, same window and referral."""
    T = diffuse_bins.shape[1]
    tb = (np.arange(T) + 0.5) * dt
    return plan["target_specular"] + window_target(tb, diffuse_bins, plan["mix"], plan["t60"])


def delta_lb(plan: dict, diffuse_bins: np.ndarray) -> np.ndarray:
    """X-b bound ΔL_b = 10·log10(E_target(AX16) / E_target(hybrid)) per band (dB)."""
    th = target_hybrid(plan, diffuse_bins)
    with np.errstate(divide="ignore", invalid="ignore"):
        return 10 * np.log10(plan["target_ax16"] / th)


def run_pairs(dims, variants: list[Variant], pairs, t_end_s: float, patch_size: float, log=None):
    """Diffuse envelopes (V, 8, P, T) for (source, listener) pairs in one room, plus the kernel."""
    rk = RoomKernel(dims, patch_size, t_end_s, variants, log=log)
    inc = np.stack([injection(rk, s) for s, _ in pairs])
    gat = np.stack([gather_kernel(rk, r) for _, r in pairs])
    env, gens = solve(rk, inc, gat)
    return env, {"patches": rk.N, "patch_size_m": patch_size, "bins": rk.T, "dt_s": rk.dt,
                 "lattice_images": rk.lattice_size, "generations": gens.tolist()}
