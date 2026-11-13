# 11 — Decider: decision round 3 (last), phase 07c-1b — Q1–Q5, smaller corrections, final plan text

2026-11-13, corpus c1b171f. Saved by the orchestrator from the decider's report. No new acoustic claim (Vorländer §4.3 Eq. 4.15
unchanged, CORRECT in round 1). Read: files 8, 10, 9-seat5/6/7, 5-seat3-r2; the C7′ / C7 lines of 2-seat3, 2-seat6, 2-seat7,
2-seat8; PRD L99–112; BUILD_PLAN L160 (AX38 in full), L169 (AX47); phase-13.md L54; phase-13-1 and 13-5 R3 (L17–19); phase-13-2
scope 1; phase-13-3 scope 4; README L87–135; code `tests/unit/test_diffuse_records.cpp` L93–110 (`kSolveWarn` 1.20,
`kMacGrowthTriggerMs` 2172.0). PRD digest as file 8, one correction: NFR-4 (L108) names platforms, not a CI form — no longer cited
for "printed on macOS" (row 15); that basis is RG-F1, her recorded 4c text.

## State per decision
| item | round-2 verdict | round-3 state |
|---|---|---|
| D-B1 | SURVIVES | stands |
| D-B2 / FM-B2 | PRD MISREAD (formal) | revised: Q4, row 04 |
| FM-10S | PRD MISREAD | revised: Q3, Phase 13 R3 lines |
| D-B3 | SURVIVES | stands; plan item 6 reworded (row 22) |
| D-B4 | SWC | corrected (rows 09, 10) |
| D-B5 (i) | SURVIVES | stands |
| D-B5 (ii) / FM-GROWTH | TM + PRD MISREAD | revised: B-iv+ cells in; composed B-iv/+07d decided (Q1); AMENDS completed (Q2) |
| D-B5 (iv) | PRD MISREAD (formal) | revised: inside FM-GROWTH's answer with PRD lines (Q2) |
| D-B5 (iii) / FM-TRIG | SWC | corrected: S7 cell entered, sum comparison dropped, debt undo added, FM-TRIG amends nothing (Q5, row 19) |
| D-B5 (v), (vi) | SURVIVES | stand; (vi) item 4 adds Seat 7's run cap |

## Q1 — D-B5 (ii), B-iv+ ranked in this phase
Options: **B-iv** (file 8); **B-iv+ now** (B-iv plus RG-1's in-window absolute 1.10 bound kept from now, ±5 %, n = 3 S2 runs);
**B-iv/+07d** (composed): B-iv until the 07d re-pin, where the in-window absolute leg is added under Seat 5's (1)–(4) (≥ 6 green
runs; 1.10 unchanged; window narrowed until (1 + w)·max(r/r̄) ≤ 1.083; in-window evaluation printed; coverage stated; not added if
max(r/r̄) ≥ 1.07), Seat 6's (a′), (e), (f), Seat 7's (1)–(3); B-i, B-ii, B-iii (file 8).
**f read in this phase (row 12)** from 07c-1b's S2 split (D-B5 (vi) item 3), before `done`; pre-registered: **branch A** f ≤ ×1.4
(≈ ×1.28 on 05h code); **branch B** f > ×1.4, or s_L ≤ 1.10·s_F (the ratio never reaches 1.10 under a uniform slowdown).

