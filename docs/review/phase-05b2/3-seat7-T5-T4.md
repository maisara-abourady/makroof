# Seat 7 (founder) — positions on D-T5 and D-T4 (2026-11-09)

Verbatim output of `seat7-founder`, convened by `1-decider-convene-T5-T4.md`; saved by the orchestrator.

Two assumptions in my persona don't hold here, and the PRD wins on both. First, the price is a subscription of $10–20 per month with fewer than 500 subscribers in year one (PRD "Business model"), not a one-time perpetual price. Second, the team is Maisara plus contracted engineers (PRD "Team"), not one founder coding with AI. So the cost that matters is contractor hours, and I measure trust as monthly churn and how many trials convert to paid. PRD L125 says conversion depends only on editing, because rendering never stops. The year-one revenue ceiling is at most $5k–10k a month `[Inferred: 500 × $10–20]`.

---

**DECISION D-T5: SEAT 7 POSITION**

1. **Reading.** This decides how many energy models and code paths stay alive, and what we may say in public about the tail level. Cues: depth being priced by effort (P8); work borrowed from later phases; a claim made ahead of the evidence.

2. **Ranking.**
   - **(1)** 5.1-A *prefer*. 5.1-C *can live with*.
   - **(2)** 5.2-A *prefer*. 5.2-B and 5.2-C: not rated (out of bounds).
   - **(3)** 5.3-D *prefer*. 5.3-A *can live with*. 5.3-B *can live with*. 5.3-C *can live with, barely*.
   - **(4)** 5.4-A *prefer*, if C1 is done before the decision. 5.4-B *can live with*.

3. and 4. **Tension now / later**

| option | now | later | why |
|---|---|---|---|
| 5.1-A | 1 | 0 | One model sets the level in all 8 bands; this session's work only. |
| 5.1-C | 1 | 2 | Two level models chosen per band, kept forever. A second switch, with another round of golden churn, comes when the outer bands are validated. Public wording would have to disclose a known-wrong approximation in 5 of 8 bands. |
| 5.2-A | 1 | 1 | The AX16 list survives only to count k_real. That is existing, tested code and one level model. Debt: it can't be deleted until AX22 is revisited. It also keeps candidate (d) open, which may be the cheapest D-T1. |
| 5.3-A | 0 | 1 | A diagnostic taken from the model we just declared wrong. Someone will read it as the truth later. |
| 5.3-D | 0 | 0 | Costs nothing and is labelled honestly. A later directional tail would be its own AX and phase, not a hidden loan. |
| 5.3-B | 2 | 2 | Widens D-T1's required output from one number per emitter and band to per-direction tallies, for a diagnostic nothing reads. That can shrink the set of D-T1 candidates and add contractor sessions. Seat 2 owns whether it does. |
| 5.3-C | 2 | 2 | Changes Phase 08's scope and adds a 05b/05h dependency. That delays binaural, the mode headphone-first producers buy. RQ6 has no perceptual basis yet. It invites a "directional late reverb" claim that Seat 1's Tier A rule forbids. |
| 5.4-A | 1 | 1 | Generic, one code path, and two independent checks for the published testing record (AI2). Risk: if the outdoor preset gets a faint tail that sounds wrong, users read it as "outdoor sounds like a room" and churn. C1's size is unknown. |
| 5.4-B | 2 | 2 | A new AX criterion invented this session. It adds a threshold seam that Phase 10 must test under automation for good. It also drifts toward environment-shaped logic, which strains the PRD's NFR-8 promise. |

**What each option lets us say in public:**
- 5.1-A allows: "tail level from a model that agrees with an independent ray tracer within 0.08 dB (500 Hz–2 kHz, 15 synthetic cases)". It forbids "matches real rooms": gate (B) failed, and BRAS was model against model.
- 5.1-C requires disclosing the band split.
- 5.3-C tempts an unproven directional claim.
- 5.4-A allows "outdoor scenes include ground scatter".
- 5.4-B forbids presenting "outdoor stays dry" as physics.

**What the team can sustain:** 5.1-A + 5.2-A + 5.3-D + 5.4-A is one level model and one existing counting list. Every other choice adds a path that Maisara cannot check by reading code (CLAUDE.md).

5. **Evidence.**
- 5.3 facts: from the code (NoiseTail.cpp L234–244 is diagnostic only; phase-08.md item 5 builds a diffuse-coherence tail and reads no tail direction).
- Validation scope: phase-05b2 §0.1 and §0.3.
- Simple beats deep in sales: P8 `[Self-report: incident]`.
- Retroactive changes cost trust: V4 `[Self-report: incident]`.
- Visible testing record: AI2 `[Peer-report, 2026, no outcome]`.
- Churn effect of a wrong outdoor tail: `[Hyp]`.
- I make no acoustic claims; audibility belongs to Seat 1.

6. **Conditions.**
- 5.1-C: a named phase and AX that validate the other five bands and remove the split → 1 later.
- 5.3-B: only if Seat 2 shows that tallies don't remove any D-T1 candidate → 1.
- 5.3-C: make it a later, separate AX, contingent on a positive RQ6 and a Seat 1 test, and don't gate Phase 08 on it → 1.
- 5.4-B: only if C1 shows 5.4-A's tail is audible by Seat 1's bar, with a continuous criterion rather than a threshold → 1.
- 5.4-A: C1 is computed before the decision round.

7. **Hand-offs.** Audibility of the band seam and the outdoor tail → Seat 1. Direction tallies against D-T1 candidates → Seat 2. Phase 08 start order → Seat 4. Outdoor preset character → Seats 8 and 9.

