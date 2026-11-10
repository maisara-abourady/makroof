---
description: Correct the PRD, BUILD_PLAN or phase files; acoustic decisions go through the board's decision loop, not the editor
argument-hint: <the fixes to make, or ledger row ids>
---
Run this loop yourself (the main session); subagents cannot start other subagents. The user does not
need to know or remember these steps.

1. Make sure the corpus is present (`tools/ci/fetch_corpus.sh` if `docs/corpus/SOURCE_COMMIT` is missing).
2. Brief the **plan-editor** subagent with $ARGUMENTS: the exact fixes, the ledger rows they come from,
   and every decision that is already settled. Wait for its report.
3. If it returned DECISIONS NEEDED, run the **interrogator** on them (document mode): for each option,
   verdict and evidence against the corpus, with arithmetic shown. Then:
   - exactly one option CORRECT and the others WRONG or CONDITIONS VIOLATED: that option is verified;
   - several options valid, none valid, or the choice is a product matter: run the decision loop below.
     Surviving decisions are adopted without stopping for the user: the decider answers for her from the
     PRD (`docs/board/README.md`, "Who answers Maisara's questions"; Maisara 2026-11-10). They are listed
     under "Decided for Maisara" in the report and the PR, and she may veto any of them afterwards.

   **Decision loop** (each role's instructions are in its file under `.claude/agents/`; the board and its
   convening table are in `docs/board/README.md`):
   a. **decider, convening round**: give it the decisions. It returns **CONVENE**: a nine-row convening
      table (every seat convened or recorded not required with the reason), a brief per convened seat,
      and its first-pass knowledge inventory with any RESEARCH NEEDED questions.
   b. **seats and researcher, in parallel**: run every convened seat (`seat1-…` to `seat9-…`) with its
      brief verbatim, all in one message so they run concurrently; run the **researcher** at the same
      time whenever the decider named a gap or a load-bearing fact lies outside the corpus. Collect the
      seats' positions (`SEAT <n> POSITION` or `NOT MY MATTER`) and the dossier. If a seat asked for a
      claim to be verified, pass it to the researcher before the decision round. A seat whose agent type
      is not registered in this session (new in this session) is run as a `general-purpose` worker given
      its agent file verbatim, and the transcript says so.
   c. **decider, decision round**: give it the positions and the dossier. It returns, per decision, the
      tension map, the minimum-tension working, **DECISION** with load-bearing claims and future-debt
      register, or **FOR MAISARA** (a question it answered for her from the PRD, with the PRD ids), or
      **RESEARCH NEEDED** (back to the researcher), or **NEEDS MAISARA**. NEEDS MAISARA covers only three
      cases: the PRD is silent or contradictory; the answer changes the PRD or one of her recorded
      decisions; or a seat's veto-grade rating would have to be overridden. The user decides those, and
      an override is recorded in the ledger.
   d. **interrogator, decision mode**: **SURVIVES** / **SURVIVES WITH CORRECTIONS** / **UNDERCONVENED**
      (run the named seats, back to (c)) / **TENSION MISREAD** (back to (c) with the seat's words) /
      **FALLS** (back to (c)) / **PRD MISREAD** (back to (c) with the PRD passage) / **UNDERINFORMED**
      (back to the researcher, then (c)). A seat is re-run
      only when the decider composed a variant it must rate or the interrogator asks what the seat meant;
      give it the provisional decision and the other seats' positions, and it answers only what changed.
   Repeat (c)–(d) for at most 3 rounds. The item goes on only with SURVIVES or SURVIVES WITH
   CORRECTIONS, or when the user answered it herself. After 3 rounds, the decider rules on what is still
   contested as FOR MAISARA from the PRD, with each side's last word. The interrogator checks that ruling
   once. It goes to the user only in the three NEEDS MAISARA cases.
   Save every round's output under `docs/review/<target>/` (decider, seats, researcher, interrogator,
   one file per round) so the steward and the reviewer can check the map against the seats' words.
4. Send the verified decisions back to the plan-editor to apply (resume it, or brief a new one with them).
5. Run the **interrogator** on the finished diff (the changed passages only) to check the science of what
   was written. Anything WRONG goes back through steps 2–4; at most 3 rounds, then report what is left.
6. Record the decisions, the convening tables, the verdicts and the final status in
   `docs/review/ledger.md` (under the target's heading, citing the corpus revision), commit with
   `plan: <summary>`, and push.
7. Report to the **steward** with the session brief (CLAUDE.md, "Reporting: the steward"): what changed,
   which decisions were verified and how (which seats were convened, the worst-off seat and what it gets
   back later, the interrogator's outcome), and the ledger rows. Close its CONTINUE gaps. Report to the
   user only on READY TO REPORT or NEEDS MAISARA. The report covers:
   - what changed;
   - which decisions were verified, and how;
   - the "Decided for Maisara" list (one plain line each, with PRD ids, open to her veto);
   - only the three-case questions that need her.
