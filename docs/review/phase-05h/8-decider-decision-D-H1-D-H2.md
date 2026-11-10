# Decider — decision round for D-H1 and D-H2 (phase 05h session 2, `/fix-plan` step 3c)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

Save as `docs/review/phase-05h/8-decider-decision-D-H1-D-H2.md`. Corpus revision `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d` (`/home/user/makroof/docs/corpus/SOURCE_COMMIT`, 14 files). The PRD digest of the convening round (`4-decider-convene-D-H1-D-H2.md`) stands unchanged; one line is added to it: **the PRD is silent on CI runner choice, on pluginval's watchdog and on which OS a block is enforced on; those are plan defaults and board answers, and the one of them that cites her acceptance (AQ10 amended / AX38 4c) is read below as `FOR MAISARA`.**

Files read this round, in full: `5-seat1…5-seat9-D-H1-D-H2.md` (Seat 6: D-H1 only), `5-researcher-RQ-H1-H2.md`, `6-orchestrator-K20-certified-listing.md`, `7-orchestrator-split-timer-K23.md`, `10-orchestrator-clause-d-replicates.md` (the coordinator's late input; K6 now known), `1-orchestrator-cpp-costs.md`, `docs/phases/phase-05h.md`, `docs/phases/phase-07c.md`, `docs/BUILD_PLAN.md` §0 rows 05h/06/07 and §2 AQ10, AX36–AX46, `docs/sessions/2026-11-10-phase-05h.md` Session 2, `docs/board/README.md` "Who answers Maisara's questions", `docs/PRD.md`, corpus Vorländer Table 6.1 (L2056–2066), §11.2.5 (L3054–3117), Table 15.1 (L3959–3966), `.github/workflows/ci.yml` (pass-marker lines 27–65, 483–521, from the code). `9-orchestrator-agreement-results.md` is noted (D-H3's two findings) but not decided here, as instructed.

---

## D-H1 — the margin, the two OPEN premises, W_max / n\*_max, the blocking gate

### Knowledge inventory (final)

| id | what must be known | source | status |
|---|---|---|---|
| K1 | ns per image evaluation at pool size / one thread, per OS | file 1 §3 (code/measurement, run 42846229834) | known |
| K2 | worst-of-10 non-diffuse restore per OS at the cubes, 96 kHz; the macOS min–worst spread | file 1 §4 | known |
| K3 | diffuse solve per scene at 3.05 M, per OS (min/median/max) | file 1 §3 | known |
| K4 | the 2.143 s per-restore budget and its basis | AQ10 amended / AX38 4c (her acceptance 2026-11-10); researcher F1–F6 (read, high): pluginval v1.0.4's `--timeout-ms` default 30 000 ms is an **inactivity** watchdog reset by every log or `expect`; the restoration test's 14 restores each end in an `expect`; a timeout fails the run; CI passes 120 000 ms; pluginval restores the default scene | **known, premise corrected**: "14 × t_restore ≤ 30 s" is a project convention 14× stricter than the tool; whether it stands is decided below (`FOR MAISARA H1-F1`) |
| K5 | realised work / W_scene at the gated scenes; the count's determinism | file 1 §2: 0.935 / 0.991 / 0.986; prototype ≤ 1.009; D7 | known; W_max does not move (below), so the measured values are the pre-registration input |
| K6 | Seat 1's floor per cube on the C++ shipping rule, 30 disjoint replicates | file 10: s = 0.3 p95 0.250 / 0.178 dB, SE median 0.117 / 0.115 dB → **met via (d)**; s = 1 p95 0.701 / 0.810 dB but SE 0.381 / 0.384 dB → **not met**; flutter met via (a) | known |
| K7 | W1 diffuse share at n\*_max 1 024 | file 1 §3: 7.65 / 9.03 (max 13.98) / 6.35 ms ≤ 25 ms | known; the linear scaling to a larger n\*_max stays [Hyp] and is not needed (N-a) |
| K8 | SE scales as 1/√N | Vorländer §11.2.5, Eqs. (11.9), (11.21) (L3062, L3089–3090): σ_L ∝ √(A/N), Poisson hit counts | known, used for direction only (ill-informed risk stated: our scores are heavy-tailed, VOV 0.08–0.24; the replicates of file 10 are the evidence) |
| K9 | G jnd 1 dB, 500–1000 Hz | Vorländer Table 6.1 (L2060) | known |
| K10 | Table 15.1's 3 s row and its condition (translational movement > 1 m) | Vorländer Table 15.1 (L3966) | known |
| K11 | Phase 07's 1.884 s build vs 2.03 / 2.17 s now | BUILD_PLAN §0 row 07; file 1 §4 | known |
| K12 | whether the macOS worst-of-10 measures the plugin or the runner | researcher F9 (public-repo runners: Linux/Windows 4 vCPU 16 GB, macOS 3 vCPU M1 7 GB; file 7 §2 confirms the repo is public), F10–F11 (cloud-VM CV 0.03–100 %, Linux runner low-noise; conditions differ), F12 **not found** for macOS | **recorded as absent**: no macOS base rate exists; the project's own replicates govern (file 1 §4: macOS min 1.50 / worst 2.59 s within one run; Windows cube worst 1–2.2 % run to run, flutter 9 %) |
| K13 | Seat 6's 3 s per emitter (one-thread basis) and its per-scene correction | Seat 6 file 5 §"My 3 s check" | known as a seat criterion; met: 3.05 M × 44.7 ns = 0.136 s |
| K14 | C++ "work" definition (Q-3); N equal across OSes with high probability, not by construction (m-3) | file 1 §5; review PR #27 | known |
| K15 | (C) as written does not pass the gate on macOS | derived: 14 × 2.3277 = 32.59 s, 14 × 2.5912 = 36.28 s > 30 s (file 1 §4; redone by Seat 5 and researcher F8) | known |
| K16 | how long hosts tolerate a blocked `setStateInformation` | F13 (VST3 `setState` on the UI thread), F14 (Windows "not responding" after 5 s), F15 (Apple tools report hangs > 250 ms; no termination), F16 host-specific **not found** | **recorded as absent** for hosts; the OS thresholds bound the severity |
| K17 | OS scope of the restore block | AX38 4c text (memory block "gated on Linux, recorded on macOS and Windows until Phase 13"; the restore block names no OS) | read below as `FOR MAISARA H1-F2` |
| K18 | what the non-diffuse 100 m / 96 kHz restore spends its time on | file 7 §1 (split timer, from the code/measurement): unit-decay synthesis (`BandNoiseGenerator` ctor 956 ms + `make` × 2 = 2 182 ms) = 3.14 of 3.29 s ≈ 95 %; ISM + matching + mix 147 ms; at 48 kHz 1.32 s total | known; Seat 2's attribution confirmed |
| K19 | `ci-ok` saves the pass marker only on a fully green run (a by-design red disables the fingerprint skip) | `ci.yml` L27–31, L483, L508–521 (from the code) | known |
| K20 | 14 = the count of non-bypass automatable parameters | researcher F5 (`parameter_ids_v1.json`, 14 ids) | known |

No load-bearing item is uninformed. K12 and K16 are absent from literature and are recorded as such; the decision below does not rest on either (it rests on the worst-of-10 rule, the OS thresholds and the register).

### Tension map, D-H1 (now / later; each cell the seat's own words; `(rfc)` = read from the seat's conditions of acceptance, the option appeared in the round)

**W — W_max and the gate.** W-x (Seat 5's variant, §2 of its file) = W_max 3.05 M pinned; the gate implemented on all three OSes as a strict check with a **defect register** in plan text (per listed OS/scene: the recorded value, the remedy, the closing phase), a **growth bound** on listed entries (median-of-10 restore ≤ 1.10 × the recorded median), per-OS min/median/worst and the 14× figure in the job summary; 07c forward next; the non-diffuse build named as a separate finding.

| seat | W-a (3.05 M, gate as written, red recorded) | W-b (≈ 2.0–2.4 M, gate as written) | W-c ((C) first; 05h split) | W-e (Linux-enforced, others recorded; 3.05 M) | **W-x** (register + growth bound; 3.05 M) |
|---|---|---|---|---|---|
| 1 | 2 / 1 "my standing J1 cell … W-a brings (C) soonest" | 2 / 2 "a cut that buys nothing I measure" | 1 / 1 "the switch waits a phase" | 2 / 1 "= W-a on my measures" | **2 / 1 (rfc)**: "I accept W-e … only at 3.05 M, or with '(C) next phase' written in regardless"; both hold in W-x |
| 2 | 0 / 1 "no SE cost … the finding gets a remedy" | 2 / 2 "a cut 'to pass the gate' … no W_max ≥ 0 protects anything" | 1 / 1 "moves the red gate to 07c rather than curing it" | 1 / 1 "changes which OS is enforced, nothing in my measures" | **0 / 1 (rfc)**: W-a's rating with its §6 condition (the finding names `tail::BandNoiseGenerator` and routes a remedy by name), written in below |
| 3 | 1 / 1 "the solve adds 58–162 ms … commits phase-07c next" | 2 / 1 "SE ×1.21 … bought for a Linux/Windows pass while macOS still fails" | 1 / 1 "the switch … stays unshipped one phase longer" | 1 / 1 "same level cost as W-a … with (C) still brought forward" | **1 / 1 (rfc)**: W-e's condition "(C) still brought forward on the recorded macOS failure" holds |
| 4 | 1 / 1 "parity holds … (C) lands before Phase 08's goldens" | 2 / 1 "p95 … crossing the 1 dB jnd of G" | 1 (2 if the switch waits) / 0 | 1 / 1 "provided the Phase 08 heaviest-mode restore is still recorded on all three OSes" | **1 / 1 (rfc)**: W-x records all three OSes on every run |
| 5 | **2 / 2** "a required check red by design … kills the signal" | 2 / 2 "a block that flakes … turns timing noise into 'defects'" | 1 / 2 "the (C) W_max pinned before the … bounce record exists" | 2 / 2 "right pattern, wrong placement" | **1 / 1** (own rating) "the macOS result is a defect on the register, not a red; `ci ok` stays meaningful" |
| 6 | 1 / 1 "the red gate is internal and says the true thing" | 1 / 1 "what it buys the user: nothing" | 1 / 1 if split; 1 / 2 if blocked whole | 1 / 2 "enforced on the one OS no customer runs" | **1 / 1 (rfc)**: its three W-e conditions (07c next regardless; macOS/Windows records to Maisara against 1/3/10 s; re-enforced on all three OSes at Phase 13) are written in below |
| 7 | **2 / 2** "a red blocking check … masks every other macOS assertion" | 2 / 2 "some flake rate … each flake a 'defect'" | 2 / 2 "buys nothing on macOS" | 1 / 1 (W-e′: "enforced where it passes … macOS recorded, phase-13 named") | **1 / 1 (rfc)**: W-e′ at 3.05 M with the Linux entry listed; its W-a conditions (a red masks nothing; the ordering knot written; the macOS entry has an owner phase or an end date) all hold under the register |
| 8 | 1 / 1 "W-a names that build as the finding, which is the wait she actually feels" | 1 / 1 "a precision price for nothing she can hear" | 2 / 1 "what W-c delays is the switch" | 1 / 2 "approved in one room, heard in another" | **1 / 1 (rfc)**: "a recorded macOS failure carries the same remedy ((C) forward) … and Phase 13 enforces it on macOS before beta" |
| 9 | 0 / 1 "for validation nothing changes" | 1 / 2 "buys nothing on macOS" | 1 / 1 "the switch … waits one phase" | 0 / 1 "same as W-a for my seat" | **0 / 1 (rfc)**: as W-e at 3.05 M |
| max / sum | 2 / 21 | 2 / 29 | 2 / 21 (split; 24 if blocked whole) | 2 / 22 | **2 / 17** |

**P — the gated cube.** P-a′ (mine, step 4) = P-a plus Seat 1's condition: the s = 1 cube's SE and replicate p95 are reported in the margin report beside the gated cube's, a replicate p95 > 1 dB there is escalated like a gated scene, and (Seat 9's P-b condition, carried over) any finding about it states that it is a bound no preset approaches.

| seat | P-a (s = 0.3) | P-b (s = 1) | **P-a′** |
|---|---|---|---|
| 1 | 1 / 2 "my watchdog on W_max is inert while the s = 1 cube's p95 crosses 1 jnd in the reported set with no escalation path" | 1 / 1 "the escalation's attention cost, not audibility" | **1 / 1 (rfc)**: "P-a later 2 → 1: the s = 1 cube's SE and p95 are reported … and a p95 > 1 dB there is escalated like a gated scene" |
| 2 | 0 / 1 "validates the cost-worst realistic box" | 1 / 1 "a known floor failure … where any rise threshold is noisiest" | 0 / 1 |
| 3 | 0 / 1 "the gate's trigger stays meaningful" | 1 / 1 "the floor is pre-failed" | 0 / 1 |
| 4 | 0 / 0 `NOT MY MATTER` | 0 / 0 | 0 / 0 |
| 5 | 1 / 1 "s does not enter [the build]" | 1 / 1 "every later rise is an escalation" | 1 / 1 |
| 6 | 0 / 1 "a test box, never a preset; … U silent" | 1 / 1 | 0 / 1 |
| 7 | 0 / 1 | 1 / 1 "it also picks the slower restore" | 0 / 1 |
| 8 | 0 / 1 "P-a is the one a default might resemble" | 1 / 1 "an escalation about a non-room" | 0 / 1 |
| 9 | 0 / 0 "the realistic cost-worst closed room" | 1 / 1 "a bound, not a room … Lambert 'hardly ever real'" | 0 / 0 |
| max / sum | 2 / 10 | 1 / 16 | **1 / 9** |

**R — "any further rise".** R-e (Seat 1's) = R-d's lines escalate (SE crossing 0.33 dB, replicate p95 crossing 1 dB) plus any rise of the fixed-key SE ≥ 0.05 dB or of the replicate p95 ≥ 0.10 dB **recorded** in the margin report, not escalated.

| seat | R-a (> 1 SD) | R-b (> 2 SD) | R-c (≥ 0.05 dB escalates) | R-d (line crossing) | **R-e** |
|---|---|---|---|---|---|
| 1 | 1 / 1 "a noise test" | 1 / 1 "lets the p95 cross 1 dB without firing" | 1 / 1 "escalations nobody can hear" | 0 / 1 | **0 / 0** (own) |
| 2 | 1 / 1 | 0 / 0 (prefer) | 1 / 1 "insensitive to a real variance regression" | 1 / 1 "collapses the clause into the floor itself" | **1 / 1 (rfc)**: R-d's rating; the record adds nothing it rated |
| 3 | 2 / 2 "a rise of a full jnd is not a rise" | 2 / 2 | 1 / 1 "escalates … on rises of 1/20 jnd" | 0 / 0 "the only [lines] with a perceptual meaning" | **0 / 0 (rfc)**: R-d's lines, no 1/20-jnd escalation |
| 4 | 0 / 0 NMM | 0 / 0 | 0 / 0 | 0 / 0 | 0 / 0 |
| 5 | 1 / 1 "a never-regenerate golden" | 1 / 1 | 0 / 1 | 0 / 1 "cheapest" | **0 / 1 (rfc)**: both quantities already recorded in O18 |
| 6 | 1 / 1 | 1 / 1 | 1 / 1 | 0 / 1 "a crossing changes what the producer sees" | **0 / 1 (rfc)**: "every rise should be recorded; only the crossing escalates" is R-e verbatim |
| 7 | 1 / 2 "fire about one time in six" | 1 / 1 | 0 / 0 | 0 / 1 | **0 / 1 (rfc)**: R-d's cost; the record is free |
| 8 | NMM | — | — | — | 0 / 0 |
| 9 | 1 / 1 | 0 / 1 | 0 / 0 | 0 / 1 "degenerates under P-b" (moot under P-a′) | **0 / 1 (rfc)** |
| max / sum | 2 / 14 | 2 / 12 | 1 / 9 | 1 / 7 | **1 / 6** |

**Q — the realised-work ratio.** | seat | Q-a 1.05 | Q-b 1.01 | Q-c 1.00 | **Q-d 1.02** |
|---|---|---|---|---|
| 1 | 0 / 0 | 0 / 0 | 0 / 0 | 0 / 0 |
| 2 | 0 / 1 "buys nothing against a deterministic count" | 0 / 1 | 0 / 2 "brittle" | **0 / 0** |
| 3 | 1 / 0 "4 % of work given away" | 0 / 0 | 0 / 0 | 0 / 0 |
| 5 | 1 / 1 "loose" | 1 / 1 "no headroom for a scene added later" | 1 / 2 "a benign 0.5 % scatter becomes a 'defect'" | **0 / 1** "above every observed value with ≈ 1 % headroom" |
| 6 | 0 / 0 | 0 / 0 | 0 / 0 | 0 / 0 |
| 7 | 1 / 0 | 0 / 1 | 2 / 2 "red by design" | **0 / 0** |
| 4, 8, 9 | 0 / 0 (NMM / Seat 5's) | | | |
| max / sum | 1 / 5 | 1 / 4 | 2 / 9 | **1 / 1** |

**N — n\*_max.** | seat | **N-a 1 024** | N-b (1 792 / 2 816) |
|---|---|---|
| 1 | **0 / 0** | 2 / 1 at 1 792; **3 / 1 at 2 816** "a shipped level error I expect producers to hear" |
| 2 | 0 / 0 | 1 / 1 "at capped scenes it is pure overhead" |
| 3 | 0 / 1 "one-end placements stay at up to 0.124 dB" | 1 / 2 "the same cost as the W-b cut, from the other side" |
| 4 | 0 / 0 | 1 / 2 "the binaural W1 arrives with no diffuse headroom" |
| 5 | 1 / 1 "44 % headroom" | 2 / 1 "0 % headroom on the worst observed value" |
| 6 | 0 / 0 | 0 / 1 |
| 7 | 0 / 0 | 1 / 1 "a gamble on the scaling" |
| 8 | NMM | — |
| 9 | 0 / 0 | 1 / 1 |
| max / sum | **1 / 3** | 3 (2 816) / 2 (1 792) |

### Minimum-tension working

1. **Bounds.** X1–X3 dropped at convening (median as margin input; re-scoping the gate without the move; time cap / range narrowing). No option on the table breaks a PRD hard constraint; none makes scene-specific `src/sim` logic (NFR-8: the gated cube is a test scene). W-x's growth bound is **not X1**: X1 was the median as the *input that sizes W_max*; W-x keeps worst-of-10 as that input (the formula was evaluated on worst-of-10 and is negative on macOS) and uses the median only as the *growth detector* on an already-listed defect.
2. **Veto-grade.** N-b at 2 816 (Seat 1: 3 / 1) dropped. Q-c, R-a, R-b, M-c-live carry no 3 but are dominated below.
3. **Worst-off seat.** W: every option's maximum is 2; no W option can go below 2 while the (A) value ships (Seat 1's standing J1 cell; W-c removes it but is 2 / 2 for Seat 7 and 2 now for Seat 8). P: P-a′ max 1 (P-a 2, P-b 1). R: R-c, R-d, R-e max 1. Q: Q-a, Q-b, Q-d max 1. N: N-a max 1.
4. **Compose.** One variant composed by me: **P-a′** (Seat 1's P-a condition; raises no seat above 1). W-x and R-e are seats' own variants, read from the others' conditions and marked `(rfc)`; the interrogator checks each reading.
5. **Sum.** W-x 17 < W-a 21 = W-c 21 < W-e 22 < W-b 29. P-a′ 9 < P-a 10 < P-b 16. R-e 6 < R-d 7 < R-c 9. Q-d 1 < Q-b 4 < Q-a 5. N-a 3.
6. **Reversibility.** W-x: a plan edit per register entry; the W_max pin is undone at (C)'s golden round, which every option owes. P-a′: a pin edit. R-e, Q-d, N-a: one constant each.
7. **Decide:** W-x, P-a′, R-e, Q-d, N-a.

### DECISION D-H1 (plan text for the plan-editor; applied with the `FOR MAISARA` answers H1-F1–H1-F3 once they survive)

**(i) AX38 4c pin of the gated closed low-α cube.** "The gated closed low-α cube is `cube100_lowalpha0.05_s0.3` (`tools/validation/phase05b2_dt1.py` `_joint_cases()`): 100 × 100 × 100 m, α 0.05 and s 0.3 on every face, listener (50, 30, 1.7) m, emitters (45, 70, 2) and (55, 70, 2) m, 96 kHz; `ismFallback` false on both emitters, asserted. The α 0.05 / s 1 cube (`cube100_lowalpha0.05_s1`) stays in the reported set: its achieved SE, VOV and 30-replicate p95 are printed in the margin report beside the gated cube's; a replicate p95 > 1 dB there is escalated exactly as at a gated scene; any finding about it states that it is a synthetic bound no preset approaches (no fixture has s > 0.7; Kuttruff: full Lambert reflection is 'hardly ever real'). Starting state (file 10, C++ shipping rule, 30 disjoint pre-registered streams, 1 kHz): gated cube p95 0.250 / 0.178 dB, achieved SE 0.117 / 0.115 dB (replicate SD 0.036 / 0.038 dB), floor **met via clause (d)**; s = 1 cube p95 0.701 / 0.810 dB, achieved SE 0.381 / 0.384 dB > 0.33 dB, floor **not met**, recorded as a starting-state finding of the reported set (not a gated scene); flutter cube met via (a)."

**(ii) "Any further rise" (Trigger 1, starting-state clause).** "The starting state per gated scene, emitter and OS is the O18 record at the pinned W_max: the fixed-key achieved SE (one deterministic number per OS, AX40/D7) and the replicate p95 (30 disjoint pre-registered streams), stored in the flags golden and never regenerated to pass. **Recorded** (in the margin report of every later run that re-derives W_max or re-baselines the non-diffuse build): any rise of the achieved SE ≥ 0.05 dB or of the replicate p95 ≥ 0.10 dB above the starting state. **Escalated** (phase-05h §2 item 1, to Maisara with the SE, the VOV and the p95): the achieved SE crossing 0.33 dB, or the replicate p95 crossing 1 dB (1 jnd of G, Vorländer Table 6.1), at a gated scene, or the p95 crossing 1 dB at the reported s = 1 cube ((i) above). Nothing else escalates."

**(iii) Realised-work ratio (AX41, pre-registered).** "realised work / W_scene ≤ **1.02** at each gated scene, pre-registered from the C++ measurements at the pinned W_max 3.05 M (measured 0.935 / 0.991 / 0.986 at flutter / s 0.3 / s 1; prototype ≤ 1.009; the count is deterministic, D7) and not changed afterwards. Beside it, W_pilot and W_final per gated scene are asserted **exactly** in the D5 golden (already recorded there); the ratio is the scene-generic guard."

**(iv) W_max and n\*_max, pinned cross-platform constants.** "**W_max = 3.05 M image evaluations per emitter (W_scene 6.10 M)**, a pinned cross-platform constant (AX39 D7), the same on every OS. Derivation (AX41 formula (A), worst of 10 restores, worst-of-10 solve, ratio 1.02): per emitter (30 s / 14 − worst non-diffuse restore of the gated cube) / 2 ÷ ns per evaluation at the runner's pool size ÷ 1.02 = Linux (2.1429 − 2.0630)/2 = 39.95 ms ÷ 16.5 ns ÷ 1.02 ≈ 2.4 M; Windows (2.1429 − 2.0035)/2 = 69.7 ms ÷ 11.7 ns ÷ 1.02 ≈ 5.8 M; **macOS 2.1429 − 2.3277 = −0.185 s: no W_max ≥ 0 exists.** The margin therefore exceeds 100 % of W_max at the worst OS build; under the settled rule (> ~20 % returns to the seats, whose options are the smaller W_max or (C) forward) the seats chose (C) forward (W-b: 2 / 2 for Seats 1, 2, 5, 7; a cut cannot buy a pass on any OS and holds Linux only inside its own 1–2 % run-to-run spread). The provisional value is pinned as the (A) value; it is not a formula result. Checked against Seat 6's 3 s: 3.05 M × 44.7 ns = 0.136 s per emitter at one thread (Linux); the solve is 58–162 ms per scene at pool size. Re-derived once more under (C) (phase-07c condition 3), where Seat 6's 3 s is read per scene (W_scene on one thread) or the emitters are shown to solve in parallel (Seat 6's correction). **n\*_max = 1 024** stands (W1 diffuse share 7.65 / 9.03 (max 13.98) / 6.35 ms ≤ 25 ms; a raise lowers N_cap at the capped cubes one-for-one through AX41's pilot rule and was rated veto-grade by Seat 1 at 2 816 under (A)); not re-derived at (C) unless the W1 measurement per output mode moves it (phase-07c §9)."

**(v) The blocking gate and phase-07c's ordering** (the mechanism is her recorded decision read in `FOR MAISARA H1-F2`; the plan text, to apply once H1-F2 survives): "The AX38 4c restore gate runs on every Release run on Linux, macOS and Windows at both gated builds and asserts per OS and scene: (a) 14 × (worst-of-10 restore + worst-of-10 solve) ≤ 30 s, **strictly** wherever the recorded value at the pinned W_max is ≤ 29.1 s (a 3 % margin, about one observed run-to-run spread), and otherwise only if that OS/scene is **listed in the defect register** below; (b) for every listed entry a growth bound: median-of-10 restore ≤ 1.10 × the recorded median; (c) a listed entry that passes is reported in the job summary (warning) and removed through `/fix-plan` before the next phase is set `done`; (d) a new failure at an unlisted OS/scene is a defect: never re-run, never a W_max cut, never a range change or a seam; it is added to the register with its remedy ((C) forward) through `/fix-plan`. Per-OS min/median/worst and the 14× figure are printed on every run. **Register at the pinned W_max** (file 1 §4; medians to be re-baselined from O18's run): `cube100_lowalpha0.05_s0.3` on **Linux** (30.27 s; median 2 032.5 ms; remedy: phase-07c moves the diffuse solve, after which the non-diffuse restore gives 28.9 s; closes at 07c) and on **macOS** (33.40 s; median 1 882.0 ms, min 1.50 / worst 2.33 s on a 3-vCPU M1 VM; remedy: the finding below; closes when the unit-decay synthesis leaves the synchronous restore (07c/07d) or, if the runner is shown to be the cause, at Phase 13's release-machine re-check, as §0 row 06 already does for the macOS callback p99.9). Windows (29.04 s) and the flutter cube on every OS (7.6–10.6 s) are strict. **Finding (separate, named):** the non-diffuse 100 m / 96 kHz restore is the unit-decay synthesis in `tail::BandNoiseGenerator` at the 12 s tail cap (constructor spectra 0.96 s + `make` × 2 emitters 2.18 s = 3.14 of 3.29 s, ≈ 95 %, split timer file 7; ISM + matching + mix ≈ 0.15 s); it is flat in room size for every room with T60_max ≥ 8 s and linear in fs; (C) as written (phase-07c moves only the diffuse solve) does **not** cure macOS (14 × 2.33–2.59 s = 32.6–36.3 s). **Remedy, routed by name:** phase-07c gains condition 9 (or a `phase-07d.md` of size S–M if 07c cannot carry it): the unit-decay synthesis moves off the synchronous restore, prepare and `reset()` with the same interim / 'settling' rules as the diffuse solve (the interim tail while the synthesis is pending is decided in 07c's loop beside D-C2; never silence where a tail existed in the saved state); after both moves the restore gate measures ISM + matching + mix (≈ 0.15 s at 96 kHz) and passes a worst-of-10 rule with 10–20× headroom. Alternatives recorded, not chosen here: a cheaper generator (output-changing; a golden round; AQ10's 'not optimised before Phase 13' to be read by the board); caching the constructor spectra per (fs, length) process-wide (bit-identical, ≈ 4 of 14 FFTs, [Hyp] 20–25 %, not enough alone). **Ordering:** phase-05h may be set `done` under CLAUDE.md step 6 with the register entries recorded in §0 row 05h (the automated check passes with them listed); phase-07c is the **next phase after 05h**, before Phase 08's goldens (AX38 4c 'brought forward on any restore-gate failure'; phase-07c §3), its 'Depends on: 05h done' unchanged; if O18 does not fit this session, the gate and records go to phase-05i and 07c follows 05i. Phase 08's heaviest-mode gate (phase-08 scope 10) runs under the same register rule. The macOS and Windows restore records go to Maisara in the 05h PR against the 1 / 3 / 10 s anchors with the spread stated (Raise item 2), and the register is re-enforced strictly on all three OSes at Phase 13's release-machine re-check (AX41)."

**Confidence:** medium (every acoustic number is corpus- or measurement-backed and every product claim cites an id, but seven W-x cells, one P-a′ cell and six R-e cells are read from conditions). **Reversal condition:** (1) O18's three-OS run shows an unlisted OS/scene over 30 s or a listed one under it (the register changes, the decision stands); (2) phase-07c's loop finds the synthesis cannot be moved without an output change (the remedy becomes the cheaper generator through a golden round; W_max unaffected); (3) a seat re-rates W-x or R-e above its read cell in the interrogator's round (step 3 redone); (4) Phase 13's release machines show the macOS restore ≤ 2.14 s (the macOS entry closes as a runner artefact).

### Load-bearing claims, D-H1

- **D-H1-L1** (verified source): pluginval v1.0.4's timeout is an inactivity watchdog reset by every log and `expect`; the restoration test's 14 restores each end in an `expect`; the tool's own bound is ≈ one restore per 30 s (120 s in CI); a timeout fails the run. Researcher F1–F6, read, high. *Bears on H1-F1.*
- **D-H1-L2** (measurement): worst-of-10 non-diffuse restore at the s = 0.3 cube, 96 kHz: Linux 2.063 s, macOS 2.328 s (min 1.501 s), Windows 2.004 s; solve median/worst Linux 98.9/99.6 ms. File 1 §3–§4.
- **D-H1-L3** (derived from L2): 14 × 2.328 = 32.6 s, 14 × 2.591 = 36.3 s > 30 s: (C) as written does not pass macOS. Redone by Seat 5 and the researcher (F8).
- **D-H1-L4** (measurement, from the code): the unit-decay synthesis is 3.14 of 3.29 s (≈ 95 %) of the non-diffuse 100 m / 96 kHz build; ISM + matching + mix 147 ms. File 7 §1.
- **D-H1-L5** (derived): formula (A) at the gated cube: Linux ≈ 2.4 M, Windows ≈ 5.8 M after the 1.02 ratio, macOS < 0 (working in (iv)). Interrogator to redo.
- **D-H1-L6** (corpus): σ_L ∝ √(A/N), Vorländer Eq. (11.21), L3089–3090, Poisson hit counts; used only as the direction of the SE cost of a cut (×1.21 at 0.685 of the work); the replicates (file 10) are the evidence. Conditions stated.
- **D-H1-L7** (corpus): G jnd 1 dB, 500–1000 Hz, Vorländer Table 6.1 (L2060). The escalation line of (ii).
- **D-H1-L8** (measurement): realised work / W_scene 0.935 / 0.991 / 0.986; prototype ≤ 1.009; D7. File 1 §2; AX41.
- **D-H1-L9** (measurement): W1 diffuse share 7.65 / 9.03 (max 13.98) / 6.35 ms. File 1 §3.
- **D-H1-L10** (replicates): gated cube p95 0.250 / 0.178 dB, SE 0.117 / 0.115 dB → floor met via (d); s = 1 cube SE 0.381 / 0.384 dB → not met. File 10.
- **D-H1-L11** (seat statements of own cost): Seat 1 N-b 2 816 = 3; Seats 1, 2, 5, 7 W-b = 2/2; Seat 5 W-a = 2/2 and W-x = 1/1; Seat 7 W-a = 2/2. Quoted above.
- **D-H1-L12** (from the code): `ci-ok` writes the pass marker only on a fully green run, so a by-design red disables the fingerprint skip for later PRs. `ci.yml` L27–31, L483, L508–521.
- **D-H1-L13** (verified source): VST3 `setState` is called on the UI thread (F13); Windows declares an app "not responding" after 5 s (F14); Apple tools report hangs > 250 ms (F15). Bears on H1-F1's reading of NFR-2.
- **D-H1-L14** (product): AX38 4c already places a block per OS (memory block "gated on Linux, recorded on macOS and Windows until Phase 13"); §0 row 06 hands a macOS runner measurement to phase-13 item 9. Plan ids.
- **D-H1-L15** (product judgement, PRD): NFR-2 "usable in a DAW session" is what a per-restore bound protects once pluginval's watchdog is not the binding tool; NFR-1 accuracy first is what keeping W_max uncut serves; NFR-8 forbids the range narrowing every option here refuses.

### Future-debt register, D-H1 (chosen options)

| seat | commits later phases to | undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| 1 (W-x later 1) | the (A) level debt: s = 1 cube SE 0.38 dB, layouts 4/5 0.13–1.33 dB, until (C) | nothing extra: (C)'s golden round | O18 margin report; 07c's W_max | phase-07c lands with W_max from the background budget |
| 1 (P-a′ later 1) | the s = 1 cube watched in the reported set with an escalation path | a pin edit | every margin report | standing rule; closes at (C) |
| 2 (W-x later 1) | the finding's remedy: 07c condition 9 / 07d (synthesis off the restore) | a 07c scope edit; or a golden round if the cheaper generator is chosen instead | 07c's loop and its restore record | 07c/07d `done` |
| 2 (R-e later 1) | shipped precision at the gated scene guarded only by the 0.33 dB / 1 dB lines and the record | one constant | the first re-derivation (07c) | if a recorded rise ≥ 0.05 dB recurs without a crossing, the board re-reads R |
| 3 (W-x, N-a later 1) | 07c next; one-end placements at up to 0.124 dB | (C)'s golden round | O18, 07c | 07c |
| 4 (W-x later 1) | the Phase 08 heaviest-mode gate runs under the register, after (C) | a register entry | phase-08 scope 10 | 07c/07d, or Phase 13 |
| 5 (W-x later 1; Q-d, N-a later 1) | a register that must shrink; growth bound re-baselined only through plan text; one pre-registered ratio | a plan edit per entry | O18 per OS; RQ-H1-2 stays absent; Phase 13 real hardware | Linux entry at 07c; macOS entry at 07c/07d or Phase 13 |
| 6 (W-x later 1) | "settling", the one-step update and the Phase 12 (ii) re-check at the final W_max come at 07c; records to Maisara in the PR | a plan edit | O18 records (Raise items 2, 3) | 07c; Phase 13 re-enforcement |
| 7 (W-x later 1) | the macOS entry listed with an end date (07c/07d or Phase 13); one golden round at (C) | a plan edit | O18; 07c | 07c/07d |
| 8 (W-x later 1) | the 2.0–2.6 s load wait outlives (C) as written until the synthesis moves | none; the record carries it | O18's (iv) records; RQ-H1-3 absent | 07c condition 9 / 07d |
| 9 (W-x, R-e later 1) | one golden round at (C); Phase 12's preset check at the final W_max (with an elongated stone cathedral case, Seat 9's hand-off) | — | phase-12 | 07c, Phase 12 |

**Strongest objection.** Seat 1's `2` now on every (A) option: W-x ships the s = 1 cube at SE 0.38 dB (p95 0.70–0.81 dB) and layouts 4/5 at 0.13–1.33 dB until (C). It holds because the one option that removes it, W-c, is 2 / 2 for Seat 7 and 2 now for Seat 8 (the switch's ≈ 4 jnd AX16 correction waits a phase) and its premise is weak (after (C) as written the gate still fails on macOS, Seat 2); W-x brings (C) soonest at the highest W_max, which is Seat 1's own reason for preferring W-a. The second objection the interrogator should press: the seats rated the 14× bound as pluginval's requirement and it is now a convention (H1-F1). The ratings rest on the **number** (2.143 s), which H1-F1 keeps, not on its label; if the interrogator holds that a seat would re-rate under the corrected label, that is a second round for that seat, and the decision waits on it rather than falling.

### FOR MAISARA H1-F1 — does the "14 × t_restore ≤ 30 s" convention stand now that it is not pluginval's requirement?

**Question.** AQ10 amended and AX38 4c (her acceptance of 2026-11-10) say the restore block is "14 × t_restore ≤ 30 s under pluginval's default watchdog, about 2.14 s per restore". pluginval v1.0.4's watchdog resets after every restore (F2–F4); the tool's own bound is one restore per 30 s. Does the 2.143 s per-restore bound stand, or is the gate re-based?

**Answer (exact wording for the rows).** "The block is **14 × t_restore ≤ 30 s, i.e. t_restore ≤ 2.143 s per synchronous restore at the gated builds, a project convention** on the synchronous restore (not pluginval's requirement: pluginval v1.0.4's watchdog is an inactivity timeout reset after each restore, so the tool itself tolerates one restore per 30 s; researcher dossier `5-researcher-RQ-H1-H2.md` F1–F6). The constant 14 is kept as written and is no longer re-derived from the automatable-parameter count. CI's pluginval run (`--timeout-ms 120000`) is not evidence for this block; the Catch2 restore test is."

**PRD ids and decisions.** NFR-2 ("the plugin must stay usable in a DAW session"); NFR-6; NFR-1; her acceptance of 2026-11-10 ("I accept the board's answer by definition").

**Reasoning (5 lines).** The PRD does not name a restore bound; the convention is the one number in the plan that bounds the synchronous restore the host's UI thread blocks on (F13), and 2.14 s sits under the one OS threshold on record (Windows 5 s, F14). Dropping to pluginval's real bound would let W_max under (A) grow ≈ 14× and the synchronous restore run for many seconds on the UI thread, which no seat rated and which strains NFR-2. Choosing a different user-facing number (1 s, 3 s) would be inventing a product goal the PRD does not state (the 1 / 3 / 10 s marks are escalation anchors, AX38 (iv), not limits). Keeping the accepted number keeps every seat's rating valid. (C) makes the (A) value transient anyway.
- *Keep the convention (chosen):* serves NFR-2 (a bounded UI-thread block), NFR-1 (W_max stays uncut), NFR-6 (restore as saved, bounded); strains nothing in the PRD.
- *Re-base to one restore per 30 s:* serves nothing the PRD names; strains NFR-2 (a 30 s synchronous restore would be "allowed").
- *Re-base to a user-facing anchor (e.g. 3 s):* the PRD gives no such number; case (a) if attempted; not chosen.

**What would make her veto it.** A reading that NFR-2's "heavy CPU and latency are acceptable" licenses a longer synchronous restore so that W_max can rise under (A) and NFR-1 gains now rather than at (C).

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AQ10 amended (1) and AX38 4c Challenge 1: "under pluginval's default watchdog" → "a project convention; pluginval's watchdog resets per restore".)

