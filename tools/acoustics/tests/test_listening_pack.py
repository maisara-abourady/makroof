"""tools/ci/listening_pack.py builds a complete pack (phase 02: every render is bit-identical;
phase 03: omni early-reflection renders, identical in both channels; phase 04: the full room)."""

import importlib.util

from conftest import REPO


def _load():
    spec = importlib.util.spec_from_file_location("listening_pack", REPO / "tools" / "ci" / "listening_pack.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def test_pack_layout_and_stub_identity(render_cli_path, tmp_path):
    lp = _load()
    pack = lp.build(tmp_path, "phase-02", render_cli_path, log=lambda *_: None)
    scenes = sorted(p.stem for p in (REPO / "tests" / "scenes" / "valid").glob("*.json") if not p.name.startswith("_"))
    for name in lp.SIGNALS:
        assert (pack / "dry" / f"{name}.wav").is_file()
        for scene in scenes:
            assert (pack / scene / f"{name}.wav").is_file()
    readme = (pack / "README.txt").read_text(encoding="utf-8")
    assert "STUB" in readme
    assert "differs" not in readme
    assert readme.count("bit-identical") >= len(lp.SIGNALS) * len(scenes)


def test_phase_03_pack_renders_the_room_in_omni(render_cli_path, tmp_path):
    from tools.acoustics import wav

    lp = _load()
    pack = lp.build(tmp_path, "phase-03", render_cli_path, log=lambda *_: None)
    readme = (pack / "README.txt").read_text(encoding="utf-8")
    assert "EARLY REFLECTIONS ONLY" in readme
    assert "bit-identical" not in readme  # the room changes every render
    for scene in ("small_room", "medium_room", "large_hall", "asymmetric_materials", "open_field"):
        out, fs = wav.read_float32(pack / scene / "clicks.wav")
        dry, _ = wav.read_float32(pack / "dry" / "clicks.wav")
        assert fs == 48000
        assert out.shape[1] == 2 and out.shape[0] > dry.shape[0]
        # Omni: both outputs carry the same room (the L and R emitters are summed into each).
        assert out[:, 0].tobytes() == out[:, 1].tobytes()


def test_phase_04_pack_renders_the_full_room(render_cli_path, tmp_path):
    from tools.acoustics import wav

    lp = _load()
    pack = lp.build(tmp_path, "phase-04", render_cli_path, log=lambda *_: None)
    readme = (pack / "README.txt").read_text(encoding="utf-8")
    assert "FULL ROOM" in readme
    for scene in ("dead_booth", "living_room", "classroom", "club", "concert_hall_box", "stone_box"):
        out, fs = wav.read_float32(pack / scene / "clicks.wav")
        assert fs == 48000
        assert out[:, 0].tobytes() == out[:, 1].tobytes()  # still a mono omni preview
    # The tail makes stone_box ring for seconds after the last click; dead_booth hardly at all.
    dry, _ = wav.read_float32(pack / "dry" / "clicks.wav")
    stone, _ = wav.read_float32(pack / "stone_box" / "clicks.wav")
    booth, _ = wav.read_float32(pack / "dead_booth" / "clicks.wav")
    assert stone.shape[0] - dry.shape[0] > 5 * 48000
    assert booth.shape[0] - dry.shape[0] < 48000
