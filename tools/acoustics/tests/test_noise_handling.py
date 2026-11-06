"""Phase-05 scope 7 (decider D5, E3, N1): the measured-IR noise handling and the simulated EDC.

Paired noise test, case A: |mean paired T30 bias| <= 0.6 % with SE <= 0.15 % in each of 18
conditions (500 Hz, 1 kHz, 2 kHz x T = 1, 2 s x noise 48, 55, 65 dB below the decay). Measured
on this branch (tools/acoustics/data/phase05_meter_checks.json): every 48 dB condition reads
+1.8 ... +2.1 % and 500 Hz / 1 s / 55 dB +0.60 %, against the plan's predicted +0.23 % at 48 dB.
The cause is the noise energy integrated between the -35 dB point and the Lundeby crosspoint (one
correction only, no noise subtraction, as specified); removing the upper hull changes it by
< 0.05 points. Those conditions are strict xfails pending a plan decision (PR, "Plan decisions
needed"); if they start passing, the test says so. Case B (125 Hz, T = 0.3 s) is reported only.
"""

import pytest

from tools.acoustics import meter_checks as m

FAILING = {(500.0, 1.0, 48.0), (500.0, 2.0, 48.0), (1000.0, 1.0, 48.0), (1000.0, 2.0, 48.0), (2000.0, 1.0, 48.0),
           (2000.0, 2.0, 48.0), (500.0, 1.0, 55.0)}


def _params():
    for k, c in enumerate(m.CASE_A):
        marks = [pytest.mark.xfail(strict=True, reason="phase-05 paired noise test: measured bias above 0.6 % "
                                   "(noise energy before the crosspoint), plan decision pending")] if c in FAILING else []
        yield pytest.param(k, c, marks=marks, id=f"{c[0]:.0f}Hz-T{c[1]}-{c[2]:.0f}dB")


@pytest.mark.parametrize("k,cond", list(_params()))
def test_paired_noise_case_a(k, cond):
    fc, T, L = cond
    res = m.paired_noise_test([cond], seed=7070 + 1000 * k)[0]  # same seeds as run_meter_checks
    assert res["unsuitable"] == 0, "a realisation returned T30 None: condition unsuitable"
    assert res["se_pct"] <= 0.15
    assert abs(res["mean_bias_pct"]) <= 0.6, res


def test_simulated_edc_within_0_01_db_of_integration_to_the_end():
    r = m.simulated_edc_check()
    assert abs(r["difference_dB"]) <= 0.01, r


def test_two_term_model_reproduces_the_plan_values():
    # phase-05 Assumptions in force: 0.42 % at D = 15 dB, 1.2 % at D = 10 dB, r = 1.1
    assert 100 * m.two_term_bias(1.1, 15.0) == pytest.approx(0.42, abs=0.01)
    assert 100 * m.two_term_bias(1.1, 10.0) == pytest.approx(1.2, abs=0.05)
    assert m.two_term_bias(1.0, 10.0) == 0.0
