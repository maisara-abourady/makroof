"""Puts the repository root on sys.path so the package imports as ``tools.validation``."""

import pathlib
import sys

REPO = pathlib.Path(__file__).resolve().parents[3]
if str(REPO) not in sys.path:
    sys.path.insert(0, str(REPO))
