# Orchestrator computation C16: N-3W\*\*\* under joint accounting; where U fires; AX16 against the long runs; block size

2026-11-10. Asked for by `32-interrogator-round2-T1-T2-T6.md` ((f), (g), (h); it renames the decider's "C15 re-run" to C16).
Prototype outside `src/sim`: `tools/validation/phase05b2_dt1.py` step `c16`; data in JSON section `c16`.

**Rule as implemented** (29 §D-T1.3).
- **History.** One history = forward path h of emitter 0 + forward path h of emitter 1 + the shared listener-started path h,
  with next-event estimation to both emitters' images.
  - The listener-started trajectories do not depend on the gather (same key, same index). The joint work is therefore exactly
    the sum of the four next-event evaluation counts.
- **Budget.** W_scene = 2·W_max = 6.10 M.
- **Pilot.** D4 blocks of 64 histories. It stops at the first block boundary where n ≥ n\*_max or the cumulative work
  ≥ W_scene/2.
- **Final N.** N_need is the largest over emitters and bands. N = max(N_need, n\*), rounded up to blocks, capped by the work
  left (rounded down to blocks). The final range is [8 000, 8 000 + N).
- **Cap hit** means N_need > N_cap.
- **U** = (both-near AND (cap hit OR pilot VOV ≥ 0.1)) OR (cap hit AND achieved SE > 0.33 dB), per emitter. Both-near:
  d_L < 0.70 m and d_E < 0.70 m.
- **n\*_max** is shown at 8 000 and at 1 024. 1 024 = 16 blocks, the block multiple nearest the provisional ≈ 1 020.

## (f) Where U fires (columns: emitter 0 / emitter 1)

| scene | both-near (e0/e1) | n\*_max 8 000: n\*, N, cap hit, SE (dB) | U | n\*_max 1 024: n\*, N, cap hit, SE (dB) | U |
|---|---|---|---|---|---|
| W1/reference_positions | no/no | 8000, 8000, –, 0.023/0.023 | –/– | 1024, 1024, –, 0.070/0.059 | –/– |
| W1/listener_wall | no/no | 3968, 3904, –, 0.040/0.043 | –/– | 1024, 1024, –, 0.073/0.074 | –/– |
| W1/listener_edge | no/no | 2944, 2816, –, 0.058/0.041 | –/– | 1024, 1152, –, 0.104/0.062 | –/– |
| W1/listener_corner | no/no | 2560, 2432, –, 0.050/0.046 | –/– | 1024, 1024, –, 0.065/0.078 | –/– |
| W1/emitter_wall | no/no | 4864, 4736, –, 0.039/0.029 | –/– | 1024, 1280, –, 0.069/0.050 | –/– |
| W1/emitter_edge | no/no | 3904, 3840, –, 0.037/0.031 | –/– | 1024, 1024, –, 0.062/0.059 | –/– |
| W1/emitter_corner | no/no | 3456, 3392, –, 0.044/0.034 | –/– | 1024, 1024, –, 0.073/0.059 | –/– |
| W1/both_wall | yes/no | 2496, 2368, cap, 0.070/0.055 | **U**/– | 1024, 3776, cap, 0.174/0.043 | **U**/– |
| W1/both_corner | yes/no | 1344, 1280, cap, 0.078/0.069 | **U**/– | 1024, 1600, cap, 0.336/0.069 | **U**/– |
| layout4_s1/reference_positions | no/no | 448, 384, cap, 0.435/0.431 | **U**/**U** | 448, 384, cap, 0.435/0.431 | **U**/**U** |
| layout4_s1/listener_wall | no/no | 384, 320, cap, 0.738/0.768 | **U**/**U** | 384, 320, cap, 0.738/0.768 | **U**/**U** |
| layout4_s1/listener_edge | no/no | 320, 192, cap, 0.845/0.902 | **U**/**U** | 320, 192, cap, 0.845/0.902 | **U**/**U** |
| layout4_s1/listener_corner | no/no | 256, 128, cap, 0.940/0.982 | **U**/**U** | 256, 128, cap, 0.940/0.982 | **U**/**U** |
| layout4_s1/emitter_wall | no/no | 384, 320, cap, 0.704/0.481 | **U**/**U** | 384, 320, cap, 0.704/0.481 | **U**/**U** |
| layout4_s1/emitter_edge | no/no | 384, 256, cap, 0.648/0.554 | **U**/**U** | 384, 256, cap, 0.648/0.554 | **U**/**U** |
| layout4_s1/emitter_corner | no/no | 320, 192, cap, 0.958/0.579 | **U**/**U** | 320, 192, cap, 0.958/0.579 | **U**/**U** |
| layout4_s1/both_wall | yes/no | 640, 576, cap, 0.290/0.514 | **U**/**U** | 640, 576, cap, 0.290/0.514 | **U**/**U** |
| layout4_s1/both_corner | yes/no | 256, 128, cap, 1.331/1.150 | **U**/**U** | 256, 128, cap, 1.331/1.150 | **U**/**U** |
| layout4_s1/listener_absorber | no/no | 512, 384, cap, 0.638/0.713 | **U**/**U** | 512, 384, cap, 0.638/0.713 | **U**/**U** |
| layout5_s1/reference_positions | no/no | 320, 192, cap, 0.441/0.396 | **U**/**U** | 320, 192, cap, 0.441/0.396 | **U**/**U** |
| layout5_s1/listener_wall | no/no | 4288, 4160, cap, 0.169/0.174 | –/– | 1024, 7296, cap, 0.131/0.132 | –/– |
| layout5_s1/listener_edge | no/no | 3840, 3648, cap, 0.337/0.295 | **U**/– | 1024, 6400, cap, 0.274/0.235 | –/– |
| layout5_s1/listener_corner | no/no | 3072, 3008, cap, 0.246/0.284 | –/– | 1024, 4992, cap, 0.196/0.240 | –/– |
| layout5_s1/emitter_wall | no/no | 512, 384, cap, 0.716/0.292 | **U**/– | 512, 384, cap, 0.716/0.292 | **U**/– |
| layout5_s1/emitter_edge | no/no | 512, 384, cap, 0.607/0.292 | **U**/– | 512, 384, cap, 0.607/0.292 | **U**/– |
| layout5_s1/emitter_corner | no/no | 448, 384, cap, 0.708/0.292 | **U**/– | 448, 384, cap, 0.708/0.292 | **U**/– |
| layout5_s1/both_wall | yes/no | 2624, 2496, cap, 0.603/0.223 | **U**/– | 1024, 4032, cap, 1.024/0.176 | **U**/– |
| layout5_s1/both_corner | yes/no | 1344, 1280, cap, 0.210/0.517 | **U**/**U** | 1024, 1600, cap, 0.186/0.458 | **U**/**U** |
| layout5_s1/listener_absorber | no/no | 640, 512, cap, 0.473/0.914 | **U**/**U** | 640, 512, cap, 0.473/0.914 | **U**/**U** |
| W1/both_wall_0.3 | yes/no | 2560, 2432, cap, 0.095/0.056 | **U**/– | 1024, 3392, –, 0.077/0.047 | **U**/– |
| W1/both_wall_0.5 | yes/no | 2624, 2496, cap, 0.148/0.054 | **U**/– | 1024, 4032, cap, 0.122/0.041 | **U**/– |
| club/default | no/no | 8000, 8000, –, 0.020/0.020 | –/– | 1024, 1024, –, 0.055/0.057 | –/– |
| club/listener_wall_0.1 | no/no | 8000, 8000, –, 0.032/0.032 | –/– | 1024, 1344, –, 0.080/0.080 | –/– |
| club/emitter0_wall_0.1 | no/no | 8000, 8000, –, 0.023/0.020 | –/– | 1024, 1024, –, 0.067/0.057 | –/– |
| club/both_wall_0.1 | yes/no | 6912, 6848, cap, 0.306/0.030 | **U**/– | 1024, 12544, cap, 0.231/0.022 | **U**/– |
| club/both_edge_0.1 | yes/no | 2176, 2112, cap, 0.113/0.062 | **U**/– | 1024, 3200, cap, 0.099/0.049 | **U**/– |
| club/both_wall_0.3 | yes/no | 7424, 7296, –, 0.059/0.028 | –/– | 1024, 5824, –, 0.069/0.032 | **U**/– |
| club/both_edge_0.3 | yes/no | 2304, 2240, cap, 0.212/0.054 | **U**/– | 1024, 3456, cap, 0.161/0.043 | **U**/– |
| club/both_wall_0.5 | yes/no | 8000, 8000, –, 0.039/0.026 | –/– | 1024, 3072, –, 0.066/0.043 | **U**/– |
| club/both_edge_0.5 | yes/no | 2496, 2432, cap, 0.140/0.049 | **U**/– | 1024, 3648, –, 0.106/0.039 | **U**/– |
| living_room/default | no/no | 8000, 8000, –, 0.008/0.009 | –/– | 1024, 1024, –, 0.024/0.024 | –/– |
| living_room/listener_wall_0.1 | no/no | 4992, 4928, –, 0.020/0.020 | –/– | 1024, 1024, –, 0.044/0.046 | –/– |
| living_room/emitter0_wall_0.1 | no/no | 8000, 7872, –, 0.009/0.009 | –/– | 1024, 1024, –, 0.026/0.024 | –/– |
| living_room/both_wall_0.1 | yes/no | 3968, 3840, –, 0.079/0.023 | **U**/– | 1024, 4608, –, 0.068/0.021 | **U**/– |
| living_room/both_edge_0.1 | yes/no | 1728, 1664, cap, 0.280/0.034 | **U**/– | 1024, 2304, cap, 0.213/0.029 | **U**/– |
| living_room/both_wall_0.3 | yes/no | 4608, 4480, –, 0.026/0.019 | –/– | 1024, 1024, –, 0.053/0.042 | –/– |
| living_room/both_edge_0.3 | yes/no | 2048, 1984, –, 0.110/0.028 | –/– | 1024, 2112, –, 0.105/0.027 | **U**/– |
| living_room/both_wall_0.5 | yes/no | 5376, 5248, –, 0.018/0.016 | –/– | 1024, 1024, –, 0.040/0.037 | –/– |
| living_room/both_edge_0.5 | yes/no | 2496, 2432, –, 0.048/0.023 | –/– | 1024, 1024, –, 0.074/0.035 | –/– |
| dead_booth/default | no/no | 2944, 2816, –, 0.011/0.011 | –/– | 1024, 1024, –, 0.018/0.018 | –/– |
| dead_booth/listener_wall_0.1 | yes/yes | 2112, 1984, –, 0.025/0.024 | –/– | 1024, 1024, –, 0.035/0.034 | –/– |
| dead_booth/emitter0_wall_0.1 | no/no | 2624, 2496, –, 0.013/0.011 | –/– | 1024, 1024, –, 0.021/0.018 | –/– |
| classroom/default | no/no | 8000, 8000, –, 0.012/0.012 | –/– | 1024, 1024, –, 0.032/0.033 | –/– |
| classroom/listener_wall_0.1 | no/no | 8000, 8000, –, 0.019/0.019 | –/– | 1024, 1024, –, 0.052/0.054 | –/– |
| classroom/emitter0_wall_0.1 | no/no | 8000, 8000, –, 0.014/0.012 | –/– | 1024, 1024, –, 0.040/0.033 | –/– |
| concert_hall_box/default | no/no | 8000, 8000, –, 0.054/0.050 | –/– | 1024, 3520, –, 0.086/0.075 | –/– |
| concert_hall_box/listener_wall_0.1 | no/no | 8000, 8000, –, 0.078/0.082 | –/– | 1024, 5504, –, 0.097/0.108 | –/– |
| concert_hall_box/emitter0_wall_0.1 | no/no | 8000, 8000, –, 0.068/0.050 | –/– | 1024, 3520, –, 0.102/0.075 | –/– |
| stone_box/default | no/no | 8000, 8000, –, 0.007/0.007 | –/– | 1024, 1024, –, 0.019/0.017 | –/– |
| stone_box/listener_wall_0.1 | no/no | 8000, 8000, –, 0.008/0.008 | –/– | 1024, 1024, –, 0.022/0.021 | –/– |
| stone_box/emitter0_wall_0.1 | no/no | 8000, 8000, –, 0.007/0.007 | –/– | 1024, 1024, –, 0.022/0.017 | –/– |
| dt6_small_room | yes/yes | 4352, 4288, –, 0.006/0.006 | –/– | 1024, 1024, –, 0.013/0.013 | –/– |
| cube100_alpha0.10-0.22_s0.3 | no/no | 1856, 1792, cap, 0.202/0.143 | –/– | 1024, 2624, cap, 0.152/0.101 | –/– |
| cube100_lowalpha0.05_s0.3 | no/no | 1856, 1792, cap, 0.187/0.128 | –/– | 1024, 2624, cap, 0.143/0.092 | –/– |
| cube100_lowalpha0.05_s1 | no/no | 1920, 1792, cap, 0.508/0.667 | **U**/**U** | 1024, 2688, cap, 0.442/0.504 | **U**/**U** |
| cube100_flutter_fallback | no/no | 320, 256, –, 0.002/0.002 | –/– | 320, 256, –, 0.002/0.002 | –/– |
| cube100_absorbing_floor_s1 | no/no | 1920, 1792, cap, 0.119/0.116 | –/– | 1024, 2688, cap, 0.099/0.090 | –/– |

Readings:
1. **U is silent at all six Phase 04 rooms' default placements, at every one-end placement in them, in the D-T6 small
   room, and in the closed 100 m cubes at s = 0.3 and with an absorbing floor**, at both n\*_max values.
   - `dead_booth` with the listener at its wall is both-near for both emitters, and U stays silent (SE 0.024 dB, VOV 0.00).
2. **U fires wherever Seat 1's floor fails:** every layout 4 case (SE 0.43–1.33 dB), layout 5's reference positions and
   most of its one-end cases, and the low-α 100 m cube at s = 1 (SE 0.44–0.67 dB).
3. **U fires on the moved emitter of every both-near placement measured in W1, `club` and `living_room` at 0.1 m**, and on
   some at 0.3 and 0.5 m.
   - Most of these estimates are poor or heavy-tailed: VOV 0.13–0.93, capped, SE 0.07–0.31 dB, and C13 §2 shows that such
     capped draws read low.
   - **Good estimates that U also flags** (C13 §3 replicate p95 in brackets):
     - `living_room` both_wall_0.1: SE 0.079 dB, VOV 0.23 (p95 0.15 dB);
     - W1 both_wall_0.3: SE 0.095 dB, VOV 0.37 (p95 0.49 dB).
4. **At n\*_max 1 024 the smaller pilot raises U more often** on good ordinary both-near placements, through a noisier
   pilot VOV:
   - `club` both_wall_0.3 and both_wall_0.5 (SE 0.069 / 0.066 dB);
   - `living_room` both_edge_0.3 (SE 0.105 dB).

   At n\*_max 8 000 the joint rule leaves `club` both_wall_0.3 silent: VOV 0.09 and no cap hit. Under C13's per-emitter
   rule it was capped.
5. **Joint accounting changes cap status.** Joint N_need is the largest over both emitters, so the unmoved emitter's
   estimate is sometimes capped together with the moved one.
   - Layout 5's one-end cases (emitter_wall/edge/corner, listener_absorber) cap the unmoved emitter at SE 0.29–0.91 dB.
   - Layout 4 caps both emitters at 0.43–1.33 dB.

## (g) AX16 against the C15 1 M-history long runs (1 kHz)

| scene, emitter | long-run SE (dB) | AX16 − long run (dB) | shipping rule under Q2 (A): achieved SE (dB, C16 n\*_max 8 000) |
|---|---|---|---|
| cube100_alpha0.10-0.22_s0.3_e0 | 0.0061 | +0.019 | 0.202 |
| cube100_alpha0.10-0.22_s0.3_e1 | 0.0061 | +0.019 | 0.143 |
| cube100_lowalpha0.05_s0.3_e0 | 0.0063 | +0.022 | 0.187 |
| cube100_lowalpha0.05_s0.3_e1 | 0.0063 | +0.023 | 0.128 |
| cube100_lowalpha0.05_s1_e0 | 0.0221 | +0.057 | 0.508 |
| cube100_lowalpha0.05_s1_e1 | 0.0220 | +0.101 | 0.667 |
| cube100_absorbing_floor_s1_e0 | 0.0051 | +2.384 | 0.119 |
| cube100_absorbing_floor_s1_e1 | 0.0051 | +2.393 | 0.116 |

Readings:
- **Closed cubes at s = 0.3.** The old method's error is +0.019 to +0.023 dB, resolved (long-run SE 0.006 dB). The shipping
  rule under (A) adds a random error of SE 0.13–0.20 dB there.
- **Low-α cube at s = 1.** AX16 is +0.06 / +0.10 dB, and the shipping rule's SE is 0.51 / 0.67 dB.
- **In these two classes the switch adds error under (A)** where the old method was nearly exact. Replicates bound that
  error: C15 medians −0.06 to +0.15 dB, p95 ≤ 0.89 dB.
- **Absorbing-floor cube at s = 1.** AX16 is **+2.38 / +2.39 dB** wrong. The shipping rule's SE is 0.12 dB, so the switch
  corrects a 2.4 dB error.
- This replaces the round-3 claim "old error +0.09 / −0.06 dB", which was unresolved within its SE (ledger
  P05B2-T1T2T6-45).

## (h) D4 block size: one-block overrun of the pilot as a fraction of W_scene

| block (histories) | divides 8 000 | divides 1 024 | worst one-block overrun / W_scene, over all C16 scenes |
|---|---|---|---|
| 32 | yes | yes | 0.076 |
| 64 | yes | yes | 0.153 |
| 128 | no | yes | 0.305 |
| 256 | no | yes | 0.611 |

- **64 is the largest of these that divides 8 000** (125 blocks) and 1 024 (16 blocks).
  - Its worst overrun is 15.3 % of W_scene, at layout4_s1/listener_corner. Next are layout4_s1/both_corner (14.6 %)
    and layout5_s1/reference_positions (12.5 %), all in layout 4/5-class rooms.
  - At every gated 100 m scene the overrun is below 10.2 %.
- **128 and 256 do not divide 8 000.** A pilot that stops at n\*_max = 8 000 would then overlap the final range's fixed
  start, unless n\*_max is rounded down.
- So the pilot is bounded by W_scene/2 plus at most 15 % of W_scene. With 32-history blocks the bound is 8 %.
