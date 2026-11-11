"""Write docs/validation/report-phase05.md from the run_validation.py results (every number in the
report comes from tools/validation/data/phase05_results.json, so two runs give the same report)."""

from __future__ import annotations

import json
import os
import posixpath
import pathlib

HERE = pathlib.Path(__file__).resolve().parent
REPO = HERE.parents[1]
METER = REPO / "tools" / "acoustics" / "data" / "phase05_meter_checks.json"
BK = ("63", "125", "250", "500", "1000", "2000", "4000", "8000")
AQ9 = ("500", "1000", "2000")


def f(x, nd=1, unit=""):
    if x is None:
        return "–"
    if isinstance(x, bool):
        return "yes" if x else "no"
    return f"{x:.{nd}f}{unit}"


def pf(p):
    return "–" if p is None else ("pass" if p else "**fail**")


SELECTED = ("CR2", "CR3", "CR4")  # bras_mapping.md §1 (pre-committed; never changed after results)
# B12 "shown separately for uniform and uneven α" (phase-05 scope 6): the grouping is the bras_mapping.md §5
# classification (Raise with Maisara item 1, read from the area tables before any comparison): CR2 uniform;
# CR3 and CR4 one strong absorber (the seating).
ALPHA_GROUP = {"CR2": "uniform", "CR3": "uneven", "CR4": "uneven"}


REDUCTION = HERE / "data" / "bras_reduction.json"
GEOMETRY = HERE / "data" / "bras_geometry.json"
# BRAS documentation sheets (Aspöck et al., Documentation.pdf pp. 25–27): the rounded room volumes, CR3 "excluding
# the attic". The one number of the volume paragraph that is not in the committed data (bras_mapping.md §1).
BRAS_SHEET_VOLUME_M3 = {"CR2": 145.0, "CR3": 2350.0, "CR4": 8650.0}
SHEET_NOTE = {"CR3": "the sheet excludes the attic that the model includes"}
# The material of the one strong absorber in the uneven-α rooms (bras_mapping.md §5 classification, read from the
# area tables before any comparison); its s is read from bras_reduction.json.
STRONG_ABSORBER = "seating"
# Recorded B12 outcome (BUILD_PLAN §5 B12, Phase 05f; ledger F5f-2 … F5f-27). Printed whenever a predictor meets the
# rule's arithmetic; the arithmetic itself is printed above from the results, the room-band count below is computed.
B12_RECORDED_OUTCOME = (
    "**Recorded outcome (BUILD_PLAN §5 B12; recommendation under C2, decider 2026-11-07, accepted by Maisara "
    "2026-11-07):** not adopted; Eyring stays in `src/sim`; AQ2 unchanged. The BRAS margin does not separate accurate "
    "from inaccurate predictors: Eyring under-predicts T in {under} of {total} room-bands ({rooms} at 500 Hz–2 kHz, "
    "initial α, against the mean measured T30), so any lengthening lowers the mean error (Sabine, less accurate than "
    "Eyring on Kuttruff Table 5.2, gains most), and γ²-Eyring (Kuttruff Eq. 5.34) lengthens T for every γ² > 0 and "
    "fails the rule on Table 5.2. Reopened only on a measured dataset that meets the conditions in BUILD_PLAN §5 B12 "
    "(ledger F5f-2 … F5f-27).")


def eyring_under_prediction(res: dict) -> tuple:
    """(room-bands where Eyring's T is below the mean measured T30, room-bands, rooms): initial α, 500 Hz–2 kHz."""
    under = total = 0
    rooms = []
    for rk in sorted(res["rooms"]):
        room, aset = rk.split("|")
        if aset != "initial":
            continue
        r = res["rooms"][rk]
        rooms.append(room)
        for b in AQ9:
            total += 1
            under += r["predictors"]["bands"][b]["Eyring"] < r["T30_meas_mean"][b]
    return under, total, rooms


def b12_recorded_outcome(res: dict) -> str:
    under, total, rooms = eyring_under_prediction(res)
    return B12_RECORDED_OUTCOME.format(under=under, total=total, rooms=", ".join(rooms))


def load_reduction(path: pathlib.Path = REDUCTION) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def model_volumes(path: pathlib.Path = GEOMETRY) -> dict:
    """Documented model volume per room (`_descr/mat_CRx.txt`, "based on provided 3d models")."""
    g = json.loads(path.read_text(encoding="utf-8"))
    return {rm: r["documented"]["V"] for rm, r in g["rooms"].items()}


def volume_ratios_pct(rooms, model_v: dict | None = None) -> dict:
    """Predicted-T rise from using the model volume instead of the sheet volume (A fixed: T ∝ V), in %."""
    model_v = model_volumes() if model_v is None else model_v
    return {rm: 100.0 * (model_v[rm] / BRAS_SHEET_VOLUME_M3[rm] - 1.0) for rm in rooms}


def _num(x: float, nd: int) -> str:
    """Space as the thousands separator, as in the plan documents (8 656.5)."""
    return f"{x:,.{nd}f}".replace(",", " ")


def volume_paragraph(rooms) -> str:
    model_v = model_volumes()
    ratios = volume_ratios_pct(rooms, model_v)
    parts = []
    for rm in rooms:
        note = SHEET_NOTE.get(rm, "rounded")
        parts.append(f"{ratios[rm]:+.2f} % in {rm} ({_num(model_v[rm], 1)} vs {_num(BRAS_SHEET_VOLUME_M3[rm], 0)} m³; {note})")
    return ("Model volume (AX26 keeps it; bras_mapping.md §1 volume check): with A fixed, predicted T scales with V, so "
            "the model volume (`_descr/mat_CRx.txt`) raises predicted T against the BRAS sheet volumes (Aspöck et al., "
            "pp. 25–27) by " + ", ".join(parts) + ". BRAS's own fitted α reproduce BRAS's measured T20 with the model "
            "volumes to within the figures of bras_mapping.md §1 (volume check, item 2).")


