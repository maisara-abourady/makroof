"""Atmospheric absorption, ISO 9613-1:1993 (pure-tone attenuation coefficient, eq. (3)-(5) and the
saturation vapour pressure of Annex B).

A second implementation, independent of ``src/sim/AirAbsorption.cpp``, so the Phase 03 tests can
compute expected per-band levels themselves. AX4 fixes the atmosphere at 20 degC, 50 % RH,
101.325 kPa.
"""

from __future__ import annotations

import numpy as np

TEMPERATURE_C = 20.0
RELATIVE_HUMIDITY_PERCENT = 50.0
PRESSURE_KPA = 101.325


def attenuation_db_per_m(
    f_hz,
    temperature_c: float = TEMPERATURE_C,
    relative_humidity_percent: float = RELATIVE_HUMIDITY_PERCENT,
    pressure_kpa: float = PRESSURE_KPA,
):
    """Attenuation coefficient alpha in dB/m at frequency ``f_hz`` (scalar or array)."""
    f = np.asarray(f_hz, dtype=np.float64)
    t = temperature_c + 273.15
    p_rel = pressure_kpa / 101.325
    t_rel = t / 293.15
    c = -6.8346 * (273.16 / t) ** 1.261 + 4.6151
    h = relative_humidity_percent * 10.0**c / p_rel  # molar concentration of water vapour, %
    fr_o = p_rel * (24.0 + 4.04e4 * h * (0.02 + h) / (0.391 + h))
    fr_n = p_rel * t_rel**-0.5 * (9.0 + 280.0 * h * np.exp(-4.170 * (t_rel ** (-1.0 / 3.0) - 1.0)))
    return 8.686 * f**2 * (
        1.84e-11 / p_rel * np.sqrt(t_rel)
        + t_rel**-2.5 * (0.01275 * np.exp(-2239.1 / t) / (fr_o + f**2 / fr_o) + 0.1068 * np.exp(-3352.0 / t) / (fr_n + f**2 / fr_n))
    )


def amplitude(f_hz, distance_m):
    """Pressure factor 10^(-alpha r / 20) of the AX4 atmosphere over ``distance_m``."""
    return 10.0 ** (-attenuation_db_per_m(f_hz) * np.asarray(distance_m, dtype=np.float64) / 20.0)
