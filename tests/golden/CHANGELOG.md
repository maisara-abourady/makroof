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

## 2026-11-10

Reason: phase 05h session 1: smoke-agreement reference of the C++ diffuse estimator (AX39, AX42 τ): ref_hybrid.target_hybrid at ℓ = 1.25 m, 8 bands, the 15 (A) cases, copied from tools/validation/data/phase05b.json by tools/validation/export_phase05h_smoke.py

- `phase05h_dt1_smoke_reference`: created

## 2026-11-10

Reason: phase 05h session 2: AX43 agreement and AX45 regression references of the C++ diffuse estimator (ref_hybrid.target_hybrid at the finest rung with l_ref per case-band, AX36; joined from tools/validation/data/phase05b.json, phase05_scope6.json and phase05h_hybrid_references.jsonl by tools/validation/export_phase05h_references.py; the gated set follows D-H2)

- `phase05h_agreement_reference`: created

## 2026-11-10

Reason: phase 05h session 2: tracer window reference of the 15 (A) cases (500 Hz-2 kHz) and the outer-band check (layouts 4/5 at s = 1; 125 Hz, 4 kHz, 8 kHz), E_tr = E_AX16,py / 10^(dL_tr/10) from the committed phase05b.json gate and outer_bands entries, by tools/validation/export_phase05h_references.py

- `phase05h_tracer_reference`: created

## 2026-11-10

