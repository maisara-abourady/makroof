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


def test_obb_axis_is_a_direction_whatever_edge_wins():
    """phase-05f: the same rectangle reached from antiparallel hull edges (CR4 on two CPUs) must
    report the same long-axis direction, in [-45°, 135°)."""
    import math

    from tools.validation import make_bras_scenes as m

    rect = [[0.0, 0.0], [33.3, 0.0], [33.3, 33.1], [0.0, 33.1]]
    angles = set()
    for k in range(4):
        for hull in (rect[k:] + rect[:k], list(reversed(rect[k:] + rect[:k]))):
            o = m.oriented_bounding_rectangle(hull)
            assert o["long"] == pytest.approx(33.3) and o["short"] == pytest.approx(33.1)
            d = math.degrees(o["long_axis_rad"])
            assert -45.0 <= d < 135.0
            angles.add(round(d, 9))
    assert angles == {0.0}
    tall = m.oriented_bounding_rectangle([[0.0, 0.0], [10.0, 0.0], [10.0, 20.0], [0.0, 20.0]])
    assert math.degrees(tall["long_axis_rad"]) == pytest.approx(90.0)


def test_reduction_check_ignores_rounding_residue_but_not_real_changes():
    """phase-05f: residues ~1e-15 (r_error_m) differ in sign between CPUs; they must not fail
    --check, while a real change of a small quantity still does."""
    from tools.validation import make_bras_scenes as m

    assert m._max_rel_diff({"r_error_m": 8.881784197001252e-16}, {"r_error_m": -1.7763568394002505e-15}) == 0.0
    assert m._max_rel_diff({"x": 1e-6}, {"x": 2e-6}) > m.REDUCTION_RTOL
    assert m._max_rel_diff({"x": 1.0}, {"x": 1.0 + 1e-8}) > m.REDUCTION_RTOL


def test_kernel_built_per_variant_gives_the_same_envelopes(monkeypatch):
    """phase-05f: scope6.run_pairs_in_budget builds the reference-hybrid kernel one material
    variant at a time above its memory budget (CR4). The variants are independent columns of the
    kernel, so the envelopes must equal the joint build."""
    import numpy as np

    from tools.acoustics import ref_hybrid as rh
    from tools.validation import scope6

    dims, pairs = (5.0, 4.0, 3.0), [([1.0, 1.0, 1.0], [3.0, 2.5, 1.5]), ([4.0, 3.0, 2.0], [1.5, 1.0, 1.2])]
    variants = [rh.variant([[0.2] * 8] * 6, [0.3] * 6, [0.001] * 8),
                rh.variant([[0.1, 0.1, 0.15, 0.2, 0.3, 0.35, 0.4, 0.45]] * 6, [0.6] * 6, [0.002] * 8)]
    joint, _ = rh.run_pairs(dims, variants, pairs, 0.04, 2.0)
    monkeypatch.setattr(scope6, "KERNEL_BUDGET_BYTES", 0)
    monkeypatch.setattr(scope6, "log", lambda *a, **k: None)
    split, info = scope6.run_pairs_in_budget(dims, variants, pairs, 0.04, 2.0)
    assert info["variants_built_separately"]
    np.testing.assert_array_equal(split, joint)  # same float32 accumulation per column: bit-identical
