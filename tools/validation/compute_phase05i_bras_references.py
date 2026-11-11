"""Phase 05i scope 1 (D-H2 (c), AX43 (c)): the BRAS pairs' outer-band references of the AX43 agreement suite.

    python tools/validation/compute_phase05i_bras_references.py            # every missing unit, committed order
    python tools/validation/compute_phase05i_bras_references.py --check    # recipe check: CR2 and CR3 at 500 Hz

Offline only (numba, tools/validation/requirements-offline.txt); CI never runs it and no gate computes a reference
live (D-H2 (c)). The recipe is phase05b.step_r1's (the R1 references of the 500 Hz-2 kHz columns, committed in
tools/validation/data/phase05b.json `r1`), unchanged, applied one band column at a time:
- per BRAS room (CR2, CR3, CR4; initial alpha, the Phase 05 positions), per rung (2.5 and 1.25 m), per band:
  hybrid_fast.FastRoomKernel(dims, rung, t_end, variant without air, band), t_end = max over the room's pairs of
  t_mix,e + crossfade half + 2 ms (as step_r1);
- solved with phase05b.lean_solve per pair while the dense kernel plus its transform fits R1_MEMORY_BUDGET_GB,
  else with phase05b.chunked_solve over every pair at once (phase-05b2 D-T2; CR4 at 1.25 m);
- the air factor exp(-m_b c t) applied per bin, then ref_hybrid.target_hybrid(plan, env)[band] per pair.
Order (D-H2 (c), decider file 19): 250 Hz and 4 kHz, then 125 Hz and 8 kHz, 63 Hz last; within a band the rooms
from the smallest kernel up. Each finished (room, rung, band) unit is appended to the JSONL at once, so a run that
stops resumes where it stopped; tools/validation/export_phase05h_references.py joins the rows.
"""

from __future__ import annotations

import argparse
import json
import pathlib
import platform
import subprocess
import sys
import time

import numpy as np

HERE = pathlib.Path(__file__).resolve().parent
REPO = HERE.parents[1]
sys.path.insert(0, str(REPO))

from tools.acoustics import radiosity  # noqa: E402
from tools.acoustics import ref_hybrid as rh  # noqa: E402
from tools.validation import phase05b as p5  # noqa: E402
from tools.validation import scope6  # noqa: E402

OUT = HERE / "data" / "phase05i_bras_references.jsonl"
PROVENANCE = HERE / "data" / "phase05i_bras_references.provenance.json"
BANDS_HZ = (63, 125, 250, 500, 1000, 2000, 4000, 8000)
ORDER = (2, 6, 1, 7, 0)  # D-H2 (c): 250 Hz, 4 kHz, then 125 Hz, 8 kHz, 63 Hz last
ROOMS = ("CR2", "CR3", "CR4")
RUNGS = (p5.PREV_ELL_M, p5.GATE_ELL_M)


def log(*a):
    print(time.strftime("%H:%M:%S"), *a, flush=True)


def room_setup(room: str) -> dict:
    """step_r1's per-room inputs, unchanged."""
    m = scope6.air_m()
    names = scope6.pair_names(room)
    sis = {n: scope6.scene_inputs(scope6.rv.SCENES / f"{n}.json") for n in names}
    dims = tuple(float(x) for x in sis[names[0]]["dims"])
    var = rh.variant(sis[names[0]]["alpha"], sis[names[0]]["s"], m)
    var0 = rh.variant(sis[names[0]]["alpha"], sis[names[0]]["s"], np.zeros(8))
    plans = {n: rh.phase04_plan(dims, var, sis[n]["src"], sis[n]["rcv"]) for n in names}
    t_end = max(pl["mix"]["mixS"] for pl in plans.values()) + rh.CROSSFADE_HALF_S + 2e-3
    return {"m": m, "names": names, "sis": sis, "dims": dims, "var0": var0, "plans": plans, "t_end": t_end,
            "T": int(np.ceil(t_end / rh.DT))}


