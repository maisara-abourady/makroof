"""golden.py and tools/ci/update_goldens.py."""

import json
import os
import subprocess
import sys

import pytest

from tools.acoustics import golden

from conftest import REPO

GOLDEN = {
    "name": "example",
    "description": "test",
    "tolerances": {"default": {"rel": 0.02}, "C80": {"abs": 0.5}, "bands.63.T30": {"rel": 0.1}},
    "metrics": {"bands": {"63": {"T30": 1.0, "C80": 2.0}, "1000": {"T30": 1.0, "label": "x", "none": None}}},
}


def test_within_tolerance_passes():
    actual = {"bands": {"63": {"T30": 1.09, "C80": 2.4, "extra": 5}, "1000": {"T30": 1.019, "label": "x", "none": None}}}
    report = golden.compare_to_golden("example", actual, GOLDEN)
    assert report.ok, str(report)
    assert report.checked == 5


def test_tolerance_lookup_order_and_failures():
    actual = {"bands": {"63": {"T30": 1.11, "C80": 2.6}, "1000": {"T30": 1.021, "label": "y", "none": 0.0}}}
    report = golden.compare_to_golden("example", actual, GOLDEN)
    paths = sorted(m.path for m in report.mismatches)
    assert paths == ["bands.1000.T30", "bands.1000.label", "bands.1000.none", "bands.63.C80", "bands.63.T30"]
    assert "bands.63.T30" in str(report)


def test_missing_values_and_missing_golden_fail():
    report = golden.compare_to_golden("example", {"bands": {"63": {"T30": 1.0}}}, GOLDEN)
    assert not report.ok
    assert any("missing" in m.reason for m in report.mismatches)
    assert not golden.compare_to_golden("does_not_exist_anywhere", {}).ok


def test_nan_never_passes():
    report = golden.compare_to_golden("example", {"bands": {"63": {"T30": float("nan"), "C80": 2.0}}}, {"metrics": {"bands": {"63": {"T30": 1.0}}}, "tolerances": {"default": {"rel": 1.0}}})
    assert not report.ok


def test_check_golden_never_writes_outside_update_mode(tmp_path, monkeypatch):
    monkeypatch.setenv(golden.ENV_GOLDEN_DIR, str(tmp_path))
    monkeypatch.delenv(golden.ENV_UPDATE_REASON, raising=False)
    (tmp_path / "example.json").write_text(json.dumps(GOLDEN), encoding="utf-8")
    before = (tmp_path / "example.json").read_text(encoding="utf-8")
    report = golden.check_golden("example", {"bands": {"63": {"T30": 9.0, "C80": 9.0}, "1000": {}}})
    assert not report.ok
    assert (tmp_path / "example.json").read_text(encoding="utf-8") == before


def test_update_mode_needs_the_script(monkeypatch):
    monkeypatch.setenv(golden.ENV_UPDATE_REASON, "some reason here")
    monkeypatch.delenv(golden.ENV_UPDATE_LOG, raising=False)
    monkeypatch.delenv("CI", raising=False)
    with pytest.raises(RuntimeError):
        golden.update_mode()
    monkeypatch.setenv(golden.ENV_UPDATE_LOG, "x")
    monkeypatch.setenv("CI", "true")
    with pytest.raises(RuntimeError):
        golden.update_mode()


def _run_update(tmp_path, reason, test_file, *extra):
    env = {k: v for k, v in os.environ.items() if k != "CI"}  # the script refuses to run in CI
    env[golden.ENV_GOLDEN_DIR] = str(tmp_path / "golden")
    return subprocess.run(
        [sys.executable, str(REPO / "tools" / "ci" / "update_goldens.py"), "--reason", reason, *extra, str(test_file), "-q", "-p", "no:cacheprovider"],
        cwd=REPO, env=env, capture_output=True, text=True, check=False,
    )