| opt | S2 | S3 | S5 | S6 | S7 | max | sum |
|---|---|---|---|---|---|---|---|
| B-iv (conditions met) | 1/1 | 1/1 (1/2) | 1/1 | 1/1 | 1/1 | 1 (2) | 10 (11) |
| B-iv+ now | 1/1 (fc, file 8) | 1/1 | **2/2** | 1/1 (1/0 with a′, e, f) | 1/1 (its (1)–(3)) | **2** | 12 (11 with S6's conditions) |
| **B-iv/+07d** | 1/1 (fc) | 1/1 (fc) (1/2) | 1/1 (Seat 5's conditional rating) | 1/1 (fc) | 1/1 (fc) | 1 (2) | 10 (11) |
| B-i / B-ii | — | 1/2 | 2/1 | 1/2 | 2/1 | 2 | 12+ |
| B-iii | — | 1/2 | 2/2 | 2/2 | 2/2 | 2 | 15+ |

(Cells "branch A (branch B)". Seats 1, 4, 8, 9 not required.) Cell reasons: S5 B-iv+ now 2/2 — "at the window's upper edge … it
goes red once r/r̄ > 1.048"; Windows max/mean 1.030–1.062; "detection gained and flake added are the same mechanism" (9-seat5
L12–24); S5 B-iv/+07d 1/1 — "Conditions (B-iv+ 2/2 → 1/1), all four", the first "adopt only at the 07d re-pin from ≥ 6 green runs";
S6 B-iv+ "Now … 1", "Later … 1, 0 under the conditions" — variant read 1/1, not 1/0 (Seat 6's B-iv later-1 reason, "07d's remedy
could grow synthesis ≈ 25 % unasserted", stays true until the absolute leg lands at 07d; its (f), (e) met); S7 B-iv+ "Now 1 …
Later 1" with (1)–(3), B-iv "1/1 can live with" — variant the larger, 1/1; S3 B-iv+ "1 | 1", "→ 1/0: at the 07d re-pin the ratio
bound re-derived from ≥ 6 runs", B-iv "1/2" if f > ×1.4 — variant read conservatively as B-iv's cell until 07d (if read 1/0 the
variant wins outright, sum 9; same decision); S2 briefed on B-iv only, its C1–C3 met by item 9 (row 13).
Working: (1) every option changes RG-1's form (her recorded 4c text): admissible only through FM-GROWTH; none breaks NFR-8, AX5 or
"never loosen" (1.10 unchanged in all); (2) no veto; (3) branch A: B-iv and B-iv/+07d max 1, B-iv+ now out on Seat 5's 2/2; branch
B: all max 2; (4) B-iv/+07d is the round's one composed variant, meets Seat 5's conditions (2 → 1), raises no other seat; (5) sum:
branch A 10 = 10; branch B 11 = 11 = 11; (6) reversibility: B-iv and B-iv/+07d equal (one plan line, one constant); B-iv+ now the
dearest (each false red on identical code a registered (d) defect closing only via `/fix-plan`); (7) the tie goes to the PRD check
(README L108–112): the preamble's "must stay usable" needs a believed load-time detector; B-iv/+07d is identical to B-iv until 07d,
then adds uniform-slowdown detection sized with a stated margin from ≥ 6 runs — the preamble points to B-iv/+07d in both branches.

**DECISION D-B5 (ii): B-iv/+07d** (exact text plan item 9, G5). PRD reason why not B-iv+ now (row 15): at ±5 % its firing range
overlaps the measured noise of identical code (red at r/r̄ > 1.048 vs observed max/mean up to 1.062); under 4c (d)'s "no re-run"
each such red is a registered defect, sending 07d after non-defects and pressing toward widening 1.10 (against "never loosen"); a
detector that fires on identical code does not serve "usable" better than one that waits for the ≥ 6 runs that size it; what is
lost before 07d is a leg evaluating on ≈ 1 in 6 x64 runs (fact 5) — none of the Linux S2-proxy runs fell in the window.

| seat | commits | undo | evidence | repaid when |
|---|---|---|---|---|
| S2 | uniform slowdown seen only from f until 07d; mandatory re-pins (07c-2, 07d) | one constant + CHANGELOG | S2 split; 07d runs | re-pins |
| S3 | branch A 1: detection only from f until 07d; branch B **2**: 07d may size its remedy on synthesis grown up to ×f unasserted (the per-stage split printed every run limits this) | bring the absolute leg forward (one plan line) | S2 split (07c-1b); 07d | 07d re-pin adds the absolute leg |
| S5 | 07d's ≥ 6-run re-pin with the margin rule; possibly no leg if max(r/r̄) ≥ 1.07 | one constant | 07d runs | 07d re-pin |
| S6 | absolute leg may be dormant (no in-window x64 run); stated in the record | — | 07d re-pin | (e) dormancy line |
| S7 | ≥ 6 manual runs at 07d ("runs 07d makes anyway"); in-window red through the evidence path | — | 07d | 07d re-pin |

Strongest objection (Seats 6, 3 premortem: a ≈ 25 % 07d synthesis change unasserted until the re-pin) holds because the per-stage
split prints on every OS every run (vi item 3), 07d's closure evidence reads it, and in branch A the ratio asserts from ×1.28.
Confidence medium (three cells from conditions). Reversal: an in-window or ratio red on identical code shown to be noise by the
evidence path; or 07d's runs giving max(r/r̄) ≥ 1.07 (then B-iv plus a printed absolute line, as Seat 5 says).

## Q2 — FM-GROWTH, complete (covers (ii) and (iv))
**Question.** May the hosted low-α growth assertion and the solve baselines leave RG-1's in-window form, which almost never
evaluates (fact 5: 1 of 9 OS-runs in window; Linux 453 / 490 / 706 vs mean 550)?
**Answer.** "AX38 4c's growth check becomes, on Linux and Windows, the same-run low-α / flutter ratio asserted at 1.10 × its S2
mean every run. At the 07d re-pin the absolute 1.10 bound returns as an in-window leg, with its window sized from ≥ 6 green runs to
leave a stated margin. The solve baselines are the S2 means, PROVISIONAL until a dated exit. The factor 1.10, macOS print-only, 'no
re-run' and the Phase 13 release-machine re-check are unchanged." Full text plan item 9 (a)–(b), G1–G14.
**Rests on:** preamble (L101 "must stay usable"); NFR-6 (L110); RG-F1 (AX38 4c, her decision via AMENDS 2026-11-10: "printed on
macOS", "Phase 13 re-enforces … the 1.10 growth bound"); CLAUDE.md "tolerances never loosened".
**Reasoning:** RG-1 set the in-window bound to detect restore growth; on current runners it evaluates on 1 of 9 OS-runs, so the
preamble's purpose has no armed detector; the same-run ratio cancels runner speed (Linux max/min 1.071, Windows 1.096) and
evaluates every run; 1.10 unchanged, blind spot written in words; the absolute leg returns once ≥ 6 runs size it without false
reds; the solve exit ends PROVISIONAL on evidence at a named date instead of never.
**Options vs PRD ids:** B-iv/+07d serves the preamble and NFR-6 (armed every Linux / Windows run — Windows only while its S2 max/min
≤ 1.10 — with a uniform detector from 07d), strains them by detecting uniform slowdowns only from ×f until 07d; B-iv the same until
07d, never adds the uniform leg before Phase 13; B-iv+ now serves detection earlier, strains the preamble and the verification
culture by false reds on identical code under "no re-run" (Seat 5 2/2); B-i, B-ii strain the preamble (0–1 in-window runs, no
detector); B-iii strains it through false defects (±22 % honest width vs 1.10); RG-1 unchanged = B-i on these runs; (iv″) with exit
serves the preamble and NFR-6 (solve print calibrated on S2 evidence, pinned at a dated point: ≥ 3 runs with ns/eval within 1.05;
else 07d; else Phase 13 release machines); (iv″) without exit strains the preamble (PROVISIONAL "may never end", Seat 3; no
calibrated solve print before Phase 13); "Confirm the 05i rule" cannot be met (no OS has 3 in-window runs) = no exit.
**Veto trigger:** reading "never loosen" as covering a change of form (between now and 07d a uniform slowdown below ×f is printed,
not asserted). **Public reason (Seat 7):** "The absolute bound measured runner speed; the same-run ratio measures the code. The
absolute bound returns where it can measure without false alarms, at 07d and on the Phase 13 release machines."

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (RG-1 / RG-F1 text in AX38 4c, BUILD_PLAN L160).
Superseded passages, verbatim (G1–G14 in plan item 9):
- (b) "on hosted runners asserted only in the RG-1 form below: on Linux and Windows inside the ±5 % flutter window, printed on
  macOS until Phase 13"
- (c) "the low-α scene's hosted-runner assertion stays in this form (in-window on Linux and Windows, printed on macOS) until Phase
  13"
- "Hosted-runner assertion unchanged until Phase 13"
- "(now the in-window mean 2 068 ms, bound 1.10 × 2 068 = 2 275 ms, asserted in-window: 'Assertion form' below)"
- "(an out-of-window row, flutter +11 %; now the in-window mean 1 817 ms, print only)"
- "(a red run; now the in-window mean 2 028 ms)"
- "and, on Linux and Windows only, median-of-10 low-α restore ≤ 1.10 × the pinned baseline median when the run's flutter median is
  within ±5 % of its pinned reference, else `NOT EVALUATED (runner)`"
- "the low-α/flutter restore ratio above 1.20 × its pinned ratio"
- "`SOLVE` printed … when the run's solve median exceeds `kSolveWarn` = 1.20 × the scene's in-window solve baseline per OS.
  Baselines, low-α / flutter: Linux 80.9 / 131.2 ms and macOS 83.7 / 102.7 ms (run 43007183782); Windows 90.4 / 144.4 ms (runs
  42964823518, 43007183782). PROVISIONAL, n = 1–2. k from the spread of the three RG-1-form runs (largest max / mean 1.086)."
- "A cell printing SOLVE in window on two runs"
- "k and the baselines are re-derived from ≥ 3 in-window runs at the 07c re-pin, and re-pinned when the work changes (07c-2)"
- "the absolute median above 1.10 × baseline where not asserted (macOS until Phase 13)"
- "the printed growth line uses the in-window baseline 1 817 ms"
- "flutter reference and ratio the mean of the measured runs per OS (Linux 701 ms / 3.05, Windows 737 / 2.83 …; macOS 484 / 3.75
  …)"
- "baseline median the mean of in-window runs (Linux 2 068, Windows 2 028; macOS 1 817, print only); never a red or out-of-window
  run"
- "the ±5 % window and the solve bound re-derived from ≥ 3 in-window runs at the 07c re-pin"
- (Conditions J1) "a growth bound, median-of-10 restore ≤ 1.10 × the recorded median (since RG-1: the pinned baseline median, (b))"
Not amended: 1.10; 4c (d) "A broken assertion, or the macOS trigger, is a defect: no re-run …"; "re-pinned only when the restore
path changes, one run PROVISIONAL, ≥ 3 runs with a CHANGELOG reason"; "Phase 13 re-enforces the strict 30 s and the 1.10 growth
bound on all three OSes on the release machines"; the flutter 14 × worst ≤ 30 s assertion.
Each side's last word if the check fails: interrogator (Q1) — the preamble and NFR-6 point to B-iv+ because it loosens nothing;
decider — they point to the variant, because B-iv+ now adds a detector that fires inside identical-code noise under "no re-run".

## Q3 — FM-10S at Phase 13 R3 (row 06)
Yes. AX38 (iv) Record: "phase-13 Raise item 3 applies the 10 s line to the former on the release machines and names the latter as a
finding if above 10 s" — where her line is applied before release. **FM-10S, revised answer:** "Yes. Wherever her 10 s line is
read, the time until the last instance is audible at load is the larger of record (h)'s totals measured without a settle wait:
prepare-first (interleaved and batched) and `setState`-first. All three are printed. The places it is read: 07d's 5 s criterion and
record (h) in CI; phase-08-4's re-read; phase-13 R3 — 13-1's first message on the latest record, and 13-5 before the beta on the
release machines (13-2 scope 1 runs the records there). 'The former' (time until audible at the interim level) is held to 10 s;
'the latter' (final tail settled) is named as a finding above 10 s." Rests on: her AX38 (iv) line and its Record (L160,
2026-11-10); phase-13-1 / 13-5 R3 (L17–19); preamble; NFR-6; R17. Reasoning: her line names the user's wait; the host order is not
fixed, so the larger total is honest, and the release-machine reading is binding. Options: the larger total serves the preamble and
NFR-6; `setState`-first only under-reports by up to 3.44 s at the very point she rules on. Veto trigger: "at load" read as the
plugin's restore alone. AMENDS nothing (a reading where her line is silent on call order). Plan lines: item 13.

