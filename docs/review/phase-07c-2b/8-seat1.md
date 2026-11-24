# 8-seat1: Seat 1, R3 on M3 (skip option, L4 frozen spec)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 1 POSITION (R3 on M3, phase 07c-2b: (a) Seat 7's skip option, (b) L4 frozen-spec-only timing). Read-only; for the orchestrator to save as /home/user/makroof/docs/review/phase-07c-2b/8-seat1.md.

Corpus present (c1b171f); neither matter rests on an acoustic fact.

**1. Reading.**
- (a) After S-W detects at 0.9 dB, should S-B\*'s 0.9 dB blocks be skipped?
- (b) For L4, is a frozen spec in the pre-registration commit as good as stimuli built and sealed before the first scored AX47 trial?
- Cues: pre-registration before data (O1); the hardest condition stays tested (B2); a result that can embarrass me (T1).

---

## (a) Skipping S-B\*'s 0.9 dB blocks after an S-W detection

**A fact the option misses.** Under the run sheet's fixed sequence (L143–145), a 0.5 dB block runs only if 0.9 dB was detected in that chain, and the scoring script refuses to unseal it otherwise. So skipping S-B\*'s 0.9 dB blocks also locks out its 0.5 dB blocks. All of F2 is lost, in exactly the branch where the step is audible.

**Statistics.** A pre-registered conditional skip only removes chances to reject, so the family bounds of ≤ 0.0439 / 0.0453 still hold. The cost is evidence, not α.

**Ranking:**

| option | rank | now | later |
|---|---|---|---|
| Full design, as decided (no skip) | prefer | 0 | 0 |
| **My option (I added it):** after any S-W 0.9 dB detection, both S-B\* chains go straight to their 0.5 dB blocks, each tested once at the chain's own pre-registered criterion, with the same anchors and the same rule for F3/F4 at 08-3 | can live with | 1 | 1 |
| Seat 7's skip as written (0.9 dB skipped, so 0.5 dB is locked) | cannot live with, as written | 2 | 2 |

**What each option costs my seat:**
- **My option, now 1:** a single-family S-W detection has no second family to back it. Because AX47's Reversal fires on one detection, this does not change the bound. It does weaken the record.
- **My option, later 1:** if 07c-2b and 08-3 fall into different branches, item 15's F2/F4 comparison at 0.9 dB is missing, and the record must say so.
- **Seat 7's skip, now 2:** the new 0.5 dB bound goes to O4 tested on S-W only, with no test on the early-part class. Seat 3's debt "s < 1 evidence (F2) before O4" is not repaid.
- **Seat 7's skip, later 2:** a 0.5 dB detection in the s < 1 class (a class (c) finding, run sheet L151) can first appear at 08-3 (F4), after admission. Undoing it costs one sitting of about 1 to 2 h on stimuli that are already sealed.

Hours saved: about 1 h under my option (the 0.9 dB blocks, at Seat 7's [Hyp] pace). Under Seat 7's literal option it is about 2 h, because the 0.5 dB blocks are lost too.

**Condition of acceptance:** Seat 7's skip falls from 2/2 to 1/1 if either (i) it becomes my option, or (ii) the skipped S-B\* blocks are deferred rather than dropped and run before O4. Either way it must be committed before any scored trial.

---

## (b) Frozen spec only, against built and sealed before the first scored AX47 trial

My round-1 worry was that L4's open choices could be bent by the AX47 scores. A frozen spec answers that only if the spec leaves no choice open. As written, it leaves two:
1. **S′'s α values** are found by iterating until T60 is 8.0 ± 0.1 s. The final per-band α values are a choice, not something the spec fixes.
2. **The chord generator's code**, which maps seeds to phases and sets the partial amplitudes, would be written after the commit.

So Seat 7's claim that "the hashes are fixed by the spec" does not hold yet. Determinism also holds only on the same platform (CLAUDE.md, Determinism), so the build platform must be named.

The decider also notes that the prefix-check margin may be thin. Under a frozen spec, a failing check could surface after the AX47 scores are known, and the redesign would then be made with that knowledge.

| option | rank | now | later |
|---|---|---|---|
| Built and sealed before the first scored AX47 trial | prefer | 0 | 0 |
| Frozen spec plus my conditions C1–C3 below | can live with | 0 | 1 |
| Frozen spec as written | can live with | 1 | 1 |

**My conditions:**
- **C1.** The pre-registration commit holds artifacts, not prose: the S′ scene JSON with its final α values (iterated on scene data with `--diagnostics`; no flag needed), the chord generator script, the seeds, the pass rule, the pinned engine commit and the named build platform and toolchain. The flag may follow, since it only calls `Engine::assembleProvisional` within F1–F6.
- **C2.** A pre-registered rule for failed checks. If a check fails after any AX47 score is known, L4 is void for that day and goes back to Seats 1 and 3. It is rebuilt under a new commit recorded as "designed after AX47 scores were known". It is never loosened and never re-specified on the listening day.
- **C3.** The stimulus hashes are committed before L4's own first trial, built on the named platform.

**What remains under C1–C3 (later 1):** a failed check after the scores taints L4 as designed after the data. My seat can track that taint, but the evidence is weaker. Built-and-sealed avoids it entirely.

**Condition to reach 0/0:** run the checks most likely to fail (Seat 1's prefix check and Seat 2's S′ asserts) before the first scored AX47 trial. That is nearly the whole build, so it removes most of what Seat 7 gains.

**Arithmetic for the decider:**
- Built and sealed: Seat 1 0/0, Seat 7 1/0, so max 1, sum 1.
- Frozen spec plus C1–C3: Seat 1 0/1, Seat 7 0/0 (if C1 does not raise Seat 7's cell), so max 1, sum 1.
- That is a tie, to be broken on reversibility. Seat 7 should re-rate under C1.

**Answer to the decider's reversal condition:** I do not rate frozen-spec-only 0/0.

---

**5. Evidence.**
- Fixed sequence, the scoring script's refusal to unseal, and class (c) wording: run sheet L141–151.
- Skipping only removes chances to reject, so the family bounds hold: [Inferred], from the union bound.
- Same-platform determinism: CLAUDE.md.
- Pre-registration integrity: O1 [Inferred]. My persona has no incident on scheduling a pre-registration ([Hyp] for the size of the taint).
- Hours: Seat 7's K6 pace [Hyp].

**7. Hand-offs.**
- Seat 7: hours under my (a) option, and a re-rating under C1.
- Seat 3: whether my (a) option repays its F2-before-O4 debt.
- Seat 5: the scoring script's gate for my (a) option.
- Seats 1 and 3: the C2 failed-check route.

**8. Premortem.** If Seat 7's skip is adopted as written, S-W detects, F2 goes silent, and the 0.5 dB bound reaches O4 untested on the early-part class. Seat 5 is the first to see a 0.5 dB flip at 08-3, after admission.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/6-decider-m3-r2.md
- /home/user/makroof/docs/review/phase-07c-2b/4-seat1.md
- /home/user/makroof/docs/review/phase-07c-2b/4-seat7.md
- /home/user/makroof/docs/review/phase-07c-2b/1-seat1.md (L77–83)
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md (L125–152)
