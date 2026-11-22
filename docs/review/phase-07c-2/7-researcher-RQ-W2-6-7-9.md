<!-- Saved by the orchestrator from the researcher's report, 2026-11-22. -->

# Researcher dossier: RQ-W2-6, RQ-W2-7, RQ-W2-9 (phase 07c-2, D-W2)

Intended path: `docs/review/phase-07c-2/7-researcher-RQ-W2-6-7-9.md`. All sources were accessed on 2026-11-22. IDs continue from R1–R29 in `3-researcher-RQ-W1-W2.md`.

**Bottom line:**
- **The licence conflict on VCTK is not settled by its official page.** The Edinburgh DataShare page returned 403 on every route I tried (handle, OAI-PMH, bitstream). The DOI registration record (DataCite) and the corpus README both say CC BY 4.0. The York aggregator says ODC-BY 1.0.
- **Only one source passes dry recording and licence and gives a consent statement:**
  - The McGill TSP corpus is documented as anechoic and is under a BSD licence, but it states no consent and offers no checksum.
  - CMU ARCTIC is the only source with a signed voice-talent waiver, but it was recorded in a foam-lined booth, not an anechoic room.
- **No source checked offers a SHA-256 checksum from its publisher.**

## 1. Decisions served and questions examined

- **D-W2 / K25, RQ-W2-6 (blocking):** dry speech with documented recording conditions, plus a licence that allows (i) a company's internal tests and (ii) processed excerpts in a public CI artifact. Covered: VCTK 0.92, CMU ARCTIC, McGill TSP, Open Speech Repository, DAPS, and LibriSpeech/LibriVox. For each: checksums, URLs and consent statements.
- **D-W2 / K25, RQ-W2-7:** the CC BY 4.0 legal code (the right to adapt, the right to share adapted material, the attribution form).
- **D-W2 / K22, RQ-W2-9 (confirmation):** strong FWER control for two Bonferroni-split fixed-sequence chains. This checks D2-L1.
- **Seat claims:**
  - Seat 9: the speech must be dry, and documented as dry.
  - Seat 7: the licence must cover commercial internal tests and redistribution.
  - Seat 1: the graphical-procedure question.

## 2. Findings

**R30. VCTK 0.92: licence in the DOI metadata**
- **Finding:** The rights field reads "Creative Commons Attribution 4.0 International Public License". The publisher is the University of Edinburgh CSTR, issued 2019-11-13. No size, format or checksum is given.
- **Reference:** DataCite REST record for doi:10.7488/ds/2645. https://api.datacite.org/dois/10.7488/ds/2645
- **Location:** `rightsList`, `dates`.
- **Read/unverified:** Read.
- **Confidence:** Medium-high. This is the metadata the publisher deposited, but it is not the DataShare landing page.
- **What it changes:** Two sources close to the publisher (this record and R31) say CC BY 4.0. Only the aggregator (R32) says ODC-BY.

**R31. VCTK 0.92: README (version, licence, recording conditions)**
- **Finding:**
  - Version 0.92, "RELEASE September 2019".
  - The README says the corpus "is licensed under the Creative Commons License: Attribution 4.0 International".
  - Recorded "in a hemi-anechoic chamber of the University of Edinburgh" with a DPA 4035 omni and a Sennheiser MKH 800, at 96 kHz/24-bit. The files were then reduced to 16-bit, downsampled to 48 kHz and manually end-pointed.
  - The MKH 800 recordings of speakers p280 and p315 had technical problems.
  - The README states no mouth-to-mic distance, does not map the mic1/mic2 folders to the two microphones, and has no consent statement.
  - It asks users to cite Veaux, Yamagishi & MacDonald.
