"""Seeded partially diffuse ray tracer: the independent reference of phase-05b gate (A) (BUILD_PLAN §5 B11).

Reference tool only. It shares no code and no random stream with `src/sim` or with
`tools/acoustics/ref_hybrid.py` (no lattice, no patches, no form factors): particles are traced
through the shoebox one wall hit at a time.

Model (Kuttruff §9.8; Vorländer Ch. 11):

- N particles leave the point source in uniformly distributed directions, each carrying the energy
  4π/N, so that the energy a point receiver collects from the direct sound at distance r is 1/r²
  (unit intensity per steradian, AX2), the same units as the image-source energies.
- **Energy multiplication** (Kuttruff §9.8 step 3a; Vorländer Eqs. 11.14–11.18): at every wall hit
  the particle's energy is multiplied by (1 − α) per band; it is never killed by absorption. It is
  followed until its path length reaches c·t_end (or its energy is zero in every band, e.g. after a
  hit on an α = 1 face).
- **Scattering**: at every hit the particle is re-emitted per Lambert's law (cosine-weighted around
  the inward normal, Kuttruff Eq. 4.21) with probability s of the face hit, and reflected
  specularly otherwise. The scattering coefficient is broadband (the contract's single s per face,
  AX17), so one path serves all 8 bands.
- **Air absorption** (AX4): energy factor exp(−m·R) at the detection, R the path length.
- **Receiver**: a counting sphere of radius r_d (default 0.5 m, B11). A segment that crosses it
  contributes w·ℓ/V_sphere (ℓ: chord length inside the sphere; Vorländer §11.x energy-density
  estimate), which averages the point receiver's energy over the sphere. Engineering note, not
  from the corpus (B11): each detection is time-stamped at the ray's closest approach to the
  receiver point, not at sphere entry.

Statistics (AX11 convention, B11): per bin, k = (ΣE)²/ΣE² over the detections (the equivalent
number of equal contributions); a bin is gated when k ≥ 684 (3σ ≈ 0.5 dB with σ = 4.34/√k dB).

Determinism (AX5): particles are traced in chunks of ``CHUNK`` with the random stream of chunk j
seeded by ``SeedSequence([seed, j])``, so the result depends only on (seed, N) and a doubled run
contains the original particles (the doubling rule of B11 adds particles, it does not redraw them).
"""

from __future__ import annotations

from dataclasses import dataclass, field

import numpy as np

C_SOUND = 343.0  # m/s (AX4 atmosphere; the same constant as the simulator, a physical input)
R_D = 0.5  # receiver radius (B11)
K_GATE = 684.0  # B11: bins with k >= 684 are gated
PARTICLES_PER_M3 = 254.0  # B11: N0 = ceil(254 V) (Vorländer Eq. 11.12 with k = 684, Δt = 10 ms)
MAX_DOUBLINGS = 4  # up to 16 N0
CHUNK = 200_000
N_BANDS = 8
TRACER_SEED = 0x05B7  # fixed before any result (B11: the seed is never changed to pass)


def n0(volume: float) -> int:
    return int(np.ceil(PARTICLES_PER_M3 * volume))


@dataclass
class Window:
    """Hann window of the AX16 matching level (src/sim NoiseTail matchTail, ref_hybrid.window_target):
    E_target = norm · Σ w(t)·E·exp(−rate·(end − t)), w = sin²(π(t − start)/(end − start)) on (start, end)."""

    start: float
    end: float
    rate: np.ndarray  # (8,) energy decay rate 1/s
    norm: float


@dataclass
class TraceResult:
    n: int
    seed: int
    bin_s: float
    e: np.ndarray  # (8, nb) ΣE per bin
    e2: np.ndarray  # (8, nb) ΣE² per bin
    detections: int
    window_s1: np.ndarray | None = None  # (8,)
    window_s2: np.ndarray | None = None
    room_energy: np.ndarray | None = None  # (8, n_room) energy in the room per room_dt (no air)
    room_dt: float | None = None
    extra: dict = field(default_factory=dict)

    @property
    def k(self) -> np.ndarray:
        with np.errstate(divide="ignore", invalid="ignore"):
            return np.where(self.e2 > 0, self.e**2 / np.where(self.e2 > 0, self.e2, 1.0), 0.0)

    def window_target(self, win: Window) -> np.ndarray:
        return win.norm * self.window_s1

    @property
    def window_k(self) -> np.ndarray:
        return np.where(self.window_s2 > 0, self.window_s1**2 / np.where(self.window_s2 > 0, self.window_s2, 1.0), 0.0)

    def merged(self, other: "TraceResult") -> "TraceResult":
        """Sum of two disjoint particle sets with the same seed (chunks continue the numbering)."""
        r = TraceResult(self.n + other.n, self.seed, self.bin_s, self.e + other.e, self.e2 + other.e2,
                        self.detections + other.detections)
        if self.window_s1 is not None:
            r.window_s1 = self.window_s1 + other.window_s1
            r.window_s2 = self.window_s2 + other.window_s2
        if self.room_energy is not None:
            r.room_energy = self.room_energy + other.room_energy
            r.room_dt = self.room_dt
        return r


