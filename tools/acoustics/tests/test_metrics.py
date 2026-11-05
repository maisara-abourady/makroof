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
    worst = (0.0, "")
    for seed in (0, 1):
        h = signals.synthetic_decay(FS, t60, seed=seed, noise_floor_db=NOISE_FLOOR_DB)
        result = metrics.room_metrics(h, FS)
        for fc in bands.OCTAVE_BANDS_HZ:
            theirs = pra_exp.measure_rt60(bands.filter_band(h, FS, fc), fs=FS, decay_db=30)
            ours = result["bands"][bands.band_key(fc)]["T30"]
            assert ours == pytest.approx(theirs, rel=0.05), f"T60={t60} seed={seed} {fc} Hz"
            worst = max(worst, (abs(ours / theirs - 1.0), f"seed {seed}, {fc} Hz"))
    print(f"T60={t60}: worst |ours/pyroomacoustics - 1| = {100 * worst[0]:.4f}% ({worst[1]})")
    # Margin guard (review question 2): with an 80 dB noise floor both see the same EDC, and the
    # worst case measured over all T60s, seeds and bands is 0.0085%. A drift towards the ±5% bound
    # shows here long before the criterion flips.
    assert worst[0] < 0.001, worst


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


# --------------------------------------------------------------------------------------------
# Per-band energy ratios (review blocker 1): the band clarity must not depend on how close the
# direct sound is to the start of the file, and must match the analytic value per band.
# --------------------------------------------------------------------------------------------


def _delta_plus_decay(t60, direct_to_decay_db, lead_s, seed, b2=1e-4):
    decay_total = _energy_decay_analytic(t60, 0.0, math.inf, b2)
    a2 = decay_total * 10.0 ** (direct_to_decay_db / 10.0)
    h = np.concatenate([[math.sqrt(a2)], _random_sign_exponential(t60, 2.0 * t60, seed=seed)[1:] * math.sqrt(b2)])
    return np.concatenate([np.zeros(int(round(lead_s * FS))), h]), a2, b2


def test_band_energy_ratios_do_not_depend_on_the_lead_in():
    # The same IR with the direct sound at sample 0, 1 ms and 10 ms into the file. Before the fix
    # the band C80 at lead 0 read 1.4-5.2 dB low (half the direct sound's band energy was dropped).
    results = [metrics.room_metrics(_delta_plus_decay(1.0, 10.0, lead, seed=3)[0], FS) for lead in (0.0, 0.001, 0.010)]
    for fc in bands.OCTAVE_BANDS_HZ:
        key = bands.band_key(fc)
        for name in ("C50", "C80", "D50", "DRR", "T30"):
            values = [r["bands"][key][name] for r in results]
            if values[0] is None:
                assert all(v is None for v in values), (key, name, values)
                continue
            for v in values[1:]:
                assert v == pytest.approx(values[0], rel=1e-9, abs=1e-9), (key, name, values)


# Ensemble size and per-band tolerance for the analytic per-band test. The ensemble removes the
# random band energy of the noise decay (at R = 300 the remaining scatter, measured over 5 seed
# sets, has zero mean and reaches 0.12 dB from 250 Hz up and 0.36 dB at 63-125 Hz, where an octave
# holds only B * 50 ms ~ 2-4 degrees of freedom per realisation in the early part).
BAND_RATIO_ENSEMBLE = 300


def _ratio_tolerance_db(fc: float) -> float:
    return 0.5 if fc < 200.0 else 0.2


