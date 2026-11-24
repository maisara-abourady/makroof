# 1-seat3: Seat 3 (reverb renderer) on M3, V1–V4 and click_check (phase-07c-2b, round 1)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 3 POSITION

Read: files 28, 29, 31, 32, 34, 40, my file 26, `docs/phases/phase-07c-2b.md` scope 2, and `tools/ci/abx_kit.py` (`ir_assertions` L264–297, `midfade_checks` L365–396, `click_check` L399–409), plus `tools/acoustics/clicks.py`. I did not open the corpus. The acoustic claims below come from the code or from the builder's measurements. Arithmetic that is my own is marked `[Hyp]`.

**1. Reading.** Two questions:
- **M3:** which scenes carry the AX47 self-ABX in 07c-2b and at 08-3.
- **K5 and `click_check`:** is the kit's click gate fit to seal on?

Cues from my §4 that apply:
- State discontinuity (the step's fade path).
- The empty early part at s = 1, where my rule "test the step on a stimulus the renderer actually produces" fails.
- A listener or emitter 0.1 m from a face. My §9 says the shared-late-field rule weakens there.

**My answers to the brief**
- **"Before 08-3".** A 07c-2b run of S-B\* meets it. That run sits in scope 3, before class (c) (O10), the W_max pin (O4) and the golden round (O6). An 08-3 run does not meet it. A detection on S-B\* at 08-3 would tighten the bound after W_max and the goldens are already pinned, so O4–O6 reopen: a re-pin plus a second golden round, roughly a phase of rework. At 08-3 the condition is met only in a weak form: a registered reversal.
- **s = 0.7, with 0.9 as can live with.**
  - At s = 0.7 the early part is −3.8 dB re direct; at s = 0.9 it is −9.5 dB (file 29). So 0.7 is the renderer's ordinary state, while 0.9 sits close to S-A's empty-early pathology.
  - The AX21 envelope jump at t_mix grows with s. My file-26 estimates were 1.8, 4.9 and 8.7 dB at s = 0.1, 0.25 and 0.4; extending that trend to 0.7 and 0.9 is `[Hyp]`.
  - Both values pass my file-26 conditions:
    - target share 0.032 and 0.004 (limit ≤ 0.50);
    - s_w 2.5e−5 and 2.8e−8 (limit ≤ 2.3 %);
    - capped at m = 6, 7 and 8;
    - item 6 passes at every g.
  - What 0.7 gives up is sensitivity (ΔG 0.032 against 0.040 dB; |ΔC80| 0.52 against 0.86 dB). That is Seat 1's to weigh.
- **K5.** I accept file 32: both events are false positives and nothing goes to NFR-8.
  - Companions (ii) and (iii) put A within 8u of the crossfade of B and E, and bit-identical to them outside the fade. So no transient can be in A that is absent from both fixed-IR renders.
  - A−B has no peak inside the fade.
  - At both_wall frame 1745, A sits between B and E (−34.43 against −36.70 and −33.97 dBFS).
  - Both scenes go back into the pool, once the check below replaces the current one.
  - A fact for the record: the near emitter's 5 ms burst fade-out (N − 208 to N + 32) always lies inside the step region. So the detector sits on a burst edge in every stimulus. S-A passed by peak-frame coincidence, 23.8 to 30.1 dB above threshold, not because it was clean.

**2. Ranking**
- **V1: prefer.** It is the only option with s < 1 evidence before O4. I rate it the same if its s = 1 family is S-W rather than S-A (variant **V1-W**, my addition, offered because it may lower Seat 1's tension).
- **V3** (with layout5_s1/default), **V2**, **V4: can live with**, in that order.

**3. Tension now**
- **V1: 1.** S-B\* still has to be built and pass Q5. S-A's empty early part is offset by the s < 1 family.
- **V2: 2.** The only scene in 07c-2b has an empty early part and sits 0.1 m from a face, a physically incoherent stimulus: a wall with no wall reflection.
- **V3: 2.** layout5/default removes the near-wall concern, but the early part is still empty.
- **V4: 2.** This is file 26's S-A rating. My condition was "an s < 1 rerun before 08-3", and V4 puts it at 08-3.

**4. Tension later**
- **V1: 1.** At 08-3 the binaural reruns of S-A and S-W are both empty-early (Seat 4's). The s < 1 omni evidence already exists by then.
- **V2, V3, V4: 2 each.** The first s < 1 result arrives at 08-3, after O4 to O6. If it detects, the W_max re-pin and golden round are redone. Evidence for that arrives at the 08-3 ABX.

**5. Evidence**
- Scene figures: file 29's table and facts 2, 4 and 5.
- K5 figures: file 32's tables.
- The IR-level guards, from the code: `ir_assertions` asserts:
  - the early part bit-identical up to t_mix − 2.5 ms;
  - diff_db within 0.01 dB on the tail alone;
  - s_w ≤ 2.3 %.
- The mechanism of the false events, from the code: `click_check` compares the frame of each event's peak sample, and each render is judged against its own median threshold (clicks.py L92–102).

**6. Conditions of acceptance**
- **V2, V3 and V4 drop to 1 later** if S-B\* moves into 07c-2b (V2 or V3 then becomes V1-W). The alternative is that O4's decision names "an S-B\* detection at 08-3" as its reversal, with the re-pin cost in the debt register; that only makes the debt visible, so it stays at 2.
- **Any S-B\* scene:**
  - the AX21 step at t_mix is printed;
  - M1's reversal condition is live, since the share is above 0;
  - file 34's "[S-A only]" clause is marked as not applying;
  - Q5 is rerun at heard T30 1.831 s (s = 0.7).

**`click_check` (joint with Seat 5): yes, it must change before the seal, and to option (2) in a model form**

How I rate the three options:
- **Option (3), keep as is: cannot live with, 2/2.** It drops scenes on false events (about 1 stimulus in 10 per scene, K4), and its pass is coincidental.
- **Option (1), literal: 1/2.** Judged against B's threshold, an up-step (+3 dB anchors) lifts reverberant frames near the threshold over it. B already flags 13 such frames in both_wall. So the same kind of false event comes back. That the rate is non-zero is `[Hyp]`.
- **Option (2), literal: 2/2.** A−B is 0 before N, so the −90 dBFS floor sets the threshold and the scaled tail itself is flagged (12 to 13 events per stimulus).

**What the changed check asserts (call it HF-W).**
- Let h be `clicks.highpass` (2 kHz, order 8, zero-phase).
- Use frames of n_f = round(2 ms·fs) samples, aligned to N, over [N − 5 ms, N + L + 5 ms), on every output channel.
- For each frame, compute E_o = Σh(o)², E_a = Σh(a)² and E_b = Σh(b)², with b the stepped IR rendered alone (as in `midfade_checks`).
- Skip a frame, and count it, when max(E_a, E_b) < n_f·10^(−9).
- **Assert E_o ≤ β·max(E_a, E_b)**, with β = (1 + n_f/L)²(1 + 1e−5). At 48 kHz that is 1.138, or 0.56 dB. This is the W-a derivation applied to the high-passed signals.
- Print the worst ratio and the margin per stimulus. The detector's events on o and a are printed for information only and not asserted.
- If any clean stimulus fails, report it. Never loosen β by fitting it to the data.
- The commutator of h with the 30 ms ramp is taken as negligible. That is `[Hyp]`: the builder confirms it on the 50 S-A stimuli and the two K5 stimuli.

**What makes it fail, as negative controls in `pytest tools/ci`:**
- **(N1)** A single-sample spike added to o at N + L/2, sized so that its frame's E_o is 3 dB over β·max. HF-W must fail.
- **(N2)** The linear fade replaced by a hard switch at N + L/2, and **(N3)** the fade quantised in 32-sample steps. Companion (ii) must fail on both.

Division of labour:
- Transients in the runtime fade path are caught exactly by (ii) and (iii).
- Transients in the stepped IR are caught by `ir_assertions`.
- HF-W catches any broadband excess over both endpoints without false positives.
- `[Hyp]`: on a noise programme, a step-sized discontinuity is about 16 dB under the frame's high-frequency energy, so no frame detector replaces (ii).

**7. Hand-offs**
- Sensitivity, the α split and the S-W pick: Seat 1.
- The AX21 jump at s = 0.7 and 0.9, and layout-5 provenance: Seat 2.
- The binaural reruns and the 0.1 m placements: Seat 4.
- CI plumbing for HF-W: Seat 5.
- Listening hours for two families (about 4 h, K6): Seat 7.
- Labels and the 0.43 ceiling: Seat 9.

**8. Premortem.** If V2 or V4 runs and the S-B\* rerun at 08-3 detects the step, AX47's bound tightens after W_max and the goldens are pinned. Seat 1 sees it first at 08-3, and 07c-2b's O4 to O6 are redone.

Files:
- /home/user/makroof/tools/ci/abx_kit.py
- /home/user/makroof/tools/acoustics/clicks.py
- /home/user/makroof/docs/review/phase-07c-2/29-k4-candidates.md
- /home/user/makroof/docs/review/phase-07c-2/32-k5-k6-clicks-session.md
- /home/user/makroof/docs/phases/phase-07c-2b.md
