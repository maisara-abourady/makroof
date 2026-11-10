# Seat 4 — ratings R1–R3 (Challenge 1, Q2a (B), Q2a (C))

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 4 POSITION: R1 (Challenge 1), R2 (Q2a (B)), R3 (Q2a (C) as a commitment now)

The corpus is present. Following the brief, the AQ10 and AX36 limits are lifted for these three questions on Maisara's authority. My own measures still apply:
- per-mode rebuild and update interval, against Vorländer Table 15.1's 700 ms translational row and 3 s scattering row (as quoted in AQ10);
- level parity across modes and ears (±1 dB);
- tail level, i.e. DRR, as a room cue.

**1. Reading.** Three questions:
- R1: whether the 100 m restore time becomes a blocking gate that sizes W_max.
- R2: whether W_max grows about 11×.
- R3: whether moving the diffuse solve off the synchronous restore is scheduled now.

My cues:
- **Per-mode rebuild headroom.** A position move re-solves E_b, because E_b depends on positions.
- **Parity.** W_max must stay independent of the output mode.
- **Room cues.** The capped SE is a random DRR error.

**2–4. Ranking and tension (now/later)**

**R1, Challenge 1**
- **"no" (recorded and escalated, AX38 4c): prefer, 0/1.**
  - Nothing in my chain depends on restore time.
  - Phase 08's binaural build cost simply adds to a recorded time.
- **"yes" (blocking gate, W_max (A) with D-H1's margin): can live with, 0/2.**
  - Now 0: W1 is unaffected, because n\*_max (1 024) binds before W_max there (C16 (f): W1 rows uncapped).
  - **Later 2.** The gate is sized against today's omni build of 1.884 s (phase-05h §3, D-H1). Phase 08 adds the binaural early-part (HRIR) build to every restore, at 100 m and 96 kHz, over the AX20 image list, and that cost is unmeasured [Hyp].
  - Either the gate fails in binaural mode, or W_max shrinks for every mode, which means a golden round and a higher capped SE everywhere.
  - W_max cannot be made per-mode. E_b would then differ between modes by about √2·SE, a random level jump on a mode switch, which breaks my parity condition [Inferred].

**R2, Q2a (B) (W_max about 11×, only with Challenge 1 "no"): can live with, 2/1.**
- **What it buys my chain.** In layouts 4/5 at s = 1, the one-end tail SE falls from 0.29–1.33 dB under (A) (C16 (f)) to 0.06–0.22 dB (C17). That is a DRR error falling from about the size of my ±1 dB parity budget to about a fifth of it. The 100 m SE falls to 0.05–0.12 dB (C14 (a)). Both-near cases still fail (C17 reading 3).
- **Now 2: position updates in capped rooms.**
  - The diffuse share of a solve is the restore minus the 1.884 s build: about 0.26 s under (A), and up to about 2.9 s under (B) in the low-α s = 1 cube (C14 (c), 1 thread) [Inferred].
  - Every source or listener move in that room class then waits about 2.9 s at 1 thread (about 0.6 s at 4 threads [Inferred]) in every output mode.
  - That exceeds Table 15.1's 700 ms translational row, unless the split update holds E_b while the specular and HRTF part updates.
- **Later 1:** a parameter change; it is recorded, and nothing in Phase 08 is frozen on it.

**R3, Q2a (C) as a commitment now**
- **Schedule it now: prefer, 0/1.**
  - It is the structural form of my standing condition: hold E_b, and update the specular and HRTF part on the fast path (D-T4a (v); my R2 condition below).
  - It frees W_max from restore, so (B)-level room-cue accuracy becomes possible without any restore cost.
  - **Later 1:** about one phase of rework in the pipeline my chain feeds on. Phase 08 binaural goldens in capped rooms would change once W_max rises.
- **Do not schedule: can live with, 1/1.**
  - In capped rooms the DRR error stays at about 0.3–1.3 dB SE. It is flagged by U, and shared across modes, so parity holds.

**5. Evidence**
- C14 (c): restore under (A) and (B).
- C16 (f): layouts 4/5 under (A).
- C17: layouts 4/5 under (B).
- phase-05h §3: D-H1.
- 43 §2–3.
- AQ10: Table 15.1 rows, and offline bounce is synchronous (AQ4).
- [Hyp] The Phase 08 HRIR build cost at 100 m.
- [Inferred] Diffuse share = restore − 1.884 s; the 4-thread scaling.

**6. Conditions of acceptance**
- **R1 "yes", to 0/1:**
  - From Phase 08 on, the gate measures the heaviest output mode.
  - A single W_max re-derivation, with its golden round, is planned in Phase 08.
  - W_max stays one constant for all modes.
- **R2 (B), to 1/1:**
  - E_b refreshes on its own interval (the split update or (C)), so the specular and HRTF part keeps its rate.
  - A bus-layout change (for example stereo to 7.1.4), which calls prepare, reuses the cached E_b when the scene is unchanged.
- **R3 (C), to 0/0:**
  - Offline bounce and `render_cli` wait for the final E_b (AX5 determinism).
  - After a load, the tail plays the saved or last E_b. It is never silent, and never the AX16 level (layout 4 differs by +3.87 dB). Its update crossfades (AQ4).
  - E_b is shared across modes and ears.
  - Phase 08 goldens in capped rooms carry a tolerance derived from the achieved SE, or the phase is scheduled before those goldens are frozen.

**7. Hand-offs**
- **Seat 5:** whether a restore-time gate is practical, and the D-H1 margin.
- **Seat 1:** whether 0.3–1.3 dB of DRR SE is audible.
- **Seat 3:** a held E_b while the listener moves.
- **Seat 6:** whether the user sees the delay.

**8. Premortem.** If "yes" ships and Phase 08 adds the binaural build, one of two things happens. The gate fails in binaural mode, and Seat 5 sees it first in CI. Or W_max is cut per mode, and the tail level jumps on a mode switch, and Maisara hears it first in the Phase 08 parity checklist.