@pytest.mark.parametrize("direct_to_decay_db", [0.0, 10.0])
def test_band_energy_ratios_match_analytic(direct_to_decay_db):
    t60 = 0.5
    irs, a2, b2 = [], None, None
    for i in range(BAND_RATIO_ENSEMBLE):
        h, a2, b2 = _delta_plus_decay(t60, direct_to_decay_db, 0.0, seed=10_000 + i)
        irs.append(h)
    result = metrics.room_metrics_ensemble(irs, FS)

    def clarity(ms):
        t = ms / 1000.0
        return 10.0 * math.log10((a2 + _energy_decay_analytic(t60, 0.0, t, b2)) / _energy_decay_analytic(t60, t, math.inf, b2))

    total = a2 + _energy_decay_analytic(t60, 0.0, math.inf, b2)
    d50 = (a2 + _energy_decay_analytic(t60, 0.0, 0.05, b2)) / total
    half = metrics.DIRECT_HALF_WINDOW_S
    drr = 10.0 * math.log10((a2 + _energy_decay_analytic(t60, 0.0, half, b2)) / _energy_decay_analytic(t60, half, math.inf, b2))

    for fc in bands.OCTAVE_BANDS_HZ:
        band = result["bands"][bands.band_key(fc)]
        tol = _ratio_tolerance_db(fc)
        assert band["C80"] == pytest.approx(clarity(80.0), abs=tol), f"C80 {fc} Hz"
        assert band["C50"] == pytest.approx(clarity(50.0), abs=tol), f"C50 {fc} Hz"
        assert band["D50"] == pytest.approx(d50, abs=0.005 if fc > 200.0 else 0.012), f"D50 {fc} Hz"
        if bands.impulse_energy_within(FS, fc, half) >= metrics.DRR_MIN_BAND_RESOLUTION:
            assert band["DRR"] == pytest.approx(drr, abs=0.2), f"DRR {fc} Hz"
        else:
            assert band["DRR"] is None
            assert any(w.startswith("DRR:") for w in band["warnings"])


def test_per_band_drr_needs_a_band_that_resolves_the_window():
    # AX13: at 48 kHz, 1 kHz and up resolve ±2.5 ms; 63-500 Hz don't.
    resolved = [fc for fc in bands.OCTAVE_BANDS_HZ if bands.impulse_energy_within(FS, fc, metrics.DIRECT_HALF_WINDOW_S) >= 0.99]
    assert resolved == [1000.0, 2000.0, 4000.0, 8000.0]


# --------------------------------------------------------------------------------------------
# IRs that end in exact zeros (image-source IRs from Phase 03 on; review question 1)
# --------------------------------------------------------------------------------------------


def test_ir_ending_in_exact_zeros_is_noise_free_and_unbiased():
    full = signals.synthetic_decay(FS, 1.0, seed=5, duration_s=2.0)  # noise-free, down to -120 dB
    cut = full.copy()
    cut[int(1.0 * FS) :] = 0.0  # stops at -60 dB, then exact zeros
    a, b = metrics.room_metrics(full, FS), metrics.room_metrics(cut, FS)
    for fc in bands.OCTAVE_BANDS_HZ:
        key = bands.band_key(fc)
        # Filter ringing after the zeros is not mistaken for a noise floor.
        assert b["bands"][key]["noise_floor_db"] is None, b["bands"][key]
        assert b["bands"][key]["dynamic_range_db"] is None
        # Cutting below -60 dB changes T30 (-5..-35 dB) and C80 only by the missing tail energy.
        assert b["bands"][key]["T30"] == pytest.approx(a["bands"][key]["T30"], rel=0.002), key
        assert b["bands"][key]["C80"] == pytest.approx(a["bands"][key]["C80"], abs=0.01), key

    spikes = np.zeros(int(0.5 * FS))
    spikes[np.arange(20) * 1000 + 50] = 10.0 ** (-np.arange(20) / 10.0)  # 20 arrivals, 1 dB apart in level per 1000 samples
    result = metrics.room_metrics(spikes, FS)
    json.dumps(result)
    # Broadband ends in exact zeros: noise-free. (In the narrow bands the last spike's filter
    # ringing still reaches the final 10% of this short IR; that is band signal, and Lundeby then
    # reports it as the level the IR ends at. Simulated IRs should run well past their last arrival.)
    assert result["broadband"]["noise_floor_db"] is None
    assert result["bands"]["8000"]["noise_floor_db"] is None


