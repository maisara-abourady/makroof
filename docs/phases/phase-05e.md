# Phase 05e — Comparison with measured IRs, part 2 (remainder of Phase 05)

Size: **M** · Depends on: 05 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ2, AQ9, AX4, AX16, AX21, AX22, AX23, AX24, AX25, AX26, AX27) and §3 (F2, F3), **`docs/phases/phase-05.md` (all of it: its rules apply here unchanged)**, `docs/validation/bras_mapping.md`, `docs/review/ledger.md` section "Phase 05 session — Table 5.2 check and AX24/AX25", PRD NFR-1, NFR-8, Q2, Q9

Created on 2026-11-06 at Maisara's request ("invest in a clean stop for this phase that is testable
and mergeable and prep a clear new phase that can start with a fresh context"). Phase 05 was split:
its delivered part merges as Phase 05; this phase does the remainder. **Every rule, threshold,
method and condition stays in `docs/phases/phase-05.md`**; this file only says which parts are left
and where to start. Where this file and phase-05.md seem to differ, phase-05.md wins and the
difference goes to `/fix-plan`.

## Raise with Maisara (she does not track these herself)

The session raises each item in its **first message** and again in the **PR description**.

1. **BRAS surface areas and room classification.** Read the per-material areas and d_char from
   `_descr/mat_CRx.txt` inside `3_surface_descriptions.zip` (researcher report 16 §4–5). Confirm or
   correct the preliminary classification in Data (CR2 uniform/low-s; CR3 and CR4 one strong, high-s
   absorber). Report to Maisara whether any BRAS room combines uneven α with low s. If none does, say
   that the X-b bias and B11 cannot be tested against BRAS for that case (F2).
2. **DELTA panel report.** If Maisara has not sent the request drafted in
   `docs/review/drafts/delta-report-request.md`, remind her. Phase 05d needs the answer.
3. **Commissioning decision.** Tell Maisara that this decision comes after Phase 05d (see phase-05d,
   "Raise with Maisara"), and summarise for her what this phase's numbers already suggest.

Three plan decisions were open from Phase 05; all three were **decided 2026-11-06** (BUILD_PLAN §6
row of that date; decider proposal at Maisara's request, interrogator verdicts on corpus c1b171f;
vetoable by Maisara). The rule text is in `docs/phases/phase-05.md`; the session applies it and tells
Maisara which decisions it applied, so she can veto.

4. **(D-A) Dimension rule: decided 2026-11-06 (§6 row; vetoable by Maisara).** AX26: keep V and
   h = V / A_floor, plan ratio from the floor surfaces' minimum-area oriented bounding rectangle, S not
   matched (its error and the Eyring change reported), A conserved per face (phase-05.md Data,
   "Dimensions"). Unblocks scope (a), and through it (c), (d), (e), (f) and every acceptance
   criterion that needs scenes or a report.
5. **(D-B) a* against Kuttruff Table 5.2: decided 2026-11-06 (§6 row; vetoable by Maisara).** a*,
   converged to < 0.4 % per halving, is gated within ±1 % in all six Table 5.2 cases against a Lambert-particle Monte
   Carlo; γ²-Eyring and the Table 5.2 column are reported, not gated, and a* may not replace Eyring in B12 while
   ledger DB-1 is unresolved (phase-05.md a* criterion; B12 condition (v)). The strict xfail in
   `tools/acoustics/tests/test_radiosity.py` becomes the new gate. Unblocks the a* criterion below and
   the B12 decision rule's use of a* (scope (e)).
6. **(D-C) Scope 7 paired noise test: decided 2026-11-06 (§6 row; vetoable by Maisara).** AX27:
   Lundeby noise-power subtraction before the Schroeder integral in the validation decay path; gated
   levels L_min = 51 dB, 55, 65 dB (48 dB reported); L_min by the test-level rule on the peak-referred
   `dynamic_range_db`; measured bands enter AQ9/B12 only at a decay-referred noise margin
   (`line_margin_db`) ≥ L_min (option C, decider 2026-11-06 with the interrogator diff check, ledger
   E5-1, E5-6, E5-7; option A, 57 dB on the line margin, rejected; the noisy arm skipping D7(2) is a
   main-session product choice; vetoable by Maisara); the hull stays (phase-05.md scope 7). The xfails in
   `tools/acoustics/tests/test_noise_handling.py` resolve under AX27. Unblocks the paired noise
   criterion below and the measured-IR noise handling of scope (d), (e).

## Goal

Finish Phase 05's goal (phase-05.md "Goal"): the first real-world evidence of accuracy (NFR-1) and
AQ2, with the committed report, the nightly gate on its baseline, and the scope 6 reference
comparisons.

## Assumptions in force

As phase-05.md "Assumptions in force", unchanged, plus AX24 and AX25 (BUILD_PLAN §2, added by
Phase 05), AX26 and AX27 (added 2026-11-06 by decisions D-A and D-C), and the Phase 05 leak
calibration and paired noise results recorded in AX23.

