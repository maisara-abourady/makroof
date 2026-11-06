"""Phase-05 nightly gate (scope 4): the simulated metrics of every validation scene against the
baseline tests/golden/validation_baseline.json, in either direction: T30 / T20 / EDT ±2 %
relative (octave meter, all bands; AX23 half-octave meter at 1-8 kHz, decider D4), C80 ±0.2 dB
(octave only). These are change-detection limits (0.4 and 0.2 of the Vorländer Table 6.1 jnds),
not perceptual ones. An intended change updates the baseline only through
tools/ci/update_goldens.py with a reason.

Marked ``nightly`` (the python CI job deselects it; .github/workflows/nightly.yml runs it, and on
the PRs that touch the validation). Needs render_cli; the bias test needs a debug-build render_cli
(MAKROOF_DEBUG_RENDER_CLI), where the MAKROOF_TEST_BIAS_T60 hook exists.
"""

import json
import os
import pathlib

import pytest

from tools.acoustics import golden, render_cli
from tools.validation import run_validation as rv

pytestmark = pytest.mark.nightly

NAME = "validation_baseline"
TOLERANCES = {
    "T30": {"rel": 0.02}, "T20": {"rel": 0.02}, "EDT": {"rel": 0.02},
    "T30_half": {"rel": 0.02}, "EDT_half": {"rel": 0.02}, "C80": {"abs": 0.2},
}
DESCRIPTION = ("Phase 05 nightly gate: simulated T30/T20/EDT (octave, and half-octave at 1-8 kHz) and C80 of "
               "the BRAS validation scenes (tests/scenes/validation), render_cli --mode omni at 44.1 kHz, emitter L. "
               "Change detection only (±2 %, ±0.2 dB). The recorded sim-meas errors are in "
               "tools/validation/data/phase05_results.json (reported, never gating).")


def _binary():
    b = render_cli.find_render_cli()
    if b is None:
        pytest.skip("render_cli not built")
    return b


def test_simulated_metrics_match_the_baseline():
    actual = rv.simulated_metrics(_binary())
    golden.assert_golden(NAME, actual, description=DESCRIPTION, tolerances=TOLERANCES)


def _bias_scenes():
    # one initial-alpha scene per room keeps the debug-build run short
    seen, out = set(), []
    for sc in rv.scene_list():
        if sc["alpha_set"] == "initial" and sc["room"] not in seen:
            seen.add(sc["room"])
            out.append(sc)
    return out


def test_t60_bias_hook_fails_the_gate_on_t30():
    """With MAKROOF_TEST_BIAS_T60=1.05 (debug builds only) the gate fails on T30, and the octave
    T30 at 500 Hz / 1 kHz / 2 kHz rises by +3 ... +5.5 % in every band with
    T30 >= 3 (t_mix,e - t_dir,e); at least one band per scene must qualify."""
    dbg = os.environ.get("MAKROOF_DEBUG_RENDER_CLI")
    if not dbg:
        if os.environ.get("MAKROOF_REQUIRE_BRAS") == "1":
            pytest.fail("MAKROOF_DEBUG_RENDER_CLI not set")
        pytest.skip("needs a debug render_cli (MAKROOF_DEBUG_RENDER_CLI)")
    dbg = pathlib.Path(dbg)
    baseline = json.loads(golden.golden_path(NAME).read_text())["metrics"]
    for sc in _bias_scenes():
        unbiased = rv.analyse(rv.render(dbg, sc["path"]), rv.FS)
        os.environ["MAKROOF_TEST_BIAS_T60"] = "1.05"
        try:
            biased = rv.analyse(rv.render(dbg, sc["path"]), rv.FS)
        finally:
            del os.environ["MAKROOF_TEST_BIAS_T60"]
        actual = {sc["name"]: {k: {q: v[q] for q in ("T30", "T20", "EDT", "C80", "T30_half", "EDT_half") if q in v}
                               for k, v in biased["bands"].items()}}
        report = golden.compare_to_golden(NAME, actual, {"tolerances": TOLERANCES, "metrics": {sc["name"]: baseline[sc["name"]]}})
        assert any(m.path.endswith(".T30") for m in report.mismatches), f"{sc['name']}: the gate did not fail on T30"
        e0 = rv.diagnostics(dbg, sc["path"])["emitters"][0]
        span = e0["handoverS"] - e0["directS"]
        qualifying = 0
        for fc in rv.AQ9_BANDS:
            k = rv.bands.band_key(fc)
            t0, t1 = unbiased["bands"][k]["T30"], biased["bands"][k]["T30"]
            if t0 is None or t1 is None or t0 < 3 * span:
                continue
            qualifying += 1
            rise = 100 * (t1 / t0 - 1)
            assert 3.0 <= rise <= 5.5, f"{sc['name']} {k} Hz: T30 rose {rise:.2f} %"
        assert qualifying >= 1, f"{sc['name']}: no band with T30 >= 3 (t_mix - t_dir): unsuitable test scene"
