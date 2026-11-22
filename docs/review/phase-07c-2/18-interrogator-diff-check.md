<!-- Saved by the orchestrator from the interrogator's report, 2026-11-22. -->

Interrogator diff check of the `/fix-plan` edits for phase 07c-2 (D-W2 final, D-W3 H-2c, D-W4 homing). Corpus revision: c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

# Diff check: `/fix-plan` edits for D-W2, D-W3 and D-W4

**Verdict: not COMPLETE. Six corrections, all minor.** One of them, correction 1, could change how M7 is run. No decided rule or number is dropped or reversed.

**Method.** I have no shell here, so I could not run `git show HEAD`. I checked the files as they stand on the branch:
- `docs/phases/phase-07c-2.md`: scope 3, scope 9, scope 11, out of scope, the new acceptance criterion.
- `docs/phases/phase-10-3.md`: D-W4 at L44–60, acceptance criterion L105–108, listening item L119–122, definition of done L145.
- `docs/BUILD_PLAN.md`: §0 rows 07c-2 (L36) and 08 (L38), AX47 (L169), AX49 (L171), §6 row (L531).
- `docs/review/ledger.md`: L2448–2461.

I compared them against decider files 8 §6, 13 ("D-W2: final" and H-2c) and 15, and file 16 including the orchestrator's application block. If HEAD's diff touches anything outside those passages, I have not seen it.

## Faithful as written
- **Scope 11 items 1–6 and 8** match file 13's H-2c and file 15's items 3 and 4 as worded in the orchestrator's application block.
  - Item 3 uses the generation read before the snapshot (L356). Item 4's token compares against that same value.
  - The code references are correct at HEAD: `ScenePipeline::decide` L356, the checks at L543 / L556, `ScenePipeline::commit` L583, `IrBuilderThread.h` L5. They are cited by function and comment, as asked.
  - The routing text and the "returns to the board if M7 or TSan fails" clause match file 13.
