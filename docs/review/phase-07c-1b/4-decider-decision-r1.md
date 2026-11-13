# 4 — Decider: decision round 1, phase 07c-1b (D-B1 … D-B5)

2026-11-13, corpus c1b171f. Positions: files 2-seat1 … 2-seat9; dossier: file 3 (R1–R21). Saved by the orchestrator from
the decider's report.

## PRD digest — file 1's, plus two additions
- **AX38 (iv) 10 s line:** "if the 8-instance, 100 m time until the last instance is audible at load exceeds 10 s, it goes to
  Maisara before the first release". Run 42 macOS keyed 10 206 ms crossed it once. Under the README it goes to the decider
  before the first release; not due now; carried into D-B4.
- **K7 settled:** cond. 12's "Builder threads keep their default priority (AX38 (i))" comes from board decision D-G1
  (`docs/review/phase-05i/13-decider-DG1.md` L154), citing AX38 (i)'s "the builder's priority is not raised to compensate"
  (board, `docs/review/phase-05b2/13-decider-round4-T4a-final.md` L62). In the AX38 row (BUILD_PLAN L160) Maisara is named only
  at the (iv) escalation and its record, not at (i). So it is **a plan default, not her recorded decision**; a board DECISION
  alone could change it (no option below does).

Orchestrator notes answered: (a) W-d = +2.64 dB accepted ((1 + 512/1440)² = 1.838); file 1's 2.88 dB withdrawn (≈ the
window-averaged equal-power excess, Seat 1 2.89, Seat 4 2.88 dB). (b) K24: no reading exists — a process defect, D-B5 (vi).
(c) K7 above. (d) 4d0bcf1 is test-only, no restore/builder path. (e) No silent borrowing: every deferral is a `/fix-plan`
line below.

## D-B1 — callback p99.9 with 8 concurrent builders
Knowledge: K1 known (fact 1; R16); K2 known (R16, code); K3 4 / 4 / 3 vCPU VMs (R1); K4 host audio threads real-time, default
workers cannot preempt them (R4–R8; macOS IOProc time-constraint a lead only, not load-bearing); K5 inversion (R9–R12); K6
Windows `sleep_for` → Sleep(2) on the tick (R13, R14; runner resolution uninformed, the instrument prints it); K7 plan default.
No load-bearing gap; no option defended by naming a cause of the low counts.

