#!/usr/bin/env python3
"""Propose the AX38 4c restore-gate S2 pin from CI benchmark logs (phase-07c-1b, FM-GROWTH and FM-TRIG).

The decided form (docs/review/phase-07c-1b/11-decider-decision-r3.md, plan item 9, G1-G14 and the macOS trigger,
as corrected by 12-interrogator-on-file11.md rows 09-15) pins, per OS and scene, from >= 3 green S2 runs:

* r-bar, the mean same-run low-alpha / flutter restore-median ratio, and the ratios' max / min (an OS above 1.10
  is print-only, as macOS always is) (G5);
* F-bar, the mean flutter restore median, and the baseline median of each scene (G10-G12);
* solveRefMs, the mean solve median per scene, and k per OS, the largest max / mean of those medians (G7);
* solveExitMet per OS, the G9 exit (the same-run ns-per-eval ratio within 1.05 of its mean on >= 3 runs): the
  solve basis prints S2-PINNED where met, S2-PROVISIONAL where not (docs/review/phase-07c-1b/25 Q3);
* kMacGrowthTriggerMs = floor(1.15 x the mean of the green macOS low-alpha medians) (4c (c), M-a);

and reads, for the PR: the uniform-slowdown factor f = [1.10(1 - s_F) - (1 - s_L)] / (s_L - 1.10 s_F) from the
stage-split synthesis shares (G5), the 14 x worst of every run and whether each low-alpha entry passes 30 s on every
run (E1), the G9 exit condition on the ns-per-eval ratio, and any run above the trigger it helped set (Seat 7).

Input: one log per run and OS-job, or one log holding several OS-jobs of the same run (the job logs or the records
section of the job summary), each given as ``green=PATH`` or ``red=PATH``. Red runs are refused (G12: never a red
run); a log marked green that holds a Catch2 failure is an error. The output is the constants to paste into
tests/unit/test_diffuse_records.cpp (a constants-only change) and a report; ``--json`` also writes them as JSON.

    python tools/ci/repin_gate.py green=run1-linux.log green=run1-macos.log ... [--json out.json]
"""

from __future__ import annotations

import argparse
import json
import math
import re
import statistics
import sys
from dataclasses import dataclass, field
from pathlib import Path

FLUTTER = "cube100_flutter_fallback"
LOWALPHA = "cube100_lowalpha0.05_s0.3"
SCENES = (FLUTTER, LOWALPHA)
OS_ORDER = ("Linux", "macOS", "Windows")

PIN_RUNS = 3  # G5 / G12: >= 3 green S2 runs
RATIO_BOUND = 1.10  # G5 (and G6, G10)
TRIGGER_FACTOR = 1.15  # 4c (c): her factor, M-a
TRIGGER_IN_FORCE_MS = 2172.0  # kMacGrowthTriggerMs before the pin (RG-1)
F_BRANCH_A = 1.4  # pre-registered branch A: f <= x1.4 (file 11)
NS_EXIT = 1.05  # G9: ns-per-eval ratio within 1.05 of its mean
LIMIT_30S = 30.0

# A log line may carry a GitHub Actions timestamp prefix; an annotation (::warning ...) repeating a GATE line
# must not count, so the record has to start the line (after the optional timestamp).
_PREFIX = r"^(?:﻿)?(?:\d{4}-\d\d-\d\dT[\d:.]+Z\s+)?"
_GATE = re.compile(_PREFIX + r"05h-records GATE (.*)$")
_SPLIT = re.compile(_PREFIX + r"07c1b-records stage split os=(\S+) scene=(\S+) (.*)$")
_KV = re.compile(r"(\w+)=(\S*)")
_ASM = re.compile(r"Assemble->Commit \([^)]*\) (-?[\d.]+)")
_RESTORE = re.compile(r"restore median (-?[\d.]+)")
_FAILED = re.compile(_PREFIX + r".*(?:\bFAILED:|test cases?:.*\d+ failed)")


