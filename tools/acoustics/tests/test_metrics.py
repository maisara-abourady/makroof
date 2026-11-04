"""metrics.py against known answers (Phase 02 acceptance criteria) and against pyroomacoustics.

About the synthetic decays: a single realisation of "white noise x exponential envelope" does
not have exactly the nominal T60 in each octave band. Its band energy fluctuates on a time scale
of 1 / bandwidth, so the decay rate of that one realisation scatters around T60, by roughly
0.5 T60 / sqrt(B T60) (ISO 3382-2 Annex A). Measured here, one realisation's T30 scatters with a
standard deviation of 10% at 125 Hz and 18% at 63 Hz for T60 = 0.3 s, and still 1.8% at 125 Hz for
T60 = 6 s. That scatter belongs to the test signal, not to the analysis, and no estimator could
remove it: the decay really is different. pyroomacoustics measures exactly the same value on the
same realisation (test_agrees_with_pyroomacoustics_*).

So the accuracy test uses what ISO 3382-1 and -2 prescribe for random decays: the ensemble average
of decay curves, here ``room_metrics_ensemble`` over R independent realisations. R is chosen per
T60 so that the remaining statistical scatter of the ensemble estimate is at most ~0.6% (a third of
the ±2% tolerance) in the 125 Hz band: R >= (sigma_1 / 0.6%)^2 with the single-realisation sigma_1
measured above. What remains is the analysis chain's own bias (filterbank smearing, Lundeby
truncation, regression), which is what the ±2% / ±5% criterion is about.
"""

import json
import math

import numpy as np
import pyroomacoustics.experimental as pra_exp
import pytest

from tools.acoustics import bands, metrics, signals

FS = 48000.0
NOISE_FLOOR_DB = -80.0  # realistic but harmless: 80 dB of dynamic range in every band

# T60 -> number of realisations in the ensemble (see module docstring).
ENSEMBLE = {0.3: 300, 1.0: 130, 2.5: 48, 6.0: 24}


def _tolerance(fc: float) -> float:
    return 0.05 if fc < 100.0 else 0.02


@pytest.fixture(scope="module", params=sorted(ENSEMBLE), ids=lambda t: f"T60={t}s")
def ensemble(request):
    t60 = request.param
    irs = [signals.synthetic_decay(FS, t60, seed=1000 * i + 7, noise_floor_db=NOISE_FLOOR_DB) for i in range(ENSEMBLE[t60])]
    return t60, irs, metrics.room_metrics_ensemble(irs, FS)


def test_t30_recovers_known_t60(ensemble):
    t60, _, result = ensemble
    errors = {}
    for fc in bands.OCTAVE_BANDS_HZ:
        band = result["bands"][bands.band_key(fc)]
        assert band["T30"] is not None, band["warnings"]
        errors[fc] = band["T30"] / t60 - 1.0
    failing = {fc: f"{100 * e:+.2f}%" for fc, e in errors.items() if abs(e) > _tolerance(fc)}
    assert not failing, f"T30 off by more than ±2% (±5% at 63 Hz) for T60={t60}: {failing}"


def test_t20_and_edt_recover_known_t60(ensemble):
    # Not an acceptance criterion; looser bounds, since T20 and EDT use a shorter part of the decay.
    t60, _, result = ensemble
    for fc in bands.OCTAVE_BANDS_HZ:
        band = result["bands"][bands.band_key(fc)]
        assert band["T20"] == pytest.approx(t60, rel=2 * _tolerance(fc))
        assert band["EDT"] == pytest.approx(t60, rel=4 * _tolerance(fc))


def test_agrees_with_pyroomacoustics_on_the_ensemble(ensemble):
    t60, irs, result = ensemble
    for fc in bands.OCTAVE_BANDS_HZ:
        energy = np.mean([bands.filter_band(h, FS, fc) ** 2 for h in irs], axis=0)
        theirs = pra_exp.measure_rt60(np.sqrt(energy), fs=FS, decay_db=30)
        ours = result["bands"][bands.band_key(fc)]["T30"]
        assert ours == pytest.approx(theirs, rel=0.05), f"{fc} Hz"