Reason: phase 05h D-H3 (a) (docs/review/phase-05h/20-decider-decision-D-H3.md): AX43's pooled bias check pools per reference room with z' = (C++ - ref) / sqrt(SE^2 + l_ref^2); the room id (the reference that shares a case's discretisation residual) is written by the generating script, a schema addition

- `phase05h_agreement_reference`: `room` column added (schema only; no reference value changed)

## 2026-11-10

Reason: phase 05h session 2 (D-H2 (a)/(c), docs/review/phase-05h/19-decider-decision-D-H1-D-H2-r2.md): references extended with this session's hybrid_fast runs at 1.25 m for concert_hall_box, stone_box, W1 (both emitters), the CS-NW+ listener-wall 0.1 m case (emitter 0; the other CS-NW+ placements and W2 were still computing), and the 0.625 m rung for the small rooms (record); gated case-bands 314 -> 402 (AX43 330 of 560, AX45 72 of 72); no existing reference value changed, keys only promoted from reported to gated

- `phase05h_agreement_reference`: extended (88 case-bands promoted to gated; AX45/W1_e0 (8 bands), AX45/W1_e1 (8 bands), AX45/stone_box_e0 (8 bands), AX45/stone_box_e1 (8 bands), W1_e0 (8 bands), W1_e1 (8 bands), W1_listener_wall_0.1_e0 (8 bands), concert_hall_box_e0 (8 bands), concert_hall_box_e1 (8 bands), stone_box_e0 (8 bands), stone_box_e1 (8 bands))
## 2026-11-10

Reason: phase 05h: the late tail's level now comes from the propagated diffuse energy (the AX37 (5.1) switch: E_target = specular entries + the seeded Monte Carlo diffuse estimate, AX39-AX41) instead of the AX16 single-scatter proxy; docs/review/phase-05h/ (decisions D-H1, D-H2, D-H3) and phase-05h §5

- `phase04_asymmetric_materials_omni`: changed `bands.63.EDT`, `bands.63.C50`, `bands.63.C80`, `bands.63.D50`, `bands.125.EDT`, `bands.125.C50`, `bands.125.C80`, `bands.125.D50`, `bands.250.EDT`, `bands.250.T20`, `bands.250.C50`, `bands.250.C80`, `bands.250.D50`, `bands.500.EDT`, `bands.500.C50`, `bands.500.C80`, `bands.500.D50`, `bands.1000.EDT`, `bands.1000.T20`, `bands.1000.C50`, `bands.1000.C80`, `bands.1000.D50`, `bands.2000.EDT`, `bands.2000.T20`, `bands.2000.T30`, `bands.2000.C50`, `bands.2000.C80`, `bands.2000.D50`, `bands.4000.EDT`, `bands.4000.T20`, `bands.4000.T30`, `bands.4000.C50`, `bands.4000.C80`, `bands.4000.D50`, `bands.8000.EDT`, `bands.8000.T20`, `bands.8000.T30`, `bands.8000.C50`, `bands.8000.C80`, `bands.8000.D50`, `broadband.EDT`, `broadband.T20`, `broadband.T30`, `broadband.C50`, `broadband.C80`, `broadband.D50`
- `phase04_classroom_omni`: rewritten, within tolerance
- `phase04_club_omni`: changed `bands.63.C50`, `bands.63.C80`, `bands.63.D50`, `bands.125.C50`, `bands.125.C80`, `bands.125.D50`, `bands.250.C50`, `bands.250.C80`, `bands.250.D50`, `bands.500.C50`, `bands.500.C80`, `bands.500.D50`, `bands.1000.C50`, `bands.1000.C80`, `bands.1000.D50`, `bands.1000.DRR`, `bands.2000.C50`, `bands.2000.C80`, `bands.2000.D50`, `bands.2000.DRR`, `bands.4000.C50`, `bands.4000.C80`, `bands.4000.D50`, `bands.4000.DRR`, `bands.8000.C50`, `bands.8000.C80`, `bands.8000.D50`, `bands.8000.DRR`, `broadband.C50`, `broadband.C80`, `broadband.D50`, `broadband.DRR`
- `phase04_concert_hall_box_omni`: changed `bands.63.C50`, `bands.63.C80`, `bands.63.D50`, `bands.125.C50`, `bands.125.C80`, `bands.125.D50`, `bands.250.C50`, `bands.250.C80`, `bands.250.D50`, `bands.500.C50`, `bands.500.C80`, `bands.500.D50`, `bands.1000.C50`, `bands.1000.C80`, `bands.1000.D50`, `bands.1000.DRR`, `bands.2000.C50`, `bands.2000.C80`, `bands.2000.D50`, `bands.2000.DRR`, `bands.4000.EDT`, `bands.4000.C50`, `bands.4000.C80`, `bands.4000.D50`, `bands.4000.DRR`, `bands.8000.EDT`, `bands.8000.C50`, `bands.8000.C80`, `bands.8000.D50`, `bands.8000.DRR`, `broadband.EDT`, `broadband.C50`, `broadband.C80`, `broadband.D50`, `broadband.DRR`
- `phase04_dead_booth_omni`: changed `bands.63.EDT`, `bands.63.C50`, `bands.63.C80`, `bands.63.D50`, `bands.125.C50`, `bands.125.C80`, `bands.125.D50`, `bands.250.C50`, `bands.250.C80`, `bands.500.EDT`, `bands.500.C50`, `bands.500.C80`, `bands.1000.C50`, `bands.1000.C80`, `bands.1000.DRR`, `bands.2000.EDT`, `bands.2000.C50`, `bands.2000.C80`, `bands.2000.DRR`, `bands.4000.T20`, `bands.4000.C50`, `bands.4000.C80`, `bands.4000.DRR`, `bands.8000.EDT`, `bands.8000.C50`, `bands.8000.C80`, `bands.8000.DRR`, `broadband.EDT`, `broadband.C50`, `broadband.C80`, `broadband.DRR`
- `phase04_edge_values_omni`: changed `bands.63.T20`, `bands.63.T30`, `bands.63.C50`, `bands.63.C80`, `bands.125.T30`, `bands.125.C50`, `bands.125.C80`, `bands.250.T20`, `bands.250.T30`, `bands.250.C50`, `bands.250.C80`, `bands.500.T30`, `bands.500.C50`, `bands.500.C80`, `bands.1000.T20`, `bands.1000.T30`, `bands.1000.C50`, `bands.1000.C80`, `bands.2000.T30`, `bands.2000.C50`, `bands.2000.C80`, `bands.4000.T20`, `bands.4000.T30`, `bands.4000.C50`, `bands.4000.C80`, `bands.8000.T30`, `bands.8000.C50`, `bands.8000.C80`, `broadband.T20`, `broadband.T30`, `broadband.C50`, `broadband.C80`
- `phase04_large_hall_omni`: changed `bands.63.C50`, `bands.63.C80`, `bands.63.D50`, `bands.125.C50`, `bands.125.C80`, `bands.125.D50`, `bands.250.EDT`, `bands.250.C50`, `bands.250.C80`, `bands.250.D50`, `bands.500.EDT`, `bands.500.C50`, `bands.500.C80`, `bands.500.D50`, `bands.1000.EDT`, `bands.1000.C50`, `bands.1000.C80`, `bands.1000.D50`, `bands.1000.DRR`, `bands.2000.EDT`, `bands.2000.C50`, `bands.2000.C80`, `bands.2000.D50`, `bands.2000.DRR`, `bands.4000.EDT`, `bands.4000.C50`, `bands.4000.C80`, `bands.4000.D50`, `bands.4000.DRR`, `bands.8000.EDT`, `bands.8000.C50`, `bands.8000.C80`, `bands.8000.D50`, `bands.8000.DRR`, `broadband.EDT`, `broadband.T20`, `broadband.T30`, `broadband.C50`, `broadband.C80`, `broadband.D50`, `broadband.DRR`
- `phase04_living_room_omni`: changed `bands.63.C50`, `bands.63.D50`, `bands.125.C50`, `bands.125.D50`, `bands.250.D50`, `bands.1000.C50`, `bands.1000.D50`, `bands.1000.DRR`, `bands.2000.C50`, `bands.2000.D50`, `bands.2000.DRR`, `bands.4000.DRR`, `bands.8000.C50`, `broadband.C50`, `broadband.C80`, `broadband.DRR`
- `phase04_medium_room_omni`: changed `bands.250.EDT`, `bands.250.C80`, `bands.250.D50`, `bands.500.EDT`, `bands.500.C50`, `bands.500.C80`, `bands.500.D50`, `bands.1000.EDT`, `bands.1000.T20`, `bands.1000.C50`, `bands.1000.C80`, `bands.1000.D50`, `bands.2000.T20`, `bands.2000.T30`, `bands.2000.C50`, `bands.2000.C80`, `bands.2000.D50`, `bands.4000.T20`, `bands.4000.T30`, `bands.4000.C80`, `bands.8000.T20`, `bands.8000.T30`, `bands.8000.C80`
- `phase04_open_field_omni`: rewritten, within tolerance
- `phase04_small_room_omni`: rewritten, within tolerance
- `phase04_stone_box_omni`: rewritten, within tolerance

## 2026-11-10

Reason: phase 05h session 2: AX39 D5 face-sequence hash, n*, N, the AX41 flags, the note U and the switched E_target of every valid fixture at the pinned W_max 3.05 M / n*_max 1 024, 48 kHz, generated by the hidden test `[.generate-d5-golden]` (cross-OS comparison, AX5); regenerated after D-H3 (c)'s pool-worker FTZ guard with no change (docs/review/phase-05h/20-decider-decision-D-H3.md)

- `phase05h_d5_hashes`: created

## 2026-11-10

Reason: phase 05h H3-F6 (docs/review/phase-05h/25-decider-decision-D-H3-r2.md addendum; K-a4 (iii)): the finest certified rung per AX43: dead_booth, living_room, classroom and club (both emitters, 8 bands) referenced at 0.625 m with l_ref = the 1.25 -> 0.625 m change (dead_booth 0.28 %, up from 0.17 %); the agreement suite was green at 1.25 m and is re-run at 0.625 m; nothing regenerated to pass

- `phase05h_agreement_reference`: the four small rooms at the 0.625 m rung (dead_booth, living_room, classroom, club; l_ref = the 1.25 -> 0.625 m change; no tolerance, N or case changed)
## 2026-11-10

Reason: phase 05h: the BRAS validation scenes' simulated metrics after the AX37 (5.1) switch (the late tail's level from the propagated diffuse energy instead of the AX16 proxy; docs/review/phase-05h/ D-H1..D-H3); the nightly gate's change-detection baseline re-pinned on the switched build, tolerances unchanged

