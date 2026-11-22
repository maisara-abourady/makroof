<!-- Saved by the orchestrator from the researcher's report, 2026-11-22. -->

# Researcher dossier: RQ-W4-1 (phase 07c-2, D-W4)

Intended path: `docs/review/phase-07c-2/17-researcher-RQ-W4-1.md`. Corpus SOURCE_COMMIT c1b171f. All sources accessed 2026-11-22. IDs continue from R45 (file 7).

**Bottom line:** I found no peer-reviewed or standards source that compares small late-level steps made **during** movement with one level change **after** movement stops. That holds for late (diffuse) level, for steps of 0.1–1 dB, and for any update interval or crossfade. What I did find is adjacent evidence, each piece with conditions that differ from the product's (R46–R55). D-W4 is **NOT READY** on the literature. The gap is the comparison phase-10-3's listening item is planned to measure.

## 1. Decision served and questions examined

- **D-W4**, RQ-W4-1, as worded in `15-decider-rebuttal-r5.md` §Q2: the audibility or annoyance of in-motion late-level steps against one end step. For each source: step size, update interval, crossfade, signal, paradigm, N, movement speed, and late versus early.
- **Outcome test**, as worded there: "in-motion 0.1–1 dB steps below detection while a single end step of similar total size is detected" favours recency adoption; the reverse, or equal detectability, favours condition 4.
- **Knowledge inventory** (my rows; the rebuttal gave none):
  - KW4-a: Table 15.1's basis.
  - KW4-b: step detection during movement.
  - KW4-c: an end step at rest.
  - KW4-d: gradual versus abrupt level change.
  - KW4-e: late-level or D/R sensitivity.
  - KW4-f: FDN or time-varying reverb audibility.
  - KW4-g: crossfade or switching practice.

## 2. Findings

**R46. Corpus: Vorländer §15.3 and Table 15.1, and their basis (KW4-a)**
- **Finding:**
  - Table 15.1 is titled a "Proposal for update intervals", after Lentz et al. 2007:
    - 35 ms for source or head rotation;
    - 700 ms for translation > 0.25 m (binaural processing plus the specular part);
    - 3 s for translation > 1 m (binaural processing, specular plus scattering part).
  - The stated basis is VR user behaviour (LaViola 2003): head rotation up to about 45°/s, translation 30–50 cm/s. From these, an azimuthal resolution of about 1° and a 20 ms update time are taken as limits.
  - The section cites no listening test for these intervals. It also says nothing about level steps, step audibility or crossfade length.
- **Reference:** Vorländer, *Auralization*, §15.3 and Table 15.1 (corpus `docs/corpus/vorlaender-auralization.md`, L3952–3968).
- **Read/unverified:** Read in the corpus. The primary source could not be retrieved (see §3).
- **Confidence:** High for what the book says.
- **What it changes for the decider:** Table 15.1 is an engineering budget derived from movement speed, not a perceptual threshold. Its 3 s row says when the scattering (late) part *needs* updating during translation. It does not say whether a level step is heard. This confirms R29 and file 12, correction D3-L2.

**R47. Corpus: other Vorländer passages (KW4-a, KW4-g)**
- **Finding:**
  - §9.2.1: segmented convolution with frame length Δt (the reciprocal of the filter update rate) and fade-in/fade-out of length t_fade between filters. No t_fade value or audibility data is given (L2593–2601).
  - §15.1: 60 Hz update and 50 ms total delay are acceptable for interactive scenes, with latency "ideally below the jnd" (L3867–3869). This concerns latency, not level steps.
  - §6.2.5: fluctuation is most salient near 4 Hz AM (L1921). Derived: one adoption per 3 s is about 0.33 Hz, so it would be heard as discrete events, if at all, not as fluctuation. This derivation is mine.
  - Table 6.1: jnd of G is 1 dB (500–1000 Hz), between room conditions (L2056–2060; already R5).
