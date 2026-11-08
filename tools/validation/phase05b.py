"""Phase 05b (B11): tracer, patch-size certification, gate (A), window-level check, self-checks.

    python tools/validation/phase05b.py tracer      # tracer runs (statistics only: k, gated bins, N, doublings)
    python tools/validation/phase05b.py selfcheck   # tracer anchors: s = 0 vs ISM, s = 1 vs Table 5.2 T
    python tools/validation/phase05b.py ell         # scope 0 ladder on the reference hybrid alone
    python tools/validation/phase05b.py gate        # gate (A), window-level check, branch (needs ell)

Writes tools/validation/data/phase05b.json (one section per step) and caches tracer and hybrid
arrays in build/validation/phase05b/ (not committed). The order is the plan's: the tracer's own
statistics and the patch size ℓ are committed before any tracer-vs-hybrid number is computed
(phase-05b scope 0, steward G1 of the session brief).

Cases (phase-05b scope 3, BUILD_PLAN §5 B11; positions AX28; AX4 air on both sides):
- s = 0.1, 0.25, 0.4 with α = 0.15 on all faces and bands, 20 × 30 × 10 m;
- Kuttruff Table 5.2 layouts 4, 5, 6 (20 × 30 × 10 m here, one α = 1 face, α = 0 elsewhere) at
  s = 0.1, 0.25, 0.4 and the s = 1 anchor.

Pre-stated reading (session brief O5, fixed before any result): a case has "at least 3 gated bins"
when every one of its 8 bands has ≥ 3 bins with k ≥ 684 among the 10 ms bins [10j, 10j + 10) ms that
end by t_mix,e; the tracer doubles N (B11) until that holds or N = 16 N0.
"""

from __future__ import annotations

import argparse
import json
import pathlib
import sys
import time

import numpy as np

HERE = pathlib.Path(__file__).resolve().parent
REPO = HERE.parents[1]
sys.path.insert(0, str(REPO))

from tools.acoustics import radiosity  # noqa: E402
from tools.acoustics import ref_hybrid as rh  # noqa: E402
from tools.acoustics import tracer as tr  # noqa: E402
from tools.validation import scope6  # noqa: E402

OUT = HERE / "data" / "phase05b.json"
CACHE = REPO / "build" / "validation" / "phase05b"
BIN_S = 0.010  # B11: 10 ms bins
AQ9_IDX = (3, 4, 5)  # 500 Hz, 1 kHz, 2 kHz
ROOM = (20.0, 30.0, 10.0)
S_CASES = (0.1, 0.25, 0.4)
S_TABLE52 = (0.1, 0.25, 0.4, 1.0)
LAYOUTS = (4, 5, 6)
ELL_LADDER = (5.0, 2.5, 1.25, 0.625)  # scope 0: 5·2^-j m down to the last rung above c·Δt = 0.343 m
ELL_TOL = 0.01  # scope 0: < 1 % per halving
GATE_DB = 1.0  # B11 (A): ±1 dB per gated bin
WINDOW_DB = 1.0  # scope 4: hybrid E_target vs tracer within ±1 dB; switch when |ΔL_b,tr| > 1 dB
SE_MAX_DB = 1.0 / 3.0  # scope 4: SE(ΔL_b,tr) = 4.34/√k_tr ≤ threshold/3
BIAS_DIAG_DB = 0.3  # scope 5: diagnose a converged bias above 0.3 dB
BIAS_BUDGET_DB = 0.5  # scope 5: systematic budget
SELF_S0_DB = 0.5  # session brief O4: s = 0, every gated bin within ±0.5 dB of the ISM
SELF_S1_REL = 0.02  # session brief O4: s = 1, decay-fitted T within ±2 % of Table 5.2's iteration T
SELF_S1_N = 400_000
SELF_S1_FIT = (0.1, 2e-3)  # relative room energy range of the late-decay fit (as radiosity.lambert_mc_t60)


def log(*a):
    print(*a, file=sys.stderr, flush=True)


