
# 17: Decider on M3, round 4 (rebuttal of interrogator file 10; corner home re-ruled; final /fix-plan texts)

This file is read-only. The orchestrator saves it as `/home/user/makroof/docs/review/phase-07c-2b/17-decider-m3-r4.md`.

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. Passages I re-read this round:
- Kuttruff Eq. 5.42 (L2698), Eqs. 5.44–5.45 (L2708–2710), the §5.6 caveat (L2724), Table 6.1 (L2827–2834).

**Files read:**
- Review files 10, 9, 13, 11, 14-seat1, 14-seat2, 14-seat7, 14-seat9, 8-seat9, plus 2 and 6 (texts only).
- The run sheet, in full.
- `phase-07c-2b.md` in full; `phase-08-3.md` L1–60; `phase-08-4.md` L1–30; `phase-07d.md` L1–30; `phase-13-2.md` L1–30.
- BUILD_PLAN §0 and §6, and AX47/AX49 (L170, L172).
- README L50–148.
- PRD L44–55, L75, L98–112, L127–174.
- From the code: `src/sim/Engine.cpp` L138–157.

## PRD digest (unchanged from file 9)
- **For whom:** producers and DJs (L17). Validation stimuli are never public copy.
- **Outcome:** NFR-1 (L105): "must match impulse responses measured in real spaces and pass listening tests".
- **Hard bounds:**
  - NFR-8 (L112): "Any valid scene renders correctly; no environment-specific code paths". This is a v1 requirement.
  - FR-3D-5 (L75): place sources "anywhere in the scene".
  - Spaces are empty (L54, L133).
  - Her AX21 decision; AX5; AX49's "never use the provisional", outside the validation exception.
  - The other AQ/AX rows, except the AX47 Reversal and design and the AX49 clause and L4 sentence.
- **Ranking:** "Accuracy first" (L49, L101), ranked against CPU and latency only.
- **Not bounded:** hours and schedule (L55, L174: "no fixed v1 deadline").
- **Verification:** every DSP behaviour has an automated check, nothing is loosened to pass, and a red is a stop.

---

## 1. Answers to the interrogator's questions (file 10)

**Q1 (corner placement): conceded.**
- Seats 2 and 7 were convened (14-seat2, 14-seat7). Both rate phase-13-2 at **0/2**.
- The phase-13-2 item is **withdrawn**. The home is re-ruled in §3 as a new report-only phase, `phase-07e`.
- C8 lapses: no edit to `phase-13.md` or `phase-13-2.md`.
- C9 is applied to the record. The premise in file 9 §4 now reads: "it already treats a W_max or n\*_max change as an output change (golden round) fixed before the first release (L23–24)". It no longer bears on anything, because 13-2 is not the home.

**Q2 (L4 label form): C7 accepted.**
- The label form is Kuttruff Eq. 5.44 with A = Σ S·α + 4mV, the same form as S-W's A ≈ 640 m².
- Seat 9 accepts C7 and gives the final text (14-seat9 §3). Its error was treating the engine's Eyring T60 as if it were Sabine's.
- Working (Eqs. 5.24–5.25, 5.44; Table 6.1, m = 1.08·10⁻³ m⁻¹ at 1 kHz and 50 % RH):
  - 4mV = 4,320 m²;
  - −S ln(1−ᾱ) = 20,125 − 4,320 = 15,805, so ln(1−ᾱ) = −0.2634 and ᾱ = 0.232;
  - A = 60,000 × 0.232 + 4,320 = 18,216 m²;
  - r_c = (18,216/16π)^½ = 19.04 m;
  - r/r_c = 40.31/19.04 = 2.12;
  - D/R = 20·log₁₀(19.04/40.31) = −6.5 dB.
- K10 is corrected to these values.
- **Fill rule (Seat 9):** ᾱ comes from the scene's 1 kHz α, and m from the engine's `bandsAirAttenuationDbPerMetre`. If the scene's α differs from the value back-solved from the printed T60 by more than 0.005, both are printed (print only).

