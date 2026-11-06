"""Phase 05: simulated vs measured (BRAS) omni room IRs, AQ9 evidence, report and nightly baseline.

    python tools/validation/run_validation.py                 # full run: report + plots + results json
    python tools/validation/run_validation.py --sim-only      # simulated metrics only (nightly gate input)

Inputs: the scenes in tests/scenes/validation/ (make_bras_scenes.py), render_cli (RENDER_CLI or
build/{cli,release,debug}/), the BRAS RIRs (fetch_bras.py). Outputs:
- docs/validation/report-phase05.md and docs/validation/phase05/*.png (EDC overlays);
- tools/validation/data/phase05_results.json (every number in the report, for reproducibility);
- the metrics that tests/golden/validation_baseline.json pins (``simulated_metrics``).

Comparison conditions (phase-05 scope 3), identical for simulated and measured IRs: the same
``metrics.room_metrics`` path (onset = first sample of |h|^2 within 20 dB of the broadband
maximum, one t0 for all bands; zero-phase octave filters on the full IR with its lead-in;
Lundeby truncation + compensation; Schroeder integration), the AX23(b) half-octave meter at
1-8 kHz beside it, the BRAS fade (last 1024 samples) dropped from every measured RIR (D6), the
usable-range tests of D7 (peak-referred dynamic range and the Lundeby late line at t0, both
>= 45 dB for T30 and >= 35 dB for T20). Renders at 44.1 kHz (the BRAS rate), emitter L, output 0.
"""

from __future__ import annotations

import argparse
import json
import math
import pathlib
import subprocess
import sys
import tempfile

import numpy as np

HERE = pathlib.Path(__file__).resolve().parent
REPO = HERE.parents[1]
sys.path.insert(0, str(REPO))

from tools.acoustics import air, bands, ensembles, metrics, radiosity, render_cli, wav  # noqa: E402
from tools.acoustics import meter_checks  # noqa: E402
from tools.validation import fetch_bras  # noqa: E402

SCENES = REPO / "tests" / "scenes" / "validation"
RESULTS = HERE / "data" / "phase05_results.json"
REDUCTION = HERE / "data" / "bras_reduction.json"
METER_CHECKS = REPO / "tools" / "acoustics" / "data" / "phase05_meter_checks.json"
REPORT = REPO / "docs" / "validation" / "report-phase05.md"
PLOTS = REPO / "docs" / "validation" / "phase05"
FS = 44100
BANDS = bands.OCTAVE_BANDS_HZ  # 63 ... 8000
AQ9_BANDS = (500.0, 1000.0, 2000.0)
HALF_BANDS = (1000.0, 2000.0, 4000.0, 8000.0)
USABLE = {"T30": 45.0, "T20": 35.0}
JND = {"T": 5.0, "EDT": 5.0, "C80": 1.0}  # % , %, dB (Vorländer Table 6.1; T: working value, AQ9)
AQ9_LIMIT = {"T": 10.0, "EDT": 10.0, "C80": 2.0}
CONDITIONS = {"CR2": (19.5, 41.7), "CR3": (22.4, 40.9), "CR4": (20.9, 37.5)}  # BRAS sheets (F3/F14)


# ------------------------------------------------------------------------------------------
# Analysis (the same for both IRs)
# ------------------------------------------------------------------------------------------


def analyse(h: np.ndarray, fs: float) -> dict:
    """Per-band T30 / T20 / EDT / C80 with the usable-range tests, both meters, and diagnostics."""
    m = metrics.room_metrics(h, fs)
    out = {"onset_s": m["onset_s"], "bands": {}}
    onset = metrics.onset_index(h)
    pre = h[:onset]
    peak = float(np.max(h**2))
    out["pre_onset_max_db"] = float(10 * np.log10(np.max(pre**2) / peak)) if pre.size and np.max(pre**2) > 0 else None
    for fc in BANDS:
        b = m["bands"][bands.band_key(fc)]
        dr, lm = b["dynamic_range_db"], b["line_margin_db"]
        def ok(name):
            need = USABLE[name]
            return (dr is None or dr >= need) and (lm is None or lm >= need)
        row = {"EDT": b["EDT"], "C80": b["C80"], "T30": b["T30"] if ok("T30") else None,
               "T20": b["T20"] if ok("T20") else None, "dynamic_range_db": dr, "line_margin_db": lm,
               "noise_floor_db": b["noise_floor_db"], "crosspoint_s": b["crosspoint_s"]}
        if fc in HALF_BANDS:
            hm = ensembles.band_metrics_half_octave_ensemble(np.asarray(h)[None, :], fs, fc)
            row["T30_half"], row["EDT_half"] = hm["T30"], hm["EDT"]
        # "noise not verified" inputs: mean square of the last 10 % of the band-filtered IR
        y, _ = bands.filter_band_with_lead(h, fs, fc)
        tail = y[int(0.9 * y.size):] ** 2
        row["last10_db"] = float(10 * np.log10(np.mean(tail))) if np.mean(tail) > 0 else None
        out["bands"][bands.band_key(fc)] = row
    out["length_s"] = h.size / fs
    return out


