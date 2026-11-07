"""Phase 05e scope (e): the phase-05 scope 6 remainder that needs the reference hybrid (AX21).

    python tools/validation/scope6.py hybrid      # deterministic: envelopes, X-b bound ΔL_b (minutes)
    python tools/validation/scope6.py ensembles   # seed-paired ensembles: B11 (B), B10, handover (tens of minutes)
    python tools/validation/scope6.py all

Writes tools/validation/data/phase05_scope6.json (every number the report's scope 6 section prints;
report.py reads it) and caches the diffuse envelopes in build/validation/scope6/ (not committed).

What is computed (phase-05.md scope 6, unchanged; BUILD_PLAN §5 B10, B11; AX16, AX21):

- Reference hybrid (tools/acoustics/ref_hybrid.py) per BRAS pair with broadband s (the scenes,
  AX17) and with BRAS per-band s (B10, tools only), on the initial- and fitted-α scenes (per-band
  s on the initial set only, which is the set AQ9/B11 count; the fitted set is reported). Patches as
  for a* (the a* start size min(dims)/2, at which a* converged to < 1 % in CR2; one halving is run
  as a convergence check where memory allows), time step 1 ms.
- X-b bound ΔL_b = 10·log10(E_target(AX16)/E_target(hybrid)) in the Phase 04 Hann window, per band:
  every BRAS pair; the six Phase 04 test rooms (emitter L); Kuttruff Table 5.2 layouts 2, 4, 5, 6 at
  s = 0.1, 0.25, 0.4, 1 on all faces; the uniform-α (A) s-cases of B11 (α = 0.15, 20×30×10 m,
  s = 0.1, 0.25, 0.4). Synthetic cases use the positions of AX28.
- Seed-paired ensembles (scope 6 "Paired comparisons"): per pair, R tail seeds from the scene's
  tailSeed through three handovers (Phase 04 rule, floors t_dir,e + 80 / 140 ms; `--mix-floor-ms`),
  each with and without the hybrid's diffuse envelope added to the squared band IR before t_mix,e
  (with the ISM crossfade weight), EDT and C80 at 500 Hz, 1 kHz, 2 kHz against the measured IR on the
  run_validation.py path (AX27 admission). Pilot R = 51, then R from the σ₁ rule, re-checked after.
"""

from __future__ import annotations

import argparse
import json
import math
import pathlib
import subprocess
import sys
import tempfile
import time
from concurrent.futures import ProcessPoolExecutor

import numpy as np

HERE = pathlib.Path(__file__).resolve().parent
REPO = HERE.parents[1]
sys.path.insert(0, str(REPO))

from tools.acoustics import bands, metrics, radiosity, render_cli, wav  # noqa: E402
from tools.acoustics import ref_hybrid as rh  # noqa: E402
from tools.validation import run_validation as rv  # noqa: E402

OUT = HERE / "data" / "phase05_scope6.json"
CACHE = REPO / "build" / "validation" / "scope6"
FACES = ("xMin", "xMax", "yMin", "yMax", "floor", "ceiling")
FLOORS_MS = (80.0, 140.0)
FS = rv.FS
AQ9_IDX = (3, 4, 5)  # 500, 1000, 2000 Hz in the octave band order
PHASE04_ROOMS = ("dead_booth", "living_room", "classroom", "club", "concert_hall_box", "stone_box")
S_TABLE52 = (0.1, 0.25, 0.4, 1.0)
S_CASES = (0.1, 0.25, 0.4)
# AX28: positions of the synthetic cases: the AQ10 benchmark room's listener and emitter L
# (tests/unit/test_engine.cpp: listener (10, 8, 1.7), emitter (7, 20, 2) in 20 x 30 x 10 m), scaled per axis
# for the 10 m cube of Table 5.2 layout 2.
AQ10_RCV = np.array([10.0, 8.0, 1.7])
AQ10_SRC = np.array([7.0, 20.0, 2.0])
AQ10_DIMS = np.array([20.0, 30.0, 10.0])
PILOT_R = 51
# The simulator's octave band impulse energies at 44.1 kHz (E_target(render_cli) / E_target(Python),
# tools/acoustics/tests/test_ref_hybrid.py): the AX29 sensitivity arm scales the envelope with these.
SIM_BAND_ENERGY_44K = np.array([0.0039404, 0.00380438, 0.00760878, 0.01521785, 0.03043599, 0.06087664, 0.12175825, 0.73911278])
R_MAX_IN_SESSION = 2000
DELTA = 0.25  # jnd


def log(*a):
    print(*a, flush=True)


