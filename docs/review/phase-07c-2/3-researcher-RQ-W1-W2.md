<!-- Saved by the orchestrator from the researcher's report, 2026-11-22. -->

# Researcher dossier: phase 07c-2, RQ-W1-1, RQ-W1-2, RQ-W2-1 to RQ-W2-5

Corpus revision: `docs/corpus/SOURCE_COMMIT` = c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. Accessed 2026-11-22.

I had no shell, so I did the binomial arithmetic by hand. The working is shown and cross-checked with logarithms. Every "read" source was fetched and read during this task. "Unverified" means I saw only a search abstract or a citation in another work.

**Verdicts:** D-W1 is **NOT READY** on RQ-W1-1 and RQ-W1-2. D-W2 is **READY** on RQ-W2-1, RQ-W2-2 and RQ-W2-5, and **NOT READY** on RQ-W2-3 and on part of RQ-W2-4. Details are in §7.

## 1. Decisions served and questions examined

- **D-W1, K13 / RQ-W1-1.** What a host does when an offline render or freeze is slower than real time.
- **D-W1, K14 / RQ-W1-2.** Base rates of physical core counts.
- **D-W1, K9 (added, corpus now present).** The conditions of the Table 15.1 rows: 700 ms and 3 s.
- **D-W2, K21 / interrogator file 16 row DC-06.** Re-checked P(X ≥ 12 | 16, ½).
- **D-W2, K22 / RQ-W2-1.** FWER under Bonferroni, fixed-sequence and Holm, with exact thresholds at n = 16.
- **D-W2, K23 / RQ-W2-2.** Power of 16-trial tests, and the Leventhal literature.
- **D-W2, K24 / RQ-W2-3.** Level-step thresholds. The corpus was read first, then outside sources.
- **D-W2, K25 / RQ-W2-4.** Speech sources and their licences.
- **D-W2, K26 / RQ-W2-5.** What ITU-R BS.1116-3 says about design.

## 2. Findings table

### 2a. RQ-W2-1 and RQ-W2-2: exact binomial numbers (computed)

**Null distribution X ~ Bin(16, ½), total 2^16 = 65 536.**
- C(16,k) for k = 16…10: 1, 16, 120, 560, 1820, 4368, 8008.
- Upper tails P(X ≥ c):
  - c = 16: 1/65536 = 0.0000153
  - c = 15: 17/65536 = 0.000259
  - c = 14: 137/65536 = 0.002090
  - c = 13: 697/65536 = 0.010635
  - c = 12: 2517/65536 = 0.038406
  - c = 11: 6885/65536 = 0.105057
  - c = 10: 14893/65536 = 0.227249

**Per-test threshold at family α = 0.05 (one-sided).** The smallest c with P(X ≥ c) ≤ the per-test level:

| procedure | k = 2 | k = 4 | k = 6 |
|---|---|---|---|
| Bonferroni (α/k = 0.025 / 0.0125 / 0.00833) | 13/16 (attained 0.01064 per test) | 13/16 (0.01064) | 14/16 (0.00209) |
| Šidák, 1−0.95^(1/k) = 0.02532 / 0.01274 / 0.00851 | 13/16 | 13/16 | 14/16 (same as Bonferroni at n = 16) |
| Holm, step thresholds α/k, α/(k−1), …, α | 13, then 12 | 13, 13, 13, then 12 | 14, 14 (α/5 = 0.01 < 0.01064), 13, 13, 13, then 12 |
| Fixed sequence (each at α, stop at first non-rejection) | 12 at every step | 12 at every step | 12 at every step |

**Family-wise error under the global null.** The k tests use separate trial sets, so I treat them as independent.
- Bonferroni and Holm:
  - k = 2: 1 − (1 − 0.010635)² = 0.02116 (bound 2 × 0.010635 = 0.02127).
  - k = 4: 1 − 0.989365⁴ = 0.04187 (bound 0.04254).
  - k = 6: 1 − (1 − 0.0020905)⁶ = 0.01248 (bound 0.01254).
  - Holm's global-null FWER equals its first step, so it is the same as Bonferroni here.
  - Discreteness makes both conservative at k = 6: 0.0125 attained against 0.05 nominal.
- Fixed sequence: the global-null FWER is P(first test rejects) = 0.03841 exactly, for every k.
- **No correction, X-1 at 12/16 on each of {noise, speech}:** 1 − (1 − 0.038406)² = 0.07534 (bound 0.07681). This confirms DC-06's concern.

**Power P(X ≥ c | 16, p) at true proportion correct p.**

