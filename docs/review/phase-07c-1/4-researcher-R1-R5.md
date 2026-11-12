# 4 — Researcher dossier R1–R5 (phase 07c-1)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Brief: file 2.

# Researcher dossier: phase 07c-1, R1–R5 (D-C1, D-C2, D-C3, D-C9)

All sources accessed 2026-11-12. Corpus revision as in the convening file (`c1b171fe…`). This dossier adds to `/home/user/makroof/docs/review/phase-05h/12-researcher-T5T4-61.md` (cited as "T5T4-61 F<n>") and does not repeat it. Local JUCE sources are no longer under `build/debug/_deps/` (Glob found no `juce_AudioProcessor.h`), so JUCE facts here come from docs.juce.com or from T5T4-61.

## 1. Decisions served and questions examined
- **R1** (Seat 5, K9; D-C9 Matter D, D-C3 A3): which thread state restore runs on, and whether hosts set a time limit on it.
- **R2** (Seat 5, K10; D-C2/D-C3): hosts that do not tell the plug-in they are rendering offline.
- **R3** (Seat 7, K11): hang dialogs and timeouts.
- **R4** (Seat 1, K8, D-C1 Matter C): whether a level step in the late reverberation is audible inside a running signal. Corpus checked first.
- **R5** (Seats 5/7/8, K12, D-C3 A3): plug-in state of several MB in practice.
- Premise screen: K5 (18 MB) and K8 (Table 6.1).

## 2. Findings

**R4: corpus first**

- **F1** | R4 | Vorländer Table 6.1 (after Vorländer 1995 and ISO 3382-1) gives these jnds, each in the 500–1000 Hz range: G 1 dB, C80 1 dB, EDT 5 %. The table states no paradigm, signal or listener type. The surrounding text says the jnds come "from laboratory and real-room tests". | corpus `vorlaender-auralization.md` §6.4, Table 6.1 (L2054–2066) | read | high | Confirms K8 as printed. It does **not** say the values hold for a step inside a running stream.
- **F2** | R4 | With music, a change of about ±1.5 dB in a reflection's level is detectable (Reichardt and Schmidt). This is a single reflection, not the late tail. | corpus `kuttruff-room-acoustics.md` §7.3 (L3284) | read | medium (conditions thin) | A within-music value above 1 dB, but for a reflection, not the tail.
- **F3** | R4 | Loudness differences below 0.5 dB are audible in monophonic noise playback, but a weak directional loudness fluctuation below 1 dB is "normally inaudible". | corpus `zotter-frank-ambisonics.md` §4 AllRAD/EPAD comparison (L1515) | read | medium | This is the bound for a change in *overall* level, which applies when the tail dominates (see D1).
- **F4** | R4 | **D/R jnd** (Larsen, Iyer, Lansing & Feng 2008, JASA 124(1) 450–461, doi:10.1121/1.2936368, PMC2677334). Stimuli: 300 ms wideband noise convolved with BRIRs measured with KEMAR at 4 m in an auditorium of about 1000 m³ with T60 0.78 s. Paradigm: 2I-2AFC, 3-down/1-up, 20 dB level rove. N = 8 experienced listeners. Results (Exp. 1, Fig. 3, binaural):
  - at D/R 0 dB: 2.4 dB (both onsets);
  - at D/R +10 dB: 2.7–3.8 dB;
  - at −10 and +20 dB: 5.8–8.7 dB, which the authors flag as unreliable because they sit near the 7.15 dB level-cue ceiling (Eq. 4).
  - Monaural ≈ binaural (Exp. 2a).
  - 3-ERB bands at 0 dB D/R (Exp. 2b): 3.6 dB at 500 Hz, 4.2 dB at 3 kHz.
  - Here the **direct** level was scaled and the reverberant level held constant. | PMC full text, §3 Fig. 3, §4 Figs. 4–5, Eq. 4 | read | high (for its conditions) | **Ill-informed if used directly.** The level rove was designed to remove the loudness cue. A tail step in the product carries an overall-level cue, so these jnds overstate the threshold for D-C1's case.
