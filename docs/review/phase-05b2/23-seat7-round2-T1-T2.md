# Seat 7 — second round, D-T1.3, D-T1.6 and D-T2

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 7 POSITION (second round: D-T1.6 NW-4C and NW-3, D-T1.3 N-3W*, D-T2 L2-F1R)

Two persona assumptions still don't hold, as in round 1 (`18-seat7-T1-T2.md`), and the PRD wins on both. The product is a subscription whose paid value is editing, and saved work must render "exactly as saved" (PRD FR-LIC-3, NFR-6). The team is Maisara plus contracted engineers. So I measure four things: contractor sessions, how long the user waits per edit, trust that saved projects render the same, and whether the public wording holds.

**1. Reading.** The question is how near-wall variance is removed, how N is chosen within a work cap, and what precision AX36 buys. Cues it triggers:
- a testing record that overstates itself (AI2);
- a retroactive change to saved work (V4, S6);
- depth priced by effort (P8);
- a flag that fires so often nobody reads it.

**2–4. Ranking and tension (now/later)**

| option | label | now | later |
|---|---|---|---|
| **(a) NW-4C** | prefer | 1 | 1 |
| **(b) NW-3**, re-rated | can live with | **2** | **2** (was 1/1) |
| **(c) N-3W\* as composed** | can live with only under the conditions in item 6 | 2 | 2 |
| (c) N-3W\* with the item-6 conditions | prefer | 1 | 1 |
| **(d) L2-F1R** | can live with | 2 | 2 |
| (d) the bias reading, for comparison | prefer | 1 | 0 |

**(a) NW-4C**
- **Now 1.** The contractor builds two path sets, the weight, and the both-near flag. One-end cases sit at reference-position SE: 0.013–0.016 dB in W1, 0.068–0.114 dB in layouts 4 and 5, largest history share ≤ 0.54 % (C12 (a), reading 1).
- **Cost.** At reference positions the median cost is 1.02× forward-only, the maximum 2.57× (C12 (c)). The 100 m edit wait stays within W_max, about 0.13 s per emitter at 4 threads (C12 (d)).
- **It changes no model.** So "same model" stays sayable, and the 0.5 m-gather disclosure I demanded under NW-3 goes away.
- **Later 1.** Both-near cases revert to NW-1 behaviour:
  - capped SE 0.15–0.29 dB, VOV 0.29–0.32 in the W1 sweep;
  - in the 32 k runs, 32 k and long runs differ by up to 5.2 dB (layout 4 corner);
  - a 0.21 dB step between 0.11 and 0.10 m (C12 (b)).

  This is a known weak region, but it is bounded and flagged.
- **Does NW-4C meet my round-1 "NW-3 or NW-2" condition?** Yes for its purpose, which was that near-wall cap hits must not be the routine result of an ordinary user action.
  - The cap-hit rate I asked for is **0 of 17** on CS-NW+ and the six Phase 04 rooms with the listener or emitter at a wall (C12 (d)).
  - It meets the condition better than NW-3, with no model change.
  - It does not meet it for both-near positions. That residue is covered by the conditions in item 6.

**(b) NW-3, re-rated: my cell changes from 1/1 to 2/2.**
- My round-1 cell rested on "+0.03 to +0.09 dB, disclosed". The measured clamp bias is:
  - **+0.322 dB** at layout 5's absorbing wall and +0.109 dB at layout 4's floor (19 §6);
  - −0.11 / −0.25 dB at layout 4's wall and edge (19 §4).
- **Now 2.** +0.322 dB exceeds τ = 0.25 dB. The pre-registered gate then either fails or needs an exemption written around a known bias. That is a testing record that hides its worst case.
- **Later 2.** The bias is systematic: every render, every machine, next to absorbers (vocal booths, treated rooms). Removing the clamp after release moves saved projects' tail level by up to 0.32 dB. That is a retroactive change to saved work (V4, S6; NFR-6) `[Inferred]`.
- This is not veto-grade, because disclosure is possible. But with NW-4C unbiased at about the same cost, NW-3 spends trust for nothing.

**(c) N-3W\* as composed**
- **Now 2. Conflict 1:** the 8 000-history pilot costs 2.7–3.1× W_max in W2 and in the gated 100 m flutter cube. So n_cap = 0 and no final range is left (C12 (d), reading 3). The contractor would implement a rule that fails a gated scene on its first C++ run.
- **Later 2. Conflict 2:** the final range is smaller than the discarded pilot (60–6 200 histories against 8 000). Final SE exceeds 0.083 dB in 6 of 17 cases.
  - A wording of "SE 0.083 dB" would then be false about a third of the time (C12 (d) continued, reading 3).
  - The pilot is 10–46 % of W_max at reference positions, so most of the user's wait is work that is thrown away.
- **The slope flag fires almost everywhere**, including 2.93 at W1's well-behaved reference positions. That floods the escalation channel, which is my round-1 premortem.