@pytest.mark.parametrize("t60", sorted(ENSEMBLE))
def test_agrees_with_pyroomacoustics_on_single_realisations(t60):
    # Second opinion on exactly the signal we analyse: same band signal, independent Schroeder
    # integration and regression (pyroomacoustics: -5 to -35 dB, no noise compensation).
    for seed in (0, 1):
        h = signals.synthetic_decay(FS, t60, seed=seed, noise_floor_db=NOISE_FLOOR_DB)
        result = metrics.room_metrics(h, FS)
        for fc in bands.OCTAVE_BANDS_HZ:
            theirs = pra_exp.measure_rt60(bands.filter_band(h, FS, fc), fs=FS, decay_db=30)
            ours = result["bands"][bands.band_key(fc)]["T30"]
            assert ours == pytest.approx(theirs, rel=0.05), f"T60={t60} seed={seed} {fc} Hz"


def _random_sign_exponential(t60: float, duration_s: float, seed: int = 0) -> np.ndarray:
    """b * 10^(-3 n / (fs T60)) with random signs: its energy per sample is exactly deterministic,
    so its broadband Schroeder curve is an exact exponential."""
    n = np.arange(int(duration_s * FS))
    signs = np.random.default_rng(seed).choice([-1.0, 1.0], n.size)
    return signs * 10.0 ** (-3.0 * n / (FS * t60))


@pytest.mark.parametrize("t60", [0.3, 1.0, 2.5, 6.0])
def test_broadband_decay_times_of_an_exact_exponential(t60):
    h = _random_sign_exponential(t60, 2.0 * t60)  # ends at -120 dB, noise-free
    bb = metrics.room_metrics(h, FS)["broadband"]
    for name in ("EDT", "T20", "T30"):
        assert bb[name] == pytest.approx(t60, rel=0.002), name


def _energy_decay_analytic(t60: float, t0: float, t1: float, b2: float) -> float:
    """Continuous-time energy of b^2 fs 10^(-6 t / T60) between t0 and t1 (t1 may be inf)."""
    tau = t60 / (6.0 * math.log(10.0))
    upper = 0.0 if math.isinf(t1) else math.exp(-t1 / tau)
    return b2 * FS * tau * (math.exp(-t0 / tau) - upper)


@pytest.mark.parametrize("t60", [0.5, 1.0, 2.0])
@pytest.mark.parametrize("direct_to_decay_db", [-10.0, 0.0, 10.0])
def test_energy_ratios_of_delta_plus_decay_match_analytic(t60, direct_to_decay_db):
    # h = direct impulse of amplitude A at t = 0, then an exponential decay from the next sample.
    b2 = 1e-4
    decay_total = _energy_decay_analytic(t60, 0.0, math.inf, b2)
    a2 = decay_total * 10.0 ** (direct_to_decay_db / 10.0)
    h = np.concatenate([[math.sqrt(a2)], _random_sign_exponential(t60, 2.0 * t60, seed=3)[1:] * math.sqrt(b2)])
    bb = metrics.room_metrics(h, FS)["broadband"]

    def clarity(ms):
        t = ms / 1000.0
        return 10.0 * math.log10((a2 + _energy_decay_analytic(t60, 0.0, t, b2)) / _energy_decay_analytic(t60, t, math.inf, b2))

    assert bb["C80"] == pytest.approx(clarity(80.0), abs=0.2)
    assert bb["C50"] == pytest.approx(clarity(50.0), abs=0.2)
    d50 = (a2 + _energy_decay_analytic(t60, 0.0, 0.05, b2)) / (a2 + decay_total)
    assert bb["D50"] == pytest.approx(d50, abs=0.005)
    half = metrics.DIRECT_HALF_WINDOW_S
    drr = 10.0 * math.log10((a2 + _energy_decay_analytic(t60, 0.0, half, b2)) / _energy_decay_analytic(t60, half, math.inf, b2))
    assert bb["DRR"] == pytest.approx(drr, abs=0.2)


