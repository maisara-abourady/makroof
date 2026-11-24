#!/usr/bin/env python3
"""Phase-07c-2b M3-L4: the AX49 L4 listening-test stimulus kit (design L4-A, scene S', Seat 1's chord).

The design is decider file 6 (docs/review/phase-07c-2b/6-decider-m3-r2.md), "M3-7 / M3-L4", DECISION items 1-8:
- L4-A (item 1): A = the chord through the AX49 provisional IR (faded over [L_f, L_p), zero from L_p), B = the same
  chord through the exact IR; one tailSeed shared by A and B (the AX47 kit's TAIL_SEED).
- Scene S' (item 2; Seat 2, file 4-seat2): 100 x 100 x 100 m, scattering 0.3 on every face, listener (50, 30, 1.7),
  emitters (45, 70, 2) and (55, 70, 2), alpha per band pinned (ABSORPTION) so that the engine prints T60 8.0 +- 0.1 s
  from 63 Hz to 1 kHz (above 1 kHz the 1 kHz alpha). Scene data only; nothing in src/sim (NFR-8).
- Chord (item 3; Seat 1, file 4-seat1, verbatim): C2 G2 C3 E3 G3, 1/k harmonic series to 5 kHz, seeded phases
  (L4_CHORD_SEED, version L4_CHORD_VERSION); 0.5 s silence, 20 ms raised-cosine attack, 4 s hold, 10 ms raised-cosine
  release, >= L of free decay. Level: the exact render's steady state equals the AX47 noise reference within +-1 dB.
- Checks (item 4): Seat 3's P1-P6, S1-S7 (file 4-seat3, with file 8-seat3's partition-grid precisions, which
  override), Seat 2's seal asserts, Seat 1's band coverage and prefix check.
- Pass rule (item 5): >= 12/16 (alpha 2517/65536), 6 interleaved exact-vs-exact anchors at tail -3 dB, pass >= 5/6,
  else void with one rerun; the two result wordings verbatim.
- Path (item 6, F3; file 8-seat3): every arm through render_cli --mode omni --realtime-emulation --block 512
  --partition 512; A with --ax49-provisional, B without, the anchor with --abx-step-db -3 --abx-step-sample 0 (the
  stepped IR alone from sample 0, the AX47 kit's anchor method).

    python tools/ci/ax49_l4.py build --out build/abx-07c-2b          # writes build/abx-07c-2b/l4 (manifest.json)
    python tools/ci/ax49_l4.py seal  --pack build/abx-07c-2b/l4 --session <dir> --key <file outside it>
    python tools/ci/ax49_l4.py score --key <file> --responses <csv> [--session <dir>] [--rerun]
    python tools/ci/ax49_l4.py blank --out <csv>

Output time. render_cli removes the real-time engine's P-sample latency (Cli.cpp renderRealtime), so output sample n
lines up with input sample n through the aligned IR (tap 0 = alignmentShiftS after emission). Seat 3's partition-grid
bounds (file 8-seat3) are stated in the engine's raw output time, which carries the +1 partition of latency; in the
written file each bound is therefore one partition earlier: S2 identity before (floor(n_on/P) + floor(n_d/P)) P,
S4 exact zero from (ceil(n_end/P) + K_p) P.

Stimulus files. render_cli writes input length + IR length - 1 samples, so the three arms differ in length; every
stimulus is the render trimmed to the input length (>= L of free decay and >= the longest IR + two partitions after
the release), and the part trimmed off is asserted exactly 0.0. Every check runs on the untrimmed render. The kit's
WAVs are written byte-deterministically (write_wav), so two builds give the same SHA-256s.

What is asserted, and how exactly:
- Asserted exactly (bit or value identity, or the stated tolerance on the stated quantity):
  P1 (L_p < L; printed timings), P2 (provisional IR == exact IR bit for bit before t_mix,e,min - 2.5 ms, all four
  channels), P3 (provisional IR exactly 0.0 from L_p), S1 (both outputs value-identical, peak <= -1 dBFS, no
  normalisation), S2 (A == B by value, +0 == -0, before the grid bound; also anchor == B), S3 (each render nulls
  against a float64 FFT convolution of the IR it wrote, residual <= -120 dB), S4 (A exactly 0 from the grid bound;
  <= -120 dB re the hold between the true end and it; free decay >= L), Seat 2's seal asserts (provisional yes;
  L_p < L; L == 12 s; L_p <= 3.82 s; T60 8.0 +- 0.1 s for 63 Hz-1 kHz; 60 (L_f - t_mix,e,max) / T60_b >= 18.7 dB in
  every band), Seat 1's band coverage (63 Hz-4 kHz within 20 dB of the strongest band) and prefix check
  (10 log10(E(A - B)/E(B)) <= -18.27 dB over [0, release + L_f - 0.1 s)), the level (+-1 dB of the noise reference).
- Measured approximations (asserted with the stated kit tolerance, and printed):
  P4' (c_b per band from the band-filtered IRs, a least-squares gain of provisional on exact over
  [t_mix,e + 0.1 s, L_f - 0.05 s); printed in dB beside a prediction from the exact IR's band energies; asserted
  |20 log10 c_b| <= 1 dB, AX47 (b)'s asserted step bound) and P5' (the fade shape: a least-squares gain of
  provisional on exact in 2.5 ms windows over [L_f, L_p), divided by the pre-fade gain, against Seat 3's raised
  cosine 0.5 (1 + cos(pi (j - lf + 1)/(fadeLen + 1))) weighted by the exact IR's energy in the window; asserted
  within FADE_TOL = 0.05; the fade's energy ratio E_prov/E_exact over [L_f, L_p) asserted strictly between the hard
  cut (0) and no fade (the pre-fade c^2)). The tap of L_f in the aligned IR is rounded from emission time, so the
  formula's phase is known to +-1 sample: that, and the per-band c_b inside a broadband window, is why P5' is not to
  1e-9.
- Printed only: P6 (per-band energy share of the exact IR past L_f), S5 (per-band and per-partial A - B over the last
  1 s of the hold), S6 (no detector asserted at the cut; nothing printed beyond S4/S7), S7 (10 log10(E_B/E_A) per band
  in 30 ms windows on a 100 ms grid after the release), B's and A's per-band level in the 100 ms after
  release + L_f re the hold, the prefix value under the other readings of "release + L_f".
- Not possible from the CLI (needs a C++ test): P4 exactly (provisional unit decay = c_b x exact unit decay per band
  on [t_mix,e + 2.5 ms, L_f) to 1e-9 relative, via StagedBuild::unitDecays()) and P5 exactly (the fade gain against
  the formula to 1e-9, monotone, first value >= 1 - 1e-5). Proposed: a Catch2 case `[ax49-l4]` that plans S' with
  StagedBuild, runs assembleProvisional() and assemble(), takes both unitDecays() per emitter and band, and asserts
  both statements, with N-L1 (a hard cut at L_f) and N-L2 (another tailSeed) failing them.
"""

from __future__ import annotations

import argparse
import copy
import csv
import json
import math
import os
import pathlib
import re
import shutil
import sys
import time

import numpy as np

REPO = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))

from tools.acoustics import bands, render_cli, signals, wav  # noqa: E402
from tools.ci import abx_kit  # noqa: E402  (read-only: _run, make_scene, seal, verify_session, binom_tail, constants)

FS = abx_kit.FS  # 48 kHz, as the AX47 kit
PARTITION = abx_kit.PARTITION  # P = 512 (F3: the kit's P)
BLOCK = abx_kit.BLOCK  # fixed block 512 (F2 as composed: realtime emulation with a fixed block)
TAIL_SEED = abx_kit.TAIL_SEED  # decision item 1: one tailSeed, the kit's, shared by A and B
MAX_PEAK_DBFS = abx_kit.MAX_PEAK_DBFS  # item 3 (Seat 1): peak <= -1 dBFS, no normalisation

# ---- Scene S' (decision item 2; Seat 2, file 4-seat2) ----
DIMENSIONS_M = (100.0, 100.0, 100.0)
SCATTERING = 0.3
LISTENER = (50.0, 30.0, 1.7)
EMITTERS = ((45.0, 70.0, 2.0), (55.0, 70.0, 2.0))
# Per band, found by iterating on scene data until the engine's diagnostics print t60 8.0 +- 0.1 s from 63 Hz to 1 kHz
# (air absorption included, AX4); above 1 kHz the 1 kHz value (Seat 2: "alpha stays at the 1 kHz value").
ABSORPTION = (0.2836145906046942, 0.2801163239249038, 0.2704382479375733, 0.2543793051751666,
              0.23188082812760125, 0.23188082812760125, 0.23188082812760125, 0.23188082812760125)
