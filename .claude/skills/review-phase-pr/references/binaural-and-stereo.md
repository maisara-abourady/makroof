# Binaural and stereo rendering (K7)

Reference file of the `review-phase-pr` skill. Scope: SOFA/AES69 conventions, HRTF datasets and their licences (SADIE II, MIT KEMAR), ITD/ILD reference values, HRIR interpolation, diffuse-field equalisation, interaural coherence and decorrelation mixing, BRIR assembly and coordinate mapping, virtual ORTF stereo, loudness matching (BS.1770). Phases 08, 09, 11, 12.

How to use it: read the "Reviewer's checklist" section first and apply the questions the diff makes
relevant; use the earlier sections to settle a disagreement with the author or to re-derive a number.
Every fact carries its source URL and the date it was verified (researched live on 2026-11-04).
Facts marked "(unverified, from memory)" must be verified before they are cited in a review; when
you verify one, fix it here. See `knowledge-inventory.md` for which facts go stale and how to
re-check them.

## Contents

- 1. SOFA / AES69
  - 1.1 Editions and versions
  - 1.2 SimpleFreeFieldHRIR (version 1.2 table, verified live)
  - 1.3 Coordinate system
  - 1.4 Conversion pitfalls (each is a reviewer check in §10)
  - 1.5 Python tools (versions and licences, verified on PyPI 2026-11-04)
- 2. HRTF datasets and licences
  - 2.1 SADIE II (University of York) — verdict: **Apache License 2.0, commercial redistribution of derived data permitted with attribution**
  - 2.2 MIT KEMAR (Gardner & Martin 1994) — "provided without any usage restrictions", citation requested
  - 2.3 TH Köln KU100 (Bernschütz 2013) — CC BY-SA 3.0 per paper; Zenodo metadata says CC BY 3.0 (conflict)
  - 2.4 CIPIC (UC Davis, 2001) — permissive, including commercial
  - 2.5 Other sets worth knowing
- 3. Binaural cue reference values
- 4. HRIR interpolation
- 5. Diffuse-field equalisation (DFE)
- 6. Interaural coherence of diffuse fields
- 7. BRIR assembly from image sources
- 8. Virtual ORTF stereo
- 9. ITU-R BS.1770
- 10. Reviewer's checklist (diff questions and the bug each catches)
  - HRTF conversion (`tools/hrtf/convert_sofa.py`, `generic-v1.bin`)
  - Lookup / interpolation (`src/sim/hrtf/HrtfSet`)
  - BRIR assembly (`BrirBuilder`, `ListenerFrame`)
  - Coherence mixing (tail)
  - Virtual ORTF (`VirtualMicPair`)
- 11. Source list (all accessed 2026-11-04 unless stated)

---

Research notes for a code-review skill covering Phase 08 (binaural output through a generic HRTF)
and Phase 09 (stereo-speaker output through a virtual ORTF pair) of the Spatial Scene VST
(`docs/phases/phase-08.md`, `docs/phases/phase-09.md`). All web facts were checked on
**2026-11-04** unless marked "(unverified, from memory)". Where a number was computed here
from a stated formula it is marked "(computed)".

Plugin frame used throughout (CLAUDE.md, AQ1): **x right, y forward, z up**, radians internally,
degrees in JSON/UI. Phase 08 defines **+90° azimuth = left** (listener's left ear leads).

---

## 1. SOFA / AES69

### 1.1 Editions and versions

- SOFA 1.0 = AES69-2015. SOFA 2.0 = AES69-2020. **SOFA 2.1 = AES69-2022**, the latest edition
  found in force. Sources: sofaconventions.org main page
  (https://www.sofaconventions.org/mediawiki/index.php/SOFA_(Spatially_Oriented_Format_for_Acoustics),
  2026-11-04) and the Forum Acusticum 2023 paper "Recent advances in the Spatially Oriented
  Format for Acoustics" (https://dael.euracoustics.org/confs/fa2023/data/articles/000729.pdf,
  2026-11-04: "AES69-2022 (as known as SOFA 2.1)", "SOFA 2.1 covers 15 standardized conventions").
