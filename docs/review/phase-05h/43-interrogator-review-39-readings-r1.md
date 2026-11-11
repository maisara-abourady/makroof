# 43 — Interrogator: decider file 42 (review file 39 readings), round 1 — SURVIVES WITH CORRECTIONS (QA's nightly-move clause UNDERCONVENED: struck or Seat 5)

phase-05h (session 2). Verbatim interrogator output (the orchestrator saved it). The decider's round 2 with the corrections applied is file 44.

**Interrogator — decision mode on `/home/user/makroof/docs/review/phase-05h/42-decider-review-39-readings.md` (P05H-QA, QB, QC + addendum).** Corpus revision c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (14 files). No acoustic fact is load-bearing except one derived point (QA, s-independence), cited below.

## Outcomes

| answer | outcome |
|---|---|
| **P05H-QA** | **SURVIVES WITH CORRECTIONS** for the check form (2^23, τ alone, N rule 3·SE ≤ τ per band, labelled smoke test, AMENDS line, test form — the working tree `tools/acoustics/tests/test_tail.py` L203–250 already implements it faithfully). **The pre-authorised nightly-move clause does not survive** (plan text's last sentence; addendum item 2's two-step form): UNDERCONVENED (Seat 5) and INCONSISTENT with the row it amends. Fix below. |
| **P05H-QB** | **SURVIVES WITH CORRECTIONS** (two wording gaps in the plan text). |
| **P05H-QC** | **SURVIVES WITH CORRECTIONS** (one imprecise number; one condition to record; a label). |

## Ledger

| decision | check | item | verdict | evidence | question |
|---|---|---|---|---|---|
| QA | convening | nightly-move clause (python job > 10 min → s 0.5, then the whole validation-N form, to `nightly.yml`) | **UNDERCONVENED (Seat 5)** | README L59: Seat 5 convened for "CI gates … the host matrix". The decider itself names Seat 5 worst-off and writes it a debt row without hearing it. AX43's identical clause (L144, "moves to the nightly") was decided with Seat 5 convened (file 19). | Q1 |
| QA | claim (hidden premise) | "Seat 5's ≤ 10 min agreement-suite budget (AX43) is the budget for the python job" | NOT CHECKABLE, the decider's own, not a seat's words | AX43 L144 scopes the budget to the agreement suite in the Release build job; no seat report states a python-job budget. | Q1 |
| QA | debt / plan text | the move "costs one line" and keeps "in PR CI on three OSes" | **INCONSISTENT** | `nightly.yml` L4, L29–30 is Linux-only and L74/L77 run only `tools/validation` and `test_radiosity.py -m slow`; the `nightly` marker is registered in `tools/validation/tests/conftest.py` L16–17, not in `tools/acoustics/tests/conftest.py` L17–27. A move needs a workflow edit and would drop two OSes from her accepted "in PR CI on three OSes" (AX37 L138; phase-05h §5 L325) — the AMENDS line does not name that phrase. | Q1 |
| QA | claim | 2^20 figures: SE 0.217/0.231, dev +0.366/+0.285, z 1.69/1.23, bound 0.90/0.94 = 3.6 τ | CORRECT | file 39 blocker 1; 0.366/0.217 = 1.69; 0.25+3·0.217 = 0.90; 0.90/0.25 = 3.6. | — |
| QA | claim | 2^23: SE ≈ 0.08 at 4–8 kHz; measured 0.073–0.076; 3·SE 0.220–0.229 ≤ 0.25; every band |dev| ≤ 0.020; capHit false; s 0.4 = s 0.5 | CORRECT | file 40 L113–154; 0.217/√8 = 0.077. | — |
| QA | claim | "213 s per s value ≈ 7 min per OS for both s" | CORRECT | 2 × 213 s = 7.1 min (file 40 L113). | — |
| QA | claim | "AX43's N rule" | IMPRECISE | AX43's rule is z_FW·SE ≤ τ − ℓ_ref (L144); the form used is constant 3 (AX46/D-H2 (d)) with no ℓ_ref term. Restate: "the plan's N-rule form with AX46's constant 3; the integral's 10 ms-bin discretisation residual is bounded by the measured |dev| ≤ 0.020 dB at 2^23 (≪ τ)". | — |
| QA | claim | "the ratio is s-independent by construction" | CORRECT (derived) | Kuttruff Eq. 4.24: Lambert re-radiation from dS is into the half-space above it; in `open_field` every other face has α = 1 (test L223–224), so no second bounce exists; estimator and integral are both linear in s(1−α), the ratio cancels s; identical deviations at s 0.4/0.5 (file 40) confirm. Moot if the move clause goes. | — |
| QA | claim | "9 % margin" | IMPRECISE | (0.25−0.229)/0.229 = 9.2 %; /0.25 = 8.4 %. | — |
| QA | PRD proxy | NFR-1, NFR-8, AX37 (5.4), AX42; four options each shown | no PRD MISREAD | PRD L105 "Pass thresholds come from the Expert": τ is her accepted number (ledger L2076–2077), the form only makes it operative; L112 NFR-8 is a loose fit for "no excluded band" (a test exclusion is not a code path) but points the same way. AMENDS id and words correct (ledger L2070, L2076). | — |
| QB | claims | AX43 lists the 30 pairs as a group; AX46's list omits them; `className(5) == "bras"`; mean z′ +0.59–0.60 over 30; no room |mean z′| > 3 | CORRECT | BUILD_PLAN L144, L147; `test_diffuse_agreement.cpp` L119–120; file 40 L87–89. | — |
| QB | PRD proxy | NFR-1 "measured in real spaces" → own line; three options shown | no PRD MISREAD; AMENDS within remit (an amendment the PRD passage calls for, README L87–89) | PRD L105. | — |
| QB | plan text | "runs now … on: reference positions, absorbing face, small rooms, and one-end near-wall" (AX46 L147; phase-05h §5 L299–300) | INCONSISTENT with "of 6 classes" unless amended | The enumeration of classes evaluated now must add "BRAS pairs (500 Hz–2 kHz)"; and "D-H2 (d)'s quoted text" lives in review file 19, which the plan-editor does not edit — say "as quoted in AX46". | — |
| QB | code | `{0,1,2,3,5,4}`, per-band "not evaluated (reference pending)", "of 6 classes" | faithful | L378–436 of the working tree. | — |
| QC | claim | SE_class = √(mean SE_i²/n) | CORRECT | Var(mean) = ΣSE_i²/n² = mean SE_i²/n; identical to D-H3 (a)'s SE_pool (file 27 L61). The only reading under which AX46's "N is pre-registered so that 3·SE ≤ …" can be satisfied by N (file 40: estimator part 0.07 %, spread 0.15 %). | — |
| QC | claim | |mean r_i| ≤ mean ℓ_ref,i | CORRECT | Triangle inequality under D-H3 (a)'s reading of ℓ_ref as a bound on a residual of unknown sign (file 27 L61, L76). Inherits the AX36 caveat already recorded in AX43 (ladder not asymptotic at dead_booth); nothing new. | — |
| QC | claim | seRel = 10^(SE_dB/10) − 1 | IMPRECISE, harmless | First-order conversion; second-order error ≤ 1.2 % of SE at 0.1 dB; consistent with `classDev`'s conversion (L269, L272). | — |
| QC | claim | heterogeneity label |mean| + 3·SE_emp > 1 % | NOT CHECKABLE (statistics, not corpus); sound as a watch | It flags where the scatter could hide a class mean beyond 1 %; at n = 2 SE_emp has 1 d.o.f. — a watch, not a CHECK, so acceptable; say so. | — |
| QC | claim | 3·0.078 % + 0.24 % = 0.47 %; means −0.14…−0.22 %; 4.6× | CORRECT | file 40 L93–102; 1/0.218 = 4.6. | — |
| QC | claim | alternative "empirical + mean ℓ_ref evaluable (3·0.15 ≤ 0.81 %)" | IMPRECISE | 0.81 % is band 2's budget; band 7's is 0.76 % (3·0.161 = 0.48 ≤ 0.76): conclusion unchanged. | — |
| QC | debt | near-wall evaluated in all 8 bands | missing condition | D-H2 (d) (file 19 L235): "once the c4 cross-check passes"; file 39 minor 2: the recorded table (file 6 L647–665) is empty, the reviewer's recomputation passes (≤ 3.4e-6). Add a row: evaluation stands when that pass is recorded. | Q2 |
| QC | PRD proxy | NFR-1; three options shown; AMENDS = a reading made explicit | no PRD MISREAD | PRD L105. | — |
| QA/QC | map | summary "worst-off: Seat 5 (python-job time)", "Seat 1 (later 1)" | TENSION MISREAD (minor) | No seat rated a cell; a FOR MAISARA outside a board round has no map. Relabel as "debt owed to Seat n's mandate (decider's own)". | — |

