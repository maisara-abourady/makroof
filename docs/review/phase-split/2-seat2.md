# Seat 2 (engine architect), position — phase split, 08-c1 and 13-c1 (2026-11-10)

Saved by the orchestrator from the seat's report. Corpus not needed (product record and code only).

**1. Reading.** 08-c1: where each AX37 (5.3) condition binds; do 08-1/08-2 read nothing from 05h? 13-c1: order, S9
placement, is 13-1 one subject? Cues: §4 cue 7 (what each piece reads and costs); failure-library row "single
statistic / seam at the handover".

**Fact check, "08-1/08-2 read no E_b or t_mix,e": refuted for 08-2 as worded; substance holds.**
- 08-1: confirmed (converter, embedded `.bin`, `HrtfSet::query`, DF-EQ and coherence targets touch no tail-match
  output).
- 08-2 reads t_mix,e: `src/sim/Engine.cpp` `planEmitter` line 124 `iso.maxArrivalTimeS = plan.mixing.mixS +
  tail::kCrossfadeHalfS`; the AX22 fallback (lines 134–148) is chosen from `TailMatch` (`needsIsmFallback`); the
  handover crossfade sits at t_mix,e. So it depends on t_mix,e, k_real and the fallback, not on E_b.
- 05h leaves all three unchanged: AX37 (5.2) "computed exactly as today"; phase-05h line 41 "Mixing-time rule:
  unchanged", "AX22/N_cap: unchanged"; lines 47, 172.
- One 05h change reaches 08-2's arithmetic: the RAII FTZ/DAZ guard on `buildRoomIR` (AX37 (5.1)(i)), denormal-level
  bits only (~700 dB below signal); no 08-2 tolerance check (AC3, AC7, AC10) sees it; 08-2 freezes no goldens.
- Net: 08-2's output does not change when 05h lands; the map's sentence is false about t_mix,e.

**2. Ranking.** 08-c1: (b′) — (b) with corrected wording and condition (i) also on 08-2 — prefer; (a) can live with;
(b) as worded can live with only under §6; (c) can live with. 13-c1: (a) prefer; (b) can live with; (c) can live
with (costs a re-run).

**3. Tension now.** (b′) 0 · (a) 0 · (b) 2 (writes a false statement about what the engine reads) · (c) 1. 13-c1:
(a) 0 · (b) 1 (Seat 5 measurement under my lead; L heavier) · (c) 1.

**4. Tension later.** (b) as worded 2 (an implementer may give the binaural early part its own bound or handover,
breaking the omni/binaural seam; AC6/AC8 catch it; rework of BrirBuilder's early path). (c) 2 (new dependency reading;
drops (i) where it guards 08-2). (a) 1 (noise). (b′) 0. 13-c1 (c) 2 (13-1's output changes — S13 W_max/n*_max, a
possible N_cap raise under C2, the S10 end fade — come after the AX5 residual, which must re-run). (a) 0. (b) 1.

**5. Evidence.** AX37 (5.1)(i), (5.2), (5.3) (BUILD_PLAN line 137); phase-05h lines 41, 47, 172, 282; AX20 (BUILD_PLAN
line 120); `src/sim/Engine.cpp` 115–150, 200–211; phase-05b2 lines 397–399 (reason for the 05h dependency: AX16 tail
level and `bandsAxisShares`, read by neither 08-1 nor 08-2) [Observed]; phase-13 S13, C2.

**6. Conditions of acceptance.** (b) → 0 by replacing the sentence with: "08-1 reads no tail data; 08-2 reads t_mix,e
(the AX20 list bound and the handover) and the AX22 fallback, through the shared `planEmitter`/`TailMatch` path, and
no E_b. 05h leaves these unchanged (AX37 (5.2); phase-05h scope 'Mixing-time rule: unchanged')." Attach (i) to 08-2
and 08-3, (ii) and (iv) to 08-3, (iii) to 08-4. (c) → 1 only if recast as (b′). 13-c1 (c) → 1 if 13-2's
cross-architecture job is a re-run gate after 13-1's last output change (essentially (a)).

**7. Hand-offs.** Seat 4: confirm (i) on 08-2. Seat 3: do 08-2's anechoic renders and AC3 use an all-α=1 scene?
(`open_field` gains a floor-diffuse tail under AX37 (5.4) once 08-3 and 05h land.) **Is 13-1 one subject under my
row? Strained.** Mine: S13, the rebuild-time part of S1, C2's AX22 i₀ and N_cap clauses, S10's representation length.
Seat 3/5: partition size, SIMD, memory budget. Seat 1: S10's Q1/Q2. Not splittable further under G2 (S13 and S10 own
no criterion but C2); acceptable with the hand-offs named in 13-1's file. Seat 5 / a human: does "release machines" in
S13 mean real hardware? If so, 13-1 and 13-2 both need an Apple-silicon Mac. Seat 1: S10 audibility.

**8. Premortem.** Under (b) as worded, 08-2 gets its own handover; 08-3's AC6 or AC8 fails at the seam.

| option | now | later |
|---|---|---|
| 08-c1 (a) | 0 | 1 |
| 08-c1 (b) as worded | 2 | 2 |
| 08-c1 (b′) | 0 | 0 |
| 08-c1 (c) | 1 | 2 |
| 13-c1 (a) | 0 | 0 |
| 13-c1 (b) | 1 | 1 |
| 13-c1 (c) | 1 | 2 |