| opt | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| B1-a | 1/2 | 0/1 | 1/2 | 1/2 | 1/**3** | 1/2 | 1/2 | 1/2 | 0/0 | 3 | 22 |
| B1-b | 0/1 | 0/0 | 0/1 | 0/0 | 1/0 | 0/1 | 1/0 | 0/0 | 0/0 | 1 | 5 |
| B1-c | 1/1 | 1/1 | 2/2 | 1/1 | 2/2 | 1/2 | 1/1 | 1/2 | 0/0 | 2 | 23 |
| B1-d | 1/1 | 1/1 | 1/1 | 1/1 | 1/1 | 1/1 | 1/1 | 1/1 | 0/0 | 1 | 16 |

(Seat 9 not required.) Reasons: S5 B1-a 3 "if the Windows 48 ms … is even partly real, criterion 1 is broken and unmeasured";
S3 B1-c 2/2 "starved builders lengthen time-to-final … reverses cond. 12"; S5 B1-c 2/2 "lower-priority builder makes that
solve preemptible → unbounded host-thread wait"; B1-b's later 1s: S1 "measures the floor … counts overruns", S3 "thread-CPU
time … separates the convolver's cost", S6 "one more record; Phase 13 owns the remedy".
Working: no bound broken (B1-c a plan default only); B1-a dropped (S5 3 later); max 1: B1-b, B1-d; no composition lowers it;
sum B1-b 5 < B1-d 16.

**DECISION D-B1: B1-b.** Re-instrument cond. 12 (c) in `tests/unit/test_diffuse_records.cpp`; test-only, a record not a gate;
no `src/` change, no priority change, no instance cap. Spec:
1. Callback priority: macOS `THREAD_TIME_CONSTRAINT_POLICY`, period = constraint = 1 333 µs in mach units (R5); Windows MMCSS
   `AvSetMmThreadCharacteristicsW(L"Pro Audio")` (R6); Linux SCHED_FIFO, else `priority: not available (errno)` (R8;
   RLIMIT_RTPRIO); the priority actually obtained printed.
2. Pacing: absolute deadlines (`sleep_until` next period, spin the last ≈ 100 µs); Windows a high-resolution wait; the timer
   resolution in force printed.
3. Per callback: wall and thread-CPU time of `process()` (Windows `QueryThreadCycleTime` with a measured cycle rate; macOS,
   Linux `CLOCK_THREAD_CPUTIME_ID` / `thread_info`); the per-callback max of `lastProcessMultiplyAdds()` (Seat 3).
4. Sweep: builders 0 / 1 / 2 / 4 / 8, the 0-builder floor first (Seat 1).
5. Printed per point: callback count vs expected; median, p99, p99.9, max of wall and CPU; overruns > period and > period/2;
   `hardware_concurrency()`; the old instrument's figures beside, labelled "old instrument (R16)"; `INSTRUMENT INVALID` when
   count < 0.95 × expected.
6. Residual owner: an overrun > period at 8 builders with none at 0 → Phase 13 scope 1 (release machines), B1-d first candidate.

Load-bearing: D1-L1 at N ≤ 1 936 the printed p99.9 is the 1st–2nd largest (R16); D1-L2 a host render thread is real-time, a
default-priority thread is not (R4, R6, R7, R8); D1-L3 Seat 5 rated B1-a 3 later (2-seat5).

| seat | commits later phases to | undo | evidence | repaid when |
|---|---|---|---|---|
| S1 | zero underruns on a real host thread, verified only on real hosts | none | Phase 13 release machines | Phase 13 re-check with this instrument |
| S3 | convolver per-callback cost before Phase 08 raises builder load | none | 07c-1b runs; 08-4 binaural repeat | 08-4 repeats in both modes |
| S6 | one more record; remedy owned by Phase 13 | none | 07c-1b runs | Phase 13 scope 1 |

Strongest objection (Seats 1, 7, 8 premortem: the rise is real and the remedy waits): B1-b's sweep in this phase clears or
confirms it with a valid instrument, and 08-4 repeats it before release (Seat 4's condition). Confidence high. Reversal:
`INSTRUMENT INVALID` on every runner (back to Seat 5), or overruns > period at 8 builders with a clean floor (board on B1-d
at Phase 13, earlier if 08-4 shows it). PRD check: no hard constraint broken (FR-3D-5, FR-3D-6, FR-SIM-7, A5; AX38 (i)); NFR
preamble ("must stay usable"): B1-b measures it, B1-d fixes the unmeasured, B1-c strains AX38 (i); no PRD id points to B1-d
before the evidence.

## D-B2 — is a fresh instance's first prepare "a load"? → FOR MAISARA FM-B2
Knowledge: K8 145–430 ms (05i (iv)); K9 VST3 no order between setState and activation (R17, R18), JUCE prepareToPlay inside
`setActive` on the UI thread (R19), Apple heavy work in Initialize (R20); K10 partly (pluginval 30 s inactivity, R21; auval,
Logic not found) — not load-bearing for B2-a (today's behaviour); only B2-b needs a limit (Seat 5's condition); K11 (code,
Seat 5) first IR installed at the first boundary, no fade; silent before it.

| opt | S1 | S2 | S3 | S5 | S6 | S7 | S8 | max | sum |
|---|---|---|---|---|---|---|---|---|---|
| B2-a | 0/0 | 0/1 | 0/1 | 1/1 | 0/0 | 0/1 | 1/1 | 1 | 7 |
| B2-b (silent) | 1/1 | 0/1 | 1/2 | 2/2 | 2/2 | 1/1 | 1/1 | 2 | 18 |
| B2-d | 0/1 | 1/2 | 1/2 | 1/2 | 0/1 | 1/2 | 0/2 | 2 | 15 |

(Seats 4, 9 not required.) For B2-b, Seat 1's dry variant 2/1, Seat 6 the dry gap 2/2 ("silent would be 3"); the silent
variant carries Seat 6's 2/2 at minimum. B2-a wins on max and sum.

**FOR MAISARA FM-B2.** Question: is a fresh instance's first prepare (no restore, no saved level) "a load" under AX48 FM-3′?
Answer: "Instance insertion is a keyless load of the instance's default scene: its first prepare runs the stage-1 (A) solve
synchronously, class (1) at the AX38 gate, and its first IrSet is installed at the first partition boundary with no fade."
Rests on: NFR preamble ("Accuracy is the top priority; CPU load and latency may be high, but the plugin must stay usable in a
DAW session"); NFR-1; NFR-2 ("Heavy CPU and latency are acceptable when they buy accuracy"); FR-3D-6, A5; NFR-8; her decision
of 2026-11-10 as amended by FM-3′ (AX48: "With no IrSet current: the stage-1 (A) solve runs synchronously"). Reasoning:
FM-3′'s condition is "no IrSet current" and a fresh instance meets it — applying FM-3′ as written, a reading, not an amendment
(Seat 7 agrees); NFR-1 served (first sound = final level, AX47 (a), step 0); the cost (a UI-thread stall 145–430 ms) is the
kind NFR-2 accepts, inside `setActive` / Initialize where Apple places heavy work (R19, R20), far below pluginval's 30 s (R21).
Options against the PRD ids: B2-a serves NFR-1 and NFR-2, strains the preamble's "usable" only by a sub-second stall; B2-b
strains NFR-1 (silence or dry at first exposure; real time differs from offline for 0.15–0.43 s), eases the stall; B2-d serves
NFR-1 equally, adds a per-platform artefact, risks NFR-8 if in `src/sim` (Seat 2 "cannot live with"). Veto trigger: the
preamble's "usable" — a host timing out or "not responding" at insertion (cond. 11 trace, Phase 13 host matrix). AMENDS:
nothing.

Code and tests this phase: a `[pipeline]` test — a fresh `ScenePipeline`, no setState, prepare at 48 kHz on `medium_room`;
asserts `insertSolves == 1` with the solve completed before prepare returns; `lastSubmittedIrSet` carries a tail with diffuse
E_b bit-identical to a stage-1 solve of the same problem; the first IrSet installed at the first boundary with `fadeCount() ==
0`; plus the same in the prepare-then-setState order (both VST3 orders, R17). `insertSolves`, `insertMs` already printed
(4d0bcf1).

| seat | commits | undo | evidence | repaid |
|---|---|---|---|---|
| S2, S3 | from 07c-2, insertion takes 07c-2's stage-1 rules for statistical sources | one reading | 07c-2 loop | line in phase-07c-2 |
| S5, S8 | UI-thread stall at insertion; under contention waits at most one running solve | switch to B2-b, one test | cond. 11 trace; Phase 13 host matrix | Phase 13 host matrix reads insertion |
| S7 | Phase 08 binaural may lengthen the stall | as above | 08-4 records | 08-4 prints insertMs per mode |

Confidence high. Reversal: a host/validator time limit below the measured insertion time, or a hang in the cond. 11 trace →
B2-b (silent + fade-from-silence test) back to the board.

## D-B3 — window and tolerance for the AX47 mid-fade check
Knowledge: K12 Eq. 4.15 (Vorländer §4.3) keeps a cross term 2|p̂₁||p̂₂|cos(·) that vanishes only on broadband averaging, so
equal-power on correlated renders exceeds the louder endpoint; AX18 FM-1 ρ ≥ 0.993. K13/K23 from the code (Seats 3, 5): one
FDL, lanes accumulate the whole history, fixed order — with the same P, input and trim 0 dB an endpoint rendered alone is
bit-identical to the matching component. K14: s0 = (⌊r/P⌋ + 2)·P (the test owns the submit point); L = lround(0.030·fs) =
1 440 / 1 323 / 2 880 at 48 / 44.1 / 96 kHz. Code (`CrossfadingConvolver.cpp` L77–85, L323): rampIn = (float)(j/L), rampOut =
(float)(1 − j/L); o = gOut·a + gIn·b in float.

**D3-L1.** In a window of N_w samples the equal-gain g rises by Δ = N_w/L; ‖(1−g)a + gb‖ ≤ (1−g₀)‖a‖ + (g₀+Δ)‖b‖ ≤
(1+Δ)·max(‖a‖, ‖b‖), so E_out ≤ (1+Δ)²·max(E_a, E_b) for any ρ; correct code always passes. W-a 1 ms +0.285 dB; W-b +0.70;
W-c +1.34; W-d +2.64 dB. Equal-power at mid-fade, ρ ≈ 1, equal energies: 10·log10(1 + ρ) ≈ 3.0 dB; W-a's margin ≈ 2.7 dB.
**D3-L2.** Per sample |(1−g)a + gb| ≤ max(|a|, |b|) (weights in [0, 1], summing to 1); Seat 3 rates it valid 0/0.
**D3-L3.** Reconstruction tolerance 8u·(|a|+|b|), u = 2⁻²⁴: rounding of each gain (≤ u), each product (≤ u) and the sum (≤ u)
gives ≤ ≈ 4u·(|a|+|b|); 8u a factor 2. A one-sample offset of g gives 1/L ≈ 6.9·10⁻⁴ ≫ 4.8·10⁻⁷: caught.

| opt | S1 | S3 | S4 | S5 | max | sum |
|---|---|---|---|---|---|---|
| W-a | 0/0 | 0/0 | 0/1 | 0/0 | 1 | 1 |
| W-b | 0/0 | 1/1 | 0/0 | 0/0 | 1 | 2 |
| W-c | 2/1 | 1/2 | 1/1 | 0/1 | 2 | 9 |
| W-d | **3**/2 | 2/2 | 2/2 | 1/1 | 3 | 15 |
| T-0 (windowed) | 1/2 | 2/2 | 1/2 | 2/2 | 2 | 14 |

