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

from tools.acoustics import radiosity
from tools.acoustics import ref_hybrid as rh
from tools.acoustics import tracer as tr
from tools.validation import scope6

OUT = HERE / "data" / "phase05b.json"
A_STAR_05E = REPO / "tools" / "acoustics" / "data" / "phase05e_a_star.json"
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
    a_star_05e = {c["case"]: c for c in json.loads(A_STAR_05E.read_text())["cases"]}
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
        ref = a_star_05e[case]
        out["s1"][str(case)] = {"T_tracer_s": T, "T_iteration_s": t_it, "T_eyring_s": t_ey, "rel": rel,
                                "pass": bool(abs(rel) <= SELF_S1_REL), "n": SELF_S1_N,
                                # scope 5 diagnosis (reported, no new pass rule): the phase-05e converged a* solver
                                # and its independent Lambert-particle MC (tools/acoustics/data/phase05e_a_star.json);
                                # the iteration column sits 0.6-7.2 % above both (ledger DB-1, open)
                                "T_a_star_05e_s": ref["solver_T60_s"], "T_mc_05e_s": ref["mc"]["T60_s"],
                                "rel_vs_mc_05e": T / ref["mc"]["T60_s"] - 1,
                                "rel_vs_a_star_05e": T / ref["solver_T60_s"] - 1,
                                "column_vs_mc_05e": ref["iteration_column_vs_mc_rel"]}
        log(f"s=1 Table 5.2 case {case}: T {T:.3f} s vs iteration {t_it} s ({rel:+.2%}), vs 05e MC "
            f"{ref['mc']['T60_s']:.3f} s ({T / ref['mc']['T60_s'] - 1:+.2%})")
    out["s1_tolerance_rel"] = SELF_S1_REL
    out["s1_pass_all"] = all(v["pass"] for v in out["s1"].values())
    out["s1_max_abs_rel_vs_mc_05e"] = max(abs(v["rel_vs_mc_05e"]) for v in out["s1"].values())
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


def _case_t_end(c) -> float:
    return plan_of(c)["mix"]["mixS"] + rh.CROSSFADE_HALF_S + 2e-3


def rung_values(c, size, env_c) -> dict:
    """The scope 0 convergence quantities of one case at one rung: full E_target (8,) and the rendered
    energy (ISM specular + hybrid diffuse) in every tracer-gated bin (session brief O4b)."""
    plan = plan_of(c)
    nbg = n_gate_bins(plan)
    rb = rendered_bins(c, plan, env_c, nbg)
    gated = load()["tracer"]["cases"][c["name"]]["gated"]
    return {"target": rh.target_hybrid(plan, env_c).tolist(),
            "gated_bins": [[float(rb[b, j]) for j in gated[b]] for b in range(8)]}


def rung_change(r1: dict, r2: dict) -> dict:
    t1, t2 = np.asarray(r1["target"]), np.asarray(r2["target"])
    ch_t = float(np.max(np.abs(t1[list(AQ9_IDX)] / t2[list(AQ9_IDX)] - 1)))
    gb = [abs(x / y - 1) for b1, b2 in zip(r1["gated_bins"], r2["gated_bins"]) for x, y in zip(b1, b2)]
    return {"target_change": ch_t, "gated_bin_change": float(max(gb)) if gb else 0.0}


def factorised_env(c, size) -> np.ndarray:
    key = CACHE / f"hybrid_fact_{c['name']}_{size}.npz"
    if key.exists():
        return np.load(key)["env"]
    t0 = time.time()
    env = hybrid_env_factorised(c, size, _case_t_end(c))
    log(f"hybrid (air factored) {c['name']} ℓ = {size} m: {time.time() - t0:.0f} s")
    CACHE.mkdir(parents=True, exist_ok=True)
    np.savez(key, env=env)
    return env


