# Researcher — dossier RQ1–RQ6 for D-T4 and D-T5

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

# Research dossier: phase 05b session 2, D-T4 (cost budget) and D-T5 (3) (matching interaction): RQ1–RQ6

All sources were accessed on 2026-11-09. **Read** means I fetched and read the text myself. **Unverified** means I saw only an abstract, a search summary or a citation in another work. I made no repository edits.

## Verdict
- **D-T4 is NOT READY.** Three rows of (a) are still uninformed: K8 (how much RAM producers' machines have), K9 (per-instance memory of comparable plugins) and K10 (instances per project). I found no credible source for any of them, and they look unlikely to exist. The decider will have to carry them as declared unknowns.
- **D-T5 (3) is READY, with an ill-informed flag.** RQ6 now has primary evidence, but only one study comes close to the product's conditions: Meyer-Kahlen 2021 (N=9, binaural, KEMAR, best case).

## 1. Decisions served and questions examined
- **D-T4 (a), K8:** RQ1, RAM in producers' machines and the RAM the main DAWs state. Also Seat 7's request: the Mac base RAM and the Live 12 and Logic minimums.
- **D-T4 (a), K9:** RQ2, per-instance memory of comparable plugins. Also Seat 7 (Altiverb, Spat), Seat 4 (dearVR, Anaglyph, IEM) and Seat 2 (shipped engines).
- **D-T4 (a), K10:** RQ3, instances per project. Also Seat 8's Izhaki claim and Seat 3's request.
- **D-T4 (c), K11:** RQ4, host and validator timeouts. Also Seat 5's pluginval claims.
- **D-T4 (c), K12:** RQ5, response-time limits. Also the Seat 6 and Seat 8 requests, and Seat 1's Table 15.1 standing.
- **D-T5 (3), K7:** RQ6, audibility of late-field anisotropy. Also requests from Seats 1, 2, 3, 6, 8 and 9.

## 2. Findings

Columns: id | question | finding (value and conditions, N where statistical) | reference | location | read/unverified | confidence | what it changes.

**RQ1: RAM in producers' machines and the DAWs' stated RAM**

- **F1 | RQ1 | Live 12.** Minimum 8 GB RAM on both macOS (11+, Intel i5 or Apple Silicon) and Windows (10/11 22H2+, AVX2). No recommended value on this page. | Ableton, "Start your free trial" (Live 12 system requirements), https://www.ableton.com/en/trial/ | "System Requirements" block | read | H | Sets the floor for the smallest supported host.
- **F2 | RQ1 | Ableton help centre.** A help-centre page reportedly recommends 16 GB for typical production and 32 GB or more for large projects. | help.ableton.com article 209775305 (HTTP 403) | – | unverified (search summary only) | L | Do not rely on it.
- **F3 | RQ1 | Logic Pro.** The official pages state no RAM figure. Support page: "Logic Pro for Mac 13.0" requires macOS 26.1 or later and Apple silicon (published 5 Nov 2026). The marketing specs page says macOS 15.6 or later and Apple silicon. | Apple Support 125029, https://support.apple.com/125029 ; https://www.apple.com/logic-pro/specs/ | specs section | read | H | Logic gives no RAM anchor. The two OS figures conflict (see §4).
- **F4 | RQ1 | FL Studio.** Minimum 4 GB RAM and 4 GB disk; Windows 10/11 (not ARM), macOS 10.15.7+. Version label blank on the page. | Image-Line, https://www.image-line.com/fl-studio/download | requirements block | read | H | The lowest stated floor among the DAWs.
- **F5 | RQ1 | REAPER.** No RAM requirement stated, only OS support (Windows XP–11, macOS 10.5–26). Version 7.85, dated 5 Nov 2026. | https://www.reaper.fm/download.php | download page | read | H | No anchor.
- **F6 | RQ1 | Cubase 15 and Studio One Pro 7.** Retailers list 8 GB minimum (Studio One: 16 GB recommended). I could not retrieve the vendor pages: steinberg.net returned 404 or no content, presonus.com returned 404. | retailer listings only | – | unverified | L | Treat as unknown from the vendors.
- **F7 | RQ1 | Mac base RAM (Seat 7).** Apple announced on 30 Oct 2024 that the M4 MacBook Pro starts at 16 GB unified memory and that the M2/M3 MacBook Air "double the starting memory to 16GB". iMac and Mac mini are not covered by this release. | Apple Newsroom, 30 Oct 2024, https://www.apple.com/newsroom/2024/10/new-macbook-pro-features-m4-family-of-chips-and-apple-intelligence/ | body text | read | H | New Macs sold since Nov 2024 have at least 16 GB. Older installed machines may have 8 GB.
- **F8 | RQ1 | Steam survey (gamers, not producers).** October 2026 system RAM: 16 GB 41.42%, 32 GB 37.06%, 8 GB 7.52%, 64 GB 3.94%. OS: Windows 93.70%, OSX 2.35%. Opt-in, anonymous; N not stated. | Valve, Steam Hardware & Software Survey, https://store.steampowered.com/hwsurvey/ | System RAM table | read | M (ill-informed: wrong population, macOS almost absent) | At most a proxy for Windows desktop RAM. It is not a producer base rate.
- **F9 | RQ1 | Producer OS split (no RAM data).** Avanzini et al. 2025, web survey Dec 2023–Jan 2024, N=613, 57.6% from Italy, 29.5% recruited via SMC mailing lists. Most DAWs' user bases are split about equally between macOS and Windows. Exceptions: FL Studio 83% Windows, Cubase 76% Windows, Pro Tools 14% Windows. No hardware or RAM questions were asked (Table 2). | F. Avanzini, R. Della Longa, D. Fantini, L.A. Ludovico, G. Presti, "A Study on the Adoption and Usage of Digital Audio Workstations", Proc. 22nd SMC 2025, Graz, pp. 136–143 (CC BY 3.0); data DOI 10.13130/RD_UNIMI/YNQHKI; PDF https://avanzini.di.unimi.it/downloads/publications/avanzini_smc25.pdf | §4.1, §4.4, Table 3 | read | M (the authors flag the small, Italy-heavy sample) | Supports "both platforms matter equally". Says nothing about RAM.

**RQ2: per-instance memory of comparable plugins**

- **F10 | RQ2 | Spat Revolution.** System RAM: 16 GB minimum, 32 GB preferred when the DAW and Spat run on one machine (local audio path); 32–64 GB for a dedicated live machine. No per-room or per-source memory figures. Docs labelled "SPAT Revolution 26.04". | FLUX::, "Appendix B — SPAT Revolution specifications", https://doc.flux.audio/spat-revolution/Appendix_A.html | generic spec tables | read | H | A whole-system requirement, not a per-instance figure.
- **F11 | RQ2 | Seventh Heaven.** "At least 8 GB of main memory". Fusion-IR (modulated convolution), captures sampled at 96 kHz, decay 0.2–30 s. No per-instance figure. | LiquidSonics, https://www.liquidsonics.com/software/seventh-heaven/ | requirements | read | H | No per-instance anchor.
- **F12 | RQ2 | Altiverb 8.** No RAM requirement and no per-instance memory figure. Core IR set about 8 GB on disk; Regular edition up to 96 kHz, XL up to 384 kHz. I read only the first 100k characters of the page. | Audio Ease, https://www.audioease.com/altiverb/ | product page | read (partial) | M | No anchor.
- **F13 | RQ2 | Steam Audio.** Longer baked IRs (`savedDuration`) increase disk use and run-time memory; longer simulated duration increases memory while baking. No MB figures. | Valve, Steam Audio C API documentation, "Baking", https://valvesoftware.github.io/steam-audio/doc/capi/baking.html | baking parameters | read | H | Qualitative only.
- **F14 | RQ2 | Derived, not sourced.** A time-domain float32 IR needs T × fs × channels × 4 B. Example: 10 s × 96 kHz × 4 channels (true stereo) × 4 B = 15.4 MB. A partitioned FFT convolver also holds the IR spectra, roughly the same size again. | my arithmetic | – | derived | M | Scale only: conventional IR reverbs sit in the tens of MB per instance. This is not a published figure.

**RQ3: instances per project**

- **F15 | RQ3 | Izhaki, qualitative (Seat 8).**
  - In 1971 analog studios, more than eight reverbs counted as reverb-happy and many mixes used no more than five.
  - Modern computers can run up to 100 reverb plugins.
  - For many software mixers, eight reverbs is not lavish.
  - Expert narrative, no N. | corpus `docs/corpus/izhaki-mixing-audio.md` L4804–4808, Ch. 24 "Reverb quantity and allocation" | – | read (corpus) | M | The only base rate available. It is qualitative and partly about analog-era practice.

**RQ4: host and validator timeouts**

- **F16 | RQ4 | pluginval v1.0.4 default timeout.** Default `--timeout-ms` is 30000 ms; "-1" disables it. Default strictness is 5, clamped to 1–10. This repo sets 120000 ms (`tools/ci/run_pluginval.sh` L19). | Tracktion/pluginval tag v1.0.4, `Source/CommandLine.cpp`, https://raw.githubusercontent.com/Tracktion/pluginval/v1.0.4/Source/CommandLine.cpp | option parsing, help text | read | H | CI is 4× more lenient than a user's default run.
- **F17 | RQ4 | How the pluginval timeout works.**
  - It is an inactivity watchdog, not a per-test limit.
  - A thread polls every 200 ms. Any log message or result update pushes the deadline back by timeoutMs.
  - On expiry it logs "FAILED: Timeout" and terminates the process.
  - It covers the whole validation of one plugin. | same repo, `Source/Validator.cpp` (PluginsUnitTestRunner), https://raw.githubusercontent.com/Tracktion/pluginval/v1.0.4/Source/Validator.cpp | runner class | read | H | The binding quantity is the longest stretch with no output, not a per-test total.
- **F18 | RQ4 | pluginval tests that restore state or prepare.**
  - "Plugin state" (level 2): setStateInformation called once.
  - "Plugin state restoration" (level 6): setStateInformation called once per non-bypass automatable parameter, with no explicit log inside the loop.
  - "Background thread state" (level 7): one restore, then a 2000 ms sleep.
  - "Audio processing" (level 3): prepareToPlay for each sample rate and block size, 10 blocks each.
  - "Fuzz parameters" (level 6): 5 iterations per parameter; no state restore or prepare.
  - "auval" test (level 5): run with `-stress 20` above strictness 5. | same repo, `Source/tests/BasicTests.cpp`, `Source/tests/ParameterFuzzTests.cpp` (v1.0.4) | test classes | read via fetch summaries of the source | M–H | If a restore is slow and silent, the stretch at risk is about N_automatable_params × t_restore, compared against the timeout.
- **F19 | RQ4 | auval.**
  - auval tests cold and warm open times. Apple: opening time "should be kept to a minimum because it impacts the launch time … usability of host applications".
  - No numeric limit or timeout is documented for open, Initialize, ClassInfo restore or render.
  - The note was last updated 2008-09-08 and is no longer being updated. | Apple, Technical Note TN2204 "Audio Unit Validation Using the auval Tool", https://developer.apple.com/library/mac/technotes/tn2204/_index.html | open-times and persistence sections | read | H | No documented auval timeout.
- **F20 | RQ4 | DAW scanners and offline bounce.**
  - I found no vendor documentation of time limits for Logic AU hosting, Ableton or Cubase scanning, a slow setStateInformation or prepareToPlay, or a slow offline bounce.
  - JUCE documents only that `isNonRealtime()` is false when run live and is unreliable before prepareToPlay. | JUCE AudioProcessor class reference, https://docs.juce.com/master/classAudioProcessor.html | isNonRealtime / setNonRealtime | read | H (that no documentation was found) | Any 4c-2 limit cannot be anchored to a documented host timeout.

**RQ5: response-time limits**

- **F21 | RQ5 | Card, Robertson & Mackinlay 1991.**
  - Table 3 "Human time constants": perceptual processing 0.1 s [ref 5: Card, Moran & Newell 1983]; immediate response 1 s [ref 21: Newell 1990]; unit task 10 s, range 5–30 s [5, 21].
  - Conditions: a visual interactive information workspace (3D/Rooms, animation). The constants are cited from cognitive psychology, not measured in this paper.
  - Design rule: agents give status feedback at intervals of no more than about 1 s. | S.K. Card, G.G. Robertson, J.D. Mackinlay, "The Information Visualizer, an Information Workspace", Proc. CHI '91, ACM, pp. 181–188 as printed, doi:10.1145/108844.108874; PDF https://courses.ischool.berkeley.edu/i213/s99/Readings/p181-card.pdf | p. 185, Table 3 and the three paragraphs after it | read | H | A citable 1 s / 10 s anchor. Conditions: visual UI, not hearing the result of an edit.
- **F22 | RQ5 | Nielsen 1993.**
  - 0.1 s feels instantaneous; 1 s keeps flow of thought; 10 s keeps attention.
  - Beyond 10 s, give completion feedback.
  - Cites Miller 1968 and Card et al. 1991. | J. Nielsen, *Usability Engineering*, Academic Press 1993, ch. 5. Seen only in the author's web excerpt, https://www.nngroup.com/articles/response-times-3-important-limits/ | ch. 5 per the excerpt; page not known | unverified (the book was not retrieved) | M | Same limits as Card. Cite Card (F21) as the read source.
- **F23 | RQ5 | Miller 1968.** Bibliographic record confirmed: R.B. Miller, "Response time in man-computer conversational transactions", AFIPS '68 Fall Joint Computer Conference, part I, pp. 267–277, doi:10.1145/1476589.1476628. I could not read the content: ACM returned 403, a mirror returned 503 twice, and the bitsavers volume is 81 MB. | Crossref record https://api.crossref.org/works/10.1145/1476589.1476628 | – | citation read; content unverified | – | Do not cite Miller for any number.
- **F24 | RQ5 | Vorländer Table 15.1 (corpus).**
  - 700 ms for translational movement > 0.25 m; 3 s for > 1 m (specular plus scattering part).
  - Labelled a "proposal" after Lentz et al. 2007.
  - Derived from VR movement speeds of 30–50 cm/s.
  - Lentz 2007 itself not retrieved. | corpus `vorlaender-auralization.md` L3957–3966, §15.3 | – | read (corpus) | M | Confirms Seat 1: a derived budget, not a measured lag threshold.

**RQ6: audibility of late-field anisotropy**

- **F25 | RQ6 | Meyer-Kahlen et al. 2021: closest to the product's conditions.**
  - Room and anisotropy: measured room "Arni", 8.71×6.81×3.6 m, T30 ≈ 0.62 s, absorbing panels on one half-wall. Directional differences in the late field reached about 12 dB (80–400 ms).
  - Rendering: binaural over headphones, via the loudspeaker responses convolved with KEMAR diffuse-field-equalized HRIRs (non-individual). Head tracking is not mentioned in the pages I read.
  - Listeners: N=9 experienced, at home, on different high-quality headphones.
  - Comparison: estimated late directions vs uniformly random directions from 80 ms.
  - Kick drum: significant difference in spatial impression (Wilcoxon p = 0.0078).
  - Speech: no significant differences.
  - The authors say audibility appears "only under best-case conditions" and is expected to fall in more regular rooms. | N. Meyer-Kahlen, S.J. Schlecht, T. Lokki, "Parametric Late Reverberation from Broadband Directional Estimates", 2021 Immersive and 3D Audio (I3DA), IEEE, art. 9610928, pp. 1–10, doi:10.1109/I3DA48870.2021.9610928; accepted manuscript https://acris.aalto.fi/ws/portalfiles/portal/76399639/Meyer_Kahlen_Parametric_late_reverberation.pdf | §III-D, §V, Figs. 4, 5, 8, 9; §VI | read | M (small N; extreme case) | 5.3-C has one perceptual basis under near-product conditions, limited to transients and extreme anisotropy.
- **F26 | RQ6 | Alary et al. 2021: loudspeakers, rotation task.**
  - Setup: 4th-order Ambisonics on 37 loudspeakers in an anechoic chamber. 16 expert audio researchers (18 recruited, 2 discarded). BS.1116-style task: reference plus two blind stimuli.
  - Comparison: the late part (after t_mix) rotated by 135° vs unrotated. This is not anisotropic vs isotropic.
  - Identification rates (read from Fig. 12): Athénée ≈97%, Kunsthalle ≈72%, Staatstheater ≈68%, Saint-Eustache ≈53% (not significant), isotropic control ≈52%. 95% line for M=160 trials ≈58%.
  - Interaural energy-decay deviation (IEDD) of 1.1 dB around 850 Hz (computed with SPARTA default HRTFs) was enough to detect the rotation.
  - Trumpet, voice, percussion, guitar and pink impulse showed no significant differences between stimuli. | B. Alary, P. Massé, S.J. Schlecht, M. Noisternig, V. Välimäki, "Perceptual analysis of directional late reverberation", JASA 149(5):3189–3199, 2021, doi:10.1121/10.0004770 (CC BY); https://acris.aalto.fi/ws/portalfiles/portal/63240868/3189_1.pdf | §IV A–H, Figs. 6, 12, 13; §V | read | H for its own conditions (ill-informed for headphones, generic HRTF, simulated rooms) | Directional late decay deviations of about 1 dB are detectable by experts over loudspeakers.
- **F27 | RQ6 | Seeber et al. 2025: "open window" gap.**
  - Setup: 36 loudspeakers on a horizontal ring (10° spacing), anechoic, direct sound at 0°. N=8.
  - Task: 3-interval 2AFC, adaptive 3-down 1-up. Stimuli: pink-noise burst trains (70 dB SPL) and one word (60 dB SPL).
  - Gap thresholds (median, pooled): 90° when the gap is at 0°; 37.5° when it is at 90°.
  - At 90°, mean threshold falls from 52.1° to 42.6° to 34.1° for RT60 0.4, 1.3 and 2.2 s (significant). DRR effect not significant.
  - About a quarter of thresholds were 20° or less. | B.U. Seeber, P. Weymar, S.D. Ewert, S. van de Par, "Perceptual sensitivity to the 'open window' in reverberation", Forum Acusticum/EuroNoise 2025, Málaga, pp. 6473–6476, doi:10.61782/fa.2025.0679 (CC BY 3.0); https://dael.euracoustics.org/confs/fa2025/data/articles/000679.pdf | §2–4, Figs. 1–3 | read | M (N=8; loudspeakers) | A fully absorbing face is detectable when lateral and wide (≳35°), hard to detect when it lies in the direction of the direct sound.
- **F28 | RQ6 | Kirsch et al. 2021 (preprint read).**
  - Setup: 86-loudspeaker spherical array with VBAP. Experiment 2: corridor 24×8×6 m with one end wall α = 0.99 and the rest α 0.01–0.11 (RT60 1.3–0.8 s). N=10. ABX against a 96-source anisotropic reference.
  - Results: 6 sources were distinguished for all stimuli except mixed speech. 12–24 sources were sufficient for the pink pulse. Mixed speech was near chance with 12 or more sources.
  - It compares resolutions of an anisotropic field, not anisotropic vs isotropic. | C. Kirsch, J. Poppitz, T. Wendt, S. van de Par, S.D. Ewert, "Spatial resolution of late reverberation in virtual acoustic environments", arXiv:2106.15888 (submitted to Trends in Hearing; Seeber 2025 cites it as Trends in Hearing 25, 2021) | preprint pp. 7–8, 14–17, Fig. 4 | read (preprint) | M | A coarse rendering of an absorbing wall is audible with transients; fine resolution matters little for running speech.
- **F29 | RQ6 | Romblom et al. 2016.** ABX on a 28-loudspeaker semi-sphere. Thresholds relative to an ideal diffuse field: −2.5 dB lateral, −6.8 dB height, −3.2 dB frontal. Level differences near these occur in real spaces. | D. Romblom, C. Guastavino, P. Depalle, "Perceptual thresholds for non-ideal diffuse field reverberation", JASA 140(5):3908–3916, 2016, doi:10.1121/1.4967523 | abstract (via Crossref) | unverified (abstract only) | M | Points to lower sensitivity to height anisotropy (bears on Seat 1's vertical-floor hypothesis).
- **F30 | RQ6 | Ahrens 2019.** In a binaural user study, arrival directions drawn from random data were "nearly indistinguishable" from the original SDM data. Which part of the IR was randomised, the listeners and head tracking are not stated on the record page. | J. Ahrens, "Auralization of Omnidirectional Room Impulse Responses Based on the Spatial Decomposition Method and Synthetic Spatial Data", ICASSP 2019, pp. 146–150, doi:10.1109/ICASSP.2019.8683661 | Chalmers record https://research.chalmers.se/en/publication/513269 | unverified (abstract) | L–M | Counter-evidence for non-extreme rooms.
- **F31 | RQ6 | Lindau et al. 2012.** Generic diffuse late reverberation can replace the room-specific part after the perceptual mixing time. 9 rooms, expert listeners; V/S and echo density predict that time. | A. Lindau, L. Kosanke, S. Weinzierl, "Perceptual Evaluation of Model- and Signal-Based Predictors of the Mixing Time in Binaural Room Impulse Responses", JAES 60(11):887–898, 2012; repository record https://depositonce.tu-berlin.de/handle/11303/16460 | abstract | unverified (abstract only; method not read) | M | Supports an isotropic tail after t_mix in binaural rendering.
- **F32 | RQ6 | Corpus anchors.**
  - Vorländer §15.3, citing Meesawat & Hammershøi 2003: after 140 ms the receiver-specific reverberation can be replaced by a statistical decay.
  - Toole Fig. 15.8 (Hiyama et al. 2002): too few loudspeaker directions degrade envelopment against a 24-loudspeaker diffuse reference. Loudspeaker reproduction, not binaural. | corpus `vorlaender-auralization.md` L3956; `toole-sound-reproduction.md` L2449–2469 | – | read (corpus) | M | Corpus support for an isotropic tail. The primary for the 140 ms value was not retrieved (see §4).

## 3. Not found / unresolved
- **RQ1, producer RAM distribution.** I searched "survey music producers RAM", "DAW users hardware survey" and the MIDiA and LIM DAW surveys. None reports RAM with a stated method. Avanzini 2025 asked no hardware questions. MIDiA's 2025 creator survey (n=2,109) is paywalled and its hardware content is unknown. What would settle it: a DAW vendor or survey publication reporting RAM with N and method.
- **RQ1, Cubase 15 and Studio One Pro 7 vendor pages.** steinberg.net returned 404 or a page with no requirements; presonus.com returned 404. Values exist only from retailers.
- **RQ2, per-instance memory** (Altiverb, Spat, dearVR PRO, Anaglyph, Steam Audio, Seventh Heaven, Space Designer, IEM). None of the vendor pages I retrieved publishes it. dearVR, Anaglyph and Space Designer searches returned nothing relevant. What would settle it: our own RSS measurement under stated conditions (IR length, sample rate), which is in-repo work, not literature.
- **Seat 2's request (memory of shipped acoustics engines in large scenes, against patch count).** Steam Audio docs are qualitative only. Project Acoustics, Wwise Reflect, RAVEN and Odeon were not researched.
- **RQ3, counted instances per project.** No project-file analysis exists that I could find. De Man et al. 2015 (AES Convention Paper 9235, read pp. 1–4) has no plugin counts. De Man's 2017 QMUL thesis is a lead I did not read.
- **RQ4, DAW time limits.** I found no Apple, Ableton or Steinberg documentation of time limits for setState, prepare, scan or offline render. The Steinberg forum reports a timeout in Dorico's scanner, but that is a forum post and not evidence.
- **RQ5, Miller 1968 content** (access blocked) and the Nielsen 1993 book text. I found no study of edit-to-hear delay where the result is heard rather than seen (Seat 6). I found none on audio-visual asynchrony for continuous spatial changes (Seat 1). Lentz et al. 2007's basis for Table 15.1 was not retrieved.
- **RQ6 under the product's exact conditions.** No study combines music, producers, a generic HRTF without head tracking and simulated concentrated absorption with an isotropic control. Penot, Green & Jurkiewicz (Proc. IoA 47 Pt 1, 2025) is relevant: binaural, anisotropic vs isotropic late energy. Its PDF and record both returned 404, so it is unverified. Also not found: Seat 8's request (anisotropy as a distance or envelopment cue in music) and Seat 1's "Lübeck 2022" claim, which I did not check.
- **Out of scope of RQ1–RQ6 and not researched:** Seat 9's venue dimensions and its cathedral/arena IR databases; Seat 5's denormal base rate; Seat 2's measured outdoor ground IRs.

## 4. Conflicts between sources
- **Logic Pro minimum OS:** apple.com/logic-pro/specs says macOS 15.6 or later; support.apple.com/125029 says macOS 26.1 or later for Logic Pro 13.0 (5 Nov 2026). Neither states RAM.
- **When a binaural tail becomes position-independent:** the corpus (Vorländer §15.3) gives 140 ms after Meesawat & Hammershøi 2003 (AES Conv. Paper 5859). A search summary of the AES abstract gives about 40–60 ms with a 3-AFC test and 4 listeners. The AES pages returned 403, so the second value is unverified. Both concern swapping tails between positions and directions, not anisotropy.
- **Audibility of late directions:** Ahrens 2019 (F30, abstract) found random late directions nearly indistinguishable. Meyer-Kahlen 2021 (F25, read) found a significant difference for a kick drum and none for speech. The conditions differ: an extreme absorbing wall and a transient in F25.
- **Card 1991 page range:** printed pp. 181–188 (read) vs DBLP 181–186.

## 5. Seat claims screened
- **Seat 5:** "pluginval's own default is 30 s; CI is ~4× more lenient." **Confirmed** (F16; repo L19 = 120000).
- **Seat 5:** "per-test timeout", and a bound of "default per-test timeout ÷ number of restores". **Corrected.** The timeout is an inactivity watchdog over the whole run, reset by any output (F17). The restore loop runs once per non-bypass automatable parameter with no explicit log inside it (F18). The quantity to bound is the longest silent stretch.
- **Seat 7:** "Mac base RAM went to 16 GB in late 2024." **Confirmed** for MacBook Air and MacBook Pro (F7). iMac and Mac mini were not checked.
- **Seat 7:** Live 12 and Logic minimums. **Confirmed/clarified.** Live 12: 8 GB (F1). Logic: no RAM stated (F3).
- **Seat 8:** Izhaki, "eight reverbs not lavish; many mixes use five or fewer; up to 100". **Confirmed, with a condition.** "Five or fewer" describes 1971 analog practice. The statement is qualitative, with no N (F15).
- **Seat 1:** Table 15.1 is a "proposal", a derived budget. **Confirmed** (F24, corpus L3959).
- **Seat 1:** Meesawat & Hammershøi, 140 ms. **Confirmed as printed in the corpus.** The primary was not retrieved, and a conflicting value exists (§4).
- **Seat 1:** "anisotropy from floor absorption is mostly vertical; elevation is what a generic HRTF renders worst" [Hyp]. **Unverifiable** as stated. Related evidence: Romblom 2016 reports a higher (less sensitive) height threshold, −6.8 dB vs −2.5 dB lateral, over loudspeakers and from the abstract only (F29).
- **Seat 1:** "Lübeck 2022 order 4–5 for the late part, an authenticity test, head-tracked". **Not checked.**
- **Seat 3:** "No evidence yet that the anisotropy is audible." **Corrected.** Detection evidence exists (F25–F29). Only F25 is binaural with a generic HRTF, and only for a transient in an extreme case.
- **Seat 9:** "late-field anisotropy has no JND-crossing case". **Corrected/qualified,** as for Seat 3: crossings exist in lab conditions. None was tested with music under the product's conditions, apart from F25's kick drum.
- **Seat 6:** "Altiverb's IR switch clicked and took 50–200 ms" (ASFX16, a 2016 interview). **Unverifiable.** The source is a press interview and I could not retrieve the passage. It is not evidence under the rules.

## 6. Corpus candidates (named only; adding them is Maisara's call)
- Alary et al. 2021, JASA 149(5) (CC BY).
- Meyer-Kahlen, Schlecht, Lokki 2021, I3DA (Aalto accepted manuscript).
- Seeber et al. 2025, Forum Acusticum (CC BY 3.0).
- Kirsch et al. 2021, Trends in Hearing 25 (open access).
- Romblom, Guastavino, Depalle 2016, JASA 140(5).
- Card, Robertson, Mackinlay 1991, CHI.
- Avanzini et al. 2025, SMC (CC BY 3.0).

## 7. Readiness by decision

**D-T4**

| row | status |
|---|---|
| K8 (customer RAM) | Partly known: DAW floors F1, F3–F5 (Live 8 GB, FL 4 GB, Logic and REAPER none); new Macs ≥ 16 GB (F7). The producer RAM distribution is **uninformed (no source exists)**. Steam (F8) is ill-informed: the population is gamers. |
| K9 (comparable plugins) | **Uninformed.** No published per-instance figure. Only system RAM recommendations (F10, F11) and a derived scale (F14). |
| K10 (instances per project) | **Uninformed** as a count. Qualitative only (F15). |
| K11 (timeouts) | **Known** for pluginval (F16–F18) and auval (F19, which documents no limit). No DAW limit is documented (F20). |
| K12 (wait limits) | **Known with conditions** (F21; F24 from the corpus). Nielsen and Miller are unverified (F22, F23). All are visual-UI or VR-derived, so ill-informed for "heard" edits. |

Verdict: **NOT READY.** K8, K9 and K10 cannot be closed from credible sources. The decider must treat them as declared unknowns, or have them measured in-repo.

**D-T5 (3)**

| row | status |
|---|---|
| K7 (late-field anisotropy) | **Known, with conditions that differ.** F25 is the only binaural, generic-HRTF result: audible for a kick drum in an extreme absorbing-wall case, N=9; not for speech. F26–F28 come from loudspeakers or other tasks. F30 and F31 (abstracts) point the other way. |
| K5 | Unaffected (from the code). |

Verdict: **READY.** The state of the evidence is now known, including the gap that no study matches the product's conditions.
