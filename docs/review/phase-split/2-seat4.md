# Seat 4 (chain keeper), position — phase split, 08-c1 and 08-c3 (2026-11-10)

Saved by the orchestrator from the seat's report.

**1. Reading.** Where AX37 (5.3) conditions (i)–(iv) attach once 08 is cut into 08-1..08-4 (08-c1); whether "2°
grouping only if the benchmark needs it" moves to 08-4 (08-c3). Cues: level and tone parity, under-resolved direct
path (grouping), measurement doubt (which build each check runs on).

**Open gap: do 08-1 and 08-2 read anything from 05h?**
- **08-1: confirmed, reads nothing** (licence, converter, `HrtfSet`, DF-EQ, coherence target: HRTF data, no room
  quantity).
- **08-2: the map's wording is refuted, its conclusion holds.** From the code (`src/sim/Engine.cpp:120-149`,
  `planEmitter`) the early part reads t_mix,e: it bounds the AX20 image list (`maxArrivalTimeS = mixS +
  kCrossfadeHalfS`) and sets the ISM crossfade weight (`crossfade(t, mixS)`, line 246). Through the AX22 fallback it
  reads k_real from `TailMatch` (`needsIsmFallback(plan.match)`). It reads no E_b and no `bandsAxisShares`; image
  directions come from Phase 03 (phase-08 S4, S5a). AX37 (5.2): k_real, `needsIsmFallback` and t_mix,e "are computed
  exactly as today"; phase-05h line 28 keeps the early part specular-only (AX21). So nothing 08-2 reads is changed by
  05h. 05h's RAII FTZ/DAZ guard (AX37 (5.1)(i)) can change denormal-range bits, but 08-2 freezes no golden (08-c2:
  goldens in 08-4). 08-2 may run before 05h, but condition (i) binds the handover 08-2 reads.

**2. Ranking.** 08-c1: **(b) amended** — prefer. Amendment: (i) attached to 08-2 as well as 08-3, worded "t_mix,e
(handover and image-list bound) read only from the same `planEmitter`/`TailMatch` result as the omni build"; 08-1
alone recorded as reading no room quantity; 08-2 recorded as reading no E_b and only the t_mix,e that 05h leaves
unchanged. (a) can live with; (b) as written can live with; (c) can live with, last. 08-c3: (b) prefer; (a) can live
with.

**3. Tension now.** 08-c1 (b) amended 0; (b) as written 1 ("08-2 reads no t_mix,e" is false against the code); (a) 1
(conditions that don't apply, nothing says which bind where); (c) 1. 08-c3 (b) 1 (in 08-3, L1–L6 and AC5/AC6/AC8 run
on a chain that may not ship); (a) 1 (rule in 08-2, its benchmark in 08-4).

**4. Tension later.** 08-c1 (b) amended 1 (commits 08-2's BRIR builder to reuse the omni `EmitterPlan`; caught at the
05h merge if its diff touches `mixingTime`, `needsIsmFallback` or the AX20 bound). (b) as written 2 (08-2 free to
compute its own t_mix,e can drift from omni; AC6 ±1 dB and AC11 see it first). (a) 1. (c) 2. 08-c3 (b) 1 (grouping
only above order 3; I-7.3: early reflections tolerate 1st/2nd order, 2° bins finer; risk is colour/level not
direction; AC5/AC6/AC8 re-run covers level and coherence; L4, L5 could flip — Seat 1 judges re-listen). 08-c3 (a) 2.

**5. Evidence.** `Engine.cpp:120-149`, `:246`; AX37 (5.2); phase-05h line 28 (AX21); AX37 (5.3), phase-05b2 lines
400-403; phase-08 S5a; [Observed, I-7.3, Frank, Brandner and Zotter] (speech/noise, tracked binaural; extension to 2°
bins in an untracked BRIR [Hyp]). Corpus not consulted.

**6. Conditions of acceptance.** 08-c1 (b) as written: adopt the amendment → 0 now, 1 later. 08-c1 (c): keep the 05h
line on 08-2, drop only from 08-1 → 1. 08-c3 (a): move the record to the benchmark's sub-phase (= (b)). 08-c3 (b): 08-4's
PR states whether grouping was introduced and, if so, marks 08-3's L4 and L5 as heard on the ungrouped chain (a note,
not a criterion).

**7. Hand-offs.** L1–L6 validity: Seat 1. BRIR build time vs AQ4/AX33: Seat 5. FTZ guard vs omni goldens: Seats 5/2.
AX20 bound and handover in 05h's diff: Seat 2.

**8. Premortem.** 08-2 recorded as reading no t_mix,e; its builder computes its own handover; AC6 ±1 dB parity in 08-3
fails on capped (AX22 fallback) rooms; seen first in CI as a binaural-only failure blamed on the tail.

| option | now | later |
|---|---|---|
| 08-c1 (a) | 1 | 1 |
| 08-c1 (b) as written | 1 | 2 |
| 08-c1 (b) amended | 0 | 1 |
| 08-c1 (c) | 1 | 2 |
| 08-c3 (a) | 1 | 2 |
| 08-c3 (b) | 1 | 1 |
