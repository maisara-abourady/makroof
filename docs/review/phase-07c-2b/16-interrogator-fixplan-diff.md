# Interrogator: /fix-plan steps 3 and 5 for phase 07c-2b (D1 and commit 33884fe)

Commit 33884fe has one blocker: the run sheet turns the pre-seal speech null into a check on fallback scene B only. On D1, both options are valid and the decider has to choose before the seal.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**How I checked the commit:** I have no shell, so I could not run `git show 33884fe`. I checked the files the commit touches in their current working-tree state against the decisions they apply:
- `docs/BUILD_PLAN.md`: AX47 (L170), AX49 (L172), L365, the §5 B11 void rule (L404), the §0 rows (L26, L37) and the §6 rows (L534–536);
- the run sheet in full;
- `docs/phases/phase-07c-2b.md` scope 2 and item 8, `phase-08-3.md` L59–82, `phase-05e.md` (b), `phase-08-4.md` L141–145, `phase-07d.md` L113–124.

The decisions are in `docs/review/phase-07c-2b/` files 2, 5, 8, 10, 11, 13 and 14, plus phase-07c-2 file 13 and builder file 4. If the commit's diff touches lines I did not open, they are not covered here.

## (1) D1: L4 anchor failure, rerun or "inconclusive"

**What each source says:**
- phase-07c-2 file 13 item 4 (AX47): "A failed anchor voids that chain's block. It gets one rerun and is never recorded as 'not detected'. A non-detection is never a reason to rerun."
- Item 13: "'inconclusive' if the anchor failed".
- Item 14 (L4): "Same chain and tool, with the 6-trial anchor".
- AX49 (L172): "carries the AX47 self-ABX's 6-trial 3 dB anchor (pass ≥ 5/6)".
- Decider file 10 L4-D sets the anchor and its pass mark only.

**Option (a): void the block, one rerun, never recorded "not detected". CORRECT** as a valid reading and a valid design.
- It reads "carries the anchor" together with the anchor's consequence in item 4.
- α is unchanged. Only one block's 16 scored trials ever count, so the chance of a detection by guessing stays P(≥ 12/16 | p = ½) = 2517/65536 = 0.0384.
- Condition: the void is decided on the anchor alone, and the voided block's scored result is discarded whatever it shows. That is item 4's "a non-detection is never a reason to rerun", applied the other way round.

**Option (b): recorded "inconclusive", no rerun. CORRECT** as the literal reading of file 10, which sets no rerun. α is unchanged.
- **Its rationale has a CONDITIONS problem.** In AX47, item 13's "inconclusive" sits alongside item 4's rerun, so that wording alone does not exclude a rerun.
- **CONSEQUENCE:** after a failed anchor, AX49's reversal ("the L4 ABX detects the cut") stays unread. That is the unread-reversal debt Seats 1, 2, 3, 5, 6 and 7 rated later 2 under L-c (9-seat files).

**Verdict:**
- Neither option is WRONG.
- The corpus does not settle it (NOT CHECKABLE: it is a pre-registration rule, not an acoustic fact).
- This is a design matter for the decider. It must be fixed before the L4 seal (item 11), and run sheet §8 L411–412 correctly marks it "open". It changes no PRD text, so it is not NEEDS MAISARA unless the decider finds the PRD silent.

**Related: the L4 detection wording "detected (≥ 12/16)" is IMPRECISE.**
- Item 13's pattern carries the family α ("detected (≥ c/16, family α 0.049)").
- L4 is a single test, so its family α is 0.0384.
- File 10 set only the non-detection wording, so the value to state is "family α 0.038".

## (2) Commit 33884fe against the surviving decisions

### Blocker: run sheet §3 item 2 (L155–156, L159–160) is WRONG
The text: "selection grounds … the pair was fixed for its measured Q5, form-(b) and **scene-E** null results", and "Open before the seal: `layout5_s0.8/default` (**fallback B**) must be nulled within −120 dB on every speech stimulus; it has been nulled on noise only. **Scene E** is nulled on speech."
- In file 10 M3-T ("E is nulled on speech; B is nulled on noise only") and in builder file 4 fact 5, **B and E are renders, not scenes**. B is the unstepped render and E is the stepped IR rendered alone (D-M3a notation).
- File 4 fact 5 nulls the E render on speech in every scene (−130.0 dB or better). It nulls the B render on noise only, in every scene.
- M3-C 7 requires "B and E nulled within −120 dB on every noise and speech stimulus" for the sealed scene.
- As written, the speech null of scene E's unstepped render (B) is dropped as a pre-seal condition. The statement "Scene E is nulled on speech" is false for that render.
- A pre-seal gate is built on this line, so it is a **blocker**.
- The plan-editor's interpretation "the fallback-B speech null" is the source of the error.

