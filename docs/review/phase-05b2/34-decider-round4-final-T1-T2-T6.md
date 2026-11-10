# Decider — final round 4, D-T1, D-T2 and D-T6

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

# Decider, final round 4: D-T1, D-T2 and D-T6 (phase 05b session 2, 2026-11-10)

**Outcome.** Every id survived the interrogator's round 2, and none changes winner. This round applies corrections 1–14, answers the four questions, adds the conditions from Seat 2 (S2-a), Seat 4 (S4-a) and Seat 6 (S6-a), and takes in C15 and C16.

| id | state |
|---|---|
| D-T1.1, D-T1.2, D-T1.4, D-T1.5, D-T6 | final |
| D-T1.3 | final rule, block size pinned at 64. One seat confirmation pending (Seat 5, question S5-b). W_max and n\*_max provisional until Q2. |
| D-T1.6 | final, with Seat 6's conditions (i) and (ii) and the optional (iii). One seat confirmation pending (Seat 6, S6-b). |
| D-T2 | NEEDS MAISARA (Q1) |
| Work limits | NEEDS MAISARA (Q2) |

**Corpus revision:** `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`.

**New inputs this round:**
- interrogator round 2 (file 32);
- seat confirmations: Seat 2 (30-S2a), Seat 4 (30-S4a), Seat 6 (30-S6a);
- C15: replicate check in the closed 100 m cubes (file 31);
- C16: the joint-rule re-run, where U fires, AX16 against the long runs, and block size (file 33).

**If a pending seat rates veto-grade (3):** this is the last decide/interrogate pair, so the item goes to Maisara with the fallback below.
- Seat 5 → block size 32 (overrun ≤ 7.6 % of W_scene).
- Seat 6 → n\*_max 8 000 (fewer notes on good estimates; C16 (f) reading 4), with Seat 4 then at 2/2.

## A. Answers to corrections 1–14 (all accepted)

| # | answer |
|---|---|
| 1 | Accepted. The D-T1.3 map now has S2 at **0/1**. Its condition, the C15 replicate check, is met: 16/16 rows pass. S4 is **1/1** at n\*_max ≈ 1 024 and **2/2** at 8 000 (30-S4a). Sum: 19 at n\*_max 1 024, 21 at 8 000. The interrogator's "20" misses that S4 moves from 1/1 to 2/2, which adds 2. |
| 2 | Accepted. Seat 4's CI list ("any fixture or preset where the pilot estimate ships") is in D-T1.3 and on the /fix-plan list. |
| 3 | Accepted. **The D4 block is pinned at 64 histories** (C16 (h)). 8 000 = 125 blocks and 1 024 = 16 blocks, so the pilot and the final range starting at 8 000 never overlap. Worst pilot overrun: 15.3 % of W_scene (layout 4 listener_corner); below 10.2 % at every gated 100 m scene. Total work stays bounded by W_scene plus the final range's cost scatter, because N_cap is computed from the work left after the pilot; the overrun shrinks the final range and does not add to the total. Seat 5 is asked (S5-b). |
| 4 | Accepted. The joint-rule re-run is **C16**, now done (file 33). Every cost and SE figure below is joint-rule (C16) unless marked otherwise. |
| 5 | Accepted. "Old error +0.09 / −0.06 dB" is withdrawn. C16 (g) gives the resolved values: AX16 − long run is +0.02 dB (closed s = 0.3 cubes), +0.06 / +0.10 dB (low-α s = 1 cube) and +2.38 / +2.39 dB (absorbing-floor cube). The strongest objection and Q2 are restated. |
| 6 | Accepted. Where the cap binds, the achieved SE is **higher** than the target. The target is met in uncapped scenes at n\*_max 8 000 (≤ 0.082 dB, C14 (b) and C16) and missed by up to 1.5× at about 1 020–1 024 (0.124 dB in C14 (b); 0.108 dB in C16). Linked to Q2b. |
| 7 | Accepted. Seat 6's condition (i) is now in the text: no ±x taken from the achieved SE in the both-near branch, and a ±x in the capped branch only where it is measured. S6 is 1/1 only with (i) in. |
| 8 | Accepted. Seat 6's condition (ii) becomes a **requirement**: no default placement of a valid fixture or Phase 12 preset may raise U, and if one does, the preset's placement is changed, not the predicate. My round-3 reversal "on the predicate at default placements" is withdrawn. |
| 8a | Accepted. Seat 6's condition (iii): U′ = cap hit OR both-near appears only as a labelled diagnostic tier in an advanced view, Phase 11. It answers Seat 2's withdrawn C5 at no audio-thread cost, because the flags live in `TailMatch`, which is built on the builder thread. |
| 9 | Accepted. "Where U fires" is replaced by C16 (f) at both n\*_max values, including the good estimates U also flags. Seat 6 is asked (S6-b). |
| 10 | Accepted. The AX text now says the rise is reduced next to a partially absorbing face and absent at α = 1. |
| 11 | Accepted. ℓ_ref in Q1 (a) is **0.63–0.65 %** (the gated W1 corner at its 1.25 m reference). So the near-wall class needs 3·SE ≤ 0.35–0.37 %, i.e. SE ≈ 0.12 % ≈ 0.0051 dB. CI time only. |
| 12 | Accepted. Precision bought under Q1 (b): **0.0145–0.019 dB, about 1/50–1/70 jnd**. Q1 (a) carries the n\*_max qualifier. |
| 13 | Accepted. Q2's old-error line is restated from C16 (g). |
| 14 | Accepted. The /fix-plan list is complete for rounds 1–4 (§F). |

