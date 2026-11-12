# Phase 07d — Restore gate at the long-T60 corner (condition 9's split)

Size: **S–M** (remainder, if needed: `07d-b`) · Depends on: 07c-1 `done` · Created 2026-11-12 under phase-07c-1
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
2. **Candidates** (decided through the board loop and recorded as an AX row before any code; decider file 12 §8):
   - the constructor-spectra cache (bit-identical);
   - parallel band-pair synthesis (bit-identical);
   - a capped interim length on the K23 shared-history fact (both crossfade states read one input history, so
     the output equals the exact render for lags up to L_f, within the normalisation step (K18′) [Inf]); convene Seats 1, 3, 5, 6, 7 and 9; Seat 9's
     L_p ≥ 0.31·T60 condition and Seat 1's depth ruling are re-rated;
   - D4 in unit-decay form (Seat 4 rated it as A3, 1; Seat 5's cell at ≈ 147 MB is unrated, interrogator file 13 row
     P07C1-63);
   - the cheaper generator (output-changing; a golden round; AQ10's "not optimised before Phase 13" read by the
     board).
3. **Inputs:** phase-07c-1 record (h)'s T60_max sweep (2, 8, 12, 20, 35 and 50 s; per-instance time until audible
   and time from provisional to exact; 1, 4 and 8 instances; 48 and 96 kHz; three OSes) and the Seat 5 / Seat 7
   ratings of the long corner (3.82 s < L_p, up to the full synthesis), which the 07c-1 loop left unrated (K24).
4. **Release premise:** BUILD_PLAN premise P1 (AX38 (iv)): if 07d lands after the first release, the interim-audible
   time stays the non-diffuse restore and phase-13 item 3 fires on it.
5. **Register:** the AX38 4c register's macOS entry names 07d as 'closes at', and the Windows entry's remedy names
   07d (or Phase 13's release-machine re-check if the runner is shown to be the cause, as written there).

## Out of scope

- Everything decided in phase-07c-1's loop outside the long-T60 corner (AX47–AX49 as written); the class (c) and
  load-fallback decisions and the AX47 / L4 ABX runs ([phase-07c-2](phase-07c-2.md)).
- AX49's "Recorded for Phase 10" alternatives (D5 within 5 %, D6): [phase-10-2](phase-10-2.md).

## Acceptance criteria — automated

- [ ] The chosen candidate(s) recorded as an AX row through the board loop (ledger rows linked) before the first
      code commit.
- [ ] The AX38 4c restore gate runs at both gated builds on three OSes in its register form; the macOS and Windows
      entries leave the register through `/fix-plan` under (c), or stay listed with their remedy and closing
      phase restated.
- [ ] Any bit-identical candidate is tested bit-identical to the current build on each platform (AX5); an
      output-changing candidate goes through one golden round (`update_goldens.py`, §6 row).

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
