Researcher report for Phase 05, follow-up to `docs/review/phase-04-consult/9-researcher-measurements.md`. All sources accessed 2026-11-05. I used only Read, Grep, Glob, WebSearch and WebFetch, changed no repo files and committed nothing. The PDFs I downloaded sit only in the session tool-results folder.

**Bottom line**
- **Q1 is answered.** Per-material α and s for CR2–CR4 are now in hand, read from a mirror (GitHub). Total S and V per room are known. Per-material areas and d_char are not: they exist only inside the BRAS zip. Exact zip paths are in §5.
- **Q2 is partly answered.** One primary source gives run-to-run scatter for ray tracing with diffuse rain (P11, F27). Measured small-displacement SDs for EDT and C80 are also found. Witew 2022 and ISO 3382-2 remain unretrieved.
- **Q3 and Q4 are not found.** The JASA full texts by Nosal, Hodgson and Ashdown, and Bork's round-robin papers, were blocked or are paywalled.

## 1. Questions examined
- **Q1.** BRAS CR2–CR4: third-octave α (initial estimates), s or d_char, area per material, dimensions. Classify each room by absorption contrast and by s.
- **Q2.** Seed-to-seed scatter of EDT and C80 in stochastic or hybrid simulation, and the spatial or measurement SD of EDT and C80.
- **Q3.** Bias of stochastic ray tracing with scattering against radiosity or analytic references; validation of diffuse rain or radiosity against measurement.
- **Q4.** Bork's round robins: quantitative EDT/C80/T differences with and without scattering, or between phases.

Corpus check: nothing new beyond what the earlier report cites (Vorländer §11.2.5 and §11.5–11.6; Kuttruff §5.7 and §8.6).

## 2. Sources retrieved in this task
- **[B-DOC]** Aspöck, Brinkmann, Ackermann, Weinzierl, Vorländer, *BRAS – Documentation of the database*, 2020. DepositOnce, DOI 10.14279/depositonce-6726.3. Read pp. 3–9 and 24–27.
  - The item has 19 files and no separate MaterialOverview.pdf.
  - Direct links exist for each zip. For example, `3_surface_descriptions.zip` (224.78 MB) is at https://depositonce.tu-berlin.de/bitstreams/b2970524-fb10-482a-ab14-f07da5ad7615/download.