## Q4 — FM-B2 / D-B2 options at project load (row 05)
Added option lines (answer text unchanged): **B2-a″** serves NFR-1 (first sound at the final level); at an 8-instance load in
prepare-first hosts it adds 1.16–3.44 s (≈ 11.4–13.6 s est. vs 10 206 ms measured keyed, run 42 macOS) — counted (FM-10S), owned by
07d with C9 first. **B2-b dry**: async insertion the restore's quiesce cancels (L914) — removes the serial 1.16–3.44 s, serving the
preamble and AX38 (iv) at load, but does not bring run 42 under 10 s (10 206 ms > 10 s), so her line fires either way; strains NFR-1
at every insertion (dry first sound 0.15–0.43 s, unlike the render); the preamble ranks "Accuracy is the top priority" (L101).
**B2-d**: an embedded default-scene E_b saves only the stage-1 solve's share of each insertion (not measured); ISM, interim synthesis
and the restore stay serial — removes at most part of the 1.16–3.44 s; strains NFR-8 (a scene-specific constant). **B2-b silent**:
Seat 6 3/3, veto-grade. The PRD check stands: no alternative clears her 10 s line on the measured run; the accuracy-first preamble
points to B2-a″; 07d (C9) owns the load cost before release. Row 04: B2-b dry S9 cell **0/0**. Row 25: Seat 6 saw the prepare-first
figure (file 6 row 14) in r2b and did not revise; Seat 8 not re-asked — strongest objection: if Seat 8 rated B2-a″ 2 later on a load
above 10 s the max would become 2, but B2-b dry already carries Seat 8 2/1 and Seat 6 2/2, so the decision stands on step 3.

