# Decider, decision round 2 — phase split (2026-11-10)

Saved by the orchestrator from the decider's report (instructions and tables verbatim; prose lightly condensed).
Re-answers D-PS1–4 and FM-1 from the existing seat positions, after `4-interrogator-decision.md`. The change since
round 1 is in Phase 13: C2's AX22 i₀ sentence is in force, so 13-1 splits and Phase 13 has five sub-phases.

## Answers to the interrogator

**Q1. C2's i₀ sentence and Seat 3's split.** The sentence is conditional, but the condition is met: AX22 records
'cap limits accuracy', measured up to 39.7 jnd (BUILD_PLAN line 122; §0 line 21; §6 line 410). So "Re-derive the AX22
i₀ after optimisation" binds Phase 13: a real check. With S13 (W_max and n*_max re-checked on the release machines;
any change "an output change (golden round, §6 row) and must be fixed before the first release") and C2's N_cap
sentence, it deserves a session. Round 1's step 4 falls; Seat 3's split is adopted. Seat 2's "not splittable under
G2" premise (C2 indivisible) is gone after the interrogator's ruling. No seat rated the five-way variant; Seats 2, 3,
5, 7 read from their conditions. If the interrogator rejects Seat 2's (rc) cell, Seat 2 alone is re-convened.

New Phase 13 sub-phases, order 13-1 → 13-2 → 13-3 → 13-4 → 13-5; each carries header H in full; C1 shared via the
umbrella.

| id | title | lead (convening-table row) | scope | owns | depends on |
|---|---|---|---|---|---|
| 13-1 | Performance and per-instance CPU | Seat 3: "per-instance CPU" | S1 (incl. memory per instance and budget); S10 (Q1/Q2 handed to Seat 1) | C2 sentence 1: "Benchmarks: AQ10 met … beyond −100 dB." | H |
| 13-2 | Engine limits after optimisation | Seat 2: "simulator compute and recompute time" | S13 | C2 sentence 2 (N_cap rule) and sentence 3 (i₀), verbatim | 13-1 |
| 13-3 | Platforms | Seat 5 | S2, S3.6, S8, S9 | C3 cross-architecture clause | 13-2 |
| 13-4 | Host robustness and conformance | Seat 5 | S3.1–S3.5, S11, S12 | C3 "Robustness tests above pass"; C4 | 13-3 |
| 13-5 | Release, licences, identity, beta | Seat 5 | S4–S7 | C5 | 13-1 to 13-4 |

Remainders (G3): `13-1b` (optimisation, non-uniform partitioning, S9 remedy); `13-5b` (notarization).

**Q2. FM-1.** Posed as "must Phase 11 be split?", the answer is Yes (corrected below). NFR-4 withdrawn as a
discriminator ("VST3 and AU on macOS and Windows" says nothing about order).

**Q3.** Each decision now has a "Decided for Maisara" line with every surviving option against the PRD ids.

**Q4. D-PS1.** Yes: (i) on 08-2 verbatim from phase-05b2 line 401, Seat 4's restatement beside it as a note; the
umbrella carries Seat 5's trigger note.

**Q5. The one-subject test (criterion ownership).**
1. Every automated criterion, or criterion clause, a sub-phase owns falls under its lead seat's convening-table row.
2. Exemptions: shared regression gates ("all earlier tests pass", pluginval re-run on unchanged conformance, e.g.
   08-3, 09 A8); a criterion whose own sub-phase would be too small to deserve a session (09 A7). Both ride under the
   lead as named hand-offs, as do scope items with no criterion.
3. A phase failing the test is split along its criteria wherever each part owns a binding criterion and deserves a
   session.

Applied: 11 (c) fails (A1–A3 Seat 6, A4–A7 Seat 5, each M per map-11); 11 (b) fails (first half owns A1 and
A4/A6/A7); 11 (a)'s 11-1 passes (A4–A7 all Seat 5; S1e, S1f, S6, S7 own no criterion, ride under Seat 6's condition
(ii)); round 1's 13-1 fails (C2 sentence 1 Seat 3, sentence 3 Seat 2, the latter binding); new 13-1 passes.

---

## D-PS1 · 08-c1 · stands, corrected

| option | S2 | S3 | S4 | S5 | S7 |
|---|---|---|---|---|---|
| (a) | 0/1 | 0/1 | 1/1 | 1/1 | 1/1 |
| (b) as worded | 2/2 | 1/2 | 1/2 | 0/1 | 0/1 |
| (b′) | 0/0 | 0/1 (rc) | 0/1 | 0/1 (rc) | 0/1 (rc) |
| (c) | out (new dependency reading) | | | | |

Working: max (b′) 1 vs (b) 2; sum (b′) 4 vs (a) 8.

