"""compare.py: arrival times to the sample, amplitudes, band energies, metric deltas."""

import json

import numpy as np
import pytest

from tools.acoustics import bands, compare, signals

FS = 48000.0


def _spiky_ir(seed: int, n_spikes: int = 20, length: int = 24000, min_gap: int = 24):
    rng = np.random.default_rng(seed)
    positions = []
    while len(positions) < n_spikes:
        p = int(rng.integers(10, length - 10))
        if all(abs(p - q) >= min_gap for q in positions):
            positions.append(p)
    positions = np.sort(np.array(positions))
    amplitudes = 10.0 ** (rng.uniform(-40.0, 0.0, n_spikes) / 20.0) * rng.choice([-1.0, 1.0], n_spikes)
    ir = np.zeros(length)
    ir[positions] = amplitudes
    return ir, positions, amplitudes


@pytest.mark.parametrize("seed", range(5))
def test_detects_arrival_times_of_20_spikes_exactly(seed):
    ir, positions, _ = _spiky_ir(seed)
    found = compare.detect_peaks(ir, 20)
    assert np.array_equal(found, positions)


@pytest.mark.parametrize("seed", range(3))
def test_detects_band_limited_arrivals_with_a_matched_template(seed):
    # Spikes smeared by a band-limited pulse (windowed sinc, ~8 kHz) plus faint noise: with the
    # pulse as the matched-filter template, the arrivals are still found to the sample.
    ir, positions, _ = _spiky_ir(seed, min_gap=48)
    t = np.arange(-32, 33)
    pulse = np.sinc(t * 2 * 8000.0 / FS) * np.hanning(t.size)
    smeared = np.convolve(ir, pulse, mode="same")
    smeared += np.random.default_rng(99).standard_normal(smeared.size) * 1e-5
    found = compare.detect_peaks(smeared, 20, template=pulse, min_separation=24)
    assert np.array_equal(found, positions)


def test_compare_irs_reports_shifts_and_gains():
    ir, positions, _ = _spiky_ir(1)
    shifted = np.zeros_like(ir)
    shifted[3:] = 0.5 * ir[:-3]  # 3 samples later, -6.02 dB
    report = compare.compare_irs(ir, shifted, FS, peaks=20, with_metrics=False)
    assert [p["reference_index"] for p in report["peaks"]] == positions.tolist()
    assert all(p["delta_samples"] == 3 for p in report["peaks"])
    assert all(p["amplitude_db"] == pytest.approx(-6.0206, abs=1e-3) for p in report["peaks"])
    for value in report["band_energy_db"].values():
        assert value == pytest.approx(-6.0206, abs=0.01)


def test_missing_peak_is_reported_as_none():
    ir, positions, _ = _spiky_ir(2)
    test = ir.copy()
    test[positions[5]] = 0.0
    report = compare.compare_irs(ir, test, FS, peaks=20, with_metrics=False, match_window=0)
    row = report["peaks"][5]
    assert row["test_index"] is None and row["amplitude_db"] is None


def test_metric_deltas_of_identical_irs_are_zero_and_serialisable():
    h = signals.synthetic_decay(FS, 0.6, seed=3, noise_floor_db=-70.0)
    report = compare.compare_irs(h, h, FS, peaks=5)
    json.dumps(report)
    for band in report["metric_deltas"]["bands"].values():
        for value in band.values():
            assert value is None or value == pytest.approx(0.0, abs=1e-12)
    assert set(report["band_energy_db"]) == {bands.band_key(fc) for fc in bands.OCTAVE_BANDS_HZ}


def test_matched_filter_alignment():
    ir = np.zeros(100)
    ir[40] = 1.0
    template = np.array([0.1, 0.5, 1.0, 0.5, 0.1])
    smeared = np.convolve(ir, template, mode="same")
    mf = compare.matched_filter(smeared, template)
    assert int(np.argmax(mf)) == 40
