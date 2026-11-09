# Decider — rebuttal round 2, D-T5 and D-T4

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

# Decider: rebuttal round 2 on D-T5 and D-T4 (phase 05b session 2)

D-T4a is revised to a new composed variant, 4a-2G+, at worst-off 1. Every other decision stands with the interrogator's corrections applied. One item still needs Maisara: the AQ10 amendment on the 100 m state-restore time (Challenge 1, unchanged).

**Corpus revision:** `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`.

**Read for this round:**
- `8-interrogator-T5-T4-round1.md`
- the re-runs `6-seat2/3/5/6/8-rerun-T5-T4.md`, `6-seat3-rerun2-T4a.md` and `6-seat6-rerun2-T4a.md`
- `docs/phases/phase-12.md` (L25–36, L57, L65)
- `docs/phases/phase-13.md` (L44–51)
- `7-builder-D-T1-evidence.md` was not read.

## State of each decision

| id | interrogator | state after this round |
|---|---|---|
| D-T5.1 | survives with corrections | **stands**; corrections 04, 05, 06 applied |
| D-T5.2 | survives with corrections | **stands**; correction 09 applied (Q5) |
| D-T5.3 | survives | **stands**, unchanged |
| D-T5.4 | survives with corrections | **stands**; corrections 16, 17, 18 applied (Q2); 19 is a fix to the C1 file |
| D-T4a | **TENSION MISREAD** | **revised: 4a-2G → 4a-2G+**; corrections 20, 22–25 applied (Q1, Q3) |
| D-T4b | survives with corrections | **stands**; correction 27 and the coupling note applied |
| D-T4c | survives with corrections | **stands**; corrections 28, 29, 31 applied (Q4) |

---

## Answers to the interrogator's questions (most consequential first)

### Q1. D-T4a: Seats 3 and 6 rate 4a-2G

I accept the TENSION MISREAD. In round 1 I carried S3 and S6 over from 4a-2 without a rating and without a mark, and the register reasons I gave for S3, S4 and S6 were not their words.

Both seats have now rated it:
- **Seat 3** (`6-seat3-rerun2-T4a.md`): **1/2**.
  - Later 2: with n instances rebuilding together, the last one waits about (n−1)·R_d, so its staleness is about 2R + 2P + (n−1)·R_d. Phase 10's gates use single-instance scenarios.
  - To 1/1 with: a record of per-instance staleness with 1, 4 and 8 instances rebuilding together (AQ10 room and 100 m, 48 and 96 kHz); and two rules: (a) a waiting instance keeps coalescing and solves its newest scene; (b) the gate serves in arrival order (FIFO).
- **Seat 6** (`6-seat6-rerun2-T4a.md`): **1/2**.
  - Later 2: at a worst-case solve the queue reaches seconds; the staircase grows with instance count and nothing on the canvas shows why.
  - To 1 with: (1) FIFO fairness at solve granularity; (2) gate wait counted in Phase 10's IR-staleness metric and driving the UI "settling" state; (3) under 4c-1C, records with 4 and 8 instances of the time until the last instance is audible at project load and of the staleness when instances are automated together, escalated against 1 / 3 / 10 s.

That puts 4a-2G at max 2, the same as 4a-2. I compose this round's one variant for D-T4a, **4a-2G+** (4a-2G plus both seats' conditions). It brings max back to 1 (tension map below). Neither seat rated a 3, so 4a-2 does not win.

### Q2. D-T5.4: `courtyard`, the reversal condition, and precision

- **Reference for `courtyard`.** The single-scatter ground estimate is a reference only when every non-ground face has α = 1. Kuttruff Eq. 4.28 keeps the re-radiation term ρB otherwise. `courtyard` has 4 hard walls (phase-12 L36), so the Phase 12 check is restated with two branches:
  - (a) Presets whose non-ground faces all have α = 1 (the `open_field` class): the diffuse E_target is compared with the finite-floor single-scatter window integral.
  - (b) All other outdoor presets (`courtyard`, a stage shell): E_target is compared with the independent Kuttruff §9.8 tracer (`tools/acoustics/tracer.py`, seeded) within the B11 window tolerance of ±1 dB. This is the same independent check the 15 (A) cases passed; the tracer treats an open face as α = 1 like any other face.
  - Both branches are reported, not tuned.
  - Seat 6's 5.4-A* later cell rested on the old wording, so it is now marked "read from conditions, pending re-confirmation". If Seat 6 returns 2, the winner is unchanged: 5.4-A* (18) still beats 5.4-A (19) and 5.4-B (28), as the interrogator verified.