def seating_s(reduction: dict, rooms) -> dict:
    """{room: (s 500 Hz, 1 kHz, 2 kHz)} of the strong absorber, octave values by AX25 (bras_reduction.json)."""
    out = {}
    for rm in rooms:
        mats = reduction[rm]["initial"]["materials"]
        key = next(k for k in mats if k.endswith("_" + STRONG_ABSORBER))
        sb = mats[key]["scattering_bands"]
        out[rm] = tuple(sb[BK.index(b)] for b in AQ9)
    return out


def seating_s_text(reduction: dict, rooms) -> str:
    """'0.43 / 0.60 / 0.85–0.87': per band, one value or the range over the rooms (two decimals)."""
    vals = seating_s(reduction, rooms)
    cells = []
    for i in range(len(AQ9)):
        lo, hi = (f"{x:.2f}" for x in (min(v[i] for v in vals.values()), max(v[i] for v in vals.values())))
        cells.append(lo if lo == hi else f"{lo}–{hi}")
    return " / ".join(cells)


def room_set(res: dict) -> list:
    return sorted({rk.split("|")[0] for rk in res["rooms"]})


def room_set_label(res: dict) -> str:
    """'three-room' once every selected room is in the results (phase-05f), else the phase-05e
    provisional label naming what is pending."""
    rooms = room_set(res)
    missing = [r for r in SELECTED if r not in rooms]
    if not missing:
        return "**Three rooms (" + ", ".join(rooms) + ")**, every selected room (bras_mapping.md §1)"
    return ("**Provisional, " + {1: "one", 2: "two"}.get(len(rooms), str(len(rooms))) + "-room (" + ", ".join(rooms)
            + "); " + ", ".join(missing) + " pending**")


def _mc_se(p: dict) -> str:
    """Phase 05h (scope 5): the tail level's Monte Carlo SE per AQ9 band and its max over bands (AX42 units, dB of the
    total E_target); 'U' marks a pair where AX44's note is raised. '–' when the diagnostics predate the switch."""
    d = p.get("diagnostics", {})
    bands_se = d.get("tail_level_se_db_bands")
    if not bands_se:
        return "–"
    idx = {"500": 3, "1000": 4, "2000": 5}
    per = " / ".join(f"{bands_se[idx[k]]:.3f}" for k in ("500", "1000", "2000") if idx[k] < len(bands_se))
    mx = d.get("tail_level_se_db")
    return f"{per}; max {mx:.3f}" + (" U" if d.get("tail_level_approximate") else "") if mx is not None else per


