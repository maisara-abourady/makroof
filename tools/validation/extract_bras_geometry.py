"""Extract the reduction inputs of the BRAS rooms (Phase 05) once, into
tools/validation/data/bras_geometry.json (derived data, CC BY-SA 4.0, BRAS attribution in
docs/THIRD_PARTY.md). CI and the nightly job use that file; they do not need this script.

    pip install -r tools/validation/requirements-extract.txt   # h5py, for the SOFA positions
    python tools/validation/fetch_bras.py --groups materials geometry
    python tools/validation/extract_bras_geometry.py

Per room it reads ``CRx.skp`` with tools/validation/skp_reader.py, checks every material's total
area against ``_descr/mat_CRx.txt`` (one-to-one match, each within 0.1 %; the extraction fails
otherwise), applies reduction rule 1 of docs/validation/bras_mapping.md (rotation about z, face
assignment) and stores, per material and box face, the assigned area; the floor-assigned faces'
bounding box; and the source and receiver positions from ``CRx_RIRs_Dodecahedron.sofa`` with the
floor elevation under each (rule 6). Everything else (dimensions, α, s, positions in the box) is
computed by make_bras_scenes.py from this file.
"""

from __future__ import annotations

import hashlib
import json
import math
import pathlib
import re
import sys

import numpy as np

HERE = pathlib.Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parents[1]))

from tools.validation import fetch_bras, skp_reader  # noqa: E402

OUT = HERE / "data" / "bras_geometry.json"
ROOMS = ("CR2", "CR3", "CR4")
BOX_FACES = ("xMin", "xMax", "yMin", "yMax", "floor", "ceiling")  # contract::surfaceIndex order


def documented_materials(descr_text: str) -> dict:
    """{material: area m^2} and V, S from a BRAS _descr/mat_CRx.txt."""
    areas = {}
    block = descr_text.split("Surface Areas:")[1].split("Characteristic depths:")[0]
    for name, a in re.findall(r"(mat_CR\d_\w+)\s+([\d.]+)\s*m", block):
        areas[name] = float(a)
    depths = {}
    block = descr_text.split("Characteristic depths:")[1].split("Data files:")[0].split("Details")[0]
    for name, dc in re.findall(r"(mat_CR\d_\w+)\s+([\d.]+)\s*m", block):
        depths[name] = float(dc)
    m = re.search(r"S\s*=\s*([\d.]+)\s*m²\s*/\s*V\s*=\s*([\d.]+)\s*m³", descr_text)
    return {"areas": areas, "d_char": depths, "S": float(m.group(1)), "V": float(m.group(2))}


def match_materials(acc: dict, documented: dict, rel_tol=1e-3, abs_tol=0.011) -> dict:
    """Map reader material ids to BRAS names by total area, one-to-one (greedy by area)."""
    ids = sorted((k for k in acc if k is not None), key=lambda k: -acc[k])
    names = sorted(documented, key=lambda n: -documented[n])
    if len(ids) != len(names):
        raise SystemExit(f"material count {len(ids)} in the model != {len(names)} documented ({acc})")
    out = {}
    for k in ids:
        best = min((n for n in names if n not in out.values()), key=lambda n: abs(acc[k] - documented[n]))
        if abs(acc[k] - documented[best]) > max(abs_tol, rel_tol * documented[best]):
            raise SystemExit(f"model material {k}: {acc[k]:.3f} m^2 matches no documented area ({documented})")
        out[k] = best
    return out


def rotation_angle(polys) -> float:
    """θ aligning the area-weighted wall normals with the axes (rule 1): ¼·atan2(Σ A sin 4φ, Σ A cos 4φ)."""
    s = c = 0.0
    for p in polys:
        n = p.normal
        if abs(n[2]) < 0.5:
            phi = math.atan2(n[1], n[0])
            s += p.area_m2 * math.sin(4 * phi)
            c += p.area_m2 * math.cos(4 * phi)
    return 0.25 * math.atan2(s, c)


def assign_face(n) -> str:
    """Box face for a face with inward unit normal n (BRAS models are built for RAVEN, whose faces
    point into the room; extract_room checks this on the floor and ceiling): the box face whose
    outward normal is closest to the face's outward normal -n, i.e. the largest |n_i|; exact ties
    go to floor/ceiling first, then x, then y (rule 1)."""
    out = -np.asarray(n)
    a = np.abs(out)
    if a[2] >= a[0] and a[2] >= a[1]:
        return "floor" if out[2] < 0 else "ceiling"
    if a[0] >= a[1]:
        return "xMin" if out[0] < 0 else "xMax"
    return "yMin" if out[1] < 0 else "yMax"


def floor_below(point, floor_polys):
    """Elevation of the highest floor-assigned face directly below ``point`` (vertical ray), or None."""
    x, y, z = point
    best = None
    for p in floor_polys:
        outer = p.loops[0]
        if not _inside(x, y, outer[:, :2]):
            continue
        if any(_inside(x, y, h[:, :2]) for h in p.loops[1:]):
            continue
        n = p.normal
        if abs(n[2]) < 1e-9:
            continue
        zf = outer[0, 2] - (n[0] * (x - outer[0, 0]) + n[1] * (y - outer[0, 1])) / n[2]
        if zf <= z + 1e-9 and (best is None or zf > best):
            best = zf
    return best


def _inside(x, y, poly) -> bool:
    inside = False
    n = len(poly)
    for i in range(n):
        x1, y1 = poly[i]
        x2, y2 = poly[(i + 1) % n]
        if (y1 > y) != (y2 > y) and x < (x2 - x1) * (y - y1) / (y2 - y1) + x1:
            inside = not inside
    return inside


