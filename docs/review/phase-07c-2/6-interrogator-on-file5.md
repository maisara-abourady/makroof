<!-- Saved by the orchestrator from the interrogator's report, 2026-11-22. -->

Interrogator on `docs/review/phase-07c-2/5-decider-decision-r1.md` (decision mode, round 1). Corpus revision: c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

# Interrogator on file 5: D-W1, D-W2, FM-W1a, FM-W1b

## Outcome per item

None of the four items survives as written. The statistics, the corpus citations and Seat 3's code claim mostly check out (two corpus readings are imprecise, D1-L5 and the Zotter & Frank section number). The failures are in how the seats' ratings were read and how the PRD was read.

| item | outcome | why, in one line |
|---|---|---|
| **D-W1** | **TENSION MISREAD** (does not survive) | Four map faults (M-1 to M-4); the backstop also contradicts the phase file. 10 corrections stack on top. |
| **FM-W1a** | **PRD MISREAD** | NFR-2 is cited for "usable", which is in the NFR preamble. NFR-1 is cited as ranking accuracy, which is also the preamble. NFR-3's sentence that sends this very tension to the Expert is left out. The per-emitter option line misreads NFR-2. Amending her decision is within the decider's remit in kind; as written it is not grounded. |
| **FM-W1b** | **PRD MISREAD** | It says "usability is held by U1–U3", but under the backstop keyless-load and insertion time grow with m, and U1–U3 do not bound them. Its accuracy evidence (×16) lies outside U1, and one number is wrong. |
| **D-W2** | **TENSION MISREAD** (does not survive) | The X-5 cells for S2, S5, S6 and S8 are those seats' ratings of other variants. Read from the seats' conditions they tie X-5 with X-3 at sum 12. S6's cell may be a 2, which would change the winner. |
| Seat 3 code claim | **CORRECT in substance, IMPRECISE in one detail** | Checked against `ScenePipeline.cpp`, see ledger row C-1. |

### Map faults in D-W1

- **M-1. S5 on W-C2.** The cell is marked "(read from conditions)", but Seat 5 states no condition of acceptance for W-6. Its words are "W-6, used as a check beside W-5: can live with", and "W-6 alone" is rated 2/2. In W-C2, W-6′ chooses the value and W-1′ only caps it, which is the reverse role.
  - If Seat 5 rates W-C2 2, the board's winner becomes W-C1′. The applied rule is the same, but the ordering and FM-W1b's premise change.
  - S7 on W-C2 is read faithfully (ledger row MAP-3).
- **M-2. The K-a cells are left out.** The brief asked every seat to rate the keyless path beside each option. The decision then ships K-a by default if the ABX is late (the "Seat 7 backstop").
  - The omitted ratings: S2 K-a 1/2, S4 1/2, S5 1/2, S6 1/2 at ×8 (2/2 at ×16).
  - Only Seat 6's condition is fully met. Seat 4's condition ("the class (c) round sees an omni projection … before choosing K-a") is bypassed by the backstop. Seat 5's restore records leave out layout 5. Seat 2's full-W_scene gate projection is not made.
  - So the chosen option's worst cell is 2 (later), not 1. The strongest objection's "every seat keeps a maximum of 1" is false under the backstop.
- **M-3. Seats 2 and 7 conflict, and the map does not show it.** Seat 2 accepts the sequencing only if "the constant is not committed to `src/` until the keyless path is decided. Otherwise K-a becomes the shipped path by default." The backstop does exactly that.
  - The backstop is also INCONSISTENT with phase-07c-2 scope 9: "The ABX runs first … are run in this phase", and the class (c) and load-fallback decisions belong to "this phase's loop".
  - Where the ABX and the class (c) round go instead has no row in the debt register, so debt is dropped.
- **M-4. S2, S5 and S7 on W-C1′ are read from variants with no bounce ratio cap.**
  - Seat 2's W-5′: "W-4 and the bounce are recorded beside it; they do not set W."
  - Seat 5: "recorded per OS with no ratio cap."
  - Seat 7: "No ratio cap from my seat."
  - U2 is Seat 8's ratio cap. The ratings may not move, but each reason must be the seat's own reading of this variant.

### Corrections to D-W1 (needed beyond M-1 to M-4)

1. **Sums.**
   - W-1 literal: 9 + 12 = 21, not 19.
   - W-2: 9 + 16 = 25, not 23.
   - W-3: 12 + 15 = 27, not 29.
   - These options are eliminated at step 3, so the winner does not change.
