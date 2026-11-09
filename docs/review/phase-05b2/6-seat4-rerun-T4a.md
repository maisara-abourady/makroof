# Seat 4 (chain keeper) — re-run on 4a-2G+

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 4 POSITION (re-run): D-T4a = 4a-2G+ — **now 1 / later 2 as written; 1/1 if the two conditions below are added.**

| option | now | later | reason | condition (later 2 → 1) |
|---|---|---|---|---|
| 4a-2G+ | 1 | 2 (1 with condition) | With one instance, the gate adds no wait. Under 4b-2, every rebuild already contains a diffuse solve, and that already puts phase-08 item 8 out of reach: rebuild ≤ 24.3 ms at P = 512 (≤ 13.7 ms with AX31's extra partition) against a W1 of 20.6 ms before any diffuse work. The gate adds (n−1)·R_d of queueing per instance to every binaural update, including yaw changes under AX3. It does this in every output mode, and nothing records it per mode. | (1) From Phase 08 on, the (iv) records (1, 4 and 8 instances; staleness; time until the last instance is audible) are also taken in binaural mode, with the gate wait shown separately. (2) Phase 08 item 8 measures the update delay of a single isolated update with the gate wait included. It also records that the diffuse solve inside every rebuild, not the gate, is what breaks the 35 ms head-rotation row (Vorländer Table 15.1). If that row applies, the remedy is a Phase 10 AX that updates the specular and directional part without waiting for the diffuse solve (Table 15.1's separate rows for the specular part and the scattering part). The remedy is not a change to the gate. |

The cell is not a 3. A per-process FIFO gate that coalesces to the newest scene changes no output, so it costs no cue. Its whole cost is delay, and the conditions above make that delay measurable per output mode.

Evidence:
- The Table 15.1 rows (35 ms "new HRTF"; 700 ms and 3 s for the specular and scattering parts) are from the corpus (Vorländer ch. 15).
- The (13.7, 24.3] ms band and W1 = 20.6 ms are from AX31 and phase-08 item 8.
- The (n−1)·R_d queueing term is Seat 3's (`6-seat3-rerun2-T4a.md`).
- That item 8 fails whatever the gate does is [Inferred]: W1 already exceeds 13.7 ms before any diffuse solve is added.

Hand-off: whether Table 15.1's head-rotation row applies to yaw changes under AX3 when there is no head tracking stays with phase-08 item 8 (Seat 1 for the limit, Seat 5 for the measurement).

Read: `/home/user/makroof/docs/review/phase-05b2/10-decider-rebuttal-T5-T4.md` (D-T4a section, tension map, register).
