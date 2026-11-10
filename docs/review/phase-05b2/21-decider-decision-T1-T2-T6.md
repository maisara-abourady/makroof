# Decider — decision round, D-T1, D-T2 and D-T6

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

# Decider: decision round for D-T1, D-T2 and D-T6 (phase 05b session 2)

**What is decided and what is not.**
- **Decided (proposed, for the interrogator):** D-T1.1 = **T1-F**, D-T1.2 = **S-1**, D-T1.4 = **Tol-2**, D-T1.5 = **CS-3 + CS-NW+** with Seat 1's pre-registered agreement rule, and D-T6 = **RS-2+ / B6-1F / M-2**.
- **Not decided: D-T1.3 and D-T1.6.** Every rated option there tops out at 2. Seat 2's NW-4 was measured after the round, and I compose a variant around it (**NW-4C**, with the work-capped N rule **N-3W\***). All nine seats must rate it after computation C12.
- **Not decided: D-T2.** L2-F2 is vetoed (Seat 5, later 3). L2-F1's low cells rest on a premise the arithmetic contradicts. It goes to a second round (L2-F1R), and in parallel a challenge goes to Maisara on how AX36 applies to an estimator.
- **D-T3 is not needed.** T1-F covers AX6 in < 2 MB, and at 100 m it agrees with an independent tracer to −0.009 dB (C7).

**Corpus revision:** `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`. Re-read this round: Vorländer Table 6.1 (L2056–2064, G jnd 1 dB at 500–1000 Hz) and §11 Fig. 11.38 (L3386–3388, diffuse rain sends scattered energy to a detector sphere).

**PRD digest:** unchanged from `9-decider-convene-T1-T2-T6.md`. The bounds in play are NFR-1, NFR-2, NFR-3/FR-SIM-6, NFR-6/AX5, NFR-8, AX6 (0.1 m listener and emitter clearance, from the code) and AX36's per-quantity < 1 % rule (accepted by Maisara 2026-11-09). Contract unchanged. Challenge 1 (the 100 m restore gate) is still pending with Maisara.

**Inputs:**
- seat positions: `18-seat1…9-*.md`;
- researcher dossier: `14-researcher-T1-T2.md` (NOT READY on RQ-T1-4 only);
- computations and evidence: `7-builder-D-T1-evidence.md`, `16-orchestrator-C4-near-wall.md`, `19-orchestrator-NW4-and-checks.md` (including §6, late evidence), `20-orchestrator-C7-ref-costs-100m.md`, and `phase05b2_dt1.json` (c5, c6, c8, c10).

Cells below are written `now/later`. Cells marked † are read from the seat's stated conditions.

---

## D-T1.1 Formulation