T60_TARGET_S = 8.0  # item 2: T60 8.0 +- 0.1 s from 63 Hz to 1 kHz
T60_TOL_S = 0.1
T60_BANDS = 5  # bands 0-4: 63 Hz .. 1 kHz
L_S = 12.0  # Seat 2: L at the 12 s cap (1.5 x 8)
LP_MAX_S = 3.82  # Seat 2: L_p <= 3.82 s
DEPTH_MIN_DB = 18.7  # Seat 2 / AX49: decay >= 18.7 dB from t_mix,e,max to L_f
# Item 9 style label (decider file 6 item 3, "fully wet" answering Seat 9; Seat 2: 10^6 m^3, no product room class)
LABEL = ("ax49_l4_cube: synthetic 100 × 100 × 100 m, V 10^6 m³, scattering 0.3, T60 8.0 s from 63 Hz to 1 kHz "
         "(T60_max 8 s, air absorption included; per-band T60 printed): a stress geometry for AX49's provisional tail, "
         "not a room prediction or a validated preset. A = AX49 provisional tail (Engine::assembleProvisional, "
         "validation-only flag --ax49-provisional); B = full engine tail ('exact' = full synthesis, not a "
         "measurement). Fully wet: the whole rendered IR (direct, early part and tail), no dry path.")
FORBIDDEN_LABEL_WORDS = ("hall", "church", "cathedral", "occupied")  # Seat 9 / Seat 2: no product room class

# ---- Chord (decision item 3; Seat 1, file 4-seat1, verbatim) ----
L4_CHORD_VERSION = "l4-chord-v1"
L4_CHORD_SEED = 4901  # kit choice: the phases' seed (pinned; versioned with L4_CHORD_VERSION)
L4_NOTES = (("C2", 65.406), ("G2", 97.999), ("C3", 130.813), ("E3", 164.814), ("G3", 195.998))
PARTIAL_MAX_HZ = 5000.0  # amplitudes 1/k for k f0 <= 5 kHz
SILENCE_S = 0.5
ATTACK_S = 0.020  # raised cosine
HOLD_S = 4.0
RELEASE_S = 0.010  # raised cosine
STEADY_S = 1.0  # the steady-state window: the last 1 s of the hold (level, S5, band coverage)
COVERAGE_BANDS_HZ = (63.0, 125.0, 250.0, 500.0, 1000.0, 2000.0, 4000.0)  # Seat 1: 63 Hz-4 kHz within 20 dB
COVERAGE_DB = 20.0
LEVEL_TOL_DB = 1.0  # Seat 1: steady-state RMS equal to the AX47 noise stimuli's within +-1 dB
L4_REF_NOISE_SEED = 4903  # kit choice: the reference pink-noise burst's seed
REF_SCENE = "layout4_s1/both_wall"  # S-W, the AX47 noise scene heard first (M3-1)

# ---- Checks (Seat 3, files 4-seat3 and 8-seat3; Seat 1's prefix check) ----
PREFIX_LIMIT_DB = 20.0 * math.log10(10.0 ** (1.0 / 20.0) - 1.0)  # -18.27 dB: AX47 (b)'s +1 dB step difference
PREFIX_H_S = 0.1  # h in [0, release + L_f - h)
NULL_LIMIT_DB = -120.0  # S3 / S4: the Phase 06 criterion (file 8-seat3)
P2_GUARD_S = 0.0025  # P2: t_mix,e,min - 2.5 ms
C_B_MAX_DB = 1.0  # P4': AX47 (b)'s asserted bound, "the step <= 1 dB per emitter in every band"
FADE_WINDOW_S = 0.0025  # P5': 2.5 ms fit windows over the 0.1 s fade
FADE_TOL = 0.05  # P5': kit tolerance on the windowed fade gain (hard cut and no fade both deviate by ~1)
S7_WINDOW_S = 0.030  # S7: 30 ms windows
S7_GRID_S = 0.100  # S7: on a 100 ms grid after the release

# ---- Pass rule (decision item 5; Seat 1) ----
L4_SCORED = 16
L4_ANCHORS = 6
L4_BLOCK = 22
L4_BREAK_AFTER = 11
L4_CRITERION = 12  # >= 12/16
L4_ALPHA = 2517 / 65536  # P(K >= 12 | n 16, p 0.5) = 0.0384
L4_POWER = 0.63  # at p = 0.75 (0.630)
L4_ANCHOR_PASS = 5  # >= 5/6
L4_ANCHOR_DB = -3.0  # the anchor: exact with the tail at -3 dB (item 5's method)
L4_PLAN_SEED = 4902  # kit choice: the anchor slots' seed
LEVEL_KEY = "L4"  # manifest["blocks"]["L4"]; trial folders L4dB/trial_NN (abx_kit.seal's layout)
WORDING_DETECTED = "detected: AX49's Reversal fires (worst case: provisional current through the whole free decay)"
WORDING_NULL = "not detected in 16 trials by one listener (power 0.63), T60 8 s, held chord, omni diotic"

TIMING_RE = re.compile(r"ax49 provisional: t_mix,e,max ([0-9.e+-]+) s, T60_max ([0-9.e+-]+) s, L_f ([0-9.e+-]+) s, "
                       r"L_p ([0-9.e+-]+) s, L ([0-9.e+-]+) s, provisional (yes|no)")


class CheckFailed(RuntimeError):
    """A pre-registered check failed on a stimulus: the kit stops (it returns to the board; never loosened)."""


def _require(ok: bool, what: str) -> None:
    if not ok:
        raise CheckFailed(what)


def _db(num: float, den: float) -> float | None:
    return 10.0 * math.log10(num / den) if num > 0 and den > 0 else None


def _fmt(x, digits: int = 2) -> str:
    return "None" if x is None else f"{x:.{digits}f}"


def write_wav(path: pathlib.Path, data: np.ndarray, fs: int = FS) -> None:
    """IEEE float32 WAV, byte-deterministic (sealed hashes must reproduce): scipy's writer, not soundfile's, whose
    libsndfile PEAK chunk carries a timestamp."""
    from scipy.io import wavfile

    path = pathlib.Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    wavfile.write(path, int(fs), np.ascontiguousarray(data, dtype=np.float32))


# ---------------------------------------------------------------------------------------------------------
# Scene S' and its seal asserts (Seat 2)
# ---------------------------------------------------------------------------------------------------------


def make_l4_scene(tail_seed: int = TAIL_SEED) -> dict:
    """S' (decision item 2): medium_room.json's other fields, the geometry, materials and positions above."""
    scene = copy.deepcopy(json.loads((REPO / "tests" / "scenes" / "valid" / "medium_room.json").read_text()))
    scene["room"]["geometry"]["dimensions"] = list(DIMENSIONS_M)
    for face in ("xMin", "xMax", "yMin", "yMax", "floor", "ceiling"):
        scene["room"]["surfaces"][face] = {"absorption": list(ABSORPTION), "scattering": SCATTERING}
    scene["listener"]["position"] = list(LISTENER)
    for em, pos in zip(scene["emitters"], EMITTERS):
        em["position"] = list(pos)
    scene["render"]["tailSeed"] = tail_seed
    return scene


def parse_timing(stdout: str) -> dict:
    """render_cli --ax49-provisional's line (F1)."""
    m = TIMING_RE.search(stdout)
    if not m:
        raise RuntimeError(f"no 'ax49 provisional:' line in render_cli's output:\n{stdout}")
    keys = ("t_mix_e_max_s", "T60_max_s", "L_f_s", "L_p_s", "L_s")
    out = dict(zip(keys, map(float, m.groups()[:5])))
    out["provisional"] = m.group(6) == "yes"
    return out


