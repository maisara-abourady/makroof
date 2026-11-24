<!-- Saved by the orchestrator from the decider's report, 2026-11-22. -->

# Phase 07c-2 board loop, round 1: CONVENING (decider)

To be saved as `docs/review/phase-07c-2/1-decider-convening.md`.

## 0. Precondition: the corpus is not present

`docs/corpus/` is missing (Glob `docs/corpus/*` and `docs/corpus/**` return nothing). **Corpus not present: run `tools/ci/fetch_corpus.sh`.** Do this before the seats run, because they cite the corpus too.

This convening states no acoustic fact. Every acoustic item below is marked as needing the corpus. The decision round will not start until `docs/corpus/SOURCE_COMMIT` can be stated. The last revision cited in the plan is c1b171f.

## 1. PRD digest

- **For whom:** producers and DJs on macOS and Windows, in any DAW. They do not understand spatial audio (PRD "Target users").
- **Outcome:** a designed space heard at the listener. Accuracy comes first, and heavy CPU or latency is acceptable (Key decisions "Accuracy vs CPU"; NFR-1, NFR-2). The plugin must stay "usable in a DAW session" (NFR preamble). Movement must be free of artefacts (NFR-3, FR-SIM-6). A reopened project restores exactly (NFR-6). Saved instances keep rendering (FR-LIC-3, NFR-7).
- **Hard constraints for these matters:**
  - **Generic engine:** NFR-8 / FR-SIM-2, no scene-specific logic.
  - **Determinism:** AX5; offline renders bit-identical.
  - **AX41:** W_max is a pinned cross-platform work count in image evaluations, derived from the C++ cost and never a time cap. Phase-07c condition 3 adds that it is "not kept at (A)". This is a board answer she accepted on 2026-11-10 ("I accept the board's answer by definition").
  - **AQ10 amended (1), her decision as amended on 2026-11-10 and 2026-11-12:** the restore gate is 14 × worst ≤ 30 s, and it includes the keyless stage-1 solve.
  - **AX38 4c:** no W_max cut once pinned, no narrowing of the room range, no formulation seam.
  - **No instance cap:** FR-3D-5, FR-3D-6, FR-SIM-7, A5.
  - **Timing:** condition 1, before the first public release, in one golden round.
  - **AX47:** bound 1 dB, reversal to 0.5 dB.
  - **AX49 L4 as specified:** T60 8 s, fully wet, 16 trials, ≥ 12/16.
  - **D-B3 condition A:** recorded speech in the self-ABX.
  - **Out of scope (07c §9):** n\*_max, any change to the estimator (AX39–AX44), a both-near fallback, a kernel cache.
- **Verification culture (CLAUDE.md):** every DSP behaviour is checked automatically; independent references are preferred over self-made goldens; goldens change only through `update_goldens.py` with a reason; listening is a person's action.

## 2. D-W1: W_max re-derived under (C) (scope 3, AC 1) and its companion checks

### Restatement

D-W1 chooses the shipped per-emitter work cap. It replaces `kWMaxPerEmitterProvisional` = 3.05 M (`src/sim/diffuse/DiffuseEstimator.h` L49). This changes:
- W_scene;
- N_cap and the cap-hit flag, U and the AX41 flags;
- the D5 golden and the E_model bump;
- E_prec in the AX48 key, so pre-raise states load keyless;
- the tail level of every capped scene, with one golden round;
- the solve time on the background, offline and keyless-load paths.

### Options

- **W-A0** — keep (A), 3.05 M. **Out of bounds:** condition 3 says "not kept at (A)", her accepted J1 answer. Listed only for reference.
- **W-1** — 3 s **per scene**, single thread. W_scene is set so that the worst-OS, single-thread solve of the costliest gated scene is ≤ 3 s. This is Seat 6's own correction, `docs/review/phase-05h/5-seat6-D-H1.md` L29.
- **W-2** — 3 s **per emitter**, single thread. This is Seat 6's original wording and about 2 × W-1.
- **W-3** — 3 s per scene at the shipping or CI pool size. This is Table 15.1's 3 s row by extension; the corpus check is pending.
- **W-4** — the AX38 (iv) load mark. W is set so that, with 8 instances at 100 m / 96 kHz on the worst OS, the time until the last final tail has settled is ≤ 10 s. Background solves serialise at the AX38 (i) gate.
- **W-5 (mine)** — the binding minimum: min(W-1 or W-3, W-4, a bounce condition from Seat 8 on the 3-minute 100 m record). The seats state the bounce condition.
- **W-6 (mine)** — accuracy-driven need under the budget. Take the smallest W at which every gated and reported capped class meets Seat 1's floor (AX38 4c, clauses (a)–(d)), or at which N_need ≤ N_cap in layouts 4/5 at s = 1. Then accept it only if it is ≤ W-5.

