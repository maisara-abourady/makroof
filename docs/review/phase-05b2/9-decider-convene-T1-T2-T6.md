# Decider — convening round, D-T1, D-T2 and D-T6

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

# Decider: convening round for D-T1, D-T2 and D-T6 (phase 05b session 2)

**Corpus revision:** `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d` (`docs/corpus/SOURCE_COMMIT`, 14 files present).

**What this round is.** This is a convening round only, so nothing is decided here. D-T3 is not convened. It is needed only if D-T1 leaves part of AX6's range uncovered within D-T4. Of the options below, only T1-A does that (a memory limit). T1-B and T1-F fit in memory at 100 m, and under the proposed D-T4c time is recorded and escalated, not blocked. If T1-A wins, a D-T3 convening follows.

**Dependence on proposals still under interrogation.** This round rests on five proposals that the interrogator is still checking:
- D-T5.1: all 8 bands, specular plus diffuse.
- D-T5.2: k_real, and therefore t_mix,e, is fixed before the diffuse solve.
- D-T4a: ≤ 1 GB transient and ≤ 128 MB resident per instance.
- D-T4b: W1/W2 include the whole diffuse computation.
- D-T4c: memory blocks; time is recorded and escalated against 1, 3 and 10 s.

If the interrogator changes any of them, the cells that depend on it are asked again:
- the 1 GB value → T1-A and T1-B;
- t_mix,e before the solve → T1-F's window premise.

T1-A cannot reach 100 m under any ceiling the board rated (≤ 4 GB). That point does not depend on D-T4a's exact value.

## PRD digest
The digest from `1-decider-convene-T5-T4.md` still holds. I re-checked the ids in PRD L89 and L105–112.
- **For whom:** producers and DJs in any DAW. They do not know spatial audio.
- **Outcome:** a track that sounds as if it were played in the designed or preset space, indoor or outdoor (FR-3D-3).
- **Hard constraints in play:**
  - NFR-1: accuracy first.
  - NFR-2: heavy CPU is fine if it buys accuracy, but the plugin must stay usable in a DAW.
  - NFR-3 and FR-SIM-6: no artefacts under automation.
  - NFR-6 and AX5: bit-identical on the same platform; within −100 dBFS of the residual across architectures.
  - NFR-8 and FR-SIM-2: no scene-specific logic.
  - AX6: rooms 1.5–100 m. The listener and emitters must be ≥ 0.1 m from every surface (from the code: `Validate.cpp` L65–67, `Validate.h` L28).
  - AQ10: the 50 ms target is recorded; full rebuilds are not budgeted.
  - The contract is unchanged.
- **Settled (phase-05b2 §1):** AX22, N_cap, the mixing-time rule and B12 stay. AX36's per-quantity < 1 % rule stands (accepted by Maisara 2026-11-09). A coarser ℓ is not a remedy. Table 15.1 is a Phase 10 remedy only if W1 > 700 ms.
- **Verification culture (CLAUDE.md):** automated checks against independent references; no golden is regenerated to pass.

---

## Option block (pass verbatim to every convened seat)

### D-T1: formulation of the propagated diffuse energy in `src/sim`

**D-T1.1 Formulation**

**T1-A: patch kernel.** This is candidate (a), with (c)'s shoebox structure where it saves memory: `ref_hybrid`'s discretisation at ℓ = 2.5 m ported to C++.
- It is deterministic and agrees with `ref_hybrid` to float precision.
- Memory, 8 bands, float32 (builder evidence §1):

| candidate | AQ10 room | AQ10 room, fallback | CR4 | 100 m |
|---|---|---|---|---|
| (a) dense kernel | 0.47 GB | 1.53 GB | 2.53 GB | 3 052–6 193 GB |
| (c) shoebox structure (arithmetic only) | 0.17 GB | 0.54 GB | 0.35 GB | 211–428 GB |

- W1 measured with numpy: kernel 9.9 s, injection and gather 0.36 s, solve 5.4 s, peak RSS 1.17 GB.
- It cannot reach 100 m under any rated ceiling, so it forces D-T3: a generic range limit with no level step at the size threshold, which is a contract major bump and Maisara's call.
- Under the proposed 1 GB ceiling, (a) already fails in the AQ10 room in fallback and in CR4.

