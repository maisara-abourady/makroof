# 2 — Seat 6 position (D-B1, D-B2, D-B4, D-B5 (iii), (v), (vi)), round 1

2026-11-13. Saved by the orchestrator from the seat's report. No acoustic claim (corpus not needed). Read: file 1, the phase
file, BUILD_PLAN AX38 (i)/(iii)/(iv)/4c, AX47–AX49, GATE lines in 07c-1 files 19, 20, 41, 42, 44, `docs/review/phase-07c-1/3-seat6.md`,
`docs/review/phase-05h/61-…`, RG-1 `docs/review/phase-05h/70-…`.

Governing point [Inf] (from file 3): at project load the plugin window is usually closed, so "settling" (AX38 (iii)) explains
nothing heard at load; at insertion the window is usually open [Inf].

## D-B1
Reading: can 8 rebuilding instances drop out (a click breaks motion integrity, criterion 4, S3)? Do the remedies lengthen
settling (AX38 (iii))? Are we keeping a non-measurement (W3)?
Ranking: B1-b prefer; B1-d can live with only after B1-b's evidence; B1-a can live with; B1-c can live with, conditions.
- B1-b 0 / 1: nothing seen changes; a figure from a host audio thread (the fact-1 instrument measures 1–2 samples); one more
  record; Phase 13 owns the remedy if the rise persists; evidence on B1-b's first run.
- B1-d 1 / 1: not an instance cap, but with more instances than cores the queued ones settle later (not computed); a remedy
  before the evidence; undo = one constant; evidence B1-b at 0/1/2/4/8.
- B1-a 1 / 2: "record only" on that instrument is silence, not a measurement (W3); real dropouts surface only at Phase 13,
  after Phase 11 drew settling around today's timings.
- B1-c 1 / 2: lowered QoS may slow macOS builds a lot [Hyp, RQ3]; settling grows for every instance (ASFX16 switch delay);
  inversion risk on class (1) restores; changes cond. 12's "default priority" (K7, the decider's reading).
