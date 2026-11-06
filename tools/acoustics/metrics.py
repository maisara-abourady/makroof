"""ISO 3382-1 room-acoustic parameters from an impulse response, per octave band and broadband.

Pipeline for one IR (``room_metrics``):

1. **Onset**: the first sample of the broadband IR whose energy is no more than 20 dB below the
   maximum. It is the common time origin for every band. ISO 3382-1 (Annex A) puts the start
   where the signal first rises significantly above the background noise, *before* it gets within
   20 dB of the maximum; for an impulsive direct sound both rules give the same sample, for a
   smeared onset (a band-limited or measured direct sound) this one is later by up to the rise
   time. Energy before the onset counts as early energy for C50, C80 and D50 and is ignored by the
   decay curve.
2. **Band filtering** with ``bands.filter_band_with_lead`` (zero-phase order-6 Butterworth
   octaves), which keeps the part of each band's response that the zero-phase filter puts before
   sample 0. Without it, a direct sound within a few ms of the start of the file loses up to half
   of its band energy and the band clarity reads several dB low.
3. **Noise floor and truncation, Lundeby et al. (1995)** (``lundeby``): an iterative estimate of
   the background noise level and of the "crosspoint", where the decay sinks into the noise. The
   Schroeder integral is truncated at the crosspoint and the energy the decay would have had after
   it is added back analytically (Lundeby's compensation term C). ISO 3382-1:2009 5.3.3 names this
   truncation-plus-correction approach as the way to handle background noise. A signal whose end
   is more than 200 dB below its peak (exact zeros, or filter ringing after them) is noise-free.
4. **Schroeder backward integration** (ISO 3382-1 5.3.3, Schroeder 1965): EDC(t) = C + sum of
   h^2 from t to the crosspoint, normalised to 0 dB at the onset.
5. **Decay times** (ISO 3382-1 A.2.1/A.2.2): least-squares line through the EDC (in dB, every
   sample) between the first times it reaches the upper and lower limits of the evaluation range,
   extrapolated to 60 dB: EDT 0 to -10 dB (x6), T20 -5 to -25 dB (x3), T30 -5 to -35 dB (x2).
   A decay time is reported only if the band's dynamic range (peak level of the smoothed envelope
   above the noise level) is at least 10 dB more than the bottom of the evaluation range
   (EDT >= 20 dB, T20 >= 35 dB, T30 >= 45 dB, after ISO 3382-1 5.3.2), and the regression is
   well defined. Otherwise the value is None and the reason is listed in ``warnings``.
   Decay times of *stochastic* decays (noise tails) are meant to be read on ensemble-averaged
   decay curves (``room_metrics_ensemble``, BUILD_PLAN AX11).
6. **Energy ratios** (ISO 3382-1 A.2.4/A.2.5): C50 and C80 = 10 log10(early / late) with the
   boundary at 50 / 80 ms after the onset; D50 = early(50 ms) / total, a ratio in [0, 1]. The late
   part is integrated to the crosspoint plus the compensation term, so background noise doesn't
   lower the clarity.
7. **DRR** (not in ISO 3382-1; BUILD_PLAN AX13): energy within ±2.5 ms of the direct-sound peak
   (the largest broadband |h| in the first 2.5 ms after the onset) over all energy after that
   window up to the crosspoint (+ compensation). Early energy before the window counts as neither.
   Per band, DRR is reported only where the band filter keeps >= 99% of an impulse's energy inside
   the window (at 44.1-96 kHz: 1 kHz and up); narrower bands can't resolve a 5 ms window.

All results are plain Python floats or None, so ``json.dumps`` works on the returned dict.

Known limits (see also bands.py):
- **Cross-band leakage in octave analysis.** A band whose T60 is shorter than an adjacent band's
  reads long: the slower neighbour leaks through the filter skirts (-6 dB at the edges, ~36 dB per
  octave beyond) and dominates the late decay. Measured on ensemble-averaged synthetic decays
  (tools/acoustics/tests/test_metrics.py): +20% at 250 Hz next to a 2:1 step (2.0 s below, 1.0 s
  above), +18% for a 0.5 s band between 0.8 s neighbours, +5% at 8 kHz for a hall profile falling
  1.3 -> 0.9 s from 4 to 8 kHz; smooth profiles stay within a few percent. A comparison of two IRs
  through this same filterbank is fair only if both have the same neighbour ratio
  r = T(slower neighbour) / T(band) and the same leak (the energy the neighbour puts through the
  band's skirts); otherwise each reading carries its own bias (phase-05 scope 7, decider D1; two-term
  model on the Kuttruff Eqs. 3.64-3.68 basis). A per-band comparison with an analytic per-band
  prediction (e.g. Eyring in Phase 04) inherits it. A property of octave filtering of this order,
  not tunable away here (note for the Expert; AX23).
- 63 Hz decays shorter than ~0.4 s are biased by the band filter (B * T60 < 16).
- A measured IR whose noise floor is not stationary defeats Lundeby's method (it assumes
  stationary noise after the crosspoint).
- An IR shorter than its decay into the noise has no noise estimate, so the last 10% of the decay
  stands in for it and the result is a mild extrapolation.
- One realisation of a noise decay scatters in T30 by roughly 0.5 T30 / sqrt(B T30) (AX11): use
  ``room_metrics_ensemble`` to measure the expected decay.
"""