(Seats 2, 6, 7, 8, 9 not required.) Working: none broken; W-d dropped (S1 3); max 1 W-a, W-b; sum W-a 1 < W-b 2.

**DECISION D-B3: W-a**, with three companions and a fade-from-silence engine case; one file `tests/unit/test_ax47_midfade.cpp`,
tag `[ax47-midfade]`, in ctest on three OSes.
1. **Harness.** IrSets built by `ScenePipeline` (`lastSubmittedIrSet`): a load's AX49 provisional and exact tail; an edit's
   interim (D5 bridge or B1′ hold) and final. Fed to a single-threaded `RealtimeEngine` (or `CrossfadingConvolver`); submit
   between blocks at a test-chosen block; s0 from `fadeStartSample()`; each endpoint rendered alone (installed at the first
   boundary), same P and input; measured at the engine output, trim 0 dB. Assert `fadeCount()` and which IrSet pair faded; a
   step-0 skip prints "no fade (step 0)" and never counts as a pass. Grid P ∈ {128, 512}, fs ∈ {48 000, 96 000}.
2. **Window.** N_w = lround(0.001·fs) (≈ 3.3 % of the 30 ms AQ4 ramp); non-overlapping, aligned to s0; covering [s0 − 4·N_w,
   s0 + L + 4·N_w); tolerance from the sample counts (1 + N_w/L)²·(1 + 10⁻⁵), energies in double; windows with max(E_a, E_b) <
   −100 dB re full scale skipped, counted, printed; asserted **per output channel**, reported as the max over channels (Seat 4
   (P)).
