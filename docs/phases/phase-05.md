# Phase 05 — Comparison with measured impulse responses (evidence) + accuracy report

Size: **M** · Depends on: 04 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ2, AQ9, AX4, AX16, AX21, AX22, AX23) and §3 (F2, F3), PRD NFR-1, NFR-8, Q2, Q9

## Raise with Maisara (she does not track these herself)

The session raises each item in its **first message** and again in the **PR description**.

1. **BRAS surface areas and room classification.** Read the per-material areas and d_char from
   `_descr/mat_CRx.txt` inside `3_surface_descriptions.zip` (researcher report 16 §4–5). Confirm or
   correct the preliminary classification in Data (CR2 uniform/low-s; CR3 and CR4 one strong, high-s
   absorber). Report to Maisara whether any BRAS room combines uneven α with low s. If none does, say
   that the X-b bias and B11 cannot be tested against BRAS for that case (F2).
2. **DELTA panel report.** If Maisara has not sent the request drafted in
   `docs/review/drafts/delta-report-request.md`, remind her. Phase 05d needs the answer.
3. **Commissioning decision.** Tell Maisara that this decision comes after Phase 05d (see phase-05d,
   "Raise with Maisara"), and summarise for her what this phase's numbers already suggest.

## Goal

Get the **first real-world evidence** of accuracy (NFR-1) early, while changing the simulation
method (AQ2) is still cheap. Compare the omni room IRs from Phases 03–04 against IRs **measured in
real rooms**, using only geometry and material data that comes with those measurements. Nothing is
hand-tuned.

## Assumptions in force

- **AQ9** thresholds against measured IRs: **T30 and EDT within ±10 %, C80 within ±2 dB, on the mean of
  the absolute per-band errors over 500 Hz, 1 kHz and 2 kHz** (absolute deviations, as in the
  round-robin rating of Vorländer §11.5, which averages |sim − meas|/jnd over source/receiver pairs;
  here per pair over bands). EDT and C80 limits are 2 jnd (Table 6.1: 5 %, 1 dB, stated for
  500–1000 Hz, so the report also prints the 500–1000 Hz mean); T30 ±10 % is a chosen tolerance (no T
  jnd in the corpus); it is 2 × a working T jnd of 5 % (expert recommendation, Seraphim 1958; outside the corpus, not
  verified; product choice, stands (AQ9)) and above single-position measurement scatter of T30, ≈ 2–3.5 % at 500 Hz–2 kHz
  for T = 0.8 s (ISO 3382-2 estimate; outside the corpus, not verified; product choice, stands (AQ9)). Signed per-band deltas are reported without gating (their sign shows bias). The
  report also gives the mean over the source/receiver pairs of each room.
  **Meter (AX23, decider D2):** the AQ9 T30 and EDT figures stay on the octave filters at 500 Hz,
  1 kHz, 2 kHz (C80 unchanged). AQ9 uses the ISO octave meter; the air-only leakage bias is ≤ 2.2 % /
  5.7 % at 1 / 2 kHz up to T = 2 s (bound, Kuttruff Eqs. 4.12, 5.24, Table 6.1), checked per room by r.
  Per room, r = T(slower octave neighbour)/T(band) at 500 Hz, 1 kHz, 2 kHz is computed from the
  room-averaged measured octave T30 (mean over pairs; σ(r)/r ≈ 2–3 % per pair) and from the simulated
  IRs; if any r > 1.1 the room's AQ9 line is marked **"leakage-sensitive"** (decider E1: the octave bias at
  r = 1.1 is b(1.1; D) from the interrogator's two-term model, Kuttruff Eqs. 3.64–3.68 basis, with the
  leak D measured by the scope 7 calibration; until it is measured, 0.42 % at D = 15 dB and 1.2 % at
  D = 10 dB (model); threshold 1.1 unchanged; if the calibration's model check fails, this reason quotes
  the measured bias table instead). The AQ9 T30/EDT mean with the half-octave 1 and 2 kHz values is always printed beside it as
  a secondary figure that never changes pass/fail. Reversal: the scope 7 calibration bias exceeds
  2.5 % at the measured BRAS r, or the Expert accepts the half-octave meter.
- **AQ2** method under test. **NFR-8**: no per-scene factors. If a room fails, report it.
- **AX4**: fixed atmosphere in the simulator; a validation-only `render_cli` atmosphere override (not
  user-facing, not in the contract) separates model error from atmosphere mismatch (scope 6).
  ISO 3382-2 §4.3.3–4.3.4 treats air as negligible only for T < 1.5 s at 2 kHz (researcher F5,
  outside the corpus); CR2 and CR4 are near 2 s, so the 2 kHz AQ9 band is atmosphere-sensitive: the
  override render at the documented conditions (CR2: 19.5 °C, 41.7 % RH; researcher F14, outside the
  corpus) is printed beside the AQ9 line, not only in the humidity section.
- **AX21**: the Phase 04 hybrid IR has no scattered energy before t_mix,e (known deficit); scope 6
  measures what adding it would change, without changing the simulator.
- **AX23** (Phase 04 decay-time meter): the `tools/acoustics` order-6 Butterworth octave filters read
  a band's decay time long when T60 falls steeply into the next band (`metrics.py` "known limits");
  Phase 04 measured +29 % at 8 kHz in `stone_box` and +10.6 % in `concert_hall_box` (central
  half-octave reading ≈ 0 %). Phase 05 reads both meters (decider D1–D4, 2026-11-06, proposals
  Maisara can veto): the **octave** reading is primary everywhere (ISO 3382-1 §4.2.2 names octave and
  third-octave bands only; researcher F6, outside the corpus); the AX23(b) **half-octave** Kaiser FIR
  reading at 1, 2, 4, 8 kHz (a single IR is an ensemble of one; outside the corpus) is printed beside
  it, gates only in the nightly change detection (scope 4) and must agree for B12 (scope 6; unless its E2 octave-only branch applies). A
  comparison through one meter is fair only if both IRs have the same neighbour ratio r and the same
  leak, so r is printed per band (Kuttruff Eqs. 3.64–3.68, via the interrogator). Reversal: the Expert
  accepts the half-octave meter (AX23-10), or the leak calibration (scope 7) shows octave bias < 1 % at
  r ≤ 1.3.

## Data

