# 5 — Seat 7 position, round 2 (D-B5 (ii), (iv))

2026-11-13. Saved by the orchestrator from the seat's report. As in its RG-1 cell (05h file 60): subscription product,
Maisara plus a contracted engineer, no customers yet, public repo; cost measured in manual three-OS runs, contractor sessions,
`/fix-plan` rounds (≈ half a session each, [Inferred] from 05h files 53/54) and the public CI record. No acoustic claim. Read:
file 4 D-B5, file 1 fact 5, 2-seat5 (ii)/(iv), 2-seat2 (iv), 05h files 60 and 70, BUILD_PLAN L160 AX38 4c.

**Reading.** How the low-α growth bound and the solve baselines are re-pinned when almost no run lands inside the ±5 % flutter
window (fact 5: Linux 1 of 3, macOS 0, Windows 0). Cues: the founder's hour, manual runs a cost (R1, criterion 2); red checks on
identical code in a public repo look one-shot (criterion 7, AI1); a rule's form changed after it proved unmeetable reads like a
retroactive deal change (V4) unless the reason is stated publicly in one sentence.

| Option | Ranking | Now | Later | Reason |
|---|---|---|---|---|
| B-iv | prefer | 1 | 1 | no runs beyond the S2 runs; the ratio cancels runner speed (Linux max/min 1.071, Windows 1.096; 1.10 × mean leaves ≈ 4–5 % headroom [Inferred]); now 1: one more "Decided for Maisara" item she may veto; later 1: blind to a slowdown hitting both scenes equally — the flutter 14 × worst ≤ 30 s stays asserted, the absolute median printed with WARNING, Phase 13 restores the absolute bound on release machines; undo = a test constant + a plan line; contrary evidence from 07d runs or the Phase 13 re-check |
| (iv″) | prefer | 0 | 1 | print-only, never a (d) trigger, no false red; later 1: "PROVISIONAL until ≥ 3 in-window runs" may never end, a record saying less than it seems (criterion 7) |
| B-ii | can live with | 2 | 1 | keeps one run (490); ≥ 3 in-window means more manual runs before the PR (Maisara 2026-11-08); at ≈ 1 in 3 per OS ≈ 9 runs per OS [Inferred], macOS 0 so far: an unbounded lottery |
| B-i | can live with | 2 | 1 | same, worse: keeps none of 453 / 490 / 706 |
| B-iii | can live with | 2 | 2 | honest window ≈ ±22 % on Linux (Seat 5): the 1.10 bound flakes under "no re-run"; each false red a (d) round ≈ half a session, red on the public Actions tab (RG-1 premortem) |

Evidence: spreads, counts, ratios (file 1 fact 5; 2-seat5 (ii)) [Observed]; ns/eval spread 1.09–1.50 and steady ratio
0.584–0.592 (2-seat2 (iv)) [Observed]; cost of a red (05h 53/54) [Observed]; session estimates and run counts [Inferred]
(researcher could verify from the CI history 05h–07c-1).

Conditions: B-i / B-ii → 1 now only with a cap of ≤ 3 extra runs, after which B-iv or (iv″) applies automatically; B-iii →
1/1 only as print-only (= (iv″)); B-iv held at 1/1 by: one sentence of public reason in the PR and ledger (e.g. "the absolute
bound measured runner speed; the same-run ratio measures the code; Phase 13 restores the absolute bound"), stated as a change
of form naming what it can no longer see (not as loosening), and GROWTH, OVER30S, MACTRIGGER emitted as `::warning::` or to
`$GITHUB_STEP_SUMMARY` (Seat 5; K24); (iv″) later 1 only with a dated exit (re-derived at 07d's re-pin, else named in Phase 13
scope) — without one, later 2.

Hand-offs: assertion form and k Seat 5; what the ratio cannot see Seats 2, 3; load time Seat 6; B-iv vs CLAUDE.md "never
loosen", amend vs read RG-1 — the decider then the interrogator; a veto — Maisara.
Premortem: B-i/B-ii — the PR waits through 6–9 manual runs or goes red, the contracted engineer notices a stalled PR; B-iv — a
uniform slowdown slips through, noticed first by Phase 13's re-check or the absolute WARNING if surfaced as an annotation.