- **Read/unverified:** Read in the corpus.
- **Confidence:** High.
- **What it changes for the decider:** The corpus holds no time-varying late-level audibility data. The search had to go outside.

**R48. Lentz, Schröder, Vorländer and Assenmacher (2007), the primary source of Table 15.1 (KW4-a)**
- **Reference:** "Virtual Reality System with Integrated Sound Field Simulation and Reproduction", *EURASIP J. Adv. Signal Process.* 2007, article 070540. doi:10.1155/2007/70540.
- **Finding:** Metadata confirmed through Crossref. The full text could not be fetched: Springer redirects to an authorisation page.
- **Read/unverified:** **Unverified** (content). I could not check whether the paper contains a listening test behind Table 15.1.
- **What it changes for the decider:** The "after Lentz et al. 2007" basis stays as the book states it (R46).

**R49. Schröder, Wefers, Pelzer, Rausch, Vorländer and Kuhlen (2010): RWTH practice (KW4-g)**
- **Finding:**
  - Engineering statements, with no listening test:
    - the late reverberation varies less when a user moves, so later IR parts get less frequent updates and longer subfilters;
    - the first 6,000 taps are updated at more than 40 Hz;
    - time-domain crossfading is used because hard filter switches cause audible artefacts.
  - No crossfade length is given. Audio runs at 44.1 kHz with 512-sample blocks.
- **Reference:** "Virtual Reality System at RWTH Aachen University", *Proc. ISRA 2010*, Melbourne, 29–31 Aug 2010. URL: https://vr.rwth-aachen.de/media/papers/VirtualRealitySystem.pdf
- **Location:** p. 7, "Real-time convolution engine".
- **Read/unverified:** Read.
- **Confidence:** Medium. It is a practitioner claim, not data.
- **What it changes for the decider:** The field's working assumption is that late updates can be slower. It is an assumption, not evidence on step audibility.

**R50. McKenzie, Meyer-Kahlen, Daugintis, McCormack, Schlecht and Pulkki (2022): 6DoF switching of interpolated SRIRs while walking (KW4-b, KW4-g)**
- **Finding:**
  - Set-up:
    - SRIRs were switched by nearest position on a 5 cm grid, interpolated from sparser measurements (IMD 10–500 cm) of a coupled-room transition (storage T60 0.29 s to stairwell 0.73 s).
    - Late reverberation was interpolated by relative RMS matching.
    - The switching crossfade was linear, over one convolution block (host block 512 shown).
  - Test:
    - VR, MUSHRA-like with a hidden reference and no anchor;
    - N = 13 (critical listeners);
    - dry drum kit and anechoic violin;
    - self-paced walking (speed not reported).
  - Results: IMD up to 50 cm was rated comparable to the 5 cm reference (median > 80 in 7 of 8 conditions). 200 and 500 cm IMD were rated significantly lower.
- **Reference:** "Perceptually informed interpolation and rendering of spatial room impulse responses for room transitions", *Proc. 24th ICA*, Gyeongju, 2022, ABS-0439. URL: https://leomccormack.github.io/sparta-site/docs/help/related-publications/mckenzie2022perceptually.pdf
- **Location:** §2.3, §3, §4.2, Fig. 4.
- **Read/unverified:** Read.
- **Confidence:** Medium.
- **What it changes for the decider:**
  - **Ill-informed if transferred.** The whole response (direct, early and late) changes together, the rating is overall similarity, and late level is not isolated. There is no "steps while moving versus one step at rest" contrast, and the listener's own walking and visuals are present.
  - It shows that frequent small switches during movement, each with a short crossfade, were not rated as degraded at fine grids.

