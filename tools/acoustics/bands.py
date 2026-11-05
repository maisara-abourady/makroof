"""Octave-band filterbank.

The band set matches ``contract::kOctaveBandsHz`` in ``src/contract/SceneDescription.h`` (nominal
63 Hz to 8 kHz, 8 bands); ``tests/test_bands.py`` checks that the two lists agree.

Each band is a Butterworth band-pass of order 6 (``scipy.signal.butter(3, ...)``: 3 poles per edge,
i.e. 18 dB/octave skirts per pass) with edges at fc / sqrt(2) and fc * sqrt(2), applied
**zero-phase** (forward and backward, ``sosfiltfilt``), so the magnitude response is squared
(-6 dB at the edges, 36 dB/octave skirts) and the band signals have no group delay. Zero-phase
filtering keeps reflections at their true arrival times. Its impulse response is symmetric in time,
so it smears a decay in both directions instead of adding a one-sided ringing tail; the backward
pass is the "time-reversed" filtering that reduces filter bias on measured decays (Jacobsen and
Rindel, 1987). Short decays in the lowest bands are still affected: a band of bandwidth B needs
roughly B * T60 > 16 (Jacobsen's criterion) for the filter not to bias the result, so T60 = 0.3 s
in the 63 Hz band (B ~ 44 Hz, B * T60 ~ 13) is marginal. That is why the 63 Hz tolerance is looser.

Centre frequencies are exact base-2 octaves, 1000 * 2**k Hz (62.5, 125, ..., 8000), as in
IEC 61260-1 base-2 design; "63 Hz" is the nominal label of the 62.5 Hz band.
"""

from __future__ import annotations

import functools

import numpy as np
from scipy import signal

# Nominal centre frequencies in Hz. Same order and values as contract::kOctaveBandsHz.
OCTAVE_BANDS_HZ: tuple[float, ...] = (63.0, 125.0, 250.0, 500.0, 1000.0, 2000.0, 4000.0, 8000.0)

# Order of the band-pass prototype per edge passed to scipy.signal.butter (band order = 2 * this).
_BUTTER_N = 3


def exact_centre_hz(nominal_hz: float) -> float:
    """Exact base-2 centre frequency of a nominal octave band (63 -> 62.5, 1000 -> 1000)."""
    k = round(np.log2(nominal_hz / 1000.0))
    return 1000.0 * 2.0**k


def band_edges_hz(nominal_hz: float) -> tuple[float, float]:
    fc = exact_centre_hz(nominal_hz)
    return fc / np.sqrt(2.0), fc * np.sqrt(2.0)


@functools.lru_cache(maxsize=64)
def octave_sos(nominal_hz: float, fs: float) -> np.ndarray:
    """Second-order sections of the order-6 Butterworth band-pass for one octave band."""
    lo, hi = band_edges_hz(nominal_hz)
    if hi >= fs / 2.0:
        raise ValueError(f"{nominal_hz} Hz band (upper edge {hi:.0f} Hz) does not fit below fs/2 = {fs / 2:.0f} Hz")
    return signal.butter(_BUTTER_N, [lo, hi], btype="bandpass", fs=fs, output="sos")


def _pad_samples(nominal_hz: float, fs: float) -> int:
    # Enough zeros for the filter's ringing to die out (~40 periods of the lower edge), so the
    # zero-phase pass doesn't wrap edge transients into the signal.
    lo, _ = band_edges_hz(nominal_hz)
    return int(np.ceil(40.0 * fs / lo))