from __future__ import annotations

import math
from dataclasses import dataclass, field

import numpy as np

from . import bands as _bands

ONSET_THRESHOLD_DB = -20.0
# A "noise" level this far below the peak energy is numerical (filter ringing after exact zeros),
# so the signal is treated as noise-free (no truncation, no compensation, noise_floor_db None).
NOISE_FREE_BELOW_PEAK_DB = -200.0
DIRECT_HALF_WINDOW_S = 0.0025  # AX13
# AX13: per-band DRR only where the band filter keeps >= 99% of an impulse's energy within the
# ±2.5 ms window. The fraction f that leaks out of the window is counted as reverberant, which
# biases DRR by about -10 log10(1 + f * 10^(DRR/10)) dB: -0.4 dB at f = 1% and DRR = +10 dB. At
# 48 kHz this leaves 1 kHz and up (1 kHz keeps 99.8%; 500 Hz 98.4%, 250 Hz 88%, 63-125 Hz ~40%).
DRR_MIN_BAND_RESOLUTION = 0.99

# Evaluation ranges in dB below the EDC start: (upper, lower, factor to 60 dB).
DECAY_RANGES: dict[str, tuple[float, float]] = {
    "EDT": (0.0, -10.0),
    "T20": (-5.0, -25.0),
    "T30": (-5.0, -35.0),
}
# Required dynamic range above the noise floor: 10 dB below the bottom of the range.
REQUIRED_DYNAMIC_RANGE_DB: dict[str, float] = {name: -lower + 10.0 for name, (_, lower) in DECAY_RANGES.items()}


def _db(x: float | np.ndarray) -> float | np.ndarray:
    with np.errstate(divide="ignore"):
        return 10.0 * np.log10(x)


def _none_if_nan(x: float) -> float | None:
    return None if x is None or not math.isfinite(x) else float(x)


def onset_index(h: np.ndarray, threshold_db: float = ONSET_THRESHOLD_DB) -> int:
    """First sample whose energy is within ``threshold_db`` of the IR's maximum energy."""
    e = np.asarray(h, dtype=np.float64) ** 2
    peak = float(np.max(e)) if e.size else 0.0
    if peak <= 0.0:
        raise ValueError("impulse response is all zeros")
    return int(np.argmax(e >= peak * 10.0 ** (threshold_db / 10.0)))


# --------------------------------------------------------------------------------------------
# Lundeby
# --------------------------------------------------------------------------------------------


@dataclass
class LundebyResult:
    """Lundeby's estimates for one band, in samples relative to the start of the analysed signal."""

    crosspoint: int  # EDC is integrated over [0, crosspoint)
    noise_power: float  # mean h^2 of the background noise (0 when the signal is noise-free)
    compensation: float  # energy (sum of h^2) of the extrapolated decay after the crosspoint
    late_slope_db_per_s: float | None  # slope of the late decay used for the compensation
    dynamic_range_db: float  # peak of the smoothed envelope above the noise level (inf if noise-free)
    iterations: int
    warnings: list[str] = field(default_factory=list)
    # Level (dB, block-mean power) of that final late-decay line extrapolated to index 0 (the onset);
    # None when there is no line (noise-free signal or too little decay). Phase-05 usable range (D7).
    late_intercept_db: float | None = None

    @property
    def line_margin_db(self) -> float | None:
        """Height of the final late-decay line at the onset above the noise level (dB)."""
        if self.late_intercept_db is None or self.noise_power <= 0.0:
            return None
        return self.late_intercept_db - float(_db(self.noise_power))


