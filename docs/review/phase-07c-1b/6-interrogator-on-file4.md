# 6 — Interrogator, decision mode, on decider round 1 (file 4)

2026-11-13, corpus c1b171f. Saved by the orchestrator from the interrogator's report. Read: files 1, 2-seat1 … 2-seat9, 3;
`docs/board/README.md`; `.claude/agents/decider.md` §1a, §3–§6; PRD; BUILD_PLAN AX38, AX47–AX49; phase-07c-1b, 07d, 08-4,
13/13-1/13-3; the brief; RG-1 `docs/review/phase-05h/70-…`; code `CrossfadingConvolver.cpp` L60–99, L270–356, `NoiseTail.cpp`
L60–119, `ScenePipeline.h` L130–336; Vorländer §4.3 (Eq. 4.14–4.17) re-read. D-B5 (ii), (iv) not ruled (still convening).

## Outcomes

| decision | outcome | why |
|---|---|---|
| D-B1 (B1-b) | **SURVIVES WITH CORRECTIONS** | two map sums swapped; the Phase 13 pointer imprecise; K7 premise misstated; winner unchanged |
| D-B2 / FM-B2 | **PRD MISREAD**, also **TENSION MISREAD** | B2-a's cost at project load in prepare-before-setState hosts vs AX38 (iv)'s 10 s line left out; Seat 6's "silent would be 3" entered as 2/2; a debt row names a non-existent test |
| D-B3 window W-a + companions | **SURVIVES WITH CORRECTIONS**, plus formal **PRD MISREAD** | D3-L1, D3-L2 correct; D3-L3 tolerance correct, detection claim imprecise; T-0 missing from the acceptance check |
| D-B3 signal ruling s1 | **TENSION MISREAD** | no seat rated s1/s2/s3; Seat 1 "speech with pauses", AX47 and AC 7 "speech"; "speech-like" changes AX47 unrated; the decider's own fallback applies |
| D-B4 (C7′) | **SURVIVES WITH CORRECTIONS**, plus formal **PRD MISREAD** | C6 and C1+C6 sums 10 (not 9), C8 21 (not 22), winner unchanged; plan text puts C1 under AX38 (i) contradicting Seats 2, 5; C2, C4, C8 not shown against the PRD ids |
| D-B5 (i) S2 | **SURVIVES WITH CORRECTIONS**, plus formal **PRD MISREAD** | S2 wins whatever the conditional readings; no option lines against PRD ids |
| D-B5 (iii) M-a | **TENSION MISREAD** | S6-k dropped on a missing Seat 5 cell that can change the winner; Seat 3 convened for this trigger, no cell |
| D-B5 (v) E1 | **SURVIVES WITH CORRECTIONS**, plus formal **PRD MISREAD** | map, ordering, debt faithful; one wording slip; no option lines |
| D-B5 (vi) X-d | **PRD MISREAD** | item 4 adds a closure "by recording a recalibration" that AX38 4c (d) does not contain; the trigger is RG-1 text (her recorded decision), so reading its scope is FOR MAISARA; items 1–3, 5 apply the rule as written |

"Formal PRD MISREAD": a surviving option not shown against the acceptance check's PRD ids (step 8a, third case); the fix is one
line per surviving option; none points to a different winner.

## Ledger

