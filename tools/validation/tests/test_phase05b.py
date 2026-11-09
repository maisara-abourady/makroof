"""Phase 05b (B11): the committed record in tools/validation/data/phase05b.json is consistent with the
plan's rules, and docs/validation/report-phase05b.md is generated from it."""

import json

import numpy as np
import pytest

from tools.acoustics import tracer as tr
from tools.validation import phase05b as p
from tools.validation import report_phase05b as rep

D = json.loads(p.OUT.read_text())


def test_tracer_rule_seed_and_doubling():
    t = D["tracer"]
    assert t["seed"] == tr.TRACER_SEED and t["r_d_m"] == 0.5 and t["k_gate"] == 684.0
    names = [c["name"] for c in p.cases()]
    assert list(t["cases"]) == names and len(names) == 15
    for c in p.cases():
        r = t["cases"][c["name"]]
        assert r["n0"] == tr.n0(float(np.prod(c["dims"])))
        assert r["n"] == r["n0"] * 2 ** r["doublings"] and r["doublings"] <= tr.MAX_DOUBLINGS
        assert r["seed"] == tr.TRACER_SEED
        # every band has >= 3 gated bins among the bins that end by t_mix,e (pre-stated reading)
        assert r["enough_gated_bins"] and min(len(g) for g in r["gated"]) >= 3
        assert all(j < r["gate_bins"] for g in r["gated"] for j in g)


def test_self_checks_recorded_outcome():
    sc = D["selfcheck"]
    # s = 0 anchor against the exact ISM image energies: every gated bin within ±0.5 dB
    assert sc["s0"]["pass"] and sc["s0"]["max_abs_db"] <= p.SELF_S0_DB
    # s = 1 anchor against Kuttruff Table 5.2's iteration column at ±2 %: recorded as it came out (no tolerance
    # change). Cases 3-6 fail against the column; the diagnosis fields compare with the phase-05e converged a*
    # solver and Lambert MC, which the column itself exceeds by 0.6-7.2 % (ledger DB-1, open).
    for k, v in sc["s1"].items():
        assert v["pass"] == (abs(v["rel"]) <= p.SELF_S1_REL)
    assert not sc["s1_pass_all"]
    assert sc["s1_max_abs_rel_vs_mc_05e"] < 0.02  # diagnosis record (reported, not a gate)


def test_ell_ladder_consistent():
    e = D["ell"]
    assert e["ladder_m"] == list(p.ELL_LADDER) and e["tolerance_rel"] == p.ELL_TOL and e["dt_s"] == 1e-3
    steps = e["steps"]
    # ℓ is the coarsest rung whose halving changes every quantity by < 1 %
    conv = [k for k, v in steps.items() if v["converged"]]
    if e["ell_m"] is None:
        assert not conv
    else:
        first = list(steps)[[v["converged"] for v in steps.values()].index(True)]
        assert float(first.split("->")[0]) == e["ell_m"]
        for k, v in steps.items():
            assert v["converged"] == (v["max_change"] < p.ELL_TOL)
    if "factorisation_check_2.5" in e:
        assert max(max(v.values()) for v in e["factorisation_check_2.5"].values()) < 1e-3


@pytest.mark.skipif("gate" not in D, reason="window check not run")
def test_window_check_follows_ax35():
    g = D["gate"]
    # AX36 (b): gate (A) per bin and the bias trigger are not evaluated; no per-bin numbers are stored
    assert g["gate_A"] == p.NOT_EVALUATED and g["bias_diagnosis"] == p.NOT_EVALUATED
    assert all("bins" not in c for c in g["cases"].values())
    # AX36 (a): E_target certified at 2.5 m (2.5 -> 1.25 m < 1 %), evaluated at 1.25 m
    st = D["ell"]["steps"][f"{p.PREV_ELL_M}->{p.GATE_ELL_M}"]
    assert max(c["target_change"] for c in st["cases"].values()) < p.ELL_TOL
    assert max(st["a_star_change"].values()) < p.ELL_TOL
    assert g["ell_m"] == p.GATE_ELL_M and g["e_target_certified_at_m"] == p.PREV_ELL_M
    s = g["summary"]
    allw = [w for c in g["cases"].values() for w in c["window"].values()]
    for w in allw:
        assert w["ell_sensitive"] == (abs(w["margin_db"]) < w["e_target_change_2.5_to_1.25_db"])
        assert abs(w["margin_db"] - (p.WINDOW_DB - abs(w["hybrid_vs_tracer_db"]))) < 1e-12
    assert s["window_pass"] == all(abs(w["hybrid_vs_tracer_db"]) <= p.WINDOW_DB for w in allw)
    assert s["se_ok"] == all(w["se_db"] <= p.SE_MAX_DB for w in allw)
    assert s["branch"] == ("(i)" if s["window_pass"] and s["se_ok"] else "(ii)")
    # AX36 (c): never "switched" in this phase
    assert "switched" not in s["tail_level_switch"]


def test_gate_b_fails_on_the_phase05_numbers():
    gb = rep.gate_b(json.loads(rep.SCOPE6.read_text()), json.loads(rep.RESULTS.read_text()))
    assert not gb["pass"]  # → early scattered energy not promoted (phase-05b Outcome)
    assert gb["initial"]["EDT"]["delta"] > rep.DELTA and gb["initial"]["EDT"]["se_ok"]


def test_report_is_generated_from_the_data(tmp_path, monkeypatch):
    committed = rep.OUT.read_text(encoding="utf-8")
    monkeypatch.setattr(rep, "OUT", tmp_path / "r.md")
    assert rep.write() == committed


def test_case_list_is_the_plans():
    names = {c["name"] for c in p.cases()}
    assert {f"s_case_s{s}" for s in (0.1, 0.25, 0.4)} <= names
    assert {f"t52_layout{L}_s{s}" for L in (4, 5, 6) for s in (0.1, 0.25, 0.4, 1.0)} <= names
