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

## 2026-11-11

Reason: phase 05h, D-H1 (v)(d) (phase-05h section 5 (d)): the AX38 4c restore gate's Windows entry at the gated low-alpha cube crossed 30 s on CI run 42942694523 (14 x worst 36.73 s, median-of-10 restore with the solve 2589 ms; strict 29.04 / 29.50 / 28.57 s on the three earlier green runs; the shared runner was 25-30 % slower on the restore, flutter and full-rebuild records of that run, the (iv) load inside its earlier range) and enters the register as a listed defect with that run's median as its growth-bound baseline (constants in tests/unit/test_diffuse_records.cpp, not a golden file); no re-run, no W_max cut, no range change, no seam; remedy phase-07c conditions 9-10 or Phase 13's release-machine re-check (orchestrator file 53).

- `(records-test constants)`: the Windows low-alpha entry listed, baseline 2589 ms (no golden file changed)

## 2026-11-11 (RG-1)

Reason: phase 05h, DECISION RG-1 (decider files 64/66/68/70, interrogator files 65/67/69/71; D-H1 (v) amended for Maisara): the AX38 4c restore gate asserts on hosted runners what is runner-independent and prints what is not. Constants in tests/unit/test_diffuse_records.cpp (not a golden): the register's growth-bound baselines become the means of the in-window runs on file (Linux 2068 ms from runs 42909003931 / 42924781618; Windows 2028 ms from 42909003931 / 42924781618; macOS 1817 ms from 42924781618 / 42935789745 / 42949252041, print only), the flutter restore references (Linux 701, Windows 737, macOS 484 ms) and the low-alpha / flutter ratio baselines (3.05 / 2.83 / 3.75) from the measured runs on file; the guard window +-5 %, the growth factor 1.10, the ratio warning at 1.20, the macOS trigger 2172 ms (1.15 x the mean of the four measured macOS medians; round 4); the work pins per gated scene (unit-decay length 1152000 / 377517 samples and synthesis FFT size 2097152 / 524288 at 96 kHz, from the [probe-restore-split] probe). The strict 30 s stays asserted at the flutter scene; the low-alpha entries' 30 s line and the macOS growth bound are printed with WARNING. Re-pinned only when the restore path changes (one run PROVISIONAL, >= 3 runs with a reason here).

- `(records-test constants)`: the RG-1 register form (no golden file changed)

## 2026-11-11

Reason: phase 05i scope 1 (D-H2 (a)/(c), decider file 19; AX43 (c)): the 30 BRAS pairs' outer bands (250 Hz and 4 kHz, then 125 Hz and 8 kHz, 63 Hz last) referenced at the 2.5 and 1.25 m rungs by tools/validation/compute_phase05i_bras_references.py (phase05b.step_r1's recipe per band column; its --check reproduces the committed R1 500 Hz values in CR2 and CR3 exactly; provenance in tools/validation/data/phase05i_bras_references.provenance.json); every one of the 150 case-bands certifies (l_ref <= 0.38 %) and is gated under rule G-a: AX43 560 of 560, AX45 72 of 72; no gated reference value changed; in these 150 case-bands the reported, never-gated single-rung value (ref_coarse, from phase05_scope6.json: the full ref_hybrid with air in the kernel at one patch size min(dims)/2 = 1.45 / 2.20 / 2.47 m, uncertified) is replaced by the two certified rungs (up to 0.33 % apart, the size of l_ref; the scope-6 values stay in phase05_scope6.json); the 63 Hz column is gated as an agreement with ref_hybrid, never claimed as a room validation below the Schroeder frequency

- `phase05h_agreement_reference`: extended (150 case-bands promoted to gated: the 30 BRAS pairs at 63, 125, 250 Hz, 4 and 8 kHz; no tolerance, N or case changed)

## 2026-11-11 (05i, Q1)