def decay_value(row: dict) -> tuple[float | None, str]:
    """T30 if usable, else T20 (flagged), else None ('not evaluable')."""
    if row["T30"] is not None:
        return row["T30"], "T30"
    if row["T20"] is not None:
        return row["T20"], "T20"
    return None, "none"


def compare_pair(sim: dict, meas: dict) -> dict:
    per_band = {}
    for fc in BANDS:
        k = bands.band_key(fc)
        s, mrow = sim["bands"][k], meas["bands"][k]
        tm, kind = decay_value(mrow)
        ts = s[kind] if kind != "none" else None  # T20 against T20, never against T30
        d = {"kind": kind, "T_meas": tm, "T_sim": ts,
             "T_err_pct": None if tm is None or ts is None else 100 * (ts / tm - 1),
             "EDT_meas": mrow["EDT"], "EDT_sim": s["EDT"],
             "EDT_err_pct": None if not mrow["EDT"] or s["EDT"] is None else 100 * (s["EDT"] / mrow["EDT"] - 1),
             "C80_meas": mrow["C80"], "C80_sim": s["C80"],
             "C80_err_db": None if mrow["C80"] is None or s["C80"] is None else s["C80"] - mrow["C80"]}
        if fc in HALF_BANDS:
            for q in ("T30", "EDT"):
                a, b = s[f"{q}_half"], mrow[f"{q}_half"]
                d[f"{q}_half_err_pct"] = None if a is None or b is None else 100 * (a / b - 1)
            if d["T_err_pct"] is not None and d.get("T30_half_err_pct") is not None:
                d["meter_dependent"] = abs(d["T_err_pct"] - d["T30_half_err_pct"]) > 5.0
        # noise not verified (D6): Lundeby noise vs the last 10 % of the trimmed file
        nf, l10 = mrow["noise_floor_db"], mrow["last10_db"]
        if nf is not None and l10 is not None and mrow["crosspoint_s"] is not None:
            B = np.diff(bands.band_edges_hz(fc))[0]
            t1 = max(meas["length_s"] - mrow["crosspoint_s"], 1e-3)
            t2 = 0.1 * meas["length_s"]
            sig = math.hypot(4.34 / math.sqrt(B * t1), 4.34 / math.sqrt(B * t2))
            d["noise_not_verified"] = abs(nf - l10) > 3 * sig
        d["low_band_BT_lt_16"] = fc <= 125 and tm is not None and 0.71 * fc * tm < 16
        per_band[k] = d
    return per_band


def aq9(per_band: dict, bands_hz=AQ9_BANDS, half=False) -> dict:
    """Mean of the absolute per-band errors (AQ9); None when no band is evaluable."""
    def mean_abs(key, bs):
        v = [abs(per_band[bands.band_key(f)][key]) for f in bs if per_band[bands.band_key(f)][key] is not None]
        return (float(np.mean(v)), len(v)) if v else (None, 0)
    tkey = "T_err_pct"
    res = {}
    for name, key in (("T", tkey), ("EDT", "EDT_err_pct"), ("C80", "C80_err_db")):
        if half and name in ("T", "EDT"):
            q = "T30" if name == "T" else "EDT"
            vals = []
            for f in bands_hz:
                kk = f"{q}_half_err_pct" if f in HALF_BANDS else key
                v = per_band[bands.band_key(f)].get(kk)
                if v is not None:
                    vals.append(abs(v))
            res[name] = float(np.mean(vals)) if vals else None
            res[name + "_n"] = len(vals)
        else:
            res[name], res[name + "_n"] = mean_abs(key, bands_hz)
    res["pass"] = {n: (None if res[n] is None else res[n] <= AQ9_LIMIT[n]) for n in ("T", "EDT", "C80")}
    res["jnd"] = {n: (None if res[n] is None else res[n] / JND[n]) for n in ("T", "EDT", "C80")}
    return res


