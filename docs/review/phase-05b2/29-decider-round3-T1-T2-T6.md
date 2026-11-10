# Decider — rebuttal round 3, D-T1, D-T2 and D-T6

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

# Decider, rebuttal round 3: D-T1, D-T2 and D-T6 (phase 05b session 2, 2026-11-10)

**State after this round**

| id | state |
|---|---|
| D-T1.1, D-T1.2, D-T1.4, D-T1.5 | stand, with corrections |
| D-T1.3 | rule **revised** (N-3W\*\*\*: work-bounded pilot, joint accounting); two seat confirmations pending (Seats 2 and 4); W_max and n\*_max provisional, pending Q2 |
| D-T1.6 | stands with a **revised note predicate**; two seat confirmations pending (Seats 2 and 6) |
| D-T6 | stands, now convened 9/9: Seat 7 rated it, and its conditions (i)–(iii) and its gate-N request are folded in |
| D-T2 | NEEDS MAISARA (Q1) |
| D-T1.3 parameters | NEEDS MAISARA (Q2): W_max and n\*_max |

None of the pending confirmations can change a winner unless the seat rates 3. In that case, the fallbacks named below are already laid out.

**Corpus revision:** `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`. Re-read this round, Kuttruff:
- L2505 (§5.2): the split per reflection, s(1−α) non-specular and (1−s)(1−α) specular, pointing to §2.7 for rough walls and to Eq. 4.24 for Lambert's law;
- L89–90: Eq. 4.24 is the irradiance and Lambert emission at dS;
- L1548–1552: Eq. 2.50.

**Inputs this round:**
- interrogator report `26-interrogator-T1-T2-T6.md`;
- orchestrator computation `27-orchestrator-C14.md`;
- Seat 7 on D-T6, `28-seat7-D-T6.md`;
- my rounds 1 and 2, `21-…` and `25-…`.

New arithmetic below is labelled [Inferred]. I computed it with Python's `statistics.NormalDist`.

---

## A. Answers to the interrogator's 18 corrections

Every correction is accepted. There is no rebuttal; on correction 7, my reading has been replaced.

| # | answer |
|---|---|
| 1 | **Accepted.** The fixed [0, 256) calibration block is removed. The pilot is now bounded in work from its first block (§D-T1.3). |
| 2 | **Accepted.** Seat 2's C1 is now met literally: the pilot stops on cumulative work. C5 is still not met as written. Seat 2 is asked (question S2-a). |
| 3 | **Accepted.** Accounting is now **joint**: one history = both emitters' forward paths + the shared listener path. One n\*, one N and one N_cap per scene, against W_scene = 2·W_max (Seat 5's two-emitter derivation). |
| 4 | **Accepted.** Q2 is restated with the measured (A) figures (C14 (b)), both old-method errors, (B) at both n\*_max values with the watchdog consequence (C14 (c)), and AQ10 quoted exactly. n\*_max moves into Q2 (§D). |
| 5 | Noted, nothing to correct. |
| 6 | **Accepted.** The AX text now says "reflecting surface", "up to +3 dB at a rigid wall", and that there is no such rise next to an absorbing face. |
| 7 | **Accepted.** My qualifier was Seat 1's escalation rule, not Seat 6's trigger, and C14 (b) shows it still fires at `concert_hall_box`, SE 0.054 dB. The predicate is replaced (§D-T1.6). For each trigger I state which seat's condition it meets and which it leaves unmet. Seat 6 is asked (S6-a). |
| 8 | **Accepted.** The geometric flag alone no longer raises the user note, so `dead_booth`'s knife-edge default (d_L = 0.700 m) decides a diagnostic only. The reversal test now covers the default placement of every valid fixture. |
| 9 | **Accepted.** Phase 11 (Minimal placement UI) gets a register row and a /fix-plan entry. |
| 10 | **Accepted.** D-T1.1 now cites Eq. 4.24 for Lambert emission and §5.2 (L2505) with §2.7 for the s(1−α) split. "Unbiased with no weights" now cites AX17 (one broadband s per surface), not AQ3. |
| 11 | **Accepted.** D-T1.1's max 1 holds only under Q1 (a). Under (b), S4 later 2 and S6 (up to 3 in both-near cases) reopen, and T1-F stays the only survivor. S3's resolution is marked †. The register's "repaid when the BRAS nightly holds" is removed. |
| 12 | **Accepted.** D4-L2 is restated (§D-T1.4). |
| 13 | **Accepted.** The D-T1.4 register is updated to the capped figures. Seat 7's Tol-2 reason now reads "claimable while no flag fires" (28-seat7), still 1/0. |
| 14 | **Accepted.** In the CS-1 row, S3 and S6 are 1/3 (vetoed). The winner is unchanged. The count is pre-registered at **70 cases, 560 case-bands, z_FW = 4.290** (C14 (e); I re-checked it). |
| 15, 16 | **Accepted.** Q1 is restated (§D-T2). |
| 17 | **Accepted.** Seat 7 has rated D-T6: composite 0/1, and 0/0 under its conditions (i)–(iii). It is folded in. |
| 18 | **Accepted.** Under the revised D-T1.6 the small room raises the geometric diagnostic but not the user note (no cap hit, VOV 0.0017). The D-T6 gate-N rule is stated, with stage 2 and no reseed. Seat 7's request (shipping N, positions unchanged) is met. |

## B. Answers to the five questions
1. **Calibration bound and the "< 256" case.** There is no separate calibration block any more.
   - The pilot samples histories [0, …) in fixed D4 blocks. It stops at the first block boundary where n ≥ n\*_max or the cumulative pilot work reaches ≥ W_scene/2.
   - The overrun is at most one D4 block, and realised work is recorded.
   - If the first block alone exceeds W_scene/2, the pilot is that one block and the pilot-floor flag fires.
   - So "pilot ≤ W_scene/2" holds by construction, up to one block. The final cap, computed from the work left, makes the floor N ≥ n\* fit, up to cost scatter. Any shortfall is a flagged cap hit.
   - The † cells are re-read in §D-T1.3.
