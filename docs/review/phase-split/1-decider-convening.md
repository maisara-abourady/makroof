# Decider, convening round — phase split 07c–13 (2026-11-10)

Saved by the orchestrator from the decider's report (verbatim content, light formatting).

Corpus: not needed. These are plan-structure choices; no acoustic fact is load-bearing. Product sources: PRD,
BUILD_PLAN §0/§2, the phase files, the session brief G1–G4.

## PRD digest
- Hard bounds: her words (2026-11-10, "smallest buildable sub phases that ship value… one subject matter"). Brief
  rules G1–G4: reallocation only, nothing changed in substance, no dependency moved or added, value rule G2.
- Recorded dependencies carry over unchanged: AX37 (5.3) conditions (i)–(iv), 07c's timing, and 13 on 00–12.
- NFR-8 is untouched by every map. The PRD says nothing on session counts, so her 2026-11-10 instruction governs.

## Ruling on G1's size test (08-c5, 11-c2, 13-c3)
CLAUDE.md applies the two-session limit to the unit a session executes; after the split, that unit is the
sub-phase. The umbrella's total session count rising is a direct consequence of "smallest buildable sub phases",
not "a size change across the two-session limit". The test bites only if a sub-phase exceeds two sessions, or a
merge would make one do so. None does. So 08-c5, 11-c2 and 13-c3 are NOT A DECISION; the resolution is the map's
finer cut. 11-c2 also follows 11-c1.

## 1. Classification

**Map 07c** — not a decision as a whole. Order forced: under (A), W_max is sized to the restore watchdog, so it
cannot be raised until the solve is off the restore path. Both sub-phases own criteria; sizes M + S.
- 07c-c1 NOT A DECISION: (a). The umbrella is the beta prerequisite (G3 default; matches §3 T1).
- 07c-c2 NOT A DECISION: (a). The umbrella is brought forward (phase-08 scope 10: "W_max is then re-derived once,
  under phase-07c, with one golden round").
- 07c-c3 NOT A DECISION: (a). D-C1–D-C3 and R1–R3 in 07c-1; A1 as written.
- **Correction:** §2.1 Raise goes into both sub-phase files (the phase's first message is 07c-1's).

**Map 08** — the cut follows the file's own sessions and scope order.
- 08-c1 DECISION: which AX37 (5.3) condition binds which sub-phase, and "vacuous for 08-1/08-2". The brief names
  AX37 (5.3) as a recorded dependency a cut may cross; only the owning seats can confirm.
- 08-c2 NOT A DECISION: (b), goldens in 08-4. Forced: S10 and AC13 require the gate result before "this phase's
  goldens are frozen".
- 08-c3 DECISION: moving "measure first… group only if needed" to 08-4 puts a possible output change after the
  checks owned by 08-2/08-3 (AC3, AC5, AC6, AC8, L1–L6); BRIR-build-time risk R3 retired last.
- 08-c4 NOT A DECISION: (a). Forced by AC3's "before the first measurement" (the converter's, in 08-1).
- 08-c5 NOT A DECISION: (a), four sub-phases (size ruling).

**Map 09** — kept whole: acceptable (one subject, Seat 4; size S; the only seam, A7, is a few lines reusing AX18 and
the Phase 06 swap).
- 09-c1 NOT A DECISION: (a), depends on the 08 umbrella (G3 default).

**Map 10** — not a decision as a whole.
- 10-c1 NOT A DECISION: (A). (B) splits AC1 along a factor ("× 2 timing modes"), not a clause (fails G2), and
  measures AC7 on intervals the product does not use. (A) follows the data dependencies (AQ10: AC8 rebuild hits the
  tail cache; AC7 needs the realtime-sim intervals).
- 10-c2 NOT A DECISION: (a), split at S7's existing clause, verbatim.
- 10-c3 NOT A DECISION: (a), 10-1 standalone (owns AC5, one subject, carries risk CR2).

**Map 11**
- 11-c1 DECISION: shell before canvas changes what ships first relative to the file's scope order and retires R2
  before R1. 11-1 (Seat 5 lead) carries user-facing readouts of Seat 6's row (S1e, S1f, S6, S7): one-subject strain.
- 11-c2 NOT A DECISION: follows 11-c1.
- 11-c3 NOT A DECISION within this split: (a). The gap (11 may reach S8/S9 before 05h's reported set and gate exist,
  via 09 → 08 → AX37 exception) predates the split → follow-up `/fix-plan` item: record 05h for 11-3.

**Map 12** — split in two: acceptable. 12-1 passes the value rule on AC5 alone; order is the file's own.
- Condition on AC2: 12-1's share only as the AC2 sentence verbatim with the other two objects omitted, marked "AC2,
  material-ID part; whole in 12-2". If the interrogator rejects that, drop 12-1's share (12-1 still owns AC5).

**Map 13**
- 13-c1 DECISION: order and S9's placement change which risk is retired first (an S9 miss found in 13-2 reopens
  13-1b; in the unsplit phase S1 and S9 iterate together; notarization K1–K3 last, four sessions out). Also: is 13-1
  (S1, S10, S13, L) one subject?
- 13-c2 NOT A DECISION: (a). (b) would own only a C1 clause every `src/sim/` change already owns (fails G2).
- 13-c3 NOT A DECISION: (a), four sub-phases.
- 13-c4 NOT A DECISION; resolution is the literal carry-over, not the map's (a): 13-1 carries all four Raise items
  (the umbrella's first message is 13-1's); 13-4 carries all four again ("before the beta decision"). The map's (a)
  would delay F2/DELTA by ~4 sessions, a change in substance.

