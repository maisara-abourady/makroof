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

(Generated by `tools/validation/make_bras_scenes.py` from `tools/validation/data/bras_geometry.json`; do not edit by hand. Areas in m², octave α at 500 Hz / 1 kHz / 2 kHz.)

### CR2

Model: V = 146.1 m³, S = 202.53 m² (documented); materials reproduced by the reader: ceiling 51.62 (doc 51.62), concrete 56.94 (doc 56.94), floor 49.29 (doc 49.29), plaster 34.93 (doc 34.93), windows 9.75 (doc 9.75); unpainted faces (not a BRAS material, ignored) 0.62 m²; rotation θ = -0.09°; floor area (floor-assigned) A_floor = 50.48 m².

Box: W × D × H = 13.921 × 3.626 × 2.894 m (h = V/A_floor); square-floor fallback: no; S(box) = 202.53 m² (+0.00 % vs documented S); model long side along y swapped to x: yes.

| face | box area | assigned area | assigned materials | α initial | α fitted | s (AX17) | s 500 / 1k / 2k |
|---|---|---|---|---|---|---|---|
| xMin | 10.5 | 23.9 | plaster 18.1, concrete 4.0, ceiling 1.8 | 0.128 / 0.124 / 0.132 | 0.100 / 0.107 / 0.113 | 0.081 | 0.058 / 0.076 / 0.108 |
| xMax | 10.5 | 23.9 | concrete 12.4, windows 9.7, ceiling 1.8 | 0.149 / 0.155 / 0.204 | 0.116 / 0.133 / 0.175 | 0.071 | 0.057 / 0.067 / 0.090 |
| yMin | 40.3 | 26.9 | concrete 26.6, ceiling 0.2, plaster 0.0 | 0.046 / 0.045 / 0.046 | 0.036 / 0.039 / 0.039 | 0.066 | 0.051 / 0.062 / 0.087 |
| yMax | 40.3 | 26.9 | plaster 16.7, concrete 10.0, ceiling 0.1 | 0.039 / 0.038 / 0.040 | 0.031 / 0.033 / 0.035 | 0.069 | 0.051 / 0.065 / 0.092 |
| floor | 50.5 | 50.5 | floor 49.3, concrete 1.2, plaster 0.0 | 0.090 / 0.076 / 0.073 | 0.069 / 0.065 / 0.062 | 0.056 | 0.050 / 0.051 / 0.067 |
| ceiling | 50.5 | 50.4 | ceiling 47.7, concrete 2.7 | 0.068 / 0.056 / 0.056 | 0.052 / 0.048 / 0.048 | 0.211 | 0.144 / 0.202 / 0.286 |

Clamps (AQ3 range [0.01, 1]): none.
Total absorption area A (box vs documented surfaces) at 500 Hz / 1 kHz / 2 kHz: 14.3 vs 14.3 / 13.0 vs 13.0 / 13.5 vs 13.5 m².

| pair | r real (m) | r box (m) | h source / receiver (m) | floor face found under the midpoint | moved (AX6) |
|---|---|---|---|---|---|
| LS1_MP1 | 4.443 | 4.443 | 0.72 / 1.23 | yes | – |
| LS1_MP2 | 2.502 | 2.502 | 0.72 / 1.23 | yes | – |
| LS1_MP3 | 2.055 | 2.055 | 0.72 / 1.23 | yes | – |
| LS1_MP4 | 3.110 | 3.110 | 0.72 / 1.23 | yes | – |
| LS1_MP5 | 2.296 | 2.296 | 0.72 / 1.23 | yes | – |
| LS2_MP1 | 1.899 | 1.899 | 0.72 / 1.23 | yes | – |
| LS2_MP2 | 3.086 | 3.086 | 0.72 / 1.23 | yes | – |
| LS2_MP3 | 3.732 | 3.732 | 0.72 / 1.23 | yes | – |
| LS2_MP4 | 3.406 | 3.406 | 0.72 / 1.23 | yes | – |
| LS2_MP5 | 4.461 | 4.461 | 0.72 / 1.23 | yes | – |

### CR3

Model: V = 3330.6 m³, S = 2763.0 m² (documented); materials reproduced by the reader: ceiling 168.46 (doc 168.46), floor 342.53 (doc 342.53), plaster 450.27 (doc 450.27), seating 178.90 (doc 178.90), stagePanels 425.55 (doc 425.55), structuredPlaster 1171.93 (doc 1171.93), windows 25.38 (doc 25.38); unpainted faces (not a BRAS material, ignored) 0.00 m²; rotation θ = -0.05°; floor area (floor-assigned) A_floor = 757.34 m².

