"""Decay predictors for shoebox rooms beside Eyring (phase-05 scope 6, decay predictors; B12).

Reference tools only: they do not change the simulator (`src/sim`), and nothing here is used to
render audio.

- `a_star`: the radiosity effective absorption exponent a* for Lambert walls, Kuttruff §5.7,
  Eqs. 5.49-5.56. The boundary is split into rectangular patches; the integral equation
  (Eq. 5.55) beta = ∬ kappa beta exp(a* R / l) dS' is discretised as an eigenproblem
  M(a) b = b with M_kl(a) = F_k->l · rho_l · <exp(a · R / l)>_kl, l = 4V/S (Eq. 5.12), F_k->l the
  patch-to-patch form factor (Eq. 5.52 with the Lambert kernel of Eq. 5.50) and <.>_kl the
  kernel-weighted average over the path lengths R between the two patches. a* is the root of lambda_max(M(a)) = 1
  (lambda_max increases with a; for uniform rho and constant R it gives Eyring, -ln rho). This
  solves Eq. 5.55's eigencondition directly instead of Kuttruff's fixed-point iteration (Eq. 5.56),
  which converges to the same root. T = 0.161 V / (S a*) (Eq. 5.53); air absorption enters as
  a* + 4mV/S (Kuttruff §4.5 with Eq. 5.55).
- `gamma2_eyring`: Kuttruff Eqs. 5.33-5.34 with gamma^2 from Table 5.1.
- `eyring_t60`: Eyring with 4mV (Kuttruff Eq. 5.24 / Vorländer Eq. 4.32), the simulator's predictor.

Form factors: point-to-polygon by the contour integral (exact for a planar polygon fully in view,
which holds for any two faces of a convex box), integrated over the emitting patch with
Gauss-Legendre points. Patches on the same face see each other with F = 0.
"""

from __future__ import annotations

from dataclasses import dataclass

import numpy as np
from scipy.optimize import brentq

C_SOUND = 343.0
K_SABINE = 0.161  # Kuttruff Eq. 4.12 / Eq. 5.53 constant (s/m)

# Face order: x-, x+, y-, y+, z- (floor), z+ (ceiling); AQ1 axes (x right, y forward, z up).
FACE_NAMES = ("x-", "x+", "y-", "y+", "floor", "ceiling")


@dataclass
class Patches:
    centers: np.ndarray  # (N, 3)
    corners: np.ndarray  # (N, 4, 3), counter-clockwise seen from inside the room
    normals: np.ndarray  # (N, 3), inward unit normals
    areas: np.ndarray  # (N,)
    face: np.ndarray  # (N,) face index into FACE_NAMES
    u: np.ndarray  # (N, 3) edge vector 1 (full length)
    v: np.ndarray  # (N, 3) edge vector 2 (full length)


def _face_frames(dims):
    """(origin, u, v, inward normal) for the 6 faces of the box [0,W]x[0,D]x[0,H]."""
    W, D, H = dims
    ex, ey, ez = np.eye(3)
    return [
        (np.zeros(3), ey * D, ez * H, ex),  # x-
        (np.array([W, 0, 0.0]), ez * H, ey * D, -ex),  # x+
        (np.zeros(3), ez * H, ex * W, ey),  # y-
        (np.array([0, D, 0.0]), ex * W, ez * H, -ey),  # y+
        (np.zeros(3), ex * W, ey * D, ez),  # floor
        (np.array([0, 0, H]), ey * D, ex * W, -ez),  # ceiling
    ]


def box_patches(dims, n_per_face) -> Patches:
    """Split each face into n_u x n_v equal rectangles. ``n_per_face``: 6 (n_u, n_v) pairs, or a
    patch edge length in metres (each face side divided into ceil(side/size) equal parts)."""
    frames = _face_frames(dims)
    if np.isscalar(n_per_face):
        size = float(n_per_face)
        n_per_face = [
            (max(1, int(np.ceil(np.linalg.norm(u) / size - 1e-9))), max(1, int(np.ceil(np.linalg.norm(v) / size - 1e-9))))
            for _, u, v, _ in frames
        ]
    cen, cor, nor, ar, fc, us, vs = [], [], [], [], [], [], []
    for f, ((o, u, v, n), (nu, nv)) in enumerate(zip(frames, n_per_face)):
        du, dv = u / nu, v / nv
        for i in range(nu):
            for j in range(nv):
                p0 = o + i * du + j * dv
                quad = np.array([p0, p0 + du, p0 + du + dv, p0 + dv])
                cen.append(p0 + 0.5 * (du + dv))
                cor.append(quad)
                nor.append(n)
                ar.append(np.linalg.norm(np.cross(du, dv)))
                fc.append(f)
                us.append(du)
                vs.append(dv)
    return Patches(np.array(cen), np.array(cor), np.array(nor), np.array(ar), np.array(fc), np.array(us), np.array(vs))