Terms used:
- p = 0.75: P16 = 0.010023, P15 = 0.053454, P14 = 0.133635, P13 = 0.207876, P12 = 0.225200.
- p = 0.85: P16 = 0.074251, P15 = 0.209650, P14 = 0.277478, P13 = 0.228511, P12 = 0.131058.
- p = 0.65: P16 = 0.001015, P15 = 0.008748, P14 = 0.035327, P13 = 0.088770, P12 = 0.155347.
- p = 0.95: P16 = 0.440127, P15 = 0.370633, P14 = 0.146302, P13 = 0.035934, P12 = 0.006147.

| true p | ≥ 12/16 | ≥ 13/16 | ≥ 14/16 |
|---|---|---|---|
| 0.50 (null) | 0.0384 | 0.0106 | 0.0021 |
| 0.65 | 0.2892 | 0.1339 | 0.0451 |
| 0.75 | 0.6302 | 0.4050 | 0.1971 |
| 0.85 | 0.9209 | 0.7899 | 0.5614 |
| 0.95 | 0.9991 | 0.9930 | 0.9571 |

Derived reading: at p = 0.75 a 16-trial test at 12/16 misses a real effect with probability 0.37. At 13/16 (the Bonferroni threshold for 2 or 4 tests) it misses with probability 0.60.

Under the X-3 fixed sequence, power at step j is the probability that steps 1…j all reject. That is a product of the per-step powers above when the steps use independent trials.

**Not sourced, flagged as a model assumption:** "p = 0.75 means the step is truly heard on 50 % of trials" holds only under a high-threshold guessing model, p = ½ + ½d. I found no source for it in this task.

### 2b. Main findings

**R1. Fixed-sequence, Holm and Bonferroni procedures (RQ-W2-1)**
- **Question:** Do the procedures control FWER?
- **Finding:**
  - Bonferroni is single-step at α/m.
  - Holm is step-down at α/m, α/(m−1), …, α. It stops at the first non-significant result and is valid "with any degree of correlation".
  - Bonferroni and Holm are "assumption-free"; Hochberg is not.
  - Fixed sequence tests in a prespecified order, all at the same α, and stops at the first failure. It needs no α adjustment.
  - If the fixed-sequence order is ignored after a failure, the Type I error rate is inflated.
- **Reference:** U.S. FDA (CDER/CBER), *Multiple Endpoints in Clinical Trials: Guidance for Industry*, October 2022. https://www.fda.gov/media/162416/download
- **Location:** Appendix, §1 Bonferroni (p. 18, l. 117–134); §2 Holm (pp. 18–19, l. 136–166); l. 188–190; §5 Fixed-Sequence (pp. 20–21, l. 223–248).
- **Read/unverified:** Read.
- **Confidence:** High. This is regulatory guidance, not peer-reviewed.
- **What it changes for the decider:** X-3 (fixed sequence) holds at α with no per-test adjustment, provided the order and the stop rule are pre-registered. X-2 needs 13/16 or 14/16.

**R2. Primary sources for the same procedures (RQ-W2-1)**
- **Finding:**
  - Goeman & Solari show that Holm and other procedures are special cases of a sequential rejection principle with strong FWER control.
  - Westfall & Krishen show that fixed-sequence and gatekeeper methods are limits of weighted closed (Holm-type) tests.
- **References:**
  - Goeman, J.J. & Solari, A. (2010), "The sequential rejection principle of familywise error control", *Ann. Stat.* 38(6), 3782–3810. doi:10.1214/10-AOS829 (arXiv 1211.3313).
  - Westfall, P.H. & Krishen, A. (2001), *J. Stat. Plan. Inference* 99, 25–40. doi:10.1016/S0378-3758(01)00077-5.
- **Location:** Abstracts.
- **Read/unverified:** Goeman & Solari abstract read. **Westfall & Krishen unverified** (search abstract only).
- **Confidence:** Medium.
- **What it changes for the decider:** These are corroborating primary sources for R1.

**R3. Leventhal 1986 (RQ-W2-2)**
- **Finding:** A small number of trials or listeners gives a high risk of a type 2 error, that is, of concluding "inaudible". The paper gives tables of type 1 and type 2 risk.
- **References:**
  - Leventhal, L. (1986), "Type 1 and Type 2 Errors in the Statistical Analysis of Listening Tests", *JAES* 34(6), 437–453.
  - A correction appeared in 1986 (AES e-lib 5247).
  - Comments by Shanefield, Clark and Nousaine, with Leventhal's replies, appeared in *JAES* 35(7/8), 567–572 (1987).
- **Location:** Abstract.
- **Read/unverified:** **Unverified.** aes.org returned 403; I saw only search-engine abstracts.
- **Confidence:** Low.
- **What it changes for the decider:** It frames the "16 trials cannot support 'not detected'" argument. The numbers in §2a stand on their own without it.

