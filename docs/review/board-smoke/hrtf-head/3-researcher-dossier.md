# D1 (dry run) — researcher dossier (2026-11-09)

Method: the registered `researcher` agent, told to re-read `.claude/agents/researcher.md` (rewritten this session) and answer R1–R10 of `1-decider-convene.md`. Verbatim.

---

# Researcher dossier — D1 (dry run): generic HRTF `generic-v1` dataset

Corpus revision checked: `docs/corpus/SOURCE_COMMIT` = `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`. All web sources accessed 2026-11-09. "read" = I retrieved the text/record/image myself; "unverified" = seen only in an abstract, snippet or citation.

## 1. Decisions served and questions examined

- D1, K1–K3 / R1: licence terms of SADIE II (York), MIT KEMAR, TH Köln KU100 — commercial redistribution of derived data, attribution, share-alike/non-commercial.
- D1, K4 / R2: naming/trademark restrictions in the dataset terms (seat 7).
- D1, K5 / R3: per-set sample rate, HRIR length, directions, grid, elevation range, azimuth spacing, symmetry, SOFA convention, file size, checksums (seats 2, 3, 5).
- D1, K6 / R4: measurement distance, far-field status (ledger B5, AX6).
- D1, K7 / R5: equalisation state and microphone position (seat 4; converter DF-EQ once or twice).
- D1, K8 / R6: lateral ITD per set vs the phase-08 AC 3 window 0.6–0.75 ms (also ILD vs > 6 dB).
- D1, K9 / R7: errata, artefacts, measurement publication (seats 3, 4).
- D1, K10 / R8: controlled evidence on head-only vs head-and-torso generic sets (seat 1).
- D1, K11 / R9: which generic set comparable tools ship (seats 4, 7).
- D1, K12 / R10: BRIRs and heads in BRAS CR2–CR4, Arni, dEchorate (seats 2, 9).
- Decider premises screened (section 5): corpus claims the convene relied on (Begault MIT description, Blauert Fig. 2.30, Vorländer §9.5, Zotter & Frank IEM note, Roginska Fig. 4.1), the phase-08 licence rule's factual basis, THIRD_PARTY "Planned" row.

## 2. Findings table

`id | question | finding (value + conditions) | reference | location | read/unverified | confidence | what it changes`

### R1 — licences (K1–K3)

