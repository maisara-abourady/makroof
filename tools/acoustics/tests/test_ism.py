"""Phase 03: the image-source model through the real render_cli binary.

- independent cross-check against pyroomacoustics (10 random rooms, first 50 reflections:
  amplitudes relative to the direct sound within +-0.5 dB, arrival times within +-1 sample);
- the first 50 peaks of rendered IRs sit within +-1 sample of the image arrival times, and the
  first 50 dominant arrivals of the fixtures (filterbank active) peak within +-1 sample;
- per-band levels of reflections (a = 0.9 above 1 kHz, 0.1 below) match prod sqrt(1 - a) within
  +-1 dB for orders 1-3 (AX14: measured in each band's central half octave);
- golden metrics of small_room, medium_room and large_hall at order 10.
"""

from __future__ import annotations

import copy
import json
import pathlib

import numpy as np
import pyroomacoustics as pra
import pytest

from tools.acoustics import air, bands, compare, golden, metrics, render_cli, wav

from conftest import REPO

FS = 48000
C = 343.0  # sim::ism::kSpeedOfSoundMps
PRE_ROLL = 32  # sim::kAlignPreRollSamples
VALID = REPO / "tests" / "scenes" / "valid"
SURFACES = ("xMin", "xMax", "yMin", "yMax", "floor", "ceiling")
# pyroomacoustics wall names for the same planes.
PRA_WALLS = {"xMin": "west", "xMax": "east", "yMin": "south", "yMax": "north", "floor": "floor", "ceiling": "ceiling"}


def load(name: str) -> dict:
    return json.loads((VALID / f"{name}.json").read_text(encoding="utf-8"))


def make_scene(dims, listener, emitters, absorption: dict, scattering: float = 0.0, order: int = 10) -> dict:
    """A scene dict. ``absorption`` maps surface -> 8 band values (or one broadband value)."""
    scene = copy.deepcopy(load("medium_room"))
    scene["room"]["geometry"]["dimensions"] = [float(v) for v in dims]
    for s in SURFACES:
        a = absorption[s]
        scene["room"]["surfaces"][s] = {
            "absorption": [float(a)] * 8 if np.isscalar(a) else [float(v) for v in a],
            "scattering": float(scattering),
        }
    scene["listener"]["position"] = [float(v) for v in listener]
    for e, pos in zip(scene["emitters"], emitters):
        e["position"] = [float(v) for v in pos]
    scene["render"]["maxReflectionOrder"] = int(order)
    return scene


def render(binary, tmp_path: pathlib.Path, scene: dict, name: str, *extra: str):
    """IR (channel 0 = emitter 0, output 0) and image list of emitter channel 0."""
    path = tmp_path / f"{name}.json"
    path.write_text(json.dumps(scene), encoding="utf-8")
    result = render_cli.run(
        binary, "--scene", path, "--mode", "omni-early", "--rate", str(FS),
        "--ir", tmp_path / f"{name}.wav", "--images", tmp_path / f"{name}.images.json", *extra,
    )
    assert result.returncode == 0, result.stderr
    ir, fs = wav.read_float32(tmp_path / f"{name}.wav")
    assert fs == FS
    images = json.loads((tmp_path / f"{name}.images.json").read_text(encoding="utf-8"))
    return ir[:, 0].astype(np.float64), images["emitters"][0]["images"]


def kernel(frac: float) -> np.ndarray:
    """The documented fractional-delay kernel (33 taps, Kaiser beta 8, unit sum), reimplemented."""
    if frac == 0.0:
        k = np.zeros(33)
        k[16] = 1.0
        return k
    x = np.arange(-16, 17) - frac
    w = np.i0(8.0 * np.sqrt(np.clip(1.0 - (x / 16.5) ** 2, 0.0, None))) / np.i0(8.0)
    k = np.sinc(x) * w
    return k / k.sum()


def reference_ir(times_samples: np.ndarray, amplitudes: np.ndarray, length: int) -> np.ndarray:
    out = np.zeros(length + 64)
    for t, a in zip(times_samples, amplitudes):
        n = int(np.round(t))
        out[n - 16 + 32 : n + 17 + 32] += a * kernel(t - n)
    return out[32 : 32 + length]


