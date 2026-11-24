"""Phase-07c-2 D-W2: the AX47 self-ABX kit (tools/ci/abx_kit.py) and render_cli --abx-step-db.

- The pre-registered numbers in the kit are file 13's (D-W2 items 2, 3, 5, 9, 13; Q5).
- src/plugin never reaches the validation-only step flag (item 5).
- The trial plan has the pre-registered structure (items 2, 7); scoring follows items 3, 4 and 13, and refuses to
  unseal a 0.5 dB block unless 0.9 dB was detected in that chain (item 11).
- Item 6's prints (decider files 27, 31): the exact split N = (a u - s)/(a - 1) behind `window_unscaled_share`,
  render_cli's `target_specular_share` parsed under its own name, and the heard-pair tail share, Delta G and Delta C80.
- M2 (files 31, 34): Seat 9's T30 label, the tail T30 beside it, and the minimum gap >= tail T30 assertion.
- End to end (render_cli needed; skipped without it unless SPATIAL_REQUIRE_RENDER_CLI=1): one noise trial with every
  item-6 assertion, and g = 0 bit-identical to no flag.
"""

from __future__ import annotations

import csv
import os
import pathlib
import sys

import pytest

# The contract-tools job installs only tools/ci/requirements.txt; numpy comes with the acoustics requirements
# (python job), where this module runs.
np = pytest.importorskip("numpy")

REPO = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))

from tools.ci import abx_kit  # noqa: E402


def test_preregistered_numbers() -> None:
    # phase-07c-2b M3-2 (decider file 6): noise 24 scored + 6 anchors, break after 15; speech per R3
    assert abx_kit.SCORED_TRIALS == {"noise": 24, "speech": 24}
    assert (abx_kit.ANCHOR_TRIALS, abx_kit.ANCHOR_DB, abx_kit.ANCHOR_PASS) == (6, 3.0, 5)
    assert abx_kit.BLOCK_TRIALS == {"noise": 30, "speech": 30}
    assert abx_kit.BREAK_AFTER == {"noise": 15, "speech": 15}
    assert abx_kit.LEVELS_DB == (0.9, 0.5)
    assert abx_kit.CRITERION == {"noise": 18, "speech": 18}
    # per family: 2 x P(>= 18 of 24) = 2 x 190051/2^24 (M3-2, decider file 9)
    p = 2 * abx_kit.binom_tail(18, 24)
    assert abs(p - 0.022656) < 5e-7 and abs(abx_kit.FAMILY_ALPHA - p) < 5e-7
    assert abs(abx_kit.binom_tail(18, 24, 0.75) - 0.607) < 5e-4
    assert (abx_kit.FS, abx_kit.PARTITION, abx_kit.CROSSFADE_S) == (48000, 512, 0.030)
    assert abx_kit.W_CANDIDATES == (6, 7, 8)
    assert (abx_kit.Q5_ONSET_MAX_T30, abx_kit.Q5_MARGIN_DB, abx_kit.Q5_BAND_HZ, abx_kit.Q5_WINDOW_S) == (0.43, 20.0, 1000.0, 0.05)
    assert abx_kit.POST_STEP_S == 2.0
    assert abx_kit.S_W_MAX == 0.023  # file 34 item 1
    assert abx_kit.C80_S == 0.080  # Vorlaender Eq. 6.7 (file 29)
    assert abx_kit.HEARD_T30_LABEL == "heard-IR T30, ISO fit spanning the AX21 gap, not a decay rate"  # Seat 9, M2


def test_exact_unscaled_split() -> None:
    # K3's split (file 25, method 5b): IR = N + T, stepped = N + a T; N = (a u - s)/(a - 1) exactly, whatever the
    # overlap of N and T (the inferred print it replaces carried the cross term 2<N, T>).
    rng = np.random.default_rng(1)
    n, tail = rng.standard_normal(4000) * 0.1, rng.standard_normal(4000)
    for g in (-3.0, -0.9, 0.5, 0.9, 3.0):
        a = 10 ** (g / 20)
        assert np.allclose(abx_kit.unscaled_part(n + tail, n + a * tail, g), n, rtol=0, atol=1e-12)


def test_parse_target_specular_share() -> None:
    out = ("abx step: emitter 0 g 0.9 dB; specular share of E_target per band: 0 0.1 0.2 0.3 0.4 0.5 0.6 0.7\n"
           "abx step: emitter 1 g 0.9 dB; specular share of E_target per band: 0 0 0 0 0 0 0 0\n"
           "abx step: emitter 0 tail-energy change set per band (dB): 0.9 0.9 0.9 0.9 0.9 0.9 0.9 0.9\n")
    assert abx_kit.parse_target_specular_share(out) == {0: [0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7], 1: [0.0] * 8}