## B. Answers to the four questions
1. **Seat 6's (i) and the "Where U fires" list.** Yes. Condition (i) is in the D-T1.6 text and the phase-11 entry. The list is corrected from C16 (f), and Seat 6 re-confirms on it (S6-b).
2. **Block size.** 64 histories. 8 000 is a multiple of it. Seat 5 is asked (S5-b).
3. **Q1 (a).** Yes: ℓ_ref = 0.65 %, and a near-wall CI SE of about 0.12 % (0.0051 dB).
4. **The 100 m cubes' "+0.09 / −0.06 dB".** Not kept. It is replaced by C16 (g), measured against 1 M-history long runs with SE 0.005–0.022 dB.

## C. Questions still to put to seats on this final text
- **S5-b (Seat 5), D-T1.3.**
  > The D4 block is pinned at 64 histories. The pilot stops at the first block boundary at or past n\*_max (a multiple of 64: 8 000 or 1 024) or W_scene/2. Its worst overrun is 15.3 % of W_scene (layout-4 class), and below 10.2 % at every gated 100 m scene. Total work is bounded by W_scene plus the final range's cost scatter, which C13 measured at ≤ 1.02 W_max, because N_cap comes from the work left. The final range starts at 8 000 = 125 blocks. Rate N-3W\*\*\* with block 64, now and later. Would you rather have 32 (overrun ≤ 7.6 %)?
- **S6-b (Seat 6), D-T1.6.**
  > This is the corrected "Where U fires" list (C16 (f)), with the note text under your (i), your (ii) as a Phase 12 requirement and (iii) adopted. U also flags good estimates: `living_room` both_wall_0.1 (SE 0.079 dB, replicate p95 0.15 dB) and W1 both_wall_0.3 (SE 0.095 dB, p95 0.49 dB). At n\*_max 1 024 it also flags `club` both_wall_0.3 and 0.5, and `living_room` both_edge_0.3. Under the joint rule at 8 000, `club` both_wall_0.3 is silent. Rate U, now and later, at n\*_max 1 024 and at 8 000.

---

## D-T1.1 Formulation: T1-F\* (final)

**Map.** T1-F\* has max 1 (sum 18) **under Q1 (a)**. T1-A and T1-B are vetoed: T1-B by S5, S6 and S8 at 3/3; T1-A by S3, S6, S8 and S9 at 3/3. S3† is read from "NW-1 under N-3 with a time-bounded N_max". Under Q1 (b), S4 (later 2) and S6 (up to 3 when both ends are near a surface) reopen, and T1-F stays the only survivor.

**DECISION.** A seeded Monte Carlo estimator with next-event estimation of the propagated diffuse energy: the ℓ → 0 form of `ref_hybrid`.
- Lambert emission per Kuttruff Eq. 4.24. The per-reflection split is s(1−α) non-specular and (1−s)(1−α) specular (§5.2, L2505; §2.7).
- Transport over lattice images per Eq. 4.35; gather per Eq. 4.29; AX4 air; the `matchTail` window.
- Unweighted branching, because s is broadband per surface (AX17).
- Specular entries stay exact.

**Determinism package:**
- **D1.** No libm in any value that decides a path. The key is (seed, start end, emitter, path, hit, attempt).
- **D2.** fp-contract off (gcc/clang), `/fp:precise` (MSVC), no fast-math.
- **D3.** RNG known-answer test on all three OSes; no `<random>`.
- **D4.** Fixed blocks of **64 histories**, independent of the thread count, reduced in block order. No N-dependent stratification.
- **D5.** Face-sequence hash golden for every path set, equal on all three OSes.
- **D6.** Stop flag checked between blocks.
- **D7.** N computed without libm, in whole blocks, recorded in the D5 golden. W_max and n\*_max are cross-platform constants.
- **Pool.** Process-wide, owned with the D-T4a gate.

**Seat 7:**
- the cross-OS E_target comparison in CI, against AX5;
- the allowed and forbidden wording: no "validated method"; no accuracy claim near walls beyond CS-NW+ or where both ends are flagged; diffuse rain named as a method family only.

**Seat 4:** one diffuse solve per scene, shared across modes.

**Load-bearing claims:**
- **D1-L2 (C3).** 15 (A) cases in 8 bands: max 0.088 dB, |z| ≤ 1.29.
- **D1-L3 (C7).** At the 100 m cube, (f) − tracer = −0.009 dB.
- **D1-L4.** References converge onto (f) in five small rooms (19 §2/§6; C14 (d), to 0.0003 %).
- **D1-L5.** Line-by-line equivalence, Seat 2.
- **D1-L6.** RQ-T1-4 is uninformed: no published validation.
- **D1-L7.** C5 checked one platform; D1–D7 carry the cross-platform claim.

**Debt register:**

