"""Shared fixtures for the tools/acoustics tests. Puts the repository root on sys.path so the
package imports as ``tools.acoustics`` (as ``python -m tools.acoustics`` does)."""

import os
import pathlib
import sys

import pytest

REPO = pathlib.Path(__file__).resolve().parents[3]
if str(REPO) not in sys.path:
    sys.path.insert(0, str(REPO))

from tools.acoustics import render_cli  # noqa: E402


def pytest_configure(config):
    config.addinivalue_line(
        "markers",
        "ensemble: Phase 04 AX11 ensemble gates (thousands of renders); CI runs them in the tail-gates "
        "job, one room per job, and deselects them in the python job",
    )
    config.addinivalue_line(
        "markers",
        "slow: full recomputation of a committed reference record (minutes, several GB; Phase 05e D-B gate); "
        "the python CI job deselects it, .github/workflows/nightly.yml runs it",
    )
    config.addinivalue_line(
        "markers",
        "open_field_validation: AX37 (5.4) open_field check at the validation N 2^23 (two renders, 4-6.5 min "
        "each); CI runs it in the open-field-validation job on three OSes and deselects it in the python job "
        "(decider file 50, P05H-QA-T)",
    )


@pytest.fixture(scope="session")
def render_cli_path() -> pathlib.Path:
    """The render_cli binary. Skips when it isn't built, unless SPATIAL_REQUIRE_RENDER_CLI=1 (CI),
    in which case a missing binary is a failure."""
    path = render_cli.find_render_cli()
    if path is None:
        if os.environ.get("SPATIAL_REQUIRE_RENDER_CLI") == "1":
            pytest.fail("render_cli not found (set RENDER_CLI or build a preset); required by SPATIAL_REQUIRE_RENDER_CLI=1")
        pytest.skip("render_cli not built (cmake --preset cli && cmake --build --preset cli)")
    return path