def _lambert(rng, normal_axis: np.ndarray, inward_sign: np.ndarray) -> np.ndarray:
    """Cosine-weighted directions around the inward normals (axis-aligned faces)."""
    m = len(normal_axis)
    r1, r2 = rng.random(m), rng.random(m)
    ct, st, ph = np.sqrt(r1), np.sqrt(1.0 - r1), 2.0 * np.pi * r2
    out = np.empty((m, 3))
    a1 = (normal_axis + 1) % 3
    a2 = (normal_axis + 2) % 3
    rows = np.arange(m)
    out[rows, normal_axis] = inward_sign * ct
    out[rows, a1] = st * np.cos(ph)
    out[rows, a2] = st * np.sin(ph)
    return out


def _trace_chunk(rng, count, scale, dims, rho, s_face, m_air, src, rcv, t_end, bin_s, nb, r_d, win, room_dt, n_room):
    d = np.asarray(dims, float)
    p = np.broadcast_to(np.asarray(src, float), (count, 3)).copy()
    u = rng.normal(size=(count, 3))
    u /= np.linalg.norm(u, axis=1)[:, None]
    w = np.full((count, N_BANDS), scale)
    L = np.zeros(count)
    alive = np.ones(count, bool)
    l_end = C_SOUND * t_end
    v_sph = 4.0 / 3.0 * np.pi * r_d**3
    rcv = np.asarray(rcv, float)
    e = np.zeros((N_BANDS, nb))
    e2 = np.zeros((N_BANDS, nb))
    s1 = np.zeros(N_BANDS) if win is not None else None
    s2 = np.zeros(N_BANDS) if win is not None else None
    room = np.zeros((N_BANDS, n_room + 1)) if room_dt else None
    det = 0
    while True:
        idx = np.nonzero(alive)[0]
        if len(idx) == 0:
            break
        P, U, Li, W = p[idx], u[idx], L[idx], w[idx]
        with np.errstate(divide="ignore", invalid="ignore"):
            tw = np.where(U > 0, (d - P) / U, np.where(U < 0, -P / U, np.inf))
        ax = np.argmin(tw, axis=1)
        tt = np.maximum(tw[np.arange(len(idx)), ax], 0.0)
        # receiver: chord of the segment [0, tt] inside the sphere, stamped at the closest approach
        rel = rcv - P
        tau0 = np.einsum("ij,ij->i", rel, U)
        d2 = np.einsum("ij,ij->i", rel, rel) - tau0 * tau0
        cand = d2 < r_d * r_d
        if np.any(cand):
            ci = np.nonzero(cand)[0]
            half = np.sqrt(r_d * r_d - d2[ci])
            lo = np.clip(tau0[ci] - half, 0.0, tt[ci])
            hi = np.clip(tau0[ci] + half, 0.0, tt[ci])
            chord = hi - lo
            path = Li[ci] + np.clip(tau0[ci], 0.0, tt[ci])
            t = path / C_SOUND
            ok = (chord > 0) & (t < t_end)
            if np.any(ok):
                ci, chord, path, t = ci[ok], chord[ok], path[ok], t[ok]
                E = W[ci] * (chord / v_sph)[:, None] * np.exp(-np.outer(path, m_air))  # (D, 8)
                b = np.minimum((t / bin_s).astype(np.int64), nb - 1)
                for k in range(N_BANDS):
                    e[k] += np.bincount(b, weights=E[:, k], minlength=nb)
                    e2[k] += np.bincount(b, weights=E[:, k] ** 2, minlength=nb)
                det += len(ci)
                if win is not None:
                    inw = (t > win.start) & (t < win.end)
                    if np.any(inw):
                        hw = np.sin(np.pi * (t[inw] - win.start) / (win.end - win.start)) ** 2
                        x = hw[:, None] * E[inw] * np.exp(-np.outer(win.end - t[inw], win.rate))
                        s1 += x.sum(axis=0)
                        s2 += (x * x).sum(axis=0)
        if room is not None:  # energy in the room while on this segment (difference array)
            i0 = np.minimum(np.ceil(Li / (C_SOUND * room_dt)).astype(np.int64), n_room)
            i1 = np.minimum(np.ceil((Li + tt) / (C_SOUND * room_dt)).astype(np.int64), n_room)
            for k in range(N_BANDS):
                room[k] += np.bincount(i0, weights=W[:, k], minlength=n_room + 1)
                room[k] -= np.bincount(i1, weights=W[:, k], minlength=n_room + 1)
        # move to the wall, absorb, reflect
        P = P + U * tt[:, None]
        np.clip(P, 0.0, d, out=P)
        Li = Li + tt
        side = (U[np.arange(len(idx)), ax] > 0).astype(np.int64)
        face = 2 * ax + side
        W = W * rho[face]
        scat = rng.random(len(idx)) < s_face[face]
        U = U.copy()
        rows = np.arange(len(idx))
        U[rows, ax] = -U[rows, ax]
        if np.any(scat):
            si = np.nonzero(scat)[0]
            U[si] = _lambert(rng, ax[si], np.where(side[si] == 1, -1.0, 1.0))
        p[idx], u[idx], L[idx], w[idx] = P, U, Li, W
        alive[idx] = (Li < l_end) & (W.max(axis=1) > 0)
    out = {"e": e, "e2": e2, "det": det, "s1": s1, "s2": s2}
    if room is not None:
        out["room"] = np.cumsum(room, axis=1)[:, :n_room]
    return out