Reason: phase 05i, decider files 5/9 (Q1), interrogator files 6/10 (SURVIVES): the AX38 4c restore gate's Linux and Windows low-alpha register entries close under rule (c) on phase 05i's runs (CI run 43007183782: 14 x worst 27.61 s and 28.74 s, both in-window, growth bound asserted and met; the PR's run of record confirms it, else the entry stays listed). Constants in tests/unit/test_diffuse_records.cpp (not a golden): `listed` false for those two entries, which changes only the printed text; no assertion changes (the hosted-runner form stands until Phase 13).

- `(records-test constants)`: the Linux and Windows low-alpha entries closed under AX38 4c (c), `listed` false, print only (no golden file changed)

## 2026-11-11 (05i, D-Q5)

Reason: phase 05i, DECISION D-Q5 (decider file 9, Seat 5 file 8, interrogator file 10: SURVIVES): the AX38 4c restore gate's per-scene solve-median bound. `kSolveWarn` 1.20 x the scene's in-window solve baseline per OS (`solveRefMs`: Linux 80.9 / 131.2 ms and macOS 83.7 / 102.7 ms from run 43007183782; Windows 90.4 / 144.4 ms from runs 42964823518 and 43007183782; low-alpha / flutter), PROVISIONAL (n = 1-2), printed as `SOLVE` in the scene's `warnings=`, never asserted; re-derived from >= 3 in-window runs at the 07c re-pin.

- `(records-test constants)`: solve-median baselines (in-window runs 42964823518 Windows, 43007183782 all OSes) and `kSolveWarn` 1.20, PROVISIONAL (no golden file changed)

## 2026-11-12 (05i follow-up, Q1)

Reason: phase 05i, decider file 9 (Q1, answer 4), interrogator file 10 (SURVIVES): an AX38 4c restore-gate register entry closes under rule (c) only if it passed 30 s on every 05i run. The 05i Q1 entry of 2026-11-11 said Linux and Windows close; on the run of record 43031773338 (docs/review/phase-05i/19) Windows printed OVER30S (46.63 s, slow runner, flutterDev +48.9 %), so under decider file 9's rule it stays listed (Linux passed both runs, 27.61 / 27.40 s, and stays closed). Constants in tests/unit/test_diffuse_records.cpp (not a golden): `listed` true for the Windows low-alpha entry, which changes only the printed text; no assertion, baseline or `solveRefMs` changes. Owed to the contractor's review push of PR #30 (interrogator file 22, P05I-120), applied here as a follow-up.

- `(records-test constants)`: the Windows low-alpha entry listed again (AX38 4c (c) 'otherwise' branch, phase-05i §3.3 (ii)); print only (no golden file changed)

## 2026-11-13 (07c-1b, scope 4)

Reason: phase 07c-1b scope 4 (AX48 E_model fingerprint): the per-platform hashes of the fingerprint fixtures' E_b are pinned from CI, each identical on the three runs of phase 07c-1's final code (43242209571 on 6db81b6, 43258505284 on 39f751b, 43291051799 on 53d1333; `docs/review/phase-07c-1/41`, `42`, `44`): Linux `22f009efe0004e82`, macOS `9d4f48216097ae94`, Windows `a70a95cd5962863b`, modelId 1. A later change of E_b with DiffuseLimits unchanged fails the test and must bump `kEstimatorModelId` (AX48). A negative check (`[ax48-fingerprint-negative]`) shows a one-ulp change of any E_b band changes the hash.

- `(records-test constants)`: `kPins` in `records: AX48 E_model fingerprint` pinned (no golden file changed)

## 2026-11-13 (07c-1b, condition 7 re-pin)

Reason: phase-07c-1b condition 7 / D-B5 / FM-GROWTH (decider files 4, 8, 11; interrogator file 12): the AX38 4c restore gate's S2 pin, from the three green S2 CI runs 43389296112, 43402114873 and 43412038058 (code 9717a58), computed by `tools/ci/repin_gate.py` on the nine build-job logs and pasted as printed (`docs/review/phase-07c-1b/22-repin-gate-output.md`). Constants in tests/unit/test_diffuse_records.cpp (not a golden): the `S2Pin` of every `kGateRegister` entry (ratioRef, ratioMaxOverMin, flutterRefMs, baselineMedianMs, solveRefMs, solveK; runs = 3 per OS and scene; Linux ratio max/min 1.3681 and macOS print-only, Windows asserted), and the macOS trigger `kMacGrowthTriggerMs` 2172 -> 1703 ms (floor(1.15 x 1481), the mean of the macOS low-alpha medians 1459 / 1398 / 1586) with `kMacGrowthTriggerS2Runs` 0 -> 3. The unused `kS2Pending` placeholder is removed.

- `(records-test constants)`: S2 pin of the six restore-gate register entries and the macOS growth trigger (no golden file changed)
- `(records-test constants)`: the macOS and Windows low-alpha entries closed under AX38 4c (c) (E1, D-B5 (v)): 14 x worst <= 30 s on every S2 run (macOS 23.46 / 22.44 / 24.08 s, Windows 20.24 / 15.96 / 19.59 s), `listed` false, print only (no golden file changed)
