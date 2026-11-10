"""Phase 05b session 2, decision D-T1 evidence: prototypes of candidate formulations of the propagated
diffuse energy for the tail-level match (docs/phases/phase-05b2.md §3 D-T1), measured OUTSIDE src/sim.

    python tools/validation/phase05b2_dt1.py agree   # candidate (f) vs the reference hybrid, 15 (A) cases
    python tools/validation/phase05b2_dt1.py bench   # candidate (f): W1/W2 (AQ10), CR4, 100 m rooms
    python tools/validation/phase05b2_dt1.py dense   # candidate (a): dense kernel on W1 + memory table

Writes tools/validation/data/phase05b2_dt1.json (one section per step). numba is an offline dependency
(tools/validation/requirements-offline.txt); CI does not run this script.

Candidate (f), "MC-NEE": a seeded Monte-Carlo estimator of the same model as tools/acoustics/ref_hybrid.py
in its continuous (ℓ → 0) form. Particles leave the emitter uniformly over the sphere (energy 4π/N each:
unit intensity per steradian, AX2) and are traced in the shoebox; at every wall hit the incident energy
is multiplied by (1 − α_b); the diffuse emission s(1 − α_b) of the incident energy (Kuttruff Eq. 4.24,
§5.2 split) is gathered at the point listener directly and over every specular route, i.e. over the
listener's lattice images with Π((1 − α)(1 − s))^hits and air exp(−m_b R) (Eq. 4.29 with Joyce/Gilbert
transport, Eq. 4.35): next-event estimation, cos θ / (π r²) per unit diffusely emitted energy, weighted by
the matching window (Hann, referred to t_mix,e with the Eyring rate, normalised to 10 ms: NoiseTail.cpp
matchTail). The particle then continues diffusely (cosine-weighted direction) with probability s and
specularly otherwise (broadband s, AQ3: no importance weights). Only the diffuse energy is estimated; the
specular entries stay exact (ISM). Air is applied along the path per band.
"""

from __future__ import annotations

import argparse
import json
import pathlib
import resource
import sys
import time

import numpy as np

HERE = pathlib.Path(__file__).resolve().parent
REPO = HERE.parents[1]
sys.path.insert(0, str(REPO))

from tools.acoustics import ref_hybrid as rh  # noqa: E402
from tools.validation import phase05b as p5  # noqa: E402
from tools.validation import scope6  # noqa: E402

OUT = HERE / "data" / "phase05b2_dt1.json"
C = rh.C_SOUND
SEED = 0x5EED
AQ9 = (3, 4, 5)

try:
    from numba import njit
except ImportError:  # pragma: no cover
    njit = None


def log(*a):
    print(*a, file=sys.stderr, flush=True)


def load() -> dict:
    return json.loads(OUT.read_text()) if OUT.exists() else {}


def save(d: dict):
    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text(json.dumps(d, indent=1) + "\n")