### Major (INCONSISTENT): run sheet §1 L35–36 does not apply D-M3f
- §1 still quotes file 34 item 1's clause "[S-A only, as long as layout4_s1/default is the ABX scene:] … the share is 0 in every band" as what item 5 scales.
- D-M3f survived (interrogator file 3) and replaced that clause with "[Scenes with s = 1 on every face:] … On an s < 1 scene … it does not, and M1's reversal condition (file 34 item 2) is live there."
- On scene E (s = 0.9, specular share 0.022 / 0.001) the quoted clause does not apply.
- L109–110 cites D-M3f, but the decided text is not on the sheet.
- Keeping S-A as a superseded record is acceptable. This clause is not that record: it is presented as the rule in force.

### Minor (INCONSISTENT): earlier decisions not reflected in the plan text
- **click_check is still presented as undecided.**
  - phase-07c-2b scope 2 (L126–129) still reads "`click_check` … per-frame flags … or … A − B against the crossfade model … Which one, and whether it is needed, is Seat 3's and Seat 5's call".
  - D-M3a decided form (b) (file 2, corrected in file 5; SURVIVES).
  - Run sheet §3 item 3 (L169) still says "no new click at the step". It does not state form (b)'s criterion or M3-C 7's per-stimulus pre-seal set: form (b) green, B and E nulled on noise and speech, M1 within 0.05 dB.
- **Stale phase references.**
  - AX49 L172 says L4 is "run with the AX47 ABX in 07c-2", while AX47 now says "(run in 07c-2b)".
  - AX49's phases column omits 07c-2b.
  - phase-07d L124 still points "the AX47 / L4 ABX runs" to phase-07c-2.

### Verified CORRECT or faithful
- **AX47:**
  - The Reversal reads "the 07c-2 self-ABX (run in 07c-2b) or its phase-08-3 rerun (… capped layout-4 or layout-5 scene …)" (M3-F; D-M3i).
  - The α sentence is present, with 2 families and union ≤ 0.098 (2 × 0.049).
- **AX49:**
  - The render_cli clause matches L4-W word for word.
  - The L4 pointer and the ghost print labelled "noise-excitation (Schroeder) estimate" (file 13, K29) are present.
  - e^(−13.82 × 0.312) = 0.0134.
- **L365:** Seat 6's settling line is present, beside the phase-07c-1b follow-up.
- **§5 B11 void rule (L404) and phase-05e (b):** faithful to D-M3h 1 plus C-b (AX21 false, t_mix,e moved, decay target changed; rebuild checks; "pre-promotion engine"; item 15 scheduling).
- **Run sheet numbers:**
  - The ABX scene's T is max(2.560, 2.582, 2.600) = 2.600 s.
  - Noise gap = ⌈(124800 + 1363)/512⌉ × 512 = 126464 samples; heard gap (126464 − 1363)/48000 = 2.606 s.
  - Speech pause = 0.43 × 2.560 + 2.600 + 0.0284 = 3.729 s.
  - r/r_c 8.46 / 4.74 with D/R −18.6 / −13.5 dB (Kuttruff §5.6 Eq. 5.44, A 343 m²); ᾱ = 319/2200 = 0.145.
  - Comb amplitude √(0.99 × 0.1) = 0.315, giving +2.38 / −3.28 dB.
  - Kuttruff §5.7 Table 5.2: case 5 is 3.06 against 2.99 s, case 4 is 1.21 against 1.38 s. The 14 % report (1.38/1.21 = 1.140) is marked as an inference, in phase-08-4 L141–145.
- **§8 (L4)** matches L4-P, L4-S, L4-D and L4-T, with file 13's corrections and file 14's conditions referenced.
- **phase-08-3 L59–82 (item 15):** faithful to M3-S, D-M3h 2(a)–(e), M3-C 2, 3 and 8, with Seat 4's L5 text verbatim. Applying M1's identity check to E is a faithful reading of file 8, since the specular share is greater than 0.
- **phase-07c-2b item 8:** the one-golden-round exception matches D-M3h 2(d) as corrected.

