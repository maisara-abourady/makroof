"""Phase-07c-2b L4-P: render_cli's validation-only --provisional-ir, --provisional-timing and
--provisional-handover-sample (decider file 10 Part A; interrogator file 13; Seat 5 file 14).

Tests (file 10's numbering):
1. Guard: src/plugin never names the option fields or the flags; only src/cli/Cli.cpp reads the option fields.
2. No golden path: the flag strings appear only in src/cli/Cli.cpp, the unit tests, tools/ci/abx_kit.py,
   tools/ci/listening_pack.py, tools/ci/test_*.py and the prose (docs/ and Markdown files).
3. Default output unchanged, per OS (AX5 holds only on one platform, so no cross-OS hash): on each runner the
   default `--mode omni --ir` output of medium_room is bit-identical whether or not unrelated options ride along,
   and its SHA-256 is printed; the C++ side (tests/unit/test_cli_provisional.cpp) asserts it bit-identical to
   sim::buildRoomIR; every existing golden and render test stays green.
4. Determinism: the flagged outputs are bit-identical run to run.
5. Flagged offline against flagged --realtime-emulation --block 512: null <= -120 dB (Phase 06).
6. Refusals r1-r5 exit 1 and leave no output file (r1 on AX49's L_p >= L 100 m low-alpha cube).
8. Handover: before N bit-identical to the --provisional-ir real-time render; from N + ceil(0.030 fs)
   bit-identical to the default (exact) real-time render with the same block and partition; inside the fade the
   AX47 mid-fade checks (abx_kit.midfade_checks, 8u reconstruction).
(Test 7, plugin parity, is the JUCE-free [pipeline] Catch2 test in tests/unit/test_cli_provisional.cpp.)

The L4 scene (decider file 10 L4-S) is tests/scenes/valid/stone_box.json with every absorption coefficient times
K_L4, built here (a new tests/scenes/valid fixture would join the per-fixture golden metrics and the listening
pack). render_cli needed: skipped without it unless SPATIAL_REQUIRE_RENDER_CLI=1.
"""

from __future__ import annotations

import copy
import hashlib
import json
import math
import os
import pathlib
import subprocess
import sys

import pytest

REPO = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))

FIELDS = ("provisionalIr", "provisionalHandoverSample")
FLAGS = ("--provisional-ir", "--provisional-handover-sample")
ALL_STRINGS = FIELDS + FLAGS + ("--provisional-timing", "provisionalTimingPath")
# L4-S: the factor on every band's absorption that makes T60_max 8.0 +/- 0.1 s (measured with
# --provisional-timing: 7.9955 s in the 63 Hz band at 48 kHz; builder file 15).
K_L4 = 0.84
FS = 48000
BLOCK = 512
PARTITION = 512


# ---------------------------------------------------------------------------------------------------------
# Tests 1 and 2: static (no binary)
# ---------------------------------------------------------------------------------------------------------


def test_plugin_never_reaches_the_provisional_flags() -> None:
    for path in (REPO / "src" / "plugin").rglob("*"):
        if not path.is_file():
            continue
        text = path.read_text(encoding="utf-8", errors="replace")
        for name in FIELDS + FLAGS:
            assert name not in text, f"{path} names {name}"
    readers = sorted(p for p in (REPO / "src").rglob("*")
                     if p.is_file() and p.suffix in (".h", ".hpp", ".cpp")
                     and any(f in p.read_text(encoding="utf-8", errors="replace") for f in FIELDS))
    assert readers == [REPO / "src" / "cli" / "Cli.cpp"]


def _repo_files() -> list[pathlib.Path]:
    try:
        out = subprocess.run(["git", "ls-files", "--cached", "--others", "--exclude-standard"], cwd=REPO,
                             capture_output=True, text=True, check=True).stdout
        return [REPO / line for line in out.splitlines() if line]
    except (OSError, subprocess.CalledProcessError):
        skip = {".git", "build", ".venv", "node_modules", "__pycache__"}
        return [p for p in REPO.rglob("*") if p.is_file() and not skip.intersection(p.relative_to(REPO).parts)]


def _allowed(rel: str) -> bool:
    if rel in ("src/cli/Cli.cpp", "tools/ci/abx_kit.py", "tools/ci/listening_pack.py"):
        return True
    if rel.startswith("docs/") or rel.startswith("tests/unit/") or rel.endswith(".md"):  # prose and unit tests
        return True
    return rel.startswith("tools/ci/test_") and rel.endswith(".py")


