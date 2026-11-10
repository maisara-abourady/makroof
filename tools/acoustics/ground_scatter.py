"""Lambert ground scattering in `open_field` (phase-05b scope 7; ledger OF).

The Phase 04 check "nothing later than 50 ms after the direct sound (< −60 dB)" holds in the shipped IR
because AX16 puts no scattered energy into the early part (AX21) and E_b = 0 in a room whose other
faces absorb everything. Physically, a Lambert-scattering floor returns energy later than that. This
module integrates it exactly over the floor, to re-derive the check (ledger OF; phase-04 consult
report 4, Q5: −23 to −43 dB per band without heights and air).

Single scattering from the floor plane z = 0 (Kuttruff Eqs. 4.24, 4.27, 4.29): an element dS at
distances r₁ (source) and r₂ (listener) receives the irradiance cos θ₁/r₁² (unit intensity per
steradian, AX2), re-radiates the fraction ρ_s = s(1 − α_b) per Lambert, and the listener receives
dE = ρ_s · cos θ₁ cos θ₂ /(π r₁² r₂²) · exp(−m (r₁ + r₂)) dS, at the delay (r₁ + r₂)/c. The direct
sound gives exp(−m r_d)/r_d². The result is the energy arriving later than t_dir + 50 ms relative
to the direct sound, per band. The floor is taken as the infinite plane (open_field's floor is
100 × 100 m; the part beyond it adds < 0.01 dB here, checked by the test with a finite floor).
"""

from __future__ import annotations

import numpy as np

C_SOUND = 343.0


def late_ratio_db(src, rcv, rho_s, m_air, after_s: float = 0.050, half_width: float | None = None,
                  n_r: int = 4000, n_phi: int = 720) -> np.ndarray:
    """10·log10(E(t > t_dir + after_s) / E_direct) per band. Integration in polar coordinates around
    the source's foot point (r log-spaced to 10 km, or to the floor's edge when ``half_width`` is
    given as the floor's extent (x0, x1, y0, y1)); rho_s, m_air: (8,)."""
    src, rcv = np.asarray(src, float), np.asarray(rcv, float)
    rho_s, m = np.asarray(rho_s, float), np.asarray(m_air, float)
    rd = np.linalg.norm(src - rcv)
    lmin = rd + C_SOUND * after_s
    # polar grid around the source foot point: area element r dr dφ (midpoint rule)
    edges = np.concatenate([[0.0], np.geomspace(1e-3, 1e4, n_r)])
    r = 0.5 * (edges[1:] + edges[:-1])
    dr = np.diff(edges)
    phi = (np.arange(n_phi) + 0.5) * 2 * np.pi / n_phi
    dphi = 2 * np.pi / n_phi
    R, P = np.meshgrid(r, phi, indexing="ij")
    x = src[0] + R * np.cos(P)
    y = src[1] + R * np.sin(P)
    r1 = np.sqrt(R**2 + src[2] ** 2)
    r2 = np.sqrt((x - rcv[0]) ** 2 + (y - rcv[1]) ** 2 + rcv[2] ** 2)
    cos1, cos2 = src[2] / r1, rcv[2] / r2
    w = (R * dr[:, None] * dphi) * cos1 * cos2 / (np.pi * r1**2 * r2**2)
    late = (r1 + r2) >= lmin
    if half_width is not None:
        x0, x1, y0, y1 = half_width
        late &= (x >= x0) & (x <= x1) & (y >= y0) & (y <= y1)
    path = (r1 + r2)[late]
    ww = w[late]
    e = np.array([rho_s[b] * np.sum(ww * np.exp(-m[b] * path)) for b in range(len(rho_s))])
    direct = np.exp(-m * rd) / rd**2
    return 10 * np.log10(e / direct)


def window_target(src, rcv, rho_s, m_air, window_start_s: float, mix_s: float, t60_s, half_width=None,
                  n_r: int = 4000, n_phi: int = 720) -> np.ndarray:
    """Phase 05h, AX37 (5.4): the single-scatter diffuse energy of the floor inside the Phase 04 matching
    window, as E_target's diffuse part (reference units, squared pressure re 1 m per 10 ms): each floor
    element's contribution dE at its arrival time t = (r1 + r2) / c, weighted by the Hann window
    sin²(π (t − a) / (b − a)) over [a, b] = [window_start_s, mix_s], referred to t_mix along the Eyring
    decay exp(13.82 (t − b) / T60_b) and normalised to 10 ms (10 ms / ((b − a) / 2), as
    src/sim/tail/NoiseTail.cpp matchTail and ref_hybrid.window_target). Independent of ref_hybrid and
    of the simulator: it is the finite-floor check of the open-field diffuse E_target. The floor is the
    finite rectangle ``half_width`` = (x0, x1, y0, y1) when given, else the infinite plane. rho_s = s (1 − α_b),
    m_air, t60_s: (8,)."""
    src, rcv = np.asarray(src, float), np.asarray(rcv, float)
    rho_s, m, t60 = np.asarray(rho_s, float), np.asarray(m_air, float), np.asarray(t60_s, float)
    a, b = float(window_start_s), float(mix_s)
    if not b > a:
        return np.zeros(len(rho_s))
    edges = np.concatenate([[0.0], np.geomspace(1e-3, 1e4, n_r)])
    r = 0.5 * (edges[1:] + edges[:-1])
    dr = np.diff(edges)
    phi = (np.arange(n_phi) + 0.5) * 2 * np.pi / n_phi
    dphi = 2 * np.pi / n_phi
    R, P = np.meshgrid(r, phi, indexing="ij")
    x = src[0] + R * np.cos(P)
    y = src[1] + R * np.sin(P)
    r1 = np.sqrt(R**2 + src[2] ** 2)
    r2 = np.sqrt((x - rcv[0]) ** 2 + (y - rcv[1]) ** 2 + rcv[2] ** 2)
    cos1, cos2 = src[2] / r1, rcv[2] / r2
    w = (R * dr[:, None] * dphi) * cos1 * cos2 / (np.pi * r1**2 * r2**2)
    t = (r1 + r2) / C_SOUND
    inside = (t > a) & (t < b)
    if half_width is not None:
        x0, x1, y0, y1 = half_width
        inside &= (x >= x0) & (x <= x1) & (y >= y0) & (y <= y1)
    path = (r1 + r2)[inside]
    tt = t[inside]
    hann = np.sin(np.pi * (tt - a) / (b - a)) ** 2
    ww = w[inside] * hann
    norm = 0.010 / (0.5 * (b - a))
    rate = np.log(1e6) / t60
    return np.array([norm * rho_s[k] * np.sum(ww * np.exp(-m[k] * path) * np.exp(rate[k] * (tt - b))) for k in range(len(rho_s))])
