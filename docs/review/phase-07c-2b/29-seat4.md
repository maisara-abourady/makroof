# 29-seat4: Seat 4 on M3-H (brief B4)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 4 POSITION (brief B4, M3-H re-run; for docs/review/phase-07c-2b/29-seat4.md, read-only, the orchestrator saves it)

**1. Reading.** Where and when the three NFR-8 placement findings get their cause ruled, judged on my row only. My row covers 08-3 (Lead Seat 4): item 15's binaural ABX record, item 7's both-near render, AC6 parity, and the content of the binaural goldens that freeze in 08-4. Cues from my persona: "validating a chain" (a record is worth only the engine it was heard on), "level and tone parity", and failure-library row "judging on an unsettled reference".

**2. Ranking**
- **H4+G: prefer.**
- **H4: can live with.**
- **H3+G and H3: can live with.**
- **H2-cg: can live with,** if its gate includes the fix phase (§6).
- **H2-c: can live with, at a major later cost.**
- **H1: can live with, at a major later cost. Ranked last.**

No option is veto-grade. None of them removes the listening test behind a delivery claim; some only risk voiding it.

**3 and 4. Tension now / later**

| option | now | later | what the later cell commits 08-3/08-4 to; when the evidence arrives |
|---|---|---|---|
| H1 | 0 | **2** | Item 15's F3/F4 stimuli are sealed and heard, and the binaural goldens are frozen, before the cause is known. A 13-2 fix fires M3-8: F3/F4 are void and re-heard (2.6–5.0 h, 08-3 L81–82), and the cross-chain comparison is void unless omni is rerun (about 3 h, 14-seat7 §4). 08-3's checklist verdicts were heard on the pre-fix engine. Evidence arrives at 13-2. |
| H2-c | 0 | **2** | 08-3 does not depend on 07d (08-3 L3), so the item 15 stimuli can be sealed before the ruling. The debt is the same M3-8 void as H1, but it arrives before the freeze. |
| H2-cg | 0 | **2 as worded, 1 with the fix clause** | The gate is on "a committed ruling artifact". If that ruling is "breach, fix needed", the stimuli could be built after the ruling but before the fix lands, and M3-8 voids them. H4's wording ("and the fix phase it rules, if any") closes this. A second point belongs to Seat 5: an artifact gate is not a §0 status, so an 08-3 session cannot check it under CLAUDE.md step 3. |
| H3 / H3+G | **1** | 0 | It holds 08-1 (converter) and 08-2 (early part), my phases, for no cue reason: neither reads tail state. Everything in 08 is then built on the settled engine. |
| H4 | 0 | **1** | The residual: if 07e rules a long fix phase, item 15 waits and 08-3 may split to 08-3b. 08-3's checklist (L1, L3, L4, colour) may also be heard on the pre-fix engine. An AX40-constant fix moves every tail's level, which can shift "outside / inside" verdicts, because D/R is a room cue. Evidence arrives with 07e's ruling. |
| H4+G | 0 | **1** | G1–G3 touch only Seats 5 and 2. G1 helps a little (08-4 cannot freeze before the fix). My residual is the same as H4's. |

**What H4's gate does to 08-3.** It defers one build step, item 15's stimuli. 07e is size S and runs in parallel with 08-1 and 08-2 (each size M). So 07e alone should be done before 08-3 reaches item 15 [Inferred]. Only a ruled fix phase that is still running at that point delays item 15.

**Item 7 and parity: neither needs to wait.**
- **Item 7's both-near render** is a listening-pack artifact, regenerated on every CI run, so a fix regenerates it automatically. AX44 already says "No accuracy claim is made where both ends are flagged". No sealed record or claim rests on it.
- **AC6 parity (±1 dB)** is an automated assertion, re-run on every build, including any fix phase's CI. E_b is read via `TailMatch` and is bit-identical across modes and ears (AX44, AX39). An AX40 or AX22 fix therefore moves omni and binaural together, and parity is re-asserted, not frozen.
- **Proposed text (08-3 item 7, and the checklist header):** "If heard before phase-07e is `done` (and the fix phase it rules, if any), the checklist verdicts and the both-near render note are recorded 'provisional: engine before the 07e ruling'. A level or dryness remark on a near-face render goes to 07e (or, once 07e is `done`, to the board) as an NFR-8 candidate, never to the HRTF or the headphones." This follows the existing "provisional if 08-4 introduces grouping" clause (D-PS2). **It does not change my cells:** the re-hear it implies is the debt my 1 already counts.

