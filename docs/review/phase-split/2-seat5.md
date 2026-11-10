# Seat 5 (deadline keeper), position — phase split, 08-c1, 08-c3, 11-c1, 13-c1 (2026-11-10)

Saved by the orchestrator from the seat's report. Corpus not needed.

**1. Reading.** Four orderings/attachments plus the 08-c2 and 13-c4 resolutions. Cues: worst case measured on the
final build (§2 criterion 1); offline determinism before goldens freeze (criterion 2); host-conformance gates ahead of
the code they guard (CS-3.6, CS-6); measure once on final code (§10.6).

**2–4. Ranking and tension (now / later).**
- **08-c1.** (b) prefer, 0/1. (a) can live with, 1/1 (noisier, silent on where (iii) bites). (c) cannot live with as a
  reading of AX37, 1/2 (adds a dependency reading no seat set). Debt under (b): phase-05h scope 10 fires "only if
  Phase 08 went first" — ambiguous after the split. Item 8, S9, S10, W1/W2 and the golden freeze all sit in 08-4
  (08-c2), so the right trigger is "08-4 ran before 05h was done". Under the umbrella reading 05h would re-render
  goldens that don't exist yet; under the opposite misreading nobody re-measures.
- **08-c2 (goldens in 08-4):** agree, 0/0.
- **08-c3.** (b) prefer, 1/1. (a) can live with, 1/2. AQ4/AX33: BRIR build time is a worker-clock quantity (spaces
  build starts, adds to update delay = rebuild + 2P), not a callback risk. Grouping changes output, item 8's delay,
  W1/W2 and t_restore at the AX38 4c scenes together; under (b) all sit in one sub-phase ahead of the freeze. Under
  (a), 08-2 decides before the full BRIR exists, so the benchmark is re-run in 08-4 anyway. If grouping lands: AC5,
  AC6, AC8 re-run (one CI round); AC3 (direct path) and AC7 (geometry) cannot move. Interval risk: from 08-3 the
  binaural mode runs unbenchmarked; no beta before 13-4, so within tolerance.
- **11-c1.** (a) prefer, 1/0: 11-1 is one subject under my row (editor lifecycle, message-thread discipline A5,
  pluginval with editor on 3 OSes A6, state and size round trip A7, DPI R2); its gates guard every canvas and panel
  line written in 11-2/11-3 (CS-6). S1e/S1f/S6/S7: wording fixed in the phase file; in 11-1 they are atomic/flag reads
  polled by a timer (CS-4 step 4). (c) can live with, 0/1. (b) can live with on a condition, 2/2 (moves A5 to the
  second sub-phase: drag/gesture code writing parameters from the message thread built before the guard exists;
  first sub-phase L).
- **13-c1.** (a) prefer with a condition, 1/2 without, 1/1 with: S9 (p99.9 < 100 % at small buffers on real Apple
  silicon) is the only real-hardware worst-case callback measurement; it belongs on final code, after 13-1. Debt: a
  miss reopens `13-1b` after 13-2 recorded the C3 residual and FTZ guard; both re-run, universal binary rebuilt.
  (b) can live with, 1/1 (measurement under a Seat 2 lead; 13-1 needs hardware). (c) cannot live with, 2/3 (S9 and
  the AX5 residual measured on code still being optimised; invalid by the phase's own trap).
- **13-c4:** agree, 0/0 (R3, R4 are restore-path matters; raise first in 13-1).

**5. Evidence.** AQ4/AX33 (BUILD_PLAN §2); phase-08 S5a; phase-05h lines 220–229 (scope 10 trigger); §2 criterion 1,
§10.6; CS-6, WI-3. Whether S9 needs the universal binary or a native arm64 build: [Hyp], checkable in CI config.

**6. Conditions of acceptance.**
- 08-c1 (b): 08-4 and the umbrella state that condition (iii) and phase-05h scope 10 apply iff 08-4 runs before 05h
  is `done` (clarifying wording).
- 08-c3 (b): within 08-4: benchmark on the full BRIR → grouping decision → item 8, S9, S10 → golden freeze; timing
  recorded on the post-grouping build only. 1/1.
- 08-c3 (a): same order plus a re-benchmark in 08-4 → later 1.
- 11-c1 (b): A5 and the S1 lead-in "message thread only" in the first sub-phase → 1/1.
- 13-c1 (a): S9 runs first in 13-2, before C3's residual and S8 are recorded; a miss opens `13-1b` and 13-2's records
  are taken after it lands → 1/1.

**7. Hand-offs.** 08-1/08-2 reads: Seats 2, 4. Grouping audibility, L1–L6: Seat 1. S1e/S1f wording: Seat 6. 13-1 one
subject: Seat 2. K1–K3: Seat 7. Note for 13-4: if notarization forces hardened-runtime/entitlement changes, C1
(umbrella, full matrix) must be green on the signed build. Apple-silicon hardware for S9: Maisara.

**8. Premortem.** Without the in-13-2 ordering, S9 misses after the cross-architecture records; re-optimisation
silently invalidates C3's residual; the engineer notices when 13-3's pluginval runs on a different binary.

| option | now | later |
|---|---|---|
| 08-c1 (a) | 1 | 1 |
| 08-c1 (b) | 0 | 1 |
| 08-c1 (c) | 1 | 2 |
| 08-c3 (a) | 1 | 2 |
| 08-c3 (b) | 1 | 1 |
| 11-c1 (a) | 1 | 0 |
| 11-c1 (b) | 2 | 2 |
| 11-c1 (c) | 0 | 1 |
| 13-c1 (a) | 1 | 2 (1 with condition) |
| 13-c1 (b) | 1 | 1 |
| 13-c1 (c) | 2 | 3 |