def test_heard_pair_metrics_synthetic() -> None:
    # A direct impulse at 10 ms and a decaying tail from 300 ms in emitter L (channel 0); emitter R (channel 2) silent.
    # Only the tail scales, and it lies wholly in C80's late window: Delta C80 = -g, Delta G = 10 log10(1 + share
    # (a^2 - 1)), share = E(tail)/E(heard).
    fs, g = 48000, 0.9
    a = 10 ** (g / 20)
    t = np.arange(fs) / fs
    tail = np.where(t >= 0.3, np.random.default_rng(2).standard_normal(fs) * np.exp(-(t - 0.3) * 6.9) * 0.05, 0.0)
    u = np.zeros((fs, 4))
    u[480, 0] = 1.0
    s = u.copy()
    u[:, 0] += tail
    s[:, 0] += a * tail
    m = abx_kit.heard_pair_metrics(u, s, fs, g)
    bb = m["broadband"]
    share = np.sum(tail**2) / np.sum(u[:, 0] ** 2)
    assert m["onset_tap"] == 480
    assert abs(bb["tail_share_of_heard"] - share) <= 1e-12
    assert abs(bb["delta_G_db"] - 10 * np.log10(1 + share * (a * a - 1))) <= 1e-9
    assert abs(bb["delta_C80_db"] + g) <= 1e-9
    assert abs(m["bands"]["1000"]["delta_C80_db"] + g) <= 1e-6
    assert set(m["bands"]) == {"63", "125", "250", "500", "1000", "2000", "4000", "8000"}


