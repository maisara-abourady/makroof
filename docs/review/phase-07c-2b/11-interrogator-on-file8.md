# Interrogator round 3 on `docs/review/phase-07c-2b/8-decider-scene.md`

The scene choice holds: `layout5_s0.9/emitter_wall` (V6-E) wins correctly. M3-T fails because Seat 1 was not heard on the speech pair, and the L4 CONVENE leaves out Seat 6. M3-S, M3-G, M3-C and M3-F survive with corrections.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Read:**
- Decider file 8 and seat files 7-seat{1,2,3,4,7,9}.
- Builder file 4: Tables 1 and 4 (L49–111) and facts 1–13 (L189–304).
- `tools/ci/abx_kit.py` speech programme (L736–815).
- `src/sim/Engine.h` L298, `src/sim/Engine.cpp` L1003, `ScenePipeline.cpp` L656/L704, `tests/unit/test_interim.cpp`.
- BUILD_PLAN AX49 (L172).
- Kuttruff §2 Eq. 2.50 (L1542–1552), §5.6–5.7 and Table 5.2 (L2782–2796).

## Rulings

| item | ruling |
|---|---|
| M3-S (scene V6-E, item 15, n = 2) | **SURVIVES WITH CORRECTIONS** |
| M3-G (gap rule, an M2 re-decision) | **SURVIVES WITH CORRECTIONS** |
| M3-C (conditions adopted) | **SURVIVES WITH CORRECTIONS** |
| M3-F (AX47 /fix-plan) | **SURVIVES WITH CORRECTIONS** |
| M3-T (TSP MA01_01 + MA01_02) | **FAILS**: UNDERCONVENED (Seat 1), and one claim is WRONG |
| AX49 L4 CONVENE | **Not sound as written**: UNDERCONVENED (Seat 6). Seats 4 and 8 are correctly not required. |

### Convening
- **Seats 5 and 6 not re-convened for M3-S: correct.** Both rated unsplit with at most 3 families at 1/1, and Seat 6 said "If the decider counts 08-3 differently, my ranking stays the same". Going down to 2 families only lowers the union rate.
- **Seat 8:** not required, as in file 31. Correct.
- **M3-T: UNDERCONVENED (Seat 1).** The speech material is the blind-test signal under item 8, which is Seat 1's row ("blind-test paradigm, listeners, signal"). Seat 1 was not asked in round 2. The decider decides first and asks Seat 1 to "object or accept" afterwards. The decision has to wait for Seat 1's rating.
- **L4: UNDERCONVENED (Seat 6).**
  - AX49's provisional is what every user hears at project load: "Every load of a scene with a tail therefore starts with a tail", and it hands over to the exact tail with a crossfade.
  - L4 tests whether that handover cut is audible. Option L-c defers that evidence.
  - Seat 6's row covers "time-to-first-plausible-scene" and anything user-facing. Its W4 concern, "an automatic jump after the user has stopped", is the same failure mode.
  - Decider §2 says to convene a PRD-priority seat whenever the matter touches what the user hears. "No user control" does not exclude Seat 6.
  - Seat 4 (omni, diotic) and Seat 8 are correctly not required.

### Tension map (step 2)
- I checked every scene cell against the seats' words. **Faithful.** That includes the cells marked "c":
  - S3: "1/1 c … Depends on M2 being re-decided"; the condition is met by M3-G.
  - S7: E is "2 as measured" later, "2 → 1" under the gap fix and re-measure; met by M3-G's C4.
  - S9: "1/1 only with condition C-a"; met.
  - S4: E later "2 → 1 under L5"; met by M3-C 3.
  - S2: "1 under C2′+C4"; met by M3-C 1 and the re-measure.
  - S1: "0/0" under the max rule with Δ; met.
