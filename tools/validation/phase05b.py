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


def chunked_solve(rk: rh.RoomKernel, inc: np.ndarray, gath: np.ndarray, v: int = 0, b: int = 0, tol: float = 1e-9,
                  max_generations: int = 2000, chunk: int = 48, workers: int = 4) -> np.ndarray:
    """lean_solve without holding the kernel's transform (phase-05b2 §3 D-T2, R1 for CR4: the 1.25 m kernel is
    5.1 GB per band in float32 and its complex64 transform another 10.2 GB). Each generation transforms the
    kernel again, ``chunk`` emitting patches at a time, and accumulates Y_f = Σ_k K_f[:, l, k] Φ_f[k]. Same
    recursion, same linear convolution and truncation as ref_hybrid.solve / lean_solve: (P, T)."""
    import scipy.fft as sfft
    N, T = rk.N, rk.T
    L = 2 * T
    F = L // 2 + 1
    K = rk.kernel(v, b)  # (N, N, T) view
    D = rk.variants[v].diffuse[rk.bands[b]][rk.p.face]
    phi = D[None, :, None] * inc[:, v, b]
    total = phi.copy()
    e0 = phi.sum()
    for g in range(max_generations):
        Pf = np.transpose(sfft.rfft(phi, n=L, axis=2, workers=workers), (2, 1, 0)).astype(np.complex64)  # (F, N, P)
        Yf = np.zeros((F, N, phi.shape[0]), dtype=np.complex64)
        for k0 in range(0, N, chunk):
            k1 = min(N, k0 + chunk)
            Kc = np.transpose(sfft.rfft(K[k0:k1], n=L, axis=2, workers=workers), (2, 1, 0)).astype(np.complex64)  # (F, l, k)
            Yf += np.matmul(Kc, Pf[:, k0:k1, :])
        y = sfft.irfft(np.transpose(Yf, (2, 1, 0)), n=L, axis=2, workers=workers)[:, :, :T]
        phi = D[None, :, None] * np.maximum(y, 0.0)
        total += phi
        log(f"chunked_solve: generation {g + 1}, emitted {phi.sum():.3e} of {total.sum():.3e}")
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


def step_dtcheck():
    """Interrogator Q3 (ledger P05B-04): is the gated-bin drift between rungs an ℓ effect or the Δt delay
    quantisation (Kuttruff Eq. 4.32, n' = Int(R/cΔt))? Halve Δt at ℓ = 2.5 m (hybrid alone, no comparison)
    in the three s = 1 layouts and compare with the 2.5 -> 1.25 m change."""
    from tools.validation import hybrid_fast
    d = load()
    out = {}
    for name in ("t52_layout4_s1.0", "t52_layout5_s1.0", "t52_layout6_s1.0"):
        c = next(x for x in cases() if x["name"] == name)
        plan = plan_of(c)
        nbg = n_gate_bins(plan)
        gated = d["tracer"]["cases"][name]["gated"]
        vals = {}
        for dt in (1e-3, 5e-4):
            rk = hybrid_fast.FastRoomKernel(c["dims"], PREV_ELL_M, _case_t_end(c), variant_of(c, np.zeros(8)), 3, dt=dt)
            env0 = lean_solve(rk, rh.injection(rk, c["src"])[None], rh.gather_kernel(rk, c["rcv"])[None])[0]
            tb = (np.arange(rk.T) + 0.5) * dt
            env = env0[None] * np.exp(-np.outer(scope6.air_m(), rh.C_SOUND * tb))
            j = np.arange(rk.T) // int(round(BIN_S / dt))
            keep = j < nbg
            dif = np.stack([np.bincount(j[keep], weights=env[b][keep], minlength=nbg)[:nbg] for b in range(8)])
            rb = ism_bins(c["dims"], variant_of(c), c["src"], c["rcv"], plan["mix"]["mixS"] + 0.02, nbg) + dif
            vals[dt] = np.array([rb[b, jj] for b in range(8) for jj in gated[b]])
        out[name] = {"dt_halving_change_at_2.5m": float(np.max(np.abs(vals[5e-4] / vals[1e-3] - 1))),
                     "ell_halving_change_2.5_to_1.25": d["ell"]["steps"][f"{PREV_ELL_M}->{GATE_ELL_M}"]["cases"][name]["gated_bin_change"]}
        log(f"{name}: {out[name]}")
    d["ell"]["dt_check"] = out
    save(d)


# ------------------------------------------------------------------------------------------
# Step 4: gate (A), window-level check, branch, bias trigger
# ------------------------------------------------------------------------------------------


def db(x):
    return float(10 * np.log10(x))


R1_MEMORY_BUDGET_GB = 12.0  # kernel + its complex64 transform on the 15 GB session machine