- **BRAS** — *Benchmark for Room Acoustical Simulation* (TU Berlin; licence CC BY-SA 4.0). It contains
  room scenes with geometry descriptions, material absorption/scattering data and measured omni and
  binaural IRs. The comparison rooms are the CR rooms, CR1 excluded as coupled. Their α and s are
  estimated, and the dataset authors state the CRs "cannot serve as a direct reference", so the errors
  measure method plus input data, not a validation of NFR-1: Phase 05 calls them evidence (researcher
  findings F1–F3, F6, F7 from the BRAS documentation, researcher report 9, `docs/review/phase-04-consult/9-researcher-measurements.md`; outside the corpus)
  (decider report 11, accepted by Maisara, 2026-11-05).
- Per-material α and s for CR2–CR4 are tabulated in the BRAS `_csv/initial_estimates`, and areas and
  d_char are in `_descr/mat_CRx.txt` inside `3_surface_descriptions.zip`; from α alone, CR2 is uniform
  and low-s, while CR3 and CR4 each have one strong absorber (seating) that is also high-s, so BRAS
  likely has no room that combines uneven α with low s, which Phase 05 confirms with the areas
  (researcher report 16 §4–5, `docs/review/phase-04-consult/16-researcher-bras-materials-priors.md`;
  external, outside the corpus; researcher report 16, preliminary; Phase 05 re-reads the values from the zip).
- Write `tools/validation/fetch_bras.py`. It downloads only the files needed (scene documentation,
  material tables, omni RIRs for the selected source/receiver pairs) from the official repository
  (DepositOnce), verifies SHA-256 checksums stored in `tools/validation/bras_manifest.json`, and caches
  them under `~/.cache/makroof/bras`. **Never commit the data** (CLAUDE.md rule). Add the attribution to
  `docs/THIRD_PARTY.md`.
- Before writing code, the session must read the BRAS documentation and record in
  `docs/validation/bras_mapping.md` which scenes were chosen and why. Pick the rooms whose geometry is
  closest to a rectangular box (likely the small seminar room and similar). State how each real room was
  reduced to a shoebox, by these generic rules, and which BRAS material set is used. The room
  selection and its reasons are committed to `bras_mapping.md` before any simulated-vs-measured number
  is computed; no room is dropped after results are seen (decider report 8, accepted by Maisara, 2026-11-05):
  - **Dimensions:** keep the mean floor-to-ceiling height h, always defined as h = V / documented floor
    area; solve the floor from a·b = V/h and a + b = (S − 2V/h)/(2h), the longer side
    along x (AQ1 axes). A real solution exists iff S ≥ 2V/h + 4√(V·h); otherwise use the square floor
    a = b = √(V/h) (the smallest S for that V and h) and report the S error. With this h the box keeps
    the room's floor and ceiling areas, total wall area and plan perimeter exactly; only the split
    between x- and y-walls is approximate, and the floor and ceiling keep their documented α under the
    face rule (expert recommendation, outside the corpus). Near-square plans sit close to the existence
    bound, so the square-floor fallback may trigger on small errors in the documented S (harmless, S
    error < 1 %; report it). Choosing to keep h is a
    product choice (the corpus statistics, Vorländer Eq. 4.22, 4.23, 4.28, depend only on V, S and ᾱ;
    individual dimensions enter through the image lattice, §11.3.3).
  - **Absorption:** assign each documented surface to exactly one box face, the one whose outward
    normal is closest to its own; per band, α_face = ΣSᵢαᵢ / S_face over the assigned surfaces, so the
    absorption area A (Eq. 4.30) is conserved per face and in total and, with S matched, ᾱ and the
    Eyring T (Eq. 4.28, 4.32) are preserved; clamp α_face ≤ 1 and report every clamp and the A it
    loses. (An area-weighted mean ΣSᵢαᵢ/ΣSᵢ does not conserve A unless face areas equal mapped areas.)
  - **Scattering:** per band, s_face = ΣSᵢ(1−αᵢ)sᵢ / ΣSᵢ(1−αᵢ) over the assigned surfaces (weighted by
    reflected energy, Vorländer Eq. 3.23–3.24), then reduced to one broadband s per face by AX17 (mean
    of 500 Hz, 1 kHz, 2 kHz). Running without scattering is not an option (Vorländer §11.5
    Round-robin II/III, §11.6).

  Use the **initial/as-documented** absorption data as
  the primary run. If the dataset also provides absorption values fitted to the measurements, run them as a
  secondary, clearly labelled run. Fitted data partly includes the answer, so it isn't proof of accuracy:
  on the fitted set T30 is circular, because the fitted α were scaled so that Eyring matches the
  measured T (researcher finding F6, outside the corpus); label it that way.
- If no room qualifies, Phase 05 still completes every part that does not need BRAS (a* Table 5.2
  test, ΔL_b on the test rooms, Table 5.2 and the s-cases, humidity bound). It is `done` with the note
  'NFR-1 not validated against measurement'. The measured remainder becomes `phase-05c` (created only if
  this case arises), `blocked` until Maisara picks a measured data source (PRD Q9 asks which reference
  IRs). Meanwhile: B11 (B) uses the 'no evaluable pair' branch; the handover rule stands (D1); Eyring
  stays (B12). Phase 13 may start with 05c blocked only on Maisara's recorded decision (decider report 8, accepted by Maisara, 2026-11-05).
  That case is also evidence for F3 and Q2.

## Scope

1. `tools/validation/fetch_bras.py`, `bras_manifest.json`, `docs/validation/bras_mapping.md`.
2. `tests/scenes/validation/bras_<room>_<src>_<rcv>.json` — contract scenes for the chosen pairs
   (source and receiver positions mapped into the shoebox frame so that the real source–receiver
   distance r and the source and receiver heights above the floor are kept; r enters C80 through the
   direct sound, Vorländer Eq. 6.20, and the heights fix the floor/ceiling reflection delays).
