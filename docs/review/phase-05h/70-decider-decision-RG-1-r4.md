# 70 — Decider: DECISION RG-1, round 4 (answers interrogator file 69): the macOS trigger armed at 2 172 ms (Seat 5's alternative); (c) never re-arms the strict branch

phase-05h (session 2). Verbatim decider output (the orchestrator saved it).

# Decider — DECISION RG-1, round 4 (interrogator file 69). **State: revised; stands** (max 1, sum 9).

## Item 1 — the macOS trigger, composed from Seats 5 and 6's own alternatives
Two forms were on the table:
- **T1: print until the 07c re-pin, armed after** — Seat 5 0 / 1, Seat 6 0 / 0, but Seat 3 (file 58 r3): "otherwise macOS carries no synthesis detector until Phase 13 and my later rating returns to 2" (07c moves the synthesis anyway, so a detector armed after 07c is none) → max **2**.
- **T2: armed now at Seat 5's alternative line** — "bound 1.15 × mean of in-window medians (1 889 → 2 172 ms): 0 of 4 rows over, double rate ≈ 0 on file. Then 0 / 1 holds" (file 57 r3) → max **1**.

**Chosen: T2.** Trigger: two consecutive macOS runs with the low-α median > **2 172 ms** (`kMacGrowthTriggerMs`, provenance: Seat 5 r3, 1.15 × 1 889, the mean of all four measured macOS low-α medians, 2 106 / 1 849 / 1 887 / 1 715; ≈ 1.20 × the in-window print baseline 1 817, which stays the printed GROWTH line). 0 of 4 rows over; the 2 106 row (the ×1.23 weather case) does not fire. Re-derived with the baselines at the 07c re-pin (≥ 3 in-window runs).

| seat | cell on T2 | words |
|---|---|---|
| 5 | 0 / 1 | own: "Alternative if the decider wants it armed now: bound 1.15 × … 2 172 ms … Then 0 / 1 holds" |
| 6 | 0 / 1 | own: armed now "I price it later 1, not 2 … it buys nothing"; 0 / 0 only "armed only after the 07c re-pin" |
| 3 | 1 / 1 *(read from c2: a macOS synthesis detector before Phase 13 exists; at 2 172 it fires at a uniform synthesis slowdown ≈ ×1.2, 0.92 share)* | r3/r4: "holds at 1 / 1 … No new condition"; its 2 was for "no synthesis detector until Phase 13" |
| 2 | 1 / 1 | "(f) 1 with the pin" |
| 7 | 1 / 1 | r2 "unchanged"; a false (d) edit "costs half a session", now 0 of 4 on file |
| 1, 4, 8, 9 | 0 / 0 | not required |

Worst-off: T2 max 1 < T1 max 2. Sum T2 = 0+1 + 0+1 + 1+1 + 1+1 + 1+1 = **9** (< (b)-conditioned 10). One composition this round. If the interrogator wants Seat 3's cell own rather than read: **CONVENE Seat 3, one line:** "macOS trigger armed now at 2 172 ms (two consecutive; fires at ≈ ×1.2 uniform synthesis), not 1 999 ms: does 1 / 1 hold?"

## Item 2 — (c)'s removal must not re-arm the strict branch: accepted
Sentence (verbatim, placed in the FOR MAISARA text after "leaves the register through `/fix-plan`" and in phase-05i scope 3 (ii) after "before 05i is `done` (§5 (c))"): "its register text closes; the low-α scene's hosted-runner assertion stays in this form (in-window on Linux and Windows, printed on macOS) until Phase 13; the strict 30 s branch applies to the flutter scene, and to the low-α scene only on the release machines." Test: the `strict30s` field (true on the flutter entries only) carries it; an entry leaving the register keeps `strict30s = false`; `listed` governs the print text only.

For the record: CI run 42954077281 (b83c49d, pre-RG-1 form) green on three OSes; it changes nothing (2 of the previous 5 runs red on identical code).