def test_m2_gap_check() -> None:
    # File 34 item 3: minimum gap, heard-IR T30 (labelled) and tail T30 printed; minimum gap >= tail T30 asserted.
    scene = {"T30_1k_s": 2.009, "tail_T30_1k_s": [1.254, 1.274]}
    rec = abx_kit.gap_check(scene, 2.016, 2.009)
    assert rec == {"min_gap_s": 2.016, "heard_T30_1k_s": 2.009, "heard_T30_label": abx_kit.HEARD_T30_LABEL,
                   "tail_T30_1k_s": [1.254, 1.274], "min_gap_ge_tail_T30": True}
    # layout 5 (K4 fact 9): heard 2.557 s against tail-alone 2.58-2.62 s fails
    with pytest.raises(AssertionError):
        abx_kit.gap_check({"T30_1k_s": 2.557, "tail_T30_1k_s": [2.58, 2.62]}, 2.560, 2.557)
    with pytest.raises(RuntimeError):
        abx_kit.gap_check({"T30_1k_s": 2.0, "tail_T30_1k_s": [None, 1.2]}, 2.1, 2.0)


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
    n = abx_kit.SCORED_TRIALS[chain]
    brk = abx_kit.BREAK_AFTER[chain]
    assert len(plan) == n + 6
    scored = [t for t in plan if t["kind"] == "scored"]
    anchors = [t for t in plan if t["kind"] == "anchor"]
    assert len(scored) == n and len(anchors) == 6
    assert sorted(t["g_db"] for t in scored) == [-level] * (n // 2) + [level] * (n // 2)
    assert all(abs(t["g_db"]) == 3.0 for t in anchors)
    assert [t["trial"] for t in plan if t["break_after"]] == [brk]
    if True:  # M3-2 (Seat 1): 3 anchors on each side of the break, both chains
        assert sum(t["trial"] <= brk for t in anchors) == 3
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
    # M3-2 (decider file 9): 18/24 detects in the speech chain, 17/24 does not
    r = abx_kit.score(key, {"0.9": _answers(key, "0.9", 6, 0)}, "speech")
    assert r[0]["verdict"] == "detected" and r[0]["k"] == 18
    assert r[0]["wording"] == "detected (>= 18/24, family alpha 0.022656)"
    r = abx_kit.score(key, {"0.9": _answers(key, "0.9", 7, 0)}, "speech")
    assert r[0]["verdict"] == "not detected"
    assert r[0]["wording"] == "not detected in 24 trials by one listener (power 0.61 at p = 0.75)"
    # the 0.5 dB block is refused unless 0.9 dB was detected (item 11)
    with pytest.raises(PermissionError):
        abx_kit.score(key, {"0.9": _answers(key, "0.9", 7, 0), "0.5": _answers(key, "0.5", 0, 0)}, "speech")
    r = abx_kit.score(key, {"0.9": _answers(key, "0.9", 0, 0), "0.5": _answers(key, "0.5", 0, 0)}, "speech")
    assert [x["level_db"] for x in r] == [0.9, 0.5]
    # a failed anchor (4/6) makes the block inconclusive, never "not detected" (item 4)
    r = abx_kit.score(key, {"0.9": _answers(key, "0.9", 10, 2)}, "speech")
    assert r[0]["verdict"] == "inconclusive" and r[0]["anchor_k"] == 4
    # noise (M3-2): 18/24 detects, 17/24 does not; null wording names 24 trials and power 0.61
    nkey = _fake_key(tmp_path, "noise")
    assert abx_kit.score(nkey, {"0.9": _answers(nkey, "0.9", 6, 1)}, "noise")[0]["verdict"] == "detected"
    r = abx_kit.score(nkey, {"0.9": _answers(nkey, "0.9", 7, 1)}, "noise")
    assert r[0]["verdict"] == "not detected" and r[0]["k"] == 17
    assert r[0]["wording"] == "not detected in 24 trials by one listener (power 0.61 at p = 0.75)"


def test_blank_response_sheet(tmp_path: pathlib.Path) -> None:
    path = tmp_path / "r.csv"
    abx_kit.blank_response_csv(path, "noise")
    rows = list(csv.DictReader(open(path, newline="")))
    assert len(rows) == 60 and {r["level_db"] for r in rows} == {"0.9", "0.5"}


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
    # M2 (files 31, 34): Seat 9's label on the heard-IR T30, the tail T30 beside it, the gap check passed on S-A
    assert sc["T30_1k_s_label"] == abx_kit.HEARD_T30_LABEL
    assert sc["label"] == abx_kit.scene_label(sc["name"])  # M3-4: the manifest carries the decided item-9 label
    assert "tail_spread" in sc and not sc["tail_spread"]["exceeds_1db"]  # M3-1 (a): printed at every seal
    assert sc["tail_T30_1k_s"] == [e["tail_T30_1k_s"] for e in em]
    gc = m["m2_gap_check"]
    assert gc["heard_T30_1k_s"] == sc["T30_1k_s"] and gc["heard_T30_label"] == abx_kit.HEARD_T30_LABEL
    assert gc["min_gap_s"] >= sc["T30_1k_s"] and gc["min_gap_s"] >= max(gc["tail_T30_1k_s"]) and gc["min_gap_ge_tail_T30"]
    keys = {"63", "125", "250", "500", "1000", "2000", "4000", "8000"}
    for g, rec in m["ir_checks"].items():
        gd = float(g)
        a = 10 ** (gd / 20)
        for row in rec["rows"]:
            assert abs(row["tail_alone"]["step_db"] - gd) <= 0.01
            # item 6 print fix (file 27): the exact split, not the inferred specular_share; s_w <= 2.3 % (file 34)
            assert "specular_share" not in row["ax47_window"]
            assert 0.0 <= row["ax47_window"]["window_unscaled_share"] <= abx_kit.S_W_MAX
            assert row["ax47_window"]["window_unscaled_share"] < 1e-9  # S-A: no images in the window (K3, K4)
        for br in rec["bands"]:
            assert br["window_unscaled_share_broadband"] < 1e-9 and set(br["bands"]) == keys
            for b in br["bands"].values():
                assert b["window_unscaled_share"] < 1e-9
                assert b["target_specular_share"] == 0.0  # render_cli's own print; 0 on layout4_s1/default
        # Seat 1's condition (file 27): per band and broadband on the heard pair; S-A's 1 kHz values are K4's (file 29)
        h = rec["heard"]
        assert set(h["bands"]) == keys
        for x in (h["broadband"], *h["bands"].values()):
            assert abs(x["delta_G_db"] - 10 * np.log10(1 + x["tail_share_of_heard"] * (a * a - 1))) <= 1e-6
            assert abs(x["delta_C80_db"] + gd) <= 0.01  # [0, 80 ms) holds only the direct sound (63 Hz rings most)
        for x in (h["broadband"], h["bands"]["1000"]):
            assert abs(x["delta_C80_db"] + gd) <= 1e-6
        assert round(h["bands"]["1000"]["tail_share_of_heard"], 3) == 0.046
    for level, block in m["blocks"].items():
        (t,) = block
        assert t["midfade"]["windows"] > 0
        a, _ = wav.read_float32(tmp_path / "noise" / f"{level}dB" / "trial_01" / "A.wav")
        b, _ = wav.read_float32(tmp_path / "noise" / f"{level}dB" / "trial_01" / "B.wav")
        s0 = t["onset_sample"]
        assert np.array_equal(a[:s0], b[:s0]) and not np.array_equal(a, b)
    # seal: X is A or B, the key outside the session, the hashes recorded
    rec = abx_kit.seal(tmp_path / "noise", tmp_path / "session", tmp_path / "key.json", key_seed=5)
    import json

    digests = rec["stimuli_salted_sha256"]
    assert len(digests) == 3 * len(m["blocks"]) and len(rec["key_sha256"]) == 64
    assert json.loads(abx_kit.prereg_path(tmp_path / "key.json").read_text()) == rec
    # the committed record must not reveal X (D-W2 item 11): no committed digest equals another, none equals a
    # stimulus's plain SHA-256, and the listener's folder holds only A, B and X
    sess = tmp_path / "session"
    files = sorted(p.relative_to(sess).as_posix() for p in sess.rglob("*") if p.is_file())
    assert files == sorted(digests) and all(f.endswith(("/A.wav", "/B.wav", "/X.wav")) for f in files)
    assert len(set(digests.values())) == len(digests)
    assert not {abx_kit.sha256_file(sess / f) for f in files} & set(digests.values())
    # scoring checks the folder against the record; a swapped X is refused
    abx_kit.verify_session(tmp_path / "key.json", sess)
    key = json.loads((tmp_path / "key.json").read_text())
    x_file = next(f for f in files if f.endswith("/X.wav"))
    level, trial = x_file.split("dB/")[0], int(x_file.split("trial_")[1][:2])
    (x_rec,) = [t for t in key["blocks"][level] if t["trial"] == trial]
    swapped = "B" if x_rec["X"] == "A" else "A"
    (sess / x_file).write_bytes((sess / x_file).with_name(f"{swapped}.wav").read_bytes())
    with pytest.raises(ValueError):
        abx_kit.verify_session(tmp_path / "key.json", sess)
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


# ---- phase-07c-2b M3-3: HF-W, the asserted click gate, with its negative controls N1-N3 ----

def _fade_triple(seed: int = 7, n: int = 48000, s0: int = 24064):
    """a, b: two different noise renders (float32, 2 channels, diotic); o: the AQ4 linear crossfade a -> b over
    [s0, s0 + L), a before, b after (what render_cli's step produces, companions (ii), (iii))."""
    rng = np.random.default_rng(seed)
    env = np.exp(-np.arange(n) / 9000.0)
    a1 = (0.1 * rng.standard_normal(n) * env).astype(np.float32)
    b1 = (0.1 * 1.1 * rng.standard_normal(n) * env).astype(np.float32)
    L = int(round(abx_kit.CROSSFADE_S * abx_kit.FS))
    j = np.arange(L, dtype=np.float64)
    o1 = np.concatenate([a1[:s0], ((1 - j / L) * a1[s0 : s0 + L] + (j / L) * b1[s0 : s0 + L]).astype(np.float32),
                         b1[s0 + L :]])
    two = lambda x: np.stack([x, x], axis=1)  # noqa: E731
    return two(o1), two(a1), two(b1), s0, L


def test_hfw_beta_is_the_derived_bound() -> None:
    # (1 + 96/1440)^2 (1 + 1e-5) = 1.1378 at 48 kHz, 0.561 dB (decider file 2, D-L8)
    assert abs(abx_kit.hfw_beta(48000) - 1.1378) < 5e-5
    assert abs(10 * np.log10(abx_kit.hfw_beta(48000)) - 0.561) < 5e-4


def test_hfw_passes_the_clean_crossfade() -> None:
    o, a, b, s0, _ = _fade_triple()
    rec = abx_kit.hf_w_check(o, a, b, s0, abx_kit.FS)
    assert rec["frames"] > 0 and rec["worst_ratio"] <= rec["beta"]
    abx_kit.midfade_checks(o, a, b, s0, abx_kit.FS)  # the companions pass too (non-vacuity pair, Seat 5)


def test_hfw_n1_spike_fails() -> None:
    # N1: a single-sample spike at s0 + L/2, sized so that its frame's E_o is 3 dB over beta max(E_a, E_b)
    o, a, b, s0, L = _fade_triple()
    fs, t = abx_kit.FS, s0 + L // 2
    nf = int(round(abx_kit.HFW_FRAME_S * fs))
    f0 = s0 + ((t - s0) // nf) * nf
    beta = abx_kit.hfw_beta(fs)

    def frame_ratio(amp: float) -> float:
        x = o[:, 0].astype(np.float64).copy()
        x[t] += amp
        h = [abx_kit.clicks.highpass(y, fs)[f0 : f0 + nf] for y in (x, a[:, 0].astype(np.float64), b[:, 0].astype(np.float64))]
        return float(np.sum(h[0] ** 2) / max(np.sum(h[1] ** 2), np.sum(h[2] ** 2)))

    lo, hi = 0.0, 1.0
    for _ in range(60):  # bisection: the amplitude whose frame ratio is 2 beta (3 dB over the bound)
        mid = 0.5 * (lo + hi)
        lo, hi = (mid, hi) if frame_ratio(mid) < 2 * beta else (lo, mid)
    spiked = o.copy()
    spiked[t, :] += np.float32(hi)
    assert abs(10 * np.log10(frame_ratio(hi) / beta) - 3.0) < 0.05
    with pytest.raises(AssertionError, match="HF-W"):
        abx_kit.hf_w_check(spiked, a, b, s0, fs)


def test_hfw_n2_hard_switch_fails_companion_ii() -> None:
    # N2: the linear fade replaced by a hard switch at s0 + L/2; companion (ii) must fail
    o, a, b, s0, L = _fade_triple()
    sw = o.copy()
    sw[s0 : s0 + L // 2] = a[s0 : s0 + L // 2]
    sw[s0 + L // 2 : s0 + L] = b[s0 + L // 2 : s0 + L]
    with pytest.raises(AssertionError, match="companion \\(ii\\)"):
        abx_kit.midfade_checks(sw, a, b, s0, abx_kit.FS)


def test_hfw_n3_quantised_fade_fails_companion_ii() -> None:
    # N3: the fade quantised in 32-sample steps; companion (ii) must fail
    o, a, b, s0, L = _fade_triple()
    jq = (np.arange(L) // 32 * 32).astype(np.float64)
    q = o.copy()
    seg = ((1 - jq / L)[:, None] * a[s0 : s0 + L].astype(np.float64) + (jq / L)[:, None] * b[s0 : s0 + L].astype(np.float64))
    q[s0 : s0 + L] = seg.astype(np.float32)
    with pytest.raises(AssertionError, match="companion \\(ii\\)"):
        abx_kit.midfade_checks(q, a, b, s0, abx_kit.FS)


def test_hfw_spike_in_a_skipped_frame_fails() -> None:
    # Seat 5's condition D: a click in a near-silent (skipped) frame still fails HF-W
    o, a, b, s0, L = _fade_triple()
    nf = int(round(abx_kit.HFW_FRAME_S * abx_kit.FS))
    t = s0 + L // 2
    f0 = s0 + ((t - s0) // nf) * nf
    for x in (o, a, b):
        x[f0 - 400 : f0 + nf + 400] = 0.0  # a silent stretch around the frame (all three renders)
    rec = abx_kit.hf_w_check(o, a, b, s0, abx_kit.FS)
    assert rec["skipped"] >= 2  # the silent frame is skipped on both channels, and passes
    o[t, :] += np.float32(0.01)
    with pytest.raises(AssertionError, match="skipped frame"):
        abx_kit.hf_w_check(o, a, b, s0, abx_kit.FS)


def test_abx_scene_labels_are_the_decided_texts() -> None:
    # phase-07c-2b M3-4 (decider file 6): the two ABX scenes, their labels, and no superseded wording
    assert abx_kit.ABX_SCENES == ("layout4_s1/both_wall", "layout4_s0.7/default")
    for name in abx_kit.ABX_SCENES:
        label = abx_kit.scene_label(name)
        assert label.startswith(name + ": 20 × 30 × 10 m, 6,000 m³")
        assert "indicative only: ᾱ ≈ 0.28 is not small, Kuttruff §5.6" in label
        assert label.endswith("Not a validated preset.")
        assert "hall" not in label.lower() and "occupied" not in label.lower()
    assert "represents no seat" in abx_kit.scene_label("layout4_s1/both_wall")
    assert "partial AX21" in abx_kit.scene_label("layout4_s0.7/default")
    with pytest.raises(RuntimeError, match="no item-9 label"):
        abx_kit.scene_label("layout4_s1/both_corner")  # a fallback is labelled only once Seat 9 confirms its text


def test_kit_labels_equal_the_run_sheet_texts() -> None:
    # M3-4 (steward round 4, G13): each ABX scene's kit label (the manifest's scene.label) equals, word for word, the
    # decided item-9 text the /fix-plan wrote into the run sheet §1 (line breaks and quote markers flattened)
    import re

    sheet = (REPO / "docs" / "validation" / "abx-07c-2-run-sheet.md").read_text(encoding="utf-8")
    flat = re.sub(r"\s*\n\s*(>\s*)?", " ", sheet)
    for name in abx_kit.ABX_SCENES:
        assert abx_kit.scene_label(name) in flat, name
