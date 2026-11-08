"""The skip gate in .github/workflows/nightly.yml (same rules as ci.yml's, see test_ci_workflow.py).

Structure: the validation job waits for the gate and is skipped when it says so; the marker is
written and saved only after every validation step succeeded (plain `if`, implicit success()), with
the key the gate looks up. Behaviour: the gate's `Decide` script, run as written per scenario.
"""

from __future__ import annotations

import os
import shutil
import subprocess
import sys
from pathlib import Path

import pytest
import yaml

WORKFLOW = Path(__file__).resolve().parents[2] / ".github" / "workflows" / "nightly.yml"
RUN_IF = "needs.changes.outputs.run == 'true'"


@pytest.fixture(scope="module")
def wf() -> dict:
    return yaml.safe_load(WORKFLOW.read_text(encoding="utf-8"))


def _step(job: dict, name: str) -> dict:
    return next(s for s in job["steps"] if s.get("name") == name)


def test_every_job_is_gated(wf: dict) -> None:
    for name, job in wf["jobs"].items():
        if name == "changes":
            continue
        needs = job.get("needs", [])
        assert "changes" in ([needs] if isinstance(needs, str) else needs), name
        assert job.get("if") == RUN_IF, name


def test_marker_saved_last_and_only_on_success(wf: dict) -> None:
    steps = wf["jobs"]["validation"]["steps"]
    names = [s.get("name") for s in steps]
    write, save = names.index("Write the pass marker"), names.index("Save the pass marker")
    assert save == len(steps) - 1 and write == save - 1
    for i in (write, save):
        assert steps[i].get("if") == RUN_IF
    for s in steps[:write]:  # nothing before the marker may be skipped silently on failure
        assert "continue-on-error" not in s
    assert steps[save]["with"]["key"] == "nightly-pass-${{ needs.changes.outputs.fingerprint }}"


def test_lookup_uses_the_same_key(wf: dict) -> None:
    lookup = _step(wf["jobs"]["changes"], "Look up a pass marker")
    assert "cache/restore" in lookup["uses"]
    assert lookup["with"]["key"] == "nightly-pass-${{ steps.fp.outputs.fingerprint }}"


def test_triggers(wf: dict) -> None:
    on = wf[True] if True in wf else wf["on"]
    assert set(on) >= {"schedule", "workflow_dispatch", "pull_request"}
    assert on["workflow_dispatch"]["inputs"]["force"]["type"] == "boolean"


@pytest.mark.skipif(sys.platform == "win32" or not shutil.which("bash"), reason="runs the gate's bash script")
@pytest.mark.parametrize("hit,force,run", [("true", "false", "false"), ("true", "true", "true"),
                                           ("false", "false", "true"), ("", "false", "true")])
def test_decide(wf: dict, tmp_path: Path, hit: str, force: str, run: str) -> None:
    script = _step(wf["jobs"]["changes"], "Decide")["run"]
    if hit == "true":
        (tmp_path / ".nightly-pass").mkdir()
        (tmp_path / ".nightly-pass" / "passed").write_text("https://example/runs/1 (commit abc)\n")
    out, summary = tmp_path / "out", tmp_path / "summary"
    out.write_text("")
    summary.write_text("")
    env = {**os.environ, "FP": "f" * 64, "HIT": hit, "FORCE": force, "GITHUB_OUTPUT": str(out),
           "GITHUB_STEP_SUMMARY": str(summary)}
    p = subprocess.run(["bash", "-e", "-c", script], env=env, cwd=tmp_path, capture_output=True, text=True)
    assert p.returncode == 0, p.stderr
    outputs = dict(line.split("=", 1) for line in out.read_text().splitlines() if "=" in line)
    assert outputs["run"] == run