def scene_inputs(path: pathlib.Path) -> dict:
    d = json.loads(path.read_text())
    r = d["room"]
    return {"dims": tuple(float(x) for x in r["geometry"]["dimensions"]),
            "alpha": [r["surfaces"][f]["absorption"] for f in FACES],
            "s": [r["surfaces"][f]["scattering"] for f in FACES],
            "src": d["emitters"][0]["position"], "rcv": d["listener"]["position"], "tailSeed": d["render"]["tailSeed"]}


def air_m() -> np.ndarray:
    return rv.air_m()


def bras_rooms() -> list[str]:
    """Every room with validation scenes (bras_mapping.md §1 selection; CR4 since phase-05f)."""
    return sorted({p.stem.split("_")[1].upper() for p in rv.SCENES.glob("bras_*.json")})


def pair_names(room: str) -> list[str]:
    return sorted(p.stem for p in rv.SCENES.glob(f"bras_{room.lower()}_*.json") if not p.stem.endswith("_fitted"))


def t_end_for(dims, pairs) -> float:
    """Long enough for the +140 ms floor's t_mix,e of every pair (plus the crossfade)."""
    V = float(np.prod(dims))
    ends = []
    for src, rcv in pairs:
        t_dir = float(np.linalg.norm(np.subtract(src, rcv)) / rh.C_SOUND)
        ends.append(rh.mixing_time(t_dir, V, FLOORS_MS[-1] * 1e-3)["mixS"])
    return max(ends) + rh.CROSSFADE_HALF_S + 2e-3


# ------------------------------------------------------------------------------------------
# Deterministic part: envelopes and ΔL_b
# ------------------------------------------------------------------------------------------


def _xb(plan, env_vb) -> dict:
    d = rh.delta_lb(plan, env_vb)
    return {"delta_lb_db": [None if not np.isfinite(x) else float(x) for x in d],
            "mix_s": plan["mix"]["mixS"], "fallback": plan["fallback"],
            "target_ax16": plan["target_ax16"].tolist(), "target_hybrid": rh.target_hybrid(plan, env_vb).tolist()}


KERNEL_BUDGET_BYTES = 6e9  # the dense float32 kernel (N² · T · V · 8 bands); above it, one variant at a time


def run_pairs_in_budget(dims, variants, pairs, t_end, size):
    """rh.run_pairs, building the kernel for all variants at once when it fits KERNEL_BUDGET_BYTES and
    one variant at a time otherwise (phase-05f: CR4's three-variant kernel is ≈ 16 GB). The variants
    are independent columns of the kernel (same geometry, own specular factors and air), so the
    envelopes are the same either way."""
    n = len(radiosity.box_patches(tuple(float(x) for x in dims), size).areas)
    T = int(np.ceil(t_end / rh.DT))
    if n * n * T * len(variants) * 8 * 4 <= KERNEL_BUDGET_BYTES:
        return rh.run_pairs(dims, variants, pairs, t_end, size, log=log)
    envs, gens, info = [], [], None
    for k, var in enumerate(variants):
        log(f"kernel above the memory budget ({n} patches, {T} bins): variant {k + 1}/{len(variants)} alone")
        e, i = rh.run_pairs(dims, [var], pairs, t_end, size, log=log)
        envs.append(e)
        gens += i["generations"]
        info = i
    info["generations"] = gens
    info["variants_built_separately"] = True
    return np.concatenate(envs, axis=0), info


