SEAT 6 POSITION (phase 07c-2b, AX49 L4: how to build the stimuli, or whether to defer L4; convened by interrogator file 11)

**1. Reading.** The provisional tail plays at the start of every reopened project that has a tail, until the handover finishes. Record (h) puts that window at up to 9.51 s (Windows, 8 instances). So it falls inside the first minute of every session. L4 is the only test of whether a producer hears, in that window, a tail that stops short.

Cues it triggers:
- S3 (a change the engine makes heavily while audio runs);
- W4 / failure-library row "automatic helper": a change the user did not cause, arriving after they stopped;
- S9 (silence is unmeasured): no result means an unread reversal, not "inaudible".

Fact from the plan: Phase 11 requires "settling" on every instance "building or crossfading", project load included (BUILD_PLAN L365). But `settling()` currently leaves out a running crossfade (07c-1b follow-up L124). So the indicator clears before the handover's 30 ms crossfade. Seat 3's ghost (the exact tail re-onsetting at about −19 dB after the provisional has gone silent) lands right after "settling" clears. That is my W4 failure exactly.

**2. Ranking.**
- **L-a: prefer.** One chain gives one result that describes what the plugin plays (Seat 3 condition 7). The flag can later take a handover time and the remedy variants, so the ghost can be heard without another round of tooling.
- **L-b: can live with.**
- **L-c: can live with, only under the conditions in point 6.** If the date can fall after Phase 11 freezes the settling semantics, or after the 13 beta, I cannot live with it.

**3. Tension now.**
- **L-a: 0.** Producers hear no difference: the flag is off by default and the plugin cannot reach it (Seat 5's guard).
- **L-b: 1.** The result describes what the plugin plays only once parity with the plugin's path is shown.
- **L-c: 1.** Nothing ships before Phase 13. But every first-minute design downstream rests on an untested event.

**4. Tension later (debt).**
- **L-a: 1.**
  - What it commits: on every option, the ghost and the indicator-clears-before-handover problem stay unheard. L-a is the cheapest way to close that later.
  - Undo cost: deleting one flag.
  - Evidence arrives at L4 and at the Phase 11 checklist.
- **L-b: 1.** Same debt, plus a second render path that can drift from the plugin (Seats 3 and 5).
- **L-c: 2.**
  - What it commits: if L4 detects the cut, the fix is to raise 0.312 or lengthen the fade (Seats 1 and 2). That makes L_p longer at the rated corner, which makes the load wait longer. The load wait is already 9.51 s against the 5 s line.
  - So 07d's remedy trades my two first-minute measures against each other: time until the room is right at load, and a gated-sounding tail. Making that trade without L4's data is choosing by rationale (W3).
  - Undo cost: a board round plus 07d rework (Seats 2, 3 and 7). If the date slips past the 13 beta, the undo is first-minute trust that producers have already spent.
  - Evidence arrives at L4, whenever it runs.

**5. Evidence.**
- The provisional plays at every load: AX49 ("Every load of a scene with a tail therefore starts with a tail") [Obs].
- 9.51 s Windows load: AX49, CI run 43242209571 [Obs].
- Settling covers crossfading in Phase 11, but the code excludes it: BUILD_PLAN L365; phase-07c-1b L124 [Obs, from the plan].
- Ghost at about −19 dB: Seat 3 (9-seat3-l4 §5) [Hyp until printed].
- A producer recognising a tail cut as "gated reverb": Seat 1, citing Gibson [corpus, via Seat 1].
- That a producer perceives the ghost as "the room changed on its own": [Hyp]. No incident in my persona covers reverb re-onset. W4 (MIR Natural Volume) is the nearest incident with the same structure.

**6. Conditions of acceptance.**
- **L-c, to lower later 2 → 1:**
  - a named date before 07d chooses its 0.312 or fade candidates (as Seats 1, 2, 3 and 5 ask);
  - L4 runs before Phase 11 fixes what "settling" means at load.
- **All options (my own conditions; they hold L-a at 0/1 and L-b at 1/1):**
  1. Adopt Seat 3's ghost print: re-onset level per band at release + L_p + {0, 1, 2, 5} s. Write it into the D-C9 debt register with a Seat 6 line: "settling must stay lit through the handover crossfade."
  2. The L-a flag accepts a handover time, so that a realistic interim-then-handover render of the L4 scene goes into the listening pack. It is unscored and labelled. Maisara can then hear the ghost before Seat 1 rules whether it needs its own ABX.
  3. A non-detection is recorded with its power (0.63 at p = 0.75) and with Seat 9's cut-depth scope. It is never worded as "inaudible" (carried from my file-10 condition 2).

**7. Hand-offs.**
- Seat 1: whether the ghost needs its own ABX.
- Seat 2 / Seat 9: the scene. From the user's side, a producer's large hard-room preset looks more like Seat 2's stone-box variant (cut at about −19 dB) than the 100 m cube (about −28 dB). Seat 9's scope warning applies.
- Seat 5: the flag guard, and fixing `settling()` to include the crossfade.
- Seat 7: the hours.
- Phase 11 builder: the settling semantics at load.

**8. Premortem.** L4 is deferred and 07d raises the fade by rationale. A producer reopens a church-sized project, plays a pad and stops it. The tail stops short, "settling" clears, then the tail breathes back in. They stop trusting the room. Maisara notices first, at the Phase 11 reopen-project checklist item.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/8-decider-scene.md
- /home/user/makroof/docs/review/phase-07c-2b/11-interrogator-on-file8.md
- /home/user/makroof/docs/review/phase-07c-2b/9-seat{1,2,3,5,7,9}-l4.md
- /home/user/makroof/docs/review/phase-07c-2b/1-seat6.md
- /home/user/makroof/docs/BUILD_PLAN.md (AX48 L171, AX49 L172, Phase 11 L358–365)
- /home/user/makroof/docs/phases/phase-07c-1b.md (L118–127)
