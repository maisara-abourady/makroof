"""Puts the repository root on sys.path so the package imports as ``tools.validation``."""

import os
import pathlib
import sys

import pytest

REPO = pathlib.Path(__file__).resolve().parents[3]
if str(REPO) not in sys.path:
    sys.path.insert(0, str(REPO))


def pytest_configure(config):
    config.addinivalue_line(
        "markers",
        "nightly: Phase 05 validation gate against the BRAS baseline (.github/workflows/nightly.yml); "
        "the python CI job deselects it",
    )


@pytest.fixture(scope="session")
def render_cli_path():
    from tools.acoustics import render_cli

    path = render_cli.find_render_cli()
    if path is None:
        if os.environ.get("SPATIAL_REQUIRE_RENDER_CLI") == "1":
            pytest.fail("render_cli not found; required by SPATIAL_REQUIRE_RENDER_CLI=1")
        pytest.skip("render_cli not built")
    return path
