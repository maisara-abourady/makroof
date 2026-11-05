"""Phase 04: the late tail and the hybrid omni IR through the real render_cli binary.

Gates (docs/phases/phase-04.md, BUILD_PLAN AX11, AX19, AX21):
- independent Python Eyring (with ISO 9613-1 air, m = D / 4.343) and mixing-time rule agree with
  the C++ diagnostics;
- Eyring gate: tail-only T30 within +-5 % (250 Hz-4 kHz) / +-10 % (125 Hz, 8 kHz) of Eyring T60_b on
  AX11 ensembles; 1-8 kHz read in the central half octave, 63-500 Hz in octaves (AX21);
- seed gate: two disjoint ensembles agree within +-2 % (125 Hz-8 kHz);
- sample-rate gate: 44.1 vs 96 kHz ensembles agree in T30 (+-2 %, 63 Hz-8 kHz, tail-only), EDT
  (+-2 %, 63 Hz-8 kHz) and C80 (+-0.5 dB, 125 Hz-8 kHz) of the hybrid IR, R from the measured
  sigma1 (tools/acoustics/data/phase04_sigma1.json, AX19);
- seam: the ensemble-averaged EDC has no step > 1 dB (beyond the expected decay) across the 5 ms
  crossfade around each emitter's t_mix;
- golden metrics of every valid fixture (48 kHz, the fixture's own tailSeed).
Single-realisation values are printed (pytest -rP), not gated.
"""

from __future__ import annotations

import functools
import json
import math
import pathlib

import numpy as np
import pytest
from scipy import integrate

from tools.acoustics import air, bands, ensembles, golden, metrics

from conftest import REPO

VALID = REPO / "tests" / "scenes" / "valid"
ROOMS = ("dead_booth", "living_room", "classroom", "club", "concert_hall_box", "stone_box")
SURFACES = ("xMin", "xMax", "yMin", "yMax", "floor", "ceiling")
C = 343.0
SIGMA1_FILE = REPO / "tools" / "acoustics" / "data" / "phase04_sigma1.json"

# Disjoint tail-seed ranges per ensemble (consecutive seeds from each base).
SEED_EYRING_A = 1_000_000  # Eyring gate and seed-gate ensemble A (48 kHz, tail-only)
SEED_B = 2_000_000  # seed-gate ensemble B
SEED_RATE_T30 = {44100: 3_000_000, 96000: 4_000_000}  # tail-only
SEED_RATE_FULL = {44100: 5_000_000, 96000: 6_000_000}  # hybrid IR (EDT, C80)
SEED_SEAM = 7_000_000

EYRING_TOL_PCT = {125.0: 10.0, 250.0: 5.0, 500.0: 5.0, 1000.0: 5.0, 2000.0: 5.0, 4000.0: 5.0, 8000.0: 10.0}
SEED_BANDS = (125.0, 250.0, 500.0, 1000.0, 2000.0, 4000.0, 8000.0)
EDT_BANDS = bands.OCTAVE_BANDS_HZ
C80_BANDS = SEED_BANDS


def scene_path(name: str) -> pathlib.Path:
    return VALID / f"{name}.json"


def load(name: str) -> dict:
    return json.loads(scene_path(name).read_text(encoding="utf-8"))


@functools.lru_cache(maxsize=None)
def diag(binary: str, name: str, rate: int = 48000) -> dict:
    return ensembles.diagnostics(pathlib.Path(binary), scene_path(name), rate)


def rel_pct(a: float, b: float) -> float:
    return 100.0 * (a / b - 1.0)


# ---------------------------------------------------------------------------------------------
# Independent references for the diagnostics
# ---------------------------------------------------------------------------------------------

