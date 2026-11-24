#!/usr/bin/env python3
"""Phase-07c-2 D-W2: the AX47 self-ABX stimulus kit, as pre-registered.

The design is decider file 13 (docs/review/phase-07c-2/13-decider-rebuttal-r4.md), "D-W2: final", items 1-16, and
its section "Q5: TSP step placement (pre-registered)"; interrogator file 14 (D-W2 SURVIVES). The listener's run
sheet is docs/validation/abx-07c-2-run-sheet.md. Every number this kit fixes from file 13 is a module constant
below, with its item.

    # noise chain (CI: tools/ci/listening_pack.py --phase phase-07c-2 calls build_noise_chain); the scene is
    # layout5_s0.9/emitter_wall (phase-07c-2b decider file 8, M3-S); --scene-name picks a registered fallback
    python tools/ci/abx_kit.py noise  --out build/abx-07c-2 [--scene-name layout5_s0.8/emitter_wall]
    # speech chain: local only (McGill TSP v2 is downloaded by our own SHA-256; no audio is ever committed)
    python tools/ci/abx_kit.py speech --out build/abx-07c-2 --speaker MA --files MA01_01 MA01_02
    # blinding (item 11): writes the session folder (A, B, X per trial) and the sealed key; prints the hashes
    python tools/ci/abx_kit.py seal   --pack build/abx-07c-2/noise --session <dir> --key <file outside it>
    # scoring (items 3, 4, 13): refuses to unseal a 0.5 dB block unless 0.9 dB was detected in that chain
    python tools/ci/abx_kit.py score  --key <file> --responses <csv> --chain noise
    # AX49 L4 (run sheet section 8): the held-chord provisional-against-exact pack (primary + pre-built rerun block),
    # sealed and scored as above (--chain l4: the anchor first, a failed anchor's block never unsealed); before a
    # session, l4-verify rebuilds A's and B's IRs and compares their SHA-256 (P8 item 4)
    python tools/ci/abx_kit.py l4 --out build/abx-07c-2b/l4
    python tools/ci/abx_kit.py l4-verify --pack build/abx-07c-2b/l4

What is stepped (item 5): render_cli --abx-step-db g (validation only, like --no-air-absorption, AX4): a change
of g dB in the tail energy, uniform across the 8 bands, from a second IrSet of the same StagedBuild through
useDiffuseLevel, faded in with the shipped AQ4 30 ms equal-gain crossfade (AX18), rendered with
--realtime-emulation, fixed block, P = 512, the onset at a seeded partition boundary.

Assertions on every stimulus (item 6): early parts bit-identical (the IRs up to the tail's fade-in, and the render
before the onset); 10 log10(E(stepped - unstepped)/E(unstepped)) = 20 log10|10^(g/20) - 1| over the tail window;
the [ax47-midfade] checks (tests/unit/test_ax47_midfade.cpp: W-a windows and companions (i)-(iii)); the
tools.acoustics click detector finds no event in the step region of the crossfade residual (A - B) - m (form (b),
phase-07c-2b M3); the per-band wet-output change, the window's
unscaled energy share (exact split, `window_unscaled_share`, asserted <= 2.3 %) and render_cli's E_target specular
share (`target_specular_share`) are printed, each under its own name (decider file 27, amendment 1; file 31, item 6).
Per g, on the heard IR pair: the tail-window share of the heard energy, Delta G and Delta C80 per band (Seat 1's
condition, file 27). M2 (files 31, 34) under M3-G (phase-07c-2b decider file 8): every gap, pause and item-7 lead
is built from T = max(heard-IR T30, every tail T30) at 1 kHz; the manifest carries the heard-IR T30 with Seat 9's
label, the tail T30 beside it and the minimum heard gap, and asserts it >= T and >= every tail T30. Phase-07c-2b
M3-C 6-7: M1's per-band step identity asserted at <= 0.05 dB; B and E nulled within -120 dB against an offline
reference on every stimulus; the gap-cue print (E - B re B at 1 kHz over 100 and 300 ms after N; max per-band
Delta G).

Speech (Q5): the onset <= 0.43 x the heard-IR T30(1 kHz) after the end of speech, the rendered tail
>= the rendered floor (TSP's own noise) + 20 dB at the onset (1 kHz band, 50 ms window); a failing seeded onset
is replaced by the next seed index and the replacement recorded. Item 7 (phase-07c-2b decider files 30 and 34): the
onsets are drawn from the candidate boundaries that lie (a) at or after the heard end of sentence 1, (b) within Q5's
ceiling and (c) at least lead + ceil(T fs) samples after the stimulus start; >= 34 must pass Q5. The speech pair is
the result of the pre-registered pair search (`speech --search-pairs`, SPEECH_PAIR); MA01_01 + MA01_02 with (c)
restricting the onsets only in the fallback branch (ITEM7_ONSET_FLOOR_PINNED).
"""

from __future__ import annotations

import argparse
import copy
import csv
import functools
import hashlib
import io
import json
import math
import os
import pathlib
import platform
import secrets
import sys
import tempfile
import urllib.request
import zipfile

import numpy as np
from scipy import signal as sps

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
# The heard-IR T30's label, per scene class (phase-07c-2b decider file 25, ruling (i); interrogator file 28): on s = 1
# scenes Seat 9's text that M2 T-a pinned (decider files 27, 31, 34); on s < 1 scenes, E included, file 8's M3-S text.
# Printed beside the tail's own T30.
HEARD_T30_LABEL = {
    "s=1": "heard-IR T30, ISO fit spanning the AX21 gap, not a decay rate",
    "s<1": "heard-IR T30, ISO fit spanning the early part, not a decay rate",
}
# Item 7 on the speech chain (phase-07c-2b decider files 30 and 34, DECISION I7; interrogator files 36 and 37): a speech
# onset is a candidate only if it lies (a) at or after the heard end of sentence 1 (D-M3b), (b) no later than
# 0.43 T_heard after the end of speech (Q5) and (c) at least lead + ceil(T fs) samples after the stimulus start (T the
# construction T, M3-G). At least Q5_MIN_PASSING candidates must pass Q5's >= 20 dB assertion.
Q5_MIN_PASSING = 34
# The pre-registered speech pair per scene (decider file 34, the pair search: the first adult MA pair in TSP index
# order whose earliest (a)(b) boundary already meets (c) and that passes every pre-seal assertion on the scene in use;
# `speech --search-pairs`, builder file 39). Filled from the search result; a fallback scene gets its own search.
SPEECH_PAIR = {
    # E: MA01_03 + MA01_04 to MA02_01 + MA02_02 fail (c) unrestricted; MA02_03 + MA02_04 meets it (earliest boundary
    # 2.901 s >= floor 2.685 s) and passes every pre-seal assertion (builder file 39)
    "layout5_s0.9/emitter_wall": {
        "speaker": "MA", "files": ("MA02_03", "MA02_04"),
        "member_sha256": ("4782a1658ec8438a88e2f6147d4682f586b359da157d6946f78ae19c2210cdc1",
                          "5ed86159c54b5e7ee83789d5b410041fd23ba8a1d667edabc8dfc166b7e49cd2")},
}
# The fallback branch (decider file 34): if no pair qualifies, MA01_01 + MA01_02 with (c) restricting the onsets and
# the onset floor (lead + ceil(T fs), samples) pinned per scene. Only a scene listed here may build restricted onsets.
ITEM7_FALLBACK_PAIR = ("MA", ("MA01_01", "MA01_02"))
ITEM7_ONSET_FLOOR_PINNED: dict[str, int] = {}
ITEM7_FALLBACK_RECORD = ("speech onsets \u2265 0.134\u00b7T_heard on E (item 7); about 2 dB less mean tail exposure "
                         "than an unrestricted draw.")
# D-M3a (phase-07c-2b decider file 5): form (b)'s single-sample spike floor, -90 dBFS frame floor less the share of a
# spike's energy above 2 kHz in one frame (about 22/24); asserted bracket (tools/ci/test_abx_kit.py)
SPIKE_CAUGHT_DBFS = -68.0
SPIKE_MISSED_DBFS = -72.0
# Decider file 8, M3-C 7 (Seat 3's pre-seal conditions): M1's per-band step identity (the step measured per band over
# [t_mix,e, L) equals g) asserted at <= 0.05 dB, inside file 34 item 1's 0.1 dB window tolerance; B and E nulled
# within -120 dB against an offline reference on every noise and speech stimulus (D-M3a, decider file 5).
BAND_STEP_TOL_DB = 0.05
NULL_MAX_DB = -120.0
GAP_CUE_WINDOWS_S = (0.100, 0.300)  # M3-C 6 (Seat 1): the 1 kHz level of E - B re B over [N, N + w), print only


def SPIKE_FLOOR_DBFS_AT(n_frame: int) -> float:  # noqa: N802 (a derived constant)
    return -90.0 - 10.0 * math.log10(0.917 / n_frame)

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


# Item 9's label for S-A (phase-07c-2b decider file 5, D-M3g; interrogator file 6 corrections). It replaces the label
# Seat 9 rated 3/3 (phase-07c-2 file 26); "hall" and "occupied" are gone. The Class line is the scene class item 13
# scopes a non-detection to (D-M3e): a manifest is never built without one. The case-4 line is decider file 8, M3-C 5
# (Seat 9's C-c).
SA_LABEL = "Direct-dominated test room, early reflections absent (AX21); not a validated preset"
SA_LABEL_DETAIL = (
    "20 x 30 x 10 m; floor alpha 1, other faces alpha 0.01; scattering s = 1 on every face; tailSeed 12345; "
    "emitters 12.4 m from the listener.",
    "D/R at 1 kHz +10.7 / +9.7 dB per emitter (heard L + R: +13.1 dB), against -10.8 dB at r/r_c 3.47 (Kuttruff "
    "Eq. 5.44, Sabine A ~ 640 m^2: 600 + 16 m^2 of surfaces, 24 m^2 of air). Indicative only: with mean alpha ~ 0.28 "
    "and one face at alpha 1 the field is far from diffuse, where Kuttruff (sections 5.6-5.7) calls these relations "
    "questionable.",
    "Early part -76.7 dB re direct: empty (AX21; Maisara decided on 2026-11-05 that the early part should contain "
    "scattered energy; the plan's AX21 row defers that fix to the B11 promotion rule, so it is a known deficit, not "
    "rendered here).",
    "Heard-IR T30 2.009 s (ISO fit spanning the AX21 gap, not a decay rate); tail T30 1.254 / 1.274 s; Eyring target "
    "1.291 s.",
    "Kuttruff Table 5.2 case 4 (floor α 1, others 0): iteration 1.21 s against Eyring 1.38 s; the engine's tail "
    "follows Eyring.",
    "Class: direct-dominated, early part empty.",
    "Stimulus scene, not a room prediction.",
)

# Item 9's label for E = layout5_s0.9/emitter_wall (phase-07c-2b decider file 8, M3-S, verbatim, with the ITDG line
# replaced by decider file 10 Part B's (interrogator file 11 correction 1, S0's floor image); Class line M3-S's, D-M3e).
E_LABEL = ("Tail-dominated stress placement, one absorbing side wall, source 0.1 m from a wall, specular-only early "
           "reflections (s 0.9, AX21); not a validated preset")
E_LABEL_DETAIL = (
    "S0 22.1 m away; direct-path difference 28.4 ms.",
    "D/R −12.7 / −5.0 dB, heard −9.5 dB, against −18.6 / −13.5 dB at r/r_c 8.46 / 4.74 (Sabine A ≈ 343 m²). "
    "Indicative only: ᾱ ≈ 0.145 and one face at α 1; Kuttruff §5.6–5.7 says these relations are questionable when ᾱ "
    "is not small, and one fully absorbing face is a severe deviation from diffuse conditions.",
    "ITDG 0.6 ms (S0's wall image, notch ≈ 860 Hz), 0.89 ms (S0's floor image, notch ≈ 560 Hz) and 1.6 ms (S1's floor "
    "image, notch ≈ 320 Hz), all inside the ±2.5 ms direct window and counted as direct; specular amplitude "
    "√(0.99 × 0.1) = 0.315 (+2.4 / −3.3 dB at the wall image).",
    "Near-wall emitter; its LF image is under-represented (one broadband s).",
    "Early part −8.6 dB re direct; the scattered early energy is absent (AX21; the fix is deferred to the B11 rule).",
    "Tail share 0.852 at 1 kHz.",
    "Heard-IR T30 2.560 s, labelled \"ISO fit spanning the early part, not a decay rate\"; tail T30 2.582 / 2.600 s; "
    "Eyring 2.61 s.",
    "Kuttruff Table 5.2 case 5: iteration 3.06 s against Eyring 2.99 s; the engine's tail follows Eyring.",
    "Gaps are built from max(heard, tail) T30.",
    "Class: tail-dominated (heard −9.5 dB, tail share 0.85), partial early part",
    "Stimulus scene, not a room prediction.",
)

# Fallback labels (decider file 8, M3-S: D, then B), Seat 9's file 7 text at s 0.8 ("as above" written out; every
# label carries Seat 9's D/R qualifier and the "Stimulus scene" line, as Seat 9 states for every label).
_L5_DR_QUALIFIER = ("Indicative only: ᾱ ≈ 0.145 and one face at α 1; Kuttruff §5.6–5.7: relations questionable when ᾱ "
                    "is not small, severe deviation from diffuse conditions.")
_L5_CASE5 = "Kuttruff Table 5.2 case 5: iteration 3.06 s against Eyring 2.99 s. The engine's tail follows Eyring."
D_LABEL = ("Tail-dominated stress placement, one absorbing side wall, source 0.1 m from a wall, specular-only early "
           "reflections (s 0.8, AX21); not a validated preset")
D_LABEL_DETAIL = (
    "S0 22.1 m away; direct-path difference 28.4 ms.",
    "D/R −12.9 / −4.5 dB, heard −9.5 dB, against −18.6 / −13.5 dB at r/r_c 8.46 / 4.74. " + _L5_DR_QUALIFIER,
    "ITDG 0.6 / 1.6 ms, counted as direct.",
    "Early part −5.2 dB. Tail share 0.834.",
    "Heard T30 2.561 s, below tail T30 2.582 / 2.600 s. " + _L5_CASE5,
    "Class: tail-dominated (heard −9.5 dB, tail share 0.83), partial early part.",
    "Stimulus scene, not a room prediction.",
)
B_LABEL = ("Test room with one absorbing side wall, specular-only early reflections (s 0.8, AX21); not a validated "
           "preset")
B_LABEL_DETAIL = (
    "x = 0 wall (30 × 10 m) α 1, others 0.01; s one value in all bands. Listener at (10, 8, 1.7); emitters 12.4 m "
    "away.",
    "D/R −3.6 / −4.4 dB, heard −1.4 dB, against −13.5 dB at r/r_c 4.74 (Sabine A ≈ 343 m²). " + _L5_DR_QUALIFIER,
    "ITDG 1.6 ms (floor), counted as direct: comb with its first notch about 320 Hz, +3.1 / −4.8 dB. The ceiling "
    "follows at about 23.6 ms.",
    "Early part −6.9 dB. Tail share 0.485.",
    "Heard-IR T30 2.556 s, below tail T30 2.617 / 2.600 s; Eyring 2.61 s.",
    _L5_CASE5,
    "Gaps are built from max(heard, tail) T30.",
    "Class: near-balanced D/R (heard −1.4 dB, tail share 0.49), partial early part.",
    "Stimulus scene, not a room prediction.",
)

FACES = ("xMin", "xMax", "yMin", "yMax", "floor", "ceiling")


def scene_layout4_s1_default() -> dict:
    """`layout4_s1/default` (S-A): Kuttruff Table 5.2 layout 4 at s = 1 as tests/unit/test_diffuse_wsweep.cpp builds
    it (20 x 30 x 10 m, faces alpha 0.01, the floor alpha 1, scattering 1 on every face), listener R0 (10, 8, 1.7),
    emitters S0 (7, 20, 2) and S1 (13, 20, 2), fixed tailSeed. Item-9 label: SA_LABEL, with SA_LABEL_DETAIL
    (phase-07c-2b decider files 2 and 5, D-M3g, as corrected by interrogator file 6; case-4 line, file 8 M3-C 5)."""
    scene = json.loads((REPO / "tests" / "scenes" / "valid" / "medium_room.json").read_text())
    scene = copy.deepcopy(scene)
    scene["room"]["geometry"]["dimensions"] = [20.0, 30.0, 10.0]
    for face in FACES:
        scene["room"]["surfaces"][face] = {"absorption": [1.0 if face == "floor" else 0.01] * 8, "scattering": 1.0}
    scene["listener"]["position"] = [10.0, 8.0, 1.7]
    scene["emitters"][0]["position"] = [7.0, 20.0, 2.0]
    scene["emitters"][1]["position"] = [13.0, 20.0, 2.0]
    scene["render"]["tailSeed"] = TAIL_SEED
    return scene


def scene_layout5(s: float, placement: str) -> dict:
    """Layout 5 (Kuttruff Table 5.2 case 5 geometry, phase-07c-2b builder file 4): S-A's room with xMin (the x = 0
    wall, 30 x 10 m) at alpha 1, every other face alpha 0.01, scattering s on every face in every band; tailSeed
    12345; listener (10, 8, 1.7); S1 (13, 20, 2); S0 (7, 20, 2) at `default` or (7, 29.9, 2) at `emitter_wall`
    (tests/unit/test_diffuse_wsweep.cpp placements). Built the way builder file 4's make_scene built it, so the JSON
    (and its SHA-256) is the measured one."""
    scene = scene_layout4_s1_default()
    for face in FACES:
        scene["room"]["surfaces"][face] = {"absorption": [1.0 if face == "xMin" else 0.01] * 8, "scattering": s}
    scene["listener"]["position"] = [10.0, 8.0, 1.7]
    scene["emitters"][0]["position"] = {"default": [7.0, 20.0, 2.0], "emitter_wall": [7.0, 29.9, 2.0]}[placement]
    scene["emitters"][1]["position"] = [13.0, 20.0, 2.0]
    scene["render"]["tailSeed"] = TAIL_SEED
    return scene


class AbxScene:
    """One registered ABX scene (item 9): its name, builder, item-9 label and detail lines, and the committed JSON
    (tools/ci/abx_scenes/, asserted equal to the builder) when the scene is the sealed one."""

    def __init__(self, name: str, build, label: str, label_detail: tuple[str, ...], committed: str | None = None):
        self.name, self.build, self.label, self.label_detail = name, build, label, tuple(label_detail)
        self.committed = None if committed is None else ABX_SCENES_DIR / committed

    def text(self) -> str:
        return json.dumps(self.build(), indent=1)


