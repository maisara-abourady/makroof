"""Test-signal generators. Every generator is deterministic: randomness comes from an explicit seed.

All functions return float64 numpy arrays (mono, 1-D) in the range [-1, 1] unless stated; use
``to_stereo`` to build the 2-channel inputs render_cli expects. Levels are in dBFS relative to a
full-scale peak of 1.0.
"""

from __future__ import annotations

from collections.abc import Mapping

import numpy as np

from . import bands as _bands


def db_to_amp(db: float) -> float:
    return float(10.0 ** (db / 20.0))


def _raised_cosine_fade(n: int) -> np.ndarray:
    if n <= 0:
        return np.ones(0)
    return 0.5 - 0.5 * np.cos(np.pi * (np.arange(n) + 0.5) / n)


def apply_fades(x: np.ndarray, fs: float, fade_in_s: float, fade_out_s: float | None = None) -> np.ndarray:
    """Raised-cosine fade in and out (fade_out_s defaults to fade_in_s). Returns a copy."""
    y = np.array(x, dtype=np.float64)
    n_in = min(int(round(fade_in_s * fs)), y.size)
    n_out = min(int(round((fade_in_s if fade_out_s is None else fade_out_s) * fs)), y.size)
    y[:n_in] *= _raised_cosine_fade(n_in)
    if n_out:
        y[y.size - n_out :] *= _raised_cosine_fade(n_out)[::-1]
    return y


def pink_noise(n: int, seed: int) -> np.ndarray:
    """Pink (1/f power) Gaussian noise, normalised to unit RMS. Shaped in the frequency domain."""
    rng = np.random.default_rng(seed)
    white = rng.standard_normal(n)
    spectrum = np.fft.rfft(white)
    k = np.arange(spectrum.size, dtype=np.float64)
    k[0] = 1.0
    spectrum /= np.sqrt(k)
    spectrum[0] = 0.0  # no DC
    x = np.fft.irfft(spectrum, n)
    return x / np.sqrt(np.mean(x**2))


def pink_bursts(
    fs: float,
    burst_s: float = 0.5,
    gap_s: float = 0.5,
    count: int = 4,
    level_dbfs: float = -12.0,
    fade_s: float = 0.005,
    seed: int = 1,
) -> np.ndarray:
    """``count`` pink-noise bursts of ``burst_s`` seconds separated by ``gap_s`` seconds of silence
    (and a gap at the end). Each burst has 5 ms raised-cosine fades so the edges don't click, and its
    peak is ``level_dbfs``."""
    n_burst = int(round(burst_s * fs))
    n_gap = int(round(gap_s * fs))
    out = np.zeros(count * (n_burst + n_gap))
    for i in range(count):
        burst = apply_fades(pink_noise(n_burst, seed + i), fs, fade_s)
        burst *= db_to_amp(level_dbfs) / np.max(np.abs(burst))
        start = i * (n_burst + n_gap)
        out[start : start + n_burst] = burst
    return out


def clicks(fs: float, interval_s: float = 0.5, count: int = 8, level_dbfs: float = -6.0, lead_s: float = 0.25) -> np.ndarray:
    """Single-sample clicks (unit impulses scaled to ``level_dbfs``), the first after ``lead_s``,
    then every ``interval_s``. Total length: lead + count * interval."""
    n = int(round((lead_s + count * interval_s) * fs))
    out = np.zeros(n)
    for i in range(count):
        out[int(round((lead_s + i * interval_s) * fs))] = db_to_amp(level_dbfs)
    return out


def click_positions(fs: float, interval_s: float = 0.5, count: int = 8, lead_s: float = 0.25) -> np.ndarray:
    """Sample indices of the clicks produced by ``clicks`` with the same arguments."""
    return np.array([int(round((lead_s + i * interval_s) * fs)) for i in range(count)])


def exp_sine_sweep(fs: float, f1: float = 20.0, f2: float = 20000.0, duration_s: float = 5.0, fade_s: float = 0.02) -> np.ndarray:
    """Exponential sine sweep (Farina 2000) from f1 to f2 Hz, peak 1.0 before fades:

        x(t) = sin(2 pi f1 L (exp(t / L) - 1)),  L = T / ln(f2 / f1)

    Short raised-cosine fades at both ends keep the edges click-free. Scale it yourself for level.
    """
    if not 0 < f1 < f2 < fs / 2:
        raise ValueError("need 0 < f1 < f2 < fs/2")
    n = int(round(duration_s * fs))
    t = np.arange(n) / fs
    rate = duration_s / np.log(f2 / f1)
    x = np.sin(2.0 * np.pi * f1 * rate * (np.exp(t / rate) - 1.0))
    return apply_fades(x, fs, fade_s)