**R4. ITU-R BS.1116-3 (RQ-W2-5)**
- **Finding:**
  - Method: "double-blind triple-stimulus with hidden reference". One subject at a time, with a continuous five-grade impairment scale (§4, Table 1).
  - Panel: experts only (§3.1). Data from 20 subjects is "often sufficient" under tight control. More subjects are needed if systems are near-transparent, and the result is valid only for the listeners actually tested (§3.3).
  - Training: a familiarization phase is mandatory (§4.1).
  - Sessions: 20–30 min, with no more than 10–15 trials per session (§4.2).
  - Switching: near-instantaneous switching with about 40 ms fade-down/change-over/fade-up is preferred (§4.2 Note 1).
  - Null findings: a "null" finding is valid only once it has been shown statistically not to be due to insensitivity. Anchors of known detectability are recommended to show this (§6).
  - Analysis: ANOVA (§9). There is no "correct" significance level; 0.05 is traditional and one- or two-tailed tests are allowed (§10.4).
  - Post-screening: a per-subject one-sided t-test on difference grades (Attachment 1).
  - ABX and single-listener designs are not mentioned anywhere I read.
- **Reference:** Recommendation ITU-R BS.1116-3 (02/2015), *Methods for the subjective assessment of small impairments in audio systems*. https://www.itu.int/dms_pubrec/itu-r/rec/bs/R-REC-BS.1116-3-201502-I!!PDF-E.pdf
- **Location:** §3.1, 3.3, 4, 4.1, 4.2, 6, 9, 10.4; Attachment 1.
- **Read/unverified:** Read (pp. 1–14, 18–25).
- **Confidence:** High.
- **What it changes for the decider:**
  - A single-listener 16-trial ABX is outside BS.1116's design. Its result holds for that listener only.
  - "Not detected" needs a demonstrated-sensitivity control, such as an anchor step known to be audible.
  - 16 trials per stimulus exceeds BS.1116's 10–15 trials per session.

**R5. Corpus: Vorländer, level and clarity jnd (RQ-W2-3)**
- **Finding:** jnd of G (level) = 1 dB and of C80 = 1 dB, in the 500–1000 Hz range.
- **Reference:** Vorländer, *Auralization* (2008), after Vorländer 1995 and ISO 3382-1.
- **Location:** §6.4.4, Table 6.1.
- **Read/unverified:** Read (corpus).
- **Confidence:** High.
- **What it changes for the decider:** These are differences between room conditions. The table does not give the paradigm or say whether a change within a stream is meant.

**R6. Corpus: Vorländer, 1 dB and the late tail (RQ-W2-3)**
- **Finding:** 1 dB ≈ the jnd (§1.5). Dropping the tail after T/2, which holds 22 % of the energy, makes the total 1 dB too small: a "just audible" difference (§6.4.2).
- **Reference:** Vorländer (2008).
- **Location:** §1.5; §6.4.2.
- **Read/unverified:** Read (corpus).
- **Confidence:** High.
- **What it changes for the decider:** This is the closest corpus statement to a change in tail energy. It concerns total energy and is not a timed step.

**R7. Corpus: Toole, overall loudness change (RQ-W2-3)**
- **Finding:** About 1 dB is the smallest audible change in overall loudness; 3 dB is easily perceived. Toole also says loudness must be very closely matched in comparisons (§17.3.1).
- **Reference:** Toole, *Sound Reproduction* (2008).
- **Location:** §19.1.1; §17.3.1.
- **Read/unverified:** Read (corpus).
- **Confidence:** High.
- **What it changes for the decider:** The paradigm and signal are not stated.

**R8. Corpus: Zotter & Frank, loudness differences in noise (RQ-W2-3)**
- **Finding:** With monophonic noise playback, loudness differences below 0.5 dB are audible. A weak directional fluctuation below 1 dB is normally inaudible (§4.8). Third-octave level differences below 1 dB are inaudible to most listeners (§2.4).
- **Reference:** Zotter & Frank, *Ambisonics* (2019).
- **Location:** §4.8 ("Performance comparison on hemispherical layouts"); §2.4.
- **Read/unverified:** Read (corpus).
- **Confidence:** Medium. The paradigm and N are not given in the corpus text.
- **What it changes for the decider:** This is the only corpus value below 1 dB, and it is for noise. It bears on the 0.5 dB reversal bound.

**R9. Corpus: Kuttruff, reflection level with music (RQ-W2-3)**
- **Finding:** Changes in reflection level of about ±1.5 dB are detectable with music (Reichardt and Schmidt).
- **Reference:** Kuttruff, *Room Acoustics*, 6th ed. (2017).
- **Location:** §7.3.
- **Read/unverified:** Read (corpus).
- **Confidence:** Medium.
- **What it changes for the decider:** This concerns a single reflection, not tail level.

