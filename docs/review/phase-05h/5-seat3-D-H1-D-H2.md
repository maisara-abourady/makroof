# Seat 3 (reverb renderer) — positions on D-H1 and D-H2 (phase 05h session 2)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

Files read: the convene file (4-decider-convene-D-H1-D-H2.md), 3-orchestrator-D-H1-D-H2-question.md, 1-orchestrator-cpp-costs.md (all sections), phase-05h.md §2–§5, §8, BUILD_PLAN §2 AQ10 (amended), AX36, AX38 4c, AX41–AX46, phase-07c.md §0, §3, §5, my own 45-seat3-R1-R3.md, decider files 47 §4, 51 §3–§4, 53 §1, interrogator 54, Seat 1 file 55, the session brief (Session 2 O15, O18, Constraints), and the corpus: Vorländer §11.2.5 (Eqs. 11.9, 11.18, 11.21), Table 6.1, Table 15.1. Corpus present (c1b171f).

---

## SEAT 3 POSITION — D-H1

**1. Reading.** Pin the gated cube, the "further rise", the realised-work ratio, W_max / n\*_max, and how a blocking gate that the *non-diffuse* 100 m build already fails on macOS is treated. Cues (my §4): **decay/level accuracy** (a fixed per-scene random level offset from the capped solve, AX40 fixed key; the SE rises with any work cut), and **cost** (the solve's share of the rebuild interval). Not a state-discontinuity matter: the solve never runs on the audio thread (AX38 (i)), so no option here touches my per-instance CPU measure at all; what moves is the tail level (criterion 2) and the rebuild interval (criterion 6).

**What my ~20 % trigger meant to protect** (file 45, [Hyp], mine). W_max was sized to a restore budget, and a margin taken for *measurement noise* on a CI runner buys no accuracy and is paid in SE: a cut of m raises SE by 1/√(1−m) (Vorländer §11.2.5, Eq. 11.9/11.21, 1/√N; redone: 20 % → ×1.118, 27 % → ×1.17, 35 % → ×1.24). At 20 % the cost at the s = 1 cube is ≈ +0.04 dB, 1/25 of the 1 dB G jnd (Table 6.1): inside my tolerance. Beyond it, layout 4 goes from 1.33 toward 1.6 dB and the cut stops being "noise absorption" and becomes audible level error bought for nothing. The data now say the margin is *not* noise: the non-diffuse build alone is 2.33–2.59 s on macOS (budget 2.143 s) and 2.063–2.075 s on Linux, so no W_max ≥ 0 passes macOS and (C) alone does not pass macOS either (14 × 2.328–2.591 = 32.6–36.3 s, redone). The trigger's own logic therefore says: **do not take the cut; the overrun belongs to the Phase 07 build (Seat 2), and the remedy the plan names is (C) forward.**

**2. Ranking per sub-choice.**

- **W (W_max and the gate):** W-a *prefer* · W-e at 3.05 M *can live with* · W-c *can live with* · W-b *can live with* (lowest) · W-e at W-b's value *can live with, worst of the set*.
- **P (gated cube):** P-a *prefer* · P-b *can live with*. Mostly Seats 1, 9, 5.
- **R ("any further rise"):** R-d *prefer* · R-c *can live with* · R-a, R-b *can live with* but rated 2 (see below). No veto.
- **Q (ratio):** touches me only under W-b or W-e-with-cut (it divides W_max there; under W-a it is an assertion costing no work). Q-b *prefer*, Q-d *can live with*, Q-c *can live with*, Q-a *can live with* (4 % of work given away for a count that is deterministic (D7) and measured ≤ 0.991). The value is Seat 5's.
- **N (n\*_max):** N-a *prefer* · N-b *can live with*.

**3. Tension now / 4. Tension later (debt).**

| option | now | later | what it costs me / commits |
|---|---|---|---|
| **W-a** keep 3.05 M, gate as written, defect recorded, (C) next, Phase 07 build named | **1** | **1** | Now: the (A) level debt as already accepted (s = 0.3 cube SE 0.092/0.075 dB; s = 1 cube 0.36 dB; layouts 4/5 0.13–1.33 dB), unchanged by this decision; the solve adds 58–162 ms per scene at pool size, 0.136 s at one thread (3.05 M × 44.7 ns, redone) — under Table 15.1's 700 ms row and Seat 6's 3 s. Later: commits phase-07c next (before Phase 08's goldens), which is the repayment I conditioned J1 on; one golden round under (C), already planned. Undo: nothing to undo. Evidence arrives: O18's gate record and 07c's W_max re-derivation. |
| **W-b** re-derive on Linux (≈ 2.0–2.4 M after the ratio) | **2** | **1** | Now: SE ×1.21 at 2.09 M (s = 0.3 cube ≈ 0.11 dB; s = 1 cube ≈ 0.44 dB; layout 4 ≈ 1.6 dB) bought for a Linux/Windows pass by construction while macOS still fails, so (C) is pulled forward anyway: the cut buys nothing lasting. It also cuts the unmoved emitter (joint cap) and every capped one-end case in layouts 4/5. Later: the lower value is frozen into every tail-level golden (O16), the D5 n\*/N golden and the replicate set until (C)'s golden round; if Phase 08 freezes capped-room goldens before 07c, their SE tolerance is 21 % wider. Undo: one parameter change plus the golden round (C) owes anyway. |
| **W-c** (C) first, 05h blocked/split, (A) never ships | **1** | **1** | Now: the switch itself (AX16 +3.87 / −1.17 dB in layouts 4/5 — 3 × the largest (A) SE) stays unshipped one phase longer; every golden, the listening pack and any Phase 08 work keep the known-wrong tail level meanwhile. Not a public debt (pre-release), but it also removes 07c's own design input: condition 5.2's interim level is "the (A)-budget estimate", and D-C1's step size is measured from (A) to final; with no (A) those decisions have no data. Later: W_max set once from the background budget (good: one golden round instead of two). Undo: a phase reorder (Seat 7). Ordering (07c depends on 05h `done`) is Seat 5/7's. |
| **W-e** Linux-enforced, macOS/Windows recorded, at 3.05 M | **1** | **1** | Same level cost as W-a. Whether this is a loosening is Seat 5's; the AX38 4c reading is `FOR MAISARA`. I would accept it if that reading survives, with (C) still brought forward on the recorded macOS failure (otherwise see next row). |
| **W-e at W-b's value** | **2** | **2** | The cut *and* a green Linux gate: nothing then forces (C) forward, so the ×1.21 level debt persists to 07c's normal date (before the beta) instead of next phase. The worst pairing for criterion 2. |
| **P-a** s = 0.3 (floor via clause (d), O18 replicates) | 0 | 1 | The gate's trigger stays meaningful (floor met, U silent); the s = 1 cube is still reported, so its SE is visible to me either way. Debt: rests on O18's 30 replicates passing; if they fail, Raise item 1 fires late rather than now. |
| **P-b** s = 1 (floor already not met; finding escalated once) | 1 | 1 | Gating the scene where the level error is worst watches the scene that matters to criterion 2, but the floor is pre-failed, so every later rise is argued against a scene already past 0.33 dB. Under W-b it also yields the smaller W_max (Linux 2.09 vs 2.44 M). Which cube is cost-worst is Seat 9's. |
| **R-a** > 1 SD of the replicate distribution | 2 | 2 | The replicate SD of the error ≈ the achieved SE (≈ 0.36 dB at s = 1); a "rise" of 1 SD lets p95 go from 0.89 to ≈ 1.25 dB — past the 1 dB G jnd (Table 6.1) — without firing. That reads as "a rise of a full jnd is not a rise". |
| **R-b** > 2 SD | 2 | 2 | Twice as permissive (a ≈ 4× work cut before firing). |
| **R-c** fixed ≥ 0.05 dB | 1 | 1 | At the s = 1 cube 0.05 dB on 0.36 dB is a 13 % SE rise ≈ a 24 % work cut: close to my trigger, sensible there. At the s = 0.3 cube it is a 54 % SE rise (58 % work cut) before firing: scene-dependent in work terms; and it escalates to Maisara on rises of 1/20 jnd that no one hears. |
| **R-d** only a crossing of 0.33 dB SE or 1 dB p95 | 0 | 0 | The two lines are the ones already in the plan and the only ones with a perceptual meaning (1 dB = 1 jnd of G). At the s = 1 cube (p95 ≤ 0.89 in the prototype) the 1 dB line fires at roughly the same work cut as R-c; at s = 0.3 nothing fires until it should. p95-of-30 is a noisy statistic: implementability is Seat 5's. |
| **Q-a** 1.05 / **Q-b** 1.01 / **Q-c** 1.00 / **Q-d** 1.02 | 1 / 0 / 0 / 0 | 0 each | Only under W-b: Q-a gives away 4 % of work (≈ 2 % SE) against a deterministic count measured ≤ 0.991 (prototype ≤ 1.009). Under W-a none of them costs me anything. Value: Seat 5. |
| **N-a** 1 024 stands | 0 | 1 | W1 diffuse share 6.35–9.03 ms (max 13.98) of 25 ms: 1.8–3.9× headroom kept for Phase 08's per-mode W1 and the Phase 10 cache question. Debt: one-end placements stay at up to 0.124 dB (1/8 jnd). |
| **N-b** raise to ≈ 1 792–2 816 | 1 | 2 | Gain: in uncapped rooms N already exceeds N_need (W1: N_need 515, N 1 024, SE 0.082/0.063 dB at target); the raise buys ≈ 0.02–0.03 dB (≤ 1/30 jnd). Cost [Inferred from AX41's rule and file 1's W_pilot 1.70 M at 1 024, ≈ 1 656 evaluations per history]: at the capped cubes the pilot grows to ≈ 2.97–3.07 M, N_cap falls from 2 624–2 688 to ≈ 1 792–1 856, so SE rises ×1.19–1.21 (s = 0.3 cube 0.092 → ≈ 0.11 dB, s = 1 cube 0.36 → ≈ 0.43 dB) — the same cost as the W-b cut, from the other side; W1 share [Hyp linear] 13–21 ms Linux, macOS max 24.5 ms at 1 792 and 38 ms at 2 816 (over the 25 ms). Later: a second parameter change if (C) re-derives it; Phase 08's per-mode W1 starts with no diffuse headroom. The orchestrator can verify the N_cap figures by one run. |

**5. Evidence.**
- SE ∝ 1/√N: `docs/corpus/vorlaender-auralization.md` §11.2.5, Eqs. (11.9), (11.21) [corpus]; stated for Poisson hit counts; our scores are heavy-tailed (VOV 0.13–0.44), so O18's replicates, not the formula, are the evidence — agreed with the packet. Arithmetic redone: ×1.208 at 0.685.
- 1 dB jnd of G, 500–1000 Hz: Table 6.1 [corpus]. The Table says nothing about other bands.
- 700 ms / 3 s rows: Table 15.1 [corpus], translational movement only (AX38 4c's caveat stands).
- All times, ns per evaluation, restore worst-of-10, flags, W_pilot: file 1 [Measured, code, CI run 42846229834]. Formula values (Linux 2.09 / 2.44 M, Windows 5.96–6.10 M, macOS < 0) redone and agree with the decider's working.
- My 20 % trigger and the reading of what it protects: file 45 §6 [Hyp, mine]. Its "accept the smaller W_max" branch assumed a noise-shaped margin; that assumption fell on file 1's data (the overrun is the non-diffuse build).
- Pilot/N_cap arithmetic for N-b: [Inferred] from AX41's text; the W1-share scaling: [Hyp] linear. Researcher/orchestrator: not needed beyond one run.
- Per-evaluation cost taken from the n\*_max-stopped scenes, not the flutter pool figure: PR #27 m-2 (from the record), correct in W-b's working.

**6. Conditions of acceptance (every 2).**
- **W-b → 1/1:** only if the gate is enforced on an OS the cut can actually make pass (Linux), (C) is still brought forward next phase on the recorded macOS failure (so the lower value lives one phase, not until the beta), and the SE cost is printed per gated scene and in layouts 4/5 beside the AX16 error it replaces. Without the "(C) next" clause it stays 2.
- **W-e at W-b's value → 1/1:** add "(C) forward next phase regardless of the Linux result". Then it equals W-e at 3.05 M in cost to me, and the cut is pointless; so prefer 3.05 M.
- **R-a / R-b → 1:** add R-d's lines as a floor ("…or any crossing of 0.33 dB SE / 1 dB p95"), so a jnd crossing always fires. Then R-a is R-d with extra noise.
- **N-b → 1/1:** cap the raise so that the capped cubes' N does not fall (i.e. stop the pilot by work before n\*_max binds there) — which is not what AX41's rule does, so in practice: keep N-a.

**7. Hand-offs.**
- Seat 5: the gate's OS scope (W-e reading), pluginval's watchdog semantics (RQ-H1-1: if the 30 s is per restore the whole formula changes), the ratio's value, R-d's p95 implementability, and whether a shared macOS runner's 1.50–2.59 s spread is the plugin or the runner (RQ-H1-2; my §7 "name the machine" rule says it is not a named machine, but worst-of-10 is settled).
- Seat 2: the non-diffuse 100 m / 96 kHz build (2.03–2.17 s best of 3 here vs 1.884 s recorded) is the finding W-a names; whether it is Phase 07/07c/10 work.
- Seat 1: audibility of every SE figure above; which cube; whether R-d's lines are its.
- Seat 9: which α/s is the real cost-worst box.
- Seat 6/8: the 2.3–2.6 s wait and "settling" until (C).
- Seat 7: the schedule cost of 07c next; a CI block red by design.
- Seat 4: capped-room binaural goldens' tolerance if Phase 08 freezes before 07c.

**8. Premortem.** W-b wins: W_max is cut to ≈ 2.1 M, macOS still fails so (C) is pulled forward anyway, and meanwhile the listening pack's layout-4 scene carries ≈ 1.6 dB of random tail-level error; Maisara hears a level that is off by more than a jnd in the "switched tail sounds natural" check and attributes it to the switch rather than the cap — Seat 1 notices first, in the pack, and the cut repaid nothing.

---

## SEAT 3 POSITION — D-H2

**1. Reading.** Which case-bands of the agreement (AX43), regression (AX45) and bias (AX46) gates have a certified reference now, what single-rung references may be used for, how the rest are produced. Cue: **decay/level accuracy** — AX45's "uniform rooms unchanged" is my check that the switch does not move the tail level where AX16 was already right; 27 of 72 case-bands are gated today, all but three of them synthetic (A) boxes. The rooms the public wording and the listening pack rest on (`stone_box` e1, the small room, W1 e1) have no ΔL_ref.

**2. Ranking.** G-a: forced; its consequence *can live with*. U-a *prefer* / U-c *can live with*. M-e *prefer* / M-a *can live with* / M-c, M-d *can live with* (not mine to cost) / M-b *can live with* (lowest). B-a *prefer* / B-b *can live with*.

**3–4. Tension now / later.**

| option | now | later | cost to me / debt |
|---|---|---|---|
| **G-a** consequence (≈ 225/560, 27/72) | 1 | 1 | Now: the regression claim for uniform rooms rests on the 24 (A) s-cases plus W1 e0 mid-bands; `stone_box` and the small room — the uniform rooms a producer actually reaches — are reported only, so "nothing audible changed" (AX45 (iii)) is unverified where it will be heard. The mixed-α Phase 04 rooms keep M-2's tracer check (±1 dB class), so a gross matching error there is still caught. Later: Phase 08's binaural goldens (Seat 4) and the listening pack run through Phase 04 rooms whose e1 tail level is gated against nothing; undo = producing the references (hours per case) and one golden round in 05i. |
| **U-a** reported only, labelled | 0 | 0 | A single-rung value at 2.25 m still catches a > 1 dB matching error before the pack is listened to; the label prevents the pass reading. The ℓ-sensitivity at reference positions is ≤ 0.33–0.37 % in the certified cases (≈ 0.015 dB), 4.75–8.7 % near walls (AX36 (c)): a z printed beside it is informative, never a gate. |
| **U-c** not used | 1 | 1 | Throws away the only early warning for the six Phase 04 rooms' e0; the pack then goes to Maisara's ears with no number beside it. |
| **M-e** cheapest now + committed priority order + "05i gates what is certified, rest reported and listed" | 0 | 1 | Debt: 05i carries the remainder; nothing is dropped by the implementer. |
| **M-a** cheapest now, rest 05i, no order | 1 | 1 | Without an order the implementer chooses which references exist at 05i's gate, which the brief forbids. |
| **M-b** all to 05i | 1 | 2 | The pack and any Phase 08 work proceed longer on unverified Phase 04 levels; 05i's compute grows. |
| **M-c** nightly job / **M-d** larger machine | 1 / 1 | 1 / 1 | Feasibility and cost are Seats 5 and 7's (RQ-H2-1); either serves me if it delivers the order below. |
| **B-a** bias now on the certified classes; 100 m class's reference named | 0 | 1 | A systematic error in the estimator is exactly what the goldens would freeze; 1 % is 0.043 dB, far under τ, so a pass on three classes says something real. For the 100 m class the only reference is the tracer (AX39: (f) − tracer = −0.009 dB), whose own statistical error at 100 m is not certified to ≤ 0.3 %: record "not evaluated (reference pending)" unless Seat 2 certifies the tracer's SE there — and 100 m is the class where my level error is random, not biased, so the loss is small. |
| **B-b** defer | 1 | 1 | The goldens freeze with no systematic-error check at all. |

**Priority order I propose for M-e (in my terms, audibility of a tail-level error):** (1) the AX45 uniform rooms at both rungs — `stone_box` e0 (certify) and e1, the small room, W1 e1 — because the public wording and the "nothing audible changed" claim rest on them; (2) the six Phase 04 rooms, e1, and certification of e0 (the listening pack and Phase 08's goldens; Seats 4, 8); (3) W2 both emitters (the AQ10 fallback workload); (4) the BRAS pairs' 63–250 Hz and 4–8 kHz bands (Table 6.1's G jnd is stated only for 500–1000 Hz; the mid bands are gated; the band edges are where I hear "boomy" or "dull", but no corpus jnd supports ranking them above rooms producers use) [Hyp on ordering]; (5) CS-NW+ e1 and the 0.3 m wall case last (GA-limited near walls, no accuracy claim made there, AX44).

**5. Evidence.** AX36 (c) ℓ changes [plan id, committed data]; AX39 100 m tracer check [plan id]; Table 6.1 [corpus]; τ = 0.25 dB and 1 % ≈ 0.043 dB [AX42, AX46; 10·log10(1.01) redone]. The ordering above is my judgement [Hyp], for Seats 1, 8, 9 to confirm.

**6. Conditions (every 2).** M-b → 1/1 if 05i starts with the order above and the pack README names, per room, "tail level reported against an uncertified reference" until then.

**7. Hand-offs.** Seat 2: the rung status of 2.25 m patches and the tracer as a 100 m bias reference. Seat 4: Phase 08 goldens in ungated rooms. Seat 7: wording "the same material on every surface" with 27/72 gated; M-d's cost. Seat 5: CI time for 225 gated + printed rest; M-c feasibility. Seats 1, 8, 9: the priority order.

**8. Premortem.** The `stone_box`/small-room references are never produced, 05i gates the 27 synthetic case-bands and calls AX45 passed; a producer's uniform stone room is the one place the switch moved the tail by more than 0.25 dB, and Maisara's "nothing audible changed" listening item in a uniform room is where it is heard first.
