# Decider, decision round — phase split: 08-c1, 08-c3, 11-c1, 13-c1 (2026-11-10)

Saved by the orchestrator from the decider's report (instructions and tables verbatim; prose lightly condensed).

All four decided; none RESEARCH NEEDED; none to Maisara (no surviving option carries a 3; no case (a)/(b)/(c)).
Cells are each seat's own `now/later` from `2-seat1.md` … `2-seat7.md`; "—" = not convened (0/0); "(rc)" = read
from the seat's conditions of acceptance.

**K1–K3 lead time (Seat 7 [Hyp]) — not load-bearing for 13-c1.** With K1–K3 marked "umbrella (shared)" Seat 7 rates
1; no other seat rates the marking; plain (a) carries a later 2 from Seats 3 and 5 anyway; the composed variant wins
whatever the lead times. PRD: "there is no fixed v1 deadline" (Team, timeline). The lead time decides when Maisara
starts enrolment (a person's action), a follow-up for 13-1's session.

---

## D-PS1 · 08-c1: where the AX37 (5.3) conditions attach

Knowledge: K1 08-2 reads t_mix,e (AX20 list bound, handover) and the AX22 fallback via `planEmitter`/`TailMatch`, no
E_b (`src/sim/Engine.cpp` 120–149, 246; Seats 2, 3, 4 independently). K2 05h leaves them unchanged (AX37 (5.2);
phase-05h "Mixing-time rule: unchanged"). K3 08-1 reads no room quantity (Seats 2, 4).

| option | S2 | S3 | S4 | S5 | S7 |
|---|---|---|---|---|---|
| (a) full line on every sub-phase | 0/1 | 0/1 | 1/1 | 1/1 | 1/1 |
| (b) as worded | 2/2 | 1/2 | 1/2 | 0/1 | 0/1 |
| (b′) composed | 0/0 | 0/1 (rc 6a) | 0/1 | 0/1 (rc) | 0/1 (rc) |
| (c) drop 05h from 08-1/08-2 | 1/2 | 1/2 | 1/2 | 1/2 | 1/2 |

Working: (c) out at bounds (a new reading of a recorded dependency; Seats 5, 7). No 3. Highest: (a) 1, (b) 2, (b′) 1.
Sum: (a) 8, (b′) 4 → **(b′)**.

**DECISION (plan-editor instructions):**
1. The umbrella and every 08-n file carry the header's dependency line verbatim. AX37 (5.3) (i)–(iv) unchanged.
2. Add to 08-1: "08-1 reads no tail data (no room quantity)."
3. Add to 08-2: "08-2 reads t_mix,e (the AX20 list bound and the handover) and the AX22 fallback, through the shared
   `planEmitter`/`TailMatch` path, and no E_b; its anechoic checks (AC3, AC7, AC10) read none. 05h leaves these
   unchanged (AX37 (5.2); phase-05h scope 'Mixing-time rule: unchanged')."
4. Attach condition (i) to 08-2 and 08-3. On 08-2 word it: "t_mix,e (handover and image-list bound) read only from
   the same `planEmitter`/`TailMatch` result as the omni build."
5. Attach (ii) and (iv) to 08-3.
6. Attach (iii) to 08-4, with notes: "In this split, 'Phase 08 went first' in phase-05h scope 10 (goldens, W1/W2,
   item 8) means 08-4 ran before 05h was `done`." · "(iv)'s re-listen (phase-05h line 286) applies if 08-3 ran before
   05h was `done`." · "The binaural goldens that (iii) re-renders include 08-2's early part; 08-2 freezes none."
7. phase-05h.md is not edited (out of scope); aligning its wording is a follow-up.

Load-bearing: D1-L1 = K1 (code, three seats); D1-L2 = K2; D1-L3 (c) is a new reading (brief G1/Constraints).

| seat | commits later phases to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| S3 | 08-2 never computes its own bound | rework of 08-2's early path | 05h golden re-render | AC6 green on capped rooms after 05h |
| S4 | 08-2 builder reuses the omni `EmitterPlan` | one refactor | 05h merge, if its diff touches `mixingTime`, `needsIsmFallback` or the AX20 bound | 05h `done` with those unchanged |
| S5 | trigger rests on the 08-4/08-3 timing reading | one wording line | 08-4 vs 05h order | 05h `done` |
| S7 | 08 before 05h costs a re-render | already booked | 05h scope 10 | 05h `done` |

Strongest objection: Seat 4's later 1 (if 05h moves the AX20 bound, 08-2's statement becomes false; the 05h merge and
AC6/AC11 catch it). Confidence high. Reversal: a 05h diff touching `mixingTime`, `needsIsmFallback` or the AX20 bound.

## D-PS2 · 08-c3: 2° grouping rule moved to 08-4

