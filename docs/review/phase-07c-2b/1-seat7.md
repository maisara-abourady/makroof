# 1-seat7: Seat 7 (founder) on M3, V1–V4 and α (phase-07c-2b, round 1)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 7 POSITION

**1. Reading.** M3 decides how much of Maisara's listening sits on 07c-2b's critical path, and whether the most sensitive scene is heard before or after the W_max pin and golden round (07c-2b O4–O8). Everything from O10 onward waits on the ABX, and 07c-2b must be done before the Phase 13 beta. The cues from my §4 and §11: "the founder's hour is the scarcest input"; "cheap now, borrowed from later phases"; and the trust withdrawal of a post-release "reverb jumps" bug.

**An assumption has fallen.** In file 30 I estimated 1 to 1.5 h per scene `[Hyp]`. K6 (file 32) measures about 2 h, with a range of 1.3–2.8 h, and 0.6–1.5 h if 0.9 dB is not detected. So two scenes "in one sitting" means about 4 h (2.6–5.6 h). That is beyond K6's 2 h sitting. My file-30 condition "same sitting" no longer holds as written (see §6).

**Cost units** (K6 for S-A; the AX49 L4 ABX is 16 trials, about 15–30 min `[Hyp]`, timed from K6's per-trial pace):
- V1: 07c-2b about 4.3 h (2.9–5.9 h), 08-3 about 4 h. Total about 8 h.
- V2: 07c-2b about 2.3 h, 08-3 about 4 h. Total about 6 h.
- V3: as V2, but layout 5's T30 of 2.56 s makes the noise stimuli about 30% longer. Each layout-5 scene is about 2.5 h `[Inferred]`, from K6's formula (3 gaps of ceil(T30), plus the IR length).
- V4: 07c-2b about 2.3 h, or about 1.2 h if S-A's ΔG of 0.045 dB is not detected at 0.9 dB. 08-3 about 4 h.

**2. Ranking.**
1. **V2.** *Prefer.* It costs the fewest hours now, and S-W is heard first. S-W is the wettest qualifying scene (both_wall, share 0.667, ΔG 0.62 dB, now that K5 has cleared it), so if any detection is coming, it most likely comes in 07c-2b, before the pin and the golden round.
2. **V3.** *Can live with.* It is V2's logic with a more sensitive pool (emitter_wall 0.869). But it adds a /fix-plan cycle and about 30% more listening per scene. File 34's T-a debt also fails on layout 5, so a Q5 rerun or reseal could come before the sitting.
3. **V4.** *Can live with.* It is cheapest now. But neither of its scenes is the sensitive one (S-A share 0.046; S-B\* 0.032–0.040). A real audible step on wall-placed sources would then most likely surface after release, through customers.
4. **V1.** *Can live with*, ranked last. It doubles the gated listening now, on the two least sensitive scenes, and S-W is first heard at 08-3, after the golden round. It pays the most and still leaves the late risk in place.

**3. Tension now.**
- V2: **1.** About 2.3 h gating O4–O8, plus the robust `click_check` builder time before the seal.
- V3: **1.** About 2.8 h, plus a /fix-plan to AX47 (board time, not Maisara's).
- V4: **0.** About 1.2–2.3 h.
- V1: **2.** About 4.3 h gating the whole remainder of 07c-2b. At K6's typical pace that is two or three sittings, so the person's calendar sets the phase's end date.

**4. Tension later (the debt).**
- **V2: 1.** 08-3 needs about 4 h, in two sittings. S-B\* is the only new class at 08-3, and its ΔG is below S-A's. A post-pin reversal is possible but the least likely of the four. Undoing one costs O4–O8 again, a phase of rework the size of S–M. The evidence arrives at 08-3, from S-B\*.
- **V3: 1.** Same as V2, at about 5 h at 08-3.
- **V4: 2.** 08-3 needs about 4 h. If the 1 dB bound is audible where the tail share is large, no scheduled test finds it. The finder is a mixer after release, or Maisara on L4. The cost is a patch, a re-pin and a golden round, plus a trust withdrawal (R1, R3).
- **V1: 2.** About 4 h at 08-3, and S-W's first run comes after the golden round. That is the most likely post-pin reversal of the four, so a phase of rework is likely on top of about 8 h of listening.

**α: unsplit.** *Prefer* unsplit; *can live with* split.
- **Now:** both 0. Neither changes the hours.
- **Later:** unsplit **1**, split **1**.
  - Unsplit: the union false-reversal rate is ≤ 0.098–0.147. If the false detection lands at 08-3, it costs a re-pin and a golden round, and we catch it ourselves.
  - Split: noise power drops from 0.63 to 0.405 (file 31, answer 4), so a real step is missed more often. A miss is caught by customers.
- Trust ranks above runway in my §2, so I would rather pay the error we find ourselves.

**5. Evidence.**
- K6 hours, stimulus lengths and pace table: file 32 `[Observed]` and `[Hyp]` (its pace assumptions).
- Tail share and ΔG per scene: file 29, table and fact 5 `[Observed]`. K5 cleared both scenes: file 32.
- Bonferroni powers: file 31, answer 4.
- 07c-2b's gating and the before-beta rule: phase-07c-2b.md, Scope, items 3–8.
- Layout-5 stimulus length: from K6's formula `[Inferred]`.
- The L4 ABX time is `[Hyp]`. I want the builder to time it the way K6 timed the main ABX.
- My persona has no incident on validation scheduling; the hour costs are arithmetic, not a record.

**6. Conditions of acceptance.**
- **V1, to 1:** the 07c-2b pair becomes S-W plus S-B\*, so the sensitive scene comes before the pin.
- **V4, later to 1:** S-W is also run (omni or binaural) before the golden round, or at the latest before the Phase 13 beta, with the trigger written into BUILD_PLAN row 08.
- **All options at 08-3** (this replaces my "same sitting"): two sittings of ≤ 2 h each, on the same or consecutive days. Setup and familiarisation are paid once per chain. The dates go in the 08-3 brief before 08-3 starts.
- **Unsplit:** the record states the union rate.

**7. Hand-offs.**
- The S-W pick, S-B\* at 0.7 or 0.9, and whether S-B\* earns a family: Seat 1 and Seat 9.
- Option to weigh (`[Hyp]`): if any 08-3 detection needs a confirmation block on a fresh seal before the rework, the false-rework rate falls to about 0.049² at about 1 h of listening, paid only when triggered. Seats 1 and 5 decide this.
- Whether Maisara can give about 6–8 h across two phases, or needs a named listener: Maisara (item 16).
- What a 0.5 dB reversal costs in load time: Seats 5 and 6.

**8. Premortem.** If the board picks V1 or V4, a 0.9 dB step on a wall-placed source goes undetected until after the golden round. Maisara then pays the hours and a second W_max round in Phase 08, or a mixer reports it after the beta.

Files read:
- /home/user/makroof/docs/review/phase-07c-2/28-interrogator-on-file27.md
- /home/user/makroof/docs/review/phase-07c-2/29-k4-candidates.md
- /home/user/makroof/docs/review/phase-07c-2/30-seat7.md
- /home/user/makroof/docs/review/phase-07c-2/31-decider-abx-r4.md
- /home/user/makroof/docs/review/phase-07c-2/32-k5-k6-clicks-session.md
- /home/user/makroof/docs/review/phase-07c-2/34-decider-m1-m2-final.md
- /home/user/makroof/docs/phases/phase-07c-2b.md

To be saved as /home/user/makroof/docs/review/phase-07c-2b/1-seat7.md.
