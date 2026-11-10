# Seat 5 — ratings R1–R3 (Challenge 1, Q2a (B), Q2a (C))

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 5 POSITION: ratings R1 (restated), R2 (Q2a (B)) and R3 (Q2a (C) as a commitment now)

Sources read:
- 43 (decider, §2–§4);
- phase-05h §3 (D-H1);
- C14 (c);
- C16 (f);
- C17;
- BUILD_PLAN AQ10 and AX38.

Nothing here is acoustic. Times are the prototype's at 1 thread, which stands in for the C++ cost [Inferred, O15].

**1. Reading**

The question is how much diffuse-solve work may sit on the host's synchronous restore and prepare calls, and whether to schedule moving it off them.

My cues:
- §4.1: unbounded work on a host thread.
- §10.3: "what the host can do to me". Restore is called on the host's thread, 14 times in a row under pluginval (AX38 4c).
- S5: offline renders must equal real time.
- Criterion 5: reversibility.

**2–4. Ratings (now / later)**

**R1, restated, unchanged.**
- **"Yes": prefer, 1/1.** This holds only with D-H1's margin in place.
- **"No": can live with, 1/2.**

My condition on "yes" is that D-H1 takes its margin from W_max, not from the gate. Its inputs, from C++:
- the worst realised-work ratio at the two gated builds, pre-registered (AX41 allows about 1.05);
- the restore spread taken from the worst of at least 10 runs, not best of 3 (row 07's 1.884 s is a best of 3).

What the margin costs [Inferred]:
- The diffuse budget is only 0.259 s (2.143 − 1.884).
- A 3 % spread on the 1.884 s build is 0.057 s, which is 22 % of that budget.
- Seat 1 pays for it through a smaller W_max.

**R2, Q2a (B): cannot live with, 2/3.**
- **Now 2.** Every gated 100 m scene restores in 2.16–4.83 s, and 14 restores take 30.2–67.6 s against pluginval's 30 s watchdog (C14 (c)).
  - This is the same order as L2-F2 (55–69 s), which I vetoed, and L2-F1R (about 52 s), which I rated 2/3.
  - Project load takes about 8 × 4.8 ≈ 39 s until the last of 8 instances is audible, against the AX38 (iv) 10 s mark [Inferred: it assumes serial restore, or serialisation through the one-solve-per-process gate].
- **Later 3.** It commits the synchronous host calls to multi-second blocks at large rooms, with nothing to bound them, because it requires Challenge 1 "no".
  - How long hosts tolerate a blocked `setStateInformation` is still unsourced. I asked the researcher in round 1, and dossier 14 has no finding.
  - Undoing it is either:
    - back to (A): a parameter change, but it changes shipped bits, so a golden round plus an announced change once projects exist (Seat 7); or
    - (C): about one phase of rework.
  - Evidence arrives only from the AX38 4c records and a beta, after users depend on it.
- **Seat 1's floor under (B)** is Seat 1's to judge. I note that C17 shows one-end SE falling to 0.06–0.22 dB, while both-near cases still fail.

**R3, Q2a (C) scheduled now (with (A) until then): prefer, 1/1.**
- **Now 1.** It reserves one phase of Phase 07-class rework. The work spans:
  - restore, prepare and `reset()` / `ResetStep3`;
  - the synchronous class of the AX38 gate;
  - the offline wait;
  - TSan and pluginval re-runs.

  Nothing is built on (A)'s restore path yet. The restore gate is not implemented until D-H1 is recorded (phase-05h §3).
- **Later 1.** After the move, restore returns after the specular build. The restore gate then measures the build alone (row 07: 14 × 1.884 = 26.4 s, which leaves margin [Inferred]). W_max is bounded by Seat 6's 3 s per emitter and the AX38 (iv) load mark instead of the watchdog. That removes the conflict between my gate and Seat 1's floor.
- **The remaining risk is mine.** Between restore and the end of the solve, a real-time instance plays a provisional state. A real-time (online) bounce started right after load would capture it. Hosts that do not signal offline rendering reliably are the hole [Hyp]; §9 says to bound the wait and record it.

**Not scheduling (C): can live with, 1/2.**
- **Now 1.** It costs nothing at the moment.
- **Later 2.**
  - Seat 1's only repayment route is a larger W_max, and that runs straight into my restore gate. The pressure to lift the gate becomes permanent.
  - The rework cost grows with every phase that builds on the synchronous restore: Phase 08's per-mode records, the Phase 10 cache, Phase 11's "settling" UI [Inferred].
  - Evidence: the AX38 4c records and Phase 12's presets.

**5. Evidence**
- **Restore times under (A) and (B):** C14 (c).
- **The gate and the watchdog:** AX38 4c and the amended AQ10 (14 × t_restore ≤ 30 s).
- **Build time:** BUILD_PLAN §0 row 07 (1.884 s, best of 3).
- **No margin as applied:** D-H1 (14 × 2.141 = 29.98 s, about 30.2 s at a ratio of 1.05).
- **SE under (B):** C17.
- **The load-time mark:** AX38 (iv), 10 s.
- **Inferred:** load-time serialisation, the 26.4 s figure after (C) and the growth of the rework cost.
- **Hypothesis:** host offline signalling.

**6. Conditions of acceptance**
- **R2 (B), 2/3 → 1/1:** only together with (C). Raise W_max only once the solve is off the synchronous calls. Nothing smaller lowers it.
  - An option of my own, for the decider to compose: (B) in offline renders only, as an explicit user-chosen "offline accuracy" setting (the Diva precedent, criterion 2). I rate it 1/2: bounce and playback would differ by the Monte Carlo difference. That cost falls to Seats 1, 6 and 8.
- **R3 (C), to hold 1/1:**
  1. **Land before the first public release (Phase 13 beta).** W_max then changes once, before any saved project exists.
  2. **Keep the seam now.** Phase 05h invokes the solve through one function from restore, prepare and reset, so the move stays local (criterion 5).
  3. **No waiting in real time.** The real-time path adopts the solved snapshot by atomic swap with a crossfade (CS-2), never by waiting. What plays before the solve lands belongs to Seats 3 and 6, and the AX38 (iii) "settling" state already exists.
  4. **Offline waits.** The offline path waits for the solve before its first block (S5). Where the host's offline signal is unreliable, the render log records it.
  5. **Re-scope the gates.** After the move, the restore gate measures restore without the solve, and the solve time moves to the staleness records (AX38 iii/iv).

**7. Hand-offs**
- **Seat 1:** whether (B) or a post-(C) W_max meets its floor.
- **Seats 3 and 6:** what plays before the solve lands.
- **Seat 7:** the golden round and the announced change if W_max moves after release.
- **Researcher:** how long hosts tolerate a blocked `setStateInformation` (still open); which hosts fail to signal offline rendering.
- **Decider / plan:** which phase hosts (C).

**8. Premortem**

If (B) ships with Challenge 1 "no", a user opens an 8-instance session in a 100 m room. Load blocks for about 40 s, and the host reports a hang or kills the plugin. A beta tester sees it first, because CI records the time but does not block on it.

Files: /home/user/makroof/docs/review/phase-05b2/43-decider-board-answers-C1-Q2.md, /home/user/makroof/docs/phases/phase-05h.md, /home/user/makroof/docs/review/phase-05b2/27-orchestrator-C14.md, /home/user/makroof/docs/review/phase-05b2/44-orchestrator-C17.md, /home/user/makroof/docs/review/phase-05b2/33-orchestrator-C16.md, /home/user/makroof/docs/BUILD_PLAN.md
