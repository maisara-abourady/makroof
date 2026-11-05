# Phase 05d — Second measured dataset (Arni, dEchorate)

Size: **M** · Depends on: 05 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ1, AQ8, AQ9, AX4, AX11, AX17) and §3 (F2), `docs/phases/phase-05.md` (Data, scope 2–4, scope 6 "Paired comparisons"), PRD NFR-1, NFR-8, FR-3D-3, Q9

Created by decider report 15 (`docs/review/phase-04-consult/15-decider-second-dataset.md`), accepted by
Maisara with its Challenge 1, 2026-11-05. Run after 05 and before 05b, but 05b does **not** depend on
this phase: if 05d is blocked on data access, 05b proceeds. Phase 13 depends on 05d being `done` or
`blocked (reason)`. The name 05c stays reserved for Phase 05's zero-rooms branch. All dataset facts
below come from researcher reports 13 and 14 (external, cited there by DOI; outside the corpus), "read
on record pages".

**Settled before the session.** The choices formerly marked *(open)* (D1–D7) were settled by decider
report 16 (`docs/review/phase-04-consult/18-decider-05d-choices.md`), accepted by Maisara with both of
its challenges, 2026-11-05, and are written below in its wording. The session does not change them.
One item is still marked *(open)* (scope 5, mean |d̄|); it needs a decision through /fix-plan before
this phase is executed, and the session does not choose it.

## Goal

Add a second measured source beside BRAS (BUILD_PLAN §3 F2), with the same comparison chain as
Phase 05 and nothing hand-tuned. Neither set has measured α for all surfaces, so every absolute
comparison is **evidence, not validation**. The only claim stronger than evidence is the
**input-matched distribution test**, stated as: "method evidence with the input bias cancelled to
first order; not an NFR-1 validation". No method change.

## Assumptions in force

- **AQ1**: v1 is a shoebox with 6 faces, per-band α and broadband s, no objects. dEchorate is an exact
  cuboid whose faces switch as whole faces; Arni's variable panels are wall- and ceiling-mounted and
  map to per-face α through Phase 05's absorption-area rule.
- **AQ8**: omni emitters only. Arni: the omni LS01 campaign only. dEchorate: **only the sources
  documented as omnidirectional**.
- **AQ9** thresholds and conditions as in Phase 05 (500 Hz, 1 kHz, 2 kHz; T30/EDT ±10 %, C80 ±2 dB),
  reported per configuration and per room, by α set; all evidence.
- **AX4**: the validation-only atmosphere override. Arni: documented, 19–20 °C, RH 28–50 % (researcher
  report 14 V4, external, DOI 10.1121/10.0013575). **Arni atmosphere rule** (D5, decider report 16,
  accepted by Maisara, 2026-11-05): If the record gives temperature and RH per IR or per combination,
  render each scene at its own logged values. Otherwise render at the campaign mid-range, 19.8 °C and
  39 % RH (midpoints of 19.3–20.3 °C and 28.5–50 %, researcher report 14 V4), and print per band Phase 05's
  Eyring humidity bound between the two ends (19.3 °C/28.5 % and 20.3 °C/50 %). Where that bound on d̄
  exceeds 1/3 jnd, d̄ is labelled "atmosphere-limited". It is a systematic term, not reduced by K.
  dEchorate: 24 °C, 80 % RH (researcher report 13 D3, external, DOI 10.1186/s13636-021-00229-0);
  dEchorate stays at these values.
- **AX11** convention for the statistics (SE ≤ threshold/3).
- **AX17**: one broadband s per face. **NFR-8**: no per-scene factors; a room that fails is reported.

## Data

- **Arni** (Aalto variable-acoustics room): Zenodo 10.5281/zenodo.6985104, the omni LS01 campaign
  with the per-IR `combinations_setup.csv`. This is the primary second source. Rectangular,
  8.9 × 6.3 × 3.6 m, nominal V = 201.9 m³ (researcher report 14 V5, external, DOI 10.1121/10.0013575);
  55 panels of 0.6 × 0.4 × 2.4 m, 8 on each of three walls, 11 on the fourth, 20 on the ceiling
  (researcher report 13 D1, external, DOI 10.5281/zenodo.6985104). The CSV maps each combination to the
  0/1 state of all 55 panels, and the IR file names carry the combination and mic index; positions
  exist only as drawings (`Arni_layout.jpg`, `Arni_panels_numbers.pdf`, JASA Fig. 3); 50.9 GB; K = 5312
  in the paper against 5 342 on the record, unexplained (researcher report 14 V6, C5, external, DOI
  10.5281/zenodo.6985104). Panel α come from one unretrievable "exploratory" DELTA report; walls and
  floor use textbook α; no scattering data (researcher report 14 V1–V3, external, DOI
  10.1121/10.0013575).