def compute_unit(room: str, size: float, b: int, rs: dict) -> dict:
    """One (room, rung, band): E_target per pair, as step_r1 computes it for its band columns."""
    from tools.validation import hybrid_fast
    dims, T, names, sis = rs["dims"], rs["T"], rs["names"], rs["sis"]
    p_ = radiosity.box_patches(dims, size)
    N = len(p_.areas)
    need = N * N * T * 4 / 1e9 + N * N * (T + 1) * 8 / 1e9
    dense_kernel = N * N * T * 4 / 1e9
    use_chunked = need > p5.R1_MEMORY_BUDGET_GB
    if use_chunked and dense_kernel >= p5.R1_MEMORY_BUDGET_GB:
        raise RuntimeError(f"{room} {size} m: the float32 kernel alone ({dense_kernel:.1f} GB) exceeds the budget")
    t0 = time.time()
    tb = (np.arange(T) + 0.5) * rh.DT
    rk = hybrid_fast.FastRoomKernel(dims, size, rs["t_end"], rs["var0"], b)
    t_kernel = time.time() - t0
    env = {}
    if use_chunked:
        inc = np.stack([rh.injection(rk, sis[n]["src"]) for n in names])
        gat = np.stack([rh.gather_kernel(rk, sis[n]["rcv"]) for n in names])
        e_all = p5.chunked_solve(rk, inc, gat)
        for i, n in enumerate(names):
            env[n] = e_all[i] * np.exp(-rs["m"][b] * rh.C_SOUND * tb)
    else:
        for n in names:
            e0 = p5.lean_solve(rk, rh.injection(rk, sis[n]["src"])[None], rh.gather_kernel(rk, sis[n]["rcv"])[None])[0]
            env[n] = e0 * np.exp(-rs["m"][b] * rh.C_SOUND * tb)
    del rk
    e_target = {}
    for n in names:
        full = np.zeros((8, T))
        full[b] = env[n]
        e_target[n] = float(rh.target_hybrid(rs["plans"][n], full)[b])
    return {"room": room, "rung": size, "band": b, "band_hz": BANDS_HZ[b], "dims": list(dims), "patches": N, "bins": T,
            "t_end_s": rs["t_end"], "memory_gb": need, "solver": "chunked (phase-05b2 D-T2)" if use_chunked else "lean",
            "e_target": e_target, "seconds_kernel": t_kernel, "seconds": time.time() - t0}


def done_units() -> set:
    if not OUT.exists():
        return set()
    rows = [json.loads(line) for line in OUT.read_text().splitlines() if line.strip()]
    return {(r["room"], r["rung"], r["band"]) for r in rows}


def l_ref_table(rows: list) -> dict:
    """max over a room's pairs of |E(1.25 m) / E(2.5 m) - 1| per band (AX36's rung rule; D-H2 (a) certifies < 1 %)."""
    by = {(r["room"], float(r["rung"]), int(r["band"])): r["e_target"] for r in rows}
    out = {}
    for (room, rung, b), fine in sorted(by.items()):
        coarse = by.get((room, RUNGS[0], b))
        if rung == RUNGS[1] and coarse is not None:
            out[f"{room}/{BANDS_HZ[b]}"] = max(abs(fine[n] / coarse[n] - 1) for n in fine)
    return out


def write_provenance(keep_commit: bool = False):
    """Writes the provenance file; keys this function does not own (e.g. recipe_check) are kept."""
    import numba
    import scipy
    git = lambda *a: subprocess.run(["git", "-C", str(REPO), *a], capture_output=True, text=True).stdout.strip()  # noqa: E731
    old = json.loads(PROVENANCE.read_text()) if PROVENANCE.exists() else {}
    commit = git("rev-parse", old["tool_commit"]) if keep_commit and old.get("tool_commit") else git("rev-parse", "HEAD")
    tools = [pathlib.Path(__file__), HERE / "hybrid_fast.py", HERE / "phase05b.py", REPO / "tools" / "acoustics" / "ref_hybrid.py"]
    dirty = bool(git("status", "--porcelain", "--", *(str(t.relative_to(REPO)) for t in tools)))
    rows = [json.loads(line) for line in OUT.read_text().splitlines() if line.strip()] if OUT.exists() else []
    PROVENANCE.write_text(json.dumps({**old,
        "file": OUT.name,
        "produced_by": "tools/validation/compute_phase05i_bras_references.py (phase05b.step_r1's recipe per band column; "
                       "see its docstring)",
        "tool_commit": commit,
        "tool_files_dirty_at_write": dirty,
        "tool_files_dirty_note": "the generator, hybrid_fast.py, phase05b.py and ref_hybrid.py, as the tree stood when this file was "
                                 "written (with --provenance: at the rewrite, not at the run; the run's state is in orchestrator_notes)",
        "python": platform.python_version(), "numba": numba.__version__, "numpy": np.__version__, "scipy": scipy.__version__,
        "requirements": "tools/acoustics/requirements.txt and tools/validation/requirements-offline.txt (hash-pinned)",
        "rungs_m": list(RUNGS), "order_hz": [BANDS_HZ[b] for b in ORDER],
        "rows": len(rows),
        "units": sorted(f"{r['room']}/{r['rung']}/{r['band_hz']}" for r in rows),
        "l_ref_max_by_room_band": l_ref_table(rows),
    }, indent=1) + "\n")


