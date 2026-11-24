<!-- Saved by the orchestrator from seat 1's report, 2026-11-22. -->

SEAT 1 POSITION: D-W1 and D-W2 (phase 07c-2, round 1)

Corpus present (SOURCE_COMMIT c1b171f). The yardstick has not changed: the G jnd is 1 dB at 500–1000 Hz (Vorländer Table 6.1, `docs/corpus/vorlaender-auralization.md` L2056–2060; paradigm not stated). My floor is AX38 4c: SE ≤ 0.33 dB per emitter and band, plus one of clauses (a)–(d). Clause (d) is replicate p95 ≤ 1 dB. Escalation is defined at the gated scenes and by the p95 of the s = 1 cube. None of my persona's assumptions falls this round.

---

## D-W1: W_max under (C)

**1. Reading.** D-W1 sets the shipped per-emitter work cap. My measure is the achieved SE, VOV and p95 at each capped class, from the F4 sweep. Cues triggered:
- S4: a borrowed threshold. Table 15.1 gives VR update intervals, not a solve budget (researcher R29).
- S6: spend where the curve is steep.
- §17 failure library: quoting a number without its method.

**What the sweep says in my units** (F4, T3 and T4; Linux; one local machine) [Observed]:
- **Gated low-α s0.3 cube.**
  - ×1: SE 0.092 / 0.075 dB, p95 0.254 / 0.179 dB.
  - From ×2 the estimate is saturated and uncapped: p95 0.157 / 0.158 dB.
  - The floor is met at every W via (d).
- **Flutter cube.** SE ≤ 0.002 dB. Met via (a) at every W.
- **s = 1 cube.**
  - ×1: SE 0.360 dB. Floor not met; this is my standing "now 2".
  - ×2: SE 0.287 / 0.251 dB, but the e0 final-range VOV is 0.117, so no clause is shown. **Unproven.**
  - ×4: SE 0.186 / 0.183 dB, band VOV 0.093 / 0.050. **Met via (c).**
  - ×8: SE 0.134 / 0.123 dB.
- **Layouts 4/5 at s = 1, not both-near.**
  - ×4: max SE 0.43 dB (layout 4 listener_corner).
  - ×8: every placement ≤ 0.254 dB.
  - ×16: ≤ 0.164 dB.
- **Both-near e0** (layout 4 both_wall and both_corner, layout 5 both_wall).
  - At ×16: SE 0.50–1.23 dB, VOV_union 0.41–0.55, U = 1 at every W.
  - **No W fixes these cases.** The fault is in the variance estimate, and the remedy is outside the scope of 07c §9.

**2–4. Ranking and tension.** The multiplier each option implies is [Inferred]. It uses single-thread cost per scene evaluation: 44–56 ns on Linux, the worst OS (05h, F2).

| option | implied W | label | now / later | reason |
|---|---|---|---|---|
| **W-6′ (mine)** | ×8 on the sweep grid | **prefer** | 0 / 1 | Smallest W at which (i) the floor holds with a clause at the gated cubes and the s = 1 cube, and (ii) SE ≤ 0.33 dB at every layout 4/5 placement except both-near. Later 1: both-near stays uncertified whatever the W. |
| **W-1**, read on a scaling scene | ≈ ×8–11 | **prefer** | 0 / 1 | Agrees with W-6′. Read on the gated scenes it never binds, because they saturate at 1.25× and 3.29× the pin's work (T1). |
| W-2 | ≈ ×17–22 | can live with | 0 / 1 | Takes layout SE from ≤ 0.25 to ≤ 0.16 dB, a gain of about 0.1 jnd where the curve is flat (criterion 6). AX38 4c forbids cutting W once pinned, so too high a pin cannot be undone. |
| W-3 | ≈ ×30+ | can live with | 0 / 1 | Same as W-2, with a larger risk of a pin that is stuck too high. |
| W-4, as a derivation | ill-posed | can live with only as a check | 2 / 2 | The settle time is dominated by synthesis. It is already 9.9–13.3 s at the pin, at 96 kHz with 8 instances (F6b). It cannot bind W, except down to (A), and (A) fails at the s = 1 cube. |
| W-5 | min of its terms | can live with if ≥ ×4 | 0 / 1, or 2 / 2 if < ×4 | The bounce is W-insensitive at the saturating cubes: the solve is 1.6–7.8 % of the bounce (F7). A W-insensitive term must not set W. |
| W-6, as worded | unsatisfiable | can live with only reworded as W-6′ | 2 / 2 | "Every reported capped class" includes both-near, which fails at every W up to ×16. |

**Keyless consequence.** It is the same for every option.
- **K-a: 0 / 0.** Stage-1 is the final, so the step is 0. From the code (F9), this is what the raise produces anyway.
- **K-b unconditioned: 2 / 3.** The (A)-to-final steps measured as drift against ×16 at ×1 exceed AX47's 1 dB bound whatever the ABX shows:
  - layout 4 listener_edge: 1.15 / 1.25 dB;
  - layout 5 emitter_wall: 1.32 dB;
  - layout 5 both_wall: 2.2 dB;
  - layout 4 both_corner: 3.72 dB.

  These steps fall at L1, the load followed by play.
