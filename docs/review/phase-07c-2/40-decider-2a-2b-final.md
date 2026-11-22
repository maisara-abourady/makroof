# 40 — Decider: 2a and 2b, final (rebuttal to interrogator file 39; file 41's corrections applied)

Both answers are final. 2a stands with the interrogator's two corrections. 2b is revised to answer all three points
of file 39, and names homes outside `docs/review/` for the vetoed label and the 8 kHz follow-up. All plan edits are
in fingerprint-excluded prose, so the CI run in progress stays valid; no code or run-sheet change is needed now (H2).

Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

## Process
File 24 gave 2a and 2b as "proposed, final after the seats report". The seats reported (files 26, 30); files 27,
31 and 34 never finalised them. This file does. File 39 found no TENSION MISREAD and no UNDERCONVENED for either
item. Seat 9 rated the old label 3/3 (26-seat9 L21) and the corrected label 1/1, 0/0 on its conditions (L22, L42).
No seat argues for sealing now.

## Answers to file 39
| file 39 point | answer | state |
|---|---|---|
| 2a correction 1: "after the data came in" | Accepted: "after the stimulus measurements came in" (no listening data exists; only file 22's onset-margin measurements). | applied |
| 2a correction 2: Seat 9's premise correction not on the record | Accepted. Edit P1 writes it in full in phase-07c-2b.md's debt-register bullet (L91). | applied |
| 2b: "seal now" not shown against NFR-8 | Accepted. Each option has one line against NFR-1, NFR-8 (both halves) and AX21. | applied |
| 2b: "serves NFR-8" overstates | Accepted. Not tuning serves "no environment-specific code paths"; against "Any valid scene renders correctly" it is a stated shortfall. | applied |
| 2b: AX21 decision of 2026-11-05 omitted | Accepted and cited; it points the same way. File 24's "found a real deficit" is withdrawn: the empty early part is her known, decided deficit. | applied |
| 2b: vetoed label not marked superseded | Accepted. Edit P2 in phase-07c-2b.md; PR Follow-up F1. Run sheet and `abx_kit.py` keep the string until M3 (H2). | home given |
| 2b: 8 kHz follow-up has no home | Accepted. Edit P3, a freeze-point condition in phase-08-4.md "Notes from the split"; PR Follow-up F2. | home given |

## FOR MAISARA 2a (final): record the realised Q5 window; no amendment
- **Question:** the stimulus measurements show the realised Q5 onset window on `layout4_s1/default` is
  [0.0007, 0.1865]·T30, narrower than the pre-registered 0.43·T30 ceiling. Amend the rule to the realised window, or
  leave it and record the window?
- **Answer:** "The pre-registered Q5 rule (onset no later than 0.43 · T30(1 kHz) after the end of speech, ≥ 20 dB
  onset assertion) is not amended. The realised window, [0.0007, 0.1865] · T30 (1.4 ms to 0.375 s at heard-IR T30
  2.009 s; passing boundaries 0–33 and 35 of 81; first-draw replacement probability 46/81 = 0.568; 46/36 = 1.28
  replaced onsets per stimulus), is recorded in the run sheet and recomputed by the kit for the pre-registered pair
  before sealing. Seat 9's premise correction to the 0.43 ceiling (t ≤ hold + (SNR − 20 − L_drop)/60 · T60_tail,
  which reproduces the measured 0.375 s) is held in the M3 debt register, phase-07c-2b.md scope 2."
- **Rests on:** NFR-1 (PRD L105), "Pass thresholds come from the Expert." No recorded decision of hers on Q5.
- **Options:** no amendment serves NFR-1 (the Expert-derived rule untouched, the realised window on record), neutral
  on NFR-8; amend strains NFR-1 (changes a pre-registered test after the stimulus measurements came in, nothing
  gained), neutral on NFR-8.
- **Strongest PRD reading against:** NFR-1's "pass listening tests" could ask for the test matching what the
  stimulus delivers; it doesn't hold, since the window is recorded either way and the accepted onsets are identical.
- **Seats:** Seat 9 keeps the ceiling at 1/1 on the condition its premise is corrected on record (26-seat9 L15,
  L29), met by P1. Seat 1 rates T-a 0/1. No 3.
- **Applied vs answered:** match (run sheet L65–74; `abx_kit.py` `q5_window_record` L674–686). Amends: none.

## FOR MAISARA 2b (final, revised): check first, then seal; the deficit is reported, not tuned
- **Question:** seal the ABX stimuli on `layout4_s1/default` now under the item-9 label "occupied mid-size hall
  envelope", or check first (D/R, early part, T30) and seal only after M3?
- **Answer:** "Check first, then seal. Sealing waits on M3 (phase-07c-2b.md scope 2). Under her AX21 decision of
  2026-11-05, the scene's empty early part is a known, decided deficit, not a new finding. It is reported, as are
  D/R about 20 dB above the diffuse-field expectation and the 8 kHz tail T30 at +18 % against target; nothing in
  `src/sim/` is tuned for it. The label 'occupied mid-size hall envelope' is superseded pending M3 (Seat 9, 3/3) and
  is replaced by M3's item-9 label before any seal. The 8 kHz follow-up is a freeze-point condition of Phase 08-4."