- The SimpleFreeFieldHRIR wiki page lists convention **version 1.2** and says it "represents the
  standardized convention set from AES69-2025" (adds optional `Normalization`); version 1.0 is
  AES69-2015 (https://www.sofaconventions.org/mediawiki/index.php/SimpleFreeFieldHRIR,
  2026-11-04). No AES69-2025 document was found anywhere else (sofaconventions news through
  March 2025, pyfar/sofa_conventions repo still "AES69-2022", conventions version 2.1:
  https://github.com/pyfar/sofa_conventions, 2026-11-04). Treat 1.2 as a draft/upcoming
  revision; **expect files in the wild to carry `GLOBAL:Version = 2.1` (or 1.0/2.0) and
  `SOFAConventionsVersion` 1.0 or 1.1**. A converter must not hard-fail on any of these.
- Reference paper: Majdak, Zotter, Brinkmann, De Muynke, Mihocic, Noisternig, "Spatially
  Oriented Format for Acoustics 2.1: Introduction and Recent Advances", JAES 70(7/8) 565–584,
  July 2022, DOI 10.17743/jaes.2022.0026 (https://aes.org/publications/elibrary/elibrary-page/?id=21824,
  2026-11-04).

### 1.2 SimpleFreeFieldHRIR (version 1.2 table, verified live)

Source: https://www.sofaconventions.org/mediawiki/index.php/SimpleFreeFieldHRIR (2026-11-04).

- Global attributes (mandatory, read-only "rm"): `Conventions = SOFA`, `Version = 2.1`,
  `SOFAConventions = SimpleFreeFieldHRIR`, `SOFAConventionsVersion = 1.2`, `DataType = FIR`.
  Mandatory: `RoomType = free field`, `License` (default string: "No license provided, ask the
  author for permission"), `AuthorContact`, `Organization`, `DatabaseName`, `ListenerShortName`,
  `DateCreated`, `DateModified`, `Title`. Optional: `ApplicationName`, `Comment`, `History`,
  `Origin`, `References`.
- Variables (default, dims, type/units):
  - `ListenerPosition` [0 0 0], dims IC or MC, cartesian, metre.
  - `ListenerView` [1 0 0], `ListenerUp` [0 0 1], dims IC or MC, cartesian.
  - `ReceiverPosition` **[0 0.09 0; 0 −0.09 0]**, dims RCI, cartesian, metre. Receiver 0 at
    **+y = left** by default. It is a default, not a rule: read `ReceiverPosition` and assign
    left/right by the sign of y.
  - `SourcePosition` [0 0 1], dims IC or MC, **type spherical, units "degree, degree, metre"**
    (azimuth, elevation, distance). "The source position is assumed to vary around the listener."
  - `EmitterPosition` [0 0 0], dims eCI/eCM ("Source consists of a single Emitter only").
  - `Data.IR` dims **mrn** = [M measurements, R receivers, N samples].
  - `Data.SamplingRate` default 48000, dims I or M, **units hertz**: "Sampling rate of the samples
    in Data.IR and Data.Delay".
  - `Data.Delay` default [0 0], dims **IR or MR**: "Additional delay of each IR (in samples, with
    the time interval as described by SamplingRate)". The SOFA specifications page adds "Delay is
    mandatory (set to 0 if not used)" and "always in samples, i.e. units of N"
    (https://www.sofaconventions.org/mediawiki/index.php/SOFA_specifications, 2026-11-04).
  - `Normalization` (optional, new in 1.2), dims I.
- Dimension letters (AES69): M = number of measurements, R = receivers, E = emitters,
  N = samples per IR, I = 1 (scalar), C = 3 (coordinate triplet). The FA2023 paper confirms
  "the dimensions I and C" are the predefined scalar/coordinate dims; the exact letter list is
  (unverified, from memory) but consistent with the MathWorks example M = 2114, R = 2, E = 1,
  N = 256 (https://www.mathworks.com/help/audio/ug/read-analyze-and-process-sofa-files.html,
  2026-11-04).

### 1.3 Coordinate system

- Cartesian: **x = front (view direction), y = left, z = up**, right-handed. Verified via
  libmysofa README: "the X axis vector (1 0 0) is the listening direction", "The Y axis (0 1 0)
  is the left side of the listener", Z up; `mysofa_s2c` takes azimuth "counted counterclockwise
  from X", elevation "up from the X-Y plane", distance (https://github.com/hoene/libmysofa,
  2026-11-04). The defaults `ListenerView = [1 0 0]`, `ListenerUp = [0 0 1]` and
  `ReceiverPosition` left ear at +y confirm the same.
- Spherical: **azimuth counter-clockwise from +x (0° front, 90° left, 180° back, 270°/−90°
  right); elevation 0° horizontal, +90° up; distance in metres.** pyfar's `spherical_elevation`
  system uses the same definition (azimuth ccw in x-y plane, 0 on +x, π/2 on +y; elevation 0 on
  +x, π/2 on +z), radians internally
  (https://pyfar.readthedocs.io/en/stable/classes/pyfar.coordinates.html, 2026-11-04).
- SADIE II labels its measurements the same way: "Azimuth is anticlockwise (0° is front).
  Elevation is positive above and negative below the horizontal plane"
  (https://www.york.ac.uk/sadie-project/database.html, 2026-11-04).
- **Mapping to the plugin frame** (x right, y forward, z up; computed):
  `sofa_x = plugin_y`, `sofa_y = −plugin_x`, `sofa_z = plugin_z`. Head-relative azimuth in the
  plugin frame with "+90° = left": `az = atan2(−x_rel, y_rel)`, `el = asin(z_rel / r)`. The
  classic sign bug is `atan2(x_rel, y_rel)` (clockwise, +90° = right): the ITD/ILD tests at ±90°
  pass only in magnitude, and the ears are swapped.

### 1.4 Conversion pitfalls (each is a reviewer check in §10)

- Ignoring `Data.Delay`. Dims may be [I R] (one pair for all measurements) or [M R]
  (per-measurement). Onset = HRIR onset + `Data.Delay[m, r]`. A file that stored onset-removed
  HRIRs with the delay in `Data.Delay` loses its entire ITD if the field is dropped.
- Assuming receiver 0 is left. Read `ReceiverPosition[:,1]` (y); left = positive y.
- Assuming units. `SourcePosition_Units` must be parsed ("degree, degree, metre" vs "metre"
  cartesian). Some files use `SourcePosition_Type = cartesian`.
- Assuming the SOFA azimuth sense in a non-SOFA source: raw MIT KEMAR files use **clockwise**
  azimuth (90° = right of KEMAR, §2.2); CIPIC uses **interaural-polar** coordinates (§2.4).
- Dimension order: NetCDF stores [M, R, N]; MATLAB `ncread` returns the reversed N×R×M
  (MathWorks page, 2026-11-04). netCDF4-python/sofar/h5py give [M, R, N].
- Sampling-rate attribute may be per-measurement (dims M); check it is constant.
- `GLOBAL:License` must be read and recorded; default text means "no licence".
- Partial-sphere grids (human subjects usually lack the bottom cap): any "average over all
  directions" (DFE, interaural coherence target) must use **area/quadrature weights** and must
  document the missing cap; uniform per-measurement weights over-weight dense rings/poles.
- 180° wrap: azimuth stored in [0, 360) vs (−180, 180]; triangulation and nearest-neighbour
  searches must be done on unit vectors, never on (az, el) pairs.

### 1.5 Python tools (versions and licences, verified on PyPI 2026-11-04)

| Package | Latest | Date | Licence | Python | Notes |
|---|---|---|---|---|---|
| sofar | 1.3.0 | 2026-08-27 | MIT | ≥3.8 | "complete definition of the AES69 standard" from pyfar/sofa_conventions; full verification against AES69; upgrades outdated conventions (https://pypi.org/project/sofar/, https://sofar.readthedocs.io/en/stable/readme.html) |
| pyfar | 0.8.1 | 2026-08-14 | MIT | ≥3.11 | `pyfar.io.read_sofa`, Coordinates class (https://pypi.org/project/pyfar/) |
| netCDF4 | 1.7.4 | 2026-01-05 | MIT | — | sofar's backend (dependency: unverified, from memory) (https://github.com/Unidata/netcdf4-python/releases) |
| h5py | 3.16.0 | 2026-03-06 | BSD-3-Clause | ≥3.10 | SOFA files are NetCDF-4/HDF5; h5py can read `Data.IR` directly (https://pypi.org/project/h5py/) |
| pyloudnorm | 0.2.0 | 2026-01-04 | MIT | — | "Implementation of ITU-R BS.1770-4"; 400 ms block default (https://pypi.org/project/pyloudnorm/) |
| libmysofa (C) | — | — | BSD-3-Clause | — | reference C reader, k-d tree lookup (https://github.com/hoene/libmysofa) |
| pyfar/sofa_conventions (data) | conv. 2.1 | — | **EUPL-1.2** | — | if the converter vendors its JSON/CSV, record EUPL in THIRD_PARTY.md (https://github.com/pyfar/sofa_conventions) |

---

## 2. HRTF datasets and licences

### 2.1 SADIE II (University of York) — verdict: **Apache License 2.0, commercial redistribution of derived data permitted with attribution**

Official page https://www.york.ac.uk/sadie-project/database.html (2026-11-04):

- Contents: 20 subjects. **D1 = Neumann KU100, D2 = GRAS KEMAR**, H3–H20 = 18 humans.
  Points: D1/D2 **8,802** directions; H3–H8 2,818; H9–H20 2,114. HRIRs "measured on a regular
  latitude-longitude grid at 15° elevation with variable azimuth resolution" plus ≥12 Ambisonic
  loudspeaker configurations (octahedron, cube, bi-rectangle, icosahedron, 7-design, 26- and
  50-point Lebedev, pentakis icosidodecahedron). Loudspeaker Genelec 8010 at **1.2 m**. BRIRs on a
  50-point Lebedev grid (Genelec 8030/8040 at 1.5 m). DT990 headphone IRs/EQ. 3D head scans, ITD/ILD
  plots.
- Formats: WAV 44.1 kHz/16-bit, 48 kHz/24-bit, 96 kHz/24-bit, and **AES69 SOFA** (the page does
  not state the SOFA sample rate: read `Data.SamplingRate` from the file; expected 48 kHz
  (unverified, from memory)).
- Latest release **v2-2, 2024-06-18**, Zenodo DOI 10.5281/zenodo.12092466; per-subject files
  `D1_HRIR_SOFA.zip` (38.2 MB), `D2_HRIR_SOFA.zip` (38.0 MB), `Database-Master_V2-2.zip` (1.3 GB),
  `LICENSE.txt` (11.6 kB) (https://zenodo.org/records/12092466, 2026-11-04). Version history:
  1.3 (2020-01-10) "Updated SOFA licence metadata", 1.4 (2020-05-13) "Updated SOFA licence and
  licence metadata" → check `GLOBAL:License` in the downloaded SOFA file says Apache 2.0.
- Licence text on the page (verbatim fragments): "Copyright 2018, University of York."
  "Licensed under the Apache License, Version 2.0 (the "License"); You may not use this database
  except in compliance with the License." "...distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
  OR CONDITIONS OF ANY KIND". Plus: **"The original dataset must be referenced whenever used in
  original or modified form."** Academic citation: Armstrong, Thresh, Murphy, Kearney, "A
  Perceptual Evaluation of Individual and Non-Individual HRTFs: A Case Study of the SADIE II
  Database", Applied Sciences 8(11) 2029, 2018, DOI 10.3390/app8112029.
- Zenodo record metadata: "Apache License 2.0". `LICENSE.txt` on Zenodo is the **unmodified
  standard Apache 2.0 text** (header "Apache License, Version 2.0, January 2004", standard
  appendix with "[yyyy] [name of copyright owner]" placeholders, no non-commercial clause)
  (https://zenodo.org/records/12092466/files/LICENSE.txt?download=1, 2026-11-04).
- Conflicting wording exists on a **different** York page: the Ambisonic decoder page says "This
  database is distributed free of charge under a non-commercial LICENSE" — it is the decoder
  configuration page (v1.0, 2018-06-20), not the HRTF database
  (https://www.york.ac.uk/sadie-project/ambidec.html, 2026-11-04). The deprecated original
  SADIE (I) database page (database_old.html) may carry other terms; do not use SADIE I.
- What Apache 2.0 requires of the plugin (standard §4, unverified-from-memory paraphrase of the
  licence text): ship a copy of the licence, retain copyright/attribution notices, state that
  files were modified (resampled, truncated, DFE'd, re-gridded), and keep any NOTICE. Commercial
  use, modification and redistribution of derivatives (e.g. `generic-v1.bin`) are permitted. Put
  the York copyright line, the Apache 2.0 text, the "original dataset must be referenced" sentence
  and the DOI into `resources/hrtf/LICENSE-generic-v1.txt` and `docs/THIRD_PARTY.md`.
- Contact for licence doubts given on the page: gavin.kearney@york.ac.uk (from a search
  summary of the York page, 2026-11-04).

### 2.2 MIT KEMAR (Gardner & Martin 1994) — "provided without any usage restrictions", citation requested

Primary source: Gardner & Martin, "HRTF Measurements of a KEMAR Dummy-Head Microphone", MIT Media
Lab Perceptual Computing TR-280, 1994. The MIT page https://sound.media.mit.edu/resources/KEMAR.html
returned HTTP 503 on 2026-11-04 (three attempts); the report PDF was read from a mirror
(https://www.linux.bucknell.edu/~kozick/elec32007/hrtfdoc.pdf, 2026-11-04):

- §7 "Usage restrictions", verbatim: **"This HRTF data is Copyright 1994 by the MIT Media Lab.
  It is provided without any usage restrictions. We request that you cite the authors when using
  this data for research or commercial applications."** The openal-soft converter definition
  paraphrases the web page: "copyrighted 1994 by MIT Media Laboratory, and provided free of charge
  with no restrictions on use so long as the authors (above) are cited"
  (https://raw.githubusercontent.com/kcat/openal-soft/master/utils/MIT_KEMAR_sofa.def, 2026-11-04).
- Data: KEMAR DB-4004 with **left pinna DB-061 (normal) and right pinna DB-065 (large)** — the
  "full" set is **asymmetric by construction**; 44.1 kHz, 16-bit signed big-endian (68000 byte
  order); Optimus Pro 7 loudspeaker at **1.4 m**; 16383-point raw responses, first 200 samples
  discarded, next **512 samples** kept (≈230 samples of air+system delay precede the head
  response, so ~30 samples of pre-delay remain in the 512); **710 positions**; elevations **−40°
  to +90° in 10° steps**; azimuth increments per elevation: −40°: 56 pts/6.43°, −30°: 60/6°,
  −20°..+20°: 72/5°, 30°: 60/6°, 40°: 56/6.43°, 50°: 45/8°, 60°: 36/10°, 70°: 24/15°, 80°:
  12/30°, 90°: 1.
- **Azimuth convention of the raw files: clockwise.** "elevation 0 azimuth 0 is directly in
  front of the KEMAR, elevation 90 is directly above the KEMAR, elevation 0 azimuth 90 is directly
  to the right of the KEMAR". Files `full/elevEE/LEEeAAAa.dat` (left ear) and `R...` (right);
  example for a source 45° to the left of the head: `L0e045a.dat`?? — no: the report says use
  `L0e045a.dat` for the left ear **and `L0e315a.dat` as the right ear** of a source at 45° (using
  left-ear symmetry), confirming 45° is to the right in file coordinates.
- **"Compact" set**: `compact.tar.Z`, `HEEeAAAa.dat`, stereo-interleaved **128-point**
  responses, **derived from the left ear only** (symmetrised: left = `L0e090a`, right = `L0e270a`
  for a source to the right), **equalised with the minimum-phase inverse of the Optimus Pro 7**,
  cropped to 128 samples starting at sample index 26. So compact = 44.1 kHz, 128 taps,
  speaker-equalised, mirror-symmetric, normal pinna.
- SOFA conversions: sofacoustics.org hosts `mit_kemar_normal_pinna.sofa` and
  `mit_kemar_large_pinna.sofa` (1.1 MB each, 2020-03-24)
  (https://www.sofacoustics.org/data/database/mit/, 2026-11-04); openal-soft's def notes the SOFA
  file is 44.1 kHz, 512 points, 1.4 m, "SOFA azimuths run counter-clockwise" (so the conversion
  re-mapped the sign), 19 elevation rings. The Two!Ears mirror names its files
  `MIT_KEMAR_anechoic_1.7m_*.sofa` while describing 1.4 m — a known inconsistency
  (http://docs.twoears.eu/en/latest/database/impulse-responses/hrirs/, 2026-11-04).
- Citation: B. Gardner and K. Martin, "HRTF measurements of a KEMAR dummy-head microphone",
  MIT Media Lab Perceptual Computing Technical Report #280, 1994 (also JASA 97(6) 3907, 1995,
  abstract — unverified, from memory).

### 2.3 TH Köln KU100 (Bernschütz 2013) — CC BY-SA 3.0 per paper; Zenodo metadata says CC BY 3.0 (conflict)

- Zenodo record 10.5281/zenodo.3928297 (v1, 2020-07-02): "Spherical Far-Field HRIR Compilation
  of the Neumann KU100", licence shown **CC BY 3.0 Unported**; files `HRIR_FULL2DEG.sofa`
  (19.7 MB), `HRIR_L2702.sofa`, `HRIR_L2354.sofa`, `HRIR_CIRC360.sofa`, `HRIR_CIRC360RM.sofa`,
  plus headphone compensation filters for ~20 headphones (https://zenodo.org/records/3928297,
  2026-11-04). Grids: full-sphere 2° Gauss (16,020 points), Lebedev 2354 and 2702, horizontal
  circle 1°; Genelec 8260A at 3.25 m; VariSphear (Two!Ears page, 2026-11-04). Sample rate/length
  not stated on the pages (44.1 kHz, 128 taps: unverified, from memory).
- The DAGA 2013 paper states **CC BY-SA 3.0** (search summary of
  http://audiogroup.web.th-koeln.de/PUBLIKATIONEN/Bernschuetz_DAGA2013.pdf, 2026-11-04); Two!Ears
  lists CC BY-SA 3.0. ShareAlike on a derived data file embedded in a closed-source commercial
  plugin is a legal grey zone (the adapted database would itself have to be CC BY-SA). **Do not
  pick it over SADIE II without legal review.** Related near-field KU100 set (Arend et al.,
  10.5281/zenodo.4297951): Zenodo says CC BY 4.0, paper says CC BY-SA 4.0 — same conflict.

### 2.4 CIPIC (UC Davis, 2001) — permissive, including commercial

- `read_me.txt` (GitHub mirror of Release 1.1, 2001-10-21): "Copyright (c) 2001 The Regents of
  the University of California. All Rights Reserved"; **"The Regents of the University of
  California hereby grant users permission to reproduce and/or use materials available therein
  for any purpose- educational, research or commercial."** "each reproduction of any part of the
  materials must include the copyright notice"; published research "should be acknowledged"
  (https://raw.githubusercontent.com/amini-allight/cipic-hrtf-database/master/read_me.txt,
  2026-11-04). The official UC Davis page is HTTP 410 Gone (2026-11-04).
- Contents: 45 subjects incl. **KEMAR large pinnae (subject_021) and small pinnae
  (subject_165)**, 1250 directions = 25 azimuths × 50 elevations in **interaural-polar**
  coordinates, 44.1 kHz, 200 samples (the 1250/44.1 kHz/200 figures: Algazi et al. WASPAA 2001,
  unverified from memory; subjects/KEMAR IDs verified from read_me). Interaural-polar → the
  "azimuth" is a lateral angle in [−80°, 80°] and "elevation" wraps −45°..230.6°: converting it
  with a vertical-polar formula is a classic bug.

### 2.5 Other sets worth knowing

- Aachen "High-Resolution HRTF Data Set and 3D-Scan of KEMAR" (Braren & Fels, RWTH, 2020;
  ITD via onset detection, 3 kHz low-pass, −10 dB threshold) — licence not checked (search result
  only, 2026-11-04).
- Groningen "Horizontal-plane HRTFs of KEMAR interpolated at 0.5°" (Zenodo 3250072) — licence
  not checked.
- SONICOM ecosystem lists SADIE II with "Apache License 2.0, rightsholder University of York"
  (https://ecosystem.sonicom.eu/databases/92, via search 2026-11-04).

---

## 3. Binaural cue reference values

- **Woodworth/spherical head**: ITD(θ) = (a/c)(θ + sin θ) for a source in the horizontal plane
  (θ in radians from the median plane), a ≈ 8.75 cm, c = 343 m/s. At 90°: **656 µs** (computed;
  a source quoting "654 µs" for a = 87.5 mm confirms). The low-frequency (kа ≪ 1) formula
  ITD = (3a/c) sin θ gives **765 µs** at 90° (computed; Frontiers 2014 article quotes 763 µs
  with v = 34,300 cm/s, https://www.frontiersin.org/articles/10.3389/fnins.2014.00034/full via
  search 2026-11-04). The two formulas differ by ~110 µs at 90°: an ITD-extraction method that
  looks at low-frequency phase will read higher than one that looks at broadband onsets.
- ITD slope near the front: d(ITD)/dθ = (a/c)(1 + cos θ) → **≈ 8.9 µs per degree at 0°, ≈ 4.5
  µs/° at 90°** (computed). Phase 08's "≤ 30 µs per 1° step" criterion is ~3× the physical
  slope; a 2° direction bin gives ≤ ~18 µs ITD error.
- Measured maxima: Woodworth 1938 solid sphere ≈ 660 µs (Wikipedia ITD page,
  https://en.wikipedia.org/wiki/Interaural_time_difference, 2026-11-04); "maximal natural ITD of
  750 µs" and "ITD bound within ±0.8 ms" are commonly cited (search snippets, 2026-11-04).
  KEMAR / KU100 measured maxima at 90° typically fall in **0.65–0.75 ms** (phase-08 acceptance
  0.6–0.75 ms is consistent); an exact dummy-head figure depends on the extraction method (the
  Aachen KEMAR paper compares 32 ITD estimators; Katz & Noisternig 2014 JASA report
  method-dependent differences of up to ~100 µs — unverified, from memory).
- **ILD**: at 90° "strongest above 1 kHz, about 10 to 20 dB" (hearing-aid review via Thieme,
  https://www.thieme-connect.com/products/ejournals/html/10.1055/s-0041-1735176, search
  2026-11-04); other sources quote ~10 dB at 500 Hz rising to ~30 dB at 5 kHz, or 6 dB at 1 kHz /
  12 dB at 5 kHz (different setups). Phase 08's ">6 dB averaged over 2–8 kHz at ±90°" is a safe
  lower bound; a value below ~5 dB indicates swapped ears, un-shadowed data, or DFE gone wrong.
- Median plane: |ITD| ≈ 0 and |ILD| small (phase-08: |ITD| < 20 µs, |ILD| < 1 dB at 0°). Residual
  asymmetry of real dummy heads (KEMAR with mismatched pinnae in the MIT full set!) can exceed
  1 dB above 4 kHz.
- **Duplex theory crossover ≈ 1.5 kHz**: below, interaural phase/time dominates; above, head
  shadow (ILD) dominates (Wikipedia ITD page, 2026-11-04). ITD detection threshold "up to 10 µs"
  (same page); ILD JND for 1/3-octave noise bands 2.6/2.6/2.5/1.4 dB at 250/500/1000/4000 Hz in one
  study (search 2026-11-04); classic JNDs ≈ 10–20 µs and ≈ 0.5–1 dB (unverified, from memory).
  Minimum audible angle ≈ 1° at the midline (search 2026-11-04).
- **Front/back confusions with non-individual HRTFs**: Wenzel, Arruda, Kistler & Wightman, JASA
  94(1) 111–123 (1993): confusions "increased significantly for virtual sources compared to the
  free-field stimuli" (abstract, https://pubs.aip.org/asa/jasa/article/94/1/111/961412,
  2026-11-04); fragments cite ≈14% free-field vs ≈29% virtual (unverified pairing). Begault,
  Wenzel & Anderson 2001: head tracking reduced reversals **from 59% to 28%**; HRTF type and
  reverberation did not significantly change reversal rates (search 2026-11-04). RWTH 2020
  preprint: 7.6% (individual) vs 10.7% (non-individual) front-back confusions, static
  (https://www.biorxiv.org/content/10.1101/2020.03.31.011650v1.full, search 2026-11-04). Expect
  **10–30% reversals** in static non-individual binaural; this is the Phase 08 "risk", not a bug.
- Externalisation: non-individual HRTFs give degraded externalisation; reverberation (a BRIR
  rather than an anechoic HRIR) is the main lever, head tracking the second (Begault 2001,
  search 2026-11-04). The plugin has no head tracking (F8/AX3), so the room tail is what sells
  externalisation; a tail with wrong coherence (too high) collapses the image inside the head.

---

## 4. HRIR interpolation

- **Nearest neighbour**: discontinuous level and ITD when the source crosses a Voronoi boundary;
  step size equals the grid spacing (5° MIT ring spacing → up to ~45 µs ITD jump frontally).
  Only acceptable if the grid is ≤ 1° (SADIE D1/D2 8,802 points is roughly 2° average spacing:
  (computed) 41,253 deg²/8,802 ≈ 4.7 deg² per point).
- **Bilinear on a regular lat-long grid**: needs a full regular grid; breaks at the poles and
  where azimuth resolution varies per ring (MIT, SADIE).
- **Barycentric on a spherical triangulation**: Gamper 2013 (JASA EL 134(6) EL547–EL554, DOI
  10.1121/1.4828983, https://hannesgamper.com/wp-content/papercite-data/pdf/gamper2013a.pdf,
  2026-11-04): Delaunay tetrahedralisation of the measurement points (for a single-radius set, the
  convex hull of the unit vectors gives the spherical Delaunay triangulation); barycentric weights
  g_i from solving the enclosing simplex, with T⁻¹ pre-computed per tetrahedron (12 adds + 9 muls
  per test); weights are positive inside, change smoothly, equal 1 at a vertex, and are identical
  on a shared edge/face across neighbouring simplices → **no discontinuities**. Search by
  adjacency walk (follow the face opposite the most negative coordinate) seeded by an octree.
  Interpolation is done on **magnitude spectra** ("as proposed by Zotkin et al."); phase from a
  spherical-head model; evaluation = RMSE of third-octave magnitudes 500 Hz–16 kHz.
- **Time alignment is required before interpolating/averaging HRIRs**: averaging raw HRIRs with
  different onsets produces comb filtering and ITD smearing. Standard pipeline: (1) estimate onset
  per ear per direction, (2) remove it (fractional delay) so all HRIRs are "aligned", (3)
  interpolate the aligned HRIRs (or their minimum-phase versions / magnitudes), (4) interpolate
  the ITD separately (linear in the same barycentric weights, or from a model), (5) re-insert the
  ITD as a fractional delay. Brinkmann & Weinzierl / Arend et al. "Magnitude-corrected and
  time-aligned interpolation of HRTFs" (arXiv 2303.09966, 2023) report that time alignment
  (SUpDEq) makes ITD errors "negligible … below the JND even at N = 1" in the SH domain (search
  2026-11-04).
- **Minimum-phase + ITD** representation: HRTF ≈ minimum-phase(|H|) · e^{−jωτ}; perceptually
  adequate when the low-frequency ITD is right (Kistler & Wightman 1992 — unverified, from
  memory; search snippet: "the minimum-phase-plus-delay approximation … is adequate as long as the
  low-frequency ITD is appropriate", 2026-11-04). Caveat: minimum-phase reconstruction via the
  cepstrum needs zero-padding (≥ 4× FFT) and a magnitude floor, else time aliasing creates
  pre-ringing.
- **Spherical harmonics** interpolation: fit SH coefficients (order N ≈ 20–35 for a dense set)
  to time-aligned HRTFs; continuous and differentiable but ringing on sparse/partial grids; SH
  order limits spatial bandwidth (N ≈ kа for alias-free). Alternative, not required by Phase 08.
- **Continuity criteria** (phase-08): per 1° azimuth step, broadband level change ≤ 1 dB and ITD
  change ≤ 30 µs. Physical expectations: level slope near 90° at high frequencies can reach
  ~1 dB/° on the shadowed ear (so test the *average of the two ears* or per-band limits, not the
  far ear alone); ITD slope ≤ 9 µs/°. Measurement of ITD in tests: cross-correlation of 1.5 kHz
  low-passed HRIRs, or onset threshold at −10/−20 dB on 3 kHz low-passed envelopes — the test and
  the converter must use the same estimator, otherwise systematic 50–100 µs offsets appear.

---

## 5. Diffuse-field equalisation (DFE)

- Definition: the diffuse-field transfer function of an ear is the power average over all
  directions, `|H_DF(f)|² = Σ_i w_i |H_i(f)|²` with quadrature weights w_i summing to 1 (area
  weights on the sphere). DFE divides every HRTF by `|H_DF|` (per ear, or a common filter from
  the mean of both ears), typically as a minimum-phase or linear-phase inverse with regularisation
  outside ~100 Hz–16 kHz. Sources: Middlebrooks' description "the root-mean-square of the measured
  HRTFs over all M directions"; "the power averaging is done for each ear of each subject";
  "assumes uniform spatial sampling around the head" (search summaries 2026-11-04, DAFx-17
  "Diffuse-field equalisation of first-order Ambisonics",
  https://www.dafx17.eca.ed.ac.uk/papers/DAFx17_paper_31.pdf). Møller et al. 1995 derived
  headphone target curves from blocked-ear-canal HRTFs (indirect citation, 2026-11-04).
- Why: removes the direction-independent part (measurement chain, microphone, ear-canal
  resonance of the dummy head, loudspeaker) so a generic HRTF adds no fixed colouration; makes a
  binaural render of a diffuse field spectrally flat per ear by construction (DF average of the
  DFE'd set is 0 dB in every band).
- Free-field vs diffuse-field headphone EQ: FF-EQ makes a frontal source flat (divides by
  H(0°,0°)); DF-EQ makes the diffuse average flat. Studio headphones are usually DF-equalised
  (or Harman-target), so DFE'd HRTFs played on DF headphones are the consistent pairing
  (unverified, from memory; consistent with the sources above).
- Per-ear vs common: per-ear DFE also removes the left/right asymmetry of the head (e.g. MIT
  full set's mismatched pinnae); a common filter keeps the asymmetry. Per-ear changes the ILD of
  the diffuse field to exactly 0 dB; the direction-dependent ILD remains.
- **Level consequences (important for Phase 08's ±1 dB energy test)**: after per-ear DFE the
  diffuse-field band energy per ear equals the omni (pressure) band energy → the *late tail*
  matches omni automatically if the noise variance matches. The *direct sound and early
  reflections* do **not**: |H_DFE(dir)|² in a band is the directional gain relative to the diffuse
  average (e.g. a frontal source may sit a few dB above the DF average at 2–5 kHz and below it at
  8 kHz; a lateral source gives +X dB near ear / −Y dB far ear). So "binaural per-band energy
  (average of two ears) = omni ±1 dB" holds exactly for the tail and only approximately for the
  early part; the review should ask what window the test uses.
- Interaction with the coherence target: DFE is a per-channel linear filter; magnitude-squared
  coherence is invariant to per-channel filtering, but max-lag IACC and any *complex* average
  used to compute the target are not — compute the IC target from the **same** (DFE'd or raw)
  set that the tail magnitudes use.

---

## 6. Interaural coherence of diffuse fields

- Definition used in acoustics (ISO 3382-1 IACC, unverified from memory for the exact clause):
  `IACF(τ) = ∫ p_L(t) p_R(t+τ) dt / sqrt(∫ p_L² ∫ p_R²)`, `IACC = max |IACF(τ)|` over
  **|τ| ≤ 1 ms**, per octave band, with early (0–80 ms), late (80 ms–end) and all variants.
  Signal-processing definition: normalised cross-spectrum `γ(f) = S_LR / sqrt(S_LL S_RR)`;
  "interaural coherence" in Faller/Menzer is the real-valued max of the normalised
  cross-correlation; for diffuse binaural sound "the imaginary part is small compared to the real
  part" (search 2026-11-04).
- **Free-field reference, two omnidirectional points spaced d**: `IC(f) = sinc(kd) = sin(kd)/(kd)`
  with `k = 2πf/c` (Politis 2016 arXiv 1608.07713: "For omnidirectional elements, the diffuse-field
  coherence is given by the well-known sinc function of the wavenumber-distance product",
  https://arxiv.org/pdf/1608.07713, 2026-11-04; Elko 2001, "Spatial coherence functions for
  differential microphones in isotropic noise fields", Microphone Arrays, Springer, pp. 61–85).
  Watch the two conventions: `sin(kd)/(kd)` vs the engineering `sinc(x)=sin(πx)/(πx)` with
  `x = 2fd/c`; both give the first zero at **f₀ = c/(2d)**: 1009 Hz for d = 17 cm, 1143 Hz for
  15 cm (computed). Values for d = 17 cm (computed): 63 Hz 0.994, 125 Hz 0.975, 250 Hz 0.902,
  500 Hz 0.642, 1 kHz ≈ 0, 2 kHz −0.009, 4 kHz −0.009.
- **Head-shadowed (measured) version**: Lindevald & Benade, JASA 80(2) 661–664 (1986): the
  two-ear correlation in a reverberant room is "well described by sinc(αδ)/[1+(βδ)⁴]^½ with
  α = 2.2 and β = 0.5" (δ = normalised frequency as defined in the paper), and head diffraction
  "lowers f_D, the decoupling frequency (first zero), to 500 Hz, about half the no-head value"
  for a 15 cm microphone pair; above f_D the two ear signals are nearly independent
  (https://pubs.aip.org/asa/jasa/article-abstract/80/2/661/673490, abstract, 2026-11-04). Borß &
  Martin (AES 35th Conf., 2009, https://aes.org/publications/elibrary/elibrary-page/?id=15157) and
  Menzer & Faller (AES 127th, 2009, "Binaural reverberation using a modified Jot reverberator with
  frequency-dependent interaural coherence matching"; Menzer & Faller 2010 IEEE TASLP; Faller &
  Menzer AES 128th 2010 "Stereo-to-binaural conversion using interaural coherence matching", which
  used the **DF-equalised MIT KEMAR set** for the head coherence curve) establish that the
  frequency-dependent IC and the energy decay relief are the perceptually relevant features of a
  late tail and that broadband IC matching is "not accurate enough" (search summaries,
  2026-11-04). Lindau, Kosanke & Weinzierl, JAES 60(11) 887–898 (2012) give the perceptual mixing
  time after which the tail may be treated as diffuse (https://www.aes.org/e-lib/browse.cfm?elib=16633).
  Practical shape: IC ≈ 1 below ~200 Hz, falls through ~0.5 near 400–600 Hz, first zero ~500–800
  Hz, |IC| ≲ 0.1–0.2 above ~1.5–2 kHz with a small positive bump 1–2 kHz for dummy heads
  (unverified, from memory; consistent with Lindevald & Benade's f_D ≈ 500 Hz).
- **Target from the HRTF set itself** (Phase 08): `IC(f) = Re{ Σ_i w_i H_L,i(f) H_R,i*(f) } /
  sqrt( Σ_i w_i |H_L,i|² · Σ_i w_i |H_R,i|² )` with area weights w_i over the measured sphere, on
  **time-aligned-as-measured** HRTFs (do **not** remove the ITD first — the ITD is what
  decorrelates the ears; do remove any common onset). Then band-average with the octave bands of
  `contract::kOctaveBandsHz`. If the test metric is max-lag IACC rather than zero-lag real
  coherence, convert consistently: for a diffuse field with a head, zero-lag Re γ can be negative
  while IACC ≥ 0 by definition.
- **2×2 decorrelation mixing** (standard): with unit-variance, uncorrelated n1, n2:
  `L = a·n1 + b·n2`, `R = a·n1 − b·n2` → `E[L²] = E[R²] = a² + b²`, `E[LR] = a² − b²`,
  `IC = (a² − b²)/(a² + b²)`. With `a² + b² = 1`: **`a = sqrt((1+IC)/2)`, `b = sqrt((1−IC)/2)`**
  (equivalently a = cos φ, b = sin φ, IC = cos 2φ). Negative IC ⇒ b > a. Swapping a and b
  flips the sign of IC. Applying per band: either (i) filter n1, n2 into bands and mix with
  per-band (a_k, b_k), or (ii) design mixing filters A(f), B(f) with A² + B² = 1 — both must use
  the **same two noise sequences** for L and R; using separately seeded noise per ear and then
  mixing gives IC = 0 regardless of a, b. The per-band envelope (Phase 04) must be applied
  identically to both ears **before or after** mixing but the same way, otherwise the energy
  balance changes the effective IC.
- **Measuring IC per band from a BRIR tail**: window the tail after the mixing time (e.g.
  80 ms → end, or from the Phase 04 crossover), octave-band filter both ears (zero-phase, same
  filter), compute the normalised cross-correlation over lags ±1 ms and take the max (IACC_late),
  or the zero-lag value if the target is zero-lag coherence; alternatively Welch cross-spectra and
  take `Re γ(f)` averaged over the band. Tolerance in phase-08: ±0.1 for 125 Hz–4 kHz; expect
  estimator variance ~0.05 for a 1 s tail at 125 Hz, so test on long tails or average several
  seeds.

---

## 7. BRIR assembly from image sources

- **Cost**: each image source needs a per-ear HRIR add: with N_h = 256 taps (48 kHz) and a
  band-shaping FIR of N_b taps the contribution is N_h + N_b − 1 samples × 2 ears, i.e. ≈ 2·N_h
  MACs per image source if band gains are applied as a short FIR before the HRIR, or 2·N_h·N_b if
  done as a direct convolution. Image-source count up to time t in a room of volume V is
  ≈ 4π c³ t³ / (3V) (classical; unverified from memory): for V = 200 m³, t = 80 ms → ≈ 430
  sources; for t = 150 ms → ≈ 2,800. Nearest-cell lookup must be O(log n) (k-d tree on unit
  vectors, or Gamper's adjacency walk), not a linear scan per image source.
- **Direction clustering** (Phase 08: bins of ~2° above order 3; direct and orders 1–3 exact):
  the perceptual argument is that early, strong, sparse reflections carry localisation and
  colouration cues (Begault: a single reflection is inaudible below ~21 dB under the direct sound
  at 3 ms and ~30 dB at 15–30 ms, NASA ICA paper via search 2026-11-04), whereas high-order,
  dense reflections only need statistically correct direction distribution. A 2° bin is below
  the frontal MAA (~1° only at the very front, >5° laterally and in elevation), and gives ≤ ~18 µs
  ITD error. Safe implementation: group members keep their **own arrival times and per-band
  amplitudes**; only the HRIR pair and the ITD are shared (the group's HRIR is applied once to
  the sum of the members' band-filtered impulses). Unsafe: snapping member delays to the group
  delay (destroys echo density), or sharing one band spectrum for all members.
- **Near-field (< 1 m)**: HRTFs are distance-independent beyond ~1 m (Gamper 2013 intro, verified
  2026-11-04); below 1 m ILDs grow strongly, especially laterally and at low frequencies where
  far-field ILD is small; ITD stays nearly constant with distance (Brungart & Rabinowitz 1999,
  search 2026-11-04). Fix if needed: distance-variation function (Kan, Jin & van Schaik 2009;
  rigid-sphere point-source/plane-wave ratio) applied to far-field HRTFs. Out of scope for
  Phase 08 but the code must at least not extrapolate the 1/r law into the HRTF gain twice.
- **Listener orientation**: a right-handed yaw ψ about +z rotates **counter-clockwise seen from
  above** (x → y). Head-relative direction = `R_z(−ψ) · (p_src − p_listener)`; using `R_z(+ψ)`
  mirrors the lateral cue whenever ψ ≠ 0 (passes all tests with the default facing!). AX3 facing
  toward the emitter centroid: in the plugin frame with facing +y at ψ = 0, `ψ = atan2(−c_x, c_y)`
  so that a centroid at +x (right) gives negative yaw (clockwise). Elevation uses the head's z
  (upright head, AX3) so `el = asin(z_rel/r)`.
- **Frame mapping, spelled out**: plugin (x right, y forward, z up) → SOFA (x front, y left,
  z up): `(x_s, y_s, z_s) = (y_p, −x_p, z_p)`; SOFA azimuth `atan2(y_s, x_s) = atan2(−x_p, y_p)`
  — exactly the plugin "+90° = left" convention. Typical sign bug: converting the SOFA grid
  with `az_plugin = az_sofa` but computing the query with `atan2(x_p, y_p)`; ITD magnitude test
  passes, the "left ear leads" sign test must be present to catch it.
- **ITD application**: the ITD belongs to the *difference* between ears; store per-direction
  onset_left/onset_right (fractional samples) and apply each ear's own delay; never add the ITD
  to one ear on top of HRIRs that still contain it (ITD applied twice → up to 1.4 ms, audibly
  wrong and will fail the 0.6–0.75 ms test — but only if the test exists at both ±90°).

---

## 8. Virtual ORTF stereo

- **Geometry**: two cardioids, **17 cm** apart, axes **110°** apart (±55° from the facing
  direction), recording angle ≈ 95–96° (Schoeps MSTC 74 page: "Distance between the microphones
  17 cm; Recording angle 95°", https://schoeps.de/en/products/stereo/stereo-microphones/mstc-74.html;
  Wikipedia: ±48° = 96°, "reasonable compatibility with mono playback", devised ~1960 at ORTF,
  https://en.wikipedia.org/wiki/ORTF_stereo_technique, both 2026-11-04).
- **Cardioid**: `g(θ) = 0.5·(1 + cos θ)`, θ = angle between arrival direction and capsule axis
  (3-D dot product). Frequency-independent ideal capsule (phase-09 assumption).
  **Random-energy efficiency (diffuse-field power gain relative to on-axis) = 1/3 = −4.77 dB**
  (computed: mean of g² over the sphere = ¼(1 + 2·0 + ⅓) = ⅓; EE417 handout lists cardioid REE
  0.333 / −4.8 dB, https://www.montana.edu/rmaher/ee417_fl08/MIC%20HANDOUT.pdf, 2026-11-04).
  Directivity factor = 1/REE = 3 for the cardioid; the "1.7" quoted by one web source is the
  directivity *index in dB* confusion — ignore.
- **Capsule delay**: capsule positions ±8.5 cm on the interaural (lateral) axis; delay per
  capsule = `−(p_capsule · u_arrival)/c` with `u_arrival` the unit vector **from listener to
  source** (the capsule nearer the source receives earlier). Max inter-capsule difference
  **0.17 m / 343 m/s = 0.496 ms = 23.8 samples at 48 kHz** for a source at ±90° (computed);
  phase-09 test: ±1 sample at 48 kHz. Sign bug: using the propagation direction (source→listener)
  without flipping the sign makes the far capsule lead.
- **Mono compatibility**: L+R for a source with inter-capsule delay τ has notches at
  `f = (2n+1)/(2τ)` with depth `20·log10((g_L+g_R)/|g_L−g_R|)` (computed): centre source τ = 0 →
  no comb; 30° source → τ = 0.248 ms, first notch 2.02 kHz, depth 11.3 dB; 55° → 0.406 ms,
  1.23 kHz, 5.9 dB; 90° → 0.496 ms, 1.01 kHz, only 1.7 dB because the far capsule is 20 dB down.
  So ORTF's mono compatibility comes from the level difference, not from the time difference;
  phase-09's "no notch deeper than 6 dB below 2 kHz for a *centre* emitter" is the right test;
  room reflections add shallow notches even for a centre source.
- **Diffuse-field coherence of the pair (analytic)**: for first-order patterns
  `g_i(u) = α + β (u·n_i)` at positions ±d/2 along unit vector d̂, with `k = 2πf/c` and spherical
  Bessel functions j_n (derived here from the plane-wave expansion; same route as Elko 2001 /
  Politis 2016):
  `C_12(f) = α² j₀(kd) + jαβ j₁(kd) (n₁+n₂)·d̂ + β²[ (n₁·n₂) j₁(kd)/(kd) − (n₁·d̂)(n₂·d̂) j₂(kd) ]`,
  `P_i = α² + β²/3`, `IC = C_12 / sqrt(P₁P₂)`.
  ORTF: α = β = ½, n₁·n₂ = cos 110° = −0.342, (n₁+n₂)·d̂ = 0 (symmetric, so IC is real),
  (n₁·d̂)(n₂·d̂) = −sin²55° = −0.671, P = ⅓:
  **`IC_ORTF(f) = 0.75·[ j₀(kd) − 0.342·j₁(kd)/(kd) + 0.671·j₂(kd) ]`**, `kd = 2πf·0.17/c`.
  Values (computed, c = 343): **DC 0.664**, 63 Hz 0.661, 125 Hz 0.652, 250 Hz 0.616, 500 Hz
  0.483, 1 kHz 0.133, 2 kHz −0.035, 4 kHz −0.010, 8 kHz −0.004. Note the low-frequency limit is
  **0.66, not 1.0** (coincident cardioids at 110° are only partly correlated); a tail model that
  assumes IC → 1 at low frequency is wrong for ORTF (but right for binaural).
- **Level calibration binaural ↔ stereo**: after per-ear DFE a binaural ear has 0 dB diffuse-field
  gain; an ORTF capsule has **−4.77 dB** diffuse-field gain and 0 dB on-axis. For a
  reverberant reference scene the stereo mode is therefore ~3–5 dB quieter in integrated loudness
  unless compensated; Phase 09 wants one fixed constant (AX2) derived from the diffuse-field gain
  (i.e. about +4.77 dB, adjusted for the direct-sound share of the reference scene) and verified
  by BS.1770 on pink noise (±1 dB). Equal **loudness** rather than equal **peak** is correct
  because peak is set by the direct sound and the crest factor of sharp HRIR pinna resonances vs
  a smooth cardioid, while the audible difference at a mode switch is the energy of the tail and
  the spectral tilt; peak-matched modes would jump several LU on the switch. BS.1770 sums channel
  powers (G_L = G_R = 1), so it is insensitive to inter-channel coherence — the match is on
  energy; fine for a fixed constant, but note both modes must be measured at the same stage
  (post-IR, pre-output-gain).

---

## 9. ITU-R BS.1770

Verified from the ITU PDF (https://www.itu.int/dms_pubrec/itu-r/rec/bs/R-REC-BS.1770-5-202311-I!!PDF-E.pdf,
2026-11-04) and the revision list (https://www.itu.int/rec/R-REC-BS.1770, 2026-11-04):

- Revisions: BS.1770-0 (07/2006), -1 (09/2007), -2 (03/2011), -3 (08/2012), -4 (10/2015),
  **-5 (11/2023), in force**. Annex 1: 3/2 systems (stereo included); Annex 2: true peak
  (4× oversampling); Annex 3: BS.2051 advanced sound systems with **position-dependent weights**
  (G = 1.41 for 60° ≤ |θ| ≤ 120° and |φ| < 30°, else 1.00); Annex 4: object-based audio (render to
  a BS.2051 layout first, then measure with Annexes 1/3) — appears to be the -5 addition
  (diff vs -4 unverified).
- Algorithm (Annex 1): K-weighting = stage 1 shelving ("spherical head") + stage 2 RLB high-pass;
  mean square per channel; weighted sum (L, R, C = 1.0; Ls, Rs = 1.41 ≈ +1.5 dB; LFE excluded);
  gating of **400 ms blocks, 75 % overlap**; **absolute gate −70 LKFS**; **relative gate −10 LU**
  below the absolute-gated loudness. `L_K = −0.691 + 10·log10 Σ G_i z_i` LKFS; "The constant
  −0.691 cancels out the K-weighting gain for 997 Hz"; a 0 dBFS 997 Hz sine in one channel reads
  −3.01 LKFS. LKFS "is equivalent to a decibel"; LUFS (EBU R128) is the same unit.
- Stage-1 coefficients at 48 kHz (from the PDF): b0 = 1.53512485958697, b1 = −2.69169618940638,
  a1 = −1.69065929318241; stage 2: b0 = 1.0, b1 = −2.0, a1 = −1.99004745483398. The remaining
  coefficients (b2 = 1.19839281085285, a2 = 0.73248077421585; stage 2 b2 = 1.0,
  a2 = 0.99007225036621) are (unverified, from memory). Other sample rates need re-derived
  coefficients (pyloudnorm does this).
- pyloudnorm 0.2.0 (2026-01-04, MIT, Christian Steinmetz) implements BS.1770-4 whose Annex 1 is
  identical to -5 for stereo; `Meter(rate, block_size=0.400)`; pin it in the Python requirements.

---

## 10. Reviewer's checklist (diff questions and the bug each catches)

### HRTF conversion (`tools/hrtf/convert_sofa.py`, `generic-v1.bin`)
1. Is `Data.Delay` read with its actual dims ([I R] or [M R]) and added to each HRIR's onset? — dropped ITD / wrong absolute delay.
2. Are left/right chosen from the sign of `ReceiverPosition[:,1]` (y > 0 = left) rather than index 0/1? — swapped ears on files that order receivers R, L.
3. Is `SourcePosition_Type`/`_Units` parsed and converted (spherical degrees → unit vectors) and the azimuth sense kept (SOFA ccw, +90° = left)? — mirrored lateral cues.
4. Is the grid converted to unit vectors before Delaunay/convex hull, and does the triangulation cover the measured cap only (no faces spanning the missing bottom cap)? — interpolation across the hole yields nonsense "below" directions.
5. Are DFE and the IC target computed with **area weights** over the sphere (and documented for a partial sphere)? — dense rings/poles bias the diffuse average by several dB.
6. Is the common onset removed with a fractional-delay estimator on low-passed (≈3 kHz) HRIRs with a stated threshold, and is the estimator the same one the tests use? — systematic 50–100 µs ITD offsets.
7. Are HRIRs time-aligned before resampling/truncation, and is the truncation window long enough (256 @ 48 kHz) to keep the shadowed ear's low-frequency tail? — pre-ringing or lost LF on the far ear.
8. Is the minimum-phase reconstruction (if used) done with ≥4× zero-padding and a magnitude floor? — time-aliased pre-echo.
9. Does the resampler use a high-quality polyphase (e.g. `resampy`/`scipy.signal.resample_poly` with ≥ 64-tap kernel) and are the ITDs rescaled by fs_new/fs_old? — ITD in samples not rescaled → 0.5× / 2× ITD at other rates.
10. Does the binary header carry: sample rate, N taps, direction count, triangulation, per-direction onset_L/onset_R in fractional samples, DFE filter, per-band IC target, and a version/checksum? — silent format drift.
11. Is the SOFA download verified by checksum, never committed, and does `LICENSE-generic-v1.txt` contain the York copyright, the full Apache 2.0 text, the "original dataset must be referenced" sentence and DOI 10.3390/app8112029; does `GLOBAL:License` inside the file agree? — licence CI check passes with the wrong licence.
12. If MIT KEMAR is the fallback: is the clockwise azimuth flipped, are the mismatched pinnae (full set) or the symmetrised compact set handled knowingly, and is the 1.4 m distance recorded? — mirrored and asymmetric HRTF.

### Lookup / interpolation (`src/sim/hrtf/HrtfSet`)
13. Is the query direction converted with `atan2(−x_rel, y_rel)` in the plugin frame (or an equivalent documented mapping), and is there a test that the **left ear leads** at +90°? — sign bug passes a magnitude-only ITD test.
14. Are barycentric weights computed on the time-aligned HRIRs and the **ITD interpolated separately** then re-applied as a fractional delay? — comb filtering between neighbours, ITD steps.
15. Does the triangle search handle points exactly on an edge/vertex and the 0/360° wrap (no (az, el) arithmetic)? — NaN weights / discontinuity at the seam.
16. Is the DFE applied exactly once (converter or runtime, switchable), and never to the tail only or the early part only? — timbre mismatch between early and late parts and the ±1 dB energy test failing in some bands.
17. Is the 1°-sweep continuity test run for the ear average (level) and for several elevations, with ITD measured by the converter's estimator? — a per-ear far-ear test flags physical 1 dB/° slopes as bugs, or hides a real jump.

### BRIR assembly (`BrirBuilder`, `ListenerFrame`)
18. Is the yaw rotation applied as `R_z(−ψ)` to world directions (and is there a test with ψ ≠ 0 and a lateral source)? — mirrored image when the listener is not facing +y.
19. Is the AX3 yaw `atan2(−c_x, c_y)` (facing +y at ψ = 0) with the < 0.1 m hold rule, and initial yaw +y? — listener spins when standing on the centroid.
20. Are per-ear onsets applied per ear (onset_L to L, onset_R to R), not the ITD added on top of HRIRs that still contain it? — ITD applied twice.
21. Does grouping keep each member's own arrival time and per-band amplitude and share only the HRIR/ITD, with direct path and orders 1–3 never grouped? — collapsed echo density, wrong early spectrum.
22. Is the fractional-delay kernel the Phase 03 one, applied with the same sign convention for arrival delay and capsule/ear delay? — ±1-sample systematic ITD offsets.
23. Does the 1/r distance law sit in the image-source amplitude only (not again in the HRIR gain), and is near-field (< 1 m) flagged as unsupported rather than extrapolated? — double distance attenuation.
24. Is the per-band energy test windowed and documented (tail-only is exact after DFE; whole-IR is direction-dependent)? — a test that can only pass for diffuse scenes, or one that hides an early-part gain error.
25. Is T30 measured on each ear after the coherence mixing with the same Phase 02 estimator? — mixing that changes energy per band changes the decay.

### Coherence mixing (tail)
26. Are `a = sqrt((1+IC)/2)`, `b = sqrt((1−IC)/2)` (and not swapped), with the formula and IC sign convention written in a comment next to the code? — IC sign flipped (tail sounds "phasey").
27. Do L and R draw from the **same two** seeded noise sequences (n1, n2), seeded from `tailSeed` + Phase 04 per-output offset, and the mixing applied per band after band-splitting both? — IC ≈ 0 regardless of target, or non-deterministic output.
28. Is the per-ear diffuse-field magnitude applied after the mixing identically per band for both ears, and does the test measure IC with the same definition as the converter target (zero-lag real coherence vs max-lag IACC)? — ±0.1 test mismatched by definition rather than by bug.
29. Is the target curve sampled at the band centres of `contract::kOctaveBandsHz` and does the test skip bands where estimator variance exceeds the tolerance (63 Hz, 8 kHz)? — flaky test.
30. Is negative IC handled (b > a allowed, no clamping to [0, 1])? — clamped target around 1–2 kHz.

### Virtual ORTF (`VirtualMicPair`)
31. Is the angle θ taken in 3-D between the arrival unit vector and the capsule axis, with `g = 0.5(1 + cos θ)` (not `cos` of the azimuth difference only)? — wrong gain for elevated reflections.
32. Are capsule axes at ±55° from the AX3 facing direction, left capsule at +8.5 cm on the **left** side (plugin −x), and does the test check the sign of L−R at +55°? — swapped channels.
33. Is the capsule delay `−(p_capsule·u_src)/c` with u pointing listener→source (near capsule earlier), giving 0.496 ms = 23.8 samples @ 48 kHz difference at ±90°? — far capsule leads (inverted image).
34. Is the analytic diffuse-field target `0.75[j₀(kd) − 0.342 j₁(kd)/(kd) + 0.671 j₂(kd)]` (low-frequency limit 0.664, not 1.0), documented with its derivation and evaluated per band? — binaural-style target reused for ORTF.
35. Is the level constant derived from the cardioid diffuse-field gain (−4.77 dB) once (AX2) and verified with pyloudnorm pinned to 0.2.0 on pink noise through the reference scene, both modes measured at the same stage? — per-scene auto-gain, or a measured match that includes the output gain.
36. Does the mono test sum L+R of a centre-emitter render and look for notches < 6 dB below 2 kHz, and does the code never add an "ORTF spacing" delay to a centre source? — spurious comb filter on centre.
37. Is `Kind::StereoSpeakers` switched through the Phase 06 crossfade with the click detector run across 10 switches? — zipper noise on mode change.
38. Is the ideal-capsule (frequency-independent cardioid) assumption and the "no crosstalk cancellation" note written in code comments with AQ7, so the Expert's Q7 decision can swap it? — undocumented assumption.

---

## 11. Source list (all accessed 2026-11-04 unless stated)

- SADIE II: https://www.york.ac.uk/sadie-project/database.html ; https://zenodo.org/records/12092466 ; https://zenodo.org/records/12092466/files/LICENSE.txt?download=1 ; https://www.york.ac.uk/sadie-project/ambidec.html (decoder page, non-commercial wording) ; paper DOI 10.3390/app8112029 (MDPI page returned 403).
- MIT KEMAR: TR-280 PDF mirror https://www.linux.bucknell.edu/~kozick/elec32007/hrtfdoc.pdf ; https://sound.media.mit.edu/resources/KEMAR.html (HTTP 503 on access) ; https://www.sofacoustics.org/data/database/mit/ ; https://raw.githubusercontent.com/kcat/openal-soft/master/utils/MIT_KEMAR_sofa.def ; https://www.auditory.org/mhonarc/1994/msg00092.html ; http://docs.twoears.eu/en/latest/database/impulse-responses/hrirs/.
- TH Köln KU100: https://zenodo.org/records/3928297 ; DAGA 2013 paper (search summary).
- CIPIC: https://raw.githubusercontent.com/amini-allight/cipic-hrtf-database/master/read_me.txt ; https://github.com/amini-allight/cipic-hrtf-database.
- SOFA: https://www.sofaconventions.org/mediawiki/index.php/SimpleFreeFieldHRIR ; https://www.sofaconventions.org/mediawiki/index.php/SOFA_specifications ; https://www.sofaconventions.org/mediawiki/index.php/SOFA_conventions ; https://www.sofaconventions.org/mediawiki/index.php/SOFA_(Spatially_Oriented_Format_for_Acoustics) ; https://dael.euracoustics.org/confs/fa2023/data/articles/000729.pdf ; https://github.com/pyfar/sofa_conventions ; https://github.com/hoene/libmysofa ; https://pyfar.readthedocs.io/en/stable/classes/pyfar.coordinates.html ; https://www.mathworks.com/help/audio/ug/read-analyze-and-process-sofa-files.html ; Majdak et al. 2022 JAES (abstract page only; PDF at ari.oeaw.ac.at returned 403).
- Python packages: https://pypi.org/project/sofar/ ; https://sofar.readthedocs.io/en/stable/readme.html ; https://pypi.org/project/pyfar/ ; https://pypi.org/project/h5py/ ; https://github.com/Unidata/netcdf4-python/releases ; https://pypi.org/project/pyloudnorm/.
- Interpolation: Gamper 2013 https://hannesgamper.com/wp-content/papercite-data/pdf/gamper2013a.pdf (DOI 10.1121/1.4828983) ; arXiv 2303.09966 (search summary).
- Cues: https://en.wikipedia.org/wiki/Interaural_time_difference ; Frontiers 2014 fnins.2014.00034 (search) ; Thieme hearing-aid review (search) ; Wenzel et al. 1993 https://pubs.aip.org/asa/jasa/article/94/1/111/961412 ; Begault, Wenzel & Anderson 2001 (search) ; RWTH 2020 bioRxiv (search) ; Brungart & Rabinowitz 1999 (search) ; Begault early-reflection thresholds (search).
- Coherence: Politis 2016 https://arxiv.org/pdf/1608.07713 ; Lindevald & Benade 1986 https://pubs.aip.org/asa/jasa/article-abstract/80/2/661/673490 ; Borß & Martin 2009 https://aes.org/publications/elibrary/elibrary-page/?id=15157 ; Menzer & Faller 2009/2010 (search; AES page 403) ; Lindau et al. 2012 https://www.aes.org/e-lib/browse.cfm?elib=16633 ; Elko 2001 https://link.springer.com/chapter/10.1007/978-3-662-04619-7_4.
- DFE: DAFx-17 paper https://www.dafx17.eca.ed.ac.uk/papers/DAFx17_paper_31.pdf (search summary) ; Møller 1995 (indirect).
- ORTF: https://en.wikipedia.org/wiki/ORTF_stereo_technique ; https://schoeps.de/en/products/stereo/stereo-microphones/mstc-74.html (search) ; cardioid REE https://www.montana.edu/rmaher/ee417_fl08/MIC%20HANDOUT.pdf (search).
- BS.1770: https://www.itu.int/rec/R-REC-BS.1770 ; https://www.itu.int/dms_pubrec/itu-r/rec/bs/R-REC-BS.1770-5-202311-I!!PDF-E.pdf (text extracted with pdftotext).