def patches_for_counts(dims, size: float) -> Patches:
    return box_patches(dims, size)


def _point_to_polygon_ff(points, normals, poly):
    """Form factor from differential areas (points (P,3), unit normals (P,3)) to a planar polygon
    (V,3) in full view: F = (1/2π) |Σ_i γ_i n·g_i|, g_i the unit normal of the plane through the
    point and edge i, γ_i the angle the edge subtends (contour-integral form)."""
    r = poly[None, :, :] - points[:, None, :]  # (P, V, 3)
    r1 = np.roll(r, -1, axis=1)
    cr = np.cross(r, r1)
    ncr = np.linalg.norm(cr, axis=2)
    dots = np.einsum("pvk,pvk->pv", r, r1)
    gamma = np.arctan2(ncr, dots)
    with np.errstate(invalid="ignore", divide="ignore"):
        g = np.where(ncr[..., None] > 0, cr / ncr[..., None], 0.0)
    s = np.einsum("pvk,pk->pv", g, normals) * gamma
    return np.abs(s.sum(axis=1)) / (2 * np.pi)


def form_factors(p: Patches, q: int = 4, q_dist: int = 2):
    """F[k, l] = F_k->l (fraction of energy leaving patch k diffusely that arrives at l), exact to
    quadrature (rows sum to 1 in a closed box), and the distribution of path lengths between the
    two patches: R[k, l, s] with weights Wt[k, l, s] (sum 1 over s), from q_dist x q_dist midpoint
    samples on both patches weighted by the Lambert kernel (Eq. 5.50). Keeping the distribution,
    not just its mean, matters: exp(a R / l) is convex, and the within-pair variance of R is part of
    the path-length variance that makes T exceed Eyring (Kuttruff §5.5)."""
    N = len(p.areas)
    x, w = np.polynomial.legendre.leggauss(q)
    x = 0.5 * (x + 1)
    w = 0.5 * w
    uu, vv = np.meshgrid(x, x, indexing="ij")
    ww = np.outer(w, w).ravel()
    F = np.zeros((N, N))
    for k in range(N):
        pts = p.corners[k, 0] + uu.ravel()[:, None] * p.u[k] + vv.ravel()[:, None] * p.v[k]  # (P, 3)
        # all target patches at once: r[l, P, V, 3]
        r = p.corners[:, None, :, :] - pts[None, :, None, :]
        r1 = np.roll(r, -1, axis=2)
        cr = np.cross(r, r1)
        ncr = np.linalg.norm(cr, axis=3)
        gamma = np.arctan2(ncr, np.einsum("lpvc,lpvc->lpv", r, r1))
        with np.errstate(invalid="ignore", divide="ignore"):
            g = np.where(ncr[..., None] > 0, cr / ncr[..., None], 0.0)
        ff = np.abs((np.einsum("lpvc,c->lpv", g, p.normals[k]) * gamma).sum(axis=2)) / (2 * np.pi)  # (l, P)
        F[k] = ff @ ww
        F[k, p.face == p.face[k]] = 0.0
    s = (np.arange(q_dist) + 0.5) / q_dist
    su, sv = np.meshgrid(s, s, indexing="ij")
    sub = p.corners[:, 0][:, None, :] + su.ravel()[None, :, None] * p.u[:, None, :] + sv.ravel()[None, :, None] * p.v[:, None, :]
    m = q_dist * q_dist
    R = np.zeros((N, N, m * m))
    Wt = np.zeros((N, N, m * m))
    for k in range(N):
        d = sub[:, :, None, :] - sub[k][None, None, :, :]  # (N, m, m, 3): l-sample i minus k-sample j
        dist = np.linalg.norm(d, axis=3)
        safe = np.maximum(dist, 1e-12)
        cos_k = np.einsum("lijc,c->lij", d, p.normals[k]) / safe
        cos_l = -np.einsum("lijc,lc->lij", d, p.normals) / safe
        ker = np.clip(cos_k, 0, None) * np.clip(cos_l, 0, None) / safe**2
        ker[p.face == p.face[k]] = 0.0
        den = ker.sum(axis=(1, 2))
        R[k] = dist.reshape(N, -1)
        Wt[k] = (ker / np.where(den > 0, den, 1)[:, None, None]).reshape(N, -1)
    return F, (R, Wt)


