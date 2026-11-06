"""Phase-05 scope 7 meter tasks (AX23 and Lundeby; decider D1, D5, D7, E1, E3, G5-4, N1).

- ``leak_calibration``: octave-filter leakage bias of T30 against a known neighbour ratio r,
  for both meters (bands.py octave and the AX23(b) half-octave Kaiser FIR), with the measured
  leak D, D1 = D + 10 log10 r and the interrogator's two-term model prediction (Kuttruff
  Eqs. 3.64-3.68 basis). Reported, not gated; results go into AX23 and the Phase 05 report.
- ``paired_noise_test``: the measured-IR path of ``run_validation.py`` (decay + stationary noise,
  BRAS-like 3.5 s file with the last 1024 samples Hann-faded, fade trimmed, then metrics) against
  the same realisation without noise, Schroeder-integrated to the end of the file. Case A gates
  |mean paired T30 bias| <= 0.6 % with SE <= 0.15 % (tests/test_noise_handling.py); case B is
  reported.
- ``simulated_edc_check``: a noise-free exponential decay ending at -90 dB through the metrics
  path (Lundeby truncation + compensation) against plain integration to the end (N1).

Every random draw is seeded, so the results are deterministic.
"""

from __future__ import annotations

import math

import numpy as np

from . import bands, ensembles, metrics

BRAS_FS = 44100.0
BRAS_FADE = 1024  # BRAS RIRs end in 1024 Hann-faded samples (BRAS documentation §3.4.1)
LN_1000 = 6.907755278982137  # ln(1000): amplitude exp(-LN_1000 t / T) falls 60 dB in T


# ------------------------------------------------------------------------------------------
# Two-term model (decider E1; interrogator's model on the Kuttruff Eqs. 3.64-3.68 basis)
# ------------------------------------------------------------------------------------------


def two_term_bias(r: float, d_db: float) -> float:
    """Octave T30 bias predicted for a band whose slower neighbour (T ratio r) leaks with
    D = 10 log10(E_own / E_leak): E(x) = e^-x + a e^(-x/r), a = 10^(-D/10), x = 2 delta t,
    T30 window x = 1.15 ... 8.06; T_read/T_b = 1 / (1 - Delta),
    Delta = [ln(1 + q2) - ln(1 + q1)] / 6.91, q = a e^(k x), k = (r - 1)/r. Returns T_read/T_b - 1."""
    if r <= 1.0:
        return 0.0
    a = 10.0 ** (-d_db / 10.0)
    k = (r - 1.0) / r
    x1, x2 = 0.5 * math.log(10) , 3.5 * math.log(10)  # -5 dB and -35 dB of e^-x: 1.151, 8.059
    q1, q2 = a * math.exp(k * x1), a * math.exp(k * x2)
    delta = (math.log1p(q2) - math.log1p(q1)) / LN_1000
    return 1.0 / (1.0 - delta) - 1.0


# ------------------------------------------------------------------------------------------
# Synthetic multi-band decays
# ------------------------------------------------------------------------------------------


def _brickwall_noise(rng, n: int, fs: float, nominal_hz: float) -> np.ndarray:
    """Unit-power white noise band-limited by an ideal FFT brick wall to f * 2^(+-1/2)."""
    f0 = bands.exact_centre_hz(nominal_hz)
    spec = np.fft.rfft(rng.standard_normal(n))
    f = np.fft.rfftfreq(n, 1.0 / fs)
    spec[(f < f0 * 2 ** -0.5) | (f >= f0 * 2 ** 0.5)] = 0.0
    x = np.fft.irfft(spec, n)
    return x / math.sqrt(np.mean(x**2))


def multiband_components(rng, n: int, fs: float, t60_by_band: dict[float, float]) -> dict[float, np.ndarray]:
    """One realisation per octave component: band-limited noise x exp(-6.91 t / T_band), equal
    start power (product choice, phase-05 scope 7)."""
    t = np.arange(n) / fs
    return {fc: _brickwall_noise(rng, n, fs, fc) * np.exp(-LN_1000 * t / T) for fc, T in t60_by_band.items()}


def _octave_energy(x: np.ndarray, fs: float, fc: float) -> np.ndarray:
    y, lead = bands.filter_band_with_lead(x, fs, fc)
    return y**2, lead