3. `tools/validation/run_validation.py` — renders each scene with `render_cli --mode omni --ir`,
   computes ISO 3382 metrics for simulated and measured IRs with `tools/acoustics`, and writes:
   - `docs/validation/report-phase05.md`: a table per scene with band metrics, deltas and an AQ9
     pass/fail summary, plus EDC overlay plots saved as PNG next to the report (matplotlib, pinned).
   - `tests/golden/validation_baseline.json`: the baseline simulated metrics for the nightly gate
     (item 4) and the recorded sim–meas errors.

   Comparison conditions, applied identically to simulated and measured IRs through the same
   `metrics.room_metrics` path and the same `tools/acoustics` octave filter bank:
   - **Meter (AX23, decider D1):** for every pair, at 1, 2, 4, 8 kHz, both IRs: T30 (or the T20
     fallback) and EDT with the `bands.py` octave filters (**primary**) and with the AX23(b) half-octave
     Kaiser FIR (`ensembles.band_metrics_half_octave_ensemble`, one IR as an ensemble of one). Print
     per band both readings per IR, the sim–meas error under each meter, and each IR's octave
     neighbour ratio r = T(slower neighbour)/T(band). Flag a band **"meter-dependent"** when the two
     meters' sim–meas errors differ by more than 5 percentage points (1 AQ9 working jnd, outside the
     corpus; for EDT the Vorländer Table 6.1 value extended past 1 kHz); expected false-flag rate
     ≈ 2 %; not gating. C80 octave only.
   - **Time origin:** the direct-sound arrival of each IR (Vorländer §6.4.2 Eq. 6.5 t₀), detected the
     same way in both: first sample within 20 dB of the broadband peak (ISO 3382-1 practice, outside
     the corpus). Not file t = 0, not the peak sample. C80 (Eq. 6.7) and EDT are taken from it.
     t₀ is detected on the squared broadband IR (|h|², threshold max − 20 dB) before band filtering, and
     the same t₀ is used for all bands of that IR. Band filtering is applied to the full IR (keep a few
     ms of lead-in), with zero-phase (forward–backward) filters or compensated group delay, before the
     80 ms window and the EDT reference. Check the measured lead-in: nothing before the first arrival
     (sweep distortion images, converter pre-ringing) may reach −20 dB (expert recommendation, outside
     the corpus; ISO 3382-1 practice).
   - **Measured EDC:** backward integration (Eq. 6.4) from the band's noise-floor intersection, with
     noise-energy compensation (ISO 3382-1 practice; the corpus gives no procedure). Integrating to
     file end without compensation biases T30 (e.g. ≈ +40 % by −5…−35 dB regression at noise −50 dB re the initial band
     envelope energy, T = 1 s, 3 s file). Crossing-point search: `metrics.lundeby` (Lundeby et al.
     1995), which since Phase 04 decides on the upper hull of the smoothed decay (BUILD_PLAN §6 Phase 04
     row; checked on noisy single realisations by the scope 7 paired noise test). Noise per band
     (decider D6): `metrics.lundeby`'s iterative estimate, the mean square from 10 dB below the
     crosspoint level on the line to the end, at least the last 10 % (consistent with Lundeby as
     summarised by Venturi, Farina, Tronchin, POMA 19, 015006 (2013), doi:10.1121/1.4800277; researcher
     F7, original unverified; outside the corpus). `run_validation.py` first drops the documented final
     1024 Hann-faded samples of every BRAS RIR (a dataset property, applied to all files, not per room;
     BRAS documentation, Aspöck et al. 2020, doi:10.14279/depositonce-6726.3, §3.4.1, researcher F14;
     effect ≈ −0.18 dB on a 0.35 s segment). The report prints beside it the mean square of the last
     10 % of the trimmed file and flags **"noise not verified"** when the two estimates differ by more
     than 3·√(σ₁² + σ₂²), σᵢ = 4.34/√(B·T_seg,i) dB (B the band's bandwidth, T_seg,i the segment
     duration; interrogator's assumption, outside the corpus). Reversal: non-stationary BRAS noise
     makes those bands not evaluable. Compensation
     energy (A/k)·e^(−k·t_c) with k from the late slope near the crossing t_c; one correction only (no
     additional noise subtraction); the same truncated and compensated energy is used in the late
     integral of C80 (Eq. 6.7) (expert recommendation, outside the corpus; window and iteration
     constants are implementation choices recorded in the report).
   - **Simulated EDC (N1):** the same `metrics.room_metrics` path as the measured IR; a simulated IR
     ending near −90 dB is truncated and compensated by `metrics.lundeby`, effect ≈ 4·10⁻⁵ dB at
     −35 dB (Eq. 6.4). Its "noise" is the decay end, so its dynamic range is ≈ 90 dB and it passes the
     usable-range test. A band whose IR ends (12 s cap) before the decay has fallen 62 dB is flagged
     (keeps the −35 dB point within 0.01 dB).
   - **Usable range (decider D7, N2):** a band's T30 is evaluable only if **both** hold: (1) the
     `metrics` peak-referred dynamic range is ≥ 45 dB (T20: ≥ 35 dB; the existing code, matching the
     start-level reference of ISO 3382-1 §4.2.1, §5.2.1; researcher F1/F2, outside the corpus); (2) the
     final Lundeby late-decay line (power domain, the line used for the compensation), extrapolated to
     t₀, lies ≥ 45 dB (T20: ≥ 35 dB) above the Lundeby noise level. (2) is the "−35 dB point 10 dB
     above noise" rule (10 dB margin outside the corpus; it limits the noise in the squared band IR at
     the −35 dB time to 0.4 dB, ≈ 0.9 dB on the uncompensated EDC) stated on that line, not on the EDC regression
     and not on the literal EDC −35 dB point, which is laxer by 10·log10(1 + (r_c/r)²) (Kuttruff
     Eq. 9.2 form; 2.9 dB at r = r_c). The two references coincide near 3.3 r_c; beyond that the peak
     rule is ≈ 1 dB stricter, within it laxer (+1.3 dB at 2 r_c, +4.6 dB at r_c). For a double-slope
     decay the late line (slower when the decay sags, Kuttruff Eq. 3.67) gives the stricter test. The
     report prints both margins per band. Otherwise T20 (−5 to −25 dB) is reported for that band,
     flagged; a 500 Hz–2 kHz band without T30 is "not evaluable" and is excluded from the AQ9 T30
     mean, never counted as a pass. A band that falls back to T20 is compared measured T20 with
     simulated T20, never with simulated T30. If T20 also fails (either test at 35 dB) the band is "not evaluable"
     for T and excluded from every T mean (T15 may be shown for information only); EDT and C80 stay
     evaluable. If all three AQ9 bands are not evaluable for T, the pair's T30 result is "not
     evaluable", not a pass.

   The report also states:
   - In Round-robin I (one band, PTB auditorium) simulated T was generally too long when users
     estimated absorption themselves, traced to underestimated absorption; with measured absorption
     agreement was much better (Vorländer §11.5). The corpus does not predict the sign for
     as-documented data, so the report states the sign of the T30 bias per band.
   - For each room the report states the Schroeder frequency under both constants: Vorländer Eq. 4.13,
     ≈1200√(T/V), which f_S must greatly exceed; and Toole §4.3.1, 2000√(T/V), the middle of the
     transition zone in large rooms and likely too low in small rooms. Deltas in bands below or within
     the transition zone are read as evidence on the method's validity, not on the input data. Where
     the two estimates differ, the report names the band it treats as the upper edge.
   - Loudness matching (BS.1770) removes overall level, so listeners cannot judge strength G
     (Vorländer Table 6.1, jnd 1 dB). The report gives the offset removed per pair (dB) as a property
     of the playback; it is not a G error unless both IRs are calibrated to the same free-field
     reference (Eq. 6.5). On the BRAS CRs: "G not evaluable: levels manually corrected by 6 dB"
     (researcher finding F3, outside the corpus); T30, EDT and C80 do not depend on absolute level.
     Position-to-position level differences inside a room may be shown for information, only if the
     documentation confirms that the correction is uniform (decider report 11, accepted by Maisara, 2026-11-05).
   - Context: where published, the round-robin errors for the same rooms and input set (RR19:
     Brinkmann et al. 2019, JASA 145(4), DOI 10.1121/1.5096178; external source) are printed next to ours, the use the dataset authors endorse
     (comparing simulations on identical input).
   - BRAS scattering data enter the scenes through AX17: one broadband s per surface. For a material
     whose s rises from 500 Hz to 2 kHz (many Annex scattering rows do; some are flat or falling),
     this overstates s at 500 Hz and understates it at 2 kHz, so per-band deltas in the AQ9 bands include an AX17 input
     error, flagged next to them. BRAS s rises as √f (s = 0.5·√(d_char·f/c), clamped to [0.05, 0.99];
     researcher finding F7, BRAS documentation, outside the corpus): for unclamped materials the AX17
     mean is (1 + √2 + 2)/3 = 1.471 × s(500), which overstates s by +47 % at 500 Hz and +4 % at 1 kHz
     and understates it by −26 % at 2 kHz, whatever d_char is (decider report 11, accepted by Maisara, 2026-11-05).
   - Non-diffuseness indicators per room: the absorption contrast ᾱ(floor + ceiling) / ᾱ(walls), and
     the decay curvature C = 100·(T30/T20 − 1) % for both IRs (a curvature above ≈ 10 % marks a
     markedly non-straight decay; outside the corpus, not verified; product choice, stands (AQ9); the
     curvature is reported only). With absorbing floor and
     ceiling and hard walls, expect T_sim < T_meas from this mechanism (Vorländer §4.4.2, Table 4.1;
     expert recommendation, outside the corpus). Next to them, per pair, the Phase 04 render's
     per-axis energy shares and k_real (Phase 04 scope 3), reported only: there is no diffuseness
     threshold (Kuttruff §8.5).
   - Low-band filter bias: 63 Hz and 125 Hz values with B·T < 16 (B ≈ 0.71·f_c; Jacobsen's rule,
     relaxed to ≈ 4 with time-reversed filtering) are flagged; EDT is affected sooner (expert
     recommendation, outside the corpus).
     Next to that flag, the result of the scope 7 paired noise test's case B (125 Hz, T = 0.3 s,
     plateau regime; reported, not gated) is cited for the bands it concerns.