def step_ell(max_rung: int = 2):
    """Scope 0 ladder: rungs 0 (5 m) and 1 (2.5 m) with the full reference hybrid (all variants of a
    group at once, as phase 05e); rungs from 1.25 m on, per case with the air factored out (one band
    column, `hybrid_env_factorised`; memory). The 2.5 m rung is recomputed the same way for the
    2.5 -> 1.25 m step and compared with the full run (factorisation check)."""
    d = load()
    groups = {}
    for c in cases():
        groups.setdefault(c["group"], []).append(c)
    result = d.get("ell", {})
    result.update({"ladder_m": list(ELL_LADDER), "tolerance_rel": ELL_TOL, "dt_s": rh.DT})
    vals = result.setdefault("values", {})
    # a* per room layout and rung
    a_star = result.setdefault("a_star", {})
    for g, cs in groups.items():
        dims, alpha = cs[0]["dims"], cs[0]["alpha_faces"]
        for size in ELL_LADDER[: max_rung + 1]:
            if str(size) not in a_star.setdefault(g, {}):
                p = radiosity.box_patches(dims, size)
                a_star[g][str(size)] = radiosity.a_star(dims, (1 - np.asarray(alpha))[p.face], p)
    for size in ELL_LADDER[:2]:
        if all(str(size) in vals.get(c["name"], {}) for c in cases()):
            continue
        for g, cs in groups.items():
            env = hybrid_env(cs, size)
            for vi, c in enumerate(cs):
                vals.setdefault(c["name"], {})[str(size)] = rung_values(c, size, env[vi])
    for size in ELL_LADDER[2: max_rung + 1]:
        for c in cases():
            if str(size) in vals.get(c["name"], {}):
                continue
            vals[c["name"]][str(size)] = rung_values(c, size, factorised_env(c, size))
            if str(ELL_LADDER[1]) + "_factorised" not in vals[c["name"]]:
                vals[c["name"]][str(ELL_LADDER[1]) + "_factorised"] = rung_values(c, ELL_LADDER[1], factorised_env(c, ELL_LADDER[1]))
            d["ell"] = result
            save(d)
    steps = {}
    ell = None
    for j in range(max_rung):
        a, b = ELL_LADDER[j], ELL_LADDER[j + 1]
        if not all(str(b) in vals[c["name"]] for c in cases()):
            break
        ka = str(a) + ("_factorised" if j >= 1 else "")
        per_case = {n: rung_change(v[ka], v[str(b)]) for n, v in vals.items()}
        per_room = {g: abs(a_star[g][str(a)] / a_star[g][str(b)] - 1) for g in groups}
        worst = max([max(x.values()) for x in per_case.values()] + list(per_room.values()))
        steps[f"{a}->{b}"] = {"cases": per_case, "a_star_change": per_room, "max_change": worst, "converged": worst < ELL_TOL}
        log(f"ℓ ladder {a} -> {b} m: max change {worst:.4%}")
        if worst < ELL_TOL:
            ell = a
            break
    if any(str(ELL_LADDER[1]) + "_factorised" in v for v in vals.values()):
        result["factorisation_check_2.5"] = {n: rung_change(v[str(ELL_LADDER[1]) + "_factorised"], v[str(ELL_LADDER[1])])
                                              for n, v in vals.items() if str(ELL_LADDER[1]) + "_factorised" in v}
    result["steps"] = steps
    result["ell_m"] = ell
    result["factorisation"] = {
        "used_from_m": ELL_LADDER[2],
        "kernel": "tools/validation/hybrid_fast.FastRoomKernel (compiled; same terms as ref_hybrid.RoomKernel, "
                  "agreement <= 1e-7 relative, tools/validation/tests/test_hybrid_fast.py)",
        "argument": "rungs from 1.25 m are computed per case with the air factored out (one band column without air, "
                    "then exp(-m_b c t) per 1 ms bin); exact for the continuous model when alpha and s do not depend on "
                    "the band, because every diffuse path's air factor is exp(-m R) with R = c t; the discrete hybrid "
                    "applies air per whole delay bin, so the two differ by the binning (factorisation_check_2.5)",
        "band_flat": {c["name"]: bool(np.all(np.ptp(variant_of(c).alpha, axis=1) == 0)
                                      and np.all(np.ptp(variant_of(c).scattering, axis=1) == 0)) for c in cases()}}
    result.pop("per_group", None)
    result.pop("halving_5_to_2.5_max_change", None)
    d["ell"] = result
    save(d)
    log(f"ℓ = {ell}")


def lean_solve(rk: rh.RoomKernel, inc: np.ndarray, gath: np.ndarray, v: int = 0, b: int = 0, tol: float = 1e-9,
               max_generations: int = 2000, chunk: int = 128) -> np.ndarray:
    """rh.solve for one variant and band with the kernel's FFT built in chunks of patches, in complex64
    (ref_hybrid.solve transforms the whole (N, N, T) kernel at once in complex128, which does not fit in
    memory at ℓ = 1.25 m in the 20 × 30 × 10 m layouts). Same recursion, same truncation: (P, T)."""
    N, T = rk.N, rk.T
    L = 2 * T
    F = L // 2 + 1
    K = rk.kernel(v, b)  # (N, N, T) view
    Kf = np.empty((F, N, N), dtype=np.complex64)  # (F, l, k)
    for k0 in range(0, N, chunk):
        k1 = min(N, k0 + chunk)
        Kf[:, :, k0:k1] = np.transpose(np.fft.rfft(K[k0:k1], n=L, axis=2), (2, 1, 0)).astype(np.complex64)
    D = rk.variants[v].diffuse[rk.bands[b]][rk.p.face]
    phi = D[None, :, None] * inc[:, v, b]
    total = phi.copy()
    e0 = phi.sum()
    for _ in range(max_generations):
        Pf = np.transpose(np.fft.rfft(phi, n=L, axis=2), (2, 1, 0)).astype(np.complex64)  # (F, N, P)
        Yf = np.matmul(Kf, Pf)
        y = np.fft.irfft(np.transpose(Yf, (2, 1, 0)), n=L, axis=2)[:, :, :T]
        phi = D[None, :, None] * np.maximum(y, 0.0)
        total += phi
        if phi.sum() <= tol * max(total.sum(), e0, 1e-300):
            break
    Gf = np.fft.rfft(gath[:, v, b], n=L, axis=2)
    Tf = np.fft.rfft(total, n=L, axis=2)
    return np.maximum(np.fft.irfft((Gf * Tf).sum(axis=1), n=L, axis=1)[:, :T], 0.0)