# ---------------------------------------------------------------------------------------------
# pyroomacoustics cross-check
# ---------------------------------------------------------------------------------------------

def _random_room(rng):
    dims = np.array([rng.uniform(3.0, 15.0), rng.uniform(3.0, 15.0), rng.uniform(2.5, 6.0)])
    while True:
        s = rng.uniform(0.5, dims - 0.5)
        l = rng.uniform(0.5, dims - 0.5)
        if np.linalg.norm(s - l) >= 1.0:
            break
    alpha = {name: float(rng.uniform(0.05, 0.6)) for name in SURFACES}
    return dims, s, l, alpha


@pytest.mark.parametrize("seed", range(10))
def test_matches_pyroomacoustics(render_cli_path, tmp_path, seed):
    rng = np.random.default_rng(3000 + seed)
    dims, s, l, alpha = _random_room(rng)
    order = 6
    # Emitter 1 is placed far away from the listener so emitter 0 sets the time alignment.
    far = np.where(l < dims / 2, dims - 0.2, 0.2)
    if np.linalg.norm(far - l) <= np.linalg.norm(s - l):
        far = s  # both at the same place: same alignment
    scene = make_scene(dims, l, [s, far], alpha, order=order)
    ir, ours = render(render_cli_path, tmp_path, scene, "room", "--no-air-absorption")

    room = pra.ShoeBox(
        dims, fs=FS, max_order=order, air_absorption=False, ray_tracing=False, use_rand_ism=False,
        materials={PRA_WALLS[k]: pra.Material(energy_absorption=v) for k, v in alpha.items()},
    )
    room.add_source(s)
    room.add_microphone(l)
    room.image_source_model()
    src = room.sources[0]
    positions = src.images.T.astype(np.float64)
    dist = np.linalg.norm(positions - l, axis=1)
    damping = src.damping[0]
    rel_amp = damping * dist.min() / dist  # relative to the direct path (damping 1)
    t0 = dist.min() / C
    pra_samples = (dist / C - t0) * FS + PRE_ROLL

    # 1. Image list: same images; first 50 reflections by time match in amplitude and time.
    assert len(ours) == positions.shape[0]
    our_pos = np.array([im["position"] for im in ours])
    our_amp = np.array([im["amplitude"][0] for im in ours])
    our_samples = np.array([im["sample"] for im in ours])
    direct = our_amp[0]
    order_idx = np.argsort(pra_samples, kind="stable")
    reflections = [i for i in order_idx if src.orders[i] > 0][:50]
    worst_db, worst_samples = 0.0, 0.0
    for i in reflections:
        j = int(np.argmin(np.linalg.norm(our_pos - positions[i], axis=1)))
        assert np.linalg.norm(our_pos[j] - positions[i]) < 1e-4  # pyroomacoustics stores float32
        db = 20 * np.log10((our_amp[j] / direct) / rel_amp[i])
        worst_db = max(worst_db, abs(db))
        worst_samples = max(worst_samples, abs(our_samples[j] - pra_samples[i]))
    print(f"seed {seed}: image list vs pyroomacoustics: max |amplitude error| {worst_db:.2e} dB, "
          f"max |time error| {worst_samples:.2e} samples")
    assert worst_db <= 0.5
    assert worst_samples <= 1.0

    # 2. Rendered IR: arrival amplitudes (value at the nearest sample of each arrival) of the first
    #    50 reflections match an IR rendered from pyroomacoustics' images, within 0.5 dB; arrivals
    #    closer than 2 samples are taken together (their peaks merge).
    ref = reference_ir(pra_samples, rel_amp * direct, ir.size)
    clusters, current = [], [order_idx[0]]
    for prev, i in zip(order_idx[:-1], order_idx[1:]):
        if pra_samples[i] - pra_samples[prev] < 2.0:
            current.append(i)
        else:
            clusters.append(current)
            current = [i]
    clusters.append(current)
    checked, worst = 0, 0.0
    for cl in clusters[1:]:  # cluster 0 is the direct path
        if checked == 50:
            break
        n = int(np.round(np.mean(pra_samples[cl])))
        if abs(ref[n]) < 1e-3 * direct:  # a cancellation between merged arrivals: nothing to measure
            continue
        worst = max(worst, abs(20 * np.log10(abs(ir[n]) / abs(ref[n]))))
        checked += 1
    residual = np.sum((ir[: ref.size] - ref) ** 2) / np.sum(ref**2)
    print(f"seed {seed}: rendered IR vs pyroomacoustics: {checked} arrivals, max error {worst:.2e} dB, "
          f"residual {10 * np.log10(residual + 1e-300):.1f} dB")
    assert checked == 50
    assert worst <= 0.5


