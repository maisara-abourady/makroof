"""Phase-07c-2 D-W2: the AX47 self-ABX kit (tools/ci/abx_kit.py) and render_cli --abx-step-db.

- The pre-registered numbers in the kit are file 13's (D-W2 items 2, 3, 5, 9, 13; Q5).
- src/plugin never reaches the validation-only step flag (item 5).
- The trial plan has the pre-registered structure (items 2, 7); scoring follows items 3, 4 and 13, and refuses to
  unseal a 0.5 dB block unless 0.9 dB was detected in that chain (item 11).
- Item 6's prints (decider files 27, 31): the exact split N = (a u - s)/(a - 1) behind `window_unscaled_share`,
  render_cli's `target_specular_share` parsed under its own name, and the heard-pair tail share, Delta G and Delta C80.
- M2 (files 31, 34) under M3-G (phase-07c-2b decider file 8): Seat 9's T30 label, the tail T30 beside it, gaps built
  from T = max(heard, every tail T30), and the minimum heard gap >= T and >= every tail T30.
- Phase-07c-2b M3: the scene registry (E, the fallbacks D and B, S-A; E's committed JSON), the Class-line refusal
  (D-M3e), M1's per-band step identity at <= 0.05 dB, the offline reference for the nulls, the speech layout.
- End to end (render_cli needed; skipped without it unless SPATIAL_REQUIRE_RENDER_CLI=1): one noise trial per block on
  E with every item-6 assertion and the M3-C 7 nulls, and g = 0 bit-identical to no flag.
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
    # File 34 item 3 under M3-G (phase-07c-2b decider file 8): the construction T is max(heard-IR T30, every tail T30);
    # the minimum heard gap or silence is asserted >= T and >= every tail T30.
    scene = {"T30_1k_s": 2.009, "tail_T30_1k_s": [1.254, 1.274]}
    rec = abx_kit.gap_check(scene, 2.016, 2.009)
    assert rec == {"min_gap_s": 2.016, "construction_T_s": 2.009,
                   "construction_rule": "max(heard-IR T30, every tail T30) at 1 kHz (decider file 8, M3-G)",
                   "heard_T30_1k_s": 2.009, "heard_T30_label": abx_kit.HEARD_T30_LABEL,
                   "tail_T30_1k_s": [1.254, 1.274], "min_gap_ge_tail_T30": True, "min_gap_ge_construction_T": True}
    # E (builder file 4): heard 2.560 s below the tail's 2.600 s; T = 2.600 s, heard gap 2.603 s passes
    e = {"T30_1k_s": 2.560, "tail_T30_1k_s": [2.582, 2.600]}
    assert abx_kit.gap_check(e, 2.603, 2.600)["construction_T_s"] == 2.600
    # red: gaps built from the heard T30 (the old M2 T-a rule) are refused on layout 5
    with pytest.raises(AssertionError):
        abx_kit.gap_check(e, 2.603, 2.560)
    # red: a heard gap shorter than a tail T30 (K7 fact 7: 2.574 s against 2.600 s)
    with pytest.raises(AssertionError):
        abx_kit.gap_check(e, 2.574, 2.600)
    with pytest.raises(RuntimeError):
        abx_kit.gap_check({"T30_1k_s": 2.0, "tail_T30_1k_s": [None, 1.2]}, 2.1, 2.0)


def test_scene_registry() -> None:
    """Decider file 8, M3-S: E is the default scene, D and B the fallbacks in order, S-A stays registered. E's JSON is
    committed beside the kit, equals the builder, and is the scene builder file 4 measured (its SHA-256)."""
    import hashlib
    import json

    assert abx_kit.DEFAULT_SCENE == "layout5_s0.9/emitter_wall"
    assert abx_kit.FALLBACK_ORDER == ("layout5_s0.9/emitter_wall", "layout5_s0.8/emitter_wall", "layout5_s0.8/default")
    assert set(abx_kit.SCENES) == {*abx_kit.FALLBACK_ORDER, "layout4_s1/default"}
    e = abx_kit.SCENES[abx_kit.DEFAULT_SCENE]
    assert e.committed == REPO / "tools" / "ci" / "abx_scenes" / "layout5_s0.9_emitter_wall.json"
    assert e.committed.read_text(encoding="utf-8") == e.text()
    assert hashlib.sha256(e.committed.read_bytes()).hexdigest() == \
        "95d46224756e27edf5c587308ba3b4cb20dd3fd86ebbba65d32d08090778a7a6"  # build/k7/layout5_s0.9__emitter_wall
    s = json.loads(e.committed.read_text())
    assert s["room"]["geometry"]["dimensions"] == [20.0, 30.0, 10.0]
    for face, surf in s["room"]["surfaces"].items():
        assert surf == {"absorption": [1.0 if face == "xMin" else 0.01] * 8, "scattering": 0.9}, face
    assert s["render"]["tailSeed"] == 12345 and s["listener"]["position"] == [10.0, 8.0, 1.7]
    assert [x["position"] for x in s["emitters"]] == [[7.0, 29.9, 2.0], [13.0, 20.0, 2.0]]
    for name, entry in abx_kit.SCENES.items():
        assert entry.name == name
        assert abx_kit.require_class_line(entry).startswith("Class: ")  # D-M3e
        assert "hall" not in entry.label.lower()
    # labels (M3-S; decider file 10 Part B's ITDG line; M3-C 5's case-4 line on S-A)
    assert e.label == ("Tail-dominated stress placement, one absorbing side wall, source 0.1 m from a wall, "
                       "specular-only early reflections (s 0.9, AX21); not a validated preset")
    assert "Class: tail-dominated (heard −9.5 dB, tail share 0.85), partial early part" in e.label_detail
    assert any(x.startswith("ITDG 0.6 ms (S0's wall image, notch ≈ 860 Hz), 0.89 ms (S0's floor image") for x in e.label_detail)
    assert "Gaps are built from max(heard, tail) T30." in e.label_detail
    assert ("Kuttruff Table 5.2 case 4 (floor α 1, others 0): iteration 1.21 s against Eyring 1.38 s; the engine's "
            "tail follows Eyring.") in abx_kit.SCENES["layout4_s1/default"].label_detail


def test_class_line_required(tmp_path: pathlib.Path) -> None:
    """D-M3e: the kit refuses to build a manifest for a scene whose label has no Class line, before rendering."""
    entry = abx_kit.AbxScene("no_class/x", abx_kit.scene_layout4_s1_default, "label",
                             ("Stimulus scene, not a room prediction.",))
    scene = tmp_path / "scene.json"
    scene.write_text(entry.text())
    with pytest.raises(RuntimeError, match="Class"):
        abx_kit.check_scene(tmp_path / "no_render_cli", scene, tmp_path, entry=entry)
    abx_kit.SCENES["no_class/x"] = entry
    try:
        with pytest.raises(RuntimeError, match="Class"):
            abx_kit.prepare_scene(tmp_path / "out", tmp_path / "no_render_cli", "no_class/x")
    finally:
        del abx_kit.SCENES["no_class/x"]
    with pytest.raises(ValueError):
        abx_kit.prepare_scene(tmp_path / "out", tmp_path / "no_render_cli", "not/registered")


def test_band_step_check() -> None:
    """M3-C 7 (Seat 3): M1's per-band step identity asserted at <= 0.05 dB, per emitter and band; red at 0.06 dB."""
    assert abx_kit.BAND_STEP_TOL_DB == 0.05
    rows = [{"emitter": e, "bands": {k: {"step_db": 0.9 + 1e-3} for k in ("63", "1000")}} for e in (0, 1)]
    rec = abx_kit.band_step_check(rows, 0.9)
    assert abs(rec["max_abs_err_db"] - 1e-3) < 1e-12
    rows[1]["bands"]["1000"]["step_db"] = 0.9 - 0.06
    with pytest.raises(AssertionError, match="per-band step"):
        abx_kit.band_step_check(rows, 0.9)