def write(res: dict, path: pathlib.Path) -> None:
    L = []
    w = L.append
    w("# Phase 05 report: simulated vs measured room IRs (BRAS) — evidence, not validation")
    w("")
    w("Generated by `tools/validation/run_validation.py` (data: `tools/validation/data/phase05_results.json`). "
      "Do not edit by hand. Measured data: BRAS (Aspöck, Brinkmann, Ackermann, Weinzierl, Vorländer; "
      "DOI 10.14279/depositonce-6726.3; CC BY-SA 4.0); this report is an adaptation under CC BY-SA 4.0.")
    w("")
    w("**Read this first.** BRAS states that its complex rooms \"cannot serve as a direct reference but may be used to "
      "compare the results from different simulations based on indentical input data\" (as printed). All α and s are "
      "estimates. The errors below measure **method plus input data**; they are evidence on NFR-1 and AQ2, not a "
      "validation (researcher findings F2, F3, F6, F7). Strength G is **not evaluable**: the BRAS RIR levels were "
      "manually corrected by 6 dB (F3); T30, EDT and C80 do not depend on absolute level. Round-robin context (RR19, "
      "Brinkmann et al. 2019, JASA 145(4), DOI 10.1121/1.5096178): blind mature hybrids on the same initial data stayed "
      "above 1 jnd at 500 Hz–2 kHz in most cases; their per-room numbers were not retrieved in this session, so they "
      "are not printed beside ours.")
    w("")
    # ---------------- summary
    w("## 1. AQ9 summary (thresholds: T30 and EDT ±10 %, C80 ±2 dB on the mean of |per-band error| at 500 Hz, 1 kHz, 2 kHz)")
    w("")
    w("| Room | α set | pairs | T30 mean \\|err\\| | EDT mean \\|err\\| | C80 mean \\|err\\| | T30 | EDT | C80 | 500–1000 Hz (T30 / EDT / C80) | half-octave 1–2 kHz (T30 / EDT, secondary) | at documented atmosphere (T30) | leakage-sensitive |")
    w("|---|---|---|---|---|---|---|---|---|---|---|---|---|")
    met = {"initial": [0, 0], "fitted": [0, 0]}
    for rk in sorted(res["rooms"]):
        r = res["rooms"][rk]
        room, aset = rk.split("|")
        a, a5, ah = r["aq9"], r.get("aq9_500_1k", {}), r.get("aq9_half", {})
        ad = r.get("aq9_documented_atmosphere", {})
        passes = [a["pass"][n] for n in ("T", "EDT", "C80")]
        if all(p is not None for p in passes):
            met[aset][1] += 1
            met[aset][0] += all(passes)
        label = aset + (" (circular for T30)" if aset == "fitted" else "")
        w(f"| {room} | {label} | {r['n_pairs']} | {f(a['T'])} % | {f(a['EDT'])} % | {f(a['C80'], 2)} dB | "
          f"{pf(a['pass']['T'])} | {pf(a['pass']['EDT'])} | {pf(a['pass']['C80'])} | "
          f"{f(a5.get('T'))} % / {f(a5.get('EDT'))} % / {f(a5.get('C80'), 2)} dB | {f(ah.get('T'))} % / {f(ah.get('EDT'))} % | "
          f"{f(ad.get('T'))} % | {f(r.get('leakage_sensitive'))} |")
    w("")
    w(f"**AQ9 met (all three metrics, room mean over pairs): initial α {met['initial'][0]}/{met['initial'][1]} rooms; "
      f"fitted α {met['fitted'][0]}/{met['fitted'][1]} rooms** (fitted: T30 circular by construction, F6).")
    w("")
    if all(r in room_set(res) for r in SELECTED):
        w(room_set_label(res) + ": CR4 entered in phase-05f after its geometry passed the bras_mapping.md §2 acceptance "
          "test (AX30). The B12 replacement and the B11 promotion decisions deferred in phase-05e are taken on these rooms "
          "with phase-05.md's unchanged pass rules (sections 3 and 6b).")
    else:
        w(room_set_label(res) + " (phase-05e scope (b)): the pending rooms stay selected and are not dropped. The B12 "
          "replacement and the B11 promotion decisions are deferred until they enter (pass rules unchanged).")
    w("")
    w(volume_paragraph(room_set(res)))
    pp = {"initial": [0, 0], "fitted": [0, 0]}
    for p in res["pairs"].values():
        ps = [p["aq9"]["pass"][n] for n in ("T", "EDT", "C80")]
        if all(x is not None for x in ps):
            pp[p["alpha_set"]][1] += 1
            pp[p["alpha_set"]][0] += all(ps)
    w(f"Per pair: initial α {pp['initial'][0]}/{pp['initial'][1]}, fitted α {pp['fitted'][0]}/{pp['fitted'][1]}. "
      "A per-pair pass/fail mostly reflects position-specific details (RR19 found the per-position structure mostly "
      "not reproduced; external source). The jnd-normalised errors (T: working 5 %, EDT 5 %, C80 1 dB; Vorländer "
      "Table 6.1 states EDT and C80 for 500–1000 Hz, extended to 2 kHz) are in the per-room tables.")
    w("")
    # ---------------- per room
    w("## 2. Per room")
    for rk in sorted(res["rooms"]):
        r = res["rooms"][rk]
        room, aset = rk.split("|")
        w("")
        w(f"### {room}, {aset} α")
        w("")
        pre = [p["meas"]["pre_onset_max_db"] for p in res["pairs"].values()
               if f"{p['room']}|{p['alpha_set']}" == rk and p["meas"]["pre_onset_max_db"] is not None]
        if pre:
            w(f"Measured lead-in: the highest level before the detected onset is {max(pre):.1f} dB re the broadband "
              "maximum (by the onset rule it is below -20 dB; a value close to -20 dB means an early component such as "
              "a sweep distortion product sits near the threshold).")
        j = r["aq9"]["jnd"]
        w(f"Mean |error| in jnd: T30 {f(j['T'], 2)}, EDT {f(j['EDT'], 2)}, C80 {f(j['C80'], 2)}.")
        if "schroeder_hz" in r:
            sh = r["schroeder_hz"]
            w(f"Schroeder frequency (measured mid T30): 1200√(T/V) = {f(sh['1200'], 0)} Hz (Vorländer Eq. 4.13; f must greatly "
              f"exceed it) and 2000√(T/V) = {f(sh['2000'], 0)} Hz (Toole §4.3.1, middle of the transition zone). The upper edge "
              f"treated as 'below this: method validity, not input data' is the 2000 constant's value, ×4 "
              f"(≈ {f(4 * sh['2000'] if sh['2000'] else None, 0)} Hz), the usual end of the transition zone; bands below it are read as evidence on the method.")
        w("")
        w("Signed mean over pairs (sign = bias), measured and simulated room-averaged T30:")
        w("")
        w("| band (Hz) | " + " | ".join(BK) + " |")
        w("|---|" + "---|" * len(BK))
        s = r["signed"]
        w("| T err (%) | " + " | ".join(f(s[k]["T_err_pct"]) for k in BK) + " |")
        w("| EDT err (%) | " + " | ".join(f(s[k]["EDT_err_pct"]) for k in BK) + " |")
        w("| C80 err (dB) | " + " | ".join(f(s[k]["C80_err_db"], 2) for k in BK) + " |")
        w("| T30 meas (s) | " + " | ".join(f(r["T30_meas_mean"][k], 2) for k in BK) + " |")
        w("| T30 sim (s) | " + " | ".join(f(r["T30_sim_mean"][k], 2) for k in BK) + " |")
        w("")
        w("Octave neighbour ratio r = T(slower neighbour)/T(band) at 500 Hz / 1 kHz / 2 kHz: measured "
          + " / ".join(f(r["r_meas"][k], 3) for k in AQ9) + ", simulated " + " / ".join(f(r["r_sim"][k], 3) for k in AQ9)
          + (". **Leakage-sensitive** (some r > 1.1)." if r["leakage_sensitive"] else "."))
        if "absorption_contrast" in r:
            w("")
            w("Non-diffuseness indicators (reported only; no diffuseness threshold, Kuttruff §8.5): absorption contrast "
              "ᾱ(floor+ceiling)/ᾱ(walls) " + " / ".join(f(r["absorption_contrast"][k], 2) for k in AQ9)
              + "; largest single-face share of A " + " / ".join(f(r["largest_face_share"][k], 2) for k in AQ9)
              + f"; decay curvature C = 100(T30/T20 − 1): measured {f(r['curvature_pct']['meas'])} %, simulated {f(r['curvature_pct']['sim'])} % "
              "(> ≈ 10 % marks a markedly non-straight decay). Broadband s per face (AX17): "
              + ", ".join(f"{k} {v:.3f}" for k, v in r["scattering"].items()) + ".")
        if "box" in r:
            bx = r["box"]
            w("")
            w(f"Box (AX26): V = {bx['V']:.1f} m³, S(box) = {bx['S_box']:.1f} m² vs documented {bx['S_documented']:.1f} m² "
              f"({bx['S_error_pct']:+.1f} %); Eyring on the box vs on the documented V, S, A at 500 Hz / 1 kHz / 2 kHz: "
              + " / ".join(f"{bx['eyring_error_pct'][i]:+.2f} %" for i in (3, 4, 5)) + " (bras_mapping.md §5).")
        if "noise_admission" in r:
            na = r["noise_admission"]
            w(f"Noise-margin admission (AX27): {na['admitted']} of {na['of']} measured AQ9 bands (pairs × 3) have a "
              f"decay-referred noise margin ≥ L_min = {na['L_min_dB']:.0f} dB and enter the gated AQ9 mean and B12; the others "
              "are flagged 'noise not verified (margin)'.")
        if "mixing_times_ms" in r:
            mt = r["mixing_times_ms"]
            tm = mt["t_mix_e_minus_t_dir_e"]
            w(f"Mixing times (context; Lindau, Kosanke & Weinzierl 2012, Eqs. 12–14, binaural, near-shoebox rooms, "
              f"V ≤ ≈ 10 000 m³): t_mp50 = 20·V/S + 12 = {mt['t_mp50_VS']:.0f} ms, 0.58·√V + 21.2 = {mt['t_mp50_sqrtV']:.0f} ms; "
              f"t_mp95 = 0.0117·V + 50.1 = {mt['t_mp95']:.0f} ms; Phase 04 rule t_mix,e − t_dir,e over the pairs: "
              + (f"{tm[0]:.0f}–{tm[1]:.0f} ms." if tm else "–."))
        if "predictors" in r:
            w("")
            w("Decay predictors for the reduced box (T60, s; AX4 air):")
            w("")
            pr = r["predictors"]
            w("| band | measured T30 | Eyring | a* | γ²-Eyring (Table 5.1: " + f(pr["gamma2_table"], 3) + f", {pr['gamma2_how']}) | γ²-Eyring (0.4) | Sabine | a* converged < 0.4 % |")
            w("|---|---|---|---|---|---|---|---|")
            for k in AQ9:
                b = pr["bands"][k]
                w(f"| {k} | {f(r['T30_meas_mean'][k], 2)} | {f(b['Eyring'], 2)} | {f(b.get('a_star'), 2)} | {f(b.get('gamma2_table'), 2)} | "
                  f"{f(b['gamma2_0.4'], 2)} | {f(b['Sabine'], 2)} | {f(b.get('a_star_converged_0.4pct'))} |")
            w("")
            hb = r["humidity_bound"]
            w("Humidity bound (AX4): Eyring T60 at 40 % / 70 % RH (20 °C) relative to 50 % RH, per band: "
              + "; ".join(f"{k} Hz {hb[k]['40%']:+.1f} / {hb[k]['70%']:+.1f} %" for k in BK) + ".")
    # ---------------- B12
    w("")
    w("## 3. Decay-predictor rule (B12), initial α only")
    w("")
    w("A predictor replaces Eyring only if it lowers the room-averaged mean |T30 error| at 500 Hz–2 kHz by ≥ 1.25 "
      "points and makes no room worse by > 5 points, on both meter runs, with a* converged to < 0.4 % per halving and "
      "γ²-Eyring passing at every admissible γ² (the Table 5.1 value and 0.4). An outcome from BRAS alone is "
      "'input-limited' (C2); Maisara decides. The octave-only branch (E2) needs the leak-calibration entry condition "
      "(section 5); it is evaluated below.")
    w("")
    w("| run | predictor | mean \\|err\\| (%) | lowers Eyring by (pts) | worst room increase (pts) | meets the margin |")
    w("|---|---|---|---|---|---|")
    for run in ("run1_octave", "run2_half"):
        for pred, s in res["b12"][run].items():
            w(f"| {run} | {pred} | {f(s.get('mean_abs_err_pct'))} | {f(s.get('lowers_by_pts'), 2)} | "
              f"{f(s.get('worst_room_increase_pts'), 2)} | {f(s['meets_margin'])} |")
    # per room, sorted by the two indicators (phase-05 scope 6: no threshold splits them), and by α group
    preds = [k for k in ("Eyring", "a_star", "gamma2_table", "gamma2_0.4") if k in res["b12"]["run1_octave"]]
    ind = {}
    for rk, r in res["rooms"].items():
        room, aset = rk.split("|")
        if aset == "initial" and "absorption_contrast" in r:
            ind[room] = (sum(r["absorption_contrast"].values()) / len(r["absorption_contrast"]),
                         sum(r["largest_face_share"].values()) / len(r["largest_face_share"]),
                         r["predictors"]["gamma2_table"], r["predictors"]["gamma2_how"],
                         all(b.get("a_star_converged_0.4pct") for k, b in r["predictors"]["bands"].items() if k in AQ9))
    w("")
    w("Per room (initial α, mean |T30 error| at 500 Hz–2 kHz in %, run 1 / run 2), with the indicators of section 2 "
      "(means over 500 Hz–2 kHz) and the γ² admissible for the room (condition ii: the Table 5.1 row where the shape "
      "is tabulated, else 0.4):")
    w("")
    w("| room | absorption contrast | largest face share of A | admissible γ² | a* converged < 0.4 % | "
      + " | ".join(preds) + " |")
    w("|---|---|---|---|---|" + "---|" * len(preds))
    for room in sorted(ind, key=lambda rm: ind[rm][0]):
        c, sh, g, how, conv = ind[room]
        cells = []
        for pr_ in preds:
            r1 = res["b12"]["run1_octave"].get(pr_, {}).get("by_room", {}).get(room)
            r2 = res["b12"]["run2_half"].get(pr_, {}).get("by_room", {}).get(room)
            cells.append(f"{f(r1)} / {f(r2)}")
        w(f"| {room} | {c:.2f} | {sh:.2f} | " + (f"{g:.3f} (Table 5.1) and 0.4" if g is not None else f"0.4 only ({how})")
          + f" | {f(conv)} | " + " | ".join(cells) + " |")
    w("")
    w("Sorted by absorption contrast: " + ", ".join(sorted(ind, key=lambda rm: ind[rm][0]))
      + "; by largest single-face share of A: " + ", ".join(sorted(ind, key=lambda rm: ind[rm][1])) + ".")
    groups = {g: [rm for rm in ind if ALPHA_GROUP.get(rm) == g] for g in ("uniform", "uneven")}
    for g, rms in groups.items():
        if not rms:
            continue
        w(f"- {g} α ({', '.join(rms)}; bras_mapping.md §5 classification): "
          + "; ".join(f"{pr_} {sum(res['b12']['run1_octave'][pr_]['by_room'][rm] for rm in rms) / len(rms):.2f} %"
                      for pr_ in preds if all(rm in res["b12"]["run1_octave"].get(pr_, {}).get("by_room", {}) for rm in rms))
          + " (run 1).")
    w("")
    w("Conditions: (i) a* counts only when converged to < 0.4 % per halving in every band used: "
      + ("met" if all(v[4] for v in ind.values()) else "not met in " + ", ".join(rm for rm, v in ind.items() if not v[4]))
      + "; (ii) γ²-Eyring must pass at every admissible γ² (per room above); (iii) the 5 % T jnd is a working value "
      "from outside the corpus; (iv) only the initial-estimate α set counts (this table); (v) a* may not replace Eyring "
      "while ledger DB-1 is unresolved (unresolved).")
    e2 = res["b12"]["e2_octave_only"]
    w("")
    w(f"Octave-only branch (E2): {'allowed' if e2['allowed'] else 'not allowed'}"
      + (f" ({'; '.join(e2['reasons'])})" if e2["reasons"] else "") + f"; S_all = {f(e2.get('S_all_pts'), 2)} points.")
    w("Decision: " + "; ".join(f"{k}: {v}" for k, v in res["b12"]["decision"].items()) + f" — {res['b12']['label']}.")
    if any(v.startswith("replaces") for v in res["b12"]["decision"].values()):
        w("")
        w(b12_recorded_outcome(res))
    # ---------------- per pair
    w("")
    w("## 4. Per pair (initial α)")
    w("")
    w("| pair | T30 err 500/1k/2k (%) | EDT err 500/1k/2k (%) | C80 err 500/1k/2k (dB) | AQ9 T30 / EDT / C80 | tail-level MC SE 500/1k/2k (dB, AX42; max over bands) | flags | EDC plot |")
    w("|---|---|---|---|---|---|---|---|")
    for name in sorted(res["pairs"]):
        p = res["pairs"][name]
        if p["alpha_set"] != "initial":
            continue
        b = p["bands"]
        flags = []
        for k in AQ9:
            if b[k]["kind"] == "T20":
                flags.append(f"{k}: T20")
            if b[k]["kind"] == "none":
                flags.append(f"{k}: T not evaluable")
            if b[k].get("meter_dependent"):
                flags.append(f"{k}: meter-dependent")
            if b[k].get("noise_not_verified"):
                flags.append(f"{k}: noise not verified")
            if b[k].get("noise_not_verified_margin"):
                flags.append(f"{k}: noise not verified (margin)")
        a = p["aq9"]["pass"]
        plot = p.get("edc_plot")
        w(f"| {name} | " + " / ".join(f(b[k]["T_err_pct"]) for k in AQ9) + " | " + " / ".join(f(b[k]["EDT_err_pct"]) for k in AQ9)
          + " | " + " / ".join(f(b[k]["C80_err_db"], 2) for k in AQ9) + f" | {pf(a['T'])} / {pf(a['EDT'])} / {pf(a['C80'])} | "
          + _mc_se(p) + " | " + (", ".join(flags) or "–") + " | "
          + (f"[png]({posixpath.relpath(plot, 'docs/validation')})" if plot else "–") + " |")
    w("")
    w("Flags: 'T20' = the T30 usable-range test failed (peak-referred dynamic range or the Lundeby late line < 45 dB); "
      "measured T20 is compared with simulated T20. 'meter-dependent' = octave and half-octave errors differ by > 5 points. "
      "'noise not verified' = the Lundeby noise estimate and the last-10 % mean square differ by more than 3·√(σ₁² + σ₂²), "
      "σᵢ = 4.34/√(B·T_seg) dB. 'noise not verified (margin)' = decay-referred noise margin < L_min (AX27): excluded from "
      "the gated AQ9 mean and B12. AX17 input error: every per-band delta in the AQ9 bands includes the broadband-s "
      "reduction (BRAS s rises as √f: +47 % at 500 Hz, −26 % at 2 kHz).")
    # ---------------- per pair and band (detail)
    w("")
    w("### 4b. Per pair and band, initial α (both meters, r, usable-range margins, flags)")
    w("")
    w("T: the decay time compared (T30, or T20 when T30 is not usable); half: the AX23(b) half-octave Kaiser FIR reading "
      "(1, 2 kHz), secondary; r: each IR's octave neighbour ratio T(slower neighbour)/T(band); margins of the measured "
      "band: peak-referred dynamic range / decay-referred Lundeby line at t₀ above the noise (dB; T30 needs both ≥ 45 dB, "
      "AQ9/B12 admission needs the line ≥ L_min).")
    w("")
    w("| pair | band | T meas / sim (s) | T err (%) | half T30 meas / sim (s) | half err (%) | EDT meas / sim (s) | r meas / sim | margins meas (dB) | admitted | flags |")
    w("|---|---|---|---|---|---|---|---|---|---|---|")
    for name in sorted(res["pairs"]):
        p = res["pairs"][name]
        if p["alpha_set"] != "initial":
            continue
        for k in AQ9:
            b, sm, ms = p["bands"][k], p["sim"]["bands"][k], p["meas"]["bands"][k]
            fl = [x for x, on in (("meter-dependent", b.get("meter_dependent")), ("noise not verified", b.get("noise_not_verified")),
                                  ("noise not verified (margin)", b.get("noise_not_verified_margin")),
                                  ("T20", b["kind"] == "T20"), ("T not evaluable", b["kind"] == "none")) if on]
            ri = p.get("r_ir", {})
            w(f"| {name} | {k} | {f(b['T_meas'], 3)} / {f(b['T_sim'], 3)} | {f(b['T_err_pct'])} | "
              f"{f(ms.get('T30_half'), 3)} / {f(sm.get('T30_half'), 3)} | {f(b.get('T30_half_err_pct'))} | "
              f"{f(b['EDT_meas'], 3)} / {f(b['EDT_sim'], 3)} | {f(ri.get('meas', {}).get(k), 3)} / {f(ri.get('sim', {}).get(k), 3)} | "
              f"{f(ms['dynamic_range_db'])} / {f(ms['line_margin_db'])} | {f(b.get('admitted'))} | {', '.join(fl) or '–'} |")
    # ---------------- meter checks
    w("")
    w("## 5. Meter checks (scope 7)")
    if METER.exists():
        mc = json.loads(METER.read_text())
        w("")
        w(f"Simulated EDC (N1): metrics path vs integration to the end at −35 dB: {mc['simulated_edc']['difference_dB']:.2e} dB (criterion ≤ 0.01 dB).")
        w("")
        lm = mc.get("ax27_l_min")
        if lm:
            w(f"AX27 L_min = {lm['L_min_dB']:.0f} dB: the lowest level (1 dB steps from 51 dB) with median − 3·SD ≥ 45 dB of the "
              "peak-referred Lundeby dynamic range in every case A condition (ledger E5-1, option C); worst condition per level: "
              + "; ".join(f"{x['level_dB']:.0f} dB: {x['worst']['dynamic_range_median_minus_3sd_dB']:.2f} dB "
                          f"({x['worst']['f_c']:.0f} Hz, T = {x['worst']['T']} s)" for x in lm["levels"]) + ".")
            w("")
        w("Paired noise test, case A, with AX27 noise subtraction (gate |mean paired T30 bias| ≤ 0.6 %, SE ≤ 0.15 %, "
          "no unsuitable realisation):")
        w("")
        w("| band | T (s) | noise below decay (dB) | R | mean bias (%) | SE (%) | EDT (%) | C80 (dB) | gate |")
        w("|---|---|---|---|---|---|---|---|---|")
        for c in mc["paired_noise_case_A"]:
            ok = c["mean_bias_pct"] is not None and abs(c["mean_bias_pct"]) <= 0.6 and c["se_pct"] <= 0.15
            w(f"| {c['f_c']:.0f} | {c['T']} | {c['noise_below_dB']:.0f} | {c['R']} | {c['mean_bias_pct']:+.3f} | {c['se_pct']:.3f} | "
              f"{c['edt_mean_pct']:+.3f} | {c['c80_mean_dB']:+.4f} | {'pass' if ok else '**fail**'} |")
        if mc.get("paired_noise_case_A_reported"):
            w("")
            w("Reported, not gated (the former 48 dB level): " + "; ".join(
                f"{c['f_c']:.0f} Hz / {c['T']} s: {c['mean_bias_pct']:+.3f} % (SE {c['se_pct']:.3f}), {c['unsuitable']} of {c['R']} unsuitable"
                for c in mc["paired_noise_case_A_reported"]) + ".")
        w("")
        w("Case B (125 Hz, T = 0.3 s, plateau regime; reported): " + "; ".join(
            f"{c['noise_below_dB']:.0f} dB: mean {c['mean_bias_pct']:+.1f} %, SD {c['sd_pct']:.0f} %, {c['unsuitable']} of {c['R']} unsuitable"
            for c in mc["paired_noise_case_B"]) + ".")
        if "leak_calibration" in mc:
            w("")
            w("Leak calibration (AX23; both meters' T30 bias, measured leak D, D₁ = D + 10·log10 r, two-term model):")
            w("")
            w("| f_c | neighbour | r | R | octave bias (%) | half-octave bias (%) | D (dB) | D₁ (dB) | model (%) | residual (pts) |")
            w("|---|---|---|---|---|---|---|---|---|---|")
            for c in mc["leak_calibration"]:
                w(f"| {c['f_c']:.0f} | {c['variant']} | {c['r']} | {c['R']} | {f(c['octave_bias_pct'], 2)} | {f(c['half_octave_bias_pct'], 2)} | "
                  f"{c['D_dB']:.1f} | {c['D1_dB']:.1f} | {c['model_bias_pct']:.2f} | {f(c['residual_pct'], 2)} |")
    # ---------------- scope 6 remainder (phase-05e session 2)
    scope6_section(w, res)
    path.write_text("\n".join(L) + "\n", encoding="utf-8")


