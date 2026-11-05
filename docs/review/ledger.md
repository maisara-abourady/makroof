# Interrogation ledger

Adversarial reviews of the PRD, BUILD_PLAN and phase files against the reference corpus
(`docs/corpus/`, git-ignored, supplied locally). Each section is one `/interrogate` run.
Citations name sections, equations and figures as numbered in the corpus files; evidence is
paraphrased (no quote over 25 words).

Corpus short names (files in `docs/corpus/`, fetched from `maisara-abourady/audio-resources` by
`tools/ci/fetch_corpus.sh`; revision 22dc9dd for the 2026-11-05 runs, same texts as the earlier local
upload): **Vorländer** = `vorlaender-auralization.md`; **Begault** = `begault-3d-sound-vr-multimedia.md`;
**Blauert Ch.n** = `blauert-chN-*.md`; **Immersive Sound** = `roginska-geluso-immersive-sound.md`;
**Toole** = `toole-sound-reproduction.md`; **Zotter & Frank** = `zotter-frank-ambisonics.md`;
**Spatial Audio** = `rumsey-spatial-audio.md`.

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

## docs/BUILD_PLAN.md — 2026-11-05

First run under the revised interrogator (scientific correctness: items sorted into FACT / NUMBER /
DECISION / SOFTWARE; verdicts CORRECT / WRONG / CONDITIONS VIOLATED / IMPRECISE / NOT CHECKABLE /
INCONSISTENT / CONSEQUENCE; severity by scientific error; arithmetic from corpus equations allowed).
Worked examples use c = 343.2 m/s (Vorländer Eq. 1.20, 20 °C) and the Vorländer Annex air row
"20°, 50–70%"; room sizes marked "e.g." are the interrogator's own picks.

### Issue ledger

| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| B1 | NUMBER | Phase 09 gate: an emitter at +55° gives the maximum L/R level difference (ORTF cardioids at ±55°) | WRONG | Spatial Audio §6.2.1 cardioid 0.5(1+cos ϑ). Working: at +55° L=1, R=0.5(1+cos 110°)=0.329 → 9.7 dB; at +90° L=0.910, R=0.090 → 20.1 dB; at +125° R=0 → unbounded. The maximum is at 125° (90° on the front half), not 55°. | minor (was blocker) | Q1 | resolved |
| B2 | NUMBER | Phase 03: "scattering removing (1−s) of specular energy" | WRONG (as written) | Vorländer §3.3.2 Eq. 3.23, Fig. 3.10: specular (1−α)(1−s), scattered (1−α)s, so scattering removes s and keeps (1−s); read literally the text leaves s. | minor (was blocker) | Q2 | resolved |
| B3 | FACT/NUMBER | F3 + AQ2: "outdoor field" = ground plane only (5 surfaces α=1.0) with the Eyring + air tail | CONDITIONS VIOLATED | Vorländer §4.4, §4.4.1 Eq. 4.32 assume a diffuse field and homogeneous absorption. Working (e.g. 100×100×10 m, ground α=0.1): mean α 0.625 (Eq. 4.30), T ≈ 0.67 s at 1 kHz — a reverberant tail for a scene expected to be nearly dry. | major | Q3 | resolved |
| B4 | FACT | AQ4/Phase 10: late tail cached when only positions change (AQ2: tail energy-matched to ISM at the mixing time) | CONDITIONS VIOLATED | Vorländer §15.3 Table 15.1: moves > 1 m need the scattering part updated; only after ≈140 ms can the receiver-specific reverberation be replaced by a statistical decay. Blauert Ch.5 "Real-time demands": translation needs full recalculation. | minor (was major) | Q4 | resolved |
| B5 | NUMBER | AX6: emitter ≥ 0.3 m from listener, rendered with a generic far-field HRTF (Phase 08) | CONDITIONS VIOLATED | Vorländer §9.5: standard HRTFs are distance-independent only beyond 1 m; Fig. 9.7 shows ILD growing below 1 m. Blauert Ch.2 §2.3.2: below 3 m head and pinna filtering depend on distance. | major | Q5 | open |
| B6 | FACT | AQ2: "ISM is exact for specular shoebox reflections" | CONDITIONS VIOLATED | Vorländer §11.3: exact only for \|R\|=1; with absorbing walls an approximation for non-grazing incidence. §11.3.3: errors > 1 dB at grazing angles > 60° within about one wavelength of a wall. Working: at the 0.1 m AX6 clearance, d ≤ λ in every band up to 2 kHz. | major | — | resolved |
| B7 | FACT | AQ2 hybrid ISM + Eyring for small rooms (Phase 12 living room, car-sized room; Phase 04 gate down to 250 Hz) | CONDITIONS VIOLATED | Toole §4.3.4: small rooms are not Sabine spaces. Vorländer §11.5, §10.1.3: energetic geometric methods hold above f_S. Working (Toole §4.3.1, f_c=2000√(T/V)): 60 m³ at 0.5 s → ≈183 Hz; 3.4 m³ at 0.1 s → ≈344 Hz, so 63–250 Hz are modal there. | major | — | open |
| B8 | NUMBER | AQ1 "1 broadband scattering coefficient" vs Phase 12 "per-band α and s from published tables" | INCONSISTENT | Vorländer Annex scattering tables are per octave band and vary strongly with frequency (e.g. 0.01 → 1.0); Fig. 3.11 0.07 → 1.03. | major | — | resolved |
| B9 | FACT | F8: under AX3 "sources can never be heard behind or beside the listener"; a circling source "will sound like nothing moves" | INCONSISTENT | AX3 faces the emitters' centroid, not each emitter. Working: listener at origin, L=(−5,1), R=(5,1) → L at 78.7° (beside); L=(−1,5), R=(1,−3) → R at 161.6° (behind). | major | — | resolved |
| B10 | NUMBER | AX11: one tail realisation scatters 4–7 % at 250 Hz for T60 ≤ 1 s | INCONSISTENT | AX11's own σ₁ table at 250 Hz: 8 % (0.3 s), 4.4 % (1.0 s), so 4.4–8 %; for a ±5 % gate R ≥ (8/1.667)² ≈ 23, not ≈ 18. | major | — | resolved |
| B11 | FACT | AX13: ±2.5 ms DRR window "keeps typical first reflections out" | WRONG | Working (image source, Vorländer Eq. 11.34): source and listener 1.2 m above the floor at distance r, floor delay (√(r²+2.4²)−r)/c = 2.45 ms at 3 m, 1.59 ms at 5 m; inside the window for any r > 2.93 m. | major | — | open |
| B12 | NUMBER | AX13 leakage bias ≈ −10·log10(1+f·10^(DRR/10)) dB; ≥ 99 % rule | IMPRECISE | Working: D'=(1−f)D, R'=R+fD give ΔDRR = 10log(1−f) − 10log(1+f·10^(DRR/10)); a term is missing. f=0.01: −0.09 dB at 0 dB, −0.46 dB at +10 dB, −3.05 dB at +20 dB, so 99 % does not bound the bias at high DRR. | minor | — | resolved |
| B13 | NUMBER | AQ9: T30 within ±10 % (≈2 JND) | IMPRECISE | Vorländer §6.4.4 Table 6.1 gives 5 % for EDT only; no T/T30 jnd in the corpus. | minor | — | resolved |
| B14 | NUMBER | AQ9: EDT ±10 % (≈2 JND), C80 ±2 dB (≈2 JND) | CORRECT | Vorländer Table 6.1: EDT 5 %, C80 1 dB; Fig. 11.33 note: clarity jnd revised from 0.5 to 1 dB. | none | — | resolved |
| B15 | NUMBER | AQ9: thresholds averaged over 500 Hz–2 kHz | IMPRECISE | Vorländer Table 6.1 states the jnds for 500–1000 Hz; the 2 JND equivalence is not stated for 2 kHz. | minor | — | resolved |
| B16 | FACT | AQ9 rationale: ≈2 JND is a common bar in round robins | IMPRECISE | Vorländer §11.5: Round-robin I, 3 of 17 programs reached jnd-level accuracy; Round-robin III reports 1–2 jnd as the achievable best, not a common bar. | minor | — | resolved |
| B17 | NUMBER | AQ2/Phase 04: per-band T60 from Eyring + air absorption | CORRECT | Vorländer §4.4.1 Eq. 4.32 (diffuse field, homogeneous absorption; see B3, B7). Working: constant 24 ln10/c = 0.1610 at 343.2 m/s vs the rounded 0.16 (c=340), a 0.6 % offset against the ±5 % gate. | none | — | resolved |
| B18 | FACT | Phase 04 risk: Eyring inaccurate for uneven absorption | CORRECT | Toole §4.1 Box; Vorländer §4.4.1 (homogeneous-absorption assumption). | none | — | resolved |
| B19 | NUMBER | AX4: 20 °C, 50 % RH, ISO 9613-1 | CORRECT | Vorländer Abbreviations name ISO 9613-1; 50 % RH sits on the edge of two Annex rows (4 kHz: 5.8 vs 4.1·10⁻³ m⁻¹); D = 4.34·m (Eq. 3.34). | none | — | resolved |
| B20 | FACT | F6: air absorption matters above about 2 kHz in large spaces | IMPRECISE | Working (Eq. 4.32, Annex m; 20×30×10 m, T=2 s): the 4mV term shortens T by 2.9 % at 500 Hz, 4.8 % at 1 kHz, 7.8 % at 2 kHz, 17 % at 4 kHz — already ≈1 EDT jnd at 1 kHz. | minor | — | resolved |
| B21 | NUMBER | Phase 03: per-band reflection factor √(1−α); α=1 → direct path only | CORRECT | Vorländer §11.3.2 Eq. 11.37. | none | — | resolved |
| B22 | NUMBER | Phase 03: 1/r spreading; AX2 direct path at 1 m = 0 dB | CORRECT | Vorländer §11.3.2 Eq. 11.36; §9.4 Eq. 9.3. | none | — | resolved |
| B23 | FACT | Phase 03: source↔receiver reciprocity; symmetric rooms give symmetric IRs | CORRECT | Vorländer §10.1.1 Eq. 10.9. | none | — | resolved |
| B24 | FACT | Phase 03 listening: echo pattern sparser and later as the room grows | CORRECT | Vorländer §4.4 Eq. 4.22 (n̄ = cS/4V). | none | — | resolved |
| B25 | NUMBER | AX1: a source 30 m away arrives 87 ms late | CORRECT | Vorländer §1.2 Eq. 1.20: 30/343.2 = 87.4 ms. | none | — | resolved |
| B26 | NUMBER | Phase 08: ITD 0.6–0.75 ms at ±90°; positive ILD above 2 kHz | CORRECT | Blauert Ch.2 §2.2.2 Fig. 2.30 (≈650 µs); Immersive Sound Ch.1 "Sound Localization in the Horizontal Dimension" (650 µs, 750 µs low-frequency); Vorländer §6.3.1 Fig. 6.7; Fig. 9.7. The 0.75 ms edge depends on the ITD estimator. | none | — | resolved |
| B27 | NUMBER | Phase 08: frontal \|ITD\| < 20 µs; tail coherence ±0.1; diffuse energy ±1 dB; ≤ 1 dB per 1° | NOT CHECKABLE | Vorländer §9.5: 1° frontal discrimination, no step threshold; Begault Ch.4 Fig. 4.42: one measured person ≈0.02 ms at 0°, exactly the gate limit. | none | — | open |
| B28 | DECISION | Phase 08: HRIR interpolation, nearest-neighbour then bilinear/spherical | CONSEQUENCE | Begault Ch.4 "Problems with Interpolation Algorithms" Figs. 4.39–4.40: time-domain interpolation without separating ITD gives double impulses and deeper notches; the ≤ 1 dB/1° gate would not catch it. | minor | — | open |
| B29 | NUMBER | AQ7: ORTF = two cardioids ±55°, 17 cm | CORRECT | Spatial Audio §6.2.4, Fig. 6.11. | none | — | resolved |
| B30 | FACT | AQ7: XTC needs a fixed sweet spot | IMPRECISE | Vorländer §16.2.4: with a head tracker and adaptive filtering the sweet spot can follow the listener; true only without tracking. | minor | — | open |
| B31 | FACT | AQ4: crossfading convolvers is the standard way to vary an IR without clicks | CORRECT | Vorländer §15.1.1 "Fast convolution", §9.2.1 (tuned against colouration and clicks). | none | — | resolved |
| B32 | DECISION | AQ4: 30 ms equal-gain crossfade | CONSEQUENCE | Vorländer §9.2.1: constant power across the overlap is required; equal gain gives it only for coherent outputs. Working: uncorrelated outputs at 0.5/0.5 → −3 dB at mid-fade (Phase 09 mode switch, Phase 10 corner jumps). | minor | — | resolved |
| B33 | NUMBER | AQ4: IR updates capped at one per 20 ms | CORRECT | Vorländer §15.3 (20 ms as printed; Table 15.1: 35 ms rotation, 700 ms for moves > 0.25 m); Blauert Ch.5: no single-number criterion. | none | — | resolved |
| B34 | NUMBER | AQ4 20 ms cap vs 30 ms fade (Phase 06) and ≤ 50 ms rebuild (AQ10) | IMPRECISE | Working: an uninterrupted 30 ms fade allows one IR per 30 ms and an order-30 rebuild one per 50 ms, so 20 ms is unreachable. | minor | — | resolved |
| B35 | NUMBER | Phase 04: mixing-time estimate | NOT CHECKABLE | Vorländer §11.7: no simple rule; §11.6.1 ≈100 ms; §15.3 140 ms. | none | — | open |
| B36 | FACT | AQ2: a statistical tail is the standard companion to ISM | CORRECT | Vorländer §11.6.1, §15.3; §11.6: scattered energy dominates after order 3–4. | none | — | resolved |
| B37 | DECISION | AQ1: 8 octave bands, 63 Hz–8 kHz | CONSEQUENCE | Working: top band edge 8k·√2 ≈ 11.3 kHz, while Begault Ch.3 "Spectral Changes…" says air absorption above 10 kHz is audible at ≈15 ft; Vorländer §11.7: coarse band data can ring when interpolated. | minor | — | open |
| B38 | FACT | AQ3: α in [0.01, 1.0] and broadband s are "the quantities in published material tables" | IMPRECISE | Vorländer Annex: α tables 125 Hz–8 kHz (no 63 Hz), s tables per band; Toole §4.3.3: measured α can exceed 1.0. | minor | — | open |
| B39 | FACT | F5/AQ3: reflectivity = 1−α, same quantity as absorption | IMPRECISE | Vorländer §11.3.2 Eq. 11.37: α fixes only \|R\|=√(1−α), the phase is separate; Eq. 3.23: specular energy (1−α)(1−s). | minor | — | open |
| B40 | NUMBER | Phase 04 IR length capped at 12 s; AX6 limits avoid "unbounded IR lengths" | IMPRECISE | Working (Eq. 4.32): 100 m cube, α=0.01 at 125 Hz → T ≈ 160 s; a 12 s IR reaches only −4.5 dB, and T30 needs T ≤ 20.6 s. Only the cap bounds length. | minor | — | resolved |
| B41 | FACT | F3: non-shoebox spaces and terrain need mesh geometry and diffraction | CORRECT | Vorländer §11.3.4, §11.6. | none | — | resolved |
| B42 | FACT | Phase 08 risk: front/back confusion and in-head localisation with a generic HRTF | CORRECT | Blauert Ch.5 "Static limitation and head tracking"; Immersive Sound Ch.4 "Inside-the-Head Locatedness" Fig. 4.14. | none | — | resolved |
| B43 | DECISION | AX3/AQ6: static yaw, no head tracking, generic HRTF | CONSEQUENCE | Immersive Sound Ch.4 Fig. 4.14: without tracking most listeners hear frontal sources behind or above, against the Phase 08 listening expectation that ±30° emitters sound in front and out of the head. | minor | — | open |
| B44 | DECISION | AQ8: omnidirectional point sources | CONSEQUENCE | Vorländer §11.7 Eq. 11.50 (H_source per path); Toole §4.3.5 (directivity changes reflections and decays). | minor | — | open |
| B45 | DECISION | AX1: no Doppler, IR switches crossfaded | CONSEQUENCE | Vorländer §15.1.1 (comb colouration when fading). Working (Phase 10, 1→15 m over 8 bars at 120 bpm = 0.875 m/s): 17.5 mm (51 µs) per 20 ms update, first notch 9.8 kHz mid-fade on unaligned paths. | minor | — | open |
| B46 | NUMBER | AX11: fluctuation "on a 1/B time scale (≈ 0.5·T/√(B·T))" | IMPRECISE | The text equates a time scale with a standard deviation; they differ by 0.5√(BT). As relative std 0.5/√(BT): 1.9 % (1 kHz, 1 s) vs 1.5 % measured, 3.4 % (0.3 s) vs 3.4 %. Vorländer §11.2.5 supports averaging repeated runs. | minor | — | resolved |
| B47 | NUMBER | AX11: R = 300/130/48/24 for the Phase 02 ±2 %/±5 % gate | NOT CHECKABLE | Working with R ≥ (σ₁/(tol/3))²: 63 Hz at ±2 % needs 729 (0.3 s) and 144 (1 s); the figures fit only if 63 Hz uses ±5 %; band split not stated; no σ₁ for 2.5 s. | none | — | open |
| B48 | NUMBER | Phase 12: living room T30 0.3–0.6 s | CORRECT | Toole §4.3.3 (0.36–0.4 s typical); Figs. 4.10–4.11 (0.32 s, 0.4 s). | none | — | resolved |
| B49 | FACT | Phase 07 / AX2: farther away = more room, less direct, quieter | CORRECT | Blauert Ch.3 §3.3; Immersive Sound Ch.1 "Reverberation Cues": beyond the critical distance overall level is roughly constant, so "quieter" applies to the direct sound. | none | — | resolved |
| B50 | NUMBER | AX13: ±2.5 ms window (Zahorik 2002) | NOT CHECKABLE | Zahorik 2002 appears only in the Immersive Sound reference list, no window value. | none | — | open |
| B51 | NUMBER | ±1 sample/±0.5 dB vs pyroomacoustics; −100/−120 dB gates; ±2 % across rates; ≤ 100 ms staleness; mono-sum notch ≤ 6 dB; ORTF diffuse coherence; BS.1770 ±1 dB; "robust on any neutral pair"; photo HRTF | NOT CHECKABLE | Not in the corpus. Pointers: Vorländer §6.4.5 Eq. 6.14 sin(kd)/kd is for omni points, not cardioids; Immersive Sound Ch.1 "HRTFs and Virtual Acoustics" lists fast individualisation, not photos. | none | — | open |

