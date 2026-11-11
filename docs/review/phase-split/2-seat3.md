# Seat 3 (reverb renderer), position — phase split, 08-c1, 08-c3, 13-c1 (2026-11-10)

Saved by the orchestrator from the seat's report. Corpus not consulted.

**1. Reading.** Where AX37 (5.3) conditions attach (08-c1); whether 2° grouping moves to 08-4 (08-c3); order of 13 and
S9 placement (13-c1). Cues: cost (BRIR build time, convolver partitioning); early-reflection region (AX20 bound).

**2. Ranking.** 08-c1: (b) amended (6a) prefer · (a), (b) as written, (c) (reluctantly) can live with. 08-c3: (b)
prefer · (a) can live with. 13-c1: **(b) S9 in 13-1 prefer** · (a), (c) can live with.

**3./4. Tension now / later**

| option | now | later | debt |
|---|---|---|---|
| 08-c1 (a) | 0 | 1 | redundant but safe |
| 08-c1 (b) as written | 1 | 2 | false fact "08-2 reads no t_mix,e": `Engine.cpp` 120–148 bounds the list at `mixS + kCrossfadeHalfS` (AX20); `mixS` moves when the AX22 fallback fires; a later session may compute its own bound in `BrirBuilder` → rework of 08-2 |
| 08-c1 (c) | 1 | 2 | new dependency reading, same blind spot |
| 08-c3 (a) | 1 | 2 | 08-2 owns a rule whose deciding measurement lands two sub-phases later; grouping ahead of measurement is the typical-performer error (§17) |
| 08-c3 (b) | 1 | 1 | AC3 untouched (direct path), AC5/AC8 tail-dominated, AC6 the only real exposure |
| 13-c1 (a) | 1 | 2 | an S9 miss found after 13-1 closed; its remedy (non-uniform partitioning) changes summation order; 13-2's AX5 residual re-runs; 13-1b becomes a reopened phase after 13-2 |
| 13-c1 (b) | 1 | 1 | S1 already profiles on macOS arm64, so hardware is needed in 13-1 anyway; measurement and remedy share one session; 13-1 grows |
| 13-c1 (c) | 1 | 2 | determinism and timing proven on code about to change |

**5. Evidence.** `src/sim/Engine.cpp` 120–148, BUILD_PLAN AX20 and line 322 ("the AX20 image list grows with t_mix,e");
whether 05h can move the fallback [Inferred] (Seat 2 to confirm whether 05h changes `energyEntries` and k_real);
phase-13 S1, S9 (run 42397114233; P = 256 costs 1.5–2.1×); phase-08 S5a.

**6. Conditions of acceptance.**
- 6a, 08-c1 (b): attach (i) to 08-2 as well (t_mix,e and the AX20 list only through the existing
  `planEmitter`/TailMatch path, never its own bound); replace "08-2 reads no t_mix,e" with "08-2's anechoic checks
  (AC3, AC7, AC10) read none"; 08-2's room early-part renders fall under (iii). → 0/1.
- 08-c3 (a): 08-2 states "no grouping" as shipped state; 08-4 owns any change → 1/1 (≈ (b)).
- 08-c3 (b), optional: 08-3's exit records BRIR build time on the AX20 worst-case scene (R3's "measure first", moved,
  not new); if grouping lands, 08-4's re-run includes a moving-source render (a 2° cell crossing is a state step;
  covered only if the AQ4 crossfade absorbs it).
- 13-c1 (a): any 13-1b ordered before 13-2's cross-architecture job, or 13-2's C3 clause re-run after 13-1b → later 1.
- 13-c1 (c): re-run C3's cross-architecture clause after 13-1 → later 1.

**Lead question:** non-uniform partitioning does not belong under a Seat 2 lead. Partitioned convolution, callback CPU
per instance and the S10 end treatment at the cap are my row; Seat 2's row covers S13 (W_max, n*_max), rebuild time,
AX22 i₀. 13-1 holds two subjects. Minimum fix: 13-1b (convolver work and S9 remedy) read as Seat 3 lead; for one
subject, C2 splits into "AQ10 met" (Seat 3) and the AX22 i₀ re-derivation (Seat 2).

**7. Hand-offs.** Seat 2: does 05h change k_real / AX22 fallback? Seat 1: L1, L3–L5 validity under (b). Seat 5: S9
pass condition, hardware in 13-1. Seat 4: (i) on 08-2.

**8. Premortem.** (b) as written → 08-2 builds its own bound → binaural and omni early parts diverge at t_mix,e when
05h moves the fallback → AC6 fails in capped rooms during 05h's golden re-render.