- **Rests on:** NFR-1 (L105); NFR-8 (L112) "Any valid scene renders correctly; no environment-specific code paths";
  her decision of 2026-11-05 (BUILD_PLAN AX21, L144) "the early part should contain scattered energy".
- **Options against each cited id:**
  - Check first / NFR-1: serves (sealed under a label matching measured D/R, early part, T30).
  - Check first / NFR-8 "no environment-specific code paths": serves (nothing tuned; 8 kHz work analysis-only).
  - Check first / NFR-8 "Any valid scene renders correctly": a stated shortfall (early part empty; D/R +10.7 / +9.7
    dB against −10 dB, file 22, 26-seat9 L32).
  - Check first / AX21: consistent (deficit recorded as hers and decided; the fix stays on B11).
  - Seal now / NFR-1: strains (label contradicted by about 20 dB in D/R).
  - Seal now / NFR-8 no-tuning half: neutral.
  - Seal now / NFR-8 correctness half: strains (shortfall unrecorded; implies a hall renders correctly).
  - Seal now / AX21: strains (presents the deficit as hall-like early structure).
  - Seal now is also excluded at step 2 by Seat 9's veto-grade rating of the old label (26-seat9 L21, 3/3).
- **Strongest PRD reading against:** waiting on M3 delays the ABX; no PRD id ranks speed above accuracy, and the
  delay is 07c-2b's recorded hand-off. Amends: none (applies AX21, does not change it). State: revised (replaces
  file 24's 2b).

## H1. Homes outside `docs/review/`
1. Seat 9's premise correction (2a): phase-07c-2b.md scope 2, debt-register bullet L91 (P1).
2. The superseded label (2b, printed by the run sheet, `abx_kit.py` and `tools/ci/listening_pack.py` L452): phase-07c-2b.md
   scope 2, "Amendments held for M3" L94–99 (P2), plus PR Follow-up F1.
   Two guards stop a seal under the old string: item 9's label is replaced once M3 survives (L94–96); "the manifest
   carries Seat 9's label" is required before each seal (L112).
3. The 8 kHz +18 % follow-up (2b): phase-08-4.md "Notes from the split", the freeze-point-conditions bullet
   L129–133 (P3), plus PR Follow-up F2.

## H2. Why the run sheet and `abx_kit.py` keep the old string until M3
Nothing is sealed in 07c-2 (the seal is 07c-2b scope 3, after M3), and two guards cover it; the replacement text
depends on M3's scene choice; editing `docs/validation/` or `tools/ci/` now would restart CI with no gain.

## Plan-text edits (prose only, fingerprint-excluded)
**P1.** `docs/phases/phase-07c-2b.md`, scope 2, replace the bullet beginning "- Seat 9's 0.43 ceiling, rated 1/1 on
every option, goes in the decision's debt register (file 31)." (L91) with:
```
   - Seat 9's 0.43 ceiling, rated 1/1 on every option, goes in the decision's debt register (file 31), with its
     premise corrected on the record (Seat 9, file 26 §5; decider file 40, 2a): the 26/60 premise assumed D/R ≤ 0;
     the corrected bound is t ≤ hold + (SNR − 20 − L_drop)/60 · T60_tail, L_drop = 10·log10(1 + 10^(D/R/10)), which
     on layout4_s1/default (L_drop 13.3 dB, from the heard L + R D/R +13.1 dB at 1 kHz, file 22; hold 0.1 s; T60_tail 1.30 s; the 46 dB SNR is broadband, Seat 9's [Hyp]) gives 0.375 s, the measured realised Q5
     window. The pre-registered Q5 rule itself is not amended (decider file 40, 2a).
```
**P2.** `docs/phases/phase-07c-2b.md`, scope 2, "Amendments held for M3" bullet, after "File 34 item 1's "[S-A only,
as long as layout4_s1/default is the ABX scene:]" clause is re-examined by M3's scene choice." (L99), append:
```
     Until then the item-9 label "occupied mid-size hall envelope, not a validated preset", still printed in
     `docs/validation/abx-07c-2-run-sheet.md` (§1 "Scene"), in `tools/ci/abx_kit.py` (scene docstring and the
     manifest `label` string) and by `tools/ci/listening_pack.py` (L452, which prints the kit's label into the
     phase-07c-2 listening-pack artifact's text and manifest), is **superseded pending M3**: Seat 9 rated it 3/3
     (file 26) and "hall" and "occupied" are removed everywhere (file 27). It is replaced by M3's item-9 label in all
     three before any seal; no stimulus is sealed under it, and the 07c-2 listening-pack artifact that still prints
     it is marked superseded in 07c-2's PR listening checklist (decider file 40, 2b).
```
**P3.** `docs/phases/phase-08-4.md`, "Notes from the split", last bullet ending "and AX35 (a converter re-run before
the freeze is a parameter change)." (L133), append:
```
  Also before the freeze: the **8 kHz tail-T30 follow-up** (phase-07c-2 decider files 27 and 40, 2b; NFR-8, reported,
  nothing tuned). The tail T30 at 8 kHz on layout4_s1/default reads 0.870 / 0.884 s against the 0.740 s target
  (+18 %; tail EDT +5 to +7 %; file 22). Render a synthetic exponential noise with T60 0.74 s through the AX13 band filter,
  and measure the tail's own band-7 noise without the neighbouring bands, to settle whether the analysis filter or
  the tail causes it. The result (cause, numbers) is cited before any golden is frozen; if it has not been run, it is
  this phase's first work (`tools/acoustics` only, no `src/sim/` change). If the tail is the cause, it returns to the
  board before the freeze; nothing is tuned for the scene.
```
**PR Follow-ups:** F1 "The ABX item-9 label 'occupied mid-size hall envelope' (run sheet §1, `abx_kit.py` docstring
and manifest `label`, and `listening_pack.py` L452 (the 07c-2 listening-pack artifact)) is superseded pending M3 (Seat 9 3/3); replaced before any seal in phase-07c-2b scope 2
(decider file 40, 2b)." F2 "The 8 kHz tail T30 reads +18 % against target (file 22); its cause is settled before
Phase 08's goldens freeze, as a freeze-point condition in phase-08-4 'Notes from the split' (decider files 27, 40)."