def trace(dims, alpha, scattering, m_air, src, rcv, n: int, seed: int = TRACER_SEED, t_end: float = 0.5,
          bin_s: float = 0.010, r_d: float = R_D, window: Window | None = None, room_dt: float | None = None,
          first_chunk: int = 0, total_n: int | None = None) -> TraceResult:
    """Trace n particles (chunks first_chunk, first_chunk + 1, ...). ``alpha``: (6, 8) per face and band
    (or (6,) broadband); ``scattering``: (6,) broadband; ``m_air``: (8,) energy attenuation 1/m.
    ``total_n``: the particle count the energies are normalised to (4π/total_n each; default n)."""
    a = np.asarray(alpha, float)
    if a.ndim == 1:
        a = np.repeat(a[:, None], N_BANDS, axis=1)
    rho = 1.0 - a  # (6, 8)
    s_face = np.asarray(scattering, float).reshape(6)
    m = np.asarray(m_air, float).reshape(N_BANDS)
    nb = int(np.ceil(t_end / bin_s))
    total = total_n or n
    scale = 4.0 * np.pi / total
    n_room = int(np.ceil(t_end / room_dt)) if room_dt else 0
    acc = None
    done, j = 0, first_chunk
    while done < n:
        cnt = min(CHUNK, n - done)
        rng = np.random.default_rng(np.random.SeedSequence([int(seed), int(j)]))
        r = _trace_chunk(rng, cnt, scale, dims, rho, s_face, m, src, rcv, t_end, bin_s, nb, r_d, window, room_dt, n_room)
        if acc is None:
            acc = r
        else:
            for key in ("e", "e2", "s1", "s2", "room"):
                if acc.get(key) is not None:
                    acc[key] = acc[key] + r[key]
            acc["det"] += r["det"]
        done += cnt
        j += 1
    res = TraceResult(n, int(seed), bin_s, acc["e"], acc["e2"], acc["det"], acc["s1"], acc["s2"])
    if room_dt:
        res.room_energy, res.room_dt = acc["room"], room_dt
    res.extra["chunks"] = (first_chunk, j)
    return res


def trace_with_doubling(dims, alpha, scattering, m_air, src, rcv, gate_end: float, seed: int = TRACER_SEED,
                        t_end: float | None = None, window: Window | None = None, log=None) -> tuple[TraceResult, dict]:
    """B11 doubling rule: start with N0 = ceil(254 V); while some band has fewer than 3 bins with
    k >= 684 among the bins that end by ``gate_end`` (t_mix,e), double N (new particles only), up to
    16 N0. Returns the result and a log {n0, n, doublings, gated_bins_min, enough}.

    Particles are always normalised to the final N: a doubling re-traces nothing, it adds chunks
    and rescales (energies scale by N_old/N_new, squares by its square)."""
    V = float(np.prod(dims))
    N0 = n0(V)
    t_end = t_end if t_end is not None else gate_end + 0.02
    chunks_per = int(np.ceil(N0 / CHUNK))
    res = trace(dims, alpha, scattering, m_air, src, rcv, N0, seed, t_end, window=window)
    doublings = 0
    while True:
        nbg = int(np.floor(gate_end / res.bin_s + 1e-9))
        gated = (res.k[:, :nbg] >= K_GATE).sum(axis=1)
        enough = bool(gated.min() >= 3)
        if log:
            log(f"tracer N = {res.n}: gated bins per band {gated.tolist()}")
        if enough or doublings >= MAX_DOUBLINGS:
            break
        doublings += 1
        add_n = res.n  # double
        new = trace(dims, alpha, scattering, m_air, src, rcv, add_n, seed, t_end, window=window,
                    first_chunk=res.extra["chunks"][1])
        f = res.n / (res.n + add_n)  # renormalise both halves to 4π/(N_old + N_new)
        merged = TraceResult(res.n + add_n, res.seed, res.bin_s, (res.e + new.e) * f, (res.e2 + new.e2) * f * f,
                             res.detections + new.detections)
        if window is not None:
            merged.window_s1 = (res.window_s1 + new.window_s1) * f
            merged.window_s2 = (res.window_s2 + new.window_s2) * f * f
        merged.extra["chunks"] = (0, new.extra["chunks"][1])
        res = merged
    info = {"n0": N0, "n": res.n, "doublings": doublings, "seed": int(seed), "gated_bins_per_band": gated.tolist(),
            "enough_gated_bins": enough, "detections": res.detections, "chunks_per_n0": chunks_per}
    return res, info
