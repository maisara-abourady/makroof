# 58 — Seat 3 (reverb renderer): the restore-gate register form against shared-runner variance (file 56)

phase-05h (session 2). Verbatim seat output (the orchestrator saved it). It answers B3 (i)–(iii) of the decider's convening file 59 in substance (what each form sees; the flutter scene as guard, not normaliser; 07c's remedy unchanged).

SEAT 3 POSITION

Read: file 56; decider 19 (D-H1 (v) W-x′, H1-F2); my files 5 and 17; file 1 §3–§4; file 7; phase-05h §5 "Blocking"; phase-07c §5 conditions 9–10; BUILD_PLAN AX38 4c (a)–(d); `test_diffuse_records.cpp` L46–92, L337–403. Corpus not consulted: the only acoustic step below is Eyring, which the code implements (`Decay.cpp`).

**1. Reading.** Which assertion form of the restore gate, until 07c, still sees a regression of the solve or the synthesis without firing on runner speed. Cue: **cost** (the restore is the rebuild interval the producer waits through, criterion 6; my §7 rule "never quote a CPU figure without a named machine": a shared runner is not one).

**What the two restores are made of** (Linux, from file 7's shares, file 1 §3, file 56's medians; synthesis scaled linearly with tail length, [Inferred/Hyp]): low-α cube: synthesis ≈ 1.8 s (≈ 88 %), solve 0.10 s (5 %), ISM+matching+mix ≈ 0.15 s (7 %). Flutter cube: T60 by Eyring ᾱ 0.64 → ≈ 2.6 s tail (vs the 12 s cap), so synthesis ≈ 0.4–0.45 s (≈ 60 %), solve 0.16 s (22 %, pilot-only), ISM+mix ≈ 0.1–0.15 s. Consequences (my arithmetic):
- A ×2 solve regression moves the low-α median +4.9 %: **no form at a 1.10 bound sees the solve below ≈ ×3.** The solve's real detector is the pinned work (`wPilot`/`wFinal` REQUIREs, L343–344, D7-deterministic). Under (b) the sign even inverts (flutter +22 %, ratio −14 %).
- A global ×1.2 synthesis regression: absolute +18 % (seen on a nominal runner, hidden on a slow one); ratio (b) +5 %: unseen. (b) sees the synthesis only from ≈ ×1.4, because the reference is itself 60 % synthesis.
- The ISM+mix (what survives 07c) is invisible to every form until 07c (10–20× headroom then).
- The ratio's own spread (±6–8 %) against a 1.10 bound: pinned to the records run, (b) would have been **red on Windows run 42935789745 (3.08/2.64 = 1.17) and Linux (3.24/2.85 = 1.14)**: runner-red again. Only the mean baseline (Linux 3.05, Windows 2.83) passes the runs on file, with 1–3 % margin.
So the flutter scene is a fair *comparability guard* (same code, same run) and an unfair *normaliser*: its mix dilutes the one regression the gate exists to catch by ≈ 3× and is as noisy as the bound.

**2. Ranking.** (f) mine *prefer* · (e) *prefer* · (d) *prefer in principle, not 05h's* · (b) *can live with* · (c) *can live with* · (a) *can live with* (lowest). No veto: no option touches the audio.

(f) = (e) plus two runner-free assertions already measurable: the solve's ns/evaluation ratio low-α / flutter on the same run (file 1 §3: 0.58 / 0.57 / 0.58 on the three OSes) ≤ 1.10 × 0.58, and the unit-decay length (1 152 000 samples at 96 kHz) pinned. The absolute 1.10 median bound asserted only when the flutter median is inside its window; otherwise "NOT EVALUATED (runner slow)" printed, counted in §0.

**3–4. Tension now / later.**
| option | now | later | cost / debt |
|---|---|---|---|
| (a) | 2 | 2 | A cost gate red on an unnamed machine 2 of 5 runs; it blocks the PR (07c) that carries its own remedy. Undo: this decision. |
| (b) | 1 | 2 | Blind to the synthesis below ×1.4 and to the solve entirely for the entry's life; false security on the term 07c is about to move and must size. Undo: a test edit. |
| (c) | 1 | 2 | On a nominal runner fires at ≈ ×1.8; every later slow run ratchets it. |
| (d) | 0 | 0 | The only form that makes an absolute bound a named-machine figure; Seat 7's euros, not this PR. |
| (e) | 1 | 1 | Sensitivity kept at 10 % when evaluated; evaluated on ≈ half the runs on file (Linux 2/4, Windows 2/5 inside ±10 %); a regression waits for the next evaluated run on that OS, at most one PR. |
| (f) | 1 | 1 | As (e), plus the solve path watched. |

