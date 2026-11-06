"""Reference hybrid (AX21, phase-05 scope 6): checks against independent anchors.

- lattice: image count of a shoebox up to order 2 (Allen & Berkley; imageCount(2) = 25);
- injection closes: the direct-path solid angles of all patches sum to 4π (closed box);
- gathering closes: uniform Lambert exitance M on every wall gives 4M at any interior point
  (Σ Ω_k/π = 4);
- all-Lambert limit (s = 1): the hybrid's late decay equals the radiosity a* (Kuttruff Eq. 5.53)
  and the independent Lambert-particle Monte Carlo (`radiosity.lambert_mc_t60`) within 2 %;
- s = 0: no diffuse energy;
- the Python Phase 04 mixing time, AX22 fallback and AX16 E_target equal `render_cli --diagnostics`
  (t_mix,e to 1e-12 s; E_target up to the simulator filterbank's band impulse energy, which is the
  same factor in every scene).
"""

import json
import pathlib

import numpy as np
import pytest

from tools.acoustics import radiosity, render_cli
from tools.acoustics import ref_hybrid as rh

REPO = pathlib.Path(__file__).resolve().parents[3]
FACES = ("xMin", "xMax", "yMin", "yMax", "floor", "ceiling")


def test_lattice_counts_images_up_to_order_2():
    lat = rh.lattice((4.0, 5.0, 3.0), 40.0)
    assert int((lat.hits.sum(axis=1) <= 2).sum()) == 25
    assert int((lat.hits.sum(axis=1) == 0).sum()) == 1


def test_direct_injection_solid_angles_close_the_box():
    p = radiosity.box_patches((6.0, 4.0, 3.0), 1.0)
    src = np.array([1.3, 2.9, 0.7])
    om = rh.solid_angle_quad(np.broadcast_to(src, (len(p.areas), 3)), p.corners)
    assert om.sum() == pytest.approx(4 * np.pi, rel=1e-9)


def test_uniform_exitance_gathers_to_4M():
    dims = (6.0, 4.0, 3.0)
    # alpha = 1: every image path carries 0, so only the direct (order-0) gather remains
    var = rh.variant([[1.0] * 8] * 6, [1.0] * 6, [0.0] * 8)
    rk = rh.RoomKernel(dims, 1.5, 0.03, [var])
    g = rh.gather_kernel(rk, [2.0, 1.0, 1.4])  # (1, 8, N, T): per unit energy emitted by patch k
    total = (g[0, 3].sum(axis=1) * rk.p.areas).sum()  # exitance M = 1: patch k emits A_k
    assert total == pytest.approx(4.0, rel=2e-3)


def test_all_lambert_decay_equals_a_star_and_the_particle_monte_carlo():
    dims = (10.0, 10.0, 10.0)
    a = 0.5
    var = rh.variant([[a] * 8] * 6, [1.0] * 6, [0.0] * 8)
    env, info = rh.run_pairs(dims, [var], [([3.0, 4.0, 5.0], [6.0, 5.0, 4.0])], t_end_s=0.16, patch_size=2.5)
    e = env[0, 3, 0]
    t = (np.arange(e.size) + 0.5) * rh.DT
    sel = (t > 0.06) & (t < 0.155)
    t60 = -60 / np.polyfit(t[sel], 10 * np.log10(e[sel]), 1)[0]
    p = radiosity.box_patches(dims, 2.5)
    t60_astar = radiosity.t60_from_a(dims, radiosity.a_star(dims, np.full(len(p.areas), 1 - a), p))
    t60_mc = radiosity.lambert_mc_t60(dims, [a] * 6, n=100_000, seed=7)[0]
    assert t60 == pytest.approx(t60_astar, rel=0.02)
    assert t60 == pytest.approx(t60_mc, rel=0.02)


def test_no_scattering_gives_no_diffuse_energy():
    var = rh.variant([[0.2] * 8] * 6, [0.0] * 6, [0.0] * 8)
    env, _ = rh.run_pairs((5.0, 4.0, 3.0), [var], [([1.0, 1.0, 1.0], [3.0, 2.5, 1.5])], 0.03, 2.0)
    assert np.all(env == 0.0)


def _scene(path):
    d = json.loads(path.read_text())
    r = d["room"]
    al = [r["surfaces"][f]["absorption"] for f in FACES]
    s = [r["surfaces"][f]["scattering"] for f in FACES]
    return d, tuple(r["geometry"]["dimensions"]), al, s


@pytest.mark.parametrize("name", ["club", "stone_box", "medium_room"])  # medium_room: AX22 fallback
def test_python_phase04_plan_matches_render_cli(name, tmp_path):
    binary = render_cli.find_render_cli()
    if binary is None:
        pytest.skip("render_cli not built")
    path = REPO / "tests" / "scenes" / "valid" / f"{name}.json"
    out = tmp_path / "d.json"
    r = render_cli.run(binary, "--scene", path, "--mode", "omni", "--rate", "44100", "--diagnostics", out)
    assert r.returncode == 0, r.stderr
    dg = json.loads(out.read_text())
    e = dg["emitters"][0]
    d, dims, al, s = _scene(path)
    var = rh.variant(al, s, dg["airEnergyPerMetre"])
    plan = rh.phase04_plan(dims, var, d["emitters"][0]["position"], d["listener"]["position"])
    assert plan["mix"]["mixS"] == pytest.approx(e["mixS"], abs=1e-12)
    assert plan["fallback"] == e["ismFallback"]
    np.testing.assert_allclose(plan["t60"], dg["t60"], rtol=1e-9)
    ratio = np.array(e["targetEnergy"]) / plan["target_ax16"]
    # the simulator's band impulse energies at 44.1 kHz (the same in every scene)
    np.testing.assert_allclose(ratio, BAND_ENERGY_44K, rtol=1e-4)


BAND_ENERGY_44K = np.array([0.0039404, 0.00380438, 0.00760878, 0.01521785, 0.03043599, 0.06087664, 0.12175825, 0.73911278])