- **Reversal condition, restated as a ghost-tail criterion.** It fires only when the independent reference (the tracer, or the branch (a) integral) puts the energy after t_mix,e more than 60 dB below the direct sound, while the rendered tail after t_mix,e is within 60 dB of it. In other words, the reference says the field has ended and the IR still carries a tail in the audible range. Real reverberation such as `courtyard`'s slap echoes (phase-12 L65) has reference energy within 60 dB after the handover, so it does not fire. The 60 dB line is Seat 9's end-of-decay convention, applied by extension.
- **Precision.** The diffuse path's window sums and E_target are computed and serialised in **double** (the orchestrator confirms every candidate prototype does this). FTZ/DAZ flushes only values below the normal range of the type in use. C1's smallest value, 1.19e−41 at 8 kHz, is a normal double (the double normal minimum is about 2.2e−308), so it survives under FTZ. The log-domain check runs on the double E_target written by `--diagnostics`. Any band where the reference falls below 1e−300 is compared as an absolute bound instead of in log; no C1 band comes near that.
- **Inaudibility claim, with the interrogator's conditions.** The tail's whole energy is ≥ 104 dB below the direct sound at 63 Hz (≥ 90 dB for the open boxes). With the direct 63 Hz band at or below 104 dB SPL (90 dB SPL for open boxes), the tail energy is below 0 dB SPL, under the mid-frequency threshold (Vorländer §1.5, Table 1.2), and the threshold rises steeply at low frequencies (Fig. 6.2). Above those direct levels the claim is not checkable without an LF threshold value. Seat 1's −80 dB floor stays [Hyp].
- **C1 file typo (ledger 19).** C1's prose says "−152 dB at 1 kHz"; the table gives −166.0 dB (−151.9 dB is 500 Hz). The orchestrator should correct the C1 file. My decisions used the table.

### Q3. D-T4a: does anything measure K8–K10, and where is multi-instance RSS?

- **None of the D-T4c records measures K8, K9 or K10.** They measure only this plugin's time and memory. The round-1 sentence is struck. K8 (customer RAM), K9 (other plugins' memory) and K10 (instances per project) stay declared unknowns, and no in-repo measurement can produce them.
- **No phase-13 item measures multi-instance RSS.** Scope 1 measures memory per instance; the scope 3 10-instance test records only the CPU sum (phase-13 L51). Proposed /fix-plan wording for phase-13 scope 3:

  > The 10-instance test also records peak process RSS and the per-instance resident delta, on all three OSes; and, with a 100 m scene, once with all instances in one process and once under Bitwig's per-plugin sandbox, where the transient counts per instance.

- **New debt row:** 128 MB of additional resident memory × K10, plus the Bitwig sandbox case.

### Q4. D-T4c: is the gated 100 m build in the AX22 fallback?

Yes, and both cases are measured.
- The memory gate runs two 100 m, 96 kHz, 2-emitter builds. One is a generic scene in the AX22 fallback for both emitters (t_cap ≈ 2.1 s, about 2 100 bins); the benchmark asserts the fallback triggered, as AQ10's W2 does. The other is a closed low-α 100 m cube without the fallback, Seat 9's cost-worst closed box.
- The gate applies to the larger peak of the two; both times are recorded.

This carries Seat 2's re-run condition, so S2 stays 1/1 on 4c-1C.

### Q5. D-T5.2: which scheduled test would show a k_real over-trigger?

None. k_real is tested only at the expected-rule t_mix,e, and i₀ does not enter it. The Phase 13 i₀ re-derivation changes N_cap and t_cap, not the trigger, and no phase file holds a listening test on a high-s flutter scene. The debt is marked **"no scheduled evidence"**. It reopens only if a later phase or Maisara schedules such a test, which would be an AX22 change through /fix-plan. The register now has one row per seat, S6's included.

---

## Final decisions

### D-T5.1 = 5.1-A* (stands)