**5. Evidence.** Medians, ratios: file 56 table [Measured, CI]. Shares 95.5 %/0.15 s: file 7 [Measured, local]; solve times and ns/evaluation: file 1 §3 [Measured, CI 42846229834]; gate code [from the code]; synthesis share of the flutter restore [Inferred, Hyp: linear in tail length — one split-timer run on the flutter scene would settle it; researcher/orchestrator]. The off-window runs show the low-α deviating more than the flutter in 2 of 3 (+33/+23, +29/+22, −18/−28 %) [Measured], so at the window's edge the bound effectively sits near 1.13.

**6. Conditions.** (a) → 1/1: none inside (d); it needs (d). (b) → 1/1: baseline = mean of runs on file, bound 1.15, the absolute median printed with a WARNING above 1.10 × baseline, and AX38 4c stating in words that the ratio detects a synthesis regression only ≥ ≈ ×1.4. (c) → later 1: baseline frozen, no further re-pin. (e) stays 1/1 only if the guard window is ±7 % with bound 1.10 (or ±10 % with 1.15), the "not evaluated" count is in §0 and the work pins run every time.

**7. Hand-offs.** Seat 5: the guard's CI form and whether `ci ok` may carry "not evaluated". Seat 7: (d)'s cost. Seat 2: the 0.58 per-evaluation ratio as a solve-path invariant; the fallback ISM's share of the flutter restore. Seats 6/8: a synthesis regression reads as a longer "settling" wait under 07c's interim tail.

**8. Premortem.** (b) lands; a `BandNoiseGenerator` edit in 07b makes `make` ×1.3 slower on every OS; the ratio moves +9 %, green; 07c sizes its background synthesis and interim-tail rules on a cost a third heavier than recorded, and Maisara meets it as a longer settling wait in 07c's bounce record.


---

## Round 2: Seat 3 on the decider's provisional (x′) (file 59 round 2)

SEAT 3 POSITION — round 2, (x′) only (file 59 "round 2" read; nothing from file 58 restated)

**Rating: (x′) now 1 / later 2** (can live with; not veto-grade: no option touches the audio).

**Now 1.** The one asserted timing figure is a relative one, the work pins stay (L343–344), the 1.15 multiplier clears every ratio on file (margins 5.5–11 %, K4), host-conformance evidence survives a red (`if: always()`). What it costs me now: nothing measured.

**Later 2, and why.** Until 07c the gate's job from my seat is to watch the synthesis (≈ 88 % of the low-α restore) and the solve. (x′) asserts a ratio whose reference is itself ≈ 60 % synthesis (file 58's inference; the orchestrator's flutter split-timer run will replace it): a global synthesis slowdown reaches the ratio at ≈ 1/3 strength, and with k = 1.15 the first synthesis regression the CHECK sees is ≈ ×1.5–1.6 (my arithmetic: low-α +0.9·1.8 s, flutter +0.5·0.43 s → ratio ≈ 1.14–1.17 × baseline). A solve regression lowers the ratio. So between now and 07c the only asserted timing figure cannot see either term below ×1.5; every real regression lands in the printed line, which nobody is obliged to read, and 07c then sizes its background synthesis and interim-tail rules on a cost it did not know had grown. Undo: a test edit; the cost is the unread regression.

**Conditions that move (x′) to 1 / 1** (each a test line, none a timing CHECK on an absolute figure):
1. Pin the unit-decay length (1 152 000 samples at 96 kHz / 576 000 at 48 kHz) and, if Seat 2 confirms it cheap, the `BandNoiseGenerator` operation count (B-seat-2 item): a runner-free synthesis *work* pin.
2. Assert the solve's per-evaluation ratio low-α / flutter on the same run ≤ 1.10 × 0.58 (file 1 §3: 0.58 / 0.57 / 0.58 on the three OSes): the solve-path detector the ratio inverts.
3. The summary line carries `WARNING` when the absolute median exceeds 1.10 × its pinned baseline or 14 × worst exceeds 30 s, and the §0 note counts the warnings; a run with a WARNING is named in the PR.
With 1–3, (x′) is blind only to a constant-factor synthesis slowdown below ≈ ×1.5 on a hosted runner, which no same-run ratio of two renderer workloads can separate from runner speed; that residue is Phase 13's and (d)'s.

