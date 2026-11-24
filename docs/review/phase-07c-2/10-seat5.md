<!-- Saved by the orchestrator from seat 5's report, 2026-11-22. -->

SEAT 5 POSITION: round 2 (phase 07c-2)

Scope: this answers only what changed. Read: file 8 (§2, §5, §6), file 6 (rows C-1, MAP-1, MAP-4) and fact sheet part 3 (M2). I also checked the code myself: `ScenePipeline.cpp` L100–123, L260–300, L490–557.

# (a) D-W1 re-decision cells

**1. Reading.** Facts used: m* = 6, with a 0.007 dB margin, at `layout4_s1/listener_corner` e1. U3 is projected to fail at m = 6 (pool solve 810 ms against the 700 ms yardstick). Per-scene costs are counted once.

Cue: the deep structure (§4.5). The ISM hold is tied to W only because one thread does both jobs. That makes the D-W1 window depend on D-W3 before anything else.

**2–4. Ratings**

| option | rank | now | later | reason |
|---|---|---|---|---|
| W-C2 (W-6′ picks, W-1′ caps) | prefer, on condition | 1 | 1 | See below |
| W-C1′ (largest m within U1–U3, U2 = Seat 8's bounce cap) | can live with | 1 | 2 | See below |
| U2 as a term (my answer to the ratio question) | can live with | 1 | 1 | See below |
| Either rule under D-W3 H-0 or H-3 | cannot be satisfied | — | — | U3 leaves the window [6, 5] empty |

**W-C2:**
- **Why 1/1 now.** The two reasons behind my "W-6 alone 2/2" are gone:
  - the layout clause binds, not the gated ×1 case;
  - the both-near placements are excluded by name, so the floor has a finite answer.
- **Why I accept W-6′ as the selector now.** The SE is deterministic (D5/D7). Choosing the smallest m is the cheapest pin to raise later, and a pin can never be cut (AX38 4c).
- **U1 holds at m = 6.** The local single-thread maximum is 2 281 ms, under 3 s. Locally U1 allows about ×7.9 (2 281 / 6 ≈ 380 ms per m, and 3 000 / 380 ≈ 7.9).
- **The 1/1 is conditional.** Without the conditions below it is 2/2. That is because a 0.007 dB margin may flip on another OS, and because U3 leaves no valid m.

**W-C1′:**
- U2 does not bind before U1 (see the U2 row), so W-C1′ ≈ U1 ≈ ×7–8 once D-W3 removes U3.
- The debt is the same kind as W-C2's but larger, and W cannot be cut later:
  - under K-a, the non-gated s = 1 cube's keyless restore projects to 35–40 s at ×8 (T5);
  - every background solve takes longer, and that time is multiplied by the number of instances under the serialised gate.
- **Undo cost:** the only direction allowed is up, so overshooting costs nothing to fix. Being wrong about restore usability means a class (c) round redo.

**U2 as a term:**
- **It does not bind.** Taking the local pool median of `layout4_s1/default` as the per-rebuild solve:
  - ×8: 36 × 0.748 s = 26.9 s, minus the pin's 36 × 0.118 s = 4.2 s, so about 22.7 s added on 180 s, i.e. 0.13× real time;
  - ×16: 36 × 1.397 s − 4.2 s ≈ 46.1 s added, i.e. 0.26× real time.
  - So U2 binds at about ×15, above U1.
- **Hosts allow it.** A bounce slower than real time is a wait, not a fault (dossier R14–R20).
- **It is veto-grade only if asserted in CI.** 96 kHz bounce ratios already span 0.76–1.36× across runs (F7), so an asserted ratio cap would flake on hosted runners.

**5. Evidence**
- From the records:
  - fact sheet part 3, the worst-SE table;
  - part 2, T5;
  - part 1, F7 and F10.
- F10 shows different AX48 fingerprint hashes per OS. So "local equals CI" is shown for Linux only: the E_b, and with it the achieved SE, is not shown bit-identical across OSes. [Inferred]
- The arithmetic above is mine.

**6. Conditions of acceptance**
- **W-C2 → 1/1:**
  - D-W3 makes the ISM hold independent of W (H-1 or H-2, below);
  - the three-OS SE/VOV print is made at the pin before the constant is committed; if any OS shows more than 0.33 dB at ×6, take ×7.
- **W-C1′ → 1/1:**
  - the class (c) round fixes the keyless path before the pin (file 8 §2 already orders this);
  - K-a restore records are printed for the s = 1 cube and for every layout 4/5 placement at the candidate m.
- **U2:** a check at derivation time, from the worst of ≥ 3 runs (M9). It is never an asserted CI gate.

# (b) D-W3: the ISM update held behind the solve

**1. Reading.** One builder thread both assembles the ISM and runs the solve. An edit that arrives during the solve therefore waits for it. Cues: "what crosses between clocks" (§4.5); the S1 snapshot protocol; "a lock added for safety".

**Code fact that changes the frame (from the code):**
- Today an edit already gets its B1′ IrSet before the solve starts (L494–524).
- A solve whose generation went stale while it ran is already discarded at L539: `dirty_ != gen`, counted as `discardedMidDrag`.
- So under continuous automation, H-0 already completes no final until a quiet spell. The starvation risk that file 8 attributes to H-1 exists today.
- The only difference: H-0 makes the ISM **wait** for a solve it will throw away anyway; H-1 abandons it at the next stop point.
- So H-1 can only make finals arrive sooner (the next solve starts earlier), and the ISM hold no longer depends on W. M7b should show H-1's completion fraction ≥ H-0's. If it does not, my reading is wrong.

**2–4. Ratings**

| option | rank | now | later | reason |
|---|---|---|---|---|
| H-1 cancel-on-edit, with conditions | prefer | 1 | 1 | See below |
| H-2 decouple | can live with | 2 | 1 | See below |
| H-0 no change | can live with | 1 | 2 | See below |
| H-3 relax U3 | can live with | 1 | 2 | See below |

**H-1:**
- It reuses the existing cancel path: `options.cancel` → `BuildCancelled` (L260, L552) → the RAII gate `Scope` releases the gate (L281).
- No new thread, no second committer.
- The hold becomes the cancel latency plus the ISM assembly, bounded by the work between stop points, not by W.
- Offline is untouched (`Source::Offline` passes no cancel, L275), so the bounce stays bit-identical (AX5).

**H-2:**
- **Why 2 now.** It adds a second concurrent actor in the pipeline. That puts at risk:
  - the single-committer invariant (L566: "The deciding thread is the only committer");
  - the lifetime of a solve still in flight when the pipeline is destroyed or quiesced (destructor L103–110), a use-after-free risk;
  - CPU load: ISM assembly would run beside a pool of `hardware_concurrency` threads, one thread over the core count, which worsens the Linux B1-b overruns (F8).
- **Why 1 later.** It is the right architecture for 08 (heavier binaural ISM) and 10-1 (cache), because the ISM latency becomes independent of every solve cost.

**H-0:**
- Thread-safe as it is.
- The hold stays proportional to W for good. Every later W re-derivation (Phase 08's heaviest mode, Phase 13's release machines) runs into U3 again.

**H-3:**
- No real-time safety issue for my seat.
- It changes AQ4's yardstick (Q4/NFR-3, the Expert's) and leaves the hold growing with W. The same debt as H-0, borrowed through the plan.

