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
   - several options valid, none valid, or the choice is a product matter: ask the user, briefly, with
     the interrogator's evidence. Don't pick for them.
4. Send the verified decisions back to the plan-editor to apply (resume it, or brief a new one with them).
5. Run the **interrogator** on the finished diff (the changed passages only) to check the science of what
   was written. Anything WRONG goes back through steps 2–4; at most 3 rounds, then report what is left.
6. Record the decisions, verdicts and final status in `docs/review/ledger.md` (under the target's
   heading, citing the corpus revision), commit with `plan: <summary>`, and push.

Report to the user: what changed, which decisions were verified and how, and what still needs them.
