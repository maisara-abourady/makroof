# Phase 07d — Restore gate at the long-T60 corner (condition 9's split)

Size: **S–M** (remainder, if needed: `07d-b`) · Depends on: 07c-1 and [07c-1b](phase-07c-1b.md) `done` (07c-1b closes or
names 07d for the AX38 4c entries on the re-pinned gate) · Created 2026-11-12 under phase-07c-1
condition 9's split clause ("If this phase's loop finds condition 9 does not fit here, a `phase-07d.md` of size S–M
is created") by the phase-07c-1 decision loop (FM-2′; AX49 "Long-T60 corner") · Lead subject matter: not named by
the loop; Seats 5 and 7 are convened on the inputs below (AX49 future-debt register) · Read first, in this order:
`CLAUDE.md`; this file in full [and `docs/phases/phase-07c-1.md`, condition 9 and record (h)]; `docs/BUILD_PLAN.md`
§2 **AQ10 (amended 2026-11-10 and 2026-11-12), AX18, AX38 (4c and its register), AX47, AX48, AX49**;
`docs/review/phase-07c-1/12-decider-decision-r3.md` §6–§9 and `13-interrogator-on-file12.md`; PRD NFR-1, NFR-2,
NFR-6 and the NFR preamble.

---

## Raise with Maisara (first message and PR)

None from the loop that created this phase.

## Goal

Close the AX38 4c restore-gate register entries that phase-07c-1 cannot close: at the long-T60 corner, where
AX49's interim is the full tail (L_p ≥ L), the restore still contains the full unit-decay synthesis. (phase-07c-1
decision loop, decider file 12 §8)

## Assumptions in force

AX47, AX48 and AX49 as decided by phase-07c-1's loop (2026-11-12), and AQ10 (amended 2026-11-12): the restore gate
measures ISM + matching + the AX49 interim tail + mix (keyless: plus the AX48 stage-1 solve) under the unchanged
worst-of-10 / 14 × worst ≤ 30 s rule, in AX38 4c's register form. Never a W_max cut, a range change, a formulation
seam (D-H1 (v)(d)) or an instance cap (PRD FR-3D-5, FR-3D-6, FR-SIM-7, A5).

## Scope

1. **Close the AX38 4c macOS and Windows entries at the long-T60 corner.** At the gated low-α cube
   (`cube100_lowalpha0.05_s0.3`, T60_max 50.5 s, exact tail L = 12 s) AX49 builds the exact tail synchronously
   (L_p ≥ L), so the restore is the pre-07c restore minus the solve. (decider file 12 §6, row 38; K22)
   *Closed in phase-07c-1b (E1, 2026-11-13):* both `cube100_lowalpha0.05_s0.3` entries closed under AX38 4c (c) on
   S2 runs 43389296112, 43402114873, 43412038058 (14 × worst macOS 23.46 / 22.44 / 24.08 s, Windows 20.24 / 15.96 /
   19.59 s); a later OVER30S is handled as AX38 4c E1 states.
2. **Candidates, in order** (decided through the board loop and recorded as an AX row before any code; decider file
   12 §8; order and conditions from the phase-07c-1b loop, D-B4 C7′, `docs/review/phase-07c-1b/11-decider-decision-r3.md`
   item 8):
   - **C9** a process-wide single-flight insertion cache keyed by canonical scene + `tailSeed`, fs, P, `engineKey()`,
     platform; any scene (NFR-8); `shared_ptr<const>`; test `insertSolves + insertCacheHits == 1` and bit-identity;
     TSan with 8 concurrent insertions;
   - **C1** the constructor-spectra cache (bit-identical): a transient shared spectra cache keyed by filterbank + FFT
     size, freed when unused; its AX38 (i) / (ii) accounting decided in this phase's loop; W1/W2 "no cache credit";
   - **C6** a process-wide count of synchronous host calls: background syntheses and builders sleep at cancel points;
     the gate holder never pauses; `quiesce()` wakes; offline not paused; bit-identity on resume tested; record (h)
     prints provisional → exact per instance (phase-07c-1b decider file 4 item 8);
   - **C2** parallel band-pair synthesis (bit-identical), only on the gate's pool with C6;
   - **C4** D4 in unit-decay form (Seat 4 rated it as A3, 1; Seat 5's cell at ≈ 147 MB is unrated, interrogator file 13
     row P07C1-63), only as shared per-(emitter, outputIndex) unit decays, memory measured;
   - **C3** a capped interim length on the K23 shared-history fact (both crossfade states read one input history, so
     the output equals the exact render for lags up to L_f, within the normalisation step (K18′) [Inf]), only as C3-pb
     (L_p,b ≥ t_mix,e,max + 0.312·T60_b + 0.1 s); convene Seats 1, 3, 5, 6, 7 and 9; Seat 9's L_p ≥ 0.31·T60 condition
     and Seat 1's depth ruling are re-rated;
   - **C5** the cheaper generator (output-changing; a golden round; AQ10's "not optimised before Phase 13" read by the
     board), only with Seat 1's ABX, Seat 2's equivalence test and Seat 9's BRAS condition, before Phase 12.
3. **Inputs:** phase-07c-1 record (h)'s T60_max sweep (2, 8, 12, 20, 35 and 50 s; per-instance time until audible
   and time from provisional to exact; 1, 4 and 8 instances; 48 and 96 kHz; three OSes) and the Seat 5 / Seat 7
   ratings of the long corner (3.82 s < L_p, up to the full synthesis), which the 07c-1 loop left unrated (K24).
