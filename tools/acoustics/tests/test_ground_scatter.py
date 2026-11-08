"""Phase 05b scope 7: the open_field check re-derived against the Lambert ground estimate (ledger OF)."""

import json
import pathlib

import numpy as np

from tools.acoustics import ground_scatter as g
from tools.validation import run_validation as rv

REPO = pathlib.Path(__file__).resolve().parents[3]
# ledger OF / phase-04 consult report 4, Q5: exact integral without heights and air, ρ_s = 0.4(1 − α_b)
LEDGER_OF_DB = (-23.4, -23.6, -24.4, -27.1, -28.2, -34.1, -43.1, -43.1)


def _fixture():
    sc = json.loads((REPO / "tests" / "scenes" / "valid" / "open_field.json").read_text())
    floor = sc["room"]["surfaces"]["floor"]
    rho = floor["scattering"] * (1 - np.asarray(floor["absorption"]))
    return sc, rho


def test_lambert_estimate_reproduces_ledger_of():
    sc, rho = _fixture()
    rcv = sc["listener"]["position"]
    for em in sc["emitters"]:  # L and its mirror R
        d = g.late_ratio_db(em["position"], rcv, rho, np.zeros(8))
        # heights kept here ("about 1 dB lower near the focus", report 4): the table is matched to ±0.3 dB
        assert np.all(np.abs(d - np.asarray(LEDGER_OF_DB)) <= 0.3), d


def test_lambert_estimate_with_air_and_finite_floor():
    sc, rho = _fixture()
    rcv = sc["listener"]["position"]
    m = rv.air_m()
    em = sc["emitters"][0]["position"]
    inf = g.late_ratio_db(em, rcv, rho, m)
    fin = g.late_ratio_db(em, rcv, rho, m, half_width=(0.0, 100.0, 0.0, 100.0))
    assert np.all(np.abs(inf - fin) < 0.1)
    # the re-derived check: physically −23 … −46 dB later than 50 ms, far above the shipped IR's < −60 dB,
    # which is therefore an AX16 consistency check (no scattered energy rendered, AX21), not physics
    assert np.all(fin > -47.0) and np.all(fin < -23.0)
    # grid convergence
    fine = g.late_ratio_db(em, rcv, rho, m, n_r=8000, n_phi=1440)
    assert np.all(np.abs(fine - inf) < 0.02)
