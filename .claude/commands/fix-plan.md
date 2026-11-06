---
description: Correct the PRD, BUILD_PLAN or phase files; acoustic decisions go to the interrogator, not the editor
argument-hint: <the fixes to make, or ledger row ids>
---
Run this loop yourself (the main session); subagents cannot start other subagents. The user does not
need to know or remember these steps.

1. Make sure the corpus is present (`tools/ci/fetch_corpus.sh` if `docs/corpus/SOURCE_COMMIT` is missing).
2. Brief the **plan-editor** subagent with $ARGUMENTS: the exact fixes, the ledger rows they come from,
   and every decision that is already settled. Wait for its report.
3. If it returned DECISIONS NEEDED, run the **interrogator** on them: for each option, verdict and
   evidence against the corpus, with arithmetic shown. Then:
   - exactly one option CORRECT and the others WRONG or CONDITIONS VIOLATED: that option is verified;
   - several options valid, none valid, or the choice is a product matter: run the decision loop below,
     then ask the user, briefly, to accept or veto each surviving decision. Don't adopt one without her.

   **Decision loop** (each agent's role is in its file under `.claude/agents/`):
   a. **researcher**: builds the dossier for the decision(s) whenever a load-bearing fact is outside the
      corpus or unverified. The decider goes in only when the dossier says READY, or with the NOT READY
      gaps listed so that it can defer those parts.
   b. **decider**: decides, with its knowledge inventory and load-bearing claims. Send any RESEARCH NEEDED
      back to (a).
   c. **interrogator** (decision mode): SURVIVES / SURVIVES WITH CORRECTIONS / FALLS / UNDERINFORMED. A
      FALLS goes back to the decider with the verdicts; an UNDERINFORMED goes back to (a). At most 3 rounds.
   d. **advocate**: screens the decisions and the interrogator's verdicts for the product. PASS goes on. A
      REDIRECT goes to the agent it names, and its answer comes back to the advocate. A NO stops the
      item: it is not applied unless the objection is settled or the user overrides it, and the override
      is recorded in the ledger.
   Only decisions that survived (c) and passed (d), or that the user cleared, go to step 4.
4. Send the verified decisions back to the plan-editor to apply (resume it, or brief a new one with them).
5. Run the **interrogator** on the finished diff (the changed passages only) to check the science of what
   was written. Anything WRONG goes back through steps 2–4; at most 3 rounds, then report what is left.
6. Record the decisions, verdicts and final status in `docs/review/ledger.md` (under the target's
   heading, citing the corpus revision), commit with `plan: <summary>`, and push.

Report to the user: what changed, which decisions were verified and how, and what still needs them.
