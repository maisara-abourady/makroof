# Seat 4 — D-H1 and D-H2 (phase 05h session 2)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

`SEAT 4 POSITION — D-H1`

Corpus present (c1b171f). No persona assumption fell on this matter.

**1. Reading.** Which W_max ships with the blocking restore gate, given that the gate already fails on macOS with no diffuse solve at all (14 × 2.328–2.591 s = 32.6–36.3 s; redone), and whether n\*_max moves. Cues from my §4: *level and tone parity* (one W_max, E_b shared across modes and ears) and *per-mode rebuild headroom* (W1 per output mode from Phase 08). My R1 premortem ("the gate fails in binaural mode, Seat 5 sees it first") has arrived early: it failed in omni, and the cause is the non-diffuse 100 m / 96 kHz build, not the estimator. My J1 conditions still hold under every option (each keeps one W_max for all modes), so no cell reaches 3.

P-a/P-b, R-a…R-d and Q-a…Q-d: not my matter (Seat 1 and Seat 9 for P, Seat 1 and Seat 5 for R, Seat 5 for Q).

**2–4. Ranking, tension now, tension later.**

| option | label | now | later | what it costs me now / what it commits later phases to, and the undo |
|---|---|---|---|---|
| **W-a** keep 3.05 M, run the gate on three OSes, record the defect, 07c next | *prefer* | 1 | 1 | Now: the DRR random error I rated 1 in J1 stays (s = 0.3 cube SE 0.09 dB; s = 1 cube 0.36 dB, p95 ≤ 0.89 dB; layout 4 up to 1.33 dB), shared across modes, so parity holds. Later: (C) lands before Phase 08's goldens, so my golden condition (phase-07c 8) is met by order, not by tolerance; one (C) golden round, already scheduled. Undo: a parameter change. Shared debt (all W options): the Phase 08 heaviest-mode gate, run after (C), measures a restore without the solve that already fails on macOS in omni; AX38 4c's only remedy ((C) forward) is then spent. Evidence arrives in phase-08 scope 10. |
| **W-c** (C) before the gate, 05h blocked/split | *can live with* | 1 (2 if the switch waits for 07c) | 0 | Now: W_max ≈ 54–68 M would bring the s = 1 cube to ≈ 0.09 dB and layout 4 to ≈ 0.32 dB (×√(3.05/54) = 0.24; Eq. 11.21 scaling, heavy tails caveat), the best DRR outcome I can get. But if the switch itself (O14–O16) waits for 07c, the +3.87 dB AX16 error in layout 4 (≈ 4 jnd of G) stays in every output mode for another phase to fix a 0.36 dB random one: wrong order of magnitude, now 2. Later 0: no SE-derived tolerance ever enters a binaural golden. Undo: phase ordering (Seats 5, 7). |
| **W-e** Linux-enforced, macOS/Windows recorded | *can live with* | 1 at 3.05 M; 2 at W-b's value | 1 | At 3.05 M it is W-a with the Linux gate failing by 0.27–0.42 s and weaker cross-OS evidence; at W-b's value it carries W-b's SE cost. My "gate measures the heaviest mode" condition is met on Linux only; I accept the reading if it survives, provided the Phase 08 heaviest-mode restore is still *recorded* on all three OSes (I need the macOS binaural build cost before (C) re-derives W_max). |
| **W-b** re-derive on Linux (≈ 2.0–2.4 M), gate as W-a | *can live with* | 2 | 1 | A 24–35 % cut raises SE ×1.21 (1/√0.685 = 1.208, redone): s = 1 cube 0.36 → ≈ 0.44 dB and its p95 0.89 → ≈ 1.07 dB [Inferred, heavy tails], crossing the 1 dB jnd of G, my ±1 dB tail-level budget; layout 4 1.33 → ≈ 1.6 dB. It buys a pass on two OSes and no pass where the gate is worst, so it spends accuracy on nothing the ear gets. Later 1: reversed under (C) in the same scheduled golden round; but if Phase 08's capped-room goldens freeze before (C), their SE-derived tolerance freezes at the ×1.21 value. |
| **N-a** 1 024 stands | *prefer* | 0 | 0 | E_b shared across modes unchanged; W1 diffuse share 6.35–9.03 ms (macOS max 13.98 ms) leaves ≥ 11 ms of the 25 ms for Phase 08's per-mode W1 growth [Hyp, unmeasured]. |
| **N-b** raise to ≈ 1 792–2 816 | *can live with* | 1 | 2 | Now: SE in uncapped rooms falls from ≤ 0.086 dB to ≈ 0.065 / 0.052 dB (×√(1024/1792), ×√(1024/2816)), under 0.1 jnd either way; capped-scene SE rises (larger pilot, lower N_cap). Later 2: it spends the whole 25 ms diffuse share (linear scaling [Hyp]: 13.98 × 1.75 = 24.5 ms at the macOS max) before W1 is measured per output mode (AQ10: every mode from Phase 08), so the binaural W1 arrives with no diffuse headroom. Undo: a parameter change plus a golden round. |

