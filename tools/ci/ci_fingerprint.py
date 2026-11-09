"""Fingerprint of everything that can change a CI result, so CI can skip a tree it already passed.

The fingerprint is the SHA-256 of `git ls-tree -r <rev>` (mode, object id and path of every tracked
file) with the INERT paths removed. Two commits with the same fingerprint differ only in inert files,
so a full green CI run on one is a full green run on the other. `.github/workflows/ci.yml` uses it:
the `changes` job looks up a pass marker keyed by the fingerprint, and the `ci-ok` job writes that
marker only when every job of the run succeeded.

INERT is deliberately narrow: prose that no build, test or CI script reads. A path read by anything
in src/, tests/, tools/, cmake/ or the workflows must NOT be listed here (docs/contract/ holds the
schema read by tools/ci/test_schema_agreement.py; docs/validation/ holds bras_mapping.md read by
tools/validation/make_bras_scenes.py, so both stay in). When in doubt, leave a path out of INERT:
the cost is one extra CI run, the cost of a wrong entry is a skipped test.

Usage: python tools/ci/ci_fingerprint.py [--rev REV]   (prints the fingerprint)
"""

from __future__ import annotations

import argparse
import hashlib
import subprocess
import sys
from pathlib import PurePosixPath

# Bump to invalidate every recorded pass marker (e.g. after changing what a pass means).
SCHEME = "1"

# Directory prefixes whose whole content is inert.
INERT_DIRS = (
    ".claude/",  # agent, skill and command prompts
    "docs/board/",  # board personas and seat protocol: sources of the generated agent prompts
    "docs/sessions/",
    "docs/review/",
    "docs/phases/",
)

# Single inert files.
INERT_FILES = frozenset(
    {
        "CLAUDE.md",
        "README.md",
        "docs/PRD.md",
        "docs/BUILD_PLAN.md",
        "docs/THIRD_PARTY.md",
    }
)


def is_inert(path: str) -> bool:
    p = PurePosixPath(path).as_posix()
    return p in INERT_FILES or p.startswith(INERT_DIRS)


def fingerprint_from_ls_tree(ls_tree: str) -> str:
    """Fingerprint from the output of `git ls-tree -r <rev>` (lines '<mode> <type> <oid>\\t<path>')."""
    h = hashlib.sha256(f"makroof-ci-fingerprint/{SCHEME}\n".encode())
    for line in sorted(ls_tree.splitlines()):
        if not line.strip():
            continue
        _, path = line.split("\t", 1)
        if not is_inert(path):
            h.update(line.encode("utf-8") + b"\n")
    return h.hexdigest()


def fingerprint(rev: str = "HEAD") -> str:
    out = subprocess.run(
        ["git", "-c", "core.quotePath=false", "ls-tree", "-r", "--full-tree", rev],
        check=True,
        capture_output=True,
        text=True,
        encoding="utf-8",
    ).stdout
    return fingerprint_from_ls_tree(out)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--rev", default="HEAD", help="commit or tree to fingerprint (default HEAD)")
    args = parser.parse_args(argv)
    print(fingerprint(args.rev))
    return 0


if __name__ == "__main__":
    sys.exit(main())