- **F5** | R4 | Two further results, as reported in the Introduction and Discussion of Larsen et al. 2008:
  - Zahorik (2002), JASA 112(5) 2110–2117, doi:10.1121/1.1506692: varied the **reverberant** level, roved the overall level, 2AFC; D/R jnds of roughly 5–6 dB at 0/10/20 dB D/R for noise, a speech syllable and an impulse.
  - Reichardt & Schmidt (1966): classical music, overall level held constant, yes/no paradigm; U-shaped jnd curve with a minimum of about 2 dB at 0 dB D/R. | as F4, Introduction; "Comparison to prior studies" | read via Larsen; Zahorik's own text **unverified** (PubMed abstract not retrievable: cookie wall) | medium | Every D/R jnd found removes or controls the overall-level cue.
- **F6** | R4 | C80 jnd for music (Vigeant, Celmer, Jasinski et al. 2015, JASA 138(1) 476–491, doi:10.1121/1.4922955). Abstract:
  - earlier studies pointed above ISO 3382's ≈1 dB;
  - the final study gave **≈3 dB** in concert-hall and chamber-hall conditions;
  - a method in which listeners **switch between the two signals in real time** gave more consistent results;
  - extensive training was required.
  - Signals and N are not stated in the abstract. | PSU Pure record (abstract) | abstract read; body unverified | medium | Disagrees with F1 for C80 (see §4). The real-time switch is the paradigm closest to a level step inside a running stream that was found, but it switches C80, not a level.