- **Condition 4 is unchanged** and FM-W3a is recorded as withdrawn. The new "out of scope" exception (condition 4's defect is scope 11) is consistent with that.
- **The new acceptance criterion** matches scope 11: generation adoption, per-generation token, no held-level adoption, TSan, bit-identity, `[reset-nowait]`, B1-b, M7 ≤ 700 ms flat in m at m = 1, 4, 5, 6, 8, and M7b.
- **Scope 3's AX38 (iv) reading** matches file 8 §3 ("a reading, no amendment").
- **BUILD_PLAN §0 rows 07c-2 and 08** carry "08-x goldens are frozen only after 07c-2 (or 07c-2b) is `done`" (Seat 7's condition).
- **AX47 (L169)** records the D-W2 criterion faithfully: noise 0.9 → 0.5 dB at ≥ 12/16, speech 0.9 → 0.5 dB at ≥ 13/16, the 0.5 dB step only after a 0.9 dB detection in that chain, FWER ≤ 0.049 (strong, union bound), a 3 dB anchor at ≥ 5/6, either-chain reversal, and "a speech non-detection never cancels a noise detection".
- **AX49 (L171)** records the L4 anchor and the release into ≥ L of free decay, citing file 13 item 14.
- **phase-10-3's D-W4 text** reproduces file 15 Q2 items 1–4 word for word, including the NEEDS MAISARA case (a) phrasing and the beta deadline with the phase-13 Raise fallback. The record is filed as an acceptance criterion ("A record, not a gate", consistent with "automated record"). The listening item sits in the checklist, and the definition-of-done clause was added.
- **Scope 11 item 7, the orchestrator's addition.** The M7 set-up (1 instance; `layout4_s1/listener_corner` and the s = 1 cube; pool size; worst over ≥ 3 runs) is copied correctly from decider file 8 §6, and file 13 does not revoke it. It narrows file 13's "capped scenes" to the two scenes file 8 named; both are capped at ×8 (T3). Seat 3's C-a "at 1 instance" and Seat 5's (iii) are met. One ambiguity remains, correction 1.

## Corrections

1. **Scope 11 item 7: "pool size" is ambiguous under H-2c.**
   - File 8 §6 set "pool size" before H-2c's rule existed. H-2c item 1 says the pool is `hardware_concurrency − 1` while the builder works alongside, and M7 is "with the solve occupying the pool".
   - As written, M7 could be run at the full pool, which is not the configuration that ships.
   - State which pool M7 uses. File 13's own wording points to the shipped H-2c pool (`hardware_concurrency − 1`, solve occupying it).
2. **Scope 3 L52 and ledger P07C2-W1 understate what the re-derivation waits on.** Scope 3 says "waits on scope 11 (M7 in)"; the ledger says "D-W3 (M7)".
   - File 13's waiting list item 1 is "D-W3 (H-2c) implemented, with M7 (≤ 700 ms, flat in m) and M7b in, and TSan green".
   - Scope 3 then cites the full list, so nothing is lost. But the short form should read "scope 11 done (M7, M7b, TSan)", not "M7 in".
3. **Ledger P07C2-W2's outcome is misquoted.** It says "SURVIVES (files 12, 14)". File 12 rated D-W2 **SURVIVES WITH CORRECTIONS** (two: the 46 dB SNR wording and the onset placement); file 13 applied them; file 14 rated it **SURVIVES**. Write it that way.
4. **BUILD_PLAN §6 row L531.** "No threshold, golden or other AX/AQ value changed" is inaccurate. AX47 now carries new pre-registered detection thresholds (12/16, 13/16, anchor 5/6) that its Reversal had left to this loop. Write "no existing threshold … changed; AX47's detection criterion is set as its Reversal provides", or equivalent.
5. **The D-W2 cross-reference misses the onset rule.** Phase-07c-2 scope 9, AX47 (L169), the §6 row and ledger P07C2-W2 cite file 13 "D-W2: final", items 1–16.
   - The pre-registered onset rule is not in items 1–16. It is in file 13's separate section "Q5: TSP step placement (pre-registered)": onset ≤ 0.43 · T30(1 kHz) after the end of speech; tail ≥ rendered floor + 20 dB, asserted per stimulus; a seeded onset that fails is replaced and recorded.
   - Item 8 points to it only as "Onset as in Q5", which is a rebuttal-question label. Name the Q5 section in each cross-reference so that the rule cannot drop out of the pre-registration.
6. **A cross-reference points to a file that does not exist yet.** phase-10-3 L60 and the ledger header cite `docs/review/phase-07c-2/17-researcher-RQ-W4-1.md` as "pending". It does not exist yet, so it must be saved under exactly that name, or both references updated, before the session closes.

## Ledger

| id | file / place | item | verdict | evidence | correction |
|---|---|---|---|---|---|
| DC-1 | phase-07c-2 scope 11 item 7 | M7 "pool size" | IMPRECISE (two readings) | file 8 §6 predates H-2c item 1 (`hardware_concurrency − 1`); file 13: "with the solve occupying the pool" | 1 |
| DC-2 | phase-07c-2 scope 3 L52; ledger P07C2-W1 | waiting list item 1 | IMPRECISE (understated) | file 13 "D-W1: waiting list, corrected", item 1 | 2 |
| DC-3 | ledger P07C2-W2 | outcome | misquote | file 12: D-W2 SURVIVES WITH CORRECTIONS (2); file 14: SURVIVES | 3 |
| DC-4 | BUILD_PLAN §6 L531 | "No threshold … changed" | INCONSISTENT with AX47 L169 | AX47 now records 12/16, 13/16, 5/6 | 4 |
| DC-5 | phase-07c-2 scope 9; AX47 L169; §6 L531; ledger P07C2-W2 | "items 1–16" leaves out the onset rule | cross-reference incomplete | file 13 "Q5: TSP step placement (pre-registered)"; item 8 "Onset as in Q5" | 5 |
| DC-6 | phase-10-3 L60; ledger L2453 | file 17 "pending" | cross-reference to a file not yet present | glob `docs/review/phase-07c-2/1[6-9]*` returns only file 16 | 6 |
| DC-7 | phase-07c-2 scope 11 items 1–6, 8; acceptance criterion | H-2c text and code references | faithful | files 13, 15, 16 application block; HEAD L356, L543, L556, L583 | — |
| DC-8 | phase-07c-2 scope 11 item 7 | orchestrator's M7 set-up | faithful to file 8 §6 (apart from DC-1) | file 8 §6 M7 | — |
| DC-9 | BUILD_PLAN §0 L36, L38 | 08-x goldens wait for 07c-2 | faithful | file 13 item 8; Seat 7 | — |
| DC-10 | AX47 L169, AX49 L171 | D-W2 criterion; L4 anchor and release | faithful | file 13 items 3, 4, 14 | — |
| DC-11 | phase-10-3 L44–60, L105–108, L119–122, L145 | D-W4 home | faithful | file 15 Q2 items 1–4; file 16 D-W4 correction 1 | — |
| DC-12 | ledger P07C2-W3, W3a, W4 | outcomes | faithful | files 12, 14, 16 | — |

Files checked:
- /home/user/makroof/docs/phases/phase-07c-2.md
- /home/user/makroof/docs/phases/phase-10-3.md
- /home/user/makroof/docs/BUILD_PLAN.md (L36, L38, L169, L171, L531)
- /home/user/makroof/docs/review/ledger.md (L2448–2461)
- /home/user/makroof/docs/review/phase-07c-2/16-interrogator-on-file15.md (L84–95)
- /home/user/makroof/docs/review/phase-07c-2/8-decider-rebuttal-r2.md (§6)
- /home/user/makroof/docs/review/phase-07c-2/13-decider-rebuttal-r4.md
- /home/user/makroof/docs/review/phase-07c-2/15-decider-rebuttal-r5.md
- /home/user/makroof/src/plugin/core/ScenePipeline.cpp (L324–359, L500–587)

---

**Orchestrator (2026-11-22):** corrections 1–5 applied in the next commit (M7 on the shipped H-2c pool, hardware_concurrency − 1; scope 3 / ledger wait on scope 11 done (M7, M7b, TSan); ledger P07C2-W2 outcome; §6 row wording; the Q5 onset section named in every D-W2 cross-reference). Correction 6: file 17 is saved under that exact name when the researcher reports.
