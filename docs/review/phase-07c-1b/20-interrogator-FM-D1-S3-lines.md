# 20 — Interrogator on the FM-D1-S3 final lines (file 19)

2026-11-13, corpus c1b171f. Saved by the orchestrator from the interrogator's report. Wording check only (Maisara chose (i)).

**Verdict:** no line falls, no tension cell misread; every line SURVIVES WITH CORRECTIONS except the 07c-2 AC (SURVIVES). The lines may
be applied once the corrections are in; no seat re-heard; nothing to Maisara.

| line | outcome | corrections |
|---|---|---|
| 07c-2 scope 9 bullet | SWC | FM-04, -07, -08, -10, -11 |
| 07c-2 AC | SURVIVES | — |
| 08-3 AC | SWC | FM-06 |
| 09 AC | SWC | FM-06 (inherited) |
| AX47 (b) evidence + text addition | SWC | FM-08 wording carried; FM-14 |
| §6 row | SWC | FM-08 wording carried |
| debt rows | SWC | FM-16, -17 |
| ledger edits | SWC | FM-19 |
| tension map | SWC (winner unchanged, max 1, sum 12) | FM-02 |

Verified: file 40 corrections 80 (NFR preamble l. 101 "Accuracy is the top priority", NFR-1), 86, 88 (2×2 mix named; N1 per output, N2
on the aggregate with closed forms), 90, 91, 92, 93 all applied; Seat 4 (file 15), Seat 5 C1–C4 (file 17), Seat 3 C1–C3 (file 18)
conditions all met in the text. Numbers recomputed: 10^(1/20) − 1 = 0.12202 → −18.27 dB; 10^(0.5/20) − 1 = 0.05925 → −24.55 dB; 1 −
10^(−1/20) = 0.10875 → −19.27 dB; N1 g² = 1.2589 → +3.54 dB, 0.7943 → +2.54 dB, margin 20.81 dB; N2 L′ − L = (b − a)(n1 − n2), R′ − R =
(a + b)(n2 − n1), energies 2(1 ∓ 2ab), 2ab = √(1 − γ²), aggregate +3.01 dB, L-only threshold |γ| ≤ 0.1218; ear imbalance aggregate
2(1 − s + 2ws), min 4w, red while w > 0.003724 (below 24.27 dB); AX18 equal-gain mid-fade (1+ρ)/2, equal-power 1+ρ, −3.01 dB at ρ = 0;
seed guard s ⊕ (s+1) = 2^m − 1 ≠ 0x9E3779B9 (NoiseTail.cpp l. 54–57).