### FOR MAISARA H1-F2 — the restore block as a strict check with a defect register, its OS scope, and the remedy beyond (C)

**Question.** AX38 4c (her acceptance) says the restore block is "a block … a gate failure is a defect … remedied by bringing (C) forward" and names no OS for it, while the memory block in the same row is "gated on Linux, recorded on macOS and Windows until Phase 13". The data say the block fails on macOS at every W_max ≥ 0 and (C) as written does not cure it. May the block run as a strict check with a plan-text defect register (W-x), and may the remedy ladder be extended to the unit-decay synthesis?

**Answer (exact wording).** "The restore block runs on all three OSes as a strict check wherever the recorded value is ≤ 29.1 s, and as a **registered defect** elsewhere: each entry in plan text with its recorded value, remedy and closing phase, a growth bound (median-of-10 restore ≤ 1.10 × the recorded median), a warning on an unexpected pass, and removal before the next phase is `done`. A gate failure stays a defect: never a re-run, a W_max cut after pinning, a range narrowing or a seam; its remedy is (C) forward, and where (C) as written does not cure it (the non-diffuse build alone exceeds the budget on macOS), the remedy ladder continues by name: phase-07c condition 9 (or phase-07d) moves the unit-decay synthesis off the synchronous restore with the diffuse solve's interim rules. The register is enforced strictly on all three OSes at Phase 13's release-machine re-check."