- **F7** | R4 | Detecting an increment in a continuous sound vs comparing gated sounds. Buss, Hall & Grose (2012), JSLHR 56(1) 71–80, doi:10.1044/1092-4388(2012/12-0008), PMC3911822: adult intensity discrimination is about 4.5 dB better, in 10log(ΔI/I) units, for continuous than for gated stimuli. They cite Viemeister & Bacon 1988 (4.6 dB) and Green et al. 1979 (4.2 dB); their own adults showed 4.9 dB (N = 11, 1 kHz tone, 65 dB SPL, 3AFC). | PMC: Introduction; Exp. 1 Discussion | read (secondary for V&B 1988) | medium | Direction only: a change inside a running sound is detected better than in paired comparison. The data are tones and a 500 ms increment, not a sustained step in a reverb tail under a 30 ms crossfade.
- **D1** (derived, not stated by any source) | R4 | How much a tail step of x dB changes the overall level. Direct energy E_d and reverberant energy E_r are held fixed apart from the step:
  - ΔL = 10·log10[(E_d + E_r·10^(x/10)) / (E_d + E_r)].
  - For x = 1 dB: ΔL ≈ 0.10 dB at D/R +10 dB; 0.53 dB at D/R 0 dB; 0.92 dB at D/R −10 dB.
  - For x = 1.33 dB (K7's SE ceiling) at D/R −10 dB: ΔL ≈ 1.22 dB.
  - Arithmetic, x = 1 dB at D/R 0: 10^0.1 = 1.259, and 10log(2.259/2) = 0.53 dB.
  - At low D/R (far source, large reverberant room), a 1 dB tail step is close to a 1 dB overall-level step. F3 then applies (< 0.5 dB audible in noise), not F4/F5. | arithmetic | — | — | The answer to R4 depends on D/R at the listener. That is a condition D-C1's options do not yet state.

**R1: thread of state restore and time limits**

- **F8** | R1 | In the VST3 SDK, `IComponent::setState` and `getState` both carry the annotation "[UI-thread & (Initialized | Connected | Setup Done | Activated | Processing)]". | Steinberg VST 3 API doc, IComponent, https://steinbergmedia.github.io/vst3_doc/vstinterfaces/classSteinberg_1_1Vst_1_1IComponent.html | setState/getState | read | high | A restore may arrive on the UI thread **while the component is Processing**, so the audio thread runs at the same time (R1(b): undo or preset recall during playback). This matches T5T4-61 F5: in offline contexts it may arrive on the process thread.
- **F9** | R1 | The VST3 FAQ "Persistence" page gives only the call order (component getState then controller getState; on load, setState then setComponentState then setState) and preset loading. It says nothing on threads, size, autosave or undo timing, and states no time limit. | https://steinbergmedia.github.io/vst3_dev_portal/pages/FAQ/Persistence.html | Q "How does persistence work?" and the setComponentState Q | read | high | No time limit is specified by Steinberg.
- **F10** | R1 | JUCE `get/setStateInformation` docs state no thread, no real-time constraint and no locking. | https://docs.juce.com/master/classAudioProcessor.html (chars 100 000+) | member docs | read | high | JUCE gives no guarantee either way.
- **F11** | R1 | Apple AU documentation:
  - `AUAudioUnit.fullState` is bridged to v2 `kAudioUnitProperty_ClassInfo`. Hosts "may use" it to save and restore state in a preset or document. No thread, timing or size is given.
  - Since macOS 11 the system loads audio units into a separate process, depending on architecture or host preference. Process names: `AUHostingServiceXPC` (native) and `AUHostingServiceXPC_arrow` (Rosetta), "may change".
  - Apple advises: when setting AU properties, "don't assume callbacks happen on the main thread". | https://developer.apple.com/tutorials/data/documentation/audiotoolbox/auaudiounit/fullstate.json ; https://developer.apple.com/documentation/audiotoolbox/debugging-out-of-process-audio-units-on-apple-silicon.md | Discussion; "Troubleshoot Common Issues" | read | high | In AU the restore thread is unspecified and may not be the main thread. Out-of-process hosting means a slow restore blocks a host process, not necessarily the DAW's own process.
- **F12** | R1/R3 | Lead only, **not evidence**. An Apple Developer Forums post (June 2026, by a third-party developer, no Apple reply) reports that Logic Pro 12 crashes when an AU takes more than about 20–30 s to initialise. The AU process does not crash, only Logic. It does not say which call is slow. | https://developer.apple.com/forums/thread/835717 | — | read; forum, unverified | low | Suggests a host-side limit in the tens of seconds, far above 0.15 s. Not citable.
- No host (Logic, Live, Cubase, Bitwig, REAPER, FL, Studio One) documents a time limit, watchdog or disable action for a slow `setState` in any retrievable text (§3).

**R3: hang indications**

- **F13** | R3 | **Windows**: an application counts as not responding if it is not waiting for input, is not in startup processing, and has not called PeekMessage within "the internal timeout period of 5 seconds". The page adds that the 5 s criterion "is subject to change". | Microsoft Learn, IsHungAppWindow, https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-ishungappwindow | Description; Remarks | read | high | Applies to the host's UI thread on Windows. A synchronous restore on the UI thread (F8) blocks it for its duration, summed over instances.
- **F14** | R3 | **macOS**:
  - A delay below 100 ms in a discrete interaction is "rarely noticeable". A few hundred ms can make an app feel unresponsive.
  - Most Apple developer tools report a hang once the main run loop is busy for more than **250 ms**.
  - The spinning wait cursor appears when an app is unresponsive, but **no onset time is stated** for it. | Apple, "Understanding hangs in your app", https://developer.apple.com/documentation/xcode/understanding-hangs-in-your-app.md | Overview; "Understand hangs" | read | high | Gives a perceptual and tooling anchor of 100/250 ms. At about 0.15 s per instance, 8 instances run sequentially take about 1.2 s (derived), past 250 ms.
- **F15** | R3 | **Bitwig**: a crashed plug-in's interface is replaced by a notification, and "Reload Plug-in" recovers it. The hosting modes decide whether the audio engine survives. The page says **nothing on unresponsive plug-ins, dialogs or timeouts**. | Bitwig User Guide, "Plug-in Handling and Options", https://bitwig.com/userguide/latest/vst_plug-in_handling_and_options | crash section | read | high | No documented hang timeout. A "Plug-in host is not responding" dialog appears only in forum reports (KVR, VI-Control), which are not citable.

**R2: offline signalling**

- **F16** | R2 | **FL Studio**: the wrapper option "Notify about rendering mode" informs the plug-in when FL is rendering. The manual page **does not state its default**. | Image-Line FL Studio online manual, Plugin Wrapper, https://www.image-line.com/fl-studio-learning/fl-studio-online-manual/html/plugins/wrapper.htm | Processing tab, Compatibility options | read | high (existence); default not found | Signalling is an option set per plug-in. It is not shown to be on.
- **F17** | R2 | **REAPER**: a preference "Inform plug-ins of offline rendering state" exists (Preferences > Plug-ins > VST). The official wiki is not retrievable (it redirects to the cockos.com home page). The only measurement found is the fst project's notes (Debian sources, fst 0.177.0-1, `docs/process-levels.md`, REAPER 6.42 on Linux, **VST2**): with the box unchecked REAPER reported `kVstProcessLevelRealtime` during offline render, and with it checked, Offline. | https://sources.debian.org/src/fst/0.177.0-1/docs/process-levels.md | — | read; developer notes, not vendor; VST2 only | low–medium | A lead that REAPER by default may not signal offline (VST2). VST3 behaviour is not found.
- **F18** | R2 | **Live 12**: the release notes (12.3) fix latency compensation in bounces for "plug-ins that have a dedicated latency for offline processing". No line on VST3 offline mode or `setupProcessing` in the first 300 k of 310 k characters read. JUCE-forum and Ableton-forum threads (2021–2022) say Live does not set offline for VST3 during export (forum.juce.com/t/ableton-vst3-isnonrealtime-not-set/46912). | https://www.ableton.com/en/release-notes/live-12/ | 12.3 bugfixes | release notes read; forum claims **unverified** | low | Live's VST3 offline signalling is not established either way from vendor text.
- **F19** | R2 | JUCE: `isNonRealtime()` returns false if the mode is unknown; it "may be unreliable until prepareToPlay()" and can change at each prepareToPlay. | docs.juce.com AudioProcessor | isNonRealtime | read | high | A host that never signals offline yields "realtime", so condition 6's offline path is never entered in such a host.

**R5: large state**

- **F20** | R5 | Neither VST3 (F8, F9) nor Apple AU (F11) nor JUCE (F10) documents a size limit, a size recommendation or a call frequency for state. | as cited | — | read | high (for absence) | No spec-level cap exists to rule A3 out. Practical cost is undocumented by vendors.
- **K5 check** | 12 s × 96 000 × 2 × 2 × 4 B = 18 432 000 B ≈ 18.4 MB (17.6 MiB). | arithmetic | — | confirmed.

## 3. Not found / unresolved
- **R1, all hosts**: no vendor document gives the thread for state restore at load versus undo or preset recall, or a time limit for it. Searched: Steinberg SDK and FAQ, Apple AudioToolbox docs, JUCE docs, Bitwig guide, Ableton release notes. Cubase help (`archive.steinberg.help`) returned HTTP 403. The REAPER wiki and user guide were unreachable (as in T5T4-61 F18). Logic and Avid help pages were not reachable or silent. **What would settle it:** an instrumented build that logs the thread id, the elapsed time and the transport state per `setStateInformation`, run in each host and OS, or vendor developer-relations statements.
- **R2 defaults**: the defaults of FL's "Notify about rendering mode" and REAPER's "Inform plug-ins…" are not found in vendor text. VST3 offline signalling in Live, Logic bounce-in-place and REAPER is not found. The same measurement build, logging `isNonRealtime()` during export, freeze and bounce-in-place, would settle it.
- **R3**: no documented onset time for the macOS spinning cursor. No documented hang timeouts for Logic, Live, Cubase, Bitwig, REAPER or FL. Logic's behaviour with a slow out-of-process AU is known only from a forum lead (F12).
- **R4**: **no study found that measures detection of a level step in the late reverberation inside a running music or speech stream under a crossfade.** Searched: D/R jnd, reverberant level, time-varying reverberation, IR switching or crossfade audibility, G jnd, C80 jnd, continuous vs gated increments. Not obtained:
  - Acta Acustica 2026 (doi 10.1051/aacus/2026012, on accepting late-reverb changes): HTTP 403.
  - Davies (Salford), difference limen of music level: HTTP 403.
  - Miller 1947 (JASA 19), white-noise intensity jnd: citation only, page conflict 606 vs 609.
  
  **What would settle it:** a within-stream 2AFC or yes/no test on music and speech at several D/R values, with a level step in the tail band under a 30 ms crossfade. That is a candidate for A4's acceptance test (Seat 1's to name).