**5. Evidence**
- From the code: L275, L281–287, L494–545, L552, L566, L103–117.
- File 6, row C-1.
- F8 (B1-b, Linux without RT priority).
- Cancel granularity, i.e. the work between `run.stop` checks, is not on file. [Hyp]

**6. Conditions of acceptance**
- **H-1 (keeps 1/1):**
  - (i) Use a cancel token per generation, separate from `builderAbandon_`. That flag is the quiesce/restart protocol (L114, L121); merging the two would race with `restartBuilder()`. The token is either an atomic comparison of `dirty_` against `gen`, or an atomic flag set from `setParameter`. Either way it is lock-free and safe from any thread.
  - (ii) Stop points are spaced by a fixed work count, never by time (AX41).
  - (iii) M7 measures the cancel-plus-ISM latency at m = 1, 4, 5, 6, 8 on three OSes; it must be ≤ 700 ms at every m and flat in m.
  - (iv) M7b shows H-1's completion fraction ≥ H-0's.
  - (v) A TSan `[pipeline]` test with edits landing at random solve points.
  - (vi) The D7 final is bit-identical with and without a cancelled predecessor.
- **H-2 → 1/1:**
  - the solve runs on the process-wide gate executor, not as an extra thread per instance (no instance cap);
  - an immutable snapshot of the problem goes in, and the result comes back through a mailbox with shared ownership that the builder alone commits;
  - quiesce waits for or orphans the task;
  - the pool is sized `hardware_concurrency − 1` while the builder runs alongside;
  - the TSan stress test above, plus a B1-b re-run.
  - Also: a solve result for a stale scene may be adopted only as a held level, never as the final (Seats 2 and 3 to judge).
- **H-0 and H-3 → 1:** a re-derivation trigger written into AX41, so that any later W raise re-checks U3.

**Debt**
- H-1 lands in 07c-2 as a small change, evidenced by M7, M7b and TSan.
- H-2 is the natural candidate for 07d or 10-1 if Phase 08's binaural ISM assembly alone approaches 700 ms (Seat 4, evidence at 08-4).

**7. Hand-offs**
- Whether H-1 meets C-a and condition 4: Seat 3.
- The adoption rule for stale-scene E_b under H-2: Seats 2 and 3.
- The audibility of a held level during long automation: Seat 1.
- Changing AQ4's yardstick (H-3): Seat 3, the Expert's question.

**8. Premortem.** If H-2 ships without a single committer and orphan-safe lifetime, the first field crash will be in a session where the user deletes an instance mid-drag. TSan sees it only if the stress test races destroy against solve. If H-0 ships instead, the first report will be a room that "lags the automation" after Phase 08.
