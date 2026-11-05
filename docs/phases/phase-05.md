# Phase 05 — Validation against measured impulse responses + accuracy report

Size: **M** · Depends on: 04 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ2, AQ9) and §3 (F2, F3), PRD NFR-1, NFR-8, Q2, Q9

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
  jnd in the corpus). Signed per-band deltas are reported without gating (their sign shows bias). The
  report also gives the mean over the source/receiver pairs of each room.
- **AQ2** method under test. **NFR-8**: no per-scene factors. If a room fails, report it.

## Data

- **BRAS** — *Benchmark for Room Acoustical Simulation* (TU Berlin; licence CC BY-SA 4.0). It contains
  room scenes with geometry descriptions, material absorption/scattering data and measured omni and
  binaural IRs.
- Write `tools/validation/fetch_bras.py`. It downloads only the files needed (scene documentation,
  material tables, omni RIRs for the selected source/receiver pairs) from the official repository
  (DepositOnce), verifies SHA-256 checksums stored in `tools/validation/bras_manifest.json`, and caches
  them under `~/.cache/makroof/bras`. **Never commit the data** (CLAUDE.md rule). Add the attribution to
  `docs/THIRD_PARTY.md`.
- Before writing code, the session must read the BRAS documentation and record in
  `docs/validation/bras_mapping.md` which scenes were chosen and why. Pick the rooms whose geometry is
  closest to a rectangular box (likely the small seminar room and similar). State how each real room was
  reduced to a shoebox, by these generic rules, and which BRAS material set is used:
  - **Dimensions:** keep the documented mean floor-to-ceiling height h (define h = V / floor area when
    the ceiling varies); solve the floor from a·b = V/h and a + b = (S − 2V/h)/(2h), the longer side
    along x (AQ1 axes). A real solution exists iff S ≥ 2V/h + 4√(V·h); otherwise use the square floor
    a = b = √(V/h) (the smallest S for that V and h) and report the S error. Choosing to keep h is a
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
  secondary, clearly labelled run. Fitted data partly includes the answer, so it isn't proof of accuracy.
- If no BRAS room can be reasonably reduced to a shoebox, the phase is `blocked`. Report it. That's
  evidence for F3 and Q2.

## Scope

1. `tools/validation/fetch_bras.py`, `bras_manifest.json`, `docs/validation/bras_mapping.md`.
2. `tests/scenes/validation/bras_<room>_<src>_<rcv>.json` — contract scenes for the chosen pairs
   (source and receiver positions mapped into the shoebox frame).
3. `tools/validation/run_validation.py` — renders each scene with `render_cli --mode omni --ir`,
   computes ISO 3382 metrics for simulated and measured IRs with `tools/acoustics`, and writes:
   - `docs/validation/report-phase05.md`: a table per scene with band metrics, deltas and an AQ9
     pass/fail summary, plus EDC overlay plots saved as PNG next to the report (matplotlib, pinned).
   - `tests/golden/validation_baseline.json`: the baseline simulated metrics for the nightly gate
     (item 4) and the recorded sim–meas errors.

   Comparison conditions, applied identically to simulated and measured IRs with the same
   `tools/acoustics` octave filter bank:
   - **Time origin:** the direct-sound arrival of each IR (Vorländer §6.4.2 Eq. 6.5 t₀), detected the
     same way in both: first sample within 20 dB of the broadband peak (ISO 3382-1 practice, outside
     the corpus). Not file t = 0, not the peak sample. C80 (Eq. 6.7) and EDT are taken from it.
   - **Measured EDC:** backward integration (Eq. 6.4) from the band's noise-floor intersection, with
     noise-energy compensation (ISO 3382-1 practice; the corpus gives no procedure). Integrating to
     file end without compensation biases T30 (e.g. +12 % at noise −50 dB, T = 1 s, 3 s file).
   - **Simulated EDC:** integrated to the end of the IR (the noise-free decay at a −90 dB end leaves
     ≈10⁻⁵ dB error at −35 dB, Eq. 6.4). A band whose IR ends (12 s cap) before the decay has fallen
     62 dB is flagged (keeps the −35 dB point within 0.01 dB).
   - **Usable range:** T30 is evaluated only if the band EDC reaches −35 dB at least 10 dB above the
     band noise level (margin outside the corpus; it limits the noise contribution at −35 dB to
     0.4 dB). Otherwise T20 (−5 to −25 dB) is reported for that band, flagged; a 500 Hz–2 kHz band
     without T30 is "not evaluable" and is excluded from the AQ9 T30 mean, never counted as a pass.

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
     reference (Eq. 6.5). Where the data permit, G deltas are reported per band from the IRs.
   - BRAS scattering data enter the scenes through AX17: one broadband s per surface. Because s
     typically rises with frequency (Vorländer Fig. 3.11, Annex scattering tables), this overstates s
     at 500 Hz and understates it at 2 kHz, so per-band deltas in the AQ9 bands include an AX17 input
     error, flagged next to them.