**R10. Corpus: Blauert, Fig 2.83 (RQ-W2-3)**
- **Finding:** Blur is 0.5–1 dB across frequency (Mills 1960: sinusoids, 5 subjects).
- **Reference:** Blauert, *Spatial Hearing*, ch. 2.
- **Location:** Fig 2.83 text.
- **Read/unverified:** Read (corpus).
- **Confidence:** —
- **What it changes for the decider:** **Ill-informed if used.** This is interaural (ILD) lateralization blur, not monaural level. The link to the monaural difference limen is von Békésy's hypothesis, which only some studies support.

**R11. Increment detection on a continuous tone (RQ-W2-3)**
- **Finding:**
  - Stimulus and task: 1 kHz tone, 500 ms increments with 25 ms ramps, 3AFC, adults.
  - An increment on a continuous pedestal is detected better than a gated level difference by 4.9 dB in 10log(ΔI/I).
  - Experiment 2 adult thresholds: −6.2 dB at a 35 dB SPL standard and −10.4 dB at 75 dB SPL.
  - Derived: ΔL = 10log(1+10^(x/10)) gives 0.93 dB and 0.38 dB.
- **Reference:** Buss, E., Hall, J.W. III & Grose, J.H. (2012), "Factors affecting the processing of intensity in school-aged children", *J. Speech Lang. Hear. Res.* 56(1), 71–80. doi:10.1044/1092-4388(2012/12-0008). PMC3911822.
- **Location:** Methods I.B–C; Discussion of Exp. 1 and Exp. 2.
- **Read/unverified:** Read.
- **Confidence:** Medium.
- **What it changes for the decider:** **Ill-informed if transferred directly.** The signal is a tone, not noise, speech or reverberant tail. The increment is transient and returns to the base level; it is not a sustained step. The listeners are trained lab subjects. It does show that a change within an ongoing stream can be detected at sub-dB levels.

**R12. Earlier tone studies cited by Buss et al. (RQ-W2-3)**
- **Finding:** Continuous advantages of 4.2 dB and 4.6 dB, as reported by Buss et al.
- **References:**
  - Green, Nachmias, Kearney & Jeffress (1979), *JASA* 66(4), 1051–1056. doi:10.1121/1.383324.
  - Viemeister & Bacon (1988), *JASA* 84(1), 172–178. doi:10.1121/1.396961.
- **Location:** As cited by Buss et al.
- **Read/unverified:** **Unverified** (cited only).
- **Confidence:** Low.
- **What it changes for the decider:** Corroboration only.

**R13. Short level increases in ongoing music (RQ-W2-3)**
- **Finding:**
  - Conditions: 1 s broadband increases in level inside ongoing music, with 100 ms rise and decay. 5 listeners (acoustics students). Loudspeakers in a studio at Leq 92.6 dB. Detect-and-report task with catch trials.
  - Fresh-ear correct rates, read off Fig. 4 and approximate: 1.5 dB ≈ 29 %, 3 dB ≈ 67 %, 4.5 dB ≈ 85 %, 6 dB ≈ 90 %.
  - The text puts the fresh-ear threshold for a short loudness increase at 2–3 dB.
- **Reference:** Kin, M.J. & Dobrucki, A. (2016), "Perception of Changes in Spectrum and Envelope of Musical Signals vs Auditory Fatigue", *Archives of Acoustics* 41(2), 323–330. doi:10.1515/aoa-2016-0033.
- **Location:** §2 (p. 325); Fig. 4 (p. 327); §4 (p. 328).
- **Read/unverified:** Read.
- **Confidence:** Low–medium. N = 5, the task is not 2AFC, and the values are read off a graph.
- **What it changes for the decider:** This is the only within-stream music data found. The step is transient and broadband, the level is high, and the context is listening fatigue. It is not a sustained step in the tail.

**R14. Host behaviour: VST3 SDK (RQ-W1-1)**
- **Finding:** In kOffline mode, each process call "could be faster than realtime or slower". The kRealtime mode is called at a realtime frequency.
- **Reference:** Steinberg, VST 3 Interfaces, VST 3.8, `Steinberg::Vst::ProcessModes`. https://steinbergmedia.github.io/vst3_doc/vstinterfaces/namespaceSteinberg_1_1Vst.html
- **Location:** ProcessModes enum.
- **Read/unverified:** Read.
- **Confidence:** High.
- **What it changes for the decider:** In VST3, slower-than-real-time offline processing is a mode the API allows, not a fault.