**Plan-editor instructions:**
1. The umbrella and every 08-n file carry the header's dependency line verbatim.
2. 08-1: "08-1 reads no tail data (no room quantity)."
3. 08-2: "(i) E_b and t_mix,e read only via `TailMatch`" (verbatim); Note (Seat 4): "t_mix,e (handover and image-list
   bound) read only from the same `planEmitter`/`TailMatch` result as the omni build."; and "08-2 reads t_mix,e (the
   AX20 list bound and the handover) and the AX22 fallback, through the shared `planEmitter`/`TailMatch` path, and no
   E_b; its anechoic checks (AC3, AC7, AC10) read none. 05h leaves these unchanged (AX37 (5.2); phase-05h scope
   'Mixing-time rule: unchanged')."
4. 08-3: (i), (ii), (iv), verbatim.
5. 08-4: (iii), verbatim.
6. 08-4 and the umbrella: "In this split, 'Phase 08 went first' in phase-05h scope 10 (goldens, W1/W2, item 8) means
   08-4 ran before 05h was `done`." · "phase-05h line 286's addition (outside AX37 (5.3)) applies if 08-3 ran before
   05h was `done`." · "The binaural goldens that (iii) re-renders include 08-2's early part; 08-2 freezes none."
7. phase-05h.md not edited (follow-up).

Debt register: unchanged from round 1 (Seats 3, 4, 5, 7).

**Decided for Maisara:** 08's four sub-phases carry the 05h exception verbatim; each condition attached where it bites.
Acceptance check: FR-SIM-3 ("binaural … and stereo speakers"), NFR-1 ("match impulse responses … pass listening
tests"); no hard constraint broken. (a) serves FR-SIM-3, leaves where each condition binds to the executing session;
neutral on NFR-1. (b) as worded serves FR-SIM-3, strains NFR-1 (false "reads no t_mix,e" invites an omni/binaural seam
AC6 fails). (b′) serves FR-SIM-3 and NFR-1; no PRD id points elsewhere. Seat 4 gives most; gets a clean 05h merge
check.

## D-PS2 · 08-c3 · stands

Map and instructions unchanged from round 1 (`3-decider-decision.md` D-PS2 steps 1–6). Max 1, sum 10.

**Decided for Maisara:** grouping decided on 08-4's benchmark; if it lands, four listening items re-heard before the
freeze. Acceptance check: NFR-1 ("pass listening tests"); NFR-2 ("heavy CPU … acceptable when they buy accuracy");
FR-SIM-3; no hard constraint broken. (a) strains NFR-2 (fixes the approximation rule before the measurement). (b)
strains NFR-1 (verdicts on a chain that may not ship). (b+) serves NFR-1, NFR-2, FR-SIM-3. Seat 1 and Maisara give
most (a possible re-listen); get verdicts on the chain that ships.

## D-PS3 · 11-c1 · stands, corrected

| option | S5 | S6 | S7 |
|---|---|---|---|
| (a) | 1/0 | 1/1 with (i) | 0/1 |
| (b) | 2/2 (1/1 with A5 moved) | 0/1 | 1/1 |
| (c) | 0/1 | 0/0 | 0/1 |

Working: step 1 excludes (b) and (c) under her 2026-11-10 instruction by the Q5 test; sizes from map-11 (each M), not
the seats. (c) would win on sum; excluded at bounds.

**Plan-editor instructions:** unchanged — order 11-1 → 11-2 → 11-3; 11-1 carries Seat 6's (i) (provisional layout,
canvas reserved as the largest region) and (ii) (references beside S1e), verbatim as in round 1.

Debt register: unchanged (Seats 6, 7).

**Decided for Maisara:** Phase 11 split shell-first; acceptance check in FM-1. Seat 6 gives most; gets a reserved
canvas region and a layout provisional until 11-2.

## D-PS4 · 13-c1 · revised (five-way)

| option | S1 | S2 | S3 | S5 | S7 |
|---|---|---|---|---|---|
| (a+5) | 1/0 | 0/0 (rc: i₀ and S13 output changes precede the cross-architecture residual) | 1/1 (rc) | 1/1 (rc) | 0/1 (rc, a′) |

Working: (a+) four-way and (b) out at bounds (their 13-1 fails Q5); (c) out at the veto step (Seat 5 later 3). (a+5)
the only survivor; max 1, sum 6.

**Plan-editor instructions:**
1. The five sub-phases and order as in Q1.
2. 13-3 runs S9 first, before C3's residual and S8 are recorded. A miss opens `13-1b`; 13-3's records are taken after
   `13-1b` lands.
