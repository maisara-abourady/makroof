"""Golden-file comparison with per-metric tolerances.

A golden file ``tests/golden/<name>.json`` stores expected metrics *and* how far a result may drift:

    {
      "name": "medium_room_omni",
      "description": "Phase 04: hybrid IR of tests/scenes/valid/medium_room.json, omni, 48 kHz",
      "tolerances": {
        "default": {"abs": 0.0, "rel": 0.02},
        "T30":     {"rel": 0.05},
        "C80":     {"abs": 0.5},
        "bands.63.T30": {"rel": 0.10}
      },
      "metrics": {"bands": {"500": {"T30": 1.23, "C80": 1.9}}, "broadband": {"T30": 1.2}}
    }

Every numeric leaf of ``metrics`` is checked; a value passes when
|actual - expected| <= abs + rel * |expected|. The tolerance for a leaf is looked up by its full
dotted path ("bands.63.T30"), then by its leaf name ("T30"), then "default" (which itself defaults
to exact equality). An abs/rel missing from the matched entry is 0. Expected ``null`` requires
actual ``null``; strings and booleans must be equal. Keys in the actual metrics that the golden
doesn't list are ignored (goldens pin what matters, not everything).

Goldens are **never** rewritten by a test run. The only way to update them is
``tools/ci/update_goldens.py --reason "<why>" <pytest args>``, which reruns the given tests in
update mode (environment variables below) and appends the reason to ``tests/golden/CHANGELOG.md``
(CLAUDE.md "Tests and golden files"). Update mode is refused when the ``CI`` environment variable
is set.
"""

from __future__ import annotations

import json
import math
import os
import pathlib
from dataclasses import dataclass, field

REPO = pathlib.Path(__file__).resolve().parents[2]
DEFAULT_GOLDEN_DIR = REPO / "tests" / "golden"

# Set by tools/ci/update_goldens.py only.
ENV_UPDATE_REASON = "SPATIAL_GOLDEN_UPDATE_REASON"
ENV_UPDATE_LOG = "SPATIAL_GOLDEN_UPDATE_LOG"
# Overrides the golden directory (used by the update script's own tests).
ENV_GOLDEN_DIR = "SPATIAL_GOLDEN_DIR"


def golden_dir() -> pathlib.Path:
    return pathlib.Path(os.environ.get(ENV_GOLDEN_DIR, DEFAULT_GOLDEN_DIR))


def golden_path(name: str) -> pathlib.Path:
    if not name or "/" in name or "\\" in name or name.startswith("."):
        raise ValueError(f"invalid golden name {name!r}")
    return golden_dir() / f"{name}.json"


@dataclass
class Mismatch:
    path: str
    expected: object
    actual: object
    allowed: float | None
    reason: str

    def __str__(self) -> str:
        if self.allowed is None:
            return f"{self.path}: {self.reason} (expected {self.expected!r}, got {self.actual!r})"
        return f"{self.path}: expected {self.expected!r} ± {self.allowed:.6g}, got {self.actual!r} ({self.reason})"


@dataclass
class GoldenReport:
    name: str
    checked: int = 0
    mismatches: list[Mismatch] = field(default_factory=list)

    @property
    def ok(self) -> bool:
        return not self.mismatches

    def __str__(self) -> str:
        head = f"golden '{self.name}': {self.checked} values checked, {len(self.mismatches)} out of tolerance"
        return "\n  ".join([head, *map(str, self.mismatches)])


def _tolerance(tolerances: dict, path: str) -> tuple[float, float]:
    leaf = path.rsplit(".", 1)[-1]
    entry = tolerances.get(path) or tolerances.get(leaf) or tolerances.get("default") or {}
    return float(entry.get("abs", 0.0)), float(entry.get("rel", 0.0))


