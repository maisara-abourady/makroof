# 67 — Interrogator: DECISION RG-1 round 2 (file 66) — TENSION MISREAD on the macOS two-warning trigger as worded (OVER30S on a listed entry is its recorded state); the rest SURVIVES WITH CORRECTIONS

phase-05h (session 2). Verbatim interrogator output (the orchestrator saved it).

Corpus present, revision c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (not load-bearing: no acoustic claim in RG-1).

**Outcome: TENSION MISREAD on one composed clause (the macOS two-warning trigger as worded); everything else SURVIVES WITH CORRECTIONS. Winner unchanged under the fix below.**

## (1) Q1–Q5 against the sources — all CORRECT
- Q1: file 1 L44–48 says the flutter ns/eval is inflated 33 % by discarded speculative blocks; one run; strike is right. ns/eval = ms·1e6/(W_pilot+W_final) reproduces file 1 §3 (161.5e6/5 701 774 = 28.3; 98.9e6/6 044 975 = 16.4).
- Q2: file 60 r2 "now 1 / later 1, unchanged … Condition: window ±5 %" — faithful.
- Q3: ±5 % rows redone from file 56: 716/701 = +2.1 %, 693/701 = −1.1 %, 757/737 = +2.7 %, 752/737 = +2.0 %; all others ≥ 15 % off. Margin at 1.4× leverage: +7 % vs 1.10 → ≈ 3 %; in-window spread 2092/2043 = 2.4 %, 2056/2000 = 2.8 %. Correct and, as stated, thin.
- Q4: (1849+1887+1715)/3 = 1 817; 537/484 = +11 % out of window. Correct.
- Q5: 0+1, 1+1, 1+1, 0+0, 1+1 = 7. Correct. K5 (0.92/0.51 → d = 0.65, ×1.65), K7, K8, NFR-4, macOS three runs, FFT n (1 152 000+31 394 → 2^21; 408 911 → 2^19) all check.

## (2) Readings of Seats 2, 5, 6 — and the clause that fails
**F1 — macOS trigger (form item 3; FOR MAISARA sentence "two consecutive runs with the low-α growth or 30 s warning are a defect under (d)").** INCONSISTENT with the record and with §5 (c)–(d). The macOS entry is listed at 33.40 s: 14 × worst > 30 s is its *recorded state* until 07c, not a signal. File 56 rows: macOS 37.37 / 31.23 / 31.71 / 27.33 s on identical code — the OVER30S trigger would have fired on runs 2 and 3, and run 4 would then print PASSES30S under (c) proposing removal. That is runner weather read as (d) defects, the thing the decision exists to stop; and (d)'s remedy for macOS is already 07c 9–10, so the "(d) edit" has nothing to add. On GROWTH alone (median > 1.10 × 1 817 = 1 999 ms) the record shows one row (2 106), never two consecutive.
  - Seat 3's c2 says "two consecutive c3 WARNINGs" (c3 = "above 1.10 × baseline / 30 s"), so the decider quoted it faithfully but composed a condition the data contradict; Seat 3's cell carries it.
  - Seat 5's reading is misquoted: file 66 says Seat 5 "priced 'plan edit per entry' (later 1)". Seat 5 file 57 §4 rates "each creep a plan edit" **2** under (c) and "'no re-run' turns runner speed into register 'defects'" **2** under (a). Not Seat 5's words; TENSION MISREAD on that cell as read.
  - Seat 6: criterion 6 ("a gate red when nothing changed says 'defect' falsely", (a) now 2) applies to the trigger as worded.
  **Fix:** narrow the trigger to the GROWTH warning only (two consecutive macOS low-α medians > 1.10 × 1 817), state that it fires 0 times on the four runs on file, mark Seat 3's cell "(c2 read: GROWTH-only is the synthesis detector it named; OVER30S on a listed entry is not)" or take one line from Seat 3; then Seats 5 and 6 can be read from their conditions (no fire on identical code). As worded, Seat 5 must see it.