2. **Step 4 allows one composed variant per round.** decider.md §5 step 4 says "At most one composed variant per round"; the decider built two (W-C2 and W-C1′). This does not change the board's winner, but W-C1′, the option FM-W1b applies, would not exist this round.
3. **The expected value is m 8–10, not 8–11.** U1 alone gives floor(3 s / (6.10 M × 1.03 × c₁)): m = 10 at 44–44.7 ns and m = 8 at 56.4 ns.
4. **The expected value contradicts the decider's own data on U3.** The ISM hold equals the pool solve time (the builder solves on the gate pool, see C-1).
   - Pool(4) medians at ×8 at capped scenes are 664–808 ms (T1; s = 1 cube 791 ms).
   - F1 shows local per-scene pool cost (15.1 ns, low-α ×1) inside CI Linux's 10.27–16.33 ns. So the fact sheet's "about 2× slower than CI" is the `nsPerEval` double count, as Seats 1 and 2 say.
   - U3 therefore projects to bind near m ≈ 7, below 8. With m\* somewhere in 5–8, it may leave no m at all, which sends the matter back to the board.
   - The "Decided for Maisara" line ("about 8–11 ×") must be restated. Seat 3's "CI ~2× faster" and Seat 8's U2 projection rest on the same wrong factor.
5. **Check W-6′ at the pin itself, not only at m\*.** Seat 2's W-5′ condition is "Accept it only if W-6 … is met at that value." The rule silently assumes W-6′ is monotone in m, and m = 9–11 is unmeasured (M2 covers only 5–7).
6. **Seat 1's condition "a three-OS CI print of SE and VOV at the pin" is dropped.** M2 is local only. Adopt the condition or put it to Seat 1.
7. **Seat 5's K-a record must include layouts 4/5.** The decision records only "layout 4 default".
8. **D1-L4 restated.** W-4 fails at (A) itself on Linux (12.0 s) and macOS (12.8–13.3 s). It passes at the pin on Windows (9.7–9.9 s) (F6 (b)). So it admits no W on the worst OS, (A) included.
9. **D1-L5 and §0 restated.** The Vorländer §15.3 text says user behaviour "informs" speed and permitted latency; the table does not say it is "derived from" them.
   - The 3 s row is the whole update of the specular and scattering parts. U1 maps it to the single-thread solve alone. That mapping is by extension and is not an equality.
10. **The K-b veto-grade ratings must be carried to the class (c) round.** They are not in this decision's text: Seat 1 "K-b unconditioned 2 / 3" and Seat 3 "K-b … 3 later".

### Corrections to D-W2 (needed beyond the map fault)

1. **Bounds.** X-1 is one size per stimulus, so scope 9's "per-size 12/16 rule over several sizes" does not literally exclude it. X-1 drops at step 3 instead (S1 is 2 now); the winner is unchanged.
2. **Sums.** X-1 is 7 + 10 = 17, not 15. X-2 is 7 + 11 = 18, not 17. X-4 is 8 + 10 = 18, not 16.
3. **Step-assertion formula.** For the 8 down-steps it must read 20·log10|10^(g/20) − 1|, with E(final) being the unstepped E_b IrSet. As written, a down-step takes the log of a negative number, and this formula is a test assertion.
4. **Zotter & Frank citation.** L1515 sits under §4.9.8 (hemispherical decoding), not §4.8, in §0 and in the summary row.
5. **Debt register.** With S5's X-5 cell read as 1/1, a Seat 5 row is needed (script-enforced stop rule; rerun expected at 08-3 and 09). Seat 7's row has an empty "undo" field.
6. **BS.1116-3 §4.1.** R4 supports "familiarisation mandatory", not "with feedback". The feedback is Seat 1's design choice.

---

## Decision ledger

| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| D-W1 | convening | nine rows | faithful | file 1: all nine convened | — | — |
| D-W2 | convening | nine rows | faithful | file 1: all nine convened; S9 NOT MY MATTER on X-4 sits at 0/0 | — | — |
| D-W1 | map | MAP-1: S5 / W-C2 "(read from conditions)" | TENSION MISREAD | seat 5 L30, L45: no condition stated for W-6; W-6 acceptable only "as a check beside W-5"; W-C2 makes W-6′ the selector | TENSION MISREAD | Q1 |
| D-W1 | map | MAP-2: K-a cells left out although the backstop ships K-a | TENSION MISREAD | seat 2 L49 "K-a: 1 / 2"; seat 4 L25; seat 5 L51; seat 6 L35 (×8 1/2); debt row "not part of this decision's map" | TENSION MISREAD | Q2 |
| D-W1 | map | MAP-3: S7 / W-C2 | faithful | seat 7 L35: "W-6 → 1: restrict it to the classes W can fix"; W-C2 restricts. Name the both-near "known limitation" record | — | — |
| D-W1 | map | MAP-4: S2, S5, S7 / W-C1′ cite variants with no bounce ratio cap; U2 is a ratio cap | TENSION MISREAD (reasons not the seats') | seat 2 L28; seat 5 L82; seat 7 L31 | TENSION MISREAD | Q2 |
| D-W1 | map | MAP-5: sums of W-1 lit., W-2, W-3 | arithmetic slip | recount 21 / 25 / 27 | correction | — |
| D-W1 | debt | DEBT-1: the backstop (no ABX in 07c-2, K-a ships, golden round proceeds) | INCONSISTENT; debt dropped | phase-07c-2 scope 9 "The ABX runs first … run in this phase"; seat 2 L56 condition; no register row | TENSION MISREAD | Q2 |
| D-W1 | debt | DEBT-2: Seat 1 row "repaid when: a board matter after 07c" | names no phase or test | BUILD_PLAN phases | correction | — |
| D-W1 | ordering | ORD-1: two composed variants | step 4 misapplied; winner unchanged | decider.md §5 step 4 "At most one composed variant per round" | correction | — |
| D-W1 | ordering | ORD-2: worst-off seat of the chosen option | wrong under the backstop | with K-a cells the max is 2 (later), not 1 | follows from MAP-2 | Q2 |
| D-W1 | D1-L1 | gated cubes saturate | CORRECT | T1/T3: s0.3 1.25 × from ×2; flutter 3.29 × from ×4 | — | — |
| D-W1 | D1-L2 | W-6′ fails at ×4, holds at ×8 | CORRECT | T3: listener_edge 0.378, listener_corner 0.426 dB at ×4; ≤ 0.256 dB at ×8 | — | — |
| D-W1 | D1-L3 | both-near not fixed by W | CORRECT (measured) | T3 finding 5: VOV_union 0.41–0.55, SE 0.5–1.2 dB at ×16 | — | — |
| D-W1 | D1-L4 | W-4 "admits no W above (A)" | IMPRECISE | F6 (b): at the pin Linux 12.0, macOS 12.8–13.3 s (> 10 s); Windows 9.7–9.9 s | correction 8 | — |
| D-W1 | D1-L5 | Table 15.1 rows; "derived from 30–50 cm/s"; 3 s as settle anchor | IMPRECISE (conditions: VR filter-update intervals; extension declared) | Vorländer §15.3, Table 15.1: "Time available for filter update"; the 3 s row covers the specular and scattering update | correction 9 | — |
| D-W1 | D1-L6 | cost(8) = 2.21–2.82 s | CORRECT | 8 × 6.10 M × 1.03 × 44–56 ns = 2.212–2.815 s | — | — |
| D-W1 | D1-L6 | "Expected m 8–11" | WRONG upper end; INCONSISTENT with U3 | U1: m ≤ 10 (44 ns) / 8 (56.4 ns); U3: T1 pool ×8 664–808 ms, F1 local ≈ CI | correction 3–4 | Q3 |
| D-W1 | hidden premise | H-1: W-6′ holds at every m ≥ m\* | NOT CHECKABLE (m 9–11 unmeasured); load-bearing | Seat 2 W-5′ checks W-6 "at that value" | correction 5 | Q3 |
| D-W1 | hidden premise | H-2: fact sheet's "local about 2× slower than CI" | WRONG (double count) | F1: CI Linux pool 10.27–16.33 ns per scene eval vs local 15.1 ns (T2) | carries into Seat 3's hold and Seat 8's U2 projections | Q3 |
| D-W1 | C-1: Seat 3 code claim | an edit mid-solve waits behind the solve | CORRECT in substance; IMPRECISE in detail | from the code: L315 only bumps `dirty_`; `builderAbandon_` set only at L114, L849; one builder thread (`IrBuilderThread.h` L5). The L539 discard check comes before `finishExact` (L545) and `makeIrSet` (L547), so an edit during the solve does not wait for them; one arriving after L539 does | — | — |
| D-W1 | conditions | Seat 1's three-OS SE/VOV print; Seat 5's layout 4/5 restore records | dropped or partial | seat 1 L66–68; seat 5 L79 | corrections 6–7 | — |
| D-W1 | inventory | K15 marked "not load-bearing" | IMPRECISE | U2 makes a bounce ratio a term; Seats 5 and 7 reject a ratio cap on R14–R20 | correction | Q2 |
| D-W1 | PRD proxy | acceptance block cites "NFR-1: 'Accuracy is the top priority'" | PRD MISREAD (wrong id) | PRD L101: NFR preamble; NFR-1 (L105): "match impulse responses … pass listening tests" | PRD MISREAD (via FM-W1b) | Q4 |
| FM-W1a | PRD proxy | "strains NFR-2's 'usable'" | PRD MISREAD (cited id does not say it) | PRD L106 NFR-2 has no "usable"; it is the preamble, L101 | PRD MISREAD | Q4 |
| FM-W1a | PRD proxy | "NFR-1 ranks accuracy first" | PRD MISREAD (wrong id) | PRD L105 vs L101 | PRD MISREAD | Q4 |
| FM-W1a | PRD proxy | NFR-3 used to settle the accuracy/smoothness tension | PRD MISREAD (passage left out) | PRD L107: "This tension goes to the Expert" (Q4, Expert-owned per README) | PRD MISREAD | Q4 |
| FM-W1a | PRD proxy | literal per-emitter option "strains NFR-2" | PRD MISREAD | NFR-2 accepts heavy latency "when they buy accuracy"; the FM's own veto reading concedes accuracy-first accepts a longer settle | PRD MISREAD | Q4 |
| FM-W1a | remit | amending her J1 acceptance | within remit in kind | README item 1 allows amendment "when the PRD calls for it", with the AMENDS line (present); not case (b) or (c). If the only PRD ground left is the preamble's two clauses with no usability number, it is PRD MISREAD (two readings), case (a) | re-answer | Q4 |
| FM-W1a | claim | load mark as a term contradicts "not kept at (A)" | CORRECT (restate as D1-L4) | F6 (b) | — | — |
| FM-W1a | claim | Seat 6's per-scene correction | CORRECT (record) | phase-05h file 5 L29 | — | — |
| FM-W1b | PRD proxy | "Usability is held by U1–U3" | PRD MISREAD (bearing passage not shown) | PRD L101 "must stay usable in a DAW session"; under K-a capped keyless restores grow with m (T5: s = 1 cube 35–40 s at ×8); U1–U3 do not bound them | PRD MISREAD | Q5 |
| FM-W1b | claim | "SE at ×16 ≤ 0.164 dB" | WRONG | T3: layout4 listener_corner e1 ×16 = 0.171 dB | correction | — |
| FM-W1b | claim | gain shown as ×16 against ×8 | INCONSISTENT | T1: single-thread ×16 = 4.2–5.3 s > U1's 3 s; W-C1′ cannot reach ×16 | PRD MISREAD | Q5 |
| D-W2 | map | X-5 / S6 1/1 is Seat 6's rating of its own 12/16 sequence | TENSION MISREAD | seat 6 L83: X-2 at 13/16 "misses a real effect 60–80 %", 2/2; L100 X-1 → 1 only "fixed sequence over the two stimuli" | TENSION MISREAD (may change the winner to X-3) | Q1 |
| D-W2 | map | X-5 / S2 0/1, S5 0/0, S8 0/1 | TENSION MISREAD | seat 2 L110 (sizes 0.75 → 0.5) and L116 condition gives 1/1; seat 5 L119: chained form is X-3's 1/1; seat 8 L71/L77 (12/16 power; X-2 with anchor gives 1/1) | sum 8 → 12, tie with X-3; step 6 then needed | Q1 |
| D-W2 | map | sums of X-1, X-2, X-4 | arithmetic slip | 17 / 18 / 18 | correction | — |
| D-W2 | ordering | X-1 dropped at bounds | wrongly applied; winner unchanged | scope 9 concerns "several sizes" | correction | — |
| D-W2 | K21 | 0.0384 / 0.0106 / 0.0021 | CORRECT | ΣC(16,k) = 2517 / 697 / 137 out of 65536 | — | — |
| D-W2 | K23 | power 0.630 / 0.405 at p = 0.75 | CORRECT | recomputed 0.6302 / 0.4050 | — | — |
| D-W2 | D2-L1 | FWER ≤ 0.0490; independent 0.0486 | CORRECT (derived from R1) | fixed sequence strong at αᵢ plus union bound; 1 − 0.961594 × 0.989365 = 0.04863 | — | — |
| D-W2 | D2-L2 | a sequence across stimuli leaves speech decision-free | CORRECT (inference) | design logic | — | — |
| D-W2 | D2-L3 | 3 dB "easily perceived"; anchor ≥ 5/6 | CORRECT (conditions: overall loudness; checked empirically) | Toole §19.1.1; 7/64 = 0.109; 0.735 + 0.232 = 0.967 | — | — |
| D-W2 | D2-L4 | held chord ≤ 0.06 dB | CORRECT | 10·log10(1.0134) = 0.058 dB; AX47 row carries 0.06 dB | — | — |
| D-W2 | claim | step assertion formula | IMPRECISE (down-steps) | 20·log10(a − 1) is undefined for g < 0; needs abs value | correction 3 | — |
| D-W2 | claim | Zotter & Frank "§4.8" | IMPRECISE (citation) | L1515 is in §4.9.8 | correction 4 | — |
| D-W2 | inventory | K25 speech source | uninformed, declared (RQ-W2-6/7) | — | the run is UNDERINFORMED as declared | — |
| D-W2 | PRD proxy | NFR-1 check | faithful | PRD L105 "pass listening tests … thresholds come from the Expert" | — | — |

## Questions for the decider's rebuttal round

1. **Seat 5 on W-C2, and Seats 6, 2, 5, 8 on the decided X-5.** Which stated condition of acceptance in seat 5's report gives W-C2 (W-6′ as selector, W-1′ as cap) 1/1? Which condition in seat 6's report admits a design with a Bonferroni-split 13/16 speech test? If none, put both cells to the seats. Then redo D-W2's ordering with S2, S5 and S8 read from their conditions (sum 12 against X-3's 12, then reversibility).
2. **The backstop.** Is it part of D-W1? If yes:
   - put the K-a cells (S2, S4, S5, S6) into the map;
   - show how it squares with Seat 2's sequencing condition and with phase-07c-2 scope 9's "run in this phase";
   - add its debt row;
   - say whether U2 as a ratio term is consistent with Seats 2, 5 and 7, who each said the bounce does not set W.
   
   If no, delete it.