**PRD ids and decisions.** NFR-2, NFR-1, NFR-6, NFR-8 ("no environment-specific code paths": the remedy is generic), FR-SIM-6 (no level jump at a size threshold: no range narrowing); her acceptance of 2026-11-10; "build the switch (option (b))", 2026-11-09.

**Reasoning (5 lines).** A block the data say is red at commit time on one OS, with no remedy in any settled text once (C) lands, protects nothing: it hides every other macOS assertion in the same job (Seat 7) and disables the fingerprint skip (D-H1-L12). The register keeps the block's content (the number, the no-re-run rule, (C) forward) and adds what the row lacks: a remedy that actually reaches the cause (D-H1-L4) and an end date. The plan already records-rather-than-enforces on macOS in the same row and in §0 row 06 (D-H1-L14), so this is the row's own pattern, not a new seam. NFR-1 is served by keeping W_max uncut; NFR-2 by the growth bound (the restore cannot grow unnoticed). Only the switch's delivery (her 2026-11-09 decision) is protected by letting 05h close.
- *W-x (chosen):* serves NFR-1 (no cut), NFR-2 (growth bound, remedy at the cause), NFR-8 (generic remedy).
- *W-a as written (red by design):* serves the letter of "block"; strains NFR-2 (no remedy for macOS after (C)) and the verification culture (a red everyone ignores).
- *W-b (cut W_max):* strains NFR-1 (SE ×1.21, p95 past 1 jnd at the s = 1 cube) for a pass on two OSes and none where it is worst.
- *W-c ((C) first):* strains her 2026-11-09 decision's delivery (the switch waits a phase) and still ends red on macOS.
- *W-e (Linux-enforced):* enforces on the OS no customer runs (PRD "Primary users … on macOS and Windows"); strains NFR-2's user.