- **K-c: unrated** until someone states it.

**Sequencing.** I accept the order: the value now, the keyless path after the ABX, and the golden round after both. My condition is that the code stays at K-a until the class (c) round, which it does (F9).

**Debt.**
- W-6′ or W-1 commits 08-4, 12-2 and the golden round to roughly ×8. Undoing it upward costs a parameter change and a golden round. Undoing it downward is forbidden (AX38 4c).
- Evidence arrives in two places: the 07c-2 CI run at three OSes (the SE should be near-identical across OSes, since the work count is cross-platform [Inferred]), and Seat 9's capped presets in 12-2.

**6. Conditions.**
- **W-4, W-5 and W-6: 2 → 1.** No term that is insensitive to W may set W, and W-6 is reworded as W-6′.
- **W-6′ or W-1 at the chosen pin, before the golden round:**
  - the 30-replicate p95 at the s = 1 cube must be ≤ 1 dB. This is its escalation line, and it has not been measured at any W.
  - a three-OS CI print of SE and VOV at the pin.
- **If the pin lands between ×2 and ×4:** clause (d) replicates at the s = 1 cube are required. Otherwise the floor is not met and the matter escalates to Maisara.
- **K-b: 3 → 1.** The (A) interim is admitted only per scene, where SE(A) ≤ 0.5 dB and VOV < 0.1. Every other scene falls back to K-a.

**Companions.**
- (b) and (c): not my matter (Seats 2, 3 and 5).
- (d): the prefix fails at work-stopped fixtures (F11). This matters to me only through K-b step sizes and the stream checks. Seat 2.
- (e): keep v2. The cost is one keyless load with step 0. 0 / 0.
- (f) and (g): not my matter.

**7. Hand-offs.**
- Seat 2 and the interrogator: the F3 claim that "this container is about 2× slower" compares local cost per scene evaluation with CI `nsPerEval` values that count the work twice. Local single-thread cost is 43–58 ns; the 05h CI Linux figure is 44–56 ns. This looks like the double count resurfacing. F12 is unaffected.
- Both-near variance: a board matter after 07c (Seat 2).

**8. Premortem.** A bounce or settle term that is insensitive to W pins W at or below ×2. The s = 1 cube then ships with no floor clause, and Seat 9's Phase 12 hall presets show layout-class SE of about 0.4 dB. Nobody escalates it because the term "passed".

---

## D-W2: the AX47 self-ABX and the AX49 L4 design

**1. Reading.** This sets the paradigm, the strictness, the family and the power before any person listens. Cues triggered:
- the claim's five items (listener, blinding, level, signal, reference);
- B2, the hardest signal;
- T1, per-listener results and the system floor;
- "a null result is weak at n = 16".

I read AX47's "16 trials" as 16 scored trials per test, that is, per stimulus.

**2–4. Ranking.**

| option | label | now / later | reason |
|---|---|---|---|
| **X-5′ (mine)** | **prefer** | 0 / 1 | Spelled out in my design below. Later 1: a null result has power 0.63 / 0.41 at p = 0.75. |
| X-5 with Holm (13 then 12) | can live with | 0 / 1 | FWER 0.021. Spends α on speech that weighted Bonferroni gives to noise. |
| X-3 over sizes within a stimulus | can live with | 1 / 1 | Run across stimuli it is useless: speech is tested only after noise has already triggered the reversal. |
| X-2 | can live with | 1 / 2 | Needs 13/16 or 14/16 per test. Miss probability at p = 0.75 is 0.60–0.80. Sizes below the decision point change no decision. |
| X-4 | can live with | 1 / 1 | This is the threshold method I trust (T1), but it answers a different question from the binary bound and needs a board DECISION to change "16 trials". |
| X-1 uncorrected | can live with | 2 / 1 | FWER 0.0753 > 0.05 (researcher §2a). The strictness is misstated. |

**My design, X-5′:**
- **Size.** One pre-registered size: 0.9 dB, the largest step below 1 dB. AX47 lets steps up to 1 dB ship, so testing at 0.75 dB would leave the steps from 0.75 to 1 dB untested.
- **Family.** {pulsed pink noise, recorded speech}, combined by weighted Bonferroni.
  - Noise needs ≥ 12/16 (α 0.0384); speech needs ≥ 13/16 (α 0.0106).
  - FWER = 1 − 0.961594 × 0.989365 = 0.0486 ≤ 0.05, one-sided. I redid this arithmetic.
  - Noise gets the larger share because it is the sensitive stimulus: Zotter & Frank §4.8 report audible differences below 0.5 dB in noise (corpus, via researcher R8).
