**Pattern** (`grep -rnPI`, case as written, plus a second pass for `Depends on:`, `until 08/09`-style and bare remainder names): `[Pp]hases?[- _]?(0?7c|0?8|0?9|1[0-3])([.]md)?\b|\b(07c|08|09|1[0-3])b\b|\b(07c|08|09|1[0-3])-[1-5]b?\b|[Pp]hases? (0?[0-9]|1[0-3])[–-](1[0-3]|0?9|0?8)\b|depends on:?[^.\n]*\b(07c|08|09|1[0-3])\b|\b(08|09|1[0-3])/(08|09|1[0-3])\b` · **Counts:** item references 251 (section A rows; 251 resolved), whole-phase references 117 (section B line occurrences: 101 umbrella, 16 phase-09), UNRESOLVED 0.

# References to phases 07c, 08, 09, 10, 11, 12 and 13 after the split

Search: every tracked text file except `docs/corpus/`, `docs/review/`, `docs/sessions/`, `.venv/`, `build/`, `.git/`
(and `__pycache__`). In the split phase files themselves (`phase-07c*.md`, `phase-08*.md`, `phase-10*.md`,
`phase-11*.md`, `phase-12*.md`, `phase-13*.md`), only references to a *different* phase are listed, plus remainder
names; a split file's references to its own phase are the split's own text and are covered by its umbrella table.
Resolution source: the "Where the original items went" table (and "Notes from the split") of each umbrella
(`docs/phases/phase-07c.md`, `-08.md`, `-10.md`, `-11.md`, `-12.md`, `-13.md`). Phase 13 uses its umbrella's five-way
numbering (13-1…13-5), not `map-13.md`. Labels in "resolves to" are the umbrella's labels (e.g. 08 AC3, 13 S9).

Two false positives of the pattern are dropped: `CLAUDE.md:298` ("never depends on `tailSeed` (AX40, Maisara
2026-11-10)") and `.claude/skills/review-phase-pr/references/metrics-and-validation-data.md:674` ("EDT depends on the
first 10 dB").

## A. Item references (resolve to a sub-phase)