**SOFTWARE** (listed, not rated): toolchain and dependencies (C++20, JUCE 8, CMake/Ninja, PFFFT,
nlohmann/json, Catch2, Python tooling, pyroomacoustics as a dependency), pluginval/auval, CI matrix and
sanitizers, SOFA conversion and data licensing, contract boundary, AQ1 JSON/semver/axes, AQ5, AQ10,
AX5, AX7–AX10, AX12, F1, F4, F9, Phase 06 audio-thread rules and FFT precision, Phase 07 state and IDs,
Phases 00/01/11/13 engineering.

### Questions (interrogator, most severe first)

1. **Q1 (B1)** For cardioids 0.5(1+cos ϑ) at ±55°, at which azimuth is the Phase 09 gate meant to find the
   maximum L/R level difference (+55°, +90° front half, or +125°), over what range, and with which sign
   convention?
2. **Q2 (B2)** After one reflection, is the specular energy (1−α)(1−s), i.e. the removed fraction is s
   (Vorländer Eq. 3.23), or (1−α)·s as the text literally says?
3. **Q3 (B3)** What 1 kHz T60 does the Phase 04 tail produce for the open-field preset: zero, or ≈0.67 s
   as Eq. 4.32 gives for a 100×100×10 m box with ground α=0.1?
4. **Q4 (B4)** After a position-only change > 1 m, are the cached tail's onset level and scattered-energy
   injection recomputed, and from what time after the direct sound is the cached tail used unchanged
   (Vorländer §15.3: 140 ms)?
5. **Q5 (B5)** At what distance was the chosen HRTF set measured, and is any near-field treatment applied
   for emitter–listener distances of 0.3–1 m, which AX6 allows?

### Builder answers (round 0)

The plan and phase files are not edited here; corrections are listed for Maisara.

