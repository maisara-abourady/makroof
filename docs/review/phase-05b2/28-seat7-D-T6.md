# Seat 7 — D-T6 (convened late, interrogator correction 17)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 7 POSITION (D-T6, convened late after interrogator correction 17; one rating of RS-2+ / B6-1F / M-2 plus the comparison rows)

PRD assumptions still in force from my rounds 1 and 2 (`18-seat7-T1-T2.md`, `23-seat7-round2-T1-T2.md`): the product is a subscription, saved work must render exactly as saved (FR-LIC-3, NFR-6), and the team is Maisara plus contractors. My measures here are what can be said in public, what the testing record shows, trust in saved work, and contractor hours.

**1. Reading.** D-T6 decides what stands behind the phase-05b2 sentence "in rooms where AX16 is exact per reflection order (uniform α) nothing audible changes, within D-T6's bound" (phase-05b2.md L115–117, listening checklist L286). Cues:
- a claim ahead of its evidence (AI2; Seat 1's Tier A rule);
- a threshold chosen after the result is known;
- a testing record that hides its worst case;
- a flag that fires where the record says the result is fine (correction 18).

**My D-T1.4 reason has changed (correction 13).** My Tol-2 cell (1/0) said the uniform-rooms claim "stays claimable" because B6-2 gated |ΔL| ≤ 0.68 dB. Under B6-1F, 0.68 dB is only a flag, so the claim rests on a pre-registered flag plus the paired report, not on a gate. Tol-2 stays 1/0, because τ = 0.25 dB still sets both the gate and the flag level. The reason now reads "claimable while no flag fires".

**2–4. Ranking and tension (now/later)**

| option | label | now | later |
|---|---|---|---|
| **RS-2+** | prefer | 0 | 0 |
| RS-2 | can live with | 0 | 1 |
| RS-1 | can live with | 1 | 2 |
| **B6-1F** | prefer | 0 | 1 |
| B6-1 | can live with | 1 | 1 |
| B6-2 (gated) | can live with | 1 | 2 |
| **M-2** | prefer | 0 | 0 |
| M-1 | can live with | 1 | 1 |
| **Composite RS-2+ / B6-1F / M-2** | prefer | 0 | 1 |

**Room set**
- **RS-2+:** the small room and its positions were fixed before C11 (21, D-T6). That is a trust deposit: the record can say "rooms and bound fixed before any result". It also adds the room size a home producer actually uses, which is my target user. Contractor cost is one fixture and a reference ladder. The gate passes at shipping N with about 15× margin (SE 0.006 dB, replicates within ±0.015 dB; C14 (d)), so a first-draw failure, which Seat 5 said "has no legitimate fix", is very unlikely [Inferred from C14 (d)].
- **RS-2, later 1:** the uniform cases cover three geometries, all of them medium to large. The 0.43 dB figure comes from one geometry (D6-L2). A claim about "uniform rooms" would rest on no small room.
- **RS-1, now 1 / later 2:** `stone_box` is the only uniform room (D6-L1). The wording must shrink to "in one test room". Any wider claim overstates the record.

**Bound**
- **B6-1F:** the gate proves the C++ does what the model predicts. The 0.68 dB flag and Seat 1's 0.5 jnd flag are pre-registered, so the "nothing audible" wording is tied to thresholds set before the data. Later 1 has two causes:
  - Nothing blocks a merge when a flag fires, so the public wording can go stale silently.
  - The ΔL_ref golden is regenerated whenever `ref_hybrid` changes (S5 register). After release, that moves the shipped uniform-room level with no absolute anchor, which is a retroactive change to saved work (V4, S6) [Inferred].
- **B6-1 (no flags), now 1:** nothing is pre-registered for the audibility claim, so any "nothing audible" wording would be chosen after reading the report. That is a threshold fitted to the result.
- **B6-2 gated, later 2:** it makes the claim a gate, but on a bound from one geometry (D6-L2). If the physics of a small room differ, it fails a correct C++. The fix is then either retuning, which NFR-8 forbids, or an exemption, which leaves a record that hides its worst case. Either way it costs contractor hours.

**Mixed rooms**
- **M-2:** five of the six Phase 04 rooms are mixed (9, D-T6). These are the rooms reviewers open first. M-2 gives each of them an independent tracer check, outside our own model. The tracer runs are prototype runs, not C++ contractor work [Inferred]. The tracer cost itself belongs to Seat 9.
- **M-1, now 1 / later 1:** a check of C++ against `ref_hybrid` is model against model. The independent-tracer wording I allowed in round 1 would have to name the few rooms that have committed tracer data.

**Public wording each option allows or forbids**
- **B6-1F + RS-2+:**
  - Allowed, measured form: "in the N even-absorption test rooms, fixed in advance, the tail level changed by at most X dB per band, below the 1 dB level jnd". X is the reported maximum.
  - "Nothing audible changed" also needs Seat 1's confirmation, because ΔC80 and ΔEDT have their own jnds (1 dB and 5 %; Table 6.1).
  - If any flag fires, the claim is withdrawn for that room.
- **B6-1:** only "the C++ matches the reference model's predicted change within 0.25 dB". No audibility claim.
- **B6-2 gated:** "≤ 0.68 dB in every test room" is allowed, as a measured statement, not a perceptual one.
- **RS-1:** "in one test room" only.
- **RS-2:** the measured statement is allowed, but it must not cover small rooms.
- **M-2:** "mixed rooms were checked against an independent ray tracer and the results were reported". Never "within X dB", because the mixed rooms are reported, not bounded.
- **All options:** the plain-language phrase is "the same material on every surface". "Uniform-α" must not appear in public copy. "Physically exact" is never allowed.

**Correction 18, from my seat.** The small room counts as both-near under D-T1.6 (d_L 0.425 m, d_E 0.5 m), yet its error is 0.006 dB (C14 (d)). That means the product would show an "approximate" note in a room our published record shows correct to ±0.015 dB, which undermines both the note and the record.
- Keep the room gated, at shipping N, under D-T1.5's no-reseed rule. Moving the positions now, after C14, would be post-hoc tuning of the test set.
- My round-2 rule ("no accuracy claim when both ends are flagged") still applies to both-near positions in general. This room's ΔL agreement does not license an accuracy claim for both-near positions.

**5. Evidence**
- G jnd 1 dB, C80 jnd 1 dB, EDT jnd 5 %: Vorländer Table 6.1 (corpus L2056–2062, re-read this round).
- 0.68 dB is 0.68 of the G jnd; 0.25 dB is a quarter of it [Inferred].
- C14 (d) margin: 0.015 dB against τ = 0.25 dB, about 17× by my arithmetic; C14 states about 15×.
- Room set facts: D6-L1 and D6-L2 (21).
- Prototype ΔL in W1 is +0.32 / +0.27 dB (26, "What checks out").
- Incidents: V4 and S6 [Self-report: incident]; AI2 [Peer-report, 2026, no outcome].
- That phase 05b2 ships before any release, so no customer's saved projects move now: [Inferred].

**6. Conditions of acceptance**
- **B6-1F to later 0:**
  - (i) After the first release, any regeneration of the ΔL_ref golden that moves a uniform-room ΔL by more than τ/3 is a release-note item announced in advance (S6).
  - (ii) The public uniform-room wording is taken from the latest paired report, and a fired flag removes it before release.
  - (iii) The date the room set was fixed (pre-registration) is recorded in the report.
- **RS-1:** use RS-2+ instead.
- **B6-2:** demote it to a flag, which is B6-1F.
- **M-1:** name the rooms that have tracer data in the wording, or use M-2.

**7. Hand-offs**
- Whether ΔL ≤ 0.68 dB with ΔC80 and ΔEDT is "nothing audible": Seat 1.
- The both-near criterion not carrying over between rooms (C14 (d)): Seats 2 and 6.
- Whether a gate N other than shipping N is acceptable: Seat 5.
- Tracer cost: Seat 9.

**8. Premortem.** If B6-1F ships without condition (ii), a flag fires on a later `ref_hybrid` change, the changelog still says "nothing changed in even rooms", and a reviewer who null-tests `stone_box` finds a 0.7 dB shift before Maisara does.
