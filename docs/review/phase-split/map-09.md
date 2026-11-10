# Split map — Phase 09 (Stereo-speaker output mode)

Source: `docs/phases/phase-09.md` (size **S**, depends on 07, 08). Drafted per
`docs/review/phase-split/0-drafting-brief.md`; pure reallocation, nothing changed in substance.

**Outcome: keep Phase 09 whole.** No sub-phase files; `docs/phases/phase-09.md` stays the phase file and
its §0 row stays `09` (not `split (…)`). The CLAUDE.md two-session remainder, if ever needed, keeps the
plain name `phase-09b.md` (no file of that name exists, so nothing collides; G3).

Item labels used below (the phase file does not number its criteria, so they are numbered here in file
order): **S1–S6** scope items 1–6; **A1–A8** automated criteria in order (A1 exact-geometry L−R gate at
5 m, A2 centre emitter, A3 90° ITD, A4 tail coherence, A5 loudness, A6 mono compatibility, A7 mode-switch
clicks, A8 earlier tests and pluginval); **L1–L5** listening items in order; **C1** contractor review
focus (clauses C1a geometry, C1b coherence formula, C1c normalization); **R1** the risk; **D1–D3**
definition of done (criteria green; status row `done`; checklist in the PR); **G** goal; **AS1** AQ7
under "Assumptions in force"; **OS** out of scope. The phase has no "Raise with Maisara" section and no
"settled" / "decisions before implementation" section.

## 1. Sub-phase table

| id | title | lead subject matter | size | depends on | what it ships | automated criteria owned |
|---|---|---|---|---|---|---|
| 09 (whole) | Stereo-speaker output mode | **Seat 4 Chain keeper** — "how the render reaches the listener: … loudspeaker decoding and layouts; … cross-format loudness and timbre parity" | S | 07, 08 (unchanged; see CHOICE 09-c1 for 08 once 08 is split) | `outputMode = stereoSpeakers` through the virtual ORTF pair (AQ7), level-matched to binaural, switchable during playback, `render_cli --mode stereoSpeakers` | A1–A8 (all) |

### Why it stays whole

