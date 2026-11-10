# Seat 7 (founder) — positions on D-T1 and D-T2

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 7 POSITION (D-T1.1–1.6 and D-T2; not convened on D-T6)

Two assumptions in my persona don't hold here, and the PRD wins on both, as in my D-T5/D-T4 position (`3-seat7-T5-T4.md`). The product is a $10–20 monthly subscription that unlocks editing, and saved work keeps rendering "exactly as saved" (PRD L114–125, FR-LIC-3, NFR-6). The team is Maisara plus contracted engineers (PRD L55). So I measure in three things: contractor sessions, how long a user waits after an edit (editing is the paid value, PRD L125), and trust that saved projects render on any machine.

---

## D-T1

**1. Reading.** The decision is which estimator sets the shipped tail level, at what precision, and what we can say publicly about it. Cues it triggers:
- depth priced by effort (P8);
- saved work that won't open (DR1, V6);
- a claim ahead of its evidence (AI2; Seat 1's Tier A rule);
- quiet borrowing from later phases.

**2–4. Ranking and tension** (now/later; all D-T1.2–1.4 cells assume T1-F)

| option | label | now | later | reason in my measures |
|---|---|---|---|---|
| **T1-F** | prefer | 1 | 1 | Now: a new estimator class with its own statistics (RNG, SE, VOV, slope, N rule, near-wall rule) for the contract reviewer to carry. Its validation rests only on in-repo agreement, because no published bias figure exists (RQ-T1-4, F22–F24). Later: diagnostics and escalations are maintained for good; cross-architecture branch flips are unquantified; no 100 m reference exists. Rises to later 2 without the conditions in item 6. |
| **T1-A** | can live with | 2 | 2 | Now: it forces D-T3, which means a contract major bump and a Maisara session. The dense form (a) already exceeds the 1 GB ceiling in CR4, a real 42 m room, so it needs (c)'s structure, which exists only as arithmetic. The "simple port" is not simple. Later: narrowing "any environment" (PRD L38, FR-3D-3 outdoor) before release is survivable. Lifting the limit later means a formulation rewrite plus revalidation, and the large-venue presets are lost meanwhile ([Hyp] on demand; Seats 8 and 9). |
| **T1-B** | cannot live with | 2 | 3 | Now: about 9 s per AQ10-room rebuild at an assumed 2 ns per evaluation [Hyp]; numpy measured 99 s (C8). Later: 1 454 s per generation at 100 m (C8). Behind D-T4a's one-solve gate, a multi-stem 100 m project does not become audible on load within a session: "my project won't open" (NFR-6, FR-LIC-3; my D-T4 reasoning). That is a range limit the contract denies, which is worse than an honest one. |
| **S-1** | prefer | 0 | 0 | E_target depends on the scene alone. The validation and ensemble numbers include the real per-scene offset, so the testing record we publish describes what each user hears. |
| **S-2** | can live with | 1 | 2 | Now: tailSeed's meaning becomes "noise and level" (Seat 6). Later: AX11/AX19 ensembles over tailSeed average the Monte Carlo error away, so the published figures describe an average that no single render has. That is an overstated testing record (AI2 inverted). |
| **N-3** | prefer | 1 | 1 | Two-stage with a fresh sample, the published design (F14); no prefix-reuse stopping bias (F12). Build time varies with listener position, and escalations surface honestly. |
| **N-2** | can live with | 1 | 2 | Stopping bias toward low means (F12) is unquantified. It points the same way as the near-wall low readings (F11), giving a systematic low tail at walls that a user finds first. |
| **N-1** | can live with | 1 | 2 | Simplest, at constant cost. But scenes worse than layout 4 have unbounded SE, and near-wall listeners read 1–4 dB low with only a report (C4). That is a silent defect in an ordinary user action. **Under L2-F2:** about 33 × 22 000 ≈ 725 000 paths everywhere, so now rises to 2. |
| **Tol-2** | prefer | 1 | 0 | Typical rooms ≤ 30 ms per emitter; 100 m 144–183 ms (builder §3). D-T6's B6-2 becomes 0.43 + 0.25 = 0.68 dB, under the 1 dB G jnd (Vorländer Table 6.1), so "uniform rooms unchanged" (§0.4) stays claimable (Seat 1 to confirm). |
| **Tol-3** | can live with | 1 | 1 | About 6× the cost of Tol-2: 100 m 0.9–1.2 s per emitter; layout 4 ≈ 9.7 s, which escalates. Under NW-3 with CS-NW, NW-3's +0.093 dB edge shift nearly uses up τ = 0.1 dB. |
| **Tol-1** | can live with, barely | 1 | 2 | B6-2 becomes 1.43 dB, above the jnd, so "nothing audible changed in uniform rooms" cannot be said. A 1 dB C++-to-reference tolerance cannot carry a claim that the switch corrects errors of −1.18 dB (CR3). |
| **CS-2 + CS-NW** | prefer | 1 | 0 | The Phase 04 rooms and W1/W2 are the scenes users and reviewers try first. CS-NW covers the ordinary "listener against the wall" action. |
| **CS-3 + CS-NW** | prefer (tie) if Seat 5 accepts the CI time | 1 | 0 | Adds 30 positions in measured-room geometries to the testing record. Wording must say "estimated inputs, model against model" (gate B failed). |
| **any set without CS-NW** | can live with | 0 | 2 | No case puts the listener within 0.5 m of a surface (addendum D-T1.5), so the first near-wall defect report comes from a customer. |
| **NW-3** | prefer | 1 | 1 | One constant ρ. Variance falls 4–7×, which means fewer escalations. A disclosed model change of +0.03 to +0.09 dB in W1 (C4 §2); whether that is acceptable is for Seats 1 and 2 to judge. Layout 4 still needs about 1 M paths. |
| **NW-2** | can live with | 1 | 1 | Two constants, h and r_near. Bias of 1–3 % (0.04–0.13 dB), and little gain at edges and corners, which is where the cost is. |
| **NW-1** | can live with, barely | 1 | 2 | W1 edge needs 1.6 M paths; layout 4 needs 1.4–47 M (C4). Cap hits become the routine result of a user action, they read low (F11), and the escalation channel floods. |

**Do D-T1.2–1.4 change with D-T2?** Yes, under L2-F2:
- N-1 rises to 2/2.
- Tol-3's cost becomes moot, because τ is then only the agreement allowance.
- NW-3's variance factor matters more: the W1 wall needs 7.1 M paths under NW-1 against roughly 1–1.8 M under NW-3 [Inferred from the 4–7× factor].
- T1-F's "later" rises to 2 unless the D-T2 condition below is met.

**Schedule and the §8 split rule.** Implementing T1-F in full is a lot for one session:
- Philox known-answer test and an FP-contraction policy;
- next-event estimation over lattice images;
- diagnostics and N-3;
- NW-3;
- the cross-OS check;
- the golden, the tracer test, the goldens update and a nightly run in one atomic push.

I would rather plan the named split now (phase-05h after §3 and R1) than rush the statistics. Before release a split costs bookkeeping hours, not customer trust, and D-T5.3 already lets Phase 08 go first, so binaural is not held up.

**Public wording (B7).** The field's own bar for "validated" is agreement with measurement: in the PTB round robin, only 3 of 17 programs matched measurement scatter and the jnds (Vorländer §11, round-robin I). We have not met that bar (gate B failed).
- **Allowed:**
  - "Tail level computed by a fixed-seed estimator of [model]; automatically tested against an independent implementation of the same model on N cases in 8 bands within τ dB, and against an independent ray tracer within 1 dB; bit-identical on the same machine; standard error reported in diagnostics."
  - "Belongs to the diffuse-rain method family" (F22). This states the method family, not that it was validated.
- **Forbidden:**
  - "validated" with no named test;
  - "validated method" (RQ-T1-4 uninformed);
  - "matches real rooms" or "physically exact";
  - any accuracy claim at 100 m (no reference) or near walls (unless CS-NW is in the set);
  - under NW-3, silence about the 0.5 m gather. It goes in the method notes.

**5. Evidence**
- Incidents: P8 `[Self-report: incident]`; V4, V6 `[Self-report: incident]`; DR1 `[Observed, press]`; AI2 `[Peer-report, 2026, no outcome]`.
- Costs: C4, C5, C8 and builder §3 (measured on the prototype; C++ unmeasured, O15).
- Corpus: G jnd 1 dB (Vorländer Table 6.1, 500–1000 Hz); round robin (Vorländer §11).
- Arithmetic [Inferred]: 1 % = 10·log10(1.01) = 0.043 dB, about 1/23 of the G jnd.
- AX5 risk [Inferred]: if one path with a 0.13 % share (largest at W1's reference positions, C4) flips branch across architectures, the amplitude changes by 6.5·10⁻⁴, about −64 dB relative to the tail. For a −30 dBFS tail that is about −94 dBFS, which fails AX5's −100 dBFS. A typical path (share ≈ 1/N) passes at about −126 dBFS. Near walls (shares of 5–73 %) a flip is worth dB.
- Customer reaction to near-wall low tails: [Hyp].

**6. Conditions of acceptance**
- **T1-F stays at 1/1 only with all of these:**
  - N-3 (or N-2 with a measured stopping bias below τ/3);
  - NW-3 or NW-2;
  - CS-NW;
  - the D-T1.2 cross-machine set (known-answer test, explicit FP contraction, no `<random>`, a pinned or owned sin/cos/log in the estimator);
  - **plus** a CI comparison of E_target across the three OSes on the agreement set and the CS-NW cases, reported against AX5;
  - the public wording above.
- **T1-A to 1/1:** D-T3 decided before the first release, with the per-scene-class numbers (D-T4a (vi)), and the limit stated on the product page.
- **T1-B to 1:** a measured C++ rate that puts the 8-instance 100 m load under D-T4a's 10 s anchor. C8's arithmetic says this is out of reach, so in practice it means T1-B plus a range limit, rated as T1-A.
- **S-2 to 1:** a per-seed spread printed beside every ensemble mean.
- **N-1, NW-1 to 1:** failed diagnostics escalate, plus a measured cap-hit rate on CS-NW and on the six Phase 04 rooms with the listener moved to a wall.
- **Tol-1:** take Tol-2 instead.
- **Any set without CS-NW:** add CS-NW.

**7. Hand-offs**
- Audibility of 0.03–0.09 dB, of 1–4 dB low tails, and of S-2 → Seat 1.
- Is NW-3 still "the same model"; N-rule statistics → Seat 2.
- Cross-architecture flips, CI time for CS-3, threads inside one solve → Seat 5.
- tailSeed meaning; whether cap hits are shown to users → Seat 6.
- Real near-wall positions → Seat 9.

**8. Premortem.** If T1-F ships with N-1 and NW-1, the first sign is a forum post saying "the reverb drops when I put the mic against the wall", from a trial user before any CI check catches it.

---

## D-T2

**1. Reading.** The precision certified and shipped under the settled < 1 % rule (AX36), and what it costs the user in waiting time. Cue: depth priced by effort (P8).

**2–4. Ranking and tension**

| option | label | now | later | reason |
|---|---|---|---|---|
| **L2-F2** | can live with | 2 | 2 | 33× the paths. 100 m: 4.7–6.0 s per emitter, so 9.4–12 s per instance. Through D-T4a's gate, 8 instances need about 75–96 s until the last one is audible at load [Inferred from the decider's scaling, single-thread prototype]. That exceeds the 10 s escalation anchor every time; Tol-2 needs about 2.6 s. Layout 4 at s = 1 ≈ 51 s per emitter; W1 wall 7.1 M paths. All this buys 0.043 dB, 1/23 of a jnd (audibility is Seat 1's). |
| **L2-F1** | can live with, barely | 1 | 2 | Pass or fail is itself random, so the CI gate is flaky by design. Reseeding after a fail is tuning, and it burns contract-engineer hours. |
| **L2-P** (only under T1-A/B) | can live with | 1 | 1 | Wording must exclude the outer bands until C9 and near-wall positions (addendum caveat: not certified). |

**5. Evidence.** Decider's L2-F2 scaling; C4; D-T4a (i) and (iv); Vorländer Table 6.1. C++ multi-thread speed is [Hyp].

**6. Conditions of acceptance**
- **L2-F2 to 1:** Maisara sees this cost line (33×, the 75–96 s load figure, 0.043 dB against the 1 dB jnd) before it becomes an AX row. Applying AX36 to an estimator is the decider's reading, not her recorded words. I am not reopening the < 1 % rule; I am asking that the price of this reading go to her (a challenge only if she wants it to be one).
- **L2-F1 to 1:** a decision rule fixed in advance (Seats 1 and 5), for example the doubling difference at 3σ of its own SE, so the result is repeatable.

**7. Hand-offs.** Whether 1 % is perceptual → Seat 1. The statistical form of the rule → Seat 2 and the interrogator. C++ times → Seat 5.

**8. Premortem.** If L2-F2 ships, every 100 m or near-wall project load escalates. Maisara stops reading the escalations, and the one that matters (a cap hit that reads 4 dB low) goes unseen.

---

**For the researcher or orchestrator:**
1. Cross-OS E_target comparison of the prototype or C++ on the agreement set and CS-NW: branch-flip count and residual against AX5's −100 dBFS.
2. Expected cap-hit rate under N-3 with NW-3 on the Phase 04 rooms with the listener at a wall.
3. C++ multi-thread time per emitter at SE 0.083 dB and 0.0145 dB at 100 m, for D-T4a (iv).
4. Schröder 2011 (RQ-T1-4): if obtained, it upgrades the public wording. It does not block anything.

Files read: /home/user/makroof/docs/review/phase-05b2/9-decider-convene-T1-T2-T6.md, /home/user/makroof/docs/review/phase-05b2/17-decider-convene-T1-addendum.md, /home/user/makroof/docs/review/phase-05b2/7-builder-D-T1-evidence.md, /home/user/makroof/docs/review/phase-05b2/14-researcher-T1-T2.md, /home/user/makroof/docs/review/phase-05b2/16-orchestrator-C4-near-wall.md, /home/user/makroof/docs/review/phase-05b2/13-decider-round4-T4a-final.md, /home/user/makroof/docs/phases/phase-05b2.md, /home/user/makroof/docs/PRD.md, /home/user/makroof/docs/corpus/vorlaender-auralization.md (Table 6.1, §11 round robin).
