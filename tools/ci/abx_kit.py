#!/usr/bin/env python3
"""Phase-07c-2 D-W2: the AX47 self-ABX stimulus kit, as pre-registered.

The design is decider file 13 (docs/review/phase-07c-2/13-decider-rebuttal-r4.md), "D-W2: final", items 1-16, and
its section "Q5: TSP step placement (pre-registered)"; interrogator file 14 (D-W2 SURVIVES). The listener's run
sheet is docs/validation/abx-07c-2-run-sheet.md. Every number this kit fixes from file 13 is a module constant
below, with its item.

    # noise chain (CI: tools/ci/listening_pack.py --phase phase-07c-2 calls build_noise_chain)
    python tools/ci/abx_kit.py noise  --out build/abx-07c-2
    # speech chain: local only (McGill TSP v2 is downloaded by our own SHA-256; no audio is ever committed)
    python tools/ci/abx_kit.py speech --out build/abx-07c-2 --speaker MA --files MA01_01 MA01_02
    # blinding (item 11): writes the session folder (A, B, X per trial) and the sealed key; prints the hashes
    python tools/ci/abx_kit.py seal   --pack build/abx-07c-2/noise --session <dir> --key <file outside it>
    # scoring (items 3, 4, 13): refuses to unseal a 0.5 dB block unless 0.9 dB was detected in that chain
    python tools/ci/abx_kit.py score  --key <file> --responses <csv> --chain noise

What is stepped (item 5): render_cli --abx-step-db g (validation only, like --no-air-absorption, AX4): a change
of g dB in the tail energy, uniform across the 8 bands, from a second IrSet of the same StagedBuild through
useDiffuseLevel, faded in with the shipped AQ4 30 ms equal-gain crossfade (AX18), rendered with
--realtime-emulation, fixed block, P = 512, the onset at a seeded partition boundary.

Assertions on every stimulus (item 6): early parts bit-identical (the IRs up to the tail's fade-in, and the render
before the onset); 10 log10(E(stepped - unstepped)/E(unstepped)) = 20 log10|10^(g/20) - 1| over the tail window;
the [ax47-midfade] checks (tests/unit/test_ax47_midfade.cpp: W-a windows and companions (i)-(iii)); the
tools.acoustics click detector finds no event in the step region; the per-band wet-output change, the window's
unscaled energy share (exact split, `window_unscaled_share`, asserted <= 2.3 %) and render_cli's E_target specular
share (`target_specular_share`) are printed, each under its own name (decider file 27, amendment 1; file 31, item 6).
Per g, on the heard IR pair: the tail-window share of the heard energy, Delta G and Delta C80 per band (Seat 1's
condition, file 27). M2 (files 31, 34): the manifest carries the heard-IR T30 with Seat 9's label, the tail T30
beside it and the minimum gap, and asserts minimum gap >= tail T30.

Speech (Q5): the onset <= 0.43 T30(1 kHz) after the end of speech, the rendered tail
>= the rendered floor (TSP's own noise) + 20 dB at the onset (1 kHz band, 50 ms window); a failing seeded onset
is replaced by the next seed index and the replacement recorded.
"""

from __future__ import annotations

import argparse
import copy
import csv
import hashlib
import io
import json
import math
import os
import pathlib
import secrets
import sys
import tempfile
import urllib.request
import zipfile

import numpy as np

REPO = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))

from tools.acoustics import bands, clicks, metrics, render_cli, signals, wav  # noqa: E402

# ---- Pre-registered numbers (file 13, "D-W2: final") ----
SCORED_TRIALS = 16  # item 2: 16 scored trials per test
ANCHOR_TRIALS = 6  # item 2: 6 interleaved anchor trials per block
ANCHOR_DB = 3.0  # item 2: a uniform 3 dB tail step
ANCHOR_PASS = 5  # item 2: pass at >= 5/6
BLOCK_TRIALS = 22  # item 2: blocks of 22 trials
BREAK_AFTER = 11  # item 2: a break at trial 11
LEVELS_DB = (0.9, 0.5)  # item 3: 0.9 dB, then (only if detected) 0.5 dB
CRITERION = {"noise": 12, "speech": 13}  # item 3: >= 12/16 (noise), >= 13/16 (speech)
FAMILY_ALPHA = 0.049  # item 3 / 13: FWER <= 0.0490 (strong, union bound)
POWER_AT_075 = {"noise": 0.63, "speech": 0.41}  # item 3 / 13 (0.405 rounded as item 13 writes it)
UP_PER_BLOCK = 8  # item 7: 8 up and 8 down per block, in random order
POST_STEP_S = 2.0  # item 7: at least 2 s of programme after the step
FS = 48000  # items 8-10: 48 kHz, no resampling
PARTITION = 512  # item 5: P = 512
BLOCK = 512  # item 5: fixed block
CROSSFADE_S = 0.030  # item 5: the shipped 30 ms AQ4 fade
W_CANDIDATES = (6, 7, 8)  # item 9: asserted capped at m = 6, 7 and 8
Q5_ONSET_MAX_T30 = 0.43  # Q5: onset no later than 0.43 T30(1 kHz) after the end of speech
Q5_MARGIN_DB = 20.0  # Q5: tail >= floor + 20 dB at the onset
Q5_BAND_HZ = 1000.0  # Q5: the 1 kHz band
Q5_WINDOW_S = 0.050  # Q5: 50 ms window

# ---- Kit choices (not in file 13; recorded in every manifest and on the run sheet) ----
TAIL_SEED = 12345  # item 9 "fixed tailSeed": the value the scene carries (medium_room.json's)
KEY_SEED_BLOCKS = {"noise": 7001, "speech": 7002}  # seeds of the trial plans (directions, anchor slots, onsets)
NOISE_BURST_S = 1.0  # pulsed pink noise: burst length (rounded to whole partitions)
NOISE_LEVEL_DBFS = -8.0  # pink-noise burst RMS before the room (fixed for the whole chain, item 10)
SPEECH_GAIN_DB = 0.0  # TSP samples as recorded (int16 full scale = 1.0), no scaling
FADE_S = 0.005  # raised-cosine edges of each noise burst
LEAD_BLOCKS = 8  # silent lead-in before the programme, in partitions, plus the seeded offset
ONSET_SEED_RANGE = 32  # noise: the onset's seeded offset in partitions, 0..31
END_OF_SPEECH_DB = 15.0  # end of speech: the last 10 ms frame above TSP's noise floor + 15 dB
MAX_PEAK_DBFS = -1.0  # no normalisation (item 10): a stimulus peaking above this fails the build
U = 2.0**-24  # float32 unit roundoff, as test_ax47_midfade.cpp uses it
S_W_MAX = 0.023  # file 34 item 1: the ISM fade-out's unscaled share s_w of [t_mix,e, L), inside the 0.1 dB tolerance
C80_S = 0.080  # Vorlaender Eq. 6.7: early [0, 80 ms), late [80 ms, end of the IR file) (file 29, method 5)
# M2 T-a, Seat 9's label for the heard-IR T30 (decider files 27, 31, 34): printed beside the tail's own T30
HEARD_T30_LABEL = "heard-IR T30, ISO fit spanning the AX21 gap, not a decay rate"

# ---- McGill TSP speech database, version 2 (2018-11), Simplified BSD; docs/THIRD_PARTY.md ----
TSP_URL = "https://mmsp.ece.mcgill.ca/Documents/Data/TSP-Speech-Database/48k.zip"
TSP_SHA256 = "9cfb3a3a13014c8ff90770a5d1923f376da73ac927b9100f09826f60cf06cf43"  # our own, 2026-11-22
TSP_SIZE = 253816919
TSP_LICENCE_URL = "https://mmsp.ece.mcgill.ca/Documents/Data/TSP-Speech-Database/Licence.html"
TSP_NOTICE = (
    "McGill TSP Speech Database, Version 2 (2018-11), P. Kabal, McGill University. Copyright (c) 2018 Peter "
    "Kabal. All rights reserved. Redistribution and use in source and binary forms, with or without "
    "modification, are permitted provided that the conditions of the Simplified BSD licence are met; see "
    + TSP_LICENCE_URL
    + ". THE DATA IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" AND ANY EXPRESS OR IMPLIED "
    "WARRANTIES ARE DISCLAIMED. Rendered (convolved) through the Spatial Scene engine for an internal listening test."
)


def sha256_file(path: pathlib.Path) -> str:
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


# ---------------------------------------------------------------------------------------------------------
# Scene (item 9)
# ---------------------------------------------------------------------------------------------------------


