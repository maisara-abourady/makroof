"""Phase-07c-1 condition 11 (A11): the SPATIAL_HOST_TRACE diagnostic build is OFF by default and never part of
a release artefact.

- the CMake option defaults to OFF;
- no configure preset turns it on;
- in the workflows, only the `host-trace` job of ci.yml turns it on, and that job uploads nothing;
- the plugin sources reach the trace only under `#if SPATIAL_HOST_TRACE` (so the default build has no hook
  and links no trace object).
"""

from __future__ import annotations

import json
import re
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parents[2]


def test_option_defaults_off() -> None:
    text = (ROOT / "CMakeLists.txt").read_text(encoding="utf-8")
    m = re.search(r'option\(\s*SPATIAL_HOST_TRACE\s+"[^"]*"\s+(\w+)\s*\)', text)
    assert m, "option(SPATIAL_HOST_TRACE ...) missing from CMakeLists.txt"
    assert m.group(1) == "OFF"


def test_no_preset_turns_it_on() -> None:
    presets = json.loads((ROOT / "CMakePresets.json").read_text(encoding="utf-8"))
    for p in presets.get("configurePresets", []):
        value = str(p.get("cacheVariables", {}).get("SPATIAL_HOST_TRACE", "OFF")).upper()
        assert value in ("OFF", "0", "FALSE"), f"preset {p['name']} turns SPATIAL_HOST_TRACE on"


def test_only_the_host_trace_job_turns_it_on_and_it_uploads_nothing() -> None:
    for wf_path in sorted((ROOT / ".github" / "workflows").glob("*.yml")):
        wf = yaml.safe_load(wf_path.read_text(encoding="utf-8"))
        for name, job in wf.get("jobs", {}).items():
            text = yaml.safe_dump(job)
            uses_trace = "SPATIAL_HOST_TRACE=ON" in text
            if wf_path.name == "ci.yml" and name == "host-trace":
                assert uses_trace, "the host-trace job must build with SPATIAL_HOST_TRACE=ON"
                for step in job.get("steps", []):
                    assert "upload-artifact" not in str(step.get("uses", "")), "host-trace uploads nothing"
            else:
                assert not uses_trace, f"{wf_path.name}:{name} must not build with SPATIAL_HOST_TRACE=ON"


def test_plugin_sources_reach_the_trace_only_under_the_macro() -> None:
    for src in sorted((ROOT / "src" / "plugin").glob("*.*")):
        depth = 0
        guarded_depth = []
        for line in src.read_text(encoding="utf-8").splitlines():
            stripped = line.strip()
            if stripped.startswith("#if"):
                depth += 1
                if "SPATIAL_HOST_TRACE" in stripped:
                    guarded_depth.append(depth)
            elif stripped.startswith("#endif"):
                if guarded_depth and guarded_depth[-1] == depth:
                    guarded_depth.pop()
                depth -= 1
            elif stripped.startswith("#else") and guarded_depth and guarded_depth[-1] == depth:
                guarded_depth.pop()  # the #else branch is the non-trace build
                guarded_depth.append(-depth)  # mark: inside the else, not guarded
            if ("trace::" in line or "HostTrace.h" in line) and not stripped.startswith("//"):
                assert guarded_depth and guarded_depth[-1] > 0, f"{src.name}: trace used outside #if SPATIAL_HOST_TRACE: {line}"
