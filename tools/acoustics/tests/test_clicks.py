"""clicks.py acceptance: 100% detection of injected discontinuities, no false positives on clean
or slowly modulated tones (Phase 02 acceptance criteria)."""

import numpy as np
import pytest

from tools.acoustics import clicks, signals

FS = 48000.0
DURATION_S = 60.0
N_EVENTS = 200


def _as_float32(x):
    # Renders are float32 WAVs: analyse what a file would contain.
    return np.asarray(x, dtype=np.float32).astype(np.float64)


def _assert_quiet_margin(result):
    # Margin (review minor 6): a clean or slowly modulated tone stays ~72 dB below the effective
    # threshold (its HF residue is the float32 quantisation floor). Require 40 dB.
    margin = result["effective_threshold_dbfs"] - result["max_frame_dbfs"]
    print(f"loudest frame {result['max_frame_dbfs']:.1f} dBFS, threshold {result['effective_threshold_dbfs']:.1f} dBFS, margin {margin:.1f} dB")
    assert margin >= 40.0, margin


def _event_positions(seed: int) -> np.ndarray:
    # 200 random positions at least 100 ms apart, away from the 0.5 s fades.
    rng = np.random.default_rng(seed)
    slots = rng.choice(np.arange(int(0.6 * FS), int((DURATION_S - 0.7) * FS), int(0.1 * FS)), N_EVENTS, replace=False)
    return np.sort(slots + rng.integers(0, int(0.05 * FS), N_EVENTS))


def _inject(kind: str, seed: int):
    """Tone (fades applied after the injection, so the file starts and ends at zero) with 200
    discontinuities of random size in [-60, -6] dBFS and random sign."""
    rng = np.random.default_rng(seed + 1)
    tone = signals.sustained_tone(FS, DURATION_S, fade_s=0.0)
    positions = _event_positions(seed)
    sizes_db = rng.uniform(-60.0, -6.0, N_EVENTS)
    sizes_db[:2] = (-60.0, -6.0)  # make sure both ends of the range are present
    rng.shuffle(sizes_db)
    for p, size_db in zip(positions, sizes_db):
        a = 10.0 ** (size_db / 20.0) * rng.choice([-1.0, 1.0])
        if kind == "step":
            tone[p:] += a  # the waveform jumps by a and stays offset
        else:
            tone[p] += a  # a single-sample spike
    return _as_float32(signals.apply_fades(tone, FS, 0.5)), positions


@pytest.mark.parametrize("kind", ["step", "spike"])
@pytest.mark.parametrize("seed", [0, 1])
def test_flags_every_injected_discontinuity(kind, seed):
    x, positions = _inject(kind, seed)
    result = clicks.detect_clicks(x, FS)
    found = np.array([e["sample"] for e in result["events"]])
    assert found.size > 0
    # Every injected event has a detection within 1 ms, and there is nothing else.
    tolerance = int(0.001 * FS)
    missed = [int(p) for p in positions if np.min(np.abs(found - p)) > tolerance]
    assert not missed, f"missed {len(missed)} of {N_EVENTS}: {missed[:10]}"
    extra = [int(f) for f in found if np.min(np.abs(positions - f)) > tolerance]
    assert not extra, f"{len(extra)} detections at no injected event: {extra[:10]}"
    assert found.size == N_EVENTS
    # Margin (review minor 6): the weakest event (a -60 dBFS discontinuity) clears the effective
    # threshold by ~9.8 dB at 48 kHz. Require 6 dB so a loss of sensitivity shows before it flips.
    weakest = min(e["level_dbfs"] for e in result["events"])
    margin = weakest - result["effective_threshold_dbfs"]
    print(f"{kind}/{seed}: weakest event {weakest:.1f} dBFS, threshold {result['effective_threshold_dbfs']:.1f} dBFS, margin {margin:.1f} dB")
    assert margin >= 6.0, margin


def test_no_false_positives_on_clean_tone():
    x = _as_float32(signals.sustained_tone(FS, DURATION_S))
    result = clicks.detect_clicks(x, FS)
    assert result["events"] == []
    _assert_quiet_margin(result)


def test_no_false_positives_on_slowly_modulated_tone():
    x = _as_float32(signals.sustained_tone(FS, DURATION_S, am_rate_hz=0.5, am_depth_db=6.0))
    result = clicks.detect_clicks(x, FS)
    assert result["events"] == []
    _assert_quiet_margin(result)


def test_abrupt_file_edges_are_reported():
    # Documented behaviour: a file that starts mid-waveform is a click at sample 0.
    x = _as_float32(signals.sustained_tone(FS, 2.0, fade_s=0.0) + 0.1)
    times = [e["time_s"] for e in clicks.detect_clicks(x, FS)["events"]]
    assert times and times[0] < 0.002


def test_multichannel_reports_per_channel():
    clean = _as_float32(signals.sustained_tone(FS, 3.0))
    dirty = clean.copy()
    dirty[int(1.5 * FS)] += 0.01
    result = clicks.detect_clicks_multi(np.stack([clean, dirty], axis=1), FS)
    assert [len(ch["events"]) for ch in result["channels"]] == [0, 1]