- `validation_baseline`: changed `bras_cr3_ls1_mp1.2000.C80`, `bras_cr3_ls1_mp1.4000.C80`, `bras_cr3_ls1_mp1.8000.EDT`, `bras_cr3_ls1_mp1.8000.C80`, `bras_cr3_ls1_mp1.8000.EDT_half`, `bras_cr3_ls1_mp2.63.C80`, `bras_cr3_ls1_mp2.125.C80`, `bras_cr3_ls1_mp2.250.C80`, `bras_cr3_ls1_mp2.500.EDT`, `bras_cr3_ls1_mp2.500.C80`, `bras_cr3_ls1_mp2.1000.EDT`, `bras_cr3_ls1_mp2.1000.C80`, `bras_cr3_ls1_mp2.1000.EDT_half`, `bras_cr3_ls1_mp2.2000.EDT`, `bras_cr3_ls1_mp2.2000.C80`, `bras_cr3_ls1_mp2.2000.EDT_half`, `bras_cr3_ls1_mp2.4000.EDT`, `bras_cr3_ls1_mp2.4000.C80`, `bras_cr3_ls1_mp2.4000.EDT_half`, `bras_cr3_ls1_mp2.8000.T20`, `bras_cr3_ls1_mp2.8000.EDT`, `bras_cr3_ls1_mp2.8000.C80`, `bras_cr3_ls1_mp2.8000.EDT_half`, `bras_cr3_ls1_mp2_fitted.63.EDT`, `bras_cr3_ls1_mp2_fitted.63.C80`, `bras_cr3_ls1_mp2_fitted.125.C80`, `bras_cr3_ls1_mp2_fitted.250.C80`, `bras_cr3_ls1_mp2_fitted.500.C80`, `bras_cr3_ls1_mp2_fitted.1000.C80`, `bras_cr3_ls1_mp2_fitted.2000.EDT`, `bras_cr3_ls1_mp2_fitted.2000.C80`, `bras_cr3_ls1_mp2_fitted.4000.T20`, `bras_cr3_ls1_mp2_fitted.4000.EDT`, `bras_cr3_ls1_mp2_fitted.4000.C80`, `bras_cr3_ls1_mp2_fitted.4000.EDT_half`, `bras_cr3_ls1_mp2_fitted.8000.EDT`, `bras_cr3_ls1_mp2_fitted.8000.C80`, `bras_cr3_ls1_mp2_fitted.8000.EDT_half`, `bras_cr3_ls1_mp3.500.C80`, `bras_cr3_ls1_mp3.1000.C80`, `bras_cr3_ls1_mp3.2000.C80`, `bras_cr3_ls1_mp3.4000.C80`, `bras_cr3_ls1_mp3.8000.EDT`, `bras_cr3_ls1_mp3.8000.C80`, `bras_cr3_ls1_mp3.8000.EDT_half`, `bras_cr3_ls1_mp3_fitted.500.C80`, `bras_cr3_ls1_mp3_fitted.1000.C80`, `bras_cr3_ls1_mp3_fitted.2000.C80`, `bras_cr3_ls1_mp3_fitted.4000.C80`, `bras_cr3_ls1_mp3_fitted.8000.C80`, `bras_cr3_ls1_mp4.8000.C80`, `bras_cr3_ls1_mp5.63.C80`, `bras_cr3_ls1_mp5.125.C80`, `bras_cr3_ls1_mp5.250.C80`, `bras_cr3_ls1_mp5.500.C80`, `bras_cr3_ls1_mp5.1000.C80`, `bras_cr3_ls1_mp5.2000.C80`, `bras_cr3_ls1_mp5.4000.C80`, `bras_cr3_ls1_mp5.8000.C80`, `bras_cr3_ls1_mp5_fitted.63.C80`, `bras_cr3_ls1_mp5_fitted.125.C80`, `bras_cr3_ls1_mp5_fitted.250.C80`, `bras_cr3_ls1_mp5_fitted.500.C80`, `bras_cr3_ls1_mp5_fitted.1000.C80`, `bras_cr3_ls1_mp5_fitted.2000.C80`, `bras_cr3_ls1_mp5_fitted.4000.C80`, `bras_cr3_ls1_mp5_fitted.8000.C80`, `bras_cr3_ls2_mp2.4000.C80`, `bras_cr3_ls2_mp2.8000.EDT`, `bras_cr3_ls2_mp2.8000.C80`, `bras_cr3_ls2_mp2.8000.EDT_half`, `bras_cr3_ls2_mp3.63.C80`, `bras_cr3_ls2_mp3.125.C80`, `bras_cr3_ls2_mp3.250.C80`, `bras_cr3_ls2_mp3.500.C80`, `bras_cr3_ls2_mp3.1000.C80`, `bras_cr3_ls2_mp3.2000.C80`, `bras_cr3_ls2_mp3.4000.C80`, `bras_cr3_ls2_mp3.8000.C80`, `bras_cr3_ls2_mp3_fitted.63.C80`, `bras_cr3_ls2_mp3_fitted.125.C80`, `bras_cr3_ls2_mp3_fitted.250.C80`, `bras_cr3_ls2_mp3_fitted.500.C80`, `bras_cr3_ls2_mp3_fitted.1000.C80`, `bras_cr3_ls2_mp3_fitted.2000.C80`, `bras_cr3_ls2_mp3_fitted.4000.C80`, `bras_cr3_ls2_mp3_fitted.8000.C80`, `bras_cr3_ls2_mp4.250.C80`, `bras_cr3_ls2_mp4.500.C80`, `bras_cr3_ls2_mp4.1000.C80`, `bras_cr3_ls2_mp4.2000.C80`, `bras_cr3_ls2_mp4.4000.C80`, `bras_cr3_ls2_mp4.8000.EDT`, `bras_cr3_ls2_mp4.8000.C80`, `bras_cr3_ls2_mp4.8000.EDT_half`, `bras_cr3_ls2_mp4_fitted.250.C80`, `bras_cr3_ls2_mp4_fitted.500.C80`, `bras_cr3_ls2_mp4_fitted.1000.C80`, `bras_cr3_ls2_mp4_fitted.2000.C80`, `bras_cr3_ls2_mp4_fitted.4000.C80`, `bras_cr3_ls2_mp4_fitted.8000.EDT`, `bras_cr3_ls2_mp4_fitted.8000.C80`, `bras_cr3_ls2_mp4_fitted.8000.EDT_half`, `bras_cr4_ls1_mp1.63.C80`, `bras_cr4_ls1_mp1.125.EDT`, `bras_cr4_ls1_mp1.125.C80`, `bras_cr4_ls1_mp1.250.C80`, `bras_cr4_ls1_mp1.500.C80`, `bras_cr4_ls1_mp1.1000.C80`, `bras_cr4_ls1_mp1.2000.EDT`, `bras_cr4_ls1_mp1.2000.C80`, `bras_cr4_ls1_mp1.2000.EDT_half`, `bras_cr4_ls1_mp1.4000.EDT`, `bras_cr4_ls1_mp1.4000.C80`, `bras_cr4_ls1_mp1.4000.EDT_half`, `bras_cr4_ls1_mp1.8000.T20`, `bras_cr4_ls1_mp1.8000.EDT`, `bras_cr4_ls1_mp1.8000.C80`, `bras_cr4_ls1_mp1.8000.EDT_half`, `bras_cr4_ls1_mp1_fitted.63.C80`, `bras_cr4_ls1_mp1_fitted.125.C80`, `bras_cr4_ls1_mp1_fitted.250.C80`, `bras_cr4_ls1_mp1_fitted.500.C80`, `bras_cr4_ls1_mp1_fitted.1000.C80`, `bras_cr4_ls1_mp1_fitted.2000.EDT`, `bras_cr4_ls1_mp1_fitted.2000.C80`, `bras_cr4_ls1_mp1_fitted.2000.EDT_half`, `bras_cr4_ls1_mp1_fitted.4000.EDT`, `bras_cr4_ls1_mp1_fitted.4000.C80`, `bras_cr4_ls1_mp1_fitted.4000.EDT_half`, `bras_cr4_ls1_mp1_fitted.8000.EDT`, `bras_cr4_ls1_mp1_fitted.8000.C80`, `bras_cr4_ls1_mp1_fitted.8000.EDT_half`, `bras_cr4_ls1_mp2.63.C80`, `bras_cr4_ls1_mp2.125.C80`, `bras_cr4_ls1_mp2.250.C80`, `bras_cr4_ls1_mp2.500.C80`, `bras_cr4_ls1_mp2.1000.C80`, `bras_cr4_ls1_mp2.2000.C80`, `bras_cr4_ls1_mp2.4000.EDT`, `bras_cr4_ls1_mp2.4000.C80`, `bras_cr4_ls1_mp2.4000.EDT_half`, `bras_cr4_ls1_mp2.8000.EDT`, `bras_cr4_ls1_mp2.8000.C80`, `bras_cr4_ls1_mp2.8000.EDT_half`, `bras_cr4_ls1_mp2_fitted.63.C80`, `bras_cr4_ls1_mp2_fitted.125.C80`, `bras_cr4_ls1_mp2_fitted.250.C80`, `bras_cr4_ls1_mp2_fitted.500.C80`, `bras_cr4_ls1_mp2_fitted.1000.C80`, `bras_cr4_ls1_mp2_fitted.2000.C80`, `bras_cr4_ls1_mp2_fitted.4000.C80`, `bras_cr4_ls1_mp2_fitted.8000.EDT`, `bras_cr4_ls1_mp2_fitted.8000.C80`, `bras_cr4_ls1_mp2_fitted.8000.EDT_half`, `bras_cr4_ls1_mp3.63.C80`, `bras_cr4_ls1_mp3.125.C80`, `bras_cr4_ls1_mp3.250.C80`, `bras_cr4_ls1_mp3.500.C80`, `bras_cr4_ls1_mp3.1000.C80`, `bras_cr4_ls1_mp3.2000.C80`, `bras_cr4_ls1_mp3.4000.EDT`, `bras_cr4_ls1_mp3.4000.C80`, `bras_cr4_ls1_mp3.4000.EDT_half`, `bras_cr4_ls1_mp3.8000.EDT`, `bras_cr4_ls1_mp3.8000.C80`, `bras_cr4_ls1_mp3.8000.EDT_half`, `bras_cr4_ls1_mp3_fitted.63.C80`, `bras_cr4_ls1_mp3_fitted.125.C80`, `bras_cr4_ls1_mp3_fitted.250.C80`, `bras_cr4_ls1_mp3_fitted.500.C80`, `bras_cr4_ls1_mp3_fitted.1000.C80`, `bras_cr4_ls1_mp3_fitted.2000.C80`, `bras_cr4_ls1_mp3_fitted.4000.C80`, `bras_cr4_ls1_mp3_fitted.8000.EDT`, `bras_cr4_ls1_mp3_fitted.8000.C80`, `bras_cr4_ls1_mp3_fitted.8000.EDT_half`, `bras_cr4_ls1_mp4.63.C80`, `bras_cr4_ls1_mp4.125.C80`, `bras_cr4_ls1_mp4.250.C80`, `bras_cr4_ls1_mp4.500.C80`, `bras_cr4_ls1_mp4.1000.EDT`, `bras_cr4_ls1_mp4.1000.C80`, `bras_cr4_ls1_mp4.2000.EDT`, `bras_cr4_ls1_mp4.2000.C80`, `bras_cr4_ls1_mp4.2000.EDT_half`, `bras_cr4_ls1_mp4.4000.EDT`, `bras_cr4_ls1_mp4.4000.C80`, `bras_cr4_ls1_mp4.4000.EDT_half`, `bras_cr4_ls1_mp4.8000.T30`, `bras_cr4_ls1_mp4.8000.T20`, `bras_cr4_ls1_mp4.8000.EDT`, `bras_cr4_ls1_mp4.8000.C80`, `bras_cr4_ls1_mp4.8000.T30_half`, `bras_cr4_ls1_mp4.8000.EDT_half`, `bras_cr4_ls1_mp4_fitted.63.C80`, `bras_cr4_ls1_mp4_fitted.125.C80`, `bras_cr4_ls1_mp4_fitted.250.C80`, `bras_cr4_ls1_mp4_fitted.500.C80`, `bras_cr4_ls1_mp4_fitted.1000.C80`, `bras_cr4_ls1_mp4_fitted.2000.EDT`, `bras_cr4_ls1_mp4_fitted.2000.C80`, `bras_cr4_ls1_mp4_fitted.2000.EDT_half`, `bras_cr4_ls1_mp4_fitted.4000.EDT`, `bras_cr4_ls1_mp4_fitted.4000.C80`, `bras_cr4_ls1_mp4_fitted.4000.EDT_half`, `bras_cr4_ls1_mp4_fitted.8000.EDT`, `bras_cr4_ls1_mp4_fitted.8000.C80`, `bras_cr4_ls1_mp4_fitted.8000.EDT_half`, `bras_cr4_ls1_mp5.250.C80`, `bras_cr4_ls1_mp5.500.C80`, `bras_cr4_ls1_mp5.2000.C80`, `bras_cr4_ls1_mp5.4000.EDT`, `bras_cr4_ls1_mp5.4000.C80`, `bras_cr4_ls1_mp5.4000.EDT_half`, `bras_cr4_ls1_mp5.8000.T20`, `bras_cr4_ls1_mp5.8000.EDT`, `bras_cr4_ls1_mp5.8000.C80`, `bras_cr4_ls1_mp5.8000.EDT_half`, `bras_cr4_ls1_mp5_fitted.125.C80`, `bras_cr4_ls1_mp5_fitted.250.C80`, `bras_cr4_ls1_mp5_fitted.500.C80`, `bras_cr4_ls1_mp5_fitted.2000.C80`, `bras_cr4_ls1_mp5_fitted.8000.EDT`, `bras_cr4_ls1_mp5_fitted.8000.C80`, `bras_cr4_ls1_mp5_fitted.8000.EDT_half`, `bras_cr4_ls2_mp1.63.C80`, `bras_cr4_ls2_mp1.125.C80`, `bras_cr4_ls2_mp1.250.C80`, `bras_cr4_ls2_mp1.500.C80`, `bras_cr4_ls2_mp1.1000.C80`, `bras_cr4_ls2_mp1.2000.EDT`, `bras_cr4_ls2_mp1.2000.C80`, `bras_cr4_ls2_mp1.2000.EDT_half`, `bras_cr4_ls2_mp1.4000.EDT`, `bras_cr4_ls2_mp1.4000.C80`, `bras_cr4_ls2_mp1.4000.EDT_half`, `bras_cr4_ls2_mp1.8000.C80`, `bras_cr4_ls2_mp1.8000.EDT_half`, `bras_cr4_ls2_mp1_fitted.63.C80`, `bras_cr4_ls2_mp1_fitted.125.C80`, `bras_cr4_ls2_mp1_fitted.250.C80`, `bras_cr4_ls2_mp1_fitted.500.C80`, `bras_cr4_ls2_mp1_fitted.1000.C80`, `bras_cr4_ls2_mp1_fitted.2000.C80`, `bras_cr4_ls2_mp1_fitted.4000.C80`, `bras_cr4_ls2_mp1_fitted.8000.EDT`, `bras_cr4_ls2_mp1_fitted.8000.C80`, `bras_cr4_ls2_mp1_fitted.8000.EDT_half`, `bras_cr4_ls2_mp2.63.C80`, `bras_cr4_ls2_mp2.125.C80`, `bras_cr4_ls2_mp2.250.C80`, `bras_cr4_ls2_mp2.500.C80`, `bras_cr4_ls2_mp2.1000.C80`, `bras_cr4_ls2_mp2.2000.EDT`, `bras_cr4_ls2_mp2.2000.C80`, `bras_cr4_ls2_mp2.2000.EDT_half`, `bras_cr4_ls2_mp2.4000.EDT`, `bras_cr4_ls2_mp2.4000.C80`, `bras_cr4_ls2_mp2.4000.EDT_half`, `bras_cr4_ls2_mp2.8000.T20`, `bras_cr4_ls2_mp2.8000.EDT`, `bras_cr4_ls2_mp2.8000.C80`, `bras_cr4_ls2_mp2.8000.EDT_half`, `bras_cr4_ls2_mp2_fitted.63.C80`, `bras_cr4_ls2_mp2_fitted.125.C80`, `bras_cr4_ls2_mp2_fitted.250.C80`, `bras_cr4_ls2_mp2_fitted.500.C80`, `bras_cr4_ls2_mp2_fitted.1000.C80`, `bras_cr4_ls2_mp2_fitted.2000.C80`, `bras_cr4_ls2_mp2_fitted.4000.C80`, `bras_cr4_ls2_mp2_fitted.8000.EDT`, `bras_cr4_ls2_mp2_fitted.8000.C80`, `bras_cr4_ls2_mp2_fitted.8000.EDT_half`, `bras_cr4_ls2_mp3.2000.C80`, `bras_cr4_ls2_mp3.4000.EDT`, `bras_cr4_ls2_mp3.4000.C80`, `bras_cr4_ls2_mp3.4000.EDT_half`, `bras_cr4_ls2_mp3.8000.EDT`, `bras_cr4_ls2_mp3.8000.C80`, `bras_cr4_ls2_mp4.63.C80`, `bras_cr4_ls2_mp4.125.C80`, `bras_cr4_ls2_mp4.250.C80`, `bras_cr4_ls2_mp4.500.C80`, `bras_cr4_ls2_mp4.1000.C80`, `bras_cr4_ls2_mp4.2000.EDT`, `bras_cr4_ls2_mp4.2000.C80`, `bras_cr4_ls2_mp4.2000.EDT_half`, `bras_cr4_ls2_mp4.4000.EDT`, `bras_cr4_ls2_mp4.4000.C80`, `bras_cr4_ls2_mp4.4000.EDT_half`, `bras_cr4_ls2_mp4.8000.EDT`, `bras_cr4_ls2_mp4.8000.C80`, `bras_cr4_ls2_mp4.8000.EDT_half`, `bras_cr4_ls2_mp4_fitted.63.C80`, `bras_cr4_ls2_mp4_fitted.125.C80`, `bras_cr4_ls2_mp4_fitted.250.C80`, `bras_cr4_ls2_mp4_fitted.500.C80`, `bras_cr4_ls2_mp4_fitted.1000.C80`, `bras_cr4_ls2_mp4_fitted.2000.C80`, `bras_cr4_ls2_mp4_fitted.4000.C80`, `bras_cr4_ls2_mp4_fitted.8000.EDT`, `bras_cr4_ls2_mp4_fitted.8000.C80`, `bras_cr4_ls2_mp4_fitted.8000.EDT_half`, `bras_cr4_ls2_mp5.8000.EDT`, `bras_cr4_ls2_mp5.8000.C80`


