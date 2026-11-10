"""Phase 05b session 2: the numbers AX37–AX46 and the board answers quote are those in the committed prototype data
(tools/validation/data/phase05b2_dt1.json). Data only, no numba: the prototype itself is offline
(tools/validation/phase05b2_dt1.py; as-run scripts in tools/validation/phase05b2_asrun/)."""

import json
import pathlib

D = json.loads((pathlib.Path(__file__).resolve().parents[1] / "data" / "phase05b2_dt1.json").read_text())


def _rng(vals):
    return round(min(vals), 2), round(max(vals), 2)


def test_ax16_against_long_runs_c16g():
    """AX16 'switched' note and Q2a's old-error line (C16 (g), 1 kHz)."""
    g = D["c16"]["g_ax16_vs_long"]
    s03 = [v["ax16_minus_long_db"] for k, v in g.items() if "_s0.3_" in k]
    assert _rng(s03) == (0.02, 0.02)
    low = [g[f"cube100_lowalpha0.05_s1_e{e}"]["ax16_minus_long_db"] for e in (0, 1)]
    assert [round(x, 2) for x in low] == [0.06, 0.10]
    flo = [g[f"cube100_absorbing_floor_s1_e{e}"]["ax16_minus_long_db"] for e in (0, 1)]
    assert [round(x, 2) for x in flo] == [2.38, 2.39]


def test_restore_times_c14c():
    """AQ10 / AX38 4c: (A) lands every gated scene at the bound; (B) is 2.16–4.83 s per restore."""
    r = D["c14"]["c_restore"]
    assert all(abs(v["restore_s"] - 30 / 14) < 0.01 for k, v in r.items() if "/A/" in k)
    b = [v["restore_s"] for k, v in r.items() if "/B/" in k]
    assert _rng(b) == (2.16, 4.83)


def test_capped_se_at_nmax_1024_c16f():
    """AX41 cost line at n*_max 1 024 (joint rule)."""
    c = D["c16"]["cases"]
    se = lambda k: [e["se_db"] for e in c[k]["nmax1024"]["emitters"]]
    lay = [x for k in c if k.startswith(("layout4_s1/", "layout5_s1/")) and "both" not in k for x in se(k)]
    lay += [x for k in ("layout4_s1/both_wall", "layout4_s1/both_corner", "layout5_s1/both_wall", "layout5_s1/both_corner")
            for x in se(k)]
    assert _rng(lay) == (0.13, 1.33)
    assert _rng(se("cube100_lowalpha0.05_s1")) == (0.44, 0.50)
    assert _rng(se("cube100_alpha0.10-0.22_s0.3") + se("cube100_lowalpha0.05_s0.3")) == (0.09, 0.15)
    assert _rng(se("cube100_absorbing_floor_s1")) == (0.09, 0.10)


def test_replicates_pass_c15():
    """Seat 2's pre-registered check in the closed 100 m cubes: every row passes."""
    assert all(v[n]["pass"] for v in D["c15"]["cases"].values() for n in ("nmax8000", "nmax1020"))


def test_case_count_c14e():
    """AX43: 70 cases, 560 case-bands, z_FW 4.290."""
    e = D["c14"]["e_case_count"]
    assert e["total_both_emitters"] == 70 and round(e["z_FW_both_emitters"], 3) == 4.290


def test_halls_not_capped_c18():
    """J1 L5 / phase-12 Trigger 2: four 20 × 30 × 10 m halls with an audience floor and s ≤ 0.5 are not capped."""
    h = D["c18"]
    assert len(h) == 4 and not any(v["cap"] for v in h.values()) and max(x for v in h.values() for x in v["se"]) <= 0.083
