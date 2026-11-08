# Phase-07 decisions: researcher dossier (2026-11-08)

Researcher report for D8, D9, D3, D4, D7 (D1 skipped: no standard found). All sources accessed 2026-11-08;
"read" = fetched by the researcher; "unverified" = snippet/abstract/forum lead. Main-session addition marked M1.

## Findings

| id | decision | finding | reference | read? | conf. |
|---|---|---|---|---|---|
| F1 | D8 | pluginval v1.0.4 default rates 44100, 48000, 96000; blocks 64…1024. `run_pluginval.sh` passes no `--sample-rates`, so CI never drives an unsupported rate through pluginval. | Tracktion pluginval v1.0.4 `Source/CommandLine.cpp` | read | high |
| F2 | D8 | pluginval processing tests fail on NaN/Inf/subnormal; **no test checks for silence**; state restoration level ≥ 8 requires byte-identical re-read state; no test catches plugin exceptions. | pluginval v1.0.4 `Source/tests/BasicTests.cpp` | read | high |
| F3 | D8 | For AU at strictness > 5 pluginval also runs `auval -strict -stress 20`. | same | read | high |
| **M1** | D8 | **Main session, repo CI log (run 42452887610, job "build (macos)", main @ c0541ed): auval RENDER TESTS run at 22050, 96000, 48000, 192000, 11025 and 44100 Hz; AU VALIDATION SUCCEEDED** (current plugin is the Phase 00 pass-through). So from Phase 07 on, `RealtimeEngine::prepare` throwing `std::invalid_argument` at 11.025/22.05/192 kHz would escape prepareToPlay during auval unless caught. Supersedes the researcher's unverified F4 (forum log with the same rates). | GitHub Actions log, maisara-abourady/makroof run 42452887610 | read | high |
| F5 | D8 | VST3: no documented way for a plug-in to refuse a sample rate in setupProcessing; rate changes only while inactive. | Steinberg VST 3 API docs (IAudioProcessor), `ivstaudioprocessor.h`, VST3 FAQ "Processing" | read | high |
| F6 | D8 | JUCE 8.0.17-security VST3 wrapper: setupProcessing does not check the rate; setActive(true) calls prepareToPlay and returns kResultOk. | JUCE `juce_audio_plugin_client_VST3.cpp` @ 8.0.17-security | read | high |
| F7 | D8 | AU: AUBase can answer kAudioUnitErr_FormatNotSupported via ValidFormat(), but JUCE's AU wrapper checks channel counts only, not rate; Initialize() calls prepareToPlay. Whether auval passes an AU that refuses a rate: not found. | apple/AudioUnitSDK `AUBase.cpp`; JUCE `juce_audio_plugin_client_AU_1.mm` | read | med-high |
| F8 | D8 | JUCE prepareToPlay returns void: no API path to refuse a rate. | JUCE AudioProcessor docs | read | high |
| F9 | D8 | Logic (10.1 help) lists 44.1–192 kHz incl. 176.4/192 kHz (file formats). Current DAW lists not found. | Apple Logic Pro X 10.1 Help, "Media and file formats overview" | read (old) | med |
| F10 | D9 | JUCE NormalisableRange skew: v = start + (end−start)·p^(1/skew); setSkewForCentre(c): skew = ln 0.5 / ln((c−start)/(end−start)); lambdas allow a true log map. | JUCE NormalisableRange docs / source @ 8.0.17-security | read | high |
| F11 | D9 | VST3 transmits normalised parameters; changing the mapping later changes recalled automation (supports freezing it with the IDs). | Steinberg dev portal "Parameters and Automation" | read | high |
| F12 | D9 | Perceived room size driven much more by reverberation time than physical volume; C80 predicted it at fixed volume. No functional form in the abstract. | Cabrera, Jeong, Kwak, Kim (2005), INTER-NOISE 2005, pp. 3221–3230 | abstract | med |
| F13 | D9 | Room-size judgements reportedly a power function of T (exponent unseen). | Yadav, Cabrera et al., AES 135th Conv. (2013) | unverified | low |
| F14 | D9 | Reverberation increases judged room size (direction only). | Kolarik, Moore, Cirstea et al. (2021), *Perception* 50, doi:10.1177/03010066211020598 | abstract | med |
| F15 | D3 | Rectangular end-truncation of a BRIR "can lead to audible artifacts"; patent applies a fade-out window. | Pallone, Emerit, US 9,848,274 B2 (2017) | read (patent) | low |
| F16 | D3 | BRIR length correlates with externalisation and colouration (headphones; conditions not stated). | Crawford-Emery, Lee (2014), AES 136th Conv. | abstract | low |
| F17 | D3 | Lundeby et al. (1995), *Acustica* 81(4), 344–355: truncation in measured-IR analysis, not rendering. ISO 3382-1 not retrieved. | citation | citation | med |
| F18 | D4 | Corpus: inside 32-bit float, > 1.0 doesn't clip; clipping at float-to-integer conversion (master/bounce); good practice keeps signals below 1.0; some plugins assume 1.0 max. | Izhaki Ch. 11 | corpus | high |
| F19 | D4 | Corpus: law of correct gain structure: set level early, later stages at unity (e.g. reverb at unity, level from the send). | Izhaki Ch. 10 | corpus | high |
| F20 | D7 | Power-preserving crossfade for correlation r: w² + 2·w·wᵢ·r + wᵢ² = 1 (Eq. 11), closed-form curves (Eqs. 16–17); linear law power-complementary only at r = 1, sin/cos only at r = 0; r measured on the two outputs (Eq. 18). | Fink, Holters, Zölzer (2016), DAFx-16, pp. 109–112 | read | high |
| F21 | D7 | Corpus: overlap power must stay constant (Vorländer §9.2.1); fades trade colouration vs clicks (Vorländer §15.1.1). Wefers (2015) thesis on IR exchange in partitioned convolution. | Vorländer; Wefers doi:10.18154/RWTH-2015-02185 | corpus; abstract | med |

