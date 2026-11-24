# Phase 07c-2b — W_max re-derived under (C), one golden round: remainder of 07c-2

Size: **S–M** · Depends on: [07c-2](phase-07c-2.md) `done` (and, through it, 07c-1, 07c-1b, 05h, 07 `done`) · Part of:
[phase-07c](phase-07c.md) · Lead subject matter: Seat 2 (Engine architect), "simulator compute and recompute time" ·
Read first, in this order: `CLAUDE.md`; this file in full; `docs/phases/phase-07c-2.md` (scopes 1–11, its acceptance
criteria and listening checklist, which this file carries in part); the session brief
`docs/sessions/2026-11-22-phase-07c-2.md` (objectives O1–O16 and every "Scope list restated" section, including the
G17 answer); `docs/validation/abx-07c-2-run-sheet.md`; decider files `docs/review/phase-07c-2/13-decider-rebuttal-r4.md`
("D-W2: final", items 1–16, and its Q5 section), `31-decider-abx-r4.md`, `34-decider-m1-m2-final.md`; builder files
`19-h2c-implementation.md` and `32-k5-k6-clicks-session.md`; `docs/BUILD_PLAN.md` §2 **AQ4, AQ10 (amended 2026-11-10 and
2026-11-12), AX5, AX18, AX33, AX38, AX41, AX44, AX47, AX48, AX49**.

Created on 2026-11-22 under CLAUDE.md's split rule ("If a phase can't be finished in two sessions, split the remainder
into `phase-XXb.md`"): phase 07c-2's session landed the scope 10 carrier commit, scope 11 (H-2c) code and local
evidence, the D-W2 ABX kit (render_cli step flag, noise and speech scripts, run sheet, THIRD_PARTY row), M1 and M2
(decider files 31, 33, 34), K5 and K6 (builder file 32) and D-W4's home in phase-10-3. The items below did not fit:
they wait on the ABX scene question (M3), the ABX itself (a person's action) and the W pin behind it. Nothing here
reopens a decision: every rule is phase-07c-2's, applied to the work that remains.

**Dependencies (CLAUDE.md rule 3).** 07c-2 `done` in BUILD_PLAN §0, with its PR, its CI run of record (three OSes) and
the board files `docs/review/phase-07c-2/` 1–36 cited there. The items arrive by three hand-offs in the 07c-2 session
brief: O12 by the scope list restated after steward round 4 (G19); M3 and the seal by the scope list restated after
decider round 4 (file 31); the split ending by the G17 answer, under which 07c-2's PR marks the ABX (O9) and the items
behind it (O10, O11, O4–O7, O12) as moved here.

The umbrella is a beta prerequisite: **Must be `done` before Phase 13's beta** (or phase-13 scope 13's versioning
fallback recorded) applies to this sub-phase as part of phase 07c (umbrella header).

---

## Raise with Maisara (first message and PR)

1. (phase-07c §2.1, carried verbatim from phase-07c-2) **Only if** this phase would land after the first public
   release without the estimator parameters versioned in saved state: Seat 7's condition fails and the item returns
   to Maisara (decider file 47 §4, strongest objection; phase-13 "Raise with Maisara" item 4). Otherwise none.
2. The ABX listening (two test rooms, noise and speech, plus the L4 held-chord test) needs you or a named listener:
   about 3.3 h if nothing is detected at 0.9 dB, up to about 5.8 h if something is, in sittings of at most 2 h split
   only at a chain boundary; the dates go in the session brief before the seal. The 08-3 binaural rerun adds about
   2.6 h, up to about 5.0 h.

## Goal

Finish phase 07c-2: settle the ABX scene (M3), have the AX47 self-ABX and the AX49 L4 ABX run by a person, decide
class (c) and the load fallback on the result, then pin W_max under (C) from the background budget, re-pin the solve
bound and run the one golden round.

## Assumptions in force

All of phase-07c-2's (the umbrella's §1 "Settled — do not reopen" and §3 Timing; D-C1–D-C3 as recorded by 07c-1; AQ4,
AQ10 as amended, AX5, AX18, AX33, AX38, AX41, AX44, AX47, AX48, AX49), and the D-W2 design as pre-registered in decider
file 13 with M1 and M2 as decided in files 31, 33 and 34. W_max stays a pinned work count in image evaluations, the
same on every platform (AX41), never a time cap. Never a W_max cut below 3.05 M, a range change, a formulation seam or
an instance cap (PRD FR-3D-5, FR-3D-6, FR-SIM-7, A5); no scene- or host-specific logic in `src/sim/` (NFR-8).

