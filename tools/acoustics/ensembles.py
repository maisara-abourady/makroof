"""Phase 04: ensembles of hybrid IRs and the rules that size them (BUILD_PLAN AX11, AX19, AX23).

- ``render_ensemble``: R realisations of a scene's omni hybrid IR (or of its tail alone) with
  consecutive ``tailSeed``s, from one ``render_cli --ensemble`` call.
- ``r_t30``: AX11's ensemble size R >= (sigma1 / (tol / 3))^2 with sigma1 from AX11's measured
  single-realisation T30 scatter of noise x exp (48 kHz), as phase-04.md "Ensemble sizes" applies it.
- ``r_two_ensembles``: R >= 9 (sigma_a^2 + sigma_b^2) / tol^2 for comparing two ensemble means (AX19).
- ``t30_half_octave_ensemble``: the AX23 meter for the Eyring gate at 1-8 kHz: each realisation's
  pressure IR, aligned at its onset, is filtered by a linear-phase Kaiser FIR that passes the band's
  central half octave (base-2 centre * 2^+-1/4) and stops from 2^+-3/8 (80 dB); the squared outputs
  are averaged over the ensemble, then Lundeby + Schroeder as in ``metrics``.
"""

from __future__ import annotations

import json
import math
import os
import pathlib
import tempfile

import numpy as np
import scipy.signal as sg

from . import bands, metrics, render_cli, wav

# AX11: measured sigma1(T30) in % of white noise x exp at 48 kHz, per band, at T60 0.3 / 1.0 / 6 s.
AX11_T60_COLUMNS_S = (0.3, 1.0, 6.0)
AX11_SIGMA1_PCT = {
    63.0: (18.0, 8.0, 3.0),
    125.0: (10.0, 6.7, 1.8),
    250.0: (8.0, 4.4, 1.3),
    500.0: (6.0, 2.7, 1.2),
    1000.0: (3.4, 1.5, 0.5),
    2000.0: (2.7, 1.4, 0.3),
    4000.0: (1.9, 1.0, 0.5),
    8000.0: (1.3, 1.0, 0.3),
}

# AX23: bands read in the central half octave in the Eyring gate (63-500 Hz: bands.py octaves).
HALF_OCTAVE_BANDS_HZ = (1000.0, 2000.0, 4000.0, 8000.0)


def r_t30(band_hz: float, t60_s: float, tol_pct: float) -> int:
    """AX11 / phase-04.md: R >= (sigma1 / (tol / 3))^2, sigma1 from the column at or just below
    T60_b; below 0.3 s, R (not sigma1) scales by 0.3 s / T60_b. ``tol_pct`` is the tolerance on one
    ensemble (the seed and sample-rate gates pass tol / sqrt(2))."""
    columns = AX11_T60_COLUMNS_S
    sigmas = AX11_SIGMA1_PCT[float(band_hz)]
    if t60_s < columns[0]:
        base = (sigmas[0] / (tol_pct / 3.0)) ** 2
        return math.ceil(base * columns[0] / t60_s - 1e-9)
    i = max(k for k, c in enumerate(columns) if c <= t60_s)
    return math.ceil((sigmas[i] / (tol_pct / 3.0)) ** 2 - 1e-9)


def r_seed_gate(band_hz: float, t60_s: float) -> int:
    """Seed gate (and sample-rate T30 gate): two ensembles within +-2 %, R per ensemble with tol / sqrt(2)."""
    return r_t30(band_hz, t60_s, 2.0 / math.sqrt(2.0))


def r_two_ensembles(sigma_a: float, sigma_b: float, tol: float) -> int:
    """AX19: R >= 9 (sigma_a^2 + sigma_b^2) / tol^2 per ensemble (same units for sigma and tol)."""
    return max(1, math.ceil(9.0 * (sigma_a**2 + sigma_b**2) / tol**2 - 1e-9))