- **dEchorate**: Zenodo 10.5281/zenodo.6576203 v2.0. Cuboid 6 × 6 × 2.4 m (86.4 m³), double-sided
  panels on all 6 faces (reflective or absorbing), floor always carpet, 11 configurations; no α;
  measured RT 500 Hz–4 kHz; IRs unreliable below about 300 Hz because of loudspeaker roll-off; 24 °C,
  80 % RH, c = 346.98 m/s; positions refined against echo times (0.4 cm); gaps between panels noted
  (researcher report 13 D3, external, DOI 10.1186/s13636-021-00229-0).
- **Reserves:** Motus (revisited with B2/B8, objects) and May et al. are reserves; SRIRACHA is a lead
  pending its licence. Everything else in reports 13 and 14 is out (decider report 15, SD-1).
- Write `tools/validation/fetch_arni.py` and `fetch_dechorate.py` with SHA-256 manifests
  (`tools/validation/arni_manifest.json`, `dechorate_manifest.json`) cross-checked against Zenodo's
  md5, caching under `~/.cache/makroof/<set>`. Partial download if the archive layout allows it; the
  layout is checked first and recorded in the mapping file. Confirm the licence on the live record and
  store it in the manifest. **Never commit the data** (CLAUDE.md rule). The `docs/THIRD_PARTY.md` rows
  exist; complete their pins.
- **Mapping files** `docs/validation/arni_mapping.md` and `docs/validation/dechorate_mapping.md`.
  Before any sim–meas number is computed, they commit:
  - the **α source rule**: Arni panel α from the paper's table, other surfaces as documented; dEchorate
    α from a published table chosen by a rule committed here. **dEchorate α rule** (D4, decider report
    16, accepted by Maisara, 2026-11-05), applied by the 05d session and written in
    `dechorate_mapping.md` before results; the interrogator checks the chosen rows against
    `docs/corpus/` (CLAUDE.md): For each material named in the dEchorate documentation (Formica 20 mm,
    perforated panels with rock or glass wool, carpet), take the Vorländer Annex random-incidence α row
    that matches by, in order: material family; construction (porous backing or cavity, mounting);
    nearest thickness. If rows tie, use their per-band mean. Record the row(s) and the reason. The Arni
    α rule stays as written.
  - **Shared gap rule for both sets** (D4, decider report 16, accepted by Maisara, 2026-11-05): bands
    below the lowest tabulated band take that band's value and are flagged. The Annex starts at 125 Hz;
    Arni's table starts at 250 Hz (researcher report 14 V1). These bands are method-validity evidence
    (Arni) or not evaluable (dEchorate), so AQ9 is unaffected.
  - the **scattering input** for both sets, which document none; Phase 05 does not allow running without
    scattering. **Scattering (both sets)** (D4, decider report 16, accepted by Maisara, 2026-11-05),
    committed before results:
    1. Per surface, read the structural depth h and length a from the documented geometry (Arni panel
       drawing; dEchorate panel layout, gaps included).
    2. At each band where a/λ < 0.125, set s = 0.05. Vorländer Annex: below 0.125, s is "generally
       smaller than 0.05".
    3. Otherwise, take the Annex scattering row of the same class (1-D or 2-D, Fig. A.1) with the
       nearest h/a, then the closest shape description. If rows tie, use their mean. Interpolate
       linearly in log₂(a/λ) between columns, and hold the end column beyond the table.
    4. Map to faces by Phase 05's reflected-energy weighting, then reduce to broadband by AX17.

    **Sensitivity run:** every face at s/2 (a chosen step, outside the corpus), same scenes, same pairs
    and K. The report prints the change in the AQ9 metrics and in d̄. Any room, configuration or d
    conclusion that differs between the two runs is labelled "s-limited".
  - the **configuration subset** and the **matched-pair list**, derived from the CSV and the panel
    drawing (below). **Configuration subset (Arni)** (D1, decider report 16, accepted by Maisara,
    2026-11-05):
    - **AQ9 sample:** for every n = 0…55 present in `combinations_setup.csv`, one configuration is drawn
      uniformly by a fixed integer seed. The seed is written in `arni_mapping.md` before the draw. All
      5 receivers are used.
    - **Pair list:** take all matched candidates (same n, equal open–open shared-edge length). Draw an
      ordered list of configuration-disjoint pairs: cycle through the n values in increasing order and,
      at each n that still has candidates, draw one unused pair per cycle with the same seed, until no
      candidates remain. No configuration appears in two pairs. Each pair gets one receiver, assigned
      cyclically 1–5 in list order. The ordered list is committed.
    - **Pilot and K:** the pilot is the first 51 pairs. The reported set is the first
      K′ = max(51, ⌈9·σ_d²⌉) pairs, with σ_d in jnd taken as the largest over T30, EDT and C80. Pilot
      pairs count towards K′. If after the run σ_d/√K′ > 1/3 jnd for any metric, the set is extended in
      list order.
    - **dEchorate:** all 11 configurations, all IRs of the omni source positions, no sampling. A pair's
      unit d is the mean over all its omni-source/receiver combinations.
  No configuration or pair is dropped after results are seen. Phase 05's generic reduction rules
  (dimensions, absorption, scattering), position rule (scope 2) and metric conditions (scope 3) apply
  unchanged.

