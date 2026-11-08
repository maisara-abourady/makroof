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
- CFaceTextureCoords: 6 bytes, 24 doubles, u32 n, n x 4 doubles, 12 bytes (214 + 32 n).
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
show up as a failed parse, and the area checks catch silently wrong geometry. When several offsets
pass that trial, the offset taken is the one that parses furthest under a strict, type-checked
extended trial (an edge's ends must be vertices, an edge-use's edge an edge, a loop's first element
an edge-use, a face's loops loops; _exact_offset, Phase 05g scope 6): the 60-reference trial alone
could accept an offset one too small, which showed up kilobytes later as a 'bad reference' skip
(11 in CR3; 11 in CR4, plus one 'index offset corrected' replay; all gone: reader_skips 45 -> 34
and 46 -> 34, geometry identical). A strict parse of the whole of CR2, CR3 and CR4 meets no type mismatch.

Definition count (Phase 05g scope 5). The u32 before the CComponentDefinition class declares the
number of definitions; read() checks it against the definition records found
(definition_records: every record ends with the same CThumbnail field tail, followed by a CDib with
a PNG or by a null reference). CR2 declares 1 (1 record, with a PNG); CR3 and CR4 declare 19: 17
records end with a PNG thumbnail and two, the group definitions 'Group#1' and 'Group#2' (a SketchUp
group is an instance of a definition of its own and is counted in the model's definition list),
with an image-less thumbnail. Counting PNGs alone (Phase 05f) therefore found 17.
"""

from __future__ import annotations

import collections
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
        self.root_start = None  # file position where the root entities begin
        self.strict = False  # type-check back-references (re-synchronisation trials only; see _typed)

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
        is_root = self.root or (self.root_start is not None and start >= self.root_start)
        o = {"_c": name, "_i": self.idx, "_owner": "root" if is_root else self.cur_def}
        self.objs[self.idx] = o
        handler = _HANDLERS.get(name)
        if handler is None:
            raise _Stop(f"no reader for {name} at {start}")
        handler(self, o)
        return o


_OPAQUE = ("skipped", "pre")


def _typed(p, o, *classes):
    """In a strict (trial) parse, a reference must name an object of one of ``classes`` (or an opaque
    one, whose class is unknown). Under a wrong index offset a back-reference resolves to a neighbouring
    object of another class; this is what tells offsets apart (Phase 05g, scope 6)."""
    if p.strict and o is not None and o["_c"] not in classes and o["_c"] not in _OPAQUE:
        raise _Stop(f"type mismatch: {o['_c']} where {'/'.join(classes)} expected at {p.pos}")
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
    o["v0"] = _typed(p, p.ref(), "CVertex")
    o["v1"] = _typed(p, p.ref(), "CVertex")
    _typed(p, p.ref(), "CCurve", "CArcCurve")  # curve


def _curve(p, o):
    p.pos += 3
    p.u32()


def _arc(p, o):
    _curve(p, o)
    p.pos += 14 * 8


def _edgeuse(p, o):
    p.u16()
    o["edge"] = _typed(p, p.ref(), "CEdge")
    o["rev"] = p.u8()
    _typed(p, p.ref(), "CLoop")  # loop
    o["next"] = _typed(p, p.ref(), "CEdgeUse")


def _loop(p, o):
    p.u16()
    p.u16()
    o["first"] = _typed(p, p.ref(), "CEdgeUse")


def _face(p, o):
    _entity(p, o)
    o["n"] = (p.f64(), p.f64(), p.f64())
    o["d"] = p.f64()
    k = p.u32()
    if k > 10000:
        raise _Stop(f"implausible loop count at {p.pos}")
    o["loops"] = [_typed(p, p.ref(), "CLoop") for _ in range(k)]


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
    # 6 bytes, 24 doubles, u32 n, n x 4 doubles, 12 bytes: 214 + 32 n bytes. n = 0 in CR2/CR3;
    # CR4's textured faces have n = 0 (1 548 records) or 4 (220) (Phase 05f; checked on every
    # record: each ends where its attribute container's null terminator follows).
    p.pos += 198
    n = p.u32()
    if n > 64:
        raise _Stop(f"implausible texture-coordinate count {n} at {p.pos - 4}")
    p.pos += 32 * n + 12


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
    definitions: int = 0  # declared (the u32 before the CComponentDefinition class)
    definition_records: list = field(default_factory=list)  # (trailer position, has a PNG thumbnail)


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
    # Every definition record ends with its thumbnail PNG, and every definition after the first
    # starts right after the previous one's thumbnail with a new object of CComponentDefinition;
    # the root entities start after the thumbnail of the last definition, i.e. after the first
    # PNG end (IEND chunk + CRC) behind the last PNG that is followed by a definition tag. Only
    # PNGs after the first geometry class count: the ones before it are the model preview and
    # material textures (CR4 has a textured material). Phase 05f: the former rule (the n_defs-th
    # PNG of the whole file) counted those and put CR4's root at the start of its last definition
    # and CR2's at its preview image.
    iends = [m.start() + 8 for m in re.finditer(rb"IEND\xaeB`\x82", data) if m.start() > first_geom]
    if n_defs:
        tag = struct.pack("<H", 0x8000 | cls_idx) if cls_idx is not None else None
        tagged = [k for k, e in enumerate(iends) if tag is not None and data[e : e + 2] == tag]
        k = tagged[-1] + 1 if tagged else 0
        if k >= len(iends):
            raise SkpFormatError(f"{n_defs} definitions: no thumbnail ends the last one")
        p.root_start = iends[k]
    records = definition_records(data, first_geom, p.root_start)
    if len(records) != n_defs:
        raise SkpFormatError(f"{n_defs} definitions declared, {len(records)} definition records found "
                             f"(thumbnail trailers after the first geometry class)")
    model = Model(definitions=n_defs, definition_records=records)
    next_report = 1 << 20
    last = None  # state at the last re-synchronisation, for the index-offset correction below
    while p.pos < len(data) - 2:
        if log and p.pos >= next_report:  # progress (Phase 05e: long runs must show how far they got)
            log(f"skp: {p.pos / 1e6:.1f} / {len(data) / 1e6:.1f} MB, {len(model.skips)} skips")
            next_report = p.pos + (1 << 20)
        try:
            p.ref()
        except (_Stop, struct.error, UnicodeDecodeError, IndexError) as e:
            k = _offset_correction(p, last, e)
            if k:
                # A class's index is the object index of its definition. A tag naming an unknown
                # class just above the class defined after the last re-synchronisation means that
                # re-synchronisation under-counted the objects in the skipped bytes by k (nothing
                # in its trial window referenced them): replay from there with delta + k, once.
                q, delta, idx0, state = last
                for i in [i for i in p.objs if isinstance(i, int) and i > idx0]:
                    del p.objs[i]
                for i in [i for i in p.cls if i > idx0]:
                    del p.cls[i]
                p.cur_def, p.defs_seen, p.root = state
                _opaque(p.objs, idx0 + 1, idx0 + delta + k)
                p.pos, p.idx = q, idx0 + delta + k
                model.skips.append((q, (q, delta + k), f"index offset corrected by {k} ({e})"))
                last = None
                continue
            fail = p.pos
            found = _resync(p, data)
            model.skips.append((fail, found, str(e)))
            if found is None:
                break
            q, delta = found
            last = (q, delta, p.idx, (p.cur_def, p.defs_seen, p.root))
            _opaque(p.objs, p.idx + 1, p.idx + delta)
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
            if not all(k in o for k in ("n", "d", "loops")):
                # a face record cut off by a parse stop (registered before its fields were read):
                # no geometry, so it is left out and logged; the per-material area check of
                # extract_bras_geometry.py shows whether anything that matters is missing (Phase 05e, CR4)
                model.skips.append((None, None, f"incomplete face record {o['_i']}"))
                continue
            model.faces.append(o)
        elif o["_c"] in ("CGroup", "CComponentInstance"):
            model.instances.append(o)
    if log:
        log(f"skp: {len(model.faces)} faces, {len(model.instances)} instances, {n_defs} definitions, {len(model.skips)} skips")
    return model


# The fixed tail of a definition record's CThumbnail fields: u16 1, an empty string, two doubles 0.0 and
# 1.0, two doubles 0.0 (39 bytes). It is followed by the thumbnail image, a new CDib object (class 3, as
# in every BRAS file: tag 0x8003) whose PNG ends the record, or by a null reference (no image: the
# record ends there and the next definition, or the root, follows). Found on every definition of CR2,
# CR3 and CR4 (Phase 05g scope 5): 1 / 17 / 17 with a PNG, 0 / 2 / 2 without. CDib = class 3 is the same
# calibration assumption as in read() (CVersionMap 1, CDib 3 in every BRAS file); a file where it differs
# fails the count check loudly (to re-check for any new dataset, e.g. phase-05d).
DEFINITION_TRAILER = b"\x01\x00\xff\xfe\xff\x00" + bytes(15) + b"\xf0\x3f" + bytes(16)
_CDIB_TAG = b"\x03\x80"


def definition_records(data: bytes, start: int, end: int | None = None) -> list:
    """(position, has PNG) of every definition-record trailer in [start, end) (see DEFINITION_TRAILER).
    read() passes the root start as ``end``: the definitions precede the root entities, and a byte
    match inside the root must not offset a missed record in the count.

    The consistency check of read(): their count equals the declared definition count. In CR3 and CR4,
    which declare 19, 17 records end with a PNG thumbnail; the other two are the group definitions
    'Group#1' and 'Group#2' (a SketchUp group is an instance of a definition of its own, counted in the
    model's definition list), whose CThumbnail has no image. The former PNG count therefore saw 17.
    The root-start rule (read) only needs the PNG-ended records: in all three files the last
    definition record before the root has a PNG."""
    out = []
    end = len(data) if end is None else end
    i = data.find(DEFINITION_TRAILER, start, end)
    while i >= 0:
        nxt = data[i + len(DEFINITION_TRAILER) : i + len(DEFINITION_TRAILER) + 2]
        if nxt == _CDIB_TAG:
            out.append((i, True))
        elif nxt == b"\x00\x00":
            out.append((i, False))
        i = data.find(DEFINITION_TRAILER, i + 1, end)
    return out


def _offset_correction(p, last, err) -> int:
    """k > 0 if ``err`` is an unknown class tag ci with ci - c in 1..63, c the newest class index
    defined since the last re-synchronisation (see read); else 0."""
    if last is None or not str(err).startswith("unknown class "):
        return 0
    try:
        ci = int(str(err).split()[2], 16)
    except (IndexError, ValueError):
        return 0
    newer = [c for c in p.cls if c > last[2] + last[1]]
    if not newer:
        return 0
    k = ci - max(newer)
    return k if 0 < k < 64 else 0


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


def _opaque(objs, first, last):
    """Objects created in skipped bytes: references to them resolve, their content is unknown."""
    for i in range(first, last + 1):
        objs.setdefault(i, {"_c": "skipped", "_i": i})


def _trial(p, data, pos, idx, k=60):
    # Copy-on-write view of the object table: a trial's writes go to its own layer and reads fall
    # through to p.objs (same semantics as the former shallow copy dict(p.objs), whose O(N) cost per
    # trial, up to 64 trials per candidate position, made re-synchronisation quadratic in the model
    # size; Phase 05e, CR4).
    objs = collections.ChainMap({}, p.objs)
    _opaque(objs, p.idx + 1, idx)
    q = _Parser(data, pos, idx, p.cls, objs)
    q.defs_seen = p.defs_seen
    q.root_start = p.root_start
    q.cur_def = p.cur_def
    got = 0
    try:
        for _ in range(k):
            if q.pos >= len(data) - 2:
                break
            o = q.ref()
            got += o is not None and o.get("_i", 0) > idx
    except _Stop as e:
        # a record this reader has no layout for is not a desync: accept the position when
        # enough objects parsed before it (bad references and unknown class tags reject it)
        # (a desynchronised parse practically never yields 20 consistent new objects, so a stop
        # after that many is the end of the record: a definition trailer, say)
        return "definition body" in str(e) or ("no reader" in str(e) and got >= 10) or got >= 20
    except Exception:
        return got >= 20
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
            passing = [delta for delta in range(0, 64) if _trial(p, data, q, p.idx + delta)]
            if passing:
                return q, _exact_offset(p, data, q, passing)
        q += 1
    return None


# Objects an extended trial parses at most (Phase 05g scope 6): enough to cross the next few
# kilobytes, where an under-counted offset used to show up as a 'bad reference' skip.
EXTENDED_TRIAL_OBJECTS = 2000


def _reach(p, data, pos, idx, k=EXTENDED_TRIAL_OBJECTS):
    """How many new objects a strict parse from ``pos`` with index base ``idx`` creates before its first
    reference error (an unresolved back-reference, an unknown class tag or a reference of the wrong
    class); ``k`` if none within ``k`` objects. Other stops (a record this reader has no layout for,
    a definition body, the end of the data) end the count without counting as an error."""
    objs = collections.ChainMap({}, p.objs)
    _opaque(objs, p.idx + 1, idx)
    q = _Parser(data, pos, idx, p.cls, objs)
    q.defs_seen = p.defs_seen
    q.root_start = p.root_start
    q.cur_def = p.cur_def
    q.strict = True
    try:
        while q.idx - idx < k and q.pos < len(data) - 2:
            q.ref()
    except _Stop as e:
        m = str(e)
        if m.startswith(("bad reference", "unknown class", "type mismatch")):
            return q.idx - idx - 1  # the object being read when the error came is not counted
    except (struct.error, UnicodeDecodeError, IndexError):  # ran off a record: as a reference error
        return q.idx - idx - 1
    return min(q.idx - idx, k)


def _exact_offset(p, data, q, passing):
    """Index offset for a re-synchronisation at ``q`` (Phase 05g scope 6). Every offset in ``passing``
    survived the 60-reference trial, which can accept an offset that is one too small: nothing in its
    window referenced the last object created in the skipped bytes, so the error showed up kilobytes
    later as a 'bad reference' skip (CR3, CR4: a few KB after each 'definition body' skip). The exact
    offset is the one under which every back-reference resolves to an object of the class its field
    expects; it is taken as the passing offset that parses furthest under the strict, type-checked
    extended trial (ties: the smallest). One rule for every file, no per-room logic.

    Where all passing offsets tie (in CR3/CR4 about half the re-synchronisations: the trial reaches a
    record this reader has no layout for within a few objects, so nothing tells the offsets apart),
    the smallest is kept, as before Phase 05g; an offset error there is still caught by the next
    stop's re-synchronisation or by _offset_correction, and the area and re-extraction tests guard
    the geometry."""
    if len(passing) == 1:
        return passing[0]
    best, best_reach = passing[0], -1
    for delta in passing:
        r = _reach(p, data, q, p.idx + delta)
        if r > best_reach:
            best, best_reach = delta, r
        if r >= EXTENDED_TRIAL_OBJECTS:
            break  # cannot be beaten; a larger offset would only tie
    return best


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

    skipped = 0

    def emit(owner, M, inherited, depth):
        nonlocal skipped
        if depth > 32:
            raise SkpFormatError("instance nesting too deep")
        for f in by_owner.get(owner, []):
            n = np.array(f["n"])
            R = M[:3, :3]
            nw = np.linalg.inv(R).T @ n
            nw /= np.linalg.norm(nw)
            loops, area, off = [], 0.0, 0.0
            try:
                pts = [_loop_points(lp) for lp in f["loops"]]
            except (KeyError, TypeError):
                skipped += 1  # depends on an object in skipped bytes
                continue
            for k, P in enumerate(pts):
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
    model.faces_not_resolved = skipped
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
