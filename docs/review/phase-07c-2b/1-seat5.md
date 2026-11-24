# 1-seat5: Seat 5 (deadline keeper, narrow) on M3's α treatment and click_check (phase-07c-2b, round 1)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 5 POSITION

(Read-only. I wrote no file. The orchestrator saves this as docs/review/phase-07c-2b/1-seat5.md.)

**1. Reading.**
- **(1)** How α should be handled across the ABX families when a detection reverses AX47 to 0.5 dB.
- **(2)** Whether `click_check` must change before the seal.
- **Cues triggered.** §4.5: what crosses into the restore path when the admission SE target moves. §9: treat any race or flake as a reproducibility bug. §17: my own over-weighting of tooling, and a gate that passes by coincidence.
- **My stake.** This is not the callback. A false reversal costs load time on the restore thread, plus re-pin work under AX38 4c.

**2. Ranking.**

Question 1, α:
- **Split:** prefer.
- **Unsplit** (each scene its own family; union ≤ 0.049 × families): can live with, on condition C1 below.

Question 2, `click_check`:
- **(a) Per-frame flags against B's threshold:** prefer. Flags in A within the step region must be a subset of the flags in B or E, judged against one fixed threshold taken from B. No event grouping, no peak-sample identity.
- **(b) A − B against the crossfade model, asserted:** can live with.
- **None, keeping today's peak-frame comparison as an assertion:** cannot live with for any scene other than S-A.

**3. Tension now.**
- **Unsplit, 1.** V1 (two families in 07c-2) puts P(false reversal) at the time of admission at 2517·2/65536 + 697·2/65536 = 0.098, against 0.049. The cost if it lands: SE ≤ 0.25 dB in place of 0.5 dB, which is 4× the histories (N ∝ SE⁻², AX41 N_need) for a stage-1 estimate above the pilot floor. Under V2, V3 and V4, 07c-2 has one family, so the rate at admission stays 0.049 and the cell is 0.
- **Split, 0.** Its cost is power, which is Seat 1's ground.
- **(a), 1.** A kit change plus a test that proves it is not vacuous.
- **(b), 1.**
- **None, 1 on S-A.** It passes 50 of 50, deterministically, but by coincidence of peak frames (file 32).

**4. Tension later (the debt).**
- **Unsplit, 2.**
  - Under V4, three families can each reverse AX47 (07c-2 S-A, then 08-3 (i) and (ii)): union 0.147. Under V1 there are up to four.
  - The 08-3 families run after a statistical stage-1 source may already have been admitted at SE 0.5 dB.
  - A flip at that point changes the restore path's work. That means an AX38 4c re-pin (≥ 3 green runs per OS, with a CHANGELOG reason), and possibly a fail of 14 × worst ≤ 30 s at the gated 100 m builds `[Hyp]`: 4× stage-1 work there was never measured.
  - In practice a reversal is one-way: undoing a false one takes a fresh ABX, which costs Seat 7 listening hours.
  - The evidence arrives at 08-3.
- **Split, 1.** The false-flip channel halves (0.0245 per family). Lower power makes a true effect more likely to surface late, at 08-3, at the same re-pin cost `[Inferred]`. That flip is correct, and I do not resist it.
- **(a), 0.** One fixed threshold makes the check stable under the sub-dB baseline moves that regrouped 97 of 182 events in file 32.
- **(b), 1.** The margin is empirical (−0.6 dB on both_wall), so a future scene could go red with no defect.
- **None, 2.** It went red falsely on 2 of the 17 K4 candidates, and every new scene or re-seal (S-W, S-B\*, 08-3) risks another false red and another builder round like K5.

**5. Evidence.**
- **Bonferroni arithmetic, redone.** 2517/65536 = 0.0384 and 697/65536 = 0.0106, total 0.049. ×2 = 0.098; ×3 = 0.147 (file 31, answer 4). Powers 0.630 and 0.405 are quoted from file 31.
- **Work ratio** `[Inferred]`, from AX41 N_need ∝ (SE_pilot/SE_target)² and AX42 SE_target 0.083 dB:
  - final over stage-1 = (0.5/0.083)² ≈ 36 at the 1 dB bound;
  - (0.25/0.083)² ≈ 9 after a reversal;
  - no cost where the pilot alone (n\* ≤ 1 024) already reaches SE ≤ 0.25 dB. AX42 records 0.017–0.086 dB at the Phase 04 default placements.
- **Re-pin rule:** AX38 4c, "re-pinned only when the restore path changes … ≥ 3 runs".
- **Click mechanism and counts:** file 32 (K5). The companions (i)–(iii) prove that A is the crossfade of B and E to within 8u, so the kit cannot add a transient that is absent from both B and E (file 32, from the code, `midfade_checks`).
- **Corpus:** not consulted. No acoustic fact is load-bearing in this position.
- **For the researcher:** none.

**6. Conditions of acceptance.**
- **C1 (unsplit, later 2 → 1).**
  - The board declares which families can reverse AX47.
  - If any family runs after admission, 07c-2 builds the admitted stage-1 source with SE_target as one named constant (AX47-cited).
  - 07c-2 also prints the AX38 4c restore record with the 0.25 dB branch at the gated builds, so that a late flip is a constant change whose cost is already measured, not a discovery.
  - Alternatively: no statistical source is admitted until every family that can reverse AX47 has run.
- **None → acceptable (1/1)** only if `click_check` is demoted to a printed record and the PR names companions (i)–(iii) as the assertion of record.
- **What any asserted form must hold, for CI and determinism:**
  - It is a pure function of the sealed WAVs: SHA-256 checked against manifest.json, float64, no RNG, no clock.
  - The threshold is pre-registered and comes from B; the margin is printed per stimulus.
  - It is non-vacuous: a pytest under `tools/ci` injects a known click into A inside the fade and asserts the check fires, then asserts that the same check passes on an unmodified stimulus.
  - It runs on the platform that generated the kit.
  - A red is a stop: never a re-run, never a widened threshold.
- **(b) → 0 later** if its margin is pre-registered before any new scene is seen.

**7. Hand-offs.**
- What counts as detection, power, and whether a binaural 08-3 family may reverse an omni bound: Seat 1 and Seat 4.
- Whether the crossfade's A − B transition is audible, and whether (b) should be asserted: Seat 3.
- Listening hours for any confirmatory rerun: Seat 7.
- Load time as the user sees it: Seat 6.

**8. Premortem.** If unsplit families keep running into 08-3 after a statistical stage-1 source has been pinned at SE 0.5 dB, one false binaural detection forces 4× stage-1 work, and the first to notice is the AX38 4c GATE line printing OVER30S at the gated 100 m builds.