## 2026-11-10

Reason: phase 05h, review file 32 M4 (a): the H3-F6 re-export (the export script now takes the finest two rungs present per case) also moved the AX45 cases `dt6_small_room_e0` / `_e1` to the 0.625 m rung (their 2.5 → 1.25 → 0.625 m ladder converges, ratio 0.14) and, for the single-rung cases (W2, the CS-NW+ emitter-1 and 0.3 m placements, the emitter-wall case; still uncertified), records their one rung as `ref_fine` instead of `ref_coarse`; no gated value changed by this note, which only completes the record of that re-export. Provenance of the references: `tools/validation/data/phase05h_hybrid_references.provenance.json`.

- `phase05h_agreement_reference`: record completed (no value changed)

## 2026-11-10

Reason: phase 05h, D-H1 (v)(b): the AX38 4c restore gate's growth-bound baselines (constants in tests/unit/test_diffuse_records.cpp, not a golden file) pinned from the first three-OS CI run of the records test (run 42909003931): median-of-10 restore with the diffuse solve at the gated low-alpha cube, 96 kHz: Linux 2043 ms (14 x worst 29.62 s), macOS 2106 ms (14 x worst 37.37 s); Windows and the flutter scene stay strict. Re-pinned here whenever W_max or n*_max is re-derived.

- `(records-test constants)`: restore-gate baselines pinned (no golden file changed)

## 2026-11-10

Reason: phase 05h session 2 (D-H2 (a)/(c), decider file 19): the last references of this session's hybrid_fast runs at 1.25 m landed (W2 both emitters; the CS-NW+ listener wall / edge / corner at 0.1 m and the wall at 0.3 m for both emitters; the emitter-wall case, emitter 0; the W1 listener-wall 0.1 m emitter 1), promoting 80 case-bands from reported to gated: AX43 410 of 560, AX45 72 of 72 (482 certified case-bands); no existing reference value changed; the gated counts pinned in tests/unit/test_diffuse_agreement.cpp re-pinned to 410 / 72. Provenance: tools/validation/data/phase05h_hybrid_references.provenance.json (28 rows at 1.25 m, 28 at 2.5 m, 10 at 0.625 m).

- `phase05h_agreement_reference`: extended (80 case-bands promoted to gated: W2_e0, W2_e1, W1_listener_wall_0.1_e1, W1_listener_edge_0.1_e0/e1, W1_listener_corner_0.1_e0/e1, W1_listener_wall_0.3_e0/e1, W1_emitter_wall_0.1_e0, 8 bands each)