# ------------------------------------------------------------------------------------------
# Rendering and data
# ------------------------------------------------------------------------------------------


def render(binary, scene_path: pathlib.Path, extra=()) -> np.ndarray:
    with tempfile.TemporaryDirectory() as td:
        out = pathlib.Path(td) / "ir.wav"
        r = render_cli.run(binary, "--scene", scene_path, "--mode", "omni", "--rate", str(FS), "--ir", out, *extra)
        if r.returncode != 0:
            raise RuntimeError(f"render_cli failed for {scene_path.name}: {r.stderr}")
        data, fs = wav.read_float32(out)
    assert fs == FS
    return np.asarray(data[:, 0], dtype=np.float64)


def diagnostics(binary, scene_path: pathlib.Path) -> dict:
    with tempfile.TemporaryDirectory() as td:
        out = pathlib.Path(td) / "d.json"
        r = render_cli.run(binary, "--scene", scene_path, "--mode", "omni", "--rate", str(FS), "--diagnostics", out)
        if r.returncode != 0:
            raise RuntimeError(r.stderr)
        return json.loads(out.read_text())


def measured(cache: pathlib.Path, room: str, src: str, rcv: str) -> np.ndarray:
    h, fs = wav.read(cache / room / "rirs" / f"{room}_RIR_{src}_{rcv}_Dodecahedron.wav")
    assert fs == FS, fs
    h = np.asarray(h, dtype=np.float64)
    if h.ndim > 1:
        h = h[:, 0]
    return meter_checks.trim_bras_fade(h)


def scene_list():
    out = []
    for p in sorted(SCENES.glob("bras_*.json")):
        parts = p.stem.split("_")
        room, src, rcv = parts[1].upper(), parts[2].upper(), parts[3].upper()
        alpha_set = "fitted" if p.stem.endswith("_fitted") else "initial"
        out.append({"path": p, "room": room, "src": src, "rcv": rcv, "alpha_set": alpha_set, "name": p.stem})
    return out


def simulated_metrics(binary) -> dict:
    """What the nightly gate pins: per scene and band, the simulated T30/T20/EDT/C80 (octave) and
    T30/EDT on the half-octave meter (1-8 kHz)."""
    out = {}
    for sc in scene_list():
        a = analyse(render(binary, sc["path"]), FS)
        out[sc["name"]] = {k: {q: v[q] for q in ("T30", "T20", "EDT", "C80", "T30_half", "EDT_half") if q in v}
                           for k, v in a["bands"].items()}
    return out


# ------------------------------------------------------------------------------------------
# Room-level quantities
# ------------------------------------------------------------------------------------------


def neighbour_ratio(T: dict, fc: float) -> float | None:
    i = BANDS.index(fc)
    t = T.get(fc)
    nbs = [T.get(BANDS[j]) for j in (i - 1, i + 1) if 0 <= j < len(BANDS)]
    nbs = [x for x in nbs if x]
    if not t or not nbs:
        return None
    return max(nbs) / t


def predictors(red: dict, m_air: np.ndarray) -> dict:
    """Eyring, a* (converged) and γ²-Eyring for the reduced box, per band (phase-05 scope 6)."""
    d = red["dims"]
    dims = (d["W"], d["D"], d["H"])
    faces = ("xMin", "xMax", "yMin", "yMax", "floor", "ceiling")
    g2_tab, how = radiosity.gamma2_table(dims)
    out = {"gamma2_table": g2_tab, "gamma2_how": how, "bands": {}}
    for b, fc in enumerate(BANDS):
        al = [red["faces"][f]["alpha"][b] for f in faces]
        row = {"Eyring": radiosity.eyring_t60(dims, al, m_air[b]), "Sabine": radiosity.sabine_t60(dims, al, m_air[b]),
               "gamma2_0.4": radiosity.gamma2_eyring_t60(dims, al, 0.4, m_air[b])}
        if g2_tab is not None:
            row["gamma2_table"] = radiosity.gamma2_eyring_t60(dims, al, g2_tab, m_air[b])
        if fc in AQ9_BANDS:
            a, hist, conv = radiosity.a_star_converged(dims, al, start_size=min(dims) / 2, tol=0.004, max_patches=1600)
            row["a_star"] = radiosity.t60_from_a(dims, a, m_air[b]) if a is not None else None
            row["a_star_history"] = hist
            row["a_star_converged_0.4pct"] = conv
        out["bands"][bands.band_key(fc)] = row
    return out