- **R5**: no vendor documentation on host undo snapshots, autosave calls of getState, or project-size handling (Cubase Auto Save page: 403; Logic: no interval documented in retrieved pages). Every concrete report (REAPER undo grows ~5 MB per parameter move, frequent getState calls, Cubasis unresponsive, base64 encoding of state) is **forum-only**: forum.juce.com /31349, /57791; forums.steinberg.net /883499, /816374. Not citable.

## 4. Conflicts between sources
- **C80 jnd**: 1 dB (Vorländer Table 6.1 / ISO 3382-1, F1) versus about 3 dB for music (Vigeant et al. 2015, F6, real-time switching, trained listeners). Both are paired comparisons of C80, not a level step.
- **D/R jnd**: 2.4–3.8 dB (Larsen 2008, direct level scaled, F4) versus 5–6 dB (Zahorik 2002, reverberant level scaled, F5) versus a ≈2 dB minimum (Reichardt & Schmidt 1966, music, F5). Larsen attributes the gap to different manipulation and level controls.
- **AU process names**: Apple's doc (F11) gives `_arrow` = Rosetta and the plain name = native. Forum posts say the opposite. Use Apple.

## 5. Seat and decider claims screened
- Decider K8 / Option C1 | "1 jnd of G and of C80, Vorländer Table 6.1" | **confirmed as printed** (F1), with conditions **ill-informed** for a within-stream step. The table gives no paradigm. C80's jnd is contested (F6). Detection of tail steps depends on D/R (D1, F3).
- Decider K5 | tail ≈ 18 MB per instance | **confirmed** (18.4 MB).
- Seat 1 brief premise | "does Table 6.1 apply … inside a running stream" | **unverifiable from literature**. No direct study (§3). F7 gives the direction (within-stream changes are detected better), on tones.
- Decider R2 premise | "if a common host by default does not signal offline" | **unverifiable** at vendor level. There are leads for REAPER (F17, VST2) and Live VST3 (F18, forum); FL's default is not stated (F16).
- T5T4-61 F5 | VST3 setState on the UI thread | **confirmed and extended**: also permitted while Processing (F8).