| option | S1 | S3 | S4 | S5 | S7 |
|---|---|---|---|---|---|
| (a) S5a whole in 08-2 | 1/1 | 1/2 | 1/2 | 1/2 | 1/1 |
| (b) as drafted | 1/2 | 1/1 | 1/1 | 1/1 | 1/1 |
| (b+) composed | 1/1 | 1/1 | 1/1 | 1/1 (rc) | 1/1 (rc) |

Working: no 3. Highest: (a) 2, (b) 2, (b+) 1 → **(b+)** (Seat 1's condition, Seat 5's in-08-4 order, Seat 4's PR
note; raises no cell). Seat 3's optional extras (08-3 build-time record, moving-source render) not adopted: they add
checks and lower no cell; movement stays covered by Phase 10 AC1 (both output modes).

**DECISION:**
1. 08-2 gets S5a's first sentence and "The direct path and orders 1–3 are never grouped."
2. 08-4 gets "No 2° grouping until … document the approximation.", with R3 and CF6.
3. Order inside 08-4, written in the file: benchmark on the full BRIR → grouping decision → S8, S9, S10 → golden
   freeze; timing recorded on the post-grouping build only.
4. 08-3 marks its verdicts on L1, L3, L4, L5 "provisional if 08-4 introduces grouping".
5. 08-4 carries: "If grouping is introduced: AC3, AC5, AC6, AC8 re-run on grouped output, and L1, L3, L4, L5 (wording
   unchanged) re-listened on grouped output before the goldens freeze (same fixed set, same forced-choice form, 08-3
   renders beside the new ones); the PR states whether grouping was introduced; the provisional mark lapses if it was
   not."
6. Not an added item: in the unsplit phase these items were heard after the grouping decision; this restores that.