3. **U3 at ×8.** T1 pool(4) at ×8 is 664–808 ms at capped scenes, and F1 puts local per-scene pool cost inside CI Linux's range. What m does U3 project to on the worst OS? Does a non-empty m\*…m_max window remain? Also: is W-6′ required at the pin (Seat 2's W-5′), and what supports monotonicity for m = 9–11?
4. **FM-W1a.** Restate it with correct PRD ids (preamble L101 for "usable" and for the accuracy ranking). Address NFR-3's "This tension goes to the Expert". Say which PRD passage, not a seat's correction, calls for reading "per emitter" as per scene. If the only ground is the preamble's two clauses with no usability threshold, is this not PRD MISREAD (two readings), and so case (a)?
5. **FM-W1b.** Under K-a the s = 1 cube keyless restore projects to 35–40 s at ×8 (T5) and grows with m. Where is that usability cost shown against PRD L101 for W-C2 and W-C1′? Restate the accuracy gain at the m W-C1′ can actually reach under U1–U3, not at ×16.

Files examined: `/home/user/makroof/docs/review/phase-07c-2/5-decider-decision-r1.md`, `/home/user/makroof/docs/review/phase-07c-2/1-decider-convening.md`, `/home/user/makroof/docs/review/phase-07c-2/2-fact-sheet-part1.md`, `/home/user/makroof/docs/review/phase-07c-2/2-fact-sheet-part2-wsweep.md`, `/home/user/makroof/docs/review/phase-07c-2/3-researcher-RQ-W1-W2.md`, `/home/user/makroof/docs/review/phase-07c-2/4-seat1.md` … `4-seat9.md`, `/home/user/makroof/docs/phases/phase-07c-2.md`, `/home/user/makroof/docs/PRD.md` (L49, L89–107), `/home/user/makroof/docs/board/README.md` (L76–147), `/home/user/makroof/.claude/agents/decider.md` (§1a, §5), `/home/user/makroof/docs/BUILD_PLAN.md` (AX41, AX47, AX48 rows), `/home/user/makroof/docs/review/phase-05h/5-seat6-D-H1.md` (L29), `/home/user/makroof/src/plugin/core/ScenePipeline.cpp` (L108–123, L252–316, L339–557, L847–853), `/home/user/makroof/src/plugin/core/IrBuilderThread.h`, and the corpus files `/home/user/makroof/docs/corpus/vorlaender-auralization.md` (Table 6.1 L2056–2066; §15.3 and Table 15.1 L3952–3966), `/home/user/makroof/docs/corpus/toole-sound-reproduction.md` (§19.1.1 L3473) and `/home/user/makroof/docs/corpus/zotter-frank-ambisonics.md` (§4.9.8 L1515).
