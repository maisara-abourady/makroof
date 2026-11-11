# 12 — Seat 1 (perceptual gatekeeper) on D-G1

Phase 05i, 2026-11-11. Convened by decider file 11 (Brief 1). Saved verbatim by the orchestrator (the seat only reads).

SEAT 1 POSITION

**1. Reading.** G-1 is a conformance defect: the gate covers the whole room-IR build instead of the solve alone. The choice is who fixes it and when, or whether her decision is amended to match the code. Cues: a threshold quoted without its method (§4, S4: the 700 ms row); motion and time variance (S7); an option that writes an untested acceptability claim into a decision (S2, Tier A).

**Brief 1, the bar.** Corpus, Vorländer §15.3 Table 15.1: a *proposal* for update intervals (after Lentz et al. 2007) for interactive VR. It states no listener, paradigm, signal or strictness, so it is an engineering update budget, not a detection threshold, read "by extension" as file 11 does. Two points from the corpus:
- **The table splits the update.** Moves > 0.25 m get 700 ms for the *specular* part; moves > 1 m get 3 s for specular *plus scattering*. Check: at the 30–50 cm/s translation speed the text gives, 0.25 m takes 0.5–0.83 s and 1 m takes 2.0–3.3 s, so each budget is roughly the travel time of its step. Following should be read against two rows: the specular (ISM) part against 700 ms, the full rebuild with the diffuse part against 3 s. On the 05i records the joint step (1 752–1 919 ms at 96 kHz, one instance) passes the 3 s row and fails the 700 ms row, because nothing delivers the specular part separately. The contended host-call waits (3.6–5.0 s) and joint staleness (up to 16.4 s) exceed even the 3 s row.
- **DAW automation is not self-motion.** The detection latencies I hold (T1: mean 108 ms, lowest 52 ms) are for head-tracked self-motion and do not transfer. In a DAW the cues are lag behind the canvas position the user sees (TS2, cross-modal), lag behind the musical timeline, and intermediate positions never rendered when staleness exceeds the duration of the move. Whether the bar is looser or tighter than 700 ms is [Hyp]; no test exists. For lags of several seconds no test is needed to say "follow" fails (S2 anomaly): the rendered trajectory misses the automated one by more than the move itself — a functional record, not an audibility claim. Offline bounce is synchronous (AQ4), so bounces follow exactly; the lag hits real-time monitoring only.

**2. Ranking.** A′ *prefer* · D *prefer* (equal to A′ on my criteria; the schedule belongs to Seat 7) · A *can live with* · E *can live with* (barely) · B *cannot live with*.

**3–4. Tension now / later.**

| Option | Now | Later |
|---|---|---|
| A′ | 0: no output change (AX5), no claim | 0: the before-remedy gate-wait baseline is the "measure the floor first" step (T1, Strategy B); it lets 07c-1 show what narrowing bought, which K-g5 says is unmeasured |
| D | 0 | 1: the narrowing's benefit to following is still unmeasured unless 05j records before and after; undo cost one S phase |
| A | 0 | 1: 07c-1 can claim narrowing helps following without a before-remedy baseline; undo is a parameter-level revert of the hook; evidence at 07c-1 conditions 4 and 7 |
| E | 1: no register entry and no release-rule coverage, so the defect is findable only in a PR follow-up | 2: a build could leave the release rule's protection with multi-second following and no recorded owner; evidence only at 07c-1 F1 review, or in user reports |
| B | 2: writes into her decision that whole-build serialisation is acceptable, with no listener or yardstick evidence; the only yardstick (700 ms specular row) already fails | 3: makes permanent a mechanism that holds instance k's ISM update behind instance j's diffuse solve, contradicting 07c-1 condition 4 ("the ISM update is never held behind the diffuse solve") across instances, and Table 15.1's specular row; undoing costs a second amendment plus the remedy anyway, at 07c-1 or Phase 10 |

**5. Evidence.** Table 15.1 is a proposal with a 700 ms specular / 3 s specular+scattering split, and translation is 30–50 cm/s: corpus, `vorlaender-auralization.md` §15.3 [Observed, corpus]. The 05i figures from file 3 and P05I-53 as cited in file 11 [Observed, records]. Head-tracked latency thresholds do not transfer to automation: T1 [Observed]; transfer [Inferred]. Visible position as part of the stimulus: TS2 [Self-report], medium. How large the DAW following threshold is, and its direction against 700 ms: [Hyp], no base rate. **Researcher:** verify whether Lentz et al. 2007 derived the 700 ms and 3 s values from listening tests or from engineering estimates.

**6. Conditions of acceptance.** B (3 → 1): the amended wording keeps the ISM/specular update outside the gate, so only the diffuse solve is serialised — A's remedy written as text, so better choose A or D. E (2 → 1): add the register entry under AX38 (i) and the release-rule coverage (that is A). A (1 → 0): whoever owns the remedy records following lag (the joint step, 1/4/8 instances, 48/96 kHz) before and after narrowing, and runs the click detector (`python -m tools.acoustics clicks`) on the contended automation renders; FR-SIM-6's "without audible artifacts" stays "not measured" until then.

**7. Hand-offs.** A′'s poller inside phase-05i scope 2, safety of narrowing, TSan: Seat 5. Concurrent CPU and following on 4-core machines: Seat 3 (and RQ-G1). Memory split outside the solve: Seat 2. The cost of 05j: Seat 7. The "settling" readout under multi-instance lag: Seat 6. Whether producers monitor moving stems live and so meet the lag: Seat 8.

**8. Premortem.** B is adopted and 07c-1 delivers the split update for one instance; a producer with 4–8 moving stems watches the canvas reach a position seconds before the audio does; a mixer tuning a fly-by by hand notices first; the fix then needs both the remedy and a second amendment of her decision.

Sources read: docs/review/phase-05i/11-decider-r3.md (D-G1); docs/corpus/vorlaender-auralization.md (§15.3, L3952–3968); docs/BUILD_PLAN.md (AQ4, L109); docs/phases/phase-07c-1.md (condition 4, L60–67); docs/review/phase-05i/10-interrogator-file9.md (P05I-53/54); docs/PRD.md (FR-SIM-6, FR-SIM-7, NFR-3). The code files on the Read list were not opened; the position rests on the code facts as file 11 states them.