**5. Evidence.** SE ∝ 1/√N: Vorländer §11.2.5, Eq. (11.21) (σ_L = 4.34√(A/(8πN r_d²)); Poisson hit counts; our scores are heavy-tailed, so the replicates, not the formula, are the evidence [corpus, Observed]. 1 dB jnd of G: Vorländer Table 6.1 [corpus]. Table 15.1's 700 ms / 3 s rows [corpus] (not reached by any option here). Gate arithmetic: file 1 §4 (14 × 2.063 = 28.9 s Linux; 14 × (2.063 + 0.099) = 30.3 s at 3.05 M; macOS 32.6–36.3 s with no solve) [from the measurement]. W-b formula: (2.143 − 2.0745)/2/16.4 ns = 2.09 M; (2.143 − 2.063)/2/16.4 ns = 2.44 M [redone, agrees]. E_b one solve per scene, bit-identical across modes and ears: AX39, AX44, phase-08 scope 5 and §5 "E_b parity" [plan ids]. My J1 conditions as carried: AQ10 amended, AX38 4c, phase-08 scope 10, phase-07c condition 8 [plan ids]. Phase 08's binaural (HRIR) early-part build cost at 100 m / 96 kHz: [Hyp], unmeasured; the researcher cannot source it, it is a Phase 08 benchmark. Diffuse-share scaling with n\*_max: [Hyp] linear.

**6. Conditions of acceptance.**
- W-b (2 → 1): (i) Phase 08's capped-room goldens are frozen only after (C), so the ×1.21 tolerance never enters a binaural golden; (ii) the SE and replicate p95 at both cubes and layouts 4/5 are re-reported from 30 replicates at the cut value, not from the 1/√N formula; (iii) the record states the cut does not cure macOS, so it is the "accept the smaller W_max" branch, not a cut "to pass" (Seat 2's line).
- W-e at W-b's value: as W-b, plus the three-OS recording of the Phase 08 heaviest-mode restore.
- W-c (2 → 1): the switch (O14–O16) lands in 05h at the provisional W_max with its goldens; only the gate waits.
- N-b (later 2 → 1): size from the worst-OS max (1 792, not 2 816), and raise it at (C)'s golden round, when W1 per output mode exists.

**7. Hand-offs.** Seat 5: the OS scope of the block (W-e's reading), the ratio, pluginval's watchdog semantics. Seat 2: the non-diffuse 100 m build cost and whether its reduction is Phase 07 / 07c / 10 work; name the remedy for a non-diffuse gate failure after (C) before phase-08 scope 10 runs. Seat 1: audibility of SE ×1.21 and of the N-b gain; P and R. Seat 9: which cube is the reference room. Seat 7: schedule cost of 07c next. Maisara (human): the FOR MAISARA reading of AX38 4c's OS scope if W-e is composed.

**8. Premortem.** If W-b ships, the s = 1 cube's replicate p95 crosses 1 dB and the gate still fails on macOS; Seat 1 reads it first in the O18 replicate report, and Phase 08 freezes binaural goldens in capped rooms with a tolerance that (C) then has to regenerate.

---

`SEAT 4 POSITION — D-H2`

**1. Reading.** Which case-bands have a certified reference now, and what Phase 08's binaural goldens inherit from an omni tail level that is gated for emitter 0 only (single-rung, uncertified) or not at all (emitter 1) in the six Phase 04 rooms, W1 and W2. Cue: *level and tone parity* is untouched (E_b is one solve, bit-identical across modes and ears, AX44); what is touched is the *absolute* tail level (DRR, and the tail's spectral tilt) that every mode inherits from omni. Two gaps matter to me: no emitter-1 case is gated at all (CS-NW+ e0, W1 e0, one pair per (A) and BRAS case), so the emitter-1 code path has no agreement check [from the packet]; and no per-band-α room is gated outside 500 Hz–2 kHz, so the tail's tilt at 63–250 Hz and 4–8 kHz rests on the band-independent-α (A) cases and the layouts 4/5 tracer check (AX37 (5.1) (ii)) only.

**2–4. Ranking and tension.**

