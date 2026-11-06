"""Minimal reader for the geometry in SketchUp 2015 (.skp, classic MFC CArchive) files: faces
(plane, outer and inner loops), their materials, and groups / component instances with their
transforms. Written for the BRAS scene models (Phase 05); no third-party code (Maisara's
decision, 2026-11-06). The format is proprietary and undocumented, so this reader was built
from the files themselves and is validated by what it reproduces, not by a specification:

- the per-material surface areas documented in BRAS ``_descr/mat_CRx.txt`` (every material, to
  the 0.01 m^2 printed there; tests/test_skp_reader.py and extract_bras_geometry.py check this);
- every loop vertex lies on its face's plane (n.p + d = 0);
- the object-index bookkeeping: every back-reference must resolve.

Stream format (as far as needed here). Objects are written MFC-style: ``ff ff <schema u16>
<len u16> <name>`` defines a class (it takes the next index) and is followed by an object of
it; ``<class index | 0x8000>`` starts a new object of a known class; a plain u16 < 0x7fff is a
back-reference to an object; ``ff 7f`` + u32 is the 32-bit form (bit 31 set: class tag).
Every new object takes the next index. Strings: ``ff fe ff`` + u8 length (``ff`` + u16 when
longer) + UTF-16LE. Coordinates are in inches.

Classes read (layouts as found):
- CVertex: u16, position (3 doubles).
- CEdge: entity header, start vertex, end vertex, curve.
- CCurve: 3 bytes, u32 edge count. CArcCurve: the same + 14 doubles.
- CEdgeUse: u16, edge, u8 reversed, loop, next edge-use (a linked list; null or a repeat ends it).
- CLoop: u16, u16, first edge-use.
- CFace: entity header, plane (normal, d: n.p + d = 0), u32 loop count, loops (first = outer).
- Entity header: attribute container (null or object), material (null or back-reference),
  8 flag bytes.
- CAttributeContainer: u16, references until null (named dictionaries, texture coordinates).
- CAttributeNamed: u16, u32, name, (key, u8 type, value) until an empty key, u32 child count,
  children. Value types 0x0a string, 0x06 double, 0x07 u8, 0x04 u32.
- CFaceTextureCoords: 214 bytes.
- CGroup, CComponentInstance: entity header, definition, transform (x axis, y axis, z axis,
  origin, w: 13 doubles), name, 16-byte GUID.
- CComponentDefinition: the entity header is read; the rest of its record (behaviour fields,
  then its entity lists, then GUID, name, description, CThumbnail with a PNG) is crossed by
  re-synchronisation (below), which also finds where the next definition or the root starts.

Re-synchronisation: where a record is not understood, the reader searches the next 64 KB, then
tries the positions just after the next thumbnail PNG (the end of the current definition record),
then searches forward for the next
position at which a new object of a geometry class (or a class definition) starts and the next
60 references parse with every back-reference resolving, trying index offsets 0-63 for objects
created in the skipped bytes. Skips are logged; any back-reference that fails after a skip would
show up as a failed parse, and the area checks catch silently wrong geometry.
"""

from __future__ import annotations

import re
import struct
import sys
from dataclasses import dataclass, field

import numpy as np

INCH = 0.0254
GEOMETRY_CLASSES = ("CEdge", "CFace", "CGroup", "CComponentInstance", "CComponentDefinition")


class SkpFormatError(Exception):
    pass


class _Stop(Exception):
    pass


class _Parser:
    def __init__(self, data: bytes, pos: int, base: int, classes: dict, objs: dict):
        self.d = data
        self.pos = pos
        self.idx = base
        self.cls = classes
        self.objs = objs
        self.cur_def = None
        self.root = False

    # primitives
    def u8(self):
        v = self.d[self.pos]
        self.pos += 1
        return v

    def u16(self):
        v = struct.unpack_from("<H", self.d, self.pos)[0]
        self.pos += 2
        return v

    def u32(self):
        v = struct.unpack_from("<I", self.d, self.pos)[0]
        self.pos += 4
        return v

    def f64(self):
        v = struct.unpack_from("<d", self.d, self.pos)[0]
        self.pos += 8
        return v

    def string(self):
        if self.d[self.pos : self.pos + 3] != b"\xff\xfe\xff":
            raise _Stop(f"not a string at {self.pos}")
        self.pos += 3
        n = self.u8()
        if n == 0xFF:
            n = self.u16()
        v = self.d[self.pos : self.pos + 2 * n].decode("utf-16-le")
        self.pos += 2 * n
        return v

    def ref(self):
        start = self.pos
        t = self.u16()
        if t == 0:
            return None
        if t == 0xFFFF:
            schema = self.u16()
            n = self.u16()
            name = self.d[self.pos : self.pos + n].decode("ascii")
            self.pos += n
            self.idx += 1
            self.cls[self.idx] = name
            ci = self.idx
        elif t == 0x7FFF:
            v = self.u32()
            if v & 0x80000000:
                ci = v & 0x7FFFFFFF
                if ci not in self.cls:
                    raise _Stop(f"unknown class {ci:#x} at {start}")
            else:
                if v not in self.objs:
                    raise _Stop(f"bad reference {v:#x} at {start}")
                return self.objs[v]
        elif t & 0x8000:
            ci = t & 0x7FFF
            if ci not in self.cls:
                raise _Stop(f"unknown class {ci:#x} at {start}")
        else:
            if t not in self.objs:
                raise _Stop(f"bad reference {t:#x} at {start}")
            return self.objs[t]
        name = self.cls[ci]
        self.idx += 1
        o = {"_c": name, "_i": self.idx, "_owner": "root" if self.root else self.cur_def}
        self.objs[self.idx] = o
        handler = _HANDLERS.get(name)
        if handler is None:
            raise _Stop(f"no reader for {name} at {start}")
        handler(self, o)
        return o


