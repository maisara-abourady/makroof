<!-- Saved by the orchestrator from the decider's report, 2026-11-22. -->

# Phase 07c-2, decision round 1: D-W1 and D-W2

To be saved as `docs/review/phase-07c-2/5-decider-decision-r1.md`.

**Outcome in brief:**
- **D-W1** is decided as a rule, but the W_max number cannot be pinned yet. A FOR MAISARA answer (FM-W1b) picks the higher-W form of the rule on the PRD's "accuracy first". About ten measurements must come in before the pin (M1–M10).
- **D-W2** is decided as a full ABX design. The run waits on one research item: a dry speech source with a licence we can use.
- The keyless-load path is **not** decided. It stays with the class (c) round that follows the ABX. No class (c) source can be admitted without the ABX result (AX47), so K-a, which is what the code already does, stays in force until then.

## 0. Corpus and PRD digest

**Corpus:** `docs/corpus/SOURCE_COMMIT` = c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. I re-read these myself:
- Vorländer Table 6.1 (L2056–2065): jnd of G 1 dB and of C80 1 dB, 500–1000 Hz.
- Vorländer §15.3 and Table 15.1 (L3957–3966): "Proposal for update intervals for some interactions of listener and source movement". Rows: 700 ms for a move > 0.25 m (specular part); 3 s for a move > 1 m (specular and scattering part). Derived from 30–50 cm/s movement.
- Toole §19.1.1 (L3473): about 1 dB is the smallest audible change in overall loudness; "3 dB is easily perceived".
- Zotter & Frank §4.8 (L1515): "in monophonic noise playback loudness differences below 0.5 dB are audible".

**PRD digest (unchanged from file 1):**
- **For whom:** producers and DJs who do not know spatial audio.
- **Outcome:** an accurate designed space. Accuracy comes first, and heavy CPU or latency is acceptable when it buys accuracy (Key decisions "Accuracy vs CPU"; NFR-1, NFR-2). The plugin must stay "usable in a DAW session" (NFR preamble). Movement must be smooth (NFR-3, FR-SIM-6). Reopening restores exactly (NFR-6).
- **Bounds:**
  - NFR-8 and AX5;
  - AX41: W_max is a pinned work count, never a time cap;
  - condition 3: "not kept at (A)", her accepted J1 answer;
  - AQ10 (1): the restore gate at the two gated builds;
  - AX38 4c (d): no W_max cut once pinned;
  - no instance cap (FR-3D-5, FR-3D-6, FR-SIM-7);
  - condition 1: lands before release;
  - AX47 bound 1 dB with its 0.5 dB reversal; AX49 L4; D-B3 condition A;
  - 07c §9: n\*_max and the estimator are out of scope.
- **Verification:** automated checks; goldens change only through `update_goldens.py`; listening is a person's action.

---

# D-W1: W_max under (C)

## Knowledge inventory

| K | what | source | status |
|---|---|---|---|
| K1 | Gated cubes saturate: low-α s0.3 work is fixed at 1.25–1.26 × the pin from ×2; flutter at 3.29 × from ×4 | part 2 T1, T3; work counts are deterministic and equal on three OSes (AX39 D5/D7) | known |
| K2 | Single-thread solve time is linear in realised work (ns per evaluation flat, max/min 1.02–1.37) | T2, local Linux | known on Linux; other OSes under-informed (M1) |
| K3 | Capped SE against W: at ×8 every non-both-near layout 4/5 case is ≤ 0.256 dB and the s = 1 cube is 0.134 / 0.123 dB with band VOV 0.030 / 0.023; at ×4 listener_edge is 0.378 and listener_corner 0.426 dB | T3 (SE is deterministic, D5) | known |
| K4 | Both-near cases do not improve with W (VOV_union 0.41–0.55, SE 0.5–1.2 dB at ×16) | T3, finding 5 | known |
| K5 | 8-instance 100 m / 96 kHz final-settled time at the pin is 9.7–13.3 s, dominated by synthesis | F6 (b) | known |
| K6 | Solve share of the 36-rebuild bounce: 1.6–7.8 % | F7 (derived) | known as a derivation; at capped producer scenes uninformed (M9) |
| K7 | Table 15.1's conditions: VR update intervals for movement | corpus L3957–3966; researcher R29 | known (conditions differ: applied by extension) |
| K8 | Printed `nsPerEval` counts the work twice | F1, from the code | known |
| K9 | Stage-1 and the final share one `DiffuseLimits`; a raise makes a keyless solve run at the new W | F9, from the code | known |
| K10 | Prefix holds at n\*_max-stopped fixtures, not at work-stopped ones | F11, from the code | known |
| K11 | Single-thread per-scene cost on 07c-era code, three OSes | 05h c309589 only (F2) | **under-informed (M1)** |
| K12 | ISM latency of an edit that arrives mid-solve, at W | Seat 3, from the code (`ScenePipeline` L315, L114, L849, L494–543) | **uninformed (M7)**; the code claim is the seat's, for the interrogator |
| K13 | `medium_room` insertion cost at W | Seat 6 [Inferred] | **uninformed (M5)** |
| K14 | s = 1 cube 30-replicate p95 at the pin | none | **uninformed (M3)** |
| K15 | Host behaviour on a slow offline render | R14–R20: a wait, with no documented timeout; REAPER and Studio One unverified | under-informed; not load-bearing (no seat sets a ratio cap that rests on it) |

