"""Locate and run the render_cli binary (src/cli) from Python (tests, listening pack).

Lookup order: the ``RENDER_CLI`` environment variable, then build/<preset>/render_cli[.exe] for
the presets cli, release and debug.
"""

from __future__ import annotations

import os
import pathlib
import subprocess
import sys

REPO = pathlib.Path(__file__).resolve().parents[2]
PRESETS = ("cli", "release", "debug")
EXE = "render_cli.exe" if sys.platform == "win32" else "render_cli"


def find_render_cli() -> pathlib.Path | None:
    env = os.environ.get("RENDER_CLI")
    if env:
        path = pathlib.Path(env)
        return path if path.is_file() else None
    for preset in PRESETS:
        path = REPO / "build" / preset / EXE
        if path.is_file():
            return path
    return None


def run(binary: pathlib.Path, *args: str | os.PathLike) -> subprocess.CompletedProcess:
    """Run render_cli with ``args``; returns the completed process (text stdout/stderr)."""
    return subprocess.run([str(binary), *map(str, args)], capture_output=True, text=True, check=False)