# K4's candidate placements (decider file 29; tests/unit/test_diffuse_wsweep.cpp L75-107): listener, emitter S0, or
# None for the default position (listener R0 (10, 8, 1.7), emitters S0 (7, 20, 2) and S1 (13, 20, 2)).
PLACEMENTS = {
    "default": (None, None),
    "listener_wall": ((10.0, 0.1, 1.7), None),
    "listener_edge": ((0.1, 0.1, 1.7), None),
    "listener_corner": ((0.1, 0.1, 9.9), None),
    "emitter_wall": (None, (7.0, 29.9, 2.0)),
    "both_wall": ((10.0, 0.1, 1.7), (7.0, 29.9, 2.0)),
    "both_corner": ((0.1, 0.1, 0.1), (19.9, 29.9, 9.9)),
}
# Kuttruff Table 5.2 layouts as test_diffuse_wsweep.cpp builds them: the one face at alpha 1.
LAYOUT_FACE = {4: "floor", 5: "xMin"}
DEFAULT_SCENE = "layout4_s1/default"
# Item 9 labels (phase-07c-2b M3-4, decider files 2 and 6; Seat 9's drafts, file 27's S-A text with the D/R corrected).
# The superseded item-9 wording is gone everywhere (decider file 27; PRD L133: all spaces are empty).
SCENE_LABELS: dict[str, str] = {
    "layout4_s1/default": (
        "layout4_s1/default: 20 x 30 x 10 m, walls and ceiling alpha 0.01, floor alpha 1, scattering 1 on every face. "
        "Direct-dominated: D/R at 1 kHz +10.7 / +9.7 dB per emitter, +13.1 dB heard, against -10.8 dB in a diffuse "
        "field at r/r_c 3.47 (Kuttruff Eq. 5.44, A ~ 640 m^2). Early part empty under AX21. Tail target is the Eyring "
        "T60, 1.29 s at 1 kHz: a diffuse target, not a room prediction. Tail measured T30 1.25-1.27 s. Not a "
        "validated preset."),
    # M3-4 final texts (phase-07c-2b decider file 6), verbatim.
    "layout4_s1/both_wall": (
        'layout4_s1/both_wall: 20 × 30 × 10 m, 6,000 m³, walls and ceiling α 0.01, floor α 1, scattering 1 on '
        'every face. Listener 0.1 m from the y = 0 wall, emitter L 0.1 m from the y = 30 m wall; '
        'listener–emitter 29.95 / 20.13 m (L / R). The reflections off those faces (delay about 0.58 ms; '
        'first interference notch near 0.86 kHz) are absent at s = 1 (AX21; Kuttruff Eq. 8.59), so the direct '
        "sound's tone colour is not room-like and the scene represents no seat. D/R at 1 kHz −7.7 / +5.2 dB "
        "per emitter, −5.3 dB heard (emitter L's direct arrives 28.6 ms after R's and counts as reflected); "
        'diffuse field −18.5 / −15.0 dB at r/r_c 8.39 / 5.64 (r_c 3.57 m, A ≈ 640 m²; Kuttruff Eqs. '
        '5.44–5.45; indicative only: ᾱ ≈ 0.28 is not small, Kuttruff §5.6). Tail onsets t_mix,e 0.165 / 0.380 '
        's; at equal times the two tails agree within 0.05 dB at 1 kHz, and the tail share 0.667 at 1 kHz '
        "rests on L's earlier onset. Early part empty (AX21). Heard-IR T30 1.370 s, tail T30 1.313 / 1.274 s. "
        'Not a validated preset.'),
    "layout4_s0.7/default": (
        'layout4_s0.7/default: 20 × 30 × 10 m, 6,000 m³, walls and ceiling α 0.01, floor α 1 (no floor '
        'reflection, unlike a real floor), scattering 0.7 on every face. D/R at 1 kHz +1.5 / +1.3 dB per '
        'emitter, +1.7 dB heard, against −10.8 dB in a diffuse field at r/r_c 3.47 (r_c 3.57 m, A ≈ 640 m²; '
        'Kuttruff Eqs. 5.44–5.45; indicative only: ᾱ ≈ 0.28 is not small, Kuttruff §5.6). Early part present '
        'but specular-only (partial AX21): first image (ceiling) about 23.6 ms after the direct sound; '
        'broadband early energy −3.8 dB re direct; the step at t_mix,e is printed. Tail target Eyring 1.29 s '
        'at 1 kHz, a diffuse target, not a room prediction; heard-IR T30 1.831 s spans early part and tail; '
        'tail T30 1.254 / 1.274 s. Not a validated preset.'),
}
# The two scenes the AX47 self-ABX decides on (M3-1, V1-W), in sitting order: S-W, then S-B*.
ABX_SCENES = ("layout4_s1/both_wall", "layout4_s0.7/default")


def parse_scene_name(name: str) -> tuple[int, float, str]:
    """`layout<4|5>_s<s>/<placement>`, e.g. layout4_s0.7/default, layout4_s1/both_wall."""
    head, placement = name.split("/")
    layout, s = head.split("_s")
    lay = int(layout.removeprefix("layout"))
    if lay not in LAYOUT_FACE or placement not in PLACEMENTS:
        raise ValueError(f"unknown ABX scene {name!r}")
    return lay, float(s), placement


def make_scene(name: str) -> dict:
    """An ABX candidate scene (K4, file 29): 20 x 30 x 10 m, every face alpha 0.01 except the layout's face at
    alpha 1, uniform scattering s on every face, medium_room.json's other fields, fixed tailSeed."""
    lay, s_coef, placement = parse_scene_name(name)
    scene = copy.deepcopy(json.loads((REPO / "tests" / "scenes" / "valid" / "medium_room.json").read_text()))
    scene["room"]["geometry"]["dimensions"] = [20.0, 30.0, 10.0]
    for face in ("xMin", "xMax", "yMin", "yMax", "floor", "ceiling"):
        scene["room"]["surfaces"][face] = {"absorption": [1.0 if face == LAYOUT_FACE[lay] else 0.01] * 8,
                                           "scattering": s_coef}
    lst, s0 = PLACEMENTS[placement]
    scene["listener"]["position"] = list(lst or (10.0, 8.0, 1.7))
    scene["emitters"][0]["position"] = list(s0 or (7.0, 20.0, 2.0))
    scene["emitters"][1]["position"] = [13.0, 20.0, 2.0]
    scene["render"]["tailSeed"] = TAIL_SEED
    return scene


def scene_layout4_s1_default() -> dict:
    """`layout4_s1/default` (S-A): Kuttruff Table 5.2 layout 4 at s = 1 (the floor alpha 1)."""
    return make_scene(DEFAULT_SCENE)


def scene_label(name: str) -> str:
    """Item 9's label for a sealed scene (decided in phase-07c-2b M3); a scene without one cannot be built."""
    if name not in SCENE_LABELS:
        raise RuntimeError(f"{name}: no item-9 label decided for this scene (M3); the kit stops")
    return SCENE_LABELS[name]


def _run(binary: pathlib.Path, *args) -> str:
    r = render_cli.run(binary, *args)
    if r.returncode != 0:
        raise RuntimeError(f"render_cli {' '.join(map(str, args))} failed ({r.returncode}):\n{r.stderr}")
    return r.stdout


def check_scene(binary: pathlib.Path, scene_path: pathlib.Path, work: pathlib.Path, log=print,
                name: str = DEFAULT_SCENE) -> dict:
    """Item 9: capped at m = 6, 7 and 8 (asserted); r/r_c and D/R printed; T30(1 kHz) of the heard IR."""
    out: dict = {"name": name, "label": scene_label(name),
                 "scene_sha256": sha256_file(scene_path), "tailSeed": TAIL_SEED, "capped": {}}
    for m in W_CANDIDATES:
        diag = work / f"diag_m{m}.json"
        _run(binary, "--scene", scene_path, "--mode", "omni", "--w-multiplier", m, "--diagnostics", diag)
        d = json.loads(diag.read_text())
        hits = [bool(e["diffuse"]["capHit"]) for e in d["emitters"]]
        out["capped"][str(m)] = hits
        if not all(hits):
            raise RuntimeError(f"{name} is not capped at m = {m} (cap hit per emitter {hits}): item 9; the kit stops")
    diag = work / "diag.json"
    ir_path = work / "ir.wav"
    _run(binary, "--scene", scene_path, "--mode", "omni", "--diagnostics", diag, "--ir", ir_path)
    d = json.loads(diag.read_text())
    ir, fs = wav.read(ir_path)
    heard = ir[:, 0] + ir[:, 2]  # the programme feeds both emitters (a centred source); omni: output 0 = output 1
    m = metrics.room_metrics(heard, fs)
    t30 = m["bands"]["1000"]["T30"]
    if t30 is None:
        raise RuntimeError("T30(1 kHz) of the scene IR could not be measured")
    scene = json.loads(scene_path.read_text())
    lst = np.asarray(scene["listener"]["position"])
    volume = float(d["volume"])
    out["T30_1k_s"] = float(t30)
    out["T30_1k_s_label"] = HEARD_T30_LABEL
    out["T60_eyring_1k_s"] = float(d["t60"][4])
    # Critical distance r_c = 0.057 sqrt(V / T) (omni source, g = 1: Kuttruff Eq. 5.44, 0.1 sqrt(V / (pi T)), stated
    # there with Sabine's T; here with the diffuse target's Eyring T60; print only).
    rc = 0.057 * math.sqrt(volume / float(d["t60"][4]))
    out["r_c_m_T30"] = 0.057 * math.sqrt(volume / float(t30))  # the same with the heard IR's T30 (file 21, 2b)
    out["emitters"] = []
    for e, em in zip(d["emitters"], scene["emitters"]):
        r = float(np.linalg.norm(np.asarray(em["position"]) - lst))
        out["emitters"].append({"id": e["id"], "r_m": r, "r_over_rc": r / rc, "capHit_shipped": e["diffuse"]["capHit"],
                                **emitter_ir_metrics(ir[:, e["channel"] * 2], fs, e, d)})
    out["r_c_m"] = rc
    out["r_c_forms"] = ("r_c_m: Kuttruff Eq. 5.44's approximate form 0.057 sqrt(V / T) with the Eyring T60; the item-9 "
                        "labels use r_c = sqrt(A / 16 pi) with A ~ 640 m^2 (3.57 m), decider file 6 M3-4")
    out["tail_spread"] = tail_spread(ir, fs, d)
    ts = out["tail_spread"]
    log(f"scene {name}: tail spread (1 kHz, emitter {ts['emitters'][0]} - {ts['emitters'][1]}) "
        + ", ".join(f"[{w[0]}, {w[1]}) s {v:+.2f} dB" for w, v in zip(ts["windows_s"], ts["L_minus_R_db"]))
        + f"; t_mix,e {', '.join(f'{x:.3f}' for x in ts['t_mix_s'])} s")
    if ts["exceeds_1db"] and SPREAD_CLAUSE not in out["label"]:
        raise RuntimeError(f"{name}: emitter tails differ by more than 1 dB at equal times ({ts['L_minus_R_db']}); the "
                           "label's SPREAD clause and an NFR-8 report to Seat 2 are required (decider file 6, M3-1 (a))")
    out["tail_T30_1k_s"] = [x["tail_T30_1k_s"] for x in out["emitters"]]  # per emitter, from t_mix,e (beside T30_1k_s)
    # The heard IR (both emitters summed): at equal r the two direct sounds coincide and add coherently, the tails
    # do not, so this D/R is about 3 dB above each emitter's own (decider file 21, 2b; file 22). The per-emitter D/R
    # (single-emitter IR, AX13) is the one to set against r/r_c.
    out["DRR_basis"] = "heard IR: emitters L + R summed (the programme feeds both); per-emitter D/R under emitters"
    out["DRR_dB_broadband"] = m["broadband"].get("DRR")
    out["DRR_dB_1k"] = m["bands"]["1000"].get("DRR")
    out["diagnostics"] = d
    log(f"scene {name}: capped at m = 6, 7, 8 ({out['capped']}); T30(1 kHz) {t30:.3f} s "
        f"({HEARD_T30_LABEL}; tail T30 {', '.join(_fmt(x, 3) for x in out['tail_T30_1k_s'])} s) "
        f"(Eyring T60 {out['T60_eyring_1k_s']:.3f} s); r_c {rc:.2f} m ({out['r_c_m_T30']:.2f} m from the heard T30); "
        + "; ".join(f"emitter {x['id']} r {x['r_m']:.2f} m r/r_c {x['r_over_rc']:.2f} D/R {_fmt(x['DRR_dB_broadband'])} dB "
                    f"(1 kHz {_fmt(x['DRR_dB_1k'])} dB), tail-alone T30(1 kHz) {_fmt(x['tail_T30_1k_s'], 3)} s"
                    for x in out["emitters"])
        + f"; heard (L + R) D/R broadband {_fmt(out['DRR_dB_broadband'])} dB, 1 kHz {_fmt(out['DRR_dB_1k'])} dB")
    return out


