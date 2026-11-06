"""Reduce the BRAS rooms to contract shoebox scenes by the generic rules of
docs/validation/bras_mapping.md §3 (no per-room parameter; NFR-8).

    python tools/validation/make_bras_scenes.py            # writes tests/scenes/validation/*.json
    python tools/validation/make_bras_scenes.py --check    # fails if the committed scenes differ

Inputs: tools/validation/data/bras_geometry.json (extract_bras_geometry.py) and the BRAS material
csv files (fetch_bras.py --groups materials). Outputs: one scene per source/receiver pair and α
set, ``tests/scenes/validation/bras_<room>_<src>_<rcv>[_fitted].json``, and the reduction table
``tools/validation/data/bras_reduction.json`` (rendered into bras_mapping.md §5 and the report).
"""

from __future__ import annotations

import argparse
import json
import math
import pathlib
import sys

import numpy as np

HERE = pathlib.Path(__file__).resolve().parent
REPO = HERE.parents[1]
sys.path.insert(0, str(REPO))

from tools.validation import fetch_bras  # noqa: E402

GEOMETRY = HERE / "data" / "bras_geometry.json"
REDUCTION = HERE / "data" / "bras_reduction.json"
SCENES = REPO / "tests" / "scenes" / "validation"
FACES = ("xMin", "xMax", "yMin", "yMax", "floor", "ceiling")
OCTAVES = (63, 125, 250, 500, 1000, 2000, 4000, 8000)
THIRDS = (20, 25, 31.5, 40, 50, 63, 80, 100, 125, 160, 200, 250, 315, 400, 500, 630, 800, 1000, 1250, 1600, 2000,
          2500, 3150, 4000, 5000, 6300, 8000, 10000, 12500, 16000, 20000)
CLEARANCE = 0.1  # AX6
CONTRACT_VERSION = "1.1"
ALPHA_MIN, ALPHA_MAX = 0.01, 1.0  # AQ3
SEED_BASE = 505000


def read_csv(path: pathlib.Path):
    lines = [l for l in path.read_text().splitlines() if l.strip()]
    f = [float(x) for x in lines[0].split(",")]
    a = [float(x) for x in lines[1].split(",")]
    s = [float(x) for x in lines[2].split(",")]
    if [round(x, 1) for x in f] != [round(x, 1) for x in THIRDS]:
        raise SystemExit(f"{path}: unexpected frequencies")
    return np.array(a), np.array(s)


def _thirds(fc):
    i = min(range(len(THIRDS)), key=lambda k: abs(THIRDS[k] - fc))
    return slice(i - 1, i + 2)


def to_octaves(alpha3: np.ndarray, s3: np.ndarray):
    """AX25: an octave's α is the arithmetic mean of its three third octaves (the absorption area
    is linear in α, Vorländer Eq. 4.30); its s is the reflected-energy-weighted mean
    Σ(1-α_k)s_k / Σ(1-α_k) over the three, as rule 4 weights s across surfaces (Vorländer
    Eqs. 3.23-3.24; interrogator AX25-5)."""
    a_oct, s_oct = [], []
    for fc in OCTAVES:
        sl = _thirds(fc)
        a, s = alpha3[sl], s3[sl]
        a_oct.append(float(np.mean(a)))
        w = 1 - a
        s_oct.append(float(np.sum(w * s) / np.sum(w)) if np.sum(w) > 0 else float(np.mean(s)))
    return np.array(a_oct), np.array(s_oct)


def dimensions(V: float, S: float, A_floor: float):
    """Rule 2: keep h = V / A_floor; a b = V/h, a + b = (S - 2V/h)/(2h); longer side along x."""
    h = V / A_floor
    P = V / h
    half_sum = (S - 2 * P) / (4 * h)  # (a + b)/2
    disc = half_sum**2 - P
    if disc >= 0:
        a = half_sum + math.sqrt(disc)
        b = half_sum - math.sqrt(disc)
        fallback = False
    else:
        a = b = math.sqrt(P)
        fallback = True
    S_box = 2 * (a * b + a * h + b * h)
    return {"W": a, "D": b, "H": h, "square_floor_fallback": fallback, "S_box": S_box, "S_error_pct": 100 * (S_box / S - 1)}


def face_areas(W, D, H):
    return {"xMin": D * H, "xMax": D * H, "yMin": W * H, "yMax": W * H, "floor": W * D, "ceiling": W * D}


