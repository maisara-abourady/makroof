# 35 — Interrogator /fix-plan diff check: phase-07c-2b.md and §0 row

Corpus revision c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. Diff check of `/home/user/makroof/docs/phases/phase-07c-2b.md` and `/home/user/makroof/docs/BUILD_PLAN.md` L37 (the 07c-2b row). Ten findings: three are INCONSISTENT and need fixing.

**Numbers and acoustic choices: CORRECT.** No acoustic or numeric choice was made in the edit.
- The item-9 values are file 31's own, and I recomputed them. Kuttruff §5.6 Eq. 5.44 gives r_c = (640/16π)^½ = 3.57 m. Eq. 5.45 gives D/R = 10·log10(r_c²/r²) = −20·log10 3.47 = −10.81 dB.
- These match their sources: the union rate ≤ 0.049 × families, the −1 dBFS peak, the 0.43 ceiling at 1/1, the item-13 wording, the V1–V4 / S-B\* / S-W definitions and the M3 convening (seats 1–7 and 9, Seat 8 not required).
- The 1.3–2.8 h and "about 2 h" figures (file 32 K6) and the M2 debt checks (file 34 item 3) also match.

**Findings**

1. **INCONSISTENT: Timing dropped (rule-2 breach).** Out of scope says "scope 1's timing sentence (O14)" was delivered. But phase-07c §3 T1 ("before the first public release … with its W_max raise in one golden round") now binds the golden round, and that round is in 07c-2b. The header's beta-prerequisite line (07c-2 L13–14) was dropped too. Correction: carry 07c-2 scope 1 and the L13–14 sentence into 07c-2b. Delete "(O14)" from Out of scope, or limit it to "07c-2's own PR sentence".

2. **IMPRECISE: scope 1 skip condition.** The item counts as done when the run prints only the `07c2-m7 ` lines. O15's criterion asks for M7, M7b and TSan `[pipeline]` together on a three-OS run. Correction: "…a green three-OS CI run that shows M7 meeting the criterion, M7b recorded against `discardedMidDrag` (with the AX38 (iv) patterns) and TSan `[pipeline]` stress green…". "Under the same condition" in the second bullet then becomes "Otherwise".

3. **CORRECT, with one caveat: M7 routing.** M7 is placed first, before the golden round, with the fail-back to the board kept. This is consistent with 07c-2 scope 11 item 8. The caveat: 07c-2 can only be set `done` if its own acceptance criterion for scope 11 is restated there as moved. Otherwise its done status contradicts its own criteria (CLAUDE.md rule 6).

4. **IMPRECISE: the AX38 (iv) load mark in scope 6.** "Read on its own definition (decider file 8 §3)" drops the definition and the binding. Restore it verbatim from 07c-2 scope 3: "the time until the last instance is audible at load (at the interim level since 07c-1), not the time until the final tail settles; it binds W only through the keyless path (K-a or `medium_room` insertion, FM-B2), which is the class (c) round's matter".

5. **IMPRECISE: scope 9 (O7).** "07c-2 lands before the freeze" should read "07c-2b lands before the freeze".

6. **MISSING: M1 reversal condition (file 34 item 2).** An s < 1 scene chosen by M3 has a specular share above 0, which is exactly where the condition can fire. Add to scope 2 before the seal: M1 reverses if item 6's identity assertions fail on a rendered A/B pair of any scene with E_target specular share > 0; click-detector results do not count. Also add that s_w ≤ 2.3 % is printed and asserted.

7. **IMPRECISE: Dependencies paragraph.** It attributes O12 to "the G17 answer". O12 moved here by the later restatement (steward round 4, G19), and M3 and the seal by the decider-round-4 restatement. Cite all three.

8. **CORRECT: dependency statement.** "Depends on 07c-2 `done` (and through it 07c-1, 07c-1b, 05h, 07)" is right.

9. **INCONSISTENT: §0 umbrella row L33.** It still reads "split (07c-1, 07c-1b, 07c-2)". Add 07c-2b, and the line "07c-2b split from 07c-2 2026-11-22".

10. **IMPRECISE: §0 row L37 notes.** They leave out O11 (interim stream check), O7 (follow-on checks) and the conditional M7. They also lack the "Depends on 07c-2 `done`" and "Lead: Seat 2" lines that row 36 carries. Correction: "…M3 ABX scene, seal and ABX (person), class (c) and load fallback, interim stream check, W pin, solveRefMs re-pin, golden round, follow-on checks, O12; M7/M7b/TSan first if 07c-2's CI did not show them. Depends on 07c-2 `done`. Lead: Seat 2."

**Everything else in the file is copied faithfully.** That covers O4–O7, O9–O12, the α treatment, the amendments held for M3 (including file 34 item 1's clause), the `click_check` follow-up and the format, which follows the 07c-1b precedent.

## Orchestrator
Corrections 1, 2, 4, 5, 6, 7, 9 and 10 were sent to the plan-editor and applied. Finding 3 (07c-2 scope 11 acceptance restated as moved) is applied at 07c-2's status commit. Finding 8 is CORRECT.