2. **Note triggers.** See §D-T1.6, "Trigger-by-seat table". Seats 2 and 6 are asked questions S2-a and S6-a.
3. **D-T6.** Seat 7 rates the composite 0/1, and 0/0 under (i)–(iii). The small room is a geometric both-near case, but it does not raise the note and stays gated at shipping N (§D-T6).
4. **Q1** is restated in §D-T2.
5. **Q2** is restated in §D. AQ10 is quoted exactly there. n\*_max **does** belong in Q2.

## C. Questions the orchestrator must put to seats (on this final text)
- **S2-a (Seat 2), on D-T1.3 N-3W\*\*\* and the D-T1.6 note.**
  > Your C1 is met: the pilot stops on cumulative joint work at W_scene/2. C2–C4 are met. Your C5 is not met as written. VOV and the bare cap hit are not user-visible on their own. The user note is U = (both-near geometric AND (cap hit OR pilot VOV ≥ 0.1)) OR (cap hit AND achieved SE > 0.33 dB). VOV, R, slope and cap hits stay in the diagnostics and CI. Rate N-3W\*\*\* with U, now and later. Also rate the alternative U′ = cap hit OR both-near geometric, which is your literal C5.
- **S6-a (Seat 6), on the D-T1.6 note.**
  > Your condition 3 listed three triggers: both-near, capped SE > 0.33 dB, and VOV ≥ 0.1, with no bare cap hit. U keeps the second as written and makes the other two count only together: both-near AND (cap hit OR VOV ≥ 0.1). The reason is that C14 (d) shows the geometric criterion flags an excellent small-room estimate (SE 0.006 dB), and C14 (b) shows VOV alone fires at SE 0.054 dB. Rate U, now and later. Also rate U′, which shows a bare cap hit.
- **S4-a (Seat 4), on D-T1.3.**
  > The pilot now stops on realised work. It is discarded, and the final N and N_cap are fixed before the final range is sampled. So your condition 4 holds for everything published, but not for the pilot. n\*_max follows your condition 1 provisionally, pending Q2. Rate N-3W\*\*\*. Also rate it with n\*_max = 8 000 fixed (if Maisara rejects target-sizing).

---

## D-T1.1 Formulation: T1-F\* (stands, corrected)

**Tension map.**

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max |
|---|---|---|---|---|---|---|---|---|---|---|
| **T1-F\*** | 1/1 | 1/1 | 1/1† | 1/1 | 1/1 (D7) | 1/1 | 1/1 | 1/1 | 1/1 | 1 (under Q1 (a)) |
| T1-B | | | | | 3/3 | 3/3 | | 3/3 | | 3 |
| T1-A | | | 3/3 | | | 3/3 | | 3/3 | 3/3 | 3 |

- S3† is read from "NW-1 under N-3 with a time-bounded N_max". NW-4C under a work cap meets that.
- Sum 18.
- Under Q1 (b), S4 goes to later 2 ("makes the split update mandatory"), and S6 can reach 3 in both-near cases (its NW-1 + L2-F2 cell). T1-F remains the only survivor either way.

**DECISION.** A seeded Monte Carlo estimator with next-event estimation of the propagated diffuse energy: the ℓ → 0 form of `ref_hybrid`.
- At each hit, s(1−α) of the incident energy is emitted diffusely as Lambert emission (Kuttruff Eq. 4.24; split per §5.2 L2505, §2.7).
- Transport over the lattice images follows Eq. 4.35, and the gather Eq. 4.29, with AX4 air and the `matchTail` window.
- Branching is unweighted because s is broadband per surface (AX17).
- Specular entries stay exact.
- Near-listener handling is D-T1.6; path count D-T1.3.

**Determinism package (Seat 5).**
- **D1.** No libm in any value that decides a branch or a path. The RNG key is (seed, start end, emitter, path, hit, attempt).
- **D2.** fp-contract off (gcc/clang), `/fp:precise` (MSVC), no fast-math.
- **D3.** RNG known-answer test on all three OSes; no `<random>`.
- **D4.** Fixed path blocks, independent of thread count; no N-dependent stratification.
- **D5.** A face-sequence hash golden for every path set, equal on all three OSes.
- **D6.** The stop flag is checked between blocks.
- **D7.** N is computed without libm (squared ratios), rounded to whole D4 blocks, and recorded per case in the D5 golden. W_max is a cross-platform constant.
- **Pool.** One process-wide pool owned with the D-T4a gate.

**Seat 7.**
- CI compares E_target across the three OSes on the agreement set and CS-NW+, against AX5.
- Allowed and forbidden wording as listed by Seat 7. In short: no "validated method", no accuracy claim near walls beyond CS-NW+, and the diffuse-rain family named as membership only.

**Seat 4.** One diffuse solve per scene, shared across output modes.

**Load-bearing claims.**
- **D1-L2.** C3: 15 (A) cases, all 8 bands, max 0.088 dB, |z| ≤ 1.29.
- **D1-L3.** C7: at the 100 m cube, (f) − tracer = −0.009 dB.
- **D1-L4.** 19 §2/§6 and C14 (d): references converge onto (f) in five small rooms. In the D-T6 small room the ladder converges to 0.0003 %, and the 256 k run sits −0.0003 dB from it.
- **D1-L5.** Seat 2's line-by-line equivalence (from the code).
- **D1-L6.** RQ-T1-4 is uninformed: there is no published validation, so the wording is limited.
- **D1-L7.** C5 is single-platform; cross-platform agreement rests on D1–D7.

**Debt register.**

| seat | commits | undo | evidence | repaid when |
|---|---|---|---|---|
| S1, S7, S8, S9 | no published validation | estimator fix | Schröder 2011 or Heinz 1993/94 obtained | a published bias figure agrees |
| S2 | B7 directivity and B10 weighted branching in both sets | estimator change | B7/B10 phases | those phases |
| S5 | D1–D7 gates for good | low | three-OS CI | permanent |
| S4, S6 | reopen under Q1 (b) | – | Q1 | Q1 = (a) |

**Confidence:** medium.