def layout_alpha(case: int):
    for c, dims, alpha, *_ in radiosity.TABLE_5_2:
        if c == case:
            return tuple(float(x) for x in dims), list(alpha)
    raise KeyError(case)


def cases() -> list[dict]:
    out = []
    for s in S_CASES:
        out.append({"name": f"s_case_s{s}", "dims": ROOM, "alpha_faces": [0.15] * 6, "s": s, "group": "s_cases"})
    for L in LAYOUTS:
        dims, alpha = layout_alpha(L)
        for s in S_TABLE52:
            out.append({"name": f"t52_layout{L}_s{s}", "dims": dims, "alpha_faces": alpha, "s": s, "group": f"layout{L}"})
    for c in out:
        scale = np.asarray(c["dims"]) / scope6.AQ10_DIMS
        c["src"], c["rcv"] = (scope6.AQ10_SRC * scale).tolist(), (scope6.AQ10_RCV * scale).tolist()
    return out


def variant_of(c, m=None):
    m = scope6.air_m() if m is None else m
    return rh.variant([[a] * 8 for a in c["alpha_faces"]], [c["s"]] * 6, m)


def plan_of(c):
    return rh.phase04_plan(c["dims"], variant_of(c), c["src"], c["rcv"])


def window_of(plan) -> tr.Window:
    mix = plan["mix"]
    a, b = mix["windowStartS"], mix["mixS"]
    return tr.Window(a, b, rh.ENERGY_DECAY_PER_T60 / np.asarray(plan["t60"]), rh.MATCH_NORMALISATION_S / (0.5 * (b - a)))


def n_gate_bins(plan) -> int:
    return int(np.floor(plan["mix"]["mixS"] / BIN_S + 1e-9))


def load() -> dict:
    return json.loads(OUT.read_text()) if OUT.exists() else {}


def save(d: dict):
    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text(json.dumps(d, indent=1) + "\n")


# ------------------------------------------------------------------------------------------
# Step 1: tracer (statistics only)
# ------------------------------------------------------------------------------------------


def run_tracer(c) -> tuple[tr.TraceResult, dict]:
    plan = plan_of(c)
    res, info = tr.trace_with_doubling(c["dims"], [[a] * 8 for a in c["alpha_faces"]], [c["s"]] * 6, scope6.air_m(),
                                       c["src"], c["rcv"], plan["mix"]["mixS"], window=window_of(plan), log=log)
    return res, info | {"mix_s": plan["mix"]["mixS"], "fallback": plan["fallback"]}


def step_tracer():
    d = load()
    d["tracer"] = {"seed": tr.TRACER_SEED, "r_d_m": tr.R_D, "k_gate": tr.K_GATE, "bin_s": BIN_S, "cases": {}}
    CACHE.mkdir(parents=True, exist_ok=True)
    for c in cases():
        t0 = time.time()
        res, info = run_tracer(c)
        plan = plan_of(c)
        nbg = n_gate_bins(plan)
        gated = res.k[:, :nbg] >= tr.K_GATE
        np.savez(CACHE / f"tracer_{c['name']}.npz", e=res.e, e2=res.e2, s1=res.window_s1, s2=res.window_s2)
        d["tracer"]["cases"][c["name"]] = info | {
            "seconds": round(time.time() - t0, 1), "gate_bins": nbg,
            "gated": [np.nonzero(gated[b])[0].tolist() for b in range(8)],
            "k_window": res.window_k.tolist(),
            "k": [[round(float(x), 1) for x in res.k[b, :nbg]] for b in range(8)]}
        log(f"{c['name']}: N {info['n']} ({info['doublings']} doublings), gated per band {info['gated_bins_per_band']}")
    save(d)


# ------------------------------------------------------------------------------------------
# Step 2: tracer self-checks (scope 5 anchors)
# ------------------------------------------------------------------------------------------


def ism_bins(dims, var, src, rcv, t_max, nb) -> np.ndarray:
    ent = rh.image_entries(dims, var, src, rcv, t_max)
    b = np.floor(ent["t"] / BIN_S).astype(np.int64)
    keep = b < nb
    return np.stack([np.bincount(b[keep], weights=ent["spec"][k][keep], minlength=nb)[:nb] for k in range(8)])