**Not rendered:** the box violates the contract (W = 136.37 m outside AX6's [1.5, 100.0] m), so no scene is written for this room. The reduction rule (rule 2) needs a plan decision (BUILD_PLAN §0, Phase 05 notes).

Box: W × D × H = 136.373 × 5.553 × 4.398 m (h = V/A_floor); square-floor fallback: no; S(box) = 2763.00 m² (-0.00 % vs documented S); model long side along y swapped to x: no.

| face | box area | assigned area | assigned materials | α initial | α fitted | s (AX17) | s 500 / 1k / 2k |
|---|---|---|---|---|---|---|---|
| xMin | 24.4 | 288.0 | stagePanels 157.0, plaster 68.0, structuredPlaster 44.9, floor 17.5, seating 0.6 | 1.000 / 1.000 / 1.000 | 1.000 / 1.000 / 1.000 | 0.079 | 0.064 / 0.077 / 0.096 |
| xMax | 24.4 | 272.3 | stagePanels 113.7, plaster 84.1, structuredPlaster 50.3, floor 16.3, windows 4.2, seating 3.8 | 1.000 / 1.000 / 1.000 | 1.000 / 1.000 / 1.000 | 0.089 | 0.070 / 0.086 / 0.111 |
| yMin | 599.7 | 338.3 | plaster 134.1, structuredPlaster 121.0, stagePanels 51.7, windows 21.2, floor 6.6, seating 3.7 | 0.060 / 0.074 / 0.087 | 0.071 / 0.067 / 0.062 | 0.114 | 0.083 / 0.110 / 0.149 |
| yMax | 599.7 | 338.7 | plaster 143.9, structuredPlaster 122.3, stagePanels 51.7, floor 15.9, seating 4.8 | 0.062 / 0.075 / 0.087 | 0.073 / 0.068 / 0.062 | 0.117 | 0.085 / 0.113 / 0.154 |
| floor | 757.3 | 757.3 | structuredPlaster 299.1, floor 273.0, seating 166.1, stagePanels 17.3, plaster 1.9 | 0.143 / 0.173 / 0.228 | 0.169 / 0.156 / 0.163 | 0.207 | 0.151 / 0.207 / 0.262 |
| ceiling | 757.3 | 768.4 | structuredPlaster 534.3, ceiling 168.5, stagePanels 34.1, plaster 18.3, floor 13.2 | 0.117 / 0.152 / 0.178 | 0.138 / 0.138 / 0.128 | 0.170 | 0.117 / 0.164 / 0.230 |

Clamps (AQ3 range [0.01, 1]): xMin 500 Hz α = 1.030 → 1.0, ΔA = -0.74 m²; xMin 1000 Hz α = 1.260 → 1.0, ΔA = -6.36 m²; xMin 2000 Hz α = 1.456 → 1.0, ΔA = -11.15 m²; xMin 4000 Hz α = 1.594 → 1.0, ΔA = -14.52 m²; xMin 8000 Hz α = 1.780 → 1.0, ΔA = -19.04 m²; xMax 500 Hz α = 1.054 → 1.0, ΔA = -1.32 m²; xMax 1000 Hz α = 1.281 → 1.0, ΔA = -6.86 m²; xMax 2000 Hz α = 1.499 → 1.0, ΔA = -12.19 m²; xMax 4000 Hz α = 1.589 → 1.0, ΔA = -14.38 m²; xMax 8000 Hz α = 1.775 → 1.0, ΔA = -18.93 m².
Total absorption area A (box vs documented surfaces) at 500 Hz / 1 kHz / 2 kHz: 319.3 vs 321.3 / 384.3 vs 397.5 / 460.9 vs 484.2 m².

| pair | r real (m) | r box (m) | h source / receiver (m) | floor face found under the midpoint | moved (AX6) |
|---|---|---|---|---|---|
| LS1_MP1 | 10.126 | 10.126 | 2.38 / 1.23 | yes | – |
| LS1_MP2 | 4.573 | 4.573 | 2.38 / 1.23 | yes | – |
| LS1_MP3 | 11.312 | 11.312 | 2.38 / 1.23 | yes | – |
| LS1_MP4 | 9.078 | 9.078 | 2.38 / 1.23 | yes | – |
| LS1_MP5 | 15.692 | 15.679 | 2.38 / 1.23 | yes | MP5 axis y 0.062 -> 0.100 |
| LS2_MP1 | 11.396 | 11.396 | 2.38 / 1.23 | yes | – |
| LS2_MP2 | 7.811 | 7.512 | 1.38 / 0.23 | yes | MP2 axis y 5.892 -> 5.453 |
| LS2_MP3 | 13.335 | 13.335 | 2.38 / 1.23 | yes | – |
| LS2_MP4 | 9.259 | 9.259 | 2.38 / 1.23 | yes | – |
| LS2_MP5 | 16.135 | 16.135 | 2.38 / 1.23 | yes | – |

### Classification (Raise with Maisara, item 1)

Absorption unevenness = largest single-face share of the total absorption area and the ratio ᾱ(floor+ceiling)/ᾱ(walls) at 1 kHz; scattering = the broadband s (AX17) of the faces that hold most of the absorption. No threshold is applied (phase-05 scope 6); the statement below reads the numbers.

| room | largest face share of A (1 kHz) | ᾱ(floor+ceiling)/ᾱ(walls) (1 kHz) | s of that face | area-weighted mean s |
|---|---|---|---|---|
| CR2 | 0.30 (floor) | 1.06 | 0.056 | 0.101 |
| CR3 | 0.34 (floor) | 1.46 | 0.207 | 0.155 |

