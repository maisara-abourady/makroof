<!-- Saved by the orchestrator from seat 5's report, 2026-11-22. -->

SEAT 5 POSITION

Corpus: present per the orchestrator (SOURCE_COMMIT c1b171f). I did not open it myself. My corpus citations come through the researcher's dossier (file 3), which read it. Sources read: decider file 1, fact sheets 2 (part 1 and part 2), dossier 3, and BUILD_PLAN AQ10.

# D-W1: re-deriving W_max under (C)

**1. Reading.** This sets the shipped per-emitter work cap and what it does to:
- the synchronous keyless restore;
- the serialised background solves;
- the offline bounce;
- the CI re-pins.

Cues triggered: "find the worst case before the common case" (§10.2), "the result must not depend on runner timing" (criterion 2), and the host's synchronous restore (S4/S5).

**Load-bearing facts:**
- **The gated cubes saturate.** The low-α s0.3 cube's realised work is fixed at 1.26× the pin from ×2 upward. The flutter cube's is fixed at 3.29× (3.52× at CI) from ×4 upward (fact sheet part 2, finding 2).
- **The gated scenes therefore no longer bound anything.** What keeps scaling is:
  - the s = 1 cube (15.9× at ×16);
  - layouts 4 and 5 (T1).
- **Time is linear in realised work.** Single-thread ns per evaluation is flat, with a max/min of 1.02–1.37 (T2).
- **Results do not depend on the pool size.** D4 held in 85 of 85 cells.

**2. Ranking**
- **W-1′ (my addition):** 3 s per scene, one thread, worst OS, on the **costliest capped scene in the reported set** (s = 1 cube, layouts 4/5). The costliest gated scene does not work as the basis: gated scenes saturate, so W-1 as written has no finite answer. **Prefer.**
  - From the 05h CI one-thread cost of 44.7–56.4 ns per scene evaluation (estimator c309589, needs re-measuring), my arithmetic gives 3 s ÷ 56.4 ns = 53.2 M and 3 s ÷ 44.7 ns = 67.1 M scene evaluations. That is ×8.7 to ×11 of 6.10 M, or about 27–34 M per emitter.
- **W-5**, with W-4 recast (see conditions) and my bounce term: **can live with.**
- **W-2:** can live with.
- **W-6**, used as a check beside W-5: can live with. On its own it gives ×1 at the gated scenes, which is ruled out, and no finite answer for the both-near cases (VOV 0.41–0.55 at ×16).
- **W-3:** can live with.
- **W-4** as written: can live with only after it is recast.
- I have no veto on D-W1.

**3–4. Tension, now / later**

| option | now | later | reason |
|---|---|---|---|
| W-1′ | 1 | 1 | A count, so deterministic and independent of instance count. The one-thread CI figure is not on file for the 07c era. Undoing it is a parameter change plus one golden round. Evidence arrives in 07c-2 CI, with the Phase 13 re-check. |
| W-1 literal | 2 | 2 | No finite W at saturated gated scenes, so the choice gets made by accident. |
| W-2 | 1 | 2 | About twice W-1′'s solve. Time to the last final grows by N × solve under the AX38 (i) gate. Under K-a, keyless restores of the s = 1 class go past 2.143 s. Undoing it costs another golden round. |
| W-3 | 2 | 2 | CI pool sizes are 3 or 4 threads; user machines differ (Steam: ≥ 8 cores 57 % on Windows, 87 % on macOS, gamer population, dossier R21). The pool is shared with other instances' builders and with the host. Phase 13 release machines change the basis. |
| W-4 | 2 | 2 | Already violated at the pin: the 96 kHz, 8-instance, 100 m cube settles in 9.9–13.3 s (F6b). That time is bound by synthesis (1.1–1.4 s per emitter), not by the solve, so W-4 yields no W above (A) and runs into condition 3. It also ties a constant to an arbitrary instance count. |
| W-5 | 1 | 1 | Inherits W-4 unless recast. |
| W-6 alone | 2 | 2 | See the ranking. |

**Keyless path**

| path | now | later | reason |
|---|---|---|---|
| K-a | 1 | 2 | See below. |
| K-b | 1 | 1 | See below. |
| K-c | — | — | No proposal on the table to rate. |