- **[MIR]** naelolaiz/acoustic-spaces on GitHub, `validation/bras/` (https://github.com/naelolaiz/acoustic-spaces/tree/main/validation/bras). This is a third-party mirror. It states that it copies the BRAS `_csv` files unchanged (CC BY-SA 4.0).
  - I read the raw CSVs for CR2 (5 files), CR3 (7) and CR4 (8), plus `tests/test_bras.py`, `prepare.py`, `README.md` and `CR2/scene.yaml`.
  - The mirror is not an official BRAS release. Values were extracted through a summarising fetch tool, so transcription risk is low to medium. Phase 05 must re-read the values from the zip.
- **[P11]** Pelzer S., Schröder D., Vorländer M. (2011). The number of necessary rays in geometrically based simulations using the diffuse rain technique. *Fortschritte der Akustik – DAGA 2011*, Düsseldorf, pp. 323–324. https://pub.dega-akustik.de/DAGA_2011/data/articles/000216.pdf. Read in full.
- **[CKR13]** Christensen C.L., Koutsouris G., Rindel J.H. (2013). The ISO 3382 parameters: Can we simulate them? Can we measure them? *Proc. ISRA 2013*, Toronto. https://www.odeon.dk/pdf/ISRA2013_Paper_The%20ISO%203382%20parameters_Can%20we%20simulate%20them_Can%20we%20measure%20them_24July2013.pdf. Read pp. 1–22. The authors work for Odeon A/S, so note the affiliation.
- **[V11]** Vorländer M. (2011). Models and algorithms for computer simulations in room acoustics. *Proc. International Seminar on Virtual Acoustics (ISVA)*, Valencia, pp. 72–81. https://www.sea-acustica.es/archivo/congresos/ISVA2011/ISVA_005.pdf. Read in full.
- **[GV14]** Guski M., Vorländer M. (2014). Uncertainty of room acoustic parameters caused by air movement and temperature changes. *DAGA 2014*, Oldenburg, pp. 439–440. https://pub.dega-akustik.de/DAGA_2014/data/articles/000426.pdf. Read in full.
- **[W22-LP]** Witew I.B. (2022). *Measurements in room acoustics. Uncertainties and influence of the measurement position*. Logos, Aachener Beiträge zur Akustik 37, ISBN 978-3-8325-5529-0, DOI 10.30819/5529. Only the 11-page reading sample (https://logos-verlag.de/lp/9783832555290lp.pdf) was read: abstract and pp. 1–7. The full open-access PDF (https://www.logos-verlag.de/ebooks/OA/978-3-8325-5529-0.pdf) is larger than the 10 MB fetch limit.
- **[DFF25]** Dijkman L., Hoekstra N., Hornikx M. (2025). Comparing open-source room acoustics simulation tools. *Forum Acusticum Euronoise 2025*, Málaga, pp. 5493ff. DOI 10.61782/fa.2025.0229, CC BY 3.0. Read pp. 1–4.
- **[H-CA]** Hodgson M. When is diffuse-field theory accurate? *Canadian Acoustics*, pp. 41–42. https://jcaa.caa-aca.ca/index.php/jcaa/article/download/840/557/947. Read in full; the page shows no volume or year.
- **Leads only (vendor documents, not cited as evidence):**
  - Treble validation page for CR2: https://docs.treble.tech/validation/rooms/CR2
  - Odeon, *Danish Acoustical Society Round Robin*, technical report, 2008: https://odeon.dk/pdf/Classroom%20RR.pdf

## 3. Findings

| id | question | finding (value + conditions) | reference | location | read/unverified | confidence | what it changes for the decider |
|---|---|---|---|---|---|---|---|
| F22 | Q1 file layout | `3 Surface descriptions` contains `MaterialOverview.pdf`, `_csv/initial_estimates` and `_csv/fitted_estimates` (each CSV holds three lines: f, α, s), `_descr` (text descriptions), `_plots` and `_img`. One description file covers all CR materials. B-DOC also says: "The structural depth of all materials is listed in the corresponding material description files." S_i "was taken from the 3D room models". | B-DOC | §2.3 pp. 4–5; §3.2.2 p. 9; Eq. 2 p. 9 | read | high | d_char and areas exist only inside `3_surface_descriptions.zip`; no separate file. |
| F23 | Q1 α, s per material | Third-octave initial estimates for CR2–CR4 at 500 Hz / 1 kHz / 2 kHz, with s, are in table §4. All 31 bands from 20 Hz to 20 kHz exist. Fitted files exist for all three rooms but were not tabulated here. | MIR (copy of BRAS `_csv/initial_estimates/mat_CRx_*.csv`) | files named in §4 | read via mirror; not checked against the zip | medium | Allows the contrast and s classification below. |
| F24 | Q1 V and S | Totals from the BRAS model descriptions, as the mirror quotes them: CR2 V = 146.1 m³, S = 202.53 m². CR3 V = 3 330.6 m³ (includes the attic), S = 2 763.0 m². CR4 V = 8 656.5 m³, S = 5 851.3 m². No per-material areas found. | MIR `tests/test_bras.py` (comment cites `3 Surface descriptions/_descr/mat_CRx.txt`) | parametrised list and its comment | read (second-hand quote of a BRAS file) | medium | Gives S for Eyring and Sabine checks. CR3's model volume is 3 331 m³, against 2 350 m³ "excluding the attic volume" in B-DOC p. 26, so the coupled attic must be removed or modelled before any shoebox reduction. |
| F25 | Q1 dimensions | No official BRAS source gives dimensions. A vendor page gives CR2 as 8.4 × 6.7 × 3 m (lead only). **Derived:** that box has S = 203.2 m², matching F24's 202.5, but V = 168.8 m³ against 146.1. The documented corner protrusion (B-DOC photo p. 25) may explain this; not verified. | Treble page (lead); B-DOC p. 25 | — | lead only | low | Main dimensions must come from the .skp or OBJ files in Phase 05. |
| F26 | Q1 sanity check | **Derived:** CR2 at ᾱ ≈ 0.06 (F23) gives Sabine T = 0.161·146.1/(202.53·0.06) ≈ 1.9 s. RR19 Table II gives T_m = 2.0 s. | F23, F24; RR19 Table II (earlier report) | — | derived | medium | The initial estimates are consistent with the measured T for CR2. |
| F27 | Q2 seed scatter (hybrid RT) | RAVEN-type ray tracing with and without diffuse rain. Shoebox rooms of 500 m³ (T ≈ 0.5 s) and 10 000 m³. Each setup was run 20 times with identical parameters: 10 receivers, 10 octaves from 31 Hz to 16 kHz, 1.2 M simulations in total. About 4 000 rays kept the C50 run-to-run error below the 1 dB jnd. EDT "showed much less sensitivity" than G and C50. Diffuse rain needed on average 29 % fewer rays: 18 % in large or long-T cases needing more than 55 000 rays, up to 50 % with few rays. The error falls with N as Vorländer's σ_L = 4.34·√(A/(8πN r_d²)) dB. | P11 | Eq. 1 p. 323; Figs. 1–2 and "Results" p. 324 | read | high (method); medium (applying it to C80) | First primary evidence that seed-to-seed scatter is controllable: about 10³–10⁴ rays bring G and C50 below 1 jnd, and EDT is less sensitive. **Inference, not stated:** C80 integrates over a longer early window than C50, so it should be no more sensitive. The plotted quantity appears to be a maximum SD over receivers and bands; that is my reading of a small axis label. |
| F28 | Q2 spatial SD, measured | Auditorium 21, DTU. 7 receiver positions within ±30 cm laterally, ±15 cm front/back and ±10 cm vertically. Measured SD of EDT, T30, Ts, D50 and C80 is ≤ 0.7 jnd at 1 kHz and < 1.2 jnd at 125 Hz, except SPL. T30 SD is 0.02 s at 1 kHz (0.2 jnd) and 0.09 s at 125 Hz. Simulated values at the same nearby positions vary much less than the measured ones. With absorption calibrated to T30, simulated minus measured is 0.52 jnd on average for EDT and 0.16 jnd for T30 at 1 kHz. Above 1 jnd at 125 and 250 Hz. | CKR13 | §4.2 pp. 15–18, Figs. 9–14; §5.1 p. 20, Fig. 15 | read | medium (one room, Odeon authors) | Measurement noise floor for the AQ9 errors at 1 kHz is ≤ 0.7 jnd from position uncertainty alone. A geometric simulation does not reproduce this small-scale scatter. |
| F29 | Q2 excitation and repeat scatter | Same room, 1 kHz, sweep against balloons and hand-clap. C80 spans −1.7 to −0.3 dB and EDT 1.70–2.00 s across stimuli (Table 5). Repeated sweeps in a 5 500 m³ hall over 24 h: relative SD of T20 ≤ 1 % with ventilation on, ≤ 0.3 % off. | CKR13 Table 5 p. 19; GV14 pp. 439–440, Fig. 2 | — | read | medium | Repeat-measurement scatter of T is negligible against the 5 % jnd. |
| F30 | Q2 de Vries data | C80 at 1 kHz, sampled every 5 cm along a seat row in the Concertgebouw (de Vries, Hulsebos & Baan 2001), varies between about −4 and +0.5 dB over 26 m. Range is my graph reading. | W22-LP | Fig. 1.1 p. 2 | read (sample only) | medium | C80 varies by several dB across a hall at fine scale. Per-position sim-meas comparisons for C80 carry this floor. |
| F31 | Q2 round-robin measurement spread | RR-I average measured T carries "an uncertainty of 5 % (± 0.05 s)", citing Lundeby et al. 1995. In RR-I some simulated T differed by more than 50 % and G by up to ±5 dB. | V11 | §2.3 p. 74, Fig. 2 caption | read (secondary quote of LU95) | medium | Partly corroborates F19 (T about 5 %). EDT and C80 values from LU95 remain unverified. |
| F32 | Q1/B10 s uncertainty | Estimated SD of a *measured* random-incidence s is 0.04 at 125 Hz–2 kHz (95 % range ±0.08) and 0.07 at 4 kHz, derived via ISO 17497-1 Eq. A5. The paper also states that low s from 0.00 to 0.10 "can have a very strong influence" on results, and that the steps 0.40, 0.20, 0.10, 0.05, 0.025, 0.0125 matter about equally. | CKR13 | Table 3 p. 4; §2.1 p. 5 | read | medium | The boundary s ≤ 0.1 sits within about 1 SD of measured-s uncertainty. A room's class can flip on input uncertainty, and BRAS s values are model estimates anyway (F7). |
| F33 | Q3 radiosity vs RT | Qualitative only. Eyring T is accurate with diffuse reflection, or with specular reflection plus cubic shape plus uniform absorption. With low diffuse reflection and non-uniform absorption it becomes inaccurate. No dB or % values. | H-CA | §§III, V, VII pp. 41–42 | read | medium (qualitative) | Supports the B11 premise. Gives no bias number. |
| F34 | Q3 diffuse rain | P11 says diffuse rain was "already validated" in Schröder's 2011 RWTH PhD thesis, which was not retrieved. P11 itself gives run-to-run statistics, not bias against a reference. | P11 | p. 323 and ref. [2] | read | — | The validation numbers would be in Schröder 2011. |

## 4. Q1 table (third-octave centre values from the initial estimates)

**How to read this table**
- α and s are given at 500 Hz / 1 kHz / 2 kHz.
- d_char is **derived** from the unclamped s values with B-DOC Eq. 3 inverted: d = 4s²c/f, c = 343 m/s. The true values are in `_descr`.
- The AX17 s̄ is the mean of the three s values.
- Per-material areas are not available, so the contrast class is a **derived judgement from α only**.

| room | V (m³) | S (m²) | dimensions | material: α 500/1k/2k; s 500/1k/2k [d_char; AX17 s̄] | contrast class | s class | source location |
|---|---|---|---|---|---|---|---|
| CR2 seminar room | 145 (B-DOC p. 25); 146.1 model | 202.53 | not official; vendor lead 8.4 × 6.7 × 3 (F25) | **ceiling** .056/.056/.055; .148/.209/.296 [≈6 cm; .22]<br>**concrete** .066/.068/.069; .050/.060/.085 [≈5 mm; .065]<br>**floor** .082/.075/.072; .050/.050/.066 [≈3 mm; .055]<br>**plaster** .046/.051/.056; .050/.066/.094 [≈6 mm; .070]<br>**windows** .057/.066/.155; .050/.050/.054 [≈2 mm; .051] | **uniform**: all α 0.046–0.082 at 500 Hz–1 kHz; windows reach 0.155 at 2 kHz | **low s** (≤ 0.1) for 4 of 5 materials; ceiling ≈ 0.22 | MIR `validation/bras/CR2/materials/initial/mat_CR2_{ceiling,concrete,floor,plaster,windows}.csv`; zip `3 Surface descriptions/_csv/initial_estimates/` |
| CR3 chamber music hall | 2 350 excl. attic (B-DOC p. 26); 3 330.6 model incl. attic | 2 763.0 (model incl. attic) | not found | **seating** .328/.395/.665; .427/.604/.854 [≈0.5 m; .63]<br>**stagePanels** .122/.172/.197; .135/.191/.270 [≈5 cm; .20]<br>**ceiling** .092/.126/.155; .085/.121/.171 [≈2 cm; .13]<br>**plaster** .106/.122/.138; .050/.066/.094 [≈6 mm; .070]<br>**floor** .052/.061/.062; .051/.071/.101 [≈7 mm; .074]<br>**structuredPlaster** .069/.089/.101; .050/.050/.050 [≈1 mm; .050]<br>**windows** .057/.066/.155; .050/.050/.054 [.051] | **one strongly absorbing material** (seating, 3–6× the others) | mixed: seating high; stage panels and ceiling 0.13–0.2; rest ≤ 0.1 | MIR `CR3/materials/initial/mat_CR3_*.csv` |
| CR4 auditorium | 8 650 (B-DOC p. 27); 8 656.5 model | 5 851.3 | not found | **seating** .312/.404/.503; .427/.604/.854 [≈0.5 m; .63]<br>**brickwall** .213/.106/.382; .105/.148/.209 [≈3 cm; .15]<br>**woodPanels** .170/.166/.201; .105/.148/.209 [≈3 cm; .15]<br>**whitePanels** .061/.119/.150; .050/.050/.054 [.051]<br>**concrete** .076/.090/.068; .050/.054/.076 [≈4 mm; .060]<br>**linoleum** .077/.088/.203; .050/.060/.085 [≈5 mm; .065]<br>**parquet** .037/.066/.138; .050/.060/.085 [≈5 mm; .065]<br>**windows** .057/.066/.155; .050/.050/.054 [.051] | **one strongly absorbing material** (seating), plus a moderately absorbing brick wall | mixed: seating high; brick and wood 0.15; rest ≤ 0.1 | MIR `CR4/materials/initial/mat_CR4_*.csv` |

**Notes on the table**
- The CR4 brick-wall α spectrum is non-monotonic: 0.341, 0.213, 0.146, 0.138, 0.106, 0.160, 0.369, 0.382 from 400 Hz to 2 kHz. I re-checked it in a second fetch. It probably reflects a resonant construction.
- Windows have identical α in CR2, CR3 and CR4, so they are probably one database entry.
- No room shows "uneven α with low s". The strong absorber in CR3 and CR4 (seating) is also the high-s material. CR2 is low-s but uniform. **This is derived and needs areas to confirm.**

## 5. Not found / unresolved
- **Per-material areas and d_char for CR2–CR4.** Searched DepositOnce, GitHub, DFF25 and its Zenodo record (10.5281/zenodo.15396531, a 94 MB zip I did not download), and the Treble page. Per F22 and F24 they are only inside the BRAS zip, at these paths (as the mirror's scripts and comments give them; to be confirmed against the zip):
  - `3 Surface descriptions/_descr/mat_CR2.txt`, `mat_CR3.txt`, `mat_CR4.txt`: areas and d_char.
  - `3 Surface descriptions/_csv/initial_estimates/mat_CRx_<material>.csv` and `.../fitted_estimates/...`.
  - `MaterialOverview.pdf`, inside `3 Surface descriptions`.
  - Geometry: `BRAS/1 Scene descriptions/CR2 small room (seminar room)/Geometry/CR2.skp`, `.../CR3 medium room (chamber music hall)/Geometry/CR3.skp` and `.../CR4 large room (auditorium)/Geometry/CR4.skp`.
  - Measured parameters: `4 Additional data/Room acoustic parameters/data/Evaluation_CRx_<param>.txt`.
  - Some paths carry a `BRAS/` top-level prefix and some don't.
- **Main dimensions of CR2–CR4.** Must be extracted from the .skp files. RR19 §II.C says RAZR kept "ratios of the main room dimensions" but publishes none.
- **Witew 2022 full text.** OAPEN timed out, the FADU repository returned 403, and the publisher PDF exceeds the 10 MB fetch limit. A tool that can download large files would settle it.
- **ISO 3382-2:2008 uncertainty clause.** The ANSI preview, the MDPI paper (Appl. Sci. 13, 8607) and DIN all returned 403. Needs the standard text.
- **Pelorson et al. 1992 and Lundeby et al. 1995.** HAL was blocked by bot protection; there is no open copy of LU95.
- **Seed scatter specifically for C80.** P11 covers G, C50 and EDT. Autio et al. 2023 (*Acoustics* 5(1), 320–342, DOI 10.3390/acoustics5010019) has variance estimates, but MDPI returned 403/503 and the 21 MB thesis is too large. Unverified.
- **Q3 dB or % bias.** The UBC repository blocked access, sonicfield returned 410, and ResearchGate returned 403. The only text seen for Hodgson & Nosal 2006 is a search snippet ("very similar" radiosity vs diffuse RT), which is unverified. Needs JASA 116, 970 and JASA 120, 808, or Schröder's 2011 RWTH thesis.
- **Q4 Bork round-robin deltas.** The IOA PDFs returned 404, and there is no open text. PTB offers `results_p3_public.xls` (measurements) and `studio_coordinates_p3.xls` (α and s); neither contains simulation deltas. Needs Bork 2000 and 2005 Part II.

## 6. Conflicts between sources
- **Bork 2000 volume:** given as 86 on the PTB page and in this brief, but as 84 in V11's reference [11]. Volume 86 matches the year 2000. **Bork 2005:** given as vol. 86 on the PTB page, but 91 in V11 [12] and in the Brazilian papers.
- **CR3 volume:** 2 350 m³ excluding the attic (B-DOC p. 26) against 3 330.6 m³ for the full model (F24).
- **CR2 dimensions:** the vendor's 8.4 × 6.7 × 3 m matches the BRAS S but not V (F25).

## 7. Corpus candidates
- P11 (DAGA 2011)
- CKR13 (ISRA 2013)
- V11 (ISVA 2011)
- GV14 (DAGA 2014)
- Witew 2022 (open access, DOI 10.30819/5529)
- BRAS `3_surface_descriptions.zip` contents (CC BY-SA 4.0)
- Schröder 2011, RWTH PhD thesis (diffuse rain validation)

## 8. For the decider
- **F22, F24:** per-material areas and d_char exist only in the BRAS zip (`_descr/mat_CRx.txt`). Total S is CR2 202.5 m², CR3 2 763 m² (includes the attic), CR4 5 851 m².
- **F23 and §4:** CR2 has uniform α and is low-s on 4 of 5 materials. CR3 and CR4 each have one strong absorber (seating), and it is also high-s (s̄ ≈ 0.63). No BRAS room appears to combine uneven α with low s. Derived; needs areas to confirm.
- **F27:** run-to-run scatter of RT with diffuse rain drops below 1 jnd for G and C50 at about 4 000 rays in a 500 m³ room, and EDT is less sensitive.
- **F28–F30:** measured position-uncertainty SD is ≤ 0.7 jnd at 1 kHz and < 1.2 jnd at 125 Hz. C80 varies by several dB at fine spatial scale. Repeat-measurement T scatter is ≤ 1 %.
- **F32:** the s ≤ 0.1 class boundary sits inside the ±0.08 (95 %) uncertainty of a measured s.
- **Q3 and Q4:** still no numeric bias or round-robin delta. Plan without an a-priori bound.