def filter_band_with_lead(x: np.ndarray, fs: float, nominal_hz: float) -> tuple[np.ndarray, int]:
    """Zero-phase octave-band filtering that keeps the anti-causal part of the response.

    Returns ``(y, lead)``: ``y`` has ``lead + len(x)`` samples and ``y[lead + n]`` lines up with
    ``x[n]``. The first ``lead`` samples hold the energy the zero-phase filter spreads *before*
    sample 0 (its impulse response is symmetric). For an impulse at sample 0 that is about half of
    its band energy (50% at 63 Hz up to 36% lost at 8 kHz), so any energy measure of a band near the
    start of a signal (C50, C80, D50, DRR, band energies) must use this, not ``filter_band``.
    The padding after the signal is cut off, so the end of ``y`` lines up with the end of ``x``.
    """
    x = np.asarray(x, dtype=np.float64)
    if x.ndim != 1:
        raise ValueError("filter_band expects a 1-D signal")
    pad = _pad_samples(nominal_hz, fs)
    padded = np.concatenate([np.zeros(pad), x, np.zeros(pad)])
    y = signal.sosfiltfilt(octave_sos(nominal_hz, fs), padded, padtype=None)
    return y[: pad + x.size], pad


def filter_band(x: np.ndarray, fs: float, nominal_hz: float) -> np.ndarray:
    """Zero-phase octave-band filtering of a 1-D signal; output has the same length as ``x``.

    The signal is zero-padded on both sides before filtering (instead of scipy's odd extension),
    so a signal that starts or stops abruptly is treated as silence outside its extent. The part of
    the response that falls before sample 0 is **dropped**: for energy that starts near sample 0
    that can be half of the band energy. Use ``filter_band_with_lead`` for energy measures; this
    function is for decay-rate analysis and signals that start well after sample 0.
    """
    y, lead = filter_band_with_lead(x, fs, nominal_hz)
    return y[lead:]


@functools.lru_cache(maxsize=256)
def impulse_energy_within(fs: float, nominal_hz: float, half_window_s: float) -> float:
    """Fraction of the band filter's (zero-phase) impulse-response energy within ±half_window_s of
    the impulse. A property of the filterbank: it says how well a band can resolve a short window."""
    pad = _pad_samples(nominal_hz, fs)
    x = np.zeros(2 * pad + 1)
    x[pad] = 1.0
    e = filter_band(x, fs, nominal_hz) ** 2
    w = int(round(half_window_s * fs))
    return float(np.sum(e[pad - w : pad + w + 1]) / np.sum(e))


def filter_bands(x: np.ndarray, fs: float, bands: tuple[float, ...] = OCTAVE_BANDS_HZ) -> np.ndarray:
    """All bands at once: array of shape (len(bands), len(x))."""
    return np.stack([filter_band(x, fs, fc) for fc in bands])


def band_key(nominal_hz: float) -> str:
    """JSON key of a band: "63", "125", ..., "8000"."""
    return str(int(round(nominal_hz)))


def band_energies_fft(x: np.ndarray, fs: float, half_width_octaves: float = 0.5,
                      bands: tuple[float, ...] = OCTAVE_BANDS_HZ) -> np.ndarray:
    """Energy of ``x`` per band from its spectrum: the sum of |X(f)|^2 over
    exact_centre * 2^(+-half_width_octaves), with rectangular (brick-wall) band edges.

    With ``half_width_octaves = 0.5`` these are full octaves. ``0.25`` measures each band's
    central half octave: what Phase 03 uses for per-band levels of band-reconstructed IRs (AX14),
    because neither this full-octave sum nor the Butterworth filters above can resolve more than
    ~20 dB (FFT) or ~16 dB (Butterworth) between adjacent octaves: the crossover of the renderer
    and the skirts of the meter put the louder band's energy into the quieter one.
    Zero padding doesn't change the result (Parseval), so ``x`` can be any length.
    """
    x = np.asarray(x, dtype=np.float64)
    n = 1 << int(np.ceil(np.log2(max(x.size, 2) * 2)))
    power = np.abs(np.fft.rfft(x, n)) ** 2
    freqs = np.fft.rfftfreq(n, 1.0 / fs)
    out = []
    for fc in bands:
        c = exact_centre_hz(fc)
        lo, hi = c * 2.0**-half_width_octaves, c * 2.0**half_width_octaves
        out.append(float(np.sum(power[(freqs >= lo) & (freqs < hi)])))
    return np.array(out)