def air_m(t_c=air.TEMPERATURE_C, rh=air.RELATIVE_HUMIDITY_PERCENT) -> np.ndarray:
    """Energy attenuation m (1/m) per octave band (D/4.343)."""
    return np.asarray(air.attenuation_db_per_m(np.array(BANDS), t_c, rh)) / (10 / math.log(10))


KUTTRUFF_6_1 = {  # m in 1e-3 1/m at 20 degC, 500 Hz ... 8 kHz (no 3 / 6 kHz octaves here)
    40: {500: 0.60, 1000: 1.07, 2000: 2.58, 4000: 8.40, 8000: 30.00},
    50: {500: 0.63, 1000: 1.08, 2000: 2.28, 4000: 6.84, 8000: 24.29},
    70: {500: 0.64, 1000: 1.15, 2000: 2.08, 4000: 5.32, 8000: 17.91},
}


def humidity_bound(red: dict) -> dict:
    """Eyring T60 at 40 % and 70 % RH, 20 degC, relative to the AX4 atmosphere (scope 6): m from
    Kuttruff Table 6.1 at 500 Hz-8 kHz, the ISO 9613-1 code below 500 Hz."""
    d = red["dims"]
    dims = (d["W"], d["D"], d["H"])
    faces = ("xMin", "xMax", "yMin", "yMax", "floor", "ceiling")
    out = {}
    for b, fc in enumerate(BANDS):
        al = [red["faces"][f]["alpha"][b] for f in faces]
        def m_of(rh):
            if int(fc) in KUTTRUFF_6_1[rh]:
                return KUTTRUFF_6_1[rh][int(fc)] * 1e-3
            return float(air_m(20.0, rh)[b])
        t50 = radiosity.eyring_t60(dims, al, m_of(50))
        out[bands.band_key(fc)] = {f"{rh}%": 100 * (radiosity.eyring_t60(dims, al, m_of(rh)) / t50 - 1) for rh in (40, 70)}
    return out


# ------------------------------------------------------------------------------------------
# Main
# ------------------------------------------------------------------------------------------