def test_update_script_rewrites_and_logs(tmp_path):
    golden_dir = tmp_path / "golden"
    golden_dir.mkdir()
    (golden_dir / "example.json").write_text(json.dumps(GOLDEN), encoding="utf-8")
    (golden_dir / "CHANGELOG.md").write_text("# Golden file change log\n\n", encoding="utf-8")
    test_file = tmp_path / "test_uses_golden.py"
    test_file.write_text(
        "import sys\n"
        f"sys.path.insert(0, {str(REPO)!r})\n"
        "from tools.acoustics import golden\n"
        "def test_it():\n"
        "    golden.assert_golden('example', {'bands': {'63': {'T30': 1.5, 'C80': 2.1, 'new': 1},"
        " '1000': {'T30': 1.0, 'label': 'x', 'none': None}}})\n"
        "    golden.assert_golden('brand_new', {'x': 1.0}, default_tolerance={'rel': 0.01})\n"
        "    golden.assert_golden('with_tolerances', {'x': 1.0}, tolerances={'default': {'abs': 0.0}, 'x': {'abs': 0.5}})\n",
        encoding="utf-8",
    )
    result = _run_update(tmp_path, "Phase 99: intended change for the test", test_file)
    assert result.returncode == 0, result.stdout + result.stderr

    updated = json.loads((golden_dir / "example.json").read_text(encoding="utf-8"))
    assert updated["tolerances"] == GOLDEN["tolerances"]  # tolerances kept
    assert updated["metrics"]["bands"]["63"] == {"T30": 1.5, "C80": 2.1}  # scope kept, value updated
    created = json.loads((golden_dir / "brand_new.json").read_text(encoding="utf-8"))
    assert created["tolerances"] == {"default": {"rel": 0.01}}
    with_tolerances = json.loads((golden_dir / "with_tolerances.json").read_text(encoding="utf-8"))
    assert with_tolerances["tolerances"] == {"default": {"abs": 0.0}, "x": {"abs": 0.5}}

    log = (golden_dir / "CHANGELOG.md").read_text(encoding="utf-8")
    assert "Reason: Phase 99: intended change for the test" in log
    assert "`example`: changed `bands.63.T30`" in log
    assert "`brand_new`: created" in log

    # Back in normal mode the new values compare clean.
    env_backup = os.environ.get(golden.ENV_GOLDEN_DIR)
    os.environ[golden.ENV_GOLDEN_DIR] = str(golden_dir)
    try:
        after = {"bands": {"63": {"T30": 1.5, "C80": 2.1}, "1000": {"T30": 1.0, "label": "x", "none": None}}}
        assert golden.compare_to_golden("example", after).ok
    finally:
        if env_backup is None:
            del os.environ[golden.ENV_GOLDEN_DIR]
        else:
            os.environ[golden.ENV_GOLDEN_DIR] = env_backup


def test_update_script_requires_a_reason(tmp_path):
    test_file = tmp_path / "test_nothing.py"
    test_file.write_text("def test_x():\n    pass\n", encoding="utf-8")
    assert _run_update(tmp_path, "short", test_file).returncode != 0


def test_update_script_fails_when_no_golden_is_checked(tmp_path):
    (tmp_path / "golden").mkdir()
    test_file = tmp_path / "test_nothing.py"
    test_file.write_text("def test_x():\n    pass\n", encoding="utf-8")
    result = _run_update(tmp_path, "a reason that is long enough", test_file)
    assert result.returncode == 1
    assert not (tmp_path / "golden" / "CHANGELOG.md").exists()


def test_update_refuses_to_drop_a_pinned_value(tmp_path):
    golden_dir = tmp_path / "golden"
    golden_dir.mkdir()
    (golden_dir / "example.json").write_text(json.dumps(GOLDEN), encoding="utf-8")
    test_file = tmp_path / "test_drops_a_value.py"
    test_file.write_text(
        "import sys\n"
        f"sys.path.insert(0, {str(REPO)!r})\n"
        "from tools.acoustics import golden\n"
        "def test_it():\n"
        "    golden.assert_golden('example', {'bands': {'63': {'T30': 1.5}, '1000': {'T30': 1.0, 'label': 'x', 'none': None}}})\n",
        encoding="utf-8",
    )
    result = _run_update(tmp_path, "Phase 99: this update would drop C80", test_file)
    assert result.returncode != 0
    assert "bands.63.C80" in result.stdout + result.stderr
    assert json.loads((golden_dir / "example.json").read_text(encoding="utf-8")) == GOLDEN  # untouched
    assert not (golden_dir / "CHANGELOG.md").exists()


def test_update_script_extend_adds_new_keys_and_keeps_pinned_ones(tmp_path):
    """--extend (phase-05f: a validation room added to the baseline) pins new keys too; without it
    the scope is kept; neither drops a pinned value."""
    golden_dir = tmp_path / "golden"
    golden_dir.mkdir()
    (golden_dir / "example.json").write_text(json.dumps(GOLDEN), encoding="utf-8")
    test_file = tmp_path / "test_extends.py"
    test_file.write_text(
        "import sys\n"
        f"sys.path.insert(0, {str(REPO)!r})\n"
        "from tools.acoustics import golden\n"
        "def test_it():\n"
        "    golden.assert_golden('example', {'bands': {'63': {'T30': 1.2, 'C80': 2.0}, '1000': {'T30': 1.0, 'label': 'x', 'none': None},"
        " '2000': {'T30': 0.8}}})\n",
        encoding="utf-8",
    )
    result = _run_update(tmp_path, "Phase 99: room added to the golden", test_file, "--extend")
    assert result.returncode == 0, result.stdout + result.stderr
    updated = json.loads((golden_dir / "example.json").read_text(encoding="utf-8"))
    assert updated["metrics"]["bands"]["2000"] == {"T30": 0.8}
    assert updated["metrics"]["bands"]["63"] == {"T30": 1.2, "C80": 2.0}  # pinned keys kept (values rewritten)
    assert updated["tolerances"] == GOLDEN["tolerances"]
    log = (golden_dir / "CHANGELOG.md").read_text(encoding="utf-8")
    assert "`example`: extended by 1 new key(s): `bands.2000`" in log