def scene_asserts(timing: dict, diag: dict) -> dict:
    """Seat 2's seal asserts (file 4-seat2; decision item 2) and prints: per-band T60, the depth at L_f and L_p from
    t_mix,e,max, t_mix,e per emitter. Depth_b(t) = 60 (t - t_mix,e,max) / T60_b (Vorlaender Eq. 6.4, as AX49 K17')."""
    t60 = [float(x) for x in diag["t60"]]
    mix = timing["t_mix_e_max_s"]
    depth_lf = [60.0 * (timing["L_f_s"] - mix) / t for t in t60]
    depth_lp = [60.0 * (timing["L_p_s"] - mix) / t for t in t60]
    t60max = max(t60)
    rec = {"t60_s": t60, "T60_max_s": timing["T60_max_s"],
           "T60_max_bands": [bands.band_key(fc) for fc, t in zip(bands.OCTAVE_BANDS_HZ, t60) if t60max - t <= 1e-6],
           "t_mix_e_s": {e["id"]: float(e["mixS"]) for e in diag["emitters"]}, "t_mix_e_max_s": mix,
           "L_f_s": timing["L_f_s"], "L_p_s": timing["L_p_s"], "L_s": timing["L_s"],
           "provisional": timing["provisional"], "depth_at_L_f_db": depth_lf, "depth_at_L_p_db": depth_lp,
           "alignmentShiftS": float(diag["alignmentShiftS"])}
    _require(timing["provisional"], "S': render_cli prints provisional no (Seat 2: provisional == true)")
    for b in range(T60_BANDS):
        _require(abs(t60[b] - T60_TARGET_S) <= T60_TOL_S,
                 f"S': T60 {t60[b]:.3f} s in the {bands.band_key(bands.OCTAVE_BANDS_HZ[b])} Hz band, not 8.0 +- 0.1 s")
    _require(abs(timing["T60_max_s"] - t60max) <= 1e-4, f"T60_max printed {timing['T60_max_s']} != max t60 {t60max}")
    _require(timing["L_p_s"] < timing["L_s"], f"P1 / Seat 2: L_p {timing['L_p_s']} s >= L {timing['L_s']} s")
    _require(abs(timing["L_s"] - L_S) <= 1e-6, f"Seat 2: L {timing['L_s']} s != 12 s (1.5 x 8)")
    _require(timing["L_p_s"] <= LP_MAX_S, f"Seat 2: L_p {timing['L_p_s']} s > {LP_MAX_S} s")
    for fc, d in zip(bands.OCTAVE_BANDS_HZ, depth_lf):
        # every band (the T60_max bands bind; the others decay faster, so this is the same assert, stated for all)
        _require(d >= DEPTH_MIN_DB - 1e-6, f"Seat 2: decay {d:.3f} dB < 18.7 dB at L_f in the {bands.band_key(fc)} Hz band")
    return rec


# ---------------------------------------------------------------------------------------------------------
# IR checks (Seat 3 P1-P6)
# ---------------------------------------------------------------------------------------------------------


def _pad(x: np.ndarray, n: int) -> np.ndarray:
    if x.shape[0] >= n:
        return x
    return np.concatenate([x, np.zeros((n - x.shape[0], x.shape[1]), dtype=x.dtype)])


def tap(t_emission_s: float, diag: dict, fs: float = FS) -> int:
    """The aligned IR's tap of an emission time (tap 0 = alignmentShiftS after emission), rounded up as the
    flag's IR length is (L_p -> the provisional IR's length)."""
    return int(math.ceil((t_emission_s - float(diag["alignmentShiftS"])) * fs))


def first_difference(a: np.ndarray, b: np.ndarray) -> int:
    """First index where two (frames, channels) arrays differ by value on any channel (+0 == -0); len if none."""
    n = max(a.shape[0], b.shape[0])
    a, b = _pad(a, n), _pad(b, n)
    d = np.flatnonzero(np.any(a != b, axis=1))
    return int(d[0]) if d.size else n


def p2_check(prov: np.ndarray, exact: np.ndarray, diag: dict) -> dict:
    """P2: the provisional IR is bit-identical to the exact one on [0, t_mix,e,min - 2.5 ms), every channel."""
    mix_min = min(float(e["mixS"]) for e in diag["emitters"])
    pre = int((mix_min - float(diag["alignmentShiftS"]) - P2_GUARD_S) * FS)
    n = max(prov.shape[0], exact.shape[0])
    p, x = _pad(prov, n), _pad(exact, n)
    bits = np.array_equal(p[:pre].view(np.uint32), x[:pre].view(np.uint32))
    return {"window_taps": pre, "bit_identical": bool(bits), "first_differing_tap": first_difference(prov, exact),
            "ok": bool(bits and pre > 0)}


def p3_check(prov: np.ndarray, timing: dict, diag: dict) -> dict:
    """P3: exactly 0.0 from L_p on (also reports the last non-zero tap, L_p as measured in the aligned IR)."""
    lp = tap(timing["L_p_s"], diag)
    nz = np.flatnonzero(np.any(prov != 0.0, axis=1))
    last = int(nz[-1]) + 1 if nz.size else 0
    zero = prov.shape[0] <= lp or bool(np.all(prov[lp:] == 0.0))
    return {"L_p_tap": lp, "file_length": int(prov.shape[0]), "L_p_measured_taps": last, "zero_from_L_p": zero,
            "ok": bool(zero and last <= lp)}


def _ls_gain(p: np.ndarray, e: np.ndarray) -> float:
    den = float(np.dot(e, e))
    return float(np.dot(p, e)) / den if den > 0 else float("nan")


def p4_band_gains(prov: np.ndarray, exact: np.ndarray, timing: dict, diag: dict) -> dict:
    """P4' (measured approximation of P4; the exact statement needs unitDecays(), see the module docstring): per
    emitter (output 0) and band, c_b = the least-squares gain of the band-filtered provisional on the band-filtered
    exact IR over [t_mix,e + 0.1 s, L_f - 0.05 s) (inside [t_mix,e + 2.5 ms, L_f), away from the filters' edges);
    printed in dB beside a model of Engine.h's c_b = 1/sqrt(E_p,b / f_b): c_b^2 = f_b / f^_b, f_b the expected and
    f^_b the realised (exact IR, band-filtered) share of the tail energy from t_mix,e that falls in [t_mix,e, L_p),
    each weighted 1 before L_f and by Seat 3's raised cosine over [L_f, L_p), the expected decay
    exp(-13.8155 t / T60_b) (print only; whether E_p,b counts the fade is not visible from the CLI). The provisional is
    the exact tail up to this realisation ratio, not energy-preserving: its missing energy past L_f is AX47 (b)'s
    truncation loss. Asserted: |20 log10 c_b| <= 1 dB (AX47 (b)'s asserted step bound)."""
    lf, lp = tap(timing["L_f_s"], diag), tap(timing["L_p_s"], diag)
    g = fade_gain(lp - lf)
    n = exact.shape[0]
    p = _pad(prov, n)
    rows = []
    for e in diag["emitters"]:
        c = e["channel"] * 2
        mix = tap(float(e["mixS"]), diag)
        w0, w1 = mix + int(0.1 * FS), lf - int(0.05 * FS)
        row = {"emitter": e["id"], "c_b_db": {}, "c_b_pred_db": {}}
        for fc in bands.OCTAVE_BANDS_HZ:
            pb = bands.filter_band(p[:, c].astype(np.float64), FS, fc)
            xb = bands.filter_band(exact[:, c].astype(np.float64), FS, fc)
            cb = _ls_gain(pb[w0:w1], xb[w0:w1])
            e2 = xb**2
            wgt = np.ones(lp - mix)
            wgt[lf - mix :] = g
            expected = np.exp(-13.8155 * np.arange(n - mix) / FS / float(diag["t60"][bands.OCTAVE_BANDS_HZ.index(fc)]))
            f_exp = float(np.sum(expected[: lp - mix] * wgt**2) / np.sum(expected))
            f_real = float(np.sum(e2[mix:lp] * wgt**2) / np.sum(e2[mix:]))
            pred = math.sqrt(f_exp / f_real)
            row["c_b_db"][bands.band_key(fc)] = 20 * math.log10(abs(cb)) if cb == cb and cb != 0 else None
            row["c_b_pred_db"][bands.band_key(fc)] = 20 * math.log10(pred)
        rows.append(row)
    worst = max(abs(v) if v is not None else math.inf for r in rows for v in r["c_b_db"].values())
    return {"rows": rows, "worst_abs_db": worst, "bound_db": C_B_MAX_DB, "ok": bool(worst <= C_B_MAX_DB)}


def fade_gain(fade_len: int) -> np.ndarray:
    """Seat 3's P5 formula: 0.5 (1 + cos(pi (j - lf + 1)/(fadeLen + 1))), j - lf = 0 .. fadeLen - 1."""
    return 0.5 * (1.0 + np.cos(np.pi * (np.arange(fade_len) + 1.0) / (fade_len + 1.0)))


