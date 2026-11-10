# Split map — Phase 07c (Asynchronous diffuse solve, Q2a (C))

Drafted from `docs/phases/phase-07c.md` (pure reallocation; brief `0-drafting-brief.md`). No threshold, number,
AX/AQ value, criterion wording or decision is changed. Item labels below are the phase file's own: §0–§10,
scope conditions 1–8 (§5), automated criteria A1–A9 (§6, in file order), listening items L1–L3 (§7), contractor
focus F1–F6 (§8, split at its semicolons), decisions D-C1–D-C3 and researcher questions R1–R3 (§4), Raise item
§2.1, timing bullets T1–T3 (§3).

Automated criteria, as numbered here (verbatim first words):
- A1 "D-C1–D-C3 recorded as AX rows (ledger rows linked) before the first code commit; …"
- A2 "Restore, prepare and `reset()` never run the diffuse solve synchronously; …"
- A3 "The real-time path adopts each solved snapshot by atomic swap with an AQ4 crossfade, …"
- A4 "The interim level is never silence and never the AX16 level in the cases of condition 5 …"
- A5 "Offline renders, bounces and `render_cli` wait for the final solve …"
- A6 "W_max re-derived under (C) from the background budget (condition 3), pinned, …"
- A7 "If E_b is saved in state: the state-version AX applied, …"
- A8 "E_b bit-identical between modes and ears (AX44); allocation tracker, TSan …"
- A9 "The Phase 12 (ii) preset check re-run under the new W_max and reported, …"

## 1. Sub-phase table

| id | title | lead subject matter (seat, row words) | size | depends on | ships | owns (automated) |
|---|---|---|---|---|---|---|
| 07c-1 | Diffuse solve off the synchronous paths | Seat 5 Deadline keeper — "anything on or beside the audio thread: real-time safety; lock-free hand-off; threading topology; host conformance (pluginval, auval, state, …); offline equals real-time" | M | 05h `done`, 07 `done` | restore, prepare and `reset()` no longer run the diffuse solve; the real-time path adopts each solved snapshot by atomic swap with an AQ4 crossfade, starting from the interim level; offline waits and stays bit-identical; the restore gate re-scoped; W_max still at (A) | A1, A2, A3, A4, A5, A7, A8 |
| 07c-2 | W_max re-derived under (C), one golden round | Seat 2 Engine architect — "simulator compute and recompute time" (the estimator's work limit from the C++ cost and the background budget) | S | 07c-1 `done` (and, through it, 05h, 07) | W_max raised from the (A) restore budget to the (C) background budget, pinned and equal on the three OSes; goldens updated once; Seat 1's "now" 2 (capped-class SE, §0) repaid; Phase 12 (ii) re-run | A6, A9 |

Why two, not one or three:
- The phase has two subject matters that deserve their own attention: the threading/host move (Seat 5, the
  bulk of the work and of the contractor focus) and the output change of raising W_max (an estimator-budget
  derivation plus a cross-platform golden round, the step that actually repays the capped-class SE).
- 07c-2 is S, but it is distinct and risky: it is the phase's only output change (one golden round on three
  OSes, §6 row) and the place where the provisional-to-final step first becomes large, so it is not merged
  back.
- A three-way cut with the decisions (D-C1–D-C3, R1–R3) as their own sub-phase was rejected: that sub-phase
  would ship no build, and A1 alone is a bookkeeping check; the decisions are inputs to 07c-1's design
  (interim level, saved E_b) and A1 requires them before the first code commit, which is 07c-1's.
- The order is forced, not chosen: W_max cannot be raised while the solve still runs inside the synchronous
  restore, because (A) W_max is sized to the restore watchdog (§0; AX41). 07c-2 cannot precede 07c-1.

Each sub-phase leaves `main` green on its own: after 07c-1 the async move works with W_max unchanged (no golden
change); after 07c-2 only W_max and the goldens change, and 07c-1's tests (A2–A5, A7, A8) keep running in CI.

## 2. Order and rationale