**What would make her veto it.** The reading that "a block" means a required red on every OS until it passes, with no register, so that the pressure to shorten the 100 m build is never relieved.

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 4c Challenge 1 and AQ10 amended (1): the register mechanism and the OS rule; the remedy ladder's extension to the unit-decay synthesis via phase-07c condition 9 / phase-07d.)

### FOR MAISARA H1-F3 — phase-05h §2 "Raise with Maisara" item 1

**Does item 1 fire?** **No, not now.** Under P-a′ the gated closed cube is s = 0.3, where the floor is met at the pinned W_max via clause (d) on the C++ shipping rule (p95 0.250 / 0.178 dB ≤ 1 dB, achieved SE 0.117 / 0.115 dB ≤ 0.33 dB; file 10), and W_max was not cut by the margin (no re-derived W_max leaves a gated scene below the floor; the negative macOS formula value resolved to (C) forward, not to a smaller W_max). The s = 1 cube's floor failure (SE 0.381 / 0.384 dB) is a **starting-state finding of the reported set**, recorded once in the PR with its SE, VOV and p95 and the statement that it is a bound no preset approaches; it is not an item-1 escalation because that cube is not a gated scene. Item 1 fires later only on (ii)'s escalation lines: the SE crossing 0.33 dB or the p95 crossing 1 dB at the gated cube, or the p95 crossing 1 dB at the reported s = 1 cube. **Answer for her:** "Item 1 does not fire at the pinned W_max; the s = 1 finding is recorded once, not escalated." PRD ids: NFR-1 (accuracy first: the gated reference is the realistic cost-worst room, and the hardest synthetic box keeps an escalation path), FR-3D-3 / FR-3D-4 (presets and user-set materials never approach s = 1 at α 0.05, Seat 9). Options: *fire now on the s = 1 finding* (serves a strict reading of "a floor failure in the starting state … escalated once"; strains nothing, but the clause applies to gated scenes and the s = 1 cube is reported) / *not fire (chosen)* (serves NFR-1 through P-a′'s escalation line; keeps her attention for a crossing a listener could hear). What would make her veto it: she wants the starting-state finding at any 100 m cube in the reported set escalated as item 1 regardless of gating. No AMENDS line: it reads the row, it does not change it.

---

## D-H2 — which AX43 / AX45 / AX46 case-bands have a certified reference now

### Knowledge inventory (final)

| id | what must be known | source | status |
|---|---|---|---|
| K20 | per-case-band certified listing with ℓ_ref | file 6: AX43 **274 / 560** certified (the 15 (A) cases × 8; BRAS × 500 Hz–2 kHz; dead_booth, living_room, classroom, club × both emitters × 8 bands, ℓ_ref 0.115–0.561 %), 286 single-rung; AX45 **40 / 72** (s-cases, dt6_small_room both emitters; stone_box and W1 single-rung); the W1 CS-NW+ e0 / W1 e0 c4 values at 1.25 m await the session-2 cross-check (table blank) | known, growing; the rule below is by listing, not by count |
| K21 | AX36's per-quantity < 1 % halving rule | AX36 | known |
| K22 | ℓ_ref values | file 6 | known |
| K23 | per-case `hybrid_fast` cost / memory | file 7 §3: the five small rooms seconds per rung; club 9 s at 1.25 m; concert_hall_box 28 s at 2.5 m, 1.25 m kernel 2.7–4.4 GB per band column (lean solver OOM at 15 GB; chunked run in progress); W1 1.25 m ≈ 1.2 GB; W2 ≈ 3 GB, 124–220 s at 2.5 m | known |
| K24 | runner limits | F17–F20: public Linux/Windows 16 GB / 4 vCPU, macOS 7 GB, 14 GB SSD; 6 h per job; artifacts 500 MB (Free); larger runners paid, org plans only | known |
| K25 | AX46 classes with ≥ 1 certified case | derived from K20: reference positions, absorbing face ((A) layouts 4–6), small rooms (dt6_small_room, dead_booth, living_room); one-end near-wall once the c4 cross-check passes; 100 m none | known |
| K26 | the AX46 100 m class's reference | Seat 2: `ref_hybrid` impossible (AX36 (c)); the estimator's own long run measures variance, not bias; the tracer is the only independent reference (AX39: −0.009 dB), its SE at 100 m ≈ 1 % at 10⁶ rays [Inferred, Vorländer (11.21)] | known as to kind; the tracer's achieved SE is a number to record, not to decide on |
| K27 | the family rule on a subset is conservative | AX43 (z_FW fixed for 560) | known |
| K28 | D-H3 inputs (pooled \|mean z\| at 500 Hz–2 kHz; U at edge_values / open_field defaults) | file 9 | noted, not decided here |

### Tension map, D-H2

| seat | G-a consequence | U-a | U-c | M-e | M-a | M-b | M-c | M-d | B-a | B-b |
|---|---|---|---|---|---|---|---|---|---|---|
| 1 | 1 / 1 "335 case-bands owed before any public wording" | 0 / 1 "wording drift" | 1 / 0 | 0 / 1 | 1 / 1 "'cheapest' is the implementer choosing" | 1 / 2 | 1 / 1 | 1 / 1 | 0 / 1 "no pooled 'bias ≤ 1 %' line across the set" | 1 / 1 |
| 2 | 1 / 1 "the listening-pack rooms are ungated at the moment the switch lands" | 0 / 0 "a gross-error detector" | 1 / 0 | 0 / 1 | 0 / 1 | 1 / 1 | 1 / 2 (live) → 1 / 1 as an artifact job | 0 / 1 | 0 / 0 | 1 / 1 |
| 3 | 1 / 1 "'nothing audible changed' is unverified where it will be heard" | 0 / 0 | 1 / 1 | 0 / 1 | 1 / 1 | 1 / 2 | 1 / 1 | 1 / 1 | 0 / 1 | 1 / 1 |
| 4 | 1 / 1 "Phase 08 goldens … may freeze on an ungated E_b" | 0 / 0 | 1 / 0 | 0 / 1 | 0 / 1 | 1 / 2 | 1 / 1 | 0 / 1 | 0 / 0 | 1 / 1 |
| 5 | 1 / 1 (CI time; the golden holds the set) | 0 / 1 "a print that could be quoted" | 0 / 1 | 1 / 1 | 1 / 1 | 1 / 1 | **2 / 2 live**; 1 / 1 manual artifact job | 1 / 1 | 1 / 1 | 0 / 1 |
| 6 | 0 / 0 not required (confirmed) | | | | | | | | | |
| 7 | 1 / 1 "certifying more is additive" | 0 / 0 | 1 / 1 | 0 / 1 | 0 / 2 "a quiet choice by the implementer" | 0 / 2 | 1 / 1 | 1 / 1 "a thing only Maisara can provide" | 0 / 0 | 0 / 1 |
| 8 | 1 / 1 "judged on rooms that are 'reported, not gated'" | 0 / 0 | 0 / 0 | 0 / 1 | 0 / 1 | 1 / 2 | NMM | NMM | NMM | NMM |
| 9 | 1 / 1 "my preset references … reported, not gated" | 0 / 0 "the cheapest ranking of which second rungs are urgent" | 1 / 1 | 0 / 1 | 1 / 1 | 1 / 1 | 1 / 1 | 1 / 0 "compose with M-e" | 0 / 1 | 1 / 1 |
| max / sum | 1 / 16 | 1 / 2 | 1 / 9 | **1 / 9** | 2 / 15 | 2 / 20 | 2 / 15 (live) | 1 / 11 | **1 / 5** | 1 / 13 |

### Minimum-tension working

1. **Bounds.** X4 dropped (gating an uncertified rung at a widened tolerance). G-a is forced by AX43's own text ("the finest certified rung, with ℓ_ref recorded") and the session constraint.
2. **Veto-grade.** None.
3. **Worst-off.** U-a (1), M-e (1) and M-d (1) beat M-a / M-b / M-c-live (2); B-a (1).
4. **Compose.** None needed; M-e already carries M-a's runs and the listing rule; M-d enters as a route, not a decision (a person's act; Seat 7).
5. **Sum.** U-a 2 < U-c 9; M-e 9 < M-d 11; B-a 5 < B-b 13.
6. **Reversibility.** All additive (`--extend` never drops a key).
7. **Decide:** G-a with the seats' conditions, U-a, M-e (M-d and a manual artifact job as routes for the 15 GB-class cases), B-a.