4. CI: a **nightly** workflow (`.github/workflows/nightly.yml`, `schedule` + `workflow_dispatch`) on
   Linux. It runs the validation, uploads the report as an artifact, and **fails on any change of the
   simulated metrics against the baseline simulation**, in either direction: any band's simulated T30
   or EDT by more than ±2 % relative on the octave meter (all bands) or on the AX23 half-octave meter
   (1, 2, 4, 8 kHz; decider D4), or simulated C80 (octave only) by more than ±0.2 dB (0.4 and 0.2 of the
   Table 6.1 jnd; T30 has no corpus jnd and the jnds are stated for 500–1000 Hz, so these are
   change-detection limits, not perceptual ones). Both meters' readings are stored in
   `validation_baseline.json`. The sim–meas errors (jnd-normalised,
   |sim − meas|/jnd) are recorded in `validation_baseline.json` and reported, never gating.
   AX23(a) (tail-only renders) does not apply here: AX23(a) concerns the Eyring comparison of the
   tail. Scope 4 is change detection on the full hybrid IR, which is what the user hears. The tail's
   own T30 is already gated against Eyring in Phase 04 CI, and the bias test shows that the full-IR
   gate detects a 5 % tail change. Reversal: if the half-octave readings are not bit-stable across the
   CI runner image, they are recorded only, not gated. An
   intended change, improvements included, updates the baseline only through
   `tools/ci/update_goldens.py` with a reason. The render is deterministic (fixed `tailSeed`), so the
   limits only absorb floating-point drift; a change that alters the tail's random draw sequence gives
   a new realisation and needs a baseline update. Also run it once on the phase PR.
5. An A/B listening pack: dry test material convolved with the measured IR and with the simulated IR,
   loudness-matched (BS.1770), named `A_*.wav`/`B_*.wav` with the key in a separate `key.txt`. Use
   public-domain or self-generated dry material only.

