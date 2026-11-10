# Orchestrator computation C16b: the note's VOV leg over pilot ∪ final range at n\*_max 1 024 (Seat 6, S6-b)

2026-11-10. Seat 6's condition in `35-seat6-confirm-S6b.md`. At n\*_max 1 024 the note's VOV leg is computed over the pilot
plus the final range, up to the first 8 000 histories (per-history scores, largest over the 8 bands), instead of over the
pilot alone. U is then recomputed for every both-near case of C16 (f). The estimate itself is unchanged, so the final range's
freshness (F14) is untouched. Code: step `c16b`; data: JSON section `c16b`.

| case | histories used | VOV pilot only (e0/e1) | VOV pilot ∪ final (e0/e1) | SE (dB, e0/e1) | cap hit | U, pilot VOV | U, union VOV | U at n\*_max 8 000 |
|---|---|---|---|---|---|---|---|---|
| W1/both_wall | 4800 | 0.985/0.047 | 0.551/0.014 | 0.174/0.043 | yes | **U**/– | **U**/– | **U**/– |
| W1/both_corner | 2624 | 0.273/0.049 | 0.502/0.022 | 0.336/0.069 | yes | **U**/– | **U**/– | **U**/– |
| layout4_s1/both_wall | 1216 | 0.161/0.042 | 0.061/0.029 | 0.290/0.514 | yes | **U**/**U** | **U**/**U** | **U**/**U** |
| layout4_s1/both_corner | 384 | 0.208/0.132 | 0.175/0.076 | 1.331/1.150 | yes | **U**/**U** | **U**/**U** | **U**/**U** |
| layout5_s1/both_wall | 5056 | 0.174/0.264 | 0.802/0.029 | 1.024/0.176 | yes | **U**/– | **U**/– | **U**/– |
| layout5_s1/both_corner | 2624 | 0.315/0.186 | 0.089/0.056 | 0.186/0.458 | yes | **U**/**U** | **U**/**U** | **U**/**U** |
| W1/both_wall_0.3 | 4416 | 0.345/0.060 | 0.064/0.014 | 0.077/0.047 | no | **U**/– | –/– | **U**/– |
| W1/both_wall_0.5 | 5056 | 0.308/0.075 | 0.089/0.012 | 0.122/0.041 | yes | **U**/– | **U**/– | **U**/– |
| club/both_wall_0.1 | 8000 | 0.393/0.005 | 0.289/0.001 | 0.231/0.022 | yes | **U**/– | **U**/– | **U**/– |
| club/both_edge_0.1 | 4224 | 0.731/0.013 | 0.160/0.003 | 0.099/0.049 | yes | **U**/– | **U**/– | **U**/– |
| club/both_wall_0.3 | 6848 | 0.265/0.005 | 0.065/0.001 | 0.069/0.032 | no | **U**/– | –/– | –/– |
| club/both_edge_0.3 | 4480 | 0.208/0.016 | 0.110/0.003 | 0.161/0.043 | yes | **U**/– | **U**/– | **U**/– |
| club/both_wall_0.5 | 4096 | 0.154/0.005 | 0.032/0.001 | 0.066/0.043 | no | **U**/– | –/– | –/– |
| club/both_edge_0.5 | 4672 | 0.148/0.012 | 0.034/0.002 | 0.106/0.039 | no | **U**/– | –/– | **U**/– |
| living_room/both_wall_0.1 | 5632 | 0.409/0.007 | 0.123/0.001 | 0.068/0.021 | no | **U**/– | **U**/– | **U**/– |
| living_room/both_edge_0.1 | 3328 | 0.288/0.005 | 0.157/0.002 | 0.213/0.029 | yes | **U**/– | **U**/– | **U**/– |
| living_room/both_wall_0.3 | 2048 | 0.082/0.008 | 0.029/0.004 | 0.053/0.042 | no | –/– | –/– | –/– |
| living_room/both_edge_0.3 | 3136 | 0.106/0.007 | 0.062/0.002 | 0.105/0.027 | no | **U**/– | –/– | –/– |
| living_room/both_wall_0.5 | 2048 | 0.011/0.008 | 0.005/0.003 | 0.040/0.037 | no | –/– | –/– | –/– |
| living_room/both_edge_0.5 | 2048 | 0.014/0.009 | 0.006/0.003 | 0.074/0.035 | no | –/– | –/– | –/– |
| dead_booth/listener_wall_0.1 | 2048 | 0.006/0.006 | 0.003/0.003 | 0.035/0.034 | no | –/– | –/– | –/– |
| dt6_small_room | 2048 | 0.006/0.005 | 0.003/0.002 | 0.013/0.013 | no | –/– | –/– | –/– |

**Readings.**
1. **Seat 6's three named good placements go silent:** `club` both_wall_0.3 (SE 0.069 dB), `club` both_wall_0.5 (0.066 dB)
   and `living_room` both_edge_0.3 (0.105 dB). Two more go silent as well: `club` both_edge_0.5 (0.106 dB) and W1
   both_wall_0.3 (0.077 dB).
2. **Every case with a capped SE above 0.33 dB still fires**, because that leg of U does not depend on VOV: W1 both_corner,
   layout 4 both_corner, layout 5 both_wall.
3. **Every heavy-tailed both-near case at 0.1 m still fires**, through the union VOV (0.12–0.80) or a cap hit: W1, `club`,
   `living_room`, and layouts 4/5.
4. **`living_room` both_wall_0.1 still fires** (union VOV 0.12, SE 0.068 dB). This is the one good estimate U flags at both
   pilot sizes; at n\*_max 8 000 it fires too.
5. **Silent as before:** `dead_booth` with the listener at a wall, the D-T6 small room, and the 0.3 / 0.5 m `living_room`
   wall placements.
6. **Pattern at 1 024 with the union VOV:** U fires on the same set as at n\*_max 8 000, minus W1 both_wall_0.3 and
   `club` both_edge_0.5.

Seat 6's test of its condition ("check that `club` both_wall_0.3/0.5 and `living_room` both_edge_0.3 go silent while every
SE > 0.33 dB case still fires") is met.
