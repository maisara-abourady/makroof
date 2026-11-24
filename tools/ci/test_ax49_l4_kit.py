"""Phase-07c-2b M3-L4: the AX49 L4 stimulus kit (tools/ci/ax49_l4.py).

Decider file 6 (M3-7 / M3-L4) items 1-8; Seat 1 (file 4-seat1: chord, pass rule, prefix check), Seat 2 (file 4-seat2:
scene S', seal asserts), Seat 3 (files 4-seat3 and 8-seat3: P1-P6, S1-S7, N-L1-N-L3).
- Pinned numbers: alpha 2517/65536, the chord (notes, seed, version, envelope), the criterion and anchors, the
  scene, the limits.
- The trial plan, the pack layout abx_kit.seal reads unchanged, and Seat 1's scoring rule with its wordings.
- Negative controls (render_cli needed; skipped without it unless SPATIAL_REQUIRE_RENDER_CLI=1):
  N-L1: a hard cut at L_f (and no fade at all) fails P5'; N-L2: a provisional built with another tailSeed fails P2 or
  the prefix check; N-L3: a written IR that differs from the rendered one fails S3; N-L4 (decider file 13): the chord
  limited to <= 500 Hz fails coverage (a) and (b).
- End to end: the full build on S' passes every check; the original 63 Hz-4 kHz clause still reads -22.94 dB, red.
"""

from __future__ import annotations

import csv
import json
import math
import os
import pathlib
import sys

import pytest

np = pytest.importorskip("numpy")
pytest.importorskip("scipy")

REPO = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))

from tools.ci import abx_kit, ax49_l4 as k  # noqa: E402


# ---------------------------------------------------------------------------------------------------------
# Pinned numbers
# ---------------------------------------------------------------------------------------------------------


