# 1-seat6: Seat 6 (canvas designer, narrow) on M3's α treatment (phase-07c-2b, round 1)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 6 POSITION (phase 07c-2b, M3: split or unsplit α, read as load time the user sees)

Read: file 31 (M3 convening, answer 4), file 34, BUILD_PLAN §2 AX47 (the "From 07c-2" sentence: a statistical source is admitted only after the self-ABX, and the p95 reading is SE ≤ 0.5 dB → 0.98 dB) and AX38 (iii)/(iv). I also checked my own earlier position (07c-2 file 10, X-5).

**1. Reading.** A false "detected" tightens AX47 from 1 dB to 0.5 dB. That raises the bar for a statistical stage-1 source at load from SE ≤ 0.5 dB to SE ≤ 0.25 dB. Triggered cues:
- Positions that recompute heavily (S3).
- An automatic level step when "settling" clears (W4).
- Silence or a non-detection read as approval (S9).

**2. Ranking.**
1. **Unsplit:** prefer.
2. **Split** (noise ≥ 13 and speech ≥ 13 per scene): can live with.

**3. Tension now.**
- **Unsplit: 1.** The user pays for a false reversal only through load time, and only on a keyless load: a v1 state, or a build that changes E_model. A keyed saved E_b loads at step 0 (AX47 class (a)) whatever the bound. Under the 0.5 dB bound, a statistical stage-1 source needs about 4× the samples (SE ∝ 1/√N; derived, [Hyp] on the real cost). Failing that, it is not admitted, and the keyless load keeps today's synchronous stage-1 (A) final. So the worst case is the load time we already have. Nothing gets worse; a possible gain is lost. A tighter bound also makes the interim-to-final step smaller, which helps trust (criterion 1).
- **Split: 1.** Nothing changes for the user at load.

**4. Tension later.**
- **Unsplit: 1.** The 0.5 dB bound would cost keyless 8 × 100 m loads, which already exceed AX38 (iv)'s 10 s line (19.5 / 16.3 / 23.0 s, 05i). Phase-13 item 3 reads that whatever α is chosen (premise P1). Undoing a false reversal takes one /fix-plan with new ABX evidence.
- **Split: 2.** The noise chain's power at p = 0.75 drops from 0.63 to 0.405, so a real sub-1 dB step is missed 59.5 % of the time instead of 37 %. A miss leaves the 1 dB bound in place, and class (c) then admits a source at SE 0.5 dB. The failure that costs my seat is an audible tail-level jump when "settling" clears on a reopened project (W4; my 07c-2 file 10 reasoning). Evidence arrives at 08-3 binaural, or with beta users in Phase 13. Undoing it means a class (c) re-decision after the source has shipped.

**How V1–V4 bear on it.**
- **V2, V3, V4:** one 07c-2b family at 0.049. The split question does not arise at 07c-2b, and noise keeps 12/16 (power 0.63). They carry no α tension for my seat.
- **V1:** two families. Unsplit gives a union rate ≤ 0.098; split costs power, as above.
- **0.147 (three families):** applies only if the 08-3 families count toward a reversal after class (c) has already admitted a source. In that case a late reversal forces re-admission at SE ≤ 0.25 dB: a re-decision plus extra solve time on keyless loads.

**5. Evidence.**
- Binomial arithmetic and powers: file 31 answer 4 [derived, checked].
- Bound and SE rule: AX47 [plan].
- Load records: AX38 (iv) [plan record].
- 4× work for half the SE [derived; the real stage-1 cost is Seat 2's and Seat 5's to measure].
- The added option's arithmetic [derived by me]. With 24 noise trials, P(≥18) = 190051/16777216 = 0.0113 under the null, and power at p = 0.75 is ≈ 0.607 (summed pmf). Adding speech ≥ 13 (0.0106) gives 0.0219 ≤ 0.0245.

**6. Conditions of acceptance.**
- **Split, 2 → 1 (option added by me).** Each scene's noise chain runs 24 trials at ≥ 18 (power ≈ 0.61) and speech stays 13/16. Per-scene α is 0.0219. This changes a trial count, so it needs Seat 1 (design) and Seat 7 (+8 noise trials per scene, in hours).
- **Unsplit, to hold its 1:**
  - (i) The record states the union rate, and which family detected at what count.
  - (ii) The AX38 (iv) records print the keyless time-to-audible under the bound in force, so the load-time cost is measured, not assumed.
  - (iii) "Settling" is shown through any keyless load (AX38 (iii)).
  - (iv) A speech non-detection never cancels a noise detection (file 10, condition 1).

**7. Hand-offs.**
- Seat 1: the family structure and pre-registration, and whether 08-3 families count toward a reversal after class (c) admission.
- Seat 5: the solve time of a stage-1 source at SE 0.25 dB against 0.5 dB.
- Seat 7: the hours for the 24-trial variant.
- Seat 2: whether any statistical stage-1 source reaches SE 0.25 dB within W_max.

**8. Premortem.** If split wins and the step is real, the noise chain misses it, class (c) admits a 0.5 dB-SE source, and a producer reopening a large-room project hears the tail jump when "settling" clears. A beta tester notices first.

Read-only. To be saved as /home/user/makroof/docs/review/phase-07c-2b/1-seat6.md.