def p5_fade_check(prov: np.ndarray, exact: np.ndarray, timing: dict, diag: dict) -> dict:
    """P5' (measured approximation of P5): per channel, the gain c = LS gain of provisional on exact over the 0.5 s
    before L_f; then in 2.5 ms windows over [L_f, L_p) the LS gain divided by c, against the energy-weighted mean of
    the raised cosine in that window (asserted within FADE_TOL; the same windows before L_f are printed, their
    deviation from 1 being the method's own noise); and R = E_prov / E_exact over [L_f, L_p), asserted strictly
    between the hard cut (0) and no fade (c^2), with its prediction c^2 sum(g^2 e^2)/sum(e^2) printed.
    N-L1: a hard cut at L_f gives windowed gains 0 (deviation up to 1) and R = 0; no fade gives gains 1 and R = c^2."""
    lf, lp = tap(timing["L_f_s"], diag), tap(timing["L_p_s"], diag)
    g = fade_gain(lp - lf)
    n = exact.shape[0]
    p = _pad(prov, n).astype(np.float64)
    x = exact.astype(np.float64)
    w = int(round(FADE_WINDOW_S * FS))
    pre0 = lf - int(round(0.5 * FS))
    rows, ok = [], True
    for c in range(x.shape[1]):
        cg = _ls_gain(p[pre0:lf, c], x[pre0:lf, c])
        fade_dev, pre_dev, gains = 0.0, 0.0, []
        for s in range(lf, lp - w + 1, w):
            e2 = x[s : s + w, c] ** 2
            expect = float(np.sum(g[s - lf : s - lf + w] * e2) / np.sum(e2))
            got = _ls_gain(p[s : s + w, c], x[s : s + w, c]) / cg
            gains.append(got)
            fade_dev = max(fade_dev, abs(got - expect))
        for s in range(pre0, lf - w + 1, w):
            pre_dev = max(pre_dev, abs(_ls_gain(p[s : s + w, c], x[s : s + w, c]) / cg - 1.0))
        ef, xf = float(np.sum(p[lf:lp, c] ** 2)), float(np.sum(x[lf:lp, c] ** 2))
        r = ef / xf
        r_pred = cg**2 * float(np.sum(g**2 * x[lf:lp, c] ** 2)) / xf
        between = 0.0 < r < cg**2
        ok_c = bool(fade_dev <= FADE_TOL and between)
        ok = ok and ok_c
        rows.append({"channel": c, "pre_fade_gain": cg, "fade_max_deviation": fade_dev,
                     "pre_fade_max_deviation": pre_dev, "first_window_gain": gains[0] if gains else None,
                     "energy_ratio": r, "energy_ratio_pred": r_pred, "hard_cut": 0.0, "no_fade": cg**2,
                     "strictly_between": between, "ok": ok_c})
    return {"L_f_tap": lf, "L_p_tap": lp, "fade_taps": lp - lf, "window_taps": w, "tolerance": FADE_TOL,
            "rows": rows, "ok": ok}


def p6_share(exact: np.ndarray, timing: dict, diag: dict) -> dict:
    """P6 (print only): per band, the exact heard IR's (emitters summed, output 0) energy past L_f, as a share of the
    tail from t_mix,e,max and of the whole IR (AX49 K17': predicted <= 0.0134)."""
    h = exact[:, 0].astype(np.float64) + exact[:, 2].astype(np.float64)
    lf, mix = tap(timing["L_f_s"], diag), tap(timing["t_mix_e_max_s"], diag)
    out = {}
    for fc in bands.OCTAVE_BANDS_HZ:
        y, lead = bands.filter_band_with_lead(h, FS, fc)
        e2 = y**2
        out[bands.band_key(fc)] = {"of_tail": float(np.sum(e2[lead + lf :]) / np.sum(e2[lead + mix :])),
                                   "of_whole_ir": float(np.sum(e2[lead + lf :]) / np.sum(e2))}
    return out


# ---------------------------------------------------------------------------------------------------------
# The chord (Seat 1) and the level reference
# ---------------------------------------------------------------------------------------------------------


def _rc(n: int) -> np.ndarray:
    return 0.5 - 0.5 * np.cos(np.pi * (np.arange(n) + 0.5) / n)


def chord_partials() -> list[dict]:
    """Every partial (note, k, f, amplitude 1/k, phase) in a fixed order; phases from default_rng(L4_CHORD_SEED),
    drawn note by note, k = 1, 2, ..."""
    rng = np.random.default_rng(L4_CHORD_SEED)
    out = []
    for name, f0 in L4_NOTES:
        kmax = int(math.floor(PARTIAL_MAX_HZ / f0 + 1e-9))
        phases = rng.uniform(0.0, 2.0 * math.pi, size=kmax)
        out += [{"note": name, "k": k, "f_hz": k * f0, "amp": 1.0 / k, "phase": float(phases[k - 1])}
                for k in range(1, kmax + 1)]
    return out


def chord_marks(free_samples: int) -> dict:
    n_sil, n_att = int(round(SILENCE_S * FS)), int(round(ATTACK_S * FS))
    n_hold, n_rel = int(round(HOLD_S * FS)), int(round(RELEASE_S * FS))
    rel = n_sil + n_att + n_hold
    return {"onset": n_sil, "hold_start": n_sil + n_att, "release_start": rel, "end": rel + n_rel,
            "total": rel + n_rel + free_samples}


def chord_signal(free_samples: int) -> tuple[np.ndarray, dict]:
    """The unscaled chord (mono, float64) and its sample marks: 0.5 s silence, 20 ms raised-cosine attack, 4 s hold,
    10 ms raised-cosine release (the chord adds no decay of its own), then `free_samples` of silence."""
    m = chord_marks(free_samples)
    n = m["end"] - m["onset"]
    t = np.arange(n) / FS
    tone = np.zeros(n)
    for p in chord_partials():
        tone += p["amp"] * np.sin(2.0 * np.pi * p["f_hz"] * t + p["phase"])
    env = np.ones(n)
    n_att, n_rel = m["hold_start"] - m["onset"], m["end"] - m["release_start"]
    env[:n_att] = _rc(n_att)
    env[n - n_rel :] = _rc(n_rel)[::-1]
    x = np.zeros(m["total"])
    x[m["onset"] : m["end"]] = tone * env
    return x, m


def free_decay_samples(ir_len: int) -> int:
    """>= L of free decay, and >= the IR length plus two partitions (so the whole convolution, and S4's grid bound,
    fall inside the stimulus); the stimulus then ends on a partition boundary."""
    n = max(int(round(L_S * FS)), ir_len + 2 * PARTITION)
    end = chord_marks(0)["end"]
    return int(math.ceil((end + n) / PARTITION)) * PARTITION - end


def reference_level(binary: pathlib.Path, work: pathlib.Path) -> dict:
    """The AX47 noise reference (Seat 1: the noise stimuli's heard RMS): a 1 s unit-RMS pink-noise burst (whole
    partitions, 5 ms raised-cosine edges, as abx_kit.noise_programme) at NOISE_LEVEL_DBFS through S-W
    (layout4_s1/both_wall), rendered as the L4 arms are; RMS of output 0 over [0.5, 1.0) s of the burst."""
    scene = work / "ref_scene.json"
    scene.write_text(json.dumps(abx_kit.make_scene(REF_SCENE), indent=1))
    ir_path = work / "ref_ir.wav"
    abx_kit._run(binary, "--scene", scene, "--mode", "omni", "--ir", ir_path)
    ir_len = wav.read_float32(ir_path)[0].shape[0]
    lead = int(round(SILENCE_S * FS))
    burst = int(round(abx_kit.NOISE_BURST_S * FS / PARTITION)) * PARTITION
    x = np.zeros(lead + burst + ir_len + 2 * PARTITION)
    b = signals.apply_fades(signals.pink_noise(burst, L4_REF_NOISE_SEED), FS, abx_kit.FADE_S)
    x[lead : lead + burst] = b * signals.db_to_amp(abx_kit.NOISE_LEVEL_DBFS)
    inp, out = work / "ref_in.wav", work / "ref_out.wav"
    write_wav(inp, signals.to_stereo(x), FS)
    y = render(binary, scene, inp, out)
    seg = y[lead + int(round(0.5 * FS)) : lead + int(round(1.0 * FS)), 0].astype(np.float64)
    rms = math.sqrt(float(np.mean(seg**2)))
    return {"scene": REF_SCENE, "noise_seed": L4_REF_NOISE_SEED, "noise_level_dbfs": abx_kit.NOISE_LEVEL_DBFS,
            "burst_samples": burst, "window_s": [0.5, 1.0], "rms": rms, "rms_dbfs": 20 * math.log10(rms),
            "scene_sha256": abx_kit.sha256_file(scene), "ir_sha256": abx_kit.sha256_file(ir_path)}


# ---------------------------------------------------------------------------------------------------------
# Rendering (F3: one tool, one path)
# ---------------------------------------------------------------------------------------------------------


def render(binary, scene_path, in_path, out_path, *extra) -> np.ndarray:
    abx_kit._run(binary, "--scene", scene_path, "--mode", "omni", "--in", in_path, "--out", out_path,
                 "--realtime-emulation", "--block", BLOCK, "--partition", PARTITION, *extra)
    return wav.read_float32(out_path)[0]


ARMS = {"provisional": ("--ax49-provisional",), "exact": (),
        "anchor": ("--abx-step-db", repr(L4_ANCHOR_DB), "--abx-step-sample", "0")}


# ---------------------------------------------------------------------------------------------------------
# Stimulus checks (Seat 3 S1-S7, file 8-seat3's grid; Seat 1's coverage and prefix check)
# ---------------------------------------------------------------------------------------------------------


def first_nonzero(x: np.ndarray) -> int:
    nz = np.flatnonzero(x != 0.0)
    return int(nz[0]) if nz.size else x.size


