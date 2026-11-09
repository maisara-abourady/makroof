# Interrogator — decision mode, round 1, D-T5 and D-T4

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

## Interrogator: decision mode, phase 05b session 2, D-T5.1–5.4 and D-T4a–c

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (14 files present).

**Read:**
- `docs/review/phase-05b2/` files 1, 2 (C1 and C2), 3 (seats 1–9), 4 and 5, plus the five re-runs in 6;
- `.claude/agents/decider.md` §4–§5; BUILD_PLAN AQ10 and AX22; phase-05b2 §3, §8 and §9; phase-12; phase-13;
- code: `ScenePipeline.cpp` L255–412, `Engine.cpp` L112–151, `NoiseTail.cpp` L207–251, `Denormals.h`, `ref_hybrid.py` L495–539, `parameter_ids_v1.json`;
- corpus: Kuttruff §4.5 (Eqs. 4.24–4.36), Eq. 4.6, §2.7 / notation L229, §5.2, Table 5.2; Vorländer §1.5 (Table 1.2), §4.4.1, §6.2.1 (Fig. 6.2), §15.2–15.3 (Table 15.1).

### Verdicts

| id | outcome |
|---|---|
| D-T5.1 (5.1-A*) | **SURVIVES WITH CORRECTIONS** |
| D-T5.2 (5.2-A) | **SURVIVES WITH CORRECTIONS** |
| D-T5.3 (5.3-D) | **SURVIVES** |
| D-T5.4 (5.4-A*) | **SURVIVES WITH CORRECTIONS** |
| D-T4a (4a-2G) | **TENSION MISREAD** |
| D-T4b (4b-2) | **SURVIVES WITH CORRECTIONS** |
| D-T4c (4c-1C) | **SURVIVES WITH CORRECTIONS** |

### Process checks that pass

- **Convening.** All nine seats were convened on both matters, and every sub-question was rated by all nine. Not underconvened.
- **Tension maps.** I rebuilt every as-offered cell of every map from the seats' own words. All of them match:
  - 5.1-A/C, 5.2-A, 5.3-A/B/C/D, 5.4-A/B;
  - 4a-1/2/3, 4b-1/2, 4c-1;
  - the vetoes: S2 on 5.1-C (3 now), S4 on 5.3-C (3 later), S5 and S7 on 4a-3, S5 and S7 on 4c-3.
- **Sums.** Every sum checks: 15, 14, 14, 21, 12, 1, 19, 28, 17, 27, 19, 16, 14, 13, 22, 17.
- **Cells read from conditions.** All of them were confirmed by the re-runs:
  - 5.1-A* S5;
  - 5.4-A* S3 and S6;
  - 4a-2G S2, S5 and S8;
  - 4c-1C S2, S3, S5, S6 and S8.
- **Dropped options.** 4c-2 is correctly out of bounds: it would budget full rebuilds, which AQ10 says are "recorded, not budgeted". It would also lose on sum (21 against 17) if it were admitted.
- **One composed variant per decision id.** I accept this reading. decider.md §4–§5 builds one map per decision and applies the ordering to each map. The sub-questions have disjoint option sets and every seat rated them separately. Every cell read from conditions was re-confirmed, which is the risk the rule guards against. The sub-decisions are coupled, though, and the ledger must say so:
  - S2's 4a-2G cell relies on 4b-2 (no cache credit);
  - 4c-1C's memory block relies on 4a-2G's ceiling;
  - D-T4b's reversal (Phase 10 adopts a kernel cache) cannot happen without first reversing D-T4a (ii). Seat 2's re-run says the 128 MB cap rules out the 0.47 GB AQ10-room kernel.
