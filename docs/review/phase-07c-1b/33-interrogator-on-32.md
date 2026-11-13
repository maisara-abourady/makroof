# 33 — Interrogator on decider file 32 (P07C1B-R1 round 3)

2026-11-13, corpus c1b171f (no acoustic fact load-bearing). Saved by the orchestrator from the interrogator's report.

**Outcome**
- **Decision (1):** SURVIVES WITH CORRECTIONS (K1, K2; K3 optional).
- **Decision (2):** SURVIVES.
- **Decided line:** PRD MISREAD on one narrow point (8a-4: her "do that" misquoted). Fixed by text; the conclusion is unchanged.
- Nothing FALLS or is UNDERCONVENED. The winners 1b′ and 2a are unchanged.

**File 31's corrections:** C-1 … C-13 all applied.
- C-8 has one gap, in the Decided line: Seat 3's C1 conditions are incomplete there (no run id, no L = 12 s, no 2 emitters).

**Questions Q1–Q5:**
- Q1 CORRECT.
- Q2 faithful, and K12 CORRECT (BUILD_PLAN L36–37).
- Q3 CORRECT.
- Q4/L7 CORRECT: code L166 `recorded14xS` 33.40, read only in prints at L679 and L687–693. BUILD_PLAN L160 and L484 give 33.40 s; L117 gives W_max 3.05 M; 33.40 > 29.1.
- Q5: Seat 6's condition is met; Seat 3's C1 is IMPRECISE in the Decided line (fixed by K1).

**Other checks:**
- L8/K11 and the lag: CORRECT. CLAUDE.md says CI does not run on `main`.
- The fallback carrier against her 2026-11-12 decision: not PRD MISREAD. With "do that" she left the owed PASSES30S follow-up to the next phase (brief L12, L54), which points the same way.
- T7 anchors: CORRECT (phase-07c-2 L103 → L105; phase-07d item 8 L83–92 → L94).
- Land-now texts: none says "listed" as a state.
- T1–T8 anchors: verbatim and unique.
- Preamble and NFR-4: verbatim; NFR-6's role is correct.
- Map, ordering and debt: correct.
- T8 date: IMPRECISE (K2).
- T7(a) form: minor (K3).

**Corrections**
- **K1, Decided line:**
  - "— on a shared hosted Mac CI runner, 100 m room at 96 kHz, not the load time of one plugin." → "— on a shared hosted Mac CI runner (run 43427854710), 100 m room at 96 kHz, 12 s exact tail, 2 emitters, not the load time of one plugin."
  - "Does not amend her decision of 2026-11-12 ("do that": the 05i flag's own follow-up PR #31); if she wants that vehicle here, a dedicated follow-up PR replaces the next-phase commit." → "Does not amend her decisions of 2026-11-12 (her request for a session for the 05i flag, "do we have a session for this small follow up…", which became follow-up PR #31; and "do that", which put the BUILD_PLAN wording fix in #31 and left the PASSES30S readings to the next phase, 07c-1); if she wants a dedicated vehicle here, a follow-up PR as #31 replaces the next-phase commit."
- **K2, T8:** "| 2026-11-13 |" → "| <carrier commit date> (decided 2026-11-13) |".
- **K3, T7:** (a) becomes scope item "10. " in phase-07c-2, and the bracket in (b) reads "phase-07c-2 scope 10".

**Questions for the decider:**
1. Is K1's reading of "do that" accepted?
2. Is T8 dated by the decision or by the commit?

**Orchestrator's application (no new decision):** K1–K3 were applied to file 32 as the faithful record of her words (brief L10–12) and the carrier's own date. This follows the file 20 precedent for wording-only corrections. Both questions are answered by those texts.