def hybrid_env_factorised(c, size, t_end) -> np.ndarray:
    """One case's diffuse envelope (8, T) at patch size ``size`` with the air factored out: the hybrid
    run without air in one band column, then exp(−m_b·c·t) per 1 ms bin centre. Exact for the
    continuous model when α and s do not depend on the band (all 15 (A) cases): every diffuse path's
    air factor is exp(−m·R) with R = c·t its arrival time; the discrete hybrid applies air per
    whole delay bin in the kernel, so the two differ by the binning (checked against the full run at
    ℓ = 2.5 m, `factorisation_check` in phase05b.json)."""
    v0 = variant_of(c, np.zeros(8))
    # the compiled kernel (tools/validation/hybrid_fast.py: the same terms as ref_hybrid.RoomKernel, agreement
    # ≤ 1e-7 relative in test_hybrid_fast.py); numba is an offline dependency (requirements-offline.txt)
    from tools.validation import hybrid_fast
    rk = hybrid_fast.FastRoomKernel(c["dims"], size, t_end, v0, 3, log=log)
    inc = rh.injection(rk, c["src"])[None]
    gat = rh.gather_kernel(rk, c["rcv"])[None]
    env0 = lean_solve(rk, inc, gat)[0]  # (T,)
    tb = (np.arange(rk.T) + 0.5) * rh.DT
    return env0[None, :] * np.exp(-np.outer(scope6.air_m(), rh.C_SOUND * tb))


# ------------------------------------------------------------------------------------------
# Step 4: gate (A), window-level check, branch, bias trigger
# ------------------------------------------------------------------------------------------


def db(x):
    return float(10 * np.log10(x))


# AX35 (phase 05b, D1): the ladder stops at a compute limit (0.625 m does not fit in memory), not at the
# c·Δt floor. The window check runs at the finest computed rung, where E_target meets scope 0 (≤ 0.33 %
# per halving); gate (A) is evaluated there too but recorded as "not ℓ-certified" (gated bins up to 5.36 %
# per halving), with the 2.5 m values printed beside it. No residual is credited, the tolerance is unchanged.
GATE_ELL_M = 1.25
PREV_ELL_M = 2.5


