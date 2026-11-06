"""Decay predictors (phase-05 scope 6; tools/acoustics/radiosity.py).

a* criterion as decided in D-B (2026-11-06, phase-05.md; vetoable by Maisara): a*, with patches
halved from 96 (cube) / 88 (1:2:3) equal elements until T changes by < 0.4 % per halving, agrees
within ±1 % in all six Kuttruff Table 5.2 cases with an independent Lambert-particle Monte Carlo
(``lambert_mc_t60``: no patches, no form factors) at SE <= 0.25 % per case. γ²-Eyring, the Table 5.2
Iteration column, the 88/96-element result and Fig. 5.10's case-4 value are reported, not gated
(the case-4 gap is 'unresolved', ledger DB-1).

The full run (case 6 converges only at 5632 patches, ≈ 6 min and ≈ 5 GB) is
``python -m tools.acoustics.radiosity``, committed as tools/acoustics/data/phase05e_a_star.json.
This file gates on that record and, on every CI OS, recomputes each case's solver history up to
1 600 patches and the first Monte Carlo seed, which must reproduce the record; the nightly workflow
re-runs the whole gate (``slow``).
"""

import json
import pathlib

import numpy as np
import pytest

from tools.acoustics import radiosity as r

# Kuttruff Table 5.2: (case, dims [W, D, H] with AQ1 axes, alpha per face in FACE_NAMES order,
# Eyring, Iteration, element size giving 96 (cube) / 88 (1:2:3) equal elements).
# 10 x 20 x 30 m: H = 10, floor 20 x 30; x-walls 30 x 10 (long side), y-walls 20 x 10 (short side).
TABLE_5_2 = [
    (1, (10, 10, 10), [1 / 6] * 6, 1.47, 1.55, 2.5),
    (2, (10, 10, 10), [0, 0, 0, 0, 1, 0], 1.47, 1.35, 2.5),
    (3, (20, 30, 10), [3 / 11] * 6, 1.38, 1.52, 5.0),
    (4, (20, 30, 10), [0, 0, 0, 0, 1, 0], 1.38, 1.21, 5.0),
    (5, (20, 30, 10), [1, 0, 0, 0, 0, 0], 2.99, 3.06, 5.0),
    (6, (20, 30, 10), [0, 0, 1, 0, 0, 0], 4.61, 5.93, 5.0),
]


def _t_iter(dims, alpha, size):
    p = r.box_patches(dims, size)
    a = r.a_star(dims, 1 - np.asarray(alpha)[p.face], p)
    return r.t60_from_a(dims, a), len(p.areas)


def test_element_counts_match_the_phase_file():
    assert len(r.box_patches((10, 10, 10), 2.5).areas) == 96
    assert len(r.box_patches((20, 30, 10), 5.0).areas) == 88


def test_form_factor_closure_and_mean_free_path():
    dims = (20, 30, 10)
    p = r.box_patches(dims, 5.0)
    F, (R, W) = r.form_factors(p)
    np.testing.assert_allclose(F.sum(axis=1), 1.0, atol=1e-9)
    # reciprocity A_k F_kl = A_l F_lk
    A = p.areas
    np.testing.assert_allclose(A[:, None] * F, (A[:, None] * F).T, rtol=1e-4, atol=1e-9)  # quadrature
    # Kuttruff Eq. 5.12: mean free path 4V/S
    mean = (A[:, None] * F * (W * R).sum(2)).sum() / A.sum()
    assert mean == pytest.approx(4 * 6000 / 2200, rel=0.01)


def test_eyring_limit_for_uniform_absorption_and_no_path_variance():
    # With uniform rho and every path length set to lbar, a* is exactly -ln(rho) (Eyring).
    dims = (10, 10, 10)
    p = r.box_patches(dims, 5.0)
    F, (R, W) = r.form_factors(p)
    lbar = 4 * 1000 / 600
    a = r.a_star(dims, np.full(len(p.areas), 0.8), p, F, (np.full_like(R, lbar), W))
    assert a == pytest.approx(-np.log(0.8), rel=1e-9)


@pytest.mark.parametrize("case", [c for c in TABLE_5_2 if c[0] in (1, 3)], ids=lambda c: f"case{c[0]}")
def test_uniform_cases_match_gamma2_eyring(case):
    """For uniform alpha the radiosity decay is set by the path-length statistics: Kuttruff
    Eqs. 5.33-5.34 with Table 5.1's gamma^2 (1:2:3 interpolated, 0.376)."""
    _, dims, alpha, _, _, size = case
    t, _ = _t_iter(dims, alpha, size)
    g2, _ = r.gamma2_table(dims)
    assert t == pytest.approx(r.gamma2_eyring_t60(dims, alpha, g2), rel=0.01)