def _entity(p, o):
    o["attr"] = p.ref()
    o["mat"] = p.ref()
    p.pos += 8


def _vertex(p, o):
    p.u16()
    o["p"] = (p.f64(), p.f64(), p.f64())


def _edge(p, o):
    _entity(p, o)
    o["v0"] = p.ref()
    o["v1"] = p.ref()
    p.ref()  # curve


def _curve(p, o):
    p.pos += 3
    p.u32()


def _arc(p, o):
    _curve(p, o)
    p.pos += 14 * 8


def _edgeuse(p, o):
    p.u16()
    o["edge"] = p.ref()
    o["rev"] = p.u8()
    p.ref()  # loop
    o["next"] = p.ref()


def _loop(p, o):
    p.u16()
    p.u16()
    o["first"] = p.ref()


def _face(p, o):
    _entity(p, o)
    o["n"] = (p.f64(), p.f64(), p.f64())
    o["d"] = p.f64()
    k = p.u32()
    if k > 10000:
        raise _Stop(f"implausible loop count at {p.pos}")
    o["loops"] = [p.ref() for _ in range(k)]


def _attr_container(p, o):
    p.u16()
    while p.ref() is not None:
        pass


_VALUE = {0x0A: lambda p: p.string(), 0x06: lambda p: p.f64(), 0x07: lambda p: p.u8(), 0x04: lambda p: p.u32()}


def _named(p, o):
    p.u16()
    p.u32()
    o["name"] = p.string()
    kv = {}
    while True:
        k = p.string()
        if k == "":
            break
        t = p.u8()
        if t not in _VALUE:
            raise _Stop(f"unknown attribute type {t:#x} at {p.pos}")
        kv[k] = _VALUE[t](p)
    o["kv"] = kv
    for _ in range(p.u32()):
        p.ref()


def _texcoords(p, o):
    p.pos += 214


def _instance(p, o):
    _entity(p, o)
    o["def"] = p.ref()
    o["xf"] = [p.f64() for _ in range(13)]
    o["name"] = p.string()
    p.pos += 16


def _definition(p, o):
    p.cur_def = o["_i"]
    p.defs_seen += 1
    _entity(p, o)
    raise _Stop("definition body")  # crossed by re-synchronisation


_HANDLERS = {
    "CVertex": _vertex, "CEdge": _edge, "CCurve": _curve, "CArcCurve": _arc, "CEdgeUse": _edgeuse,
    "CLoop": _loop, "CFace": _face, "CAttributeContainer": _attr_container, "CAttributeNamed": _named,
    "CFaceTextureCoords": _texcoords, "CGroup": _instance, "CComponentInstance": _instance,
    "CComponentDefinition": _definition,
}


@dataclass
class Model:
    faces: list = field(default_factory=list)       # dicts with owner, n, d, loops, mat
    instances: list = field(default_factory=list)   # dicts with owner, def, xf, mat
    material_refs: set = field(default_factory=set)
    skips: list = field(default_factory=list)
    definitions: int = 0


def _class_definitions(d: bytes):
    return [(m.start(), m.group(3).decode()) for m in re.finditer(rb"\xff\xff(..)(..)(C[A-Za-z]+)", d, re.S)
            if int.from_bytes(m.group(2), "little") == len(m.group(3))]


