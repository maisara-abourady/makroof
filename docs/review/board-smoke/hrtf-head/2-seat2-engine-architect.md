# D1 (dry run) — Seat 2, the scene-to-response architect (2026-11-09)

Method: the registered `seat2-engine-architect` agent, briefed with B2 of `1-decider-convene.md`; no dossier yet (dataset facts `[Hyp]`). Verbatim.

---

SEAT 2 POSITION

**1. Reading.** Which dummy-head set becomes `generic-v1`, judged only on (i) whether it keeps a path to compare binaural renders with measured BRIRs and (ii) whether its direction grid covers the arrival directions the shoebox ISM produces under AX3. Cues: §4 cue 4 (path geometry: source or listener near a wall, floor images), cue 6 (a claim of accuracy needs a measurement behind it). Corpus present (c1b171f). Researcher dossier not yet available: every dataset fact below not in the corpus or a project file is `[Hyp]`.

**2. Ranking.**
1. (d) TH Köln KU100 — *prefer*, conditional: the corpus names its file `HRIR_L2702.sofa`; if "L2702" is a 2702-node Lebedev grid it is full-sphere to the poles `[Hyp]`, so no extrapolation anywhere. Licence and grid are R1/R3 facts.
2. (a) SADIE II KU100 — *can live with* (grid, lowest elevation unknown `[Hyp]`).
3. (b) SADIE II KEMAR — *can live with*, same grounds as (a); head-vs-torso is Seat 1/4's ground, not mine.
4. (c) MIT KEMAR — *can live with only under the conditions in §6*: its grid stops at −40° (corpus), and the ISM puts the strongest early reflection below that in ordinary producer scenes.
Condition "converter and `.bin` header dataset-agnostic" — *prefer*, and for my seat it is the load-bearing item (see later debt).

**3. Tension now.**
- (a), (b): `1`. Grid unknown; if the lowest elevation is above about −83°, part of the early field is extrapolated (see arithmetic).
- (c): `2`. From the code, `computeImageSources` enumerates every lattice image and hands over `arrivalDirection` as a unit vector; AX3 keeps the head upright, so world elevation is head elevation. First-order floor image of an emitter at ear height (z_l = z_s = 1.2 m): elevation = −atan(2.4 / d_h): d_h = 3 m → −38.7°, 2 m → −50.2°, 1 m → −67.4°, 0.3 m (AX6 minimum) → −82.9°. A direct path to an emitter 0.1 m above the floor (AX6) 0.3 m away is at −74.7°. So in any scene with an emitter within ≈ 3 m horizontally the strongest reflection, and sometimes the direct sound, lies in a cap the set never measured: (1 − sin 50°)/2 = 11.7 % of the sphere. Criterion 3 (early reflections right) and criterion 5 (no false precision) both pay. Measurement distance 1.4 m (corpus) is fine for the plane-wave assumption (Vorländer §9.5: > 1 m).
- (d): `1`. Full-sphere coverage is my inference, not a read fact.
- Condition: `1` (header fields: set id, rate, grid, lowest elevation, EQ state; the triangulation must not assume a particular grid).

**4. Tension later (the debt).**
- All options, comparison path: `2` without the condition, `1` with it. BRAS contains measured binaural IRs (phase-05 Data, researcher facts, outside corpus). Which head measured them is R10; my recollection is the FABIAN head-and-torso `[Hyp]`. If so, none of (a)–(d) gives a head-matched comparison: a 2019-style plausibility test (my §0 base rates, d′ 0.07–0.3) renders the simulation through the same head as the measurement, and with a mismatched head the listener hears head plus room confounded. What survives any head: per-ear T30/EDT per band (a stationary filter does not change a decay slope); C80/D50 and IACC survive only approximately (direction-weighted by the head's own filter; size of the bias `[Hyp]`, for the researcher or Phase 05e-style measurement). Undoing: with a dataset-agnostic converter, running a validation-only FABIAN set is a CLI change; without it, a phase of rework in `src/sim/hrtf`.
- (c): `2`. Any statement about early-reflection accuracy carries an "unmeasured below −40°" clause for life; the DF-EQ and the tail-coherence target (phase-08 scope 3/5: diffuse-field averages over the set) are biased unless solid-angle-weighted and the missing cap declared. Evidence arrives in the phase-08 listening check "move the listener close to the L emitter" and in B9. Swap cost: a parameter change if the condition holds, otherwise rework.
- (a), (b), (d): `1`. Evidence arrives at R3 (lowest elevation) and R10.

**5. Evidence.** ISM lattice, every image visible, `arrivalDirection` handed to Phases 08/09: from the code (`src/sim/ism/ImageSources.h`). AX3 upright yaw-only, AX6 ≥ 0.3 m listener / ≥ 0.1 m surfaces: BUILD_PLAN §2. MIT KEMAR −40° to +90°, 1.4 m, 44.1 kHz, 710 positions: corpus, Begault Ch. 4 (signed-elevations row and the MIT description). Plane-wave HRTF valid > 1 m: corpus, Vorländer §9.5. Up vs down spectra differ (notches ≈ 5.8 / 8.8 kHz at −36°): corpus, Begault Fig. 2.15, so mirroring the upper hemisphere is wrong, not an approximation. BRAS has binaural IRs: `docs/phases/phase-05.md` Data (external). BRAS head = FABIAN: `[Hyp]`, R10. TH Köln L2702 = full-sphere Lebedev: `[Hyp]`, R3 (corpus names the file only). Plausibility base rates: my register §0 (Brinkmann et al. 2019, [Observed]). Researcher to verify: R3 (lowest elevation, grid type for all sets), R10 (BRAS/Arni/dEchorate head), and whether a FABIAN HRTF set exists under a licence that permits validation-only use (never shipped).

**6. Conditions of acceptance.**
- (c) now 2 → 1, later 2 → 1: the renderer treats elevation < −40° as a declared unmeasured zone: nearest-elevation clamp of the magnitude HRIR, ITD interpolated or from the head model, never mirrored, never silently triangulated across the cap; `--diagnostics` reports per emitter the share of early energy rendered from the zone; the DF-EQ and coherence averages are solid-angle (Voronoi) weighted with the cap reported in the header.
- All options later 2 → 1: adopt the dataset-agnostic condition, and give `render_cli` a validation-only HRTF override (the AX4 `--no-air-absorption` pattern: CLI only, never in the scene, `hrtfId` stays the schema const) so B9 can render through the reference dataset's head once R10 names it.

**7. Hand-offs.** Audibility of elevation error below −40° and of head-vs-torso → Seat 1. Clamp/interpolation continuity, 44.1 → 48 kHz resampling of (c), 256-tap truncation → Seat 3. Licence → Seat 4, Seat 7, a human. Allocation-free lookup, binary size → Seat 5. BRAS head and grid facts → researcher.

**8. Premortem.** If (c) ships without a declared unmeasured zone, the floor reflection of a close emitter is rendered with a −40° pinna spectrum at −70°; Maisara hears it as colouration when moving the listener toward an emitter and blames the room, and B9 can then never separate head from room.