def _smooth_db(e: np.ndarray, block: int) -> tuple[np.ndarray, np.ndarray]:
    """Mean energy in consecutive blocks of ``block`` samples: (centre sample index, level in dB)."""
    block = max(1, int(block))
    nblocks = e.size // block
    if nblocks == 0:
        return np.array([e.size / 2.0]), np.array([_db(max(float(np.mean(e)), 1e-300))])
    means = e[: nblocks * block].reshape(nblocks, block).mean(axis=1)
    centres = (np.arange(nblocks) + 0.5) * block
    return centres, _db(np.maximum(means, 1e-300))


def _upper_hull_db(level: np.ndarray) -> np.ndarray:
    """Running maximum from the end: hull[i] = max(level[i:]). The smoothed decay of a measured IR
    is close to monotonic, so this is (almost) the level itself; in a synthetic IR whose early part
    is a few sparse reflections, a band filter can leave blocks of exact zeros (-3000 dB) between
    them, and Lundeby's steps would take the first such gap for the noise floor. The hull bridges
    those gaps with the later energy, so the decisions below see the decay, not the gaps (Phase 04)."""
    return np.maximum.accumulate(level[::-1])[::-1]


def _fit_line(x: np.ndarray, y: np.ndarray) -> tuple[float, float] | None:
    """Least-squares y = a + b x; None if fewer than 2 points or a degenerate x."""
    if x.size < 2 or np.ptp(x) == 0.0:
        return None
    b, a = np.polyfit(x, y, 1)
    return float(a), float(b)