3. If `13-1b` changes rebuild time, 13-2's i₀ sentence re-runs.
4. K1, K2, K3 "umbrella (shared)", read by 13-1; risk text verbatim.
5. Raise items: all four carried by 13-1 (first message) and by 13-5 ("before the beta decision").
6. S13's "release machines" and S9 need Apple-silicon hardware; Maisara provides it (follow-up).

| seat | commits | undo cost | evidence | repaid when |
|---|---|---|---|---|
| S3 | an S9 miss reopens `13-1b` after 13-2 | re-run 13-2's i₀ sentence if rebuild time moves | 13-3, S9 | S9 passes, or `13-1b` lands before 13-3's records |
| S5 | the same | universal binary rebuilt | 13-3 | 13-3 `done` |
| S7 | K1–K3 lead times [Hyp] | beta slips or `signing pending secrets` | 13-1 | enrolment started |
| S1 | S10 answered in 13-1 | none later | 13-1 | Q1/Q2 answered with method |

Strongest objection: Seat 2's (rc) cell. Confidence medium. Reversal: Seat 2's (rc) rejected (re-convene Seat 2), or
an S9 miss recurs after `13-1b`.

**Decided for Maisara:** Phase 13 runs in five parts — performance, engine limits, platforms, hosts, release;
real-hardware timing first in platforms; signing logistics visible from the first session. Acceptance check: NFR-2,
NFR-4, NFR-6 ("restores the scene and its render exactly, on any machine"), PRD line 174 ("no fixed v1 deadline"); no
hard constraint broken. (a+5) serves NFR-6 (every output change, 13-1 and 13-2, precedes the cross-architecture
residual); neutral on NFR-2, NFR-4; breaches no date. For completeness: (a+) four-way and (b) same PRD standing, out
only under her instruction; (c) strains NFR-6 (residual on code still changing). Seat 3 gives most; gets its own lead
in 13-1 with `13-1b` before the platform records.

## FOR MAISARA FM-1 (corrected)

Question: must Phase 11 be split, rather than kept whole?

Answer: Yes. Phase 11 owns criteria under two seats' rows that each deserve a session (Seat 5: A4–A7; Seat 6: A1–A3;
map-11 sizes M each). Her instruction calls for the split. Split shell-first under D-PS3, canvas region reserved,
layout provisional until 11-2.

Rests on: her decision of 2026-11-10 ("smallest buildable sub phases that ship value while keeping the session's
attention focused on one subject matter that deserves it"); PRD Overview (line 9); FR-3D-5, FR-3D-8, NFR-4, line 174.
None of the PRD ids separates the options, so her recorded instruction settles it (not case (a)). Phase 09 stayed
whole because its only cut was too small; Phase 11's are not.

- (a): Overview — canvas one sub-phase later, no user receives it before 13-5; FR-3D-5, FR-3D-8 hold (positions stay
  host parameters throughout); NFR-4 neutral; no date breached (line 174); serves her instruction. Strain: 11-1 carries
  user-facing readouts under a Seat 5 lead, exempt as criterion-less hand-offs (Q5, condition (ii)).
- (b): Overview, FR-3D-5, FR-3D-8, NFR-4, line 174 neutral as in (a); strains her instruction (both halves mix two
  rows' criteria).
- (c): Overview and FR-3D-5 — editor laid out once around the canvas; FR-3D-8, NFR-4, line 174 neutral; strains her
  instruction (two subjects in one session).

Veto trigger: reading the Overview ("build or pick it visually") as making the canvas the organising surface, so a
shell laid out before the canvas risks the core experience. Amends none of her recorded decisions.

## Corrections for the plan-editor (final)
1. 07c: §2.1 Raise in 07c-1 and 07c-2.
2. 12: drop 12-1's AC2 share; 12-1 owns AC5 alone; AC2 whole in 12-2.
3. 13-c4: all four Raise items in 13-1 and 13-5 (beta sub-phase is now 13-5).
4. Ids in the debt registers (08-4, 11-2, 13-1b, 13-3) land with exactly those names.

## Summary
| id | decision | state | worst cell | sum | confidence | reversal |
|---|---|---|---|---|---|---|
| D-PS1 | (b′) | stands, corrected | 1 | 4 | high | 05h diff touches the t_mix,e path |
| D-PS2 | (b+) | stands | 1 | 10 | medium | 08-4 benchmark |
| D-PS3 | (a) + (i), (ii) | stands, corrected | 1 | 4 | medium | FM-1 vetoed |
| D-PS4 | (a+5), five sub-phases | revised | 1 | 6 | medium | Seat 2 (rc) rejected; S9 miss after 13-1b |
| FM-1 | split, Yes | for Maisara | — | — | medium | her veto |

NEEDS MAISARA: none.