def run(binary, cache, log=print) -> dict:
    reduction = json.loads(REDUCTION.read_text())
    res = {"pairs": {}, "rooms": {}}
    for sc in scene_list():
        log(f"{sc['name']}")
        hs = render(binary, sc["path"])
        hm = measured(cache, sc["room"], sc["src"], sc["rcv"])
        a_s, a_m = analyse(hs, FS), analyse(hm, FS)
        pb = compare_pair(a_s, a_m)
        entry = {"room": sc["room"], "alpha_set": sc["alpha_set"], "src": sc["src"], "rcv": sc["rcv"],
                 "sim": a_s, "meas": a_m, "bands": pb, "aq9": aq9(pb), "aq9_500_1k": aq9(pb, (500.0, 1000.0)),
                 "aq9_half": aq9(pb, half=True)}
        if sc["alpha_set"] == "initial":
            t, rh = CONDITIONS[sc["room"]]
            ho = analyse(render(binary, sc["path"], ("--atmosphere", f"{t},{rh}")), FS)
            pbo = compare_pair(ho, a_m)
            entry["aq9_documented_atmosphere"] = aq9(pbo)
            entry["bands_documented_atmosphere"] = {k: {"T_err_pct": v["T_err_pct"]} for k, v in pbo.items()}
            dg = diagnostics(binary, sc["path"])
            e0 = dg["emitters"][0]
            entry["diagnostics"] = {k: e0.get(k) for k in ("handoverS", "expectedMixS", "ismFallback", "realisedKeffAtMix",
                                                           "axisShares", "directS", "realisedKeff")}
            entry["edc_plot"] = plot_edc(sc["name"], hs, hm)
        res["pairs"][sc["name"]] = entry
    for room in sorted({p["room"] for p in res["pairs"].values()}):
        for alpha_set in ("initial", "fitted"):
            ps = [p for p in res["pairs"].values() if p["room"] == room and p["alpha_set"] == alpha_set]
            if not ps:
                continue
            red = reduction[room][alpha_set]
            room_res = {"n_pairs": len(ps)}
            for key in ("aq9", "aq9_500_1k", "aq9_half", "aq9_documented_atmosphere"):
                vals = [p[key] for p in ps if key in p]
                if not vals:
                    continue
                agg = {}
                for n in ("T", "EDT", "C80"):
                    v = [x[n] for x in vals if x[n] is not None]
                    agg[n] = float(np.mean(v)) if v else None
                    agg[n + "_pairs"] = len(v)
                agg["pass"] = {n: (None if agg[n] is None else agg[n] <= AQ9_LIMIT[n]) for n in ("T", "EDT", "C80")}
                agg["jnd"] = {n: (None if agg[n] is None else agg[n] / JND[n]) for n in ("T", "EDT", "C80")}
                room_res[key] = agg
            # signed per-band means over pairs (bias), measured room-averaged T30
            signed, Tm, Ts = {}, {}, {}
            for fc in BANDS:
                k = bands.band_key(fc)
                for q in ("T_err_pct", "EDT_err_pct", "C80_err_db"):
                    v = [p["bands"][k][q] for p in ps if p["bands"][k][q] is not None]
                    signed.setdefault(k, {})[q] = float(np.mean(v)) if v else None
                v = [p["meas"]["bands"][k]["T30"] for p in ps if p["meas"]["bands"][k]["T30"]]
                Tm[fc] = float(np.mean(v)) if v else None
                v = [p["sim"]["bands"][k]["T30"] for p in ps if p["sim"]["bands"][k]["T30"]]
                Ts[fc] = float(np.mean(v)) if v else None
            room_res["signed"] = signed
            room_res["T30_meas_mean"] = {bands.band_key(f): Tm[f] for f in BANDS}
            room_res["T30_sim_mean"] = {bands.band_key(f): Ts[f] for f in BANDS}
            room_res["r_meas"] = {bands.band_key(f): neighbour_ratio(Tm, f) for f in AQ9_BANDS}
            room_res["r_sim"] = {bands.band_key(f): neighbour_ratio(Ts, f) for f in AQ9_BANDS}
            room_res["leakage_sensitive"] = any((r or 0) > 1.1 for r in room_res["r_meas"].values())
            if alpha_set == "initial":
                V = red["dims"]["W"] * red["dims"]["D"] * red["dims"]["H"]
                tmid = np.mean([Tm[500.0], Tm[1000.0]]) if Tm[500.0] and Tm[1000.0] else None
                room_res["schroeder_hz"] = {"1200": 1200 * math.sqrt(tmid / V) if tmid else None,
                                            "2000": 2000 * math.sqrt(tmid / V) if tmid else None}
                room_res["predictors"] = predictors(red, air_m())
                room_res["humidity_bound"] = humidity_bound(red)
                faces = red["faces"]
                def mean_alpha(names, b):
                    A = sum(faces[f]["alpha"][b] * faces[f]["area_m2"] for f in names)
                    return A / sum(faces[f]["area_m2"] for f in names)
                room_res["absorption_contrast"] = {bands.band_key(fc): mean_alpha(("floor", "ceiling"), b) / mean_alpha(("xMin", "xMax", "yMin", "yMax"), b)
                                                   for b, fc in enumerate(BANDS) if fc in AQ9_BANDS}
                Atot = np.array(red["absorption_area_box_m2"])
                room_res["largest_face_share"] = {bands.band_key(fc): max(faces[f]["alpha"][b] * faces[f]["area_m2"] for f in faces) / Atot[b]
                                                  for b, fc in enumerate(BANDS) if fc in AQ9_BANDS}
                room_res["scattering"] = {f: faces[f]["scattering"] for f in faces}
                curv = {}
                for who in ("sim", "meas"):
                    vals = []
                    for p in ps:
                        for fc in AQ9_BANDS:
                            r_ = p[who]["bands"][bands.band_key(fc)]
                            if r_["T30"] and r_["T20"]:
                                vals.append(100 * (r_["T30"] / r_["T20"] - 1))
                    curv[who] = float(np.mean(vals)) if vals else None
                room_res["curvature_pct"] = curv
            res["rooms"][f"{room}|{alpha_set}"] = room_res
    res["b12"] = b12(res)
    return res