| id | decision | check | item | verdict | evidence | outcome | question |
|---|---|---|---|---|---|---|---|
| P07C1B-R1-01 | D-B1 | convening | 9 rows; S9 not required | faithful | README row 9: the callback deadline touches none of it | — | — |
| P07C1B-R1-02 | D-B1 | map | 32 cells S1–S8 | faithful | 2-seat1 L16–19; 2-seat2 L11–14; 2-seat3 L48–51; 2-seat4 L13; 2-seat5 L36–49; 2-seat6 L14–21; 2-seat7 L14–17; 2-seat8 L14–17 | — | — |
| P07C1B-R1-03 | D-B1 | ordering | sums | slip | B1-a = **23** (decider 22); B1-c = **22** (decider 23); B1-a dropped on S5's 3; among max-1, B1-b 5 < B1-d 16 | SWC | correct both sums |
| P07C1B-R1-04 | D-B1 | debt | "Phase 13 scope 1 (release machines)" | IMPRECISE | phase-13.md L59 maps S1 to 13-1 scope 1 (profiling, lead Seat 3); L69 maps real-hardware callback timing (S9) to 13-3 scope 4 | SWC | which sub-phase owns the re-measure: 13-1 scope 1 or 13-3 scope 4? |
| P07C1B-R1-05 | D-B1 | D1-L1 | p99.9 = 1st–2nd largest at N ≤ 1 936 | CORRECT | R16: `us[ceil(0.999·N)−1]`; N = 953 → index 952 (max); N = 1 936 → 1 934 (2nd) | — | — |
| P07C1B-R1-06 | D-B1 | D1-L2 | host render thread real-time | NOT CHECKABLE (corpus); researcher read | R4, R7, R8 high; R6 documents MMCSS "Pro Audio"; that hosts use it is a lead | — | — |
| P07C1B-R1-07 | D-B1 | K7 premise | "Maisara named only at (iv) … not at (i)" | IMPRECISE | AX38 rationale "4a … Accepted by Maisara 2026-11-10" (L160), and 4a contains (i) incl. "not raised to compensate"; B1-c lowers priority, touching cond. 12 (D-G1), not that clause; conclusion stands, premise misstated, not load-bearing | SWC | restate K7 |
| P07C1B-R1-08 | D-B1 | PRD proxy | acceptance check | faithful | B1-b, B1-c, B1-d shown against the preamble and AX38 (i) | — | — |
| P07C1B-R1-09 | D-B2 | map | S6, B2-b (silent) | **TENSION MISREAD** | Seat 6: "AX47 forbids an early-only first IrSet, so the gap is dry or silent; silent would be 3 for this seat" (2-seat6 L36); entered 2/2 "at minimum"; the reversal sends "B2-b (silent …) back to the board" without recording the veto | TM | cell to 3; mark the reversal as a vetoed option (only Maisara overrides) |
| P07C1B-R1-10 | D-B2 | ordering | B2-d sum | slip | **16** (decider 15) | — | — |
| P07C1B-R1-11 | D-B2 | debt | S7 "08-4 prints insertMs per mode"; S5/S8 "Phase 13 host matrix reads insertion" | INCONSISTENT | phase-08-4.md has no insertion / insertMs item; plan-text 1–10 add none; phase-13 S6 (13-5 scope 3) exists but nothing adds insertion | TM | add via plan text, or name existing tests |
| P07C1B-R1-12 | D-B2 | convening | S4 not required ("E_b shared") | observation | the debt commits Phase 08 binaural; Seat 4 F2 (2-seat4 L7–9): binaural per-ear unit decays, synthesised synchronously at insertion (2-seat5 L66); README row 4 lists "binaural architecture" | — | justify S4 against F2 or convene Seat 4 narrowly |
| P07C1B-R1-13 | FM-B2 | "applying FM-3′ as written" | IMPRECISE | AX48 L170: keyless load = "any mismatch, or a v1 state", solved "on the restore thread"; scope 6: AQ10/AX48 "do not name instance insertion"; FM-B2 settles scope where her decision is silent — allowed without AMENDS, but not "as written" | — | restate as a scope reading |
| P07C1B-R1-14 | FM-B2 | PRD proxy | B2-a "strains 'usable' only by a sub-second stall" | **PRD MISREAD** | Seat 5 (2-seat5 L22–23): "in a prepare-before-setState host every instance pays an insertion solve on top"; VST3 fixes no order (R17), JUCE prepares in `setActive` (R19); at 8 instances ≈ 8 × 430 ms ≈ 3.4 s serial in class (1), on a load already at 10 206 ms; AX38 (iv)'s 10 s line (accepted 2026-11-10, a recorded decision) left out; B2-d's "real gain at project load in prepare-first hosts" (2-seat5 L67) and B2-b not shown against it | PRD MISREAD | Q1 |
| P07C1B-R1-15 | FM-B2 | NFR-2 reading | the stall "the kind NFR-2 accepts" | IMPRECISE | NFR-2's latency is processing latency "report[ed] … to the DAW for compensation" (PRD L106); a UI stall falls under the preamble's "usable" | — | cite the preamble only |
| P07C1B-R1-16 | FM-B2 | K11 | first IrSet at the first boundary, no fade | CORRECT (code) | `computeBlock` L281–287 (`blockStart_ == 0`); zero fill L301 | — | — |
| P07C1B-R1-17 | D-B3 | map / ordering | W rows S1, S3, S4, S5 | faithful | 2-seat1 L47–51; 2-seat3 L33–37; 2-seat4 L28–30; 2-seat5 L77–79; W-d dropped on S1's 3; max 1 W-a, W-b; 1 < 2 | — | — |
| P07C1B-R1-18 | D-B3 | D3-L1 | bound; dB; 3.0 dB excess | CORRECT | triangle inequality with g ∈ [g0, g0+Δ]; Δ = 1/30 → 0.285 dB; 2.5 ms 0.695; 5 ms 1.339; 512/1440 → 2.643 dB; Eq. 4.15 with the cross term unaveraged, equal energies, ρ → E(1+ρ): 3.01 dB at ρ = 1, 2.99 at 0.993; margin 2.7 dB (Eq. 4.15 stated for two rays with a path difference; the ρ form is the correlated-signal reading) | — | — |
| P07C1B-R1-19 | D-B3 | D3-L2 | per sample \|o\| ≤ max | CORRECT | convex weights (L79–81, L323); rounding covered by companion (i)'s 8u | — | — |
| P07C1B-R1-20 | D-B3 | D3-L3 tolerance | 8u·(\|a\|+\|b\|) never false-reds | CORRECT | gain cast (L80–81), two products, the sum (L323) → ≤ 3u·(\|a\|+\|b\|), ≤ 8u even with FMA; 8u = 2⁻²¹ = 4.77·10⁻⁷ (−126 dB) meets Seat 3's −120 dB | — | — |
| P07C1B-R1-21 | D-B3 | D3-L3 detection | "one-sample offset … 1/L ≫ 4.8·10⁻⁷: caught" | IMPRECISE | an offset moves o by \|b−a\|/L, not 1/L; caught only where \|b−a\| > 8u·L·(\|a\|+\|b\|) = 6.9·10⁻⁴ (48 kHz) / 1.37·10⁻³ (96 kHz) relative (≈ −63 / −57 dB); a provisional→exact fade with a near-zero step will not show an offset (its effect is below that level) | SWC | restate with \|b−a\| |
| P07C1B-R1-22 | D-B3 | companion (iii) | memcmp outside the fade | IMPRECISE (minor) | in the last fade block o = 0·a + 1·b (idx = len): bit-equal to b except b = −0 with a > 0 (gives +0); negligible on wet noise | — | compare by value, or document the signed-zero case |
| P07C1B-R1-23 | D-B3 | fade from silence | \|o\| ≤ \|b\| no ε | CORRECT | `rampIn` = float(j/L) ≤ 1; y_A zero-filled (L301); rounding monotone | — | — |
| P07C1B-R1-24 | D-B3 | signal s1 | "read from Seat 1's condition" | **TENSION MISREAD** | Seat 1: "Signal: the fixed sparse set — pink noise and speech with pauses (B2)" (2-seat1 L53–54); the decider: "not claims about speech"; no seat rated s1/s2/s3; AX47 ("Wet pink-noise and speech renders", L169) and AC 7 ("renders wet pink noise and speech") read as speech; "speech-like" in plan item 6 changes AX47 and the AC unrated; the acoustic rationale (bounds hold for any input) is correct — the reading is the defect | TM | Q2 |
| P07C1B-R1-25 | D-B3 | PRD proxy | acceptance check | PRD MISREAD (formal) | T-0 (a survivor) not shown against NFR-1, FR-SIM-6 | formal | add the line |
| P07C1B-R1-26 | D-B4 | convening / map | 9 seats; cells from conditions S3, S4, S5, S9 | faithful | conditions met by plan item 8; Seat 8's C4 "0 / —" entered 0/0 (harmless, losing option) | — | — |
| P07C1B-R1-27 | D-B4 | ordering | sums; exclusion of C1, C6, C1+C6 | slip | C6 = C1+C6 = **10** (decider 9); C8 = **21** (22); the exclusion is not a §5 step — it stands only as a §3 deferral (K17/K18 load-bearing for any "remedy"); "C1+C6 now, residual to 07d" as each seat's max over C1, C6, C7′ gives 14 (verified), the decider's reading, not a seat's; winner unchanged | SWC | — |
| P07C1B-R1-28 | D-B4 | D4-L1 | 8 × 634 = 5.07 s | CORRECT arithmetic; IMPRECISE as stated | one run's single-instance figure (run 41); other runs' Windows single-instance figures not shown | — | — |
| P07C1B-R1-29 | D-B4 | D4-L2, D4-L4 | vetoes; 10 206 ms | CORRECT | 2-seat1 L69–70; 2-seat3 L83; 2-seat9 L22; file 1 L118–119 | — | — |
| P07C1B-R1-30 | D-B4 | D4-L3 | C1's key filterbank + FFT size | CORRECT (code) | `NoiseTail.cpp` L85–105 | — | — |
| P07C1B-R1-31 | D-B4 | hidden premise (plan 8) | C1 "counted under AX38 (i), not (ii)" | INCONSISTENT (not load-bearing for C7′) | Seat 5 "resident size counted under AX38 (ii) 128 MB" (2-seat5 L101–102); Seat 2 "a resident 134 MB entry > 128 MB" (2-seat2 L38–39); 8 × 2²¹ × 8 B = 134 217 728 B (134 MB / 128 MiB); placing it under (i) is a scope reading of AX38 (accepted 2026-11-10) | SWC | strike the clause; leave it to 07d's loop |
| P07C1B-R1-32 | D-B4, D-B5 (i) | hidden premise | "background syntheses running" and the four-stage split test-only | NOT CHECKABLE yet | `ScenePipeline.h` has no running-syntheses counter (atomics L292–336); stage hook (L197–199) separates Plan / Solve / Assemble, not synthesis from assembly; a `src/` change moves "C7′ commits no code" and the S1 reading, not the winners | — | Q5 |
| P07C1B-R1-33 | D-B4 | PRD proxy | acceptance check | PRD MISREAD (formal) | C2, C4, C8 not shown against the preamble, NFR-6, P1 | formal | add the lines |
| P07C1B-R1-34 | D-B5 (i) | map / ordering | S1 cells 1/1 (S5), 0/1 (S7) | faithful, conditional on row 32 | both conditions "no D-B decision touches restore/builder path"; S2 (max 1, sum 1) wins either way | SWC; formal PRD lines | — |
| P07C1B-R1-35 | D-B5 (iii) | map | S6-k: Seat 5's cell missing | **TENSION MISREAD** | neither asked nor read from conditions (§4); dropped "rated by Seat 6 alone" (not a §5 step); if Seat 5 rates ≤ 0/1, S6-k (sum ≤ 3) beats M-a (4) | TM | Q3 |
| P07C1B-R1-36 | D-B5 (iii) | map | Seat 3 no cell | **TENSION MISREAD** | Seat 3 convened for D-B5 because it "rated RG-1's trigger (05h file 58)" (file 1 L151); (iii) re-derives that trigger; the decider withholds (ii)/(iv) for the same reason | TM | Q3 |
| P07C1B-R1-37 | D-B5 (iii) | "existing rule, no change of form" | IMPRECISE | 4c: mean of the measured medians, "re-derived at the 07c re-pin", no window (M-a matches); RG-1 file 70 L12 and brief O3 say "(≥ 3 in-window runs)", which macOS cannot meet | — | state it as a reading |
| P07C1B-R1-38 | D-B5 (v) | map / ordering / debt | E1 | faithful | 2-seat3 L93–95; 2-seat5 L127–128; 2-seat6 L62–65; E1 2 < E3 3; S3, S6 debt present; the 05i Windows precedent matches E1 | SWC; formal PRD lines | — |
| P07C1B-R1-39 | D-B5 (v) | wording | "at both gated builds" | IMPRECISE | low-α entries concern `cube100_lowalpha0.05_s0.3` only; the flutter build strict, not listed | — | reword |
| P07C1B-R1-40 | D-B5 (vi) | map | X-d from conditions | faithful | 2-seat3 L105–112; 2-seat5 L129–131; 2-seat6 L72–76; 2-seat7 L80–81; sum 7 | — | — |
| P07C1B-R1-41 | D-B5 (vi) | PRD proxy | "applying the rule as written (no amendment, not FOR MAISARA)", item 4 | **PRD MISREAD** | 4c (d): a fired trigger "is a defect … it enters the register with its remedy"; no closure "by recording a recalibration"; Seat 7: X-b "reads away a rule inside an accepted board answer" (2-seat7 L79–80); the macOS trigger is RG-1 text carrying `AMENDS her decision of 2026-11-10` (her recorded decision); reading its scope is FOR MAISARA (README item 1) | PRD MISREAD | Q4 |

