
# 21: Decider on L4-COV, round 2 (rebuttal of interrogator file 15)

This file is read-only. The orchestrator saves it as `/home/user/makroof/docs/review/phase-07c-2b/21-decider-l4-coverage-r2.md`.

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. I re-read Kuttruff Table 6.1 (L2827–2834) for Seat 9's air figure.

**Files read:**
- Review files 13, 15, 16-seat5, 17 (§6 texts), 18, 19-seat3, 19-seat7, 19-seat9, 12-seat1 and 12-seat8.
- PRD L10–112.
- `phase-08-3.md`, searched for L4/AX49/held chord.
- From the code: `.github/workflows/ci.yml` L406–418 and the header of `tests/unit/test_ax49_l4.cpp` (L1–9, L156–160).

**Outcome in short:**
- **L4-COV: E stands, with corrections.** It ties C at the sum (6 each); I name E because its check is an assert rather than a print. It beats B-second by one point, 6 against 7, and that margin rests on one Seat 1 cell I read from its conditions.
- **R5(a) and R5(e): Seat 5's option (c) is ratified,** with binding conditions from Seats 5 and 7.
- **NEEDS MAISARA:** none.

## PRD digest (corrected per interrogator file 15: L101 restored, L13 added)
- **For whom:** producers and DJs (L17).
- **Outcome:** NFR-1 (L105): "match impulse responses measured in real spaces and pass listening tests. Pass thresholds come from the Expert."
- **Who designs the tests:** L13, "Acoustic and psychoacoustic decisions belong to the dedicated Spatial Audio Expert project". The board fills that role here.
- **Ranking:** "Accuracy is the top priority; CPU load and latency may be high…" (L101). L49 says "Accuracy first; heavy CPU/latency acceptable". Both rank accuracy against CPU and latency only.
- **Hard bounds:**
  - NFR-8 (L112).
  - AX5, and AX49's validation-only provisional.
  - Her AX21 decision; spaces are empty (L54).
- **Not bounded:** hours. L55 says "no fixed deadline", but it does not rank her hours against anything.
- **Verification culture:** every behaviour has an automated check, and a red is a stop. Tolerances follow from the requirement and are never loosened to pass (decider.md §5; file 15 notes this is not CLAUDE.md wording).

## 1. Answers to file 15's questions

**Q1 (PRD, E against B-second): answered as FOR MAISARA L4-COV-P (§4).**
- No PRD passage ranks one over the other.
- L105 and L13 leave test design and thresholds to the Expert, and L101 ranks accuracy against CPU and latency only. Neither option changes a render, CPU or latency.
- I withdraw file 13's phrase "NFR-1 plus brighter evidence". It overstated what the bright arm adds:
  - Its direction is contested (K5). Seat 1 says it gives +9–12 dB of exposure at 1–2 kHz. Seat 3 says it is about 1 dB *less* sensitive. Seat 8 says it "may also make the test more lenient".
  - Seat 9 says it does not reach the band the null excludes: "the bright arm still tests 4 kHz at a 40 dB depth in this cube".
- So no PRD goal points to B-second, and the board's ordering governs.

**Q2 (convening): conceded.** Seat 9 (19-seat9) and Seat 7 (19-seat7) were convened, and their cells are in the map below.