def bras_room(room: str, halving: bool) -> dict:
    """Envelopes (cached as npz) and ΔL_b for one BRAS room, three variants."""
    reduction = json.loads(rv.REDUCTION.read_text())[room]["initial"]
    names = pair_names(room)
    sc = {n: scene_inputs(rv.SCENES / f"{n}.json") for n in names}
    scf = {n: scene_inputs(rv.SCENES / f"{n}_fitted.json") for n in names}
    dims = sc[names[0]]["dims"]
    m = air_m()
    s_bands = [reduction["faces"][f]["scattering_bands"] for f in FACES]
    a0, s0 = sc[names[0]]["alpha"], sc[names[0]]["s"]
    for n in names:  # one material set per room and α set (the scenes differ only in positions)
        assert sc[n]["alpha"] == a0 and sc[n]["s"] == s0 and scf[n]["alpha"] == scf[names[0]]["alpha"]
    variants = {"initial": rh.variant(a0, s0, m), "initial_bands_s": rh.variant(a0, s_bands, m),
                "fitted": rh.variant(scf[names[0]]["alpha"], scf[names[0]]["s"], m)}
    pairs = [(sc[n]["src"], sc[n]["rcv"]) for n in names]
    t_end = t_end_for(dims, pairs)
    size = min(dims) / 2  # the a* start size (scope 6: patches as for a*)
    t0 = time.time()
    env, info = run_pairs_in_budget(dims, list(variants.values()), pairs, t_end, size)
    info["seconds"] = time.time() - t0
    log(f"{room}: hybrid {info}")
    CACHE.mkdir(parents=True, exist_ok=True)
    np.savez_compressed(CACHE / f"{room}.npz", env=env, names=np.array(names), variants=np.array(list(variants)))
    out = {"info": info, "dims": list(dims), "variants": list(variants), "pairs": {}}
    for vi, (vk, var) in enumerate(variants.items()):
        for pi, n in enumerate(names):
            plan = rh.phase04_plan(dims, var, *pairs[pi])
            out["pairs"].setdefault(n, {})[vk] = _xb(plan, env[vi, :, pi])
    if halving:  # convergence: one patch halving on the counted variant
        t1 = time.time()
        env2, info2 = rh.run_pairs(dims, [variants["initial"]], pairs, t_end, size / 2, log=log)
        info2["seconds"] = time.time() - t1
        conv = {}
        for pi, n in enumerate(names):
            plan = rh.phase04_plan(dims, variants["initial"], *pairs[pi])
            d1 = rh.delta_lb(plan, env[0, :, pi])
            d2 = rh.delta_lb(plan, env2[0, :, pi])
            e1 = env[0, :, pi].sum(axis=1)
            e2 = env2[0, :, pi].sum(axis=1)
            conv[n] = {"delta_lb_change_db": (d2 - d1).tolist(), "diffuse_energy_change_rel": (e2 / e1 - 1).tolist()}
        out["halving"] = {"info": info2, "pairs": conv}
    return out


def phase04_rooms() -> dict:
    out = {}
    m = air_m()
    for name in PHASE04_ROOMS:
        si = scene_inputs(REPO / "tests" / "scenes" / "valid" / f"{name}.json")
        var = rh.variant(si["alpha"], si["s"], m)
        plan = rh.phase04_plan(si["dims"], var, si["src"], si["rcv"])
        t_end = plan["mix"]["mixS"] + 2e-3
        env, info = rh.run_pairs(si["dims"], [var], [(si["src"], si["rcv"])], t_end, min(si["dims"]) / 2)
        out[name] = _xb(plan, env[0, :, 0]) | {"info": info}
        log(f"{name}: ΔL_b {np.round(out[name]['delta_lb_db'], 2)}")
    return out


def synthetic(dims, alpha_faces, s_values, size) -> dict:
    """ΔL_b for one layout at several uniform s (AX28 positions, AX4 air)."""
    dims = tuple(float(x) for x in dims)
    scale = np.asarray(dims) / AQ10_DIMS
    src, rcv = AQ10_SRC * scale, AQ10_RCV * scale
    m = air_m()
    al = [[a] * 8 for a in alpha_faces]
    vs = [rh.variant(al, [s] * 6, m) for s in s_values]
    plans = [rh.phase04_plan(dims, v, src, rcv) for v in vs]
    t_end = max(p["mix"]["mixS"] for p in plans) + 2e-3
    env, info = rh.run_pairs(dims, vs, [(src, rcv)], t_end, size)
    return {f"s={s}": _xb(plans[i], env[i, :, 0]) for i, s in enumerate(s_values)} | {
        "info": info, "src": src.tolist(), "rcv": rcv.tolist(), "dims": list(dims)}


def table52_and_s_cases() -> dict:
    out = {"table_5_2": {}, "s_cases": None}
    for case, dims, alpha, *_ in radiosity.TABLE_5_2:
        if case not in (2, 4, 5, 6):
            continue
        size = 1.25 if case == 2 else 2.5  # the converged D-B sizes for cases 2 and 4 (< 0.4 % per halving)
        t0 = time.time()
        out["table_5_2"][str(case)] = synthetic(dims, alpha, S_TABLE52, size)
        log(f"Table 5.2 layout {case}: {time.time() - t0:.0f} s; " + "; ".join(
            f"{k}: {np.round(v['delta_lb_db'][3:6], 2)}" for k, v in out["table_5_2"][str(case)].items() if k.startswith("s=")))
    out["s_cases"] = synthetic((20.0, 30.0, 10.0), [0.15] * 6, S_CASES, 2.5)
    log("s-cases: " + "; ".join(f"{k}: {np.round(v['delta_lb_db'][3:6], 2)}" for k, v in out["s_cases"].items() if k.startswith("s=")))
    return out


