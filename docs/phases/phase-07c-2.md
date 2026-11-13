# Phase 07c-2 — W_max re-derived under (C), one golden round

Size: **S** (remainder, if needed: `07c-2b`) · Depends on: 07c-1 and [07c-1b](phase-07c-1b.md) `done` (and, through
them, 05h, 07 `done`; 07c-1b because condition 3's re-pin starts from its condition 7 re-pin) · Part of:
[phase-07c](phase-07c.md) · Lead subject matter: Seat 2 (Engine architect), "simulator compute and recompute
time" · Read first, in this order: `CLAUDE.md`; this file in full [and the umbrella, `docs/phases/phase-07c.md`, and
`docs/phases/phase-07c-1.md`]; `docs/BUILD_PLAN.md` §2 **AQ4, AQ10 (amended 2026-11-10 and 2026-11-12), AX5, AX18, AX33, AX38,
AX41, AX44, AX47, AX48, AX49**; `docs/phases/phase-05h.md` (§3 D-H1, §4 scope 2, the solve seam); `docs/phases/phase-07.md` (state
restore, reset sequence, offline path); `docs/review/phase-05b2/47-decider-board-answers-C1-Q2a-final.md` §4 and
`51-decider-addendum-J1.md`; `49-interrogator-board-answers-C1-Q2.md`; ledger P05B2-C1Q2-01…14; PRD NFR-2, NFR-3,
NFR-6, FR-SIM-6.

The umbrella is a beta prerequisite: **Must be `done` before Phase 13's beta** (or phase-13 scope 13's versioning
fallback recorded) applies to this sub-phase as part of phase 07c (umbrella header).

---

## Raise with Maisara (first message and PR)

(phase-07c §2.1)
1. **Only if** this phase would land after the first public release without the estimator parameters
   versioned in saved state: Seat 7's condition fails and the item returns to Maisara (decider file 47 §4,
   strongest objection; phase-13 "Raise with Maisara" item 4). Otherwise none.

## Goal

This is Seat 1's "now" 2, repaid when this phase lands with W_max re-derived from the background budget.
(phase-07c §0; the move off the synchronous paths is 07c-1's.)

## Assumptions in force

All of the umbrella's: §1 "Settled — do not reopen" (AX37–AX46 and the AQ10 amendment; the board's J1 answer; D-H1
as decided in phase 05h) and §3 Timing. D-C1–D-C3 as recorded by 07c-1 (AX rows).

## Scope

- **Timing** (phase-07c §3, first bullet; shared with the umbrella): Lands **before the first public release (the
  Phase 13 beta)**, with its W_max raise in one golden round. If it lands after release, the estimator parameters
  are versioned in saved state (Seats 5, 7; condition 1). (phase-07c §3 T1)

1. **Timing** (section 3): before the first public release, with its W_max raise in one golden round;
   after release only with the estimator parameters versioned in saved state. (phase-07c condition 1; shared
   with the umbrella)
3. **W_max re-derived under (C)** from the background budget: Seat 6's 3 s per emitter, the AX38 (iv)
   load mark, and Table 15.1's 700 ms / 3 s rows (Seats 1 (i), 3 (5), 5). It is not kept at (A). It stays a
   pinned work count, the same on every platform (AX41), re-derived from the C++ cost, never a time cap;
   AX41 and the AQ10 amendment are updated through `/fix-plan`. The W_max raise changes the work: the solve
   bound's baselines (`solveRefMs`) are re-pinned with the new work and k (G7) re-derived (D-Q5).
   Whether the per-evaluation solve time (`nsPerEval` on the GATE line) stays invariant across 07c's moves is
   checked here; if it moves, Seats 2 and 3 are convened (the re-pin above is unconditional) (D-Q5
   future-debt register, decider file `docs/review/phase-05i/9-decider-r2.md`). (phase-07c condition 3)
8. **Follow-on checks.** The Phase 12 (ii) preset check (no preset default raises U) is re-run under this
   phase's W_max (Seat 6 (e)). Phase 08 goldens in capped rooms carry a tolerance derived from the
   achieved SE, unless this phase lands before they are frozen (Seat 4). (phase-07c condition 8)