**R51. Neidhardt and Zerlik (2021): position-dynamic AR, BRIR switching while walking (KW4-b, KW4-g)**
- **Finding:**
  - Set-up:
    - BRIRs on a 25 cm grid along 2 m, 2° azimuth;
    - room 144 m³, T60 0.99 s;
    - no interpolation; a cosine-square crossfade over one 512-sample block at 48 kHz (about 10.7 ms) at each switch.
  - Test: Yes/No plausibility with SDT; N = 17 (5 experienced); dry speech, pop music, snare drum; walking speed not reported.
  - No test of switching artefacts was run. Some participants said the change of level during walking was a helpful cue, and four untrained listeners reported unexpected level progression.
- **Reference:** "The Availability of a Hidden Real Reference Affects the Plausibility of Position-Dynamic Auditory AR", *Front. Virtual Real.* 2:678875 (2021). doi:10.3389/frvir.2021.678875
- **Location:** §2.2, §2.3, §2.5, §2.6, §4.1.
- **Read/unverified:** Read (first 100k characters of the page).
- **Confidence:** Medium.
- **What it changes for the decider:**
  - **Ill-informed if transferred.** The steps are whole-BRIR steps tied to the listener's own walking, and late level is not isolated.
  - Listeners do notice level progressions during movement and treat them as expected or unexpected cues, which is relevant to annoyance rather than detection.

**R52. Schneiderwind and Neidhardt (2024): late tail held static across positions (KW4-g)**
- **Finding:** In a position-dynamic AR demo, one BRIR's late tail was modified and applied to every position, on the stated assumption that the tail does not change significantly between positions and orientations. The paper is a demo, with no listening test.
- **Reference:** "Modified Late Reverberation in an Audio Augmented Reality Scenario", *Proc. DAFx24* (Demo), Guildford, pp. 310–313. URL: https://www.dafx.de/paper-archive/2024/papers/DAFx24_paper_97.pdf
- **Location:** §2.3, p. 312.
- **Read/unverified:** Read.
- **Confidence:** Medium, as a statement of practice.
- **What it changes for the decider:** Freezing the late part during movement is a published working assumption. It is not evidence that freezing is inaudible.

**R53. Simpson and Reiss (2013): gradual versus fast intensity changes (KW4-d)**
- **Finding:**
  - Set-up:
    - broadband noise pedestal at 33 dB SPL, diotic headphones;
    - symmetric linear up-then-down increments with half-ramps of 5 ms to 50 s;
    - 2IFC, 3-down 1-up (79.4 %);
    - N = 10, little training.
  - Thresholds are U-shaped on log time, with the best detection at about a 100 ms half-ramp. The authors state that slow ramps are hard to detect.
  - The per-condition dB values appear only in Fig. 5A, with no numbers in the text, so I report none.
- **Reference:** "The Dynamic Range Paradox: A Central Auditory Model of Intensity Change Detection", *PLoS ONE* 8(2):e57497. doi:10.1371/journal.pone.0057497
- **Location:** Supplementary Experiment; Fig. 5A.
- **Read/unverified:** Read (text). Values not extractable.
- **Confidence:** Medium (qualitative).
- **What it changes for the decider:**
  - Derived: a step with a crossfade of about 30 ms lies on the fast side, near the best-detection region (10–100 ms half-ramps).
  - Both options' steps are therefore near-best-detectable *per event*. Only a truly slow ramp (seconds) would gain from "slow ramps are hard to detect".
  - **Conditions differ:** these are transient up-down increments on noise, not sustained steps in a reverberant tail, and at a low level.

**R54. Larsen, Iyer, Lansing and Feng (2008): D/R discrimination (KW4-e)**
- **Finding:**
  - Set-up:
    - 300 ms wideband noise through auditorium BRIRs (T60 0.78 s);
    - the direct part was scaled and the reverberant energy held constant;
    - 2I-2AFC with a 20 dB level rove;
    - N = 8 experienced listeners, about 2 weeks of training.
  - D/R JND, slow / fast onset:
    - at −10 dB D/R: 6.7 / 5.8 dB (near the 7.15 dB ceiling, unreliable);
    - at 0 dB: 2.4 / 2.4 dB;
    - at 10 dB: 3.8 / 2.7 dB;
    - at 20 dB: 8.7 / 7.3 dB (near the ceiling, unreliable).
  - The text elsewhere gives slightly different values.
