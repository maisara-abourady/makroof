"""render_cli end to end (the real binary): stub render is bit-identical, invalid scenes give exit
code 2 with readable errors, --ir layout. The same checks run in-process on every OS in
tests/unit/test_cli.cpp."""

import json
import pathlib

import numpy as np
import pytest

from tools.acoustics import render_cli, wav

from conftest import REPO

SCENES = REPO / "tests" / "scenes"
VALID = sorted(p for p in (SCENES / "valid").glob("*.json") if not p.name.startswith("_"))
INVALID = sorted(p for p in (SCENES / "invalid").glob("*.json") if not p.name.startswith("_"))


@pytest.mark.parametrize("scene", VALID, ids=lambda p: p.stem)
@pytest.mark.parametrize("fs", [44100, 48000, 96000])
def test_stub_render_is_bit_identical(render_cli_path, tmp_path, scene, fs):
    rng = np.random.default_rng(fs)
    data = rng.uniform(-1.0, 1.0, (fs // 2 + 7, 2)).astype(np.float32)
    data[0, 0] = -0.0
    wav.write_float32(tmp_path / "in.wav", data, fs)
    result = render_cli.run(render_cli_path, "--scene", scene, "--in", tmp_path / "in.wav", "--out", tmp_path / "out.wav")
    assert result.returncode == 0, result.stderr
    out, out_fs = wav.read_float32(tmp_path / "out.wav")
    assert out_fs == fs
    assert out.shape == data.shape
    assert out.tobytes() == data.tobytes()


@pytest.mark.parametrize("fixture", INVALID, ids=lambda p: p.stem)
def test_invalid_fixture_exits_2_with_readable_errors(render_cli_path, tmp_path, fixture):
    result = render_cli.run(render_cli_path, "--scene", fixture, "--ir", tmp_path / "ir.wav")
    assert result.returncode == 2, result.stdout + result.stderr
    code = fixture.name.split(".")[0]
    assert f"error: {code}" in result.stderr
    assert "invalid scene" in result.stderr
    assert not (tmp_path / "ir.wav").exists()


def test_ir_mode_writes_emitter_by_output_channels(render_cli_path, tmp_path):
    result = render_cli.run(render_cli_path, "--scene", VALID[0], "--ir", tmp_path / "ir.wav", "--rate", "88200")
    assert result.returncode == 0, result.stderr
    ir, fs = wav.read_float32(tmp_path / "ir.wav")
    assert fs == 88200
    assert ir.shape == (1, 4)
    assert ir[0].tolist() == [1.0, 0.0, 0.0, 1.0]


def test_automation_is_not_implemented_yet(render_cli_path, tmp_path):
    result = render_cli.run(render_cli_path, "--scene", VALID[0], "--ir", tmp_path / "ir.wav", "--automation", "a.json")
    assert result.returncode == 1
    assert "not implemented until Phase 10" in result.stderr


def test_io_error_exit_code(render_cli_path, tmp_path):
    result = render_cli.run(render_cli_path, "--scene", tmp_path / "nope.json", "--ir", tmp_path / "ir.wav")
    assert result.returncode == 3
    result = render_cli.run(render_cli_path, "--scene", VALID[0], "--in", tmp_path / "nope.wav", "--out", tmp_path / "o.wav")
    assert result.returncode == 3


def test_validation_overrides_atmosphere_and_mix_floor(render_cli_path, tmp_path):
    """Phase-05 validation-only flags (AX4 atmosphere override, scope 6 handover floor)."""
    scene = SCENES / "valid" / "medium_room.json"

    def ir(name, *extra):
        r = render_cli.run(render_cli_path, "--scene", scene, "--mode", "omni", "--ir", tmp_path / name, *extra)
        assert r.returncode == 0, r.stderr
        return wav.read_float32(tmp_path / name)[0]

    base = ir("a.wav")
    assert np.array_equal(base, ir("b.wav", "--atmosphere", "20,50"))  # the AX4 atmosphere itself
    assert not np.array_equal(base, ir("c.wav", "--atmosphere", "20,70"))

    def diag(name, *extra):
        r = render_cli.run(render_cli_path, "--scene", scene, "--mode", "omni", "--diagnostics", tmp_path / name, *extra)
        assert r.returncode == 0, r.stderr
        return json.loads((tmp_path / name).read_text())["emitters"]

    for e0, e1 in zip(diag("d0.json"), diag("d1.json", "--mix-floor-ms", "140")):
        assert e1["mixLowerBoundS"] == pytest.approx(e0["directS"] + 0.140, abs=1e-12)
        assert e1["handoverS"] >= e1["mixLowerBoundS"]

    for bad in (["--atmosphere", "99,50"], ["--atmosphere", "20"], ["--mix-floor-ms", "-1"],
                ["--atmosphere", "20,50", "--no-air-absorption"]):
        r = render_cli.run(render_cli_path, "--scene", scene, "--mode", "omni", "--ir", tmp_path / "x.wav", *bad)
        assert r.returncode == 1, bad