8. **Premortem.** If 5.3-C or 5.1-C wins, binaural ships a phase late on a split model, and the contractor's second-switch invoice is what Maisara notices first.

---

**DECISION D-T4: SEAT 7 POSITION**

1. **Reading.** A per-instance memory ceiling for a product that needs several instances by design: FR-SIM-7 multi-stem scenes, and one builder thread per instance (from the code, IrBuilderThread.h). Cues: ruin before growth; a deal changed after release (V4); saved work that stops working (DR1, V6).

2. **Ranking.**
   - **(a)** 4a-2 *prefer*. 4a-1 *can live with*. 4a-3 *cannot live with*.
   - **(b)** 4b-1 *prefer*. 4b-2 *can live with*.
   - **(c)** 4c-1 *prefer*. 4c-2 *can live with*. 4c-3 *cannot live with*.

3. and 4. **Tension now / later**

| option | now | later | why |
|---|---|---|---|
| 4a-1 ≤128 MB | 2 | 2 | Rules out storing N² per band at 100 m. A 9600² float32 matrix is 368.6 MB per band. The (b)-style history is 9600 × 2100 × 4 B ≈ 80.6 MB per band per emitter, so two emitters come to ≈ 161 MB, over 128 MB `[Inferred]`. That means more D-T1 sessions and a real chance of forcing D-T3. |
| 4a-2 ≤1 GB | 1 | 1 | N² fits one band at a time. Matrix-free, structure-based and Monte Carlo plausibly fit `[Hyp; Seat 2]`. Four stems rebuilding at once on project open is about 4 GB on top of the session, which is tight on 8 GB machines `[Hyp]`. |
| 4a-3 ≤4 GB | 1 | 3 | 4 GB × several instances, all rebuilding on project load, means "my project won't open" on 16 GB machines. That breaks NFR-6 ("any machine") in spirit and does to saved work what DR1 did to licences. It creates the worst support tickets and churn. |
| 4b-1 | 0 | 1 | Measures what the user waits for. Resident cache memory counts inside (a), so it is bounded. |
| 4b-2 | 1 | 1 | Pessimistic. It may trigger the W1 > 700 ms remedy in Phase 10 without need. |
| 4c-1 | 1 | 1 | A memory miss is a crash or a refused open, so it blocks. A time miss is lag with crossfades and no clicks (AQ10), so it is recorded. |
| 4c-2 | 2 | 1 | Reopens Maisara's AQ10 decision of 2026-11-05 this session, and RQ5 base rates are unknown. But editing is the paid value (PRD L125), so a slow full rebuild at large sizes hits trial conversion. |
| 4c-3 | 1 | 3 | Memory overruns surface in Phase 13 or at customers, after release. A fix then is retroactive (V4) and breaks saved large-room projects. |

**Does any ceiling rule out every candidate class at 100 m?** No, on arithmetic alone `[Inferred; Seat 2 confirms]`. The dense kernel (3–6 TB) fails under every ceiling. 4a-1 leaves only classes that store less than N² per band, and even (b) is marginal there. So 4a-1 is the ceiling most likely to force D-T3.

**Cost of narrowing "any environment":**
- Before release, it is a change to PRD wording and the outdoor and festival presets (FR-3D-3), plus a major contract version bump. That is Maisara's call, and moderate.
- After release, it is retroactive: saved projects with rooms above the new limit would no longer open exactly (NFR-6, V4). That cost is veto-grade.

5. **Evidence.**
- Phase 07 RSS (+122.6 MB, Linux only) and full-rebuild times: BUILD_PLAN §0 row 07.
- Kernel sizes: phase-05b2 §0.3.
- Retroactive changes draw backlash: V4 `[Self-report: incident]`.
- Licences that keep working offline: V6 `[Self-report: incident]`.
- Licences deactivated after an exit: DR1 `[Observed, press]`.
- Support and OS work are the real load: R1 `[Peer-report]`.
- I have no incident on plugin memory, so every hardware claim is `[Hyp]`.
- For the researcher:
  - RQ1: base RAM of current Macs (I believe it went to 16 GB in late 2024; unverified), and the Ableton Live 12 and Logic minimums.
  - RQ2: memory per instance of Altiverb and Spat Revolution.
  - RQ3: instances per session, because FR-SIM-7 makes this the multiplier.
  - Any data on what share of plugin support tickets come from memory or crashes.

6. **Conditions.**
- 4a-3: a process-wide build serialiser, so peak equals one instance's ceiling, plus a Phase 13 test that opens a 10-instance project at 100 m on a 16 GB machine → 2.
- 4a-1: Seat 2 shows at least one class fits with both emitters → 1.
- 4c-2: instead of blocking, record the full rebuild at 100 m and report it to Maisara in the D-T1 decision if it exceeds an RQ5 anchor (a variant I added) → 1.
- 4c-3: Phase 13 holds a binding memory gate before the first release → 2.
- For every option: any D-T3 narrowing must happen before the first release, never after.

7. **Hand-offs.**
- Concurrency on project load and host timeouts → Seat 5.
- Viability of each candidate class under each ceiling → Seat 2.
- Room sizes near 100 m in real venues → Seat 9.
- Edit-to-hear delay → Seat 6.
- Narrowing AX6 → Maisara.

8. **Premortem.** If 4a-3 or 4c-3 wins, the first sign is a support thread titled "project won't open since I added the third stem". It comes within the first month of trials and cuts conversion against the target of fewer than 500 subscribers.