## Load-bearing claims
- D40-L1: NFR-1 L105 "Pass thresholds come from the Expert"; NFR-8 L112 "Any valid scene renders correctly; no
  environment-specific code paths."
- D40-L2: BUILD_PLAN L144, AX21: "Maisara decided on 2026-11-05 that the early part should contain scattered energy."
- D40-L3 (file 22; 26-seat9 L32): per-emitter D/R +10.7 / +9.7 dB at 1 kHz against −10.2 dB diffuse at r/r_c 3.22
  (Kuttruff §5.6, Eqs. 5.43–5.45, as Seat 9 cites).
- D40-L4 (26-seat9 L36): L_drop 13.3 dB; (46 − 20 − 13.3)/60 · 1.30 = 0.275 s; + 0.1 s hold = 0.375 s.
- D40-L5 (per file 39): [0.0007, 0.1865]·T30 × 2.009 s = 0.375 s.
- D40-L6 (file 22 L121; 26-seat3 L65): 8 kHz tail T30 0.870 / 0.884 s against 0.740 s. Caution: file 25 L61 finds
  it in all four K3 scenes, but they share one tail realisation, so not independent evidence it is generic.
- D40-L7 (CLAUDE.md "When CI skips"): `docs/phases/` fingerprint-excluded; `docs/validation/`, `tools/ci/` not.

## Future-debt register
| seat | commits later phases to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| 9 | 0.43 ceiling kept with premise corrected; binds again on s < 1 scenes | re-check the window on the M3 scene | M3, item 15(i) | M2/Q5 checks pass on the sealed scene (07c-2b scope 2) |
| 9 | old label stays in run sheet and kit until M3 | three lines in three files (run sheet L56; abx_kit.py L133, L156; listening_pack.py L452 reads the kit's string) + one CI run | M3 survives | replaced before any seal (P2) |
| 3 | 8 kHz tail T30 +18 % | analysis fix, or tail fix through the board | the 8 kHz follow-up | cited before the 08-4 freeze (P3) |

## Strongest objection
The label is still live in code and run-sheet text. Editing it now costs a CI rerun and pre-empts M3's scene
choice; it holds because no seal can happen before M3 and both guards stop a seal under the old string.

Confidence: high (2a), medium (2b; the 8 kHz cause is open, which is the follow-up). Reversal: 2a, the Expert sets a
different Q5 threshold; 2b, the 8 kHz follow-up shows the tail is the cause, or M3 keeps layout4_s1/default with a
label Seat 9 rejects.

## Summary
| id | decision | state | worst-off seat | sum | confidence | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| 2a | no amendment; window recorded; premise correction at 07c-2b L91 (P1) | stands (corrected) | Seat 9 (1/1) | 3 | high | NFR-1 | Kuttruff §5.6 via Seat 9 | Expert Q5 threshold |
| 2b | check first, seal after M3; reported not tuned; label superseded (P2); 8 kHz at 08-4 freeze (P3) | revised | Seat 9 (1/1; 0/0 on conditions) | 2 | medium | NFR-1, NFR-8, AX21 | Kuttruff §5.6 | tail is the 8 kHz cause; M3 label rejected |

Challenges to settled decisions: none. NEEDS MAISARA: none.

## Decided for Maisara
- **2a.** The pre-registered Q5 onset rule stays as written; the narrower window the stimulus measurements showed
  (up to 0.375 s) is recorded, and Seat 9's corrected reasoning for the 0.43 ceiling is written into 07c-2b's M3
  debt register. NFR-1. Amends none of her decisions.
- **2b.** The ABX stimuli are checked first and sealed only after M3; the dry scene's empty early part is reported
  as her known AX21 deficit (2026-11-05), nothing tuned; the "occupied mid-size hall envelope" label is superseded
  pending M3; the 8 kHz +18 % tail-T30 question is settled before Phase 08-4 freezes its goldens. NFR-1, NFR-8 (both
  halves), AX21. Amends none of her decisions.
