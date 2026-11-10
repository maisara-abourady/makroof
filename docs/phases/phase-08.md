# Phase 08 — Binaural output with a generic HRTF

Size: **L** (plan for two sessions; split into 08 and 08b if needed) · Depends on: 04, 05b, 05h, 07 (05b `done` in either outcome; with "not promoted", this phase builds on the specular-only early part, AX21). It depends on 05h, except that it may precede 05h on Seat 4's conditions per AX37 (5.3) (D-T5.3): (i) E_b and t_mix,e are read only via `TailMatch`; (ii) parity is checked within the same build; (iii) 05h re-renders the binaural goldens, re-measures binaural W1/W2 and re-runs item 8; (iv) this phase's listening items on concentrated absorption are marked provisional · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ6, AX3, AX5, AX35) and §3 (F7, F8), PRD FR-SIM-3, FR-SIM-4, FR-3D-9, A1; the D1 decision (`docs/review/board-smoke/hrtf-head/`, accepted by Maisara 2026-11-09) behind scope 1–3

## Goal

Headphone rendering (`outputMode = binaural`). Every early reflection reaches the listener's ears from
its true direction through a measured **generic HRTF**, and the late tail has the interaural coherence
of a diffuse field. The result is a 2-emitter × 2-ear binaural room impulse response (BRIR) applied by
the Phase 06 convolver.

## Assumptions in force

- **AQ6**: one generic HRTF, with the contract `hrtfId = "generic-v1"`. No personalization (deferred, B4).
- **AX3**: the head is upright, and yaw points toward the horizontal centroid of the emitters. If the
  centroid is within 0.1 m horizontally of the listener, the previous yaw is held (initial yaw = +y).
- **AX5**: deterministic; tail noise per ear is seeded from `tailSeed` with the per-output offset from Phase 04.
- **AX37 (5.3)** (phase 05b): this phase receives E_b and t_mix,e per emitter through `TailMatch` and no
  tail directions; `bandsAxisShares` is a labelled specular-only diagnostic. A directional late tail is
  backlog (§5 B18), behind Seat 1's blind test. **AX39**: one diffuse solve per scene, shared across
  output modes. **AX38**: the diffuse solve runs through the process-wide gate; W1/W2 include it.
- **AX35**: the data behind a released `hrtfId` is never replaced; a different head, campaign or re-converted
  set is `generic-v2` with the old data retained. Before this phase's goldens are frozen a converter re-run
  is a parameter change.

## Scope

### Session 1: HRTF data and lookup