Conditions: B1-a → 1/1 = B1-b; B1-c → 1/1 if settling at 8 instances under the lowered priority is measured at or below the
current (iv) staleness records and class (1) restores keep their own priority. Hand-offs: Seat 1 (audibility), Seat 5 (RQ2,
instrument, inversion), Seat 7 (cost of B1-b's runs).

## D-B2
Reading: the product's first sound; time to first plausible scene; "default = most real state" (criterion 1, E1); recorded
AX48 input "no load gap or step".
Ranking: B2-a prefer; B2-d can live with; B2-b can live with at 2/2.
- B2-a 0 / 0: the default room from the first sample, no step; ≈ 145–430 ms inside an insertion the DAW already blocks on
  (below the 1 s anchor); undo = one test and one reading.
- B2-d 0 / 1: same sound, slightly shorter wait; an embedded per-platform constant; fingerprint failure falls back to B2-a;
  NFR-8 and complexity Seats 2, 7.
- B2-b 2 / 2: the first sound ever heard is dry, then the room arrives by itself after ≈ 0.15–0.43 s (W4 pattern) at the most
  important moment; not veto-grade (no saved tail; window open at insertion); every later mode (08, 09) inherits the gap;
  AX47 forbids an early-only first IrSet, so the gap is dry or silent; silent would be 3 for this seat.
Condition (B2-b): only if the gap fell inside the first host block — nothing within AX47 does that, so it stays 2.
Hand-offs: Seat 8 (insertion in a playing session), Seat 5 (RQ5), Seat 2 (B2-d, NFR-8).

## D-B4
Reading: an 8-stem project at the corner (96 kHz, T60 8 s, 100 m); every instance audible from the start (right result);
cost a 5–10 s DAW load, past the 3 s and under the 10 s anchors (Card et al., UI anchors, not audibility); cues: heavy
recompute; a trigger answered with "record" (W3).
Ranking: C1, C2, C6 prefer together; C4, C7 can live with; C5 can live with if Seat 1 passes it; C3 can live with; C8 can live
with at 1/2.
- C1, C2 0 / 0 (bit-identical; for C2 Seat 5 checks it adds no D-B1 callback contention); C6 0 / 1 (shorter load; others play
  the provisional a little longer; an edit during an insertion settles later; settling stays honest); C4 0 / 1 (memory Seat
  5's); C7 1 / 1 (load stays until 07d, which lands before release); C5 1 / 1 (sound changes for every render; golden round;
  Seats 1, 9); C3 1 / 2 (earlier and larger handover: a room changing by itself after load; L4 may detect it; depth floor Seat
  9's); C8 1 / 2 (fact 3: partly work, not weather; 8 × 634 = 5.07 s).
Conditions: C3 → 1/1 if the cap never puts L_p below the current L_f at the gated corner and the L4 ABX passes first; C8 →
1/1 only alongside C1, C2 or C6, with a Phase 13 threshold whose miss returns to the board before release. Hand-offs: Seat 8,
Seat 7 (07d sizing), Seat 5 (C2, C6).

## D-B5
**(iii)** macOS medians of the selected runs: 1 528 (41), 2 223 (42), 2 572 (44); mean 2 108; M-a → 1.15 × 2 108 ≈ 2 424 ms;
spread ×1.68. M-a prefer 1 / 1 (over all green runs, independent of in-window runs, which macOS lacks; at ×1.15 vs a ×1.68
spread it can still call weather a defect — run 44 already exceeds 2 424; undo one constant). M-b can live with 1 / 2 (fewer
than 3 in-window macOS runs → the trigger drifts); condition M-b → 1/1: ≥ 3 in-window macOS runs remain, else M-a. Added
option: the factor from the measured spread, never below 1.15, by kSolveWarn's k rule — 1 / 1.

**(v)** E3 prefer 0 / 1 (true: at L_p ≥ L the restore holds the full synthesis, as the split clause anticipates); E1 can live
with 0 / 1 (outcome = E3 on these runs: macOS 23.68 / 38.78 / 47.15 s, Windows 31.97 / 20.47 / 22.37 s, neither ≤ 30 s on all
three); E4 can live with 1 / 1 (only as the register's existing "or" branch next to E3; runner cause not shown); E2 can live
with 2 / 2 (closing on the median while the worst reads 47 s makes the gate say "fine" when it is not, criterion 6; no
condition short of E1's rule).

**(vi)** The trigger was derived from pre-condition-9 medians and the rule says it is "re-derived at the 07c re-pin"; RG-1's
reversal clause: a double on identical code before 07c means disarm (T1); runs 42, 44 ran on a changed restore path. The runs
differ: 42 (flutterDev +38.4 %) reads as weather; 44 (flutterDev +5.3 %, ratio 5.048 above the 4.5 warning line) is a signal
to read (Seats 3, 5 to diagnose). The real incident: it fired twice and nobody read it (K24) — W3 inside our own process.
- X-b with conditions prefer 0 / 1: (1) a ledger and §6 entry stating both medians, flutterDev, the ratio and "uncalibrated";
  (2) the re-derived trigger applied to runs 42/44 and to the re-pin runs, and if they exceed it the outcome becomes X-a;
  (3) reading MACTRIGGER a fixed step whenever a run's records are read.
- X-a can live with 1 / 1 (a defect entry with the remedy the macOS entry already carries, 07d; may label weather a defect).
- X-b without those conditions 1 / 2 (after-the-fact reclassification lets every later trigger be explained away).
Whether X-b reads or amends a recorded rule (FOR MAISARA or not) is the decider's (Seat 7 on the PRD reading).

Evidence: GATE lines files 41/42/44 [Obs]; RG-1 file 70 items 1, 12 [Obs]; defaults = reality, switch delay {Obs/SRi;
IndMan, ASFX16; pre}; automatic change unasked {SRi; VSL-forum-NV} (W4); silence is not approval {Obs; FF-forum-float} (W3);
window closed at load / open at insertion [Inf]; QoS slowdown [Hyp] (RQ3).
Premortem: B2-b ships and B1-a keeps the instrument — a reviewer hears a dry vocal on insert then the room popping in; months
later a 16-track beta report says "crackles while I edit the room"; Seat 8's testers notice before any CI record.
