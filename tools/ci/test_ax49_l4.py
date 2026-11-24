"""Phase-07c-2b M3-L4: render_cli --ax49-provisional, the validation-only flag of the AX49 L4 listening item.

Decider file 6 (M3-7 / M3-L4) with Seat 5's F1-F6 and F2' (file 8-seat5) and Seat 3's checks (files 4-seat3,
8-seat3), on a small scene with L_p < L (F6: living_room, L_p 0.43 s, L 1.48 s):
- F1: refused unless --mode omni; L_f, L_p and L printed; refused where the scene has no provisional.
- F2 (as composed) / F2': excluded with --ensemble, --abx-step-db, --tail-level ax16, --switch-scene; with --in/--out
  only through --realtime-emulation and a fixed --block.
- F4: src/plugin never names the flag.
- F5: two flagged runs are bit-identical (IR and realtime render); the default IR does not depend on the flag's code.
- P2 / P3 (Seat 3): the provisional IR equals the exact one bit for bit before the earliest t_mix,e - 2.5 ms, and is
  exactly 0 from L_p on.
- S3 / F2' (3): the realtime render through the flag nulls against a float64 FFT convolution of the IR the flag
  writes (<= -120 dB residual / signal energy, the Phase 06 criterion), so the IR rendered is the IR written.
"""

from __future__ import annotations

import json
import os
import pathlib
import re
import sys

import pytest

np = pytest.importorskip("numpy")

REPO = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))

SCENE = REPO / "tests" / "scenes" / "valid" / "living_room.json"
FLAG = "--ax49-provisional"


def _binary() -> pathlib.Path | None:
    from tools.acoustics import render_cli

    b = render_cli.find_render_cli()
    if b is None and os.environ.get("SPATIAL_REQUIRE_RENDER_CLI") == "1":
        pytest.fail("render_cli not found and SPATIAL_REQUIRE_RENDER_CLI=1")
    return b


def test_plugin_never_names_the_flag() -> None:
    # F4: the plugin never names the flag (and never links src/cli: test_abx_kit.py checks the include side)
    for path in (REPO / "src" / "plugin").rglob("*"):
        if path.is_file():
            text = path.read_text(encoding="utf-8", errors="replace")
            assert "ax49-provisional" not in text and "ax49Provisional" not in text, path


@pytest.fixture()
def binary() -> pathlib.Path:
    b = _binary()
    if b is None:
        pytest.skip("render_cli not built")
    return b


def test_guards(binary: pathlib.Path, tmp_path: pathlib.Path) -> None:
    from tools.acoustics import render_cli, signals, wav

    inp = tmp_path / "in.wav"
    wav.write_float32(inp, signals.to_stereo(np.zeros(4800)), 48000)
    base = ["--scene", SCENE, FLAG]
    refused = [
        [*base, "--mode", "binaural", "--ir", tmp_path / "a.wav"],
        [*base, "--mode", "omni", "--ir", tmp_path / "a.wav", "--ensemble", "2"],
        [*base, "--mode", "omni", "--ir", tmp_path / "a.wav", "--abx-step-db", "0.9", "--abx-stepped-ir", tmp_path / "b.wav"],
        [*base, "--mode", "omni", "--ir", tmp_path / "a.wav", "--tail-level", "ax16"],
        [*base, "--mode", "omni", "--in", inp, "--out", tmp_path / "o.wav"],
        [*base, "--mode", "omni", "--in", inp, "--out", tmp_path / "o.wav", "--realtime-emulation", "--block", "random"],
        [*base, "--mode", "omni", "--in", inp, "--out", tmp_path / "o.wav", "--realtime-emulation", "--block", "512",
         "--switch-scene", SCENE, "--switch-every", "0.5"],
    ]
    for args in refused:
        r = render_cli.run(binary, *args)
        assert r.returncode == 1, (args, r.stdout, r.stderr)


def test_refused_without_a_provisional(binary: pathlib.Path, tmp_path: pathlib.Path) -> None:
    # F1: a scene whose L_p >= L has no provisional; the flag refuses (never silently the exact IR)
    from tools.acoustics import render_cli

    scene = json.loads(SCENE.read_text())
    for face in scene["room"]["surfaces"].values():
        face["absorption"] = [0.95] * 8  # a near-anechoic room: T60 so short that L_p >= L
    path = tmp_path / "dead.json"
    path.write_text(json.dumps(scene))
    r = render_cli.run(binary, "--scene", path, "--mode", "omni", FLAG, "--ir", tmp_path / "p.wav")
    if "provisional yes" in r.stdout:
        pytest.skip("this near-anechoic variant still has a provisional")
    assert r.returncode == 1 and "no provisional tail" in r.stderr, (r.stdout, r.stderr)


