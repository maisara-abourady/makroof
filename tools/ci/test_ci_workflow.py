"""The skip gate in .github/workflows/ci.yml: structure, and the gate's own shell scripts run per scenario.

Structure: every job other than the gate (`changes`) and the summary (`ci-ok`) waits for the gate,
is skipped when it says so, and is listed in `ci-ok`'s needs, so a job added later (e.g. a
sanitizer) cannot run ungated or pass outside the marker rule. The marker is saved only by steps
that run after the result check succeeded.

Behaviour: the `Decide` and `Check job results` scripts are taken from the workflow file as they are
and run under bash with the inputs GitHub would give them.
"""

from __future__ import annotations

import json
import os
import shutil
import subprocess
import sys
from pathlib import Path

import pytest
import yaml

WORKFLOW = Path(__file__).resolve().parents[2] / ".github" / "workflows" / "ci.yml"
GATE, SUMMARY = "changes", "ci-ok"
RUN_IF = "needs.changes.outputs.run == 'true'"


@pytest.fixture(scope="module")
def wf() -> dict:
    return yaml.safe_load(WORKFLOW.read_text(encoding="utf-8"))


def _needs(job: dict) -> list[str]:
    n = job.get("needs", [])
    return [n] if isinstance(n, str) else list(n)


def _step(job: dict, name: str) -> dict:
    return next(s for s in job["steps"] if s.get("name") == name)


def _work_jobs(wf: dict) -> list[str]:
    return [k for k in wf["jobs"] if k not in (GATE, SUMMARY)]


def test_every_job_is_gated(wf: dict) -> None:
    for name in _work_jobs(wf):
        job = wf["jobs"][name]
        assert GATE in _needs(job), f"{name} must need {GATE}"
        assert job.get("if") == RUN_IF, f"{name} must have if: {RUN_IF}"


def test_summary_needs_every_job(wf: dict) -> None:
    summary = wf["jobs"][SUMMARY]
    assert set(_needs(summary)) == set(wf["jobs"]) - {SUMMARY}
    assert summary.get("if") == "always()"


def test_marker_saved_only_after_a_passing_check(wf: dict) -> None:
    steps = wf["jobs"][SUMMARY]["steps"]
    names = [s.get("name") for s in steps]
    check = names.index("Check job results")
    for s in steps:
        if "cache/save" in s.get("uses", "") or s.get("name") == "Write the pass marker":
            assert names.index(s["name"]) > check
            # A plain `if` keeps the implicit success(): the step is skipped when the check failed.
            # always(), failure() or cancelled() would bypass that.
            cond = s.get("if", "")
            assert cond == RUN_IF, s["name"]
    save = next(s for s in steps if "cache/save" in s.get("uses", ""))
    assert save["with"]["key"] == "ci-pass-${{ needs.changes.outputs.fingerprint }}"


def test_lookup_uses_the_same_key(wf: dict) -> None:
    lookup = _step(wf["jobs"][GATE], "Look up a pass marker")
    assert "cache/restore" in lookup["uses"]
    assert lookup["with"]["key"] == "ci-pass-${{ steps.fp.outputs.fingerprint }}"


# Maisara, 2026-11-08 (option 2): one automatic run per PR (opened / reopened / ready for review), never
# on a push to the PR, on main or on a schedule; anything else is started by hand.
ONCE_PER_PR = {"opened", "reopened", "ready_for_review"}


def _on(wf: dict) -> dict:
    return wf[True] if True in wf else wf["on"]  # PyYAML reads the key `on` as True


def test_triggers(wf: dict) -> None:
    on = _on(wf)
    assert set(on) == {"pull_request", "workflow_dispatch"}
    assert set(on["pull_request"]["types"]) == ONCE_PER_PR
    assert on["workflow_dispatch"]["inputs"]["force"]["type"] == "boolean"


def test_validation_triggers() -> None:
    nightly = yaml.safe_load((WORKFLOW.parent / "nightly.yml").read_text(encoding="utf-8"))
    on = _on(nightly)
    assert set(on) == {"pull_request", "workflow_dispatch"}  # no schedule
    assert set(on["pull_request"]["types"]) == ONCE_PER_PR
    assert "src/sim/**" in on["pull_request"]["paths"]


# ---- the scripts, run as written ----

needs_shell = pytest.mark.skipif(
    sys.platform == "win32" or not shutil.which("bash") or not shutil.which("jq"),
    reason="runs the workflow's bash/jq scripts; covered on the Linux and macOS jobs",
)


def _run(script: str, env: dict[str, str], tmp_path: Path) -> tuple[int, dict[str, str]]:
    out, summary = tmp_path / "out", tmp_path / "summary"
    out.write_text("")
    summary.write_text("")
    full = {**os.environ, **env, "GITHUB_OUTPUT": str(out), "GITHUB_STEP_SUMMARY": str(summary)}
    p = subprocess.run(["bash", "-e", "-c", script], env=full, cwd=tmp_path, capture_output=True, text=True)
    outputs = dict(line.split("=", 1) for line in out.read_text().splitlines() if "=" in line)
    return p.returncode, outputs


@needs_shell
@pytest.mark.parametrize(
    "hit,force,run",
    [("true", "false", "false"), ("true", "true", "true"), ("false", "false", "true"), ("", "false", "true"),
     ("false", "true", "true")],
)
def test_decide(wf: dict, tmp_path: Path, hit: str, force: str, run: str) -> None:
    script = _step(wf["jobs"][GATE], "Decide")["run"]
    if hit == "true":
        (tmp_path / ".ci-pass").mkdir()
        (tmp_path / ".ci-pass" / "passed").write_text("https://example/runs/1 (commit abc)\n")
    code, out = _run(script, {"FP": "f" * 64, "HIT": hit, "FORCE": force}, tmp_path)
    assert code == 0
    assert out["run"] == run
    if run == "false":
        assert out["reused"] == "https://example/runs/1 (commit abc)"


