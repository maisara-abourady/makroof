# Phase 05e — Comparison with measured IRs, part 2 (remainder of Phase 05)

Size: **M** · Depends on: 05 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ2, AQ9, AX4, AX16, AX21, AX22, AX23, AX24, AX25) and §3 (F2, F3), **`docs/phases/phase-05.md` (all of it: its rules apply here unchanged)**, `docs/validation/bras_mapping.md`, `docs/review/ledger.md` section "Phase 05 session — Table 5.2 check and AX24/AX25", PRD NFR-1, NFR-8, Q2, Q9

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

Three plan decisions are open from Phase 05. Each must be taken through `/fix-plan` (acoustic choices
go to the interrogator first, CLAUDE.md) **before the work that depends on it starts**. Check
`docs/BUILD_PLAN.md` §6 first: if a row records the decision, apply it and say so; if not, raise it.

4. **(D-A) Dimension rule.** phase-05.md Data, "Dimensions" (keep h = V / documented floor area and
   S) gives degenerate or invalid boxes: CR2 becomes 13.9 × 3.6 × 2.9 m against a real ≈ 6.2 × 8.6 m;
   CR3 becomes 136.4 × 5.55 × 4.40 m, outside AX6 (≤ 100 m), so no CR3 scene is written (both CR3 end
   walls would also be clamped to α = 1). Waits on it: scope (a), and through it (c), (d), (e), (f)
   and every acceptance criterion that needs scenes or a report.
5. **(D-B) a* against Kuttruff Table 5.2.** The criterion "the a* solver reproduces the iteration
   column of Kuttruff Table 5.2 within ±1 %" is not checkable as written: the converged solver and an
   independent Monte Carlo are 1.6–7.3 % below the column (ledger T52-01, T52-10). The test is a
   strict xfail (`tools/acoustics/tests/test_radiosity.py`). Waits on it: the a* criterion below, and
   the B12 decision rule's use of a* (scope (e)).
6. **(D-C) Scope 7 paired noise test.** Case A fails in the 48 dB conditions (+1.8 … +2.1 % against
   the 0.6 % gate) and in 500 Hz / T = 1 s / 55 dB (+0.60 %); the cause is noise energy before the
   crosspoint, not the hull. Besides the bias, three 48 dB conditions have "unsuitable" realisations
   (noisy-arm T30 None): 5/51 at 500 Hz / 1 s, 1/51 at 500 Hz / 2 s, 1/51 at 1 kHz / 1 s.
   `tools/acoustics/tests/test_noise_handling.py` checks bias and suitability separately, both as
   strict xfails (7 bias, 3 suitability).
   phase-05.md scope 7's reversal ("measured IRs run without the hull behind a flag, through a new AX")
   concerns the hull; the decision says whether it applies or what replaces it. Waits on it: the
   paired noise criterion below, and the measured-IR noise handling that the report's numbers pass
   through (scope (d), (e)).

## Goal

Finish Phase 05's goal (phase-05.md "Goal"): the first real-world evidence of accuracy (NFR-1) and
AQ2, with the committed report, the nightly gate on its baseline, and the scope 6 reference
comparisons.

## Assumptions in force

As phase-05.md "Assumptions in force", unchanged, plus AX24 and AX25 (BUILD_PLAN §2, added by
Phase 05) and the Phase 05 leak calibration and paired noise results recorded in AX23.

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
- 20 CR2 scenes in `tests/scenes/validation/` (initial and `_fitted` α sets). No CR3 scene (D-A),
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

a. **After D-A:** regenerate the scenes for all selected rooms (`make_bras_scenes.py`), with the
   reduction results appended to `bras_mapping.md` before any comparison (phase-05.md Data). No room
   is dropped after results are seen. If after D-A no room qualifies, phase-05.md Data's zero-room
   branch applies unchanged.
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
- [ ] The a* solver against the iteration column of Kuttruff Table 5.2 (phase-05.md criterion),
      **subject to D-B**.
- [ ] Scope 7 paired noise test, each of the 18 case A conditions (phase-05.md criterion),
      **subject to D-C**.
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

As phase-05.md "Risks", unchanged. Also: CR4 extraction time (scope (b)); D-A may change the
scenes of CR2, so nothing built on the current 20 CR2 scenes is final until D-A is applied.

## Definition of done

Automated criteria green; report committed; status row 05e `done` with an "AQ9 met in x/y" note per
room and per pair, by α set (BRAS: evidence, not validation);
the PR summarizes findings for the Spatial Audio Expert.
