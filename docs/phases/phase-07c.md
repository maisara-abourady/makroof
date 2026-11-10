# Phase 07c — Asynchronous diffuse solve (Q2a (C))

Size: **split into 07c-1…07c-2** (originally M, about one phase of Phase 07 rework, decider file 47; each
sub-phase's two-session remainder is `07c-<n>b`, CLAUDE.md) · Depends on: 05h, 07 `done` · **Must be `done` before Phase 13's
beta** (or phase-13 scope 13's versioning fallback recorded) · Read first, in this order: `CLAUDE.md`; this file in full; `docs/BUILD_PLAN.md` §2 **AQ4, AQ10
(amended 2026-11-10), AX5, AX18, AX33, AX38, AX41, AX44**; `docs/phases/phase-05h.md` (§3 D-H1, §4
scope 2, the solve seam); `docs/phases/phase-07.md` (state restore, reset sequence, offline path);
`docs/review/phase-05b2/47-decider-board-answers-C1-Q2a-final.md` §4 and
`51-decider-addendum-J1.md`; `49-interrogator-board-answers-C1-Q2.md`; ledger P05B2-C1Q2-01…14; PRD
NFR-2, NFR-3, NFR-6, FR-SIM-6.

Created on 2026-11-10 from the board's answer to Challenge 1 and Q2a (J1: Challenge 1 = yes, Q2a = (A)
now, (C) scheduled now as its own phase; decider files 47 §4 (iii) and 51 §4 item 4; interrogator file 49
SURVIVES WITH CORRECTIONS, applied).

---

## 0. Why this phase exists

Under Q2a (A) the diffuse estimator's work limit W_max is sized to pluginval's restore watchdog (30 s / 14
restores minus the worst OS build, less D-H1's margin; AX41), because the diffuse solve runs inside the
synchronous state restore, prepare and `reset()`. That keeps random level error in the capped class until
this phase: SE 0.13–1.33 dB in Kuttruff Table 5.2 layouts 4/5 at s = 1 and 0.44–0.50 dB in the low-α
s = 1 100 m cube (C16 (f), at n\*_max 1 024); rooms near 100 m are capped at SE ≤ 0.15 dB in the s = 0.3
and absorbing-floor cubes (decider file 51 §2, L3/L5). This is Seat 1's "now" 2, repaid when this phase
lands with W_max re-derived from the background budget. This phase moves the diffuse solve off the
synchronous paths so W_max no longer has to fit the restore watchdog.

## 1. Settled — do not reopen

- AX37–AX46 and the AQ10 amendment (phase-05h §1).
- The board's J1 answer: the blocking 100 m, 96 kHz restore gate (AX38 4c, with its conditions); W_max
  (A) now; this phase scheduled before the first public release; Q2b (i), n\*_max 1 024 (decider files 43,
  47, 51).
- D-H1 as decided in phase 05h (the margin rule; AX41).

## 2. Raise with Maisara (first message and PR)

1. **Only if** this phase would land after the first public release without the estimator parameters
   versioned in saved state: Seat 7's condition fails and the item returns to Maisara (decider file 47 §4,
   strongest objection; phase-13 "Raise with Maisara" item 4). Otherwise none.

## 3. Timing

- Lands **before the first public release (the Phase 13 beta)**, with its W_max raise in one golden round.
  If it lands after release, the estimator parameters are versioned in saved state (Seats 5, 7;
  condition 1).
- **Brought ahead of Phase 08's golden freeze** if Phase 08's heaviest-mode build makes the pinned W_max
  fail the restore gate (AX38 4c; phase-08 scope 10). That gate exists only once 05h is `done`, so this
  phase comes forward only after 05h (its dependency); if Phase 08 went first, the heaviest-mode gate is
  run in phase-05h scope 10.
- **Brought forward on any restore-gate failure** (AX38 4c: a gate failure is a defect, remedied only by
  moving work off the restore path).

## 4. Decisions before implementation (decision loop, `/fix-plan` step 3)

Moved verbatim to [phase-07c-1](phase-07c-1.md) (D-C1–D-C3, R1–R3; see "Where the original items went").

## 5. Scope — conditions 1–8 (decider file 47 §4 (iii))

The diffuse solve moves off the synchronous restore, prepare and `reset()`.
1. **Timing** (section 3): before the first public release, with its W_max raise in one golden round;
   after release only with the estimator parameters versioned in saved state.

Conditions 2, 4, 5, 6 and 7 are in [phase-07c-1](phase-07c-1.md); conditions 3 and 8 in
[phase-07c-2](phase-07c-2.md); condition 1 is shared with phase-07c-2 (verbatim in both).

## 6. Acceptance criteria — automated

Moved verbatim: A1–A5, A7, A8 to [phase-07c-1](phase-07c-1.md); A6, A9 to [phase-07c-2](phase-07c-2.md).

## 7. Listening checklist (Maisara)

Moved verbatim: L1 to [phase-07c-2](phase-07c-2.md); L2, L3 to [phase-07c-1](phase-07c-1.md).

## 8. Contractor review focus

Moved verbatim: F1–F5 to [phase-07c-1](phase-07c-1.md); F6 to [phase-07c-2](phase-07c-2.md).

## 9. Out of scope

Changing the estimator (AX39–AX44); a both-near fallback (§5 B15); a kernel cache (AX38 (ii), phase-10 AX
only); n\*_max (Q2b (i) stays unless the C++ W1 measurement moves it, AX41).

## 10. Definition of done

Section 6 all checked with CI evidence; §0 row 07c `done` before Phase 13's beta; PR with the listening
checklist, contractor focus, AX/ledger links and the "Raise with Maisara" item if it applies.

---

## Sub-phases

| id | title | lead seat | size | depends on | ships | owns (automated) |
|---|---|---|---|---|---|---|
| [07c-1](phase-07c-1.md) | Diffuse solve off the synchronous paths | Seat 5 (Deadline keeper) | M | 05h, 07 `done` | restore, prepare and `reset()` no longer run the diffuse solve; the real-time path adopts each solved snapshot by atomic swap with an AQ4 crossfade, starting from the interim level; offline waits and stays bit-identical; the restore gate re-scoped; W_max still at (A) | A1, A2, A3, A4, A5, A7, A8 |
| [07c-2](phase-07c-2.md) | W_max re-derived under (C), one golden round | Seat 2 (Engine architect) | S | 07c-1 `done` (and, through it, 05h, 07) | W_max raised from the (A) restore budget to the (C) background budget, pinned and equal on the three OSes; goldens updated once; Seat 1's "now" 2 (capped-class SE, §0) repaid; Phase 12 (ii) re-run | A6, A9 |

Order 07c-1 → 07c-2 (forced: under (A), W_max is sized to the restore watchdog, so it cannot be raised until the solve
is off the restore path; convening round, Map 07c).

## Where the original items went

Labels: A1–A9 are the §6 criteria in file order; L1–L3 the §7 items; F1–F6 the §8 focus items split at its
semicolons; T1–T3 the §3 bullets; R1–R3 the §4 researcher questions.

| original item | goes to |
|---|---|
| Header: size line | umbrella (per sub-phase: `07c-1b` / `07c-2b`) |
| Header: depends on 05h, 07 `done` | umbrella and 07c-1 (07c-2 depends on 07c-1) |
| Header: must be `done` before Phase 13's beta (or phase-13 scope 13's versioning fallback) | umbrella (both sub-phases) |
| Header: read-first list | umbrella, cited in both sub-phase headers |
| Header: creation note | umbrella |
| §0 Why this phase exists | umbrella (last sentence also 07c-1's goal; "now" 2 sentence also 07c-2's goal) |
| §1 Settled — do not reopen | umbrella (governs both) |
| §2.1 Raise with Maisara | umbrella, 07c-1 and 07c-2 (each raises it in its first message) |
| §3 T1 | umbrella and 07c-2 |
| §3 T2, T3 | umbrella (the umbrella is brought forward) |
| §4 D-C1, D-C2, D-C3; R1, R2, R3; the ordering note | 07c-1 |
| §5 lead sentence | umbrella (cited in 07c-1) |
| condition 1 | umbrella and 07c-2 |
| conditions 2, 4, 5, 6, 7 | 07c-1 |
| conditions 3, 8 | 07c-2 |
| A1, A2, A3, A4, A5, A7, A8 | 07c-1 (A4's test keeps running in CI through 07c-2) |
| A6, A9 | 07c-2 |
| L1 | 07c-2 |
| L2, L3 | 07c-1 |
| F1, F2, F3, F4, F5 | 07c-1 |
| F6 | 07c-2 |
| §9 Out of scope | umbrella (cited in both) |
| §10 clause 1 (§6 all checked with CI evidence) | umbrella, and each sub-phase for its own criteria |
| §10 clause 2 (§0 row 07c `done` before Phase 13's beta) | umbrella |
| §10 clause 3 (PR with listening checklist, contractor focus, AX/ledger links, Raise item) | umbrella, and each sub-phase PR for its share |

## Notes from the split

- 07c-c1 (convening round, `docs/review/phase-split/1-decider-convening.md`, NOT A DECISION): "(a). The umbrella is
  the beta prerequisite (G3 default; matches §3 T1)."
- 07c-c2 (convening round, NOT A DECISION): "(a). The umbrella is brought forward (phase-08 scope 10: "W_max is then
  re-derived once, under phase-07c, with one golden round")."
- 07c-c3 (convening round, NOT A DECISION): "(a). D-C1–D-C3 and R1–R3 in 07c-1; A1 as written."
- Correction (convening round; `5-decider-decision-r2.md` corrections item 1): "§2.1 Raise goes into both sub-phase
  files (the phase's first message is 07c-1's)."

Status: the umbrella is `done` when every sub-phase is. A dependency on phase 07c means all of its sub-phases unless a
sub-phase is named.
