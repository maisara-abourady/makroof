# Seat 6 — D-H3 (b)

SEAT 6 POSITION

**1. Reading.** Whether my requirement AX44 Seat 6 (ii) is broken by U at the default placement of two contract-limits fixtures, and what Phase 11/12 do when an outdoor preset meets the same cause. Cues: "a default that is not the most realistic state" (criterion 1) and "automatic helper fires on unrelated edits / cries wolf" (W3, W4).

**Scope of "valid fixture" in my (ii).** My words (phase-05b2 file 30, condition (ii); file 34 L186) said "valid fixture or Phase 12 preset", and the test reads them literally: `CHECK_FALSE(r.approximate[e])` on every file under `tests/scenes/valid/` (from the code, `test_diffuse_reports.cpp` L254). My intent was narrower: **every scene a user can reach as a room or preset** (the plugin default `medium_room`, the Phase 04 rooms, the Phase 12 presets). The requirement protects the first minute; a 1.5 × 100 × 4 m slot with α alternating 0.01/1.0 per band and a −60 dB emitter 0.3 m from the listener (from the code, `edge_values.json`) is not a place any producer builds [Hyp; Seat 8 confirms]. So the reversal is met on my words, not on my meaning; I own the AMENDS. But `open_field` is user-reachable in substance: FR-3D-3's outdoor category will put presets in the same state (K-b6), so (ii) still bites at Phase 12 and needs a remedy there.

**2–4. Ranking and tension (now / later).**
- **(d) prefer — 0 / 1.** Now: (d)(ii) is my living register made visible (cause, and whether a move silences it: K-b3 shown, not asserted). Later 1: commits Phase 11 to a suppression rule and Phase 12 to report the cause per outdoor preset; undo is a display toggle; evidence at Phase 12's outdoor check (AX37 (5.4) branch (a)).
- **(a) can live with — 1 / 2.** Now: an honest reading; the two fixtures move to a known-case list. Later 2: it leaves Phase 12 outdoor presets to meet (ii) with no remedy (placement cannot silence the capped branch), so either the reversal fires again or the note says "level unreliable" on the first field preset about a tail below −60 dB after t_dir + 50 ms (AX37 (5.4), kept check) — the W4 cry-wolf pattern that teaches users to ignore the note in the both-near corners that read 1–6 dB low (C13 §2). Undo: a Phase 12 loop.
- **(b) can live with — 2 / 1.** Now: changing a fixture to silence a truthful flag is tuning content to a test, and it does nothing for `open_field` or the presets that follow it. Later 1: fixtures are cheap to restore; blast radius is Seat 5's.
- **(c) cannot prefer — 2 / 2.** Now: the predicate I confirmed 1/1 (file 30) is reopened on evidence from scenes no user reaches, a full loop before the push. Later 2: a predicate tuned to be silent at an open field risks silence at the real both-near cases; a cried-wolf or silenced note, once shipped to beta, is not recovered by a patch (my file 30 later-2). Not veto: U is a parameter before release.

**(d)(i) answered.** The note should **not** be shown on an open field where the tail it describes is below the −60 dB line: it is a true statement about something inaudible, i.e. noise in the first minute. A rule "no note where the tail it describes is below AX37 (5.4)'s −60 dB line" is a display condition of the same kind as "settled scene only, info view, never mid-drag" (Seat 6 (i)); it touches neither U nor `TailMatch.approximate`, so it is mine — with the line itself borrowed from the plan, and Seat 1 saying whether "below −60 dB" means inaudible to the target listener. The fact stays visible in the (iii) diagnostic tier. If shown anyway (tier (iii), or Seat 1 asks for it): "Outdoor scene: the reverberant tail is more than 60 dB below the direct sound; its level is only roughly estimated." No ±x, no "move either 0.7 m" (there is no action).