## Q5 — FM-TRIG and D-B5 (iii) corrections (rows 19, 20)
**FM-TRIG restated as a reading that amends nothing.** "(≥ 3 in-window runs)" is in RG-1's file 70, not in her record; her recorded
4c text (README L102–104) says "1.15 × the mean of the four measured macOS medians, rounded down; re-derived at the 07c re-pin".
Question: at the 07c re-pin, over which runs? Answer: "Over all green macOS low-α medians of the 07c-1b S2 runs, factor 1.15,
rounded down, computed by script from the GATE lines." Rests on: preamble; NFR-4 (macOS a shipping platform, so its load signal
needs a detector); RG-F1. Options: M-a serves the preamble (≈ ×1.16); S6-k blunts detection (≈ ×1.25) and changes her "1.15 ×".
Veto trigger: a trigger firing on its own calibration run (then S6-k). AMENDS nothing.

| opt | S3 | S5 | S6 | S7 | max |
|---|---|---|---|---|---|
| **M-a + closure path** | 1/1 | 1/1 | 1/1 | **1/1** (9-seat7: "M-a 1 … M-a 1 only with X-d−'s closure path") | 1 |
| S6-k | 1/1 | 1/1 | 1/1 | 1/1 | 1 |

S6-k falls at step 1 (changes "1.15 ×" in her recorded text; no PRD id calls for it); no sum comparison. **DECISION M-a** with Seat
7's conditions: (1) one sentence in 4c and the PR when an S2 run exceeds the trigger it helped set (proxy: run 44's 2 572 vs 2 423
ms); (2) MACTRIGGER print or annotation only; (3) closure evidence from runs 07d makes, ≤ 3 extra manual runs per defect; (4) if the
closure path is dropped, Seat 7 → 1/2 and the board reconsiders S6-k.

| seat | commits | undo | evidence | repaid when |
|---|---|---|---|---|
| S3, S5, S6, S7 | a weather double ([Hyp] ≈ 1 in 9 pairs) becomes a defect closing only on evidence | one constant + CHANGELOG; switching to S6-k needs a FOR MAISARA amendment | 07d runs; Phase 13 | X-d− closure evidence |