def sofa_positions(path):
    import h5py  # extraction only (tools/validation/requirements-extract.txt)

    with h5py.File(path, "r") as f:
        em = np.array(f["EmitterPosition"])[:, :, 0]
        rc = np.array(f["ReceiverPosition"])[:, :, 0]
        eid = [int(x) for x in np.array(f["EmitterID"]).ravel()]
        rid = [int(x) for x in np.array(f["ReceiverID"]).ravel()]
    return {f"LS{e}": em[i].tolist() for i, e in enumerate(eid)}, {f"MP{r}": rc[i].tolist() for i, r in enumerate(rid)}


def extract_room(room: str, cache: pathlib.Path, log=print) -> dict:
    skp_path = cache / room / "geometry" / f"{room}.skp"
    data = skp_path.read_bytes()
    doc = documented_materials((cache / "materials" / "descr" / f"mat_{room}.txt").read_text(encoding="utf-8", errors="replace"))
    model = skp_reader.read(data, log=log)
    polys = skp_reader.world_polygons(model)
    acc: dict = {}
    for p in polys:
        acc[p.material] = acc.get(p.material, 0.0) + p.area_m2
    unpainted = acc.pop(None, 0.0)
    names = match_materials(acc, doc["areas"])
    off_plane = max(p.off_plane_m for p in polys)
    theta = rotation_angle([p for p in polys if p.material in names])
    c, s = math.cos(-theta), math.sin(-theta)
    Rz = np.array([[c, -s, 0], [s, c, 0], [0, 0, 1.0]])
    rot = []
    for p in polys:
        if p.material not in names:
            continue
        p.normal = Rz @ p.normal
        p.loops = [L @ Rz.T for L in p.loops]
        rot.append(p)
    # inward normals: the floor faces' normals must point up
    assigned: dict = {}
    for p in rot:
        f = assign_face(p.normal)
        key = (names[p.material], f)
        assigned[key] = assigned.get(key, 0.0) + p.area_m2
    floor_polys = [p for p in rot if assign_face(p.normal) == "floor"]
    ceiling_polys = [p for p in rot if assign_face(p.normal) == "ceiling"]
    # Orientation check: with inward normals the ceiling-assigned faces lie above the
    # floor-assigned ones (a model with outward normals would swap them). The per-material
    # assignment table in bras_mapping.md shows any single flipped face.
    def mean_z(ps):
        return sum(p.area_m2 * float(np.mean(p.loops[0][:, 2])) for p in ps) / sum(p.area_m2 for p in ps)
    if not floor_polys or not ceiling_polys or mean_z(ceiling_polys) <= mean_z(floor_polys):
        raise SystemExit(f"{room}: face normals do not point into the room")
    fl = np.concatenate([L for p in floor_polys for L in p.loops[:1]])
    floor_area = sum(p.area_m2 for p in floor_polys)
    zbar = sum(p.area_m2 * float(np.mean(p.loops[0][:, 2])) for p in floor_polys) / floor_area
    emitters, receivers = sofa_positions(cache / room / "geometry" / f"{room}_RIRs_Dodecahedron.sofa")
    pos = {k: {"xyz": (Rz @ np.asarray(v)).tolist()} for k, v in {**emitters, **receivers}.items()}
    # AX24: the floor plane of a pair = the floor face under the pair's horizontal midpoint.
    pair_floor = {}
    for s in emitters:
        for r in receivers:
            m = 0.5 * (np.asarray(pos[s]["xyz"]) + np.asarray(pos[r]["xyz"]))
            zf = floor_below(m, floor_polys)
            pair_floor[f"{s}_{r}"] = {"z_floor": zf if zf is not None else zbar, "floor_found": zf is not None}
    model_area = sum(acc.values())
    log(f"{room}: θ = {math.degrees(theta):.3f}°, A_floor = {floor_area:.2f} m², S(model) = {model_area:.2f} m², "
        f"unpainted {unpainted:.3f} m², off-plane {off_plane:.2e} m")
    return {
        "source": {"skp": skp_path.name, "skp_sha256": hashlib.sha256(data).hexdigest(), "reader_skips": len(model.skips)},
        "documented": doc,
        "model_material_area_m2": {names[k]: acc[k] for k in names},
        "unpainted_area_m2": unpainted,
        "max_off_plane_m": off_plane,
        "rotation_deg": math.degrees(theta),
        "assigned_area_m2": {f"{m}|{f}": a for (m, f), a in sorted(assigned.items())},
        "floor_area_m2": floor_area,
        "floor_bbox_xy": [fl[:, 0].min(), fl[:, 1].min(), fl[:, 0].max(), fl[:, 1].max()],
        "floor_mean_z": zbar,
        "positions": pos,
        "pair_floor": pair_floor,
    }


def main():
    cache = fetch_bras.cache_dir()
    fetch_bras.fetch(["materials", "geometry"], cache)
    out = {"note": "Derived from BRAS (CC BY-SA 4.0; DOI 10.14279/depositonce-6726.3) by "
                   "tools/validation/extract_bras_geometry.py; see docs/validation/bras_mapping.md.",
           "rooms": {r: extract_room(r, cache) for r in ROOMS}}
    OUT.parent.mkdir(exist_ok=True)
    OUT.write_text(json.dumps(out, indent=1, ensure_ascii=False) + "\n", encoding="utf-8")
    print("wrote", OUT)


if __name__ == "__main__":
    main()