## Exact fixes

1. **QA plan text, last sentence** → "If the two 2^23 renders add more than 10 min to the python job on any OS, the clause returns to the board (Seat 5 convened; the nightly is Linux-only and does not run `test_tail.py`), never a loosened τ." Drop addendum item 2's two-step marker form (it is not applicable: unregistered marker, workflow not running the file). Alternatively convene Seat 5 now on that one clause. Keep item 3 (3·SE > τ on an OS → N 2^24).
2. **QA AMENDS line:** if any pre-authorised move is kept, name the amended phrase "in PR CI on three OSes".
3. **QA wording:** "AX43's N rule" → "the plan's N-rule form with AX46's constant 3, no ℓ_ref term (the integral's discretisation residual is bounded by |dev| ≤ 0.020 dB at 2^23)"; "9 %" → "8–9 %".
4. **QB plan text:** add "BRAS pairs (500 Hz–2 kHz, outer bands as 05i certifies)" to the enumeration of classes evaluated now in AX46 and phase-05h §5 criterion 3; replace "D-H2 (d)'s quoted text" with "D-H2 (d)'s text as quoted in AX46".
5. **QC:** "0.81 %" → "0.76–0.84 %"; add the c4-cross-check record (file 39 minor 2) as the condition for the near-wall line, in the debt table; label the watch "n ≥ 2, 1 d.o.f. at n = 2".
6. **Summary table:** strike the invented cells (Seat 5, Seat 1) or mark them "decider's own debt, no seat rated".

## Questions for the rebuttal round

1. (QA) Which seat report or recorded decision states a wall-time budget for the **python** job and pre-authorises moving a check out of "PR CI on three OSes" to a Linux-only workflow? If none, does the > 10 min case become a board return?
2. (QC) Where is the c4 cross-check pass recorded (file 6 L647–665 is empty per file 39 minor 2)? D-H2 (d) conditions the near-wall evaluation on it.
3. (QA) Is the floor integral's 10 ms-bin discretisation residual bounded anywhere other than by the 2^23 measurement? If not, say so in the plan text (it is the ℓ_ref the N rule omits).

Files read: 42, 40, 39, 19 (L227–236), 27 (L57–86); BUILD_PLAN L106, L138, L143–147; PRD L1–60, L105–112; README L45–63, L76–145; decider.md L222–257; phase-05h L296–302, L323–326; `test_tail.py` L150–250; `test_diffuse_agreement.cpp` L100–437; `ci.yml` L108–172; `nightly.yml` L1–80; conftests; ledger L2066–2081; corpus Kuttruff L2335–2345.