- **D-T4: K8–K10 declared unknown.** It is legitimate to set a working ceiling with these unknown:
  - phase-05b2 §3 D-T4 asks only for a working ceiling;
  - phase-13 L45–47 owns the budget;
  - the researcher shows there is nothing to research (§3, §7), so this is not UNDERINFORMED;
  - the gate makes the transient part independent of K10, except under Bitwig's sandboxing;
  - confidence is stated as low.

  Two statements must be corrected (D4-K and D4-REG below). The leftover exposure, 128 MB resident × K10 plus the Bitwig case, must be stated as debt.

### Decision ledger

| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| D-T5.1 | D5-L1 | `target_hybrid` = specular + window(diffuse); within 0.08 dB at 500 Hz–2 kHz | CORRECT | `ref_hybrid.py` L528–533; report-phase05b L9 (max \|Δ\| 0.08 dB, SE ≤ 0.078) | – | – |
| D-T5.1 | D5-L2 | AX16 vs hybrid is 3.83 dB in the outer bands, as inside | CORRECT | C2 table: layout 4 is +3.83 in all 8 bands; 41/425 case-bands > 1 dB | – | – |
| D-T5.1 | D5-L3 | offline build runs under ScopedNoDenormals; builder, prepare, restore and CLI set no FP mode | CORRECT | `PluginProcessor.cpp` L166/181; `ScenePipeline.cpp` L271, L322, L400–402; `Denormals.h` exists | – | – |
| D-T5.1 | text | "injected as s(1−α) … (Kuttruff Eq. 4.24)" | IMPRECISE | Eq. 4.24 is Lambert's law with ρ; the s(1−α) / (1−s)(1−α) split is Kuttruff §5.2 (also §2.7, notation L229). Cite both. | corrections | – |
| D-T5.1 | condition (i) | "bit-identical IRs on three OSes" | IMPRECISE | AX5 asks for bit identity on the same platform; phase-13 scope 3 allows ≤ −100 dBFS across architectures. Restate as "FTZ-on and FTZ-off builds bit-identical on each of the three CI platforms". Add Seat 5's re-run notes (RAII guard that also restores on throw; the test room must produce denormals without FTZ). | corrections | – |
| D-T5.1 | debt / hidden premise | "(ii) passes" repays the S1/S4/S9 "validated only at 500 Hz–2 kHz" debt | IMPRECISE | Kuttruff Table 5.2 layouts 4 and 5 have band-independent α (C2 L27 says the same of all 15 (A) cases). So (ii) differs from the validated check only through air, exp(−mR) (Kuttruff §4.5 L2372). It tests the AX4 regime at 4–8 kHz and nearly repeats the in-band check at 125 Hz. S1's 63 Hz debt ("wrong under any geometric method") is not repaid by (ii). | corrections | – |
| D-T5.1 | map | S1 kept at 1/1 although its 1→0 condition is a subset of (ii) | faithful (conservative) | Seat 1 §6: "tracer comparison at 125 Hz and 4 kHz in layout 4 and layout 5 at s = 1"; the result is pending | – | – |
| D-T5.1 | ordering | 5.1-C dropped by veto; 5.1-A* max 1 | CORRECT | Even without S2's veto, 5.1-C has max 2 (S1, S3, S4, S6, S8, S9), so the veto basis (E5, outside the corpus) is not load-bearing | – | – |
| D-T5.2 | E10 (S2) | splitting an entry px / (1−p)x scales Q by p²+(1−p)², so k = S²/Q rises by up to 2× | CORRECT | working: S unchanged, Q' = (p²+(1−p)²)Q, minimum 0.5 at p = 0.5 | – | – |
| D-T5.2 | D5-L5 | t_mix,e fixed before the diffuse solve | CORRECT | `Engine.cpp` L121–148 | – | – |
| D-T5.2 | debt | "evidence arrives at Phase 13's i₀ re-derivation" for the k_real over-trigger | INCONSISTENT | k_real is tested only at the expected-rule t_mix,e (AX22; `Engine.cpp` L130–134), and i₀ does not enter it. The i₀ re-derivation (phase-13 L116) changes N_cap and t_cap, not the trigger. "A listening result on a high-s flutter scene" appears in no phase file. Also, the register merges nine seats into three items; S6's "invisible coupling of s to the fallback" should be its own row. | corrections | Q5 |
| D-T5.3 | ordering | 5.3-C vetoed (S4 later 3); 5.3-A and 5.3-D tie at max 1; 5.3-D wins on sum, 1 against 12 | CORRECT | rebuilt from the seats | SURVIVES | – |
| D-T5.3 | D5-L6 | the shares have no consumer | CORRECT | grep: `NoiseTail.cpp` L244 and `Cli.cpp` L484 only | – | – |
| D-T5.3 | D5-L7 | F25: kick drum, extreme case, no effect for speech | NOT CHECKABLE (researcher-read, outside the corpus); not load-bearing (5.3-C is vetoed regardless) | dossier F25 | – | – |
| D-T5.4 | D5-L8 | tail −104 dB (63 Hz) and −166 dB (1 kHz) re direct; two evaluations agree within SE; open boxes ≥ 90 dB below | CORRECT | C1 table: integral and MC within 1 SE in all 8 bands (4 and 8 kHz at about 0.9 SE). Addendum minimum −90.6 dB (20×20×8 m, 63 Hz; only 63 Hz–1 kHz printed). C1's prose "−152 dB at 1 kHz" is the 500 Hz value; the decider used the table correctly. | – | – |
| D-T5.4 | inaudibility | a tail ≥ 90–104 dB below the direct sound is inaudible | CORRECT with conditions | Vorländer §1.5 / Table 1.2: 0 dB ≈ mid-frequency threshold; Fig. 6.2: the threshold rises steeply toward low frequencies. With the direct 63 Hz band ≤ 104 dB SPL (≤ 90 dB for open boxes), the tail energy is below 0 dB SPL. Above those levels it is not checkable without an LF threshold value. Seat 1's −80 dB floor stays [Hyp]. | – | – |
| D-T5.4 | D5-L9 | Eyring assumes homogeneous α and a diffuse field | CORRECT | Vorländer §4.4.1 L1658 | – | – |
| D-T5.4 | Phase 12 check (carries S6's later cell and the S2/S8 debt) | each outdoor preset checked against an "independent single-scatter ground estimate" | CONDITIONS VIOLATED | One generation holds only when every non-ground face has α = 1 (C1 model; Kuttruff Eq. 4.28 keeps the ρB re-radiation term otherwise). Phase 12's `courtyard` (phase-12 L36: 4 hard walls) breaks this, so the estimate is neither a reference nor a bound there. Not load-bearing for the choice: if S6 returns to 2, the max is 2 and 5.4-A* (18) still beats 5.4-A (19) and 5.4-B (28). | corrections (re-ask S6 on the restated check) | Q2 |
| D-T5.4 | reversal condition | "outdoor or semi-open preset whose tail after the handover is within 60 dB of the direct sound" | INCONSISTENT | `courtyard`'s physical reverberation (phase-12 L65, "slap echoes") puts energy after the handover within 60 dB, so the reversal would fire on correct behaviour. It needs a ghost-tail criterion. | corrections | Q2 |
| D-T5.4 | hidden premise | log-domain check of the diffuse E_target to D-T1's tolerance in every band, under condition (i)'s FTZ | NOT CHECKABLE (software), flagged | C1: 8 kHz E_target is 1.19e−41, below the float32 normal range; under FTZ any float32 stage flushes it to 0 and log(0) is undefined. State the precision of the diffuse path (double), or a per-band floor. | corrections | Q2 |
| D-T4a | map (S6, S3) | 4a-2G cells carried from 4a-2 without the seat's rating or a "(read from conditions)" mark | TENSION MISREAD | decider.md §4 requires an unrated variant to be read from conditions and marked. The composed term (one diffuse solve per process; under 4b-2 every rebuild contains it) serialises rebuilds across instances. That bears on S6's stated measure ("how long the user waits between an edit and hearing it") and S3's (AQ4 staleness 2R + 2P). S3 can be read from its own 4a-3 condition ("builds serialised across instances") but must be marked; S6 has no condition on serialisation. The register reasons attributed to S3, S4 and S6 for the later 1 are not the seats' words (they gave none for 4a-2). | **TENSION MISREAD** (the winner changes only if S3 or S6 rates a 3; then 4a-2 wins at 19 against 27) | Q1 |
| D-T4a | D4-L1 / D4-L2 | dense kernel 3–6 TB; 9 600 × 2 100 × 4 B = 80.6 MB per band per emitter, 161 MB for two emitters | CORRECT | N = 6·100²/2.5² = 9 600; t_cap = (3VN/(4πc³))^(1/3) = (3·10⁶·1560/(4π·343³))^(1/3) ≈ 2.10 s (Kuttruff Eq. 4.6 integrated); 9 600²·1 035·4 B = 381 GB per band, ×8 = 3.05 TB | – | – |
| D-T4a | decision text (ii) | "resident memory ≤ 128 MB per instance" | IMPRECISE | Convening (a) defines the ceiling as the diffuse computation's *additional* memory. Read as a total it collides with the +122.6 MB Phase 07 baseline (phase-13 L44). Restate as "additional resident". "Baseline that already ships" is also loose: nothing has shipped. | corrections | – |
| D-T4a | D4-K | "the in-repo measurements that close K8–K10 for Phase 13 are listed under D-T4c" | INCONSISTENT | D-T4c records only this plugin's time and memory. None of them measures customer RAM (K8), other plugins' memory (K9) or instances per project (K10). Not load-bearing for the choice; strike it, and record 128 MB × K10 plus the Bitwig case as debt. | corrections | Q3 |
| D-T4a | D4-REG | evidence "Phase 13's three-OS multi-instance RSS" | INCONSISTENT | phase-13 scope 1 measures memory *per instance* on three OSes; the scope 3 10-instance test records only the CPU sum (L51). No multi-instance RSS test exists. Add it through /fix-plan or restate the row. | corrections | Q3 |
| D-T4b | ordering | 4b-2 max 1 against 4b-1 max 2 (S2 2/2, S5 later 2) | CORRECT | rebuilt from the seats | – | – |
| D-T4b | text | "a cache that phase-05b2 §9 puts out of scope" | IMPRECISE | §9 excludes only "Phase 10 caching beyond what D-T1 needs"; §3 D-T1 (a) explicitly includes a cached room kernel. Not load-bearing (the worst-off decides). D-T1 must not read W1/W2 under 4b-2 as what candidate (a) would ship. | corrections | – |
| D-T4c | map (S2 later) | 4c-1C S2 read as 1/1 | condition not carried | Seat 2's re-run: the later 1 holds only if the gated 100 m, 96 kHz, 2-emitter build is in the AX22 fallback (about 2 100 against 1 035 bins), or both cases are measured; otherwise 2. The 4c-1C text omits this. Add it, or set S2 to 1/2 with a debt row. Either way the max stays 2 (S5) and the winner is unchanged (sum 18 against 4c-1's 22). | corrections | Q4 |
| D-T4c | records | Seat 5's contended-restore record and Seat 8's bounce/real-time ratio | to add | re-runs 6-seat5 and 6-seat8 (no rating change) | corrections | – |
| D-T4c | D4-L6 / Challenge 1 | 30 s watchdog / 14 parameters ≈ 2.1 s per restore; 100 m, 96 kHz rebuild 1.51–1.88 s | CORRECT (arithmetic); watchdog facts NOT CHECKABLE (researcher F16–F18) | 30/14 = 2.14 s; phase-13 L42–44: 1509.1–1883.7 ms; 14 ids in `parameter_ids_v1.json`. Ruling that Seat 5's gate amends AQ10 is correct: a restore is a full rebuild, and AQ10 says full rebuilds are "recorded, not budgeted". | – | – |
| D-T4c | D4-L7 / escalation | Table 15.1 is a "proposal"; 3 s used as the escalation yardstick for full rebuilds | CORRECT / IMPRECISE | Vorländer §15.3 Table 15.1 caption. The 3 s row covers only "translational … movement > 1 m", derived from 30–50 cm/s VR movement (L3957). There is no row for room-geometry or material edits, so the packet must state that. | corrections | – |