## Scope

- **Timing** (phase-07c-2 scope 1, O14; phase-07c §3 T1, condition 1; shared with the umbrella): before the first
  public release (the Phase 13 beta), with its W_max raise in one golden round; after release only with the estimator
  parameters versioned in saved state (Seats 5, 7).

The numbered items run in this order.

1. **M7 under H-2c, only if 07c-2's CI did not already show it** (phase-07c-2 scope 11 item 7, routed by its item 8:
   "It lands in this phase, or as the first work of `07c-2b`, before the golden round (Seat 7)"). If 07c-2's PR cites a
   green three-OS CI run that shows M7 meeting the criterion, M7b recorded against `discardedMidDrag` (with the AX38 (iv)
   patterns) and TSan `[pipeline]` stress green, this item
   records that run id here (evidence: 07c-2's PR and its §0 row; builder file 19's "CI pending on run 45020888832" is
   superseded by it) and is done. Otherwise it is this phase's first work:
   - **M7 under H-2c:** the ISM latency of an edit made mid-solve, with the solve occupying the pool, on the three CI
     OSes at m = 1, 4, 5, 6, 8, capped scenes (1 instance; `layout4_s1/listener_corner` and the s = 1 cube; the shipped
     H-2c pool, `hardware_concurrency − 1`, with the solve occupying it; worst over ≥ 3 runs; set-up from decider file 8
     §6): **≤ 700 ms on the worst OS and flat in m** (Seat 3 (a), Seat 5 (iii); AQ4's yardstick, Vorländer Table 15.1
     by extension).
   - Otherwise, the rest of scope 11's criterion that W_max waits on (phase-07c-2 scope 3: "waits on
     scope 11 done (M7, M7b, TSan)"): M7b recorded against H-0's `discardedMidDrag` (including the AX38 (iv) patterns)
     and the TSan `[pipeline]` stress green, on a three-OS CI run.
   - If M7 fails (above 700 ms or not flat in m) or TSan shows a race, D-W3 returns to the board, and Seat 5's W-C2
     condition fails with it (phase-07c-2 scope 11 item 8).