4. **Release premise:** BUILD_PLAN premise P1 (AX38 (iv)): if 07d lands after the first release, the interim-audible
   time stays the non-diffuse restore and phase-13 item 3 fires on it.
5. **Register:** the AX38 4c register's macOS entry names 07d as 'closes at', and the Windows entry's remedy names
   07d (or Phase 13's release-machine re-check if the runner is shown to be the cause, as written there). Both
   entries closed in phase-07c-1b (E1; scope 1).
6. **8-instance load (AX49 reversal, moved here by D-B4 C7′; phase-07c-1b loop, 2026-11-13).** The 8-instance Windows
   load at the rated corner is brought to ≤ 5 s on record (h) (criterion below), the candidates of scope 2 in order,
   C9 first. Also: insertion unit decays for every outputIndex (Seat 4 (i)) — output-1 built by the builder after the
   first IrSet unless the current mode needs two outputs; whether a mode switch inside the settling window plays an
   interim, decided with Seats 3 and 4 and asserted in 08-3; any remedy scales with the number of outputs; 07d lands
   before 08-4 freezes its goldens. Never an instance cap (PRD FR-3D-5, FR-3D-6, FR-SIM-7, A5).
7. **The macOS (d) defect (D-B5 (vi) X-d−, AX38 4c):** MACTRIGGER on runs 42 and 44, remedy here. Closure evidence:
   the macOS per-stage split after the remedy at equal work pins; the macOS / Linux per-emitter synthesis ratio within
   1.10 × the same runs' flutter macOS / Linux ratio; the trigger in force not exceeded on two consecutive runs; built
   from runs 07d makes, ≤ 3 extra manual runs per defect (Seat 7); no closure by recalibration.
   Re-derived at 07c-1b (AX38 4c X-d−, 2026-11-13): runs 42 (2 223 ms) and 44 (2 572 ms) exceed the S2 trigger
   1 703 ms, so the defect stands.
8. **The growth re-pin (D-B5 (ii), FM-GROWTH, AX38 4c):** after the remedy, the ratio reference and baselines
   re-derived from ≥ 6 green runs on the restore path in force (manual runs after 07d's last code change; earlier runs
   pooled only if 07d leaves the restore path unchanged), and the in-window absolute leg added under AX38 4c
   "Asserted every run" (w the largest value with (1 + w)·max(r/r̄) ≤ 1.083 over those runs; not added if max(r/r̄)
   ≥ 1.07; dormancy stated if no in-window x64 run); the solve bound's PROVISIONAL exit, second branch (re-derived
   here if its first branch was not met). A synthesis growth 07d itself introduces is read by scope 7's closure
   evidence, not by the re-pinned absolute leg.

## Out of scope

- Everything decided in phase-07c-1's loop outside the long-T60 corner (AX47–AX49 as written); the class (c) and
  load-fallback decisions and the AX47 / L4 ABX runs ([phase-07c-2](phase-07c-2.md)).
- AX49's "Recorded for Phase 10" alternatives (D5 within 5 %, D6): [phase-10-2](phase-10-2.md).

## Acceptance criteria — automated

- [ ] The chosen candidate(s) recorded as an AX row through the board loop (ledger rows linked) before the first
      code commit.
- [ ] The AX38 4c restore gate runs at both gated builds on three OSes in its register form; the macOS and Windows
      entries leave the register through `/fix-plan` under (c), or stay listed with their remedy and closing
      phase restated. (Both closed in phase-07c-1b, E1, 2026-11-13; scope 1.)
- [ ] Any bit-identical candidate is tested bit-identical to the current build on each platform (AX5); an
      output-changing candidate goes through one golden round (`update_goldens.py`, §6 row).
- [ ] 8-instance Windows load at the rated corner ≤ 5 s on record (h), read on the larger of the prepare-first
      (interleaved, batched) and setState-first totals (FM-10S), with runner label and vCPU printed (R1). AX38 (iv)'s
      10 s line read on the same total (run 42 macOS keyed 10 206 ms; prepare-first ≈ 11.4–13.6 s est.); an
      exceedance after 07d goes to the decider for Maisara before the first release. (D-B4 C7′, FM-10S; scope 6)
- [ ] The macOS (d) defect (runs 42, 44) closed on scope 7's closure evidence through `/fix-plan`, or left open with
      its evidence stated; no closure by recalibration. (AX38 4c X-d−)
- [ ] The growth re-pin (scope 8): reference and baselines from ≥ 6 green runs with a CHANGELOG reason and a §6 row;
      the in-window absolute leg asserted on Linux and Windows (an OS whose ratios over the current pin's runs have
      max/min > 1.10 is print-only), or not added (max(r/r̄) ≥ 1.07) with the GROWTH print
      kept; in-window runs per OS counted and dormancy stated. (AX38 4c, FM-GROWTH)

## Listening / manual checklist

- [ ] Set by this phase's decision loop for the chosen candidate.

## Contractor review focus

- The restore path at the long-T60 corner and the chosen candidate's threading and determinism.

## Risks

A capped interim or a cheaper generator changes what is heard during or after load; both return to the seats named
above before any code.

## Definition of done

- Section "Acceptance criteria — automated" all checked with CI evidence.
- PR with the listening checklist, contractor focus and AX/ledger links.
- CLAUDE.md rules apply: one phase per session; if it can't be finished in two sessions, split the remainder into
  `phase-07d-b.md`.