def xb_reading(res: dict) -> dict:
    """|ΔL_b| <= 1 dB everywhere (every case, 500 Hz-2 kHz) -> X-b accepted (bound recorded in
    AX16); else phase-05b switches tail-level matching to the hybrid's propagated diffuse energy."""
    worst = []

    def scan(label, d):
        for i in AQ9_IDX:
            x = d["delta_lb_db"][i]
            if x is not None:
                worst.append((abs(x), x, label, rv.BANDS[i]))

    for room, r in res["bras"].items():
        for n, vs in r["pairs"].items():
            for vk, d in vs.items():
                scan(f"{n} ({vk})", d)
    for n, d in res["phase04_rooms"].items():
        scan(n, d)
    for case, r in res["synthetic"]["table_5_2"].items():
        for k, d in r.items():
            if k.startswith("s="):
                scan(f"Table 5.2 layout {case}, {k}", d)
    for k, d in res["synthetic"]["s_cases"].items():
        if k.startswith("s="):
            scan(f"s-case {k}", d)
    worst.sort(reverse=True)
    n_over = sum(1 for w in worst if w[0] > 1.0)
    return {"max_abs_db": worst[0][0], "max_case": f"{worst[0][2]} at {worst[0][3]:.0f} Hz ({worst[0][1]:+.2f} dB)",
            "cases_over_1db": n_over, "evaluated": len(worst), "accepted": n_over == 0,
            "top": [{"case": w[2], "band_hz": w[3], "delta_lb_db": w[1]} for w in worst[:12]]}


# ------------------------------------------------------------------------------------------
# Seed-paired ensembles
# ------------------------------------------------------------------------------------------


def _filter_energy(fc: float) -> float:
    """Energy of the analysis octave filter's (zero-phase) impulse response: the factor between a
    band energy in amplitude² units and the squared band IR (scope 6: the envelope is added to the
    squared band IR before the Schroeder integral and C80)."""
    pad = bands._pad_samples(fc, FS)
    x = np.zeros(2 * pad + 1)
    x[pad] = 1.0
    y, _ = bands.filter_band_with_lead(x, FS, fc)
    return float(np.sum(y**2))


def render_ensemble(scene: pathlib.Path, first_seed: int, count: int, floor_ms: float | None) -> np.ndarray:
    with tempfile.TemporaryDirectory() as td:
        out = pathlib.Path(td) / "ens.wav"
        extra = ["--mix-floor-ms", str(floor_ms)] if floor_ms else []
        r = render_cli.run(render_cli.find_render_cli(), "--scene", scene, "--mode", "omni", "--rate", str(FS),
                           "--tail-seed", str(first_seed), "--ensemble", str(count), "--ensemble-emitter", "0",
                           "--ir", out, *extra)
        if r.returncode != 0:
            raise RuntimeError(r.stderr)
        data, fs = wav.read_float32(out)
    assert fs == FS
    return np.asarray(data, dtype=np.float64).T  # (count, n)


def diag(scene: pathlib.Path, floor_ms: float | None) -> dict:
    with tempfile.TemporaryDirectory() as td:
        out = pathlib.Path(td) / "d.json"
        extra = ["--mix-floor-ms", str(floor_ms)] if floor_ms else []
        r = render_cli.run(render_cli.find_render_cli(), "--scene", scene, "--mode", "omni", "--rate", str(FS),
                           "--diagnostics", out, *extra)
        if r.returncode != 0:
            raise RuntimeError(r.stderr)
        return json.loads(out.read_text())


def envelope_samples(env_b: np.ndarray, shift: float, mix_s: float, n: int, scale: float) -> np.ndarray:
    """1 ms bins of emission time -> per-sample energy on the IR's time axis (sample k is emission
    time k/fs + shift), uniform within a bin, weighted by the ISM crossfade weight cos² (equal power,
    AX18; zero after t_mix,e + 2.5 ms), times the analysis filter energy ``scale``."""
    t = np.arange(n) / FS + shift
    b = np.floor(t / rh.DT).astype(np.int64)
    ok = (b >= 0) & (b < env_b.size)
    e = np.zeros(n)
    e[ok] = env_b[b[ok]] / (rh.DT * FS)
    tau = (t - (mix_s - rh.CROSSFADE_HALF_S)) / (2 * rh.CROSSFADE_HALF_S)
    w = np.where(tau <= 0, 1.0, np.where(tau >= 1, 0.0, np.cos(0.5 * np.pi * np.clip(tau, 0, 1)) ** 2))
    return scale * e * w


