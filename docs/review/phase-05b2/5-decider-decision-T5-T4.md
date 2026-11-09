# Decider — decision round, D-T5 and D-T4

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

# Decider: decision round for D-T5 and D-T4 (phase 05b session 2)

D-T5 is decided at worst-off 1 in all four parts. D-T4 is decided with worst-off 1 for memory and time reading and 2 for blocking (Seat 5 later), with one AQ10 challenge for Maisara.

**Corpus revision:** `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`.

**PRD digest:** unchanged from `docs/review/phase-05b2/1-decider-convene-T5-T4.md`. The hard constraints in play here are NFR-1, NFR-2, NFR-6/AX5, NFR-8, FR-SIM-6, AX6, AQ4, AQ10, AX22, the phase-05b2 §1 settled list, phase-05b scope 0, and phase-13 scope 1.

**Inputs read:**
- `3-seat1…9-T5-T4.md`
- `4-researcher-T5-T4.md`
- `2-orchestrator-C1-open-field.md`
- `2-orchestrator-C2-dLb-all-bands.md`
- Corpus re-reads: Vorländer §4.4.1 (L1656–1658) and Table 15.1 (L3959–3966); Kuttruff Eq. 4.29 (L2375–2377) and §5.2 (L2500ff).
- Code: `ScenePipeline.cpp` L306–323; `tests/state/parameter_ids_v1.json`.
- `7-builder-D-T1-evidence.md` was **not** read.

**Rule I apply and expose:** each numbered sub-question is its own decision id (D-T5.1–5.4, D-T4a–c). So the "at most one composed variant per round" rule applies per id. The interrogator may contest this.

---

## D-T5: how the switch interacts with the matching

### Knowledge inventory