1. **Licence first.** The dataset is decided (board decision loop D1, `docs/review/board-smoke/hrtf-head/`,
   accepted by Maisara 2026-11-09): `generic-v1` = **SADIE II**, subject **D1 (Neumann KU100)**, University
   of York, Zenodo record DOI 10.5281/zenodo.12092466, version **V2-2 (2024-06-18)**, file
   `D1_HRIR_SOFA.zip` (record MD5 `4850c1eb8e63e2d4f605edcdb4d5c883`; SHA-256 computed at the first
   download and pinned in `tools/hrtf/fetch_hrtf_source.py`, on the `fetch_corpus.sh` pattern: fetched by
   checksum into a git-ignored directory, **never committed**; the round-trip test (AC 2) skips with a
   marker when the source is absent unless `SPATIAL_REQUIRE_HRTF_SOURCE=1`, set in CI). SOFA at the
   record's native rate, read at pin time: the SOFA convention, native sample rate and `GLOBAL_Comment`
   are read and recorded then; the Armstrong et al. 2018 PDF is checked against the dossier's grid and
   length facts (F11/F12); and the converter's source-state consistency check (scope 3) runs on the
   pinned file in the same session, a "not confirmed" result being raised before any golden is frozen.
   Licence: **Apache License 2.0** ("Copyright 2018, University of York"; the York page's condition that
   the original dataset must be referenced whenever used in original or modified form; the citation
   Armstrong, Thresh, Murphy, Kearney 2018, Applied Sciences 8(11):2029, DOI 10.3390/app8112029; an
   Apache §4(2) change notice listing the converter's transformations: resampled, trimmed, grid subset,
   diffuse-field EQ computed and applied, onset removed, ITD stored). Record the licence text and
   attribution in `resources/hrtf/LICENSE-generic-v1.txt` and `docs/THIRD_PARTY.md`; the AC 1 script
   matches `LICENSE-<id>.txt` to the **header's** set id, not to a filename. Re-read the licence on the
   official record (the record's licence field and the SOFA `GLOBAL_License` attribute) at pin time.
   **Fallback:** if at pin time the record's licence is no longer Apache 2.0, or a lawyer reads the York
   sentence as more than attribution, fall to **MIT KEMAR** (check its licence the same way) under these
   conditions: the zone below −40° elevation is a declared unmeasured zone, never mirrored; the DF-EQ and
   tail-coherence averages are Voronoi-weighted with the missing cap reported in the header; DF-EQ on by
   default; the below-grid policy stored as header data, not renderer code; the head confound against the
   IEM baseline recorded. The TH Köln KU100 set is **excluded** under "unclear licence" (CC BY-SA 3.0 in
   the paper vs CC BY 3.0 in the Zenodo field); it re-enters only if both the SOFA `GLOBAL_License`
   attribute and a written answer from the record contact say CC BY, before the Phase 08 goldens are
   frozen. If neither allowed dataset is clearly licensed at pin time, mark the phase `blocked` and
   escalate. Don't ship data under an unclear licence.
2. `tools/hrtf/convert_sofa.py` (uses `sofar` or `netCDF4`/`h5py`, pinned; dataset-agnostic: it converts
   any SOFA set, the header below records which) — reads the SOFA file, resamples to 44.1/48/88.2/96 kHz
   (high-quality polyphase), trims to a common length (e.g. 256 taps at 48 kHz, scaled for other rates)
   with a **fade-out window at the trim, not a hard cut**, removes the common onset delay while keeping
   the ITD as a separate per-direction value (`onset_left`, `onset_right` in fractional samples), and
   writes `resources/hrtf/generic-v1.bin` (a simple versioned binary: header, direction grid,
   minimum-phase or raw HRIRs, ITDs). The original SOFA is downloaded by checksum (scope 1), **never
   committed**.
   - **Embed bound.** The committed four-rate `.bin` is ≤ ~32 MB (32·10⁶ B, whole file; the full
     8802-direction grid in four-rate float32 would be ≈ 104 MB). Four-rate float32 costs 11 784 B
     per direction (1473 taps × 2 ears × 4 B), float16 5 892 B, so the bound holds for **either** a
     float32 grid subset of **≤ ~2700 directions** (31.8 MB; 3000 would be 35.4 MB) **or** a float16
     grid subset of **≤ ~3000 directions** (17.7 MB; the count is a product choice near a 2702-node
     full-sphere grid, the bound is the bytes). Either subset keeps the lowest measured elevation
     row (−81°) and the 0°-elevation ring; the route is chosen in this phase so that AC 2 (−60 dB,
     both terms) and AC 4 (continuity) hold on the real file. **AC 2 measures the storage and
     decoding path plus the trim**, not the converter's transformations: its reference is built in
     the test from the pinned source by the converter's own pinned steps with the parameters read
     from the `.bin` header (pinned resampler; the **stored** DF-EQ curve applied; the **stored**
     `onset_left`/`onset_right` removed; the minimum-phase step if the header says the stored form
     is minimum-phase). Two residuals in the `residualDb` form (10·log10 Σ(decoded − reference)² /
     Σ reference² over the reference length, decoded = 0 beyond its end), per ear, stored direction
     and rate, both gated at −60 dB: the **storage term**, against that reference trimmed and faded
     identically (it cannot fail from truncation), and the **total term**, against the same
     reference left **untrimmed and unfaded**, so the energy the trim and fade remove counts as
     error. A total failure with the storage term passing is a truncation finding (trim length or
     fade), reported and handled through the interrogator, never by loosening a gate. For SADIE II
     the truncation term is expected small (York trimmed to 512 samples at 96 kHz = 256 at 48 kHz,
     with fades, dossier F12; what remains is whatever the converter's own fade window removes and
     what the pinned resampler and the DF-EQ filter realisation spread beyond the trim) and is
     measured, not assumed. The EQ's correctness is the DF-EQ
     identity AC's subject, not AC 2's; the pre-EQ data exists only as the fetched source and inside
     the test, and no product code path switches the EQ off. If the bound cannot be met with AC 2
     and AC 4 held, report it (decision reversal condition 3); don't loosen either gate.
   - **Dataset-agnostic header.** `generic-v1.bin` records: set identity; lab and campaign; record
     version and DOI; source SHA-256; converter version; sample rates and per-rate tap count; direction
     count and grid type; lowest/highest measured elevation (SADIE II: −81°/+90°, the −90° point
     interpolated by York); measurement distance (1.2 m); microphone position (built-in capsules); the
     source EQ state as publisher-documented plus converter-confirmed / not confirmed (scope 3); the
     converter's computed DF-EQ curve; the solid-angle (Voronoi) weights of the stored subset or their
     sum check (Σ w_i = 1); the weighted DF-EQ curve per ear; the weighted tail-coherence target per
     band; the unweighted DF curve for diagnostics; ITD method and sign convention; onset/minimum-phase
     treatment; the stored triangulation; a human-readable attribution string; fixed little-endian. No UI
     code or string table knows which head shipped: any About/credits text reads the header's attribution
     string; the main window and the mode switch never show a dataset name.
3. `src/sim/hrtf/HrtfSet.h/.cpp` — loads the embedded binary (embedded as a build-step object:
   `add_custom_command` → object / `.incbin`-style; no generated C++ byte array; `sim` stays JUCE-free).
   `HrtfSet` is one immutable process-wide object built off the audio thread, with an O(1)
   direction → triangle index; it assumes **no left–right symmetry** (a B4 personal set breaks it; the
   AC 3 mirror check stays a data test); `[alloc]` tests on `query` and on the BRIR build. Lookup:
   - `query(azimuth, elevation) → {hrirL, hrirR, itd}` with interpolation: triangulate the measurement
     grid (spherical Delaunay computed offline in the converter and stored), then barycentric
     interpolation of magnitude-aligned (onset-removed) HRIRs; prefer onset-removed/minimum-phase
     interpolation (Begault Ch. 4 "Problems with Interpolation Algorithms"). ITD is interpolated
     separately and re-applied as a fractional delay.
   - **Diffuse-field equalization, computed once from the set and always applied.** The converter's
     diffuse-field averages, the DF-EQ curve and the tail-coherence target (scope 5: the diffuse-field
     average of the interaural cross-spectrum), are computed over the **stored** direction subset with
     each direction weighted by the solid angle of its spherical Voronoi cell, w_i = Ω_i / 4π (the
     Voronoi cells are the dual of the stored Delaunay triangulation), per ear (DF curve) / per band
     (coherence target), **as power averages** in one-third-octave bands — L_b = 10·log10(Σ_i
     w_i · P_{i,b}), P_{i,b} the band-b mean of |H_i(f)|² (Begault Ch. 4 'Equalization of HRTFs':
     random-incidence noise levels in third-octave bands; Vorländer §16.1.1: incoherent waves) — the
     DF-EQ curve being C_b of the source and the converter applying −C_b (filter realisation
     recorded in the header; the band set recorded in the header), stored in the `.bin` header
     beside the weights' sum check (Σ w_i = 1), and reported by `--diagnostics` together with the
     unweighted curve, so the bias the weighting removes is visible on the pinned file. The
     converter applies its own weighted diffuse-field curve to every set it converts (per ear). The
     header records (i) the source's EQ state as documented by the publisher (SADIE II:
     diffuse-field equalised by York), (ii) the converter's computed curve, (iii) the post-EQ check:
     the weighted one-third-octave **power** average L_b of the converted set (per ear) is 0 dB
     within 0.1 dB in every band of the converter's curve (automated test, the DF-EQ identity AC; a
     numerical identity bound, one tenth of the level jnd). **Source-state consistency check (pin
     time):** if the computed curve C_b on the pinned `D1_HRIR_SOFA.zip` lies within ±1 dB in every
     one-third-octave band with centre from 200 Hz to 8 kHz, the header records "source:
     diffuse-field equalised (publisher), converter residual ≤ 1 dB"; if any band exceeds ±1 dB, the
     header records "source EQ state: not confirmed" and the phase raises it with Maisara and
     through the interrogator before the Phase 08 goldens are frozen. The curve above 8 kHz is
     reported, not gated. Nothing in the rule switches the application off. Provenance of the
     numbers (the decider's product judgement, not load-bearing for the head choice): 1 dB is
     Vorländer's general level jnd of roughly 1 dB (`vorlaender-auralization.md` abbreviations table
     and line 3167); Table 6.1's 1 dB row is strength G at 500–1000 Hz, so the
     per-one-third-octave-band use from 200 Hz to 8 kHz is by extension (as §5 B11 already says of
     Table 6.1); one-third-octave bands: Rumsey §3.2.4, Begault Ch. 4 "Equalization of HRTFs";
     200 Hz: the set's measured range (sweeps from 200 Hz, LF modelled below); 8 kHz: the top of
     `contract::kOctaveBandsHz` and of the AC 3 ILD band; 0.1 dB: one tenth of the jnd. Begault's
     ±1.5–2.5 dB diffuse-minus-free-field figure is not a tolerance.

