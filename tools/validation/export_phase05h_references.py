"""Phase 05h session 2: export the reference goldens of the AX43 agreement suite, the AX45 regression gate and
the tracer check (docs/sessions/2026-11-10-phase-05h.md O15; decision D-H2 in docs/review/phase-05h/).

    python tools/validation/export_phase05h_references.py

Writes, and appends each reason to tests/golden/CHANGELOG.md:
- tests/golden/phase05h_agreement_reference.json   (AX43: 70 cases x 8 bands; AX45: 9 cases x 8 bands)
- tests/golden/phase05h_tracer_reference.json      (the 15 (A) cases at 500 Hz-2 kHz; layouts 4/5 at s = 1 in the
                                                    outer bands 125 Hz, 4 kHz, 8 kHz)

Nothing acoustic is computed here: every value is joined from committed data.
- ref_hybrid.target_hybrid at the finest rung with the coarser rung beside it:
  tools/validation/data/phase05b.json (the 15 (A) cases, `ell.values`, 2.5 and 1.25 m, 8 bands; the 30 BRAS pairs,
  `r1.rooms.<room>.rungs`, 2.5 and 1.25 m, 500 Hz-2 kHz), tools/validation/data/phase05_scope6.json (the BRAS pairs'
  other bands, one rung, uncertified), tools/validation/data/phase05h_hybrid_references.jsonl (the references
  computed in session 2 with tools/validation/hybrid_fast.py for the six Phase 04 rooms, W1, W2, the CS-NW+ placements
  and the small room, 2.5 and 1.25 m, 8 bands; produced by the script recorded in
  docs/review/phase-05h/6-orchestrator-K20-certified-listing.md).
- l_ref per case-band = |E(1.25 m) / E(2.5 m) - 1| (AX36's rung rule); `certified` = both rungs exist and l_ref < 1 %.
  Which case-bands the C++ test gates is D-H2's rule (`gated` column), never the implementer's.
- The tracer reference (independent of ref_hybrid): E_tr = E_AX16,py / 10^(dL_tr / 10) from the committed
  phase05b.json `gate` (500 Hz-2 kHz) and `outer_bands` (125 Hz, 4 kHz, 8 kHz) entries, where E_AX16,py is the
  Python Phase 04 plan's AX16 E_target (ref_hybrid.phase04_plan, deterministic; equal to render_cli's, tested).
Rows are flat number lists (see "columns") so the C++ tests read them without a JSON library.
"""

from __future__ import annotations

import datetime
import json
import pathlib
import sys

import numpy as np

HERE = pathlib.Path(__file__).resolve().parent
REPO = HERE.parents[1]
sys.path.insert(0, str(REPO))

from tools.acoustics import ref_hybrid as rh  # noqa: E402
from tools.validation import phase05b as p5  # noqa: E402
from tools.validation import scope6  # noqa: E402

GOLDEN = REPO / "tests" / "golden"
CHANGELOG = GOLDEN / "CHANGELOG.md"
DATA = HERE / "data"
FACES = ("xMin", "xMax", "yMin", "yMax", "floor", "ceiling")
AQ = [0.15, 0.18, 0.2, 0.22, 0.24, 0.26, 0.28, 0.3]
AQ9 = (3, 4, 5)
REASON_AGREE = ("phase 05h session 2: AX43 agreement and AX45 regression references of the C++ diffuse estimator "
                "(ref_hybrid.target_hybrid at the finest rung with l_ref per case-band, AX36; joined from "
                "tools/validation/data/phase05b.json, phase05_scope6.json and phase05h_hybrid_references.jsonl by "
                "tools/validation/export_phase05h_references.py; the gated set follows D-H2)")
REASON_TRACER = ("phase 05h session 2: tracer window reference of the 15 (A) cases (500 Hz-2 kHz) and the outer-band "
                 "check (layouts 4/5 at s = 1; 125 Hz, 4 kHz, 8 kHz), E_tr = E_AX16,py / 10^(dL_tr/10) from the "
                 "committed phase05b.json gate and outer_bands entries, by tools/validation/export_phase05h_references.py")