**Reversal:**
- an estimator-caused stage-2 fail;
- a face-hash mismatch across OSes with a residual above −100 dBFS;
- a published bias figure that contradicts D1-L2 or D1-L3.

---

## D-T1.2 Seed: S-1 (stands)
- **Map:** S-1 max 1, sum 2 (S3 0/1, S9 0/1). S-2 max 2, sum 16.
- **Decision:** the key is a fixed constant; E_target does not depend on tailSeed.
- **Debt:**
  - S3: τ budgets the fixed per-scene offset.
  - S9: the BRAS report prints the Monte Carlo SE beside the ensemble spread.
- **Confidence:** high.

---

## D-T1.4 Tolerance: Tol-2 (stands, corrected)
- **Map:** Tol-2 max 1, sum 9. Tol-1 is vetoed (S2 3/3, S9 later 3). Tol-3 max 2.
- **S7's reason (28-seat7):** "claimable while no flag fires", 1/0.

**DECISION.**
- τ = 0.25 dB per case and band, C++ against the reference, with ℓ_ref inside τ.
- Shipped **target** SE 0.083 dB. Where the D-T1.3 work cap binds, the achieved SE is lower than the target allows and is reported (Q2), unless Q1 binds.

**Load-bearing claims.**
- **D4-L1.** G jnd 1 dB (Vorländer Table 6.1).
- **D4-L2 (corrected).** At τ = 1 dB the agreement test cannot fail an implementation that kept AX16 wherever |ΔL_b| ≤ 0.43 dB. That covers the uniform-α cases, the six Phase 04 rooms and CR2 (C2), which are most of the agreement set. It would catch AX16 in Table 5.2 layouts 4–6 (+3.83, −1.12, −1.14 dB). The veto rests on Seat 2's words, which name exactly the first group.
- **D4-L3.** τ = ¼ jnd = gate (B)'s δ.

**Debt register.**

| seat | commits | undo | evidence | repaid |
|---|---|---|---|---|
| S2, S5, S6 | the target is not reached where W_max binds (Q2 (A): 0.39–1.11 dB in layouts 4/5 at s = 1; 0.11–0.20 dB in closed 100 m cubes at s = 0.3 or with an absorbing floor; 0.44–0.64 dB in the low-α 100 m cube at s = 1; C13, C14) | Q2 | C++ W_max | Q2 answered |
| S3 | target overridden if Q1 = (b) | – | Q1 | Q1 answered |
| S9 | ℓ_ref inside τ in small rooms | – | ladders 19 §2/§6, C14 (d) | met |
| S7 (later 0) | – | – | – | – |

**Confidence:** high.

---

## D-T1.5 Agreement case set: CS-3 + CS-NW+ (stands, corrected)

