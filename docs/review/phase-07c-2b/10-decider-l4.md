# 10: Decider on AX49 L4: how the stimuli are produced, the scene, A and B, the design, the assertions, the AX49 wording and the sittings

To be saved as `docs/review/phase-07c-2b/10-decider-l4.md`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Outcome:**
- **Production: L-a.** A validation-only `render_cli --provisional-ir` flag, specified exactly below, with AX49's wording amended through /fix-plan.
- **Scene:** a variant of `stone_box` with every band's α scaled by one common factor, giving T60_max 8.0 ± 0.1 s (Seat 2). This is the more sensitive test.
- **A and B:** A is the static provisional IR and B the exact IR, from one plan, both rendered through the real-time engine (Seat 3).
- **Chord, hold, release, wet, anchor:** Seat 1's design, with Seat 3's anchor construction.
- **Assertions:** Seat 3's list plus Seat 1's prefix check.
- **Handover ghost:** printed, not tested, and recorded as debt (07d).
- **Sittings:** L4 is its own block in E's second sitting if that fits K6's 2 h; otherwise a third dated sitting.
- **M3-T:** Seat 1 accepts it on condition the selection grounds are written into the pre-registration. Adopted.
- NEEDS MAISARA: none.

The L4 round does not depend on the interrogator's pending ruling on file 8, except that M3-T is part of that file.

## Convening (file 8)
- **Convened:** Seats 1, 2, 3, 5, 7, and 9 (narrow). All answered.
- **Not required:** Seat 4 (omni, diotic chain), Seat 6 (no user control) and Seat 8 (a validation stimulus). Each scores 0/0.

## Knowledge inventory (new rows)
| K | what | source | status |
|---|---|---|---|
| K25 | `assembleProvisional` is called by `src/plugin/core/ScenePipeline.cpp` L656 and L704. A guard must therefore name the CLI option, not the word "provisional" | Seat 5, from the code | known |
| K26 | render_cli's validation-only flags already follow a gating pattern (`--abx-step-db`, Cli.cpp L274–282, L350–375), and a guard test exists for it (`test_abx_kit.py` L188–197) | Seat 5, from the code | known |
| K27 | Stone variant: Eyring 0.161·2400/(1120·0.0431) = 8.0 s; t_mix,e ≥ 64.7 ms (K20 bound); L_f ≥ 2.561 s; L_p ≥ 2.661 s; L = min(1.5·T60_max, 12) = 12 s | Seat 2; Kuttruff Eq. 4.12 and 5.24 (corpus); L from the code (Engine.h L240) | known as bounds. The realised values are measured and asserted (below) |
| K28 | The 100 m "low-α" cube has T60_max 50.5 s and L_p ≥ L, so it cannot host L4. At T60 8 s the cube needs ᾱ ≈ 0.23–0.29 | Seat 9; AX49 K22; Kuttruff Table 6.1 | known |
| K29 | After an interrupted steady excitation, the decay equals the backward-integrated IR | Kuttruff §8.4 Eq. 8.29; Vorländer §6.4.1 Eq. 6.3 (Seat 3) | known |
| K30 | At the same T60, a smaller volume cuts earlier and louder (t_mix,e grows with √V; K20) | Seats 2 and 9 [Inf] | known in direction. Seat 2 puts the size at about 7 dB for this pair. The real figure is the cut depth, measured below |
| K31 | Whether a −19 dB cut, or a re-onset after silence, is audible | Seats 1 and 3 [Hyp] | uninformed. It is not load-bearing for the choice: L4 is the test of it |