def _timing(stdout: str) -> dict[str, float]:
    m = re.search(r"t_mix,e,max ([0-9.e+-]+) s, T60_max ([0-9.e+-]+) s, L_f ([0-9.e+-]+) s, L_p ([0-9.e+-]+) s, "
                  r"L ([0-9.e+-]+) s, provisional yes", stdout)
    assert m, stdout
    return dict(zip(("mix", "t60", "lf", "lp", "L"), map(float, m.groups())))


def test_provisional_ir(binary: pathlib.Path, tmp_path: pathlib.Path) -> None:
    from tools.acoustics import render_cli, wav

    common = ["--scene", SCENE, "--mode", "omni"]
    r1 = render_cli.run(binary, *common, FLAG, "--ir", tmp_path / "p1.wav", "--diagnostics", tmp_path / "d.json")
    r2 = render_cli.run(binary, *common, FLAG, "--ir", tmp_path / "p2.wav")
    rx = render_cli.run(binary, *common, "--ir", tmp_path / "x.wav")
    assert r1.returncode == r2.returncode == rx.returncode == 0, (r1.stderr, r2.stderr, rx.stderr)
    t = _timing(r1.stdout)
    assert t["lp"] < t["L"] and abs(t["lp"] - t["lf"] - 0.1) < 1e-9  # F1 print; AX49 L_p = L_f + 0.1 s
    assert (tmp_path / "p1.wav").read_bytes() == (tmp_path / "p2.wav").read_bytes()  # F5: deterministic
    p, fs = wav.read(tmp_path / "p1.wav")
    x, _ = wav.read(tmp_path / "x.wav")
    d = json.loads((tmp_path / "d.json").read_text())
    shift = float(d["alignmentShiftS"])
    mix_min = min(float(e["mixS"]) for e in d["emitters"])
    pre = int((mix_min - shift - 0.0025) * fs)
    assert pre > 0
    # P2: before the earliest t_mix,e - 2.5 ms the provisional IR is the exact one, bit for bit
    assert np.array_equal(p[:pre].view(np.uint32), x[:pre].view(np.uint32))
    # P3: exactly 0 from L_p on (times from emission; the aligned IR starts alignmentShiftS after emission)
    lp = int(np.ceil((t["lp"] - shift) * fs))
    assert lp < len(x) and (len(p) <= lp or np.all(p[lp:] == 0.0)), (lp, len(p), len(x))
    assert np.any(p[: min(lp, len(p))] != x[: min(lp, len(p))])  # the provisional differs from the exact tail


def test_realtime_render_is_the_written_ir(binary: pathlib.Path, tmp_path: pathlib.Path) -> None:
    # S3 / F2' (3): the realtime render through the flag is the IR the flag writes, convolved (Phase 06 criterion)
    from scipy import signal as sps

    from tools.acoustics import render_cli, signals, wav

    x = np.zeros(48000)
    x[:12000] = signals.pink_noise(12000, 11) * 0.1
    inp = tmp_path / "in.wav"
    wav.write_float32(inp, signals.to_stereo(x), 48000)
    common = ["--scene", SCENE, "--mode", "omni", FLAG]
    rt = ["--in", inp, "--realtime-emulation", "--block", "512", "--partition", "512"]
    assert render_cli.run(binary, *common, "--ir", tmp_path / "p.wav").returncode == 0
    assert render_cli.run(binary, *common, *rt, "--out", tmp_path / "o1.wav").returncode == 0
    assert render_cli.run(binary, *common, *rt, "--out", tmp_path / "o2.wav").returncode == 0
    assert (tmp_path / "o1.wav").read_bytes() == (tmp_path / "o2.wav").read_bytes()  # F5
    h, _ = wav.read(tmp_path / "p.wav")
    o, _ = wav.read(tmp_path / "o1.wav")
    xin = signals.to_stereo(x).astype(np.float64)
    for ch in range(2):  # omni: output ch = emitter 0's tap ch + emitter 1's tap ch (identical input channels)
        ref = sps.fftconvolve(xin[:, 0], h[:, ch].astype(np.float64) + h[:, 2 + ch].astype(np.float64))[: len(o)]
        res = o[:, ch].astype(np.float64) - ref[: len(o)]
        assert 10 * np.log10(np.sum(res**2) / np.sum(ref**2)) <= -120.0
