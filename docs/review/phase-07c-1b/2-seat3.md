# 2 — Seat 3 position (D-B1 … D-B5), round 1

2026-11-13, corpus c1b171f (Vorländer §4.3 Eq. 4.14–4.15 read). Saved by the orchestrator from the seat's report.

## D-B3 (lead)
Reading: the window and tolerance of the AX47 "no mid-fade value exceeds the louder endpoint" check, relative to the AQ4 30
ms ramp. Cues: state discontinuity (law), perceptual equivalence (level).

**K23 holds, from the code.** `CrossfadingConvolver` has one `fdl_`; lanes A and B both read it (`advanceLane` /
`finishLane`), so y_A, y_B are exactly x*A, x*B; summation order fixed by unit index u, independent of host block size. An
endpoint "rendered alone" (installed at the first boundary, the `blockStart_ == 0` path, same P, same input, no reset) is
bit-identical to the matching crossfade component. Caveats: (a) no `reset()` / `resetKeepIr` between renders (clears the FDL);
(b) `ScenePipeline` applies the output-trim ramp after the engine (L961–987): hold trim at 0 dB or measure at the engine
output; (c) the skip rule (L629–644) can make a settling step 0 with no fade — print "no fade (step 0)", never count it as a
pass; (d) latest-wins mailbox: an interim can be superseded before it fades — assert `fadeCount()` and which IrSet pair
faded; (e) s0 = `fadeStartSample()` is a multiple of P, windows aligned to s0; L = lround(0.030·fs) = 1440 @ 48 kHz, 1323 @
44.1 kHz, 2880 @ 96 kHz.

**Bound (checked).** Equal-gain: ‖(1−g)a + gb‖ ≤ (1−g0)‖a‖ + (g0+Δ)‖b‖ ≤ (1+Δ)·max, so E_out ≤ (1+Δ)²·max(E_a, E_b) for any
ρ; correct code always passes. dB: W-a +0.28, W-b +0.70, W-c +1.34; **W-d +2.64, not +2.88** (Δ = 512/1440 = 0.356;
20·log10 1.356 = 2.64). A swapped law (equal-power on a correlated same-scene step) gives +3.0 dB at mid-fade (Eq. 4.15 cross
term, 10·log10(1+ρ), ρ = 1; 2.99 dB at ρ = 0.993).

**Choice: W-a.** N_w = lround(1 ms·fs) samples, non-overlapping, aligned to s0; tolerance (1 + N_w/L)² from the sample counts,
plus relative float ε 1e-5; windows with max(E_a, E_b) below −100 dB re full scale skipped, counted and printed. Additions,
each proven: (1) **fade from silence**: a = 0, out = g·b (or sin·b) ≤ b under either law → tolerance ε only (factor 1);
(2) **outside [s0, s0+L)**: output is a or b alone → assert a bit-identical null against the endpoint rendered alone (tests
K23 and the alignment); (3) **load fade (equal-power)**: record the per-window excess and ρ over the fade, read against Eq.
4.15.

