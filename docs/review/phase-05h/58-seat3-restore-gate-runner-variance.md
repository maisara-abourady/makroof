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
