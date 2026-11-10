# Seat 3 — D-H3 (a), (b), (c)

Read in full: file 16 (both deliveries), 11 (with addendum), 9, 13, 14, 18 (K-a3/K-a4/K-b3), 12 (researcher T5T4-61); BUILD_PLAN AX36–AX46, AQ4, AX18, AX31; phase-05h §4 item 4, §5, §8; phase-07 L108–162; phase-07c §5–§6; my own files 3/18/23 (phase-05b2) and the C1 addendum (file 2). From the code: `test_diffuse_agreement.cpp` L190–289, `test_diffuse_gate.cpp` L295–389, `Engine.cpp` L40–66, L220–540, `tail/NoiseTail.cpp`, `tail/NoiseTail.h`, `tail/Decay.cpp`/`.h`, `conv/Denormals.h`, `conv/CrossfadingConvolver.cpp` L168–345, `RealtimeEngine.cpp` L20–44, `ScenePipeline.cpp` L90–134, L160–240, L245–350, the two fixtures. Corpus present (c1b171f, per file 16); the one corpus fact I lean on is G's 1 dB jnd (Vorländer Table 6.1, as cited in AX42 and my files 18/23). Settled items not rated.

## D-H3 (a)

**NOT MY MATTER.** The pooled statistic is a rule about reference uncertainty (Seats 1, 2, 9, researcher), not about anything rendered: file 18's reconciled mean signed deviation at 500 Hz–2 kHz is +0.0009 dB, about 1/1000 of the G jnd, every per-case-band passes τ by ≥ 5×, AX45's text carries no pooled check, and the tail decay rate (B12) is untouched; nothing my criteria measure moves under (a)–(e).

## D-H3 (b)

**1. Reading.** Whether U at the default placement of two contract-limits fixtures is a Seat 6 (ii) breach or a true flag. Cues: decay/level accuracy (tail level against the room), state discontinuity (level steps under motion in the capped regime).

**What the rendered tail does (from the code).** The mechanism is unchanged in every option: the tail is the same seeded unit decay scaled per band by √(E_target/ē) (`matchTail` L245–248, `buildHybridOmni` L368–373). A shipped pilot (edge_values: 64 histories, VOV 0.95 on e1) only makes that per-band scale uncertain: ±0.76 dB (e0) and ±3.98 dB (e1) at 1 SE, differently per band, so a possible spectral tilt (criterion 3). Deterministic (fixed key, AX40): no click, no seam change, no run-to-run variation. The audible emitter in that fixture is e1 (+12 dB; e0 is −60 dB at 0.3 m), so what a listener would hear is a tail whose level is uncertain by about 4 jnd: U is *true* there. K-b3 (file 18) shows U raised at every placement through the capped branch alone (SE 0.93–3.3 dB with both-near 0): the cause is the cap, as stated. At open_field the capped SE (2.1–4.1 dB) sits on a tail whose whole energy is ≥ 104 dB below the direct sound (C1), ≥ 90 dB in the 12×12×6 to 30×30×10 boxes of my AX37 (5.4) condition (C1 addendum): even at +3 SE (≈ +7 dB at SE 2.4) it stays > 80 dB down. **So my (5.4) condition says this about U at an open field: estimator-true, listener-void.** A display rule keyed to the existing −60 dB ghost-tail line is consistent with it, provided the line is tested against E_target raised by 3·SE, so the suppression is robust to the very uncertainty it hides.

**2–4. Ranking and tension.**

