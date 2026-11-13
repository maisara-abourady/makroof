# 1 — Decider: convening round, phase 07c-1b (D-B1 … D-B5)

2026-11-13, corpus `docs/corpus/` @ c1b171f (14 files). Saved by the orchestrator from the decider's report.

## Five facts that change the framing (verified from the records; orchestrator to check)

1. **D-B1 — the finding is larger than the phase file says, and the instrument is suspect.** 8-builder p99.9 (Linux / macOS
   / Windows): run 41: 911 / 1 202 / **8 937** µs; run 42: 1 205 / 4 192 / **6 657** µs; run 44: 1 145 / 1 845 / **48 415**
   µs (Windows max 48 469). With **one** builder, macOS already reads 9 135 / 9 306 µs (runs 41, 42), Windows 6 243–8 300 µs.
   On macOS and Windows a 10 s loop completes only 953–1 936 callbacks (≈ 7 500 expected at a 1 333 µs period), so p99.9 is
   effectively the 1st–2nd largest sample. The instrument (`test_diffuse_records.cpp` L774–826) uses a normal-priority
   thread, wall-clock timing and `sleep_for` pacing. The phase file's 1 178 / 4 245 / 1 137 µs are from runs 43215018040 /
   43227272415 (files 19, 20).
2. **D-B4 — trigger quantity.** The record prints FLAG only on the until-audible sum > 5 s. Run 41 Linux keyless (4 995 ms)
   is not flagged; keyed (5 083) is. The 12 009 ms on Linux in run 44 is "provisional → exact (all settled)"; the trigger
   figure there is 8 996 / 8 965 ms. The trigger fires on all three OSes in all three runs except run 41 Linux keyless.
3. **D-B4 — Windows misses 5 s even without contention:** run 41's single instance 634 ms; 8 × 634 = 5.07 s. Measured
   8-instance per-instance means ≈ 0.6–1.3 s, i.e. 1.5–2.6× the single-instance load: contention from the earlier
   instances' background exact syntheses too.
4. **D-B5 — the macOS trigger already fired:** `MACTRIGGER` on two consecutive runs, 42 (median 2 223 ms) and 44
   (2 572 ms), both > 2 172 ms. AX38 4c: two consecutive runs over the trigger are "a defect under (d), remedy named, through
   `/fix-plan`". No record found that this was read (07c-1 / 07c-1b briefs, phase files, BUILD_PLAN). Added as D-B5 (vi).
5. **D-B5 — in-window against the old refs:** Linux −35.3 / −30.0 / +0.7 % (only run 44 in); macOS −9.0 / +38.4 / +5.3 %
   (none); Windows +14.4 / −28.2 / −12.7 % (none). The low-α / flutter ratio is far steadier: Linux 2.433–2.606, Windows
   2.439–2.674, macOS 3.318–5.048.

## PRD digest

Producers / DJs on macOS and Windows, any DAW, no spatial-audio knowledge needed. Multi-stem scenes from several instances
(FR-3D-5, FR-3D-6, FR-SIM-7, A5); movement automatable without audible artifacts (FR-SIM-6, NFR-3); reopening restores
exactly (NFR-6). Hard: no instance cap; no W_max cut / range change / seam (D-H1 (v)(d)); no scene-specific logic in
`src/sim` (NFR-8, FR-SIM-2); AX5 determinism; offline never interim (AX49, cond. 6); AQ4 30 ms; AQ10 as amended; AX18 FM-1;
AX47 (statistical interim only from 07c-2); AX48 FM-3′; AX49; AX38 (i) incl. "the builder's priority is not raised to
compensate"; phase-07c-1 cond. 12 "Builder threads keep their default priority"; latency reported (NFR-2); nothing reopens
a 07c-1 decision. Usability: "Accuracy is the top priority; CPU load and latency may be high, but the plugin must stay
usable in a DAW session" (NFR preamble; NFR-2). PRD silent on: callback deadlines on any machine, load-time limits, what an
instance plays at insertion.

## D-B1 — callback p99.9 with 8 concurrent builders (scope 3, cond. 12 (c))

