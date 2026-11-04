"""Click / discontinuity detector for renders of **sustained low tones**.

Why it works: the test input (``signals.sustained_tone``: 110 + 220 + 330 Hz) has no energy above
a few hundred hertz, and a linear time-invariant system, or one that changes slowly (a smooth
crossfade between IRs, a gain ramp), can only reshape the energy that is there. So the render has
essentially nothing above 2 kHz. A click or a sample-level discontinuity (a step or a spike) is
broadband: a fraction of its energy always lands above 2 kHz. The detector therefore:

1. high-passes the signal at 2 kHz (Butterworth, order 8, applied zero-phase with ``sosfiltfilt``,
   so the stop-band attenuation is doubled: about -250 dB at 330 Hz; the 110-330 Hz tone leaves
   only the float32 quantisation floor, around -150 dBFS);
2. computes the RMS level in consecutive 2 ms frames, in dBFS;
3. takes the median frame level as the stationary baseline;
4. flags frames above ``baseline + threshold_db`` (default 20 dB) **and** above an absolute floor
   of -90 dBFS (so quantisation or dither noise never counts, however quiet the baseline);
5. merges flagged frames that touch (or are one frame apart) into one event, reported at the
   sample with the largest high-passed magnitude.

Sensitivity, for a -12 dBFS tone at 48 kHz: a single-sample spike or a step of -60 dBFS gives a
high-passed frame level around -80 dBFS, well above the floor; -6 dBFS steps are trivially found.

Blind spots (read these before trusting a "0 clicks" result):
- Only meaningful for low-tone inputs. Music, noise, speech or sweeps have HF energy of their own,
  which raises the baseline and hides clicks.
- Discontinuities below about -70 dBFS (step or spike size) fall under the -90 dBFS floor.
- A level change spread over more than ~1 ms (e.g. a fast but smooth gain jump) has little energy
  above 2 kHz and is not seen; zipper noise from many tiny gain steps is seen only if each step's
  HF energy clears the floor. Use a dedicated envelope check for level pumping.
- Clicks closer than ~4 ms are merged into one event.
- Signal edges: the input is zero-padded before filtering, so a file that starts or ends abruptly
  (not at zero) is reported as a click at its first or last sample. Test tones fade in and out.
- If more than half the frames contain clicks, the median baseline itself rises and the 20 dB
  rule weakens; the absolute floor still applies.
"""

from __future__ import annotations

import functools

import numpy as np
from scipy import signal

HIGHPASS_HZ = 2000.0
HIGHPASS_ORDER = 8
FRAME_S = 0.002
DEFAULT_THRESHOLD_DB = 20.0
ABSOLUTE_FLOOR_DBFS = -90.0


@functools.lru_cache(maxsize=16)
def _highpass_sos(fs: float) -> np.ndarray:
    return signal.butter(HIGHPASS_ORDER, HIGHPASS_HZ, btype="highpass", fs=fs, output="sos")


def highpass(x: np.ndarray, fs: float) -> np.ndarray:
    """Zero-phase 2 kHz high-pass with zero padding at both ends (see blind spots)."""
    x = np.asarray(x, dtype=np.float64)
    pad = int(round(0.02 * fs))
    padded = np.concatenate([np.zeros(pad), x, np.zeros(pad)])
    return signal.sosfiltfilt(_highpass_sos(fs), padded, padtype=None)[pad : pad + x.size]


def frame_levels_dbfs(hp: np.ndarray, fs: float, frame_s: float = FRAME_S) -> np.ndarray:
    """RMS level of consecutive frames in dBFS (the last partial frame is included)."""
    n = max(1, int(round(frame_s * fs)))
    frames = -(-hp.size // n)
    padded = np.zeros(frames * n)
    padded[: hp.size] = hp
    rms = np.sqrt(np.mean(padded.reshape(frames, n) ** 2, axis=1))
    with np.errstate(divide="ignore"):
        return 20.0 * np.log10(np.maximum(rms, 1e-30))


def detect_clicks(
    x: np.ndarray,
    fs: float,
    threshold_db: float = DEFAULT_THRESHOLD_DB,
    floor_dbfs: float = ABSOLUTE_FLOOR_DBFS,
    frame_s: float = FRAME_S,
) -> dict:
    """Detect clicks in a mono signal (multi-channel: call per channel, or use ``detect_clicks_multi``).

    Returns a JSON-serialisable dict: ``events`` (list of {"time_s", "sample", "level_dbfs"}),
    ``baseline_dbfs`` (median frame level) and the parameters used.
    """
    x = np.asarray(x, dtype=np.float64)
    if x.ndim != 1:
        raise ValueError("detect_clicks expects a mono signal")
    n = max(1, int(round(frame_s * fs)))
    hp = highpass(x, fs)
    levels = frame_levels_dbfs(hp, fs, frame_s)
    baseline = float(np.median(levels)) if levels.size else -600.0
    flagged = np.flatnonzero((levels > baseline + threshold_db) & (levels > floor_dbfs))

    events = []
    if flagged.size:
        # Group frames whose indices differ by at most 2 (touching or one frame apart).
        splits = np.flatnonzero(np.diff(flagged) > 2) + 1
        for group in np.split(flagged, splits):
            start, stop = int(group[0]) * n, min((int(group[-1]) + 1) * n, hp.size)
            peak = start + int(np.argmax(np.abs(hp[start:stop])))
            events.append({"time_s": peak / fs, "sample": peak, "level_dbfs": float(np.max(levels[group]))})
    return {
        "events": events,
        "baseline_dbfs": baseline,
        "threshold_db": float(threshold_db),
        "floor_dbfs": float(floor_dbfs),
        "frame_s": float(frame_s),
        "highpass_hz": HIGHPASS_HZ,
    }


def detect_clicks_multi(x: np.ndarray, fs: float, **kwargs) -> dict:
    """``detect_clicks`` on each channel of a (frames, channels) array: {"channels": [...]}."""
    x = np.asarray(x, dtype=np.float64)
    if x.ndim == 1:
        x = x[:, None]
    return {"channels": [detect_clicks(x[:, c], fs, **kwargs) for c in range(x.shape[1])]}
