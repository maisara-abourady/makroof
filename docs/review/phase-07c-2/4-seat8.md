<!-- Saved by the orchestrator from seat 8's report, 2026-11-22. -->

SEAT 8 POSITION: D-W1 and D-W2 (phase 07c-2, round 1). Corpus c1b171f. My persona holds no incident on load or bounce wait times, so every waiting judgement below is tagged [Hyp] or [Inf].

# D-W1: W_max under (C)

**Whose ears.** A producer on headphones builds a hall-class room (20 × 30 × 10 m with an absorbing audience floor: layouts 4/5, the C18 class). She puts 2 to 8 stems in it, automates a source position and bounces the song. She needs one room for every stem, a room that does not change by itself after she presses play, and a bounce that ends without trouble.

**1. Reading.** Which W, and therefore what the bounce costs and how well one room holds together. Cues it triggers:
- cue 10, "where was it judged": the bounce record is on a cube that saturates;
- cue 4: two stems in one hall at levels that differ for no positional reason sound like two rooms (ST4, MSA2).

**Key fact 1: the gated cubes saturate.** From F3/F4 T1 and T3:
- `cube100_lowalpha0.05_s0.3` stops at ×1.26 work from ×2;
- flutter stops at ×3.29 work from ×4.

So any criterion written on "the costliest gated scene" (W-1, W-2, W-3) or on the 100 m s = 0.3 bounce does not bind above ×4. The scenes that keep scaling are the s = 1 cube and layouts 4/5, which are the producer-class halls.

**Key fact 2: the bounce is not W-limited today.** Solve share of the 36-rebuild bounce is 6.1–7.8 % at 48 kHz and 1.6–2.3 % at 96 kHz (F7). The 96 kHz ratio above 1× (0.76–1.36× across runs) comes from synthesis, not from W.

**My bounce term (for W-5).**
- What is measured: the bounce time that W adds, on a 36-rebuild 3-minute position automation, in the costliest capped producer-class scene (layout 4/5 at s = 1), on the worst OS, at the gate's pool size. That is the pool an offline bounce uses (F2), so pool size is the correct basis for this term.
- Limit: the added time is at most 0.25 × real time.
- Also required: the 48 kHz bounce stays at or below 1× real time on every OS.
- At 96 kHz, above 1× is a wait, not a break. The researcher found that VST3 kOffline allows slower-than-real-time processing, and six hosts document no timeout (R14–R20). REAPER, Studio One and freeze are unverified.
- Projection [Inf]: the local container is about 2× slower than CI (part 2, Method). Layout 4 ×16 pool solve is 1.1–1.6 s locally, so about 0.6–0.8 s on CI. 36 × 0.7 s ≈ +25 s, about +0.14× real time, which passes. At one thread, ×16 is about 2.5 s on CI, so about +0.5×, which fails.

| option | label | now / later | reason |
|---|---|---|---|
| W-6 inside W-5 (accuracy need, capped by the binding minimum; my composite) | prefer | 0 / 1 | Layout 4 at ×1: SE 0.47–0.93 dB, U = 1, drift up to 1.25 dB against ×16 (listener_edge). Two stem positions in one hall can then differ by more than the 1 dB jnd of G (Vorländer Table 6.1; R5). At ×8 SE ≤ 0.25 dB and U = 0 outside both-near; at ×16 SE ≤ 0.16 dB. Later: re-pin is one golden round; evidence arrives in 07c-2 CI (3-OS sweep) and 12-2 presets. |
| W-5 | can live with | 1 / 1 | Holds the bounce with my term. Only if W-4's infeasibility is handled (see W-4). |
| W-1 | can live with | 1 / 2 | It does not bind on the gated set (saturation), so in effect it leaves W unbounded for producer halls. Debt: the bounce and settling cost lands in 12-2 or 13 on real projects. |
| W-2 | can live with | 1 / 2 | Same as W-1, at twice the value. |
| W-3 | can live with | 2 / 2 | Up to 3 s per rebuild at pool size: 36 × 3 s = +108 s, about +0.6× real time. A dragged source settles seconds late, and stems sit in different versions of the room meanwhile (ST4). |
| W-4 | can live with | 1 / 2 | The 8-instance 100 m 96 kHz final-settled time is already 9.7–13.3 s at the pin (F6b), before any raise. As a W rule it is either infeasible or pushes toward a cut, which AX38 4c forbids. The lever is synthesis, not W. |
| W-A0 | out of bounds | (2 / 2) | Listed for the record only. Layout-4 halls keep U = 1 and drift above 1 dB. |

**Conditions of acceptance.**
- W-1, W-2, W-3 later 2 → 1: rewrite the criterion on the costliest *capped* producer-class scene (layout 4/5 at s = 1), not the saturating gated cubes, and add my bounce term.
- W-3 now 2 → 1: the same rewrite, plus a pool-size basis no larger than 4 threads. The Steam survey puts ≥ 4 cores at 96–97 %, but its population is gamers (R21).
- W-4 later 2 → 1: record it as a load mark that W does not set, and send it to 07d (synthesis).
- All options: **before pinning, the AX38 4c bounce record is re-run at the chosen W on three OSes.** It must include a layout 4 at s = 1 position-automation bounce. The 100 m s = 0.3 record cannot show W's effect.

