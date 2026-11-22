# 21 — Decider: the two ABX kit points (item 5 reading; Q5 window, D/R check)

Decider ruling on the two builder points (kit commit 87a62d5). Corpus revision c1b171fe. Neither point needs a seat convened now. Neither point changes the D-W2 pre-registration. Point 2b is a check that must pass before the stimuli are sealed.

**1. What item 5 steps: DECISION, file 13's reading is confirmed.**
- The step is "a change of g dB in tail energy" (file 13, item 5). In the kit that is E'_diff = k·E_diff + (k − 1)·E_spec, with k = 10^(g/10).
- File 5 wrote "E_b·10^(g/10)". That was the round-1 wording, and file 13 superseded it. File 14 rated file 13 SURVIVES.
- Load-bearing reason (D1-L1, derived): item 6 asserts 10·log10(E(stepped − unstepped)/E(unstepped)) = 20·log10|10^(g/20) − 1| over the tail window. That identity is exact only if the whole tail scales by 10^(g/10). File 5's reading would make item 6 fail wherever the specular share is above 0. Only file 13's reading is consistent with the pre-registered assertions.
- On `layout4_s1/default` the specular share is 0 in all 8 bands, so the two readings give byte-identical stimuli. The ABX is unaffected.
- The kit refusing an impossible down-step is correct. It can only arise on scenes the pre-registration does not use, except at 08-3 (item 15) or a fallback to `listener_wall` (item 9). Either of those prints the specular share (item 6) and would refuse rather than distort.
- Wording to add, one sentence, in the run sheet under item 5 and in the PR: "Item 5 scales the whole tail energy (diffuse and specular) by 10^(g/10), as item 6's formula requires; on layout4_s1/default the specular share is 0 in every band, so this equals scaling E_b alone (file 5's wording); the kit refuses a down-step that would need E'_diff < 0."
- Confidence: high (no acoustic claim). Reversal: none expected.

**2a. Q5 onset clustering: within the pre-registration, no amendment.**
- Q5 has two parts:
  - the 0.43·T30 figure is a ceiling, from (46 − 20)/60;
  - the measured assertion governs. File 14, row Q5: "the measured assertion is authoritative".
- The 0.43 arithmetic took the tail level at the end of speech to equal the speech level. It did not subtract D/R. Derived check (D2-L1): (46 − 13.1 − 20)/60 = 0.215·T30, close to the measured 0.187·T30. The early cutoff is therefore what Q5's rule predicts once the actual tail level is used. It is not a malfunction.
- 35 passing boundaries out of 81 is a contiguous early run: 35/81 × 0.43 = 0.186. With the replace-and-record rule, accepted onsets are therefore uniform over [0, 0.187·T30].
- What the speech chain tests is unchanged: a tail step in a speech pause, with the tail ≥ 20 dB above floor. That is the condition Q5 exists to guarantee. The pre-registered power (0.405 at p = 0.75) assumes p and does not depend on the onset distribution.
- Smallest action, which is not an amendment: before sealing, write into the run sheet and manifest the realised window [0, 0.187·T30] and the expected replacement rate (46/81). They are then on record before the run. If 2b changes the scene or T30, recompute both before sealing.

**2b. D/R and T30 against Eyring: yes, check before the run.**
- Corpus: at the diffuse-field distance, direct equals diffuse level (Blauert ch. 3, Fig 3.47 passage). "beyond it reverberation is louder" (Izhaki, critical distance).
- Working (D2-L2): direct level falls 6 dB per doubling of distance (Blauert). At r/r_c = 3.18 the diffuse-field expectation is D/R ≈ −20·log10(3.18) = −10 dB. The kit prints +13.1 dB at 1 kHz, about 23 dB away.
- Item 9 pre-registers both numbers and the label "occupied mid-size hall envelope". One of the two is wrong, or the room is not what the label says.
- Leads from the code, to be checked:
  - `check_scene` computes DRR on the sum of two emitters (ir[:,0] + ir[:,2]). AX13's ±2.5 ms window sees only one direct peak.
  - r_c uses the Eyring T60 (1.291 s), but the IR decays with T30 = 2.009 s.
- Who and how: the orchestrator delegates to the builder (code fact, no seat).
  - Compute DRR per emitter, on single-emitter IRs.
  - Compute r_c from both the Eyring T60 and the measured T30.
  - Report the diffuse-target T60 against the measured T30 for each emitter.
  - The interrogator then checks the reconciliation against the corpus (Kuttruff, critical-distance equation).
- Outcome rule:
  - If it is a print or method artefact: fix the print and run unchanged.
  - If the rendered scene really does have D/R ≈ +13 dB and T30 ≈ 1.56 × Eyring: correct item 9's label, report the T30 gap as a sim finding (NFR-8: report, don't tune), and CONVENE Seats 1, 2, 3 and 9 on whether the scene still serves AX47's "all scenes" bound. Do this before sealing, because a drier-than-labelled scene biases the result toward non-detection.

**Decided for Maisara**
- Item 5 reading and 2a: these are plan readings with no product trade-off. They keep the pre-registered test intact (NFR-1, listening-test thresholds "from the Expert"). No seat gives anything up.
- 2b: checked before the run because NFR-1 requires the render to be verified and item 9 records these numbers. The cost is one builder check.
- AMENDS none of her decisions. No NEEDS MAISARA.

Files: /home/user/makroof/docs/review/phase-07c-2/13-decider-rebuttal-r4.md, /home/user/makroof/docs/review/phase-07c-2/14-interrogator-on-file13.md, /home/user/makroof/tools/ci/abx_kit.py (lines 144–185, 538–608), /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md.
