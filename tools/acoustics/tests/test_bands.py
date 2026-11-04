"""bands.py: band set agrees with the C++ contract; filters are zero-phase with the stated shape."""

import re

import numpy as np
import pytest

from tools.acoustics import bands

from conftest import REPO


def test_band_set_matches_contract():
    header = (REPO / "src" / "contract" / "SceneDescription.h").read_text(encoding="utf-8")
    match = re.search(r"kOctaveBandsHz\{([^}]*)\}", header)
    assert match, "kOctaveBandsHz not found in SceneDescription.h"
    cpp = tuple(float(v) for v in re.findall(r"[0-9]+(?:\.[0-9]+)?", match.group(1)))
    assert cpp == bands.OCTAVE_BANDS_HZ


@pytest.mark.parametrize("fs", [44100.0, 48000.0, 96000.0])
@pytest.mark.parametrize("fc", bands.OCTAVE_BANDS_HZ)
def test_band_response_shape(fs, fc):
    # Impulse response of the zero-phase filter, measured through filter_band itself.
    n = 1 << 17
    x = np.zeros(n)
    x[n // 2] = 1.0
    h = bands.filter_band(x, fs, fc)
    # Zero phase: symmetric about the impulse.
    assert np.max(np.abs(h[n // 2 + 1 :][: n // 4] - h[n // 2 - 1 :: -1][: n // 4])) < 1e-12 * np.max(np.abs(h)) + 1e-15
    H = np.abs(np.fft.rfft(h))
    f = np.fft.rfftfreq(n, 1.0 / fs)

    def gain_db(freq):
        return 20 * np.log10(np.interp(freq, f, H))

    centre = bands.exact_centre_hz(fc)
    lo, hi = bands.band_edges_hz(fc)
    assert abs(gain_db(centre)) < 0.05
    # Squared Butterworth magnitude: -6.02 dB at both edges.
    assert gain_db(lo) == pytest.approx(-6.02, abs=0.1)
    assert gain_db(hi) == pytest.approx(-6.02, abs=0.1)
    # One octave beyond the edges: at least 30 dB down (36 dB/octave skirts asymptotically).
    assert gain_db(lo / 2) < -30
    if hi * 2 < fs / 2:
        assert gain_db(hi * 2) < -30


def test_exact_centres():
    assert bands.exact_centre_hz(63.0) == 62.5
    assert bands.exact_centre_hz(1000.0) == 1000.0
    assert bands.exact_centre_hz(8000.0) == 8000.0
    assert [bands.band_key(fc) for fc in bands.OCTAVE_BANDS_HZ] == ["63", "125", "250", "500", "1000", "2000", "4000", "8000"]


def test_band_that_does_not_fit_is_rejected():
    with pytest.raises(ValueError):
        bands.octave_sos(8000.0, 16000.0)


def test_filter_bands_shape():
    x = np.random.default_rng(0).standard_normal(4800)
    assert bands.filter_bands(x, 48000.0).shape == (8, 4800)