def inverse_sweep(fs: float, f1: float = 20.0, f2: float = 20000.0, duration_s: float = 5.0, fade_s: float = 0.02) -> np.ndarray:
    """Farina inverse filter of ``exp_sine_sweep`` with the same arguments: the time-reversed sweep
    with an amplitude envelope falling 6 dB/octave (exp(-t / L)), which compensates the sweep's
    pink (-3 dB/octave) energy spectrum. Normalised so that sweep * inverse has unit gain at the
    geometric centre frequency sqrt(f1 f2), so ``deconvolve`` returns the IR at its true level.
    The peak of sweep * inverse lies at index len(sweep) - 1.
    """
    sweep = exp_sine_sweep(fs, f1, f2, duration_s, fade_s)
    n = sweep.size
    t = np.arange(n) / fs
    rate = duration_s / np.log(f2 / f1)
    inv = sweep[::-1] * np.exp(-t / rate)
    # Normalise at the geometric centre frequency.
    nfft = 1 << int(np.ceil(np.log2(2 * n)))
    h = np.fft.rfft(sweep, nfft) * np.fft.rfft(inv, nfft)
    f_mid = np.sqrt(f1 * f2)
    k = int(round(f_mid * nfft / fs))
    return inv / np.abs(h[k])


def deconvolve(recorded: np.ndarray, inverse: np.ndarray) -> np.ndarray:
    """Linear convolution of a recorded sweep response with the inverse filter; the IR starts at
    index len(inverse) - 1 of the result (sweep length - 1)."""
    n = recorded.size + inverse.size - 1
    nfft = 1 << int(np.ceil(np.log2(n)))
    y = np.fft.irfft(np.fft.rfft(recorded, nfft) * np.fft.rfft(inverse, nfft), nfft)
    return y[:n]


def sustained_tone(
    fs: float,
    duration_s: float = 10.0,
    freqs_hz: tuple[float, ...] = (110.0, 220.0, 330.0),
    level_dbfs: float = -12.0,
    fade_s: float = 0.5,
    am_rate_hz: float = 0.0,
    am_depth_db: float = 0.0,
) -> np.ndarray:
    """Sum of equal-amplitude sines (default 110 + 220 + 330 Hz, a low "hum") whose combined peak is
    ``level_dbfs``. Long raised-cosine fades (0.5 s) keep the start and end free of high-frequency
    energy, which matters for the click detector.

    Optional slow amplitude modulation: the level swings by ±``am_depth_db`` dB sinusoidally at
    ``am_rate_hz`` (gain in dB = am_depth_db * sin(2 pi am_rate t)). Peak level then reaches
    ``level_dbfs + am_depth_db``.
    """
    n = int(round(duration_s * fs))
    t = np.arange(n) / fs
    x = np.zeros(n)
    for f in freqs_hz:
        x += np.sin(2.0 * np.pi * f * t)
    # Peak of the unmodulated sum, measured over one common period (1 s covers it for integer freqs).
    period = np.arange(int(fs)) / fs
    peak = np.max(np.abs(sum(np.sin(2.0 * np.pi * f * period) for f in freqs_hz)))
    x *= db_to_amp(level_dbfs) / peak
    if am_rate_hz > 0.0 and am_depth_db != 0.0:
        x *= 10.0 ** (am_depth_db * np.sin(2.0 * np.pi * am_rate_hz * t) / 20.0)
    return apply_fades(x, fs, fade_s)