K1–K10 carry the **rule**. K11–K14 carry the **pinned number**. So the rule is decided here and the number waits for measurement.

## Options

- Options as convened: W-1 to W-6.
- Reworded during the round, using the seats' own conditions:
  - W-1′ (Seat 5) and W-5′ (Seat 2): 3 s per scene, single thread, read on a scene that spends its whole W_scene.
  - W-6′ (Seat 1): the floor at the gated cubes and the s = 1 cube, and SE ≤ 0.33 dB at every layout 4/5 case that is not both-near.
- My two composed variants, each built from those conditions:
  - **W-C2:** pin the **smallest** W that meets W-6′, provided it is at or below the upper terms.
  - **W-C1′:** pin the **largest** W that is at or below every upper term, provided it is at or above the W-6′ minimum.
  - The upper terms are: 3 s single-thread per scene; Seat 8's bounce term; Seat 3's 700 ms ISM hold (C-a (ii)).
  - W-4 becomes a printed record of the solve's share, never a term.

## Tension map (now / later; reasons in the seats' words, shortened)

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| W-1 literal ("costliest gated scene") | 0/1 | 1/1 | 1/2 "ill-posed on the costliest gated scene" | 1/1 | **2/2** "no finite W" | 1/1 | 1/1 | 1/2 | 1/1 | 2 | 19 |
| W-2 | 0/1 | 1/2 | **2/2** "ISM hold 1.1–1.65 s" | 1/2 | 1/2 | **2/2** "settle 4.2–5.3 s" | 1/2 | 1/2 | 0/1 | 2 | 23 |
| W-3 | 0/1 | **2/2** | **2/2** | 1/2 | **2/2** | **2/2** | 1/1 | **2/2** | 0/1 | 2 | 29 |
| W-4 | **2/2** | **2/2** | **2/2** | **2/2** | **2/2** | **2/2** | **2/2** | 1/2 | 1/2 | 2 | 34 |
| W-6 as worded | **2/2** "unsatisfiable" (both-near) | 1/1 | 1/2 without conditions | 1/1 | **2/2** "W-6 alone" | 1/1 | 1/2 | 0/1 | 0/1 | 2 | 22 |
| **W-C2** | 0/1 (W-6′ "prefer") | 1/1 (W-6 "as the acceptance test") | 1/1 (W-6 "with conditions" C-a to C-d) | 1/1 ("W-6 bounded by W-5") | 1/1 *(read from conditions)* | 1/1 (W-6 "without both-near … ×8") | 1/1 *(read from conditions: "restrict it to the classes W can fix")* | 0/1 ("W-6 inside W-5") | 0/1 (W-6) | **1** | **15** |
| **W-C1′** | 0/1 (W-1 "read on a scaling scene", prefer) | 1/1 (W-5′) | 1/1 ("W-5, composed with my terms") | 1/1 (W-1) | 1/1 (W-1′) | 1/1 (W-5 = min(W-1, bounce)) | 1/1 (W-5 with its bounce term) | 1/1 (W-5 "holds the bounce with my term") | 1/1 (W-1 / W-5) | **1** | **17** |

Notes on two cells:
- **S5 on W-C2.** Seat 5 rated "W-6 alone" 2/2 for two reasons: "gives ×1 at the gated scenes" and "no finite answer for both-near". W-C2 removes both. It is bounded above by Seat 5's own W-1′, with all of W-1′'s conditions adopted, and it uses W-6′ as the "check beside W-5" that Seat 5 can live with.
- **S7 on W-C2.** Seat 7's condition for W-6 was "W-6 → 1: restrict it to the classes W can fix". W-C2 does that.

The interrogator should check both readings. If either seat disputes it, the cell is put to that seat in a second round.

## Minimum-tension working

1. **Bounds.** W-A0 is out (condition 3). Nothing else breaks a bound. The m ≥ 2 floor below keeps every option off (A).
2. **Veto.** No seat gave a 3.
3. **Worst-off seat.** W-1 literal, W-2, W-3, W-4 and W-6 as worded each have a 2. W-C2 and W-C1′ both have a maximum of 1, so they survive.
4. **Compose.** W-C2 and W-C1′ are already composed from the conditions. No further composition lowers the maximum.
5. **Sum.** W-C2 has 15 and W-C1′ has 17. W-C2 wins.
6. **Reversibility.** Not needed after step 5. It would also favour W-C2: a lower pin can be raised later, while a pin cannot be cut (AX38 4c (d)).
7. **Board DECISION: W-C2.**

## Acceptance for Maisara, and FM-W1b (the PRD governs)

The PRD check finds a ranked requirement that points to the other surviving option:
- NFR-1: "Accuracy is the top priority".
- NFR-2: "Heavy CPU and latency are acceptable when they buy accuracy."

W-C1′ buys lower SE than W-C2. On the sweep, SE at ×16 is ≤ 0.164 dB, against 0.11–0.26 dB at ×8. It does so inside the same usability bounds: the 3 s settle, the 700 ms ISM hold and the bounce term. So FM-W1b below governs, and **the applied rule is W-C1′**.