class InputError(Exception):
    pass


@dataclass
class SceneRun:
    median: float
    solve: float
    ns_per_eval: float
    x14worst: float
    ratio: float | None = None  # low-alpha only
    synth_share: float | None = None  # Assemble->Commit / restore median (stage split)


@dataclass
class Run:
    label: str
    os: str
    scenes: dict[str, SceneRun] = field(default_factory=dict)


def _num(fields: dict[str, str], key: str, where: str) -> float:
    if key not in fields:
        raise InputError(f"{where}: GATE line has no {key}=")
    try:
        return float(fields[key].rstrip("%"))
    except ValueError as e:
        raise InputError(f"{where}: {key}={fields[key]!r} is not a number") from e


def parse_log(text: str, label: str) -> list[Run]:
    """The runs (one per OS) of one log: GATE lines for both scenes, and the stage-split shares when present."""
    runs: dict[str, Run] = {}
    shares: dict[tuple[str, str], float] = {}
    for n, raw in enumerate(text.splitlines(), 1):
        line = raw.rstrip("\r")
        where = f"{label}:{n}"
        if m := _GATE.match(line):
            body = m.group(1)
            head, _, _warnings = body.partition(" warnings=")
            fields = dict(_KV.findall(head))
            os_name, scene = fields.get("os"), fields.get("scene")
            if os_name is None or scene not in SCENES:
                raise InputError(f"{where}: GATE line without a known os= / scene=")
            run = runs.setdefault(os_name, Run(label=f"{label} [{os_name}]", os=os_name))
            if scene in run.scenes:
                raise InputError(f"{where}: a second GATE line for {os_name} {scene}; give each run its own log")
            run.scenes[scene] = SceneRun(
                median=_num(fields, "median", where),
                solve=_num(fields, "solveMedianMs", where),
                ns_per_eval=_num(fields, "nsPerEval", where),
                x14worst=_num(fields, "x14worst", where),
                ratio=_num(fields, "ratio", where) if scene == LOWALPHA else None,
            )
        elif (m := _SPLIT.match(line)) and not line[m.start(3) :].startswith("replay"):
            os_name, scene, rest = m.groups()
            if os_name == "replay" or scene not in SCENES:
                continue
            asm, restore = _ASM.search(rest), _RESTORE.search(rest)
            if asm and restore and float(asm.group(1)) >= 0.0 and float(restore.group(1)) > 0.0:
                if (os_name, scene) in shares:
                    raise InputError(f"{where}: a second stage-split line for {os_name} {scene}")
                shares[(os_name, scene)] = float(asm.group(1)) / float(restore.group(1))
    for (os_name, scene), s in shares.items():
        if os_name in runs and scene in runs[os_name].scenes:
            runs[os_name].scenes[scene].synth_share = s
    for run in runs.values():
        missing = [s for s in SCENES if s not in run.scenes]
        if missing:
            raise InputError(f"{run.label}: no GATE line for {', '.join(missing)}")
    return list(runs.values())


def load_runs(specs: list[str]) -> tuple[list[Run], list[str]]:
    """Parse ``green=PATH`` / ``red=PATH``; return the green runs and the refused (red) labels."""
    green: list[Run] = []
    refused: list[str] = []
    for spec in specs:
        status, sep, path = spec.partition("=")
        if not sep or status not in ("green", "red") or not path:
            raise InputError(f"{spec!r}: give each run as green=PATH or red=PATH")
        text = Path(path).read_text(encoding="utf-8", errors="replace")
        if status == "red":
            refused.append(path)
            continue
        if any(_FAILED.match(line.rstrip("\r")) for line in text.splitlines()):
            raise InputError(f"{path}: marked green but holds a Catch2 failure; mark it red=")
        runs = parse_log(text, path)
        if not runs:
            raise InputError(f"{path}: no 05h-records GATE lines")
        green.extend(runs)
    return green, refused