**T1-B: matrix-free patch propagation.** This is candidate (b), on the same ℓ = 2.5 m discretisation.
- Form factors and delays are computed per generation. It keeps a per-patch history of N·T per band: 40–81 MB per band and emitter at 100 m.
- It is deterministic.
- Time per generation is 4.6·10⁸ pair-image evaluations in the AQ10 room and up to 4·10¹² in the 100 m fallback. This is builder arithmetic only (C8 asks for a measurement).
- It covers AX6 in memory. Time at large rooms is recorded and escalated under D-T4c, not blocked.

**T1-F: seeded Monte Carlo with next-event estimation (MC-NEE).** This is candidate (f), as in builder evidence §2.
- Particles start uniformly from the emitter. At every hit, the diffuse emission s(1−α) (Kuttruff Eq. 4.24) is gathered at the point listener over its lattice images: Eq. 4.29, with Gilbert/Joyce transport (Eq. 4.35), the AX4 air term and the `matchTail` window. The particle then continues diffusely with probability s, otherwise specularly.
- It has no patches; it is the ℓ → 0 form of the model. The specular entries stay exact (ISM).
- Memory is < 2 MB in every room measured.
- Agreement with `ref_hybrid` (ℓ = 1.25 m) on the 15 (A) cases at 32 000 paths: ≤ 0.087 dB and ≤ 1.67 SE, in 500 Hz–2 kHz only.
- Cost per emitter (numba prototype, one thread):

| scene | at SE 0.083 dB | at SE 0.033 dB |
|---|---|---|
| W1 | 1.8–2.5 ms | 11.7–16.0 ms |
| W2 | 1.3 ms | – |
| CR4 | 2.5–13.6 ms | 15.8–86.1 ms |
| 100 m cube | 144–183 ms | 0.91–1.16 s |
| 100 m flutter (AX22 fallback) | ≤ 0.2 ms | – |
| Table 5.2 layout 4, s = 1 | ≈ 1.5 s | ≈ 9.7 s (scaled as 1/SE²) |

- Corpus kin: Vorländer §11 describes "diffuse rain" (Heinz 1993): scattered energy sent from each wall hit to a detector **sphere** (Fig. 11.38). (f) uses a **point** listener instead, so its cos θ/r² term is unbounded near walls (see C4 and RQ-T1-1).

**Not offered:**
- (d) adjoint: the windows are per emitter, so it saves nothing over a forward solve (builder evidence, reasoning only). A seat that sees a saving should say so.
- (e) transform-domain approximation: it has no error bound, so it fails "the same model to a stated tolerance". Its exact form costs as much as (a).
- (a) or (f) switched by room size: it carries (a)'s memory, (f)'s standard error and a threshold step. A seat that needs it should state it as a condition.

**D-T1.2 Seed.** Rate this only if T1-F is acceptable to you; otherwise write "n/a".
- **S-1:** the RNG key is (fixed constant, emitter index, path index). E_target does not vary with tailSeed. The Monte Carlo deviation is a fixed per-scene offset, present in every AX11/AX19 ensemble.
- **S-2:** the key is (tailSeed, emitter index, path index). E_target varies with tailSeed by about 1 SE, and tailSeed ensembles average that out. A user who changes tailSeed changes the tail level by about 1 SE.
- Both use a counter-based RNG and a fixed-order reduction, so they are bit-identical run to run (AX5).
- Not offered: a key hashed from the scene. It redraws every path on each update, so E_target would jitter by about 1 SE per update.

**D-T1.3 Path count (T1-F only)**
- **N-1:** one fixed N for every scene, equal to the paths that the worst case in the agreement set needs to meet the SE target. With today's data that is ≈ 22 000 for SE 0.083 dB (layout 4, s = 1). The SE then varies by scene and is unbounded in scenes worse than that case.
- **N-2:** an SE target. Paths are added in fixed batches, always as a prefix of one deterministic sequence, until the estimated relative SE is ≤ the target in every band, or until a constant N_max is reached. The diagnostics report N, the SE and any cap hit.