6. **Reference comparisons** in `tools/acoustics` (Python, not `src/sim`; they add comparisons and
   report lines, not a method change). Results go into the report, per room and pair, next to the AQ9
   errors.
   - **Decay predictors:** beside Eyring, the radiosity effective absorption exponent a* for Lambert
     walls (Kuttruff §5.7 Eqs. 5.53–5.56, T = 0.161·V/(S·a*)) and γ²-Eyring (Kuttruff Eq. 5.34 with
     Table 5.1), the latter for information only: on Kuttruff Table 5.2 cases 2 and 4 it moves T away
     from the iteration result. a* assumes s = 1 on all walls; with low s the true T can fall on the
     other side of Eyring (Kuttruff §9.4). The report gives the mean |T30 error| at 500 Hz–2 kHz (AQ9)
     for Eyring, a* and γ²-Eyring against BRAS, with the rooms listed sorted by the absorption-contrast
     indicator of scope 3 **and** by the largest single-face share of the total absorption. No
     threshold splits them: the contrast ratio alone cannot separate Kuttruff Table 5.2 cases 5 and 6
     (+2.3 % against +28.6 % vs Eyring). Air absorption enters both as 4mV added to the denominator;
     for a* this is equivalent to an exp(−mR) factor in the kernel (a* = a₀ + 4mV/S, Kuttruff §4.5 with
     Eq. 5.55), for γ²-Eyring it factors out of Eq. 5.29. γ² is the Table 5.1 row where the room's shape
     is tabulated, else 0.4 (Kuttruff §5.5). The choice changes T by ≈ 0.4 % in Table 5.2 case 4
     (γ² ≈ 0.376, linearly interpolated between Table 5.1's 1:2:2 = 0.363 and 1:2:5 = 0.403 rows, against 0.40); in general ΔT/T ≈ (Δγ²·a/2)/(1 − γ²a/2) with a = −ln(1−ᾱ) (Kuttruff
     Eqs. 5.33–5.34), e.g. ≈ 1 % for case 3 with 0.342 against 0.4, and a few % in elongated rooms with
     high ᾱ. a* solver patches for the Table 5.2 test: 88 equal elements for the 1:2:3 room (cases 3–6,
     Miles' example, Kuttruff §5.7) and 96 equal elements (6 × 4²) for the cube (cases 1–2); for BRAS rooms,
     halve the patch size until a* changes by < 1 %. **Decision rule (B12)** (decider report 8, accepted by Maisara, 2026-11-05): Phase 05
     compares predicted T₆₀ (deterministic, so no seed noise, but not error-free: a* is converged to < 1 % per patch halving and the γ² choice moves γ²-Eyring by ≈ 0.4–3.6 % (Kuttruff Eqs. 5.33–5.34), both the size of the 1.25-point margin) with measured T30 at 500 Hz–2 kHz,
     room-averaged. A predictor replaces Eyring for all scenes (NFR-8: one predictor, no per-room
     choice) only if it lowers the mean |error| by ≥ 0.25 working jnd (1.25 % points) and makes no room
     worse by > 1 jnd (5 %). Otherwise Eyring stays. Shown separately for uniform and uneven α.
     Conditions (decider report 11, accepted by Maisara, 2026-11-05): (i) a predictor counts as lowering the error only if it does so with a* converged to < 0.4 % per halving (margin/3, by analogy with AX11); (ii) a predictor with a free modelling input (γ²) must meet the rule at every admissible value: the Table 5.1 row and 0.4; (iii) the 5 % T jnd is a working value from outside the corpus (Vorländer Table 6.1 gives 5 % for EDT, not for T); (iv) only the initial-estimate α set counts: the fitted set is circular in Eyring's favour by construction (its α were scaled so that Eyring matches the measured T; researcher finding F6, BRAS documentation, outside the corpus) and is reported only. **Meter (AX23, decider D3):** the rule runs twice on the room-averaged measured T30, run 1 on octaves at 500 Hz, 1 kHz, 2 kHz and run 2 on octaves at 500 Hz and the half-octave meter at 1 and 2 kHz (outside the corpus), each under conditions (i)–(iv) unchanged; a predictor replaces Eyring only if both runs pass; if they disagree the outcome is "meter-dependent, Eyring stays", reported with both runs. **Octave-only branch (decider E2; outside the corpus):** B12 runs on octaves only (run 1) iff all hold, else the both-meters rule above: (1) the scope 7 calibration's entry condition holds (measured D ≥ 13 dB at 1 kHz and at 2 kHz in both variants, model check passed); (2) room set: every BRAS room that enters B12 (initial-estimate α set, condition (iv)), with its usable-range-evaluable AQ9 bands; (3) per room and band (500 Hz, 1 kHz, 2 kHz): r = T30(slower octave neighbour)/T30(band) from the room-averaged (pair-mean) measured octave T30; b_band = the model bias at that r and the measured D(f_c) of the matching variant, b = 0 when r ≤ 1; S_room = 2·mean of b_band over the room's evaluable AQ9 bands (% points); S_all = 2·mean over rooms (equal weight) of the per-room band means; (4) octave-only is allowed iff no room has an evaluable AQ9 band with r > 1.1, S_all ≤ 0.42 points (the 1.25-point margin / 3, as condition (i)), and every S_room ≤ 1.67 points (the 5 % "no room worse" limit / 3). 2·mean(b) is the worst-case change in two predictors' |error| gap when they straddle the measurement (interrogator D-12), a bound held to margin/3 like the a* convergence error. The report prints r, b_band, S_room, S_all and the branch applied. An outcome from BRAS alone is labelled "input-limited" in the AQ2 change request, and Maisara decides on it (C2). The replacement is implemented in a later phase, through an AQ2 change (BUILD_PLAN §5 B12).
   - **Reference hybrid (AX21):** at each specular hit, inject s(1−α) of the incident energy into the
     Lambert boundary patch hit, at the hit time (Kuttruff Eq. 4.24; Gilbert, §4.6). Propagate it with
     the **mixed specular/diffuse** form, not the all-Lambert Eq. 4.28: at every later hit, split the
     energy into s (re-radiated per Lambert) and 1−s (continuing specularly): Joyce's reflection matrix
     R_j (Kuttruff §4.6, Eq. 4.35) with the §5.2 split s(1−α) / (1−s)(1−α); Gilbert (§4.6) splits the
     boundary into specular and non-specular portions. Gather the diffuse part at the
     listener with Eq. 4.29, and add it to the early part before t_mix,e. Patches as for a* (above),
     time step 1 ms (Kuttruff §9.8 typical class width). The gathered energy is added as a per-band
     energy envelope to the squared band IR before the Schroeder integral and C80 (EDT and C80 are
     energy integrals, Vorländer Eqs. 6.4, 6.7). The report gives the EDT and C80 errors against BRAS
     with and without it. **Per-band s (B10)** (decider report 8, accepted by Maisara, 2026-11-05): the reference hybrid also runs with BRAS
     per-band s (tools only, no contract change). If that changes the room-averaged AQ9 EDT or C80
     error by ≥ δ, or any room's by > 1 jnd, B10 moves ahead of phase-05b, so B11 is validated only
     once; otherwise it stays after 12. The tail decay source is **not** a*; it is decided by the decay-predictor
     evidence above.
     **X-b bound (AX16):** report per band (500 Hz–2 kHz; other bands for information)
     ΔL_b = 10·log10(E_target,b(AX16) / E_target,b(hybrid)), both in the same Hann window
     [t_dir,e + 2.5 ms, t_mix,e] and both referred to t_mix,e. Compute it for every BRAS pair and for the
     six Phase 04 test rooms (per-face α differs between faces, so their ΔL_b mixes X-b with the
     hit-count residual), and for Kuttruff Table 5.2 layouts 2, 4, 5 and 6 with the solver called
     directly. The hit-count residual alone is isolated by also computing ΔL_b in the three uniform-α
     (A) s-cases of BUILD_PLAN §5 B11 (α = 0.15, 20×30×10 m), where AX16 is exact (Kuttruff §5.2).
     Table 5.2 layouts 2, 4, 5 and 6 are run at s = 0.1, 0.25, 0.4 and 1 on all faces (as in B11).
     "Everywhere" means every case in bands 500 Hz–2 kHz; the 1 dB is G's jnd (Table 6.1, stated for
     500–1000 Hz, applied by extension to 2 kHz); other bands are reported. Both E_target values are
     deterministic, so ΔL_b needs no statistical margin. Reading: if |ΔL_b| ≤ 1 dB
     everywhere, X-b is accepted as is and the measured bound is recorded in AX16; if |ΔL_b| > 1 dB
     anywhere, phase-05b (B11) switches tail-level matching to the hybrid's propagated diffuse energy
     (even if rendering early scattering is not promoted), under the same independent-reference
     validation. This is model against model: it bounds what B11 would change, not a measured truth.
     **Promotion evidence (BUILD_PLAN §5 B11, check (B)):** the AQ9 metric for EDT and C80 (mean
     |sim − meas|/jnd over 500 Hz, 1 kHz, 2 kHz per pair, averaged over pairs per room, then over rooms
     with equal room weight), with and without the hybrid. Vorländer Table 6.1 states these jnds for
     500–1000 Hz only; at 2 kHz they are applied by extension (AQ9). The 500–1000 Hz mean is printed as
     the in-range figure. Pass rule: the room-averaged error with the hybrid is not higher by more than δ = 0.25 jnd for either metric
     (Δ̂ ≤ +δ), and no room's Δ̂ exceeds +1 jnd on either, each with SE ≤ threshold/3 from seed-paired
     ensembles sized per "Paired comparisons" below. Report the per-room gain sorted by absorption contrast,
     largest single-face absorption share and broadband s, with no threshold. If BRAS has too few
     uneven-α or low-s rooms, no minimum count applies: the report and `bras_mapping.md` state "B11 not
     validated against measurement for uneven-α / low-s rooms" (F2). Promotion into `src/sim` follows
     the B11 rule only; a check at s = 1 alone is circular.
   - **Mixing-time handover:** EDT and C80 with t_mix,e from the Phase 04 rule against the same with
     floors at t_dir,e + 80 ms and t_dir,e + 140 ms (Vorländer §6.4, §15.3; Begault Ch. 3). A floor
     raises the rule's lower bound (t_mix,e ≥ t_dir,e + floor); it does not fix t_mix,e. Report per band
     whether they differ by more than 1 jnd (Vorländer Table 6.1: EDT 5 %, C80 1 dB; Table 6.1 states
     these jnds for 500–1000 Hz only). This needs a validation-only `render_cli` override of that lower
     bound (not in the contract). Run the three handovers (Phase 04 rule, floors t_dir,e + 80 ms and
     + 140 ms) on both the Phase 04 IR and the reference-hybrid IR. The reference-hybrid run is the
     arbiter (on the Phase 04 IR a later floor mostly measures the AX21 deficit). For each, report the
     AQ9 error metric (mean |sim − meas|/jnd at 500 Hz, 1 kHz, 2 kHz) for EDT and C80. Vorländer Table 6.1 states these jnds
     for 500–1000 Hz only; at 2 kHz they are applied by extension (AQ9). The 500–1000 Hz mean is
     printed as the in-range figure. A floor replaces the current lower bound (through an AX change, raising the lower bound only)
     only if, on the reference-hybrid IR, all three hold, with seed-paired ensembles sized per "Paired
     comparisons" below: (a) |Δ̂| > 1 jnd for EDT or C80 in at least one evaluable pair; (b) the
     room-averaged mean |error|/jnd falls by at least δ = 0.25 jnd for both EDT and C80 (Δ̂ ≤ −δ);
     (c) no room's Δ̂ exceeds +1 jnd on either. Each comparison requires SE ≤ threshold/3 (AX11).
     Otherwise the current rule stands (decider D1, accepted by Maisara, 2026-11-05; margin: decider
     report 7, FE-01). As context, report per room the perceptual mixing times t_mp50 and t_mp95 of
     Lindau, Kosanke & Weinzierl 2012 (JAES 60(11), Eqs. 12–14; external source, DOI
     10.14279/depositonce-15236, researcher finding F20; scope: binaural, near-shoebox rooms, V up to
     about 10 000 m³) next to t_mix,e; no t_mp95 floor arm is added (decider report 11, accepted by Maisara, 2026-11-05).
   - **Paired comparisons: margin and ensemble size** (decider report 7, FE-01 and DN5, accepted by
     Maisara, 2026-11-05). Δ̂_X = (room-averaged AQ9 error of metric X with the change) − (same, base),
     X ∈ {EDT, C80}, on seed-paired ensembles; δ = 0.25 jnd. "Not worse" means Δ̂_X ≤ +δ; "lowers"
     means Δ̂_X ≤ −δ; "no room worse by more than 1 jnd" means Δ̂_room,X ≤ +1 jnd; "moves by more than
     1 jnd" means |Δ̂_pair,X| > 1 jnd. Each is valid only if its standard error is ≤ (its threshold)/3:
     SE(Δ̂_X) ≤ δ/3 = 0.083 jnd, and SE(Δ̂_room,X), SE(Δ̂_pair,X) ≤ 1/3 jnd. Error rates at that
     SE: "not worse" and the per-room rule fail falsely with 0.135 % at a true Δ = 0 (less for any true
     Δ < 0); "lowers" passes falsely with 0.135 % at a true Δ = 0 and fails falsely with 0.135 % at a
     true Δ = −2δ; the two-sided "moves by more than 1 jnd" passes falsely with 0.27 % at a true Δ = 0.
     For the (B) family of m = 2 + 2·n_rooms comparisons, the false-failure rate at Δ = 0 is about
     m·0.135 % (e.g. 4 rooms: 10 comparisons, ≈ 1.3 %). Residual tail noise survives the pairing
     because the tail can start before 80 ms (C80's early integral) and the EDC integrates it (EDT)
     (Vorländer Eq. 6.4; derived); averaging repeated runs reduces it (by analogy with the ray-tracing
     fluctuations of Vorländer §11.2.5).
     **Ensemble size:** first a pilot per comparison, n ≥ 51 seeds through both arms (AX19's sampling
     rule: relative standard error of σ₁ ≤ 10 %). From the single-realisation metrics take the SD of the
     paired difference: σ₁,Δ for the room-averaged error, σ₁,Δ,room per room, σ₁,Δ,pair per pair (for
     the handover (a) only). Then R ≥ max(144·σ₁,Δ², 9·σ₁,Δ,room², 9·σ₁,Δ,pair²), σ in jnd, rounded up
     ((σ₁/(tol/3))² with tol = δ or 1 jnd). Pilot seeds may count towards R. One R per comparison, used
     in both arms with the same seeds. After the run, check that σ₁,Δ/√R meets the bound; if not,
     increase R. If R > 2 000 per arm, run it outside CI when the projected time is ≤ 24 h on one
     CI-class machine (validation compute is not user CPU, so this does not touch NFR-2). Beyond that,
     δ goes to Maisara, with the δ that 2 000 per arm would support, δ·√(R/2000), and the projected
     time. Until she decides, the comparison counts as 'no evaluable pair': B11 promotion needs her
     sign-off on (A) alone, and no handover floor is adopted (decider report 8, accepted by Maisara, 2026-11-05). The report prints Δ̂, SE, R and pass/fail for each comparison.
   - **Humidity bound (AX4):** per band, the Eyring T60 at 40 % and 70 % RH, 20 °C (Kuttruff Table 6.1
     rows, Eq. 5.24) relative to the AX4 atmosphere, for each room; for example 8 kHz in a room with
     V = 10 000 m³, S = 4725 m², ᾱ = 0.15 gives −11.6 % / +17.2 % (an air-dominated room would differ
     more). m comes from Kuttruff Table 6.1 at 500 Hz–8 kHz and from the code's `AirAbsorption` below
     500 Hz (the humidity effect there is negligible: the Vorländer Annex 20 °C rows are identical at
     125–500 Hz). Where BRAS documents its measurement conditions, render once more with the AX4
     override set to them, to separate model error from atmosphere mismatch. Not shown in the UI.

7. **`tools/acoustics` meter tasks** (AX23 and Lundeby, decider D1, D5, D7, N1, 2026-11-06):
   - `metrics.py`: correct the "known limits" sentence on comparisons through the same filterbank (fair
     only if both IRs have the same neighbour ratio r and the same leak); correct the `lundeby`
     docstring's "a measured, near-monotonic decay is unchanged" to what the paired noise test below
     shows; expose the intercept of the final Lundeby late-decay line (needed by the usable-range test).
   - **Leak calibration** (D1, E1; reported, not gated; results recorded in AX23; outside the corpus
     except the model): test signal = sum of per-octave components, each independent white noise
     band-limited by an ideal FFT brick wall to f·2^(±½), times exp(−6.91·t/T_band), all at equal start
     power (product choice). Band f_c ∈ {500 Hz, 1, 2, 4, 8 kHz} at T_b = 1.0 s; its slower neighbour at
     r·T_b, r ∈ {1.05, 1.1, 1.2, 1.3, 1.5, 2.0}, in two variants (slower neighbour below, and above);
     all other bands at T_b; R from AX11 for SE ≤ 0.2 % (R ≥ 51 is safe for σ₁ ≤ 1.5 %). Record both
     meters' bias. **Leak D**, per f_c, variant and r: D = 10·log10(E_own/E_leak), E_own = total
     energy of the band's own component alone after the band's octave filter, E_leak = total energy of
     the slower neighbour's component alone after the same filter, onset to end, ensemble-averaged
     (a is exactly their ratio at t₀). **Model check:** the interrogator's two-term model (Kuttruff
     Eqs. 3.64–3.68 basis) E(x) = e^(−x) + a·e^(−x/r), a = 10^(−D/10), x = 2δ_b·t, T30 window
     x = 1.15–8.06, T_read/T_b = 1/(1 − Δ), Δ = [ln(1+q₂) − ln(1+q₁)]/6.91, q = a·e^(kx),
     k = (r − 1)/r, predicts the octave T30 bias from the measured D and r; record measured D,
     predicted bias, measured bias and residual in AX23. Reversal: a residual > 0.6 % means the model
     is not adequate: B12 stays on both meters permanently and the AQ9 "leakage-sensitive" reason
     quotes the measured bias table.
   - **Paired noise test** (D5, E3; outside the corpus): R noise × exponential realisations per
     condition; per realisation i, bias_i = T30_noisy,i / T30_clean,i − 1 (the pairing isolates the
     noise handling). Noisy arm = the measured-IR path of `run_validation.py`: decay + independent
     stationary white noise scaled per band to 48, 55 or 65 dB below the decay's band power at t₀
     (48 = ISO 3382-1's 45 dB T30 minimum + 3 dB, product choice, so the usable-range rule does not
     reject a random subset at the edge; researcher F1/F2), file 3.5 s with the last 1024 samples
     Hann-faded (BRAS-like, researcher F14), fade trimmed (D6), then the `metrics.room_metrics` octave
     band. Clean arm = the same decay realisation without noise or fade, same band filter, Schroeder
     integration to the end of the file (as N1). **Case A** (AQ9 regime): 18 conditions, 500 Hz,
     1 kHz, 2 kHz × T = 1.0, 2.0 s × the three noise levels; gate |mean_i bias_i| ≤ 0.6 % in every
     condition, with SE ≤ 0.15 % per condition (tol/4: tol/3 would give ≈ 4.9 % family false failure
     over 18 conditions, tol/4 ≈ 0.11 %). R: pilot n ≥ 51 per condition, σ₁,Δ = SD of bias_i in %,
     R = max(51, ⌈(σ₁,Δ/0.15)²⌉) per condition; check the SE afterwards. Seeds are fixed, so the test
     is deterministic in CI; with the interrogator's +0.45 % estimate at 45 dB the real headroom is only
     0.15 %, so a fail is a real finding. A condition where any realisation returns T30 None fails as
     "unsuitable" (reported separately), not as a bias failure. EDT and C80 are computed and reported
     per condition, not gated (0.6 % derives from B12, which uses T30 only; expected effect < 0.01 dB).
     0.6 % is half of B12's 1.25-point margin, since a common bias b shifts a predictor gap by up to 2b
     (product derivation). **Case B** (plateau regime): 125 Hz, T = 0.3 s, reported, not gated.
     Reversal: if any case A condition fails, measured IRs run without the hull behind a flag,
     through a new AX.
   - **Simulated-EDC test** (N1): for a noise-free exponential decay ending at −90 dB, the
     `metrics.room_metrics` EDC at −35 dB differs from integration to the end by ≤ 0.01 dB.