**Map.**

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| CS-3 + NW | 0/0 | 0/1 | 0/1 | 0/0 | 0/0 | 0/1 | 1/0 | 0/0 | 0/0 | 1 | 4 |
| CS-2 + NW | | | | | | | | | 1/**2** | 2 | 11 |
| CS-1 (no NW) | 2/2 | 2/2 | 1/**3** | 0/1 | 0/1 | 1/**3** | 0/2 | 2/2 | 2/2 | 3 | – |

**DECISION.**
- **Gated set: 70 cases, 560 case-bands**, pre-registered (C14 (e)):
  - 15 (A) cases;
  - the six Phase 04 rooms × 2 emitters;
  - W1 and W2 × 2 emitters;
  - 30 BRAS pairs;
  - CS-NW+ with both emitters at each listener placement (W1 listener at 0.1 m from a wall, an edge and a corner, and at 0.3 m from a wall; plus the emitter at 0.1 m from a wall).
- **Rule:**
  - z_FW = 4.290 (Bonferroni, family α 1 %, two-sided).
  - Test N per case chosen so that z_FW·SE_test ≤ τ − ℓ_ref.
  - Pooled bias check per band: |mean z| ≤ 3/√M.
  - On a fail: no reseed and no case-specific N. Stage 2 re-runs all cases on a disjoint, pre-registered range at 4× N, and the decision rests on stage 2 alone.
- **Reference per case:** the finest certified rung (last halving < 1 %). Its ℓ_ref is recorded.
- **Reported, not gated:**
  - layout 4/5 near-wall cases, whose reference is uncertified (4.75 %, 5.3 %, 8.7 %);
  - W1 both_wall and both_corner at 0.1 m;
  - W1 both-near at 0.3 and 0.5 m;
  - `club` and `living_room` both-near at 0.1, 0.3 and 0.5 m;
  - an independent near-corner reference.
- **CI:** Release build, hidden tag, three OSes. Debug, ASan and TSan run one smoke case.

**Load-bearing claims.**
- **D5-L1.** C7: every reference is computable, ≤ 2.5 GB.
- **D5-L3.** 19 §3: bands correlated ≥ 0.978.
- **D5-L4 [Inferred].** z_FW = 4.290 over 560 case-bands.

**Debt register:** as in round 1, with S5† for the CI time of the larger suite. **Confidence:** medium. **Reversal:** the suite's Release CI time exceeds Seat 5's budget; then the BRAS pairs move to the nightly (Seat 9's variant).

---

## D-T1.6 Near-listener handling: NW-4C+ (stands, note revised)

**Map** (round-2 cells, unchanged):

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| **NW-4C+** | 1/**2** | 1/1 (S2-a) | 1/1 | 0/1 | 1/1 | 1/1 (S6-a) | 1/1 | 1/1 | 1/1 | 2 | 18 |
| NW-3 | 1/2 | 2/**3** | 2/2 | 1/2 | 0/2 | 1/2 | 2/2 | 1/2 | 2/2 | 3 | – |
| NW-2 / NW-1 (round 1) | | | | | | | | | | 2 | 21 / 31 |

**Working.**
- NW-3 is vetoed.
- Max ties at 2 (S1 later: in both-near cases the estimate reads low).
- NW-4C+ wins on sum.
- No variant lowers S1 without a measured both-near fallback.

**DECISION.**
- **Estimator (unchanged):**
  - Per emitter, E = w·E_fwd + (1−w)·E_rev, with w = d_L²/(d_L² + d_E²), from geometry only.
  - One listener-started set (from the head centre) serves both emitters, both ears and every mode.
  - Both sets run in the same D4 blocks and are hashed in D5.
- **Diagnostic both-near flag (Seat 2's condition):** d_L < 0.70 m and d_E < 0.70 m, pre-registered from the C13 §4 VOV crossing.
  - In the diagnostics and in `TailMatch`, it means only "both ends within 0.70 m of a surface", not "estimate weak". C14 (d) shows the criterion does not carry over between rooms.
- **User note U** (`TailMatch.approximate`, with ±x from the achieved SE; shown by Phase 11 on the settled scene, in the info view, worded by Seats 6 and 7):

  > **U = (both-near AND (cap hit OR pilot VOV ≥ 0.1)) OR (cap hit AND achieved SE > 0.33 dB)**

  Bare cap hits, R, VOV, slope and the pilot floor stay in the diagnostics and CI.

**Trigger-by-seat table.**

| trigger | meets | leaves unmet |
|---|---|---|
| capped SE > 0.33 dB | S6 cond. 3 (literal); S1's floor | – |
| both-near AND (cap OR VOV ≥ 0.1) | S6's aim (no note on good estimates: C14 (d) small room SE 0.006, C14 (b) `concert_hall_box` SE 0.054 do not fire); S7 (no flag at W1 reference positions) | S6's literal "both ends near" and "VOV ≥ 0.1" as separate triggers (S6-a); S2 C5 ("VOV diagnostics only"; "cap hit and both-near user-visible") (S2-a); S8 (ii) "any cap hit… as approximate" |

Seat 8's (ii) was its condition for moving from 1/1 to 1/0. Leaving it unmet keeps Seat 8 at its own 1/1, so nothing rises.

**Where U fires, checked against C13 and C14** [Inferred from those tables]:
- **Fires:**
  - layouts 4/5 at s = 1 (capped, SE > 0.33);
  - the low-α 100 m cube at s = 1 (SE 0.44–0.64);
  - W1 both_wall and both_corner (both-near, capped).
- **Silent:**
  - W1/CR4 reference positions;
  - all 24 Phase 04 near-wall cases;
  - the listener grid;
  - the D-T6 small room;
  - closed 100 m cubes at s = 0.3 (SE 0.11–0.20).

**AX-row text (corrected, Seat 9 and Seat 7).**
> Within about half a wavelength of a **reflecting** surface the geometrical-acoustics tail level ignores the near-wall pressure rise, up to +3 dB at a rigid wall (Kuttruff Eq. 2.50, §8.7). Next to an absorbing face there is no such rise. The tail there is GA-true, not room-true. No accuracy claim is made where both ends are flagged, nor at layout-4/5-type edges and corners, where the reference is uncertified.

**Reported, not gated:** see D-T1.5. The near-corner reference is computed before the goldens are frozen (Seat 2).

**Benchmark:** W1 both_corner asserts the cap flag (Seat 5).

**Phase 08:**
- a test that E_b is bit-identical between omni and binaural and between the two ears;
- one both-near binaural render in the listening pack (Seat 4).

**Load-bearing claims.**
- **D16-L1–L3, L5–L7:** as in round 2; the interrogator confirmed them.
- **D16-L4:** C13 §2 table: both-near median −0.35 to −6.72 dB against the long runs.
- **D16-L8 (C14 (d)):** the small room raises the geometric flag, but its estimate has SE 0.006 dB, VOV 0.0017, and replicates within ±0.015 dB of a reference converged to 0.0003 %.
- **D16-L9 (C14 (b)):** VOV 0.106 at `concert_hall_box` with final SE 0.054 dB.
- **D16-L10 (corpus):** Eq. 2.50 (R = 1), L1552.

**Debt register.**

| seat | commits | undo | evidence | repaid when |
|---|---|---|---|---|
| S1 (2) | both-near reads low, flagged, not bounded | a measured both-near fallback (Seat 2 designs it) | reported set, C++ | fallback p95 ≤ 1 dB |
| S2 | uncertified edges and corners; B7/B10 in both sets | estimator change | near-corner reference (this session) | reported |
| S3, S6, S7, S9 | the 0.70 m threshold comes from one W1 sweep | parameter, before release | C++ reported set | release |
| **S6, S7 (Phase 11)** | the "approximate" note: settled scene, info view, wording | UI change | Phase 11 | Phase 11 done |
| S4 | binaural parity and the both-near render | – | Phase 08 | Phase 08 |
| S8 | both-near measured only in W1, layouts 4/5, `club` and `living_room` | – | Phase 12 presets | presets checked |

**Strongest objection.** U depends on two seat confirmations. If Seat 2 rates U 3 (its C5), the fallback is U′ = cap hit OR both-near, which Seat 6 must then rate. If both seats veto each other's form, the note design goes to Maisara as a NEEDS MAISARA item. The estimator itself is unaffected.

**Confidence:** medium.

**Reversal:**
- U raised at the default placement of any valid fixture or Phase 12 preset with achieved SE ≤ 0.1 dB (a CI-reported list);
- the near-corner reference contradicting NW-4C by more than τ;
- a measured both-near fallback.

---

## D-T1.3 Path count, pilot and cap: N-3W\*\*\* (revised)

**Map.**

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| N-3W\* as composed | 2/2 | 3/1 | 2/2 | 2/2 | 2/2 | 3/3 | 2/2 | 2/2 | 2/2 | 3 | – |
| **N-3W\*\*\*** | **2/2** | ? (S2-a) | 1/1† | 1/1† (S4-a) | 1/1† | 1/1† (S6-a) | 1/1† | 1/1† | 1/1† | 2 if confirmed | 20 if confirmed |
| N-1 | | 2/**3** | | | | | | | **3/3** | 3 | – |

How the † cells are re-read against the revised rule:
- **Holds by construction** (up to one block and cost scatter): "pilot ≤ W_max/2" and "N ≥ pilot" (Seats 1, 2, 3, 5, 6, 7, 9).
- **Seat 3's C-1 to C-3:** met (floor flag; slope not flagged).
- **Seat 5:**
  - joint budget = its two-emitter derivation;
  - D7 and the constant W_max are met;
  - the overrun of at most one block needs its confirmation of the D4 block size.
- **Seat 7:** R and VOV escalated in CI; slope reported only.
- **Seat 8:** (a) and (c) met.
- **Seat 9:** work pilot with a floor; N ≥ n\*.
- **Seat 4:** see S4-a. Condition 1 holds under Q2's provisional n\*_max; condition 4 holds for everything published.
- **Seat 1 stays 2/2.** Its floor (SE ≤ 0.33 dB with VOV < 0.1) fails in:
  - layouts 4/5 at s = 1 (C13 §2);
  - the 100 m cube at s = 0.3 (VOV 0.31/0.37);
  - the low-α 100 m cube at s = 1 (SE 0.44–0.64; C14 (a)).

**Working.**
- Vetoes drop N-3W\* as composed and N-1.
- N-3W\*\*\* is at max 2 (S1), pending S2-a and S4-a. The round-1 rows N-2 and N-3 are the underspecified parents of this rule (ledger row 22, accepted).
- Lowering S1 needs a larger W_max. That is Q2 (B), which exceeds the restore bound in every gated scene (C14 (c)).

### DECISION D-T1.3 = N-3W\*\*\* (rule)
- **History.** History h = forward path h of emitter 0 + forward path h of emitter 1 + listener-started path h, with next-event estimation to both emitters' images. Each start end has its own RNG key. The work of h is all image evaluations of its three paths.
- **Budget.** W_scene = 2·W_max per scene. This is Seat 5's derivation: both emitters within the restore bound.
- **Pilot (Seat 2 C1).** Histories [0, …) in D4 blocks. Stop at the first block boundary where n ≥ n\*_max or the cumulative pilot work ≥ W_scene/2; n\* = the histories done.
  - Overrun is at most one block.
  - If n\* < 1 000, the pilot-floor flag is raised (Seats 1, 3, 9).
  - The pilot is discarded.
- **Final range (Seats 1, 2, 4; F12, F14).**
  - N_need = max over emitters and bands of ⌈n\*·(SE_pilot/SE_target)²⌉ (D7).
  - N = max(N_need, n\*), rounded up to whole blocks.
  - N_cap = ⌊(W_scene − W_pilot)/ē_pilot⌋, rounded down to blocks. Both are computed **before** the final range is sampled (Seat 4).
  - N = min(N, N_cap). A cap hit is flagged.
  - The final range is [8 000, 8 000 + N), and n\*_max ≤ 8 000.
  - If N_cap is less than one block, the pilot estimate ships, flagged (Seat 4 (3)).
- **Diagnostics.** Reported: n\*, N, achieved SE per emitter against the target SE (Seat 7 wording), R, VOV, slope (reported, never flagged), cap hit, pilot floor, both-near, and realised work against W_scene.
- **CI escalation.** R, and VOV ≥ 0.1 where the pilot SE > target/3 (Seats 7, 1). Pre-registered expected flags:
  - the pilot floor at W2 and the flutter cube;
  - the cap and VOV at the closed 100 m cubes;
  - the cap at W1 both_corner.
- **User note:** U (D-T1.6).
- **W_max.** A pinned constant in image evaluations, the same on every platform. It is re-derived once from the C++ cost, at the CI runner's pool size, the worst gated cost and the worst OS restore build (Seats 2, 5, 6), and checked against Seat 6's 3 s per emitter.
  - **Sizing basis: Q2.** Provisional value: W_max = 3.05 M per emitter, i.e. W_scene = 6.10 M.
- **n\*_max.** Provisional value: Seat 4's condition 1. That is the largest value ≤ 8 000 for which the C++ W1 diffuse solve (pilot plus final, both emitters) takes ≤ 25 ms, and never below 1 000. The prototype puts it at about 1 020 [Inferred]. If those two bounds conflict at the C++ cost, it goes back to Seats 1, 3 and 4. **Sizing basis: Q2.**
- **C15 (orchestrator, before the goldens).** Re-run C13 and C14 under the joint rule. Their per-emitter figures, with the listener set run per emitter, are an upper bound on cost.

**Load-bearing claims.**
- **D13-L1.** C13 §1, C14 (a): every gated 100 m scene's first 256 histories cost 0.07–0.41 W_max. The interrogator's failure (more than W_max/2) occurs only in layout-4-class rooms (e_cal 7 000–8 800, t_mix,e 0.38 s). The revised pilot bounds it in every scene.
- **D13-L2.** C13 §2, C14 (a): Seat 1's floor fails in the scenes listed above.
- **D13-L3.** C14 (b), C13 §5: 0 cap hits in the 24 Phase 04 near-wall cases at 3.05 M (measured) and in the 72-point grid.
- **D13-L4.** F12, F14: a fresh, disjoint final range.
- **D13-L5 (product, AQ10 quoted in §D).** Sizing output-changing parameters to rebuild times is Maisara's.

**Debt register.**

| seat | commits | undo | evidence | repaid |
|---|---|---|---|---|
| S1 (2/2) | random tail error of about 0.4–1.1 dB SE in long-window rooms with a fully absorbing face, and 0.44–0.64 dB in the low-α 100 m cube at s = 1 | W_max (Q2) | Q2; Phase 12 presets | Q2 answered |
| S2, S5, S6 | W_max and n\*_max pinned from C++ | golden round before release | C++ benchmark | AX rows |
| S4 | W1 headroom depends on n\*_max | Q2 | C++ W1 | Q2 |
| S7 | SE target, W_max and n\*_max set shipped bits | golden round before release; announced change after | – | first release |
| S8, S9 | the 1 000 floor is [Hyp] | parameter | researcher (pilot-size rule) | sourced |

**Strongest objection.** Seat 1 at 2/2 sits in the rooms the switch exists for. It holds because the median errors there are small:

| room | old error (AX16, systematic) | new under (A): median | p5/p95 |
|---|---|---|---|
| layout 4 | +3.87 dB | −0.29 … +0.34 dB one-end | ±1–2 dB |
| layout 5 | −1.17 dB | −0.29 … +0.34 dB one-end | ±1–2 dB |
| closed 100 m cube, s = 0.3 | +0.09 / −0.06 dB (builder §3) | random SE 0.11–0.20 dB | – |

The closed 100 m cube is the one place where the switch adds error, both sides under 0.2 jnd. That cost line is in Q2.

**Confidence:** medium (seven † cells, two confirmations pending, provisional parameters).

**Reversal:**
- Q2's answer;
- S2-a or S4-a rated 3;
- n\*_max below 1 000 at the C++ cost;
- realised work above W_scene plus one block.

---

## D-T2 Resolution rule: NEEDS MAISARA (Q1)

**Map.** L2-F2 is vetoed (S5 2/3). L2-F1R: S1–S8 at 2/2 (S5 **2/3**), S9 1/2. The bias reading: S1 1/1, S2 0/1 (with its per-class condition), S3 0/1, S5 0/1, S6 1/1, S7 1/0, S8 0/0, S9 1/1. Seat 4 states a preference and gives no cell. Max 1.

Every in-bounds option carries a 3. The variant composed from conditions is the bias reading, which departs from the convening's reading of AX36 (accepted by Maisara). So it is hers.

**Q1 for Maisara.** Your 1 % rule (AX36) was written for patch size, where the error is systematic. The new estimator's error is random and measured. Should the rule apply:
- (a) to the estimator's **bias**, checked in CI;
- (b) to **every scene's random error**?

**(a) Bias reading.**
- **Shipped precision:**
  - target SE 0.083 dB (0.08 jnd) wherever the work cap does not bind: W1, CR4, all six Phase 04 rooms, near-wall cases included (achieved ≤ 0.082 dB at n\*_max 8 000, ≤ 0.124 dB at about 1 020; C14 (b));
  - where it binds, Q2 decides: under Q2 (A), 0.39–1.11 dB in layouts 4/5 at s = 1, 0.11–0.20 dB in closed 100 m cubes, 0.44–0.64 dB in the low-α 100 m cube at s = 1.
- **CI check (Release, hidden tag).** Per band and per case class: reference positions, one-end near-wall, absorbing face, small rooms, 100 m (Seat 2). Tested both pooled and per class.
  - The mean signed deviation from the reference must be ≤ 1 %.
  - N is pre-registered so that 3·SE_class ≤ 1 % − ℓ_ref,class. ℓ_ref is the finest certified rung's last-halving change, up to 0.37 % in the gated set; this mirrors D-T1.4's τ.
  - Classes with ℓ_ref ≥ 1 % are reported only (layout-4/5 edges and corners).
  - The BRAS report prints the Monte Carlo SE (Seat 9).
- **Cost:** CI time only.
- **Board:** max 1, over eight rated cells.

**(b) Strict reading.** Costs are relative to Tol-2's paths, with the 100 m cube's work in units of the provisional W_max (A) = 3.05 M. Restore uses the prototype's cube100 cost, 34 ns at 1 thread and 9.0 ns at 4 threads, with the 1.884 s build. All figures [Inferred].

| variant | paths vs Tol-2 | 100 m work vs W_max (A) | 100 m restore, 1 / 4 threads | 14 restores (1 thread) | W1 rebuild (1 thread) |
|---|---|---|---|---|---|
| L2-F1R (p ≥ 0.999 per case; family false-fail 6.4 % / 6.8 % at 66 / 70 cases) | 19.75× | ≈ 32–35× | ≈ 8.6 / 3.7 s | ≈ 120 s | ≈ 93–121 ms |
| family α 1 % (z 3.79–3.80, SE ≤ 0.373 %) | ≈ 26.3× | ≈ 43–47× | ≈ 10.8 / 4.2 s | ≈ 151 s | ≈ 117–154 ms |
| L2-F2 (AX11 threshold/3, SE ≤ 0.33 %) | ≈ 32.9× | ≈ 54–58× | ≈ 13.0 / 4.8 s | ≈ 182 s | ≈ 140–187 ms |

- Every variant exceeds pluginval's 30 s watchdog over 14 restores, and the AQ10 W1 target of 50 ms.
- Under any cap that protects restore, the 100 m cube cannot reach the strict SE.
- Precision bought: 0.016–0.019 dB, about 1/50–1/60 jnd.
- **Each variant requires your override of Seat 5's veto.**
- Under (b), D-T1.1's S4 and S6 cells reopen, and Q2 is forced toward (B) or (C).

---

## D. Q2 for Maisara: what sets the work limits? (W_max and n\*_max; extends Challenge 1)

**AQ10, quoted exactly:**
- "IR rebuild ≤ 50 ms (target)."
- "Full rebuilds (room or material changes) are recorded, not budgeted. A miss is recorded in §0 with the time and the effective update interval it implies (AQ4). It is not optimised before Phase 13, and it is never met by shortening the image list or N_cap: that changes the output, so it goes through AX20/AX22 and /fix-plan."

Both diffuse work limits change the shipped tail level in order to meet a time:
- **W_max** meets a full-rebuild (restore) time, which AQ10 records and does not budget.
- **n\*_max** meets the 50 ms position-rebuild **target** before Phase 13.

So both are yours. That is why n\*_max is in Q2.

**Q2a: W_max.**
- **(A) Size it to pluginval's restore watchdog** (30 s ÷ 14 restores, minus today's 100 m build): 3.05 M evaluations per emitter (provisional).
  - Every gated 100 m scene uses its full cap: restore 2.14 s, and 14 restores take 30.0 s, at the watchdog (C14 (c)).
  - Ordinary rooms: 0 cap hits in 24 near-wall cases in the six Phase 04 rooms at this value (C14 (b), measured), achieved SE ≤ 0.082 dB.
  - Capped rooms:
    - layouts 4/5 at s = 1: SE 0.39–1.11 / 0.16–0.60 dB. Old error +3.87 dB (layout 4), −1.17 dB (layout 5).
    - closed 100 m cubes at s = 0.3: SE 0.11–0.20 dB, against an old error of +0.09 / −0.06 dB.
    - low-α 100 m cube at s = 1: SE 0.44–0.64 dB.
  - Board: Seat 1 at 2.
- **(B) About 11× more** (sized to Seat 1's floor).
  - Restore 2.16–4.83 s per restore, 30.2–67.6 s for 14, so the watchdog is exceeded in every gated scene. The worst is the low-α s = 1 cube at about 4.8 s at both n\*_max values; the flutter cube is 4.83 s at n\*_max 8 000 and 2.73 s at 1 020 (C14 (c)).
  - 100 m cube SE 0.05–0.12 dB.
  - Not rated by Seat 5. A veto would be yours to override.
- **(C) Move the diffuse solve off the synchronous restore and prepare** (Seat 5's route, about a phase of Phase 07 rework, after this session). (A) ships meanwhile.

**Q2b: n\*_max.**
- **(i) About 1 020, sized to 25 ms of the W1 target** (Seat 4; provisional, re-derived in C++). W1-class SE about 0.06 dB; Phase 04 near-wall SE ≤ 0.124 dB.
- **(ii) 8 000 fixed.** SE about 0.023 dB in W1, but the diffuse solve alone would take about 0.25 s per W1 rebuild on the prototype at 1 thread [Inferred]. Seat 4 goes to 2/2.

Both are inaudible (≤ 0.12 jnd).

**Timing:** both must be fixed before the first release (Seat 7). Before then a change costs one golden round.

---

## D-T6 Regression bound: RS-2+ / B6-1F / M-2 (stands, now 9/9 convened)

**Map** (Seats 4, 6, 8 not required, 0/0; Seat 7 now rated):

| option | S1 | S2 | S3 | S5 | S7 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|
| **RS-2+** | 0/0 | 0/0† | 0/1 | 0/0 | 0/0 | 0/0 | 1 | 1 |
| **B6-1F** | 0/1 | 0/0 | 0/1 | 0/1 | 0/0† (i–iii) | 0/1 | 1 | 4 |
| **M-2** | 0/0 | 0/0 | 0/1 | 0/0 | 0/0 | 1/0 | 1 | 2 |

Seat 7's composite cell is 0/1, and 0/0 with (i)–(iii) included. The losing rows are unchanged. Seat 7's own: RS-1 1/2, B6-2 1/2, M-1 1/1.

**DECISION.**
- **Room set** (fixed in round 1, not moved after C14, as Seat 7 asks):
  - `stone_box`;
  - W1 (both emitters);
  - the three (A) s-cases;
  - the small room: 3 × 2.5 × 2.5 m, α 0.03, s 0.1; listener (1.5, 0.667, 0.425) m; emitters (1.05, 1.667, 0.5) and (1.95, 1.667, 0.5) m.
- **Gate (B6-1):** |ΔL_C++ − ΔL_ref| ≤ τ = 0.25 dB per emitter and band, all 8 bands.
  - Family: 9 emitter-cases × 8 bands = 72 case-bands, z_FW = 3.81 [Inferred].
  - **Gate N.** Shipping N for every case whose shipping SE satisfies z_FW·SE ≤ τ − ℓ_ref (SE ≤ 0.066 dB). This meets Seat 7's request: the small room ships at SE 0.006–0.013 dB (C14 (d)). Otherwise that case runs at test N under the D-T1.5 rule, with its shipping-N value reported beside it.
  - On a fail: stage 2 on a disjoint range at 4× N, no reseed (Seats 5, 7).
  - The small room raises the geometric both-near diagnostic but not U. Its agreement licenses no accuracy claim for both-near positions in general (Seat 7).
- **Flags (not gates):** |ΔL| > 0.68 dB; Seat 1's |mean| > 0.5 jnd.
- **Seat 7 (i)–(iii):**
  - (i) After release, a regeneration of the ΔL_ref golden that moves a uniform-room ΔL by more than τ/3 is announced in advance in the release notes.
  - (ii) Public wording comes from the latest paired report, and a fired flag removes it before release.
  - (iii) The report records the date the room set was fixed.
  - Public copy says "the same material on every surface", never "uniform-α".
  - "Nothing audible changed" also needs Seat 1's confirmation on ΔC80 and ΔEDT.
- **Report:** paired before/after at the same tailSeed, R ≥ 30: ΔG, ΔC80, ΔEDT, ΔT30 and the seam step, all bands.
- **M-2:** tracer runs on the five mixed Phase 04 rooms (r_d below the listener clearance, two radii), reported, not bounded.

**Load-bearing claims.**
- **D6-L1.** C10: the uniform-α fixtures.
- **D6-L2.** C2: 0.43 dB comes from one geometry.
- **D6-L3.** C14 (d): small-room ladder converged to 0.0003 %; shipping estimate within ±0.015 dB.
- **D6-L4 [Inferred].** z_FW = 3.81 over 72 case-bands.

**Debt register.**
- S1: audibility rests on the report.
- S3: M-2 tracer runs.
- S5: the ΔL_ref golden is regenerated with `ref_hybrid`.
- S9: the B6-1 later 1.

All are as in round 1. Seat 7's later is repaid by (i)–(iii).

**Confidence:** medium. **Reversal:** a stage-2 gate fail, or C11 showing |ΔL_ref| > 0.68 dB (reported as a physics finding).

---

## Summary

| id | decision | state | worst-off (cell) | sum | conf. | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| D-T1.1 | T1-F\* + D1–D7, wording, cross-OS comparison | stands, corrected | 1 (under Q1 (a)) | 18 | medium | NFR-1/2/6, AX5, AX6 | Kuttruff Eqs. 4.24, 4.29, 4.35, §5.2; Vorländer Fig. 11.38 | stage-2 estimator fail; face-hash mismatch |
| D-T1.2 | S-1 | stands | 1 | 2 | high | NFR-6 | – | MC spread needed |
| D-T1.3 | N-3W\*\*\* (joint, work-bounded pilot) | revised; S2-a, S4-a pending; parameters → Q2 | S1 2/2 | 20 | medium | NFR-1/2, AQ10, AX5 | Table 6.1 | Q2; seat 3s; n\*_max < 1 000 |
| D-T1.4 | Tol-2: τ 0.25 dB, target SE 0.083 dB | stands, corrected | 1 | 9 | high | NFR-1 | Table 6.1 | ℓ_ref > τ/2 |
| D-T1.5 | CS-3 + CS-NW+: 70 cases / 560 case-bands, z_FW 4.290 | stands, corrected | 1 | 4 | medium | NFR-1, NFR-8 | – | CI budget |
| D-T1.6 | NW-4C+, flag 0.70 m (diagnostic), note U | stands, revised; S2-a, S6-a pending | S1 1/2 | 18 | medium | NFR-1/8, FR-SIM-6 | Kuttruff Eq. 2.50, §8.7 | U at a default placement; reference > τ |
| D-T2 | – | NEEDS MAISARA (Q1) | L2-F1R S5 2/3 | – | – | AX36 | – | her ruling |
| D-T6 | RS-2+ / B6-1F / M-2 + Seat 7 (i)–(iii), gate-N rule | stands (9/9) | 1 | 7 | medium | NFR-1 | Table 6.1 | stage-2 fail |
| D-T3 | – | not needed | – | – | – | AX6 | – | – |

## Challenges to settled decisions
1. **AX36 applied to an estimator: Q1.**
2. **AQ10 "recorded, not budgeted" and "not optimised before Phase 13": Q2** (W_max and n\*_max). This extends Challenge 1.

No conflict found between `board.md` §1 and the PRD.

## /fix-plan list (rounds 1–3; to apply after the interrogator's check and Maisara's answers)
1. **BUILD_PLAN §2, new AX rows:**
   - **D-T1.1:** estimator text with the corrected citations, D1–D7, cross-OS comparison, wording.
   - **D-T1.2:** S-1.
   - **D-T1.3:** the N-3W\*\*\* rule, with W_max and n\*_max as values after Q2. Provisional 3.05 M / C++-derived about 1 020; re-derivation rule.
   - **D-T1.4:** τ, target SE, the cap coupling.
   - **D-T1.5:** 70 cases, ladders, z_FW 4.290, stage 2.
   - **D-T1.6:** NW-4C+, flag, U, GA-limit text.
   - **D-T6:** room set, gate and gate-N rule, flags, Seat 7 (i)–(iii), M-2.
   - **D-T2:** after Q1.
2. **AX36 (c):** resolved (R1 certified at 2.5 m in CR2/CR3/CR4; R2 = D-T1.1). Restated after Q1.
3. **AX16:** "switched" with the ΔL_b,tr table (phase-05b2 §4 item 7). **AX21:** cross-reference.
4. **AQ10:** amendments only if Maisara accepts Challenge 1 and/or Q2.
5. **phase-05b2:**
   - §3: D-T1/D-T2/D-T6 settled, D-T3 not needed.
   - §4 scope:
     - the agreement suite;
     - the reported set;
     - the near-corner reference;
     - M-2 tracer runs;
     - C15 re-run before the goldens;
     - a both-near omni render in the listening pack.
   - §5 acceptance:
     - agreement over 70 cases at z_FW 4.290 with stage 2;
     - the D-T6 gate;
     - the cross-OS E_target comparison;
     - the D5 hashes;
     - the RNG known-answer test.
6. **phase-08:** a test that E_b is bit-identical between omni and binaural and between the ears; a both-near binaural render in the listening pack.
7. **phase-11:** the "approximate" note (U): settled scene, info view, wording by Seats 6 and 7.
8. **phase-12:** a check that U stays silent at every preset's default placement (reported).
9. **phase-13:** W_max and n\*_max re-checked on the release machines. Q2 (C) scheduled if chosen.
10. **BUILD_PLAN §0 records:** W1/W2 including the diffuse share; flags at the gated scenes; realised work.
11. **Ledger:** rows P05B2-T1T2T6-01…36 with this round's answers. Seat 7's D-T6 row.

## For Maisara
- **Formulation and test (D-T1.1, 1.2, 1.4, 1.5):** settled.
  - A fast, seeded random-sampling estimate of the validated model.
  - The noise seed never changes the level.
  - The C++ must match the reference within 0.25 dB on 70 pre-registered cases.
- **Near walls (D-T1.6):** settled.
  - An "approximate" note shows only when an estimate is actually weak: in rooms like the extreme test rooms, or with both the mic and the source against walls.
  - Seats 2 and 6 confirm the exact trigger.
  - Seat 1 gave the most: both-near tails can read low.
- **Uniform rooms (D-T6):** settled, now including Seat 7's rules for the public "nothing changed" wording.
- **Q1:** apply your 1 % rule to the method's bias (checked in CI; users get 0.08 dB precision wherever the work limit doesn't bind), or to every scene (about 20–33× the cost, restores of about 9–13 s at 100 m, and an override of Seat 5's veto)?
- **Q2:** two work limits change the sound to meet a time, which your AQ10 does not budget.
  - Size the big-room limit to the 2-second restore budget: about ±1 dB of random error in extreme absorbing rooms (old error +3.9 / −1.2 dB), and 0.1–0.2 dB in closed 100 m rooms (old about 0.1 dB).
  - Or spend 11× more: restores 2.2–4.8 s, past pluginval's watchdog.
  - Or move the work off the load path in a later phase.
  - Separately: may the small-room limit be sized to the 50 ms rebuild target? It costs about 0.06 dB of inaudible error.

Files:
- /home/user/makroof/docs/review/phase-05b2/26-interrogator-T1-T2-T6.md
- /home/user/makroof/docs/review/phase-05b2/27-orchestrator-C14.md
- /home/user/makroof/docs/review/phase-05b2/28-seat7-D-T6.md
- /home/user/makroof/docs/review/phase-05b2/25-decider-round2-T1-T2.md
- /home/user/makroof/docs/review/phase-05b2/21-decider-decision-T1-T2-T6.md