Options: **B1-a** record only (hosted runners share cores; instrument not a host audio thread) — AX38 4c register, 'closes
at' Phase 13's release-machine re-check (as §0 row 06 for the macOS p99.9). **B1-b** re-instrument, then decide: callback
thread at the platform audio priority (time-constraint on macOS, MMCSS "Pro Audio" on Windows, SCHED_FIFO where permitted on
Linux, else "not available" printed); process() thread-CPU beside wall time; median / p99 / p99.9 / max, callback count,
overruns > period, builders 0/1/2/4/8, hardware-thread count; if the rise persists, owner Phase 13 scope 1 (running-build
limit); a record, not a gate. **B1-c** lower builder priority / QoS — changes cond. 12's "Builder threads keep their default
priority"; admissible only as a board DECISION on that row (FOR MAISARA amendment if it is her recorded decision);
priority-inversion risk vs AX38 (i) class (1). **B1-d** limit concurrently running builds process-wide (not instances),
e.g. ≤ hardware threads − 1 (cond. 12 (f) "the open remedy").

| seat | status | reason |
|---|---|---|
| 1 | convened | audibility of an overrun (dropout); which bar applies |
| 2 | convened | B1-c/B1-d lengthen rebuilds |
| 3 | convened | per-instance CPU; staleness under concurrent rebuilds |
| 4 | convened (narrow) | Phase 08 binaural raises per-callback CPU |
| 5 | convened (lead) | audio thread, worst-case callback, topology, CI records |
| 6 | convened | settling/staleness with many instances |
| 7 | convened | cost, release machines, compatibility wording |
| 8 | convened | editing an 8-stem scene while builds run |
| 9 | not required | no room reference |

Knowledge: K1 figures (known); K2 instrument (known from code); K3 runner vCPU (RQ1); K4 host audio scheduling (RQ2); K5
QoS / inversion (RQ3); K6 `sleep_for` granularity (RQ4); K7 whether "default priority" is her recorded decision (to check).

## D-B2 — is a fresh instance's first prepare "a load" under AX48 FM-3′? (scope 6, review M1)

Default scene `medium_room.json`; prepare builds ISM + stage-1 solve + AX49 interim synchronously (05i (iv): ≈ 145–430 ms per
instance at the AQ10 room). Options: **B2-a** insertion is a load (FM-3′ read to cover it; text clarified; test asserts the
synchronous solve; no code change). **B2-b** not a load: async solve, dry/silent until the first IrSet. **B2-d** insertion as
a keyed load: an embedded per-platform default-scene E_b with the five-part key, AX47 source (a), step 0, guarded by the
fingerprint test; NFR-8 to check. **B2-c** reduced (A)-budget estimate — out of bounds (AX47: statistical sources only from
07c-2), not rated.

| seat | status | reason |
|---|---|---|
| 1 | convened | what plays at insertion; gap noticed? |
| 2 | convened | stage-1 solve; B2-d's embedded level |
| 3 | convened | interim rules; first IrSet; fade from silence |
| 4 | not required | E_b shared across modes and ears (AX39, AX44) |
| 5 | convened (lead) | prepare on the host thread; host conformance |
| 6 | convened | time to first plausible scene; "no load gap or step" |
| 7 | convened | complexity of B2-d; PRD reading |
| 8 | convened | inserting a stem into a playing session |
| 9 | not required | default scene not a room reference |

Knowledge: K8 insertion time (known); K9 host call order setState vs prepare (RQ5); K10 host time limits (RQ5); K11 output
before the first IrSet (Seat 5 from code).

## D-B3 — window and tolerance for the AX47 mid-fade check (scope 7)

Derivation (for the interrogator): equal-gain a + b = 1, linear 30 ms ramp → gain moves ΔG = T / 30 ms across a window of
length T; the triangle inequality gives E_out(w) ≤ (1 + ΔG)² · max(E₁(w), E₂(w)) for any correlation ρ, so a correct
equal-gain implementation always passes; the check tests the law, its alignment and the gain sum. Equal-power adds ≈ +3 dB
at mid-fade where ρ ≥ 0.993 (AX18 FM-1; Vorländer §4.3 Eq. 4.15). Endpoints "rendered alone" equal the crossfade's
components only if K23 holds (one input history). Options (non-overlapping windows aligned to the fade start, tolerance
(1 + T/30 ms)² + float ε): **W-a** 1 ms (+0.28 dB); **W-b** 2.5 ms (+0.70 dB); **W-c** 5 ms (+1.34 dB); **W-d** one P = 512
partition at 48 kHz, 10.67 ms (+2.88 dB); **T-0** zero tolerance beyond ε (not proven valid per window). The load's
equal-power fade over another scene is recorded, not asserted.