def step_selfcheck():
    d = load()
    out = {"s0": {}, "s1": {}}
    # s = 0: the s-case room, α = 0.15, AX28 positions, AX4 air; ISM energies are exact (Kuttruff §4.1)
    c = dict(cases()[0], s=0.0, name="s0_anchor")
    plan = plan_of(c)
    nbg = n_gate_bins(plan)
    res, info = tr.trace_with_doubling(c["dims"], [[0.15] * 8] * 6, [0.0] * 6, scope6.air_m(), c["src"], c["rcv"],
                                       plan["mix"]["mixS"], log=log)
    ism = ism_bins(c["dims"], variant_of(c), c["src"], c["rcv"], plan["mix"]["mixS"] + 0.02, nbg)
    g = res.k[:, :nbg] >= tr.K_GATE
    with np.errstate(divide="ignore", invalid="ignore"):
        diff = 10 * np.log10(res.e[:, :nbg] / ism)
    dg = np.where(g, diff, np.nan)
    out["s0"] = info | {"gate_bins": nbg, "diff_db_gated": [[None if not np.isfinite(x) else round(float(x), 4) for x in r] for r in dg],
                        "max_abs_db": float(np.nanmax(np.abs(dg))), "mean_db": float(np.nanmean(dg)),
                        "tolerance_db": SELF_S0_DB, "pass": bool(np.nanmax(np.abs(dg)) <= SELF_S0_DB)}
    log(f"s=0 anchor: max |Δ| {out['s0']['max_abs_db']:.3f} dB, mean {out['s0']['mean_db']:+.3f} dB")
    # s = 1: Table 5.2 (no air), room-energy decay of the tracer's particles vs the iteration T
    for case, dims, alpha, t_ey, t_it, _ in radiosity.TABLE_5_2:
        scale = np.asarray(dims) / scope6.AQ10_DIMS
        src = scope6.AQ10_SRC * scale
        rcv = scope6.AQ10_RCV * scale
        t_end = 0.6 * t_it  # −36 dB, beyond the fit's lower end (−27 dB)
        r = tr.trace(dims, alpha, [1.0] * 6, np.zeros(8), src, rcv, SELF_S1_N, t_end=t_end, room_dt=1e-3)
        E = r.room_energy[0] / r.room_energy[0, 0]
        t = np.arange(len(E)) * 1e-3
        sel = (E < SELF_S1_FIT[0]) & (E > SELF_S1_FIT[1])
        slope = np.polyfit(t[sel], np.log(E[sel]), 1)[0]
        T = -np.log(1e6) / slope
        rel = T / t_it - 1
        out["s1"][str(case)] = {"T_tracer_s": T, "T_iteration_s": t_it, "T_eyring_s": t_ey, "rel": rel,
                                "pass": bool(abs(rel) <= SELF_S1_REL), "n": SELF_S1_N}
        log(f"s=1 Table 5.2 case {case}: T {T:.3f} s vs iteration {t_it} s ({rel:+.2%})")
    out["s1_tolerance_rel"] = SELF_S1_REL
    d["selfcheck"] = out
    save(d)


# ------------------------------------------------------------------------------------------
# Step 3: scope 0 ladder (hybrid only)
# ------------------------------------------------------------------------------------------


def hybrid_env(group_cases, size, cache=True) -> np.ndarray:
    """Reference hybrid diffuse envelopes (V, 8, T) for the cases of one group (same room and pair)."""
    key = CACHE / f"hybrid_{group_cases[0]['group']}_{size}.npz"
    if cache and key.exists():
        return np.load(key)["env"]
    c0 = group_cases[0]
    vs = [variant_of(c) for c in group_cases]
    t_end = max(plan_of(c)["mix"]["mixS"] for c in group_cases) + rh.CROSSFADE_HALF_S + 2e-3
    t0 = time.time()
    env, info = scope6.run_pairs_in_budget(c0["dims"], vs, [(c0["src"], c0["rcv"])], t_end, size)
    log(f"hybrid {c0['group']} ℓ = {size} m: {info['patches']} patches, {time.time() - t0:.0f} s")
    env = env[:, :, 0]
    CACHE.mkdir(parents=True, exist_ok=True)
    np.savez(key, env=env)
    return env