| id | question | finding | reference | location | status | conf. | changes |
|---|---|---|---|---|---|---|---|
| F1 | SADIE II licence (a, b) | Licence stated as **Apache License, Version 2.0**, "Copyright 2018, University of York", data "AS IS"; condition on the page: "The original dataset must be referenced whenever used in original or modified form"; academic users asked to cite DOI 10.3390/app8112029. No commercial restriction, no share-alike. KU100 (D1) and KEMAR (D2) are subjects of one database under one licence. | University of York, SADIE II Database page, https://www.york.ac.uk/sadie-project/database.html | licence paragraph; subject list | read | high | Both (a) and (b) are under one permissive licence; the attribution sentence is a York-page condition, not part of the Apache text (F3). |
| F2 | SADIE II official record, version, licence field | Zenodo record "SADIE II Database", AudioLab / Kearney (York), **licence field: Apache License 2.0**, current version **V2-2** (2024-06-18, "Erroneous .zip file corrected"), DOI 10.5281/zenodo.12092466; version history V1-0 (2018-06-20) … V1-3/V1-4 (2020) "updated license metadata in SOFA files", V2-1 (2024-03-27, DOI 10.5281/zenodo.10886409). Files with MD5: D1.zip 116.7 MB 468f0fce29c2f5880627c571b73e64c3; D1_HRIR_SOFA.zip 38.2 MB 4850c1eb8e63e2d4f605edcdb4d5c883; D2.zip 125.2 MB 0564133299f118fe2731f6d65abbd8f8; D2_HRIR_SOFA.zip 38.0 MB f555491d1b6b1a108bb4d26b63ad84a4; LICENSE.txt 11.6 kB; "SADIE II V2-2 README.pdf" 42 kB. | Zenodo, https://doi.org/10.5281/zenodo.12092466 (V2-2) and https://doi.org/10.5281/zenodo.10886409 (V2-1) | record metadata, "Files", "Versions" | read | high | Pin V2-2 files by these MD5s (SHA-256 to be computed at pin time; none published). Note: D2.zip was 1.3 GB in V2-1 and 125.2 MB in V2-2 — my inference, not stated: the "erroneous zip" was probably D2.zip; pin V2-2 only. |
| F3 | What the Apache 2.0 text itself requires for an embedded converted set | §4 Redistribution: give recipients a copy of the License; modified files carry prominent change notices; retain copyright/attribution notices from the Source form; NOTICE file only "if the Work includes a NOTICE text file" (SADIE's LICENSE.txt is the plain Apache text with the placeholder appendix, no NOTICE — F4). "Derivative Works" = "any work … based on (or derived from) the Work"; "Object form" = "any form resulting from mechanical transformation or translation of a Source form". No commercial restriction; no share-alike (§4 allows "additional or different license terms" for your modifications). §6: "This License does not grant permission to use the trade names, trademarks, service marks, or product names of the Licensor" except customary use in describing origin. | Apache Software Foundation, Apache License 2.0, https://www.apache.org/licenses/LICENSE-2.0 | §1, §4(1)–(4), §6, §7, §9 | read | high | Compliance = ship the Apache text + York copyright/attribution in `LICENSE-generic-v1.txt` and THIRD_PARTY; a change notice ("resampled/trimmed/DF-EQ'd") satisfies §4(2). Whether the York-page "must be referenced" sentence binds beyond §4 is a lawyer's call (seat 7 hand-off). |
| F4 | SADIE II LICENSE.txt content | The LICENSE.txt in the Zenodo record is the standard Apache 2.0 text; no York copyright header, dataset name or extra clause inside the file. | Zenodo, https://zenodo.org/records/12092466/files/LICENSE.txt | whole file | read | high | The attribution requirement lives on the York page / Zenodo description, not in the licence file; record both. |
| F5 | MIT KEMAR licence (c) | Page statement: data "Copyright 1994 by the MIT Media Laboratory", "provided free with no restrictions on use" provided "the authors are cited when the data is used in any research or commercial application". The technical document says "provided without any usage restrictions" and "We request that you cite the authors". No licence name; no share-alike; commercial use named explicitly. | MIT Media Lab, "KEMAR HRTF" page, https://sound.media.mit.edu/resources/KEMAR.html ; hrtfdoc, https://sound.media.mit.edu/resources/KEMAR/hrtfdoc.txt | copyright paragraph (page); copyright section (hrtfdoc) | read | high | (c) is permissive with a citation condition; wording differs between the two MIT texts (one makes citation a proviso, the other a request) — quote both in LICENSE-generic-v1.txt. Not a named OSI/CC licence: lawyer may want to classify it. |
| F6 | TH Köln KU100 licence (d) — paper | The 2013 paper's "License and Access" section: compilation "freely available under a Creative Commons CC BY-SA 3.0 license" (share-alike). | Bernschütz, B. (2013). A Spherical Far Field HRIR/HRTF Compilation of the Neumann KU 100. Fortschritte der Akustik – AIA-DAGA 2013, Merano, pp. 592–595. PDF: https://audiogroup.web.th-koeln.de/FILES/AIA-DAGA2013_HRIRs.pdf (also in Zenodo record F7) | p. 595, "License and Access" | read | high | **Share-alike** clause → phase-08 scope 1 stop condition unless the Zenodo licence (F7) is the operative one. See Conflict C1. |
| F7 | TH Köln KU100 licence (d) — Zenodo record | Zenodo record "Spherical Far-Field HRIR Compilation of the Neumann KU100", Bernschütz, published 2020-07-02, v1, DOI 10.5281/zenodo.3928297, **licence field: Creative Commons Attribution 3.0 Unported (CC BY 3.0)**; contact Christoph Pörschmann (TH Köln). Files with MD5: HRIR_L2702.sofa 3.4 MB a810d4bb3a2807155286f0835d18922c; HRIR_FULL2DEG.sofa 19.7 MB aa48acb20c1fb8ff3d8de116107b73c2; HRIR_CIRC360.sofa 493.7 kB 058fcf99ac72c2ab94b2eed514b90bdf; HRIR_L2354.sofa 3.0 MB; KU100_CDFC.mat 5.3 kB; HPCF.zip 1.1 MB. | Zenodo, https://doi.org/10.5281/zenodo.3928297 | metadata, licence field, file list | read | high | If CC BY 3.0 governs: attribution + no-endorsement only (F9). Conflict C1 with F6. |
| F8 | TH Köln official download page | Page lists the same datasets (CIRC360, CIRC360RM, L2354, L2702 "Lebedev", FULL2DEG "Gauss 2°"), HPCF (2015) and DFC (KU100_CDFC.mat, 2013); the only licence mark is a CC BY-SA 3.0 badge attached to the pictures download; no licence statement for the HRIR files; no citation request. | TH Köln Audio Group, https://audiogroup.web.th-koeln.de/ku100hrir.html | whole page | read | high | The publisher's own page does not settle the licence of the HRIRs; see C1. |
| F9 | CC BY-SA 3.0 vs CC BY 3.0 terms (for d) | BY-SA 3.0 §4(b): "You may Distribute or Publicly Perform an Adaptation only under: (i) the terms of this License" (or later/compatible); §1 "Adaptation" = "a work based upon the Work … such as a translation, adaptation, derivative work"; §4(c) attribution + "may not implicitly or explicitly assert or imply any connection with, sponsorship or endorsement"; no non-commercial clause. CC BY 3.0: attribution (§4(b)) and the same no-endorsement sentence; no share-alike, no non-commercial. | Creative Commons, https://creativecommons.org/licenses/by-sa/3.0/legalcode ; https://creativecommons.org/licenses/by/3.0/legalcode | §1(a), §4(b), §4(c) (BY-SA); §1(a), §4(b) (BY) | read | high | Whether a converted `.bin` embedded in a paid plugin is an "Adaptation" (SA would then reach it) is a legal question → lawyer. Under CC BY 3.0 it is attribution only. |

### R2 — naming/trademark (K4)

| id | finding | reference | status | changes |
|---|---|---|---|---|
| F10 | None of the three dataset terms grants or restricts use of "KU100", "Neumann", "KEMAR", "GRAS" beyond: Apache §6 (no trademark licence from York; customary origin description allowed — F3) and the CC no-endorsement sentence (F9). MIT text: silent. Trademark registrations for "KEMAR"/"KU 100" were not found in a retrievable primary register (search hit DPMA/USPTO pages for unrelated Neumann marks only; GRAS pages are vendor material, not cited). | F3, F5, F9 sources | read (dataset terms); **not found** (registers) | Seat 7: dataset terms are not the constraint; the trademark question stays with the lawyer. Describing origin ("measured on a Neumann KU 100 by TH Köln/York") is the customary use Apache §6 allows; marketing use of the names is not covered by any dataset licence. |

### R3 — dataset properties (K5)

| id | set | finding | reference | location | status | conf. |
|---|---|---|---|---|---|---|
| F11 | SADIE II D1 (KU100), D2 (KEMAR) — grid | 8802 measurements each at 1° resolution ("399 stoppages"); 23 Genelec 8010 at 23 elevations on three vertical arcs 45° apart, subject rotated on a motor stool; **elevation range −81° to +90°**, the −90° point interpolated from −81° (chair/motor blocked it); 12 elevations at 15° steps from −75° to +90°, plus Ambisonic-layout points. Points file: format `index, azimuth elevation;`, elevations present −90 (one point, az 0), −81, −75, −64.8, −60, −54, −45, −35.3, −30, −25, −17.5, −15, 0, 15, 17.5, 25, 30, 35.3, 45, 54, 60, 64.8, 75, 90; 1° azimuth at 0° elevation (0.0…359.0); last index 9201 (tool hand-tally; York page says 8802 — likely duplicates/overlaps, confirm from the SOFA file). Azimuth anticlockwise, 0° front; elevation + above. | Armstrong, C., Thresh, L., Murphy, D., Kearney, G. (2018). A Perceptual Evaluation of Individual and Non-Individual HRTFs: A Case Study of the SADIE II Database. Applied Sciences 8(11):2029, https://doi.org/10.3390/app8112029 ; York page (F1); points list https://www.york.ac.uk/sadie-project/Resources/SADIEIIDatabase/Extras/1deg.txt | paper §3.1, §3.2.1; page "Point counts"; 1deg.txt | paper **read via a text-rendering proxy of the publisher page** (MDPI and White Rose PDF blocked; confirm against the PDF at phase time); page and points file read | medium-high |
| F12 | SADIE II — rates, length, SOFA | Measured at 96 kHz / 24-bit (Fireface 400); IRs time-aligned and trimmed to **512 samples ("256 samples at 48/44.1 kHz")** with 10-sample fades; WAV offered at 44.1 k/16-bit, 48 k/24-bit, 96 k/24-bit; SOFA "AES69". **SOFA convention/version not stated** anywhere I could read (README PDF not readable through the tools). Symmetry: not stated; built-in microphones of each head (F18). | paper §3.1, §3.2.3; York page; Zenodo F2 | as listed | read (as F11) | medium |
| F13 | MIT KEMAR — grid, rates, length | 44.1 kHz, 16-bit; 710 positions, elevations −40° to +90° in 10° steps; azimuth count per elevation: −40°: 56 (6.43°), −30°: 60 (6°), −20…+20°: 72 (**5°**), +30°: 60, +40°: 56, +50°: 45 (8°), +60°: 36 (10°), +70°: 24 (15°), +80°: 12 (30°), +90°: 1. Full set: 512-sample responses (first 200 of 16383 discarded); compact set: 128 samples, symmetric (left ear data mirrored: right response = left at 360°−az), so no interaural difference in the median plane. Positioning ≈ ±0.5°. Pinnae: left DB-061 ("normal"), right DB-065 ("large red") — the two ears differ. Sizes: compact.zip ≈ 226 KB, full.zip ≈ 1.4 MB; no checksums published; original format raw .dat, not SOFA (third-party SOFA conversions exist at sofacoustics.org: mit_kemar_normal_pinna.sofa / mit_kemar_large_pinna.sofa, 1.1 MB each — unofficial). | hrtfdoc (F5), KEMAR page (F5), FAQ https://sound.media.mit.edu/resources/KEMAR/KEMAR-FAQ.txt ; https://www.sofacoustics.org/data/database/mit/ | hrtfdoc "measurements", table of elevations; FAQ Q7, Q10 | read | high |
| F14 | TH Köln KU100 — grid, rates, length | 48 kHz; grids: circular 1° (CIRC360, two variants), **Lebedev 2354 and 2702 nodes (full sphere)**, Gauss–Legendre 2° equiangular **16020 nodes** (full sphere; "no grid discontinuities as all grid nodes could be measured"); ≈22 000 post-processed IRs; HRIRs reduced to **128 taps** at 48 kHz after phase compensation; "around 30 taps" cover the interaural runtime difference. MATLAB `miro` objects, SOFA and OpenDAFF versions. Symmetry: not stated (both ears measured). SOFA convention: not stated. | Bernschütz 2013 (F6) | pp. 592–593 "HRIR Measurements", Fig. 2; p. 595 Conclusion | read | high |
| F15 | TH Köln files on the SOFA mirror | sofacoustics.org/data/database/thk/ lists HRIR_L2702.sofa 3.3 M, HRIR_FULL2DEG.sofa 19 M, HRIR_CIRC360.sofa 482 K, near-field variants (NF025…NF150), and KU100 BRIRs of WDR rooms (see F33). | https://www.sofacoustics.org/data/database/thk/ | directory | read | high (mirror, not the publisher; pin from Zenodo F7) |
| F16 | Embedded size (derived, seat 5) | My arithmetic, float32, 2 ears, 256 taps at 48 kHz scaled to 44.1/48/88.2/96 → 256·(0.919+1+1.838+2) ≈ 1474 taps per ear-direction across the four rates: SADIE 8802 dirs → 8802·2·1474·4 B ≈ **104 MB**; TH Köln L2702 → ≈ **32 MB**; MIT 710 → ≈ **8.4 MB** (before any decimation of the grid or int16 storage). | derived from F11, F13, F14 | — | derived | — |

### R4 — distance / far field (K6)

| id | set | finding | reference | status |
|---|---|---|---|---|
| F17 | all | SADIE II HRIRs: **1.2 m** (Genelec 8010; BRIRs 1.5 m). MIT KEMAR: **1.4 m** (Optimus Pro 7, anechoic chamber). TH Köln: **≈3.25 m** (Genelec 8260A, anechoic chamber 4.5×11.7×2.3 m, lower boundary ≈200 Hz), "can be considered as far field referring to the speaker dimensions". Corpus condition (Vorländer §9.5): standard HRTF distance-independent for > 1 m; Fig. 9.7 ILD grows below 1 m. | York page/paper (F1, F11); hrtfdoc (F5); Bernschütz 2013 p. 592; corpus `vorlaender-auralization.md` lines 2648–2650 | read |

All three sets were measured beyond 1 m, so none is itself "near-field"; AX6's 0.3 m minimum remains the CONDITIONS VIOLATED item (ledger B5), independent of the head chosen.

### R5 — equalisation state, microphone position (K7)

| id | set | finding | reference | location | status |
|---|---|---|---|---|---|
| F18 | SADIE II | Free-field equalisation removed loudspeaker and microphone responses, then **diffuse-field equalisation applied to all measurements** ("all measurements are diffuse field equalised"); LF below ~200 Hz modelled (275 Hz crossover, 4096-tap FIR; flat magnitude, linear phase below ~400 Hz). KU100 and KEMAR measured with their **built-in microphones**; the KEMAR's microphones "sit deeper in the ear canal mould" (paper's wording per §3.2.3). ITDs kept (used for alignment/QC); no minimum-phase step stated. Whether the shipped SOFA files are the DF-EQ'd version or also a raw variant is not stated on the page (original SADIE offered RAW/DFC/min-phase variants; SADIE II pages do not). | Armstrong et al. 2018 (F11) | §3.2.2, §3.2.3 | read (proxy) |
| F19 | MIT KEMAR | Full and compact data **include the KEMAR ear-canal resonance** (Etymotic ER-11 in Zwislocki occluded-ear simulators, i.e. eardrum-position pressure); full set unequalised (includes the measurement chain); compact set equalised for the loudspeaker (minimum-phase inverse filter, flat above 18 kHz) and "to a Neumann reference" per FAQ; separate **diffuse-field-equalised set** (`diffuse.tar.Z`, 44.1 kHz; power-spectrum average over all directions inverted by a minimum-phase filter). ITD not removed. | hrtfdoc; FAQ Q8, Q11, Q14, Q15 | as listed | read |
| F20 | TH Köln | Loudspeaker magnitude/phase compensated (FIR), adaptive LF extension below 200 Hz crossover, head/tail windowing; **not diffuse-field equalised in the HRIRs** — a separate "common diffuse field compensation filter" (KU100_CDFC) derived from spherical magnitude averaging is provided, plus headphone compensation filters for ≈20 headphones (12 re-seatings each). Built-in KU100 microphones (position inside the head not stated in the paper). | Bernschütz 2013 | pp. 593–595, Figs. 3, 6, 7 | read |

