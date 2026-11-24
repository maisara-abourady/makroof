
# 28: Decider on M3-H, fresh ruling, round 1 (convening). Phase-07c-2b; Maisara's hand-back of 2026-11-24

Read-only. The orchestrator saves this as `/home/user/makroof/docs/review/phase-07c-2b/28-decider-m3h.md`.

**State: CONVENE.** No decision this round. Her hand-back, "hand it back", was given against an option worded "re-run with all seats convened" (session brief `docs/sessions/2026-11-24-phase-07c-2b.md` L17–18). Under that wording, and under "when in doubt, convene", I convene all nine seats. Seats 2, 5 and 7 have already given cells, so their briefs are short follow-ups. Each of them must rate the variants it has not rated. Seat 7 must also turn its H4 range into one value. I will not read any cell from conditions this time. That was the TENSION MISREAD in file 20.

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. This round rests on no acoustic fact. The findings are builder measurements (file 5), and Kuttruff Eq. 5.42 is cited only as the indicative expectation the findings are measured against.

## PRD digest
- **For whom:** producers and DJs who are not spatial-audio experts (L17, L20).
- **Outcome:** a user places sources "anywhere in the scene" (FR-3D-5, L75) and hears it rendered correctly. Accuracy is a quality gate (L26; NFR-1, L105).
- **Hard bounds:**
  - NFR-8 (L112): "Any valid scene renders correctly; no environment-specific code paths". It is a v1 requirement.
  - FR-SIM-2: no preset-specific logic.
  - AX6 (BUILD_PLAN L129): an emitter ≥ 0.1 m from any surface is a valid scene, so both_corner is valid.
  - AX5: bit-identity holds only on the same OS and architecture.
  - The other AQ/AX defaults and her recorded decisions. The decision may not tune `src/sim` for a scene.
- **Ranking:** "Accuracy first" (L49, L101), ranked against CPU and latency.
- **Not bounded:** schedule. "no fixed v1 deadline" (L174, L55).
- **Verification:** every DSP behaviour is checked automatically, nothing is loosened to pass, goldens are never regenerated to pass, and a red is a stop.

## Restatement
**The matter:** where, and in what order against 07d scope 8, 08-3 item 15 and 08-4's golden freeze, the board rules the cause of three NFR-8 placement findings. The findings are from file 5 L21–23 and 14-seat9 §2:
- (a) `layout4_s1/both_corner`: L's 1 kHz tail is −6.20 / −6.12 dB at equal windows.
- (b) `layout4_s1/both_wall`: the t_mix,e onsets are 0.165 / 0.380 s.
- (c) `layout4_s0.7/default`: a −1.23 dB spread from the common onset.

**What depends on it:**
- which plan files exist (07e, or none);
- the §0 Depends-on text of 08-4;
- 07d scope 8's order;
- when 08-3 item 15's stimuli are built;
- whether a `src/sim` fix, if one is ruled, lands before the binaural goldens freeze.

**Options.** Every option rates in full, now and later:
- **H1:** an item in phase-13-2.
- **H2-c:** a named scope inside 07d, Lead Seat 2, exempt from 07d's split-off. It precedes 08-4 by 07d L79–80. It does not gate 08-3 item 15.
- **H2-cg** *(composed by me from Seat 2's §6 and Seat 5's §6 conditions)*: H2-c, plus three things:
  - it gates 08-3 item 15's stimulus build and 08-4;
  - the gate is on a committed ruling artifact (an interrogator SURVIVES under `docs/review/phase-07d/`), not on 07d `done`;
  - the item is placed before scope 8 in the file.
- **H3:** a report-only phase-07e that blocks all of Phase 08, with no ordering against 07d.
- **H3+G:** H3 with G1–G3.
- **H4:** phase-07e as written in file 17 §3. It is report-only, Lead Seat 2, and runs in parallel with 08-1 and 08-2. It gates only 08-3 item 15's stimulus build and 08-4's freeze. The gate sits in the Notes column and in prose. It has no order against 07d.
- **H4+G:** H4 with Seat 5's G1–G3 (22-seat5 §6) and the interrogator's R2:
  - **G1:** "07e `done` and the fix phase it rules, if any" goes into §0 row 08-4's *Depends on*.
  - **G2:** 07d scope 8 runs only after 07e is `done`, and after its fix phase, if any, is `done`. If 07d reaches scope 8 first, scope 8 splits to 07d-b. A fix that lands after a re-pin carries the re-pin in its own acceptance criteria: ≥ 6 green runs, a CHANGELOG reason and a §6 row.
  - **G3:** the 07e pytest asserts bit-identity on the OS and architecture that produced the values, and AX5's cross-architecture bound elsewhere.

