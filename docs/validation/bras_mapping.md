# BRAS → shoebox mapping (Phase 05)

Status: **room selection and reduction rules committed before any simulated-vs-measured number was
computed** (phase-05 Data; decider report 8, accepted by Maisara, 2026-11-05). No room is dropped
after results are seen. The reduction outputs (box dimensions, per-face α and s, positions) are
generated from these rules by `tools/validation/make_bras_scenes.py` and listed in §5 (appended
when they are generated, also before any comparison).

Data: BRAS — *Benchmark for Room Acoustical Simulation*, Aspöck, Brinkmann, Ackermann, Weinzierl,
Vorländer; TU Berlin / RWTH Aachen; DepositOnce, DOI 10.14279/depositonce-6726.3 (v3), licence
CC BY-SA 4.0. This file and everything derived from BRAS in the repository are adaptations under
CC BY-SA 4.0 (see `docs/THIRD_PARTY.md`). Files are fetched by `tools/validation/fetch_bras.py`
(SHA-256 manifest `tools/validation/bras_manifest.json`) and never committed.

**What the comparison is.** BRAS's own documentation states that the complex rooms "cannot serve
as a direct reference but may be used to compare the results from different simulations based on
indentical input data" (as printed; researcher finding F2). Every α and s is an estimate
(F6, F7). Phase 05 results against BRAS are therefore **evidence, not validation** of NFR-1.

## 1. Room selection

BRAS has four complex rooms (CR1–CR4); the seven reference scenes RS1–RS7 are single
reflections, diffraction and seat-dip set-ups in (hemi-)anechoic chambers, not rooms (F1).

| Room | Description (BRAS) | Model V / S (`_descr/mat_CRx.txt`) | Selected | Reason |
|---|---|---|---|---|
| CR1 | Coupled rooms: reverberation chamber + laboratory, open door | 121.4 + 102.3 m³ | **no** | Two coupled volumes; a shoebox with one Eyring decay cannot represent a coupled-room double slope (phase-05 Data: "CR1 excluded as coupled"). |
| CR2 | Seminar room, RWTH Aachen | 146.1 m³ / 202.53 m² | **yes** | Single volume, "relatively simple and easy to describe geometry, but challenging low frequency behaviour" (BRAS sheet); closest of the four to a rectangular box. |
| CR3 | Small hall (chamber music hall), Konzerthaus Berlin | 3 330.6 m³ / 2 763.0 m² | **yes** | Single main volume with a coupled attic joined by openings (F3). Kept: the dataset gives one model volume and one material set, and the phase file excludes only CR1. The attic coupling is a known reduction limit, reported with the results, not a reason to drop the room. |
| CR4 | Auditorium Maximum, TU Berlin | 8 656.5 m³ / 5 851.3 m² | **yes** | Single volume, "relatively simple and easy to describe geometry" (BRAS sheet); raked seating and stage reduce to box faces by the face rule. |

Volume: the documentation sheet gives CR3 as 2 350 m³ "excluding attic"; the material file states
V = 3 330.6 m³ and S = 2 763.0 m² "based on provided 3d models", the values its fitted α set was
computed with. The reduction uses the material files' V and S (they belong to the same model as
the surface areas). The difference is printed in the report.

Every omni (dodecahedron) RIR the dataset provides for the selected rooms is used: 2 sources ×
5 receivers per room, 30 source/receiver pairs (`CRx_RIR_LSi_MPj_Dodecahedron.wav`; CR3 also has a
third source position, measured with the Genelec only, which is not omni and is not used, AQ8).

## 2. Inputs per room