| id | item | source | status |
|---|---|---|---|
| K1 | Validated combination: specular entries plus diffuse window term; t_mix,e and fallback from k_real on specular + AX16 entries | from the code: `ref_hybrid.py` L502–533; report-phase05b §5 | known |
| K2 | Outer bands (63–250 Hz, 4–8 kHz) | C2 (committed `phase05_scope6.json`) | known for AX16 vs hybrid: up to 3.83 dB, 41/425 case-bands > 1 dB. Under-informed against the tracer (no tracer run outside 500 Hz–2 kHz). Load-bearing only through 5.1-A*'s added check. |
| K5 | `bandsAxisShares` is diagnostic only; Phase 08 reads E_b and t_mix,e only | from the code (NoiseTail.cpp L234–244, Cli.cpp L484); phase-08 item 5 | known |
| K6 | Eq. 4.29 gathers along dS′→P | Kuttruff §4.5 L2375–2377 | known |
| K7 | Audibility of late-field anisotropy | researcher F25 (read); F26–F28 (read, loudspeakers); F29–F31 (unverified) | known with conditions: only F25 is binaural with a generic HRTF (kick drum, extreme absorbing wall, N = 9; speech not audible). Ill-informed for music under product conditions. |
| K9 | `open_field` under 5.1-A | C1 (two independent evaluations agree within SE) | known |
| K10 | Eyring assumes homogeneous α and a diffuse field | Vorländer §4.4.1 L1658 | known |
| K11 | FP-environment split between the offline build and the builder thread | from the code, per Seat 5 (PluginProcessor L166/181, ScenePipeline L400–402, IrBuilderThread L29) | known (Seat 5's code citation; not independently re-read) |

### D-T5.1: what E_target is built from

**Tension map (now/later).** 5.1-C is excluded: Seat 2 rates it a 3. The table shows 5.1-C, 5.1-A, and my composed variant 5.1-A*.

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 5.1-C | 2/2 | **3**/2 | 2/2 | 2/2 | 1/2 | 2/2 | 1/2 | 2/2 | 2/2 | 3 | – |
| 5.1-A | 1/1 | 1/1 | 1/1 | 0/1 | 1/**2** | 1/1 | 1/0 | 0/0 | 1/1 | 2 | 15 |
| **5.1-A\*** | 1/1 | 1/1 | 1/1 | 0/1 | 1/1 (read from conditions) | 1/1 | 1/0 | 0/0 | 1/1 | 1 | 14 |

Seats' reasons for 5.1-A, cell by cell:
- **S1:** validated only at 500 Hz–2 kHz; extending to other bands is mild.
- **S2:** same equations in all 8 bands; the tracer and ℓ certification cover 500 Hz–2 kHz only. Later: an outer-band failure is fixed by a finer ℓ (a D-T2 rung).
- **S3:** the seam moves by −ΔL_b; Phases 08–10 inherit E_b; undoing costs one golden round.
- **S4:** both modes read the same E_b; later, validated only at 500 Hz–2 kHz.
- **S5:** later 2 = the FP-environment hazard breaks offline = real-time.
- **S6:** level right, decay stays Eyring; later, patch-boundary steps under drags.
- **S7:** one model in all 8 bands.
- **S8:** removes up to +3.87 / −1.17 dB of reverb-ratio error.
- **S9:** same physics in every band; a 4–8 kHz failure is a parameter fix.

The 5.1-C veto is Seat 2's: a ≈ 3.9 dB tone-colour step at 250/500 Hz and 2/4 kHz in the rooms the switch exists for. C2 confirms that AX16's outer-band error is as large as the inner one.

**Working.**
1. Bounds: keeping AX16 or blending it is dropped (convening).
2. Veto: 5.1-C is dropped (S2 now 3).
3. Worst-off: 5.1-A has max 2 (S5 later).
4. Composition: **5.1-A\*** = 5.1-A plus two additions.
   - Seat 5's condition: `buildRoomIR` sets FTZ/DAZ itself on entry and restores the caller's mode on exit (`sim/conv/Denormals.h`); window sums accumulate in double; a `[pipeline]` test builds an absorbent room with the caller's FTZ on and off and requires bit-identical IRs on three OSes. Seat 5's own words: "later 2 → 1".
   - Seat 9's proviso for keeping its 1: a tracer window check outside 500 Hz–2 kHz before the goldens are frozen.

   No seat objects to either addition, so no cell rises. Max falls to 1.
5. Sum: 14.

**DECISION D-T5.1 = 5.1-A\*.** The AX text to record:

> E_target,b = the window-referred specular entries + the window-referred propagated diffuse energy, in all 8 bands. The diffuse energy is injected as s(1−α) at each specular hit (Kuttruff Eq. 4.24), transported per Eq. 4.35 with the §5.2 split, gathered per Eq. 4.29, with AX4 air. Same Hann window, same Eyring referral, same t_mix,e. This equals `ref_hybrid.target_hybrid`. The AX16 E_target stays computed and reported in diagnostics (scope 3).
>
> Conditions:
> - (i) Seat 5's FP condition above.
> - (ii) A tracer window check at 125 Hz, 4 kHz and 8 kHz on Table 5.2 layouts 4 and 5 at s = 1, against the B11 window tolerance (±1 dB). It is reported before any golden is updated. A failing band goes to D-T2 (finer ℓ for that band) and to Maisara with numbers. It never returns to AX16 (5.1-C is vetoed).

Seat 1's acceptance tests (before/after ΔG, ΔC80, ΔEDT, ΔT30 and the seam step, reported) are handed to D-T6's convening; they are not part of this decision.

**Load-bearing claims.**
- **D5-L1 (code).** `target_hybrid` = `target_specular` + `window_target(diffuse)` on the `phase04_plan` plan (L522–533). This is the combination validated within 0.08 dB (report §5; 500 Hz–2 kHz, 15 cases, one AX28 pair each).
- **D5-L2 (computed, C2).** AX16 vs hybrid reaches 3.83 dB in the outer bands, the same as inside. Keeping AX16 there therefore keeps a known error of full size (the veto basis).
- **D5-L3 (code, Seat 5).** The offline build runs under `ScopedNoDenormals`; the builder thread and `render_cli` set no FP mode. This is the basis of condition (i).

**Future-debt register (D-T5.1).**

| seat | commits later phases to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| S1, S4, S9 | an E_b validated against the tracer only at 500 Hz–2 kHz | a per-band ℓ rung or parameter change | condition (ii), this session | (ii) passes |
| S2 | outer-band ℓ certification | a D-T2 rung | D-T2 extended to 8 bands | D-T2 certifies all bands |
| S3 | Phases 08–10 inherit the switched E_b | one golden round | Phase 08/10 goldens | at those phases |
| S5 (read from conditions) | the FP-mode test kept forever | low | `[pipeline]` CI, three OSes | permanent gate |
| S6 | patch-boundary steps under drags and room-size sweeps | D-T1 continuity check | Phase 10 scope 6 | Phase 10 |

**Strongest objection.** The S5 cell is read from Seat 5's condition text. If Seat 5 judges that the test does not cover the builder's use of `render_cli`, it stays 2 and 5.1-A* is still the only survivor at max 2.

**Confidence:** medium (one cell read from conditions; no tracer data outside 500 Hz–2 kHz yet).

**Reversal condition:** (ii) fails in any band, or D-T1's agreement test fails outside 500 Hz–2 kHz (this session).

### D-T5.2: what the AX22 k_real test counts

**Tension map.** 5.2-B and 5.2-C are out of bounds (AX22 is settled), and no seat rated 5.2-A a 3.

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| **5.2-A** | 0/1 | 1/1 | 1/1 | 0/1 | 0/1 | 1/1 | 1/1 | 0/1 | 1/1 | 1 | 14 |

Seats' reasons:
- **S1:** no audible change; later, k_real rests on a model known to be wrong.
- **S2:** keeps t_mix,e as validated; the over-trigger in parallel-wall rooms with high s already exists (E10).
- **S3:** the jump point does not move; Phase 10's method is unchanged.
- **S4:** the existing jump-point coherence debt remains.
- **S5:** zero added cost; later, the AX16 list is kept only for this test.
- **S6:** an invisible coupling of s to the fallback.
- **S7:** the AX16 list cannot be deleted until AX22 is revisited.
- **S8:** nothing new is audible.
- **S9:** may over-trigger the fallback; a later AX22 matter.

**DECISION D-T5.2 = 5.2-A.** k_real, `needsIsmFallback` and t_mix,e are computed exactly as today, from the specular + AX16 scattered entries. The AX16 list survives only for this test and for diagnostics. AX22 is unchanged.
- D5-L4 (product): AX22 is settled (phase-05b2 §1).
- D5-L5 (code): `planEmitter` fixes t_mix,e before matching (Engine.cpp L121–148), so the diffuse horizon is known before the solve. Candidate (d) keeps its linearity (phase-05b2 D-T1 (d)).

**Debt register (all nine seats, later 1).**
- The AX16 list is kept alive.
- k_real over-triggers in high-s parallel-wall rooms (S2, S9). Evidence arrives at Phase 13's i₀ re-derivation or from a listening result on a high-s flutter scene. Undoing needs an AX22 change through /fix-plan.
- At the jump point the interaural coherence changes, not only the band energy (S4). This is Phase 10's gate.

**Confidence:** high. **Reversal:** the evidence above shows an over-trigger.

### D-T5.3: `bandsAxisShares` and what Phase 08 receives

**Tension map.** 5.3-C is excluded: Seat 4 rates it later 3.

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 5.3-A | 1/1 | 1/1 | 0/1 | 0/1 | 0/1 | 0/1 | 0/1 | 0/1 | 1/1 | 1 | 12 |
| 5.3-B | 0/1 | 2/2 | 1/2 | 1/1 | 1/2 | 0/1 | 2/2 | 0/1 | 1/1 | 2 | 21 |
| 5.3-C | 2/2 | 2/2 | 2/2 | 2/**3** | 2/2 | 2/2 | 2/2 | 1/2 | 2/2 | 3 | – |
| **5.3-D** | 0/0 | 0/0 | 0/1 | 0/0 | 0/0 | 0/0 | 0/0 | 0/0 | 0/0 | 1 | 1 |

- Seat 4's veto on 5.3-C: a delivery feature adopted on a formula with no listening evidence; a window distribution applied to the whole tail; and frozen by NFR-6.
- Seat 3's 5.3-D later 1: it changes a reported number and breaks consistency with k_real.

**Working.** 5.3-D and 5.3-A tie at max 1; 5.3-D wins on sum (1 against 12). No composition is needed, since the max is already 1.

Does the new evidence matter? F25 qualifies Seats 3 and 9's statement that there is "no evidence" of audibility. It would not lift 5.3-C: Seat 2's wrong-time-segment objection (window directions are not the late field's, E6b, E7) and Seat 4's NFR-6 objection are independent of F25, and 5.3-C's maximum without the veto would still be 2 against 5.3-D's 1.

**DECISION D-T5.3 = 5.3-D.**
- `bandsAxisShares` is computed from the specular entries in the window only, with today's per-entry definition (NoiseTail.cpp L234–244). It is labelled "specular entries only" in the diagnostics and the header. It is not gated.
- Phase 08 receives E_b (switched) and t_mix,e per emitter through `TailMatch`, and no tail directions. phase-08 item 5 is unchanged.
- The phase-05b2 §3 phrase "(used for directional output in Phase 08)" is corrected through /fix-plan.
- §8 split rule: if the session splits, the loop records why Phase 08 may go before 05h, on Seat 4's conditions (i)–(iv):
  - (i) E_b and t_mix,e are read only via `TailMatch`;
  - (ii) parity is checked within the same build;
  - (iii) 05h re-renders the binaural goldens, re-measures binaural W1/W2 and re-runs phase-08 item 8;
  - (iv) the Phase 08 listening items on concentrated absorption are marked provisional.
  - This rests on Seat 4, the owning seat. Seat 7's 5.3-C reason (it delays binaural) supports it. The other seats did not rate it.
- A directional late tail becomes a backlog item, entered only after a blind test passes:
  - Seat 1's protocol: Phase 08 binaural, generic HRTF, layouts 4 and 5 at s = 1, pink bursts and voice, 12 or more of 16 trials correct;
  - Seat 4's form: a per-band 2×2 ear covariance;
  - grounds: F25.

**Load-bearing claims.**
- **D5-L6 (code / plan):** the shares have no consumer (K5).
- **D5-L7 (researcher F25, read):** the only binaural generic-HRTF result is a kick drum in an extreme case, with no effect for speech.

**Debt register:** S3. The diagnostic no longer matches k_real's list. Undo is a one-line change. Repaid when a reader needs AX16-entry shares (none today).

**Confidence:** high. **Reversal:** the blind test above passes.

### D-T5.4: `open_field`

**Tension map.** Both 5.4-A and 5.4-B carry a 2 (5.4-B's S2 cell is 1/1 with an exact-zero criterion); the table shows 5.4-A, 5.4-B and my composed variant 5.4-A*.

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 5.4-A | 1/1 | 1/1 | 1/**2** | 0/1 | 1/1 | 1/**2** | 1/1 | 1/1 | 1/1 | 2 | 19 |
| 5.4-B | 1/2 | 2/2 | 2/2 | 1/1 | 1/2 | 1/2 | 2/2 | 1/1 | 1/2 | 2 | 28 |
| **5.4-A\*** | 1/1 | 1/1 | 1/1 (read from conditions) | 0/1 | 1/1 | 1/1 (read from conditions) | 1/1 | 1/1 | 1/1 | 1 | 17 |

Where the cells come from:
- **S3, later 2:** smaller open boxes have a milder referral, so a "ghost tail" there could be audible. Seat 3's condition (→1): C1 also computes a smaller box, and Seat 1 judges the onsets inaudible. The C1 addendum gives open boxes of 864–9000 m³ ≥ 90 dB below the direct sound. Seat 1's stated floor is −80 dB [Hyp].
- **S6, later 2:** semi-open presets. Condition (→1): the independent single-scatter ground estimate becomes a check on every outdoor preset in Phase 12.
- **Conditional vetoes that are not triggered:**
  - Seat 8 (→3 if C1 shows an audible tail): not triggered, C1 gives ≤ −104 dB.
  - Seat 6 (→3 if audible): not triggered.
  - Seat 9 (stays 1 if the tail is ≥ 60 dB below the direct sound after 0.5 s): met, by more than 44 dB.

**DECISION D-T5.4 = 5.4-A\*.**
- **No rule:** `open_field` gets whatever the generic model gives.
- **Tests replaced** through the golden process: the "E_b = 0 / `bandsNonZeroEntries` = 0" asserts in `test_hybrid_ir.cpp` L234–261 and `test_tail.py::test_open_field_has_no_tail`.
- **New check:** the diffuse E_target per band from `--diagnostics` against an independent single-scatter window integral over the **finite** 100×100 m floor (not the infinite-plane default of `ground_scatter.py`; it does not import `ref_hybrid`), in the log domain, to D-T1's tolerance.
- **Kept checks:** E_b finite and ≥ 0, and the existing "energy later than t_dir + 50 ms below −60 dB" check, which C1 shows holds by more than 44 dB.
- **Golden:** `phase04_open_field_omni` is updated only through `update_goldens.py`, after confirming that every "no late energy" sentinel sits ≥ 10 dB from 60 dB on every OS (Seat 5).
- **Phase 12 gains** (Seat 6's condition): each outdoor preset's energy after the handover is checked against an independent single-scatter ground estimate and reported, not tuned.

**Load-bearing claims.**
- **D5-L8 (computed, C1):** the whole tail is −104 dB re direct at 63 Hz and −166 dB at 1 kHz, starting at 1.404 s. Two independent evaluations agree within SE. Open boxes stay ≥ 90 dB below.
- **D5-L9 (corpus):** Eyring assumes homogeneous α and a diffuse field (Vorländer §4.4.1). So the tail's shape is non-physical; its level makes that harmless.

**Debt register (all nine seats, later 1).**
- S1: the check is consistency, not audibility.
- S2, S8: a 5.4-B-like rule if a semi-open preset contradicts C1.
- S3: ghost-tail shape (read from conditions).
- S4: an isotropic tail for a half-space field, to be recorded as a Phase 08 limit.
- S5: two tests and one golden replaced.
- S6: the Phase 12 preset check (read from conditions).
- S7: outdoor churn risk.
- S9: the artefact sits below audibility.
- Evidence arrives at Phase 12 preset listening and checks. Undo: an exact-zero rule (5.4-B), at parameter level.

**Strongest objection.** The S3 cell depends on Seat 1's −80 dB floor, which is a hypothesis. Even if that floor were wrong by 10 dB, C1 still has more than 10 dB of margin.

**Confidence:** medium (two cells read from conditions).

**Reversal:** a Phase 12 outdoor or semi-open preset whose tail after the handover is within 60 dB of the direct sound.

---

## D-T4: cost budget (formulation-neutral)

### Knowledge inventory

| id | item | source | status |
|---|---|---|---|
| K1 | AQ10 definitions; full rebuilds recorded, not budgeted | BUILD_PLAN AQ10 | known |
| K2 | +122.6 MB RSS (Linux only); full rebuild 603–802 ms (48 kHz), 1509–1884 ms (96 kHz) | §0 row 07 | known (RSS under-informed for macOS and Windows) |
| K4 | W1 > 700 ms → Phase 10 Table 15.1 remedy; a coarser ℓ is not a remedy | phase-05b scope 0 | known |
| K5 | Table 15.1 (700 ms, 3 s) is a "proposal" derived from VR movement speeds | Vorländer L3957–3966; F24 | known |
| K6 | Dense kernel 3–6 TB at 100 m | phase-05b2 §0.3 | known |
| K7 | One builder thread per instance; synchronous builds on prepare, restore and offline | from the code (IrBuilderThread L29; ScenePipeline L271, L322 re-read, L400–402) | known |
| K8 | RAM in producers' machines | F1 (Live 12 min 8 GB), F4 (FL 4 GB), F7 (new MacBooks ≥ 16 GB) | **declared unknown** for the distribution: researcher reports no source exists |
| K9 | Per-instance memory of comparable plugins | none (F10–F14 give system figures only) | **declared unknown** |
| K10 | Instances per project | F15 (Izhaki, qualitative only) | **declared unknown** as a count |
| K11 | pluginval default watchdog 30 s (inactivity over the whole run); restore loop once per automatable parameter, silent; auval and DAWs document no limit | F16–F20 | known |
| K12 | 0.1 / 1 / 10 s response-time constants | F21 (Card 1991, read) | known, for visual-UI conditions |

**Why K8–K10 do not block a working ceiling.**
- phase-13 scope 1 (settled) owns the memory *budget*. D-T4 sets only a working ceiling (phase-05b2 §3).
- The chosen variant is built so its transient part does not depend on K10: one diffuse solve in flight per process.
- Its resident part per instance is of the order of the Phase 07 baseline that already ships.
- The in-repo measurements that close K8–K10 for Phase 13 are listed under D-T4c.

The interrogator may disagree. If so, D-T4a becomes RESEARCH NEEDED, and the research question is those measurements, not literature.

### D-T4a: memory ceiling

**Tension map.** 4a-3 is excluded: Seat 5 rates it 3/3 and Seat 7 later 3.

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 4a-1 | 0/2 | 2/2 | 1/2 | 1/1 | 1/1 | 1/2 | 2/2 | 1/2 | 2/2 | 2 | 27 |
| 4a-2 | 0/1 | 1/1 | 1/1 | 0/1 | **2/2** | 1/1 | 1/1 | 1/**2** | 1/1 | 2 | 19 |
| 4a-3 | 0/0 | 0/1 | 2/2 | 1/2 | **3/3** | 1/2 | 1/**3** | 2/2 | 0/1 | 3 | – |
| **4a-2G** | 0/1 | 1/1 (read from conditions) | 1/1 | 0/1 | 1/1 (read from conditions) | 1/1 | 1/1 | 1/1 (read from conditions) | 1/1 | 1 | 16 |

**Working.**
1. Veto: 4a-3 is dropped.
2. Worst-off: 4a-1 and 4a-2 tie at max 2.
3. Composition: **4a-2G** = 4a-2 plus Seat 5's condition (2/2 → 1/1): a process-wide gate allowing one diffuse solve in flight per process; resident memory between rebuilds ≤ 128 MB per instance; callback p99.9 recorded under concurrent builders.
   - This also meets Seat 8's condition (serialise concurrent builds → later 1). Seat 3 itself proposed serialisation in its 4a-3 condition.
   - S2 is read as 1/1: its 4a-1 → 1 condition is "a ceiling ≥ 2·N·T·4 B ≈ 161 MB plus headroom", and 4a-2G allows a 1 GB transient. The only residue of its 4a-1 reason ("rules out any resident cache") is the 128 MB resident cap, which also matters less under 4b-2 (no cache credit).
   - S6, S7, S9 are carried from 4a-2: the added terms were not addressed by them.

**DECISION D-T4a = 4a-2G.** Working ceiling per instance at the largest AX6 room (100 m per side), any supported sample rate, both emitters:
- (i) peak **transient** memory of one diffuse solve ≤ **1 GB**, with at most one diffuse solve in flight per process (a JUCE-free process-wide gate; taken only on builder, synchronous and offline build paths, never in the realtime callback);
- (ii) **resident** memory kept between rebuilds ≤ **128 MB** per instance.
- Cross-reference: phase-13 scope 1 sets the real budget; these numbers are its input, not its outcome.
- Known gap: Bitwig's per-plugin sandboxing defeats a per-process gate (Seat 5), so the transient then counts per instance.

**Load-bearing claims.**
- **D4-L1 (plan):** the dense kernel is 3–6 TB at 100 m, so it is over every ceiling.
- **D4-L2 (derived from phase-05b2 §0.3):** 9 600 × 2 100 × 4 B = 80.6 MB per band per emitter, so 161 MB for one band and two emitters. A per-patch-history class fits 1 GB band-group-wise, and a Monte-Carlo tally is O(bins). Memory alone does not force D-T3. The class memories are [Hyp] until D-T1 measures them.
- **D4-L3 (code):** builders are per instance, so without the gate transient peaks add across instances.
- **D4-L4 (researcher):** DAW floors are 8 GB (Live 12) and 4 GB (FL). New MacBooks have ≥ 16 GB. K8–K10 are declared unknowns.

**Debt register (all later 1).**
- S1, S9: the D-T3 risk depends on D-T1.
- S2 (read from conditions): the resident cap limits caches.
- S3: serialised builds lengthen update intervals when several instances rebuild together.
- S4: binaural headroom.
- S5 (read from conditions): gate and recording kept.
- S6: D-T3 risk.
- S7: several stems at project open are tight on 8 GB machines.
- S8 (read from conditions): session-level peak.
- Evidence arrives at D-T1's measured peak at 100 m (this session) and Phase 13's three-OS multi-instance RSS. Undoing is a parameter change before release.

**Strongest objection.** S2's cell is read from conditions. If Seat 2 rates the 128 MB resident cap a 2, the max returns to 2 and the choice falls back to 4a-2 against 4a-1 on sum (19 against 27). 4a-2 would still win. I ask the interrogator to have Seat 2 confirm in the next round.

**Confidence:** low (declared unknowns; three cells read from conditions).

**Reversal:** Phase 13 memory per instance and the multi-instance test, or D-T1's measured peak at 100 m above (i)/(ii).

### D-T4b: how W1/W2 are read

**Tension map.**

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 4b-1 (as offered) | 0/1 | **2/2** | 1/1 | 0/1 | 1/**2** | 0/1 | 0/1 | 0/1 | 0/0 | 2 | 14 |
| **4b-2** | 0/1 | 1/1 | 1/1 | 1/1 | 0/1 | 0/1 | 1/1 | 1/1 | 0/0 | 1 | 13 |

- S2 rates 4b-1 at 1 only "with conditions" it lists (cache built and tested this session, horizon covering the fallback, cold = warm bit-identical); the option as offered does not include them, hence 2/2.
- Composing 4b-1 would not lower the max below 4b-2's 1, and it would bring a cache into scope that phase-05b2 §9 puts out of scope.

**DECISION D-T4b = 4b-2.**
- AQ10 is unchanged: 50 ms target, recorded.
- W1/W2 include the whole diffuse computation, with no cache credit. Unit-decay generation stays excluded, as AQ10's Phase 10 proxy already does.
- Credit comes only when Phase 10 adopts a kernel cache through an AX.
- Also recorded:
  - full-rebuild time at the AQ10 room, CR4 and the 100 m room, at 48 and 96 kHz;
  - from Phase 08, W1/W2 per output mode with the diffuse share shown separately (Seat 4).

**Debt register (later 1: S1–S8).** It overstates the interval and may trigger the Table 15.1 remedy early. It measures something that does not ship if a cache is adopted (S4). Reversible through an AX. Evidence arrives at Phase 10.

**Confidence:** high. **Reversal:** Phase 10 adopts a kernel cache.

### D-T4c: what blocks and what is recorded

**Tension map.** Bounds and vetoes:
- 4c-2 is dropped at bounds: it amends AQ10's "full rebuilds are recorded, not budgeted" (accepted by Maisara 2026-11-05). It would not have helped anyway: its max is 2 (S6 later, S7 now, S9 later).
- 4c-3 is excluded: Seat 5 later 3, Seat 7 later 3.

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 4c-1 | 1/1 | 1/2 | 1/2 | 0/1 | 1/**2** | 2/2 | 1/1 | 1/2 | 0/1 | 2 | 22 |
| **4c-1C** | 1/1 | 1/1 (read from conditions) | 1/1 (read from conditions) | 0/1 | 1/**2** | 1/1 (read from conditions; its own 4c-1E) | 1/1 | 1/1 (read from conditions) | 0/1 | 2 | 17 |

**Composition 4c-1C** = 4c-1 plus the conditions of Seats 2, 3, 6 (4c-1E), 7 (report variant) and 8. Seat 5's condition is not met in its blocking form; see the challenge below. Its contents:
- **Blocks:**
  - peak working-set delta of a 100 m, 96 kHz, 2-emitter build above D-T4a's ceiling (gated on Linux; recorded on macOS and Windows until Phase 13), which sends the formulation to D-T3 for that range;
  - the existing gates: allocation tracker, TSan `[conv],[pipeline]` with the diffuse builder, pluginval strictness 10 on three OSes and auval, bit-identical builder/offline/`render_cli` output (D-T5.1 (i)), no NaN/Inf/denormals.
- **Records:**
  - W1/W2;
  - full rebuild at 48 and 96 kHz for the six Phase 04 rooms, the AQ10 room, CR4 and 100 m;
  - the implied AQ4 intervals (R + 2P isolated, about 2R + 2P continuous, full rebuild + 2P) against 100 ms, 700 ms and 3 s;
  - the synchronous restore time at 100 m and 96 kHz, and the derived pluginval silent stretch (14 parameters × t_restore against the 30 s default watchdog);
  - the offline-bounce time of a 3-minute room-size automation at 100 m, at 48 and 96 kHz;
  - callback p99.9 at host buffer 64 with 1, 4 and 8 concurrent builders.
- **Escalation:** the D-T1 decision packet to Maisara carries these numbers against 1 s and 10 s (F21, visual-UI conditions stated) and 3 s (Table 15.1). Any room above 3 s is named as a finding.
- **Hand-off to the UI phase and Phase 10:** a visible "settling" state while a long rebuild is pending; room-size automation at large rooms documented as stepwise.

**DECISION D-T4c = 4c-1C.** Worst-off: Seat 5, later 2, in its own words: nothing gates the synchronous paths (state load, prepare, pluginval restores) at the largest room.

**Load-bearing claims.**
- **D4-L5 (plan):** AQ10's no-budget rule for full rebuilds.
- **D4-L6 (researcher F16–F18, code):** pluginval's 30 s inactivity watchdog; restores are silent and synchronous (ScenePipeline L306–323); 14 parameters (`parameter_ids_v1.json`). That allows about 2.1 s per restore. Today's 100 m, 96 kHz full rebuild is 1.51–1.88 s (§0 row 07).
- **D4-L7 (corpus):** Table 15.1 is a proposal (F24).

**Debt register.**
- S5 (later 2): the synchronous restore and prepare at the largest room are ungated. Undo is a CI gate plus an AQ10 amendment. Evidence arrives at the first recorded restore time after D-T1. Repaid if Maisara accepts Challenge 1.
- S1–S4, S6–S9 (later 1): unbounded full-rebuild lag that is recorded, not blocked (S2 and S3 read from conditions). Evidence arrives at D-T1's numbers and Phase 10's room-size sweep.

**Strongest objection.** Seat 5's later 2. It holds because the only way to lower it is to budget full-rebuild time, which is Maisara's settled AQ10. The grounding is also weak: pluginval loads the plugin's own states, not a 100 m cube (F18), and no DAW documents a limit (F20).

**Confidence:** medium. **Reversal:** Maisara's answer to Challenge 1, or a recorded 100 m restore above about 2.1 s.

---

## Summary

| id | decision (exact wording) | state | worst-off seat (cell) | sum | confidence | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| D-T5.1 | 5.1-A*: specular + propagated diffuse in all 8 bands; FTZ/DAZ in `buildRoomIR` + bit-identity test; tracer check at 125 Hz / 4 kHz / 8 kHz (layouts 4 and 5, s = 1) before goldens | proposed | several at 1 | 14 | medium | NFR-1, NFR-6 | Kuttruff Eqs. 4.24, 4.29, 4.35, §5.2 | (ii) fails in a band |
| D-T5.2 | 5.2-A: k_real on specular + AX16 entries, AX22 unchanged | proposed | 1 | 14 | high | AX22 (settled) | Kuttruff §4.1–4.2 | over-trigger evidence (Phase 13) |
| D-T5.3 | 5.3-D: shares from specular entries, labelled; Phase 08 gets E_b and t_mix,e only; directional tail to backlog behind a blind test | proposed | S3 (0/1) | 1 | high | NFR-6, NFR-8 | Kuttruff Eq. 4.29; F25 | blind test passes |
| D-T5.4 | 5.4-A*: generic outcome; finite-floor integral check; −60 dB check kept; Phase 12 outdoor preset check | proposed | 1 | 17 | medium | NFR-8, FR-SIM-6 | Vorländer §4.4.1; C1 | preset tail within 60 dB |
| D-T4a | 4a-2G: ≤ 1 GB transient per diffuse solve, one solve per process; ≤ 128 MB resident per instance; at 100 m | proposed | 1 (S2 read from conditions) | 16 | low | NFR-2, AX6, phase-13 scope 1 | – | Phase 13 or D-T1 measurement |
| D-T4b | 4b-2: W1/W2 include the whole diffuse computation, no cache credit | proposed | 1 | 13 | high | AQ10 | Table 15.1 (context) | Phase 10 cache AX |
| D-T4c | 4c-1C: memory blocks, time recorded and escalated (1 / 3 / 10 s) | proposed | S5 (1/2) | 17 | medium | AQ10 (settled) | Table 15.1; F21 | Challenge 1 answer |

## Challenges to settled decisions
1. **AQ10, "full rebuilds recorded, not budgeted" (Maisara, 2026-11-05).** Seat 5 asks for a CI gate on the synchronous restore and prepare at 100 m, 96 kHz: 14 × t_restore must stay under pluginval's 30 s default watchdog (F16–F18), which allows about 2.1 s per restore. Today's 100 m full rebuild at 96 kHz is 1.51–1.88 s. Accepting would lower Seat 5 to 1. The grounding is thin: no DAW limit is documented (F20), and pluginval does not itself load a 100 m state. **Maisara's call.**
2. **Plan text, not a settled decision.** phase-05b2 §3 D-T5 (3) says the shares are "used for directional output in Phase 08". The code and phase-08 item 5 show they are not. To be corrected through /fix-plan with D-T5.3.

No conflict between board.md §1 and the PRD was found.

## For Maisara
- **D-T5.1:** the tail level switches to the validated model in all 8 bands. The band-split variant was vetoed by Seat 2 for its tone-colour seam. Seat 5 gets a determinism guard (FP mode set inside the build), and the outer bands get a tracer check before any golden changes.
- **D-T5.2:** the fallback test stays exactly as today. All seats carry a small debt: a counting list kept alive, and a possible over-trigger that Phase 13 checks.
- **D-T5.3:** Phase 08 gets only the tail level and the handover time; there is no directional tail. Seat 4 vetoed the directional option. A directional tail stays a backlog idea behind a blind test, since one study (kick drum, extreme room) suggests it can be audible.
- **D-T5.4:** `open_field` gains a mathematically non-zero tail that is more than 100 dB below the direct sound (inaudible). Tests now check it against an independent ground integral, and outdoor presets get the same check in Phase 12.
- **D-T4a:** up to 1 GB of temporary memory per build, one diffuse build at a time per process, and at most 128 MB kept per instance at the 100 m room. Seat 5 gave the most (it wanted ≤ 128 MB overall) and gets the process-wide gate. Producer RAM is an unknown that Phase 13 measures.
- **D-T4b:** rebuild time is measured including the whole diffuse computation, with no cache credit.
- **D-T4c:** memory over the ceiling blocks; time is recorded and escalated to you with the numbers. You are asked one question: should a 100 m state-restore time limit (about 2.1 s, from pluginval's 30 s watchdog) become a CI block? That amends your AQ10. Seat 5 is the worst-off seat here at 2 until you decide.

Files:
- /home/user/makroof/docs/review/phase-05b2/3-seat1-T5-T4.md … 3-seat9-T5-T4.md
- /home/user/makroof/docs/review/phase-05b2/4-researcher-T5-T4.md
- /home/user/makroof/docs/review/phase-05b2/2-orchestrator-C1-open-field.md
- /home/user/makroof/docs/review/phase-05b2/2-orchestrator-C2-dLb-all-bands.md
- /home/user/makroof/src/plugin/core/ScenePipeline.cpp
- /home/user/makroof/tests/state/parameter_ids_v1.json
