# 39 — Interrogator on file 24, items 2a and 2b (answers for Maisara never checked)

Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. Raised by the Decided-for-Maisara compilation (steward G23): file
24 gave 2a and 2b as "proposed, final after the seats report"; no later decider file finalised them and no
interrogator checked them; 2a's content is applied in the run sheet and `abx_kit.py`.

## 2a (record the realised Q5 window, no amendment): SURVIVES WITH CORRECTIONS
- PRD reading: NFR-1 (L105) read correctly ("Pass thresholds come from the Expert" supports leaving the
  pre-registered rules alone); both options shown against NFR-1; nothing in NFR-8 or her recorded decisions points
  the other way.
- Correction 1: "amend … after the data came in" is imprecise; no listening data exists, only the kit's
  onset-margin measurements (file 22). Restate as "after the stimulus measurements came in".
- Seats: no TENSION MISREAD. Seat 9 (26-seat9) keeps the 0.43 ceiling (1/1) on condition its premise is corrected
  on the record; Seat 1 rates T-a 0/1 and the window is the same under either T30.
- Correction 2: Seat 9's premise correction (the D/R drop, with the 0.1 s hold reproducing 0.375 s) is not in the
  run sheet yet; it is held in the debt register at phase-07c-2b.md L91. Say so in the final 2a line.
- Applied vs answered: match. Run sheet L65–74 gives [0.0007, 0.1865]·T30, boundaries 0–33 and 35, 46/81 = 0.568,
  46/36 = 1.28; `abx_kit.py` `q5_window_record` (L674–686) recomputes them on every build (0.1865 × 2.009 = 0.375 s).

## 2b (check first, then seal; deficit reported, not tuned): FAILS (PRD MISREAD, narrow)
- Option not shown: "seal now" is shown only against NFR-1, though NFR-8 is cited (README "Who answers": one line
  per option against the cited ids).
- Imprecise: "serves NFR-8" overstates. NFR-8 (L112) says "Any valid scene renders correctly"; the check serves its
  "no environment-specific code paths" by not tuning, but records that this valid scene does not render as diffuse
  theory predicts: a shortfall to state, not an NFR-8 benefit.
- Omitted recorded decision: her 2026-11-05 decision (BUILD_PLAN L144, AX21), "the early part should contain
  scattered energy", bears on this and points the same way; the empty early part is her known, decided deficit,
  not a new finding.
- Seats: no TENSION MISREAD (Seat 9 rates the old label 3/3; no seat argues for sealing now).
- Applied vs answered, partial: sealing waits (phase-07c-2b L94–113); but the run sheet (L56) and `abx_kit.py`
  (L133, L156) still carry the label "occupied mid-size hall envelope" that Seat 9 vetoed, held for M3 and not
  marked superseded; and the 8 kHz +18 % follow-up "before Phase 08's goldens freeze" (file 27) is in no phase
  file or BUILD_PLAN, so the "reported" half of 2b is dropped.

## Process
Both answers stayed "proposed"; no decider file made them final after files 26 and 30.

## For the decider
1. Give the "seal now" line against NFR-8. 2. Cite AX21's 2026-11-05 decision. 3. Say where the 8 kHz follow-up is
recorded outside docs/review/.