SCOPE6 = HERE / "data" / "phase05_scope6.json"
COMP_TITLE = {
    "B11_B": "B11 (B): reference hybrid vs Phase 04 IR (rule handover)",
    "B10": "B10: hybrid with BRAS per-band s (diffuse and specular) vs broadband s",
    "B11_B_simE": "B11 (B) sensitivity (AX29): envelope scaled by the simulator's band energies (reported)",
    "handover80_hybrid": "Handover floor t_dir,e + 80 ms vs Phase 04 rule, on the reference-hybrid IR (arbiter)",
    "handover140_hybrid": "Handover floor t_dir,e + 140 ms vs Phase 04 rule, on the reference-hybrid IR (arbiter)",
    "handover80_phase04": "Handover floor + 80 ms vs rule, on the Phase 04 IR (reported)",
    "handover140_phase04": "Handover floor + 140 ms vs rule, on the Phase 04 IR (reported)",
}


def scope6_section(w, res: dict) -> None:
    """Phase-05 scope 6 comparisons that need the reference hybrid (tools/validation/scope6.py)."""
    w("")
    w("## 6. Reference hybrid (AX21), X-b bound (AX16), handover and the B11 (B) / B10 evidence (scope 6)")
    w("")
    if not SCOPE6.exists():
        w("Not computed (run `python tools/validation/scope6.py all`).")
        return
    s6 = json.loads(SCOPE6.read_text())
    w("Generated by `tools/validation/scope6.py` (data: `tools/validation/data/phase05_scope6.json`). Model against model "
      "and against BRAS: the reference hybrid (`tools/acoustics/ref_hybrid.py`) injects s(1−α) of the incident energy into "
      "the Lambert patch hit at each specular hit (Kuttruff Eq. 4.24; Gilbert, §4.6), propagates it with the mixed "
      "specular/diffuse form (Joyce's reflection matrix, Kuttruff §4.6 Eq. 4.35, with the §5.2 split: s re-radiated per "
      "Lambert, 1−s continuing specularly over the image patches) and gathers it at the listener (Eq. 4.29); 1 ms bins, "
      "AX4 air, patches as for a*. Checks: s = 1 decay equals a* and the particle Monte Carlo within 2 %; the Python "
      "t_mix,e and AX16 E_target equal `render_cli` (tools/acoustics/tests/test_ref_hybrid.py).")
    w("")
    bras = s6.get("bras", {})
    if bras:
        w("Hybrid runs: " + "; ".join(
            f"{room}: {r['info']['patches']} patches ({r['info']['patch_size_m']:.2f} m), {r['info']['bins']} bins, "
            f"{r['info']['lattice_images']} image cells, {r['info']['seconds']:.0f} s" for room, r in bras.items()) + ".")
        hv = bras.get("CR2", {}).get("halving")
        if hv:
            ch = [abs(x) for p in hv["pairs"].values() for i, x in enumerate(p["delta_lb_change_db"]) if i in (3, 4, 5)]
            ce = [abs(x) for p in hv["pairs"].values() for i, x in enumerate(p["diffuse_energy_change_rel"]) if i in (3, 4, 5)]
            w(f"Patch halving (CR2, initial α, {hv['info']['patches']} patches): ΔL_b changes by ≤ {max(ch):.3f} dB and the "
              f"diffuse energy before t_mix by ≤ {100 * max(ce):.2f} % at 500 Hz–2 kHz. CR3 and CR4 were not halved (memory: "
              f"at half the patch size the dense kernel needs ≈ 8× the RAM); a* convergence per room is in section 2.")
        w("")
    xb = s6.get("xb")
    if xb:
        w("### 6a. X-b bound ΔL_b = 10·log10(E_target(AX16) / E_target(hybrid)) (dB; Hann window [t_dir,e + 2.5 ms, t_mix,e], "
          "both referred to t_mix,e; deterministic, no statistical margin)")
        w("")
        verdict = ("**|ΔL_b| ≤ 1 dB everywhere: X-b accepted as is** (the bound is recorded in AX16)" if xb["accepted"] else
                   f"**|ΔL_b| > 1 dB in {xb['cases_over_1db']} of {xb['evaluated']} case-bands (500 Hz–2 kHz): phase-05b (B11) "
                   "switches tail-level matching to the hybrid's propagated diffuse energy** (AX16; even if early rendering is "
                   "not promoted, under the same independent-reference validation)")
        w(f"Reading: {verdict}. Largest |ΔL_b|: {xb['max_abs_db']:.2f} dB ({xb['max_case']}). This is model against "
          "model: it bounds what B11 would change, not a measured truth.")
        w("")
        w("| case | 63 | 125 | 250 | 500 | 1000 | 2000 | 4000 | 8000 | t_mix,e (ms) |")
        w("|---|---|---|---|---|---|---|---|---|---|")

        def row(label, d):
            w(f"| {label} | " + " | ".join(f(x, 2) for x in d["delta_lb_db"]) + f" | {1000 * d['mix_s']:.1f}"
              + (" (AX22 fallback)" if d.get("fallback") else "") + " |")
        for room, r in bras.items():
            for n, vs in r["pairs"].items():
                for vk in ("initial", "initial_bands_s", "fitted"):
                    if vk in vs:
                        row(f"{n} ({vk.replace('_', ' ')})", vs[vk])
        for n, d in s6.get("phase04_rooms", {}).items():
            row(f"{n} (Phase 04 test room, emitter L)", d)
        syn = s6.get("synthetic", {})
        for case, r in syn.get("table_5_2", {}).items():
            for k, d in r.items():
                if k.startswith("s="):
                    row(f"Table 5.2 layout {case}, {k} (all faces)", d)
        for k, d in (syn.get("s_cases") or {}).items():
            if k.startswith("s="):
                row(f"uniform α = 0.15, 20×30×10 m, {k} (AX16 exact: hit-count residual only)", d)
        w("")
        w("Positions of the synthetic cases: AX28 (the AQ10 benchmark room's listener and emitter L, scaled per axis for the "
          "10 m cube). Bands outside 500 Hz–2 kHz are for information; the 1 dB is G's jnd (Vorländer Table 6.1, stated for "
          "500–1000 Hz, applied by extension to 2 kHz).")
        w("")
    ens = s6.get("ensembles")
    if not ens:
        return
    w("### 6b. Seed-paired comparisons (EDT and C80, AQ9 error in jnd: mean of |sim − meas|/jnd over 500 Hz, 1 kHz, 2 kHz "
      "per pair, mean over pairs per room, then over rooms with equal weight)")
    w("")
    w("Δ̂ = error with the change − error of the base, paired on the same tail seeds. Validity: SE(Δ̂) ≤ δ/3 = 0.083 jnd, "
      "SE per room (and per pair for the handover (a)) ≤ 1/3 jnd; R from the pilot (n = 51) by R ≥ max(144·σ₁,Δ², "
      "9·σ₁,Δ,room², 9·σ₁,Δ,pair²), checked after the run. Jnds: EDT 5 %, C80 1 dB (Vorländer Table 6.1, 500–1000 Hz, "
      "extended to 2 kHz, AQ9). Room set: " + room_set_label(res) + ("." if all(r in room_set(res) for r in SELECTED)
      else ": the B11 promotion and any handover change are deferred (phase-05e scope (b))."))
    w("")
    for aset in ("initial", "fitted"):
        if aset not in ens:
            continue
        e = ens[aset]
        w(f"**{aset} α**" + (" (counted)" if aset == "initial" else " (reported only)") + f": R per arm = "
          f"{e['R_history'][-1]['R']} (pilot 51; R needed per comparison after the run: "
          + ", ".join(f"{k} {v}" for k, v in e["R_history"][-1]["by_comparison"].items()) + ").")
        w("")
        w("| comparison | metric | error base → with (jnd) | Δ̂ (jnd) | SE | per room Δ̂ (SE) | valid | reading |")
        w("|---|---|---|---|---|---|---|---|")
        for comp, c in e["comparisons"].items():
            rd = c["readings"]
            if comp == "B11_B":
                reading = "not worse (B11 (B) passes)" if rd["not_worse"] else "**worse or not valid** (B11 (B) fails)"
            elif comp == "B11_B_simE":
                reading = f"reported; not worse: {f(rd['not_worse'])}"
            elif comp == "B10":
                reading = "**B10 moves ahead of phase-05b**" if rd["b10_moves_ahead"] else "B10 stays after phase 12"
            elif comp.endswith("hybrid"):
                reading = ("**floor replaces the lower bound**" if rd["floor_replaces"] else
                           f"rule stands ((a) {f(rd['a_some_pair_moves'])}, (b) {f(rd['b_lowers'])}, (c) {f(rd['c_no_room_worse'])})")
            else:
                reading = f"reported; some pair moves > 1 jnd: {f(rd['a_some_pair_moves'])}"
            for met in ("EDT", "C80"):
                m = c["metrics"][met]
                rooms = "; ".join(f"{rm} {r['delta']:+.3f} ({r['se']:.3f})" for rm, r in m["room"].items())
                w(f"| {COMP_TITLE.get(comp, comp)} | {met} | {m['error_base_jnd']:.3f} → {m['error_with_jnd']:.3f} | "
                  f"{m['delta']:+.3f} | {m['se']:.3f} | {rooms} | {f(c['R_ok'])} | {reading if met == 'EDT' else ''} |")
        w("")
        w("In-range figure (500–1000 Hz mean; Vorländer Table 6.1 states these jnds for 500–1000 Hz only) and per-band Δ̂ "
          "(room-averaged; for the handover, per band whether the two handovers differ by more than 1 jnd):")
        w("")
        w("| comparison | metric | Δ̂ 500–1000 Hz (SE) | Δ̂ 500 Hz | Δ̂ 1 kHz | Δ̂ 2 kHz | bands with \\|Δ̂\\| > 1 jnd | pairs > 1 jnd per band (500 / 1k / 2k) |")
        w("|---|---|---|---|---|---|---|---|")
        for comp, c in e["comparisons"].items():
            if "in_range_500_1000" not in c:
                continue
            for met in ("EDT", "C80"):
                ir = c["in_range_500_1000"][met]
                pb = {k: c["per_band"][k][met] for k in ("500", "1000", "2000")}
                over = [k for k, v in pb.items() if abs(v["delta"]) > 1.0]
                w(f"| {COMP_TITLE.get(comp, comp)} | {met} | {ir['delta']:+.3f} ({ir['se']:.3f}) | "
                  + " | ".join(f"{pb[k]['delta']:+.3f}" for k in ("500", "1000", "2000"))
                  + f" | {', '.join(over) if over else 'none'} | "
                  + " / ".join(str(len(pb[k]["pairs_over_1jnd"])) for k in ("500", "1000", "2000")) + " |")
        w("")
        big = [(n, met, p["delta"]) for comp, c in e["comparisons"].items() if comp.startswith("handover")
               for met in ("EDT", "C80") for n, p in c["metrics"][met]["pair"].items() if abs(p["delta"]) > 1.0]
        if big:
            w("Pairs whose handover Δ̂ exceeds 1 jnd: " + "; ".join(f"{n} {met} {d:+.2f}" for n, met, d in big[:20]) + ".")
            w("")
    b11 = ens.get("initial", {}).get("comparisons", {}).get("B11_B")
    if b11:
        w("Per-room gain with the hybrid (B11 (B), initial α; gain = −Δ̂, jnd), sorted by each indicator (section 2; no threshold):")
        w("")
        rows = []
        for rk, r in res["rooms"].items():
            room, aset = rk.split("|")
            if aset != "initial" or room not in b11["metrics"]["EDT"]["room"]:
                continue
            ind = (sum(r["absorption_contrast"].values()) / 3, sum(r["largest_face_share"].values()) / 3,
                   sum(r["scattering"].values()) / 6)
            rows.append((room, ind, -b11["metrics"]["EDT"]["room"][room]["delta"], -b11["metrics"]["C80"]["room"][room]["delta"]))
        for i, lab in enumerate(("absorption contrast (mean 500 Hz–2 kHz)", "largest single-face share of A (mean 500 Hz–2 kHz)",
                                 "broadband s (mean over faces)")):
            w(f"- by {lab}: " + "; ".join(f"{rm} {ind[i]:.2f}: EDT {ge:+.3f}, C80 {gc:+.3f}"
                                            for rm, ind, ge, gc in sorted(rows, key=lambda x: x[1][i])))
        w("")
    w("**B11 not validated against measurement for uneven-α / low-s rooms**: no BRAS room in this set combines uneven α "
      "with low s (CR2: uniform α, low s; CR3 and CR4: one strong absorber, the seating, whose own s is high, "
      + seating_s_text(load_reduction(), [rm for rm in room_set(res) if ALPHA_GROUP.get(rm) == "uneven"])
      + " at 500 Hz / 1 / 2 kHz; F2; bras_mapping.md §5 classification).")