## Tension map (now/later, in the seats' words)
| option | S1 | S2 | S3 | S5 | S7 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|
| **L-a** | 0/1 (→ 0/0 under L-a1) | 1/0 | 1/1 | 1/1 (its conditions keep it at 1/1) | 1/1 | 0/1 | **1** | 9 (8 with L-a1) |
| L-b | 1/1 | 1/1 | 1/**2** | 1/**2** | 1/1 | 0/0 | 2 | 12 |
| L-c | 1/**2** | 1/**2** | 1/**2** | 0/**2** | 1/**2** | 0/1 | 2 | 15 |

The seats' reasons, cell by cell:

**L-a**
- S1: no user output and no reference render carries the cut, "if the flag is off by default". Later, the risk is a flagged render ending up "in a golden or BRAS comparison".
- S2: "A settled clause is amended … no engine change". Later, "Removal is one flag".
- S3: a small src/cli change plus AX49's wording. Later, "condition 6 erodes".
- S5: "About 40 lines … one guard test and one end-to-end test". Later, "every later flag change" keeps the guard green.
- S7: "one more /fix-plan … orchestrator time".
- S9: "a provenance risk".

**L-b**
- S3: "Every rerun maintains a second renderer".
- S5: stimuli come "from a binary that is neither the shipped one nor the CLI" (Debug against Release [Hyp]).

**L-c**
- S1: the remedy "is chosen without data".
- S2: "the 'L4 detects the cut' reversal cannot fire".
- S3 and S5: "a phase of rework".
- S7: class (c) and the W pin are decided without L4. It rises to 3 if the date passes the 08-4 freeze.

## Working (minimum tension)
1. **Bounds.** L-a widens AX49's sentence, which is a board row (D-C9) changeable by a board DECISION. Her recorded decisions are not touched. Nothing is added to `src/sim`.
2. **Veto.** No seat rated any option 3. Seat 7's possible 3 on L-c (if the date slips past 08-4) is conditional.
3. **Worst-off seat.** L-a has a maximum of 1; L-b and L-c have 2. **L-a.**
4. **Compose, sum, reversibility:** not reached. A version of L-b with its conditions met could reach a maximum of 1 (Seats 3 and 5 → 1), but it would not lower the maximum below L-a's 1, so step 4 does not apply.

## DECISION L4-P: the `--provisional-ir` flag (`src/cli` only)
**Behaviour.**
- render_cli builds the room IR with `StagedBuild` on the same plan and at the solve's level as the default, then calls `assembleProvisional()` in place of `assemble()`.
- Every output written in that run uses the provisional IR:
  - `--ir`;
  - `--out` with `--in`, whether offline or with `--realtime-emulation`.
- The flag is off by default, and validation-only.
- **`--provisional-timing <file.json>`** is allowed only with the flag. It writes `provisionalTiming()`: provisional, mixMaxS, t60MaxS, fadeStartS (L_f), endS (L_p), exactS (L), and the per-band T60.
  - This answers Seat 2's request without touching the `--diagnostics` JSON.
- Comments are updated (Engine.h L295–298) to read "render_cli calls it only under `--provisional-ir`".

**Refusals** (exit 1, usage; message names the conflict):
- (r1) `provisionalTiming().provisional` is false (L_p ≥ L). That scene has no provisional (Seats 2 and 3).
- (r2) `--mode` other than `omni` (Seat 5).
- (r3) together with `--diagnostics`, `--ensemble`, `--tail-only`, `--ensemble-emitter`, `--tail-level ax16`, `--switch-scene`, `--switch-every`, `--abx-step-db`, `--abx-stepped-ir`, `--image-cap`, or `--automation` (where present) (Seats 1, 3 and 5).
- (r4) `--provisional-timing` without the flag.

**Tests:**
1. **Guard (Seat 5 iii).** `src/plugin` never names `provisionalIr` or `--provisional-ir`. Only `src/cli/Cli.cpp` reads the option field. This extends the `abxStepDb` guard pattern.
2. **No golden path (Seat 1 L-a1).** A `tools/ci` pytest asserts that `--provisional-ir` appears in no golden-generating code. That covers `tools/ci/update_goldens.py`, `tests/golden/` and the BRAS validation scripts. The string may appear only in `src/cli/Cli.cpp`, its tests, `tools/ci/abx_kit.py` (L4 builder), `tools/ci/test_*.py` and `docs/`.
3. **Default unchanged (Seat 5 iv).** Every existing golden and render test passes unchanged. One added test pins the SHA-256 of a default `render_cli --mode omni --ir` output on `medium_room.json`, built from the same binary that has the flag compiled in.
4. **Determinism (AX5).** The flagged output is bit-identical run to run.
5. **Offline against real-time.** The flagged offline output and the `--realtime-emulation --block 512` output null within −120 dB (Phase 06's criterion).
6. **Refusals.** Each of r1–r4 exits 1. r1 is tested on AX49's L_p ≥ L branch scene (the 100 m low-α cube).
   - This meets Seat 5's intent, "no output differs where there is no provisional", by refusing rather than passing the output through. It is flagged to Seat 5 below.
7. **Plugin parity (Seat 3 item 7).** A JUCE-free `[pipeline]` test: for the L4 scene, the keyless-load interim IR (ScenePipeline L652–656) is bit-identical to the IR that `--provisional-ir --ir` writes.
8. All of these run in CI (`SPATIAL_REQUIRE_RENDER_CLI=1`) on three OSes before any L4 seal.

## DECISION L4-W: AX49 wording (/fix-plan, §6 row)
- **Replace** "Offline renders, bounces in hosts that signal offline, and `render_cli` never use the provisional (AX5, condition 6)."
- **With** "Offline renders and bounces in hosts that signal offline never use the provisional, and neither does `render_cli`, except under the validation-only `--provisional-ir` flag (off by default; omni only; refused with `--diagnostics`, the ensemble, switch, step and image-cap flags, and on scenes with L_p ≥ L; never reached by `src/plugin` and never used for goldens; tests in phase-07c-2b decider file 10). AX5, condition 6."
- **Listening item L4** gains: "scene, stimuli and assertions: phase-07c-2b decider file 10".
- **07d's AX49 reversal list** gains the handover-ghost print (L4-D below) as an input.

## DECISION L4-S: the scene
- **Scene.** `tests/scenes/valid/stone_box.json` (20 × 12 × 10 m, V 2400 m³, S 1120 m²; listener (10, 8, 1.7); emitters (8, 3, 1.7) and (12, 3, 1.7); s 0.1; tailSeed 106), with every band's α multiplied by one common factor k.
  - k starts at 0.844. The builder adjusts it until `--provisional-timing` reports T60_max 8.0 ± 0.1 s (inside the 5 % JND, Vorländer Table 6.1). k is recorded.
  - One factor on every band, so the room's spectral shape is unchanged. It is a stimulus scene, so no engine path is involved (NFR-8).
- **Asserted before the seal:** provisional true, L_p < L, and L_f, L_p, L and the per-band T60 printed.
- **Committed** with the kit: the scene JSON, with its SHA-256 in the manifest.
- **Why not the cube.** The 100 m "low-α" cube cannot host L4 (K28). Raising its α to reach 8 s gives a cut that comes later and lies deeper (K30). The stone variant is the harder test under NFR-1.
  - The cube is not run, to save a family and an extra half-sitting. A non-detection is scoped by the measured cut depth, not by "T60 8 s" (Seat 9).
- **Label** (Seat 9's template, with Seat 2's wording; Seat 9 confirms it before the seal):
  - `label`: "Long-decay test room, hard stone box with uniform absorption, T60_max 8 s; provisional-vs-exact tail test (provisional tail, validation-only flag); not a validated preset"
  - Detail lines:
    1. 20 × 12 × 10 m (V 2400 m³, S 1120 m²); α = k × stone_box's per band, on every face; s 0.1 (early part specular only, AX21); tailSeed 106; 48 kHz; emitters 5.39 m from the listener.
    2. T60 per band (the engine's Eyring with air absorption); T60_max [8.0] s in band [b]; T60 at 1 kHz [ ].
    3. D/R at 1 kHz [measured], against [ ] dB at r/r_c [ ] (Kuttruff Eq. 5.44, Sabine A [ ] m²). ᾱ ≈ [0.04–0.07] is small, so §5.6's ᾱ caveat does not apply.
    4. t_mix,e,max [ ], L_f [ ], L_p [ ], L [12.0] s.
    5. **Cut depth**, per band: 10·log10(E_B[L_f, L)/E_B[0, L)), measured on B's IR, with the chord's band energy beside it.
    6. The early reflections are identical in A and B (shared ISM) and are not the variable under test.
    7. "Stimulus scene, not a room prediction."
  - Class line: "long-decay, [Seat 9's D/R class] (heard D/R [ ] dB), cut [ ] dB in the T60_max band"
- **Scope of the record** (Seat 9): "not detected" covers "a cut ≥ [measured] dB below the full-IR energy in the T60_max band, at T60_max 8 s, by one listener". It is never worded "inaudible at T60 8 s".

## DECISION L4-D: the design and the assertions
**A and B** (Seat 3):
- A is the provisional IR, from `--provisional-ir`.
- B is the exact IR from the same plan (the default render).
- Both are rendered by `render_cli --realtime-emulation --block 512 --partition 512`, like AX47.
- The ABX compares the two static IRs. The live handover is not in the stimulus.

**Chord** (Seat 1):
- A deterministic additive synthesis, versioned in the kit, with no licence:
  - an open voicing C2–G2–C3–E3–G3–C4, equal-tempered;
  - harmonic partials up to 8 kHz with a −3 dB/octave tilt;
  - no vibrato;
  - a 50 ms onset and a 10 ms raised-cosine release.
- Its energy in each band is printed.

**Timing:**
- Hold H = max(L_p, 0.5·T60_max), which is 4 s here.
- One release per file, then at least L + 0.5 s of silent input.
- The whole of the exact render's decay is inside the file (asserted). A and B are the same length.

**Fully wet:**
- The input is convolved with the whole room IR (direct, early and tail). No dry path, no tail-alone.
- Diotic. No normalisation.
- One fixed gain for every file, recorded; peak ≤ −3 dBFS (Seat 1; stricter than item 10).

**Trials** (AX49, item 14):
- 16 scored trials, detected at ≥ 12/16 (chance 0.038; power 0.63 at p = 0.75). Its own family.
- 6 anchor trials (3 up, 3 down) interleaved at seeded positions, passing at ≥ 5/6. The anchor is B against B with the tail stepped ±3 dB (`--abx-step-db ±3 --abx-step-sample 0`), on the L4 scene and chord (Seats 1 and 3).
- Blocks of 22 trials, with a break after trial 11.
- Familiarisation includes a labelled A/B pair.
- No 0.5 dB block.
- The record wording follows item 13, plus L4-S's scope.

**Assertions on every stimulus** (Seat 3's list and Seat 1's check; all asserted unless marked print):
1. The provisional flag is true in A's manifest. The flag and "provisional tail, validation-only flag" are printed (Seat 9).
2. A and B agree bit for bit before the earliest tail crossfade start.
3. Prefix: 10·log10(E(A − B)/E(B)) ≤ −18.27 dB per emitter and band over [t_mix,e, L_f − h) (AX47 (b); Seat 1).
4. The per-band A/B energy over [t_mix,e,max + 2.5 ms, L_f) equals AX47 (b)'s predicted step within 0.05 dB (Seat 3).
5. A carries zero energy from L_p onward.
6. B's length is L.
7. Decay from t_mix,e,max to L_f is ≥ 18.7 dB in every band.
8. B's energy share past L_f is ≤ 0.0134 in every band.
9. Print: the held-portion A/B level difference per band.
10. Silence after release ≥ L of input.
11. Peak ≤ −3 dBFS.
12. Two builds are bit-identical. Form-(b)-style checks do not apply, because L4 has no crossfade in the stimulus.
13. **Handover-ghost print** (Seat 3 item 9, print only): from B's backward-integrated curve, per band, the re-onset level at a handover time of release + L_p + {0, 1, 2, 5} s.

**Not adopted now:** Seat 1's optional parameters for fade length and the L_f fraction. They go to 07d as a follow-up, and are used only if L4 detects.

## DECISION L4-T: sittings (Seat 7)
- K6 is redone on the sealed L4 stimuli. Its estimate from the seats is about 18–20 min of audio per block [Hyp].
- L4 runs as its own block with its own anchor, in E's second sitting, if that sitting plus L4 stays within 2 h.
- Otherwise a third dated sitting goes into the session brief before any seal.
- L4's seal comes before the session, together with E's.

## M3-T (Seat 1's condition)
- The pre-registration states the grounds for the choice: MA01_01 + MA01_02 were fixed for their measured assertions (Q5, form (b), nulls), before any blind result.
- MA is recorded as an adult speaker from TSP's documentation. The children CA and CB are excluded (abx_kit L737).

## Load-bearing claims
- **L4-L1** (map): L-a has a maximum of 1; L-b and L-c have 2 (Seat 3 L-b later, Seat 5 L-b later, five seats' L-c later).
- **L4-L2** (K27): 0.161·2400/(1120·0.0431) = 8.0 s; L_f ≥ 0.0647 + 0.312·8 = 2.561 s; L = 12 s. All are measured and asserted before the seal.
- **L4-L3** (K28): the low-α cube has L_p ≥ L, so it cannot be used.
- **L4-L4** (from the code, K25 and K26): the guard must name the option field; the flag's gating pattern already exists.
- **L4-L5** (AX49 K17′): the energy past L_f is ≤ e^(−4.312) = 0.0134.

## Future-debt register
| seat | commits | undo cost | evidence | repaid when |
|---|---|---|---|---|
| 3 | A validation flag calling `assembleProvisional` from render_cli; condition 6 could erode | Delete one flag | `[pipeline]` offline-bypass test; default goldens unchanged | Tests 1–3 green on three OSes |
| 3 | Handover ghost (re-onset after silence at handover) is not covered by AX47 (b) or by the ABX | A 07d remedy round | Researcher: audibility of a tail re-onset at about −20 dB; 07d | Ghost print recorded; 07d rules on it, and Seat 1 says whether it needs its own ABX |
| 5 | Every later flag change keeps the guard green | Delete one option | Default-output hash (test 3) | Each CI run |
| 7 | render_cli carries a provisional path; possibly a third sitting | Flag deletion; one sitting | K6 on L4 | Per-sitting plan in the brief |
| 9 | Provenance: render_cli makes a non-room IR | Label line | Manifest | "provisional tail, validation-only flag" printed |
| 1 | (Later 0 under L-a1) | — | — | — |

## Strongest objection
- **Seats 7 and 9 prefer L-b.** It needs no AX49 amendment, and its stimuli never come from the product tool.
  - L-a still wins on the worst-off seat. L-b leaves Seats 3 and 5 at 2 later: a second renderer to maintain, and stimuli from a binary that is neither the shipped one nor the CLI.
  - L-b's conditions could lower those to 1, which would tie L-a's maximum. L-a would then still lead on the sum and on reuse (07d, 08-3).
- **Seat 5's test (iv) asked for "bit-identical to the default" on L_p ≥ L. This decision refuses there instead (Seats 2 and 3).** If Seat 5 holds that a refusal does not meet its condition, its L-a cell becomes 1/2. The maximum would then be 2, tied with L-b. That is the reversal check for the interrogator.

**Confidence: medium.** K31 is open, and the label's bracketed values are measured later.

**Reversal:**
- Seat 5 rejects refusal r1;
- the stone variant fails any pre-seal assertion (then the next-smallest valid scene at T60 8 s with L_p < L, re-convened);
- test 7 (plugin parity) fails. The stimulus would then not be what the plugin plays, and L4 returns to the board.

## Summary
| id | decision | state | worst-off (cell) | sum | confidence | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| L4-P | `--provisional-ir` (+ `--provisional-timing`), refusals r1–r4, tests 1–8 | proposed | 1 (S2, S3, S5, S7) | 8 | medium | NFR-1, NFR-8 | — (code) | Seat 5 rejects r1; parity fails |
| L4-W | AX49 wording, via /fix-plan with a §6 row | proposed | 1 | — | high | NFR-1 | — | — |
| L4-S | stone_box with α × k, T60_max 8.0 ± 0.1 s; label; cut-depth scope | proposed | — (Seat 9 confirms the label) | — | medium | NFR-1, NFR-8 | Eq. 4.12, 5.24, 5.44; Table 6.1 | pre-seal fail |
| L4-D | A/B static; Seat 1's chord and timing; anchor; assertions 1–13 | proposed | 0 | — | medium | NFR-1 | Eq. 8.29, 6.3, 6.4 | — |
| L4-T | own block in E's sitting 2, or a third dated sitting | proposed | 1 (S7) | — | high | L101 | — | K6 on L4 |
| M3-T cond. | selection grounds pre-registered | proposed | 0 | — | high | NFR-1 | — | — |

**Challenges to settled decisions:** AX49's render_cli clause, a board row (D-C9), is widened by L4-W. It is not one of Maisara's recorded decisions.

## Decided for Maisara
- **L4-P and L4-W.** The listening test of the shortened "provisional" reverb, which plays while a large room loads, is built with the same tool as the main test. It uses a switch that is off by default, that the plugin can never reach, and that no reference file ever uses.
  - NFR-1: L4 is the listening test that AX49's reversal reads.
  - NFR-8: nothing changes in the engine.
  - Other options:
    - L-b (separate harness): strains NFR-1's evidence chain, because the stimuli come from a binary that is not the shipped one.
    - L-c (later): strains NFR-1, because class (c) and the W pin would be decided without L4.
  - Seats 7 and 9 give up their preferred harness.
  - Amends nothing of hers. It amends AX49, a board row.
- **L4-S and L4-D.** The test uses a small, very reverberant stone room, where the cut is easiest to hear, and a held chord released into a full 12 s of decay. A non-detection is recorded only for the measured depth of the cut. NFR-1, NFR-8. Amends nothing.
- **L4-T.** About 20 min, inside E's second sitting if it fits; otherwise a third dated sitting. L101 ("must stay usable" does not apply; this is scheduling). It is a person's action for her.

**NEEDS MAISARA:** none. The person's action is Raise item 2: possibly a third short sitting.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/9-seat1-l4.md
- /home/user/makroof/docs/review/phase-07c-2b/9-seat2-l4.md
- /home/user/makroof/docs/review/phase-07c-2b/9-seat3-l4.md
- /home/user/makroof/docs/review/phase-07c-2b/9-seat5-l4.md
- /home/user/makroof/docs/review/phase-07c-2b/9-seat7-l4.md
- /home/user/makroof/docs/review/phase-07c-2b/9-seat9-l4.md