- **Reference:** CSTR VCTK Corpus README v0.92, read through a third-party mirror: https://huggingface.co/spaces/GipAdonimus/Real-Time-Voice-Cloning/raw/main/samples/VCTK.txt
- **Location:** README header, recording paragraph, licence line.
- **Read/unverified:** Read, but from a mirror, not the DataShare copy.
- **Confidence:** Medium.
- **What it changes:**
  - **Conditions differ:** hemi-anechoic means a reflective floor, so the recording is not fully anechoic. The distance is undocumented.
  - **Licence:** CC BY 4.0 would allow both uses (R36–R38).

**R32. VCTK 0.92: York catalogue record**
- **Finding:** Licence "ODC-BY 1.0". The record names datashare.ed.ac.uk as its source and gives the same DOI. It gives no recording conditions and no consent statement.
- **Reference:** YorVoice catalogue. https://catalogue.yorvoice.york.ac.uk/catalogue/M4IACQQQ
- **Location:** Rights field.
- **Read/unverified:** Read.
- **Confidence:** Medium. This is an aggregator.
- **What it changes:** The conflict stays open (§4). I did not read the ODC-BY text, so I make no claim about what ODC-BY permits.

**R33. VCTK 0.92: download URL and checksum**
- **Finding:**
  - URL: `https://datashare.is.ed.ac.uk/bitstream/handle/10283/3443/VCTK-Corpus-0.92.zip`
  - SHA-256 `f96258be9fdc2cbff6559541aae7ea4f59df3fcaf5cf963aae5ca647357e359c`
  - torchaudio defaults to `mic2`.
- **Reference:** torchaudio source, `torchaudio.datasets.vctk`. https://docs.pytorch.org/audio/main/_modules/torchaudio/datasets/vctk.html
- **Location:** Module constants; `VCTK_092.__init__`.
- **Read/unverified:** Read. It is a **third-party** checksum, not the publisher's. Any checksums DataShare shows are unverified (403).
- **Confidence:** Medium.
- **What it changes:** There is a reproducible pin for the archive, but the project would still need its own SHA-256 of the excerpt.

**R34. CMU ARCTIC: recording conditions, licence, consent**
- **Recording (§4 p. 9; §2 p. 4):**
  - A "soundproof booth" in CMU's speech lab: a double steel-walled chamber with foam baffling on the inner walls.
  - The talker sits 6–12 inches from a Sennheiser MD431, which the report calls a "near field condenser microphone". No pop filter was used in v0.95.
  - Capture at 32,000 Hz, with EGG on the second channel.
- **Licence (Appendix A p. 13):**
  - CMU, Copyright (c) 2003. "Permission to use, copy, modify, and license this software and its documentation for any purpose" without fee.
  - Conditions: retain the notice, conditions and disclaimer; mark modifications "clearly"; do not delete the authors' names.
- **Consent (Appendix A p. 13):** "All voice talents have signed a waiver agreeing to distribution of their recordings under these terms."
- **Release:** v0.95 has 4 voices (3 male, 1 female).
- **References:**
  - Kominek, J. & Black, A.W. (2003), *CMU ARCTIC databases for speech synthesis*, Tech. Rep. CMU-LTI-03-177, Carnegie Mellon University. Read through a third-party copy: https://fhgspco.github.io/ssmgan_spco/cmu_arctic_report.pdf
  - Corroboration: Kominek & Black (2004), "The CMU Arctic speech databases", *5th ISCA Speech Synthesis Workshop*, pp. 223–224, https://www.isca-archive.org/ssw_2004/kominek04b_ssw.pdf. Its abstract says the databases are distributed "without restriction on commercial or non-commercial use".
- **Read/unverified:** Read (the tech report through a mirror; the SSW paper on the ISCA archive).
- **Confidence:** Medium-high on the licence and consent; medium on whether later releases carry the same terms (the official festvox.org page returned 503 twice).
- **What it changes:**
  - This is the **only source with an explicit voice-consent statement**.
  - **Conditions differ:** a foam-baffled booth at 6–12 in is close-miked but not anechoic, and 32 kHz capture limits the bandwidth to below 16 kHz.
  - Downloads, checksums and the sample rate of the distributed files: **not retrieved.**