### Questions for the decider's rebuttal, most consequential first

1. **D-T4a.** What do Seat 6 and Seat 3 rate 4a-2G, given that the process-wide gate serialises every instance's diffuse solve (and under 4b-2 every rebuild contains one)? If Seat 3 is read from its 4a-3 condition, mark it. Seat 6 has no applicable condition, so it must be asked. A 3 from either changes the winner to 4a-2.
2. **D-T5.4.** Against what independent reference is Phase 12's `courtyard` checked, given that the single-scatter ground estimate holds only when every non-ground face has α = 1? Restate the reversal condition so that real reverberation does not trigger it, and state the diffuse path's precision for the 4–8 kHz log-domain check under FTZ.
3. **D-T4a.** Which D-T4c record measures K8, K9 or K10? If none, strike the sentence. Which phase-13 item measures multi-instance RSS, or will /fix-plan add one?
4. **D-T4c.** Will the gated 100 m, 96 kHz build be in the AX22 fallback, as Seat 2's re-run requires? If not, record S2 at 1/2 with its debt row.
5. **D-T5.2.** Which scheduled test produces evidence of a k_real over-trigger, given that i₀ does not enter k_real? If none, mark the debt "no scheduled evidence".

### Ledger rows for `docs/review/ledger.md`

| id | item | verdict | status |
|---|---|---|---|
| P05B2-T5T4-01 | D-T5.1 D5-L1 target_hybrid composition, 0.08 dB at 500 Hz–2 kHz | CORRECT | closed |
| P05B2-T5T4-02 | D-T5.1 D5-L2 AX16 vs hybrid 3.83 dB in all bands (C2) | CORRECT | closed |
| P05B2-T5T4-03 | D-T5.1 D5-L3 FP-mode split between paths (code) | CORRECT | closed |
| P05B2-T5T4-04 | D-T5.1 citation: Eq. 4.24 (Lambert) + §5.2 for the s(1−α) split | IMPRECISE | open |
| P05B2-T5T4-05 | D-T5.1 condition (i) "bit-identical on three OSes" → per platform; add Seat 5's RAII and denormal-producing test room | IMPRECISE | open |
| P05B2-T5T4-06 | D-T5.1 condition (ii) on band-independent-α layouts tests only air at 4–8 kHz; register "repaid when (ii) passes" overclaims (S1 63 Hz) | IMPRECISE | open |
| P05B2-T5T4-07 | D-T5.2 E10 k inflation ≤ 2× | CORRECT | closed |
| P05B2-T5T4-08 | D-T5.2 D5-L5 t_mix,e fixed before the solve | CORRECT | closed |
| P05B2-T5T4-09 | D-T5.2 debt evidence "Phase 13 i₀ re-derivation" cannot show a k_real over-trigger; per-seat rows (S6) | INCONSISTENT | open |
| P05B2-T5T4-10 | D-T5.3 ordering and map | CORRECT | closed |
| P05B2-T5T4-11 | D-T5.3 D5-L6 shares have no consumer | CORRECT | closed |
| P05B2-T5T4-12 | D-T5.3 D5-L7 F25 (external) | NOT CHECKABLE (not load-bearing) | closed |
| P05B2-T5T4-13 | D-T5.4 D5-L8 C1 levels, MC vs integral within SE, open boxes ≥ 90 dB | CORRECT | closed |
| P05B2-T5T4-14 | D-T5.4 inaudibility at C1 levels (Vorländer §1.5, Fig. 6.2; stated level conditions) | CORRECT with conditions | closed |
| P05B2-T5T4-15 | D-T5.4 D5-L9 Eyring premises | CORRECT | closed |
| P05B2-T5T4-16 | D-T5.4 Phase 12 single-scatter ground check applied to `courtyard` | CONDITIONS VIOLATED | open |
| P05B2-T5T4-17 | D-T5.4 reversal condition fires on courtyard's real reverberation | INCONSISTENT | open |
| P05B2-T5T4-18 | D-T5.4 log-domain check below the float32 normal range under FTZ (precision unstated) | NOT CHECKABLE (software), flagged | open |
| P05B2-T5T4-19 | C1 prose "−152 dB at 1 kHz" (table: −166 dB; −152 is 500 Hz) | INCONSISTENT (source typo; decider unaffected) | open |
| P05B2-T5T4-20 | D-T4a 4a-2G S6 (and S3 unmarked) cells carried without rating; invented register reasons | TENSION MISREAD | open |
| P05B2-T5T4-21 | D-T4a D4-L1/L2 kernel and history sizes, t_cap ≈ 2.1 s (Kuttruff Eq. 4.6) | CORRECT | closed |
| P05B2-T5T4-22 | D-T4a (ii) resident cap must read "additional" (baseline +122.6 MB) | IMPRECISE | open |
| P05B2-T5T4-23 | D-T4a "D-T4c measurements close K8–K10" | INCONSISTENT | open |
| P05B2-T5T4-24 | D-T4a register "Phase 13 multi-instance RSS" (does not exist; scope 3 records the CPU sum) | INCONSISTENT | open |
| P05B2-T5T4-25 | D-T4a working ceiling with K8–K10 declared unknown | legitimate (phase-05b2 §3, phase-13 L45–47); debt 128 MB × K10 + Bitwig to record | open |
| P05B2-T5T4-26 | D-T4b ordering | CORRECT | closed |
| P05B2-T5T4-27 | D-T4b "§9 puts a cache out of scope" (§9: beyond what D-T1 needs) | IMPRECISE | open |
| P05B2-T5T4-28 | D-T4c S2 re-run condition (gated build in the AX22 fallback) not carried | correction (winner unchanged) | open |
| P05B2-T5T4-29 | D-T4c contended-restore and bounce/real-time records (Seats 5 and 8) | to add | open |
| P05B2-T5T4-30 | D-T4c D4-L6 / Challenge 1 arithmetic (2.14 s; 1.51–1.88 s); AQ10 ruling | CORRECT | closed |
| P05B2-T5T4-31 | D-T4c Table 15.1 3 s row used for full rebuilds: state its conditions | IMPRECISE | open |
| P05B2-T5T4-32 | One composed variant per decision id; coupling 4a-2G ↔ 4b-2 ↔ 4c-1C to be recorded | accepted reading | closed |

Files:
- /home/user/makroof/docs/review/phase-05b2/5-decider-decision-T5-T4.md
- /home/user/makroof/docs/review/phase-05b2/2-orchestrator-C1-open-field.md
- /home/user/makroof/docs/review/phase-05b2/2-orchestrator-C2-dLb-all-bands.md
- /home/user/makroof/docs/review/phase-05b2/6-seat2-rerun-T5-T4.md
- /home/user/makroof/docs/review/phase-05b2/6-seat5-rerun-T5-T4.md
- /home/user/makroof/docs/phases/phase-12.md
- /home/user/makroof/docs/phases/phase-13.md
- /home/user/makroof/docs/phases/phase-05b2.md
- /home/user/makroof/src/sim/Engine.cpp
- /home/user/makroof/src/plugin/core/ScenePipeline.cpp