def _mean(xs: list[float]) -> float:
    return statistics.fmean(xs)


def uniform_slowdown_factor(s_l: float, s_f: float) -> float | None:
    """f = [1.10(1 - s_F) - (1 - s_L)] / (s_L - 1.10 s_F); None outside the domain s_L > 1.10 s_F (G5)."""
    den = s_l - RATIO_BOUND * s_f
    if den <= 0.0:
        return None
    return (RATIO_BOUND * (1.0 - s_f) - (1.0 - s_l)) / den


def propose(runs: list[Run]) -> dict:
    """The proposed constants and the read-outs, per OS (only the OSes the runs cover)."""
    by_os: dict[str, list[Run]] = {}
    for r in runs:
        by_os.setdefault(r.os, []).append(r)
    out: dict = {"os": {}, "macTrigger": None}
    for os_name in sorted(by_os, key=lambda o: (OS_ORDER.index(o) if o in OS_ORDER else 99, o)):
        rs = by_os[os_name]
        n = len(rs)
        ratios = [r.scenes[LOWALPHA].ratio for r in rs]
        r_bar = _mean(ratios)
        max_min = max(ratios) / min(ratios)
        fl_medians = [r.scenes[FLUTTER].median for r in rs]
        f_bar = _mean(fl_medians)
        scenes: dict = {}
        k = 0.0
        for scene in SCENES:
            solves = [r.scenes[scene].solve for r in rs]
            solve_ref = _mean(solves)
            k = max(k, max(solves) / solve_ref)
            x14 = [r.scenes[scene].x14worst for r in rs]
            scenes[scene] = {
                "baselineMedianMs": _mean([r.scenes[scene].median for r in rs]),
                "solveRefMs": solve_ref,
                "x14worstPerRun": x14,
                "passes30sEveryRun": all(x <= LIMIT_30S for x in x14),
            }
        ns_ratios = [
            r.scenes[LOWALPHA].ns_per_eval / r.scenes[FLUTTER].ns_per_eval
            for r in rs
            if r.scenes[FLUTTER].ns_per_eval > 0.0
        ]
        ns_mean = _mean(ns_ratios) if ns_ratios else None
        ns_exit = (
            bool(ns_ratios)
            and n >= PIN_RUNS
            and max(ns_ratios) / ns_mean <= NS_EXIT
            and ns_mean / min(ns_ratios) <= NS_EXIT
        )
        s_l_runs = [r.scenes[LOWALPHA].synth_share for r in rs if r.scenes[LOWALPHA].synth_share is not None]
        s_f_runs = [r.scenes[FLUTTER].synth_share for r in rs if r.scenes[FLUTTER].synth_share is not None]
        split: dict = {"runsWithSplit": min(len(s_l_runs), len(s_f_runs))}
        if s_l_runs and s_f_runs:
            s_l, s_f = _mean(s_l_runs), _mean(s_f_runs)
            f = uniform_slowdown_factor(s_l, s_f)
            split.update(
                {
                    "sL": s_l,
                    "sF": s_f,
                    "domainSharesOk": s_l > RATIO_BOUND * s_f,
                    "domainMaxMinOk": max_min <= RATIO_BOUND,
                    "f": f,
                    "seat3Later2": f is None or f > F_BRANCH_A,
                    "macDetectionFactor": 1.0 + (TRIGGER_FACTOR - 1.0) / s_l if os_name == "macOS" else None,
                }
            )
        print_only = os_name == "macOS" or max_min > RATIO_BOUND
        out["os"][os_name] = {
            "runs": n,
            "pinnable": n >= PIN_RUNS,
            "runLabels": [r.label for r in rs],
            "ratioRef": r_bar,
            "ratioMaxOverMin": max_min,
            "ratioPrintOnly": print_only,
            "ratioPerRun": ratios,
            "ratioOverRefPerRun": [x / r_bar for x in ratios],
            "flutterRefMs": f_bar,
            "solveK": k,
            "nsPerEvalRatioPerRun": ns_ratios,
            "g9ExitMet": ns_exit,
            "scenes": scenes,
            "split": split,
        }
    if "macOS" in by_os:
        medians = [r.scenes[LOWALPHA].median for r in by_os["macOS"]]
        trig = math.floor(TRIGGER_FACTOR * _mean(medians))
        out["macTrigger"] = {
            "kMacGrowthTriggerMs": float(trig),
            "runs": len(medians),
            "pinnable": len(medians) >= PIN_RUNS,
            "lowAlphaMediansMs": medians,
            "runsAboveComputed": [r.label for r in by_os["macOS"] if r.scenes[LOWALPHA].median > trig],
            "runsAboveInForce": [
                r.label for r in by_os["macOS"] if r.scenes[LOWALPHA].median > TRIGGER_IN_FORCE_MS
            ],
        }
    return out