def _lambda_max(M, v0=None, iters=2000, tol=1e-13):
    """Perron eigenvalue of a non-negative matrix by power iteration."""
    v = np.ones(M.shape[0]) if v0 is None else v0.copy()
    v /= np.linalg.norm(v)
    lam = 0.0
    for _ in range(iters):
        w = M @ v
        lam_new = np.linalg.norm(w)
        if lam_new == 0:
            return 0.0, v
        w /= lam_new
        if abs(lam_new - lam) < tol * lam_new and np.linalg.norm(w - v) < 1e-10:
            return lam_new, w
        v, lam = w, lam_new
    return lam, v


def a_star(dims, rho_patch, patches: Patches, F=None, R=None) -> float:
    """Effective absorption exponent a* (Kuttruff Eq. 5.53-5.56) without air absorption.
    ``rho_patch``: reflection coefficient 1 - alpha per patch. ``F``, ``R``: from form_factors
    (computed when omitted)."""
    if F is None or R is None:
        F, R = form_factors(patches)
    W, D, H = dims
    V = W * D * H
    S = 2 * (W * D + W * H + D * H)
    lbar = 4 * V / S
    rho = np.asarray(rho_patch, float)
    base = F * rho[None, :]
    Rs, Wt = R

    def f(a):
        delay = np.einsum("kls,kls->kl", Wt, np.exp(a * Rs / lbar))
        return _lambda_max(base * delay)[0] - 1.0

    lo, hi = 0.0, 1.0
    if f(lo) >= 0:  # no absorption at all: a* = 0
        return 0.0
    while f(hi) < 0:
        hi *= 2
        if hi > 1e3:
            raise ValueError("a* diverges (fully absorbing room?)")
    return brentq(f, lo, hi, xtol=1e-12, rtol=1e-12)


def t60_from_a(dims, a, m_air=0.0):
    """T = 0.161 V / (S a + 4 m V) (Kuttruff Eq. 5.53, air as in Eq. 5.24)."""
    W, D, H = dims
    V = W * D * H
    S = 2 * (W * D + W * H + D * H)
    return K_SABINE * V / (S * a + 4 * m_air * V)


def face_areas(dims):
    W, D, H = dims
    return np.array([D * H, D * H, W * H, W * H, W * D, W * D])


def mean_alpha(dims, alpha_faces):
    A = face_areas(dims)
    return float(np.dot(A, alpha_faces) / A.sum())


def eyring_t60(dims, alpha_faces, m_air=0.0):
    return t60_from_a(dims, -np.log(1 - mean_alpha(dims, alpha_faces)), m_air)


def sabine_t60(dims, alpha_faces, m_air=0.0):
    return t60_from_a(dims, mean_alpha(dims, alpha_faces), m_air)


# Kuttruff Table 5.1: relative dimensions (sorted ascending) -> gamma^2.
TABLE_5_1 = {
    (1, 1, 1): 0.342, (1, 1, 2): 0.356, (1, 1, 5): 0.412, (1, 1, 10): 0.415, (1, 2, 2): 0.363,
    (1, 2, 5): 0.403, (1, 2, 10): 0.465, (1, 5, 5): 0.464, (1, 5, 10): 0.510, (1, 10, 10): 0.613,
}
GAMMA2_DEFAULT = 0.4  # Kuttruff §5.5: "for most shapes gamma^2 ≈ 0.4"


def gamma2_table(dims, rel_tol=0.01):
    """gamma^2 from Kuttruff Table 5.1 for the room's shape: the row itself when the ratios match
    (within rel_tol), else linear interpolation in the largest ratio between two rows that share
    the other two ratios and bracket it (the phase-05 example: 1:2:3 between 1:2:2 and 1:2:5 gives
    0.376). None when the shape is outside the table (then only GAMMA2_DEFAULT applies)."""
    d = np.sort(np.asarray(dims, float))
    r = d / d[0]
    for key, g in TABLE_5_1.items():
        if np.allclose(r, key, rtol=rel_tol):
            return g, "row " + ":".join(map(str, key))
    rows = [(k, g) for k, g in TABLE_5_1.items() if abs(k[1] - r[1]) <= rel_tol * r[1]]
    below = [(k, g) for k, g in rows if k[2] <= r[2]]
    above = [(k, g) for k, g in rows if k[2] >= r[2]]
    if below and above:
        (k0, g0) = max(below, key=lambda t: t[0][2])
        (k1, g1) = min(above, key=lambda t: t[0][2])
        if k1[2] == k0[2]:
            return g0, "row " + ":".join(map(str, k0))
        g = g0 + (g1 - g0) * (r[2] - k0[2]) / (k1[2] - k0[2])
        return g, f"interpolated {':'.join(map(str, k0))}-{':'.join(map(str, k1))}"
    return None, "not tabulated"