1. **07c-1 first.** It retires the threading risk (the restore watchdog, no real-time wait, offline
   determinism) and holds every decision of §4, so A1's "before the first code commit" keeps its literal
   meaning (the first code commit of the phase is 07c-1's). The interim-level rule (condition 5, A4) and the
   saved E_b (D-C2, D-C3, A7) are part of the move: once the solve is asynchronous, the real-time path needs
   an interim level from the first restore, so they cannot wait for 07c-2.
2. **07c-2 second.** It re-derives W_max (condition 3) and makes the one golden round of condition 1 / T1.
   A4's test (including "the provisional-to-final step stays within D-C1's ruling") is owned by 07c-1 and
   stays in CI, so the W_max raise is checked against D-C1 by that test without the criterion being assigned
   twice.

Elements the session brief may count as decisions (G1):

- **CHOICE 07c-c1 — beta prerequisite and Raise §2.1 across two sub-phases.** Phase 13's beta depends on
  "07c `done`" (BUILD_PLAN §0 row 07c; phase-13 header and scope 13). Options: (a) the dependency means the
  umbrella, i.e. both 07c-1 and 07c-2 (G3's default reading), and the Raise item is carried by the umbrella
  and raised by the 07c-2 session; (b) only 07c-1 is a beta prerequisite, and 07c-2's W_max raise may land
  after release under the versioning fallback. Recommended **(a)**: it changes nothing recorded (§3 T1 ties
  the move and "its W_max raise in one golden round" to before release; a W_max change after release is an
  output change that needs the versioning of condition 1). Why it may be a decision: a cut that places part
  of a recorded beta dependency in a later sub-phase.
- **CHOICE 07c-c2 — which sub-phase comes forward on a restore-gate failure or ahead of Phase 08's golden
  freeze (§3 T2, T3; AX38 4c; phase-08 scope 10; phase-05h scope 10).** Options: (a) the umbrella (07c-1 then
  07c-2), as written — phase-08 scope 10 says "W_max is then re-derived once, under phase-07c, with one golden
  round", and the capped-room SE tolerance lifts only once W_max is raised (07c-2); (b) only 07c-1 (the move
  off the restore path is the remedy AX38 4c names), with 07c-2 following on its own schedule and Phase 08's
  capped-room goldens keeping the SE-derived tolerance. Recommended **(a)**, the reading that changes no
  recorded text. Why it may be a decision: (b) changes which work is retired first and what ships ahead of
  Phase 08's golden freeze.
- **CHOICE 07c-c3 — where D-C1 sits.** D-C1 (Seat 1's ruling on the provisional-to-final step) matters most
  once W_max is raised (07c-2), but A4's second clause and 07c-1's interim level already need it. Options: (a)
  D-C1, D-C2, D-C3 and R1–R3 all in 07c-1, before its first code commit (A1 as written); (b) D-C1 moved to
  07c-2 and A4 split into its two clauses (interim-level clause → 07c-1; step clause → 07c-2). Recommended
  **(a)**: §4 says the decisions are recorded "before any code", and (b) would let 07c-1 ship an interim
  level whose step has no ruling. Why it may be a decision: (b) moves an item across the recorded "decisions
  before implementation" ordering.

Not a decision (recorded for the decider): the sub-phase order (forced, see §1); the sizes (M + S, the
original M; neither crosses the two-session limit; the CLAUDE.md remainder name becomes `07c-<n>b` per G3,
replacing `phase-07d.md` in the size line); L1 assigned to 07c-2 (see coverage note).

## 3. Coverage table

| original item | label | goes to | note |
|---|---|---|---|
| Header: size line (M; "split into `phase-07d.md`") | header | umbrella | becomes per sub-phase `07c-1b` / `07c-2b` (G3) |
| Header: depends on 05h, 07 `done` | header | 07c-1 (shared with umbrella) | 07c-2 depends on 07c-1 |
| Header: must be `done` before Phase 13's beta (or phase-13 scope 13's versioning fallback) | header | umbrella | means both sub-phases (CHOICE 07c-c1) |
| Header: read-first list | header | umbrella (shared) | each sub-phase file cites it; AX41/AQ10 lines most relevant to 07c-2, AQ4/AX5/AX18/AX33/AX38/AX44 and phase-07 to 07c-1 |
| Header: creation note (J1, decider files 47, 51, interrogator 49) | header | umbrella | |
| §0 Why this phase exists | §0 | umbrella | |
| §1 Settled — do not reopen (3 bullets) | §1 | umbrella | governs both |
| §2.1 Raise with Maisara (landing after release without versioning) | §2.1 | umbrella + 07c-2 (shared) | raised by the 07c-2 session (the one whose landing completes the phase) |
| §3 T1 lands before first public release, W_max raise in one golden round; else versioned | §3 | umbrella + 07c-2 (shared) | the golden round is 07c-2's |
| §3 T2 brought ahead of Phase 08's golden freeze (after 05h) | §3 | umbrella | CHOICE 07c-c2 |
| §3 T3 brought forward on any restore-gate failure | §3 | umbrella | CHOICE 07c-c2 |
| §4 D-C1 provisional-to-final step ruling | §4 | 07c-1 | CHOICE 07c-c3 |
| §4 D-C2 interim level and saved E_b (state-version AX if stored) | §4 | 07c-1 | |
| §4 D-C3 solved result in saved state (Seat 8 → Seat 5) | §4 | 07c-1 | |
| §4 R1 blocked `setStateInformation` tolerance | §4 | 07c-1 | |
| §4 R2 hosts without a reliable offline signal | §4 | 07c-1 | |
| §4 R3 host hang dialogs and timeouts (Logic, Live, Cubase, Bitwig) | §4 | 07c-1 | |
| §4 note: researcher-before-D-C ordering is the plan-editor's | §4 | 07c-1 | |
| §5 lead sentence ("The diffuse solve moves off …") | §5 | umbrella | |
| §5 condition 1 Timing | cond. 1 | umbrella + 07c-2 (shared) | same as §3 T1 |
| §5 condition 2 Seam | cond. 2 | 07c-1 | |
| §5 condition 3 W_max re-derived under (C) (incl. AX41/AQ10 update via `/fix-plan`) | cond. 3 | 07c-2 | |
| §5 condition 4 No real-time waiting (swap + AQ4 crossfade, "settling"; ISM never held; phase-10 AX38 (v) cross-reference) | cond. 4 | 07c-1 | |
| §5 condition 5 Interim level (5.1 saved E_b; 5.2 (A)-budget estimate or previous level; never silence / AX16 > 1 dB; step within D-C1) | cond. 5 | 07c-1 | |
| §5 condition 6 Offline | cond. 6 | 07c-1 | |
| §5 condition 7 Gates re-scoped (restore gate without the solve; solve time to staleness records; E_b shared across modes and ears) | cond. 7 | 07c-1 | |
| §5 condition 8, first sentence (Phase 12 (ii) re-run under this phase's W_max) | cond. 8 | 07c-2 | |
| §5 condition 8, second sentence (Phase 08 capped-room goldens' SE tolerance unless 07c lands before freeze) | cond. 8 | 07c-2 | the SE only changes with the W_max raise; see CHOICE 07c-c2 |
| A1 | §6 | 07c-1 | |
| A2 | §6 | 07c-1 | |
| A3 | §6 | 07c-1 | |
| A4 | §6 | 07c-1 | whole criterion; its test stays in CI through 07c-2 (CHOICE 07c-c3 option (b) would split it) |
| A5 | §6 | 07c-1 | |
| A6 | §6 | 07c-2 | |
| A7 | §6 | 07c-1 | |
| A8 | §6 | 07c-1 | |
| A9 | §6 | 07c-2 | |
| L1 load a large-room project: interim level at once, "settling", final level without click or obvious jump | §7 | 07c-2 | under (A) W_max the interim and final levels mostly coincide; the step is audible to judge only after the raise |
| L2 drag a source: early part follows at once, tail level after the drag | §7 | 07c-1 | |
| L3 bounce twice: identical, match playback after settling | §7 | 07c-1 | |
| F1 threading of the moved solve (no real-time wait, no lock on the audio thread, AX38 gate classes after the move) | §8 | 07c-1 | |
| F2 the atomic swap and crossfade | §8 | 07c-1 | |
| F3 the interim-level rule | §8 | 07c-1 | |
| F4 offline determinism | §8 | 07c-1 | |
| F5 the saved-state format if E_b is stored | §8 | 07c-1 | |
| F6 the W_max re-derivation from the background budget | §8 | 07c-2 | |
| §9 Out of scope (estimator AX39–AX44; both-near fallback B15; kernel cache AX38 (ii); n\*_max Q2b (i)) | §9 | umbrella | governs both |
| §10 DoD: §6 all checked with CI evidence | §10 | umbrella (shared) | each sub-phase: its own criteria |
| §10 DoD: §0 row 07c `done` before Phase 13's beta | §10 | umbrella | umbrella `done` when both are |
| §10 DoD: PR with listening checklist, contractor focus, AX/ledger links, Raise item if it applies | §10 | umbrella (shared) | each sub-phase PR its own share; Raise item with 07c-2 |
| Risks | — | — | the file has no risks section; §0's capped-class SE is the rationale (umbrella) |


## 4. References

Grep of the repo for `07c` / `Q2a (C)` / phase-07c condition numbers, excluding `docs/corpus/`,
`docs/review/`, `docs/sessions/` (hash strings in requirements/manifest files matched `07c` and are ignored).

| file:line | reference | → new sub-phase |
|---|---|---|
| docs/BUILD_PLAN.md:32 | §0 row 07c (depends 05h, 07; before Phase 13's beta) | umbrella (row becomes `split (07c-1…07c-2)`; new rows 07c-1, 07c-2) |
| docs/BUILD_PLAN.md:95 | AQ10: gate failure remedied by bringing (C) (phase-07c) forward; (C) scheduled before first public release | umbrella (CHOICE 07c-c2) |
| docs/BUILD_PLAN.md:138 | AX38: gate failure remedied by bringing (C) (phase-07c) forward | umbrella (CHOICE 07c-c2); the move itself is 07c-1 |
| docs/BUILD_PLAN.md:141 | AX41: W_max (C) scheduled in phase-07c; re-derived once under (C) from the background budget; phase-07c moves the solve off the synchronous paths | W_max re-derivation → 07c-2; the move → 07c-1 |
| docs/BUILD_PLAN.md:257 | phase-05h out of scope: Q2a (C), the async restore (phase 07c) | umbrella |
| docs/BUILD_PLAN.md:289–292 | §4 entry for Phase 07c (goal, scope, decisions first, dependencies) | umbrella (decisions first and conditions 2, 4–7 → 07c-1; condition 3, Phase 12 re-run, Phase 08 tolerance → 07c-2) |
| docs/BUILD_PLAN.md:349 | phase-13 entry: phase-07c a beta prerequisite | umbrella (CHOICE 07c-c1) |
| docs/BUILD_PLAN.md:443, 446, 447, 449 | §6 change-log rows naming phase-07c | historical record, not remapped |
| docs/phases/phase-05h.md:75–77 | Q2a (C) is its own phase, phase-07c | umbrella |
| docs/phases/phase-05h.md:120 | 20 % trigger: bring (C) (phase-07c) forward | umbrella (CHOICE 07c-c2) |
| docs/phases/phase-05h.md:170–171 | solve seam / phase-07c condition 2 | 07c-1 |
| docs/phases/phase-05h.md:225–227 | heaviest-mode failure: phase-07c lands before binaural goldens are frozen | umbrella (CHOICE 07c-c2) |
| docs/phases/phase-05h.md:228–229 | capped-room tolerance unless phase-07c has landed (phase-07c condition 8) | 07c-2 |
| docs/phases/phase-05h.md:265 | remedy is bringing phase-07c forward | umbrella (CHOICE 07c-c2) |
| docs/phases/phase-05h.md:316 | out of scope: Q2a (C), phase-07c | umbrella |
| docs/phases/phase-05b2.md:409–411 | note: Q2a (C) now its own phase, phase-07c (kept as record) | umbrella (historical note) |
| docs/phases/phase-08.md:205–207 | heaviest-mode gate failure: phase-07c brought forward; W_max re-derived once under phase-07c with one golden round | umbrella (CHOICE 07c-c2) |
| docs/phases/phase-08.md:208–209 | capped-room goldens' SE tolerance unless phase-07c has landed | 07c-2 |
| docs/phases/phase-08.md:272 | criterion: SE-derived tolerance unless phase-07c has landed | 07c-2 |
| docs/phases/phase-10.md:58–59 | split update designed with phase-07c condition 4 | 07c-1 |
| docs/phases/phase-12.md:49 | preset check re-run under phase-07c's W_max once landed | 07c-2 |
| docs/phases/phase-13.md:3 | depends on 07c (`done`, or scope 13's versioning fallback) | umbrella (CHOICE 07c-c1) |
| docs/phases/phase-13.md:18–20 | Raise item 4: phase-07c not landed | umbrella + 07c-2 (CHOICE 07c-c1) |
| docs/phases/phase-13.md:115 | W_max re-derived once under phase-07c | 07c-2 |
| docs/phases/phase-13.md:116–120 | Q2a (C) is phase-07c, a prerequisite for the beta | umbrella (CHOICE 07c-c1) |
| docs/phases/phase-07c.md:129, 151 | self-references (A9 "07c's W_max"; DoD "§0 row 07c") | 07c-2 (line 129); umbrella (line 151) |

No reference in `src/`, `tests/`, `tools/` or `.claude/` (code comments or skill files) names phase-07c.