# ---------------------------------------------------------------------------------------------
# Peaks of rendered IRs vs image arrival times (with air absorption: the filterbank is active)
# ---------------------------------------------------------------------------------------------

def _first_peaks(ir: np.ndarray, count: int = 50) -> np.ndarray:
    """The first ``count`` arrival peaks of ``ir`` (sample indices), picked with compare.detect_peaks.

    A band-limited (fractional-delay sinc) arrival also has local maxima of |h| on its sidelobes:
    min_separation = 4 suppresses the first two (1.5 - 2.6 samples out, <= 0.22 of the peak);
    further out a sinc sidelobe is <= 0.09 of its peak, so a candidate below 0.12 of a stronger
    accepted peak within the kernel's reach (16 samples) counts as that peak's sidelobe."""
    candidates = compare.detect_peaks(ir, count=2000, min_separation=4, threshold_db=-40.0)
    accepted: list[int] = []
    for p in sorted(candidates, key=lambda i: -abs(ir[i])):
        if any(abs(p - q) <= 16 and abs(ir[p]) < 0.12 * abs(ir[q]) for q in accepted):
            continue
        accepted.append(int(p))
    return np.sort(np.array(accepted))[:count]


@pytest.mark.parametrize("seed", range(5))
def test_first_50_peaks_match_image_times(render_cli_path, tmp_path, seed):
    """Peak-driven: every one of the first 50 peaks of the rendered IR is within +-1 sample of an
    image arrival time (random rooms of the cross-check: each arrival is the bare kernel)."""
    rng = np.random.default_rng(3000 + seed)
    dims, s, l, alpha = _random_room(rng)
    scene = make_scene(dims, l, [s, s], alpha, order=6)
    ir, images = render(render_cli_path, tmp_path, scene, "room", "--no-air-absorption")
    samples = np.array([im["sample"] for im in images])
    first = _first_peaks(ir)
    assert first.size == 50
    distance = np.array([np.min(np.abs(samples - p)) for p in first])
    print(f"seed {seed}: first 50 peaks, max distance to an image arrival {distance.max():.2f} samples")
    assert np.all(distance <= 1.0), list(zip(first[distance > 1.0], distance[distance > 1.0]))


@pytest.mark.parametrize("name", ["small_room", "medium_room", "large_hall", "asymmetric_materials"])
def test_first_50_arrivals_peak_at_their_time(render_cli_path, tmp_path, name):
    """Arrival-driven, with air absorption and per-band materials (the filterbank is active): for the
    first 50 dominant arrivals (no other arrival within +-8 samples at >= 1/4 of its amplitude), the
    largest |h| within +-3 samples is within +-1 sample of the arrival. Shows that the filterbank's
    group delay is removed and that band filtering doesn't move reflections. A supplement to the
    phase criterion (the test above); small_room is too dense to have 50 dominant arrivals at
    order 10 (it has 41), so >= 40 are required."""
    scene = load(name)
    scene["render"]["maxReflectionOrder"] = 10
    ir, images = render(render_cli_path, tmp_path, scene, name)
    samples = np.array([im["sample"] for im in images])
    amp = np.array([np.sqrt(np.mean(np.square(im["amplitude"]))) for im in images])
    checked, worst = 0, 0.0
    for i in np.argsort(samples, kind="stable"):
        if checked == 50:
            break
        near = (np.abs(samples - samples[i]) <= 8.0) & (np.arange(samples.size) != i)
        if np.any(amp[near] >= 0.25 * amp[i]) or amp[i] < amp[0] * 1e-3:
            continue
        n = int(np.round(samples[i]))
        window = np.abs(ir[n - 3 : n + 4])
        peak = n - 3 + int(np.argmax(window))
        worst = max(worst, abs(peak - samples[i]))
        checked += 1
    print(f"{name}: {checked} arrivals, max |peak - arrival| {worst:.2f} samples")
    assert checked >= 40
    assert worst <= 1.0