| option | label | now | later | debt and undo |
|---|---|---|---|---|
| **G-a** consequence (≈ 225/560, 27/72) | *can live with* | 1 | 1 | Phase 08 goldens in the Phase 04 rooms, W1, W2 may freeze on an ungated E_b. A reference arriving later (phase-05i) that moves E_b by more than τ regenerates the binaural goldens and re-renders the Phase 08 listening pack: one golden round, not rework. Evidence arrives in phase-05i's agreement test. |
| **U-a** single-rung values reported, labelled | *prefer* | 0 | 0 | An alarm, not a gate: my §9 rule for metrics. |
| **U-c** not used | *can live with* | 1 | 0 | Throws away the only alarm on the rooms producers use. |
| **M-e** M-a now plus a committed order; 05i gates what is certified, the rest listed | *prefer* | 0 | 1 | Later 1 only if 05i lands after Phase 08's goldens. |
| **M-a** cheapest now, rest 05i | *can live with* | 0 | 1 | Same, without the order: risk the emitter-1 case is not first. |
| **M-c** nightly job | *can live with* | 1 | 1 | Feasibility is Seat 5's (RQ-H2-1); fine if it certifies before Phase 08 freezes. |
| **M-d** larger machine | *can live with* | 0 | 1 | A person's matter (Seat 7). |
| **M-b** all to 05i | *can live with* | 1 | 2 | Phase 08's binaural goldens then almost certainly freeze before any emitter-1 or outer-band reference exists; undo is a golden round plus a re-rendered listening pack after producers have heard it. |
| **B-a** AX46 now on certified classes, 100 m class's reference named | *prefer* | 0 | 0 | A bias propagates into every mode equally: parity holds, DRR is wrong in all of them; knowing it on three classes now beats not knowing. The 100 m class must be named (tracer or "not evaluated"), never implicit. |
| **B-b** defer | *can live with* | 1 | 1 | — |

**My priority order for M-e** (delivery terms): (1) one small Phase 04 room, both emitters, all 8 bands: it checks the emitter-1 path and a per-band-α room's outer bands in one run; (2) W1 e1 (the AQ10 room is also Phase 08's per-mode benchmark room); (3) the BRAS outer bands; (4) the 0.3 m wall case; (5) W2. Seats 1, 8 and 9 rank by audibility and use; mine is by what the binaural goldens inherit.

**5. Evidence.** E_b via `TailMatch`, one solve per scene, bit-identical across modes and ears: AX37 (5.3) (i), AX39, AX44, phase-08 scope 5 and §5 [plan ids]. Certified set and its gaps: the D-H2 packet and file 3's table [committed data, orchestrator to confirm per case-band]. Outer-band check limited to band-independent-α layouts: AX37 (5.1) (ii) [plan id]. Per-band-α room in the gated set: PR #27 m-10, met under G-a only at 500 Hz–2 kHz [from the packet]. τ = 0.25 dB = ¼ of the 1 dB jnd of G: AX42, Vorländer Table 6.1 [corpus]. No acoustic claim beyond these; nothing for the researcher from my seat.

**6. Conditions of acceptance.** G-a (1 → 0 now): the Phase 08 goldens in rooms with ungated case-bands carry "tail-level reference pending (D-H2)" in `tests/golden/CHANGELOG.md`, so a later move is read as a reference arriving, not a regression. M-b (later 2 → 1): phase-05i is sequenced before Phase 08's golden freeze, or Phase 08's goldens in those rooms are marked as above. M-a (→ 0/0): the first background run is a both-emitter case.

**7. Hand-offs.** Seat 2: whether a 2.25 m patch is a rung, and the 100 m class's reference. Seat 5: CI time and M-c feasibility. Seat 7: M-d's machine and cost; public wording at 27/72. Seat 1: whether an outer-band tail tilt error is audible; whether U-a misleads. Seat 9: which rooms first as references.

**8. Premortem.** If M-b wins, Phase 08 freezes binaural goldens in the Phase 04 rooms with emitter 1's tail level unverified, phase-05i's reference later moves it past τ, and the contractor reviewing the golden regeneration notices first, after Maisara has already listened to the Phase 08 pack on that level.

---

Files read: /home/user/makroof/docs/review/phase-05h/4-decider-convene-D-H1-D-H2.md, /home/user/makroof/docs/review/phase-05h/3-orchestrator-D-H1-D-H2-question.md, /home/user/makroof/docs/review/phase-05h/1-orchestrator-cpp-costs.md, /home/user/makroof/docs/phases/phase-05h.md, /home/user/makroof/docs/phases/phase-07c.md, /home/user/makroof/docs/phases/phase-08.md (scopes 5, 10; §5), /home/user/makroof/docs/BUILD_PLAN.md (AQ10, AX36–AX46), /home/user/makroof/docs/sessions/2026-11-10-phase-05h.md (Session 2), /home/user/makroof/docs/review/phase-05b2/45-seat4-R1-R3.md, 47-decider-board-answers-C1-Q2a-final.md, 51-decider-addendum-J1.md, 53-decider-J1-trigger-definitions.md, 54-interrogator-J1-triggers-round2.md, 55-seat1-confirm-clause-d.md, /home/user/makroof/docs/corpus/vorlaender-auralization.md (§11.2.5 Eq. 11.21, Table 6.1, Table 15.1). Nothing saved; the orchestrator saves this as docs/review/phase-05h/5-seat4-D-H1-D-H2.md.