- **Continuation.** Only if a stimulus detects at 0.9 dB, that stimulus's α passes to a 0.5 dB test, which challenges the reversal bound itself. Whether this holds FWER as a graphical procedure is **for the researcher to verify** [Inferred].
- **Power statement, pre-registered.** At p = 0.75, P(detect) is 0.630 at 12/16 and 0.405 at 13/16.
- **Positive-control anchor (BS.1116-3 §6, researcher R4).**
  - 6 interleaved trials at a 3 dB tail step; 3 dB is "easily perceived" per Toole §19.1.1 (R7).
  - Required: ≥ 5/6. Chance gives 0.109; at p = 0.95 the pass rate is 0.967.
  - If the anchor fails, the block is void and is rerun once. A non-detection is never a reason to rerun.
- **Familiarisation.** Feedback during familiarisation only, never in scored blocks.

**Sub-items (mine):**
- **Step.**
  - Tail only, uniform across all 8 bands, which is the worst case.
  - Rendered as the shipped AQ4 crossfade (Seat 3 confirms the law).
  - Direction balanced: 8 up and 8 down per block, in random order. Up and down counts are descriptive only.
- **Reference.**
  - B is the pre-step IrSet held throughout ("the final never lands").
  - The step time is randomised within a fixed window per trial, and X = A shares it.
  - Each interval plays whole, with no time-aligned looping. Otherwise the test collapses into a static 0.9 dB level comparison [Inferred].
- **Signals.**
  - Pulsed pink noise, so the tail is exposed in the gaps (B2, T1).
  - Recorded speech with the step inside a pause (my D-B3 condition C).
  - Fully wet.
- **Chain.**
  - Headphones, the target chain, for both AX47 and L4.
  - Model and level recorded, and the level fixed.
  - No level matching after the step: the step is the variable.
  - Mode: Seat 4's call.
- **Listener.** One pre-registered decision listener. Any further listener is pre-registered and splits α by Bonferroni. Results hold for that listener only (BS.1116 §3.3).
- **Blinding.** The trial key is generated from a seed whose hash is committed before the run. Answers go to a file, and a script does the scoring.
- **Sessions.** BS.1116-3 §4.2 allows 10–15 trials per session, and a block is 22 trials. Insert a break at trial 11.
- **Record.**
  - Per listener and stimulus: k/16, the exact p, anchor k/6, size, scene, seed, stimulus hashes and the pre-registration hash.
  - Wording: "detected (≥ c/16, family α 0.049)" or "not detected in 16 trials (power 0.63 / 0.41 at p = 0.75)". Never "inaudible", and no public wording (Seat 7).
- **What "detected" licenses.** The 0.5 dB bound for all scenes (asymmetry rule).
- **L4.**
  - It is its own family, since it carries a separate reversal: 12/16 as fixed.
  - The held chord is released into at least L (12 s) of silence, so that the tail past L_f is exposed.
  - Same chain and same blinding tool as AX47.

**Debt.**
- A false null leaves the 1 dB bound standing over the class (c) admission, the 08-3 and 09 stream checks and the goldens. Undoing it means a bound change, a −24.55 dB check and possibly a golden round.
- The first evidence arrives at 08-3: binaural may change how audible the tail is [Hyp]. So I add a condition that the ABX is rerun on the binaural chain at 08-3, before 08's goldens freeze. Otherwise the evidence arrives in Phase 13's beta.

**6. Conditions.**
- X-1: 2 → 0 with any FWER control at or below 0.05.
- X-2: later 2 → 1 by keeping only the first size in the family.

**7. Hand-offs.**
- Seat 2: which capped layout-4 placement (still capped at ×8).
- Seat 3: the crossfade law and the window.
- Seat 4: the mode and the diotic chain.
- Seat 7: the speech licence. LibriSpeech is CC BY 4.0; EARS is non-commercial, so it is out.
- Seat 8: the chord material.
- Researcher: the graphical-procedure FWER.

**8. Premortem.** An uncorrected or underpowered null, run on dense or continuous material with no anchor, keeps the 1 dB bound. Class (c) then ships about 0.9 dB tail steps at load, and the first to notice is a producer on a vocal track with a reverb-heavy room, in the beta.

Files read: `/home/user/makroof/docs/review/phase-07c-2/1-decider-convening.md`, `2-fact-sheet-part1.md`, `2-fact-sheet-part2-wsweep.md` (L1–313), `3-researcher-RQ-W1-W2.md`; `/home/user/makroof/docs/BUILD_PLAN.md` (AX38 4c floor text, AX47, AX48, AX49); `/home/user/makroof/docs/review/phase-05h/5-seat1-D-H1-D-H2.md`; `/home/user/makroof/docs/review/phase-07c-1b/7-seat1-r2-signal.md`; `/home/user/makroof/docs/phases/phase-07c-2.md` (scope 9); `/home/user/makroof/docs/corpus/vorlaender-auralization.md` (Table 6.1).