# ---------------------------------------------------------------------------------------------
# Per-band levels (AX14)
# ---------------------------------------------------------------------------------------------

BAND_ALPHA = np.array([0.1, 0.1, 0.1, 0.1, 0.1, 0.9, 0.9, 0.9])  # 0.9 above 1 kHz, 0.1 up to 1 kHz


def _two_wall_scene(order: int) -> dict:
    # Only xMin and xMax reflect; everything else is fully absorbing, so the images lie on the
    # x axis and the two images of each order arrive >= 100 ms apart.
    absorption = {s: [1.0] * 8 for s in SURFACES}
    absorption["xMin"] = absorption["xMax"] = list(BAND_ALPHA)
    return make_scene([60.0, 6.0, 4.0], [40.0, 3.0, 2.0], [[10.0, 3.0, 2.0], [10.0, 3.0, 2.0]], absorption, order=order)


def _images_1d(order: int, xs=10.0, xl=40.0, w=60.0):
    """Analytic images of exactly `order` reflections between two parallel walls: (distance, hits)."""
    out = []
    for n in range(-order, order + 1):
        for p in (0, 1):
            hits = abs(n - p) + abs(n)
            if hits == order:
                x = 2 * n * w + (xs if p == 0 else -xs)
                out.append((abs(x - xl), hits))
    return out


def test_per_band_levels_orders_1_to_3(render_cli_path, tmp_path):
    irs = {k: render(render_cli_path, tmp_path, _two_wall_scene(k), f"order{k}")[0] for k in range(4)}
    n = max(len(v) for v in irs.values())
    irs = {k: np.pad(v, (0, n - len(v))) for k, v in irs.items()}
    fc = np.array([bands.exact_centre_hz(f) for f in bands.OCTAVE_BANDS_HZ])
    nominal = np.array(bands.OCTAVE_BANDS_HZ)
    r0 = 30.0
    direct_core = bands.band_energies_fft(irs[0], FS, 0.25)

    worst = 0.0
    for k in (1, 2, 3):
        part = irs[k] - irs[k - 1]  # exactly the order-k images (the renderer is linear)
        measured = bands.band_energies_fft(part, FS, 0.25) / direct_core

        # Expected: the images' pressure spectra (amplitude per band: r0/r * prod sqrt(1-a) * air,
        # relative to the direct path), including the interference of the two images, averaged
        # over the same central half octave.
        expected = np.zeros(8)
        for b in range(8):
            f = np.linspace(fc[b] * 2**-0.25, fc[b] * 2**0.25, 4001)
            spectrum = np.zeros_like(f, dtype=complex)
            for r, hits in _images_1d(k):
                a = (r0 / r) * np.sqrt(1.0 - BAND_ALPHA[b]) ** hits
                a *= air.amplitude(nominal[b], r) / air.amplitude(nominal[b], r0)
                spectrum += a * np.exp(-2j * np.pi * f * (r - r0) / C)
            expected[b] = np.mean(np.abs(spectrum) ** 2)
        error = 10 * np.log10(measured / expected)
        plain = 20 * np.log10(np.sqrt(1.0 - BAND_ALPHA) ** k)

        # For information: the full-octave Butterworth meter (bands.py) on the same response.
        butter = np.array([
            np.sum(bands.filter_band_with_lead(part, FS, f)[0] ** 2) / np.sum(bands.filter_band_with_lead(irs[0], FS, f)[0] ** 2)
            for f in bands.OCTAVE_BANDS_HZ
        ])
        butter_error = 10 * np.log10(butter / expected)
        print(f"order {k}: prod sqrt(1-a) = {np.round(plain, 2)} dB")
        print(f"  error, central half octave (AX14): {np.round(error, 3)} dB")
        print(f"  error, Butterworth octave meter (info): {np.round(butter_error, 2)} dB")
        worst = max(worst, float(np.max(np.abs(error))))
    assert worst <= 1.0


