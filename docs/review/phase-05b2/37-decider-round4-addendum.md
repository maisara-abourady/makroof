# Decider — addendum to the final round 4 (Seat 5 and Seat 6 confirmations)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

# Decider: addendum to the final round 4 (Seat 5 and Seat 6 confirmations)

Both pending confirmations came back at 1/1 once their conditions are folded in. Nothing else is reopened. D-T2 (Q1) and the work limits (Q2) still go to Maisara. Sources: `35-seat5-confirm-S5b.md`, `35-seat6-confirm-S6b.md`, `36-orchestrator-C16b.md`.

## D-T1.3: path count, pilot and cap (N-3W\*\*\*, block 64)

**Updated map row**

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| **N-3W\*\*\*** | **2/2** | 0/1 | 1/1† | 1/1 at n\*_max 1 024; 2/2 at 8 000 | **1/1 (confirmed, with (1)–(3))** | 1/1† | 1/1† | 1/1† | 1/1† | 2 | 19 at 1 024; 21 at 8 000 |

S5's cell is no longer read from conditions. Seat 5 rated block 64 "prefer, 1/1" itself, and its three conditions are now in the text. It did not ask for block 32.

**Added to the decision text (Seat 5)**
1. **Integer arithmetic.** The pilot stop test (2·W_pilot ≥ W_scene, or n ≥ n\*_max) and the cap N_cap = ⌊(W_scene − W_pilot)·n\* / W_pilot⌋ use 64-bit integers on evaluation counts, with no floating-point division. N_cap is then rounded down to whole 64-history blocks.
2. **Golden.** The per-case n\* and N go into the D5 golden beside the face-sequence hash, and must be equal on all three OSes.
3. **CI assertion.** At the gated scenes, CI asserts realised work / W_scene ≤ a pre-registered ratio (Seat 5 suggests about 1.05).
   - The ratio is set from C++ measurements of realised against planned work before the first CI run, and is not changed afterwards.
   - This turns the statistical bound into a checked one.

Strongest objection and reversal are unchanged. Seat 5's own premortem names the realised-work assertion as the guard against final-range cost scatter at small N (layout 4).

## D-T1.6: near-listener handling (NW-4C+, note U)