# --------------------------------------------------------------------------------------------
# Different T60 per band (review major 2): octave-filter leakage, pinned and documented in
# metrics.py "Known limits". These are measurements of the analysis, not targets to tune.
# --------------------------------------------------------------------------------------------

_B = bands.OCTAVE_BANDS_HZ
PROFILES = {
    # Smooth, realistic profiles: every band within the T30 criterion's tolerance.
    "room": (dict(zip(_B, [0.7, 0.65, 0.6, 0.55, 0.5, 0.48, 0.45, 0.4])), {}),
    # Hall: T60 falls 1.3 -> 0.9 s from 4 to 8 kHz; 8 kHz reads ~+5% (leakage from 4 kHz).
    "hall": (dict(zip(_B, [2.4, 2.2, 2.0, 1.9, 1.8, 1.6, 1.3, 0.9])), {8000.0: (0.02, 0.08)}),
    # Contrast cases: a 2:1 step between 125 and 250 Hz, and a 1 kHz absorber dip.
    "step_2_to_1": (dict(zip(_B, [2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0])), {250.0: (0.14, 0.26)}),
    "dip_1k": (dict(zip(_B, [0.8, 0.8, 0.8, 0.8, 0.5, 0.8, 0.8, 0.8])), {1000.0: (0.12, 0.24)}),
}


@pytest.mark.parametrize("name", sorted(PROFILES))
def test_per_band_t60_profiles_and_their_leakage_bias(name):
    t60s, biased = PROFILES[name]
    irs = [signals.synthetic_decay(FS, t60s, seed=20_000 + i, noise_floor_db=-90.0) for i in range(60)]
    result = metrics.room_metrics_ensemble(irs, FS)
    for fc in _B:
        error = result["bands"][bands.band_key(fc)]["T30"] / t60s[fc] - 1.0
        if fc in biased:
            lo, hi = biased[fc]
            assert lo <= error <= hi, f"{name} {fc} Hz: leakage bias {100 * error:+.1f}% outside the documented {100 * lo:+.0f}..{100 * hi:+.0f}%"
        else:
            assert abs(error) <= 1.5 * _tolerance(fc), f"{name} {fc} Hz: {100 * error:+.1f}%"


def test_lundeby_ignores_exact_zero_gaps_in_a_sparse_early_part():
    """Phase 04 (metrics._upper_hull_db): a synthetic IR whose early part is a few isolated impulses
    with exact zeros between them, then an exponential noise decay with a noise floor. Without the
    hull, the first zero gap after the direct sound read as the noise floor (crosspoint after ~40 ms,
    T30 None); with it the T30 of the decay is recovered as for the same decay without the gaps."""
    fs = 48000.0
    rng = np.random.default_rng(4)
    n = int(2.0 * fs)
    t = np.arange(n) / fs
    t60 = 0.8
    tail = rng.standard_normal(n) * np.exp(-6.91 * t / t60) * 0.05
    tail[: int(0.08 * fs)] = 0.0  # the tail starts at 80 ms
    h = tail + 1e-6 * rng.standard_normal(n)
    gapped = h.copy()
    gapped[: int(0.08 * fs)] = 0.0  # exact zeros between the early impulses
    for t_i, a in ((0.0, 1.0), (0.012, 0.3), (0.031, 0.2), (0.064, 0.15)):
        gapped[int(t_i * fs)] = a
    lb = metrics.lundeby(gapped**2, fs)
    assert lb.crosspoint > int(1.0 * fs)  # well into the decay, not at the first gap
    t30 = metrics.room_metrics(gapped, fs)["broadband"]["T30"]
    assert t30 is not None and abs(t30 / t60 - 1.0) < 0.1


def test_upper_hull_leaves_a_monotonic_decay_unchanged():
    level = np.array([0.0, -3.0, -7.5, -12.0, -40.0, -60.0, -60.0])
    np.testing.assert_array_equal(metrics._upper_hull_db(level), level)
    np.testing.assert_array_equal(metrics._upper_hull_db(np.array([0.0, -3000.0, -10.0, -20.0])), [0.0, -10.0, -10.0, -20.0])
