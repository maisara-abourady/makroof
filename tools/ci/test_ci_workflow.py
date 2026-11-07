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


def test_triggers(wf: dict) -> None:
    on = wf[True] if True in wf else wf["on"]  # PyYAML reads the key `on` as True
    assert set(on) >= {"push", "pull_request", "workflow_dispatch"}
    assert on["workflow_dispatch"]["inputs"]["force"]["type"] == "boolean"


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