def step_r1(rooms=None, chunked: bool = False):
    """AX36 (c), R1: E_target (500 Hz-2 kHz) and a* at 2.5 and 1.25 m in the selected BRAS rooms (initial α,
    Phase 05 positions), from the hybrid alone. Per band with the air factored out (exact per band: every
    path's air factor is exp(-m_b R) with R = c t, whatever α and s are). A rung whose dense kernel plus
    transform exceeds R1_MEMORY_BUDGET_GB is recorded as not computed (compute limit)."""
    from tools.validation import hybrid_fast
    d = load()
    m = scope6.air_m()
    out = {"rungs_m": [PREV_ELL_M, GATE_ELL_M], "bands_hz": [500, 1000, 2000], "rooms": {}}
    if rooms is not None and "r1" in d:  # re-run selected rooms, keep the others as committed
        out = d["r1"]
    for room in scope6.bras_rooms():
        if rooms is not None and room not in rooms:
            continue
        names = scope6.pair_names(room)
        sis = {n: scope6.scene_inputs(scope6.rv.SCENES / f"{n}.json") for n in names}
        dims = tuple(float(x) for x in sis[names[0]]["dims"])
        var = rh.variant(sis[names[0]]["alpha"], sis[names[0]]["s"], m)
        var0 = rh.variant(sis[names[0]]["alpha"], sis[names[0]]["s"], np.zeros(8))
        plans = {n: rh.phase04_plan(dims, var, sis[n]["src"], sis[n]["rcv"]) for n in names}
        t_end = max(pl["mix"]["mixS"] for pl in plans.values()) + rh.CROSSFADE_HALF_S + 2e-3
        T = int(np.ceil(t_end / rh.DT))
        r = {"dims": list(dims), "pairs": len(names), "bins": T, "rungs": {}}
        for size in (PREV_ELL_M, GATE_ELL_M):
            p_ = radiosity.box_patches(dims, size)
            N = len(p_.areas)
            need = N * N * T * 4 / 1e9 + N * N * (T + 1) * 8 / 1e9
            a_star = [radiosity.a_star(dims, (1 - var.alpha[:, b])[p_.face], p_) for b in AQ9_IDX]
            rung = {"patches": N, "memory_gb": need, "a_star": a_star}
            # phase-05b2 D-T2 (R1 for CR4): above the dense budget, the chunked solver keeps only the
            # float32 kernel (N²T·4 bytes) and one transformed chunk in memory
            use_chunked = chunked and need > R1_MEMORY_BUDGET_GB and N * N * T * 4 / 1e9 < R1_MEMORY_BUDGET_GB
            if use_chunked:
                rung["solver"] = "chunked (phase-05b2 D-T2)"
                rung["memory_gb_chunked"] = N * N * T * 4 / 1e9
            if need > R1_MEMORY_BUDGET_GB and not use_chunked:
                rung["e_target"] = None
                rung["note"] = f"not computed (compute limit: {need:.1f} GB > {R1_MEMORY_BUDGET_GB} GB)"
                log(f"R1 {room} {size} m: {rung['note']}")
                r["rungs"][str(size)] = rung
                continue
            env = {n: np.zeros((8, T)) for n in names}
            tb = (np.arange(T) + 0.5) * rh.DT
            for b in AQ9_IDX:
                rk = hybrid_fast.FastRoomKernel(dims, size, t_end, var0, b)
                if use_chunked:  # all pairs in one solve: the kernel is transformed once per generation
                    inc = np.stack([rh.injection(rk, sis[n]["src"]) for n in names])
                    gat = np.stack([rh.gather_kernel(rk, sis[n]["rcv"]) for n in names])
                    e_all = chunked_solve(rk, inc, gat)
                    for i, n in enumerate(names):
                        env[n][b] = e_all[i] * np.exp(-m[b] * rh.C_SOUND * tb)
                    del rk, inc, gat
                    continue
                for n in names:
                    e0 = lean_solve(rk, rh.injection(rk, sis[n]["src"])[None], rh.gather_kernel(rk, sis[n]["rcv"])[None])[0]
                    env[n][b] = e0 * np.exp(-m[b] * rh.C_SOUND * tb)
            rung["e_target"] = {n: [float(x) for x in rh.target_hybrid(plans[n], env[n])[list(AQ9_IDX)]] for n in names}
            r["rungs"][str(size)] = rung
            log(f"R1 {room} {size} m: {N} patches done")
        a, b_ = r["rungs"][str(PREV_ELL_M)], r["rungs"][str(GATE_ELL_M)]
        r["a_star_change"] = float(max(abs(x / y - 1) for x, y in zip(a["a_star"], b_["a_star"])))
        if a["e_target"] is not None and b_["e_target"] is not None:
            r["e_target_change"] = float(max(abs(x / y - 1) for n in names for x, y in zip(a["e_target"][n], b_["e_target"][n])))
            r["certified_at_2.5"] = bool(r["e_target_change"] < ELL_TOL and r["a_star_change"] < ELL_TOL)
        else:
            r["e_target_change"] = None
            r["certified_at_2.5"] = None
        out["rooms"][room] = r
        log(f"R1 {room}: E_target change {r['e_target_change']}, a* change {r['a_star_change']:.4%}")
    d["r1"] = out
    save(d)


