# 29 — Interrogator on decider file 28 (P07C1B-R1)

2026-11-13, corpus c1b171f (no acoustic fact load-bearing). Saved by the orchestrator from the interrogator's report.

**Outcome: UNDERCONVENED, TENSION MISREAD, PRD MISREAD.** No factual claim falls.
- Waits for Seat 5 (README row 5 "CI gates"; precedent phase-05i file 9 item 2; file 28 itself says "Seat 5 gives most").
- Seat 7 is needed narrowly, for answer 2's "the pair joins X-d−": does phase-07d scope 7's "≤ 3 extra manual runs per defect (Seat 7)" budget stay per defect? This is FM-TRIG condition (3), file 11 Q5.
- Seats 3 and 6 hold the X-d− debt row (file 11 L178) and are to be heard if the joins clause stays.

**Facts checked: CORRECT.**
- Run facts (macos.log L3069–3070, windows.log L3968, linux.log L2977). 4.626 / 3.1203 = 1.4826; 1.10 × 2.5297 = 2.783; growthBound 1629.
- Trigger: ⌊1.15 × 4443/3⌋ = 1703. The preceding macOS run is S2 43412038058 at 1 586 ms.
- FM-TRIG two-consecutive reading. AC 2 = the S2 runs (phase-07c-1b L141–144).
- The 29.1 s source is (a). "Re-listing changes no hosted assertion" holds.
- T1–T5 anchors: verbatim and unique.

**Not checkable here:** no macOS run between 43412038058 and 43427854710 (the brief records none); "src/ identical to 9717a58" (no git history in the interrogator's view).

**Imprecise or inconsistent claims:**
- R1-L4, Windows 29.50 s precedent: that print was ≤ 30 s on a strictly asserted entry, and the entry was listed later through (d). That route is unavailable to a closed low-α macOS entry.
- R1-L4b, a contrary precedent was omitted: phase-05i file 9 item 4 put `listed` back to true after OVER30S on the run of record, in the next permitted push. Distinguish it: that entry was still closing on 05i's runs; this one closed on the S2 runs under E1.
- R1-L5: (a) reads the recorded value at the pinned W_max, not "a pin's recorded values".
- R1-L7: re-listing is not a duplicate of X-d−. It is a listed entry with the same remedy and closing phase.
- R1-L8: re-listing could ride the review-round push (05i practice). The decider should name the CLAUDE.md clause T1–T6 ride under.
- R1-L10: T5 omits PASSES30S on Linux and Windows, the in-window status (Linux no, macOS no, Windows yes) and the counts.
- H1: "only that pin's runs count" is stricter than 05i practice and is not stated as such.

**PRD MISREAD:** the options are not each shown against NFR-4, the NFR preamble and NFR-6 one line at a time, and NFR-6's role (exact restore, not restore time) is not stated.

**TENSION MISREAD:** the map gives worst-off none (0/0), yet the text says "Seat 5 gives most" and has a Seat 5 debt row read from no report.

**Restatements, if the decision returns:**
- T1 precedent clause: "(as Windows' strict 29.50 s on run 42924781618, ≤ 30 s on a strictly asserted entry, did not list it; unlike phase-05i decider file 9 item 4, where the entry was still closing on 05i's runs including the run of record, this entry closed on the S2 runs under E1)".
- T1 gloss: "(a) reads the register's recorded value at the pinned W_max (for a closed entry, the E1 values), not one later print".
- Answer 1: "would add a listed entry with the same remedy and closing phase as X-d−". The push clause stated.
- T5: "WARNING: Linux GROWTH, PASSES30S; macOS RATIO, GROWTH, OVER30S, MACTRIGGER; Windows PASSES30S; in-window Linux no / macOS no / Windows yes", plus the counts.

**Questions for the decider:**
1. Seat 5's row: which item does this decision not touch?
2. Where does the Seat 5 debt row come from?
3. Under the joins clause, is the Seat 7 run budget per defect or merged?
4. What distinguishes this from 05i file 9 item 4?
5. Show each option against NFR-4, the preamble and NFR-6.