def _needs_json(run: str, results: dict[str, str]) -> str:
    d = {GATE: {"result": "success", "outputs": {"run": run}}}
    d.update({k: {"result": v, "outputs": {}} for k, v in results.items()})
    return json.dumps(d)


WORK = ["format", "contract-tools", "python", "tail-gates", "build", "asan"]


@needs_shell
@pytest.mark.parametrize(
    "run,results,ok",
    [
        ("true", dict.fromkeys(WORK, "success"), True),
        ("true", {**dict.fromkeys(WORK, "success"), "build": "failure"}, False),
        ("true", {**dict.fromkeys(WORK, "success"), "tail-gates": "cancelled"}, False),
        ("true", {**dict.fromkeys(WORK, "success"), "asan": "skipped"}, False),
        ("false", dict.fromkeys(WORK, "skipped"), True),
        ("false", {**dict.fromkeys(WORK, "skipped"), "python": "success"}, False),
    ],
)
def test_check_job_results(wf: dict, tmp_path: Path, run: str, results: dict[str, str], ok: bool) -> None:
    script = _step(wf["jobs"][SUMMARY], "Check job results")["run"]
    code, _ = _run(script, {"RUN": run, "REUSED": "x", "NEEDS": _needs_json(run, results)}, tmp_path)
    assert (code == 0) is ok


@needs_shell
@pytest.mark.parametrize("gate_result", ["failure", "cancelled"])
def test_check_fails_when_the_gate_failed(wf: dict, tmp_path: Path, gate_result: str) -> None:
    script = _step(wf["jobs"][SUMMARY], "Check job results")["run"]
    needs = json.loads(_needs_json("", dict.fromkeys(WORK, "skipped")))
    needs[GATE]["result"] = gate_result
    code, _ = _run(script, {"RUN": "", "REUSED": "", "NEEDS": json.dumps(needs)}, tmp_path)
    assert code != 0


# Phase-07c-1b D-B5 (vi) item 5 (AX38 4c (f)): the restore gate's fired warnings reach the job summary and the
# annotations; the step is run as written, on a benchmark log with GATE lines as the test prints them.
_GATE_LOG = (
    "05h-records GATE os=macOS scene=cube100_flutter_fallback x14worst=7.10 median=480 fullRebuildMedian=1 "
    "solveMedianMs=99.0 solveWarnAt=123.2 solveBasis=PROVISIONAL(n=1) nsPerEval=1.00 status=asserted(30s) "
    "flutterRef=484 flutterDev=-0.8% warnings=\r\n"
    "05h-records GATE os=macOS scene=cube100_lowalpha0.05_s0.3 ratio=4.700 ratioWarnAt=4.500 "
    "solveMedianMs=90.0 solveWarnAt=100.4 solveBasis=PROVISIONAL(n=1) nsPerEval=1.00 x14worst=33.20 "
    "median=2300 growthBound=1999 fullRebuildMedian=1 status=reported-only trigger=2172 "
    "warnings=RATIO GROWTH OVER30S MACTRIGGER \r\n"
    "05h-records restore gate cube100_lowalpha0.05_s0.3 macOS: LISTED defect; WARNING OVER30S\n"
    "07c1b-records stage split os=macOS scene=cube100_lowalpha0.05_s0.3 96 kHz keyless restore\n"
)
_QUIET_LOG = (
    "05h-records GATE os=Linux scene=cube100_lowalpha0.05_s0.3 ratio=2.900 status=asserted trigger=0 "
    "warnings=PASSES30S \n"
)


def _run_records_step(wf: dict, tmp_path: Path, log: str) -> tuple[int, str, str]:
    script = _step(wf["jobs"]["build"], "Records to the job summary")["run"].replace("${{ matrix.name }}", "macos")
    (tmp_path / "build").mkdir()
    (tmp_path / "build" / "benchmark.log").write_bytes(log.encode())
    summary = tmp_path / "summary"
    summary.write_text("")
    env = {**os.environ, "GITHUB_STEP_SUMMARY": str(summary)}
    p = subprocess.run(["bash", "-eo", "pipefail", "-c", script], env=env, cwd=tmp_path, capture_output=True,
                       text=True)
    return p.returncode, p.stdout, summary.read_text()


@needs_shell
def test_gate_warnings_surface(wf: dict, tmp_path: Path) -> None:
    code, stdout, summary = _run_records_step(wf, tmp_path, _GATE_LOG)
    assert code == 0
    section = summary.split("### GATE warnings, macos")[1]
    assert "scene=cube100_lowalpha0.05_s0.3" in section and "MACTRIGGER" in section
    assert "scene=cube100_flutter_fallback" not in section  # empty warnings=
    assert "07c1b-records stage split" in summary  # the phase-07c-1b record lines reach the summary
    notes = [line for line in stdout.splitlines() if line.startswith("::warning ")]
    assert len(notes) == 1
    assert "title=GATE macos cube100_lowalpha0.05_s0.3::RATIO GROWTH OVER30S MACTRIGGER " in notes[0]


@needs_shell
def test_gate_warnings_none(wf: dict, tmp_path: Path) -> None:
    code, stdout, summary = _run_records_step(wf, tmp_path, _QUIET_LOG)
    assert code == 0
    assert "(none)" in summary.split("### GATE warnings, macos")[1]
    assert "::warning" not in stdout  # PASSES30S is not OVER30S
