# Acoustic metrics and validation data (K5)

Reference file of the `review-phase-pr` skill. Scope: ISO 3382-1 metric code (tools/acoustics), golden files, IR comparison, click detector, pyroomacoustics as second opinion, BRAS validation (Phase 05), loudness (BS.1770). Phases 02, 03, 04, 05, 09, 10, 12.

How to use it: read the "Reviewer's checklist" section first and apply the questions the diff makes
relevant; use the earlier sections to settle a disagreement with the author or to re-derive a number.
Every fact carries its source URL and the date it was verified (researched live on 2026-11-04).
Facts marked "(unverified, from memory)" must be verified before they are cited in a review; when
you verify one, fix it here. See `knowledge-inventory.md` for which facts go stale and how to
re-check them.

## Contents

- 1. ISO 3382-1:2009 parameter definitions
  - 1.1 Reverberation time family (clause 3.5 and clause 6)
  - 1.2 Required dynamic range / SNR
  - 1.3 Energy-ratio parameters (Annex A; formulas from memory, confirmed by ODEON paper text)
  - 1.4 JND values (ISO 3382-1 Annex A, as reproduced by ODEON's ISRA 2013 Table 1)
- 2. Schroeder backward integration and noise-floor handling
  - 2.1 Formula
  - 2.2 The truncation problem and the compensation term C
  - 2.3 Lundeby's method (Lundeby, Vigran, Bietz, Vorländer, Acustica 81(4):344-355, 1995)
  - 2.4 The simpler "-10 dB above noise" truncation
  - 2.5 Typical implementation mistakes (each one has bitten real code)
  - 2.6 Octave-band filtering of short decays (filter ringing, the BT rule)
- 3. Octave-band filters per IEC 61260-1:2014
- 4. Second-opinion implementations
  - 4.1 `pyroomacoustics.experimental.rt60.measure_rt60` (source read 2026-11-04)
  - 4.2 python-acoustics `acoustics.room.t60_impulse(file_name, bands, rt='t30')`
  - 4.3 pyrato (pyfar family)
- 5. Click/discontinuity detection for time-varying audio tests
- 6. BRAS and the simulation round robins
  - 6.1 Hosting, licence, versions
  - 6.2 Contents (Documentation.pdf, accessed 2026-11-04)
  - 6.3 Round-robin accuracy figures (what a reviewer should expect)
- 7. Loudness: ITU-R BS.1770 and pyloudnorm
- 8. Pitfalls when comparing a simulated IR to a measured IR
- 9. Reviewer's checklist (metrics code, goldens, comparison scripts, validation reports)
- Appendix: quick formulas (plain text)

---

Scope: ISO 3382-1 metric code (`tools/acoustics/metrics.py`, Phase 02), golden files, IR
comparison scripts, click detector, and the BRAS validation of Phase 05. All facts carry a source
URL and the access date (all accessed 2026-11-04 unless stated). Anything I could not confirm
against a live source is marked **(unverified, from memory)**. Repo context read first:
`/home/user/makroof/docs/phases/phase-02.md` and `phase-05.md`.

Sources I actually opened (text extracted with `pdftotext`):
- ISO 3382-1:2009 preview (first 12 pages, clauses 1-5): https://cdn.standards.iteh.ai/samples/40979/b0e9f87f3d9f4df6b18f767e3439bfb6/ISO-3382-1-2009.pdf
- Rindel/Christensen, "The ISO 3382 parameters: Can we simulate them? Can we measure them?", ISRA 2013: https://www.odeon.dk/pdf/ISRA2013_Paper_The%20ISO%203382%20parameters_Can%20we%20simulate%20them_Can%20we%20measure%20them_24July2013.pdf
- Brinkmann et al., "A round robin on room acoustical simulation and auralization", JASA 145(4) 2746-2760, 2019, open-access copy: https://depositonce.tu-berlin.de/bitstreams/1bd07cea-0ad8-4e90-9e17-be9dec102e15/download (redirects to api-depositonce.tu-berlin.de)
- BRAS documentation PDF: https://depositonce.tu-berlin.de/bitstreams/ba6b4f29-418b-4ec8-bb9d-72d488b8e5e6/download
- BRAS DepositOnce record: https://depositonce.tu-berlin.de/items/38410727-febb-4769-8002-9c710ba393c4
- Vorländer, "Performance of computer simulations for architectural acoustics", ICA 2010: https://www.acoustics.asn.au/conference_proceedings/ICA2010/cdrom-ICA2010/papers/p76.pdf
- ITU-R BS.1770-5 (11/2023): https://www.itu.int/dms_pubrec/itu-r/rec/bs/R-REC-BS.1770-5-202311-I!!PDF-E.pdf
- pyroomacoustics `experimental/rt60.py` (master): https://raw.githubusercontent.com/LCAV/pyroomacoustics/master/pyroomacoustics/experimental/rt60.py
- python-acoustics `acoustics/room.py` (master): https://raw.githubusercontent.com/python-acoustics/python-acoustics/master/acoustics/room.py
- pyrato `pyrato/edc.py` (main; Lundeby implementation): https://raw.githubusercontent.com/pyfar/pyrato/main/pyrato/edc.py
- IS 6964:2001 = IEC 61260:1995 reprint (Table 1 tolerances): https://law.resource.org/pub/in/bis/S04/is.6964.2001.pdf
- NTi octave-band table (IEC 61260-1:2014 base-10): https://www.nti-audio.com/en/support/know-how/fractional-octave-band-filter
- python-acoustics `standards/iec_61260_1_2014.py`: http://python-acoustics.github.io/python-acoustics/_modules/acoustics/standards/iec_61260_1_2014.html
- pyloudnorm on PyPI (JSON API) and GitHub: https://pypi.org/pypi/pyloudnorm/json , https://github.com/csteinmetz1/pyloudnorm

---

## 1. ISO 3382-1:2009 parameter definitions

Standard: ISO 3382-1:2009 "Acoustics - Measurement of room acoustic parameters - Part 1:
Performance spaces". It replaced ISO 3382:1997; the 2009 foreword says Annex A "has been extended
with information on JND (just noticeable difference), recommended frequency averaging and by the
addition of a new parameter" (late lateral sound level, LJ) (ISO preview, p. iv, accessed
2026-11-04).

### 1.1 Reverberation time family (clause 3.5 and clause 6)
- T is "the duration required for the space-averaged sound energy density in an enclosure to
  decrease by 60 dB after the source emission has stopped" (ISO preview, 3.5).
- Note 2 of 3.5 (verbatim from the preview): "if T is derived from the time at which the decay
  curve first reaches 5 dB and 25 dB below the initial level, it is labelled T20. If decay values
  of 5 dB to 35 dB below the initial level are used, it is labelled T30."
- The fit is a **linear least-squares regression of the decay curve (in dB) against time** over
  the evaluation range; the slope d (dB/s) gives T = 60/d. ODEON's ISRA 2013 paper states it the
  same way: "a least-squares fitted line is computed for the range ... The slope of the fitted
  line gives the decay rate, d in dB per second, from which the reverberation time is calculated
  e.g. as T30 = 60/d" (ODEON paper, section 2.3).
- Evaluation ranges and extrapolation factors (python-acoustics `t60_impulse` encodes exactly
  these; the ODEON paper confirms T20/T30):
  - EDT: 0 dB to -10 dB, factor 6.
  - T10: -5 to -15 dB, factor 6 (not in ISO 3382-1; python-acoustics extra).
  - T20: -5 to -25 dB, factor 3.
  - T30: -5 to -35 dB, factor 2.
  - "Factor" means: T = factor * (t_end - t_start) where t_* are read **from the regression
    line**, not from the first crossing of the raw curve. Equivalent: T = -60 / slope_dB_per_s.