def _e2_octave_only(res: dict) -> dict:
    """Decider E2: B12 may run on octaves only iff (1) the leak calibration's entry condition holds,
    (2)-(4) every room's evaluable AQ9 band has r <= 1.1, S_all <= 0.42 and every S_room <= 1.67
    points, with b_band from the two-term model at the measured r and D(r) = D1,min - 10 log10 r."""
    out = {"allowed": False, "reasons": []}
    if not METER_CHECKS.exists():
        out["reasons"].append("no leak calibration results")
        return out
    lc = json.loads(METER_CHECKS.read_text()).get("leak_calibration", [])
    ok_entry = True
    d1min = {}
    for fc in (500.0, 1000.0, 2000.0):
        for var in ("below", "above"):
            rows = [r for r in lc if r["f_c"] == fc and r["variant"] == var and 1.0 < r["r"] <= 1.3]
            if not rows:
                continue
            d1 = [r["D1_dB"] for r in rows]
            d1min[(fc, var)] = min(d1)
            if fc in (1000.0, 2000.0):
                if any(r["D_dB"] < 13.0 for r in rows if r["r"] <= 1.1):
                    ok_entry = False
                if any(abs(r["residual_pct"]) > 0.6 for r in rows if r["residual_pct"] is not None):
                    ok_entry = False
            if max(d1) - min(d1) > 1.0:
                ok_entry = False
    if not ok_entry:
        out["reasons"].append("calibration entry condition fails")
    rooms = [k for k in res["rooms"] if k.endswith("|initial")]
    s_rooms = {}
    for rk in rooms:
        r = res["rooms"][rk]
        T = {float(k): v for k, v in r["T30_meas_mean"].items()}
        bs = []
        for fc in AQ9_BANDS:
            rr = neighbour_ratio(T, fc)
            if rr is None:
                continue
            if rr > 1.1:
                out["reasons"].append(f"{rk.split('|')[0]} {fc:.0f} Hz r = {rr:.3f} > 1.1")
            i = BANDS.index(fc)
            nb = [BANDS[j] for j in (i - 1, i + 1) if 0 <= j < len(BANDS) and T.get(BANDS[j])]
            slower = max(nb, key=lambda f: T[f]) if nb else None
            var = "below" if slower is not None and slower < fc else "above"
            d1 = d1min.get((fc, var))
            if d1 is None or rr <= 1.0:
                bs.append(0.0)
                continue
            bs.append(100 * meter_checks.two_term_bias(rr, d1 - 10 * math.log10(rr)))
        if bs:
            s_rooms[rk.split("|")[0]] = 2 * float(np.mean(bs))
    s_all = float(np.mean(list(s_rooms.values()))) if s_rooms else None
    out.update({"S_room_pts": s_rooms, "S_all_pts": s_all})
    if s_all is None or s_all > 0.42 or any(v > 1.67 for v in s_rooms.values()):
        out["reasons"].append(f"S_all = {s_all} / S_room = {s_rooms} above the margin/3 limits")
    out["allowed"] = not out["reasons"]
    return out