### DECISION D-H2 (plan text; the AX43/AX45/AX46 scope-now reading is `FOR MAISARA H2-F1`)

**(a) Gating rule (G-a).** "A case-band of AX43 / AX45 / AX46 is **gated** when the agreement golden holds for it a reference at two rungs of the ℓ ladder with the finer-rung change < 1 % (AX36, per quantity), ℓ_ref = that change recorded per case-band; the committed `phase05b.json` `ell` / `r1`, the c4 CS-NW+ values (once the session-2 1.25 m run reproduces them: `6-orchestrator-K20-certified-listing.md` cross-check) and this session's `hybrid_fast` runs all count. Everything else is **reported, not gated (reference pending)** and listed per case-band with its status (gated / single-rung uncertified / none) **in the agreement golden itself**, extended only through `update_goldens.py --extend` with a CHANGELOG reason, so that promotion is visible and the implementer can never narrow the set. z_FW stays 4.290 (AX43) and 3.81 (AX45), conservative on the subset. The report prints '<gated> of 560 gated; <n> reported (reference pending)' and '<gated> of 72 gated' in the same table (at the time of writing 274 / 560 and 40 / 72, growing this session); Phase 13's copy is written from that line. The gated set keeps at least one room with per-band α (club, living_room, classroom, dead_booth are certified) and one with mixed per-face s (the orchestrator confirms from the fixtures; else the gap is reported; PR #27 m-10). The listening-pack README states per room whether its tail level is gated, reported-only or without reference; the 05h PR's accuracy paragraph counts gated case-bands only and labels the listening line as listening content. Phase 08 goldens in rooms with ungated case-bands carry 'tail-level reference pending (D-H2)' in `tests/golden/CHANGELOG.md`. The M-2 tracer comparison is printed per band for the five mixed-α Phase 04 rooms. CI: the `build` job gets a `timeout-minutes`; the agreement suite's per-OS wall time is printed; Seat 5's budget is ≤ 10 min added wall time per OS, above which the BRAS pairs' bias check moves to the nightly (AX43's reversal clause)."