- **K-a:**
  - It is what the code already does: one `DiffuseLimits` on every path (F9).
  - The gated projection stays inside the gate. Flutter at ≥ ×4 comes to 15.9–18.2 s on Linux (T5), under the strict 29.1 s.
  - The macOS low-α register entry gains only about 23 ms on a 1.72–2.18 s restore, +1.1 to 1.3 % against its 1.10 growth bound.
  - The debt sits at the scenes the gate does not see. The s = 1 cube projects to 35–40 s at ×8 (T5), past the 14 × 2.143 s convention, on the host's synchronous thread.
- **K-b:**
  - Synchronous work stays bounded whatever W is. From the thread's point of view I prefer it.
  - It needs a separate stage-1 limit and key. That opens a mis-key risk: if the interim E_b were saved under the new key, a reopened project would restore the interim as exact, which breaks NFR-6.
  - Whether the step is audible is Seat 1's question, not mine.

**Sequencing:** I accept deciding the value now and the keyless path after the ABX, with the golden round after both. The condition is that 07c-2 CI measures the restore gate at the new W under K-a. K-a is the code's default, so the gate must be measured, not projected; T5 is local Linux, scaled.

**5. Evidence**
- From the records and code: fact sheet part 1 (F6, F7, F8, F9, F10) and part 2 (T1, T2, T5). The 05h one-thread figures are from estimator c309589 and their current cost is not on file.
- Vorländer §15.3, Table 15.1: update intervals for VR movement, not a solve budget (dossier R29). So W-1, W-2 and W-3 all extend it beyond its conditions.
- VST3 kOffline and the host manuals: an offline render slower than real time is a wait, not a fault (R14–R20). REAPER and Studio One are unverified, so the host-matrix smoke test is needed.
- [Hyp]: factory presets carry no E_b, so every preset load is keyless. Researcher or orchestrator to check from the code.

**6. Conditions of acceptance**
- **W-1 → W-1′:** take the bound over the capped reported set, from the worst of ≥ 3 CI runs. Runner noise is about 1.6× per OS (F1).
  - Add the `05h-cost` one-thread lines and the `[wmax-sweep]` lines to the ci.yml summary grep.
  - Then drop `[benchmark]` from the sweep: about 7.5 min per OS per run is a maintenance cost; run it by hand. Rating then 1/1.
- **W-4 → a check, not a derivation:** the settle time added by the raise at 8 instances, 96 kHz, solve only, ≤ a stated budget. Rating → 1/1.
- **W-3:** pin from one thread, and report the pool figures only. Rating → 1/1.
- **K-a:** print the restore of the s = 1 cube and layouts 4/5 at the new W, as a record, not a gate. If the host-matrix smoke test shows a watchdog or a hang, K-b is the remedy. Later rating → 1.
- **Bounce term (W-5):**
  - Offline waits synchronously for the final at every W (ScenePipeline L478–484, unchanged) and stays bit-identical run to run (AX5).
  - The 3-minute bounce is recorded per OS with no ratio cap. The solve share is 1.6–7.8 % (F7), so ×16 moves the bounce by at most about 1.25× at 48 kHz, an upper bound that assumes linearity.

**Companion items**
- **(b)** The printed `nsPerEval` counts the work twice (F1), so any derivation must use per-scene, one-thread cost. Rename the record field rather than silently changing its meaning. Invariance itself is for Seats 2 and 3.
- **(c)** The S2 form is acceptable if:
  - restores are the worst of ≥ 10 (AQ10 J1);
  - solveRefMs comes from ≥ 3 runs;
  - the three AX48 fingerprint hashes (F10) and the AX38 4c starting-state constants are re-pinned with a CHANGELOG reason, in one commit after the W commit.
- **(d)** Seat 2's. Add a cheap test that the final range is an exact prefix for fixtures whose pilot stopped at n*_max (F11).
- **(e)** Keep `pluginStateVersion` 2; the serialised layout is unchanged.
  - Strengthen `test_plugin_state` L341–369 after the raise: `v2_modified` must load **keyless**, with exactly one synchronous solve and no warning.
  - Under K-b, add a test that a save during the interim stores no E_b under the new key.