def edt_c80(h: np.ndarray, adds: dict) -> dict:
    """EDT and C80 at the AQ9 bands of IR h, plain and with each added envelope (name -> (8, n)
    per-sample energies or None); the run_validation path (onset, zero-phase bands with lead, Lundeby,
    AX27 subtraction)."""
    onset = metrics.onset_index(h)
    half = int(round(metrics.DIRECT_HALF_WINDOW_S * FS))
    direct = onset + int(np.argmax(np.abs(h[onset: onset + half + 1])))
    out = {k: {} for k in adds}
    for i in AQ9_IDX:
        fc = rv.BANDS[i]
        y, lead = bands.filter_band_with_lead(h, FS, fc)
        e0 = y**2
        for k, add in adds.items():
            rescale = None
            if isinstance(add, tuple):  # (additive envelope, specular rescale (dbins, bin index, scale))
                add, rescale = add
            e = e0 if add is None else e0 + np.concatenate([np.zeros(lead), add[i][: h.size]])
            if rescale is not None:
                e = rescale_specular(e, lead, h.size, *rescale, i)
            m = metrics._band_metrics(y, FS, onset + lead, direct + lead, energy=e, lead=lead, band_hz=fc,
                                      noise_subtraction=True)
            out[k][bands.band_key(fc)] = (m["EDT"], m["C80"])
    return out


def specular_delta_bins(scene: pathlib.Path, room: str, mix_s: float, T: int) -> np.ndarray:
    """Per band, the specular image energy with BRAS per-band s minus that with the scene's broadband
    s, binned in 1 ms bins of arrival time (amplitude² units) and weighted by the ISM crossfade
    weight cos² (AX18, AX29): (8, T)."""
    si = scene_inputs(scene)
    red = json.loads(rv.REDUCTION.read_text())[room]["initial"]
    s_bands = [red["faces"][f]["scattering_bands"] for f in FACES]
    m = air_m()
    t_max = min(T * rh.DT, mix_s + rh.CROSSFADE_HALF_S)
    eb = rh.image_entries(si["dims"], rh.variant(si["alpha"], si["s"], m), si["src"], si["rcv"], t_max)
    ep = rh.image_entries(si["dims"], rh.variant(si["alpha"], s_bands, m), si["src"], si["rcv"], t_max)
    assert np.array_equal(eb["t"], ep["t"])
    d = ep["spec"] - eb["spec"]  # (8, M)
    tau = (eb["t"] - (mix_s - rh.CROSSFADE_HALF_S)) / (2 * rh.CROSSFADE_HALF_S)
    w = np.where(tau <= 0, 1.0, np.where(tau >= 1, 0.0, np.cos(0.5 * np.pi * np.clip(tau, 0, 1)) ** 2))
    b = np.minimum(np.floor(eb["t"] / rh.DT).astype(np.int64), T - 1)
    out = np.zeros((8, T))
    for k in range(8):
        out[k] = np.bincount(b, weights=d[k] * w, minlength=T)
    return out


def rescale_specular(e: np.ndarray, lead: int, n: int, dbins: np.ndarray, bidx: np.ndarray, scale: np.ndarray,
                     band: int) -> np.ndarray:
    """Scale the band energy of every 1 ms bin by 1 + ΔE_spec/E_bin (≥ 0), so the bin's energy
    changes by the specular difference while staying non-negative."""
    e = e.copy()
    ok = bidx >= 0
    seg = e[lead: lead + n]
    E = np.bincount(bidx[ok], weights=seg[ok], minlength=dbins.shape[1])
    with np.errstate(divide="ignore", invalid="ignore"):
        f = np.where(E > 0, np.maximum(1 + scale[band] * dbins[band] / np.where(E > 0, E, 1), 0.0), 1.0)
    seg[ok] *= f[bidx[ok]]
    return e