**R35. McGill TSP speech database v2 (2018-11): conditions and licence**
- **Recording (§1.1–1.2, pp. 1–2):**
  - "Recorded in an acoustic anechoic room" at McGill ECE.
  - Microphone on a stand about 15 cm from the talker, slightly off-axis. Sony ECM-909A stereo microphone; Sony TCD-D3 DAT recorder at 48 kHz/16-bit. The two channels were averaged to mono and the DC offset removed.
  - Constant gain; the files are not scaled.
- **Noise (App. A, pp. 15–16):** about 46 dB SNR relative to the average active speech level at 48 kHz, mainly preamplifier noise.
- **Content:** 24 adult speakers (12 male, 12 female) reading Harvard sentences, 1444 files. There are also 2 children (CA, CB), described as "extras" (§3.2).
- **Licence (§3.6 p. 13):** Simplified BSD, "Copyright (c) 2018 Peter Kabal". Redistribution with or without modification is permitted. Binary redistributions must reproduce the copyright notice, the conditions and the disclaimer in the documentation.
- **Documentation licence:** the PDF itself is CC BY 4.0 (p. ii). That licence covers the report, not the data.
- **Downloads:** `48k.zip` (248 MB) and others, from https://mmsp.ece.mcgill.ca/Documents/Data. **No checksums.**
- **Consent:** none found, either on the data page or in the PDF pages I read (pp. i–2, 12–16).
- **References:**
  - Kabal, P. (2018), *TSP Speech Database*, Database Version 2, McGill University. https://www.mmsp.ece.mcgill.ca/Documents/Reports/2018/KabalR2018b.pdf
  - Data page: https://mmsp.ece.mcgill.ca/Documents/Data
- **Read/unverified:** Read. The separate Licence.html returned 404; the licence was read in §3.6.
- **Confidence:** High.
- **What it changes:**
  - This is the only candidate documented as **anechoic** whose licence plainly allows commercial use and redistribution of modified material.
  - Gaps: the noise floor (46 dB SNR), no checksum, no consent statement, and the child recordings must be excluded.

**R39. Open Speech Repository (Telchemy)**
- **Terms:** free for "VoIP testing, research, development, marketing and any other reasonable application". The files may be "copied, downloaded, broadcast, modified". The source must be credited as "Open Speech Repository".
- **Files:** American English Harvard sentences, 10 female and 15 male files, **8 kHz** 16-bit WAV only.
- Recording conditions, checksums and consent: none given.
- **References:** https://www.voiptroubleshooter.com/open_speech/ and https://www.voiptroubleshooter.com/open_speech/american.html
- **Location:** Conditions of use; file list.
- **Read/unverified:** Read.
- **Confidence:** High.
- **What it changes:** **Unfit.** The audio stops at 4 kHz and dryness is undocumented.

**R40. DAPS**
- **Finding:**
  - Licence: "Creative Commons Attribution Non Commercial 4.0 International".
  - v1.0, 2014-05-20, G. J. Mysore (Adobe Research). The clean set is studio-produced speech, 20 speakers.
  - `daps.tar.gz` 16.1 GB, md5 `303c130b7ce2e02b59c7ca5cd595a89c`.
  - No consent statement.
- **Reference:** Zenodo record 4660670. https://zenodo.org/records/4660670
- **Location:** Licence field; files.
- **Read/unverified:** Read.
- **Confidence:** High.
- **What it changes:** **Non-commercial, so excluded** (same status as EARS, R27).

**R41. LibriSpeech: how "clean" was defined**
- **Finding:**
  - Speakers were ranked by the word error rate (WER) of a WSJ-trained recognizer. The lower-WER half was labelled "clean".
  - Selection for the first two training subsets favoured "higher recording quality" by an unspecified simple procedure.
  - Audio is 16 kHz. The paper documents no microphone or room.
