"""Integrated loudness after ITU-R BS.1770-4 (mono or multichannel, LKFS), for loudness-matching
listening material (phase-05 scope 5). K-weighting = high shelf (+4 dB above ~1.7 kHz) followed
by an RLB high-pass (~38 Hz), designed at any sample rate from the standard's analogue parameters
(the 48 kHz coefficients of BS.1770 are reproduced to < 1e-4); 400 ms blocks with 75 % overlap,
absolute gate -70 LKFS, relative gate -10 LU. Channel weights 1 (no surround channels here).
"""

from __future__ import annotations

import math

import numpy as np
import scipy.signal as sg


def _biquad(fs, f0, gain_db, q, kind):
    k = math.tan(math.pi * f0 / fs)
    if kind == "shelf":
        vh = 10 ** (gain_db / 20)
        vb = vh ** 0.4996667741545416
        a0 = 1 + k / q + k * k
        b = [(vh + vb * k / q + k * k) / a0, 2 * (k * k - vh) / a0, (vh - vb * k / q + k * k) / a0]
        a = [1.0, 2 * (k * k - 1) / a0, (1 - k / q + k * k) / a0]
    else:  # high-pass
        a0 = 1 + k / q + k * k
        b = [1.0, -2.0, 1.0]
        a = [1.0, 2 * (k * k - 1) / a0, (1 - k / q + k * k) / a0]
    return np.array(b), np.array(a)


def k_weighting(fs: float):
    """(b, a) pairs of the two K-weighting stages."""
    return [_biquad(fs, 1681.974450955533, 3.999843853973347, 0.7071752369554196, "shelf"),
            _biquad(fs, 38.13547087602444, 0.0, 0.5003270373238773, "hp")]


def integrated_loudness(x: np.ndarray, fs: float) -> float:
    """LKFS of ``x`` (samples, or samples x channels)."""
    x = np.asarray(x, dtype=np.float64)
    if x.ndim == 1:
        x = x[:, None]
    y = x
    for b, a in k_weighting(fs):
        y = sg.lfilter(b, a, y, axis=0)
    block = int(round(0.4 * fs))
    step = int(round(0.1 * fs))
    if y.shape[0] < block:
        raise ValueError("signal shorter than one 400 ms block")
    starts = range(0, y.shape[0] - block + 1, step)
    z = np.array([np.mean(y[s : s + block] ** 2, axis=0).sum() for s in starts])
    lk = -0.691 + 10 * np.log10(np.maximum(z, 1e-300))
    z = z[lk > -70.0]
    if z.size == 0:
        return -math.inf
    rel = -0.691 + 10 * math.log10(np.mean(z)) - 10.0
    z2 = z[-0.691 + 10 * np.log10(z) > rel]
    return -0.691 + 10 * math.log10(np.mean(z2))