def _fmt(x, digits: int = 1) -> str:
    return "None" if x is None else f"{x:.{digits}f}"


SPREAD_WINDOWS_S = ((0.45, 0.65), (0.8, 1.0))  # file 5's absolute windows, after every layout-4 t_mix,e
SPREAD_CLAUSE = "Emitter tails at the listener differ by"  # Seat 9's SPREAD clause (decider file 6, M3-4 template)


def tail_spread(ir: np.ndarray, fs: float, diag: dict) -> dict:
    """M3-1 (a) (phase-07c-2b decider file 6): the two emitters' diffuse tails at the listener at equal absolute times,
    1 kHz octave, over file 5's windows; > 1 dB (Vorlaender Table 6.1, the jnd for G) fires the SPREAD clause."""
    em = diag["emitters"][:2]
    lv = []
    for e in em:
        b = bands.filter_band(ir[:, e["channel"] * 2].astype(np.float64), fs, 1000)
        lv.append([10 * math.log10(float(np.sum(b[int(w0 * fs) : int(w1 * fs)] ** 2)) + 1e-300)
                   for w0, w1 in SPREAD_WINDOWS_S])
    diff = [a - b for a, b in zip(lv[0], lv[1])]
    return {"emitters": [e["id"] for e in em], "t_mix_s": [float(e["mixS"]) for e in em],
            "windows_s": [list(w) for w in SPREAD_WINDOWS_S], "L_minus_R_db": diff,
            "exceeds_1db": bool(max(abs(x) for x in diff) > 1.0)}


def emitter_ir_metrics(h: np.ndarray, fs: float, e: dict, diag: dict) -> dict:
    """One emitter's own omni IR (print only; decider file 21, 2b): D/R (AX13) broadband and at 1 kHz; T30 and EDT
    (1 kHz) of the whole IR; T30 and EDT (1 kHz) of the tail alone, from t_mix,e, beside the diffuse target's T60.
    The whole-IR T30 includes the empty stretch between the direct sound and t_mix,e (AX21: specular-only early part,
    scattering 1 on every face here), so it reads longer than the tail's own decay (file 22)."""
    h = np.asarray(h, dtype=np.float64)
    whole = metrics.room_metrics(h, fs)
    mix = int(math.ceil((e["mixS"] - diag["alignmentShiftS"]) * fs))
    tail = metrics.room_metrics(h[mix:], fs)
    return {"DRR_dB_broadband": whole["broadband"].get("DRR"), "DRR_dB_1k": whole["bands"]["1000"].get("DRR"),
            "T30_1k_s": whole["bands"]["1000"]["T30"], "EDT_1k_s": whole["bands"]["1000"]["EDT"],
            "t_mix_s": float(e["mixS"]), "tail_T30_1k_s": tail["bands"]["1000"]["T30"],
            "tail_EDT_1k_s": tail["bands"]["1000"]["EDT"], "target_T60_1k_s": float(diag["t60"][4]),
            "tmix_step_db": tmix_step_db(h, fs, mix)}


def tmix_step_db(h: np.ndarray, fs: float, mix: int) -> dict:
    """Print only (phase-07c-2b M3-1, Seats 2 and 3): the AX21 step / dip at t_mix,e, broadband and per octave band:
    10 log10 of the energy over [t_mix,e + 2.5 ms, t_mix,e + 20 ms) against [t_mix,e - 20 ms, t_mix,e - 2.5 ms)
    (positive: the tail onset is louder than the specular early part just before it)."""
    g, w = int(round(0.0025 * fs)), int(round(0.020 * fs))
    if mix - w < 0 or mix + w > h.size:
        return {"broadband": None, "bands": {}}

    def step(x: np.ndarray) -> float | None:
        pre, post = float(np.sum(x[mix - w : mix - g] ** 2)), float(np.sum(x[mix + g : mix + w] ** 2))
        return 10 * math.log10(post / pre) if pre > 0 and post > 0 else None

    return {"broadband": step(h),
            "bands": {bands.band_key(fc): step(bands.filter_band(h, fs, fc))
                      for fc in bands.OCTAVE_BANDS_HZ}}


# ---------------------------------------------------------------------------------------------------------
# IR pair checks (item 6, first two bullets)
# ---------------------------------------------------------------------------------------------------------


def ir_pair(binary: pathlib.Path, scene_path: pathlib.Path, g: float,
            work: pathlib.Path) -> tuple[np.ndarray, np.ndarray, dict]:
    """The unstepped and stepped IR (float32) and render_cli's own print of E_target's specular share per emitter
    and band (`target_specular_share`: E_spec / (E_spec + E_diff) of the tail target, not a share of the window)."""
    u, s = work / f"ir_unstepped.wav", work / f"ir_stepped_{g:+.2f}.wav"
    stdout = _run(binary, "--scene", scene_path, "--mode", "omni", "--abx-step-db", repr(float(g)), "--ir", u,
                  "--abx-stepped-ir", s)
    return wav.read_float32(u)[0], wav.read_float32(s)[0], parse_target_specular_share(stdout)


def parse_target_specular_share(stdout: str) -> dict[int, list[float]]:
    """render_cli --abx-step-db's line "abx step: emitter E g G dB; specular share of E_target per band: v1 .. v8"."""
    out: dict[int, list[float]] = {}
    marker = "specular share of E_target per band:"
    for line in stdout.splitlines():
        if line.startswith("abx step: emitter ") and marker in line:
            emitter = int(line.split()[3])
            out[emitter] = [float(v) for v in line.split(marker, 1)[1].split()]
            assert len(out[emitter]) == len(bands.OCTAVE_BANDS_HZ), line
    return out


def unscaled_part(u: np.ndarray, s: np.ndarray, g: float) -> np.ndarray:
    """K3's exact split (decider file 27; file 25, method 5b): with IR = N + T and stepped = N + a T, a = 10^(g/20),
    the part that does not scale is N = (a u - s) / (a - 1)."""
    a = 10.0 ** (g / 20.0)
    return (a * u - s) / (a - 1.0)


def ir_assertions(unstepped: np.ndarray, stepped: np.ndarray, diag: dict, g: float) -> dict:
    """The IR-level part of item 6, per emitter and output channel: the early part bit-identical up to the tail's
    fade-in (t_mix,e - 2.5 ms), the stated step over the tail window [t_mix,e, L) (AX47's) and over the tail alone
    [t_mix,e + 2.5 ms, L); the window's unscaled share s_w = E(N)/E(u), N from the exact split (asserted <= S_W_MAX
    on [t_mix,e, L), file 34 item 1)."""
    fs = float(diag["sampleRate"])
    half = int(round(0.0025 * fs))
    expected = 20.0 * math.log10(abs(10.0 ** (g / 20.0) - 1.0))
    rows = []
    for e in diag["emitters"]:
        mix = int(math.ceil((e["mixS"] - diag["alignmentShiftS"]) * fs))
        for o in range(2):
            c = e["channel"] * 2 + o
            u = unstepped[:, c].astype(np.float64)
            s = stepped[:, c].astype(np.float64)
            differ = np.flatnonzero(unstepped[:, c].view(np.uint32) != stepped[:, c].view(np.uint32))
            first = int(differ[0]) if differ.size else len(u)
            assert first + half >= mix, f"emitter {e['channel']} output {o}: the early part differs at tap {first} < t_mix - 2.5 ms"
            assert differ.size, f"emitter {e['channel']} output {o}: the stepped IR equals the unstepped one"
            res = {}
            for name, start in (("ax47_window", mix), ("tail_alone", mix + half)):
                eu, es, ed = (np.sum(u[start:] ** 2), np.sum(s[start:] ** 2), np.sum((s[start:] - u[start:]) ** 2))
                en = np.sum(unscaled_part(u[start:], s[start:], g) ** 2)
                res[name] = {"start_tap": start, "length": len(u) - start, "step_db": 10 * math.log10(es / eu),
                             "diff_db": 10 * math.log10(ed / eu), "window_unscaled_share": float(en / eu)}
            # D-W2 item 6, stated tolerances: 0.01 dB on the tail alone (exact up to float32 rounding); 0.1 dB over
            # [t_mix,e, L), which also holds the early part's 2.5 ms fade-out: inside it while s_w <= 2.3 % (file 34).
            assert res["ax47_window"]["window_unscaled_share"] <= S_W_MAX, (e["channel"], o, res, S_W_MAX)
            assert abs(res["tail_alone"]["diff_db"] - expected) <= 0.01, (e["channel"], o, res, expected)
            assert abs(res["tail_alone"]["step_db"] - g) <= 0.01, (e["channel"], o, res, g)
            assert abs(res["ax47_window"]["diff_db"] - expected) <= 0.1, (e["channel"], o, res, expected)
            rows.append({"emitter": e["channel"], "output": o, "first_differing_tap": first, "t_mix_tap": mix,
                         "expected_diff_db": expected, **res})
    return {"g_db": g, "rows": rows}