Consequence for scope 3 (converter DF-EQ): applying the converter's own DF-EQ to SADIE II would equalise twice; to TH Köln or MIT (full/compact) once. MIT data additionally carry an ear-canal resonance (Rumsey §3.2.4 / Begault Ch. 4 "Equalization" condition); SADIE's KEMAR mic position is also deeper than the KU100's per F18.

### R6 — ITD and ILD at ±90° (K8)

| id | set | finding | reference | status | note |
|---|---|---|---|---|---|
| F21 | SADIE II D1 (KU100) | York's own ITD plot: peak **≈ 0.85 ms** at ±90° (y-axis "ITD (s)", ×10⁻³; x-axis 180…−180); a dashed unlabelled reference peaks ≈ 0.53 ms. **Estimation method not stated** in the paper or on the page. ILD plot: ≈ 21–25 dB at 60–90° (band not stated). | https://www.york.ac.uk/sadie-project/Resources/SADIEIIDatabase/D1/ITD.png ; D1/ILD.png | read (image) | If this is a low-frequency/cross-correlation ITD it will exceed an onset ITD; the phase's onset-based AC 3 must be measured on the files. As plotted, 0.85 ms lies **above** the 0.6–0.75 ms window. |
| F22 | SADIE II D2 (KEMAR) | ITD plot peak **≈ 0.77 ms** at ±90°; ILD ≈ 23–25 dB at ±90°. Same caveats as F21. | D2/ITD.png ; D2/ILD.png | read (image) | Also above 0.75 ms as plotted. |
| F23 | TH Köln KU100 | Paper: "around 30 taps are covering the sonic runtime difference between the ears" at 48 kHz → 30/48000 = **0.625 ms** (derived from a stated approximate figure). Corpus: Zotter & Frank Fig. 4.25(b) shows the single-ear arrival curve (not an ITD). | Bernschütz 2013 p. 595; corpus `zotter-frank-ambisonics.md` line 1564 | read | Inside the window, but approximate. |
| F24 | MIT KEMAR | Corpus Roginska Fig. 4.1 (MIT KEMAR right ear, 44.1 kHz): onset ≈ −13 samples near 80–100°, ≈ +15 near 270–280° → spread 28 samples / 44.1 kHz ≈ **0.635 ms** (my reading of a figure description). Spherical-head cross-check (Woodworth, a(θ+sin θ)/c, θ = 90°): KEMAR a₁ = 8.5 cm (Algazi et al. 2001 p. 1118) → 0.0850/343·2.571 = **0.637 ms**; KU100 "typical diameter 17.5 cm" (Bernschütz 2013 Fig. 4) → 0.0875/343·2.571 = **0.656 ms**. Human onset ITD ≈ 650 µs at 90° (corpus Blauert Fig. 2.30). | corpus `roginska-geluso-immersive-sound.md` line 1499; F27; F14; corpus `blauert-ch2-one-sound-source.md` line 237 | derived | Model values, not measured; the phase must measure. |

