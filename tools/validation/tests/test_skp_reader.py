"""tools/validation/skp_reader.py against what BRAS documents (needs the BRAS cache: run
fetch_bras.py --groups materials geometry; skipped otherwise, required in the nightly job)."""

import os

import pytest

from tools.validation import extract_bras_geometry as ex, fetch_bras, skp_reader

CACHE = fetch_bras.cache_dir()


def _need(path):
    if not path.exists():
        if os.environ.get("MAKROOF_REQUIRE_BRAS") == "1":
            pytest.fail(f"{path} missing (MAKROOF_REQUIRE_BRAS=1)")
        pytest.skip("BRAS cache not present")


def test_cr2_material_areas_match_the_documentation():
    skp = CACHE / "CR2" / "geometry" / "CR2.skp"
    _need(skp)
    doc = ex.documented_materials((CACHE / "materials" / "descr" / "mat_CR2.txt").read_text(errors="replace"))
    model = skp_reader.read(skp.read_bytes())
    polys = skp_reader.world_polygons(model)
    acc = {}
    for p in polys:
        acc[p.material] = acc.get(p.material, 0.0) + p.area_m2
    names = ex.match_materials({k: v for k, v in acc.items() if k is not None}, doc["areas"])
    for k, name in names.items():
        assert acc[k] == pytest.approx(doc["areas"][name], abs=0.011)
    assert sum(doc["areas"].values()) == pytest.approx(doc["S"], abs=0.02)
    assert max(p.off_plane_m for p in polys) < 1e-9