def step_gate():
    d = load()
    e_ = d["ell"]
    if e_["ell_m"] is None and GATE_ELL_M not in [float(k.split("->")[1]) for k in e_["steps"]]:
        raise SystemExit("the gate rung was not computed in the ladder (phase05b.json 'ell')")
    ell = e_["ell_m"] if e_["ell_m"] is not None else GATE_ELL_M
    certified = e_["ell_m"] is not None
    out = {"ell_m": ell, "ell_certified_for_gate_A": certified,
           "ell_note": None if certified else "AX35: window check at 1.25 m (E_target meets scope 0); gate (A) not "
                                               "ℓ-certified (scope 0 unmet for the gated bins at 2.5 -> 1.25 m)",
           "cases": {}}
    for c in cases():
        plan = plan_of(c)
        nbg = n_gate_bins(plan)
        z = np.load(CACHE / f"tracer_{c['name']}.npz")
        e, e2 = z["e"][:, :nbg], z["e2"][:, :nbg]
        with np.errstate(divide="ignore", invalid="ignore"):
            k = np.where(e2 > 0, e * e / np.where(e2 > 0, e2, 1), 0.0)
        env_c = factorised_env(c, ell)
        rb = rendered_bins(c, plan, env_c, nbg)
        rb_prev = rendered_bins(c, plan, factorised_env(c, PREV_ELL_M), nbg)
        last_change_db = abs(db(1 + e_["steps"][f"{PREV_ELL_M}->{ell}"]["cases"][c["name"]]["gated_bin_change"])) \
            if not certified else 0.0
        bins = []
        worst = 0.0
        n_gated = []
        for b in range(8):
            gb = np.nonzero(k[b] >= tr.K_GATE)[0]
            n_gated.append(len(gb))
            for j in gb:
                dd = db(rb[b, j] / e[b, j])
                dprev = db(rb_prev[b, j] / e[b, j])
                worst = max(worst, abs(dd))
                sens = (abs(dd) <= GATE_DB) != (abs(dprev) <= GATE_DB) or abs(abs(dd) - GATE_DB) <= last_change_db
                bins.append({"band": b, "bin": int(j), "delta_db": dd, "delta_db_prev_rung": dprev,
                             "ell_sensitive": bool(sens), "k": float(k[b, j]), "sigma_db": 4.34 / np.sqrt(k[b, j])})
        enough = min(n_gated) >= 3
        gate_pass = bool(enough and worst <= GATE_DB)
        win = window_of(plan)
        e_tr = win.norm * z["s1"]
        k_tr = z["s1"] ** 2 / z["s2"]
        se = 4.34 / np.sqrt(k_tr)
        e_hyb = rh.target_hybrid(plan, env_c)
        e_ax16 = plan["target_ax16"]
        wl = {str(rh_b): {"delta_lb_tr_db": db(e_ax16[i] / e_tr[i]), "hybrid_vs_tracer_db": db(e_hyb[i] / e_tr[i]),
                          "delta_lb_db": db(e_ax16[i] / e_hyb[i]), "k_tr": float(k_tr[i]), "se_db": float(se[i])}
              for i, rh_b in zip(AQ9_IDX, (500, 1000, 2000))}
        out["cases"][c["name"]] = {
            "mix_s": plan["mix"]["mixS"], "fallback": plan["fallback"], "gate_bins": nbg, "gated_per_band": n_gated,
            "bins": bins, "max_abs_db": worst, "enough_gated_bins": enough, "gate_A_pass": gate_pass,
            "ell_sensitive_bins": sum(b["ell_sensitive"] for b in bins), "window": wl}
        log(f"{c['name']}: (A) {'pass' if gate_pass else 'FAIL'} max |Δ| {worst:.2f} dB; window "
            + "; ".join(f"{k_}: ΔL_tr {v['delta_lb_tr_db']:+.2f} hyb-tr {v['hybrid_vs_tracer_db']:+.2f}" for k_, v in wl.items()))
    allw = [w for c in out["cases"].values() for w in c["window"].values()]
    window_pass = all(abs(w["hybrid_vs_tracer_db"]) <= WINDOW_DB for w in allw)
    se_ok = all(w["se_db"] <= SE_MAX_DB for w in allw)
    over = any(abs(w["delta_lb_tr_db"]) > WINDOW_DB for w in allw)
    xb_over_phase05 = True  # phase 05e/05f X-b: |ΔL_b| > 1 dB in 26 of 345 case-bands (report-phase05.md §6a)
    if window_pass and se_ok:
        branch = "(i)"
        switch = over or xb_over_phase05
    else:
        branch = "(ii)"
        switch = False
    bias_trigger = any(abs(b["delta_db"]) > BIAS_DIAG_DB for c in out["cases"].values() for b in c["bins"])
    out["summary"] = {
        "gate_A_pass_all": all(c["gate_A_pass"] for c in out["cases"].values()),
        "gate_A_label": "certified" if certified else "not ℓ-certified (AX35)",
        "gate_A_failed_cases": [n for n, c in out["cases"].items() if not c["gate_A_pass"]],
        "window_pass": window_pass, "se_ok": se_ok, "any_abs_delta_lb_tr_over_1db": over,
        "max_abs_hybrid_vs_tracer_db": max(abs(w["hybrid_vs_tracer_db"]) for w in allw),
        "max_abs_delta_lb_tr_db": max(abs(w["delta_lb_tr_db"]) for w in allw),
        "max_se_db": max(w["se_db"] for w in allw),
        "branch": branch, "phase05_xb_over_1db": xb_over_phase05, "tail_level_switch": switch,
        "bias_diagnosis_triggered": bias_trigger}
    d["gate"] = out
    save(d)
    log(json.dumps(out["summary"], indent=1))


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("step", choices=["tracer", "selfcheck", "ell", "gate"])
    ap.add_argument("--max-rung", type=int, default=1, help="ell: deepest ladder rung to compute (0 = 5 m ... 3 = 0.625 m)")
    a = ap.parse_args(argv)
    if a.step == "ell":
        step_ell(a.max_rung)
    else:
        {"tracer": step_tracer, "selfcheck": step_selfcheck, "gate": step_gate}[a.step]()


if __name__ == "__main__":
    main()
