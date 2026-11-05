# Golden file change log

Every change to a golden file in `tests/golden/` is recorded here by `tools/ci/update_goldens.py`,
which is the only supported way to update them (CLAUDE.md "Tests and golden files"). An entry
gives the date, the reason, and which goldens were created or which values moved out of their
tolerance. A golden change also needs an explanation in the PR and a row in `docs/BUILD_PLAN.md` §6.

Golden file format: see `tools/acoustics/golden.py`.

## 2026-11-05

Reason: Phase 03: first goldens of the early-reflection (ISM) omni IR of small_room, medium_room and large_hall at order 10

- `phase03_small_room_omni_order10`: created
- `phase03_medium_room_omni_order10`: created
- `phase03_large_hall_omni_order10`: created

## 2026-11-05

Reason: phase 04 adds tail: first goldens of the hybrid omni IR (ISM + late tail) of every valid fixture, 48 kHz, the fixture's own tailSeed; energy ratios without late energy recorded as such

- `phase04_asymmetric_materials_omni`: created
- `phase04_classroom_omni`: created
- `phase04_club_omni`: created
- `phase04_concert_hall_box_omni`: created
- `phase04_dead_booth_omni`: created
- `phase04_edge_values_omni`: created
- `phase04_large_hall_omni`: created
- `phase04_living_room_omni`: created
- `phase04_medium_room_omni`: created
- `phase04_open_field_omni`: created
- `phase04_small_room_omni`: created
- `phase04_stone_box_omni`: created