def pair_job(args) -> dict:
    """All arms of one pair for seeds [first, first + count)."""
    name, alpha_set, first, count = args
    scene = rv.SCENES / (f"{name}_fitted.json" if alpha_set == "fitted" else f"{name}.json")
    room = name.split("_")[1].upper()
    z = np.load(CACHE / f"{room}.npz")
    names = list(z["names"])
    variants = list(z["variants"])
    env = z["env"]
    pi = names.index(name)
    v_bb = variants.index("fitted" if alpha_set == "fitted" else "initial")
    scale = np.array([_filter_energy(fc) if i in AQ9_IDX else 0.0 for i, fc in enumerate(rv.BANDS)])
    res = {}
    for arm, floor in (("rule", None), ("f80", FLOORS_MS[0]), ("f140", FLOORS_MS[1])):
        dg = diag(scene, floor)
        shift, mix = dg["alignmentShiftS"], dg["emitters"][0]["mixS"]
        irs = render_ensemble(scene, first, count, floor)
        n = irs.shape[1]
        add_bb = np.stack([envelope_samples(env[v_bb, b, pi], shift, mix, n, scale[b]) for b in range(8)])
        adds = {arm: None, arm + "+hyb": add_bb}
        if arm == "rule":  # AX29 sensitivity (reported): the simulator's band energies instead of the analysis filter's
            adds["rule+hyb_simE"] = np.stack([envelope_samples(env[v_bb, b, pi], shift, mix, n, SIM_BAND_ENERGY_44K[b])
                                              for b in range(8)])
        if arm == "rule" and alpha_set == "initial":
            v_pb = variants.index("initial_bands_s")
            add_pb = np.stack([envelope_samples(env[v_pb, b, pi], shift, mix, n, scale[b]) for b in range(8)])
            # The rendered specular part carries the scenes' broadband (1 - s) per hit (AX17); with
            # per-band s it changes too, so the B10 arm rescales each 1 ms bin's early energy by the
            # per-band / broadband specular energy difference (Python image entries), not only adds
            # the per-band-s diffuse envelope (review of PR #12, finding M1).
            dbins = specular_delta_bins(scene, room, mix, env.shape[-1])
            t = np.arange(n) / FS + shift
            bidx = np.where((t >= 0) & (t < env.shape[-1] * rh.DT), np.floor(t / rh.DT), -1).astype(np.int64)
            adds["rule+hyb_bands_s"] = (add_pb, (dbins, bidx, scale))
        per_seed = [edt_c80(h, adds) for h in irs]
        for k in adds:
            res[k] = [ps[k] for ps in per_seed]
        res.setdefault("mix_s", {})[arm] = mix
    return {"name": name, "alpha_set": alpha_set, "first": first, "count": count, "arms": res}


def errors(arm_seeds: list, meas: dict, bands_hz=("500", "1000", "2000")) -> np.ndarray:
    """Per seed AQ9 error in jnd, (R, 2) for EDT and C80: mean over the admitted bands in
    ``bands_hz`` (default the AQ9 bands) of |EDT_sim/EDT_meas - 1|·100/5 and |C80_sim - C80_meas|/1."""
    out = []
    for s in arm_seeds:
        ed, cc = [], []
        for k, (edt, c80) in s.items():
            mb = meas[k]
            if k not in bands_hz or not mb["admitted"]:
                continue
            if edt is not None and mb["EDT"]:
                ed.append(abs(100 * (edt / mb["EDT"] - 1)) / rv.JND["EDT"])
            if c80 is not None and mb["C80"] is not None:
                cc.append(abs(c80 - mb["C80"]) / rv.JND["C80"])
        out.append((np.mean(ed) if ed else np.nan, np.mean(cc) if cc else np.nan))
    return np.array(out)


COMPARISONS = {  # name: (with, base, needs pair-level SE (handover (a)))
    "B11_B": ("rule+hyb", "rule", False),
    "B10": ("rule+hyb_bands_s", "rule+hyb", False),
    "B11_B_simE": ("rule+hyb_simE", "rule", False),  # AX29 sensitivity, reported only
    "handover80_hybrid": ("f80+hyb", "rule+hyb", True),
    "handover140_hybrid": ("f140+hyb", "rule+hyb", True),
    "handover80_phase04": ("f80", "rule", True),
    "handover140_phase04": ("f140", "rule", True),
}