**Map** (corrections do not change cells): S1 1/1 · S2 1/1 · S3 1/1 · S4 0/1 · S5 1/1 (confirmed in Seat 5's re-run) · S6 1/1 · S7 1/0 · S8 0/0 · S9 1/1. Max 1, sum 14. 5.1-C is vetoed (S2, 3 now); even without the veto its max is 2.

**Decision text.**

E_target,b is the window-referred specular entries plus the window-referred propagated diffuse energy, in all 8 bands:
- At each specular hit, s(1−α) of the incident energy is injected into the Lambert patch hit. The scattered/specular split is Kuttruff §5.2 (and §2.7); the diffuse re-radiation is Lambert's law, Eq. 4.24.
- Transport per Eq. 4.35 with the §5.2 split; gather per Eq. 4.29; AX4 air.
- Same Hann window, Eyring referral and t_mix,e as today. This equals `ref_hybrid.target_hybrid`.
- The AX16 E_target stays computed and reported in diagnostics.

Conditions:
- **(i) FP mode.**
  - `buildRoomIR` sets FTZ/DAZ on entry through a scoped (RAII) guard that restores the caller's mode on every exit, including a throw (AX34).
  - Window sums and E_target are in double.
  - A `[pipeline]` test builds an absorbent room, asserted to produce denormals without FTZ, with the caller's FTZ on and off. It requires the IRs to be **bit-identical on each of the three CI platforms** (AX5, same platform).
- **(ii) Outer-band tracer check.** The tracer window check at 125 Hz, 4 kHz and 8 kHz on Table 5.2 layouts 4 and 5 at s = 1, within ±1 dB, is reported before any golden is updated. A failing band goes to D-T2 and to Maisara with numbers, never back to AX16.
- **What (ii) does and does not test.** These layouts have band-independent α, so (ii) differs from the validated check only through air, exp(−mR) (Kuttruff §4.5). It tests the AX4 regime at 4–8 kHz and nearly repeats the in-band check at 125 Hz.

**Register (corrected).**

| seat | debt | evidence arrives | repaid when |
|---|---|---|---|
| S4, S9 | the outer bands checked only via air | (ii), this session | (ii) passes |
| S1 | 63 Hz "wrong under any geometric method" | none scheduled | not repaid by (ii) |
| S1, S2, S4 | band-varying α outside 500 Hz–2 kHz has no tracer evidence | D-T1's agreement test (model vs model) and D-T2's outer-band ℓ ladder; neither is a tracer | no scheduled independent evidence |
| S3 | Phases 08–10 inherit the switched E_b | Phase 08/10 goldens | at those phases |
| S5 | the FP test kept as a permanent gate | `[pipeline]` CI | permanent |
| S6 | patch-boundary steps under automation | Phase 10 scope 6 | Phase 10 |

**Confidence:** medium. **Reversal:** (ii) fails in a band.

### D-T5.2 = 5.2-A (stands)

**Map:** S1 0/1 · S2 1/1 · S3 1/1 · S4 0/1 · S5 0/1 · S6 1/1 · S7 1/1 · S8 0/1 · S9 1/1. Max 1, sum 14.

**Decision text.** k_real, `needsIsmFallback` and t_mix,e are computed exactly as today, from the specular + AX16 scattered entries. The AX16 list is kept only for this test and for diagnostics. AX22 is unchanged.

**Register (one row per seat, in their words).**

| seat | debt | evidence |
|---|---|---|
| S1 | "k_real rests on a level model known to be wrong (AX16)" | **no scheduled evidence** |
| S2 | the AX16 list survives for this decision only; "only an AX22 change could fix the over-trigger, and nothing forces one now" | **no scheduled evidence** |
| S3 | "the jump point stays where it is in position space"; Phase 10's inputs ρ and f now come from the switched E_b | Phase 10 gates |
| S4 | existing debt: at the jump point interaural coherence changes as well as band energy; "Phase 10's gate measures band energy only" | Phase 10 (band energy only) |
| S5 | "an AX16 list kept alive only for this test" | none needed |
| S6 | "s still steers the fallback through AX16 entries that no longer set the level. That coupling is invisible to the user" | **no scheduled evidence** |
| S7 | "can't be deleted until AX22 is revisited" | **no scheduled evidence** |
| S8 | "a counter list kept only to count" | none needed |
| S9 | "may over-trigger the fallback … a later AX22 matter" | **no scheduled evidence** |

**Confidence:** high. **Reversal:** only if a test of the over-trigger is scheduled and shows one.

### D-T5.3 = 5.3-D (stands, unchanged)

- `bandsAxisShares` is computed from the specular entries in the window only, with today's per-entry definition, labelled "specular entries only". It is not gated.
- Phase 08 receives E_b and t_mix,e per emitter through `TailMatch`, and no directions.
- The phase-05b2 §3 phrase "(used for directional output in Phase 08)" is corrected.
- If the session splits, Phase 08 may go before 05h on Seat 4's conditions (i)–(iv).
- A directional late tail goes to the backlog behind Seat 1's blind-test protocol, in Seat 4's 2×2 covariance form.
- **Register:** S3, later 1 (the diagnostic no longer matches k_real's list).

### D-T5.4 = 5.4-A* (stands, corrected)

**Map:** S1 1/1 · S2 1/1 · S3 1/1 (confirmed) · S4 0/1 · S5 1/1 · **S6 1/1 (read from conditions, pending re-confirmation on the restated Phase 12 check)** · S7 1/1 · S8 1/1 · S9 1/1. Max 1, sum 17. If S6 returns 2: max 2, sum 18, still the winner.

**Decision text.**
- **No rule:** `open_field` gets whatever the generic model gives.
- **Tests replaced** through the golden process: the asserts "E_b = 0" and `bandsNonZeroEntries` = 0 in `test_hybrid_ir.cpp` L234–261 and `test_tail.py::test_open_field_has_no_tail`.
- **New check:** the double diffuse E_target from `--diagnostics` against an independent finite-floor (100×100 m) single-scatter window integral (Hann weight, Eyring referral; it does not import `ref_hybrid`). Compared in the log domain, or as an absolute bound below 1e−300, to D-T1's tolerance.
- **Kept checks:** E_b finite and ≥ 0; energy later than t_dir + 50 ms below −60 dB (C1 margin > 44 dB).
- **Golden:** `phase04_open_field_omni` is updated only through `update_goldens.py`, after confirming every "no late energy" sentinel sits ≥ 10 dB from 60 dB on every OS.
- **Phase 12 gains** (via /fix-plan): each outdoor preset is checked with branch (a) or branch (b) as stated under Q2, reported, not tuned.

**Register (all nine, later 1).** As in round 1, with two changes:
- S6's row is now "the Phase 12 two-branch check".
- The S2/S8 rows now use the ghost-tail criterion.
- Evidence arrives at Phase 12.

**Confidence:** medium. **Reversal:** the ghost-tail criterion fires on any outdoor preset or generic open box.

### D-T4a = 4a-2G+ (revised)

**Tension map (cells updated this round in bold).**

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 4a-1 | 0/2 | 2/2 | 1/2 | 1/1 | 1/1 | 1/2 | 2/2 | 1/2 | 2/2 | 2 | 27 |
| 4a-2 | 0/1 | 1/1 | 1/1 | 0/1 | 2/2 | 1/1 | 1/1 | 1/2 | 1/1 | 2 | 19 |
| 4a-3 | 0/0 | 0/1 | 2/2 | 1/2 | 3/3 | 1/2 | 1/3 | 2/2 | 0/1 | veto | – |
| 4a-2G | 0/1ᶜ | 1/1 (confirmed) | **1/2** (rated) | 0/1ᶜ | 1/1 (confirmed) | **1/2** (rated) | 1/1ᶜ | 1/1 (confirmed) | 1/1ᶜ | 2 | 18 |
| **4a-2G+** | 0/1ᶜ | 1/1 | **1/1 (read from conditions: S3's "with these the rating is 1/1")** | 0/1ᶜ | 1/1 | **1/1 (read from conditions: S6 "later 2 → 1")** | 1/1ᶜ | 1/1 | 1/1ᶜ | **1** | **16** |

ᶜ = carried from 4a-2, not re-asked:
- The interrogator found the gate bears on the measures of S3 and S6.
- S1's lag concern sits under its (c) ratings.
- S7 proposed a process-wide serialiser in its own 4a-3 condition.
- S9 says time is "not my matter".
- **S4 is the open risk.** Its measure includes per-mode update delay (phase-08 item 8). If S4 rated 4a-2G+ later 2, the max would be 2 and 4a-2G+ (17) would still beat 4a-2 (19). Only a 3 from S4 would change the winner to 4a-2.

**Working.**
1. Bounds: all in bounds.
2. Veto: 4a-3 is dropped.
3. Worst-off: 4a-1, 4a-2 and 4a-2G all at 2.
4. Composition: 4a-2G+ meets both new conditions. It raises no seat: Seat 5's re-run already requires the gate around the solve only, and Seat 7 and Seat 8 asked for serialisation themselves. Max 1.
5. Sum: 16.

**DECISION D-T4a = 4a-2G+.** Working ceiling per instance at the largest AX6 room (100 m per side), any supported sample rate, both emitters. Cross-reference: phase-13 scope 1 owns the budget.
- **(i) Transient memory.** One diffuse solve uses ≤ **1 GB**. At most one diffuse solve runs at a time per process, through a JUCE-free gate:
  - the gate is held only around the solve, never while holding `stateMutex_` or the builder's mutex;
  - it is taken on the builder, synchronous and offline build paths, never in the realtime callback;
  - it serves waiting instances in arrival order (FIFO) at solve granularity;
  - a waiting instance keeps coalescing and solves its newest scene when its turn comes;
  - gate order never changes any output (each solve depends only on its own scene). Test: the same IRs with two pipelines in either order, plus TSan `[pipeline]` with two pipelines.
- **(ii) Resident memory.** **Additional** resident memory kept between rebuilds ≤ **128 MB** per instance, beyond the Phase 07 baseline measured in CI (+122.6 MB at 96 kHz, maximum room, Linux).
- **(iii) Gate wait is visible.** Time spent waiting at the gate counts in Phase 10's IR-staleness metric and drives the UI "settling" state (via /fix-plan to phase-10 and to the UI phase).
- **(iv) Records** (under D-T4c): with 1, 4 and 8 instances rebuilding together (AQ10 room and 100 m, 48 and 96 kHz), per-instance staleness, the time until the last instance is audible at project load, and staleness when the instances are automated together (position and room size). They are escalated against 1 / 3 / 10 s.
- **Known gap:** Bitwig's per-plugin sandbox defeats a per-process gate; there the transient counts per instance (Seat 5 accepts this at 1).

**Load-bearing claims.**
- D4-L1 and D4-L2: checked CORRECT (dense kernel 3–6 TB; 80.6 MB per band per emitter, 161 MB for both emitters; t_cap ≈ 2.10 s).
- D4-L3 (from the code): builders run per instance.
- D4-L4: DAW floors (Live 12 8 GB, FL 4 GB) and new MacBooks ≥ 16 GB are known. K8–K10 are declared unknowns, and nothing scheduled measures them.

**Register (in the seats' words).**

| seat | commits later phases to | undo | evidence | repaid when |
|---|---|---|---|---|
| S1 | "Same risk [Hyp], depending on D-T1" (a D-T3 level step under room-size automation) | D-T3 route | D-T1's measured peak at 100 m | D-T1/D-T3 settled |
| S2 | "if Phase 10 proposes a kernel cache for mid-size rooms (≈ 0.47 GB) the 128 MB cap rules it out" | parameter change via a Phase 10 AX and the Phase 13 budget | Phase 10 | Phase 10 |
| S3 (read from conditions) | the multi-instance staleness record and rules (a)/(b) | builder rework | the (iv) records, this session | when recorded |
| S4 | no reason stated for this cell (Seat 4's 4a-2: "prefer. Now 0, later 1") | – | Phase 08 per-mode W1/W2 | Phase 08 |
| S5 | gate held around the solve only; Bitwig gap accepted at 1 | – | TSan two-pipeline test | this session |
| S6 (read from conditions) | the FIFO gate; wait shown in Phase 10's staleness metric and the UI settling state | builder rework in Phase 10/13 | (iv), Phase 10 | Phase 10/UI phase |
| S7 | "Four stems rebuilding at once on project open is about 4 GB … tight on 8 GB machines [Hyp]"; the transient part is now counted once, the resident part remains | Phase 13 budget | proposed phase-13 multi-instance RSS record | Phase 13 |
| S8 | "a delay before the last instance's room is heard … loses no work" | – | (iv) | this session |
| S9 | "The D-T3 risk depends on D-T1." | D-T3 route | D-T1 | D-T1 |
| (interrogator 25) | 128 MB additional resident × K10, plus the Bitwig case; K8–K10 unknown | Phase 13 budget | proposed phase-13 scope 3 RSS addition (Q3) | Phase 13 |

**Strongest objection.** S4's carried cell (see the sensitivity under the map). Second: the S3 and S6 cells are read from conditions, although both seats state the resulting rating explicitly.

**Confidence:** low. **Reversal:** Phase 13 RSS, the multi-instance records, or D-T1's measured peak at 100 m above (i) or (ii).

### D-T4b = 4b-2 (stands, corrected)

**Map:** max 1, sum 13 (unchanged).

**Decision text.**
- AQ10 is unchanged.
- W1/W2 include the whole diffuse computation, with no cache credit. Unit-decay generation stays excluded, as AQ10's Phase 10 proxy already does.
- Also recorded: full rebuilds at the AQ10 room, CR4 and 100 m, at 48 and 96 kHz; from Phase 08, W1/W2 per output mode with the diffuse share shown separately.

**Correction 27.** phase-05b2 §9 excludes only "Phase 10 caching beyond what D-T1 needs", and D-T1 (a) explicitly includes a cached room kernel. So D-T1 must not read W1/W2 under 4b-2 as what candidate (a) would ship.

**Coupling (ledger 32):**
- Seat 2's 4a-2G+ cell relies on 4b-2.
- 4c-1C's memory block relies on 4a-2G+'s ceiling.
- D-T4b's reversal (Phase 10 adopts a kernel cache) requires reversing D-T4a (ii) first.
- **If D-T1 chooses a cached-kernel candidate, D-T4a (ii) and D-T4b reopen together.**

**Register:** S1–S8 later 1, as in round 1. **Confidence:** high.

### D-T4c = 4c-1C (stands, corrected)

**Map:** S1 1/1 · S2 1/1 (condition now carried, Q4) · S3 1/1 · S4 0/1 · **S5 1/2** · S6 1/1 · S7 1/1 · S8 1/1 · S9 0/1. Max 2 (S5), sum 17. 4c-2 is out of bounds (AQ10); 4c-3 is vetoed.

**Decision text.**

*Blocks:*
- the peak working-set delta of the two gated 100 m, 96 kHz, 2-emitter builds (AX22 fallback for both emitters, and a closed low-α cube without fallback), taking the larger, above D-T4a's ceiling. Gated on Linux; recorded on macOS and Windows until Phase 13. A miss sends that range to D-T3.
- the existing gates: allocation tracker; TSan `[conv],[pipeline]`, including two pipelines; pluginval strictness 10 on three OSes and auval; bit-identical builder, offline and `render_cli` output on each platform; no NaN/Inf/denormals.

*Records:*
- W1/W2;
- full rebuilds at 48 and 96 kHz for the six Phase 04 rooms, the AQ10 room, CR4 and both 100 m cases;
- the AQ4 intervals (R + 2P, about 2R + 2P, full rebuild + 2P) against 100 ms, 700 ms and 3 s;
- synchronous restore time at 100 m and 96 kHz, alone and **contended** (a second pipeline solving the 100 m room at the same time; Seat 5), with the pluginval silent stretch (14 × t_restore against the 30 s default watchdog);
- the offline-bounce time of a 3-minute room-size automation at 100 m, 48 and 96 kHz, **with its ratio to real time** (Seat 8);
- callback p99.9 at host buffer 64 with 1, 4 and 8 concurrent builders;
- the D-T4a (iv) multi-instance records.

*Escalation:* the D-T1 packet to Maisara carries these numbers against 1 s and 10 s (Card et al. 1991, visual-UI conditions) and 3 s. Any room above 3 s is named as a finding. The packet states that **Table 15.1's 3 s row covers only translational movement > 1 m, derived from 30–50 cm/s VR movement, and has no row for room-geometry or material edits**; it is applied to full rebuilds by extension only.

*Hand-offs:* to the UI phase and Phase 10, the "settling" state and stepwise room-size automation at large rooms; to the UI phase, Seat 6's note not to show the nominal Eyring T60 as an open field's reverb time.

**Register:** S5 later 2 (synchronous restore and prepare at 100 m are ungated; repaid only by Challenge 1); S1–S4 and S6–S9 later 1, as in round 1.

**Confidence:** medium.

---

## Summary

| id | decision | state | worst-off seat (cell) | sum | confidence | reversal condition |
|---|---|---|---|---|---|---|
| D-T5.1 | 5.1-A*: all 8 bands; RAII FTZ/DAZ, per-platform bit-identity; tracer check at 125 Hz / 4 kHz / 8 kHz | stands (corrected) | 1 | 14 | medium | (ii) fails |
| D-T5.2 | 5.2-A: k_real on the AX16 entries, AX22 unchanged | stands (corrected) | 1 | 14 | high | no scheduled evidence |
| D-T5.3 | 5.3-D: specular-only shares; Phase 08 gets E_b and t_mix,e | stands | S3 0/1 | 1 | high | blind test passes |
| D-T5.4 | 5.4-A*: generic; double-precision finite-floor check; Phase 12 two-branch check; ghost-tail reversal | stands (corrected) | 1 (S6 pending) | 17 (18 if S6 = 2) | medium | ghost-tail criterion fires |
| D-T4a | 4a-2G+: 1 GB transient, one FIFO-gated coalescing solve per process; 128 MB additional resident; gate wait visible; multi-instance records | **revised** | 1 (S4 carried) | 16 | low | Phase 13 RSS, (iv) records, D-T1 peak |
| D-T4b | 4b-2: no cache credit (coupled to D-T4a (ii)) | stands (corrected) | 1 | 13 | high | Phase 10 cache AX, after D-T4a (ii) reverses |
| D-T4c | 4c-1C: memory blocks at the larger of the fallback and non-fallback 100 m builds; time recorded and escalated | stands (corrected) | S5 1/2 | 17 | medium | Challenge 1 answer |

## NEEDS MAISARA
- **Challenge 1 (unchanged; the interrogator confirmed the arithmetic and the ruling).** Should a CI gate on the synchronous state restore at 100 m and 96 kHz become a block? It would require 14 × t_restore under pluginval's 30 s watchdog, about 2.1 s per restore; today's figure is 1.51–1.88 s. It amends her AQ10 rule "full rebuilds recorded, not budgeted". Yes lowers Seat 5 to 1/1; no leaves Seat 5 at 1/2 as recorded debt. No veto-grade override is pending.
- **Proposed /fix-plan additions for her to see:**
  - phase-13 scope 3: multi-instance RSS record, including the Bitwig sandbox case;
  - phase-12: the outdoor-preset two-branch check;
  - phase-10 and the UI phase: gate wait counted in the staleness metric and driving the settling state;
  - phase-05b2 §3: the Phase 08 wording correction.

## For Maisara
- **D-T5:** unchanged in substance. The tail level comes from the validated model in all 8 bands, the fallback test is untouched, Phase 08 gets level and handover time only, and outdoor scenes get an inaudible residue. The checks are now stated precisely.
- **D-T4a:** still a 1 GB temporary ceiling per build, one build at a time per process. Instances now wait in order and always build their newest scene; the wait shows as "settling" in the UI; and the multi-instance delays are recorded and sent to you. Seats 3 and 6 had flagged waits that grow with instance count, and they get these conditions.
- **D-T4c:** memory blocks, now tested on the worst-case 100 m scene; time is recorded and escalated. Your one question remains the 100 m restore-time gate (Challenge 1).

Files:
- /home/user/makroof/docs/review/phase-05b2/8-interrogator-T5-T4-round1.md
- /home/user/makroof/docs/review/phase-05b2/6-seat3-rerun2-T4a.md
- /home/user/makroof/docs/review/phase-05b2/6-seat6-rerun2-T4a.md
- /home/user/makroof/docs/review/phase-05b2/6-seat2-rerun-T5-T4.md
- /home/user/makroof/docs/review/phase-05b2/6-seat5-rerun-T5-T4.md
- /home/user/makroof/docs/review/phase-05b2/6-seat8-rerun-T5-T4.md
- /home/user/makroof/docs/review/phase-05b2/2-orchestrator-C1-open-field.md
- /home/user/makroof/docs/phases/phase-12.md
- /home/user/makroof/docs/phases/phase-13.md
