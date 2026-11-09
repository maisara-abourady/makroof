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
    ap.add_argument("step", choices=["agree", "bench", "dense", "openfield"])
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
    else:
        step_openfield()


if __name__ == "__main__":
    main()