def test_pinned_numbers() -> None:
    # decision item 5 (Seat 1): >= 12/16, alpha 2517/65536 = 0.0384, power 0.630 at p = 0.75
    assert (k.L4_SCORED, k.L4_ANCHORS, k.L4_BLOCK, k.L4_BREAK_AFTER) == (16, 6, 22, 11)
    assert (k.L4_CRITERION, k.L4_ANCHOR_PASS, k.L4_ANCHOR_DB) == (12, 5, -3.0)
    assert k.L4_ALPHA == 2517 / 65536 == abx_kit.binom_tail(12, 16)
    assert abs(abx_kit.binom_tail(12, 16, 0.75) - 0.630) < 5e-4 and k.L4_POWER == 0.63
    assert k.WORDING_DETECTED == ("detected: AX49's Reversal fires (worst case: provisional current through the "
                                  "whole free decay)")
    # decider file 21 (L4-COV revised): Seat 9's null wording, verbatim
    assert k.WORDING_NULL == (
        "not detected in 16 trials by one listener (power 0.63); ax49_l4_cube, T60 8.0 s at 63 Hz–1 kHz and 6.5 s at "
        "2 kHz, held chord, omni diotic; cut exposed at 63 Hz–2 kHz; no claim at 4 kHz and above, where this scene's "
        "tail (T60 3.7 s, mostly air absorption in 10⁶ m³) has by L_f decayed 40 dB from its own onset, against 19 dB "
        "at 63 Hz–1 kHz.")
    # decision item 3 (Seat 1's chord, verbatim)
    assert k.L4_NOTES == (("C2", 65.406), ("G2", 97.999), ("C3", 130.813), ("E3", 164.814), ("G3", 195.998))
    assert (k.L4_CHORD_VERSION, k.L4_CHORD_SEED, k.PARTIAL_MAX_HZ) == ("l4-chord-v1", 4901, 5000.0)
    assert (k.SILENCE_S, k.ATTACK_S, k.HOLD_S, k.RELEASE_S) == (0.5, 0.020, 4.0, 0.010)
    # L4-COV E: (a) and (b) over 63 Hz-2 kHz within 20 dB; the original 63 Hz-4 kHz clause printed; 4k/8k printed
    assert k.COVERAGE_BANDS_HZ == (63.0, 125.0, 250.0, 500.0, 1000.0, 2000.0) and k.COVERAGE_DB == 20.0
    assert k.ORIGINAL_COVERAGE_BANDS_HZ == (*k.COVERAGE_BANDS_HZ, 4000.0) and k.PRINTED_BANDS_HZ == (4000.0, 8000.0)
    assert k.CUT_WINDOW_S == 0.100
    assert k.LEVEL_TOL_DB == 1.0 and k.MAX_PEAK_DBFS == -1.0
    # decision item 4: Seat 1's prefix limit = 20 log10(10^(1/20) - 1) (AX47 (b)); h = 0.1 s; Phase 06's -120 dB
    assert abs(k.PREFIX_LIMIT_DB - (-18.27)) < 5e-3 and k.PREFIX_H_S == 0.1 and k.NULL_LIMIT_DB == -120.0
    # decision item 2 (Seat 2): S'
    assert (k.DIMENSIONS_M, k.SCATTERING, k.LISTENER, k.EMITTERS) == (
        (100.0, 100.0, 100.0), 0.3, (50.0, 30.0, 1.7), ((45.0, 70.0, 2.0), (55.0, 70.0, 2.0)))
    assert len(k.ABSORPTION) == 8 and len(set(k.ABSORPTION[4:])) == 1  # above 1 kHz: the 1 kHz value
    assert (k.T60_TARGET_S, k.T60_TOL_S, k.L_S, k.LP_MAX_S, k.DEPTH_MIN_DB) == (8.0, 0.1, 12.0, 3.82, 18.7)
    assert k.TAIL_SEED == abx_kit.TAIL_SEED  # item 1: the kit's fixed tailSeed
    assert (k.FS, k.PARTITION, k.BLOCK) == (48000, 512, 512)
    # Seat 9's final label (14-seat9 section 3): two fields, {printed} and {seed}
    filled = k.LABEL_TEMPLATE.format(printed="\u22128.5", seed=12345)
    for w in k.FORBIDDEN_LABEL_WORDS:
        assert w not in filled.lower()
    assert k.LABEL_TEMPLATE.count("{") == 2 and "one tailSeed 12345 for A and B" in filled
    assert "not a room prediction or a validated preset" in filled and "no dry path" in filled


def test_scene() -> None:
    s = k.make_l4_scene()
    assert s["room"]["geometry"]["dimensions"] == [100.0, 100.0, 100.0]
    assert all(f["absorption"] == list(k.ABSORPTION) and f["scattering"] == 0.3
               for f in s["room"]["surfaces"].values()) and len(s["room"]["surfaces"]) == 6
    assert s["listener"]["position"] == [50.0, 30.0, 1.7]
    assert [e["position"] for e in s["emitters"]] == [[45.0, 70.0, 2.0], [55.0, 70.0, 2.0]]
    assert s["render"]["tailSeed"] == 12345


def test_chord() -> None:
    parts = k.chord_partials()
    assert parts == k.chord_partials()  # deterministic
    assert all(p["f_hz"] <= 5000.0 and abs(p["amp"] - 1 / p["k"]) < 1e-15 for p in parts)
    for name, f0 in k.L4_NOTES:  # every harmonic up to 5 kHz, none above
        ks = [p["k"] for p in parts if p["note"] == name]
        assert ks == list(range(1, len(ks) + 1)) and (len(ks) + 1) * f0 > 5000.0
    # the phases are pinned by the seed and version (default_rng(4901), drawn note by note)
    assert [round(p["phase"], 9) for p in parts[:3]] == [
        round(float(v), 9) for v in np.random.default_rng(4901).uniform(0, 2 * math.pi, size=76)[:3]]
    x, m = k.chord_signal(48000)
    assert (m["onset"], m["hold_start"], m["release_start"], m["end"]) == (24000, 24960, 216960, 217440)
    assert not np.any(x[: m["onset"]]) and not np.any(x[m["end"] :]) and x.size == m["end"] + 48000
    assert x[m["onset"]] != 0.0 and x[m["end"] - 1] != 0.0
    # raised-cosine attack and release: the hold is the full chord, the edges rise and fall monotonically in envelope
    env = k._rc(960)
    assert np.all(np.diff(env) > 0) and env[0] > 0 and env[-1] < 1
    # the free decay: >= L and >= IR + two partitions; the stimulus ends on a partition boundary
    for ir_len in (1000, 570391, 700000):
        f = k.free_decay_samples(ir_len)
        assert f >= 12 * 48000 and f >= ir_len + 1024 and (m["end"] + f) % 512 == 0