def test_no_golden_or_validation_path_names_the_flags() -> None:
    offenders = []
    for path in _repo_files():
        if not path.is_file() or path.suffix in (".wav", ".bin", ".sofa", ".png", ".zip", ".pyc"):
            continue
        rel = path.relative_to(REPO).as_posix()
        if _allowed(rel):
            continue
        text = path.read_text(encoding="utf-8", errors="replace")
        if rel == "src/sim/Engine.h":
            # file 10 L4-P: assembleProvisional()'s comment names the flag; no code line may
            text = "\n".join(line for line in text.splitlines() if not line.lstrip().startswith("//"))
        offenders += [f"{rel}: {s}" for s in ALL_STRINGS if s in text]
    assert offenders == []


# ---------------------------------------------------------------------------------------------------------
# render_cli
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


@pytest.fixture(scope="module")
def np():
    return pytest.importorskip("numpy")


def _run(binary: pathlib.Path, *args) -> subprocess.CompletedProcess:
    from tools.acoustics import render_cli

    return render_cli.run(binary, *args)


def _ok(binary: pathlib.Path, *args) -> str:
    r = _run(binary, *args)
    assert r.returncode == 0, r.stderr
    return r.stdout


def l4_scene(k: float = K_L4) -> dict:
    scene = json.loads((REPO / "tests" / "scenes" / "valid" / "stone_box.json").read_text(encoding="utf-8"))
    for surface in scene["room"]["surfaces"].values():
        surface["absorption"] = [a * k for a in surface["absorption"]]
    scene["extensions"] = {"notes": f"L4 (phase-07c-2b decider file 10): stone_box with absorption x {k}"}
    return scene


def cube100_scene() -> dict:
    # AX49's L_p >= L scene: the 100 m low-alpha cube of the records (tests/unit/test_diffuse_records.cpp).
    scene = copy.deepcopy(l4_scene(1.0))
    scene["room"]["geometry"]["dimensions"] = [100.0, 100.0, 100.0]
    for surface in scene["room"]["surfaces"].values():
        surface["absorption"] = [0.05] * 8
        surface["scattering"] = 0.3
    scene["listener"]["position"] = [50.0, 30.0, 1.7]
    scene["emitters"][0]["position"] = [45.0, 70.0, 2.0]
    scene["emitters"][1]["position"] = [55.0, 70.0, 2.0]
    return scene


