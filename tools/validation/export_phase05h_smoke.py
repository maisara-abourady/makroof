"""Phase 05h session 1: export the estimator's smoke-agreement reference (docs/sessions/2026-11-10-phase-05h.md O5).

    python tools/validation/export_phase05h_smoke.py

Writes tests/golden/phase05h_dt1_smoke_reference.json and appends its reason to tests/golden/CHANGELOG.md.

Reference: ref_hybrid.target_hybrid at ℓ = 1.25 m (the finest certified rung, AX36), all 8 bands, for the 15 (A)
cases of phase 05b, exactly as committed in tools/validation/data/phase05b.json (ell.values.<case>."1.25".target).
Nothing is recomputed here: the script only joins those values with each case's geometry, materials and positions
(tools/validation/phase05b.py cases()) and the Python plan (ref_hybrid.phase04_plan) so the C++ test can check
that it builds the same window. Rows are flat number lists (see "columns") so the C++ test reads them without a
JSON library.
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

from tools.validation import phase05b as p5  # noqa: E402

OUT = REPO / "tests" / "golden" / "phase05h_dt1_smoke_reference.json"
CHANGELOG = REPO / "tests" / "golden" / "CHANGELOG.md"
RUNG = "1.25"
REASON = ("phase 05h session 1: smoke-agreement reference of the C++ diffuse estimator (AX39, AX42 τ): "
          "ref_hybrid.target_hybrid at ℓ = 1.25 m, 8 bands, the 15 (A) cases, copied from "
          "tools/validation/data/phase05b.json by tools/validation/export_phase05h_smoke.py")
COLUMNS = (["dims_x", "dims_y", "dims_z"] + [f"alpha_{f}" for f in ("xMin", "xMax", "yMin", "yMax", "floor", "ceiling")]
           + ["s", "src_x", "src_y", "src_z", "rcv_x", "rcv_y", "rcv_z"] + [f"target_{b}" for b in range(8)]
           + ["py_window_start_s", "py_mix_s", "py_fallback"] + [f"py_t60_{b}" for b in range(8)]
           + [f"py_target_specular_{b}" for b in range(8)] + [f"ref_change_2.5_to_1.25_{b}" for b in range(8)])


def main() -> int:
    data = json.loads((HERE / "data" / "phase05b.json").read_text())["ell"]["values"]
    names, rows = [], []
    for c in p5.cases():
        v = data[c["name"]]
        target = np.asarray(v[RUNG]["target"], float)
        coarse = np.asarray(v["2.5"]["target"], float)
        plan = p5.plan_of(c)
        row = (list(map(float, c["dims"])) + list(map(float, c["alpha_faces"])) + [float(c["s"])]
               + list(map(float, c["src"])) + list(map(float, c["rcv"])) + target.tolist()
               + [float(plan["mix"]["windowStartS"]), float(plan["mix"]["mixS"]), float(plan["fallback"])]
               + np.asarray(plan["t60"], float).tolist() + np.asarray(plan["target_specular"], float).tolist()
               + np.abs(target / coarse - 1).tolist())
        assert len(row) == len(COLUMNS)
        names.append(c["name"])
        rows.append(row)
    doc = {"description": REASON, "source": f"tools/validation/data/phase05b.json ell.values.<case>.\"{RUNG}\".target",
           "rung_m": float(RUNG), "columns": COLUMNS, "names": names, "rows": rows}
    OUT.write_text(json.dumps(doc, indent=1) + "\n")
    entry = f"\n## {datetime.date.today().isoformat()}\n\nReason: {REASON}\n\n- `{OUT.stem}`: created\n"
    log = CHANGELOG.read_text()
    if f"`{OUT.stem}`: created" not in log:
        CHANGELOG.write_text(log.rstrip("\n") + "\n" + entry)
    print(f"wrote {OUT.relative_to(REPO)} ({len(rows)} cases)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