def eyring_reference(scene: dict, air_absorption: bool = True) -> np.ndarray:
    w, d, h = scene["room"]["geometry"]["dimensions"]
    areas = {"xMin": d * h, "xMax": d * h, "yMin": w * h, "yMax": w * h, "floor": w * d, "ceiling": w * d}
    s = sum(areas.values())
    v = w * d * h
    alpha = np.array([sum(areas[k] * scene["room"]["surfaces"][k]["absorption"][b] for k in SURFACES) / s for b in range(8)])
    m = air.attenuation_db_per_m(np.array(bands.OCTAVE_BANDS_HZ)) / (10.0 / math.log(10.0)) if air_absorption else np.zeros(8)
    return 0.161 * v / (-s * np.log(1.0 - np.minimum(alpha, 0.999)) + 4.0 * m * v)


def keff(a: float, b: float, v: float) -> float:
    w = lambda t: math.sin(math.pi * (t - a) / (b - a)) ** 2  # noqa: E731
    num = integrate.quad(w, a, b)[0] ** 2
    den = integrate.quad(lambda t: w(t) ** 2 / t**2, a, b, limit=200)[0]
    return 4.0 * math.pi * C**3 / v * num / den


def mixing_time_reference(direct: float, v: float) -> float:
    lower = direct + max(0.020, math.sqrt(v) * 1e-3)
    start = direct + 0.0025
    if keff(start, lower, v) >= 19.0:
        return lower
    lo, hi = lower, lower + 0.001
    while keff(start, hi, v) < 19.0:
        hi = start + 2.0 * (hi - start)
    for _ in range(60):
        mid = 0.5 * (lo + hi)
        lo, hi = (lo, mid) if keff(start, mid, v) >= 19.0 else (mid, hi)
    return hi


@pytest.mark.parametrize("name", [*ROOMS, "medium_room", "open_field", "edge_values"])
def test_diagnostics_match_independent_eyring_and_mixing_time(render_cli_path, name):
    scene = load(name)
    d = diag(str(render_cli_path), name)
    np.testing.assert_allclose(d["t60"], eyring_reference(scene), rtol=1e-9)
    # m_b = D_b / 4.343 (energy, not pressure), from the independent ISO 9613-1 implementation.
    np.testing.assert_allclose(d["airEnergyPerMetre"], air.attenuation_db_per_m(np.array(bands.OCTAVE_BANDS_HZ)) / 4.342944819032518, rtol=1e-9)
    assert d["tailLengthS"] == pytest.approx(min(12.0, 1.5 * max(d["t60"])), rel=1e-12)
    w, dd, h = scene["room"]["geometry"]["dimensions"]
    for e in d["emitters"]:
        emitter = next(x for x in scene["emitters"] if x["channel"] == e["channel"])
        direct = math.dist(emitter["position"], scene["listener"]["position"]) / C
        assert e["directS"] == pytest.approx(direct, abs=1e-12)
        assert e["mixS"] == pytest.approx(mixing_time_reference(direct, w * dd * h), abs=1e-7)
        assert e["expectedKeff"] >= 19.0 - 1e-9
        assert e["expectedSigmaDb"] == pytest.approx(4.342944819032518 / math.sqrt(e["expectedKeff"]), rel=1e-9)
        print(f"{name} emitter {e['id']}: t_dir {1e3 * direct:.1f} ms, t_mix {1e3 * e['mixS']:.1f} ms, "
              f"{e['imageCount']} images, expected sigma {e['expectedSigmaDb']:.2f} dB, "
              f"non-zero entries {e['nonZeroEntries']}, realised k_eff {[round(k, 1) for k in e['realisedKeff']]}, "
              f"realised/target at t_mix {[None if x is None else round(x, 1) for x in e['realisedOverTargetDb']]} dB")


def test_open_field_has_no_tail(render_cli_path):
    """E_b = 0 in every band for the fixture (floor s = 0.4) and for floor s = 0.5 (the C++ test
    test_hybrid_ir.cpp also checks the energy 50 ms after the direct sound)."""
    for s in (0.4, 0.5):
        scene = load("open_field")
        scene["room"]["surfaces"]["floor"]["scattering"] = s
        d = ensembles.diagnostics(render_cli_path, scene)
        for e in d["emitters"]:
            assert e["amplitude"] == [0.0] * 8
            assert e["nonZeroEntries"] == [0] * 8