COLUMNS = (["dims_x", "dims_y", "dims_z"] + [f"alpha_{f}_{b}" for f in FACES for b in range(8)] + [f"s_{f}" for f in FACES]
           + ["rcv_x", "rcv_y", "rcv_z", "src0_x", "src0_y", "src0_z", "src1_x", "src1_y", "src1_z", "num_emitters",
              "ref_emitter"]
           + [f"ref_fine_{b}" for b in range(8)] + [f"ref_coarse_{b}" for b in range(8)] + [f"l_ref_{b}" for b in range(8)]
           + [f"certified_{b}" for b in range(8)] + [f"gated_{b}" for b in range(8)] + ["suite", "cls"]
           + ["py_window_start_s", "py_mix_s", "py_fallback"] + [f"py_t60_{b}" for b in range(8)]
           + [f"py_target_specular_{b}" for b in range(8)] + [f"py_target_ax16_{b}" for b in range(8)] + ["room"])
REASON_ROOM = ("phase 05h D-H3 (a) (docs/review/phase-05h/20-decider-decision-D-H3.md): AX43's pooled bias check pools per "
               "reference room with z' = (C++ - ref) / sqrt(SE^2 + l_ref^2); the room id (the reference that shares a "
               "case's discretisation residual) is written by the generating script, a schema addition")
REASON_0625 = ("phase 05h H3-F6 (docs/review/phase-05h/25-decider-decision-D-H3-r2.md addendum; K-a4 (iii)): the finest "
               "certified rung per AX43: dead_booth, living_room, classroom and club (both emitters, 8 bands) referenced at "
               "0.625 m with l_ref = the 1.25 -> 0.625 m change (dead_booth 0.28 %, up from 0.17 %); the agreement suite was "
               "green at 1.25 m and is re-run at 0.625 m; nothing regenerated to pass")
REASON_05I = ("phase 05i scope 1 (D-H2 (a)/(c), decider file 19; AX43 (c)): the 30 BRAS pairs' outer bands (250 Hz and "
              "4 kHz, then 125 Hz and 8 kHz, 63 Hz last) referenced at the 2.5 and 1.25 m rungs by "
              "tools/validation/compute_phase05i_bras_references.py (phase05b.step_r1's recipe per band column; its --check "
              "reproduces the committed R1 500 Hz values in CR2 and CR3 exactly; provenance in "
              "tools/validation/data/phase05i_bras_references.provenance.json); every one of the 150 case-bands certifies "
              "(l_ref <= 0.38 %) and is gated under rule G-a: AX43 560 of 560, AX45 72 of 72; no existing reference value "
              "changed; the 63 Hz column is gated as an agreement with ref_hybrid, never claimed as a room validation below "
              "the Schroeder frequency")
SUITES = {"AX43": 0.0, "AX45": 1.0}
# AX46 classes: 0 reference positions, 1 one-end near-wall, 2 absorbing face, 3 small rooms, 4 100 m (none here),
# 5 BRAS (measured-room pairs), 6 both-near / placements reported only
CLASSES = {"reference": 0.0, "near_wall": 1.0, "absorbing": 2.0, "small": 3.0, "bras": 5.0}


def gated_rule(certified: np.ndarray, decision: dict) -> np.ndarray:
    """D-H2: the gated set. Default rule (G-a): every certified case-band."""
    rule = decision.get("rule", "G-a")
    if rule == "G-a":
        return certified.astype(float)
    raise ValueError(rule)


def fixture(name: str) -> dict:
    path = REPO / "tests" / "scenes" / "valid" / f"{name}.json"
    sc = json.loads(path.read_text())
    si = scope6.scene_inputs(path)
    return {"dims": list(si["dims"]), "alpha": [list(map(float, a)) for a in si["alpha"]], "s": [float(x) for x in si["s"]],
            "rcv": list(map(float, si["rcv"])), "ems": [list(map(float, e["position"])) for e in sc["emitters"]]}