## Convening table

| seat | status | reason (README row item touched) | brief |
|---|---|---|---|
| 1 | convened | "audibility of a detail, parameter or error"; "acceptance tests for other seats". How severe it is to ship a 6 dB corner deficit or a 0.215 s onset shift bears on H1's later debt. 08-3 item 15's ABX design is Seat 1's acceptance test, and its stimulus build is what is gated. This touches what the user hears (a priority seat). | B1 |
| 2 | convened (follow-up) | "late-tail statistics; image-source order; … simulator compute and recompute time; claims of physical accuracy". Lead of the investigation. | B2 |
| 3 | convened | "decay matching; early-reflection rendering". A fix to the t_mix,e rule or to AX22 moves the early/late handover that the renderer crossfades. The interrogator found "not required" correct in file 20; I convene under her instruction, and NOT MY MATTER is an acceptable answer. | B3 |
| 4 | convened | "the listening tests for these" (binaural). 08-3 is Seat 4-led. Item 15 and item 7's both-near binaural render (AX44) sit in its phase, and the 08-x binaural goldens are what freezes. | B4 |
| 5 | convened (follow-up) | "CI gates"; 08-4 is Seat 5-led; 07d scope 8's AX38 4c re-pin; the audio thread (a priority seat). | B5 |
| 6 | convened | "defaults … canvas metaphor and interaction". AX6 makes 0.1 m from a face the nearest valid placement. If drags push sources to the AX6 margin (phase-07 D1 push-away), a source dragged into a corner may land exactly at the finding's geometry. This touches the user's controls (a priority seat). | B6 |
| 7 | convened (follow-up) | "schedule and complexity cost of an option"; "what one founder can sustain" (a priority seat). | B7 |
| 8 | convened | "what a producer or sound designer does with the product … which features serve storytellers". Whether producers put sources in corners and next to walls (PA stacks, wall speakers) sets how often the findings are met in use. | B8 |
| 9 | convened | "preset validation against measured rooms"; "which geometry … choices are audible at a position". 12-2 presets with sources near faces; attribution of (c); real-room behaviour of a source at a boundary. | B9 |

## Briefs (the orchestrator passes each one on verbatim)

**Common to every brief.** Read:
- `docs/review/phase-07c-2b/28-decider-m3h.md` (this file: the options H1, H2-c, H2-cg, H3, H3+G, H4, H4+G, defined in "Restatement");
- `5-builder-tail-spread.md` L1–40;
- `17-decider-m3-r4.md` §3;
- `20-interrogator-on-file17.md`;
- `14-seat2.md`, `14-seat7.md`, `22-seat2.md`, `22-seat5.md`;
- PRD L49, L75, L101, L105, L112, L174;
- BUILD_PLAN §0 rows 07d, 08-3, 08-4, 12-2, and AX6 (L129);
- `docs/phases/phase-07d.md` L75–103, `phase-08-3.md` L3 and L58–87, `phase-08-4.md` L22–26.

Nothing in any option tunes `src/sim` (NFR-8). The question is only *where and when* the cause is ruled.

For **every** option, give: ranking, tension now / later (0–3) in your own words, what the later cell commits later phases to and when the evidence arrives, conditions of acceptance for any cell ≥ 2, and hand-offs. If no item of your row is touched, answer NOT MY MATTER and say which items you checked.

**B1 (Seat 1).**
- Rate all seven options on your row.
- Say whether the audibility of (a), a ~6 dB per-emitter 1 kHz tail deficit at equal times for a source 0.1 m from two walls and the ceiling, or of (b), one emitter's tail beginning 0.215 s earlier, changes any option's cell, especially H1's later. Say what test would settle it, and in which phase.
- Under H2-c (no 08-3 gate), 08-3 item 15's F3/F4 stimuli could be sealed before the cause is known. Rate what that does to your acceptance test (the M3-8 "void as evidence" clause).
- Your register entries are leads, not facts. Mark them.