## Smaller corrections
Row 04 S9 B2-b dry 0/0. Row 09 D-B4's S6 / S8 debt row: "8-stem loads ≈ 10.2 s measured `setState`-first (run 42 macOS keyed,
10 206 ms) and ≈ 11.4–13.6 s estimated prepare-first (D2-L2) until 07d". Row 10: the seats' C7′ / C7 conditions are each met under
the stricter 5 s reading — Seat 3 "the trigger and its figure carried into 07d / Phase 13 acceptance, read on a named machine"; Seat
6 "load stays until 07d, which lands before release"; Seat 8 "provided the trigger is in 07d's scope"; Seat 7 "keeps 07c-1b within
two sessions; 07d (S–M) may split to 07d-b" (its later 1 already names the 07d-b split C9 may make likelier); nothing ties a cell to
the restore-only total, so no cell rises; C7′ max 1, sum 13. Row 14: both conditions on f in 9(a). Row 19: done (Q5). Row 22: item
6 replaces one sentence only.

## Final consolidated plan text for /fix-plan (replaces round 2's)
1. **BUILD_PLAN AX38 (i), cond. 12 (c) note:** "Cond. 12 (c) record re-instrumented in 07c-1b (D-B1 B1-b): the 05i / 07c-1 p99.9
   on a normal-priority `sleep_for` thread is the 1st–2nd largest of 953–1 936 callbacks (R16), not a host audio thread (R4, R7,
   R8); 07c-1b figures [runs]. A residual (overrun > period at 8 builders, none at 0) is re-measured in phase-13-3 scope 4 and on
   the R5 Windows release machine; a miss opens 13-1b with B1-d first; never an instance cap." + §6 row.
2. **phase-13-3 scope 4, add:** "and the 8-concurrent-builder sweep with 07c-1b's instrument (buffer 64; 0/1/2/4/8 builders;
   priority obtained and callback count printed), also on the R5 Windows release machine; a residual opens 13-1b with B1-d = a
   process-wide limit on running background builds ≤ hardware threads − 1, class (1) and offline exempt, slot taken before the gate
   and never under `stateMutex_`, `quiesce()` waking slot waiters."
3. **phase-08-4:** the AX38 (iv) binaural repeat runs 07c-1b's callback instrument in both modes in one CI run, printing callback
   count and priority obtained; re-reads the AX49 8-instance trigger on the larger (prepare-first) total (FM-10S) in the heaviest
   mode and returns it to the board if it fires.
4. **AX48, add the FM-B2 sentence:** "AX48 FM-3′ covers instance insertion, which its text does not name: a fresh instance's first
   prepare (no IrSet current, no saved state) is a keyless load of the instance's default scene. Its stage-1 (A) solve runs
   synchronously, class (1) at the AX38 gate, and its first IrSet is installed at the first partition boundary with no fade. In a
   host that prepares before restoring, this insertion cost counts in the load totals of record (h) and AX38 (iv) (FM-10S)."
   phase-07c-1b scope 6 tests: "a fresh `ScenePipeline`, no setState, prepare at 48 kHz on `medium_room`: `insertSolves == 1`, solve
   done before prepare returns; diffuse E_b bit-identical to a stage-1 solve; first IrSet at the first boundary, `fadeCount() == 0`;
   also prepare-then-setState (both VST3 orders, R17)"; "record (h) prints prepare-first totals (interleaved; batched) without a
   settle wait, beside the setState-first total". + §6 row + "Decided for Maisara" line.
5. **phase-07c-2, add:** "Instance insertion (FM-B2) takes 07c-2's stage-1 rules for statistical sources." and "The generated
   speech-like stimulus of `[ax47-midfade]` is a CI test signal only; 07c-2's self-ABX and the acceptance set use recorded speech
   (D-B3 condition A)."
6. **AX47 Measurement — replace only the sentence** "Wet pink-noise and speech renders check that no mid-fade value exceeds the
   louder endpoint." ("Every step is measured on the builder thread …" stays) with: "Wet pink-noise and seeded speech-like renders
   (D-B3: generated; seed and parameters fixed and versioned; pauses starting and ending inside a fade) check, per 1 ms window
   aligned to the fade start (N_w = lround(0.001·fs)), per output channel, E_out ≤ (1 + N_w/L)²·max(E_a, E_b)·(1 + 10⁻⁵); a
   per-sample bound |o| ≤ max(|a|,|b|) + 8u·(|a|+|b|); a reconstruction to 8u·(|a|+|b|) (detects alignment errors where
   |b−a|/(|a|+|b|) > 8u·L); value equality with the endpoint outside the fade; fades from silence |o| ≤ |b|; the load's
   equal-power fade recorded." phase-07c-1b scope 7 / AC 7: "speech" → "seeded speech-like"; phase-08-3, phase-09: "the AX47
   mid-fade check per ear / speaker feed"; public records never say "tested with speech".
