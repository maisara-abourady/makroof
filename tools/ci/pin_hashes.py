#!/usr/bin/env python3
"""Add (or refresh) --hash lines for every `name==version` pin in pip requirements files.

    python tools/ci/pin_hashes.py tools/ci/requirements.txt tools/acoustics/requirements.txt

The hashes come from PyPI's JSON API and cover every file PyPI publishes for that release (all
wheels and the sdist), so the same file installs on Linux, macOS and Windows. Once any requirement
carries a hash, pip runs in hash-checking mode: every package it installs, including transitive
dependencies, must then be pinned with hashes in the files given to that pip command.

Run it after changing a pin. Comments and blank lines are kept; existing --hash lines are replaced.
"""

from __future__ import annotations

import json
import pathlib
import re
import sys
import urllib.request

PIN = re.compile(r"^([A-Za-z0-9_.\-]+)==([A-Za-z0-9_.\-+!]+)\s*(?:\\)?\s*(#.*)?$")


def release_hashes(name: str, version: str) -> list[str]:
    with urllib.request.urlopen(f"https://pypi.org/pypi/{name}/{version}/json", timeout=60) as response:
        data = json.load(response)
    hashes = sorted({f["digests"]["sha256"] for f in data["urls"]})
    if not hashes:
        raise RuntimeError(f"PyPI lists no files for {name}=={version}")
    return hashes


def rewrite(path: pathlib.Path) -> None:
    out: list[str] = []
    for raw in path.read_text(encoding="utf-8").splitlines():
        line = raw.strip()
        if line.startswith("--hash"):
            continue  # replaced below
        match = PIN.match(line)
        if not match:
            out.append(raw)
            continue
        name, version, comment = match.groups()
        hashes = release_hashes(name, version)
        head = f"{name}=={version}" + (f"  {comment}" if comment else "")
        if comment:
            out.append(f"# {comment.lstrip('#').strip()}")
            head = f"{name}=={version}"
        out.append(head + " \\")
        out += [f"    --hash=sha256:{h}" + (" \\" if i < len(hashes) - 1 else "") for i, h in enumerate(hashes)]
        print(f"{path}: {name}=={version}: {len(hashes)} hashes")
    path.write_text("\n".join(out) + "\n", encoding="utf-8")


def main(argv: list[str]) -> int:
    if not argv:
        print(__doc__, file=sys.stderr)
        return 1
    for arg in argv:
        rewrite(pathlib.Path(arg))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