**B2 (Seat 2, follow-up to 22-seat2).**
- Rate H2-cg, H3+G and H4+G. Your 22-seat2 cells stand for H1, H2-c, H3 and H4 unless you revise them.
- Answer Seat 5's hand-off (22-seat5 §7): would a likely fix (the AX40 estimator constant, or AX22's realised-k test at a near-face source) change restore work or only the level? If only the level, G2's re-pin debt falls to 0.
- Rate G2's clause "a fix landing after a re-pin carries the re-pin in its own acceptance criteria", which is written into 07e scope 5.
- Confirm or amend the 07e skeleton's sweep and finding texts (file 17 §3 "Scope" 1–3) as the text your seat will lead from.

**B3 (Seat 3).**
- Rate all seven options on your row.
- Say whether a 07e-ruled fix that moves t_mix,e or the AX22 handover touches a rendering commitment: the AX49 provisional tail and its fade [L_f, L_p), crossfades, coloration, or per-instance CPU. If it does, say whether any home makes that worse, now or later.

**B4 (Seat 4).**
- Rate all seven options on your row, and in particular what H4/H4+G's gate does to 08-3 (your phase): item 15's stimulus build waits on 07e. Item 7's both-near binaural render (listener and an emitter within 0.70 m of surfaces, AX44) does not.
- Say whether item 7's render, or the binaural vs omni ±1 dB parity, also needs to wait. If so, give the exact text, and say whether that changes your cells.
- Say whether the 08-x binaural goldens frozen in 08-4 are your cost or Seat 5's.

**B5 (Seat 5, follow-up to 22-seat5).**
- Rate H2-cg and H4+G as composed here. Your 0/1 for H4 with G1–G3 and 1/0 for H3 with G1–G3 stand unless you revise them, and confirm that H3+G here is your "H3 with G1–G3".
- Give the exact plan-editor text for G1 (the 08-4 *Depends on* clause) and G2 (the 07d scope 8 line, and the 07e scope 5 re-pin clause) as you would accept them.
- Say whether G3's "Linux x64" producer is fixed, or "the OS/architecture that produced them" is enough.
- Say whether H4+G holds 07d's scope 6 and 7 work. G2 orders only scope 8.

**B6 (Seat 6).**
- Rate all seven options on your row.
- Confirm from the code or the plan (cite it) the nearest placement the canvas and parameter map allow to a face, and whether a drag past the margin lands exactly at the AX6 limit of 0.1 m. If it does, the finding's geometry is where a dragged corner source ends up.
- Say whether that changes any option's later cell, through 11-2's canvas, the presets, or the defaults.

**B7 (Seat 7, follow-up to 14-seat7).**
- Give **one** value for H4's later cell. The interrogator's Q4 in file 20 asks for it: "0–1" cannot be summed.
- Do the same for H3's later cell, which you also gave as "0–1".
- Rate H2-c (as worded here, not your earlier "H2"), H2-cg, H3+G and H4+G.
- Answer Seat 5's hand-off: the cost of a 07d/07d-b split under G2, if 07d reaches scope 8 before 07e is `done`.

**B8 (Seat 8).**
- Rate all seven options on your row.
- Say whether placing sources at walls and corners is a routine producer move (a stage against a back wall, PA stacks in club corners, wall-mounted speakers), and so how often a user would meet (a) or (b).
- Say whether that changes any option's later cell.

**B9 (Seat 9).**
- Rate all seven options on your row.
- Say whether 12-2's starter presets (clubs, halls, domestic; PRD FR-3D-3) would place sources within ~0.5 m of one, two or three faces. Under H1, they would be built before the ruling.
- As a lead only, marked as such, give what real rooms do to a source's radiated power at a boundary or corner at 1 kHz. Seat 2 rated (a) "the wrong way" on this, [Hyp].
- Say whether (c)'s attribution needs anything a home must provide.

## Knowledge inventory (first pass)