7. **AX49 Reversal:** "(trigger met 2026-11-12 … to the board in 07c-1b) → moved to phase-07d by D-B4 (C7′)."
8. **phase-07d.** New criterion: "8-instance Windows load at the rated corner ≤ 5 s on record (h), read on the larger of the
   prepare-first (interleaved, batched) and setState-first totals (FM-10S), with runner label and vCPU printed (R1). AX38 (iv)'s 10 s
   line read on the same total (run 42 macOS keyed 10 206 ms; prepare-first ≈ 11.4–13.6 s est.); an exceedance after 07d goes to
   the decider for Maisara before the first release." Candidates in order: **C9** (process-wide single-flight insertion cache keyed
   by canonical scene + `tailSeed`, fs, P, `engineKey()`, platform; any scene, NFR-8; `shared_ptr<const>`; test `insertSolves +
   insertCacheHits == 1` and bit-identity; TSan with 8 concurrent insertions); **C1** (transient shared spectra cache keyed by
   filterbank + FFT size, freed when unused; AX38 (i) / (ii) accounting decided in 07d's loop; W1/W2 "no cache credit"); **C6** (as
   round 1); **C2** only on the gate's pool with C6; **C4** only as shared per-(emitter, outputIndex) unit decays, memory measured;
   **C3** only as C3-pb (L_p,b ≥ t_mix,e,max + 0.312·T60_b + 0.1 s); **C5** only with Seat 1's ABX, Seat 2's equivalence test, Seat
   9's BRAS condition, before Phase 12. Also in 07d: insertion unit decays for every outputIndex (Seat 4 (i)) — output-1 built by the
   builder after the first IrSet unless the current mode needs two outputs; whether a mode switch inside the settling window plays
   an interim, decided with Seats 3, 4 and asserted in 08-3; any remedy scales with outputs; 07d lands before 08-4 freezes goldens;
   the macOS (d) defect from D-B5 (vi) with its closure evidence (item 9 (d)); **the growth re-pin (D-B5 (ii), FM-GROWTH)** — after
   the remedy, the ratio reference and baselines re-derived from ≥ 6 green runs on the restore path in force (manual runs after 07d's
   last code change; earlier runs pooled only if 07d leaves the restore path unchanged), and the in-window absolute leg added under
   item 9 G5; the solve (iv″) exit's second branch.
