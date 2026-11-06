"""Phase-05 scope 7 (decider D5, E3, N1; Phase 05e decision D-C, AX27): the measured-IR noise
handling and the simulated EDC.

Paired noise test, case A, with AX27 noise subtraction: |mean paired T30 bias| <= 0.6 % with
SE <= 0.15 % in each of 18 conditions (500 Hz, 1 kHz, 2 kHz x T = 1, 2 s x noise L_min, 55, 65 dB
below the decay), no realisation 'unsuitable' (T30 None). L_min follows AX27's rule (the lowest
level, in 1 dB steps from 51 dB, with median - 3 SD of the noise margin >= 45 dB in every
condition); ``test_l_min_is_the_lowest_level_meeting_the_ax27_rule`` checks the constant against
the rule. The former 48 dB level, 51 dB, case B, EDT and C80 are reported (run_meter_checks), not
gated. Seeds are fixed per condition, so the test is deterministic.
"""

import functools

import pytest

from tools.acoustics import meter_checks as m


@functools.lru_cache(maxsize=None)
def _result(cond):
    return m.paired_noise_test([cond])[0]  # same seeds as run_meter_checks (condition_seed)


CONDS = [pytest.param(c, id=f"{c[0]:.0f}Hz-T{c[1]}-{c[2]:.0f}dB") for c in m.CASE_A]


def test_case_a_has_18_conditions_at_l_min_55_65():
    assert len(m.CASE_A) == 18
    assert sorted({c[2] for c in m.CASE_A}) == sorted({m.L_MIN_DB, 55.0, 65.0})


@pytest.mark.parametrize("cond", CONDS)
def test_paired_noise_case_a_bias(cond):
    res = _result(cond)
    assert res["noise_subtraction"]
    assert res["se_pct"] <= 0.15, res
    assert abs(res["mean_bias_pct"]) <= 0.6, res


@pytest.mark.parametrize("cond", CONDS)
def test_paired_noise_case_a_every_realisation_is_suitable(cond):
    assert _result(cond)["unsuitable"] == 0, "a realisation returned T30 None: condition unsuitable"


def _worst_margin(level):
    rows = [m.paired_noise_condition(fc, T, level, 51, m.condition_seed(fc, T, level)) for fc, T in m.CASE_A_FC_T]
    return min(r["margin_median_minus_3sd_dB"] for r in rows)


def test_l_min_is_the_lowest_level_meeting_the_ax27_rule():
    assert m.L_MIN_DB >= m.L_MIN_PLAN_DB
    assert _worst_margin(m.L_MIN_DB) >= m.MARGIN_REQUIRED_DB
    if m.L_MIN_DB > m.L_MIN_PLAN_DB:
        assert _worst_margin(m.L_MIN_DB - 1.0) < m.MARGIN_REQUIRED_DB


def test_simulated_edc_within_0_01_db_of_integration_to_the_end():
    r = m.simulated_edc_check()  # AX27 on
    assert abs(r["difference_dB"]) <= 0.01, r


def test_ax27_is_off_by_default_and_no_op_without_noise():
    import numpy as np

    from tools.acoustics import metrics

    rng = np.random.default_rng(3)
    fs = 48000.0
    t = np.arange(int(1.2 * fs)) / fs
    h = rng.standard_normal(t.size) * np.exp(-6.91 * t / 0.8)
    h[int(0.9 * fs):] = 0.0  # exact zeros: noise-free, so the subtraction has nothing to remove
    a = metrics.room_metrics(h, fs)
    b = metrics.room_metrics(h, fs, noise_subtraction=True)
    assert a["bands"]["1000"]["T30"] == b["bands"]["1000"]["T30"]


def test_two_term_model_reproduces_the_plan_values():
    # phase-05 Assumptions in force: 0.42 % at D = 15 dB, 1.2 % at D = 10 dB, r = 1.1
    assert 100 * m.two_term_bias(1.1, 15.0) == pytest.approx(0.42, abs=0.01)
    assert 100 * m.two_term_bias(1.1, 10.0) == pytest.approx(1.2, abs=0.05)
    assert m.two_term_bias(1.0, 10.0) == 0.0


def test_leak_calibration_smoke():
    """leak_calibration runs in CI (reduced R): the octave meter reads the slower neighbour long,
    the two-term model tracks it, the half-octave meter does not (full run: run_meter_checks)."""
    rows = m.leak_calibration(fc_list=(1000.0,), ratios=(1.5,), r_count=12)
    assert len(rows) == 2  # neighbour below and above
    for r in rows:
        assert r["octave_bias_pct"] > 2.0  # leakage is visible at r = 1.5
        assert abs(r["residual_pct"]) < 1.5  # model within a loose, R = 12 bound
        assert abs(r["half_octave_bias_pct"]) < 2.0
        assert 10.0 < r["D_dB"] < 25.0