def compare(per_pair: dict, meas: dict, alpha_set: str) -> dict:
    """Paired Δ̂ per comparison: overall (equal room weight), per room, per pair, with SE, σ₁ and the
    R the σ₁ rule asks for (scope 6: R >= max(144 σ₁,Δ², 9 σ₁,Δ,room², 9 σ₁,Δ,pair²))."""
    out = {}
    names = sorted(per_pair)
    rooms = sorted({n.split("_")[1].upper() for n in names})
    for comp, (a, b, pair_level) in COMPARISONS.items():
        if any(a not in per_pair[n] or b not in per_pair[n] for n in names):
            continue
        R = min(len(per_pair[n][a]) for n in names)
        d_pair = {n: errors(per_pair[n][a][:R], meas[n]) - errors(per_pair[n][b][:R], meas[n]) for n in names}  # (R, 2)
        base_pair = {n: errors(per_pair[n][b][:R], meas[n]) for n in names}
        with_pair = {n: errors(per_pair[n][a][:R], meas[n]) for n in names}
        d_room = {rm: np.nanmean(np.stack([d_pair[n] for n in names if n.split("_")[1].upper() == rm]), axis=0) for rm in rooms}
        d_all = np.nanmean(np.stack(list(d_room.values())), axis=0)  # (R, 2)
        res = {"R": R, "metrics": {}}
        for j, met in enumerate(("EDT", "C80")):
            sig = float(np.std(d_all[:, j], ddof=1))
            sig_room = {rm: float(np.std(d_room[rm][:, j], ddof=1)) for rm in rooms}
            sig_pair = {n: float(np.std(d_pair[n][:, j], ddof=1)) for n in names}
            need = 144 * sig**2
            need = max(need, 9 * max(sig_room.values()) ** 2)
            if pair_level:
                need = max(need, 9 * max(sig_pair.values()) ** 2)
            mean_base = {rm: float(np.nanmean([np.nanmean(base_pair[n][:, j]) for n in names if n.split("_")[1].upper() == rm])) for rm in rooms}
            mean_with = {rm: float(np.nanmean([np.nanmean(with_pair[n][:, j]) for n in names if n.split("_")[1].upper() == rm])) for rm in rooms}
            res["metrics"][met] = {
                "delta": float(np.mean(d_all[:, j])), "se": sig / math.sqrt(R), "sigma1": sig,
                "room": {rm: {"delta": float(np.mean(d_room[rm][:, j])), "se": sig_room[rm] / math.sqrt(R),
                              "error_base_jnd": mean_base[rm], "error_with_jnd": mean_with[rm]} for rm in rooms},
                "pair": {n: {"delta": float(np.mean(d_pair[n][:, j])), "se": sig_pair[n] / math.sqrt(R)} for n in names},
                "error_base_jnd": float(np.mean(list(mean_base.values()))), "error_with_jnd": float(np.mean(list(mean_with.values()))),
                "R_needed": int(math.ceil(need)),
            }
        res["R_needed"] = max(res["metrics"][m]["R_needed"] for m in ("EDT", "C80"))
        res["R_ok"] = all(res["metrics"][m]["se"] <= DELTA / 3 + 1e-12
                          and all(r["se"] <= 1 / 3 + 1e-12 for r in res["metrics"][m]["room"].values())
                          and (not pair_level or all(p["se"] <= 1 / 3 + 1e-12 for p in res["metrics"][m]["pair"].values()))
                          for m in ("EDT", "C80"))
        # The 500-1000 Hz mean (the in-range figure: Vorländer Table 6.1 states the jnds for 500-1000 Hz)
        # and the per-band Δ̂ (handover: per band, whether the two handovers differ by > 1 jnd).
        def summary(bands_hz):
            dp = {n: errors(per_pair[n][a][:R], meas[n], bands_hz) - errors(per_pair[n][b][:R], meas[n], bands_hz)
                  for n in names}
            dr = {rm: np.nanmean(np.stack([dp[n] for n in names if n.split("_")[1].upper() == rm]), axis=0) for rm in rooms}
            da = np.nanmean(np.stack(list(dr.values())), axis=0)
            out_ = {}
            for j, met in enumerate(("EDT", "C80")):
                pair_d = {n: float(np.nanmean(dp[n][:, j])) for n in names}
                out_[met] = {"delta": float(np.nanmean(da[:, j])), "se": float(np.nanstd(da[:, j], ddof=1) / math.sqrt(R)),
                             "room": {rm: float(np.nanmean(dr[rm][:, j])) for rm in rooms},
                             "pairs_over_1jnd": sorted(n for n, d in pair_d.items() if abs(d) > 1.0)}
            return out_
        res["in_range_500_1000"] = summary(("500", "1000"))
        res["per_band"] = {k: summary((k,)) for k in ("500", "1000", "2000")}
        res["readings"] = readings(comp, res)
        res["alpha_set"] = alpha_set
        out[comp] = res
    return out


def readings(comp: str, res: dict) -> dict:
    M = res["metrics"]
    if comp == "B11_B":  # not worse: Δ̂ <= +δ for both, no room > +1 jnd
        ok = all(M[m]["delta"] <= DELTA for m in M) and all(r["delta"] <= 1.0 for m in M for r in M[m]["room"].values())
        return {"not_worse": bool(ok and res["R_ok"]), "valid": res["R_ok"]}
    if comp == "B11_B_simE":  # same rule as B11 (B), reported only (AX29 filter-energy sensitivity)
        ok = all(M[m]["delta"] <= DELTA for m in M) and all(r["delta"] <= 1.0 for m in M for r in M[m]["room"].values())
        return {"not_worse": bool(ok and res["R_ok"]), "valid": res["R_ok"], "reported_only": True}
    if comp == "B10":  # B10 moves ahead of 05b if the room-averaged change >= δ or any room's > 1 jnd
        moves = any(abs(M[m]["delta"]) >= DELTA for m in M) or any(abs(r["delta"]) > 1.0 for m in M for r in M[m]["room"].values())
        return {"b10_moves_ahead": bool(moves), "valid": res["R_ok"]}
    if comp.startswith("handover") and comp.endswith("hybrid"):  # (a), (b), (c) on the reference-hybrid IR
        a = any(abs(p["delta"]) > 1.0 for m in M for p in M[m]["pair"].values())
        b = all(M[m]["delta"] <= -DELTA for m in M)
        c = all(r["delta"] <= 1.0 for m in M for r in M[m]["room"].values())
        return {"a_some_pair_moves": bool(a), "b_lowers": bool(b), "c_no_room_worse": bool(c),
                "floor_replaces": bool(a and b and c and res["R_ok"]), "valid": res["R_ok"]}
    a = any(abs(p["delta"]) > 1.0 for m in M for p in M[m]["pair"].values())
    return {"a_some_pair_moves": bool(a), "valid": res["R_ok"], "reported_only": True}