def ir_band_shares(unstepped: np.ndarray, stepped: np.ndarray, diag: dict, g: float,
                   target_share: dict[int, list[float]]) -> list[dict]:
    """Per emitter and band (print only; file 27, "specular_share print"): the window's unscaled share
    `window_unscaled_share` = E(N)/E(u) over [t_mix,e, L), N from the exact split, per band and broadband; beside it,
    under its own name, render_cli's `target_specular_share` (E_target's specular share, a level target, not a
    waveform in the window); and the step measured per band."""
    fs = float(diag["sampleRate"])
    out = []
    for e in diag["emitters"]:
        mix = int(math.ceil((e["mixS"] - diag["alignmentShiftS"]) * fs))
        c = e["channel"] * 2
        u, s = unstepped[:, c].astype(np.float64), stepped[:, c].astype(np.float64)
        n = unscaled_part(u, s, g)
        shares = target_share.get(e["channel"])
        row = {"emitter": e["channel"],
               "window_unscaled_share_broadband": float(np.sum(n[mix:] ** 2) / np.sum(u[mix:] ** 2)), "bands": {}}
        for i, fc in enumerate(bands.OCTAVE_BANDS_HZ):
            ub, sb, nb = (bands.filter_band(x, fs, fc)[mix:] for x in (u, s, n))
            eu = np.sum(ub**2)
            row["bands"][bands.band_key(fc)] = {"step_db": 10 * math.log10(np.sum(sb**2) / eu),
                                                "window_unscaled_share": float(np.sum(nb**2) / eu),
                                                "target_specular_share": None if shares is None else shares[i]}
        out.append(row)
    return out


def _c80_db(x: np.ndarray, early_end: int) -> float:
    early, late = float(np.sum(x[:early_end] ** 2)), float(np.sum(x[early_end:] ** 2))
    return 10 * math.log10(early / late)


def heard_pair_metrics(unstepped: np.ndarray, stepped: np.ndarray, fs: float, g: float) -> dict:
    """Print only (Seat 1's condition, decider file 27; method of file 29, step 5), on the heard IR pair
    hu = u[:, 0] + u[:, 2], hs = s[:, 0] + s[:, 2], broadband and per band (`bands.filter_band_with_lead`, so the
    zero-phase filter's pre-ringing is kept): the tail-window share of the heard energy E(T)/E(hu), with
    T = (hs - hu)/(a - 1) the part that scales; Delta G = 10 log10(E(hs)/E(hu)) over the whole IR;
    Delta C80 = C80(hs) - C80(hu), C80 per Vorlaender Eq. 6.7, t = 0 at the broadband onset of hu (ISO 3382-1's
    -20 dB rule), late window 80 ms to the end of the IR file (no noise floor, so no Lundeby truncation)."""
    hu = unstepped[:, 0].astype(np.float64) + unstepped[:, 2].astype(np.float64)
    hs = stepped[:, 0].astype(np.float64) + stepped[:, 2].astype(np.float64)
    a = 10.0 ** (g / 20.0)
    onset = metrics.onset_index(hu)
    n80 = int(round(C80_S * fs))

    def one(xu: np.ndarray, xs: np.ndarray, lead: int) -> dict:
        eu = float(np.sum(xu**2))
        tail = (xs - xu) / (a - 1.0)
        b = lead + onset + n80
        return {"tail_share_of_heard": float(np.sum(tail**2)) / eu,
                "delta_G_db": 10 * math.log10(float(np.sum(xs**2)) / eu),
                "delta_C80_db": _c80_db(xs, b) - _c80_db(xu, b)}

    out = {"basis": "heard IR: emitters L + R summed (output 0)", "onset_tap": onset, "broadband": one(hu, hs, 0),
           "bands": {}}
    for fc in bands.OCTAVE_BANDS_HZ:
        (bu, lead), (bs, _) = bands.filter_band_with_lead(hu, fs, fc), bands.filter_band_with_lead(hs, fs, fc)
        out["bands"][bands.band_key(fc)] = one(bu, bs, lead)
    return out


# ---------------------------------------------------------------------------------------------------------
# Stimulus checks (item 6, the rest)
# ---------------------------------------------------------------------------------------------------------


def midfade_checks(o: np.ndarray, a: np.ndarray, b: np.ndarray, s0: int, fs: float) -> dict:
    """The AX47 mid-fade checks of tests/unit/test_ax47_midfade.cpp (D-B3 items 2-3) on one stimulus: o the
    stepped render, a the unstepped render, b the stepped IR rendered alone from sample 0 (float32 arrays)."""
    L = int(round(CROSSFADE_S * fs))
    nw = int(round(0.001 * fs))
    out = {"windows": 0, "skipped": 0, "worst_window_ratio": 0.0}
    for ch in range(o.shape[1]):
        oc, ac, bc = (x[:, ch].astype(np.float64) for x in (o, a, b))
        # W-a: 1 ms windows aligned to s0 over [s0 - 4 N_w, s0 + L + 4 N_w)
        bound = (1.0 + nw / L) ** 2 * (1.0 + 1e-5)
        for w0 in range(s0 - 4 * nw, s0 + L + 4 * nw, nw):
            eo, ea, eb = (float(np.sum(x[w0 : w0 + nw] ** 2)) for x in (oc, ac, bc))
            m = max(ea, eb)
            if m < nw * 1e-10:  # below -100 dB re full scale: skipped, counted
                out["skipped"] += 1
                continue
            out["windows"] += 1
            out["worst_window_ratio"] = max(out["worst_window_ratio"], eo / m)
            assert eo <= bound * m, f"channel {ch} window {w0}: E_out {eo} > {bound} max(E_a, E_b) {m}"
        seg = slice(s0, s0 + L)
        aa, bb, oo = np.abs(ac[seg]), np.abs(bc[seg]), oc[seg]
        # (i) per-sample bound
        assert np.all(np.abs(oo) <= np.maximum(aa, bb) + 8 * U * (aa + bb)), f"channel {ch}: companion (i) fails"
        # (ii) reconstruction, j = t - s0 in double; o == 0 where |a| + |b| == 0
        j = np.arange(L, dtype=np.float64)
        rec = (1.0 - j / L) * ac[seg] + (j / L) * bc[seg]
        assert np.all(np.abs(oo - rec) <= 8 * U * (aa + bb)), f"channel {ch}: companion (ii) fails"
        assert np.all(oo[(aa + bb) == 0.0] == 0.0), f"channel {ch}: companion (ii) (silence) fails"
        # (iii) outside [s0, s0 + L) the output equals the end point rendered alone, bit for bit
        assert np.array_equal(o[:s0, ch].view(np.uint32), a[:s0, ch].view(np.uint32)), f"channel {ch}: before s0"
        assert np.array_equal(o[s0 + L :, ch].view(np.uint32), b[s0 + L :, ch].view(np.uint32)), f"channel {ch}: after the fade"
    return out


HFW_FRAME_S = 0.002  # M3-3 (phase-07c-2b decider file 2): HF-W frames of 2 ms, aligned to the step onset
HFW_MARGIN_S = 0.005  # HF-W region [s0 - 5 ms, s0 + L + 5 ms)
HFW_SKIP = 1e-9  # a frame with max(E_a, E_b) < n_f * 1e-9 is skipped and counted


def hfw_beta(fs: float) -> float:
    """HF-W's bound (M3-3): the W-a derivation on the high-passed signals, (1 + n_f / L)^2 (1 + 1e-5); 1.1378 at
    48 kHz (0.561 dB). Never fitted to data."""
    nf = int(round(HFW_FRAME_S * fs))
    L = int(round(CROSSFADE_S * fs))
    return (1.0 + nf / L) ** 2 * (1.0 + 1e-5)


