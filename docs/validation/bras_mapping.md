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

**Volume check (phase-05e scope (a); done 2026-11-06 before any simulated-vs-measured number).**
AX26 keeps the model volume. The documentation sheets (Aspöck et al., pp. 25–27) give CR2 145 m³,
CR3 2 350 m³ "excluding the attic", CR4 8 650 m³; the material files give 146.1, 3 330.6 and
8 656.5 m³ "based on provided 3d models". Two checks, neither involving a simulated IR:
1. *Enclosed volume of the model* (divergence theorem over every face of `CRx.skp`, unpainted
   faces included, read by `skp_reader.py`): CR2 146.09 m³, CR3 3 330.64 m³. The material files'
   V is the enclosed volume of the model whose surface areas the reduction uses.
2. *Which V the dataset's own Eyring fit used* (documentation Eq. (1); the fitted α were scaled so
   that Eyring matches the measured T): Eyring on the fitted α with the material file's S and the
   ISO 9613-1 air at the documented measurement conditions, against BRAS's own measured
   third-octave T20 (`Evaluation_CRx_T20.txt`), 100 Hz–10 kHz, mean / max |error|:
   CR2 V = 146.1: +0.11 % / 0.45 %; V = 145: −0.52 % / 0.95 %. CR3 V = 3 330.6: +0.02 % / 0.23 %;
   V = 2 350: −26.7 % / 29.4 %. CR4 V = 8 656.5: +0.06 % / 0.29 %; V = 8 650: −0.00 % / 0.25 %.

Cause: the sheet volumes are rounded room figures (CR4's 8 650 against the model's 8 656.5 m³ shows
the same rounding); the fitted α, the areas and S all belong to the model volume, which the fit
reproduces to ≤ 0.45 % in CR2 (a 145 m³ fit would be off by up to 0.95 %). CR3's sheet volume
excludes the attic that the model (and the fit) include; the attic coupling stays a known reduction
limit (§4). The model volume is therefore not wrong: no /fix-plan, and AX26's rule is unchanged (one
generic rule, NFR-8). With A fixed, the model volume raises the CR2 predicted T by +0.76 %
(146.1/145) and the CR3 one by +41.7 % (3 330.6/2 350) against the sheet volumes; the report prints
these beside the AQ9 lines. The model also omits a few small objects (cable ducts, a pipe, a fire
extinguisher in CR2; `CRx_ModelSimplifications.pdf`), whose volume is far below the 1.1 m³ gap.

**CR4 extraction (pre-committed 2026-11-06, before any simulated-vs-measured number; decider decision on
CR4 handling, phase-05e scope (b), vetoable by Maisara).** CR4 stays selected. It enters the comparison only if
the §2 acceptance test passes (every documented material area of `_descr/mat_CR4.txt` reproduces and every loop
vertex lies on its face's plane, as for CR2 and CR3);
a parse whose areas do not reproduce counts as "not extracted" and is never tuned against. Until it enters, the
results are labelled "provisional, two-room (CR2, CR3; uniform α: CR2, uneven α: CR3 only); CR4 pending". CR4's extraction is the work of phase-05f (created 2026-11-06 at Maisara's request); if it is not accepted
within phase-05f's two-session stop rule, CR4 is recorded "pending extraction (reader)", not dropped; no other
reason, and no comparison result, removes CR4 from the selection. Maisara's acceptance of the two-room label
(phase-05e scope (b), reversal) keeps CR4 selected and pending; it goes through /fix-plan as a phase-05.md change.

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
2. **Dimensions (AX26; decision D-A, 2026-11-06, vetoable by Maisara; replaces the Phase 05
   S-preserving rule, which gave CR2 13.9 × 3.6 m and an invalid 136 m CR3 box):** keep V and
   h = V / A_floor, where A_floor is the total area assigned to the floor face (BRAS documents no
   dimensions, F4). The plan ratio ρ ≥ 1 is the side ratio of the minimum-area oriented bounding
   rectangle of the floor-assigned faces' horizontal projection (rotated frame of rule 1; computed
   on their convex hull, stored by the extractor); a = √(A_floor·ρ) along x (AQ1),
   b = √(A_floor/ρ), so a·b = A_floor. S is not matched: §5 reports S(box) against the documented
   S, the mean free path 4V/S of both, and per band the box's Eyring T against Eyring on the
   documented V, S, A. A room whose box has a side outside AX6 is not written and is reported.