@pytest.mark.parametrize("case", [c for c in TABLE_5_2 if c[0] in (2, 4, 5, 6)], ids=lambda c: f"case{c[0]}")
def test_absorbing_face_cases_match_independent_monte_carlo(case):
    _, dims, alpha, _, _, _ = case
    t_conv, _ = _t_iter(dims, alpha, 2.5)  # converged to < 0.5 % at 2.5 m for these rooms
    absorbing = [i for i, a in enumerate(alpha) if a == 1]
    t_mc, _ = r.diffuse_mc_t60(dims, absorbing, n=200_000, seed=7)
    assert t_conv == pytest.approx(t_mc, rel=0.02)


RECORD = pathlib.Path(r.__file__).resolve().parent / "data" / "phase05e_a_star.json"


def _record():
    return {c["case"]: c for c in json.loads(RECORD.read_text())["cases"]}


def _check_gate_row(c):
    assert c["solver_converged"], c["solver_history"]
    h = c["solver_history"]
    assert abs(h[-1]["T60_s"] / h[-2]["T60_s"] - 1) < r.D_B_CONVERGENCE
    assert h[0]["patches"] == (96 if c["dims"] == [10, 10, 10] else 88)
    assert c["mc"]["se_rel"] <= r.D_B_SE, c["mc"]
    assert abs(c["solver_T60_s"] / c["mc"]["T60_s"] - 1) <= r.D_B_TOL, c


@pytest.mark.parametrize("case", [c[0] for c in r.TABLE_5_2], ids=lambda c: f"case{c}")
def test_a_star_agrees_with_the_independent_monte_carlo_within_1_percent(case):
    c = _record()[case]
    _check_gate_row(c)
    print(f"case {case}: a* {c['solver_T60_s']:.4f} s ({c['solver_history'][-1]['patches']} patches), MC {c['mc']['T60_s']:.4f} s "
          f"(SE {100 * c['mc']['se_rel']:.3f} %, {c['mc']['seeds']} x {c['mc']['n_per_seed']}), difference "
          f"{100 * c['difference_rel']:+.2f} %; reported: Iteration column {c['iteration_column_s']} s "
          f"({100 * c['iteration_column_vs_mc_rel']:+.2f} % vs MC), gamma2-Eyring {c['gamma2_eyring_s']:.4f} s "
          f"({100 * c['gamma2_eyring_vs_mc_rel']:+.2f} %), 88/96 elements {c['solver_88_96_s']:.4f} s"
          + (f", Fig. 5.10 {c['fig_5_10_s']} s ({c['case4_gap']})" if case == 4 else ""))


@pytest.mark.parametrize("case", [c for c in r.TABLE_5_2], ids=lambda c: f"case{c[0]}")
def test_record_reproduces_on_this_platform(case):
    """Solver levels up to 1 600 patches and the first MC seed, recomputed, equal the record."""
    n, dims, alpha, _, _, size = case
    c = _record()[n]
    for lvl in c["solver_history"]:
        if lvl["patches"] > 1600:
            continue
        t, count = _t_iter(dims, alpha, lvl["size_m"])
        assert count == lvl["patches"]
        assert t == pytest.approx(lvl["T60_s"], rel=1e-6)
    mc = r.mc_case(n, dims, alpha, seeds=[0])
    assert mc["T60_per_seed_s"][0] == pytest.approx(c["mc"]["T60_per_seed_s"][0], rel=1e-6)


@pytest.mark.slow
def test_full_gate_recomputed():
    """The whole D-B gate from scratch (nightly): every case converges and agrees within ±1 %."""
    rows = r.table_5_2_gate()
    for c in rows:
        _check_gate_row(c)


def test_gamma2_table_lookup():
    assert r.gamma2_table((10, 10, 10))[0] == pytest.approx(0.342)
    g, how = r.gamma2_table((20, 30, 10))
    assert g == pytest.approx(0.363 + (0.403 - 0.363) * (3 - 2) / (5 - 2))  # 0.376 (phase-05 example)
    assert how.startswith("interpolated")
    assert r.gamma2_table((7, 13, 29))[0] is None  # untabulated shape: only 0.4 applies
