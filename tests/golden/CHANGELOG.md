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

## 2026-11-05

Reason: phase 04 plan update (AX22): the realised-k switch falls back to ISM-only up to the image-count cap N_cap = nu_r(10) in asymmetric_materials, edge_values, medium_room and open_field, moving their handover to max(t_mix, t_cap); the other goldens are unchanged

- `phase04_asymmetric_materials_omni`: changed `bands.63.EDT`, `bands.63.T20`, `bands.63.T30`, `bands.63.C50`, `bands.63.C80`, `bands.63.D50`, `bands.125.EDT`, `bands.125.T20`, `bands.125.T30`, `bands.125.C50`, `bands.125.C80`, `bands.125.D50`, `bands.250.EDT`, `bands.250.T20`, `bands.250.T30`, `bands.250.C50`, `bands.250.C80`, `bands.250.D50`, `bands.500.EDT`, `bands.500.T20`, `bands.500.T30`, `bands.500.C50`, `bands.500.C80`, `bands.500.D50`, `bands.1000.EDT`, `bands.1000.T20`, `bands.1000.T30`, `bands.1000.C50`, `bands.1000.C80`, `bands.1000.D50`, `bands.1000.DRR`, `bands.2000.EDT`, `bands.2000.T20`, `bands.2000.T30`, `bands.2000.C50`, `bands.2000.C80`, `bands.2000.D50`, `bands.2000.DRR`, `bands.4000.EDT`, `bands.4000.T20`, `bands.4000.T30`, `bands.4000.C50`, `bands.4000.C80`, `bands.4000.D50`, `bands.4000.DRR`, `bands.8000.EDT`, `bands.8000.T20`, `bands.8000.T30`, `bands.8000.C50`, `bands.8000.C80`, `bands.8000.D50`, `bands.8000.DRR`, `broadband.EDT`, `broadband.T20`, `broadband.T30`, `broadband.C50`, `broadband.C80`, `broadband.D50`, `broadband.DRR`, `emitters.L.mix_ms`, `emitters.R.mix_ms`
- `phase04_classroom_omni`: rewritten, within tolerance
- `phase04_club_omni`: rewritten, within tolerance
- `phase04_concert_hall_box_omni`: rewritten, within tolerance
- `phase04_dead_booth_omni`: rewritten, within tolerance
- `phase04_edge_values_omni`: changed `bands.63.T20`, `bands.63.T30`, `bands.63.C50`, `bands.63.C80`, `bands.125.T20`, `bands.125.T30`, `bands.125.C50`, `bands.125.C80`, `bands.250.EDT`, `bands.250.T20`, `bands.250.T30`, `bands.250.C50`, `bands.250.C80`, `bands.250.D50`, `bands.500.T20`, `bands.500.T30`, `bands.500.C50`, `bands.500.C80`, `bands.1000.EDT`, `bands.1000.T20`, `bands.1000.T30`, `bands.1000.C50`, `bands.1000.C80`, `bands.1000.D50`, `bands.1000.DRR`, `bands.2000.EDT`, `bands.2000.T20`, `bands.2000.T30`, `bands.2000.C50`, `bands.2000.C80`, `bands.4000.EDT`, `bands.4000.T20`, `bands.4000.T30`, `bands.4000.C50`, `bands.4000.C80`, `bands.4000.D50`, `bands.4000.DRR`, `bands.8000.T30`, `bands.8000.C50`, `bands.8000.C80`, `broadband.T20`, `broadband.T30`, `broadband.C50`, `broadband.C80`, `broadband.DRR`, `emitters.L.mix_ms`
- `phase04_large_hall_omni`: rewritten, within tolerance
- `phase04_living_room_omni`: rewritten, within tolerance
- `phase04_medium_room_omni`: changed `bands.63.EDT`, `bands.63.T20`, `bands.63.T30`, `bands.63.C50`, `bands.63.C80`, `bands.63.D50`, `bands.125.EDT`, `bands.125.T20`, `bands.125.T30`, `bands.125.C50`, `bands.125.C80`, `bands.125.D50`, `bands.250.EDT`, `bands.250.T20`, `bands.250.T30`, `bands.250.C50`, `bands.250.C80`, `bands.250.D50`, `bands.500.EDT`, `bands.500.T20`, `bands.500.T30`, `bands.500.C50`, `bands.500.C80`, `bands.500.D50`, `bands.1000.EDT`, `bands.1000.T20`, `bands.1000.T30`, `bands.1000.C50`, `bands.1000.C80`, `bands.1000.D50`, `bands.1000.DRR`, `bands.2000.EDT`, `bands.2000.T20`, `bands.2000.T30`, `bands.2000.C50`, `bands.2000.C80`, `bands.2000.D50`, `bands.2000.DRR`, `bands.4000.EDT`, `bands.4000.T20`, `bands.4000.T30`, `bands.4000.C50`, `bands.4000.C80`, `bands.4000.D50`, `bands.4000.DRR`, `bands.8000.EDT`, `bands.8000.T20`, `bands.8000.T30`, `bands.8000.C50`, `bands.8000.C80`, `bands.8000.D50`, `bands.8000.DRR`, `broadband.EDT`, `broadband.T20`, `broadband.T30`, `broadband.C50`, `broadband.C80`, `broadband.D50`, `broadband.DRR`, `emitters.L.mix_ms`, `emitters.R.mix_ms`
- `phase04_open_field_omni`: changed `emitters.L.mix_ms`, `emitters.R.mix_ms`
- `phase04_small_room_omni`: rewritten, within tolerance
- `phase04_stone_box_omni`: rewritten, within tolerance

## 2026-11-06

Reason: Phase 05e: create the nightly-gate baseline of the BRAS validation scenes (CR2, CR3 under AX26; AX27 noise subtraction in the validation path). CR4 is added when its extraction is accepted.

- `validation_baseline`: created

## 2026-11-07

Reason: CR4 added, pre-committed room (phase-05f: CR4 geometry accepted by the bras_mapping.md §2 test under AX30; CR2/CR3 entries unchanged)

- `validation_baseline`: extended by 20 new key(s): `bras_cr4_ls1_mp1`, `bras_cr4_ls1_mp1_fitted`, `bras_cr4_ls1_mp2`, `bras_cr4_ls1_mp2_fitted`, `bras_cr4_ls1_mp3`, `bras_cr4_ls1_mp3_fitted`, `bras_cr4_ls1_mp4`, `bras_cr4_ls1_mp4_fitted`, `bras_cr4_ls1_mp5`, `bras_cr4_ls1_mp5_fitted`, `bras_cr4_ls2_mp1`, `bras_cr4_ls2_mp1_fitted`, `bras_cr4_ls2_mp2`, `bras_cr4_ls2_mp2_fitted`, `bras_cr4_ls2_mp3`, `bras_cr4_ls2_mp3_fitted`, `bras_cr4_ls2_mp4`, `bras_cr4_ls2_mp4_fitted`, `bras_cr4_ls2_mp5`, `bras_cr4_ls2_mp5_fitted`
- `validation_baseline`: rewritten, pinned values within tolerance

