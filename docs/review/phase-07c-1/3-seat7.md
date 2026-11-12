# 3 — Seat 7 position (phase 07c-1, D-C1/D-C2/D-C3/D-C9)

Saved verbatim by the orchestrator from the seat's report, 2026-11-12. Brief: file 2.

SEAT 7 POSITION (phase 07c-1, Matters A–D; my main matters are A and D, the rest is cost only)

No acoustic claims are made from this seat. The corpus was not needed. All schedule and support figures below are [Hyp] (I have no incident that measures them) unless they carry a product id.

**1. Reading.** The question is what the saved project carries and what plays between reopening and the final IR. Cues it triggers from my persona:
- **"A deal is being changed for existing customers."** This covers my condition 1 (decider file 47 §4; phase-07c-1 Raise item 1), V4 and P11.
- **Support load is the founder's hour.** Tickets saying "the reverb is missing for 3 s after I open my project" or "my projects are 150 MB" (R1, R3).
- **Visible durability (AI1).** A plugin that reopens differently reads as a one-shot.
- **Timing.** No release has happened yet (decider file 2, last line). So a `pluginStateVersion` bump costs no customer anything today. After release, every bump becomes a trust event.

**2–4. Ranking, tension now / later**

**Matter A (prefer A2, with my key split below)**
- **A2: prefer. Now 1 / later 1.**
  - Cost: state v2, fixtures and the invalidation rules, a few days [Hyp].
  - Commercial gains: a bounce right after load needs no solve, which protects us whatever R2 finds; projects sound the same on a collaborator's machine.
  - Commits: 07c-2 and Phase 13 to honouring saved E_b.
  - Undo: a state parameter before release, a migration after.
  - Evidence: 07c-2's W_max raise is the first time old projects meet a new estimator.
- **A1: can live with. Now 1 / later 2.**
  - Once 07c-2 or any post-release estimator change lands, a reopened project plays the saved E_b and then moves to the new final by itself (07c-2's change to W_max moves the level by 0.13–1.33 dB in layouts 4/5, AX41, K7).
  - That is a deal changed retroactively by a software update (V4): "the update changed my mix". The key detects the mismatch; it does not prevent it.
- **A0: can live with only before release. Now 0 / later 2, rising to 3 if A0 ships in a release.**
  - A0 is exactly the case where my condition 1 fails and the item returns to Maisara.
  - Undo cost: free now; after release, a migration plus a customer-visible sound change.
- **A3: can live with only under conditions. Now 2 / later 2.**
  - About 18 MB per instance means about 144 MB for 8 instances, multiplied again by autosave and undo snapshots [Hyp, R5].
  - The tickets would be slow saves, cloud-sync and collaboration bloat, and forum threads like "this plugin bloats projects". Each is a trust withdrawal, and it is permanent once released, because old projects carry it.

**Does the key discharge condition 1?** Only partly. The A1/A2 key, as written, invalidates on an estimator-version or W_max mismatch, which triggers a re-solve, which changes the sound. Condition 1's purpose is that an updated plugin does not silently change a saved mix (NFR-6 "exactly"). My condition: split the key in two.
- **Scene part** (effective scene, positions, materials; fs if Seat 2 says E_b depends on it): a mismatch invalidates.
- **Engine part** (W_max, n\*_max, estimator-version id): on a mismatch, the saved E_b stays authoritative. The diagnostics mark it "solved by engine vN", and the user's next edit re-solves with the current engine.
With that split, A2 discharges condition 1 and A1 drops to 1/1.

**Matter D (prefer D3 at load with A2's level, D2 or D5 on edits)**
- **D2 (edits, reset, prepare): prefer. Now 0 / later 0.** Cheap and invisible.
- **D5 (edits that change T60): can live with. Now 0 / later 1.** It reuses the cached unit decays. Whether a wrong-T60 waveform is audible belongs to Seats 1 and 3.
- **D3 (load): prefer. Now 1 / later 1.** A second generator adds test surface and schedule (Seat 3 costs it). It meets condition 9 without A3's file size, and offline never uses it.
- **D1 (load): can live with only for scenes with no saved tail. Now 2 / later 2.**
  - At 100 m / 96 kHz the user hears about 3.3 s of early part only after reopening. That is the most likely first support ticket and forum "bug" post.
  - The bound that rules it out at load is condition 9 ("never silence where a tail existed in the saved state"). That reading is the interrogator's.
- **D4: can live with only under A3's conditions. Now 2 / later 2.**

**Matters B and C (cost only; audibility belongs to Seats 1 and 9)**
- **B4: prefer, 0/1. B1: 0/1.**
- **B2: 0 now, 1 later** (a two-stage solve to maintain from 07c-2 on).
- **B3: 2/2.** It needs research into a generic error predictor and may not exist under NFR-8. That is a phase of uncertainty for an option that may be out at step 1.
- **C1: prefer, 0/0.** The step counter feeds the public testing record (AI2) and support triage.
- **C4: 0/1.** No number to point to when a user reports "the room changed by itself".
- **C2: 1/1.** An extra refusal path to test.
- **C3: 1/1.** It depends on R4.

**5. Evidence**
- No release yet: decider file 2, final line.
- Condition 1: decider file 47 L157 and L185; phase-07c-1 Raise item 1.
- 07c-2 step size of 0.13–1.33 dB: AX41 (K7).
- 18 MB: orchestrator file 1.
- Retroactive change backlash: incident V4. Bridge for an installed base: incident P11. Support temperament as product: incident R3. Scan for one-shots: AI1, AI2.
- Ticket and project-size behaviour: [Hyp].

**6. Conditions of acceptance**
- **A1, A2:** the split key above (condition 1).
- **A0:** a written AX stating that state v2 with E_b lands before the first public release, and Phase 13 checks it.
- **A3, D4:** R5 shows no host caps or slowdowns at about 18 MB, and the tail is stored once, not per undo step. Then 1/2. If R5 shows caps or slowdowns, both are out on Seat 5's ground.
- **D1:** used only where no tail existed in the saved state, with "settling" shown. Then 1/1.
- **B3:** the predictor exists and is validated (Seats 2 and 9). Then 1/1.

**R3: what would change my ratings.** If Logic, Live, Cubase or Bitwig shows a not-responding dialog, or sandbox-kills a plugin, for a main thread blocked about 1–2 s during load, then the synchronous work for 8 instances (0.15 s × 8 ≈ 1.2 s) becomes a support risk:
- D3 must move to the background: D3 1/1 becomes 1/2.
- A3's deserialisation becomes unacceptable: 2/2 becomes 3/3.
If hosts tolerate several seconds at load, my ratings stand.

**Public wording**
- Allowed (A2 plus D3): "A reopened project restores its saved room level. The room's tail settles within seconds while it is rebuilt."
- Under D1, never "opens instantly" or "exactly as saved".
- Never "bounces always use the final room" unless R2 clears the common hosts. Otherwise: "offline export waits for the final room in hosts that signal offline rendering".
- Never claim cross-machine bit-identity (AX5 is same-OS only).

**7. Hand-offs**
- Seat 2: whether E_b depends on fs, n\*_max and the estimator constants (the scene part of the key).
- Seat 5: state cost and R1/R2.
- Seat 1: C-level audibility.
- Seat 3: D3 generator cost.
- Human (Phase 13): the release date against the versioning.

**8. Premortem.** If A0 or A1 with a whole-key invalidation ships in the first release, then 07c-2's W_max raise makes users' saved mixes move by up to about 1.3 dB on reopening. The first to notice is a user comparing an old bounce in a forum thread titled "update changed my reverb", and that thread is the trust withdrawal V4 describes.