# ---------------------------------------------------------------------------------------------
# Eyring gate (AX11 ensembles, AX21 meter)
# ---------------------------------------------------------------------------------------------

def eyring_r(t60: list[float]) -> dict[float, int]:
    out = {}
    for i, fc in enumerate(bands.OCTAVE_BANDS_HZ):
        if fc not in EYRING_TOL_PCT:
            continue
        r = ensembles.r_t30(fc, t60[i], EYRING_TOL_PCT[fc])
        out[fc] = 2 * r if fc in ensembles.HALF_OCTAVE_BANDS_HZ else r  # AX21: half octave, half the bandwidth
    return out


@pytest.mark.ensemble
@pytest.mark.parametrize("name", ROOMS)
def test_eyring_gate_t30_of_the_tail(render_cli_path, name):
    d = diag(str(render_cli_path), name)
    t60 = d["t60"]
    r_by_band = eyring_r(t60)
    r = max(r_by_band.values())
    acc = ensembles.EnsembleAccumulator(48000.0, octave_bands=bands.OCTAVE_BANDS_HZ,
                                        half_octave_bands=ensembles.HALF_OCTAVE_BANDS_HZ)
    ensembles.accumulate(render_cli_path, scene_path(name), SEED_EYRING_A, r, 48000, True, acc)
    single, _ = ensembles.render_ensemble(render_cli_path, scene_path(name), SEED_EYRING_A, 1, 48000, tail_only=True)
    single_m = metrics.room_metrics(single[0, 0], 48000.0)
    failures = []
    for i, fc in enumerate(bands.OCTAVE_BANDS_HZ):
        key = bands.band_key(fc)
        octave = acc.octave(fc)["T30"]
        half = acc.half_octave(fc)["T30"] if fc in ensembles.HALF_OCTAVE_BANDS_HZ else None
        gated = half if fc in ensembles.HALF_OCTAVE_BANDS_HZ else octave
        fmt = lambda x: "None" if x is None else f"{rel_pct(x, t60[i]):+.2f} %"  # noqa: E731
        print(f"{name} {key} Hz: Eyring {t60[i]:.3f} s, R {r} (band needs {r_by_band.get(fc, '-')}), "
              f"gated ({'half octave' if half is not None else 'octave'}) {fmt(gated)}, octave {fmt(octave)}, "
              f"single realisation (octave) {fmt(single_m['bands'][key]['T30'])}")
        if fc in EYRING_TOL_PCT:
            if gated is None or abs(rel_pct(gated, t60[i])) > EYRING_TOL_PCT[fc]:
                failures.append(f"{key} Hz: {fmt(gated)} (tolerance +-{EYRING_TOL_PCT[fc]} %)")
    assert not failures, f"{name}: " + "; ".join(failures)


# ---------------------------------------------------------------------------------------------
# Seed gate
# ---------------------------------------------------------------------------------------------

@pytest.mark.ensemble
@pytest.mark.parametrize("name", ROOMS)
def test_seed_gate_two_ensembles_agree(render_cli_path, name):
    t60 = diag(str(render_cli_path), name)["t60"]
    r = max(ensembles.r_seed_gate(fc, t60[i]) for i, fc in enumerate(bands.OCTAVE_BANDS_HZ) if fc in SEED_BANDS)
    a = ensembles.accumulate(render_cli_path, scene_path(name), SEED_EYRING_A, r, 48000, True,
                             ensembles.EnsembleAccumulator(48000.0, octave_bands=SEED_BANDS))
    b = ensembles.accumulate(render_cli_path, scene_path(name), SEED_B, r, 48000, True,
                             ensembles.EnsembleAccumulator(48000.0, octave_bands=SEED_BANDS))
    singles, _ = ensembles.render_ensemble(render_cli_path, scene_path(name), SEED_EYRING_A, 1, 48000, tail_only=True)
    single_b, _ = ensembles.render_ensemble(render_cli_path, scene_path(name), SEED_B, 1, 48000, tail_only=True)
    ma, mb = metrics.room_metrics(singles[0, 0], 48000.0), metrics.room_metrics(single_b[0, 0], 48000.0)
    failures = []
    for fc in SEED_BANDS:
        key = bands.band_key(fc)
        ta, tb = a.octave(fc)["T30"], b.octave(fc)["T30"]
        sa, sb = ma["bands"][key]["T30"], mb["bands"][key]["T30"]
        single = "None" if sa is None or sb is None else f"{rel_pct(sa, sb):+.2f} %"
        diff = None if ta is None or tb is None else rel_pct(ta, tb)
        print(f"{name} {key} Hz: R {r} per ensemble, T30 A {ta} s, B {tb} s, difference "
              f"{'None' if diff is None else f'{diff:+.2f} %'}; single realisations {single}")
        if diff is None or abs(diff) > 2.0:
            failures.append(f"{key} Hz: {diff}")
    assert not failures, f"{name}: " + "; ".join(failures)