| file:line | reference text | resolves to |
|---|---|---|
| `.claude/skills/review-phase-pr/references/binaural-and-stereo.md:50` | "Phase 08 defines **+90° azimuth = left** (listener's left ear leads)" | 08-2 (08 AC3 ITD sign; scope 4 `ListenerFrame`) |
| `…/binaural-and-stereo.md:310` | "Phase 08's '≤ 30 µs per 1° step' criterion" | 08-1 (08 AC4) |
| `…/binaural-and-stereo.md:315` | "0.65–0.75 ms (phase-08 acceptance …)" | 08-2 (08 AC3) |
| `…/binaural-and-stereo.md:322` | "Phase 08's '>6 dB averaged over 2–8 kHz at ±90°'" | 08-2 (08 AC3) |
| `…/binaural-and-stereo.md:324` | "Median plane … (phase-08: \|ITD\| < 20 µs, \|ILD\| < 1 dB at 0°)" | 08-2 (08 AC3) |
| `…/binaural-and-stereo.md:340` | "10–30% reversals … this is the Phase 08 'risk'" | 08 R1: shared, umbrella + 08-2 + 08-3 |
| `…/binaural-and-stereo.md:384` | "Continuity criteria (phase-08): per 1° azimuth step …" | 08-1 (08 AC4) |
| `…/binaural-and-stereo.md:416` | "Phase 08's ±1 dB energy test" | 08-3 (08 AC6) |
| `…/binaural-and-stereo.md:467` | "Target from the HRTF set itself (Phase 08): IC(f) = …" | 08-3 (08 scope 5b) |
| `…/binaural-and-stereo.md:488` | "Tolerance in phase-08: ±0.1 for 125 Hz–4 kHz" | 08-3 (08 AC5) |
| `…/binaural-and-stereo.md:503` | "Direction clustering (Phase 08: bins of ~2° above order 3 …)" | 08-4 (08 scope 5a grouping rule, D-PS2). Note: the plan's rule is conditional ("No 2° grouping until the Phase 08 benchmark shows it is needed"), as it was before the split |
| `…/convolution-and-movement.md:56` | "worst-case staleness budget 100 ms (phase-10 acceptance)" | 10-2 (10 AC8) |
| `…/convolution-and-movement.md:410` | "Hard-switch negative control (phase 10 `MAKROOF_TEST_HARD_SWITCH`)" | 10-3 (10 scope 5) |
| `…/convolution-and-movement.md:450` | "Design facts from AQ4/phase 10: builder on a background thread, at most one rebuild per 20 ms" | 10-2 (10 scope 3) |
| `…/convolution-and-movement.md:462` | "(phase 10 text)" (no catch-up builds) | 10-2 (10 scope 3) |
| `…/convolution-and-movement.md:472` | "can exceed the budget at high orders in large rooms (the phase-10 risk)" | 10-2 (10 R1) |
| `…/convolution-and-movement.md:482` | "Tail cache key (phase 10: 'room dimensions, materials, mode, seed, sample rate')" | 10-1 (10 scope 2) |
| `…/convolution-and-movement.md:491` | "phase 10 keeps the tail and 're-runs energy matching'" | 10-1 (10 scope 2) |
| `…/convolution-and-movement.md:792` | "positions passed to the builder unsmoothed (phase 10 rule)" | 10-2 (10 scope 4) |
| `…/convolution-and-movement.md:805` | "a 40 Hz tone and a low-band detector variant as phase 10's risk note asks" | 10-3 (10 R2) |
| `…/phase-checklists.md:276` | "early accumulation reusing the Phase 08 structure" | 08-2 (08 scope 5a) |
| `CLAUDE.md:229` | "binaural/stereoSpeakers stay a dry stub until 08/09" (`render_cli --mode`) | 08-2 (08 scope 7, `--mode binaural`); phase-09 (whole) |
| `docs/THIRD_PARTY.md:11` | "revenue cap must be checked before the first paid release (Phase 13)" | 13-5 (13 S5) |
| `docs/THIRD_PARTY.md:12` | "add it to the product's licence notices before release (Phase 13)" | 13-5 (13 S5) |
| `docs/THIRD_PARTY.md:13` | "add them to the product's licence notices before release (Phase 13)" | 13-5 (13 S5) |
| `docs/THIRD_PARTY.md:51` | "The HRTF dataset arrives in Phase 08" | 08-1 (08 scope 1–2) |
| `docs/THIRD_PARTY.md:67` | "`docs/phases/phase-08.md` scope 1" | 08-1 (08 scope 1) |
| `docs/THIRD_PARTY.md:68` | "the data is pinned in Phase 08 session 1" | resolved: pointer added after "Phase 08 session 1": "[= sub-phase 08-1 since the 2026-11-10 split]" |
| `docs/contract/README.md:249` | "A UI resize that keeps absolute positions is a Phase 11 gesture" | 11-2 (11 scope 5) |
| `docs/contract/README.md:265` | "Phases 08/09; until then the stored `render.outputMode` is kept" | 08-3 (08 scope 6, sentences 2–3); phase-09 (whole) |
| `src/sim/Engine.h:94` | "benchmark / Phase 10 proxy only: precomputed unit decays" | 10-1 (10 scope 2) |
| `src/sim/Engine.cpp:166` | "the unit decay stays independent of positions (Phase 10)" | 10-1 (10 scope 2) |
| `src/sim/ism/ImageSources.h:35` | "arrivalDirection … (Phases 08/09)" | 08-2 (08 scope 5a); phase-09 (whole) |
| `src/sim/tail/NoiseTail.h:5` | "Unit decay (the object Phase 10 caches …)" | 10-1 (10 scope 2) |
| `src/sim/tail/NoiseTail.h:44` | "Phase 08 hook: per-output seed offset for decorrelated tails" | 08-3 (08 scope 5b) |
| `tests/unit/test_noise_tail.cpp:244` | `"per-output seed offset for Phase 08"` | 08-3 (08 scope 5b) |
| `src/plugin/CMakeLists.txt:39` | "splash screen … (licence check in Phase 13)" | 13-5 (13 S5) |
| `src/plugin/PluginProcessor.h:15` | "the omni room IR (mono preview …) until Phase 08" | 08-3 (08 scope 6, sentence 2, plugin `outputMode`) |
| `src/plugin/PluginProcessor.h:69` | "Warning flags (shown by the UI from Phase 11)" | 11-1 (11 scope 1f status strip; AX34 warning scope 7) |
| `src/plugin/PluginProcessor.cpp:214` | "The generic editor is enough until Phase 11." | 11-1 (11 scope 4) |
| `src/plugin/core/ScenePipeline.h:28` | "EqualGain (AX18 placeholder until Phase 10)" | 10-3 (AX18 law set there) |
| `src/plugin/core/ScenePipeline.cpp:68` | "outputMode is ignored until 08/09" | 08-3 (08 scope 6, sentences 2–3); phase-09 (whole) |
| `src/cli/Cli.cpp:259` | `"--automation is not implemented until Phase 10"` | 10-2 (10 scope 1) |
| `src/cli/Cli.cpp:623` | `"--automation not implemented until Phase 10"` | 10-2 (10 scope 1) |
| `tests/unit/test_cli.cpp:220` | `"not implemented until Phase 10"` | 10-2 (10 scope 1) |
| `tools/acoustics/tests/test_render_cli.py:57` | `"not implemented until Phase 10"` | 10-2 (10 scope 1) |
| `src/module3d/ParameterMap.h:14` | "output_mode … (wired in Phases 08/09" | 08-3 (08 scope 6, sentences 2–3); phase-09 (whole) |
| `src/module3d/ParameterMap.cpp:127` | "output_mode is not applied in Phase 07 (wired in Phases 08/09)" | 08-3 (08 scope 6, sentences 2–3); phase-09 (whole) |
| `tests/unit/test_hybrid_ir.cpp:325` | "the unit decays come from the cache, as in Phase 10" | 10-1 (10 scope 2) |
| `tests/unit/test_hybrid_ir.cpp:581` | "A rebuild from cached unit decays (the Phase 10 proxy AQ10 times)" | 10-1 (10 scope 2) |
| `tools/validation/tests/test_phase05b2_data.py:59` | "J1 L5 / phase-12 Trigger 2: four … halls" | 12-2 (12 scope 7, Hall presets and J1) |
| `tools/validation/phase05b2_asrun/README.md:15` | "J1 / phase-12 Trigger 2" | 12-2 (12 scope 7) |
| `docs/phases/phase-00.md:26` | "licence check happens in Phase 13" | 13-5 (13 S5) |
| `docs/phases/phase-02.md:38` | "'not implemented until Phase 10'" | 10-2 (10 scope 1) |
| `docs/phases/phase-03.md:34` | "Phase 08 needs it [arrival direction], and stereo-speaker mode needs it in Phase 09" | 08-2 (08 scope 5a); phase-09 (whole) |
| `docs/phases/phase-04.md:120` | "Phase 10 caches, so keep it as a separate value" | 10-1 (10 scope 2) |
| `docs/phases/phase-04.md:154` | "which Phase 10's cache relies on" | 10-1 (10 scope 2) |
| `docs/phases/phase-04.md:187` | "Phase 08 will need decorrelated tails per ear" | 08-3 (08 scope 5b) |
| `docs/phases/phase-04.md:374` | "Phase 10 gates the maximum dip … (full statement in phase-10)" | 10-3 (10 AC7 position-fade gate) |
| `docs/phases/phase-05.md:585` | "Phase 13's beta decision lists 'AQ9 met in x/y'" | 13-5 (13 D4) |
| `docs/phases/phase-05.md:620` | "required before the Phase 13 beta decision (BUILD_PLAN §3 F2)" | 13-5 (13 D4) |
| `docs/phases/phase-05b.md:27` | "the Phase 10 tail cache" | 10-1 (10 scope 2) |
| `docs/phases/phase-05b.md:125` | "≤ … −1.0 dB (Vorländer Eq. 4.14), the Phase 10 bound" | 10-3 (10 AC7) |
| `docs/phases/phase-05b2.md:161` | "Phase 08 gets E_b and t_mix,e only (5.3)" | 08-3 (08 scope 5d) |
| `docs/phases/phase-05b2.md:192` | "position-only rebuilds as in the Phase 10 tail cache" | 10-1 (10 scope 2) |
| `docs/phases/phase-05b2.md:228` | "Phase 10's mid-fade gate is not this yardstick" | 10-3 (10 AC7) |
| `docs/phases/phase-05b2.md:230` | "phase-10 puts its limit at ≳ 8.5 dB" | 10-3 (10 AC7) |
| `docs/phases/phase-05b2.md:234` | "defers any budget to Phase 13" (memory) | 13-1 (13 S1, memory budget) |
| `docs/phases/phase-05b2.md:236` | "cross-referenced to Phase 13, with the Phase 07 baseline" (memory) | 13-1 (13 S1) |
| `docs/phases/phase-05b2.md:248` | "Phase 08 does not use it for directional output, it receives E_b and …" | 08-3 (08 scope 5d) |
| `docs/phases/phase-05b2.md:251` | "decide what Phase 08 receives" | 08-3 (08 scope 5d) |
| `docs/phases/phase-05b2.md:372` | "no level jumps (Phase 10 will gate this" | 10-3 (10 AC7) |
| `docs/phases/phase-05b2.md:402` | "(iii) … re-runs phase-08 item 8" | 08-4 (08 scope 8) |
| `docs/phases/phase-05b2.md:403` | "(iv) the Phase 08 listening items on concentrated absorption marked provisional" | 08-3 (08 L items; AX37 (iv) binds 08-3) |
| `docs/phases/phase-05b2.md:409–411` | "Q2a (C), phase-13 scope 13 … *Note (2026-11-10): Q2a (C) is now its own phase, `phase-07c.md`, not phase-13 scope 13*" | phase-07c umbrella (in-line note; the label "phase-13 scope 13" itself now resolves to 13-2, AX41 limits) |
| `docs/phases/phase-05d.md:41` | "If she defers, record 'deferred' …; Phase 13 raises it again" (commissioning decision) | 13-1 and 13-5 (13 R1) |
| `docs/phases/phase-05h.md:48` | "Phase 08 gets E_b and t_mix,e only (5.3)" | 08-3 (08 scope 5d) |
| `docs/phases/phase-05h.md:79` | "re-runs phase-08 item 8 (scope 10)" | 08-4 (08 scope 8) |
| `docs/phases/phase-05h.md:95` | "(also phase-13 'Raise with Maisara' item 3)" | 13-1 and 13-5 (13 R3) |
| `docs/phases/phase-05h.md:170` | "AX38 4c / phase-07c condition 2" | 07c-1 |
| `docs/phases/phase-05h.md:220` | "Only if Phase 08 went first" | 08-4 (08 "Notes from the split": means 08-4 ran before 05h was `done`, D-PS1) |
| `docs/phases/phase-05h.md:221` | "re-run phase-08 item 8. This also carries phase-08 scopes 9 and 10" | 08-4 (08 scope 8; scopes 9, 10) |
| `docs/phases/phase-05h.md:223` | "(phase-08 scope 9)" | 08-4 |
| `docs/phases/phase-05h.md:224` | "(phase-08 scope 10)" | 08-4 |
| `docs/phases/phase-05h.md:227` | "the same rule applies to Phase 08's goldens" | 08-4 (08 scope 7 goldens) |
| `docs/phases/phase-05h.md:229` | "(phase-07c condition 8)" | 07c-2 |
| `docs/phases/phase-05h.md:267–269` | "Only if Phase 08 went first (scope 10): … phase-08 item 8 re-run … (phase-08 scopes 9 and 10)" | 08-4 |
| `docs/phases/phase-05h.md:283` | "no level jumps (Phase 10 will gate this" | 10-3 (10 AC7) |
| `docs/phases/phase-05h.md:286` | "if Phase 08 went before this phase, its listening items on …" | 08-3 (08 "Notes from the split": applies if 08-3 ran before 05h was `done`) |
| `docs/phases/phase-06.md:18` | "(Phase 09 mode switch, Phase 10 large jumps)" | phase-09 (whole); 10-3 (AX18 equal-power for large jumps) |
| `docs/phases/phase-06b.md:35` | "`docs/phases/phase-13.md` scope 1" | 13-1 (13 S1) |
| `docs/phases/phase-06b.md:52` | "whether `phase-13.md` scope 1 and item 9 … are restated" | 13-1 (S1); 13-3 (S9) |
| `docs/phases/phase-06b.md:145` | "Non-uniform partitioning …: `docs/phases/phase-13.md` scope 1" | 13-1 (S1; non-uniform partitioning → `13-1b`) |
| `docs/phases/phase-06b.md:146` | "MSVC/ARM64 flush-to-zero guard: `phase-13.md` scope item 8" | 13-3 (13 S8) |
| `docs/phases/phase-06b.md:147` | "Real-hardware macOS small-buffer timing: `phase-13.md` scope item 9" | 13-3 (13 S9) |
| `docs/phases/phase-06b.md:150` | "`docs/phases/phase-08.md` scope item 8" | 08-4 (08 scope 8) |
| `docs/phases/phase-06b.md:151` | "`docs/phases/phase-10.md` scope item 8" | 10-2 (10 scope 8) |
| `docs/phases/phase-07.md:36` | "Phase 08 changes the render of 07-era states by design" | 08-3 (08 scope 6, plugin `outputMode`) |
| `docs/phases/phase-07.md:54` | "A UI resize that keeps absolute positions is a Phase 11 gesture" | 11-2 (11 scope 5) |
| `docs/phases/phase-07.md:61` | "wired in 08/09" (output mode) | 08-3 (08 scope 6); phase-09 (whole) |
| `docs/phases/phase-07.md:83` | "Reversal: Phase 10 traversal scenarios or Phase 08 listening" | 10-2 (10 scope 6 scenario suite); 08-3 (08 L items) |
| `docs/phases/phase-07.md:197` | "the AX18 placeholder …; Phase 10 sets the law" | 10-3 |
| `docs/phases/phase-07.md:225` | "a visible warning flag (shown by the UI in Phase 11)" | 11-1 (11 scope 1f) |
| `docs/phases/phase-07.md:238` | "automation smoothing beyond basic rebuild + crossfade (10) … presets (12)" | 10-2 (10 scope 4); 12-2 |
| `docs/phases/phase-07.md:287` | "zipper noise is acceptable here; Phase 10 removes it" | 10-2 (10 scope 4) |
| `docs/phases/phase-09.md:26` | "Reuse the Phase 08 accumulation structure" | 08-2 (08 scope 5a) |
| `docs/phases/phase-09.md:75` | "Set expectations in UI text in Phase 11." | 11-1 (cited in `phase-11-1.md:23`, scope 1e) |
| `docs/BUILD_PLAN.md:29` | "handed off to phase-13 scope item 9 (real hardware)" | 13-3 (13 S9) |
| `docs/BUILD_PLAN.md:29` | "non-uniform partitioning planned for Phase 13" | 13-1 (S1) → `13-1b` |
| `docs/BUILD_PLAN.md:30` | "phase-13 item 9 remedy no longer P = 256" | 13-3 (S9; a miss opens `13-1b`) |
| `docs/BUILD_PLAN.md:30` | "phase-08 item 8 limit note" | 08-4 (08 scope 8) |
| `docs/BUILD_PLAN.md:32` | "must be `done` before Phase 13's beta, or phase-13 scope 13's versioning fallback recorded" | 13-5 (13 D4 beta decision); 13-2 (13 S13) |
| `docs/BUILD_PLAN.md:32` | "Brought ahead of Phase 08's golden freeze if Phase 08's heaviest mode fails the restore gate" | 08-4 (08 scope 7 goldens, scope 10) |
| `docs/BUILD_PLAN.md:53–57` | "(phase-13 header, in full)" / "the phase-13 header in full" / "the versioning fallback of scope 13" | 13 H: umbrella (shared); scope 13 → 13-2 |
| `docs/BUILD_PLAN.md:54` | "S13 = phase-13 scope 13, in phase-13-2.md" | 13-2 |
| `docs/BUILD_PLAN.md:69` | "Check the current JUCE licence tiers … (Phase 13 checklist)" | 13-5 (13 S5) |
| `docs/BUILD_PLAN.md:78` | "dataset-agnostic header; phase-08 scope 1–3" | 08-1 |
| `docs/BUILD_PLAN.md:78` | "Fallback: MIT KEMAR under the conditions in phase-08 scope 1" | 08-1 |
| `docs/BUILD_PLAN.md:78` | "re-entry condition in phase-08 scope 1" | 08-1 |
| `docs/BUILD_PLAN.md:108` | "equal-gain … (placeholder until Phase 10, AX18)" | 10-3 |
| `docs/BUILD_PLAN.md:108` | "settled by AX33 (Phase 07); Phase 10 confirms or replaces it" | 10-2 (10 scope 8) |
| `docs/BUILD_PLAN.md:114` | "non-uniform partitioning, phase-13 scope 1 (13b) [now `13-1b`, per the phase-13 umbrella]" | 13-1 (S1) → `13-1b` (already annotated) |
| `docs/BUILD_PLAN.md:114` | "the Phase 10 tail cache hits" | 10-1 (10 scope 2) |
| `docs/BUILD_PLAN.md:114` | "macOS arm64 and Windows x64 recorded in Phase 13" | 13-1 (13 C2 sentence 1) |
| `docs/BUILD_PLAN.md:114` | "every output mode from Phase 08" (AQ10 benchmark) | 08-4 (08 AC12 sentences 3–4) |
| `docs/BUILD_PLAN.md:114` | "It is not optimised before Phase 13" | 13-1 (13 S1) |
| `docs/BUILD_PLAN.md:114` | "from Phase 08 on, the gate measures the heaviest output mode … if Phase 08's heaviest-mode build … before Phase 08's goldens are frozen" | 08-4 (08 scope 10; scope 7 goldens) |
| `docs/BUILD_PLAN.md:114` | "re-checked in phase-13" (Q2a/Q2b limits) | 13-2 (13 S13) |
| `docs/BUILD_PLAN.md:131` | "including `--automation` until Phase 10" | 10-2 (10 scope 1) |
| `docs/BUILD_PLAN.md:137` | "the output-mode switch (Phase 09), large jumps (Phase 10)" | phase-09 (whole); 10-3 (AX18 law) |
| `docs/BUILD_PLAN.md:137` | "as a placeholder until Phase 10 sets the law and its gate" | 10-3 |
| `docs/BUILD_PLAN.md:141` | "Phase 13 then re-derives i₀ after optimisation" (twice) | 13-2 (13 C2 sentence 3) |
| `docs/BUILD_PLAN.md:141` | "Phase 10 reports that largest dip … and gates the total output" | 10-3 (10 AC6) |
| `docs/BUILD_PLAN.md:141` | "full statement in phase-10" | 10-3 (10 AC6/AC7) |
| `docs/BUILD_PLAN.md:141` | "if it fails, Phase 10 proposes a time-segment-split crossfade as a new AX" | 10-3 (10 AC7) |
| `docs/BUILD_PLAN.md:150` | "the 35 ms head-rotation row is deferred to phase-08 item 8" (twice) | 08-4 (08 scope 8) |
| `docs/BUILD_PLAN.md:150` | "Open for Phase 08: … to be checked in Phase 08" | 08-4 (08 scope 8) |
| `docs/BUILD_PLAN.md:150` | "so phase 08 applies this row's reversal clause if the row applies" | 08-4 (08 scope 8) |
| `docs/BUILD_PLAN.md:152` | "Phase 10 confirms or replaces it" (AX33) | 10-2 (10 scope 8) |
| `docs/BUILD_PLAN.md:153` | "the warning flag is set (shown in Phase 11)" | 11-1 (11 scope 7) |
| `docs/BUILD_PLAN.md:153` | "No resampling in v1 (Phase 13 decides)" | 13-4 (13 S11) |
| `docs/BUILD_PLAN.md:154` | "Before the Phase 08 goldens are frozen a converter re-run is a parameter change" | 08-4 (08 scope 7 goldens) |
| `docs/BUILD_PLAN.md:154` | "the head chosen in Phase 08 is frozen" | 08-1 (08 scope 1) |
| `docs/BUILD_PLAN.md:156` | "Phase 08 receives E_b and t_mix,e per emitter through `TailMatch` … (phase-08 scope 5 unchanged)" | 08-3 (08 scope 5d); scope 5 lead-in 08-2 + 08-3 |
| `docs/BUILD_PLAN.md:156` | "(iii) 05h … re-runs phase-08 item 8" | 08-4 |
| `docs/BUILD_PLAN.md:156` | "(iv) the Phase 08 listening items on concentrated absorption are marked provisional" | 08-3 (08 L items) |
| `docs/BUILD_PLAN.md:156` | "Phase 12 checks each outdoor preset with branch (a)" | 12-2 |
| `docs/BUILD_PLAN.md:157` | "phase-13 scope 1 owns the memory budget" | 13-1 |
| `docs/BUILD_PLAN.md:157` | "under Bitwig's per-plugin sandbox … until Phase 13 measures it" | 13-4 (13 S3.1, Bitwig sandbox RSS) |
| `docs/BUILD_PLAN.md:157` | "counts in Phase 10's IR-staleness metric" | 10-2 (10 scope 3) |
| `docs/BUILD_PLAN.md:157` | "(iv) Records … from Phase 08 also in binaural mode" | 08-4 (08 scope 9) |
| `docs/BUILD_PLAN.md:157` | "(v) Phase 08 item 8 measures the delay of one isolated update" | 08-4 (08 scope 8) |
| `docs/BUILD_PLAN.md:157` | "the remedy is a Phase 10 AX that updates the specular and directional part without waiting" | 10-2 (10 scope 3 split update, AX38 (v)) |
| `docs/BUILD_PLAN.md:157` | "reaches Maisara before Phase 12 builds the FR-3D-3 presets" | 12-2 |
| `docs/BUILD_PLAN.md:157` | "from Phase 08, W1/W2 per output mode with the diffuse share" | 08-4 (08 AC12 sentences 3–4) |
| `docs/BUILD_PLAN.md:157` | "gated on Linux, recorded on macOS and Windows until Phase 13" (D-T1 peak) | 13-1 (13 S1, memory per instance on three OSes) |
| `docs/BUILD_PLAN.md:157` | "from Phase 08 on, the gate measures the heaviest output mode … Phase 08's heaviest-mode build … Phase 08's goldens" | 08-4 (08 scope 10; scope 7 goldens) |
| `docs/BUILD_PLAN.md:157` | "the 'settling' state and stepwise room-size automation at large rooms (Phase 10, Phase 11)" | 10-2 (10 scope 4, stepwise); 11-3 (11 scope 9, settling) |
| `docs/BUILD_PLAN.md:157` | "the nominal Eyring T60 is not shown as an open field's reverb time (Phase 11)" | 11-1 (11 scope 1f) |
| `docs/BUILD_PLAN.md:157` | "There was no memory budget (phase-13 scope 1)" | 13-1 |
| `docs/BUILD_PLAN.md:157` | "Reversal: Phase 13 RSS" | 13-4 (13 S3.1 RSS) |
| `docs/BUILD_PLAN.md:160` | "Phase 12's reopening trigger … is phase-12 'Hall presets and J1'" | 12-2 (12 scope 7) |
| `docs/BUILD_PLAN.md:160` | "phase-13 re-checks them on the release machines" | 13-2 (13 S13) |
| `docs/BUILD_PLAN.md:163` | "Phase 11 shows it on the settled scene only, in the info view" | 11-3 (11 scope 8) |
| `docs/BUILD_PLAN.md:163` | "no default placement of a valid fixture or Phase 12 preset may raise U" | 12-2 |
| `docs/BUILD_PLAN.md:163` | "a labelled diagnostic tier in a Phase 11 advanced view" | 11-3 (11 scope 8; AX44) |
| `docs/BUILD_PLAN.md:163` | "Phase 08: E_b bit-identical …; one both-near binaural render" | 08-3 (08 AC11; scope 7 both-near render) |
| `docs/BUILD_PLAN.md:163` | "(Phase 12 presets checked)" | 12-2 |
| `docs/BUILD_PLAN.md:174` | "required before the Phase 13 beta decision" | 13-5 (13 D4; R1 also in 13-1) |
| `docs/BUILD_PLAN.md:231` | "Out of scope: binaural tail decorrelation (Phase 08)" | 08-3 (08 scope 5b) |
| `docs/BUILD_PLAN.md:235` | "Phase 10 gates the maximum dip of the expected output power" | 10-3 (10 AC7) |
| `docs/BUILD_PLAN.md:310` | "cross-reference AX38 (v) and phase-10's update scheduling" | 10-2 (10 scope 3) |
| `docs/BUILD_PLAN.md:310` | "the Phase 12 (ii) re-run and Phase 08's capped-room golden tolerance" | 12-2; 08-4 (08 AC13) |
| `docs/BUILD_PLAN.md:312` | "Before Phase 13's beta; ahead of Phase 08's golden freeze if Phase 08's heaviest mode fails the restore gate" | 13-5 (D4); 08-4 |
| `docs/BUILD_PLAN.md:345` | "per-surface material dropdown (from Phase 12's library once present …)" | 12-1 |
| `docs/BUILD_PLAN.md:390` | "User-audible fact for Phase 13's beta list" | 13-5 (13 D4) |
| `docs/BUILD_PLAN.md:410` | "Added AX17 (broadband s …; Phase 12)" | 12-1 (AX17: umbrella and 12-1) |
| `docs/BUILD_PLAN.md:411` | "phase-10 cache wording aligned (B4)" | 10-1 (10 scope 2) |
| `docs/BUILD_PLAN.md:413` | "phase-10 cache wording aligned" | 10-1 (10 scope 2) |
| `docs/BUILD_PLAN.md:414` | "phase-10 and §4 Phase 10 aligned (staleness gate no longer tied to order 20)" | 10-2 (10 AC8) |
| `docs/BUILD_PLAN.md:417` | "position-crossfade dip at the switch measured in Phase 10" / "power ratio recorded in Phase 10 (FQ-07)" | 10-3 (10 AC6) |
| `docs/BUILD_PLAN.md:418` | "in AX22, §4 Phase 04, phase-04 Risks and phase-10 (FQ-13)" | 10-3 (10 AC6) |
| `docs/BUILD_PLAN.md:421` | "switch-point dip gated ≤ 1 dB (Phase 10)" | 10-3 (10 AC6) |
| `docs/BUILD_PLAN.md:421` | "phase-10 (switch-point gate, staleness branch)" | 10-3 (AC6); 10-2 (AC8) |
| `docs/BUILD_PLAN.md:421` | "phase-13 (AQ10 workloads, acceptance, beta decision)" | 13-1 + 13-2 (13 C2 split); 13-5 (D4) |
| `docs/BUILD_PLAN.md:422` | "exact Phase 10 dip gate" | 10-3 (10 AC6/AC7) |
| `docs/BUILD_PLAN.md:422` | "second measured dataset required before the Phase 13 beta" / "phase-13 beta decision" | 13-5 (13 D4) |
| `docs/BUILD_PLAN.md:423` | "phase-13 (depends on, scope 5, beta decision)" | 13 H umbrella; 13-5 (S5, D4) |
| `docs/BUILD_PLAN.md:424` | "phase-13 (beta decision coverage)" | 13-5 (13 D4) |
| `docs/BUILD_PLAN.md:443` | "user-audible fact for Phase 13 recorded" | 13-5 (13 D4) |
| `docs/BUILD_PLAN.md:446` | "left to a Phase 10 AX entry" (20 ms cap, isolated request) | 10-2 (10 scope 8) |
| `docs/BUILD_PLAN.md:446` | "phase-13 scope 1 gains the measured 12 s benchmark numbers" | 13-1 |
| `docs/BUILD_PLAN.md:447` | "phase-13 scope item 9 added" | 13-3 (13 S9) |
| `docs/BUILD_PLAN.md:448` | "phase-08 and phase-10 items added" | 08-4 (08 scope 8); 10-2 (10 scope 8) |
| `docs/BUILD_PLAN.md:449` | "head-rotation row deferred to phase-08 item 8" / "phase-08 item 8 note" | 08-4 (08 scope 8) |
| `docs/BUILD_PLAN.md:449` | "phase-13 item 9 remedy restated (… another output-preserving scope 1 optimisation …)" | 13-3 (S9); 13-1 / `13-1b` (S1) |
| `docs/BUILD_PLAN.md:453` | "phase-10 scope 8, AX18 placeholder note, position-fade gate AC" | 10-2 (scope 8); 10-3 (AX18, AC7) |
| `docs/BUILD_PLAN.md:453` | "phase-11 scope 5–7" | 11-2 (scope 5); 11-1 (scopes 6, 7) |
| `docs/BUILD_PLAN.md:453` | "phase-13 scope 10–11" | 13-1 (S10); 13-4 (S11) |
| `docs/BUILD_PLAN.md:454` | "phase-10 scope 8: the builder's 1 ms idle poll" | 10-2 |
| `docs/BUILD_PLAN.md:454` | "phase-13 scope 1: Phase 07 rebuild times … any budget decided in Phase 13" | 13-1 |
| `docs/BUILD_PLAN.md:454` | "phase-13 scope 12 (new): pluginval release cached in CI" | 13-4 (13 S12) |
| `docs/BUILD_PLAN.md:457` | "phase-08: scope 1 (SADIE II D1 KU100 …)" | 08-1 |
| `docs/BUILD_PLAN.md:457` | "Phase 11 tooltip note" | 11-1 (scope 1e; hand-off cited in `phase-11-1.md:24`) |
| `docs/BUILD_PLAN.md:458` | "phase-08 AC 2 redefined as a two-term storage/decoding round-trip" | 08-1 (08 AC2) |
| `docs/BUILD_PLAN.md:460` | "Phase 08 gets E_b and t_mix,e only" | 08-3 (08 scope 5d) |
| `docs/BUILD_PLAN.md:462` | "Q2a (C), moving the diffuse solve off the synchronous restore and prepare, scheduled in phase-13 (scope 13)" | resolved: historical §6 change-log row, not edited (history is append-only); 'phase-13 scope 13' = S13, now in 13-2; (C)'s move to phase-07c predates the split |
| `docs/BUILD_PLAN.md:464` | "the reported set (B15, phase-11)" | 11-3 (11 scope 8) |
| `docs/BUILD_PLAN.md:465` | "phase-08 scope 10 and AC (heaviest mode, one W_max, SE-derived golden tolerance)" | 08-4 (scope 10, AC13) |
| `docs/BUILD_PLAN.md:465` | "phase-11 (U's note reaches the producer's editor)" | 11-3 (11 scope 8) |
| `docs/BUILD_PLAN.md:465` | "phase-12 (re-run (ii) under (C)'s W_max; hall presets checked …)" | 12-2 |
| `docs/BUILD_PLAN.md:465` | "phase-13 (…; Raise item 4)" | 13-1 and 13-5 (13 R4) |
| `docs/BUILD_PLAN.md:465` | "New phase-07c (asynchronous diffuse solve: conditions (iii) 1–8 …)" | conditions 2, 4–7 → 07c-1; 3, 8 → 07c-2; 1 → umbrella + 07c-2 |
| `docs/BUILD_PLAN.md:466` | "phase-13 depends on 07c `done` or scope 13's versioning fallback recorded" | 13 H umbrella; scope 13 → 13-2 |
| `docs/BUILD_PLAN.md:466` | "phase-07c §6 last criterion conditional on Phase 12 having run" | 07c-2 (07c A9); 12-2 |
| `docs/BUILD_PLAN.md:466` | "phase-07c §4 researcher-question ordering" | 07c-1 (07c §4 R1–R3, ordering note) |
| `docs/BUILD_PLAN.md:466` | "phase-10 scope 3 points to phase-07c for the split update" | 10-2 (10 scope 3); 07c-1 (condition 4) |
| `docs/BUILD_PLAN.md:468` | "phase-08 scopes 9 and 10 and their two criteria" | 08-4 (scopes 9, 10; AC12 s. 3–4, AC13) |
| `docs/BUILD_PLAN.md:468` | "phase-07c comes forward ahead of Phase 08's golden freeze … (phase-08, phase-07c §3)" | 08-4 (golden freeze); 07c §3 T2 → umbrella |
| `docs/BUILD_PLAN.md:469` | "if Phase 08's heaviest-mode build makes the pinned W_max fail the gate, … before Phase 08's goldens are frozen" | 08-4 |
| `docs/BUILD_PLAN.md:470` | "the '13b' in AQ10 is now `13-1b`, notarization's remainder `13-5b`" | `13-1b` / `13-5b` (definitional) |
| `docs/phases/phase-07c-1.md:12`, `phase-07c-2.md:12`, `phase-07c.md:4–5`, `phase-07c.md:111` | "Must be `done` before Phase 13's beta (or phase-13 scope 13's versioning fallback)" | 13-5 (13 D4); 13-2 (13 S13) |
| `docs/phases/phase-07c-1.md:22`, `phase-07c-2.md:22`, `phase-07c.md:41` | "phase-13 'Raise with Maisara' item 4" | 13-1 and 13-5 (13 R4) |
| `docs/phases/phase-07c-1.md:65` | "the remedy for Table 15.1's head-rotation row (a Phase 10 AX …)" | 10-2 (10 scope 3 split update) |
| `docs/phases/phase-07c-1.md:67` | "designed together with phase-10's update scheduling" | 10-2 (10 scope 3) |
| `docs/phases/phase-07c-2.md:37`, `phase-07c.md:45` | "before the first public release (the Phase 13 beta)" | 13-5 (13 D4) |
| `docs/phases/phase-07c-2.md:47`, `:61`, `:62`; `phase-07c.md:97` | "The Phase 12 (ii) preset check … if Phase 12 has run; otherwise Phase 12 runs it" | 12-2 (per `phase-12.md` notes) |
| `docs/phases/phase-07c-2.md:48` | "Phase 08 goldens in capped rooms carry a tolerance" | 08-4 (08 AC13) |
| `docs/phases/phase-07c-2.md:91`, `phase-07c.md:139` | "(phase-08 scope 10: 'W_max is then …')" | 08-4 |
| `docs/phases/phase-07c.md:48–50` | "Brought ahead of Phase 08's golden freeze if Phase 08's heaviest-mode build … (phase-08 scope 10) … if Phase 08 went first" | 08-4 |
| `docs/phases/phase-07c.md:87`, `:132` | "§0 row 07c `done` before Phase 13's beta" | 13-5 (13 D4) |
| `docs/phases/phase-08.md:45`, `phase-08-2.md:37`, `phase-08-3.md:46` | "the Phase 12 preset listening checklist and its PR listening notes, the Phase 13 final listening pass through all presets" | 12-2 (12 L1–L4); 13-5 (13 L1–L5) |
| `docs/phases/phase-08.md:142` | "status row 08 `done` (or 08b added)" | resolved: pointer added after "(or 08b added)": "[after the 2026-11-10 split: a sub-phase remainder is `08-<n>b`]" |
| `docs/phases/phase-08-3.md:39` | "keeps using omni until Phase 09" | phase-09 (whole) |
| `docs/phases/phase-08-3.md:95` | "Hand-off to Phase 11 (Seat 6): output-mode tooltip or manual" | 11-1 (scope 1e; received in `phase-11-1.md:22`) |
| `docs/phases/phase-08-4.md:44` | "the remedy is a Phase 10 AX" | 10-2 (10 scope 3 split update) |
| `docs/phases/phase-10-2.md:38` | "the same wait drives Phase 11's 'settling' state" | 11-3 (11 scope 9) |
| `docs/phases/phase-10-2.md:40`, `:110`; `phase-10.md:58` | "`phase-07c.md` condition 4" | 07c-1 |
| `docs/phases/phase-10-2.md:73` | "this phase may apply the phase-13 scope 1 optimisations" | 13-1 (13 S1) |
| `docs/phases/phase-11-1.md:22` | "the phase-08 line 302 hand-off ('Hand-off to Phase 11 (Seat 6)' …)" | resolved: pointer added after "phase-08 line 302": "[now docs/phases/phase-08-3.md line ~95, after the 2026-11-10 split]" (line 95 checked: holds the hand-off) |
| `docs/phases/phase-11-1.md:23` | "the phase-09 line 75 hand-off" | phase-09 (whole); line 75 still holds it |
| `docs/phases/phase-11-3.md:23`; `phase-12.md:78` | "(from Phase 12's library if Phase 12 is done …)" / "phase-11's 'if Phase 12 is done'" | 12-1; the phase-11 item is 11-3 (scope 1d) |
| `docs/phases/phase-11.md:45`; `phase-12.md:77–78` | "presets browser (Phase 12 adds it)" / "phase-11 out of scope's …" | 12-2; phase-11 Out of scope → umbrella |
| `docs/phases/phase-12.md:23` | "feeding Phase 11's surface dropdown" | 11-3 (11 scope 1d) |
| `docs/phases/phase-12.md:77`; `phase-12-2.md:110` | "phase-07c §5 item 8 and §6 last criterion" | 07c-2 (condition 8; A9) |
| `docs/phases/phase-12.md:78` | "phase-08's preset validation logs" | 08 scope 7 sentence: shared, umbrella + 08-2 + 08-3 |
| `docs/phases/phase-12.md:79` | "phase-13's dependency on '00–12' means both" | 13 H umbrella (shared) |
| `docs/phases/phase-12-2.md:43` | "re-run under phase-07c's W_max once that phase has landed" | 07c-2 |
| `docs/phases/phase-13-2.md:23` | "re-derived once under phase-07c" (W_max) | 07c-2 |
| `docs/phases/phase-13-1.md:43` | "non-uniform partitioning (if needed, make it 13b)" | `13-1b` (annotated at `phase-13-1.md:57`) |
| `docs/phases/phase-13-3.md:40` | "(new AX entry, 13b, per scope 1)" | `13-1b` (annotated at `phase-13-3.md:43`) |