**(b) Single-rung references (U-a).** "A case-band whose reference exists at one rung only is **printed, never asserted**: |C++ − ref| in dB and z, on the same line as the fixed label `uncertified rung, no ℓ_ref, not pass/fail`, in the job summary and the phase record; never counted in a pass total or in public wording. It is a gross-error detector (a wrong face, a unit, a prune radius at per-band α); a difference > 1 dB is a flag worth a look, a small difference is not evidence of agreement to τ."

**(c) Producing the missing references (M-e, with the committed priority order).** "References are produced offline by `tools/validation/hybrid_fast.py` at two rungs (2.5 → 1.25 m) per band column, committed by script with provenance (tool commit, hash-pinned numba/numpy, rungs, ℓ_ref) and the CHANGELOG reason; never computed live in a gate. This session's 4-core background runs continue in this order, and **phase-05i gates whatever is certified by then; the rest stays reported and listed, never dropped**; every item not finished in 05i gets a named owner phase before Phase 12 freezes presets and before Phase 13 writes copy. Order (merged from Seats 1, 2, 3, 4, 8, 9: audible relevance and use first, cost deciding ties): (1) `concert_hall_box` both emitters at 1.25 m (chunked; 2.7–4.4 GB per band column) and `stone_box` both emitters at 1.25 m (cheap: ≤ 720 patches); (2) W1 e0 and e1 at 1.25 m, all 8 bands (≈ 1.2 GB; the kernel persisted to disk once); (3) the CS-NW+ emitter-1 cases and the 0.3 m wall case, 500 Hz–2 kHz first, then all bands, as gathers on the persisted W1 kernel; (4) W2 both emitters (≈ 3 GB); (5) the BRAS pairs' 250 Hz and 4 kHz, then 125 Hz and 8 kHz, 63 Hz last (15 GB class: gated when certified, never claimed as a room validation below the Schroeder frequency, Seats 1, 2, 9). Routes for the 15 GB class if this machine does not fit them: a manual, Linux-only, hash-pinned `workflow_dispatch` job on the public 16 GB standard runner (6 h limit) that uploads the small reference JSON as an artifact for a person to commit (never a live gate input; F17–F20), or a larger machine for a few days (M-d), which only Maisara can provide and is listed for her as an action, not a decision."

