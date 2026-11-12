# 2 — Decider, convening round: D-C1, D-C2, D-C3, D-C9 (phase 07c-1)

Phase 07c-1, 2026-11-12. Saved by the orchestrator from the decider's report (the decider reads only). Corpus
revision `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`.

## PRD digest
- **For whom:** producers and DJs on macOS and Windows, in any DAW, who know nothing about spatial audio (PRD "Target users").
- **Outcome:** a reopened project sounds exactly as saved (NFR-6, FR-LIC-1 "Scene, settings and render state are saved in the DAW project"); movement renders smoothly (NFR-3, FR-SIM-6); the bounce reaches the track (A4).
- **Hard constraints for this loop:** NFR-8 / FR-SIM-2 (no scene-specific path); AX5 (offline bit-identical on the same OS); AQ4 / AX18 (one 30 ms crossfade per IR switch; restore equal-power, position/size equal-gain); AX38 (i) (the gate covers the solve only; no lock or allocation on the audio thread; default builder priority); AX40 / AX44 (E_b independent of `tailSeed`, shared across modes and ears); AX41 (W_max stays (A), 3.05 M, in 07c-1); contract boundary (no `contractVersion` change, condition 12; saved data goes into plugin state, not the scene contract); Phase 07 state rules (phase-07 L225–235: any `pluginStateVersion` bump adds fixtures, old fixtures keep loading); 07c-1 condition 2 / A2; condition 5 (never silence, never AX16 where > 1 dB off); condition 6 (offline waits for the final result); condition 9 ("never silence where a tail existed in the saved state"); condition 10 (a realtime reset keeps the current IrSet); no instance cap, W_max cut or range change (D-H1 (v)(d)); no per-host code path.
- **Settled, not reopened:** condition 5's preference order (decider file 47 §4 (iii) 5, a board answer she accepted).
- **Verification culture (CLAUDE.md):** every DSP behaviour checked automatically; independent references preferred; goldens never regenerated to pass.

## Can any of the four be settled without the board?
None in full. Fixed already: D-C2's preference order (condition 5); the mechanics of a state-version AX if E_b is stored (phase-07 L225–235). Still open: whether to store E_b and in which role (interim or authoritative); the choice inside (2); Seat 1's step ruling; the interim tail.

Fact from the code that reshapes D-C1 and D-C2 (2): in 07c-1 W_max is the (A) value, so "the (A)-budget estimate" **is** the final solve and that alternative of (2) is empty until 07c-2 raises W_max. D-C1's step therefore binds within 07c-1 only for steps from a saved E_b or a previous level; it becomes load-bearing at 07c-2. It must still be decided now (A1). All four share one subject matter (what plays between a restore or edit and the final IR, and what the project state carries): **one convening table covers all four**; each seat rates per matter (A–D).

## The matters and options