def rendered_bins(c, plan, env_c, nb) -> np.ndarray:
    """ISM specular (exact image energies) + hybrid diffuse in 10 ms bins: (8, nb)."""
    spec = ism_bins(c["dims"], variant_of(c), c["src"], c["rcv"], plan["mix"]["mixS"] + 0.02, nb)
    T = env_c.shape[1]
    j = np.arange(T) // int(round(BIN_S / rh.DT))
    keep = j < nb
    dif = np.stack([np.bincount(j[keep], weights=env_c[b][keep], minlength=nb)[:nb] for b in range(8)])
    return spec + dif


def step_ell():
    d = load()
    trc = d["tracer"]["cases"]
    groups = {}
    for c in cases():
        groups.setdefault(c["group"], []).append(c)
    rungs = {}
    a_star = {}
    for gi, (g, cs) in enumerate(groups.items()):
        dims, alpha = cs[0]["dims"], cs[0]["alpha_faces"]
        for size in ELL_LADDER[:2]:
            p = radiosity.box_patches(dims, size)
            a_star.setdefault(g, {})[str(size)] = radiosity.a_star(dims, (1 - np.asarray(alpha))[p.face], p)
    result = {"ladder_m": list(ELL_LADDER), "tolerance_rel": ELL_TOL, "dt_s": rh.DT, "per_group": {}}
    for g, cs in groups.items():
        per = {}
        for size in ELL_LADDER[:2]:
            env = hybrid_env(cs, size)
            for vi, c in enumerate(cs):
                plan = plan_of(c)
                nbg = n_gate_bins(plan)
                rb = rendered_bins(c, plan, env[vi], nbg)
                gated = trc[c["name"]]["gated"]
                per.setdefault(c["name"], {})[str(size)] = {
                    "target": rh.target_hybrid(plan, env[vi]).tolist(),
                    "gated_bins": [[float(rb[b, j]) for j in gated[b]] for b in range(8)]}
        rungs[g] = per
    # one halving 5 -> 2.5 m: max relative change per quantity
    worst = 0.0
    for g, per in rungs.items():
        a5, a25 = a_star[g]["5.0"], a_star[g]["2.5"]
        ch_a = abs(a5 / a25 - 1)
        cases_out = {}
        for n, r in per.items():
            t5, t25 = np.asarray(r["5.0"]["target"]), np.asarray(r["2.5"]["target"])
            ch_t = float(np.max(np.abs(t5[list(AQ9_IDX)] / t25[list(AQ9_IDX)] - 1)))
            gb = [abs(x / y - 1) for b5, b25 in zip(r["5.0"]["gated_bins"], r["2.5"]["gated_bins"]) for x, y in zip(b5, b25)]
            ch_b = float(max(gb)) if gb else 0.0
            cases_out[n] = {"target_change": ch_t, "gated_bin_change": ch_b}
            worst = max(worst, ch_t, ch_b)
        worst = max(worst, ch_a)
        result["per_group"][g] = {"a_star": a_star[g], "a_star_change": ch_a, "cases": cases_out}
    result["halving_5_to_2.5_max_change"] = worst
    result["ell_m"] = 5.0 if worst < ELL_TOL else None
    d["ell"] = result
    save(d)
    log(f"ℓ ladder 5 -> 2.5 m: max change {worst:.4%}; ℓ = {result['ell_m']}")


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("step", choices=["tracer", "selfcheck", "ell", "gate"])
    a = ap.parse_args(argv)
    {"tracer": step_tracer, "selfcheck": step_selfcheck, "ell": step_ell}[a.step]()


if __name__ == "__main__":
    main()