**medium_room.** Pilot-floor / floor-truncated with U silent and SE ≤ 0.19 dB (file 9) is fine: those flags are tier-(iii) diagnostics, under 0.33 dB and far under the 1 dB G jnd (AX42's basis). Condition: they never surface outside the advanced tier. Why the plugin's default scene hits the pilot floor is AX41's matter (Seats 2, 5), not mine.

**5. Evidence.** From the code: L254/L257 of the reports test; both fixtures. Plan ids: AX44 (ii)/(iii) text, AX37 (5.4), AX41 "pilot ships" list, AX42; PRD FR-3D-3, FR-3D-5. File 9 (SE figures, "every other fixture silent"). My words: file 30 (ii), file 34 L40/L186. Incidents W3, W4 (`{SRi; FST21, FF-forum-float}`). No acoustic claim of mine; corpus not needed. [Hyp]: no producer builds the slot; a cried-wolf note trains dismissal (incident-based, unmeasured here).

**6. Conditions.** (a) → 1/1: add (d)(i) or write into (ii) that for an outdoor preset the remedy is the display rule, not placement. (b) → drop. (c) → 1/1 only if the reopening trigger is restricted to a user-reachable room or preset.

**7. Hand-offs.** Seat 1: whether "below −60 dB after t_dir + 50 ms" is inaudible for the target listener. Seat 5: the `pilotShipped` assertion and the known-case list in the test; blast radius of (b). Seat 7: public wording for outdoor scenes. Seat 8: that neither fixture is a scene producers build. Seat 9: whether an open field has a "tail" at all. Human: a five-user first-minute test on an outdoor preset in Phase 12.

**Commitments.** (a): Phase 11 shows the note on fields; Phase 12 meets (ii) at outdoor presets with no remedy. (d): Phase 11 implements one display rule keyed to AX37 (5.4) and the tier-(iii) fact; Phase 12 reports cause and movability per outdoor preset. Undo of either: a display toggle, not a loop.

**8. Premortem.** If (a) ships alone, the first festival preset says "level unreliable" about a tail nobody hears, the beta producer learns to ignore the note, then backs mic and amp into a club corner where the tail reads 1–6 dB low and nobody heeds it; Maisara notices at the Phase 12 listening checklist.


---

## D-H3 (e)

SEAT 6 POSITION (item (e); file 18's K-b3 table changes nothing in my item (b) position: every moved placement of both fixtures stays capped, as I assumed)

**1. Reading.** What the producer experiences in a 100 m room when the host delivers `reset()` or the offline switch, under each option. Cues: "motion is first-class / no workflow breaks" (criterion 4) and "show engine honesty in the picture" (Strategy B4; FST21 incident: say plainly what is read on release).

**The user's experience, in my measures.** From the code (`ScenePipeline.cpp` L245–265, L313–327) and phase-07 L128–133: when the last IrSet is scene-current, every option reuses it and installs it at once; the only exposed case is a parameter change still in flight when stop is pressed. There, under (e-a)/(e-d), a VST3 host that issues `setProcessing(false)` on the processing thread (file 12 F1, F2, F6; which hosts: unknown, K-e7 [Hyp]) stalls its whole graph for the quiesce wait plus a full build, 0.18–0.80 s at 48 kHz, up to ≈ 2.6 s at 100 m / 96 kHz (§0 row 07, file 16). No picture can explain a stall: the producer reads it as "the plugin froze my DAW" (my register: post-release artefact tickets, `{Obs; IEM-changes}`). Under (e-b)/(e-c): no stall; after play, silence until the builder delivers (same 0.2–2.6 s), then a 2P fade (Seat 1's to judge), with "settling" shown. Bounce/freeze: a conforming host switches on the UI thread (F3) and offline always waits for the final solve (phase-07c condition 6) — identical across options from the user's chair.

**2–4. Ranking, tension now / later.**
- **(e-b) prefer — 1 / 1.** Now: the stale case is silence-with-"settling", honest and bounded, in the default room ≤ 0.2 s (under the 1 s anchor, AX38 (iv)); costs phase-07's "not silent after reset" in that one case. Later: it is 07c's `reset()` half done early; nothing to undo. Scope and test cost are Seats 5 and 7's.
- **(e-d) can live with — 1 / 1.** Now: the stall stays possible but measured (K-e6), thread-named in a log, and the note can carry a number. Later: 07c is next (D-H1 (v)); undo is nil. Condition for 1: the compatibility note is scoped ("very large rooms, right after editing") and the measurement is 07c's, not Phase 13's.
- **(e-c) can live with, conditional — 2 / 1.** Now: removes the seconds-long build but keeps a wait of unknown length on the audio thread (ISM/synthesis cancel points unrecorded, K-e6); until measured it is (e-a) in another name. Condition → 1: K-e6 shows the worst wait under the 100 ms "instantaneous" anchor from my side (Seat 5's one-buffer rule is stricter and governs). Later 1: superseded by 07c.
- **(e-a) can live with — 2 / 2.** Now: an unscoped, unmeasured possible 2.6 s session stall; nothing on the canvas can show it. Later: the note stays vague until Phase 13's matrix; beta tickets arrive before 07c. Condition → 1/1: (e-d)'s bound and the 07c routing.

**What "settling" should say.** The existing AX38 (iii) state, one more trigger (post-reset stale build): "Settling the room…" on the scene, no number unless measured, never mid-drag, cleared on the first IR install. Under (e-a) there is nothing to say: a stall shows no UI. For bounce/freeze no "settling": the host's progress bar is the UI and the render waits for the final solve.

**Compatibility note the user needs** (Seat 7 writes it). Say what happens and what to do, never "thread", "reset()" or a spec: "In very large rooms (tens of metres), pressing stop right after editing may pause your session for up to about 3 s in some hosts while the room finishes computing. Bounces and freezes always wait for the full room and are identical every run." Under (e-b) the first sentence becomes "…the room may take up to about 3 s to settle after you press play; you will see 'settling'." Name hosts only after measurement.

**Defaults and controls.** None of (e-a)–(e-d) changes a default, a range, a parameter or the canvas; confirmed.

**5. Evidence.** From the code: `ScenePipeline.cpp` L102–133, L245–265, L313–327. Plan: phase-07 L128–141, phase-07c §5 conditions 4–6, AX38 (iii)/(iv) (Card 1991 anchors as cited there; not corpus). File 12 F1, F2, F3, F6, F9 (researcher, read, high). Build times: §0 row 07 via file 16. [Hyp]: which hosts use the processing thread for `setProcessing(false)` (K-e7, RQ-H3-3); the producer's reading of a stall (incident-based, unmeasured here). No acoustic claim; corpus not needed.

**7. Hand-offs.** Seat 5: the audio-thread rule, K-e6, the scope pull. Seat 7: note wording, measurement cost and phase. Seat 1: audibility of a 2P fade after a transport discontinuity. Seat 3: whether a stale IR can be kept across a realtime reset without breaking X11 (I would prefer it: then silence never occurs). Seat 8: the freeze habit. Human: the per-host measurement on Maisara's machines.

**8. Premortem.** If (e-a) ships unscoped and one beta host delivers `reset()` on the audio thread, the first ticket reads "my DAW hangs 3 s when I press stop in the stadium preset", filed in the beta forum before any matrix measures it; Maisara notices first.
