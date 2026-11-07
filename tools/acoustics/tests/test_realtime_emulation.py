"""Phase 06: render_cli --realtime-emulation (sim::RealtimeEngine, partitioned convolution in host
blocks) nulls against the offline reference render of a Phase 04 room IR within -120 dB
(residual / signal energy), for random and fixed host block sizes and every partition size.
The C++ unit tests check the same engine in-process (tests/unit/test_realtime_engine.cpp)."""

import numpy as np
import pytest

from tools.acoustics import render_cli, signals, wav

from conftest import REPO

SCENES = REPO / "tests" / "scenes" / "valid"


def _residual_db(test: np.ndarray, ref: np.ndarray) -> float:
    ref = ref.astype(np.float64)
    return float(10 * np.log10(np.sum((test.astype(np.float64) - ref) ** 2) / np.sum(ref**2)))


@pytest.fixture(scope="module")
def drums(tmp_path_factory):
    path = tmp_path_factory.mktemp("rt") / "drums.wav"
    wav.write_float32(path, signals.to_stereo(*signals.drum_loop(48000, bars=2)).astype(np.float32), 48000)
    return path


@pytest.mark.parametrize(
    "block,partition",
    [("random", "512"), ("random", "256"), ("random", "128"), ("37", "512"), ("2048", "512"), ("1", "128")],
)
def test_realtime_emulation_nulls_against_offline(render_cli_path, tmp_path, drums, block, partition):
    scene = SCENES / "medium_room.json"
    off, rt = tmp_path / "off.wav", tmp_path / "rt.wav"
    r = render_cli.run(render_cli_path, "--scene", scene, "--mode", "omni", "--in", drums, "--out", off)
    assert r.returncode == 0, r.stderr
    r = render_cli.run(
        render_cli_path, "--scene", scene, "--mode", "omni", "--in", drums, "--out", rt,
        "--realtime-emulation", "--block", block, "--partition", partition,
    )
    assert r.returncode == 0, r.stderr
    a, fs_a = wav.read_float32(off)
    b, fs_b = wav.read_float32(rt)
    assert fs_a == fs_b == 48000
    assert a.shape == b.shape
    db = _residual_db(b, a)
    print(f"block {block}, P {partition}: residual {db:.1f} dB (gate -120 dB)")
    assert db <= -120.0


def test_realtime_emulation_is_deterministic_at_44k(render_cli_path, tmp_path):
    x = signals.to_stereo(signals.pink_noise(44100, seed=5) * 0.1, signals.pink_noise(44100, seed=6) * 0.1)
    wav.write_float32(tmp_path / "in.wav", x.astype(np.float32), 44100)
    outs = []
    for k in range(2):
        out = tmp_path / f"rt{k}.wav"
        r = render_cli.run(
            render_cli_path, "--scene", SCENES / "living_room.json", "--mode", "omni", "--in", tmp_path / "in.wav",
            "--out", out, "--realtime-emulation", "--block", "random",
        )
        assert r.returncode == 0, r.stderr
        outs.append(out.read_bytes())
    assert outs[0] == outs[1]
    r = render_cli.run(render_cli_path, "--scene", SCENES / "living_room.json", "--mode", "omni",
                       "--in", tmp_path / "in.wav", "--out", tmp_path / "off.wav")
    assert r.returncode == 0, r.stderr
    a, _ = wav.read_float32(tmp_path / "off.wav")
    b, _ = wav.read_float32(tmp_path / "rt0.wav")
    assert _residual_db(b, a) <= -120.0


def test_switch_demo_renders_and_alternates(render_cli_path, tmp_path):
    tone = signals.to_stereo(signals.sustained_tone(48000, 3.0))
    wav.write_float32(tmp_path / "tone.wav", tone.astype(np.float32), 48000)
    out = tmp_path / "sw.wav"
    r = render_cli.run(
        render_cli_path, "--scene", SCENES / "living_room.json", "--switch-scene", SCENES / "concert_hall_box.json",
        "--switch-every", "0.5", "--mode", "omni", "--in", tmp_path / "tone.wav", "--out", out, "--realtime-emulation",
    )
    assert r.returncode == 0, r.stderr
    y, fs = wav.read_float32(out)
    # In the first 0.5 s the output is the living_room render exactly (no switch has happened yet).
    off = tmp_path / "off.wav"
    r = render_cli.run(render_cli_path, "--scene", SCENES / "living_room.json", "--mode", "omni",
                       "--in", tmp_path / "tone.wav", "--out", off)
    assert r.returncode == 0, r.stderr
    a, _ = wav.read_float32(off)
    head = int(0.45 * fs)
    assert _residual_db(y[:head], a[:head]) <= -120.0
    # Between the end of the first fade and the start of the second (switch requests at 0.5 s and
    # 1.0 s, picked up at the next partition, 30 ms fades) the output is exactly the
    # concert_hall_box render: the new state convolves the full input history.
    hall = tmp_path / "hall.wav"
    r = render_cli.run(render_cli_path, "--scene", SCENES / "concert_hall_box.json", "--mode", "omni",
                       "--in", tmp_path / "tone.wav", "--out", hall)
    assert r.returncode == 0, r.stderr
    b, _ = wav.read_float32(hall)
    lo, hi = int(0.55 * fs), int(0.98 * fs)
    assert _residual_db(y[lo:hi], b[lo:hi]) <= -120.0
