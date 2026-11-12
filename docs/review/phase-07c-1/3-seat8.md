# 3 — Seat 8 position (phase 07c-1, D-C1/D-C2/D-C3/D-C9)

Saved verbatim by the orchestrator from the seat's report, 2026-11-12. Brief: file 2.

SEAT 8 POSITION (phase 07c-1, Matters A to D; corpus present, revision as in file 2)

**Whose ears.** The producer reopens a project they have already judged. They are listening through the ears of the listener they placed in that room, and they expect that room back exactly (NFR-6, FR-LIC-1). Two moments decide it: pressing play straight after load, and printing the track straight after load or after an edit (A4).

**1. Reading.** What plays, and what gets bounced, between a restore or edit and the final IR. My §4 cues are 10 (where was it judged) and 1 (whose ears), and my criterion 5 (translation): a capture made right after load must equal what the producer approved.

**Matter A (my question): should the solved result travel in saved state?**
- Ranking: **A2 prefer**, A1 can live with, A3 can live with, A0 can live with in 07c-1 only.
- **A2.** Now 0, later 1. What reopens and bounces is the level that was saved, on any machine. That is the most literal reading of NFR-6 "exactly", and it removes cross-machine drift in E_b. The debt is that the key's estimator-version id means an estimator fix changes old projects' level on reopen. That is Seat 7's condition 1, not mine.
- **A1.** Now 1, later 1. In 07c-1 it plays the same as A2, because the saved E_b equals the same-build solve. It costs a solve per load and allows a step if anything in the key leaks.
- **A3.** Now 1, later 2. It is the only option that closes the tail gap at load (Matter D). The cost is ≈ 18 MB per instance and about 144 MB for 8 instances (my arithmetic: 12 s × 96 000 × 2 × 2 × 4 B ≈ 18.4 MB). That cost is Seat 5's and Seat 7's (R5). It is also void when the project reopens at a different fs, because the unit decays depend on fs (file 1). Undoing it costs a state version.
- **A0.** Now 1, later 2. In 07c-1 B2 is the final solve (81 to 131 ms), so the level is harmless. At 07c-2's W_max raise, a v1-style load would play an (A) estimate and then step by up to 1.33 dB SE (AX41, K7) after the producer has started listening. Evidence arrives at 07c-2's packet.
- **Important (Inf):** A1 and A2 save the level, not the waveform. Neither closes the 3.14 s synthesis window. Matter D carries the load risk.

**Matter B: interim level when no saved E_b matches.**
- Ranking: **B4 prefer**, B1 and B2 can live with, B3 cannot live with unless a predictor exists.
- **B4.** Now 0, later 1. On edits the step is the user's own change arriving late, which a producer A/B-ing rooms accepts while "settling" shows. At load it plays the true level in 07c-1.
- **B1 alone.** Now 0, later 2. Under 07c-2, a drastic edit (booth to hall) holds a level that is many dB wrong until the slower solve lands. The A/B then judges a hybrid room.
- **B2 alone.** Now 1, later 1. It gives a near level fast under 07c-2 and costs a two-stage solve.
- **B3.** Now 3, later 3. AX16 is +3.83 dB off in layout 4, which is about 4 jnd of G (Vorländer, *Auralization*, Table 6.1: G 1 dB, 500 to 1000 Hz). That changes how far away the listener is, which is my criterion 1. The condition 5 bound already excludes B3 without a predictor (NFR-8).

**Matter C: the step size.** NOT MY MATTER for the number; it is Seat 1's ruling. One point from my seat: whatever bound is chosen must also cover a realtime capture (see Matter D), because a step inside a bounce is printed.

**Matter D: what plays while the synthesis is pending.**
- Ranking: **D3 prefer**, D4 can live with (load only), D2 can live with (edits), D5 can live with, D1 cannot live with at load.
- **D3.** Now 1, later 1. Space, level and T60 are present from the first second; only the waveform swaps under equal-power (AX18). Plausibility, not authenticity, is the bar (my criterion 3; Seat 1 agrees). Feasibility and cost are Seat 3's [Hyp].
- **D4.** Now 1, later 2. Exact at load, but its costs are those of A3.
- **D2 on edits.** Now 1, later 1. The A/B is clean (whole room A, then whole room B) but delayed up to about 3.3 s at 96 kHz. Its conflict with condition 4's "ISM never held" is Seat 3's call.
- **D5.** Now 2, later 1. For 1 to 3 s it plays a room that never existed (new early part, old T60), and a producer A/B-ing judges room B on that first impression.
- **D1 at load.** Now 2, later 2. For ≈ 3.3 s at 96 kHz (about 1.3 s at 48 kHz [Inf from the ×2.5 scaling]) the anchor stays but the space is gone. The early-only IR moves C80 by far more than its 1 dB jnd [Inf from the definition]. I read this against condition 9's "never silence where a tail existed in the saved state" and ask the interrogator to rule. Undoing it costs one phase of rework at Phase 13 if producers report it.
- **Evidence for D1's later rating.** Most producers press play after the host's own load time, which may hide the window [Hyp]. The evidence would be Maisara's producer test or the K16 re-take.

**Gap no option covers (Inf).** Captures that are realtime by design never signal offline, so condition 6 cannot protect them: a realtime bounce, or Live-style resampling to a track straight after load or after an edit [Hyp: how common this is in the target users' hosts; researcher, extend R2]. They print whatever interim plays. My incidents for this are WM4 and GM1 (the failure is found in the deliverable). Only D3, D4 or A3 make that print plausible.

**Conditions of acceptance.**
- **A0:** acceptable if it is paired with A1 or A2 before 07c-2's W_max raise (then 1).
- **A3:** acceptable if only the unit decays are stored, keyed by fs and seed, and R5 shows no undo or autosave bloat (then 1).
- **B1:** acceptable if B2 replaces it on edits whenever the 07c-2 solve exceeds about 0.5 s [Hyp threshold; Seat 1 and Seat 6 own it] (then 1).
- **D5:** acceptable if it is restricted to edits whose T60 change is under one EDT jnd of 5 % (Table 6.1), with D2 otherwise (then 1).
- **D1 at load:** acceptable only with A3/D4, or D3 behind it (then 1).

**Hand-offs.**
- Seat 1: the D-C1 number, and whether D3's waveform swap is audible.
- Seat 3: D3's cost, and D2 against condition 4.
- Seat 5 and Seat 7: the 18 MB cost and R5.
- Seat 6: whether "settling" must also warn when a realtime capture starts while settling.
- Researcher: realtime-capture prevalence (extend R2).
- Interrogator: D1 against condition 9.

**Premortem.** If A0 and D1 win, a producer resamples or bounces in realtime right after opening the project. The track ships with a first phrase that has no room, and the first to notice is the listener on earbuds, then the producer, then the refund request.

The derived workflow requirement most affected: the translation view (§8): the bounce must equal what was judged.