Load-bearing: D2-L1 grouping touches only reflections above order 3 (phase-08 S5a), so L2 and L6 are unaffected
(Seat 1's inference); D2-L2 S10 requires the gate before the freeze (08-c2).

| seat | commits | undo cost | evidence | repaid when |
|---|---|---|---|---|
| S1 | possible re-listen | Maisara's hours | 08-4 benchmark | grouping not introduced, or re-listen passes |
| S3 | AC6 is the exposure | one CI round | 08-4 | AC6 green on the grouped build |
| S4 | L4/L5 could flip | re-listen | 08-4 | as S1 |
| S5 | binaural unbenchmarked 08-3→08-4 | none (no beta before 13-4) | 08-4 | 08-4 `done` |
| S7 | Maisara's hours | as S1 | 08-4 | as S1 |

Strongest objection: Seat 4's premortem (grouping colours the hall, first heard at 13-4) — answered by the re-listen
before the freeze. Confidence medium (audibility [Hyp]). Reversal: 08-4's benchmark result.

## D-PS3 · 11-c1: order of Phase 11

| option | S5 | S6 | S7 |
|---|---|---|---|
| (a) shell first | 1/0 | 1/1 with (i), 2 without | 0/1 |
| (b) canvas first, two-way | 2/2 (1/1 with A5 moved) | 0/1 | 1/1 |
| (c) whole | 0/1 | 0/0 | 0/1 |

Working: bounds — (c) and (b) out under her 2026-11-10 instruction (FM-1): (c) keeps two subjects that each deserve
an M session (Seat 5: editor lifecycle, A4–A7, R2; Seat 6: canvas), unlike 09 whose only cut was too small; (b)'s
halves both mix Seat 5's host-conformance criteria with Seat 6's canvas. Survivor **(a)** with Seat 6's (i), (ii):
highest 1, sum 4. (c) would have won on sum (2); excluded at bounds, not outscored.

**DECISION:**
1. Order 11-1 → 11-2 → 11-3.
2. 11-1's file states: "its aspect ratio and region layout are provisional, set in 11-2 once the two scale views
   exist; 11-1 reserves the canvas region as the largest region." S3 wording unchanged.
3. Beside S1e, 11-1 cites the phase-08 line 302 and phase-09 line 75 hand-offs and the §6 "Phase 11 tooltip note" row
   (D1) — a reference, not an item.

| seat | commits | undo cost | evidence | repaid when |
|---|---|---|---|---|
| S6 | layout set before the canvas exists | a constant + re-layout; A4, A6 re-run | 11-2's L1 | layout confirmed in 11-2 |
| S7 | canvas ~1 session later | none for producers before 13-4 | 11-2 | 11-2 `done` |

Strongest objection: Seat 6 prefers (c) at 0/0; overturned only if FM-1 falls (then (c) wins on sum). Confidence
medium. Reversal: FM-1 vetoed, or PRD MISREAD on FM-1.

## D-PS4 · 13-c1: order of Phase 13 and S9's placement

| option | S1 | S2 | S3 | S5 | S7 |
|---|---|---|---|---|---|
| (a) as mapped | 0/0 | 0/0 | 1/2 | 1/2 | 0/2 |
| (a+) composed | 0/0 | 0/0 | 1/1 (rc) | 1/1 (rc) | 0/1 (rc, a′) |
| (b) S9 in 13-1 | 1/0 | 1/1 | 1/1 | 1/1 | 0/2 (0/1 with K1–K3 marked, rc) |
| (c) 13-2 before 13-1 | 0/1 | 1/2 | 1/2 | 2/3 | 0/2 |

Seat 1's "S10 in 13-1" 1/— applies to (a) and (b) alike. Working: (c) out (Seat 5 later 3). Highest: (a) 2, (a+) 1,
(b)+K 1. Sum: (a+) 5, (b)+K 8 → **(a+)**.

**DECISION:**
1. Order 13-1 → 13-2 → 13-3 → 13-4.
2. 13-2 runs S9 first, before C3's cross-architecture residual and S8 are recorded. "A miss opens `13-1b`; 13-2's
   records are taken after `13-1b` lands." (Meets Seat 3's condition: 13-1b before 13-2's cross-architecture job.)
3. In the coverage table K1, K2, K3 become "umbrella (shared)", read by 13-1's session; risk text verbatim; no Raise
   item added.
4. Lead of 13-1 (correction to the map, read from the convening table): Seat 3 ("per-instance CPU": S1, C2's "AQ10
   met", partitioned convolution, S10); Seat 2 hand-offs named in the file (S13, C2's AX22 i₀ clause, rebuild time).
   Not split further (under G2, S13 and S10 own no criterion except C2).

| seat | commits | undo cost | evidence | repaid when |
|---|---|---|---|---|
| S3 | S9 miss → 13-1b changes summation order | 13-1b ahead of the residual | S9 in 13-2 | S9 passes, or 13-1b lands before the C3 records |
| S5 | the same | universal binary rebuilt | 13-2 | 13-2 `done` |
| S7 | K1–K3 lead times [Hyp] | beta slips or `signing pending secrets` | 13-1 | enrolment started by Maisara |

Strongest objection: Seat 3 prefers (b) (measurement and remedy in one session); outscored on sum (8 vs 5), and needs
Apple-silicon hardware in 13-1 anyway. Confidence high. Reversal: an S9 miss recurring after 13-1b.

## FOR MAISARA FM-1 — does "one subject matter" rule out keeping Phase 11 whole?

Answer: No. Phase 11 holds two subject matters that each deserve a session (Seat 5: editor host conformance, A4–A7,
R2; Seat 6: placement canvas and controls, A1–A3, R1). Her instruction calls for a split wherever buildable,
value-shipping, one-subject cuts exist. Split shell-first under D-PS3, canvas region reserved and layout provisional
until 11-2.

Rests on: her decision of 2026-11-10 ("smallest buildable sub phases that ship value while keeping the session's
attention focused on one subject matter that deserves it"); PRD Overview (the user must "build or pick it visually,
and place the listener and sound sources"); FR-3D-5, FR-3D-8, NFR-4; "There is no fixed v1 deadline."

Per option: (a) serves her instruction and NFR-4 (Windows DPI, pluginval with the editor retired first), strains the
vision only in ordering. (b) strains her instruction (both halves mix subjects). (c) serves FR-3D-5 laid out once,
strains "smallest … one subject". What would make her veto: reading the canvas as the product, so a shell-first
layout is a design risk and an M phase should not grow to three sessions. Amends none of her recorded decisions.

## Corrections from the convening round, confirmed
1. 07c Raise: §2.1 carried in both 07c-1 and 07c-2; each raises it in its first message.
2. 12 AC2: 12-1 owns "AC2, material-ID part; whole in 12-2" — the AC2 sentence verbatim with "every preset name" and
   "the string `preset`" omitted. If the interrogator rejects it as a clause split, drop it; 12-1 still owns AC5.
3. 13-c4: 13-1 and 13-4 each carry all four Raise items (13-1's first message; 13-4's "before the beta decision").

Follow-ups (not this session): phase-05h scope 10 and line 286 wording aligned to D-PS1 step 6; record 05h as a
dependency of 11-3 (11-c3); Apple-silicon hardware for 13-1/13-2 and starting K1–K3 enrolment (Maisara's actions);
review-skill drift (maps 08, 10).

## Summary
| id | decision | highest | sum | confidence | PRD bound | reversal |
|---|---|---|---|---|---|---|
| D-PS1 08-c1 | (b′) | 1 | 4 | high | brief G1, AX37 (5.3) | 05h diff touches the t_mix,e path |
| D-PS2 08-c3 | (b+) | 1 | 10 | medium | FR-SIM-3 | 08-4 benchmark |
| D-PS3 11-c1 | (a) + (i), (ii) | 1 | 4 | medium | her 2026-11-10 instruction, FM-1 | FM-1 vetoed |
| D-PS4 13-c1 | (a+) | 1 | 5 | high | NFR-4, no deadline | S9 miss after 13-1b |
| FM-1 | 11 split, not whole | — | — | medium | Overview, FR-3D-5/8, NFR-4 | her veto |

NEEDS MAISARA: none. Corpus basis: none needed.