**F2 — Seat 3's cell is on ±7 %** (file 58 r3 names "±7 %, 1.10"); mark it "(±5 % read from Seat 7 r2: same four rows evaluated, 1.10 unchanged)". Correction only.
**Seat 2:** faithful via its own hand-off (§7: "the exact synthesis count to pin: Seat 3"; Seat 3 c1 = n + unit-decay length). Residue: Seat 2's premortem is "an extra filterbank pass", which changes neither length nor n (the count has no counter). Add to its debt row: "a per-op slowdown *or an added pass* at unchanged length/n invisible until Phase 13".
**Seat 5 ns/eval → print:** faithful (its §2 rule "no timing figure is a CHECK on shared runners"; (ii)'s "Seat 2 to confirm" never met).
**Seat 6:** line + §0 met (ratio+bound, 14 × worst, full-rebuild median, status present at test L519–524).

## (3) Map and ordering
Max 1, sum 7 < 10; (d) bounds; (a) veto (file 57 §3 "(a) **3**"); worst-off tie with (b)-conditioned; sum; reversibility. One composed variant this round. Correct and unchanged by F1 if Seat 3 holds 1/1 on GROWTH-only.

## (4) Plan text
Fit for the plan-editor after F1 and: **phase-05i scope 3 (L77–85)** still pins "Linux 2 043 ms, macOS 2 106 ms from run 42909003931" and "the macOS entry (37.37 s, median 2 106 ms)" — contradicts the mean baselines 2 068 / 2 028 / 1 817; the decider's "carries the re-pin rule" does not name this amendment; it must. AX38 4c register sentence, §5 (c)–(d) ("growth bound" → "the asserted figures above"), AX41, phase-13 L123, phase-07c condition 9 (L95, L126, L140): consistent and existing.

## (5) Test form and CI
Implementable and already in the tree: constants L83–88 (kGuardPct 5, FFT sizes correct), work pins L376–392 (nPinned != 0 guard = PROVISIONAL form), solve timer L393–414 (`estimateDiffuse`, work from `d.wPilot + d.wFinal`), guarded REQUIRE L525–526, GATE lines L514–524; ci.yml L427 and L437 already `if: always()`. Nits: status prints `not-evaluated(runner)` without "+N %" (flutterDev is on the flutter line); L524 has a dead `? "" : ""`. macOS two-consecutive read from §0 by the orchestrator: feasible, no test state.

## (6) File 63 vs the form
G4/G6 bear on the one remaining timing CHECK (in-window 1.10 at n = 2); the decider states "thin" and names the reversal — adequate, no research gap. G7: at k = 1.20 the per-OS one-sided level is ≈ 97–98 % (t ≈ 3.37 at df 3, 3.02 at df 4), i.e. a RATIO warning ≈ 2 % per OS-run, not Seat 5's "0.2 %" (K3); print-only, restate K3 and mark file 63 read.

## Questions for the rebuttal
1. On runs 42909003931→42924781618→42935789745 macOS read 37.37 / 31.23 / 31.71 s on identical code: does the OVER30S trigger fire there, and what does its (d) entry say that 07c 9–10 does not?
2. Where does Seat 5 rate "a plan edit per entry" at later 1? (file 57 §4 gives 2 under (c).)
3. Does Seat 3 hold 1/1 with c2 narrowed to GROWTH-only and the window at ±5 %?
4. Which text replaces phase-05i scope 3's "2 043 / 2 106 from run 42909003931"?

Files: /home/user/makroof/docs/review/phase-05h/66-decider-decision-RG-1-r2.md, /home/user/makroof/docs/review/phase-05h/56-orchestrator-restore-gate-runner-variance.md, /home/user/makroof/docs/review/phase-05h/57-seat5-restore-gate-runner-variance.md, /home/user/makroof/docs/review/phase-05h/58-seat3-restore-gate-runner-variance.md, /home/user/makroof/docs/review/phase-05h/60-seat7-restore-gate-runner-variance.md, /home/user/makroof/docs/review/phase-05h/61-seat6-restore-gate-runner-variance.md, /home/user/makroof/docs/review/phase-05h/62-seat2-restore-gate-runner-variance.md, /home/user/makroof/docs/review/phase-05h/63-researcher-RQ-RG.md, /home/user/makroof/docs/review/phase-05h/1-orchestrator-cpp-costs.md, /home/user/makroof/docs/phases/phase-05h.md L365–390, /home/user/makroof/docs/phases/phase-05i.md L77–85, /home/user/makroof/tests/unit/test_diffuse_records.cpp L83–88, L376–414, L491–527, /home/user/makroof/.github/workflows/ci.yml L425–437, /home/user/makroof/src/sim/tail/NoiseTail.cpp L72–132.
