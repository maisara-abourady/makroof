"""Self-test of tools/ci/ci_fingerprint.py: inert edits keep the fingerprint, every other edit changes it,
and no inert path is read by the build, the tests or the CI scripts."""

from __future__ import annotations

import re
import subprocess
import sys
from pathlib import Path

import pytest

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))

import ci_fingerprint as fp  # noqa: E402

OID_A = "a" * 40
OID_B = "b" * 40


def tree(**files: str) -> str:
    return "\n".join(f"100644 blob {oid}\t{path}" for path, oid in files.items())


BASE = {
    "src/sim/Ism.cpp": OID_A,
    "docs/BUILD_PLAN.md": OID_A,
    "docs/sessions/2026-11-07-x.md": OID_A,
    "docs/contract/scene-v1.schema.json": OID_A,
}


def with_change(path: str) -> dict[str, str]:
    files = dict(BASE)
    files[path] = OID_B
    return files


@pytest.mark.parametrize(
    "path",
    ["docs/BUILD_PLAN.md", "docs/sessions/2026-11-07-x.md", "docs/review/phase-06/r.md", "CLAUDE.md",
     ".claude/agents/steward.md", "docs/phases/phase-07.md"],
)
def test_inert_change_keeps_fingerprint(path: str) -> None:
    files = dict(BASE)
    files[path] = OID_B  # changed or added
    assert fp.fingerprint_from_ls_tree(tree(**files)) == fp.fingerprint_from_ls_tree(tree(**BASE))


@pytest.mark.parametrize(
    "path",
    ["src/sim/Ism.cpp", "docs/contract/scene-v1.schema.json", "docs/validation/bras_mapping.md",
     ".github/workflows/ci.yml", "tools/ci/ci_fingerprint.py", "tests/golden/CHANGELOG.md",
     "docs/phases.md", "docs/sessionsX/a.md"],
)
def test_other_change_changes_fingerprint(path: str) -> None:
    assert fp.fingerprint_from_ls_tree(tree(**with_change(path))) != fp.fingerprint_from_ls_tree(tree(**BASE))


def test_removing_a_file_changes_fingerprint() -> None:
    files = dict(BASE)
    del files["src/sim/Ism.cpp"]
    assert fp.fingerprint_from_ls_tree(tree(**files)) != fp.fingerprint_from_ls_tree(tree(**BASE))


def test_mode_change_changes_fingerprint() -> None:
    a = tree(**BASE)
    b = a.replace("100644 blob " + OID_A + "\tsrc/sim/Ism.cpp", "100755 blob " + OID_A + "\tsrc/sim/Ism.cpp")
    assert a != b
    assert fp.fingerprint_from_ls_tree(a) != fp.fingerprint_from_ls_tree(b)


def test_order_independent() -> None:
    lines = tree(**BASE).splitlines()
    assert fp.fingerprint_from_ls_tree("\n".join(reversed(lines))) == fp.fingerprint_from_ls_tree("\n".join(lines))


def test_real_repo_head() -> None:
    try:
        subprocess.run(["git", "-C", str(REPO), "rev-parse", "HEAD"], check=True, capture_output=True)
    except (OSError, subprocess.CalledProcessError):
        pytest.skip("not a git checkout")
    assert re.fullmatch(r"[0-9a-f]{64}", fp.fingerprint("HEAD"))


def _inert_tracked_paths() -> list[str]:
    out = subprocess.run(["git", "-C", str(REPO), "ls-files"], check=True, capture_output=True, text=True).stdout
    return [p for p in out.splitlines() if fp.is_inert(p)]


def test_no_inert_path_is_read_by_build_tests_or_ci() -> None:
    """Every inert file is referenced by name nowhere a build, test or CI step could read it from.

    Mentions in comments and docstrings are fine but cannot be told apart from reads by a grep, so
    the check is on the path expressions that would read the file: the exact relative path, or the
    file name joined to `docs` / the repository root through pathlib (`/ "BUILD_PLAN.md"`).
    """
    try:
        inert = _inert_tracked_paths()
    except (OSError, subprocess.CalledProcessError):
        pytest.skip("not a git checkout")
    roots = ["src", "tests", "tools", "cmake", ".github", "CMakeLists.txt", "CMakePresets.json"]
    code_files = [
        f
        for r in roots
        for f in ([REPO / r] if (REPO / r).is_file() else (REPO / r).rglob("*"))
        if f.is_file() and f.suffix in {".py", ".sh", ".yml", ".yaml", ".cmake", ".txt", ".json", ".cpp", ".h", ".hpp"}
        and f.resolve() != Path(__file__).resolve()
        and f.name != "ci_fingerprint.py"
    ]
    patterns = set()
    for p in inert:
        name = p.rsplit("/", 1)[-1]
        patterns.add(re.compile(r"""['"]""" + re.escape(p) + r"""['"]"""))  # "docs/BUILD_PLAN.md" as a string literal
        patterns.add(re.compile(r"""/\s*['"]""" + re.escape(name) + r"""['"]"""))  # REPO / "BUILD_PLAN.md"
    for d in fp.INERT_DIRS:
        top = d.rstrip("/").rsplit("/", 1)[-1]
        patterns.add(re.compile(r"""/\s*['"]""" + re.escape(top) + r"""['"]"""))  # REPO / "docs" / "sessions"
        patterns.add(re.compile(r"""['"]""" + re.escape(d)))  # "docs/sessions/..."
    hits = []
    for f in code_files:
        text = f.read_text(encoding="utf-8", errors="replace")
        for pat in patterns:
            for m in pat.finditer(text):
                hits.append(f"{f.relative_to(REPO)}: {m.group(0)}")
    assert not hits, "inert paths read by code; remove them from INERT in ci_fingerprint.py:\n" + "\n".join(hits)
