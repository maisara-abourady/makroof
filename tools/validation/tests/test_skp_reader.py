"""tools/validation/skp_reader.py against what BRAS documents (needs the BRAS cache: run
fetch_bras.py --groups materials geometry; skipped otherwise, required in the nightly job).

The bras_mapping.md §2 acceptance test, one rule for every selected room (no per-room logic):
every documented material area reproduces (one-to-one, to the printed 0.01 m², ±0.1 % for large
areas, the tolerance of extract_bras_geometry.match_materials) and every loop vertex lies on its
face's plane within AX30 (SketchUp's geometric tolerance, 0.001 inch).
"""

import os

import pytest

from tools.validation import extract_bras_geometry as ex, fetch_bras, skp_reader

CACHE = fetch_bras.cache_dir()
# AX30: planarity limit |n.p + d| for every loop vertex = SketchUp's geometric tolerance, 0.001 in.
# CR2 and CR3 meet 1e-9 m (7.2e-16, 3.2e-12 m); CR4's textured model reads up to 1.98e-5 m.
OFF_PLANE_TOL_M = 0.001 * skp_reader.INCH


def _need(path):
    if not path.exists():
        if os.environ.get("MAKROOF_REQUIRE_BRAS") == "1":
            pytest.fail(f"{path} missing (MAKROOF_REQUIRE_BRAS=1)")
        pytest.skip("BRAS cache not present")


@pytest.mark.parametrize("room", ["CR2", "CR3", "CR4"])
def test_material_areas_match_the_documentation(room):
    skp = CACHE / room / "geometry" / f"{room}.skp"
    _need(skp)
    descr = (CACHE / "materials" / "descr" / f"mat_{room}.txt").read_text(encoding="utf-8", errors="replace")
    doc = ex.documented_materials(descr)
    model = skp_reader.read(skp.read_bytes())
    polys = skp_reader.world_polygons(model)
    acc = {}
    for p in polys:
        acc[p.material] = acc.get(p.material, 0.0) + p.area_m2
    acc.pop(None, None)
    names = ex.match_materials(acc, doc["areas"])  # one-to-one; raises on any unmatched area
    assert sorted(names.values()) == sorted(doc["areas"])
    for k, name in names.items():
        assert acc[k] == pytest.approx(doc["areas"][name], abs=max(0.011, 1e-3 * doc["areas"][name]))
    assert sum(doc["areas"].values()) == pytest.approx(doc["S"], abs=0.06)
    assert max(p.off_plane_m for p in polys) < OFF_PLANE_TOL_M
    assert model.faces_not_resolved == 0


def test_texture_coordinate_record_layout():
    """CFaceTextureCoords: 6 bytes, 24 doubles, u32 n, n x 4 doubles, 12 bytes (214 + 32 n)."""
    import struct

    for n in (0, 4):
        body = bytes(6) + bytes(192) + struct.pack("<I", n) + bytes(32 * n) + bytes(12) + b"\x00\x00"
        p = skp_reader._Parser(body, 0, 0, {}, {})
        skp_reader._texcoords(p, {})
        assert p.pos == 214 + 32 * n
    bad = bytes(198) + struct.pack("<I", 1000) + bytes(64)
    with pytest.raises(skp_reader._Stop):
        skp_reader._texcoords(skp_reader._Parser(bad, 0, 0, {}, {}), {})
