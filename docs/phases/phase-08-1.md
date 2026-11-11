# Phase 08-1 — HRTF data, converter and lookup

Size: **M** (remainder, if needed: `08-1b`) · Depends on: 04, 05b, 05h, 07 (05b `done` in either outcome; with "not promoted", this phase builds on the specular-only early part, AX21). It depends on 05h, except that it may precede 05h on Seat 4's conditions per AX37 (5.3) (D-T5.3): (i) E_b and t_mix,e are read only via `TailMatch`; (ii) parity is checked within the same build; (iii) 05h re-renders the binaural goldens, re-measures binaural W1/W2 and re-runs item 8; (iv) this phase's listening items on concentrated absorption are marked provisional · Part of: [phase-08](phase-08.md) · Lead subject matter: Seat 4 (Chain keeper), "HRTF dataset choice and licence; binaural architecture" · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ6, AX3, AX5, AX35) and §3 (F7, F8), PRD FR-SIM-3, FR-SIM-4, FR-3D-9, A1; the D1 decision (`docs/review/board-smoke/hrtf-head/`, accepted by Maisara 2026-11-09) behind scope 1–3; the umbrella [phase-08](phase-08.md) (shared items)

## Goal

This sub-phase's share of the [phase-08](phase-08.md) goal: the measured **generic HRTF** through which
every early reflection will reach the listener's ears — licensed, converted to
`resources/hrtf/generic-v1.bin`, embedded in `sim` and looked up through `HrtfSet` (phase-08 scope 1–3).

## Assumptions in force

- **AQ6**: one generic HRTF, with the contract `hrtfId = "generic-v1"`. No personalization (deferred, B4).
- **AX35**: the data behind a released `hrtfId` is never replaced; a different head, campaign or re-converted
  set is `generic-v2` with the old data retained. Before this phase's goldens are frozen a converter re-run
  is a parameter change.
- And all of the umbrella's ([phase-08](phase-08.md), "Assumptions in force").

## Scope

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
   escalate. Don't ship data under an unclear licence. (phase-08 scope 1)