- **Reference:** "On the minimum audible difference in direct-to-reverberant energy ratio", *JASA* 124(1):450–461. doi:10.1121/1.2936368. PMC2677334
- **Location:** §3, Fig. 3.
- **Read/unverified:** Read.
- **Confidence:** Medium–high.
- **What it changes for the decider:**
  - The ratio cue alone needs about 2–3 dB near 0–10 dB D/R. Without a rove, a late-level step also changes overall level, and the jnd for that is about 1 dB (R5).
  - **Conditions differ:** separate static intervals, not a change inside a stream or during movement.

**R55. Lokki and Hiipakka (2001): time-variant FDN-type reverberator (KW4-f)**
- **Finding:**
  - Allpass coefficients were modulated sinusoidally at 2.6–3.5 Hz to raise gain before instability by 2.3–5.6 dB.
  - No listening test was run. The authors state that the time variance becomes more audible with modulation depth, mostly as coloration, and that this should be studied with listening tests.
- **Reference:** "A Time-Variant Reverberation Algorithm for Reverberation Enhancement Systems", *Proc. DAFx-01*, Limerick. URL: https://www.dafx.de/paper-archive/2001/papers/lokki.pdf
- **Location:** §2.2, §3.4.
- **Read/unverified:** Read.
- **Confidence:** Medium.
- **What it changes for the decider:** The FDN modulation literature I could reach is about coloration and phase or pitch modulation, not level steps. It is not transferable to D-W4.

## 3. Not found / unresolved

1. **The direct comparison** (in-motion late-level steps against one end step; any step size, interval or crossfade). Not found.
   - Searched (web, standard and extended): "audibility late reverberation update listener translation"; "time-varying late reverberation level fluctuation threshold"; "reverberation level step during moving source"; "switching room impulse responses crossfade during listener movement"; FDN modulation audibility; RIR interpolation 6DoF perceptual.
   - What would settle it: a JASA, Acta Acustica or JAES study, or phase-10-3's own blind test.
2. **Lentz et al. 2007 full text** (R48), to check whether Table 15.1 rests on any listening data. The Springer and SpringerOpen PDFs redirect to `idp.springer.com` authorisation; academia.edu and DOAJ returned 403.
3. **Sources located but not retrieved; all unverified, none used as evidence:**

| Source | Access result | What it may contain |
|---|---|---|
| Neidhardt and Reif (2020), "Minimum BRIR grid resolution for interactive position changes in dynamic binaural synthesis", AES 148th Conv., paper 10371 | aes.org 403; core.ac.uk 403 | Search snippets suggest a 1×2 m area, grids down to 5 cm and four signals |
| Neidhardt (2023), dissertation, TU Ilmenau, urn:nbn:de:gbv:ilm1-2023000155 | Bot-protection page | Reported to test simplified (including static-late) BRIR sets for translation |
| Neidhardt, Tommy and Pereppadan (2018), AES 144th Conv. | Paywall | — |
| Abehsera-Morell, Poirier-Quinot and Katz (2024), "Perception of changes in source orientation-dependent reverberation for a visible virtual vocal source", AES 156th Conv. (HAL hal-04639132) | Anubis block | Time-varying reverberant part during source rotation; the closest topical match found |
| 2026 *Acta Acustica* paper (modified late reverberation in AR, two rooms) | 403 | — |
| MDPI *Appl. Sci.* 11(3):1150 (2021) | 403 | — |
| Lindau (2014), dissertation (d-nb.info/106738622X) | 503 | Crossfade and perceptual mixing time in dynamic synthesis |
| Schlecht and Habets (2015), *JASA* 138(3):1389–1398, doi:10.1121/1.4928394 | Metadata only | Whether it has a listening test |
| Plack, Gallun and Hafter (2006), *JASA* 119(6):3950 | Abstract snippet via search only | Reportedly, abrupt onsets do not facilitate increment or decrement detection |

