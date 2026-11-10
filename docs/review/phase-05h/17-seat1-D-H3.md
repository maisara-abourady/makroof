# Seat 1 — D-H3 (a), (b), (d)

SEAT 1 POSITION

Corpus present (c1b171f). Yardstick as in my earlier rounds: the G jnd is 1 dB [corpus: Vorländer Table 6.1, L2060, 500–1000 Hz; other bands by extension]; a tail-only error ΔL moves G by less than ΔL. No new persona assumption falls (motion thresholds already set aside: no head tracking in v1). Files read: `16-decider-convene-D-H3.md`; `11-`, `9-`, `13-`, `14-orchestrator-*.md`; BUILD_PLAN AX37, AX41–AX46 and §5 B15; phase-05h §4 item 4, §5, §8; my phase-05b2 files 18 and 23; decider file 25 L180–194; from the code: `test_diffuse_agreement.cpp` L196–284, `test_diffuse_records.cpp` L303–375, `edge_values.json`, `open_field.json`.

---

## (a) AX43's pooled bias check

**1. Reading.** Whether my pooled check |mean z| ≤ 3/√M, z = (C++ − ref)/SE_C++, should carry the reference's certified error ℓ_ref and/or pool by shared reference. Cues: a threshold that must carry its method (§4); a test that measures the system's own floor instead of the thing under test (Strategy B step 1); a check that is red by design is not evidence (criterion 3).

**What my rule was meant to catch.** An estimator bias shared across cases, relative to the true value: a wrong factor or split that would move every user's tail the same way and might be larger in untested rooms. The 0.02 dB figure was the catch size the pooled SE allowed, not a perceptual threshold: 0.02 dB is 0.02 jnd of G, which no listener on any chain with any signal detects. The pooled check's value is diagnostic, not perceptual. My per-case rule already carries ℓ_ref (z_FW·SE ≤ τ − ℓ_ref, file 18 item 2); the pooled formula omitted it. That was an oversight in my own rule, not a design: a pooled statistic whose SE (≈ 0.005 dB) is below the reference's own residual (0.015 dB) measures the reference's floor, not the estimator (K-a6). **A shared 0.015 dB that the reference cannot resolve is not the bias I meant.**

**Is (a) principled or a loosening?** Principled as far as it goes: it enters the same ℓ_ref the per-case gate subtracts, and the catch size for a true shared estimator bias stays ≈ 0.016–0.02 dB (3/√53 × √(0.035² + 0.0156²)). Nothing my rule 4 forbids changes: no reseed, no added N, no wider τ, no dropped case, the constant 3 untouched. Incomplete, because ℓ_ref is a signed residual shared by one room's 10 pairs (Seat 2 to confirm); adding it per case-band in quadrature still lets the shared part accumulate with M as if it averaged out. The principled form for a shared reference error is clustering by the reference that shares it: (e), with (b) as a coarse proxy. The metrology form (E_n) I cannot source: [Hyp], researcher RQ-H3-1.

**Arithmetic I redid, for K-a3/K-a4 [Inferred, the table decides].** The packet carries two incompatible SE figures. (i) Per-case SE 0.03–0.05 dB: then BRAS z_i ≈ 0.0048/0.035 ≈ 0.14, (A) ≈ 0.04, and the 8 Phase 04 case-bands would have to carry mean z ≈ 2.3 to reach 0.44 × 53, which max |dev| 0.046 dB cannot supply at club's SE 0.053 dB (file 14): the sum does not close. (ii) AX46's SE_class 0.03 % over 30 BRAS cases implies per-case SE ≈ 0.16 % ≈ 0.007 dB (and ≈ 0.008 dB for the (A) class): then BRAS z_i ≈ 0.0048/0.007 ≈ 0.7, 30 × 0.7 ≈ 21 of the 23.3 needed, and the sum closes. Under (ii): (b) alone **fails** the BRAS class (0.7 > 0.548) with z as written; (a) scales BRAS by 1/√(1 + (0.0156/0.007)²) ≈ 0.41 at 500 Hz/1 kHz and ≈ 0.75 at 2 kHz, giving a pooled mean ≈ 0.3–0.35 < 0.412, so the decider's "(a) fails at 2 kHz" rests on reading (i). Independent evidence against an estimator bias in the Phase 04 rooms: the M-2 tracer (file 14) shows mixed signs within ±0.045 dB in dead_booth, living_room, classroom and club at tracer SE 0.006–0.055 dB.

**2–4. Ranking and tension (now / later).**