**(d) AX46 now (B-a).** "The bias check runs now, per band and per class, on every class with ≥ 1 certified case at the pre-registered N (3·SE ≤ 1 % − ℓ_ref): reference positions, absorbing face, small rooms, and one-end near-wall once the c4 cross-check passes. Classes without a certified case print 'not evaluated (reference pending)'. The **100 m class** names the tracer (AX39: (f) − tracer = −0.009 dB) as an independent comparison, reported at the tracer's achieved SE and labelled 'not evaluated at 1 % (compute limit)' unless a larger run certifies the tracer's SE ≪ 0.043 dB; never an AX46 pass. The result appears only as the per-class table; AX46's pooled figure is computed over the evaluated classes and labelled 'pooled over <n> of 5 classes', never as a bare 'bias ≤ 1 %'."

**Confidence:** high for (a), (b), (d) (plan ids, committed data, verified runner findings; no acoustic claim beyond τ = ¼ jnd); medium for (c)'s order (the seats' audibility ranking is their judgement, tagged [Hyp] by Seats 3 and 9). **Reversal condition:** phase-05i's agreement test on a newly certified case-band shows |C++ − ref| > τ (a reference arriving, read as such, one golden round); D-H3's ruling on the pooled |mean z| failure at 500 Hz–2 kHz (file 9) may change how the BRAS references enter the family rule, not the gating rule here.

### Load-bearing claims, D-H2
- **D-H2-L1** (committed data): 274 / 560 and 40 / 72 certified; the per-case-band ℓ_ref values. File 6.
- **D-H2-L2** (plan id): AX36's per-quantity < 1 % rule; AX43 "the finest certified rung, with ℓ_ref recorded"; CLAUDE.md `--extend` never drops a key.
- **D-H2-L3** (measurement): per-case costs and memory, file 7 §3; the lean solver OOM at 15 GB for concert_hall_box at 1.25 m.
- **D-H2-L4** (verified source): runner RAM 16 / 7 GB, 6 h job limit, artifact 500 MB, larger runners paid. F17–F20.
- **D-H2-L5** (plan id / corpus): τ 0.25 dB = ¼ of the 1 dB G jnd (AX42; Vorländer Table 6.1); 1 % = 0.043 dB (10·log10 1.01).
- **D-H2-L6** (seat statement): Seat 2's reading that a single rung lacks ℓ_ref and any evidence of the convergent regime; the tracer as the only independent 100 m reference.
- **D-H2-L7** (product judgement, PRD): NFR-1 (accuracy "measured match … pass thresholds from the Expert") is served by gating only what is certified and claiming only what is gated; FR-3D-3 (the preset categories) orders the rooms producers reach first.

### Future-debt register, D-H2
| seat | commits later phases to | undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| 1 (G-a, U-a, M-e, B-a later 1) | 286 / 32 case-bands owed before public wording; the label text frozen; the per-class-only bias form | nil (additive) | phase-05i | 05i, or a named owner phase |
| 2 (M-e later 1) | the order and the persisted kernels | — | the background-run log | 05i |
| 3 (G-a, M-e, B-a later 1) | `stone_box` and W1 (AX45) certified in 05i before "nothing audible changed" is said for them | a golden round if a reference arrives > τ | 05i | 05i |
| 4 (G-a, M-e later 1) | Phase 08 goldens in ungated rooms marked "reference pending (D-H2)" | a golden round plus a re-rendered pack | 05i's agreement test | 05i before Phase 08's freeze, else the mark |
| 5 (G-a, M-e, B-a later 1) | a monotonically growing golden; the ≤ 10 min per-OS budget; the artifact-job route if used | a nightly move for the BRAS bias check | the first Release run with the suite | standing |
| 7 (G-a, M-e later 1) | an owner phase for anything 05i leaves; M-d listed as her action | nil | 05i | before Phase 12 / 13 |
| 8 (G-a, M-e later 1) | the listening README's per-room status | — | the 05h pack | 05i |
| 9 (G-a, M-e, B-a later 1) | the bass bands and the preset rooms gated in 05i | — | 05i | 05i |