def render_ensemble(
    binary: pathlib.Path,
    scene: dict | pathlib.Path,
    first_seed: int,
    count: int,
    rate: int = 48000,
    tail_only: bool = False,
    work_dir: pathlib.Path | None = None,
    emitter: int | None = None,
) -> tuple[np.ndarray, int]:
    """IRs of ``count`` realisations, seeds first_seed ... first_seed + count - 1:
    array (count, 2, n) = (realisation, emitter channel, sample) of output 0, float64. With
    ``emitter`` given only that channel is built (the other is all zeros)."""
    with tempfile.TemporaryDirectory(dir=work_dir) as tmp:
        tmp = pathlib.Path(tmp)
        if isinstance(scene, dict):
            path = tmp / "scene.json"
            path.write_text(json.dumps(scene), encoding="utf-8")
        else:
            path = pathlib.Path(scene)
        out = tmp / "ensemble.wav"
        args = ["--scene", path, "--mode", "omni", "--rate", str(rate), "--tail-seed", str(first_seed),
                "--ensemble", str(count), "--ir", out]
        if tail_only:
            args.append("--tail-only")
        if emitter is not None:
            args += ["--ensemble-emitter", str(emitter)]
        result = render_cli.run(binary, *args)
        if result.returncode != 0:
            raise RuntimeError(f"render_cli failed ({result.returncode}): {result.stderr}")
        data, fs = wav.read_float32(out)
    data = np.asarray(data, dtype=np.float64).T  # (channels, n)
    if emitter is None:
        return data.reshape(count, 2, -1), fs
    out = np.zeros((count, 2, data.shape[1]))
    out[:, emitter, :] = data
    return out, fs


def diagnostics(binary: pathlib.Path, scene: dict | pathlib.Path, rate: int = 48000) -> dict:
    """render_cli --diagnostics of the hybrid omni IR."""
    with tempfile.TemporaryDirectory() as tmp:
        tmp = pathlib.Path(tmp)
        if isinstance(scene, dict):
            path = tmp / "scene.json"
            path.write_text(json.dumps(scene), encoding="utf-8")
        else:
            path = pathlib.Path(scene)
        out = tmp / "diag.json"
        result = render_cli.run(binary, "--scene", path, "--mode", "omni", "--rate", str(rate), "--diagnostics", out)
        if result.returncode != 0:
            raise RuntimeError(f"render_cli failed ({result.returncode}): {result.stderr}")
        return json.loads(out.read_text(encoding="utf-8"))


def half_octave_fir(nominal_hz: float, fs: float) -> np.ndarray:
    """AX23: linear-phase Kaiser band-pass, pass band base-2 centre * 2^+-1/4, stop band from
    2^+-3/8 (or 0.999 Nyquist), 80 dB; odd length, centred."""
    fc = bands.exact_centre_hz(nominal_hz)
    lo, hi = fc * 2.0**-0.25, fc * 2.0**0.25
    stop_lo, stop_hi = fc * 2.0**-0.375, min(fc * 2.0**0.375, 0.4995 * fs)
    transition = min(lo - stop_lo, stop_hi - hi)
    attenuation = 80.0
    numtaps = int(math.ceil((attenuation - 8.0) / (2.285 * 2.0 * math.pi * transition / fs))) | 1
    beta = 0.1102 * (attenuation - 8.7)
    return sg.firwin(numtaps, [0.5 * (lo + stop_lo), 0.5 * (hi + stop_hi)], pass_zero=False, fs=fs,
                     window=("kaiser", beta))


def band_metrics_half_octave_ensemble(irs: np.ndarray, fs: float, nominal_hz: float) -> dict:
    """AX23 meter: metrics (``metrics._band_metrics`` format) of the ensemble-averaged energy of the
    onset-aligned IRs, each filtered by ``half_octave_fir`` before squaring."""
    taps = half_octave_fir(nominal_hz, fs)
    half = taps.size // 2
    aligned = [np.asarray(h, dtype=np.float64)[metrics.onset_index(h):] for h in irs]
    length = min(a.size for a in aligned)
    energy = np.zeros(length + taps.size - 1)
    for a in aligned:
        energy += sg.fftconvolve(a[:length], taps) ** 2
    energy /= len(aligned)
    return metrics._band_metrics(np.empty(0), fs, half, half, energy=energy, lead=half)


def eyring_t30_readings(irs: np.ndarray, fs: float, bands_hz=bands.OCTAVE_BANDS_HZ) -> dict:
    """T30 per band for the Eyring gate (AX23): half octave for 1-8 kHz, bands.py octaves below.
    Returns {band_key: {"T30": value, "meter": "half-octave" | "octave", "octave_T30": value}}."""
    octave = metrics.room_metrics_ensemble(list(irs), fs, tuple(bands_hz))
    out = {}
    for fc in bands_hz:
        key = bands.band_key(fc)
        octave_t30 = octave["bands"][key]["T30"]
        if float(fc) in HALF_OCTAVE_BANDS_HZ:
            value = band_metrics_half_octave_ensemble(irs, fs, fc)["T30"]
            out[key] = {"T30": value, "meter": "half-octave", "octave_T30": octave_t30}
        else:
            out[key] = {"T30": octave_t30, "meter": "octave", "octave_T30": octave_t30}
    return out