| id | item | verdict | correction |
|---|---|---|---|
| P07C1B-FM-01 | S3 0/1, S4 0/1 | faithful | — |
| P07C1B-FM-02 | S5 1/1 "(read from conditions)" | faithful cell, imprecise basis — clause (2) (handover law) is a crossfade law, Seat 3's README row, rated 0/1 by Seat 3 | "S5 1/1 as rated (file 17, C1–C4); clause (2) lies in Seat 3's row, rated by Seat 3 (file 18)" |
| P07C1B-FM-03 | −18.27 / −24.55 / −19.27 dB | CORRECT | — |
| P07C1B-FM-04 | 07c-2 N1 "+2.5 to +3.5 dB" | IMPRECISE | "+2.54 to +3.54 dB" |
| P07C1B-FM-05 | N2 closed forms, aggregate | CORRECT | — |
| P07C1B-FM-06 | 08-3 AC (09 inherits) "green where |γ_b| ≤ 0.122" | IMPRECISE (holds at B = 1 dB only; at 0.5 dB, ≤ 0.059) | "green where |γ_b| ≤ 0.122 at B = 1 dB (≤ 0.059 at 0.5 dB)" |
| P07C1B-FM-07 | 07c-2 "zero matched tail energy (the AX22 ISM-only fallback; …)" | IMPRECISE (AX22 L144: the fallback is matched at max(t_mix,e, t_cap,e) "only if the window holds non-zero energy") | "(e.g. an AX22 ISM-only fallback whose matching window holds zero energy; AX49 D1 early-only scenes)" |
| P07C1B-FM-08 | 07c-2 clause (2) "equal-power, AX18's law … (as a `tailSeed` change)" | IMPRECISE (AX18's sentence names only `tailSeed` and fs changes; a same-seed different-stream interim is outside AX18's equal-gain "Same-scene steps" only by that rule's condition "the same emitter streams"; AX47 Scope reads "Same-scene steps are equal-gain (AX18)") | cite AX18 Same-scene steps' "same emitter streams" condition as the reason, mark it outside AX47 Scope's equal-gain sentence; same wording in §6 row and AX47 evidence |
| P07C1B-FM-09 | consequence of clause (2) | stated: with a shared early part the output correlation ρ_b = the band's shared (early) energy share; equal-power lifts mid-fade by 10·log10(1+ρ_b), 0 to +3.01 dB (AX18 evidence, Vorländer §4.3 Eq. 4.15); recorded, not bounded, as AX47 Measurement does for the load fade | — |
| P07C1B-FM-10 | 07c-2 "this phase's loop (Seat 5, AX18)" | IMPRECISE (crossfades are Seat 3's row, README l. 57; Seat 3 handed thread and fade mechanics to Seat 5) | "(Seats 3 and 5, AX18)" |
| P07C1B-FM-11 | 07c-2 "In a two-output mode, N2 as phase-08-3 states it is added" | IMPRECISE (07c-2 has no two-output mode: omni uses output index 0 for both, Engine.cpp l. 465, NoiseTail.h l. 45–47; 08-3, 09 test only the AX49 provisional) | state which test carries it, or drop the clause |
| P07C1B-FM-12 | full-length window | CORRECT | — |
| P07C1B-FM-13 | EDT 5 % (Vorländer Table 6.1) | CORRECT | — |
| P07C1B-FM-14 | AX47 (b) text addition position | IMPRECISE (after ")" the text runs "…to 0.5 dB per emitter and band…") | end the clause with a comma, or place it inside the parenthesis |
| P07C1B-FM-15 | S5 facts | CORRECT | — |
| P07C1B-FM-16 | S5 debt "≈ 16 IR builds" | IMPRECISE (with C1's repeat builds 4 × 2 × 2 fs × 2 seeds = 32; 28 new with the exact IR reused) | "≈ 28 new IR builds per scene per mode (repeat builds included)" |
| P07C1B-FM-17 | S5 debt "1 seed only with C1 met and a stated reason" | INCONSISTENT (row only; lines say 2 seeds, Seat 4's cell rests on ≥ 2) | drop the clause, or "a 1-seed form needs a /fix-plan with Seat 4 heard" |
| P07C1B-FM-18 | debt completeness | faithful | — |
| P07C1B-FM-19 | ledger round-files / rows | IMPRECISE (§6 row cites file 20; the list stops at 19; P07C1B-FM rows missing) | add "20 (interrogator on 19)" and "P07C1B-FM-01 … 20" |
| P07C1B-FM-20 | strongest objection | holds | stronger objection below |

**Stronger objection (inherited from AX47 (b), no outcome changes):** the window starts at t_mix,e; in an AX22 fallback with a tail
(onset at max(t_mix,e, t_cap,e)) the window also holds specular energy both IRs share, scaling the ratio by the window's tail share s
and loosening the pass side (s = 0.5: a ≈ 1.38 dB step passes a 1 dB bound); N1 stays red unless s < 0.0075. Seat 3 offered printing
the specular share as an optional, zero-rated item.

Questions: (1) the specular share of E(final) in the window on A4 cases under an AX22 fallback with a tail — printed? (2) clause (2) in
Seat 3's row (FM-02); (3) which test the "two-output mode" clause binds (FM-11).

**Orchestrator's application (no new decision):** FM-11 — the clause is dropped (no 07c-2 two-output mode; any later two-output
interim falls under 08-3 / 09's own lines); Q1 — Seat 3's optional, zero-rated print of the window's specular energy share is added to
the 07c-2 bullet and the 08-3 / 09 lines (print only); FM-17 — the clause is replaced by "a 1-seed form needs a /fix-plan with Seat 4
heard"; FM-14 — the clause ends with a comma.