- **Sums recomputed:** E 13, D 14, B 15, both_wall 15.
- **Item 15 dropping S-B\*** is the decider's own composition. I found no seat reason that it raises a cell:
  - Seat 1 kept S-B\* only "where it serves Seats 3 and 9".
  - Seat 9's V6 later 1 rests on O10 being read from a scene with a filled early part, which E has (−8.6 dB).
  - Seat 4 rated "layout 5 in item 15, in with L5: 0/1".
- **D-M3d (S-B\* = s 0.7)** is now dormant. Say so in the record.

### Ordering (step 4)
- listener_wall is vetoed (Seat 1 later 3).
- E, D and B have a maximum of 1; all other survivors have 2.
- On sum, E 13 is below D 14 and B 15. **E is correct.**
- A composed B with Seat 1's condition ("run a late-dominated scene with share ≥ 0.6 at 08-3") could also reach 13. Step 4 does not require it, because the maximum is already 1, so this is not an error.
- The strongest objection says "B would win if Seat 1 re-rated E above 0/0". That is IMPRECISE. If E rose by 1, D (14) would tie or lead. B leads only if both emitter_wall scenes fail C4.

### Load-bearing claims
- **K19 and M3S-L1: CORRECT** (file 4 row 53, row 101, facts 3 and 13).
  - Capped at m = 6, 7 and 8; peak −8.0 to −4.8 dBFS; heard D/R −9.5 dB; share 0.852; ΔG 0.778 dB.
  - Early part −8.6 dB; specular share 0.022/0.001; s_w 7.3e−7 (5.2e−5 in the worst band).
  - Heard T30 2.560 s; tail T30 2.582/2.600 s; Q5 window [0.013, 0.380]; 2.39 h; item 6 ≤ 8.8e−4 dB.
- **M3S-L2: CORRECT.**
  - S0 is at √(9 + 479.61 + 0.09) = 22.11 m.
  - r_c = √(343/16π) = 2.612 m, so 8.46 → −18.6 dB and 4.74 → −13.5 dB.
  - Δ = 9.74/343 = 28.4 ms.
  - ᾱ = 319/2200 = 0.145.
- **Label combs: CORRECT.**
  - The specular amplitude is √(0.99 × 0.1) = 0.315, giving +2.4/−3.3 dB at the wall image (0.583 ms, 857 Hz).
  - The floor image for S1 is 0.538 m longer (1.57 ms, 318 Hz), giving +2.3/−3.1 dB.
  - **IMPRECISE:** S0's own floor image arrives 0.31 m (0.89 ms, notch ≈ 560 Hz) after its direct sound. It also falls inside the ±2.5 ms direct window, and the label leaves it out.
- **M3S-L3 / K20: CORRECT.** Kuttruff §5.7 Table 5.2: 3.06/2.99 = +2.3 %; 1.21/1.38 = −12.3 %.
- **M3-C 9, "the engine's Eyring tail runs ≈ 14 % long", is IMPRECISE.**
  - 1.38/1.21 = 1.14 holds for case 4 (others at α 0, diffusely reflecting walls).
  - Applying it to layout 4 (α 0.01 plus air, Eyring 1.291 s) is an inference. Seat 9 tags it "[Inf; M]". Write it as an inference.
- **K21: CORRECT.**
  - Kuttruff §2 Eq. 2.50 gives |p|²_av ∝ 1 + sin(2kx)/(2kx).
  - At x = 0.1 m: +2.93 dB at 125 Hz, +1.84 dB at 500 Hz, −0.64 dB at 1 kHz. This matches Seat 4.