9. **Interim-step items from 07c-1's loop** (phase-07c-1 decision loop, 2026-11-12; decider file
   `docs/review/phase-07c-1/12-decider-decision-r3.md` §8, interrogator file 13 correction 7):
   - **The ABX runs first:** the AX47 self-ABX (16 trials, capped layout-4 scene, noise and speech) and the
     AX49 listening item L4 (blind held-chord ABX, provisional against exact tail, T60 8 s, fully wet,
     16 trials, ≥ 12/16 = detected) are run in this phase. This phase's loop sets the AX47 ABX's detection
     criterion and step sizes before the run (AX47 reversal; a per-size 12/16 rule over several sizes raises
     the family-wise false-detection rate, interrogator file 16 row P07C1-DC-06). AX47's reversal (bound 0.5 dB) and AX49's reversal
     (L4 detects the cut) follow from their results. The generated speech-like stimulus of `[ax47-midfade]` is a CI
     test signal only; 07c-2's self-ABX and the acceptance set use recorded speech (D-B3 condition A; phase-07c-1b
     loop, 2026-11-13).
   - **Class (c) decision, bound by AX47:** whether a statistical source (a stage-1 estimate that is not the
     final) is admitted, decided by this phase's loop under AX47 ("From 07c-2"; Seat 1's p95 reading is the
     recorded input). **Admission waits for the AX47 ABX result** (the bound it is held to, 1 dB or 0.5 dB,
     is the ABX's outcome).
   - **The load fallback:** the load source when stage 1 is inadmissible, decided in the same loop; it meets
     AX47 and conditions 5 and 9 and never gives an early-only first IrSet for a scene with a tail.
   - **Interim stream check (D1, FM-D1-S3; Maisara 2026-11-13).** If this phase's loop admits a class (c) source or a
     load fallback whose interim tail is built from the exact tail's `BandNoiseGenerator`, seed and emitter stream
     (`tailSeedForOutput`), a test compares the interim IR with the final IR, both as shipped, from two serial builds of
     one scene and seed in one process (never from the async pipeline; never against a measured IR; a repeat build of
     each IR is asserted bit-identical before any comparison), per emitter, output and band on the A4 set (48 and
     96 kHz, 2 seeds, more only with a reason in the PR): 10·log10(E(interim − final)/E(final)) ≤ 20·log10(10^(B/20) − 1)
     dB, B the AX47 bound in force after the ABX (1 dB → −18.27 dB; 0.5 dB → −24.55 dB). Window: an interim that fades
     at the AX49 L_f uses AX47 (b)'s [t_mix,e, L_f − h), h AX47 (b)'s plus the backward reach of any per-mode filter in
     force; a full-length interim (the final's length L and per-band decay, differing only in per-band level) uses
     AX47's tail window [t_mix,e, L), since the two IRs share their end: h is subtracted only at an L_f edge, never at
     L. The window length is printed per case and band; the window's specular energy share of E(final) is printed per
     case and band (Seat 3, print only); an empty window prints 'not evaluated', and a case with zero matched tail
     energy (e.g. an AX22 ISM-only fallback whose matching window holds zero energy; AX49 D1 early-only scenes) prints
     'not evaluated (no tail)'; neither ever counts as a pass; ≥ 1 evaluated case per band, output and fs
     (non-vacuity, not a quota). Negative control N1, asserted red per emitter, output and band: the interim built with
     tailSeed + 1 (neither of its `tailSeedForOutput` seeds equal to either of tailSeed's, asserted as a guard on the
     seed derivation); expected 10·log10(1 + g²), +2.54 to +3.54 dB for an interim step g within ±1 dB (≈ +3.01 dB at
     g = 1; incoherent energies add, Vorländer §4.3 Eq. 4.15). The final IRs are those the AX47 tests already build;
     the test runs in the Release test job; the PR prints the added wall time per OS.
     **No shared prefix.** An admitted source whose interim does not share the exact tail's stream, length or per-band
     decay is outside this check, and instead: (1) a test asserts the fact that excludes it (its `tailSeedForOutput`
     seeds, its length or its per-band decay differ from the final's); (2) where its stream differs, it fails AX18's
     Same-scene steps condition (the same emitter streams), so it lies outside AX47 Scope's "Same-scene steps are
     equal-gain (AX18)", and its handover to the final is equal-power, recorded by AX47's measurement sentence, unless
     this phase's loop (Seats 3 and 5, AX18) sets another law together with an asserted bound on the mid-fade band
     level; (3) where its per-band decay differs, EDT within 5 % at 500 Hz and 1 kHz against the final on AX47 (b)'s
     terms (cases with d < 0.5; 'not evaluated (outside EDT domain …)' otherwise; ≥ 1 evaluated case at each); (4)
     AX47's level step ≤ B per emitter and band, asserted in the tail window and, for an interim that fades at L_f, in
     the common window t_mix,e…L_f. The PR names the source and gives these results.
   - **Instance insertion (FM-B2, AX48):** Instance insertion (FM-B2) takes 07c-2's stage-1 rules for statistical
     sources. (phase-07c-1b loop, 2026-11-13)
   - **The W_max raise changes E_prec** (AX48), so v2 states saved before the raise load keyless.
   - **Seat 2's prefix check:** verify Seat 2's prefix claim (`pathCount`, `pilotStops`).
10. **Carried from 07c-1b (P07C1B-R1), only if `listed` is still `false` on the macOS `cube100_lowalpha0.05_s0.3` row
    of `kGateRegister` on `main` when this phase starts:** in this phase's first code commit, in one commit: that
    row's `listed` `false` → `true` in `tests/unit/test_diffuse_records.cpp` with its comment line, the
    `tests/golden/CHANGELOG.md` line, and texts T1, T4 and T8 (through `/fix-plan`), exactly as written in
    `docs/review/phase-07c-1b/32-decider-R1-round3.md`; nothing else in the row changes (`recorded14xS` stays 33.40).
    The same item stands in phase-07d scope 9; whichever phase starts first does it, and the other records it as done
    with the commit.

## Out of scope

- The umbrella's §9 (phase-07c §9): Changing the estimator (AX39–AX44); a both-near fallback (§5 B15); a kernel cache
  (AX38 (ii), phase-10 AX only); n\*_max (Q2b (i) stays at the pinned 1 024 and is not re-derived here unless the W1
  measurement per output mode moves it, AX41; D-H1 (iv)). Moving the unit-decay synthesis **is** in scope (condition
  9); caching its constructor spectra per (fs, length) is not the AX38 (ii) kernel cache but an alternative recorded,
  not chosen. **W_max re-derivation (condition 3) has a prerequisite:** the (C) W_max is pinned only after the AX38 4c
  record "offline-bounce time of a 3-minute room-size automation at 100 m, with its ratio to real time" is in this
  phase's packet (Seat 8; D-H1 (iv), AX41).
- Conditions 2, 4–7 and 9–11 and the decisions D-C1–D-C3: [phase-07c-1](phase-07c-1.md) (condition 7's re-pin:
  [phase-07c-1b](phase-07c-1b.md)).

## Acceptance criteria — automated

- [ ] W_max re-derived under (C) from the background budget (condition 3), pinned, equal on the three OSes;
      goldens updated once through `update_goldens.py` with the reason; §6 row. (phase-07c A6)
- [ ] The Phase 12 (ii) preset check re-run under the new W_max and reported, if Phase 12 has run;
      otherwise Phase 12 runs it at 07c's W_max. (phase-07c A9)
- [ ] **Interim stream check (D1, FM-D1-S3):** every admitted interim source that shares the exact tail's stream
      passes scope 9's interim stream check per emitter, output and band (repeat builds bit-identical, N1 red, ≥ 1
      evaluated case per band, output and fs, zero-tail cases 'not evaluated (no tail)'); every admitted source with
      no shared prefix has scope 9's asserted exclusion fact, handover law (equal-power, or the loop's law with its
      asserted mid-fade bound), EDT check where its decay differs, and level step in both windows; or the PR states
      that no such source was admitted. The added wall time per OS is printed.

## Listening / manual checklist

- [ ] Load a project with a large room: the room is heard at once at the interim level, shows "settling",
      and moves to the final level without a click or an obvious jump. (phase-07c L1)
- [ ] The AX47 self-ABX and the AX49 L4 ABX (scope 9), run before the class (c) decision. (AX47, AX49)

## Contractor review focus

- the W_max re-derivation from the background budget (phase-07c F6)

## Risks

The original phase file has no risks section; the umbrella's §0 gives the rationale.

## Definition of done

- Section 6 all checked with CI evidence (phase-07c §10, clause 1; here: this file's automated criteria).
- PR with the listening checklist, contractor focus, AX/ledger links and the "Raise with Maisara" item if it applies
  (phase-07c §10, clause 3; this sub-phase's share).
- CLAUDE.md rules apply: one sub-phase per session; if it can't be finished in two sessions, split the remainder into
  `phase-07c-2b.md`.

## Notes from the split

- Convening-round correction (`docs/review/phase-split/1-decider-convening.md`, Map 07c; confirmed in
  `3-decider-decision.md` and `5-decider-decision-r2.md` corrections item 1): "§2.1 Raise goes into both sub-phase
  files (the phase's first message is 07c-1's)." Each raises it in its first message.
- 07c-c1 (convening round, NOT A DECISION): "(a). The umbrella is the beta prerequisite (G3 default; matches §3 T1)."
- 07c-c2 (convening round, NOT A DECISION): "(a). The umbrella is brought forward (phase-08 scope 10: "W_max is then
  re-derived once, under phase-07c, with one golden round")."