def _walk(expected, actual, path: str, tolerances: dict, report: GoldenReport) -> None:
    if isinstance(expected, dict):
        if not isinstance(actual, dict):
            report.mismatches.append(Mismatch(path, "{...}", actual, None, "expected an object"))
            return
        for key, value in expected.items():
            sub = f"{path}.{key}" if path else str(key)
            if key not in actual:
                report.mismatches.append(Mismatch(sub, value, None, None, "missing in the actual metrics"))
                continue
            _walk(value, actual[key], sub, tolerances, report)
        return
    if isinstance(expected, list):
        if not isinstance(actual, list) or len(actual) != len(expected):
            report.mismatches.append(Mismatch(path, expected, actual, None, "list length or type differs"))
            return
        for i, (e, a) in enumerate(zip(expected, actual)):
            _walk(e, a, f"{path}[{i}]", tolerances, report)
        return

    report.checked += 1
    if expected is None or isinstance(expected, (bool, str)) or isinstance(actual, bool):
        if expected != actual:
            report.mismatches.append(Mismatch(path, expected, actual, None, "values differ"))
        return
    if not isinstance(expected, (int, float)) or not isinstance(actual, (int, float)):
        report.mismatches.append(Mismatch(path, expected, actual, None, "not a number"))
        return
    abs_tol, rel_tol = _tolerance(tolerances, path)
    allowed = abs_tol + rel_tol * abs(float(expected))
    diff = abs(float(actual) - float(expected))
    if not math.isfinite(float(actual)) or diff > allowed:
        report.mismatches.append(Mismatch(path, expected, actual, allowed, f"off by {diff:.6g}"))


def compare_to_golden(name: str, actual: dict, golden: dict | None = None) -> GoldenReport:
    """Compare ``actual`` metrics with golden ``name`` (read from disk unless ``golden`` is given)."""
    if golden is None:
        path = golden_path(name)
        if not path.is_file():
            report = GoldenReport(name)
            report.mismatches.append(Mismatch(str(path), "a golden file", None, None, "golden file does not exist"))
            return report
        golden = json.loads(path.read_text(encoding="utf-8"))
    report = GoldenReport(name)
    _walk(golden.get("metrics", {}), actual, "", golden.get("tolerances", {}), report)
    return report


def update_mode() -> str | None:
    """The update reason when running under tools/ci/update_goldens.py, else None."""
    reason = os.environ.get(ENV_UPDATE_REASON, "").strip()
    if not reason:
        return None
    if os.environ.get("CI"):
        raise RuntimeError("golden update mode is not allowed in CI")
    if not os.environ.get(ENV_UPDATE_LOG):
        raise RuntimeError(f"{ENV_UPDATE_REASON} is set without {ENV_UPDATE_LOG}: use tools/ci/update_goldens.py")
    return reason


def _prune_like(template, actual):
    """``actual`` restricted to the keys of ``template`` (so an update keeps the golden's scope)."""
    if isinstance(template, dict) and isinstance(actual, dict):
        return {k: _prune_like(v, actual[k]) for k, v in template.items() if k in actual}
    return actual


def check_golden(name: str, actual: dict, description: str = "", default_tolerance: dict | None = None) -> GoldenReport:
    """What tests call. Normally compares and returns the report (assert ``report.ok``).

    In update mode (only via tools/ci/update_goldens.py) it rewrites ``metrics`` of the golden
    (keeping its tolerances, description and the set of keys it pins; a new golden pins
    everything) and records the change in the update log, then returns an OK report.
    """
    reason = update_mode()
    if reason is None:
        return compare_to_golden(name, actual)

    path = golden_path(name)
    old = json.loads(path.read_text(encoding="utf-8")) if path.is_file() else None
    before = compare_to_golden(name, actual, old) if old is not None else None
    new = {
        "name": name,
        "description": (old or {}).get("description", description),
        "tolerances": (old or {}).get("tolerances", {"default": default_tolerance or {"abs": 0.0, "rel": 0.0}}),
        "metrics": _prune_like(old["metrics"], actual) if old is not None else actual,
    }
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(new, indent=2, sort_keys=False) + "\n", encoding="utf-8")
    entry = {
        "name": name,
        "created": old is None,
        "changed": [] if before is None else [m.path for m in before.mismatches],
    }
    with open(os.environ[ENV_UPDATE_LOG], "a", encoding="utf-8") as log:
        log.write(json.dumps(entry) + "\n")
    return GoldenReport(name, checked=0)


def assert_golden(name: str, actual: dict, **kwargs) -> None:
    """``check_golden`` that raises AssertionError with the readable report on a mismatch."""
    report = check_golden(name, actual, **kwargs)
    assert report.ok, str(report)