# AX36 (phase 05b, D1; vetoable by Maisara): the ladder stops at a compute limit (0.625 m does not fit in
# memory), not at the c·Δt floor; scope 0's < 1 % rule is applied per quantity. The window check uses the
# hybrid's E_target, certified at 2.5 m (2.5 -> 1.25 m ≤ 0.324 %) and evaluated at 1.25 m. Gate (A) per bin
# and the scope 5 bias trigger are NOT evaluated (the gated bins converge at no computable rung): no per-bin
# tracer-vs-hybrid number is computed here.
GATE_ELL_M = 1.25
PREV_ELL_M = 2.5
NOT_EVALUATED = "not evaluated (compute limit, AX36)"


def step_gate():
    d = load()
    e_ = d["ell"]
    st = e_["steps"][f"{PREV_ELL_M}->{GATE_ELL_M}"]
    if max(c["target_change"] for c in st["cases"].values()) >= ELL_TOL or max(st["a_star_change"].values()) >= ELL_TOL:
        raise SystemExit("E_target / a* not certified at 2.5 m (AX36 (a)): no window comparison")
    vals = e_["values"]
    out = {"ell_m": GATE_ELL_M, "e_target_certified_at_m": PREV_ELL_M, "gate_A": NOT_EVALUATED,
           "bias_diagnosis": NOT_EVALUATED, "cases": {}}
    for c in cases():
        plan = plan_of(c)
        z = np.load(CACHE / f"tracer_{c['name']}.npz")
        win = window_of(plan)
        e_tr = win.norm * z["s1"]
        k_tr = z["s1"] ** 2 / z["s2"]
        se = 4.34 / np.sqrt(k_tr)
        env_c = factorised_env(c, GATE_ELL_M)
        e_hyb = rh.target_hybrid(plan, env_c)
        e_ax16 = plan["target_ax16"]
        t_prev = np.asarray(vals[c["name"]][f"{PREV_ELL_M}_factorised"]["target"])
        t_here = np.asarray(vals[c["name"]][str(GATE_ELL_M)]["target"])
        wl = {}
        for i, band in zip(AQ9_IDX, (500, 1000, 2000)):
            hv = db(e_hyb[i] / e_tr[i])
            change_db = abs(db(t_here[i] / t_prev[i]))
            margin = WINDOW_DB - abs(hv)
            wl[str(band)] = {"delta_lb_tr_db": db(e_ax16[i] / e_tr[i]), "hybrid_vs_tracer_db": hv,
                             "delta_lb_db": db(e_ax16[i] / e_hyb[i]), "k_tr": float(k_tr[i]), "se_db": float(se[i]),
                             "margin_db": margin, "e_target_change_2.5_to_1.25_db": change_db,
                             "ell_sensitive": bool(abs(margin) < change_db)}
        out["cases"][c["name"]] = {"mix_s": plan["mix"]["mixS"], "fallback": plan["fallback"], "window": wl}
        log(f"{c['name']}: " + "; ".join(f"{k_}: ΔL_tr {v['delta_lb_tr_db']:+.2f} hyb-tr {v['hybrid_vs_tracer_db']:+.2f}"
                                         for k_, v in wl.items()))
    allw = [w for c in out["cases"].values() for w in c["window"].values()]
    window_pass = all(abs(w["hybrid_vs_tracer_db"]) <= WINDOW_DB for w in allw)
    se_ok = all(w["se_db"] <= SE_MAX_DB for w in allw)
    over = any(abs(w["delta_lb_tr_db"]) > WINDOW_DB for w in allw)
    sensitive = any(w["ell_sensitive"] for w in allw)
    xb_over_phase05 = True  # phase 05f X-b: |ΔL_b| > 1 dB in 26 of 345 case-bands (report-phase05.md §6a)
    branch = "(i)" if window_pass and se_ok else "(ii)"
    out["summary"] = {
        "gate_A": NOT_EVALUATED, "bias_diagnosis": NOT_EVALUATED,
        "window_pass": window_pass, "se_ok": se_ok, "any_abs_delta_lb_tr_over_1db": over,
        "any_ell_sensitive": sensitive,
        "max_abs_hybrid_vs_tracer_db": max(abs(w["hybrid_vs_tracer_db"]) for w in allw),
        "max_abs_delta_lb_tr_db": max(abs(w["delta_lb_tr_db"]) for w in allw),
        "max_se_db": max(w["se_db"] for w in allw),
        "branch": branch, "phase05_xb_over_1db": xb_over_phase05,
        # AX36 (c): under (i) the switch is due by scope 4 but waits for R1 (BRAS convergence), R2 (formulation,
        # memory and rebuild cost) and Maisara; meanwhile AX16 records ΔL_b,tr as a known deficit
        "tail_level_switch": ("due, waits for R1/R2/Maisara (AX36 (c))" if branch == "(i)" and (over or xb_over_phase05)
                              else "no (branch (ii): ΔL_b,tr recorded as a known deficit)")}
    d["gate"] = out
    save(d)
    log(json.dumps(out["summary"], indent=1))