def test_offline_reference_and_null() -> None:
    """M3-C 7's offline reference (renderOffline emulated, builder file 4 fact 5) is the direct convolution
    out_o = sum_e x_e * ir(e, o); the null is its energy ratio; the lengths must match."""
    rng = np.random.default_rng(5)
    prog = rng.standard_normal((300, 2)).astype(np.float32)
    ir = rng.standard_normal((40, 4)).astype(np.float32)
    ref = abx_kit.offline_reference(prog, ir)
    for o in range(2):
        direct = sum(np.convolve(prog[:, e].astype(np.float64), ir[:, 2 * e + o].astype(np.float64)) for e in range(2))
        assert np.allclose(ref[:, o], direct, rtol=1e-5, atol=1e-5)
    assert abx_kit.null_db(ref, ref) <= -300
    assert abs(abx_kit.null_db(ref * np.float32(1.1), ref) - 20 * np.log10(0.1)) < 1e-3
    with pytest.raises(AssertionError):
        abx_kit.null_db(ref[:-1], ref)
    assert abx_kit.NULL_MAX_DB == -120.0


def test_speech_layout_e() -> None:
    """M3-G (decider file 8, restated in file 10 Part B): sentence 2 at the input end of sentence 1 +
    ceil((0.43 T_heard + T) fs) + Delta; on E (T_heard 2.560 s, T 2.600 s, Delta 1363) the pause is 3.729 s; the heard
    pause and the heard silence after every onset are >= T; onsets at or after the heard end of sentence 1."""
    t_h, t, delays = 2.5597945976385454, 2.600119578366251, [1395, 32]
    lay = abx_kit.speech_layout(150000, 150000, 140000, t_h, t, delays)
    assert lay["pause"] == int(np.ceil((0.43 * t_h + t) * 48000)) + 1363 == 179003
    assert lay["heard_pause"] == lay["pause"] - 1363 >= t * 48000
    assert lay["heard_silence_after_latest_onset"] >= t * 48000
    assert lay["boundaries"][0] >= lay["s1_end"] + max(delays) and lay["boundaries"][0] % abx_kit.PARTITION == 0
    assert lay["boundaries"][-1] <= lay["eos"] + 0.43 * t_h * 48000  # Q5's ceiling stays 0.43 x heard T30
    # red: no boundary when the heard end of sentence 1 lies past the Q5 ceiling
    with pytest.raises(AssertionError, match="no partition boundary"):
        abx_kit.speech_layout(150000, 150000, 40000, t_h, t, delays)