- **One subject matter already.** Every scope item is delivery to loudspeakers through one virtual mic
  pair (Seat 4's row: loudspeaker decoding, cross-format loudness parity): the pair's gains and delays
  (S1), applied to the early part (S2) and the tail (S3), level-matched to the other format (S4). The
  mode switch (S5) touches Seat 3's row ("crossfades, … clicks") and Seat 5's ("host conformance …
  automation"), but only as plumbing: the equal-power crossfade law (AX18) and the swap API supporting it
  already exist (Phase 06 scope, used by Phase 07's state restore), so S5 is a parameter that selects
  `Kind` and reuses them.
- **The only candidate cut is too small to deserve a session.** The one seam is DSP (S1–S4, S6; A1–A6)
  vs. the plugin mode switch (S5; A7). A "09-2 mode switch" sub-phase would be a few lines of wiring
  owning one criterion (A7); the brief's rule ("don't create S sub-phases that are a few lines of work
  unless the subject is distinct and risky") rules it out — the risky part (a click on the switch) is
  retired by the existing AX18 law, not by new design.
- **The other seams don't stand alone.** S1 (VirtualMicPair) without S2/S3 owns no criterion that it can
  check through the renderer (A1–A3 are measured on renders); A5 (loudness parity) needs both the early
  and the tail path in place, and S4's constant is derived from the pair's diffuse-field gain (S1/S3).
  Splitting early (S2) from tail (S3) would give an S2 sub-phase that ships a stereo mode with no tail —
  not a usable output and a listening pack (L2 "rooms clearly audible") it could not pass.
- **Size S**, well inside one session; no part approaches the two-session limit.

## 2. Order and rationale

Single unit; the phase file's own order (S1 → S2 → S3 → S4 → S5 → S6) is kept. Keeping it whole changes
no order of delivery, no dependency and no risk retirement, so by G1 it is **not a decision**.

- **CHOICE 09-c1 — granularity of the dependency on Phase 08 once 08 is split.** Options: (a) depend on
  the 08 umbrella, i.e. all 08 sub-phases (G3 default; the recorded dependency unchanged); (b) depend only
  on the 08 sub-phase(s) that deliver the shared accumulation path (BUILD_PLAN §Phase 09 "08 (shared
  accumulation path)"; phase-09 S2 "Reuse the Phase 08 accumulation structure") plus whichever delivers a
  working binaural mode, which A5 (LUFS vs binaural) and S5/A7/L3 (switch between binaural and
  stereoSpeakers) need. **Recommended: (a)**, because it moves nothing across a recorded dependency and
  needs no knowledge of the 08 map; (b) could let 09 start before 08 ends, which changes what ships first
  and is therefore a decision for the loop, not for this draft. Note for the decider: under (b) the 08
  sub-phases named must include binaural rendering of the tail and the plugin's `outputMode` pass-through
  (phase-08 scope 6), not only the early accumulation.

No other CHOICE.

## 3. Coverage table

| original item | goes to |
|---|---|
| Header: size S, depends on 07, 08, read-first list | 09 (whole) |
| G Goal | 09 (whole) |
| AS1 AQ7 (virtual ORTF, ±55°, 17 cm, no crosstalk cancellation; behind `StereoSpeakers` kind) | 09 (whole) |
| S1 `VirtualMicPair` (cardioid 3D gain, frequency-independent note, ±8.5 cm capsule delay, Phase 03 kernel) | 09 (whole) |
| S2 Early part (per-image accumulation, Phase 08 structure and grouping rule) | 09 (whole) |
| S3 Late tail (two decorrelated tails, analytic ORTF diffuse coherence per band, formula documented, Phase 04 envelopes) | 09 (whole) |
| S4 Level match (BS.1770 via pinned `pyloudnorm`, ±1 dB vs binaural, fixed constant, not per-scene, AX2) | 09 (whole) |
| S5 Plugin `output_mode` switches `Kind`, IR rebuild, Phase 06 crossfade, equal-power (AX18) | 09 (whole) |
| S6 `render_cli --mode stereoSpeakers`, listening pack, goldens | 09 (whole) |
| OS Out of scope (crosstalk cancellation, speaker calibration, multichannel) | 09 (whole) |
| A1 Exact-geometry L−R gate at 5 m (φ set, sign/mirror, peak ±3° of ≈+56.7°, plane-wave 9.7 / 20.1 dB) | 09 (whole) |
| A2 Centre emitter \|L−R\| < 0.1 dB, 0-sample delay | 09 (whole) |
| A3 90° ITD = 17 cm / c ±1 sample at 48 kHz | 09 (whole) |
| A4 Tail coherence per band ±0.1 of analytic target | 09 (whole) |
| A5 \|LUFS(stereoSpeakers) − LUFS(binaural)\| ≤ 1 dB, reference + 3 fixtures | 09 (whole) |
| A6 Mono compatibility, no notch > 6 dB below 2 kHz | 09 (whole) |
| A7 Mode switch, 0 click events across 10 switches | 09 (whole) |
| A8 All earlier tests and pluginval still pass | 09 (whole) |
| L1 Stable phantom centre, L/R spread | 09 (whole) |
| L2 Rooms audible and distinguishable on speakers | 09 (whole) |
| L3 Switch during playback smooth, roughly equal loudness | 09 (whole) |
| L4 On headphones, like a decent room recording | 09 (whole) |
| L5 Mono check | 09 (whole) |
| C1a/C1b/C1c Contractor focus (geometry; coherence formula; normalization) | 09 (whole) |
| R1 Height/depth expectations on speakers; UI text in Phase 11 | 09 (whole) (the UI text itself stays Phase 11's) |
| D1 All automated criteria green | 09 (whole) |
| D2 Status row 09 `done` | 09 (whole) |
| D3 Checklist in the PR | 09 (whole) |
| Raise with Maisara | none in the file |
| Settled / decisions before implementation | none in the file |

Nothing unassigned, nothing assigned twice.

## 4. References

Grep of the repo (excluding `docs/corpus`, `docs/review`, `docs/sessions`, `.git`) for Phase 09 /
`phase-09` references. Because the phase is kept whole, every reference keeps resolving as written.

| file:line | reference | → |
|---|---|---|
| `src/sim/Engine.h:5` | "stereo speakers in Phase 09" (body of `buildRoomIR`) | 09 (whole), S2/S3 |
| `docs/BUILD_PLAN.md:34` | §0 status row 09 | 09 (whole); row unchanged |
| `docs/BUILD_PLAN.md:118` | AX18 "the output-mode switch (Phase 09)"; phases column "04, 06, 07, 09, 10" | 09 (whole), S5 |
| `docs/BUILD_PLAN.md:307` | "### Phase 09 — Stereo-speaker output mode · S" summary | 09 (whole) |
| `docs/BUILD_PLAN.md:318` | Phase 10 dependencies "06, 07, 08, 09" | 09 (whole) |
| `docs/BUILD_PLAN.md:328` | Phase 11 dependencies "07, 09" | 09 (whole) |
| `docs/BUILD_PLAN.md:391` | §6 change log 2026-11-05 "Phase 09 gate … (B1)"; AX18 "Phases 06, 09, 10" | 09 (whole), A1 / S5 |
| `docs/phases/phase-03.md:34` | DOA "stereo-speaker mode needs it in Phase 09" | 09 (whole), S1/S2 |
| `docs/phases/phase-06.md:18` | AX18 "(Phase 09 mode switch, …)" | 09 (whole), S5 |
| `docs/phases/phase-08.md:171` | "`stereoSpeakers` keeps using omni until Phase 09" | 09 (whole), S5 |
| `docs/phases/phase-10.md:3` | Depends on "06, 07, 08, 09" | 09 (whole) |
| `docs/phases/phase-10.md:39-40` | tail cache "Phase 04/08/09 … per output for 08/09" | 09 (whole), S3 |
| `docs/phases/phase-11.md:3` | Depends on "07, 09" | 09 (whole) |
| `docs/phases/phase-13.md:3` | Depends on "00–12" (range includes 09) | 09 (whole) |
| `.claude/skills/review-phase-pr/references/binaural-and-stereo.md:44-45` | scope note, `docs/phases/phase-09.md` | 09 (whole) |
| `.claude/skills/review-phase-pr/references/binaural-and-stereo.md:545` | "phase-09 assumption" (ideal capsule) | 09 (whole), S1 |
| `.claude/skills/review-phase-pr/references/binaural-and-stereo.md:555` | "phase-09 test: ±1 sample at 48 kHz" | 09 (whole), A3 |
| `.claude/skills/review-phase-pr/references/binaural-and-stereo.md:562` | "phase-09's … centre emitter" mono test | 09 (whole), A6 |
| `.claude/skills/review-phase-pr/references/binaural-and-stereo.md:580` | "Phase 09 wants one fixed constant (AX2)" | 09 (whole), S4 |
| `.claude/skills/review-phase-pr/references/knowledge-inventory.md:51` | "ITU-R BS.1770 … Phase 09 tests" | 09 (whole), A5 |
| `.claude/skills/review-phase-pr/references/phase-checklists.md:272` | "## Phase 09 — Stereo-speaker output mode" checklist | 09 (whole) |