## FOR MAISARA RG-F1 (final plan text; phase-05h §5 "Blocking" (a)–(d) and AX38 4c's register paragraph)
As file 66/68, with these sentences final:
- macOS: "On macOS two consecutive runs with the low-α median above 2 172 ms (1.15 × the mean of the four measured macOS medians; re-derived at the 07c re-pin) are a defect under (d), remedy named, through `/fix-plan`; the 30 s warning on a listed entry is its recorded state until phase-07c, not a trigger; the printed growth line uses the in-window baseline 1 817 ms."
- (c): "A listed entry whose printed 14 × worst passes 30 s is a job-log warning and leaves the register through `/fix-plan` before the next phase is `done`; its register text closes; the low-α scene's hosted-runner assertion stays in this form (in-window on Linux and Windows, printed on macOS) until Phase 13; the strict 30 s branch applies to the flutter scene, and to the low-α scene only on the release machines."
- (d): "A broken assertion, or the macOS trigger, is a defect: no re-run, no W_max cut, no range change, no seam; remedy phase-07c conditions 9–10 through `/fix-plan`."
Everything else (work pins W / length / FFT n; flutter 30 s strict; low-α 1.10 in a ±5 % flutter window on Linux and Windows; ratio, solve median, 30 s, macOS printed with WARNING; mean baselines 701 / 737 / 484, 3.05 / 2.83 / 3.75, 2 068 / 2 028 / 1 817 with the run lists; PROVISIONAL / ≥ 3-run re-pin; `if: always()`; Phase 13 strict; 07c split-timer packet) unchanged. Amended texts: AQ10 amended (1), AX38 4c, phase-05h §5, **phase-05i scope 3 (file 68's text plus the item-2 sentence in (ii) and the 2 172 ms line in (iii))**, phase-07c condition 9 packet, phase-13, AX41. PRD ids (L101, NFR-2, NFR-4 "macOS and Windows", NFR-1, NFR-6, L20; CLAUDE.md step 6), the option lines ((x‴), (a), (b), (c), (e), (g), (d)) and the veto line: as file 66.
`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`

## Test form and CI (final)
As in the tree (constants L83–88, pins, solve timer, GATE lines, guarded REQUIRE; `strict30s` on the flutter entries only; ci.yml L427/L437 `if: always()`), plus the constant `kMacGrowthTriggerMs = 2172` with its provenance comment, printed on the macOS GATE line as `trigger=2172`; the two-consecutive rule is read by the orchestrator from the §0 count against that line, not 1 999. Nits as file 68.

## Future-debt register (x‴, T2)
| seat | commits later phases to | undoing costs | evidence | repaid when |
|---|---|---|---|---|
| 5 (later 1) | a record that must be read; strict re-enforcement on release machines; the 2 172 line re-derived at 07c | flag flip; one constant | Phase 13; 07c re-pin | Phase 13 |
| 6 (later 1) | a trigger armed on n = 4 data that could label weather a defect (0 of 4 on file); the §0 explanation in plain words | one constant (disarm) | §0 counts to 07c | 07c re-pin |
| 3 (later 1) | uniform synthesis slowdown < ≈ ×1.2 on macOS / ≈ ×1.65 in the ratio reaches hosted CI as a warning; solve bound after ≥ 3 runs; 07c sizes on the split-timer packet | — | 07c packet; 3 runs | 07c |
| 2 (later 1) | a per-op slowdown or an added pass at unchanged length / n invisible until Phase 13; re-pin at 07c | one constant + CHANGELOG | 07c; Phase 13 | 07c / Phase 13 |
| 7 (later 1) | the in-window 1.10 at n = 2 until 07c; release machines bought once | — | 07c re-pin; Phase 13 | Phase 13 |

**Strongest objection:** Seat 6's later 1 ("buys nothing": the macOS entry already carries the same remedy). It holds because the trigger is the only macOS synthesis detector before Phase 13 (Seat 3's 2 otherwise), fires 0 of 4 on file, and costs one constant to disarm. **Confidence:** medium (Seat 3's cell read; n = 4). **Reversal:** a macOS double on identical code before 07c (disarm, T1); the 07c re-pin; Phase 13's run.

**Summary:** `RG-1 | (x‴) with the macOS trigger armed at 2 172 ms, (c) no re-arm of the strict branch | revised, stands | Seats 2, 3, 7 (1 / 1) | 9 | medium | L101/NFR-2, NFR-4, NFR-1, (v)(d) | none needed | macOS double on identical code; 07c re-pin; Phase 13 run`

**Decided for Maisara.** RG-F1: on shared CI machines the gate judges the work exactly and the restore's growth only when the machine is at normal speed; the rest is printed with a warning and counted; on macOS two runs in a row above 2 172 ms count as a defect; an entry that passes 30 s leaves the register without bringing the strict check back on shared machines; the strict 30 s is judged on the release machines at Phase 13 (L101, NFR-2, NFR-4, NFR-1). Seat 6 and Seat 3 gave the most (a trigger on thin data; a weaker detector than wanted) and get the 07c re-pin, the split-timer packet and the Phase 13 strict check back. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` **NEEDS MAISARA:** none.

Files: /home/user/makroof/docs/review/phase-05h/69-interrogator-RG-1-r3.md, /home/user/makroof/docs/review/phase-05h/57-seat5-restore-gate-runner-variance.md (round 3), /home/user/makroof/docs/review/phase-05h/61-seat6-restore-gate-runner-variance.md (round 2), /home/user/makroof/docs/review/phase-05h/58-seat3-restore-gate-runner-variance.md (rounds 3–4), /home/user/makroof/tests/unit/test_diffuse_records.cpp L443–462.