- Decay curve = Schroeder backward integration of the squared IR (ISO 3.3: "method of obtaining
  decay curves by reverse-time integration of the squared impulse responses").

### 1.2 Required dynamic range / SNR
- ISO preview, clause 4.1 (source): "a source level will be required that gives at least 45 dB
  above the background level in the corresponding frequency band. If only T20 is to be measured,
  it is sufficient to create a level at least 35 dB above the background".
- Clause 5.2 repeats it for interrupted noise: "decay curve starting at least 35 dB above the
  background noise in the corresponding frequency band. If T30 is to be measured, it is
  necessary to create a level at least 45 dB above the background level in each frequency band."
- Logic: evaluation range ends at -35 dB (T30) and must stay >= 10 dB above the noise floor
  → 45 dB. The 10 dB margin above noise for the lower evaluation limit is in clause 5.3.3
  **(unverified, from memory; not in the preview pages)**.
- Mic/source placement (clause 4.3, preview): microphone positions at least half a wavelength
  apart ("around 2 m"), at least a quarter wavelength (~1 m) from any surface incl. the floor,
  mic height 1.2 m ("ear height of average listeners in typical chairs"); source as close to
  omnidirectional as possible with Table 1 deviation limits averaged over gliding 30-degree arcs.
- Frequency range (clause 5.1): engineering/precision methods at least 125 Hz-4 kHz in octaves or
  100 Hz-5 kHz in third octaves; survey method at least 250 Hz-2 kHz. The project's 63 Hz and
  8 kHz bands are outside the standard's mandatory range (fine, but tolerances must be looser).
- Filters: "The octave or one-third-octave filters shall conform with IEC 61260"; equipment
  "type 1 sound level meter according to IEC 61672-1" (clause 4.2, preview).

### 1.3 Energy-ratio parameters (Annex A; formulas from memory, confirmed by ODEON paper text)
- Clarity C_te = 10 log10( integral_0^te p^2(t) dt / integral_te^inf p^2(t) dt ) dB, te = 50 ms
  (speech) or 80 ms (music). The ODEON paper: "In the case of C80 (Eq.(1)) the time intervals are
  from 0 to 80 ms and from 80 ms to infinity, after the arrival of direct sound." **t = 0 is the
  arrival of the direct sound**, not the start of the file.
- Definition D50 = integral_0^50ms p^2 / integral_0^inf p^2 (ratio 0..1, often in %).
  Relation: C50 = 10 log10( D50 / (1 - D50) ).
- Centre time Ts = integral_0^inf t p^2(t) dt / integral_0^inf p^2(t) dt (seconds; ISO JND is
  stated in ms). Ts is the first moment of the squared IR; it needs no boundary and so is less
  sensitive to the 50/80 ms edge, but it is very sensitive to the noise tail (noise far out in
  time has a large lever arm).
- Strength G = 10 log10( integral_0^inf p^2(t) dt / integral_0^inf p_10^2(t) dt ) dB, where p_10
  is the free-field response at 10 m from the same omnidirectional source. For a simulation,
  G is only meaningful if the direct-path level follows 1/r with the same reference.
  **(formula from memory)**
- Lateral energy fraction J_LF = integral_5ms^80ms p_L^2 / integral_0^80ms p^2 (figure-of-eight
  mic, cosine-weighted). IACC from binaural IRs: max over |tau| <= 1 ms of the normalised
  cross-correlation, early (0-80 ms) or late. **(from memory)** Not needed for omni validation.
- DRR (not in ISO 3382-1): DRR = 10 log10( E_direct / E_reverberant ). The common engineering
  choice (ACE challenge, Eaton et al. 2016) is "the energy in a window of 2.5 ms around the
  maximum of the AIR" as direct, everything outside as reverberant (quoted by arXiv 1911.00566,
  https://arxiv.org/pdf/1911.00566, which says its version is "slightly modified compared to the
  definitions given by Eaton et al."; accessed 2026-11-04). The ACE TASLP paper itself
  (IEEE/ACM TASLP 24(10):1681-1693, 2016) was not opened. Some authors use 4 ms, some centre the
  window at the onset rather than the peak. **Whichever is chosen must be written down in the
  metric's docstring and in the golden file**, since DRR differences of several dB follow from the
  window alone.
- DRR JND: Zahorik 2002 (JASA 112(5):2110-2117, doi 10.1121/1.1506692) measured discrimination
  thresholds of about 5-6 dB for DRR from 0-20 dB (abstract via search, accessed 2026-11-04);
  Larsen et al. 2008 summarise a minimum JND of about 2 dB at 0 dB D/R rising to ~20 dB at
  +-20 dB (https://pmc.ncbi.nlm.nih.gov/articles/PMC2677334). Treat 2-3 dB as a tight tolerance
  and 5-6 dB as the perceptual limen.

### 1.4 JND values (ISO 3382-1 Annex A, as reproduced by ODEON's ISRA 2013 Table 1)
| Parameter | JND |
|---|---|
| EDT | 5 % |
| T20, T30 | 5 % |
| C50, C80 | 1 dB |
| D50 | 0.05 |
| Ts | 10 ms |
| G | 1 dB |
| LF | 0.05 (Archives of Acoustics 37(4), 2012, via search; **not checked in the standard**) |
| IACC | 0.075 (same secondary source) |

Source for the main table: ODEON paper Table 1 "All parameters are derived by formulas given in
the ISO 3382 standard", accessed 2026-11-04. The ODEON authors also call the 10 ms Ts JND "highly
questionable" for some rooms. ISO 3382-1 Annex A recommends reporting single-number values as the
**average of the 500 Hz and 1 kHz octave bands** (T, EDT, C80, G, D50, Ts); the project's AQ9
averages 500 Hz/1 kHz/2 kHz, which is stricter than the standard and must be stated as a project
choice, not as "ISO" **(the 500/1000 Hz rule is from memory; not in the preview pages)**.

How to read them: a simulation that is within 1 JND of the measurement in a band is perceptually
"correct" in that band; the 2019 round robin uses exactly this criterion (section 6 below).

---

## 2. Schroeder backward integration and noise-floor handling

### 2.1 Formula
- EDC(t) = integral_t^inf p^2(tau) dtau, usually normalised: L(t) = 10 log10( EDC(t) / EDC(0) ).
- Discrete: `edc = cumsum(h[::-1]**2)[::-1]` (pyroomacoustics does literally this; pyrato's
  `schroeder_integration` the same with optional `is_energy`).
- For an ideal exponential decay with time constant giving T60 the EDC is a straight line in dB
  with slope -60/T60 dB/s. For a measured IR of finite length t1 plus noise, the EDC is biased.

### 2.2 The truncation problem and the compensation term C
- ODEON paper (section 2.3): "some energy is not included in the real impulse response due to its
  finite length t1. The problem can be corrected by estimating the energy that is lost due to the
  truncation. This amount of energy can be added as an optional constant C in Eq.(2) ... If the
  curve is not corrected for truncation, the estimated decay time may be too short."
- Conversely, integrating **through** the noise tail makes the EDC flatten and the fitted T too
  long (ODEON section 3.4: "misinterpreted, often leading to longer reverberation times").
- C for an exponential tail: if the squared IR at the truncation time t1 has level p^2(t1) and the
  late decay time is T_late, then C = integral_t1^inf p^2(t1) exp(-6 ln(10) (t - t1)/T_late) dt
  = p^2(t1) * T_late / (6 ln 10). pyrato implements exactly this
  (`correction = p_square_at_intersection * late_reverberation_time * (1/(6*np.log(10))) *
  sampling_rate`, the `sampling_rate` factor converting seconds to samples because its EDC is a
  plain sample sum; the code carries a "TO-DO: check reference!" comment) (pyrato edc.py, accessed
  2026-11-04). In closed form with A = p^2(t1), B = 6 ln10 / T_late: C = A / B.
- ODEON's additional step: subtract the estimated noise power from the valid part of the squared
  IR before integrating (ODEON section 3.5: "the estimated background noise floor excluding the
  truncated tail ... can be subtracted from the valid part of the backwards integrated decay
  curve"). This is Chu's method; pyrato offers `energy_decay_curve_chu`,
  `energy_decay_curve_lundeby` and `energy_decay_curve_chu_lundeby` (combination, citing Guski &
  Vorländer 2014).
- Guski & Vorländer, Acta Acustica united with Acustica 100:320-327 (2014), doi
  10.3813/AAA.918711: five compensation methods compared; "methods perform differently to a
  significant degree ... this also holds for the three methods that are compliant with ISO 3382";
  "Four methods cause systematic errors depending on the peak-signal to noise ratio" (abstract
  via search, accessed 2026-11-04). Consequence for review: **a metric test must run at several
  PSNR values (e.g. 30, 45, 60 dB) and the golden must say which method was used.**

### 2.3 Lundeby's method (Lundeby, Vigran, Bietz, Vorländer, Acustica 81(4):344-355, 1995)
The paper is paywalled; the steps below are the ones implemented in pyrato
`intersection_time_lundeby` (which cites the paper) and match the standard description:
1. Square the IR and **average it in local time intervals** of 10-50 ms (pyrato default 30 ms
   broadband; per band it uses `800/f_c + 10` ms, e.g. 22.7 ms at 63 Hz, 10.1 ms at 8 kHz).
2. **Noise estimate** from the last 10 % of the smoothed response.
3. **Regression** (least squares, dB vs time) from the peak to the point 10 dB above the noise
   estimate (pyrato: `dB_above_noise = 10`, requiring at least 5 dB of dynamic range).
4. Preliminary **crosspoint** = intersection of the regression line with the noise level.
5. New local time-interval length chosen so that there are 3-10 intervals per 10 dB of decay
   (pyrato uses 5).
6. Re-average with the new interval.
7. **Re-estimate the noise** from the part of the response starting 5-10 dB beyond the crosspoint
   (pyrato: 10 dB), or from the last 10 % if that comes earlier.
8. Re-fit the late slope over a 10-20 dB range (pyrato: 20 dB) ending 5-10 dB above the noise
   (pyrato: 10 dB).
9. New crosspoint; iterate until it changes by less than a small amount (pyrato: 0.01 s; the
   paper says 5 iterations suffice; pyrato caps at 30).
Outputs: intersection time t_i, late reverberation time T_late (= -60/slope), noise level.
Then: truncate the integration at t_i and add C from 2.2. pyrato notes the EDC is NaN "if the
intersection time could not be computed due to a low signal-to-noise ratio" and applies a
PSNR threshold of 15 dB "in correspondence with ISO 3382-1:2009" for the truncation variant
(pyrato edc.py docstrings, accessed 2026-11-04).
Known fragility: one secondary source reports Lundeby failing in a large fraction of test cases
in a comparison (search result, not verified); the ODEON authors "utilize a modification of this
method". Any implementation needs a **failure policy** (NaN + warning per band, never silently 0).

### 2.4 The simpler "-10 dB above noise" truncation
- Estimate noise power N from the final 10 % (or a user-given window before the onset, ODEON
  uses a 10 ms window before the onset by default), find the first time the smoothed squared IR
  falls to N + 10 dB (5-10 dB margin is the usual safety band), truncate there, integrate backward
  from the truncation point, add C using the slope fitted just before truncation. Simpler, fewer
  failure modes, slightly biased when the margin cuts into the decay. Must still be **per band**:
  "The Truncation time is unique to each band of interest" (ODEON section 3.4).

### 2.5 Typical implementation mistakes (each one has bitten real code)
- Integrating the **pressure** instead of the **squared** pressure (sign cancellation → garbage).
- Computing the EDC from **dB values** (cumsum of dB) instead of from linear energy.
- Doing the regression on a **time range** ("fit between 0.1 s and 0.5 s") instead of the
  **level range** (-5 to -35 dB) read from the EDC itself.
- Starting the forward integral for C80/D50/Ts at the **file start** instead of the **direct-sound
  onset**; a 10 ms leading delay moves the 80 ms boundary and changes C80 by several dB in a small
  room. python-acoustics `clarity()` has exactly this behaviour (`h2[:t]/h2[t:]` with t counted
  from sample 0; room.py accessed 2026-11-04).
- Reading t_start/t_end from the **raw EDC crossings** instead of from the fitted line (small bias,
  but it is not what the standard says).
- Fitting the EDC after **normalising to the first sample** only; fine for T, wrong for EDT when the
  onset isn't at sample 0 (the first 10 dB then include leading silence).
- Using the whole IR for simulated data but a truncated one for measured data without saying so
  (the 2019 round robin did exactly this on purpose: "For the simulated RIRs, the calculation of
  the EDC was based on the entire RIR, while the measured RIRs were truncated after..." (Brinkmann
  et al. 2019, section II.E, accessed 2026-11-04)). Document it.
- Forgetting that the **correction C** must be computed from the late slope (not the T30 slope) and
  in the same units as the EDC (energy, not dB).
- Noise estimate taken from the last 10 % of a **simulated** IR that has a zero tail → log of zero;
  pyroomacoustics explicitly strips the "possibly all zero tail" before taking the log.

### 2.6 Octave-band filtering of short decays (filter ringing, the BT rule)
- A bandpass filter with bandwidth B has its own decay; the measured decay is the convolution of
  the room decay with the filter's. Jacobsen (1987 and later) concluded that **B*T > 16** gives
  acceptable reverberation-time estimates from the average decay slope; time-reversed filtering
  (Jacobsen & Rindel, "Time reversed decay measurements", J. Sound Vib. 117:187-190, 1987;
  Jacobsen & Kob) relaxes this to **B*T > 4** (search results citing Semantic Scholar and a
  ScienceDirect paper on group delay of digital filters, accessed 2026-11-04).
- ISO 3382:1997 stated the lower limit for traditional forward analysis as a BT product plus
  "T > 2 T_det" (detector); the OCR of the iteh preview reads "BT ≥ 6" but the digit may be
  garbled (could be 16) **(unverified)**. The same text gives B = 0.71 f_c for octave filters and
  B = 0.23 f_c for third-octave filters.
- So the **minimum measurable T per octave band**, conservative rule T_min ≈ 16/B = 16/(0.71 f_c):
  63 Hz → 0.36 s; 125 Hz → 0.18 s; 250 Hz → 0.09 s; 500 Hz → 0.045 s. With BT > 4 (time-reversed
  filtering): 63 Hz → 0.09 s. This is why Phase 02 loosens the 63 Hz tolerance to +-5 % and why a
  T60 = 0.3 s synthetic decay at 63 Hz is already at the limit of the rule.
- ODEON uses IEC 61260 2nd-order Butterworth octave filters with a defined "effective length"
  (99.9 % of the filter's energy) and reverse-forward filtering for decay analysis so "all the
  transients are ... eliminated" and the filter delay doesn't stretch the decay (ODEON section
  3.2). For gated energy parameters (C80 etc.) they apply **forward filtering per gated window
  and include the filter tail** ("window-before-filtering", ISO 3382-1 suggestion) so the 80 ms
  boundary is set on the broadband IR, not on the smeared filtered IR (ODEON section 2.4).
- Practical consequence for `bands.py` (6th-order zero-phase Butterworth): zero-phase filtering
  smears energy **both ways in time**, so the band-filtered IR has pre-ringing before the direct
  sound. Fine for T30/T20/EDT slopes, **wrong for onset detection and risky for C50/C80/D50/Ts at
  63-125 Hz**. Gate first on the broadband IR, then filter, or compute the energy-ratio
  parameters with forward (causal) filtering and include the filter tail.

---

## 3. Octave-band filters per IEC 61260-1:2014

- Edition: IEC 61260-1:2014 "Electroacoustics - Octave-band and fractional-octave-band filters -
  Part 1: Specifications" (https://webstore.iec.ch/en/publication/5063, accessed 2026-11-04).
  Changes vs 1995: design goals "based only [on] base-10"; class 0 removed, classes 1 and 2
  remain ("Class 2 limits are greater than, or equal to, those for class 1"); maximum permitted
  measurement uncertainties added (IEC webstore abstract via search).
- Base-10 octave ratio G = 10^(3/10) = 1.99526 (python-acoustics module constant). Base-2 is
  G = 2 (option in the 1995 edition; IS 6964 reprint: "The base-ten system is preferred"; the
  difference is ~0.6 % at 5 kHz and 1.4 % at 50 kHz).
- Exact centre frequencies, reference f_r = 1000 Hz, bandwidth designator b (1 for octaves):
  f_m = f_r * G^(x/b) for odd b; f_m = f_r * G^((2x+1)/(2b)) for even b.
  Band edges: f_1 = f_m * G^(-1/(2b)), f_2 = f_m * G^(+1/(2b)). For octaves: f_m / sqrt(G),
  f_m * sqrt(G) (base-10) or f_m / sqrt(2), f_m * sqrt(2) (base-2).
  (python-acoustics iec_61260_1_2014 module, accessed 2026-11-04.)
- Nominal vs exact (base-10), Hz (NTi table, accessed 2026-11-04):
  63 → 63.1 (44.7-89.1); 125 → 125.9 (89.1-177.8); 250 → 251.2 (177.8-354.8);
  500 → 501.2 (354.8-707.9); 1000 → 1000.0 (707.9-1412.5); 2000 → 1995.3 (1412.5-2818.4);
  4000 → 3981.1 (2818.4-5623.4); 8000 → 7943.3 (5623.4-11220.2).
  Note the 8 kHz upper edge 11.2 kHz: the band is fully inside 44.1/48 kHz Nyquist but a 6th-order
  Butterworth designed with `fs/2` normalisation must be checked for warping (use `sos`, and
  check `|H|` at the edges numerically).
- Class limits on relative attenuation, octave filters, from the 1995 table (IS 6964 reprint; the
  2014 class 1/2 numbers are believed identical **(unverified)**), normalised frequency f/f_m:
  | f/f_m | class 1 min; max (dB) | class 2 |
  |---|---|---|
  | 1 (G^0) | -0.3; +0.3 | -0.5; +0.5 |
  | G^(+-1/8) | -0.3; +0.4 | -0.5; +0.6 |
  | G^(+-1/4) | -0.3; +0.6 | -0.5; +0.8 |
  | G^(+-3/8) | -0.3; +1.3 | -0.5; +1.6 |
  | G^(+-1/2) inside the band | -0.3; +5.0 | -0.5; +5.5 |
  | G^(+-1/2) outside the band | +2.0; +5.0 | +1.6; +5.5 |
  | G^(+-1) | +17.5; inf | +16.5; inf |
  | G^(+-2) | +42; inf | +41; inf |
  | G^(+-3) | +61; inf | +55; inf |
  | G^(+-4) and beyond | +70; inf | +60; inf |
  A 6th-order Butterworth bandpass (3 dB at the edges, 36 dB/oct per side beyond) comfortably
  meets the class 1 stopband (>= 17.5 dB one octave out) but is at the limit of the passband
  tolerance near G^(+-3/8) where a Butterworth already drops ~0.1-0.5 dB **(estimate)**. Zero-phase
  application squares the magnitude response (6 dB at the edges, double the stopband attenuation);
  `bands.py` should state whether "order 6" means per pass or total.
- Why zero-phase (`filtfilt`) changes the apparent onset: the effective impulse response
  h_zp = h * reverse(h) is symmetric and non-causal; energy appears **before** the true arrival by
  roughly the filter's group delay (tens of ms at 63 Hz). Any onset/arrival-time detector run on a
  band-filtered signal therefore reports an early (zero-phase) or late (causal) arrival.
  **Do not band-filter for arrival detection**: detect arrivals on the broadband IR (matched filter
  or peak picking), then gate, then filter (ODEON's approach, section 2.4/3.3). ISO 3382-1 says
  the onset is where the broadband response first rises within 20 dB of the direct-sound peak
  ("the onset of the direct sound ... should be at least 20 dB below the peak of the direct
  sound", ODEON quoting ISO 3382-1 pp. 18-19; ODEON's default trigger is 40 dB below the peak and
  it uses a 10 ms pre-onset window for the noise estimate).

---

## 4. Second-opinion implementations

### 4.1 `pyroomacoustics.experimental.rt60.measure_rt60` (source read 2026-11-04)
Signature: `measure_rt60(h, fs=1, decay_db=60, energy_thres=1.0, plot=False, rt60_tgt=None,
label=None, linear_domain_fit=False)`. Docstring: "we measure the RT20 or RT30 and extrapolate to
RT60", and `decay_db` is "The decay in decibels for which we actually estimate the time".
What it does, line by line:
1. `power = h**2`; `energy = np.cumsum(power[::-1])[::-1]` (Schroeder). **No band filtering, no
   onset detection, no noise compensation.**
2. If `energy_thres < 1`, subtracts `energy[0]*(1-energy_thres)` from the whole curve and clips at
   0 (a crude way to discard the last fraction of the energy; not a noise estimate).
3. Drops the all-zero tail, converts to dB, normalises to `energy_db[0]` (file start, so leading
   silence is harmless here because the EDC is flat there).
4. **Silently shrinks `decay_db`** if the curve's dynamic range minus 5 dB is smaller than
   `decay_db`: `if min_energy_db - 5 < decay_db: decay_db = min_energy_db`. With the default
   `decay_db=60` and a 50 dB SNR measurement it therefore fits -5 dB to roughly the noise floor
   and the result is biased long. For a fair comparison with T30 call it with `decay_db=30`
   (fit -5 to -35 dB); for T20 use 20.
5. `i_5db` = first index below -5 dB (returns **0.0** if the curve never reaches -5 dB);
   `i_decay` = first index below `e_5db - decay_db` (or the end).
6. Fit: `_fit_exp_and_extrapolate(energy_db[i_5db:i_decay], fs, -60)`: ordinary least squares of
   dB vs time (after subtracting the first value) → returns `-60 / slope` seconds. With
   `linear_domain_fit=True` it instead fits `b*exp(a*t)` to the **linear** energy with
   `scipy.optimize.curve_fit` (initialised from the log fit) and returns `(-60/10) ln(10) / a`.
7. `plot=True` imports matplotlib and draws the EDC, the -5/-60 dB lines, the fitted line and
   vertical lines at the estimate and at `rt60_tgt`.
Return value: a single float (seconds if `fs` given, otherwise samples). One channel only
(`np.array(h)` 1-D expected).
Sensitivity: the default fit range is -5 to -65 dB (not T30!), so on a noiseless synthetic decay
it equals T30 only if the decay is perfectly exponential; on noisy data it is longer than T30. The
`fs=1` default means a forgotten `fs` yields the answer in samples; a test comparing to
`metrics.py` within +-5 % (Phase 02 acceptance) must pass `fs` and `decay_db=30`, and must band-
filter the IR itself before calling it. Licence: MIT (file header).

### 4.2 python-acoustics `acoustics.room.t60_impulse(file_name, bands, rt='t30')`
(room.py read 2026-11-04.) Reads a **WAV file path** (not an array) with `scipy.io.wavfile`;
`bands` is a NumPy array of octave or third-octave nominal centres; `rt` in {'t30','t20','t10',
'edt'} with ranges/factors as in section 1.1. Per band: `bandpass(raw_signal, low, high, fs,
order=8)` (acoustics.signal.bandpass; whether it is zero-phase was not checked **(unverified)**),
rectify and normalise by the max, `sch = cumsum(abs**2 reversed) reversed`, `sch_db = 10 log10(
sch/max)`, picks the samples whose EDC value is nearest to `init` and `end` dB, `linregress` over
that sample span, then `t60 = factor * (t_end_from_line - t_init_from_line)`. Returns an array
per band. No noise compensation, no truncation, no onset handling; `clarity(time, signal, fs,
bands)` does `10 log10(sum(h2[:t]) / sum(h2[t:]))` with `t = int(time/1000*fs + 1)` from sample 0
(no onset detection). `c50_from_file`/`c80_from_file` wrap it. The module also has
`t60_sabine/eyring/millington/fitzroy/arau` (analytic estimates, useful as a third cross-check
on the shoebox scenes). Licence: BSD-3 **(from memory)**.

### 4.3 pyrato (pyfar family)
`pyrato.edc.energy_decay_curve_lundeby`, `_truncation`, `_chu`, `_chu_lundeby` and
`intersection_time_lundeby` as in section 2.3; the docs recommend the band-dependent smoothing
and return NaN with `failure_policy='warning'` per band. Good third opinion for the Lundeby part
specifically; pyroomacoustics has none.

---

## 5. Click/discontinuity detection for time-varying audio tests

Phase 02 design (phase-02.md): high-pass at 2 kHz (8th-order zero-phase Butterworth), RMS in
2 ms frames, flag frames > median + `threshold_db` (20 dB) and above -90 dBFS; input = sustained
tones at 110/220/330 Hz. Rationale: an LTI (or slowly varying) system driven by low tones produces
no energy above 2 kHz; a step discontinuity is broadband.

Approaches found in the literature (search 2026-11-04; detailed references from memory):
- **HF-energy vs baseline** (the project's method): simple and robust for tonal probes. Blind to
  anything whose spectrum stays below the high-pass cutoff.
- **Spectral flux** (frame-to-frame positive change of the magnitude spectrum, as used for onset
  detection, Bello et al. 2005 IEEE TSAP **(from memory)**): catches broadband and partial-band
  steps on arbitrary programme material; false positives on musical onsets unless the probe is
  stationary.
- **AR/LPC residual outliers** (Vaseghi & Rayner 1990; Godsill & Rayner 1996, "Robust treatment of
  impulsive noise in speech and audio signals", IMS Lecture Notes 29, projecteuclid link in search
  results): model the signal as autoregressive, flag residual samples far above the residual's
  robust scale. Most sensitive; works on music; needs tuning per material.
- **Derivative kurtosis / short-time energy + kurtosis** (search found a laser-speech paper using
  "a combination of the average short-time energy and kurtosis"; cetacean click detectors use
  kurtosis with a sliding-window threshold, arXiv 2402.04735): kurtosis of the first difference in
  a frame rises sharply for a single-sample step; immune to slow level changes.
- **Warped linear prediction** click detection (Esquef et al., search result): a refinement for
  broadband material.

Known blind spots of the HF-energy detector (and how to cover them):
- **Low-frequency thumps** (DC steps, a crossfade whose two IRs differ in LF phase, a filter state
  reset): most energy below 2 kHz → not flagged. Cover with a second band (e.g. 20-200 Hz energy
  vs baseline on a tone-free probe) or with the derivative-kurtosis detector.
- **Slow zipper noise** (parameter stepped every block at 48 kHz/512 = 94 Hz): produces a
  periodic buzz; frames rise together, so median baseline rises too and nothing stands out. Cover
  with a spectral check: energy at the block rate and its harmonics vs. the clean run.
- **Level pumping / gain modulation** (a crossfade that dips -3 dB in the middle, equal-gain vs
  equal-power): no HF energy at all. Cover by envelope comparison against the dry/expected
  envelope (e.g. max frame-RMS deviation < 0.5 dB).
- **Clicks masked by HF content**: if the probe already has HF energy (sweeps, pink noise) the
  20 dB threshold is never reached. Keep the sustained-tone probe for this detector.
- **Clicks below the absolute floor** (-90 dBFS) or within 2 ms of a flagged frame (merged).
- **Two-sample DC offsets** (tiny steps) at -60 dBFS: Phase 02 requires detection down to -60 dBFS
  steps; at 2 ms frames and 48 kHz a single-sample step of amplitude a has HF energy of order a^2
  spread over the frame, so the frame RMS is ~a/sqrt(96) → ~-80 dBFS for a = -60 dBFS, above the
  -90 dBFS floor but only ~10-20 dB above the baseline of a clean float32 tone; verify the margin
  in the test rather than assume it.

Negative control: a detector is only proven by (a) a **positive control** (N known injected
events, 100 % recall, exact times) and (b) **negative controls** that exercise each blind spot
that is *supposed* to be allowed: clean 60 s tone (0 hits), tone with slow +-6 dB AM at 0.5 Hz
(0 hits; Phase 02 acceptance), and ideally a legitimately time-varying but click-free case (a
30 ms equal-gain crossfade between two IRs, AQ4). If the negative control passes only because
the threshold is high, the positive control must still pass at the smallest step size, otherwise
the test is vacuous. Also log the baseline level and the maximum frame excess in the test output
so a regression that narrows the margin is visible before it flips the result.

---

## 6. BRAS and the simulation round robins

### 6.1 Hosting, licence, versions
- DepositOnce record (accessed 2026-11-04): title "BRAS - Benchmark for Room Acoustical
  Simulation"; authors Lukas Aspöck, Fabian Brinkmann, David Ackermann, Stefan Weinzierl, Michael
  Vorländer; DOI **10.14279/depositonce-6726.3** (version 3, issued 2020-10-06: "Updated
  documentation, revised directory structure"; v2 2019-05-15; v1 2018-03-19 under the earlier name
  GRAS, "Ground Truth for Room Acoustical Simulation"); licence **Creative Commons Attribution
  ShareAlike 4.0 (CC BY-SA 4.0)** as stated on the record page; "Is Supplement To"
  10.1016/j.apacoust.2020.107867 (Brinkmann, Aspöck, Ackermann, Opdam, Vorländer, Weinzierl,
  "A benchmark for room acoustical simulation. Concept and database", Applied Acoustics 176,
  107867, 2021). A Zenodo mirror (https://zenodo.org/records/8419919) lists CC BY 4.0 - the
  DepositOnce record is authoritative and says BY-SA; the phase-05 statement "CC BY-SA 4.0" is
  correct. Attribution + share-alike apply to redistributed derived data (e.g. if measured IRs are
  ever committed, which CLAUDE.md forbids anyway).
- Files on the record (sizes): Documentation.pdf 3.51 MB; 1_scene_descriptions-RS1..RS7.zip
  (3.7-74 MB each); 1_scene_descriptions-CR1..CR4.zip (371, 587, 706, 749 MB);
  2_source_and_receiver_descriptions-{FABIAN_HRIRs 4.38 GB, FABIAN_meshes 4.5 MB, Genelec_8020c
  1.17 GB, ITA_dodecahedron 242 MB, QSC_K8 1.26 GB}; 3_surface_descriptions.zip 225 MB;
  4_additional_data.zip 22.5 MB. **`fetch_bras.py` must download only the CR zip(s) it needs plus
  Documentation.pdf and 3_surface_descriptions.zip; the per-scene zips are not split further on the
  server, so a 587 MB download for CR2 is unavoidable.** A 2026 extension "RS8" (curved surfaces,
  DOI 10.14279/depositonce-25649) exists but is not needed.

### 6.2 Contents (Documentation.pdf, accessed 2026-11-04)
- Seven **reference scenes** RS1-RS7 (controlled, in anechoic rooms) and four **complex rooms**
  CR1-CR4 ("can not be used as a direct reference due to increased measurement uncertainties").
  Round-robin numbering 1-11 maps to RS1-7 = scenes 1-7, CR1 = 8, CR2 = 9, CR3 = 10, CR4 = 11.
  - RS1 simple reflection, infinite plate (floor of hemi-anechoic chamber, rigid/absorber/
    diffusor sub-scenes); RS2 simple reflection and diffraction at a finite plate (1 m and 2 m
    MDF); RS3 multiple reflection between two finite plates (flutter); RS4 reflection at a
    reflector array (nine 68 cm MDF plates); RS5 diffraction at an infinite edge (25 mm MDF
    partition); RS6 diffraction at a finite body; RS7 seat-dip-like multiple diffraction (15 cubic
    blocks). Anechoic rooms: TU Berlin full anechoic V = 1070 m^3 (f_low 63 Hz), hemi-anechoic
    V = 296 m^3 (f_low 100 Hz).
  - CR1 coupled rooms: reverberation chamber 122 m^3 + laboratory 104 m^3 (RWTH Aachen).
  - **CR2 small room, seminar room at RWTH Aachen, V = 145 m^3**, chosen "because its relatively
    simple and easy to describe geometry, but challenging low frequency behaviour"; 49 RIRs,
    5 BRIR sets, IR length 154,350 samples = 3.5 s at 44.1 kHz; Genelec RIRs measured in 4
    orientations (+X, +Y, -X, -Y); one RIR missing (LS1 +Y, MP5). **WARNING in the doc: "The
    level of the RIRs was manually corrected by 6 dB to meet the expected direct sound level."**
  - CR3 medium room, small hall of the Konzerthaus Berlin, V = 2,350 m^3 excluding an attic
    volume that is coupled to the hall ("might be excluded or simplified"); 70 RIRs; same 6 dB
    warning.
  - CR4 large room, Auditorium Maximum TU Berlin, V = 8,650 m^3; 50 RIRs; same warning.
  - Table II of the 2019 paper: T_m (mean of 500 Hz and 1 kHz octaves) small 2.0 s, medium 1.3 s,
    large 2.1 s; Schroeder frequency 234 / 47 / 31 Hz; critical distance 0.49 / 2.42 / 3.66 m.
    **At 145 m^3 with T = 2 s, modes dominate below 234 Hz: the 63 and 125 Hz bands of CR2 are not
    diffuse and no GA method should be expected to match them.**
- Formats: IRs as **SOFA** (field `Data.IR`, dims M x R x E x N for CR scenes; metadata fields
  MeasurementView/ReceiverID/EmitterID give the order) **and per-pair wav at 44.1 kHz**, naming
  `<scene>_RIR_<LSn>_<MPn>.wav`-style (e.g. `RS1_RIR_Rigid_LS1_MP3.wav`); BRIRs with FABIAN head
  rotations (HATO) in 10-degree steps over +-50 degrees. Geometry as SketchUp `.skp` (one with
  sources/receivers, one geometry-only), screenshots and pictures; surfaces as CSV with frequency,
  absorption and scattering in **third octaves 20 Hz-20 kHz** in a `3_surface_descriptions`
  folder, with material names referenced from the .skp textures.
- Sources: Genelec 8020c (2-way studio monitor; omni below ~200 Hz within 1 dB), QSC K8 (PA, for
  binaural scenes), RWTH 3-way dodecahedron (crossovers 177 Hz and 1.42 kHz). Directivities on
  1 x 1 degree grids (IRs + third-octave spectra); "the directivities were not normalised" and the
  source frequency response is **contained in the measured IRs** (2019 paper II.D). Level
  calibration: 80 dB SPL free field at 1 kHz at 2 m on axis.
- Receivers: omni 1/2" capsules (B&K 4134, DPA 4006-class), FABIAN HATS for BRIRs; "They are
  supposed to be modeled as omnidirectional receivers in the simulation."
- Materials for CR1-4: "derived from in-situ measurements whenever possible [pu-probe, reliable
  only for porous absorbers at normal incidence] and attributed from material databases
  otherwise"; "Less important materials and small surfaces were disregarded, which lead to four,
  five, seven, and eight different materials for scenes CR1-4". These are the **initial
  estimates**. A second set of **fitted estimates** exists only for CR1-4: "fitted to the measured
  reverberation times by multiplication with the ratio ᾱ_fit/ᾱ for each third octave band and
  scene, i.e., the same ratio was applied for all materials within a scene", where ᾱ solves the
  Eyring equation T = 0.161 V / (-S ln(1-ᾱ) + 4mV) with the measured T. So the fitted set
  **encodes the measured T60 by construction** (phase-05 is right to treat it as a secondary run).
- Onset-based level checks "could not be done for CR1-4" because the Genelec was not facing the
  receivers and the dodecahedron is a multi-driver source (documentation section 3.4) - hence the
  manual 6 dB correction. **Do not use absolute level (G) from the CR RIRs as a reference.**

### 6.3 Round-robin accuracy figures (what a reviewer should expect)
Brinkmann et al. 2019 (open-access copy, accessed 2026-11-04), six teams, five GA algorithms
(incl. ODEON 12, RAVEN, and RAZR for the shoebox-only case), blind simulation from the initial
material estimates:
- Complex rooms (scenes 9-11), T20 averaged over 10 source/receiver positions: "the measured
  reverberation times are, on average, overestimated by 58 % (125 Hz) and 35 % (250 Hz). For the
  mid-frequency range (500 Hz-2 kHz), there is no systematic deviation; the differences between
  simulation and measurement are, however, still above the JND in most cases." Above 2 kHz: a
  tendency to **underestimate** T. "The simulations resulted in reverberation times that are
  closer to the Eyring estimates than to the measured values in most cases" → the error is
  dominated by the absorption data, not by the algorithm.
- "While the EDT is overestimated at low frequencies and underestimated at high frequencies, the
  opposite holds for the clarity (C80) and definition (D50)." Per-position correlation between
  measured and simulated values at 1 kHz was **not statistically significant**, except C80/D50 in
  the large room (r = 0.7-0.9); EDT in the small room showed a "reversed spatial dependency" for
  one algorithm. I.e. T30 is matched on average, but **position-dependent parameters are not**.
- Conclusion: "no algorithm met the investigated room acoustical parameters within the tolerance
  of the JND in all frequency bands"; "neither able to provide an exact pattern of early
  reflections, nor ... an exact prediction of room acoustic parameters outside a medium frequency
  range of 500 Hz-2 kHz".
- Perceptual: 2AFC authenticity test on the medium room, detection rate p >= 0.98 for every
  algorithm ("none of the auralizations managed to be indistinguishable"); plausibility test: 3 of
  4 algorithms plausible for most listeners (p2AFC 0.52-0.58); differences driven by tone colour
  and source position, attributed to early reflections, random-incidence absorption/scattering
  coefficients and missing diffraction.
- Simple scenes: only the infinite rigid plate (RS1) was matched well; nobody matched the diffusor
  comb filter; one algorithm with first-order edge diffraction approximated the finite plate at
  long wavelengths; the coupled-room double slope was not modelled by most.
- Earlier PTB round robins (Vorländer ICA 2010 paper, accessed 2026-11-04): RR-I (Vorländer 1995,
  ICA Trondheim; 17 simulation participants, 7 measuring teams, PTB auditorium) showed "a
  surprisingly large scatter with a strong tendency to underestimate the absorption coefficients
  and thus to overestimate the reverberation time"; "In some cases the differences exceeded 50 %.
  Even simple quantities such as the sound level (strength) were predicted with up to +-5 dB
  maximum deviation"; purely specular programs "overestimated the reverberation time
  systematically"; the measurement itself has ~5 % (+-0.05 s) uncertainty at 1 kHz (Lundeby 1995).
  RR-II (Bork, Acustica 86:943-956, 2000; Elmia concert hall, 16 participants, three measuring
  teams) and RR-III (Bork, Acta Acustica united with Acustica 91:753-763, 2005; PTB music
  recording studio; T30, EDT, D50, C80, G, Ts, LF, LFC, IACC in six octave bands) found that "no
  simulation software ... predicted the acoustical parameters clearly better than the others" and
  that standardising input data "can significantly reduce the divergence" (search summaries,
  accessed 2026-11-04). Quantitative RR-II/III figures (roughly: best programs within ~1-2 JND for
  T30 at mid frequencies with fixed input data, several JND for EDT/C80/LF, worse at 125 Hz)
  **(unverified, from memory)**.
- Vorländer's uncertainty-propagation argument (ICA 2010): to keep T within the 5 % JND the
  absorption coefficients must be known to roughly +-0.015-0.035 absolute, which is below the ISO
  354 inter-laboratory standard deviation of 0.03-0.09 (ODEON Table 2 / Vorländer Table 1); a 10 %
  uncertainty in T translates to a C80 uncertainty "rather small compared with the JND for clarity
  (1 dB)" only in the diffuse-field sense.

What is realistic for Phase 05 (shoebox ISM + stochastic tail, initial materials): mid-band T30
within +-10 % is plausible but not guaranteed (the professionals were "above the JND in most
cases" even at 500 Hz-2 kHz); **EDT and C80 at single positions will likely miss** (no measured
early-reflection pattern can be matched by a shoebox); 63/125/250 Hz misses of 30-60 % are the
norm. AQ9 (T30/EDT +-10 %, C80 +-2 dB averaged over 500 Hz-2 kHz) is therefore ~2 JND for T and
EDT and 2 JND for C80: a fair "engineering" bar, but a report claiming to pass it must show the
per-position scatter, not just the average.

---

## 7. Loudness: ITU-R BS.1770 and pyloudnorm

- Latest: **Recommendation ITU-R BS.1770-5 (11/2023)**, "Algorithms to measure audio programme
  loudness and true-peak audio level", revision history 2006-2007-2011-2012-2015-2023 (PDF cover,
  accessed 2026-11-04). Four stages (Annex 1): "K" frequency weighting; mean square per channel;
  channel-weighted summation ("surround channels have larger weights, and the LFE channel is
  excluded"); gating of 400 ms blocks overlapping by 75 % with two thresholds, "the first at
  -70 LKFS; the second at -10 dB relative to the level measured after application of the first
  threshold".
- K-weighting = stage 1 shelving filter (spherical-head model) + stage 2 RLB high-pass, both
  biquads at 48 kHz. Table 1 (stage 1): b0 = 1.53512485958697, b1 = -2.69169618940638, a1 =
  -1.69065929318241 (b2 = 1.19839281085285, a2 = 0.73248077421585 **from memory**). Table 2
  (stage 2): b0 = 1.0, b1 = -2.0, b2 = 1.0, a1 = -1.99004745483398 (a2 = 0.99007225036621 **from
  memory**). "Implementations at other sampling rates will require different coefficient values,
  which should be chosen to provide the same frequency response" - i.e. **do not reuse the 48 kHz
  coefficients at 44.1 kHz** (pyloudnorm recomputes them from the analogue prototype).
- Loudness L_K = -0.691 + 10 log10( sum_i G_i z_i ) LKFS; "The constant -0.691 ... cancels out
  the K-weighting gain for 997 Hz". Table 3 weights: L, R, C = 1.0; Ls, Rs = 1.41 (~ +1.5 dB).
  Gated loudness: blocks with l_j > Gamma_a = -70 LKFS are kept; relative gate
  Gamma_r = (loudness of those blocks) - 10 LKFS; final value from blocks above Gamma_r (eq. 5-6).
  "Incomplete gating blocks at the end of the measurement interval are not used." The algorithm
  "is not, in general, suitable for use to estimate the subjective loudness of pure tones".
- True peak (Annex 2): 12.04 dB attenuation (optional in float), 4x oversampling to 192 kHz,
  low-pass, absolute value, dB TP. "Higher sampling rates and over-sampling ratios are preferred".
- What changed in rev. 5 vs 4: extended channel weighting guidance for advanced/immersive sound
  systems per BS.2051 (the PDF links BS.775, BS.2051 and Report BS.2217) **(unverified; only the
  link list was readable)**. For stereo material there is no numerical change since BS.1770-3.
- **pyloudnorm**: version **0.2.0 released 2026-01-04** (PyPI JSON: releases 0.0.1 2018-06-20,
  0.1.0 2019-09-05, 0.1.1 2023-01-05, 0.2.0 2026-01-04), licence MIT, `requires_python >= 3.9`,
  README says "Implementation of ITU-R BS.1770-4" (GitHub, accessed 2026-11-04). API:
  `Meter(rate, block_size=0.400, filter_class="K-weighting")`, `integrated_loudness(data)` with
  `data` shaped (samples, channels), `loudness_range(data)` ("Attempt to measure" LRA per EBU Tech
  3342), `pyln.normalize.peak(data, target_dB)`, `pyln.normalize.loudness(data, measured, target)`.
  `filter_class` options: default, "DeMan" ("fully compliant filters"), "Fenton/Lee 1",
  "Fenton/Lee 2", "Dash et al.", "custom". Caveats: a signal shorter than one 400 ms block returns
  -inf; the -70 LKFS absolute gate drops silence, so a sparse IR-convolved test signal is gated
  differently from the dry one; for pure tones (the click-detector probes) the result is
  level-dependent but still usable as a *relative* match.
- "Within +-1 LU" for mode matching: 1 LU = 1 dB of K-weighted, gated level. ISO 3382-1's JND for
  level (G) is 1 dB, and 1 LU is the commonly cited loudness-matching tolerance in broadcast
  practice (EBU R 128 target tolerance +-1 LU for live programmes **(from memory)**). For an A/B
  pack: measure both files with the same `Meter`, apply a static gain so integrated loudness
  differs by < 0.1 LU (there is no reason to leave 1 LU of mismatch when the gain is a scalar);
  then check true peak < -1 dBTP after gain.

---

## 8. Pitfalls when comparing a simulated IR to a measured IR

- **Time alignment**: measured IRs have a latency (interface, sweep processing, propagation
  from the *acoustic centre*, not the box) and BRAS documents centre definitions per source
  (e.g. dodecahedron mid-unit centre). Align on the direct-sound onset (broadband, 20-40 dB below
  peak) before computing C50/C80/D50/Ts/DRR; T30/T20/EDT need no alignment. Never align on the
  peak of a band-filtered signal (section 3).
- **Level normalisation**: BRAS CR RIRs were manually corrected by 6 dB; the source frequency
  response is inside the measured IR; the simulation has an ideal flat omni source. Compare
  level-independent metrics (T, EDT, C, D, Ts, DRR) and **per-band energy differences only after
  normalising to the direct-sound energy** or to the total energy, and say which.
- **Noise floor**: measured IRs decay into noise; the 3.5 s BRAS IRs with T ~ 2 s at 145 m^3 may
  have < 45 dB usable range at 63-125 Hz (where the dodecahedron and Genelec output is weakest).
  Use the same EDC method with noise compensation on both; for the simulation the noise floor is
  numerical (float32, ~-150 dB), so Lundeby's "last 10 %" estimate is meaningless and the
  compensation must be skipped or the simulation must be truncated to the measured length. The
  2019 round robin truncated the measured IRs and used the entire simulated IRs; report what was
  done.
- **Bandwidth of the measurement loudspeaker**: the Genelec 8020c is a small 2-way monitor; the
  dodecahedron has crossovers at 177 Hz and 1.42 kHz; the 63 Hz band in the measured RIR is the
  loudspeaker's roll-off plus room modes, not a diffuse decay. Treat 63 Hz as informative only.
- **Source directivity vs omni assumption**: the Genelec is not omni above ~200 Hz and was
  measured in four orientations; comparing the omni simulation to one orientation biases the
  early energy (C80, EDT, DRR) by several dB at high frequencies. Average the four orientations
  or use the dodecahedron RIRs where available and say so in `bras_mapping.md`.
- **Receiver height and position**: BRAS positions are in the scene's coordinate frame (SketchUp
  model); after reducing a real room to a shoebox the positions must be re-expressed in the shoebox
  frame; a receiver that was 1 m from a real wall must stay 1 m from the corresponding shoebox
  wall, not be scaled with the room. Keep the 1.2 m height; keep >= 1 m from surfaces (ISO).
- **Why T30 is easy and EDT/C80 are hard**: T30 is a global property that follows from volume
  and total absorption (Sabine/Eyring) and "only varies little with position" (ODEON: standard
  deviation 0.02 s = 0.2 JND at 1 kHz over positions). EDT depends on the first 10 dB, i.e. on the
  direct sound and the first reflections, which a shoebox ISM places at the wrong times/levels for
  any non-rectangular surface, plus scattering and diffraction (the round robin's main finding);
  C80 depends on an 80 ms boundary cutting through that early pattern and on the exact onset.
  Expect EDT/C80 position scatter in both the measurement and the simulation of 1-2 JND even
  when T30 agrees.
- **Fitted absorption**: BRAS fitted estimates are scaled so that Eyring reproduces the measured
  T per third-octave; a simulation using them *will* match T30 (that is circular) but says nothing
  about EDT/C80. Report the initial-estimate run as the result and the fitted run as a
  diagnostic.
- **Air absorption** (BRAS gives temperature/humidity per room: CR2 19.5 C / 41.7 %); at 4-8 kHz
  a missing or wrong air-attenuation term shifts T30 by tens of percent in a 2 s room.
- **Averaging across positions**: average metrics, not IRs; average T in seconds, C80 in dB (ISO
  3382-1 averages parameter values; averaging energies then taking dB gives a different number).
- **Sample rate**: BRAS is 44.1 kHz; the engine renders at 48 kHz by default; resample the
  **metrics' inputs** consistently (or render at 44.1 kHz), never compare EDCs sample-by-sample
  across rates.

---

## 9. Reviewer's checklist (metrics code, goldens, comparison scripts, validation reports)

Schroeder / decay parameters
1. Is the EDC built from `h**2` (linear energy) and only converted to dB afterwards? (Catches
   cumsum of dB or of |h|.)
2. Is the regression range selected by **level** (-5/-35 dB from the EDC) and not by time? (Catches
   "fit 0.1-0.5 s" hacks that pass on one synthetic decay.)
3. Are T20/T30/EDT derived as -60/slope (or factor x regression-line times), not from raw EDC
   crossings? (Catches 1-3 % biases on noisy EDCs.)
4. Does the EDT range start at the **onset** (0 dB at the direct sound) and not at sample 0 of a
   file with leading silence? (Catches EDT inflated by the silent lead-in.)
5. Is noise compensation (Lundeby or the -10 dB rule) applied **per band**, with its intersection
   time and noise level returned/logged? (Catches a single broadband truncation that cuts the
   63 Hz decay.)
6. Is the truncation compensation C computed from the **late** slope and in energy units, then
   added before the dB conversion? (Catches "C added in dB".)
7. What happens when the band's SNR is below ~35-45 dB? NaN + warning, or a silently wrong number
   (pyroomacoustics returns 0.0, shrinks `decay_db`)? Does the golden comparison treat NaN as a
   failure?
8. Is the synthetic-decay test run at several PSNRs (e.g. noiseless, 60, 45, 35 dB) and several
   T60 values including the BT-limit cases (0.3 s at 63/125 Hz)? (Catches methods that only work
   on noiseless data.)
9. Does the second-opinion test call `measure_rt60(h_band, fs=fs, decay_db=30)` (or 20) and
   band-filter first? (Catches a vacuous +-5 % agreement on broadband -5/-65 dB fits.)
10. Is the 63 Hz tolerance justified by the BT rule, and is anything looser than that explained in
    the golden file? (Catches "loosen until green".)

Energy-ratio parameters and onset
11. Is t = 0 for C50/C80/D50/Ts/DRR the detected **broadband** onset, defined as the first sample
    within X dB (20-40) of the peak, and is X in the docstring and the golden? (Catches off-by-80 ms
    errors and python-acoustics-style sample-0 integration.)
12. Is onset detection done on the unfiltered IR and the gating done before band filtering (or the
    filter tail included after gating)? (Catches zero-phase pre-ringing shifting the 80 ms edge.)
13. Is the DRR window (2.5 ms? 4 ms? centred on peak or onset?) stated, and is it the same in the
    simulated and measured path? (Catches multi-dB DRR deltas from definitions.)
14. For the analytic C80 test: is the "delta + exponential decay" analytic value computed with the
    same onset convention and with the decay energy split exactly at 80 ms (closed form of the
    exponential integral), and is +-0.2 dB really achievable with the band filter in the loop?
15. Are C80 values averaged in dB and T values in seconds across positions, and is the band
    average (500/1k/2k) stated as a project choice vs ISO's 500/1k? (Catches "ISO says" claims.)

Band filters
16. Are the centre/edge frequencies base-10 (63.1 Hz, 89.1-177.8 Hz) or base-2 (62.5/63 Hz,
    88.4-176.8 Hz), and does `contract::kOctaveBandsHz` agree with `bands.py` to the Hz? (Catches
    a 0.6 % band shift that differs between C++ and Python.)
17. Is "order 6" the per-pass order, and is the squared response of `sosfiltfilt` what the tests
    assume? Is the filter built as `sos` (not `b, a`) to avoid instability at 63 Hz/48 kHz?
18. Does a unit test check the filter bank's magnitude at f_m, the edges and one octave out
    against the class 1 limits (-0.3/+0.3 dB, <= +5 dB at edges, >= 17.5 dB at G^+-1)? (Catches a
    filter that leaks the 125 Hz decay into the 63 Hz band.)
19. Does the 8 kHz band handle the 11.2 kHz upper edge correctly at 44.1 kHz input?

Click detector
20. Is there a positive control (200 injected single-sample steps at -60...-6 dBFS, 100 % recall,
    event times within one frame) **and** negative controls (clean tone, +-6 dB 0.5 Hz AM, and a
    legitimate crossfade)? (A detector with no negative control proves nothing.)
21. Are the baseline (median) and the maximum frame excess printed, so a shrinking margin is
    visible before the test flips?
22. Is the blind-spot list (LF thumps, zipper noise, pumping, probes with HF content) documented
    next to the detector, and is at least one of them covered by another test (envelope or
    block-rate spectral check)? (Catches false confidence in "no clicks".)
23. Does the detector merge adjacent frames into one event, and does the test count events, not
    frames? (Catches 200 injected / 400 detected "passes".)

Comparison scripts and goldens
24. Does `compare.py` align on the broadband onset before computing per-peak amplitude and
    per-band energy differences, and does it report the alignment shift it applied?
25. Are both IRs resampled to one rate and truncated to one length before any metric? Is the
    simulated IR's "noise floor" handling explicitly disabled or the IR explicitly truncated to the
    measured length?
26. Does every golden file carry: metric definition version, filter bank version, EDC method,
    onset rule, tolerance per metric, source commit, and a `reason` entry in CHANGELOG.md on
    update? (Catches goldens regenerated to make a test pass.)
27. Were any golden tolerances widened in this diff? If yes, is there a change-log row and a
    physical justification (BT rule, SNR), not just "flaky"?
28. Is the golden comparison tolerant of NaN in a band only where the golden says the band is
    unmeasurable? (Catches silent skipping.)
29. Is the regression gate of the nightly ("worsening > 2 % relative to baseline") computed on the
    **absolute delta** |sim - meas|, and does an improvement update the baseline only through the
    documented update script?

Validation report / BRAS
30. Does `bras_mapping.md` give the shoebox dimensions, the rule used (match V and S), the
    area-weighted material mapping per surface, which BRAS material set (initial vs fitted), which
    source (Genelec orientation(s) or dodecahedron) and which receiver positions - and is the rule
    identical for every room (NFR-8)? (Catches per-room tuning.)
31. Does the fetch script verify SHA-256 of every file, fail on mismatch, and never commit data;
    does the manifest pin the DepositOnce version (6726.3)? Is the CC BY-SA 4.0 attribution in
    THIRD_PARTY.md?
32. Is the 6 dB manual level correction of CR RIRs acknowledged and are no absolute-level metrics
    (G) claimed from them?
33. Are results reported per band *and* per position with scatter (SD or min/max), not only the
    500 Hz-2 kHz average, and are 63/125/250 Hz results labelled "below Schroeder frequency
    (234 Hz for CR2)" rather than counted as failures of the algorithm?
34. Does the report compare its errors to the round-robin reference numbers (mid-band T within a
    few JND; LF T overestimated by 35-58 %; EDT/C80 uncorrelated per position) before drawing
    conclusions about AQ2? (Catches both over-claiming and over-blaming.)
35. Is the fitted-absorption run clearly labelled as circular for T30 and never used as evidence
    for AQ9?
36. Is the A/B listening pack loudness-matched with the same `Meter` on both files to < 0.1 LU,
    true-peak checked, and generated at one sample rate; is `key.txt` separate and the file order
    randomised with a seed recorded?
37. Do two runs of `run_validation.py` produce byte-identical report numbers (seeded tail, fixed
    resampler, fixed BLAS thread count)? (Catches nondeterministic nightly diffs.)
38. Does the report state the EDC method and PSNR for the **measured** IRs per band, so a future
    change in the metrics code can be separated from a change in the engine?

---

## Appendix: quick formulas (plain text)

- EDC(t) = sum_{n >= t} h[n]^2 ; L(t) = 10 log10(EDC(t)/EDC(0))
- T_xx = -60 / slope_dB_per_s over [-5, -5-xx] dB (xx = 20, 30); EDT over [0, -10] dB
- C = p^2(t_i) * T_late / (6 ln 10) (energy units) ; added to EDC before dB
- C_te = 10 log10( sum_{0..te} h^2 / sum_{te..end} h^2 ), te = 50 ms or 80 ms after onset
- D50 = sum_{0..50ms} h^2 / sum_all h^2 ; C50 = 10 log10( D50/(1-D50) )
- Ts = sum t h^2 / sum h^2 (t from onset)
- DRR = 10 log10( sum_{|t - t_peak| <= 2.5 ms} h^2 / sum_else h^2 ) (state the window!)
- Octave edges: f_m * G^(-1/2), f_m * G^(+1/2), G = 10^0.3 (base-10) or 2 (base-2)
- T_min per band (BT rule): T_min ≈ 16 / (0.71 f_c) (forward filtering), ≈ 4/(0.71 f_c) with
  time-reversed filtering
- BS.1770: L_K = -0.691 + 10 log10( sum_i G_i z_i ); gates -70 LKFS absolute, -10 LU relative
