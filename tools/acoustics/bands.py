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


def filter_band(x: np.ndarray, fs: float, nominal_hz: float) -> np.ndarray:
    """Zero-phase octave-band filtering of a 1-D signal; output has the same length.

    The signal is zero-padded on both sides before filtering (instead of scipy's odd extension),
    so a signal that starts or stops abruptly is treated as silence outside its extent. Energy that
    the backward pass spreads before t = 0 is cut off with the padding; it is far below the
    signal (> 60 dB down after one period of the lower band edge).
    """
    x = np.asarray(x, dtype=np.float64)
    if x.ndim != 1:
        raise ValueError("filter_band expects a 1-D signal")
    pad = _pad_samples(nominal_hz, fs)
    padded = np.concatenate([np.zeros(pad), x, np.zeros(pad)])
    y = signal.sosfiltfilt(octave_sos(nominal_hz, fs), padded, padtype=None)
    return y[pad : pad + x.size]


def filter_bands(x: np.ndarray, fs: float, bands: tuple[float, ...] = OCTAVE_BANDS_HZ) -> np.ndarray:
    """All bands at once: array of shape (len(bands), len(x))."""
    return np.stack([filter_band(x, fs, fc) for fc in bands])


def band_key(nominal_hz: float) -> str:
    """JSON key of a band: "63", "125", ..., "8000"."""
    return str(int(round(nominal_hz)))