def synthetic_decay(
    fs: float,
    t60_s: float | Mapping[float, float],
    duration_s: float | None = None,
    seed: int = 0,
    noise_floor_db: float | None = None,
    onset_s: float = 0.0,
) -> np.ndarray:
    """White Gaussian noise times an exponential envelope with a known T60: the amplitude falls by
    60 dB in T60 seconds, a(t) = 10 ** (-3 t / T60), starting at ``onset_s``.

    ``t60_s`` is one value for all bands (exact: the decay is the same in every band), or a mapping
    {nominal band Hz: T60} covering every band in ``bands.OCTAVE_BANDS_HZ``: then each band's noise
    is filtered with the octave filterbank and given its own envelope, and the bands are summed
    (the per-band T60 then holds up to the filters' overlap with neighbouring bands).

    ``duration_s`` defaults to 1.5 * the longest T60 + 0.25 s (the decay reaches -90 dB).
    ``noise_floor_db`` adds stationary white noise over the whole signal, from an independent seed,
    at that level relative to the unit-variance white noise the decay starts from (e.g. -60 gives
    the same 60 dB initial signal-to-noise ratio in every band). The peak is not normalised.
    """
    t60_max = max(t60_s.values()) if isinstance(t60_s, Mapping) else float(t60_s)
    if duration_s is None:
        duration_s = onset_s + 1.5 * t60_max + 0.25
    n = int(round(duration_s * fs))
    n_onset = int(round(onset_s * fs))
    rng = np.random.default_rng(seed)
    t = np.arange(n - n_onset) / fs

    decay = np.zeros(n)
    if isinstance(t60_s, Mapping):
        missing = [fc for fc in _bands.OCTAVE_BANDS_HZ if fc not in t60_s]
        if missing:
            raise ValueError(f"t60_s mapping lacks bands {missing}")
        white = rng.standard_normal(n - n_onset)
        for fc in _bands.OCTAVE_BANDS_HZ:
            band = _bands.filter_band(white, fs, fc)
            decay[n_onset:] += band * 10.0 ** (-3.0 * t / t60_s[fc])
    else:
        decay[n_onset:] = rng.standard_normal(n - n_onset) * 10.0 ** (-3.0 * t / float(t60_s))

    if noise_floor_db is not None:
        noise_rng = np.random.default_rng(seed + 1_000_003)
        decay += noise_rng.standard_normal(n) * db_to_amp(noise_floor_db)
    return decay


def drum_loop(fs: float, bpm: float = 100.0, bars: int = 4, level_dbfs: float = -6.0, seed: int = 6) -> tuple[np.ndarray, np.ndarray]:
    """A synthetic stereo drum loop (4/4, eighth-note grid) for listening checks, as (left, right).

    Kick (a 0.35 s sine glide 110 -> 45 Hz with an exponential decay) on beats 1 and 3 and the
    "and" of 3, both channels; snare (0.2 s of noise plus a 190 Hz tone) on beats 2 and 4, slightly
    left; closed hi-hat (40 ms of noise, first differences, so mostly above 5 kHz) on every eighth,
    slightly right. Every hit has a 1 ms raised-cosine attack so nothing starts with a step.
    Deterministic for a seed; peak normalised to ``level_dbfs``.
    """
    rng = np.random.default_rng(seed)
    beat = 60.0 / bpm
    n = int(round(bars * 4 * beat * fs + 0.5 * fs))  # half a second of room after the last bar
    left, right = np.zeros(n), np.zeros(n)
    attack = _raised_cosine_fade(max(1, int(round(0.001 * fs))))

    def hit(x: np.ndarray, start: int, sound: np.ndarray, gain: float) -> None:
        sound = sound.copy()
        sound[: attack.size] *= attack[: sound.size]
        stop = min(n, start + sound.size)
        x[start:stop] += gain * sound[: stop - start]

    tk = np.arange(int(0.35 * fs)) / fs
    f = 45.0 + 65.0 * np.exp(-tk / 0.04)
    kick = np.sin(2.0 * np.pi * np.cumsum(f) / fs) * np.exp(-tk / 0.12)
    ts = np.arange(int(0.2 * fs)) / fs
    th = np.arange(int(0.04 * fs)) / fs
    for bar in range(bars):
        for eighth in range(8):
            start = int(round((bar * 4 + eighth / 2.0) * beat * fs))
            if eighth in (0, 4, 5):
                hit(left, start, kick, 1.0)
                hit(right, start, kick, 1.0)
            if eighth in (2, 6):
                snare = (0.6 * rng.standard_normal(ts.size) + 0.5 * np.sin(2.0 * np.pi * 190.0 * ts)) * np.exp(-ts / 0.05)
                hit(left, start, snare, 0.8)
                hit(right, start, snare, 0.55)
            hat = np.diff(rng.standard_normal(th.size + 1)) * np.exp(-th / 0.012)
            hit(left, start, hat, 0.12)
            hit(right, start, hat, 0.2)
    peak = max(np.max(np.abs(left)), np.max(np.abs(right)))
    g = db_to_amp(level_dbfs) / peak
    return left * g, right * g


def to_stereo(left: np.ndarray, right: np.ndarray | None = None) -> np.ndarray:
    """Shape (frames, 2) array; right defaults to a copy of left."""
    right = left if right is None else right
    if left.shape != right.shape:
        raise ValueError("left and right must have the same length")
    return np.stack([left, right], axis=1)