| seat | commits later phases to | repaid when |
|---|---|---|
| S1, S7, S8, S9 | no published validation | Schröder 2011 or Heinz is obtained and agrees |
| S2 | B7/B10 need estimator changes in both sets | in those phases |
| S5 | D1–D7 kept for good | permanent |
| S4, S6 | reopen under Q1 (b) | Q1 = (a) |

**Confidence:** medium.

**Reversal:** an estimator-caused stage-2 fail; a cross-OS hash mismatch with a residual above −100 dBFS; a contradicting published bias.

## D-T1.2 Seed: S-1 (final)
- **Decision:** fixed key; E_target does not depend on tailSeed.
- **Map:** max 1, sum 2.
- **Debt:** S3 (τ budgets the per-scene offset); S9 (the BRAS report prints the Monte Carlo SE).
- **Confidence:** high.

## D-T1.4 Tolerance: Tol-2 (final)
- **Map:** Tol-2 max 1, sum 9. Tol-1 is vetoed. S7's reason is 1/0, "claimable while no flag fires".
- **DECISION:**
  - τ = 0.25 dB per case and band, C++ against the reference, with ℓ_ref inside τ.
  - Shipped **target** SE 0.083 dB.
    - Uncapped scenes meet it at n\*_max 8 000 (≤ 0.082 dB).
    - At n\*_max ≈ 1 024 they miss it by up to 1.5× (≤ 0.124 dB, a noisier pilot).
    - Where the work cap binds, the achieved SE is **higher**: see Q2.
- **Load-bearing claims:**
  - **D4-L1.** G jnd 1 dB, Vorländer Table 6.1.
  - **D4-L2.** At τ = 1 dB the test cannot fail a C++ that kept AX16 wherever |ΔL_b| ≤ 0.43 dB (uniform-α, Phase 04 rooms, CR2; C2). It would catch AX16 only in layouts 4–6. The veto rests on Seat 2's words.
  - **D4-L3.** τ = ¼ jnd, which equals gate (B)'s δ.
- **Debt:**
  - S2, S5, S6: target not reached where capped (Q2).
  - S3: the target is overridden under Q1 (b).
  - S9: ℓ_ref inside τ (met).
- **Confidence:** high.

## D-T1.5 Agreement case set: CS-3 + CS-NW+ (final)
- **Map:** max 1, sum 4. CS-1 is vetoed (S3 and S6 at 1/3); CS-2 + NW has max 2.
- **DECISION:** **70 cases, 560 case-bands, z_FW = 4.290.** The cases:
  - 15 (A) cases;
  - six Phase 04 rooms × 2 emitters;
  - W1 and W2 × 2;
  - 30 BRAS pairs;
  - CS-NW+ (W1 listener at a wall, an edge and a corner at 0.1 m, and at a wall at 0.3 m, both emitters; emitter at a wall at 0.1 m).
- **Statistical rule:**
  - test N per case with z_FW·SE_test ≤ τ − ℓ_ref (W1 corner: ℓ_ref 0.65 % = 0.028 dB, so SE_test ≤ 0.052 dB);
  - pooled bias check per band, |mean z| ≤ 3/√M;
  - no reseed; stage 2 at 4× N on a disjoint pre-registered range decides.
- **Reference:** the finest certified rung, with ℓ_ref recorded.
- **Reported, not gated:**
  - layout 4/5 near-wall cases (reference uncertified: 4.75 / 5.3 / 8.7 %);
  - W1 both-near at 0.1, 0.3 and 0.5 m;
  - `club` and `living_room` both-near at 0.1, 0.3 and 0.5 m;
  - the independent near-corner reference.
- **CI reports (Seats 2, 4, 6, 7):**
  - U at the default placement of every valid fixture;
  - every fixture or preset where the pilot estimate ships;
  - the cross-OS E_target comparison;
  - the RNG known-answer test;
  - the D5 hashes.
- **Where it runs:** Release build, hidden tag, three OSes; smoke cases only in Debug, ASan and TSan.
- **Confidence:** medium.
- **Reversal:** Release CI over Seat 5's budget. The BRAS pairs then move to the nightly.

## D-T1.6 Near-listener handling: NW-4C+ with note U (final)