- **(f)** No objection. The diffuse problem takes no sample rate or mode (F7, part 2 Method), so one constant across modes costs nothing at the thread. Seat 4 confirms.
- **(g)** Fact only: `main` has false, HEAD has true. The PR diff must show the change. Not otherwise my matter.
- **Instance count:** every option is a per-scene count with no instance cap. Time to the last final and keyless project-load time grow linearly with N under the serialised gate. They are recorded, never capped (FR-3D-5/6).
- **Callback:** B1-b already runs builders without pause (F8), so the worst-case duty in that test does not change with W. Re-run B1-b at the new W with the solve duration printed (missing per F8). Linux CI has no RT priority (RLIMIT_RTPRIO 0), so its overruns do not represent a user host.

**7. Hand-offs**
- Audibility of K-b's interim step: Seat 1.
- The floor at layouts 4/5 and both-near: Seats 1 and 2.
- The prefix check, and E_model or D5: Seat 2.
- Bounce ratio as a workflow matter: Seat 8.
- Factory presets loading keyless [Hyp]: Seats 6 and 2.

**8. Premortem.** W gets pinned from a gated scene that saturates, so it is effectively unbounded. Then a user's project of eight s = 1-class instances restores keyless for more than 10 s on the host's thread. Logic shows a beach ball, and the first beta post reports a "hang on open" before anyone has looked at CI.

# D-W2: AX47 self-ABX and the AX49 L4 design

**1. Reading.** Stimuli must be generated deterministically offline and must be the shipped transition, with no change to any shipped code path. Cues: determinism (criterion 2), and a confound in the player that introduces clicks.

**2–4. Options.** These are mostly Seat 1's; I rank them only on implementation risk.

| option | label | now | later | reason |
|---|---|---|---|---|
| X-1 | prefer | 0 | 0 | One stimulus pair per stimulus; the fewest files to pin. |
| X-5 | prefer | 0 | 0 | Same as X-1 for me. |
| X-2 | can live with | 0 | 1 | More files to pin. |
| X-3 | can live with | 1 | 1 | The stop rule must be enforced by the script, which refuses to unseal later sizes after a non-detection. Ignoring the order inflates the error rate (R1). |
| X-4 | can live with | 1 | 1 | Needs a pre-rendered grid. The trial sequence depends on the answers, so it must be logged. Changing "16 trials" is not my matter. |

**Debt:**
- If the stimulus is not the shipped transition, the result licenses nothing about AQ4. The class (c) round then re-runs, and a person's listening session is lost.
- 08-3 and 09 (binaural, speakers) change the chain, so a re-run is expected. Hash-pinned stimuli make that a planned rerun, not a rebuild.

**Sub-items within my mandate (conditions)**
- **Render the step through the shipped path.** Use render_cli `--realtime-emulation` (RealtimeEngine, AQ4 crossfade, adopted at block start). Use a fixed block and P = 512, with the onset jittered from a seed fixed in the pre-registration (the fade start depends on P, AX31).
- **Any per-band tail-gain flag is validation-only.** It belongs in render_cli/Engine options, in the precedent of `--image-cap` and `--no-air-absorption`, and is off by default.
  - A test shows `src/plugin` never reaches it.
  - With the flag at 0 dB, the output nulls bit-exactly against the shipped render.
- **Pin the stimuli.** Bit-identical per platform (AX5). Generate on one stated OS and record the SHA-256 of every file in the sealed pre-registration. Pin the speech download by SHA-256; LibriSpeech gives MD5 only, so compute SHA-256 on first fetch.
- **No live switching in the player.** Each trial plays whole pre-rendered A, B and X files, so the player cannot add a switch transient as a cue. Run `tools.acoustics clicks` on every file; a flag inside the step window voids the file.
- **Blind answers.** A seeded A/B/X key file is committed by hash before the run, and a script writes the answer file. None of this lives in shipped code.
- **CI listening pack or local build:** either is deterministic, so it is Seat 7's call on the licence (R23–R25). Generating the stimuli costs little CI time.

**7. Hand-offs**
- Paradigm, power and what "not detected" licenses (R4: an anchor is needed): Seat 1.
- Crossfade law and length: Seat 3.
- Level matching and the chain: Seat 4.
- Licence and artifact: Seat 7.

**8. Premortem.** The step gets built in a Python script instead of the shipped engine. The ABX "passes", Phase 08 reveals that the shipped crossfade differs, and the class (c) admission has to be rerun with Maisara's listening time.