ABX_SCENES_DIR = REPO / "tools" / "ci" / "abx_scenes"
SCENE_E = "layout5_s0.9/emitter_wall"
# Decider file 8, M3-S: E, then (if any pre-seal check fails) D, then B. S-A stays registered (07c-2's scene).
SCENES = {
    SCENE_E: AbxScene(SCENE_E, lambda: scene_layout5(0.9, "emitter_wall"), E_LABEL, E_LABEL_DETAIL,
                      "layout5_s0.9_emitter_wall.json"),
    "layout5_s0.8/emitter_wall": AbxScene("layout5_s0.8/emitter_wall", lambda: scene_layout5(0.8, "emitter_wall"),
                                          D_LABEL, D_LABEL_DETAIL),
    "layout5_s0.8/default": AbxScene("layout5_s0.8/default", lambda: scene_layout5(0.8, "default"), B_LABEL,
                                     B_LABEL_DETAIL),
    "layout4_s1/default": AbxScene("layout4_s1/default", scene_layout4_s1_default, SA_LABEL, SA_LABEL_DETAIL),
}
DEFAULT_SCENE = SCENE_E
FALLBACK_ORDER = (SCENE_E, "layout5_s0.8/emitter_wall", "layout5_s0.8/default")


def scene_file_name(name: str) -> str:
    return "scene_" + name.replace("/", "_") + ".json"


def write_scene(entry: AbxScene, path: pathlib.Path) -> pathlib.Path:
    """Writes the scene JSON the kit renders. For a committed scene, the committed file's bytes, after asserting
    they equal the builder's output (so the manifest's scene_sha256 is the committed file's)."""
    text = entry.text()
    if entry.committed is not None:
        committed = entry.committed.read_text(encoding="utf-8")
        if committed != text:
            raise RuntimeError(f"{entry.committed} differs from the builder of {entry.name}: regenerate it knowingly")
    path.write_bytes(text.encode("utf-8"))  # bytes, not text mode: Windows would write CRLF and change scene_sha256
    return path


def require_class_line(entry: AbxScene) -> str:
    """D-M3e (decider file 5): every sealed scene's label carries a Class line; no manifest is built without one."""
    lines = [x for x in entry.label_detail if x.startswith("Class: ")]
    if not lines:
        raise RuntimeError(f"{entry.name}: the item-9 label has no 'Class: ' line (D-M3e); the kit builds no manifest")
    return lines[0]


def scene_class_s(scene: dict) -> str:
    """The scene class of ruling (i) (phase-07c-2b decider file 25): "s=1" when every face scatters fully in every band
    (the early part is empty, AX21), else "s<1"."""
    vals = []
    for face in scene["room"]["surfaces"].values():
        sc = face.get("scattering", 0.0)
        vals += list(sc) if isinstance(sc, (list, tuple)) else [sc]
    return "s=1" if vals and all(float(v) == 1.0 for v in vals) else "s<1"


def heard_t30_label(scene: dict) -> str:
    """The heard-IR T30's label for this scene's class (decider file 25, ruling (i))."""
    return HEARD_T30_LABEL[scene_class_s(scene)]


def _run(binary: pathlib.Path, *args) -> str:
    r = render_cli.run(binary, *args)
    if r.returncode != 0:
        raise RuntimeError(f"render_cli {' '.join(map(str, args))} failed ({r.returncode}):\n{r.stderr}")
    return r.stdout


def check_scene(binary: pathlib.Path, scene_path: pathlib.Path, work: pathlib.Path, log=print,
                entry: AbxScene | None = None) -> dict:
    """Item 9: capped at m = 6, 7 and 8 (asserted); r/r_c and D/R printed; T30(1 kHz) of the heard IR; the tail T30
    per emitter; the construction T = max(heard-IR T30, every tail T30) at 1 kHz (decider file 8, M3-G). Refuses a
    scene whose label has no Class line (D-M3e)."""
    entry = entry or SCENES[DEFAULT_SCENE]
    class_line = require_class_line(entry)
    name = entry.name
    out: dict = {"name": name, "label": entry.label, "label_detail": list(entry.label_detail), "class": class_line,
                 "scene_sha256": sha256_file(scene_path), "tailSeed": TAIL_SEED, "capped": {}}
    if entry.committed is not None:
        out["scene_file"] = entry.committed.relative_to(REPO).as_posix()
    for m in W_CANDIDATES:
        diag = work / f"diag_m{m}.json"
        _run(binary, "--scene", scene_path, "--mode", "omni", "--w-multiplier", m, "--diagnostics", diag)
        d = json.loads(diag.read_text())
        hits = [bool(e["diffuse"]["capHit"]) for e in d["emitters"]]
        out["capped"][str(m)] = hits
        if not all(hits):
            raise RuntimeError(f"{name} is not capped at m = {m} (cap hit per emitter {hits}): item 9 fails; the kit "
                               f"stops (decider file 8, M3-S: fall back in the order {', '.join(FALLBACK_ORDER)})")
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
    out["scene_class_s"] = scene_class_s(scene)
    out["T30_1k_s_label"] = heard_t30_label(scene)  # ruling (i): per scene class
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
    out["tail_T30_1k_s"] = [x["tail_T30_1k_s"] for x in out["emitters"]]  # per emitter, from t_mix,e (beside T30_1k_s)
    if any(x is None for x in out["tail_T30_1k_s"]):
        raise RuntimeError(f"tail T30(1 kHz) not measured on every emitter ({out['tail_T30_1k_s']}): M3-G cannot run")
    # M3-G (decider file 8): every gap, pause and item-7 lead is built from T = max(heard-IR T30, every tail T30);
    # Q5's ceiling stays 0.43 x the heard-IR T30.
    out["construction_T_s"] = max(float(t30), *out["tail_T30_1k_s"])
    out["heard_delays_samples"] = heard_delays(d)
    # The heard IR (both emitters summed): at equal r the two direct sounds coincide and add coherently, the tails
    # do not, so this D/R is about 3 dB above each emitter's own (decider file 21, 2b; file 22). The per-emitter D/R
    # (single-emitter IR, AX13) is the one to set against r/r_c.
    out["DRR_basis"] = "heard IR: emitters L + R summed (the programme feeds both); per-emitter D/R under emitters"
    out["DRR_dB_broadband"] = m["broadband"].get("DRR")
    out["DRR_dB_1k"] = m["bands"]["1000"].get("DRR")
    out["diagnostics"] = d
    log(f"scene {name}: capped at m = 6, 7, 8 ({out['capped']}); T30(1 kHz) {t30:.3f} s "
        f"({out['T30_1k_s_label']}; tail T30 {', '.join(_fmt(x, 3) for x in out['tail_T30_1k_s'])} s; construction T "
        f"{out['construction_T_s']:.3f} s) "
        f"(Eyring T60 {out['T60_eyring_1k_s']:.3f} s); r_c {rc:.2f} m ({out['r_c_m_T30']:.2f} m from the heard T30); "
        + "; ".join(f"emitter {x['id']} r {x['r_m']:.2f} m r/r_c {x['r_over_rc']:.2f} D/R {_fmt(x['DRR_dB_broadband'])} dB "
                    f"(1 kHz {_fmt(x['DRR_dB_1k'])} dB), tail-alone T30(1 kHz) {_fmt(x['tail_T30_1k_s'], 3)} s"
                    for x in out["emitters"])
        + f"; heard (L + R) D/R broadband {_fmt(out['DRR_dB_broadband'])} dB, 1 kHz {_fmt(out['DRR_dB_1k'])} dB")
    return out


def _fmt(x, digits: int = 1) -> str:
    return "None" if x is None else f"{x:.{digits}f}"


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
            "tail_EDT_1k_s": tail["bands"]["1000"]["EDT"], "target_T60_1k_s": float(diag["t60"][4])}


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


def band_step_check(band_rows: list[dict], g: float) -> dict:
    """M1's per-band step identity (decider file 8, M3-C 7; Seat 3): per emitter and band, the step `step_db` that
    `ir_band_shares` measures over [t_mix,e, L) equals g within BAND_STEP_TOL_DB. Asserted; the worst error printed."""
    errs = [(row["emitter"], band, b["step_db"] - g) for row in band_rows for band, b in row["bands"].items()]
    worst = max(errs, key=lambda e: abs(e[2]))
    rec = {"tol_db": BAND_STEP_TOL_DB, "max_abs_err_db": abs(worst[2]), "worst": {"emitter": worst[0], "band": worst[1],
                                                                                  "err_db": worst[2]}}
    assert abs(worst[2]) <= BAND_STEP_TOL_DB, f"M1 per-band step identity: {rec} (g {g:+.2f} dB)"
    return rec


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


def crossfade_residual(o: np.ndarray, a: np.ndarray, b: np.ndarray, s0: int, fs: float, channel: int = 0) -> np.ndarray:
    """One channel of r = (o - a) - m, with m the crossfade model of the step (o the stepped render, a the
    unstepped render, b the stepped IR rendered alone from sample 0): m = 0 before s0, (j/L)(b - a) over
    [s0, s0 + L) with j = t - s0, and b - a from s0 + L on. By companions (ii) and (iii) of `midfade_checks`,
    |r| <= 8u(|a| + |b|) at every sample, so r holds nothing a crossfade does not explain."""
    L = int(round(CROSSFADE_S * fs))
    oc, ac, bc = (x[:, channel].astype(np.float64) for x in (o, a, b))
    m = np.zeros_like(ac)
    j = np.arange(L, dtype=np.float64)
    m[s0 : s0 + L] = (j / L)[: max(0, min(L, m.size - s0))] * (bc - ac)[s0 : s0 + L]
    m[s0 + L :] = (bc - ac)[s0 + L :]
    return (oc - ac) - m


