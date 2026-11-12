# 14 — Seat 3, answer to interrogator row P07C1-59 (phase 07c-1)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Question: file 13 row P07C1-59 and Q1. Result: D3*″ vetoed by Seat 3 in its own words (3/3); the decider's D3*‴ stands (reading A); no NEEDS MAISARA.

SEAT 3: **3/3.** On T60-changing edits, D3*″ holds the ISM about 3 s whenever the provisional becomes the full synthesis (T60_max ≳ 35 s at 100 m). That is the same hold I vetoed in D2: the ISM held behind the synthesis, which breaks condition 4's intent and my S4.

My r2 2/2 and my r3 "stands" both assumed a wait of 0.2–0.25 s. They do not cover this case. In D3*″, 2/2 applies only while max(0, t_prov − t_ISM) stays at or below about 0.25 s.

**Condition to lower it to 1/1:** the bridge.
1. On a T60 edit, submit the new ISM as soon as it is ready.
2. Pair it with the previous unit decays at the interim level, rescaled to the old ebar: √(E_target/ebar_old).
3. Replace them with the provisional or exact tail through equal-gain steps (the noise is the same, ρ high).
4. Print the ISM latency in record (g).

Without the bridge, a looser condition lowers it only to 2/2: cap the hold at about 0.25 s, and past the cap fall back to the bridge.