### Session 2: BRIR assembly and tail

4. `src/sim/binaural/ListenerFrame.h/.cpp` — AX3 orientation; converts world-space directions of
   arrival (from Phase 03 image sources) into head-relative azimuth/elevation.
5. `src/sim/binaural/BrirBuilder.h/.cpp` — for each emitter:
   - **Early part:** for each image source (from Phase 03, using its per-band amplitude, delay and
     direction), add `band-filtered(amplitudes) * HRIR(direction)` into the left and right ear buffers at
     the arrival time plus the per-ear ITD. **No 2° grouping until the Phase 08 benchmark shows it is
     needed; measure first.** Only if the measured BRIR build time calls for it, group image sources by
     direction cell (e.g. 2° bins) above reflection order 3 and render each group once, and document the
     approximation. The direct path and orders 1–3 are never grouped.
   - **Late tail:** two noise tails (left/right seeds) with the Phase 04 per-band envelopes, then mixed per
     band so the **interaural coherence** follows the diffuse-field model for a head: compute the target
     coherence per band from the HRTF set itself (diffuse-field average of the interaural cross-spectrum,
     solid-angle (Voronoi) weighted over the stored subset, done in the converter, scope 3), and apply it
     with the standard 2×2 mixing
     (`L = a·n1 + b·n2, R = a·n1 − b·n2` with a and b set from the target coherence), then apply the
     diffuse-field HRTF magnitude per ear.
   - Energy: the binaural BRIR's per-band energy (average of the two ears, diffuse-field equalized)
     equals the omni IR's per-band energy within ±1 dB. This keeps levels consistent between modes.
   - E_b and t_mix,e are read only via `TailMatch` (AX37 (5.3)), from the one diffuse solve per scene
     (AX39); E_b is bit-identical between omni and binaural and between the ears (AX44, Seat 4).
