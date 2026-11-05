"""Compare two impulse responses: arrival times and amplitudes of the strongest peaks, per-band
energy, and ISO 3382 metric deltas.

Peak picking uses a matched filter: the IR is cross-correlated with a template of the expected
arrival shape (default: a unit impulse, for which the matched filter is the IR itself), and the
largest local maxima of the magnitude of the result are taken as arrivals. For a band-limited
renderer (Phase 03 builds IRs from octave bands) pass the renderer's direct-path pulse as the
template; the correlation peak of a pulse with itself is at its centre, so arrival times stay on
the sample grid.
"""

from __future__ import annotations

import numpy as np
from scipy import signal

from . import bands as _bands
from . import metrics as _metrics


def matched_filter(ir: np.ndarray, template: np.ndarray | None = None) -> np.ndarray:
    """Cross-correlation of ``ir`` with ``template``, aligned so that index i of the result is the
    template's peak placed at index i of the IR. Same length as ``ir``."""
    ir = np.asarray(ir, dtype=np.float64)
    if template is None:
        return ir.copy()
    template = np.asarray(template, dtype=np.float64)
    if template.ndim != 1 or template.size == 0:
        raise ValueError("template must be a non-empty 1-D array")
    peak = int(np.argmax(np.abs(template)))
    full = signal.correlate(ir, template, mode="full", method="auto")
    # full[k] = sum_n ir[n + k - (len(t) - 1)] * t[n]; the template peak at IR index i is at
    # k = i + (len(t) - 1) - peak.
    start = template.size - 1 - peak
    return full[start : start + ir.size]


def detect_peaks(
    ir: np.ndarray,
    count: int,
    template: np.ndarray | None = None,
    min_separation: int = 1,
    threshold_db: float = -120.0,
) -> np.ndarray:
    """Sample indices (sorted by time) of the ``count`` strongest arrivals in ``ir``.

    Candidates are local maxima of |matched_filter(ir, template)| (a plateau counts once, at its
    first sample) at most ``threshold_db`` below the strongest. They are accepted in order of
    decreasing magnitude, skipping any within ``min_separation`` samples of an accepted one. Fewer
    than ``count`` indices are returned if there aren't enough candidates.
    """
    mf = np.abs(matched_filter(ir, template))
    if mf.size == 0 or not np.any(mf > 0.0):
        return np.zeros(0, dtype=np.int64)
    padded = np.concatenate([[-1.0], mf, [-1.0]])
    is_peak = (padded[1:-1] > padded[:-2]) & (padded[1:-1] >= padded[2:])
    floor = np.max(mf) * 10.0 ** (threshold_db / 20.0)
    candidates = np.flatnonzero(is_peak & (mf >= floor) & (mf > 0.0))
    order = candidates[np.argsort(-mf[candidates], kind="stable")]
    accepted: list[int] = []
    for idx in order:
        if all(abs(int(idx) - a) >= min_separation for a in accepted):
            accepted.append(int(idx))
            if len(accepted) == count:
                break
    return np.array(sorted(accepted), dtype=np.int64)


def _db_ratio(num: float, den: float) -> float | None:
    if num <= 0.0 or den <= 0.0:
        return None
    return float(10.0 * np.log10(num / den))


def compare_irs(
    reference: np.ndarray,
    test: np.ndarray,
    fs: float,
    peaks: int = 20,
    template: np.ndarray | None = None,
    min_separation: int = 1,
    match_window: int = 8,
    with_metrics: bool = True,
) -> dict:
    """Compare ``test`` against ``reference`` (mono IRs at the same rate). JSON-serialisable:

    - ``peaks``: the ``peaks`` strongest arrivals of the reference, each matched to the test's
      strongest matched-filter value within ±``match_window`` samples: reference and test index,
      time difference in samples (test - reference), amplitude difference in dB (20 log10 of
      |test| / |reference| at the matched indices, None when the test has nothing there).
    - ``band_energy_db``: per octave band 10 log10(E_test / E_reference).
    - ``metric_deltas``: test minus reference for each ``metrics.room_metrics`` value (if
      ``with_metrics``; None where either side is None).
    """
    reference = np.asarray(reference, dtype=np.float64)
    test = np.asarray(test, dtype=np.float64)
    ref_mf = matched_filter(reference, template)
    test_mf = matched_filter(test, template)

    ref_idx = detect_peaks(reference, peaks, template, min_separation)
    peak_rows = []
    for i in ref_idx:
        lo, hi = max(int(i) - match_window, 0), min(int(i) + match_window + 1, test_mf.size)
        if lo >= hi:
            peak_rows.append({"reference_index": int(i), "test_index": None, "delta_samples": None, "amplitude_db": None})
            continue
        j = lo + int(np.argmax(np.abs(test_mf[lo:hi])))
        amp = _db_ratio(test_mf[j] ** 2, ref_mf[i] ** 2)
        peak_rows.append(
            {
                "reference_index": int(i),
                "test_index": int(j) if amp is not None else None,
                "delta_samples": int(j - i) if amp is not None else None,
                "amplitude_db": amp,
            }
        )

    band_energy = {}
    for fc in _bands.OCTAVE_BANDS_HZ:
        # With the lead, so energy near t = 0 is not cut in half by the zero-phase filter.
        e_ref = float(np.sum(_bands.filter_band_with_lead(reference, fs, fc)[0] ** 2))
        e_test = float(np.sum(_bands.filter_band_with_lead(test, fs, fc)[0] ** 2))
        band_energy[_bands.band_key(fc)] = _db_ratio(e_test, e_ref)

    result: dict = {"fs": float(fs), "peaks": peak_rows, "band_energy_db": band_energy}
    if with_metrics:
        result["metric_deltas"] = metric_deltas(_metrics.room_metrics(reference, fs), _metrics.room_metrics(test, fs))
    return result


_DELTA_KEYS = ("EDT", "T20", "T30", "C50", "C80", "D50", "DRR")


def metric_deltas(reference: dict, test: dict) -> dict:
    """Per band (and broadband): test - reference for each metric in ``_DELTA_KEYS``."""

    def delta(a, b):
        return None if a is None or b is None else float(b - a)

    out = {"bands": {}}
    for key, ref_band in reference["bands"].items():
        test_band = test["bands"].get(key, {})
        out["bands"][key] = {name: delta(ref_band.get(name), test_band.get(name)) for name in _DELTA_KEYS}
    out["broadband"] = {name: delta(reference["broadband"].get(name), test["broadband"].get(name)) for name in _DELTA_KEYS}
    return out