3. **Absorption** per face and octave band: α_face = Σ Sᵢαᵢ / S_face over the assigned surfaces,
   S_face the box face area, clamped to ≤ 1 (every clamp and the absorption area it loses are
   reported; AQ3's lower limit 0.01 is applied the same way and reported). This conserves the
   absorption area A per face and in total; S is not matched (rule 2), so ᾱ and the Eyring T shift
   at second order (reported in §5).
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

## 4b. B11 (B) coverage (phase-05e session 2)

**B11 not validated against measurement for uneven-α / low-s rooms** (phase-05.md scope 6, F2). In the
CR2 + CR3 set (provisional two-room; CR4 pending in phase-05f) no room combines uneven α with low s:
CR2 has near-uniform α (absorption contrast ≈ 0.76–1.03) and low s (broadband 0.06–0.21); CR3 has one
strong, high-s absorber (contrast ≈ 0.54–0.59, largest single-face share ≈ 0.33–0.36). No minimum room
count applies (B11 (B)); the B11 (B) result in `report-phase05.md` §6b holds only for these two rooms.

## 5. Reduction results

(Generated by `tools/validation/make_bras_scenes.py` from `tools/validation/data/bras_geometry.json`; do not edit by hand. Areas in m², octave α at 500 Hz / 1 kHz / 2 kHz.)

### CR2

Model: V = 146.1 m³, S = 202.53 m² (documented); materials reproduced by the reader: ceiling 51.62 (doc 51.62), concrete 56.94 (doc 56.94), floor 49.29 (doc 49.29), plaster 34.93 (doc 34.93), windows 9.75 (doc 9.75); unpainted faces (not a BRAS material, ignored) 0.62 m²; rotation θ = -0.09°; floor area (floor-assigned) A_floor = 50.48 m².

Box (AX26): W × D × H = 8.371 × 6.031 × 2.894 m (h = V/A_floor, W·D = A_floor); plan ratio ρ = 1.388 from the minimum-area oriented bounding rectangle of the floor faces (8.59 × 6.19 m, long side at 90.1° in the rotated model frame); model long side along y swapped to x: yes.

S not matched (AX26): S(box) = 184.32 m² vs documented 202.53 m² (-8.99 %); mean free path 4V/S = 3.171 m (box) vs 2.885 m (documented). Eyring T60 on the box vs Eyring on the documented V, S, A (AX4 air, initial α), 125 Hz … 8 kHz: 125 Hz 2.481 vs 2.487 s (-0.23 %), 250 Hz 1.468 vs 1.473 s (-0.39 %), 500 Hz 1.540 vs 1.546 s (-0.36 %), 1000 Hz 1.671 vs 1.676 s (-0.32 %), 2000 Hz 1.536 vs 1.540 s (-0.32 %), 4000 Hz 1.168 vs 1.171 s (-0.32 %), 8000 Hz 0.704 vs 0.705 s (-0.28 %).

| face | box area | assigned area | assigned materials | α initial | α fitted | s (AX17) | s 500 / 1k / 2k |
|---|---|---|---|---|---|---|---|
| xMin | 17.5 | 23.9 | plaster 18.1, concrete 4.0, ceiling 1.8 | 0.077 / 0.075 / 0.079 | 0.060 / 0.064 / 0.068 | 0.081 | 0.058 / 0.076 / 0.108 |
| xMax | 17.5 | 23.9 | concrete 12.4, windows 9.7, ceiling 1.8 | 0.090 / 0.093 / 0.123 | 0.069 / 0.080 / 0.105 | 0.071 | 0.057 / 0.067 / 0.090 |
| yMin | 24.2 | 26.9 | concrete 26.6, ceiling 0.2, plaster 0.0 | 0.077 / 0.075 / 0.076 | 0.060 / 0.064 / 0.065 | 0.066 | 0.051 / 0.062 / 0.087 |
| yMax | 24.2 | 26.9 | plaster 16.7, concrete 10.0, ceiling 0.1 | 0.065 / 0.064 / 0.067 | 0.051 / 0.055 / 0.057 | 0.069 | 0.051 / 0.065 / 0.092 |
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

Box (AX26): W × D × H = 38.292 × 19.778 × 4.398 m (h = V/A_floor, W·D = A_floor); plan ratio ρ = 1.936 from the minimum-area oriented bounding rectangle of the floor faces (29.05 × 15.00 m, long side at 0.0° in the rotated model frame); model long side along y swapped to x: no.

S not matched (AX26): S(box) = 2025.44 m² vs documented 2763.0 m² (-26.69 %); mean free path 4V/S = 6.578 m (box) vs 4.822 m (documented). Eyring T60 on the box vs Eyring on the documented V, S, A (AX4 air, initial α), 125 Hz … 8 kHz: 125 Hz 2.075 vs 2.111 s (-1.72 %), 250 Hz 2.371 vs 2.406 s (-1.46 %), 500 Hz 1.497 vs 1.532 s (-2.31 %), 1000 Hz 1.174 vs 1.209 s (-2.92 %), 2000 Hz 0.919 vs 0.953 s (-3.60 %), 4000 Hz 0.881 vs 0.909 s (-3.01 %), 8000 Hz 0.583 vs 0.599 s (-2.67 %).

| face | box area | assigned area | assigned materials | α initial | α fitted | s (AX17) | s 500 / 1k / 2k |
|---|---|---|---|---|---|---|---|
| xMin | 87.0 | 288.0 | stagePanels 157.0, plaster 68.0, structuredPlaster 44.9, floor 17.5, seating 0.6 | 0.289 / 0.354 / 0.409 | 0.341 / 0.320 / 0.293 | 0.079 | 0.064 / 0.077 / 0.096 |
| xMax | 87.0 | 272.3 | stagePanels 113.7, plaster 84.1, structuredPlaster 50.3, floor 16.3, windows 4.2, seating 3.8 | 0.296 / 0.360 / 0.421 | 0.349 / 0.325 / 0.302 | 0.089 | 0.070 / 0.086 / 0.111 |
| yMin | 168.4 | 338.3 | plaster 134.1, structuredPlaster 121.0, stagePanels 51.7, windows 21.2, floor 6.6, seating 3.7 | 0.215 / 0.263 / 0.308 | 0.253 / 0.238 / 0.221 | 0.114 | 0.083 / 0.110 / 0.149 |
| yMax | 168.4 | 338.7 | plaster 143.9, structuredPlaster 122.3, stagePanels 51.7, floor 15.9, seating 4.8 | 0.220 / 0.269 / 0.310 | 0.259 / 0.243 / 0.222 | 0.117 | 0.085 / 0.113 / 0.154 |
| floor | 757.3 | 757.3 | structuredPlaster 299.1, floor 273.0, seating 166.1, stagePanels 17.3, plaster 1.9 | 0.143 / 0.173 / 0.228 | 0.169 / 0.156 / 0.163 | 0.207 | 0.151 / 0.207 / 0.262 |
| ceiling | 757.3 | 768.4 | structuredPlaster 534.3, ceiling 168.5, stagePanels 34.1, plaster 18.3, floor 13.2 | 0.117 / 0.152 / 0.178 | 0.138 / 0.138 / 0.128 | 0.170 | 0.117 / 0.164 / 0.230 |

Clamps (AQ3 range [0.01, 1]): none.
Total absorption area A (box vs documented surfaces) at 500 Hz / 1 kHz / 2 kHz: 321.3 vs 321.3 / 397.5 vs 397.5 / 484.2 vs 484.2 m².

| pair | r real (m) | r box (m) | h source / receiver (m) | floor face found under the midpoint | moved (AX6) |
|---|---|---|---|---|---|
| LS1_MP1 | 10.126 | 10.126 | 2.38 / 1.23 | yes | – |
| LS1_MP2 | 4.573 | 4.573 | 2.38 / 1.23 | yes | – |
| LS1_MP3 | 11.312 | 11.312 | 2.38 / 1.23 | yes | – |
| LS1_MP4 | 9.078 | 9.078 | 2.38 / 1.23 | yes | – |
| LS1_MP5 | 15.692 | 15.692 | 2.38 / 1.23 | yes | – |
| LS2_MP1 | 11.396 | 11.396 | 2.38 / 1.23 | yes | – |
| LS2_MP2 | 7.811 | 7.811 | 1.38 / 0.23 | yes | – |
| LS2_MP3 | 13.335 | 13.335 | 2.38 / 1.23 | yes | – |
| LS2_MP4 | 9.259 | 9.259 | 2.38 / 1.23 | yes | – |
| LS2_MP5 | 16.135 | 16.135 | 2.38 / 1.23 | yes | – |

### Classification (Raise with Maisara, item 1)

Absorption unevenness = largest single-face share of the total absorption area and the ratio ᾱ(floor+ceiling)/ᾱ(walls) at 1 kHz; scattering = the broadband s (AX17) of the faces that hold most of the absorption. No threshold is applied (phase-05 scope 6); the statement below reads the numbers.

| room | largest face share of A (1 kHz) | ᾱ(floor+ceiling)/ᾱ(walls) (1 kHz) | s of that face | area-weighted mean s |
|---|---|---|---|---|
| CR2 | 0.30 (floor) | 0.87 | 0.056 | 0.105 |
| CR3 | 0.33 (floor) | 0.55 | 0.207 | 0.167 |

Per material (documented areas from `_descr/mat_CRx.txt`, initial α and s, octave values by AX25; d_char as documented), sorted by share of the total absorption area at 1 kHz:

| room | material | area (m², % of S) | α 500 / 1k / 2k | share of A (1 kHz) | s 500 / 1k / 2k | s (AX17) | d_char (m) |
|---|---|---|---|---|---|---|---|
| CR2 | concrete | 56.9 (28.1 %) | 0.07 / 0.07 / 0.07 | 0.30 | 0.05 / 0.06 / 0.09 | 0.07 | 0.005 |
| CR2 | floor | 49.3 (24.3 %) | 0.09 / 0.08 / 0.07 | 0.29 | 0.05 / 0.05 / 0.07 | 0.06 | 0.003 |
| CR2 | ceiling | 51.6 (25.5 %) | 0.07 / 0.06 / 0.06 | 0.22 | 0.15 / 0.21 / 0.30 | 0.22 | 0.06 |
| CR2 | plaster | 34.9 (17.2 %) | 0.05 / 0.05 / 0.06 | 0.14 | 0.05 / 0.07 / 0.09 | 0.07 | 0.006 |
| CR2 | windows | 9.8 (4.8 %) | 0.06 / 0.07 / 0.12 | 0.05 | 0.05 / 0.05 / 0.05 | 0.05 | 0.002 |
| CR3 | structuredPlaster | 1171.9 (42.4 %) | 0.13 / 0.17 / 0.19 | 0.49 | 0.14 / 0.19 / 0.27 | 0.20 | 0.05 |
| CR3 | seating | 178.9 (6.5 %) | 0.32 / 0.38 / 0.58 | 0.17 | 0.43 / 0.60 / 0.87 | 0.64 | 0.5 |
| CR3 | plaster | 450.3 (16.3 %) | 0.11 / 0.12 / 0.14 | 0.14 | 0.05 / 0.07 / 0.09 | 0.07 | 0.006 |
| CR3 | stagePanels | 425.6 (15.4 %) | 0.07 / 0.09 / 0.10 | 0.09 | 0.05 / 0.05 / 0.05 | 0.05 | 0.001 |
| CR3 | floor | 342.5 (12.4 %) | 0.06 / 0.06 / 0.06 | 0.05 | 0.05 / 0.07 / 0.10 | 0.08 | 0.007 |
| CR3 | ceiling | 168.5 (6.1 %) | 0.09 / 0.12 / 0.16 | 0.05 | 0.09 / 0.12 / 0.17 | 0.13 | 0.02 |
| CR3 | windows | 25.4 (0.9 %) | 0.06 / 0.07 / 0.12 | 0.00 | 0.05 / 0.05 / 0.05 | 0.05 | 0.002 |