## What each dataset can and cannot validate

Use these labels verbatim in the report and the beta decision (decider report 15, SD-2):

| Question | Arni | dEchorate |
|---|---|---|
| Absolute T30/EDT/C80 vs AQ9 | **Evidence, not validation.** Panel α come from one unretrievable "exploratory" report; walls and floor use textbook α (V1–V3). Vorländer §11.5: the operator's absorption choice has "crucial influence". | **Evidence, not validation.** No α at all, so α come from a published table chosen by a rule committed before results. |
| Effect of absorption distribution with the input bias held fixed (T30, EDT, C80) | **Yes**, on matched pairs: same receiver, same number of open panels, equal open–open shared-edge length. Position effects cancel too (EDT "varies considerably within a hall", Kuttruff §8). | **Yes, if** two configurations have equal absorbing area on different faces (e.g. two 6 × 2.4 m walls). The 05d session checks this. |
| Early reflection **timing** per wall | Not useful (protruding panels). | Sanity check only. The authors refined positions against echo times (0.4 cm), so agreement is nearly circular, and Phase 03 already gates timing analytically. Compare arrival times scaled by c_meas/c_sim = 346.98/343 (1.16 %, ≈ 16 samples at 48 kHz over 10 m), analysis-side, no code change. |
| Early reflection **level** per wall (reflective vs absorbing state) | No. | Reported. It depends on the table α, and random-incidence α can misstate a specific-angle reflection by up to 2 dB (Vorländer §11.1.2). |
| Small room under 100 m³ | No (201.9 m³, V5). | Yes, at 500 Hz–4 kHz only. |
| Below about 250 Hz | Transition zone, evidence on method validity only. | Not evaluable. |
| B12 (decay predictor) | The matched-pair spread directly measures what Eyring cannot see; it is shown by the mean \|d̄\| and SD(Δln T30_meas) (scope 5). Reported as "input-matched", not counted in B12 rule (iv). | Same. |
| Atmosphere | Documented, 19–20 °C, RH 28–50 % (V4). Use the AX4 override. | 24 °C, 80 % RH. Use the AX4 override. |

## Scope

1. Fetch scripts, manifests and mapping files (Data).
2. `tests/scenes/validation/arni_<config>_<rcv>.json` and `dechorate_<config>_<src>_<rcv>.json`:
   contract scenes for the selected configurations, mapped with Phase 05's rules.