9. **AX38 4c (FM-GROWTH, FM-TRIG, D-B5 (iii)–(vi)).** Replace each passage (verbatim superseded text under Q2):
   - **G1, in (b):** "… on hosted runners asserted only in the same-run ratio form below (FM-GROWTH, 2026-11-13): on Linux and
     Windows the low-α / flutter ratio every run, from the 07d re-pin also the in-window absolute leg; printed on macOS until Phase
     13".
   - **G2, in (c):** "… stays in this form (the same-run ratio on Linux and Windows, from the 07d re-pin also the in-window absolute
     leg; printed on macOS) until Phase 13".
   - **G3, Linux entry:** "Hosted-runner assertion in the 'Assertion form' below until Phase 13".
   - **G4a–c, register entries:** "now the in-window mean …" → "at RG-1 the in-window mean … ; from 07c-1b the S2 mean ('Assertion
     form')" (Linux 2 068 / 2 275, macOS 1 817 print only, Windows 2 028).
   - **G5, "Asserted every run":** "and, on Linux and Windows, the run's low-α / flutter median-of-10 ratio r ≤ 1.10 × r̄, r̄ the
     mean ratio of the ≥ 3 green S2 runs on that OS (phase-07c-1b), every run; an OS whose S2 ratios have max/min > 1.10 is
     print-only, as macOS. From the 07d re-pin also the absolute leg: median-of-10 low-α restore ≤ 1.10 × the baseline median when
     the run's flutter median f lies within ±w of its reference F̄, w the largest value with (1 + w)·max(r/r̄) ≤ 1.083 over the ≥ 6
     re-pin runs (today w ≈ 2 %); 1.10 unchanged. If those runs give max(r/r̄) ≥ 1.07 the leg is not added and stays a GROWTH
     print. Outside the window: `NOT EVALUATED (runner)`. Every GATE line prints in-window yes / no and the flutter deviation; each
     in-window evaluation prints f/F̄, r/r̄, their product and the margin to `$GITHUB_STEP_SUMMARY` or `::warning::`; §0 counts
     in-window runs per OS; if the 07d re-pin finds no in-window x64 run, the record says the absolute leg was dormant. An in-window
     or ratio red on identical code goes through (d)'s per-stage split evidence path (X-d−): never re-run until green, never
     widened. What it detects, in words: a scene-specific slowdown every run; a slowdown common to both scenes only when s_L >
     1.10·s_F, from f = [1.10(1−s_F) − (1−s_L)]/(s_L − 1.10·s_F) on the 07c-1b S2 split, value [f] (≈ ×1.28 at s_L 0.92, s_F 0.51 on
     05h code); from the 07d re-pin also uniform slowdowns from ×[computed at the re-pin] on in-window runs (≈ ×1.12–1.28 on
     upper-edge runs at ±5 %); otherwise a uniform slowdown is printed (GROWTH) and asserted only at 30 s and on the Phase 13
     release machines. If [f] > ×1.4 or s_L ≤ 1.10·s_F, the 07c-1b PR states Seat 3's later 2 until the 07d re-pin."
   - **G6, in "Printed":** "the ratio below r̄ / 1.10 (WARNING: an ISM or solve regression lowers it); on a print-only OS the ratio
     above 1.10 × r̄".
   - **G7, solve:** "`SOLVE` printed in the scene's `warnings=` when the run's solve median exceeds k × solveRefMs, solveRefMs the
     mean solve median of the S2 runs per OS and scene, k per OS the largest max / mean of those runs [values]; PROVISIONAL
     (print-only, never a (d) trigger); the same-run low-α / flutter ns-per-evaluation ratio printed every run."
   - **G8:** "A cell printing SOLVE on two runs …" ("in window" struck).
   - **G9:** "Exit from PROVISIONAL: ≥ 3 green runs on unchanged work pins (S2 or later) whose ns-per-eval ratio lies within 1.05 of
     its mean; k and solveRefMs then pinned from those runs with a CHANGELOG reason (still print-only on hosted runners); otherwise
     re-derived at the 07d re-pin; otherwise named in Phase 13 on the release machines (13-5 R5)."
   - **G10:** "the absolute low-α median above 1.10 × its S2 mean on every OS (GROWTH WARNING, to `$GITHUB_STEP_SUMMARY`, counted per
     run in §0)".
   - **G11:** "the printed growth line uses the S2 mean".
   - **G12 + G12a, Baselines:** "flutter reference, ratio reference and baseline median the mean of the ≥ 3 green S2 runs per OS
     (07c-1b, [values]); never a red run; out-of-window runs count".
   - **G13:** "the flutter window and the absolute leg re-derived at the 07d re-pin from ≥ 6 green runs (G5); the solve bound under
     G9". The rule "re-pinned only when the restore path changes … ≥ 3 runs with a CHANGELOG reason" stays; 07c-2's W_max change and
     07d's remedy are such changes.
   - **G14, Conditions J1:** append "; on hosted runners since 07c-1b the same-run ratio form, (b)".
   - **(c) macOS trigger (M-a, FM-TRIG, as written):** "On macOS two consecutive runs with the low-α median above
     kMacGrowthTriggerMs = ⌊1.15 × the mean of the green macOS low-α medians of the 07c-1b S2 runs⌋ (the 07c re-pin; computed by
     script from the GATE lines, never by hand) are a defect under (d)." Detection factor in words 1 + 0.15/s_L from the S2 split
     (≈ ×1.16 at s_L 0.92). If an S2 run exceeds the trigger it helped set, 4c and the PR say so: "the board kept her factor 1.15,
     which detects ≈ ×1.16, over a clean calibration (k ≈ 1.23) that detects only ≈ ×1.25". MACTRIGGER print or annotation only.
   - **(d) X-d−:** runs 42 and 44 recorded as "two consecutive runs over 2 172 ms, a defect under 4c (d)", remedy phase-07d, with
     medians, flutterDev and ratio; the (c) trigger applied to 42, 44 and the S2 runs, printed; the per-stage split (ISM / solve /
     synthesis + assembly; `sim::StagedBuild` replay labelled "replay") printed on every OS on the S2 runs, test-only; closure
     evidence in 07d: the macOS per-stage split after the remedy at equal work pins; the macOS / Linux per-emitter synthesis ratio
     within 1.10 × the same runs' flutter macOS / Linux ratio; the trigger in force not exceeded on two consecutive runs; built from
     runs 07d makes, ≤ 3 extra manual runs per defect; no closure by recalibration.
   - **(e) E1:** "Each `cube100_lowalpha0.05_s0.3` entry (macOS, Windows) closes under 4c (c) only if 14 × worst ≤ 30 s on every S2
     run; otherwise it stays listed, 'closes at' phase-07d (scope 1)."
   - **(f)** MACTRIGGER, OVER30S, GROWTH to `$GITHUB_STEP_SUMMARY` or `::warning::`; `pytest tools/ci` green.
   - **Also:** the public reason sentence (FM-GROWTH); the `AMENDS` line with G1–G14 listed; a §6 row; a CHANGELOG reason (scope 1).
10. **Ledger:** rows for D-B1 … D-B5, FM-B2, FM-10S (with R3), FM-GROWTH (B-iv/+07d, (iv″) + exit), FM-TRIG (amends nothing), K24
    ("MACTRIGGER fired on 42, 44, unread").
11. **phase-08-3 / 08-4 (D-B2 debt):** 08-3 asserts the first IrSet at insertion carries the per-ear seeds and decorrelation, beside
    the `[pipeline]` insertion test; 08-4 prints `insertMs` per mode (omni, binaural, stereoSpeakers) and returns it to the board if
    binaural exceeds a host or validator limit.