def test_trial_plan() -> None:
    plan = k.trial_plan()
    assert plan == k.trial_plan() and len(plan) == 22
    scored = [t for t in plan if t["kind"] == "scored"]
    anchors = [t for t in plan if t["kind"] == "anchor"]
    assert len(scored) == 16 and len(anchors) == 6
    assert all(t["A"] == "provisional" and t["B"] == "exact" and t["g_db"] is None for t in scored)
    assert all(t["A"] == "anchor" and t["B"] == "exact" and t["g_db"] == -3.0 for t in anchors)
    assert [t["trial"] for t in plan if t["break_after"]] == [11]


def test_prescale_and_readback(tmp_path: pathlib.Path) -> None:
    # R3: a power-of-two pre-scale to a peak < 1.0, undone exactly; R2: every WAV the kit writes reads back bit-equal
    x = np.sin(np.arange(4800) * 0.01) * 1.42
    xp, s = k.prescale(x)
    assert s == 1 and np.max(np.abs(xp)) < 1.0 and np.array_equal(xp * 2.0, x)
    y = (xp[:, None] * np.ones(2)).astype(np.float32)
    assert np.array_equal(k.undo_prescale(y, s), (x[:, None] * np.ones(2)).astype(np.float32))
    assert k.prescale(x * 0.5)[1] == 0
    k.write_wav(tmp_path / "a.wav", y)
    k.write_wav(tmp_path / "b.wav", y)
    assert (tmp_path / "a.wav").read_bytes() == (tmp_path / "b.wav").read_bytes()  # byte-deterministic


# ---------------------------------------------------------------------------------------------------------
# Scoring and the pack (no render_cli)
# ---------------------------------------------------------------------------------------------------------


def _key_block(xs: list[str] | None = None) -> list[dict]:
    plan = k.trial_plan()
    xs = xs or ["A" if i % 2 else "B" for i in range(len(plan))]
    return [{"trial": t["trial"], "kind": t["kind"], "g_db": t["g_db"], "X": x} for t, x in zip(plan, xs)]


def _answers(block: list[dict], scored_right: int, anchors_right: int) -> dict[int, str]:
    flip = {"A": "B", "B": "A"}
    out, s, a = {}, 0, 0
    for t in block:
        if t["kind"] == "scored":
            out[t["trial"]] = t["X"] if s < scored_right else flip[t["X"]]
            s += 1
        else:
            out[t["trial"]] = t["X"] if a < anchors_right else flip[t["X"]]
            a += 1
    return out


def test_scoring_rule() -> None:
    block = _key_block()
    r = k.score_block_l4(block, _answers(block, 12, 5))
    assert (r["verdict"], r["wording"], r["k"], r["anchor_k"]) == ("detected", k.WORDING_DETECTED, 12, 5)
    assert abs(r["p_exact"] - 2517 / 65536) < 1e-15
    r = k.score_block_l4(block, _answers(block, 11, 6))
    assert (r["verdict"], r["wording"]) == ("not detected", k.WORDING_NULL)
    r = k.score_block_l4(block, _answers(block, 16, 4))  # anchors 4/6: void whatever the score
    assert r["verdict"] == "void" and "one rerun" in r["wording"] and "inaudible" not in r["wording"]
    r = k.score_block_l4(block, _answers(block, 16, 4), rerun=True)
    assert r["verdict"] == "void" and "no L4 result" in r["wording"]
    with pytest.raises(ValueError):
        k.score_block_l4(block, {1: "A"})
    for v in (k.WORDING_DETECTED, k.WORDING_NULL):
        assert "inaudible" not in v


