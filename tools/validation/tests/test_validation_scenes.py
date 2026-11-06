"""Every committed BRAS validation scene is a valid contract scene (render_cli validates it)."""

import pathlib

import pytest

from tools.acoustics import render_cli

SCENES = sorted((pathlib.Path(__file__).resolve().parents[3] / "tests" / "scenes" / "validation").glob("bras_*.json"))


def test_there_are_validation_scenes():
    assert SCENES


@pytest.mark.parametrize("scene", SCENES, ids=lambda p: p.stem)
def test_scene_is_valid(render_cli_path, scene, tmp_path):
    r = render_cli.run(render_cli_path, "--scene", scene, "--mode", "omni", "--images", tmp_path / "i.json")
    assert r.returncode == 0, r.stdout + r.stderr