def lundeby(e: np.ndarray, fs: float, initial_block_s: float = 0.010, intervals_per_10db: int = 5, max_iterations: int = 5) -> LundebyResult:
    """Lundeby, Vigran, Bietz and Vorlaender (1995), "Uncertainties of measurements in room
    acoustics", Acustica 81, 344-355, as used by ISO 3382-1 5.3.3.

    ``e`` is the squared band IR from the onset on. Steps:
      1. average e in 10 ms blocks (level in dB), and take the upper hull of that level (running
         maximum from the end), so exact-zero gaps between sparse early reflections of a synthetic
         IR are not mistaken for the noise floor. On a noisy decay the hull is not the level itself:
         it lifts the block-to-block dips of the noise, so a measured IR is not left unchanged; the
         phase-05 paired noise test (tools/acoustics/tests/test_noise_handling.py) measures the
         resulting T30 bias (case A: |bias| <= 0.6 % at 48-65 dB below the decay, 500 Hz-2 kHz);
      2. preliminary noise level = mean of the last 10% of e;
      3. line through the smoothed decay from its peak to the first block 10 dB above the noise;
      4. crosspoint = where the line meets the noise level;
      5. new block length so there are ``intervals_per_10db`` blocks per 10 dB of decay;
      6. iterate: noise = mean of e from the point 10 dB below the crosspoint level on the line
         (at least the last 10% of the signal); late-decay line over the 20 dB range that starts
         7.5 dB above the noise; new crosspoint; stop when it moves less than 1 ms.
    Compensation C = energy of the late-decay line after the crosspoint = noise_power * tau * fs
    samples' worth, with tau the power decay time constant of that line (the line meets the
    noise level at the crosspoint by construction).

    A noise-free signal (the mean of its last 10% is zero or more than 200 dB below its peak, i.e.
    exact zeros or filter ringing after them) is not truncated: crosspoint = end of the last
    non-zero sample, C = 0, dynamic range = inf (reported as None).
    """
    e = np.asarray(e, dtype=np.float64)
    n = e.size
    warnings: list[str] = []
    nonzero = np.flatnonzero(e > 0.0)
    if nonzero.size == 0:
        raise ValueError("band signal is all zeros")
    tail_start = int(0.9 * n)
    noise = float(np.mean(e[tail_start:])) if n - tail_start > 0 else 0.0
    # Noise-free: the end is exact zeros, or (after band filtering of an IR that ends in zeros, e.g.
    # an image-source IR) only filter ringing far below anything physical.
    if noise <= float(np.max(e)) * 10.0 ** (NOISE_FREE_BELOW_PEAK_DB / 10.0):
        return LundebyResult(int(nonzero[-1]) + 1, 0.0, 0.0, None, math.inf, 0, warnings)

    # Steps 1-4 (on the upper hull of the smoothed decay, see _upper_hull_db).
    centres, level = _smooth_db(e, initial_block_s * fs)
    level = _upper_hull_db(level)
    peak_i = int(np.argmax(level))
    peak_db = float(level[peak_i])
    noise_db = float(_db(noise))
    dynamic_range = peak_db - noise_db
    below = np.flatnonzero(level[peak_i:] <= noise_db + 10.0)
    if below.size == 0 or below[0] < 1:
        warnings.append(f"Lundeby: decay does not fall 10 dB above the noise floor (dynamic range {dynamic_range:.1f} dB)")
        return LundebyResult(n, noise, 0.0, None, dynamic_range, 0, warnings)
    stop = peak_i + int(below[0])
    fit = _fit_line(centres[peak_i : stop + 1] / fs, level[peak_i : stop + 1])
    if fit is None or fit[1] >= 0.0:
        warnings.append("Lundeby: no decaying slope in the preliminary fit")
        return LundebyResult(n, noise, 0.0, None, dynamic_range, 0, warnings)
    a, b = fit
    t_cross = (noise_db - a) / b

    # Step 5.
    block = max(1, int(round((10.0 / -b) / intervals_per_10db * fs)))

    # Steps 6-9.
    iterations = 0
    for iterations in range(1, max_iterations + 1):
        noise_from = int(round((t_cross + 10.0 / -b) * fs))
        noise_from = min(max(noise_from, 0), tail_start)
        noise = float(np.mean(e[noise_from:]))
        if noise <= 0.0:
            return LundebyResult(int(nonzero[-1]) + 1, 0.0, 0.0, None, math.inf, iterations, warnings)
        noise_db = float(_db(noise))

        centres, level = _smooth_db(e, block)
        level = _upper_hull_db(level)
        peak_i = int(np.argmax(level))
        dynamic_range = float(level[peak_i]) - noise_db
        lo_db = noise_db + 7.5
        hi_db = min(lo_db + 20.0, float(level[peak_i]))
        seg = np.flatnonzero((level <= hi_db) & (level >= lo_db))
        seg = seg[seg >= peak_i]
        # Use the contiguous run starting at the first block below hi_db (late noise blocks that
        # happen to fall into the range are excluded).
        if seg.size:
            run_end = np.flatnonzero(np.diff(seg) > 1)
            seg = seg[: run_end[0] + 1] if run_end.size else seg
        fit = _fit_line(centres[seg] / fs, level[seg]) if seg.size >= 2 else None
        if fit is None or fit[1] >= 0.0 or hi_db - lo_db < 10.0:
            warnings.append("Lundeby: late decay range too short; kept the previous estimate")
            break
        a, b = fit
        new_cross = (noise_db - a) / b
        moved = abs(new_cross - t_cross)
        t_cross = new_cross
        if moved < 0.001:
            break

    crosspoint = int(round(t_cross * fs))
    if crosspoint >= n:
        crosspoint = n
    crosspoint = max(crosspoint, 1)
    tau = 10.0 / (-b * math.log(10.0))  # power time constant of the late decay line, seconds
    compensation = noise * tau * fs
    return LundebyResult(crosspoint, noise, compensation, b, dynamic_range, iterations, warnings, late_intercept_db=a)


# --------------------------------------------------------------------------------------------
# EDC and parameters
# --------------------------------------------------------------------------------------------


def schroeder_edc(e: np.ndarray, crosspoint: int, compensation: float = 0.0) -> np.ndarray:
    """Backward-integrated energy decay curve in dB (0 dB at index 0) over [0, crosspoint):
    EDC[n] = compensation + sum_{k=n}^{crosspoint-1} e[k]."""
    tail = np.cumsum(e[:crosspoint][::-1])[::-1] + compensation
    return _db(tail / tail[0])


def decay_time(edc_db: np.ndarray, fs: float, upper_db: float, lower_db: float) -> float | None:
    """Least-squares line through every EDC sample between the first times the EDC reaches
    ``upper_db`` and ``lower_db``, extrapolated to -60 dB. None if the EDC never reaches the range."""
    upper_hits = np.flatnonzero(edc_db <= upper_db)
    lower_hits = np.flatnonzero(edc_db <= lower_db)
    if upper_hits.size == 0 or lower_hits.size == 0:
        return None
    i0, i1 = int(upper_hits[0]), int(lower_hits[0])
    if i1 - i0 < 2:
        return None
    t = np.arange(i0, i1 + 1) / fs
    fit = _fit_line(t, edc_db[i0 : i1 + 1])
    if fit is None or fit[1] >= 0.0:
        return None
    return -60.0 / fit[1]