2. **M3, the ABX scene** (decider file 31, "M3: CONVENE"; moved here by file 34 and the 07c-2 brief's restatement
   after decider round 4). A full board round, exactly as file 31 convenes it:
   - **Seats convened:** 1, 2, 3, 4, 5 (narrow), 6 (narrow), 7 and 9; Seat 8 not required (file 31's convening table
     and reasons). Every seat reads files 28 and 29 and file 31, and rates V1–V4 now and later, with its conditions,
     and answers its seat-specific question in file 31's "Briefs".
   - **Options V1–V4** as file 31 states them, with S-B\* (layout4_s0.7 or layout4_s0.9; the seats pick) and S-W (Seat
     1's rule: among the qualifying scenes, the one with the largest tail share). Every scene in them must be: capped at
     m = 6, 7 and 8; clean on item 6 including K5; rerun through Q5; at a peak of −1 dBFS or below (file 31, "New
     options to rate").
   - **The α treatment:** split or unsplit, as file 31's answer 4 sets out the Bonferroni arithmetic (each scene its
     own family at item 3's thresholds, item 4 in each family; the record states a union rate ≤ 0.049 × families;
     item 15(i) declared as a second family). Thresholds, α per family, trial counts and item 4 are unchanged unless
     the round's decision says otherwise.
   - **V3's /fix-plan:** if V3 is chosen, AX47's Reversal "capped layout-4 scene" becomes "capped layout-4 or layout-5
     scene" through `/fix-plan` (file 31), with a §6 row.
   - Seat 9's 0.43 ceiling, rated 1/1 on every option, goes in the decision's debt register (file 31), with its
     premise corrected on the record (Seat 9, file 26 §5; decider file 40, 2a): the 26/60 premise assumed D/R ≤ 0;
     the corrected bound is t ≤ hold + (SNR − 20 − L_drop)/60 · T60_tail, L_drop = 10·log10(1 + 10^(D/R/10)), which
     on layout4_s1/default (L_drop 13.3 dB, from the heard L + R D/R +13.1 dB at 1 kHz, file 22; hold 0.1 s;
     T60_tail 1.30 s; the 46 dB SNR is broadband, Seat 9's [Hyp]) gives 0.375 s, the measured realised Q5 window.
     The pre-registered Q5 rule itself is not amended (decider file 40, 2a; interrogator file 41).
   - The decider decides; the interrogator returns SURVIVES or SURVIVES WITH CORRECTIONS (applied); ledger rows;
     "Decided for Maisara" entry with PRD ids (file 31's provisional PRD reading: NFR-1, NFR-8 L112).
   - **Amendments held for M3** (applied: M3, decider files 9 and 17; run sheet §0) (file 31, "Amendments to file
     13", "Held for M3"), applied to file 13's design and the run sheet once M3 survives: **item 9** (the scene,
     including the item-9 label, with r/r_c 3.47 and diffuse-field
     D/R −10.8 dB, Kuttruff Eq. 5.44, A ≈ 640 m², as file 31 gives them for S-A); **item 13** (wording: "A
     non-detection is recorded for its scene class only; the 1 dB bound elsewhere rests on D-C1, as AX47 states.",
     file 31 answer 5); **item 15** (the 08-3 binaural rerun, per the chosen option's 08-3 part). File 34 item 1's
     "[S-A only, as long as layout4_s1/default is the ABX scene:]" clause is re-examined by M3's scene choice.
     Until then the item-9 label "occupied mid-size hall envelope, not a validated preset", still printed in
     `docs/validation/abx-07c-2-run-sheet.md` (§1 "Scene"), in `tools/ci/abx_kit.py` (scene docstring and the
     manifest `label` string) and by `tools/ci/listening_pack.py` (L452, which prints the kit's label into the
     phase-07c-2 listening-pack artifact's text and manifest), is **superseded pending M3**: Seat 9 rated it 3/3
     (file 26) and "hall" and "occupied" are removed everywhere (file 27). It is replaced by M3's item-9 label in all
     three before any seal; no stimulus is sealed under it, and the 07c-2 listening-pack artifact that still prints
     it is marked superseded in 07c-2's PR listening checklist (decider file 40, 2b; interrogator file 41).
   - **Before any seal: M1's reversal condition and s_w** (decider file 34 item 2): M1 reverses if item 6's identity
     assertions fail on a rendered A/B pair of any scene with E_target specular share > 0 (10·log10(E(stepped −
     unstepped)/E(unstepped)) = 20·log10|10^(g/20) − 1| over the tail window; the per-band step equals g);
     click-detector results do not count. The window's unscaled share s_w ≤ 2.3 % is printed and asserted on the
     chosen scene(s) (file 34 item 1).
   - **Before any seal: `click_check` made robust** (builder file 32, "Follow-up for the decider"): `click_check`
     compares per-frame flags, with each render judged against B's threshold, or runs on A − B against the crossfade
     model. Either is a kit change under item 6, not an `src/` change. Which one, and whether it is needed, is Seat 3's
     and Seat 5's call; both read the outcome on the chosen scene(s) before the seal.
   - **The M2 debt checks on whatever scene M3 picks** (decider file 34 item 3), at M3's scene choice and at item
     15(i), before each seal: for each sealed scene, the manifest prints the minimum gap, the heard-IR T30 and the tail
     T30, asserts minimum gap ≥ tail T30, and passes Q5's ≥ 20 dB onset assertion (Seat 1 row); the manifest carries
     Seat 9's label, and the Seat 1 row's gap-versus-tail-T30 assertion passes on that scene (Seat 9 row).
3. **Seal, then the ABX run by a person (O9)**, per `docs/validation/abx-07c-2-run-sheet.md` (§3 before the session:
   listener named, speech material fixed, stimuli built, each chain sealed and `prereg_hashes.json` committed before
   the run; §4 procedure; §6 record). The AX49 L4 ABX is run too, with its own stimuli (file 13 item 14 as amended by
   M3-L4; run sheet §7). About 3.3 h of listening if nothing is detected at 0.9 dB, up to about 5.8 h if something is,
   L4 included (builder file 32 K6 pace, [Hyp]; the builder times one speech block and L4 before the dates are fixed),
   in sittings of ≤ 2 h split only at a chain boundary. **This is a person's action:
   the session hands it to Maisara** (file 13 item 16; Raise item 2). Done when (O9): a person's results (trials,
   correct counts) recorded in the session brief and the review folder (`docs/validation/abx-07c-2-results.md`, run
   sheet §6); AX47's and AX49's reversal read from them.
4. **Class (c) and load fallback (O10)** (phase-07c-2 scope 9): admission of a statistical stage-1 source under AX47
   after the ABX result; the load source when stage 1 is inadmissible (meets AX47, conditions 5, 9; never an early-only
   first IrSet for a scene with a tail); FM-B2 takes the stage-1 rules. Done when: board loop, interrogator SURVIVES
   (applied); AX47 / AX48 / AX49 text via `/fix-plan`; §6 row; code if a source is admitted; "Decided for Maisara"
   entry.
5. **Interim stream check (O11)** (phase-07c-2 scope 9, "Interim stream check (D1, FM-D1-S3; Maisara 2026-11-13)" and
   "No shared prefix", as written there): the D1 test for every admitted shared-stream source, or the no-shared-prefix
   checks, or the PR states no such source was admitted; added wall time per OS printed. Done when: the test green in
   CI on three OSes (run id) with N1 red asserted, or the PR sentence.
6. **W_max under (C) (O4)** (phase-07c-2 scope 3): re-derived from the background budget (Seat 6's 3 s per emitter,
   the AX38 (iv) load mark, Table 15.1's 700 ms / 3 s rows), not kept at (A); a pinned work count, equal on three OSes,
   from the C++ cost, never a time cap; the bounce record (prerequisite) cited in the packet. Done when: the D-W1
   re-decision (after O15, the ABX and O10) survives the interrogator and the constant is pinned with this evidence:
   board loop (decider CONVENE → seats → decision; interrogator SURVIVES or SURVIVES WITH CORRECTIONS, applied; ledger
   rows); the bounce record's run ids in the decision packet; `kWMaxPerEmitter…` changed in
   `src/sim/diffuse/DiffuseEstimator.h`; AX41 and the AQ10 amendment via `/fix-plan` with a §6 row, after an
   interrogator corpus check of the new value (CLAUDE.md "Assumptions and decisions"), ledger rows linked; "Decided for
   Maisara" entry; a CI run id green on Linux, macOS and Windows on the final code whose records print the pinned W_max
   (one constant, no per-OS branch). The waiting list is decider file 13's "D-W1: waiting list, corrected", as restated
   in file 15, "Other items"; the AX38 (iv) load mark is read on its own definition, the time until the last instance is audible at load (at the
   interim level since 07c-1), not the time until the final tail settles; it binds W only through the keyless path (K-a
   or `medium_room` insertion, FM-B2), which is the class (c) round's matter (decider file 8 §3). Prerequisite
   (umbrella §9 / AX41): the 3-minute 100 m bounce record, CI runs 43258505284 and 43291051799 (07c-2 brief).
7. **Solve bound re-pin (O5)** (phase-07c-2 scope 3, D-Q5): `solveRefMs` re-pinned with the new work and k (G7)
   re-derived; `nsPerEval` invariance across 07c's moves checked (Seats 2, 3 convened if it moved). Done when: the
   re-pin by `tools/ci/repin_gate.py` from green CI runs on the final code; constants diff; CHANGELOG reason; §6 row;
   the `nsPerEval` comparison (before / after values with run ids).
8. **One golden round (O6)** (phase-07c-2 AC 1): goldens changed by the W_max raise updated once. Done when: one
   `tools/ci/update_goldens.py --reason …` invocation (CHANGELOG entry); §6 row; the D5 golden's per-case n\*/N asserted
   on all three OSes in a green CI run (run id, same run as O4's); realised-work / W_scene guard re-registered as AX41
   requires.
9. **Follow-on checks (O7)** (phase-07c-2 scope 8, AC 2): Phase 12 (ii) preset check; Phase 08 goldens tolerance.
   Done when: Phase 12 has not run (§0 12-1/12-2 `not started`): the phase-12-x line that has Phase 12 run it at 07c's
   W_max, quoted if present or added through `/fix-plan`; Phase 08 goldens not frozen (08-x `not started`): stated in
   the PR description (Follow-ups / criteria checklist) that 07c-2b lands before the freeze, so no SE-derived tolerance
   is needed. (If Phase 12 or the Phase 08 freeze has happened by then, phase-07c-2 scope 8 applies as written: the
   preset check re-run under this phase's W_max; Phase 08 goldens in capped rooms carry a tolerance derived from the
   achieved SE.)
10. **E_prec and Seat 2's prefix check (O12)** (phase-07c-2 scope 9; moved here behind O4 by the 07c-2 brief's
    restatement after steward round 4, G19): v2 states saved before the raise load keyless (asserted); Seat 2's prefix
    claim (`pathCount`, `pilotStops`) verified. Done when: a test asserting keyless load of a pre-raise v2 state fixture
    (it needs a pre-raise v2 fixture and the raised E_prec); and Seat 2's prefix check through the golden round's D5
    byte-identity assertion (Seat 2's condition (d), decider file 4-seat2 L78; F11): the D5 diff touches only
    open_field, asymmetric_materials, medium_room and edge_values, and the other 8 fixtures stay byte-identical
    (asserted).

## Out of scope

- Everything phase-07c-2 delivered: scope 10 (the P07C1B-R1 carrier commit, and phase-07d scope 9's record of it);
  scope 11's H-2c code and tests (except item 1 above, if its CI evidence is not in 07c-2's PR); the D-W2 ABX kit and
  run sheet; M1 and M2 (files 31, 33, 34); K5 and K6 (file 32); D-W4's home in phase-10-3; O14, limited to 07c-2's
  own PR sentence (the timing itself binds this phase: Scope, "Timing").
- Phase-07c-2's own "Out of scope" list (the umbrella's §9; conditions 2, 4–7 and 9–11 and D-C1–D-C3 in 07c-1 /
  07c-1b), and phase-07d (long-T60 load, the macOS (d) defect, growth re-pin). Phase 12's preset check itself.
- The cause ruling on the NFR-8 placement findings (both_corner, both_wall onset, s0.7 spread): home pending Maisara
  (M3-H, `docs/review/phase-07c-2b/24-m3h-for-maisara.md`); this phase's PR lists them under Follow-ups.

## Acceptance criteria — automated

Carried from phase-07c-2 for the items above.

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
- [ ] Only if 07c-2's CI did not already show it (scope 1): **M7 ≤ 700 ms on the worst OS and flat in m** at m = 1, 4,
      5, 6, 8 (three CI OSes, capped scenes); M7b recorded against H-0's `discardedMidDrag`; TSan `[pipeline]` stress
      green. (phase-07c-2, scope 11 criterion)
- [ ] O5: `solveRefMs` re-pinned with the new work and k (G7) re-derived by `tools/ci/repin_gate.py` from green CI
      runs on the final code; CHANGELOG reason; §6 row; the `nsPerEval` comparison printed (before / after, run ids).
- [ ] O12: a test asserts keyless load of a pre-raise v2 state fixture; the golden round's D5 diff touches only
      open_field, asymmetric_materials, medium_room and edge_values, and the other 8 fixtures stay byte-identical
      (asserted).

## Listening / manual checklist

- [ ] Load a project with a large room: the room is heard at once at the interim level, shows "settling",
      and moves to the final level without a click or an obvious jump. (phase-07c L1)
- [ ] The AX47 self-ABX and the AX49 L4 ABX (scope 9), run before the class (c) decision. (AX47, AX49)

## Contractor review focus

- the W_max re-derivation from the background budget (phase-07c F6)

## Risks

A false "detected" sets AX47's bound to 0.5 dB, which raises the admission cost (SE ≤ 0.25 dB); the α treatment changes
how likely that is (decider file 31, Seat 5's convening reason). If no person can hold the ABX session, O9 and every
item behind it (O10, O11, O4–O7, O12) wait, and the phase goes `blocked (awaiting ABX results)`.

## Definition of done

- Section "Acceptance criteria — automated" all checked with CI evidence; the ABX results recorded (scope 3); §0 rows
  07c-2b (and the 07c umbrella) updated.
- PR with the listening checklist, contractor focus, AX/ledger links, the "Raise with Maisara" items and "Decided for
  Maisara".
- CLAUDE.md rules apply: one phase per session; if it can't be finished in two sessions, split the remainder into
  `phase-07c-2c.md`.

## Notes

- Split from 07c-2 on 2026-11-22 (two-session rule; the 07c-2 brief's G17 answer, from the 07c-1 / 07c-1b precedent).