def reduce_room(room: str, g: dict, cache: pathlib.Path, alpha_set: str) -> dict:
    doc = g["documented"]
    dims = dimensions(doc["V"], doc["S"], g["floor_area_m2"])
    # the model's horizontal axes: the longer floor extent goes along x (AQ1)
    x0, y0, x1, y1 = g["floor_bbox_xy"]
    swap = (y1 - y0) > (x1 - x0)
    areas_box = face_areas(dims["W"], dims["D"], dims["H"])
    mats = {}
    for name in doc["areas"]:
        a3, s3 = read_csv(cache / "materials" / alpha_set / f"{name}.csv")
        mats[name] = to_octaves(a3, s3)
    assigned = {}
    for key, a in g["assigned_area_m2"].items():
        name, face = key.split("|")
        if swap:  # box x = model y, box y = -model x (a 90 deg rotation, right-handed)
            face = {"yMin": "xMin", "yMax": "xMax", "xMin": "yMax", "xMax": "yMin"}.get(face, face)
        assigned.setdefault(face, {})[name] = assigned.get(face, {}).get(name, 0.0) + a
    faces = {}
    clamps = []
    for face in FACES:
        part = assigned.get(face, {})
        Sf = areas_box[face]
        A = np.zeros(8)
        num = np.zeros(8)
        den = np.zeros(8)
        for name, a in part.items():
            al, sc = mats[name]
            A += a * al
            num += a * (1 - al) * sc
            den += a * (1 - al)
        alpha = A / Sf
        for b in range(8):
            if alpha[b] > ALPHA_MAX or alpha[b] < ALPHA_MIN:
                c = min(max(alpha[b], ALPHA_MIN), ALPHA_MAX)
                clamps.append({"face": face, "band_hz": OCTAVES[b], "alpha": float(alpha[b]), "clamped": c,
                               "absorption_area_change_m2": float((c - alpha[b]) * Sf)})
                alpha[b] = c
        s_band = np.where(den > 0, num / np.where(den > 0, den, 1), 0.0)
        s_broad = float(np.clip(np.mean(s_band[3:6]), 0.0, 1.0))  # AX17: 500 Hz, 1 kHz, 2 kHz
        faces[face] = {"area_m2": Sf, "assigned_m2": sum(part.values()), "materials_m2": part,
                       "alpha": alpha.tolist(), "scattering_bands": s_band.tolist(), "scattering": s_broad}
    total_A = sum(np.array(faces[f]["alpha"]) * faces[f]["area_m2"] for f in FACES)
    doc_A = sum(np.array(mats[n][0]) * a for n, a in doc["areas"].items())
    return {"dims": dims, "swap_xy": swap, "faces": faces, "clamps": clamps,
            "absorption_area_box_m2": total_A.tolist(), "absorption_area_documented_m2": doc_A.tolist()}


def map_positions(g: dict, red: dict) -> dict:
    """Rule 6 (AX24) for every source/receiver pair."""
    W, D, H = red["dims"]["W"], red["dims"]["D"], red["dims"]["H"]
    x0, y0, x1, y1 = g["floor_bbox_xy"]
    swap = red["swap_xy"]
    pos = g["positions"]

    def horiz(p):
        x, y = p[0], p[1]
        u, v = (x - x0) / (x1 - x0), (y - y0) / (y1 - y0)
        if swap:  # model y becomes box x; model x becomes box y, flipped to keep a right-handed frame
            u, v = v, 1 - u
        return np.array([u * W, v * D])

    def dir_xy(d):
        return np.array([d[1], -d[0]]) if swap else np.array([d[0], d[1]])

    out = {}
    for s in sorted(k for k in pos if k.startswith("LS")):
        for r in sorted(k for k in pos if k.startswith("MP")):
            ps, pr = pos[s], pos[r]
            # AX24: both heights to one floor plane, the floor face under the pair's horizontal
            # midpoint (where the floor reflection lands); so dh = dz and the real horizontal
            # separation is kept (interrogator AX24-4, AX24-5).
            zf = g["pair_floor"][f"{s}_{r}"]["z_floor"]
            hs, hr = ps["xyz"][2] - zf, pr["xyz"][2] - zf
            dm = np.array(pr["xyz"]) - np.array(ps["xyz"])
            r_real = float(np.linalg.norm(dm))
            dh = float(np.linalg.norm(dm[:2]))
            mid = 0.5 * (horiz(ps["xyz"]) + horiz(pr["xyz"]))
            u = dir_xy(dm[:2])
            u = u / np.linalg.norm(u) if np.linalg.norm(u) > 0 else np.array([1.0, 0.0])
            qs = np.array([*(mid - 0.5 * dh * u), hs])
            qr = np.array([*(mid + 0.5 * dh * u), hr])
            moved = []
            for q, tag in ((qs, s), (qr, r)):
                for k, lim in enumerate((W, D, H)):
                    c = min(max(q[k], CLEARANCE), lim - CLEARANCE)
                    if c != q[k]:
                        moved.append(f"{tag} axis {'xyz'[k]} {q[k]:.3f} -> {c:.3f}")
                        q[k] = c
            r_box = float(np.linalg.norm(qr - qs))
            out[f"{s}_{r}"] = {"source": qs.tolist(), "receiver": qr.tolist(), "r_real": r_real, "r_box": r_box,
                               "r_error_m": r_box - r_real, "h_source": hs, "h_receiver": hr,
                               "z_floor": zf, "floor_found": g["pair_floor"][f"{s}_{r}"]["floor_found"], "moved": moved}
    return out