### Keyless-load consequence (seats rate it beside each option)

This is the coupling to D-W2 and the later class (c) round. Today the AX48 stage-1 (A) solve at a keyless load runs synchronously and is the final (step 0). After the raise there are three possible paths:
- **K-a:** the synchronous stage-1 runs at the new W. It stays class (a) with step 0, but the restore gate grows (AQ10 (1)).
- **K-b:** stage-1 stays at the (A) work and becomes an interim. That is a class (c) statistical source, and its admission waits for the ABX.
- **K-c:** another load fallback.

My intent: D-W1 decides the basis and the value. The keyless path is carried to the post-ABX class (c) round. The golden round lands only after both are decided. Seats should say whether they accept that sequencing or need the path fixed first.

### Companion items, decided in the same matter

- **(b)** D-Q5: is `nsPerEval` invariant across 07c's moves? If it moved, Seats 2 and 3 judge it.
- **(c)** Re-pin `solveRefMs` and k (G7) on the new work. I propose the S2 form: ≥ 3 green runs on unchanged pins, the PROVISIONAL exit as in AX38 4c, and a CHANGELOG reason.
- **(d)** Seat 2's prefix check (`pathCount`, `pilotStops`). Is the (A) final range a prefix of the (C) one wherever the pilot stopped at n\*_max, and not where the pilot was work-stopped? The flutter cube is a candidate for the work-stopped case: W_pilot 3 154 338 > W_scene/2 = 3 050 000 (file 44 L44).
- **(e)** E_prec: pre-raise v2 states load keyless. The options are to keep `pluginStateVersion` 2 (a key mismatch already means keyless) or to bump it. Pre-release only (condition 1). Confirm that the v2 fixtures still load.
- **(f)** Scope 8, from BUILD_PLAN §0: 12-1 and 12-2 are "not started", so Phase 12 runs the (ii) check at 07c's W_max. 08-1…08-4 are "not started", so 07c-2 lands before Phase 08's goldens are frozen and no SE-derived tolerance is needed. Seats 4 and 6 confirm or object.
- **(g)** Scope 10 (P07C1B-R1): a fact check of `listed` on `main`.

### Convening table, D-W1