**Updated map row**

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| **NW-4C+** | 1/**2** | 1/1 | 1/1 | 0/1 | 1/1 | **1/1 at both n\*_max (confirmed)** | 1/1 | 1/1 | 1/1 | 2 | 18 |

Seat 6's ratings:
- at n\*_max 8 000: 1/1 as written;
- at n\*_max 1 024: 2/1 with the pilot-only VOV, and 1/1 with the union VOV (C16b passed its pre-stated test).

**Added to the decision text (Seat 6)**
1. **VOV leg of U.** The note's VOV is computed over the pilot plus the final range, up to the first 8 000 histories, at both pilot sizes.
   - The note does not feed the estimate, so the final range stays fresh (F14).
   - U = (both-near AND (cap hit OR VOV_union ≥ 0.1)) OR (cap hit AND achieved SE > 0.33 dB).
2. **Unmoved emitter (Seat 6's optional item, adopted).** When U is raised on an emitter the user did not edit, Phase 11's note names the scene, not that emitter, as the cause.

**Corrected "Where U fires" at n\*_max 1 024 (C16b)**
- Five good estimates go silent:
  - `club` both_wall_0.3 and both_wall_0.5;
  - `living_room` both_edge_0.3;
  - `club` both_edge_0.5;
  - W1 both_wall_0.3.
- Every case with capped SE > 0.33 dB still fires, and so does every heavy-tailed both-near case at 0.1 m.
- `living_room` both_wall_0.1 (SE about 0.07 dB) is the one good estimate flagged at both sizes.
- At 1 024, U now fires on the n\*_max 8 000 set minus W1 both_wall_0.3 and `club` both_edge_0.5.

**New computation, C16c (reported, not blocking).** Recompute C16 (f)'s U column at n\*_max 8 000 with the union VOV. Where the pilot stopped on work (n\* < 8 000), the union adds final-range histories, so U can change. Seat 6 re-confirms only if a default or one-end placement starts to fire. Its condition (ii) still governs.

## Q2b cost line (replaces the earlier one)
With the union VOV, the note behaves almost identically at both sizes. The choice no longer turns on the note; it turns on precision against rebuild time:

| | (i) n\*_max 1 024 | (ii) n\*_max 8 000 |
|---|---|---|
| Sized to | 25 ms of the 50 ms W1 target | fixed |
| Achieved SE at the Phase 04 default placements | 0.017–0.086 dB | 0.007–0.054 dB |
| Achieved SE in near-wall cases | up to 0.124 dB | ≤ 0.082 dB |
| W1 diffuse solve | ≤ 25 ms | about 0.25 s per rebuild (prototype, 1 thread) |
| Seat 4 | 1/1 | 2/2, unless an AX lets E_b refresh on a slower interval |
| Seat 6 | 1/1 | 1/1, and states a preference for 8 000 |

- Both are inaudible (≤ 0.12 jnd).
- Board maximum is 2 (Seat 1) either way.
- Sum is 19 at 1 024 and 21 at 8 000.

## /fix-plan additions (to the round-4 list)
- **D-T1.3 AX row**:
  - the integer stop test and N_cap formula (Seat 5 (1));
  - n\* and N in the D5 golden (Seat 5 (2));
  - block 64 confirmed.
- **phase-05b2 §5 acceptance:**
  - the CI realised-work assertion at a ratio pre-registered from C++ data before the first run (Seat 5 (3));
  - n\* and N equal on three OSes.
- **D-T1.6 AX row:** the VOV leg of U over pilot ∪ final range, up to the first 8 000 histories (Seat 6).
- **phase-11:** the unmoved-emitter wording (the note names the scene as the cause).
- **phase-05b2 §4:** C16c, reported only.
- **Ledger:** S5-b and S6-b closed at 1/1, and C16b recorded.

## Final summary

| id | decision | state | worst-off (cell) | sum | conf. | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| D-T1.1 | T1-F\* + D1–D7 (block 64), wording, cross-OS comparison | final | 1 (under Q1 (a)) | 18 | medium | NFR-1/2/6, AX5, AX6 | Kuttruff Eqs. 4.24, 4.29, 4.35, §5.2; Vorländer Fig. 11.38 | stage-2 estimator fail; hash mismatch |
| D-T1.2 | S-1 | final | 1 | 2 | high | NFR-6 | – | MC spread needed |
| D-T1.3 | N-3W\*\*\* (joint, block 64, integer cap, work pilot, CI lists, realised-work assertion) | final rule; W_max and n\*_max go to Q2 | S1 2/2 | 19 (21 at 8 000) | medium | NFR-1/2, AQ10, AX5 | Table 6.1 | Q2; n\*_max < 1 000; realised-work assertion fails |
| D-T1.4 | τ 0.25 dB; target SE 0.083 dB (achieved is higher where capped) | final | 1 | 9 | high | NFR-1 | Table 6.1 | ℓ_ref > τ/2 |
| D-T1.5 | 70 cases / 560 case-bands, z_FW 4.290, stage 2, CI reports | final | 1 | 4 | medium | NFR-1/8 | – | CI budget |
| D-T1.6 | NW-4C+; both-near diagnostic at 0.70 m; U with union VOV; Seat 6 (i)–(iii) and the unmoved-emitter wording | final | S1 1/2 | 18 | medium | NFR-1/8, FR-SIM-6 | Kuttruff Eq. 2.50, §8.7 | U at a default; reference > τ; C16c |
| D-T2 | – | NEEDS MAISARA (Q1) | L2-F1R S5 2/3 | – | – | AX36 | – | her ruling |
| Work limits | W_max (Q2a), n\*_max (Q2b) | NEEDS MAISARA (Q2) | S1 2/2; S4 2/2 if n\*_max is 8 000 | – | – | AQ10 | – | her ruling |
| D-T6 | RS-2+ / B6-1F / M-2 + Seat 7 (i)–(iii) | final | 1 | 7 | medium | NFR-1 | Table 6.1 | stage-2 fail |
| D-T3 | – | not needed | – | – | – | AX6 | – | – |

**For Maisara, the only change from round 4.** On Q2b, the "approximate" note now behaves the same at both small-room limits. The choice is only slightly better precision at 8 000 (Seat 6's preference) against rebuilds that fit the 50 ms target at 1 024 (Seat 4's need).

Files:
- /home/user/makroof/docs/review/phase-05b2/35-seat5-confirm-S5b.md
- /home/user/makroof/docs/review/phase-05b2/35-seat6-confirm-S6b.md
- /home/user/makroof/docs/review/phase-05b2/36-orchestrator-C16b.md
- /home/user/makroof/docs/review/phase-05b2/34-decider-round4-final-T1-T2-T6.md