| option | rating now / later | reason |
|---|---|---|
| **(d)** prefer | 0 / 1 | (a) plus (ii) gives Phase 10 the cause list it needs; (i) is Seat 1/6's note rule and is consistent with my (5.4) condition under the 3·SE margin. Later 1: the capped-regime level-step debt below is unaddressed by any option. Undo: a display-rule change, free. |
| **(a)** can live with | 0 / 1 | Nothing in the render changes; U describes a true 1–4 dB SE. Same later debt. Undo: a reading, free. |
| (b) can live with | 1 / 2 | edge_values is the only fixture that exercises the pilot-ships / long-window regime, which is where my criterion-1 risk lives; moving it removes the canary and (per K-b3) silences nothing anyway. Later: the regime goes untested at the limits; undo = restore the fixture plus a golden round, plus Seat 5's blast radius. |
| (c) cannot live with if its aim is silence here | 2 / 3 | A loop before the atomic push to make a predicate stop reporting an achieved SE of 1–4 dB would turn the note (the only place the user learns the tail level is unreliable) into a lie: criterion 2. If the reopening keeps the capped-branch SE > 0.33 dB leg, 2 / 2. |

**What each commits later phases to.** (a)/(d): Phase 11 shows U on slot-like user rooms (true); Phase 12 outdoor presets meet the capped branch and (d)(i) decides whether the note appears; Phase 10 must measure the step under motion in capped scenes. (b): a fixture change touches contract validation, the (5.4) finite-floor and −60 dB checks and `phase04_open_field_omni` (Seat 5). (c): predicate, note text, goldens.

**5. Evidence.** [From the code] tail scaling and `toFloatNoDenormal` as cited; T60 of edge_values alternates ≈ 0.56 s / 0.13 s between bands by Eyring (Decay.cpp L50; my arithmetic from the fixture: V 600 m³, S 1 112 m²). [Measured, file 18 K-b3] U through the cap at every placement. [Measured, C1 and its addendum] ghost-tail levels. [Corpus via AX42] G jnd 1 dB. [Hyp] the step size under motion in a capped heavy-tailed scene (my file 23 L34 saw 0.209 dB between 0.11 and 0.10 m at the W1 cap; at SE 4 dB it could be jnd-sized).

**6. Conditions.** (c) → 2/2 if the capped-branch SE leg survives any reopening. (b) → 1/1 if the original slot is kept as a reported (not asserted) case. (d)(i) → stays 0 if the −60 dB test uses E_target·10^(0.3·SE).

**7. Hand-offs.** Phase 10 / Seat 5 / Seat 1: in any capped scene the estimate at neighbouring placements is a 64–1 024-history draw with VOV up to 0.95; the level step per automation update there is unmeasured and is not fixture-specific. Seat 6/1: the (d)(i) note rule. Seat 9: whether α alternating 0.01/1.0 per band is a material.

**8. Premortem.** (a) lands, a producer automates a source along a corridor-shaped room, the tail level wanders by jnd-sized steps between capped draws, and Maisara hears it first in Phase 10's listening pack.

## D-H3 (c)

**1. Reading.** Whether "asserted to produce denormals" can be made true, or is read as satisfied by a negative probe. Cue: cost class (denormal CPU) is Seat 5's; mine is the IR path's numerics.

**From the code, the answer to my brief.** The whole build path is double: no `float` arithmetic exists in `ism/`, `tail/` or `diffuse/`; the only float on the path is the final conversion `toFloatNoDenormal` (Engine.cpp L51–55, L373), which zeros |v| < 1.2e-38. So a *float* denormal cannot reach the IR by construction, guard or no guard, and the bit-difference probe can only ever be negative unless a *double* denormal (|v| < 2.2e-308) changes a float bit, which needs an amplitude factor of ~1e270: unreachable. Double denormals *do* arise, in `BandNoiseGenerator::make` L145: `exp(−rate·j)` is subnormal where 708.4 < rate·j < 745.1. The probe set never reaches that: its mixed-α case is a 100 m cube, where the α 0.999 band still has T60 ≈ 0.39 s and rate·j_max ≈ 213. **A scene that does (my arithmetic, [derived, needs the run]):** dead_booth geometry (2.5 × 2.0 × 2.2 m, V 11 m³, S 29.8 m²) with α 0.01 at 63 Hz and 0.999 above, s 0.5: T60(63 Hz) ≈ 5.9 s → tail 8.9 s; T60(≥125 Hz) ≈ 8.6 ms → rate 0.0167/sample at 48 kHz → ≈ 2 190 subnormal samples per fast band (j ≈ 42 300–44 500), multiplied by O(1) noise, then by `norm` and `bandsAmplitude`, then flushed at the float conversion. The IR stays bit-identical (what the test asserts), while a direct detector (MXCSR DE / FPSR IDC, or `fpclassify` over `unit.bands`) would read *positive*. That makes AX37 (5.1) (i)'s clause literally true in the form (d) proposes: "produces denormals (double, in the tail envelope), flushed, IRs bit-identical".