## Load-bearing claims

- **D1-L1 (code and measurement, K1).** The gated cubes stop costing more from ×2 and ×4. A term written on them sets no bound, so every term is read on the capped reported set.
- **D1-L2 (measurement, K3).** W-6′ fails at ×4 (0.378 and 0.426 dB > 0.33 dB) and holds at ×8, so the W-6′ minimum m\* is between 5 and 8.
- **D1-L3 (measurement, K4).** Both-near cases are excluded from W-6′, using the AX44 both-near diagnostic flag. No W fixes them, and their remedy is outside 07c §9.
- **D1-L4 (records, K5).** W-4 as a sizing term admits no W above (A). It becomes a record of the solve's share of the settle.
- **D1-L5 (corpus, K7).** Table 15.1's rows are update intervals for listener or source movement. They are applied by extension: 3 s is the settle anchor, and 700 ms bounds the ISM latency after an edit (Seat 3's mapping).
- **D1-L6 (derived).** The 3 s term uses the per-scene cost, counted once:
  - cost(m) = m × 6.10 M × r_max(m) × c₁;
  - r_max(m) is the largest realised work / W_scene over the capped reported set at m. Up to 1.031 is measured (T3), above AX41's 1.02 (Seat 2).
  - c₁ is the worst-of-≥ 3-runs single-thread ns per scene evaluation, on the worst CI OS.
  - Orientation only, not a pin: with the 05h Linux c₁ of 44–56 ns and r_max = 1.03, cost(8) = 2.21–2.82 s ≤ 3 s.
- **D1-L7 (product, FM-W1b).** NFR-1 and NFR-2 rank accuracy above CPU, within usability.

## DECISION D-W1 (rule applied per FM-W1b)

**W_max per emitter = m × 3.05 M image evaluations, with m an integer.**
- **Lower bound.** m ≥ m\*, the smallest integer m ≥ 2 at which W-6′ holds. W-6′ means:
  - at the two gated cubes and the s = 1 cube: SE ≤ 0.33 dB per emitter and band, plus one of floor clauses (a)–(d) (AX38 4c);
  - at every layout 4/5 s = 1 case of the reported set without the AX44 both-near flag: SE ≤ 0.33 dB per emitter and band.
- **The pin is the largest m ≥ m\* that meets all of:**
  - **(U1)** cost(m) ≤ 3 s (D1-L6) on the capped reported set, on the worst CI OS, worst of ≥ 3 runs;
  - **(U2)** Seat 8's bounce term: the bounce time W adds, on a 36-rebuild 3-minute position-automation bounce at layout 4 s = 1, at pool size on the worst OS, is ≤ 0.25 × real time; and the 48 kHz bounce is ≤ 1 × real time on every OS;
  - **(U3)** Seat 3's C-a (ii): the ISM latency of a position edit that arrives mid-solve is ≤ 700 ms, at 1 instance, on the worst OS, in a capped scene.
- **If no m ≥ m\* meets U1–U3,** the matter returns to the board: Seats 1, 3, 5, 6 and 8, with C-a (i) (cancel-on-edit) on the table. It is never resolved by a time cap.
- **Records, never terms:**
  - the solve-attributable share of the AX38 (iv) 8-instance settle;
  - keyless restores of the s = 1 cube and layout 4 default;
  - 8 × s = 1 cube keyless load against the 1 / 3 / 10 s anchors.
