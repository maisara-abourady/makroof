"""tools/validation/skp_reader.py against what BRAS documents (needs the BRAS cache: run
fetch_bras.py --groups materials geometry; skipped otherwise, required in the nightly job).

The bras_mapping.md §2 acceptance test, one rule for every selected room (no per-room logic):
every documented material area reproduces (one-to-one, to within 1.1 × its printed unit, absolute:
0.011 m², extract_bras_geometry.AREA_TOL_M2; phase-05g, ledger T5g-1…T5g-18), the reader's total
over all faces reproduces the documented S to within 1.1 × S's printed unit, and every loop vertex
lies on its face's plane within AX30 (1 mm absolute).
"""

import os

import pytest

from tools.validation import extract_bras_geometry as ex, fetch_bras, skp_reader

CACHE = fetch_bras.cache_dir()
# AX30: planarity limit |n.p + d| <= 1 mm for every loop vertex (absolute, one rule for all rooms;
# a misparse gives metres, 1 mm is ~15 x below lambda/2 at 11.3 kHz). Measured: CR2 7.2e-16 m,
# CR3 3.2e-12 m, CR4 1.98e-5 m (bras_geometry.json max_off_plane_m).
OFF_PLANE_TOL_M = 1.0e-3


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
    units = ex.documented_units(descr)
    assert set(units["areas"].values()) == {ex.AREA_UNIT_M2}  # every BRAS area printed to 0.01 m²
    model = skp_reader.read(skp.read_bytes())
    polys = skp_reader.world_polygons(model)
    acc = {}
    for p in polys:
        acc[p.material] = acc.get(p.material, 0.0) + p.area_m2
    acc.pop(None, None)
    names = ex.match_materials(acc, doc["areas"])  # one-to-one; raises on any unmatched area
    assert sorted(names.values()) == sorted(doc["areas"])
    for k, name in names.items():
        assert acc[k] == pytest.approx(doc["areas"][name], abs=ex.AREA_TOL_M2)
    # the reader's total over every face, unpainted included, against the documented S (1.1 × its printed unit)
    assert sum(p.area_m2 for p in polys) == pytest.approx(doc["S"], abs=ex.AREA_TOL_FACTOR * units["S"])
    # the documentation's own consistency: Σ documented areas vs S, to the worst-case rounding n·u/2 + u_S/2
    assert sum(doc["areas"].values()) == pytest.approx(doc["S"], abs=ex.documentation_sum_bound_m2(units))
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


@pytest.mark.parametrize("room", ["CR2", "CR3", "CR4"])
def test_extraction_reproduces_the_committed_geometry(room):
    """The reader regression guard (phase-05f scope (a)): re-extracting a room gives the committed
    tools/validation/data/bras_geometry.json entry (areas, off-plane maximum, reduction inputs,
    reader skip count), compared numerically as make_bras_scenes.py --check does (last-bit float
    differences between CPUs allowed, nothing else)."""
    import json

    from tools.validation import make_bras_scenes as m

    _need(CACHE / room / "geometry" / f"{room}.skp")
    committed = json.loads(ex.OUT.read_text(encoding="utf-8"))["rooms"][room]
    fresh = json.loads(json.dumps(ex.extract_room(room, CACHE, log=lambda *_: None)))
    assert m._max_rel_diff(committed, fresh) <= m.REDUCTION_RTOL


# ---------------------------------------------------------------- phase-05g scope 4: area tolerance (no cache needed)


def test_printed_unit_and_absolute_area_tolerance():
    assert ex._printed_unit("178.90") == 0.01 and ex._printed_unit("2763.0") == 0.1 and ex._printed_unit("8") == 1.0
    assert ex.AREA_TOL_M2 == pytest.approx(0.011)
    doc = {"mat_CR4_concrete": 1773.89, "mat_CR4_windows": 8.50}
    assert ex.match_materials({1: 1773.89 + 0.0105, 2: 8.50 - 0.0105}, doc) == {1: "mat_CR4_concrete", 2: "mat_CR4_windows"}
    with pytest.raises(SystemExit):  # the 05f review's case: a reader bug losing ~1 m^2 of CR4 concrete
        ex.match_materials({1: 1773.89 - 1.0, 2: 8.50}, doc)
    with pytest.raises(SystemExit):  # absolute at any size: 0.012 m^2 fails on the largest area too
        ex.match_materials({1: 1773.89 + 0.012, 2: 8.50}, doc)