def bras_scene(pair: str) -> dict:
    path = REPO / "tests" / "scenes" / "validation" / f"{pair}.json"
    sc = json.loads(path.read_text())
    si = scope6.scene_inputs(path)
    return {"dims": list(si["dims"]), "alpha": [list(map(float, a)) for a in si["alpha"]], "s": [float(x) for x in si["s"]],
            "rcv": list(map(float, si["rcv"])), "ems": [list(map(float, e["position"])) for e in sc["emitters"]]}


def plan(c: dict, src) -> dict:
    var = rh.variant(c["alpha"], c["s"], scope6.air_m())
    return rh.phase04_plan(c["dims"], var, src, c["rcv"])


def room_of(name: str) -> str:
    """The reference room that shares a case's discretisation residual (D-H3 (a), AX43's pooled check per reference
    room): each BRAS room over its pairs, each Phase 04 room and W1/W2 over its emitters and placements, each (A)
    case its own room."""
    for prefix in ("bras_cr2", "bras_cr3", "bras_cr4", "dead_booth", "living_room", "classroom", "club", "concert_hall_box",
                   "stone_box", "W1", "W2", "dt6_small_room"):
        if name.startswith(prefix):
            return prefix
    return name


ROOM_IDS: dict = {}


def row_of(name, suite, cls, c, srcs, ref_emitter, fine, coarse, decision) -> list:
    fine = np.asarray(fine, float)
    coarse = np.asarray(coarse, float)
    l_ref = np.where(np.isfinite(fine) & np.isfinite(coarse) & (coarse > 0), np.abs(fine / coarse - 1), np.nan)
    certified = np.isfinite(l_ref) & (l_ref < 0.01)
    gated = gated_rule(certified, decision)
    p = plan(c, srcs[ref_emitter])
    src1 = srcs[1] if len(srcs) > 1 else [float("nan")] * 3
    row = (list(map(float, c["dims"])) + [float(c["alpha"][f][b]) for f in range(6) for b in range(8)]
           + [float(x) for x in c["s"]] + list(map(float, c["rcv"])) + list(map(float, srcs[0])) + list(map(float, src1))
           + [float(len(srcs)), float(ref_emitter)] + fine.tolist() + coarse.tolist()
           + [float(x) if np.isfinite(x) else float("nan") for x in l_ref] + certified.astype(float).tolist() + gated.tolist()
           + [SUITES[suite], CLASSES[cls]] + [float(p["mix"]["windowStartS"]), float(p["mix"]["mixS"]), float(p["fallback"])]
           + np.asarray(p["t60"], float).tolist() + np.asarray(p["target_specular"], float).tolist()
           + np.asarray(p["target_ax16"], float).tolist()
           + [float(ROOM_IDS.setdefault(room_of(name), len(ROOM_IDS)))])
    assert len(row) == len(COLUMNS), (len(row), len(COLUMNS))
    return [name] + row


def load_phase05i_bras() -> dict:
    """Phase 05i scope 1: the BRAS pairs' outer-band references (tools/validation/compute_phase05i_bras_references.py),
    {(room, rung, band): {pair: E_target}}; empty when the file is absent."""
    path = DATA / "phase05i_bras_references.jsonl"
    if not path.exists():
        return {}
    out = {}
    for line in path.read_text().splitlines():
        if line.strip():
            r = json.loads(line)
            out[(r["room"], float(r["rung"]), int(r["band"]))] = r["e_target"]
    return out


def load_session2() -> dict:
    out = {}
    path = DATA / "phase05h_hybrid_references.jsonl"
    for line in path.read_text().splitlines():
        r = json.loads(line)
        out.setdefault(r["case"], {})[str(r["rung"])] = r
    return out