# ---------------------------------------------------------------------------------------------
# Sample-rate gate (44.1 vs 96 kHz)
# ---------------------------------------------------------------------------------------------

def _sigma1() -> dict:
    return json.loads(SIGMA1_FILE.read_text(encoding="utf-8"))["rooms"]


def rate_full_r(name: str) -> tuple[int, dict]:
    """R per ensemble of the EDT/C80 sample-rate gate (AX19) and the per-band needs."""
    s = _sigma1()[name]
    needs = {}
    for fc in EDT_BANDS:
        key = bands.band_key(fc)
        needs[f"EDT {key}"] = ensembles.r_two_ensembles(s["44100"]["EDT_pct"][key], s["96000"]["EDT_pct"][key], 2.0)
    for fc in C80_BANDS:
        key = bands.band_key(fc)
        needs[f"C80 {key}"] = ensembles.r_two_ensembles(s["44100"]["C80_dB"][key], s["96000"]["C80_dB"][key], 0.5)
    return max(needs.values()), needs


def test_sigma1_file_covers_the_six_rooms_with_n_51():
    s = _sigma1()
    for name in ROOMS:
        for rate in ("44100", "96000"):
            entry = s[name][rate]
            assert entry["n"] >= 51
            for key in map(bands.band_key, EDT_BANDS):
                assert entry["EDT_pct"][key] is not None and entry["EDT_pct"][key] > 0.0
            for key in map(bands.band_key, C80_BANDS):
                assert entry["C80_dB"][key] is not None and entry["C80_dB"][key] > 0.0


@pytest.mark.ensemble
@pytest.mark.parametrize("name", ROOMS)
def test_sample_rate_gate_t30(render_cli_path, name):
    t60 = diag(str(render_cli_path), name)["t60"]
    r = max(ensembles.r_seed_gate(fc, t60[i]) for i, fc in enumerate(bands.OCTAVE_BANDS_HZ))
    accs = {}
    for rate in (44100, 96000):
        accs[rate] = ensembles.accumulate(render_cli_path, scene_path(name), SEED_RATE_T30[rate], r, rate, True,
                                          ensembles.EnsembleAccumulator(float(rate)))
    failures = []
    for fc in bands.OCTAVE_BANDS_HZ:
        key = bands.band_key(fc)
        t44, t96 = accs[44100].octave(fc)["T30"], accs[96000].octave(fc)["T30"]
        diff = None if t44 is None or t96 is None else rel_pct(t44, t96)
        print(f"{name} {key} Hz: R {r} per rate, T30 44.1 kHz {t44} s, 96 kHz {t96} s, difference "
              f"{'None' if diff is None else f'{diff:+.2f} %'}")
        if diff is None or abs(diff) > 2.0:
            failures.append(f"{key} Hz: {diff}")
    assert not failures, f"{name}: " + "; ".join(failures)