**Rule failures**: none on the value rule (given the 12 AC2 condition). 13-2 passes narrowly (C3's
cross-architecture clause, restated with the subject "Robustness test:"); interrogator to check the wording.
One-subject: 11-1 and 13-1 strained (in 11-c1, 13-c1).

## 2. CONVENE — decisions 08-c1, 08-c3, 11-c1, 13-c1

| seat | status | CHOICE ids | reason |
|---|---|---|---|
| 1 Perceptual | convened | 08-c3, 13-c1 | validity of 08-2/08-3 listening checks if grouping lands later; S10 end treatment audibility placed with optimisation |
| 2 Engine | convened | 08-c1, 13-c1 | E_b/t_mix,e via TailMatch; 13-1 lead (compute and recompute time) |
| 3 Reverb renderer | convened | 08-c1, 08-c3, 13-c1 | decay matching (08-3); early-reflection rendering and per-instance CPU; convolver optimisation |
| 4 Chain keeper | convened | 08-c1, 08-c3 | owner of AX37 (5.3) conditions; binaural architecture |
| 5 Deadline keeper | convened | 08-c1, 08-c3, 11-c1, 13-c1 | condition (iii), restore gate, AQ4 cadence benchmark; host conformance/DPI; platforms, CI gates |
| 6 Canvas designer | convened | 11-c1 | canvas metaphor, controls, time-to-first-plausible-scene |
| 7 Founder | convened | 08-c1, 08-c3, 11-c1, 13-c1 | schedule and complexity cost; 08 vs 05h timing; beta timing, signing/notarization |
| 8 Storyteller | not required | — | no sub-phase reaches producers before 13-4's beta; in-phase order changes nothing a producer receives |
| 9 Room acoustician | not required | — | no decision touches materials, presets or reference rooms; AX37 (iv) marking is Seat 4's |

Common instructions: rate every option of your CHOICE ids now/later (0–3), conditions of acceptance for any 2 or 3,
optional minimal variant. Read the brief ("Reading of her words"), `docs/board/README.md`, the named maps.

- **Seat 1**: map-08 (08-c3, §1 table), map-13 (13-c1, 13-c2), phase-08 S5a, R3, listening checklist; phase-13 S9,
  S10. 08-c3: (a) whole S5a in 08-2; (b) grouping rule and R3/CF6 in 08-4, AC3/AC5/AC6/AC8 re-run on grouped output
  before the freeze — are L1–L6 still valid under (b)? 13-c1: (a) S9 in 13-2, order 1→2→3→4; (b) S9 in 13-1;
  (c) 13-2 before 13-1; rate S10 staying in 13-1.
- **Seat 2**: map-08 (08-c1, coverage rows H-dep (i)–(iv)), BUILD_PLAN AX37, AX39, phase-05b2 lines 397–408 (D-T5.3),
  map-13 (13-c1, 13-c3), phase-13 S1, S10, S13. 08-c1: (a) full exception line on every sub-phase; (b) (i), (ii),
  (iv) on 08-3 and (iii) on 08-4, 08-1/08-2 reading no E_b or t_mix,e — confirm or refute. 13-c1 as Seat 1, plus
  whether 13-1 is one subject under your row.
- **Seat 3**: map-08 (08-c1, 08-c3), phase-08 S5a, S5b, S8, R3, map-13 (13-c1), phase-13 S1, S9. Rate 08-c1, 08-c3,
  13-c1; does convolver optimisation (non-uniform partitioning, 13-1b) belong under a Seat 2 lead?
- **Seat 4**: map-08 in full, phase-08, BUILD_PLAN AX37 (5.3), phase-05b2 397–408. 08-c1 (your conditions: does (b)
  match what you set?); 08-c3.
- **Seat 5**: map-08 (08-c1, 08-c2 resolution, 08-c3), phase-08 S8–S10, AC12/AC13, map-11 (11-c1), phase-11,
  map-13 (13-c1, 13-c4 resolution), phase-13. 08-c1 (condition (iii), 05h scope-10 re-runs); 08-c3 (benchmark vs AQ4
  cadence, AX33); 11-c1: (a) three-way shell first, (b) two-way canvas first (L + M), (c) whole (M) — is 11-1 one
  subject?; 13-c1.
- **Seat 6**: map-11 in full, phase-11. 11-c1 (a)/(b)/(c); rate the interval in (a) where the generic editor is gone
  and placement exists only through host lanes; should S1e/S1f/S6/S7 sit in a Seat 5-led sub-phase? Variant allowed
  (e.g. S4 removal moved to 11-2).
- **Seat 7**: all four DECISION items; BUILD_PLAN §0 (05h in progress); phase-13 K1–K3 and Raise items. 08-c1
  (schedule effect of 08-1/08-2 before 05h); 08-c3 (rework cost); 11-c1; 13-c1 (notarization last vs earlier).

Knowledge inventory (all product documents, "known"): K1 AX37 (5.3) conditions; K2 S10/AC13 freeze rule; K3 AC3
"before the first measurement"; K4 phase-11 scope order and dependencies; K5 phase-13 Raise preamble and S9/S1
coupling. Open gap: whether 08-1/08-2 read nothing from 05h (Seats 2 and 4 to confirm; code checkable). No RESEARCH
NEEDED.

Follow-ups (not this split): record 05h as a dependency of 11-3 (11-c3) via its own `/fix-plan`; review-skill drift
noted by maps 08 and 10.

Decided for Maisara (proposed; final only after the interrogator): two-session limit per sub-phase; 09 whole; 12 in
two; Raise items reach her in the first session of each split phase, and again where the maps place them.

NEEDS MAISARA: none. Verdict: **CONVENE**.