if njit is not None:
    @njit(cache=True, inline='always')
    def _next(state, inc):
        old = state
        state = (old * np.uint64(6364136223846793005) + inc)
        xs = np.uint32((((old >> np.uint64(18)) ^ old) >> np.uint64(27)) & np.uint64(0xFFFFFFFF))
        rot = np.uint32(old >> np.uint64(59))
        out = np.uint32((xs >> rot) | (xs << ((np.uint32(32) - rot) & np.uint32(31))))
        return state, (out + 0.5) / 4294967296.0

    @njit(cache=True, fastmath=True)
    def mc2(dims, alpha, s, m_air, src, face_pos, face_spec, face_dist, face_cnt, rcv, a, b, rate, norm, npaths, seed, strat):
        nb = 8
        acc = np.zeros(nb); acc2 = np.zeros(nb)
        gam = np.empty(nb)
        for k in range(nb):
            gam[k] = m_air[k] - rate[k] / C
        w = np.empty(nb); contrib = np.empty(nb); hitf = np.empty(nb)
        x = np.empty(3); d = np.empty(3)
        nsq = int(np.sqrt(npaths)) if strat else 0
        for p in range(npaths):
            st = np.uint64(seed) * np.uint64(0x9E3779B97F4A7C15) + np.uint64(p) * np.uint64(0xD1B54A32D192ED03)
            inc = np.uint64(2 * p + 1)
            st, u1 = _next(st, inc); st, u1 = _next(st, inc); st, u2 = _next(st, inc)
            if strat and p < nsq * nsq:
                u1 = ((p % nsq) + u1) / nsq; u2 = ((p // nsq) + u2) / nsq
            z = 1 - 2 * u1; ph = 2 * np.pi * u2; rr = np.sqrt(max(0.0, 1 - z * z))
            d[0] = rr * np.cos(ph); d[1] = rr * np.sin(ph); d[2] = z
            x[0] = src[0]; x[1] = src[1]; x[2] = src[2]
            for k in range(nb):
                w[k] = 4 * np.pi / npaths; contrib[k] = 0.0
            t = 0.0
            while True:
                tb = 1e300; f = -1
                for ax in range(3):
                    if d[ax] > 1e-15:
                        tt = (dims[ax] - x[ax]) / d[ax]
                        if tt < tb: tb = tt; f = 2 * ax + 1
                    elif d[ax] < -1e-15:
                        tt = -x[ax] / d[ax]
                        if tt < tb: tb = tt; f = 2 * ax
                for i in range(3): x[i] += tb * d[i]
                ax = f // 2
                x[ax] = 0.0 if f % 2 == 0 else dims[ax]
                t += tb / C
                if t >= b: break
                for k in range(nb): w[k] *= np.exp(-m_air[k] * tb)
                sf = s[f]
                if sf > 0:
                    rem = C * (b - t)
                    dx0 = x[0] - rcv[0]; dy0 = x[1] - rcv[1]; dz0 = x[2] - rcv[2]
                    dlr = np.sqrt(dx0 * dx0 + dy0 * dy0 + dz0 * dz0)
                    for k in range(nb):
                        hitf[k] = w[k] * (1 - alpha[f, k]) * sf / np.pi * np.exp(-rate[k] * (b - t))
                    for m in range(face_cnt[f]):
                        if face_dist[f, m] - dlr > rem: break
                        dx = face_pos[f, m, 0] - x[0]; dy = face_pos[f, m, 1] - x[1]; dz = face_pos[f, m, 2] - x[2]
                        r2 = dx * dx + dy * dy + dz * dz; r = np.sqrt(r2)
                        ta = t + r / C
                        if ta <= a or ta >= b: continue
                        cs = (dx if ax == 0 else (dy if ax == 1 else dz))
                        if f % 2 == 1: cs = -cs
                        cs /= r
                        if cs <= 0: continue
                        hw = np.sin(np.pi * (ta - a) / (b - a)); hw *= hw
                        g = cs / r2 * hw
                        for k in range(nb):
                            contrib[k] += hitf[k] * g * face_spec[f, m, k] * np.exp(-gam[k] * r)
                for k in range(nb): w[k] *= (1 - alpha[f, k])
                st, u = _next(st, inc)
                if u < sf:
                    st, u1 = _next(st, inc); st, u2 = _next(st, inc)
                    ct = np.sqrt(u1); stt = np.sqrt(1 - u1); ph = 2 * np.pi * u2
                    a1 = (ax + 1) % 3; a2 = (ax + 2) % 3
                    d[a1] = stt * np.cos(ph); d[a2] = stt * np.sin(ph); d[ax] = ct if f % 2 == 0 else -ct
                else:
                    d[ax] = -d[ax]
                mx = 0.0
                for k in range(nb): mx = max(mx, w[k])
                if mx == 0.0: break
            for k in range(nb):
                v = contrib[k] * norm
                acc[k] += v; acc2[k] += (v * npaths) ** 2
        return acc, acc2


def face_lists(dims, var, rcv, reach):
    lat = rh.lattice(dims, reach + 1.0)
    pos = lat.map(np.asarray(rcv, float)); spec = rh.specular_factor(lat.hits, var.spec).T
    dist = np.linalg.norm(pos - np.asarray(rcv, float), axis=1)
    keep = dist <= reach + np.linalg.norm(dims) + 1e-9
    pos, spec, dist = pos[keep], spec[keep], dist[keep]
    M = len(pos)
    fp = np.zeros((6, M, 3)); fs = np.zeros((6, M, 8)); fd = np.zeros((6, M)); fc = np.zeros(6, np.int64)
    for f in range(6):
        ax, hi = f // 2, f % 2
        plane = dims[ax] if hi else 0.0
        front = (pos[:, ax] < plane - 1e-12) if hi else (pos[:, ax] > plane + 1e-12)
        idx = np.nonzero(front)[0]; idx = idx[np.argsort(dist[idx], kind='stable')]
        n = len(idx); fc[f] = n
        fp[f, :n] = pos[idx]; fs[f, :n] = spec[idx]; fd[f, :n] = dist[idx]
    return fp, fs, fd, fc, M

def e_diff(dims, alpha_faces8, s_faces, m_air, src, rcv, mix, t60, npaths, seed=SEED, strat=True):
    var = rh.variant(alpha_faces8, s_faces, m_air)
    a, b = mix['windowStartS'], mix['mixS']
    fp, fs, fd, fc, M = face_lists(np.asarray(dims, float), var, rcv, C * b)
    rate = rh.ENERGY_DECAY_PER_T60 / np.asarray(t60)
    norm = rh.MATCH_NORMALISATION_S / (0.5 * (b - a))
    acc, acc2 = mc2(np.asarray(dims, float), np.asarray(alpha_faces8, float).reshape(6, 8), np.asarray(s_faces, float),
                    np.asarray(m_air, float), np.asarray(src, float), fp, fs, fd, fc, np.asarray(rcv, float),
                    a, b, rate, norm, npaths, seed, strat)
    var_ = acc2 / npaths - acc**2
    return acc, np.sqrt(np.maximum(var_, 0) / npaths), M


# ------------------------------------------------------------------------------------------
# Steps
# ------------------------------------------------------------------------------------------

AQ = [0.15, 0.18, 0.2, 0.22, 0.24, 0.26, 0.28, 0.3]  # AQ10 benchmark room materials (test_hybrid_ir.cpp aq10Room)


def bench_scenes() -> list[dict]:
    """W1/W2 (AQ10, tests/unit/test_hybrid_ir.cpp aq10Room), CR4's 10 pairs, two 100 m cubes."""
    out = []
    for e, src in enumerate(((7.0, 20.0, 2.0), (13.0, 20.0, 2.0))):
        out.append({"name": f"W1_e{e}", "dims": (20.0, 30.0, 10.0), "alpha": [AQ] * 6, "s": [0.3] * 6,
                    "src": src, "rcv": (10.0, 8.0, 1.7), "group": "W1"})
    flutter = [[0.02] * 8] * 2 + [[0.8] * 8] * 4
    for e, src in enumerate(((7.0, 20.0, 2.0), (13.0, 20.0, 2.0))):
        out.append({"name": f"W2_e{e}", "dims": (20.0, 30.0, 10.0), "alpha": flutter, "s": [0.0, 0.0, 0.1, 0.1, 0.1, 0.1],
                    "src": src, "rcv": (10.0, 8.0, 1.7), "group": "W2"})
    for n in scope6.pair_names("CR4"):
        si = scope6.scene_inputs(scope6.rv.SCENES / f"{n}.json")
        out.append({"name": n, "dims": tuple(float(x) for x in si["dims"]), "alpha": np.asarray(si["alpha"]).reshape(6, 8).tolist(),
                    "s": [float(x) for x in si["s"]], "src": tuple(si["src"]), "rcv": tuple(si["rcv"]), "group": "CR4"})
    big = [0.1, 0.1, 0.12, 0.14, 0.16, 0.18, 0.2, 0.22]
    for e, src in enumerate(((45.0, 70.0, 2.0), (55.0, 70.0, 2.0))):
        out.append({"name": f"cube100_e{e}", "dims": (100.0, 100.0, 100.0), "alpha": [big] * 6, "s": [0.3] * 6,
                    "src": src, "rcv": (50.0, 30.0, 1.7), "group": "cube100"})
    # flutter at the contract maximum (hard x-walls, α = 0.95 elsewhere): AX22 fallback, t_cap ≈ 2.1 s (the 100 m fallback row)
    for e, src in enumerate(((45.0, 70.0, 2.0), (55.0, 70.0, 2.0))):
        out.append({"name": f"cube100_flutter_e{e}", "dims": (100.0, 100.0, 100.0), "alpha": [[0.02] * 8] * 2 + [[0.95] * 8] * 4,
                    "s": [0.0, 0.0, 0.05, 0.05, 0.05, 0.05], "src": src, "rcv": (50.0, 30.0, 1.7), "group": "cube100_flutter"})
    return out


def run_case(c: dict, npaths: int, seed: int = SEED) -> dict:
    m = scope6.air_m()
    var = rh.variant(c["alpha"], c["s"], m)
    plan = rh.phase04_plan(c["dims"], var, c["src"], c["rcv"])
    t0 = time.perf_counter()
    mean, se, M = e_diff(c["dims"], c["alpha"], c["s"], m, c["src"], c["rcv"], plan["mix"], plan["t60"], npaths, seed)
    dt = time.perf_counter() - t0
    tot = plan["target_specular"] + mean
    return {"plan": plan, "mean": mean, "se": se, "images": M, "seconds": dt, "total": tot,
            "se_db": 4.343 * se / np.maximum(tot, 1e-300)}


def step_agree(npaths: int):
    """(f) vs the reference hybrid on the 15 (A) cases. The reference is the hybrid's E_target as session 1
    evaluated it (ℓ = 1.25 m, AX36 (a)): E_target(AX16) / 10^(ΔL_b/10) from phase05b.json."""
    d5 = json.loads(p5.OUT.read_text())
    out = {"npaths": npaths, "seed": SEED, "cases": {}}
    for c in p5.cases():
        r = run_case({"dims": c["dims"], "alpha": [[a] * 8 for a in c["alpha_faces"]], "s": [c["s"]] * 6,
                      "src": c["src"], "rcv": c["rcv"]}, npaths)
        row = {}
        for bi, bhz in zip(AQ9, ("500", "1000", "2000")):
            dl = d5["gate"]["cases"][c["name"]]["window"][bhz]["delta_lb_db"]
            e_hyb = r["plan"]["target_ax16"][bi] / 10 ** (dl / 10)
            row[bhz] = {"mc_vs_hybrid_db": float(10 * np.log10(r["total"][bi] / e_hyb)), "se_db": float(r["se_db"][bi])}
        out["cases"][c["name"]] = {"mix_s": r["plan"]["mix"]["mixS"], "images": r["images"], "seconds": r["seconds"], "bands": row}
        log(c["name"], {k: round(v["mc_vs_hybrid_db"], 3) for k, v in row.items()}, f"SE {row['1000']['se_db']:.3f}")
    z = [abs(v["mc_vs_hybrid_db"]) / v["se_db"] for c in out["cases"].values() for v in c["bands"].values()]
    out["max_abs_db"] = float(max(abs(v["mc_vs_hybrid_db"]) for c in out["cases"].values() for v in c["bands"].values()))
    out["max_abs_over_se"] = float(max(z))
    d = load()
    d["agree"] = out
    save(d)


def step_bench(npaths: int, se_targets=(0.083, 0.033)):
    """(f) per emitter: time at npaths (single thread, numba), SE at npaths, paths needed for SE targets
    (SE ∝ 1/√N), and memory (the image tables). The prototype runs one thread; times are for scale."""
    out = {"npaths": npaths, "seed": SEED, "threads": 1, "cases": {}}
    for c in bench_scenes():
        run_case(c, 64)  # compile once
        r = run_case(c, npaths)
        worst = float(np.max(r["se_db"][list(AQ9)]))
        need = {str(t): int(np.ceil(npaths * (worst / t) ** 2)) for t in se_targets}
        out["cases"][c["name"]] = {
            "group": c["group"], "mix_s": r["plan"]["mix"]["mixS"], "fallback": r["plan"]["fallback"],
            "listener_images": r["images"], "ms_per_emitter": 1e3 * r["seconds"], "se_db_aq9": r["se_db"][list(AQ9)].tolist(),
            "paths_for_se": need, "ms_for_se": {k: 1e3 * r["seconds"] * v / npaths for k, v in need.items()},
            "image_table_mb": r["images"] * 6 * (3 + 8 + 1) * 8 / 1e6,
            "dL_ax16_vs_f_db_1k": float(10 * np.log10(r["plan"]["target_ax16"][4] / r["total"][4]))}
        log(c["name"], f"{1e3 * r['seconds']:.1f} ms", f"SE {worst:.3f} dB", need)
    d = load()
    d["bench"] = out
    save(d)


def step_dense():
    """(a) the dense kernel of ref_hybrid on W1 (numpy reference implementation; a C++ port would be faster but
    keeps the same N²T memory), and the dense memory table (8 bands, float32, decimal GB) for the plan's rooms."""
    m = scope6.air_m()
    var = rh.variant([AQ] * 6, [0.3] * 6, m)
    dims, rcv, srcs = (20.0, 30.0, 10.0), (10.0, 8.0, 1.7), ((7.0, 20.0, 2.0), (13.0, 20.0, 2.0))
    plans = [rh.phase04_plan(dims, var, s, rcv) for s in srcs]
    t_end = max(p["mix"]["mixS"] for p in plans) + rh.CROSSFADE_HALF_S + 2e-3
    t0 = time.perf_counter()
    rk = rh.RoomKernel(dims, 2.5, t_end, [var])
    t1 = time.perf_counter()
    inc = np.stack([rh.injection(rk, s) for s in srcs])
    gat = np.stack([rh.gather_kernel(rk, rcv) for _ in srcs])
    t2 = time.perf_counter()
    env, gens = rh.solve(rk, inc, gat)
    t3 = time.perf_counter()
    targets = [rh.target_hybrid(p, env[0, :, i]) for i, p in enumerate(plans)]
    out = {"W1": {"patches": rk.N, "bins": rk.T, "kernel_gb": rk.K.nbytes / 1e9,
                  "kernel_build_s": t1 - t0, "injection_gather_s": t2 - t1, "solve_s": t3 - t2, "generations": int(gens.max()),
                  "peak_rss_gb": resource.getrusage(resource.RUSAGE_SELF).ru_maxrss / 1e6,
                  "E_target_1k": [float(t[4]) for t in targets],
                  "dL_ax16_vs_hybrid_db_1k": [float(10 * np.log10(p["target_ax16"][4] / t[4])) for p, t in zip(plans, targets)]}}

    def dense_gb(dims_, t_end_, ell=2.5):
        from tools.acoustics import radiosity
        n = len(radiosity.box_patches(dims_, ell).areas)
        return n, int(np.ceil(t_end_ / rh.DT)), n * n * int(np.ceil(t_end_ / rh.DT)) * 8 * 4 / 1e9

    rows = {}
    for name, dims_, t_ in (("AQ10 non-fallback", (20, 30, 10), 0.118), ("AQ10 fallback", (20, 30, 10), 0.385),
                            ("CR4", (42.026308, 41.744215, 4.934291), 0.155), ("100 m non-fallback", (100, 100, 100), 1.035),
                            ("100 m fallback", (100, 100, 100), 2.1)):
        n, T, gb = dense_gb(dims_, t_)
        rows[name] = {"patches": n, "bins": T, "kernel_gb_8_bands_float32": gb}
    out["memory_table"] = rows
    d = load()
    d["dense"] = out
    save(d)
    log(json.dumps(out, indent=1))


def step_openfield(npaths: int = 400_000):
    """C1 (decider, D-T5 (4)): open_field under 5.1-A. Exact single-scatter floor integral (polar grid, as
    tools/acoustics/ground_scatter.py, restricted to the floor, window-weighted) against (f)."""
    sc = json.loads((REPO / "tests" / "scenes" / "valid" / "open_field.json").read_text())
    S = sc["room"]["surfaces"]
    order = ["xMin", "xMax", "yMin", "yMax", "floor", "ceiling"]
    alpha = [S[k]["absorption"] for k in order]
    s = [S[k]["scattering"] for k in order]
    m = scope6.air_m()
    var = rh.variant(alpha, s, m)
    dims = tuple(sc["room"]["geometry"]["dimensions"])
    rcv = np.array(sc["listener"]["position"], float)
    out = {}
    for e in sc["emitters"]:
        src = np.array(e["position"], float)
        plan = rh.phase04_plan(dims, var, src, rcv)
        a, b, t60 = plan["mix"]["windowStartS"], plan["mix"]["mixS"], plan["t60"]
        rate = rh.ENERGY_DECAY_PER_T60 / t60
        norm = rh.MATCH_NORMALISATION_S / (0.5 * (b - a))
        edges = np.concatenate([[0.0], np.geomspace(1e-3, 1e3, 6000)])
        r = 0.5 * (edges[1:] + edges[:-1])
        dr = np.diff(edges)
        phi = (np.arange(1440) + 0.5) * 2 * np.pi / 1440
        R, P = np.meshgrid(r, phi, indexing="ij")
        x, y = src[0] + R * np.cos(P), src[1] + R * np.sin(P)
        inside = (x >= 0) & (x <= dims[0]) & (y >= 0) & (y <= dims[1])
        r1 = np.sqrt(R**2 + src[2] ** 2)
        r2 = np.sqrt((x - rcv[0]) ** 2 + (y - rcv[1]) ** 2 + rcv[2] ** 2)
        w = (R * dr[:, None] * 2 * np.pi / 1440) * (src[2] / r1) * (rcv[2] / r2) / (np.pi * r1**2 * r2**2) * inside
        t = (r1 + r2) / C
        hw = np.where((t > a) & (t < b), np.sin(np.pi * (t - a) / (b - a)) ** 2, 0.0)
        rho = np.asarray(s[4]) * (1 - np.asarray(alpha[4]))
        e_int = np.array([norm * rho[k] * np.sum(w * hw * np.exp(-m[k] * (r1 + r2)) * np.exp(-rate[k] * (b - t))) for k in range(8)])
        mean, se, _ = e_diff(dims, alpha, s, m, src, rcv, plan["mix"], t60, npaths)
        rd = np.linalg.norm(src - rcv)
        direct = np.exp(-m * rd) / rd**2
        tail_total = e_int / (rh.MATCH_NORMALISATION_S * rate)
        out[e["id"]] = {"mixS": b, "fallback": plan["fallback"], "t60_s": t60.tolist(),
                        "E_target_spec": plan["target_specular"].tolist(), "E_target_diff_integral": e_int.tolist(),
                        "E_target_diff_mc": mean.tolist(), "mc_se": se.tolist(),
                        "tail_level_at_mix_re_direct_per10ms_db": (10 * np.log10(np.maximum(e_int, 1e-300) / direct)).tolist(),
                        "tail_energy_re_direct_db": (10 * np.log10(np.maximum(tail_total, 1e-300) / direct)).tolist()}
        log(e["id"], np.round(out[e["id"]]["tail_energy_re_direct_db"], 1))
    d = load()
    d["open_field"] = out
    save(d)


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("step", choices=["agree", "bench", "dense", "openfield", "c3", "c4", "c5", "c6", "c7", "c9b", "c12a", "c12b", "c12d", "c13", "c13x", "c13g"])
    ap.add_argument("--paths", type=int, default=32_000)
    a = ap.parse_args(argv)
    if njit is None:
        raise SystemExit("numba is required (pip install --require-hashes -r tools/validation/requirements-offline.txt)")
    if a.step == "agree":
        step_agree(a.paths)
    elif a.step == "bench":
        step_bench(a.paths)
    elif a.step == "dense":
        step_dense()
    elif a.step == "openfield":
        step_openfield()
    else:
        {"c3": step_c3, "c4": step_c4, "c5": step_c5, "c6": step_c6, "c7": step_c7, "c9b": step_c9b,
         "c12a": step_c12a, "c12b": step_c12b, "c12d": step_c12d,
         "c13": step_c13, "c13x": step_c13x, "c13g": step_c13g}[a.step]()



# ------------------------------------------------------------------------------------------
# Convening-round computations C3–C10 for D-T1/D-T2/D-T6 (docs/review/phase-05b2/9-decider-convene-T1-T2-T6.md)
# ------------------------------------------------------------------------------------------

if njit is not None:
    from numba import prange

    @njit(parallel=True, fastmath=False, cache=True)
    def mc3(dims, alpha, s, m_air, src, face_pos, face_spec, face_dist, face_cnt, rcv, a, b, rate, norm, npaths, seed,
            f32, out, hsh):
        """As mc2 (same model, same RNG stream per path index p), parallel over paths: out[p, k] is path p's
        window-weighted diffuse energy per band (already divided by npaths), hsh[p] a hash of its face-hit
        sequence. f32: round the path state (position, direction, time) to float32 after every step."""
        nb = 8
        gam = np.empty(nb)
        for k in range(nb):
            gam[k] = m_air[k] - rate[k] / C
        for p in prange(npaths):
            w = np.empty(nb); contrib = np.zeros(nb); hitf = np.empty(nb)
            x = np.empty(3); d = np.empty(3)
            st = np.uint64(seed) * np.uint64(0x9E3779B97F4A7C15) + np.uint64(p) * np.uint64(0xD1B54A32D192ED03)
            inc = np.uint64(2 * p + 1)
            st, u1 = _next(st, inc); st, u1 = _next(st, inc); st, u2 = _next(st, inc)
            z = 1 - 2 * u1; ph = 2 * np.pi * u2; rr = np.sqrt(max(0.0, 1 - z * z))
            d[0] = rr * np.cos(ph); d[1] = rr * np.sin(ph); d[2] = z
            x[0] = src[0]; x[1] = src[1]; x[2] = src[2]
            for k in range(nb):
                w[k] = 4 * np.pi / npaths
            t = 0.0
            h = np.uint64(1469598103934665603)
            while True:
                tb = 1e300; f = -1
                for ax in range(3):
                    if d[ax] > 1e-15:
                        tt = (dims[ax] - x[ax]) / d[ax]
                        if tt < tb:
                            tb = tt; f = 2 * ax + 1
                    elif d[ax] < -1e-15:
                        tt = -x[ax] / d[ax]
                        if tt < tb:
                            tb = tt; f = 2 * ax
                for i in range(3):
                    x[i] += tb * d[i]
                ax = f // 2
                x[ax] = 0.0 if f % 2 == 0 else dims[ax]
                t += tb / C
                if f32:
                    for i in range(3):
                        x[i] = np.float64(np.float32(x[i])); d[i] = np.float64(np.float32(d[i]))
                    t = np.float64(np.float32(t))
                h = (h ^ np.uint64(f + 1)) * np.uint64(1099511628211)
                if t >= b:
                    break
                for k in range(nb):
                    w[k] *= np.exp(-m_air[k] * tb)
                sf = s[f]
                if sf > 0:
                    rem = C * (b - t)
                    dx0 = x[0] - rcv[0]; dy0 = x[1] - rcv[1]; dz0 = x[2] - rcv[2]
                    dlr = np.sqrt(dx0 * dx0 + dy0 * dy0 + dz0 * dz0)
                    for k in range(nb):
                        hitf[k] = w[k] * (1 - alpha[f, k]) * sf / np.pi * np.exp(-rate[k] * (b - t))
                    for m in range(face_cnt[f]):
                        if face_dist[f, m] - dlr > rem:
                            break
                        dx = face_pos[f, m, 0] - x[0]; dy = face_pos[f, m, 1] - x[1]; dz = face_pos[f, m, 2] - x[2]
                        r2 = dx * dx + dy * dy + dz * dz; r = np.sqrt(r2)
                        ta = t + r / C
                        if ta <= a or ta >= b:
                            continue
                        cs = (dx if ax == 0 else (dy if ax == 1 else dz))
                        if f % 2 == 1:
                            cs = -cs
                        cs /= r
                        if cs <= 0:
                            continue
                        hw = np.sin(np.pi * (ta - a) / (b - a)); hw *= hw
                        g = cs / r2 * hw
                        for k in range(nb):
                            contrib[k] += hitf[k] * g * face_spec[f, m, k] * np.exp(-gam[k] * r)
                for k in range(nb):
                    w[k] *= (1 - alpha[f, k])
                st, u = _next(st, inc)
                if u < sf:
                    st, u1 = _next(st, inc); st, u2 = _next(st, inc)
                    ct = np.sqrt(u1); stt = np.sqrt(1 - u1); ph = 2 * np.pi * u2
                    a1 = (ax + 1) % 3; a2 = (ax + 2) % 3
                    d[a1] = stt * np.cos(ph); d[a2] = stt * np.sin(ph); d[ax] = ct if f % 2 == 0 else -ct
                else:
                    d[ax] = -d[ax]
                mx = 0.0
                for k in range(nb):
                    mx = max(mx, w[k])
                if mx == 0.0:
                    break
            for k in range(nb):
                out[p, k] = contrib[k] * norm
            hsh[p] = h


def paths_run(c: dict, npaths: int, seed: int = SEED, f32: bool = False, plan=None):
    """Per-path contributions (npaths, 8), face-sequence hashes, plan and image count for one scene dict."""
    m = scope6.air_m()
    var = rh.variant(c["alpha"], c["s"], m)
    plan = rh.phase04_plan(c["dims"], var, c["src"], c["rcv"]) if plan is None else plan
    a, b = plan["mix"]["windowStartS"], plan["mix"]["mixS"]
    fp, fs, fd, fc, M = face_lists(np.asarray(c["dims"], float), var, c["rcv"], C * b)
    rate = rh.ENERGY_DECAY_PER_T60 / np.asarray(plan["t60"])
    norm = rh.MATCH_NORMALISATION_S / (0.5 * (b - a))
    out = np.zeros((npaths, 8))
    hsh = np.zeros(npaths, dtype=np.uint64)
    mc3(np.asarray(c["dims"], float), np.asarray(c["alpha"], float).reshape(6, 8), np.asarray(c["s"], float), m,
        np.asarray(c["src"], float), fp, fs, fd, fc, np.asarray(c["rcv"], float), a, b, rate, norm, npaths, seed,
        f32, out, hsh)
    return out, hsh, plan, M


def summarise(out: np.ndarray, plan) -> dict:
    """Fixed-order reduction (sum over the path axis in index order) and statistics per band."""
    n = out.shape[0]
    mean = np.zeros(8)
    for p in range(n):  # fixed order, independent of the number of threads that produced `out`
        mean += out[p]
    x = out * n  # per-path estimators
    se = np.sqrt(np.maximum((x ** 2).mean(axis=0) - mean ** 2, 0) / n)
    tot = plan["target_specular"] + mean
    share = np.where(mean > 0, out.max(axis=0) / np.maximum(mean, 1e-300), 0.0)
    return {"mean": mean, "se": se, "total": tot, "se_db": 4.343 * se / np.maximum(tot, 1e-300), "max_path_share": share}


SE_TARGETS_DB = (0.33, 0.083, 0.033, 0.0145)  # Tol-1/2/3 SE targets and L2-F2 (convening D-T1.4, D-T2)


def _need(n, se_db, t):
    return int(np.ceil(n * (se_db / t) ** 2)) if se_db > 0 else 1


def _abc(c):  # (A)-case dict -> scene dict
    return {"dims": c["dims"], "alpha": [[a] * 8 for a in c["alpha_faces"]], "s": [c["s"]] * 6, "src": c["src"], "rcv": c["rcv"]}


def step_c3(npaths: int = 32_000):
    """C3 (and C9 for the (A) cases): (f) vs ref_hybrid in all 8 bands on the 15 (A) cases; reference at 2.5 and
    1.25 m (air factored out: exact for these band-flat cases, phase05b.factorised_env); the 2.5 -> 1.25 m change."""
    out = {"npaths": npaths, "cases": {}}
    for c in p5.cases():
        plan = p5.plan_of(c)
        ref = {str(sz): rh.target_hybrid(plan, p5.factorised_env(c, sz)) for sz in (2.5, 1.25)}
        o, _, plan2, _ = paths_run(_abc(c), npaths, plan=plan)
        s = summarise(o, plan)
        row = {}
        for b in range(8):
            row[str([63, 125, 250, 500, 1000, 2000, 4000, 8000][b])] = {
                "f_vs_ref1.25_db": float(10 * np.log10(s["total"][b] / ref["1.25"][b])),
                "f_vs_ref2.5_db": float(10 * np.log10(s["total"][b] / ref["2.5"][b])),
                "z_vs_ref1.25": float((s["total"][b] - ref["1.25"][b]) / max(s["se"][b], 1e-300)),
                "se_db": float(s["se_db"][b]),
                "ref_change_2.5_to_1.25": float(abs(ref["1.25"][b] / ref["2.5"][b] - 1))}
        out["cases"][c["name"]] = row
        log(c["name"], round(max(abs(v["f_vs_ref1.25_db"]) for v in row.values()), 3))
    per_band = {}
    for bhz in ["63", "125", "250", "500", "1000", "2000", "4000", "8000"]:
        v = [r[bhz] for r in out["cases"].values()]
        per_band[bhz] = {"max_abs_db": max(abs(x["f_vs_ref1.25_db"]) for x in v),
                         "max_abs_z": max(abs(x["z_vs_ref1.25"]) for x in v),
                         "mean_z": float(np.mean([x["z_vs_ref1.25"] for x in v])),
                         "max_ref_change": max(x["ref_change_2.5_to_1.25"] for x in v)}
    out["per_band"] = per_band
    d = load(); d["c3"] = out; save(d)


def near_wall_scenes():
    w1 = {"dims": (20.0, 30.0, 10.0), "alpha": [AQ] * 6, "s": [0.3] * 6}
    _, l4 = p5.layout_alpha(4)
    l4s = {"dims": (20.0, 30.0, 10.0), "alpha": [[a] * 8 for a in l4], "s": [1.0] * 6}
    pos = {"wall": (10.0, 0.1, 1.7), "edge": (0.1, 0.1, 1.7), "corner": (0.1, 0.1, 9.9)}
    out = []
    for room, base in (("W1", w1), ("layout4_s1", l4s)):
        for k, rcv in pos.items():
            out.append(dict(base, name=f"{room}_listener_{k}", src=(7.0, 20.0, 2.0), rcv=rcv))
        out.append(dict(base, name=f"{room}_emitter_wall", src=(7.0, 29.9, 2.0), rcv=(10.0, 8.0, 1.7)))
        out.append(dict(base, name=f"{room}_reference_positions", src=(7.0, 20.0, 2.0), rcv=(10.0, 8.0, 1.7)))
    return out


def _ref_bands(c, sizes, bands):
    """ref_hybrid E_target per band at the given ℓ: per-band kernel without air (hybrid_fast), air applied per bin
    (exact per band), for scenes with band-dependent α. Returns {size: (8,) with NaN outside `bands`}."""
    from tools.validation import hybrid_fast
    m = scope6.air_m()
    var = rh.variant(c["alpha"], c["s"], m)
    plan = rh.phase04_plan(c["dims"], var, c["src"], c["rcv"])
    t_end = plan["mix"]["mixS"] + rh.CROSSFADE_HALF_S + 2e-3
    res = {}
    for sz in sizes:
        e = np.full(8, np.nan)
        env = np.zeros((8, int(np.ceil(t_end / rh.DT))))
        tb = (np.arange(env.shape[1]) + 0.5) * rh.DT
        var0 = rh.variant(c["alpha"], c["s"], np.zeros(8))
        for b in bands:
            rk = hybrid_fast.FastRoomKernel(c["dims"], sz, t_end, var0, b)
            e0 = p5.lean_solve(rk, rh.injection(rk, c["src"])[None], rh.gather_kernel(rk, c["rcv"])[None])[0]
            env[b, :len(e0)] = e0 * np.exp(-m[b] * rh.C_SOUND * tb[:len(e0)])
        th = rh.target_hybrid(plan, env)
        for b in bands:
            e[b] = th[b]
        res[str(sz)] = e
    return res, plan


def step_c4():
    """C4: listener (or emitter) at the AX6 0.1 m clearance from one wall, an edge and a corner."""
    out = {}
    for c in near_wall_scenes():
        rows = {}
        for n in (8000, 32000):
            o, _, plan, M = paths_run(c, n)
            s = summarise(o, plan)
            worst = float(np.max(s["se_db"]))
            rows[str(n)] = {"se_db": s["se_db"].tolist(), "max_path_share": s["max_path_share"].tolist(),
                            "paths_for_se": {str(t): _need(n, worst, t) for t in SE_TARGETS_DB}, "total": s["total"].tolist()}
        t0 = time.perf_counter()
        paths_run(c, 32000, plan=plan)
        dt32 = time.perf_counter() - t0
        rows["ms_32000_4threads"] = 1e3 * dt32
        ref, _ = _ref_bands(c, (2.5, 1.25), AQ9)
        rows["ref"] = {k: [None if np.isnan(x) else float(x) for x in v] for k, v in ref.items()}
        rows["f_vs_ref1.25_db_aq9"] = [float(10 * np.log10(rows["32000"]["total"][b] / ref["1.25"][b])) for b in AQ9]
        rows["ref_change_2.5_to_1.25_aq9"] = [float(abs(ref["1.25"][b] / ref["2.5"][b] - 1)) for b in AQ9]
        out[c["name"]] = rows
        log(c["name"], "SE32k", round(max(rows["32000"]["se_db"]), 3), "share", round(max(rows["32000"]["max_path_share"]), 4),
            "f-ref", np.round(rows["f_vs_ref1.25_db_aq9"], 3))
    d = load(); d["c4"] = out; save(d)


def step_c5(npaths: int = 32_000):
    """C5: sensitivity of (f) to a 1e-9 m perturbation of the positions and to float32 path state; thread-count
    bit-identity of the fixed-order reduction (1, 2, 4 threads)."""
    import numba
    out = {}
    w1 = bench_scenes()[0]
    _, l4 = p5.layout_alpha(4)
    l4s = {"name": "layout4_s1", "dims": (20.0, 30.0, 10.0), "alpha": [[a] * 8 for a in l4], "s": [1.0] * 6,
           "src": (7.0, 20.0, 2.0), "rcv": (10.0, 8.0, 1.7)}
    for c in (w1, l4s):
        o0, h0, plan, _ = paths_run(c, npaths)
        s0 = summarise(o0, plan)
        pert = dict(c, src=tuple(np.asarray(c["src"]) + 1e-9), rcv=tuple(np.asarray(c["rcv"]) + 1e-9))
        o1, h1, _, _ = paths_run(pert, npaths, plan=plan)
        s1 = summarise(o1, plan)
        o2, h2, _, _ = paths_run(c, npaths, f32=True, plan=plan)
        s2 = summarise(o2, plan)
        thr = []
        for th in (1, 2, 4):
            numba.set_num_threads(th)
            o3, _, _, _ = paths_run(c, npaths, plan=plan)
            thr.append(summarise(o3, plan)["mean"])
        numba.set_num_threads(4)
        out[c["name"]] = {
            "perturb_1e-9m": {"max_abs_db": float(np.max(np.abs(10 * np.log10(s1["total"] / s0["total"])))),
                              "paths_changed": int(np.sum(h1 != h0))},
            "float32_state": {"max_abs_db": float(np.max(np.abs(10 * np.log10(s2["total"] / s0["total"])))),
                              "paths_changed": int(np.sum(h2 != h0))},
            "threads_1_2_4_bit_identical": bool(all(np.array_equal(thr[0], x) for x in thr[1:])),
            "npaths": npaths}
        log(c["name"], out[c["name"]])
    d = load(); d["c5"] = out; save(d)


def step_c6(npaths: int = 32_000, batch: int = 1000, se_target_db: float = 0.083):
    """C6: continuity. Source moved 1 m in 1 cm steps (W1, layout 4 s = 1); W1 uniform room-size sweep ±5 % in
    0.1 % steps (dimensions and positions scaled). Largest step between adjacent points per band at N = 8 000,
    32 000 and under N-2 (prefix batches of `batch` until SE ≤ target), beside AX16's; AX22 jump points excluded."""
    _, l4 = p5.layout_alpha(4)
    base = {"W1": bench_scenes()[0], "layout4_s1": {"dims": (20.0, 30.0, 10.0), "alpha": [[a] * 8 for a in l4],
                                                    "s": [1.0] * 6, "src": (7.0, 20.0, 2.0), "rcv": (10.0, 8.0, 1.7)}}
    sweeps = []
    for k, c in base.items():
        sweeps.append((f"{k}_source_1m", [dict(c, src=(c["src"][0] + 0.01 * i, c["src"][1], c["src"][2])) for i in range(101)]))
    c = base["W1"]
    pts = []
    for i in range(101):
        f = 0.95 + 0.001 * i
        pts.append(dict(c, dims=tuple(f * np.asarray(c["dims"])), src=tuple(f * np.asarray(c["src"])), rcv=tuple(f * np.asarray(c["rcv"]))))
    sweeps.append(("W1_roomsize_pm5pct", pts))
    out = {}
    m = scope6.air_m()
    for name, seq in sweeps:
        vals = {"8000": [], "32000": [], "N2": [], "ax16": [], "fallback": [], "N2_paths": []}
        for c in seq:
            var = rh.variant(c["alpha"], c["s"], m)
            plan = rh.phase04_plan(c["dims"], var, c["src"], c["rcv"])
            o, _, _, _ = paths_run(c, npaths, plan=plan)
            for n in (8000, 32000):
                # prefix of the same deterministic sequence: paths 0..n-1, rescaled to n paths
                vals[str(n)].append((plan["target_specular"] + o[:n].sum(axis=0) * npaths / n).tolist())
            n2 = batch
            while True:
                sub = o[:n2] * npaths / n2
                ss = summarise(sub, plan)
                if np.max(ss["se_db"][list(AQ9)]) <= se_target_db or n2 >= npaths:
                    break
                n2 += batch
            vals["N2"].append(ss["total"].tolist()); vals["N2_paths"].append(n2)
            vals["ax16"].append(plan["target_ax16"].tolist()); vals["fallback"].append(bool(plan["fallback"]))
        res = {"points": len(seq), "fallback_changes": int(np.sum(np.diff(np.asarray(vals["fallback"], int)) != 0)),
               "N2_paths_min_max": [min(vals["N2_paths"]), max(vals["N2_paths"])],
               "N2_changes": int(np.sum(np.diff(vals["N2_paths"]) != 0))}
        ok = ~np.r_[np.diff(np.asarray(vals["fallback"], int)) != 0]
        for key in ("8000", "32000", "N2", "ax16"):
            v = 10 * np.log10(np.asarray(vals[key]))
            st = np.abs(np.diff(v, axis=0))[ok]
            res[f"max_step_db_{key}"] = st.max(axis=0).tolist()
        out[name] = res
        log(name, {k: (np.round(v, 3).tolist() if isinstance(v, list) else v) for k, v in res.items() if k.startswith("max_step") or k.startswith("N2")})
    d = load(); d["c6"] = out; save(d)


def step_c7():
    """C7: ref_hybrid (2.5 m, 8 bands, numpy reference) memory and time for the Phase 04 rooms, W2 and the BRAS
    rooms; independent checks at the 100 m cube: the tracer (N0 = 254 V, seeded, own code) and a coarse ℓ ladder."""
    from tools.acoustics import tracer as tr
    out = {"ref": {}}
    m = scope6.air_m()
    rooms = []
    for r in ("dead_booth", "living_room", "classroom", "club", "concert_hall_box", "stone_box"):
        si = scope6.scene_inputs(REPO / "tests" / "scenes" / "valid" / f"{r}.json")
        rooms.append((r, si["dims"], si["alpha"], si["s"], [(si["src"], si["rcv"])]))
    c = bench_scenes()[2]
    rooms.append(("W2", c["dims"], c["alpha"], c["s"], [(c["src"], c["rcv"]), (bench_scenes()[3]["src"], c["rcv"])]))
    for room in ("CR2", "CR3", "CR4"):
        names = scope6.pair_names(room)
        sis = [scope6.scene_inputs(scope6.rv.SCENES / f"{n}.json") for n in names]
        rooms.append((room, sis[0]["dims"], sis[0]["alpha"], sis[0]["s"], [(x["src"], x["rcv"]) for x in sis]))
    for name, dims, alpha, s, pairs in rooms:
        dims = tuple(float(x) for x in dims)
        var = rh.variant(np.asarray(alpha).reshape(6, 8), np.asarray(s).reshape(-1)[:6] if np.ndim(s) else [s] * 6, m)
        plans = [rh.phase04_plan(dims, var, a_, b_) for a_, b_ in pairs]
        t_end = max(p["mix"]["mixS"] for p in plans) + rh.CROSSFADE_HALF_S + 2e-3
        t0 = time.perf_counter()
        rk = rh.RoomKernel(dims, 2.5, t_end, [var])
        t1 = time.perf_counter()
        inc = np.stack([rh.injection(rk, a_) for a_, _ in pairs]); gat = np.stack([rh.gather_kernel(rk, b_) for _, b_ in pairs])
        env, gens = rh.solve(rk, inc, gat)
        t2 = time.perf_counter()
        out["ref"][name] = {"patches": rk.N, "bins": rk.T, "kernel_gb": rk.K.nbytes / 1e9, "kernel_s": t1 - t0, "solve_s": t2 - t1,
                            "pairs": len(pairs), "generations": int(gens.max())}
        log(name, out["ref"][name])
        del rk, inc, gat, env
    # 100 m: tracer vs (f) on a band-flat cube (α 0.15, s 0.3), and a coarse ℓ ladder 20 / 10 m
    cube = {"dims": (100.0, 100.0, 100.0), "alpha": [[0.15] * 8] * 6, "s": [0.3] * 6, "src": (45.0, 70.0, 2.0), "rcv": (50.0, 30.0, 1.7)}
    var = rh.variant(cube["alpha"], cube["s"], m)
    plan = rh.phase04_plan(cube["dims"], var, cube["src"], cube["rcv"])
    a, b = plan["mix"]["windowStartS"], plan["mix"]["mixS"]
    win = tr.Window(a, b, rh.ENERGY_DECAY_PER_T60 / np.asarray(plan["t60"]), rh.MATCH_NORMALISATION_S / (0.5 * (b - a)))
    t0 = time.perf_counter()
    res, info = tr.trace_with_doubling(cube["dims"], cube["alpha"], cube["s"], m, cube["src"], cube["rcv"], b, window=win, log=log)
    t_tr = time.perf_counter() - t0
    e_tr = win.norm * res.window_s1
    k_tr = res.window_s1 ** 2 / res.window_s2
    o, _, _, _ = paths_run(cube, 128_000, plan=plan)
    s = summarise(o, plan)
    lad = {}
    for sz in (20.0, 10.0):
        c_ = {"dims": cube["dims"], "alpha_faces": [0.15] * 6, "s": 0.3, "src": cube["src"], "rcv": cube["rcv"]}
        env = p5.hybrid_env_factorised(c_, sz, b + rh.CROSSFADE_HALF_S + 2e-3)
        lad[str(sz)] = rh.target_hybrid(plan, env)[list(AQ9)].tolist()
    out["cube100"] = {"mix_s": b, "tracer_n": info["n"], "tracer_s": t_tr, "tracer_k_aq9": k_tr[list(AQ9)].tolist(),
                      "f_vs_tracer_db_aq9": (10 * np.log10(s["total"][list(AQ9)] / e_tr[list(AQ9)])).tolist(),
                      "tracer_se_db_aq9": (4.34 / np.sqrt(k_tr[list(AQ9)])).tolist(), "f_se_db_aq9": s["se_db"][list(AQ9)].tolist(),
                      "ladder_e_target_aq9": lad,
                      "f_vs_ladder10_db_aq9": (10 * np.log10(s["total"][list(AQ9)] / np.asarray(lad["10.0"]))).tolist(),
                      "ladder_change_20_to_10": (np.abs(np.asarray(lad["10.0"]) / np.asarray(lad["20.0"]) - 1)).tolist()}
    log("cube100", out["cube100"])
    d = load(); d["c7"] = out; save(d)


def step_c9b(npaths: int = 8000):
    """C9 (second part): (f) SE in all 8 bands at 8 000 paths for the bench scenes; paths and time per emitter for SE
    0.33 / 0.083 / 0.033 / 0.0145 dB (worst band); process peak RSS."""
    import numba
    out = {"npaths": npaths, "threads": numba.get_num_threads(), "cases": {}}
    for c in bench_scenes():
        paths_run(c, 64)
        t0 = time.perf_counter()
        o, _, plan, M = paths_run(c, npaths)
        dtm = time.perf_counter() - t0
        s = summarise(o, plan)
        worst = float(np.max(s["se_db"]))
        out["cases"][c["name"]] = {"se_db": s["se_db"].tolist(), "ms": 1e3 * dtm,
                                   "paths_for_se": {str(t): _need(npaths, worst, t) for t in SE_TARGETS_DB},
                                   "ms_for_se": {str(t): 1e3 * dtm * _need(npaths, worst, t) / npaths for t in SE_TARGETS_DB},
                                   "image_table_mb": M * 6 * 12 * 8 / 1e6, "worst_band": int(np.argmax(s["se_db"]))}
        log(c["name"], round(worst, 3), out["cases"][c["name"]]["ms_for_se"])
    out["process_peak_rss_mb"] = resource.getrusage(resource.RUSAGE_SELF).ru_maxrss / 1e3
    d = load(); d["c9b"] = out; save(d)

# ------------------------------------------------------------------------------------------
# Near-field remedy prototype (C4 follow-up, RQ-T1-1): (image, hit) pairs closer than r_near, for the listener
# images near the listener, are gathered through the exact solid angle of the hit's wall cell (edge h),
# Ω_cell/(π A_cell), instead of the point kernel cos θ/(π r²) — the MCNP "average flux in a region around
# the detector" idea applied on the wall. Bias: uniform exitance within a near cell (checked by halving h);
# the near-wall score is capped at ≈ Ω/(π A) ≤ 2/h² instead of 1/(π d²).
# ------------------------------------------------------------------------------------------

if njit is not None:

    @njit(parallel=True, fastmath=False, cache=True)
    def mc4(dims, alpha, s, m_air, src, face_pos, face_spec, face_dist, face_cnt, rcv, a, b, rate, norm, npaths, seed,
            r_near, h, ng, near_img, G, out):
        nb = 8
        gam = np.empty(nb)
        for k in range(nb):
            gam[k] = m_air[k] - rate[k] / C
        nimg = near_img.shape[0]
        for p in prange(npaths):
            w = np.empty(nb); contrib = np.zeros(nb); hitf = np.empty(nb)
            x = np.empty(3); d = np.empty(3)
            st = np.uint64(seed) * np.uint64(0x9E3779B97F4A7C15) + np.uint64(p) * np.uint64(0xD1B54A32D192ED03)
            inc = np.uint64(2 * p + 1)
            st, u1 = _next(st, inc); st, u1 = _next(st, inc); st, u2 = _next(st, inc)
            z = 1 - 2 * u1; ph = 2 * np.pi * u2; rr = np.sqrt(max(0.0, 1 - z * z))
            d[0] = rr * np.cos(ph); d[1] = rr * np.sin(ph); d[2] = z
            x[0] = src[0]; x[1] = src[1]; x[2] = src[2]
            for k in range(nb):
                w[k] = 4 * np.pi / npaths
            t = 0.0
            while True:
                tb = 1e300; f = -1
                for ax in range(3):
                    if d[ax] > 1e-15:
                        tt = (dims[ax] - x[ax]) / d[ax]
                        if tt < tb:
                            tb = tt; f = 2 * ax + 1
                    elif d[ax] < -1e-15:
                        tt = -x[ax] / d[ax]
                        if tt < tb:
                            tb = tt; f = 2 * ax
                for i in range(3):
                    x[i] += tb * d[i]
                ax = f // 2
                x[ax] = 0.0 if f % 2 == 0 else dims[ax]
                t += tb / C
                if t >= b:
                    break
                for k in range(nb):
                    w[k] *= np.exp(-m_air[k] * tb)
                sf = s[f]
                if sf > 0:
                    rem = C * (b - t)
                    dx0 = x[0] - rcv[0]; dy0 = x[1] - rcv[1]; dz0 = x[2] - rcv[2]
                    dlr = np.sqrt(dx0 * dx0 + dy0 * dy0 + dz0 * dz0)
                    for k in range(nb):
                        hitf[k] = w[k] * (1 - alpha[f, k]) * sf / np.pi * np.exp(-rate[k] * (b - t))
                    b1 = (ax + 1) % 3; b2 = (ax + 2) % 3
                    ci = int(np.floor((x[b1] - (rcv[b1] - ng * h)) / h)); cj = int(np.floor((x[b2] - (rcv[b2] - ng * h)) / h))
                    incell = ci >= 0 and cj >= 0 and ci < 2 * ng and cj < 2 * ng
                    for m in range(face_cnt[f]):
                        if face_dist[f, m] - dlr > rem:
                            break
                        dx = face_pos[f, m, 0] - x[0]; dy = face_pos[f, m, 1] - x[1]; dz = face_pos[f, m, 2] - x[2]
                        r2 = dx * dx + dy * dy + dz * dz; r = np.sqrt(r2)
                        ta = t + r / C
                        if ta <= a or ta >= b:
                            continue
                        cs = (dx if ax == 0 else (dy if ax == 1 else dz))
                        if f % 2 == 1:
                            cs = -cs
                        cs /= r
                        if cs <= 0:
                            continue
                        hw = np.sin(np.pi * (ta - a) / (b - a)); hw *= hw
                        geo = cs / r2
                        if r < r_near and incell:
                            for q in range(nimg):
                                if abs(near_img[q, 0] - face_pos[f, m, 0]) + abs(near_img[q, 1] - face_pos[f, m, 1]) + abs(near_img[q, 2] - face_pos[f, m, 2]) < 1e-9:
                                    geo = np.pi * G[f, ci, cj, q]  # Ω/(π A) replaces cos/(π r²); hitf already holds 1/π
                                    break
                        g = geo * hw
                        for k in range(nb):
                            contrib[k] += hitf[k] * g * face_spec[f, m, k] * np.exp(-gam[k] * r)
                for k in range(nb):
                    w[k] *= (1 - alpha[f, k])
                st, u = _next(st, inc)
                if u < sf:
                    st, u1 = _next(st, inc); st, u2 = _next(st, inc)
                    ct = np.sqrt(u1); stt = np.sqrt(1 - u1); ph = 2 * np.pi * u2
                    b1 = (ax + 1) % 3; b2 = (ax + 2) % 3
                    d[b1] = stt * np.cos(ph); d[b2] = stt * np.sin(ph); d[ax] = ct if f % 2 == 0 else -ct
                else:
                    d[ax] = -d[ax]
                mx = 0.0
                for k in range(nb):
                    mx = max(mx, w[k])
                if mx == 0.0:
                    break
            for k in range(nb):
                out[p, k] = contrib[k] * norm


def near_field_run(c: dict, npaths: int, h: float, r_near: float = 1.0, seed: int = SEED):
    """(f) with the near-field cell gather: per-path contributions (npaths, 8) and the plan."""
    m = scope6.air_m()
    var = rh.variant(c["alpha"], c["s"], m)
    plan = rh.phase04_plan(c["dims"], var, c["src"], c["rcv"])
    a, b = plan["mix"]["windowStartS"], plan["mix"]["mixS"]
    dims = np.asarray(c["dims"], float)
    rcv = np.asarray(c["rcv"], float)
    fp, fs, fd, fc, M = face_lists(dims, var, c["rcv"], C * b)
    rate = rh.ENERGY_DECAY_PER_T60 / np.asarray(plan["t60"])
    norm = rh.MATCH_NORMALISATION_S / (0.5 * (b - a))
    lat = rh.lattice(tuple(dims), 2 * r_near + 1.0)
    pos = lat.map(rcv)
    near_img = np.ascontiguousarray(pos[np.linalg.norm(pos - rcv, axis=1) < 2 * r_near])
    ng = int(np.ceil(r_near / h)) + 1
    G = np.zeros((6, 2 * ng, 2 * ng, len(near_img)))
    for f in range(6):
        ax = f // 2; a1 = (ax + 1) % 3; a2 = (ax + 2) % 3
        plane = 0.0 if f % 2 == 0 else dims[ax]
        for i in range(2 * ng):
            for j in range(2 * ng):
                u0 = rcv[a1] - ng * h + i * h; v0 = rcv[a2] - ng * h + j * h
                u1, v1 = min(u0 + h, dims[a1]), min(v0 + h, dims[a2]); u0, v0 = max(u0, 0.0), max(v0, 0.0)
                if u1 <= u0 or v1 <= v0:
                    continue
                q = np.zeros((4, 3))
                for k, (uu, vv) in enumerate(((u0, v0), (u1, v0), (u1, v1), (u0, v1))):
                    q[k, ax] = plane; q[k, a1] = uu; q[k, a2] = vv
                area = (u1 - u0) * (v1 - v0)
                for kn, I in enumerate(near_img):
                    front = (I[ax] > plane) if f % 2 == 0 else (I[ax] < plane)
                    if front:
                        G[f, i, j, kn] = rh.solid_angle_quad(I[None], q[None])[0] / (np.pi * area)
    out = np.zeros((npaths, 8))
    mc4(dims, np.asarray(c["alpha"], float).reshape(6, 8), np.asarray(c["s"], float), m, np.asarray(c["src"], float), fp, fs,
        fd, fc, rcv, a, b, rate, norm, npaths, seed, r_near, h, ng, near_img, G, out)
    return out, plan


# ------------------------------------------------------------------------------------------
# C12 (docs/review/phase-05b2/21-decider-decision-T1-T2-T6.md): NW-4C (blend of the emitter-started and the
# listener-started estimator, w = d_L² / (d_L² + d_E²)) and N-3W* (pilot [0, n*), final estimate from the disjoint
# range [n*, n* + N), work cap W_max in image evaluations, R / VOV / slope flagged).
# ------------------------------------------------------------------------------------------

if njit is not None:

    @njit(parallel=True, fastmath=False, cache=True)
    def mc5(dims, alpha, s, m_air, src, face_pos, face_spec, face_dist, face_cnt, rcv, a, b, rate, norm, npaths, p0, wn,
            seed, out, nev):
        """mc3's model and RNG, paths p0 .. p0 + npaths - 1 (path index drives the stream), each weighted 4π / wn;
        nev[p] = image evaluations of the path (inner-loop iterations of the NEE gather)."""
        nb = 8
        gam = np.empty(nb)
        for k in range(nb):
            gam[k] = m_air[k] - rate[k] / C
        for q in prange(npaths):
            p = q + p0
            w = np.empty(nb); contrib = np.zeros(nb); hitf = np.empty(nb)
            x = np.empty(3); d = np.empty(3)
            st = np.uint64(seed) * np.uint64(0x9E3779B97F4A7C15) + np.uint64(p) * np.uint64(0xD1B54A32D192ED03)
            inc = np.uint64(2 * p + 1)
            st, u1 = _next(st, inc); st, u1 = _next(st, inc); st, u2 = _next(st, inc)
            z = 1 - 2 * u1; ph = 2 * np.pi * u2; rr = np.sqrt(max(0.0, 1 - z * z))
            d[0] = rr * np.cos(ph); d[1] = rr * np.sin(ph); d[2] = z
            x[0] = src[0]; x[1] = src[1]; x[2] = src[2]
            for k in range(nb):
                w[k] = 4 * np.pi / wn
            t = 0.0
            ne = 0
            while True:
                tb = 1e300; f = -1
                for ax in range(3):
                    if d[ax] > 1e-15:
                        tt = (dims[ax] - x[ax]) / d[ax]
                        if tt < tb:
                            tb = tt; f = 2 * ax + 1
                    elif d[ax] < -1e-15:
                        tt = -x[ax] / d[ax]
                        if tt < tb:
                            tb = tt; f = 2 * ax
                for i in range(3):
                    x[i] += tb * d[i]
                ax = f // 2
                x[ax] = 0.0 if f % 2 == 0 else dims[ax]
                t += tb / C
                if t >= b:
                    break
                for k in range(nb):
                    w[k] *= np.exp(-m_air[k] * tb)
                sf = s[f]
                if sf > 0:
                    rem = C * (b - t)
                    dx0 = x[0] - rcv[0]; dy0 = x[1] - rcv[1]; dz0 = x[2] - rcv[2]
                    dlr = np.sqrt(dx0 * dx0 + dy0 * dy0 + dz0 * dz0)
                    for k in range(nb):
                        hitf[k] = w[k] * (1 - alpha[f, k]) * sf / np.pi * np.exp(-rate[k] * (b - t))
                    for m in range(face_cnt[f]):
                        if face_dist[f, m] - dlr > rem:
                            break
                        ne += 1
                        dx = face_pos[f, m, 0] - x[0]; dy = face_pos[f, m, 1] - x[1]; dz = face_pos[f, m, 2] - x[2]
                        r2 = dx * dx + dy * dy + dz * dz; r = np.sqrt(r2)
                        ta = t + r / C
                        if ta <= a or ta >= b:
                            continue
                        cs = (dx if ax == 0 else (dy if ax == 1 else dz))
                        if f % 2 == 1:
                            cs = -cs
                        cs /= r
                        if cs <= 0:
                            continue
                        hw = np.sin(np.pi * (ta - a) / (b - a)); hw *= hw
                        g = cs / r2 * hw
                        for k in range(nb):
                            contrib[k] += hitf[k] * g * face_spec[f, m, k] * np.exp(-gam[k] * r)
                for k in range(nb):
                    w[k] *= (1 - alpha[f, k])
                st, u = _next(st, inc)
                if u < sf:
                    st, u1 = _next(st, inc); st, u2 = _next(st, inc)
                    ct = np.sqrt(u1); stt = np.sqrt(1 - u1); ph = 2 * np.pi * u2
                    a1 = (ax + 1) % 3; a2 = (ax + 2) % 3
                    d[a1] = stt * np.cos(ph); d[a2] = stt * np.sin(ph); d[ax] = ct if f % 2 == 0 else -ct
                else:
                    d[ax] = -d[ax]
                mx = 0.0
                for k in range(nb):
                    mx = max(mx, w[k])
                if mx == 0.0:
                    break
            for k in range(nb):
                out[q, k] = contrib[k] * norm
            nev[q] = ne


SEED_REV = SEED + 1  # the listener-started set has its own stream (independent of the emitter-started one)
PILOT = 8000         # N-3W* pilot n* (decider's composed variant; a product choice the seats rate)


def wall_distance(dims, pos) -> float:
    d = np.asarray(dims, float); x = np.asarray(pos, float)
    return float(np.min(np.minimum(x, d - x)))


def nw4c_weight(c: dict) -> float:
    dl, de = wall_distance(c["dims"], c["rcv"]), wall_distance(c["dims"], c["src"])
    return dl * dl / (dl * dl + de * de)


class _Prep:
    """Face lists of both ends and the plan of the true positions, built once per scene."""

    def __init__(self, c: dict, plan=None):
        m = scope6.air_m()
        self.var = rh.variant(c["alpha"], c["s"], m)
        self.plan = rh.phase04_plan(c["dims"], self.var, c["src"], c["rcv"]) if plan is None else plan
        self.a, self.b = self.plan["mix"]["windowStartS"], self.plan["mix"]["mixS"]
        self.dims = np.asarray(c["dims"], float)
        self.fl = {"fwd": face_lists(self.dims, self.var, c["rcv"], C * self.b), "rev": face_lists(self.dims, self.var, c["src"], C * self.b)}
        self.ends = {"fwd": (np.asarray(c["src"], float), np.asarray(c["rcv"], float)), "rev": (np.asarray(c["rcv"], float), np.asarray(c["src"], float))}
        self.rate = rh.ENERGY_DECAY_PER_T60 / np.asarray(self.plan["t60"])
        self.norm = rh.MATCH_NORMALISATION_S / (0.5 * (self.b - self.a))
        self.alpha = np.asarray(c["alpha"], float).reshape(6, 8); self.s = np.asarray(c["s"], float); self.m = m
        self.w = nw4c_weight(c)

    def run(self, end: str, n: int, p0: int = 0, rep: int = 0):
        fp, fs, fd, fc, _ = self.fl[end]
        st, gt = self.ends[end]
        out = np.zeros((n, 8)); nev = np.zeros(n, np.int64)
        if n > 0:
            mc5(self.dims, self.alpha, self.s, self.m, st, fp, fs, fd, fc, gt, self.a, self.b, self.rate, self.norm, n, p0,
                float(n), (SEED if end == "fwd" else SEED_REV) + 2 * rep, out, nev)
        return out, nev

    def nw4c(self, n: int, p0: int = 0, timed: bool = False, rep: int = 0):
        """Per-history NW-4C scores (n, 8): w·fwd_p + (1 − w)·rev_p (histories pair path p of each set)."""
        t0 = time.perf_counter(); of, ef = self.run("fwd", n, p0, rep); t1 = time.perf_counter(); orv, er = self.run("rev", n, p0, rep)
        t2 = time.perf_counter()
        x = self.w * of + (1 - self.w) * orv
        return {"x": x, "fwd": of, "rev": orv, "ev_fwd": ef, "ev_rev": er, "s_fwd": t1 - t0, "s_rev": t2 - t1}


def tally_stats(out: np.ndarray, total_spec: np.ndarray) -> dict:
    """MCNP-style tally checks per band on per-history scores (out sums to the estimate): R = SE/mean of the
    diffuse estimate, VOV, and the slope of the largest scores' tail (1 + Hill index over the top min(200, 5 %))."""
    n = out.shape[0]
    x = out * n
    mu = x.mean(axis=0)
    dev = x - mu
    s2 = (dev ** 2).sum(axis=0); s4 = (dev ** 4).sum(axis=0)
    vov = np.where(s2 > 0, s4 / np.maximum(s2 ** 2, 1e-300) - 1.0 / n, 0.0)
    se = np.sqrt(np.maximum(s2 / n, 0) / n)
    R = np.where(mu > 0, se / np.maximum(mu, 1e-300), 0.0)
    k = max(10, min(200, int(0.05 * n)))
    slope = np.zeros(8)
    for bb in range(8):
        v = np.sort(x[:, bb])[::-1]
        if v[k] <= 0:
            slope[bb] = 0.0; continue
        hill = np.mean(np.log(v[:k] / v[k]))
        slope[bb] = 1.0 + (1.0 / hill if hill > 0 else 1e9)
    return {"R": R.tolist(), "VOV": vov.tolist(), "slope": np.minimum(slope, 10.0).tolist(),
            "R_ok": bool(np.all(R < 0.05)), "VOV_ok": bool(np.all(vov < 0.1)), "slope_ok": bool(np.all(slope > 3.0))}


def n3w(pr: _Prep, w_max: float, se_t: float = 0.083, pilot: int = PILOT) -> dict:
    """N-3W*: pilot [0, n*) sets N from its worst-band SE (dB of the total); the final estimate comes from the disjoint
    range [n*, n* + N); N is capped so that pilot + final image evaluations ≤ w_max (cap hit flagged)."""
    pl = pr.nw4c(pilot)
    sp = summarise(pl["x"], pr.plan)
    worst = float(np.max(sp["se_db"]))
    n_need = _need(pilot, worst, se_t)
    w_pilot = float(pl["ev_fwd"].sum() + pl["ev_rev"].sum())
    ev_pp = w_pilot / pilot
    n_cap = int(max(0, np.floor((w_max - w_pilot) / max(ev_pp, 1e-12))))
    cap_hit = n_need > n_cap
    n = min(n_need, n_cap)
    fin = pr.nw4c(n, p0=pilot) if n > 0 else None
    sf = summarise(fin["x"], pr.plan) if n > 0 else None
    return {"pilot_se_db_worst": worst, "n_need": n_need, "n_cap": n_cap, "n": n, "cap_hit": bool(cap_hit),
            "work_pilot": w_pilot, "work_final": float(fin["ev_fwd"].sum() + fin["ev_rev"].sum()) if n > 0 else 0.0,
            "total": (sf["total"] if n > 0 else np.full(8, np.nan)), "se_db": (sf["se_db"] if n > 0 else np.full(8, np.nan)),
            "pilot_stats": tally_stats(pl["x"], pr.plan["target_specular"]), "ev_per_history": ev_pp}


def c12_scenes() -> dict:
    """(a): C4's cases, both-near cases and Seat 9's absorbing-face cases in W1 and layouts 4 and 5 at s = 1."""
    w1 = {"dims": (20.0, 30.0, 10.0), "alpha": [AQ] * 6, "s": [0.3] * 6}
    rooms = {"W1": w1}
    for L in (4, 5):
        dims, al = p5.layout_alpha(L)
        rooms[f"layout{L}_s1"] = {"dims": dims, "alpha": [[x] * 8 for x in al], "s": [1.0] * 6}
    out = {}
    for rn, base in rooms.items():
        D = base["dims"]
        S0, R0 = (7.0, 20.0, 2.0), (10.0, 8.0, 1.7)
        cases = {"reference_positions": (S0, R0),
                 "listener_wall": (S0, (10.0, 0.1, 1.7)), "listener_edge": (S0, (0.1, 0.1, 1.7)),
                 "listener_corner": (S0, (0.1, 0.1, D[2] - 0.1)),
                 "emitter_wall": ((7.0, D[1] - 0.1, 2.0), R0), "emitter_edge": ((D[0] - 0.1, D[1] - 0.1, 2.0), R0),
                 "emitter_corner": ((D[0] - 0.1, D[1] - 0.1, D[2] - 0.1), R0),
                 "both_wall": ((7.0, D[1] - 0.1, 2.0), (10.0, 0.1, 1.7)),
                 "both_corner": ((D[0] - 0.1, D[1] - 0.1, D[2] - 0.1), (0.1, 0.1, 0.1))}
        out[rn] = {k: dict(base, name=f"{rn}_{k}", src=v[0], rcv=v[1]) for k, v in cases.items()}
    # Seat 9's absorbing-face cases (19 §6): layout 4's floor, layout 5's xMin wall
    out["layout4_s1"]["listener_absorber"] = dict(rooms["layout4_s1"], name="layout4_s1_listener_absorber", src=(7.0, 20.0, 2.0), rcv=(10.0, 8.0, 0.1))
    out["layout5_s1"]["listener_absorber"] = dict(rooms["layout5_s1"], name="layout5_s1_listener_absorber", src=(7.0, 20.0, 2.0), rcv=(0.1, 8.0, 1.7))
    return out


def step_c12a(n: int = 32_000, n_long: int = 256_000, refs: bool = True):
    """(a): NW-4C at n histories (SE, largest share) against a disjoint long NW-4C run and ref_hybrid at 1.25 m (500 Hz–2 kHz)."""
    d = load(); res = d.get("c12", {}).get("a", {})
    for rn, cs in c12_scenes().items():
        for k, c in cs.items():
            key = f"{rn}/{k}"
            if key in res:
                continue
            pr = _Prep(c)
            r = pr.nw4c(n)
            s = summarise(r["x"], pr.plan); sf = summarise(r["fwd"], pr.plan); sr = summarise(r["rev"], pr.plan)
            lg = pr.nw4c(n_long, p0=n)
            sl = summarise(lg["x"], pr.plan)
            row = {"w": pr.w, "d_L": wall_distance(c["dims"], c["rcv"]), "d_E": wall_distance(c["dims"], c["src"]),
                   "se_db": s["se_db"].tolist(), "se_db_fwd_only": sf["se_db"].tolist(), "se_db_rev_only": sr["se_db"].tolist(),
                   "max_share": s["max_path_share"].tolist(), "total": s["total"].tolist(),
                   "long_total": sl["total"].tolist(), "long_se_db": sl["se_db"].tolist(),
                   "vs_long_db": (10 * np.log10(s["total"] / sl["total"])).tolist(),
                   "stats_32k": tally_stats(r["x"], pr.plan["target_specular"]),
                   "s_fwd": r["s_fwd"], "s_rev": r["s_rev"],
                   "ev_per_history": float((r["ev_fwd"].sum() + r["ev_rev"].sum()) / n)}
            if refs:
                ref, _ = _ref_bands(c, (1.25,), AQ9)
                row["ref1.25_aq9"] = [float(ref["1.25"][bb]) for bb in AQ9]
                row["long_vs_ref1.25_db_aq9"] = [float(10 * np.log10(sl["total"][bb] / ref["1.25"][bb])) for bb in AQ9]
                row["long_z_vs_ref_aq9"] = [float((sl["total"][bb] - ref["1.25"][bb]) / max(sl["se_db"][bb] / 4.343 * sl["total"][bb], 1e-300)) for bb in AQ9]
            res[key] = row
            log(key, "w", round(pr.w, 3), "SE", round(max(row["se_db"]), 3), "share", round(max(row["max_share"]), 4),
                "vs long", round(max(np.abs(row["vs_long_db"])), 3), "vs ref", np.round(row.get("long_vs_ref1.25_db_aq9", []), 3))
            d = load(); d.setdefault("c12", {})["a"] = res; save(d)


def step_c12d(threads=(1, 4)):
    """(c), (d), (e): cost per image evaluation, W_max from the restore bound, NW-4C vs forward-only cost to Tol-2 at the
    reference positions, paths allowed, Seat 1's floor, the 3 s bound, cap hits on CS-NW+ and Phase 04 near-wall cases."""
    import numba
    out = {}
    T_BOUND = 30.0 / 14.0           # pluginval watchdog / 14 restores (Challenge 1)
    T_BUILD = (1.51, 1.88)          # Phase 07 restore at 100 m, 96 kHz (BUILD_PLAN §0 row 07)
    ref_scenes = [c for c in bench_scenes() if c["group"] in ("W1", "W2", "CR4", "cube100", "cube100_flutter")]
    # cost per image evaluation, gated scene (100 m cube, both builds' rooms), 1 and 4 threads
    cost = {}
    for th in threads:
        numba.set_num_threads(th)
        for c in [x for x in ref_scenes if x["group"].startswith("cube100")]:
            pr = _Prep(c); pr.run("fwd", 64)
            t0 = time.perf_counter(); o, ev = pr.run("fwd", 8000); dt_ = time.perf_counter() - t0
            cost[f"{c['name']}_t{th}"] = {"s": dt_, "evals": int(ev.sum()), "ns_per_eval": 1e9 * dt_ / max(ev.sum(), 1)}
            log("cost", c["name"], th, cost[f"{c['name']}_t{th}"])
    numba.set_num_threads(max(threads))
    out["cost"] = cost
    ns = max(v["ns_per_eval"] for k, v in cost.items() if k.startswith("cube100_e") and k.endswith(f"_t{max(threads)}"))
    out["ns_per_eval_used"] = ns
    out["restore_bound_s"] = T_BOUND
    out["w_max"] = {str(tb): (T_BOUND - tb) / 2 / (ns * 1e-9) for tb in T_BUILD}
    w_max = out["w_max"][str(T_BUILD[1])]
    out["w_max_used"] = w_max
    out["w_max_seconds_per_emitter_this_box"] = w_max * ns * 1e-9
    log("W_max", out["w_max"])
    # (c) and (e) at the reference positions; paths allowed under W_max
    ref = {}
    for c in ref_scenes:
        pr = _Prep(c)
        pr.run("fwd", 64); pr.run("rev", 64)
        r = pr.nw4c(PILOT, timed=True)
        s = summarise(r["x"], pr.plan); sf = summarise(r["fwd"], pr.plan)
        wf = float(np.max(sf["se_db"])); wc = float(np.max(s["se_db"]))
        nf = _need(PILOT, wf, 0.083); nc = _need(PILOT, wc, 0.083)
        evf = float(r["ev_fwd"].mean()); evc = float((r["ev_fwd"].sum() + r["ev_rev"].sum()) / PILOT)
        ref[c["name"]] = {"w": pr.w, "fwd_se_db_8k": wf, "nw4c_se_db_8k": wc,
                          "fwd_paths_tol2": nf, "nw4c_histories_tol2": nc,
                          "fwd_evals_tol2": nf * evf, "nw4c_evals_tol2": nc * evc,
                          "fwd_s_tol2": r["s_fwd"] * nf / PILOT, "nw4c_s_tol2": (r["s_fwd"] + r["s_rev"]) * nc / PILOT,
                          "cost_ratio_nw4c_over_fwd": (nc * evc) / max(nf * evf, 1e-12),
                          "ev_per_path_fwd": evf, "ev_per_history_nw4c": evc,
                          "paths_allowed_fwd": int(w_max / max(evf, 1e-12)), "histories_allowed_nw4c": int(w_max / max(evc, 1e-12)),
                          "pilot_work_over_w_max": PILOT * evc / w_max,
                          "pilot_stats": tally_stats(r["x"], pr.plan["target_specular"]),
                          "pilot_stats_fwd": tally_stats(r["fwd"], pr.plan["target_specular"])}
        log(c["name"], {k: (round(v, 4) if isinstance(v, float) else v) for k, v in ref[c["name"]].items() if not k.startswith("pilot_stats")})
    out["reference_positions"] = ref
    d = load(); d.setdefault("c12", {})["d"] = out; save(d)
    # cap hits: CS-NW+ (W1) and the six Phase 04 rooms with the listener, then one emitter, at 0.1 m from a wall
    w1 = bench_scenes()[0]
    csnw = {"W1_listener_wall": dict(w1, rcv=(10.0, 0.1, 1.7)), "W1_listener_edge": dict(w1, rcv=(0.1, 0.1, 1.7)),
            "W1_listener_corner": dict(w1, rcv=(0.1, 0.1, 9.9)), "W1_listener_wall_0.3": dict(w1, rcv=(10.0, 0.3, 1.7)),
            "W1_emitter_wall": dict(w1, src=(7.0, 29.9, 2.0))}
    for r_ in ("dead_booth", "living_room", "classroom", "club", "concert_hall_box", "stone_box"):
        si = scope6.scene_inputs(REPO / "tests" / "scenes" / "valid" / f"{r_}.json")
        base = {"dims": si["dims"], "alpha": np.asarray(si["alpha"], float).reshape(6, 8).tolist(), "s": [float(x) for x in si["s"]],
                "src": tuple(float(x) for x in si["src"]), "rcv": tuple(float(x) for x in si["rcv"])}
        for end in ("rcv", "src"):
            x = np.asarray(base[end], float); D = np.asarray(base["dims"], float)
            gaps = np.r_[x, D - x]; i = int(np.argmin(gaps)); ax = i % 3
            x[ax] = 0.1 if i < 3 else D[ax] - 0.1
            csnw[f"{r_}_{'listener' if end == 'rcv' else 'emitter'}_wall"] = dict(base, **{end: tuple(x)})
    caps = {}
    for k, c in csnw.items():
        pr = _Prep(c)
        r = n3w(pr, w_max)
        caps[k] = {"w": pr.w, "n_need": r["n_need"], "n_cap": r["n_cap"], "n": r["n"], "cap_hit": r["cap_hit"],
                   "pilot_se_db_worst": r["pilot_se_db_worst"], "final_se_db_worst": float(np.nanmax(r["se_db"])) if r["n"] > 0 else None,
                   "work_pilot_over_w_max": r["work_pilot"] / w_max, "pilot_stats": r["pilot_stats"],
                   "evals_for_se_0.33": r["work_pilot"] * (r["pilot_se_db_worst"] / 0.33) ** 2,
                   "seat1_floor_met": bool(r["work_pilot"] * (r["pilot_se_db_worst"] / 0.33) ** 2 <= w_max)}
        log(k, {kk: (round(v, 4) if isinstance(v, float) else v) for kk, v in caps[k].items() if kk != "pilot_stats"})
    out["cap_hits"] = caps
    out["cap_hit_rate"] = float(np.mean([v["cap_hit"] for v in caps.values()]))
    d = load(); d.setdefault("c12", {})["d"] = out; save(d)


def step_c12b(w_max: float | None = None, se_t: float = 0.083):
    """(b): 1 cm sweeps under N-3W* at Tol-2 in W1; largest neighbour step per band, N range, cap hits."""
    d = load()
    if w_max is None:
        w_max = d["c12"]["d"]["w_max_used"]
    w1 = bench_scenes()[0]
    sweeps = {
        "listener_off_wall_1.0_to_0.1m": [dict(w1, rcv=(10.0, 1.0 - 0.01 * i, 1.7)) for i in range(91)],
        "listener_along_wall_at_0.1m_1m": [dict(w1, rcv=(10.0 + 0.01 * i, 0.1, 1.7)) for i in range(101)],
        "listener_into_corner_1m_to_0.1m": [dict(w1, rcv=(1.0 - 0.009 * i, 1.0 - 0.009 * i, 1.7)) for i in range(101)],
        # listener held at 0.3 m off the y = 0 wall; the emitter crosses d_E = d_L = 0.3 m (0.6 -> 0.1 m off y = 30)
        "emitter_crossing_dE_eq_dL": [dict(w1, rcv=(10.0, 0.3, 1.7), src=(7.0, 29.4 + 0.01 * i, 2.0)) for i in range(51)],
        "both_off_walls_1.0_to_0.1m": [dict(w1, rcv=(10.0, 1.0 - 0.01 * i, 1.7), src=(7.0, 29.0 + 0.01 * i, 2.0)) for i in range(91)],
    }
    out = {"w_max": w_max, "se_target_db": se_t, "pilot": PILOT, "sweeps": {}}
    for name, seq in sweeps.items():
        tots, ns, caps, ws = [], [], [], []
        for c in seq:
            pr = _Prep(c)
            r = n3w(pr, w_max, se_t)
            tots.append(r["total"]); ns.append(r["n"]); caps.append(r["cap_hit"]); ws.append(pr.w)
        v = 10 * np.log10(np.asarray(tots))
        st = np.abs(np.diff(v, axis=0))
        same_n = np.asarray([ns[i] == ns[i + 1] for i in range(len(ns) - 1)])
        res = {"points": len(seq), "max_step_db": st.max(axis=0).tolist(),
               "max_step_db_same_N": (st[same_n].max(axis=0).tolist() if same_n.any() else None),
               "N_min_max": [int(min(ns)), int(max(ns))], "N_changes": int(np.sum(~same_n)),
               "cap_hits": int(sum(caps)), "w_range": [float(min(ws)), float(max(ws))],
               "worst_step_at": int(np.argmax(st.max(axis=1)))}
        out["sweeps"][name] = res
        log(name, {k: (np.round(x, 3).tolist() if isinstance(x, list) else x) for k, x in res.items()})
        d = load(); d.setdefault("c12", {})["b"] = out; save(d)


# ------------------------------------------------------------------------------------------
# C13 (second seat round, docs/review/phase-05b2/23-seat*-round2-T1-T2.md): N-3W* under the seats' conditions.
#  - W_max at Seat 5's correction: the 1-thread CI pool, the gated set's worst cost per evaluation (flutter cube,
#    42.5 ns), Linux build 1.884 s: 0.1296 s per emitter -> 3.05 M evaluations; 2-thread pool ≈ 5.9 M.
#  - pilot defined in work (Seats 1, 3, 4, 5, 6, 7, 8, 9): n* = min(8 000, ⌊(W_max/2) / e_cal⌋), with e_cal the mean
#    image evaluations per history of a fixed calibration block [0, 256) (sized before the pilot is sampled, Seat 4);
#    pilot floor 1 000 histories (Seats 1, 3): below it the "pilot floor" flag is raised;
#  - final range starts at the fixed index 8 000 (Seat 4) and is disjoint from the pilot (Seat 1);
#    N_final = max(N_need, n*) (Seats 1, 3, 5, 6, 7, 9), capped by the remaining work; cap hit flagged.
# ------------------------------------------------------------------------------------------

W_MAX_1T = 0.1296 / 42.5e-9   # Seat 5 round 2: ≈ 3.05 M
W_MAX_2T = 5.9e6              # Seat 5 round 2: 2-thread pool, ≈ 1.95× scaling
FINAL_START = 8000
CAL = 256


def n3w_c(pr: _Prep, w_max: float, se_t: float = 0.083, n_max: int = PILOT, share: float = 0.5, floor: int = 1000, rep: int = 0) -> dict:
    cal = pr.nw4c(CAL, rep=rep)
    e_cal = float(cal["ev_fwd"].sum() + cal["ev_rev"].sum()) / CAL
    n_star = int(min(n_max, max(CAL, np.floor(share * w_max / max(e_cal, 1e-12)))))
    pl = pr.nw4c(n_star, rep=rep)
    sp = summarise(pl["x"], pr.plan)
    worst = float(np.max(sp["se_db"]))
    n_need = _need(n_star, worst, se_t)
    w_pilot = float(pl["ev_fwd"].sum() + pl["ev_rev"].sum())
    ev_pp = w_pilot / n_star
    n_cap = int(max(0, np.floor((w_max - w_pilot) / max(ev_pp, 1e-12))))
    n_want = max(n_need, n_star)
    n = min(n_want, n_cap)
    fin = pr.nw4c(n, p0=FINAL_START, rep=rep) if n > 0 else None
    sf = summarise(fin["x"], pr.plan) if n > 0 else None
    st = tally_stats(pl["x"], pr.plan["target_specular"])
    return {"n_star": n_star, "e_cal": e_cal, "pilot_floor_flag": bool(n_star < floor), "pilot_se_db_worst": worst,
            "n_need": n_need, "n_cap": n_cap, "n": n, "cap_hit": bool(n_need > n_cap), "min_final_binds": bool(n_star > n_need),
            "work": w_pilot + (float(fin["ev_fwd"].sum() + fin["ev_rev"].sum()) if n > 0 else 0.0),
            "total": (sf["total"] if n > 0 else sp["total"]), "se_db": (sf["se_db"] if n > 0 else sp["se_db"]),
            "empty_final": n == 0, "pilot_R": max(st["R"]), "pilot_VOV": max(st["VOV"]),
            "vov_rule_ok": bool(max(st["VOV"]) < 0.1 or worst <= se_t / 3)}


def _row(r):
    return {k: (v.tolist() if isinstance(v, np.ndarray) else v) for k, v in r.items()}


def c13_scenes() -> dict:
    sc = {}
    for rn, cs in c12_scenes().items():
        for k, c in cs.items():
            sc[f"{rn}/{k}"] = c
    w1 = bench_scenes()[0]
    for dd in (0.3, 0.5):
        sc[f"W1/both_wall_{dd}"] = dict(w1, src=(7.0, 30.0 - dd, 2.0), rcv=(10.0, dd, 1.7))
    for r_ in ("club", "living_room"):
        si = scope6.scene_inputs(REPO / "tests" / "scenes" / "valid" / f"{r_}.json")
        D = tuple(float(x) for x in si["dims"])
        base = {"dims": D, "alpha": np.asarray(si["alpha"], float).reshape(6, 8).tolist(), "s": [float(x) for x in si["s"]]}
        src = np.asarray(si["src"], float); rcv = np.asarray(si["rcv"], float)
        for dd in (0.1, 0.3, 0.5):
            # listener to dd from its nearest wall (x or y), emitter to dd from the opposite wall along y
            r2 = rcv.copy(); s2 = src.copy()
            r2[1] = dd; s2[1] = D[1] - dd
            sc[f"{r_}/both_wall_{dd}"] = dict(base, src=tuple(s2), rcv=tuple(r2))
            r3 = r2.copy(); r3[0] = dd; s3 = s2.copy(); s3[0] = D[0] - dd
            sc[f"{r_}/both_edge_{dd}"] = dict(base, src=tuple(s3), rcv=tuple(r3))
    return sc


def step_c13(reps: int = 30):
    """C13: the conditioned N-3W* at W_max (1-thread) on reference positions, CS-NW+, Phase 04 near-wall cases, C12 (a)'s
    W1/layout 4/5 cases and Seats 3/8's both-near cases; replicates (independent seeds) for the shipped-error spread."""
    d = load()
    out = d.get("c13", {"w_max_1t": W_MAX_1T, "w_max_2t": W_MAX_2T, "cases": {}})
    a = d["c12"]["a"]
    groups = {}
    for c in bench_scenes():
        if c["group"] in ("W1", "W2", "CR4", "cube100", "cube100_flutter"):
            groups[f"ref/{c['name']}"] = c
    for k, c in c13_scenes().items():
        groups[f"nw/{k}"] = c
    for key, c in groups.items():
        if key in out["cases"]:
            continue
        pr = _Prep(c)
        row = {"w": pr.w}
        for wn, wm in (("1t", W_MAX_1T), ("2t", W_MAX_2T)):
            row[wn] = _row(n3w_c(pr, wm))
        nr = reps if key.startswith("nw/") else 0
        if nr:
            tots = np.asarray([n3w_c(pr, W_MAX_1T, rep=1 + i)["total"] for i in range(nr)])
            row["reps_1t_total_1k"] = tots[:, 4].tolist()
            k12 = key[3:]
            if k12 in a:
                ref = a[k12]["ref1.25_aq9"][1]; lng = a[k12]["long_total"][4]
                e = 10 * np.log10(tots[:, 4] / ref)
                row["reps_vs_ref1.25_db"] = {"p5": float(np.percentile(e, 5)), "p50": float(np.median(e)), "p95": float(np.percentile(e, 95)),
                                             "max_abs": float(np.max(np.abs(e)))}
                e2 = 10 * np.log10(tots[:, 4] / lng)
                row["reps_vs_long_db"] = {"p5": float(np.percentile(e2, 5)), "p50": float(np.median(e2)), "p95": float(np.percentile(e2, 95)),
                                          "max_abs": float(np.max(np.abs(e2)))}
            ep = 10 * np.log10(tots[:, 4] / tots[:, 4].mean())
            row["reps_spread_db"] = {"sd": float(np.std(ep)), "p95_abs": float(np.percentile(np.abs(ep), 95)), "max_abs": float(np.max(np.abs(ep)))}
        out["cases"][key] = row
        r1 = row["1t"]
        log(key, "n*", r1["n_star"], "N", r1["n"], "cap", r1["cap_hit"], "SE", round(max(r1["se_db"]), 3), "VOV", round(r1["pilot_VOV"], 3),
            "reps", row.get("reps_vs_ref1.25_db", row.get("reps_spread_db")))
        d = load(); d["c13"] = out; save(d)


def step_c13x():
    """C13 extras: layout 4 emitter-edge rerun on two more disjoint ranges (Seats 1, 3, 6, 9); layout 5 edge/corner
    reference ladder 2.5 -> 1.25 m (Seat 9)."""
    d = load(); out = {}
    sc = c12_scenes()
    c = sc["layout4_s1"]["emitter_edge"]; pr = _Prep(c)
    a = d["c12"]["a"]["layout4_s1/emitter_edge"]
    for name, p0, n in (("range_300k_556k", 300_000, 256_000), ("range_1M_2M", 1_000_000, 1_000_000)):
        r = pr.nw4c(n, p0=p0); s = summarise(r["x"], pr.plan)
        out[f"l4_emitter_edge_{name}"] = {"total_1k": float(s["total"][4]), "se_db": float(s["se_db"][4]),
                                         "vs_32k_db": float(10 * np.log10(a["total"][4] / s["total"][4])),
                                         "vs_long_db": float(10 * np.log10(a["long_total"][4] / s["total"][4])),
                                         "vs_ref1.25_db": float(10 * np.log10(s["total"][4] / a["ref1.25_aq9"][1])),
                                         "max_share": float(s["max_path_share"][4])}
        log(name, out[f"l4_emitter_edge_{name}"])
    lad = {}
    for k in ("listener_edge", "listener_corner", "emitter_edge", "emitter_corner"):
        c = sc["layout5_s1"][k]
        ref, _ = _ref_bands(c, (2.5,), AQ9)
        r125 = d["c12"]["a"][f"layout5_s1/{k}"]["ref1.25_aq9"][1]
        lad[k] = {"ref2.5_1k": float(ref["2.5"][4]), "ref1.25_1k": r125, "change_2.5_to_1.25": float(abs(r125 / ref["2.5"][4] - 1))}
        log("layout5", k, lad[k])
    out["layout5_ladder"] = lad
    d = load(); d["c13x"] = out; save(d)


def step_c13g():
    """C13 (Seat 2): both-near sweep in W1 with the pilot's VOV per point (where VOV crosses 0.1), and the cap-hit rate
    of the conditioned N-3W* (1-thread W_max) on a grid of ordinary positions in W1, club and concert_hall_box."""
    d = load(); out = {}
    w1 = bench_scenes()[0]
    sw = []
    for i in range(19):
        dd = 1.0 - 0.05 * i
        pr = _Prep(dict(w1, rcv=(10.0, dd, 1.7), src=(7.0, 30.0 - dd, 2.0)))
        r = n3w_c(pr, W_MAX_1T)
        sw.append({"d": dd, "pilot_VOV": r["pilot_VOV"], "pilot_se_db": r["pilot_se_db_worst"], "n": r["n"], "cap_hit": r["cap_hit"],
                   "se_db": float(np.max(r["se_db"]))})
        log("both", round(dd, 2), sw[-1])
    out["W1_both_near_vov_sweep"] = sw
    grids = {"W1": w1}
    for r_ in ("club", "concert_hall_box"):
        si = scope6.scene_inputs(REPO / "tests" / "scenes" / "valid" / f"{r_}.json")
        grids[r_] = {"dims": tuple(float(x) for x in si["dims"]), "alpha": np.asarray(si["alpha"], float).reshape(6, 8).tolist(),
                     "s": [float(x) for x in si["s"]], "src": tuple(float(x) for x in si["src"])}
    for gname, base in grids.items():
        D = np.asarray(base["dims"], float)
        rows = []
        for fx in (0.2, 0.5, 0.8):
            for fy in (0.15, 0.35, 0.65, 0.85):
                for zl in (1.2, 1.7):
                    rcv = (fx * D[0], fy * D[1], min(zl, D[2] - 0.3))
                    if np.linalg.norm(np.asarray(rcv) - np.asarray(base["src"])) < 1.0:
                        continue
                    r = n3w_c(_Prep(dict(base, rcv=rcv)), W_MAX_1T)
                    rows.append({"rcv": rcv, "n": r["n"], "n_need": r["n_need"], "cap_hit": r["cap_hit"], "se_db": float(np.max(r["se_db"])),
                                 "pilot_floor_flag": r["pilot_floor_flag"]})
        out[f"grid_{gname}"] = {"points": len(rows), "cap_hits": int(sum(x["cap_hit"] for x in rows)),
                                "max_final_se_db": max(x["se_db"] for x in rows), "rows": rows}
        log("grid", gname, out[f"grid_{gname}"]["points"], out[f"grid_{gname}"]["cap_hits"], round(out[f"grid_{gname}"]["max_final_se_db"], 3))
    d = load(); d["c13g"] = out; save(d)

if __name__ == "__main__":
    main()
