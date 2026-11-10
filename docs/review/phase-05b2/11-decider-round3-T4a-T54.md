# Decider — round 3 (D-T4a → 4a-2G++, D-T5.4 confirmed)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

# Decider: round 3 (D-T4a and D-T5.4 only)

D-T4a changes to 4a-2G++ (4a-2G+ plus Seat 4's two Phase 08 measurement conditions), worst-off 1, sum 17. D-T5.4 stands with Seat 6's cell now confirmed at 1/1. No veto-grade cell remains in any of the seven decisions; Challenge 1 still waits for Maisara.

Inputs this round: `6-seat4-rerun-T4a.md` and `6-seat6-rerun3-T54.md`. Corpus revision `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`.

**Naming.** I call the D-T4a variant **4a-2G++**, not "4a-2G+ made explicit". It adds Seat 4's two conditions, which are commitments for Phase 08, not wording already in 4a-2G+. Round 3 is a new round, so this is the round's one composed variant for D-T4a. It meets the rule: it lowers the maximum (2 → 1), and it raises no other seat. Its additions are records and a stated remedy route that only says what Phase 10 *may* propose, as an AX; it adopts nothing.

## D-T4a, final

**Tension map.** Bold marks cells updated in round 3. ᶜ = carried from 4a-2, not re-asked.

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 4a-1 | 0/2 | 2/2 | 1/2 | 1/1 | 1/1 | 1/2 | 2/2 | 1/2 | 2/2 | 2 | 27 |
| 4a-2 | 0/1 | 1/1 | 1/1 | 0/1 | 2/2 | 1/1 | 1/1 | 1/2 | 1/1 | 2 | 19 |
| 4a-3 | – | – | – | – | 3/3 | – | 1/3 | – | – | veto | – |
| 4a-2G+ as written | 0/1ᶜ | 1/1 | 1/1 (read from conditions) | **1/2** (rated) | 1/1 | 1/1 (read from conditions) | 1/1ᶜ | 1/1 | 1/1ᶜ | 2 | 18 |
| **4a-2G++** | 0/1ᶜ | 1/1 | 1/1 (read from conditions) | **1/1** (read from conditions: Seat 4 "1/1 if the two conditions below are added") | 1/1 | 1/1 (read from conditions) | 1/1ᶜ | 1/1 | 1/1ᶜ | **1** | **17** |

**Working.**
1. Veto: 4a-3 is out.
2. Worst-off: 4a-1, 4a-2 and 4a-2G+ all reach 2.
3. Composing 4a-2G++ brings the maximum down to 1.
4. **Decision: 4a-2G++.**

**DECISION D-T4a = 4a-2G++.** This is a working ceiling per instance at the largest AX6 room (100 m), at any supported sample rate, with both emitters. phase-13 scope 1 owns the actual budget.

- **(i) Transient memory.** One diffuse solve may use at most **1 GB**. At most one diffuse solve runs per process, through a gate that:
  - is JUCE-free;
  - is held only around the solve, never while holding `stateMutex_` or the builder mutex;
  - is used on the builder, synchronous and offline build paths, never in the realtime callback;
  - serves instances first come, first served (FIFO), one solve at a time;
  - lets a waiting instance keep coalescing, so it solves its newest scene when its turn comes;
  - never changes any output. The test is the same IRs with two pipelines in either order, plus TSan `[pipeline]` with two pipelines.
- **(ii) Resident memory.** At most **128 MB of additional** memory kept between rebuilds per instance, on top of the Phase 07 baseline (+122.6 MB at 96 kHz in the maximum room, Linux).
- **(iii) Gate wait is visible.** Time spent waiting at the gate counts in Phase 10's IR-staleness metric and drives the UI "settling" state.
- **(iv) Multi-instance records** (filed under D-T4c). With 1, 4 and 8 instances rebuilding together, in the AQ10 room and at 100 m, at 48 and 96 kHz, record:
  - per-instance staleness;
  - time until the last instance is audible at project load;
  - staleness when the instances are automated together.

  These are escalated against 1, 3 and 10 s. **From Phase 08 on**, they are also taken in binaural mode, with the gate wait shown separately (Seat 4 condition 1).
- **(v) Phase-08 item 8** (Seat 4 condition 2):
  - It measures the delay of one isolated update with the gate wait included.
  - It records that the diffuse solve inside every rebuild, not the gate, is what breaks the 35 ms head-rotation row of Vorländer Table 15.1.
  - If that row applies, the remedy is a Phase 10 AX that updates the specular and directional part without waiting for the diffuse solve (Table 15.1 gives specular and scattering parts separate rows). The remedy is not a change to the gate.
  - Whether the row applies to AX3 yaw changes without head tracking stays open in item 8 (Seat 1 for the limit, Seat 5 for the measurement).
- **Known gap:** Bitwig's per-plugin sandbox makes the transient count per instance.

**Register (later ≥ 1).** As in round 2, with S4's row replaced:

| seat | commits later phases to | undo | evidence | repaid when |
|---|---|---|---|---|
| S4 (read from conditions) | Binaural multi-instance records with the gate wait shown separately. Item 8 measured with the gate wait included. The 35 ms row is attributed to the diffuse solve; Seat 4 [Inferred]: "W1 already exceeds 13.7 ms before any diffuse solve is added". Remedy route: a Phase 10 split-update AX. | Phase 10 AX | phase-08 item 8 and the binaural (iv) records | Phase 08 / Phase 10 |

The other rows are unchanged:
- S1 and S9: D-T3 risk, which depends on D-T1.
- S2: the 128 MB cap rules out a mid-size kernel cache; lifting it is a parameter change in Phase 10/13.
- S3 and S6 (read from conditions): the multi-instance rules and records; the wait is made visible.
- S5: the Bitwig gap is accepted at 1.
- S7: what remains after the gate is the resident memory, not the 4 GB transient at project open.
- S8: the last room is heard later, but no work is lost.
- Interrogator 25: 128 MB additional resident × K10, plus the Bitwig case. K8–K10 stay unknown. The proposed phase-13 scope 3 RSS record would measure it.

**Strongest objection:** S1, S7 and S9 are still carried from 4a-2. A 3 from any of them would hand the decision to 4a-2. A 2 would not change the winner (18 against 19). **Confidence:** low.

## D-T5.4, final

**Map:** S1 1/1 · S2 1/1 · S3 1/1 · S4 0/1 · S5 1/1 · **S6 1/1 (confirmed, re-run 3; no longer pending)** · S7 1/1 · S8 1/1 · S9 1/1. Max 1, sum 17.

The decision text is unchanged from round 2:
- the generic outcome stands;
- a double-precision finite-floor check;
- the Phase 12 two-branch check: (a) single-scatter floor integral when all non-ground faces have α = 1, (b) the seeded tracer within ±1 dB otherwise;
- the ghost-tail reversal criterion.

S6's register row is now "Phase 12 two-branch check (confirmed)".

**Confidence:** medium (S3's earlier cell read from conditions was confirmed in round 2).

## Final summary (all seven ids)

| id | decision (exact) | state | worst-off (cell) | sum | confidence | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| D-T5.1 | 5.1-A* (round 2 text): specular + propagated diffuse in all 8 bands (Kuttruff Eq. 4.24 Lambert with the §5.2 split, Eq. 4.35, Eq. 4.29, AX4 air). RAII FTZ/DAZ in `buildRoomIR`; FTZ on/off builds bit-identical per platform. Tracer check at 125 Hz, 4 kHz and 8 kHz on layouts 4 and 5 at s = 1 before goldens. | stands (corrected) | 1 | 14 | medium | NFR-1, NFR-6/AX5 | Kuttruff §4.5, §5.2 | (ii) fails in a band |
| D-T5.2 | 5.2-A: k_real on specular + AX16 entries; AX22 unchanged | stands (corrected) | 1 | 14 | high | AX22 (settled) | Kuttruff §4.1–4.2 | no scheduled evidence |
| D-T5.3 | 5.3-D: specular-only axis shares, labelled; Phase 08 gets E_b and t_mix,e only; directional tail goes to the backlog behind a blind test | stands | S3 0/1 | 1 | high | NFR-6, NFR-8 | Kuttruff Eq. 4.29 | blind test passes |
| D-T5.4 | 5.4-A*: generic outcome; double-precision finite-floor check; Phase 12 two-branch check; ghost-tail reversal | stands (corrected) | 1 | 17 | medium | NFR-8, FR-SIM-6 | Vorländer §4.4.1, §1.5; C1 | ghost-tail criterion fires |
| D-T4a | 4a-2G++: as stated above | **revised (round 3)** | 1 (S1, S7, S9 carried) | 17 | low | NFR-2, AX6, phase-13 scope 1 | – | Phase 13 RSS, (iv) records, D-T1 peak at 100 m |
| D-T4b | 4b-2: W1/W2 include the whole diffuse computation, no cache credit; coupled to D-T4a (ii) | stands (corrected) | 1 | 13 | high | AQ10 | Table 15.1 (context) | Phase 10 cache AX, after D-T4a (ii) is reversed |
| D-T4c | 4c-1C: memory blocks on the larger of the two 100 m builds (AX22 fallback and non-fallback); time is recorded and escalated (1, 3, 10 s, with Table 15.1's conditions stated); contended-restore record; bounce-to-real-time ratio | stands (corrected) | S5 1/2 | 17 | medium | AQ10 (settled) | Table 15.1; F21 | Challenge 1 answer |

**NEEDS MAISARA (unchanged).** Challenge 1: should a CI gate on the 100 m, 96 kHz state restore become blocking? The limit would be 14 × t_restore under pluginval's 30 s watchdog, about 2.1 s per restore; today it is 1.51–1.88 s. Making it blocking amends AQ10. Her answer moves Seat 5 from 1/2 to 1/1 or leaves it as recorded debt.

**For Maisara (D-T4a, one line):** the 1 GB per-build ceiling is unchanged. Seat 4 gets binaural measurements of the multi-instance wait, and a recorded finding that the 35 ms head-turn update can only be met by a Phase 10 split update, not by changing the gate.

Files:
- /home/user/makroof/docs/review/phase-05b2/6-seat4-rerun-T4a.md
- /home/user/makroof/docs/review/phase-05b2/6-seat6-rerun3-T54.md