def check(chunked: bool = False) -> int:
    """The recipe reproduces the committed R1 references (phase05b.json r1, 500 Hz): CR2 and CR3 at both rungs (the
    lean solver), or with ``chunked`` CR4 at 1.25 m (the chunked solver, which produced CR4's 1.25 m units)."""
    d = json.loads((HERE / "data" / "phase05b.json").read_text())["r1"]["rooms"]
    worst = 0.0
    for room, sizes in ((("CR4", (RUNGS[1],)),) if chunked else (("CR2", RUNGS), ("CR3", RUNGS))):
        rs = room_setup(room)
        for size in sizes:
            u = compute_unit(room, size, 3, rs)
            for n, v in u["e_target"].items():
                ref = d[room]["rungs"][str(size)]["e_target"][n][0]
                worst = max(worst, abs(v / ref - 1))
            log(f"check {room} {size} m 500 Hz: worst relative difference so far {worst:.3e} ({u['seconds']:.0f} s)")
    what = "CR4 1.25 m (chunked)" if chunked else "CR2 and CR3, 2.5 and 1.25 m (lean)"
    print(json.dumps({"check": f"500 Hz, {what}, against phase05b.json r1", "worst_rel_diff": worst}))
    if PROVENANCE.exists():  # recorded by the run itself, beside the references it vouches for
        prov = json.loads(PROVENANCE.read_text())
        prov.pop("recipe_check", None)
        prov.setdefault("recipe_checks", {})[f"500 Hz, {what}, against phase05b.json r1"] = {
            "worst_rel_diff": worst, "script_commit": subprocess.run(
                ["git", "-C", str(REPO), "rev-parse", "HEAD"], capture_output=True, text=True).stdout.strip(),
            "date": time.strftime("%Y-%m-%d")}
        PROVENANCE.write_text(json.dumps(prov, indent=1) + "\n")
    return 0 if worst < 1e-9 else 1


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--check", action="store_true", help="recompute CR2/CR3 at 500 Hz against the committed r1 values")
    ap.add_argument("--check-chunked", action="store_true", help="recompute CR4 1.25 m at 500 Hz (chunked solver)")
    ap.add_argument("--provenance", action="store_true", help="rewrite the provenance file only (tool commit kept)")
    ap.add_argument("--bands", nargs="*", type=int, default=list(ORDER), help="band indices, in this order")
    ap.add_argument("--rooms", nargs="*", default=list(ROOMS))
    a = ap.parse_args(argv)
    if a.check or a.check_chunked:
        rc = check(chunked=False) if a.check else 0
        return rc or (check(chunked=True) if a.check_chunked else 0)
    if a.provenance:
        write_provenance(keep_commit=True)
        return 0
    have = done_units()
    setups = {}
    for b in a.bands:
        for room in a.rooms:
            for size in RUNGS:
                if (room, size, b) in have:
                    continue
                rs = setups.setdefault(room, room_setup(room))
                log(f"start {room} {size} m {BANDS_HZ[b]} Hz")
                u = compute_unit(room, size, b, rs)
                with OUT.open("a") as f:
                    f.write(json.dumps(u) + "\n")
                write_provenance()
                log(f"done {room} {size} m {BANDS_HZ[b]} Hz: {u['patches']} patches, {u['solver']}, "
                    f"kernel {u['seconds_kernel']:.0f} s, total {u['seconds']:.0f} s")
    return 0


if __name__ == "__main__":
    sys.exit(main())
