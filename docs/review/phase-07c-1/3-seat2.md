# 3 — Seat 2 position (phase 07c-1, D-C1/D-C2/D-C3/D-C9)

Saved verbatim by the orchestrator from the seat's report, 2026-11-12. Brief: file 2.

SEAT 2 POSITION

Corpus is present at revision c1b171f. My claims rest mainly on the code. Where a corpus source is involved I cite it through the AX row that already cites it (AX16 cites Kuttruff §5.2; C1 cites Vorländer Table 6.1).

**1. Reading.** The question is what a saved E_b must be keyed on to equal the current build's solve, and which interim level is admissible. It triggers these cues from my persona: §4 cue 7 (cost growth), §9 "precompute what does not move", and §17 "fitting/claiming outside the validated set".

Code facts that decide Matter A (from `src/sim/Engine.cpp` L218–340 and `diffuse/DiffuseEstimator.cpp` L530–619):
- **(a) What to save.** The level the tail uses, `bandsAmplitude`, depends on fs: it is built from `bandImpulseEnergies(filterbank(fs))` and the unit-decay energy. The estimator output `er.bandsDiffuse` (reference units, which is `bandsDiffuseReference`) has no fs in its transport arithmetic. So the saved quantity must be `bandsDiffuse` per emitter, never the amplitude or E_target. The specular part is recomputed at load from the ISM, which is deterministic and inside the 0.15 s.
- **(b) fs still reaches the solve, through a rounding.** N_need is a ceiling that uses `bandsSpecularTarget` = specular energy × bandEnergy(fs) / bandEnergy(fs). That division can leave a few-ulp difference. So fs-independence holds only to rounding, not bit for bit.
- **(c) Other inputs.** The solve also depends on the emitter gain (`gainSquared`), the window start and t_mix (which carry the AX22 cap and the mixing constants), AX4 air per band, `DiffuseLimits` (W_scene = 2·W_max, n*_max, SE_target 0.083 dB) and the D1–D7 constants (key, 64-history block, final range start 8 000, the 8 000-history window for VOV_union).

**Matter A**
- **A1 (prefer).** Now 1 / later 1. On the same OS, a matching key gives the same inputs and so the same E_b: the step is 0 dB and the solve only confirms it.
- **A2 (can live with, under conditions).** Now 2 / later 2. If the key is incomplete, a level the current build would not produce plays silently until the next edit. That level sits outside the gated AX43 set.
- **A0 (can live with).** Now 0 / later 1. Honest by construction. The cost is that any estimator change before release moves the level of saved projects (a Seat 5/8 cost under NFR-6).
- **A3 (can live with).** Now 1 / later 2. The waveform is deterministic from tailSeed, fs, T60 and length, so saving it adds nothing physical. It is a second artifact that would need its own key: fs, generator version and the T60 bits.

On the validity key, which I hold as a condition for both A1 and A2:
- Key on a canonical hash of the actual `DiffuseProblem` plus `DiffuseLimits`, taken after ISM planning, plus an estimator-version id. Do not key on a scene-level list of constants.
- The hash is complete by construction for everything above: gain, mixing constants, AX22 cap, AX4 air, W_max, n*_max, SE_target. It is also conservative: a change of fs, or a different OS whose ISM-derived inputs differ in ulps, gives a mismatch and a fresh solve of 81–131 ms. That is harmless.
- Tie the version id to the D5 golden. Bump it whenever `update_goldens.py` regenerates D5, and add a test that the golden records the id.

