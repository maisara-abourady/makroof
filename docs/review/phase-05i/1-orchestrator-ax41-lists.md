# Phase 05i scope 5: the AX41 lists against the D5 golden and the reports test (orchestrator, 2026-11-11)

Sources: `docs/BUILD_PLAN.md` AX41 ("a list of every fixture or preset where the pilot estimate ships (`edge_values`
at the time of writing, D-H3 (b); kept current in phase-05i)") and AX44 (the contract-limits fixtures `edge_values`
and `open_field` raise U at their defaults through the capped branch); `tests/golden/phase05h_d5_hashes.json`
(pilotShipped, approximate = U per emitter, capHit, floorTruncated per valid fixture); the reports test
`[diffuse][d5][reports]` (`tests/unit/test_diffuse_reports.cpp`), which pins every flag exactly.

| fixture | pilot ships (golden) | U e0 / e1 (golden) | cap hit | floor truncated | in AX41 'pilot ships' | in the known-U list |
|---|---|---|---|---|---|---|
| asymmetric_materials | 0 | 0 / 0 | 1 | 1 | no | no |
| classroom | 0 | 0 / 0 | 0 | 0 | no | no |
| club | 0 | 0 / 0 | 0 | 0 | no | no |
| concert_hall_box | 0 | 0 / 0 | 0 | 0 | no | no |
| dead_booth | 0 | 0 / 0 | 0 | 0 | no | no |
| edge_values | **1** | **1 / 1** | 1 | 1 | **yes** | **yes** (cap, K-b3) |
| large_hall | 0 | 0 / 0 | 0 | 0 | no | no |
| living_room | 0 | 0 / 0 | 0 | 0 | no | no |
| medium_room | 0 | 0 / 0 | 0 | 1 | no | no |
| open_field | 0 | **1 / 1** | 1 | 0 | no | **yes** (cap, K-b3) |
| small_room | 0 | 0 / 0 | 0 | 0 | no | no |
| stone_box | 0 | 0 / 0 | 0 | 0 | no | no |

Presets: none exist yet (`resources/presets/` absent; Phase 12). The fixture set (`tests/scenes/valid/`, 12 files) is
unchanged since phase 05h.

**Reading.** The 'pilot ships' list (`edge_values`) and the known-U list (`edge_values`, `open_field`) match the
golden exactly; U at every user-reachable room stays asserted by the D5 golden (D-H3 (b)). The reports test passes
on this branch (local Release run 2026-11-11: "All tests passed (507 assertions in 1 test case)"). No AX41 or AX44
edit is needed; the lists are re-read at Phase 12 when presets land (AX41 "kept current").