## Start here

What Phase 05 delivered (on `main` once PR #10 is merged; for history:
PR [#10](https://github.com/maisara-abourady/makroof/pull/10), branch `claude/brave-maxwell-5lfm80`;
details in BUILD_PLAN §0 row 05):

- `tools/validation/fetch_bras.py`, `bras_manifest.json` (SHA-256), tamper test
  (`tools/validation/tests/test_fetch_bras.py`).
- `tools/validation/skp_reader.py`: own SketchUp reader; reproduces every documented material area
  of CR2 and CR3. CR4 did not finish within 40 min (re-synchronisation performance).
- `tools/validation/extract_bras_geometry.py`, `tools/validation/make_bras_scenes.py`,
  `docs/validation/bras_mapping.md` (selection and rules committed before any comparison; CR2 and
  CR3 reduction results).
- 20 CR2 scenes in `tests/scenes/validation/` (initial and `_fitted` α sets). No CR3 scene (old dimension rule; D-A),
  no CR4 scene (reader).
- AX24, AX25 in BUILD_PLAN §2.
- `render_cli --atmosphere`, `--mix-floor-ms` (validation only) and the debug-only
  `MAKROOF_TEST_BIAS_T60` hook.
- `tools/acoustics/radiosity.py` (a*, γ²-Eyring, Lambert Monte Carlo).
- Scope 7 meter checks: `tools/acoustics/meter_checks.py`, results
  `tools/acoustics/data/phase05_meter_checks.json`, recorded in AX23.
- `tools/validation/run_validation.py` + `report.py` (pipeline works on CR2; no report committed),
  `tools/validation/ab_pack.py`, `tools/acoustics/loudness.py` (BS.1770).
- `.github/workflows/nightly.yml` and its tests (`tools/validation/tests/test_nightly_gate.py`). The
  baseline golden `tests/golden/validation_baseline.json` does **not** exist yet: the gate tests skip
  until it does.

Commands:

```bash
# BRAS cache: ~/.cache/makroof/bras (override with MAKROOF_BRAS_CACHE or --cache); never commit it
python tools/validation/fetch_bras.py --groups docs materials parameters rirs geometry
# geometry extraction (one-off; needs the extra pins)
pip install -r tools/validation/requirements-extract.txt
python tools/validation/extract_bras_geometry.py --rooms CR2      # CRx; other rooms are kept
python tools/validation/make_bras_scenes.py            # write scenes; --check verifies they are current
python tools/validation/run_validation.py              # renders, metrics, report (--sim-only, --no-report)
python tools/validation/ab_pack.py                     # A/B pack -> build/listening-pack/phase-05
python -m tools.acoustics.run_meter_checks             # scope 7 leak calibration + paired noise test
pytest tools/validation
# nightly: .github/workflows/nightly.yml (schedule + workflow_dispatch)
```

Known state: CR2 parses in seconds, CR3 in ≈ 15 min, CR4 in > 40 min (not finished; run it
detached, see scope (b)).

## Scope

All of it as specified in phase-05.md, unchanged; this list says what is left.

a. **D-A (AX26) applied:** regenerate the scenes for all selected rooms (`make_bras_scenes.py`), with the
   reduction results appended to `bras_mapping.md` before any comparison (phase-05.md Data). No room
   is dropped after results are seen. If after D-A no room qualifies, phase-05.md Data's zero-room
   branch applies unchanged.
   - **CR2 volume.** BRAS documents V = 145 m³ (documentation p. 25; Brinkmann et al. 2019 Table II;
     external), the model gives 146.1 m³, which AX26 uses; with A fixed this raises predicted T by
     ≈ +0.76 % for every CR2 pair. Before any comparison, establish the cause (e.g. rounding in the
     documentation, or a volume the model includes that the documentation excludes) and record it in
     `bras_mapping.md`. The rule is unchanged: AX26 keeps the model volume (one generic rule for all
     rooms; no per-room correction, NFR-8). Report the +0.76 % beside the CR2 AQ9 line. If the cause
     shows the model volume is wrong, raise it through /fix-plan before the baseline is created; never
     after results are seen.
   - CR3: the documentation gives 2 350 m³ excluding the attic, the model 3 330.6 m³ including it
     (`bras_mapping.md`); the same check applies and is reported.
b. **CR4:** the geometry extraction is a one-off developer step, never run at run time (Maisara,
   2026-11-06). Run it detached with no time limit, outside the 40-minute tool timeouts, e.g.
   `nohup python tools/validation/extract_bras_geometry.py --rooms CR4 > extract-cr4.log 2>&1 &`.
   Speeding up `skp_reader.py`'s re-synchronisation is optional, not required. Accept CR4 only if
   every documented material area reproduces (the same check as for CR2 and CR3).
c. **Baseline and nightly gate:** create `tests/golden/validation_baseline.json` through
   `tools/ci/update_goldens.py` with a reason, and make the nightly gate (phase-05.md scope 4) and the
   `MAKROOF_TEST_BIAS_T60` test green.
   Known issue to resolve (PR #10 review; the criterion is unchanged): on `bras_cr2_ls1_mp1` (the
   scene the test picks for CR2) the debug-build hook at 1.05 raised T30 by +5.79 % at 500 Hz, above
   the criterion's +5.5 % upper limit. The cause is not established (a single realisation whose tail
   noise may differ between the biased and unbiased renders, or an interaction with tail length /
   level matching). Establish the cause before deciding whether the test design or the criterion
   needs a `/fix-plan`.