**Map.**

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| **NW-4C+** | 1/**2** | 1/1 | 1/1 | 0/1 | 1/1 | 1/1 (with (i); S6-b) | 1/1 | 1/1 | 1/1 | 2 | 18 |
| NW-3 | | 2/**3** | | | | | | | | 3 | – |
| NW-2 / NW-1 | | | | | | | | | | 2 | 21 / 31 |

Seat 6 rates U at 2/1 as written in round 3 and 1/1 with (i); (i) is now in. NW-4C+ wins on sum.

### DECISION
**Estimator.** Per emitter, E = w·E_fwd + (1−w)·E_rev, with w = d_L²/(d_L² + d_E²) from geometry only. One listener-started set (from the head centre) serves both emitters, both ears and every mode. Both sets run in the same D4 blocks and are hashed in D5.

**Diagnostic flag "both-near".** d_L < 0.70 m and d_E < 0.70 m. It is pre-registered (C13 §4) and fixed before release. It means only that both ends are within 0.70 m of a surface. C14 (d) and C16 (f) show it does not mark a weak estimate across rooms.

**User note** (`TailMatch.approximate`):
> **U = (both-near AND (cap hit OR pilot VOV ≥ 0.1)) OR (cap hit AND achieved SE > 0.33 dB)**, per emitter.

**Note text** (Seat 6 (i); Phase 11 shows it on the settled scene only, in the info view, never mid-drag; wording by Seats 6 and 7):
- **Both-near branch:** no ±x from the achieved SE. Either the measured replicate p95 of its case class from the C++ reported set, or qualitative text: "level unreliable with source and listener this close to surfaces; move either about 0.7 m away".
- **Capped branch:** ±x from the achieved SE only for classes whose reported set shows SE ≥ the replicate SD (layout 4 listener_wall fails: 0.68 against 0.89 dB). Otherwise the class p95, or qualitative text.

**Seat 6 (ii), a requirement.** No default placement of a valid fixture or Phase 12 preset may raise U. If one does, the placement is changed, not the predicate. C16 (f) shows U silent at all six Phase 04 defaults at both n\*_max values.

**Seat 6 (iii).** U′ = cap hit OR both-near appears only as a labelled diagnostic in a Phase 11 advanced view.

**Where U fires (C16 (f), joint rule)**
- **Fires, at both n\*_max values:**
  - every layout 4 case, both emitters, SE 0.29–1.33 dB. The joint cap also caps the unmoved emitter;
  - layout 5: the reference positions and most one-end cases;
  - the low-α 100 m cube at s = 1 (SE 0.44–0.67 dB);
  - the moved emitter of every both-near placement at 0.1 m in W1, `club` and `living_room`;
  - W1 both_wall at 0.3 and 0.5 m;
  - `club` both_edge at 0.3 m.
- **Fires only at n\*_max 8 000:** `club` both_edge_0.5 (capped).
- **Good estimates it also flags:**
  - `living_room` both_wall_0.1 (SE 0.079 dB, p95 0.15 dB);
  - W1 both_wall_0.3 (SE 0.095 dB, p95 0.49 dB);
  - at n\*_max 1 024 only: `club` both_wall_0.3 and 0.5 (SE 0.069 / 0.066 dB) and `living_room` both_edge_0.3 (SE 0.105 dB). `club` both_edge_0.5 also fires at 1 024, through VOV.
- **Silent:**
  - all six Phase 04 defaults and their one-end placements;
  - `dead_booth` with the listener at a wall (both-near for both emitters; SE 0.024 dB);
  - the D-T6 small room;
  - W1/CR4 reference positions;
  - the closed 100 m cubes at s = 0.3, the absorbing-floor cube and the flutter cube.

C15 shows the capped cubes are not skewed: median −0.06 to +0.04 dB, p95 ≤ 0.28 dB.

**AX-row text.**
> Within about half a wavelength of a reflecting surface the GA tail level ignores the near-wall pressure rise, up to +3 dB at a rigid wall (Kuttruff Eq. 2.50, §8.7). The rise is reduced next to a partially absorbing face and absent at α = 1. The tail there is GA-true, not room-true. No accuracy claim is made where both ends are flagged, nor at layout-4/5-type edges and corners.

**Also in this session, before the goldens:**
- the near-corner reference (Seat 2);
- W1 both_corner asserts the cap flag (Seat 5).

**Phase 08:**
- E_b bit-identical between omni and binaural and between the ears;
- one both-near binaural render (Seat 4).

**Load-bearing claims:**
- **D16-L1–L3, L5–L7:** confirmed in round 2.
- **D16-L4:** C13 §2: both-near capped medians −0.35 to −6.72 dB.
- **D16-L8:** C14 (d): the small room is both-near with SE 0.006 dB.
- **D16-L9:** C16 (f): the "Where U fires" list above.
- **D16-L10:** C15: 16/16 rows pass in the cubes where U is silent.
- **D16-L11:** Kuttruff Eq. 2.50 (R = 1), L1552.

**Debt register**

| seat | commits | undo | evidence | repaid when |
|---|---|---|---|---|
| S1 (2) | both-near reads low; flagged, not bounded | a measured both-near fallback (Seat 2) | C++ reported set | fallback p95 ≤ 1 dB |
| S2 | uncertified edges and corners; B7/B10 in both sets | estimator change | near-corner reference | reported |
| S6, S7 (Phase 11) | the note: wording per (i), settled scene, advanced tier (iii) | UI change | Phase 11 | Phase 11 done |
| S6 (Phase 12) | (ii): presets never raise U at their default | preset placement | Phase 12 check | each preset |
| S3, S6, S9 | 0.70 m comes from one sweep, and U flags some good both-near estimates | parameter, before release | C++ reported set | release |
| S4 | binaural parity and the both-near render | test | Phase 08 | Phase 08 |
| S8 | both-near measured in W1, layouts 4/5, `club` and `living_room` only | – | Phase 12 | presets checked |

**Strongest objection.** U flags some good both-near estimates (p95 0.15–0.49 dB), and more of them at n\*_max 1 024. It holds because Seat 6's (ii) keeps every default placement silent, and because U′, the only rated alternative, is Seat 6's 3/2. S6-b settles it.

**Confidence:** medium.

**Reversal:** S6-b rated 3 (then Maisara, with the fallback above); a default placement raises U and cannot be moved; the near-corner reference contradicts NW-4C by more than τ.

## D-T1.3 Path count, pilot and cap: N-3W\*\*\* (final rule)

**Map.**

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| **N-3W\*\*\*** | **2/2** | 0/1 | 1/1† | 1/1 (n\*_max 1 024); 2/2 (8 000) | 1/1† (S5-b) | 1/1† | 1/1† | 1/1† | 1/1† | 2 | 19 / 21 |
| N-3W\* as composed | | 3/1 | | | | 3/3 | | | | 3 | – |
| N-1 | | 2/**3** | | | | | | | **3/3** | 3 | – |

S1 stays at 2/2. Its floor (SE ≤ 0.33 dB with VOV < 0.1) fails in:
- layouts 4/5 at s = 1 (C16: 0.29–1.33 dB);
- the low-α s = 1 cube (0.44–0.67 dB);
- the VOV part in the closed cubes.

### DECISION
- **History.** h = forward path h of emitter 0 + forward path h of emitter 1 + listener-started path h, with next-event estimation to both emitters' images. The work of h is all its image evaluations.
- **Budget.** W_scene = 2·W_max.
- **Pilot (Seat 2 C1).** Histories [0, …) in 64-history blocks. Stop at the first block boundary where n ≥ n\*_max or cumulative work ≥ W_scene/2. The pilot is discarded.
  - If n\* < 1 000, the pilot-floor flag fires (Seats 1, 3, 9).
- **Final range** (Seats 1, 2, 4; F12, F14).
  - N_need = max over emitters and bands of ⌈n\*·(SE_pilot/SE_target)²⌉, computed without libm.
  - N = max(N_need, n\*), rounded up to blocks.
  - N_cap = ⌊(W_scene − W_pilot)/ē_pilot⌋, rounded down to blocks.
  - Both are fixed before the final range is sampled. N = min(N, N_cap); a cap hit is flagged.
  - The range is [8 000, 8 000 + N).
  - If N_cap is under one block, the pilot estimate ships, flagged.
- **Diagnostics:** n\*, N, achieved SE per emitter against the target (Seat 7's wording), R, VOV, slope (reported only, never flagged), cap hit, pilot floor, both-near, realised work against W_scene.
- **CI** (Seats 7, 1, 4):
  - escalate on R, and on VOV ≥ 0.1 where the pilot SE > target/3;
  - pre-registered expected flags at the gated scenes;
  - **a list of every fixture or preset where the pilot estimate ships**.
- **W_max.** A pinned constant in image evaluations, re-derived once from the C++ cost at the CI runner's pool size, the worst gated cost and the worst OS restore build. It is checked against Seat 6's 3 s per emitter.
  - **Provisional value: 3.05 M per emitter (W_scene 6.10 M). Basis: Q2a.**
- **n\*_max.** A multiple of 64, ≤ 8 000, never below 1 000.
  - **Provisional value: 1 024**, Seat 4's condition 1 (C++ W1 diffuse share ≤ 25 ms for two emitters), to be re-derived in C++. If the C++ cost puts this below 1 000, the conflict returns to Seats 1, 3 and 4. **Basis: Q2b.**

**Load-bearing claims:**
- **D13-L1 (C16 (h)).** Block 64: pilot ≤ W_scene/2 + 15.3 % (worst), < 10.2 % at gated 100 m scenes. Total work is bounded by W_scene plus final scatter.
- **D13-L2 (C16 (f)).** The joint rule gives every scene a final range. 0 cap hits at the Phase 04 defaults and one-end placements.
- **D13-L3 (C15).** In the capped closed cubes the median is −0.06 to +0.15 dB and p95 ≤ 0.89 dB.
- **D13-L4.** F12, F14.
- **D13-L5.** AQ10 quoted in Q2.

**Debt register**

| seat | commits | undo | evidence | repaid |
|---|---|---|---|---|
| S1 (2/2) | random error of about 0.3–1.3 dB SE in long-window rooms with a fully absorbing face, and 0.44–0.67 dB in the low-α s = 1 cube. The joint cap degrades the unmoved emitter there too. | W_max (Q2) | Q2; Phase 12 presets | Q2 answered |
| S2 (later 1) | VOV-driven U flips; W_max and n\*_max re-pinned from C++ | one golden round | C++ | AX rows |
| S4 | W1 headroom | Q2b | C++ W1 | Q2b |
| S5 | block size | parameter | S5-b | confirmed |
| S7 | parameters set shipped bits | golden round before release; announced change after | – | first release |
| S8, S9 | the 1 000 floor is [Hyp] | parameter | a researcher pilot-size rule | sourced |

**Strongest objection.** S1 at 2/2 sits in the rooms the switch exists for. It holds because the error moves from systematic to random:

| room | old error (AX16) | new estimate under Q2 (A) |
|---|---|---|
| layout 4 | +3.87 dB, systematic | one-end medians −0.29 … +0.34 dB (C13 §2) |
| layout 5 | −1.17 dB, systematic | same |
| absorbing-floor 100 m cube | +2.38 dB | SE 0.12 dB |

The switch **adds** random error in two places:
- the closed s = 0.3 cubes: AX16 is +0.02 dB, against SE 0.13–0.20 dB, p95 ≤ 0.28 dB;
- the low-α s = 1 cube: AX16 is +0.06 / +0.10 dB, against SE 0.51–0.67 dB, p95 ≤ 0.89 dB (C15, C16 (g)).

This cost line goes to Maisara in Q2.

**Confidence:** medium.

**Reversal:** Q2; S5-b rated 3 (fallback: block 32); n\*_max below 1 000 at the C++ cost.

## D-T2 Resolution rule: NEEDS MAISARA (Q1)
**Map.**
- L2-F2: vetoed (S5 2/3).
- L2-F1R: S1–S8 at 2/2, S5 at **2/3**, S9 at 1/2.
- Bias reading: max 1 over eight rated cells (S4 states a preference, no cell).

The only option without a 3 depends on how Maisara reads AX36, so it is hers.

## D-T6 Regression bound: RS-2+ / B6-1F / M-2 (final, 9/9)
**Map.** Max 1, sum 7. S7 is 0/0 with its (i)–(iii) folded in. Seats 4, 6 and 8 are not required (0/0).

**DECISION.**
- **Room set**, fixed in round 1 and not moved:
  - `stone_box`;
  - W1 (both emitters);
  - the three (A) s-cases;
  - the small room (3 × 2.5 × 2.5 m, α 0.03, s 0.1; listener (1.5, 0.667, 0.425); emitters (1.05 | 1.95, 1.667, 0.5)).
- **Gate:** |ΔL_C++ − ΔL_ref| ≤ 0.25 dB per emitter and band.
  - The family is 72 case-bands, z_FW = 3.81.
  - It runs at shipping N wherever z_FW·SE ≤ τ − ℓ_ref; otherwise at test N, with the shipping value reported beside it.
  - Stage 2 applies, with no reseed.
  - The small room is both-near in the diagnostic but silent under U (C16), and is gated at shipping N.
- **Flags:** > 0.68 dB; Seat 1's 0.5 jnd.
- **Seat 7's conditions:**
  - (i) After release, a golden regeneration that moves a uniform-room ΔL by more than τ/3 is announced in advance.
  - (ii) The public wording comes from the latest report, and a fired flag removes it.
  - (iii) The report records the date the room set was fixed.
  - Public copy says "the same material on every surface".
  - "Nothing audible" also needs Seat 1 on ΔC80 and ΔEDT.
- **Report:** paired, R ≥ 30: ΔG, ΔC80, ΔEDT, ΔT30 and the seam step.
- **M-2:** tracer on the five mixed Phase 04 rooms (r_d below the listener's clearance, at two radii), reported.

**Confidence:** medium. **Reversal:** a stage-2 fail; C11 showing |ΔL_ref| > 0.68 dB (reported as a finding).

---

## D. Q1 and Q2 as they go to Maisara

**Q1. How does your 1 % rule (AX36) apply to the new estimator?** You accepted AX36 for patch size, where the error is systematic. The new estimator's error is random and measured.

**(a) To the method's bias, checked in CI.**
- Users get the 0.083 dB target precision (0.08 of the smallest audible level change) wherever the work limit does not bind:
  - met at n\*_max 8 000;
  - up to 0.124 dB at n\*_max 1 024.
  - Where the limit binds, Q2 sets the precision.
- CI (Release, hidden tag) checks, per band and per case class (reference positions, one-end near-wall, absorbing face, small rooms, 100 m), pooled and per class, that the mean deviation from the reference is ≤ 1 %.
  - The test is sized so that 3·SE ≤ 1 % − ℓ_ref. The near-wall class carries ℓ_ref = 0.65 %, so SE ≈ 0.12 % ≈ 0.005 dB, which is CI time only.
  - Classes with ℓ_ref ≥ 1 % are reported only.
- Board: no seat above 1.

**(b) To every scene's random error.** Prototype costs, 100 m cube, provisional W_max = 3.05 M; all figures [Inferred].

| variant | paths vs Tol-2 | 100 m work vs W_max | restore at 100 m, 1 / 4 threads | 14 restores | W1 rebuild |
|---|---|---|---|---|---|
| L2-F1R | 19.75× | 32–35× | 8.6 / 3.7 s | about 120 s | 93–121 ms |
| family α 1 % | 26.3× | 43–47× | 10.8 / 4.2 s | about 151 s | 117–154 ms |
| L2-F2 | 32.9× | 54–58× | 13.0 / 4.8 s | about 182 s | 140–187 ms |

- Every variant exceeds pluginval's 30 s watchdog and the 50 ms W1 target.
- At 100 m the strict SE cannot be reached under any restore-protecting cap.
- Precision bought: 0.0145–0.019 dB, 1/50–1/70 of a jnd.
- **It needs your override of Seat 5's veto.** Under (b), D-T1.1's Seat 4 and Seat 6 cells reopen, and Q2 is pushed to (B) or (C).

**Q2. What sets the two work limits?** This extends Challenge 1.

AQ10 says:
> "IR rebuild ≤ 50 ms (target)." … "Full rebuilds (room or material changes) are recorded, not budgeted. A miss is recorded in §0 with the time and the effective update interval it implies (AQ4). It is not optimised before Phase 13, and it is never met by shortening the image list or N_cap: that changes the output, so it goes through AX20/AX22 and /fix-plan."

Both limits change the shipped tail level to meet a time.

**Q2a, the big-room limit W_max.**
- **(A) Size it to pluginval's restore watchdog** (provisional: 3.05 M evaluations per emitter).
  - Restore at the gated 100 m scenes is 2.14 s, so 14 restores take 30.0 s, at the watchdog with no margin; realised work can scatter about 2 % above it.
  - Ordinary rooms: 0 cap hits at the six Phase 04 rooms' defaults and near-wall placements (C14 (b), C16 (f)).
  - Old against new error:

    | rooms | old error (AX16) | new under (A) |
    |---|---|---|
    | layout 4 / layout 5, s = 1 (absorbing floor or wall, fully diffuse) | +3.87 / −1.17 dB | random, SE 0.29–1.33 dB |
    | absorbing-floor 100 m cube | +2.38 / +2.39 dB | SE 0.12 dB |
    | closed 100 m cubes, s = 0.3 | +0.02 dB | SE 0.13–0.20 dB, p95 ≤ 0.28 dB |
    | low-α 100 m cube, s = 1 | +0.06 / +0.10 dB | SE 0.51–0.67 dB, p95 ≤ 0.89 dB |

  - The switch corrects the first two rows and **adds** random error in the last two (C16 (g), C15).
  - Seat 1 stays at 2.
- **(B) About 11× more.** Restore 2.16–4.83 s, 30.2–67.6 s for 14, so the watchdog is exceeded in every gated scene (C14 (c), per-emitter rule). 100 m SE 0.05–0.12 dB. Seat 5 has not rated it; a veto would be yours to override.
- **(C) Move the diffuse solve off the synchronous restore and prepare.** About one phase of Phase 07 rework, after this session. (A) ships meanwhile.

**Q2b, n\*_max.**
- **(i) 1 024, sized to 25 ms of the W1 target** (Seat 4).
  - W1-class SE about 0.06–0.10 dB, near-wall SE ≤ 0.124 dB.
  - The note fires on a few more good both-near placements (C16 (f) reading 4).
  - Seat 4 at 1/1.
- **(ii) 8 000 fixed.**
  - SE about 0.023 dB in W1.
  - The diffuse solve takes about 0.25 s per W1 rebuild (prototype, 1 thread).
  - Seat 4 at 2/2, unless an AX lets E_b refresh on its own slower interval (Table 15.1's 3 s scattering row; a Phase 10 option).
  - Both are inaudible.

Both values must be fixed before the first release, which costs one golden round.

---

## E. Summary

| id | decision | state | worst-off (cell) | sum | conf. | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| D-T1.1 | T1-F\* + D1–D7 (block 64), wording, cross-OS comparison | final | 1 (under Q1 (a)) | 18 | medium | NFR-1/2/6, AX5, AX6 | Kuttruff Eqs. 4.24, 4.29, 4.35, §5.2; Vorländer Fig. 11.38 | stage-2 estimator fail; hash mismatch |
| D-T1.2 | S-1 | final | 1 | 2 | high | NFR-6 | – | MC spread needed |
| D-T1.3 | N-3W\*\*\* (joint, block 64, work pilot, CI lists) | final rule; S5-b pending; W_max and n\*_max → Q2 | S1 2/2 | 19 (21 at 8 000) | medium | NFR-1/2, AQ10, AX5 | Table 6.1 | Q2; S5-b; n\*_max < 1 000 |
| D-T1.4 | τ 0.25 dB, target SE 0.083 dB (achieved higher where capped) | final | 1 | 9 | high | NFR-1 | Table 6.1 | ℓ_ref > τ/2 |
| D-T1.5 | 70 cases / 560 case-bands, z_FW 4.290, stage 2, CI reports | final | 1 | 4 | medium | NFR-1/8 | – | CI budget |
| D-T1.6 | NW-4C+, both-near diagnostic (0.70 m), U with Seat 6 (i)–(iii) | final; S6-b pending | S1 1/2 | 18 | medium | NFR-1/8, FR-SIM-6 | Kuttruff Eq. 2.50, §8.7 | S6-b; U at a default; reference > τ |
| D-T2 | – | NEEDS MAISARA (Q1) | L2-F1R S5 2/3 | – | – | AX36 | – | her ruling |
| D-T6 | RS-2+ / B6-1F / M-2 + Seat 7 (i)–(iii) | final | 1 | 7 | medium | NFR-1 | Table 6.1 | stage-2 fail |
| D-T3 | – | not needed | – | – | – | AX6 | – | – |

## Challenges to settled decisions
1. **AX36 applied to an estimator: Q1.**
2. **AQ10 "recorded, not budgeted" and "not optimised before Phase 13": Q2**, which extends Challenge 1.

No conflict found between `board.md` §1 and the PRD.

## F. /fix-plan list (rounds 1–4)
Apply after the S5-b and S6-b answers and Maisara's answers to Q1, Q2 and Challenge 1.

1. **BUILD_PLAN §2, new AX rows:**
   - **D-T1.1:** estimator text, citations, D1–D7 with block 64, cross-OS comparison, wording.
   - **D-T1.2:** S-1.
   - **D-T1.3:** the N-3W\*\*\* rule. W_max and n\*_max per Q2 (provisional 3.05 M per emitter and 1 024), with the re-derivation rule.
   - **D-T1.4:** τ, the target SE and its coupling to the cap.
   - **D-T1.5:** 70 cases, ladders, z_FW, stage 2, CI reports.
   - **D-T1.6:** NW-4C+, both-near diagnostic, U, note text (i), AX GA-limit text.
   - **D-T6:** room set, gate and gate-N rule, flags, Seat 7 (i)–(iii), M-2.
   - **D-T2:** after Q1.
2. **AX36 (c):** resolved. R1 is certified at 2.5 m in CR2, CR3 and CR4; R2 is D-T1.1. The final wording follows Q1.
3. **AX16:** marked "switched", with the ΔL_b,tr table and C16 (g). **AX21:** cross-reference. **AX5:** note that cross-architecture agreement rests on D1–D7.
4. **AQ10:** amended only per Maisara's answers to Q2 and Challenge 1.
5. **phase-05b2:**
   - §3: D-T1, D-T2 and D-T6 settled; D-T3 not needed.
   - §4 scope:
     - the agreement suite;
     - the reported set;
     - the near-corner reference;
     - the M-2 tracer runs;
     - C++ re-measurement of W_max and n\*_max;
     - the CI reports (U at defaults; pilot-estimate ships; cross-OS E_target; KAT; D5 hashes);
     - a both-near omni render in the listening pack.
   - §5 acceptance:
     - agreement over 70 cases at z_FW 4.290 with stage 2;
     - the D-T6 gate (72 case-bands, z_FW 3.81);
     - KAT, D5 and the cross-OS check;
     - U silent at every valid fixture's default.
6. **tests/golden:**
   - the agreement reference golden;
   - the ΔL_ref golden;
   - the D5 face-hash and per-case-N golden;
   - the RNG KAT vectors.

   Each is created by script, with its reason recorded in CHANGELOG.
7. **phase-08:** E_b bit-identical between modes and between the ears; a both-near binaural render in the listening pack. Under Q2b (ii), the split-update or E_b-refresh AX goes before item 8.
8. **phase-10:** under Q2b (ii), an E_b refresh-interval AX (Table 15.1's 3 s scattering row).
9. **phase-11:**
   - the "approximate" note U with Seat 6 (i) text, settled scene, info view, wording by Seats 6 and 7;
   - the U′ advanced diagnostic tier (iii).
10. **phase-12:** Seat 6 (ii) as a requirement: no preset default placement raises U; if one does, the placement is changed.
11. **phase-13:** re-check W_max and n\*_max on the release machines. Schedule Q2 (C) (async restore) if chosen.
12. **BUILD_PLAN §0 records:** W1/W2 including the diffuse share; flags at the gated scenes; realised work against W_scene.
13. **§5 backlog:**
    - a both-near fallback with measured bias (Seats 1, 2);
    - RQ-T1-4 (Schröder 2011, Heinz);
    - a sourced pilot-size rule (researcher).
14. **Ledger:** rows P05B2-T1T2T6-01…55 closed with this round's answers; Seat 7's D-T6 row; the S5-b and S6-b outcomes.

## For Maisara
- **Settled:**
  - the formulation (a fast seeded estimate of the validated model);
  - the seed (it never moves the level);
  - the 0.25 dB agreement test on 70 pre-registered cases;
  - near-wall handling, with a note that is quiet at every Phase 04 default placement;
  - the uniform-room bound, with Seat 7's rules for the "nothing changed" wording.

  Seat 1 gave the most: in extreme absorbing rooms the tail level is now a random estimate of about ±0.3–1.3 dB, replacing a systematic +3.9 / −1.2 dB.
- **Q1:** apply your 1 % rule to the method's bias, checked in CI at no user cost? Or to every scene, at 20–33× the cost and 9–13 s restores at 100 m, which overrides Seat 5's veto?
- **Q2a:** size the big-room work limit to pluginval's 2-second restore? Then the switch fixes 2.4–3.9 dB errors but adds 0.1–0.7 dB of random error in some closed 100 m rooms where the old method was nearly exact. Or spend about 11× more (restores 2.2–4.8 s, past the watchdog), or move the work off the load path later?
- **Q2b:** may the small-room limit be sized to the 50 ms rebuild target (about 0.06–0.12 dB of inaudible error), or should it stay at 8 000 (about 0.25 s rebuilds)?

Files:
- /home/user/makroof/docs/review/phase-05b2/32-interrogator-round2-T1-T2-T6.md
- /home/user/makroof/docs/review/phase-05b2/33-orchestrator-C16.md
- /home/user/makroof/docs/review/phase-05b2/31-orchestrator-C15.md
- /home/user/makroof/docs/review/phase-05b2/30-seat2-confirm-S2a.md
- /home/user/makroof/docs/review/phase-05b2/30-seat4-confirm-S4a.md
- /home/user/makroof/docs/review/phase-05b2/30-seat6-confirm-S6a.md
- /home/user/makroof/docs/review/phase-05b2/29-decider-round3-T1-T2-T6.md
