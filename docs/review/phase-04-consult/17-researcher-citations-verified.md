## 1. Questions examined
- Q1: The exact title, authors and venue of dEchorate, DOI 10.1186/s13636-021-00229-0.
- Q2: The licence on Zenodo records 6576203 and 6985104, and the exact Arni JASA citation.
- Q3: Does the dEchorate record say which sources are omnidirectional, and in which configurations they were used?

## 2. Findings table
All records accessed 2026-11-05.

| id | question | finding | reference | location | read/unverified | confidence | what it changes |
|---|---|---|---|---|---|---|---|
| R1 | Q1 | **The THIRD_PARTY.md title is correct** for the published article: "dEchorate: a calibrated room impulse response dataset for echo-aware signal processing". Authors in order: Diego Di Carlo, Pinchas Tandeitnik, Cédric Foy, Nancy Bertin, Antoine Deleforge, Sharon Gannot. Venue: EURASIP J. Audio Speech Music Process., vol. 2021, issue 1, article 39. Published online 2021-11-23. Licence on the article: CC BY 4.0. | Crossref metadata, https://api.crossref.org/works/10.1186/s13636-021-00229-0 | Crossref fields title, author, volume, article-number, license | read (Crossref metadata only; the Springer page redirected to a login and I could not fetch it) | high | Fixes the citation. Use "article 39". |
| R2 | Q1 | The arXiv preprint has a different title: "dEchorate: a Calibrated Room Impulse Response **Database** for Echo-aware Signal Processing". Its author order puts Deleforge before Bertin. This is v1, 27 Apr 2021. | Di Carlo et al., arXiv:2104.13168v1, https://arxiv.org/abs/2104.13168 | abstract page; PDF p. 1 | read | high | Cite the journal version (R1), not the preprint. |
| R3 | Q2 | dEchorate Zenodo record: "The dEchorate dataset", "Version 2.0 HDF5". Licence shown: **Creative Commons Attribution 4.0 International**. Publication date shown: March 22, 2021. Creators: Di Carlo, Tandeitnik, Foy, Bertin, Deleforge, Gannot. | https://zenodo.org/records/6576203 (DOI 10.5281/zenodo.6576203) | record metadata | read | high | Confirms CC BY 4.0. |
| R4 | Q2 | Arni Zenodo record: "Dataset of impulse responses from variable acoustics room Arni at Aalto Acoustic Labs", v1, 2022-08-12. Creators: Karolina Prawda, Sebastian J. Schlecht, Vesa Välimäki. Licence shown: **Creative Commons Attribution 4.0 International**. | https://zenodo.org/records/6985104 (DOI 10.5281/zenodo.6985104) | record metadata | read | high | Confirms CC BY 4.0. |
| R5 | Q2 | Karolina Prawda, Sebastian J. Schlecht, Vesa Välimäki (2022), "Calibrating the Sabine and Eyring formulas", J. Acoust. Soc. Am. 152(2), 1158–1169, DOI 10.1121/10.0013575. The DOI resolves to this title. | https://pubs.aip.org/jasa/article/152/2/1158/2838408/Calibrating-the-Sabine-and-Eyring-formulas | article landing page | read | high | Confirms the citation as given. |
| R6 | Q3 | **The paper names the omni source but does not give its configurations.** Table 2 lists the loudspeakers: 4× Avanton (directional, direct), 2× Avanton (directional, indirect), **1× B&G (omnidirectional)**, and 4× Fostex 6301bx (babble noise). Figure 3 (top view) marks three positions labelled omni₀, omni₁ and omni₂ as "omnidirectional sources", plus dir₀–dir₅. | arXiv:2104.13168v1 PDF | §2.1, Table 2 (p. 3); Fig. 3 (p. 4) | read (preprint; the journal text was not reachable) | medium | One omni loudspeaker shown at three positions. That is enough to make omni-only use possible, but see R7. |
| R7 | Q3 | No statement says in which of the 11 configurations the omni positions were recorded. The paper's own analyses use only directional sources. The RT60 analysis (Table 5) uses "directional sources 1, 2 and 3", 90 RIRs in each of the 10 rooms. The geometry estimation (Table 7) uses sources #1–#4. The Zenodo description and the GitHub README (https://github.com/Chutlhu/dEchorate) also say nothing on directivity or omni IDs. | arXiv PDF; Zenodo 6576203; GitHub README | §3.1 (p. 8), Table 5 (p. 9), §4.2 and Table 7 (pp. 11–12) | read | medium | Omni-per-configuration coverage can only be settled from the dataset's own metadata tables, at the 05d session (the reversal condition in report 15). It is not settled by any published text I could retrieve. |
| R8 | Q3 | Other conditions in the preprint. Room 6 × 6 × 2.4 m. Floor always absorbent. Excitation: ESS sweeps, 100 Hz–14 kHz. Temperature 24 ± 0.5 °C, 80 % RH, c_air = 346.98 m/s. RT60 is reported only for 500–4000 Hz because the 125 and 250 Hz bands had too little power. The authors say the loudspeaker response falls off exponentially below 300 Hz. | arXiv PDF | §2.1, §2.2 (pp. 3–4); §3.1 (p. 7) | read | high | Relevant to band coverage and to the speed of sound (the code uses c = 343 m/s). |

## 3. Not found / unresolved
- **Which configurations include omni recordings.** I searched the paper text (preprint), the Zenodo description and the GitHub README. None of them says. The dataset's database table or HDF5 metadata would settle it. I did not download either (licence and size rules).
- **The published article's full text.** The Springer link redirected to idp.springer.com authorisation. So R6 and R7 rest on preprint v1, and the journal version may differ. The Springer full text would settle this; it is open access but was not fetchable from here.

## 4. Conflicts between sources
- **Title and author order.** The arXiv v1 says "…Database…" and orders Deleforge before Bertin. The journal (Crossref) says "…dataset…" and orders Bertin before Deleforge. These are different versions, not an error.
- **Source count.** §1 says "6 sound sources". Table 2 lists 6 directional loudspeakers plus 1 omni. Figure 3 shows 6 directional and 3 omni positions. The preprint does not reconcile these.
- **Zenodo date.** Record 6576203 (v2.0) shows a publication date of 22 March 2021. That is earlier than the arXiv v1 (27 April 2021). I report it as displayed; it is probably the concept date.

## 5. Corpus candidates
- Di Carlo et al. 2021, EURASIP JASMP 2021:39 (CC BY 4.0).
- Prawda, Schlecht, Välimäki 2022, JASA 152(2):1158–1169.

## 6. For the decider
- R1: the THIRD_PARTY.md title is correct. Add "2021:39" and the author order Di Carlo, Tandeitnik, Foy, Bertin, Deleforge, Gannot.
- R3 and R4: both Zenodo records show CC BY 4.0.
- R5: the Arni citation is confirmed as given.
- R6: an omnidirectional B&G loudspeaker exists, shown at three positions (omni₀–omni₂).
- R7: no source I could retrieve says which configurations include the omni recordings. This stays open for 05d.