OUTER_CASES = ("t52_layout4_s1.0", "t52_layout5_s1.0")  # phase-05b2 D-T5.1 condition (ii)
OUTER_BANDS = (1, 6, 7)  # 125 Hz, 4 kHz, 8 kHz


def step_outer():
    """phase-05b2 decision D-T5.1, condition (ii): the window check of scope 4 outside 500 Hz–2 kHz, before any
    golden is updated. Tracer (same seed and doubling rule as `tracer`) against the hybrid's E_target at the
    certified ℓ = 2.5 m and at 1.25 m (air factored out: exact here, α and s are band-flat in these layouts), at
    125 Hz, 4 kHz and 8 kHz, on Table 5.2 layouts 4 and 5 at s = 1; ±1 dB (B11 window tolerance), SE ≤ 1/3 dB."""
    d = load()
    out = {"bands_hz": [125, 4000, 8000], "tolerance_db": WINDOW_DB,
           "se_max_db": SE_MAX_DB, "cases": {}}
    for name in OUTER_CASES:
        c = next(x for x in cases() if x["name"] == name)
        plan = plan_of(c)
        res, info = run_tracer(c)
        win = window_of(plan)
        e_tr = win.norm * res.window_s1
        k_tr = res.window_s1 ** 2 / res.window_s2
        row = {"tracer_n": info["n"], "doublings": info["doublings"], "bands": {}}
        envs = {size: factorised_env(c, size) for size in (PREV_ELL_M, GATE_ELL_M)}
        for b, hz in zip(OUTER_BANDS, (125, 4000, 8000)):
            e_h = {str(size): float(rh.target_hybrid(plan, env)[b]) for size, env in envs.items()}
            row["bands"][str(hz)] = {
                "hybrid_vs_tracer_db": db(e_h[str(GATE_ELL_M)] / e_tr[b]),
                "hybrid_2.5_vs_tracer_db": db(e_h[str(PREV_ELL_M)] / e_tr[b]),
                "e_target_change_2.5_to_1.25": abs(e_h[str(GATE_ELL_M)] / e_h[str(PREV_ELL_M)] - 1),
                "delta_lb_tr_db": db(plan["target_ax16"][b] / e_tr[b]), "k_tr": float(k_tr[b]),
                "se_db": float(4.34 / np.sqrt(k_tr[b]))}
        out["cases"][name] = row
        log(name, {k: round(v["hybrid_vs_tracer_db"], 3) for k, v in row["bands"].items()})
    allb = [v for c in out["cases"].values() for v in c["bands"].values()]
    out["pass"] = bool(all(abs(v["hybrid_vs_tracer_db"]) <= WINDOW_DB and v["se_db"] <= SE_MAX_DB for v in allb))
    out["max_abs_hybrid_vs_tracer_db"] = max(abs(v["hybrid_vs_tracer_db"]) for v in allb)
    d["outer_bands"] = out
    save(d)


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("step", choices=["tracer", "selfcheck", "ell", "dtcheck", "gate", "r1", "outer"])
    ap.add_argument("--rooms", nargs="*", help="r1 only: re-run these BRAS rooms (others kept as committed)")
    ap.add_argument("--chunked", action="store_true", help="r1 only: chunked solver above the dense memory budget (phase-05b2 D-T2)")
    ap.add_argument("--max-rung", type=int, default=1, help="ell: deepest ladder rung to compute (0 = 5 m ... 3 = 0.625 m)")
    a = ap.parse_args(argv)
    if a.step == "ell":
        step_ell(a.max_rung)
    elif a.step == "r1":
        step_r1(a.rooms, a.chunked)
    else:
        {"tracer": step_tracer, "selfcheck": step_selfcheck, "dtcheck": step_dtcheck, "gate": step_gate, "r1": step_r1,
         "outer": step_outer}[a.step]()


if __name__ == "__main__":
    main()