12. **phase-13-5 scope 3:** "The matrix's load column records instance-insertion time per host (cond. 11 trace, FM-B2); a hang,
    not-responding state or limit at insertion returns FM-B2 to the board (B2-b dry or B2-d only; B2-b silent vetoed by Seat 6)."
13. **New (FM-10S at Phase 13):** in phase-13-1 and phase-13-5, R3, append: "The recorded time is the larger of record (h)'s
    prepare-first (interleaved, batched) and setState-first totals without a settle wait (FM-10S), per instance until audible at the
    interim level ('the former', AX38 (iv) Record); 13-1 raises it on the latest CI record (07d), 13-5 on the release machines (13-2
    scope 1); the time until the final tail has settled is named as a finding if above 10 s." In phase-13-2 scope 1 append: "and
    AX38 (iv) record (h) (the totals R3 reads, FM-10S)". In the AX38 (iv) Record, after "applies the 10 s line to the former on the
    release machines", add "(read on the larger of record (h)'s prepare-first and setState-first totals, FM-10S)".

## Summary
| id | decision | state | worst-off | sum | conf. | PRD bound | corpus | reversal |
|---|---|---|---|---|---|---|---|---|
| D-B1 | B1-b | stands | S5, S7 1 now | 5 | high | FR-3D-5/6, FR-SIM-7, AX38 (i) | — | INSTRUMENT INVALID; overrun with a clean floor |
| D-B2 | B2-a″ + FM-B2 + FM-10S | revised (Q3, Q4) | S5, S8 1/1 | 8 | medium | preamble, NFR-1, NFR-6, NFR-8, AX38 (iv) | — | host limit or hang → B2-b dry / B2-d |
| D-B3 | W-a + companions; s1 | stands | S4 1 later | 1 / 0 | high (signal medium) | NFR-1, FR-SIM-6 | Vorländer §4.3 Eq. 4.15 | false red on correct code |
| D-B4 | C7′ → 07d (C9 first) | stands (corrected) | several 1 | 13 | medium | preamble, NFR-6 | — | 07d cannot reach 5 s |
| D-B5 (i) | S2 | stands | S7 1 now | 1 | high | NFR-6 | — | — |
| D-B5 (ii) | B-iv/+07d (FM-GROWTH) | revised / for Maisara | 1 (S3 2 later if f > ×1.4) | 10 (11) | medium | preamble, NFR-6, RG-F1 | — | identical-code red; 07d max(r/r̄) ≥ 1.07 |
| D-B5 (iv) | (iv″) + dated exit (FM-GROWTH) | revised / for Maisara | S2 1/1 | 5 | medium | preamble, NFR-6 | — | exit unmet at 07d |
| D-B5 (iii) | M-a + FM-TRIG | stands (corrected) | S3, S5, S6, S7 1/1 | 8 | medium | preamble, NFR-4, RG-F1 | — | weather double shown to be weather |
| D-B5 (v) | E1 | stands | S3, S6 1 later | 2 | high | preamble, NFR-6 | — | — |
| D-B5 (vi) | X-d− (+ ≤ 3 runs per defect) | stands | S3, S7 1/1 | 6 | medium | preamble | — | 07d evidence |

Challenges to settled decisions: none.

## Decided for Maisara
- **FM-B2** — a newly added instance computes its default room in full before it plays (0.15–0.43 s), never silent or dry;
  preamble, NFR-1, NFR-8, a scope reading of AX48 FM-3′; Seats 5, 8 gave most, get the cost counted at load, C9 first in 07d, checks
  in 08-4 and the 13-5 matrix; amends nothing.
- **FM-10S** — the 10 s load line counts the slower host call order everywhere it is read, incl. Phase 13 R3 on the release
  machines; AX38 (iv) and its Record, preamble, NFR-6; amends nothing.
- **FM-GROWTH** — restore growth judged on Linux and Windows by the within-run low-α / flutter ratio at 1.10; the absolute 1.10
  bound returns at 07d, sized from ≥ 6 runs so it cannot fire on unchanged code, and again on the Phase 13 release machines; solve
  baselines provisional until a dated exit; preamble, NFR-6, RG-F1; Seat 3 gave most (weaker uniform detection until 07d), gets the
  absolute leg back at 07d; `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (G1–G14 of AX38 4c,
  verbatim).
- **FM-TRIG** — the macOS trigger keeps her 1.15 ×, over all green re-pin runs; preamble, NFR-4; amends nothing.
- **D-B1, D-B3, D-B4, D-B5 (i), (v), (vi)** — measure the deadline properly first; 1 ms windows + exact reconstruction on a fixed,
  named speech-like test signal; the 8-stem load fix to 07d, slower host order counted, hard line before release; fresh baseline
  runs; register entries close only when every run passes; the fired macOS trigger a 07d defect closing only on measured evidence
  (≤ 3 extra runs); preamble, NFR-1, NFR-6, FR-SIM-6.

NEEDS MAISARA: none new (FM-D1-S3 already with her). If round 3's check fails on Q1 or Q2, those go to her as case (a), with each
side's last word under Q2; recommendation B-iv/+07d.
