"""Phase-07c-2 D-W2: the AX47 self-ABX kit (tools/ci/abx_kit.py) and render_cli --abx-step-db.

- The pre-registered numbers in the kit are file 13's (D-W2 items 2, 3, 5, 9, 13; Q5).
- src/plugin never reaches the validation-only step flag (item 5).
- The trial plan has the pre-registered structure (items 2, 7); scoring follows items 3, 4 and 13, and refuses to
  unseal a 0.5 dB block unless 0.9 dB was detected in that chain (item 11).
- End to end (render_cli needed; skipped without it unless SPATIAL_REQUIRE_RENDER_CLI=1): one noise trial with every
  item-6 assertion, and g = 0 bit-identical to no flag.
"""

from __future__ import annotations

import csv
import os
import pathlib
import sys

import numpy as np
import pytest

REPO = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))

from tools.ci import abx_kit  # noqa: E402


def test_preregistered_numbers() -> None:
    assert abx_kit.SCORED_TRIALS == 16
    assert (abx_kit.ANCHOR_TRIALS, abx_kit.ANCHOR_DB, abx_kit.ANCHOR_PASS) == (6, 3.0, 5)
    assert (abx_kit.BLOCK_TRIALS, abx_kit.BREAK_AFTER) == (22, 11)
    assert abx_kit.LEVELS_DB == (0.9, 0.5)
    assert abx_kit.CRITERION == {"noise": 12, "speech": 13}
    assert abx_kit.FAMILY_ALPHA == 0.049
    assert (abx_kit.FS, abx_kit.PARTITION, abx_kit.CROSSFADE_S) == (48000, 512, 0.030)
    assert abx_kit.W_CANDIDATES == (6, 7, 8)
    assert (abx_kit.Q5_ONSET_MAX_T30, abx_kit.Q5_MARGIN_DB, abx_kit.Q5_BAND_HZ, abx_kit.Q5_WINDOW_S) == (0.43, 20.0, 1000.0, 0.05)
    assert abx_kit.POST_STEP_S == 2.0


def test_family_error_and_power() -> None:
    # Item 3: FWER <= 0.0490 by the union bound over the two chains' first tests (the 0.5 dB tests inherit alpha
    # only after a detection, graphical procedure); power at p = 0.75 is 0.63 (noise) and 0.405 (speech).
    a_noise, a_speech = abx_kit.binom_tail(12, 16), abx_kit.binom_tail(13, 16)
    assert round(a_noise + a_speech, 4) == 0.0490  # 0.03841 + 0.01064 = 0.04904, as file 13 rounds it
    assert round(abx_kit.binom_tail(12, 16, 0.75), 2) == 0.63
    assert round(abx_kit.binom_tail(13, 16, 0.75), 3) == 0.405


def test_plugin_never_reaches_the_step_flag() -> None:
    for path in (REPO / "src" / "plugin").rglob("*"):
        if path.suffix not in (".h", ".hpp", ".cpp", ".txt", ".cmake"):
            continue
        text = path.read_text(encoding="utf-8", errors="replace")
        assert "abx" not in text.lower(), f"{path} names the ABX step"
        assert '#include "cli/' not in text, f"{path} includes src/cli"
        assert "spatial_cli" not in text and "spatial::cli" not in text, f"{path} links src/cli"
    step_users = [p for p in (REPO / "src").rglob("*.cpp") if "abxStepDb" in p.read_text(encoding="utf-8", errors="replace")]
    assert step_users == [REPO / "src" / "cli" / "Cli.cpp"]


@pytest.mark.parametrize("chain", ["noise", "speech"])
@pytest.mark.parametrize("level", abx_kit.LEVELS_DB)
def test_trial_plan(chain: str, level: float) -> None:
    plan = abx_kit.trial_plan(chain, level)
    assert len(plan) == 22
    scored = [t for t in plan if t["kind"] == "scored"]
    anchors = [t for t in plan if t["kind"] == "anchor"]
    assert len(scored) == 16 and len(anchors) == 6
    assert sorted(t["g_db"] for t in scored) == [-level] * 8 + [level] * 8
    assert all(abs(t["g_db"]) == 3.0 for t in anchors)
    assert [t["trial"] for t in plan if t["break_after"]] == [11]
    assert plan == abx_kit.trial_plan(chain, level)  # seeded, reproducible


