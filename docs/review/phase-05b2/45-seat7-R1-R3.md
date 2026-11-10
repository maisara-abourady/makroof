# Seat 7 — ratings R1–R3 (Challenge 1, Q2a (B), Q2a (C))

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 7 POSITION: R1–R3 (Challenge 1, Q2a (B), Q2a (C) as a commitment)

As in my earlier rounds, two persona assumptions fall to the PRD. The product is a subscription whose paid value is editing, and saved work must render "exactly as saved" (FR-LIC-3, NFR-6). The team is Maisara plus contractors. I measure in contractor sessions, user wait at load and per edit, and trust that saved projects open and sound the same. My round-1 objection to blocking on time (4c-2, rated 2/1 because it "reopens AQ10", `3-seat7-T5-T4.md`) no longer applies: Maisara has lifted AQ10 for these questions (43, preamble).

**1. Reading**

| question | what it decides | cues it triggers |
|---|---|---|
| R1 | Whether the 100 m restore time is a hard gate | "My project won't open" (my 4c premortem); an escalation channel nobody reads (my D-T2 premortem) |
| R2 | Whether to buy large-room precision with load time | Depth priced by effort (P8) |
| R3 | Whether the debt that (A) leaves is scheduled or left silent | Retroactive change to saved work (V4, S6); quiet borrowing from later phases |

**2–4. Ranking and tension (now / later)**

**R1: Challenge 1**