### The plan-editor's interpretations
| interpretation | ruling |
|---|---|
| The "phase-05b row" is the §0 row | acceptable |
| Item 15 stays in §7; L4 becomes a new §8 | consistent with file 13 |
| The void rule covers AX47 stimuli only | faithful to D-M3h 1. No decision sets a void rule for L4 stimuli, although a t_mix,e or decay-target change also moves L_f and L_p. That is a gap for the decider, not a plan-editor defect. |
| The 08-3 M1 identity check applies to E | faithful |
| "The fallback-B speech null" | **WRONG** (the blocker above) |
| S-A kept as a superseded record | acceptable, but the item-5 clause must carry D-M3f (the major finding above) |
| L4 detection wording "detected (≥ 12/16)" | IMPRECISE (family α 0.038 missing) |

## Ledger
| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| D1-a | DECISION/FACT | L4 failed anchor: void, one rerun | CORRECT (valid) | file 13 items 4, 14; AX49 L172; α 2517/65536 = 0.0384 unchanged if the voided block is discarded | none | Which does the decider pre-register? | open (decider) |
| D1-b | DECISION/FACT | L4 failed anchor: "inconclusive", no rerun | CORRECT (valid); its rationale has CONDITIONS (item 13 sits alongside item 4's rerun) | file 10 L4-D; file 13 items 4, 13; CONSEQUENCE: AX49 reversal unread (L-c debt) | minor | same | open (decider) |
| P1 | NUMBER | L4 "detected (≥ 12/16)" | IMPRECISE | item 13 pattern; family α 0.0384 | minor | State "family α 0.038"? | open |
| P2 | FACT | run sheet §3 item 2: "fallback B … nulled on noise only. Scene E is nulled on speech"; "scene-E null results" | WRONG: B and E are renders | file 10 M3-T; file 4 fact 5; M3-C 7 | **blocker** | Restate as: every sealed scene's B render nulled on speech before the seal | open |
| P3 | FACT | run sheet §1 L35–36: S-A-only "share 0" clause | INCONSISTENT with D-M3f | file 2 D-M3f; file 8 (share 0.022 / 0.001 on E) | major | Replace with D-M3f's text? | open |
| P4 | FACT | 07c-2b scope 2 click_check "Which one … call"; run sheet "no new click at the step" | INCONSISTENT (D-M3a decided form (b)); M3-C 7 pre-seal set absent | files 2, 5 D-M3a; file 8 M3-C 7 | minor | — | open |
| P5 | FACT | AX49 "run with the AX47 ABX in 07c-2"; phases column; 07d L124 | INCONSISTENT (stale phase) | AX47 "(run in 07c-2b)" | minor | — | open |
| P6 | FACT | AX47 Reversal widening and α sentence, n = 2, union ≤ 0.098 | CORRECT | D-M3i, M3-F, M3-S | none | — | — |
| P7 | FACT | AX49 render_cli clause, L4 pointer, ghost print | CORRECT (verbatim) | file 10 L4-W, L4-D 13; file 13 K29 | none | — | — |
| P8 | FACT | L365 settling line; B11 void rule; 05e (b); 07c-2b item 8 exception | faithful | file 10 L4-W; D-M3h 1, 2(d); C-b | none | Void rule for L4 stimuli? (decider gap) | — |
| P9 | NUMBER | gaps 126464 / 2.606 s; pause 3.729 s; r/r_c and D/R; ᾱ; combs | CORRECT | Kuttruff §5.6 Eq. 5.44; arithmetic above | none | — | — |
| P10 | NUMBER | Table 5.2 cases 4 and 5; 14 % marked as inference | CORRECT | Kuttruff §5.7 Table 5.2 | none | — | — |
| P11 | FACT | phase-08-3 item 15 (L5, per-ear rules, M1 identity on E) | faithful | M3-S, M3-C 2, 3, 8; D-M3h 2 | none | — | — |
| P12 | SOFTWARE | §8 flags, refusals and tests by reference | — (not rated) | — | — | — | — |

**Questions, most severe first:**
1. **(P2)** Is the speech null in §3 item 2 to read: "on every sealed scene, the unstepped render B is nulled within −120 dB on every speech stimulus before the seal; the stepped render E already is"?
2. **(P3)** Does §1's item-5 clause carry D-M3f's "[Scenes with s = 1 on every face:] …; on an s < 1 scene M1's reversal condition is live" in place of the S-A-only clause?
3. **(D1)** Rerun or no rerun after a failed L4 anchor? The decider must pre-register one before the L4 seal.
4. **(P1)** Is L4's detection wording to include "family α 0.038"?
5. **(P8)** Should a change to t_mix,e or to the decay target also void sealed L4 stimuli? No surviving decision says so.
