# 14-seat1: Seat 1 on Seat 9's hand-off (the +9.4 dB onset and the S-W null)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 1 POSITION (R3 hand-off from 8-seat9 §8, required by interrogator file 10 C2). Read-only; for saving as /home/user/makroof/docs/review/phase-07c-2b/14-seat1.md.

**Short answer.** I confirm my V1-W cell at **0/1**. File 5 does not raise it. The onset only changes what the null covers through one quantity, the heard tail share, and item 13 already records that. The wording must add one thing: the heard size of each step. Without it, my later rating becomes 2 (see §6).

**1. Reading.** The question is whether the +9.4 dB own-onset L − R difference on layout4_s1/both_wall changes what an S-W null can be cited for. Cues: a threshold must carry its method and strictness (S4, §2 criterion 1); a null is recorded at the minimum effect it actually reached (T1).

**2. Why the onset does not change the test itself (from the code and file 5) [Inferred]:**
- A, B and X all come from the same scene, tailSeed and engine. A differs from B only by the tail-energy step g with the AQ4 fade. The onsets of 0.165 and 0.380 s are the same in every interval, so they cannot be what the listener tells apart. They do not confound detection.
- The onset matters only because it sets the heard tail share (0.667 at 1 kHz). The share sets how big the step is at the ear: ΔG = 10·log10(1 + s(10^(g/10) − 1)).
  - At g = 0.9 dB: 10·log10(1 + 0.667 × 0.2303) = **+0.62 dB** (file 5 prints +0.621). ΔC80 is −0.90 dB.
  - At g = 0.5 dB: 10·log10(1 + 0.667 × 0.1220) = **+0.34 dB**. This is my arithmetic; the manifest's printed value takes precedence.
  - If L's onset moves to 0.380 s (s ≈ 0.29): 10·log10(1 + 0.29 × 0.2303) = **+0.28 dB** at 0.9 dB. That matches file 5.
- So a null on S-W means "one listener did not detect a heard step of about 0.62 dB (ΔG) at 1 kHz". It does not mean "did not detect 0.9 dB". The same tail step on the same geometry would be less than half as large at the ear once the t_mix,e rule changes.
- **A detection still counts.** It is the shipped engine's output for a valid placement (FR-3D-5). It reverses AX47 for the engine version recorded. M3-8 rebuilds if the rule changes.
- **A null counts only at its heard size.** Item 13 already limits it to its scene class. The onset sentence (C-a) and the commit column then tie it to this engine version.

**3. Tension now.** V1-W with C-a, C-b and the item-13 line: **0**. Nothing changes in the stimuli or the trials.

**4. Tension later.** **1**, as before: S-W's rank rests on ΔG and ΔC80, and 08-3 (i) is a near-wall scene. With the addition below, the onset adds no debt: M3-8 reprints ΔG at any rebuild, and the commit is in the results table.
- **Without the addition: 2.** The results table's "level (dB)" column records 0.9, the tail-step size. A null there would be read at AX47, 08-3 and any later citation as "0.9 dB not detected". The heard step was actually 0.62 dB, and it rests on an engine rule that file 5 shows can halve it. That breaks my criterion 1 (a stated minimum effect).
- Undoing that later means rewording a null that is already on the record. The evidence that would expose it is the M3-8 rebuild, or Seat 2's ruling on the onset.

**5. Evidence**
- The +9.39 dB own-onset difference, −0.05 dB at equal windows, ΔG +0.621 and ΔC80 −0.900: file 5 L21 and L48 (builder measurement).
- The share-to-ΔG formula and the 0.34 and 0.28 dB figures: my own arithmetic [Inferred]. The 0.28 matches file 5.
- That the onset cannot confound A/B/X discrimination: from the code [Inferred]. The onset is a property of the scene, and the step is the only difference between A and B.
- Whether a real room's share would be above or below 0.667: [Hyp]. I cannot settle it because the early part is empty (AX21), so I make no claim in either direction. That question is Seat 9's and Seat 2's.

**6. Conditions (later 2 → 1).** Add the heard step to the S-W null wording (run sheet §6, item 13), as:

> "not detected in 24 trials by one listener (power 0.61 at p = 0.75) on layout4_s1/both_wall (<record line>); heard step at 1 kHz ΔG +0.62 dB, ΔC80 −0.90 dB for the 0.9 dB tail step [0.5 dB: ΔG and ΔC80 as printed in the manifest], at the recorded commit; void as evidence for this scene after a t_mix,e change until rebuilt (M3-8)."

- The same clause goes in 08-3 item 15 (i), with the per-ear values.
- The heard ΔG and ΔC80 at each level are taken from the manifest, not typed by hand.

**7. Hand-offs**
- **Seat 2:** which onset departs from the t_mix,e rule (an NFR-8 candidate; already routed).
- **Seat 9:** whether a real room's share would sit above or below 0.667.
- **Decider:** C2's reversal condition does not fire as long as the wording addition is adopted.

**8. Premortem.** If the null is recorded as "0.9 dB, not detected" without its heard step, Seat 2 then moves L's onset, and the AX47 bound is defended at 08-3 with a null that would now be a 0.28 dB heard step. The first to notice is the M3-8 rebuild's ΔG print.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/5-builder-tail-spread.md
- /home/user/makroof/docs/review/phase-07c-2b/8-seat9.md
- /home/user/makroof/docs/review/phase-07c-2b/4-seat1.md
- /home/user/makroof/docs/review/phase-07c-2b/9-decider-m3-r3.md
- /home/user/makroof/docs/review/phase-07c-2b/10-interrogator-on-file9.md
- /home/user/makroof/docs/review/phase-07c-2b/12-seat1.md
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md