def test_documented_units_and_total_checks():
    descr = ("(Room surface/volume S = 2763.0 m² / V = 3330.6 m³ - based on provided 3d models)\n"
             "Surface Areas:\tmat_CR3_floor\t342.53 m²\n\tmat_CR3_seating\t178.90 m²\nCharacteristic depths:\n")
    u = ex.documented_units(descr)
    assert u == {"areas": {"mat_CR3_floor": 0.01, "mat_CR3_seating": 0.01}, "S": 0.1}
    assert ex.documentation_sum_bound_m2(u) == pytest.approx(2 * 0.005 + 0.05)
    ex.check_total_area(2763.0 + 0.10, 2763.0, 0.1)
    with pytest.raises(SystemExit):
        ex.check_total_area(2763.0 + 0.12, 2763.0, 0.1)


# ---------------------------------------------------------------- phase-05g scope 5: declared vs found definitions


def test_definition_trailer_detection_and_count_check():
    pad = b"\x55" * 40
    tr = skp_reader.DEFINITION_TRAILER
    data = pad + tr + b"\x03\x80" + pad + tr + b"\x00\x00" + pad + tr + b"\x07\x80" + pad
    assert [has_png for _, has_png in skp_reader.definition_records(data, 0)] == [True, False]  # 0x8007: not a trailer end


@pytest.mark.parametrize("room,declared,with_png", [("CR2", 1, 1), ("CR3", 19, 17), ("CR4", 19, 17)])
def test_declared_definition_count_matches_the_definition_records(room, declared, with_png):
    """CR3 and CR4 declare 19 definitions: 17 records end with a PNG thumbnail, the group definitions
    'Group#1' and 'Group#2' with an image-less CThumbnail (skp_reader.definition_records). read()
    raises SkpFormatError when the counts differ."""
    skp = CACHE / room / "geometry" / f"{room}.skp"
    _need(skp)
    data = skp.read_bytes()
    model = skp_reader.read(data)
    assert model.definitions == declared == len(model.definition_records)
    assert sum(has_png for _, has_png in model.definition_records) == with_png
    for pos, has_png in model.definition_records:
        if not has_png:  # the image-less records are the group definitions (their name precedes the trailer)
            assert "Group#".encode("utf-16-le") in data[pos - 400 : pos]


def test_count_mismatch_is_an_error(monkeypatch):
    skp = CACHE / "CR3" / "geometry" / "CR3.skp"
    _need(skp)
    real = skp_reader.definition_records
    monkeypatch.setattr(skp_reader, "definition_records", lambda d, s: real(d, s)[:-1])
    with pytest.raises(skp_reader.SkpFormatError, match="19 definitions declared, 18"):
        skp_reader.read(skp.read_bytes())


# ---------------------------------------------------------------- phase-05g scope 6: exact index offsets


@pytest.mark.parametrize("room", ["CR3", "CR4"])
def test_no_under_counted_index_offset_after_a_definition_header(room):
    """Before phase-05g, crossing a definition header could pick an index offset one too small, which
    showed up a few KB later as a 'bad reference' skip (11 in CR3, 11 in CR4 plus one
    'index offset corrected' replay). With the strict extended
    trial (skp_reader._exact_offset) no such skip remains, and a strict (type-checked) parse of the whole
    file meets no type mismatch, i.e. the type rules hold on the real data."""
    skp = CACHE / room / "geometry" / f"{room}.skp"
    _need(skp)
    data = skp.read_bytes()
    model = skp_reader.read(data)
    assert not [s for s in model.skips if s[2].startswith("bad reference")]
    assert len(model.skips) == 34


@pytest.mark.parametrize("room,faces", [("CR2", 258), ("CR3", 47360), ("CR4", 48465)])
def test_strict_parse_meets_no_type_mismatch(monkeypatch, room, faces):
    skp = CACHE / room / "geometry" / f"{room}.skp"
    _need(skp)
    init = skp_reader._Parser.__init__

    def strict_init(self, *a, **k):
        init(self, *a, **k)
        self.strict = True

    monkeypatch.setattr(skp_reader._Parser, "__init__", strict_init)
    model = skp_reader.read(skp.read_bytes())
    assert not [s for s in model.skips if "type mismatch" in s[2]]
    assert len(model.faces) == faces