| option | label | now | later | note |
|---|---|---|---|---|
| W-a 1 ms | prefer | 0 | 0 | resolves a gain-sum error ≥ 0.29 dB (< AX47's 0.5 dB reversal value); 2.7 dB margin on a swapped law |
| W-b 2.5 ms | can live with | 1 | 1 | misses gain-sum errors 0.5–0.7 dB (the reversal bound's range); L/N_w = 12 at 48 kHz |
| W-c 5 ms | can live with | 1 | 2 | blind up to +1.34 dB, above the 1 dB G jnd (Vorländer Table 6.1 via AX47); 08-3/09 inherit it per channel |
| W-d 10.67 ms | cannot live with | 2 | 2 | 0.36 dB margin on a swapped law at ρ = 0.993; N_w does not divide L |
| T-0 windowed | cannot live with | 2 | 2 | a correct implementation can exceed it (energy early in a window as the gain rises: factor 1+Δ² > 1); a false red invites loosening |

Conditions: W-d → 1/1 only at N_w ≤ 5 ms (= W-c). T-0 is valid **per sample**: |out(t)| ≤ max(|a(t)|, |b(t)|) + ε (gains in
[0,1], summing to 1) → 0/0 as a companion to W-a. Note for Seats 1, 5: no energy bound catches a **step** in g (a ramp step
stays convex and passes every window, yet clicks); condition for later 0: a null reconstruction out(t) − [(1−g(t))a(t) +
g(t)b(t)] ≤ −120 dB with the documented g(t) and s0, or the click detector (`tools/acoustics clicks`) on the same renders.

## D-B1

| option | label | now | later | reason |
|---|---|---|---|---|
| B1-b | prefer | 0 | 1 | thread-CPU time of process() separates the convolver's cost from preemption; with 953–1 936 samples p99.9 is the max |
| B1-d | can live with | 1 | 1 | throughput unchanged under contention (fact 3: already 1.5–2.6×); staleness per instance → N/(hw−1)×build; not an instance cap |
| B1-a | can live with | 1 | 2 | per-callback cost unmeasured before Phase 08 raises it; a CPU figure from no named machine |
| B1-c | cannot live with | 2 | 2 | starved builders lengthen time-to-final and, from Phase 10, movement latency; reverses cond. 12 |

Conditions: B1-d → 1/0 latest-wins per instance (superseded generation dropped, never run), fairness across instances,
hold/interim always plays; B1-a → 1/1 B1-b's instrument run once before Phase 08; B1-c none in this seat (Seat 5's inversion
analysis and a board decision on the cond. 12 row). Addition for B1-b: the per-callback max of `lastProcessMultiplyAdds()`
(work spreading checked runner-free).

## D-B2
From the code: an IrSet taken at the first boundary after prepare is installed in full, no fade; a later one fades in from
silence (y_A = 0), click-free.

| option | label | now | later | reason |
|---|---|---|---|---|
| B2-a | prefer | 0 | 1 | first IrSet exact at the first boundary; offline = real time from sample 0; later under 07c-2's statistical sources insertion falls under AX47 like any load |
| B2-d | can live with | 1 | 2 | same audio, saves only the solve (the AX49 synthesis still runs); the level regenerated per E_model bump, per platform |
| B2-b | can live with | 1 | 2 | clean fade from silence, but real-time start differs from offline for 145–430 ms (seconds under 8-instance contention) |

Conditions: B2-d → 1/1 generated by a CI tool, never by hand; full five-part key (mismatch → B2-a); outside `src/sim` (NFR-8,
Seat 2). B2-b → 1/1 offline stays synchronous (AX49 cond. 6); time to the first IrSet printed; scope 7's fade-from-silence
check covers it.

## D-B4

| option | label | now | later | reason |
|---|---|---|---|---|
| C1 | prefer | 0 | 0 | bit-identical; needs a test proving it |
| C6 | prefer | 1 | 1 | output-identical; earlier instances play the provisional longer (AX47 (b) step ≤ 0.06 dB), more listening on the L_p cut L4 has not tested |
| C2 | can live with | 0 | 1 | bit-identical; more threads per instance compounds D-B1 |
| C8 | can live with | 1 | 2 | a named machine is right, but fact 3 (5.07 s uncontended) shows it is not only the runner |
| C7 | can live with | 1 | 2 | borrows from 07d's sizing |
| C4 | can live with | 1 | 2 | ≈ 147 MB × 8 ≈ 1.2 GB; memory scales (criterion 5) |
| C5 | can live with | 2 | 2 | output change + golden round; spectral purity, decay accuracy |
| C3 | cannot live with | 3 | 3 | any cap below L_f = t_mix + 0.312·T60 breaks AX47 (b)'s ≥ 18.7 dB construction and Seat 9's line; at T60 8 s a 2 s cap stops at ≈ −14 dB, then the tail grows at handover |

Conditions: C3 none short of keeping L_f (then no cap); C5 → 1/1 one generator for provisional and exact (else AX49's prefix
identity and the −18.27 dB check break), band EDC within 5 %, the AX11 ensemble and AX47 (b) pass; C4 → 1/1 memory measured
per instance and shared process-wide where the key is identical; C7/C8 → 1/1 the trigger and its figure carried into 07d /
Phase 13 acceptance, read on a named machine; C6 stays 1/1 only if record (h) prints provisional→exact per instance, cancel
points preserve bit-identity on resume, and resume is guaranteed when the host call ends. Composite (own): C1 + C6 now, C2 if
Seat 5 clears it, the residual read under C8.

## D-B5 (v), (vi)
**(v)** E3 prefer 0 / 1 (at L_p ≥ L the restore holds the full synthesis by design; 07d owns the corner); E1 can live with 0 /
1 (gives E3: macOS 38.78 / 47.15 s and Windows 31.97 s fail); E2 cannot live with 2 / 2 (closes Windows on a median while one
run is 7 % over); E4 cannot live with 2 / 2 (runner cause not shown; removes the synthesis detector until Phase 13).
Conditions: E2, E4 → 1 only with a split-timer showing the synthesis stage unchanged on that OS.

**(vi)** 05h file 58 r3 condition 2: two consecutive macOS triggers are "(v)(d)'s trigger (defect, remedy named), not
weather"; otherwise the later rating returns to 2. The restore changed by design since (cond. 9/12), so 2 172 ms is
uncalibrated against the new code — but a deliberate change does not show there is no regression; the macOS low-α / flutter
ratio 3.32–5.05 vs Linux 2.43–2.61 points to a macOS-specific load.

| option | label | now | later |
|---|---|---|---|
| X-c (own) | prefer | 1 | 1 |
| X-a | can live with | 1 | 2 |
| X-b | cannot live with | 1 | 2 |

X-c: record that the trigger fired and was not read (K24); diagnose by scope 1's re-derivation plus a per-stage split timing
on macOS; if the synthesis stage is unchanged per emitter (work pins equal), record a recalibration; otherwise a defect with
remedy 07d. X-a may send 07d a non-existent defect. X-b reads the trigger as weather, which file 58 r3 ruled out; → 1/1 only
with X-c's split timing.

Evidence: K23, fade timing, trim ramp, skip rule from the code (`src/sim/conv/CrossfadingConvolver.{h,cpp}`,
`src/sim/RealtimeEngine.cpp` L32, `src/plugin/core/ScenePipeline.cpp` L629–648, L961–987); the bound and dB figures own
arithmetic; Vorländer §4.3 Eq. 4.15; Table 6.1 via AX47; AX49 / §6.4.1 Eq. 6.4; C1's 20–25 % and C6's settling cost [Hyp].
Hand-offs: interrogator (W-d figure, windowed bound); Seat 5 (anything time-varying after the convolver; C2, C6; B1-c); Seat 1
(energy bound + null/click as the acceptance test; L4 under C6); Seat 4 (per ear/channel in 08-3, 09); Seat 9 (C3); Seat 2
(B2-d NFR-8). Premortem: W-c or W-d chosen; a +0.8 dB gain-sum error (or a step in g) passes green; the 07c-2 self-ABX or
Maisara on a load hears a level bump at every settling step.