def test_lundeby_handles_a_high_noise_floor():
    # T60 = 1 s under a -50 dB noise floor: the decay meets the noise at 50/60 s.
    t60, floor_db = 1.0, -50.0
    irs = [signals.synthetic_decay(FS, t60, seed=s, noise_floor_db=floor_db, duration_s=3.0) for s in range(40)]
    result = metrics.room_metrics_ensemble(irs, FS)
    for fc in bands.OCTAVE_BANDS_HZ:
        band = result["bands"][bands.band_key(fc)]
        assert band["T30"] == pytest.approx(t60, rel=0.03), f"{fc} Hz: {band['warnings']}"
        assert band["crosspoint_s"] == pytest.approx(-floor_db / 60.0 * t60, abs=0.05)
        # Noise level estimate matches the noise alone, filtered the same way, within 1 dB.
        noise = np.random.default_rng(1_000_003).standard_normal(irs[0].size) * 10.0 ** (floor_db / 20.0)
        expected = 10.0 * np.log10(np.mean(bands.filter_band(noise, FS, fc) ** 2))
        assert band["noise_floor_db"] == pytest.approx(expected, abs=1.0)

        # Without truncation and compensation the noise flattens the EDC and T30 is far too long:
        # proof that the compensation is doing the work.
        energy = np.mean([bands.filter_band(h, FS, fc) ** 2 for h in irs], axis=0)
        plain = metrics.decay_time(metrics.schroeder_edc(energy, energy.size), FS, -5.0, -35.0)
        assert plain > 1.2 * t60


def test_insufficient_dynamic_range_gives_none_with_a_reason():
    # -40 dB noise floor (~40 dB dynamic range): enough for EDT (20 dB) and T20 (35 dB), not T30 (45 dB).
    h = signals.synthetic_decay(FS, 1.0, seed=1, noise_floor_db=-40.0, duration_s=3.0)
    band = metrics.room_metrics(h, FS)["bands"]["1000"]
    assert band["T30"] is None
    assert band["T20"] is not None and band["EDT"] is not None
    assert any("T30: dynamic range" in w for w in band["warnings"])
    # -30 dB: T20 goes too, EDT stays.
    h = signals.synthetic_decay(FS, 1.0, seed=1, noise_floor_db=-30.0, duration_s=3.0)
    band = metrics.room_metrics(h, FS)["bands"]["1000"]
    assert band["T30"] is None and band["T20"] is None
    assert band["EDT"] is not None


def test_delta_ir_and_short_irs():
    # The Phase 02 stub IR is a single unit sample: decay times are undefined, nothing crashes.
    result = metrics.room_metrics(np.array([1.0]), FS)
    assert result["broadband"]["T30"] is None
    assert result["broadband"]["DRR"] is None  # no reverberant energy at all
    assert result["onset_s"] == 0.0
    with pytest.raises(ValueError):
        metrics.room_metrics(np.zeros(100), FS)


def test_onset_and_time_origin():
    # A decay that starts 0.1 s into the file gives the same clarity as one that starts at 0.
    h = _random_sign_exponential(1.0, 2.0)
    late = np.concatenate([np.zeros(int(0.1 * FS)), h])
    a = metrics.room_metrics(h, FS)["broadband"]
    b = metrics.room_metrics(late, FS)
    assert b["onset_s"] == pytest.approx(0.1)
    assert b["broadband"]["C80"] == pytest.approx(a["C80"], abs=1e-6)
    assert b["broadband"]["T30"] == pytest.approx(a["T30"], rel=1e-6)


def test_result_is_json_serialisable():
    h = signals.synthetic_decay(FS, 0.5, seed=0, noise_floor_db=-70.0)
    result = metrics.room_metrics(h, FS)
    text = json.dumps(result)
    assert "NaN" not in text and "Infinity" not in text
    assert set(result["bands"]) == {bands.band_key(fc) for fc in bands.OCTAVE_BANDS_HZ}
    for band in result["bands"].values():
        assert {"EDT", "T20", "T30", "C50", "C80", "D50", "DRR"} <= set(band)