def _synthetic_step(fs: int = 48000, g_db: float = 0.9, seed: int = 3):
    """A noise 'unstepped' render a, its stepped twin b = a * 10^(g/20), and o = the exact AQ4 crossfade from a to
    b at s0 (float32, two identical outputs), as render_cli's step writes it (companions (ii), (iii))."""
    rng = np.random.default_rng(seed)
    n, s0 = fs, fs // 2
    a = (0.05 * rng.standard_normal(n)).astype(np.float32)
    b = (a.astype(np.float64) * 10 ** (g_db / 20)).astype(np.float32)
    L = int(round(abx_kit.CROSSFADE_S * fs))
    j = np.arange(L, dtype=np.float64)
    o = a.astype(np.float64).copy()
    o[s0 : s0 + L] = (1 - j / L) * a[s0 : s0 + L] + (j / L) * b[s0 : s0 + L]
    o[s0 + L :] = b[s0 + L :]
    two = lambda x: np.stack([x, x], axis=1).astype(np.float32)  # noqa: E731
    return two(o), two(a), two(b), s0, L


def test_click_check_form_b_green_on_a_crossfade() -> None:
    """M3 (phase-07c-2b; Seats 3 and 5): the residual against the crossfade model is at the float32 floor on an
    exact crossfade of noise, where the old peak-frame comparison was blind or flaky (builder file 32, K5)."""
    o, a, b, s0, _ = _synthetic_step()
    rec = abx_kit.click_check(o, a, b, s0, 48000)
    assert rec["events_in_step_region"] == 0
    assert rec["residual_peak_dbfs"] < -110.0, rec
    # deterministic (CLAUDE.md, Determinism)
    assert rec == abx_kit.click_check(o, a, b, s0, 48000)