- **Reference:** Panayotov, V., Chen, G., Povey, D. & Khudanpur, S. (2015), "LibriSpeech: an ASR corpus based on public domain audio books", *Proc. ICASSP 2015*. https://www.danielpovey.com/files/2015_icassp_librispeech.pdf
- **Location:** Abstract; §3.1–3.2, p. 3; Table 1.
- **Read/unverified:** Read.
- **Confidence:** High.
- **What it changes:** **"Clean" is a recognizer-error label, not an acoustic one** (ill-informed risk if it is read as "dry"). No reader is documented as close-miked or dry.

**R42. LibriVox recording requirements**
- **Finding:**
  - Submissions are MP3 at a constant 128 kbps, mono.
  - The guide gives no room requirement and no fixed mic distance ("speak closer" if the level is low).
- **Reference:** LibriVox wiki, "Newbie Guide to Recording". https://wiki.librivox.org/index.php/Newbie_Guide_to_Recording
- **Location:** Export settings; mic advice.
- **Read/unverified:** Read. This is the project's own guidance, a wiki of the publisher.
- **Confidence:** Medium.
- **What it changes:** LibriSpeech and LibriVox audio comes from lossy MP3 home recordings with undocumented rooms. **Their dryness cannot be documented.**

**R36. CC BY 4.0: grant, commercial use, adaptation**
- **Finding:**
  - §2(a)(1) grants a "worldwide, royalty-free, non-sublicensable, non-exclusive, irrevocable" licence. It covers reproducing and Sharing the material, and the right to "produce, reproduce, and Share Adapted Material".
  - Commercial use is not restricted, and there is no ShareAlike clause.
  - §1(a): Adapted Material is material "derived from or based upon" the licensed material. A processed (convolved) excerpt is my reading of "adapted"; the code does not name processing.
  - §1: "Share" means providing the material to the public.
- **Reference:** Creative Commons, *Attribution 4.0 International Public License*. https://creativecommons.org/licenses/by/4.0/legalcode.en
- **Location:** §1(a), §1 "Share", §2(a)(1).
- **Read/unverified:** Read through a fetch summarizer, with verbatim fragments.
- **Confidence:** High.
- **What it changes:**
  - Internal tests and a public artifact of processed excerpts are both within the grant.
  - The attribution duties in §3(a) apply "if You Share". Read literally, internal-only use does not trigger them. That is my reading of the text.

**R37. CC BY 4.0: attribution form**
- **Finding:**
  - §3(a)(1)(A): if the Licensor supplied them, retain:
    - (i) the creator identification;
    - (ii) the copyright notice;
    - (iii) a notice referring to the licence;
    - (iv) a notice referring to the disclaimer of warranties;
    - (v) a URI to the material, "to the extent reasonably practicable".
  - §3(a)(1)(B): indicate any modification and keep earlier modification notices.
  - §3(a)(1)(C): state that the material is under CC BY 4.0, with the licence text or a link to it.
  - §3(a)(2): these may be met "in any reasonable manner based on the medium, means, and context".
  - §3(a)(3): remove the attribution on the Licensor's request.
- **Reference:** As R36.
- **Location:** §3(a)(1)–(3).
- **Read/unverified:** Read.
- **Confidence:** High.
- **What it changes:** For a CI artifact, an attribution or notice file in the artifact appears to satisfy §3(a)(2). It would carry the creator, copyright, licence link, disclaimer reference, source URI/DOI and a "processed (convolved) by …" modification note. Whether a notice file suffices is my reading of §3(a)(2), not a statement in the code.

**R38. CC BY 4.0: limits relevant to voices and to a commercial project**
- **Finding:**
  - §2(b)(1): moral rights, and "publicity, privacy, and/or other similar personality rights", are **not licensed**.
  - §2(b)(2): patent and trademark rights are not licensed.
  - §2(a)(5)(B): no additional or different terms may be imposed on downstream recipients.
  - §3(a)(4): the licence applied to Adapted Material must not prevent recipients from complying with CC BY.
  - §2(a)(6): no endorsement may be implied.
  - §6(b): rights reinstate automatically if a violation is cured within 30 days of discovery.
