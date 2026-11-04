# Phase 05 — Validation against measured impulse responses + accuracy report

Size: **M** · Depends on: 04 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ2, AQ9) and §3 (F2, F3), PRD NFR-1, NFR-8, Q2, Q9

## Goal

Get the **first real-world evidence** of accuracy (NFR-1) early, while changing the simulation
method (AQ2) is still cheap. Compare the omni room IRs from Phases 03–04 against IRs **measured in
real rooms**, using only geometry and material data that comes with those measurements. Nothing is
hand-tuned.

## Assumptions in force

- **AQ9** thresholds against measured IRs: **T30 and EDT within ±10%, C80 within ±2 dB**, each averaged
  over the 500 Hz, 1 kHz and 2 kHz bands. Also reported per band, without gating.
- **AQ2** method under test. **NFR-8**: no per-scene factors. If a room fails, report it.

## Data

- **BRAS** — *Benchmark for Room Acoustical Simulation* (TU Berlin; licence CC BY-SA 4.0). It contains
  room scenes with geometry descriptions, material absorption/scattering data and measured omni and
  binaural IRs.
- Write `tools/validation/fetch_bras.py`. It downloads only the files needed (scene documentation,
  material tables, omni RIRs for the selected source/receiver pairs) from the official repository
  (DepositOnce), verifies SHA-256 checksums stored in `tools/validation/bras_manifest.json`, and caches
  them under `~/.cache/makroof/bras`. **Never commit the data** (CLAUDE.md rule). Add the attribution to
  `docs/THIRD_PARTY.md`.
- Before writing code, the session must read the BRAS documentation and record in
  `docs/validation/bras_mapping.md` which scenes were chosen and why. Pick the rooms whose geometry is
  closest to a rectangular box (likely the small seminar room and similar). State how each real room was
  reduced to a shoebox: dimensions so that the shoebox **volume and total surface area** match the
  documented room as closely as possible; materials mapped surface-by-surface with area-weighted
  averaging; and which BRAS material set is used. Use the **initial/as-documented** absorption data as
  the primary run. If the dataset also provides absorption values fitted to the measurements, run them as a
  secondary, clearly labelled run. Fitted data partly includes the answer, so it isn't proof of accuracy.
- If no BRAS room can be reasonably reduced to a shoebox, the phase is `blocked`. Report it. That's
  evidence for F3 and Q2.

## Scope

1. `tools/validation/fetch_bras.py`, `bras_manifest.json`, `docs/validation/bras_mapping.md`.
2. `tests/scenes/validation/bras_<room>_<src>_<rcv>.json` — contract scenes for the chosen pairs
   (source and receiver positions mapped into the shoebox frame).
3. `tools/validation/run_validation.py` — renders each scene with `render_cli --mode omni --ir`,
   computes ISO 3382 metrics for simulated and measured IRs with `tools/acoustics`, and writes:
   - `docs/validation/report-phase05.md`: a table per scene with band metrics, deltas and an AQ9
     pass/fail summary, plus EDC overlay plots saved as PNG next to the report (matplotlib, pinned).
   - `tests/golden/validation_baseline.json`: the current deltas, used for regression tracking.
4. CI: a **nightly** workflow (`.github/workflows/nightly.yml`, `schedule` + `workflow_dispatch`) on
   Linux. It runs the validation, uploads the report as an artifact, and **fails only on regression**
   (any metric delta worsening by > 2 % relative to the baseline). Also run it once on the phase PR.
5. An A/B listening pack: dry test material convolved with the measured IR and with the simulated IR,
   loudness-matched (BS.1770), named `A_*.wav`/`B_*.wav` with the key in a separate `key.txt`. Use
   public-domain or self-generated dry material only.

## Out of scope

Changing the simulation method. If results are poor, the PR proposes options (e.g. ray tracing for the
tail, better absorption mapping, a Sabine/Eyring/Arau-Puchades comparison) as **follow-ups for the
Expert**. It doesn't implement them.

## Acceptance criteria — automated

- [ ] `fetch_bras.py` verifies checksums. A corrupted file is detected (unit test with a tampered cached file).
- [ ] The report generates reproducibly (two runs give identical numbers).
- [ ] The nightly workflow runs green on the baseline and **fails** when a deliberate +5% T60 bias is injected
      via an environment variable test hook (`MAKROOF_TEST_BIAS_T60=1.05`; the hook exists only in debug builds).
- [ ] Each chosen scene's AQ9 pass/fail is printed and stated in the report summary.

Failing AQ9 thresholds does **not** fail CI. It goes in the BUILD_PLAN status notes as "AQ9 met in
x/y scenes" and is escalated.

## Listening / manual checklist (Maisara)

Headphones, A/B pack, without looking at `key.txt` first:
- [ ] For each pair, can you tell which is real? Note what differs: brightness, decay length, early
      "slap", graininess.
- [ ] Then check `key.txt` and write your notes on the PR. They go to the Expert with the report.

## Contractor review focus

The shoebox reduction rules (are they generic, not per-room tweaks?), the material mapping, the metric
comparison method, and whether the conclusions in the report follow from the numbers.

## Risks

- The documentation may be ambiguous about geometry or material assignment. Record each choice in
  `bras_mapping.md`; a reviewer can then challenge it.
- Real rooms aren't shoeboxes, so expect misses. This phase exists to surface that early (F2, F3).

## Definition of done

Automated criteria green; report committed; status row 05 `done` with an "AQ9 met in x/y scenes" note;
the PR summarizes findings for the Spatial Audio Expert.