def _band_metrics(
    h: np.ndarray,
    fs: float,
    onset: int,
    direct: int,
    energy: np.ndarray | None = None,
    lead: int = 0,
    band_hz: float | None = None,
) -> dict:
    """Metrics of one (band-filtered or broadband) IR given the common onset and direct indices.

    ``energy`` (h^2, or an average of h^2 over an ensemble) replaces h when given. ``onset`` and
    ``direct`` index into ``e``; ``lead`` is the number of samples in ``e`` before sample 0 of the
    original IR (the anti-causal part of a zero-phase band filter, ``bands.filter_band_with_lead``),
    which counts as early energy. ``band_hz`` is the band's nominal centre (None for broadband)."""
    e = np.asarray(h, dtype=np.float64) ** 2 if energy is None else np.asarray(energy, dtype=np.float64)
    warnings: list[str] = []
    result: dict = {}

    decay_part = e[onset:]
    if not np.any(decay_part > 0.0):
        return {name: None for name in (*DECAY_RANGES, "C50", "C80", "D50", "DRR")} | {
            "noise_floor_db": None,
            "dynamic_range_db": None,
            "crosspoint_s": None,
            "line_margin_db": None,
            "warnings": ["band has no energy after the onset"],
        }
    lb = lundeby(decay_part, fs)
    warnings += lb.warnings
    edc = schroeder_edc(decay_part, lb.crosspoint, lb.compensation)

    for name, (upper, lower) in DECAY_RANGES.items():
        value = None
        needed = REQUIRED_DYNAMIC_RANGE_DB[name]
        if lb.dynamic_range_db < needed:
            warnings.append(f"{name}: dynamic range {lb.dynamic_range_db:.1f} dB < {needed:.0f} dB required")
        else:
            value = decay_time(edc, fs, upper, lower)
            if value is None:
                warnings.append(f"{name}: EDC does not cover {upper:.0f} to {lower:.0f} dB")
        result[name] = value

    # Energy ratios. Early: everything before the boundary (including pre-onset energy).
    # Late: from the boundary to the crosspoint plus the compensation.
    end = onset + lb.crosspoint
    total = float(np.sum(e[:end])) + lb.compensation
    for name, ms in (("C50", 50.0), ("C80", 80.0)):
        boundary = min(onset + int(round(ms * 1e-3 * fs)), end)
        early = float(np.sum(e[:boundary]))
        late = total - early
        result[name] = _none_if_nan(float(_db(early / late))) if late > 0.0 and early > 0.0 else None
    boundary50 = min(onset + int(round(0.050 * fs)), end)
    result["D50"] = float(np.sum(e[:boundary50]) / total) if total > 0.0 else None

    # AX13: DRR window ±2.5 ms around the direct-sound peak. A band whose filter can't resolve that
    # window (less than DRR_MIN_BAND_RESOLUTION of an impulse's band energy inside it) gets None.
    half = int(round(DIRECT_HALF_WINDOW_S * fs))
    d0, d1 = max(direct - half, 0), min(direct + half + 1, end)
    direct_energy = float(np.sum(e[d0:d1]))
    reverberant = float(np.sum(e[d1:end])) + lb.compensation
    resolution = 1.0 if band_hz is None else _bands.impulse_energy_within(fs, band_hz, DIRECT_HALF_WINDOW_S)
    if resolution < DRR_MIN_BAND_RESOLUTION:
        result["DRR"] = None
        warnings.append(
            f"DRR: the band filter keeps only {100 * resolution:.0f}% of an impulse's energy within "
            f"±{1000 * DIRECT_HALF_WINDOW_S:.1f} ms (< {100 * DRR_MIN_BAND_RESOLUTION:.0f}%), so the band can't resolve the direct sound"
        )
    else:
        result["DRR"] = float(_db(direct_energy / reverberant)) if direct_energy > 0.0 and reverberant > 0.0 else None

    result["noise_floor_db"] = _none_if_nan(float(_db(lb.noise_power))) if lb.noise_power > 0.0 else None
    result["dynamic_range_db"] = _none_if_nan(lb.dynamic_range_db)
    # Phase-05 usable range (decider D7): the final Lundeby late-decay line at the onset above the
    # noise level, beside the peak-referred dynamic range. Reported only; not used here.
    result["line_margin_db"] = _none_if_nan(lb.line_margin_db) if lb.line_margin_db is not None else None
    result["crosspoint_s"] = (onset - lead + lb.crosspoint) / fs
    result["warnings"] = warnings
    return result