def _s2_init(os_d: dict, scene: str) -> str:
    sc = os_d["scenes"][scene]
    low = scene == LOWALPHA
    return (
        f"{{{os_d['ratioRef'] if low else 0.0:.4f}, {os_d['ratioMaxOverMin'] if low else 0.0:.4f}, "
        f"{os_d['flutterRefMs']:.1f}, {sc['baselineMedianMs']:.1f}, {sc['solveRefMs']:.1f}, "
        f"{os_d['solveK']:.4f}, {os_d['runs']}, {'true' if os_d['g9ExitMet'] else 'false'}}}"
    )


def report(p: dict, refused: list[str]) -> str:
    lines: list[str] = ["# AX38 4c restore gate: proposed S2 pin (tools/ci/repin_gate.py)", ""]
    for path in refused:
        lines.append(f"REFUSED (red run, G12: never a red run): {path}")
    if refused:
        lines.append("")
    for os_name, d in p["os"].items():
        lines.append(f"## {os_name}: {d['runs']} green run(s)" + ("" if d["pinnable"] else " -- NOT PINNABLE (n < 3)"))
        lines.append(f"  runs: {'; '.join(d['runLabels'])}")
        lines.append(
            f"  r-bar {d['ratioRef']:.4f}; ratios {', '.join(f'{x:.3f}' for x in d['ratioPerRun'])}; "
            f"max/min {d['ratioMaxOverMin']:.4f}; r/r-bar {', '.join(f'{x:.4f}' for x in d['ratioOverRefPerRun'])}"
        )
        why = "macOS, until Phase 13" if os_name == "macOS" else f"max/min > {RATIO_BOUND:.2f}"
        lines.append(
            "  ratio check: " + (f"PRINT-ONLY ({why})" if d["ratioPrintOnly"] else f"ASSERTED (r <= {RATIO_BOUND:.2f} x r-bar)")
        )
        lines.append(f"  F-bar (flutter reference) {d['flutterRefMs']:.1f} ms; k {d['solveK']:.4f}")
        for scene in SCENES:
            sc = d["scenes"][scene]
            x14 = ", ".join(f"{x:.2f}" for x in sc["x14worstPerRun"])
            lines.append(
                f"  {scene}: baseline median {sc['baselineMedianMs']:.1f} ms; solveRefMs {sc['solveRefMs']:.1f}; "
                f"14 x worst per run [{x14}] s; <= 30 s on every run: {'yes' if sc['passes30sEveryRun'] else 'NO'}"
            )
        lowe = d["scenes"][LOWALPHA]
        if os_name in ("macOS", "Windows"):
            lines.append(
                f"  E1 ({LOWALPHA} {os_name} register entry): "
                + (
                    "closes under 4c (c) (14 x worst <= 30 s on every S2 run)"
                    if lowe["passes30sEveryRun"]
                    else "stays listed, closes at phase-07d (scope 1)"
                )
            )
        ns = ", ".join(f"{x:.4f}" for x in d["nsPerEvalRatioPerRun"])
        lines.append(
            f"  ns-per-eval ratio (low-alpha / flutter) per run [{ns}]; G9 exit (>= 3 runs within 1.05 of the mean): "
            + ("met" if d["g9ExitMet"] else "not met")
        )
        sp = d["split"]
        if "sL" in sp:
            f = sp["f"]
            lines.append(
                f"  stage split ({sp['runsWithSplit']} run(s)): s_L {sp['sL']:.4f}, s_F {sp['sF']:.4f}; "
                f"s_L > 1.10 s_F: {'yes' if sp['domainSharesOk'] else 'NO'}; max/min <= 1.10: "
                f"{'yes' if sp['domainMaxMinOk'] else 'NO'}; f = " + ("undefined (s_L <= 1.10 s_F)" if f is None else f"x{f:.3f}")
            )
            if sp["seat3Later2"]:
                lines.append("  f > x1.4 or s_L <= 1.10 s_F: the 07c-1b PR states Seat 3's later 2 until the 07d re-pin")
            if sp["macDetectionFactor"] is not None:
                lines.append(f"  macOS trigger detects x{sp['macDetectionFactor']:.3f} (1 + 0.15 / s_L)")
        else:
            lines.append("  stage split: no 07c1b-records stage split lines for both scenes; f not computed")
        lines.append("")
    mt = p["macTrigger"]
    if mt is not None:
        lines.append(
            f"## macOS trigger: kMacGrowthTriggerMs = floor(1.15 x mean of {mt['runs']} macOS low-alpha medians) "
            f"= {mt['kMacGrowthTriggerMs']:.0f} ms" + ("" if mt["pinnable"] else " -- NOT PINNABLE (n < 3)")
        )
        if mt["runsAboveComputed"]:
            lines.append(
                "  Seat 7: an S2 run exceeds the trigger it helped set ("
                + "; ".join(mt["runsAboveComputed"])
                + '). 4c and the PR say: "the board kept her factor 1.15, which detects ~x1.16, over a clean '
                'calibration (k ~ 1.23) that detects only ~x1.25".'
            )
        else:
            lines.append("  no S2 run exceeds the computed trigger")
        above = "; ".join(mt["runsAboveInForce"]) or "none"
        lines.append(f"  runs above the trigger in force ({TRIGGER_IN_FORCE_MS:.0f} ms): {above}")
        lines.append("")
    lines.append("## Constants for tests/unit/test_diffuse_records.cpp (the S2Pin of each kGateRegister entry)")
    lines.append(
        "  // {ratioRef, ratioMaxOverMin, flutterRefMs, baselineMedianMs, solveRefMs, solveK, runs, solveExitMet}"
    )
    lines.append("  // solveExitMet: the OS's G9 exit (true: solve basis S2-PINNED; false: S2-PROVISIONAL)")
    for os_name, d in p["os"].items():
        for scene in SCENES:
            lines.append(f"  {scene:<26} {os_name:<8} {_s2_init(d, scene)}")
    if mt is not None:
        lines.append(f"  constexpr double kMacGrowthTriggerMs = {mt['kMacGrowthTriggerMs']:.1f};")
        lines.append(f"  constexpr int kMacGrowthTriggerS2Runs = {mt['runs']};")
    return "\n".join(lines) + "\n"


def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("runs", nargs="+", metavar="STATUS=PATH", help="green=PATH or red=PATH, one per run log")
    ap.add_argument("--json", type=Path, help="also write the proposal as JSON here")
    args = ap.parse_args(argv)
    try:
        green, refused = load_runs(args.runs)
    except (InputError, OSError) as e:
        print(f"repin_gate: {e}", file=sys.stderr)
        return 2
    if not green:
        print("repin_gate: no green run to pin from", file=sys.stderr)
        return 2
    p = propose(green)
    p["refused"] = refused
    sys.stdout.write(report(p, refused))
    if args.json:
        args.json.write_text(json.dumps(p, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