def main() -> int:
    decision = json.loads((DATA / "phase05h_dh2_decision.json").read_text()) if (DATA / "phase05h_dh2_decision.json").exists() else {}
    d05b = json.loads((DATA / "phase05b.json").read_text())
    s6 = json.loads((DATA / "phase05_scope6.json").read_text())
    s2 = load_session2()
    names, rows = [], []

    def s2_ref(case):
        # The finest two rungs present (AX43 "the finest certified rung, with l_ref recorded"; H3-F6, file 25
        # addendum: the small rooms move to 0.625 m once that rung is computed; a case with one rung stays
        # single-rung / uncertified).
        m = s2.get(case, {})
        rungs = sorted((float(k) for k in m), reverse=False)
        if not rungs:
            return [float("nan")] * 8, [float("nan")] * 8
        fine = m[str(rungs[0])]["target_hybrid"]
        coarse = m[str(rungs[1])]["target_hybrid"] if len(rungs) > 1 else [float("nan")] * 8
        return fine, coarse

    def add(name, suite, cls, c, srcs, ref_emitter, fine, coarse):
        names.append(name)
        rows.append(row_of(name, suite, cls, c, srcs, ref_emitter, fine, coarse, decision))

    # AX43 (70 cases): 15 (A)
    for c in p5.cases():
        v = d05b["ell"]["values"][c["name"]]
        cc = {"dims": c["dims"], "alpha": [[a] * 8 for a in c["alpha_faces"]], "s": [c["s"]] * 6, "rcv": c["rcv"]}
        cls = "reference" if c["group"] == "s_cases" else "absorbing"
        add(c["name"], "AX43", cls, cc, [c["src"]], 0, v["1.25"]["target"], v["2.5"]["target"])
    # six Phase 04 rooms x 2 emitters
    for r in ("dead_booth", "living_room", "classroom", "club", "concert_hall_box", "stone_box"):
        f = fixture(r)
        for e in (0, 1):
            fine, coarse = s2_ref(f"{r}_e{e}")
            add(f"{r}_e{e}", "AX43", "reference", f, f["ems"], e, fine, coarse)
    # W1 x 2, W2 x 2
    w1 = {"dims": [20.0, 30.0, 10.0], "alpha": [AQ] * 6, "s": [0.3] * 6, "rcv": [10.0, 8.0, 1.7]}
    E = [[7.0, 20.0, 2.0], [13.0, 20.0, 2.0]]
    w2 = {"dims": [20.0, 30.0, 10.0], "alpha": [[0.02] * 8] * 2 + [[0.8] * 8] * 4, "s": [0.0, 0.0, 0.1, 0.1, 0.1, 0.1],
          "rcv": [10.0, 8.0, 1.7]}
    for e in (0, 1):
        fine, coarse = s2_ref(f"W1_e{e}")
        add(f"W1_e{e}", "AX43", "reference", w1, E, e, fine, coarse)
    for e in (0, 1):
        fine, coarse = s2_ref(f"W2_e{e}")
        add(f"W2_e{e}", "AX43", "reference", w2, E, e, fine, coarse)
    # 30 BRAS pairs (initial alpha), reference at 500 Hz-2 kHz (r1, two rungs); the other bands at the two rungs where
    # phase 05i computed them (phase05i_bras_references.jsonl, step_r1's recipe per band), else one rung (scope6)
    b05i = load_phase05i_bras()
    for room in ("CR2", "CR3", "CR4"):
        r1 = d05b["r1"]["rooms"][room]
        for pair, fine3 in r1["rungs"]["1.25"]["e_target"].items():
            coarse3 = r1["rungs"]["2.5"]["e_target"][pair]
            other = s6["bras"][room]["pairs"][pair]["initial"]["target_hybrid"]
            fine = [float("nan")] * 8
            coarse = [float("nan")] * 8
            for i, b in enumerate(AQ9):
                fine[b], coarse[b] = fine3[i], coarse3[i]
            for b in range(8):
                if b in AQ9:
                    continue
                f05i, c05i = b05i.get((room, 1.25, b)), b05i.get((room, 2.5, b))
                if f05i is not None and c05i is not None:
                    fine[b], coarse[b] = f05i[pair], c05i[pair]  # two rungs: l_ref = the 2.5 -> 1.25 m change
                else:
                    coarse[b] = other[b]  # single rung, uncertified
            bs = bras_scene(pair)
            add(pair, "AX43", "bras", bs, bs["ems"], 0, fine, coarse)
    # CS-NW+: W1 listener at a wall / edge / corner at 0.1 m and at a wall at 0.3 m, both emitters; emitter at a wall
    nw = {"listener_wall_0.1": [10.0, 0.1, 1.7], "listener_edge_0.1": [0.1, 0.1, 1.7], "listener_corner_0.1": [0.1, 0.1, 9.9],
          "listener_wall_0.3": [10.0, 0.3, 1.7]}
    for k, rcv in nw.items():
        for e in (0, 1):
            fine, coarse = s2_ref(f"W1_{k}_e{e}")
            add(f"W1_{k}_e{e}", "AX43", "near_wall", dict(w1, rcv=rcv), E, e, fine, coarse)
    fine, coarse = s2_ref("W1_emitter_wall_0.1_e0")
    add("W1_emitter_wall_0.1_e0", "AX43", "near_wall", w1, [[7.0, 29.9, 2.0], E[1]], 0, fine, coarse)
    assert sum(1 for r in rows if r[1 + COLUMNS.index("suite")] == 0.0) == 70, "AX43 has 70 cases"

    # AX45 (9 cases): stone_box x 2, W1 x 2, the three (A) s-cases, the small room x 2
    sb = fixture("stone_box")
    for e in (0, 1):
        fine, coarse = s2_ref(f"stone_box_e{e}")
        add(f"AX45/stone_box_e{e}", "AX45", "reference", sb, sb["ems"], e, fine, coarse)
    for e in (0, 1):
        fine, coarse = s2_ref(f"W1_e{e}")
        add(f"AX45/W1_e{e}", "AX45", "reference", w1, E, e, fine, coarse)
    for c in p5.cases():
        if c["group"] == "s_cases":
            v = d05b["ell"]["values"][c["name"]]
            cc = {"dims": c["dims"], "alpha": [[a] * 8 for a in c["alpha_faces"]], "s": [c["s"]] * 6, "rcv": c["rcv"]}
            add(f"AX45/{c['name']}", "AX45", "reference", cc, [c["src"]], 0, v["1.25"]["target"], v["2.5"]["target"])
    sr = {"dims": [3.0, 2.5, 2.5], "alpha": [[0.03] * 8] * 6, "s": [0.1] * 6, "rcv": [1.5, 0.667, 0.425]}
    srcs = [[1.05, 1.667, 0.5], [1.95, 1.667, 0.5]]
    for e in (0, 1):
        fine, coarse = s2_ref(f"dt6_small_room_e{e}")
        add(f"AX45/dt6_small_room_e{e}", "AX45", "small", sr, srcs, e, fine, coarse)
    assert sum(1 for r in rows if r[1 + COLUMNS.index("suite")] == 1.0) == 9

    doc = {"description": REASON_AGREE, "rule": decision.get("rule", "G-a"), "columns": COLUMNS, "names": names,
           "rows": [r[1:] for r in rows]}
    (GOLDEN / "phase05h_agreement_reference.json").write_text(json.dumps(doc, indent=1, allow_nan=True) + "\n")

    # Tracer reference (15 (A) cases at 500 Hz-2 kHz; outer bands for layouts 4/5 at s = 1)
    tcols = (["dims_x", "dims_y", "dims_z"] + [f"alpha_{f}" for f in FACES] + ["s", "src_x", "src_y", "src_z", "rcv_x", "rcv_y", "rcv_z"]
             + [f"e_tr_{b}" for b in range(8)] + [f"se_tr_db_{b}" for b in range(8)] + [f"py_target_ax16_{b}" for b in range(8)]
             + ["py_window_start_s", "py_mix_s", "py_fallback"])
    tnames, trows = [], []
    gate = d05b["gate"]["cases"]
    outer = d05b["outer_bands"]["cases"]
    for c in p5.cases():
        p = p5.plan_of(c)
        e_tr = [float("nan")] * 8
        se = [float("nan")] * 8
        for b, hz in zip(AQ9, (500, 1000, 2000)):
            w = gate[c["name"]]["window"][str(hz)]
            e_tr[b] = float(p["target_ax16"][b]) / 10 ** (w["delta_lb_tr_db"] / 10)
            se[b] = float(w["se_db"])
        if c["name"] in outer:
            for b, hz in zip((1, 6, 7), (125, 4000, 8000)):
                w = outer[c["name"]]["bands"][str(hz)]
                e_tr[b] = float(p["target_ax16"][b]) / 10 ** (w["delta_lb_tr_db"] / 10)
                se[b] = float(w["se_db"])
        row = (list(map(float, c["dims"])) + list(map(float, c["alpha_faces"])) + [float(c["s"])] + list(map(float, c["src"]))
               + list(map(float, c["rcv"])) + e_tr + se + np.asarray(p["target_ax16"], float).tolist()
               + [float(p["mix"]["windowStartS"]), float(p["mix"]["mixS"]), float(p["fallback"])])
        assert len(row) == len(tcols)
        tnames.append(c["name"])
        trows.append(row)
    tdoc = {"description": REASON_TRACER, "tolerance_db": 1.0, "columns": tcols, "names": tnames, "rows": trows}
    (GOLDEN / "phase05h_tracer_reference.json").write_text(json.dumps(tdoc, indent=1, allow_nan=True) + "\n")

    log = CHANGELOG.read_text()
    for stem, reason in (("phase05h_agreement_reference", REASON_AGREE), ("phase05h_tracer_reference", REASON_TRACER)):
        if f"`{stem}`: created" not in log:
            log = log.rstrip("\n") + f"\n\n## {datetime.date.today().isoformat()}\n\nReason: {reason}\n\n- `{stem}`: created\n"
    if "`phase05h_agreement_reference`: the four small rooms at the 0.625 m rung" not in log:
        log = (log.rstrip("\n") + f"\n\n## {datetime.date.today().isoformat()}\n\nReason: " + REASON_0625
               + "\n\n- `phase05h_agreement_reference`: the four small rooms at the 0.625 m rung (dead_booth, living_room, "
               "classroom, club; l_ref = the 1.25 -> 0.625 m change; no tolerance, N or case changed)\n")
    if "`phase05h_agreement_reference`: `room` column added" not in log:
        log = (log.rstrip("\n") + f"\n\n## {datetime.date.today().isoformat()}\n\nReason: " + REASON_ROOM
               + "\n\n- `phase05h_agreement_reference`: `room` column added (schema only; no reference value changed)\n")
    if load_phase05i_bras() and "`phase05h_agreement_reference`: extended (150 case-bands promoted" not in log:
        log = (log.rstrip("\n") + f"\n\n## {datetime.date.today().isoformat()}\n\nReason: " + REASON_05I
               + "\n\n- `phase05h_agreement_reference`: extended (150 case-bands promoted to gated: the 30 BRAS pairs at "
               "63, 125, 250 Hz, 4 and 8 kHz; no tolerance, N or case changed)\n")
    CHANGELOG.write_text(log)
    n_cert = sum(int(r[1 + COLUMNS.index(f"certified_{b}")]) for r in rows for b in range(8))
    n_gated = sum(int(r[1 + COLUMNS.index(f"gated_{b}")]) for r in rows for b in range(8))
    print(f"wrote {len(rows)} cases ({n_cert} certified case-bands, {n_gated} gated) and {len(trows)} tracer cases")
    return 0


if __name__ == "__main__":
    sys.exit(main())
