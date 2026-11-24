SEAT 7 POSITION (phase 07c-2b, AX49 L4 stimuli; decider file 8, "AX49 L4: CONVENE")

**1. Reading.** The question is how the L4 stimuli (the provisional tail from `StagedBuild::assembleProvisional`, T60_max 8 s) get built, or whether L4 leaves this phase. Two of my cues apply:
- "The founder's hour is the scarcest input": Maisara's listening hours and sittings.
- "Cheap now, borrowed from later phases": the class (c) round reads AX49's L4 reversal, and the W pin waits on class (c) (phase-07c-2b scope 3–6; Risks).

Nothing here touches price, licence or public wording. Run sheet §6 already rules out public copy from any ABX result. So nothing is veto-grade for me.

**2. Ranking**
1. **L-b (JUCE-free harness in `tests/`): prefer.** L4 can be built and sealed this session and heard in E's second sitting. It needs no AX49 amendment and no /fix-plan cycle on the critical path.
2. **L-a (validation-only `render_cli` flag): prefer, tied on Maisara's hours.** It goes through the kit's existing chain (`abx_kit.py` → `render_cli`). It costs one more /fix-plan plus an AX49 amendment, which is orchestrator time, not hers.
3. **L-c (L4 handed to a later phase by a date): can live with, only under the conditions in section 6.**

**3. Tension now**
- **L-b: 1.** Builder time only. Maisara's L4 block (16 trials + 6 anchors) rides on a sitting already planned.
- **L-a: 1.** As L-b, plus one /fix-plan round before the seal.
- **L-c: 1.** It saves the block this session. It still costs a board re-plan, and class (c) has to be decided without the L4 reading or wait for it.

**4. Tension later (the debt)**
- **L-a: 1.** It commits `render_cli` to carrying a provisional path behind a flag. Undoing it is a flag deletion. A test is already planned to show `src/plugin` never reaches the flag. Evidence comes from that test and AX5 determinism in CI (Seat 5's matter).
- **L-b: 1.** It commits a harness that has to stay in step with `StagedBuild`. Undoing it means deleting test code. Evidence comes from the seal's pre-seal checks.
- **L-c: 2.** Maisara needs a separate dated session in another phase, with setup, anchors and warm-up again: a fresh sitting rather than one block added to an existing one. That is the "blocked (awaiting ABX)" pattern (Risks) moved into 07d or Phase 10.
  - Worse, class (c) and the W pin would be decided without L4's reversal.
  - If L4 later detects, the undo is the one I priced in file 7 (α): a board round, about 2 h of confirmatory ABX, a W_max re-pin and a second golden round with /fix-plan. That is a phase-sized piece of rework.
  - If the named date slips past the 08-4 freeze, that undo lands on the Phase 08 goldens or Phase 13, and the rating rises to 3.

**5. Evidence**
- AX49's reversal is already homed in 07d (D-B4). That comes from BUILD_PLAN §0 row 07c-1b `[Observed]`.
- That class (c) reads L4 and the W pin waits on class (c) comes from phase-07c-2b scope 3–6 and Risks `[Observed]`.
- The undo cost comes from file 5 Q5 and D-M3h 2(d), as restated in my file 7 `[Observed]`.
- E is 2.39 h, split into two sittings of about 1.2 h (file 8, M3-C 8) `[Observed]`.
- L4's own duration is not yet measured. K6 has not been run on L4 stimuli, so "about one block" is `[Hyp]`. I invent no number.
- That a separate later sitting costs more than a block added to an existing one is `[Hyp]`. No incident in my persona covers scheduling listening sessions.

**6. Conditions of acceptance**
- **L-a and L-b (both kept at 1):**
  - K6 redone with L4's measured time.
  - L4 placed as its own block, with its own anchor, in E's second sitting, if that sitting plus L4 stays within K6's 2 h one-sitting limit. Otherwise a third dated sitting goes into the brief before the seal.
- **L-c, later 2 → 1:** all three of these must hold.
  - Class (c) and the W pin wait for L4's result. If they don't wait, the decision records them as conditional on L4, with the re-pin path pre-registered.
  - The named date falls before the 08-4 freeze, and before 07d where AX49's reversal already lives.
  - L4's session is dated in the brief now, not at handover.

  If class (c) proceeds unconditionally without L4, the rating stays at 2. If the date can fall after the 08-4 freeze, it rises to 3.

**7. Hand-offs**
- `src/cli` flag safety, determinism, whether `src/plugin` can reach it, and whether `render_cli` is ever distributed: Seat 5.
- The held-chord design, block order, fatigue and M3-T: Seat 1.
- The L4 scene, L_p and L: Seat 2. Its label: Seat 9.
- The provisional tail's handover: Seat 3.
- Whether Maisara can sit a third session: Maisara, as a person's action.

**8. Premortem.** If L-c is chosen and class (c) and the W pin go ahead without L4, then L4 detects in 07d. W gets re-pinned and the goldens go through a second round after Phase 08 has started building on them. The steward sees it first when a "second golden round" appears in the 07d brief.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/8-decider-scene.md
- /home/user/makroof/docs/review/phase-07c-2b/7-seat7.md
- /home/user/makroof/docs/phases/phase-07c-2b.md
- /home/user/makroof/docs/BUILD_PLAN.md (§0 rows 07c-1b, 07c-2b, 07d, 10, 13)
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md (§7)