2. `tools/hrtf/convert_sofa.py` (uses `sofar` or `netCDF4`/`h5py`, pinned; dataset-agnostic: it converts
   any SOFA set, the header below records which) — reads the SOFA file, resamples to 44.1/48/88.2/96 kHz
   (high-quality polyphase), trims to a common length (e.g. 256 taps at 48 kHz, scaled for other rates)
   with a **fade-out window at the trim, not a hard cut**, removes the common onset delay while keeping
   the ITD as a separate per-direction value (`onset_left`, `onset_right` in fractional samples), and
   writes `resources/hrtf/generic-v1.bin` (a simple versioned binary: header, direction grid,
   minimum-phase or raw HRIRs, ITDs). The original SOFA is downloaded by checksum (scope 1), **never
   committed**. (phase-08 scope 2)
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
     and AC 4 held, report it (decision reversal condition 3); don't loosen either gate. (phase-08 scope 2,
     Embed bound)
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
     string; the main window and the mode switch never show a dataset name. (phase-08 scope 2,
     Dataset-agnostic header; its last sentence is shared with the umbrella and binds 08-3's plugin wiring)
3. `src/sim/hrtf/HrtfSet.h/.cpp` — loads the embedded binary (embedded as a build-step object:
   `add_custom_command` → object / `.incbin`-style; no generated C++ byte array; `sim` stays JUCE-free).
   `HrtfSet` is one immutable process-wide object built off the audio thread, with an O(1)
   direction → triangle index; it assumes **no left–right symmetry** (a B4 personal set breaks it; the
   AC 3 mirror check stays a data test); `[alloc]` tests on `query` and on the BRIR build. Lookup:
   (phase-08 scope 3; the "`[alloc]` … on the BRIR build" part is owned by 08-2, shared with 08-3, which
   build the BRIR)
   - `query(azimuth, elevation) → {hrirL, hrirR, itd}` with interpolation: triangulate the measurement
     grid (spherical Delaunay computed offline in the converter and stored), then barycentric
     interpolation of magnitude-aligned (onset-removed) HRIRs; prefer onset-removed/minimum-phase
     interpolation (Begault Ch. 4 "Problems with Interpolation Algorithms"). ITD is interpolated
     separately and re-applied as a fractional delay. (phase-08 scope 3, `query`)
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
     ±1.5–2.5 dB diffuse-minus-free-field figure is not a tolerance. (phase-08 scope 3, Diffuse-field
     equalization)

## Out of scope

The umbrella's out-of-scope list ([phase-08](phase-08.md)) applies. Phase-08 scope 4–10 belongs to 08-2,
08-3 and 08-4.

## Acceptance criteria — automated

- [ ] Licence file present and `docs/THIRD_PARTY.md` updated (a CI script fails if `resources/hrtf/*.bin`
      exists without the `LICENSE-<id>.txt` matching the **header's** set id). (phase-08 AC1)
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
      (phase-08 AC2)
- [ ] **Interpolation continuity:** sweeping azimuth in 1° steps never changes broadband level by more than
      1 dB or ITD by more than 30 µs per step. (phase-08 AC4)
- [ ] **DF-EQ identity:** the solid-angle-weighted one-third-octave **power** average of the
      converted set, L_b = 10·log10(Σ_i w_i P_{i,b}) per ear (scope 3), is 0 dB within 0.1 dB in
      every band of the converter's curve. The committed `.bin` is within the scope 2 embed bound
      with this, AC 2 and AC 4 green on the real file; its size is recorded in the PR. (phase-08 AC9)
- [ ] All earlier tests still pass. (phase-08 AC12, sentence 1; shared, umbrella)

## Listening / manual checklist (Maisara, headphones)

None: this sub-phase renders no audio. The umbrella's checklist preamble (phase-08 L0) applies from 08-2.

## Contractor review focus

- Licence review (licence re-read on the record at pin time; head named nowhere in UI) (phase-08 CF1; "head
  named nowhere in UI" shared, umbrella)
- HRIR interpolation (triangulation, ITD handling, the named onset estimator) (phase-08 CF2)
- the dataset-agnostic header and the Voronoi-weighted DF-EQ / coherence averages with the identity test
  (phase-08 CF4)
- the two-term AC 2 reference (header parameters, untrimmed total term) (phase-08 CF5)

## Risks

- The four-rate embed may not reach ≤ ~32 MB with AC 2 and AC 4 held (scope 2). Report it; don't loosen a
  gate (decision reversal condition 3: Maisara is told the deadline keeper's cell is back at 2). (phase-08 R4)
- The pin-time source-state check (scope 3) may exceed ±1 dB in a band: the header records "not
  confirmed", the dossier's F18 is marked contradicted and it is raised before any golden is frozen.
  The converted set's **state** is the same either way — weighted one-third-octave power average
  0 dB in every band, by construction (the DF-EQ identity AC) — but not its **signal**: the
  converter's weighted normalisation replaces, band by band, whatever direction-independent
  equalisation the source carried, so a 'not confirmed' result means the shipped set differs from
  York's published equalisation by the reported curve. That is why it is raised before any golden is
  frozen. (phase-08 R6)

## Notes from the split

- 08-1 reads no tail data (no room quantity). (D-PS1, `docs/review/phase-split/5-decider-decision-r2.md`,
  instruction 2)
- The decision loop names AC 3's onset criterion and sign convention at the start of 08-1, before the
  converter's first run; AC 3 stays in 08-2 (convening round, 08-c4 (a), `1-decider-convening.md`). AC 3
  says the criterion is "named in this AC by the decision loop **before the first measurement**"; the first
  onset measurement is this sub-phase's converter run.
- The freeze point that scope 1 (TH Köln re-entry), scope 3 and R6 ("before any golden is frozen") and AX35
  refer to is 08-4's golden freeze (convening round, 08-c2 (b)).

## Definition of done

- All automated criteria green (phase-08 DoD1; this sub-phase's own).
- licence re-read on the official record at pin time and recorded (scope 1) (phase-08 DoD2).
- the head named only in `LICENSE-generic-v1.txt`, `docs/THIRD_PARTY.md` and the public testing record
  (phase-08 DoD3; shared, umbrella).
- CLAUDE.md rules apply: one sub-phase per session; if it can't be finished in two sessions, split the
  remainder into `phase-08-1b.md`.