6. `sim::buildRoomIR(Kind::Binaural)` returns the 2×2 BRIR matrix: emitter L → ear L/R and emitter R →
   ear L/R. The plugin sends `outputMode` through, so `binaural` now uses this path. `stereoSpeakers`
   keeps using omni until Phase 09.
7. `render_cli --mode binaural`, listening-pack entries (including one both-near binaural render:
   listener and an emitter within 0.70 m of surfaces, AX44, Seat 4), goldens for 3 scenes. `render_cli --hrtf <file>`:
   a **validation-only** override that renders through another converted `.bin` (CLI only, never in the
   scene, no host parameter; `hrtfId` stays the schema const; the AX4 `--no-air-absorption` pattern), so
   B9 can render through BRAS's FABIAN HRIRs (CC BY-SA 4.0: validation only, as the BRAS row in
   `docs/THIRD_PARTY.md` states). Every preset validation log (the Phase 12 preset listening checklist
   and its PR listening notes, the Phase 13 final listening pass through all presets, and the B9 (§5)
   protocol logs) records the `hrtfId` and the header's set identity string of the build it was listened
   through; this phase's checklist does the same.
8. **Update-time check (ledger P06F-4):** once the head yaw follows the emitter centroid (AX3), emitter
   moves change the HRTF set; check whether Vorländer Table 15.1's head-rotation row (35 ms; filter
   content 'new HRTF') applies and, if so, whether the AQ4/AX31 isolated-update delay (slot wait +
   rebuild + 2P) meets it; record the result (an AX through /fix-plan if a change is needed).
   Before measuring, state which limit is applied (Table 15.1's 35 ms or the 20 ms printed in Vorländer
   §15 prose) and whether the 30 ms fade counts toward it (ledger P06B-66, phase-06b advocate). Under the
   35 ms limit with the fade not counted, W1 (20.6 ms on the Linux runner) lies in (35 − 2P, 35 − P] =
   (13.7, 24.3] ms at P = 512, where AX31's extra partition decides the row (31.3 vs 41.9 ms); so if the
   row applies, AX31's reversal clause applies (AX31 note, phase-06b D2). Under the 20 ms limit neither
   pickup variant meets it for W1 (20.6 > 20 ms) (ledger P06B-76).
   **Since phase 05b (AX38 (v)):** item 8 measures the delay of one isolated update with the wait at the
   diffuse-solve gate included, and records that the diffuse solve inside every rebuild, not the gate,
   is what breaks Table 15.1's 35 ms head-rotation row. If that row applies, the remedy is a Phase 10 AX
   that updates the specular and directional part without waiting for the diffuse solve, not a change to
   the gate. Seat 1 reads AX3's centroid-following yaw under the source-movement rows, not the
   head-rotation row [Inferred]; item 8 still measures.