## Out of scope

Changing the simulation method. If results are poor, the PR proposes options (e.g. ray tracing for the
tail, better absorption mapping, a Sabine/Eyring/Arau-Puchades comparison) as **follow-ups for the
Expert**. It doesn't implement them. The reference comparisons of scope 6 live in `tools/acoustics`
and do not change the simulator.

## Acceptance criteria — automated

- [ ] `fetch_bras.py` verifies checksums. A corrupted file is detected (unit test with a tampered cached file).
- [ ] The report generates reproducibly (two runs give identical numbers).
- [ ] The nightly workflow runs green on the baseline. With the environment variable test hook
      `MAKROOF_TEST_BIAS_T60=1.05` (scales the tail's per-band T60 only; the hook exists only in debug
      builds) the gate **fails** on T30, and the simulated octave-meter T30 (no half-octave assertion) in each of the 500 Hz, 1 kHz and 2 kHz
      bands with T30 ≥ 3·(t_mix,e − t_dir,e) has risen by between +3 % and +5.5 % (the full +5 % when
      the EDC's −5 dB point lies after t_mix,e; less when the early part covers part of the fit range,
      e.g. ≈ +4.7 % at T = 0.5 s, t_mix 80 ms; below T ≈ 2.9·(t_mix,e − t_dir,e) the rise can fall
      under +3 %, e.g. +2.5 % at T = 0.2 s, so shorter bands are reported only). At least one of the
      three bands must meet the condition, else the test scene is unsuitable. The test does not assert on C80 or EDT (C80 moves only ≈ −0.21 dB at
      t_mix = 80 ms, at the 0.2 dB limit).
