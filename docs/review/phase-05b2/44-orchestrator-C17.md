# Orchestrator computation C17: layouts 4/5 at s = 1 under Q2a (B) (for rating R2, decider file 43)

2026-11-10. Same joint rule as C16, but with W_scene = 2 × 11.4 × W_max (A) = 69.5 M evaluations (option (B)) and n\*_max 1 024.
Each emitter is checked against Seat 1's floor: SE ≤ 0.33 dB with pilot VOV < 0.1. The VOV here is the pilot's alone, over
1 024 histories. Code: step `c17`; data: JSON section `c17`. Under (A), for comparison (C16 (f)), every layout-4 case is
capped at SE 0.29–1.33 dB.

| case | n\* | N | cap hit | SE (dB, e0/e1) | pilot VOV (e0/e1) | floor met (e0/e1) |
|---|---|---|---|---|---|---|
| layout4_s1/reference_positions | 1024 | 9024 | yes | 0.091/0.092 | 0.023/0.013 | yes/yes |
| layout4_s1/listener_wall | 1024 | 6976 | yes | 0.147/0.150 | 0.025/0.024 | yes/yes |
| layout4_s1/listener_edge | 1024 | 5248 | yes | 0.174/0.217 | 0.024/0.042 | yes/yes |
| layout4_s1/listener_corner | 1024 | 3776 | yes | 0.202/0.210 | 0.027/0.029 | yes/yes |
| layout4_s1/emitter_wall | 1024 | 7616 | yes | 0.147/0.100 | 0.030/0.013 | yes/yes |
| layout4_s1/emitter_edge | 1024 | 6528 | yes | 0.153/0.108 | 0.023/0.013 | yes/yes |
| layout4_s1/emitter_corner | 1024 | 5248 | yes | 0.185/0.121 | 0.025/0.013 | yes/yes |
| layout4_s1/both_wall | 1024 | 12992 | yes | 0.575/0.110 | 0.069/0.024 | no/yes |
| layout4_s1/both_corner | 1024 | 4032 | yes | 0.456/0.233 | 0.904/0.031 | no/yes |
| layout4_s1/listener_absorber | 1024 | 9152 | yes | 0.136/0.136 | 0.028/0.031 | yes/yes |
| layout5_s1/reference_positions | 1024 | 4928 | yes | 0.091/0.084 | 0.023/0.018 | yes/yes |
| layout5_s1/listener_wall | 1024 | 28416 | no | 0.073/0.065 | 0.227/0.264 | no/no |
| layout5_s1/listener_edge | 1024 | 83648 | yes | 0.069/0.063 | 0.455/0.131 | no/no |
| layout5_s1/listener_corner | 1024 | 67776 | yes | 0.063/0.064 | 0.081/0.233 | yes/no |
| layout5_s1/emitter_wall | 1024 | 9728 | yes | 0.140/0.060 | 0.307/0.018 | no/yes |
| layout5_s1/emitter_edge | 1024 | 9344 | yes | 0.130/0.061 | 0.252/0.018 | no/yes |
| layout5_s1/emitter_corner | 1024 | 9024 | yes | 0.130/0.063 | 0.153/0.018 | no/yes |
| layout5_s1/both_wall | 1024 | 42496 | no | 0.306/0.054 | 0.174/0.264 | no/no |
| layout5_s1/both_corner | 1024 | 29184 | yes | 2.130/0.110 | 0.315/0.186 | no/no |
| layout5_s1/listener_absorber | 1024 | 12736 | yes | 0.113/0.155 | 0.071/0.294 | yes/no |

**Readings.**
1. **Layout 4 under (B):** every one-end case meets the floor (SE 0.09–0.22 dB, VOV ≤ 0.04), and so do the reference
   positions (0.09 dB). Under (A) these cases had SE 0.29–1.33 dB.
2. **Layout 5 under (B):**
   - SE falls to 0.06–0.15 dB in every one-end case.
   - The VOV part fails on the moved emitter in most of them (0.13–0.46), and on the unmoved one at the listener cases. The
     cause is the 1 024-history pilot's VOV, not the SE.
   - The reference positions meet the floor (0.09 / 0.08 dB).
3. **Both-near cases still fail under (B):** layout 4 both_wall 0.58 dB, both_corner 0.46 dB with VOV 0.90; layout 5
   both_corner 2.13 dB.
4. **(B) does not remove Seat 1's both-near residual.** It removes the long-window SE problem in the one-end cases. It
   exceeds the restore bound in every gated scene (C14 (c)), so it exists only with Challenge 1 "no".
