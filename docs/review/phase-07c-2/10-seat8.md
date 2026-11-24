<!-- Saved by the orchestrator from seat 8's report, 2026-11-22. -->

SEAT 8 POSITION, round 2 (phase 07c-2): U2 re-projected without the 2× factor, and D-W3 rated. Corpus c1b171f. My persona holds no incident on hold latency or bounce wait, so every figure below is arithmetic on the fact sheets [Inf] and every producer reading is [Hyp].

**Whose ears.** A producer automates a source across a hall-class room (layouts 4/5 at s = 1, 20 × 30 × 10 m with an absorbing floor). The automation is timed to the arrangement, for example a fly-by landing on the downbeat. She judges it in playback and then bounces it.

## (a) U2 re-projected (CI ≈ local per scene, interrogator H-2)

**U2 as I stated it.** The bounce time that W adds to a 36-rebuild, 3-minute bounce is at most 0.25 × real time, which is 45 s. On the worst OS at pool size that allows about 1.25 s added per rebuild. The 48 kHz bounce must also stay at or below 1× real time.

**Inputs.**
- Pool(4) maximum medians over the capped set (part 3): ×5 590 ms, ×6 810 ms, ×8 813 ms.
- At the pin, the largest capped-set pool median is about 184 ms (part 2 T1).
- macOS runs a pool of 3. I scale its time by 4/3 as a worst-OS hedge [Inf].

| m | added per rebuild, Linux / macOS hedge | added over 36 rebuilds | as × real time | 48 kHz bounce (pin 0.24–0.42×) | U2 |
|---|---|---|---|---|---|
| 5 | 0.41 / 0.61 s | 15 / 22 s | 0.08 / 0.12 | ≤ 0.54× | holds |
| 6 | 0.63 / 0.90 s | 23 / 32 s | 0.13 / 0.18 | ≤ 0.60× | holds |
| 8 | 0.63 / 0.90 s | 23 / 33 s | 0.13 / 0.18 | ≤ 0.60× | holds |

**Answer: U2 does not bind anywhere in m = 5…8.**
- It would bind only near ×16. The worst ×16 cell is 1 632 ms (layout5 emitter_wall, T1), which adds about 0.29× on Linux and about 0.43× under the macOS hedge. That is above any window U3 allows.
- So U2 never becomes the deciding term. I accept that it be **recorded rather than pinned as a W term**, which agrees with Seats 2, 5 and 7.
- My one remaining condition: the AX38 4c bounce record is re-run at the chosen W on three OSes, and it includes a layout-4 s = 1 position-automation bounce. The 100 m s = 0.3 cube saturates at ×2, so on its own it cannot show what W does.

## (b) D-W3: the ISM update held behind a running solve

**What the hold costs my seat.** While the hold lasts, the whole ISM, direct path and early reflections included, lags the automation in playback. The offline bounce waits for every final (condition 6), so it is exact. She therefore approves a move in playback that is not what she bounces, which is cue 10 and the GM1 pattern. At 120 bpm one beat is 0.5 s:
- ×5: up to 590 ms, about 1.2 beats late;
- ×6: up to 810 ms, about 1.6 beats late;
- at the pin: about 184 ms, about 0.4 beats.

The §8 requirement this breaks is "automation that is click-free and timed to the arrangement".

| option | label | now / later | reason |
|---|---|---|---|
| **H-2** decouple | prefer | 0 / 1 | The ISM follows the automation at once, so position, early field and direct sound arrive on the beat. During continuous automation the diffuse level holds at B1′, then makes one AQ4 step at rest. That step is bounded by AX47 and its ABX. Debt: the generation check means continuous automation also starves adoption, as H-1 does (evidence in M7b). |
| **H-1** cancel-on-edit | can live with | 1 / 1 | Same benefit for the ISM, with latency up to the next stop point. Same diffuse starvation, and partial solves are wasted. Evidence in M7b. Undo is a builder-loop change. |
| **H-0** no change, W ≤ ×5 | can live with | 2 / 2 | It keeps a lag of up to 590 ms (1.2 beats) in playback, and the bounce differs from what she heard. The layout4 listener_corner position stays U = 1 at SE 0.375 dB: two stem positions about 0.53 dB apart (√2·SE), under the 1 dB jnd (Vorländer Table 6.1). The lag, not the SE, is my cost. Debt: the lag is locked in, and the fix later is the same threading change in 10-1 or 13, plus a re-pin and a golden round. Before release that round is condition 1; after release it needs versioned state. |
| **H-3** relax U3 | can live with | 2 / 2 | It makes an 810 ms lag (1.6 beats) the norm in hall-class rooms, and it grows with W. Table 15.1 is a VR yardstick, but a lag against the musical grid is what she hears. Undoing it means reopening AQ4's rationale (Q4, NFR-3). |

**Conditions of acceptance.**
- **H-0, 2 → 1:** pin at ×5 only with H-2 recorded as dated debt in 07d or 10-1, before 13's beta. Phase 13's release check must test the playback lag in an automation case.
- **H-3, 2 → 1:** a new yardstick no longer than one beat at 120 bpm (500 ms), measured as the ISM latency in M7 on three OSes. That likely amounts to H-2 by another name [Hyp].
- **H-2 and H-1, later 1 (not required):** an anti-starvation rule, such as adopting the newest completed solve during a move. Admissibility is for Seats 2 and 5 (determinism, NFR-8); offline is unaffected.

**Hand-offs.**
- Seat 5: H-2 threading topology and TSan.
- Seat 2: the adoption rule.
- Seat 1: whether a held B1′ diffuse level during a long move, and the step at rest, can be heard.
- Seat 3: time variance.
- Seat 7: scope and schedule.
- Orchestrator: M7 and M7b decide H-0's lag off this local box.

**Premortem.** If H-0 or H-3 wins, a beta producer automates a fly-by in a hall and hears it land more than a beat late in playback. She re-times the automation to compensate, and then the bounce is early. Beta support notices first.

Files read (under /home/user/makroof/docs/review/phase-07c-2/):
- 8-decider-rebuttal-r2.md
- 2-fact-sheet-part3-m2.md (L1–181)
- 6-interrogator-on-file5.md (H-2 rows)
- 2-fact-sheet-part2-wsweep.md (T1, T5)