- [ ] AQ9 pass/fail is printed per room (mean over pairs) and per pair, with the α set of each, and
      stated in the report summary; a per-pair pass/fail mostly reflects noise in position-specific
      details (RR19 found the per-position structure mostly not reproduced; external source)
      (decider report 11, accepted by Maisara, 2026-11-05).
- [ ] The a* solver reproduces the iteration column of Kuttruff Table 5.2 (all six cases), called
      directly (the α = 0 walls of those cases are forbidden in scenes by AQ3), within **±1 %**, with 88 equal
      elements for the 1:2:3 room (cases 3–6, Miles' example, Kuttruff §5.7) and 96 equal elements
      (6 × 4², the nearest equal layout) for the cube (cases 1–2) (Maisara, 2026-11-05). The corpus's own two methods agree to ≈ 0.5 %
      (Fig. 5.10's slope of −1.57 dB per mean free path, with n̄ = cS/4V, gives 1.216 s against
      case 4's 1.21 s).
- [ ] The report contains the scope 6 comparisons (decay predictors, reference hybrid, handover,
      humidity bound); they are reported, not gated.
- [ ] Scope 7 paired noise test: each of the 18 case A conditions: |mean paired T30 bias| ≤ 0.6 %
      with SE ≤ 0.15 % (case B, EDT and C80 reported, not gated).
- [ ] Scope 7 simulated-EDC test: EDC at −35 dB within 0.01 dB of integration to the end.
- [ ] Scope 7 leak calibration runs and its results (both meters' bias per f_c, variant and r; measured leak D;
      model-predicted bias and residual)
      are printed and recorded in AX23; reported, not gated.
- [ ] The report prints per band the octave and half-octave readings, r, the "meter-dependent",
      "leakage-sensitive" and "noise not verified" flags, both usable-range margins, the secondary
      half-octave AQ9 mean and the AX4 override render beside the AQ9 line.

Failing AQ9 thresholds does **not** fail CI. It goes in the BUILD_PLAN status notes as "AQ9 met in
x/y scenes". Maisara decides at the Phase 05 review (via /fix-plan) whether to schedule
B10/B11/B12/B2 inside v1. Phase 13's beta decision lists 'AQ9 met in x/y' and every recorded known
deficit (AX16, AX21, AX22, AQ10 misses) (decider report 8, accepted by Maisara, 2026-11-05).

## Listening / manual checklist (Maisara)

Note: the A/B pack uses the omni IRs, so only monaural attributes can be compared: reverberance,
clarity and coloration. Level is removed by loudness matching. Coloration is heard under monaural
conditions, which exaggerate reflection coloration compared with binaural listening (Blauert §4.4.2).
Spaciousness (ASW, LEV) cannot be compared.

Headphones, A/B pack, without looking at `key.txt` first:
- [ ] For each pair, can you tell which is real? Note what differs: brightness, decay length, early
      "slap", graininess.
- [ ] Then check `key.txt` and write your notes on the PR. They go to the Expert with the report.

## Contractor review focus

The shoebox reduction rules (are they generic, not per-room tweaks?), the material mapping, the metric
comparison method, the scope 6 reference predictors and reference hybrid (independent of `src/sim`,
a* against Table 5.2), and whether the conclusions in the report follow from the numbers.

## Risks

- The documentation may be ambiguous about geometry or material assignment. Record each choice in
  `bras_mapping.md`; a reviewer can then challenge it.
- Expect misses. Geometrical acoustics is exact only in idealised cases, and a small room breaks its
  large-room and broadband conditions at low frequencies (Vorländer §11.5). The round robins name the
  absorption input data, the presence of a scattering model, and the chosen absorption and scattering
  coefficients as decisive. The shoebox reduction adds a geometry error the corpus does not quantify.
  This phase exists to surface that early (F2, F3).
- On BRAS initial data, blind mature hybrids stayed above 1 jnd at 500 Hz–2 kHz in most cases, driven
  by the input data (RR19: Brinkmann et al. 2019, JASA 145(4), DOI 10.1121/1.5096178; external source); the corpus reports 1–2 jnd
  achievable with carefully chosen coefficients (Vorländer §11.5, RR-III). An AQ9 miss on initial data
  is therefore expected and is read against the RR19 spread before it is escalated (decider report 11, accepted by Maisara, 2026-11-05).
- BRAS gives at most three usable rooms with estimated inputs: results are evidence, not validation. A
  second measured dataset is required before the Phase 13 beta decision (BUILD_PLAN §3 F2); Maisara
  decides, the researcher agent searches. It does not block this phase (decider report 11, accepted by Maisara, 2026-11-05).
  Second source adopted: Arni + dEchorate, phase 05d, run after this phase (decider report 15, accepted by Maisara, 2026-11-05).

## Definition of done

Automated criteria green; report committed; status row 05 `done` with an "AQ9 met in x/y" note per room
and per pair, by α set (BRAS: evidence, not validation);
the PR summarizes findings for the Spatial Audio Expert.