### Tension map

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max |
|---|---|---|---|---|---|---|---|---|---|---|
| **T1-F** | 1/1 | 1/1 | 1/1ᶜ | 1/1ᶜ | 1/2 → **1/1†** (D1–D6) | 1/1ᶜ | 1/1ᶜ | 1/1 | 1/1 | 1 (pending the ᶜ cells) |
| T1-B | 2/2 | 2/2 | 2/**3** | 2/2 | **3/3** | **3/3** | 2/**3** | **3/3** | 1/2 | 3 |
| T1-A | 1/2 | 2/2 | **3/3** | 2/2 | 2/**3** | **3/3** | 2/2 | **3/3** | **3/3** | 3 |

ᶜ marks a cell that each seat made conditional on other sub-decisions:
- **S3:** 1/1 "with NW-3, or NW-1 under N-3 with a time-bounded N_max; later 2 otherwise".
- **S4:** later 2 under L2-F2.
- **S6:** 1/2 under NW-1, 3 under NW-1 with L2-F2.
- **S7:** later 2 unless all of its item-6 conditions are met:
  - N-3;
  - NW-3 or NW-2;
  - CS-NW;
  - the cross-machine set;
  - a cross-OS E_target comparison in CI;
  - the wording.

The seats' reasons, in their own words:
- **T1-F:** "same model; < 2 MB" (S2); "no published validation (RQ-T1-4)" (S1, S7, S8, S9).
- **S5 on T1-F:** later 2 because "libm differs across MSVC, glibc and Apple (F19). FMA defaults also differ…", which breaks AX5 across architectures. Its own words: "T1-F, 1/2 → 1/1 (the determinism package)".
- **T1-B vetoes:** "≈ 9 s per rebuild in the AQ10 room… minutes to hours at 100 m" (S5, S6, S8; S3 later; S7 later).
- **T1-A vetoes:** "forces D-T3… fails CR4 at 1 GB" (S3, S6, S8, S9).

### Working
1. **Bounds:** no option breaks a PRD bound.
2. **Vetoes:** T1-A and T1-B are dropped. T1-F is the only survivor.
3. **Composition (T1-F\*):** T1-F plus Seat 5's determinism package and Seat 7's cross-OS and wording conditions. This lowers S5 from 2 to 1†. The ᶜ cells are resolved by D-T1.3, D-T1.6 and D-T2, so T1-F's final maximum is not known yet. That does not change the choice, because nothing else survives.

### DECISION D-T1.1 = T1-F\*
**The estimator.** Seeded Monte Carlo with next-event estimation of the propagated diffuse energy (builder evidence §2). It is the ℓ → 0 form of `ref_hybrid`: injection s(1−α) per Kuttruff Eq. 4.24, transport per Eq. 4.35 over the listener's lattice images, gather per Eq. 4.29, AX4 air, and the `matchTail` window. Specular entries stay exact (ISM). Near-listener handling is set by D-T1.6; the path count by D-T1.3.

**Determinism package (Seat 5's conditions):**
- **D1.** No libm call in any value that decides a branch or a path. Directions are sampled with +, ×, ÷, sqrt and comparisons only. The RNG counter is keyed by (seed, start end, emitter, path, hit, attempt). libm is used in scores only.
- **D2.** `-ffp-contract=off` on gcc and clang for `src/sim`, `/fp:precise` on MSVC, no fast-math.
- **D3.** A known-answer test of the counter-based RNG on all three CI platforms. No `<random>` distributions (F16).
- **D4.** Fixed path blocks whose boundaries do not depend on the thread count, reduced in block order. Stratification, if any, does not depend on N: the prototype's √N grid is not copied (Seat 2, Seat 5). The SE estimator must match the sampling design.
- **D5.** A committed golden integer hash of every path's face sequence, required to be equal on all three CI platforms.
- **D6.** The stop flag is checked between batches, and a cancelled solve is discarded.
- **Threads:** one process-wide pool owned with the D-T4a gate, created at prepare, with at most hardware_concurrency − 2 threads [Hyp] at normal priority. The callback p99.9 record runs with the pool busy (Seat 5).

**Seat 7's conditions:**
- CI compares E_target across the three OSes on the agreement set and CS-NW, and reports it against AX5's −100 dBFS.
- Public wording follows Seat 7's allowed and forbidden lists:
  - no "validated" without the named test;
  - no "validated method";
  - no claim of "matches real rooms";
  - no accuracy claim near walls beyond CS-NW;
  - the method notes name the diffuse-rain family (F22) as class membership only.

**Seat 4's condition:** the diffuse solve runs once per scene and is shared across output modes.

### Load-bearing claims
- **D1-L1 (seats' words):** the vetoes on T1-A and T1-B, as in the map above.
- **D1-L2 (computed, 19 §5):** (f) vs `ref_hybrid` (ℓ = 1.25 m), 15 (A) cases, all 8 bands: max |Δ| 0.088 dB, max |z| 1.29, mean z −0.11.
- **D1-L3 (computed, 20 §2):** 100 m cube. (f) − tracer = −0.009 dB (SE 0.022 dB each; tracer N₀ = 254·V). (f) − `ref_hybrid` at ℓ = 10 m = −0.031 dB (20 → 10 m change 0.077 %). This holds for one pair, band-flat α.
- **D1-L4 (computed, 19 §2 and §6):** in `dead_booth`, `living_room`, `classroom` and `small_room` the reference converges onto (f) as ℓ shrinks.
- **D1-L5 (code, Seat 2):** `mc2` matches `ref_hybrid`'s `injection`, `gather_kernel` and transport line by line. Broadband branching is unbiased because s is band-independent (AQ3).
- **D1-L6 (corpus and researcher):** diffuse rain is a published method class (Vorländer Fig. 11.38; F22). No published bias or variance validation exists (RQ-T1-4 uninformed). So "validated" means only the in-repo checks D1-L2 to D1-L4.
- **D1-L7 (C5, one platform):** a 1e-9 m perturbation changes E_target by ≤ 2.7e-10 dB, and float32 path state by ≤ 7.5e-8 dB. No path changed its face sequence. Results are bit-identical with 1, 2 and 4 threads. Whether results agree across architectures depends on D1–D2 (F19, F20).

### Future-debt register

| seat | what later phases are committed to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| S1, S7, S8, S9 | an estimator with no published validation; the claim rests on in-repo checks | estimator fix, not a rewrite (S9) | nightly BRAS; RQ-T1-4 if Schröder 2011 is obtained | Schröder 2011 obtained, or the BRAS nightly holds |
| S2 | one more link in the validation chain (MC → ref → tracer); per-band s (B10) needs weighted branching | parameter-level change | B10 | B10 |
| S3, S6 | build cost depends on listener position | D-T1.6 | C12 and round 2 | D-T1.6 decided |
| S4 | E_b cost shared across modes (later 2 if L2-F2) | split-update AX | D-T2, Phase 08 item 8 | D-T2 decided |
| S5† | D1–D6 kept for good; face-hash golden | low | CI on three OSes | permanent gate |

**Strongest objection.** S5's cell is read from its conditions. If Seat 5 finds D1–D6 insufficient for cross-architecture AX5 (glibc runtime dispatch, its open researcher check), it stays 1/2. T1-F still wins, because both alternatives are vetoed.

**Confidence:** medium (RQ-T1-4 uninformed; one cell read from conditions).

**Reversal:**
- a C++ stage-2 agreement fail that is traced to the estimator rather than the implementation; or
- face-hash mismatch across platforms with a cross-OS E_target residual above −100 dBFS; or
- a published diffuse-rain bias figure that contradicts D1-L2 or D1-L3.

---

## D-T1.2 Seed

### Tension map

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| **S-1** | 0/0 | 0/0 | 0/1 | 0/0 | 0/0 | 0/0 | 0/0 | 0/0 | 0/1 | 1 | 2 |
| S-2 | 0/1 | 1/1 | 1/1 | 1/1 | 0/1 | 1/**2** | 1/**2** | 1/1 | 0/0 | 2 | 16 |

### Working
No vetoes. On the worst-off seat, S-1 (max 1) beats S-2 (max 2).

### DECISION D-T1.2 = S-1
The RNG key is (fixed constant, start end, emitter index, path index…). E_target does not depend on tailSeed. A tailSeed edit regenerates noise only.

### Load-bearing claims
- **D2-L1 (seats):** S-2 makes tailSeed a hidden level control (S6, later 2), and its ensembles would average away a Monte Carlo error that no single render has (S7, later 2).

### Future-debt register

| seat | what later phases are committed to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| S3 | τ must budget the fixed per-scene offset explicitly | none extra; it is in D-T1.4/1.5's rule | agreement test | it passes |
| S9 | the per-scene offset sits inside every AX11/AX19 ensemble, and its σ is left out of the validation spread | key change, one golden round | BRAS nightly report | the report prints the Monte Carlo SE beside the ensemble spread |

**Confidence:** high. **Reversal:** a validation result whose error budget needs the Monte Carlo spread inside the ensembles (Seat 9).

---

## D-T1.4 Tolerance τ (SE target τ/3)

### Tension map

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| Tol-1 | 2/2 | **3/3** | 2/2 | 1/1 | 0/1 | 1/2 | 1/2 | 2/2 | 2/**3** | 3 | – |
| **Tol-2** | 0/0 | 1/1 | 0/1 | 0/0 | 1/1 | 1/1 | 1/0 | 0/0 | 0/1 | 1 | 9 |
| Tol-3 | 0/1 | 1/1 (under L2-F1) | 1/2 | 0/1 | 2/2 | 1/2 | 1/1 | 0/1 | 1/2 | 2 | 20 |

### Working
Tol-1 is vetoed (S2: "τ = 1 dB passes a C++ that kept AX16"; S9). Tol-2 wins on the worst-off seat (max 1 against 2).

### DECISION D-T1.4 = Tol-2
- τ = 0.25 dB per case and band, C++ against the reference, and τ includes the reference's own ℓ term.
- Shipped SE target = 0.083 dB (τ/3, AX11 convention), **unless D-T2's outcome sets a stricter shipped SE**.
- τ also bounds the D-T5.4 `open_field` check and D-T6.

### Load-bearing claims
- **D4-L1 (corpus):** the G jnd is 1 dB (Vorländer Table 6.1, 500–1000 Hz; other bands by extension). τ is ¼ jnd, and SE 0.083 dB is 0.08 jnd.
- **D4-L2 (C2, computed):** AX16 vs hybrid is ≤ 0.43 dB in the uniform cases. τ = 1 dB therefore cannot detect AX16 left in place, which is the basis of the veto.
- **D4-L3 (product):** τ = 0.25 dB matches gate (B)'s δ of 0.25 jnd. This is a judgement anchored on D4-L1 and AQ9.

### Future-debt register

| seat | what later phases are committed to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| S2, S5, S6 | build cost at SE 0.083 dB (ms in typical rooms; ≈ 1.5 s in layout 4 at s = 1 at reference positions) | parameter change | C++ W1/W2 (O15) | recorded |
| S3 | SE target overridden if D-T2 binds | – | D-T2 | D-T2 decided |
| S9 | the reference's ℓ term must fit inside τ in small rooms | per-room ℓ ladder (D-T1.5) | 19 §2/§6: ≤ 0.58 % at 2.5 m | already met at finer rungs |

**Confidence:** high. **Reversal:** a measured case whose reference ℓ term exceeds τ/2, or a Seat 1 source showing that tail-level steps below 0.25 dB are detectable.

---

## D-T1.5 Agreement case set and decision rule

### Tension map

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| **CS-3 + NW** | 0/0 | 0/1 | 0/1 | 0/0 | 0/0 | 0/1 | 1/0 | 0/0 | 0/0 | 1 | 4 |
| CS-2 + NW | 1/1 | 1/1 | 0/1 | 0/0 | 0/0 | 0/1 | 1/0 | 0/1 | 1/**2** | 2 | 11 |
| CS-1 | 2/2 | 2/2 | 1/2 | 0/1 | 0/1 | 1/2 | 0/2 | 2/2 | 2/2 | 2 | – |

### Working
CS-3 + NW wins on max (1). Then step 4: I compose **CS-3 + CS-NW+** from conditions, adding:
- Seat 9's 0.3 m listener position;
- C4's W1 emitter-at-the-wall case, which covers the start end that D-T1.6 may move the problem to;
- Seat 2's per-room reference ladder;
- Seat 5's CI arrangement;
- Seat 1's decision rule.

No seat's cell rises, apart from S5's CI-cost cell, which I read from Seat 5's condition (†).

### DECISION D-T1.5 = CS-3 + CS-NW+
**Cases, all 8 bands:**
- the 15 (A) cases;
- the six Phase 04 rooms (both emitters);
- W1 and W2;
- the 30 BRAS pairs;
- CS-NW+: W1 listener at 0.1 m from a wall, an edge and a corner; at 0.3 m from a wall; and the emitter at 0.1 m from a wall.

Layout-4 near-wall cases are reported, not gated: the reference there is not certified (4.75 % per halving, C4).

**Reference per case:** `ref_hybrid` at the finest computed rung whose last halving changed it by < 1 %. That change is recorded as the case's ℓ_ref (small rooms per 19 §2/§6). The reference is exported once as a golden through the script, with its reason in the CHANGELOG.

**Decision rule (Seat 1), pre-registered before any C++ number:**
- **Family rule.** z_FW is the Bonferroni z for a family α of 1 % over the pre-registered number of case-bands. The test N per case is chosen so that z_FW·SE_test ≤ τ − ℓ_ref.
- **Pooled bias check.** Per band, |mean signed z| ≤ 3/√M.
- **On a fail.** No reseed, no extra N for the failing case, no wider τ, no dropped case. Instead, stage 2 re-runs all cases on a disjoint, pre-registered path range at 4× N, and the decision rests on stage 2 alone. A stage-2 fail is a defect, or goes to Maisara if the reference's ℓ is the cause.

**CI (Seat 5):** the suite runs under a hidden tag from the Release build on three OSes. Debug, ASan and TSan run one smoke case.

### Load-bearing claims
- **D5-L1 (C7):** every reference in CS-3 is computable, ≤ 2.5 GB (CR4), and exported once it costs CI nothing.
- **D5-L2 (C4):** without CS-NW no case has the listener within 0.5 m of a surface (seats 1–9 concur).
- **D5-L3 (19 §3):** cross-band correlation of (f) is ≥ 0.978. Case-bands are therefore near-fully correlated, and Bonferroni is conservative.

### Future-debt register

| seat | what later phases are committed to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| S2 | the reference ladder must be kept per room | script | – | permanent |
| S3, S6 | CI time is Seat 5's to carry | move BRAS to nightly (Seat 9's variant) | first CI run | recorded |
| S5† | test N ≈ 2.6× shipping N, plus a possible stage 2 | nightly move | first CI run | recorded |
| S7 (now 1) | contractor time on a larger suite | – | – | – |

**Confidence:** medium (S5 cost read from conditions). **Reversal:** a Release CI run of the suite beyond Seat 5's budget, in which case the BRAS pairs move to the nightly (Seat 9's variant, which it also rated 0/0).

---

## D-T1.3 and D-T1.6: not decided; a composed variant must be rated

### Tension maps of the rated options

| D-T1.6 | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| NW-3 | 0/1 | 1/**2** | 1/1 | 0/1 | 0/1 | 1/1 | 1/1 | 0/1 | 1/1 | 2 | 15 |
| NW-2 | 1/1 | 2/2 | 1/2 | 0/1 | 1/1 | 1/2 | 1/1 | 1/1 | 1/1 | 2 | 21 |
| NW-1 | 2/2 | 1/2 | 2/2 | 1/2 | 1/2 | 2/2 | 1/2 | 2/2 | 1/2 | 2 | 31 |
| NW-4 | – | 0/1 | – | – | – | – | – | – | – | unrated by 8 seats | – |

| D-T1.3 | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max |
|---|---|---|---|---|---|---|---|---|---|---|
| N-1 | 2/2 | 2/**3** | 2/2 | 1/2 | 2/2 | 2/2 | 1/2 | 2/2 | **3/3** (NW-1) | 3 |
| N-2 | 1/1 | 1/2 | 1/2 | 0/1 | 1/2 | 1/2 | 1/2 | 1/1 | 1/1 | 2 |
| N-3 | 0/1 | 1/1 | 1/2 (gate coupling) | 0/1 | 1/2 | 1/1 (NW-3) | 1/1 | 1/1 | 0/1 | 2 |
| N-3W (S5's own) | – | – | – | – | 1/1 | – | – | – | – | unrated |

### Why I cannot decide
1. **NW-3 leads on sum, but its Seat 2 condition cannot be met.** Seat 2's condition for lowering NW-3 to 1 is "a long-run clamp-bias measurement in layout 4/5… and τ budgeted for it". The late evidence (19 §4 and §6) puts the clamp at:
   - −0.11 / −0.25 dB at the layout-4 wall and edge (against NW-4);
   - +0.109 dB at the absorbing floor in layout 4;
   - **+0.322 dB at the absorbing wall in layout 5**.

   The last exceeds the whole τ = 0.25 dB just decided, so there is no room to budget the clamp's bias.
2. **Five seats' NW-3 cells rest on a premise the new data change.** Seats 1, 4, 7, 8 and 9 rated NW-3 on "+0.03 to +0.09 dB (W1)". Seat 1's later 1 cites "the shift in layout 4 is unmeasured". I do not re-rate them; they must be asked.
3. **NW-4 was measured after the round, but only Seat 2 rated it.** NW-4 removes the heavy tail at the listener: in W1 at a wall, edge or corner, SE is 0.013–0.015 dB at 32 k paths, within 0.04 dB of the long runs. In layout 4 near walls, SE is ≈ 0.07 dB, and the edge is +0.04 dB against the 1.25 m reference (19 §1). It does this without biasing the model. But it moves the problem to an emitter near a wall, and a start-end switch would add a random step.

### Composed variant for the second round (one per id)

**NW-4C (D-T1.6).** Composed from Seat 2's NW-4, Seat 3's "a blend… instead of a switch" and Seat 9's NW-1 condition.
- Per emitter, E_diffuse = w·E_fwd + (1 − w)·E_rev:
  - E_fwd: paths started at the emitter, gathered at the listener's images;
  - E_rev: paths started at the listener, gathered at the emitter's images; one listener-started set serves both emitters;
  - w = d_L² / (d_L² + d_E²), where d is that endpoint's distance to the nearest surface.
- Why this is unbiased and continuous:
  - Both estimators are unbiased, so the combination is unbiased for every w.
  - w is continuous in position, so there is no switch.
  - The weight follows F3's near-wall variance term ∝ 1/d² at the gather end, i.e. inverse-variance weighting. This is my derivation from F3, which is itself derived and unsourced.
- **No clamp, so no model change.**
- When both endpoints are near walls the cost reverts to NW-1's. That case is capped by N-3W\* and flagged "near-wall, unreferenced" (Seat 9) in TailMatch and the diagnostics.

**N-3W\* (D-T1.3).** Seat 5's N-3W with Seats 1, 3 and 6's conditions folded in.
- **Pilot:** a pilot range [0, n*) with n* = 8 000 (a product choice, to be rated) sets N from its SE.
- **Final estimate:** taken from a disjoint, fixed-start range [n*, n* + N), so it is fresh (F14) and its start does not depend on N (Seat 4).
- **Diagnostics:** R, VOV and slope (F8–F10) are computed and flagged, not iterated on.
- **Work cap:** a deterministic cap W_max counted in image evaluations. It is derived as Seat 5 states: two emitters must fit in the restore bound minus the existing build time at the gated scene. It is also bounded by:
  - at most 3 s per emitter on the CI runner (Seats 3 and 6);
  - at least Seat 1's floor: C4's worst cases reach SE ≤ 0.33 dB with VOV < 0.1.

  If these bounds conflict, the conflict goes back to the seats.
- **Cap hits:** a deterministic flag. Escalation happens in CI and `render_cli` only.

### Orchestrator computations needed before the second round (C12)
- **(a)** NW-4C on C4's cases (listener or emitter at the wall, edge or corner), on new both-near cases (listener and emitter each at 0.1 m), and on Seat 9's absorbing-face cases, in W1 and in layouts 4 and 5. Report SE at 32 k, the largest path share, and the difference from the long runs or the reference.
- **(b)** 1 cm sweeps under N-3W\* at Tol-2:
  - the listener from 1 m to 0.1 m off a wall, along a wall, and into a corner;
  - an emitter crossing d_E = d_L;
  - both moving together.

  Report the largest neighbour step per band and the range of N.
- **(c)** The cost of NW-4C against forward-only at the reference positions in W1, W2, CR4 and the 100 m cube.
- **(d)** W_max in image evaluations, from the Phase 07 restore times (1.51–1.88 s at 100 m, 96 kHz). Report:
  - the paths it allows in each scene above;
  - whether Seat 1's floor and the 3 s bound are both met;
  - the cap-hit rate on CS-NW+ and on the six Phase 04 rooms with first the listener and then one emitter at 0.1 m from a wall (Seat 7).
- **(e)** R, VOV and slope on the pilot in those scenes.

**Second-round brief (all nine seats).** Rate NW-4C and N-3W\* now and later, with conditions, reading C12 and 19 §1/§4/§6. Re-rate NW-3 on its measured bias (+0.322 dB in layout 5). Seat 5 confirms its T1-F† cell. Seat 7 says whether NW-4C meets its "NW-3 or NW-2" condition.

---

## D-T2 Resolution rule for T1-F: second round, then NEEDS MAISARA

### Tension map

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| L2-F2 | 2/2 | 1/1 | 2/2 | 1/2 | 2/**3** | 2/2 (NW-3), 2/**3** (NW-1) | 2/2 | 2/2 | 0/1 | 3 | – |
| L2-F1 | 2/2 | 2/2 | 2/2 | 1/1 | 0/1 | 1/1 | 1/2 | 1/1 | 1/2 | 2 | 25 |

### Working
- L2-F2 is vetoed. Seat 5: "a 100 m restore gains 2.4–3.0 s even with 4 threads… 55–69 s against 30 s."
- L2-F1 survives at max 2. **However, I think Seats 4, 5, 6 and 8 have misjudged its cost.** I state this separately and do not re-rate them. They rated it as keeping Tol-2's costs ("deterministic run at N and 2N… runs once"; "keeps Tol-2 costs").

**My arithmetic, for the interrogator to redo:**
- At Tol-2's N the shipped SE is 1.911 % (0.083 dB ÷ 4.343).
- The doubling difference has SD = SE/√2 = 1.351 %. So P(|Δ| < 1 %) = 2Φ(0.740) − 1 = 0.541 per case. This is Seat 2's 0.54.
- Bands are correlated ≥ 0.978, so treat each case as about one test. Over roughly 50 cases in CS-3 + CS-NW+, the certification fails with near certainty (0.54⁵⁰ ≈ 4·10⁻¹⁴).
- AX36 then requires the next rung. To pass each case with p ≥ 0.999: 3.29·SE/√2 ≤ 1 %, so SE ≤ 0.430 % (0.0187 dB), which is **≈ 19.8× Tol-2's paths**.
- Scaling the prototype to that: W1 36–50 ms per emitter; 100 m cube 2.85–3.62 s per emitter (single thread); layout 4 at s = 1 ≈ 30 s.

I call this corrected option **L2-F1R** and send it to the second round for all nine seats.

### Challenge to Maisara (raised by Seats 1, 3, 7 and 8; Seat 2 holds the strict reading)
AX36's < 1 % rule certifies a discretisation, whose error is systematic. A Monte Carlo estimator has no systematic error, only a random error that the SE measures.

**The bias reading** (Seat 1's form): in CI, at a pre-registered high N with 3·SE ≤ 1 %, the pooled mean deviation of the estimator from the converged reference must be < 1 % in every band. The shipped per-scene SE is then governed by D-T1.4 (0.083 dB, 0.08 jnd).

| | bias reading | strict reading |
|---|---|---|
| shipped cost | Tol-2's | L2-F1R (≈ 20×) or L2-F2 (≈ 33×) |
| precision bought | – | 0.0145–0.019 dB, about 1/50–1/70 of the G jnd |
| what it requires | Maisara accepts the reading | an override of Seat 5's veto, if round 2 confirms one |

The bias reading departs from how the convening read "under the same per-quantity < 1 % rule": the convening dropped L2-F3 at bounds. Only Maisara can accept it.

**State:** a second round on L2-F1R. If any seat rates it 3, D-T2 is **NEEDS MAISARA**: the bias reading, or a veto override.

**Coupling:** D-T1.4's shipped SE target of 0.083 dB holds only under the bias reading.

---

## D-T6 Regression bound in uniform-α rooms
Convened: Seats 1, 2, 3, 5 and 9. Seats 4, 6, 7 and 8 were not required and score 0/0 (reasons in the convening table).

### Tension map

| option | S1 | S2 | S3 | S5 | S9 | max | sum |
|---|---|---|---|---|---|---|---|
| RS-1 | 1/1 | 2/2 | 1/1 | 0/1 | 1/2 | 2 | 12 |
| RS-2 | 0/0 | 0/1 | 0/1 | 0/0 | 0/1 | 1 | 3 |
| **RS-2+** (Seat 9's option; Seat 2's addition) | 0/0† | 0/0† | 0/1† | 0/0† | 0/0 | 1 | 1 |
| **B6-1** | 0/1 | 0/0 | 0/1 | 0/1 | 0/1 | 1 | 4 |
| B6-2 (Tol-2) | 1/2 | 2/2 | 1/2 | 1/1 | 1/2 | 2 | 15 |
| M-1 | 1/1 | 1/2 | 1/1 | 0/0 | 1/2 | 2 | 10 |
| **M-2** | 0/0 | 0/0 | 0/1 | 0/0 | 1/0 | 1 | 2 |

How the † cells are read:
- **S2's** RS-2 later 1 cites the missing small room, which RS-2+ adds.
- **S1, S3 and S5** gave reasons on RS-2 that a fifth small room does not touch.

### Working
No vetoes (B6-2 at Tol-1 is out with Tol-1). On max and sum: RS-2+, B6-1 and M-2.

Step 4, composition **B6-1F:** B6-1 is gated, and B6-2's bound is printed as a flag only. These are Seats 2 and 3's own variants, so no cell rises.

Seat 9's flag that W1 is not a blind case is handled by B6-1. Its bound is a formula, |ΔL_C++ − ΔL_ref| ≤ τ, not a number fitted after W1's prototype value was seen.

### DECISION D-T6 = RS-2+ / B6-1F / M-2

**Room set:**
- `stone_box`;
- W1 (both emitters);
- the three (A) s-cases;
- a synthetic small uniform room, fixed now before C11 (Seat 9):
  - 3 × 2.5 × 2.5 m, α = 0.03 in all bands, s = 0.1;
  - positions are AX28's scaled per axis: listener (1.5, 0.667, 0.425) m, emitters (1.05, 1.667, 0.5) and (1.95, 1.667, 0.5) m;
  - its reference is laddered to < 1 %.

**Gate:**
- |ΔL_C++,b − ΔL_ref,b| ≤ τ = 0.25 dB per emitter and band, all 8 bands.
- ΔL is taken within one `--diagnostics` run (AX16 and diffuse E_target side by side).
- ΔL_ref comes from `ref_hybrid` (C11, run only now), exported as a golden by script and regenerated whenever `ref_hybrid` changes.
- The gate runs in PR CI on three OSes, in the same push as the switch (§8).

**Flags, not gates:**
- |ΔL_ref| and |ΔL_C++| > 0.43 + τ = 0.68 dB, reported as a physics finding (Seat 2).
- Seat 1's |mean| > 0.5 jnd.

**Report, not gated:**
- Paired before and after with the same binary and tailSeed, through a validation-only `render_cli` flag that renders the AX16 tail level (Seat 5).
- R ≥ 30 seeds (Seat 1's R, which covers Seat 3's 16).
- ΔG, ΔC80, ΔEDT and ΔT30, plus the seam step (Seat 3's `test_envelope_step_reported` metric), all 8 bands.
- jnd units at 500–1000 Hz, "by extension" elsewhere.
- Scope: RS-2+, the mixed rooms and the listening-pack scenes.
- Seat 3's plumbing check (rendered tail ΔL against the diagnostics) is reported only; gating it needs a derived tolerance.
- The EDC seam gate keeps running; a failure is a finding.

**Mixed-α rooms (M-2):** `ref_hybrid` plus new tracer runs (500 Hz–2 kHz window) on `dead_booth`, `living_room`, `classroom`, `club` and `concert_hall_box`.
- The tracer's r_d is below the listener clearance and is run at two radii (Seat 2, F2). Seat 9 checks this against `dead_booth`.
- Data are committed with seed and statistics (Seat 5).
- Results are reported, not bounded.

### Load-bearing claims
- **D6-L1 (C10, from the code):** the uniform-α fixtures are `stone_box`, W1 and the (A) s-cases only.
- **D6-L2 (C2):** 0.43 dB comes from one geometry (α 0.15, s ≤ 0.4, 20×30×10 m). So B6-2 is not an a priori bound (Seats 1, 2, 3, 9).
- **D6-L3 (corpus):** the G jnd is 1 dB (Table 6.1).

### Future-debt register

| seat | what later phases are committed to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| S1 | audibility rests on the report, not the gate | optional ABX on `stone_box` | report | Maisara's listening |
| S3 | M-2: tracer runs per mixed room; RS-2: the s = 0.4 coverage | – | – | – |
| S5 | the ΔL_ref golden is regenerated whenever `ref_hybrid` changes | script | – | permanent |
| S9 | B6-1 later 1 | – | C11 | gate passes |
| S9 (now 1) | M-2 tracer cost | – | – | – |

**Confidence:** medium (four cells read from conditions). **Reversal:** C11 shows |ΔL_ref| beyond its prediction in the small room (a physics finding, reported), or a stage-2 gate failure.

---

## Summary

| id | decision | state | worst-off (cell) | sum | conf. | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| D-T1.1 | T1-F\* (MC-NEE + D1–D6, cross-OS comparison, wording) | proposed | pending ᶜ cells; S5 1/1† | 18 | medium | NFR-1, NFR-2, NFR-6/AX5, AX6 | Kuttruff Eqs. 4.24, 4.29, 4.35; Vorländer Fig. 11.38 | estimator-caused stage-2 fail; face-hash mismatch |
| D-T1.2 | S-1 (fixed key) | proposed | S3, S9 0/1 | 2 | high | NFR-6 | – | validation needs MC spread |
| D-T1.4 | Tol-2: τ 0.25 dB, SE 0.083 dB unless D-T2 binds | proposed | 1 | 9 | high | NFR-1 | Vorländer Table 6.1 | ℓ_ref > τ/2; step-detectability source |
| D-T1.5 | CS-3 + CS-NW+, ladders, Seat 1's rule, Release CI | proposed | 1 (S5†) | 4 | medium | NFR-1, NFR-8 | – | CI budget → BRAS nightly |
| D-T1.3 | N-3W\* | second round (C12, 9 seats) | – | – | – | FR-SIM-6, NFR-2 | – | – |
| D-T1.6 | NW-4C | second round (C12, 9 seats) | – | – | – | FR-SIM-6, NFR-8 | – | – |
| D-T2 | L2-F1R round 2, then Maisara | needs Maisara (pending round 2) | L2-F2 S5 2/3 | – | – | AX36 | – | her ruling |
| D-T6 | RS-2+ (small room fixed now) / B6-1F / M-2 | proposed | 1 | 7 | medium | NFR-1 | Table 6.1 | C11 physics finding |
| D-T3 | – | not needed | – | – | – | AX6 | – | – |

## Challenges to settled decisions
1. **AX36 applied to an estimator (D-T2).** Raised by Seats 1, 3, 7 and 8, with the numbers above. Maisara chooses the bias reading, or the strict reading with a veto override.
2. **Challenge 1 (100 m restore gate) is still open.** N-3W\*'s W_max is derived from its ≈ 2.1 s bound, and her answer fixes whether that bound blocks.

No conflict found between `board.md` §1 and the PRD.

## For Maisara
- **D-T1.1:** the tail level is computed by a seeded random-sampling estimate of the validated model.
  - It fits every room size in under 2 MB, and at 100 m it agrees with an independent ray tracer to 0.01 dB.
  - The exact-port options were vetoed: one cannot fit large rooms, the other takes seconds to hours per change.
  - Seat 5 gave the most and gets a determinism package so saved projects match across machines.
- **D-T1.2:** the noise seed changes only the texture of the tail, never its level.
- **D-T1.4:** the C++ must match the reference within 0.25 dB, a quarter of the smallest audible level change.
- **D-T1.5:** it is tested on 64 cases, including real measured rooms and listeners pressed against walls, under a pre-registered rule. A test that fails cannot be retried with a new seed.
- **D-T1.3 and D-T1.6:** a new way to handle listeners near walls, with no model change, goes back to the board after one more measurement.
- **D-T2: your call is likely needed.** Does the 1 % rule apply to the estimator's bias, at today's cost, or to every scene's random error (about 20–33× the cost)? Seat 5 vetoed the strictest version.
- **D-T6:** in uniform rooms, each room must change exactly as the reference model predicts, within 0.25 dB, now including a small room fixed in advance. Mixed rooms get new independent tracer checks.

Files:
- /home/user/makroof/docs/review/phase-05b2/18-seat1-T1-T2-T6.md … 18-seat9-T1-T2-T6.md
- /home/user/makroof/docs/review/phase-05b2/19-orchestrator-NW4-and-checks.md
- /home/user/makroof/docs/review/phase-05b2/20-orchestrator-C7-ref-costs-100m.md
- /home/user/makroof/docs/review/phase-05b2/14-researcher-T1-T2.md
- /home/user/makroof/tools/validation/data/phase05b2_dt1.json