### R7 — errata and data quality (K9)

| id | set | finding | reference | status |
|---|---|---|---|---|
| F25 | MIT KEMAR | SNR ≈ 65 dB for frontal incidence, lower contralaterally; turntable/other reflections arrive after the head response (~230 samples in); inverse filters "hacked together", magnitudes below −20 dB clipped, flat above 15 kHz; errata: compact-data maximum is in H-10e100a.dat (doc corrected); byte order may need swapping; compact set symmetric by construction (no median-plane binaural cues); page last revised 2000. Publication: Gardner, W. G., Martin, K. D. (1995). HRTF measurements of a KEMAR. J. Acoust. Soc. Am. 97(6):3907–3908, https://doi.org/10.1121/1.412407 (citation page read; text paywalled). | FAQ Q6, Q13, Q15; hrtfdoc; AIP page https://pubs.aip.org/jasa/article/97/6/3907/825514 | read |
| F26 | SADIE II | Version history: SOFA metadata fixed (V1-1), licence metadata (V1-3, V1-4), "bug fixes" (V2-1), "erroneous .zip corrected" (V2-2); two human subjects excluded for ITD asymmetries (paper §3.1); −90° row interpolated (F11); excitation 200 Hz–24 kHz sweeps with LF modelled below 200 Hz (F18). | F2; F11 | read |
| F27 | TH Köln | Chamber lower boundary ≈200 Hz, LF replaced by analytic extension below 200 Hz; residual floor/base-plate reflections smoothed in the tail; speaker deviations ±1 dB compensated; licence conflict C1. Same head measured by 10 labs in "Club Fritz" (Andreopoulou, Begault, Katz 2015, IEEE JSTSP 9(5):895–906, https://doi.org/10.1109/JSTSP.2015.2400417 — citation verified via Crossref; the reported inter-lab spectral differences ~12.5 dB < 6 kHz / ~23 dB > 6 kHz are **unverified**, abstract-level only). | Bernschütz 2013; Crossref record | read / unverified as marked |

### R8 — head-only vs head-and-torso, perceptual (K10)

| id | finding (paradigm, N, signal, static/tracked, EQ, result) | reference | location | status |
|---|---|---|---|---|
| F28 | **Møller et al. 1999** (the controlled multi-head study). 19 loudspeakers in a standard listening room (RT ≈0.3–0.4 s), 5-s **female speech**, identification task, **static** (heads held still), DT990 with per-head/per-subject equalisation. Experiment B (built-in mics, 8 subjects, 912 stimuli per head): median-plane errors real life 16.0% vs KEMAR 2 38.5%, KU80i 50.2%, **KU81i 44.0%**, HMS I 37.3%, HMS II 46.7%, B&K 4128 42.1%, 5930 48.5%, Toronto 41.2%; within-cone errors KU80i 21.7%, KU81i 13.7% vs KEMAR 2 3.6%. Experiment C (blocked-ear-canal mics, 20 subjects, 380 stimuli/head): same pattern (Fig. 6, 15). Authors note the Neumann heads (the only ones **without a torso**) have LEFT LOW/RIGHT LOW sources often heard as LEFT HIGH/RIGHT HIGH and suggest "lack of shadowing from the shoulders". **KU100 not tested**: Neumann had announced it but could not lend one. All heads performed in the poorer part of a set of human recording heads (Fig. 14). | Møller, H., Hammershøi, D., Jensen, C. B., Sørensen, M. F. (1999). Evaluation of Artificial Heads in Listening Tests. J. Audio Eng. Soc. 47(3):83–100. Open copy: https://vbn.aau.dk/ws/files/227876184/1999_M_ller_et_al_AES_Journal.pdf | §0.3.2 (KU100), §1.1–1.5, Table 1, Figs. 4, 6, 13–15, §2.6 p. 93 | read | Conditions differ from the product: speech, trained student listeners (N = 8/20), 1990s heads (KU81, not KU100), no room simulation. It is the only direct torso-vs-no-torso localisation evidence among dummy heads. |
| F29 | **Armstrong et al. 2018 (SADIE II)**: 16 listeners (all database subjects), ~90 s jazz ensemble, **static** binaural renders, DT-990 Pro with personalised headphone EQ, blind ratings of brightness, richness, externalisation, preference across 20 sets + anchors. Results: **KU100 highest mean preference, KEMAR next**; 81% preferred the KU100 to their own set; **externalisation: no significant pairwise differences**; preference–externalisation r = 0.46. **Localisation and front/back confusion not tested.** | Armstrong et al. 2018 (F11) | §4, §5, Tables 4–6 | read (proxy) | Music, static — closest conditions to the product; it speaks to timbre/preference, not to localisation. |
| F30 | **Algazi, Avendano, Duda 2001**: 6 untrained listeners, individualised HRTFs, headphones with Møller-type compensation, noise bursts; elevation judgement with 3-kHz-low-pass stimuli collapses in the median plane (r ≈ 0.1–0.2) but remains usable away from it (r up to 0.58 at −65° back; Table I); the low-frequency elevation cues are attributed to **torso reflection and head diffraction**; KEMAR with/without torso and pinnae analysed (Table III, Figs. 6–9). | Algazi, V. R., Avendano, C., Duda, R. O. (2001). Elevation localization and head-related transfer function analysis at low frequencies. J. Acoust. Soc. Am. 109(3):1110–1122. https://doi.org/10.1121/1.1349185 ; open copy https://escholarship.org/uc/item/7rf421w9 | §II–IV, Tables I–III | read | Physics-level support that a torso adds LF elevation cues; individualised HRTFs, not a generic-head preference test. |
| F31 | **Brinkmann, Roden, Lindau, Weinzierl 2015**: head-above-torso orientation produces "clearly audible differences"; median audibility thresholds ≈25° (torso interpolation) / ≈10° (head interpolation). | IEEE J. Sel. Topics Signal Process. 9(5):931–942, https://doi.org/10.1109/JSTSP.2015.2414905 ; DepositOnce record https://doi.org/10.14279/depositonce-9004 | abstract | unverified (abstract via repository page) | Lead only: shows torso cues are audible with a HATS (FABIAN); not a KU100/KEMAR comparison. |
| F32 | Corpus already holds: Roginska Fig. 4.16 (Andreopoulou & Roginska 2014: MIT-KEMAR among 16 sets, personal HRTF best overall, some public sets approach it); Vorländer §16.1.2 (dummy heads: front–back confusion for a large portion of subjects); Begault Ch. 2 Fig. 2.32 (≈47% reversals, speech, frontal, non-individual). | `roginska-geluso-immersive-sound.md` line 1682; `vorlaender-auralization.md` line 1967; ledger line 95–96 | read (corpus) | No controlled KU100-vs-KEMAR localisation study was found (see Not found N3). |

### R9 — what comparable tools ship (K11)

| id | tool | finding | reference | status |
|---|---|---|---|---|
| F33a | IEM BinauralDecoder | "The used HRTFs come from the Neumann KU 100 dummy head"; headphone EQ "measurements by Benjamin Bernschütz et al." linking to the TH Köln KU100 page; cites Schörkhuber, Zaunschirm, Höldrich (DAGA 2018, MagLS). Corpus (Zotter & Frank, Ch. 4 BinauralDecoder note) names "Cologne Applied Science University". | https://plugins.iem.at/docs/plugindescriptions/ ; corpus `zotter-frank-ambisonics.md` lines 413, 1654 | read |
| F33b | SPARTA / Spatial_Audio_Framework | Default compiled HRIR set: "a Genelec Aural ID of a KEMAR Dummy Head (@48kHz)", 836 directions × 2 × 256 taps (`__default_hrirs[836][2][256]`). | saf_hrir.h, https://raw.githubusercontent.com/leomccormack/Spatial_Audio_Framework/master/framework/modules/saf_hrir/saf_hrir.h | read |
| F33c | Steam Audio | Ships a "built-in HRTF" (`IPL_HRTFTYPE_DEFAULT`); dataset/head **not named** in the documentation; SOFA (SimpleFreeFieldHRIR subset) loadable. | https://valvesoftware.github.io/steam-audio/doc/capi/hrtf.html ; programmer's guide | read |
| F33d | Resonance Audio (archived 2023) | Repository ships `third_party/SADIE_hrtf_database/WAV/Subject_002` under an Apache 2.0 LICENSE; York's original-SADIE page lists Subject 002 = **KU100** (Subject 001 = KEMAR; original SADIE: 1.5 m, 1550 points for dummy heads, Apache 2.0, now deprecated). The link Subject_002 → KU100 is my inference from these two documents. | https://github.com/resonance-audio/resonance-audio/tree/master/third_party/SADIE_hrtf_database ; https://www.york.ac.uk/sadie-project/database_old.html | read (both); derived link |
| F33e | Apple, Dolby, dearVR | **Not found** in official documentation: Apple developer pages document personalised profiles and head tracking APIs, not a dataset; no Dolby renderer HRTF documentation retrieved; dearVR has only vendor pages (not citable). | developer.apple.com updates pages (search) | not found |

Base rate (from F33a–d, N = 4 documented): KU100 in 2 (IEM: TH Köln campaign; Resonance: original SADIE), KEMAR in 1 (SPARTA, Genelec Aural ID, a third campaign), unnamed in 1 (Steam).

### R10 — BRIRs in project reference datasets (K12)

| id | dataset | finding | reference | location | status |
|---|---|---|---|---|---|
| F34 | BRAS v3 | **Yes, BRIRs exist, measured with the FABIAN head-and-torso simulator (DPA 4060 at the blocked ear-canal entrances)**, head orientations ±44° in 2° steps; for CR2–CR4: one receiver position, QSC-K8 at five positions (string-quartet layout), "BRIR 5/1 (S2, R3, C3, C4)"; RS1, RS3, RS5 also have BRIRs; RIRs for CR1–CR4 use B&K 4134 and the dodecahedron. BRIRs normalised by one gain per scene (unit-less), 44.1 kHz, SOFA + wav. FABIAN HRIRs (256 samples, 44.1 kHz, 11 HATOs) and meshes are supplied for simulation. Licence CC BY-SA 4.0 (badge on the documentation; record field). | Aspöck, L., Brinkmann, F., Ackermann, D., Weinzierl, S., Vorländer, M. BRAS – Documentation of the database, 2020-09-01, in record DOI 10.14279/depositonce-6726.3 (Documentation.pdf, 3.68 MB) | §2.1.3, §2.2, Table 1–3, §3.3.2, §3.4.2 (pp. 2–12) | read |
| F35 | Arni | Zenodo record: omnidirectional source, 5 receivers per configuration, 132 037 IRs, CC BY 4.0; **no dummy-head/binaural receiver mentioned**. | https://doi.org/10.5281/zenodo.6985104 | description | read |
| F36 | dEchorate | 6 handcrafted non-uniform linear arrays × 5 AKG CK32 mics (30 mics), 4 directional + 2 indirect Avanton loudspeakers, 1 omnidirectional B&G; 6×6×2.4 m room; **no binaural/dummy-head receiver**; CC BY 4.0 (Zenodo v2.0). | Di Carlo, D. et al. (2021). dEchorate… EURASIP J. Audio Speech Music Process. 2021:39, https://doi.org/10.1186/s13636-021-00229-0 (read as arXiv:2104.13168 PDF, §2.1, Table 2); Zenodo https://doi.org/10.5281/zenodo.6576203 | §2.1, Table 2 | read |
| F37 | Not a project reference, but relevant to seats 2/9: WDR broadcast-studio compilation (Stade, Bernschütz, Rühl 2012, TMT 27) has **KU100 BRIRs** (360 horizontal head orientations, 1°) for four rooms (LBS, SBS, CR1, CR7), CC BY 4.0. | https://doi.org/10.5281/zenodo.3930833 ; files mirrored at F15 | record | read |

Consequence: no project reference room is measured with a KU100 or a KEMAR; BRAS's binaural path is FABIAN, so option choice neither keeps nor loses a same-head comparison. A same-head (KU100) measured-BRIR comparison exists only outside the project set (F37).

## 3. Not found / unresolved

- N1 **TH Köln operative licence** (K3): three publisher-side statements disagree (F6 BY-SA 3.0 in the paper; F7 CC BY 3.0 on Zenodo; F8 badge on pictures only). Searched: Zenodo record, TH Köln page, paper. Settles it: the `GLOBAL_License` attribute inside HRIR_L2702.sofa (read at pin time, download not performed here) and/or a written answer from the record contact (C. Pörschmann).
- N2 **SADIE II SOFA convention/version and whether the SOFA files are the DF-EQ'd variant**: README PDF not readable through my tools (binary); paper silent. Settles it: `GLOBAL_SOFAConventions`, `GLOBAL_SOFAConventionsVersion`, `GLOBAL_Comment` in D1_HRIR_SOFA at pin time.
- N3 **A controlled KU100-vs-KEMAR localisation study** (static, untracked, with room): searched Google-style web, Acta Acustica, AES, JASA leads. Møller 1999 predates the KU100 (F28). A 2025 Acta Acustica paper (DOI 10.1051/aacus/2025005, KU100 non-individual BRIRs, static localisation in a studio) was blocked on four routes (PDF, HTML, DOI, redirect) — **lead, unverified, title not confirmed**. Two 2025–2026 arXiv preprints on KEMAR vs individual HRTFs are not peer-reviewed and are not cited.
- N4 **Onset ITD per set by the phase's criterion**: no source documents it; York's plots (F21–F22) use an unstated method. Settles it: compute from the pinned files in the phase (AC 3).
- N5 **SHA-256 of any file**: not published by any of the three publishers; Zenodo gives MD5 (F2, F7); MIT gives none. Compute at pin time.
- N6 **Andreopoulou et al. 2015 full text** (inter-lab KU100 variance): HAL, IEEE, LISN all blocked. Citation verified via Crossref only.
- N7 **Trademark registrations** for KEMAR / KU 100 (K4): no retrievable register entry found; lawyer item.
- N8 **Apple / Dolby / dearVR generic set** (K11): no official documentation found.
- N9 **Gardner & Martin 1995 JASA letter text**: paywalled; citation verified on the AIP page.

## 4. Conflicts between sources

- C1 TH Köln licence: Bernschütz 2013 p. 595 says CC BY-SA 3.0 (F6) vs Zenodo 10.5281/zenodo.3928297 licence field CC BY 3.0 (F7); TH Köln page gives no HRIR licence (F8). Not resolved here.
- C2 MIT wording: KEMAR.html makes citation a proviso ("provided the authors are cited… commercial application") vs hrtfdoc "without any usage restrictions… request that you cite" (F5). Same publisher, two texts.
- C3 SADIE II grid count: York page/paper 8802 points vs 1deg.txt last index 9201 (tool tally) (F11).
- C4 SADIE II D1/D2 ITD peaks as plotted (≈0.85 / ≈0.77 ms, F21–F22) vs the phase-08 AC 3 window 0.6–0.75 ms derived from Blauert Fig. 2.30 onset ITD ≈650 µs; the plotted method is unknown, so this is a potential conflict, not an established one.
- C5 Base rate: corpus says IEM uses KU100 "from Cologne Applied Science University" (Zotter & Frank); the IEM page names the KU100 but not the campaign, naming Bernschütz only for headphone EQ (F33a). Consistent, not contradictory; the campaign attribution rests on the corpus.

## 5. Seat claims / decider premises screened

| seat / source | claim (as stated) | status | reference |
|---|---|---|---|
| Decider K5 (Begault Ch. 4) | MIT KEMAR: 1.4 m, 44.1 kHz, 710 positions, elevations −40° to +90°, ML sequences | **confirmed** by the primary source; adds 5° azimuth at 0° elevation, 512/128-sample sets, differing L/R pinnae, ear-canal resonance included | F13, F19, hrtfdoc |
| Decider K8 (Blauert Fig. 2.30) | human onset ITD ≈ 650 µs at 90° | confirmed in corpus (`blauert-ch2` line 237) | corpus |
| Decider K8 (Zotter & Frank Fig. 4.25(b)) | KU100 TH Köln single-ear arrival curve, not an ITD | confirmed (`zotter-frank` line 1564) | corpus |
| Decider K6 / ledger B5 (Vorländer §9.5) | standard HRTF distance-independent only beyond 1 m | confirmed (`vorlaender` line 2648; Fig. 9.7 line 2650) | corpus |
| Decider K11 (Zotter & Frank) | IEM BinauralDecoder uses KU100 (TH Köln) | confirmed KU100 on the IEM page; campaign named only in the corpus | F33a |
| Decider B2 brief | "MIT KEMAR stops at −40° (corpus) and SADIE's lowest elevation is unknown" | confirmed for MIT; SADIE now known: −81° measured, −90° interpolated; TH Köln full sphere | F11, F13, F14 |
| Phase-08 scope 1 | "If the licence doesn't allow commercial redistribution of derived data, fall back to MIT KEMAR" | premise checked: SADIE II is Apache 2.0 (permits), MIT permits with citation; the only option with an unclear licence is the decider's variant (d) | F1–F9 |
| BUILD_PLAN §1 "Generic HRTF" row | "Measured dummy-head data with a permissive licence (verify in Phase 8)" | confirmed for SADIE II (Apache 2.0) | F1–F4 |
| Decider K7 (Begault/Rumsey) | KU100 as a recording head is diffuse-field equalised; measurement heads include ear-canal resonance | confirmed in corpus; dataset-level fact added: SADIE II stores DF-EQ'd data for both heads; MIT stores ear-canal-resonant data; TH Köln stores un-DF-EQ'd data with a separate DFC filter | F18–F20 |
| Decider K10 (Roginska Ch. 4) | "missing shoulders may weaken elevation cues" | corpus statement confirmed; external support: Møller 1999 p. 93 (Neumann heads without torso: low lateral sources heard high), Algazi 2001 (torso = LF elevation cue) | F28, F30 |
| THIRD_PARTY "Planned" | HRTF row to be added when pinned | no conflict; F2/F7 give the pin data | — |

## 6. Corpus candidates (primary sources worth adding; Maisara's decision, subject to licence)

- Møller, Hammershøi, Jensen, Sørensen (1999), JAES 47(3):83–100 (open copy at Aalborg VBN).
- Armstrong, Thresh, Murphy, Kearney (2018), Applied Sciences 8(11):2029 (CC BY 4.0).
- Bernschütz (2013), AIA-DAGA 2013 pp. 592–595 (in the Zenodo record).
- Algazi, Avendano, Duda (2001), JASA 109(3):1110–1122 (eScholarship copy).
- Aspöck, Brinkmann, Ackermann, Weinzierl, Vorländer, BRAS Documentation v3 (CC BY-SA 4.0) — already a project dataset; the documentation itself is not in the corpus.
- MIT KEMAR hrtfdoc.txt and KEMAR-FAQ.txt (dataset documentation).

## 7. Readiness for the decider — D1

| K | status after this dossier | facts |
|---|---|---|
| K1 SADIE II licence | **known** | F1–F4 |
| K2 MIT licence | **known** (two wordings, C2) | F5 |
| K3 TH Köln licence | **under-informed → unresolved conflict** | F6–F9, C1, N1 |
| K4 naming | known for dataset terms; trademark registers not found (lawyer) | F10, N7 |
| K5 properties | known for all three (SOFA convention of SADIE/THK: N2; grid-count discrepancy C3) | F11–F16 |
| K6 distance | **known** | F17 |
| K7 EQ state / mic position | **known** (corrected detail: SADIE already DF-EQ'd; MIT includes ear canal; THK raw + DFC) | F18–F20 |
| K8 ITD | **under-informed**: measured values only as York plots with unstated method (≈0.85/0.77 ms), THK ≈0.625 ms approximate, MIT derived; must be measured in the phase (N4, C4) | F21–F24 |
| K9 errata | known | F25–F27 |
| K10 head-only vs torso | **ill-informed: conditions differ** — the only controlled multi-head localisation study is speech, static, KU81 not KU100, 1999 (F28); the only KU100-vs-KEMAR study is static music preference/externalisation, no localisation (F29); no KU100-vs-KEMAR localisation study found (N3) | F28–F32 |
| K11 base rate | known for 4 tools (N = 4); Apple/Dolby/dearVR not documented | F33 |
| K12 reference BRIRs | **known**: BRAS = FABIAN; Arni, dEchorate none | F34–F37 |
| K13–K16 | known (corpus / plan), unchanged | — |

**Verdict: NOT READY** for a decision that includes option (d), and **READY on the licence question for options (a), (b), (c)**. What is still missing:

1. K3 — the operative licence of the TH Köln set is contradictory across the publisher's own documents (C1/N1). Phase-08 scope 1 treats "unclear" as a stop; nothing I can retrieve removes the ambiguity. Only the SOFA file's licence attribute or the record contact can.
2. K8 — no set has a documented onset ITD at ±90° by a stated criterion; York's own plots put both SADIE heads above the AC 3 window as plotted (C4). The decider can decide the head without this, but cannot assert that AC 3 as written passes for any head; the gate has to be measured on the files, and if it fails, challenged on evidence per the convene's note (i).
3. K10 — the decider holds true facts whose conditions differ from the product's (speech vs music; KU81 vs KU100; preference vs localisation). It can decide knowing this, but no retrievable study answers "KU100 vs KEMAR, static, untracked, music, with room" for localisation.

Facts the decider can rely on now, by id: F1–F5 (licences a–c), F11–F20 (properties, distance, EQ state), F25–F27 (quality), F28–F30 (perceptual, with their stated conditions), F33a–d (base rate), F34–F36 (reference datasets).
