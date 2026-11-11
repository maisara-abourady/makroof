# Split map: Phase 08 — Binaural output with a generic HRTF

Drafted from `docs/phases/phase-08.md` (344 lines, as on branch `claude/funny-rubin-pdkwd1`) under
`docs/review/phase-split/0-drafting-brief.md`. This is a reallocation only: no scope item, criterion, threshold,
AX/AQ value, listening item, contractor focus or risk is added, dropped or reworded. Where a compound scope
item or criterion is cut, the clauses are quoted verbatim.

Labels used below. **S1…S10** = scope items 1–10 (S2a "Embed bound", S2b "Dataset-agnostic header", S3a lookup /
`query`, S3b "Diffuse-field equalization …", S5a "Early part", S5b "Late tail", S5c "Energy", S5d "E_b and
t_mix,e …"). **AC1…AC13** = the automated criteria in file order (AC1 licence, AC2 converter round-trip, AC3 ITD/ILD
sanity, AC4 interpolation continuity, AC5 tail coherence, AC6 energy, AC7 orientation (AX3), AC8 T30, AC9 DF-EQ
identity, AC10 validation-only override, AC11 E_b parity (AX44), AC12 "All earlier tests …", AC13 restore gate).
The phase file itself already numbers AC 2, AC 3, AC 4 that way. **L0** = the checklist preamble, **L1…L7** the
listening items in order. **CF1…CF9** = the contractor review focus clauses in order. **R1…R7** = the risks in
order. **DoD1…DoD5** = the definition-of-done clauses. **H-dep (i)…(iv)** = Seat 4's AX37 (5.3) conditions in the
header line.

## 1. Sub-phase table

| id | title | lead subject matter (seat · convening-table row words) | size | depends on | ships | automated criteria owned |
|---|---|---|---|---|---|---|
| 08-1 | HRTF data, converter and lookup | Seat 4 Chain keeper · "HRTF dataset choice and licence; binaural architecture" | M | as recorded for 08 (04, 05b, 05h except AX37 (5.3), 07); nothing in 08-1 reads E_b or t_mix,e, so Seat 4's conditions are vacuous here (CHOICE 08-c1) | licensed, pinned, converted `resources/hrtf/generic-v1.bin` with its dataset-agnostic header and Voronoi-weighted DF-EQ / coherence target, embedded in `sim`, and `HrtfSet::query` with interpolated HRIRs + ITD | AC1, AC2, AC4, AC9 (both clauses) |
| 08-2 | Head-relative early binaural part | Seat 4 Chain keeper · "binaural architecture" | M | 08-1; 03/04 image sources (done), 05b (specular-only early part, AX21); 05h as recorded, conditions vacuous (no E_b read) (CHOICE 08-c1) | `ListenerFrame` (AX3), BRIR early part through the HRTF, `buildRoomIR(Kind::Binaural)` 2×2, `render_cli --mode binaural`, the `--hrtf` validation override, anechoic listening-pack renders incl. `anechoic_azimuth_sweep.wav` | AC3, AC7, AC10 |
| 08-3 | Binaural late tail, level parity and plugin mode | Seat 4 Chain keeper · "binaural architecture; … cross-format loudness and timbre parity" | M | 08-2; 05h, except it may precede 05h on Seat 4's conditions **(i)** E_b and t_mix,e read only via `TailMatch`, **(ii)** parity checked within the same build, **(iv)** this sub-phase's listening items on concentrated absorption marked provisional (AX37 (5.3), D-T5.3); 06, 07 (done) | two seeded ear tails mixed to the HRTF-derived interaural coherence, diffuse-field magnitude per ear, omni/binaural energy and T30 parity, E_b via `TailMatch` (AX39 one solve), plugin `output_mode = binaural` wired, room listening-pack renders incl. the both-near render | AC5, AC6, AC8, AC11, AC12 clause "pluginval passes." |
| 08-4 | Binaural timing records, restore gate and golden freeze | Seat 5 Deadline keeper · "worst-case callback time; … host conformance (pluginval, auval, state …); … CI gates" | M (S-to-M in the 08-first order, where S9/S10 move to phase-05h scope 10) | 08-3; 05h, except AX37 (5.3) condition **(iii)**: if 08 precedes 05h, 05h re-renders this sub-phase's binaural goldens, re-measures binaural W1/W2 and re-runs item 8 (phase-05h scope 10); S9 and S10 only if 05h is `done` (otherwise phase-05h scope 10 carries them); phase-07c brought forward before this sub-phase's golden freeze if S10's gate fails (07c depends on 05h) | plugin CPU / BRIR-build benchmark in binaural, the 2° grouping decision taken on it, item 8's update-time record, W1/W2 per mode with the diffuse share and the binaural AX38 (iv) records, the heaviest-mode restore gate, the goldens for 3 scenes frozen | AC12 clauses "Plugin CPU benchmark is recorded." and "If 05h is `done`: W1/W2 per output mode with the diffuse share and the binaural AX38 (iv) records are recorded (scope 9); otherwise phase-05h scope 10 records them."; AC13 |