def b12(res: dict) -> dict:
    """Decay-predictor decision rule (B12) on the initial α set (condition iv), octave run (run 1)
    and the octave-500 Hz + half-octave-1/2 kHz run (run 2). A predictor replaces Eyring only if it
    lowers the room-averaged mean |T30 error| by >= 1.25 points and makes no room worse by > 5
    points; a* only when converged to < 0.4 % per halving in every band used (condition i);
    γ²-Eyring only when it passes at every admissible γ² (the Table 5.1 value and 0.4, condition
    ii); both runs must agree, unless the E2 octave-only branch applies (then run 1 alone)."""
    rooms = [k for k in res["rooms"] if k.endswith("|initial")]
    out = {}
    for run_name, use_half in (("run1_octave", False), ("run2_half", True)):
        errs = {}
        conv = {}
        for rk in rooms:
            r = res["rooms"][rk]
            pairs = [p for p in res["pairs"].values() if f"{p['room']}|{p['alpha_set']}" == rk]
            for pred in ("Eyring", "a_star", "gamma2_table", "gamma2_0.4"):
                vals = []
                for fc in AQ9_BANDS:
                    k = bands.band_key(fc)
                    tp = r["predictors"]["bands"][k].get(pred)
                    if tp is None:
                        continue
                    if pred == "a_star" and not r["predictors"]["bands"][k].get("a_star_converged_0.4pct"):
                        conv[rk] = False
                    if use_half and fc in HALF_BANDS:
                        tm = [p["meas"]["bands"][k]["T30_half"] for p in pairs if p["meas"]["bands"][k]["T30_half"]]
                    else:
                        tm = [p["meas"]["bands"][k]["T30"] for p in pairs if p["meas"]["bands"][k]["T30"]]
                    if tm:
                        vals.append(abs(100 * (tp / np.mean(tm) - 1)))
                if vals:
                    errs.setdefault(pred, {})[rk.split("|")[0]] = float(np.mean(vals))
        summary = {}
        base = errs.get("Eyring", {})
        for pred, by_room in errs.items():
            common = [rm for rm in by_room if rm in base]
            if not common:
                continue
            mean_p = float(np.mean([by_room[rm] for rm in common]))
            mean_e = float(np.mean([base[rm] for rm in common]))
            worst = max(by_room[rm] - base[rm] for rm in common)
            meets = pred != "Eyring" and mean_e - mean_p >= 1.25 and worst <= 5.0
            if pred == "a_star" and conv:
                meets = False
            summary[pred] = {"mean_abs_err_pct": mean_p, "by_room": by_room, "lowers_by_pts": mean_e - mean_p,
                             "worst_room_increase_pts": worst, "meets_margin": meets}
        # condition (ii): γ²-Eyring as one predictor, at every admissible γ²
        g = [summary[k]["meets_margin"] for k in ("gamma2_table", "gamma2_0.4") if k in summary]
        summary["gamma2 (all admissible)"] = {"meets_margin": bool(g) and all(g)}
        out[run_name] = summary
    e2 = _e2_octave_only(res)
    out["e2_octave_only"] = e2
    decision = {}
    for pred in ("a_star", "gamma2 (all admissible)"):
        r1 = out["run1_octave"].get(pred, {}).get("meets_margin", False)
        r2 = out["run2_half"].get(pred, {}).get("meets_margin", False)
        if e2["allowed"]:
            decision[pred] = "replaces Eyring (octave-only branch)" if r1 else "Eyring stays"
        elif r1 and r2:
            decision[pred] = "replaces Eyring (both runs)"
        elif r1 != r2:
            decision[pred] = "meter-dependent, Eyring stays"
        else:
            decision[pred] = "Eyring stays"
    out["decision"] = decision
    out["label"] = "input-limited (BRAS alone; Maisara decides, C2)"
    return out


def plot_edc(name: str, hs: np.ndarray, hm: np.ndarray) -> str | None:
    try:
        import matplotlib
        matplotlib.use("Agg")
        import matplotlib.pyplot as plt
    except ImportError:
        return None
    PLOTS.mkdir(parents=True, exist_ok=True)
    fig, axes = plt.subplots(1, 3, figsize=(12, 3.2), sharey=True)
    for ax, fc in zip(axes, AQ9_BANDS):
        for h, lab, sty in ((hm, "measured", "-"), (hs, "simulated", "--")):
            on = metrics.onset_index(h)
            y, lead = bands.filter_band_with_lead(h, FS, fc)
            e = (y**2)[on + lead:]
            lb = metrics.lundeby(e, FS)
            edc = metrics.schroeder_edc(e, lb.crosspoint, lb.compensation)
            t = np.arange(edc.size) / FS
            ax.plot(t, edc, sty, label=lab, lw=1)
        ax.set_title(f"{fc:.0f} Hz")
        ax.set_xlabel("t after onset (s)")
        ax.set_ylim(-60, 2)
        ax.grid(alpha=0.3)
    axes[0].set_ylabel("EDC (dB)")
    axes[0].legend()
    fig.suptitle(name)
    fig.tight_layout()
    out = PLOTS / f"{name}.png"
    fig.savefig(out, dpi=80, metadata={"Software": None})
    plt.close(fig)
    return str(out.relative_to(REPO))


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("--sim-only", action="store_true", help="print the simulated metrics (nightly gate input) as JSON")
    ap.add_argument("--no-report", action="store_true")
    a = ap.parse_args(argv)
    binary = render_cli.find_render_cli()
    if binary is None:
        raise SystemExit("render_cli not found (build the cli preset or set RENDER_CLI)")
    if a.sim_only:
        print(json.dumps(simulated_metrics(binary), indent=1))
        return
    cache = fetch_bras.cache_dir()
    fetch_bras.fetch(["docs", "materials", "parameters", "rirs"], cache)
    res = run(binary, cache)
    RESULTS.write_text(json.dumps(res, indent=1, default=float) + "\n")
    if not a.no_report:
        from tools.validation import report
        report.write(res, REPORT)
    print("wrote", RESULTS)


if __name__ == "__main__":
    main()