**R15. Host behaviour: Logic Pro (RQ-W1-1)**
- **Finding:** An offline bounce "can perform bounces not possible in real time" that might exceed the computer's processing power. A realtime bounce runs in real time.
- **Reference:** Apple, Logic Pro (Mac) Help, "Bounce a project to an audio file". https://help.apple.com/logicpro/mac/10.2.1/en.lproj/lgcp785a41c3.html
- **Location:** Mode: Offline / Realtime.
- **Read/unverified:** Read. This is the 10.2.1-era page; I could not read the current Logic Pro (Mac) page.
- **Confidence:** Medium.
- **What it changes for the decider:** In Logic, a bounce slower than real time is designed behaviour: a wait, not a break.

**R16. Host behaviour: Cubase Pro 14 (RQ-W1-1)**
- **Finding:** "Realtime Export" takes at least the playback time and is meant for external gear or plug-ins that need it. If the CPU or disk cannot keep up in realtime export, Cubase stops, reduces the number of channels and restarts. The page says nothing about timeouts in non-realtime export.
- **Reference:** Steinberg, Cubase Pro 14.0 Operation Manual, "Export Audio Mixdown Dialog". https://www.steinberg.help/r/cubase-pro/14.0/en/cubase_nuendo/topics/export_audio_mixdown/export_audio_mixdown_options_r.html
- **Location:** "Realtime Export".
- **Read/unverified:** Read.
- **Confidence:** High.
- **What it changes for the decider:** Offline is the default. Nuendo was not checked separately.

**R17. Host behaviour: Ableton Live 12 (RQ-W1-1)**
- **Finding:** Rendering is normally offline. It is real-time only with External Audio Effect or External Instrument devices. "Auto-Restart on drop-outs" applies to real-time renders.
- **Reference:** Ableton, *Live 12 Reference Manual*, "Managing Files and Sets". https://www.ableton.com/en/live-manual/12/managing-files-and-sets/
- **Location:** §5.1.3.5 Real-Time Rendering.
- **Read/unverified:** Read (first 100k characters). Freeze was not covered there.
- **Confidence:** High.
- **What it changes for the decider:** The manual states no timeout for offline renders.

**R18. Host behaviour: Bitwig Studio (RQ-W1-1)**
- **Finding:** "Real-time overrides the standard offline bounce."
- **Reference:** Bitwig Studio User Guide (latest), "Exporting Audio". https://www.bitwig.com/userguide/latest/exporting_audio/
- **Location:** Real-time option.
- **Read/unverified:** Read. The version is not stated on the page.
- **Confidence:** Medium.
- **What it changes for the decider:** Offline is the default; no behaviour for slow renders is stated.

**R19. Host behaviour: FL Studio (RQ-W1-1)**
- **Finding:** Export is a "non-real time process called 'rendering'". There is no real-time export option. VSTs can be told the rendering mode through "Notify about rendering mode".
- **Reference:** Image-Line, FL Studio Online Manual, "Save/Export file formats". https://www.image-line.com/fl-studio-learning/fl-studio-online-manual/html/fformats_save_export.htm
- **Location:** Export section.
- **Read/unverified:** Read. The page's examples refer to FL Studio 2024.
- **Confidence:** Medium.
- **What it changes for the decider:** No timeout is stated.

**R20. Host behaviour: Fender Studio Pro 8.2 (RQ-W1-1)**
- **Finding:** Export can be Automatic, Realtime or Offline. Automatic switches to Realtime when external gear is in the signal path.
- **Reference:** Fender Studio Pro manual (v8.2), "Mixing Down". https://fenderstudiopromanual.fender.com/en/Content/Mixing_Topics/Mixing_Down.htm
- **Location:** Export Mixdown options.
- **Read/unverified:** Read.
- **Confidence:** Medium.
- **What it changes for the decider:** This is Fender's product, built on Studio One. I did not read the PreSonus Studio One manual itself.

**R21. Steam core counts (RQ-W1-2)**
- **Finding:** Steam Hardware & Software Survey, **October 2026**, "Physical CPUs":
  - Windows: 2 cores 2.75 %, 4 cores 11.76 %, 6 cores 28.12 %, 8 cores 28.63 %. **≥ 4 cores = 97.14 %** (100 − 0.02 − 2.75 − 0.09). **≥ 8 cores = 57.05 %** (100 − 42.95).
  - macOS: 2 cores 3.40 %, 4 cores 3.64 %, 6 cores 6.41 %, 8 cores 34.20 %, 10 cores 35.54 %. **≥ 4 cores = 96.59 %**. **≥ 8 cores = 86.54 %** (99.99 − 13.45).