AC12's first clause "All earlier tests still pass." is umbrella (shared): every sub-phase keeps it.

Why not keep 08 whole: the file is L and already cut into two sessions; its Session 2 (S4–S10) holds three
distinct subject matters (head-relative early rendering and the onset/sign risk; the diffuse-coherence tail and
cross-mode level parity, which is where the 05h coupling bites; and timing/CI gates with the golden freeze,
which is where 07c's bring-forward bites). Why Session 1 stays whole as 08-1: the embed route (S2a) is chosen
"so that AC 2 … and AC 4 (continuity) hold on the real file", and AC9's second clause needs AC2 and AC4 green on
the same file. Cutting the converter from `HrtfSet` would put the embed-bound loop across two sessions with a
re-conversion between them; 08-1 keeps that loop in one sub-phase.

## 2. Order and rationale

Order: **08-1 → 08-2 → 08-3 → 08-4**, linear, the phase file's own order (S1–S3, then S4–S7, then S8–S10).

- 08-1 first: every later sub-phase reads `HrtfSet`; the licence gate (S1, "Licence first") and the pin-time
  source-state check must precede any golden. Risks retired first: licence (S1 fallback/blocked), embed bound (R4),
  source EQ state (R6), as the phase file orders them.
- 08-2 before 08-3: the early part and AC3's onset ITD need no tail; the tail's diffuse-field magnitude and
  coherence target come from 08-1, not from 08-2, so 08-3 could technically go before 08-2, but `Kind::Binaural`
  (S6 clause 1) and `render_cli --mode binaural` (S7 clause 1) are built in 08-2 and 08-3 extends them. Keeping
  the phase order retires the ITD-window risk (R5, C-1) before the 05h-coupled risk.
- 08-4 last: S10 requires the gate "to land before this phase's goldens are frozen"; the goldens (S7 clause 3)
  therefore sit in 08-4 with S10, and the grouping rule ("measure first", S5a clause 2) sits with the benchmark
  that decides it.
- Intermediate state: after 08-2, `render_cli --mode binaural` gives the early part only and the plugin still
  routes `binaural` to the omni preview (S6 clause 2 lands in 08-3). `main` stays green; nothing ships a
  half-binaural mode to the plugin.

Elements the session brief counts as decisions (G1), for the decider:

- **CHOICE 08-c1 (dependency attachment, AX37 (5.3)).** Options: (a) every sub-phase carries the full recorded
  line "Depends on 04, 05b, 05h, 07 … except AX37 (5.3) (i)–(iv)" unchanged; (b) the line is carried by every
  sub-phase, with each of Seat 4's conditions attached where it bites — (i), (ii), (iv) to 08-3, (iii) to 08-4 —
  and 08-1/08-2 recorded as reading no E_b or t_mix,e, so they may precede 05h under the existing AX37 exception
  with the conditions vacuous; (c) drop 05h from 08-1/08-2 outright. Recommended **(b)**: it moves nothing across
  the recorded dependency (the AX37 exception already lets all of 08 precede 05h on these conditions) and says
  which sub-phase each condition binds; (c) would be a new dependency reading. Why it is a decision: the brief
  names AX37 (5.3) as a recorded dependency a cut may cross.
- **CHOICE 08-c2 (golden freeze placed after the restore gate).** Options: (a) S7's "goldens for 3 scenes" in 08-3
  with the rest of the BRIR; (b) in 08-4 with S10. Recommended **(b)**: S10 and AC13 already require the gate
  result (and, on a failure, phase-07c) before "this phase's goldens are frozen", and AC13's last clause
  ("capped-room goldens with the SE-derived tolerance unless phase-07c has landed") is about those goldens. Why it
  is a decision: it fixes where 07c's bring-forward lands (07c timing is a recorded dependency) and moves the
  golden freeze later in delivery than a reader of S7 alone would place it.
- **CHOICE 08-c3 (2° grouping rule moved to the benchmark sub-phase).** Options: (a) S5a's whole "Early part"
  bullet in 08-2; (b) the first and last sentences of S5a (accumulation; "The direct path and orders 1–3 are
  never grouped.") in 08-2, and "**No 2° grouping until the Phase 08 benchmark shows it is needed; measure
  first.** Only if the measured BRIR build time calls for it, group … and document the approximation." with R3
  and CF6 in 08-4. Recommended **(b)**: the measurement it waits for (BRIR build time against AQ4's cadence, AX33;
  AC12 CPU benchmark) is 08-4's. Consequence to record: if 08-4 introduces grouping, 08-2/08-3's AC3, AC5, AC6,
  AC8 re-run on the grouped output before the goldens freeze. Why it is a decision: it orders a possible output
  change after 08-3's checks.
- **CHOICE 08-c4 (where the onset criterion is named).** AC3 says the onset criterion and sign convention are
  "named in this AC by the decision loop **before the first measurement**", and the estimator is "the converter's
  per-ear onset detection that yields `onset_left`/`onset_right`". The converter (S2) and AC4's ITD-per-step check
  run in 08-1, before AC3's own test in 08-2. Options: (a) the decision loop names the criterion at the start of
  08-1, before the converter's first run; AC3 stays in 08-2; (b) move AC3 into 08-1. Recommended **(a)**: AC3
  needs a rendered anechoic output (`Kind::Binaural`, 08-2), while the first onset measurement is 08-1's. Why it
  is a decision: it puts a pre-measurement decision of AC3 into an earlier sub-phase than the criterion.
- **CHOICE 08-c5 (size: four sub-phases where the file planned two sessions).** Options: (a) four sub-phases as
  above (≈ four sessions); (b) three: merge 08-2 and 08-3 into one "BRIR assembly" sub-phase (S4–S7, L, two
  sessions). Recommended **(a)**: each sub-phase owns distinct criteria and one lead row, and the original
  Session 2 (S4–S10 in one session) is the part of the file most likely to overrun. Why it is a decision: the
  umbrella's planned effort moves from two sessions to about four (each sub-phase stays within the two-session
  limit; its remainder would be `08-<n>b`).

Not decisions (pure reallocation, for the record): the lead seats (read from the convening table: Seat 4's row
covers 08-1 to 08-3, Seat 5's row covers 08-4; Seat 3's "decay matching; channel spreading" and Seat 2 are
touched by 08-3 and are convened there by the decider as usual); keeping S1–S3 together (follows the file's
Session 1).

## 3. Coverage table

| original item | → sub-phase | note |
|---|---|---|
| Header: Size L, "split into 08 and 08b if needed" | umbrella | replaced by per-sub-phase sizes; remainders are `08-<n>b` (G3) |
| Header: Depends on 04, 05b, 05h, 07; 05b either outcome, AX21 | umbrella (shared) | 05b/AX21 bites in 08-2 |
| Header: AX37 (5.3) exception, H-dep (i) | 08-3 | umbrella (shared); CHOICE 08-c1 |
| H-dep (ii) | 08-3 | umbrella (shared) |
| H-dep (iii) | 08-4 | umbrella (shared); also phase-05h scope 10 |
| H-dep (iv) | 08-3 | umbrella (shared); phase-05h line 286 note re-listens them |
| Header: Read first (CLAUDE.md, §2 AQ6/AX3/AX5/AX35, §3 F7/F8, PRD FR-SIM-3, FR-SIM-4, FR-3D-9, A1) | umbrella | |
| Header: D1 decision behind scope 1–3 | 08-1 | |
| Goal | umbrella | |
| Assumption AQ6 | umbrella | |
| Assumption AX3 | umbrella (shared) | bites in 08-2 (S4, AC7) |
| Assumption AX5 | umbrella (shared) | bites in 08-3 (S5b ear seeds) |
| Assumption AX37 (5.3) / B18; AX39; AX38 | umbrella (shared) | AX37/AX39 bite in 08-3; AX38 in 08-4 |
| Assumption AX35 | umbrella (shared) | converter in 08-1; "before goldens are frozen" ends at 08-4 |
| S1 Licence first (dataset, pin-time reads, licence, fallback MIT KEMAR, TH Köln exclusion, blocked/escalate) | 08-1 | |
| S2 converter (resample, trim with fade, onset removal + ITD, `.bin`, never commit SOFA) | 08-1 | |
| S2a Embed bound (incl. AC2 reference definition, "report it (decision reversal condition 3)") | 08-1 | |
| S2b Dataset-agnostic header (incl. "No UI code or string table knows which head shipped …") | 08-1 | UI clause umbrella (shared): binds 08-3's plugin wiring too |
| S3 `HrtfSet` (build-step embedding, immutable, O(1) index, no L–R symmetry, `[alloc]` on `query`) | 08-1 | "`[alloc]` … on the BRIR build" clause → 08-2 (shared with 08-3, which extends the build) |
| S3a `query` with Delaunay/barycentric, onset-removed interpolation, separate ITD | 08-1 | |
| S3b DF-EQ computed once and applied; Voronoi weights; source-state consistency check; provenance | 08-1 | |
| S4 `ListenerFrame` (AX3) | 08-2 | |
| S5a Early part: accumulation per image source + per-ear ITD; "The direct path and orders 1–3 are never grouped." | 08-2 | |
| S5a "No 2° grouping until … measure first. Only if … document the approximation." | 08-4 | CHOICE 08-c3 |
| S5b Late tail (two seeded tails, Phase 04 envelopes, 2×2 coherence mixing, DF magnitude per ear) | 08-3 | |
| S5c Energy (binaural vs omni ±1 dB) | 08-3 | |
| S5d E_b and t_mix,e via `TailMatch` (AX37), one solve (AX39), bit-identical (AX44) | 08-3 | |
| S6 clause "`sim::buildRoomIR(Kind::Binaural)` returns the 2×2 BRIR matrix: emitter L → ear L/R and emitter R → ear L/R." | 08-2 | early part; 08-3 adds the tail to the same path |
| S6 clause "The plugin sends `outputMode` through, so `binaural` now uses this path. `stereoSpeakers` keeps using omni until Phase 09." | 08-3 | |
| S7 clause "`render_cli --mode binaural`" | 08-2 | |
| S7 clause "listening-pack entries" | shared 08-2 / 08-3 | 08-2: anechoic renders (incl. `anechoic_azimuth_sweep.wav`); 08-3: room renders and omni previews |
| S7 clause "(including one both-near binaural render: … AX44, Seat 4)" | 08-3 | |
| S7 clause "goldens for 3 scenes" | 08-4 | CHOICE 08-c2 |
| S7 clause "`render_cli --hrtf <file>`: a **validation-only** override …" | 08-2 | |
| S7 clause "Every preset validation log … records the `hrtfId` and the header's set identity string …; this phase's checklist does the same." | umbrella (shared) | every sub-phase checklist (08-2, 08-3) |
| S8 Update-time check (P06F-4; which limit; fade; W1 window; AX31 reversal; AX38 (v); Seat 1 reading) | 08-4 | re-run by phase-05h scope 10 in the 08-first order |
| S9 Records from 05b (AX38) — only if 05h `done` | 08-4 | otherwise phase-05h scope 10 |
| S10 Restore gate in the heaviest mode — only if 05h `done` | 08-4 | otherwise phase-05h scope 10; 07c bring-forward before 08-4's golden freeze |
| Out of scope (B4, head tracking, near-field) | umbrella | |
| AC1 Licence file + CI script | 08-1 | |
| AC2 Converter round-trip (both terms) | 08-1 | |
| AC3 ITD/ILD sanity | 08-2 | criterion-naming step before the first measurement → start of 08-1 (CHOICE 08-c4) |
| AC4 Interpolation continuity | 08-1 | |
| AC5 Tail coherence | 08-3 | |
| AC6 Energy | 08-3 | |
| AC7 Orientation (AX3) | 08-2 | |
| AC8 T30 per ear vs omni | 08-3 | |
| AC9 DF-EQ identity (both clauses: identity; embed bound with AC2 and AC4 green, size in the PR) | 08-1 | |
| AC10 Validation-only override | 08-2 | |
| AC11 E_b parity (AX44) | 08-3 | |
| AC12 "All earlier tests still pass." | umbrella (shared) | every sub-phase |
| AC12 "pluginval passes." | 08-3 | the sub-phase that changes the plugin (CI runs it on all) |
| AC12 "Plugin CPU benchmark is recorded." | 08-4 | |
| AC12 "If 05h is `done`: W1/W2 … (scope 9); otherwise phase-05h scope 10 records them." | 08-4 | |
| AC13 Restore gate, heaviest mode | 08-4 | |
| L0 preamble (pack `binaural/`, head never named, fixed acceptance set, anechoic + omni beside each render, forced-choice form, record `hrtfId`/set identity) | umbrella (shared) | applies to 08-2's and 08-3's checklists |
| L1 Default scene ±30° ahead | 08-3 | |
| L2 `anechoic_azimuth_sweep.wav` | 08-2 | |
| L3 Listener close to the L emitter | 08-3 | |
| L4 Large hall surrounds | 08-3 | |
| L5 Colour vs omni preview, room and anechoic render | 08-3 | |
| L6 Complaint protocol (Seat 9) | 08-3 | |
| L7 Hand-off to Phase 11 (Seat 6) PR line | 08-3 | the sub-phase that wires `binaural` into the plugin |
| CF1 Licence review (re-read at pin time; head named nowhere in UI) | 08-1 | "head named nowhere in UI" umbrella (shared) |
| CF2 HRIR interpolation (triangulation, ITD handling, the named onset estimator) | 08-1 | |
| CF3 coordinate and sign conventions | 08-2 | |
| CF4 dataset-agnostic header, Voronoi-weighted DF-EQ / coherence averages with the identity test | 08-1 | |
| CF5 two-term AC 2 reference | 08-1 | |
| CF6 image-source grouping approximation (if introduced) | 08-4 | |
| CF7 diffuse-coherence mixing | 08-3 | |
| CF8 energy normalization between modes | 08-3 | |
| CF9 `--hrtf` override staying out of the scene and the plugin | 08-2 | |
| R1 front/back confusion, weak externalization (B4 evidence) | umbrella (shared) | heard in 08-2 (L2) and 08-3 (L1) |
| R2 F8 head always faces emitters | 08-2 | |
| R3 BRIR build time; grouping only if the benchmark shows it | 08-4 | |
| R4 four-rate embed ≤ ~32 MB (decision reversal condition 3) | 08-1 | |
| R5 AC3 ITD window (C-1) | 08-2 | the first ITD figures appear in 08-1 (converter onsets, AC4) |
| R6 pin-time source-state check, "not confirmed", raised before any golden | 08-1 | the "before any golden is frozen" limit ends at 08-4 |
| R7 headphone compensation, no slot (B14) | 08-3 | |
| Raise-type items in the text (no "Raise with Maisara" section exists in phase-08.md): S1 "If neither allowed dataset is clearly licensed … mark the phase `blocked` and escalate"; S3b / R6 "not confirmed" raised "with Maisara and through the interrogator before the Phase 08 goldens are frozen"; S2a / R4 "report it (decision reversal condition 3: Maisara is told …)" | 08-1 | carried verbatim; routed under `docs/board/README.md` "Who answers Maisara's questions" by the executing session |
| Decision before implementation: AC3 onset criterion and sign convention named by the decision loop before the first measurement | 08-1 (start) | CHOICE 08-c4 |
| Decision before measuring: S8 "state which limit is applied … and whether the 30 ms fade counts" | 08-4 | |
| DoD1 All automated criteria green | umbrella (shared) | each sub-phase for its own |
| DoD2 licence re-read on the official record at pin time and recorded (scope 1) | 08-1 | |
| DoD3 head named only in `LICENSE-generic-v1.txt`, `docs/THIRD_PARTY.md` and the public testing record | umbrella (shared) | first set in 08-1 |
| DoD4 status row 08 `done` (or 08b added) | umbrella | row 08 becomes `split (08-1…08-4)`, `done` when all four are; remainders `08-<n>b` (G3) |
| DoD5 checklist in the PR with the `hrtfId` and set identity string | umbrella (shared) | 08-2 and 08-3 PRs |

Nothing unassigned; shared items are umbrella + the sub-phase(s) named.

## 4. References

Grep of the repo (excluding `docs/corpus`, `docs/review`, `docs/sessions`, `.git`, build dirs) for references to
Phase 08 items. Change-log rows (§6) are history and are not re-pointed; their mapping is listed for the reader.

| file:line | reference | → sub-phase |
|---|---|---|
| docs/BUILD_PLAN.md:30 | §0 row 06b "phase-08 item 8 limit note" | 08-4 |
| docs/BUILD_PLAN.md:32 | §0 row 07c "Brought ahead of Phase 08's golden freeze if Phase 08's heaviest mode fails the restore gate" | 08-4 |
| docs/BUILD_PLAN.md:33 | §0 row 08, AX37 (5.3) conditions (i)–(iv) | umbrella; (i),(ii),(iv) 08-3, (iii) 08-4 |
| docs/BUILD_PLAN.md:59 | §1 HRTF row "phase-08 scope 1–3", "conditions in phase-08 scope 1", "re-entry condition in phase-08 scope 1" | 08-1 |
| docs/BUILD_PLAN.md:95 | AQ10 "every output mode from Phase 08"; "from Phase 08 on, the gate measures the heaviest output mode"; "before Phase 08's goldens are frozen" | 08-4 |
| docs/BUILD_PLAN.md:131 | AX31 "deferred to phase-08 item 8"; "Open for Phase 08 …"; "phase 08 applies this row's reversal clause" | 08-4 |
| docs/BUILD_PLAN.md:135 | AX35 "Before the Phase 08 goldens are frozen a converter re-run is a parameter change"; "head chosen in Phase 08" | 08-1 (converter, head); freeze point 08-4 |
| docs/BUILD_PLAN.md:137 | AX37 "phase-08 scope 5 unchanged"; (iii) "re-runs phase-08 item 8"; (iv) "Phase 08 listening items on concentrated absorption"; B18 blind test on Phase 08 binaural | 08-3 (scope 5, (iv)); 08-4 ((iii)); B18 umbrella |
| docs/BUILD_PLAN.md:138 | AX38 (iv) "from Phase 08 also in binaural mode"; "(v) Phase 08 item 8"; W1/W2 per output mode; heaviest-mode gate, Phase 08's goldens | 08-4 |
| docs/BUILD_PLAN.md:144 | AX44 "Phase 08: E_b bit-identical between omni and binaural and between the ears" | 08-3 |
| docs/BUILD_PLAN.md:212 | Phase 04 out of scope "binaural tail decorrelation (Phase 08)" | 08-3 |
| docs/BUILD_PLAN.md:251 | 05b "Phase 08 builds on 05b in either outcome" | 08-2 |
| docs/BUILD_PLAN.md:291, :293 | 07c "Phase 08's capped-room golden tolerance"; "ahead of Phase 08's golden freeze" | 08-4 |
| docs/BUILD_PLAN.md:297–300 | §4 Phase 08 summary | umbrella |
| docs/BUILD_PLAN.md:377 | §5 B18 "Phase 08 binaural" blind test | umbrella (after 08-3) |
| docs/BUILD_PLAN.md:402, 429, 430, 438, 439, 441, 442, 445, 446, 449, 450 | §6 change-log rows (phase-08 depends on 05b; item 8 added/limit note; scope 1 SADIE II; AC 2 two-term; AX37 E_b only; dependency on 05h; scope 10 and AC; scopes 9 and 10 conditional; golden freeze) | history: 402/445 umbrella; 429/430 08-4; 438/439 08-1; 441/442 08-3; 446/449/450 08-4 |
| docs/phases/phase-03.md:34 | direction of arrival "Phase 08 needs it" | 08-2 |
| docs/phases/phase-04.md:187 | "Phase 08 will need decorrelated tails per ear" | 08-3 |
| docs/phases/phase-05b.md:14 | "Phase 08 builds on the specular-only early part" | 08-2 |
| docs/phases/phase-05b.md:64–65 | per-patch contributions "so that Phase 08 can assign directions … Phase 08's decision" | umbrella (superseded by AX37 (5.3); B18) |
| docs/phases/phase-05b2.md:161, 248, 251 | "Phase 08 gets E_b and t_mix,e only"; "decide what Phase 08 receives" | 08-3 |
| docs/phases/phase-05b2.md:397, 400–403, 408 | dependency gains 05h; D-T5.3 conditions (i)–(iv); "Phase 08 directions beyond D-T5 (3)" | umbrella; (i),(ii),(iv) 08-3, (iii) 08-4 |
| docs/phases/phase-05h.md:48 | "Phase 08 gets E_b and t_mix,e only (5.3)" | 08-3 |
| docs/phases/phase-05h.md:78–79 | "Phase 08 may precede this phase …; re-renders the binaural goldens, re-measures binaural W1/W2 and re-runs phase-08 item 8 (scope 10)" | 08-4 (goldens, W1/W2, item 8); precedence umbrella |
| docs/phases/phase-05h.md:220–227 | scope 10: "re-run phase-08 item 8 … phase-08 scopes 9 and 10 … Phase 08's goldens" | 08-4 |
| docs/phases/phase-05h.md:267–269 | AC: "phase-08 item 8 re-run … (phase-08 scopes 9 and 10)" | 08-4 |
| docs/phases/phase-05h.md:286 | note: Phase 08 listening items on concentrated absorption re-listened | 08-3 |
| docs/phases/phase-05h.md:314 | out of scope "Phase 08 directions beyond AX37 (5.3)" | umbrella |
| docs/phases/phase-06b.md:150 | "`docs/phases/phase-08.md` scope item 8" | 08-4 |
| docs/phases/phase-07.md:34, 36 | "Binaural is Phase 08"; "Phase 08 changes the render of 07-era states" | 08-3 (plugin `output_mode` wiring) |
| docs/phases/phase-07.md:83 | reversal "Phase 08 listening find the tie jumps objectionable" | 08-3 (room listening) |
| docs/phases/phase-07.md:279 | "in Phase 08's binaural render it is less audible" | 08-3 |
| docs/phases/phase-07c.md:48–50 | "Brought ahead of Phase 08's golden freeze … (AX38 4c; phase-08 scope 10)" | 08-4 |
| docs/phases/phase-07c.md:106 | "Phase 08 goldens in capped rooms carry a tolerance …" | 08-4 |
| docs/phases/phase-09.md:26 | "Reuse the Phase 08 accumulation structure" | 08-2 |
| docs/THIRD_PARTY.md:51 | "The HRTF dataset arrives in Phase 08" | 08-1 |
| docs/THIRD_PARTY.md:67–68 | "`docs/phases/phase-08.md` scope 1"; "pinned in Phase 08 session 1" | 08-1 |
| src/sim/Engine.h:4 | "binaural in Phase 08" | 08-2 (`Kind::Binaural`), completed in 08-3 |
| src/sim/tail/NoiseTail.h:44 | "Phase 08 hook: per-output seed offset" | 08-3 |
| src/plugin/PluginProcessor.h:15 | omni preview "until Phase 08" | 08-3 |
| tests/unit/test_noise_tail.cpp:244 | test "per-output seed offset for Phase 08" | 08-3 |
| .claude/skills/review-phase-pr/references/phase-checklists.md:240–268 | "Phase 08 — Binaural output …" review checklist (whole phase) | umbrella; its lines map: licence/converter/HrtfSet/round trip/continuity 08-1; ListenerFrame, coordinate mapping, ITD/ILD, `--mode binaural` 08-2; coherence, energy, T30, two seeded tails 08-3; grouping, goldens 08-4. Finding for the plan-editor (not changed here): it says "diffuse-field EQ switchable", while phase-08 S3b says "always applied" and "no product code path switches the EQ off" |
| .claude/skills/review-phase-pr/references/binaural-and-stereo.md:43–50 | Phase 08 scope; "+90° azimuth = left" | 08-2 |
| …binaural-and-stereo.md:310, 383–384 | continuity criterion (≤ 30 µs, ≤ 1 dB per 1° step) | 08-1 |
| …binaural-and-stereo.md:315, 322, 324 | AC3 ITD/ILD figures | 08-2 |
| …binaural-and-stereo.md:340 | front/back confusion is the Phase 08 risk | umbrella (R1) |
| …binaural-and-stereo.md:416 | level consequences for the ±1 dB energy test | 08-3 |
| …binaural-and-stereo.md:467, 488 | coherence target from the set; ±0.1 tolerance | target 08-1; AC5 08-3 |
| …binaural-and-stereo.md:503 | direction clustering above order 3 | 08-4 (grouping); "direct and orders 1–3 exact" 08-2 |
| …binaural-and-stereo.md:518 | near-field: not extrapolating the 1/r law | umbrella (out of scope) |
| .claude/skills/review-phase-pr/references/knowledge-inventory.md:49 | HRTF dataset licence, Phase 08, `LICENSE-*.txt` | 08-1 |
| .claude/skills/review-phase-pr/references/room-acoustics.md:538 | "wrong HRTF direction in phase 08" | 08-2 |