- **Reference:** As R36.
- **Location:** §2(a)(5)(B), §2(a)(6), §2(b)(1)–(2), §3(a)(4), §6(b).
- **Read/unverified:** Read.
- **Confidence:** High.
- **What it changes:** **CC BY does not cover speakers' personality rights in their voices.** For VCTK and LibriSpeech, a consent statement is therefore a separate fact, and none was found. The artifact must not imply that the corpus authors endorse the product.

**R43. Graphical procedures: FDA guidance**
- **Finding (§8, ll. 343–370):**
  - The graphical approach (citing Bretz et al. 2009) builds Bonferroni-based sequentially rejective tests that ensure "control of the Type I error rate".
  - The initial node alphas sum to the total α. Each node is tested at its own alpha with the Bonferroni procedure.
  - An edge weight is the fraction of a rejected node's alpha passed along. Outgoing weights "should be 1.0, so that the entire preserved alpha is used".
- **Fixed sequence (Fig. A2, ll. 377–387):** the graph α → 0 → 0 with edge weights 1.
- **α split across branches:** Fig. A1 (ll. 332–339) shows α₁ + α₂ = α split over two branches.
- **Reference:** U.S. FDA (CDER/CBER), *Multiple Endpoints in Clinical Trials*, Guidance for Industry, October 2022. https://www.fda.gov/media/162416/download
- **Location:** Appendix §7 Fig. A1; §8 ll. 341–438; Figs. A2–A3.
- **Read/unverified:** Read.
- **Confidence:** High. This is regulatory guidance.
- **What it changes:** It confirms the construction in D2-L1. Note that the FDA's "should be 1.0" concerns using all the α ("α-exhaustive"), not validity (see R44).

**R44. Graphical procedures: the weight conditions for strong FWER control**
- **Finding:**
  - §2 states the conditions: initial weights ≥ 0 with Σ wᵢ ≤ 1; edge weights g_ij ≥ 0 with Σ_j g_ij ≤ 1 and g_ii = 0.
  - It says Bretz et al. [8] showed that such graphs define a procedure that "controls the FWER in the strong sense at level α". It describes the procedure as a closed-test shortcut with weighted Bonferroni intersection tests.
  - The §4.1 example passes a rejected primary's level within its own arm. If both hypotheses of one arm are rejected, the other arm's primary "can be tested at full level α".
- **References:**
  - Klinglmueller, F., Posch, M. & Koenig, F. (2014), "Adaptive graph-based multiple testing procedures", *Pharmaceutical Statistics* 13(6), 345–356. doi:10.1002/pst.1640. https://pmc.ncbi.nlm.nih.gov/articles/PMC4789493
  - The primary it cites: Bretz, F., Maurer, W., Brannath, W. & Posch, M. (2009), "A graphical approach to sequentially rejective multiple test procedures", *Statistics in Medicine* 28(4), 586–604. doi:10.1002/sim.3495
- **Location:** Klinglmueller §2, §4.1.
- **Read/unverified:** Klinglmueller read through a summarizer. **Bretz 2009 is unverified**: Wiley returned 403 and the scispace copy was empty.
- **Confidence:** Medium-high.
- **What it changes:**
  - D2-L1's design is a valid graph: w = (α₁, 0, α₂, 0)/α, g₁₂ = g₃₄ = 1, every other g = 0. The end nodes have outgoing sums of 0 (allowed, since ≤ 1), which is conservative.
  - Strong FWER ≤ α₁ + α₂ = 0.0490. This holds by the union bound with no assumption of independence.
  - **A property the decider may not hold:** the same framework allows the α of a fully rejected chain to pass to the other chain (an α-exhaustive variant). Doing so keeps FWER control. I state this as a property only, not as a choice.

