# Spatial Scene VST: The Board of Experts to Model

Nov 9, 2026 · @Maisara

## 1. A disagreement with the brief

"Every detail that might impact how sound is heard" is the wrong accomplishment, and the people who solved this problem say so by what they built.

- IRCAM's Spat, the longest-running spatialiser in existence, was designed the other way round. Its control interface specifies the room effect in perceptual terms, deliberately avoiding the constraints of controlling a reverberator through a geometric or physical description of the room ([Spat 4 manual](https://www.scribd.com/document/650742616/Spat4-UserManual1)).
- Raghuvanshi's Triton ran a full wave simulation and then discarded almost all of it. The field of impulse responses is coded as a few perceptual parameters derived from energy decay ([Raghuvanshi & Snyder 2014](https://microsoft.com/en-us/research/wp-content/uploads/2016/07/ParametricWaveField.pdf)); billions of responses amounting to terabytes fit in under 100 MB, with tens of moving sources on a fraction of one CPU core ([Triton, JASA 2017](https://sonicfield.org/library/triton-practical-pre-computed-sound-propagation-for-games-and-virtual-reality)). Even then, the Gears of War 4 team found the accurate data pushed them toward stylised, emotional acoustics to escape an uncanny valley ([GDC 2017](https://www.gdcvault.com/play/1024008/)).
- The shoebox-plus-materials-plus-positions product is already commoditised. [HoRNet Spaces MK2](https://rekkerd.org/hornet-plugins-releases-spaces-mk2-room-based-reverb-effect-plugin/) sells room dimensions, per-wall materials, 3D source and listener positions and ray-traced reflections for €19.99. [Audiocube Space](https://mixdownmag.com.au/news/product/audiocube-space-puts-a-3d-acoustic-space-inside-your-daw/) links instances across tracks around one movable listener, with occlusion, directivity, Doppler and air absorption in real time. [THALM](https://www.production-expert.com/production-expert-1/tunary-instruments-thalm-place-music-in-another-room-using-geometry-now-with-aax-support) derives filtering from the walls and doorways between source and listener on a floor plan, and Soundly's Place It does geometry-based room modelling for free. IEM's RoomEncoder has done image-source rooms with movable source and listener, free and open-source, for years.
- Listeners cannot hear most of the detail. Plausibility is reached far below authenticity (Lindau and Weinzierl), and the BRAS round robin showed the best engines diverge from measurement in exactly the places that cost most to simulate.

**The accomplishment every seat shares.** A producer with no acoustics training builds a space and places sources in minutes; at any listening position the result is perceptually indistinguishable from a real room of that description (or deliberately better), updates within the edit, moves without artifacts, and translates to the output format, inside a DAW. Physical detail is admitted only when a listener can hear it.

If physical completeness stays the goal, say so: the slate shifts toward Odeon- and Treble-style engineering and away from the plugin masters.

## 2. The complexity map, including what the brief leaves out

What the brief named, compressed: physics splits at the Schroeder frequency (modes and diffraction below, rays above), so no single method covers a room and the real decision is the hybrid and where to cut it. Engineering has two clocks (millisecond audio deadlines against recomputation that takes seconds), plus time-varying partitioned convolution, lock-free threading, a 3D GUI inside a plugin window and bus layouts up to 7th-order Ambisonics. Product has to choose whether physical or perceptual controls are primary, and for whom: producers, post, games and architects each demand a different truth.

Nine angles the brief leaves out:

1. **The scene is cross-track.** One room, many tracks means a central renderer with linked satellite instances, inter-instance communication, 3D automation in a DAW's linear lanes, and session recall. Audiocube's instance linking has set that expectation.
2. **The listener's ears.** HRTF individualisation, externalisation and headphone correction can make a perfect room sound inside the head. Jot was still publishing on externalised binaural rendering in 2023 ([publications](https://sites.google.com/site/jmmjot/)); it is not solved.
3. **3D authoring is a CAD problem.** Direct manipulation, snapping, glTF/OBJ/IFC import, material tagging. SketchUp is the precedent for making this approachable.
4. **Sources are not points.** Instrument and voice directivity, extent, near-field, moving sources.
5. **Matching reality beats inventing it.** Users trust sampled spaces: Indoor measured 60 spaces across 10 locations, over 1,000 impulse responses ([review](https://www.pro-tools-expert.com/video-reviews/2016/11/20/review-indoor-by-audio-ease-part-one)), moving a speaker to six or seven positions and the mic array to other rooms ([Mix](https://www.mixonline.com/?p=13894)). A "fit a room to this reference" feature may be worth more than any geometry option.
6. **Format churn.** Atmos/ADM, MPEG-H, IAMF, SOFA; the output stage must be pluggable.
7. **Convincers for two audiences.** Producers need loudness-matched A/B against references; acousticians need ISO 3382 parameters against measurement; both need to see where the simulation stops.
8. **IP.** HRTF dataset licences, material databases, live patents. Check before shipping.
9. **Your own constraint.** Solo, AI-assisted coding, outside the hubs. No exemplar with verified results exists for an AI-assisted solo DSP founder; per the Directive that reads "not found", so the positive deviants below are solo humans who shipped deep DSP.

## 3. The board: how to read it

Nine seats, each defined by an accomplishment rather than a title; each gets its own chat and a full Directive build (3 to 5 exemplars, 5 to 10 incidents each).

- Each seat states the accomplishment, what the persona is for, the typical performer to subtract, and candidates tagged master, positive deviant (excels under constraints like yours) or adjacent domain.
- Each candidate carries evidence of superior results, the non-practice advantages they had, and how much primary material exists (rich, moderate or thin).
- Linked claims trace to the pages in Sources; unlinked claims are from my own knowledge and get verified in each seat's Phase 1.
- Cross-listed people (Costello, Fonseca, van der Schoot) yield different incident sets for different accomplishments.

## Seat 1. Perceptual gatekeeper

**Accomplishment:** decides which acoustic details the target listener can hear, proves it with listening data, and cuts the rest. **For:** critique and decide. **Typical performer:** judges on one pair of headphones, never blind, ships every parameter the engine can produce.

| Candidate | Role | Evidence of superior results | Non-practice advantages | Primary material |
| --- | --- | --- | --- | --- |
| Stefan Weinzierl and Fabian Brinkmann (TU Berlin) | Master | Led the BRAS benchmark of simulation against measurement and the plausibility/authenticity test paradigms; hold the instrument-directivity database you will need | Funded lab, anechoic chamber | Rich: peer-reviewed papers, open data |
| [Nikunj Raghuvanshi](https://www.microsoft.com/en-us/research/people/nikunjr/) (Microsoft Research) | Positive deviant | Shipped wave acoustics in Gears of War 4 on a fraction of one core by encoding a few perceptual parameters; Triton became Project Acoustics | Microsoft compute, a AAA partner | Rich: thesis, papers, GDC talk, podcast |
| Nicolas Tsingos (Dolby) | Within-domain | Perceptual culling and clustering of hundreds of sources (2004); beam tracing with Funkhouser; now Atmos rendering | INRIA, then Dolby | Papers; incidents moderate |
| Sean Olive (Harman) | Adjacent | Made listening-test evidence decisive inside a product company (speaker and headphone targets) | Harman's listening lab | Rich |

## Seat 2. Scene-to-response engine architect

**Accomplishment:** from user geometry and materials, computes a response that stays plausible against measured rooms and recomputes within the edit cycle. **For:** decide. **Typical performer:** shoebox image-source plus Sabine RT60, broadband absorption, no diffraction, never validated.

| Candidate | Role | Evidence of superior results | Non-practice advantages | Primary material |
| --- | --- | --- | --- | --- |
| Lauri Savioja (Aalto) | Master | One of the first interactive auralisation systems (DIVA), the canonical survey of geometric methods, the acoustic rendering equation, GPU wave solvers | Academic career | Papers; incident narratives thin |
| Michael Vorländer (RWTH Aachen) | Master | The Auralization textbook, the RAVEN hybrid engine, the round robins that exposed where simulation fails | Institute scale, measurement gear | Rich |
| [Lakulish Antani](https://endeavors.unc.edu/?p=2543) (Valve) | Positive deviant | Co-founded Impulsonic from UNC research in 2011, bought by Valve in January 2017 and continued as Steam Audio; hybrid reverb and pathing built under Half-Life: Alyx; whole SDK [open-sourced under Apache 2.0](https://gamefromscratch.com/valve-open-source-steam-audio/) | UNC lineage, Valve's resources after 2017 | Rich, including the source code and issue history |
| [Finnur Pind](https://www.cbinsights.com/company/treble-technologies) (Treble, Reykjavik) | Positive deviant, hard end | Hybrid wave-FEM plus geometric engine as a Python SDK; [L-Acoustics partnership](https://www.l-acoustics.com/fr/?p=609987) in February 2025; founded 2020, [€15 million Series A](https://www.preqin.com/data/profile/asset/treble-technologies-ehf-/454856) in September 2026. Caveat: serves architects and AI-data buyers, not DAWs; evidence is traction more than audited accuracy | Venture funding, Nordic research ties | Moderate |
| Marcos Fajardo (Arnold renderer) | Adjacent | Bet on the brute-force physically correct algorithm and made it fast; the analogy for the wave-versus-geometric decision | Timing with hardware | Moderate: talks, interviews |

## Seat 3. Reverb and real-time rendering designer

**Accomplishment:** turns the response into early reflections and a late field that sound right, move smoothly and fit a DAW CPU budget. **For:** decide, critique. **Typical performer:** stock FDN that zippers on parameter change; convolution that clicks on IR swap.

| Candidate | Role | Evidence of superior results | Non-practice advantages | Primary material |
| --- | --- | --- | --- | --- |
| [Jean-Marc Jot](https://sites.google.com/site/jmmjot/) | Master | The 1991 AES paper with Chaigne on digital delay networks for artificial reverb; Spat's room engine, born when [Jullien and Warusfel's perceptual model met Jot's FDN](https://www.soundingfuture.com/en/article/ircam-spat-swiss-army-knife-immersive-audio-creation-and-performance); later EAX, DTS, Magic Leap | IRCAM | Rich: papers, manuals, keynotes |
| [Michael Carnes](https://www.mixonline.com/news/izotope-acquires-exponential-audio) | Master and deviant | Created Lexicon's 960L, PCM96 and plug-ins; founded Exponential Audio (R4, PhoenixVerb Surround, Symphony 3D, Stratus 3D) essentially alone; product line acquired by iZotope in April 2019, joining as Research Fellow | Lexicon pedigree, Hollywood network | Moderate: interviews, newsletters, manuals |
| Sean Costello (Valhalla DSP) | Positive deviant | Solo, perceptually tuned algorithms, and the richest public record of reverb design decisions in the industry (his blog). Cross-listed with Seat 7 | None notable beyond timing | Rich |
| Matthew Hill (Liquidsonics) | Positive deviant | One-developer convolution/algorithmic hybrids used in post. Company size: medium confidence, verify | Early access to the Bricasti M7 licence | Moderate: blog |

Alternates: Sebastian Schlecht (modern FDN theory), David Griesinger (Lexicon; perceptual contrarian).

## Seat 4. Delivery to the ear

**Accomplishment:** delivers the scene to the real listener, localised and externalised on headphones, correct on any speaker layout or object format. **For:** decide, critique. **Typical performer:** one generic HRTF, nearest-speaker panning, no headphone EQ, formats bolted on.

| Candidate | Role | Evidence of superior results | Non-practice advantages | Primary material |
| --- | --- | --- | --- | --- |
| Ville Pulkki (Aalto) | Master | VBAP and DirAC; the standard text on parametric spatial audio | Academic career | Rich |
| Franz Zotter and Matthias Frank (IEM Graz) | Master and deviant | The open-access Ambisonics book and the IEM Plugin Suite, whose RoomEncoder is the free baseline your product must beat | Institute backing | Rich: book, code, issue history |
| Brian Katz (Sorbonne/CNRS) | Binaural specialist | HRTF individualisation and externalisation research; SOFA community (Piotr Majdak as alternate) | CNRS lab | Rich |
| Richard Furse (Blue Ripple Sound) | Positive deviant | Solo developer of higher-order Ambisonics tools used in broadcast and VR for two decades | Early Ambisonics community ties | Moderate: docs, forums |

Incident source rather than exemplar: Michael Gerzon, Ambisonics' technical triumph and commercial failure.

## Seat 5. Real-time plugin architect

**Accomplishment:** ships a plugin that never glitches while geometry recomputation, a 3D UI and multichannel I/O run beside the audio thread, across hosts and OSes, from a one-person codebase. **For:** decide, critique code. **Typical performer:** allocations and locks on the audio thread, a UI that stalls audio, one host that crashes.

| Candidate | Role | Evidence of superior results | Non-practice advantages | Primary material |
| --- | --- | --- | --- | --- |
| Timur Doumler | Master | Codified the audio-thread rules the industry now treats as law; JUCE; ISO C++ committee | JUCE platform as a stage | Rich: talks |
| Ross Bencina | Positive deviant | AudioMulch alone for over twenty years; PortAudio; the canonical "time waits for nothing" essay | None notable | Rich: essays |
| Urs Heckmann (u-he) | Positive deviant | Small team, complex plugins with a reputation for stability across hosts; two decades of engineering notes on KVR | Early synth-plugin market timing | Rich: forum posts |
| Julian Storer | Master | JUCE's creator; the framework decisions most plugin companies inherited; Tracktion | Framework-author vantage point | Moderate: talks |

Alternate: Miller Puckette (Pure Data). Cross-reference Antani (Seat 2) for how a propagation engine coexists with real-time audio.

## Seat 6. 3D-canvas product designer

**Accomplishment:** lets a non-acoustician build a space and place sources in minutes, trust the result and automate it in a DAW. **For:** decide, critique. **Typical performer:** raw physics controls per wall per band, a 3D view as decoration, automation an afterthought.

| Candidate | Role | Evidence of superior results | Non-practice advantages | Primary material |
| --- | --- | --- | --- | --- |
| [Nuno Fonseca](https://www.soundonsound.com/music-business/sound-particles-podcast) (Sound Particles, Leiria) | Positive deviant, closest precedent | Former professor; founded 2016; a 3D CGI-like canvas with virtual microphones now used across major Hollywood studios (Dune, Game of Thrones, Star Wars); team of over 30; [Cinema Audio Society nomination](https://blog.soundparticles.com/interview-with-nuno-fonseca) for Outstanding Product. Cross-listed with Seat 7 | Academic salary cushion, timing with immersive formats | Rich: interviews, podcasts, talks |
| Olivier Warusfel and Thibaut Carpentier ([IRCAM Spat](https://www.soundingfuture.com/en/article/ircam-spat-swiss-army-knife-immersive-audio-creation-and-performance)) | Master of the control model | Thirty years iterating a perceptual interface (the "ingredients" and "recipe" model) with composers; spat5 documentation and release notes record the decisions | IRCAM | Rich |
| [Arjen van der Schoot](https://www.asoundeffect.com/indoor-reverb-plugin) (Audio Ease) | Master of trust-first spatial UX | In Indoor, clicking a square moves the speaker and clicking an egg moves the microphone, and the team chose to [move the world rather than turn the mic](https://audioease.com/indoor/files/Indoor-five-page-manual.pdf); [click-free automation, zipper-free motion](https://www.frontendaudio.com/audio-ease-indoor-2-plug-in/). Cross-listed with Seat 7 | Altiverb's installed base and IR library | Rich: interviews, manual, videos |
| Floris Klinkert (FabFilter) | Master of pro-audio UX | Pro-Q set the benchmark for direct manipulation in plugins | Co-founder with a strong engineer partner | Moderate: interviews |
| Brent Burley (Disney) | Adjacent | The principled BRDF reduced physical material models to a few artist-intuitive parameters; the template for exposing acoustic materials | Disney's production pipeline | Rich: paper, course notes |

Alternates: Peter Neubäcker (Melodyne), Dietz Tinhof (VSL MIR Pro 3D), SketchUp's founders for accessible 3D authoring.

## Seat 7. Indie deep-tech plugin founder

**Accomplishment:** makes a one-person plugin company sustainable against free and incumbent tools, from outside the industry hubs. **For:** decide, advise. **Typical performer:** launches at $149 against free tools with a feature list, discounts in panic within a year.

| Candidate | Role | Evidence of superior results | Non-practice advantages | Primary material |
| --- | --- | --- | --- | --- |
| Sean Costello (Valhalla DSP) | Positive deviant | Flat pricing, no copy protection, trust built by publishing the craft; fifteen-plus years solo. Cross-listed with Seat 3 | Early mover in the affordable-plugin wave | Rich: blog |
| [Arjen van der Schoot](https://www.asoundeffect.com/indoor-reverb-plugin) (Audio Ease, Utrecht) | Master | Altiverb, the first convolution reverb plug-in; still independent after 25 years; [Indoor 2 priced around €700](https://www.milkaudiostore.com/ie/shop/audio-ease-indoor-2) for a defined post market. Cross-listed with Seat 6 | Category creation before competitors existed | Rich |
| [Nuno Fonseca](https://tech.eu/brief/portugals-sound-particles-raises-e400000-for-its-3d-audio-tech/) (Sound Particles) | Positive deviant | €400,000 seed round led by Indico Capital; [growth of about 70% a year](https://www.forbespt.com/sound-particles-cresce-de-70-ao-ano-e-aposta-em-novos-produtos-de-massas) while deferring the next round; his own [regret at doubting that Hollywood would buy from a small Portuguese town](https://blog.soundparticles.com/interview-with-nuno-fonseca). Cross-listed with Seat 6 | Academic cushion; a Skywalker Sound contact early | Rich |
| Achim Fell and Christian Sander (Dear Reality) | Within-domain | The spatial-specific plugin company (dearVR) that became part of Sennheiser in 2019: the exit-route incident. Medium confidence, verify | German pro-audio network | Moderate |

Alternates: Matthew Hill (Liquidsonics), Olli Keskinen (oeksound, Finland), Helmuts Bēms (Sonarworks, Riga). Finnur Pind (Seat 2) if venture funding is ever on the table.

## Seat 8. Spatial storyteller (the expert user)

**Accomplishment:** uses acoustic space to make audiences believe and feel, in film, games and music, and so defines the workflows the tool must serve. **For:** critique. **Typical performer:** reverb as a wet knob, space as decoration, no point-of-view logic.

| Candidate | Role | Evidence of superior results | Non-practice advantages | Primary material |
| --- | --- | --- | --- | --- |
| Walter Murch | Master | Worldizing (re-recording sound through speakers in real spaces for American Graffiti); Apocalypse Now's multichannel mix; unusually rich process writing | Coppola's circle at the right moment | Rich: books, essays, interviews |
| Randy Thom (Skywalker Sound) | Master | "Designing a Movie for Sound" and decades of essays on when space serves story; Academy Awards | Skywalker Sound's facilities | Rich: essays, talks |
| Martin Stig Andersen (Limbo, Inside) | Positive deviant | Tiny team, BAFTA-winning audio; space and tone carrying narrative. Medium confidence | Playdead's creative freedom | Moderate: talks |
| One immersive music mixer, chosen in Phase 1 (Alan Meyerson or Giles Martin are candidates) | Within-domain | Grammy-recognised Atmos and score mixing | Major-label and studio access | Interviews |

## Seat 9 (optional). Room acoustician

**Accomplishment:** predicts which real-room geometry and material choices change what people hear; validates presets and the material library. **For:** critique, advise. Fold into Seat 2's slate unless you sell to architects.

| Candidate | Role | Evidence of superior results | Non-practice advantages | Primary material |
| --- | --- | --- | --- | --- |
| Leo Beranek | Master, incident-rich | The Philharmonic Hall (1962) failure and recovery; subjective ratings against measures across a hundred halls | Postwar institutional standing | Rich: his own books, oral histories |
| David Griesinger | Master, contrarian | Lexicon, LARES, perceptual room acoustics and a sustained critique of standard measures | Lexicon's platform | Rich: his own site |
| Trevor Cox and Peter D'Antonio | Specialists | Absorbers and diffusers, the science and its commercialisation (RPG) | University lab; manufacturing | Rich: textbook |
| Yasuhisa Toyota (Nagata Acoustics) | Master | Disney Hall, Elbphilharmonie; results undisputed, written process thin, so a downgrade candidate | Nagata's model-building resources | Moderate: interviews |

## Build order

Build the seats in the order their judgement changes the least reversible decisions.

1. **Seat 1, perceptual gatekeeper.** It rewrites scope before code is spent, and its validity map becomes the acceptance test for every other seat.
2. **Seat 2, engine architect.** The hybrid and precompute decisions are the hardest to undo.
3. **Seat 5, plugin architect.** Topology (central renderer or per-track), threading, formats.
4. **Seat 6, canvas designer.** Control model and DAW integration.
5. **Seat 7, founder.** Pull forward if the PRD's target user is still open, since positioning decides which seats matter.
6. **Seats 3 and 4** as the engine matures.
7. **Seat 8** before beta.
8. **Seat 9** only if needed.

## Where to start

The first chat builds the perceptual gatekeeper; each remaining seat gets its own chat. Phase 0 intake needs only what cannot be researched:

- [ ] The target user and output formats already fixed in the PRD
- [ ] Any other hard constraints (budget, hosts, timeline)
- [ ] Exemplars already in mind for this seat

## Sources

Pages surfaced in the research behind this slate, checked at summary level only; every claim drawn from them gets re-verified against the full page in its seat's Phase 1.

- [Spat 4 user manual](https://www.scribd.com/document/650742616/Spat4-UserManual1) and [Ircam Spat overview](https://www.soundingfuture.com/en/article/ircam-spat-swiss-army-knife-immersive-audio-creation-and-performance): perceptual control model, FDN origins
- [Jean-Marc Jot, publications](https://sites.google.com/site/jmmjot/): 1991 FDN paper, 2023 externalised binaural rendering
- [Parametric Wave Field Coding](https://microsoft.com/en-us/research/wp-content/uploads/2016/07/ParametricWaveField.pdf), [Triton, JASA 2017](https://sonicfield.org/library/triton-practical-pre-computed-sound-propagation-for-games-and-virtual-reality), [GDC 2017 session](https://www.gdcvault.com/play/1024008/), [Raghuvanshi at Microsoft Research](https://www.microsoft.com/en-us/research/people/nikunjr/)
- [HoRNet Spaces MK2](https://rekkerd.org/hornet-plugins-releases-spaces-mk2-room-based-reverb-effect-plugin/), [Audiocube Space](https://mixdownmag.com.au/news/product/audiocube-space-puts-a-3d-acoustic-space-inside-your-daw/), [THALM and Soundly Place It](https://www.production-expert.com/production-expert-1/tunary-instruments-thalm-place-music-in-another-room-using-geometry-now-with-aax-support): current competitors
- [iZotope acquires Exponential Audio](https://www.mixonline.com/news/izotope-acquires-exponential-audio): Michael Carnes
- [Sound Particles podcast, Sound On Sound](https://www.soundonsound.com/music-business/sound-particles-podcast), [interview with Nuno Fonseca](https://blog.soundparticles.com/interview-with-nuno-fonseca), [seed round](https://tech.eu/brief/portugals-sound-particles-raises-e400000-for-its-3d-audio-tech/), [Forbes Portugal on growth](https://www.forbespt.com/sound-particles-cresce-de-70-ao-ano-e-aposta-em-novos-produtos-de-massas)
- [Treble Technologies profile](https://www.cbinsights.com/company/treble-technologies), [Preqin funding record](https://www.preqin.com/data/profile/asset/treble-technologies-ehf-/454856), [L-Acoustics partnership](https://www.l-acoustics.com/fr/?p=609987), [WASPAA 2025 demo paper](https://www.waspaa.com/waspaa25/proceedings/WASPAA2025-295.pdf)
- [Indoor review, Pro Tools Expert](https://www.pro-tools-expert.com/video-reviews/2016/11/20/review-indoor-by-audio-ease-part-one), [Indoor in Mix](https://www.mixonline.com/?p=13894), [Indoor five-page manual](https://audioease.com/indoor/files/Indoor-five-page-manual.pdf), [Arjen van der Schoot interview](https://www.asoundeffect.com/indoor-reverb-plugin), [Indoor 2 listing](https://www.frontendaudio.com/audio-ease-indoor-2-plug-in/), [Indoor 2 price](https://www.milkaudiostore.com/ie/shop/audio-ease-indoor-2)
- [UNC on Impulsonic and Valve](https://endeavors.unc.edu/?p=2543), [Steam Audio tool page](https://soundingfuture.com/tools/steam-audio), [Steam Audio open-source release](https://gamefromscratch.com/valve-open-source-steam-audio/)