d. **Report:** generate and commit `docs/validation/report-phase05.md` and its EDC PNGs (phase-05.md
   scope 3).
e. **Scope 6 remainder**, as specified in phase-05.md scope 6, unchanged: the reference hybrid
   (AX21) with its per-band-s (B10) run; the X-b bound ΔL_b (AX16), including the Table 5.2 layouts
   and the uniform-α s-cases; the mixing-time handover comparison; paired comparisons and ensemble
   sizing; t_mp50 / t_mp95; the B11 (B) promotion evidence; the B12 decision with its conditions.
f. **A/B pack** (phase-05.md scope 5) added to the `listening-pack` artifact through
   `tools/ci/listening_pack.py`.

## Out of scope

As phase-05.md "Out of scope", unchanged. Also: the parts Phase 05 delivered, except where scope
(a)–(f) changes them.

## Acceptance criteria — automated

The Phase 05 criteria not yet met, as stated in phase-05.md "Acceptance criteria — automated",
unchanged:

- [ ] The report generates reproducibly (two runs give identical numbers).
- [ ] The nightly workflow runs green on the baseline, and the `MAKROOF_TEST_BIAS_T60=1.05` test
      meets phase-05.md's criterion.
- [ ] AQ9 pass/fail is printed per room (mean over pairs) and per pair, with the α set of each, and
      stated in the report summary (phase-05.md criterion).
- [ ] a* against the independent references, Table 5.2 column reported (phase-05.md criterion,
      as decided in D-B).
- [ ] AX26 unit test on a synthetic rotated L-shaped room and `make_bras_scenes.py --check`
      (phase-05.md criterion, added by D-A).
- [ ] Scope 7 paired noise test with AX27, each of the 18 case A conditions at L_min = 51, 55, 65 dB
      (48 dB reported; phase-05.md criterion, as decided in D-C).
- [ ] The report contains the scope 6 comparisons (decay predictors, reference hybrid, handover,
      humidity bound); reported, not gated.
- [ ] The report prints per band the octave and half-octave readings, r, the "meter-dependent",
      "leakage-sensitive" and "noise not verified" flags, both usable-range margins, the secondary
      half-octave AQ9 mean and the AX4 override render beside the AQ9 line.

Met in Phase 05 and kept green: the `fetch_bras.py` tamper test; the scope 7 simulated-EDC test; the
scope 7 leak calibration (recorded in AX23).

phase-05.md's paragraph below its criteria applies unchanged (failing AQ9 does not fail CI; "AQ9 met
in x/y scenes"; Maisara decides at the review via /fix-plan on B10/B11/B12/B2).

## Listening / manual checklist (Maisara)

Note: the A/B pack uses the omni IRs, so only monaural attributes can be compared: reverberance,
clarity and coloration. Level is removed by loudness matching. Coloration is heard under monaural
conditions, which exaggerate reflection coloration compared with binaural listening (Blauert §4.4.2).
Spaciousness (ASW, LEV) cannot be compared.

Headphones, A/B pack, without looking at `key.txt` first:
- [ ] For each pair, can you tell which is real? Note what differs: brightness, decay length, early
      "slap", graininess.
- [ ] Then check `key.txt` and write your notes on the PR. They go to the Expert with the report.

## Contractor review focus

The shoebox reduction rules (are they generic, not per-room tweaks?), the material mapping, the metric
comparison method, the scope 6 reference predictors and reference hybrid (independent of `src/sim`,
a* against Table 5.2), and whether the conclusions in the report follow from the numbers.

## Risks

As phase-05.md "Risks", unchanged. Also: CR4 extraction time (scope (b)); D-A (AX26) changes the
scenes of CR2, so nothing built on the 20 CR2 scenes from Phase 05 is final; regenerate them first. The ±1 % a* gate may be borderline on Table 5.2 case 6 (the solver at 1.25 m, 5.787 s,
is ≈ 1.2 % below a from-scratch particle simulation, 5.860 s, and still converging: last halving 0.42 %); 05e establishes it with the project MC at
SE ≤ 0.25 %; a failure is a finding for /fix-plan, not a reason to retune either implementation.

## Definition of done

Automated criteria green; report committed; status row 05e `done` with an "AQ9 met in x/y" note per
room and per pair, by α set (BRAS: evidence, not validation);
the PR summarizes findings for the Spatial Audio Expert.