**R45. D2-L1 arithmetic (derived)**
- **Finding:**
  - P(X ≥ 13 | 16, ½) = (560 + 120 + 16 + 1)/65536 = 697/65536 = 0.010635.
  - P(X ≥ 12 | 16, ½) = 2517/65536 = 0.038406.
  - Sum 0.049041.
  - Independent trial sets: 1 − 0.961594 × 0.989365 = 1 − 0.951368 = 0.048632.
- **Reference:** Computation.
- **Read/unverified:** Derived.
- **Confidence:** High.
- **What it changes:** It confirms the decider's 0.0490 and 0.0486.

## 3. Not found / unresolved

1. **VCTK on DataShare: the official landing page, its checksums and its licence field.**
   - All returned 403: https://datashare.ed.ac.uk/handle/10283/3443, the doi.org redirect, OAI-PMH, and the bitstream `license_text`.
   - What would settle it: the DataShare page fetched from another network, or the README and licence file inside `VCTK-Corpus-0.92.zip`, read locally after download by checksum.
2. **VCTK speaker consent.** No statement in the README (mirror) or the DataCite abstract. What would settle it: the CSTR data descriptor, or a written answer from CSTR.
3. **CMU ARCTIC downloads, checksums, distributed sample rate, and whether later releases keep the Appendix A terms.**
   - festvox.org/cmu_arctic returned 503 on three attempts (http and https).
   - What would settle it: the festvox page, or the `COPYING` file inside each `cmu_us_*_arctic` archive.
4. **TSP checksums and speaker consent.** None on the data page or in the report pages I read. What would settle it: a statement from the author (P. Kabal) or the archive's contents.
5. **Per-reader recording conditions for LibriSpeech/LibriVox.** None in the LibriSpeech paper or the LibriVox guide. I found no reader documented as close-miked dry.
6. **ODC-BY 1.0 legal text.** Not read; I make no claim about its terms.
7. **Miller et al. (2025), "An Anechoic, High-Fidelity, Multidirectional Speech Corpus"**
   - *JSLHR* 68(1), 411–418, doi:10.1044/2024_JSLHR-24-00296.
   - Anechoic, 17 microphones, 48 kHz, 30 talkers.
   - The Illinois record says the corpus is "publicly available" but gives no licence or host. ASHA returned 403.
   - **Unverified lead.** It would be a strong dry candidate if its licence allows commercial use.
8. **Bretz et al. (2009) full text.** Wiley returned 403; supported only through R43 and R44.

## 4. Conflicts between sources

- **VCTK 0.92 licence:**
  - CC BY 4.0 (DataCite R30; README mirror R31; torchaudio and Kaggle-style mirrors, not cited).
  - ODC-BY 1.0 (York aggregator R32).
  - The official DataShare page is unread. I pick no winner.
- **TSP licence:** the data is Simplified BSD (report §3.6 and the data page). The PDF is CC BY 4.0 (p. ii). This is not a real conflict: the two licences cover different objects. The search tool's summary had wrongly treated them as one.
- **Graphical procedures: "should be 1.0" (FDA, R43) against "≤ 1" (Klinglmueller citing Bretz, R44).** The first is a recommendation to use all the α; the second is the validity condition. Both stand.

## 5. Seat claims screened