def read(data: bytes, log=None) -> Model:
    defs = _class_definitions(data)
    # The definition count (u32) precedes the CComponentDefinition class (if any).
    cdef = next((pos for pos, name in defs if name == "CComponentDefinition"), None)
    first_geom = next(pos for pos, name in defs if name in ("CEdge", "CFace", "CVertex"))
    n_defs = struct.unpack_from("<I", data, cdef - 4)[0] if cdef is not None and cdef < first_geom else 0
    # Parsing starts at the first geometry class definition. Objects before it (materials,
    # layers, the first definition record) are opaque; their count is calibrated. Classes
    # defined before it: CAttributeContainer = 5 and CAttributeNamed = 7 in every BRAS file
    # (CVersionMap 1, CDib 3), CComponentDefinition when there are definitions.
    base = _calibrate(data, first_geom)
    classes = {5: "CAttributeContainer", 7: "CAttributeNamed"}
    p = _Parser(data, first_geom, base, classes, {i: {"_c": "pre", "_i": i} for i in range(1, base + 1)})
    if n_defs:
        # the class index of CComponentDefinition: the tag that starts the second definition
        # (searched below); until then the geometry belongs to the first definition, "def0".
        p.cur_def = "def0"
        p.defs_seen = 1
        cls_idx = _definition_class_index(data, first_geom, base)
        if cls_idx is not None:
            classes[cls_idx] = "CComponentDefinition"
    else:
        p.defs_seen = 0
        p.root = True
    model = Model(definitions=n_defs)
    while p.pos < len(data) - 2:
        try:
            p.ref()
        except (_Stop, struct.error, UnicodeDecodeError, IndexError) as e:
            fail = p.pos
            found = _resync(p, data)
            model.skips.append((fail, found, str(e)))
            if found is None:
                break
            q, delta = found
            # After the last definition's thumbnail (a PNG) the root entities start.
            if not p.root and p.defs_seen >= n_defs and data.find(b"IEND\xaeB`\x82", fail, q) >= 0:
                p.root = True
            p.pos = q
            p.idx += delta
    # The first definition's object is in the opaque region: the one pre-region object that
    # instances reference as a definition.
    pre_defs = {i["def"]["_i"] for i in (o for o in p.objs.values() if o["_c"] in ("CGroup", "CComponentInstance"))
                if i["def"] is not None and i["def"].get("_c") == "pre"}
    if len(pre_defs) > 1:
        raise SkpFormatError(f"several definitions in the opaque region: {sorted(pre_defs)}")
    for i in pre_defs:
        p.objs[i]["_i"] = "def0"
    for o in p.objs.values():
        if o["_c"] == "CFace":
            model.faces.append(o)
        elif o["_c"] in ("CGroup", "CComponentInstance"):
            model.instances.append(o)
    if log:
        log(f"skp: {len(model.faces)} faces, {len(model.instances)} instances, {n_defs} definitions, {len(model.skips)} skips")
    return model


def _definition_class_index(data, first_geom, base):
    """Class index of CComponentDefinition: definitions after the first start right after the
    previous definition's thumbnail PNG (IEND chunk + CRC) with a new object of that class."""
    i = data.find(b"IEND\xaeB`\x82", first_geom)
    while i >= 0:
        t = struct.unpack_from("<H", data, i + 8)[0]
        if t & 0x8000 and t != 0xFFFF:
            return t & 0x7FFF
        i = data.find(b"IEND\xaeB`\x82", i + 8)
    return None


def _trial(p, data, pos, idx, k=60):
    q = _Parser(data, pos, idx, p.cls, dict(p.objs))
    q.defs_seen = p.defs_seen
    got = 0
    try:
        for _ in range(k):
            if q.pos >= len(data) - 2:
                break
            o = q.ref()
            got += o is not None and o.get("_i", 0) > idx
    except _Stop as e:
        return "definition body" in str(e)
    except Exception:
        return False
    return got >= 10


def _resync(p, data):
    # Fast path: a record this reader does not understand is usually inside a definition, whose
    # record ends with its thumbnail PNG; try the positions just after the next IEND chunk first.
    # Faces skipped this way would break the per-material area check (extract_bras_geometry.py).
    found = _scan(p, data, p.pos, min(len(data) - 12, p.pos + 65536))
    if found is not None:
        return found
    end = data.find(b"IEND\xaeB`\x82", p.pos)
    if end >= 0:
        found = _scan(p, data, end + 8, min(len(data) - 12, end + 8 + 4096))
        if found is not None:
            return found
    return _scan(p, data, p.pos, len(data) - 12)