**A1 (Q1, B1).** Conceded: the gate is wrong. With the cardioid 0.5(1+cos ϑ) (Spatial Audio §6.2.1), a
source at azimuth φ (positive = left, toward the left capsule) gives
ΔL(φ) = 20·log10[(1+cos(φ−55°)) / (1+cos(φ+55°))]: 0 dB at 0°, +9.7 dB at +55°, +20.1 dB at +90°,
unbounded at +125° (right capsule's null). What is special at +55° is that the **left channel's own level
is maximal** (on axis), not the difference. Replacement gate proposed for `docs/phases/phase-09.md`
(and the BUILD_PLAN §4 Phase 09 line): anechoic direct path, emitter at 5 m, where the 1/r difference
across the 17 cm spacing is at most 20·log10(5.085/4.915) ≈ 0.3 dB (at 90°), or that 1/r term added to
the expected value; the measured ΔL matches the formula within ±0.5 dB at φ ∈ {0°, ±30°, ±55°, ±90°}, with positive sign for
positive φ and mirrored for negative φ; and the left channel's level as a function of φ peaks at +55°.

**A2 (Q2, B2).** Conceded as a wording error in BUILD_PLAN §4 (Phase 03 scope line). The intended model
is Vorländer Eq. 3.23: specular energy after a reflection (1−α)(1−s), scattered energy (1−α)s, so the
pressure factor per specular reflection is √((1−α)(1−s)). `docs/phases/phase-03.md` already says
"scattering is applied as (1−s) on energy", which is the correct form, so the two documents disagree
and the BUILD_PLAN line is the one to fix. A side condition follows from the same figure: the scattered
fraction (1−α)s is not lost; it belongs to the diffuse part (Vorländer §11.6: scattered energy dominates
after order 3–4), so Phase 04's energy matching must account for it. Test: shoebox with uniform α and
s, every first-order specular amplitude equals √((1−α)(1−s))/r within ±0.05 dB of the analytic value.

**A3 (Q3, B3).** Accepted that Eq. 4.32 does not apply: five fully absorbing faces cannot give a diffuse
field (Vorländer §4.4.1). AQ2 sets the tail's *level* by energy-matching it to the ISM at the mixing time,
and Eyring sets only its *decay rate*. In the open field the ISM has one floor reflection and nothing at
the mixing time, so a correctly matched tail has zero energy whatever its nominal T60, without any
scene-specific logic (NFR-8). That makes the answer to Q3 "nominal ≈0.67 s, amplitude zero", but only if
the matching is defined on ISM energy in a window around the mixing time. Proposed test: open-field
render, energy later than 50 ms after the direct sound below −60 dB re direct. Remaining: the plan does
not define the matching window.

**A4 (Q4, B4).** Accepted. What can be cached is what depends only on room and materials: the per-band
decay rates and the noise seed. The onset level (energy matching) and the scattered-energy share must be
recomputed on every rebuild; that is cheap. Vorländer Table 15.1 puts the full scattering update at moves
> 1 m and §15.3 the statistical region after ≈140 ms; the mixing time itself is not checkable from the
corpus (B35). Proposed test: move the listener 3 m; tail energy after the mixing time from the cached
path vs a full rebuild within ±0.5 dB per band.

**A5 (Q5, B5).** The measurement distance of SADIE II is not in the corpus, so it can't be checked here;
Phase 08 must record it from the dataset. Whatever it is, a far-field HRTF is valid only beyond about
1 m (Vorländer §9.5, Fig. 9.7), and AX6 allows 0.3 m. Two corpus-consistent options, a decision for
Maisara: raise the binaural minimum emitter–listener distance to 1 m, or keep 0.3 m and document that
0.3–1 m renders with far-field ILD and spectrum (level by 1/r only). Proposed test either way: ILD at
90° for 0.5 m and 2 m sources is reported; if near-field treatment is added, it must grow below 1 m as in
Fig. 9.7.

### Round 1 (interrogator on blockers B1, B2)

Builder's descriptions of the phase files confirmed: `phase-09.md` (gate line) and BUILD_PLAN §4 Phase 09
carry the old +55° gate; BUILD_PLAN §4 Phase 03 carries "(1−s) of specular energy"; `phase-03.md` already
uses √(1−α)·√(1−s) per hit and "(1−s) on energy", consistent with Vorländer Eq. 3.23.

| id | verdict | severity now | citation/arithmetic check | reason | follow-up |
|---|---|---|---|---|---|
| B1 (A1) | OPEN | minor (was blocker) | Citations check (Spatial Audio §6.2.1, §6.2.4 Table 6.2). ΔL: +30° 4.88 dB, +55° 9.66 dB, +90° 20.05 dB, +125° unbounded — correct. 5 m 1/r bound 0.295 dB correct, but point-source parallax (≈0.56° per capsule at +55°) adds ≈0.12 dB, so ≈0.36 dB total at 55°. The left channel's peak at 5 m falls near +56.7°, not exactly +55°. | Acoustics and values right, the ΔL table is falsifiable; the "≤ 0.3 dB" bound and "peak at +55°" are slightly off for a 5 m point source. | What angular tolerance on the left-channel peak, and what geometric correction (1/r + parallax), does the gate use? |
| B2 (A2) | OPEN | minor (was blocker) | Citations check (Vorländer §3.3.2 Eq. 3.23, Fig. 3.10; §11.3.2 Eq. 11.37; §11.6, Fig. 11.34). √((1−α)(1−s)) correct. With AX4 air on, a 10 m path loses ≈0.59 dB at 8 kHz (Annex m, Eq. 3.34), above the ±0.05 dB test tolerance. With s = 0.5, the specular share after 3 hits is (1−s)³ = −9.0 dB, so a tail matched to specular energy only would be ≈9 dB low. | Wording fix and model correct; the test must state air off (or include it), and the tail matching must count the scattered energy. | Is the Phase 04 tail matched to specular ISM energy plus accumulated scattered energy, or specular only? |

**Builder replies to the round-1 follow-ups**

- **B1.** The expected value is computed from the exact geometry, not from the plane-wave formula: per
  capsule, its own angle to the source (parallax) in the cardioid 0.5(1+cos ϑ) and its own distance in
  1/r (Vorländer Eq. 11.36). Gate: measured ΔL equals that value within ±0.5 dB at φ ∈ {0°, ±30°, ±55°,
  ±90°} for a 5 m source, sign positive for positive φ, mirrored for negative φ; the left channel's level
  peaks within ±3° of the geometric prediction (≈+56.7° at 5 m). The plane-wave values (9.7 dB at 55°,
  20.1 dB at 90°) are kept as a sanity check, within ±0.5 dB.
- **B2.** The ±0.05 dB first-order test runs with air absorption off (or, equivalently, with
  4.34·m·r dB per band included in the analytic value). Phase 04 matches the tail's onset energy to the
  specular ISM energy **plus** the accumulated scattered energy Σ(1−α)s per hit (Vorländer Eq. 3.23,
  Fig. 3.10; §11.6), so with s = 0.5 the tail is not 9 dB low. This also makes A3's open-field answer
  precise: with five α = 1 faces the scattered energy is zero too, so the tail is still zero.

No blocker remains, so no round 2 was run.

### Status after round 1

| id | severity | status | what closes it |
|---|---|---|---|
| B1 | minor (was blocker) | resolved | Builder adopted the geometric gate. Maisara: correct the +55° gate in `phase-09.md` and BUILD_PLAN §4 Phase 09 before Phase 09 starts. |
| B2 | minor (was blocker) | resolved | Builder: specular (1−α)(1−s), air off in the test, tail matched to specular + scattered energy. Maisara: fix the BUILD_PLAN §4 Phase 03 wording; add the matching rule to `phase-04.md`. |
| B3 | major | open | A3 answer given (energy-matched tail is zero in the open field) but not re-checked; matching window still undefined in the plan. |
| B4 | major | open | A4 answer given (cache decay rates and seed only, recompute onset level) but not re-checked. |
| B5 | major | open | Maisara: raise the binaural minimum distance to 1 m, or document far-field rendering for 0.3–1 m. |
| B6–B11 | major | open | No question asked in this run (ISM "exact" wording, small-room validity, per-band s, F8 vs AX3, AX11 range, DRR window). |
| B12, B13, B15, B16, B20, B28, B30, B32, B34, B37–B40, B43–B46 | minor | open | No question asked; listed for the next plan revision. |
| B14, B17–B19, B21–B26, B29, B31, B33, B36, B41, B42, B48, B49 | none (CORRECT) | resolved | — |
| B27, B35, B47, B50, B51 | none (NOT CHECKABLE) | open | Needs a source outside the corpus. |

### Plan fixes applied (2026-11-05)

Commit "plan: apply corpus-review corrections" on `claude/modest-turing-afvz7v` fixed the plan text for
B1, B2, B6, B8 (AX17; per-band s moved to backlog B10), B9, B10, B12, B13, B15, B16, B20, B32 (AX18),
B34, B40, B46 and PRD row P1; those rows are now **resolved**. Phase 04's open-field wording was
corrected along with B3, which stays open until the interrogator re-checks it. Not changed, still open:
the ±2.5 ms DRR window (B11), the minimum binaural distance (B5), small-room validity (B7), the cached
tail (B4), and the phase-07 / phase-10 lines that still mention only the 20 ms cap.

### Round 2 (interrogator on B3, B4 against the current `phase-04.md`, `phase-10.md`, BUILD_PLAN on main)

Corpus revision 22dc9dd. Target: `docs/phases/phase-04.md` (whole), BUILD_PLAN §2 (AQ1–AQ10, AX1–AX18)
and §4 Phases 04–10, `docs/phases/phase-10.md` (tail cache).

| id | verdict | severity now | citation/arithmetic check | reason | follow-up |
|---|---|---|---|---|---|
| B3 | DISPUTED | major | Vorländer §4.4.1 (diffuse field, homogeneous absorption) confirms Eyring does not apply. But under AX16 the floor path's scattered energy is E_noScatter·s, non-zero for any s_floor > 0. Working (100×100×10 m, ground α=0.1, s=0.5, both 1.5 m high, 10 m apart): direct 0.0100, floor E_noScatter 0.00826, scattered 0.00413 = −3.8 dB re direct, 1.3 ms after it. Phase 04 adds scattered energy "up to that time", so E_b ≈ −3.8 dB re direct and the < −60 dB open-field gate fails by ≈56 dB. | The builder's round-1 claim that the scattered energy is also zero with five α=1 faces was **wrong**: the ground face has α < 1 and s ≥ 0. The tail is zero only when s_floor = 0. | Over which interval is scattered energy summed for E_b (all AX16 entries before t_mix, or only [t_mix−10 ms, t_mix]), and what E_b follows for s_floor = 0.5? |
| B4 | RESOLVED | minor | Vorländer §15.3 Table 15.1: moves > 1 m need the specular and scattering parts updated; Phase 10 rebuilds the early part and re-runs the energy matching, and AX16 is recomputed from the new image list. Every input to the Eyring decay (V, S, ᾱ_b, m_b) is independent of position and is in the cache key, so the cached tail equals a full rebuild; the −120 dB equivalence gate is stricter than A4's ±0.5 dB. | The corpus condition is met. Remaining gap: the t_mix clamp to the ISM order's coverage depends on positions and `maxReflectionOrder`, which are not in the cache key. The early t_mix (√V ms vs §15.3's ≈140 ms) is B35, not a cache issue. | Is the cached tail stored before any t_mix-dependent gating or crossfade, so a move that changes the clamp still gives the −120 dB match? |

New rows (phase-04 acoustic content):

| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| B52 | NUMBER | Phase 04 energy matching: tail energy in a 10 ms window after t_mix = extrapolated ISM energy **plus** scattered energy "up to that time" | INCONSISTENT | Vorländer §11.7 Eq. 11.51 matches the envelope per time interval; §4.4.1 Eq. 4.25 is an energy density. A sum over [0, t_mix] is not a 10 ms quantity; at a steady arrival rate the ratio is t_mix/10 ms (7.7, +8.9 dB, for V = 6000 m³). B3 is the extreme case. | major | Is the scattered term an energy per 10 ms at t_mix, in the same units as the ISM window term? | resolved |
| B53 | NUMBER | Phase 04 gates: "a different seed gives the same T30 within ±2 %"; T30 within ±5 % of Eyring on one realisation | INCONSISTENT | Not set by the corpus; conflicts with BUILD_PLAN AX11's measured single-realisation scatter σ₁ = 8 % at 250 Hz, T60 0.3 s, so two seeds differ by ≈ 8·√2 ≈ 11 %. AX11 requires the ±5 % gate on an ensemble (R ≥ 23); phase-04 doesn't say so. | major | Are both T30 gates evaluated on AX11 ensemble-averaged decays, and with which R per band? | resolved |
| B54 | NUMBER | Phase 04: "m_b = air attenuation coefficient in nepers/m" in 4·m_b·V | IMPRECISE | Vorländer §3.6 Eq. 3.31–3.34, §4.4.1 Eq. 4.32: m is the energy coefficient (I = I₀e^(−mx), D = 4.34·m dB/m); a pressure-neper value (D/8.686) would halve the 4mV term, biasing T by ≈8 % at 4 kHz in a 20×30×10 m room (B20 working). The 0.161 constant (24 ln10/c at 343.2 m/s) is correct. | minor | Is m_b the energy coefficient D/4.34 or the pressure attenuation D/8.686? | resolved |

Checked and CORRECT (no rows): "≈9 dB low with s = 0.5 after 3 hits" ((1−s)³ = −9.0 dB); the 12 s cap vs
T30 (needs T ≤ 60·12/35 = 20.6 s). Noted, not filed (row cap): phase-04's ISM→tail crossfade uses
complementary cos² windows, which is equal-gain on uncorrelated signals and dips up to 3 dB mid-fade,
against Vorländer §9.2.1 and AX18 (≈0.3 dB EDC effect at T60 0.2 s, below the seam gate).

### Status after round 2

| id | severity | status |
|---|---|---|
| B3 | major | disputed: the open-field tail is not zero as specified; needs B52's fix and a defined summation interval |
| B4 | minor | resolved (follow-up on the t_mix clamp vs the cache key) |
| B52, B53 | major | open |
| B54 | minor | resolved |

### Plan fixes applied (round 2)

`docs/phases/phase-04.md`, `docs/phases/phase-10.md` and BUILD_PLAN (AX18, §4 Phases 04/10, §6) were
corrected for B3, B52, B53, B54, the B4 cache follow-up and the ISM→tail crossfade:
- one time-binned energy envelope (specular + AX16 scattered, at arrival time), matched per 10 ms
  window at t_mix, so the open-field tail is zero for any floor s;
- the cached object is the unmatched unit-energy decay, with E_b, t_mix and the crossfade recomputed on
  every rebuild;
- both T30 gates run on AX11 ensembles with R per band in phase-04;
- m_b is the energy coefficient D/4.34;
- the ISM→tail crossfade is equal-power (AX18).

Rows B3, B52, B53 and B54 are now **resolved** in the plan text, not re-checked by the interrogator.
B52's citation is corrected to §11.7. Follow-up still open: the phase-04 gate "44.1 vs 96 kHz give the
same T30/EDT/C80 within ±2 %" compares different noise realisations, so B53's problem applies to it too.

### Verification of the round-2 plan fixes (commit b62b110)

Interrogator on the decisions in `docs/phases/phase-04.md`, `phase-10.md` and BUILD_PLAN (AX18, §4
Phase 04, §6 last row). Corpus revision 22dc9dd. Arithmetic re-done and confirmed: the R table (all 49
cells), 4.5·σ₁², 6·ln10 = 13.82, 3·ln10 = 6.91, m = D/4.34, the −3 dB equal-gain dip, the ≈ −9 dB figure.

| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| V1 | FACT | Tail level matched per 10 ms interval at t_mix; nothing accumulated from t = 0 | CORRECT | Vorländer §11.7 Eq. 11.51 (envelope per interval); §15.2.3 (envelopes averaged over some 10 ms suffice). | none | — | open |
| V2 | NUMBER | One 10 ms bin of the image list before t_mix is an adequate level estimate | CONDITIONS VIOLATED | Blauert Ch.3 §3.3 (Fig. 3.46): density 4πc³t²/V; arrivals in bin 0 ≈ 3.0 (400 m³, 20 ms), ≈ 4.6 (10⁴ m³, 100 ms), limit ≈ 5.1 for t_mix = √V ms; Poisson-like scatter ≈ 45 % (+1.6/−2.6 dB). Mean order at t_mix ≈ 2.4 (Vorländer Eq. 4.22, 20×30×10 m), below the order 3–4 of §11.6. | major | Q4 | resolved |
| V3 | DECISION | Scattered energy placed at the specular arrival time (AX16) | CONSEQUENCE | Vorländer §3.3.2 Fig. 3.9: scattered paths are longer and delayed; a delay δ shifts bin 0 by ≈ 60·δ/T dB (δ = 5 ms, T = 0.3 s → 1 dB). No corpus value for δ. | minor | — | open |
| V4 | NUMBER | Specular-only matching ≈ 9 dB low (s = 0.5, 3 hits) | CORRECT | Vorländer Eq. 3.23: (1−s)³ = −9.03 dB. | none | — | open |
| V5 | FACT | Open-field fixture: bin 0 empty for any floor s | CORRECT for the fixture | Eq. 3.23 (α = 1 faces carry no energy); fixture: direct 60.2 ms, floor 61.6 ms, t_mix ≈ 548 ms, nearest order-3 image 198 ms. Holds in general only if the floor arrives before t_mix − 10 ms (V6). | none | — | open |
| V6 | FACT | Direct and floor arrivals are "long before" the window; ISM dropped after the fade | CONDITIONS VIOLATED | Blauert Ch.3 §3.3, Vorländer §11.7: the transition comes after the direct sound, but t_mix = max(20 ms, √V ms) is counted from emission. 10×10×2.5 m, 8 m apart: direct at 23.3 ms > t_mix = 20 ms, bin 0 empty → E_b = 0 and the direct sound is dropped. Also 100×100×1.5 m (t_mix 122 ms vs direct up to 411 ms). Both are inside AX6. | major | Q2 | resolved |
| V7 | FACT | "Empty bin 0 ⇒ E_b = 0" combined with the t_mix clamp to the ISM order's coverage | CONDITIONS VIOLATED | Eq. 4.32 gives a finite T in any closed room; with maxReflectionOrder 0–1 bin 0 is empty (no tail in a reverberant room) or holds the direct sound (tail level set by it). | major | Q3 | resolved |
| V8 | NUMBER | E_target = E_bin0·exp(−13.82·0.010/T60_b); amplitude exp(−6.91 t/T) | CORRECT | Vorländer §4.4.1 Eq. 4.26–4.27. | none | — | open |
| V9 | DECISION | Eyring slope rather than a fit | CONSEQUENCE | Vorländer §4.4: concentrated absorption is not diffuse; a slope error ε over 10 ms gives 0.6·ε/T dB (ε = 20 %, T = 0.3 s → 0.4 dB). | minor | — | open |
| V10 | NUMBER | §6 row says "extrapolated over [t_mix − 10 ms, t_mix]"; phase-04 says from bin 0 into [t_mix, t_mix + 10 ms) | INCONSISTENT | Different matching windows stated; phase-04 says the open-field result depends on them. | major | — | resolved |
| V11 | FACT | Cached unit-energy decay depends only on V, S, ᾱ_b, m_b, tailSeed, fs; the rest is recomputed | CORRECT | Vorländer Eq. 4.32; §15.3 Table 15.1. | none | — | open |
| V12 | NUMBER | R ≥ (σ₁/(tol/3))² (3σ coverage) | CORRECT (arithmetic) | ≈ 0.27 % two-sided false-fail per gate, assuming Gaussian scatter and no bias; no corpus statistics of decay estimates. | none | — | open |
| V13 | NUMBER | σ₁ table and σ₁ ≈ 0.5/√(B·T) | NOT CHECKABLE | Not in the corpus (ISO 3382-2 Annex A would settle it); matches AX11 and falls with T in every band. | none | — | open |
| V14 | NUMBER | R table (Eyring and seed gates) | CORRECT (recomputed) | e.g. Eyring 250 Hz ⌈23.04⌉ = 24; seed 125 Hz 4.5·6.7² → 203; all cells agree. | none | — | open |
| V15 | NUMBER | Seed gate tol/√2, R = 4.5·σ₁² | CORRECT (arithmetic) | Difference of two independent means has √2·σ_R. | none | — | open |
| V16 | NUMBER | σ₁ column "at or just below" T60_b | CORRECT (conservative) | σ₁ falls with T in every band. | none | — | open |
| V17 | NUMBER | Below 0.3 s, "scale the 0.3 s value by 0.3 s/T60_b" | IMPRECISE | The sentence is in the σ₁ rule, but σ₁ scales by √(0.3/T) and R by 0.3/T; the dead_booth figure (36) scales R; scaling σ₁ would give 52. | minor | Q5 | resolved |
| V18 | DECISION | Whole tolerance spent on random error at 3σ | CONSEQUENCE | With an analysis bias of tol/3 the false-fail rate rises from 0.27 % to ≈ 2.3 %. | minor | — | open |
| V19 | FACT | m_b = D/4.34 energy coefficient | CORRECT | Vorländer §3.6 Eq. 3.31, 3.33–3.34; §4.4.1 Eq. 4.32. | none | — | open |
| V20 | NUMBER | "≈ 8 % too long a T at 4 kHz in 20×30×10 m" | NOT CHECKABLE | Needs D(4 kHz) and ᾱ, not stated. | none | — | open |
| V21 | FACT | ISM and tail uncorrelated → equal-power crossfade | CORRECT | Vorländer §9.2.1 (constant power in the overlap). | none | — | open |
| V22 | NUMBER | Equal-gain dips 3 dB on uncorrelated signals | CORRECT (arithmetic) | −3.01 dB at mid-fade. | none | — | open |
| V23 | FACT | Energy conserved across the seam with E_b matched on the un-faded tail | CORRECT in expectation | A single render deviates by the bin-0 sampling error of V2. | none | — | open |
| V24 | NUMBER | Open-field gate: energy > 50 ms after the direct sound < −60 dB re direct | NOT CHECKABLE | No corpus threshold; AX15's ≈163 ms filterbank ringing means the gate also measures band-filter ringing. | none | — | open |
| V25 | FACT | Eyring does not apply to the open field | CORRECT | Vorländer §4.4, §4.4.1. | none | — | open |
| V26 | NUMBER | 44.1 vs 96 kHz: same T30/EDT within ±2 % | INCONSISTENT | Contradicts AX11 (single realisations are reported, not gated): the two renders are independent realisations, σ_diff = √2·σ₁ = 6.2 % at 250 Hz, T = 1 s. Valid only with per-rate ensembles (R ≥ 4.5·σ₁²) and measured σ₁ for EDT, which AX11 lacks. | major | Q1 | resolved |
| V27 | NUMBER | 44.1 vs 96 kHz: C80 within ±2 % | WRONG | Vorländer §6.4.3 Eq. 6.7, Table 6.1: C80 is in dB (jnd 1 dB) and can be 0 or negative, so a relative tolerance is undefined; it must be in dB. | blocker | Q1 | resolved |
| V28 | NUMBER | T30 on a 12 s IR only for T ≤ ≈ 20 s | CORRECT (arithmetic) | Eq. 4.26: 35/60 · 20 s = 11.7 s. | none | — | open |

**Questions:** Q1 (V27, V26) C80 tolerance in dB, and ensembles for T30/EDT in the sample-rate gate?
Q2 (V6) is t_mix counted from emission or from the direct-sound arrival? Q3 (V7) what is "the time
covered by the ISM order" for order 0–1? Q4 (V2) what tail-level uncertainty is accepted with 3–5
arrivals in bin 0, and how large is the E_b jump when one arrival crosses a bin edge? Q5 (V17) below
0.3 s, is R or σ₁ scaled by 0.3/T60_b?

## docs/phases/phase-04.md — 2026-11-05 (/fix-plan rounds 3–5)

First run of the `/fix-plan` loop: the plan-editor applied only specified fixes and returned every acoustic
or numeric choice; the interrogator verified the options (corpus 22dc9dd) and the main session chose
with the PRD (NFR-1 accuracy first, NFR-3/FR-SIM-6 smooth movement, NFR-6, NFR-8). Commits c0754fc,
32a96dd, 3bfffc8 and the F1 fix.

**Round 3 (V-rows).** Specified fixes applied: V10 (change-log windows), V17 (R, not σ₁, scales below
0.3 s), V26 T30 part (per-rate ensembles). Decisions verified and chosen:

| decision | chosen | interrogator verdicts (others) | basis for the choice |
|---|---|---|---|
| D1 EDT in the rate gate | (a) ensembles, σ₁(EDT) measured (AX19) | (b) CONDITIONS VIOLATED (the decay curve contains the stochastic tail, Vorländer Eq. 6.4); (c) correct but checks nothing | CLAUDE.md: every DSP behaviour needs an automated check |
| D2 C80 tolerance | (a) ±0.5 dB on ensembles; E_b matched to the *expected* window energy | (b) ±1 dB valid (one jnd, Table 6.1, 500–1000 Hz only); (c) ±2 dB CONDITIONS VIOLATED (AQ9 is sim-vs-measured) | NFR-1; consistent with the T30 gate at 0.4 jnd |
| D3 63 Hz | (b) included | (a) also valid | NFR-1/NFR-8: every shipped band at every rate |
| D4 t_mix reference | (c) per emitter from its own direct arrival; direct path never faded | (a) CONDITIONS VIOLATED (emitter spread); (b) correct but couples emitters | NFR-3: continuous in position, per emitter like the tails |
| D5 low order | (a) time-bounded matching list | (b), (c), (d) CONDITIONS VIOLATED | NFR-1, NFR-8 |
| D6 level estimator | (a) + (d1): Eyring-referred Hann window | (b) uncompensated biased, k ≈ 15 IMPRECISE; (c) CONDITIONS VIOLATED; (d2) breaks offline/realtime equivalence | NFR-1, NFR-3, NFR-6 |

**Round 4 (follow-ups E1–E5 + science check R1–R10).** R1 (major): sparse windows gave no tail in
closed near-cubic rooms of ≈370–480 m³. R2 WRONG (4.91 should be 5.52·V^(1/3) under the old rule). R3
INCONSISTENT (maxReflectionOrder "minimum" had no effect). R4 (k_eff must weight arrival energy
1/(ct)²). R5 (σ is an expectation only). R6/E5 (ē_b independent of the window, truncation). R7, R8
minor. Chosen: an **adaptive mixing time** (the corpus has no transition-time rule, Vorländer §11.7, so
PRD NFR-1 decided: a later t_mix keeps more of the response deterministic and conditions the
estimator); energy-weighted k_eff ≥ 19; E1 (a) EDT 63 Hz–8 kHz; E2 (b) σ₁ measured at both rates with
n ≥ 51 (sampling statistics, not corpus); E3 energy-weighted; E4 (a)+(c) limitation + Expert question,
no cut-off; E5 (b) truncation-aware ē_b; R3: maxReflectionOrder applies only to the kept ISM-only IR
(`Kind::OmniEarly`, `render_cli --mode omni-early`, a software choice so the Phase 03
pyroomacoustics cross-check and goldens stay valid), contract minor bump in Phase 04.

**Round 5 (final science check).** One finding:

| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| F1 | NUMBER | "≈ 5.5·V^(1/3) ms (≈ 28 arrivals)" for the k_eff criterion with t_dir → 0 | WRONG | From the document's own energy-weighted k_eff with a Hann window: K = π[Si(2π) − ½Si(4π)] = 2.111, k_eff = 1.488·c³L³/V, so k_eff = 19 gives cL = 2.338·V^(1/3) m, L ≈ 6.8·V^(1/3) ms, N ≈ 53 (Blauert Ch.3 §3.3 density). | major (explanatory; understated rebuild cost) | — | resolved (corrected to 6.8·V^(1/3) ms, ≈ 53) |

Confirmed CORRECT in round 5: the k_eff formula and its dimensions; the adaptive rule always terminates
and t_mix,e is continuous in position (k_eff strictly increasing in window length; entries enter and leave
at zero weight), as artifact-free movement needs; σ ≈ 1 dB at k_eff = 19; the R1 cube case is handled;
the ē_b formula and its time origin; the R rule for unequal σ₁; n ≥ 51 ↔ 10 % relative SE (statistics
outside the corpus; ≈ ±20 % on R); gate bands; crossfade note; consistency across phase-04, phase-10,
AX19, AX20, §4 and §6.

**Status:** V2, V6, V7, V10, V17, V26, V27, R1–R8, E1–E5, F1 resolved in the plan text. Open, for the
Expert: the mixing-time rule itself (Vorländer §11.7 gives none); the E4 sparse/non-diffuse limitation.
Open follow-up: AQ10 and `phase-13.md` still state the rebuild budget at "order 30", which no longer sets
the hybrid IR's workload (AX20).

## docs/phases/phase-05.md — 2026-11-05 (corpus 22dc9dd59cf2f4ced36440b3b3f4cc23576e56f0)

`/interrogate` run on the Phase 05 plan (validation against measured BRAS IRs). The interrogator returned
no WRONG item and so no blocker; by the `/interrogate` rule (re-run only for open blockers) no verification
round was run on the builder answers below. Those answers are proposals: the target document is unchanged,
and every row they touch stays **open** until Maisara decides and `/fix-plan` applies a change. Corpus note:
the Schroeder-frequency constant differs between books (Vorländer §4.2.1 Eq. 4.13 ≈ 1200√(T/V) as a
lower bound, "f_S ≫"; Toole §4.3.1 2000√(T/V)); cite the book whose constant is used.

SOFTWARE (not rated): fetch_bras.py, SHA-256 manifest, cache under ~/.cache, DepositOnce download, CC BY-SA
attribution, scene fixtures, run_validation.py, matplotlib pin, nightly.yml, artifact upload, tampered-cache
test, two-run reproducibility, debug-only `MAKROOF_TEST_BIAS_T60` hook, A_/B_ naming with key.txt, AQ9
failure not failing CI, BUILD_PLAN status note.

### Issue ledger

| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| V5-1 | NUMBER | AQ9: EDT within ±10 % | CORRECT | Vorländer §6.4.4 Table 6.1: EDT jnd 5 %, so ±10 % = 2 jnd; §11.5 Round-robin III: 1–2 jnd achievable. | none | — | resolved |
| V5-2 | NUMBER | AQ9: C80 within ±2 dB | CORRECT | Vorländer Table 6.1: C80 jnd 1 dB; Fig. 11.33 caption: older 0.5 dB jnd replaced by 1 dB. | none | — | resolved |
| V5-3 | NUMBER | AQ9: T30 within ±10 % | NOT CHECKABLE | Vorländer Table 6.1 lists no jnd for T/T30, nor does any other corpus book; ISO 3382-1 or a T-jnd study would settle it. | none | — | resolved (no defect) |
| V5-4 | NUMBER | AQ9 metrics "averaged over the 500 Hz, 1 kHz and 2 kHz bands" | IMPRECISE | Vorländer Table 6.1: jnd frequency range 500–1000 Hz, so 2 kHz is outside it. §11.5 Round-robin I rates accuracy as the mean of \|sim−meas\| / jnd; a signed mean can cancel (+12 % and −12 % → 0). | minor | Q3 | open |
| V5-5 | FACT | Matching shoebox V and S preserves the diffuse-field quantities | CORRECT | Vorländer §4.4 Eq. 4.22–4.23: n̄ = cS/4V, l̄ = 4V/S; with ᾱ fixed, Eq. 4.28 and 4.32 give the same T. | none | — | resolved |
| V5-6 | FACT | Shoebox dimensions "so that volume and total surface area match as closely as possible" as a generic rule | IMPRECISE | Working: V = abc and S = 2(ab+bc+ca) leave one free dimension (aspect ratio); an exact match needs S ≥ 6V^(2/3) (AM–GM, equality for a cube). Vorländer §11.3.3: the image lattice, so early timing behind EDT/C80, depends on the individual dimensions. | major (scenes and baseline are built on it) | Q4 | open |
| V5-7 | FACT | Area-weighted averaging of absorption | CORRECT | Vorländer §4.4.1 Eq. 4.30 ᾱ = (1/S)ΣSᵢαᵢ, Eq. 4.38 for Eyring; diffuse-field assumption, which §4.4 says fails for concentrated absorption. | none | — | resolved |
| V5-8 | FACT | Per-surface mapping onto the 6 faces keeps the room's absorption | IMPRECISE | Vorländer Eq. 4.30: A = ΣSᵢαᵢ is conserved only if each box face's area equals the real area mapped onto it; matching total S does not guarantee this. | minor | Q4 | open |
| V5-9 | FACT | Fitted absorption "partly includes the answer, so it isn't proof of accuracy" | CORRECT | Vorländer §11.5 Round-robin I (agreement improved with measured absorption data); Round-robin III (operator's choice of α and s has crucial influence). | none | — | resolved |
| V5-10 | DECISION | Initial/as-documented absorption is the primary run | CONSEQUENCE | Vorländer §11.5 Round-robin I: with users' own absorption guesses simulated T was generally too large; expect worse agreement than with fitted data. | minor | — | open |
| V5-11 | DECISION | Prefer the room closest to a box ("likely the small seminar room") | CONSEQUENCE | Vorländer §11.5 (GA exact for large rooms, low absorption, broadband); Round-robin III (small room with modal effects needs a good scattering model); §11.3.3 (50–200 m³ below 200 Hz at GA's limit); Toole §4.3.1 transition region. | minor | — | open |
| V5-12 | DECISION | Per-band reporting "without gating" includes 63–250 Hz | CONSEQUENCE | Vorländer §4.2.1 Eq. 4.13; Toole §4.3.1: small rooms are mode-dominated below the transition, so low-band deltas measure method validity, not input accuracy. | minor | — | open |
| V5-13 | DECISION | Method under test stays ISM + tail; use of BRAS scattering data not stated | CONSEQUENCE | Vorländer §11.5 Round-robin II/III (a scattering module is needed, essential in small rooms); §11.1.1 (above ≈ 700 Hz surfaces partly scattering, covering the 1 and 2 kHz AQ9 bands). | minor | — | open |
| V5-14 | FACT | "Real rooms aren't shoeboxes, so expect misses" | IMPRECISE | Vorländer §11.5: misses expected (GA exact only in mostly academic cases), but Round-robins I–III name absorption input and scattering as the main error sources, not shape. | minor | — | open |
| V5-15 | FACT | Comparing ISO 3382 T30/EDT/C80 of simulated and measured IRs | CONDITIONS VIOLATED | Vorländer §6.4.1 Eq. 6.4 (backward integral; T from −5 to −35 dB regression; EDT 6 × the 0 to −10 dB time), Eq. 6.7 (C80 from the direct sound). Needs ≥ 35 dB usable decay above measured noise, a common time origin, and an untruncated simulated IR (§11.3.3 Eq. 11.39); none is stated. | major | Q5 | open |
| V5-16 | FACT | EDC overlay plots | CORRECT | Vorländer §6.4.1 Eq. 6.4, Fig. 6.9: EDC is the backward-integrated h²(t). | none | — | resolved |
| V5-17 | NUMBER | Regression gate: "any metric delta worsening by > 2 % relative to the baseline" | CONDITIONS VIOLATED | Meaningful only for \|baseline delta\| ≫ 0: a 0.1 dB C80 delta gives a 0.002 dB gate (1/500 of the 1 dB jnd, Table 6.1); a zero delta trips on any change. §11.5 normalises errors by the jnd instead. | major (CI gate is built on it) | Q2 | open |
| V5-18 | FACT | The nightly gate "fails when a deliberate +5 % T60 bias is injected" | CONDITIONS VIOLATED | Vorländer Eq. 4.27: T scales by 1.05. With d = T_sim/T_meas − 1, d′ = 1.05(1+d) − 1; \|d\| worsens only if d > −0.05/2.05 ≈ −2.4 % (d = −3 % → d′ = +1.85 %, an improvement). By Eq. 6.20 C80 falls as T rises, so a positive C80 delta also improves. | major (acceptance test is built on it) | Q1 | open |
| V5-19 | FACT | BS.1770 loudness-matching of the A/B renders | CORRECT | Immersive Sound Ch. 8 Fig. 8.14 (BS.1770-4: K-filter, mean square, gating); Izhaki Ch. 4 (the louder version is judged better). | none | — | resolved |
| V5-20 | DECISION | Loudness-matching removes level differences from the A/B pack | CONSEQUENCE | Vorländer Table 6.1: strength G is its own attribute (jnd 1 dB); after matching, listeners cannot judge G errors. | minor | — | open |
| V5-21 | DECISION | Omni (monaural) IRs auditioned on headphones | CONSEQUENCE | Vorländer §6.4.4 Eq. 6.11–6.13: ASW/LEV depend on lateral energy and IACC, absent from an omni IR; only monaural attributes can be judged, as the checklist asks. | minor | — | open |
| V5-22 | FACT | BRAS holds geometry, absorption/scattering data and measured omni and binaural IRs | NOT CHECKABLE | Not in the corpus; the BRAS documentation (DepositOnce) settles it. | none | — | resolved (no defect) |

Interrogator's worked threshold in V5-18, rechecked by the builder: d′ > −d ⇔ d > −0.05/2.05 = −2.44 % (the
report's "2.07" is a typo; the −2.4 % figure stands).

### Questions (interrogator)

- **Q1 (V5-18):** Is "metric delta" the signed relative error, its absolute value, or a difference in seconds?
  Must the gate fire under `MAKROOF_TEST_BIAS_T60=1.05` even when the baseline T30/EDT delta is below
  ≈ −2.4 % or the C80 delta is positive?
- **Q2 (V5-17):** What threshold is meant for C80 (dB) and for a baseline delta near 0: 2 % of the delta,
  or a fixed fraction of the Table 6.1 jnd?
- **Q3 (V5-4):** Is the 500/1k/2k average a signed mean or a mean of absolute deltas (Vorländer §11.5)? Should
  2 kHz be in it, given Table 6.1's 500–1000 Hz range?
- **Q4 (V5-6, V5-8):** Which rule fixes the free aspect ratio? Must each face's area equal the real area
  mapped onto it, so that A = ΣSᵢαᵢ (Eq. 4.30) is conserved?
- **Q5 (V5-15):** Which time origin for EDT/C80, which upper integration limit and noise handling for the
  Eq. 6.4 EDC, and what minimum usable decay range above noise for T30?

### Builder answers (proposals; not verified by a further round, not applied)

| q | rows | proposed answer | corpus basis | outside the corpus | status |
|---|---|---|---|---|---|
| Q1 | V5-18 | Split the nightly check in two. (a) **Accuracy record:** per band and metric, the jnd-normalised error e = \|sim − meas\| / jnd (EDT 5 %, C80 1 dB; T30 given the EDT 5 % as a stand-in, labelled as chosen), stored in `validation_baseline.json` and reported, never gating. (b) **Regression gate on the simulated metrics alone:** fail when any simulated T30/EDT moves by more than ±2 % relative to the baseline simulation, or any simulated C80 by more than ±0.2 dB, in either direction; an intended change is accepted only through `update_goldens.py` with a reason. The +5 % T60 hook then moves simulated T30 by 5 % whatever the sign of the measured delta, so the acceptance test always fires. Note: the hook scales the tail only, so EDT and C80 move less than T30; the acceptance test should assert on T30. This reverses the phase text's "fails only on regression" (worsening), which is Maisara's call. | Vorländer Eq. 4.27 (T ∝ 1/slope, so the bias is a 5 % shift of simulated T); §11.5 Fig. 11.33 (jnd-normalised mean absolute error). | ±2 % / ±0.2 dB are change-detection limits, chosen as 0.4 × and 0.2 × the Table 6.1 jnd; not a corpus value. | open (needs plan decision) |
| Q2 | V5-17 | Covered by Q1(b): absolute limits on the simulated metric (2 % for T30/EDT, 0.2 dB for C80), never a fraction of the sim–meas delta, so a near-zero delta cannot trip the gate on noise. The run is deterministic (fixed `tailSeed`, CLAUDE.md), so any change above zero is real; the limits only stop platform-level floating-point drift from failing the nightly. | Vorländer Table 6.1 (C80 jnd 1 dB, EDT 5 %). | The 0.2 dB / 2 % choice. | open (needs plan decision) |
| Q3 | V5-4 | Mean of **absolute** per-band errors over 500 Hz, 1 kHz, 2 kHz, each divided by its jnd (§11.5 rating); pass if the mean ≤ 2 jnd, i.e. mean\|ΔEDT\| ≤ 10 %, mean\|ΔC80\| ≤ 2 dB, mean\|ΔT30\| ≤ 10 %. Keep 2 kHz (AQ9 already says the jnd equivalence is not stated there) and also print the 500–1000 Hz mean, where Table 6.1 states the jnd. Signed per-band deltas stay in the per-band table, because their sign shows bias (V5-10: T too large with guessed absorption). | Vorländer §11.5 Round-robin I rating; Table 6.1 range. | — | open (needs plan decision; AQ9 wording) |
| Q4 | V5-6, V5-8 | **Aspect ratio:** keep the documented mean floor-to-ceiling height h; solve the floor a·b = V/h and a + b = (S − 2V/h)/(2h); if no real solution (S below the box minimum for that h), match V exactly and take the square floor nearest to S, and report the S error. The rule is generic (no per-room choice) and fixes the floor–ceiling reflection timing, which the image lattice depends on (§11.3.3). **Faces:** assign each documented surface to the box face whose outward normal is closest to its own; set α_face = ΣSᵢαᵢ / S_face over the surfaces assigned, so A per face and in total equals the room's A (Eq. 4.30) and, with S matched, ᾱ and the Eyring T are preserved (Eq. 4.28, 4.32); clamp α_face to ≤ 1 and report any clamp. Scattering faces use the same area weighting, then AX17's broadband mean. | Vorländer §4.4 Eq. 4.22–4.23, 4.28, 4.30, 4.32; §11.3.3. | Keeping h (rather than the floor-plan ratio) is a choice; the corpus gives no shoebox-reduction rule. | open (needs plan decision; `bras_mapping.md` content) |
| Q5 | V5-15 | Same `tools/acoustics` octave filter bank for both IRs. **Origin:** for each IR the direct-sound onset, detected the same way in both (first sample within 20 dB of the broadband peak, the ISO 3382-1 convention); C80 per Eq. 6.7 and EDT from that origin. **Measured EDC:** backward integration from the band's noise-floor intersection with the noise-energy compensation of ISO 3382-1 (no corpus method). **Simulated EDC:** Phase 04 already renders to −90 dB in the slowest band, so the Eq. 11.39 truncation energy is negligible; integrate to the end. **Range:** T30 needs the band's decay to reach −35 dB at least 10 dB above the noise floor (peak-to-noise ≥ 45 dB); otherwise report T20 for that band and flag it, and exclude it from the AQ9 mean if it is a 500 Hz–2 kHz band (counted as "not evaluable", not pass). | Vorländer §6.4.1 Eq. 6.4 (−5 to −35 dB regression), Eq. 6.7; §11.3.3 Eq. 11.39. | 20 dB onset threshold, noise-floor intersection/compensation, 10 dB margin: ISO 3382-1 practice, not in the corpus. | open (needs plan decision) |

Builder notes on the CONSEQUENCE rows (no answer needed, to state in `report-phase05.md`): V5-10 expect
T_sim > T_meas on the primary run; V5-11/V5-12 report the band of the transition frequency for each room
(stating which constant, Vorländer Eq. 4.13 or Toole §4.3.1) and read bands below it as method validity;
V5-13 state whether the BRAS scattering data enters through AX17 (it should, under Q4); V5-14 report
absorption input and scattering as the corpus's main error sources alongside shape; V5-20 report the
level offset removed by loudness matching (dB, per pair) so G errors stay visible; V5-21 the A/B pack
judges monaural attributes only.

**Status after round 0 (no blocker, no verification round run):** 9 rows resolved (CORRECT / NOT CHECKABLE),
13 open: 4 major (V5-6, V5-15, V5-17, V5-18) and 9 minor. None disputed. Every open major row has a
proposed answer that needs a plan decision (Maisara) and then `/fix-plan`; the numeric choices in the
answers (±2 % / ±0.2 dB, held height, 20 dB onset, 10 dB noise margin) are outside the corpus and should
go to the interrogator when `/fix-plan` applies them.

### docs/phases/phase-05.md — verification batches and final check (2026-11-05, corpus 22dc9dd)

On Maisara's instruction, the open rows were batched by topic and each batch verified by its own interrogator;
the plan-editor then applied the verified options (PR maisara-abourady/makroof#9), and a final interrogator
checked the applied text.

| batch | rows | decision | verdict | chosen | basis |
|---|---|---|---|---|---|
| A | V5-17, V5-18 | gate quantity | (a) two-sided gate on simulated metrics vs baseline simulation CORRECT; (b) one-sided jnd-error gate WRONG (misses the +5 % hook for baseline d ≤ −2.2 %); (c) original CONDITIONS VIOLATED | (a), ±2 % T30/EDT, ±0.2 dB C80 (0.4 / 0.2 jnd; T30 limit NOT CHECKABLE) | only verified option |
| A | V5-18 | bias-test assertion | T30 rise CORRECT with a stated tolerance (Eq. 6.4 working: +5.0 % when the −5 dB point is after t_mix; less otherwise); C80 only −0.21 dB at t_mix 80 ms | assert on T30, +3 % … +5.5 % | derivable from Eq. 6.4 |
| B | V5-15 | time origin | direct sound CORRECT (Eq. 6.5 t₀); file t = 0 CONDITIONS VIOLATED (≈1.4 dB C80 bias at 15 ms lead); peak WRONG | direct sound, 20 dB onset rule (ISO practice) | only verified option |
| B | V5-15 | EDC / noise | measured: compensated integration consistent, uncompensated CONDITIONS VIOLATED; simulated: to end CORRECT by Eq. 6.4 (Eq. 11.39 the wrong citation) | compensated; simulated to end, 62 dB flag | only verified option |
| B | V5-15 | usable range | T30 with ≥ 10 dB margin else T20 CORRECT in substance; 35 dB-only and always-T30 CONDITIONS VIOLATED | (a), "peak-to-noise ≥ 45 dB" wording dropped (IMPRECISE) | only consistent option |
| B | V5-4 | AQ9 mean | absolute mean CORRECT (§11.5); signed mean WRONG; dropping 2 kHz valid | absolute mean, keep 2 kHz, also print 500–1000 Hz mean | (a) contains (c) |
| C | V5-6 | free dimension | keep height and keep floor ratio both valid closures (product choice); uniform scaling CONDITIONS VIOLATED | keep height | main session: single well-defined closure (floor-ratio closure has two roots) |
| C | V5-8 | face absorption | α_face = ΣSᵢαᵢ/S_face CORRECT (Eq. 4.30); area-weighted mean CONDITIONS VIOLATED | (a) with clamp report | only verified option |
| C | V5-13 | scattering | area-weighted s IMPRECISE (weight should be Sᵢ(1−αᵢ), Eq. 3.23); s = 0 CONDITIONS VIOLATED | Sᵢ(1−αᵢ)-weighted, then AX17 | corrected per verdict |
| D | V5-10..14, V5-20, V5-21 | report / risk / listening wording | S6 CORRECT; S1, S4 CONDITIONS VIOLATED; S5 INCONSISTENT; S2, S3 IMPRECISE | interrogator's corrected wording | verdicts |

Status after PR #9: V5-4, V5-6, V5-8, V5-10, V5-11, V5-12, V5-13, V5-14, V5-15, V5-17, V5-18, V5-20, V5-21
**resolved** in the plan text. V5-6's height closure stays a recorded product choice.

#### Final check of the applied text

| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| F5-1 | NUMBER | "+12 % at noise −50 dB, T = 1 s, 3 s file" (uncompensated EDC) | WRONG | Vorländer Eq. 4.25 + Eq. 6.4: EDC = e^(−kt)/k + 10⁻⁵(3 − t); −35 dB reached only at ≈ 0.81 s, ≈ +40 % by regression, +45 % two-point. | major | — | resolved (≈ +40 %, reference stated) |
| F5-2 | NUMBER | bias test: T30 rises +3 % … +5.5 % in every 500 Hz–2 kHz band | CONDITIONS VIOLATED | Same model, t_mix 80 ms: +3.9 % at 0.3 s, +2.5 % at 0.2 s; bound holds for T ≳ 2.9·(t_mix,e − t_dir,e). | major | — | resolved (assertion limited to bands with T30 ≥ 3·(t_mix,e − t_dir,e), inside the verified bound; at least one band required) |
| F5-3 | NUMBER | "≈ +4.3 % at T = 0.5 s, t_mix 80 ms" | IMPRECISE | Eq. 6.4 two-point: 0.5236 s, +4.7 %. | minor | — | resolved (+4.7 %) |
| F5-4 | NUMBER | 10 dB margin "limits the noise contribution at −35 dB to 0.4 dB" | IMPRECISE | 0.41 dB is the instantaneous ratio; integrated uncompensated EDC ≈ 0.9 dB. | minor | — | resolved (both stated) |
| F5-5 | FACT | AX17 over/understatement because s rises with frequency | IMPRECISE | Fig. 3.11 spans 80–630 Hz only; several Annex rows flat or falling over 500 Hz–2 kHz. | minor | — | resolved (made conditional per material) |
| F5-6 | FACT | AQ9 rationale "best achievable agreement" | IMPRECISE | §11.5 Round-robin III: 1–2 jnd achievable, not stated as a limit. | minor | — | resolved ("achievable") |
| F5-7 | NUMBER | 20 dB onset rule, T20 range, noise compensation | NOT CHECKABLE | Marked outside the corpus in the text; ISO 3382-1/-2 settle them. | none | — | resolved (no defect) |

Confirmed CORRECT in the final check: AQ9 wording agrees across phase-05 and BUILD_PLAN; gate limits and
their jnd fractions; shoebox formulas and existence bound; A conservation; Sᵢ(1−αᵢ) weighting; −90 dB and
62 dB end-of-IR numbers; all cited sections and equations exist and say what is claimed.
F5-1, F5-3–F5-6 fixed with the interrogator's own values; the F5-2 condition (factor 3) lies inside the bound
the interrogator derived (2.9), so no further round was run.

**Remaining for Maisara / the Expert:** the height-keeping shoebox closure (V5-6, product choice); the T30
limits (±10 % AQ9, ±2 % gate) have no corpus jnd; the onset rule, noise compensation and 10 dB margin rest on
ISO 3382-1, outside the corpus.

### docs/phases/phase-05.md — consultant answers (2026-11-05, corpus 22dc9dd)

Maisara asked the interrogator, as a consultant and subject-matter expert (outside its usual audit role), the
three questions left open after the final check. Answers label each point [corpus] or [expert]; expert points
that rest on ISO 3382-1/-2 or the literature are applied to the plan marked "expert recommendation" or "to
verify".

| q | question | recommendation | basis | confidence | status |
|---|---|---|---|---|---|
| C1 | Shoebox closure (V5-6) | Keep h, defined as V / floor area: floor and ceiling areas, total wall area and perimeter then exact, only the x/y wall split approximate; floor-ratio closure valid but moves floor/ceiling α and the 2h/c series; keep r and source/receiver heights when mapping; report absorption contrast and decay curvature as non-diffuseness indicators | expert, using Vorländer Eq. 4.22, 4.23, 4.28, 4.30, §11.3.3, §4.4, Table 4.1; Toole §21.4, §4.1 | medium (second-order next to absorption and scattering input, Vorländer §11.5) | resolved (applied) |
| C2 | T30 tolerances | Working T jnd 5 % (Seraphim 1958); keep ±10 % AQ9 (2 working jnd, above single-position σ(T30) ≈ 2–3.5 %); keep ±2 % gate (0.5 % also valid, product choice) | Vorländer §11.5, Table 6.1, Immersive Sound Ch. 1 Fig. 1.14; expert (ISO 3382-2 σ formula, from memory) | medium / high | resolved (applied; 0.5 % option not taken) |
| C3a | Onset detection | Broadband \|h\|², max − 20 dB, before band filtering, one t₀ for all bands; zero-phase or delay-compensated filters on the full IR; check measured lead-in | expert (ISO 3382-1); Immersive Sound Fig. 1.14 (peak ≠ first arrival) | high | resolved (applied) |
| C3b | Measured-EDC noise | Lundeby-style crossing with compensation (A/k)e^(−k·t_c) from the late slope; noise from a verified noise tail; one correction only; same energy in C80's late integral | expert (ISO 3382-1 practice; Lundeby 1995); Vorländer Eq. 6.4 | high (method), medium (constants) | resolved (applied) |
| C3c | 10 dB margin | Keep; noise referred to the decay-line intercept; T20 vs T20 fallback; "not evaluable" rules; curvature report; low-band B·T > 16 flag | expert (ISO 3382-1/-2; Jacobsen); Immersive Sound Fig. 1.14 | high (margin), medium (curvature threshold, B·T rule) | resolved (applied) |

**To verify against the standards before they are cited as fact:** the ISO 3382-2 constants in σ(T20/T30) and
its "integrated IR ≈ 10 averaged decays" equivalence; the ISO 3382-2 curvature threshold (≈ 10 %); whether the
ISO 3382-1 jnd table lists T. These are marked "to verify" in the plan text.

## docs/phases/phase-04.md — 2026-11-05 (/interrogate, fresh pass; corpus 22dc9dd59cf2f4ced36440b3b3f4cc23576e56f0)

Independent re-read of the current phase-04 text (after /fix-plan rounds 3–5). Earlier reviews were not
taken as evidence. Phase 04 has already been executed on another branch; this pass covers the plan text
only, and cross-examination against that branch comes later. One interrogator round: there were no
blockers, so the builder answers were not re-interrogated (the skill re-runs only for open blockers).
The target document was not edited. "Resolved" below means the question is answered here; the
document wording it points at is unchanged and is listed under "Remaining" for Maisara.

**Round 1: interrogator.** No WRONG items, so no gate or golden rests on a corpus contradiction.
1 major, 3 minor, 3 CONSEQUENCE rows.

| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| P4-01 | NUMBER | m_b = D_b/4.34 (energy coefficient) enters Eyring as 4mV | CORRECT | Vorländer §3.6 Eq. 3.33–3.34; §4.4.1 Eq. 4.31–4.32 | none | — | — |
| P4-02 | FACT | the Np/m coefficient D/8.686 halves the 4mV term | CORRECT | Vorländer §3.6 Eq. 3.31: pressure decays as e^(−(m/2)x) | none | — | — |
| P4-03 | NUMBER | "≈ 8 % too long a T at 4 kHz in a 20×30×10 m room" | CONDITIONS VIOLATED | Vorländer Eq. 4.32: with x = 4mV/(−S ln(1−ᾱ)), T_wrong/T_right = (1+x)/(1+x/2), which is 1.08 only at x ≈ 0.174. ᾱ_4k and D_4k are not stated. | major | Q1 | resolved (answer B1); text fix pending |
| P4-04 | FORMULA | T60 = 0.161V/(−S ln(1−ᾱ) + 4mV), ᾱ area-weighted | CORRECT | Vorländer §4.4.1 Eq. 4.28, 4.30, 4.32; 24 ln10/343 = 0.1611 | none | — | — |
| P4-05 | FACT | Eyring does not apply in open_field and is inaccurate for non-uniform absorption | CORRECT | Vorländer §4.4, §4.4.1 (diffuse field, homogeneous absorption) | none | — | — |
| P4-06 | FORMULA | reflection density 4πc³t²/V, N(t) = (4π/3)(ct)³/V | CORRECT | Blauert Ch. 3 §3.3 (after Cremer) | none | — | — |
| P4-07 | FORMULA | k_eff = (4πc³/V)(∫w)²/∫w²/t² | CORRECT | Poisson rate from Blauert §3.3 with entry energy ∝ 1/t² (Vorländer Eq. 11.50); mean²/variance via Eq. 11.8, 11.20 | none | — | — |
| P4-08 | NUMBER | t_dir → 0: ≈ 6.8·V^(1/3) ms, ≈ 53 arrivals | CORRECT | Hann on [0, b]: k = πc³b³/(V·2.111); k = 19 gives b = 6.81·V^(1/3) ms, N ≈ 53.5 | none | — | — |
| P4-09 | NUMBER | σ_dB = 4.34/√k_eff is an expectation under Poisson arrivals only | CORRECT | Vorländer §11.2.5 Eq. 11.9, 11.17; k = 19 gives 0.996 dB | none | — | — |
| P4-10 | FACT | equal-power crossfade for uncorrelated ISM and tail, citing Vorländer §9.2.1; equal-gain dips 3 dB | IMPRECISE | The arithmetic is right, but §9.2.1 (segmented convolution) states constant power without any correlation condition. The "uncorrelated → powers add" step is §4.3 Eq. 4.14–4.16. | minor | Q3 | resolved (answer B3); citation fix pending |
| P4-11 | FACT | band-filter ringing "Vorländer §11.7, which describes filter ringing qualitatively only" | IMPRECISE | Vorländer §11.7 "Interpolation", Fig. 11.41: that ringing comes from coarse interpolation of reflection-factor spectra, not from an analysis filterbank | minor | Q4 | resolved (answer B4); citation fix pending |
| P4-12 | FACT | the corpus gives no transition-time rule | CORRECT | Vorländer §11.7, last bullet before Fig. 11.42 | none | — | — |
| P4-13 | NUMBER | specular-only matching ≈ 9 dB low at s = 0.5 after 3 hits | CORRECT | Vorländer §3.3.2 Eq. 3.23, Fig. 3.10: (1−s)³ = 0.125 = −9.03 dB; §11.6 | none | — | — |
| P4-14 | FORMULA | exp(−6.91t/T), exp(−13.82Δt/T), ē_b formula | CORRECT | Vorländer §11.2.5 Eq. 11.13; ln 10⁶ = 13.82; ē_b = 10 ms × density of a truncated unit exponential; Eq. 11.51 | none | — | — |
| P4-15 | NUMBER | AX6 limits allow "T of order 160 s, e.g. α = 0.01 in a 100 m room" | IMPRECISE | Vorländer Eq. 4.32, 100 m cube: T = 267 s without air; Fig. 3.15 low-frequency D of 10⁻⁵ to 5·10⁻⁴ dB/m gives 151–263 s. 160 s holds only at the top of that range. The cap conclusion is unaffected. | minor | Q2 | resolved (answer B2); text fix pending |
| P4-16 | NUMBER | T30 on a 12 s IR only for T ≤ ≈ 20 s | CORRECT | Vorländer §6.4.1 (−5 to −35 dB); 12·60/35 = 20.6 s | none | — | — |
| P4-17 | FACT | the Schroeder EDC is monotonic | CORRECT | Vorländer §6.4.1 Eq. 6.4 | none | — | — |
| P4-18 | NUMBER | C80 jnd 1 dB stated only for 500–1000 Hz | CORRECT | Vorländer §6.4.4 Table 6.1 | none | — | — |
| P4-19 | FACT | open_field: every window entry is zero for any s | CORRECT | Vorländer §3.3.2 Eq. 3.23 (both parts ∝ 1−α = 0). The 1.4 ms floor delay is fixture geometry and not checkable here. | none | — | — |
| P4-20 | FORMULA | AX16 scattered entry E·(1 − Π(1−s)^hits) | CORRECT | Vorländer Eq. 3.23 applied per hit | none | — | — |
| P4-21 | NUMBER | √V ms as the widely used perceptual mixing-time estimate | NOT CHECKABLE | not in the corpus; needs a perceptual mixing-time source | none | — | — |
| P4-22 | NUMBER | AX11 σ₁ table; σ₁ ∝ 1/√(B·T) | NOT CHECKABLE | not in the corpus (ISO 3382-2 annex / Davy would settle it) | none | — | — |
| P4-23 | NUMBER | all R rules and table cells, 1458/288/41, dead_booth 2187/36/675 | CORRECT (arithmetic) | every cell recomputed, rounding up | none | — | — |
| P4-24 | NUMBER | n ≥ 51 gives a relative SE of σ̂ ≤ 10 % | NOT CHECKABLE | the arithmetic holds; the formula is sampling statistics, outside the corpus | none | — | — |
| P4-25 | NUMBER | gate tolerances (±5/10 %, ±2 %, ±0.5 dB, 1 dB seam, −60 dB) | NOT CHECKABLE | chosen tolerances; each is tighter than the Table 6.1 jnd where one exists | none | — | — |
| P4-D1 | DECISION | AQ2 Eyring noise tail | CONSEQUENCE | Vorländer §4.4, §4.4.1: non-diffuse rooms and concentrated absorption will differ | minor | — | open (Expert, Phase 05) |
| P4-D2 | DECISION | AX4 fixed atmosphere | CONSEQUENCE | Vorländer §3.6 Fig. 3.15: humidity matters strongly at 1–10 kHz, so the HF decay is fixed to one atmosphere | minor | — | open (product decision) |
| P4-D3 | DECISION | AX16 scattered energy at the specular time | CONSEQUENCE | Vorländer §3.3.2 Fig. 3.9: scattered paths are longer, so their temporal smearing is not represented | minor | — | open (product decision) |
| P4-D4 | DECISION | AX20 time-bounded image list | CONSEQUENCE | Vorländer §11.6; cost grows with t_mix | none | — | — |
| P4-D5 | DECISION | mixing-time rule, window, 5 ms fade, 12 s cap, test rooms | CONSEQUENCE | Vorländer §11.7: no corpus rule, so the rule is unvalidated against a reference | none | — | open (existing Expert question) |
| P4-S | SOFTWARE | Rng.h PRNG, seed offsets, `Kind::OmniEarly`, cache, filterbank reuse, contract bump, goldens, NaN/denormal check, bit-identity, AQ10 timing | listed, not rated | — | — | — | — |

**Round 1: builder answers** (corpus 22dc9dd; working shown; ISO 9613-1 values are outside the corpus and marked so).

- **B1 (Q1, P4-03).** Room 20×30×10 m: V = 6000 m³, S = 2200 m². AX4 is 20 °C, 50 % RH. Fig. 3.15
  (Vorländer §3.6) puts D at 4 kHz at the order of 10⁻² dB/m for 40–80 % RH. The ISO 9613-1 value at
  20 °C/50 % RH is ≈ 0.028 dB/m (not in the corpus; the `AirAbsorption` unit test pins it). Then
  m = 0.028/4.34 = 6.45·10⁻³ m⁻¹ and 4mV = 155 m². x = 0.174 needs −S ln(1−ᾱ) = 890, so ᾱ_4k ≈ 0.33.
  For D from 0.02 to 0.04 dB/m the same 8 % needs ᾱ_4k from 0.25 to 0.44. The general statement from
  Eq. 4.32 is: the error is (1+x)/(1+x/2) − 1. It runs from 0 in absorptive rooms up to +100 % as air
  dominates. The figure is explanatory, and no gate depends on it. Proposed wording: "≈ 8 % too long a T
  at 4 kHz in a 20×30×10 m room with ᾱ_4k ≈ 0.33 (up to 2× where air absorption dominates)". Status:
  resolved as answered; the text change is Maisara's.
- **B2 (Q2, P4-15).** A 100 m cube with α = 0.01: −S ln(0.99) = 603 m², and 0.161·10⁶/603 = 267 s
  without air. With D at 63 Hz ≈ 10⁻⁴ dB/m (Fig. 3.15 low-frequency range; the ISO 9613-1 order of
  magnitude, outside the corpus), 4mV = 92 m² and T ≈ 232 s. The "160 s" is reached only at
  D ≈ 5·10⁻⁴ dB/m. Proposed wording, here and in AX6: "of order 200–270 s". This strengthens the point
  that only the 12 s cap bounds the IR. Status: resolved; the text change is Maisara's.
- **B3 (Q3, P4-10).** Yes. The equal-power choice rests on incoherent energy addition, Vorländer §4.3
  Eq. 4.14–4.16: for broadband signals the cross term averages out and powers add. That is the
  condition under which sin/cos amplitude windows keep the power constant. §9.2.1 only shows that
  constant overlap power is the goal in segmented convolution. The citation should read "Vorländer §4.3
  Eq. 4.14–4.16; cf. §9.2.1". The 3 dB dip of equal-gain windows follows from the same equations
  (0.5² + 0.5² = 0.5). Status: resolved; the citation change is Maisara's.
- **B4 (Q4, P4-11).** No. §11.7 covers ringing from coarse interpolation of octave-band
  reflection-factor spectra (Fig. 11.41). Ringing of the octave-band analysis filterbank is not
  addressed in the corpus, so the claim is NOT CHECKABLE. The plan already treats it as a measured,
  reported check (scope 3, ē_b). The parenthetical citation should be dropped or replaced by "not
  covered by the corpus". Status: resolved; the citation change is Maisara's.
- **Interrogator aside (P4-S, not corpus).** The builder agrees, from the C++ standard
  ([rand.eng.mt], [rand.dist]) and outside the corpus. The `std::mt19937` output sequence is fixed by
  the standard (the 10000th output is required to be 4123659995). `std::normal_distribution` and the
  other distributions are implementation-defined. The AX5 sentence should read "the standard library
  distributions (e.g. `std::normal_distribution`) are not portable". The conclusion stands: use a
  self-contained PRNG with its own Gaussian transform.

**Status after round 1:** no blockers. P4-03, P4-10, P4-11, P4-15 resolved as answered. P4-D1–D3 stay
open as stated consequences (decisions, not questions), and P4-D5 stays open under the existing Expert
question.

**Remaining (Maisara's decision; target unchanged):** text fixes from B1 (state ᾱ_4k, or give the
general form), B2 (160 s → of order 200–270 s, also in BUILD_PLAN AX6), B3 (equal-power citation
§4.3 Eq. 4.14–4.16), B4 (drop the §11.7 filter-ringing citation), and the AX5 mt19937 wording. Carried
over from the earlier phase-04 run: the Expert questions on the mixing-time rule and on sparse or
non-diffuse fields, and the AQ10 / phase-13 "order 30" rebuild-budget follow-up.

## docs/phases/phase-04.md — 2026-11-05 (expert consultation on P4-D1–D3, P4-D5, sparse fields; corpus 22dc9dd)

Maisara asked the interrogator to act as the subject-matter expert and to recommend alternatives.
Acoustic claims are from the corpus. PRD, BUILD_PLAN and the phase files were used only as
constraints. No plan file was edited; adopting any of this goes through `/fix-plan`.

**Cross-cutting finding X.** Checked by the main session against phase-03 scope 1 and BUILD_PLAN AX16.
- Phase 03 renders only specular energy (1−α)(1−s) per hit, and the AX16 scattered entries are used only to set the tail level.
- So the rendered IR has no scattered energy before t_mix and has it after. For one path the mean level steps by 10·log(1/Π(1−s)^hits) dB: ≈ 11 dB at s = 0.4 after 5 hits (Vorländer Eq. 3.23). Kuttruff's example puts the diffuse share at ≈ 45 % at order 2 (Vorländer §11.6, Fig. 11.34).
- The Schroeder EDC is an integral (Eq. 6.4), so this step changes its slope, not its value, and the EDC-step gate does not detect it.
- Under AX16, specular + scattered = E_noScatter, so E_target does not depend on s. AX16 also never sends scattered energy toward absorbent faces, which is the mechanism that diffuses non-uniform rooms (§11.5).
- Severity: major (affects EDT, C80 and D50 of the hybrid IR, and the seam). Status: **open**.

| item | recommendation | confidence | would change | corpus basis |
|---|---|---|---|---|
| 1 Eyring, uneven α (P4-D1) | Keep Eyring in 04. Add a seeded Lambert-scattering stochastic ray tracer (energy multiplication) as a second decay predictor in Phase 05. Promote it to T60_b only if BRAS T30/EDT errors drop. Reject fitting the decay to the late ISM (pure specular, per X). | medium | AQ2, new AX, AQ10; phases 05, 04, 10, 13; no contract change | Vorländer §4.4, §4.4.1–4.4.2, §11.2, Tables 11.3–11.5, §11.5–11.6.1; Toole Box "Calculating reverberation time" (no universal formula). Millington, Kuttruff correction and Fitzroy/Arau formulas NOT CHECKABLE. |
| 2 fixed atmosphere (P4-D2) | Keep AX4. Report a per-band T bound at 30 % and 70 % RH. Add a render_cli atmosphere override for validation only. | high (keep) / medium | AX4; phases 04, 05; no contract change | Eq. 4.32 with the Vorländer Annex air table, rooms from Table 11.2, ᾱ = 0.15: 8 kHz −12 %/+6 % (1000 m³), −17 %/+10 % (10000 m³); 4 kHz −4 to −7 %; Begault Ch. 3 |
| 3 AX16 timing (P4-D3) | Render the scattered entries before t_mix as seeded noise on an energy-preserving causal kernel, so specular + scattered is continuous across t_mix. Keep the AX16 list for matching. A physical transfer (ray tracing or diffuse rain) comes later. | medium | AX16, new AX; phases 04, 05, 08; no contract change | Eq. 3.23, Fig. 3.9, Figs. 11.34, 11.35, 11.42, Eq. 11.51; kernel shape NOT CHECKABLE |
| 4 mixing time (P4-D5) | Keep the k_eff ≥ 19 rule, restated as "1 dB expected level precision" (Eq. 11.9/11.17, Table 6.1). Don't lengthen t_mix before item 3. In Phase 05, compare floors at t_dir + 80 ms and + 140 ms. | medium | phase-04 scope 2 wording; phases 04, 05 | Blauert Ch. 3 §3.3; Vorländer §6.4, §11.6.1, §11.7, §15.3; Begault Ch. 3/4; √V NOT CHECKABLE |
| 5 sparse fields | Require realised k_eff ≥ 19 as well as the expected value. Extend the time-bounded ISM up to a cap. Prune zero-energy images. Report k_real, the realised σ and diffuseness ψ. open_field keeps E_b = 0. | medium-low | new AX (cap, realised-k rule), AX20, AQ10; phases 04, 05, 10, 13 | Vorländer §4.4, §4.4.2, Table 4.1, §11.3.3, §15.2.3; Zotter & Frank §A.6.2 Eq. A.82 (ψ on image sums NOT CHECKABLE) |

**Proposed falsifiable checks:**
1. Ray-traced T within ±5 % of Eq. 4.32 for uniform α and s = 1. In Phase 05, a lower mean |T30 error| at 500 Hz–2 kHz in the BRAS rooms with uneven absorption.
2. A unit test that T60_b moves by the Eq. 4.32 prediction when m_b is swapped.
3. A 10 ms-bin ensemble envelope with no step > 1 dB across t_mix ± 5 ms, plus a Phase 05 C80 error no worse than with AX16 as is.
4. With item 3 in place, BRAS EDT/C80 errors change by less than 1 jnd across the three handover times.
5. A flat-room test scene matches the Table 4.1 specular sum within ±1 dB.

**Requirement notes from the consult:** NFR-6 in the PRD is Persistence. Offline/realtime equivalence comes from AQ4, AX5 and Phase 10. Shoebox-only comes from AQ1/F3, not the PRD ("any environment"; B2 plans ray/beam tracing).

**Questions for Maisara and the Expert (open):**
1. Is the rendered early part meant to have no scattered energy (X)?
2. Is E_target meant to be independent of s?
3. Does the Annex air table agree with the ISO 9613-1 values AX4 uses? 50 % RH falls between rows that differ ≈ 1.5× at 4–8 kHz.
4. Should t_mix,e also require a realised k_eff ≥ 19?
5. If a ray-traced decay is adopted, room-averaged T60_b (cache stays position-independent) or receiver-specific?

## docs/phases/phase-04.md — 2026-11-05 (expert consultation, rounds 2–4: Kuttruff added, advocate, rebuttal; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Corpus c1b171f adds `kuttruff-room-acoustics.md` (Kuttruff, *Room Acoustics*, 6th ed., 2017). The other
13 files are byte-identical to 22dc9dd (git diff), so earlier citations stand.

The four reports are kept verbatim in `docs/review/phase-04-consult/`:
1. SME consult, 22dc9dd
2. SME re-consult with Kuttruff
3. advocate cross-examination
4. SME rebuttal

The advocate was given the SME reports as written, without the main session's summary. The SME answered the advocate's questions in one rebuttal round.

**Main-session spot checks:**
- Kuttruff Table 5.2 (Eyring and iteration columns) and Table 6.1 (m of air at 20 °C) match the values used.
- phase-12 expects slap echoes in `courtyard`.
- Izhaki "Early reflections (ERs)": ER level indicates room size; ERs carry most of the spatial information.
- Not independently re-derived by the main session: the open_field scattering integral, the q_d flat-room value, γ²-Eyring. The SME and the advocate each computed these and agree.

**Corrections the SME made to its own earlier reports:**
- Its proposed Eyring check (s = 1, uniform α, ±5 %) would fail. Kuttruff Table 5.2 puts Lambert rooms 5–10 % above Eyring.
- Its ray-tracing cost was understated (Kuttruff §9.8: 10⁵–10⁶ particles).
- Millington–Sette is rejected (Kuttruff §5.4).
- Eyring with arithmetic ᾱ is the correct diffuse-field result. The error comes from lost diffuseness, not uneven α as such (§5.2, §5.4).
- In the rebuttal it withdrew three things: the a* tail decay (item 3), the specular-share t_mix (item 4) and q_d (item 5). It also accepted that its check C3 was circular.

| id | final position (SME and advocate) | agree? | status |
|---|---|---|---|
| X-a | The hybrid IR has no scattered energy before t_mix. The step is ≈ 0.9 / 1.8 / 4.9 / 8.7 dB for s = 0.05 / 0.1 / 0.25 / 0.4 in the AQ10 room. The EDC gate cannot see it (Eq. 6.4). Add a reported-only 10 ms envelope-step metric. | yes | open: needs Maisara's decision (Q1) |
| X-b | AX16 energy accounting is exact for uniform α (Kuttruff §5.2). A bias of unbounded sign and size appears with uneven α (§4.5, §4.6 Gilbert, Table 5.2). Phase 05 groups errors by absorption contrast. | partly | disputed: an unquantified per-path hit-count residual even with uniform α |
| 1 | Keep Eyring in 04. Add radiosity a* (§5.7) as a Phase 05 reference in `tools/acoustics`; promote on BRAS evidence only. γ²-Eyring for information only: it moves T away from the iteration in Table 5.2 cases 2 and 4. | yes | resolved (to adopt via /fix-plan: phase-05 scope line) |
| 2 | Keep AX4. Report a humidity bound in Phase 05: 8 kHz −11.6 % / +17.2 % at 40 / 70 % RH in a 10 000 m³ room (Kuttruff Table 6.1, Eq. 5.24). Add a validation-only render_cli override and an `AirAbsorption` test against Kuttruff Table 6.1. No UI display. | yes | resolved (to adopt); Q3 answered by that test |
| 3 | Inject early scattered energy (Lambert, Eq. 4.24, Gilbert §4.6) as a Phase 05 Python reference hybrid. Promote to `src/sim` in a later phase only if EDT/C80 errors drop. The tail decay source is decided by item 1's evidence, not a*. | yes | resolved (direction); open: Maisara's Q1 |
| 4 | Keep the k_eff ≥ 19 rule and add a realised-k condition. No specular-share re-derivation (0.7–1.4 s, up to 8·10⁴ images). Compare 80 / 140 ms handovers in Phase 05. | yes | resolved (to adopt); the rule itself remains an Expert question |
| 5 | Realised k plus capped ISM extension (§4.1, Eq. 4.3). Report per-axis energy shares, not q_d (q_d ≈ 0.85 for a 1-D flat-room field). No diffusion-equation fallback (§4.6). | partly | disputed: per-axis shares are also only necessary (they miss three-axis flutter); no threshold; cap to be measured against AQ10 |
| OF | Keep E_b = 0 for open_field. Recast "< −60 dB after 50 ms" as an AX16 consistency check, not physics. Lambert floor scattering with the fixture geometry gives −23 to −43 dB per band (exact integral). AX17's broadband s overstates LF ground scattering. | yes | resolved (to adopt via /fix-plan) |
| C1 | The a* test reproduces Table 5.2 by calling the solver directly (α = 0 is forbidden in scenes by AQ3). | yes | resolved |
| C3 | The s = 1 hybrid test is circular. Mixed-s reference: an independent Kuttruff §9.8 ray tracer, plus Vorländer Table 4.1 (plot-read). | yes | resolved |
| C5 | Flat-room (Eq. 4.3) and 1/t (Eq. 4.16) tests with α ≥ 0.01, air absorption and the ISM cap. | yes | resolved |

**Remaining for Maisara:**
1. Is the early part meant to have no scattered energy (X-a, items 3 and 4)?
2. Is E_target meant to be independent of s?

**Remaining for the Expert:**
- the mixing-time rule;
- a diffuseness criterion with a threshold (none in the corpus);
- the X-b residual;
- the gain of early scattering in real rooms (Phase 05).

**Caveat:** the SME and the advocate run on the same underlying model. Their convergence is a useful sign but not independent verification.

## docs/phases/phase-04.md (with phase-05, phase-06, phase-10, BUILD_PLAN) — 2026-11-05 (/fix-plan, consultation applied; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

This run applied the resolved items of the fresh pass (B1–B4, AX5 wording) and of the expert consultation (rounds 1–4 above).
- Plan-editor: 3 rounds. Interrogator: one decision round and 3 science-check rounds, the maximum.
- Commits: a016d0a (round 1, D1–D14 pending), then the round-2 commit, 380ef01 (cap counting, flat-room sum tolerance), and 048edf0 (FQ corrections).
- Change-log row: BUILD_PLAN §6, 2026-11-05, "Phase 04 expert consultation applied".
- New assumptions: AX21 (specular-only early part is a known deficit; Maisara decided on 2026-11-05 that it should contain scattered energy) and AX22 (realised-k switch and image-count cap). New backlog: B11, B12.
- No contract change and no golden changed.

**Decisions**

| D | decision | how decided |
|---|---|---|
| D4 (air) | 4mV in the denominator; equivalent to exp(−mR) in the a* kernel, and factors out for γ²-Eyring | **verified** by the interrogator (Kuttruff §4.5, Eq. 5.55, Eq. 5.29) |
| D9 (decay) | remove 60·0.010/T60_b dB between the envelope-step bins | **verified** (Vorländer Eq. 11.13) |
| D6 | switch rule: expected-k t_mix; ISM-only fallback to the cap if k_real < 19 at 500 Hz–2 kHz; a single jump point, with the crossfade dip measured in Phase 10 | Maisara. Options (a)–(c) had CONDITIONS VIOLATED or PRODUCT MATTER verdicts. Only (d) was continuous, and it dropped the sparse-room fallback. |
| D1–D3, D4 (γ²), D5, D7, D8, D9 (bins, R), D10–D14, cap counting, flat-room sum tolerance, FQ-01 (96 cube elements), FQ-03 (gate bins with ≥ 19 expected images) | as listed in the §6 row | Maisara (no corpus answer: PRODUCT MATTER or NOT CHECKABLE), mostly following the interrogator's lean |

The main session computed one fact from the code: the repository's ISO 9613-1 implementation (`src/sim/AirAbsorption.cpp`) matches Kuttruff Table 6.1 within 0.7 % at 0.5–8 kHz and 40/50/70 % RH (6.83 against 6.84·10⁻³ m⁻¹ at 4 kHz / 50 %). So the code is consistent with Kuttruff, and the coarse Vorländer Annex bins account for the disagreement between the two books. This also corrects the builder answers B1 (0.028 dB/m should be ≈ 0.0297) and B2 (T at 125 Hz ≈ 160 s, so the original "160 s" was right for that band).

**Science checks**
- Round 1: FP-01–FP-15. Three major CONDITIONS VIOLATED: the flat-room conditions, rigid walls for Eq. 4.16, and the all-Lambert Eq. 4.28. All fixed.
- Round 2: FQ-01–FQ-10. Three major: the 88-element cube layout, the γ² "≤ 0.3 %", and the early 1/t bins. All fixed.
- Round 3: nothing WRONG. Remaining findings:

| id | kind | item | verdict | evidence | severity | status |
|---|---|---|---|---|---|---|
| FQ-11 | NUMBER | γ² "≤ 0.3 % in case 4, 0.38 against 0.40" | IMPRECISE | Kuttruff Eqs. 5.33–5.34: 0.34 %. 0.38 is interpolated, not a Table 5.1 row. | minor | open |
| FQ-12 | NUMBER | one-absorbing-wall gate ±1 dB on bins with ≥ 19 expected images, "expected scatter ≤ 1 dB" | CONDITIONS VIOLATED | Vorländer Eqs. 11.7–11.9/11.17: σ ≈ 1 dB at 19 counts, so ±1 dB is a 1σ bound and about a third of bins would fail under that model (AX11 uses tol/3). Lattice counts are deterministic, so the corpus doesn't settle it. The main session's own recommendation caused this. | major | open: needs Maisara (e.g. ≥ 171 images for 3σ, or ±3 dB) |
| FQ-13 | NUMBER | crossfade "≈ 4.4 dB at 10:1" | IMPRECISE | the mid-fade dip is 3 dB at any ratio; 4.4 dB is the largest dip (g ≈ 0.24) relative to power-linear interpolation, which the text should name | minor | open |
| FQ-14 | FACT | "Table 6.1 prints 2–3 significant figures" | IMPRECISE | it prints two decimals (2–4 significant figures); the ±0.8 % is unaffected | minor | open |

**Still open:**
- FQ-11 to FQ-14 (FQ-12 needs Maisara's choice; the other three are wording).
- Expert questions: the mixing-time rule, a diffuseness threshold, the X-b residual, and the size of early scattering in real rooms (Phase 05).
- Follow-up: AQ10 and phase-13 still state the rebuild budget "order 30".

## docs/phases/phase-04.md (with phase-05, phase-10, BUILD_PLAN) — 2026-11-05 (/fix-plan, FQ-11–FQ-15; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

**FQ-12: decided by the `decider` agent.** It was run under `.claude/agents/decider.md` as a general-purpose agent, before that agent type had loaded. Maisara accepted the proposal by running /fix-plan on it.
- The decision: gate the one-absorbing-wall test at ±1 dB per **100 ms** bin. The bins start at t_on = max(t₁₉, (2L − z_s − z_r)/c, |z_s − z_r|/c) and end at the AX22 cap. The level is analytic, from the two image planes (Kuttruff §4.3, Eqs. 4.14–4.16), with no fitted constant. A partial final bin is gated if it holds ≥ 171 images. At least 3 gated bins are asserted.
- Rejected:
  - ±1 dB per 10 ms bin (1σ; 1.3 % of geometries pass);
  - ≥ 171 images per 10 ms bin (vacuous: reached only after the cap);
  - ±3 dB (12–18 % of correct geometries fail, and the tolerance is the size of a real bug).
- The lattice statistics were computed by the decider (not corpus).

**Interrogator verification** (round 1, nothing WRONG):
- t₁₉ = 0.257 s.
- The first 100 ms bin holds 227 images, which is ≥ 190.
- σ = 0.315 dB, so 3σ = 0.94 dB.
- The partial-bin threshold of 171 gives 3σ = 0.996 dB.
- The image-plane onset terms and the absolute level are consistent with Kuttruff §4.1, §4.3 and Eq. 9.24 (derived).
- 8 full bins plus a gated partial bin fit before the 37 880-image cap (t = 1.104 s).
- FQ-13 and FQ-14 are fixed.
- FQ-11: one minor finding.

| id | kind | item | verdict | evidence | severity | status |
|---|---|---|---|---|---|---|
| FQ-15 | NUMBER | γ² sensitivity "≈ 0.34 % (0.38 interpolated)" | IMPRECISE | linear interpolation gives γ² = 0.376, and Kuttruff Eqs. 5.33–5.34 then give ≈ 0.40 % | minor | resolved (main session: "≈ 0.4 %, γ² ≈ 0.376" in phase-05 and the §6 row) |

**Status:** FQ-11–FQ-15 resolved. Commits: b9309b1, plus the FQ-15 commit.

**Still open:**
- Expert questions: the mixing-time rule, a diffuseness threshold, the X-b residual, and the size of early scattering in real rooms (Phase 05).
- Follow-up: AQ10 and phase-13 still state the rebuild budget as "order 30".