| option | label | now | later |
|---|---|---|---|
| **yes** (blocking gate + W_max (A) with D-H1's margin) | prefer | 1 | 1 |
| no (recorded and escalated, AX38 4c) | can live with | 1 | 2 |

- **yes, now 1.**
  - It costs a timing gate, the D-H1 measurement and the work of setting the margin. That is contractor time, inside tolerance.
  - It is coherent only with the margin. Without it the gate fails by design at about 30.2 s against 30 s (phase-05h §3, D-H1), and timing noise burns sessions.
- **yes, later 1.**
  - W_max stays tied to the restore budget for good, so the precision cost Seat 1 measures in long-window rooms stays until (C).
  - A CI pass at ≤ 2.14 s does not guarantee a slower customer machine `[Hyp]`.
  - In return it bounds project load. One solve runs at a time per process (AX38 (i)), so 8 instances at 100 m serialise to about 8 × 2.14 ≈ 17 s `[Inferred]`. Without a cap, a later cost regression can grow that unseen.
- **no, now 1.** Same restore times as yes today, because (A) is sized to the same budget.
- **no, later 2.**
  - A C++ cost regression or a W_max change reaches users before anyone acts.
  - The safeguard is an escalation to Maisara against the 1/3/10 s anchors (AX38 4c). That is the channel my D-T2 premortem expects to go unread.
  - Undoing it after release means a slower-than-saved project load, which customers notice first.

**R2: Q2a (B)**

| option | label | now | later |
|---|---|---|---|
| (B) | can live with | 2 | 2 |

- **Now 2.**
  - Restore is 2.16–4.81 s at the decided n\*_max of 1 024 (C14 (c)). One gated scene, the low-α s = 1 cube at 4.81 s, is above the 3 s anchor.
  - Eight instances at that scene serialise to about 38 s before the last is audible, against about 17 s under (A) `[Inferred, from C14 (c) × 8]`.
  - Every edit at 100 m adds roughly 11× the diffuse work, about 1.4 s per emitter at 4 threads `[Inferred: 11 × 0.13 s, 22 (d), prototype]`. Editing is the paid value.
  - It requires Challenge 1 "no", so it carries R1's "no" debt.
- **What it buys:**
  - 100 m SE of 0.05–0.12 dB;
  - layout-4 one-end cases within Seat 1's floor (C17, reading 1).

  It does not remove the both-near residual (layout 5 both_corner 2.13 dB; C17, reading 3), and layout 5's VOV still fails (C17, reading 2). Whether the gain is worth having is Seat 1's to judge.
- **Later 2.** W_max sets the shipped bits (43 §3 register, S7). (B) is a cost paid at every project load from day one, and it can be withdrawn only by changing saved renders.

**R3: Q2a (C) as a commitment now**

| option | label | now | later |
|---|---|---|---|
| **schedule (C) now** | prefer | 1 | 1 |
| do not schedule | can live with | 0 | 2 |

- **Schedule now, now 1.** About one phase of Phase 07 rework, so roughly one or two contractor sessions under the two-session rule `[Inferred]`. It is a known, named cost.
- **Schedule now, later 1.** It repays Seat 1's 2/2 under (A) and frees W_max from the restore budget without making project load slower.
  - Risk: an asynchronous restore opens projects in the "settling" state (AX38 (iii)). Users hear the tail arrive. That is acceptable if offline bounce never uses an unsettled tail.
- **Do not schedule, later 2.**
  - The debt is invisible.
  - Long-window rooms keep 0.3–1.3 dB SE (43 §3), so large-room accuracy can never be claimed (my wording list).
  - If W_max is raised later, after release, every saved large-room project changes level by up to about that SE. That is a retroactive change to saved work (V4; NFR-6) `[Inferred]`.

**Shared debt (R1–R3).** Whatever W_max ships at first release defines how saved projects sound. A later raise, whether through (B) or after (C), must land before the first release or be versioned: the estimator parameters go into saved state, so old projects keep their N. Otherwise it is a deal change for existing customers.

**5. Evidence**
- Restore times: C14 (c).
- Margin: phase-05h §3, D-H1.
- SE under (A): C16 (f) and 43 §3.
- SE under (B): C17, readings 1–4.
- Anchors and gate serialisation: AX38 (i), (iii) and 4c, from BUILD_PLAN §2.
- W_max and per-emitter time: 22 (d), prototype. C++ is unmeasured.
- Incidents: V4 `[Self-report: incident]`; my premortems in `3-seat7-T5-T4.md` and `18-seat7-T1-T2.md`.
- Host behaviour on slow restores ("not responding"): `[Hyp]`. **For the researcher:** do the major hosts (Logic, Live, Cubase, Bitwig) have restore watchdogs or hang dialogs, and at what times?

**6. Conditions of acceptance**
- **R1 "no" to 1/1:**
  - the restore record is a CI artifact compared run to run, so a regression of more than D-H1's spread fails as a finding, not only as an escalation;
  - W_max cannot change without a board round.
- **R1 "yes" stays at 1/1** only if all of these hold:
  - D-H1's margin is set from C++ data before the gate exists (already in phase-05h §3);
  - a gate failure is treated as a defect and never "fixed" by rerunning the job;
  - the gate runs on the Release build.
- **R2 (B) to 1:**
  - (C) lands first, so that (B)'s W_max is no longer on the synchronous restore; or
  - a measured C++ cost puts every gated restore at ≤ 3 s and 8-instance 100 m load at ≤ 10 s.
- **R3 "do not schedule" to 1:** W_max (A) is declared permanent for the first release, and the product page states that large absorbing rooms are approximate. Scheduling (C) is cheaper than that wording.
- **R3 "schedule now" stays at 1:** (C) is placed before the first public release, with its W_max raise in one golden round; or, if it comes after release, the estimator parameters are versioned in saved state.

**7. Hand-offs**
- Whether (B) meets the floor, and whether 0.05–0.12 dB is worth the load time → Seat 1.
- Timing-gate flakiness, the D-H1 margin and the (C) rework estimate → Seat 5.
- The "settling" state on load under (C), and whether large-room approximation is shown in the UI → Seat 6.
- How often producers use 100 m and long-window absorbing rooms → Seats 8 and 9.
- Versioning estimator parameters in saved state → Seat 5, with a contract/state AX if it is adopted.

**8. Premortem.** If "no" plus (B) ships and fails, the first sign is a trial user's post: "the arena preset takes 40 seconds to open my session and Logic says not responding". It arrives before Maisara reads the escalation record.
