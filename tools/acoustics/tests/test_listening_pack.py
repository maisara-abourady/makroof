"""tools/ci/listening_pack.py builds a complete pack (phase 02: every render is bit-identical)."""

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
