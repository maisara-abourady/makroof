# 3 — Seat 4 position (phase 07c-1, D-C1/D-C2/D-C3/D-C9)

Saved verbatim by the orchestrator from the seat's report, 2026-11-12. Brief: file 2.

SEAT 4 POSITION (phase 07c-1, Matters A, B, D; Matter C: NOT MY MATTER. The size of the step is Seat 1's ruling and the crossfade is Seat 3's. My only condition on C is under Matter B below.)

**1. Reading.** The question is what plays, and what is saved, between a restore or edit and the final IR, as it affects delivery. Cues it triggers: level and tone parity (§4), the mode switch as a parity event, a missing room cue (a dry interim), and measurement doubt (the provenance of stored data).

One fact from the code reshapes A1 and A2. `render.outputMode`, `render.hrtfId` and `render.tailSeed` are part of the scene (src/contract/Json.cpp L380–388). E_b depends on none of them. AX44 says one set serves "both emitters, both ears and every mode", and AX40 makes E_b independent of `tailSeed`. A validity key that is "an exact match of the effective scene" would therefore throw away a correct E_b after a mode switch, an HRTF change or a reseed.

**2. Ranking.**
- **Matter A:** A2 *prefer* (with key condition K) > A1 *prefer* (with K) > A0 *can live with* > A3 *cannot live with* in its "assembled IR" form. A3 with unit decays only is *can live with*.
- **Matter B:** B1, B2 and B4 *can live with*; B4 is my *prefer*. B3 *cannot live with* where AX16 is more than 1 dB off; condition 5 already excludes it there.
- **Matter D:** D5 *prefer* (edits) > D2 *can live with*, on condition M > D3 *can live with*, on condition R > D1 *can live with* only for scenes with no saved tail. D4: as A3.

**3–4. Tension now / later (0–3).**

Matter A:
- **A0: now 1, later 2.** A project reopened at 07c-2 shows an interim step of up to 1.33 dB (AX41, K7). That step lands in the first seconds of a Phase 08/09 parity check and gets confused with a mode difference. Undoing it is a state-version bump.
- **A1/A2 with key K: now 0, later 1.**
- **A1/A2 without K: now 1, later 2.** At Phase 09, every reopen in the other mode, and every mode switch if the switch rewrites `render.outputMode`, throws E_b away. That forces a re-solve, so the AX18 equal-power mode crossfade picks up a level step of up to 1.33 dB under 07c-2. The switch then changes level, not just space (§2 rank 7). Undoing it means a key-format change, which is a state v3 and new fixtures.
- **A3 (assembled IR): now 1, later 3.** From Phase 08 the assembled IR depends on the mode, the HRTF set and the headphone compensation. A stored IR is a second, frozen copy of the chain. A project saved before an HRTF or compensation change would play the old chain, and loudness parity would hold or fail per project with no way to trace it (§7.4, Club Fritz doubt; §2 "never trade": compensation matched to the HRTF head). It does not break AX44 if E_b is stored beside it. It does break the output-mode switch: a stored binaural IR is no use in stereoSpeakers, so the switch still needs a full build. Evidence arrives at Phase 08.

Matter B: every B option is one E_b used for both ears and both modes, so parity between modes holds by construction.
- **B1, B2, B4: now 0, later 1 each.**
- **B3: now 2, later 2,** even where it is admissible. A second estimator in the chain is a second level source. Its error by class (+3.83 / +2.38 dB, K6) could not be checked against Phase 09's loudness parity.

Matter D:
- **D1: now 2, later 2.** For about 3.3 s the render is early part only. A dry binaural render externalises worse, and reverberation "almost consistently enhances externalization" (Begault, *3-D Sound*, ch. 3, corpus L1108; L1166). The interim is then both drier and quieter than the final. I name condition 9 ("never silence where a tail existed in the saved state") as the bound the interrogator should read: a missing tail is silence in the late field.
- **D2: now 1, later 2.** Holding the old IrSet on a mode switch keeps the wrong mode playing for seconds [Hyp: depends on whether the Phase 08/09 tail decorrelation needs new unit decays].
- **D3: now 1, later 2.** A provisional tail whose interaural coherence differs from the final mode's target (binaural diffuse coherence, or ORTF for stereoSpeakers, Phase 09 scope) makes the image width jump at the swap.
- **D5: now 1, later 1.** The T60 is wrong for a few seconds, but the coherence and the mode are right.

**5. Evidence.**
- From the code and plan: AX44 (shared set), AX40, AX18 (mode switch is equal-power), the Phase 09 scope ("loudness matched to binaural mode"), K7 and K6.
- From the corpus: Begault *3-D Sound* ch. 3 (L1108, L1166) on reverberation and externalisation.
- Not sourced: the dependence of unit decays on mode after Phase 08/09 is `[Hyp]`. Researcher or Seat 3: confirm that the decorrelation is applied downstream of the per-emitter unit decays.

**6. Conditions of acceptance.**
- **K (A1/A2 → 0/1).** The key is the projection of the scene that E_b depends on: geometry, materials, positions, W_max, n*_max, estimator version, plus fs only if Seat 2 confirms it. It excludes `outputMode`, `hrtfId` and `tailSeed`. A test asserts that a v2 state restored with the other `outputMode` uses the saved E_b, bit-identical (extends the AX44 Phase 08 check). An output-mode or HRTF change never triggers a diffuse re-solve or an interim level.
- **A3 → 1.** Store mode-independent unit decays only, never the assembled IR. If an assembled IR is ever stored, its key must include mode, `hrtfId`, a hash of the HRTF resource and compensation, and the build id.
- **D1 → 1.** Use it only where no tail existed in the saved state and no previous IrSet exists.
- **M (D2 → 1).** A mode switch reuses the cached unit decays and never waits for a synthesis.
- **R (D3 → 1).** The provisional tail is decorrelated to the same target coherence for each mode as the final tail.
- **B3:** out unless Seat 2 shows a generic predictor of its error.
- **Matter C** (step bound itself is Seat 1's): whatever bound Seat 1 sets applies to the level step. The mode switch must add no level step on top of the AX18 equal-power crossfade.

**7. Hand-offs.**
- State format and fixtures: Seat 5.
- Whether fs belongs in the key: Seat 2.
- Whether the dry interim is audible: Seat 1.
- The provisional generator: Seat 3.
- Whether Phase 08 stores per-mode decorrelation upstream of the unit decays: Seat 3 / Phase 08.

**8. Premortem.** The key is drafted as "effective scene" and includes `outputMode`. At Phase 09 the loudness-parity test then catches a 0.5–1.3 dB step at every mode switch on reopened projects (07c-2 interim error, K7), and a producer A/B-ing headphones against monitors hears the switch change level as well as space.