def _fake_key(tmp_path: pathlib.Path, chain: str) -> pathlib.Path:
    import json

    key = {"chain": chain, "seed": 1, "blocks": {}}
    for level in abx_kit.LEVELS_DB:
        key["blocks"][f"{level:.1f}"] = [{"trial": t["trial"], "kind": t["kind"], "g_db": t["g_db"], "X": "A" if t["trial"] % 2 else "B"}
                                          for t in abx_kit.trial_plan(chain, level)]
    path = tmp_path / "key.json"
    path.write_text(json.dumps(key))
    return path


def _answers(key_path: pathlib.Path, level: str, wrong_scored: int, wrong_anchor: int) -> dict[int, str]:
    import json

    block = json.loads(key_path.read_text())["blocks"][level]
    out, ws, wa = {}, wrong_scored, wrong_anchor
    for t in block:
        flip = False
        if t["kind"] == "scored" and ws > 0:
            flip, ws = True, ws - 1
        if t["kind"] == "anchor" and wa > 0:
            flip, wa = True, wa - 1
        out[t["trial"]] = ("B" if t["X"] == "A" else "A") if flip else t["X"]
    return out


def test_scoring_rules(tmp_path: pathlib.Path) -> None:
    key = _fake_key(tmp_path, "speech")
    # 13/16 detects in the speech chain, 12/16 does not (item 3)
    r = abx_kit.score(key, {"0.9": _answers(key, "0.9", 3, 0)}, "speech")
    assert r[0]["verdict"] == "detected" and r[0]["k"] == 13
    assert r[0]["wording"] == "detected (>= 13/16, family alpha 0.049)"
    r = abx_kit.score(key, {"0.9": _answers(key, "0.9", 4, 0)}, "speech")
    assert r[0]["verdict"] == "not detected"
    assert r[0]["wording"] == "not detected in 16 trials by one listener (power 0.41 at p = 0.75)"
    # the 0.5 dB block is refused unless 0.9 dB was detected (item 11)
    with pytest.raises(PermissionError):
        abx_kit.score(key, {"0.9": _answers(key, "0.9", 4, 0), "0.5": _answers(key, "0.5", 0, 0)}, "speech")
    r = abx_kit.score(key, {"0.9": _answers(key, "0.9", 0, 0), "0.5": _answers(key, "0.5", 0, 0)}, "speech")
    assert [x["level_db"] for x in r] == [0.9, 0.5]
    # a failed anchor (4/6) makes the block inconclusive, never "not detected" (item 4)
    r = abx_kit.score(key, {"0.9": _answers(key, "0.9", 10, 2)}, "speech")
    assert r[0]["verdict"] == "inconclusive" and r[0]["anchor_k"] == 4
    # noise: 12/16 detects
    nkey = _fake_key(tmp_path, "noise")
    assert abx_kit.score(nkey, {"0.9": _answers(nkey, "0.9", 4, 1)}, "noise")[0]["verdict"] == "detected"


def test_blank_response_sheet(tmp_path: pathlib.Path) -> None:
    path = tmp_path / "r.csv"
    abx_kit.blank_response_csv(path, "noise")
    rows = list(csv.DictReader(open(path, newline="")))
    assert len(rows) == 44 and {r["level_db"] for r in rows} == {"0.9", "0.5"}


def _binary() -> pathlib.Path | None:
    from tools.acoustics import render_cli

    b = render_cli.find_render_cli()
    if b is None and os.environ.get("SPATIAL_REQUIRE_RENDER_CLI") == "1":
        pytest.fail("render_cli not found and SPATIAL_REQUIRE_RENDER_CLI=1")
    return b


def test_q5_window_record() -> None:
    # Decider file 21, 2a and interrogator file 23: the realised window and the replacement rate. N = 81 boundaries,
    # K = 35 passing: the first draw is replaced with p = 46/81, and 46/36 onsets per stimulus are replaced on average.
    b = [1000 + 512 * i for i in range(81)]
    passing = b[:34] + [b[35]]
    rec = abx_kit.q5_window_record(b, passing, eos=1000, t30_samples=512 * 100.0)
    assert rec["q5_first_draw_replaced_p"] == 46 / 81
    assert rec["q5_expected_replaced_per_stimulus"] == 46 / 36
    assert rec["q5_realised_window_T30"] == [0.0, 0.35]
    assert rec["q5_passing_contiguous_from_first"] is False
    assert rec["q5_passing_boundary_indices"] == list(range(34)) + [35]
    # Monte Carlo of the kit's draw (a seeded permutation, the first passing one taken): failures before it.
    rng = np.random.default_rng(3)
    ok = np.zeros(81, bool)
    ok[rec["q5_passing_boundary_indices"]] = True
    fails = [int(np.argmax(ok[rng.permutation(81)])) for _ in range(20000)]
    assert abs(np.mean(fails) - 46 / 36) < 0.05