**Premortem of file 58 against (x′): stands, slightly worse.** A ×1.3 `make` slowdown in 07b moves the ratio ≈ +9–10 %, under 1.15: green, no WARNING unless condition 3 is in. With condition 3 it is printed and counted; with condition 1 it is caught only if the slowdown changes the work count, not if it is a constant factor. Maisara still meets it as a longer settling wait in 07c's bounce record; with condition 3 the orchestrator meets it first.

**Hand-offs.** Seat 2: the operation-count pin; the flutter share once measured (if the share is ≥ 75 %, the ratio is blinder than I state; if ≤ 50 %, less). Seat 5: whether conditions 1–3 are test lines inside (x′)'s form. Seat 7: (d) for Phase 13.


---

## Round 3: Seat 3 on (x″) with the ns/evaluation CHECK demoted (interrogator file 65)

SEAT 3 POSITION — round 3, (x″) as worded by the coordinator (files 64/65 not re-read; rated on the stated form)

**Rating: (x″) holds at 1 / 1.**

Why the strike of c2 does not move me: the interrogator is right that 0.58 is a 4-thread, one-run artefact (file 1 L44–48), and the solve is 0.10 of ≈ 2.0 s, so a ×2 solve-time regression at constant work is +5 %, below anything the gate ever resolved; solve *work* stays pinned exactly (wPilot/wFinal, D7). What I asked c2 to catch is better served by accruing a per-scene solve median per run (the print) and converting it to a CHECK once ≥ 3 runs give a spread. The detector I need is the in-window absolute bound (±7 %, 1.10) on x64, which sees the synthesis from ×1.1 on a nominal runner, plus c1 (n and the unit-decay length) and c3 (WARNING above 1.10 × baseline / 30 s, counted, named in the PR). The corrected shares (0.92 / 0.51 → ratio 1.20 at ≈ ×1.65) make the ratio an even weaker synthesis detector than I stated; that is why it is a print, and I agree.

**What keeps it at 1 / 1 (inside the bounds, two lines of text, no new CHECK):**
1. The solve print is the per-scene solve median (ms) and its one-thread-equivalent is not inferred; after ≥ 3 runs the orchestrator proposes k from the spread through `/fix-plan` (the plan says so now).
2. On macOS (no in-window absolute bound), two consecutive c3 WARNINGs on the low-α entry are read as (v)(d)'s trigger (defect, remedy named), not as weather; otherwise macOS carries no synthesis detector until Phase 13 and my later rating returns to 2.

Premortem unchanged in mechanism, shortened in reach: a ×1.3 `make` slowdown is caught on x64 by the in-window bound on the next nominal run, and on macOS by c3's WARNING under condition 2.


---

## Round 4: Seat 3 on c2 narrowed to GROWTH-only at ±5 % (interrogator file 67)

SEAT 3 — round 4, one line: **(x‴) holds at 1 / 1.** The interrogator's narrowing is right: the macOS entry's recorded state is OVER30S until 07c, so a 30 s WARNING there carries no information; the GROWTH warning (two consecutive macOS low-α medians > 1.10 × 1 817 = 1 999 ms; the rows on file 2 106 / 1 849 / 1 887 / 1 715 fire it 0 times) is exactly the synthesis-growth detector I asked for, and it is the trigger that names a new defect, not 07c 9–10 restated. The ±5 % window with 1.10 unchanged evaluates the same four x64 rows, so my x64 detector's sensitivity is unchanged; only its evaluation rate falls, which c3's §0 count already records. No new condition.


---

## Round 5: Seat 3 on the macOS trigger armed at 2 172 ms (decider file 70)

SEAT 3 — round 5: **1 / 1 holds at 2 172 ms.** A macOS synthesis detector exists before Phase 13; at the 0.92 share, two consecutive medians over 1.15 × the four-run mean fires at a uniform slowdown ≈ ×1.19 (2 172 / 1 889 = 1.15 → (1.15 − 0.08) / 0.92 ≈ 1.16–1.2, my arithmetic), close to the x64 bound; 0 of 4 rows fire, so it is not weather. The 1 817 print stays as the record. No new condition.