def end_of_input(x: np.ndarray) -> int:
    nz = np.flatnonzero(x != 0.0)
    return int(nz[-1]) + 1 if nz.size else 0


def s1_check(y: np.ndarray) -> dict:
    """S1: omni, the two outputs identical (diotic, by value); peak <= -1 dBFS; nothing normalised."""
    same = bool(np.array_equal(y[:, 0], y[:, 1]))
    peak = 20 * math.log10(max(float(np.max(np.abs(y))), 1e-30))
    return {"diotic": same, "peak_dbfs": peak, "ok": bool(same and peak <= MAX_PEAK_DBFS)}


def s2_check(x_in: np.ndarray, a: np.ndarray, b: np.ndarray, n_d: int) -> dict:
    """S2 (file 8-seat3): A == B by value (+0 == -0) before (floor(n_on/P) + floor(n_d/P)) P in the written file
    (Seat 3's (... + 1) P less the partition of latency render_cli removes); n_on = first non-zero input sample,
    n_d = first IR tap where the two IRs differ."""
    n_on = first_nonzero(x_in)
    bound = (n_on // PARTITION + n_d // PARTITION) * PARTITION
    n = min(a.shape[0], b.shape[0])
    same = bool(np.array_equal(a[: min(bound, n)], b[: min(bound, n)]))
    first = first_difference(a[:n], b[:n])
    return {"n_on": n_on, "n_d": n_d, "bound_sample": bound, "identical_before_bound": same,
            "first_differing_sample": first, "margin_samples": first - bound, "ok": same}


def s3_check(x_in: np.ndarray, y: np.ndarray, ir: np.ndarray) -> dict:
    """S3 (file 8-seat3): the render equals a float64 FFT convolution of the IR it wrote (output ch = conv(input,
    ir[:, ch] + ir[:, 2 + ch]), the input channels being identical), residual / signal energy <= -120 dB."""
    from scipy import signal as sps

    worst = -math.inf
    per = []
    for ch in range(2):
        ref = sps.fftconvolve(x_in.astype(np.float64), ir[:, ch].astype(np.float64) + ir[:, 2 + ch].astype(np.float64))
        n = max(ref.size, y.shape[0])
        r = np.zeros(n)
        r[: ref.size] = ref
        o = np.zeros(n)
        o[: y.shape[0]] = y[:, ch]
        db = 10 * math.log10(max(float(np.sum((o - r) ** 2)), 1e-300) / float(np.sum(r**2)))
        per.append(db)
        worst = max(worst, db)
    return {"residual_db": per, "worst_db": worst, "limit_db": NULL_LIMIT_DB, "margin_db": NULL_LIMIT_DB - worst,
            "ok": bool(worst <= NULL_LIMIT_DB)}


def s4_check(x_in: np.ndarray, a: np.ndarray, prov_ir: np.ndarray, hold_ms: float, m: dict) -> dict:
    """S4 (file 8-seat3): A exactly 0 from (ceil(n_end/P) + K_p) P in the written file (Seat 3's (... + 1) P less the
    latency), K_p = ceil(L_p/P), L_p measured in the aligned IR (last non-zero tap + 1); between the true end of the
    convolution and that bound, <= -120 dB re the hold (mean square); free decay >= L after the release."""
    n_end = end_of_input(x_in)
    nz = np.flatnonzero(np.any(prov_ir != 0.0, axis=1))
    lp = int(nz[-1]) + 1
    k_p = -(-lp // PARTITION)
    bound = (-(-n_end // PARTITION) + k_p) * PARTITION
    true_end = n_end + lp - 1  # the last non-zero sample of conv(input, ir) is n_end - 1 + lp - 1
    zero = bool(np.all(a[bound:] == 0.0))
    seg = a[true_end:bound].astype(np.float64)
    resid = _db(float(np.mean(seg**2)), hold_ms) if seg.size and np.any(seg != 0) else None
    free = x_in.size - m["end"]
    ok = zero and (resid is None or resid <= NULL_LIMIT_DB) and free >= int(round(L_S * FS))
    return {"n_end": n_end, "L_p_measured_taps": lp, "K_p": k_p, "zero_from_sample": bound, "true_end_sample": true_end,
            "exactly_zero_from_bound": zero, "partial_block_db_re_hold": resid, "partial_block_samples": int(seg.size),
            "free_decay_s": free / FS, "free_decay_min_s": L_S, "ok": bool(ok)}


def prefix_check(a: np.ndarray, b: np.ndarray, end: int, lf_aligned_s: float) -> dict:
    """Seat 1's prefix check (decision item 4; AX49's prefix form): 10 log10(E(A - B)/E(B)) <= -18.27 dB over
    [0, release + L_f - h) of output 0, h = 0.1 s; "release" = the end of the 10 ms release (the first silent input
    sample), L_f in the aligned output (L_f - alignmentShiftS: where the cut actually begins in the written file)."""
    w = end + int(round((lf_aligned_s - PREFIX_H_S) * FS))
    d = a[:w, 0].astype(np.float64) - b[:w, 0].astype(np.float64)
    v = _db(float(np.sum(d**2)), float(np.sum(b[:w, 0].astype(np.float64) ** 2)))
    v = -math.inf if v is None and not np.any(d) else v
    return {"window_end_sample": w, "window_end_s": w / FS, "value_db": v, "limit_db": PREFIX_LIMIT_DB,
            "margin_db": PREFIX_LIMIT_DB - v, "ok": bool(v <= PREFIX_LIMIT_DB)}


def band_signals(y: np.ndarray) -> dict[str, np.ndarray]:
    return {bands.band_key(fc): bands.filter_band(y[:, 0].astype(np.float64), FS, fc) for fc in bands.OCTAVE_BANDS_HZ}


def band_coverage(bb: dict, m: dict) -> dict:
    """Seat 1: the exact render's steady state, every band 63 Hz-4 kHz within 20 dB of the strongest (asserted);
    8 kHz printed."""
    s0, s1 = m["release_start"] - int(round(STEADY_S * FS)), m["release_start"]
    lv = {k: 10 * math.log10(float(np.mean(v[s0:s1] ** 2))) for k, v in bb.items()}
    cov = [bands.band_key(fc) for fc in COVERAGE_BANDS_HZ]
    top = max(lv[k] for k in cov)
    rel = {k: lv[k] - top for k in lv}
    return {"level_dbfs": lv, "re_strongest_db": rel, "strongest": max(cov, key=lambda k: lv[k]),
            "weakest_asserted": min(cov, key=lambda k: lv[k]), "limit_db": -COVERAGE_DB,
            "ok": bool(all(rel[k] >= -COVERAGE_DB for k in cov))}


def s5_hold(a: np.ndarray, b: np.ndarray, ab: dict, bb: dict, m: dict) -> dict:
    """S5 (print only): per band 10 log10(E_A/E_B) over the last 1 s of the hold, and per partial (Hann-windowed
    projection at each partial frequency; partials closer than 2 Hz are one cluster: C2 k = 3 and G3 are 0.22 Hz
    apart, unresolvable in 1 s)."""
    s0, s1 = m["release_start"] - int(round(STEADY_S * FS)), m["release_start"]
    per_band = {k: 10 * math.log10(float(np.sum(ab[k][s0:s1] ** 2)) / float(np.sum(bb[k][s0:s1] ** 2))) for k in bb}
    freqs = sorted({round(p["f_hz"], 3) for p in chord_partials()})
    clusters: list[float] = []
    for f in freqs:
        if not clusters or f - clusters[-1] >= 2.0:
            clusters.append(f)
    n = s1 - s0
    win = np.hanning(n)
    t = np.arange(n) / FS
    xa, xb = a[s0:s1, 0].astype(np.float64) * win, b[s0:s1, 0].astype(np.float64) * win
    diffs = []
    for f in clusters:
        e = np.exp(-2j * np.pi * f * t)
        diffs.append(20 * math.log10(abs(np.dot(xa, e)) / abs(np.dot(xb, e))))
    d = np.asarray(diffs)
    return {"per_band_db": per_band, "partials_hz": clusters, "per_partial_db": diffs,
            "per_partial_rms_db": float(np.sqrt(np.mean(d**2))), "per_partial_max_abs_db": float(np.max(np.abs(d)))}


def after_cut_levels(ab: dict, bb: dict, m: dict, lf_aligned_s: float) -> dict:
    """S4's print (file 4-seat3) and Seat 1's "the cut's energy per band re B's steady state": A's and B's per-band
    mean square in the 100 ms after release + L_f, re B's hold."""
    s0, s1 = m["release_start"] - int(round(STEADY_S * FS)), m["release_start"]
    c0 = m["end"] + int(round(lf_aligned_s * FS))
    c1 = c0 + int(round(0.1 * FS))
    out = {}
    for k in bb:
        hold = float(np.mean(bb[k][s0:s1] ** 2))
        out[k] = {"B_db_re_hold": _db(float(np.mean(bb[k][c0:c1] ** 2)), hold),
                  "A_db_re_hold": _db(float(np.mean(ab[k][c0:c1] ** 2)), hold)}
    return {"window_s": [c0 / FS, c1 / FS], "bands": out}


def s7_handover(a: np.ndarray, ab: dict, bb: dict, m: dict, total: int) -> dict:
    """S7 (print only): the would-be handover step 10 log10(E_B/E_A) per band in 30 ms windows on a 100 ms grid after
    the release (None where A is exactly 0 in the window, broadband: the step from silence is unbounded; the band
    filters' zero-phase smear leaves A's band signals non-zero there, which is not A)."""
    w, g = int(round(S7_WINDOW_S * FS)), int(round(S7_GRID_S * FS))
    starts = list(range(m["end"], total - w + 1, g))
    out = {}
    for k in bb:
        row = []
        for s in starts:
            if not np.any(a[s : s + w, 0]):
                row.append(None)
                continue
            ea, eb = float(np.sum(ab[k][s : s + w] ** 2)), float(np.sum(bb[k][s : s + w] ** 2))
            row.append(_db(eb, ea))
        out[k] = row
    return {"grid_s_after_release": [(s - m["end"]) / FS for s in starts], "window_s": S7_WINDOW_S, "bands": out}


# ---------------------------------------------------------------------------------------------------------
# Trial plan and pack
# ---------------------------------------------------------------------------------------------------------


def trial_plan() -> list[dict]:
    """One block of 22: 16 scored (A = provisional, B = exact) and 6 anchors (A = anchor, B = exact) at seeded slots
    (L4_PLAN_SEED), a break after trial 11. Which of A and B is X is drawn at sealing (abx_kit.seal)."""
    rng = np.random.default_rng(L4_PLAN_SEED)
    slots = sorted(int(s) for s in rng.choice(L4_BLOCK, size=L4_ANCHORS, replace=False))
    plan = []
    for t in range(L4_BLOCK):
        anchor = t in slots
        plan.append({"trial": t + 1, "kind": "anchor" if anchor else "scored",
                     "g_db": L4_ANCHOR_DB if anchor else None, "A": "anchor" if anchor else "provisional",
                     "B": "exact", "break_after": t + 1 == L4_BREAK_AFTER})
    assert sum(p["kind"] == "scored" for p in plan) == L4_SCORED
    return plan


def _link(src: pathlib.Path, dst: pathlib.Path) -> None:
    dst.parent.mkdir(parents=True, exist_ok=True)
    try:
        os.link(src, dst)
    except OSError:
        shutil.copyfile(src, dst)


def _prepare_out(out: pathlib.Path) -> pathlib.Path:
    l4 = out / "l4"
    if l4.exists():
        ours = (l4 / "manifest.json").exists() or (l4 / "check_failed.json").exists()
        if not ours and any(l4.iterdir()):
            raise RuntimeError(f"{l4} exists and is not an L4 pack; refusing to overwrite it")
        shutil.rmtree(l4)
    l4.mkdir(parents=True)
    return l4


def write_pack(l4: pathlib.Path, stimuli: dict[str, np.ndarray], man: dict) -> None:
    """The pack abx_kit.seal reads unchanged: stimuli/{provisional,exact,anchor}.wav, the block at
    L4dB/trial_NN/{A,B}.wav (hard links to the stimuli where the file system allows, else copies),
    manifest["blocks"]["L4"] (trial, kind, g_db), the labelled familiarisation pairs and the pass rule."""
    stim = {}
    for k in ARMS:
        p = l4 / "stimuli" / f"{k}.wav"
        write_wav(p, stimuli[k], FS)
        stim[k] = p
        man["sha256"][f"stimuli/{k}.wav"] = abx_kit.sha256_file(p)
    block = []
    for t in trial_plan():
        d = l4 / f"{LEVEL_KEY}dB" / f"trial_{t['trial']:02d}"
        _link(stim[t["A"]], d / "A.wav")
        _link(stim[t["B"]], d / "B.wav")
        block.append({**t, "sha256": {"A": man["sha256"][f"stimuli/{t['A']}.wav"],
                                      "B": man["sha256"][f"stimuli/{t['B']}.wav"]}})
    man["blocks"] = {LEVEL_KEY: block}
    # Familiarisation (decision item 5): labelled, never scored, no scored feedback.
    fam = [("pair_01_provisional_vs_exact", {"provisional.wav": "provisional", "exact.wav": "exact"}),
           ("pair_02_anchor_vs_exact", {"anchor_tail_-3dB.wav": "anchor", "exact.wav": "exact"})]
    man["familiarisation"] = []
    for name, files in fam:
        for fname, k in files.items():
            _link(stim[k], l4 / "familiarisation" / name / fname)
        man["familiarisation"].append({"pair": name, "files": files, "labelled": True, "scored": False})
    man["pass_rule"] = {"criterion": f">= {L4_CRITERION}/{L4_SCORED}", "alpha": L4_ALPHA, "alpha_exact": "2517/65536",
                        "power_at_0.75": L4_POWER, "anchors": f"{L4_ANCHORS} at tail {L4_ANCHOR_DB} dB, pass >= "
                        f"{L4_ANCHOR_PASS}/{L4_ANCHORS}, else void with one rerun", "break_after": L4_BREAK_AFTER,
                        "plan_seed": L4_PLAN_SEED, "detected": WORDING_DETECTED, "null": WORDING_NULL}


def _build(l4: pathlib.Path, man: dict, binary: pathlib.Path, log) -> dict:
    """Build, check and pack L4 (decision items 1-6, 8): every check above is asserted before anything is packed; a
    failure raises CheckFailed (the kit stops; the value goes back to the board, never loosened)."""
    t_start = time.monotonic()
    work = l4 / "_work"
    work.mkdir()
    man.update({"chain": "l4", "label": LABEL, "preregistration": "phase-07c-2b decider file 6, M3-7 / M3-L4 items 1-8",
                 "design": "L4-A", "fs": FS, "partition": PARTITION, "block": BLOCK, "render_cli": str(binary),
                 "tailSeed": TAIL_SEED, "sha256": {}})
    for w in FORBIDDEN_LABEL_WORDS:
        _require(w not in LABEL.lower(), f"label names '{w}' (Seats 2, 9)")

    # ---- Scene S' and its IRs ----
    scene_path = l4 / "scene.json"
    scene_path.write_text(json.dumps(make_l4_scene(), indent=1))
    man["sha256"]["scene.json"] = abx_kit.sha256_file(scene_path)
    irs = {k: l4 / "ir" / f"{k}.wav" for k in ARMS}
    irs["provisional"].parent.mkdir()
    so = abx_kit._run(binary, "--scene", scene_path, "--mode", "omni", "--ax49-provisional", "--ir",
                      irs["provisional"], "--diagnostics", l4 / "ir" / "diagnostics_provisional.json")
    timing = parse_timing(so)
    abx_kit._run(binary, "--scene", scene_path, "--mode", "omni", "--ir", irs["exact"], "--diagnostics",
                 l4 / "ir" / "diagnostics_exact.json")
    abx_kit._run(binary, "--scene", scene_path, "--mode", "omni", "--ir", work / "unstepped.wav", "--abx-step-db",
                 repr(L4_ANCHOR_DB), "--abx-stepped-ir", irs["anchor"])
    diag = json.loads((l4 / "ir" / "diagnostics_exact.json").read_text())
    ir = {k: wav.read_float32(p)[0] for k, p in irs.items()}
    _require(wav.read_float32(work / "unstepped.wav")[0].tobytes() == ir["exact"].tobytes(),
             "the anchor's unstepped IR is not the exact IR bit for bit")
    for k, p in irs.items():
        man["sha256"][f"ir/{k}.wav"] = abx_kit.sha256_file(p)
    sc = scene_asserts(timing, diag)
    man["scene"] = sc
    log(f"L4 scene S': T60 per band {', '.join(f'{t:.3f}' for t in sc['t60_s'])} s (T60_max {sc['T60_max_s']} s in "
        f"bands {sc['T60_max_bands']}); t_mix,e {sc['t_mix_e_s']} s; L_f {sc['L_f_s']} s, L_p {sc['L_p_s']} s, "
        f"L {sc['L_s']} s; provisional yes")
    log("L4 scene S': depth at L_f per band " + ", ".join(f"{d:.2f}" for d in sc["depth_at_L_f_db"])
        + " dB; at L_p " + ", ".join(f"{d:.2f}" for d in sc["depth_at_L_p_db"]) + " dB (>= 18.7 dB asserted)")

    # ---- IR checks P1-P6 ----
    p2 = p2_check(ir["provisional"], ir["exact"], diag)
    p3 = p3_check(ir["provisional"], timing, diag)
    p4 = p4_band_gains(ir["provisional"], ir["exact"], timing, diag)
    p5 = p5_fade_check(ir["provisional"], ir["exact"], timing, diag)
    p6 = p6_share(ir["exact"], timing, diag)
    n_d_anchor = first_difference(ir["anchor"], ir["exact"])
    man["ir_checks"] = {"P1": {"L_p_lt_L": timing["L_p_s"] < timing["L_s"], **timing}, "P2": p2, "P3": p3, "P4": p4,
                        "P5": p5, "P6": p6, "anchor_first_differing_tap": n_d_anchor}
    log(f"L4 P1: L_p {timing['L_p_s']} s < L {timing['L_s']} s; P2: bit-identical on [0, {p2['window_taps']}) taps "
        f"({p2['bit_identical']}), first differing tap {p2['first_differing_tap']}; P3: L_p tap {p3['L_p_tap']}, "
        f"last non-zero {p3['L_p_measured_taps']}, zero from L_p {p3['zero_from_L_p']}")
    for r in p4["rows"]:
        log(f"L4 P4' emitter {r['emitter']}: 20 log10 c_b " + ", ".join(_fmt(v, 3) for v in r["c_b_db"].values())
            + " dB (model f_b/f^_b " + ", ".join(_fmt(v, 3) for v in r["c_b_pred_db"].values()) + f" dB); |c_b| <= 1 dB")
    log(f"L4 P5': fade max deviation " + ", ".join(f"{r['fade_max_deviation']:.4f}" for r in p5["rows"])
        + f" (<= {FADE_TOL}; pre-fade method noise " + ", ".join(f"{r['pre_fade_max_deviation']:.4f}" for r in p5["rows"])
        + "); E ratio over the fade " + ", ".join(f"{r['energy_ratio']:.4f} (pred {r['energy_ratio_pred']:.4f})"
                                                for r in p5["rows"]))
    log("L4 P6: exact energy past L_f, share of tail per band "
        + ", ".join(f"{k} {v['of_tail']:.4f}" for k, v in p6.items()))
    _require(p2["ok"], f"P2 failed: {p2}")
    _require(p3["ok"], f"P3 failed: {p3}")
    _require(p4["ok"], f"P4' failed: worst |20 log10 c_b| {p4['worst_abs_db']:.3f} dB > {C_B_MAX_DB} dB")
    _require(p5["ok"], f"P5' failed: {p5['rows']}")
    _require(n_d_anchor >= p2["window_taps"], f"the anchor IR differs before t_mix,e,min - 2.5 ms (tap {n_d_anchor})")

    # ---- Level reference and the chord's gain ----
    ref = reference_level(binary, work)
    man["level_reference"] = ref
    free = free_decay_samples(max(v.shape[0] for v in ir.values()))
    raw, m = chord_signal(free)
    hold = slice(m["release_start"] - int(round(STEADY_S * FS)), m["release_start"])
    g0 = 0.1 / float(np.max(np.abs(raw)))
    probe_in = work / "probe_in.wav"
    write_wav(probe_in, signals.to_stereo(raw * g0), FS)
    yp = render(binary, scene_path, probe_in, work / "probe_out.wav")
    rms_p = math.sqrt(float(np.mean(yp[hold, 0].astype(np.float64) ** 2)))
    gain = g0 * ref["rms"] / rms_p
    x = (raw * gain).astype(np.float32).astype(np.float64)
    in_path = l4 / "chord_dry.wav"
    write_wav(in_path, signals.to_stereo(x), FS)
    man["sha256"]["chord_dry.wav"] = abx_kit.sha256_file(in_path)
    man["chord"] = {"version": L4_CHORD_VERSION, "seed": L4_CHORD_SEED, "notes": [list(n) for n in L4_NOTES],
                    "partials": len(chord_partials()), "partial_max_hz": PARTIAL_MAX_HZ,
                    "envelope_s": {"silence": SILENCE_S, "attack": ATTACK_S, "hold": HOLD_S, "release": RELEASE_S,
                                   "free_decay": free / FS},
                    "marks_samples": m, "gain": gain, "gain_db": 20 * math.log10(gain), "probe_gain": g0,
                    "input_peak_dbfs": 20 * math.log10(float(np.max(np.abs(x)))), "length_s": m["total"] / FS}

    # ---- The three arms ----
    raw_out = {k: render(binary, scene_path, in_path, work / f"{k}_out.wav", *a) for k, a in ARMS.items()}
    n = m["total"]
    for k, y in raw_out.items():
        _require(bool(np.all(y[n:] == 0.0)), f"{k}: the render is not zero past the stimulus end (trim would lose audio)")
    y = {k: v[:n] for k, v in raw_out.items()}
    rms_b = math.sqrt(float(np.mean(y["exact"][hold, 0].astype(np.float64) ** 2)))
    lvl = {"exact_steady_rms_dbfs": 20 * math.log10(rms_b), "reference_rms_dbfs": ref["rms_dbfs"],
           "difference_db": 20 * math.log10(rms_b / ref["rms"]), "tolerance_db": LEVEL_TOL_DB}
    lvl["ok"] = abs(lvl["difference_db"]) <= LEVEL_TOL_DB
    man["level"] = lvl
    log(f"L4 level: exact steady state {lvl['exact_steady_rms_dbfs']:.3f} dBFS, noise reference "
        f"{ref['rms_dbfs']:.3f} dBFS (difference {lvl['difference_db']:+.4f} dB); chord gain {man['chord']['gain_db']:.2f} "
        f"dB, input peak {man['chord']['input_peak_dbfs']:.2f} dBFS")
    _require(lvl["ok"], f"level: {lvl}")

    st: dict = {}
    for k in ARMS:
        st[f"S1_{k}"] = s1_check(y[k])
        st[f"S3_{k}"] = s3_check(x, raw_out[k], ir[k])
    st["S2_provisional"] = s2_check(x, y["provisional"], y["exact"], p2["first_differing_tap"])
    st["S2_anchor"] = s2_check(x, y["anchor"], y["exact"], n_d_anchor)
    hold_ms = float(np.mean(y["provisional"][hold, 0].astype(np.float64) ** 2))
    st["S4"] = s4_check(x, raw_out["provisional"], ir["provisional"], hold_ms, m)
    lf_al = timing["L_f_s"] - float(diag["alignmentShiftS"])
    st["prefix"] = prefix_check(y["provisional"], y["exact"], m["end"], lf_al)
    # the other readings of "release + L_f" (print only): L_f from emission; release = the start of the release
    st["prefix_readings"] = {"L_f_from_emission": prefix_check(y["provisional"], y["exact"], m["end"], timing["L_f_s"]),
                             "release_start": prefix_check(y["provisional"], y["exact"], m["release_start"], lf_al)}
    ab, bb = band_signals(y["provisional"]), band_signals(y["exact"])
    st["band_coverage"] = band_coverage(bb, m)
    st["S5"] = s5_hold(y["provisional"], y["exact"], ab, bb, m)
    st["after_cut"] = after_cut_levels(ab, bb, m, lf_al)
    st["S7"] = s7_handover(y["provisional"], ab, bb, m, n)
    man["stimulus_checks"] = st
    for k in ARMS:
        log(f"L4 S1 {k}: diotic {st[f'S1_{k}']['diotic']}, peak {st[f'S1_{k}']['peak_dbfs']:.2f} dBFS; S3 residual "
            f"{st[f'S3_{k}']['worst_db']:.1f} dB (margin {st[f'S3_{k}']['margin_db']:.1f} dB)")
    for k in ("S2_provisional", "S2_anchor"):
        s = st[k]
        log(f"L4 {k}: n_on {s['n_on']}, n_d {s['n_d']}, identical before {s['bound_sample']} ({s['identical_before_bound']}), "
            f"first difference {s['first_differing_sample']} (margin {s['margin_samples']} samples)")
    s4 = st["S4"]
    log(f"L4 S4: A zero from {s4['zero_from_sample']} ({s4['exactly_zero_from_bound']}; K_p {s4['K_p']}, L_p "
        f"{s4['L_p_measured_taps']} taps), partial block [{s4['true_end_sample']}, {s4['zero_from_sample']}) "
        f"{_fmt(s4['partial_block_db_re_hold'], 1)} dB re hold; free decay {s4['free_decay_s']:.3f} s >= {L_S} s")
    pc = st["prefix"]
    log(f"L4 prefix (Seat 1): {pc['value_db']:.3f} dB over [0, {pc['window_end_s']:.4f} s) (<= {PREFIX_LIMIT_DB:.2f} dB, "
        f"margin {pc['margin_db']:.3f} dB); other readings: L_f from emission "
        f"{st['prefix_readings']['L_f_from_emission']['value_db']:.3f} dB, release start "
        f"{st['prefix_readings']['release_start']['value_db']:.3f} dB (print only)")
    bc = st["band_coverage"]
    log("L4 band coverage (exact steady state, re strongest): "
        + ", ".join(f"{k} {v:+.1f}" for k, v in bc["re_strongest_db"].items()) + f" dB (63 Hz-4 kHz >= -20 dB)")
    log("L4 S5: A - B per band over the last 1 s of the hold "
        + ", ".join(f"{k} {v:+.3f}" for k, v in st["S5"]["per_band_db"].items())
        + f" dB; per partial rms {st['S5']['per_partial_rms_db']:.3f} dB, max {st['S5']['per_partial_max_abs_db']:.3f} dB")
    log("L4 after release + L_f (100 ms, re hold): B " + ", ".join(
        f"{k} {_fmt(v['B_db_re_hold'], 1)}" for k, v in st["after_cut"]["bands"].items()) + " dB; A " + ", ".join(
        f"{k} {_fmt(v['A_db_re_hold'], 1)}" for k, v in st["after_cut"]["bands"].items()) + " dB")
    grid = st["S7"]["grid_s_after_release"]
    picks = [i for i, d in enumerate(grid) if any(abs(d - t) < 1e-6 for t in (0.0, 1.0, 2.0, 3.0, 3.4, 3.5, 3.6, 4.0))]
    log("L4 S7 (would-be handover step, dB, 1 kHz): " + ", ".join(
        f"{grid[i]:.1f} s {_fmt(st['S7']['bands']['1000'][i], 2)}" for i in picks))
    failed = [f"S1 {k}: {st[f'S1_{k}']}" for k in ARMS if not st[f"S1_{k}"]["ok"]]
    failed += [f"S3 {k}: {st[f'S3_{k}']}" for k in ARMS if not st[f"S3_{k}"]["ok"]]
    failed += [f"{k}: {st[k]}" for k in ("S2_provisional", "S2_anchor", "S4") if not st[k]["ok"]]
    if not bc["ok"]:
        failed.append(f"band coverage (Seat 1): {bc['weakest_asserted']} Hz at "
                      f"{bc['re_strongest_db'][bc['weakest_asserted']]:.2f} dB re the strongest band "
                      f"({bc['strongest']} Hz) < -{COVERAGE_DB} dB; per band {bc['re_strongest_db']}")
    if not pc["ok"]:
        failed.append(f"Seat 1's prefix check: {pc['value_db']:.3f} dB > {PREFIX_LIMIT_DB:.2f} dB (stop: Seats 1 and 3)")
    _require(not failed, "; ".join(failed))

    # ---- Pack (only once every check passed) ----
    write_pack(l4, y, man)
    man["stimulus_length_s"] = n / FS
    shutil.rmtree(work)
    man["build_seconds"] = time.monotonic() - t_start
    (l4 / "manifest.json").write_text(json.dumps(man, indent=1, default=float, allow_nan=False))
    log(f"L4: every check passed; stimulus {n / FS:.3f} s; {len(man['blocks'][LEVEL_KEY])} trials, 2 familiarisation pairs; "
        f"built in {man['build_seconds']:.1f} s; {l4 / 'manifest.json'}")
    return man


def build(out: pathlib.Path, binary: pathlib.Path, log=print) -> dict:
    """Build, check and pack L4 into <out>/l4. On a failed check the record so far (every value computed, the
    failures) goes to <out>/l4/check_failed.json, nothing is packed, and CheckFailed is raised."""
    l4 = _prepare_out(out)
    man: dict = {}
    try:
        return _build(l4, man, binary, log)
    except CheckFailed as e:
        man["check_failed"] = str(e)
        (l4 / "check_failed.json").write_text(json.dumps(man, indent=1, default=float))
        raise


# ---------------------------------------------------------------------------------------------------------
# Scoring (decision item 5; Seat 1)
# ---------------------------------------------------------------------------------------------------------


def score_block_l4(key_block: list[dict], answers: dict[int, str], rerun: bool = False) -> dict:
    scored = [t for t in key_block if t["kind"] == "scored"]
    anchors = [t for t in key_block if t["kind"] == "anchor"]
    if len(scored) != L4_SCORED or len(anchors) != L4_ANCHORS:
        raise ValueError(f"an L4 block has {L4_SCORED} scored and {L4_ANCHORS} anchor trials")
    missing = [t["trial"] for t in key_block if t["trial"] not in answers]
    if missing:
        raise ValueError(f"L4: no answer for trials {missing}")
    k = sum(answers[t["trial"]] == t["X"] for t in scored)
    ka = sum(answers[t["trial"]] == t["X"] for t in anchors)
    if ka < L4_ANCHOR_PASS:
        verdict = "void"
        wording = (f"void: anchors {ka}/{L4_ANCHORS} < {L4_ANCHOR_PASS}/{L4_ANCHORS}; "
                   + ("void after its one rerun: no L4 result" if rerun else "the block gets one rerun"))
    elif k >= L4_CRITERION:
        verdict, wording = "detected", WORDING_DETECTED
    else:
        verdict, wording = "not detected", WORDING_NULL
    return {"chain": "l4", "k": k, "n": L4_SCORED, "p_exact": abx_kit.binom_tail(k, L4_SCORED), "anchor_k": ka,
            "anchor_n": L4_ANCHORS, "rerun": rerun, "verdict": verdict, "wording": wording}


def score_l4(key_path: pathlib.Path, responses: dict[int, str], rerun: bool = False) -> dict:
    """Seat 1's pass rule on the sealed key (abx_kit.seal's format, block "L4")."""
    key = json.loads(pathlib.Path(key_path).read_text())
    if key.get("chain") != "l4":
        raise ValueError(f"the key is for the {key.get('chain')} chain, not l4")
    return score_block_l4(key["blocks"][LEVEL_KEY], responses, rerun)


def read_responses_l4(path: pathlib.Path) -> dict[int, str]:
    """CSV with columns trial, answer (A or B); a level_db column, if present, must read L4."""
    out: dict[int, str] = {}
    with open(path, newline="") as f:
        for row in csv.DictReader(f):
            if "level_db" in row and row["level_db"].strip() not in ("", LEVEL_KEY):
                continue
            ans = row["answer"].strip().upper()
            if ans in ("A", "B"):
                out[int(row["trial"])] = ans
    return out


def blank_response_csv(path: pathlib.Path) -> None:
    with open(path, "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["level_db", "trial", "answer"])
        for t in trial_plan():
            w.writerow([LEVEL_KEY, t["trial"], ""])


# ---------------------------------------------------------------------------------------------------------


def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("build")
    p.add_argument("--out", type=pathlib.Path, default=REPO / "build" / "abx-07c-2b")
    p.add_argument("--render-cli", type=pathlib.Path, default=None)
    p = sub.add_parser("seal")
    p.add_argument("--pack", type=pathlib.Path, required=True)
    p.add_argument("--session", type=pathlib.Path, required=True)
    p.add_argument("--key", type=pathlib.Path, required=True)
    p = sub.add_parser("score")
    p.add_argument("--key", type=pathlib.Path, required=True)
    p.add_argument("--responses", type=pathlib.Path, required=True)
    p.add_argument("--session", type=pathlib.Path, default=None, help="the listener's folder; X.wav is checked")
    p.add_argument("--rerun", action="store_true", help="this block is the one rerun after a void block")
    p = sub.add_parser("blank")
    p.add_argument("--out", type=pathlib.Path, required=True)
    args = ap.parse_args(argv)
    if args.cmd == "build":
        binary = args.render_cli or render_cli.find_render_cli()
        if binary is None or not binary.is_file():
            print("ax49_l4.py: render_cli not found (cmake --preset cli && cmake --build --preset cli)", file=sys.stderr)
            return 1
        try:
            build(args.out, binary)
        except CheckFailed as e:
            print(f"ax49_l4.py: CHECK FAILED, the kit stops (returns to the board; never loosened): {e}",
                  file=sys.stderr)
            return 2
    elif args.cmd == "seal":
        record = abx_kit.seal(args.pack, args.session, args.key)
        print(json.dumps({"key_sha256": record["key_sha256"], "stimuli": len(record["stimuli_salted_sha256"])}, indent=1))
        print(f"commit {abx_kit.prereg_path(args.key)} before the run; keep {args.key} unseen until scoring")
    elif args.cmd == "score":
        if args.session is not None:
            abx_kit.verify_session(args.key, args.session)
        print(json.dumps(score_l4(args.key, read_responses_l4(args.responses), args.rerun)))
    elif args.cmd == "blank":
        blank_response_csv(args.out)
    return 0


if __name__ == "__main__":
    sys.exit(main())