- **Reference:** Valve, Steam Hardware & Software Survey, CPUs. https://store.steampowered.com/hwsurvey/cpus/
- **Location:** Physical CPUs table, per OS.
- **Read/unverified:** Read.
- **Confidence:** Medium.
- **What it changes for the decider:** **Ill-informed risk:**
  - The population is Steam (gaming) users, not producers.
  - The sampling method and N are not stated on the page.
  - The "physical" counts include efficiency cores (Apple, Intel hybrid).

**R22. Apple base configurations (RQ-W1-2)**
- **Finding:**
  - MacBook Air base: Apple M5, 10-core CPU (4 "super" + 6 efficiency). The page lists no lower configuration.
  - Mac mini base: Apple M6, 12-core CPU (2 super + 4 performance + 6 efficiency).
- **References:** apple.com/macbook-air/specs/ and apple.com/mac-mini/specs/.
- **Location:** Tech specs.
- **Read/unverified:** Read through a fetch summarizer on 2026-11-22.
- **Confidence:** Medium. Re-check before citing: the core labels came through a summarizer.
- **What it changes for the decider:** Current base Macs have ≥ 10 cores, but only 4 or 6 high-performance cores. The installed base is older (see R21).

**R23. LibriSpeech (RQ-W2-4)**
- **Finding:**
  - Licence: CC BY 4.0. About 1000 h of read English speech.
  - Citation requested: Panayotov, Chen, Povey & Khudanpur, ICASSP 2015.
  - Download: archives such as `dev-clean.tar.gz` (337 MB), plus `md5sum.txt` with MD5 checksums, on three mirrors (e.g. https://openslr.trmal.net/resources/12/).
- **Reference:** OpenSLR SLR12. https://www.openslr.org/12/
- **Location:** Resource page.
- **Read/unverified:** Read.
- **Confidence:** High.
- **What it changes for the decider:**
  - CC BY 4.0 allows processing and redistribution with attribution, so it suits a public artifact. I did not read the CC legal code in this task.
  - The checksums are MD5, not SHA-256.
  - The recordings are not anechoic (LibriVox home recordings).

**R24. LibriVox (RQ-W2-4)**
- **Finding:** "all our recordings are public domain" in the USA, but not necessarily in other countries. Credit is not required but is appreciated.
- **Reference:** LibriVox, "Public domain". https://librivox.org/pages/public-domain/
- **Location:** Page text.
- **Read/unverified:** Read.
- **Confidence:** High.
- **What it changes for the decider:** This is the source audio behind LibriSpeech. Public-domain status outside the USA is not guaranteed.

**R25. EBU SQAM (RQ-W2-4)**
- **Finding:** By downloading, the user agrees "not to use this material for commercial purposes other than as a R&D tool". The page does not address redistribution. Track details are in EBU Tech 3253, which I did not read. The download is FLAC at https://qc.ebu.io/testmaterial/523/, with no checksums.
- **Reference:** EBU, "SQAM CD" (07 Oct 2008). https://tech.ebu.ch/publications/sqamcd
- **Location:** Page text.
- **Read/unverified:** Read. The separate "EBU Terms of Use" were not read.
- **Confidence:** Medium.
- **What it changes for the decider:** Redistributing processed SQAM speech in a public CI artifact is not shown to be permitted. Building stimuli locally is the case the page supports.

**R26. ITU-T P.501 (RQ-W2-4)**
- **Finding:** The edition in force is P.501 (07/26). The 04/25 edition's signals are served from the ITU-T Test Signal Database. The 2000 Amendment 1 signals were sold on CD-ROM. The page states no licence for the signals.
- **Reference:** ITU-T, P.501 record page. https://www.itu.int/rec/T-REC-P.501
- **Location:** Edition list.
- **Read/unverified:** Read.
- **Confidence:** Medium.
- **What it changes for the decider:** Redistribution rights are **unknown**.

**R27. EARS (RQ-W2-4)**
- **Finding:** 107 speakers and about 100 h of anechoic speech at 48 kHz. Licence "CC-NC 4.0". No checksums.
- **References:**
  - Richter et al., "EARS: An Anechoic Fullband Speech Dataset…", arXiv:2406.06185, accepted at Interspeech 2024.
  - Dataset: github.com/facebookresearch/ears_dataset.
- **Location:** Abstract; README.
- **Read/unverified:** Read.
- **Confidence:** High.
- **What it changes for the decider:** This is the anechoic option, but it is non-commercial. It is **not usable** in a commercial product's public artifact.

**R28. Liverpool ARU speech corpus (RQ-W2-4)**
- **Finding:** IEEE (Harvard) sentences, 12 British English speakers, anechoic. The page states **no licence**.
- **Reference:** University of Liverpool ARU Speech Corpus. doi:10.17638/datacat.liverpool.ac.uk/681
- **Location:** Page text.
- **Read/unverified:** Read.
- **Confidence:** Medium.
- **What it changes for the decider:** Its terms are unknown.

**R29. K9 added: corpus, Vorländer Table 15.1**
- **Finding:**
  - Table 15.1 is a *proposal for filter-update intervals* in interactive VR, after Lentz et al. 2007.
  - Rows: 35 ms for source or head rotation; **700 ms** for translational movement > 0.25 m (specular part); **3 s** for movement > 1 m (specular + scattering part).
  - The text says the data are subject to future development.
- **Reference:** Vorländer (2008).
- **Location:** §15.3, Table 15.1.
- **Read/unverified:** Read (corpus).
- **Confidence:** High.
- **What it changes for the decider:** **Conditions differ.** These are update intervals for a moving listener or source in real-time VR. They are not a load-time, per-scene or per-emitter budget, and the table says nothing about thread count. W-1, W-2 and W-3 all read it by extension.

## 3. Not found / unresolved

1. **Sustained level step in a reverberant tail, inside an ongoing signal (RQ-W2-3), with step size, rise time (about 30 ms equal-gain), signal and paradigm.**
   - Searched: increment detection in continuous noise; level change in ongoing music or speech; JASA/JAES; the corpus (Vorländer, Toole, Blauert, Kuttruff, Zotter & Frank).
   - Not found. Only transient increments on tones (R11) and music (R13) turned up, plus jnds between conditions (R5–R9).
   - What would settle it: a JASA or Acta Acustica study of DRR or reverberant-level change detection *within* a stream, or of time-varying reverberation.
2. **Miller (1947), JASA 19, white-noise intensity DL.**
   - The full text could not be retrieved.
   - Secondary sources disagree on the pages (606–619 vs 609–619), and the value was not confirmed. Unverified.
3. **Leventhal 1986 and the 1987 replies; Burstein.**
   - The AES e-library returned 403 or 503. Abstracts were seen through search only.
4. **Maurer, Hothorn & Lehmacher (1995).**
   - Not retrieved; only a citation from memory exists, which is not used here.
   - R1 and R2 cover the property instead.
5. **ITU-R BS.1534-3 (MUSHRA).** Not retrieved in this task.
6. **REAPER render modes (full-speed offline, 1× offline, online).**
   - The cockos wiki redirected, and the User Guide PDF (v7.x) was not read. Unverified.
7. **PreSonus Studio One manual itself.** Only Fender Studio Pro 8.2 was read (R20).
8. **Any vendor statement that a host times out or drops audio on a slow offline render.**
   - None found in any manual read.
   - What would settle it: vendor knowledge-base articles, or a test on each host. That test is an orchestrator measurement, not literature.
9. **Core counts among DAW users.**
   - No producer or DAW-user hardware survey with core counts was found.
   - Avanzini et al. (SMC 2025) and Production Expert surveys cover DAW choice only, and I did not read them.
   - MIDiA (n = 2,109) is paywalled.
10. **VCTK 0.92 licence.**
    - The DataShare page (doi:10.7488/ds/2645) returned 403. See §4.
11. **CC BY 4.0 legal code.**
    - Not fetched. The rights to process and redistribute are taken from the licence's name only.
    - Read creativecommons.org/licenses/by/4.0/legalcode before relying on them.

## 4. Conflicts between sources

- **VCTK 0.92 licence.** A third-party mirror of the README states CC BY 4.0. The University of York catalogue record (catalogue.yorvoice.york.ac.uk/catalogue/M4IACQQQ) lists ODC-BY 1.0. Both were seen through search only. The official record is unread.
- **Miller (1947) page range.** The OrDB record gives 606–619; Allen & Neely (1997) give 609–619. Both were seen through search only.
- **Sub-dB audibility in the corpus.**
  - Toole §19.1.1 puts the smallest audible overall loudness change at about 1 dB, and Vorländer Table 6.1 puts the G jnd at 1 dB.
  - Zotter & Frank §4.8 say loudness differences below 0.5 dB are audible in monophonic noise.
  - Conditions differ: program loudness against noise, with paradigms not stated. Both are reported; I pick no winner.

## 5. Seat claims screened

| seat / source | claim (as stated) | status | reference |
|---|---|---|---|
| Interrogator file 16 DC-06; decider K21 | P(X ≥ 12 \| 16, ½) = 0.038 (2517/65536 = 0.0384); "a per-size 12/16 rule raises the family-wise false-detection rate" | **Confirmed.** 2517/65536 = 0.038406. Two uncorrected tests give 0.0753; more sizes raise it further (§2a). | Computation §2a |
| Decider K9 / options W-1 to W-3 | "Table 15.1's 700 ms / 3 s rows" as a background-solve budget | **Corrected (conditions).** These are VR filter-update intervals for listener or source movement (> 0.25 m and > 1 m). They are not a load or solve budget, and the table says nothing about thread count. | Vorländer §15.3, Table 15.1 |
| Decider K24 / AX47 | "level-step detection conditions (G and C80 jnd 1 dB…)" | **Confirmed as a value; conditions differ.** 1 dB in 500–1000 Hz, between room conditions, paradigm not stated. Sub-dB audibility in noise is reported (R8), and within-stream increments on tones reach 0.4–0.9 dB (R11). | Vorländer Table 6.1; R8; R11 |
| Decider brief (S8 focus) | 3-minute bounce at 96 kHz runs 0.82–1.17 × real time; is above 1 × a break? | **Partly informed.** VST3 allows slower-than-real-time offline processing. Logic, Cubase, Live, Bitwig, FL Studio and Studio Pro document offline export as the default, with real-time only for external gear. No timeout is documented. REAPER and Studio One were not verified. | R14–R20 |

## 6. Corpus candidates (named only; adding them is Maisara's decision, subject to licence)

- ITU-R BS.1116-3 (2015). Free from the ITU, but ITU copyright applies.
- Buss, Hall & Grose (2012), PMC open access.
- Kin & Dobrucki (2016), *Archives of Acoustics*, open access.
- FDA, *Multiple Endpoints in Clinical Trials* (2022). US government work.
- Goeman & Solari (2010), *Ann. Stat.* (arXiv preprint).
- Leventhal (1986), JAES, paywalled.
- Viemeister & Bacon (1988), JASA, paywalled.
- Miller (1947), JASA, paywalled.

## 7. Readiness for the decider

**D-W1. NOT READY on the rows below.**

| K | status | facts to rely on |
|---|---|---|
| K9 (Table 15.1) | **Ill-informed: conditions differ.** Now known: VR movement-update intervals, not a solve or load budget. | R29 |
| K13 (DAW behaviour on slow offline render) | **Under-informed.** Six hosts plus the VST3 API document offline as unbounded in time, with no timeout. REAPER and Studio One (PreSonus) are unverified. No vendor states what happens on a timeout or freeze. | R14–R20 |
| K14 (core counts) | **Under-informed, with an ill-informed risk.** Steam, October 2026: ≥ 4 cores Windows 97.14 % / macOS 96.59 %; ≥ 8 cores 57.05 % / 86.54 %. The population is gamers, the method is unstated, and E-cores are counted. No DAW-user survey exists in what I found. | R21, R22 |

The other D-W1 rows (K3–K8, K10–K12) are code and CI facts, F1–F13 for the orchestrator, and were not in my scope.

**D-W2.**

| K | status | facts to rely on |
|---|---|---|
| K21 | **Known (confirmed)** | §2a |
| K22 (FWER of the procedures; thresholds at n = 16) | **Known.** Bonferroni/Šidák: 13/13/14 for k = 2/4/6. Holm: 13→12 (k = 2), 13,13,13→12 (k = 4), 14,14,13,13,13→12 (k = 6). Fixed sequence: 12/16 at each step, FWER exactly 0.0384 under the global null. | §2a, R1, R2 |
| K23 (power at 16 trials) | **Known (computed).** At p = 0.75, P(≥ 12) = 0.630 and P(≥ 13) = 0.405. Leventhal remains unverified. | §2a; R3 unverified |
| K24 (level-step thresholds within a stream) | **Under-informed, and ill-informed if R10 or R11 are transferred.** No study of a sustained step in a reverberant tail. Corpus jnds are 1 dB between conditions (0.5 dB audible in noise, per Zotter & Frank). Within-stream data exist only for tones (≈ 0.4–0.9 dB, transient) and music (2–3 dB, N = 5, transient). | R5–R13 |
| K25 (speech source and licence) | **Partly known.** LibriSpeech is CC BY 4.0 with MD5 sums, but not anechoic. SQAM is R&D-only, with redistribution unaddressed. EARS is non-commercial. VCTK is in conflict. P.501 and ARU terms are unknown. | R23–R28 |
| K26 (BS.1116 practice) | **Known.** A single-listener ABX lies outside BS.1116-3. A null result needs a shown-sensitivity anchor. Sessions hold 10–15 trials. | R4 |

**Verdict for D-W2: NOT READY** on K24, and on K25 only if a source other than LibriSpeech or LibriVox is preferred. The step sizes would rest on 1 dB jnds measured between conditions under unstated paradigms. No source found measures a sustained tail-level step inside an ongoing signal. The design and statistics (K21–K23, K26) are ready.
