"""AX26 (decision D-A, 2026-11-06): the shoebox reduction on a synthetic rotated L-shaped room.

The room goes through the same code as the BRAS rooms (extract_bras_geometry.reduce_polygons, then
make_bras_scenes.reduce_room). Checked: the box keeps V and A_floor (rel. 1e-9), ρ equals the side
ratio of the minimum-area oriented bounding rectangle (found here independently by a brute-force
angle scan), the absorption area A is conserved per face, and the S and Eyring errors are printed.
"""

from __future__ import annotations

import math
from dataclasses import dataclass

import numpy as np
import pytest

from tools.validation import extract_bras_geometry as ex
from tools.validation import make_bras_scenes as mk

# L-shaped plan: 10 x 6 m minus the 4 x 3 m corner at x 6..10, y 3..6; height 3 m
PLAN = [(0, 0), (10, 0), (10, 3), (6, 3), (6, 6), (0, 6)]
H = 3.0
A_FLOOR = 10 * 6 - 4 * 3
V = A_FLOOR * H
ROT_DEG = 27.0  # rotation of the whole model about z
MATERIALS = {1: "mat_T_floor", 2: "mat_T_wall", 3: "mat_T_ceiling"}


@dataclass
class Poly:
    material: int
    normal: np.ndarray
    area_m2: float
    loops: list
    off_plane_m: float = 0.0


def _rz(deg):
    c, s = math.cos(math.radians(deg)), math.sin(math.radians(deg))
    return np.array([[c, -s, 0], [s, c, 0], [0, 0, 1.0]])


def _poly(material, pts, normal):
    pts = np.asarray(pts, dtype=float)
    n = np.asarray(normal, dtype=float)
    # area of a planar polygon: |Σ p_i × p_{i+1}| / 2
    cr = sum(np.cross(pts[i], pts[(i + 1) % len(pts)]) for i in range(len(pts)))
    return Poly(material, n / np.linalg.norm(n), 0.5 * float(np.linalg.norm(cr)), [pts])


def l_room(rot_deg=ROT_DEG):
    """Polygons with inward normals (the BRAS/RAVEN convention), rotated by rot_deg about z."""
    polys = [_poly(1, [(x, y, 0) for x, y in PLAN], (0, 0, 1)),
             _poly(3, [(x, y, H) for x, y in PLAN], (0, 0, -1))]
    ccw = PLAN  # counter-clockwise, so the inward normal of edge p->q is the left normal
    for i in range(len(ccw)):
        (x1, y1), (x2, y2) = ccw[i], ccw[(i + 1) % len(ccw)]
        inward = (-(y2 - y1), x2 - x1, 0)
        polys.append(_poly(2, [(x1, y1, 0), (x2, y2, 0), (x2, y2, H), (x1, y1, H)], inward))
    R = _rz(rot_deg)
    for p in polys:
        p.normal = R @ p.normal
        p.loops = [L @ R.T for L in p.loops]
    return polys


def brute_force_rho(points_xy, step_deg=0.005):
    best = None
    P = np.asarray(points_xy, dtype=float)
    for t in np.arange(0.0, 90.0, step_deg):
        u = np.array([math.cos(math.radians(t)), math.sin(math.radians(t))])
        v = np.array([-u[1], u[0]])
        lu, lv = np.ptp(P @ u), np.ptp(P @ v)
        if best is None or lu * lv < best[0]:
            best = (lu * lv, max(lu, lv) / min(lu, lv))
    return best[1]


def _write_csv(path, alpha, s):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(",".join(str(f) for f in mk.THIRDS) + "\n" + ",".join(f"{alpha:.4f}" for _ in mk.THIRDS) + "\n"
                    + ",".join(f"{s:.4f}" for _ in mk.THIRDS) + "\n")