3. **Companions.** (i) per sample |o| ≤ max(|a|, |b|) + 8u·(|a|+|b|); (ii) reconstruction |o − ((1 − j/L)·a + (j/L)·b)| ≤
   8u·(|a|+|b|), j = t − s0 computed independently in double; where |a| + |b| = 0, o exactly 0 (closes Seat 1's single-band gap
   and Seat 3's "step in g"); (iii) outside [s0, s0 + L) the output is bit-identical (memcmp) to the endpoint rendered alone
   (K23).
4. **Fade from silence (engine case).** A fresh engine runs k = 3 blocks with no IrSet, then the first submit; asserts output 0
   before s0; per sample |o| ≤ |b| with no ε (g ≤ 1, b representable, the rounded product cannot exceed |b|); per-window energy
   ≤ E_b·(1 + 10⁻¹²); (ii) and (iii) with a = 0. Exercises the path reached today only if a first build is late (K11).
5. **Equal-power load fade over another scene** (AX18): recorded, not asserted — per window 10·log10(E_out / max) and ρ over
   the fade (Eq. 4.15).
6. **Signals.** A seeded pink noise and a speech-like stimulus (**ruling s1**); ≥ 2 s of input precede s0 so both lanes carry a
   full history.

**Signal ruling: s1.** A deterministic, seeded speech-like stimulus generated in the test: a glottal pulse train f0 120 Hz with
±5 % seeded jitter through three two-pole resonators at 500 / 1 500 / 2 500 Hz; a 4 Hz syllabic envelope; pauses ≥ 200 ms, one
starting inside the fade. Why: (1) the assertions are proven for any input (D3-L1, D3-L2), so the stimulus only has to
exercise transients, onsets into silence and a speech-band spectrum (Seat 1's "speech with pauses"); (2) bit-identical on
three OSes (AX5), no download, licence row or committed WAV (CLAUDE.md small WAVs "only where needed"); (3) s2 and s3 bring
Seat 7 in on licensing for no gain in detection. Limits: resonator frequencies are test design parameters, not claims about
speech; not claimed to conform to ITU-T P.50 (unverified); the 07c-2 self-ABX still needs recorded speech (07c-2's matter).
Fallback if the interrogator reads AX47's "speech" as recorded speech: s2 (by checksum, THIRD_PARTY row), Seat 7 convened.

| seat | commits | undo | evidence | repaid |
|---|---|---|---|---|
| S4 | tight per-channel windows carried into 08-3 / 09 per ear and speaker feed | widen N_w | 08-3 / 09 CI | 08-3 / 09 extend (P) per ear / feed; mode switches recorded, not asserted |

Strongest objection: Seat 4 prefers W-b (0/0 vs W-a's 0/1); W-a holds on the sum, and Seat 5 (whose determinism margins Seat
4's debt points to) rated W-a 0/0. Confidence high (window, tolerance, companions; Eq. 4.15 + derivation); medium for s1 (read
from Seat 1's condition). Reversal: a false red on correct code falsifies D3-L1 or D3-L3 → the interrogator, never loosened; a
07c-2 tightening of AX47 to 0.5 dB leaves W-a valid (0.285 < 0.5). PRD check: NFR-1, FR-SIM-6 best served by W-a; W-b too,
coarser; W-c, W-d strain NFR-1 (1.34 / 2.64 dB faults hide); no hard constraint touched.

## D-B4 — AX49 reversal fired
Knowledge: K16 known; K19 known (R1); K17 contention share under-informed (why the remedy is not chosen here; printed in this
phase); K18 C1/C2 speed-ups uninformed ([Hyp] 20–25 %); K20 C4 memory under-informed; code (`NoiseTail.cpp` L78–108): band
spectra depend only on the filterbank and the FFT size. Choosing C1, C2, C4 or C6 as the remedy would rest on K17, K18, K20:
RESEARCH NEEDED for the remedy itself, answered by measurement, which C7′ schedules.

(C3, C5 vetoed: Seat 1 3/3 and 3/2; Seat 3 3/3 on C3.)

| opt | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| C1 | 0/0 | 0/0 | 0/0 | 0/0 | 1/1 | 0/0 | 0/0 | 0/1 | 0/0 | 1 | 3 |
| C6 | 0/1 | 0/0 | 1/1 | 0/1 | 1/1 | 0/1 | 0/1 | 1/1 | 0/0 | 1 | 9 |
| C1 + C6 (S3, S5 own; each seat's max) | 0/1 | 0/0 | 1/1 | 0/1 | 1/1 | 0/1 | 0/1 | 1/1 | 0/0 | 1 | 9 |
| C2 | 0/0 | 0/0 | 0/1 | 0/0 | 1/2 | 0/0 | 0/1 | 0/1 | 0/0 | 2 | 6 |
| C4 | 0/0 | — | 1/2 | 1/2 | 2/2 | 0/1 | 1/2 | 0/0 | 0/0 | 2 | — |
| C8 | 0/1 | 0/1 | 1/2 | 1/2 | 1/2 | 1/2 | 1/2 | 1/2 | 0/1 | 2 | 22 |
| **C7′** (conditions met) | 0/1 | 0/1 | 1/1 | 1/1 | 0/1 | 1/1 | 1/1 | 1/1 | 0/0 | 1 | 13 |

C7′ cells read from conditions: S3 1/2 → 1/1 (trigger carried into 07d, machine named); S4 1/2 → 1/1 (07d before 08-4 freezes
goldens); S5 0/2 → 0/1 (trigger in 07d's scope with C6 + C1 named); S9 0/1 → 0/0 (07d's C3 bound by 0.312·T60_b); S7 rated C7′
1/1 itself.
Working: C3, C5 dropped (veto). C1 alone and C1 + C6 are not complete answers: the cells rate them harmless but none shows
they bring the trigger under 5 s (fact 3: 8 × 634 = 5.07 s uncontended; Seat 2 "not enough alone"; Seat 4 ≈ double in
binaural); adopting one would rest on uninformed K17, K18. A "C1 + C6 now, residual to 07d" variant inherits C7′'s cells plus
Seat 5's C1 1/1 → sum ≥ 14 > 13. Max 1: C7′ (and the incomplete C1 / C6 rows); among complete answers C7′ 13 lowest; C7′
commits no code (cheapest to undo); keeps the phase within two sessions (Seat 7; note e).

**DECISION D-B4: C7′.** The AX49 reversal moves to phase-07d as an acceptance criterion with named candidates and conditions.
This phase adds records only (test code, not the restore path): record (h) prints per instance its restore time, the number of
background syntheses running at its start, `hardware_concurrency()`, and a prepare-first total (insertion + restore) beside the
trigger (Seat 5's records; Seat 8's K17 condition).
Load-bearing: D4-L1 Windows uncontended 8 × 634 = 5.07 s > 5 s (fact 3); D4-L2 C3, C5 vetoed (Seat 1 C3 3/3, C5 3/2; Seat 3
C3 3/3; Seat 9 C3 2/3); D4-L3 C1's key (filterbank, FFT size) (`NoiseTail.cpp` L85–108); D4-L4 run 42 macOS keyed 10 206 ms >
AX38 (iv)'s 10 s.

| seat | commits 07d to | undo | evidence | repaid |
|---|---|---|---|---|
| S1 | interims play as now until 07d | — | 07d | 07d bit-identical tests |
| S2 | C1 / C2 land late | — | 07d | 07d |
| S3 | trigger figure carried, machine named | — | 07d records | 07d criterion met |
| S4 | remedy scales with outputs (binaural output-1 decays; AX49 "M") | — | 08-3 / 08-4 | 07d before 08-4 freezes goldens; 08-4 re-reads the trigger in the heaviest mode |
| S5 | C6 + C1 designed in 07d | — | 07d TSan | 07d |
| S6, S8 | 5–10 s 8-stem loads until 07d | — | 07d | 07d before first release (P1) |
| S7 | 07d may split to 07d-b | — | 07d sizing | P1; phase-13 item 3 |

Strongest objection: Seats 3, 5, 6 prefer C1 + C6 now (Seat 5 "the contention … follows users to their machines"); it holds
because those seats rated C7 1/1 or lower on the very condition written here, and no measurement yet shows C1 + C6 clears 5 s.
Confidence medium (three cells read from conditions). Reversal: 07d's records show C1 + C6 + C2 cannot reach 5 s on Windows →
board on C4 or C3-pb under their conditions, never an instance cap. PRD check: C7′ serves the preamble ("usable", fixed before
release, P1) and NFR-6; C1 + C6 now serves the same earlier, unproven; C3, C5 strain NFR-1 (vetoed); no PRD id ranks timing
within the pre-release plan.

## D-B5 — re-pin
**(i) run selection**

| opt | S5 | S7 | max | sum |
|---|---|---|---|---|
| S1 | 1/1 | 0/1 | 1 | 3 |
| S2 | 0/0 | 1/0 | 1 | 1 |
| S3 | 0/1 | 0/1 | 1 | 2 |

(Read for S1: no D-B decision touches the restore path (D-B4 = C7′), so S3 reduces to S1 and Seat 5's "→ 1" holds.)
**DECISION D-B5 (i): S2.** ≥ 3 manual (`force`) CI runs on the head commit after the session's last code change, every job
green; runs 41 / 42 / 44 printed, never baselines; satisfies steward G1; the same runs carry the D-B1 and D-B3 evidence. Debt
none (Seat 7's 1 is now-only).

**(ii) and (iv): CONVENE (second round) before deciding.** Only Seat 5 rated (ii), only Seats 2 and 5 rated (iv). B-iv and
(iv″) amend RG-1's form and cond. 7's "never an out-of-window run as a baseline"; RG-1 is an answer given for her (§6
2026-11-11, `AMENDS her decision of 2026-11-10`); Seats 3 and 6 took part in RG-1 and were not briefed: deciding now would be
UNDERCONVENED. Provisional reading for the seats to attack:
- **B-iv:** assert the low-α / flutter median ratio ≤ 1.10 × the mean ratio of the S2 runs on Linux and Windows; on an OS where
  the S2 runs' ratio max/min exceeds 1.10, print only (macOS today 3.32–5.05); absolute medians printed with WARNING; flutter
  14 × worst ≤ 30 s stays asserted as the backstop; the ±5 % flutter window re-derived as the S2 mean and printed.
- **(iv″)** (= Seat 2 (iv′) ≡ Seat 5's fallback): solveRefMs = mean of the S2 runs per OS and scene; k per OS = the largest
  max/mean over those runs; PROVISIONAL (print-only, never a (d) trigger) until ≥ 3 in-window runs exist; the same-run low-α /
  flutter ns-per-eval ratio printed.
Brief: Seats 3, 6, 7 rate B-i, B-ii, B-iii, B-iv and (iv″) now / later with conditions (files: file 1 fact 5, 2-seat5 (ii),
(iv), 2-seat2 (iv), RG-1 `docs/review/phase-05h/60-…`, `70-…`, BUILD_PLAN L160 4c); Seat 2 rates B-iv. If B-iv survives it is
a FOR MAISARA amendment: `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (via RG-1); PRD ids
the preamble ("usable") and NFR-6, against CLAUDE.md "never loosen". Does not block code work.

**(iii) macOS trigger**

| opt | S5 | S6 | max | sum |
|---|---|---|---|---|
| M-a (S2 runs) | 1/1 | 1/1 | 1 | 4 |
| M-b | undefined | 1/2 | 2 | — |
| S6-k (factor from spread, ≥ 1.15) | — | 1/1 | — | — |

**DECISION D-B5 (iii): M-a.** kMacGrowthTriggerMs = ⌊1.15 × mean of the green macOS low-α medians of the S2 runs⌋ — the
existing rule ("re-derived at the 07c re-pin"), no change of form; Seat 6's spread factor rated by Seat 6 alone, not adopted.
Debt: Seats 5, 6 (1 later) — ×1.15 against a ×1.68 spread can flag weather; evidence 07d's runs; repaid at Phase 13.

**(v) register entries**

| opt | S3 | S5 | S6 | max | sum |
|---|---|---|---|---|---|
| E1 | 0/1 | 0/0 | 0/1 | 1 | 2 |
| E3 | 0/1 | 0/1 | 0/1 | 1 | 3 |
| E2 | 2/2 | 2/2 | 2/2 | 2 | — |
| E4 | 2/2 | 1/1 | 1/1 | 2 | — |

**DECISION D-B5 (v): E1.** Each low-α entry (macOS, Windows) closes under 4c (c) only if 14 × worst ≤ 30 s on every S2 run at
both gated builds; otherwise stays listed with 'closes at' phase-07d (scope 1); `kGateRegister` `listed` flags follow. Debt:
Seats 3, 6 — 07d owns the corner; repaid when 07d closes it.

**(vi) MACTRIGGER on runs 42 and 44** — variant **X-d** (cells read from conditions: S3 1/1 (X-c's diagnosis included); S5 1/0;
S6 1/1 (all three X-b conditions met); S7 1/1 ("X-a plus a re-derivation")): max 1, sum 7; X-a max 2 (S3 later 2); X-b S7 2/2.
**DECISION D-B5 (vi): X-d**, applying the rule as written (no amendment, not FOR MAISARA):
1. Record runs 42 and 44 as "two consecutive runs over 2 172 ms, a defect under 4c (d)", remedy phase-07d; the record names the
   medians, flutterDev and the ratio; a ledger row records that the fired trigger went unread (K24).
2. Apply the trigger re-derived under (iii) to runs 42, 44 and the S2 runs; print it.
3. The restore gate prints the per-stage split (ISM, solve, synthesis, assembly) per gated scene on every OS on the S2 runs
   (test-only).
4. 07d closes the defect with its remedy, or by recording a recalibration — the split shows per-emitter synthesis time unchanged
   with the work pins equal, and the re-derived trigger not exceeded on two consecutive runs.
5. MACTRIGGER, OVER30S and GROWTH written to `$GITHUB_STEP_SUMMARY` or emitted as `::warning::` annotations; `pytest tools/ci`
   (`test_ci_workflow.py`) stays green.
Debt: Seats 3, 6 — 07d may inherit a non-defect (the split repays it); Seat 7 — the precedent held by recording "as written".

## Plan text for /fix-plan (only after the interrogator's SURVIVES)
1. **BUILD_PLAN AX38 (i) / cond. 12 (c) note:** "Cond. 12 (c) record re-instrumented in 07c-1b (D-B1 B1-b): the 05i/07c-1 p99.9
   on a normal-priority `sleep_for` thread is the 1st–2nd largest of 953–1 936 callbacks (R16), not a host audio thread
   (R4–R8); 07c-1b figures [runs]; a residual (overrun > period at 8 builders, none at 0) is Phase 13 scope 1's, B1-d first
   candidate; never an instance cap." + §6 row.
2. **phase-13 scope 1:** re-measure with 07c-1b's instrument on the release machines (buffer 64; 0/1/2/4/8 builders); the
   residual rule; B1-d = a process-wide limit on running background builds ≤ hardware threads − 1, class (1) and offline exempt,
   slot taken before the gate and never under `stateMutex_`, `quiesce()` waking slot waiters.
3. **phase-08-4:** the AX38 (iv) binaural repeat runs 07c-1b's callback instrument in both modes in one CI run, printing the
   callback count and the priority obtained; re-reads the AX49 8-instance trigger in the heaviest mode and returns it to the
   board if it fires.
4. **AX48 (keyless load):** the FM-B2 answer sentence; tests "a fresh instance's first prepare runs the stage-1 solve
   synchronously (`insertSolves`), first IrSet at the first boundary, no fade, both VST3 orders" + §6 row + "Decided for
   Maisara" line.
5. **phase-07c-2:** "Instance insertion (FM-B2) takes 07c-2's stage-1 rules for statistical sources."
6. **AX47 Measurement:** replace with "Wet pink-noise and seeded speech-like renders (D-B3) check, per 1 ms window aligned to
   the fade start (N_w = lround(0.001·fs), 1/30 of the AQ4 ramp), per output channel, E_out ≤ (1 + N_w/L)²·max(E_a,
   E_b)·(1 + 10⁻⁵), plus a per-sample bound, a reconstruction to 8u·(|a|+|b|), and bit-identity outside the fade; fades from
   silence at ε only; the load's equal-power fade recorded." Tick phase-07c-1b scope 7 / AC 7 to this; Seat 4's (P) into
   phase-08-3 and phase-09: "the AX47 mid-fade check per ear / speaker feed".
7. **AX49 Reversal:** "(trigger met 2026-11-12 … to the board in 07c-1b) → moved to phase-07d by D-B4 (C7′)."
8. **phase-07d:** new criterion "8-instance Windows load at the rated corner ≤ 5 s on record (h), with the runner label and vCPU
   printed (R1); AX38 (iv)'s 10 s line read on the same record (run 42 macOS keyed 10 206 ms); a post-07d exceedance goes to the
   decider for Maisara before the first release". Candidates in order: C1 (transient shared cache keyed by filterbank + FFT
   size, freed when unused, counted under AX38 (i), not (ii); W1/W2 "no cache credit"); C6 (process-wide count of synchronous
   host calls; background syntheses and builders sleep at cancel points; the gate holder never pauses; `quiesce()` wakes;
   offline not paused; bit-identity on resume tested; record (h) prints provisional → exact per instance); C2 only on the gate's
   pool with C6; C4 only as per-(emitter, outputIndex) unit decays, shared, memory measured; C3 only as C3-pb (L_p,b ≥
   t_mix,e,max + 0.312·T60_b + 0.1 s); C5 only with Seat 1's ABX, Seat 2's equivalence test and Seat 9's BRAS condition, before
   Phase 12 and the first release. Any remedy scales with the number of outputs (Seat 4); 07d lands before 08-4 freezes its
   goldens; the macOS (d) defect from D-B5 (vi) with its closure rule.
9. **AX38 4c:** the MACTRIGGER defect entry (X-d); the re-derived trigger (M-a); register closures (E1); the step-summary rule;
   + §6 row and CHANGELOG reason (scope 1).
10. **Ledger:** rows for D-B1 … D-B5 and K24 ("MACTRIGGER fired on 42, 44 unread").

## Summary
| id | decision | state | worst-off (cell) | sum | conf. | PRD bound | corpus | reversal |
|---|---|---|---|---|---|---|---|---|
| D-B1 | B1-b re-instrument | proposed | S5, S7 (1 now) | 5 | high | FR-3D-5/6, FR-SIM-7, A5; AX38 (i) | — | INSTRUMENT INVALID, or overrun at 8 builders with a clean floor |
| D-B2 | FM-B2: insertion is a keyless load | for Maisara | S5, S8 (1/1) | 7 | high | preamble, NFR-1, NFR-2, NFR-8 | — | host limit or hang |
| D-B3 | W-a, 1 ms + companions; signal s1 | proposed | S4 (1 later) | 1 | high (s1 medium) | NFR-1, FR-SIM-6 | Vorländer §4.3 Eq. 4.15 | false red on correct code |
| D-B4 | C7′ → 07d; records now | proposed | several 1 | 13 | medium | preamble, NFR-6, P1 | — | 07d cannot reach 5 s |
| D-B5 (i) | S2 | proposed | S7 (1 now) | 1 | high | — | — | — |
| D-B5 (ii), (iv) | B-iv / (iv″) provisional | convening (S2, S3, S6, S7) | — | — | — | preamble, NFR-6 | — | — |
| D-B5 (iii) | M-a on S2 runs | proposed | S5, S6 (1/1) | 4 | high | — | — | Phase 13 |
| D-B5 (v) | E1 | proposed | S3, S6 (1 later) | 2 | high | — | — | — |
| D-B5 (vi) | X-d | proposed | S3, S6, S7 (1/1) | 7 | medium | — | — | 07d split |

Challenges to settled decisions: none (the AX38 (iv) 10 s line, crossed once, carried into 07d, not challenged).
Decided for Maisara (applied once they survive): D-B1 (re-measure before fixing; PRD preamble, FR-3D-5; Seats 5, 7 gave most,
get a valid Phase 13 number); FM-B2 (adding an instance computes its default room in full before it plays, 0.15–0.43 s; NFR-1,
NFR-2, preamble; Seats 5, 8 gave most, get Phase 13's host-matrix check; amends nothing); D-B3 (1 ms windows + exact
reconstruction, generated speech-like signal; NFR-1, FR-SIM-6; Seat 4 gave most, gets per-channel assertions); D-B4 (the
8-stem load fix moves to 07d with a hard line before the first release; preamble, NFR-6; Seats 6, 8 gave most, get 07d's
criterion); D-B5 (i), (iii), (v), (vi) (fresh runs; trigger by the old rule; entries close only if they pass on every run; the
fired macOS trigger recorded as a defect for 07d and no longer unread; preamble, NFR-6). NEEDS MAISARA: none new (FM-D1-S3
already with her).

Files: file 1, 2-seat1 … 2-seat9, 3-researcher (same directory); `docs/phases/phase-07d.md`; `docs/BUILD_PLAN.md` (L160,
L169–171); `src/sim/conv/CrossfadingConvolver.cpp` (L70–85, L311–323); `src/sim/tail/NoiseTail.cpp` (L78–108).