9. **Records from phase 05b (AX38):** W1/W2 per output mode with the diffuse share shown separately
   (AX38 4b); the AX38 (iv) multi-instance records repeated in binaural mode, with the gate wait shown
   separately.
10. **Restore gate in the heaviest mode (AX38 4c, AQ10; board answer, decider files 47 §4 (i), 51 §4
    item 5):** from this phase on, the blocking 100 m, 96 kHz restore gate measures the heaviest output
    mode, and W_max stays one constant for all modes. If the heaviest-mode build makes the pinned W_max
    fail the gate, phase-07c is brought forward to land before this phase's goldens are frozen (W_max is
    then re-derived once, under phase-07c, with one golden round); W_max is never cut to pass. Goldens in
    capped rooms carry a tolerance derived from the achieved SE, unless phase-07c has landed before they
    are frozen.

## Out of scope

Personalized HRTF / SOFA import (B4), head tracking and head orientation control (PRD out of scope),
near-field HRTF correction (sources < 1 m; note it as a follow-up).

## Acceptance criteria — automated

- [ ] Licence file present and `docs/THIRD_PARTY.md` updated (a CI script fails if `resources/hrtf/*.bin`
      exists without the `LICENSE-<id>.txt` matching the **header's** set id).
- [ ] **Converter round-trip (storage and decoding):** at every stored direction, each ear and each
      of the four rates, the HRIR decoded from `generic-v1.bin` is within −60 dB (`residualDb`) of
      the reference built in the test from the pinned SOFA source by the converter's pinned steps
      with the header's parameters (pinned resampler, stored DF-EQ curve, stored onsets,
      minimum-phase step if recorded) — **both** against that reference trimmed and faded
      identically (storage term) **and** against it untrimmed and unfaded (total term; truncation
      loss counts). The test prints both terms' worst values per rate. The source is fetched by
      checksum (scope 1); the test skips with a marker when it is absent unless
      `SPATIAL_REQUIRE_HRTF_SOURCE=1` (CI). The DF-EQ curve's correctness is tested by the DF-EQ
      identity AC, the onset estimator by AC 3, the interpolation by AC 4; AC 2 tests none of them.