3. Extend `tools/validation/run_validation.py` to the 05d scenes and write
   `docs/validation/report-phase05d.md` with Phase 05's report generator, unchanged except for the
   hybrid-IR d below (tools only, no simulator change). Reported, not gated:
   - AQ9 per configuration and per room, by α set.
   - The matched-pair differential d: mean, SE and K. **Unit** (D2, decider report 16, accepted by
     Maisara, 2026-11-05): d_X = [ln(X_a/X_b)]_sim − [ln(X_a/X_b)]_meas, divided by 0.05, for X = T30
     and EDT (T at the working 5 %, AQ9; EDT 5 %, Vorländer Table 6.1). For C80,
     d = [(C80_a − C80_b)_sim − (C80_a − C80_b)_meas]/1 dB. The orientation of a and b is fixed in
     scope 4.
     **Bands** (D3, decider report 16, accepted by Maisara, 2026-11-05): Per pair, d̄ = mean of the
     signed per-band d over the evaluable bands among 500 Hz, 1 kHz and 2 kHz (Phase 05 evaluability
     rules; a pair with no evaluable band is "not evaluable"). σ_d, K and the 1-jnd check use d̄. The
     report also prints the 500–1000 Hz mean as the in-range figure (Table 6.1 jnds are stated for
     500–1000 Hz; 2 kHz by extension, AQ9), and the per-band means with SE, descriptive only.
   - **Hybrid-IR d** (decider report 16, Challenge 2, accepted by Maisara, 2026-11-05): the EDT and C80
     d are also printed on Phase 05's reference-hybrid IR (tools only, no simulator change), next to the
     Phase 04 IR, as phase-05 scope 6 does for BRAS.
   - Per-face reflection level changes (dEchorate, reflective vs absorbing state), and the arrival-time
     sanity check scaled by c_meas/c_sim = 346.98/343, analysis-side, no code change. **Isolation,
     timing and level** (D6, decider report 16, accepted by Maisara, 2026-11-05):
     - A reflection is evaluated only if, by the simulated image list, no other arrival within ±2.5 ms
       of it has predicted broadband energy within 10 dB of its own.
     - **Timing:** the largest broadband |h| within ±2.5 ms of the predicted arrival. Delays are taken
       relative to each IR's t₀ (Phase 05 rule), and the simulated delay is scaled by
       c_sim/c_meas = 343/346.98 before comparison.
     - **Level:** band energy in a ±2.5 ms window centred on each IR's own detected peak, with bands
       reported per AX13 (≥ 99 % rule: 1 kHz and up). Reported per face as
       ΔL = L_absorbing − L_reflective, simulated against measured, in dB.
   - Coverage by FR-3D-3 category (clubs & warehouses; halls, chapels & churches; outdoor; domestic).
   - Low frequencies: the Schroeder frequency under both constants per room, as in Phase 05 (Kuttruff
     Eq. 3.44, Vorländer Eq. 4.13). Arni bands at 63–250 Hz fall under Phase 05's Schroeder rule
     (method-validity evidence). dEchorate bands below about 300 Hz are **"not evaluable"**, never a pass.
   - Each committed report carries the attribution of `docs/THIRD_PARTY.md`.
4. **Matched pairs (input-matched distribution test).** Eyring depends on α only through ᾱ
   (Vorländer Eq. 4.30, 4.32), so a common error in a material's α cancels exactly from the Eyring ΔT
   of two configurations with the same area of each material, and to first order for models that
   respond to where the absorption sits. Placement alone changes the effective α at free edges
   (Kuttruff §8.7 Eq. 8.56, α_eff = βL′ + α_∞), so an Arni pair must have:
   - the same receiver;
   - the same number of open panels;
   - equal open–open shared-edge length, computed from the panel drawing.
   For dEchorate (whole-face switching) the edge problem does not arise (Kuttruff §8.7); a pair needs
   equal absorbing area on different faces, which the session checks. The slope across different
   numbers of open panels (dT/dn) is **not** input-independent and is not used for this test.
   **Orientation** (D2, decider report 16, accepted by Maisara, 2026-11-05): a is the configuration with
   the longer a* T at 1 kHz (phase-05 solver, same committed α and s, converged < 0.4 %). Where |ΔT_a*|
   is below 0.4 %, a is the lower CSV combination number. The orientation is committed with the pair
   list.
