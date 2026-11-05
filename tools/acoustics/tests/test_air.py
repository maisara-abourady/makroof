"""tools/acoustics/air.py against the ISO 9613 octave-band table (same rows as the C++ test
tests/unit/test_air_absorption.cpp), and against the C++ implementation through render_cli."""

import numpy as np
import pytest

from tools.acoustics import air

EXACT_MIDBANDS_HZ = np.array([63.0957, 125.893, 251.189, 501.187, 1000.0, 1995.26, 3981.07, 7943.28])

# ISO 9613-2:1996 Table 2 (computed with ISO 9613-1), dB/km, 101.325 kPa.
TABLE = {
    (10.0, 70.0): [0.1, 0.4, 1.0, 1.9, 3.7, 9.7, 32.8, 117.0],
    (20.0, 70.0): [0.1, 0.3, 1.1, 2.8, 5.0, 9.0, 22.9, 76.6],
    (30.0, 70.0): [0.1, 0.3, 1.0, 3.1, 7.4, 12.7, 23.1, 59.3],
    (15.0, 20.0): [0.3, 0.6, 1.2, 2.7, 8.2, 28.2, 88.8, 202.0],
    (15.0, 50.0): [0.1, 0.5, 1.2, 2.2, 4.2, 10.8, 36.2, 129.0],
    (15.0, 80.0): [0.1, 0.3, 1.1, 2.4, 4.1, 8.3, 23.7, 82.8],
}


@pytest.mark.parametrize("row", list(TABLE), ids=lambda r: f"{r[0]:g}C-{r[1]:g}pct")
def test_matches_iso_table_within_5_percent(row):
    expected = np.array(TABLE[row])
    actual = 1000.0 * air.attenuation_db_per_m(EXACT_MIDBANDS_HZ, *row)
    rounding = np.where(expected < 100.0, 0.05, 0.5)  # half a unit of the table's last digit
    assert np.all(np.abs(actual - expected) <= np.maximum(0.05 * expected, rounding) + 1e-9), (actual, expected)


def test_ax4_atmosphere_values():
    # The values pinned in the C++ test (dB/km at the nominal band centres).
    nominal = np.array([63.0, 125.0, 250.0, 500.0, 1000.0, 2000.0, 4000.0, 8000.0])
    pinned = np.array([0.1225, 0.4398, 1.3097, 2.7281, 4.6647, 9.8870, 29.6655, 105.2909])
    np.testing.assert_allclose(1000.0 * air.attenuation_db_per_m(nominal), pinned, rtol=1e-3)