def test_pack_seal_score_round_trip(tmp_path: pathlib.Path) -> None:
    # the pack abx_kit.seal reads unchanged; a seal, a verified session and a scored CSV
    l4 = tmp_path / "pack" / "l4"
    l4.mkdir(parents=True)
    stim = {name: np.full((64, 2), 0.01 * (i + 1), dtype=np.float32) for i, name in enumerate(k.ARMS)}
    man = {"chain": "l4", "sha256": {}}
    k.write_pack(l4, stim, man)
    (l4 / "manifest.json").write_text(json.dumps(man))
    assert sorted(p.name for p in (l4 / "L4dB").iterdir()) == [f"trial_{i:02d}" for i in range(1, 23)]
    for t in man["blocks"]["L4"]:
        d = l4 / "L4dB" / f"trial_{t['trial']:02d}"
        assert (d / "A.wav").read_bytes() == (l4 / "stimuli" / f"{t['A']}.wav").read_bytes()
        assert (d / "B.wav").read_bytes() == (l4 / "stimuli" / "exact.wav").read_bytes()
    assert {p.name for p in (l4 / "familiarisation").iterdir()} == {"pair_01_provisional_vs_exact",
                                                                    "pair_02_anchor_vs_exact"}
    session, key = tmp_path / "session", tmp_path / "key.json"
    record = abx_kit.seal(l4, session, key, key_seed=5)
    assert len(record["stimuli_salted_sha256"]) == 22 * 3
    abx_kit.verify_session(key, session)
    block = json.loads(key.read_text())["blocks"]["L4"]
    csv_path = tmp_path / "responses.csv"
    k.blank_response_csv(csv_path)
    rows = list(csv.DictReader(open(csv_path)))
    assert len(rows) == 22 and {r["level_db"] for r in rows} == {"L4"}
    with open(csv_path, "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["level_db", "trial", "answer"])
        for t in block:
            w.writerow(["L4", t["trial"], t["X"]])
    r = k.score_l4(key, k.read_responses_l4(csv_path))
    assert (r["verdict"], r["k"], r["anchor_k"]) == ("detected", 16, 6)
    assert k.main(["score", "--key", str(key), "--responses", str(csv_path), "--session", str(session)]) == 0


# ---------------------------------------------------------------------------------------------------------
# Negative controls (render_cli)
# ---------------------------------------------------------------------------------------------------------


@pytest.fixture(scope="module")
def binary() -> pathlib.Path:
    from tools.acoustics import render_cli

    b = render_cli.find_render_cli()
    if b is None:
        if os.environ.get("SPATIAL_REQUIRE_RENDER_CLI") == "1":
            pytest.fail("render_cli not found and SPATIAL_REQUIRE_RENDER_CLI=1")
        pytest.skip("render_cli not built")
    return b


def _irs(binary: pathlib.Path, d: pathlib.Path, prov_seed: int = k.TAIL_SEED) -> dict:
    from tools.acoustics import wav

    d.mkdir(parents=True, exist_ok=True)
    exact_scene, prov_scene = d / "exact.json", d / f"prov_{prov_seed}.json"
    exact_scene.write_text(json.dumps(k.make_l4_scene()))
    prov_scene.write_text(json.dumps(k.make_l4_scene(prov_seed)))
    so = abx_kit._run(binary, "--scene", prov_scene, "--mode", "omni", "--ax49-provisional", "--ir", d / "p.wav")
    abx_kit._run(binary, "--scene", exact_scene, "--mode", "omni", "--ir", d / "x.wav", "--diagnostics", d / "dx.json")
    return {"timing": k.parse_timing(so), "diag": json.loads((d / "dx.json").read_text()),
            "prov": wav.read_float32(d / "p.wav")[0], "exact": wav.read_float32(d / "x.wav")[0],
            "exact_scene": exact_scene, "prov_scene": prov_scene}


@pytest.fixture(scope="module")
def clean(binary: pathlib.Path, tmp_path_factory) -> dict:
    return _irs(binary, tmp_path_factory.mktemp("clean"))


def test_clean_ir_checks(clean: dict) -> None:
    # positive control: the clean provisional passes P2, P3, P4', P5' on S'
    t, diag = clean["timing"], clean["diag"]
    assert k.scene_asserts(t, diag)["provisional"]
    assert k.p2_check(clean["prov"], clean["exact"], diag)["ok"]
    assert k.p3_check(clean["prov"], t, diag)["ok"]
    assert k.p5_fade_check(clean["prov"], clean["exact"], t, diag)["ok"]


def test_nl1_hard_cut_fails_the_fade_check(clean: dict) -> None:
    # N-L1 (Seat 3): a hard cut at L_f must fail P5' (the windowed gains drop to 0, and the fade's energy ratio is
    # the hard-cut value 0, not strictly between it and no fade); so must a provisional with no fade at all
    t, diag = clean["timing"], clean["diag"]
    lf, lp = k.tap(t["L_f_s"], diag), k.tap(t["L_p_s"], diag)
    cut = clean["prov"].copy()
    cut[lf:] = 0.0
    r = k.p5_fade_check(cut, clean["exact"], t, diag)
    assert not r["ok"] and all(not row["strictly_between"] and row["fade_max_deviation"] > 0.5 for row in r["rows"])
    nofade = k._pad(clean["prov"].copy(), clean["exact"].shape[0])
    for c in range(nofade.shape[1]):
        cg = k._ls_gain(nofade[lf - 24000 : lf, c].astype(np.float64), clean["exact"][lf - 24000 : lf, c].astype(np.float64))
        nofade[lf:lp, c] = (cg * clean["exact"][lf:lp, c]).astype(np.float32)
    r = k.p5_fade_check(nofade, clean["exact"], t, diag)
    assert not r["ok"] and all(row["fade_max_deviation"] > 0.5 for row in r["rows"])


def _offline_arms(x: np.ndarray, ir: np.ndarray) -> np.ndarray:
    from scipy import signal as sps

    y = np.stack([sps.fftconvolve(x, ir[:, c].astype(np.float64) + ir[:, 2 + c].astype(np.float64)) for c in range(2)],
                 axis=1)
    return y[: x.size]


def test_nl2_other_seed_fails_p2_or_prefix(binary: pathlib.Path, clean: dict, tmp_path: pathlib.Path) -> None:
    # N-L2 (Seat 3; decision item 4): a provisional built with a different tailSeed must fail P2 or Seat 1's prefix
    # check (here on float64 convolutions of the chord, the check's own arithmetic); the clean one passes both
    other = _irs(binary, tmp_path, prov_seed=k.TAIL_SEED + 1)
    t, diag = clean["timing"], clean["diag"]
    x, m = k.chord_signal(k.free_decay_samples(clean["exact"].shape[0]))
    lf_al = t["L_f_s"] - float(diag["alignmentShiftS"])
    b = _offline_arms(x, clean["exact"])
    good = k.prefix_check(_offline_arms(x, clean["prov"]), b, m["end"], lf_al)
    assert good["ok"] and k.p2_check(clean["prov"], clean["exact"], diag)["ok"], good
    p2 = k.p2_check(other["prov"], clean["exact"], diag)
    bad = k.prefix_check(_offline_arms(x, other["prov"]), b, m["end"], lf_al)
    assert not (p2["ok"] and bad["ok"]), (p2, bad)
    assert not bad["ok"]  # the tail is another realisation: the difference is of the tail's own order


def test_nl3_written_ir_must_be_the_rendered_one(binary: pathlib.Path, clean: dict, tmp_path: pathlib.Path) -> None:
    # N-L3 (Seat 3): S3 passes for the IR the flag wrote and fails for any other (the exact IR; one tap changed)
    from tools.acoustics import signals, wav

    x, m = k.chord_signal(k.free_decay_samples(clean["prov"].shape[0]))
    x = (x * 0.05).astype(np.float32).astype(np.float64)
    inp = tmp_path / "in.wav"
    wav.write_float32(inp, signals.to_stereo(x), k.FS)
    y = k.render(binary, clean["prov_scene"], inp, tmp_path / "a.wav", "--ax49-provisional")
    assert k.s3_check(x, y, clean["prov"])["ok"]
    assert not k.s3_check(x, y, clean["exact"])["ok"]
    # one tap changed: the strongest (the direct sound) by 1e-4 relative. S3's floor is -120 dB of the render's
    # energy, so a change below it (a 1 % change of one late tail tap is about -132 dB here) passes by design.
    j = int(np.argmax(np.abs(clean["prov"][:, 0])))
    bent = clean["prov"].copy()
    bent[j, :] *= np.float32(1.0001)
    r = k.s3_check(x, y, bent)
    assert not r["ok"], r


def test_nl4_dull_chord_fails_coverage(clean: dict) -> None:
    # N-L4 (decider file 13): the same chord with partials limited to <= 500 Hz fails both (a) and (b); the built
    # chord passes both (float64 convolutions of the exact IR, the checks' own arithmetic)
    t, diag = clean["timing"], clean["diag"]
    lf_al = t["L_f_s"] - float(diag["alignmentShiftS"])
    free = k.free_decay_samples(clean["exact"].shape[0])
    for limit, ok in ((k.PARTIAL_MAX_HZ, True), (500.0, False)):
        x, m = k.chord_signal(free, limit)
        bc = k.band_coverage(k.band_signals(_offline_arms(x, clean["exact"])), m, lf_al)
        assert bc["a_steady_state"]["ok"] is ok and bc["b_cut_window"]["ok"] is ok, (limit, bc)


# ---------------------------------------------------------------------------------------------------------
# End to end
# ---------------------------------------------------------------------------------------------------------

def test_full_build(binary: pathlib.Path, tmp_path: pathlib.Path) -> None:
    lines: list[str] = []
    man = k.build(tmp_path, binary, log=lines.append)
    l4 = tmp_path / "l4"
    assert (l4 / "manifest.json").exists() and len(man["blocks"]["L4"]) == 22
    assert man["stimulus_length_s"] >= 16.53  # L4-L4
    bc = man["stimulus_checks"]["band_coverage"]
    assert bc["a_steady_state"]["ok"] and bc["b_cut_window"]["ok"]
    bm = bc["b_cut_window_vs_median"]  # decider file 21: printed beside the asserted form, never asserted
    assert set(bm["re_median_db"]) >= set(bc["b_cut_window"]["bands"]) and "print only" in bm["reference"]
    # decider file 13: Seat 1's original clause (63 Hz-4 kHz) still reads -22.94 dB, red, on this deterministic build
    orig = bc["original_clause_63_4k"]
    assert not orig["ok"] and orig["weakest"] == "4000" and round(orig["weakest_db"], 2) == -22.94
    assert man["label"] == k.LABEL_TEMPLATE.format(printed=man["label_fill"]["printed"], seed=12345)
    assert man["input_scaling"]["chord_s"] == 1 and man["input_scaling"]["chord_prescaled_peak_dbfs"] < 0.0
    for rel, digest in man["sha256"].items():
        assert abx_kit.sha256_file(l4 / rel) == digest, rel