- [ ] **ITD/ILD sanity** (anechoic scene: α = 1 everywhere, direct path only): an emitter at +90°
      azimuth (left; define the azimuth sign convention in the code and docs) gives ITD between **0.6 and
      0.75 ms** with the left ear leading, and ILD > 6 dB averaged over 2–8 kHz. The mirror holds at −90°.
      An emitter straight ahead gives |ITD| < 20 µs and |ILD| < 1 dB. The window 0.6–0.75 ms
      **presupposes an onset (pulse-arrival) estimator**: it is sized to the onset ITD of brief
      pulses, ≈ 650 µs at 90° (Blauert Ch. 2 §2.2.2, Fig. 2.30), and to the far-source path
      difference divided by the speed of sound, (D/2)(φ + sin φ)/c = 0.225 m / 343 m s⁻¹ = 0.656 ms
      for D = 17.5 cm (Blauert Ch. 2 §2.2.2). The estimator is therefore of the
      onset class — the converter's per-ear onset detection that yields `onset_left`/`onset_right`,
      run on the resampled HRIRs before EQ and onset removal, and the same criterion applied by the
      test to the rendered anechoic output — and its exact criterion (threshold relative to the
      ear's peak) and the sign convention are named in this AC by the decision loop **before the
      first measurement**. A low-frequency ITD (≈ 750 µs for an average human head) exceeds the
      broadband onset ITD (≈ 650 µs); the value depends on stimulus and measurement technique
      (Roginska & Geluso Ch. 1; Blauert Ch. 2 §2.2.2: the sphere model's interaural phase and group
      delay reach about 0.6–0.8 ms), so an estimator of another class would need its own window
      derived from the corpus before measuring — never this one widened. If the pinned file measures
      outside 0.6–0.75 ms with the named onset criterion, the window is challenged on that evidence
      through the interrogator, never widened to pass (decider challenge C-1: York's own ITD plots
      read ≈ 0.85 ms for D1 by an unstated method, dossier F21). Not a head reversal.
- [ ] **Interpolation continuity:** sweeping azimuth in 1° steps never changes broadband level by more than
      1 dB or ITD by more than 30 µs per step.
- [ ] **Tail coherence:** measured interaural coherence of the late tail per band is within ±0.1 of the
      target curve (125 Hz–4 kHz); the target is the solid-angle-weighted one (scope 3).
- [ ] **Energy:** binaural vs omni per-band energy within ±1 dB for all valid fixtures.
- [ ] **Orientation (AX3):** a unit test with emitters ahead, behind and on top of the listener gives
      the documented yaw, and the hold rule triggers at < 0.1 m.
- [ ] T30 of each ear's BRIR within ±5% of the omni IR's T30 (250 Hz–4 kHz).
- [ ] **DF-EQ identity:** the solid-angle-weighted one-third-octave **power** average of the
      converted set, L_b = 10·log10(Σ_i w_i P_{i,b}) per ear (scope 3), is 0 dB within 0.1 dB in
      every band of the converter's curve. The committed `.bin` is within the scope 2 embed bound
      with this, AC 2 and AC 4 green on the real file; its size is recorded in the PR.
- [ ] **Validation-only override:** `render_cli --hrtf <file>` renders through the given converted set;
      the option exists only in the CLI (no scene field, no host parameter; `hrtfId` stays the schema
      const), and the scene validator still rejects any other `hrtfId`.
- [ ] **E_b parity (AX44):** E_b is bit-identical between omni and binaural and between the ears.
- [ ] All earlier tests still pass. pluginval passes. Plugin CPU benchmark is recorded; W1/W2 per output
      mode with the diffuse share and the binaural AX38 (iv) records are recorded (scope 9).
- [ ] **Restore gate, heaviest mode (scope 10):** 14 × t_restore ≤ 30 s at the AX38 4c scenes in the
      heaviest output mode, with the one W_max constant; capped-room goldens with the SE-derived
      tolerance unless phase-07c has landed.

## Listening / manual checklist (Maisara, headphones)

Listening pack (`binaural/`) and the plugin in a DAW with `output_mode = binaural`. The pack never names
the head (the dataset is named only in the licence file, `docs/THIRD_PARTY.md` and the public testing
record). Fixed acceptance set, rendered for every item: an **a cappella voice, pink-noise pulses and
speech**. Every room render comes with an **anechoic direct-only render** (α = 1, direct path only) of the
same emitter and listener positions beside it, and with the omni preview. Answer in the **forced-choice
form**: location **front / back / above / inside / outside**; colour against the omni preview **none /
boxy / thin / harsh**. Record the `hrtfId` and the header's set identity string of the build you listened
through (scope 7).
- [ ] Default scene with emitters at about ±30° ahead: where is the image (front / back / above / inside /
      outside)? Expected: in front and outside your head. (Generic HRTFs are heard inside the head,
      or reversed front/back, by some people, and height on the median plane is uncertain
      (Begault Ch. 3; Vorländer §6.3.2). Note what you hear; that's what B4 is for.)
- [ ] `anechoic_azimuth_sweep.wav`: a sound circling the head. It should be clearly left, right and
      front. Front/back confusion is common with generic HRTFs, so note it.
- [ ] Move the listener close to the L emitter: the image pulls left and the room recedes.
- [ ] Large hall: the reverb surrounds you rather than sitting between the ears like a normal stereo reverb.
- [ ] Colour against the omni preview, for the room render and for its anechoic render: none / boxy / thin /
      harsh.
- [ ] **Complaint protocol (Seat 9):** a colour complaint on a preset is checked against the anechoic
      render and the omni preview beside the preset before it is assigned to room, head or headphones.
      Head shadow is not a low-frequency effect (Rumsey §2.1.2: the head is an appreciable barrier at HF,
      not at LF), so a weak 125–250 Hz is not head shadow. A low-frequency loss can still come from the
      HRIR window (Begault Ch. 4 "Methods for Data Reduction": rectangular windowing may lose
      low-frequency information) or from the set's LF extension (SADIE II: below ~200 Hz modelled).
      "Thin" that persists in the anechoic render is therefore checked against the converter's LF
      response (the `--diagnostics` curve below 400 Hz) before it is assigned to room or headphones.
- [ ] **Hand-off to Phase 11 (Seat 6):** one line in the PR for the output-mode tooltip or manual, a
      default-experience note (what a listener may hear through the generic head: inside or behind for
      some), with no head name.

## Contractor review focus

Licence review (licence re-read on the record at pin time; head named nowhere in UI), HRIR interpolation
(triangulation, ITD handling, the named onset estimator), coordinate and sign conventions, the
dataset-agnostic header and the Voronoi-weighted DF-EQ / coherence averages with the identity test,
the two-term AC 2 reference (header parameters, untrimmed total term), the image-source grouping
approximation (if the benchmark introduced it), the diffuse-coherence mixing, energy normalization
between modes, and the `--hrtf` override staying out of the scene and the plugin.

## Risks

- Generic HRTFs cause front/back confusion and weak externalization for some listeners. This is an
  expected limitation, recorded as evidence for B4.
- F8: the head always faces the emitters, so sources can't be put behind the listener. Report it if it
  sounds odd in practice.
- BRIR build time with many image sources. Measure it against AQ4's 20 ms cadence (AX33) first; grouping
  (scope 5) is introduced only if the benchmark shows it is needed.
- The four-rate embed may not reach ≤ ~32 MB with AC 2 and AC 4 held (scope 2). Report it; don't loosen a
  gate (decision reversal condition 3: Maisara is told the deadline keeper's cell is back at 2).
- AC 3's ITD window may fail on the SADIE heads (York's plots read ≈ 0.85 ms by an unstated method;
  a low-frequency estimator reads higher than an onset estimator). Not a head reversal: name the
  onset criterion first, then challenge the window through the interrogator on the measurement
  (C-1).
- The pin-time source-state check (scope 3) may exceed ±1 dB in a band: the header records "not
  confirmed", the dossier's F18 is marked contradicted and it is raised before any golden is frozen.
  The converted set's **state** is the same either way — weighted one-third-octave power average
  0 dB in every band, by construction (the DF-EQ identity AC) — but not its **signal**: the
  converter's weighted normalisation replaces, band by band, whatever direction-independent
  equalisation the source carried, so a 'not confirmed' result means the shipped set differs from
  York's published equalisation by the reported curve. That is why it is raised before any golden is
  frozen.
- Headphone compensation has no slot in the plan (§5 B14, open debt): expect colouration notes in the
  checklist that no Phase 08 step addresses.

## Definition of done

All automated criteria green; licence re-read on the official record at pin time and recorded (scope 1);
the head named only in `LICENSE-generic-v1.txt`, `docs/THIRD_PARTY.md` and the public testing record;
status row 08 `done` (or 08b added); checklist in the PR with the `hrtfId` and set identity string.