**D-T1.4 Agreement tolerance τ and SE target τ/3 (AX11 convention)**

τ is the C++ vs `ref_hybrid` difference allowed per case and band, and it includes the reference's own ℓ term. Under T1-A or T1-B, τ is a float tolerance and there is no SE.
- **Tol-1:** τ = 1 dB (the B11 window tolerance), SE ≤ 0.33 dB.
- **Tol-2:** τ = 0.25 dB, SE ≤ 0.083 dB.
- **Tol-3:** τ = 0.1 dB, SE ≤ 0.033 dB.

τ is also used by D-T5.4's `open_field` check and enters D-T6's bound.

**D-T1.5 Agreement case set** (all 8 bands; reference = `ref_hybrid` at ℓ = 2.5 m, exported as a small golden)
- **CS-1:** the 15 (A) cases.
- **CS-2:** CS-1, plus the six Phase 04 rooms (both emitters), plus the W1 and W2 scenes.
- **CS-3:** CS-2 plus the 30 BRAS pairs (Phase 05 positions, initial α).

No case set reaches 100 m, because `ref_hybrid` needs terabytes there. C7 reports whether any independent check at 100 m is feasible.

### D-T2: the tail path's resolution parameter (R1), restated for D-T1's discretisation
- **If T1-A or T1-B, option L2-P: ℓ = 2.5 m.** It is certified in the 15 (A) cases, CR2, CR3 and CR4 (CR4: 0.140 %, report-phase05b §5b), but only at 500 Hz–2 kHz. The outer bands are pending (C9).
- **If T1-F, the resolution parameter is N or the SE:**
  - **L2-F1 (literal):** N is certified if doubling it changes E_target by < 1 % in every case and band of the agreement set. This is one realisation at the fixed seed, so pass or fail is itself random.
  - **L2-F2 (AX11's threshold/3 applied to the 1 % rule):** 3·SE ≤ 1 %, i.e. SE ≤ 0.33 % (0.0145 dB). This overrides D-T1.4 when it is stricter. It needs ≈ 33× the paths of SE 0.083 dB. My scaling of the prototype per emitter: W1 59–82 ms, 100 m 4.7–6.0 s, layout 4 at s = 1 ≈ 51 s.
- **Dropped at bounds:** "the < 1 % rule does not transfer to an estimator without discretisation". That contradicts phase-05b2 §3 D-T2 ("under the same per-quantity < 1 % rule"), which rests on AX36 as accepted by Maisara. A seat that wants it argues it as a challenge for Maisara.

### D-T6: regression bound for rooms where AX16 is exact per reflection order (uniform α)
Fixed before any C++ agreement number. Frame (b) for mixed-α rooms is settled: report, do not bound.

**Room set**
- **RS-1:** the uniform-α rooms among the six Phase 04 rooms.
  - From the fixture files, `stone_box` is uniform and `dead_booth`, `living_room` and `classroom` are mixed.
  - phase-05b2 §3 calls `club` and `concert_hall_box` mixed.
  - C10 confirms the list.
- **RS-2:** RS-1, plus the W1 AQ10 room (uniform α, s = 0.3, both emitters), plus the three uniform (A) s-cases, plus any other uniform-α valid fixture (C10).

**Bound** (per emitter and band; ΔL = 10·log10(E_target,after / E_target,before))
- **B6-1, per room, predicted:** |ΔL_C++ − ΔL_ref| ≤ τ in all 8 bands. ΔL_ref comes from `ref_hybrid` at 2.5 m (C11). C11 is computed only after D-T6 is decided.
- **B6-2, global and a priori:** |ΔL_C++| ≤ 0.43 dB + τ in all 8 bands for every room in the set. 0.43 dB is the largest hit-count residual measured in the uniform s-cases in all bands (C2; report-phase05 §6a).

**Reported under either bound (Seat 1's request):** paired before/after values with the same tailSeed, per band: ΔG, ΔC80, ΔEDT, ΔT30 and the seam step at t_mix,e. This covers the room set and the mixed-α rooms. It is not gated.

**Mixed-α rooms**
- **M-1:** C++ vs `ref_hybrid`, plus vs the tracer's committed data where it exists.
- **M-2:** M-1 plus new tracer runs (500 Hz–2 kHz window, as in session 1) on the five mixed-α Phase 04 rooms.

---

## Convening table, D-T1 and D-T2 (one shared table)
D-T1 and D-T2 are convened together because under T1-F, D-T2 is the same precision-and-cost matter as D-T1.3 and D-T1.4.

| seat | status | reason (README convening item) | brief |
|---|---|---|---|
| 1 | convened | Audibility of τ and the SE (scene-to-scene random level error against the 1 dB jnd of G); level steps under automation; the acceptance-test rule. PRD-priority seat: what the user hears. | B1 |
| 2 | convened | GA formulation, scattering transport, validation against the reference, simulator compute; claims of physical accuracy | B2 |
| 3 | convened | Tail level at the seam; time variance under automation; per-instance build cost | B3 |
| 4 | convened | Phases 08/09 share the rebuild budget (AQ10: "every output mode from Phase 08"); E_b parity across modes under S-1/S-2; the §8 rule on whether Phase 08 may go first | B4 |
| 5 | convened | Builder thread; determinism (AX5); synchronous restore and prepare (pluginval, Challenge 1); CI gates and runtime. PRD-priority seat. | B5 |
| 6 | convened | Edit-to-hear delay; automation behaviour; what tailSeed means to the user; T1-A's range limit. PRD-priority seat. | B6 |
| 7 | convened | Complexity and schedule; what one founder can sustain; public accuracy wording; "any environment" under T1-A. PRD-priority seat: cost. | B7 |
| 8 | convened | Workflow: rebuild delays, bounces, many instances; large venues | B8 |
| 9 | convened | Real positions (listeners near walls and in corners); the reference set (BRAS); large venues; honest validation | B9 |

## Convening table, D-T6
| seat | status | reason | brief |
|---|---|---|---|
| 1 | convened | Bound against audibility; its own before/after report request. PRD-priority seat. | B1 (D-T6 part) |
| 2 | convened | Validation; the physics of the hit-count residual and whether 0.43 dB can serve as an a priori bound | B2 (D-T6 part) |
| 3 | convened | Seam step and decay reporting | B3 (D-T6 part) |
| 4 | not required | No delivery-chain item (HRTF, decoding, format parity) is touched. D-T6 bounds the omni tail level of existing fixtures, and Phase 08 is built on the switched E_b anyway (D-T5.3). | – |
| 5 | convened | A CI gate on three OSes; the golden process; paired-seed renders | B5 (D-T6 part) |
| 6 | not required | D-T6 defines no control, name, range, default or preset. Presets come in Phase 12. Audibility of the uniform-room change is Seat 1's. | – |
| 7 | not required | No price, wording or schedule item. The CI time of a few fixtures belongs to Seat 5. | – |
| 8 | not required | No storytelling item. Seat 8 rated the mixed-room corrections in D-T5.1, and they are report-only under settled frame (b). | – |
| 9 | convened | Which real rooms are uniform; whether `stone_box` and W1 are representative; M-1 vs M-2 | B9 (D-T6 part) |

---

## Common brief (verbatim to every convened seat, followed by its addendum)

> **Subject:** phase 05b session 2, decisions D-T1 and D-T2 (all nine seats) and D-T6 (seats 1, 2, 3, 5 and 9), `docs/phases/phase-05b2.md` §3. The options are exactly those in the decider's option block, which the orchestrator attaches.
>
> **Settled, do not reopen:** the switch is built this session (Maisara, option (b)); AX21, AX22, N_cap, the mixing-time rule, B12 and AX36's < 1 % per-quantity rule; the contract is unchanged; NFR-8; a coarser ℓ is not a remedy.
>
> **Proposed and under interrogation (rate on them as stated, and say if your rating depends on one):** D-T5.1–5.4 and D-T4a–c (`docs/review/phase-05b2/5-decider-decision-T5-T4.md`).
>
> **Read:**
> - `docs/phases/phase-05b2.md` §0–§8;
> - `docs/review/phase-05b2/7-builder-D-T1-evidence.md` (all of it);
> - `tools/validation/phase05b2_dt1.py` (`mc2`, `e_diff`);
> - `tools/acoustics/ref_hybrid.py` (`phase04_plan`, `target_hybrid`);
> - `docs/validation/report-phase05b.md` §3, §5, §5b;
> - `docs/review/phase-05b2/2-orchestrator-C2-dLb-all-bands.md`;
> - BUILD_PLAN §2 AX5, AX6, AX11, AX16, AX19, AX22, AX36, AQ10;
> - PRD NFR-1, NFR-2, NFR-3, NFR-6, NFR-8, FR-SIM-6;
> - Vorländer §11, the "diffuse rain" paragraph and Fig. 11.38.
>
> **For each option of D-T1.1–1.5 and D-T2 (and D-T6 if you are convened on it):**
> - ratings now and later (0–3), each with a one-line reason in your own measures;
> - conditions of acceptance for every 2 or 3;
> - evidence tags, corpus first.
>
> Rate D-T1.2–1.4 under T1-F, and say whether your ratings change with D-T2's choice: L2-F2 overrides the SE target. Name anything the researcher or the orchestrator should check.

**Addenda**

**B1 (Seat 1)**
- Is a per-scene random tail-level error of 0.33, 0.083, 0.033 or 0.0145 dB audible? Compare it with the 1 dB jnd of G (Vorländer Table 6.1, 500–1000 Hz, by extension).
- Are the level steps under automation audible: edge crossings of order 1/N, and N-2's batch steps (C6)?
- Is the S-2 level change on a tailSeed change audible?
- Is D-T2's 1 % (0.043 dB) perceptual, or only a numerical rule?
- Give the agreement-test decision rule you require for a stochastic estimate:
  - how it handles multiple comparisons across case-bands;
  - what happens when a case-band fails, given that changing the seed afterwards is tuning.
- **D-T6:** rate B6-1 and B6-2 against audibility. Specify your before/after report: metrics, bands, the paired design, and any ensemble.

**B2 (Seat 2)**
- Is T1-F the same model as `ref_hybrid`? Check:
  - next-event estimation over the listener's lattice images = Eq. 4.29 with Eq. 4.35 transport;
  - broadband-s branching;
  - a point listener against exact patch solid angles;
  - unbiasedness.
- Near-wall variance at AX6's 0.1 m listener clearance (C4, RQ-T1-1): is a detector sphere as in diffuse rain needed, and what bias would it add?
- What evidence covers T1-F at 100 m (C7)?
- T1-B's time, and whether the builder's claim that (d) saves nothing holds.
- **D-T2:** L2-F1 against L2-F2, and the outer-band ℓ under L2-P (C9).
- Your D-T4c condition (the gated 100 m scene must be in the fallback, or both cases measured): under T1-F the fallback scene is the cheap one. Which scene is the worst case for (f)?
- **D-T6:** is 0.43 dB a defensible a priori bound for RS-2 (`stone_box` at s = 0.1; W1 at s = 0.3), or does the residual depend on s, size or t_mix in a way that makes only B6-1 sound?

**B3 (Seat 3)**
- Tail-level jitter under source and room-size automation as heard at the seam (C6).
- Builder cost per instance under N-1, N-2 and L2-F2.
- S-1 vs S-2 for the renderer: under S-2, a seed change alters both the noise and the level.
- **D-T6:** how the seam step should be reported.

**B4 (Seat 4)**
- Does each option's cost leave headroom for Phase 08/09 builds (W1/W2 per output mode)?
- E_b parity between omni and binaural within one build under S-1 and S-2.
- Any effect on whether Phase 08 may go first (§8).

**B5 (Seat 5)**
- Builder time per option and N rule, read under D-T4b and D-T4c.
- The 100 m synchronous restore against Challenge 1 (about 2.1 s per restore).
- Which scene is gated as the worst case for T1-F.
- Determinism:
  - counter-based RNG;
  - fixed-order reduction;
  - FTZ/DAZ (D-T5.1 (i));
  - the −100 dBFS residual across architectures, given that branch flips are discrete (C5, RQ-T1-3).
- Threads inside one solve under the one-solve-per-process gate.
- CI runtime of CS-1, CS-2 and CS-3 in Debug and Release on three OSes.
- **D-T6:** the gate design and the paired renders.

**B6 (Seat 6)**
- Edit-to-hear delay for room-size and material edits (full rebuilds) per option.
- Level steps under automation (C6).
- tailSeed becoming a level control under S-2.
- Users losing large rooms under T1-A.

**B7 (Seat 7)**
- Complexity: porting a validated discretisation (A, B) against maintaining a new estimator class with its own statistics (F).
- Schedule against the §8 split rule.
- Public wording: what "validated" can mean for an estimate with a standard error.
- What T1-A's contract narrowing does to "any environment".

**B8 (Seat 8)**
- Rebuild and bounce delays at Tol-3 and L2-F2 costs, in sessions with many instances.
- Whether a 0.03–0.3 dB scene-to-scene level scatter matters for depth or anchor.
- Large venues under T1-A.

**B9 (Seat 9)**
- Real positions near walls and in corners (booths, back-row seats) under T1-F (C4).
- Whether CS-3 (BRAS) is needed for honest validation.
- Large venues near 100 m, which no reference covers.
- **D-T6:** are real rooms ever uniform-α? Are `stone_box` and W1 representative? M-1 vs M-2.

---

## Knowledge inventory (first pass)
| id | what must be known | source | status |
|---|---|---|---|
| K1 | Memory of (a) and (c) by room | builder evidence §1; phase-05b2 §0.3 | known for (a), measured on W1. (c) is arithmetic only, and under-informed, but load-bearing only if T1-A wins. |
| K2 | (f) agrees with `ref_hybrid` | builder evidence §3; `phase05b2_dt1.json` "agree" | known under its conditions: one seed, 32 000 paths, 500 Hz–2 kHz, reference at 1.25 m, 15 cases |
| K3 | (f) agrees in 63–250 Hz and 4–8 kHz | none | uninformed → C3 |
| K4 | (f) variance and bias with the listener or emitter at the 0.1 m clearance | none | uninformed → C4, RQ-T1-1 |
| K5 | (f) is the same model (Eqs. 4.24, 4.29, 4.35; diffuse rain) | builder evidence §2; Vorländer §11 Fig. 11.38 | under-informed; corpus re-read and Seat 2 in the decision round |
| K6 | (f) cost and peak memory in C++ | prototype only (numba, one thread, 4-core container) | ill-informed risk for C++ (O15). Prototype peak RSS not reported → C9. |
| K7 | (b) time per rebuild | builder arithmetic | under-informed → C8 |
| K8 | (d) saves nothing | builder evidence, reasoning only | misinformed risk; load-bearing only for "not offered" (Seat 2) |
| K9 | AX5 across architectures for a branching estimator | none | uninformed → C5, RQ-T1-3 |
| K10 | Continuity under automation | builder evidence §4 (argument only) | uninformed → C6 |
| K11 | Reference cost for CS-2 and CS-3; any check at 100 m | none | uninformed → C7 |
| K12 | Statistical acceptance and stopping rules for deterministic-seed MC | none | uninformed → RQ-T1-2 |
| K13 | R1 at 2.5 m, 500 Hz–2 kHz (15 (A), CR2, CR3, CR4) | report-phase05b §3, §5b | known |
| K14 | ℓ change in the outer bands; (f) SE in all 8 bands; cost at SE 0.0145 dB | scaled from AQ9-band SE only | under-informed → C9 |
| K15 | Which fixtures are uniform-α | from the code: fixture files (`stone_box` uniform; `dead_booth`, `living_room`, `classroom` mixed); phase-05b2 §3 (`club`, `concert_hall_box` mixed) | partly known → C10 |
| K16 | Hit-count residual | C2 (+0.43 dB in all 8 bands, s-cases); report-phase05b §5 (+0.03…+0.40 dB vs tracer) | known for α = 0.15, s ≤ 0.4, 20×30×10 m; ill-informed risk for other uniform rooms (Seat 2) |
| K17 | G jnd 1 dB | Vorländer Table 6.1 | known; re-read in the decision round |
| K18 | D-T4 and D-T5 values | decider proposals | misinformed risk until the interrogator returns SURVIVES |
| K19 | Each seat's tension | seat reports | uninformed (this round) |

## RESEARCH NEEDED (researcher, in parallel with the seats)

**RQ-T1-1 (D-T1.1, D-T1.3).** Point-detector, next-event or "diffuse rain" estimators: is the variance finite for a point receiver at distance d from a Lambertian surface, and how does it scale with d? What remedies exist (a finite detector sphere as in Heinz 1993 or Schröder et al. 2007; exclusion or average-flux spheres in particle transport, e.g. MCNP), and what bias does each introduce?
- Conditions: energy tallies, receiver 0.1–2 m from a wall.
- What it changes: whether T1-F needs a near-wall remedy or an SE rule that detects heavy tails (Seats 2, 5, 9).

**RQ-T1-2 (D-T1.3–1.5).** Primary documentation of statistical acceptance checks for Monte Carlo tallies: MCNP's tally fluctuation checks (relative-error limits for point detectors, variance of the variance, slope of the tally's tail), with values. Also sequential stopping rules with a relative-precision target (e.g. Glynn & Whitt 1992): their validity conditions and stopping bias.
- What it changes: whether N-2 is valid; whether the SE estimate is reliable; the agreement-test decision rule.

**RQ-T1-3 (D-T1.2, AX5).** Counter-based RNGs (Philox, PCG streams; Salmon et al. 2011): are the streams identical across x86-64 and arm64 and across MSVC, clang and gcc? Is the integer-to-float conversion exact?
- What it changes: whether T1-F meets AX5.

**RQ-T1-4 (D-T1.1).** Published validation of diffuse rain (Heinz 1993; Schröder 2011, RAVEN) against radiosity or exact solutions, with any bias or variance figures.
- What it changes: whether (f) belongs to an established, validated method class (Seats 2 and 7).

## Orchestrator computations (in-repo, offline, outside `src/sim`)
- **C3 (K3):** (f) vs `ref_hybrid` on the 15 (A) cases in **all 8 bands**, reference at 2.5 m (and 1.25 m where it exists). Per band: max |Δ| in dB, max |Δ|/SE, mean signed z.
- **C4 (K4):** (f) with the listener at the 0.1 m clearance from one wall, from two walls (edge) and from three (corner), in the W1 room and in layout 4 at s = 1; plus one case with the emitter at 0.1 m. Report:
  - the SE at 8 000 and 32 000 paths;
  - the paths and time needed for SE 0.33, 0.083, 0.033 and 0.0145 dB (worst of 8 bands);
  - the largest share of the estimate coming from a single path;
  - `ref_hybrid` at 2.5 and 1.25 m (with its own ℓ change).
- **C5 (K9):** (f) on W1 and layout 4 at s = 1, (i) with positions perturbed by 1e-9 m and (ii) with float32 path state. Report |ΔE_target| in dB and the number of paths whose face-hit sequence changed. Confirm that a fixed-order block reduction is bit-identical with 1, 2 and 4 threads.
- **C6 (K10):** sweeps in W1 and in layout 4 at s = 1:
  - source moved 1 m in 1 cm steps;
  - in W1, a uniform room-size sweep of ±5 % in 0.1 % steps;
  - at N = 8 000 and 32 000, and under N-2 with batches of 1 000.

  Report the largest step between adjacent sweep points per band, beside AX16's steps on the same sweep, and the points where N changes. State where the AX22 jump point falls and exclude it.
- **C7 (K11):** memory and time of `ref_hybrid` at 2.5 m in all 8 bands for the six Phase 04 rooms, W1/W2 and the 30 BRAS pairs. Feasibility of an independent check at the 100 m cube: a coarse ℓ ladder (20, 10, 5 m, per band) with its halving changes, or the tracer (N₀ = 254·V, run time).
- **C8 (K7):** T1-B: the generation count for the AQ10 room, CR4 and 100 m (with and without fallback); the per-evaluation cost derived from the measured W1 kernel build (9.9 s); the extrapolated rebuild time per emitter.
- **C9 (K14, K6):**
  - `ref_hybrid` E_target change from 2.5 m to 1.25 m in all 8 bands for the 15 (A) cases and CR2, CR3 and CR4 (extends R1 to the outer bands; Seat 2's D-T5.1 debt).
  - (f) SE in all 8 bands at 8 000 paths for the bench scenes, with the paths and time per emitter for 0.33, 0.083, 0.033 and 0.0145 dB.
  - The prototype's peak RSS delta per scene.
- **C10 (K15):** classify every fixture in `tests/scenes/valid`, the W1/W2 scenes and the 15 (A) cases by uniform α (the same α vector on all six faces). Give dimensions, s per face and fallback status. **Compute no before/after or ΔL_ref for them.**
- **C11 (deferred):** `ref_hybrid` ΔL_ref for the D-T6 room set. Run it only after D-T6 is decided, so the bound is fixed before any number it would be tested against.

---

## Summary
| id | decision | state | worst-off seat | sum | confidence | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| D-T1 | formulation (T1-A, T1-B, T1-F); seed; N rule; τ and SE; case set | convening (9/9 seats), RQ-T1-1…4, C3–C9 | – | – | – | NFR-1, NFR-2, NFR-6/AX5, NFR-8, FR-SIM-6, AX6 | Kuttruff Eqs. 4.24, 4.29, 4.35; Vorländer §11 Fig. 11.38 (to re-read) | – |
| D-T2 | L2-P, or L2-F1 / L2-F2 | convening (9/9 seats), C9 | – | – | – | AX36 (settled < 1 % rule) | – | – |
| D-T6 | RS-1 or RS-2; B6-1 or B6-2; M-1 or M-2 | convening (seats 1, 2, 3, 5, 9), C10 (C11 deferred) | – | – | – | NFR-1 | Vorländer Table 6.1; Kuttruff §5.2 | – |
| D-T3 | – | not convened (needed only if T1-A wins) | – | – | – | AX6, FR-SIM-6 | – | – |

## Challenges to settled decisions
- **None raised.** One option was dropped at bounds because it would contradict phase-05b2 §3 and AX36: "the < 1 % rule does not transfer to Monte Carlo". If a seat argues for it, it comes to Maisara as a challenge in the decision round.
- I found no conflict between `board.md` §1 and the PRD.

## For Maisara
- **D-T1 (convening):** all nine seats are asked how to compute the new tail level in the plugin. There are three ways:
  - an exact port of the validated model, which cannot fit large rooms and would force a room-size limit;
  - a slower exact method that fits in memory;
  - a fast random-sampling estimate, which needs little memory but carries a small random error.

  The seats also rate how precise the estimate must be and what it is tested against. Nothing is decided.
- **D-T2 (convening):** the precision rule that goes with that choice. The strictest reading costs about 33× more computation.
- **D-T6 (convening):** five seats are asked how much the tail level may change in rooms where the old method was already exact. The bound is fixed before any test result exists. No veto-grade override is pending.

**CONVENE**

Files:
- /home/user/makroof/docs/phases/phase-05b2.md
- /home/user/makroof/docs/review/phase-05b2/5-decider-decision-T5-T4.md
- /home/user/makroof/docs/review/phase-05b2/7-builder-D-T1-evidence.md
- /home/user/makroof/docs/review/phase-05b2/2-orchestrator-C2-dLb-all-bands.md
- /home/user/makroof/tools/validation/phase05b2_dt1.py
- /home/user/makroof/docs/validation/report-phase05b.md
- /home/user/makroof/src/contract/Validate.cpp
- /home/user/makroof/tests/scenes/valid/stone_box.json
