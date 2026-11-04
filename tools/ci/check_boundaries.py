#!/usr/bin/env python3
"""Enforces the contract boundary (CLAUDE.md "The contract boundary", BUILD_PLAN §1).

Fails (exit 1) when, in any C/C++ source under src/:
  - src/sim/      includes anything from src/module3d/ or src/plugin/;
  - src/module3d/ includes anything from src/sim/ or src/plugin/;
  - src/contract/ includes anything from src/sim/, src/module3d/ or src/plugin/ (it is the bottom layer);
  - src/contract/ or src/sim/ includes a JUCE header (juce_*, JuceHeader.h).

An include counts as "from src/<lib>/" when its path starts with "<lib>/" (the include root is src/)
or when it resolves, relative to the including file, into src/<lib>/.

Usage: tools/ci/check_boundaries.py [--root REPO_ROOT]
"""

from __future__ import annotations

import argparse
import pathlib
import re
import sys
from dataclasses import dataclass

SOURCE_SUFFIXES = {".h", ".hh", ".hpp", ".hxx", ".inl", ".ipp", ".c", ".cc", ".cpp", ".cxx", ".m", ".mm"}
INCLUDE_RE = re.compile(r'^\s*#\s*(?:include|import)\s*([<"])([^>"]+)[>"]')

# library -> libraries it must not include
FORBIDDEN_LIBS = {
    "sim": {"module3d", "plugin"},
    "module3d": {"sim", "plugin"},
    "contract": {"sim", "module3d", "plugin"},
}
NO_JUCE = {"contract", "sim"}


@dataclass(frozen=True)
class Violation:
    file: pathlib.Path
    line: int
    include: str
    reason: str

    def format(self, root: pathlib.Path) -> str:
        return f"{self.file.relative_to(root).as_posix()}:{self.line}: #include {self.include!r}: {self.reason}"


def is_juce_header(include: str) -> bool:
    name = include.replace("\\", "/").split("/")[-1]
    first = include.replace("\\", "/").split("/")[0]
    return name.startswith("juce_") or first.startswith("juce_") or name == "JuceHeader.h"


def included_library(src: pathlib.Path, including_file: pathlib.Path, include: str) -> str | None:
    """Returns the src/ library an include points into, or None."""
    normalized = include.replace("\\", "/")
    first = normalized.split("/")[0]
    if first in {"sim", "module3d", "plugin", "contract", "cli"} and "/" in normalized:
        return first
    resolved = (including_file.parent / normalized).resolve()
    try:
        relative = resolved.relative_to(src.resolve())
    except ValueError:
        return None
    return relative.parts[0] if len(relative.parts) > 1 else None


def check(root: pathlib.Path) -> list[Violation]:
    src = root / "src"
    violations: list[Violation] = []
    for lib in sorted(FORBIDDEN_LIBS):
        lib_dir = src / lib
        if not lib_dir.is_dir():
            continue
        for path in sorted(p for p in lib_dir.rglob("*") if p.is_file() and p.suffix.lower() in SOURCE_SUFFIXES):
            text = path.read_text(encoding="utf-8", errors="replace")
            for number, line in enumerate(text.splitlines(), start=1):
                match = INCLUDE_RE.match(line)
                if not match:
                    continue
                include = match.group(2).strip()
                if lib in NO_JUCE and is_juce_header(include):
                    violations.append(Violation(path, number, include, f"src/{lib} must not include JUCE"))
                    continue
                target = included_library(src, path, include)
                if target in FORBIDDEN_LIBS[lib]:
                    violations.append(
                        Violation(path, number, include, f"src/{lib} must not include from src/{target}")
                    )
    return violations


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--root", type=pathlib.Path, default=pathlib.Path(__file__).resolve().parents[2])
    args = parser.parse_args(argv)
    root = args.root.resolve()
    if not (root / "src").is_dir():
        print(f"check_boundaries: no src/ directory under {root}", file=sys.stderr)
        return 2
    violations = check(root)
    for violation in violations:
        print(violation.format(root), file=sys.stderr)
    if violations:
        print(f"check_boundaries: {len(violations)} violation(s)", file=sys.stderr)
        return 1
    print("check_boundaries: OK (sim, module3d and contract respect the contract boundary)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