## Derivations (researcher's arithmetic)
- D9: centre-10 m power skew: L = 1.5 + 98.5·p^3.535 → 1.53 / 2.23 / 10.0 / 37.1 / 69.4 m at p = 0.1/0.25/0.5/0.75/0.9; log map L = 1.5·66.67^p → 2.28 / 4.29 / 12.25 / 35.0 / 65.7 m. EDT-jnd (5 %) steps per quarter (T ∝ L): power 8.1/30.8/26.9/20.3, log 21.5 each.
- D3: decay before the 12 s cut at 125 Hz (T 39–43 s): 16.7–18.5 dB; 500 Hz 47.7 dB; 1 kHz 66 dB; uncapped design 90 dB.
- D4: 20·log10(2/0.3) = +16.48 dB; float headroom ≈ 770 dB; engine input guard |x| > 2²⁰ = +120.4 dB.
- D7: mid-fade equal-gain at r = 0: −3.01 dB; equal-power at r = 1: +3.01 dB.

## Not found
auval's verdict on an AU that refuses a rate; current DAW rate lists; peer-reviewed audibility threshold for IR truncation or end-fade length; perceptual scaling exponent for room size; a spatial-plugin unity-gain standard.

## Premises checked
- `RealtimeEngine::prepare` throws outside AX6 rates and leaves the engine silent: confirmed (`src/sim/RealtimeEngine.h` 32–42; `tests/unit/test_realtime_engine.cpp:459`).
- "pluginval's sample-rate test covers unsupported rates": corrected (F1); auval does drive them (M1).
- "centre 10 m = log-like": corrected (D9 derivation).
- "room-size change ⇒ uncorrelated tail": likely wrong: tail noise seeded only from (tailSeed, stream) (`NoiseTail.cpp:121`); correlation depends on envelope and AX1 alignment shift.
- Equal-power recall into an identical state gives +3 dB mid-fade.

## Readiness
- D8: READY with M1 (auval drives 11.025, 22.05, 192 kHz).
- D9: READY on mechanics; under-informed on perception (no scaling law).
- D3: READY on facts; NOT READY on audibility (no threshold found).
- D4: READY (corpus).
- D7: READY with the corrected premise.
- D1, D2, D6: no outside-corpus facts needed beyond the option check (D6's full-rebuild time is a Phase 07 measurement).