5. **Statistics** (AX11 convention): the simulated side is seed-paired, as in phase-05 "Paired
   comparisons". On the measured side, take a pilot of **≥ 51 disjoint pairs**, measure σ_d, then use
   **K ≥ 9·(σ_d/1 jnd)²** disjoint pairs, so that SE ≤ 1/3 jnd. The two-sided "moves by more than 1 jnd"
   check then gives a false-positive rate of 0.27 % at a true d = 0. Example: with σ_d ≈ 1 jnd (two
   single-position T30s at ≈ 2–3.5 % each, phase-05 figure, outside the corpus), K ≥ 9. The pilot, K′
   and the pair order follow the configuration subset rule (Data, D1).
   **Too few pairs** (D7, decider report 16, accepted by Maisara, 2026-11-05): If a set has fewer than
   51 configuration-disjoint pairs, or its committed list ends before K′ is reached, the report prints
   mean d̄, SE, the number of pairs and per-band values, labelled "descriptive: too few pairs for the
   1-jnd test". No 1-jnd conclusion is drawn, and for the F2 commissioning reading the set counts as "no
   evaluable pair". Sets are never pooled.
   **Mean |d̄|** (decider report 16, Challenge 1, accepted by Maisara, 2026-11-05): the report also
   prints the mean |d̄| per metric and set, descriptive only, next to its expected value at d = 0.
   SD-2's "spread" (B12 row of the table above) is shown by that figure and by SD(Δln T30_meas). How
   that expected value at d = 0 is computed, and the bands SD(Δln T30_meas) is taken over, are
   *(open)*.
6. CI: the nightly workflow of Phase 05 includes the 05d scenes, with the same change limits
   (±2 % T30/EDT, ±0.2 dB C80) against the baseline simulation; sim–meas errors are recorded and
   reported, never gating. If the projected nightly runtime is too long, the run moves outside CI under
   phase-05's 24 h rule, with K unchanged.

## Out of scope

Any change to `src/sim` or the contract. B11 (B) stays on BRAS as decided; 05b only prints the 05d
numbers as context. The dT/dn slope as an input-independent test. Motus, May et al. and SRIRACHA
(reserves and lead; see Risks).

## Acceptance criteria — automated

- [ ] `fetch_arni.py` and `fetch_dechorate.py` verify checksums. A corrupted file is detected (unit test
      with a tampered cached file).
- [ ] The report reproduces exactly (two runs give identical numbers).
- [ ] The nightly baseline includes the 05d scenes (the same ±2 % T30/EDT and ±0.2 dB C80 change
      limits) and runs green on it.
- [ ] Matched-pair selector unit test: every selected pair gives an Eyring ΔT of exactly 0 and equal
      shared-edge length, and a deliberately unmatched pair is rejected. This is the negative control,
      so the test is not vacuous.
- [ ] The mapping files are committed before any sim–meas number (git history shows it).
- [ ] AQ9 pass/fail is printed per configuration and per room, by α set, with the labels of the table
      above.

Failing AQ9 thresholds or a matched-pair differential above 1 jnd does **not** fail CI. They go to the
status notes and to Maisara's commissioning decision (BUILD_PLAN §3 F2).

## Listening / manual checklist (Maisara)

- [ ] Read the report summary: every absolute comparison is labelled "evidence, not validation", and
      the input-matched test carries its stated label.
- [ ] Note the matched-pair result for the commissioning decision after 05/05d (BUILD_PLAN §3 F2): a
      differential within 1 jnd with large absolute AQ9 errors means the input data dominate (Vorländer
      §11.5); a differential above 1 jnd means the method comes first (B12/B2).

## Contractor review focus

The mapping files (generic Phase 05 rules, α source rule committed before results, no per-room
tweaks), the matched-pair selector and its shared-edge computation from the panel drawing, the
c_meas/c_sim scaling (analysis-side only), the pilot and K computation, and whether the report's labels
follow the table above.

## Risks

- **Reversal:** the session finds that Arni's file layout makes even a subset impractical, or that
  dEchorate's 11 configurations contain no omni source. Then Motus moves up as the under-100 m³ source,
  labelled "reduction-limited", through /fix-plan. Motus and May et al. are reserves; SRIRACHA is a lead
  pending its licence.
- Arni dimensions conflict (8.9 × 6.3 × 3.6 m against an unexplained 5.75 × 7.87 × 2.91 m drawing;
  researcher reports 13 C1 and 14 V5, external); record the choice in `arni_mapping.md`. Positions are
  read off a drawing (about ±cm).
- Geometrical acoustics is limited to large rooms (Vorländer §11.5), so dEchorate small-room misses are
  expected; they are the evidence that was missing (FR-3D-3 domestic).
- Data access: if a set cannot be fetched, the phase is `blocked (reason)`; 05b proceeds and Phase 13
  may start.

## Definition of done

Automated criteria green; mapping files and report committed; `docs/THIRD_PARTY.md` pins and confirmed
licences filled in; status row 05d `done` with an "AQ9 met in x/y" note per room and per configuration,
by α set (evidence, not validation), and the input-matched result; or `blocked (reason)`.