def leak_calibration(fc_list=(500.0, 1000.0, 2000.0, 4000.0, 8000.0), ratios=(1.0, 1.05, 1.1, 1.2, 1.3, 1.5, 2.0),
                     t_b: float = 1.0, fs: float = 48000.0, r_count=None, seed: int = 5050, log=None) -> list[dict]:
    """Both meters' T30 bias, leak D and the model check per (f_c, variant, r).

    Variants: the slower neighbour below the band ('below') and above it ('above'); all other
    octave components at t_b. Ensemble size per f_c from AX11's sigma1 ~ 0.5/sqrt(B T) for
    SE <= 0.2 %: R = max(51, ceil((sigma1 / 0.2)^2)) (``r_count`` overrides, for tests)."""
    out = []
    all_bands = bands.OCTAVE_BANDS_HZ
    for fc in fc_list:
        i = all_bands.index(fc)
        bw = bands.band_edges_hz(fc)[1] - bands.band_edges_hz(fc)[0]
        sigma1_pct = 100 * 0.5 / math.sqrt(bw * t_b)
        R = r_count or max(51, math.ceil((sigma1_pct / 0.2) ** 2))
        for variant in ("below", "above"):
            j = i - 1 if variant == "below" else i + 1
            if j < 0 or j >= len(all_bands):
                continue
            nb = all_bands[j]
            for r in ratios:
                t60 = {f: t_b for f in all_bands}
                t60[nb] = r * t_b
                n = int((1.5 * 1.5 * max(t60.values()) + 0.3) * fs)  # to beyond -90 dB of the slowest
                rng = np.random.default_rng(seed + int(fc) * 1000 + (0 if variant == "below" else 7) * 100 + int(r * 100))
                acc_oct = None
                hal = []
                e_own = e_leak = 0.0
                for _ in range(R):
                    comps = multiband_components(rng, n, fs, t60)
                    x = sum(comps.values())
                    e, lead = _octave_energy(x, fs, fc)
                    acc_oct = e if acc_oct is None else acc_oct + e
                    e_own += float(np.sum(_octave_energy(comps[fc], fs, fc)[0]))
                    e_leak += float(np.sum(_octave_energy(comps[nb], fs, fc)[0]))
                    hal.append(x)
                    if len(hal) == 16:
                        hal = [np.stack(hal)]
                m_oct = metrics._band_metrics(np.empty(0), fs, lead, lead, energy=acc_oct / R, lead=lead, band_hz=fc)
                irs = np.concatenate([h if h.ndim == 2 else h[None, :] for h in hal]) if hal else None
                m_half = ensembles.band_metrics_half_octave_ensemble(irs, fs, fc) if fc >= 1000 else None
                d_db = 10 * math.log10(e_own / e_leak)
                row = {
                    "f_c": fc, "variant": variant, "r": r, "R": R,
                    "octave_bias_pct": _pct(m_oct["T30"], t_b),
                    "half_octave_bias_pct": _pct(m_half["T30"], t_b) if m_half else None,
                    "D_dB": d_db, "D1_dB": d_db + 10 * math.log10(r),
                    "model_bias_pct": 100 * two_term_bias(r, d_db),
                }
                row["residual_pct"] = None if row["octave_bias_pct"] is None else row["octave_bias_pct"] - row["model_bias_pct"]
                out.append(row)
                if log:
                    log(row)
    return out


def _pct(t, ref):
    return None if t is None else 100.0 * (t / ref - 1.0)


# ------------------------------------------------------------------------------------------
# Paired noise test (D5, E3)
# ------------------------------------------------------------------------------------------


def _hann_fade(x: np.ndarray, n_fade: int) -> np.ndarray:
    y = x.copy()
    w = 0.5 * (1 + np.cos(np.pi * np.arange(1, n_fade + 1) / n_fade))  # 1 -> 0
    y[-n_fade:] *= w
    return y


def trim_bras_fade(h: np.ndarray) -> np.ndarray:
    """Drop the documented final 1024 Hann-faded samples of a BRAS RIR (decider D6)."""
    return np.asarray(h)[:-BRAS_FADE]


def _schroeder_to_end_t30(e: np.ndarray, onset: int, fs: float) -> float | None:
    edc = metrics.schroeder_edc(e[onset:], e[onset:].size, 0.0)
    return metrics.decay_time(edc, fs, -5.0, -35.0)