**A2 against AX5 and against 07c-2.**
- No conflict with AX5. On the same OS a key match means identical inputs and so identical bits. Across architectures the saved value differs from the local solve only at ulp level, which is within AX5's −100 dBFS and the CI cross-OS E_target comparison (AX39).
- No conflict with 07c-2's single golden round, because goldens come from render_cli, which carries no state. However, W_max is in the key, so every v2 state fixture will mismatch after 07c-2. Condition: committed v2 fixtures assert only "loads, and a mismatch triggers a solve". The key-match test builds its state in-process, so 07c-2 needs no new fixture set.
- Conditions that lower A2 to 1/1:
  1. The key is defined as above.
  2. Save the U/diagnostic fields with E_b: achieved SE, VOV_union, cap hit, both-near, n*, N, a few dozen doubles. Phase 11's note (AX44) needs them without a solve.
  3. A Release CI check loads a saved state, solves anyway, and requires bit equality (A1's confirmation, moved into CI).

**Matter B**
- **B4 (prefer).** Now 0 / later 1.
- **B2 (prefer).** Now 0 / later 1. In 07c-1 it is the final solve.
  - Under 07c-2, from the code: the pilot range is [0, …) and the final range [8 000, 8 000+N) with N = min(N_need, N_cap). If the (A) pilot stopped at n*_max, the (C) pilot is identical, so N_need is identical. Then the (A) final range is a prefix of the (C) range: the step is 0 dB wherever the cap did not bind, and stage 2 can continue the same blocks (D4 reduces in block order), bit-identical to a one-shot (C) solve.
  - A step appears only where (A) capped or truncated the pilot. There its size scales with the achieved SE at (A), 0.13–1.33 dB in layouts 4/5 (AX41), which the solve's own diagnostics predict. [Inferred from the code; the 07c-2 implementer must verify it.]
- **B1 (can live with).** Now 1 / later 1. My refinement **B1′**: hold the previous *diffuse* part only and recompute the specular part with the new ISM. That keeps the energy matching at the handover consistent with the new early part, and it lasts at most about 131 ms at (A).
- **B3 (general form: cannot live with).** Now 3 / later 3.
  - No validated, scene-data-only predictor of AX16's error exists. Its sign depends on the case (AX16 row, by analogy with Kuttruff Table 5.2). It is above 1 dB in 26 of 345 case-bands, and a predictor that misses one of them breaks condition 5.
  - The only exact predictor is the solve itself.
  - One sufficient condition is admissible: α uniform across all faces in a band, where AX16 is exact (Kuttruff §5.2) and the residual is ≤ 0.43 dB (AX16, measured). B3 restricted to that condition rates 1/1, but B2 dominates it at ≤ 131 ms, so I do not propose it.

**Matter C:** not my ruling; it belongs to Seat 1. One engine fact for it: the size of the step from interim to final can be predicted from the solve's own cap-hit flag and achieved SE, without any scene name (NFR-8). So C2 is implementable.

**Matter D:** NOT MY MATTER. It is the renderer's (Seat 3). The only engine fact: unit decays depend on the T60s, so D5's waveform carries the old decay shape.

**5. Evidence.**
- [Observed, from the code] facts (a)–(c) above, the prefix structure, and the fs-free transport.
- [Observed] AX16 row: 26/345 case-bands, +3.83 / +2.38 dB, uniform α ≤ 0.43 dB.
- [Observed] AX41: SE 0.13–1.33 dB.
- Corpus via the AX rows: Kuttruff §5.2 (exactness for uniform α), Table 5.2 (sign).
- [Inferred] that the 07c-2 prefix holds when the pilot is not work-stopped. **Researcher/implementer:** confirm against `pathCount` and `pilotStops`.

**7. Hand-offs.**
- Step bound: Seat 1.
- State format, fixtures, offline at load: Seat 5.
- A3 per output mode: Seat 4.
- Whether "exactly as saved" across estimator versions favours A2: Seats 5 and 8.

**8. Premortem.** If A2 ships with a key built from a hand-written list of scene constants and some upstream constant changes (for example the AX22 cap or the mixing floor), old projects keep playing a level the current engine would not compute, and no test catches it. The first to notice would be a reviewer comparing render_cli against the plugin's bounce.

Files: /home/user/makroof/src/sim/Engine.cpp (L218–340), /home/user/makroof/src/sim/diffuse/DiffuseEstimator.cpp (L530–619), /home/user/makroof/src/sim/tail/NoiseTail.cpp (L59–71, L177–189), /home/user/makroof/docs/review/phase-07c-1/2-decider-convening.md