**Goldens: whose cost?** What the 08-x binaural goldens assert (parity, per-ear T30, coherence) is mine. Freezing them (the CI gate, the order against 08-4's benchmark, a second golden round) is Seat 5's, and the session cost is Seat 7's. Because E_b is shared across modes, a post-freeze fix re-renders omni and binaural together and leaves parity intact. So **my cost from a late fix is the listening record (item 15 and the checklist), not the goldens.**

**5. Evidence**
- 08-3 has no 07d dependency: phase-08-3 L3 [plan].
- Item 15 timings and the M3-8 rebuild clause: phase-08-3 L80–87 [plan].
- Omni rerun of about 3 h: 14-seat7 §4 [Hyp, Seat 7].
- E_b shared and bit-identical; "no accuracy claim" at both-near: BUILD_PLAN AX44 [plan].
- AC6 runs over `tests/scenes/valid/` only, and no layout4 scene is in it [from the code, directory listing].
- That item 15 (i) is already "chain comparison only" at the listener 0.1 m from a face: 08-3 L63–64.
- No new acoustic fact is used; the corpus was not opened.

**6. Conditions of acceptance**
- **H1, from 2 to 1:** Seat 7's deferral clause (the cause is ruled before item 15's build and 08-4).
- **H2-c, from 2 to 1:** gate item 15's stimulus build (this is H2-cg).
- **H2-cg, from 2 to 1:** the gate reads "the committed ruling artifact, and the fix phase it rules, if any, `done`".
- **Offered for every option (no cell change):** add `layout4_s1/both_corner` and `both_wall` to AC6's parity cases (built as `abx_kit.py make_scene` builds them). Parity would then be asserted at the geometry where a fix moves the early/late handover. There, energy shifts between the HRTF-rendered images and the DF-equalised tail.

**7. Hand-offs**
- **Seat 5:** whether an artifact gate is checkable at an 08-3/08-4 session start; G1's text.
- **Seat 7:** the cost of an 08-3b split if a fix phase holds item 15.
- **Seat 1:** whether a 6 dB corner-tail deficit is audible; this sets H1's severity.
- **Researcher (K11):** AX44 already cites a receiver-side near-wall rise (up to +3 dB at a rigid wall, Kuttruff Eq. 2.50, §8.7). Whether a source-side counterpart holds at 0.1 m and 1 kHz is for the researcher and Seat 9, not me.

**8. Premortem.** Suppose H2-c is chosen without the gate. Item 15's F3/F4 stimuli are sealed, then 07d's loop rules an AX40 fix. Maisara's 2.6–5.0 h of binaural ABX is voided by M3-8, and the 08-3 reviewer finds the cross-chain comparison recorded void.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/28-decider-m3h.md, 5-builder-tail-spread.md (L1–40), 17-decider-m3-r4.md, 20-interrogator-on-file17.md, 14-seat2.md, 14-seat7.md, 22-seat2.md, 22-seat5.md
- /home/user/makroof/docs/PRD.md (L45–112)
- /home/user/makroof/docs/BUILD_PLAN.md (§0 L38–43, L55; AX44 L167)
- /home/user/makroof/docs/phases/phase-08-3.md (full), phase-08-4.md (L1–40), phase-07d.md (L72–105)
- the /home/user/makroof/tests/scenes/valid/ directory listing

Not read: BUILD_PLAN AX6 (L129; the line was too long to display, so I relied on the decider's digest). Not opened: the corpus.
