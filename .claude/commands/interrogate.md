---
description: Run the interrogator subagent on a document, append its ledger, answer it as the builder
argument-hint: <path to PRD, BUILD_PLAN or phase file>
---
First make sure the corpus is present: if `docs/corpus/*.md` is missing or `docs/corpus/SOURCE_COMMIT` is
absent, run `tools/ci/fetch_corpus.sh` (in a cloud session, attach `maisara-abourady/audio-resources` first).
If that fails, stop and report it.

Use the interrogator subagent on $ARGUMENTS. Append the ledger to `docs/review/ledger.md` under a heading
with the target file and today's date (create the file if it does not exist).

Then answer each question as the builder, citing the corpus in `docs/corpus/` (record the `SOURCE_COMMIT` revision in the ledger heading) with the same citation
rules as the interrogator (real section numbers only, short paraphrase, no quotes over 25 words).
Re-run the interrogator on your answers only for open blockers, at most 3 rounds. Update each ledger
row's status (open / resolved / disputed) after every round.

List what remains unresolved, and report it to the **steward** with the session brief before you report
to the user (CLAUDE.md, "Reporting: the steward"). Do not edit the target document. Changes to the plans go through `/fix-plan`, where the decider
answers for Maisara from the PRD. Changes to the PRD itself are hers (`docs/board/README.md`, "Who answers
Maisara's questions").