| seat | status | reason |
|---|---|---|
| 1 | convened | acceptance test meaningful? |
| 2 | not required | analysis parameter, no engine item |
| 3 | convened (lead) | crossfades; owner of AX47 "Measurement" |
| 4 | convened (narrow) | per ear / channel in 08-3, 09 |
| 5 | convened | determinism on three OSes; K23 from code |
| 6 | not required | no control |
| 7 | not required | test-internal; speech excerpt licence is the session's (THIRD_PARTY) |
| 8 | not required | no producer-facing behaviour |
| 9 | not required | no room reference |

Knowledge: K12 AX18 ρ, Eq. 4.15 (known); K13 K23 (Seat 5 to confirm); K14 fade-start alignment per P (under-informed); K15
the bound (interrogator to check).

## D-B4 — AX49 reversal fired (scope 8)

Trigger (until-audible sum, keyless / keyed, ms): run 41 Linux 4 995 / 5 083, macOS 7 846 / 8 780, Windows 9 511 / 9 448;
run 42 6 283 / 6 265, 8 662 / 10 206, 6 572 / 6 232; run 44 8 996 / 8 965, 8 394 / 9 019, 7 703 / 7 729. Single instance
269–634 ms. Options: **C1** constructor-spectra cache (bit-identical; [Hyp] 20–25 %); **C2** parallel band-pair synthesis
(bit-identical); **C3** capped interim length (output-changing; Seat 9 L_p ≥ 0.31·T60, Seat 1 depth); **C4** D4 in
unit-decay form (≈ 147 MB; Seat 5 unrated); **C5** cheaper generator (output-changing; golden round; AQ10 "not optimised
before Phase 13"); **C6** (decider's variant) class-(1) CPU priority: other instances' background builds pause at cancel
points while any synchronous host call runs process-wide (output-identical); **C7** move to 07d (trigger added to 07d's
scope); **C8** record-only for hosted runners, read on Phase 13's release machines. No instance cap in any option.

All nine seats convened (Seat 5 lead; Seat 9 for C3).

Knowledge: K16 (known); K17 contention share (under-informed; per-instance breakdown printable); K18 C1/C2 speedups
(uninformed); K19 runner cores (RQ1); K20 C4 memory (under-informed).

## D-B5 — re-pin run selection, in-window bootstrap, constants, register entries (scopes 1–2)

(i) Runs: **S1** runs 41, 42, 44; **S2** only ≥ 3 runs on 07c-1b's final code (steward G1); **S3** S1 unless D-B1/D-B2/D-B4
change a restore/builder path, else S2. (ii) In-window when the ref is re-derived: **B-i** iterate (ref = mean of flutter
medians, drop runs outside ±5 %, recompute, ≥ 3 must remain; Linux 453 / 490 / 706 → mean 550, none within ±5 %); **B-ii**
ref = median, ±5 %; **B-iii** window width from the measured spread (never loosen to pass); **B-iv** anchor the growth
assertion on the low-α / flutter ratio (RG-1 form change, FOR MAISARA amendment). (iii) kMacGrowthTriggerMs: **M-a** 1.15 ×
mean of all green macOS medians of the selected runs (the old rule: 2 172 / 1.15 ≈ 1 889 = mean of the four measured
medians); **M-b** 1.15 × in-window mean. (iv) kSolveWarn / solveRefMs: k = largest max/mean over the in-window runs;
baselines = in-window means per OS and scene (05i rule); confirm or amend. (v) Low-α entries (macOS 23.68 / 38.78 / 47.15 s;
Windows 31.97 / 20.47 / 22.37 s): **E1** close under (c) only if ≤ 30 s on every selected run; **E2** close on the median
run; **E3** stay listed, 'closes at' 07d (at L_p ≥ L the restore still holds the full synthesis); **E4** 'closes at' Phase 13
if the runner is shown to be the cause. (vi) MACTRIGGER on 42 and 44: **X-a** a (d) defect, remedy 07d; **X-b** uncalibrated
(derived from pre-condition-9 medians; re-derivation is this scope), recorded, not a defect (may be FOR MAISARA).

| seat | status | reason |
|---|---|---|
| 1 | not required | gate calibration |
| 2 | convened | kSolveWarn, ns/eval |
| 3 | convened | rated RG-1's trigger (05h file 58) |
| 4 | not required | no chain item |
| 5 | convened (lead) | CI gates, assertion form |
| 6 | convened | RG-1 participant; load time |
| 7 | convened | manual run cost, 07d sizing |
| 8 | not required | no workflow change |
| 9 | not required | no room reference |

Knowledge: K21 GATE lines (known); K22 which 07c-1b changes touch the restore path (after D-B1/2/4); K23 runner variance
(RQ1); K24 MACTRIGGER read anywhere (orchestrator: grep the ledger).

## Seat briefs

Common: read CLAUDE.md, the phase file, phase-07c-1 conditions 7, 9, 12, BUILD_PLAN §2 AQ4, AQ10, AX18, AX38 (i)/(iv)/4c,
AX47, AX48, AX49, `docs/phases/phase-07d.md`, the session brief, files 41/42/44, and the five facts above. For each option
of each matter you are convened on: tension now / later (0–3), one-line reason, conditions of acceptance for every 2 or 3,
later debt (what it commits, cost of undoing, where the evidence arrives). Never an instance cap, W_max cut, range change or
seam.

- **S1:** D-B1 audibility of the observed overrun and the bar; D-B2 gap or synchronous build at insertion noticed?; D-B3
  meaningful acceptance test for equal-gain vs equal-power?; D-B4 C3 depth, C5 audibility, L4.
- **S2:** D-B1 recompute cost of B1-c/B1-d; D-B2 B2-d embedded level and NFR-8; D-B4 C1, C2, C5, C3 fidelity; D-B5 (iv).
- **S3:** D-B1 staleness under B1-c/B1-d; D-B2 first IrSet, fade from silence; D-B3 lead (window and tolerance; rate all;
  K23); D-B4 interim, bridge, coloration of C3/C5, C6 on settling; D-B5 (v), (vi) with your 05h file 58 trigger rating.
- **S4:** D-B1 narrow (Phase 08 callback load); D-B3 narrow (per ear / channel in 08-3, 09); D-B4 C4 and mode-switch.
- **S5:** D-B1 lead (B1-a…d; what the instrument measures; B1-c inversion vs AX38 (i) class (1)); D-B2 lead (host thread for
  prepare; output before first IrSet from the code; B2-a/b/d); D-B3 determinism, fade alignment per P; D-B4 lead (C1–C8, C4
  memory, C6 design); D-B5 lead ((i)–(vi), steward G1).
- **S6:** D-B1 settling with many instances; D-B2 time to first plausible scene; D-B4 load experience; D-B5 (iii), (v), (vi).
- **S7:** D-B1 cost of B1-b vs release machines, wording; D-B2 B2-d complexity; D-B4 schedule, 07d sizing, P1; D-B5 cost of
  S2 and (vi)'s PRD reading.
- **S8:** D-B1 editing an 8-stem scene during builds; D-B2 inserting a stem in a playing session; D-B4 opening an 8-stem
  project.
- **S9:** D-B4 C3 vs L_p ≥ 0.31·T60; C5 room fidelity.

## RESEARCH NEEDED

- **RQ1** GitHub-hosted runner hardware (`ubuntu-24.04`, `macos-15` arm64, `windows-2022`): vCPU/cores, SMT, memory, VM
  sharing, stated variability.
- **RQ2** Host audio-thread scheduling (CoreAudio IOProc time-constraint, Windows MMCSS "Pro Audio", Linux); can
  default-priority workers preempt them?
- **RQ3** Platform guidance on lowering worker priority / QoS and priority-inversion risks.
- **RQ4** `std::this_thread::sleep_for` resolution on macOS and Windows (MSVC STL, default timer resolution).
- **RQ5** Call order at project load and insertion (VST3 `setState` vs `setActive`/`setupProcessing`, AU, JUCE 8.0.17
  wrapper); host/validator time limits on instantiate/prepare (Logic, auval, pluginval).

D-B3 needs only Vorländer §4.3 (Eq. 4.14–4.16), §15.1 from the corpus. D-B5 (i) waits on D-B1, D-B2, D-B4 (K22).

Summary: all five CONVENE; no challenges to settled decisions yet (D-B5 (vi) and B1-c may become FOR MAISARA); NEEDS
MAISARA none (FM-D1-S3 already with her).