| seat | status | reason (README table item) | brief |
|---|---|---|---|
| 1 | convened | **What the listener hears:** the achieved SE, VOV and p95 at capped scenes; its "now 2" is repaid here; floor clauses (a)–(d); keyless interim audibility. PRD-priority seat. | Shared brief + S1 focus |
| 2 | convened | Lead seat. **Simulator compute and recompute time:** work count from the C++ cost; pilot, N_cap, prefix claim; `nsPerEval`. | Shared + S2 focus |
| 3 | convened | **Per-instance CPU:** the background solve beside playback; Table 15.1 rows; decay matching at the step; Seat 3 (5) condition; D-Q5 hand-off if `nsPerEval` moved. | Shared + S3 focus |
| 4 | convened | **Delivery:** W_max is one constant for all modes; Phase 08 heaviest-mode build and goldens (scope 8); E_b shared across modes and ears. | Shared + S4 focus |
| 5 | convened | **Threads, gate and CI:** restore gate including keyless stage-1; class (1) priority; bounce (offline equals real-time); solve-bound re-pin; v2 state fixtures; callback p99.9 with builders. PRD-priority seat (audio thread). | Shared + S5 focus |
| 6 | convened | **User-facing:** its own 3 s criterion and per-scene reading; U at default placements; "settling" duration; Phase 12 (ii); load wait. PRD-priority seat (user's controls). | Shared + S6 focus |
| 7 | convened | **Cost:** golden round, release timing (condition 1), contractor time, and public wording about large rooms. PRD-priority seat (cost). | Shared + S7 focus |
| 8 | convened | **Producer workflow:** the AX38 4c 3-minute bounce record is its prerequisite (AX41), with bounce time against real time and freeze. | Shared + S8 focus |
| 9 | convened | **Real rooms:** which real or preset-class rooms hit the cap (large halls, churches); the capped presets' SE; Phase 12 preset validation. | Shared + S9 focus |

### Shared brief for every D-W1 seat (pass on verbatim)

> **Matter D-W1 (phase 07c-2 scope 3, AC 1).** Re-derive W_max per emitter under (C) from the background budget: Seat 6's 3 s per emitter, the AX38 (iv) load mark, and Table 15.1's 700 ms / 3 s rows.
>
> It stays a pinned cross-platform work count in image evaluations, derived from the C++ cost and never a time cap (AX41). It is not kept at (A): 3.05 M per emitter, W_scene 6.10 M, `src/sim/diffuse/DiffuseEstimator.h` L49.
>
> **Options:**
> - W-1: 3 s per scene, single thread, worst OS, costliest gated scene.
> - W-2: 3 s per emitter, single thread.
> - W-3: 3 s per scene at the pool size.
> - W-4: 8 instances × 100 m / 96 kHz, last final tail settled ≤ 10 s (AX38 (iv)).
> - W-5: the binding minimum of W-1 or W-3, W-4 and a bounce condition you state.
> - W-6: the smallest W meeting Seat 1's floor at every capped class, accepted only if ≤ W-5.
>
> **For each option**, also rate its keyless-load consequence:
> - K-a: the synchronous stage-1 at the new W (restore gate grows).
> - K-b: stage-1 at the (A) work as a class (c) interim (awaits the ABX).
> - K-c: another fallback.
>
> Say whether you accept deciding the value now and the keyless path after the ABX, with the golden round after both.
>
> **Companion items:** (b) `nsPerEval` invariance (D-Q5); (c) the solveRefMs / k re-pin form; (d) Seat 2's prefix check; (e) E_prec, keep state v2 or bump; (f) scope 8 (Phase 12 not started; Phase 08 goldens not frozen); (g) scope 10.
>
> **Read:**
> - `docs/phases/phase-07c-2.md`; `docs/phases/phase-07c.md` §0, §1, §3, §9.
> - BUILD_PLAN §2: AQ10 (amendments of 2026-11-10 and 2026-11-12), AX38 (i), (iv), 4c, AX41, AX44, AX47, AX48, AX49.
> - `docs/review/phase-07c-1/42-orchestrator-ci-records-43258505284.md` and `44-orchestrator-ci-records-43291051799.md` (bounce lines L141–144, solve and work lines L44–58, (iv) loads).
> - `docs/review/phase-07c-1b/22-repin-gate-output.md`, `23-s2-records-excerpt.md`, decider files 4, 8, 11, 25.
> - `docs/review/phase-05i/9-decider-r2.md` (D-Q5 and its debt register).
> - `docs/review/phase-05h/5-seat6-D-H1.md` L29; `docs/review/phase-05b2/47-decider-board-answers-C1-Q2a-final.md` §4 (iii).
> - The orchestrator's fact sheet (F1–F13 below), when it arrives.
>
> **Return:** for every option, `now / later` on the 0–3 scale with a one-line reason each; conditions of acceptance for every 2 or 3; what each option commits later phases to, what undoing it costs and where the evidence arrives (07c-2 CI, 07d, 08-4, 12-2, 13); your positions on (b)–(g) where they touch your mandate; and NOT MY MATTER where none does.

### Per-seat focus, D-W1

- **S1:** the SE, VOV and p95 at each candidate W for the gated cubes, the s = 1 cube and layouts 4/5 at s = 1. Does any option leave the floor not met (escalation)? Is K-b's interim audible against AX47? Corpus needed: Vorländer Table 6.1.
- **S2:** how cost scales with W (pilot, final range, N_cap); which fixtures are capped; the prefix check (d); the D5 / E_model consequence; whether one constant holds across output modes.
- **S3:** the CPU of background solves beside playback and its effect on callback p99.9; how the Table 15.1 700 ms / 3 s rows apply once the ISM is not held behind the solve (condition 4); D-Q5 (b).
- **S4:** the heaviest mode (Phase 08) under each W; one constant; confirm scope 8 (f).
- **S5:** the gate under K-a; the re-pin form (c); state v2 against a bump (e); bounce and offline; the instance-count independence of each option (no instance cap).
- **S6:** your per-scene reading of the 3 s, and whether it is single-thread or at the pool size; settling time; U at defaults; Phase 12 (ii) (f).
- **S7:** golden-round cost; release timing; public wording on large-room load, settle and bounce.
- **S8:** the bounce ratio you accept at 48 and 96 kHz (current: 48 kHz 0.24–0.33 × real time, 96 kHz 0.82–1.17 ×, 36 rebuilds); freeze.
- **S9:** which room classes (presets in FR-3D-3 categories) sit in the capped class at each W.

### Facts to extract or measure first (orchestrator, before the seats or alongside them)

- **F1. `nsPerEval` per OS and scene**, from every GATE line on file:
  - 05i: 43007183782, 43031773338;
  - 07c-1: 43215018040, 43227272415, 43242209571, 43258505284, 43291051799;
  - 07c-1b S2: 43389296112, 43402114873, 43412038058, plus 43427854710.
  - Also, from the code: does the timed region still cover `estimateDiffuse` alone (D-Q5 K18)?
- **F2. CI pool size per OS**, and the solve median of both gated scenes at **1 thread and at the pool size**, per OS (Release).
- **F3. Solve time and transient memory against W.** Use a validation-only `DiffuseLimits` override, like `--image-cap`, with no shipped code path. Take W_max × {1, 2, 4, 8, 16} at the two gated cubes, the s = 1 cube and layouts 4/5 at s = 1, per OS. Report time against W (linearity) and peak RSS against AX38 (i)'s 1 GB.
- **F4. Accuracy at the same W values.** Per emitter and band: achieved SE, VOV, cap hit, N_need, N_cap, and the 30-replicate p95 where it is cheap (the file 10 form).
- **F5. Cap and pilot status of every fixture** at the current pin, from the D5 golden (`phase05h_d5_hashes.json`): N_need, N_cap, n\*, W_pilot, cap hit, and the pilot stop reason (n\*_max or work). From these, compute W_uncap = W_pilot + N_need·W_pilot/n\* per capped fixture. Include W1 and W2 of AQ10: does W2 bind the cap? If so, the 50 ms W2 time grows with W.
- **F6. AX38 (iv) load totals** from the latest records (07c-1b S2 and run 43291051799): 1, 4 and 8 instances; 100 m and the AQ10 room; 48 and 96 kHz; per OS. Give the time until audible at the interim and the time until the final tail settled, split into synthesis and solve where printed.
- **F7. Bounce decomposition:** per rebuild, the solve share of the 36-rebuild 3-minute bounce at 48 and 96 kHz, so that the bounce can be projected per W.
- **F8. Callback p99.9 and overruns with concurrent builders**, from the cond. 12 (c) B1-b records, together with the solve duration during those runs.
- **F9. Keyless stage-1 from the code:** do the stage-1 solve and the background final share one `DiffuseLimits`? What W would a keyless load solve at after the raise?
- **F10. State fixtures:** list `tests/state/v2_*.bin` and confirm that they load keyless after an E_prec or E_model change. From the code: does a D5 regeneration force an E_model bump?
- **F11. Seat 2's prefix claim**, from the code (`pathCount`, `pilotStops`): which fixtures are work-stopped at the pin (F5)?
- **F12. Restore-gate projection for K-a:** 14 × (worst restore + worst solve at W) per OS, from F3.
- **F13. Scope 10:** the `listed` value of the macOS `cube100_lowalpha0.05_s0.3` row of `kGateRegister` on `main`.

### Knowledge inventory, first pass (D-W1)

| K | what must be known | source | status |
|---|---|---|---|
| K1 | current pin 3.05 M per emitter; W_scene 6.10 M | AX41; `DiffuseEstimator.h` L49, L90 (from the code) | known |
| K2 | bounce record: 48 kHz 0.30 ×, 96 kHz 1.08 × on Linux, run 43291051799 (36 rebuilds) | file 44 L141–144 | known (other OSes: under-informed until the orchestrator states the 0.24–1.17 range per OS) |
| K3 | ns per evaluation: flutter 12.97 ns, low-α 7.59 ns, Linux run 43291051799 | file 44 L47, L58 | under-informed (thread count; other OSes and runs: F1, F2) |
| K4 | single-thread cost basis for Seat 6's 3 s (44.7 ns per evaluation) | `docs/review/phase-05h/8-decider-decision-D-H1-D-H2.md` K13 | misinformed risk (05h code; re-measure, F2) |
| K5 | solve time is linear in W; memory against W | none | uninformed (F3) |
| K6 | SE, VOV and p95 against W at capped classes | AX41 (prototype and C++ at the pin only) | uninformed at the new W (F4) |
| K7 | which fixtures and benchmarks are capped; W_uncap | D5 golden | uninformed (F5) |
| K8 | (iv) 8-instance final-settled time | (iv) records | under-informed (F6) |
| K9 | Table 15.1 rows and their conditions; Vorländer Table 6.1 jnd | corpus | **uninformed: corpus absent** |
| K10 | keyless stage-1 W after the raise | code | uninformed (F9) |
| K11 | prefix claim | Seat 2, 07c-1 file 3 L38–39, 55 [Inferred] | misinformed risk (F11) |
| K12 | Phase 08 and Phase 12 not started | BUILD_PLAN §0 rows 08-1…08-4, 12-1, 12-2 | known |
| K13 | DAW behaviour when an offline render is slower than real time | none | uninformed (RQ-W1-1) |
| K14 | core counts of target machines (pool-size basis) | none | uninformed (RQ-W1-2) |

### Researcher questions (D-W1), to run alongside the seats

- **RQ-W1-1.** In Live 12, Logic Pro (bounce, offline), Cubase or Nuendo (export, real-time off), REAPER (render, full speed), Bitwig, FL Studio and Studio One: when a plugin makes an offline render or freeze slower than real time, does the host time out, warn, fall back to real-time rendering or drop audio? Cite vendor documentation, with versions.
  - *Changes:* whether a bounce ratio above 1 × is a product break (Seats 5 and 8) or only a wait (W-5's bounce term).
- **RQ-W1-2.** Base rates of physical core counts among macOS and Windows users in 2025–2026: Steam Hardware Survey, Apple Silicon base configurations, and any DAW-user survey. Report the share with ≥ 4 and ≥ 8 cores, with dates and population.
  - *Changes:* whether W-1 (single thread) or W-3 (pool size) is the fair "user machine" basis.

## 3. D-W2: AX47 self-ABX and AX49 L4 ABX design, set before the run (scope 9, first bullet)

### Restatement

D-W2 fixes the following before a person runs the tests:
- the detection criterion;
- the step sizes;
- the trial allocation;
- the stimuli: recorded speech, noise and the L4 held chord;
- the rendering of A, B and X, the playback chain and the step direction;
- the family-wise false-detection control (interrogator file 16 row P07C1-DC-06: "a per-size 12/16 rule raises the family-wise false-detection rate").

What depends on it:
- AX47's reversal (bound 0.5 dB if a step below 1 dB is detected);
- AX49's reversal (L4 detects the cut);
- the bound B in the interim stream check;
- the admission of a class (c) source.

L4 is fixed by AX49 (16 trials, ≥ 12/16; one test). Its only open parts are the stimulus details and the chain. The AX47 self-ABX is where the family arises.

### Options for the AX47 criterion and step sizes

- **X-1** — one pre-registered step size just below the bound (e.g. 0.75 dB), 16 trials per stimulus, ≥ 12/16. The family is {noise, speech}, so two tests.
- **X-2** — k sizes (e.g. 0.25 / 0.5 / 0.75 dB), 16 trials each, per-size threshold Bonferroni-adjusted at n = 16, with the family over sizes × stimuli.
- **X-3** — k sizes in a fixed sequence from the largest to the smallest, testing each at ≥ 12/16 and stopping at the first non-detection. This is the fixed-sequence procedure; its FWER property is to be verified (RQ-W2-1).
- **X-4** — an adaptive procedure (a staircase toward a threshold), reported against 1 dB. This changes AX47's "16 trials" and needs a board DECISION.
- **X-5 (mine)** — X-1 or X-3 with the family's α fixed at 0.05 one-sided over both stimuli, plus a pre-registered power statement at 16 trials.

### Sub-items, decided at the same time

- Step direction: up, down or both.
- What the step is: rendered as the AQ4 equal-gain crossfade between two IrSets differing only in per-band tail level. This is the AX47 Scope.
- Where the step falls in the stimulus, and its timing.
- The capped layout-4 scene and its output mode: omni or the stereo stub, since binaural lands in Phase 08.
- Headphones or speakers; playback level; level matching.
- The recorded speech source and its licence (D-B3 condition A; THIRD_PARTY row); whether stimuli go into the CI `listening-pack` artifact or are built locally.
- Who listens (Maisara or her listener) and how answers are recorded blind: a tool or script producing a sealed answer file.
- What is recorded as the result.

**Not decided now:** class (c) admission and the load fallback. They are convened after the result. I judge that no part of them can be decided before the ABX, apart from what D-W1's keyless-path rating already exposes.

### Convening table, D-W2

| seat | status | reason (README table item) | brief |
|---|---|---|---|
| 1 | convened | Owner: **blind-test paradigm**, listeners, signal, strictness, sample size, JND conditions, acceptance tests. PRD-priority seat (what the user hears). | Shared + S1 focus |
| 2 | convened | **Step sizes engine-realistic:** the interim-to-final steps the solve produces (cap hit, achieved SE at (A) against the new W; 0.13–1.33 dB at layouts 4/5, AX41); scene definition. | Shared + S2 focus |
| 3 | convened | **Rendering of the step:** crossfade law and length (AQ4, AX18), the tail window, decay matching, so that the stimulus is the shipped transition. | Shared + S3 focus |
| 4 | convened | **Playback chain:** headphones or speakers, output mode before Phase 08, level matching (loudness parity), the listening-test chain. | Shared + S4 focus |
| 5 | convened | **Determinism:** stimuli rendered offline and bit-identical (AX5); any test-only render flag; CI listening-pack generation. Touches what the user hears through the shipped transition, so convened on the PRD-priority rule. | Shared + S5 focus |
| 6 | convened | **The user's moment:** the step is the "settling → final" moment of L1 (load, press play); the stimulus should match the user's situation. PRD-priority seat (what the user sees and hears at load). | Shared + S6 focus |
| 7 | convened | **Cost and licence:** recorded speech licence and attribution; the listener's time (a person's action); the wording of any "not audible" record. PRD-priority seat (cost). | Shared + S7 focus |
| 8 | convened | **Program material and context:** speech, noise, held chord; fully wet against in-mix; whose ears. | Shared + S8 focus |
| 9 | convened | **Scenes as rooms:** the capped layout-4 scene and L4's T60 8 s room; whether they are plausible rooms and which presets they stand for. | Shared + S9 focus |

### Shared brief for every D-W2 seat (pass on verbatim)

> **Matter D-W2 (phase 07c-2 scope 9, first bullet).** Fix before the run:
> - the AX47 self-ABX design (16 trials, capped layout-4 scene, recorded speech per D-B3 condition A and noise): detection criterion, step sizes, trial allocation and family-wise false-detection control (interrogator `docs/review/phase-07c-1/16-interrogator-diff-check.md` row P07C1-DC-06; P(X ≥ 12 | 16, ½) = 0.038 one-sided, as stated there);
> - the AX49 L4 details: held chord, provisional against exact, T60 8 s, fully wet, 16 trials, ≥ 12/16 detected, as already fixed.
>
> **Options (AX47):**
> - X-1: one size just below 1 dB, per stimulus.
> - X-2: k sizes, Bonferroni-adjusted.
> - X-3: k sizes in a fixed sequence, largest first, stop at the first non-detection.
> - X-4: adaptive staircase (changes "16 trials").
> - X-5: X-1 or X-3 at family α 0.05 over both stimuli, with a pre-registered power statement.
>
> **Sub-items:** step direction; the step rendered as the shipped AQ4 equal-gain crossfade between IrSets differing only in per-band tail level; step timing in the stimulus; output mode before Phase 08; headphones or speakers and level; the recorded speech source and its licence, and whether stimuli enter the CI listening pack; the blind-answer procedure; what is recorded.
>
> Class (c) admission and the load fallback are **not** decided now.
>
> **Read:**
> - BUILD_PLAN §2: AX47 (whole row, the Reversal especially), AX49 (L4, Reversal), AX18, AQ4, AQ9.
> - `docs/phases/phase-07c-2.md` scope 9.
> - `docs/review/phase-07c-1/12-decider-decision-r3.md` §7–§8; file 16 row DC-06.
> - `docs/review/phase-07c-1b/4-decider-decision-r1.md`, `8-decider-decision-r2.md` (D-B3), `7-seat1-r2-signal.md`, `7-seat7-r2b-signal.md`.
> - The researcher's findings (RQ-W2-*), when they arrive.
>
> **Return:** for every option, `now / later` on 0–3 with a one-line reason each; conditions of acceptance for every 2 or 3; your positions on the sub-items that touch your mandate; the future debt, i.e. what a wrong design costs in the class (c) round, 08-3, 09 and 13, and when the evidence arrives; NOT MY MATTER where none applies.

### Per-seat focus, D-W2

- **S1:** the paradigm and its strictness, the family definition, power at 16 trials, the step sizes against the JND conditions (corpus), what "detected" licenses.
- **S2:** the step sizes the engine actually produces at the new W; how the scene is pinned.
- **S3:** the stimulus equals the shipped transition (law, length, window).
- **S4:** the chain and level matching before binaural exists.
- **S5:** deterministic offline stimulus generation; no shipped code path changes.
- **S6:** the L1 situation as the stimulus.
- **S7:** the licence of the speech source; artifact distribution; listener time; record wording.
- **S8:** material and wet or dry context.
- **S9:** scene plausibility.

### Knowledge inventory, first pass (D-W2)

| K | what must be known | source | status |
|---|---|---|---|
| K20 | AX47 "16 trials, capped layout-4 scene, noise and speech"; L4 as specified | AX47, AX49 | known (whether "16 trials" is per stimulus or in total is ambiguous; the board reads it) |
| K21 | P(X ≥ 12 \| 16, ½) = 2517/65536 = 0.0384 | file 16 row DC-06 | known (the decider re-derives: Σ_{k=12..16} C(16,k) = 1820 + 560 + 120 + 16 + 1 = 2517) |
| K22 | FWER of fixed-sequence testing; Bonferroni thresholds at n = 16 | none | uninformed (RQ-W2-1) |
| K23 | power of a 16-trial ABX at a given true p | none | uninformed (RQ-W2-2; computable, method to be verified) |
| K24 | level-step detection conditions (G and C80 jnd 1 dB; within-stream evidence) | Vorländer Table 6.1 (corpus); 07c-1 researcher R4 (none found) | **uninformed: corpus absent**; under-informed (within-stream) |
| K25 | recorded speech source and licence | none | uninformed (RQ-W2-4) |
| K26 | BS.1116-type double-blind practice on listener count and trials | none | uninformed (RQ-W2-5) |
| K27 | engine step sizes at (A) and at the new W | AX41 (0.13–1.33 dB, layouts 4/5); F4 | under-informed (new W) |

### Researcher questions (D-W2)

- **RQ-W2-1.** Do these procedures control the family-wise error rate over k one-sided exact binomial tests (n = 16, p₀ = ½), and at what level?
  - (i) Bonferroni;
  - (ii) the fixed-sequence (hierarchical) procedure: test in a pre-set order at α each and stop at the first non-rejection (e.g. Maurer, Hothorn and Lehmacher 1995, or Westfall and Krishen 2001);
  - (iii) Holm.
  - Give the exact per-test thresholds at n = 16 for family α = 0.05 with k = 2, 4 and 6, and the attained α.
  - *Changes:* X-2 against X-3 against X-5.
- **RQ-W2-2.** The probability of reaching ≥ 12/16, ≥ 13/16 and ≥ 14/16 at true proportions correct of 0.65, 0.75, 0.85 and 0.95. Cite the published treatment of type II error in small-n ABX (Leventhal, JAES 1986, and replies), verified.
  - *Changes:* whether 16 trials can support a "not detected" reading at all, and whether X-4 is needed.
- **RQ-W2-3.** Published thresholds for detecting a **level step within an ongoing** broadband noise, speech or reverberant signal (not paired comparison of separate stimuli), with conditions: signal, step rise time, level, paradigm. Search outside the corpus only after the decider has read the corpus (Blauert, Toole, Vorländer Table 6.1).
  - *Changes:* the step sizes.
- **RQ-W2-4.** The licence and redistribution terms for recorded speech usable as listening-test stimuli and in a public CI artifact: EBU SQAM speech tracks, LibriSpeech (CC BY 4.0), VCTK, ITU-T P.501 speech, plus any public-domain anechoic speech. Cover attribution, the right to process, the right to redistribute processed audio, and checksum-pinned download URLs.
  - *Changes:* whether stimuli ship in the `listening-pack` artifact or are built locally (Seat 7).
- **RQ-W2-5.** What ITU-R BS.1116-3 (and, if relevant, ITU-R BS.1534) says about hidden-reference double-blind designs, listener count, training and statistical treatment, and how a single-listener ABX relates to it.
  - *Changes:* the wording of what "detected" or "not detected" licenses (Seats 1 and 7).

## 4. Summary

| id | decision | state | worst-off seat | sum | confidence | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| D-W1 | — | convening (all nine) | — | — | — | NFR-1, NFR-2, NFR-6, NFR-8, AX41, AQ10 (1), condition 1, condition 3 "not kept at (A)" | pending (corpus absent) | — |
| D-W2 | — | convening (all nine) | — | — | — | NFR-1, AX47, AX49 L4, D-B3 condition A | pending (corpus absent) | — |

## 5. Challenges to settled decisions

None.

One reading is flagged for the decision round: whether AX47's "16 trials" is per stimulus or in total. AX47 is a board row and not her dated decision, so the board reads it in D-W2.

## 6. Decided for Maisara

Nothing is decided in this round.

No NEEDS MAISARA. The phase's Raise item 1 does not apply: 07c-2 is pre-release, and the condition 1 timing holds (BUILD_PLAN §0: no release; 13-x not done).

## Orchestrator actions, in order

1. Run `tools/ci/fetch_corpus.sh` and record `docs/corpus/SOURCE_COMMIT`.
2. Run the nine seats on D-W1 and the nine on D-W2. They can run as two parallel batches. Pass each seat the shared brief plus its focus line, verbatim.
3. Run the researcher on RQ-W1-1, RQ-W1-2 and RQ-W2-1…5.
4. Extract or measure F1–F13. F3 and F4 need a validation-only W override and CI or local Release runs on three OSes; say which.
5. Return the positions, findings and the fact sheet to me for the decision round.

Files read for this convening:
- `/home/user/makroof/docs/phases/phase-07c-2.md`
- `/home/user/makroof/docs/phases/phase-07c.md`
- `/home/user/makroof/docs/BUILD_PLAN.md` (§0 rows; AQ10, AX38, AX41, AX47–AX49)
- `/home/user/makroof/docs/board/README.md`
- `/home/user/makroof/docs/PRD.md`
- `/home/user/makroof/docs/review/phase-07c-1b/22-repin-gate-output.md`
- `/home/user/makroof/docs/review/phase-07c-1/44-orchestrator-ci-records-43291051799.md` (L1–222)
- `/home/user/makroof/docs/review/phase-07c-1/16-interrogator-diff-check.md`
- `/home/user/makroof/docs/review/phase-07c-1/3-seat2.md`
- `/home/user/makroof/docs/review/phase-05i/9-decider-r2.md`
- `/home/user/makroof/docs/review/phase-05h/5-seat6-D-H1.md`
- `/home/user/makroof/docs/review/phase-05b2/47-decider-board-answers-C1-Q2a-final.md`
- `/home/user/makroof/src/sim/diffuse/DiffuseEstimator.h`