**Q3 (Seat 9's hand-off to Seat 1): answered in 14-seat1.**
- Seat 1 confirms its V1-W cell at **0/1**. Its reason: A, B and X share the onsets, so the onset acts only through the heard tail share. That is "provided the S-W null wording adds the heard step". Without the heard step its later cell is 2.
- Seat 1's text is adopted verbatim (run sheet §6; 08-3 item 15 (i), per ear). So C2's reversal condition does not fire (Seat 1 §7).
- K13 is closed with the line: "answered, 14-seat1; heard-step clause adopted".

**Q4 (M3-3): conceded; the omission was mechanical.**
- C6's line is added to M3-3's acceptance check, and C1's line to M3-1's (§2).

**Q5 (run sheet texts): C3 and C5 accepted.**
- **C5:** "per family" (run sheet §4).
- **C3** is now met in full:
  - Seat 9 gave its (e) answer: S-B\* takes a **non-attributing** SPREAD clause (14-seat9 §2, exact text in §6 item 1). Seat 9 rates gated S-B\* with this clause 1/1, and 1/2 without any clause. The gate is released: "With this text adopted, my (e) answer is given and the S-B\* seal may proceed".
  - Seat 9 handed a residual question to Seat 1: "whether 1.2 dB per emitter changes what the S-B\* null covers". It goes to Seat 1 before the S-B\* seal, the same treatment C2 gave the S-W question.
  - In the meantime the S-B\* null wording carries the heard-step form. That form is my composition from Seat 1's S-W text and is marked as such.

---

## 2. Corrections C1–C9, applied

| C | applied text / state |
|---|---|
| C1 | M3-1 acceptance check gains: "**V1-W, file 6 handling:** NFR-1 with an equal-window seal print that cannot see an onset-driven spread, so the record could understate what a null rests on; L133 met. No PRD id ranks it above." |
| C2 | K13 added, then closed (Q3). Reversal condition added: "Seat 1, answering Seat 9's §8 hand-off before the seal, raises its V1-W later cell to 2". It does not fire: Seat 1 answered 0/1 with the heard step, and the clause is adopted. The new S-B\* hand-off goes to Seat 1 before the S-B\* seal. |
| C3 | Superseded by Seat 9's answer. Run sheet §1 carries the S-B\* SPREAD clause, and §3 lists the S-B\* seal preconditions (§6 item 1). |
| C4 | M3-2 step 5 now reads: "a skip removes evidence whose recovery costs one sitting of about 1–2 h (Seats 1, 6)". The winner is unchanged. |
| C5 | Run sheet §4: "≤ 0.0227 per family". |
| C6 | M3-3 acceptance check gains: "**HF-W without D:** NFR-1 with no asserted bound in a frame HF-W skips (Seat 5 later 2). No PRD id ranks it above." |
| C7 | L4 label: Seat 9's final text (§6 item 1, run sheet §7). K10 corrected as in Q2. |
| C8 | Lapses: 13-2 is not the home. Its counterpart for the new home is applied: §0 row 07e, plus the notes on rows 08-3 and 08-4, and `phase-08-4.md` (§6 items 6–8). |
| C9 | Applied to the record (Q1). |

Every other matter (M3-1, M3-2, M3-3, M3-4, M3-L4 and the hours) stands as file 9 ruled it, with the corrections above. None of them changes a winner.

---

## 3. Corner and onset findings: the home, re-ruled

### Restatement
The question is where Seat 2's board establishes the cause of three NFR-8 candidates, and whether that happens before 08-3's ABX stimuli and 08-4's golden freeze:
- **(a)** `both_corner`: L's 1 kHz tail is −6.20 / −6.12 dB at equal windows.
- **(b)** `both_wall`: the onsets are 0.165 / 0.380 s, giving +9.39 dB measured from each emitter's own onset.
- **(c)** s0.7: a −1.23 dB level spread measured from the common onset, lower priority (Seat 9).

The findings are measured, and no option tunes for them. The options:
- **H1:** a scope item in phase-13-2 (file 9; withdrawn).
- **H2:** a scope item in 07d.
- **H2-c:** H2 under Seat 2's condition: its own named scope with Seat 2 as Lead, exempt from 07d's split-off.
- **H3 (Seat 7's sense):** a dedicated phase that blocks all of Phase 08.
- **H4 (Seat 7's own option):** a report-only phase "07e" that depends on 07c-2b `done`, runs in parallel with 08-1 and 08-2, and gates only the build of 08-3's ABX stimuli and 08-4's freeze. Any fix it rules lands before 08-4.

Seat 2's "H3" means a phase "before 07d's growth re-pin and before 08-3". So the two seats use the label H3 differently: Seat 2's H3 is H4 plus an ordering against 07d.

### Convening table

| seat | status | reason | brief |
|---|---|---|---|
| 1 | not required for the home | The home is report-only, and NFR-8 binds whether or not the deficit is audible. Audibility of a 6 dB deficit (hand-offs from Seats 2 and 7) is an input to 07e's own loop, where the skeleton convenes Seat 1. | — |
| 2 | convened (14-seat2) | "late-tail statistics; image-source order; … simulator compute and recompute time; claims of physical accuracy" | as run |
| 3 | not required | no rendering, coloration or CPU-per-instance choice | — |
| 4 | not required | The chain is unchanged. 08-3 item 15's gate is a stimulus-build date, and the item-15 design is unchanged. | — |
| 5 | not required | The home adds a phase-order dependency: no audio-thread code, no CI gate, no host matter. 08-4's freeze already waits on 07c-2b by the same mechanism (D-W3). I do **not** adopt Seat 2's ordering against 07d's growth re-pin, which is Seat 5 ground. The skeleton sends any fix's order against 07d scope 8 to 07e's loop with Seat 5 convened. | — |
| 6 | not required | No control or default is affected. Whether the canvas makes corner placement easy (Seat 7's hand-off) is an input to 07e's loop. | — |
| 7 | convened (14-seat7) | "schedule and complexity cost of an option" | as run |
| 8 | not required | no producer-practice question | — |
| 9 | not required **now** | 12-2 is `not started` (§0). Under the chosen home the ruling precedes 08-3, and the decision adds no dependency to 12-2. The skeleton makes 07e's loop convene Seat 9 if 12-2 has started by then, and for (c)'s attribution. | — |

### Knowledge inventory

| K | what | source | status |
|---|---|---|---|
| K14 | finding values (a), (b), (c) | file 5 L21–23 (builder measurement); 14-seat9 §4 (−0.21 / −0.73 dB windows) | known |
| K15 | the AX22 fallback moves the handover to t_cap,e only when the realised-k test fails | from the code, Engine.cpp L138–157 | known. Seat 2's cause reading for (b) is [Inferred] and not load-bearing for the home. |
| K16 | 08-1 to 08-4 list no 07d dependency; 07d depends only on 07c-1 and 07c-1b; the 08-x freeze waits on 07c-2b (D-W3) | BUILD_PLAN §0 rows 07d, 08, 08-1 to 08-4 | known |
| K17 | 12-2 is `not started`; it depends on 12-1, 01 and 11 | §0 row 12-2 | known |
| K18 | the seats' cells and reasons | 14-seat2 §3–4, §6; 14-seat7 §3–4, §6 | known. Seat 2's H4 cell is read (below). Seat 7's H3/H4 later cell is given as a range, "0–1". |

No load-bearing gap remains. The session counts are Seat 7's [Hyp] and do not decide anything.

### Tension map (now / later)

| option | S2 | S7 | max | sum |
|---|---|---|---|---|
| H1, 13-2 | 0/**2** "a second golden round after 08-4's freeze … roughly a phase of rework" | 0/**2** "second golden round … re-hearing up to about 11 h … one phase before 13-5's beta" | 2 | 4 |
| H2, 07d item | 1/1 "enlarges an S–M phase"; "the item gets dropped when 07d splits" | 1/1 "likely to be split off again"; "M3-8 still voids the cross-chain comparison unless omni is rerun" | 1 | 4 |
| H2-c | 1/0 (Seat 2's condition) | 1/1. Seat 7's condition for H2 going "from 1 to 0" is "home it as its own sub-phase (H4)", which H2-c does not meet. | 1 | 3 (premise unmet; see step 5) |
| H3, blocks all of 08 | 1/1 (Seat 2's H3 reasons: "one S session"; "a fix still costs one golden round … only once and before the freeze") | 1/0–1 "holds up all of Phase 08" | 1 | 3–4 |
| **H4, 07e** | 1/1 (**read** from Seat 2's own H3 cell, the closest option it rated: its own phase, Lead Seat 2, before 08-3; H4 lacks only the 07d ordering, which none of Seat 2's reasons cite) | 1/0–1 "off the critical path"; residual: "a fix that turns out to need more than one session … would then hold 08-4" | **1** | **3–4** |

### Working
1. **Bounds.** NFR-8 (L112) is a v1 requirement. Every option rules before release, so none breaks a bound.
2. **Veto.** No seat rated 3.
3. **Worst-off seat.** H1 holds a 2 from both seats and is out. H2, H2-c, H3 and H4 tie at max 1.
4. **Compose.** No variant lowers the maximum below 1. Every survivor's "now" is 1: one session, as both seats say.
5. **Sum.** H2-c (3) would lead H4 (3–4), but it cannot be ranked as rated:
   - Seat 2's later 0 for H2 rests on its premise "It still lands before the freeze" ("It does sit before 08"). The plan does not give 07d that order (K16).
   - Making the premise true needs one of two things:
     - 07d gates 08-3 and 08-4. That puts 07d's load, macOS and re-pin work (Seats 5 and 7 are 07d's convened seats) on Phase 08's critical path, a cost no seat has rated.
     - Only the item gates them. That is H4 under another file name, and Seat 7's condition asks for exactly that ("its own sub-phase").
   - Separately, and not as a re-rating: Seat 2 counts the golden round in H3's later 1 but not in H2-c's 0. I put the question to Seat 2 under the strongest objection.
   - Among the rankable options, H3 and H4 have equal cells.
6. **Reversibility.** H3 and H4 both undo by deleting one phase file. H4 does not hold 08-1 and 08-2, so if the investigation stalls it holds only the two gated items. Seat 7's H3 later reason ("holds up all of Phase 08") does not arise.
7. **Decide: H4.**

### DECISION M3-H: H4, `phase-07e`
- It is a report-only phase with Seat 2 as Lead, size S, and depends on 07c-2b `done`.
- It runs in parallel with 08-1 and 08-2. It gates **only** the build of 08-3 item 15's stimuli and 08-4's golden freeze.
- If 07e's board rules that `src/sim` must change, the fix is a **separate phase file** written by that loop and ordered before 08-4's freeze. It fires M3-8 and costs one golden round (§6 row). It must contain no scene-specific logic (NFR-8).
- Items (1), (3) and (4) of file 6's corner routing stand: the PR Follow-ups NFR-8 report; both_corner third in the S-W fallback order; M3-8 on any fix.

**Load-bearing:**
- **H-L1:** Seats 2 and 7 rate H1 0/2 in their own words.
- **H-L2:** K16, plan text.
- **H-L3:** the seats' H3 and H4 cells; Seat 2's H4 cell is read (marked).

**Future-debt register (H4):**

| seat | commits later phases to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| 2 (later 1) | a fix costs one golden round before 08-4's freeze, and M3-8 rebuilds both sealed scenes | delete the 07e file (before it starts); after a ruling, as the ruling says | 07e's board ruling | 07e rules "no breach", or the fix phase lands before 08-4 |
| 7 (later 0–1) | a fix that needs more than one session holds 08-4's freeze | 07e's loop rules on the fix's order (Seats 2, 5, 7) | 07e's board ruling | the fix lands, or the loop records another order |

**Strongest objection:** H2-c's sum of 3.
- **Why it holds anyway:** its later 0 needs 07d ordered before the freeze, and the plan does not order it there (K16). The ordering has unrated costs for Seats 5 and 7, and Seat 7's own condition is a separate sub-phase.
- **Question to Seat 2 (not a re-rating):** does H2-c's later 0 still hold once the golden round you count in H3 is included?
- **When the decision would not hold:** if Seat 2 rates H4 later 0, nothing changes. If Seats 2, 5 and 7 rate an H2-c with gating below H4's sum, the scope moves into 07d by one `/fix-plan`, before 07e starts.

**Confidence:** medium. One cell is read, and one is a range.

**Reversal conditions:**
- the rated H2-c-with-gating case above;
- 07e's loop finds the investigation needs a `src/sim` probe. A report-only phase cannot do that, so the loop writes the fix or probe phase.

### Which reading of README 3(a) I apply
This is past the third contested round on M3, and the corner home is the one item still contested. I apply the **strict reading**: the README counts rounds, not rulings ("a ruling after 3 contested rounds that fails the interrogator's check"), and my own rules say "at most 3 rounds in all".

So M3-H is also written below as **FOR MAISARA M3-H**. The interrogator checks it **once**. Any verdict other than SURVIVES or SURVIVES WITH CORRECTIONS, UNDERCONVENED included, sends it to her as **NEEDS MAISARA, case (a)**, with both readings and my recommendation (H4).

The other reading, under which the count restarts because the corner home is a new ruling, is not applied. It would allow three more rounds on an item already three rounds old.

### FOR MAISARA M3-H
- **Question:** before or after Phase 08's golden freeze, and in which phase, is the cause of the three placement findings established?
- **Answer:** "A report-only phase-07e (Lead Seat 2) rules on the cause before 08-3's ABX stimuli are built and before 08-4 freezes the goldens; any `src/sim` fix is its own phase, landing before 08-4."
- **Rests on:**
  - NFR-8 L112: "Any valid scene renders correctly; no environment-specific code paths".
  - FR-3D-5 L75: "any number of sources anywhere in the scene".
  - NFR-1 L105.
  - "Accuracy first" (L49, L101).
  - "no fixed v1 deadline" (L174, L55).
- **Reasoning:**
  - NFR-8 is a v1 requirement, and FR-3D-5 makes corner placement a product use.
  - A tail that is wrong at a corner would be frozen into the goldens and into 08-3's binaural record if its cause were found only at 13-2.
  - The PRD puts accuracy first and bounds no schedule, so settling the cause earlier strains no PRD id.
  - The PRD does not rank one file placement over another. Among homes that rule before the freeze, the board's ordering decides.
- **Options against the PRD ids:**
  - **H1:** strains NFR-1 and NFR-8 (goldens and the 08-3 record are frozen before the cause is known); L174 is unaffected.
  - **H2 / H2-c:** serve NFR-8 only if 07d is ordered before the freeze, which the plan does not do.
  - **H3:** serves NFR-8 and NFR-1; no PRD id strains (Seat 7's schedule cost is not a PRD bound, L174).
  - **H4:** serves NFR-8 and NFR-1, the same as H3.
- **What would make her veto it:** a reading of L174 and her one-founder capacity as weighing against any extra phase before release. The PRD does not say this; it says only that there is no deadline.
- Amends nothing.

### Phase file skeleton: `docs/phases/phase-07e.md` (verbatim for the plan-editor)

> # Phase 07e — NFR-8 placement findings from the 07c-2b ABX scenes: cause ruling (report only)
>
> Size: **S** · Depends on: [07c-2b](phase-07c-2b.md) `done` (the engine its golden round leaves) · Lead subject matter: Seat 2 (Engine architect), "late-tail statistics; image-source order; … claims of physical accuracy" · Created 2026-11-24 by phase-07c-2b's M3 loop (`docs/review/phase-07c-2b/17-decider-m3-r4.md` §3; Seats 2 and 7, 14-seat2, 14-seat7) · Read first, in this order: `CLAUDE.md`; this file; `docs/review/phase-07c-2b/5-builder-tail-spread.md`, `14-seat2.md`, `14-seat7.md`, `14-seat9.md` §2, `17-decider-m3-r4.md` §3; `docs/BUILD_PLAN.md` §2 AX16, AX21, AX22, AX37, AX40, AX43; PRD NFR-1, NFR-8, FR-3D-5.
>
> ## Raise with Maisara
> None.
>
> ## Goal
> Establish, for each finding below, whether NFR-8 ("Any valid scene renders correctly") is breached and why, before 08-3's ABX stimuli are built and before 08-4 freezes the goldens. No `src/sim` change in this phase; nothing is tuned for a scene.
>
> ## Gates (what waits on this phase)
> - The build of phase-08-3 item 15's stimuli, and phase-08-4's golden freeze, wait on this phase `done`, and on the fix phase it rules, if any. Nothing else waits: 08-1 and 08-2 run in parallel.
> - It is not ordered against 07d. If a fix is ruled, the loop sets its order against 07d scope 8 (growth re-pin) with Seat 5 convened.
>
> ## Scope
> 1. **Findings** (builder file 5; 14-seat9):
>    - (a) `layout4_s1/both_corner`: emitter L (0.1 m from two walls and the ceiling) has a 1 kHz tail 6.20 / 6.12 dB below R's at equal absolute windows (−6.80 dB from each emitter's own t_mix,e), where Kuttruff Eq. 5.42 expects equal reverberant levels at equal power (indicative, §5.6).
>    - (b) `layout4_s1/both_wall`: tail onsets t_mix,e 0.165 / 0.380 s; from its own onset L's 1 kHz tail energy is +9.39 dB over R's (−0.05 / −0.03 dB at equal windows).
>    - (c) lower priority: `layout4_s0.7/default`, −1.23 dB (L − R) from the common onset 0.380 s (−0.21 / −0.73 dB in the equal windows), not attributed (the room is not diffuse).
> 2. **Candidate causes:**
>    - (a): the AX40 estimator, the image-source set at a corner source, the t_mix,e rule.
>    - (b): AX22's realised-k test at a source 0.1 m from a face. From the code, `planEmitter` moves the handover to t_cap,e only when the test fails, and R's 0.380 s matches the fallback time of the other layout4_s1 scenes (Seat 2, [Inferred]). Or the t_mix,e rule.
>    - Confirm with `ismFallback`, `expectedMixS` and `capTimeS` from `--diagnostics`.
> 3. **Measurement** (Seat 2; no `src/sim` edit; deterministic, AX5):
>    - A placement sweep at 0.1, 0.2, 0.5, 1 and 2 m from 1, 2 and 3 faces.
>    - For each placement and each emitter: the equal-window 1 kHz level against Eq. 5.42; E_target (AX40) against the `matchTail` energy; `--tail-level ax16` against the default; k_real and the fallback flag.
>    - For (b), window energy from the full IR (not tail-only), to test whether L's ISM-to-tail energy is continuous across [0.165, 0.380) s against R's ISM-only energy.
>    - Nothing is fitted to the compared level (no circularity).
> 4. **Board loop** (Lead Seat 2; decider; interrogator SURVIVES):
>    - It rules, per finding: NFR-8 breached / not breached (a level spread > 1 dB at equal times unexplained by physics, Seat 2's test) / not decidable, with the cause.
>    - Hand-offs it convenes: Seat 1 (whether a ~6 dB per-emitter tail deficit is audible for producers); Seat 6 (whether the canvas makes corner placement easy, FR-3D-5); Seat 9 (attribution for (c), and, if phase 12-2 has started, which presets place a source within 0.5 m of a face); Seat 5 and Seat 7 (any fix's order and cost); the researcher (a corpus source on a source's radiated power near a boundary at 1 kHz, 0.1 m).
> 5. **If a `src/sim` change follows:** the loop writes it as its own phase file (e.g. `phase-07f.md`), ordered before 08-4's golden freeze. It is an output change (golden round, §6 row), fires phase-07c-2b M3-8 (rebuild and reseal both ABX scenes before 08-3 listening), and adds no scene- or placement-specific logic (NFR-8). If the loop finds the fix cannot land before 08-4, that order is its own board ruling, never a default.
>
> ## Out of scope
> Any `src/sim` edit; tuning for a scene; preset or canvas changes; 07d's work.
>
> ## Acceptance criteria — automated
> - [ ] The sweep script and its output JSON committed; a pytest re-runs at least one placement through `render_cli` and asserts the committed values bit-identically (AX5).
> - [ ] §0 rows 07e (and 08-3 / 08-4 notes, if the ruling adds a fix phase) updated.
>
> ## Definition of done
> The report and the board ruling for (a), (b) and (c) are committed under `docs/review/phase-07e/`, and the interrogator returns SURVIVES. If a fix is ruled, the fix phase file and its §0 row exist. The PR lists "Decided for Maisara". CLAUDE.md rules apply.

---

## 4. M3-1 and M3-3 acceptance checks (restated with C1 and C6)
- **M3-1:** file 9's six lines plus C1's line. No PRD goal points away from V1-W with Seat 9's conditions.
- **M3-3:** "**HF-W + D, N1–N3:** serves NFR-1 (a derived bound, with failing tests built in)", plus C6's line. No PRD id points away.

---

## 5. Hours
Unchanged from file 9 (SURVIVES).

---

## 6. FINAL consolidated texts for one `/fix-plan`

### Item 1: `docs/validation/abx-07c-2-run-sheet.md`

**Title:** "# AX47 self-ABX and AX49 L4: run sheet (phase 07c-2 D-W2, as amended by phase 07c-2b M3)"

**Intro:** "Nothing on this sheet changes it" becomes "Nothing on this sheet changes it except the amendments in §0, each made by a board decision before any stimulus was heard."

**New §0:**
> ## 0. Amendments to file 13 (phase-07c-2b M3; decider files 2, 6, 9, 13, 17; interrogator files 3, 7, 10 and its check of file 17)
> - **Items 2–3:** each chain of each family has 24 scored trials + 6 interleaved 3 dB anchors (3 per half, break after presentation 15); 0.9 dB, then 0.5 dB only after a 0.9 dB detection in that chain of that family; detection ≥ 18/24; anchor ≥ 5/6 (M3-2). Fallback: §4.
> - **Item 4:** applies across F1–F4 (§4).
> - **Item 5's clause:** "[S-A only …]" replaced (§1).
> - **Item 9:** two scenes, F1 S-W `layout4_s1/both_wall` and F2 S-B\* `layout4_s0.7/default`, with their labels and fallbacks (§1).
> - **Item 13:** the record wording, with the heard step (§6).
> - **Item 14:** L4 design (M3-L4, decider file 9), its band coverage amended by decider file 13 after the first build's red (4 kHz −22.94 dB), before any scored trial (§7).
> - **Item 15:** the 08-3 binaural rerun, now in `docs/phases/phase-08-3.md`.
> - **M3-6:** the speech pair rule (§3). **M3-8:** the rebuild trigger (§1). **C-b:** the two-measure tail-spread print (§1).

**§1 edits:**
- **Item 5:** replace the "[S-A only, as long as layout4_s1/default is the ABX scene:] … (file 5's wording)." paragraph with:
  > "[every ABX scene with s = 1 on all faces (layout4_s1/both_wall or its sealed fallback): E_spec = 0 in every band (AX21; Kuttruff Eq. 8.59), so this equals scaling E_b alone.] [layout4_s0.7/default: the target specular share is up to 0.032 (max over bands and emitters, file 29), so scaling E_b alone would give 0.87 dB, not 0.9 (10·log10(0.032 + 1.2303 × 0.968) = 0.874 dB). Item 6's identity is asserted there, and M1's reversal condition is live on this scene.]"
- **"Which T30", "M2 debt check" and the Q5 realised window:** prefix each layout4_s1/default figure with "S-A, history:" and add:
  > "Each sealed scene's values are printed and used instead: both_wall heard-IR T30 1.370 s, tail T30 1.313 / 1.274 s; s0.7 heard-IR T30 1.831 s, tail T30 1.254 / 1.274 s; the Q5 window is recomputed per sealed scene."
- **"Scene" bullet:** replace it with:
  > "**Scenes (item 9, M3-1):** F1 S-W and F2 S-B\*, labels below; fixed tailSeed 12345 (kit choice); each asserted capped at m = 6, 7, 8; D/R per emitter and heard, printed. **S-W fallback order** (by tail share; the first that passes every gate): listener_corner, listener_edge, both_corner, emitter_wall, listener_wall; if none with share ≥ 0.129 passes, M3 returns to the board. **S-B\* fallback:** `layout4_s0.9/default`. Fallback labels use the S-W template below with their own values, name every face whose reflection is absent, and are confirmed by Seat 9 before the seal."
- **S-W label:** file 9 §6's text, verbatim. It already holds the C-a onset sentence.
- **S-B\* label:** file 6's text, with Seat 9's clause inserted after "tail T30 1.254 / 1.274 s." and before "Not a validated preset.":
  > "At equal source power the emitter tails at the listener differ at 1 kHz by −1.2 dB (L − R), integrated from their common onset t_mix,e 0.380 s; −0.2 / −0.7 dB in the equal windows [0.45, 0.65) / [0.8, 1.0) s. A diffuse room gives equal reverberant levels (Kuttruff Eq. 5.42), but with all absorption on the floor this room is not diffuse (§5.6), so the spread is not attributed to engine or room; reported under NFR-8."
- **S-W fallback template:** Seat 9's template (4-seat9 L56), with NEAR-FACE naming each face and "Tail onsets t_mix,e {a} / {b} s" before {SPREAD} (file 6). SPREAD has two forms:
  - the onset form: the C-a text with the scene's values;
  - the level form: Seat 9's R2-2 text, or the non-attributing S-B\* form above, at Seat 9's call when it confirms the filled label.
- **New bullets:**
  > "- **Tail-spread print (C-b), before each seal:** L − R at 1 kHz (i) integrated from each emitter's own t_mix,e to the end of the IR, (ii) over [0.45, 0.65) and [0.8, 1.0) s; on S-B\* also [0.380, 0.45) s (print only). On S-W and its fallbacks, either measure > 1 dB (a print threshold, not an audibility claim) requires the SPREAD clause in the label; every firing goes to phase-07e as an NFR-8 candidate.
  > - **S-B\* step/dip print:** the AX21 step and dip at t_mix,e per band and emitter, [t_mix,e − 20, t_mix,e − 2.5) ms against [t_mix,e + 2.5, t_mix,e + 20) ms.
  > - **Q5 on both_wall (kit choice):** the onset window counts from the latest heard end of speech (input end plus the largest emitter direct delay).
  > - **Rebuild trigger (M3-8):** 'On any `src/sim` change that alters a sealed scene's rendered IR (B11 promotion, the t_mix,e rule, estimator constants), the stimuli are rebuilt, pass every seal gate again, and their hashes are re-registered before the next listening session. Earlier results stand, each recorded with the engine it was obtained on.'
  > - **r_c in the manifest:** the kit's '0.057·√(V/T60_Eyring)' is named as such; labels use Kuttruff Eq. 5.44 (A/16π)^½ with A = Σ S·α + 4mV."

**§3 edits:**
- **Item 2:** "Speaker MA, files MA01_01 and MA01_02 (M3-6). Fallback order: MA01_03 / MA01_04, then the first two files of the next adult speaker in the archive's alphabetical directory order (CA, CB excluded); the first pair that passes Q5 on every sealed scene is used in all four families."
- **Item 3:** builds per scene. In the assertion list, "no new click at the step" becomes "HF-W (β 1.1378) with condition D and N1–N3".
- **Item 4:** add:
  > "The pre-registration commit holds both scenes' prereg records and L4's sealed hashes, before the first scored trial. **Seal preconditions:** S-W: Seat 9 confirms the filled label. S-B\*: the SPREAD clause above is in the label (Seat 9's (e) answer, 14-seat9) and Seat 1 has answered Seat 9's question whether the −1.2 dB spread changes what the S-B\* null covers. L4: §7."
- **Item 5:** add "The builder times one speech block and L4 before the dates are fixed."

**§4 edits:**
- **Blocks:** "30 presentations: 24 scored trials and 6 interleaved anchors (a uniform 3 dB tail step), 3 anchors in each half; break after presentation 15."
- **Table:**

  | family | scene | chain | first test | second test (only after a 0.9 dB detection in that chain of that family) | anchor |
  |---|---|---|---|---|---|
  | F1 | S-W | noise | 0.9 dB at ≥ 18/24 | 0.5 dB at ≥ 18/24 | 6 per block, ≥ 5/6 |
  | F1 | S-W | speech | 0.9 dB at ≥ 18/24 | 0.5 dB at ≥ 18/24 | 6 per block, ≥ 5/6 |
  | F2 | S-B\* | noise | 0.9 dB at ≥ 18/24 | 0.5 dB at ≥ 18/24 | 6 per block, ≥ 5/6 |
  | F2 | S-B\* | speech | 0.9 dB at ≥ 18/24 | 0.5 dB at ≥ 18/24 | 6 per block, ≥ 5/6 |

- **Rates:**
  > "Family: ≤ 0.0227 per family (2 × 190051/2²⁴, union bound), ≤ 0.0453 at 07c-2b, ≤ 0.0906 with 08-3's F3/F4; power 0.607 per chain at p = 0.75; no α passes between chains or families. If the trial count is cut (only in the pre-registration commit, before any scored trial), all four families revert to file 13's unsplit thresholds (noise ≥ 12/16, speech ≥ 13/16) with C1; never 13/13."
- **Stopping rule, step 4:** "A detection at 0.9 dB in any chain of any family (F1–F4) sets AX47's bound to 0.5 dB for all scenes; a non-detection never cancels a detection. A detection at 0.5 dB is a class (c) finding; at 08-3 it reopens that round at the board."
- **Order:** "S-W (noise 0.9 dB first, then speech), then S-B\*, then L4 alone after a rest, the same day as the S-B\* sitting; sittings ≤ 2 h, split only at a chain boundary."

**§5:** "One table per family, chain and level, presentations 1–15 | break | 16–30 (`abx_kit.py blank` writes them; anchor positions are in the key only). 0.5 dB tables are headed 'only after a 0.9 dB detection in this chain of this family'."

**§6:**
- **Columns:** listener | family | scene | chain | level (dB) | k/24 | exact p | anchor k/6 | heard ΔG / ΔC80 at 1 kHz (manifest) | scene hash | tailSeed | commit | wording.
- **Wording:**
  > - "detected (≥ 18/24, family α 0.0227)";
  > - S-W: "not detected in 24 trials by one listener (power 0.61 at p = 0.75) on layout4_s1/both_wall (tail share 0.667 at 1 kHz, resting on the engine's t_mix,e onsets 0.165 / 0.380 s (own-onset tail L − R +9.4 dB; −0.05 dB at equal times); listener and emitter 0.1 m from a face); heard step at 1 kHz ΔG +0.62 dB, ΔC80 −0.90 dB for the 0.9 dB tail step [0.5 dB: ΔG and ΔC80 as printed in the manifest], at the recorded commit; void as evidence for this scene after a t_mix,e change until rebuilt (M3-8)." (Seat 1, 14-seat1 §6; Seat 9's record line);
  > - S-B\* (decider's composition from Seat 1's form; Seat 1 confirms before the S-B\* seal): "not detected in 24 trials by one listener (power 0.61 at p = 0.75) on layout4_s0.7/default (tail share {printed} at 1 kHz; tail onsets 0.380 / 0.380 s; tail spread L − R −1.2 dB from the common onset, not attributed; early part specular-only, partial AX21); heard step at 1 kHz ΔG {printed} dB, ΔC80 {printed} dB for the 0.9 dB tail step [0.5 dB: as printed in the manifest], at the recorded commit; void as evidence for this scene after an M3-8 trigger until rebuilt.";
  > - "inconclusive" if the anchor failed.
  > - ΔG and ΔC80 are taken from the manifest, never typed by hand. "A non-detection is recorded for its scene class only; the 1 dB bound elsewhere rests on D-C1, as AX47 states." The record states each family's α, the union rate and which family detected at what count. Never write "inaudible"; no public copy.

**§7, new: "AX49 L4: the held-chord ABX (item 14, as amended by M3-L4 and decider file 13)":**
> - **Design (L4-A on S′):** A = AX49 provisional tail (`Engine::assembleProvisional`, `render_cli --ax49-provisional`), faded over [L_f, L_p) = [3.6135, 3.7135) s; B = the exact tail; one tailSeed for both; fully wet; omni diotic. Seat 1's chord ('l4-chord-v1', 4-seat1 L96–121; kit seeds 4901/4902/4903). 16 scored trials + 6 anchors (3 dB, ≥ 5/6); detected at ≥ 12/16; α 2517/65536 = 0.0384, its own family; power 0.630 at p = 0.75.
> - **Label (Seat 9, 14-seat9 §3, verbatim):** "ax49_l4_cube: synthetic 100 × 100 × 100 m, V 10⁶ m³, every face the same α per band, scattering 0.3. Listener (50, 30, 1.7) m; emitters (45, 70, 2) and (55, 70, 2) m, each 40.3 m from the listener. T60 8.0 ± 0.1 s from 63 Hz to 1 kHz as printed by the engine (Eyring, T60_max 8 s, air absorption included), shorter above 1 kHz where α is held at its 1 kHz value; per-band T60 printed. D/R at 1 kHz {printed} dB heard, against about −6.5 dB in a diffuse field at r/r_c 2.1 (r_c ≈ 19 m from A = Σ S·α + 4mV ≈ 18,200 m² at 1 kHz, the label form; Kuttruff Eqs. 5.24–5.25, 5.44–5.45, Table 6.1; indicative only: ᾱ ≈ 0.23 at 1 kHz is not small, §5.6). A stress geometry for AX49's provisional tail, not a room prediction or a validated preset. A = AX49 provisional tail (Engine::assembleProvisional, validation-only flag --ax49-provisional), faded over [L_f, L_p) = [3.6135, 3.7135) s; B = full engine tail ('exact' = full synthesis, not a measurement); one tailSeed {seed} for A and B. Fully wet: the whole rendered IR (direct, early part and tail), no dry path." Fill rule: ᾱ from the scene's 1 kHz α and m from the engine's air table; if the back-solved α differs by > 0.005, both are printed. Seat 9 confirms the filled text.
> - **Band coverage (decider file 13, verbatim):** "Band coverage (Seat 1; amended by decider file 13 after the first build's red, before any scored trial). (a) The exact render's steady state (the last 1 s of the hold) has every band from 63 Hz to 2 kHz within 20 dB of its strongest band. (b) In the 100 ms where the cut begins in the aligned output (kit interpretation 2), the exact render's energy in every band from 63 Hz to 2 kHz is within 20 dB of its strongest band. Both are asserted. 4 kHz and 8 kHz are printed with their depth at L_f. The original clause (63 Hz–4 kHz) is printed with its result (first build: 4 kHz −22.94 dB, red). The scope follows from S′'s depth at L_f (63 Hz–1 kHz 18.72 dB, 2 kHz 23.19 dB, 4 kHz 40.14 dB), which no chord changes." Negative control N-L4: the chord limited to ≤ 500 Hz fails (a) and (b).
> - **Checks before the seal:** Seat 2's S′ asserts; Seat 3's P1–P6 and S1–S7, S2–S4 on the partition grid (IR time with +1·P; written-file time without it); N-L1–N-L4; in both arms the IR is installed in the first partition (no AQ4 fade-in in the prefix); Seat 1's prefix check; F1–F6 and F2′ 1–4 of the flag; decider file 13 R1–R7; the Catch2 `[ax49-l4]` case (P4/P5 at 1e−9, N-L1/N-L2 inside) green on Linux, macOS and Windows, its CI placement per Seat 5's answer (file 13 brief). A red is a stop, never loosened.
> - **Timing:** built, all checks green, sealed, hashes in the pre-registration commit, before the first scored AX47 trial. If the build stalls, AX47 listening waits and Seats 1, 3 and 7 are re-asked (frozen spec + C1–C3 is the pre-rated candidate).
> - **Wording:** "not detected in 16 trials by one listener (power 0.63), T60 8 s, held chord, omni diotic; cut exposed at 63 Hz–2 kHz; at 4 kHz the tail is 40 dB down at L_f". A detection fires AX49's Reversal: "worst case: provisional current through the whole free decay".

**§8 (was §7) "Not in this kit":** the 08-3 rerun is now `docs/phases/phase-08-3.md`, item 15; the kit-choices list stays as it is.

### Item 2: `docs/phases/phase-08-3.md`
Add a new scope item after item 7, and the manual-checklist line "AX47 binaural rerun, item 15, F3/F4". The item's text is file 9 §6 item 2, verbatim, with three insertions:
- **Into (i)**, after "a detection reverses AX47 per item 4.":
  > "A null there is worded with its heard step per ear: 'not detected in 24 trials by one listener (power 0.61 at p = 0.75) on layout4_s1/both_wall (<record line>); heard step at 1 kHz ΔG {L} / {R} dB, ΔC80 {L} / {R} dB per ear for the 0.9 dB tail step [0.5 dB: as printed in the manifest], at the recorded commit; void as evidence for this scene after a t_mix,e change until rebuilt (M3-8)', values from the manifest, never typed by hand."
- **Into (ii)**, after "likewise identical.":
  > "Its null is worded in the 07c-2b S-B\* form, with per-ear ΔG and ΔC80, and carries the label's SPREAD clause."
- **Before "Before any stimulus, per scene":**
  > "Stimuli are built only after phase-07e is `done` (and the fix phase it rules, if any)."

### Item 3: BUILD_PLAN AX47
- **Reversal:** file 9 §6 item 3's text, verbatim.
- **Design:** file 9's paragraph, with two changes:
  - the citation becomes "decider files 2, 6, 9, 17; interrogator files 3, 7, 10 and its check of file 17";
  - before "If the trial count is cut", insert: "a non-detection is recorded for its scene class only and at its heard step (ΔG, ΔC80 at 1 kHz from the manifest, at the recorded commit);".
- **Sources:** "M3 loop; decided for Maisara, amends nothing".

### Item 4: BUILD_PLAN AX49
- **Clause:** file 9 §6 item 4, verbatim.
- **L4 sentence:**
  - "07c-2" becomes "07c-2b".
  - After "free decay", insert: "(design, phase-07c-2b M3-L4: A = the provisional faded over [L_f, L_p), B = the exact tail, one fixed tailSeed; scene `ax49_l4_cube` (100 m, T60 8.0 s at 63 Hz–1 kHz, L_p 3.71 s < L 12 s); band coverage asserted at 63 Hz–2 kHz in the steady state and in the cut window, 4 and 8 kHz printed (decider file 13: a criterion change after the first build's red, before any scored trial); stimuli built, checked and sealed before the first scored AX47 trial)".
- FM-2′ is untouched.

### Item 5: `docs/phases/phase-07c-2b.md`
- Raise 2 and the scope 3 texts: file 9 §5, verbatim.
- Scope 2's "Amendments held for M3" is marked "applied (M3, decider files 9 and 17; run sheet §0)".
- Add to "Out of scope": "The cause ruling on the NFR-8 placement findings (both_corner, both_wall onset, s0.7 spread): phase-07e (decider file 17 §3); this phase's PR lists them under Follow-ups."

### Item 6: new file `docs/phases/phase-07e.md`
The skeleton in §3, verbatim.

### Item 7: BUILD_PLAN §0
- **New row after 07d:**
  > "| 07e | [NFR-8 placement findings: cause ruling (report only)](phases/phase-07e.md) | S | not started | | | Depends on 07c-2b `done`. Created 2026-11-24 by phase-07c-2b's M3 loop (decider file 17 §3, H4; Seats 2, 7). Lead: Seat 2 (Engine architect). No `src/sim` change; a fix, if ruled, is its own phase before 08-4's freeze. Gates only 08-3 item 15's stimulus build and 08-4's golden freeze; runs in parallel with 08-1 and 08-2. |"
- **Row 08-3 notes**, append: "Item 15's stimuli (AX47 binaural rerun) are built only after 07e `done` (and its fix phase, if any)."
- **Row 08-4 notes**, append: "The golden freeze also waits on 07e `done` and on the fix phase 07e rules, if any (phase-07c-2b M3, decider file 17)."

### Item 8: `docs/phases/phase-08-4.md`
After the scope's order paragraph (L24–26), add:
> "The golden freeze also waits on phase-07e `done` and on the fix phase it rules, if any (phase-07c-2b M3, decider file 17 §3; Seats 2, 7)."

### Item 9: BUILD_PLAN §6, two rows dated 2026-11-24, by "phase-07c-2b session (Claude), board loop"
1. "Phase 07c-2b M3 loop (decider files 2, 6, 9, 13, 17; interrogator files 3, 7, 10 and its check of file 17; corpus c1b171f): AX47 Reversal and design amended (F1–F4, both chains ≥ 18/24, 24 + 6, per family ≤ 0.0227, union ≤ 0.0906; nulls at their heard step); AX49 validation-only `render_cli --ax49-provisional` clause and L4 design; run sheet §0–§8 (two scenes and labels, C-b tail-spread print, S-B\* SPREAD clause, L4 section); phase-08-3 item 15; phase-07e created (report-only cause ruling on three NFR-8 placement findings, gating 08-3 item 15's stimuli and 08-4's freeze; §0 rows 07e, 08-3, 08-4); phase-07c-2b Raise 2 and scope 3 hours. Decided for Maisara; amends nothing."
2. "Threshold changed (AX49 L4 band coverage, decider file 13): Seat 1's clause '63 Hz–4 kHz within 20 dB' failed on the first full build (4 kHz −22.94 dB re 125 Hz, builder file 11), before any scored trial; replaced by 63 Hz–2 kHz in the steady state plus a cut-window assert, 4/8 kHz and the original clause printed, the null scoped to 63 Hz–2 kHz. Reason: S′'s depth at L_f (4 kHz 40.14 dB) is chord-independent; recorded as a criterion change after a red, not a loosening to pass."

**Builder items (kit, not `/fix-plan`):**
- C-b's two-measure print, plus the S-B\* [0.380, 0.45) s window;
- the label fills;
- ΔG and ΔC80 in the record template;
- the file 13 kit items;
- timing one speech block and L4.

---

## 7. Summary

| id | decision | state | worst-off (cell) | sum | conf. | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| M3-1 | V1-W with C-a, C-b, item-13 line; S-B\* non-attributing SPREAD clause; heard-step null wording | stands (C1–C3 applied) | 1 | 12 | high | NFR-1, FR-3D-5, L133 | Kuttruff 5.42, 5.44–5.45, 7.6, 8.59 | gates exhausted; HF-W red; Seat 9 rejects a label; Seat 1 raises S-W or S-B\* later to 2 |
| M3-2 | both chains ≥ 18/24 in F1–F4; no skip | stands (C4, C5) | 1 (S7) | 4 | high | NFR-1, L55 | — | trial count cut before scoring |
| M3-3 | HF-W + D, N1–N3 | stands (C6) | 1 | 4 | high | NFR-1 | — | a clean stimulus reds |
| M3-4 / M3-L4 | texts; L4 label in the Σ S·α + 4mV form | stands (C7) | 1 | 8 | high (timing, flag); medium (design) | NFR-1, AX5, AX49 | Kuttruff 5.24–5.25, 5.44–5.45, Table 6.1 | S′ fails; check reds; Seat 9 rejects fill |
| M3-H | phase-07e, report only, Lead Seat 2; gates 08-3 item 15 stimuli and the 08-4 freeze | proposed; FOR MAISARA (one check) | 1 (S2, S7) | 3–4 | medium | NFR-8, FR-3D-5, NFR-1, L174 | Kuttruff 5.42 (indicative, the findings) | Seats 2, 5, 7 rate a gated H2-c below H4 |

**Challenges to settled decisions:** none.

## Decided for Maisara
- **M3-1 to M3-L4 (corrections only):**
  - A "not heard" result now states how big the step actually was at the ear (about 0.62 dB, not 0.9).
  - The second test room's label says its two sources' reverb differs by 1.2 dB and does not claim to know why.
  - The held-chord label's room figures are corrected (−6.5 dB, not −6.1).
  - Rests on NFR-1 L105 and L133. Seat 1 gives nothing; Seat 9 corrects its own figures.
  - Amends nothing.
- **M3-H:** whether a source in a corner loses reverb, and whether one source's reverb starts late, is settled in a small report-only phase (07e) before the binaural goldens freeze, not just before release.
  - Rests on NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L49/L101; no deadline (L174).
  - Seat 7 gives about one session before 08-3. It gets back no second golden round and no re-listening (up to about 11 h) next to the beta.
  - Amends nothing.

**NEEDS MAISARA:** none at present. If the interrogator's single check of M3-H returns anything but SURVIVES or SURVIVES WITH CORRECTIONS, M3-H goes to her as **case (a)**: the README reading "after 3 contested rounds". My recommendation is H4, for the PRD reasoning above.

**Person's action (not a question):** the sitting dates go in the brief before the seal.

**Files:**
- /home/user/makroof/docs/review/phase-07c-2b/10-interrogator-on-file9.md
- /home/user/makroof/docs/review/phase-07c-2b/9-decider-m3-r3.md
- /home/user/makroof/docs/review/phase-07c-2b/13-decider-l4-coverage.md
- /home/user/makroof/docs/review/phase-07c-2b/11-builder-l4-kit.md
- /home/user/makroof/docs/review/phase-07c-2b/14-seat1.md, 14-seat2.md, 14-seat7.md, 14-seat9.md
- /home/user/makroof/docs/review/phase-07c-2b/8-seat9.md, 6-decider-m3-r2.md, 2-decider-m3.md
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md
- /home/user/makroof/docs/phases/phase-07c-2b.md, phase-08-3.md, phase-08-4.md, phase-07d.md, phase-13-2.md
- /home/user/makroof/docs/BUILD_PLAN.md (§0 L13–61, AX47 L170, AX49 L172, §6 L415)
- /home/user/makroof/docs/board/README.md (L50–148)
- /home/user/makroof/docs/PRD.md
- /home/user/makroof/src/sim/Engine.cpp (L138–157)
- /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (L2694–2725, L2824–2835)