4. CI: a **nightly** workflow (`.github/workflows/nightly.yml`, `schedule` + `workflow_dispatch`) on
   Linux. It runs the validation, uploads the report as an artifact, and **fails on any change of the
   simulated metrics against the baseline simulation**, in either direction: any band's simulated T30
   or EDT by more than ±2 % relative, or simulated C80 by more than ±0.2 dB (0.4 and 0.2 of the
   Table 6.1 jnd; T30 has no corpus jnd and the jnds are stated for 500–1000 Hz, so these are
   change-detection limits, not perceptual ones). The sim–meas errors (jnd-normalised,
   |sim − meas|/jnd) are recorded in `validation_baseline.json` and reported, never gating. An
   intended change, improvements included, updates the baseline only through
   `tools/ci/update_goldens.py` with a reason. The render is deterministic (fixed `tailSeed`), so the
   limits only absorb floating-point drift; a change that alters the tail's random draw sequence gives
   a new realisation and needs a baseline update. Also run it once on the phase PR.
5. An A/B listening pack: dry test material convolved with the measured IR and with the simulated IR,
   loudness-matched (BS.1770), named `A_*.wav`/`B_*.wav` with the key in a separate `key.txt`. Use
   public-domain or self-generated dry material only.

## Out of scope

Changing the simulation method. If results are poor, the PR proposes options (e.g. ray tracing for the
tail, better absorption mapping, a Sabine/Eyring/Arau-Puchades comparison) as **follow-ups for the
Expert**. It doesn't implement them.

## Acceptance criteria — automated

- [ ] `fetch_bras.py` verifies checksums. A corrupted file is detected (unit test with a tampered cached file).
- [ ] The report generates reproducibly (two runs give identical numbers).
- [ ] The nightly workflow runs green on the baseline. With the environment variable test hook
      `MAKROOF_TEST_BIAS_T60=1.05` (scales the tail's per-band T60 only; the hook exists only in debug
      builds) the gate **fails** on T30, and the simulated T30 in each of the 500 Hz, 1 kHz and 2 kHz
      bands has risen by between +3 % and +5.5 % (the full +5 % when the EDC's −5 dB point lies after
      t_mix,e; less when the early part covers part of the fit range, e.g. ≈ +4.3 % at T = 0.5 s,
      t_mix 80 ms). The test does not assert on C80 or EDT (C80 moves only ≈ −0.21 dB at
      t_mix = 80 ms, at the 0.2 dB limit).
- [ ] Each chosen scene's AQ9 pass/fail is printed and stated in the report summary.

Failing AQ9 thresholds does **not** fail CI. It goes in the BUILD_PLAN status notes as "AQ9 met in
x/y scenes" and is escalated.

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
comparison method, and whether the conclusions in the report follow from the numbers.

## Risks

- The documentation may be ambiguous about geometry or material assignment. Record each choice in
  `bras_mapping.md`; a reviewer can then challenge it.
- Expect misses. Geometrical acoustics is exact only in idealised cases, and a small room breaks its
  large-room and broadband conditions at low frequencies (Vorländer §11.5). The round robins name the
  absorption input data, the presence of a scattering model, and the chosen absorption and scattering
  coefficients as decisive. The shoebox reduction adds a geometry error the corpus does not quantify.
  This phase exists to surface that early (F2, F3).

## Definition of done

Automated criteria green; report committed; status row 05 `done` with an "AQ9 met in x/y scenes" note;
the PR summarizes findings for the Spatial Audio Expert.