@pytest.mark.parametrize("plant", ["hard_switch", "impulse"])
def test_click_check_form_b_red_on_a_planted_transient(plant: str) -> None:
    """The gate is shown red (the "N1 red asserted" precedent): a hard switch at s0 (L = 0) and a single-sample
    impulse of -65 dBFS inside [s0, s0 + L) are both caught on noise. The measured floor of the check is a
    single-sample spike of about -69.8 dBFS (-69.8 dBFS derived; the asserted bracket, caught at -68 and missed at -72, is test_click_check_form_b_spike_bracket)."""
    o, a, b, s0, L = _synthetic_step()
    o = o.copy()
    if plant == "hard_switch":
        o[s0:] = b[s0:]
    else:
        o[s0 + L // 3] += np.float32(10 ** (-65 / 20))
    with pytest.raises(AssertionError, match="click_check"):
        abx_kit.click_check(o, a, b, s0, 48000)


@pytest.mark.parametrize("where", ["mid_frame", "frame_boundary"])
def test_click_check_form_b_spike_bracket(where: str) -> None:
    """D-M3a (decider file 5): the asserted bracket of form (b)'s floor: a single-sample spike is caught at
    SPIKE_CAUGHT_DBFS and missed at SPIKE_MISSED_DBFS, mid-frame and on a frame boundary."""
    frame = int(round(abx_kit.clicks.FRAME_S * 48000))
    assert abs(abx_kit.SPIKE_FLOOR_DBFS_AT(frame) + 69.8) < 0.1
    for level, caught in ((abx_kit.SPIKE_CAUGHT_DBFS, True), (abx_kit.SPIKE_MISSED_DBFS, False)):
        o, a, b, s0, L = _synthetic_step()
        o = o.copy()
        k = s0 + L // 3
        k = (k // frame) * frame + (frame // 2 if where == "mid_frame" else 0)
        o[k] += np.float32(10 ** (level / 20))
        if caught:
            with pytest.raises(AssertionError, match="click_check"):
                abx_kit.click_check(o, a, b, s0, 48000)
        else:
            assert abx_kit.click_check(o, a, b, s0, 48000)["events_in_step_region"] == 0


def test_speech_layout_item7_lead_on_e_with_ma01_01() -> None:
    """Finding (phase-07c-2b builder file 12): with TSP MA01_01 (114221 samples, end of speech at 108480) the earliest
    onset boundary at or after the heard end of sentence 1 is 119808 (2.496 s from the file start), below one T of
    programme (item 7) on E: T = 2.600 s under M3-G, and also below the heard-IR T30 2.560 s of the old rule. The kit
    stops; nothing is loosened. On S-A (T 2.009 s, delays 32/32) the same sentence passes."""
    with pytest.raises(AssertionError, match="one T of programme"):
        abx_kit.speech_layout(114221, 111954, 108480, 2.5597945976385454, 2.600119578366251, [1395, 32])
    with pytest.raises(AssertionError, match="one T of programme"):
        abx_kit.speech_layout(114221, 111954, 108480, 2.5597945976385454, 2.5597945976385454, [1395, 32])
    lay = abx_kit.speech_layout(114221, 111954, 108480, 2.009, 2.009, [32, 32])
    assert lay["boundaries"][0] == 118784 >= 2.009 * 48000


@pytest.mark.parametrize("t30, delays, gap, heard_gap, after", [
    (2.009, [32, 32], 96768, 96768, 96800),        # S-A: Delta 0, N moves one partition (decider file 5)
    (1.370, [32, 1407], 67584, 66209, 66080),      # both_wall: Delta 1375 (interrogator file 6 arithmetic)
    (2.600119578366251, [1395, 32], 126464, 125101, 124960),  # E under M3-G: T = 2.600 s (interrogator file 11)
])
def test_noise_programme_as_heard(t30, delays, gap, heard_gap, after) -> None:
    """D-M3b (decider file 5; interrogator file 6): gaps ceil((T fs + Delta)/P) P, the onset at the first partition
    boundary at or after the heard end of burst 2, burst 3 at N + ceil(T fs/P) P; every heard silence >= T."""
    x, onset, rec = abx_kit.noise_programme(t30, 0, 7001, delays)
    assert onset % abx_kit.PARTITION == 0
    assert round(rec["heard_gaps_s"][0] * abx_kit.FS) == heard_gap == gap - (max(delays) - min(delays))
    assert round(rec["heard_silence_after_onset_s"] * abx_kit.FS) == after
    assert min(rec["onset_minus_heard_end_samples"]) >= 0
    assert all(g >= t30 for g in rec["heard_gaps_s"]) and rec["heard_silence_after_onset_s"] >= t30


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
    # E (decider file 8, M3-S): the committed scene, its label and Class line, capped at m = 6, 7, 8
    e = abx_kit.SCENES[abx_kit.SCENE_E]
    assert sc["name"] == abx_kit.SCENE_E and sc["label"] == e.label and sc["label_detail"] == list(e.label_detail)
    assert sc["class"] == abx_kit.require_class_line(e)
    assert sc["scene_sha256"] == abx_kit.sha256_file(e.committed)
    assert sc["scene_file"] == "tools/ci/abx_scenes/layout5_s0.9_emitter_wall.json"
    assert all(all(v) for v in sc["capped"].values())
    em = sc["emitters"]
    assert len(em) == 2 and abs(em[0]["r_m"] - 22.11) < 0.01 and abs(em[1]["r_m"] - 12.37) < 0.01
    for x in em:
        assert abs(x["tail_T30_1k_s"] / x["target_T60_1k_s"] - 1.0) <= 0.10, x
    # M3-G: T = max(heard, every tail T30); on E the tail is longer than the heard IR's T30 (builder file 4)
    assert sc["T30_1k_s_label"] == abx_kit.HEARD_T30_LABEL
    assert sc["construction_T_s"] == max(sc["T30_1k_s"], *sc["tail_T30_1k_s"]) > sc["T30_1k_s"]
    gc = m["m2_gap_check"]
    assert gc["construction_T_s"] == sc["construction_T_s"] and gc["heard_T30_1k_s"] == sc["T30_1k_s"]
    assert gc["min_gap_s"] >= gc["construction_T_s"] and gc["min_gap_ge_tail_T30"] and gc["min_gap_ge_construction_T"]
    keys = {"63", "125", "250", "500", "1000", "2000", "4000", "8000"}
    for g, rec in m["ir_checks"].items():
        gd = float(g)
        assert rec["band_step_check"]["max_abs_err_db"] <= abx_kit.BAND_STEP_TOL_DB  # M3-C 7
        for row in rec["rows"]:
            assert abs(row["tail_alone"]["step_db"] - gd) <= 0.01
            assert "specular_share" not in row["ax47_window"]
            assert 0.0 <= row["ax47_window"]["window_unscaled_share"] <= abx_kit.S_W_MAX
        for br in rec["bands"]:
            assert set(br["bands"]) == keys
        # s < 1: E_target has a specular share, so M1's reversal condition is live (decider file 8, file 34's clause)
        assert max(b["target_specular_share"] for b in rec["bands"][0]["bands"].values()) > 0.0
        h = rec["heard"]
        assert set(h["bands"]) == keys
        # (S-A's identity Delta G = 10 log10(1 + share (a^2 - 1)) holds only when the scaled and unscaled parts are
        # disjoint; on E the ISM fade-out overlaps the tail's fade-in, so it is not asserted here.)
        assert round(h["bands"]["1000"]["tail_share_of_heard"], 3) == 0.852  # builder file 4, E
        assert abs(h["bands"]["1000"]["delta_G_db"] - (0.778 if gd == 0.9 else h["bands"]["1000"]["delta_G_db"])) < 5e-4
    stims = [*(t for blk in m["blocks"].values() for t in blk), *m["familiarisation"]]
    for t in stims:
        # M3-C 7: B and E nulled against the offline reference; M3-C 6's gap-cue print present
        assert t["nulls"]["B_vs_offline_db"] <= -120.0 and t["nulls"]["E_vs_offline_stepped_ir_db"] <= -120.0
        assert set(t["gap_cue"]) == {"E_minus_B_re_B_1k_db_100ms", "E_minus_B_re_B_1k_db_300ms", "delta_G_band_max_db"}
        assert t["heard"]["heard_silence_after_onset_s"] >= sc["construction_T_s"]
        assert min(t["heard"]["heard_gaps_s"]) >= sc["construction_T_s"]
    assert m["summary"]["stimuli"] == len(stims) == 8
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