@pytest.mark.ensemble
@pytest.mark.parametrize("name", ROOMS)
def test_sample_rate_gate_edt_and_c80(render_cli_path, name):
    r, needs = rate_full_r(name)
    print(f"{name}: R {r} per rate (largest need {max(needs, key=needs.get)})")
    accs = {}
    singles = {}
    for rate in (44100, 96000):
        accs[rate] = ensembles.accumulate(render_cli_path, scene_path(name), SEED_RATE_FULL[rate], r, rate, False,
                                          ensembles.EnsembleAccumulator(float(rate)))
        one, _ = ensembles.render_ensemble(render_cli_path, scene_path(name), SEED_RATE_FULL[rate], 1, rate)
        singles[rate] = metrics.room_metrics(one[0, 0], float(rate))
    failures = []
    for fc in bands.OCTAVE_BANDS_HZ:
        key = bands.band_key(fc)
        m44, m96 = accs[44100].octave(fc), accs[96000].octave(fc)
        s44, s96 = singles[44100]["bands"][key], singles[96000]["bands"][key]
        edt = None if m44["EDT"] is None or m96["EDT"] is None else rel_pct(m44["EDT"], m96["EDT"])
        c80 = None if m44["C80"] is None or m96["C80"] is None else m44["C80"] - m96["C80"]
        single_edt = None if s44["EDT"] is None or s96["EDT"] is None else rel_pct(s44["EDT"], s96["EDT"])
        single_c80 = None if s44["C80"] is None or s96["C80"] is None else s44["C80"] - s96["C80"]
        print(f"{name} {key} Hz: EDT {m44['EDT']} / {m96['EDT']} s ({edt}%), C80 {m44['C80']} / {m96['C80']} dB "
              f"({c80} dB); single renders: EDT {single_edt} %, C80 {single_c80} dB")
        if fc in EDT_BANDS and (edt is None or abs(edt) > 2.0):
            failures.append(f"EDT {key} Hz: {edt}")
        if fc in C80_BANDS and (c80 is None or abs(c80) > 0.5):
            failures.append(f"C80 {key} Hz: {c80}")
    assert not failures, f"{name}: " + "; ".join(failures)


# ---------------------------------------------------------------------------------------------
# Seam test
# ---------------------------------------------------------------------------------------------

SEAM_R = 16
# Gated: the six test rooms and the Phase 03 room fixtures. Reported only: edge_values, the
# contract-limits fixture (a 1.5 m wide corridor with alpha alternating 0.01 / 1.0 between bands,
# so T60 steps ~4.5:1 at every octave and the octave analysis of a fast band reads its slower
# neighbours: measured -2.4 dB at 8 kHz on 16 realisations; a non-diffuse field where Eyring does not
# apply). open_field has no tail (E_b = 0).
SEAM_FIXTURES = (*ROOMS, "small_room", "medium_room", "large_hall", "asymmetric_materials")
SEAM_REPORTED_ONLY = ("edge_values",)


def seam_steps(binary, name: str, irs: np.ndarray, fs: float) -> np.ndarray:
    """EDC drop across [t_mix - 2.5 ms, t_mix + 2.5 ms] minus the expected 60 dB * 5 ms / T60_b, per
    emitter and band (dB), on the ensemble-averaged band energy."""
    d = diag(str(binary), name)
    steps = np.zeros((2, len(bands.OCTAVE_BANDS_HZ)))
    for e in (0, 1):
        acc = ensembles.EnsembleAccumulator(fs)
        acc.add_all(irs[:, e])
        onset = metrics.onset_index(irs[0, e])
        t_mix = (d["emitters"][e]["mixS"] - d["alignmentShiftS"]) * fs - onset
        for i, fc in enumerate(bands.OCTAVE_BANDS_HZ):
            energy, lead = acc.octave_energy(fc)
            edc = np.cumsum(energy[::-1])[::-1]
            edc_db = 10.0 * np.log10(edc / edc[0])
            a = int(round(t_mix - 0.0025 * fs)) + lead
            b = int(round(t_mix + 0.0025 * fs)) + lead
            assert np.all(np.diff(edc) <= 0.0)  # Schroeder EDC is monotonic
            steps[e, i] = (edc_db[a] - edc_db[b]) - 60.0 * 0.005 / d["t60"][i]
    return steps


