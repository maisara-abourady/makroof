# 14-seat7: Seat 7 on the corner/onset findings' home

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 7 POSITION

**1. Reading.** Where Seat 2's ruling on the two NFR-8 findings should sit: both_corner, where the corner emitter's tail is 6.2 dB low at equal windows, and both_wall, where the onset is 0.165 s against 0.380 s. The question is what each home costs in sessions, golden rounds and Maisara's listening hours. Cues from my §4/§11: "cheap now, borrowed from later phases"; lateness costs more than doing it early (A7); "support and installers come before the next algorithm" (R1); and a shipped "corner source loses its reverb" bug would be a trust withdrawal.

**2. Ranking**
- **H4 (my own option): prefer.** Split the cause ruling from the fix. A small investigation phase, "07e", does a builder measurement plus a board loop, with no `src/sim` change. It depends on 07c-2b `done` and runs in parallel with 08-1 and 08-2. It gates only two things: the build of the 08-3 ABX stimuli and 08-4's golden freeze. Any fix it calls for lands before 08-4 and shares that freeze.
- **H3 (dedicated phase before 08, blocking all of 08): can live with.**
- **H2 (an earlier home inside an existing phase before 08's freeze, e.g. 07d or 08-x): can live with.**
- **H1 (phase-13-2): can live with, ranked last.**

**3. Tension now**
- **H4: 1.** About 1 session `[Hyp]`, off the critical path.
- **H3: 1.** About 1 session `[Hyp]`, and it holds up all of Phase 08.
- **H2: 1.** It adds scope to a phase that is already S–M. 07d is mostly a Seat 5 load phase, so the item is likely to be split off again: +1 session `[Hyp]`.
- **H1: 0.** Nothing is spent now.

**4. Tension later (the debt)**
- **H1: 2.**
  - A fix at 13-2 is a second golden round after Phase 08's freeze. It would re-render the 08-x binaural goldens.
  - If the cause is the AX40 estimator, the fix also reopens the 560 case-band agreement golden. 05h's round alone ran three extension rounds over several sessions (BUILD_PLAN §0 row 05h).
  - It fires M3-8, which rebuilds the sealed scenes. Moving L's onset drops S-W's share from 0.667 to about 0.29 (file 5, fact 1). That rescopes 3.3–5.8 h of 07c-2b listening and 2.6–5.0 h at 08-3. Re-hearing those is up to about 11 h of Maisara's time `[Inferred from file 9 §5]`.
  - The 12-2 presets are built before the ruling (interrogator file 10, row "corner/debt"), so any preset with a source near a face has to be re-checked.
  - All of this lands one phase before 13-5's beta, on the release path. That is where "ship it as a known issue" becomes tempting (A7: lateness under pressure).
  - Undo cost: about one phase of rework. Evidence arrives at 13-2, too late to reorder anything.
- **H2: 1.** A fix shares 08-4's freeze. If the item lands after 08-3's stimuli are built, M3-8 still voids the cross-chain comparison unless omni is rerun (about 3 h).
- **H3: 0–1.** One golden round at most, shared with 08-4. 08-3 is built on the settled engine. The 1 is the risk that the investigation stalls and holds all of 08.
- **H4: 0–1.** Same as H3, without blocking 08-1 and 08-2. The residual 1 is a fix that turns out to need more than one session, which would then hold 08-4.

**5. Evidence**
- Measured spreads and onsets: file 5, facts 1–2, as builder measurements.
- Phase order and freeze rule: BUILD_PLAN §0 rows 08, 12-2 and 13-2. The freeze waits on 07c-2b `done` (D-W3).
- That a 13-2 fix needs a second golden round: file 9 §4, the decider's own strongest objection, and file 10 C9.
- Session and round counts: `[Hyp]`, from row 05h's history. I have no incident on golden-round cost (my §18). The **researcher** can't verify these; the builder can, by costing a dry-run golden round.
- Platform lateness compounding: A7 and P1 `[Observed]`.
- PRD L55/L174 put no deadline on the schedule. My cost here is the founder's hours and the beta date, not a contract date.

**6. Conditions of acceptance**
- **H1, from 2/later to 1:** do the cause ruling (no fix) before 08-4's freeze and before 08-3's stimuli are built. Only an agreed fix that costs more than one session may wait for 13-2. Write it into 13-5's beta gate as a release blocker under NFR-8, so it cannot become a known issue. That is H4 with a deferral clause.
- **H2, from 1 to 0:** home it as its own sub-phase (H4) rather than adding it to 07d's load scope.

**7. Hand-offs**
- **Seat 2:** estimator or image-source set. The answer decides whether a fix touches the AX43 agreement golden, which is the expensive case.
- **Seat 1:** whether a 6 dB tail deficit at a corner source is audible. That sets how bad shipping it would be.
- **Seat 9:** whether 12-2 presets place sources within about 0.1–0.5 m of two faces.
- **Seat 6:** whether the canvas makes corner placement easy or a default (FR-3D-5).
- **Seat 5:** mechanics of holding 08-4's freeze on 07e.

**8. Premortem.** The item sits at 13-2, the cause turns out to be the estimator, and the fix costs a full golden round plus re-listening just before the beta. Under schedule pressure it ships as a known issue. The first to notice is a producer who drags a source into a corner, hears the room go dry, and posts about it.

Note: I am read-only, so this file is not saved yet. The orchestrator saves it as /home/user/makroof/docs/review/phase-07c-2b/14-seat7.md.