**Q3 (what (b) measures): accepted.**
- (b) compares absolute band energies within the cut window. On builder file 18 §1:
  - the strongest band is 125 Hz;
  - the weakest is 2 kHz at −17.71 dB;
  - the margin is 2.29 dB (the interrogator's 17.7 / 2.3).
- "At the cut 1 kHz is the strongest band" is withdrawn.
- Without that sentence, my answer to K5 no longer holds as I wrote it. (b) bounds 1–2 kHz only to within 20 dB of 125 Hz, so it does not settle K5.
- The objection is now met by the ordering alone:
  - B as the primary is out on Seat 8's own 2/2.
  - B-second, the option that would answer K5 if Seat 1 is right, loses at step 5 by one point (strongest objection, §3).

**Q4 (step 6): conceded; it is a tie.**
- Under C the cut-window levels are printed in the sealed manifest, so C could gain the assert before the seal as cheaply as E could drop it.
- E is named at step 7 on a stated ground (below).
- Seat 3 was asked (19-seat3):
  - E is 0/1 in its own words: "My E cell is not one point above C."
  - The time base is confirmed correct.
  - The partition grid "does not enter (b) at all". This answers Seat 1's hand-off.

**Q5 (R5(a), R5(e)): both were held until Seat 5 answered (16-seat5). They are ruled in §5.**

**File-15 corrections:**
- **Loosening reasons (i) and (ii)** are restated in the texts below.
- **R5(c) attribution:** now reads "decider, from the code". The test header already says so (L8, from the code).
- **C9:** the header of `test_ax49_l4.cpp` is fixed in the tree.
  - L4–9 now assert 1e−9 and cite decider files 9 and 13.
  - The phantom CLAUDE.md quotation is gone.
  - L156–157 record the measured values: P4 2.5e−13, P5 3.6e−14.

## 2. Convening (L4-COV, round 2)

| seat | status | reason (README row item) |
|---|---|---|
| 1 | convened (12-seat1); cells carried | "acceptance tests for other seats"; "audibility". Two cells are read from its conditions, both marked: (i) E with Seat 9's null text, which keeps both elements of Seat 1's condition ("cut exposed at 63 Hz–2 kHz" and the 40 dB depth sentence) and adds the reference point; (ii) B-second, which appeared after its round (Seat 8 proposed it in the same round). |
| 2 | not required | S′ is unchanged and all of Seat 2's asserts pass (file 18). The interrogator found this faithful. |
| 3 | convened (19-seat3) | "decay matching"; "listening validation of a rendering design" |
| 4 | not required | The chain stays omni diotic (faithful). |
| 5 | convened on R5 (16-seat5); **not required for the stimulus options** | Its row is the audio thread, hosts, formats, sanitizers and "CI gates". No option touches the audio thread, a host, a format or a sanitizer, and none adds or moves a CI gate: (a) and (b) already run inside the existing python-job kit test (file 18, green). B-second would lengthen that existing test by about one kit build, roughly 30 s (file 18). It would not create or place a gate. Any cell Seat 5 gave B-second would be ≥ 0, so B-second's sum could not fall below 7. |
| 6 | not required | No control is touched (faithful). |
| 7 | convened (19-seat7) | "what one founder can sustain; schedule and complexity cost of an option" |
| 8 | convened (12-seat8); cells carried | "where was it judged": the material |
| 9 | convened (19-seat9) | "early structure vs decay"; the null wording states S′'s per-band decay |

## 3. L4-COV decision round

### Knowledge inventory

| K | what | source | status |
|---|---|---|---|
| K1′ | (a) steady state re 125 Hz: 63 −9.76, 250 −9.25, 500 −11.58, 1k −13.31, 2k **−15.83** dB | file 18 §1 (builder measurement; two builds with identical hashes) | known |
| K3′ | (b) cut window [8.0267, 8.1267) s re 125 Hz (absolute): 63 −14.73, 125 0.00, 250 −5.65, 500 −6.57, 1k −5.91, 2k **−17.71** dB | file 18 §1; agrees with file 15's K1 + K3 to rounding | known |
| K2 | depth at L_f: 18.72 dB (63 Hz–1k), 23.19 dB (2k), 40.14 dB (4k) | Kuttruff §3.8 definition of T; working in file 13, rechecked in file 15 | known |
| K8 | at 4 kHz, air absorption is 63 % of the absorption area | Kuttruff Table 6.1: m = 6.84·10⁻³ m⁻¹ at 4 kHz, 50 % RH (re-read L2832). 4mV = 4 × 6.84·10⁻³ × 10⁶ = 27,360 m². Surface term 15,805 m² (file 17 Q2). 27,360 / 43,165 = 0.634. Eyring 0.161·10⁶ / 43,165 = 3.73 s, against the printed 3.731 s (Seat 9's working, rechecked) | known |
| K9 | the held-chord L4 does not recur at 08-3 | plan text: `phase-08-3.md` has no AX49 held-chord item. L122's "(phase-08 L4)" is the large-hall listening item. | known (from the plan) |
| K10 | fragility of (b): σ ≈ 3.1 dB, so the margin is about 0.7σ | 19-seat3 §5 [Inferred], from Kuttruff §3.7 Eq. 3.47 | under-informed. Not load-bearing: the stimulus is sealed and bit-reproducible, and a red fails safe. The ensemble print below measures it. |
| K5 | B's sensitivity, Seat 1 against Seat 3 | 12-seat1, 12-seat3, both [Inferred] | conflicting. Not load-bearing: B is excluded on Seat 8's 2, and B-second on its sum. |

No load-bearing gap remains.

### Tension map (now / later)

| option | S1 | S3 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|
| A | 2/1 | 2/1 | — | 1/1 | — | 2 | out |
| B (primary) | 0/0 | 1/1 | — | **2/2** | — | 2 | out |
| C | 1/1 "a loosened criterion stays at 1" | 0/1 "my reasons in 12-seat3 still apply" | 0/1 "same debt as E" | 0/1 "material stays representative" / beta report | 0/1 with Seat 9's wording ("1/2 without") | 1 | 6 |
| **E** | 1/1 (null condition met by Seat 9's text, **read from conditions**) | 0/1 "a margin smaller than one realisation's spread" | 0/1 "no extra sitting" / "a re-sitting … after scores exist" | 0/1 (**read**: "C: no condition from me") | 0/1 with its wording | 1 | 6 |
| D (A + C) | 1/1 | 0/1 | 0/1 (**read**: the same hours as C) | 1/1 (**read**, file 13) | 0/1 (**read**: its wording condition applies to any scoped null) | 1 | 7 |
| B-second | 1/1 (**read**: the pad arm keeps E's loosened criterion; "C and E, from 1 to 0: none available") | 0/1 "if the two arms disagree, someone has to reconcile them" | 1/0 ("0–1": its later 1 "applies only if L4 is re-run at 08-3"; K9 meets its condition, so 0) | 1/1 (Seat 8's condition: a "second, labelled 'bright' variant") | 0/1 "closes the chord gap, not the scene gap" | 1 | 7 |

### Working
1. **Bounds:** no option breaks one. All are kit-only, with no `src/sim` (NFR-8), and AX5 and AX49 are untouched.
2. **Veto:** no 3 anywhere.
3. **Worst-off seat:**
   - A and B hold a 2 and are out.
   - C, E, D and B-second hold max 1.
   - 0 is unreachable: Seat 1 says "C and E, from 1 to 0: none available".
4. **Compose:** Seat 9's wording is its condition, and it is applied to C, E, D and B-second alike. Without it, Seat 9 rates C and E 1/2. Nothing lowers the maximum below 1.
5. **Sum:** C 6 = E 6 < D 7 = B-second 7.
6. **Reversibility, C against E:** a tie (Q4).
7. **Decide: E.**
   - **Ground:** with C and E equal on every rule, I take the option whose exposure check is an automated assert rather than a print. This follows the verification culture ("every behaviour has an automated check"). The assert already exists and is green (file 18).
   - **Supporting, not decisive:** Seats 3 and 7 rank E "prefer". Seat 1 proposed E. Seat 8's "prefer C" carries no tension difference: its E cell equals its C cell.

### DECISION L4-COV (round 2): E, with Seat 9's null wording and Seat 3's two prints; no automatic reference fallback

- **Seat 3's prints are adopted.** Both are print-only:
  - (b) against the median of 63 Hz–1 kHz;
  - a 16-tailSeed ensemble of (b) on the exact arm.
- **Seat 3's recorded fallback (median reference on a strongest-band red) is declined.**
  - A pre-agreed switch to a wider-margin reference after a red is the loosening Seat 3 itself calls "a second post-hoc loosening".
  - A red on a rebuild is a stop, and it returns to the board (Seats 1 and 3) with both prints in hand.
  - Seat 3 left this to me ("the decider's call"), and its cells do not depend on it.

**Load-bearing claims:**
- **21-L1:** (a) margin 4.17 dB and (b) margin 2.29 dB, with 125 Hz the strongest band in the cut window (K1′, K3′; builder measurements).
- **21-L2:** K2, the depth table (corpus definition plus working). It is a judgement input, not a pre-set threshold (file 15 reason (ii)).
- **21-L3:** K8, air is 63 % of A at 4 kHz (corpus Table 6.1 plus working). It carries the null's cause clause.
- **21-L4:** K9 (plan text) resolves Seat 7's B-second later cell to 0 under Seat 7's own condition.
- **21-L5:** the seats' cells as quoted. Four are read from conditions (marked).
- **21-L6 (product):** L13 and L105 leave the test design to the Expert. L101 and L49 rank accuracy only against CPU and latency.

**Future-debt register (E):**

| seat | commits to | undo cost | evidence | repaid when |
|---|---|---|---|---|
| 1 | a null scoped to 63 Hz–2 kHz at the cut | a bright-arm re-sitting (about 0.75 h) plus a rebuild and re-seal | the 07d AX49 review | the null is sealed with the scope sentence and 07d does not contest it |
| 3 | an asserted (b) whose 2.29 dB margin rests on one 125 Hz draw | a board round on any pre-seal rebuild red (no automatic fallback) | any rebuild; the 16-seed ensemble print | the seal, with hashes registered; after that only a rebuild re-tests it |
| 7 | a contest after scores costs a re-sitting at a later phase | about 0.75 h plus a rebuild and re-seal | 07d; 13-5 beta | 07d and the beta raise no bright-pad contest |
| 8 | bright-pad material untested | one variant sitting | Phase 13 beta reports | no bright-pad cut report, or the bright arm is run |
| 9 | a null that does not carry over to scenes whose 4 kHz T60 is close to the mid T60 (small or hard rooms) | a sitting on such a scene | the 07d AX49 review, or wherever the provisional reaches small scenes (Seat 2's hand-off) | the null carries the cause clause (it stays at 1, not 2) and no small-scene claim cites it |

**Strongest objection: B-second.**
- Seat 9 ranks B-second "prefer" by a small margin. Seat 7 calls it "the better buy if the 07d contest looks likely". If Seat 1's K5 is right, it would answer the dull-chord premortem.
- **Why E holds:** B-second loses at step 5 (7 against 6).
- **When it would not hold:**
  - B-second's Seat 1 cell is read from conditions. If Seat 1 rates B-second's later cell 0, the sums tie at 6.
  - Step 6 would then favour B-second. Dropping its arm before the sitting costs nothing, while E's undo costs a later sitting (Seat 7's A7 reason).
  - That is the first reversal condition.

**Confidence:** medium. Four cells are read from conditions, and the C/E pick at step 7 is a tie-break on stated ground.

**Reversal conditions:**
- Seat 1 rates B-second below 1/1 (re-run steps 5–6);
- (a) or (b) reds on a rebuild (a stop; board round with the median print and the ensemble);
- the ensemble shows 2.29 dB is lucky (median of seeds below 0 dB margin), in which case Seats 1 and 3 re-rate E before the seal;
- 07d contests the scope (the bright arm runs);
- Seat 8 rates B ≤ 1 as the primary.

**Acceptance check (L105, L13, L101/L49, L17, L55, NFR-8, AX5, AX49):**
- **E:** serves NFR-1 with an asserted exposure check on producer material (L17). No bound is strained.
- **C:** the same as E, with a print instead of the assert. No PRD id ranks it above E.
- **D:** the same as C, with slightly brighter material and no gain at the cut. No PRD id ranks it above E.
- **B-second:** NFR-1 with an added arm whose gain is contested (K5) and which does not reach 4 kHz (Seat 9). L55 does not bound its 0.75 h, and L13/L105 leave its value to the Expert. No PRD id ranks it above E (§4).
- **B (primary):** strains L17 (Seat 8). Out.
- **A:** red. Out.

No PRD goal points to another surviving option. The decision amends nothing.

## 4. FOR MAISARA L4-COV-P

**Question:** should 07c-2b's held-chord L4 test use the producer pad alone, with coverage asserted at 63 Hz–2 kHz (E), or add a second, brighter-chord arm at about 0.75 h more listening (B-second)?

**Answer:** "The pad alone (E). Coverage is asserted at 63 Hz–2 kHz in the steady state and at the cut, and the null claims nothing at 4 kHz and above. The bright arm is the recorded remedy if the 07d AX49 review or a beta report contests that scope."

**Rests on:**
- L105: "pass listening tests. Pass thresholds come from the Expert"
- L13: "Acoustic and psychoacoustic decisions belong to the dedicated Spatial Audio Expert project"
- L101: "Accuracy is the top priority; CPU load and latency may be high"
- L17: "producers and DJs"
- L55: "no fixed deadline"

**Reasoning:**
- The PRD requires that the rendering pass listening tests, and it hands their design to the Expert (L105, L13). How many arms a test has is therefore the board's call, not a PRD ranking.
- L101 ranks accuracy against CPU and latency. Neither option changes a render, CPU or latency.
- The bright arm's added evidence is contested in direction (Seats 1, 3 and 8, all [Inferred]). It also leaves the excluded 4 kHz band at the same 40 dB depth (Seat 9).
- L17 is kept by both options (the pad arm runs in each). L55 removes a deadline but does not make her hours free.
- The PRD is silent between the two, so the board's ordering governs: E has sum 6, B-second 7.

**Options against the PRD ids:**
- **E:** serves L105 (an asserted exposure check, scoped null) and L17 (producer pad); L101 neutral; uses no extra hours (L55).
- **B-second:** serves L105 with an extra arm of contested value and L17 (the pad is kept); L101 neutral; about 0.75 h more (L55 does not bound it, and does not ask for it either).

**What would make her veto it:** reading L101's "top priority" as covering validation evidence, so that with L55's absent deadline she would buy the extra arm now rather than risk a later re-sitting (Seat 7's A7).

Amends nothing.

## 5. R5(a) and R5(e): CI placement of `[ax49-l4]` (Seat 5, 16-seat5; Seat 7, 19-seat7)

**Convening:**
- Seats 5 ("CI gates and sanitizers") and 7 ("schedule … cost") were convened.
- Seat 3 is not required: under (c) the case runs in Debug *and* Release, so its hand-off ("whether Debug-only coverage is enough") does not arise. Any MSVC Release red goes to Seat 3 as a red.
- The other seats are not required: no audibility, response, chain, control, material or room matter is involved.

| option | S5 | S7 | max | sum |
|---|---|---|---|---|
| (a) default set, ctest only | 1/2 "drifts toward the 600 s timeout"; "ships-as-Release path … untested" | — | 2 | out |
| (b) Release-only, hidden | 2/2 "hidden gates are forgotten" | — | 2 | out |
| **(c) non-hidden in ctest (Debug on 3 OS, ASan) plus a Release gate step on 3 OS** | 1/1 | 1/0 (with its conditions) | 1 | 3 |

**DECISION R5 (round 2): (c) ratified.** It is already in the tree: `ci.yml` L406–418, "AX49 L4 gate (release)" (from the code). Binding conditions:
- **Tag:** exactly `"[ax49-l4]"`, with no `[.]` and no `[benchmark]`. The hidden probe may stay `[.]`.
- **Budgets** for the whole case, all sections, per run: Release ≤ 60 s per OS, Debug ≤ 300 s per OS, ASan ≤ 300 s.
  - Release is measured at 2.5 s on Linux.
  - Before the seal, the builder records the Debug and ASan `--durations` and the peak RSS in the PR.
  - If either exceeds 300 s, first remove the SECTION re-entry so S′ is built once.
  - If it is still over, that is a stop and returns to Seats 5 and 3. Seat 5's `[.][ax49-l4-slow]` twin is the pre-rated candidate at 1/2. The case is never simply hidden.
- **Seal evidence:** a CI run whose fingerprint includes the sealed `tests/unit/test_ax49_l4.cpp`, green on Linux, macOS and Windows, showing the `ax49-l4:` line. A skipped run linking to such a run counts.
  - **The session starts that run**, not Maisara.
  - Her L4 sitting is scheduled only after it is green. A red never costs her a sitting.
- `tools/ci/test_ci_workflow.py` stays green.

**Load-bearing claims:**
- **R5-L1:** the step layout and the 600 s timeout (16-seat5 §1, from the code).
- **R5-L2:** the seats' cells as quoted.

**Debt register (later ≥ 1):**

| seat | commits to | undo cost | evidence | repaid when |
|---|---|---|---|---|
| 5 | per-PR Debug and ASan time | a one-line tag or step change | the first `--durations` reading | all budgets are met at half the limit |

**Confidence:** high. Every cell is in the seats' own words, and no acoustic claim is involved.

**Acceptance check:** this serves NFR-1 and AX5 by gating the shipped Release binary. NFR-4's three platforms are covered. No PRD id points elsewhere. The decision amends nothing.

## 6. Texts for the plan-editor (these replace the corresponding texts in file 17 §6)

**Run sheet §0, header:** "decider files 2, 6, 9, 13, 17" becomes "decider files 2, 6, 9, 13, 17, 21; interrogator files 3, 7, 10, 15 and its check of file 21".

**Item 14:** "…its band coverage amended by decider files 13 and 21 after the first build's red (4 kHz −22.94 dB), before any scored trial (§7)."

**Run sheet §7, band-coverage paragraph (replaces "Band coverage (decider file 13, verbatim)…"):**
> - **Band coverage (decider files 13 and 21, verbatim):** "Band coverage (Seat 1; amended by decider files 13 and 21 after the first build's red, before any scored trial). (a) In the exact render's steady state (the last 1 s of the hold), every band from 63 Hz to 2 kHz is within 20 dB of the strongest band. (b) In the 100 ms where the cut begins (the fade [L_f, L_p) in written-file time: from the chord's release sample plus round((L_f − alignmentShiftS)·fs); kit interpretation 2), the exact render's energy in every band from 63 Hz to 2 kHz is within 20 dB of the strongest band in that same window (absolute band energies, not levels relative to each band's hold). Both are asserted. A red on either, at any build, is a stop and returns to the board; the reference band is not changed after a red. Printed beside them: 4 kHz and 8 kHz with their depth at L_f; the original clause (63 Hz–4 kHz) with its result (first build: 4 kHz −22.94 dB re 125 Hz, red); (b) against the median of 63 Hz–1 kHz; and (b) for the exact arm over 16 further tailSeeds, run once by the builder before the seal and committed with the pre-registration commit (Seat 3; print only, not a CI step). The scope is a judgement on S′'s depth at L_f (63 Hz–1 kHz 18.72 dB, 2 kHz 23.19 dB, 4 kHz 40.14 dB; chord-independent), made after the red; no depth threshold was fixed in advance, and the null claims nothing at 4 kHz and above. First passing build (builder file 18): (a) weakest 2 kHz −15.83 dB, margin 4.17 dB; (b) strongest 125 Hz, weakest 2 kHz −17.71 dB, margin 2.29 dB." Negative control N-L4: the chord limited to partials ≤ 500 Hz fails (a) and (b).

**Run sheet §7, "Checks before the seal":** replace "the Catch2 `[ax49-l4]` case … its CI placement per Seat 5's answer (file 13 brief)" with:
> "the Catch2 `[ax49-l4]` case (P4/P5 at 1e−9, N-L1/N-L2 inside; tag exactly `[ax49-l4]`), run by ctest in Debug (Linux, macOS, Windows) and ASan (Linux) and by the 'AX49 L4 gate (release)' step on all three OS (Seat 5, option (c); decider file 21 §5); per run of the case Release ≤ 60 s, Debug ≤ 300 s, ASan ≤ 300 s, with Debug and ASan `--durations` and peak RSS recorded before the seal; seal evidence is a CI run, started by the session, whose fingerprint includes the sealed `tests/unit/test_ax49_l4.cpp`, green on all three OS with the `ax49-l4:` line; the L4 sitting is scheduled only after that run is green."

**Run sheet §7, "Wording" (the null; Seat 9, 19-seat9, verbatim):**
> "not detected in 16 trials by one listener (power 0.63); ax49_l4_cube, T60 8.0 s at 63 Hz–1 kHz and 6.5 s at 2 kHz, held chord, omni diotic; cut exposed at 63 Hz–2 kHz; no claim at 4 kHz and above, where this scene's tail (T60 3.7 s, mostly air absorption in 10⁶ m³) has by L_f decayed 40 dB from its own onset, against 19 dB at 63 Hz–1 kHz."
>
> The sentence that follows is unchanged: "A detection fires AX49's Reversal: …"

**BUILD_PLAN AX49, L4 sentence fragment.** Replace file 17's "band coverage asserted … (decider file 13: …)" with:
> "band coverage asserted at 63 Hz–2 kHz in the steady state and in the cut window, 4 and 8 kHz and the original 63 Hz–4 kHz clause printed, the null claiming nothing at 4 kHz and above (decider files 13, 21: a criterion change after the first build's red, before any scored trial); `[ax49-l4]` (P4/P5 at 1e−9) green in Debug and ASan ctest and in a Release gate step on Linux, macOS and Windows"

The fragment then continues with "; stimuli built, checked and sealed before the first scored AX47 trial)".

**BUILD_PLAN §6, row 1:** the citation list becomes "decider files 2, 6, 9, 13, 17, 21; interrogator files 3, 7, 10, 15 and its check of file 21".

**BUILD_PLAN §6, row 2 (replaces file 17's row 2):**
> "Threshold changed (AX49 L4 band coverage, decider files 13 and 21): Seat 1's clause '63 Hz–4 kHz within 20 dB' failed on the first full build (4 kHz −22.94 dB re 125 Hz, builder file 11), before any scored trial; replaced by (a) 63 Hz–2 kHz in the steady state and (b) 63 Hz–2 kHz in the cut window, each within 20 dB of the strongest band (first passing build, builder file 18: margins 4.17 and 2.29 dB); 4 and 8 kHz, the original clause, (b) against the 63 Hz–1 kHz median and a 16-seed ensemble printed; the null scoped to 63 Hz–2 kHz with the scene's per-band T60 and the air-absorption cause (Seat 9). Reason: a judgement, made after the red by the clause's author and the board, on S′'s chord-independent depth at L_f (4 kHz 40.14 dB against 18.72 dB at 63 Hz–1 kHz); no threshold was fixed in advance; the 20 dB tolerance is unchanged. A stimulus predicted to pass (1/√k; Seats 1, 3, 8, [Inferred]; not built) was declined as the primary on Seat 8's 2/2; a second bright arm was weighed and not added (FOR MAISARA L4-COV-P). `[ax49-l4]` placed per Seat 5's option (c). Decided for Maisara; amends nothing."

**Builder items (kit, not `/fix-plan`):**
- the median print and the 16-seed ensemble (a one-off kit command, output committed with the pre-registration commit);
- the null text in the kit and its pinning test replaced by the wording above;
- Debug and ASan `--durations` and peak RSS recorded in the PR.

## 7. Summary

| id | decision | state | worst-off (cell) | sum | conf. | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| L4-COV | E: (a) and (b) at 63 Hz–2 kHz within 20 dB, asserted; 4/8 kHz, the original clause, the median and the 16-seed ensemble printed; Seat 9's null wording; no automatic fallback | revised (stands on E) | 1 (S1 1/1) | 6 | medium | L105, L13, L17, NFR-8, AX5, AX49 | Kuttruff §3.8 (depth), Table 6.1 (air share) | S1 rates B-second < 1/1; (a)/(b) red on rebuild; ensemble median margin < 0; 07d contests; S8 rates B ≤ 1 |
| L4-COV-P | pad alone, bright arm as the recorded remedy | for Maisara | — | — | medium | L105, L13, L101, L17, L55 | — | as above |
| R5(a)/(e) | option (c), ratified with Seat 5's and Seat 7's conditions | proposed | 1 (S5 1/1, S7 1/0) | 3 | high | NFR-1, NFR-4, AX5 | — | Debug or ASan over 300 s after the re-entry fix; a Release red on MSVC (to Seat 3) |

**Challenges to settled decisions:** none.

## Decided for Maisara
- **L4-COV:** the held-chord test keeps the producer-style pad.
  - Its "enough energy" check now covers 63 Hz–2 kHz, both while the chord is held and in the 100 ms where the tail is cut.
  - 4 kHz is no longer asserted, and the result claims nothing there. By the cut, that band's tail has decayed 40 dB from its onset, mostly because air absorption in a room this large shortens its 4 kHz decay to 3.7 s.
  - This is recorded openly as a criterion change after a failed check, before any scored trial (NFR-1 L105; L17).
  - **Seat that gives the most:** Seat 1 gives up its 4 kHz clause.
  - **What it gets back:** an assert on the cut's exposure, and a result that states which bands it covers and why.
  - Amends nothing.
- **L4-COV-P:** no second, brighter-chord session (about 0.75 h) now. The PRD leaves test design to the Expert (L13, L105), and the board found its gain contested. It is the recorded remedy if the 07d review or a beta report contests the scope (L101, L55 weighed).
  - **Seat that gives the most:** Seat 8 (bright material stays untested).
  - **What it gets back:** the bright arm is held ready.
  - Amends nothing.
- **R5:** the 1e−9 provisional-versus-exact test runs on every PR in Debug and ASan, and in a Release step on Linux, macOS and Windows. The session starts the CI run, and her sitting is booked only after it is green (NFR-1; NFR-4; AX5).
  - **Seat that gives the most:** Seat 5 (per-PR CI time).
  - **What it gets back:** a gate on the binary that ships.
  - Amends nothing.

**NEEDS MAISARA:** none.

**Files:**
- /home/user/makroof/docs/review/phase-07c-2b/13-decider-l4-coverage.md
- /home/user/makroof/docs/review/phase-07c-2b/15-interrogator-on-file13.md
- /home/user/makroof/docs/review/phase-07c-2b/16-seat5.md
- /home/user/makroof/docs/review/phase-07c-2b/17-decider-m3-r4.md
- /home/user/makroof/docs/review/phase-07c-2b/18-builder-l4-coverage-applied.md
- /home/user/makroof/docs/review/phase-07c-2b/19-seat3.md, 19-seat7.md, 19-seat9.md
- /home/user/makroof/docs/review/phase-07c-2b/12-seat1.md, 12-seat8.md
- /home/user/makroof/docs/PRD.md (L13, L17, L49, L55, L101, L105, L112)
- /home/user/makroof/docs/phases/phase-08-3.md (L38–42, L122)
- /home/user/makroof/.github/workflows/ci.yml (L406–418)
- /home/user/makroof/tests/unit/test_ax49_l4.cpp (L1–9, L156–160)
- /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (L2827–2834)