@pytest.mark.parametrize("name", (*SEAM_FIXTURES, *SEAM_REPORTED_ONLY))
def test_seam_edc_has_no_step_at_t_mix(render_cli_path, name):
    irs, fs = ensembles.render_ensemble(render_cli_path, scene_path(name), SEED_SEAM, SEAM_R, 48000)
    steps = seam_steps(render_cli_path, name, irs, float(fs))
    single = seam_steps(render_cli_path, name, irs[:1], float(fs))
    gated = name in SEAM_FIXTURES
    # AX21: the hybrid IR's own T30 (octave meter, R = SEAM_R) is reported here, not gated.
    t60 = diag(str(render_cli_path), name)["t60"]
    full = metrics.room_metrics_ensemble(list(irs[:, 0]), float(fs))
    report = {bands.band_key(fc): (None if full["bands"][bands.band_key(fc)]["T30"] is None
                                   else round(rel_pct(full["bands"][bands.band_key(fc)]["T30"], t60[i]), 1))
              for i, fc in enumerate(bands.OCTAVE_BANDS_HZ)}
    print(f"{name}: hybrid-IR T30 vs Eyring (octave meter, R = {SEAM_R}, reported only): {report} %")
    print(f"{name}{'' if gated else ' (reported only)'}: EDC step beyond the expected decay across the "
          f"crossfade, R = {SEAM_R}, [emitter][63 Hz..8 kHz]: {np.round(steps, 2).tolist()} dB; "
          f"one realisation: {np.round(single, 2).tolist()} dB")
    if gated:
        assert np.all(np.abs(steps) <= 1.0), np.round(steps, 2).tolist()


# ---------------------------------------------------------------------------------------------
# Goldens
# ---------------------------------------------------------------------------------------------

GOLDEN_TOLERANCES = {
    "default": {"abs": 0.0, "rel": 0.0},
    "T30": {"rel": 0.01},
    "T20": {"rel": 0.01},
    "EDT": {"rel": 0.01},
    "C50": {"abs": 0.05},
    "C80": {"abs": 0.05},
    "DRR": {"abs": 0.05},
    "D50": {"abs": 0.002},
    "eyring_t60": {"rel": 1e-6},
    "mix_ms": {"rel": 1e-6},
}
NO_LATE_ENERGY_DB = 60.0
ALL_FIXTURES = sorted(p.stem for p in VALID.glob("*.json"))


@pytest.mark.parametrize("name", ALL_FIXTURES)
def test_golden_metrics_hybrid(render_cli_path, name):
    irs, fs = ensembles.render_ensemble(render_cli_path, scene_path(name), load(name)["render"]["tailSeed"], 1, 48000)
    d = diag(str(render_cli_path), name)
    m = metrics.room_metrics(irs[0, 0], float(fs))
    keep = ("EDT", "T20", "T30", "C50", "C80", "D50", "DRR")

    def pinned(values: dict) -> dict:
        out = {n: values[n] for n in keep}
        # A band without late energy (open_field) has an energy ratio that is numerical noise
        # (late energy ~1e-15 of the early: 140 dB on one platform, None or 159 dB on another).
        for n in ("C50", "C80", "DRR"):
            if out[n] is None or out[n] > NO_LATE_ENERGY_DB:
                out[n] = f"no late energy (> {NO_LATE_ENERGY_DB:.0f} dB)"
        return out

    actual = {
        "bands": {
            bands.band_key(fc): {**pinned(m["bands"][bands.band_key(fc)]), "eyring_t60": d["t60"][i]}
            for i, fc in enumerate(bands.OCTAVE_BANDS_HZ)
        },
        "broadband": pinned(m["broadband"]),
        "emitters": {e["id"]: {"mix_ms": 1e3 * e["mixS"]} for e in d["emitters"]},
        "length_samples": int(irs.shape[2]),
    }
    golden.assert_golden(
        f"phase04_{name}_omni",
        actual,
        description=f"Phase 04: hybrid IR (ISM + tail) of tests/scenes/valid/{name}.json, omni, 48 kHz, "
        "emitter channel 0 / output 0, the fixture's own tailSeed",
        tolerances=GOLDEN_TOLERANCES,
    )