**Strongest objection.** Seat 7's M-a later 2 / M-b later 2 ("a quiet choice by what happened to finish"): M-e answers it only if the order and the "gates what is certified, rest listed" rule are in plan text and the status lives in the golden; if phase-05i is itself split, the owner-phase rule is what keeps the debt visible. Seat 5's note that the 100 m class may read as "evaluated" if the tracer line is not labelled is met by the fixed wording in (d).

### FOR MAISARA H2-F1 — the scope of AX43 / AX45 / AX46 now

**Question.** AX43 ("70 cases / 560 case-bands"), AX45 ("72 case-bands") and AX46 (five classes) were accepted on 2026-11-10 on the premise that every reference existed at a certified rung. Only part of the set does. Do the gates run on the certified subset now with the rest reported and listed, with the full set gated by phase-05i or a named owner phase?

**Answer (exact wording).** "AX43, AX45 and AX46 run now on every case-band and class with a certified reference (ℓ_ref recorded); the rest are reported, not gated, listed per case-band in the agreement golden, and gated in phase-05i or a named owner phase as their references are certified in the committed priority order. No case-band is dropped, no tolerance widened, and no accuracy claim counts a reported case-band."

**PRD ids and decisions.** NFR-1 ("Rendering must match impulse responses … Pass thresholds come from the Expert"); the verification culture (CLAUDE.md: tolerances follow from the requirement; goldens never regenerated to pass); her acceptance of 2026-11-10; "build the switch (option (b))", 2026-11-09.

**Reasoning (5 lines).** AX43's own text gates against "the finest certified rung, with ℓ_ref recorded"; a case-band without one cannot be gated without inventing a tolerance (X4), which the verification culture forbids. Gating the certified subset now lets the switch (her 2026-11-09 decision) land with its evidence instead of waiting a phase; the family rule on a subset is conservative, so nothing passes more easily. Reporting the rest in the same table keeps NFR-1's claim honest. Additive promotion costs no shipped bit.
- *Gate the certified subset now, rest listed (chosen):* serves NFR-1 and the switch's delivery; strains nothing.
- *All references first (M-b):* serves a literal "560" but delays the switch a phase and leaves the listening pack's rooms unreferenced longer (Seats 1, 4, 8: later 2).
- *Gate uncertified rungs at a widened tolerance (X4):* strains NFR-1 and the verification culture; out at bounds.

**What would make her veto it.** A reading that AX43's "560 case-bands" is a hard count that must be gated before any golden freezes, whatever it costs the switch's delivery.

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX43, AX45, AX46: the phrase "the subset with a certified reference now; the rest reported and listed; gated in phase-05i or a named owner phase" added to each row's scope.)

---

## Summary table

| id | decision (exact value / wording) | state | worst-off seat (cell) | sum | confidence | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| D-H1 (i) P-a′ | gated cube `cube100_lowalpha0.05_s0.3` (α 0.05, s 0.3); s = 1 cube reported with an escalation at p95 > 1 dB | proposed | Seat 1 (1 / 1, rfc), Seat 5 (1 / 1) | 9 | medium (one rfc cell) | NFR-8, NFR-1 | Table 6.1; Kuttruff §5 (Seat 9) | O18 replicates at a later W_max cross a line |
| D-H1 (ii) R-e | record SE ≥ 0.05 dB / p95 ≥ 0.10 dB; escalate on SE 0.33 dB / p95 1 dB crossings | proposed | Seat 2 (1 / 1, rfc) | 6 | medium | NFR-1 | Table 6.1 | a recorded rise recurs without a crossing |
| D-H1 (iii) Q-d | ratio 1.02 at W_max 3.05 M; W_pilot/W_final exact in the D5 golden | proposed | Seat 5 (0 / 1) | 1 | high | AX41 (plan) | — | a gated scene scatters > 1.02 |
| D-H1 (iv) | W_max 3.05 M per emitter pinned (formula negative on macOS); n\*_max 1 024 | proposed | Seat 1 (2 / 1) on W_max; Seat 5 (1 / 1) on n\*_max | 17 / 3 | medium | NFR-1, NFR-2 | Eq. (11.21) direction only; Table 6.1 | 07c's re-derivation |
| D-H1 (v) W-x | strict gate + defect register + growth bound; 07c next with condition 9 / 07d; finding named | proposed (rests on H1-F2) | Seat 1 (2 / 1) | 17 | medium (7 rfc cells) | NFR-2, NFR-8 | — | O18 three-OS run; 07c's loop; Phase 13 |
| H1-F1 | "14 × t_restore ≤ 30 s" stands as a project convention; 14 a constant | for Maisara | — | — | high | NFR-2, NFR-6 | — | her veto |
| H1-F2 | register + OS rule + remedy ladder extended to the synthesis | for Maisara | — | — | medium | NFR-2, NFR-1, NFR-8 | — | her veto |
| H1-F3 | Raise item 1 does not fire now | for Maisara | — | — | high | NFR-1 | Table 6.1 | a line crossing |
| D-H2 (a)–(d) | gate the certified subset by listing; U-a print; M-e order; B-a per class, 100 m = tracer, labelled | proposed | Seat 5 (1 / 1) | 9 (M-e), 2 (U-a), 5 (B-a) | high / medium (order) | NFR-1 | Table 6.1 (τ) | 05i agreement > τ; D-H3 |
| H2-F1 | AX43/45/46 scope now: certified subset; rest listed; 05i or owner phase | for Maisara | — | — | high | NFR-1 | — | her veto |

## Challenges to settled decisions
None. (The board's shared accomplishment and the PRD do not conflict on these matters; the one settled premise found false, pluginval's watchdog, is handled in H1-F1.)

## Decided for Maisara
- **D-H1 (i)–(v) accepted for her** (PRD check: no hard constraint broken — NFR-8 no scene-specific code, FR-SIM-6 no range narrowing, NFR-6/AX5 determinism kept; no PRD goal points to another surviving option: W-c would serve NFR-1 sooner but delays her 2026-11-09 switch and still fails on macOS; W-b strains NFR-1). Chosen: the s = 0.3 cube gated, R-e, ratio 1.02, W_max 3.05 M and n\*_max 1 024 pinned, the gate as a strict check with a defect register, phase-07c next with the synthesis move named. **Seat 1 gave the most** (2 now: random tail-level error 0.38 dB at the s = 1 box and 0.13–1.33 dB in the layout 4/5 class until (C)); it gets back a W_max from the background budget at phase-07c, next phase, and an escalation line at the reported s = 1 cube.
- **H1-F1:** the 2.143 s per-restore bound is kept as the project's own convention (NFR-2, NFR-6), no longer attributed to pluginval. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`
- **H1-F2:** the restore block runs strictly where it passes and as a registered defect where it does not, with a growth bound, an end date per entry, and the remedy extended to moving the unit-decay synthesis off the restore (NFR-2, NFR-1, NFR-8). `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`
- **H1-F3:** Raise item 1 does not fire now; the s = 1 cube's floor failure is recorded once as a finding of the reported set (NFR-1).
- **D-H2 accepted for her** (PRD check: NFR-1 served; no option breaks a constraint; M-b serves no PRD id better). Chosen: gate what is certified, print the rest labelled, produce the missing references in the committed order, run the bias check per class now. **Seat 1 gave the most** (later 1: 286 + 32 case-bands owed before public wording); it gets them back in phase-05i or a named owner phase, with the order fixed in plan text.
- **H2-F1:** AX43 / AX45 / AX46 run on the certified subset now; the rest listed and gated in phase-05i or an owner phase (NFR-1). `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`

**NEEDS MAISARA:** none of the three cases arises. One **action** only a person can take is listed for her, not as a decision: M-d, a larger machine (≈ 32–64 GB, a few days, tens of euros [Hyp, Seat 7]) if the BRAS outer-band rungs and `concert_hall_box` at 1.25 m do not fit this machine or the 16 GB public runner; the plan does not depend on it (those case-bands stay listed until certified).

**Hand-offs to the orchestrator:** re-baseline the register's medians from O18's three-OS run; print per-OS min/median/worst and the 14× figure in the job summary; confirm m-10 (a mixed-per-face-s room in the certified set); persist the W1 and BRAS kernels to disk; the c4 cross-check column; file 9's two findings go to D-H3 (not decided here).