# 14-seat2: Seat 2 on the corner/onset findings' home

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 2 POSITION

**1. Reading.** The question is where the two NFR-8 placement findings (the both_corner tail level and the both_wall t_mix,e onset) get their cause established, and whether that happens before or after Phase 08's golden freeze. The cues it triggers from my §4: 4 (path geometry: source or listener near a wall or corner), 5 (which parameter deviates: a late level against an early/late split) and 7 (does the cost land once or twice). This is §6 S4 and S6 territory, with the circularity watch from S6.

**2. Ranking**
- **H3, a dedicated report-only phase before 08 (for example `phase-07e`, Lead Seat 2, size S, runs before 07d's growth re-pin and before 08-3): prefer.** The investigation ships as its own phase. If the board there rules that `src/sim` must change, the fix is a separate phase file that lands before 08-4 freezes the goldens. I add that split myself.
- **H2, a new scope item in `phase-07d`: can live with.** 07d's subject is load, the macOS defect and the growth re-pin, which is Seat 5 ground, and its Lead is unnamed (phase-07d L6). It does sit before 08 and before the re-pin it would otherwise invalidate.
- **H1, `phase-13-2` as proposed: can live with, at a major later cost.** 13-2's Goal is the performance budget (L7–9). It depends on 13-1, which depends on 00–12. So the cause stays unknown through 08, 10-1 and 12-2.

**3. Tension now**
- H3: **1.** One S session, no output change; the scripts already exist (file 5's method, `--diagnostics`).
- H2: **1.** The same work, but it enlarges an S–M phase towards its split limit.
- H1: **0.**

**4. Tension later (the debt)**
- **H1: 2.** If the cause is the AX40 estimator or the AX22 test, every scene's tail can move. A fix found at 13-2 then means:
  - a second golden round after 08-4's freeze;
  - an M3-8 rebuild of both sealed ABX scenes, with 08-3's cross-chain comparison void;
  - a rework of 10-1's position-only tail cache, which is keyed on per-emitter handover state;
  - a re-check of 12-2's presets.

  Undoing it costs roughly a phase of rework. The overturning evidence arrives only at 13-2, the latest point available.
- **H2: 1.** It still lands before the freeze. The risk is that the item gets dropped when 07d splits on its own work.
- **H3: 1.** A fix still costs one golden round (§6 row), but only once and before the freeze. Undoing H3 means deleting one phase file.

**5. Evidence**
- **The cause of the both_wall onset can already be narrowed from the code [Observed, code; reading Inferred].**
  - `planEmitter` (Engine.cpp L142–156) moves the handover from the expected-rule t_mix,e to the N_cap image time t_cap,e only when AX22's realised-k test fails, meaning k_real < 19 in some band from 500 Hz to 2 kHz.
  - R's 0.380 s matches the fallback time of every other layout4_s1 scene (file 5, column 3). L's 0.165 s therefore looks like the base rule's value: L passed the realised-k test and R did not.
  - So the candidate cause for (b) is AX22's realised-k test on the image-source set at a source 0.1 m from a face, not the t_mix,e rule (MixingTime.h). The decider's candidate list should name it. The `ismFallback` / `expectedMixS` / `capTimeS` diagnostics can confirm it in minutes.
- **(b) may not breach NFR-8 at all.** At equal times L and R agree within 0.05 dB (file 5 L21). The question is whether L's ISM-to-tail energy is continuous across [0.165, 0.380) s compared with R's ISM-only energy in the same window. If it is, the +9.39 dB is only a split between ISM and tail, not a level error.
- **(a) is a probable breach.** 6.2 dB is about six JNDs of G (1 dB; Vorländer Table 6.1, as cited in MixingTime.h). Kuttruff Eq. 5.42 expects equal reverberant level at equal power, which is indicative only (§5.6). The deficit also points the wrong way for the near-boundary physics I know: a source at a boundary radiates more power, not less [Hyp; researcher to source].
- **What the investigation must establish (cost: one S session, no `src/sim` edit, roughly CPU minutes):**
  1. A placement sweep at 0.1, 0.2, 0.5, 1 and 2 m from 1, 2 and 3 faces.
  2. For each placement, per emitter: the equal-window 1 kHz level against Eq. 5.42, E_target from AX40 against the `matchTail` energy, `--tail-level ax16` against the default, k_real and the fallback flag.
  3. Window energy from the full IR (not tail-only) for (b).
  4. A verdict, per finding, on whether NFR-8 is breached: a level spread over 1 dB at equal times, unexplained by physics.
  5. Non-circular: nothing is fitted to the compared level.

**6. Conditions of acceptance**
- H1 drops from later 2 to later 1 if the investigation half moves before 08 (that is, H3), with only the fix, if one is ruled, left to a later phase.
- H2 drops from 1/1 to 1/0 if the item is named its own scope with Seat 2 as Lead and is exempt from 07d's split-off.

**7. Hand-offs**
- Seat 7: schedule cost of one extra S phase before 08.
- Seat 1: whether a 6 dB per-emitter tail deficit is audible for producers.
- Seat 9: whether 12-2's presets place sources within 0.5 m of a corner.
- Seat 5: ordering against 07d's growth re-pin.
- Researcher: a corpus source for near-boundary sound power at 1 kHz, 0.1 m.

**8. Premortem.** If the item stays at 13-2 and the cause is the estimator, 08-4's goldens and 08-3's binaural record are frozen on a known-wrong tail. The contractor reviewing 13-2's golden diff would notice first, as a second golden round touching every scene.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/5-builder-tail-spread.md
- /home/user/makroof/docs/review/phase-07c-2b/9-decider-m3-r3.md
- /home/user/makroof/docs/review/phase-07c-2b/10-interrogator-on-file9.md
- /home/user/makroof/docs/phases/phase-13-2.md
- /home/user/makroof/docs/phases/phase-07d.md
- /home/user/makroof/docs/BUILD_PLAN.md §0
- /home/user/makroof/src/sim/Engine.cpp (L105–164)
- /home/user/makroof/src/sim/tail/MixingTime.h

Not read: phase-13.md. The corpus was not re-opened; Kuttruff citations are taken from files 9 and 10.
