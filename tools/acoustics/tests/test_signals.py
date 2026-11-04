"""signals.py: each generator produces what its docstring promises."""

import numpy as np
import pytest

from tools.acoustics import bands, signals

FS = 48000.0


def test_generators_are_deterministic():
    assert np.array_equal(signals.pink_bursts(FS, seed=3), signals.pink_bursts(FS, seed=3))
    assert np.array_equal(signals.synthetic_decay(FS, 0.5, seed=4), signals.synthetic_decay(FS, 0.5, seed=4))
    assert not np.array_equal(signals.synthetic_decay(FS, 0.5, seed=4), signals.synthetic_decay(FS, 0.5, seed=5))


def test_pink_noise_slope():
    x = signals.pink_noise(1 << 20, seed=1)
    assert np.sqrt(np.mean(x**2)) == pytest.approx(1.0)
    # Band energy of pink noise is the same in every octave (power ~ 1/f): within ±1 dB.
    energies = [10 * np.log10(np.mean(bands.filter_band(x, FS, fc) ** 2)) for fc in bands.OCTAVE_BANDS_HZ[1:]]
    assert np.ptp(energies) < 2.0


def test_pink_bursts_layout():
    x = signals.pink_bursts(FS, burst_s=0.5, gap_s=0.5, count=4, level_dbfs=-12.0)
    assert x.size == int(4 * FS)
    assert np.max(np.abs(x)) == pytest.approx(10 ** (-12 / 20))
    for i in range(4):
        start = int(i * FS)
        assert np.all(x[start + int(0.5 * FS) : start + int(FS)] == 0.0)  # gaps are silent
        assert x[start] == pytest.approx(0.0, abs=1e-3)  # faded in


def test_clicks_positions_and_level():
    x = signals.clicks(FS, interval_s=0.5, count=8, level_dbfs=-6.0)
    pos = signals.click_positions(FS, interval_s=0.5, count=8)
    assert np.array_equal(np.flatnonzero(x), pos)
    assert np.allclose(x[pos], 10 ** (-6 / 20))


def test_sweep_and_inverse_give_a_delta():
    f1, f2, dur = 50.0, 16000.0, 2.0
    sweep = signals.exp_sine_sweep(FS, f1, f2, dur)
    inv = signals.inverse_sweep(FS, f1, f2, dur)
    ir = signals.deconvolve(sweep, inv)
    peak = int(np.argmax(np.abs(ir)))
    assert peak == sweep.size - 1
    # Flat magnitude in band (±1 dB from 2*f1 to f2/2), unit gain at the centre.
    spectrum = np.abs(np.fft.rfft(ir, 1 << 19))
    f = np.fft.rfftfreq(1 << 19, 1 / FS)
    in_band = (f > 2 * f1) & (f < f2 / 2)
    assert np.all(np.abs(20 * np.log10(spectrum[in_band])) < 1.0)
    # Energy is concentrated at the peak: everything more than 5 ms away is 30 dB down.
    far = np.ones(ir.size, bool)
    far[peak - int(0.005 * FS) : peak + int(0.005 * FS)] = False
    assert np.max(np.abs(ir[far])) < np.abs(ir[peak]) * 10 ** (-30 / 20)


def test_sustained_tone_spectrum_and_level():
    x = signals.sustained_tone(FS, duration_s=4.0)
    assert np.max(np.abs(x)) == pytest.approx(10 ** (-12 / 20), rel=1e-3)
    seg = x[int(FS) : int(3 * FS)]  # 2 s, outside the fades: 0.5 Hz bins
    spectrum = np.abs(np.fft.rfft(seg))
    f = np.fft.rfftfreq(seg.size, 1 / FS)
    top = sorted(f[np.argsort(spectrum)[-3:]])
    assert top == [110.0, 220.0, 330.0]
    # Nothing above 1 kHz but rounding.
    assert np.max(spectrum[f > 1000]) < 1e-9 * np.max(spectrum)


def test_amplitude_modulated_tone():
    x = signals.sustained_tone(FS, duration_s=4.0, am_rate_hz=0.5, am_depth_db=6.0)
    # Peak of the envelope at t = 0.5 s (sin = 1): +6 dB over the unmodulated -12 dBFS.
    window = x[int(0.6 * FS) : int(0.6 * FS) + int(FS / 110)]
    assert np.max(np.abs(x)) == pytest.approx(10 ** (-6 / 20), rel=0.01)
    assert np.max(np.abs(window)) > 10 ** (-12 / 20)


@pytest.mark.parametrize("t60", [0.5, 2.0])
def test_synthetic_decay_envelope(t60):
    x = signals.synthetic_decay(FS, t60, seed=2)
    assert x.size == int(round((1.5 * t60 + 0.25) * FS))
    # Energy in 50 ms windows follows 10^(-6 t / T60) (averaged over the window), within 1 dB.
    win = int(0.05 * FS)
    for start_s in (0.1, 0.5 * t60, t60):
        start = int(start_s * FS)
        measured = 10 * np.log10(np.mean(x[start : start + win] ** 2))
        expected = -60.0 * (start_s + 0.025) / t60
        assert measured == pytest.approx(expected, abs=1.0)


def test_synthetic_decay_per_band_mapping_requires_all_bands():
    with pytest.raises(ValueError):
        signals.synthetic_decay(FS, {1000.0: 1.0})
    t60s = {fc: 0.4 + 0.1 * i for i, fc in enumerate(bands.OCTAVE_BANDS_HZ)}
    x = signals.synthetic_decay(FS, t60s, seed=0)
    assert x.size == int(round((1.5 * max(t60s.values()) + 0.25) * FS))


def test_to_stereo():
    a = np.arange(4.0)
    assert signals.to_stereo(a).shape == (4, 2)
    with pytest.raises(ValueError):
        signals.to_stereo(a, np.arange(3.0))