def hf_w_check(o: np.ndarray, a: np.ndarray, b: np.ndarray, s0: int, fs: float) -> dict:
    """HF-W (phase-07c-2b M3-3; Seat 3's design, Seat 5's asserted-form rules): no broadband high-frequency excess
    of the stepped stimulus o over both fixed-IR end points, a (unstepped) and b (the stepped IR rendered alone).
    h = `clicks.highpass` (2 kHz, order 8, zero-phase); frames of n_f = 2 ms aligned to s0 over [s0 - 5 ms,
    s0 + L + 5 ms) on every output channel; asserted E_o <= beta max(E_a, E_b) per frame. A pure float64 function
    of the three renders: no RNG, no clock. A red is a stop (never a rerun, beta never fitted)."""
    nf = int(round(HFW_FRAME_S * fs))
    L = int(round(CROSSFADE_S * fs))
    margin = int(round(HFW_MARGIN_S * fs))
    beta = hfw_beta(fs)
    out = {"beta": beta, "frames": 0, "skipped": 0, "worst_ratio": 0.0, "worst_frame_start": None}
    # Frames aligned to s0: whole frames covering [s0 - margin, s0 + L + margin)
    first = s0 - -(-margin // nf) * nf
    last = s0 + L + margin
    for ch in range(o.shape[1]):
        ho, ha, hb = (clicks.highpass(x[:, ch].astype(np.float64), fs) for x in (o, a, b))
        for f0 in range(max(first, 0), min(last, o.shape[0] - nf + 1), nf):
            eo, ea, eb = (float(np.sum(h[f0 : f0 + nf] ** 2)) for h in (ho, ha, hb))
            m = max(ea, eb)
            if m < nf * HFW_SKIP:
                # Seat 5's condition D (round 2, file 4-seat5): a skipped frame must stay near-silent in o too, so
                # a click in a near-silent frame (a speech pause) still fails
                out["skipped"] += 1
                assert eo <= beta * nf * HFW_SKIP, (f"HF-W: channel {ch} skipped frame s0{f0 - s0:+d}: E_o {eo:.4e} "
                                                    f"> beta n_f 1e-9 {beta * nf * HFW_SKIP:.4e}")
                continue
            out["frames"] += 1
            r = eo / m
            if r > out["worst_ratio"]:
                out["worst_ratio"], out["worst_frame_start"] = r, f0 - s0
            assert eo <= beta * m, (f"HF-W: channel {ch} frame s0{f0 - s0:+d}: E_o {eo:.4e} > beta {beta:.4f} "
                                    f"max(E_a, E_b) {m:.4e} (ratio {r:.4f})")
    out["margin_db"] = 10 * math.log10(beta / out["worst_ratio"]) if out["worst_ratio"] > 0 else None
    return out


def click_record(o: np.ndarray, a: np.ndarray, b: np.ndarray, s0: int, fs: float) -> dict:
    """Print only (M3-3): `tools.acoustics clicks` events on the stepped and unstepped renders, and Seat 5's (a)
    reading (the step region's flagged frames of o, against a's threshold, are a subset of those of a or b). Not
    asserted: on noise and speech the detector's peak-frame comparison is coincidental (builder file 32, K5)."""
    nf = int(round(clicks.FRAME_S * fs))
    L = int(round(CROSSFADE_S * fs))
    lo, hi = (s0 - int(0.005 * fs)) // nf, (s0 + L + int(0.005 * fs)) // nf + 1
    det_a = clicks.detect_clicks(a[:, 0].astype(np.float64), fs)
    thr = det_a["effective_threshold_dbfs"]
    flags = [set(np.flatnonzero(clicks.frame_levels_dbfs(clicks.highpass(x[:, 0].astype(np.float64), fs), fs)[lo:hi] > thr))
             for x in (o, a, b)]
    return {"events_stepped": len(clicks.detect_clicks(o[:, 0].astype(np.float64), fs)["events"]),
            "events_unstepped": len(det_a["events"]), "threshold_unstepped_dbfs": thr,
            "step_region_flags_subset_of_a_or_b": flags[0] <= (flags[1] | flags[2])}


def wet_band_change(o: np.ndarray, a: np.ndarray, s0: int, fs: float) -> dict:
    """Print only (item 6): per band, 10 log10(E(stepped)/E(unstepped)) of the wet output over the 0.5 s after the
    fade (inside the gap or pause: both are >= T30 long and the onset is at most 0.43 T30 into it)."""
    start = s0 + int(round(CROSSFADE_S * fs))
    stop = start + int(round(0.5 * fs))
    out = {}
    for fc in bands.OCTAVE_BANDS_HZ:
        ob = bands.filter_band(o[:, 0].astype(np.float64), fs, fc)[start:stop]
        ab = bands.filter_band(a[:, 0].astype(np.float64), fs, fc)[start:stop]
        out[bands.band_key(fc)] = 10 * math.log10(np.sum(ob**2) / np.sum(ab**2)) if np.sum(ab**2) > 0 else None
    return out


def band_level_db(x: np.ndarray, fs: float, start: int, n: int) -> float:
    y = bands.filter_band(x, fs, Q5_BAND_HZ)[start : start + n]
    return 10 * math.log10(max(float(np.mean(y**2)), 1e-30))


# ---------------------------------------------------------------------------------------------------------
# Trial plan (items 2, 3, 7)
# ---------------------------------------------------------------------------------------------------------


def trial_plan(chain: str, level_db: float) -> list[dict]:
    """One block: 16 scored trials at +-level (8 up, 8 down, random order) and 6 anchor trials at +-3 dB (3 up, 3
    down) interleaved at seeded positions; 22 trials, a break after trial 11. Seeded (KEY_SEED_BLOCKS), so the plan is
    reproducible; which of A and B is X is drawn at sealing, from a key the plan does not hold."""
    rng = np.random.default_rng([KEY_SEED_BLOCKS[chain], int(round(level_db * 100))])
    scored = [+1] * UP_PER_BLOCK + [-1] * (SCORED_TRIALS - UP_PER_BLOCK)
    rng.shuffle(scored)
    anchors = [+1] * (ANCHOR_TRIALS // 2) + [-1] * (ANCHOR_TRIALS - ANCHOR_TRIALS // 2)
    rng.shuffle(anchors)
    slots = sorted(rng.choice(BLOCK_TRIALS, size=ANCHOR_TRIALS, replace=False).tolist())
    plan, si, ai = [], 0, 0
    for t in range(BLOCK_TRIALS):
        if t in slots:
            kind, g = "anchor", anchors[ai] * ANCHOR_DB
            ai += 1
        else:
            kind, g = "scored", scored[si] * level_db
            si += 1
        plan.append({"trial": t + 1, "kind": kind, "g_db": g, "direction": "up" if g > 0 else "down",
                     "seed_index": t, "break_after": t + 1 == BREAK_AFTER})
    assert len(plan) == BLOCK_TRIALS and si == SCORED_TRIALS and ai == ANCHOR_TRIALS
    return plan


# ---------------------------------------------------------------------------------------------------------
# Programmes (item 8)
# ---------------------------------------------------------------------------------------------------------


def noise_programme(t30_s: float, seed_index: int, chain_seed: int) -> tuple[np.ndarray, int]:
    """Pulsed pink noise, gaps >= T30(1 kHz), the step at a gap start: two bursts before the step (>= one T30 of
    programme before it, item 7), then a gap, a burst and a final gap after it (>= 2 s). The onset is a seeded
    partition boundary (item 5): the lead-in silence is LEAD_BLOCKS + a seeded 0..31 partitions."""
    rng = np.random.default_rng([chain_seed, 1000 + seed_index])
    burst = int(round(NOISE_BURST_S * FS / PARTITION)) * PARTITION
    gap = int(math.ceil(t30_s * FS / PARTITION)) * PARTITION
    lead = (LEAD_BLOCKS + int(rng.integers(0, ONSET_SEED_RANGE))) * PARTITION
    onset = lead + burst + gap + burst  # the start of the second gap
    total = onset + gap + burst + gap
    assert (gap + burst) / FS >= POST_STEP_S and burst + gap + burst >= t30_s * FS
    x = np.zeros(total)
    for start in (lead, lead + burst + gap, onset + gap):
        b = signals.apply_fades(signals.pink_noise(burst, int(rng.integers(0, 2**31))), FS, FADE_S)
        x[start : start + burst] = b * signals.db_to_amp(NOISE_LEVEL_DBFS)  # unit-RMS noise at the fixed level
    return x, onset


# ---------------------------------------------------------------------------------------------------------
# Rendering one chain
# ---------------------------------------------------------------------------------------------------------


def _render(binary, scene_path, prog_path, out_path, g=None, onset=None):
    args = ["--scene", scene_path, "--mode", "omni", "--in", prog_path, "--out", out_path, "--realtime-emulation",
            "--block", BLOCK, "--partition", PARTITION]
    if g is not None:
        args += ["--abx-step-db", repr(float(g)), "--abx-step-sample", onset]
    _run(binary, *args)
    return wav.read_float32(out_path)[0]


def render_trial(binary, scene_path, programme: np.ndarray, onset: int, g: float, trial_dir: pathlib.Path) -> dict:
    """A (the step at the onset) and B (unstepped, held throughout) of one trial, with every item-6 assertion on
    them. Returns the trial's record (hashes, measured values)."""
    trial_dir.mkdir(parents=True, exist_ok=True)
    prog = trial_dir / "programme_dry.wav"
    wav.write_float32(prog, signals.to_stereo(programme), FS)
    a_path, b_path = trial_dir / "A.wav", trial_dir / "B.wav"
    with tempfile.TemporaryDirectory() as tmp:
        end_path = pathlib.Path(tmp) / "stepped_alone.wav"
        A = _render(binary, scene_path, prog, a_path, g, onset)
        B = _render(binary, scene_path, prog, b_path)
        E = _render(binary, scene_path, prog, end_path, g, 0)
    prog.unlink()
    assert np.array_equal(A[:, 0].view(np.uint32), A[:, 1].view(np.uint32)), "omni: both outputs must be the same (diotic)"
    peak = 20 * math.log10(max(float(np.max(np.abs(A))), float(np.max(np.abs(B))), 1e-30))
    assert peak <= MAX_PEAK_DBFS, f"a stimulus peaks at {peak:.2f} dBFS > {MAX_PEAK_DBFS} (no normalisation, item 10)"
    mid = midfade_checks(A, B, E, onset, FS)
    hfw = hf_w_check(A, B, E, onset, FS)
    clk = click_record(A, B, E, onset, FS)
    return {"onset_sample": onset, "onset_s": onset / FS, "g_db": g, "peak_dbfs": peak, "midfade": mid, "hf_w": hfw,
            "clicks": clk,
            "wet_band_change_db": wet_band_change(A, B, onset, FS),
            "sha256": {"A": sha256_file(a_path), "B": sha256_file(b_path)}}


def gap_check(scene: dict, min_gap_s: float, gap_t30_s: float) -> dict:
    """M2 debt check (decider file 34, item 3): T-a's gaps and pauses are >= the heard-IR T30, which is harmless only
    while the minimum gap also exceeds the tail's own decay (true on S-A, false on layout 5). Printed: the minimum
    gap, the heard-IR T30 (Seat 9's label) and the tail T30 per emitter; asserted: minimum gap >= every tail T30."""
    tail = scene["tail_T30_1k_s"]
    if any(t is None for t in tail):
        raise RuntimeError(f"tail T30(1 kHz) not measured on every emitter ({tail}): the M2 gap check cannot run")
    assert abs(gap_t30_s - scene["T30_1k_s"]) <= 1e-9, (gap_t30_s, scene["T30_1k_s"])  # the gaps use the heard T30
    rec = {"min_gap_s": float(min_gap_s), "heard_T30_1k_s": scene["T30_1k_s"], "heard_T30_label": HEARD_T30_LABEL,
           "tail_T30_1k_s": tail, "min_gap_ge_tail_T30": bool(min_gap_s >= max(tail))}
    assert rec["min_gap_ge_tail_T30"], f"M2: minimum gap {min_gap_s:.3f} s < tail T30 {max(tail):.3f} s (file 34 item 3)"
    return rec


def build_chain(chain: str, binary: pathlib.Path, out: pathlib.Path, programme_for, log=print, levels=LEVELS_DB,
                trials: int | None = None, min_gap_s: float | None = None, gap_t30_s: float | None = None,
                scene_name: str = DEFAULT_SCENE) -> dict:
    """Both blocks of one chain (0.9 dB and 0.5 dB: every stimulus is sealed before the run, item 11) plus the
    familiarisation pairs; `programme_for(seed_index) -> (x, onset, record)`. `trials` limits each block (tests).
    `min_gap_s`, `gap_t30_s`: the programme's shortest gap or pause and the T30 it was built from (the M2 check)."""
    out.mkdir(parents=True, exist_ok=True)
    scene_path = out / "scene.json"
    scene_path.write_text(json.dumps(make_scene(scene_name), indent=1))
    work = out / "_work"
    work.mkdir(exist_ok=True)
    manifest: dict = {"chain": chain, "preregistration": "phase-07c-2 decider file 13, D-W2 final items 1-16 and Q5",
                      "criterion": f">= {CRITERION[chain]}/{SCORED_TRIALS}", "levels_db": list(levels),
                      "anchor": f"{ANCHOR_DB} dB, pass >= {ANCHOR_PASS}/{ANCHOR_TRIALS}", "fs": FS,
                      "partition": PARTITION, "block": BLOCK, "render_cli": str(binary), "blocks": {}, "ir_checks": {}}
    manifest["scene"] = check_scene(binary, scene_path, work, log, scene_name)
    diag = manifest["scene"].pop("diagnostics")
    manifest["m2_gap_check"] = gap_check(manifest["scene"], min_gap_s, gap_t30_s)
    gc = manifest["m2_gap_check"]
    log(f"{chain}: M2 gap check: minimum gap {gc['min_gap_s']:.3f} s >= tail T30(1 kHz) "
        f"{', '.join(f'{x:.3f}' for x in gc['tail_T30_1k_s'])} s; T30(1 kHz) {gc['heard_T30_1k_s']:.3f} s ({HEARD_T30_LABEL})")
    for g in sorted({s * x for x in (*levels, ANCHOR_DB) for s in (1, -1)}):
        u, s, target_share = ir_pair(binary, scene_path, g, work)
        rec = {**ir_assertions(u, s, diag, g), "bands": ir_band_shares(u, s, diag, g, target_share),
               "heard": heard_pair_metrics(u, s, float(diag["sampleRate"]), g)}
        manifest["ir_checks"][f"{g:+.1f}"] = rec
        hb, h1k = rec["heard"]["broadband"], rec["heard"]["bands"]["1000"]
        log(f"{chain}: IR step {g:+.1f} dB: tail alone "
            + ", ".join(f"{r['tail_alone']['step_db']:+.4f}" for r in rec["rows"])
            + " dB; window_unscaled_share (s_w, <= 2.3 %) "
            + ", ".join(f"{r['ax47_window']['window_unscaled_share']:.2e}" for r in rec["rows"])
            + "; per band (max over bands) "
            + ", ".join(f"{max(b['window_unscaled_share'] for b in r['bands'].values()):.2e}" for r in rec["bands"])
            + "; target_specular_share (max over bands) "
            + ", ".join(_fmt(max((b["target_specular_share"] or 0.0) for b in r["bands"].values()), 3) for r in rec["bands"])
            + f"; heard: tail share 1 kHz {h1k['tail_share_of_heard']:.3f} (broadband {hb['tail_share_of_heard']:.3f}), "
            f"delta G 1 kHz {h1k['delta_G_db']:+.3f} dB (broadband {hb['delta_G_db']:+.3f}), delta C80 1 kHz "
            f"{h1k['delta_C80_db']:+.3f} dB (broadband {hb['delta_C80_db']:+.3f})")
    for level in levels:
        block = []
        for t in trial_plan(chain, level)[: trials or BLOCK_TRIALS]:
            x, onset, record = programme_for(t["seed_index"])
            rec = render_trial(binary, scene_path, x, onset, t["g_db"], out / f"{level:.1f}dB" / f"trial_{t['trial']:02d}")
            block.append({**t, **record, **rec})
            log(f"{chain} {level:.1f} dB trial {t['trial']:02d} ({t['kind']}, {t['g_db']:+.1f} dB): onset "
                f"{onset / FS:.3f} s, peak {rec['peak_dbfs']:.1f} dBFS, mid-fade windows {rec['midfade']['windows']}, "
                f"HF-W worst ratio {rec['hf_w']['worst_ratio']:.4f} (margin {_fmt(rec['hf_w']['margin_db'], 3)} dB, "
                f"skipped {rec['hf_w']['skipped']})")
        manifest["blocks"][f"{level:.1f}"] = block
    # Familiarisation (item 2, mandatory before any scored block): labelled A/B pairs, the anchor and each level, up
    # and down; never scored. Feedback during familiarisation is Seat 1's design choice (not set by this kit).
    fam = []
    for i, g in enumerate((ANCHOR_DB, -ANCHOR_DB, *[s * x for x in levels for s in (1, -1)])):
        x, onset, record = programme_for(100 + i)
        rec = render_trial(binary, scene_path, x, onset, g, out / "familiarisation" / f"pair_{i + 1:02d}_{g:+.1f}dB")
        fam.append({"pair": i + 1, "g_db": g, **record, **rec})
    manifest["familiarisation"] = fam
    for p in work.iterdir():
        p.unlink()
    work.rmdir()
    (out / "manifest.json").write_text(json.dumps(manifest, indent=1, default=float))
    return manifest


def build_noise_chain(out: pathlib.Path, binary: pathlib.Path, log=print, trials: int | None = None,
                      scene_name: str = DEFAULT_SCENE) -> dict:
    """The noise chain (CI, the listening pack): pulsed pink noise through the ABX scene `scene_name`."""
    holder: dict = {}

    def programme_for(seed_index: int):
        if "t30" not in holder:
            raise RuntimeError("T30 not measured yet")
        x, onset = noise_programme(holder["t30"], seed_index, KEY_SEED_BLOCKS["noise"])
        return x, onset, {"programme": "pulsed pink noise", "noise_level_dbfs": NOISE_LEVEL_DBFS}

    # T30 is needed for the gaps before any programme: measure it once on the scene first.
    out.mkdir(parents=True, exist_ok=True)
    tmp_scene = out / "scene.json"
    tmp_scene.write_text(json.dumps(make_scene(scene_name), indent=1))
    with tempfile.TemporaryDirectory() as tmp:
        ir = pathlib.Path(tmp) / "ir.wav"
        _run(binary, "--scene", tmp_scene, "--mode", "omni", "--ir", ir)
        h, fs = wav.read(ir)
        holder["t30"] = float(metrics.room_metrics(h[:, 0] + h[:, 2], fs)["bands"]["1000"]["T30"])
    gap_s = int(math.ceil(holder["t30"] * FS / PARTITION)) * PARTITION / FS  # noise_programme's gap (all gaps equal)
    return build_chain("noise", binary, out, programme_for, log, trials=trials, min_gap_s=gap_s, gap_t30_s=holder["t30"],
                       scene_name=scene_name)


# ---------------------------------------------------------------------------------------------------------
# Speech chain (local only)
# ---------------------------------------------------------------------------------------------------------


def fetch_tsp(cache: pathlib.Path, log=print) -> pathlib.Path:
    """48k.zip by the pinned URL, verified against our own SHA-256 (the archive publishes none). Cached."""
    cache.mkdir(parents=True, exist_ok=True)
    path = cache / "48k.zip"
    if not path.exists() or sha256_file(path) != TSP_SHA256:
        log(f"downloading {TSP_URL} ({TSP_SIZE / 1e6:.0f} MB)")
        part = path.with_suffix(".part")
        with urllib.request.urlopen(TSP_URL, timeout=120) as r, open(part, "wb") as f:  # noqa: S310 (pinned https URL)
            while chunk := r.read(1 << 20):
                f.write(chunk)
        part.replace(path)
    digest = sha256_file(path)
    if digest != TSP_SHA256:
        raise RuntimeError(f"{path}: SHA-256 {digest} != pinned {TSP_SHA256}; delete it and retry, or re-pin knowingly")
    return path


def read_tsp_member(zip_path: pathlib.Path, speaker: str, name: str) -> tuple[np.ndarray, str]:
    if speaker in ("CA", "CB"):
        raise ValueError("the child recordings CA and CB are excluded (adult speakers only, item 8; researcher R35)")
    member = f"48k/{speaker}/{name}.wav"
    with zipfile.ZipFile(zip_path) as z:
        data = z.read(member)
    import soundfile as sf

    x, fs = sf.read(io.BytesIO(data), dtype="float64", always_2d=True)
    if fs != FS:
        raise RuntimeError(f"{member}: {fs} Hz, expected {FS} (no resampling, item 10)")
    return x[:, 0] * signals.db_to_amp(SPEECH_GAIN_DB), hashlib.sha256(data).hexdigest()


def _frames_db(x: np.ndarray, n: int) -> np.ndarray:
    k = len(x) // n
    return 10 * np.log10(np.maximum(np.mean(x[: k * n].reshape(k, n) ** 2, axis=1), 1e-30))


def speech_parts(s1: np.ndarray, s2: np.ndarray) -> dict:
    """End of speech of sentence 1 (the last 10 ms frame above TSP's noise level + END_OF_SPEECH_DB) and the noise
    segment used for the floor: the file's leading 10 ms frames before the first one more than 6 dB above the
    noise level (TSP's lead-in, preamplifier noise; R35 App. A), at least 30 ms. The noise level is the 5th
    percentile of the 10 ms frame levels of sentence 1."""
    n = FS // 100
    lv = _frames_db(s1, n)
    noise_db = float(np.percentile(lv, 5))
    active = np.flatnonzero(lv > noise_db + END_OF_SPEECH_DB)
    end = int((active[-1] + 1) * n)
    lead = int(np.flatnonzero(lv > noise_db + 6.0)[0])
    if lead < 3:
        raise RuntimeError(f"sentence 1 has only {lead * 10} ms of noise before speech (>= 30 ms needed for the floor)")
    return {"end_of_speech": end, "noise_db_10ms": noise_db, "noise": s1[: lead * n].copy(), "noise_ms": lead * 10}


def q5_window_record(boundaries: list[int], passing: list[int], eos: int, t30_samples: float) -> dict:
    """The realised Q5 onset window and replacement rate (decider file 21, 2a; interrogator file 23), recorded before
    sealing. Onsets are drawn from a seeded permutation of all N boundaries and the first of the K passing ones is
    taken (replace-and-record), so accepted onsets are uniform over the passing set; the first draw is replaced with
    p = (N - K) / N, and the expected number of replaced onsets per stimulus (failures before the first success,
    without replacement) is (N - K) / (K + 1). The window is [first, latest] passing boundary, in T30 after the end
    of speech; `contiguous` says whether the passing set is the first K boundaries."""
    n, k = len(boundaries), len(passing)
    return {"q5_realised_window_T30": [(min(passing) - eos) / t30_samples, (max(passing) - eos) / t30_samples],
            "q5_passing_contiguous_from_first": list(passing) == list(boundaries[:k]),
            "q5_passing_boundary_indices": [boundaries.index(b) for b in passing],
            "q5_first_draw_replaced_p": (n - k) / n,
            "q5_expected_replaced_per_stimulus": (n - k) / (k + 1)}


def build_speech_chain(out: pathlib.Path, binary: pathlib.Path, speaker: str, files: tuple[str, str],
                       cache: pathlib.Path, log=print, trials: int | None = None,
                       scene_name: str = DEFAULT_SCENE) -> dict:
    """The speech chain: TSP sentence 1, a pause >= T30, sentence 2 (item 8); the onset in the pause, <= 0.43 T30
    after the end of speech, at a seeded partition boundary; the Q5 assertion on every stimulus."""
    zip_path = fetch_tsp(cache, log)
    s1, h1 = read_tsp_member(zip_path, speaker, files[0])
    s2, h2 = read_tsp_member(zip_path, speaker, files[1])
    out.mkdir(parents=True, exist_ok=True)
    scene_path = out / "scene.json"
    scene_path.write_text(json.dumps(make_scene(scene_name), indent=1))
    parts = speech_parts(s1, s2)
    with tempfile.TemporaryDirectory() as tmp:
        tmp = pathlib.Path(tmp)
        ir = tmp / "ir.wav"
        dpath = tmp / "diag.json"
        _run(binary, "--scene", scene_path, "--mode", "omni", "--ir", ir, "--diagnostics", dpath)
        h, fs = wav.read(ir)
        t30 = float(metrics.room_metrics(h[:, 0] + h[:, 2], fs)["bands"]["1000"]["T30"])
        dd = json.loads(dpath.read_text())
        # M3-1 (phase-07c-2b decider file 2, Seat 1): Q5's window counts from the latest *heard* end of speech. The
        # programme feeds both emitters, so the far emitter's speech ends later by the difference of the direct
        # delays in the aligned IR (0 when they are equal, as on S-A and layout4_s0.7/default).
        direct = [int(round((e["directS"] - dd["alignmentShiftS"]) * fs)) for e in dd["emitters"]]
        heard_extra = max(direct) - min(direct)
        # The rendered floor: TSP's own noise (looped past one IR length) through the room, steady state.
        reps = int(math.ceil((len(h) + 2 * FS) / len(parts["noise"])))
        noise = np.tile(parts["noise"], reps)
        npath, nout = tmp / "noise.wav", tmp / "noise_out.wav"
        wav.write_float32(npath, signals.to_stereo(noise), FS)
        rn = _render(binary, scene_path, npath, nout)
        floor_db = band_level_db(rn[:, 0].astype(np.float64), FS, len(h) + FS // 2, FS)
    lead = LEAD_BLOCKS * PARTITION
    pause = int(math.ceil(t30 * FS))
    eos = lead + parts["end_of_speech"] + heard_extra
    x = np.zeros(lead + len(s1) + pause + len(s2))
    x[lead : lead + len(s1)] = s1
    x[lead + len(s1) + pause :] = s2
    excerpt = io.BytesIO()
    import soundfile as sf

    sf.write(excerpt, x.astype(np.float32), FS, subtype="FLOAT", format="WAV")
    first_boundary = -(-(eos + 1) // PARTITION) * PARTITION
    last_allowed = eos + int(math.floor(Q5_ONSET_MAX_T30 * t30 * FS))
    boundaries = list(range(first_boundary, last_allowed + 1, PARTITION))
    assert boundaries, "no partition boundary inside the Q5 window"
    assert len(x) - boundaries[-1] >= POST_STEP_S * FS, "less than 2 s of programme after the latest onset"
    assert boundaries[0] >= t30 * FS, "less than one T30 of programme before the earliest onset"
    rec_base = {"programme": "McGill TSP v2 speech", "speaker": speaker, "files": list(files),
                "member_sha256": [h1, h2], "excerpt_sha256": hashlib.sha256(excerpt.getvalue()).hexdigest(),
                "end_of_speech_s": eos / FS, "heard_end_extra_samples": heard_extra,
                "direct_delay_samples": direct, "pause_s": pause / FS, "T30_1k_s": t30, "floor_db_1k": floor_db}
    # The unstepped render does not depend on the onset: render it once for the Q5 measurement.
    with tempfile.TemporaryDirectory() as tmp:
        p, o = pathlib.Path(tmp) / "x.wav", pathlib.Path(tmp) / "y.wav"
        wav.write_float32(p, signals.to_stereo(x), FS)
        unstepped = _render(binary, scene_path, p, o)[:, 0].astype(np.float64)

    win = int(round(Q5_WINDOW_S * FS))
    margins = [band_level_db(unstepped, FS, b, win) - floor_db for b in boundaries]
    passing = [b for b, mg in zip(boundaries, margins) if mg >= Q5_MARGIN_DB]
    rec_base["q5_boundaries"] = len(boundaries)
    rec_base["q5_margin_db_per_boundary"] = margins
    rec_base["q5_boundaries_passing"] = len(passing)
    rec_base["q5_latest_passing_after_eos_T30"] = (max(passing) - eos) / FS / t30 if passing else None
    if not passing:
        raise RuntimeError(f"no partition boundary in the Q5 window has tail >= floor + {Q5_MARGIN_DB} dB")
    rec_base.update(q5_window_record(boundaries, passing, eos, t30 * FS))

    def programme_for(seed_index: int):
        rng = np.random.default_rng([KEY_SEED_BLOCKS["speech"], 1000 + seed_index])
        order = rng.permutation(len(boundaries))
        replaced = []
        for k in order:  # a seeded onset that fails Q5 is replaced by the next seed index, and recorded
            onset = boundaries[int(k)]
            tail_db = band_level_db(unstepped, FS, onset, int(round(Q5_WINDOW_S * FS)))
            if tail_db >= floor_db + Q5_MARGIN_DB:
                return x, onset, {**rec_base, "q5_tail_db_1k": tail_db, "q5_margin_db": tail_db - floor_db,
                                  "onset_after_eos_T30": (onset - eos) / FS / t30, "replaced_onsets": replaced}
            replaced.append({"onset_sample": onset, "tail_db_1k": tail_db})
        raise RuntimeError(f"seed index {seed_index}: no onset in the Q5 window meets tail >= floor + {Q5_MARGIN_DB} dB")

    log(f"speech: {speaker} {files}, end of speech {eos / FS:.3f} s, pause {pause / FS:.3f} s, T30(1 kHz) {t30:.3f} s, "
        f"floor {floor_db:.1f} dB (1 kHz), {len(boundaries)} onset boundaries in the Q5 window, {len(passing)} of them "
        f"with tail >= floor + {Q5_MARGIN_DB:g} dB (latest at {rec_base['q5_latest_passing_after_eos_T30']:.3f} T30); "
        f"realised onset window [{rec_base['q5_realised_window_T30'][0]:.3f}, {rec_base['q5_realised_window_T30'][1]:.3f}]"
        f" T30 after the end of speech, passing set contiguous from the first boundary: "
        f"{rec_base['q5_passing_contiguous_from_first']}; replacement: first draw replaced with p "
        f"{rec_base['q5_first_draw_replaced_p']:.3f}, {rec_base['q5_expected_replaced_per_stimulus']:.2f} replaced "
        "onsets per stimulus expected")
    manifest = build_chain("speech", binary, out, programme_for, log, trials=trials, min_gap_s=pause / FS, gap_t30_s=t30,
                           scene_name=scene_name)
    manifest["tsp"] = {"url": TSP_URL, "sha256": TSP_SHA256, "notice": TSP_NOTICE, **{k: v for k, v in rec_base.items()}}
    (out / "manifest.json").write_text(json.dumps(manifest, indent=1, default=float))
    (out / "NOTICE-TSP.txt").write_text(TSP_NOTICE + "\n")
    return manifest


# ---------------------------------------------------------------------------------------------------------
# Blinding and scoring (items 4, 11, 13)
# ---------------------------------------------------------------------------------------------------------


def prereg_path(key_path: pathlib.Path) -> pathlib.Path:
    """Where seal writes the record to commit before the run: beside the key, never in the session folder."""
    return key_path.with_name(key_path.stem + "-prereg.json")


def salted_sha256(salt_hex: str, path: pathlib.Path) -> str:
    """SHA-256 of a secret per-file salt followed by the file's bytes (item 11's commitment)."""
    h = hashlib.sha256(bytes.fromhex(salt_hex))
    h.update(path.read_bytes())
    return h.hexdigest()


def seal(pack: pathlib.Path, session: pathlib.Path, key_path: pathlib.Path, key_seed: int | None = None) -> dict:
    """Item 11: draws X = A or B per trial from a seeded key (secret unless given), writes the session folder (A, B,
    X per trial, no other information), the key to `key_path` (keep it outside the session folder, unseen by the
    listener) and the record to commit before the run to `prereg_path(key_path)`: the key's SHA-256 and a salted
    SHA-256 of every stimulus. X is a byte copy of A or B, so plain digests would give every answer away (X's digest
    would equal A's or B's); each file gets its own secret salt, held in the key, and `score` checks the session
    folder against the record with them."""
    import shutil

    manifest = json.loads((pack / "manifest.json").read_text())
    if key_path.resolve().is_relative_to(session.resolve()):
        raise ValueError("the key must not be inside the session folder")
    seed = int(key_seed if key_seed is not None else secrets.randbits(63))
    rng = np.random.default_rng(seed)
    key: dict = {"chain": manifest["chain"], "seed": seed, "blocks": {}}
    record: dict = {"chain": manifest["chain"], "stimuli_salted_sha256": {}}
    for level, block in manifest["blocks"].items():
        key["blocks"][level] = []
        for t in block:
            rel = f"{level}dB/trial_{t['trial']:02d}"
            src, dst = pack / rel, session / rel
            dst.mkdir(parents=True, exist_ok=True)
            x = "A" if rng.integers(0, 2) == 0 else "B"
            for name in ("A", "B"):
                shutil.copyfile(src / f"{name}.wav", dst / f"{name}.wav")
            shutil.copyfile(src / f"{x}.wav", dst / "X.wav")
            salts = {name: secrets.token_hex(32) for name in ("A", "B", "X")}  # never from the seed: unguessable
            for name in ("A", "B", "X"):
                record["stimuli_salted_sha256"][f"{rel}/{name}.wav"] = salted_sha256(salts[name], dst / f"{name}.wav")
            key["blocks"][level].append({"trial": t["trial"], "kind": t["kind"], "g_db": t["g_db"], "X": x,
                                         "salts": salts})
    text = json.dumps(key, indent=1, sort_keys=True)
    key_path.write_text(text)
    record["key_sha256"] = hashlib.sha256(text.encode()).hexdigest()
    prereg_path(key_path).write_text(json.dumps(record, indent=1, sort_keys=True))
    return record


def verify_session(key_path: pathlib.Path, session: pathlib.Path) -> None:
    """At scoring: the key is the committed one, and every file in the session folder is the one committed (item 11)."""
    text = key_path.read_text()
    record = json.loads(prereg_path(key_path).read_text())
    if hashlib.sha256(text.encode()).hexdigest() != record["key_sha256"]:
        raise ValueError("the key does not match the committed record")
    key = json.loads(text)
    for level, block in key["blocks"].items():
        for t in block:
            rel = f"{level}dB/trial_{t['trial']:02d}"
            for name in ("A", "B", "X"):
                if salted_sha256(t["salts"][name], session / rel / f"{name}.wav") != record["stimuli_salted_sha256"][
                        f"{rel}/{name}.wav"]:
                    raise ValueError(f"{rel}/{name}.wav does not match the committed record")


def binom_tail(k: int, n: int, p: float = 0.5) -> float:
    """Exact one-sided p = P(K >= k), K ~ Bin(n, p)."""
    return float(sum(math.comb(n, i) * p**i * (1 - p) ** (n - i) for i in range(k, n + 1)))


def score_block(key_block: list[dict], answers: dict[int, str], chain: str, level: str) -> dict:
    scored = [t for t in key_block if t["kind"] == "scored"]
    anchors = [t for t in key_block if t["kind"] == "anchor"]
    missing = [t["trial"] for t in key_block if t["trial"] not in answers]
    if missing:
        raise ValueError(f"{chain} {level} dB: no answer for trials {missing}")
    k = sum(answers[t["trial"]] == t["X"] for t in scored)
    ka = sum(answers[t["trial"]] == t["X"] for t in anchors)
    c = CRITERION[chain]
    if ka < ANCHOR_PASS:
        verdict, wording = "inconclusive", (f"inconclusive: anchor {ka}/{ANCHOR_TRIALS} < {ANCHOR_PASS}/{ANCHOR_TRIALS}; "
                                            "the block is void and gets one rerun (item 4)")
    elif k >= c:
        verdict, wording = "detected", f"detected (>= {c}/16, family alpha {FAMILY_ALPHA})"
    else:
        verdict = "not detected"
        wording = f"not detected in 16 trials by one listener (power {POWER_AT_075[chain]:.2f} at p = 0.75)"
    return {"chain": chain, "level_db": float(level), "k": k, "n": len(scored), "p_exact": binom_tail(k, len(scored)),
            "anchor_k": ka, "anchor_n": len(anchors), "verdict": verdict, "wording": wording}


def read_responses(path: pathlib.Path) -> dict[str, dict[int, str]]:
    """CSV with columns level_db, trial, answer (A or B): the run sheet's response table."""
    out: dict[str, dict[int, str]] = {}
    with open(path, newline="") as f:
        for row in csv.DictReader(f):
            ans = row["answer"].strip().upper()
            if ans not in ("A", "B"):
                continue
            out.setdefault(f"{float(row['level_db']):.1f}", {})[int(row["trial"])] = ans
    return out


def score(key_path: pathlib.Path, responses: dict[str, dict[int, str]], chain: str) -> list[dict]:
    """Items 3, 4, 13: the 0.9 dB block first; the 0.5 dB block is unsealed only if 0.9 dB was detected in this chain."""
    key = json.loads(key_path.read_text())
    if key["chain"] != chain:
        raise ValueError(f"the key is for the {key['chain']} chain")
    results = []
    first = score_block(key["blocks"]["0.9"], responses.get("0.9", {}), chain, "0.9")
    results.append(first)
    if "0.5" in responses:
        if first["verdict"] != "detected":
            raise PermissionError(f"refusing to unseal the {chain} 0.5 dB block: 0.9 dB was not detected in this chain "
                                  f"({first['wording']})")
        results.append(score_block(key["blocks"]["0.5"], responses["0.5"], chain, "0.5"))
    return results


def blank_response_csv(path: pathlib.Path, chain: str) -> None:
    with open(path, "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["level_db", "trial", "answer"])
        for level in LEVELS_DB:
            for t in trial_plan(chain, level):
                w.writerow([f"{level:.1f}", t["trial"], ""])


# ---------------------------------------------------------------------------------------------------------


def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    for name in ("noise", "speech"):
        p = sub.add_parser(name)
        p.add_argument("--out", type=pathlib.Path, default=REPO / "build" / "abx-07c-2")
        p.add_argument("--render-cli", type=pathlib.Path, default=None)
        p.add_argument("--trials", type=int, default=None, help="limit each block (smoke runs only)")
        p.add_argument("--scene", default=DEFAULT_SCENE, help="the ABX scene, layout<4|5>_s<s>/<placement> (M3)")
        if name == "speech":
            p.add_argument("--speaker", required=True, help="adult TSP speaker, fixed in the pre-registration (item 8)")
            p.add_argument("--files", nargs=2, required=True, metavar=("SENTENCE1", "SENTENCE2"),
                           help="the TSP file pair, e.g. MA01_01 MA01_02 (fixed in the pre-registration)")
            p.add_argument("--cache", type=pathlib.Path, default=pathlib.Path.home() / ".cache" / "makroof" / "tsp")
    p = sub.add_parser("seal")
    p.add_argument("--pack", type=pathlib.Path, required=True)
    p.add_argument("--session", type=pathlib.Path, required=True)
    p.add_argument("--key", type=pathlib.Path, required=True)
    p = sub.add_parser("score")
    p.add_argument("--key", type=pathlib.Path, required=True)
    p.add_argument("--responses", type=pathlib.Path, required=True)
    p.add_argument("--chain", choices=("noise", "speech"), required=True)
    p.add_argument("--session", type=pathlib.Path, required=True, help="the listener's folder; X.wav is checked")
    p = sub.add_parser("blank")
    p.add_argument("--chain", choices=("noise", "speech"), required=True)
    p.add_argument("--out", type=pathlib.Path, required=True)
    args = ap.parse_args(argv)

    if args.cmd in ("noise", "speech"):
        binary = args.render_cli or render_cli.find_render_cli()
        if binary is None or not binary.is_file():
            print("abx_kit.py: render_cli not found (cmake --preset cli && cmake --build --preset cli)", file=sys.stderr)
            return 1
        if args.cmd == "noise":
            build_noise_chain(args.out / "noise", binary, trials=args.trials, scene_name=args.scene)
        else:
            build_speech_chain(args.out / "speech", binary, args.speaker, tuple(args.files), args.cache, trials=args.trials,
                               scene_name=args.scene)
        print(f"written to {args.out / args.cmd}")
    elif args.cmd == "seal":
        record = seal(args.pack, args.session, args.key)
        print(json.dumps({"key_sha256": record["key_sha256"], "stimuli": len(record["stimuli_salted_sha256"])}, indent=1))
        print(f"commit {prereg_path(args.key)} before the run; keep {args.key} unseen until scoring")
    elif args.cmd == "score":
        verify_session(args.key, args.session)
        for r in score(args.key, read_responses(args.responses), args.chain):
            print(json.dumps(r))
    elif args.cmd == "blank":
        blank_response_csv(args.out, args.chain)
    return 0


if __name__ == "__main__":
    sys.exit(main())
