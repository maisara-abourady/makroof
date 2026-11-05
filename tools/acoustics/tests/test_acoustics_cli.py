"""python -m tools.acoustics {metrics,compare,clicks} on WAV files."""

import json
import subprocess
import sys

import numpy as np

from tools.acoustics import signals, wav

from conftest import REPO

FS = 48000


def _run(*args):
    return subprocess.run([sys.executable, "-m", "tools.acoustics", *map(str, args)], cwd=REPO, capture_output=True, text=True, check=False)


def test_metrics_command(tmp_path):
    h = signals.synthetic_decay(FS, 0.8, seed=1, noise_floor_db=-80.0)
    wav.write_float32(tmp_path / "ir.wav", h / np.max(np.abs(h)), FS)
    result = _run("metrics", tmp_path / "ir.wav")
    assert result.returncode == 0, result.stderr
    data = json.loads(result.stdout)
    assert 0.6 < data["bands"]["1000"]["T30"] < 1.0


def test_compare_command(tmp_path):
    ir = np.zeros(4800)
    ir[[100, 900, 2000]] = [1.0, 0.5, -0.25]
    wav.write_float32(tmp_path / "a.wav", ir, FS)
    wav.write_float32(tmp_path / "b.wav", ir, FS)
    result = _run("compare", tmp_path / "a.wav", tmp_path / "b.wav", "--peaks", "3")
    assert result.returncode == 0, result.stderr
    data = json.loads(result.stdout)
    assert [p["reference_index"] for p in data["peaks"]] == [100, 900, 2000]
    assert all(p["delta_samples"] == 0 for p in data["peaks"])


def test_clicks_command_exit_status(tmp_path):
    tone = signals.sustained_tone(FS, 3.0)
    wav.write_float32(tmp_path / "clean.wav", signals.to_stereo(tone), FS)
    assert _run("clicks", tmp_path / "clean.wav").returncode == 0
    tone[FS] += 0.05
    wav.write_float32(tmp_path / "click.wav", signals.to_stereo(tone), FS)
    result = _run("clicks", tmp_path / "click.wav")
    assert result.returncode == 1
    assert len(json.loads(result.stdout)["channels"][0]["events"]) == 1
