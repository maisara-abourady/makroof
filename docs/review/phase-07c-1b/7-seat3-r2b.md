# 7 — Seat 3 position, round 2b (D-B5 (iii) Q3, (vi) Q4)

2026-11-13. Saved by the orchestrator from the seat's report. No acoustic claim. Read: file 4 D-B5 (iii), (vi); file 6 rows 35,
36, 41, Q3/Q4; 2-seat6 D-B5 (iii); 2-seat3 (vi); 05h file 58 r3 condition 2 and r5; BUILD_PLAN L160 AX38 4c (d). Arithmetic on
the S2-proxy macOS low-α medians 1 528 (41), 2 223 (42), 2 572 (44): mean 2 107.7, max/min 1.68, max/mean 1.220; low-α synthesis
share 0.92 (RG-1 r3).

**Reading.** Q3: does the re-derived macOS trigger still detect synthesis growth and stay clear of weather? Q4: how the
MACTRIGGER defect closes. Cue: cost — the synthesis-growth detector on a named machine. Standard: 05h file 58 r5 (trigger 1/1
because it fired at ≈ ×1.16–1.2 and 0 of 4 rows on file fired it).

**Q3**

| option | trigger | detects uniform synthesis slowdown at mean runner speed | rows over it | label | now | later |
|---|---|---|---|---|---|---|
| S6-k (k = max(1.15, max/mean) = 1.22) | ⌊1.22 × 2 107.7⌋ = 2 571 ms | ≈ ×1.24 ((1.22 − 0.08)/0.92) | run 44 (2 572) over by 1 ms (rounding) | prefer | 1 | 1 (conditions) |
| M-a | ⌊1.15 × 2 107.7⌋ = 2 423 ms | ≈ ×1.16 (as 05h r5) | 1 of 3 (run 44) | can live with | 1 | 2, or 1 under a condition |

- M-a later 2: breaks 05h r5's premise — one run in three over by itself; with independent runs a weather double ≈ once per 9
  consecutive pairs [Hyp, N = 3]; under Q4 without item 4 such a double becomes a defect only a remedy closes; on a fast runner
  (run 41 = 0.725 × mean) neither form sees anything below ≈ ×1.6–1.7.
- S6-k: keeps a detector (05h r5's requirement), sensitivity ×1.16 → ×1.24; set at the largest of 3 runs, the next run exceeds it
  with probability ≈ 1/4 (order statistics, exchangeable), a weather double ≈ 1/16 [Hyp, independence]; debt: k ratchets up with
  every re-pin including a slow run (05h file 58 option (c)'s failure).

**Q4**

| option | label | now | later |
|---|---|---|---|
| X-d with item 4 as an explicit FOR MAISARA reading | prefer (= X-c) | 1 | 1, conditional |
| X-d without item 4 (closes only by 07d's remedy) | can live with | 1 | 2 → 1 under a condition |

- Without item 4: item 3's split printed but closes nothing = X-a (rated 1/2). Risks: weather becomes a defect to "remedy"; worse,
  07d's long-T60 remedy cuts the low-α restore, the trigger stops firing and the defect closes while a macOS-specific per-emitter
  synthesis load (suggested by the low-α / flutter ratio 3.32–5.05 on macOS vs 2.43–2.61 on Linux) is never explained.
- With item 4: as worded "per-emitter synthesis time unchanged" has no reference — no pre-change macOS split exists — so
  "unchanged" is undefined, and an undefined test is explaining-away (05h r3 condition 2 ruled it out).

Evidence: medians from the GATE lines of 41/42/44 [Measured, CI]; 0.92 RG-1 r3 [Measured]; 4c (d) text BUILD_PLAN L160 [Obs], no
recalibration closure (agrees with row 41); exceedance rates own order statistics [Hyp, N = 3].

**Conditions.** S6-k stays 1/1 only if: k rounded up so no S2 run exceeds the trigger; k capped at 1.25 (detection ≈ ×1.27, just
under the ×1.28 rated later 2 in B-iv); the detection factor written in words in 4c. M-a → 1/1 if the closure path below exists
(a weather double can be shown to be weather). X-d without item 4 → 1/1 if the MACTRIGGER entry's remedy line in 07d requires
closure evidence: the macOS per-stage split after the remedy at equal work pins; the macOS/Linux per-emitter synthesis ratio within
1.10 × the same runs' flutter macOS/Linux ratio (same-run reference) [Hyp: factor from the x64 bound]; the re-derived trigger not
exceeded on two consecutive runs — read as naming the remedy with its evidence, inside 4c (d) as written. X-d with item 4 stays
1/1 only if "unchanged" uses that same same-run reference.

Hand-offs: decider and Seat 7 — S6-k changes RG-1's "1.15 ×" (text carrying `AMENDS her decision of 2026-11-10`), probably FOR
MAISARA like item 4; M-a needs no amendment (row 37). Seat 5 — its S6-k cell and the CI form of the split. Seat 2 — is
per-emitter synthesis ns a stable invariant across OSes. Premortem: M-a with closure by remedy only — a weather double enters as
a defect, 07d's remedy closes it, the real macOS synthesis load behind the 5.05 ratio ships unexplained; the orchestrator notices
first in 07d's records (a closed entry whose ratio did not move).