**Matter A: D-C3 and the storage half of D-C2 (what the saved state carries).** Depends on it: `PluginProcessor` get/setStateInformation, `pluginStateVersion`, state fixtures, the offline path at load, A7, F5.
- **A0:** no change (state v1; nothing solved is saved).
- **A1:** save per emitter E_b (8 doubles; 2 emitters = 16 doubles) plus a validity key (an exact match of the effective scene, W_max, n\*_max and an estimator-version id); `pluginStateVersion` 2. On a key match E_b is the **interim** level; the background solve still runs.
- **A2 (decider's variant):** as A1, but on a key match the saved E_b is the **final** level: no solve runs for that scene, offline renders use it; any edit invalidates it.
- **A3:** A1 or A2, plus the tail waveform (the unit decays or the assembled IR) in state: ≈ 18 MB per instance at 100 m / 96 kHz (12 s × 96 000 × 2 emitters × 2 outputs × 4 B); removes the pending synthesis at load.

**Matter B: D-C2 (2), the interim level when no matching saved E_b exists** (old v1 projects, a key mismatch, edits, `reset()`, prepare).
- **B1:** previous level (held). Exists on edits, reset and prepare; at a fresh load there is none.
- **B2:** the (A)-budget estimate solved in the background first. Under 07c-2 a two-stage solve; in 07c-1 identical to the final.
- **B3:** the AX16 level, except where AX16 is > 1 dB off; admissible only if a generic, scene-data-only predictor of that error exists (NFR-8), otherwise out at step 1.
- **B4 (decider's variant):** B1 on edits, reset and prepare; B2 at load.

**Matter C: D-C1, the provisional-to-final step.** Scope proposed for the ruling: the step between an interim source and the final level *for the same scene*, not the step the user's own edit causes (seats may contest this scope).
- **C1:** |interim − final| ≤ 1 dB per band (1 jnd of G and of C80, Vorländer Table 6.1); a larger step is still taken as one AQ4 crossfade and recorded (diagnostic plus counter).
- **C2:** ≤ 1 dB per band; an interim source that cannot guarantee it is not used; the next preference applies, or the previous output is held.
- **C3:** ≤ 0.5 dB per band.
- **C4:** no numeric bound: one AQ4 crossfade per solve, "settling" shown, step size recorded only.

**Matter D: D-C9, what plays while the unit-decay synthesis is pending** (3.14 of 3.29 s at 100 m / 96 kHz; restore after the move ≈ 0.15 s: ISM + matching + mix).
- **D1:** early part (ISM) alone; the tail joins as one AQ4 step when the synthesis lands. Bound check: at load this reads against condition 9's "never silence where a tail existed in the saved state"; kept on the table for the interrogator's reading and for scenes without a saved tail.
- **D2:** hold the previous IrSet whole until the full new IR is ready (edits, reset, prepare). At load there is nothing to hold, so D2 = D1 there.
- **D3:** a cheap provisional tail at the interim level (shorter or cheaper synthesis), replaced by the exact tail with an equal-power crossfade (AX18: unrelated waveforms). The final output is unchanged; offline never uses it.
- **D4:** the tail carried in state (Matter A3). Load only; edits use D2 or D3.
- **D5 (decider's variant, edits only):** the new early part with the previous tail waveform at the interim level, until the new unit decays exist. Position-only edits already reuse cached unit decays (AQ4); D5 is for edits that change T60.

## Convening table (one table for matters A–D)

| seat | convened / not required | reason | brief |
|---|---|---|---|
| 1 | convened | audibility of the interim level, the provisional-to-final step (D-C1 is "Seat 1's ruling"), the tail gap at load; which bar; A4's acceptance test (PRD-priority seat) | Common + S1 |
| 2 | convened | E_b's dependencies (validity key, fs), AX16-error predictability (B3), (A)→(C) difference, stage split, estimator versioning | Common + S2 |
| 3 | convened | rendering the switch: level step under crossfade, provisional tail (D3/D5), synthesis cost, crossfade law (AX18), coloration | Common + S3 |
| 4 | convened | E_b shared across modes and ears (AX44, condition 7); interim parity binaural/stereoSpeakers; a project restored in another output mode | Common + S4 |
| 5 | convened (lead) | state format and version, restore timing, threading, offline signal (condition 6), feasibility (D-C3 "a feasibility call for Seat 5") (PRD-priority seat) | Common + S5 |
| 6 | convened | what the user sees and hears at load and while editing: "settling", the interim choice (Seat 6 (b)), the step (Seat 6 (d)) (PRD-priority seat) | Common + S6 |
| 7 | convened | cost and schedule, project-size support burden, versioning after release (condition 1), hang dialogs (R3), public wording (PRD-priority seat) | Common + S7 |
| 8 | convened | D-C3 is Seat 8's question; what a producer hears on reopening and bouncing right after load; translation | Common + S8 |
| 9 | convened | condition 5's "never AX16 where > 1 dB off" (Seats 1, 4, 9); which real rooms/presets sit in the AX16-error and capped classes; audibility of a tail-level error in real rooms | Common + S9 |

## Briefs

### Common brief (every seat)
> **Matter.** Phase 07c-1 moves the diffuse solve and the unit-decay synthesis off the synchronous restore, prepare and `reset()`. Four open choices must be decided before any code (phase-07c-1 "Decisions before implementation", A1): D-C1, the provisional-to-final level step; D-C2, the interim level and whether E_b is saved; D-C3, whether the solved result travels in saved state; D-C9, what plays while the unit-decay synthesis is pending. They are grouped as Matters A–D with options A0–A3, B1–B4, C1–C4 and D1–D5, as listed in "The matters and options" above (verbatim part of this brief).
>
> **Bounds you may not argue against** (umbrella §1 settled; phase-07c-1 conditions): condition 5's preference order; never silence, never AX16 where it is more than 1 dB off; condition 9's "never silence where a tail existed in the saved state"; offline waits and stays bit-identical (condition 6, AX5); a realtime reset keeps the current IrSet (condition 10); the gate around the solve only (condition 12); W_max stays (A) in 07c-1 (AX41); no `contractVersion` change, no per-host path, no instance cap, no W_max cut (NFR-8, D-H1 (v)(d)). If you think one of these bounds rules an option out, say so and name the bound.
>
> **Facts from the code** (`docs/review/phase-07c-1/1-orchestrator-decisions.md`): the tail level (per-band amplitudes from E_b) and the tail waveform (the unit decays) are separable, the IR is linear in the amplitudes; the unit decays depend on fs, `tailSeed`, the emitter, the T60s and the length; E_b depends on geometry, materials, positions and W_max, not on `tailSeed` (AX40); at (A) W_max the solve takes 81 ms (low-α 100 m cube) and 131 ms (flutter scene) on Linux at 96 kHz (AX38 4c RG-1 baselines); the synthesis takes 3.14 s at 100 m / 96 kHz, ISM + matching + mix about 0.15 s (AX38 4c finding); before the first IrSet the convolver outputs silence (`CrossfadingConvolver`); in 07c-1 the "(A)-budget estimate" equals the final solve.
>
> **Read:** `docs/phases/phase-07c-1.md` conditions 4, 5, 6, 9, 10, 12, A3, A4, A7; `docs/review/phase-07c-1/1-orchestrator-decisions.md`; `docs/review/phase-05b2/47-decider-board-answers-C1-Q2a-final.md` §4 (iii) and `51-decider-addendum-J1.md`; BUILD_PLAN §2 AQ4, AX5, AX16, AX18, AX38 ((i), (iii), (iv), 4c's synthesis finding), AX40, AX41, AX44; `docs/phases/phase-07.md` (state, L225–235); PRD NFR-3, NFR-6, NFR-7, NFR-8, FR-LIC-1, FR-LIC-3, FR-SIM-6, A4.
>
> **Return, per matter A–D:** `NOT MY MATTER`, or your ranking; for **every** option your tension **now / later** (0–3; 3 veto-grade) with a one-line reason; what each option commits later phases to (07c-2's W_max raise, Phase 10, 11, 13), what undoing it costs, and when the evidence arrives; conditions of acceptance for every option you rate 2 or 3. Cite the corpus or a product id for any acoustic or product claim; mark anything else [Hyp].

### Seat 1 (Perceptual gatekeeper)
> **Your ruling is D-C1 (Matter C).** Give a number (dB, per band or broadband, which bands) or a rule, the conditions it holds under, and what happens when a step would exceed it. State whether Vorländer Table 6.1 (G 1 dB, C80 1 dB, 500–1000 Hz) applies to a level step inside a running stream under a 30 ms crossfade, or only to paired comparison. Name the acceptance test A4 should run. Rate whether D1's tail gap at load (≈ 3.3 s at 100 m / 96 kHz; less at 48 kHz and in small rooms) counts as "silence" for you. Rate the interim-to-final error each B option implies (B3: AX16 up to +3.83 dB off in layout 4; B2 under 07c-2: SE 0.13–1.33 dB in layouts 4/5 at s = 1, AX41).

### Seat 2 (Engine architect)
> **Matters A and B.** What exactly must the validity key contain so that a saved E_b equals the solve the current build would make (including whether E_b depends on fs, n\*_max, AX4 air, the estimator constants D1–D7)? Does A2 (authoritative saved E_b) conflict with AX5 across architectures, or with 07c-2's single golden round? Is there a generic, scene-data-only predictor of AX16's error that would make B3 admissible under NFR-8 (if not, say B3 is out)? Rate B2's two-stage solve as it would stand in 07c-2.

### Seat 3 (Reverb renderer)
> **Matters C and D**, and A3's effect on the renderer. Rate a level step under the AQ4 / AX18 crossfade law. Rate D3's cost and feasibility (could a provisional tail fit the ≈ 0.15 s synchronous budget, or a short background step; which generator; cost [Hyp unless measured]). Rate D5's wrong-T60 waveform. Say whether the unit decays can be produced progressively and bit-identically to the whole-length generator (no golden round); the cheaper-generator alternative of condition 9 stays "recorded, not chosen". Rate D2 against condition 4's "ISM update never held behind the diffuse solve" for edits that change T60.

### Seat 4 (Chain keeper)
> **Matters A, B and D** as they touch delivery. A saved E_b must stay shared across modes and ears (AX44, condition 7): rate a project saved in one output mode and reopened in the other. Rate interim parity between binaural and stereoSpeakers (Phase 08/09 not yet built; rate "later" against them). Rate A3: a saved assembled IR is mode-specific; does it break AX44 or the output-mode switch (AX18 equal-power, Phase 09)?

### Seat 5 (Deadline keeper, lead)
> **All four matters; D-C3's feasibility is yours.** State-format cost of A1/A2 (version 2, fixtures, v1 loading) and of A3 (≈ 18 MB per instance; serialisation time on the host's state thread; undo and autosave). Restore timing under each D option. The offline path at load: under A2 does offline skip the solve; under A1 does it wait? Thread safety of handing an interim then a final IrSet. What an unreliable host offline signal (condition 6) does under each option: does a bounce right after load render interim state? The researcher is checking R1, R2, R5; say which of your ratings would change on which answer.

### Seat 6 (Canvas designer)
> **Matters B, C and D** from the user's side. At project load: what the user hears in the first seconds under each D option, and whether "settling" covers it (AX38 (iii)). On edits: B1 versus B2 and the step (your (b) and (d) from decider file 47 §4 (iii) 5). Whether any option needs a new control or message (none is proposed). Rate C1–C4 by what a producer perceives as "the room changed by itself".

### Seat 7 (Founder)
> **Matters A and D, plus cost for all.** Schedule and complexity cost of each option; support cost of large project files (A3); whether A1/A2's key, by including the estimator parameters, also discharges your condition 1 (versioned estimator parameters if 07c lands after release); wording risk: what may be said publicly about load behaviour. R3 (hang dialogs) is with the researcher; say what answer would change your rating.

### Seat 8 (Storyteller)
> **Matter A is your question** (does the solved result travel in saved state?). Also Matters B and D from the producer's workflow: reopening a project and playing at once; bouncing right after load in a host that may not signal offline; A/B-ing rooms while editing. Rate each option by whether the producer's point of view and anchor survive the first seconds after load and the bounce.

### Seat 9 (Room acoustician)
> **Matter B (B3) and Matter C**, from real rooms. Which real-room or preset classes (FR-3D-3 categories) fall where AX16 is more than 1 dB off (absorbing floor with diffuse walls; layout 4/5-type) or in the capped class? Is a tail-level interim error of the B options' sizes audible as a room change at a real listening position? Does saved E_b (A1/A2) raise any provenance or validation issue for Phase 12 presets?

## Knowledge inventory (first pass)

| K | what must be known | source | status |
|---|---|---|---|
| K1 | E_b size and dependencies | code (`Engine.cpp` L285–337; file 1); AX40 | known; fs, n\*_max and estimator-constant dependence under-informed (Seat 2) |
| K2 | level and waveform separable; `cachedUnitDecays` exists | code | known |
| K3 | synthesis 3.14 of 3.29 s at 100 m / 96 kHz, ≈ 2.5× from 48 kHz, flat for T60_max ≥ 8 s; ISM + mix ≈ 0.15 s | AX38 4c finding | known; re-timed on a named box (condition 9 packet) before the interim rules are sized |
| K4 | solve at (A) W_max: 81 / 131 ms (Linux), 84 / 103 (macOS), 90 / 144 (Windows) | AX38 4c RG-1 | known (PROVISIONAL n = 1–2) |
| K5 | full IR ≈ 18 MB at 100 m / 96 kHz | computed | known |
| K6 | AX16 error by class (layout 4 +3.83 dB; absorbing-floor cube +2.38 dB; others ≤ 0.43 dB) | AX16 row | known |
| K7 | (A)→(C) step under 07c-2: SE 0.13–1.33 dB (layouts 4/5, s = 1), ≤ 0.15 dB near 100 m | AX41; decider file 51 L3/L5 | known |
| K8 | jnd G 1 dB, C80 1 dB, 500–1000 Hz | Vorländer Table 6.1 | known; conditions ill-informed risk → R4 |
| K9 | host tolerance of a blocked `setStateInformation` | none | uninformed → R1 |
| K10 | hosts that do not signal offline reliably | researcher T5T4-61 F12–F19 | under-informed → R2 |
| K11 | host hang dialogs and timeouts | none | uninformed → R3 |
| K12 | limits and costs of multi-MB plugin state | none | uninformed → R5 |
| K13 | silence before the first IrSet; restore law equal-power | code; AX18 | known |
| K14 | a generic predictor of AX16's error (B3 under NFR-8) | none | uninformed (Seats 2, 9) |
| K15 | cost/feasibility of a provisional tail (D3), progressive bit-identical synthesis | none | uninformed (Seat 3 [Hyp]; condition 9 packet) |
| K16 | 8-instance load after the move | AX38 (iv) pre-move records | uninformed until the re-take; not load-bearing for the choice, load-bearing for its reversal |
| K17 | cross-OS E_target agreement (A2 across machines) | AX5, AX39 D1–D7, CI | known |
| K18 | product reading: FR-LIC-1 "render state" saved; NFR-6 "exactly" | PRD | known by id; the decider's reading in the decision round |

## RESEARCH NEEDED (start from `docs/review/phase-05h/12-researcher-T5T4-61.md`; add only what it lacks)

- **R1 (Seat 5): blocked `setStateInformation`.** Hosts: Logic (AU, macOS arm64), Live 12, Cubase 13/14, Bitwig 5, REAPER 7, FL Studio 2024, Studio One / Fender Studio Pro, on macOS arm64 and Windows x64. On which thread does the host call state restore at (a) project load and (b) undo or preset recall during playback? Does the host document a time limit, a watchdog, or a "plug-in not responding" / disable action for a slow restore, and after how long? What changes: a documented limit ≤ ≈ 0.2–0.5 s constrains the synchronous ISM + mix (≈ 0.15 s per instance, sequential at load) and rules out A3's 18 MB deserialisation; tolerance of seconds leaves D unchanged.
- **R2 (Seat 5): hosts that do not signal offline.** VST3 `kOffline` / `setupProcessing`, AU `kAudioUnitProperty_OfflineRender`, JUCE `isNonRealtime()`; export/bounce, freeze, render- or bounce-in-place, in the same hosts (FL Studio's "Notify about rendering mode" default, REAPER's render modes, Live's freeze/export, Logic's bounce-in-place, Bitwig's and Studio One's offline export). Vendor or developer-forum statements marked read, or "not found". What changes: if a common host by default does not signal offline, a bounce right after load renders the interim state (favours A2/A3 over A0/A1; condition 6's log line the only protection).
- **R3 (Seat 7): hang dialogs and timeouts.** Logic, Live, Cubase, Bitwig (REAPER and FL Studio if cheap); OS-level unresponsive indications on macOS and Windows with documented onset times; Logic's out-of-process AU hosting; Bitwig's sandbox hang detection; project load vs playback. What changes: the synchronous budget per restore and per load of 8 instances; public wording for load behaviour.
- **R4 (Seat 1, D-C1; new): audibility of a level change of the late reverberation inside a running signal.** JND or detection threshold for a change in reverberant level (or D/R, G, C80) applied within a continuous music or speech stream over ≈ 30 ms, vs paired comparison; per-band vs broadband; frequency dependence outside 500–1000 Hz; signal, listeners, paradigm, level. What changes: a within-stream threshold < 1 dB tightens D-C1 toward C3 (B2's 07c-2 interim, SE up to 1.33 dB, would fail it); ≥ 1 dB supports C1/C2. Check the corpus first.
- **R5 (Seats 5, 7, 8, D-C3; new): large plugin state in practice.** Documented limits or known problems with multi-MB plugin state chunks (VST3 `getState`, AU ClassInfo in the project file, Live's stored state, Logic packages); how often hosts call `getState` (autosave, undo snapshots, per-parameter undo). What changes: known slowdowns, undo bloat or size caps at ≈ 1–20 MB per instance rule out A3.

**CONVENE**: all nine seats, the researcher on R1–R5 in parallel; the decision round follows on the seats' ratings and the researcher's findings marked read. Gaps still open then are deferred as RESEARCH NEEDED, not decided.

## Summary table

| id | decision | state | PRD bound | corpus basis |
|---|---|---|---|---|
| D-C1 | — | convening | NFR-3, FR-SIM-6, NFR-6 | Vorländer Table 6.1 (conditions → R4) |
| D-C2 | — (order fixed by condition 5) | convening | NFR-6, FR-LIC-1, NFR-8 | — |
| D-C3 | — | convening | NFR-6, FR-LIC-1, FR-LIC-3, A4 | — |
| D-C9 | — | convening | NFR-6, NFR-3, condition 9 | — |

Challenges to settled decisions: none. Decided for Maisara: nothing yet; no NEEDS MAISARA. The Raise item does not apply (no release has happened).