## B. Whole-phase references (umbrella)

| file | lines | reference text (examples) | resolves to |
|---|---|---|---|
| `.claude/skills/review-phase-pr/references/binaural-and-stereo.md` | 3, 43, 45, 383, 518 | "Phases 08, 09, 11, 12"; "covering Phase 08 (binaural output …)"; "`docs/phases/phase-08.md`"; "not required by Phase 08"; "Out of scope for Phase 08" | umbrella (all sub-phases, G3 default) |
| `.claude/skills/review-phase-pr/references/convolution-and-movement.md` | 32, 42, 48, 448, 770 | "Update scheduling for moving sources (phase 10)"; "`docs/phases/phase-10.md`"; "Scheduler and automation (phase 10)" | umbrella (all sub-phases, G3 default) |
| `.claude/skills/review-phase-pr/references/knowledge-inventory.md` | 44, 49 | "Phase 13"; "Phase 08" | umbrella (all sub-phases, G3 default) |
| `.claude/skills/review-phase-pr/references/room-acoustics.md` | 538 | "wrong HRTF direction in phase 08" | umbrella (all sub-phases, G3 default) |
| `.claude/skills/review-phase-pr/references/phase-checklists.md` | 240, 291, 313, 331, 348 | "## Phase 08 — Binaural output …", "## Phase 10 …", "## Phase 11 …", "## Phase 12 …", "## Phase 13 …" | umbrella (all sub-phases, G3 default); each checklist now spans several sub-phase PRs |
| `docs/validation/report-phase05.md` | 590 | "B10 stays after phase 12" | umbrella (all sub-phases, G3 default) |
| `tools/validation/report.py` | 573 | "B10 stays after phase 12" | umbrella (all sub-phases, G3 default) |
| `src/sim/Engine.h` | 4, 9 | "binaural in Phase 08"; "(Phases 08 and 09)" | umbrella (all sub-phases, G3 default) |
| `src/sim/conv/CrossfadingConvolver.h` | 4 | "Phase 10 builds movement on it" | umbrella (all sub-phases, G3 default) |
| `docs/phases/phase-05.md` | 155 | "Phase 13 may start with 05c blocked …" | umbrella (13 H, shared) |
| `docs/phases/phase-05b.md` | 14, 40, 64, 65 | "Phase 08 builds on the specular-only early part"; "the first remedy Phase 10 may propose" (no sub-phase names it); "so that Phase 08 can assign directions"; "Phase 08's decision" | umbrella (all sub-phases, G3 default) |
| `docs/phases/phase-05b2.md` | 215, 397, 400, 408 | "a Phase 10 remedy only if W1 > 700 ms" (no sub-phase names it); "Phase 08's dependencies gain 05h"; "Phase 08 may go before 05h"; "Phase 08 directions beyond D-T5 (3); Phase 10 caching beyond …" | umbrella (all sub-phases, G3 default) |
| `docs/phases/phase-05d.md` | 7, 356 | "Phase 13 depends on 05d being `done` or …" | umbrella (13 H, shared) |
| `docs/phases/phase-05h.md` | 76, 78, 120, 171, 225, 228, 265, 314, 316 | "`phase-07c.md`"; "Phase 08 may precede this phase …"; "(phase-07c) forward"; "so phase-07c can move it"; "phase-07c lands before …"; "Phase 08 directions beyond AX37 (5.3); Phase 10 …" | umbrella (all sub-phases, G3 default) |
| `docs/phases/phase-06.md` | 9 | "Phase 10 builds movement on top of that swap" | umbrella (all sub-phases, G3 default) |
| `docs/phases/phase-07.md` | 34, 84, 238, 279 | "Binaural is Phase 08"; "Phase 10 proposes an AX"; "Binaural/stereo-speaker output (08/09) … custom UI (11)"; "in Phase 08's binaural render" | umbrella (all sub-phases, G3 default) |
| `docs/phases/phase-09.md` | 3 | "Depends on: 07, 08" | umbrella (all of 08-1…08-4, G3 default) |
| `docs/phases/phase-07c-1.md`, `phase-07c-2.md`, `phase-07c.md` | 07c-1: 86; 07c-2: 54; 07c: 82 | "a kernel cache (AX38 (ii), phase-10 AX only)" (no sub-phase owns a kernel cache) | umbrella (all sub-phases, G3 default) |
| `docs/phases/phase-08-4.md` | 56, 58, 59, 76 | "phase-07c (which depends on 05h) is brought forward"; "unless phase-07c has landed" | umbrella (all sub-phases, G3 default) |
| `docs/phases/phase-13-1.md`, `phase-13-5.md`, `phase-13.md`, `phase-13-2.md` | 13-1: 20; 13-5: 20; 13: 55; 13-2: 26 | "Phase 07c not landed (conditional) … (phase-07c)"; "`phase-07c.md`" | umbrella (all sub-phases, G3 default) |
| `docs/BUILD_PLAN.md` | 32, 35, 41, 45, 49, 52 (each umbrella's own status row and link), 53–57 ("00–12"), 114 (phase-07c ×2; "08-first order"), 127 ("Must be confirmed before the first beta (Phase 13)"; breaks "00, 13"), 150 ("Phase 10 swaps about every 30 ms"), 156 ("Phase 08 may go before 05h"; "Phase 08 binaural"), 157 ("(phase-07c) forward"; "08-first order"; "a kernel cache (Phase 10)"), 160 (phase-07c ×3), 270, 276, 308, 309, 312 ("Dependencies: 05h, 07"), 316, 334, 343, 353, 362, 368, 388 ("after 12"), 396 ("after 08"; "Phase 08 binaural"), 421 ("phase-08 (depends on 05b)"), 422 ("phase-10 and AX22"), 454 ("§4 Phase 10/13 summaries"), 460 ("phase-08, -10,"), 461 ("phase-08, -10, -11, -12, -13"), 464 ("Phase 08 depends on 05h"; "phase-13 dependencies list 05h"), 465 ("phase-13 ((C) a beta prerequisite …; depends on 07c"), 466 ("phase-07c header"), 468 ("phase-05b2 §9 notes that Q2a (C) is phase-07c"), 469 ("08-first order"), 470 ("Phases 07c, 08, 10, 11, 12 and 13 split") | §4 headings, status rows, dependency lines, change-log mentions | umbrella (all sub-phases, G3 default) |
| phase 09, all files | `.claude/…/binaural-and-stereo.md` 3, 44, 45, 545, 555, 562, 580; `…/knowledge-inventory.md` 51; `…/phase-checklists.md` 272; `docs/BUILD_PLAN.md` 114 ("Phases 04–09"), 326, 410 ("Phase 09 gate"); `src/sim/Engine.h` 4, 5, 9; `docs/phases/phase-11.md` 76 ("depends on 07, 09"); plus the "phase-09 (whole)" halves of the section A rows for `CLAUDE.md:229`, `docs/contract/README.md:265`, `ImageSources.h:35`, `ScenePipeline.cpp:68`, `ParameterMap.h:14`, `ParameterMap.cpp:127`, `phase-03.md:34`, `phase-06.md:18`, `phase-07.md:61`, `BUILD_PLAN.md:137`, `phase-08-3.md:39`, `phase-11-1.md:23` | "Phase 09", "phase-09", "08/09" | phase-09 (whole) |

Not counted: direct sub-phase ids that name themselves (BUILD_PLAN §0 rows 33–34, 36–39, 42–44, 46–48, 50–51,
53–57, and the dependency columns of the sub-phase files), which need no resolution.

## C. UNRESOLVED

None remaining: the four rows below were resolved on 2026-11-10.

| file:line | reference text | reason |
|---|---|---|
| `docs/phases/phase-11-1.md:22` | "the phase-08 line 302 hand-off" | stale line pointer: line 302 was in the pre-split `phase-08.md`; the umbrella now has 146 lines. The hand-off is now `phase-08-3.md:95` (08-3). resolved: pointer added after "phase-08 line 302": "[now docs/phases/phase-08-3.md line ~95, after the 2026-11-10 split]" (line 95 checked: holds the hand-off) |
| `docs/phases/phase-08.md:142` | "status row 08 `done` (or 08b added)" | stale remainder name: remainders are `08-<n>b` (same file, line 79), and the umbrella DoD does not say which. resolved: pointer added after "(or 08b added)": "[after the 2026-11-10 split: a sub-phase remainder is `08-<n>b`]" |
| `docs/THIRD_PARTY.md:68` | "pinned in Phase 08 session 1" | "session 1" is no longer a label; best reading 08-1. resolved: pointer added after "Phase 08 session 1": "[= sub-phase 08-1 since the 2026-11-10 split]" |
| `docs/BUILD_PLAN.md:462` | "Q2a (C) … scheduled in phase-13 (scope 13)" | meaning changed: (C) is now phase-07c; "phase-13 scope 13" now names S13 (AX41 limits, 13-2). Historical change-log row. resolved: historical §6 change-log row, not edited (history is append-only); 'phase-13 scope 13' = S13, now in 13-2; (C)'s move to phase-07c predates the split |
