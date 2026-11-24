# 1: Seat 3 (reverb renderer), M3: the ABX scene, s < 1 timing, K5, click_check

Convened by decider file `docs/review/phase-07c-2/31-decider-abx-r4.md` ("M3: CONVENE") and builder file 32
("Follow-up for the decider"). Run 2026-11-24 in the phase-07c-2b session as `seat3-reverb-renderer`. Recorded
verbatim from the seat's answer.

SEAT 3 POSITION

I read: phase-07c-2b scope 2 (L76–124); decider files 13 (items 6–16), 31, 34 and 40; builder files 29 and 32; my file 26; `tools/ci/abx_kit.py` L365–409; `tools/acoustics/clicks.py`. The corpus was not re-opened. Every claim below comes from the code or the cited files.

**1. Reading.**
- **M3:** which scene or scenes carry the AX47 tail-level ABX, and when an s < 1 scene is run.
- **click_check:** whether the kit's click test is fit to support the seal.
- **Cues from my §4:** (1) the AX47 tail-level step tested on stimuli whose early part is empty (decay accuracy and representativeness); (2) a broadband tick reported on a state change (state discontinuity). Situation 1's anomaly rule applies: if the tick is also there in the unstepped render, the cause is the source, not the change.

**2. Ranking**
- **V1, prefer.** It is the only option with an s < 1 scene run before class (c), W_max and the golden round.
- **V4, can live with.**
- **V2, can live with.**
- **V3, can live with, ranked last.** Layout 5 adds a /fix-plan to AX47 and still has an empty early part.

**3. Tension now**
- **V1: 1.** One more scene through the kit, minutes of compute. Its early part (−3.8 dB re direct, file 29 L30) gives the one-variable contrast with S-A (−76.7 dB, L33).
- **V4: 2.** 07c-2b runs only S-A, the AX21-extreme scene (empty from the direct sound to t_mix). That is my file 26 S-A cell, unchanged.
- **V2: 2.** S-W is an s = 1 placement, so its early part is still empty (file 29 L34–39).
  - If S-W is both_wall, the far emitter's direct burst plays through 29.3 ms of the 30 ms fade (file 32 L52, L60–62). Item 7's "step at a gap start" therefore fails as heard.
  - At 0.1 m from a face, s = 1 renders no wall reflection at about 0.6 ms. My §9 near-surface rule says that tap carries the position, so the stimulus is less like the renderer's output at s < 1, not more.
- **V3: 2.** The same as V2. The M2 premise also fails on layout 5 (file 34 item 3).

**4. Tension later**
- **V1: 1.** 08-3 has no s < 1 binaural scene. Whether the binaural chain needs an early part is Seat 4's call.
- **V2, V3, V4: 2 each.** The s < 1 evidence arrives at 08-3, after class (c) (O10), the W_max pin (O4) and the one golden round (O6), all of which use the 1 dB bound.
  - If 08-3's S-B\* detects a step that S-A or S-W did not, the bound drops to 0.5 dB. The cost of undoing that is a class (c) board round, a possible W_max re-pin, and a second golden round. The umbrella's "one golden round" rule forbids the last of these.

**My "before 08-3".**
- A 07c-2b run meets it.
- An 08-3 run does not. The condition existed so that the decisions that use the bound are not taken on empty-early evidence alone, and those decisions all fall in 07c-2b.

**s = 0.7.**
- s = 0.7 maximises the variable my seat needs, early part present: −3.8 dB re direct at 0.7, against −9.5 dB at 0.9, which is nearly S-A.
- Both values are clean (file 29 L30, L32):
  - specular share 0.032 / 0.004, so the down-step refusal sits near −15 dB, far from any step in the design;
  - s_w 2.5e−5;
  - capped at m = 6, 7 and 8;
  - peak −6.3 dBFS or below.
- Cost at 0.7: ΔG 0.032 against 0.040, and |ΔC80| 0.519 against 0.860. Whether that sensitivity loss matters is Seat 1's to judge.
- Mechanism, from the code: in every gap from t_mix onward, only lags ≥ t_mix contribute, so A/B is exactly g whatever s is. The sensitivity loss is confined to the first t_mix of each gap and to the speech chain. [Hyp] on what that means perceptually. `wet_band_change` should print it for S-B\* and S-A side by side.