def run_ensembles(alpha_sets=("initial", "fitted"), workers: int = 4) -> dict:
    results = json.loads(rv.RESULTS.read_text())
    out = {}
    for aset in alpha_sets:
        names = [n for room in bras_rooms() for n in pair_names(room)]
        meas = {n: {k: {"EDT": results["pairs"][n + ("_fitted" if aset == "fitted" else "")]["meas"]["bands"][k]["EDT"],
                        "C80": results["pairs"][n + ("_fitted" if aset == "fitted" else "")]["meas"]["bands"][k]["C80"],
                        "admitted": results["pairs"][n + ("_fitted" if aset == "fitted" else "")]["bands"][k]["admitted"]}
                    for k in ("500", "1000", "2000")} for n in names}
        seed0 = {n: scene_inputs(rv.SCENES / f"{n}.json")["tailSeed"] for n in names}
        per_pair: dict = {n: {} for n in names}
        mix: dict = {}
        have = 0
        target = PILOT_R
        history = []
        while have < target:
            jobs = [(n, aset, seed0[n] + have, target - have) for n in names]
            t0 = time.time()
            with ProcessPoolExecutor(workers) as ex:
                for r in ex.map(pair_job, jobs):
                    for k, v in r["arms"].items():
                        if k == "mix_s":
                            mix[r["name"]] = v
                            continue
                        per_pair[r["name"]].setdefault(k, []).extend(v)
            log(f"{aset}: seeds {have}..{target - 1} in {time.time() - t0:.0f} s")
            have = target
            comp = compare(per_pair, meas, aset)
            need = max(c["R_needed"] for c in comp.values())
            history.append({"R": have, "R_needed_max": need, "by_comparison": {k: c["R_needed"] for k, c in comp.items()}})
            log(f"{aset}: R = {have}, R needed per comparison {history[-1]['by_comparison']}")
            if need > have and need <= R_MAX_IN_SESSION:
                target = need
        CACHE.mkdir(parents=True, exist_ok=True)
        (CACHE / f"ensembles_{aset}.json").write_text(json.dumps({"per_pair": per_pair, "meas": meas}, default=float))
        out[aset] = {"comparisons": comp, "R_history": history, "mix_s": mix,
                     "R_beyond_session": need > R_MAX_IN_SESSION}
    return out


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("part", choices=("hybrid", "ensembles", "all"))
    ap.add_argument("--workers", type=int, default=4)
    ap.add_argument("--rooms", nargs="+", default=None,
                    help="hybrid: (re)compute these BRAS rooms only and keep the others from the existing file "
                         "(the envelopes are deterministic); default: every room with scenes")
    a = ap.parse_args(argv)
    res = json.loads(OUT.read_text()) if OUT.exists() else {}
    if a.part in ("hybrid", "all"):
        # The patch-halving convergence check runs on CR2 only: at the halved size the dense kernel of the larger
        # rooms needs ~8x the RAM (CR3: reported in the report; CR4 is larger still).
        keep = {} if a.rooms is None else {k: v for k, v in res.get("bras", {}).items() if k not in a.rooms}
        todo = a.rooms or bras_rooms()
        res["bras"] = dict(sorted({**keep, **{r: bras_room(r, halving=r == "CR2") for r in todo}}.items()))
        res["phase04_rooms"] = phase04_rooms()
        res["synthetic"] = table52_and_s_cases()
        res["xb"] = xb_reading(res)
        OUT.write_text(json.dumps(res, indent=1, default=float) + "\n")
    if a.part in ("ensembles", "all"):
        res["ensembles"] = run_ensembles(workers=a.workers)
        OUT.write_text(json.dumps(res, indent=1, default=float) + "\n")
    log("wrote", OUT)


if __name__ == "__main__":
    main()