- **Seat 6's insertion condition.** If `medium_room` insertion takes > 1 s at pool size on the worst shipping OS, insertion goes to the class (c) round. W is not cut.
- **Seat 1's condition.** If the s = 1 cube's 30-replicate p95 at the pin is > 1 dB, it is escalated as AX38 4c says.
- **Expected value:** m between 8 and 11, about 24–34 M per emitter. Not a pin.
- **Sequencing:**
  - Measurements run on a measurement branch commit, or through the validation-only `DiffuseLimits` override.
  - The shipped constant and the golden round follow the class (c) round (Seat 2's condition).
  - If the ABX record is not in when the rest of 07c-2 is done, no class (c) source is admitted (AX47), K-a stands as the code already does, and the golden round proceeds (Seat 7's backstop).
- **Companion items:**
  - **(b)** No move in `nsPerEval` can be resolved at the instrument's ±25–30 % run-to-run spread, and there is no trend from 05i to S2 (F1; Seats 2 and 3). Seats 2 and 3 were already heard. Fix the denominator so the work is counted once, and rename the field `nsPerSceneEval` (Seat 5). Ratios are unchanged. Print the single-thread per-scene figure as the invariant. Add the `05h-cost` and `[wmax-sweep]` lines to the `ci.yml` summary grep. Drop `[benchmark]` from the sweep after M1 (Seat 5).
  - **(c)** Re-pin in the S2 form:
    - ≥ 3 green runs on the new pins;
    - restores worst of ≥ 10;
    - solveRefMs and k from those runs;
    - the solve bound also guards the s = 1 cube (Seat 3 C-c);
    - AX41's realised-work assertion ≤ 1.02 also applied to the s = 1 cube, which stays capped up to ×8 (measured 0.996 at ×8); its bound is unchanged (Seat 2);
    - flags re-registered: s0.3 cap hit 1 → 0; flutter floor-truncated 1 → 0 at m ≥ 4;
    - AX38 4c starting-state constants and the three AX48 fingerprint hashes re-pinned, with a CHANGELOG reason, in one commit after the W commit (Seat 5).
  - **(d)** The prefix holds only at n\*_max-stopped fixtures (F11). The golden round asserts that the D5 diff touches only open_field, asymmetric_materials, medium_room and edge_values, with the other 8 fixtures byte-identical (Seat 2). Add a cheap test of an exact final-range prefix at n\*_max-stopped fixtures (Seat 5). The changelog never says the raise "only refines" (Seat 7).
  - **(e)** Keep `pluginStateVersion` 2. `v2_modified` must load **keyless**, with exactly one synchronous solve and no warning (Seat 5). Bump `kEstimatorModelId` 1 → 2, as AX48 requires: "bumped with every D5-golden regeneration". Correct the fingerprint comment at L2455 (Seat 2).
  - **(f)** Phase 12 runs the (ii) check at 07c-2's W, and the 12-2 preset records print cap status and SE per preset (Seat 9). Phase 08 goldens are not frozen, so no SE-derived tolerance is needed. The 08-4 CHANGELOG prints achieved SE and U for rooms still capped. 08-4 prints the binaural restore and settle at the s = 1 cube and one layout 4 room, print only (Seat 4).
  - **(g)** On `main` `listed` is false; on HEAD it is true (5b65864). The steward checks that 5b65864 carries the CHANGELOG line and texts T1, T4 and T8 that scope 10 requires.
- **Prints for the golden round:** per fixture, cap hit, N_need / N_cap, achieved SE and |ΔE_b| from (A) to the new W at 500 Hz–2 kHz; any |ΔE_b| > 1 dB is named (Seats 6 and 9).
- **Finding, named (Seat 3, from the code):** an edit that arrives mid-build waits behind the running solve, so condition 4 of 07c-1 holds only after a quiet spell. M7 measures it at the pin and at the candidate W. If it is > 700 ms at the pin, it is a 07c-1 condition 4 defect, routed through `/fix-plan`, independent of W.

**Confidence:** medium. The SE grid is local but deterministic. Time costs exist for Linux only. Table 15.1 is used by extension.

**Reversal condition:** M1–M9 put no m ≥ m\* within U1–U3; or 08-4's heaviest mode; or the 12-2 capped-preset records; or Phase 13 release machines.

## Future-debt register (W-C1′)

| seat | commits later phases to | undoing costs | evidence | repaid when |
|---|---|---|---|---|
| 1 (L1) | both-near stays uncertified at any W; the pin cannot be cut | an estimator change (out of §9) | 12-2, 13 | a board matter after 07c |
| 2 (L1) | a pin from CI single-thread costs not yet measured on three OSes | constant + golden round (state bump after release) | M1; 13 | M1 green on three OSes |
| 3 (L1) | U3 holds only as measured; Phase 10 sets the final crossfade law | re-measure, or cancel-on-edit (C-a (i)) | M7, M8; 08-4; 10 | M7 ≤ 700 ms |
| 4 (L1) | binaural restore and settle at W unknown | binaural golden round after 08-4 | 08-4 prints | 08-4 |
| 5 (L1) | one golden round; capped restores grow linearly under K-a | constant + golden round | M4; 13 | the class (c) round, with M4 |
| 6 (L1) | settle up to about 3 s at capped rooms; insertion routing | class (c) round | M5; 11-3 | M5 ≤ 1 s, or the class (c) round |
| 7 (L1) | about 4 CI runs per round; after release a W change alters the deal | versioned state | 07c-2 CI | landing before release |
| 8 (L1) | bounce at producer-class halls | constant + golden round | M9; 12-2 | M9 meets U2 |
| 9 (L1) | no church-class fixture in W-6′ (Seat 9's suggestion: 2–5 × 10⁴ m³, T60 6–10 s) | add the fixture | 12-1, 12-2 | a fixture added before 12-2 (follow-up) |
| 2, 4, 5, 6 (K-a, later 2, **not part of this decision's map**) | if the class (c) round admits nothing, K-a ships: capped keyless restores grow, the s = 1 cube projects to 35–40 s at ×8, ungated | class (c) round | M4–M6 | the class (c) round rules with M4–M6 in hand |

## Strongest objection

The objection is Seat 4's least-W preference together with Seat 1's criterion 6. Above m\* the SE gain is about 0.1 jnd where the curve is flat, and AX38 4c makes the pin impossible to cut, so FM-W1b spends irreversible CPU. It holds anyway because:
- the PRD ranks accuracy above CPU (NFR-1, NFR-2);
- U1–U3 are measured caps tied to usability;
- every seat keeps a maximum of 1.

It would fail if M7 or M4 showed the larger m breaking the 700 ms hold, or a keyless restore the class (c) round cannot carry. U3 then lowers m.

---

# D-W2: AX47 self-ABX and AX49 L4 design

## Knowledge inventory

| K | what | source | status |
|---|---|---|---|
| K21 | P(X ≥ 12 \| 16, ½) = 0.0384; ≥ 13 gives 0.0106; ≥ 14 gives 0.0021 | researcher §2a; I re-derived Σ C(16, k) = 2517, 697, 137 | known |
| K22 | Fixed sequence controls FWER at α with no adjustment; Bonferroni at α/m | R1 (FDA 2022, read) | known |
| K23 | Power at p = 0.75: 0.630 at 12/16, 0.405 at 13/16 | §2a | known |
| K24 | Level-step thresholds within a stream | R5–R13 | under-informed. **Not load-bearing:** the sizes come from the decision logic (0.9 = the largest step below the bound under test; 0.5 = the reversal bound), not from a threshold |
| K25 | A dry or anechoic speech source with a usable licence | R23–R28 | **uninformed (RQ-W2-6, RQ-W2-7)** |
| K26 | BS.1116-3: a null needs an anchor; 10–15 trials per session | R4 | known |
| K27 | Anchor: "3 dB is easily perceived" | Toole §19.1.1 L3473 | known (conditions: overall loudness; the anchor is checked empirically, ≥ 5/6) |

## Tension map

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| X-1 | **2/1** "FWER 0.0753" | 1/2 | 0/0 | 0/1 | 0/0 | 1/2 | 1/2 | 1/1 | 1/1 | 2 | 15 |
| X-2 | 1/2 | 1/1 | 0/0 | 0/1 | 0/1 | **2/2** "misses 60–80 %" | **2/1** | 1/2 | 0/1 | 2 | 17 |
| X-3 | 1/1 | 0/1 | 0/0 | 0/1 | 1/1 | 1/1 | 1/1 | 1/1 | 0/0 | 1 | 12 |
| X-4 | 1/1 | 1/1 | 1/2 | 0/1 | 1/1 | 1/2 | **2/1** | 1/1 | 0/0 (NOT MY MATTER) | 2 | 16 |
| **X-5** | 0/1 (X-5′) | 0/1 | 0/0 | 0/1 | 0/0 | 1/1 | 1/1 | 0/1 | 0/0 ("sizes reaching 0.5 dB") | **1** | **8** |

## Working

1. **Bounds.** X-1 uncorrected leaves the family uncontrolled, the defect interrogator row DC-06 names. It is out of bounds as scoped by scope 9.
2. **Veto.** None.
3. **Worst-off seat.** X-3 and X-5 survive at a maximum of 1.
4. **Compose.** Seat 1's X-5′ is the concrete X-5. It meets Seat 2's condition ("add 0.5 dB as a second step"), the anchor conditions of Seats 6, 7 and 8, and Seat 5's stop-rule condition.
5. **Sum.** X-5 has 8 and X-3 has 12.
6. **Reversibility.** Not needed.
7. **DECISION: X-5 as below.**

**PRD check:**
- NFR-1 ("pass listening tests"; thresholds from the Expert, whose stand-ins are AQ9 and AX47). It points to no other option.
- X-5 serves NFR-1 with α ≤ 0.05 and stated power.
- X-3 serves NFR-1 but leaves speech untested in effect.
- X-1, X-2 and X-4 strain NFR-1: uncontrolled α, low power, or a changed protocol.

## Load-bearing claims

- **D2-L1 (derived from R1, my working).** The design is two fixed-sequence chains, noise (0.9 → 0.5 dB) at α₁ = 0.0384 and speech (0.9 → 0.5 dB) at α₂ = 0.0106.
  - Each chain controls FWER strongly at αᵢ: a false rejection in chain i needs its first true null rejected at level αᵢ.
  - By the union bound, FWER ≤ α₁ + α₂ = 0.0490. Independent trial sets give 1 − 0.961594 × 0.989365 = 0.0486.
  - This answers Seat 1's graphical-procedure question without a new source. RQ-W2-9 below only confirms it.
- **D2-L2.** Fixed sequence across stimuli (Seat 6's variant) would test speech only after noise has already set the reversal. Speech would then change no decision (Seat 1).
- **D2-L3 (corpus).** The anchor of 3 dB is "easily perceived" (Toole §19.1.1). The anchor criterion is ≥ 5/6: chance 7/64 = 0.109; at p = 0.95, 0.735 + 0.232 = 0.967.
- **D2-L4 (code, Seat 3).** A held chord with no release differs by ≤ 0.06 dB (AX47 (b)), so L4 must expose a free decay.

## DECISION D-W2

**Family and criterion**
- One pre-registered decision listener. Any further listener is pre-registered and splits α by Bonferroni. Results hold for that listener only (BS.1116-3 §3.3, R4).
- AX47's "16 trials" is read as 16 scored trials per test.
- **Noise chain:** 0.9 dB at ≥ 12/16; if detected, 0.5 dB at ≥ 12/16.
- **Speech chain:** 0.9 dB at ≥ 13/16; if detected, 0.5 dB at ≥ 13/16.
- Family α 0.049, one-sided.
- The script refuses to unseal a 0.5 dB block unless 0.9 dB was detected in that chain (Seat 5).
- **Detection at 0.9 dB in either chain** sets AX47's bound to 0.5 dB for all scenes.
- **Detection at 0.5 dB** is recorded as a finding for the class (c) round.
- **Pre-registered power:** at p = 0.75, 0.63 (noise) and 0.41 (speech).

**Anchor**
- 6 interleaved trials of a uniform 3 dB tail step in every block, scored separately; pass at ≥ 5/6.
- A failed anchor voids the block, which is rerun once. A non-detection is never a reason to rerun.
- L4 gets the same 6-trial anchor, so that its null can read "not detected" rather than "inconclusive" (Seat 7).

**Sessions**
- Familiarisation with feedback first, and only then (BS.1116-3 §4.1).
- 22-trial blocks with a break at trial 11 (§4.2).

**Step**
- A tail-level change of g dB in energy, uniform in all 8 bands.
- Two IrSets from one StagedBuild through the existing `useDiffuseLevel` override (E_b and E_b·10^(g/10)).
- Joined by the shipped 30 ms AQ4 equal-gain fade (AX18).
- Rendered through `render_cli --realtime-emulation` (RealtimeEngine), fixed block, P = 512, onset at a seeded partition boundary.
- The g flag is validation-only and off by default. A test shows `src/plugin` never reaches it. At 0 dB it nulls bit-exactly against the shipped render.
- Assertions on every stimulus:
  - early parts bit-identical;
  - 10·log10(E(diff)/E(final)) = 20·log10(10^(g/20) − 1);
  - the `[ax47-midfade]` checks;
  - `tools.acoustics clicks` clean.
- The per-band measured wet-output change and the window's specular share are printed (Seats 3 and 5).

**Trials**
- B is the pre-step IrSet held throughout; A carries the step; X is A or B.
- Direction: 8 up and 8 down per block, in random order.
- Onset: seeded, inside a pre-registered window, with at least one T30 of the scene before it and ≥ 2 s after it. For speech, the onset falls inside a pause. For pulsed pink noise (Seat 1's signal; Seat 8's continuous-noise preference is recorded), at a gap start, with gaps ≥ the scene's T30 at 1 kHz.
- Fully wet.
- Each interval plays whole from pre-rendered files. No live switching.

**Scene**
- A committed `layout4_s1/default` fixture (Seats 2, 6, 9): fixed tailSeed, 48 kHz, cap hit asserted at the new pin. If default uncaps at the pin, use `listener_wall`.
- Print r/r_c and D/R at the listener.
- The record names it "occupied mid-size hall envelope, not a validated preset" (Seat 9).

**Chain (Seat 4)**
- Omni, presented diotically, on wired headphones, model recorded.
- Fixed and recorded playback level, at or above monitoring level.
- No loudness normalisation of A, B or X.
- 48 kHz with no resampling. No virtualisers, enhancers, ReplayGain or Bluetooth.

**Blinding**
- The seeded key's hash and every stimulus's SHA-256 are committed before the run.
- A script writes the answer file and does the scoring. Nothing of this is in shipped code.

**Record**
- Per stimulus: k/16, exact p, anchor k/6, size, scene hash, tailSeed, commit, chain, level.
- Wording: "detected (≥ c/16, family α 0.049)" or "not detected in 16 trials by one listener (power 0.63 / 0.41 at p = 0.75)".
- "Inconclusive" if the anchor failed. Never "inaudible". No public copy.

**L4 (AX49 as written: 12/16, its own family)**
- A shipped `assembleProvisional` render against the exact render, through the RT convolver.
- The chord is released into ≥ L of free decay.
- Same chain, tool and anchor.

**Speech requirement**
- Recorded, anechoic or close-miked dry, with that property documented (Seat 9).
- A licence permitting a commercial company's internal testing, and redistribution if the stimuli go into an artifact (Seat 7).
- One utterance of ≤ 10 s, pinned by our own SHA-256. Stimuli built locally unless the licence allows the listening pack. A THIRD_PARTY row.
- **The source is RESEARCH NEEDED (RQ-W2-6, RQ-W2-7).** The ABX waits for it.

**Binaural (plan text for phase-08-3)**
- Re-run the AX47 self-ABX on the binaural chain at the bound in force, before Phase 08's goldens freeze (Seat 1's condition; Seats 4 and 8).

**Confidence:** medium. The statistics are known. The speech source is open, and the chain transfer to binaural is [Hyp].

**Reversal condition:** a detection at 0.9 dB (the bound becomes 0.5 dB); a detection at 0.5 dB (finding); the 08-3 binaural rerun differing from the omni result.

## Future-debt register (X-5)

| seat | commits | undo | evidence | repaid |
|---|---|---|---|---|
| 1 (L1) | a null has power 0.63 / 0.41 | re-run (a person's session) | 08-3 binaural rerun | 08-3 |
| 2 (L1) | 0.75 dB is not tested separately | add a chain step | class (c) round | if that round needs it |
| 4 (L1) | omni diotic only | 08-3 rerun | 08-3 | 08-3 |
| 6 (L1) | across-stimulus Bonferroni rather than its sequence | design change | ABX result | the record |
| 7 (L1) | about 5 sessions of listener time; record wording | — | the run | the record |
| 8 (L1) | binaural audibility | 08-3 rerun | 08-3 | 08-3 |

## Strongest objection

Seat 6 (and Seat 2) preferred 0.75 → 0.5 dB, with Seat 6 running noise then speech in one sequence. The design holds because:
- 0.9 dB is the most powerful test of the question AX47 asks ("a step below 1 dB");
- 0.5 dB is still probed in the chain;
- a sequence across stimuli leaves speech decision-free (D2-L2).

It would not hold if the class (c) round needed evidence at 0.75 dB specifically. A chain step can then be added at no cost in α.

---

# FOR MAISARA answers

## FM-W1a: reading of condition 3's "background budget"

**Question.** How are "Seat 6's 3 s per emitter, the AX38 (iv) load mark, and Table 15.1's 700 ms / 3 s rows" read, now that the gated cubes saturate and W-4 is already exceeded at the pin?

**Answer.** They are read as follows:
- **Seat 6's 3 s** is per scene (W_scene), on one thread of the worst CI OS, on the capped reported set. This is the seat's own correction, 05h file 5 L29.
- **Table 15.1's 3 s row** is that same settle anchor, applied by extension. Its **700 ms row** bounds the ISM latency of an edit that arrives mid-solve.
- **The AX38 (iv) load mark** is a printed record of the solve's share of the 8-instance settle, never a sizing term.

**Rests on:** NFR-1, NFR-2, NFR-3 / FR-SIM-6, FR-SIM-7; her J1 acceptance of 2026-11-10.

**Reasoning.**
- Taken as a term, the load mark admits no W above (A), because synthesis alone puts the settle at 9.7–13.3 s (F6 (b)).
- That contradicts the same condition's "not kept at (A)".
- NFR-1 ranks accuracy first, so the term that W cannot move gives way.
- The literal per-emitter reading (about ×16) gives a 4.2–5.3 s settle and an ISM hold of 1.1–1.65 s, which strains NFR-2's "usable" and NFR-3.

**Options against the PRD:**
- Literal per emitter: serves NFR-1 marginally; strains NFR-2 and NFR-3.
- Per scene, with the load mark as a record: serves NFR-1, NFR-2 and NFR-3.
- Load mark as a term: strains NFR-1 (the s = 1 floor is not met) and contradicts condition 3.

**Veto reading.** She approved "per emitter" as written, and accuracy first would accept a longer settle.

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`

## FM-W1b: acceptance of D-W1

**Question.** Should the board's W-C2 (the smallest W meeting the floor) be accepted, or W-C1′ (the largest W within U1–U3)?

**Answer.** W-C1′, as in "DECISION D-W1" above.

**Rests on:**
- NFR preamble: "Accuracy is the top priority";
- NFR-2: "Heavy CPU and latency are acceptable when they buy accuracy";
- Key decision "Accuracy vs CPU: Accuracy first".

**Reasoning.** Both options survive with a maximum of 1. The PRD ranks accuracy above CPU. Lower SE is better expected agreement with measured IRs (NFR-1). Usability is held by U1–U3.

**Options against the PRD:**
- W-C2: serves NFR-2 most cheaply; under-serves NFR-1's ranking.
- W-C1′: serves NFR-1 and NFR-2 to the usability bound.

**Veto reading.** NFR-2 says accuracy must be *bought*: above m\* the gain is about 0.1 jnd (Seat 1), so the extra CPU may buy nothing audible, and the pin cannot be cut. Amends nothing.

---

# RESEARCH NEEDED and MEASUREMENTS NEEDED

## Measurements (orchestrator)

All on 07c-era code. Three CI OSes unless marked local. Each through the validation-only override or a measurement commit.

- **M1.** Single-thread solve time and ns per scene evaluation, **counted once**, plus r_max, over the capped reported set (the s = 1 cube and every layout 4/5 s = 1 placement) at m = 8 and m = 16. Worst of ≥ 3 runs per OS. **Gives U1.**
- **M2.** Local is enough, because the result is deterministic: SE, VOV and the both-near flag per emitter and band at m = 5, 6, 7 (and m\* if outside that range). **Gives m\*.**
- **M3.** At the candidate pin: 30-replicate p95 at the s = 1 cube and the gated cubes, in the file 10 form.
- **M4.** At the candidate: the restore gate as built (K-a), worst of 10, at both gated builds; plus printed keyless restores of the s = 1 cube and layout 4 default.
- **M5.** At the candidate: `medium_room` insertion (first prepare, keyless) and keyless restores of the six Phase 04 rooms, at pool size and on one thread.
- **M6.** At the candidate: the 8 × s = 1 cube keyless load (audible and settled, 48 / 96 kHz), and the solve's share of the (iv) settle.
- **M7.** At the pin and at the candidate: the ISM latency of a position edit at a random point of a running builder solve, 1 instance, s = 1 cube and layout 4 default, pool size. **Gives U3.**
- **M8.** At the candidate: B1-b with the s = 1 cube as the builder scene, with the solve duration printed.
- **M9.** At the candidate: the 3-minute, 36-rebuild bounce on the 100 m s0.3 cube (the AX38 4c record) and a layout 4 s = 1 position-automation bounce, 48 / 96 kHz, with the time added over the pin. **Gives U2.**
- **M10.** Check that 5b65864 matches scope 10 (steward).

The candidate is the largest m with M1's U1 and the projected U2. Measure M3–M9 there. If U3 or U2 fails, step down to m\*.

## Research (researcher)

- **RQ-W2-6 (blocking the ABX).** Recorded speech that is anechoic or close-miked dry, with its recording conditions documented, and with a licence permitting:
  - (i) a commercial company's internal listening tests;
  - (ii) redistribution of processed excerpts in a public CI artifact.

  Cover:
  - VCTK 0.92: resolve the CC BY 4.0 / ODC-BY conflict from the official record;
  - CMU ARCTIC;
  - the McGill TSP database;
  - the Open Speech Repository (Harvard sentences);
  - DAPS;
  - which LibriSpeech or LibriVox readers, if any, are close-miked dry.

  For each, give the checksums offered and the voice-consent statement. **What changes:** which source the ABX uses, and whether the stimuli go into the listening pack or are built locally.
- **RQ-W2-7 (blocking only for distribution).** Read the CC BY 4.0 legal code: the rights to adapt and to share adapted material, and the attribution form for a commercial project's public artifact.
- **RQ-W2-9 (confirmation only, not blocking).** A source for strong FWER control of Bonferroni-split fixed-sequence chains, i.e. a graphical procedure with α passed only within a chain (e.g. Bretz et al. 2009). D2-L1 already derives it from R1.
- **Non-blocking, for Phase 13's host matrix:** REAPER and Studio One offline modes; Live and Logic freeze.

---

# Summary

| id | decision | state | worst-off seat (cell) | sum | confidence | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| D-W1 | W_max = largest m × 3.05 M (m ≥ m\*, W-6′) within U1 (3 s single-thread per scene, capped set), U2 (bounce +0.25 ×), U3 (ISM hold ≤ 700 ms); W-4 as a record; companions (b)–(g) as above | proposed (rule); pin = **measurements needed** M1–M9 | S2–S9 1/1 | 17 (W-C1′; the board's W-C2: 15) | medium | NFR-1, NFR-2, NFR-3, AX41, condition 3, AQ10 (1) | Vorländer Tables 6.1, 15.1 (by extension) | no m within U1–U3; 08-4; 12-2; 13 |
| FM-W1a | reading of condition 3's inputs | for Maisara | — | — | medium | NFR-1, NFR-2, NFR-3 | Table 15.1 | her veto |
| FM-W1b | W-C1′ over W-C2 | for Maisara | — | — | medium | NFR-1, NFR-2 | — | her veto; M7 |
| D-W2 | X-5: noise 0.9 → 0.5 dB at 12/16, speech 0.9 → 0.5 dB at 13/16, family α 0.049; 3 dB anchor ≥ 5/6; shipped-path stimuli; omni diotic headphones; L4 released chord with anchor; 08-3 binaural rerun | proposed; speech source **research needed** (RQ-W2-6/7) | S6, S7 1/1 | 8 | medium | NFR-1 | Toole §19.1.1; Vorländer Table 6.1; Zotter & Frank §4.8 | detection at 0.9 / 0.5 dB; 08-3 |

# Challenges to settled decisions

None beyond FM-W1a. Seat 3's condition-4 finding is a defect route, not a challenge.

# Decided for Maisara

- **D-W1 (FM-W1a, FM-W1b).** We raise the reverb-tail work cap to the largest value that still settles a large, hard-to-compute room within about 3 s on one CPU core, keeps the room's early reflections following an edit within 0.7 s, and adds at most a quarter of real time to a bounce. It must also be at least high enough that every room the cap can help shows no level error above 0.33 dB. Expected: about 8–11 × today's cap.
  - Rests on NFR-1, NFR-2 and NFR-3.
  - Seat 4 gives most (it wanted the smallest raise). It gets back the 08-4 binaural prints and the fact that the value is measured, not guessed.
  - `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (condition 3's "3 s per emitter" read per scene; the load mark becomes a record.)
- **D-W2.** The listening test for interim-to-final level steps uses:
  - one listener, 16 trials per test;
  - pulsed noise and dry recorded speech;
  - a 0.9 dB step first, then 0.5 dB only if 0.9 dB is heard;
  - stricter odds for speech, so that the overall false-alarm chance stays under 5 %;
  - a clearly audible 3 dB check step to prove the session was sensitive;
  - headphones;
  - a repeat in binaural at Phase 08-3.

  Rests on NFR-1. Seat 6 gives most (its noise-then-speech order); it gets back a speech test that always counts. Amends none of her decisions.

**NEEDS MAISARA:** none. Speech-source licensing goes to the researcher, not to her. A lawyer is needed only if a voice reaches marketing (Seat 7).

Files relevant:
- /home/user/makroof/docs/review/phase-07c-2/2-fact-sheet-part1.md
- /home/user/makroof/docs/review/phase-07c-2/2-fact-sheet-part2-wsweep.md
- /home/user/makroof/docs/review/phase-07c-2/3-researcher-RQ-W1-W2.md
- /home/user/makroof/docs/review/phase-07c-2/4-seat1.md … 4-seat9.md
- /home/user/makroof/docs/corpus/vorlaender-auralization.md (L2056–2065, L3957–3966)
- /home/user/makroof/docs/corpus/toole-sound-reproduction.md (L3473)
- /home/user/makroof/docs/corpus/zotter-frank-ambisonics.md (L1515)
