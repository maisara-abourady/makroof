# Orchestrator computation C12: NW-4C and N-3W* (for the second D-T1 seat round)

(Part (a) is appended when its run completes.)

2026-11-09. Requested by the decider (`21-decider-decision-T1-T2-T6.md`, "Orchestrator computations needed before the second
round (C12)"). Prototype outside `src/sim`: `tools/validation/phase05b2_dt1.py` steps `c12d`, `c12b`, `c12a` (kernel `mc5` =
`mc3`'s model and random stream with a path-index offset and a per-path count of image evaluations); data in
`tools/validation/data/phase05b2_dt1.json` section `c12`. 4 threads unless stated.

**As implemented.**
- **NW-4C:** per emitter, E_diffuse = w·E_fwd + (1 − w)·E_rev with w = d_L² / (d_L² + d_E²), d = that end's distance to the nearest
  surface. E_fwd starts paths at the emitter and gathers at the listener's images (seed 0x5EED). E_rev starts at the listener and
  gathers at the emitter's images (seed 0x5EEE, an independent stream). History p pairs path p of each set; its score is
  w·fwd_p + (1 − w)·rev_p. The plan (window, t_mix,e, referral) is always the true positions'. The prototype runs the
  listener-started set once per emitter, so its costs are an upper bound: the shipping design shares one listener-started set
  between both emitters.
- **N-3W\*:** pilot histories [0, n\*) with n\* = 8 000 give the worst-band SE (dB of the total E_target, all 8 bands).
  N = ⌈n\*·(SE_pilot / 0.083 dB)²⌉ (Tol-2). The final estimate comes from the disjoint range [n\*, n\* + N) alone; the pilot is
  discarded. N is capped so that pilot plus final image evaluations ≤ W_max, and a cap hit is flagged.
- **Tally checks** on the pilot's per-history scores, per band:
  - R = SE / mean of the diffuse estimate;
  - VOV = Σ(x − x̄)⁴ / (Σ(x − x̄)²)² − 1/N;
  - slope = 1 + Hill index over the largest min(200, 5 %) scores, capped at 10. This is a simpler estimator than MCNP's
    Pareto fit.
  - Thresholds as in the researcher's dossier: R < 0.05, VOV < 0.1, slope > 3.

## (d) W_max from the restore bound

Cost per image evaluation of the prototype kernel at the gated scene (100 m cube, forward, 8 000 paths, wall time including the
path tracing):

| scene | evaluations | 1 thread | 4 threads |
|---|---|---|---|
| cube100 (α 0.10–0.22, s 0.3), e0 / e1 | 3.32 M | 34.1 / 35.2 ns | 9.0 / 8.6 ns |
| cube100_flutter (AX22 fallback), e0 / e1 | 19.56 M | 41.9 / 42.5 ns | 10.6 / 10.5 ns |

W_max is two emitters' solves within the restore bound minus the existing build:
- The restore bound is 30 s / 14 = 2.143 s (Challenge 1, still with Maisara).
- The existing build at 100 m and 96 kHz takes 1.51–1.88 s (BUILD_PLAN §0 row 07).
- The cost used is the gated scene's 9.02 ns at 4 threads.

| existing build | budget for two emitters | **W_max per emitter** |
|---|---|---|
| 1.51 s | 0.633 s | 35.1 M evaluations |
| **1.88 s (used)** | 0.263 s | **14.6 M evaluations** (0.131 s at 4 threads on this box) |

- **Seat 3's and Seat 6's 3 s bound** is met with room to spare. W_max is 0.13 s per emitter at 4 threads and about 0.51 s at
  1 thread on this box. The CI runner's speed is not measured `[Inferred: same order]`.
- **The C++ cost per evaluation is not measured.** The numba prototype is a proxy `[Inferred]`. W_max scales inversely with
  the real cost, so it must be re-derived from the C++ build.

### Paths allowed under W_max, NW-4C against forward-only at the reference positions, and the pilot's tally checks — parts (c), (d) and (e)

Columns:
- "Tol-2 need": paths or histories for a worst-band SE of 0.083 dB, from the 8 000-path pilot.
- "cost ratio": NW-4C's image evaluations to Tol-2 over forward-only's.
- "pilot / W_max": the 8 000-history NW-4C pilot's evaluations over W_max.
- Tally checks: largest R and VOV, and smallest slope, over the 8 bands of the NW-4C pilot.

| scene | w | evals per fwd path | Tol-2 need, fwd | Tol-2 need, NW-4C | cost ratio | fwd paths in W_max | NW-4C histories in W_max | pilot / W_max | R | VOV | slope |
|---|---|---|---|---|---|---|---|---|---|---|---|
| W1_e0 | 0.42 | 90 | 1223 | 607 | 0.98 | 161,485 | 81,503 | 0.10 | 0.012 | 0.008 | 2.93 |
| W1_e1 | 0.42 | 90 | 1538 | 672 | 0.87 | 162,089 | 81,670 | 0.10 | 0.012 | 0.007 | 2.94 |
| W2_e0 | 0.42 | 2826 | 73 | 16 | 0.44 | 5,155 | 2,575 | 3.11 | 0.022 | 0.397 | 3.25 |
| W2_e1 | 0.42 | 2819 | 16 | 6 | 0.75 | 5,167 | 2,579 | 3.10 | 0.014 | 0.018 | 3.21 |
| bras_cr4_ls1_mp1 | 0.42 | 80 | 1524 | 717 | 1.17 | 181,577 | 73,170 | 0.11 | 0.013 | 0.003 | 3.73 |
| bras_cr4_ls1_mp2 | 0.28 | 149 | 1252 | 547 | 0.89 | 97,996 | 48,290 | 0.17 | 0.013 | 0.003 | 3.62 |
| bras_cr4_ls1_mp3 | 0.44 | 165 | 1474 | 798 | 1.13 | 88,357 | 42,335 | 0.19 | 0.015 | 0.006 | 3.19 |
| bras_cr4_ls1_mp4 | 0.35 | 97 | 1136 | 550 | 1.07 | 149,674 | 67,710 | 0.12 | 0.012 | 0.003 | 4.00 |
| bras_cr4_ls1_mp5 | 0.51 | 138 | 1515 | 774 | 1.05 | 105,565 | 51,412 | 0.16 | 0.013 | 0.004 | 3.56 |
| bras_cr4_ls2_mp1 | 0.43 | 106 | 1089 | 581 | 1.32 | 137,424 | 55,732 | 0.14 | 0.013 | 0.003 | 3.93 |
| bras_cr4_ls2_mp2 | 0.15 | 117 | 3562 | 915 | 0.54 | 124,039 | 59,349 | 0.13 | 0.015 | 0.006 | 3.15 |
| bras_cr4_ls2_mp3 | 0.45 | 125 | 807 | 519 | 1.44 | 116,589 | 52,032 | 0.15 | 0.012 | 0.004 | 3.81 |
| bras_cr4_ls2_mp4 | 0.36 | 146 | 1122 | 606 | 1.20 | 99,533 | 44,881 | 0.18 | 0.013 | 0.003 | 3.93 |
| bras_cr4_ls2_mp5 | 0.51 | 253 | 1218 | 645 | 1.08 | 57,669 | 28,162 | 0.28 | 0.014 | 0.005 | 3.43 |
| cube100_e0 | 0.42 | 415 | 13825 | 5568 | 0.81 | 35,092 | 17,534 | 0.46 | 0.024 | 0.077 | 2.07 |
| cube100_e1 | 0.42 | 416 | 4710 | 6063 | 2.57 | 35,034 | 17,520 | 0.46 | 0.026 | 0.118 | 2.25 |
| cube100_flutter_e0 | 0.42 | 2445 | 4 | 1 | 0.50 | 5,957 | 2,975 | 2.69 | 0.049 | 0.308 | 2.55 |
| cube100_flutter_e1 | 0.42 | 2446 | 4 | 1 | 0.50 | 5,957 | 2,974 | 2.69 | 0.050 | 0.675 | 2.70 |
Readings:
1. **Cost of NW-4C at the reference positions.** Here both ends are 1.7–2 m from a surface, so w ≈ 0.15–0.51. Image
   evaluations to Tol-2 run from 0.44× (W2) to 2.57× (cube100 e1) of forward-only. The median over the 18 rows is 1.02×.
   Two sets of half the length cost what one set of the full length costs.
2. **The pilot dominates the work, not the final range.** At the W1, CR4 and 100 m reference positions the Tol-2 need is
   519–6 063 histories, below n\* = 8 000. The pilot alone costs 10–46 % of W_max there.
3. **Conflict 1: the pilot does not fit W_max in the hard-walled rooms.**
   - The 8 000-history pilot costs 3.1× W_max in W2 and 2.7× in the 100 m flutter cube. The flutter cube is a gated scene:
     the AX22 fallback build, which is the larger of the two 100 m builds.
   - So N-3W\* as composed cannot run there. n_cap = 0, and no final range is left.
   - Yet those scenes need only 1–16 histories for Tol-2.
   - The decider's rule ("if these bounds conflict, the conflict goes back to the seats") applies. A pilot defined in work
     rather than in histories, e.g. n\* = min(8 000, the histories that fit a fixed share of W_max), would remove the conflict.
     That is a product choice for the seats.
4. **(e) Tally checks.** R < 0.05 holds in every row except the 100 m flutter cube (0.049 / 0.050, the limit). VOV < 0.1
   holds at W1, CR4 and cube100 e0. It is exceeded at:
   - W2 e0: 0.40;
   - cube100 e1: 0.118;
   - the flutter cube: 0.31 / 0.68.

   Forward-only is worse in every one of these. The slope, as estimated here, is below 3 even at the W1 reference positions
   (2.93), where the estimate is well behaved. As a flag it would fire almost everywhere, so it carries little information
   at n\* = 8 000.

## (d) continued: cap hits and Seat 1's floor on CS-NW+ and the six Phase 04 rooms (Seat 7)

N-3W\* run as specified, with W_max = 14.6 M evaluations:
- **CS-NW+:** the W1 listener at 0.1 m from a wall, an edge and a corner; at 0.3 m from a wall; and the emitter at 0.1 m from
  a wall.
- **The six Phase 04 rooms:** first the listener, then the first emitter, moved to 0.1 m from its nearest surface.

"Evals for SE 0.33 dB" is the work Seat 1's floor needs, scaled from the pilot.

| case | w | pilot SE (dB) | N need | N cap | cap hit | final SE (dB) | evals for SE 0.33 dB | R | VOV | slope |
|---|---|---|---|---|---|---|---|---|---|---|
| W1_listener_wall | 0.002 | 0.030 | 1,040 | 29,842 | no | 0.072 | 25,321 | 0.012 | 0.0099 | 2.73 |
| W1_listener_edge | 0.002 | 0.032 | 1,192 | 23,639 | no | 0.101 | 34,698 | 0.012 | 0.0137 | 2.59 |
| W1_listener_corner | 0.002 | 0.025 | 753 | 18,360 | no | 0.079 | 26,307 | 0.010 | 0.0129 | 3.15 |
| W1_listener_wall_0.3 | 0.022 | 0.030 | 1,045 | 30,587 | no | 0.068 | 24,942 | 0.012 | 0.0096 | 2.73 |
| W1_emitter_wall | 0.997 | 0.029 | 990 | 23,934 | no | 0.081 | 28,571 | 0.012 | 0.0167 | 2.52 |
| dead_booth_listener_wall | 0.038 | 0.012 | 174 | 11,661 | no | 0.095 | 8,127 | 0.004 | 0.0008 | 8.28 |
| dead_booth_emitter_wall | 0.980 | 0.007 | 60 | 13,956 | no | 0.087 | 2,505 | 0.003 | 0.0005 | 10.00 |
| living_room_listener_wall | 0.010 | 0.016 | 283 | 39,545 | no | 0.078 | 5,482 | 0.008 | 0.0009 | 6.53 |
| living_room_emitter_wall | 0.993 | 0.009 | 104 | 61,513 | no | 0.080 | 1,372 | 0.006 | 0.0009 | 6.65 |
| classroom_listener_wall | 0.007 | 0.020 | 448 | 107,411 | no | 0.072 | 3,573 | 0.014 | 0.0015 | 4.95 |
| classroom_emitter_wall | 0.993 | 0.014 | 232 | 99,007 | no | 0.071 | 1,990 | 0.010 | 0.0024 | 3.72 |
| club_listener_wall | 0.002 | 0.033 | 1,242 | 100,070 | no | 0.081 | 10,589 | 0.017 | 0.0016 | 5.38 |
| club_emitter_wall | 0.997 | 0.023 | 595 | 90,809 | no | 0.091 | 5,542 | 0.011 | 0.0013 | 5.11 |
| concert_hall_box_listener_wall | 0.004 | 0.073 | 6,199 | 89,720 | no | 0.089 | 58,464 | 0.027 | 0.0466 | 2.33 |
| concert_hall_box_emitter_wall | 0.997 | 0.056 | 3,631 | 89,975 | no | 0.099 | 34,153 | 0.020 | 0.0383 | 2.33 |
| stone_box_listener_wall | 0.003 | 0.008 | 83 | 112,729 | no | 0.071 | 631 | 0.011 | 0.0021 | 4.25 |
| stone_box_emitter_wall | 0.997 | 0.007 | 61 | 110,803 | no | 0.083 | 470 | 0.009 | 0.0037 | 5.61 |
Readings:
1. **Cap hits.** The rate is **0 of 17**. Every case needs at most 6 200 final histories against caps of 9 100–113 000.
2. **Seat 1's floor is met in all 17.** SE 0.33 dB needs 0.5 k–58 k evaluations against W_max = 14.6 M. VOV < 0.1 holds on
   every pilot (largest 0.047, `concert_hall_box`).
3. **Conflict 2: the final range is smaller than the discarded pilot.**
   - N is 60–6 200 against n\* = 8 000, so the published estimate rests on fewer histories than were computed and thrown away.
   - Its SE is about the target (0.07–0.10 dB). It exceeds 0.083 dB in 6 of 17 cases (the SE of an N-path range is itself
     estimated).
   - The pilot alone reached 0.007–0.073 dB.
   - This is the price of a fresh range (F14) whose start does not depend on N. A minimum final N (e.g. N ≥ n\*) would cost
     at most twice the pilot's work and is within W_max in all 17 cases. That is a choice for the seats, not made here.

## (b) 1 cm sweeps under N-3W\* at Tol-2 (W1)

Largest step between neighbouring points over the 8 bands, with W_max = 14.6 M evaluations. The "same-N" column covers only
neighbours whose N is equal.

| sweep | points | w range | N range | N changes | cap hits | largest step (dB) | largest step at equal N (dB) |
|---|---|---|---|---|---|---|---|
| listener 1.0 → 0.1 m off a wall | 91 | 0.002–0.20 | 1 029–1 071 | 75 | 0 | 0.040 | 0.006 |
| listener along a wall at 0.1 m, 1 m | 101 | 0.002 | 1 016–1 087 | 90 | 0 | 0.030 | 0.001 |
| listener into a corner, 1 → 0.1 m | 101 | 0.002–0.20 | 1 179–1 524 | 94 | 0 | 0.027 | 0.003 |
| emitter crossing d_E = d_L (listener 0.3 m off y = 0; emitter 0.6 → 0.1 m off y = 30) | 51 | 0.20–0.90 | 9 327–9 890 (capped) | 50 | **51** | 0.026 | – |
| both 1.0 → 0.1 m off opposite walls | 91 | 0.50 | 3 291–9 943 | 90 | **38** | **0.209** (at 0.11 → 0.10 m) | – |

Readings:
1. **Listener sweeps.** With the listener near a wall NW-4C puts almost all weight on the listener-started set (w ≈ 0.002).
   - N barely changes, and the largest step is 0.04 dB per cm.
   - Under NW-1 with N-2 the step was up to 0.358 dB along a wall (19 §4).
   - Where N changes between neighbours the step is a fresh-range draw at SE ≈ 0.083 dB. That bounds the step at
     ≈ √2 × the SE.
2. **The emitter crossing d_E = d_L is continuous.** The weight moves from 0.2 to 0.9 and no step exceeds 0.026 dB.
3. **Why the last two sweeps hit the cap.** These sweeps put emitter and listener 28–30 m apart, so the window is longer:
   t_mix,e is 0.160–0.165 s, against 0.114 s at the reference positions. Image evaluations rise to 750–850 per history,
   against 180, and the cap allows about 9 100–11 400 histories.
   - **Crossing sweep:** SE needs exceed that (pilot SE 0.105–0.178 dB), so every point is capped at N ≈ 9.3–9.9 k. The
     final SE is 0.081–0.128 dB at the start, middle and end points checked.
4. **Both ends near walls: NW-4C reverts to NW-1's cost, as the decider stated.**

   | point | pilot SE | pilot VOV | N need | capped final SE |
   |---|---|---|---|---|
   | both at 1.0 m | 0.053 dB | – | 3 291 | – |
   | both at 0.5 m | 0.089 dB | 0.056 | 9 143 | – |
   | both at 0.11 m | 0.56 dB | 0.32 | 364 000 | 0.29 dB |
   | both at 0.10 m | 0.57 dB | 0.29 | 377 000 | 0.15 dB |

   - At 0.11 and 0.10 m the final SE is below Seat 1's 0.33 dB, but the VOV condition (< 0.1) fails, and the step between
     those two points is 0.21 dB.
   - That case is the one the decider's NW-4C flags "near-wall, unreferenced".

## Coupling with D-T2's L2-F1R (for the second-round rating)

L2-F1R targets SE 0.0187 dB (decider's working: ≈ 19.8× Tol-2's paths). Under the same pilot and W_max (14.6 M evaluations), the
work for one emitter (pilot plus final) relative to W_max is:

| scene | histories for SE 0.0187 dB | work / W_max |
|---|---|---|
| W1 (both emitters) | 12 000–13 200 | 0.24–0.26 |
| CR4 (10 pairs) | 10 200–18 000 | 0.28–0.73 |
| **cube100 e0 / e1** | 110 000 / 119 000 | **6.7 / 7.3** |
| W2, cube100_flutter | 16–311 | 2.7–3.2 (the pilot alone; conflict 1) |
| CS-NW+ and the Phase 04 near-wall cases | 1 200–122 000 | cap hit in 1 of 17 (`concert_hall_box`, listener at the wall) |

At the gated 100 m scene, L2-F1R needs about 7× W_max. At 4 threads on this box that is about 0.9–1.0 s per emitter, and about
1.9 s for two. Against a 0.26 s budget, the restore comes to about 3.7 s (1.88 + 1.84 s) against 2.14 s. This is the same order as Seat 5's
estimate for L2-F2 in the first round.
