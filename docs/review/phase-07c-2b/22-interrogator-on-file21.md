# Interrogator on decider file 21 (P8 item 3, P8-S, the O1/O2/O4 deferral, D1 corrections) and builder file 15 (commit e4c34ac)

Everything in file 21 stands; P8-S needs two wording corrections. Builder file 15 is faithful to L4-P apart from three narrow points: the test-2 allow-list was widened to all of `tests/unit/`, test 3 changed form, and L moved from 12.0 s to 11.993 s.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**What I read:**
- `docs/review/phase-07c-2b/21-decider-p8.md`, `19-seat7-p8.md`, `20-seat3-p8.md` and `15-builder-provisional-flag.md`.
- From commit e4c34ac's tree: `tools/ci/test_provisional_flag.py` (L57–101, L191–311), `tests/unit/test_cli_provisional.cpp` (L104–169) and `tools/ci/ci_fingerprint.py`.
- Earlier rulings: my file 18; file 10 L4-P and L4-S; file 13 (r5, tests 3 and 8); file 14 (Seat 5's conditions).

I have no shell, so I read the code; I did not run it.

## Rulings

| id | ruling |
|---|---|
| **P8-3** (item 3 plus O5) | **SURVIVES** |
| **P8-S** (replacement clause) | **SURVIVES WITH CORRECTIONS** |
| **Deferral of O1/O2/O4 to 07d's board round** | **sound** |
| **D1 corrections** (hours; map) | **SURVIVES**: both file-18 corrections are closed |
| **Builder file 15 / e4c34ac** | faithful, with three departures (B1–B3 below) |

### Convening
- File 18 asked for Seats 3 and 7; both answered.
- Not convening Seats 1, 2 and 5 for O1, O2 and O4 is sound, because those options are not decided here.
- One gap: Seat 7's hand-off "Whether a provisional-then-confirm ordering is valid for the reversal: Seat 1" (19-seat7 §7) is not carried into 07d's input list.
- This is **not UNDERCONVENED** for P8-S. Seat 1's own condition L-c1 (9-seat1-l4: "07d cannot decide AX49's remedy or reach `done` without the L4 result") is met: 07d decides with 07c-2b's L4 result in hand, and cannot reach `done` without the confirming L4.

### Tension map against the seats' words
- **Item 3 with O5:** S3 0/1, S7 0/1, matching 20-seat3 and 19-seat7 ("Item 3 void: 0 … later 1"). Faithful.
- **Clause as written:** S3 1/2, S7 1/2. Faithful.
- **Composed rule:**
  - S3 ≤1/1 c follows from Seat 3's condition: "drops to 1 only with O3 alone". O3 is in P8-S.
  - S7 1/1 c follows from Seat 7's conditions 1–3, all in P8-S.
- **Ordering:** the composed rule is the only option at a maximum of 1 that both seats rated. Correct.

### P8-3
- The trigger rests on L_f = t_mix,e,max + 0.312·T60_max (AX49) and on the fade and normalisation that define A. Seat 3: "Change any of them and the sealed A is no longer what the plugin plays". CORRECT.
- O5 (the manifest prints f, the fade, the normalisation and L's rule) is Seat 3's only condition. It is adopted.

### P8-S: corrections
1. **The freeze date covers only the first 07d session.**
   - Seat 7's condition 3: "Dated before the 08-4 freeze … If the date can fall after the freeze, the rating becomes 3."
   - P8-S dates only "the 07d L4 session". A detection there sends the remedy back to the board, which runs "one L4 session per board round", and those later sessions are undated.
   - Read against Seat 7's words, an undated later session puts its cell at 3.
   - **Correction:** "every 07d L4 session, including those after a detection, is dated before the 08-4 freeze". Alternatively, ask Seat 7 whether its condition covers only the first session.
2. **Seat 7's hand-off to Seat 1 is not recorded.** List it with O1, O2 and O4 as an input to 07d's round, which convenes Seat 1 anyway for O4's α.

The rest of P8-S is faithful:
- one session per decision point, with intervening changes collapsing into it (Seat 7 condition 1);
- provisional decision, rebuild, L4 before `done`, return to the board with Seat 3 if detected (Seat 3's O3; Seat 7 condition 2);
- voids under items 1–4 force a reseal only.

It also removes file 18's INCONSISTENT finding: an ordering that 07d could not satisfy for its own remedy.

### Deferral of O1/O2/O4
- Each needs a seat not convened here: Seat 1 for the α across a candidate sequence, Seat 5 for the override guard, Seat 2 for L_p per candidate. O1 also needs flags that do not exist yet.
- Seat 3's own fallback ("1 only with O3 alone") covers the gap.
- The debt row (an extra board round if the provisional remedy is detected) and the strongest objection record the cost.
- **Sound.**

### D1 corrections
- **Hours:** Seat 7's three file-19 conditions are taken over word for word: the worst case (E's sitting 2 + L4 primary + L4 rerun), the third-sitting decision made before the seal, and a rerun opening the next sitting.
- **Map:**
  - (a): S1 ≤1 c, S6 ≤1 c, S7 1/1 ("D1 rerun: 1 … 1").
  - (b): later 2 for S1 c and S6 c (by analogy with their L-c reasons), and for S7 (file 19: "rated later 2 under L-c's reasons").
  - (a) wins on the maximum.
- Closed.

### Builder file 15 (e4c34ac) against L4-P, file 13 and file 14
**Faithful:**
- **Flag semantics:** the keyless-load sequence solve → `useUnitDecays(nullptr)` → `useDiffuseLevel` → `assembleProvisional` matches test 7's parity.
- **r1** is decided from `provisionalTiming()` before any output file is opened. This meets file 14 (a), and test 6 asserts that no file is left behind (file 14 (b)).
- **r3** adds `--abx-step-sample`, which is harmless.
- **r5** mirrors `--abx-step-sample` (multiple of the partition and of the block, at least one partition, inside the input), meeting file 13's correction.
- **The handover** goes through `RealtimeEngine::submitIrSet` with `EqualGain`. The request is at N − P, so the fade starts at N (file 14 (i)–(ii)).
- **Test 8:**
  - before N, bit-identical to the provisional real-time render;
  - from N + ⌈0.030·fs⌉ = N + 1440, bit-identical to the default real-time render;
  - the mid-fade checks pass.
  - This meets file 13 and file 14 (iii).
- **Measured timing:**
  - t_mix,e,max 0.08017 s, L_f 2.5748 s, L_p 2.6748 s.
  - These sit above K27's bounds of 64.7 ms, 2.561 s and 2.661 s.
  - L_p = L_f + 0.1 holds exactly.
- **k = 0.84:** T60_max 7.9955 s lies within 8.0 ± 0.1 s.
  - The rule was "start 0.844, adjust until … ± 0.1 s; k recorded", so the choice is inside the rule.
  - The builder notes that K27's 8.00 s left out air absorption at 63 Hz. That is consistent with my file 13, which rated K27 "known as bounds; measured".
- **H** = max(2.675, 0.5 × 7.9955) = 3.998 s, i.e. 4 s.

**B1. Test 2's allow-list was widened (departure, minor).**
- File 10 allows the flag strings only in "Cli.cpp, its tests, abx_kit.py, listening_pack.py, tools/ci/test_*.py, docs/".
- `_allowed()` (test_provisional_flag.py L80–85) also allows all of `tests/unit/` and every `*.md` file.
- The Engine.h comment-line exemption is required by L4-P's mandated comment. Allowing prose (`*.md`) is harmless.
- **But the whole of `tests/unit/` is wider than "its tests"**, and that tree holds golden-producing and golden-asserting code (the `[.generate-state-fixtures]` generator, the D5 golden assertions).
- Seat 1's L-a1 condition and test 2's purpose are that no golden path ever names the flag.
- **Correction:** narrow the exemption to the flag's own test files (`test_cli_provisional.cpp`, plus `test_cli.cpp` if it names the flag).

**B2. Test 3 changed form (departure, acceptable as an equivalent, Seat 5 to confirm).**
- File 14 asked for "a SHA-256 per OS, or a comparison with and without the flag on each runner".
- The implementation:
  - pytest prints the per-OS SHA without pinning it, and asserts it equal run to run and with `--images` added;
  - the C++ half (test_cli_provisional.cpp L153–167) asserts that the default `render_cli --mode omni --ir` output on medium_room is bit-identical to `sim::buildRoomIR` in-process, on each runner.
- The C++ comparison does detect the provisional path leaking into the default output, on every OS, without a cross-OS pin.
- Record it as the chosen form, and have Seat 5 confirm it meets its condition (its stated risk was a cross-OS pin).

**B3. L is 11.993 s, not 12.0 s (minor; plan text).**
- At k = 0.84, L = min(1.5 × 7.9955, 12) = 11.993 s, so the cap is not reached.
- Run sheet §8 detail line 4 states "L (12.0 s)". It should say **[measured at build]** (11.993 s at k = 0.84).
- L4-D's "silence after the release ≥ L + 0.5 s" is unaffected.

**Open, not a departure:** the L4 scene is built from stone_box.json and k in the tests, not committed as a fixture. The builder gives a reason (it would join `ALL_FIXTURES` and need a new golden). L4-S still requires "the scene JSON and its SHA-256 committed with the kit"; that falls due when `abx_kit.py` gains L4, which e4c34ac does not touch.

## Ledger
| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| P8-3 | map | item 3 + O5: S3 0/1, S7 0/1 | faithful | 20-seat3 §3–4; 19-seat7 §3–4 | SURVIVES | — |
| P8-3 | claim | constants define A and L_f | CORRECT | AX49 L172; 20-seat3 §2 | — | — |
| P8-S | map | composed rule: S3 ≤1/1 c, S7 1/1 c | faithful | Seat 3 §6 (O3 alone); Seat 7 §6 conditions 1–3 | — | — |
| P8-S | condition | freeze date covers only the first 07d session | IMPRECISE: Seat 7's "rating becomes 3" is open for later rounds | 19-seat7 §6 condition 3 | SWC | date every 07d L4 session before 08-4, or ask Seat 7 |
| P8-S | hand-off | Seat 7 → Seat 1: validity of provisional-then-confirm | not carried | 19-seat7 §7 | SWC | add it to 07d's input list |
| P8-S | convening | Seat 1 not needed now | sound (L-c1 met) | 9-seat1-l4 L-c1 | — | — |
| deferral | ordering | O1/O2/O4 to 07d's round | sound | they need Seats 1, 2, 5; Seat 3's O3-alone fallback | — | — |
| D1 | correction | hours in L4-T's K6 redo (worst case) | closed | 19-seat7 §6 | SURVIVES | — |
| D1 | correction | (a)/(b) map rows | closed | 19-seat7; 9-seat1/6-l4 L-c | SURVIVES | — |
| e4c34ac | test 2 | allow-list includes all of `tests/unit/` | departure (minor) | test_provisional_flag.py L80–85; file 10 test 2 | fix | narrow to the flag's own tests |
| e4c34ac | test 3 | per-OS print + C++ default-vs-`buildRoomIR` identity | acceptable equivalent | test_cli_provisional.cpp L153–167; file 14 §3 | Seat 5 to confirm | — |
| e4c34ac | r1, r3, r5, handover, test 8 | as L4-P, file 13, file 14 | faithful | builder file 15; Cli.cpp | — | — |
| e4c34ac | k, timing | k 0.84 → T60_max 7.9955 s; L_f 2.5748; L_p 2.6748 | consistent with L4-S and K27's bounds | builder file 15 | — | — |
| run sheet §8 | number | "L (12.0 s)" | IMPRECISE (measured 11.993 s at k 0.84) | 1.5 × 7.9955 = 11.993 | fix | — |
| L4-S | open | scene JSON and SHA committed with the kit | pending (abx_kit not yet touched) | file 10 L4-S | — | — |