**Keyless path.**
- K-a, prefer, 0 / 1: step 0, and the room never changes after play. On a gated cube it adds at most +0.37 s / +5.6 s to 14 × worst (F12).
- K-b, cannot live with if it ships before the ABX, 2 / 2: interim-to-final drift at layout 4 is up to 1.25 dB. She hears "the reverb changes a few seconds after I press play".
- K-c: 1 / 1, unspecified.

I accept the sequencing (value now, keyless path after the ABX, golden round after both), on one condition: K-a stays in force until the class (c) round rules. It already is, from the code (F9).

**Companions.** (b), (c), (d), (g): NOT MY MATTER (Seats 2, 3, 5). (e): either is fine; pre-release, with no producer states yet. (f): no objection; Phase 12 (ii) presets are Seats 6 and 9.

**Hand-offs.**
- Seat 1: whether 0.25–1.25 dB position-to-position drift is heard in a mix.
- Seat 5: pool contention when the DAW renders other tracks in parallel.
- Researcher: freeze in Live and Logic, and REAPER and Studio One offline behaviour.
- Seat 9: which presets fall in the layout 4/5 class.

**Premortem.** If the W criterion is written on the saturating cubes, a beta producer bounces a hall session with automated sources, waits about 1.5× real time, and hears two stems in "one" hall sit about a dB apart. Beta support notices first.

**Workflow requirement most affected:** speed, then the anchor (one shared room for cohesion).

# D-W2: AX47 self-ABX and L4 design

**Whose ears.** She opens the project and presses play. The first thing she listens to closely is the exposed tail: a phrase ends, or the band stops and the room rings (ST5, refuge). If the step falls there, it is in the spotlight, which is the exception to RT8.

**1. Reading.** Program material and context. Cues it triggers: 9 (the maker's detector against the audience's), 10, and S9.

| option | label | now / later | reason |
|---|---|---|---|
| X-5 (X-3 form) | prefer | 0 / 1 | Fixed sequence at 12/16 keeps power: 0.63 at p = 0.75. FWER is 0.0384 (R1, §2a). |
| X-3 | can live with | 1 / 1 | Same procedure, without the power statement. |
| X-1 | can live with | 1 / 1 | One size only; nothing on smaller steps. |
| X-2 | can live with | 1 / 2 | 13/16 misses a real effect 60 % of the time at p = 0.75 (§2a). A false "not heard" keeps the bound at 1 dB, and the step comes back in the class (c) round or 08-3. |
| X-4 | can live with | 1 / 1 | Changes "16 trials"; Seat 7 (listener time). |

**Condition for X-2, later 2 → 1:** add an anchor step of known audibility before the family, as a sensitivity check (BS.1116-3 §6, R4). The anchor is outside the family.

**Sub-items.**
- **Material.** Recorded speech with pauses; the step falls inside a pause or decay, where the tail is exposed. Noise runs continuous, as the sensitivity case. The L4 held chord stays as fixed: an ambient pad in a huge space is a plausible producer moment.
- **Wet or dry.** Fully wet for both AX47 stimuli, the conservative choice, matching the L4 precedent. A context condition with dry signal present is reported only, never gating, and costs no trials from the 16.
- **Speech source.** Prefer a dry, close reader. A reverberant LibriSpeech take puts a room inside the room [Hyp]. Licence is Seat 7's: EARS is non-commercial, so build stimuli locally only if it is chosen (R27).
- **Scene.** The layout-4 hall is a real producer class, so it is a good choice. Seat 9 owns plausibility.
- **Output mode.** Omni or stereo stub on headphones, diotic. Debt: externalised binaural tails may change how detectable the step is [Hyp]. Evidence arrives at 08-3; record a conditional re-run of the ABX there.
- **Listener.** A trained listener (Maisara) is conservative for a bound. The result holds for that listener only (R4).
- **Step direction.** Seats 1 and 2, but it must be the direction the engine produces at load.

**Hand-offs.**
- Seat 1: paradigm, anchor size, the "detected" reading.
- Seat 3: the step is the shipped AQ4 crossfade.
- Seat 4: chain and level matching.
- Seat 7: speech licence and artifact.
- Seat 5: deterministic stimuli.

**Premortem.** If the step sits under continuous program material only, the ABX says "not heard". A producer then hears the hall grow on the first vocal phrase ending after play, the moment she judges depth (WM10). Maisara's own listening notices first.

**Workflow requirement most affected:** transitions with a chosen slope, so that no space changes by itself.

Sources read (all under /home/user/makroof/docs/):
- review/phase-07c-2/1-decider-convening.md
- review/phase-07c-2/2-fact-sheet-part1.md
- review/phase-07c-2/2-fact-sheet-part2-wsweep.md
- review/phase-07c-2/3-researcher-RQ-W1-W2.md
- phases/phase-07c-2.md
- BUILD_PLAN.md (AX47, AX48, AX49)
- review/phase-05h/5-seat8-D-H1-D-H2.md
- review/phase-07c-1b/2-seat8.md