def room_metrics(h: np.ndarray, fs: float, bands: tuple[float, ...] = _bands.OCTAVE_BANDS_HZ) -> dict:
    """ISO 3382-1 parameters of a mono IR: EDT, T20, T30 (s), C50, C80 (dB), D50 (ratio), DRR (dB),
    per octave band and broadband, plus the noise-floor diagnostics. JSON-serialisable:

        {"fs": 48000.0, "onset_s": ..., "bands_hz": [63.0, ...],
         "bands": {"63": {"EDT": ..., "T20": ..., ...}, ..., "8000": {...}},
         "broadband": {...}}
    """
    h = np.asarray(h, dtype=np.float64)
    if h.ndim != 1:
        raise ValueError("room_metrics expects a mono IR (1-D array)")
    onset = onset_index(h)
    half = int(round(DIRECT_HALF_WINDOW_S * fs))
    direct = onset + int(np.argmax(np.abs(h[onset : onset + half + 1])))
    out: dict = {
        "fs": float(fs),
        "onset_s": onset / fs,
        "direct_s": direct / fs,
        "bands_hz": [float(fc) for fc in bands],
        "bands": {},
    }
    for fc in bands:
        # With the lead: the band energy a zero-phase filter puts before sample 0 is kept (early).
        band, lead = _bands.filter_band_with_lead(h, fs, fc)
        out["bands"][_bands.band_key(fc)] = _band_metrics(band, fs, onset + lead, direct + lead, lead=lead, band_hz=fc)
    out["broadband"] = _band_metrics(h, fs, onset, direct)
    return out


def room_metrics_ensemble(irs: list[np.ndarray], fs: float, bands: tuple[float, ...] = _bands.OCTAVE_BANDS_HZ) -> dict:
    """Metrics of the **ensemble-averaged** energy of several IRs of the same system (e.g. several
    measurements, positions or noise realisations), in the same format as ``room_metrics``.

    Each IR is aligned at its own onset, band-filtered and squared, and the squared band signals are
    averaged before Lundeby and Schroeder integration. This is the "average of decay curves" of
    ISO 3382-1 (spatial averaging by combining decay curves) and of ISO 3382-2: it estimates the
    expected decay of a random process, which a single noise realisation only approximates (its
    T30 scatters by roughly 0.5 T30 / sqrt(B T30) in a band of bandwidth B, cf. ISO 3382-2 Annex A;
    BUILD_PLAN AX11).
    The direct-sound index is the mean of the per-IR direct indices relative to their onsets.
    """
    if not irs:
        raise ValueError("need at least one IR")
    aligned = []
    directs = []
    half = int(round(DIRECT_HALF_WINDOW_S * fs))
    for h in irs:
        h = np.asarray(h, dtype=np.float64)
        onset = onset_index(h)
        directs.append(int(np.argmax(np.abs(h[onset : onset + half + 1]))))
        aligned.append(h[onset:])
    length = min(a.size for a in aligned)
    aligned = [a[:length] for a in aligned]
    direct = int(round(float(np.mean(directs))))
    out: dict = {
        "fs": float(fs),
        "onset_s": 0.0,
        "direct_s": direct / fs,
        "bands_hz": [float(fc) for fc in bands],
        "ensemble_size": len(irs),
        "bands": {},
    }
    for fc in bands:
        filtered = [_bands.filter_band_with_lead(a, fs, fc) for a in aligned]
        lead = filtered[0][1]
        energy = np.mean([y**2 for y, _ in filtered], axis=0)
        out["bands"][_bands.band_key(fc)] = _band_metrics(
            np.empty(0), fs, lead, direct + lead, energy=energy, lead=lead, band_hz=fc
        )
    energy = np.mean([a**2 for a in aligned], axis=0)
    out["broadband"] = _band_metrics(np.empty(0), fs, 0, direct, energy=energy)
    return out
