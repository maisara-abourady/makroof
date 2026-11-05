# Interrogation ledger

Adversarial reviews of the PRD, BUILD_PLAN and phase files against the reference corpus
(`docs/corpus/`, git-ignored, supplied locally). Each section is one `/interrogate` run.
Citations name sections, equations and figures as numbered in the corpus files; evidence is
paraphrased (no quote over 25 words).

Corpus short names: **Vorländer** = `auralization_compressed.md`; **Begault** = `begault_compressed.md`;
**Blauert Ch.n** = `blauert_spatial_hearing_chN_compressed.md`; **Immersive Sound** =
`immersive_sound_compressed.md`; **Toole** = `sound-reproduction_compressed.md`; **Zotter & Frank** =
`1007063_compressed.md`; **Spatial Audio** = `spatial_audio_compressed.md`.

## docs/PRD.md — 2026-11-05

### Issue ledger

| id | claim | evidence | severity | question | status |
|---|---|---|---|---|---|
| P1 | Atmosphere is not modelled; temperature, humidity and wind are out of scope (Key decisions; Out of scope) | CONTRADICTED. Vorländer §3.6 Eq. 3.33–3.35; §4.4.1 Eq. 4.32/4.34; §11.7 Eq. 11.50 (H_air term); Blauert Ch.2 §2.3.2 "Physical cues by SS distance"; Begault Ch.3 "Spectral Changes and Sound Source Distance". Air attenuation is part of every BRIR component and of the reverberation formula (4mV term). | minor (was blocker) | Q1 | resolved |
| P2 | Outdoor presets (festivals, mountains, fields) come from the same generic engine; wind and temperature excluded (FR-3D-3, Out of scope) | OUTSIDE MODEL VALIDITY. Vorländer §3.5 Eq. 3.30: refraction is essential outdoors and strongly affects long-distance propagation; Begault Ch.3 Table 3.1: wind and ground cover change the spectrum of a source 100 m away. Condition: short ranges in homogeneous, still air. | major | Q4 | open |
| P3 | Binaural mode reaches "highest achievable accuracy" with no head tracking and no head-orientation control (Overview, Key decisions, Out of scope) | CONTRADICTED. Blauert Ch.5 §5.2 "Static limitation and head tracking"; Vorländer §15.1.1, §16.1; Immersive Sound Ch.4 "Inside-the-Head Locatedness", Fig. 4.14. Static binaural gives front–back reversals and inside-the-head locatedness; head tracking is the named remedy. | blocker | Q3 | open |
| P4 | The listener always faces the sources (FR-3D-9) | SUPPORTED only as a convention (Vorländer §11.7, text after Eq. 11.50). Risk: a single source sits at 0° azimuth, where Begault Ch.2 Fig. 2.32 reports the most front–back reversals with non-individual HRTFs; forced reorientation by automation is not addressed (Begault Ch.2 "Head Movement and Source Movement Cues"). | major | Q3 | open |
| P5 | A1: with several sources, the listener faces their centre point | UNSOURCED | minor | — | open |
| P6 | A personalised head/ear profile can be made from ear photos or measurements (FR-SIM-4, Q6) | SUPPORTED. Immersive Sound Ch.4 "Advanced HRTF Techniques", Fig. 4.15 (photo-based modelling exists; acoustic measurement most accurate); Vorländer §16.1.2 (individual filters cut localisation errors, mainly above 6 kHz). No accuracy figure for photos in the corpus. | minor | — | open |
| P7 | Headphone mode accuracy; PRD silent on headphone equalisation (FR-SIM-3/4) | OUTSIDE MODEL VALIDITY. Vorländer §16.1.1–16.1.2; Blauert Ch.2 §2.3.2 "IHL". Condition: the headphone-to-ear path must be equalised or the benefit of an individual HRTF is lost. | major | — | open |
| P8 | Speaker mode assumes neutral playback with no user-room calibration (FR-SIM-5, Q7) | CONTRADICTED. Vorländer §16.2.4 "Dynamic cross talk cancellation" (offsets of ~2 cm audibly distort a static CTC); Immersive Sound Ch.5 "Background and Motivation", "Analytical BACCH Filter Design Strategy" (>20 dB crosstalk cancellation needed; geometry is a filter input); Toole §4.3.1 (room and positions dominate below ~300 Hz); Begault Ch.2 "Head Movement…". | major (was blocker) | Q2 | open |
| P9 | Any valid scene renders correctly from one generic engine, including cars, small rooms and halls (NFR-8, FR-SIM-2, FR-3D-3, Q2) | OUTSIDE MODEL VALIDITY. Vorländer §11.1 (geometrical acoustics valid in large rooms above the Schroeder frequency, broadband signals); §11.3.3 (50–200 m³ rooms below 200 Hz at the method's limit); Toole §4.3.1 (cabin resonances in cars matter to much higher frequencies). Condition: room dimensions ≫ wavelength. | major | Q4 | open |
| P10 | Per-surface properties are absorption, reflectivity and permeability (FR-3D-4, Q3) | Partly CONTRADICTED. Vorländer §3.3.2 Eq. 3.23–3.24 (reflected energy 1−α, so reflectivity duplicates absorption; scattering missing); §11.5, §11.6 (a scattering model is essential); permeability maps to transmission τ (§12.1). | major | — | open |
| P11 | Accuracy validated by matching measured IRs plus listening tests (NFR-1, Q9) | SUPPORTED. Vorländer §11.5 (agreement within 1–2 jnd achievable), Table 6.1; Blauert Ch.5 §5.2 "Perceptual validation". Condition: depends on absorption and scattering input data. | minor | — | open |
| P12 | Full scenes with objects, built in the editor or imported from 3D tools (FR-3D-1/2) | OUTSIDE MODEL VALIDITY. Vorländer §11.1.1 (CAD detail below ~0.5 m makes the model acoustically wrong); Blauert Ch.5 §5.2 "Perceptual validation" (fine detail pointless except near the source). | major | — | open |
| P13 | Speakers are generic and ideal (position only) by default (FR-3D-7) | OUTSIDE MODEL VALIDITY. Vorländer Eq. 11.50, Eq. 15.1 (source directivity term); Blauert Ch.5 §5.2 inputs (Fig. 5.4). Condition: reference source near omnidirectional. | minor | — | open |
| P14 | No audience; spaces always empty | OUTSIDE MODEL VALIDITY. Blauert Ch.5 §5.2 lists audience among modelled objects; Vorländer Annex (Ch.17) audience absorption and seating scattering tables. Condition: reference IRs measured unoccupied. | minor | — | open |
| P15 | Automated listener and source movement renders without audible artifacts (FR-SIM-6) | OUTSIDE MODEL VALIDITY. Blauert Ch.5 §5.2 "VR vs. room simulation" (moving scenes are time-variant; Doppler cannot be represented by IRs and is needed at high speeds); Vorländer §3.7; §15.1.1 "Fast convolution" (filter fading trades clicks against colouration). | major | Q5 | open |
| P16 | Movement stays smooth despite heavy processing (NFR-3, Q4) | SUPPORTED. Vorländer §15.3 Table 15.1 (update intervals by type of change); Blauert Ch.5 §5.2 "Real-time demands". | minor | — | open |
| P17 | Heavy CPU load and latency are acceptable (NFR-2, Q10) | UNSOURCED for a DAW with latency compensation; corpus limits (Vorländer Ch.15 intro) concern interactive systems. | minor | — | open |
| P18 | Single L/R pair, stereo track through a multi-speaker layout, multi-stem scenes in one shared scene (FR-3D-6, FR-SIM-7); binaural or stereo output (FR-SIM-3) | SUPPORTED by superposition: Blauert Ch.2 "Notation and scope"; Ch.5 §5.2 "Clarifications"; Vorländer §16.1, §16.2.4. Phantom images shift toward the nearer speaker off-axis (Blauert Ch.3 §3.1.1–3.1.2; Zotter & Frank §2.2.9 Fig. 2.9) — correct physics, not a defect. | minor | — | open |
| P19 | The engine derives sound from geometry and materials alone, never presets (Overview, FR-SIM-2) | SUPPORTED. Blauert Ch.5 §5.2 "Binaural room simulation"; Vorländer §15.2.3. Note Eq. 11.50 also needs source directivity, air attenuation and the HRTF. | minor | — | open |

**Out of corpus scope** (never blockers): VST3/AU in any DAW (NFR-4); macOS and Windows; scene
storage in the DAW project, no export (FR-LIC-1, NFR-6); licensing, trial and lapse behaviour
(FR-LIC-2..4, NFR-7); price and subscriber targets; 3D tech stack (NFR-5, Q12); import formats (Q11);
instance sharing mechanics (Q13); latency reporting (NFR-2); automatable parameters (FR-3D-8);
versioned contract (FR-SIM-1, FR-3D-10, Q1); local vs cloud compute (Q5); bounce through the DAW (A4);
Max for Live and multichannel output exclusions; team and timeline.

### Questions (interrogator, highest risk first)

1. **Q1 (P1)** Does "Atmosphere not modelled" mean no air absorption at all (H_air = 1, m = 0 in
   Vorländer Eq. 4.32/11.50), or only that temperature, humidity and wind are not user-controlled while a
   fixed standard air absorption stays in? Test: render a 50 m direct path and check the 8 kHz octave is
   attenuated beyond 1/r; compare large-hall T at 4–8 kHz with and without the 4mV term.
2. **Q2 (P8)** In stereo-speaker mode, is the output binaural with crosstalk cancellation? If so, for
   what span and distance, given no calibration? Test: CTC level with a dummy head at the assumed geometry
   and at ±2 cm / ±10° offsets, against the >20 dB figure (Immersive Sound Ch.5).
3. **Q3 (P3/P4)** With a static head and the source held at 0° azimuth, what front–back reversal rate and
   externalisation rate must the Q9 listening test pass, and are they measured at all? Test: reversal % at
   0° against the non-individual baseline in Begault Fig. 2.32.
4. **Q4 (P9/P2)** Does NFR-8 include car interiors, small rooms below ~200 Hz and long-range outdoor
   paths? If yes, in which bands and by which metric (Vorländer §11.1, §11.3.3, §3.5)? Test: 63–250 Hz
   bands of a car or small-room render vs a measured IR, in jnd units (Table 6.1).
5. **Q5 (P15)** Must FR-SIM-6 reproduce Doppler shift? What maximum speed must render artifact-free, with
   which update intervals (Vorländer Table 15.1)? Test: automate a source at that speed, run the click
   detector and measure pitch shift against Eq. 3.37/3.39.

### Builder answers (round 0)

The builder answers from the current plan (`docs/BUILD_PLAN.md` §2–§3), which already holds defaults
for several of these. The PRD itself is not changed here.

**A1 (Q1, P1).** The plan reads "not modelled" as "not user-controlled": AX4 applies a fixed standard
atmosphere (20 °C, 50 % RH) and flag F6 records the conflict. The per-path loss follows Vorländer §3.6
Eq. 3.33–3.35 (exponential intensity loss, D = 4.34·m dB/m) and the tail decay uses the air term of
Eq. 4.32/4.34 (A = Σ Sᵢαᵢ + 4mV). Fig. 3.15 shows the absorption depends strongly on humidity between
about 1 and 10 kHz, so a single fixed RH is an approximation, not a model of a particular day. The
interrogator's test is accepted as stated: a 50 m direct path must lose 4.34·m·50 dB in the 8 kHz band
on top of 1/r, and a large-hall render's T at 4–8 kHz must follow Eq. 4.32 rather than Eq. 4.28.
Remaining: the PRD wording still reads as "no air absorption"; Maisara must confirm the AX4 reading.

**A2 (Q2, P8).** No. Speaker mode is not binaural plus CTC. AQ7 renders the scene through a virtual
near-coincident ORTF pair (two cardioids, ±55°, 17 cm; Spatial Audio Table 6.2, recording angle 95°) at
the listener, and plays the two signals as ordinary stereo. Localisation then comes from summing
localisation between the user's two loudspeakers: level and time differences between the loudspeaker
signals shift the phantom image (Blauert Ch.3 §3.1.1), and for inter-channel delays beyond about 1 ms the
first wavefront dominates (§3.1.2). CTC is rejected because a static CTC is audibly wrong after ~2 cm of
head offset and needs a tracked or fixed listener (Vorländer §16.2.4, "Dynamic cross talk
cancellation"), which contradicts "no calibration". Consequences the PRD should state: speaker mode
gives no rear or elevated images, only frontal phantom images inside the loudspeaker span, and below
roughly 300 Hz the user's own room dominates and is not corrected (Toole §4.3.1). Test: render a source
swept from −90° to +90° and check, with a dummy-head capture over a standard ±30° pair, that the
interaural cues move monotonically and stay within the span.

**A3 (Q3, P3/P4).** No head tracking is a product decision (PRD Out of scope), and v1 ships one generic
HRTF (AQ6), so the static, non-individual case is exactly the one the corpus warns about: front–back
reversals of about 47 % for speech at frontal targets with non-individual HRTFs (Begault Ch.2 Fig. 2.32),
and the most unexternalised judgments at 0° and 180° (Begault Ch.3, IHL discussion of Begault and Wenzel
1993). Vorländer §15.1.1 says room-related rendering with head tracking gives a large gain even with
non-individual HRTFs. The plan has one mitigation the corpus supports: every render includes the room, and
reverberation almost consistently improves externalisation of headphone 3-D sound (Begault Ch.3, Table
3.2), though it can reduce localisation accuracy. The builder cannot set the pass threshold; that is Q9
(Expert). Proposed test: listening test reporting front–back reversal % and unexternalised % at 0°, for a
dry render and a room render, compared with Begault Fig. 2.32 and Table 3.2. Remaining: the PRD claim
"highest achievable accuracy" needs the qualifier "without head tracking", or head tracking must come into
scope. That is Maisara's decision.

**A4 (Q4, P9/P2).** No. v1 is a shoebox image-source model plus a stochastic tail (AQ2), and flag F3
already says cars, chapels and terrain are not covered. Geometrical acoustics is valid only above the
Schroeder frequency (Vorländer §11.1, Eq. 4.13, f_S ≈ 1200·√(T/V); Toole §4.3.1 notes the formula tends
to underestimate the transition in small rooms), small rooms below 200 Hz are at the method's limit
(Vorländer §11.3.3), car cabins stay modal to much higher frequencies (Toole §4.3.1), and refraction,
needed outdoors, is not modelled (Vorländer §3.5). The plan's accuracy gates (AQ9) are averaged over
500 Hz–2 kHz for that reason. NFR-8's "any valid scene renders correctly" therefore needs a validity
statement (per band, per room size). Proposed test: per-band T30 and EDT error in jnd (Vorländer
Table 6.1) against a measured small-room IR, reported but not gated below the room's f_S.

**A5 (Q5, P15).** No Doppler in v1 (AX1): an IR change is a 30 ms equal-gain crossfade between two
convolvers, rebuilt at most once per 20 ms (AQ4). The corpus says Doppler is needed at "sufficiently high"
speeds without a number (Blauert Ch.5 §5.2). For scale, Eq. 3.37 at the 30–50 cm/s translation speeds of
Vorländer §15.3 gives a frequency ratio of about 1.0015 (≈2.5 cents). The corpus gives no pitch-change
threshold to compare it with (Vorländer §6.2.7 has none), so a maximum artifact-free speed cannot be
sourced. Vorländer §15.1.1 warns that fading between IRs trades clicks against colouration. Proposed test:
automate a source at a speed Maisara or the Expert names, run the click detector, and report the
colouration of the crossfade (comb-filter depth) at the largest direct-path delay jump per update.
Remaining: the maximum speed is a product/Expert number.

### Round 1 (interrogator on open blockers P1, P3/P4, P8)

| id | verdict | severity now | citation check | reason | follow-up |
|---|---|---|---|---|---|
| P1 (A1) | RESOLVED (acoustics); PRD wording still needs Maisara's confirmation | minor | All correct (Vorländer §3.6 Eq. 3.33–3.35, Fig. 3.15; §4.4.1 Eq. 4.28, 4.32, 4.34). | A fixed standard atmosphere on every path and on the tail matches the corpus; the test is falsifiable, but its expected value is not pinned: 50 % RH at 20 °C sits on the edge of two rows of the Vorländer Annex (Ch.17) "Air attenuation coefficient" table. | Which row does AX4 use (8 kHz: 20.3 vs 13.5 ·10⁻³ m⁻¹, i.e. ≈4.4 vs ≈2.9 dB over 50 m), and with what tolerance? |
| P8 (A2) | OPEN (approach sound, test inadequate) | major (was blocker) | All correct (Spatial Audio Table 6.2; Blauert Ch.3 §3.1.1, §3.1.2; Vorländer §16.2.4; Toole §4.3.1). | Dropping CTC removes the contradiction, but a 95° recording angle maps sources beyond about ±47.5° onto the loudspeakers, so "monotonic over ±90°" is the wrong expectation, and time-difference localisation is frequency-dependent and can leave the span (Blauert Ch.3 §3.1.1). The direct-sound inter-channel delay of a 17 cm pair stays in the summing range, so the >1 ms precedence remark does not apply to it. | How far off the centre line can the listener sit before a centred source collapses into one loudspeaker (Blauert Ch.3 §3.1.2: 630 µs–1 ms)? Test: dummy-head capture at 0, 10, 20, 30 cm lateral offset. |
| P3/P4 (A3) | OPEN (pass threshold pending Q9 / Maisara) | P3 blocker; P4 major | Mostly correct. Begault Fig. 2.32: the 47 % is the mean; at 0° it is about 59 %, so A3 understated the P4 risk. Fig. 3.10, Table 3.2 and Vorländer §15.1.1 confirmed. | A3 accepts the corpus but changes neither the claim nor the scope and sets no threshold. Its mitigation (always render the room) has a side effect at 0°: Begault Fig. 3.17 shows reverberant-minus-dry azimuth error of about +32° there. | Will the Q9 test also measure absolute azimuth error at 0°, dry and room, with a pass limit, so a gain in externalisation cannot hide a ~30° localisation loss? |

**Builder replies to the round-1 follow-ups**

- **P1.** The corpus table brackets the AX4 atmosphere (20 °C, 50 % RH) between its "20°, 30–50%" and
  "20°, 50–70%" rows (Vorländer Annex, Ch.17). The test that can be checked against the corpus is therefore
  a bracket: the extra 8 kHz loss over 50 m must lie between ≈2.9 and ≈4.4 dB (4.34·m·50 m), and the 4 kHz
  loss between ≈0.9 and ≈1.3 dB. The exact ISO 9613-1 value AX4 names is outside the corpus. Status
  **resolved**; the PRD wording ("not modelled") is left for Maisara.
- **P8.** Accepted: the expectation follows the ORTF recording angle (Spatial Audio Table 6.2, 95°). Test:
  a broadband source swept in the scene must move the captured interaural cues monotonically for
  |azimuth| ≤ ≈47.5° and saturate at the loudspeaker beyond; band-limited stimuli are reported, not gated
  (Blauert Ch.3 §3.1.1). On the sweet spot: by the 630 µs–1 ms figure (Blauert Ch.3 §3.1.2), a builder's
  geometric estimate for a ±30° pair gives a collapse after roughly 20–35 cm of lateral offset (arrival
  difference ≈ offset/c); this is arithmetic, not a corpus number, and the offset test above is adopted
  to measure it. Speaker mode is then a sweet-spot stereo image, which the PRD should say. Status
  **open (major)**: a product statement, not a further acoustic question.
- **P3/P4.** Correction accepted: at 0° the non-individual front–back reversal rate is about 59 %
  (Begault Fig. 2.32). The proposed Q9 test is extended to report, for a 0° source, dry and room renders:
  front–back reversal %, unexternalised % (Begault Fig. 3.10, Table 3.2) and absolute azimuth error
  (Begault Fig. 3.17). The builder cannot supply pass limits (Q9, Expert) or head tracking (PRD Out of
  scope). Status **open (blocker)**.

### Round 2 (interrogator on the remaining blocker P3/P4)

| id | verdict | severity now | citation check | reason | follow-up |
|---|---|---|---|---|---|
| P3/P4 | OPEN. P3 now rests only on product decisions; P4's measurement set had protocol gaps | P3 blocker (until the PRD qualifies its wording or brings head tracking into scope); P4 major | All correct. Begault Fig. 2.32 (≈59 % front–back reversals at 0°); Fig. 3.10 (0°: ≈32 % intracranial, ≈47 % with verged-cranial); Table 3.2 (pooled IHL, dry vs reverberant, no per-azimuth values); Fig. 3.17 (≈+32° reverb-minus-dry azimuth error at 0°); Vorländer §15.1.1. | The corpus has nothing more to give on P3: Vorländer §15.1.1 names head tracking as the remedy, so the conflict with "highest achievable accuracy" closes only through a qualifier or a scope change; pass limits are Q9. The P4 measurements are falsifiable only if the protocol matches the baselines: (a) the baselines use speech, and white noise is almost always externalised (Begault Ch.3, Wenzel et al. 1993); (b) "unexternalised" moves by ~15 points at 0° depending on whether verged-cranial counts (Fig. 3.10); (c) Fig. 3.17 is a difference, not an absolute error, and Table 3.2 has no 0° value; (d) at 0° an unscored reversal reads as a ~180° azimuth error. | Will the Q9 test use speech, count unexternalised as intracranial plus verged-cranial, and score reversals before computing azimuth error, so each 0° result compares with ≈59 %, ≈47 % and ≈+32°? |

**Builder reply to the round-2 follow-up (P4)**

Yes to all three. The proposed test uses speech; scores front–back reversals first (folding across the
interaural axis, as Begault Ch.2 describes for "reversal-corrected" judgments) and then computes azimuth
error on the folded judgments; counts unexternalised as intracranial plus verged-cranial (Begault Fig. 3.10);
and compares dry vs room renders in two separate ways: per-azimuth at 0° against Fig. 2.32, Fig. 3.10 and the
Fig. 3.17 difference, and pooled across azimuths against Table 3.2. The two studies' numbers are not combined
into one baseline. This closes the protocol question from the corpus side. Pass limits stay with the Expert
(Q9). No round 3 was run: the interrogator stated that nothing more on P3 can be answered from the corpus.

### Status after round 2

| id | severity | status | what closes it |
|---|---|---|---|
| P1 | minor (was blocker) | resolved | Acoustics settled (AX4 reading, bracketed test). Maisara to confirm that "Atmosphere: not modelled" means "not user-controlled". |
| P3 | blocker | open | Maisara: qualify "highest achievable accuracy" as "without head tracking", or bring head tracking into scope; Expert: Q9 pass limits. |
| P4 | major | open | Q9 pass limits for the agreed 0° protocol; Maisara to confirm FR-3D-9 / A1 given F8. |
| P8 | major (was blocker) | open | Maisara: PRD to state that speaker mode is a sweet-spot stereo image (no rear/elevated images, room below ~300 Hz uncorrected). |
| P2, P9 | major | open | Not re-run (not blockers). A4 proposes a per-band, per-room-size validity statement for NFR-8; product decision. |
| P15 | major | open | Not re-run. Maximum artifact-free movement speed is a product/Expert number (A5). |
| P7, P10, P12 | major | open | No question asked; builder notes: P10 already handled by AQ3/F5 (absorption + scattering, no reflectivity); P7 and P12 have no plan answer yet. |
| P5, P6, P11, P13, P14, P16–P19 | minor | open | No question asked; no action taken in this run. |