**2–4. Ranking and tension.**

| option | now / later | reason |
|---|---|---|
| **(d)** prefer, with my scene added to the probe set | 1 / 0 | The detector work is Seat 5's; the clause becomes true rather than read away; a future positive is asserted from then on. Commits 05h to one hidden test on three OSes; undo trivial. |
| (b) bounded (one detector run, probe set + my scene, three OSes, before the push) | 1 / 0 | It is the input (d) needs; unbounded it would be 2. |
| (a) can live with | 1 / 1 | Honest about the property, wrong about the premise: the probe is under-powered by construction, so "satisfied by the negative result" rests on a criterion that cannot see what the clause names. Undo: a comment rewrite. |
| (c) can live with | 2 / 1 | An injected denormal in test code asserts the guard, which the convolver tests already cover (CrossfadingConvolver L359, PartitionedConvolver L227), and nothing about the build; it is not evidence. |

**5. Evidence.** [From the code] as cited; `kMaxMeanAbsorption` 0.999 and `kEyringConstant` 0.161 (Decay.h L15, L17) so the 8.6 ms T60 is not clamped away. [Hyp] that libm's `exp` returns subnormals in (−745, −708) on all three toolchains under D2; an `fpclassify` sweep is independent of that.

**6. Conditions.** (c) → 1 only as a companion to (d), never alone.

**7. Hand-offs.** Seat 5: detector per OS; the FTZ/DAZ flags also flush double on x86 and AArch64 (Denormals.h L5–7), so the guard's effect on the double path is real even though the IR cannot show it. Seat 2: the estimator's `exp(−γr)` weights (DiffuseEstimator.cpp L116, L134, L159) are far from underflow for the lattice range; confirm.

**8. Premortem.** (a) ships with the comment "asserted to produce denormals"; the contractor reads the probe, sees it cannot see a denormal, and files the test as decorative.

## D-H3 (e)

**1. Reading.** What a host `reset()` does to the audio under each option, and whether a stale IR can play across a realtime reset without breaking X11. Cues: state discontinuity (silence, level jumps, dropouts); criterion 6 (tailorable while audio runs).

**What the listener hears (from the code).** Today / (e-a) / (e-d): `engine_.reset()` drops every IR and clears history (RealtimeEngine.cpp L38–43, `resetAndDropIrs`); step 3 submits; with no IR and `blockStart_ == 0` the IR is installed at once (CrossfadingConvolver L278–285): full reverb from the first sample, no fade. The cost is on the calling thread: a wait bounded by cancel granularity plus, in the stale case, a full build (0.18–0.80 s; 2.0–2.6 s at 100 m / 96 kHz). From `buildHybridOmni` L220–414 the only use of `options.cancel` is the diffuse solve (L324–327); I did not read `planEmitter`, `renderImageSources` or `makeIrSet`, so the non-diffuse 2–2.6 s may be un-cancellable (Seat 2 confirms; it decides (e-c)). On the audio thread that is a whole-graph dropout of the same length. (e-b)/(e-c), stale case: `current_` is null, so the output is **silence, not dry** (L337–338: y_A = 0), for build + 2P, then a 30 ms equal-gain fade from zero at s0 = blockStart_ + P (AX31). The fade itself is click-free; the hole is the artifact: a one-track level event of −∞ for 0.2–2.6 s after play, mute/unmute or bypass (F9: reset is sent when a unit is re-added to the chain). How often stale: whenever transport stops mid-build, i.e. commonly under automation.