def sigma1(values: list[float | None], relative: bool) -> float | None:
    """Single-realisation scatter: sample standard deviation (ddof 1), in % of the mean if relative."""
    v = np.array([x for x in values if x is not None], dtype=np.float64)
    if v.size < 2 or v.size < len(values):
        return None
    s = float(np.std(v, ddof=1))
    return 100.0 * s / float(np.mean(v)) if relative else s


def cache_dir() -> pathlib.Path | None:
    value = os.environ.get("SPATIAL_ENSEMBLE_TMP")
    return pathlib.Path(value) if value else None


class EnsembleAccumulator:
    """Streaming form of ``metrics.room_metrics_ensemble`` (and of the AX23 half-octave meter) for
    ensembles too large to hold in memory: add IRs in chunks, then read the metrics of the
    ensemble-averaged band energies. Same method: each IR aligned at its own onset, band-filtered
    (``bands.filter_band_with_lead``, or ``half_octave_fir``), squared and averaged; the direct index
    is the mean of the per-IR direct indices. All IRs are cut to ``length`` samples after their
    onset (default: the first IR's length minus 20 ms, so later onsets still fit)."""

    def __init__(self, fs: float, octave_bands=bands.OCTAVE_BANDS_HZ, half_octave_bands=(), length: int | None = None):
        self.fs = float(fs)
        self.octave_bands = tuple(float(f) for f in octave_bands)
        self.half_octave_bands = tuple(float(f) for f in half_octave_bands)
        self.length = length
        self.count = 0
        self._directs: list[int] = []
        self._octave: dict[float, np.ndarray] = {}
        self._leads: dict[float, int] = {}
        self._half: dict[float, np.ndarray] = {}
        self._taps = {f: half_octave_fir(f, self.fs) for f in self.half_octave_bands}

    def add(self, h: np.ndarray) -> None:
        h = np.asarray(h, dtype=np.float64)
        onset = metrics.onset_index(h)
        half = int(round(metrics.DIRECT_HALF_WINDOW_S * self.fs))
        if self.length is None:
            self.length = h.size - onset - int(round(0.020 * self.fs))
        if h.size - onset < self.length:
            raise ValueError("IR too short after its onset for this ensemble's length")
        a = h[onset : onset + self.length]
        self._directs.append(int(np.argmax(np.abs(a[: half + 1]))))
        for fc in self.octave_bands:
            y, lead = bands.filter_band_with_lead(a, self.fs, fc)
            e = y**2
            self._leads[fc] = lead
            self._octave[fc] = e if fc not in self._octave else self._octave[fc] + e
        for fc in self.half_octave_bands:
            e = sg.fftconvolve(a, self._taps[fc]) ** 2
            self._half[fc] = e if fc not in self._half else self._half[fc] + e
        self.count += 1

    def add_all(self, irs) -> None:
        for h in irs:
            self.add(h)

    def octave(self, nominal_hz: float) -> dict:
        fc = float(nominal_hz)
        direct = int(round(float(np.mean(self._directs))))
        lead = self._leads[fc]
        return metrics._band_metrics(np.empty(0), self.fs, lead, direct + lead, energy=self._octave[fc] / self.count,
                                     lead=lead, band_hz=fc)

    def half_octave(self, nominal_hz: float) -> dict:
        fc = float(nominal_hz)
        half = self._taps[fc].size // 2
        return metrics._band_metrics(np.empty(0), self.fs, half, half, energy=self._half[fc] / self.count, lead=half)

    def octave_energy(self, nominal_hz: float) -> tuple[np.ndarray, int]:
        """Ensemble-averaged squared band signal and its lead (samples before the onset)."""
        fc = float(nominal_hz)
        return self._octave[fc] / self.count, self._leads[fc]


def accumulate(binary, scene, first_seed: int, count: int, rate: int, tail_only: bool, acc: EnsembleAccumulator,
               emitters=(0,), chunk: int = 64, work_dir=None) -> EnsembleAccumulator:
    """Render ``count`` realisations in chunks and add the given emitter channels' IRs to ``acc``."""
    only = emitters[0] if len(emitters) == 1 else None
    for first in range(0, count, chunk):
        n = min(chunk, count - first)
        irs, _ = render_ensemble(binary, scene, first_seed + first, n, rate, tail_only, work_dir, emitter=only)
        for r in range(n):
            for e in emitters:
                acc.add(irs[r, e])
    return acc