- **K22: CORRECT** (file 4 fact 7: emitter_wall's heard gap from burst 1 to burst 2 is 2.574 s against 2.600 s).
- **K23: IMPRECISE.** `assembleProvisional` is also called from `tests/unit/test_interim.cpp`, not only from `src/plugin/core`. That matters for L4: L-b already has a test-side precedent.
- **M3S-L4: the bound holds, but the working is IMPRECISE.**
  - Sentence 2 starts at s1_end + ⌈(0.43·T_h + T)·fs⌉ + Δ, its earliest heard start adds min d, and the onset is at most eos + 0.43·T_h·fs, with eos ≤ s1_end.
  - So the silence after the onset is at least T·fs + Δ + min d, which is at least T·fs. The decider's "− max d" term does not belong.
- **M3S-L5: CORRECT.** 2 × 0.049 = 0.098, and 1 − 0.951² = 0.0956.
- **M3-G "cost on E: about +1.1 s per speech stimulus": IMPRECISE.**
  - The new pause is 0.43 × 2.560 + 2.600 + 0.0284 = 3.729 s, against the kit's ceil(T_heard) = 2.560 s.
  - That is +1.17 s, so about +1.2 s.
  - Over 44 trials at 5 plays this adds about 0.08 h to the 2.39 h, which the adopted K6 redo should carry.
- **M3-G noise check on E:**
  - T = 2.600 s and Δ = 1363 samples, so G = ⌈126163/512⌉ × 512 = 126464 samples.
  - The heard gap is 125101 samples, 2.606 s, at least 2.600 s. **CORRECT.**
- **"On layout 4 the max rule changes nothing": CORRECT for the measured set** (file 4 Table 1: heard T30 ≥ tail T30 on every layout-4 row).
- **M3-T, "passes … the nulls on all 16 scenes": WRONG for B.**
  - File 4 fact 5 nulls B on the 160 noise stimuli only. E is nulled on speech ("−130.0 dB or better on the speech stimuli").
  - Seat 3 (7-seat3 §5): "B was not nulled on the speech stimuli".
  - The ≥ 20 dB assertion and form (b) on speech are CORRECT (facts 4 and 9).

### Debt register (step 3)
- Every later cell of 1 or more on E has a row: Seats 2, 3, 4, 5, 6, 7 and 9.
- Every "repaid when" names a phase that exists (05d, 08-3, 08-4, O10/O4).
- Seat 7's undo cost is now honest. **Faithful.**
- **M3-C 8:** "Seat 7's 'rises to 2' trigger is met" should read "is avoided". Seat 7 said its rating becomes 2 if the confirmatory ABX "is allowed to fall after the 08-4 freeze".

### PRD proxy (step 8a)
- **M3-S "Decided for Maisara": PRD MISREAD.** Several surviving options are not shown against NFR-1, NFR-8 and L101: D (s0.8/emitter_wall, max 1), layout4_s0.7/both_wall, layout5_s0.9/default and V3′. Decider §1a requires one line each.
- **The same line is IMPRECISE in two places.**
  - "with real early reflections": the early part is specular only, and the label itself says "specular-only".
  - "the hardest scene that qualifies": V3's layout5_s1/emitter_wall has ΔG 0.792 dB against E's 0.778 (Seat 1: "0.014 dB below the maximum"). E is the hardest **s < 1** scene that qualifies.
- **M3-G "every silence is at least …": IMPRECISE.** The lead-in silence is 8 to 39 partitions (0.085–0.416 s), which is shorter than T. Restate as "every gap and pause, and the silence after the step".
- **M3-C and M3-F:** the NFR-1/NFR-8 readings are fine.

### M3-F
- The AX47 edit and the extra homes are consistent.
- It omits where M3-G's re-decision of M2 is recorded: the run sheet's gap and pause construction, the phase-07c-2b scope 2 "M2 debt checks" text, and file 34 item 3.
- It also omits where the held file-13 amendments are recorded: item 9's new scene and item 15's new text.
- Add both to the apply list.

## Corrections to apply
1. **M3-S:**
   - Add Decided-for-Maisara lines for D, both_wall, layout5_s0.9/default and V3′.
   - "real early reflections" → "specular-only early reflections".
   - "hardest scene that qualifies" → "hardest s < 1 scene that qualifies (0.014 dB under V3's s = 1 scene)".
   - Strongest objection: D comes next, not B.
   - Optional: add S0's floor-image line (0.89 ms) to the label.
   - Record D-M3d as dormant.
2. **M3-G:**
   - Restate M3S-L4 as "≥ T·fs + Δ + min d ≥ T·fs".
   - "+1.1 s" → "about +1.2 s".
   - The K6 redo includes the longer pause.
   - Plain-language line: "every gap and pause, and the silence after the step".
3. **M3-C:**
   - Item 8: "trigger avoided".
   - Item 9: mark the 14 % as an inference from case 4 (others at α 0).
4. **M3-F:** list the homes for M3-G and for the item-9 and item-15 amendments.
5. **M3-T:**
   - Withdraw it until Seat 1 rates it.
   - Restate "the nulls" as "E nulled on speech; B nulled on noise only".
   - Seat 3's pre-seal condition (B nulled on speech) is still open.
6. **L4:**
   - Convene Seat 6.
   - Restate K23 to include `tests/unit/test_interim.cpp`.

## Ledger rows
| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| M3-S | convening | Seats 5/6 not re-convened (n 3 → 2) | correct | 1-seat5 §2, 1-seat6 §1 | — | — |
| M3-S | map | all cells incl. c | faithful | 7-seat{1,2,3,4,7,9} §3–6 | — | — |
| M3-S | ordering | E 13 < D 14 < B 15 | correct | sums recomputed | — | — |
| M3-S | ordering | strongest objection: "B would win" | IMPRECISE | D next at 14 | SWC | — |
| M3-S | claim K19/L1 | E measurements | CORRECT | file 4 row 53, row 101, facts 3, 13 | — | — |
| M3-S | claim L2 | r_c, D/R, Δ, ᾱ | CORRECT | Kuttruff §5.6 Eq. 5.44; arithmetic | — | — |
| M3-S | label | combs 860/320 Hz and depths | CORRECT; S0 floor image at 0.89 ms omitted (IMPRECISE) | geometry | SWC | — |
| M3-S | PRD proxy | surviving options not shown; "real early reflections"; "hardest that qualifies" | PRD MISREAD / IMPRECISE | decider §1a; Seat 1 table | SWC | add lines |
| M3-G | claim L4 | silence after onset ≥ T | CORRECT bound, IMPRECISE working | derivation above | SWC | — |
| M3-G | claim | +1.1 s | IMPRECISE (+1.17 s) | 0.43·2.560 + 2.600 + 0.028 − 2.560 | SWC | — |
| M3-G | claim | E noise gap 126464, heard 2.606 ≥ 2.600 s | CORRECT | construction | — | — |
| M3-G | PRD | "every silence" | IMPRECISE | lead-in 0.085–0.416 s | SWC | — |
| M3-C | claim K21 | Eq. 2.50 rise | CORRECT | Kuttruff §2 Eq. 2.50 | — | — |
| M3-C | claim | case-4 label line | CORRECT | Kuttruff §5.7 Table 5.2 | — | — |
| M3-C | claim | engine ≈ 14 % long | IMPRECISE (conditions) | case 4 at α 0; layout 4 by inference | SWC | — |
| M3-C | debt | "trigger is met" | IMPRECISE (avoided) | 7-seat7 §4 | SWC | — |
| M3-F | completeness | homes for M3-G and items 9/15 | incomplete | phase-07c-2b scope 2 | SWC | — |
| M3-T | convening | Seat 1 not heard on item-8 signal | UNDERCONVENED | README Seat 1 row; file 8 L185 | FAILS (waits) | — |
| M3-T | claim | "the nulls on all 16 scenes" | WRONG for B on speech | file 4 fact 5; 7-seat3 §5 | FAILS | — |
| L4 | convening | Seat 6 not required ("No user control") | UNDERCONVENED | AX49 L172 (load-time provisional, handover); README Seat 6 row | redo CONVENE | — |
| L4 | claim K23 | called only from src/plugin/core | IMPRECISE | tests/unit/test_interim.cpp | SWC | — |
| L4 | knowledge | K24 under-informed → CONVENE | correct | AX49 L_p example only for the gated geometry | — | — |