def scene_json(red: dict, pair: dict, seed: int) -> dict:
    d = red["dims"]
    surfaces = {f: {"absorption": [round(a, 6) for a in red["faces"][f]["alpha"]],
                    "scattering": round(red["faces"][f]["scattering"], 6)} for f in ("floor", "ceiling", "xMin", "xMax", "yMin", "yMax")}
    src = [round(x, 6) for x in pair["source"]]
    return {
        "contractVersion": CONTRACT_VERSION,
        "units": "meters",
        "room": {"geometry": {"kind": "shoebox", "dimensions": [round(d["W"], 6), round(d["D"], 6), round(d["H"], 6)]},
                 "surfaces": surfaces},
        "listener": {"position": [round(x, 6) for x in pair["receiver"]]},
        "emitters": [{"id": "L", "channel": 0, "position": src, "gainDb": 0.0},
                     {"id": "R", "channel": 1, "position": src, "gainDb": 0.0}],
        "render": {"outputMode": "binaural", "hrtfId": "generic-v1", "maxReflectionOrder": 20, "tailSeed": seed},
        "extensions": {"bras": "Derived from BRAS (CC BY-SA 4.0), docs/validation/bras_mapping.md; omni analysis "
                               "of emitter L (R duplicates it)."},
    }


def build(cache: pathlib.Path):
    g_all = json.loads(GEOMETRY.read_text(encoding="utf-8"))["rooms"]
    reduction = {}
    scenes = {}
    for k_room, (room, g) in enumerate(sorted(g_all.items())):
        reduction[room] = {}
        for alpha_set, suffix in (("initial", ""), ("fitted", "_fitted")):
            red = reduce_room(room, g, cache, alpha_set)
            pairs = map_positions(g, red)
            red["pairs"] = pairs
            reduction[room][alpha_set] = red
            for k_pair, (pk, pair) in enumerate(sorted(pairs.items())):
                s, r = pk.split("_")
                seed = SEED_BASE + 100 * k_room + k_pair
                scenes[f"bras_{room.lower()}_{s.lower()}_{r.lower()}{suffix}.json"] = scene_json(red, pair, seed)
    return reduction, scenes


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument("--check", action="store_true")
    a = ap.parse_args(argv)
    cache = fetch_bras.cache_dir()
    fetch_bras.fetch(["materials"], cache)
    reduction, scenes = build(cache)
    texts = {n: json.dumps(s, indent=2) + "\n" for n, s in scenes.items()}
    red_text = json.dumps(reduction, indent=1) + "\n"
    if a.check:
        bad = [n for n, t in texts.items() if not (SCENES / n).exists() or (SCENES / n).read_text() != t]
        if REDUCTION.read_text() != red_text:
            bad.append(REDUCTION.name)
        if bad:
            raise SystemExit(f"out of date: {bad}")
        print("scenes up to date")
        return
    SCENES.mkdir(parents=True, exist_ok=True)
    for n, t in texts.items():
        (SCENES / n).write_text(t)
    REDUCTION.write_text(red_text)
    print(f"wrote {len(texts)} scenes and {REDUCTION}")


if __name__ == "__main__":
    main()