def _scan(p, data, q, stop):
    n = len(data)
    while q < stop:
        t = struct.unpack_from("<H", data, q)[0]
        ok = False
        if t == 0xFFFF:
            ok = data[q + 6 : q + 7] == b"C" and data[q + 2] < 0x20
        elif t == 0x7FFF:
            v = struct.unpack_from("<I", data, q + 2)[0]
            ok = bool(v & 0x80000000) and p.cls.get(v & 0x7FFFFFFF) in GEOMETRY_CLASSES
        elif t & 0x8000:
            name = p.cls.get(t & 0x7FFF)
            if name == "CComponentDefinition":
                ok = data[q - 8 : q] == b"IEND\xaeB`\x82"  # definitions follow the previous thumbnail
            else:
                ok = name in GEOMETRY_CLASSES and (data[q + 7 : q + 9] == b"\x01\x01" or data[q + 2 : q + 4] == b"\x05\x80")
        if ok:
            for delta in range(0, 64):
                if _trial(p, data, q, p.idx + delta):
                    return q, delta
        q += 1
    return None


def _calibrate(data, start):
    for base in range(8, 4000):
        p = _Parser(data, start, base, {5: "CAttributeContainer", 7: "CAttributeNamed"},
                    {i: {"_c": "pre", "_i": i} for i in range(1, base + 1)})
        p.defs_seen = 0
        got = 0
        try:
            for _ in range(300):
                o = p.ref()
                got += o is not None and o.get("_i", 0) > base
        except Exception:
            continue
        if got >= 50:
            return base
    raise SkpFormatError("could not calibrate the object index base")


# ------------------------------------------------------------------------------------------
# Geometry
# ------------------------------------------------------------------------------------------


def _loop_points(loop):
    pts = []
    eu = loop["first"]
    seen = set()
    while eu is not None and id(eu) not in seen:
        seen.add(id(eu))
        e = eu["edge"]
        v = e["v1"] if eu["rev"] else e["v0"]
        pts.append(v["p"])
        eu = eu["next"]
    return np.array(pts, float)


def _xf_matrix(xf):
    """4x4 from SketchUp's 13 numbers: x axis, y axis, z axis, origin, w (p' = (o + Σ p_i a_i) / w)."""
    m = np.eye(4)
    m[:3, 0], m[:3, 1], m[:3, 2], m[:3, 3] = xf[0:3], xf[3:6], xf[6:9], xf[9:12]
    return m / xf[12]


@dataclass
class Polygon:
    material: int | None  # material object index (opaque), None = unpainted
    normal: np.ndarray     # unit, world frame
    area_m2: float
    loops: list            # world-frame vertex arrays (m), first = outer
    off_plane_m: float


def world_polygons(model: Model) -> list[Polygon]:
    """Every face of the root, and of every definition placed (recursively) by a root group or
    instance, in the world frame (metres). A face without a material takes the material of the
    innermost painted instance above it (SketchUp's inheritance)."""
    by_owner: dict = {}
    for f in model.faces:
        by_owner.setdefault(f["_owner"], []).append(f)
    inst_by_owner: dict = {}
    for i in model.instances:
        inst_by_owner.setdefault(i["_owner"], []).append(i)
    out: list[Polygon] = []

    def mat_of(o):
        m = o["mat"]
        return m["_i"] if m is not None and m.get("_c") == "pre" else None

    def emit(owner, M, inherited, depth):
        owner = "def0" if owner == "def0" else owner
        if depth > 32:
            raise SkpFormatError("instance nesting too deep")
        for f in by_owner.get(owner, []):
            n = np.array(f["n"])
            R = M[:3, :3]
            nw = np.linalg.inv(R).T @ n
            nw /= np.linalg.norm(nw)
            loops, area, off = [], 0.0, 0.0
            for k, lp in enumerate(f["loops"]):
                P = _loop_points(lp)
                off = max(off, float(np.max(np.abs(P @ n + f["d"])) * INCH)) if len(P) else off
                Pw = (P @ R.T + M[:3, 3]) * INCH
                loops.append(Pw)
                a = 0.5 * abs(float(np.dot(np.cross(Pw, np.roll(Pw, -1, 0)).sum(0), nw)))
                area += a if k == 0 else -a
            m = mat_of(f)
            out.append(Polygon(m if m is not None else inherited, nw, area, loops, off))
        for inst in inst_by_owner.get(owner, []):
            d = inst["def"]
            if d is None:
                continue
            m = mat_of(inst)
            emit(d["_i"], M @ _xf_matrix(inst["xf"]), m if m is not None else inherited, depth + 1)

    emit("root", np.eye(4), None, 0)
    return out


if __name__ == "__main__":
    import collections
    data = open(sys.argv[1], "rb").read()
    model = read(data, log=print)
    for s in model.skips[:20]:
        print("skip", s)
    polys = world_polygons(model)
    acc = collections.defaultdict(float)
    for pg in polys:
        acc[pg.material] += pg.area_m2
    print("max off-plane (m):", max(pg.off_plane_m for pg in polys))
    for m, a in sorted(acc.items(), key=lambda t: -t[1]):
        print(m, round(a, 3))