def click_check(o: np.ndarray, a: np.ndarray, b: np.ndarray, s0: int, fs: float, channel: int = 0) -> dict:
    """Item 6's click gate, form (b) (phase-07c-2b M3; Seats 3 and 5, review files 1-seat3.md and 1-seat5.md):
    `tools.acoustics clicks` on the crossfade residual r = (A - B) - m (`crossfade_residual`) rather than on A,
    so the detector never judges a frame against a noise or speech baseline (clicks.py's blind spot; builder
    file 32, K5). Pre-registered criterion: no detector event (2 kHz high-pass, 2 ms frames, absolute floor
    -90 dBFS) on r in the step region [s0 - 5 ms, s0 + L + 5 ms). Red on a hard switch (L = 0) and on a
    single-sample impulse in [s0, s0 + L) (tools/ci/test_abx_kit.py); measured floor: a spike of about -68 dBFS. Printed only, for continuity with 07c-2:
    the old comparison of A's events against B's peak frames (`legacy_new_in_step_region`), and the detector's event
    counts on A, B and E. Channel 0 in omni (the two outputs are asserted identical); each ear at 08-3 (`channel`).
    The spike floor printed is -90 - 10 log10(0.917/n_frame) (decider file 5, D-M3a; asserted bracket: caught at
    -68 dBFS, missed at -72 dBFS, tools/ci/test_abx_kit.py)."""
    L = int(round(CROSSFADE_S * fs))
    lo, hi = s0 - int(0.005 * fs), s0 + L + int(0.005 * fs)
    r = crossfade_residual(o, a, b, s0, fs, channel)
    det = clicks.detect_clicks(r, fs)
    hits = [ev for ev in det["events"] if lo <= ev["sample"] < hi]
    hp = clicks.highpass(r, fs)[max(0, lo) : hi]
    with np.errstate(divide="ignore"):
        rec = {"form": "b: residual against the crossfade model",
               "residual_peak_dbfs": float(20 * np.log10(max(float(np.max(np.abs(r[max(0, lo) : hi]))), 1e-30))),
               "residual_hp_peak_dbfs": float(20 * np.log10(max(float(np.max(np.abs(hp))), 1e-30))),
               "floor_dbfs": det["floor_dbfs"], "events_in_step_region": len(hits)}
    frame = int(round(clicks.FRAME_S * fs))
    rec["spike_floor_dbfs"] = SPIKE_FLOOR_DBFS_AT(frame)
    rec["spike_bracket_dbfs"] = {"caught": SPIKE_CAUGHT_DBFS, "missed": SPIKE_MISSED_DBFS}
    stepped = clicks.detect_clicks(o[:, channel].astype(np.float64), fs)["events"]
    unstepped = clicks.detect_clicks(a[:, channel].astype(np.float64), fs)["events"]
    rec["detector_events"] = {"A": len(stepped), "B": len(unstepped),
                              "E": len(clicks.detect_clicks(b[:, channel].astype(np.float64), fs)["events"])}
    plain = {ev["sample"] // frame for ev in unstepped}
    rec["legacy_new_in_step_region"] = sum(1 for ev in stepped if lo <= ev["sample"] < hi and ev["sample"] // frame not in plain)
    assert not hits, f"click_check (b): detector events on the crossfade residual in the step region: {hits}"
    return rec


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


def offline_reference(programme: np.ndarray, ir: np.ndarray) -> np.ndarray:
    """`sim::renderOffline` emulated (OfflineRender.cpp L133-171; phase-07c-2b builder file 4, fact 5, where it nulls
    against render_cli's own offline render at -219 dB or better): out_o = sum_e x_e * ir(e, o) in double, then
    float32; input channel e feeds emitter e. The offline reference for E (render_cli refuses --abx-step-db with
    --in/--out and no --realtime-emulation): the programme convolved with the stepped IR from --abx-stepped-ir."""
    outs = []
    for o in range(2):
        acc = None
        for e in range(2):
            part = sps.fftconvolve(programme[:, e].astype(np.float64), ir[:, 2 * e + o].astype(np.float64))
            acc = part if acc is None else acc + part
        outs.append(acc.astype(np.float32))
    return np.stack(outs, axis=1)


def null_db(x: np.ndarray, ref: np.ndarray) -> float:
    """10 log10(E(x - ref)/E(ref)) over the whole file (both outputs); the lengths must match."""
    assert x.shape == ref.shape, f"null: shapes differ ({x.shape} against {ref.shape})"
    r = x.astype(np.float64) - ref.astype(np.float64)
    e_r, e_ref = float(np.sum(r**2)), float(np.sum(ref.astype(np.float64) ** 2))
    return 10 * math.log10(max(e_r, 1e-300) / e_ref)


def gap_cue(e: np.ndarray, b: np.ndarray, onset: int, fs: float, delta_g_bands: dict | None = None) -> dict:
    """Print only (decider file 8, M3-C 6; Seat 1): the 1 kHz level of E - B relative to B over [N, N + 100 ms) and
    [N, N + 300 ms) (E the stepped IR rendered alone, B the unstepped render), and the per-band maximum of the heard
    pair's Delta G at the stimulus's g (largest magnitude, with its band)."""
    d = bands.filter_band(e[:, 0].astype(np.float64) - b[:, 0].astype(np.float64), fs, Q5_BAND_HZ)
    r = bands.filter_band(b[:, 0].astype(np.float64), fs, Q5_BAND_HZ)
    out: dict = {}
    for w in GAP_CUE_WINDOWS_S:
        n = int(round(w * fs))
        ed, er = float(np.sum(d[onset : onset + n] ** 2)), float(np.sum(r[onset : onset + n] ** 2))
        out[f"E_minus_B_re_B_1k_db_{int(round(w * 1000))}ms"] = 10 * math.log10(max(ed, 1e-300) / max(er, 1e-300))
    if delta_g_bands:
        band = max(delta_g_bands, key=lambda k: abs(delta_g_bands[k]))
        out["delta_G_band_max_db"] = {"band": band, "delta_G_db": delta_g_bands[band]}
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


def heard_delays(diag: dict, fs: float = FS) -> list[int]:
    """d_e per emitter: the direct sound's delay in the aligned IR, ceil((directS - alignmentShiftS) fs), in samples
    (phase-07c-2b decider file 5, D-M3b: every gap, pause and onset is placed as heard)."""
    align = float(diag["alignmentShiftS"])
    return [int(math.ceil((float(e["directS"]) - align) * fs - 1e-9)) for e in diag["emitters"]]


def noise_programme(t30_s: float, seed_index: int, chain_seed: int,
                    delays: tuple[int, ...] | list[int] = (0,)) -> tuple[np.ndarray, int, dict]:
    """Pulsed pink noise, two bursts before the step (>= one T30 of programme before it, item 7), then a heard
    silence and a burst after it (>= 2 s). Placed as heard (decider file 5, D-M3b; interrogator file 6): with d the
    emitters' heard delays, Delta = max d - min d and T = max(heard-IR T30, every tail T30) (decider file 8, M3-G;
    `t30_s` is that T), the gap between bursts 1 and 2
    is ceil((T fs + Delta)/P) P, so every heard gap is >= T; the onset N is the first partition boundary at or after
    the heard end of burst 2 (input end + max d); burst 3 starts at N + ceil(T fs/P) P, so the heard silence after N
    is >= T. The lead-in silence is LEAD_BLOCKS + a seeded 0..31 partitions (item 5). Returns the programme, N and
    the heard record (every quantity asserted here; M2's tail-T30 assertion is `gap_check`)."""
    rng = np.random.default_rng([chain_seed, 1000 + seed_index])
    d_min, d_max = min(delays), max(delays)
    delta = d_max - d_min
    t_fs = t30_s * FS
    burst = int(round(NOISE_BURST_S * FS / PARTITION)) * PARTITION
    gap = int(math.ceil((t_fs + delta) / PARTITION)) * PARTITION
    after = int(math.ceil(t_fs / PARTITION)) * PARTITION
    lead = (LEAD_BLOCKS + int(rng.integers(0, ONSET_SEED_RANGE))) * PARTITION
    b1, b2 = lead, lead + burst + gap
    heard_end_2 = b2 + burst + d_max
    onset = -(-heard_end_2 // PARTITION) * PARTITION
    b3 = onset + after
    total = b3 + burst + gap
    heard_gaps = [(b2 + d_min) - (b1 + burst + d_max), (b3 + d_min) - heard_end_2]
    rec = {"heard_delays_samples": [int(d) for d in delays], "delta_samples": int(delta),
           "onset_minus_heard_end_samples": [int(onset - (b2 + burst + d)) for d in delays],
           "heard_silence_after_onset_s": ((b3 + d_min) - onset) / FS, "heard_gaps_s": [g / FS for g in heard_gaps]}
    assert all(v >= 0 for v in rec["onset_minus_heard_end_samples"]), rec  # D-M3b assertion 1
    assert (b3 + d_min) - onset >= t_fs, rec  # assertion 2 (noise chain): heard silence after N >= T
    assert all(g >= t_fs for g in heard_gaps), rec  # assertion 3: every heard gap >= T
    assert onset - b1 >= t_fs and (total - onset) >= POST_STEP_S * FS, rec  # assertion 5 (item 7)
    x = np.zeros(total)
    for start in (b1, b2, b3):
        b = signals.apply_fades(signals.pink_noise(burst, int(rng.integers(0, 2**31))), FS, FADE_S)
        x[start : start + burst] = b * signals.db_to_amp(NOISE_LEVEL_DBFS)  # unit-RMS noise at the fixed level
    return x, onset, rec


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


def render_trial(binary, scene_path, programme: np.ndarray, onset: int, g: float, trial_dir: pathlib.Path,
                 stepped_ir: np.ndarray, delta_g_bands: dict | None = None) -> dict:
    """A (the step at the onset) and B (unstepped, held throughout) of one trial, with every item-6 assertion on
    them, and Seat 3's nulls (decider file 8, M3-C 7): B against render_cli's offline render of the same programme,
    E (the stepped IR rendered alone) against the programme convolved offline with the stepped IR (`stepped_ir`, from
    --abx-stepped-ir), each <= NULL_MAX_DB. Returns the trial's record (hashes, measured values, the gap-cue print)."""
    trial_dir.mkdir(parents=True, exist_ok=True)
    prog = trial_dir / "programme_dry.wav"
    wav.write_float32(prog, signals.to_stereo(programme), FS)
    a_path, b_path = trial_dir / "A.wav", trial_dir / "B.wav"
    with tempfile.TemporaryDirectory() as tmp:
        end_path, off_path = pathlib.Path(tmp) / "stepped_alone.wav", pathlib.Path(tmp) / "B_offline.wav"
        A = _render(binary, scene_path, prog, a_path, g, onset)
        B = _render(binary, scene_path, prog, b_path)
        E = _render(binary, scene_path, prog, end_path, g, 0)
        _run(binary, "--scene", scene_path, "--mode", "omni", "--in", prog, "--out", off_path)
        B_off = wav.read_float32(off_path)[0]
    prog_f32 = wav.read_float32(prog)[0]
    prog.unlink()
    assert np.array_equal(A[:, 0].view(np.uint32), A[:, 1].view(np.uint32)), "omni: both outputs must be the same (diotic)"
    peak = 20 * math.log10(max(float(np.max(np.abs(A))), float(np.max(np.abs(B))), 1e-30))
    assert peak <= MAX_PEAK_DBFS, f"a stimulus peaks at {peak:.2f} dBFS > {MAX_PEAK_DBFS} (no normalisation, item 10)"
    mid = midfade_checks(A, B, E, onset, FS)
    clk = click_check(A, B, E, onset, FS)
    nulls = {"B_vs_offline_db": null_db(B, B_off), "E_vs_offline_stepped_ir_db": null_db(E, offline_reference(prog_f32, stepped_ir)),
             "max_db": NULL_MAX_DB}
    assert nulls["B_vs_offline_db"] <= NULL_MAX_DB and nulls["E_vs_offline_stepped_ir_db"] <= NULL_MAX_DB, \
        f"null against the offline reference above {NULL_MAX_DB} dB: {nulls} (M3-C 7; goes back to Seats 3 and 5)"
    return {"onset_sample": onset, "onset_s": onset / FS, "g_db": g, "peak_dbfs": peak, "midfade": mid, "clicks": clk,
            "nulls": nulls, "gap_cue": gap_cue(E, B, onset, FS, delta_g_bands), "duration_s": len(A) / FS,
            "wet_band_change_db": wet_band_change(A, B, onset, FS),
            "sha256": {"A": sha256_file(a_path), "B": sha256_file(b_path)}}


def gap_check(scene: dict, min_gap_s: float, construction_t_s: float) -> dict:
    """M2 debt check (decider file 34, item 3), under M3-G (phase-07c-2b decider file 8): every gap, pause and item-7
    lead is built from T = max(heard-IR T30, every tail T30) at 1 kHz. Printed: the minimum heard gap or silence,
    T, the heard-IR T30 (Seat 9's label) and the tail T30 per emitter; asserted: T is that maximum, and the minimum
    heard gap or silence is >= T and >= every tail T30."""
    tail = scene["tail_T30_1k_s"]
    if any(t is None for t in tail):
        raise RuntimeError(f"tail T30(1 kHz) not measured on every emitter ({tail}): the M2 gap check cannot run")
    expected = max(scene["T30_1k_s"], *tail)
    assert abs(construction_t_s - expected) <= 1e-9, (construction_t_s, expected)  # M3-G: T = max(heard, tails)
    rec = {"min_gap_s": float(min_gap_s), "construction_T_s": float(construction_t_s),
           "construction_rule": "max(heard-IR T30, every tail T30) at 1 kHz (decider file 8, M3-G)",
           "heard_T30_1k_s": scene["T30_1k_s"], "heard_T30_label": scene["T30_1k_s_label"], "tail_T30_1k_s": tail,
           "min_gap_ge_tail_T30": bool(min_gap_s >= max(tail)), "min_gap_ge_construction_T": bool(min_gap_s >= construction_t_s)}
    assert rec["min_gap_ge_tail_T30"], f"M2: minimum gap {min_gap_s:.3f} s < tail T30 {max(tail):.3f} s (file 34 item 3)"
    assert rec["min_gap_ge_construction_T"], f"M3-G: minimum gap {min_gap_s:.3f} s < T {construction_t_s:.3f} s"
    return rec


def prepare_scene(out: pathlib.Path, binary: pathlib.Path, scene_name: str = DEFAULT_SCENE, log=print):
    """Writes the selected scene (item 9; committed JSON where there is one) and runs `check_scene` once. Returns
    (entry, scene_path, scene record, diagnostics); the work folder `out/_work` keeps the scene's IR (ir.wav)."""
    if scene_name not in SCENES:
        raise ValueError(f"unknown ABX scene {scene_name!r}; registered: {', '.join(SCENES)}")
    entry = SCENES[scene_name]
    require_class_line(entry)  # D-M3e: before anything is rendered
    out.mkdir(parents=True, exist_ok=True)
    scene_path = write_scene(entry, out / scene_file_name(entry.name))
    work = out / "_work"
    work.mkdir(exist_ok=True)
    sc = check_scene(binary, scene_path, work, log, entry)
    diag = sc.pop("diagnostics")
    return entry, scene_path, sc, diag


def build_chain(chain: str, binary: pathlib.Path, out: pathlib.Path, programme_for, scene, log=print, levels=LEVELS_DB,
                trials: int | None = None, min_gap_s: float | None = None, construction_t_s: float | None = None) -> dict:
    """Both blocks of one chain (0.9 dB and 0.5 dB: every stimulus is sealed before the run, item 11) plus the
    familiarisation pairs; `programme_for(seed_index) -> (x, onset, record)`; `scene` is `prepare_scene`'s result.
    `trials` limits each block (tests). `min_gap_s`, `construction_t_s`: the programme's shortest heard gap or
    silence and the T it was built from (the M2 check, M3-G)."""
    entry, scene_path, sc, diag = scene
    work = out / "_work"
    manifest: dict = {"chain": chain, "preregistration": "phase-07c-2 decider file 13, D-W2 final items 1-16 and Q5",
                      "scene_selection": "phase-07c-2b decider file 8, M3-S (fallbacks in order: "
                                         + ", ".join(FALLBACK_ORDER[1:]) + ")",
                      "criterion": f">= {CRITERION[chain]}/{SCORED_TRIALS}", "levels_db": list(levels),
                      "anchor": f"{ANCHOR_DB} dB, pass >= {ANCHOR_PASS}/{ANCHOR_TRIALS}", "fs": FS,
                      "partition": PARTITION, "block": BLOCK, "render_cli": str(binary), "blocks": {}, "ir_checks": {}}
    manifest["scene"] = sc
    manifest["m2_gap_check"] = gap_check(sc, min_gap_s, construction_t_s)
    gc = manifest["m2_gap_check"]
    log(f"{chain}: M2 gap check (M3-G): minimum heard gap {gc['min_gap_s']:.3f} s >= T {gc['construction_T_s']:.3f} s "
        f"= max(heard T30 {gc['heard_T30_1k_s']:.3f} s, tail T30(1 kHz) {', '.join(f'{x:.3f}' for x in gc['tail_T30_1k_s'])} s)")
    stepped_irs: dict[str, np.ndarray] = {}
    for g in sorted({s * x for x in (*levels, ANCHOR_DB) for s in (1, -1)}):
        u, s, target_share = ir_pair(binary, scene_path, g, work)
        band_rows = ir_band_shares(u, s, diag, g, target_share)
        rec = {**ir_assertions(u, s, diag, g), "bands": band_rows, "band_step_check": band_step_check(band_rows, g),
               "heard": heard_pair_metrics(u, s, float(diag["sampleRate"]), g)}
        stepped_irs[f"{g:+.1f}"] = s
        manifest["ir_checks"][f"{g:+.1f}"] = rec
        hb, h1k = rec["heard"]["broadband"], rec["heard"]["bands"]["1000"]
        log(f"{chain}: IR step {g:+.1f} dB: tail alone "
            + ", ".join(f"{r['tail_alone']['step_db']:+.4f}" for r in rec["rows"])
            + f" dB; per-band step error max {rec['band_step_check']['max_abs_err_db']:.2e} dB (<= {BAND_STEP_TOL_DB})"
            + "; window_unscaled_share (s_w, <= 2.3 %) "
            + ", ".join(f"{r['ax47_window']['window_unscaled_share']:.2e}" for r in rec["rows"])
            + "; per band (max over bands) "
            + ", ".join(f"{max(b['window_unscaled_share'] for b in r['bands'].values()):.2e}" for r in rec["bands"])
            + "; target_specular_share (max over bands) "
            + ", ".join(_fmt(max((b["target_specular_share"] or 0.0) for b in r["bands"].values()), 3) for r in rec["bands"])
            + f"; heard: tail share 1 kHz {h1k['tail_share_of_heard']:.3f} (broadband {hb['tail_share_of_heard']:.3f}), "
            f"delta G 1 kHz {h1k['delta_G_db']:+.3f} dB (broadband {hb['delta_G_db']:+.3f}), delta C80 1 kHz "
            f"{h1k['delta_C80_db']:+.3f} dB (broadband {hb['delta_C80_db']:+.3f})")

    def one(seed_index: int, g: float, trial_dir: pathlib.Path) -> tuple[dict, dict]:
        x, onset, record = programme_for(seed_index)
        key = f"{g:+.1f}"
        dg = {k: v["delta_G_db"] for k, v in manifest["ir_checks"][key]["heard"]["bands"].items()}
        rec = render_trial(binary, scene_path, x, onset, g, trial_dir, stepped_irs[key], dg)
        cue = rec["gap_cue"]
        log(f"{chain} {trial_dir.parent.name}/{trial_dir.name} ({g:+.1f} dB): onset {onset / FS:.3f} s, peak "
            f"{rec['peak_dbfs']:.1f} dBFS, mid-fade windows {rec['midfade']['windows']}, nulls B "
            f"{rec['nulls']['B_vs_offline_db']:.1f} / E {rec['nulls']['E_vs_offline_stepped_ir_db']:.1f} dB; gap cue "
            f"E - B re B (1 kHz) {cue['E_minus_B_re_B_1k_db_100ms']:+.2f} dB [N, N + 100 ms), "
            f"{cue['E_minus_B_re_B_1k_db_300ms']:+.2f} dB [N, N + 300 ms); max |delta G| "
            f"{cue['delta_G_band_max_db']['delta_G_db']:+.3f} dB at {cue['delta_G_band_max_db']['band']} Hz")
        return record, rec

    for level in levels:
        block = []
        for t in trial_plan(chain, level)[: trials or BLOCK_TRIALS]:
            record, rec = one(t["seed_index"], t["g_db"], out / f"{level:.1f}dB" / f"trial_{t['trial']:02d}")
            block.append({**t, **record, **rec})
        manifest["blocks"][f"{level:.1f}"] = block
    # Familiarisation (item 2, mandatory before any scored block): labelled A/B pairs, the anchor and each level, up
    # and down; never scored. Feedback during familiarisation is Seat 1's design choice (not set by this kit).
    fam = []
    for i, g in enumerate((ANCHOR_DB, -ANCHOR_DB, *[s * x for x in levels for s in (1, -1)])):
        record, rec = one(100 + i, g, out / "familiarisation" / f"pair_{i + 1:02d}_{g:+.1f}dB")
        fam.append({"pair": i + 1, "g_db": g, **record, **rec})
    manifest["familiarisation"] = fam
    stims = [*(t for blk in manifest["blocks"].values() for t in blk), *fam]
    manifest["summary"] = {
        "stimuli": len(stims), "peak_dbfs_max": max(t["peak_dbfs"] for t in stims),
        "null_B_worst_db": max(t["nulls"]["B_vs_offline_db"] for t in stims),
        "null_E_worst_db": max(t["nulls"]["E_vs_offline_stepped_ir_db"] for t in stims),
        "residual_hp_peak_max_dbfs": max(t["clicks"]["residual_hp_peak_dbfs"] for t in stims),
        "band_step_err_max_db": max(r["band_step_check"]["max_abs_err_db"] for r in manifest["ir_checks"].values()),
        "duration_s_mean": float(np.mean([t["duration_s"] for t in stims])),
        "duration_s_blocks_mean": float(np.mean([t["duration_s"] for blk in manifest["blocks"].values() for t in blk]))}
    for p in work.iterdir():
        p.unlink()
    work.rmdir()
    (out / "manifest.json").write_text(json.dumps(manifest, indent=1, default=float))
    return manifest


def build_noise_chain(out: pathlib.Path, binary: pathlib.Path, log=print, trials: int | None = None,
                      scene_name: str = DEFAULT_SCENE) -> dict:
    """The noise chain (CI, the listening pack): pulsed pink noise through the selected scene (default E)."""
    scene = prepare_scene(out, binary, scene_name, log)
    sc = scene[2]
    t_con, delays = sc["construction_T_s"], sc["heard_delays_samples"]

    def programme_for(seed_index: int):
        x, onset, heard = noise_programme(t_con, seed_index, KEY_SEED_BLOCKS["noise"], delays)
        return x, onset, {"programme": "pulsed pink noise", "noise_level_dbfs": NOISE_LEVEL_DBFS, "heard": heard}

    # M2 (D-M3b assertion 4): the shortest heard silence (gaps and the silence after N; equal on every seed index)
    _, _, heard = noise_programme(t_con, 0, KEY_SEED_BLOCKS["noise"], delays)
    gap_s = min(*heard["heard_gaps_s"], heard["heard_silence_after_onset_s"])
    return build_chain("noise", binary, out, programme_for, scene, log, trials=trials, min_gap_s=gap_s,
                       construction_t_s=t_con)


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


def speech_layout(len_s1: int, len_s2: int, end_of_speech: int, t_heard_s: float, t_con_s: float,
                  delays: list[int] | tuple[int, ...]) -> dict:
    """Where the speech programme puts things (decider file 8, M3-G, as restated in file 10 Part B): sentence 1 after
    the lead-in; sentence 2 at the input end of sentence 1 + ceil((0.43 T_heard + T) fs) + Delta (T = max(heard,
    tail) T30, Delta = max d - min d). Candidate onsets (item 7, phase-07c-2b decider files 30 and 34): partition
    boundaries (a) at or after the heard end of sentence 1 (input end + max d; D-M3b), (b) no later than 0.43 T_heard
    after the end of speech (Q5, unchanged) and (c) at least lead + ceil(T fs) samples after the stimulus start (the
    onset floor; programme is counted from the first sample of sentence 1's file, the lead-in excluded).
    `ab_boundaries` is the set under (a) and (b) alone; `item7_unrestricted` says whether its first boundary already
    meets (c). Asserted: an (a)(b) boundary exists; the candidate set is not empty; the heard pause >= T; the heard
    silence after the latest candidate >= T (so after every onset); item 7 on the first candidate (at least T of
    programme before it) and 2 s of programme after the latest."""
    lead = LEAD_BLOCKS * PARTITION
    d_min, d_max = min(delays), max(delays)
    delta = d_max - d_min
    t_fs = t_con_s * FS
    pause = int(math.ceil((Q5_ONSET_MAX_T30 * t_heard_s + t_con_s) * FS)) + delta
    s1_end = lead + len_s1
    s2_start = s1_end + pause
    eos = lead + end_of_speech
    s1_heard_end = s1_end + d_max  # the file's end, heard (TSP's trailing silence included)
    first = -(-max(eos + 1, s1_heard_end) // PARTITION) * PARTITION
    last_allowed = eos + int(math.floor(Q5_ONSET_MAX_T30 * t_heard_s * FS))
    ab = list(range(first, last_allowed + 1, PARTITION))  # (a) and (b)
    onset_floor = lead + int(math.ceil(t_con_s * FS))  # (c): lead + ceil(T fs)
    boundaries = [b for b in ab if b >= onset_floor]  # the candidate set: (a), (b) and (c)
    total = s2_start + len_s2
    rec = {"lead": lead, "pause": pause, "s1_end": s1_end, "s2_start": s2_start, "eos": eos, "total": total,
           "boundaries": boundaries, "ab_boundaries": ab, "onset_floor": onset_floor, "delta": delta,
           "item7_unrestricted": bool(ab) and ab[0] >= onset_floor, "removed_by_item7": len(ab) - len(boundaries),
           "heard_pause": (s2_start + d_min) - s1_heard_end,
           "heard_silence_after_latest_onset": (s2_start + d_min) - boundaries[-1] if boundaries else None}
    assert ab, "no partition boundary inside the Q5 window at or after the heard end of sentence 1"
    assert boundaries, (f"no candidate onset boundary: none of the {len(ab)} in the Q5 window lies at or after the "
                        f"onset floor lead + ceil(T fs) = {onset_floor} (item 7)")
    assert rec["heard_pause"] >= t_fs, rec  # M3-G: heard pause >= T
    assert rec["heard_silence_after_latest_onset"] >= t_fs, rec  # M3-G: heard silence after the onset >= T
    assert total - boundaries[-1] >= POST_STEP_S * FS, "less than 2 s of programme after the latest onset"
    assert boundaries[0] >= onset_floor and boundaries[0] - lead >= t_fs, \
        "less than one T of programme before the earliest candidate onset (item 7)"
    return rec


def item7_branch(lay: dict, scene_name: str, speaker: str, files: tuple[str, str] | list[str]) -> dict:
    """Which branch of decider file 34's rule a speech build is in, with the item-7 record. Unrestricted: the
    earliest (a)(b) boundary already meets (c) (the pair-search branch; nothing is pinned). Restricted: only the
    fallback pair MA01_01 + MA01_02 may build, and only on a scene whose onset floor is pinned
    (ITEM7_ONSET_FLOOR_PINNED, asserted equal); the manifest then carries the record wording (Seat 1 condition 3)."""
    pair = SPEECH_PAIR.get(scene_name)
    rec = {"rule": "candidates: (a) >= heard end of sentence 1, (b) <= end of speech + 0.43 T_heard, (c) >= lead + "
                   "ceil(T fs) (phase-07c-2b decider files 30 and 34)",
           "onset_floor_samples": lay["onset_floor"], "onset_floor_s": lay["onset_floor"] / FS,
           "first_ab_boundary_s": lay["ab_boundaries"][0] / FS, "first_candidate_boundary_s": lay["boundaries"][0] / FS,
           "unrestricted": bool(lay["item7_unrestricted"]), "boundaries_removed_by_c": lay["removed_by_item7"],
           "preregistered_pair": pair is not None and (speaker, tuple(files)) == (pair["speaker"], tuple(pair["files"]))}
    if lay["item7_unrestricted"]:
        rec["branch"] = "unrestricted: the earliest (a)(b) boundary meets (c) (pair search, decider file 34)"
        return rec
    if (speaker, tuple(files)) != ITEM7_FALLBACK_PAIR:
        raise RuntimeError(f"item 7: {speaker} {tuple(files)} needs the onset restriction (earliest (a)(b) boundary "
                           f"{rec['first_ab_boundary_s']:.3f} s < floor {rec['onset_floor_s']:.3f} s); restricted onsets "
                           f"are pre-registered only for the fallback pair {ITEM7_FALLBACK_PAIR} (decider file 34)")
    pinned = ITEM7_ONSET_FLOOR_PINNED.get(scene_name)
    if pinned is None:
        raise RuntimeError(f"item 7: the fallback branch is not in force on {scene_name} (no onset floor pinned; "
                           f"pre-registered pair {pair}); decider file 34 pins the floor only in the fallback branch")
    assert lay["onset_floor"] == pinned, f"item 7: onset floor {lay['onset_floor']} != pinned {pinned} (decider file 30)"
    rec["branch"] = "fallback: MA01_01 + MA01_02, onsets restricted by (c) (decider file 34)"
    rec["record_wording"] = ITEM7_FALLBACK_RECORD
    return rec


def q5_passing(candidates: list[int], margins: list[float]) -> list[int]:
    """Q5's >= 20 dB assertion over the candidate set; at least Q5_MIN_PASSING candidates must pass (decider files 25,
    30: the smallest count K4 and K7 accepted)."""
    passing = [b for b, mg in zip(candidates, margins) if mg >= Q5_MARGIN_DB]
    assert len(passing) >= Q5_MIN_PASSING, (f"Q5: {len(passing)} of {len(candidates)} candidate boundaries have tail >= "
                                            f"floor + {Q5_MARGIN_DB:g} dB, fewer than {Q5_MIN_PASSING} (decider file 30)")
    return passing


def draw_speech_onset(candidates: list[int], tail_db_at, floor_db: float, onset_floor: int,
                      seed_index: int) -> tuple[int, float, list[dict]]:
    """One stimulus's onset: a seeded permutation of the candidate set; a draw that fails Q5 (tail < floor + 20 dB) is
    replaced by the next one and recorded (replace-and-record). Item 7 is asserted on the drawn onset (decider file
    30: on every drawn onset)."""
    rng = np.random.default_rng([KEY_SEED_BLOCKS["speech"], 1000 + seed_index])
    replaced = []
    for k in rng.permutation(len(candidates)):
        onset = candidates[int(k)]
        tail_db = tail_db_at(onset)
        if tail_db >= floor_db + Q5_MARGIN_DB:
            assert onset >= onset_floor, f"item 7: drawn onset {onset} < onset floor lead + ceil(T fs) = {onset_floor}"
            return onset, tail_db, replaced
        replaced.append({"onset_sample": onset, "tail_db_1k": tail_db})
    raise RuntimeError(f"seed index {seed_index}: no onset in the Q5 window meets tail >= floor + {Q5_MARGIN_DB} dB")


def speech_programme(s1: np.ndarray, s2: np.ndarray, lay: dict) -> np.ndarray:
    x = np.zeros(lay["total"])
    x[lay["lead"] : lay["s1_end"]] = s1
    x[lay["s2_start"] :] = s2
    return x


def speech_q5_measure(binary: pathlib.Path, scene_path: pathlib.Path, x: np.ndarray, noise: np.ndarray, ir_len: int,
                      candidates: list[int]) -> tuple[float, list[float], np.ndarray]:
    """The rendered floor (TSP's own lead-in noise, looped past one IR length, through the room, steady state, 1 kHz)
    and the unstepped render's tail level above it at every candidate (1 kHz, 50 ms; Q5)."""
    with tempfile.TemporaryDirectory() as tmp:
        tmp = pathlib.Path(tmp)
        reps = int(math.ceil((ir_len + 2 * FS) / len(noise)))
        npath, nout = tmp / "noise.wav", tmp / "noise_out.wav"
        wav.write_float32(npath, signals.to_stereo(np.tile(noise, reps)), FS)
        rn = _render(binary, scene_path, npath, nout)
        floor_db = band_level_db(rn[:, 0].astype(np.float64), FS, ir_len + FS // 2, FS)
        # The unstepped render does not depend on the onset: render it once for the Q5 measurement.
        p, o = tmp / "x.wav", tmp / "y.wav"
        wav.write_float32(p, signals.to_stereo(x), FS)
        unstepped = _render(binary, scene_path, p, o)[:, 0].astype(np.float64)
    win = int(round(Q5_WINDOW_S * FS))
    return floor_db, [band_level_db(unstepped, FS, b, win) - floor_db for b in candidates], unstepped


def build_speech_chain(out: pathlib.Path, binary: pathlib.Path, speaker: str, files: tuple[str, str],
                       cache: pathlib.Path, log=print, trials: int | None = None, scene_name: str = DEFAULT_SCENE) -> dict:
    """The speech chain: TSP sentence 1, a pause, sentence 2 (item 8); the onset in the pause, drawn from the item-7
    candidate set (`speech_layout`: (a), (b), (c)), at a seeded partition boundary; the Q5 assertion on every
    stimulus, at least Q5_MIN_PASSING passing candidates, item 7 on every drawn onset (decider files 30 and 34). The
    pause is lengthened so that the heard pause and the heard silence after the onset are each >= T = max(heard, tail)
    T30 (decider file 8, M3-G). Printed before the seal (Seat 1 condition 1): the tail level above the floor at every
    drawn onset with its minimum and median, the realised window, the passing count, the replacement rate, the onset
    floor and the first candidate boundary."""
    zip_path = fetch_tsp(cache, log)
    s1, h1 = read_tsp_member(zip_path, speaker, files[0])
    s2, h2 = read_tsp_member(zip_path, speaker, files[1])
    pair = SPEECH_PAIR.get(scene_name)
    if pair is not None and (speaker, tuple(files)) == (pair["speaker"], tuple(pair["files"])):
        assert [h1, h2] == list(pair["member_sha256"]), f"pre-registered pair's member SHA-256s differ: {[h1, h2]}"
    scene = prepare_scene(out, binary, scene_name, log)
    _, scene_path, sc, _ = scene
    parts = speech_parts(s1, s2)
    t30, t_con, delays = sc["T30_1k_s"], sc["construction_T_s"], sc["heard_delays_samples"]
    h, fs = wav.read(out / "_work" / "ir.wav")
    lay = speech_layout(len(s1), len(s2), parts["end_of_speech"], t30, t_con, delays)
    item7 = item7_branch(lay, scene_name, speaker, files)
    pause, eos, boundaries = lay["pause"], lay["eos"], lay["boundaries"]
    x = speech_programme(s1, s2, lay)
    # The excerpt's SHA-256 is over its float32 little-endian samples, not over WAV bytes: libsndfile writes a
    # timestamped PEAK chunk into float WAVs, so two writes of the same samples hash differently (builder file 43).
    excerpt_digest = hashlib.sha256(np.ascontiguousarray(x, dtype="<f4").tobytes()).hexdigest()
    d_min = min(delays)
    rec_base = {"programme": "McGill TSP v2 speech", "speaker": speaker, "files": list(files),
                "member_sha256": [h1, h2], "excerpt_sha256": excerpt_digest,
                "excerpt_sha256_basis": "float32 LE samples",
                "end_of_speech_s": eos / FS, "pause_s": pause / FS, "T30_1k_s": t30, "construction_T_s": t_con,
                "pause_rule": "ceil((0.43 T_heard + T) fs) + Delta (decider file 8, M3-G)", "item7": item7,
                "heard": {"heard_delays_samples": delays, "delta_samples": lay["delta"],
                          "heard_pause_s": lay["heard_pause"] / FS,
                          "heard_silence_after_latest_onset_s": lay["heard_silence_after_latest_onset"] / FS}}
    floor_db, margins, unstepped = speech_q5_measure(binary, scene_path, x, parts["noise"], len(h), boundaries)
    rec_base["floor_db_1k"] = floor_db
    rec_base["q5_boundaries"] = len(boundaries)
    rec_base["q5_margin_db_per_boundary"] = margins
    passing = q5_passing(boundaries, margins)
    rec_base["q5_boundaries_passing"] = len(passing)
    rec_base["q5_latest_passing_after_eos_T30"] = (max(passing) - eos) / FS / t30
    rec_base.update(q5_window_record(boundaries, passing, eos, t30 * FS))
    win = int(round(Q5_WINDOW_S * FS))

    def programme_for(seed_index: int):
        onset, tail_db, replaced = draw_speech_onset(boundaries, lambda b: band_level_db(unstepped, FS, b, win),
                                                     floor_db, lay["onset_floor"], seed_index)
        silence = lay["s2_start"] + d_min - onset
        assert silence >= t_con * FS and lay["heard_pause"] >= t_con * FS, (silence, lay["heard_pause"])  # M3-G
        return x, onset, {**rec_base, "q5_tail_db_1k": tail_db, "q5_margin_db": tail_db - floor_db,
                          "onset_after_eos_T30": (onset - eos) / FS / t30, "replaced_onsets": replaced,
                          "heard_silence_after_onset_s": silence / FS}

    log(f"speech: {speaker} {files} ({item7['branch']}), end of speech {eos / FS:.3f} s, pause {pause / FS:.3f} s (heard "
        f"{lay['heard_pause'] / FS:.3f} s >= T {t_con:.3f} s), T30(1 kHz) {t30:.3f} s, "
        f"floor {floor_db:.1f} dB (1 kHz); item 7: onset floor {item7['onset_floor_s']:.4f} s, first (a)(b) boundary "
        f"{item7['first_ab_boundary_s']:.4f} s, first candidate boundary {item7['first_candidate_boundary_s']:.4f} s, "
        f"{lay['removed_by_item7']} removed by (c); {len(boundaries)} candidate boundaries, {len(passing)} of them "
        f"with tail >= floor + {Q5_MARGIN_DB:g} dB (>= {Q5_MIN_PASSING}; latest at "
        f"{rec_base['q5_latest_passing_after_eos_T30']:.3f} T30); "
        f"realised onset window [{rec_base['q5_realised_window_T30'][0]:.3f}, {rec_base['q5_realised_window_T30'][1]:.3f}]"
        f" T30 after the end of speech, passing set contiguous from the first boundary: "
        f"{rec_base['q5_passing_contiguous_from_first']}; replacement: first draw replaced with p "
        f"{rec_base['q5_first_draw_replaced_p']:.3f}, {rec_base['q5_expected_replaced_per_stimulus']:.2f} replaced "
        "onsets per stimulus expected")
    manifest = build_chain("speech", binary, out, programme_for, scene, log, trials=trials,
                           min_gap_s=min(rec_base["heard"]["heard_pause_s"], rec_base["heard"]["heard_silence_after_latest_onset_s"]),
                           construction_t_s=t_con)
    stims = [*(t for blk in manifest["blocks"].values() for t in blk), *manifest["familiarisation"]]
    drawn = [float(t["q5_margin_db"]) for t in stims]
    n_replaced = sum(len(t["replaced_onsets"]) for t in stims)
    onset_margins = {"per_stimulus_db": drawn, "min_db": min(drawn), "median_db": float(np.median(drawn)),
                     "basis": "tail level above the floor at the drawn onset, 1 kHz band, 50 ms window (Q5)",
                     "replaced_onsets": n_replaced, "replaced_per_stimulus": n_replaced / len(stims),
                     "onsets_ge_floor": all(t["onset_sample"] >= lay["onset_floor"] for t in stims)}
    assert onset_margins["onsets_ge_floor"]  # item 7 on every drawn onset (decider file 30)
    log(f"speech, before the seal: tail above floor at the drawn onsets min {onset_margins['min_db']:.1f} dB, median "
        f"{onset_margins['median_db']:.1f} dB ({len(drawn)} stimuli); realised window "
        f"[{rec_base['q5_realised_window_T30'][0]:.3f}, {rec_base['q5_realised_window_T30'][1]:.3f}] T30_heard; "
        f"{len(passing)} passing of {len(boundaries)}; replacement: p {rec_base['q5_first_draw_replaced_p']:.3f}, "
        f"realised {n_replaced} replaced onsets ({onset_margins['replaced_per_stimulus']:.2f} per stimulus); onset floor "
        f"{item7['onset_floor_s']:.4f} s; first candidate boundary {item7['first_candidate_boundary_s']:.4f} s"
        + (f"; record: {item7['record_wording']}" if "record_wording" in item7 else ""))
    manifest["tsp"] = {"url": TSP_URL, "sha256": TSP_SHA256, "notice": TSP_NOTICE, **{k: v for k, v in rec_base.items()},
                       "q5_drawn_onset_margin": onset_margins}
    manifest["item7"] = item7
    (out / "manifest.json").write_text(json.dumps(manifest, indent=1, default=float))
    (out / "NOTICE-TSP.txt").write_text(TSP_NOTICE + "\n")
    return manifest


def tsp_pairs(zip_path: pathlib.Path, speaker: str) -> list[tuple[str, str]]:
    """The speaker's file pairs in TSP index order (decider file 34): within each group, files 01 + 02, 03 + 04, ...;
    the groups in order (MA01_..., then MA02_..., ...)."""
    if speaker in ("CA", "CB"):
        raise ValueError("the child recordings CA and CB are excluded (adult speakers only, item 8; researcher R35)")
    with zipfile.ZipFile(zip_path) as z:
        stems = sorted(pathlib.PurePosixPath(n).stem for n in z.namelist()
                       if n.startswith(f"48k/{speaker}/") and n.endswith(".wav"))
    groups: dict[str, list[str]] = {}
    for s in stems:
        groups.setdefault(s.split("_")[0], []).append(s)
    return [(g[i], g[i + 1]) for _, g in sorted(groups.items()) for i in range(0, len(g) - 1, 2)]


def search_speech_pairs(out: pathlib.Path, binary: pathlib.Path, cache: pathlib.Path, speaker: str = "MA", log=print,
                        trials: int | None = None, scene_name: str = DEFAULT_SCENE) -> dict:
    """The pre-registered pair search (phase-07c-2b decider file 34; interrogator files 36 and 37): adult pairs in TSP
    index order from MA01_03 + MA01_04 (MA01_01 + MA01_02 is the fallback pair), on the scene in use. Per pair, first
    from the dry files: the earliest (a)(b) boundary and whether it meets (c); then one unstepped render: Q5's passing
    count over the candidate set; only a pair meeting (c) unrestricted with >= Q5_MIN_PASSING passing gets the full
    speech build (every pre-seal assertion on every stimulus). The first pair passing it is the speech pair; every
    pair tried is recorded (`search.json`, one printed row each). No pair is chosen by listening."""
    zip_path = fetch_tsp(cache, log)
    scene = prepare_scene(out / "_scene", binary, scene_name, log)
    _, scene_path, sc, _ = scene
    t30, t_con, delays = sc["T30_1k_s"], sc["construction_T_s"], sc["heard_delays_samples"]
    h, _ = wav.read(out / "_scene" / "_work" / "ir.wav")
    pairs = [p for p in tsp_pairs(zip_path, speaker) if (speaker, p) != ITEM7_FALLBACK_PAIR]
    rows, chosen = [], None
    for a, b in pairs:
        s1, h1 = read_tsp_member(zip_path, speaker, a)
        s2, h2 = read_tsp_member(zip_path, speaker, b)
        parts = speech_parts(s1, s2)
        row: dict = {"pair": [a, b], "member_sha256": [h1, h2], "end_of_speech_s": (LEAD_BLOCKS * PARTITION
                                                                                    + parts["end_of_speech"]) / FS}
        rows.append(row)
        try:
            lay = speech_layout(len(s1), len(s2), parts["end_of_speech"], t30, t_con, delays)
        except AssertionError as e:
            row["result"] = f"layout refused: {e}"
            log(f"search {a} + {b}: {row['result']}")
            continue
        eos = lay["eos"]
        row.update({"first_ab_boundary_s": lay["ab_boundaries"][0] / FS, "onset_floor_s": lay["onset_floor"] / FS,
                    "c_unrestricted": bool(lay["item7_unrestricted"]), "ab_boundaries": len(lay["ab_boundaries"]),
                    "candidates": len(lay["boundaries"]), "heard_pause_s": lay["heard_pause"] / FS,
                    "heard_silence_after_latest_onset_s": lay["heard_silence_after_latest_onset"] / FS})
        x = speech_programme(s1, s2, lay)
        _, margins, _ = speech_q5_measure(binary, scene_path, x, parts["noise"], len(h), lay["boundaries"])
        passing = [bd for bd, mg in zip(lay["boundaries"], margins) if mg >= Q5_MARGIN_DB]
        row["q5_passing"] = len(passing)
        if passing:
            q5 = q5_window_record(lay["boundaries"], passing, eos, t30 * FS)
            row.update({"q5_window_T30": q5["q5_realised_window_T30"], "q5_first_draw_replaced_p": q5["q5_first_draw_replaced_p"]})
        if not lay["item7_unrestricted"]:
            row["result"] = (f"(c) fails unrestricted: earliest (a)(b) boundary {row['first_ab_boundary_s']:.3f} s < onset "
                             f"floor {row['onset_floor_s']:.3f} s")
        elif len(passing) < Q5_MIN_PASSING:
            row["result"] = f"Q5: {len(passing)} passing < {Q5_MIN_PASSING}"
        else:
            try:
                m = build_speech_chain(out / f"{a}+{b}", binary, speaker, (a, b), cache, log, trials, scene_name)
            except (AssertionError, RuntimeError) as e:
                row["result"] = f"pre-seal assertion failed: {e}"
            else:
                stims = [*(t for blk in m["blocks"].values() for t in blk), *m["familiarisation"]]
                row.update({"stimuli": len(stims), "peak_dbfs_max": m["summary"]["peak_dbfs_max"],
                            "form_b_events": sum(t["clicks"]["events_in_step_region"] for t in stims),
                            "null_B_worst_db": m["summary"]["null_B_worst_db"],
                            "null_E_worst_db": m["summary"]["null_E_worst_db"],
                            "midfade_windows_min": min(t["midfade"]["windows"] for t in stims),
                            "q5_drawn_onset_margin_min_db": m["tsp"]["q5_drawn_onset_margin"]["min_db"],
                            "q5_drawn_onset_margin_median_db": m["tsp"]["q5_drawn_onset_margin"]["median_db"],
                            "q5_window_T30": m["tsp"]["q5_realised_window_T30"],
                            "q5_first_draw_replaced_p": m["tsp"]["q5_first_draw_replaced_p"],
                            "band_step_err_max_db": m["summary"]["band_step_err_max_db"],
                            "result": "qualifies: every pre-seal assertion passed", "manifest": str(out / f"{a}+{b}")})
                chosen = row
        log(f"search {a} + {b}: earliest (a)(b) boundary {row['first_ab_boundary_s']:.3f} s, onset floor "
            f"{row['onset_floor_s']:.3f} s, (c) unrestricted {row['c_unrestricted']}, Q5 passing {row['q5_passing']} of "
            f"{row['candidates']} candidates, window {[round(v, 3) for v in row.get('q5_window_T30', [])]} T30, "
            f"first draw replaced p {row.get('q5_first_draw_replaced_p', float('nan')):.3f}, heard pause "
            f"{row['heard_pause_s']:.3f} s, silence after latest onset {row['heard_silence_after_latest_onset_s']:.3f} s"
            + (f", peak {row['peak_dbfs_max']:.1f} dBFS, form (b) events {row['form_b_events']}, nulls B "
               f"{row['null_B_worst_db']:.1f} / E {row['null_E_worst_db']:.1f} dB, mid-fade windows >= "
               f"{row['midfade_windows_min']}" if "stimuli" in row else "")
            + f": {row['result']}")
        if chosen is not None:
            break
    result = {"scene": scene_name, "scene_sha256": sc["scene_sha256"], "speaker": speaker, "rule": "phase-07c-2b decider "
              "file 34 (pair search), interrogator files 36 and 37", "construction_T_s": t_con, "T30_1k_s": t30,
              "rows": rows, "chosen": None if chosen is None else {"pair": chosen["pair"], "member_sha256": chosen["member_sha256"]},
              "branch": "pair found" if chosen is not None else
                        f"no pair qualifies: fallback branch, {ITEM7_FALLBACK_PAIR} with the onset restriction"}
    log(f"search: {result['branch']}" + (f": {' + '.join(chosen['pair'])}" if chosen else ""))
    (out / "search.json").write_text(json.dumps(result, indent=1, default=float))
    return result


# ---------------------------------------------------------------------------------------------------------
# AX49 L4: held-chord ABX, provisional against exact tail (run sheet section 8)
# ---------------------------------------------------------------------------------------------------------
# Phase-07c-2b decider file 10 Part A (L4-S, L4-D 1-14, L4-T), interrogator file 13, Seat 5 file 14; decider file 17
# (D1: a primary and a pre-built rerun block sealed together, the anchor scored first and a failed anchor voiding its
# block unread; P1: the wording; P8: the void rule and the IR-hash record) and file 21 (P8-3: the manifest prints the
# AX49 constants each stimulus was built with); builder file 15 (render_cli --provisional-ir, --provisional-timing,
# --provisional-handover-sample; k = 0.84). Every stimulus is rendered by the shipped engine through render_cli; A
# under the validation-only --provisional-ir flag ("provisional tail, validation-only flag"), B without it.

L4_K = 0.84  # L4-S: every band's absorption x k; builder file 15 measured T60_max 7.9955 s at k = 0.84
L4_T60_MAX_S, L4_T60_MAX_TOL_S = 8.0, 0.1  # L4-S: k is chosen so that T60_max = 8.0 +/- 0.1 s
L4_TAIL_SEED = 106  # stone_box.json's tailSeed (L4-S)
L4_SCORED, L4_ANCHORS, L4_BLOCK_TRIALS, L4_BREAK_AFTER = 16, 6, 22, 11  # L4-D trials
L4_CRITERION = 12  # >= 12/16 (P1)
L4_FAMILY_ALPHA_EXACT = 2517 / 65536  # P(K >= 12), K ~ Bin(16, 1/2) = 0.0384 (decider file 17, R-L1)
L4_FAMILY_ALPHA = 0.038
L4_POWER_AT_075 = 0.63
L4_ANCHOR_DB, L4_ANCHOR_PASS = 3.0, 5  # decider file 41 (A-ii): B against B with the tail stepped +3 dB; pass >= 5/6
L4_ANCHOR_CHANCE = 7 / 64  # P(>= 5/6 | 1/2) under random X, for any role assignment (decider file 41, A-L2)
L4_RENDER_NULL_DB = -120.0  # L4-D 2 on the renders over [boundary, fade start): Seat 3's per-sample criterion at
# Phase 06's -120 dB level (decider file 41 (4); interrogator file 42)
L4_PRINT_4 = ("consistency check; weak on this scene (all predicted |A/B| < 0.01 dB); red test: a 1.2 dB hot "
              "provisional fails it")  # decider file 41 (3)
L4_PRINT_7 = "realised Schroeder drop [t_mix,e,max, L_f), one realisation, not asserted"  # decider file 41 (2)
L4_PRINT_2 = "Seat 3's per-sample criterion at Phase 06's -120 dB level"  # interrogator file 42
L4_BLOCKS = ("primary", "rerun")  # D1: both built and sealed together, before the session
L4_KEY_SEEDS = {"primary": 7101, "rerun": 7102}  # each block's own seeded trial order and anchor positions (D1)
L4_MAX_PEAK_DBFS = -3.0  # L4-D: peak <= -3 dBFS
L4_SILENCE_MARGIN_S = 0.5  # L4-D: at least L + 0.5 s of silent input after the release
L4_PREFIX_DB = 20.0 * math.log10(10.0 ** (1.0 / 20.0) - 1.0)  # AX47 (b): -18.27 dB
L4_STEP_TOL_DB = 0.05  # L4-D 4
L4_DECAY_MIN_DB = 18.7  # L4-D 7 (AX49)
L4_SHARE_MAX = 0.0134  # L4-D 8: e^(-13.82 x 0.312) (AX49 K17')
L4_GHOST_OFFSETS_S = (0.0, 1.0, 2.0, 5.0)  # L4-D 13: release + L_p + {0, 1, 2, 5} s
L4_GHOST_LABEL = "noise-excitation (Schroeder) estimate"
L4_DEMO_DELAY_S = 1.0  # L4-D 14: handover at the first partition boundary at or after t_r + L_p + 1 s
L4_FLAG_NOTE = "provisional tail, validation-only flag"
# AX49's provisional construction (P8 item 3, P8-3): the constants each stimulus is built with, printed per stimulus;
# f, the fade and L's rule are checked against render_cli's --provisional-timing at every build.
AX49_F = 0.312
AX49_FADE_S = 0.1
AX49_L_RULE = "L = min(1.5 T60_max, 12 s)"
AX49_NORMALISATION = ("each band divided by sqrt(E_p,b / f_b), E_p,b its realised energy over [0, L_f), f_b = (1 - "
                      "e^(-13.82 L_f / T60_b)) / (1 - e^(-13.82 L / T60_b)); never scaled up for the energy past L_p")
ENERGY_DECAY_PER_T60 = 13.815510557964274  # tail::kEnergyDecayPerT60 = ln(10^6)
TAIL_FADE_HALF_S = 0.0025  # tail::kCrossfadeHalfS: the ISM -> tail crossfade [t_mix - 2.5 ms, t_mix + 2.5 ms]

# The chord (L4-D, Seat 1), versioned: deterministic additive synthesis, open voicing C2-G2-C3-E3-G3-C4 in equal
# temperament (A4 = 440 Hz), harmonic partials up to 8 kHz tilted -3 dB/octave (amplitude n^-1/2 against the
# fundamental), no vibrato, a 50 ms raised-cosine onset and a 10 ms raised-cosine release. Partial phases are fixed
# by a seeded draw (a sum of zero-phase partials would peak needlessly). One fixed, recorded gain for every file.
L4_CHORD_VERSION = 1
L4_CHORD_MIDI = (36, 43, 48, 52, 55, 60)
L4_CHORD_MAX_HZ = 8000.0
L4_CHORD_TILT_DB_PER_OCT = -3.0
L4_CHORD_ONSET_S, L4_CHORD_RELEASE_S = 0.050, 0.010
L4_CHORD_PHASE_SEED = 4049
L4_CHORD_GAIN_DB = -12.0  # the dry chord's peak level (dBFS), fixed for all files (L4-D "no normalisation")
L4_LEAD_SAMPLES = LEAD_BLOCKS * PARTITION  # silent lead-in (also > the 30 ms anchor fade from sample 0)

L4_LABEL = ("Long-decay test room, hard stone box with uniform absorption, T60_max 8 s; provisional-vs-exact tail test "
            "(provisional tail, validation-only flag); not a validated preset")
# L4-S's detail lines (Seat 9's template with Seat 2's wording); the fields are measured at build. Seat 9's D/R class
# bands (phase-07c-2b review file 7-seat9): direct-dominated >= +3 dB, near-balanced between, tail-dominated <= -3 dB.
L4_LABEL_DETAIL = (
    "Geometry {dims} m, listener {listener}, emitters {emitters}; α = k × stone_box per band (k = {k}); s 0.1 "
    "(early part specular only, AX21); tailSeed {seed}; {fs_khz:g} kHz; emitters {r} m away.",
    "T60 per band {t60s} s; T60_max {t60max:.4f} s in band {t60max_band} Hz.",
    "D/R at 1 kHz {drr_1k} dB against {drr_diffuse:+.1f} dB at r/r_c {r_over_rc:.2f} (Kuttruff Eq. 5.44, Sabine A "
    "{sabine_a:.1f} m²). ᾱ ≈ {abar:.3f} (expected 0.04–0.07) is small, so §5.6's ᾱ caveat does not apply.",
    "t_mix,e,max {mix:.5f} s, L_f {lf:.4f} s, L_p {lp:.4f} s and L {L:.3f} s.",
    "Cut depth per band, 10·log10(E_B[L_f, L)/E_B[0, L)) on B's heard IR (dB): {cuts}; the chord's band energy "
    "beside it (dB re its total): {chord_bands}.",
    "The early reflections are identical in A and B.",
    "Stimulus scene, not a room prediction.",
    "Class: long-decay, {dr_class} (heard D/R {drr_heard:+.1f} dB), cut {cut:.1f} dB in the T60_max band",
)


def scene_stone_box_l4(k: float = L4_K) -> dict:
    """L4-S: tests/scenes/valid/stone_box.json with every band's absorption times k (built as
    tools/ci/test_provisional_flag.py's l4_scene builds it, so the timing it measured is this scene's)."""
    scene = json.loads((REPO / "tests" / "scenes" / "valid" / "stone_box.json").read_text(encoding="utf-8"))
    for surface in scene["room"]["surfaces"].values():
        surface["absorption"] = [a * k for a in surface["absorption"]]
    scene["extensions"] = {"notes": f"L4 (phase-07c-2b decider file 10): stone_box with absorption x {k}"}
    return scene


L4_SCENE = AbxScene("stone_box_l4", scene_stone_box_l4, L4_LABEL, L4_LABEL_DETAIL, "stone_box_l4.json")


def dr_class(drr_db: float) -> str:
    """Seat 9's D/R class (review file 7-seat9, 'Class bands'), applied to the measured heard D/R."""
    if drr_db >= 3.0:
        return "direct-dominated"
    if drr_db > -3.0:
        return "near-balanced"
    return "tail-dominated"


def fill_l4_label(entry: AbxScene, values: dict) -> list[str]:
    """The L4 detail lines with the measured values; refuses a template without a Class line (D-M3e) and any field
    left unfilled."""
    require_class_line(entry)
    lines = [t.format(**values) for t in entry.label_detail]
    left = [x for x in lines if "{" in x or "[measured" in x]
    if left:
        raise RuntimeError(f"L4 label lines left unfilled: {left}")
    return lines


@functools.lru_cache(maxsize=4)
def engine_band_firs(fs: float) -> tuple[tuple[np.ndarray, ...], int]:
    """sim::ism::OctaveFilterbank (src/sim/ism/BandRenderer.cpp) in numpy: 7 linear-phase Kaiser-windowed-sinc
    low-passes at sqrt(2) x the band centres (transition +-1/8 octave, 80 dB stopband), complementary band filters
    B_b = P_b - P_(b-1), centred, length 2 maxHalf + 1. The filterbank the tail generator and the ISM use, and the
    one tests/unit/test_interim.cpp splits the AX47 (b) prefix with; h = 2 maxHalf (generator + analysis)."""
    stop_db, trans_oct = 80.0, 0.125
    beta = 0.1102 * (stop_db - 8.7)
    lows = []
    for fc in bands.OCTAVE_BANDS_HZ[:-1]:
        fx = bands.exact_centre_hz(fc) * math.sqrt(2.0)
        transition = fx * (2.0**trans_oct - 2.0**-trans_oct)
        taps = int(math.ceil((stop_db - 8.0) / (2.285 * (2.0 * math.pi * transition / fs))))
        half = (taps + 1) // 2
        m = np.arange(-half, half + 1, dtype=np.float64)
        window = np.i0(beta * np.sqrt(np.maximum(0.0, 1.0 - (m / half) ** 2))) / np.i0(beta)
        wc = 2.0 * fx / fs
        h = wc * np.sinc(wc * m) * window
        lows.append(h / np.sum(h))
    max_half = max((len(h) - 1) // 2 for h in lows)
    out = []
    for b in range(len(bands.OCTAVE_BANDS_HZ)):
        f = np.zeros(2 * max_half + 1)
        for k, sign in ((b, 1.0), (b - 1, -1.0)):
            if 0 <= k < len(lows):
                off = max_half - (len(lows[k]) - 1) // 2
                f[off : off + len(lows[k])] += sign * lows[k]
        if b == len(lows):
            f[max_half] += 1.0
        out.append(f)
    return tuple(out), max_half


def engine_bands(x: np.ndarray, fs: float) -> list[np.ndarray]:
    """x split into the engine's 8 bands (centred, so zero-phase; the output has x's length)."""
    firs, half = engine_band_firs(float(fs))
    x = np.asarray(x, dtype=np.float64)
    return [sps.oaconvolve(x, h)[half : half + len(x)] for h in firs]


def l4_chord(hold_samples: int, total_samples: int, fs: int = FS) -> tuple[np.ndarray, dict]:
    """The L4 chord (L4_CHORD_*), starting at L4_LEAD_SAMPLES: the 50 ms onset and the steady part fill the hold H
    (onset start to release start), then the 10 ms release; zeros to `total_samples`. Peak = L4_CHORD_GAIN_DB."""
    rng = np.random.default_rng(L4_CHORD_PHASE_SEED)
    n_on, n_rel = int(round(L4_CHORD_ONSET_S * fs)), int(round(L4_CHORD_RELEASE_S * fs))
    n = hold_samples + n_rel
    t = np.arange(n, dtype=np.float64) / fs
    y = np.zeros(n)
    partials = []
    for midi in L4_CHORD_MIDI:
        f0 = 440.0 * 2.0 ** ((midi - 69) / 12.0)
        for h in range(1, int(L4_CHORD_MAX_HZ // f0) + 1):
            amp = 10.0 ** (L4_CHORD_TILT_DB_PER_OCT * math.log2(h) / 20.0)
            y += amp * np.sin(2.0 * np.pi * h * f0 * t + rng.uniform(0.0, 2.0 * np.pi))
            partials.append(h * f0)
    env = np.ones(n)
    env[:n_on] = 0.5 * (1.0 - np.cos(np.pi * (np.arange(n_on) + 0.5) / n_on))
    env[hold_samples:] = 0.5 * (1.0 + np.cos(np.pi * (np.arange(n_rel) + 0.5) / n_rel))
    y *= env
    y *= signals.db_to_amp(L4_CHORD_GAIN_DB) / np.max(np.abs(y))
    x = np.zeros(total_samples)
    x[L4_LEAD_SAMPLES : L4_LEAD_SAMPLES + n] = y
    rec = {"version": L4_CHORD_VERSION, "midi": list(L4_CHORD_MIDI), "notes": "C2 G2 C3 E3 G3 C4 (equal-tempered, A4 440 Hz)",
           "partials": len(partials), "max_partial_hz": max(partials), "tilt_db_per_octave": L4_CHORD_TILT_DB_PER_OCT,
           "onset_s": L4_CHORD_ONSET_S, "release_s": L4_CHORD_RELEASE_S, "phase_seed": L4_CHORD_PHASE_SEED,
           "gain": f"dry peak {L4_CHORD_GAIN_DB} dBFS, one fixed gain for every file (no normalisation)",
           "lead_samples": L4_LEAD_SAMPLES, "hold_samples": hold_samples, "release_start_sample": L4_LEAD_SAMPLES + hold_samples,
           "release_end_sample": L4_LEAD_SAMPLES + n, "total_samples": total_samples}
    return x, rec


def _ir_band_energies(h: np.ndarray, fs: float, start: int, stop: int) -> list[float]:
    """Per engine band, the energy of the IR gated to [start, stop) (the gate applied before the band split)."""
    g = np.zeros(len(h))
    g[start:stop] = h[start:stop]
    return [float(np.sum(b**2)) for b in engine_bands(g, fs)]


def _band_dict(values) -> dict[str, float]:
    return {bands.band_key(fc): float(v) for fc, v in zip(bands.OCTAVE_BANDS_HZ, values)}


def l4_ir_checks(A: np.ndarray, B: np.ndarray, timing: dict, diag: dict) -> dict:
    """L4-D's IR-level assertions on A (the provisional IR, --provisional-ir --ir) and B (the exact IR, --ir), float32
    arrays (taps x 4: emitter e, output o at column 2e + o). Times are emission times; IR tap n is emission time
    n/fs + alignmentShiftS (unit-decay index n + offset, offset = round(shift fs)).
    2. A and B bit-identical before the earliest tail crossfade start (t_mix,e - 2.5 ms, the earliest emitter);
    3. per emitter and band, 10 log10(E(A - B)/E(B)) <= -18.27 dB over [t_mix,e, L_f - h), h = 2 maxHalf of the
       engine filterbank (the prefix split as tests/unit/test_interim.cpp splits it);
    4. per emitter and band, the A/B energy over [t_mix,e,max + 2.5 ms, L_f) equals AX47 (b)'s step,
       +10 log10(1 + (1 - f_b) delta_b) (A against B; the provisional-to-exact step is its negative), within 0.05 dB,
       delta_b the realised remainder's deviation measured on B (below);
    5. A is zero from L_p on; 6. B is L long; 7. the decay from t_mix,e,max to L_f, 60 (L_f - t_mix,e,max)/T60_b,
    is >= 18.7 dB in every band, read on the model (decider file 41 (2)); B's realised Schroeder drop over
    [t_mix,e,max, L_f) is printed beside it, one realisation, not asserted; 8. B's share past L_f <= 0.0134 per band."""
    fs = float(timing["sampleRate"])
    shift = float(diag["alignmentShiftS"])
    offset = int(round(shift * fs))
    lf_unit = int(math.ceil(timing["fadeStartS"] * fs))
    lp_unit = int(math.ceil(timing["endS"] * fs))
    l_unit = int(math.ceil(timing["exactS"] * fs))
    lf_tap, lp_tap, l_tap = lf_unit - offset, lp_unit - offset, l_unit - offset
    mixes = [float(e["mixS"]) for e in diag["emitters"]]
    mix_max = float(timing["mixMaxS"])
    assert abs(mix_max - max(mixes)) <= 1e-12, (mix_max, mixes)
    firs, half = engine_band_firs(fs)
    h_prefix = 2 * half
    t60 = [float(v) for v in timing["bandsT60S"]]
    rec: dict = {"alignment_shift_s": shift, "offset_samples": offset, "lf_tap": lf_tap, "lp_tap": lp_tap, "l_tap": l_tap,
                 "h_samples": h_prefix, "engine_filterbank_max_half": half}
    # 2. the first tap with a tail weight > 0 per emitter: n/fs + shift > t_mix,e - 2.5 ms
    fade_starts = [int(math.floor((m - TAIL_FADE_HALF_S - shift) * fs)) + 1 for m in mixes]
    k0 = min(fade_starts)
    first = []
    for c in range(A.shape[1]):
        n = min(len(A), len(B))
        d = np.flatnonzero(A[:n, c].view(np.uint32) != B[:n, c].view(np.uint32))
        first.append(int(d[0]) if d.size else n)
    rec["2_ir"] = {"earliest_tail_fade_start_tap": k0, "tail_fade_start_taps": fade_starts, "first_differing_tap": first}
    assert min(first) >= k0, f"L4-D 2: A and B differ at tap {min(first)} < the earliest tail fade start {k0}"
    # 3. prefix
    prefix = []
    for e, m in enumerate(mixes):
        c = 2 * e
        frm = int(round((m - shift) * fs))
        to = int(round((timing["fadeStartS"] - shift) * fs)) - h_prefix
        assert to > frm, (frm, to)
        n = to + half
        ab, bb = engine_bands(A[:n, c].astype(np.float64), fs), engine_bands(B[:n, c].astype(np.float64), fs)
        row = {}
        for i, fc in enumerate(bands.OCTAVE_BANDS_HZ):
            diff = float(np.sum((ab[i][frm:to] - bb[i][frm:to]) ** 2))
            ref = float(np.sum(bb[i][frm:to] ** 2))
            row[bands.band_key(fc)] = 10 * math.log10(max(diff, 1e-300) / ref)
        prefix.append({"emitter": e, "from_tap": frm, "to_tap": to, "db": row})
        worst = max(row.values())
        assert worst <= L4_PREFIX_DB, f"L4-D 3 (prefix): emitter {e} {row} > {L4_PREFIX_DB:.2f} dB"
    rec["3_prefix"] = {"bound_db": L4_PREFIX_DB, "rows": prefix,
                       "worst_db": max(max(r["db"].values()) for r in prefix)}
    # 4. the A/B step over [t_mix,e,max + 2.5 ms, L_f) against AX47 (b)'s prediction
    w0 = int(math.ceil((mix_max + TAIL_FADE_HALF_S - shift) * fs))
    t0_em = (w0 + offset) / fs  # the window start as emission time (unit-decay index / fs)
    lf_em, l_em = lf_unit / fs, l_unit / fs
    steps = []
    for e in range(len(mixes)):
        c = 2 * e
        a, b = A[:, c].astype(np.float64), B[:, c].astype(np.float64)
        ea, eb = _ir_band_energies(a, fs, w0, lf_tap), _ir_band_energies(b, fs, w0, lf_tap)
        rb = _ir_band_energies(b, fs, lf_tap, len(b))
        row = {}
        for i, fc in enumerate(bands.OCTAVE_BANDS_HZ):
            k = ENERGY_DECAY_PER_T60 / t60[i]
            norm = 1.0 - math.exp(-k * l_em)
            f_b = (1.0 - math.exp(-k * timing["fadeStartS"])) / (1.0 - math.exp(-k * timing["exactS"]))
            p0_model = (1.0 - math.exp(-k * t0_em)) / norm
            w_model = (math.exp(-k * t0_em) - math.exp(-k * lf_em)) / norm
            p0_est = eb[i] * p0_model / w_model  # [0, t0) is masked by the early part: taken at the model's share
            rho = (p0_est + eb[i]) / (p0_est + eb[i] + rb[i])  # B's realised share of its decay over [0, L_f)
            # 1 + (1 - f_b) delta = f_b / rho; delta is printed only where the remainder is not negligible
            predicted = 10 * math.log10(f_b / rho)
            delta = (f_b / rho - 1.0) / (1.0 - f_b) if 1.0 - f_b >= 1e-6 else None
            measured = 10 * math.log10(ea[i] / eb[i])
            row[bands.band_key(fc)] = {"measured_db": measured, "predicted_db": predicted, "err_db": measured - predicted,
                                       "f_b": f_b, "delta": delta, "provisional_to_exact_step_db": -predicted}
            assert abs(measured - predicted) <= L4_STEP_TOL_DB, \
                f"L4-D 4: emitter {e} band {fc}: A/B {measured:+.4f} dB against AX47 (b)'s {predicted:+.4f} dB"
        steps.append({"emitter": e, "window_taps": [w0, lf_tap], "bands": row})
    rec["4_step"] = {"tol_db": L4_STEP_TOL_DB, "window_emission_s": [t0_em, lf_em], "rows": steps, "print": L4_PRINT_4,
                     "max_abs_predicted_db": max(abs(b["predicted_db"]) for r in steps for b in r["bands"].values()),
                     "max_abs_err_db": max(abs(b["err_db"]) for r in steps for b in r["bands"].values())}
    # 5. A is zero from L_p on
    nz = np.flatnonzero(np.any(A != 0.0, axis=1))
    a_last = int(nz[-1]) if nz.size else -1
    rec["5_A_zero_from_Lp"] = {"A_length": len(A), "last_nonzero_tap": a_last, "lp_tap": lp_tap}
    assert a_last < lp_tap and len(A) <= lp_tap, f"L4-D 5: A nonzero at tap {a_last} >= L_p tap {lp_tap}"
    # 6. B is L long
    nzb = np.flatnonzero(np.any(B != 0.0, axis=1))
    rec["6_B_length"] = {"B_length": len(B), "l_tap": l_tap, "B_length_s_emission": (len(B) + offset) / fs,
                         "L_s": timing["exactS"], "last_nonzero_tap": int(nzb[-1])}
    assert len(B) == l_tap and int(nzb[-1]) >= l_tap - int(0.01 * fs), f"L4-D 6: B is not L long: {rec['6_B_length']}"
    # 7. the decay from t_mix,e,max to L_f
    heard_b = B[:, 0].astype(np.float64) + B[:, 2].astype(np.float64)
    bb = engine_bands(heard_b, fs)
    mix_tap = int(round((mix_max - shift) * fs))
    decay = {}
    for i, fc in enumerate(bands.OCTAVE_BANDS_HZ):
        model = 60.0 * (timing["fadeStartS"] - mix_max) / t60[i]
        edc = np.cumsum((bb[i] ** 2)[::-1])[::-1]
        drop = 10 * math.log10(edc[mix_tap] / edc[lf_tap])
        decay[bands.band_key(fc)] = {"model_db": model, "realised_schroeder_drop_db": drop}
        assert model >= L4_DECAY_MIN_DB, f"L4-D 7: band {fc}: decay {model:.2f} dB < {L4_DECAY_MIN_DB} dB"
    rec["7_decay"] = {"min_db": L4_DECAY_MIN_DB, "asserted_on": "the model, 60 (L_f - t_mix,e,max)/T60_b (AX49)",
                      "print": L4_PRINT_7, "bands": decay}
    # 8. B's share past L_f, per emitter and band (and the heard IR); the cut depth is its log (label line 5)
    share = {}
    for name, h in (("emitter_0", B[:, 0]), ("emitter_1", B[:, 2]), ("heard", heard_b)):
        hb = engine_bands(np.asarray(h, dtype=np.float64), fs) if name != "heard" else bb
        share[name] = _band_dict(float(np.sum(x[lf_tap:] ** 2) / np.sum(x**2)) for x in hb)
        worst = max(share[name].values())
        assert worst <= L4_SHARE_MAX, f"L4-D 8: B's share past L_f {share[name]} > {L4_SHARE_MAX} ({name})"
    rec["8_share_past_Lf"] = {"max": L4_SHARE_MAX, **share}
    rec["cut_depth_db"] = {k: 10 * math.log10(v) for k, v in share["heard"].items()}
    # 13. the ghost print (print only): the re-onset level, re steady state, from B's backward-integrated curve at
    # release + L_p + {0, 1, 2, 5} s (Kuttruff Eq. 8.29: after an interrupted steady excitation the decay is the
    # backward-integrated IR)
    ghost = {}
    for i, fc in enumerate(bands.OCTAVE_BANDS_HZ):
        edc = np.cumsum((bb[i] ** 2)[::-1])[::-1]
        row = {}
        for dt in L4_GHOST_OFFSETS_S:
            tap = int(round((timing["endS"] + dt) * fs))
            row[f"+{dt:g}s"] = 10 * math.log10(edc[tap] / edc[0]) if tap < len(edc) and edc[tap] > 0 else None
        ghost[bands.band_key(fc)] = row
    rec["13_ghost"] = {"label": L4_GHOST_LABEL, "print_only": True,
                       "basis": "B's heard IR (emitters L + R), dB re the steady state, at release + L_p + dt",
                       "bands": ghost}
    return rec


def l4_anchor_feasibility(binary: pathlib.Path, scene_path: pathlib.Path, work: pathlib.Path,
                          diag: dict) -> tuple[dict, np.ndarray]:
    """The L4 anchor (decider file 41, L4-A = A-ii): B against B with the tail stepped +3 dB through render_cli
    --abx-step-db +3 (the only anchor step the kit requests; it never asks for a negative one). --abx-step-db changes
    only the diffuse part of E_target, so on the L4 scene (specular share 0.828) a -3 dB step cannot be built
    (render_cli refuses below 10 log10(0.828) = -0.82 dB); the share and that limit are recorded, as the reason for
    A-ii. Asserted on the +3 dB anchor IR (Seat 3's condition, file 40): M1's per-band step identity within 0.05 dB
    (`band_step_check`) and s_w <= 2.3 % (`ir_assertions`, printed and asserted); the anchor stimulus' peak (<= -3
    dBFS) is asserted where it is rendered. Returns the record and the stepped IR."""
    u, s, shares = ir_pair(binary, scene_path, +L4_ANCHOR_DB, work)
    worst = max(max(v) for v in shares.values())
    band_rows = ir_band_shares(u, s, diag, +L4_ANCHOR_DB, shares)
    ira = ir_assertions(u, s, diag, +L4_ANCHOR_DB)  # s_w <= S_W_MAX asserted per emitter and output
    s_w = max(r["ax47_window"]["window_unscaled_share"] for r in ira["rows"])
    assert s_w <= S_W_MAX, f"L4 anchor IR: s_w {s_w:.4%} > {S_W_MAX:.1%}"
    rec = {"step_db": +L4_ANCHOR_DB, "flags": f"--abx-step-db +{L4_ANCHOR_DB:g} --abx-step-sample 0",
           "decision": "decider file 41, L4-A = A-ii: B vs B + 3 dB tail, roles stepped_as_A / stepped_as_B 3/3",
           "target_specular_share": shares, "max_target_specular_share": worst,
           "largest_feasible_down_step_db": 10.0 * math.log10(worst),
           "down_step_refused_reason": ("--abx-step-db scales only the diffuse part of E_target; a -3 dB step needs a "
                                        f"specular share <= {10.0 ** (-L4_ANCHOR_DB / 10.0):.4f}"),
           "ir_assertions": ira, "bands": band_rows,
           "M1_band_step_check": band_step_check(band_rows, +L4_ANCHOR_DB),
           "s_w_max": s_w, "s_w_bound": S_W_MAX}
    return rec, s


L4_ANCHOR_ROLES = ("stepped_as_A", "stepped_as_B")  # decider file 41 (A-ii): 3 and 3 per block


L4_STIMULUS_SPECS = {"A": {"provisional": True}, "B": {}, "anchor_up": {"step_db": +L4_ANCHOR_DB}}  # no negative step


def l4_trial_plan(block: str) -> list[dict]:
    """One L4 block (L4-D; decider file 41, L4-A = A-ii): 16 scored trials (A provisional, B exact) and 6 anchor
    trials at seeded positions, each B against B with the tail stepped +3 dB: 3 with the stepped file as A
    (`role: stepped_as_A`) and 3 with it as B (`stepped_as_B`); 22 trials, a break after trial 11. Each block has its
    own seed (D1: its own trial order and anchor positions); X is drawn at sealing from the block's own key. The
    seeded positions are those of the earlier 3 up / 3 down plan (the role list is shuffled exactly as the sign list
    was, so the generator's draws are unchanged)."""
    rng = np.random.default_rng([L4_KEY_SEEDS[block], 49])
    roles = [L4_ANCHOR_ROLES[0]] * (L4_ANCHORS // 2) + [L4_ANCHOR_ROLES[1]] * (L4_ANCHORS - L4_ANCHORS // 2)
    rng.shuffle(roles)
    slots = sorted(rng.choice(L4_BLOCK_TRIALS, size=L4_ANCHORS, replace=False).tolist())
    plan, ai = [], 0
    for t in range(L4_BLOCK_TRIALS):
        if t in slots:
            role = roles[ai]
            ai += 1
            a, b = ("anchor_up", "B") if role == "stepped_as_A" else ("B", "anchor_up")
            plan.append({"trial": t + 1, "kind": "anchor", "g_db": +L4_ANCHOR_DB, "role": role, "A": a, "B": b,
                         "break_after": t + 1 == L4_BREAK_AFTER})
        else:
            plan.append({"trial": t + 1, "kind": "scored", "g_db": None, "A": "A", "B": "B",
                         "break_after": t + 1 == L4_BREAK_AFTER})
    assert ai == L4_ANCHORS and sum(t["kind"] == "scored" for t in plan) == L4_SCORED
    return plan


def _platform() -> str:
    return f"{sys.platform} {platform.machine()}"


def l4_ir_hashes(binary: pathlib.Path, scene_path: pathlib.Path, work: pathlib.Path) -> tuple[dict, pathlib.Path, pathlib.Path]:
    """P8 item 4: A's IR (render_cli --provisional-ir --ir) and B's IR (--ir) on the L4 scene, their SHA-256 and the
    platform (AX5: bit-identity holds on one platform only)."""
    a_ir, b_ir = work / "A_provisional_ir.wav", work / "B_exact_ir.wav"
    _run(binary, "--scene", scene_path, "--mode", "omni", "--provisional-ir", "--ir", a_ir)
    _run(binary, "--scene", scene_path, "--mode", "omni", "--ir", b_ir)
    return ({"A_provisional_ir_sha256": sha256_file(a_ir), "B_exact_ir_sha256": sha256_file(b_ir),
             "A_command": "render_cli --scene <L4 scene> --mode omni --provisional-ir --ir A.wav",
             "B_command": "render_cli --scene <L4 scene> --mode omni --ir B.wav", "platform": _platform(),
             "render_cli_sha256": sha256_file(binary)}, a_ir, b_ir)


def l4_verify(pack: pathlib.Path, binary: pathlib.Path, log=print) -> dict:
    """P8 item 4, before a session: rebuilds A's and B's IRs from the pack's scene on this platform and compares
    their SHA-256 with the manifest's. Any mismatch (or another platform) voids the sealed L4 stimuli."""
    manifest = json.loads((pack / "manifest.json").read_text())
    rec = manifest["ir_hashes"]
    scene_path = pack / manifest["scene"]["file_in_pack"]
    if sha256_file(scene_path) != manifest["scene"]["scene_sha256"]:
        raise RuntimeError(f"{scene_path}: SHA-256 differs from the manifest's")
    with tempfile.TemporaryDirectory() as tmp:
        now, _, _ = l4_ir_hashes(binary, scene_path, pathlib.Path(tmp))
    out = {"platform_sealed": rec["platform"], "platform_now": now["platform"],
           "A_match": now["A_provisional_ir_sha256"] == rec["A_provisional_ir_sha256"],
           "B_match": now["B_exact_ir_sha256"] == rec["B_exact_ir_sha256"]}
    out["platform_match"] = out["platform_sealed"] == out["platform_now"]
    out["void"] = not (out["A_match"] and out["B_match"] and out["platform_match"])
    out["verdict"] = ("VOID (P8 item 4): rebuild, rerun section 8's assertions 1-13, L4-P's tests 1-8 and Seat 9's label "
                      "check, then reseal" if out["void"] else "hashes match: the sealed L4 stimuli stand")
    log(json.dumps(out, indent=1))
    return out


def _l4_render(binary, scene_path, prog_path, out_path, provisional: bool = False, step_db: float | None = None,
               extra: tuple = ()) -> np.ndarray:
    args = ["--scene", scene_path, "--mode", "omni", "--in", prog_path, "--out", out_path, "--realtime-emulation",
            "--block", BLOCK, "--partition", PARTITION, *extra]
    if provisional:
        args.append("--provisional-ir")
    if step_db is not None:
        args += ["--abx-step-db", repr(float(step_db)), "--abx-step-sample", 0]
    _run(binary, *args)
    return wav.read_float32(out_path)[0]


def _link_or_copy(src: pathlib.Path, dst: pathlib.Path) -> None:
    import shutil

    dst.parent.mkdir(parents=True, exist_ok=True)
    if dst.exists():
        dst.unlink()
    try:
        os.link(src, dst)
    except OSError:
        shutil.copyfile(src, dst)


def k6_l4(stim_s: float, fam_files: int, trials_per_block: int = L4_BLOCK_TRIALS) -> dict:
    """K6 on the L4 stimuli (L4-T; decider file 21, D1 corrections): builder file 32's pace model (plays x stimulus
    length + overhead per trial, a 2 min break per block, familiarisation f plays of each labelled file), for the
    primary block alone and for the worst case primary + rerun. Audio floor: every file heard once, no overhead."""
    paces = {"brisk": (3, 5.0, 1), "typical": (5, 8.0, 2), "slow": (8, 10.0, 3)}
    out = {"stimulus_s": stim_s, "audio_floor_min_per_block": trials_per_block * 3 * stim_s / 60.0}
    for name, (plays, overhead, f) in paces.items():
        block = (trials_per_block * (plays * stim_s + overhead) + 120.0) / 60.0
        fam = f * fam_files * stim_s / 60.0
        out[name] = {"block_min": block, "familiarisation_min": fam, "primary_min": fam + block,
                     "primary_plus_rerun_min": fam + 2 * block}
    return out


def build_l4(out: pathlib.Path, binary: pathlib.Path, log=print, trials: int | None = None) -> dict:
    """The AX49 L4 pack (run sheet section 8): the scene (committed JSON, asserted equal to its builder), A and B
    rendered from the chord, the anchors, the IR- and stimulus-level assertions 1-13, the two blocks (primary and
    pre-built rerun) and the familiarisation pairs, the manifest (P8 items 3-4). `trials` limits each block (tests)."""
    import time

    t_start = time.monotonic()
    entry = L4_SCENE
    require_class_line(entry)  # D-M3e: before anything is rendered
    out.mkdir(parents=True, exist_ok=True)
    scene_path = write_scene(entry, out / scene_file_name(entry.name))
    work = out / "_work"
    work.mkdir(exist_ok=True)
    scene = json.loads(scene_path.read_text())
    # L4-S: provisional, L_p < L, T60_max 8.0 +/- 0.1 s; the AX49 constants as built (P8-3)
    tpath = work / "timing.json"
    stdout = _run(binary, "--scene", scene_path, "--mode", "omni", "--provisional-ir", "--provisional-timing", tpath)
    assert L4_FLAG_NOTE in stdout, stdout  # L4-D 1: render_cli prints it
    timing = json.loads(tpath.read_text())
    assert timing["validationOnly"] == L4_FLAG_NOTE and timing["provisional"] is True, timing
    assert timing["endS"] < timing["exactS"], f"L4-S: L_p {timing['endS']} >= L {timing['exactS']}"
    assert abs(timing["t60MaxS"] - L4_T60_MAX_S) <= L4_T60_MAX_TOL_S, f"L4-S: T60_max {timing['t60MaxS']} s"
    assert int(timing["sampleRate"]) == FS
    constants = {"f": (timing["fadeStartS"] - timing["mixMaxS"]) / timing["t60MaxS"],
                 "fade_s": timing["endS"] - timing["fadeStartS"],
                 "L_over_rule": timing["exactS"] / min(1.5 * timing["t60MaxS"], 12.0)}
    assert abs(constants["f"] - AX49_F) <= 1e-9 and abs(constants["fade_s"] - AX49_FADE_S) <= 1e-9 \
        and abs(constants["L_over_rule"] - 1.0) <= 1e-9, f"AX49 constants differ from the kit's (P8 item 3): {constants}"
    ax49 = {"f": AX49_F, "fade_s": AX49_FADE_S, "normalisation": AX49_NORMALISATION, "L_rule": AX49_L_RULE,
            "checked_against_provisional_timing": constants}
    log(f"l4: {L4_FLAG_NOTE}; k {L4_K}; t_mix,e,max {timing['mixMaxS']:.5f} s, T60_max {timing['t60MaxS']:.4f} s, "
        f"L_f {timing['fadeStartS']:.4f} s, L_p {timing['endS']:.4f} s, L {timing['exactS']:.4f} s; T60 per band "
        + " ".join(f"{v:.4f}" for v in timing["bandsT60S"]) + " s")
    # B's diagnostics (alignment, t_mix,e, direct times), then the IRs by the plain P8 commands
    dpath = work / "diag.json"
    _run(binary, "--scene", scene_path, "--mode", "omni", "--diagnostics", dpath)
    diag = json.loads(dpath.read_text())
    hashes, a_ir_path, b_ir_path = l4_ir_hashes(binary, scene_path, work)
    a_ir, b_ir = wav.read_float32(a_ir_path)[0], wav.read_float32(b_ir_path)[0]
    (work / "rebuild").mkdir(exist_ok=True)
    hashes2, _, _ = l4_ir_hashes(binary, scene_path, work / "rebuild")
    assert hashes2 == hashes, "L4-D 12: two IR builds differ"
    irc = l4_ir_checks(a_ir, b_ir, timing, diag)
    log(f"l4: IR checks: first differing tap {min(irc['2_ir']['first_differing_tap'])} >= earliest tail fade start "
        f"{irc['2_ir']['earliest_tail_fade_start_tap']}; prefix worst {irc['3_prefix']['worst_db']:.1f} dB "
        f"(<= {L4_PREFIX_DB:.2f}); step error max {irc['4_step']['max_abs_err_db']:.4f} dB (<= {L4_STEP_TOL_DB}); "
        f"A last nonzero tap {irc['5_A_zero_from_Lp']['last_nonzero_tap']} < L_p tap {irc['lp_tap']}; B length "
        f"{irc['6_B_length']['B_length']} = L tap {irc['l_tap']}; share past L_f (heard, max) "
        f"{max(irc['8_share_past_Lf']['heard'].values()):.5f} (<= {L4_SHARE_MAX})")
    log(f"l4: assertion 4 ({L4_PRINT_4}): max |predicted| {irc['4_step']['max_abs_predicted_db']:.4f} dB, max |measured - "
        f"predicted| {irc['4_step']['max_abs_err_db']:.4f} dB")
    log(f"l4: assertion 7 on the model (>= {L4_DECAY_MIN_DB} dB): "
        + ", ".join(f"{k}: {v['model_db']:.2f}" for k, v in irc["7_decay"]["bands"].items()) + " dB")
    log(f"l4: assertion 7, {L4_PRINT_7}: "
        + ", ".join(f"{k}: {v['realised_schroeder_drop_db']:.2f}" for k, v in irc["7_decay"]["bands"].items()) + " dB")
    # Scene facts for the label (L4-S): D/R at 1 kHz per emitter and heard (AX13), r/r_c (Kuttruff Eq. 5.44 with
    # Sabine A from the engine's 1 kHz T60), the surfaces' mean alpha at 1 kHz
    dims = scene["room"]["geometry"]["dimensions"]
    volume = dims[0] * dims[1] * dims[2]
    area = 2 * (dims[0] * dims[1] + dims[0] * dims[2] + dims[1] * dims[2])
    face_area = {"floor": dims[0] * dims[1], "ceiling": dims[0] * dims[1], "xMin": dims[1] * dims[2],
                 "xMax": dims[1] * dims[2], "yMin": dims[0] * dims[2], "yMax": dims[0] * dims[2]}
    abar = sum(face_area[f] * s["absorption"][4] for f, s in scene["room"]["surfaces"].items()) / area
    assert 0.04 <= abar <= 0.07, f"L4-S label: mean alpha {abar} outside the expected 0.04-0.07"
    t60_1k = float(timing["bandsT60S"][4])
    sabine_a = 0.161 * volume / t60_1k
    rc = math.sqrt(sabine_a / (16.0 * math.pi))
    lst = np.asarray(scene["listener"]["position"])
    r = [float(np.linalg.norm(np.asarray(em["position"]) - lst)) for em in scene["emitters"]]
    drr = [metrics.room_metrics(b_ir[:, 2 * e].astype(np.float64), FS)["bands"]["1000"].get("DRR") for e in range(2)]
    heard_b = b_ir[:, 0].astype(np.float64) + b_ir[:, 2].astype(np.float64)
    drr_heard = metrics.room_metrics(heard_b, FS)["bands"]["1000"].get("DRR")
    if drr_heard is None or any(x is None for x in drr):
        raise RuntimeError(f"L4-S label: D/R at 1 kHz not measured ({drr}, heard {drr_heard})")
    t60s = [float(v) for v in timing["bandsT60S"]]
    i_max = int(np.argmax(t60s))
    band_max = bands.band_key(bands.OCTAVE_BANDS_HZ[i_max])
    # the chord's band energy (dry, engine bands) beside the cut depth (label line 5)
    hold = max(int(math.ceil(timing["endS"] * FS)), int(math.ceil(0.5 * timing["t60MaxS"] * FS)))
    n_rel = int(round(L4_CHORD_RELEASE_S * FS))
    silence = int(math.ceil((timing["exactS"] + L4_SILENCE_MARGIN_S) * FS))
    total = -(-(L4_LEAD_SAMPLES + hold + n_rel + silence) // PARTITION) * PARTITION
    x, chord = l4_chord(hold, total)
    cb = [float(np.sum(b**2)) for b in engine_bands(x, FS)]
    chord["band_energy_db_re_total"] = _band_dict(10 * math.log10(v / sum(cb)) for v in cb)
    chord["band_energy_dbfs_samples"] = _band_dict(10 * math.log10(v) for v in cb)
    chord["hold_rule"] = "H = max(L_p, 0.5 T60_max)"
    chord["hold_s"] = hold / FS
    values = {"dims": " × ".join(f"{d:g}" for d in dims), "listener": tuple(scene["listener"]["position"]),
              "emitters": " and ".join(str(tuple(e["position"])) for e in scene["emitters"]), "k": L4_K,
              "seed": scene["render"]["tailSeed"], "fs_khz": FS / 1000, "r": " / ".join(f"{x:.2f}" for x in r),
              "t60s": " ".join(f"{bands.band_key(fc)}: {v:.3f}" for fc, v in zip(bands.OCTAVE_BANDS_HZ, t60s)),
              "t60max": timing["t60MaxS"], "t60max_band": band_max,
              "drr_1k": " / ".join(f"{v:+.1f}" for v in drr) + f" (heard L + R {drr_heard:+.1f})",
              "drr_diffuse": 20 * math.log10(rc / r[0]), "r_over_rc": r[0] / rc, "sabine_a": sabine_a, "abar": abar,
              "mix": timing["mixMaxS"], "lf": timing["fadeStartS"], "lp": timing["endS"], "L": timing["exactS"],
              "cuts": ", ".join(f"{k}: {v:.1f}" for k, v in irc["cut_depth_db"].items()),
              "chord_bands": ", ".join(f"{k}: {v:.1f}" for k, v in chord["band_energy_db_re_total"].items()),
              "dr_class": dr_class(drr_heard), "drr_heard": drr_heard, "cut": irc["cut_depth_db"][band_max]}
    label_detail = fill_l4_label(entry, values)
    class_line = next(x for x in label_detail if x.startswith("Class: "))
    sc = {"name": entry.name, "label": entry.label, "label_detail": label_detail, "class": class_line,
          "seat9_label_check": "Seat 9 confirms the label before the seal (L4-S)",
          "scene_file": entry.committed.relative_to(REPO).as_posix(), "file_in_pack": scene_path.name,
          "scene_sha256": sha256_file(scene_path), "k": L4_K, "tailSeed": scene["render"]["tailSeed"],
          "timing": timing, "T60_max_band": band_max, "volume_m3": volume, "surface_m2": area,
          "mean_alpha_1k": abar, "sabine_A_1k_m2": sabine_a, "A_over_S_1k": sabine_a / area, "r_c_m": rc, "r_m": r,
          "r_over_rc": [x / rc for x in r], "DRR_1k_db": drr, "DRR_1k_heard_db": drr_heard,
          "DRR_diffuse_db": [20 * math.log10(rc / x) for x in r], "cut_depth_db": irc["cut_depth_db"],
          "cut_depth_T60max_band_db": irc["cut_depth_db"][band_max]}
    for line in label_detail:
        log(f"l4 label: {line}")

    # The anchor (decider file 41, L4-A = A-ii): +3 dB only; M1's step identity and s_w asserted on its IR
    anchor_rec, _ = l4_anchor_feasibility(binary, scene_path, work, diag)
    log(f"l4: anchor IR (+{L4_ANCHOR_DB:g} dB tail): M1 per-band step error max "
        f"{anchor_rec['M1_band_step_check']['max_abs_err_db']:.2e} dB (<= {BAND_STEP_TOL_DB}); s_w "
        f"{anchor_rec['s_w_max']:.3e} (<= {S_W_MAX:.3f}); E_target specular share max "
        f"{anchor_rec['max_target_specular_share']:.4f} (a -3 dB step would need <= 0.5012; deepest "
        f"{anchor_rec['largest_feasible_down_step_db']:.2f} dB)")
    # Stimuli (L4-D): A provisional, B exact, the anchor B with the tail +3 dB from sample 0; each rendered twice
    # (L4-D 12), then cut to the input's length after asserting that nothing follows it (the whole exact decay fits)
    prog = work / "chord_dry.wav"
    wav.write_float32(prog, signals.to_stereo(x), FS)
    stim_dir = out / "stimuli"
    stim_dir.mkdir(exist_ok=True)
    specs = L4_STIMULUS_SPECS
    stims: dict[str, np.ndarray] = {}
    stim_rec: dict = {}
    for name, kw in specs.items():
        y1 = _l4_render(binary, scene_path, prog, work / f"{name}_1.wav", **kw)
        y2 = _l4_render(binary, scene_path, prog, work / f"{name}_2.wav", **kw)
        identical = sha256_file(work / f"{name}_1.wav") == sha256_file(work / f"{name}_2.wav")
        assert identical, f"L4-D 12: two builds of {name} differ"
        assert np.all(y1[total:] == 0.0), f"L4-D: {name} continues past the input (the exact decay does not fit)"
        y = np.ascontiguousarray(y1[:total])
        assert np.array_equal(y[:, 0].view(np.uint32), y[:, 1].view(np.uint32)), f"{name}: not diotic"
        wav.write_float32(stim_dir / f"{name}.wav", y, FS)
        stims[name] = y
        peak = 20 * math.log10(max(float(np.max(np.abs(y))), 1e-30))
        assert peak <= L4_MAX_PEAK_DBFS, f"L4-D 11: {name} peaks at {peak:.2f} dBFS > {L4_MAX_PEAK_DBFS}"
        stim_rec[name] = {"file": f"stimuli/{name}.wav", "sha256": sha256_file(stim_dir / f"{name}.wav"),
                          "samples": total, "duration_s": total / FS, "peak_dbfs": peak, "two_builds_identical": identical,
                          "render": ("render_cli --mode omni --in chord --out --realtime-emulation --block 512 "
                                     "--partition 512" + (" --provisional-ir" if kw.get("provisional") else "")
                                     + (f" --abx-step-db {kw['step_db']:+g} --abx-step-sample 0" if "step_db" in kw else "")),
                          "provisional": bool(kw.get("provisional")), "ax49_constants": ax49}
    A, B = stims["A"], stims["B"]
    assert A.shape == B.shape  # L4-D: A and B are the same length
    anchor_peak = stim_rec["anchor_up"]["peak_dbfs"]
    assert anchor_peak <= L4_MAX_PEAK_DBFS, anchor_peak  # the +3 dB anchor's peak (decider file 41), as in 11
    anchor_rec["peak_dbfs"] = anchor_peak
    # 2. on the renders (decider file 41 (4); interrogator file 42): bit-identical before the partition boundary at
    # or below the chord-aligned earliest tail fade start (the partitioned convolver mixes whole partitions), and over
    # [that boundary, fade start) max |A - B| <= -120 dB re B's peak, per sample
    s_on = L4_LEAD_SAMPLES
    k0 = s_on + irc["2_ir"]["earliest_tail_fade_start_tap"]
    k0_block = (k0 // PARTITION) * PARTITION
    d = np.flatnonzero(np.any(A.view(np.uint32) != B.view(np.uint32), axis=1))
    first_render = int(d[0]) if d.size else len(A)
    assert first_render >= k0_block, f"L4-D 2: the renders differ at {first_render} < {k0_block}"
    b_peak = float(np.max(np.abs(B.astype(np.float64))))
    gap = np.abs(A[k0_block:k0].astype(np.float64) - B[k0_block:k0].astype(np.float64))
    gap_max = float(np.max(gap)) if gap.size else 0.0
    gap_db = 20 * math.log10(gap_max / b_peak) if gap_max > 0 else -math.inf
    assert gap_db <= L4_RENDER_NULL_DB, \
        f"L4-D 2: max |A - B| over [{k0_block}, {k0}) is {gap_db:.1f} dB re B's peak > {L4_RENDER_NULL_DB} dB"
    # 5. A is zero from L_p after the release (stimulus)
    rel_end = chord["release_end_sample"]
    nz = np.flatnonzero(A[:, 0] != 0.0)
    a_last = int(nz[-1])
    assert a_last < rel_end + len(a_ir) + PARTITION, (a_last, rel_end, len(a_ir))
    # 9. print: the A/B level difference over the held part, per band
    held = slice(s_on + int(round(L4_CHORD_ONSET_S * FS)), chord["release_start_sample"])
    ab = engine_bands(A[:, 0].astype(np.float64), FS)
    bbb = engine_bands(B[:, 0].astype(np.float64), FS)
    held_db = _band_dict(10 * math.log10(np.sum(a[held] ** 2) / np.sum(b[held] ** 2)) for a, b in zip(ab, bbb))
    # 10. the silence after the release
    sil = (total - rel_end) / FS
    assert sil >= timing["exactS"] + L4_SILENCE_MARGIN_S - 1.0 / FS and sil >= timing["exactS"], f"L4-D 10: {sil} s"
    stim_checks = {"1_flag": {"recorded": True, "note": L4_FLAG_NOTE},
                   "2_render": {"first_differing_sample": first_render, "chord_onset_sample": s_on,
                                "earliest_tail_fade_start_sample": k0, "bit_identical_before": k0_block,
                                "null_window": [k0_block, k0], "null_max_abs_diff_db_re_B_peak": gap_db,
                                "null_bound_db": L4_RENDER_NULL_DB, "null_criterion": L4_PRINT_2},
                   "5_render": {"A_last_nonzero_sample": a_last, "release_end_sample": rel_end,
                                "A_last_minus_release_end_s": (a_last - rel_end) / FS, "L_p_s": timing["endS"]},
                   "9_held_A_over_B_db": held_db, "9_print_only": True,
                   "10_silence_after_release_s": sil,
                   "11_peak_dbfs_max": max(v["peak_dbfs"] for v in stim_rec.values()),
                   "12_two_builds_identical": all(v["two_builds_identical"] for v in stim_rec.values()) and hashes2 == hashes}
    log(f"l4: assertion 2 on the renders: bit-identical before {k0_block} (asserted); over [{k0_block}, {k0}) max |A - B| "
        f"{gap_db:.1f} dB re B's peak (<= {L4_RENDER_NULL_DB:g}; {L4_PRINT_2}); first differing sample {first_render}")
    log(f"l4: stimuli {total / FS:.3f} s; renders identical before sample {first_render} (asserted from {k0_block}); A "
        f"last nonzero {(a_last - rel_end) / FS:.4f} s after the release end; held-part A/B (dB) "
        + ", ".join(f"{k}: {v:+.4f}" for k, v in held_db.items())
        + f"; silence after the release {sil:.3f} s; peak max {stim_checks['11_peak_dbfs_max']:.2f} dBFS")
    log("l4: ghost print (" + L4_GHOST_LABEL + ", dB re steady state at release + L_p + dt): "
        + "; ".join(f"{k}: " + " ".join(f"{dt} {v:.1f}" if v is not None else f"{dt} -" for dt, v in row.items())
                    for k, row in irc["13_ghost"]["bands"].items()))
    # Blocks (D1): primary and the pre-built rerun, both built (and later sealed) together
    blocks = {}
    for block in L4_BLOCKS:
        plan = l4_trial_plan(block)[: trials or L4_BLOCK_TRIALS]
        for t in plan:
            tdir = out / block / f"trial_{t['trial']:02d}"
            _link_or_copy(stim_dir / f"{t['A']}.wav", tdir / "A.wav")
            _link_or_copy(stim_dir / f"{t['B']}.wav", tdir / "B.wav")
        blocks[block] = plan
    fam_dir = out / "familiarisation"
    # familiarisation (decider file 41): the labelled A/B pair and the labelled anchor pair
    fam = [("pair_01_A_provisional.wav", "A"), ("pair_01_B_exact.wav", "B"),
           ("pair_02_anchor_tail_+3dB.wav", "anchor_up"), ("pair_02_B_exact.wav", "B")]
    for fname, src in fam:
        _link_or_copy(stim_dir / f"{src}.wav", fam_dir / fname)
    stim_s = total / FS
    k6 = k6_l4(stim_s, len(fam))
    for p in sorted(work.rglob("*"), reverse=True):
        p.unlink() if p.is_file() else p.rmdir()
    work.rmdir()
    manifest = {
        "chain": "l4", "provisional": True, "flag_note": L4_FLAG_NOTE,
        "preregistration": ("run sheet section 8; phase-07c-2b decider files 10 Part A (L4-S, L4-D, L4-T), 17 (D1, P1, "
                            "P8), 21 (P8-3, P8-S), 41 (L4-A, assertions 7, 4, 2); interrogator files 13, 18, 22, 42; "
                            "Seat 5 file 14; builder file 15"),
        "family": ("L4 is its own family (AX49), not in the AX47 union (<= 0.098): detection at >= 12/16, family alpha "
                   f"{L4_FAMILY_ALPHA} (2517/65536)"),
        "criterion": f">= {L4_CRITERION}/{L4_SCORED}",
        "anchor": (f"B vs B with the tail stepped +{L4_ANCHOR_DB:g} dB (--abx-step-db +{L4_ANCHOR_DB:g} --abx-step-sample 0), "
                   f"roles stepped_as_A / stepped_as_B 3/3, pass >= {L4_ANCHOR_PASS}/{L4_ANCHORS}, chance "
                   f"{L4_ANCHOR_CHANCE:.3f} (7/64) (decider file 41, L4-A = A-ii)"),
        "fs": FS, "partition": PARTITION, "block": BLOCK, "render_cli": str(binary), "scene": sc,
        "ax49_constants": ax49, "anchor_feasibility": anchor_rec, "ir_hashes": hashes, "chord": chord, "ir_checks": irc, "stimulus_checks": stim_checks,
        "stimuli": stim_rec, "blocks": blocks, "familiarisation": [{"file": f"familiarisation/{f}", "stimulus": s} for f, s in fam],
        "k6": k6, "build_seconds": time.monotonic() - t_start}
    (out / "manifest.json").write_text(json.dumps(manifest, indent=1, default=float))
    log(f"l4: K6 (typical pace) primary {k6['typical']['primary_min']:.1f} min, primary + rerun "
        f"{k6['typical']['primary_plus_rerun_min']:.1f} min; built in {manifest['build_seconds']:.0f} s")
    return manifest


def l4_handover_demo(out_dir: pathlib.Path, binary: pathlib.Path, log=print) -> dict:
    """L4-D 14 (Seat 6; Seat 5 file 14 (vi)): one UNSCORED render, never sealed or scored: the L4 chord released at
    t_r, the provisional IR until the first partition boundary at or after t_r + L_p + 1 s, then the shipped AQ4 30 ms
    equal-gain crossfade to the exact IR (render_cli --provisional-ir --provisional-handover-sample N, with an
    explicit --block). "unscored" is in its file name and in the pack index."""
    out_dir.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory() as tmp:
        tmp = pathlib.Path(tmp)
        scene_path = write_scene(L4_SCENE, tmp / scene_file_name(L4_SCENE.name))
        tpath = tmp / "timing.json"
        _run(binary, "--scene", scene_path, "--mode", "omni", "--provisional-ir", "--provisional-timing", tpath)
        timing = json.loads(tpath.read_text())
        hold = max(int(math.ceil(timing["endS"] * FS)), int(math.ceil(0.5 * timing["t60MaxS"] * FS)))
        n_rel = int(round(L4_CHORD_RELEASE_S * FS))
        silence = int(math.ceil((timing["exactS"] + L4_SILENCE_MARGIN_S) * FS))
        total = -(-(L4_LEAD_SAMPLES + hold + n_rel + silence) // PARTITION) * PARTITION
        x, chord = l4_chord(hold, total)
        t_r = chord["release_start_sample"]
        target = t_r + int(math.ceil((timing["endS"] + L4_DEMO_DELAY_S) * FS))
        n = -(-target // PARTITION) * PARTITION
        prog = tmp / "chord.wav"
        wav.write_float32(prog, signals.to_stereo(x), FS)
        name = "L4_handover_demo_unscored.wav"
        _l4_render(binary, scene_path, prog, out_dir / name, provisional=True,
                   extra=("--provisional-handover-sample", n))
    y, _ = wav.read_float32(out_dir / name)
    rec = {"file": name, "title": "L4 handover demo (unscored; interim then handover, as at project load)",
           "unscored": True, "release_sample": t_r, "handover_sample": n,
           "handover_after_release_s": (n - t_r) / FS, "L_p_s": timing["endS"], "block": BLOCK, "partition": PARTITION,
           "peak_dbfs": 20 * math.log10(max(float(np.max(np.abs(y))), 1e-30)), "duration_s": len(y) / FS,
           "flag_note": L4_FLAG_NOTE}
    log(f"l4 demo: release {t_r / FS:.3f} s, handover at {n / FS:.3f} s (t_r + {(n - t_r) / FS:.3f} s; L_p "
        f"{timing['endS']:.4f} s), peak {rec['peak_dbfs']:.1f} dBFS")
    return rec


# ---------------------------------------------------------------------------------------------------------
# Blinding and scoring (items 4, 11, 13)
# ---------------------------------------------------------------------------------------------------------


def prereg_path(key_path: pathlib.Path) -> pathlib.Path:
    """Where seal writes the record to commit before the run: beside the key, never in the session folder."""
    return key_path.with_name(key_path.stem + "-prereg.json")


def trial_rel(chain: str, block: str, trial: int) -> str:
    """A trial's folder inside a pack and a session: `<level>dB/trial_NN` (AX47 chains), `<block>/trial_NN` (L4)."""
    return f"{block}/trial_{trial:02d}" if chain == "l4" else f"{block}dB/trial_{trial:02d}"


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
    chain = manifest["chain"]
    seed = int(key_seed if key_seed is not None else secrets.randbits(63))
    rng = np.random.default_rng(seed)
    key: dict = {"chain": chain, "seed": seed, "blocks": {}}
    record: dict = {"chain": chain, "stimuli_salted_sha256": {}}
    if chain == "l4":
        # D1: every block has its own seeded key (and its own trial order and anchor positions, from the plan); both
        # are sealed here together, before the session. The non-detection wording carries the measured cut (P1).
        key["block_seeds"] = {b: int(secrets.randbits(63)) if key_seed is None else int(key_seed) + 1 + i
                              for i, b in enumerate(manifest["blocks"])}
        key["l4"] = {"cut_depth_T60max_band_db": manifest["scene"]["cut_depth_T60max_band_db"],
                     "T60_max_band": manifest["scene"]["T60_max_band"], "scene_sha256": manifest["scene"]["scene_sha256"],
                     "ir_hashes": manifest["ir_hashes"]}
    for level, block in manifest["blocks"].items():
        key["blocks"][level] = []
        if chain == "l4":
            rng = np.random.default_rng(key["block_seeds"][level])
        for t in block:
            rel = trial_rel(chain, level, t["trial"])
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
            if chain == "l4":
                key["blocks"][level][-1].update({"A": t["A"], "B": t["B"]})
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
            rel = trial_rel(key["chain"], level, t["trial"])
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


def l4_wording(cut_db: float) -> dict[str, str]:
    """P1 (decider file 17; run sheet section 8, Seats 9 and 6). The cut is label line 5 in the T60_max band, its
    magnitude rounded down to 0.1 dB so that "a cut >= X dB" holds."""
    depth = math.floor(-cut_db * 10.0) / 10.0
    return {"detected": f"detected (≥ {L4_CRITERION}/{L4_SCORED}, family α {L4_FAMILY_ALPHA})",
            "not detected": (f"not detected in {L4_SCORED} trials by one listener (power {L4_POWER_AT_075} at p = 0.75); "
                             f"covers a cut ≥ {depth:.1f} dB below the full-IR energy in the T60_max band at T60_max 8 s"),
            "inconclusive": "inconclusive (anchor failed twice)",
            "family": "L4 is its own family (AX49), not in the AX47 union (≤ 0.098)"}


def l4_score_anchor(key_block: list[dict], answers: dict[int, str], block: str) -> dict:
    """D1: a block's anchor trials are scored first (pass >= 5/6)."""
    anchors = [t for t in key_block if t["kind"] == "anchor"]
    missing = [t["trial"] for t in anchors if t["trial"] not in answers]
    if missing:
        raise ValueError(f"L4 {block}: no answer for anchor trials {missing}")
    ka = sum(answers[t["trial"]] == t["X"] for t in anchors)
    return {"block": block, "anchor_k": ka, "anchor_n": len(anchors), "passed": ka >= L4_ANCHOR_PASS}


def l4_unseal_scored(key_block: list[dict], answers: dict[int, str], anchor: dict) -> dict:
    """The scored trials of one block, unsealed only after its anchor passed (D1: refuses otherwise)."""
    if not anchor["passed"]:
        raise PermissionError(f"refusing to unseal the L4 {anchor['block']} block's scored trials: its anchor failed "
                              f"({anchor['anchor_k']}/{anchor['anchor_n']} < {L4_ANCHOR_PASS}/{L4_ANCHORS}); the block is "
                              "void (D1)")
    scored = [t for t in key_block if t["kind"] == "scored"]
    missing = [t["trial"] for t in scored if t["trial"] not in answers]
    if missing:
        raise ValueError(f"L4 {anchor['block']}: no answer for trials {missing}")
    k = sum(answers[t["trial"]] == t["X"] for t in scored)
    return {"k": k, "n": len(scored), "p_exact": binom_tail(k, len(scored))}


def score_l4(key_path: pathlib.Path, responses: dict[str, dict[int, str]]) -> list[dict]:
    """D1 and P1: the primary block's anchor first; if it passed, its scored trials are unsealed and the record is
    "detected" or "not detected" (and the rerun block is refused: a non-detection is never a reason to rerun); if it
    failed, the block is void, its scored trials stay sealed, and the pre-sealed rerun block is scored the same way;
    a second failed anchor reads "inconclusive (anchor failed twice)". A voided result is never "not detected"."""
    key = json.loads(key_path.read_text())
    if key["chain"] != "l4":
        raise ValueError(f"the key is for the {key['chain']} chain, not L4")
    words = l4_wording(key["l4"]["cut_depth_T60max_band_db"])
    results = []
    for i, block in enumerate(L4_BLOCKS):
        if i > 0:
            if results[-1]["verdict"] != "void":
                if block in responses:
                    raise PermissionError(f"refusing the L4 {block} block: the {L4_BLOCKS[i - 1]} block's anchor passed "
                                          "(a non-detection is never a reason to rerun; D1)")
                break
            if block not in responses:
                break  # the rerun is owed (D1); nothing more to score yet
        answers = responses.get(block, {})
        anchor = l4_score_anchor(key["blocks"][block], answers, block)
        rec = {"chain": "l4", "family": words["family"], **anchor, "k": None, "n": L4_SCORED}
        if not anchor["passed"]:
            if i == 0:
                rec["verdict"] = "void"
                rec["wording"] = (f"void: anchor {anchor['anchor_k']}/{anchor['anchor_n']} < {L4_ANCHOR_PASS}/{L4_ANCHORS}; "
                                  "its scored trials are not unsealed or scored; one rerun follows on the pre-sealed "
                                  "rerun block (D1)")
            else:
                rec["verdict"], rec["wording"] = "inconclusive", words["inconclusive"]
        else:
            rec.update(l4_unseal_scored(key["blocks"][block], answers, anchor))
            rec["verdict"] = "detected" if rec["k"] >= L4_CRITERION else "not detected"
            rec["wording"] = words[rec["verdict"]]
        results.append(rec)
    return results


def read_l4_responses(path: pathlib.Path) -> dict[str, dict[int, str]]:
    """CSV with columns block (primary or rerun), trial, answer (A or B): the run sheet's L4 response table."""
    out: dict[str, dict[int, str]] = {}
    with open(path, newline="") as f:
        for row in csv.DictReader(f):
            ans = row["answer"].strip().upper()
            if ans not in ("A", "B"):
                continue
            block = row["block"].strip()
            if block not in L4_BLOCKS:
                raise ValueError(f"unknown L4 block {block!r}")
            out.setdefault(block, {})[int(row["trial"])] = ans
    return out


def blank_response_csv(path: pathlib.Path, chain: str) -> None:
    if chain == "l4":
        with open(path, "w", newline="") as f:
            w = csv.writer(f)
            w.writerow(["block", "trial", "answer"])
            for block in L4_BLOCKS:
                for t in l4_trial_plan(block):
                    w.writerow([block, t["trial"], ""])
        return
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
        p.add_argument("--scene-name", choices=tuple(SCENES), default=DEFAULT_SCENE,
                       help="the registered ABX scene (decider file 8, M3-S: E, fallbacks in order "
                            + ", ".join(FALLBACK_ORDER[1:]) + ")")
        if name == "speech":
            p.add_argument("--speaker", default=None, help="adult TSP speaker, fixed in the pre-registration (item 8); "
                                                           "MA for --search-pairs")
            p.add_argument("--files", nargs=2, default=None, metavar=("SENTENCE1", "SENTENCE2"),
                           help="the TSP file pair (the pair search's result, fixed in the pre-registration; "
                                "SPEECH_PAIR); not with --search-pairs")
            p.add_argument("--search-pairs", action="store_true",
                           help="the pre-registered pair search (decider file 34): adult pairs in TSP index order from "
                                "MA01_03 + MA01_04 on the scene in use, one row per pair tried, stopping at the first "
                                "that passes every pre-seal assertion; writes <out>/speech-search/")
            p.add_argument("--cache", type=pathlib.Path, default=pathlib.Path.home() / ".cache" / "makroof" / "tsp")
    p = sub.add_parser("l4", help="AX49 L4 (run sheet section 8): the provisional-against-exact held-chord pack")
    p.add_argument("--out", type=pathlib.Path, default=REPO / "build" / "abx-07c-2b" / "l4")
    p.add_argument("--render-cli", type=pathlib.Path, default=None)
    p.add_argument("--trials", type=int, default=None, help="limit each block (smoke runs only)")
    p = sub.add_parser("l4-verify", help="P8 item 4: rebuild A's and B's IRs and compare their SHA-256 before a session")
    p.add_argument("--pack", type=pathlib.Path, required=True)
    p.add_argument("--render-cli", type=pathlib.Path, default=None)
    p = sub.add_parser("seal")
    p.add_argument("--pack", type=pathlib.Path, required=True)
    p.add_argument("--session", type=pathlib.Path, required=True)
    p.add_argument("--key", type=pathlib.Path, required=True)
    p = sub.add_parser("score")
    p.add_argument("--key", type=pathlib.Path, required=True)
    p.add_argument("--responses", type=pathlib.Path, required=True)
    p.add_argument("--chain", choices=("noise", "speech", "l4"), required=True)
    p.add_argument("--session", type=pathlib.Path, required=True, help="the listener's folder; X.wav is checked")
    p = sub.add_parser("blank")
    p.add_argument("--chain", choices=("noise", "speech", "l4"), required=True)
    p.add_argument("--out", type=pathlib.Path, required=True)
    args = ap.parse_args(argv)

    if args.cmd in ("noise", "speech", "l4", "l4-verify"):
        binary = args.render_cli or render_cli.find_render_cli()
        if binary is None or not binary.is_file():
            print("abx_kit.py: render_cli not found (cmake --preset cli && cmake --build --preset cli)", file=sys.stderr)
            return 1
        if args.cmd == "l4":
            build_l4(args.out, binary, trials=args.trials)
            print(f"written to {args.out}")
            return 0
        if args.cmd == "l4-verify":
            return 1 if l4_verify(args.pack, binary)["void"] else 0
        if args.cmd == "noise":
            build_noise_chain(args.out / "noise", binary, trials=args.trials, scene_name=args.scene_name)
        elif args.search_pairs:
            if args.files is not None:
                ap.error("--files is not used with --search-pairs")
            search_speech_pairs(args.out / "speech-search", binary, args.cache, args.speaker or "MA", trials=args.trials,
                                scene_name=args.scene_name)
            print(f"written to {args.out / 'speech-search'}")
            return 0
        else:
            if args.speaker is None or args.files is None:
                ap.error("speech needs --speaker and --files (or --search-pairs)")
            build_speech_chain(args.out / "speech", binary, args.speaker, tuple(args.files), args.cache, trials=args.trials,
                               scene_name=args.scene_name)
        print(f"written to {args.out / args.cmd}")
    elif args.cmd == "seal":
        record = seal(args.pack, args.session, args.key)
        print(json.dumps({"key_sha256": record["key_sha256"], "stimuli": len(record["stimuli_salted_sha256"])}, indent=1))
        print(f"commit {prereg_path(args.key)} before the run; keep {args.key} unseen until scoring")
    elif args.cmd == "score":
        verify_session(args.key, args.session)
        if args.chain == "l4":
            for r in score_l4(args.key, read_l4_responses(args.responses)):
                print(json.dumps(r, ensure_ascii=False))
            return 0
        for r in score(args.key, read_responses(args.responses), args.chain):
            print(json.dumps(r))
    elif args.cmd == "blank":
        blank_response_csv(args.out, args.chain)
    return 0


if __name__ == "__main__":
    sys.exit(main())