| option | label | now | later | reason |
|---|---|---|---|---|
| (e) per reference room, z with ℓ_ref | prefer | 1 | 1 | Matches the error's structure. Now: a clustering rule and a cluster id in the golden that nobody has written (update_goldens with reason). Later: small M_cluster loosens the pooled limit, but the cluster means' SE is small, so the catch stays ≈ 0.01–0.03 dB (≤ 0.03 jnd). |
| (d) (a)+(b) | can live with | 1 | 1 | Carries ℓ_ref and stops cross-class accumulation; within the BRAS class a room's shared sign still accumulates over 10 pairs. Undo: one loop in the test. |
| (a) | can live with | 1 | 1 | Consistent with my per-case rule; may still fail at 2 kHz under reading (i), in which case it is (c) in disguise. Gets stricter by itself as rungs certify (ℓ_ref shrinks). |
| (b) | can live with | 1 | 1 | Lower power (M 15/30/8); no ℓ_ref, so under reading (ii) the BRAS class fails on its own rung error. |
| (c) red by design | cannot live with | 2 | 3 | Now: a CHECK that cannot pass whatever the estimator does is a measurement of ℓ_ref, not a test. Later: a real shared bias (say +0.1 dB at 2 kHz after a refactor) hides behind the known red; the check I asked for stops existing while appearing to exist (criterion 3; "a flag that always fires trains people to ignore flags", file 23). |

**Debt.** (a)/(b)/(d): a formula or grouping change in one test, ℓ_ref and class already in the golden (from the code: `k.lRef`, `k.cls`); undo = one edit, no golden regeneration. (e): a cluster field in the golden; undo = a golden round. (c): every later CI run and Phase 13's accuracy wording carry an explained red. Evidence arrives: K-a3 now; the next certified rung (ℓ_ref shrinks); the small-room and 100 m classes when gated.

**5. Evidence.** [corpus] Vorländer Table 6.1 L2060. [Observed] files 9, 14. From the code: L198–203, L229, L276–283. [Inferred] all arithmetic above. [Hyp] E_n form → RQ-H3-1. Researcher: whether a shared signed reference error is clustered or added in quadrature in a pooled consistency test.

**6. Conditions.** (c) 3 → 1: the pooled statistic is printed per band and per reference room (not CHECKed) until the clustered rule exists, with a dated note that it cannot pass below ℓ_ref; that is (e) as a report, a stopgap of one golden round at most.

**7. Hand-offs.** Whether ℓ_ref is signed per room: Seat 2. How a round-robin pools over shared references: Seat 9. Implementability and CI gate: Seat 5. Public wording: Seat 7.

**8. Premortem.** Under (c), a refactor of the random stream adds +0.1 dB at 2 kHz, the pooled check was already red, nobody looks, and the contracted engineer finds it months later reading the CI log.

---

## (b) U raised at the default placement of two fixtures

**1. Reading.** Whether U at `edge_values` (pilot ships, SE 0.76 / 3.98 dB, the 3.98 on the +12 dB emitter) and `open_field` (cap, SE 2.4 / 2.1 dB on a tail below −60 dB after t_dir + 50 ms) triggers AX44's reversal or is read as outside Seat 6 (ii)'s scope. Cues: the hardest signal stays fixed between versions (B2; failure library "letting the test signal drift"); a note nobody can act on is noise (criterion 2); my later-2 debt "flagged, not bounded" (B15).

**What U means at each.** At `open_field`, U is true as statistics and empty as perception: ±2.4 dB on a component ≥ 60 dB below the direct sound changes the total by ≈ 3 × 10⁻⁶ dB [Inferred], and the component sits at the decay convention's end-point (T is defined to −60 dB [corpus: Vorländer Table 6.1 context; Kuttruff decay convention]). No test is needed (S2 anomaly: many times a JND). A "level unreliable" note there is **truthful but noise**: there is nothing the user could do that changes anything audible, and a note that fires on every field trains the user to ignore the one in a hall where it matters. At `edge_values`, U is true and salient: a near-rigid 100 m slot with a +12 dB emitter has an audible tail, and SE 3.98 dB at 1 SE is ≈ 4 jnd of G before the tail-share reduction. This is the current worst instance of my B15 debt and should enter that register as its evidence row.