def test_band_selectivity_seen_by_the_meters(render_cli_path, tmp_path):
    """For information and as a guard on AX14: a reflection whose bands differ by 28.6 dB (order 3
    of the a = 0.9 / 0.1 room) is still resolved in the central half octave, and the full-octave
    FFT meter shows the crossover leakage that AX14 is about (2 kHz band reads high)."""
    ir0 = render(render_cli_path, tmp_path, _two_wall_scene(0), "o0")[0]
    ir3 = render(render_cli_path, tmp_path, _two_wall_scene(3), "o3")[0]
    ir2 = render(render_cli_path, tmp_path, _two_wall_scene(2), "o2")[0]
    n = max(ir0.size, ir2.size, ir3.size)
    ir0, ir2, ir3 = (np.pad(x, (0, n - x.size)) for x in (ir0, ir2, ir3))
    part = ir3 - ir2
    core = 10 * np.log10(bands.band_energies_fft(part, FS, 0.25) / bands.band_energies_fft(ir0, FS, 0.25))
    full = 10 * np.log10(bands.band_energies_fft(part, FS, 0.5) / bands.band_energies_fft(ir0, FS, 0.5))
    print(f"order 3, central half octave: {np.round(core, 1)} dB; full octave: {np.round(full, 1)} dB")
    assert core[4] - core[5] > 25.0  # 1 kHz vs 2 kHz: the 28.6 dB step is resolved
    assert full[5] - core[5] > 3.0  # the full octave can't see it: leakage from the 1 kHz band


# ---------------------------------------------------------------------------------------------
# Goldens
# ---------------------------------------------------------------------------------------------

# Same-platform renders are bit-identical; the tolerances absorb float differences across OSes
# (compilers, libm) in the IR and in the analysis. Counts and sample indices are exact.
GOLDEN_TOLERANCES = {
    "default": {"abs": 0.0, "rel": 0.0},
    "C50": {"abs": 0.05},
    "C80": {"abs": 0.05},
    "DRR": {"abs": 0.05},
    "D50": {"abs": 0.002},
    "energy_db": {"abs": 0.05},
}


def golden_metrics(ir: np.ndarray, fs: float, images: list) -> dict:
    m = metrics.room_metrics(ir, fs)
    keep = ("C50", "C80", "D50", "DRR")
    energy = bands.band_energies_fft(ir, fs, 0.5)
    out = {"bands": {}, "broadband": {name: m["broadband"][name] for name in keep if name in m["broadband"]}}
    for f, e in zip(bands.OCTAVE_BANDS_HZ, energy):
        key = bands.band_key(f)
        out["bands"][key] = {name: m["bands"][key][name] for name in keep if name in m["bands"][key]}
        out["bands"][key]["energy_db"] = float(10 * np.log10(e))
    out["length_samples"] = int(ir.size)
    out["image_count"] = len(images)
    out["first_peaks"] = [int(p) for p in _first_peaks(ir, 10)]
    return out


@pytest.mark.parametrize("name", ["small_room", "medium_room", "large_hall"])
def test_golden_metrics_order_10(render_cli_path, tmp_path, name):
    scene = load(name)
    scene["render"]["maxReflectionOrder"] = 10
    ir, images = render(render_cli_path, tmp_path, scene, name)
    actual = golden_metrics(ir, FS, images)
    golden.assert_golden(
        f"phase03_{name}_omni_order10",
        actual,
        description=f"Phase 03: early-reflection (ISM) IR of tests/scenes/valid/{name}.json at order 10, "
        "omni, 48 kHz, emitter L / output 0",
        tolerances=GOLDEN_TOLERANCES,
    )
