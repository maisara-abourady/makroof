"""BS.1770-4 loudness (tools/acoustics/loudness.py)."""

import numpy as np
import pytest

from tools.acoustics import loudness


def test_48k_coefficients_match_the_standard():
    (b1, a1), (b2, a2) = loudness.k_weighting(48000)
    np.testing.assert_allclose(b1, [1.53512485958697, -2.69169618940638, 1.19839281085285], atol=1e-4)
    np.testing.assert_allclose(a1, [1.0, -1.69065929318241, 0.73248077421585], atol=1e-4)
    np.testing.assert_allclose(b2, [1.0, -2.0, 1.0])
    np.testing.assert_allclose(a2, [1.0, -1.99004745483398, 0.99007225036621], atol=1e-4)


@pytest.mark.parametrize("fs", [44100, 48000, 96000])
def test_full_scale_997_hz_sine_reads_minus_3_01(fs):
    # BS.1770-4: a 0 dBFS 997 Hz sine in one front channel reads -3.01 LKFS
    t = np.arange(int(5 * fs)) / fs
    assert loudness.integrated_loudness(np.sin(2 * np.pi * 997 * t), fs) == pytest.approx(-3.01, abs=0.05)


def test_gain_moves_loudness_by_the_same_db():
    rng = np.random.default_rng(1)
    x = rng.standard_normal(48000 * 3)
    a = loudness.integrated_loudness(x, 48000)
    assert loudness.integrated_loudness(0.5 * x, 48000) == pytest.approx(a - 6.0206, abs=1e-6)