**Could a stale IrSet keep playing without breaking X11? Yes, in realtime mode.** X11 lives in the offline branch (drop, then "the next `process()` builds before the block"), which stays untouched. A realtime-only reset that clears the convolver's input history, pending output and counter (the host's "stop any tails" / "clears memory", F9, F11) but keeps `current_` (promoting `next_` if a fade was running) costs nothing audible: the reset instant has zero state, so any IR change there produces no output and no click. The stale→fresh switch then arrives as an ordinary AQ4 update (build + 2P, 30 ms, equal-gain; equal-power when `restoreGen_` is set, AX18): exactly what the listener was hearing before the stop. Cost to AX31/AQ4: none; no rule changes. Two bonuses for Seat 5 to weigh: nothing is built *or freed* on the calling thread (today step 2 frees the dropped 12 s IRs on it, phase-07 L116), and the "install at once" property is kept for the current-scene case (the kept IR *is* that IR). Realtime mode has no bit-identity requirement across resets (AX5 is offline); the realtime-emulation null tests do not exercise a mid-render reset as far as I read (Seat 5 confirms).

**2–4. Ranking and tension.**

| option | now / later | reason |
|---|---|---|
| **(e-k) mine: (e-b) with the realtime reset keeping the current IR; offline unchanged** — prefer | 1 / 1 | No stall, no silence; the stale case is an AQ4 update. Later: pulls 07c's `reset()` half into 05h (tests, scope); the enter-offline path still waits (bounded by K-e6) because the offline branch must not race the builder. Undo: revert to the drop, one test round. |
| (e-b) can live with | 2 / 1 | No stall, but a 0.2–2.6 s silent hole on the track in the stale case: criterion 1. Later 1: 07c condition 5 ("never silence") would have to repair it. |
| (e-c) can live with | 2 / 1 | Same hole as (e-b) plus a wait that is seconds if the synthesis has no cancel point. |
| (e-d) can live with | 2 / 1 | Signal is perfect; the exposure is a whole-graph dropout of 0.2–2.6 s reachable by VST3 spec (F1, F2, F6) in VST3, unspecified in AU, unmeasured in any host; (e-d) at least makes it visible and names 07c. |
| (e-a) can live with | 2 / 2 | As (e-d) without the bound or the assert: the dropout, if a host triggers it, is found by a user. |

**5. Evidence.** [From the code] as cited. [Read, high: file 12 F1, F2, F6, F9, F11] spec and wrapper facts. [Plan] phase-07 L128–141, AX31, AQ4, AX18. [Hyp] how often a host's reset lands mid-build; which hosts call `setProcessing(false)` on the audio thread (K-e7).

**6. Conditions.** (e-b)/(e-c) → 1/1 with the keep-IR rule above. (e-a)/(e-d) → 1/1 only if the per-host measurement shows no host in the matrix delivers `reset()` or the offline switch on the audio thread, or once 07c's `reset()` half lands and the quiesce wait is shown ≤ one host block.

**7. Hand-offs.** Seat 5: the keep-IR variant's thread rules, the D7 skip-rule bookkeeping for a reset that no longer "always submits" (ScenePipeline L210–213), whether any realtime test asserts install-at-once after reset, the scope pull. Seat 2: cancel points outside the solve (K-e6). Seat 6/8: what "settling" shows during the stale window under (e-b) versus the keep-IR variant (nothing to show: the old room keeps playing).

**8. Premortem.** (e-a) ships; a host delivers `setProcessing(false)` on its audio thread at every transport stop while the builder is mid-build in a 100 m room, the whole session drops out for ~2 s on stop, and Maisara hears it in her own DAW before any CI gate does. Under (e-b): "the reverb goes silent for half a second after play" is the first forum report.
