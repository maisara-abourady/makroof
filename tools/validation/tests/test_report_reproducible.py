"""Phase 05e criterion: the report generates reproducibly (two runs give identical numbers).

Runs the comparison twice on one initial- and one fitted-α pair per room (renders are deterministic:
fixed tailSeed; the analysis is seeded nowhere) and checks that the results and the report text are
identical. Needs render_cli and the BRAS cache, so it is marked nightly."""

import json

import pytest

from tools.acoustics import render_cli
from tools.validation import fetch_bras, report
from tools.validation import run_validation as rv

pytestmark = pytest.mark.nightly

SUBSET = {"bras_cr2_ls1_mp1", "bras_cr2_ls1_mp1_fitted", "bras_cr3_ls1_mp1", "bras_cr3_ls1_mp1_fitted",
          "bras_cr4_ls1_mp1", "bras_cr4_ls1_mp1_fitted"}  # one pair per room (phase-05f: three rooms)


def test_two_runs_give_identical_numbers_and_report(tmp_path):
    binary = render_cli.find_render_cli()
    if binary is None:
        pytest.skip("render_cli not built")
    cache = fetch_bras.cache_dir()
    if not (cache / "CR2" / "rirs").exists():
        pytest.skip("BRAS cache not fetched")
    a = rv.run(binary, cache, log=lambda *_: None, only=SUBSET, plots=False)
    b = rv.run(binary, cache, log=lambda *_: None, only=SUBSET, plots=False)
    ja, jb = json.dumps(a, sort_keys=True, default=float), json.dumps(b, sort_keys=True, default=float)
    assert ja == jb
    report.write(a, tmp_path / "a.md")
    report.write(b, tmp_path / "b.md")
    assert (tmp_path / "a.md").read_text() == (tmp_path / "b.md").read_text()
