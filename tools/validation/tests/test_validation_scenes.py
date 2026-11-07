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


def test_reduction_check_tolerates_last_bit_float_differences_only():
    """make_bras_scenes.py --check compares bras_reduction.json numerically (relative 1e-9): a
    last-bit difference between runner CPUs passes, a real change or a structural change fails."""
    from tools.validation import make_bras_scenes as m

    a = {"CR2": {"dims": {"W": 8.370809602004694}, "faces": [0.1, 0.2], "note": "x"}}
    assert m._max_rel_diff(a, {"CR2": {"dims": {"W": 8.370809602004696}, "faces": [0.1, 0.2], "note": "x"}}) < m.REDUCTION_RTOL
    assert m._max_rel_diff(a, {"CR2": {"dims": {"W": 8.371}, "faces": [0.1, 0.2], "note": "x"}}) > m.REDUCTION_RTOL
    assert m._max_rel_diff(a, {"CR2": {"dims": {"W": 8.370809602004694}, "faces": [0.1], "note": "x"}}) == float("inf")
    assert m._max_rel_diff(a, {"CR2": {"dims": {"W": 8.370809602004694}, "faces": [0.1, 0.2], "note": "y"}}) == float("inf")