4. **Movement speed in the auralization studies:** none of the studies read reports walking speed. Only Vorländer's 30–50 cm/s assumption exists (R46).

## 4. Conflicts between sources

None directly on the question. The nearest tension:
- **Practice says late parts can be updated slowly or frozen** (R49, R52, and Table 15.1 R46). This is assumed, not tested.
- **Neidhardt and Zerlik report that listeners use, and sometimes find unexpected, level progressions during walking** (R51).

The two do not contradict each other on data, and neither isolates late level.

## 5. Seat claims screened

| Seat | Claim | Status | Reference |
|---|---|---|---|
| S4 (file 10) | "Table 15.1 already separates the two parts… 700 ms specular… 3 s specular plus scattering"; a design where "the diffuse level follow[s] within seconds matches the table's own structure" | **Confirmed** as a reading of the table. **Ill-informed** if taken as perceptual support: the table is a movement-derived proposal with no step-audibility data. | R46 |
| S3 (file 10) | Table 15.1 is "the only sourced latency anchor"; 0.25 m ÷ 0.7 s = 0.36 m/s, inside 30–50 cm/s | **Confirmed** (arithmetic correct; corpus L3957, L3965) | R46 |
| S1 (file 10) | The 700 ms is "a VR proposal applied 'by extension'" | **Confirmed** | R46 |
| Rebuttal r5 | Alternative "at most one per 3 s" | Mirrors Table 15.1's 3 s row by extension; no perceptual source found for 3 s as a *level-adoption* interval | R46 |

No seat submitted a claim specific to RQ-W4-1.

## 6. Corpus candidates (names only)

- Larsen et al. (2008), *JASA* 124(1), PMC open access.
- Simpson and Reiss (2013), *PLoS ONE* (CC BY).
- McKenzie et al. (2022), ICA.
- Neidhardt and Zerlik (2021), *Front. Virtual Real.* (CC BY).
- Lentz et al. (2007), *EURASIP J. Adv. Signal Process.* (open access per Semantic Scholar, but not retrievable here).

## 7. Readiness for the decider: D-W4

| Row | Status | IDs |
|---|---|---|
| KW4-a: Table 15.1's basis | Known. A movement-speed proposal with no listening data in the corpus; primary unverified. | R46, R48 |
| KW4-b: late-level step detection during movement | **Uninformed (not found).** Only whole-BRIR switching studies exist; they are ill-informed if transferred. | R50, R51 |
| KW4-c: single end step at rest | Under-informed. 1 dB G jnd between conditions; about 2–3 dB D/R jnd with rove; within-stream data are on tones or music only. | R5, R11, R13, R54 |
| KW4-d: gradual versus abrupt change | Under-informed (qualitative). Slow ramps are hard to detect; a crossfade of about 30 ms is not slow. Conditions differ. | R53 |
| KW4-e: late-level or D/R sensitivity | Known, with conditions (static intervals). | R54 |
| KW4-f: FDN or time-varying reverb audibility | Not transferable (coloration, no level steps). | R55 |
| KW4-g: switching and crossfade practice | Known as practice: about 10 ms block crossfades; late parts updated slowly or frozen; no thresholds. | R49–R52 |

**Verdict: NOT READY.** The load-bearing fact, how detectable or annoying in-motion late-level steps of 0.1–1 dB are against one end step of similar total size, has no published source I could find or retrieve. Several possibly relevant sources were blocked (§3, item 3). Neither branch of the rebuttal's "what would change the outcome" test is supported by the literature. If the blocked sources stay unavailable, only a measurement can fill this row, which is the kind of comparison phase-10-3's listening item is planned to run.

The decider should also know that every movement study found involves the listener's own walking, with visuals and proprioception. The product's "movement" is DAW automation heard by a stationary producer. That is a condition difference for any transfer.