- Geometry: `CRx.skp` (SketchUp 2015), read by `tools/validation/skp_reader.py` (this
  repository's own reader). Accepted only if every material's total area reproduces
  `_descr/mat_CRx.txt` to the printed precision (0.01 m², ±0.1 % allowed for rounding of large
  areas) and every loop vertex lies on its face's plane.
- Source and receiver positions: `RIRs/CRx_RIRs_Dodecahedron.sofa` (EmitterPosition,
  ReceiverPosition, model frame, metres), extracted once by
  `tools/validation/extract_bras_geometry.py` into `tools/validation/data/bras_geometry.json`
  together with the per-face reduction inputs (derived data, CC BY-SA 4.0).
- Materials: `_csv/initial_estimates/mat_CRx_*.csv` — **primary run** (as documented).
  `_csv/fitted_estimates/` — **secondary run, labelled "fitted (circular for T30)"**: its α were
  scaled per band so that Eyring matches the measured T (F6), so it partly contains the answer.
  Each csv has third-octave α (line 2) and s (line 3), 20 Hz–20 kHz.
- Measurement conditions (BRAS sheets): CR2 19.5 °C, 41.7 % RH; CR3 22.4 °C, 40.9 % RH; CR4
  20.9 °C, 37.5 % RH. Used only for the AX4 override renders (phase-05 scope 6).

## 3. Reduction rules (generic; the same code for every room, no per-room parameter)

1. **Faces.** Every model face (polygon, with holes) with a BRAS material is a "documented
   surface". The model is first rotated about z by the angle that aligns the area-weighted wall
   normals with the axes (θ = ¼·atan2(Σ A sin 4φ, Σ A cos 4φ) over faces with |n_z| < 0.5), then
   each face is assigned to the box face whose outward normal is closest to its own (the largest
   |n·e|; ties go to the floor/ceiling first, then x, then y). Faces of other materials (none
   expected) are reported.
2. **Dimensions** (phase-05 Data): h = V / A_floor, where A_floor is the total area assigned to the
   floor face (the model's floor area: BRAS documents no dimensions, F4). a·b = V/h and
   a + b = (S − 2V/h)/(2h), longer side along x (AQ1). Real solution iff S ≥ 2V/h + 4√(V·h);
   otherwise the square floor a = b = √(V/h) and the S error is reported.
3. **Absorption** per face and octave band: α_face = Σ Sᵢαᵢ / S_face over the assigned surfaces,
   S_face the box face area, clamped to ≤ 1 (every clamp and the absorption area it loses are
   reported; AQ3's lower limit 0.01 is applied the same way and reported). This conserves the
   absorption area A per face and in total; with S matched, ᾱ and the Eyring T are preserved.
4. **Scattering** per face and octave band: s_face = Σ Sᵢ(1−αᵢ)sᵢ / Σ Sᵢ(1−αᵢ) (reflected-energy
   weights, Vorländer Eqs. 3.23–3.24), then one broadband s per face by AX17 (mean of the 500 Hz,
   1 kHz and 2 kHz octave values). Per-band s is kept for the B10 run of the reference hybrid.
5. **Third octaves → octaves (AX25):** an octave band's α is the arithmetic mean of its three
   third-octave values (63 Hz: 50, 63, 80 Hz; … 8 kHz: 6.3, 8, 10 kHz; the three tile the octave,
   Vorländer Eq. 1.39; A is linear in α, Eq. 4.30, so the order relative to rule 3 does not
   matter); its s is the reflected-energy-weighted mean Σ(1−α_k)s_k / Σ(1−α_k) over the three, as
   in rule 4 (interrogator AX25-1…6). Eyring on the octave-mean ᾱ underestimates the octave's
   initial decay rate by ≈ Var_k(ᾱ_k)/(2(1−ᾱ)²) (Kuttruff Eqs. 3.68, 5.22; AX25-4), reported.
6. **Positions (AX24)** — keep the real source–receiver distance r and the source and receiver
   heights above the floor (phase-05 scope 2):
   - both heights are measured vertically to one floor plane per pair: z_floor, the elevation of
     the highest floor-assigned face below the pair's horizontal midpoint (where the floor
     reflection lands), or the area-weighted mean floor elevation when none is below it. One
     plane per pair, so the box floor reflection corresponds to one real face (Vorländer §11.3.1;
     interrogator AX24-4) and Δh = Δz;
   - horizontal: the midpoint of the pair is mapped proportionally from the floor-assigned faces'
     bounding box (rotated frame) to the box floor; the pair keeps its real horizontal direction
     and horizontal separation about that midpoint, so r is kept exactly (AX24-5);
   - if a point falls closer than AX6's 0.1 m to a box face it is moved to 0.1 m and the r error
     is reported; the heights are capped at h − 0.1 m the same way.
   - Both contract emitters (L, R) are placed at the source; emitter 0 (L) is analysed.
7. **Scene settings:** `outputMode` irrelevant (`render_cli --mode omni`), `tailSeed` fixed per
   scene (the nightly gate is deterministic), 44.1 kHz renders (the BRAS sample rate).

## 4. Known limits of the reduction (reported, not corrected)

- Heights are vertical; over a sloped floor face the normal distance that sets the reflection
  delay is (z − z_floor)·cos θ (Vorländer Eq. 11.33; AX24-3). Proportional mapping keeps wall
  distances only where the box extent equals the model's (AX24-6). Points moved to AX6's 0.1 m
  are near grazing for that face (AX24-8). The specular box floor has no seat-dip attenuation
  over audience seating (Kuttruff §6.7; AX24-9).

- Non-rectangular plan, raked floors, balconies, the stage house and the coupled attic (CR3) are
  represented only through the face-rule areas and α.
- The face rule assigns sloped seating to the floor and splays to the nearest wall; the x/y wall
  split of the box is approximate (phase-05 Data).
- AX17 broadband s: BRAS s rises as √f, so the AX17 mean overstates s at 500 Hz by up to +47 %
  and understates it at 2 kHz by up to −26 % (F7; decider report 11).
- Whether any room combines uneven α with low s is stated in §5 (Raise with Maisara, item 1).

## 5. Reduction results

(Generated by `tools/validation/make_bras_scenes.py`; appended before any comparison.)
