# Phase-07 wording fixes (commit e2f1d7a): interrogator diff check, round 1 (2026-11-08; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Rated against the working tree (the interrogator has no shell), `src/sim/RealtimeEngine.h`,
`src/sim/conv/CrossfadingConvolver.{h,cpp}` (reset() 147–170, computeBlock() 260–345), `src/sim/Engine.h`,
`tests/scenes/valid/medium_room.json`.

| id | passage | verdict | evidence | fix | severity |
|---|---|---|---|---|---|
| P07-15a | `RealtimeEngine::reset()` keeps the current IR; determinism AC requires same-instance second bounce = fresh instance | INCONSISTENT (API vs AC) | computeBlock step 1 installs at once only if current_ == nullptr && blockStart_ == 0; with current_ kept, the initial IR fades in from s0 = 2P (step 4), so outputs differ | reset must leave the convolver as a fresh prepare() (no current IR), or relax the AC | blocker |
| P07-15b | what reset() does | IMPRECISE | `CrossfadingConvolver.h:96–98`: also clears pending output, ends a running fade on its target; mailbox untouched; not concurrent with process() | restate | minor |
| P07-15c | "enters the output up to 2P later" | IMPRECISE (condition) | AX31 s0 − r ∈ (P, 2P] only for an isolated update | add "isolated update; during a running fade, after it ends" | minor |
| P07-14 | non-realtime path, "only submitter" | CORRECT, one clause IMPRECISE | setStateInformation / prepareToPlay also submit | "only submitter during a bounce" | minor |
| P07-16 | discriminating ACs | CORRECT; wording IMPRECISE | "one field (A and B)" | "at least one … (e.g. …)" | minor |
| P07-17 | parameters authoritative on restore | CORRECT | same float derivation on both sides (AX5) | — | none |
| P07-6 | pure function | CORRECT | — | — | none |
| P07-27 | generation counter, no lost update | CORRECT; "atomic store" IMPRECISE | increment is fetch_add | "atomic increment" | minor |
| P07-28 | no allocation tested, no lock by construction | CORRECT; same wording | — | same | minor |
| P07-3 | AX2 per emitter path | CORRECT | `Engine.h:34`; Vorländer §1.7 Table 1.3, Eq. 1.38 | — | none |
| P07-18 | 07 forces Omni | CORRECT | `Engine.h:127`; medium_room outputMode binaural | — | none |
| P07-20 | state before prepareToPlay | CORRECT | `RealtimeEngine.h:35–36, 55–57` | — | none |
| P07-21 | AX32 bound | CORRECT | `CrossfadingConvolver.h:41–44, 117–118`; 2²⁰ = 120.4 dB | — | none |
| P07-4 | comb colouring "goes away in Phase 08" | IMPRECISE | Vorländer §1.7 cross term; Blauert Ch. 4 "Binaural timbre compensation": binaural listening makes it much less audible, not removed; none for uncorrelated L/R | reword | minor |
| P07-25 | symmetric L/R for the PDC check | CORRECT | medium_room L/R both 6.090 m; Izhaki Ch. 11 | — | none |
| P07-10 | RSS recorded, not gated | CORRECT; NOT CHECKABLE | `maxIrLengthSamples` | — | none |
| BP-389 | §6 row | CORRECT; inherits P07-15a | — | update with the fix | none |

Main session: P07-15a is a software contradiction (no acoustic choice): sent to the plan-editor with the fix
"reset() returns the engine to the post-prepare() state (no IR); the plugin resubmits the current scene's IR
immediately", plus the minor fixes. Re-check in diff round 2.