| seat | claim (as stated) | status | reference |
|---|---|---|---|
| 9 | Speech must be "anechoic or close-miked dry, with that property documented" | **Can be met only by** TSP (anechoic, 15 cm) and VCTK (hemi-anechoic: conditions differ). CMU ARCTIC is close-miked in a foam-lined booth. LibriSpeech, LibriVox and OSR are undocumented. | R31, R34, R35, R41, R42 |
| 7 | Licence must allow a company's internal tests and redistribution in an artifact | **Met by** TSP (BSD), CMU ARCTIC (CMU permissive), OSR (credit required), VCTK if CC BY 4.0, and LibriSpeech (CC BY 4.0). **Not met** by DAPS, EARS (NC) or SQAM (R&D only). | R34–R40, R25, R27 |
| 1 / decider D2-L1 | Bonferroni-split fixed-sequence chains control FWER strongly at α₁ + α₂ | **Confirmed** (graph form; union bound). Bretz 2009 itself is unread. | R43–R45 |
| earlier dossier R23 | "CC BY 4.0 allows processing and redistribution with attribution" (inferred from the licence's name) | **Confirmed** from the legal code, with a caveat: personality rights are excluded. | R36–R38 |

## 6. Corpus candidates (named only; adding them is Maisara's decision)

- Kabal (2018), *TSP Speech Database* report (CC BY 4.0 document).
- Kominek & Black (2003), CMU-LTI-03-177.
- FDA (2022), *Multiple Endpoints* (US government work).
- Klinglmueller, Posch & Koenig (2014), PMC open access.
- Bretz et al. (2009), *Stat. Med.* (paywalled).
- The CC BY 4.0 legal code.

## 7. Readiness for the decider

| K | status | facts |
|---|---|---|
| K25: dry speech source | **Known, with gaps.** TSP: anechoic and documented, BSD. VCTK: hemi-anechoic (conditions differ), licence conflict unresolved by the official page. CMU ARCTIC: booth, not anechoic, has consent. LibriSpeech and OSR: dryness undocumented. DAPS and EARS: NC. | R30–R35, R39–R42 |
| K25: licence for an artifact | **Known for TSP** (BSD notice needed), **CMU ARCTIC** (notice, modification marking, author names) and **CC BY** sources (R37 form). **Under-informed for VCTK** (conflict). | R34–R38 |
| K25: consent | **Known only for CMU ARCTIC.** Uninformed for TSP and VCTK. CC BY does not cover voice rights. | R34, R38 |
| K25: checksums | **No publisher SHA-256 anywhere.** Third-party SHA-256 for VCTK; MD5 for DAPS and LibriSpeech; none for TSP, OSR or ARCTIC (unretrieved). The project's own SHA-256 pin, already in the requirement, is needed in every case. | R33, R35, R40, R23 |
| K22: FWER of the split chains | **Known (confirmed).** | R43–R45 |

**Verdict for D-W2:**
- **Ready on K22.**
- **Ready on K25 for the source choice with the gaps marked above.** At least one source (TSP) meets the stated requirement on dryness and licence, as documented. CMU ARCTIC meets it with a booth in place of an anechoic room, and it is the only one with consent.
- **Not ready on consent for TSP and VCTK, and on VCTK's licence**, for the reasons in §3 (official pages unreachable, no statements published).

### Ranking of speech sources by fitness (dry, then licence, then checksum)

This ranks the sources against the stated criteria only; it is not the choice.

1. **McGill TSP v2 (48 kHz).**
   - Dry: anechoic, 15 cm, documented.
   - Licence: BSD, commercial use and modification allowed. The artifact must carry the BSD notice and disclaimer.
   - Checksum: none offered.
   - Also: no consent statement; noise about 46 dB below active speech level; exclude CA/CB.
2. **VCTK 0.92 (48 kHz).**
   - Dry: hemi-anechoic, documented, distance not stated.
   - Licence: CC BY 4.0 per DataCite and README, against ODC-BY per York.
   - Checksum: third-party SHA-256 only.
   - Also: no consent statement.
3. **CMU ARCTIC v0.95.**
   - Dry: foam-baffled booth, 6–12 in, 32 kHz capture.
   - Licence: CMU permissive. **Signed talent waiver.**
   - Checksum: not retrieved.
4. **LibriSpeech (CC BY 4.0, MD5).** Fails on dryness: home MP3 recordings, "clean" defined by recognizer error.
5. **Open Speech Repository.** Fails: 8 kHz, conditions undocumented.

Excluded on licence: DAPS (CC BY-NC), EARS (CC BY-NC), EBU SQAM (R&D only). Licence unknown: Liverpool ARU, ITU-T P.501, Miller et al. 2025.

Note: the earlier dossier's R25–R28 entries were not re-checked in this task; their findings stand as reported there.