**(d) L2-F1R**
- **Now 2:**
  - At the gated 100 m scene it needs ≈ 7× W_max. Restore comes to ≈ 3.7 s (1.88 + 1.84 s) against 2.14 s (C12, coupling section).
  - The edit wait at 100 m is ≈ 0.9–1.0 s per emitter at 4 threads, about 1.9 s for two.
  - Layout 4 at s = 1 takes ≈ 30 s (21, D-T2).
  - What it buys: SE 0.0187 dB, about 1/53 of the G jnd, against 0.083 dB (0.08 jnd).
- **Later 2:**
  - There is a cap hit in 1 of 17 near-wall cases (concert_hall_box).
  - It holds a pending restore-gate conflict (Challenge 1).
  - The suite runs about 50 cases at p ≥ 0.999 each, so 1 − 0.999⁵⁰ ≈ 4.9 % chance the fixed-key suite fails somewhere. With reseeding forbidden, that failure costs contractor hours `[Inferred]`.

**Debt common to all (D-T1.3 and D-T2).** Under N-3W\*, the SE target and the pilot rule set N, so they set the shipped bits of every saved project. Changing either after release changes saved renders by up to about one SE. Fix both before the first release; after it, any change is a deal change that must be pre-announced (S6) `[Inferred]`.

**5. Evidence**
- C12 (a), (b), (d) and the coupling section (`22-orchestrator-C12.md`); 19 §1, §4 and §6; 21 (D-T1.6 and D-T2 sections).
- G jnd 1 dB: Vorländer Table 6.1, as cited in 21. I did not re-read it this round.
- Arithmetic `[Inferred]`:
  - 10·log10(1.0043) = 0.0186 dB;
  - 0.083 dB ÷ 4.343 = 1.91 %;
  - 1 − 0.999⁵⁰ = 0.049.
- Incidents: V4, S6 `[Self-report: incident]`; AI2 `[Peer-report, 2026, no outcome]`.
- How often users put both source and listener within 0.5 m of surfaces: `[Hyp]`.
- C++ cost per evaluation is unmeasured. Every time figure here is from the prototype.

**6. Conditions of acceptance**
- **NW-4C stays at 1/1 with all of these:**
  - The both-near flag is deterministic, written to TailMatch and the diagnostics, and its threshold is fixed before release.
  - W1 both_wall and both_corner join the reported (not gated) set, so the record shows the weak region.
  - Wording: no accuracy claim when both ends are flagged, or at layout-4/5-type edges and corners, where the reference is uncertified (C12 (a), reading 2).
  - D5's face-hash golden covers both path sets.
- **NW-3 to 1:** none that I can name, short of a clamp whose measured bias at absorbing faces in layouts 4 and 5 is ≤ τ/3 and budgeted. That is Seat 2's to design.
- **N-3W\* to 1/1:**
  - **Conflict 1:** define the pilot in work. n\* = min(8 000, the histories that fit a fixed, published share of W_max), counted in image evaluations, which are deterministic under D5. The share is Seat 5's to set; a statistical floor on the pilot is Seat 2's. It must be re-checked against the C++-derived W_max on every gated scene.
  - **Conflict 2:** a minimum final N of at least the effective pilot size. C12 says this costs ≤ 2× the pilot and fits W_max in all 17 cases. The diagnostics must report the achieved final SE, and the public wording must say "target SE 0.083 dB; achieved SE reported", never "SE ≤ 0.083 dB".
  - **Flags:** R and VOV are flagged. The slope is only reported until its threshold stops firing at reference positions. No flag that fires at W1 reference positions reaches users or the escalation channel.
- **L2-F1R to 1/1:**
  - Maisara chooses it knowingly, from this cost line: about 7× W_max at 100 m, restore 3.7 s against 2.14 s, about 2 s edit wait at 100 m, about 30 s in layout 4, 1/53 of a jnd.
  - The restore conflict is resolved, whether by Seat 5, by her, or by a measured C++ time under the bound.
  - The SE target is fixed before the first release.
  - Otherwise I prefer the bias reading. The decider's challenge in 21 meets my round-1 L2-F2 condition, which was that she sees the price of the reading.

**7. Hand-offs**
- Audibility of the 0.21 dB both-near step, of 0.04 dB per cm, and of 0.0187 against 0.083 dB → Seat 1.
- The layout-4 emitter-edge outlier (z −3.7); the uncertified references at layout 4 and 5 edges; the pilot floor and the slope estimator → Seat 2.
- The W_max share, the C++ re-derivation, and the restore-gate veto under L2-F1R → Seat 5.
- Whether the both-near flag is shown to users → Seat 6.
- How often real setups put both ends near surfaces → Seats 8 and 9.
- Challenge 1 and the AX36 reading → Maisara.

**8. Premortem.** If NW-3 ships and is later replaced, the first sign is a forum post saying "the update changed my mix near the vocal-booth panels", about a level shift of 0.1–0.3 dB in saved projects. Maisara hears it from a paying subscriber, not from CI.

Files read:
- /home/user/makroof/docs/review/phase-05b2/21-decider-decision-T1-T2-T6.md
- /home/user/makroof/docs/review/phase-05b2/22-orchestrator-C12.md
- /home/user/makroof/docs/review/phase-05b2/19-orchestrator-NW4-and-checks.md
- /home/user/makroof/docs/review/phase-05b2/18-seat7-T1-T2.md
