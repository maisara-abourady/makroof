"""Phase 05b: the seeded partially diffuse ray tracer (tools/acoustics/tracer.py)."""

import numpy as np

from tools.acoustics import ref_hybrid as rh
from tools.acoustics import tracer as tr

DIMS = (20.0, 30.0, 10.0)
SRC = np.array([7.0, 20.0, 2.0])


def test_direct_sound_is_one_over_r_squared_with_air():
    # all faces absorbing: only the direct sound reaches the counting sphere (AX2 units, AX4 air)
    m = np.linspace(1e-4, 3e-2, 8)
    rcv = SRC + np.array([3.0, 0.0, 0.0])
    r = tr.trace(DIMS, [1.0] * 6, [0.0] * 6, m, SRC, rcv, 1_000_000, t_end=0.05)
    ratio = r.e.sum(axis=1) / (np.exp(-m * 3.0) / 9.0)
    # ≈ 6 900 detections: relative SE ≈ 1.3 % (chord-length spread); ±4 % is 3 SE
    assert np.all(np.abs(ratio - 1) < 0.04), ratio
    # the stamp is the closest approach: the direct sound lands in the bin of r/c = 8.7 ms
    assert r.e[:, 0].sum() > 0 and r.e[:, 1:].sum() == 0


def test_same_seed_bit_identical_and_doubling_extends():
    a = tr.trace(DIMS, [0.15] * 6, [0.3] * 6, np.zeros(8), SRC, (10, 8, 1.7), 50_000, t_end=0.1)
    b = tr.trace(DIMS, [0.15] * 6, [0.3] * 6, np.zeros(8), SRC, (10, 8, 1.7), 50_000, t_end=0.1)
    assert np.array_equal(a.e, b.e) and np.array_equal(a.e2, b.e2)
    c = tr.trace(DIMS, [0.15] * 6, [0.3] * 6, np.zeros(8), SRC, (10, 8, 1.7), 50_000, seed=tr.TRACER_SEED + 1, t_end=0.1)
    assert not np.array_equal(a.e, c.e)


def test_k_is_sum_squared_over_sum_of_squares():
    r = tr.TraceResult(4, 1, 0.01, np.array([[4.0, 0.0]] * 8), np.array([[4.0, 0.0]] * 8), 4)
    assert np.allclose(r.k[:, 0], 4.0) and np.all(r.k[:, 1] == 0)


def test_specular_room_matches_image_sources():
    # s = 0: the tracer's energy per 10 ms bin is the sum of the image energies (Kuttruff §4.1)
    m = np.zeros(8)
    var = rh.variant([[0.15] * 8] * 6, [0.0] * 6, m)
    rcv = np.array([10.0, 8.0, 1.7])
    r = tr.trace(DIMS, [0.15] * 6, [0.0] * 6, m, SRC, rcv, 1_500_000, t_end=0.08)
    ent = rh.image_entries(DIMS, var, SRC, rcv, 0.08)
    b = np.floor(ent["t"] / 0.01).astype(int)
    ism = np.bincount(b, weights=ent["spec"][0], minlength=8)[:8]
    k = r.k[0]
    sel = k >= 300  # a looser k than the gate, to keep the test fast: 3σ = 0.75 dB
    assert sel.sum() >= 2
    d = 10 * np.log10(r.e[0][sel] / ism[sel])
    assert np.all(np.abs(d) < 0.75), d


def test_window_sums_match_window_definition():
    win = tr.Window(0.03, 0.09, np.full(8, 5.0), 0.01 / 0.03)
    r = tr.trace(DIMS, [0.15] * 6, [0.2] * 6, np.zeros(8), SRC, (10, 8, 1.7), 100_000, t_end=0.1, window=win)
    assert np.all(r.window_s1 > 0) and np.all(r.window_k > 1)
    # the window sum is at most the bins' plain sum over the window span (weights ≤ 1, exp(−rate·(end − t)) ≤ 1)
    assert np.all(r.window_s1 <= r.e[:, 3:9].sum(axis=1) + 1e-15)


def test_n0_rule():
    assert tr.n0(6000.0) == 1_524_000


def test_detection_stamped_at_closest_approach_within_1_ms():
    # direct sound at r = 3 m: r/c = 8.746 ms. A stamp at sphere entry would be (r - r_d)/c = 7.29 ms (bin 7);
    # the closest-approach stamp is within d_min²/(2rc) ≤ 0.12 ms of r/c (d_min ≤ r_d), so all energy is in the 1 ms bin 8.
    rcv = SRC + np.array([3.0, 0.0, 0.0])
    r = tr.trace(DIMS, [1.0] * 6, [0.0] * 6, np.zeros(8), SRC, rcv, 300_000, t_end=0.02, bin_s=0.001)
    assert r.e[0, 8] > 0
    assert r.e[0].sum() == r.e[0, 8]