**(d)(i), the display rule.** It costs my later-2 debt nothing, on two terms: it keys on the measured energy ratio (AX37 (5.4)'s existing −60 dB check), never on a preset category or a fixture name; and U itself stays raised in the diagnostics and the Seat 6 (iii) tier, so the record exists. On those terms I rate (d)(i) **1**, not ≥ 2; it may stand. Without the first term it is 3 (a festival preset with a stage wall behind it and an audible tail would lose its note).

**2–4. Ranking and tension.**

| option | label | now | later | reason |
|---|---|---|---|---|
| (d) (a) + the two rules | prefer | 0 | 1 | The hardest case stays in CI with its cause printed; (ii) is my K-b3 demand made standing. Later 1: Phase 12 outdoor presets meet the same cause; the display rule must be keyed as above. |
| (a) reading | can live with | 1 | 1 | Honest if both cases are listed and the pilot-ships path stays exercised. Now 1: a requirement narrowed after the result it failed, and "cannot be moved" is asserted, not shown (K-b3). |
| (b) change the fixtures | can live with | 2 | 2 | Tuning the acceptance signal to pass the test: the only fixture where the pilot ships leaves CI, and the extreme-window path becomes untested. Open_field cannot be silenced by placement at all. |
| (c) reopen U to silence it here | cannot live with | 3 | 3 | A predicate that is silent at SE 3.98 dB says "level reliable" where it is not. Acceptable only as a reopening that raises U on at least the same set, then it is cost (Seat 7's), 1/1. |

**Debt.** (a)/(d) commit Phase 11 to the display rule and Phase 12 to the same reading for outdoor presets (AX41's J1 trigger stays for capped presets with U raised at every reasonable placement); undo = a display rule and a report line. (b) commits the extreme-window behaviour to being unexercised until a user finds it; undo = re-adding the fixture. Evidence arrives: Phase 12 preset checks; the B15 fallback's p95.

**5. Evidence.** From the code: both fixtures; file 9 §"AX44 Seat 6 (ii)". [Inferred] the 3 × 10⁻⁶ dB and the 4 jnd. [corpus] Table 6.1 for the jnd.

**6. Conditions.** (b) 2 → 1: the present `edge_values` scene stays in the reported set under another name with U expected, so the pilot-ships path is still exercised. (c) 3 → 1: as stated in the table.

**7. Hand-offs.** Scope of "valid fixture": Seat 6. Whether a producer builds either scene, and what a field note does to the story: Seat 8. Whether the pilot stopping at the first block is the rule as designed: Seat 2. The B15 register row: plan-editor via the decider.

**8. Premortem.** Under (b), the pilot-ships path leaves CI; a producer builds a long rigid corridor, the tail ships 4 dB off with a note he learned to ignore on field presets; a beta user with a corridor scene notices first.

---

## (d) "W1 both_corner asserts the cap flag"

**1. Reading.** The cap flag is 0 at W1 both_corner (pilot SE ≤ 0.086 dB, achieved 1.122 dB, VOV_union 0.567, U raised through the VOV leg) and the REQUIRE stops the club / living_room both-near rows. Cues: a systematic weakness observed, not hypothesised; the rows I need for B15 do not run.

**What the assertion protects for me.** Nothing directly: the cap path is Seat 5's benchmark. What I need is that U is raised where SE is 1.12 dB (it is), and that the under-read is recorded. **The pilot missing a heavy tail at VOV 0.6 is an audibility matter and sharpens my debt without changing its rating.** In round 2 I wrote that a small pilot under-reads the SE of a heavy-tailed variable and sets N too low [Hyp then]; file 13 makes it [Observed]: a 13× under-read. At this placement, with tail share f = 0.5 [Hyp], 1 SE gives ΔG ≈ 0.6 dB and 2 SE ≈ 1.3 dB, over the G jnd [Inferred]. B15 stays later 2 because U fires there and the debt is registered. What would raise it to 3: a case with achieved SE > 0.33 dB and U silent. The mechanism exists: at a one-end placement, a pilot under-read with cap hit 0 leaves U's second leg (cap ∧ SE > 0.33) silent whatever the SE. No instance in file 13 (every one-end row with SE > 0.33 dB has cap hit 1), but the club / living_room rows must run to show it. The predicate is out at bounds; I record this as B15 evidence, not a reopening.

**2–4. Ranking and tension.**

| option | label | now | later | reason |
|---|---|---|---|---|
| (d) cap benchmark at layout4_s1/both_corner; W1 both_corner asserts U with its flags pinned in the D5 golden; Q-3 finding recorded once | prefer | 0 | 1 | The cap is asserted where it is a property of the rule (N_need ≫ N_cap); pinning the flags makes the draw-dependence visible, which is the honest form. Later 1: a stream refactor flips the pinned flags, costing one golden round, by the rule. |
| (a) read as "U raised" | can live with | 1 | 1 | True and recorded; the deterministic cap exercise is lost unless another case carries it. |
| (c) "cap or floor-truncated or U" | can live with | 1 | 1 | (a) with a disjunction that hides which leg fired. |
| (b) keep red | can live with | 2 | 2 | Red by design, and a REQUIRE that stops my both-near rows: the per-class replicate p95 the AX44 note text needs is never sourced. |

**Debt.** (d): the golden gains W1 both_corner's exact flags (D7 already records n\*/N); undo = a golden row. (b): the Phase 11 note ships qualitative text everywhere for want of the p95. Evidence arrives: the club / living_room rows (this phase); the B15 fallback.

**5. Evidence.** [Observed] file 13; from the code: L342, L372–373. [Inferred] the ΔG figures. [Hyp] f = 0.5.

**6. Conditions.** (b) 2 → 1: the REQUIRE becomes a non-fatal CHECK so the remaining rows run; it stays red, so 1 only together with (d).

**7. Hand-offs.** Whether the under-read is the pilot rule as designed or a defect; Q-3: Seat 2. The benchmark's purpose: Seat 5.

**8. Premortem.** Under (b), the both-near rows never print, Phase 11 ships vague text, a producer with mic and source in a corner gets a 2 dB-weak tail and a note that names nothing; a beta user with a hall preset notices first.