def gamma2_eyring_t60(dims, alpha_faces, gamma2, m_air=0.0):
    """Kuttruff Eqs. 5.33-5.34: a'' = -ln(1-α)·[1 + (γ²/2)·ln(1-α)]."""
    L = np.log(1 - mean_alpha(dims, alpha_faces))
    a2 = -L * (1 + 0.5 * gamma2 * L)
    return t60_from_a(dims, a2, m_air)


def a_star_converged(dims, alpha_faces, start_size=None, tol=0.004, max_patches=1600, log=None):
    """a* with patch halving until a* changes by < tol (relative) per halving (phase-05: < 1 %,
    and < 0.4 % for B12 condition (i)). ``alpha_faces``: 6 values in FACE_NAMES order. Returns
    (a*, history [(n_patches, a*)], converged flag)."""
    size = start_size if start_size is not None else min(dims) / 2
    hist = []
    prev = None
    while True:
        p = box_patches(dims, size)
        if len(p.areas) > max_patches:
            return prev, hist, False
        rho = 1 - np.asarray(alpha_faces, float)[p.face]
        a = a_star(dims, rho, p)
        hist.append((len(p.areas), a))
        if log:
            log(f"a*: {len(p.areas)} patches -> {a:.6f}")
        if prev is not None and abs(a - prev) / a < tol:
            return a, hist, True
        prev = a
        size /= 2


def diffuse_mc_t60(dims, absorbing_faces, n=200_000, seed=1, max_bounces=400):
    """Independent reference for fully absorbing faces (alpha = 1) and rigid Lambert walls
    elsewhere (Kuttruff Table 5.2's arrangements): particles start in a uniform diffuse field,
    reflect per Lambert's law (Kuttruff Eq. 4.21) and die on an absorbing face; the late slope of
    ln(survival) per mean free path is a*. Not used by a_star; it checks it."""
    rng = np.random.default_rng(seed)
    d = np.asarray(dims, float)
    V = d.prod()
    S = 2 * (d[0] * d[1] + d[0] * d[2] + d[1] * d[2])
    lbar = 4 * V / S
    p = rng.random((n, 3)) * d
    u = rng.normal(size=(n, 3))
    u /= np.linalg.norm(u, axis=1)[:, None]
    dist = np.zeros(n)
    alive = np.ones(n, bool)
    death = np.full(n, np.inf)
    for _ in range(max_bounces):
        idx = np.nonzero(alive)[0]
        if len(idx) == 0:
            break
        P, U = p[idx], u[idx]
        with np.errstate(divide="ignore", invalid="ignore"):
            t = np.where(U > 0, (d - P) / U, np.where(U < 0, -P / U, np.inf))
        ax = np.argmin(t, 1)
        tt = t[np.arange(len(idx)), ax]
        P = P + U * tt[:, None]
        dist[idx] += tt
        side = (U[np.arange(len(idx)), ax] > 0).astype(int)
        face = ax * 2 + side  # FACE_NAMES order
        dead = np.isin(face, absorbing_faces)
        death[idx[dead]] = dist[idx[dead]]
        alive[idx[dead]] = False
        k = ~dead
        m = int(k.sum())
        r1, r2 = rng.random(m), rng.random(m)
        ct, st, ph = np.sqrt(r1), np.sqrt(1 - r1), 2 * np.pi * r2
        a, sd = ax[k], side[k]
        nv = np.zeros((m, 3))
        nv[np.arange(m), a] = np.where(sd == 1, -1.0, 1.0)
        e1 = np.zeros((m, 3))
        e1[np.arange(m), (a + 1) % 3] = 1
        e2 = np.cross(nv, e1)
        p[idx[k]] = P[k]
        u[idx[k]] = (st * np.cos(ph))[:, None] * e1 + (st * np.sin(ph))[:, None] * e2 + ct[:, None] * nv
    x = np.sort(death[np.isfinite(death)])
    surv = 1 - np.arange(1, len(x) + 1) / n
    sel = (surv < 0.1) & (surv > 2e-3)
    a_star_mc = -np.polyfit(x[sel] / lbar, np.log(surv[sel]), 1)[0]
    return t60_from_a(dims, a_star_mc), a_star_mc