| K | what must be known | source | status |
|---|---|---|---|
| K1 | finding values (a), (b), (c) | file 5 L14–37; 14-seat9 §2 | known (builder measurement) |
| K2 | 07d lands before 08-4's freeze; 08-3 has no 07d dependency; 08-4's internal order (benchmark → grouping → S8–S10 → freeze) | phase-07d L79–80; phase-08-3 L3; phase-08-4 L24–26 | known |
| K3 | 07d scope 8 pools runs only if the restore path is unchanged | phase-07d L94–96 | known |
| K4 | an emitter 0.1 m from a face is a valid scene | BUILD_PLAN AX6, L129 | known |
| K5 | bit-identity only per OS and architecture; the `python` CI job runs on 3 OSes | AX5 (L128); from the code, ci.yml L113–127 | known |
| K6 | the AX22 fallback moves the handover only when the realised-k test fails | from the code, Engine.cpp L138–157 (file 17 K15) | known |
| K7 | whether a likely fix changes restore work or only the level (G2's debt) | Seat 2, B2 | uninformed (a seat's own-cost claim is pending) |
| K8 | whether a canvas drag lands at exactly 0.1 m from a face | Seat 6, B6 (code citation) | uninformed |
| K9 | every seat's cells for all seven options; Seat 7's single H4 later value | this round | uninformed |
| K10 | 12-2 follows 07e under H4 (12-2 → 11 → 09 → 08 → 08-4) | file 20 "Phase order"; §0 | known |
| K11 | a source's radiated power at a boundary or corner, 1 kHz, 0.1 m | researcher (below); Seat 9 lead | uninformed. **Not load-bearing for the home**: every pre-freeze option leaves the physics ruling to 07e or 07d's loop. It feeds that loop. Run it in parallel so 07e starts informed. |

**Record correction (not a decision):** file 24's sum for "H4 + G1–G3" is wrong.
- Working, from its own cells: S2 1/1 = 2; S5 0/1 = 1; S7 1/(0–1) = 1–2. The total is **4–5**, not "3–4".
- Its H3 row (4–5 with Seat 5 at 1/1, or 3–4 with G1–G3) has the same issue. With Seat 5 1/1 the total is 2 + 2 + (1–2) = 5–6. With G1–G3 (Seat 5 1/0) it is 2 + 1 + (1–2) = 4–5.
- The ranking file 24 showed (H4 + G lowest) survives the correction, but the decision round will recompute every sum from this round's cells.

## RESEARCH NEEDED (parallel, non-blocking for the home)
**R-H1.** What does the corpus (Kuttruff, Vorländer) or a verified external source state about a point source's radiated sound power, or its reverberant level, when placed at 0.1 m from one, two and three rigid faces, at 1 kHz (ka with a = 0.1 m and λ ≈ 0.343 m)? I need:
- the factor relative to free field;
- the frequency range where it holds;
- the condition on distance relative to wavelength.

What it changes: it does not change the home. It sets whether 07e's (a) verdict can be "breach" on physics, because a boundary source radiating more power makes a 6.2 dB deficit point the wrong way, as Seat 2's [Hyp] says. Cite the equation or section numbers as they appear.

## Summary

| id | decision | state | worst-off seat (cell) | sum | confidence | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| M3-H | — | convening (all nine seats; Seats 2, 5, 7 as follow-ups) | — | — | — | NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L49/L101, L55/L174 | Kuttruff Eq. 5.42 (indicative, the findings only) | — |

**Challenges to settled decisions:** none.

**Decided for Maisara:** nothing this round. Her hand-back is applied as an instruction: the item is re-run with every seat convened, and her hand-back supersedes the README 3(a) round count for this item. The decision round will give the acceptance check against NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L49/L101 and L55/L174, with every surviving option. If H4+G wins, it will give the plan-editor texts listed in the task: 07e file, §0 rows 07e and 08-4 Depends-on (G1), the 08-3 note, the 07d scope 8 line (G2), phase-08-4, the 08-3 item 15 sentence, the run sheet C-b bullet (with R1), the 07c-2b Out-of-scope line, and the §6 row.

**NEEDS MAISARA:** none.

**Files read:**
- /home/user/makroof/docs/review/phase-07c-2b/24-m3h-for-maisara.md, 17-decider-m3-r4.md, 20-interrogator-on-file17.md, 14-seat2.md, 14-seat7.md, 22-seat2.md, 22-seat5.md, 5-builder-tail-spread.md (L1–40)
- /home/user/makroof/docs/sessions/2026-11-24-phase-07c-2b.md (L14–18)
- /home/user/makroof/docs/board/README.md (L45–148)
- /home/user/makroof/docs/PRD.md (full)
- /home/user/makroof/docs/BUILD_PLAN.md (§0 L30–59; AX5 L128; AX6 L129)
- /home/user/makroof/docs/phases/phase-07d.md (full), phase-08-3.md (L1–90), phase-08-4.md (L1–40), phase-07c-2b.md (L192–193, via search)
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md (L124–135)
- /home/user/makroof/.github/workflows/ci.yml (L105–134)
- /home/user/makroof/docs/corpus/SOURCE_COMMIT