def paired_noise_condition(fc: float, t60: float, noise_below_db: float, R: int, seed: int,
                           fs: float = BRAS_FS, length_s: float = 3.5) -> dict:
    """Paired T30 bias of the measured-IR path for one condition (per realisation
    bias_i = T30_noisy,i / T30_clean,i - 1). EDT and C80 are reported too."""
    rng = np.random.default_rng(seed)
    n = int(round(length_s * fs))
    t = np.arange(n) / fs
    pre = int(0.005 * fs)  # a few ms of lead-in before the decay starts
    env = np.exp(-LN_1000 * np.maximum(t - pre / fs, 0) / t60) * (t >= pre / fs)
    biases, edt_d, c80_d, unsuitable = [], [], [], 0
    for _ in range(R):
        decay = rng.standard_normal(n) * env
        decay[pre] = 0.0
        # noise level per band: white noise is flat, so the broadband ratio is the band ratio
        p0 = 1.0  # decay power at t0 (unit-variance carrier)
        noise = rng.standard_normal(n) * math.sqrt(p0 * 10 ** (-noise_below_db / 10))
        noisy = trim_bras_fade(_hann_fade(decay + noise, BRAS_FADE))
        clean = decay
        # noisy arm: the metrics path, octave band
        yb, lead = bands.filter_band_with_lead(noisy, fs, fc)
        onset = metrics.onset_index(noisy) + lead
        mn = metrics._band_metrics(yb, fs, onset, onset, lead=lead, band_hz=fc)
        # clean arm: same band filter, Schroeder to the end of the file (N1)
        yc, lead_c = bands.filter_band_with_lead(clean, fs, fc)
        onset_c = metrics.onset_index(clean) + lead_c
        t_clean = _schroeder_to_end_t30(yc**2, onset_c, fs)
        if mn["T30"] is None or t_clean is None:
            unsuitable += 1
            continue
        biases.append(mn["T30"] / t_clean - 1.0)
        mc = metrics._band_metrics(yc, fs, onset_c, onset_c, lead=lead_c, band_hz=fc)
        if mn["EDT"] and mc["EDT"]:
            edt_d.append(mn["EDT"] / mc["EDT"] - 1.0)
        if mn["C80"] is not None and mc["C80"] is not None:
            c80_d.append(mn["C80"] - mc["C80"])
    b = np.array(biases) * 100
    return {
        "f_c": fc, "T": t60, "noise_below_dB": noise_below_db, "R": R, "unsuitable": unsuitable,
        "mean_bias_pct": float(b.mean()) if b.size else None,
        "sd_pct": float(b.std(ddof=1)) if b.size > 1 else None,
        "se_pct": float(b.std(ddof=1) / math.sqrt(b.size)) if b.size > 1 else None,
        "edt_mean_pct": float(100 * np.mean(edt_d)) if edt_d else None,
        "c80_mean_dB": float(np.mean(c80_d)) if c80_d else None,
    }


CASE_A = [(fc, T, L) for fc in (500.0, 1000.0, 2000.0) for T in (1.0, 2.0) for L in (48.0, 55.0, 65.0)]
CASE_B = [(125.0, 0.3, L) for L in (48.0, 55.0, 65.0)]


def paired_noise_test(conditions=CASE_A, pilot: int = 51, se_target_pct: float = 0.15, seed: int = 7070, log=None,
                      r_max: int = 2000) -> list[dict]:
    """Pilot n >= 51 per condition, then R = max(51, ceil((sigma1 / 0.15)^2)); the pilot seeds
    count towards R (the run is repeated with R realisations from the same seed). R is capped at
    ``r_max`` (case B, reported only, is far from Gaussian in the plateau regime)."""
    out = []
    for k, (fc, T, L) in enumerate(conditions):
        s = seed + 1000 * k
        res = paired_noise_condition(fc, T, L, pilot, s)
        if res["sd_pct"] is not None:
            R = min(r_max, max(pilot, math.ceil((res["sd_pct"] / se_target_pct) ** 2)))
            if R > pilot:
                res = paired_noise_condition(fc, T, L, R, s)
        out.append(res)
        if log:
            log(res)
    return out


# ------------------------------------------------------------------------------------------
# Simulated EDC (N1)
# ------------------------------------------------------------------------------------------


def simulated_edc_check(fs: float = 48000.0, t60: float = 1.0, fc: float = 1000.0, seed: int = 9) -> dict:
    """A noise-free exponential decay ending at -90 dB: EDC at -35 dB from the metrics path
    (Lundeby truncation + compensation) against integration to the end of the IR (N1)."""
    rng = np.random.default_rng(seed)
    n = int(round(1.5 * t60 * fs))  # -90 dB at 1.5 T60
    t = np.arange(n) / fs
    h = rng.standard_normal(n) * np.exp(-LN_1000 * t / t60)
    y, lead = bands.filter_band_with_lead(h, fs, fc)
    onset = metrics.onset_index(h) + lead
    e = (y**2)[onset:]
    lb = metrics.lundeby(e, fs)
    edc_m = metrics.schroeder_edc(e, lb.crosspoint, lb.compensation)
    edc_end = metrics.schroeder_edc(e, e.size, 0.0)
    i35 = int(np.flatnonzero(edc_end <= -35.0)[0])
    return {"edc_metrics_dB": float(edc_m[i35]), "edc_to_end_dB": float(edc_end[i35]),
            "difference_dB": float(edc_m[i35] - edc_end[i35]), "crosspoint_s": lb.crosspoint / fs}