## Questions for the decider's rebuttal (most consequential first)
1. **FM-B2.** In a host calling `setActive` before `setState` at project load (R17, R19), does each of 8 instances solve the
   default scene before its restore (2-seat5 L22–23)? The added serial time against AX38 (iv)'s 10 s line (already crossed at
   10 206 ms)? Show B2-a, B2-b, B2-d against the preamble and AX38 (iv) with that figure.
2. **D-B3 signal.** Does Seat 1, asked in a second round, accept the seeded glottal-pulse / resonator stimulus as its "speech with
   pauses"? Is AX47's "speech" kept or changed to "speech-like", and which seats rated that change? If kept, the fallback s2
   applies with Seat 7 convened.
3. **D-B5 (iii).** Seat 5's cell on S6-k and Seat 3's cells on M-a and S6-k; redo the ordering.
4. **D-B5 (vi) item 4.** Which AX38 4c text lets a (d) defect close "by recording a recalibration"? If none, write it as a FOR
   MAISARA reading with PRD ids, or drop it and re-read the S3 and S6 cells that rely on it.
5. **D-B2 / D-B4 bookkeeping.** Seat 6's B2-b (silent) cell as 3; name an existing 08-4 or Phase 13 item for the D-B2 debt rows
   or add them to the plan text; confirm whether record (h)'s running-syntheses count and the four-stage split need a `src/`
   counter or hook.

Corrections if re-issued: rows 03, 04, 07, 10, 13, 15, 21, 22, 27 (sums), 28, 31, 37, 39; and the missing option lines in the
"Decided for Maisara" checks for D-B3, D-B4, D-B5 (i), (iii), (v), (vi).