@pytest.fixture
def geometry(tmp_path):
    polys = l_room()
    names = dict(MATERIALS)
    src = (_rz(ROT_DEG) @ np.array([2.0, 1.5, 1.5])).tolist()
    rcv = (_rz(ROT_DEG) @ np.array([4.0, 4.5, 1.2])).tolist()
    g = ex.reduce_polygons("T", polys, names, {"LS1": src}, {"MP1": rcv})
    S = sum(p.area_m2 for p in l_room())
    g["documented"] = {"V": V, "S": S, "areas": {}}
    for n in MATERIALS.values():
        g["documented"]["areas"][n] = sum(p.area_m2 for p in l_room() if MATERIALS[p.material] == n)
    for n, (a, s) in {"mat_T_floor": (0.30, 0.2), "mat_T_wall": (0.05, 0.1), "mat_T_ceiling": (0.15, 0.4)}.items():
        _write_csv(tmp_path / "materials" / "initial" / f"{n}.csv", a, s)
    return g, tmp_path


def test_rotation_is_undone(geometry):
    g, _ = geometry
    # rule 1 aligns the walls with the axes: the rotation is ROT_DEG modulo 90 deg
    assert ((g["rotation_deg"] - ROT_DEG + 45) % 90) - 45 == pytest.approx(0.0, abs=1e-9)
    assert g["floor_area_m2"] == pytest.approx(A_FLOOR, rel=1e-12)


def test_box_keeps_v_and_floor_area_and_rho(geometry):
    g, cache = geometry
    red = mk.reduce_room("T", g, cache, "initial")
    d = red["dims"]
    assert d["W"] * d["D"] * d["H"] == pytest.approx(V, rel=1e-9)
    assert d["W"] * d["D"] == pytest.approx(A_FLOOR, rel=1e-9)
    assert d["H"] == pytest.approx(V / A_FLOOR, rel=1e-9)
    assert d["W"] >= d["D"]  # long side along x (AQ1)
    # independent ρ: brute-force minimum-area rectangle over the floor polygon's own vertices
    floor = [p for p in l_room() if p.material == 1][0]
    rho_ref = brute_force_rho(floor.loops[0][:, :2])
    assert d["rho"] == pytest.approx(rho_ref, rel=1e-5)
    assert d["W"] / d["D"] == pytest.approx(rho_ref, rel=1e-5)


def test_absorption_area_conserved_per_face(geometry):
    g, cache = geometry
    red = mk.reduce_room("T", g, cache, "initial")
    alpha = {"mat_T_floor": 0.30, "mat_T_wall": 0.05, "mat_T_ceiling": 0.15}
    for face, fr in red["faces"].items():
        expected = sum(a * alpha[n] for n, a in fr["materials_m2"].items())
        for b in range(8):
            assert fr["alpha"][b] * fr["area_m2"] == pytest.approx(expected, rel=1e-9, abs=1e-12)
    assert not red["clamps"]
    for b in range(8):
        assert red["absorption_area_box_m2"][b] == pytest.approx(red["absorption_area_documented_m2"][b], rel=1e-9)


def test_s_and_eyring_errors_are_reported(geometry, capsys):
    g, cache = geometry
    red = mk.reduce_room("T", g, cache, "initial")
    d = red["dims"]
    S = g["documented"]["S"]
    # the L room's real S exceeds the box S: the box has less wall (perimeter 32 m vs 2(a + b))
    assert d["S_box"] < S
    assert d["S_error_pct"] == pytest.approx(100 * (d["S_box"] / S - 1), rel=1e-12)
    assert d["mean_free_path_box_m"] == pytest.approx(4 * V / d["S_box"], rel=1e-12)
    # Eyring on the documented V, S, A (independent formula) and on the box
    m = mk.air_m_per_m()
    A = np.array(red["absorption_area_documented_m2"])
    t_doc = 0.161 * V / (-S * np.log(1 - A / S) + 4 * m * V)
    assert red["eyring_t60_documented_s"] == pytest.approx(t_doc.tolist(), rel=1e-12)
    print(f"AX26 L-room: box {d['W']:.3f} x {d['D']:.3f} x {d['H']:.3f} m, rho {d['rho']:.4f}, "
          f"S box {d['S_box']:.2f} vs {S:.2f} m^2 ({d['S_error_pct']:+.2f} %), Eyring error per band (%) "
          + ", ".join(f"{e:+.2f}" for e in red["eyring_error_pct"]))
    out = capsys.readouterr().out
    assert "S box" in out
    with capsys.disabled():
        print("\n" + out.strip())