## 6. Corpus candidates
- Larsen, Iyer, Lansing & Feng 2008, JASA 124(1) 450–461 (open via PMC).
- Vigeant et al. 2015, JASA 138(1) 476–491.
- Zahorik 2002, JASA 112(5) 2110–2117.
- Apple, "Understanding hangs in your app"; Microsoft, IsHungAppWindow.
- Steinberg VST3 IComponent doc and FAQ "Persistence".

## 7. Readiness for the decider

| K | fact | status |
|---|---|---|
| K5 | 18 MB tail state | known (confirmed) |
| K8 | jnd for a provisional-to-final tail step | **ill-informed → partially corrected**: Table 6.1 confirmed as printed. Paired-comparison D/R jnds of 2.4–6 dB (F4, F5) remove the level cue and do not transfer. At low D/R a tail step ≈ an overall-level step, whose bound is < 0.5 dB in noise (F3, D1). No within-stream study exists (§3). |
| K9 | host tolerance of a blocked setState | **uninformed by documentation**: VST3 restore on the UI thread, possibly while Processing (F8). No host limit is documented. OS anchors: macOS hang reporting at 250 ms, perceptible above about 100 ms (F14); Windows not-responding at 5 s (F13). Forum lead: Logic crash at 20–30 s of init (F12). |
| K10 | hosts not signalling offline | **under-informed**: FL per-plug-in option with default unstated (F16); REAPER box (VST2 lead, F17); Live VST3 forum-only (F18); unknown is treated as realtime (F19). |
| K11 | hang dialogs and timeouts | partly known: OS-level only (F13, F14); host-level not found. |
| K12 | multi-MB state limits and costs | **uninformed at vendor level**: no spec cap (F20); all cost reports are forum-only. |

**Verdict: NOT READY.**
- **R1, R2, R3 and R5** cannot be closed from documentation. Only a per-host instrumented measurement (thread, duration, `isNonRealtime`, getState frequency and size) or vendor statements would close them.
- **R4** has no direct study. The decider can stand on F1, F3, F4–F7 and D1 only with their conditions stated: paired comparison versus within-stream, level-roved versus not, and D/R at the listener.

Files read: `/home/user/makroof/docs/review/phase-07c-1/2-decider-convening.md`, `/home/user/makroof/docs/review/phase-05h/12-researcher-T5T4-61.md`, and corpus files `vorlaender-auralization.md`, `kuttruff-room-acoustics.md`, `zotter-frank-ambisonics.md` and `roginska-geluso-immersive-sound.md` in `/home/user/makroof/docs/corpus/`.