**K5: I read both events as false positives, not clicks.**
- Companions (ii) and (iii) show that A is the linear crossfade of B and E within 8u, and bit-identical to B or E outside the fade (abx_kit L388–395). B and E are fixed-IR renders, so A cannot hold a transient that neither of them holds.
- The flagged frame is flagged in B as well (file 32 L71).
- The high-passed peak of A − B inside the fade is below its peak in the 100 ms after it (L74).
- An equal-gain fade is correct here. My S4 "equal power" rule is for uncorrelated states; here E's tail is B's tail × a (the same noise realisation), so the linear fade is a monotone gain ramp from 1 to a.
- Both scenes re-enter the pool. Whether to pick either of them is Seat 1's call.

**click_check: the fix is needed before the seal, in form (b).**
- **Why the current check fails** (abx_kit L406–407): it compares the frame index of each event's peak sample against a median baseline taken from each render separately (clicks.py L92–102). On noise:
  - the step region's frames sit 23.8–30.1 dB above threshold in both A and B (file 32 L105–116), so the check is blind;
  - when A's threshold moves, the grouping changes, so it is also flaky.
- A sealed record that says "clicks clean" would cite a test that cannot see a click there.
- **Form (a)**, per-frame flags with each render judged against B's threshold, fixes the grouping but stays blind under burst frames that are already flagged. At g = +3 it can still flag tail frames near threshold (both_wall's 13 reverberance events in B, L69).
- **Form (b), my pick:**
  - Run `detect_clicks` (absolute floor −90 dBFS) on the residual r = (A − B) − m over [N − 5 ms, N + L + 5 ms]. The model m is (j/L)(E − B) inside the fade and E − B after it.
  - By companion (ii), r ≤ 8u(|a| + |b|), roughly −120 dBFS or below [Hyp: order of magnitude], so it never false-flags. A −70 dBFS spike shows at once.
  - It does not depend on the programme, the baseline or the scene.
  - Keep the old A-vs-B comparison printed but not asserted, for continuity.
- **The one gap (b) leaves:** a transient common to B and E, meaning a convolver artifact. Close it by nulling B and E against the offline render, which is Phase 06's identity.

**5. Evidence.** From the code: abx_kit L384–409 and clicks.py L22–33 and L92–102. From the files: 29 L30–39; 32 L52, L60–74, L105–123; 34 item 2 (click results do not count for M1); 13 item 15 (L205); phase-07c-2b L117–120 and L159. Equal-gain over coherent states is arithmetic. [Hyp]: whether an empty early part biases toward non-detection, and in which direction (Seat 1 to test).

**6. Conditions.**
- **V2, V3, V4 drop to 1 if** 08-3's S-B\* result is written as a reversal trigger for O10 and O4, with the second golden round named as the undo cost. If it detects, the bound is re-decided before the 08-4 freeze.
- **V2 with both_wall:** the onset moves to the heard gap start (N + max direct delay), or the deviation is recorded.
- **S-B\* in any option:**
  - print the per-band share, s_w, the AX21 step at t_mix and `wet_band_change`;
  - run Q5 plus the M2 gap ≥ tail T30 assertion;
  - check clicks with form (b).

**7. Hand-offs.**
- Sensitivity at 0.7 against 0.9, the S-W pick, and α: Seat 1.
- The AX21 step at t_mix for s = 0.7: Seat 2.
- Early part in binaural, and the 0.1 m placements: Seat 4.
- The CI or gate shape of form (b), and the false-detect cost: Seat 5.
- Representativeness of s = 0.7: Seat 9.
- Listening hours: Seat 7.

**8. Premortem.** S-A or S-W is sealed, class (c) and W_max are pinned, and at 08-3 S-B\* detects at 0.9 dB. Then the bound, the admission rule and the goldens all reopen after their one round. Seat 1 notices first, at 08-3.

Files: tools/ci/abx_kit.py, tools/acoustics/clicks.py, docs/review/phase-07c-2/29-k4-candidates.md, docs/review/phase-07c-2/32-k5-k6-clicks-session.md, docs/phases/phase-07c-2b.md