def test_noise_trial_end_to_end(tmp_path: pathlib.Path) -> None:
    binary = _binary()
    if binary is None:
        pytest.skip("render_cli not built")
    from tools.acoustics import wav

    m = abx_kit.build_noise_chain(tmp_path / "noise", binary, log=lambda *_: None, trials=1)
    sc = m["scene"]
    assert all(all(v) for v in sc["capped"].values())
    # Decider file 21, 2b (file 22): D/R per emitter, on that emitter's own IR, beside the heard (L + R) one. At equal
    # r the two direct sounds add coherently and the uncorrelated tails do not: the heard D/R is about 3 dB higher.
    # The tail alone decays at the diffuse target's T60; the whole-IR T30 reads longer (AX21 empty early part).
    em = sc["emitters"]
    assert len(em) == 2 and abs(em[0]["r_m"] - em[1]["r_m"]) < 1e-9
    per_emitter = 10 * np.log10(np.mean([10 ** (e["DRR_dB_1k"] / 10) for e in em]))
    assert 2.0 <= sc["DRR_dB_1k"] - per_emitter <= 4.0, (sc["DRR_dB_1k"], [e["DRR_dB_1k"] for e in em])
    for e in em:
        assert abs(e["tail_T30_1k_s"] / e["target_T60_1k_s"] - 1.0) <= 0.10, e
        assert e["T30_1k_s"] > 1.3 * e["tail_T30_1k_s"], e
    for g, rec in m["ir_checks"].items():
        for row in rec["rows"]:
            assert abs(row["tail_alone"]["step_db"] - float(g)) <= 0.01
    for level, block in m["blocks"].items():
        (t,) = block
        assert t["midfade"]["windows"] > 0
        a, _ = wav.read_float32(tmp_path / "noise" / f"{level}dB" / "trial_01" / "A.wav")
        b, _ = wav.read_float32(tmp_path / "noise" / f"{level}dB" / "trial_01" / "B.wav")
        s0 = t["onset_sample"]
        assert np.array_equal(a[:s0], b[:s0]) and not np.array_equal(a, b)
    # seal: X is A or B, the key outside the session, the hashes recorded
    rec = abx_kit.seal(tmp_path / "noise", tmp_path / "session", tmp_path / "key.json", key_seed=5)
    assert len(rec["stimuli_sha256"]) == 3 * len(m["blocks"]) and len(rec["key_sha256"]) == 64
    with pytest.raises(ValueError):
        abx_kit.seal(tmp_path / "noise", tmp_path / "session", tmp_path / "session" / "key.json")


def test_zero_step_is_bit_identical(tmp_path: pathlib.Path) -> None:
    binary = _binary()
    if binary is None:
        pytest.skip("render_cli not built")
    from tools.acoustics import render_cli, signals, wav
    import json

    scene = tmp_path / "scene.json"
    scene.write_text(json.dumps(abx_kit.scene_layout4_s1_default()))
    x = np.zeros(48000 * 2)
    x[:24000] = signals.pink_noise(24000, 3) * 0.1
    inp = tmp_path / "in.wav"
    wav.write_float32(inp, signals.to_stereo(x), 48000)
    common = ["--scene", scene, "--mode", "omni", "--in", inp, "--realtime-emulation", "--block", "512", "--partition", "512"]
    assert render_cli.run(binary, *common, "--out", tmp_path / "plain.wav").returncode == 0
    assert render_cli.run(binary, *common, "--out", tmp_path / "zero.wav", "--abx-step-db", "0",
                          "--abx-step-sample", "25088").returncode == 0
    assert (tmp_path / "plain.wav").read_bytes() == (tmp_path / "zero.wav").read_bytes()