@pytest.fixture(scope="module")
def work(tmp_path_factory, np) -> dict:
    from tools.acoustics import wav

    d = tmp_path_factory.mktemp("provisional")
    paths = {"dir": d, "l4": d / "l4.json", "cube": d / "cube100.json", "in": d / "in.wav"}
    paths["l4"].write_text(json.dumps(l4_scene()), encoding="utf-8")
    paths["cube"].write_text(json.dumps(cube100_scene()), encoding="utf-8")
    # 0.5 s of seeded noise, then silence: 1.5 s of input
    rng = np.random.default_rng(20261124)
    x = np.zeros((int(1.5 * FS), 2))
    x[: FS // 2] = rng.standard_normal((FS // 2, 2)) * 0.1
    wav.write_float32(paths["in"], x, FS)
    return paths


def _read(path):
    from tools.acoustics import wav

    data, fs = wav.read_float32(path)
    assert fs == FS
    return data


def _bits(a, b) -> bool:
    return a.shape == b.shape and bool((a.view("uint32") == b.view("uint32")).all())


def _sha(path: pathlib.Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def test_l4_scene_timing(binary, work) -> None:
    # L4-S: provisional, L_p < L, T60_max 8.0 +/- 0.1 s; printed for the record.
    t = work["dir"] / "timing.json"
    out = _ok(binary, "--scene", work["l4"], "--mode", "omni", "--provisional-ir", "--provisional-timing", t)
    assert "provisional tail, validation-only flag" in out
    timing = json.loads(t.read_text())
    assert timing["provisional"] is True
    assert timing["endS"] < timing["exactS"]
    assert abs(timing["t60MaxS"] - 8.0) <= 0.1
    assert timing["t60MaxS"] == max(timing["bandsT60S"])
    assert timing["endS"] == pytest.approx(timing["fadeStartS"] + 0.1, abs=1e-12)
    print(f"L4 k {K_L4}: {json.dumps(timing)}")


def test_default_output_unchanged_per_os(binary, work) -> None:
    # Test 3 on this runner: unrelated options leave the default omni IR bit-identical; its hash is printed per OS.
    medium = REPO / "tests" / "scenes" / "valid" / "medium_room.json"
    d = work["dir"]
    _ok(binary, "--scene", medium, "--mode", "omni", "--ir", d / "default.wav")
    _ok(binary, "--scene", medium, "--mode", "omni", "--ir", d / "default2.wav")
    _ok(binary, "--scene", medium, "--mode", "omni", "--ir", d / "default_images.wav", "--images", d / "img.json")
    assert _sha(d / "default.wav") == _sha(d / "default2.wav") == _sha(d / "default_images.wav")
    # the flagged IR differs from the default one (it is the provisional) and the default is the exact
    _ok(binary, "--scene", work["l4"], "--mode", "omni", "--ir", d / "l4_exact.wav")
    _ok(binary, "--scene", work["l4"], "--mode", "omni", "--provisional-ir", "--ir", d / "l4_prov.wav")
    assert _sha(d / "l4_exact.wav") != _sha(d / "l4_prov.wav")
    print(f"test 3 ({sys.platform}): sha256 of render_cli --mode omni --ir on medium_room.json = {_sha(d / 'default.wav')}")


def test_flagged_output_is_deterministic(binary, work) -> None:
    d = work["dir"]
    common = ("--scene", work["l4"], "--mode", "omni", "--provisional-ir")
    for i in (1, 2):
        _ok(binary, *common, "--ir", d / f"det_ir{i}.wav", "--in", work["in"], "--out", d / f"det_out{i}.wav")
        _ok(binary, *common, "--in", work["in"], "--out", d / f"det_rt{i}.wav", "--realtime-emulation",
            "--block", str(BLOCK), "--provisional-handover-sample", str(BLOCK * 93))
    for name in ("det_ir", "det_out", "det_rt"):
        assert _sha(d / f"{name}1.wav") == _sha(d / f"{name}2.wav"), name


def test_flagged_offline_nulls_realtime(binary, work, np) -> None:
    d = work["dir"]
    common = ("--scene", work["l4"], "--mode", "omni", "--provisional-ir", "--in", work["in"])
    _ok(binary, *common, "--out", d / "off.wav")
    _ok(binary, *common, "--out", d / "rt.wav", "--realtime-emulation", "--block", "512")
    off, rt = _read(d / "off.wav").astype(np.float64), _read(d / "rt.wav").astype(np.float64)
    assert off.shape == rt.shape
    for ch in range(off.shape[1]):
        null = 10 * math.log10(float(np.sum((rt[:, ch] - off[:, ch]) ** 2)) / float(np.sum(off[:, ch] ** 2)))
        print(f"test 5: channel {ch} null {null:.1f} dB")
        assert null <= -120.0


REFUSALS = {
    # r2
    "r2_no_mode": [],
    "r2_omni_early": ["--mode", "omni-early"],
    # r3
    "r3_diagnostics": ["--mode", "omni", "--diagnostics", "{d}/x.json"],
    "r3_ensemble": ["--mode", "omni", "--ensemble", "2"],
    "r3_tail_only": ["--mode", "omni", "--tail-only"],
    "r3_ensemble_emitter": ["--mode", "omni", "--ensemble", "2", "--ensemble-emitter", "0"],
    "r3_tail_level_ax16": ["--mode", "omni", "--tail-level", "ax16"],
    "r3_switch": ["--mode", "omni", "--realtime-emulation", "--switch-scene", "{scene}", "--switch-every", "0.5"],
    "r3_abx_step_db": ["--mode", "omni", "--abx-step-db", "0.9"],
    "r3_abx_stepped_ir": ["--mode", "omni", "--abx-step-db", "0.9", "--abx-stepped-ir", "{d}/s.wav"],
    "r3_image_cap": ["--mode", "omni", "--image-cap", "1000"],
    "r3_automation": ["--mode", "omni", "--automation", "{d}/a.json"],
    # r5
    "r5_not_partition_multiple": ["--mode", "omni", "--realtime-emulation", "--block", "256", "--partition", "512",
                                  "--provisional-handover-sample", "768"],
    "r5_not_block_multiple": ["--mode", "omni", "--realtime-emulation", "--block", "384", "--partition", "128",
                              "--provisional-handover-sample", "512"],
    "r5_below_one_partition": ["--mode", "omni", "--realtime-emulation", "--block", "128", "--partition", "512",
                               "--provisional-handover-sample", "256"],
    "r5_zero": ["--mode", "omni", "--realtime-emulation", "--block", "512", "--provisional-handover-sample", "0"],
    "r5_beyond_input": ["--mode", "omni", "--realtime-emulation", "--block", "512",
                        "--provisional-handover-sample", str(512 * 200)],
    "r5_no_realtime": ["--mode", "omni", "--provisional-handover-sample", "512"],
    "r5_random_block": ["--mode", "omni", "--realtime-emulation", "--block", "random",
                        "--provisional-handover-sample", "512"],
    "r5_no_block": ["--mode", "omni", "--realtime-emulation", "--provisional-handover-sample", "512"],
}


@pytest.mark.parametrize("case", sorted(REFUSALS))
def test_refusals_r2_r3_r5(binary, work, case) -> None:
    d = work["dir"] / f"refuse_{case}"
    d.mkdir()
    extra = [a.format(d=d, scene=work["l4"]) for a in REFUSALS[case]]
    r = _run(binary, "--scene", work["l4"], "--provisional-ir", "--in", work["in"], "--out", d / "out.wav",
             "--ir", d / "ir.wav", *extra)
    assert r.returncode == 1, (case, r.stdout, r.stderr)
    assert "provisional" in r.stderr or "automation" in r.stderr, r.stderr
    assert sorted(p.name for p in d.iterdir()) == []


@pytest.mark.parametrize("flag", [["--provisional-timing", "t.json"], ["--provisional-handover-sample", "512"]])
def test_refusal_r4(binary, work, flag) -> None:
    d = work["dir"] / f"refuse_r4_{flag[0].strip('-')}"
    d.mkdir()
    args = [flag[0], str(d / flag[1]) if flag[1].endswith(".json") else flag[1]]
    r = _run(binary, "--scene", work["l4"], "--mode", "omni", "--in", work["in"], "--out", d / "out.wav",
             "--realtime-emulation", "--block", "512", *args)
    assert r.returncode == 1 and "need --provisional-ir" in r.stderr, r.stderr
    assert list(d.iterdir()) == []


def test_refusal_r1_on_the_cube_leaves_no_file(binary, work) -> None:
    # r1: L_p >= L, decided from provisionalTiming() before any output file is opened (Seat 5 (a), (b), (c)).
    d = work["dir"] / "refuse_r1"
    d.mkdir()
    r = _run(binary, "--scene", work["cube"], "--mode", "omni", "--provisional-ir", "--in", work["in"],
             "--out", d / "out.wav", "--ir", d / "ir.wav", "--images", d / "images.json",
             "--provisional-timing", d / "timing.json")
    assert r.returncode == 1, r.stderr
    assert "L_p" in r.stderr and "does not apply to this scene" in r.stderr and "exit 1" in r.stderr
    assert list(d.iterdir()) == []


def test_handover(binary, work, np) -> None:
    from tools.ci import abx_kit

    d = work["dir"]
    n = BLOCK * 93  # 47616: a multiple of P and of the block, inside the 72000-sample input
    rt = ("--in", work["in"], "--realtime-emulation", "--block", str(BLOCK), "--partition", str(PARTITION))
    _ok(binary, "--scene", work["l4"], "--mode", "omni", "--provisional-ir", *rt, "--out", d / "h.wav",
        "--provisional-handover-sample", str(n))
    _ok(binary, "--scene", work["l4"], "--mode", "omni", "--provisional-ir", *rt, "--out", d / "p.wav")
    _ok(binary, "--scene", work["l4"], "--mode", "omni", *rt, "--out", d / "x.wav")
    h, p, x = _read(d / "h.wav"), _read(d / "p.wav"), _read(d / "x.wav")
    assert h.shape == x.shape and p.shape[0] < h.shape[0]
    fade = math.ceil(0.030 * FS)
    assert _bits(h[:n], p[:n])
    assert _bits(h[n + fade :], x[n + fade :])
    a = np.zeros_like(h)  # the provisional render, zero past its end (only [0, n + fade) is compared to it)
    a[: p.shape[0]] = p
    assert not _bits(h, a) and not _bits(h, x)
    mid = abx_kit.midfade_checks(h, a, x, n, float(FS))
    assert mid["windows"] > 0
    print(f"test 8: handover at {n}, fade {fade} samples, mid-fade {mid}")
