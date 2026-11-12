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

## docs/phases/phase-04.md (with phase-05, BUILD_PLAN) — 2026-11-05 (/fix-plan, former Expert questions closed; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

**Decisions.** All are product choices by the `decider` agent, accepted by Maisara on 2026-11-05. Its reports are in `docs/review/phase-04-consult/`: report 5 (D1–D4) and report 7 (gate details).

- **D1 (mixing time).** The "Expert may revise" clause is closed. Phase 05 arbitrates by running the three handovers on the Phase 04 IR and on the reference-hybrid IR; the hybrid run is the arbiter.
- **D2 (diffuseness threshold).** Closed: no code path or gate needs a threshold, and Kuttruff §8.5 gives none. Eyring's diffuse-field presumption is measured in B12.
- **D3 (X-b).** Bounded by ΔL_b in Phase 05, read against a 1 dB rule.
- **D4 (B11 promotion).** Two checks:
  - (A) an independent ray-tracer gate;
  - (B) the BRAS paired comparison must be "not worse". This was relaxed from "better" on the decider's challenge, accepted by Maisara.
- **Report 7 (gate details):**
  - δ = 0.25 jnd, with SE ≤ threshold/3;
  - a paired pilot of n ≥ 51 runs, then R ≥ max(144·σ₁,Δ², 9·σ₁,Δ,room², 9·σ₁,Δ,pair²);
  - ray-tracer gate k ≥ 684 (tracer 3σ = 0.498 dB, 0.5 dB systematic budget);
  - N₀ = ⌈254·V⌉ (Vorländer Eq. 11.12), doubled up to 16·N₀ and then fail;
  - α = 0.15 for the s-cases.
- **Verified by the interrogator:**
  - DN3: Table 5.2 layouts 4–6 run at s = 0.1, 0.25 and 0.4 plus the s = 1 anchor (s = 1 alone is circular, ledger C3);
  - DN4: the 10×20×30 m room, in Table 5.2's notation.

**Science checks.**

- **Round 1** (report 6), nothing WRONG:
  - FE-01, major: zero-margin "not worse"/"lowers" can be decided by residual paired tail noise. Fixed by δ and the SE rule.
  - FE-02, major: k = 171 left no systematic budget. Fixed by k ≥ 684.
  - FE-03 to FE-07, minor or none. Fixed.
- **Round 2**, nothing WRONG:
  - all FE items confirmed fixed, with the arithmetic redone (144σ², 0.135 %, 0.498 dB, N₀ = 253.9·V, the false-failure figures);
  - two minor items, below.

| id | kind | item | verdict | evidence | severity | status |
|---|---|---|---|---|---|---|
| FG-01 | NUMBER | "0.135 % … at a true Δ on the wrong side of zero" | IMPRECISE | 0.135 % is the false failure at Δ = 0 for "not worse"; for "lowers" it is the false pass at Δ = 0 and the false failure at Δ = −2δ; the two-sided rule passes falsely with 0.27 % | minor | resolved (main session: error rates stated per rule, phase-05) |
| FG-02 | FACT | "residual tail noise survives the pairing (Vorländer §11.2.5)" | IMPRECISE | §11.2.5 concerns ray-tracing fluctuations; survival follows from the tail starting before 80 ms and the EDC integral (Vorländer Eq. 6.4; derived) | minor | resolved (main session: reason restated, §11.2.5 cited by analogy) |

**Status:** all former Expert questions are closed in the plan; FE-01 to FE-07, FG-01 and FG-02 are resolved.

**Remaining:**
- Empirical, to be settled by Phase 05 or the B11 phase: BRAS room coverage, σ₁,Δ, ΔL_b, and the ray-tracer bias. Each has a decision rule in the plan.
- Old follow-up: AQ10 and phase-13 still state the rebuild budget as "order 30".

## docs/phases (phase-04, 05, 05b, 08, 10, 13) and BUILD_PLAN — 2026-11-05 (/fix-plan, open items closed; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d; external sources: researcher report 9)

Sources, kept verbatim in `docs/review/phase-04-consult/`:

| report | what it is |
|---|---|
| 8 | decider, open items |
| 9 | researcher, BRAS and priors; external, cited by DOI |
| 10 | interrogator, check of the report-8 diff |
| 11 | decider, DN-1, FR-01–05 and the researcher findings |
| 12 | interrogator, pre-check of report 11 |

The researcher's second-dataset search was still running when this entry was written.

**Decisions, all accepted by Maisara on 2026-11-05**

*Report 8*
- **AQ10:** the budget is a position-only rebuild, measured as workloads W1 (no fallback) and W2 (AX22 fallback at N_cap). Order 30 now applies only to omni-early.
- **N_cap:** ν_r(i₀) for the largest i₀ ≥ 10 that meets W2. Frozen, with a sensitivity report at ν_r(2i₀).
- **Measurement-rule repairs:**
  - room selection is committed before any result is seen;
  - zero suitable rooms: Phase 05 is done without BRAS, and the measured part moves to 05c;
  - R > 2 000: run if ≤ 24 h, otherwise δ goes to Maisara;
  - branches for an (A) failure and for tracer bias.
- **New v1 phase 05b**, early scattered energy (B11), placed before 08.
- **B12 and B10:** decision rules added.
- **AQ9 failures:** go to Maisara.
- **Switch-point dip:** gated ≤ 1 dB (decider challenge, accepted).

*Report 11*
- **DN-1, rendering:** equivalent-reflection pulses at the Kuttruff Eq. 4.6 density, with a floor of one pulse per 1 ms step.
- **DN-1, patches:** a frozen absolute patch size, floor 0.343 m.
- **FR-01:** the exact Phase 10 dip gate.
- **FR-02 to FR-05:** applied.
- **BRAS:** results are evidence, not validation; G is not evaluable; B12 uses the initial α set only.
- **C1 and C2:** |ΔL_b,tr| trigger; BRAS-only B12 results labelled "input-limited".
- **Second measured dataset:** required before the Phase 13 beta.

*DN-A*
- **Window:** the padded whole early part, verified by the interrogator.
- **Tolerance:** 3σ of the exact random-sign scatter, gated where ≤ 1 dB (the interrogator's proposal, adopted by Maisara).

**Verification**
- **Report-8 diff (report 10):** nothing WRONG.
  - FR-01, major: the f ≤ 0.41 bound assumed equal segment powers; fixed by report 11.
  - FR-02 to FR-05: minor.
  - DN-1 rendering option (c), envelope only: rejected as WRONG for audio.
- **Report-11 pre-check (report 12):** two WRONG items, both corrected before applying:
  - the energy-exactness claim was valid only in the tap domain;
  - the continuity threshold: 0.79 gives a 0.48 dB dip, and 0.59 gives 1 dB.
- **Report-11 diff:** nothing WRONG. FS-01 (signed trigger) and FS-02 (2.6×, not 3×) are fixed. DN-A tolerance option (b) was rejected as the wrong fluctuation model.
- **Main session:** re-ran the FR-01 bounds (0.411 / 0.324 / 0.206) and the density figures (1 300 s⁻¹; t_floor 109 / 17 ms).

**Deliberately left to the phase sessions (low stakes)**
- DN-B: the room set for the t_mp context.
- DN-C: which of the two Phase 10 self-test forms to use.

**Status:** no open plan decisions.

**Waiting on data**
- BRAS material files (Phase 05).
- Paired-comparison noise (Phase 05).
- Tracer results (05b).
- The second dataset, which Maisara will choose from the researcher's candidates.

## docs/phases/phase-05d.md (new), phase-05, 05b, 13, BUILD_PLAN, THIRD_PARTY — 2026-11-05 (second measured dataset; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d; external sources: researcher reports 13, 14, 16, 17)

Sources, verbatim in `docs/review/phase-04-consult/`:

| file | agent | content |
|---|---|---|
| 13 | researcher | candidate datasets |
| 14 | researcher | Arni, Bologna and May et al. verified |
| 15 | decider | dataset choice |
| 16 | researcher | BRAS CR2–CR4 materials and priors |
| 17 | researcher | citations and licences verified |
| 18 | decider (report 16) | 05d D1–D7 |
| 19 | interrogator | 05d check |
| 20 | decider (report 17) | follow-ups |
| 21 | interrogator | final 05d check |

Draft email for the DELTA panel report: `docs/review/drafts/delta-report-request.md`. Not sent; Maisara sends it.

**Decisions (all accepted by Maisara, 2026-11-05)**

*Datasets and phase structure*
- Second source: Arni and dEchorate (CC BY 4.0, verified on the live records).
- New phase 05d, after 05. Phase 05b is independent of it; Phase 13 depends on it.
- Labels: "evidence, not validation", plus the input-matched distribution test.
- The measured-α bar is kept for the word "validated". Commissioning a measured room is decided after 05/05d.
- Wording: "compared with measured rooms (evidence)".
- §1 BRAS row corrected (decider challenge).

*Phase 05d rules*
- D1–D7:
  - seeded per-n sample and configuration-disjoint pairs;
  - log-ratio d with the a* orientation;
  - signed 500 Hz–2 kHz mean;
  - Annex scattering and α rules, with an s/2 sensitivity run;
  - Arni atmosphere rule;
  - dEchorate reflection rules;
  - descriptive output when too few pairs.
- Mean |d̄| and the hybrid-IR EDT/C80 are printed.
- Follow-ups:
  - noise-model d = 0 reference, and RMS of the measured placement spread;
  - selector at a common atmosphere;
  - "α-limited" ΔL above α 0.48;
  - 20 dB per-band amplitude-sum isolation.
- Last choices:
  - dEchorate pairs need equal perimeter against perpendicular rigid surfaces; panel gaps are reported;
  - the noise model matches each measured IR;
  - the level window is centred on the predicted arrival.

**Verification**
- **Check 19:** nothing WRONG in the plan text.
  - Major findings: B1 (atmosphere vs. selector), B2 (edges against perpendicular surfaces), B3 (2 dB bound only for α ≤ 0.48), B4 (coherent leakage 2.4/3.3 dB at 10 dB isolation). All fixed.
  - Minor findings: B5–B9, all fixed.
  - It also corrected the main session: the recomputed humidity effect of 0.89 % was wrong (air counted twice). The decider's 0.95 % stands.
- **Check 21:** B1–B9 confirmed fixed; arithmetic confirmed: 0.480 / 0.594; +0.828 / −0.915 dB; 1.752 dB; 0.0181. Nothing WRONG.
  - N1 (major): leakage outside the counted window. Fixed by Maisara's choice: the level window is centred on the predicted arrival and neighbours are counted over ±(2.5 ms + h_b).
  - N2 (major): the perimeter rule must count only rigid surfaces (Kuttruff §8.7). Fixed.
  - N3 (minor): Eyring cancellation is exact only at a common atmosphere. Fixed.
- This was the third check round, the /fix-plan limit. The N1–N3 fixes follow the interrogator's stated readings and Maisara's choice, and were not re-checked.

**Status:** phase-05d has no open items.

**Remaining**
- Empirical: which dEchorate configurations include the omni source (in the dataset metadata, read by the 05d session), the BRAS areas, and all measured numbers.
- Maisara: send the DELTA request.

## BUILD_PLAN AX23 (Phase 04 session) — 2026-11-05

Numbering: interrogated as "AX21"; renumbered **AX23** (rows AX23-1 … AX23-17) when main's phase-04 plan update assigned AX21 (specular-only early part) and AX22 (realised-k switch). Content unchanged.

Interrogator on the proposed AX23 row (signal and meter of the Phase 04 decay-time gates), corpus
revision 22dc9dd. Builder answers and the resulting changes to the row follow the table.

| id | kind | item | verdict | evidence | severity | status |
|---|---|---|---|---|---|---|
| AX23-1 | NUMBER | m_8k = 0.0242 1/m at 20 °C, 50 % RH | WRONG (vs corpus) | Vorländer air table: 20.3·10⁻³ (30–50 %) / 13.5·10⁻³ (50–70 %) 1/m at 8 kHz; ISO 9613-1 (AX4) not in the corpus | major | resolved: attributed to ISO 9613-1 (AX4), marked unchecked against the corpus, corpus value quoted |
| AX23-2 | NUMBER | air-only T60 limit 8 kHz ≈ 1.66 s | WRONG (input) | 0.161/(4m), Eq. 4.32: 1.98 s with the corpus m | major | resolved as AX23-1 |
| AX23-3 | NUMBER | air-only T60 limit 4 kHz ≈ 5.9 s | WRONG (vs corpus) | corpus m gives 6.94 / 9.82 s | major | resolved as AX23-1 |
| AX23-4 | FACT | air caps T60 in any room; m = D/4.34 | CORRECT | Vorländer Eqs. 4.32/4.34, notation D = 4.34 m | – | – |
| AX23-5 | FACT | "always ≥ 2:1 between 4 and 8 kHz" | WRONG as stated | Eq. 4.32: ratio < 2 below T_wall ≈ 3.8 s; concert_hall_box 1.77 | major | resolved: reworded to "in rooms like stone_box … ≈ 1.8–2.2 : 1" |
| AX23-6 | FACT | octave filters read the faster band long (leakage) | NOT CHECKABLE | corpus silent on filter-skirt bias | – | – |
| AX23-7 | NUMBER | measured biases | NOT CHECKABLE | project measurements, reproducible | – | – |
| AX23-8 | NUMBER | half octave = centre · 2^±¼ | CORRECT | Vorländer §1.8 Eqs. 1.39/1.40 | – | – |
| AX23-9 | NUMBER | Kaiser FIR spec | NOT CHECKABLE | no filter-design source in the corpus | – | – |
| AX23-10 | FACT | half-octave reading acceptable for an octave Eyring T60 | NOT CHECKABLE | §1.8 standard bands octave / third octave; nothing forbids it | – | open (Expert) |
| AX23-11 | NUMBER | R × 2 for half octaves | CORRECT (given AX11) | bandwidth ratio 2.03, round up | – | – |
| AX23-12 | FACT | half-octave FIR too long below 1 kHz | NOT CHECKABLE | – | – | 1–2 kHz data added (Q4) |
| AX23-13 | FACT | early part dominates high-band EDC start at C80 ≈ +5 dB | CORRECT (given C80) | Eq. 6.7: EDC(80 ms) = −6.2 dB | – | – |
| AX23-14 | FACT | tail-only T30 stands for "T30 of the generated IR" | INCONSISTENT | §6.4.1 evaluates T on the whole IR | major | resolved: the row says the gate is on the tail; hybrid T30 reported; the join is gated by the seam test |
| AX23-15 | DECISION | hybrid T30 not gated | CONSEQUENCE | §11.7 no rule for the transition | minor | noted in the row and PR |
| AX23-16 | DECISION | two meters in the gate bands | CONSEQUENCE | – | minor | noted in the row |
| AX23-17 | DECISION | EDT, C80 on the full IR | CONSISTENT | §6.4.1, Eq. 6.7 | – | – |

Builder answers: Q1 the Eyring reference and the generator use the ISO 9613-1 m_b of AX4 (D_b/4.343
from `sim::airAttenuationDbPerMetre`), so the corpus table is not used; Q2 the row now states that
the T30 gates read the tail; Q3 reworded; Q4 `dead_booth` 1 / 2 kHz: octave +0.3 % / −0.0 %, half
octave +0.0 % / +0.4 %; Q5 each realisation's pressure IR is FIR-filtered, then squared and averaged.

**Status:** AX23 committed with the corrections above. Open for the Expert: AX23-10.

## BUILD_PLAN AX22 measured values and AX23 re-check (Phase 04 session) — 2026-11-05

Interrogator on the AX22 values recorded in Phase 04 (PR #8) and on AX23 against corpus revision
c1b171f (adds Kuttruff, Room Acoustics). Corrections applied to the rows are listed after the tables.

| id | kind | item | verdict | evidence | severity | status |
|---|---|---|---|---|---|---|
| AX22-M1 | NUMBER | N_cap = ν_r(10) = 1 560 | CORRECT | Kuttruff §9.8 Eq. 9.23: (2/3)(2000+300+40) = 1560 (orders 1…i₀, direct not counted) | – | – |
| AX22-M2 | NUMBER | ν_r(30) = 37 880; ν_r(11…16, 20) | CORRECT | Eq. 9.23 | – | – |
| AX22-M3 | NUMBER | W1/W2 timings | NOT CHECKABLE | project measurements (CI logs) | – | – |
| AX22-M4 | FACT | rebuild time not proportional to image count | NOT CHECKABLE (internally consistent) | ×1.31 images, ×1.99 time from i₀ 10 → 11 | – | – |
| AX22-M5 | FACT | "steps where the early part's FFT size doubles" | NOT CHECKABLE; corpus-mean working does not support it | t_cap + 0.163 s = 26 112 / 27 840 samples at i₀ 10 / 11, same power-of-two block | – | resolved: sentence removed |
| AX22-M6 | NUMBER | t_cap ≈ 0.38 s at ν_r(10) | CORRECT | Kuttruff Eq. 4.6 integrated: 0.381 / 0.526 / 1.104 s at ν_r(10 / 14 / 30) | – | – |
| AX22-M7 | FACT | Eq. 4.6 time for a cap counted by ν_r(i₀) | IMPRECISE | Eq. 4.6 is the mean N-th arrival of any order, not the completion of orders ≤ i₀ | minor | resolved: row states arrival-order counting |
| AX22-M8 | NUMBER | jnd EDT 5 %, C80 1 dB | CORRECT | Vorländer Table 6.1 | – | – |
| AX22-M9 | NUMBER | jnd applied at 500 Hz–2 kHz | CONDITIONS VIOLATED | Table 6.1 states 500–1000 Hz | major | resolved: extension stated in the row |
| AX22-M10 | NUMBER | T jnd "working 5 %" | IMPRECISE | Kuttruff §7.6: ≈ 4 % | minor | resolved: noted in the row |
| AX22-M11 | FACT | 'cap limits accuracy' (39.7 jnd) | NOT CHECKABLE; follows from the rule | far above AX19 single-realisation scatter (≤ 2.2 jnd) | – | – |
| AX23-1 (changed) | NUMBER | m_8k = 0.0242 1/m | CORRECT (was WRONG vs corpus) | Kuttruff Table 6.1: 24.29·10⁻³ m⁻¹ at 50 % RH | – | – |
| AX23-2 (changed) | NUMBER | air-only T60 8 kHz ≈ 1.7 s | CORRECT | Kuttruff Eq. 5.24: 1.657 s | – | – |
| AX23-3 (changed) | NUMBER | m_4k, air-only T60 ≈ 5.9 s | CORRECT | Kuttruff Table 6.1: 6.84·10⁻³ → 5.885 s | – | – |
| AX23-6 (changed) | FACT | octave filter reads the faster band long | mechanism CORRECT in substance; magnitude NOT CHECKABLE | Kuttruff §3.8 Fig. 3.13, §8.4 | – | – |
| AX23-10 (re-checked) | FACT | half-octave reading for an octave Eyring comparison | NOT CHECKABLE | Kuttruff names octave / third-octave only | – | open (Expert) |
| AX23-18 (new) | FACT | filter, square, ensemble-average, then Schroeder | CORRECT | Kuttruff §8.4 Eq. 8.29 | – | – |
| AX23-19 (new) | FACT | "not checked against the corpus" (stale) | IMPRECISE | Kuttruff agrees with ISO; Vorländer annex differs | minor | resolved: row cites both |
| AX23-20 (new) | FACT | direct sound / early part shape a high-band EDC start | CORRECT in substance | Kuttruff §8.4 | – | – |
| AX23-21 (new) | FACT | 4 → 8 kHz ratio ≈ 1.8–2.2 : 1 with Kuttruff m | CORRECT | Eq. 5.24: 2.29 with a 6 s wall term | – | – |

**Status:** AX22 values committed with the corrections above; AX23 verdicts hold on c1b171f
(AX23-1…3 now CORRECT). Open: AX23-10 (Expert); which corpus air table AX4/AX23 should cite
(Kuttruff Table 6.1 agrees with ISO 9613-1; Vorländer's annex bins do not) is a plan question.


## docs/phases/phase-05.md — AX23 and Lundeby (2026-11-06) (/fix-plan; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d; external sources: researcher report below)

Trigger: the Phase 04 session reported that AX23 (octave-filter leakage reads decay times long at 4–8 kHz
when T falls steeply between bands; numbered AX21 on its branch) and the upper-hull change to
`metrics.lundeby` were not reflected in the Phase 05 plan. Chain run by the main session as orchestrator:
plan-editor (pass 1, DECISIONS NEEDED D1–D7) → interrogator ×2 → advocate ×2 (cross-examination) →
interrogator final verdicts → researcher (outside the corpus) → decider (D1–D7, N1, N2; addenda E1–E3,
G5-1, G5-4) → plan-editor passes 2–3 → interrogator final check, rounds 1–3. The advocate, researcher and
decider were run as general-purpose agents following `.claude/agents/<name>.md` verbatim (they were added
after this session started and are not registered in it). Decisions are proposals Maisara can veto.
Commits 2c1b785, 44eef9e, 0cb2068, 389ad46, 977c5f3.

### Decisions (interrogator final verdict → decider choice)

| id | question | interrogator final (after advocate) | decided | outside the corpus |
|---|---|---|---|---|
| D1 | meter at 1–8 kHz, sim vs meas | "fair because both carry the bias" CONDITIONS VIOLATED (bias depends on r and per-band leak D, Kuttruff Eq. 3.64–3.68 two-term model); half-octave NOT CHECKABLE (AX23-10); R 1.8 rejected; several options valid | (c): octave primary, AX23 half-octave beside on both IRs; "meter-dependent" flag at > 5 points; r printed; leak calibration recorded in AX23 | 5 % working jnd; half-octave meter; ISO octave practice |
| D2 | AQ9 bands | "BRAS rooms small" INCONSISTENT (145/2350/8650 m³); air-only bound CORRECT under conditions; product matter | (a)+(b): AQ9 on octaves, half-octave mean printed (never gating); per-room r from pair-mean T30, r > 1.1 → "leakage-sensitive" | 1.1 threshold (model-derived) |
| D3 | B12 meter | (a) not provably safe vs 1.25-point margin (bound 5.5 / 3.7 points on 2·mean); (c) robust | (c): B12 on both meters, else "meter-dependent, Eyring stays"; octave-only branch (E2) only with measured D ≥ 13 dB at r ≤ 1.1, S_all ≤ 0.42, S_room ≤ 1.67 points | branch thresholds |
| D4 | nightly gate | all valid; AX23(a)(i) reason imprecise for scope 4 | (b): octave all bands + half-octave 1–8 kHz, ±2 %; AX23(a) not applied, reason reworded | — |
| D5 | upper-hull Lundeby on measured IRs | "1.5–3 % T30" and "B·T ≲ 67" withdrawn; ≈ +0.45 % in AQ9 bands; plateau only for B·T ≲ 30–45 with ≳ 9T noise | (d): paired single-realisation test, 18 conditions gated ≤ 0.6 % (SE ≤ 0.15 %), noise 48/55/65 dB, BRAS-like fade; case B 125 Hz reported; §6 "unchanged" claim annotated | 0.6 % (half B12 margin), 48 dB |
| D6 | noise estimate | all valid | (c): iterative Lundeby estimate (Venturi et al. 2013 summary), BRAS 1024-sample fade trimmed, last-10 % cross-check flag | F7, F14, σ formula |
| D7+N2 | usable-range reference | peak and intercept references coincide only near 3.3 r_c; literal EDC rule laxer by 10·log10(1 + (r_c/r)²) | (c): peak rule (ISO 3382-1 §4.2.1/§5.2.1) AND the Lundeby late line at t₀, both ≥ 45/35 dB | 45/35 dB (ISO) |
| N1 | simulated EDC vs code | plan "integrated to the end" INCONSISTENT with code (sim IR goes through lundeby; ≈ 4·10⁻⁵ dB) | plan amended to one path; unit test ≤ 0.01 dB | — |

Researcher (sources read unless noted): ISO 3382-1:2009 §4.2.1, §4.2.2, §5.2.1 and ISO 3382-2:2008 §4.3.3–4.3.4,
§5.2.1 (previews); Venturi, Farina, Tronchin, POMA 19, 015006 (2013), doi:10.1121/1.4800277 (Lundeby summary;
leakage magnitudes); Brinkmann et al., JASA 145(4) 2746–2760 (2019), doi:10.1121/1.5096178, Table II (CR2
145 m³, T ≈ 2.0 s, d_c 0.49 m); Aspöck et al., BRAS documentation (2020), doi:10.14279/depositonce-6726.3,
§3.4.1 (omni RIRs 3.5 s, last 1024 samples Hann-faded). Not retrieved: Lundeby et al. 1995 original;
ISO 3382-2 Annex B threshold, §7 text and uncertainty constants; Jacobsen B·T rule; ISO 3382-1 Annex A table.

### Final check of the applied text

| id | kind | item | verdict | severity | status |
|---|---|---|---|---|---|
| G5-1 | NUMBER | air-only leakage bound stated only for 50 % RH | CONDITIONS VIOLATED | major | resolved (round 3: ≤ 2.5 % at 1 kHz (70 % RH), ≤ 7.1 % at 2 kHz (40 % RH); 50 % and CR2 values added; measured-r check is the rule) |
| G5-2 | NUMBER | "R ≥ 51 safe for σ₁ ≤ 1.5 %" | WRONG | major | resolved (≤ 1.4 %; R per band by the SE rule) |
| G5-3 | NUMBER | "2.9 dB at r = r_c" | IMPRECISE | minor | resolved (3.0 dB) |
| G5-4 | FACT | which r's D is used | IMPRECISE | minor | resolved (decider: D₁ = D + 10·log10 r; entry at r_i ≤ 1.1; lookup with D₁,min) |
| G5-5 | NUMBER | headroom quoted at untested 45 dB | IMPRECISE | minor | resolved (≈ 0.23 % / 0.37 % at 48 dB) |
| G5-6 | NUMBER | §6 row SE 0.2 % superseded | IMPRECISE | minor | resolved (marked superseded) |
| G5-7 | DECISION | AX23 row omits E2 branch | INCONSISTENT | minor | resolved |
| G5-8 | NUMBER | EDT effect in dB | IMPRECISE | minor | resolved |
| G5-9 | NUMBER | BRAS T not labelled | NOT CHECKABLE | none | resolved (labelled, Brinkmann et al. 2019) |
| G5-11 | NUMBER | 1 kHz worst case at 40 % RH | WRONG | major | resolved (70 % RH, 2.5 %) |

Confirmed CORRECT by the final check: two-term model and its window; 0.42 %/1.2 %; 0.42/1.67 points; 0.6 %;
0.15 %; family false-failure rates; R formula; 10·log10(1 + (r_c/r)²) form; 62 dB flag; −0.18 dB fade;
nightly limits; Kuttruff citations; labels; consistency across scopes 3, 4, 6, 7, acceptance criteria and
BUILD_PLAN; no stale text.

**Open (for Maisara / the Expert):** AX23-10 (is a half-octave reading an acceptable basis for octave-band
T; the decided design reports both and gates on neither alone); the T jnd (5 % working value, practice-cited
only); the ISO 3382-2 curvature threshold and uncertainty constants and the Lundeby 1995 original (not
retrieved); the advocate, researcher and decider agents should be registered in a fresh session so they run
natively.

**Accepted by Maisara (2026-11-06):** all decider decisions of this run (D1–D7, N1, N2, E1–E3, G5-1, G5-4)
are accepted as applied; they are no longer proposals.

## Phase 05 session — Table 5.2 check and AX24/AX25 (2026-11-06) (interrogator; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

### Kuttruff Table 5.2 as the a* acceptance reference

The converged radiosity solver (`tools/acoustics/radiosity.py`; form-factor closure 1e-15, mean
free path = 4V/S within 0.2 %) and an independent Lambert Monte Carlo agree within ≈ 1–2 %; both sit
1.6–7.3 % below the Iteration column. For uniform α the solver equals Eq. 5.34 with Table 5.1's γ².

| id | kind | item | verdict | severity | status |
|---|---|---|---|---|---|
| T52-01 | NUMBER | a* within ±1 % of the Table 5.2 Iteration column (all 6 cases) | CONDITIONS VIOLATED (no stated method parameters, element count or accuracy for the column) | major | open (plan decision; test is a strict xfail) |
| T52-02 | NUMBER | 88 elements belong to the Fig. 5.10 Miles example, not to Table 5.2 | IMPRECISE | minor | open |
| T52-03 | NUMBER | 96 elements for the cube | NOT CHECKABLE | none | open |
| T52-04 | FACT | provenance, Δt, m = Int(R/cΔt) of the column | NOT CHECKABLE (R5.5 / R5.7 needed) | none | open |
| T52-05 | FACT | case geometry (Sabine and Eyring columns re-derived) | CORRECT | none | closed |
| T52-06 | FACT | ℓ̄ = 4V/S, T = 0.161 V/(S a*) | CORRECT | none | closed |
| T52-07 | FACT | Eq. 5.49 ρ(r) vs ρ_l in Eq. 5.51 | INCONSISTENT (as printed; harmless for the eigenvalue) | minor | closed |
| T52-08 | FACT | solver path statistics (ℓ̄ ±0.2 %, γ² 0.349 / 0.385) | CORRECT | none | closed |
| T52-09 | NUMBER | Eq. 5.34: case 1 1.519 s, case 3 1.467 s | CORRECT | none | closed |
| T52-10 | FACT | Iteration cases 1, 3 imply γ² ≈ 0.55 / 0.58, outside Table 5.1 | CONDITIONS VIOLATED (Eq. 5.34 is second order, independent paths) | major | open |
| T52-11 | NUMBER | Fig. 5.10 slope −1.57 dB/MFP → 1.215 s (consistency, not independent proof) | IMPRECISE | minor | open |
| T52-12 | NUMBER | case 4 a* 0.3905 (MC) vs 0.3893 (solver) | INCONSISTENT (0.35 %, two different runs) | minor | closed |
| T52-13 | FACT | qualitative signs (case 4 < Eyring, case 6 > Eyring, case 5 close) | CORRECT | none | closed |
| T52-14 | FACT | "least deviation in case 1" vs the table | INCONSISTENT (corpus-internal) | minor | closed |
| T52-15 | FACT | §9.8 ray tracing as numeric reference | NOT CHECKABLE (no numbers) | none | open |
| T52-16 | FACT | offset pattern explained by early stopping | NOT CHECKABLE | none | open |

### AX24 (positions in the shoebox) and AX25 (third octaves → octaves)

| id | kind | item | verdict | severity | status |
|---|---|---|---|---|---|
| AX25-1 | NUMBER | the three third octaves tile the octave (Vorländer Eq. 1.39) | CORRECT | none | closed |
| AX25-2 | FACT | arithmetic mean of α is consistent with A = ΣSα (Eq. 4.30) | CORRECT | none | closed |
| AX25-3 | FACT | equal weights match the octave's initial slope only for equal energy per third (Kuttruff Eq. 3.68) | IMPRECISE | minor | open (reported) |
| AX25-4 | FACT | mean of α, not of ln(1−α) (Millington–Sette, Kuttruff §5.4) | CORRECT | none | closed |
| AX25-5 | FACT | plain mean of s contradicts rule 4's (1−α) weighting | INCONSISTENT | major | resolved (s weighted by (1−α) across the thirds) |
| AX25-6 | FACT | how octave tables are formed from thirds | NOT CHECKABLE | none | open |
| AX24-1 | FACT | r enters C80 through the direct sound (Vorländer Eq. 6.20) | CORRECT | none | closed |
| AX24-2 | FACT | heights fix floor/ceiling reflection delays (Eqs. 11.33–11.34) | CORRECT | none | closed |
| AX24-3 | FACT | vertical height vs normal distance on a sloped face | IMPRECISE | minor | open (reported in bras_mapping.md §4) |
| AX24-4 | FACT | heights to two different local faces describe no real reflection | CONDITIONS VIOLATED | major | resolved (one floor plane per pair, under its midpoint) |
| AX24-5 | NUMBER | √(r² − Δh²) undefined when \|Δh\| > r | CONDITIONS VIOLATED | major | resolved (Δh = Δz; real horizontal separation kept) |
| AX24-6 | DECISION | proportional mapping keeps wall distances only where extents match | CONSEQUENCE | minor | open (reported) |
| AX24-7 | DECISION | mean-floor fallback | CONSEQUENCE | minor | open (reported) |
| AX24-8 | NUMBER | 0.1 m clearance is near grazing | NOT CHECKABLE | minor | open (reported) |
| AX24-9 | DECISION | specular box floor has no seat dip (Kuttruff §6.7) | CONSEQUENCE | minor | open (reported) |

## docs/phases/phase-05.md, phase-05e.md, BUILD_PLAN — decisions D-A, D-B, D-C (2026-11-06) (/fix-plan; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d; external sources: researcher report, this session)

Maisara asked: "decide D-A (shoebox dimension rule), D-B (Table 5.2 test) and D-C (noise test)". Loop: the
interrogator rated the options, the researcher looked for external evidence, the decider decided (proposals,
vetoable by Maisara), the plan-editor applied them, and the interrogator checked the diff (two rounds).
Main-session measurements were scratch prototypes (not committed). Results: D-A → **AX26**, D-B → a*
gated against an independent Lambert-particle Monte Carlo, D-C → **AX27** with L_min = 51 dB.

### Option verdicts (interrogator, round 1)

| id | kind | item | verdict | severity | status |
|---|---|---|---|---|---|
| DA-1 | NUMBER | A3 "x/y wall areas equal the assigned areas" (a·b would be 76.8 ≠ 50.48 m²) | IMPRECISE | minor | closed (A3 not chosen) |
| DA-2 | FACT | A1 (S kept) gives CR2 aspect 3.84 against a real 1.39; CR3 invalid | CONDITIONS VIOLATED | major | closed (A2 chosen, AX26) |
| DA-3 | DECISION | A2: V, h = V/A_floor, A_floor, plan ratio from the oriented bounding rectangle; S reported | CORRECT (preferred) | none | closed (AX26) |
| DB-1 | NUMBER | Fig. 5.10 (−1.57 dB/MFP) gives 1.215 s for case 4, agreeing with the column (1.21), ≈ 7 % above the solver and both Monte Carlos | CONDITIONS VIOLATED (for treating the MC as resolving the column) | major | open (reported "unresolved"; B12 (v) blocks a* replacing Eyring while open) |
| DB-2 | NUMBER | B2 (Table 5.2 at ±8 %): plain Eyring would pass cases 1 and 5 | CONDITIONS VIOLATED | major | closed (not chosen) |
| DC-1 | NUMBER | C3 margin at 55 dB without subtraction (+0.5 % predicted) | CONDITIONS VIOLATED | major | closed (AX27; fallback margin 60 dB) |
| DC-2 | FACT | C2 noise subtraction follows from the linearity of Kuttruff Eq. 8.29; not a corpus-named method | NOT CHECKABLE (derivable) | none | closed (AX27) |

### Diff check (interrogator, round 1 → fixes applied in round 2)

| id | kind | item | verdict | severity | status |
|---|---|---|---|---|---|
| PC-1 | FACT | EDC/τ = e^(−x) + N(x_c − x); symbol order vs Kuttruff | CORRECT (form), symbols swapped | minor | resolved (wording) |
| PC-2 | NUMBER | uncorrected bias +1.78/+0.55/+0.22/+0.08 % | IMPRECISE (≈ 1.7/0.5/0.2/0.07 %, fit convention stated) | minor | resolved |
| PC-3 | FACT | subtraction + compensation, no double counting | CORRECT if N̂, t_c, late line come from the unsubtracted envelope | minor | resolved (condition added) |
| PC-4 | DECISION | "EDC ≤ 0 above −35 dB → None" | CONSEQUENCE (needs precise definition) | minor | resolved (wording) |
| PC-5 | NUMBER | residual bias | IMPRECISE (εN(x_c − x); ≈ ε × uncorrected) | minor | resolved |
| PC-6 | NUMBER | 45 dB T30 requirement, ISO 3382-1:2009 §4.2.1 | NOT CHECKABLE (corpus; researcher read it externally) | none | open (external) |
| PC-7 | NUMBER | L_min = 52 dB vs "lowest in 1 dB steps" (51 not measured) | INCONSISTENT | major | resolved: 51 dB measured, worst median − 3·SD 45.7 dB → L_min = 51 dB |
| PC-8 | NUMBER | admission margin vs the test's nominal level | IMPRECISE (different quantity) | minor | resolved (estimator defined; reads ≈ 1.4 dB low, conservative) |
| PC-9 | FACT | Begault: ideally 60 dB above the noise floor | CORRECT (stated for whole-decay capture) | none | closed |
| AD-1 | NUMBER | AX26 formulas and CR2/CR3 boxes | CORRECT | none | closed |
| AD-2 | FACT | "Eqs. 5.8, 4.8, 4.6" | IMPRECISE (Eq. 4.6 depends on V only; per-axis rate Eqs. 4.8–4.9) | minor | resolved |
| AD-3 | FACT | S enters at second order (Eq. 5.35) | CORRECT | none | closed |
| AD-4 | FACT | §7.5.2 for "early reflections depend on geometry" | IMPRECISE (§7.5.2 defines C only) | minor | resolved |
| DB-3 | NUMBER | Fig. 5.10 → 1.215 s; ≈ 7 % gap | CORRECT | none | closed |
| DB-4 | NUMBER | SE ≤ 0.25 % (tol/4); < 0.4 % per halving | CORRECT | none | closed |
| DB-5 | FACT | γ²-Eyring as a ±1 % gate for cases 1, 3 (Eq. 5.30 needs ½σ_N²a² ≪ 1; 0.26–0.51 at −35 dB) | CONDITIONS VIOLATED | major | resolved: all six cases gated against the particle MC (cases 1, 3: particle 1.526 / 1.473 s, solver 1.525 / 1.472 s); γ²-Eyring reported only |
| DB-6 | NUMBER | "fixed 2.5 m layout" for the 1:2:3 room | IMPRECISE (88 elements are 5 m) | minor | resolved (numbers restated per layout) |
| DB-7 | NUMBER | Table 5.2 values | CORRECT | none | closed |
| DB-8 | DECISION | B12 (v): Eyring stays e.g. for case 4 (14 % above Iteration) | CONSEQUENCE | minor | recorded in B12 |

### Main-session measurements (prototype, scratch; seeds and R as `test_noise_handling.py`)

- AX27 prototype, paired bias with subtraction: ≤ +0.24 % at 48 dB, ≤ +0.17 % at 50, ≤ +0.14 % at 51, ≤ +0.14 % at 52,
  ≤ +0.08 % at 55 dB; unsuitable realisations 5/1/1 at 48 dB (Lundeby range estimate below 45 dB), 0 at ≥ 50 dB.
  Worst median − 3·SD of the Lundeby dynamic-range estimate: 42.8 (48), 44.7 (50), 45.7 (51), 46.8 (52) dB.
- a*: from-scratch Lambert particle simulation (survivor fraction / energy decay, 200k–400k particles): cases 1–6 =
  1.526, 1.350, 1.473, 1.133, 2.981, 5.860 s (table 1.55, 1.35, 1.52, 1.21, 3.06, 5.93). Solver convergence: case 2
  1.3315 / 1.3378 / 1.3393 s (2.5 / 1.25 / 0.625 m), case 6 5.667 / 5.763 / 5.787 s (5 / 2.5 / 1.25 m). Risk recorded
  in phase-05e: the ±1 % gate may be borderline on case 6.

### Decisions

| decision | rule | basis | status |
|---|---|---|---|
| D-A | AX26 (A2) | interrogator DA-3; Brinkmann et al. 2019 §II.D (RAZR: V + main-dimension proportions; external) | applied; vetoable by Maisara |
| D-B | a* converged, ±1 % vs independent Lambert-particle MC, all six cases; Table 5.2, Fig. 5.10, 88/96-element and γ²-Eyring results reported; B12 (v). Changes Maisara's 2026-11-05 choice to gate at 88/96 elements | DB-1, DB-2, DB-5 | applied; vetoable by Maisara |
| D-C | AX27 noise subtraction; case A levels L_min = 51, 55, 65 dB (48 reported); admission margin ≥ L_min; reversal: margin ≥ 60 dB without AX27 | DC-1, DC-2, PC-1…PC-8 | applied; vetoable by Maisara |

### Diff check, round 2 (interrogator; final)

Every round-1 item resolved (PC-1…PC-8, AD-2, AD-4, DB-5, DB-6, DB-8; PC-6 stays open, external). R2-1 (−3.29 % at
88 elements; converged −0.79 % case 2, −1.25 % case 6; halvings 0.47/0.11 % and 1.69/0.42 %; γ² 0.376): CORRECT.
R2-2 ("≈ 1 % below" → "≈ 1.2 %, still converging") and R2-3 (AX23 / scope 7 "as predicted" / "matching" → "close to":
the measured +1.8…+2.1 % at 48 dB exceeds the ≈ +1.7 % prediction by more than the condition SEs of 0.05–0.14 %):
IMPRECISE, minor, resolved (wording). Case 5 converged: solver 2.978 s at 2.5 m vs particle 2.981 s (−0.1 %), so only
case 6 is borderline. No round 3 needed. Status: D-A, D-B, D-C applied; vetoable by Maisara.

### Follow-up: CR2/CR3 documented-vs-model volume check added to phase-05e scope (a) (2026-11-06, at Maisara's request)

No rule, threshold or assumption changed; one science statement, checked by the main session: with A fixed, Sabine
T = 0.161 V/A (Kuttruff Eq. 5.8, and Eyring likewise) scales with V, so 146.1 vs 145 m³ gives +1.1/145 = +0.76 % in
predicted T for every CR2 pair. CORRECT. Status: applied; 05e establishes the cause before any comparison.

## Phase 05e session 1 — AX27 L_min re-measurement and noise-margin estimator (2026-11-06; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Main session measured AX27's L_min as the rule requires (`tools/acoustics/meter_checks.py` `find_l_min`, R = 51 per
condition, seeds fixed per condition by `condition_seed`; record `tools/acoustics/data/phase05_meter_checks.json`).
The noise margin AX27 defines, 10·log10(P_line(t₀)/N̂) (`line_margin_db`), gives worst median − 3·SD (500 Hz, T = 1 s)
41.9 / 42.6 / 44.6 / 44.3 / 44.5 / 44.7 / 46.8 dB at 51…57 dB, so **L_min = 57 dB** by the rule. The plan's prototype
numbers (42.8 / 44.7 / 45.7 / 46.8 dB at 48 / 50 / 51 / 52 dB) and its "≈ 1.4 dB below nominal" are reproduced exactly
by the peak-referred dynamic range (`dynamic_range_db`), not by the defined estimator (which reads 1.2–2.8 dB below
nominal, SD 2–3 dB at 500 Hz / 1 s against ≈ 1.1 dB). Paired T30 bias with AX27: |mean| ≤ 0.13 %, SE ≤ 0.042 % in all
18 gated conditions (57, 55, 65 dB); 51 dB +0.06…+0.15 %, 0 unsuitable; 48 dB up to +0.26 %, 7/51 unsuitable at
500 Hz / 1 s.

| id | kind | item | verdict | evidence | severity | status |
|---|---|---|---|---|---|---|
| E5-1 | NUMBER | L_min = 51 dB "of the Lundeby dynamic-range estimate (the noise margin below)" = P_line(t₀)/N̂ | INCONSISTENT | the "≈ 1.4 dB" claim and the prototype values match `dynamic_range_db` (51 − 49.56 = 1.44 dB), not the defined estimator (51 − 48.18 = 2.82 dB); with the defined estimator the rule gives 56–57 dB depending on the seed scheme | major (test gate and BRAS admission) | resolved by option C with corrections (decider 2026-11-06, interrogator diff check); applied: L_min = 51 dB on dynamic_range_db; admission on line_margin_db ≥ 51 dB; option A, 57 dB, rejected |
| E5-2 | NUMBER | 45 dB margin requirement | NOT CHECKABLE | Kuttruff §8.4, Vorländer §6.4.1 give the −5…−35 dB range re the initial level; no corpus noise-margin rule (ISO 3382-1 would settle it) | none | open |
| E5-3 | FACT | margin referred to the decay, not the envelope peak | NOT CHECKABLE (leans to the defined estimator) | Kuttruff §8.4 (Eq. 8.29 context): noise bends the lower end of the backward-integrated curve; the reference is the decay's initial level; in a measured IR the envelope peak includes the direct sound (interrogator's inference) | none | open |
| E5-4 | NUMBER | median − 3·SD over R = 51 in 1 dB steps | NOT CHECKABLE | non-corpus arithmetic: SE(3·SD) ≈ 0.6 dB, SE(median) ≈ 0.35 dB at SD 2 dB: the ±1 dB seed sensitivity observed | none | open |
| E5-5 | FACT | Begault's 60 dB | CONSEQUENCE | Begault Ch. 4: 60 dB "to capture the whole decay" is an auralization condition, not a T30 condition | minor | open |
| E5-6 | FACT | "noise term of Kuttruff Eq. 8.29" | WRONG | Kuttruff §8.4: Eq. 8.29 ⟨h²(t)⟩ = ∫ₜ^∞ g² dx has no noise term; noise appears only in the prose and Fig. 8.13 | minor (attribution) | resolved by correction 2 (and E5-D14 in AX23) |
| E5-7 | FACT | noisy arm "= measured-IR path" | INCONSISTENT | the arm skips D7(2), which would fail in ≈ 5.5 % of realisations at 51 dB; no effect on admission | minor | resolved by correction 3 (main-session product choice; vetoable by Maisara) |

Consequence on BRAS (measured `line_margin_db`, AQ9 bands): CR2 500 Hz 51.8–61.2 dB, CR4 500 Hz 55.7–59.6 dB, CR4
2 kHz 56.7–62.1 dB, CR3 ≥ 65.5 dB. At 57 dB a large share of CR2/CR4 AQ9 bands leaves the gated mean; at 51 dB nearly
all enter. Status: L_min = 51 dB (option C, decider 2026-11-06 with interrogator diff check; vetoable by Maisara); 57 dB
is the result of the rejected option A (non-monotone, SD 2.2–3.0 dB, ±1 dB seed-sensitive, E5-4, no measured bias
benefit).

### Decision: option C (decider, 2026-11-06; /fix-plan, corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Decider (medium confidence): L_min = 51 dB with one estimator per job. The test-level rule (median − 3·SD ≥ 45 dB, 1 dB
steps) is read on the peak-referred `dynamic_range_db` (D7(1) quantity; worst 45.75 dB at 500 Hz / 1 s at 51 dB,
44.74 dB at 50 dB). Measured bands are admitted to the gated AQ9 mean and B12 only at a decay-referred
`line_margin_db` ≥ 51 dB (it reads below nominal: median 48.18 dB, SD 1.99 dB at nominal 51 dB; below the peak-referred
value on BRAS, e.g. CR2 500 Hz 51.8 vs 59.9 dB). Option A (57 dB on the line margin) rejected: non-monotone, seed-
sensitive (E5-4), no measured bias benefit (bias with AX27 0.26 % at 48, ≤ 0.15 % at 51, ≤ 0.13 % at 57 dB).
Reversal: a case A condition at 51 dB fails the 0.6 % gate in the 05e CI run; a nominal-48 dB band reads line ≥ 51 dB
in > 1 % of realisations (normal approx. 0.44 %: z = (51 − 46.21)/1.83 = 2.62, outside the corpus); or ISO 3382-1
requires a decay-referred 45 dB margin → test-level rule on the line margin (57 dB).

Interrogator diff check of the proposal: adoptable with three corrections (E5-6 Eq. 8.29 has no noise term; drop "both
refer to the same decay", state the measured offset; E5-7 noisy arm "= measured-IR path except the D7(2) test, which
cannot fire for a band admitted at line_margin_db ≥ L_min" — the alternative, applying D7(2), would move the
suitability gate towards 57 dB; main-session product choice, vetoable by Maisara).

### Diff check of the applied text (interrogator; two rounds)

Round 1 (E5-D1…D15): D1–D8, D10, D13, D15 CORRECT; D9 IMPRECISE (Fig. 8.13 illustrates, the reference level follows
from the Eq. 8.29 derivation); D11 NOT CHECKABLE (the 0.44 % inputs were not stated); D12 INCONSISTENT ("any
condition" vs "every case A condition"); D14 IMPRECISE (AX23 row repeated the E5-6 attribution). Round 2 after the
fixes: D9, D10, D11, D12, D14 CORRECT (0.44 %: z = 4.79/1.83 = 2.62; L_min: 48.56 − 3.81 = 44.75 < 45, 49.56 − 3.81 =
45.75 ≥ 45). One labelling note, not an error: "≤ 0.15 %" (05e session 1) vs "≤ +0.14 %" (prototype) at 51 dB come
from different runs. Status: applied (BUILD_PLAN AX23, AX27, §6 row; phase-05.md scope 7 and criterion; phase-05e.md
item 6 and criterion); vetoable by Maisara.

## phase-05e.md, BUILD_PLAN §6, bras_mapping.md §1 — CR4 handling (decider, 2026-11-06, at Maisara's request; /fix-plan; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Facts: CR4 extraction unfinished in Phase 05 (> 40 min) and in 05e session 1 (a detached run died after ≥ 41 min with
an empty log, most likely at container reclamation); CR4.skp 17.1 MB vs CR3.skp 12.7 MB (CR3 parsed in ≈ 25 s), so a
reader pathology is suspected (re-synchronisation fallback scanning to the end of file), not measured.

Decision (decider, option D; vetoable by Maisara): CR4 stays selected; exclusion criteria pre-committed in
bras_mapping.md §1 before any simulated-vs-measured number; ≤ 1 h profile, then a generic reader fix allowed under the
CR2/CR3 regression guard (test_skp_reader.py, area reproduction, make_bras_scenes.py --check); foreground extraction
with progress output; main track on CR2 + CR3 labelled 'provisional, two-room (CR2, CR3; uniform α: CR2, uneven α: CR3
only); CR4 pending'; the B12 replacement and B11 promotion decisions deferred (pass rules unchanged); stop rule at the
end of 05e session 2 → 05e `done` with 'CR4 pending extraction (reader), not dropped' and phase-05f. No acoustic claim.

Interrogator diff check, round 1: C1 (Maisara's two-room acceptance would drop CR4 after results are seen) INCONSISTENT,
major; C2 (holding B11 promotion vs phase-05.md B11 (B) "no minimum count applies") INCONSISTENT, major; C3 (one room per
α group) IMPRECISE; C4 (acceptance test is also face planarity) IMPRECISE; C5 (status at the stop rule unstated)
INCONSISTENT, minor. Fixes: C1 the acceptance keeps CR4 selected and goes through /fix-plan as a phase-05.md change; C2
deferral of the decision time, pass rules unchanged; C3 full label; C4 "the bras_mapping.md §2 acceptance test"; C5
status `done` with the note. Round 2: C1, C2, C4, C5 resolved; C3 label and the reversal's acceptance wording completed
by the main session. Status: applied; vetoable by Maisara.

## phase-05f.md (new), phase-05e.md, phase-05b.md, phase-13.md, BUILD_PLAN §0/§4/§6, bras_mapping.md §1 — phase-05f for CR4 (Maisara, 2026-11-06; /fix-plan; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Maisara: "Go for setting 5f dedicated for whatever CR4 needs". Phase-05f created: decode the CFaceTextureCoords layout
variant(s) in skp_reader.py (generic, regression guard), extract and accept CR4 only by the bras_mapping §2 test, then
the three-room report, baseline extension and the deferred B12/B11 decisions; two-session stop rule →
`blocked (reader: CR4 not extracted)`, CR4 pending, not dropped. 05e completes on CR2 + CR3 (provisional two-room).
Following from the CR4-handling deferral (above): 05b and 13 wait for 05f `done` or Maisara's recorded two-room
acceptance. Facts (05e session 1, measured): reader fixes; CR4 parses in ≈ 1 min, ≈ 1 083 of 5 851 m²; 1 547 of 1 767
CFaceTextureCoords records fit 214 bytes, 220 do not; parse stops at 16.46 of 17.08 MB; the dict copy was 59 % (209 of
353 s) of the profiled run.

Interrogator diff check: no acoustic claim; C4, C5 (no room dropped, selection before comparison, B11 (B), B12, one
CR4 owner, gating, stop rules) consistent; P1 phase-05f.md structure complies with CLAUDE.md; minor items fixed by the
main session: F1 "≈ 220" → 220; F4 59 % referred to the profiled run; C1 05e scope (a) and BUILD_PLAN §4 "all selected
rooms except CR4 (05f)"; C2 §6 row marks that it supersedes the 05e session-2 stop rule; C3 05f criterion for the
CR4 bias-hook test. Status: applied; vetoable by Maisara.

## Phase 05f session 1 — AX30 planarity tolerance of the BRAS acceptance test (2026-11-07; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Main session proposal: |n·p + d| ≤ 2.54e-5 m (SketchUp's 0.001 in) for every loop vertex. CR2 7.2e-16 m, CR3 3.2e-12 m,
CR4 max 1.98e-5 m (374 of 1 844 faces > 1e-9 m); CR4's 8 material areas within 0.005 m², enclosed volume 8 656.51 vs
8 656.5 m³, zero re-synchronisations in the room geometry.

| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| F5f-1 | NUMBER | AX30: BRAS SketchUp planarity limit, absolute, for every loop vertex; ≤ 25 µm off-plane is acoustically immaterial | CORRECT (acoustic immateriality); 0.001 in as a SketchUp tolerance NOT CHECKABLE (file-format spec); the limit's value is a product matter | Vorländer §3.3.2, Fig. 3.8 (smooth if h, a ≪ λ/2) and §11.1.1 (0.5 m model resolution; off-plane uncertainty of 4th+ vertices admissible if adjusted onto the plane); Kuttruff Ch. 9 after Eq. 9.9 (irregularities ≪ λ negligible). c = 343 m/s (Kuttruff Eq. 1.1): λ(8 kHz) = 42.9 mm, δ/λ ≈ 6e-4; path change ≤ 2δ ≈ 148 ns; normal tilt ≤ 2.5e-5 rad. Absolute preferred (corpus criteria are absolute lengths vs λ); nothing argues tighter. | none | value → decider | confirmed |
| F5f-1d | DECISION | AX30 value | decider 2026-11-07: **1.0e-3 m absolute** instead of 2.54e-5 m | 1 mm ≈ 15 × below λ/2 at 11.3 kHz (Vorländer §3.3.2) and ≈ 1/1 870 of the pre-fix misparse (1.87 m); 2.54e-5 m is unverifiable and was proposed after CR4's 1.98e-5 m was seen (looks fitted). Sub-mm reader errors covered by the area check and the CR2/CR3 guard. | none | none | applied; accepted by Maisara 2026-11-07 ("I accept all with no vetos") |

## BUILD_PLAN §5 B12, phase-05.md scope 6 — Phase 05f B12 outcome and the γ²-Eyring wording (2026-11-07; /fix-plan; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Asked by Maisara ("Why haven't you delegated the decider on the 4 points?!"). Decider D1 (B12 outcome under C2) and D2
(scope 6 wording) → interrogator round 1 (both SURVIVE WITH CORRECTIONS) → advocate round 1 (D1 REDIRECT: the reversal's
"Eyring within ±5 %" clause was circular in Eyring's favour, and condition (ii) was not shown at the admissible γ²; D2 PASS)
→ decider round 2 (input-side reversal criterion; γ² sweep from the main session: 0.342 → −1.56, 0.4 → −1.83, 0.613 → −2.87
pts; 0.4 the only admissible value) → interrogator round 2 (D1 SURVIVES WITH CORRECTIONS: the user-audible-fact sentence
restated, §5.7 limited to floor/audience absorption in auditoria, Eq. 5.30 "most of the T30 range"; D2 SURVIVES) → advocate
round 2 (PASS, PASS) → plan-editor applied → interrogator check of the finished diff (below).

| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| F5f-2 | FACT | for γ² > 0, a'' = a(1−γ²a/2) < a, so γ²-Eyring T ≥ Eyring T | CORRECT | Kuttruff §5.5 Eqs. 5.33–5.34 | none | – | closed |
| F5f-3 | NUMBER | Table 5.2 case 4: 1.473 s (γ² 0.4) vs Eyring 1.379 s (+14.0 %), Iteration 1.21 s; worse by 7.75 pts | CORRECT | Kuttruff Table 5.2, Eqs. 5.33–5.34; also vs Fig. 5.10 1.215 s | none | – | closed |
| F5f-4 | NUMBER | case 2 and six-case means (Eyring 10.29 %, γ²-Eyring 10.13–10.18 %) | CORRECT | Kuttruff Tables 5.1, 5.2 | none | – | closed |
| F5f-5 | NUMBER | γ² = 0.376 for 1:2:3 | IMPRECISE → applied: only 0.4 cited | interpolation, not a Table 5.1 row | minor | – | closed |
| F5f-6 | NUMBER/FACT | Sabine control (BRAS −4.5 pts; Table 5.2 Sabine 14.3 % vs Eyring 10.3 %) | CORRECT; gloss restated (8 of 9 room-bands under-predicted) | report §2; Kuttruff Table 5.2, §9.4 | minor | – | closed |
| F5f-7 | NUMBER | BRAS γ²-Eyring 19.5 → 17.7 %, −1.83 pts, worst room −1.22 | CORRECT | report §3 | none | – | closed |
| F5f-8 | NUMBER | Table 5.1 rows 1:5:5 0.464, 1:10:10 0.613, 1:5:10 0.510 | CORRECT | Kuttruff Table 5.1 | none | – | closed |
| F5f-9 | NUMBER | CR4 ≈ 1:8.5:8.5, CR3 ≈ 1:4.5:8.7 | CORRECT (ratios); 0.57 interpolation NOT CHECKABLE | box dims | none | – | closed |
| F5f-10 | FACT | γ² ≈ 0.4 near-cubic; Eq. 5.34 inaccurate at higher γ²; Eq. 5.30 condition | CORRECT | Kuttruff §5.5, Eqs. 5.30–5.31 | none | – | closed |
| F5f-11 | DECISION | "not adopted" | applied as a recommendation under C2; Maisara decides | phase-05 scope 6 | minor | – | closed |
| F5f-12 | FACT | reversal ordering T_Eyring < T_γ² < T_Sabine | CORRECT; ±5 % clause later dropped (advocate) | Kuttruff Eq. 5.35 | none | – | closed |
| F5f-13 | FACT | "diffuse-field T" | IMPRECISE → applied: "T for diffusely reflecting walls (the §5.7 iteration)" | Kuttruff §5.7 | minor | – | closed |
| F5f-14 | FACT/NUMBER | D2: T longer for every γ² > 0; case 4 ≈ 1.47 / 1.38 / 1.21 s | CORRECT | Kuttruff §5.5, Table 5.2 | none | – | closed |
| F5f-15 | DECISION | D2 makes γ²-Eyring a B12 candidate; BRAS-only pass input-limited | CONSEQUENCE | Kuttruff §9.4 | minor | – | closed |
| F5f-16 | NUMBER | γ² sweep 1.56 / 1.83 / 2.87 pts; 0.4 only admissible | NOT CHECKABLE (tool output); consistent | radiosity.gamma2_eyring_t60; report §3 | none | – | closed |
| F5f-17 | NUMBER | Eq. 5.30 term ≈ 0.55 at −35 dB (case 4) | CORRECT | Kuttruff Eqs. 5.30–5.32 | none | – | closed |
| F5f-18 | FACT | "not met over the T30 range" | IMPRECISE → applied: "most of the T30 range (≈ 0.08 at −5 dB to ≈ 0.55 at −35 dB)" | Kuttruff Eqs. 5.30–5.32 | minor | – | closed |
| F5f-19 | FACT | §5.7 uneven absorption; "fixes neither" | IMPRECISE → applied: floor/audience absorption in auditoria; case 6 ≈ −21 % | Kuttruff §5.7, Table 5.2 | minor | – | closed |
| F5f-20 | NUMBER | room means 16.1 / 21.0 / 22.1 % ≈ 3.2–4.4 working jnd | CORRECT | report §1, §2 | none | – | closed |
| F5f-21 | FACT | "16–22 % short" | WRONG → applied: room-mean \|error\|; CR2/CR4 short in every band, CR3 mixed | report §2 | major | – | closed |
| F5f-22 | FACT | "whatever the predictor" | WRONG → applied: no predictor within 10 %; predictor moves error ≤ ≈ 8 pts | report §2–§3 | major | – | closed |
| F5f-23 | FACT | remaining B12-text numbers | CORRECT | report §3; Kuttruff | none | – | closed |
| F5f-24 | DECISION | reversal input criterion (≥ 10 % of A, α measured independently; product threshold) | CONSEQUENCE (coherent) | Kuttruff §9.4, §8.7 | none | – | closed |
| F5f-25 | FACT | largest-face room clause | CORRECT (coherent) | Kuttruff Table 5.2 case 4, §5.7 | none | – | closed |
| F5f-26 | FACT | D2 final wording | CORRECT | Kuttruff §5.5, §5.7 | none | – | closed |
| F5f-27 | DECISION | D1 (recommendation: γ²-Eyring not adopted; Eyring stays; AQ2 unchanged) and D2 | decider; interrogator SURVIVES (with corrections applied); advocate PASS ×2 | this section | – | Maisara decides (C2) | applied; accepted by Maisara 2026-11-07 ("I accept all with no vetos") |

Finished diff (interrogator, step 5): **CLEAN** — every changed passage matches F5f-2 … F5f-26. Noted for a later check, not
part of this diff: phase-05 scope 6's unchanged "with low s the true T can fall on the other side of Eyring (Kuttruff §9.4)";
the §9.4 passages read in round 1 do not contain the low-s statement.

## BUILD_PLAN §2 AQ4 / AX31 / §6, phase-06.md AC 3, phase-07.md scope 3, phase-13.md scope 1 / item 8 — Phase 06 follow-ups (2026-11-07; /fix-plan; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Asked by Maisara ("Take care of all the follow-ups"; on non-uniform partitioning: "Spread only, plan later
(Recommended)"). Decider D1 (pickup timing under work spreading: option A, s0 = (⌊r/P⌋ + 2)·P) → interrogator
round 1, decision mode (SURVIVES WITH CORRECTIONS: AQ4's interval statement imprecise, restatement proposed;
L3 NOT CHECKABLE, product judgement) → advocate (PASS; bound to be stated as rebuild + 2P, not one runner's
number) → decider round 2 (L3 replaced by L3a/L3b: Table 15.1 translational rows, 700 ms, apply; the
rotation rows don't in v1; the rebuild, not the A/B choice, sets the total delay; AQ4 restatement accepted
with the 20 ms build-slot wait; the cap's semantics left to a Phase 10 AX) → plan-editor (AX28 was taken:
the new row is AX31) → interrogator diff check (nothing WRONG; four IMPRECISE points, applied).

| id | type | claim | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| P06F-1 | DECISION | D1: option A (spread; +1 partition for an isolated update; pace and reported latency unchanged) | decider; interrogator SURVIVES WITH CORRECTIONS; advocate PASS | code (CrossfadingConvolver computeBlock), deterministic per-call test | – | vetoable by Maisara | applied (AX31) |
| P06F-2 | NUMBER | back-to-back period ⌈1440/P⌉·P = 1536 samples = 32 ms at P = 256 and 512 | CORRECT | arithmetic | none | – | closed |
| P06F-3 | FACT | AQ4 "interval = max(20, 30, rebuild)" | IMPRECISE → applied: each term rounded to whole partitions; isolated-update delay stated (slot wait + rebuild + 2P) | Vorländer Table 15.1 heading "time available for filter update" | minor | – | closed |
| P06F-4 | FACT | Table 15.1 rows applying to v1 | CORRECT: translational 700 ms / 3 s apply; source rotation (AQ8 omni) and head rotation don't | Vorländer §15 Table 15.1; PRD out of scope | none | Phase 08: HRTF set changes with the centroid yaw (AX3): does the head-rotation row (35 ms; filter content "new HRTF") apply then? (wording corrected, P06B-4) | open for Phase 08 (phase-08.md scope item 8) |
| P06F-5 | NUMBER | 28.5 + 2 × 10.67 = 49.8 ms (W2, Linux, P = 512, no slot wait) | IMPRECISE (49.9) → applied 49.8 | arithmetic | minor | – | closed |
| P06F-6 | FACT | "32 ms at P = 256 or 512" | IMPRECISE → applied: only while the rebuild ≤ 32 ms (Windows W2 41.6 ms → 42.7 ms) | §0 W2 times | minor | – | closed |
| P06F-7 | FACT | AQ4 rationale "within Table 15.1's 35 ms" | IMPRECISE → applied: reworded to the 700 ms translational row | Vorländer Table 15.1 | minor | – | closed |
| P06F-8 | FACT | AX31 "§15's 50 ms head-tracked total delay" | IMPRECISE → applied: "§15's 50 ms total delay for interactive virtual environments" | Vorländer §15 | minor | – | closed |
| P06F-9 | FACT | phase-06 AC 3 wording (ramp start = where the new IR enters the output) | CORRECT; same test | code, AX31 | none | – | closed |
| P06F-10 | FACT | phase-07 threading bullets; phase-13 scope 1 numbers, item 8 | SOFTWARE / NOT CHECKABLE (measurements, CI run 42355829013) | – | none | – | closed |
| P06F-11 | NUMBER | AQ4 "32 ms at P = 256 or 512" (found by the phase re-review) | IMPRECISE → applied: 32 ms at 48 kHz for P = 128/256/512; at 44.1 kHz ⌈1323/P⌉·P = 1536 samples = 34.8 ms (P = 256, 512), 1408 = 31.9 ms (P = 128) | arithmetic | minor | – | closed |
| P06F-12 | FACT | phase-13 scope item 9: CI timing figures (Linux 66.6 / 65.9 %, Windows 32.2 %, macOS wall 75.5 / 609 / 161.8 / 657.4 %, thread-CPU 109.9 %) | NOT CHECKABLE (measurements, run ids given) | CI runs 42390056623, 42392204088, 42394370942, 42397114233 | none | – | closed |
| P06F-13 | FACT | "most of the wall overshoot is the runner taking the thread off the CPU" | CORRECT as an inference (547.5 of 557.4 points above 100 % are not thread-CPU time; separate distributions; CPU p99.9 still misses) | run 42397114233 | none | – | closed |
| P06F-14 | FACT | item 9 remedy "a smaller first partition or non-uniform partitioning (scope 1)" | IMPRECISE → applied: "P = 256 (allowed under scope 1) or non-uniform partitioning (new AX entry, 13b, per scope 1)" | phase-13 scope 1, AX31 | minor | – | closed |

Finished diff: nothing WRONG; the four IMPRECISE points applied. Noted: Vorländer §15.3 prints 20 ms where
Table 15.1 gives 35 ms (corpus erratum; neither AQ4 nor AX31 relies on it).

## phase-06b.md (new), phase-07.md, phase-08.md, phase-10.md, BUILD_PLAN §0/§2 AX31/§6 — Phase 06b created (Maisara, 2026-11-07; /fix-plan; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Asked by Maisara ("Create a phase for the two pending decisions and what is left for later"). Brief
`docs/sessions/2026-11-07-phase-06b-plan.md` (steward BRIEF OK, round 2). Plan-editor wrote phase-06b.md and
the phase-07 gate / phase-08 / phase-10 items; no acoustic or numeric choice was made (open values are
marked "decided through /fix-plan in the 06b session"). Interrogator diff check: nothing WRONG; four
IMPRECISE points, applied. The P = 256 CPU figures were checked by the main session against the saved CI
logs of run 42397114233 (Linux 7.0 / 12.6 %, macOS 3.5 / 6.5 %, Windows 3.2 / 5.4 %: match).

| id | type | claim | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| P06B-1 | NUMBER | every number in phase-06b.md cited or marked for the 06b session | CORRECT (P = 256 CPU figures NOT CHECKABLE by the interrogator; matched the CI logs) | §0 row 06, re-review, PR #14, CMakePresets.json, CI run 42397114233 | none | – | closed |
| P06B-2 | FACT | "Assumptions in force" AQ4 summary (32 ms at 48 kHz) | IMPRECISE → applied: "while the rebuild is ≤ 32 ms" | BUILD_PLAN §2 AQ4 | minor | – | closed |
| P06B-3 | FACT | AX1 bullet cites the 32-sample value to AX1 | IMPRECISE → applied: value cited to AX31 and §0 row 06 | BUILD_PLAN §2 AX1, AX31 | minor | – | closed |
| P06B-4 | FACT | "Table 15.1 'new HRTF' row (35 ms)" | IMPRECISE → applied: "head-rotation row (35 ms; filter content 'new HRTF')" in phase-08, phase-06b, AX31; P06F-4 reworded | Vorländer §15 Table 15.1 | minor | – | closed |
| P06B-5 | FACT | "12 s IR, P = 256: over budget while crossfading" | IMPRECISE (overstated) → applied: over budget on Linux (103.2 %); Windows 64.2 %, macOS 48.9 % | PR #14 "For the Expert", run 42397114233 | minor | – | closed |
| P06B-6 | FACT | arithmetic 544 / 288 / 10.7 / 5.3 ms / 32 ms; AQ10, AX18, AX31 summaries; phase-07 gate; phase-10 item; §6 row | CORRECT | BUILD_PLAN §2, phase-06.md | none | – | closed |


## Phase 06b decisions D1–D4 (session 1, 2026-11-07; /fix-plan; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Maisara, 2026-11-07, asked to choose decisions 1 and 2 herself: "I have created an entire workflow described in
claude.md so you don't ask me these" / "Same answer". The decision loop therefore decided all four; each is a
proposal she can veto. Brief `docs/sessions/2026-11-07-phase-06b.md`. Full rows and reasoning:
`docs/review/phase-06b/` — `decisions-request.md`, `measurements.md` (M1–M3), `interrogator-option-check.md`
(P06B-7…30), `researcher-dossier.md` (F1–F20; D1, D3 NOT READY, gaps not fillable: no retrievable monitoring
threshold, largest host level or clamp/zero convention), `decider-round1.md`, `interrogator-round1.md`
(P06B-31…60), `advocate-round1.md`, `decider-round2.md`, `interrogator-round2.md` (P06B-61…73),
`advocate-round2.md`.

| id | type | claim | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| P06B-7…30 | OPTIONS | option check of D1–D4 | D1, D2 product matters; D3 product matter inside the window +40 dB … 1.83e33 (+24 dBFS CONDITIONS VIOLATED; −120 dB null invalid under clamping, P06B-24); D4 family (b) verified, (a) alone CONDITIONS VIOLATED, no FMA margin (P06B-29); M1 duration evidence WRONG (P06B-16) → re-measured (189 440 samples per channel = IR + run) | interrogator-option-check.md | major (P06B-16, 22, 24, 26, 29) | – | closed (applied) |
| P06B-31…60 | DECISION | decider round 1 (D1 (a), D2 confirm, D3 AX32 B = 2²⁰ zero, D4 50 ulp) | all four SURVIVE WITH CORRECTIONS; majors: P06B-39 (phase-13 item 9 remedy P = 256 inconsistent), P06B-47 (AX32 formula counted N twice), P06B-55 (window) | interrogator-round1.md | major ×3 | advocate: D1 REDIRECT (Linux-only evidence, NFR-4); D2 wording; D3, D4 PASS | closed (round 2) |
| P06B-61…73 | DECISION | decider round 2 final texts | nothing falls; minor wording P06B-62, 63, 68, 69, 71 applied with the texts; P06B-66 carried to phase-08 item 8 | interrogator-round2.md | minor | advocate round 2: all four PASS | closed |
| P06B-D1 | DECISION | AQ10: keep P = 512; reported latency P + 32 = 544 samples (11.3 ms); phase-13 item 9 remedy restated (not P = 256) | SURVIVES WITH CORRECTIONS (applied); advocate PASS | decider-round2.md D1 | – | vetoable by Maisara (veto → P = 256, see D1 "If Maisara vetoes") | accepted (Maisara 2026-11-08, no vetoes) |
| P06B-D2 | DECISION | AX31 confirmed (note appended) | SURVIVES; advocate PASS | decider-round2.md D2 | – | vetoable by Maisara | accepted (Maisara 2026-11-08, no vetoes) |
| P06B-D3 | DECISION | AX32: |x| > 2²⁰, ±Inf, NaN → 0 before the forward FFT; test (a)–(d) | SURVIVES WITH CORRECTIONS (applied); advocate PASS | decider-round2.md D3 | – | vetoable by Maisara | accepted (Maisara 2026-11-08, no vetoes) |
| P06B-D4 | DECISION | summation-order test: T = 400 exact case, max error ≤ 50 ulp (midpoint of 0 and 100) at P = 128/256/512 | SURVIVES WITH CORRECTIONS (applied); advocate PASS | decider-round2.md D4; measured SSE: 0 ulp (descending), 100 ulp (ascending mutant) | – | vetoable by Maisara | accepted (Maisara 2026-11-08, no vetoes) |

Diff check (interrogator, /fix-plan step 5) of the applied plan edits (commit 67034fe): nothing WRONG.

| id | type | claim | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| P06B-74 | FACT | AX31 row: rationale "the 35 ms rotation rows … don't apply to v1" vs the appended note "head rotation deferred to phase-08 item 8, not out of scope" | INCONSISTENT → applied: the rationale now names only the source-rotation / directivity row and §15's 50 ms; the head-rotation row is deferred to phase-08 item 8 | Vorländer Table 15.1 (two 35 ms rows) | major | – | closed |
| P06B-75 | NUMBER | AX32 "peak taps 0.155–0.49 over the test scenes" | IMPRECISE → applied: "0.155 in medium_room to 0.49, the largest over the test scenes" (smallest peak not measured) | M1 | minor | – | closed |
| P06B-76 | NUMBER | phase-08 item 8: W1 in (13.7, 24.3] ms decides the row | IMPRECISE → applied: "under the 35 ms limit with the fade not counted"; under 20 ms neither variant meets it for W1 | Vorländer §15, Table 15.1 | minor | – | closed |

Outside the diff: the plain D1 line for Maisara (P06B-63, "compensates … on playback and bounce") is qualified
in the PR / report text.

## docs/phases/phase-07.md — interrogation (2026-11-08; /interrogate; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Interrogator, document mode, on `docs/phases/phase-07.md` with BUILD_PLAN §2 (AQ4, AQ5, AQ10, AX1, AX2, AX5,
AX6, AX7, AX9, AX18, AX31, AX32), PRD FR-3D-5/8/10, FR-LIC-1, NFR-2, NFR-6, phase-06b, phase-08 and the `src/sim`
API (`RealtimeEngine.h`, `Engine.h`, `CrossfadingConvolver.h`, `BandRenderer.h`, `NoiseTail.{h,cpp}`). Rows tagged
(API)/(plan) are rated against those documents, not the corpus. Not rated (pure software): JUCE APVTS and generic
editor, pluginval/auval, TSan, boundary check, bus layout, ID list file, 1 000-blob fuzz, XML vs JSON state,
embedded default scene, 20 ms trim smoothing. The target document was not edited (changes are Maisara's, via /fix-plan).

### Interrogator ledger (round 0)

The interrogator's five questions (most severe first): (1) P07-5/P07-6, (2) P07-14/P07-15, (3) P07-16/P07-17,
(4) P07-8, (5) P07-19. The other rows are findings; all 29 are answered below.

| id | kind | finding / question | verdict | evidence | severity |
|---|---|---|---|---|---|
| P07-1 | NUMBER | Reported latency 544 samples at P = 512 (P + 32) | CORRECT | `RealtimeEngine.h` latencySamples(); AQ10/AX1; 11.33 ms at 48 kHz; Izhaki Ch. 11 "Plugin delay compensation" | none |
| P07-2 | NUMBER | Latency AC: first peak at exactly getLatencySamples(), emitter at 0.3 m, α = 1 | CORRECT on timing; IMPRECISE on why 0.3 m | AX1 / `Engine.h` alignment removes the 0.3 m (≈ 42-sample) propagation delay; zero-phase filterbank (`BandRenderer.h`); 0.3 m only sets amplitude (+10.46 dB, AX2); α = 1 → Eyring T → 0 (Kuttruff Eq. 4.12) | minor |
| P07-3 | NUMBER | AX2 "0 dB at 1 m" with both emitters summed in the mono preview | IMPRECISE (per path, not per track) | `Engine.h` out = Σ in·h; coherent L = R +6 dB, uncorrelated +3 dB (Vorländer §1.7, Table 1.3, Eq. 1.38); worst direct gain 20·log10(2/0.3) = +16.5 dB | minor |
| P07-4 | CONSEQUENCE | Mono preview sums two coherent emitters at one receiver | CONSEQUENCE | Vorländer §1.7; comb filtering from delay differences (Izhaki Ch. 11); notches at (2k+1)c/(2Δd) when `listener_x` moves | minor |
| P07-5 | FACT (plan) | Push-away along listener→emitter keeps the scene valid | INCONSISTENT with AX6 / contract README | counter-example: 1.5 m room, listener x = 0.3, emitter x = 0.1 → pushed to x = 0.0; direction undefined when coincident; a valid point always exists (box side ≥ 1.3 m > 0.6 m) | major |
| P07-6 | FACT (plan) | Is params → scene a pure function (push, resize)? | NOT SPECIFIED (AX5 at risk) | stored or written-back pushes make output order-dependent and fight host automation | major |
| P07-7 | DECISION | Resizing keeps relative positions | CONSEQUENCE | default scene scaled to 100 m: distance 6.09 → 53.0 m, −18.8 dB direct (Blauert Ch. 2, distance cues); ear height 42 m | minor |
| P07-8 | FACT (listening) | "min … max: small booth vs large hall" | CONDITIONS VIOLATED (12 s cap) | 100 m cube, medium_room materials, Eyring with air (Kuttruff Eq. 4.12, Table 6.1): T 15.1 s (500 Hz), 10.9 s (1 kHz), ≈ 39–43 s (125 Hz); IR = min(12 s, 1.5·T60max) (`NoiseTail.cpp`) cut without fade after ≈ 18 dB of decay at 125 Hz | major |
| P07-9 | NUMBER (plan) | CPU at maximum room size | NOT CHECKABLE (corpus) | AQ10 ≤ 15 % stated for a 3 s tail; linear estimate ≈ 25 % for 12 s | minor |
| P07-10 | NUMBER (plan) | Builder-thread memory at maximum room | NOT CHECKABLE (corpus) | estimate ≈ 37 MB per IrSet at 96 kHz / 12 s, up to ~4 live + FDL ≈ 18.5 MB | minor |
| P07-11 | DECISION | 1.5 m minimum room reachable from a host parameter | CONSEQUENCE | Kuttruff Eq. 3.44, §3.6: f_s ≈ 520–880 Hz at V = 3.375 m³; diffuse tail model not valid below | minor |
| P07-12 | NUMBER (plan) | "Runs at most every 20 ms" | CORRECT as a cap; semantics open in AQ4 (INCONSISTENT) | AQ4 defers the cap's meaning to a Phase 10 AX but 07 must implement one; 32 ms output interval at P = 512 (AQ4/AX31); 07 rebuilds are full (no tail cache); Vorländer Table 15.1 700 ms | minor |
| P07-13 | FACT (plan) | Crossfade law for state recall and room-size swaps unstated (engine default EqualGain) | IMPRECISE | AX18; equal gain on uncorrelated outputs dips −3.0 dB (Vorländer §1.7, Eq. 1.37) | minor |
| P07-14 | FACT (API) | Offline: processBlock builds and submits synchronously "so bounces are deterministic" | INCONSISTENT with `RealtimeEngine` contract and AX5 | submitRoomIR is "any non-audio thread"; latest-wins mailbox; an in-flight builder-thread IR can land after the synchronous one | major |
| P07-15 | FACT (API) | Bit-identical bounces vs fade timing from the sample counter | CONDITIONS VIOLATED | AX31 s0 = (⌊r/P⌋+2)·P counted from prepare/reset; RealtimeEngine has no reset(); change enters up to 2P later | major |
| P07-16 | AC testability | State round-trip / offline-determinism ACs pass with a no-op restore or ignored change | AC DOES NOT DISCRIMINATE | default state restores to itself; an ignored 2.0 s change is still deterministic | major |
| P07-17 | FACT (plan) | Positions/dimensions in both scene JSON and APVTS: which wins? | NOT SPECIFIED (AX5 at risk) | float32 normalized ↔ metres not exact (≈ 6 µm at 100 m) | major |
| P07-18 | FACT (API) | Default scene `outputMode: binaural`, 07 renders omni | IMPRECISE | `Engine.h` kindForOutputMode(binaural) = dry stub; 07 must force Omni; 07-era projects render differently after 08 | minor |
| P07-19 | FACT (API) | prepareToPlay builds IR and reports latency | CONDITIONS VIOLATED (only AX6 rates) | `RealtimeEngine::prepare` throws std::invalid_argument outside 44.1/48/88.2/96 kHz | major |
| P07-20 | FACT (API) | setStateInformation "rebuilds the IR synchronously" | CONDITIONS VIOLATED | called before prepareToPlay (Logic, 07 Risks); submit fails on rate mismatch | minor |
| P07-21 | FACT (plan) | "Non-finite input zeroed inside the engine" | IMPRECISE | AX32 also zeroes |x| > 2²⁰ (`CrossfadingConvolver.h`) | minor |
| P07-22 | NUMBER | 1.5–100 m, 0.1 m margin ↔ 0/1, 0.3 m min distance | CORRECT; skew unspecified | AX6, README, AX9 1 nm tolerance; skew frozen into `parameter_ids_v1.json` | minor |
| P07-23 | FACT (API) | prepare drops IRs; join builder first; bare convolver untouched when unprepared; allocation off audio thread | CORRECT | `RealtimeEngine.h`, `CrossfadingConvolver.h` | none |
| P07-24 | FACT (listening) | Moving `listener_y` away: "more distant and roomier" | CORRECT | Blauert Ch. 3 §3.3; Vorländer Fig. 4.7; under AX1 no propagation-delay cue (Vorländer Eq. 2.5) | none |
| P07-25 | FACT (listening) | With PDC, drum hits line up with a dry duplicate | CORRECT, with a condition | Izhaki Ch. 11; under AX1 only the nearest emitter is on the grid (1 m farther → 2.9 ms) | minor |
| P07-26 | NUMBER | "Bit-identical (same platform)" vs NFR-6 | CORRECT | AX5 | none |
| P07-27 | FACT (PRD) | FR-3D-10 with coalescing and latest-wins mailbox | IMPRECISE | holds only if the last dirty state is always built (no lost wake-up) | minor |
| P07-28 | AC testability | "No allocation / lock in processBlock" | IMPRECISE | AllocationTracker sees allocations, not locks; APVTS listeners may run on the audio thread | minor |
| P07-29 | DECISION | Two emitters (AX7) vs FR-3D-5 "any number" | PRODUCT MATTER | AX7 recorded user decision | none |

### Builder answers (round 1)

Status key: **resolved** = the answer settles it with no change to phase-07 needed; **open** = phase-07 (or an
AX) needs a wording or decision change, which is Maisara's via /fix-plan; **disputed** = builder disagrees with
the verdict (none this round).

| id | builder answer | status |
|---|---|---|
| P07-1 | Agreed. | resolved |
| P07-2 | Agreed. The latency AC tests one thing: the reported latency equals the arrival of the aligned direct sound. 0.3 m maximises the direct peak relative to everything else, so the peak pick is unambiguous. With α = 1 there are no reflections (Kuttruff Eq. 4.12: T → 0), so distance only scales the peak (AX2). Distance independence of the alignment is AX1 and is already Phase 03's test, so one distance is enough here. No change needed. | resolved |
| P07-3 | Agreed: AX2 holds **per emitter path**. Coherent L = R material sums +6 dB in each output (Vorländer §1.7, Table 1.3). The +16.5 dB worst case (both emitters at 0.3 m) is inside the −24 dB trim range. Whether that headroom and the reverb energy on top are acceptable is product matter. Proposed wording: "AX2 is per emitter path; the mono preview sums both paths". | open (wording) |
| P07-4 | Agreed. Comb colouring is a property of the mono preview (two delayed coherent copies at one receiver; Vorländer §1.7; Izhaki Ch. 11 on delay-induced comb filtering). It goes away in Phase 08 when L and R reach two ears through different HRTFs. Proposed: add a checklist line so Maisara does not report it as a defect. | open (checklist wording) |
| P07-5 | Agreed: INCONSISTENT. Proposed rule (pure, deterministic): (1) clamp listener and emitters to the margin box; (2) if \|e − l\| < 0.3 m, set e = l + 0.3·d, with d = (e − l)/\|e − l\| or +y (AQ1 forward) when \|e − l\| = 0 (exact float equality); (3) clamp to the box; (4) if still < 0.3 m, use l + 0.3·s·â, where â is the axis with the most free room for the listener (ties x, y, z) and s its sign. Step 4 always succeeds: the box side is ≥ 1.3 m, so on every axis the listener has ≥ 0.65 m to one side. Needs a /fix-plan wording change. | open (needs /fix-plan) |
| P07-6 | Builder intent: the scene is a **pure function** of (current parameter values, non-parameter scene fields). The push is recomputed on every change and is never stored or written back to a host parameter. State restores the parameters and re-derives the push. That keeps AX5 independent of the order of changes and does not fight automation in read mode. Needs to be written into scope 2. | open (needs /fix-plan) |
| P07-7 | Agreed consequence (Blauert Ch. 2 distance cues: the −18.8 dB follows from 1/r). Relative positions are what the plan specifies, and they keep the scene valid at any size without clamping jumps. Absolute positions with clamping are the alternative. This is a product choice, frozen with the parameter IDs. | open (product, Maisara) |
| P07-8 | Agreed; I checked the code: `tailLengthS` = min(12 s, kTailDecayRangeDb/60 · T60max), with no end fade (`NoiseTail.cpp`). AX6 already records that renders over the cap are truncated, but in 07 it becomes a host-reachable parameter. Options for Maisara: (a) accept and say so in the checklist ("at maximum size the low end is cut at 12 s"); (b) add a short end fade at the cap (changes Phase 04 output: goldens, AX entry); (c) lower `room_h`/`room_w`/`room_d` maxima (contract stays 100 m). Builder recommends (a) for 07 with an AX note, and (b) as a Phase 10/13 follow-up. | open (product, Maisara) |
| P07-9 | Not checkable from the corpus, but already measured: BUILD_PLAN §0 row 06 records a 12 s IR at P = 512, host 512: steady 7.3–11.7 %, crossfading 14.0–26.2 % (run 42355829013). AQ10's 15 % is stated for a 3 s tail only, so 07 makes no CPU claim at maximum size. | resolved |
| P07-10 | Not checkable from the corpus. The engine already pre-allocates its history for 12 s at prepare (`RealtimeEngine::maxIrLengthSamples`), so the audio thread never allocates. The IrSet sizes are an estimate. Proposed: Phase 07 logs peak RSS at 96 kHz with the maximum room in its PR (no gate). | open (follow-up, measurement) |
| P07-11 | Agreed (Kuttruff §3.6, Eq. 3.44: below f_s the field is modal, not diffuse). A known limit of the ISM + diffuse tail model, not new in 07; 07 only exposes it on a parameter. Proposed: record it as a model limit (AX note), no change to the build. | open (product note) |
| P07-12 | Agreed: 07 has to implement one semantics now. Builder proposal: AQ4's recommendation (decider D1 Q2): a minimum 20 ms spacing between build **starts**, and an isolated request starts at once. Phase 10 then confirms or changes it through the AX it already owes. 07 also records the measured full-rebuild time (default and maximum room) in §0. Needs an AX row or a sentence in phase-07 scope 3. | open (needs /fix-plan) |
| P07-13 | Agreed (AX18; Vorländer §1.7, Eq. 1.37: −3 dB with equal gain on uncorrelated signals). Proposed: equal-power for state recall (setStateInformation during playback) and for room-size changes (new tail, new modal structure); equal-gain for listener/emitter position changes. Needs a sentence in scope 3. | open (needs /fix-plan) |
| P07-14 | Agreed: INCONSISTENT. Proposed: when isNonRealtime() is true, the builder thread is quiesced (stop accepting work, join any in-flight build, drain it before the first offline block), and processBlock builds and calls submitRoomIR itself. The "non-audio thread" restriction exists because submit allocates and frees. In offline mode that is acceptable, and no other thread touches the engine. RealtimeEngine.h's comment then needs "or the processing thread when nothing else submits". The switch back to realtime restarts the builder. | open (needs /fix-plan) |
| P07-15 | Agreed. Proposed: add `RealtimeEngine::reset()` (forwards to `CrossfadingConvolver::reset()`, clearing the history and the sample counter, keeping the current IR) and call it from the JUCE `AudioProcessor::reset()` and on entering non-realtime mode. The determinism AC then renders two bounces in **one** instance with a reset in between, plus a fresh instance, all three bit-identical with the same block partitioning. Note in scope 3 that "synchronous" means the IR is submitted before the block; under AX31 it enters the output up to 2P later, identically in every run. | open (needs /fix-plan) |
| P07-16 | Agreed. Proposed AC wording: the saved state differs from the default in at least one parameter (e.g. `listener_y`) and one non-parameter field (tailSeed and one α). The test asserts that the restored output differs from a default-instance output, and that the 2.0 s change makes the output after 2.0 s differ from a run without the change. | open (needs /fix-plan) |
| P07-17 | Builder proposal: on restore the **APVTS values are authoritative** for every field that has a parameter, and the scene JSON for every other field. The scene is re-derived from (parameters, JSON) by the same pure function as P07-6, so live and restored renders match bit for bit on one platform. If they disagree, the parameters win and the JSON value is ignored, with no warning. Needs a sentence in scope 4. | open (needs /fix-plan) |
| P07-18 | Agreed. 07 forces Kind::Omni and stores outputMode unchanged. No released projects exist before v1 ships, so NFR-6 is not at stake; Phase 08 changes the render of 07-era states by design. Proposed wording in "Assumptions in force": "07 ignores outputMode/output_mode; renders omni". | open (wording) |
| P07-19 | Agreed. Proposed: prepareToPlay catches the unsupported rate. The engine stays unprepared (silence, per `RealtimeEngine.h`), the warning flag is set (shown in Phase 11), and the reported latency stays P + 32, so PDC doesn't jump if the host later switches to a supported rate. Silence vs dry pass-through is Maisara's call (builder recommends silence plus the flag: a dry pass-through would be mistaken for the room). pluginval's sample-rate test must cover it. | open (product, Maisara) |
| P07-20 | Agreed: if not prepared, setStateInformation validates and stores the scene, and the synchronous build happens in the next prepareToPlay. Wording in scope 4. | open (wording) |
| P07-21 | Agreed: restate as "non-finite input and \|x\| > 2²⁰ are zeroed inside the engine (Phase 06, AX32)". | open (wording) |
| P07-22 | Agreed. The skew is a software choice, but it is frozen. Proposed: JUCE `NormalisableRange` with skew set so that 10 m sits at the centre (log-like over 1.5–100 m), recorded in `parameter_ids_v1.json`. Product sign-off before the freeze. | open (product, Maisara) |
| P07-23 | Agreed. | resolved |
| P07-24 | Agreed (Blauert Ch. 3 §3.3; Vorländer Fig. 4.7). | resolved |
| P07-25 | Agreed (Izhaki Ch. 11; AX1 aligns the nearest emitter only). Proposed checklist note: "use the default symmetric L/R positions for this check". | open (checklist wording) |
| P07-26 | Agreed. | resolved |
| P07-27 | Builder intent: an atomic dirty generation counter. The builder rebuilds while the counter has changed since its last build start, so the final state is always built (no lost wake-up). A unit test fires N changes and asserts that the last submitted scene equals the final parameters. Wording in scope 3. | open (wording) |
| P07-28 | Agreed. "No lock" can't be proven by the AllocationTracker. Proposed: the parameter listener only does an atomic store (code review plus a test that the listener path makes no allocation), and the TSan AC covers the cross-thread part. The AC should say "no allocation (tested); no lock (by construction, reviewed)". | open (wording) |
| P07-29 | Agreed: AX7 is a recorded user decision. | resolved |

### Re-rounds

The interrogator rated no row **blocker** (its scale: a WRONG item that code, a test gate or a golden will be
built on). Under `/interrogate`, re-rounds run only for open blockers, so **no re-round needed**. Statuses above
are final for this session: 7 resolved, 22 open, 0 disputed.

### Unresolved (each closes through /fix-plan on phase-07, Maisara's decision)

- **Major (should be settled before Phase 07 starts):** P07-5 (push-away rule keeping AX6), P07-6 (pure params →
  scene function), P07-14 (offline submit thread, builder quiesced), P07-15 (`RealtimeEngine::reset()`, bounce
  determinism AC), P07-16 (discriminating state/determinism ACs), P07-17 (parameters authoritative on restore),
  P07-19 (unsupported sample rates: silence + flag vs pass-through), P07-8 (12 s truncation at maximum room:
  accept / end fade / lower maxima).
- **Product choices for Maisara:** P07-7 (resizing moves sources), P07-11 (small-room modal limit noted),
  P07-22 (room-size skew before the freeze), and P07-3 (trim headroom) and P07-19/P07-8 above.
- **Wording/checklist (minor):** P07-3, P07-4, P07-12 (cap semantics for 07, needs an AX or sentence), P07-13
  (crossfade law), P07-18, P07-20, P07-21, P07-25, P07-27, P07-28.
- **Measurement follow-up:** P07-10 (peak memory at 96 kHz, maximum room).

### /fix-plan on the open rows (2026-11-08, Maisara: "why are you waiting for me? You have people to delegate to - cehck claude.md"; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Run by the main session under `.claude/commands/fix-plan.md`. Records in `docs/review/phase-07/`:
interrogator-option-check.md (step 3), research-dossier.md (researcher + M1: auval renders at 11.025/22.05/192 kHz,
CI run 42452887610), decider-round1/2/3.md, interrogator-decision-round1/2/3.md, advocate-round1/2.md,
interrogator-diff-check-1/2/3.md (wording fixes). Commits e2f1d7a, a06e5ca, 8493ac7, 38bbbfe (wording/software),
7871f26, 614a005 (decisions). Decisions are **proposals Maisara can veto**.

Paths: **W** = wording/software fix by the plan-editor, diff-checked by the interrogator (3 rounds; P07-15a blocker
found and closed in round 2; nothing WRONG/INCONSISTENT left after round 3). **V** = interrogator-verified option (one
CORRECT, others not). **L** = decision loop (researcher → decider → interrogator decision mode → advocate).

| row | end state | path | outcome |
|---|---|---|---|
| P07-3 | resolved | W + L (D4) | AX2 per emitter path; output_trim_db −48…+24 dB (band-mean basis; +24 covers the ≈ 22 dB mid-band drop at max room); extreme-scene gain recorded in the PR |
| P07-4 | resolved | W | checklist: comb colouring expected for coherent L/R in the mono preview; less audible or inaudible binaurally (Blauert Ch. 4) |
| P07-5 | resolved | L (D1) | nearest valid point on the 0.3 m sphere in the margin box, tie-break y, x, z; tie jumps up to 0.6 m; brute-force reference test |
| P07-6 | resolved | W | scene = pure function of parameters + non-parameter fields |
| P07-7 | resolved | L (D2) | relative positions kept; consequence documented; absolute-position resize gesture → phase-11 item 5 |
| P07-8 | resolved (07) + follow-up | L (D3) | 07 accepts and documents the 12 s cut (checklist; AX6 note); end treatment Q1–Q3 → phase-13 item 10 |
| P07-10 | follow-up | W | peak RSS at 96 kHz / max room recorded in the 07 PR (DoD) |
| P07-11 | resolved | V (D5) | Risks line: modal below ≈ 520–1040 Hz in the 1.5 m room (Kuttruff §3.6 Eq. 3.44); raising the minimum would not remove it |
| P07-12 | resolved | L (D6) | AX33: 20 ms = minimum spacing between build starts; isolated request starts at once; AQ4 pointer; phase-10 scope 8 confirms or replaces |
| P07-13 | resolved | L (D7) | skip bit-identical IRs; restore flag consumed by the restore's own decision → EqualPower; EqualGain placeholder otherwise; AX18 amended (correlation of position updates, ρ_b formula); phase-10 position-fade gate with known limit |
| P07-14 | resolved | W | one reset sequence; builder quiesced offline; processBlock the only submitter during a bounce |
| P07-15 | resolved | W | `RealtimeEngine::reset()` = post-prepare state (no IR, empty mailbox); resubmit; determinism AC incl. same instance + fresh instance |
| P07-16 | resolved | W | discriminating state and determinism ACs |
| P07-17 | resolved | W | parameters authoritative on restore |
| P07-18 | resolved | W | 07 forces omni; outputMode kept |
| P07-19 | resolved | L (D8) | AX34: bypass-like delayed dry pass-through at unsupported rates, flag set; warning → phase-11 item 7; resampling → phase-13 item 11 |
| P07-20 | resolved | W | state before prepareToPlay stored, built in prepareToPlay |
| P07-21 | resolved | W | AX32 bound stated |
| P07-22 | resolved | L (D9) | true log map L = 1.5·(100/1.5)^x, explicit endpoints, tested on three OSes |
| P07-25 | resolved | W | PDC checklist: symmetric L/R |
| P07-27 | resolved | W | dirty generation counter; builder compares against the recorded submitted generation (R3-1); no-lost-update test |
| P07-28 | resolved | W | no allocation tested; no lock by construction (atomic increment), TSan |

D7 final advocate screen of the applied text: PASS (`docs/review/phase-07/advocate-round3.md`).

Totals for the 22 rows: 20 resolved, 1 resolved for 07 with a follow-up (P07-8), 1 follow-up (P07-10); none needs
Maisara for correctness. Proposals she can veto: D1, D2, D3, D4, D6 (AX33), D7 (AX18 amendment), D8 (AX34), D9.

Diff check of the applied decisions (interrogator, 3 rounds; `docs/review/phase-07/interrogator-decision-diff-check-1/2/3.md`):
round 1 found nothing acoustic WRONG but three software INCONSISTENT items in the new skip rule / restore flag (DC-1
endless rebuild on a bit-identical skip, DC-2 no-lost-update AC, DC-3 realtime restore decision) plus minors; fixed
(f6dfc2f); round 2 closed them with minor N1–N5; fixed (f9fc41e); round 3: nothing WRONG or INCONSISTENT remains.
Final state of the 22 rows as in the table above.

**Accepted by Maisara 2026-11-08 ("accepted, merge with no ci"): D1, D2, D3, D4, D6 (AX33), D7 (AX18 amendment), D8
(AX34), D9, no vetoes.** Merged to main without a CI run at her instruction.

## Phase 05g — Kuttruff §9.4 citation (scope 3) and the BRAS area tolerance (scope 4) (2026-11-07; /fix-plan; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Scope 3: interrogator check of phase-05.md scope 6 "a* assumes s = 1 on all walls; with low s the true T can fall on the
other side of Eyring (Kuttruff §9.4)" and the §5 B12 citation (§5.7, §9.4). Scope 4: interrogator (options) → decider
(05g-4.1…4.3) → interrogator (decision mode; printed units then read from the BRAS files by the main session: every
material area printed to 0.01 m², S printed 202.53 / 2763.0 / 5851.3) → advocate (PASS ×3 with the interrogator's text
corrections; an engineering choice, not a C2 product choice; Maisara's accept/veto is still asked under fix-plan step 3)
→ plan-editor applied → interrogator diff check (CLEAN on substance; five minor fixes applied by the main session).

| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| G5g-1 | FACT | "a* assumes s = 1 on all walls (Kuttruff §5.7, §9.4)" | IMPRECISE: substance correct, §9.4 the wrong citation | Kuttruff §5.7 L2729–2730 (Lambert premise of Eqs. 5.49–5.56), Table 5.2 caption; §2.7 L1620, §9.8 L4311 (s = 1 diffuse/Lambert); §9.4 L4183–4241 never mentions a* or s | minor | – | applied: §5.7 Eqs. 5.49–5.56, §2.7, §5.2 Eq. 4.24 |
| G5g-2 | FACT | "with low s the true T can fall on the other side of Eyring (Kuttruff §9.4)" | IMPRECISE | §9.4 L4240–4241: regular geometry, smooth walls, non-uniform absorption → 2-D field, measured T ≈ 2 s vs 1.6–1.7 s predicted (formula unnamed); no s, no Eyring comparison | minor | – | applied: corpus wording (§9.4 'coupling without separate rooms'; §5.2) |
| G5g-3 | FACT | implied fixed side of a* relative to Eyring | IMPRECISE | Table 5.2: case 4 a* 1.21 < Eyring 1.38 s, case 6 5.93 > 4.61 s (table governs; printed prose slip L2796) | minor | – | applied: no fixed direction stated |
| T5g-1 | NUMBER | "±0.1 % allowed for rounding of large areas" | IMPRECISE | rounding to 0.01 m² is ≤ 0.005 m² absolute at any size; measured residuals show no size trend (max 0.00477 = E[max] of 20 uniform rounding errors) | minor | – | closed (rationale replaced) |
| T5g-2 | NUMBER | option A (keep) | CORRECT acoustically, loose detector (admits 1.77 m² on CR4 concrete) | Kuttruff Eqs. 5.24–5.26; Vorländer §11.1.1 (0.5 m elements) | none | – | not chosen |
| T5g-3 | NUMBER | option B (0.011 m² absolute) | CORRECT | headroom 0.0062 m² | none | – | chosen (05g-4.1) |
| T5g-4 | NUMBER | option C (≈ 0.006 m²) | CORRECT on data; dataset precision NOT CHECKABLE | headroom 0.0012 m² | none | – | not chosen |
| T5g-5 | NUMBER | option D (relative 1e-5) | WRONG | fails the correct reader (CR2 windows limit 9.75e-5 vs 0.00296 m²) | blocker if adopted | – | rejected |
| T5g-6 | FACT | tightness has no acoustic need | CORRECT | α uncertainty dominates (Kuttruff §9 audience passage; Vorländer §11.1.2) | none | – | closed |
| T5g-7 | DECISION | A/B/C | product/engineering choice | detection threshold vs headroom | minor | – | decided (decider B) |
| T5g-8 | NUMBER | total-S assertion | checked the documentation against itself only | test_skp_reader.py | none | – | closed by 05g-4.3 |
| T5g-9 | SOFTWARE | code and test change together | – | match_materials + test | – | – | applied (shared `AREA_TOL_M2`) |
| T5g-10 | NUMBER | 05g-4.1 arithmetic; every reader area rounds to its documented value | CORRECT | bras_geometry.json | none | – | verified |
| T5g-11 | FACT | "any change ≥ 0.011 m² fails" | WRONG → applied: "> 1.1u + u/2 ≈ 0.016 m² always fails, smaller may pass" | residual up to 0.0048 m² | major (text) | – | closed |
| T5g-12 | NUMBER | u_S per room | UNDERINFORMED → resolved: S printed 202.53 / 2763.0 / 5851.3 (u_S 0.01 / 0.1 / 0.1) | BRAS `_descr/mat_CRx.txt` line 19 | major | – | closed |
| T5g-13 | NUMBER | "a further u/2 for the dataset's computation" vs the CR2 total bound | INCONSISTENT → applied: "twice the rounding bound plus 10 %" | arithmetic | major (text) | – | closed |
| T5g-14 | NUMBER | "5 % jnd" | IMPRECISE → applied: working T jnd, Vorländer Table 6.1 gives 5 % for EDT, B12 iii | Vorländer Table 6.1 | minor | – | closed |
| T5g-15 | NUMBER | self-check bound n·u/2 + u_S/2 = 0.030 / 0.085 / 0.090 | CORRECT | arithmetic | none | – | verified |
| T5g-16 | NUMBER | every material printed to 0.01 m² | resolved: yes (178.90, 698.50, 8.50 …) | BRAS files | none | – | closed (the extractor now checks it) |
| T5g-17 | DECISION | relative term removed in the matcher too | CONSEQUENCE | – | minor | – | applied |
| T5g-18 | DECISION | reversal: a correct reader above 1.1u on a new room → /fix-plan, never per room | CONSEQUENCE | – | none | – | applied |
| 05g-4.1 | DECISION | per-material \|A_reader − A_doc\| ≤ 1.1u = 0.011 m² absolute, no relative term, one shared constant | decider; interrogator SURVIVES WITH CORRECTIONS; advocate PASS | above | – | accepted by Maisara 2026-11-08 | applied: `extract_bras_geometry.AREA_TOL_M2`, `test_skp_reader.py`, bras_mapping §2 |
| 05g-4.2 | DECISION | bras_mapping §2 rationale text | decider; corrections T5g-11/13/14 applied; advocate PASS | above | – | accepted by Maisara 2026-11-08 | applied |
| 05g-4.3 | DECISION | reader total (all faces, unpainted included) vs S within 1.1 u_S (measured 0.0027 / 0.026 / 0.033 m²); documentation self-check bound n·u/2 + u_S/2 replacing 0.06 | decider; interrogator UNDERINFORMED → resolved; advocate PASS | above | – | accepted by Maisara 2026-11-08 | applied: `check_total_area`, `documentation_sum_bound_m2`, test |

Maisara's accept/veto of 05g-4.1…4.3 (fix-plan step 3: several options were valid, T5g-2/3/4): **accepted by Maisara 2026-11-08 ("I'm okay with both", asked to accept or veto: no veto, the committed rule stands)**.

Finished diff (interrogator, step 5): **CLEAN on substance**; all numbers re-derived (0.011 / 0.11 / 0.11; 0.016;
0.030 / 0.085 / 0.090; 1 105 m², 4.93 m, 7.84 m; reader skip counts).

| id | kind | item | verdict | evidence | severity | status |
|---|---|---|---|---|---|---|
| D5g-1 | FACT | a* Lambert premise, Kuttruff §5.7 Eqs. 5.49–5.56 | CORRECT | §5.7 (Eq. 5.49 kernel 5.50; a* Eq. 5.53; iteration 5.54–5.56) | none | closed |
| D5g-2 | FACT | "s = 1 is Lambert reflection, §2.7" | IMPRECISE | §2.7 says "diffusely reflecting"; Lambert in §5.2 / Eq. 4.24, §9.8 | minor | applied |
| D5g-3 | FACT | "large face absorbs (cases 2, 4)" | IMPRECISE | Table 5.2 case 2 is a cube (six equal faces); case 4 the largest face | minor | applied |
| D5g-4 | FACT | §9.4 smooth walls + non-uniform absorption | CORRECT, "regular geometry" omitted | §9.4 L4240–4241 | minor | applied |
| D5g-5 | NUMBER | 1.1u = 0.011 m² | CORRECT | arithmetic | none | closed |
| D5g-6 | NUMBER | reader total vs S limits 0.011 / 0.11 / 0.11 | CORRECT (measured values: data) | printed decimals | none | closed |
| D5g-7 | NUMBER | detection floor ≈ 0.016 m² | CORRECT | u/2 + 1.1u | none | closed |
| D5g-8 | NUMBER | "≤ 0.13 %" for T | IMPRECISE: largest undetected error 0.016 m² → 0.19 % (Sabine, Eq. 5.26) | Kuttruff Eq. 5.26 | minor | applied |
| D5g-9 | NUMBER | 5 % working T jnd, Vorländer Table 6.1 EDT | CORRECT | Vorländer §6.4 Table 6.1 | none | closed |
| D5g-10 | NUMBER | self-check bound 0.030 / 0.085 / 0.090 | CORRECT | arithmetic, n = 5 / 7 / 8 | none | closed |
| D5g-11 | NUMBER | smallest material 8.50 m², smallest faces ≈ 1e-5 m² | CORRECT (consistent) | §5 areas; reader data | none | closed |
| D5g-12 | NUMBER | former rule '0.01 m², ±0.1 %' vs '0.011 m²' | INCONSISTENT (bookkeeping) | phase-05g scope 4; code abs_tol=0.011 | minor | applied (documented vs coded both named) |
| D5g-13 | NUMBER | CR4 1 105 m², 4.93 m, 7.84 m | CORRECT | arithmetic | none | closed |
| D5g-14 | DECISION | tolerance set by misparse detection | CONSEQUENCE | Eq. 5.26: ≤ 0.19 % vs 5 % | minor | closed |
| D5g-15 | DECISION | AX26 unchanged, CR4 box flat | CONSEQUENCE | Kuttruff §5.3, §5.7 Table 5.2 / Fig. 5.11 | minor | closed (Expert question) |
| D5g-16 | FACT | §6 row "§9.4 citation … corrected" for B12 | IMPRECISE | B12 no longer cites §9.4 | minor | applied |
| D5g-17 | SOFTWARE | reader statements in the §6 row | consistent with `skp_reader.py` docstring | – | – | closed |
| D5g-18 | SOFTWARE | threshold applied to code and test | consistent (`AREA_TOL_FACTOR`) | – | – | closed |

Six minor fixes (D5g-2, 3, 4, 8, 12, 16) were applied by the main session in the interrogator's proposed wording (its
"Fixes" list), not by the plan-editor; T5g-12 (printed units) was resolved by the main session reading the BRAS files,
and `extract_bras_geometry.documented_units` now checks the printed units in the BRAS-cache tests. The fixes were:
D5g-2 (s = 1 ↔ Lambert also cited to §5.2 Eq. 4.24), D5g-3 ("when the absorption sits on one face (cases 2, 4; in case 4
the largest)"), D5g-4 ("regular geometry" added to the §9.4 conditions), D5g-8 (the T effect stated for the largest
undetected error, < 0.016 m² → ≤ 0.19 % Sabine, Eq. 5.26), D5g-12 (former rule: documented '0.01 m², ±0.1 %', coded
max(0.011 m², 1e-3·A)), D5g-16 (§6 row: B12 citation replaced, not "§9.4 corrected").

## Phase 07 follow-ups recorded in the plan (2026-11-08; /fix-plan; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Maisara 2026-11-08: "Have we recorded those follow ups in a phase? Otherwise they will be lost and our progressive phase execution will miss them!". Source: PR #23 "Follow-ups". Already recorded before this edit: `output_mode` wiring (phase-08, phase-09 scope 5), AX33 confirm/replace (phase-10 scope 8). Plan-editor: all applied, no DECISIONS NEEDED (no acoustic or numeric choice; numbers are measurements from CI run 42465826545).

| id | passage | verdict (interrogator, diff check) |
|---|---|---|
| P07F-1 | phase-13 scope 1: full-rebuild times 48 kHz default/max (Linux 183.6/752.1, macOS 132.7/801.9, Windows 141.8/603.0 ms) | CORRECT against the CI run; not checkable against the corpus (measurement) |
| P07F-2 | same at 96 kHz (392.4/1883.7, 278.6/1832.1, 295.2/1509.1 ms) | CORRECT; not checkable against the corpus |
| P07F-3 | RSS +122.6 MB per instance, Linux, 96 kHz, maximum room | CORRECT; not checkable against the corpus |
| P07F-4 | "maximum room (100 × 100 × 100 m)" | CORRECT against phase-07 scope 2 / contract README |
| P07F-5 | phase-13 scope 1: memory budget left to that phase | not rated (no value) |
| P07F-6 | phase-10 scope 8: builder 1 ms idle poll, listener only fetch_add | CORRECT against the code (IrBuilderThread.h kIdlePollS, ScenePipeline.cpp setParameter) |
| P07F-7 | phase-10 scope 8: Phase 10 states the worst-case extra delay | CORRECT; consistent with AQ4/AX31/AX33 (their bound excludes the ≤ 1 ms poll) |
| P07F-8 | phase-13 scope 12: cache the pinned pluginval release | not rated (software) |
| P07F-9 | BUILD_PLAN §5 B13 `dry_wet` | not rated (decision deferred); consistent with phase-07 scope 2 |
| P07F-10 | BUILD_PLAN §4 summaries (10, 13), §6 row | CORRECT; mirror the phase text, no assumption/threshold/golden changed |

Context noted by the interrogator (not a defect): the default-room full rebuild (133–184 ms at 48 kHz) includes tail-noise generation and is not the AQ10 W1/W2 position-only workload; phase-10's acceptance already allows phase-13 optimisation or `blocked (AQ10 miss)`. Status: applied, verified, committed.

## Phase 05b: patch size at a compute limit (D1 → AX35, 2026-11-08; decision loop + /fix-plan; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Decider D1 (rounds 1–2), interrogator (decision mode, three rounds), advocate GO (round 1 REDIRECT on D1c settled by D1c′). Applied as AX35 (BUILD_PLAN §2), phase-05b scope 0 / scope 4 notes, AX16 count fix; vetoable by Maisara. Departures from accepted text listed for her: scope 0's joint certification of one ℓ, the Definition of done "all automated criteria evaluated", scope 4 (i)/AX16 "switches".

| id | claim | verdict | status |
|---|---|---|---|
| P05B-01 | E_target meets scope 0 at 1.25 m | IMPRECISE → restated: certified at 2.5 m, evaluated at 1.25 m | applied |
| P05B-02 | a* ≤ 0.42 % | CORRECT value; scope = the four (A) geometries only, BRAS rooms are R1 | applied |
| P05B-03 | gated-bin changes 3.230→3.181 % (layouts 5/6 s = 1), 14.6→5.36 % (layout 4 s = 1) | CORRECT | — |
| P05B-04 | non-convergence attributed to ℓ | open → resolved by P05B-27 | resolved |
| P05B-05 | 0.625 m rung 15–49 GB: compute limit, not the c·Δt floor | CORRECT (computed) | — |
| P05B-06 | air-factored rungs comparable with the full run | CORRECT (≤ 1.02e-4) | — |
| P05B-07 | ΔL_b,tr independent of ℓ | CORRECT | — |
| P05B-08 | (B) fails → not promoted regardless of (A) | CORRECT (plan logic) | — |
| P05B-09 | corpus gives no patch-size criterion (Kuttruff §4.5 Eqs. 4.32/4.33; Vorländer Eqs. 10.26/10.27) | CORRECT | — |
| P05B-10 | labelling vs skipping (A), per-quantity reading | NOT CHECKABLE (product) | listed for Maisara |
| P05B-11 | ℓ-sensitive flag as a bound | IMPRECISE (minor) → "heuristic flag, not an error bound" | applied |
| P05B-12 | no src/sim ℓ in every branch | FALLS under branch (i) → replaced by D1c′ (switch waits for R1, R2, Maisara) | applied |
| P05B-13 | bias trigger evaluable at 1.25 m | UNDERINFORMED → moot: not evaluated (AX35 (b)) | applied |
| P05B-14 | joint vs per-quantity certification | holds on plan text, survives on science | listed for Maisara |
| P05B-15 | AX16 "26 of 255" vs three-room "26 of 345" | INCONSISTENT (minor) → AX16 aligned | applied |
| P05B-16 | E_target certified at 2.5 m by the halving rule | CORRECT | — |
| P05B-17 | margin rule | IMPRECISE (minor) → heuristic, per case-band | applied |
| P05B-18 | one reading must govern D1a and D1b | INCONSISTENT → per-quantity reading for both | applied |
| P05B-19 | per-bin (A) uncertifiable on available compute | CORRECT | — |
| P05B-20 | "(A) not evaluated" vs brief/DoD text | plan point → listed for Maisara (vetoable) | listed |
| P05B-21 | not promoted on (B); bias "not evaluated" | CORRECT | — |
| P05B-22 | tracer self-checks ℓ-independent | CORRECT (s = 1 diagnosis still rests on DB-1, open) | — |
| P05B-23 | "≈ 3 TB" framing | NOT CHECKABLE as stated → 9 600²·1 035·4 B·8 bands of this implementation; R2 per formulation | applied |
| P05B-24 | D1c′ inference, research named | CORRECT (UNDERINFORMED, gap named: R1, R2) | — |
| P05B-25 | D1e conditional on the Δt diagnostic | resolved by P05B-27 | resolved |
| P05B-26 | count aside | resolved (= P05B-15) | resolved |
| P05B-27 | Δt halving at 2.5 m ≤ 0.126 % vs ℓ halving 3.18–5.36 % (`ell.dt_check`, commit 98baa04) | CORRECT: the cause is ℓ | — |
| P05B-28 | D1e "certified ℓ" | IMPRECISE → re-worded: < 1 % rule at 1.25 m, else scope 0's floor branch at 0.625 m | applied |
| P05B-29 | compute limit 15–49 GB, floor 0.343 m | CORRECT | — |
| P05B-30 | per-quantity rule | NOT CHECKABLE (product), survives | listed for Maisara |
| P05B-31 | D1a text | CORRECT | — |
| P05B-32 | D1b ground | CORRECT | — |
| P05B-33 | record wording ("not evaluated (compute limit, AX35)") | CORRECT | — |
| P05B-34 | scope 4 (i)/AX16 "switches" departure | IMPRECISE (minor) → added to Maisara's list | applied |
| P05B-35 | 3 052 GB arithmetic | CORRECT | — |
| P05B-36 | "≥ 49 GB" for the dense route | IMPRECISE (minor) → "≈ 147 GB with the current dense solver" | applied |
| P05B-37 | re-run rule | CORRECT | — |

Diff check of the /fix-plan text (interrogator, rows P05B-38…56): every changed passage CORRECT (AX16 26 of 345 recounted from report-phase05.md §6a, sub-values, AX35 numbers 0.324 % / 0.417 % / 5.36 % / 3.23→3.18 %, 15–49 / ≈ 147 GB recomputed, 3 TB order of magnitude, phase-05b notes, §6 row); three minor wording corrections applied: P05B-44 (Δt check covers the three s = 1 layouts), P05B-48 (2.5 m memory figures stated with patches, bins and decimal GB), P05B-50 (Δt/ℓ separation credited to `ell.dt_check`, not to Eq. 4.32 alone). P05B-52/53 note the consequences: the per-bin early envelope stays unverified while (B) keeps B11 unpromoted, and the tail level keeps AX16's measured bias (up to +3.83 dB, BRAS −1.47 dB) until the switch lands. Status: applied, verified; vetoable by Maisara.

## Phase 05b session 2 phase file `docs/phases/phase-05b2.md` (2026-11-09; /fix-plan; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Created on Maisara's decision of 2026-11-09 (Q2 option (b): "Answer to q2: b. Make the dedicated phase's prompt extremely aware with the utmost level of detailed analysis of what and why."); AX35 accepted the same day ("W1: accept"). Plan-editor applied the orchestrator's draft, holding two test-number choices as open decisions (D-T1 case set, new D-T6 regression bound). Interrogator document audit round 1 (P05B2-01…34): SOUND WITH CORRECTIONS (majors P05B2-12 fallback memory rows, P05B2-23 D-T3 yardstick wrong, P05B2-28 wrong example room); advocate round 1: no NO, REDIRECTs on §0.1 framing (extreme cases, empty venues, jnd by extension), D-T3, D-T6 (uniform vs mixed α), decision order (D-T5 → D-T4 → D-T1 → D-T2 → D-T6 → D-T3), listening pack (real BRAS scene, open_field), split rule (atomicity, named split point). All applied (cbc8d36). Round 2: interrogator P05B2-35…56 SOUND (minor P05B2-37 "bounding" → "extreme cases", P05B2-38 fallback label: applied c89b0d4); advocate GO, one narrow REDIRECT (split branch: Phase 08 waits for 05h; nightly before the PR): applied c89b0d4. No acoustic or numeric value decided: D-T1…D-T6 are open decisions for session 2's decision loop.

| id | item | verdict | status |
|---|---|---|---|
| P05B2-01…04, 06, 07, 09, 11, 13, 15, 17, 18, 25, 26, 32 | §0 numbers (ΔL_b,tr table, hybrid vs tracer, t_mix,e, patch counts, kernel sizes, convergence, BRAS ΔL_b, 26/345, +122.6 MB), model description, AX16 mechanism and sign, D-T5 code claims | CORRECT | — |
| P05B2-05, 10, 14, 16, 19, 20, 21, 22, 24, 27, 29, 30, 31 | AX16 exactness per order, jnd of G, time ∝ N²TG, Δt scope, Gilbert/Fujiwara attribution, D-T1 (b)–(e) feasibility notes, per-patch directions, validation scope, Table 15.1 | IMPRECISE → restated | applied (cbc8d36) |
| P05B2-12 | memory table without the AX22 fallback | CONDITIONS VIOLATED → fallback rows added | applied |
| P05B2-23 | D-T3 used Phase 10's mid-fade gate as yardstick | WRONG → listener level step vs 1 dB jnd per room class | applied |
| P05B2-28 | D-T6 example room | INCONSISTENT → six Phase 04 rooms named | applied |
| P05B2-33, 34 | consequences (AX21 step stays; listening scenes) | noted | — |
| P05B2-35…56 | round-2 changed passages | CORRECT (37, 38 IMPRECISE minor → applied) | applied (c89b0d4) |

Renumbering (2026-11-09, merge of main, commit 7e7f506): the AX35 of this block and of the block 'Phase 05b: patch size at a compute limit' is BUILD_PLAN **AX36**; main's AX35 is the hrtfId rule.

## docs/phases/phase-05g.md L17, L68; docs/phases/phase-06b.md L60 — board loop wording replaces the advocate (2026-11-09; /fix-plan; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Session brief `docs/sessions/2026-11-09-board-agents.md` (O6). Plan-editor: three SPECIFIED wording fixes, no DECISIONS NEEDED (commits c8f7c2d, 871959f). Interrogator document mode on the changed passages: **no FACT or NUMBER changed**; no blocker, no major.

| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| 05G-W1 | SOFTWARE | phase-05g L16–18: area-tolerance item raised to Maisara only if the `/fix-plan` loop (interrogator → decider over the board's seats, step 3) finds it needs her | listed, not rated | process wording; matches `.claude/commands/fix-plan.md` step 3 | none | — | resolved |
| 05G-W2 | SOFTWARE | phase-05g L67–69: the tolerance decision belongs to the `/fix-plan` step 3 loop | listed, not rated | same | none | — | resolved |
| 05G-D1 | DECISION | phase-05g L64–72: whether to tighten the area tolerance is deferred to the loop; no value proposed | CONSEQUENCE | procedural only; `bras_mapping.md` §2 value stands until decided | minor | — | resolved (unchanged by the edit) |
| 06B-W1 | SOFTWARE | phase-06b L60: if AX31 is vetoed, "a new decision loop (decider over the board's seats → interrogator, through `/fix-plan`) picks the replacement" | listed, not rated | process wording; names fix-plan step 3c–3d | none | Q1 | resolved |
| 06B-D1 | DECISION | phase-06b L58–62: AX31 confirmed → no code change; vetoed → replacement by the loop | CONSEQUENCE | the crossfade's acoustic content is not restated in the changed lines | minor | — | resolved (unchanged by the edit) |

**Builder's answers.** Q1 (arrow order): all three clauses name the whole of `/fix-plan` step 3 (document-mode interrogation of the options, then convening, seats, decision, decision-mode interrogation); the arrow order is shorthand and immaterial; phase-06b L60 does not skip the document-mode pass. Q2 (phase-06b L15, L36 still say "decider, interrogator, advocate"): intentional; they record the loop as it was run on 2026-11-07, when an advocate agent existed (`docs/review/phase-06b/advocate-round1.md`, `advocate-round2.md`). Historical records are not rewritten.

## Phase 08 generic HRTF dataset — board decision D1 (2026-11-09; the nine-seat board's first run, then applied via /fix-plan; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Session brief `docs/sessions/2026-11-09-board-agents.md` (O8, O10). Full records under `docs/review/board-smoke/hrtf-head/` (index and outcome: `docs/review/board-smoke/README.md`).

**Decision loop.** Decider convening round (`1-decider-convene.md`): nine-row table, all nine seats convened (three narrowly), researcher questions R1–R10, knowledge inventory K1–K16 → **CONVENE**. Seats 1–9 (`2-seat*.md`): nine positions in the protocol's format, none `NOT MY MATTER`; researcher dossier (`3-researcher-dossier.md`): F1–F37 (SADIE II Apache 2.0, read on the York page and the Zenodo record; MIT KEMAR permissive with citation; TH Köln CC BY-SA 3.0 in the paper vs CC BY 3.0 on Zenodo, C1 unresolved; BRAS BRIRs are FABIAN; no KU100-vs-KEMAR localisation study found), readiness NOT READY for option (d), READY for (a)–(c). Decider decision round (`4-decider-decision.md`): tension map (options × nine seats, now/later from the seats' own ratings), ordering (bounds drop (d) on the unclear-licence stop; no veto-grade survivor; worst-off tie at 2; composed variant (a′) max 1 / sum 16 against (a) 20, (b) 25, (c) 30), future-debt register, challenges C-1 (AC 3 names no estimator) and C-2 (scope 1/3 wording). Interrogator decision mode round 1 (`5-…`): **SURVIVES WITH CORRECTIONS** (convening PASS, map faithful, nine restatements, Q1–Q5). Decider rebuttal (`6-…`): stands, wording revised (Voronoi-weighted DF averages, always-apply rule with pin-time source-state check, S4 open debt, S5 undo window, Seat 9 head-id logging). Interrogator round 2 (`7-…`): **SURVIVES WITH CORRECTIONS, no questions remain** (three wording restatements). **Accepted by Maisara 2026-11-09 ("accepted")**, together with the board design assumptions A1, A2 and choices D2–D5 of the session brief.

**Applied (fix-plan steps 4–6).** Plan-editor applied the decision to `docs/phases/phase-08.md` (scope 1–3, 5, 7, AC 2/AC 3, new ACs "DF-EQ identity" and "Validation-only override", listening checklist, Risks, DoD), `docs/BUILD_PLAN.md` (§1 "Generic HRTF" row; **AX35** added: data behind a released `hrtfId` is never replaced, a different set is `generic-v2` with the old data retained; §5 **B14** Headphone compensation, open debt, no scheduled phase; §6 rows) and `docs/THIRD_PARTY.md` (planned HRTF line). Interrogator document-mode check 1 (`9-interrogator-plan-diff-check-1.md`): one **major INCONSISTENT** P08D-1 (AC 2's −60 dB reference was the un-equalised resampled source while scope 3 made the converter's DF-EQ always applied: a 1 dB residual reads −18.3 dB, not −60 dB), five minor IMPRECISE (P08D-3 bound arithmetic, -6 "cross-correlation", -15 power vs dB average, -21 "above", -22 "same output"). Decider round 3 (`10-decider-round3.md`): withdrew its own AC 2 reference sentence; AC 2 redefined as a two-term storage/decoding round-trip against a reference built from the header's parameters (storage term trimmed identically, total term untrimmed; both −60 dB); embed bound restated float32 ≤ ~2700 or float16 ≤ ~3000 directions (11 784 / 5 892 B per direction); DF-EQ averages stated as power averages; AC 3 window stated to presuppose an onset estimator; "same either way" → state, not signal; checklist "above" restated. Applied by the plan-editor (second §6 row). Interrogator check 2 (`12-interrogator-plan-diff-check-2.md`): **P08D-1 resolved, all check-1 minors resolved, no questions**; two new minors applied by the plan-editor (P08D2-5 units in the AC 3 path-difference line; P08D2-8 basis of "expected near zero"), one minor CONSEQUENCE (P08D2-10: both AC 2 terms gated).

| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| D1 | DECISION | `generic-v1` = SADIE II subject D1 (KU100), Zenodo 10.5281/zenodo.12092466 V2-2, Apache 2.0; composed variant (a′) | interrogator decision mode SURVIVES WITH CORRECTIONS ×2, no questions remain | `4-`, `5-`, `6-`, `7-decider/interrogator` files | — | — | accepted by Maisara 2026-11-09; applied |
| P08D-1 | NUMBER/FACT | AC 2 reference vs always-applied DF-EQ | INCONSISTENT → resolved by the two-term AC 2 | check 1 → decider round 3 → check 2 | major → none | Q1 | resolved |
| P08D-3 | NUMBER | ≤ ~3000 directions and/or float16 under ≤ ~32 MB | IMPRECISE → CORRECT (float32 ≤ ~2700 or float16 ≤ ~3000) | 3000 × 11 784 B = 35.4 MB | minor | Q3 | resolved |
| P08D-6 | FACT | "low-frequency/cross-correlation ITD exceeds an onset ITD" | IMPRECISE → CORRECT (LF ≈ 750 µs vs onset ≈ 650 µs; Roginska & Geluso Ch. 1; Blauert Ch. 2 §2.2.2) | corpus lines cited in check 2 | minor | Q4 | resolved |
| P08D-15 | FACT | averaged quantity unstated | IMPRECISE → CORRECT (power average; Begault Ch. 4; Vorländer §16.1.1) | check 2 | minor | Q2 | resolved |
| P08D-21 | FACT | "heard inside or above" | IMPRECISE → CORRECT (inside / reversed / median-plane uncertainty; Begault Ch. 3; Vorländer §6.3.2) | check 2 | minor | — | resolved |
| P08D-22 | FACT | "converted output the same either way" | IMPRECISE → CORRECT (state, not signal; Blauert Ch. 4 §4.5.2) | check 2 | minor | Q5 | resolved |
| P08D2-5 | NUMBER | (D/2)(φ + sin φ) "= 0.656 ms" (units) | IMPRECISE → restated with /c | check 2; plan-editor | minor | — | resolved |
| P08D2-8 | FACT | "truncation term expected near zero" basis incomplete | IMPRECISE → restated (converter fade and filter spread) | check 2; plan-editor | minor | — | resolved |
| P08D2-10 | DECISION | both AC 2 terms gated at −60 dB | CONSEQUENCE | check 2 | minor | — | recorded |
| C-1 | DECISION | AC 3 window names no estimator | CONSEQUENCE → plan now states the window presupposes an onset estimator, criterion named by the loop before the first measurement; never widened to pass | decider; check 2 P08D-5 | minor | — | recorded (open for Phase 08 session 1) |
| C-2 | DECISION | scope 1 "48 kHz, in SOFA format"; scope 3 DF-EQ wording | applied as the R6 wording | plan diff | minor | — | resolved |

Open for Phase 08 session 1 (not blocking): N1 the TH Köln operative licence (re-entry condition only); N4 the onset ITD of the pinned file by the named criterion; the pin-time source-state check (±1 dB, 200 Hz–8 kHz) and the AC 2 truncation term, measured not assumed. Corpus candidates named by the researcher (Møller 1999; Armstrong 2018; Bernschütz 2013; Algazi 2001; BRAS documentation; MIT KEMAR hrtfdoc/FAQ) are Maisara's decision, subject to licence.


## Phase 05b session 2 — D-T1 (all parts), D-T2, D-T6: interrogator decision mode (2026-11-10)

Source: `docs/review/phase-05b2/26-interrogator-T1-T2-T6.md` (on decider rounds 21 and 25). Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

| id | item | verdict | status |
|---|---|---|---|
| P05B2-T1T2T6-01 | D-T1/D-T2 convening: 9/9 convened, every seat rated both rounds | faithful | closed |
| P05B2-T1T2T6-02 | Round-1 and round-2 tension cells (all ids) against seats' words, except rows 14, 15 | faithful | closed |
| P05B2-T1T2T6-03 | D1-L2, D1-L3, D1-L4 (C3, C7, 19 §2/§6) | CORRECT | closed |
| P05B2-T1T2T6-04 | D-T1.1 "injection s(1−α) per Eq. 4.24"; "AQ3" for band-independent s | IMPRECISE (§5.2/§2.7; AX17) | open |
| P05B2-T1T2T6-05 | D-T1.1 "max 1" holds only under Q1 (a) (S4, S6 cells); S3 resolution unmarked †; register "BRAS nightly" repays a published-validation debt | IMPRECISE | open |
| P05B2-T1T2T6-06 | D-T1.2 S-1 | SURVIVES | closed |
| P05B2-T1T2T6-07 | D-T1.4 D4-L1 (Table 6.1), D4-L3 (gate B δ 0.25 jnd) | CORRECT | closed |
| P05B2-T1T2T6-08 | D-T1.4 D4-L2 "τ = 1 dB cannot detect AX16" | IMPRECISE (true only where \|ΔL\| ≤ 0.43 dB) | open |
| P05B2-T1T2T6-09 | D-T1.4 register stale against W_max (A); shipped 0.083 dB not reached where capped; S7 Tol-2 reason rests on B6-2 | IMPRECISE | open |
| P05B2-T1T2T6-10 | D-T1.5 CS-1 row S3, S6 should be 1/3 ("+1 later without NW") | TENSION MISREAD (non-winning row; winner unchanged) | open |
| P05B2-T1T2T6-11 | D-T1.5 case count 50 vs 64 (z_FW, family false-fail) | INCONSISTENT | open |
| P05B2-T1T2T6-12 | D5-L1, D5-L3 | CORRECT | closed |
| P05B2-T1T2T6-13 | D16-L1, L2, L3, L5, L6, L7 (C12, C13, 19; blend cap algebra) | CORRECT | closed |
| P05B2-T1T2T6-14 | D-T1.6 AX row "within λ/2 of a surface … pressure rise (Eq. 2.50)" | CONDITIONS VIOLATED (rigid wall, R = 1) | open |
| P05B2-T1T2T6-15 | D-T1.6 note qualifier "pilot SE > target/3" read as Seat 6's | defensible but amended condition; needs Seat 6 confirmation; conflicts with S2 C5 and S8 (ii) | open |
| P05B2-T1T2T6-16 | D-T1.6 both-near threshold 0.70 m equals `dead_booth` default d_L | open risk (knife-edge) | open |
| P05B2-T1T2T6-17 | D-T1.6 register lacks UI-phase row ("approximate" note); no /fix-plan list in round 2 | debt not registered | open |
| P05B2-T1T2T6-18 | C13 §2 table/reading mismatch | resolved (C13 corrected; decider cited the table) | closed |
| P05B2-T1T2T6-19 | D-T1.3 calibration block unbounded; pilot ≤ W_max/2 and N ≥ n\* violated in C13 layout-4 corners; cap not a bound for e_cal > W_max/256 | INCONSISTENT / CONDITIONS VIOLATED | open |
| P05B2-T1T2T6-20 | D-T1.3 S2 † cell (C1 replaced by pre-sampling rule; C5 unmet) | TENSION MISREAD | open |
| P05B2-T1T2T6-21 | D-T1.3 N_cap per-emitter vs joint accounting | INCONSISTENT (ambiguous; up to ~2× restore budget) | open |
| P05B2-T1T2T6-22 | D-T1.3 working: N-3 (round 1, sum 17) set aside as the unspecified parent of N-3W\*\* | accepted (reasoning exposed; not a §5 step) | closed |
| P05B2-T1T2T6-23 | W_max = 3.05 M arithmetic; D7 | CORRECT | closed |
| P05B2-T1T2T6-24 | Q2 (A) "six Phase 04 rooms no cap hits" at 3.05 M | NOT CHECKABLE (measured only at 14.6 M) | open (compute) |
| P05B2-T1T2T6-25 | Q2 (B) restore "≈ 2.6 s" | IMPRECISE (2.7 s at n\*_max ≈ 1 020; ≈ 4.8 s at 8 000; watchdog exceeded either way) | open |
| P05B2-T1T2T6-26 | Q2 AQ10 quotation; n\*_max not treated as an AQ10 matter | IMPRECISE / INCONSISTENT | open |
| P05B2-T1T2T6-27 | D-T2 ordering: both in-bounds options carry S5's 3; bias reading out of bounds; NEEDS MAISARA | CORRECT | closed |
| P05B2-T1T2T6-28 | D-T2 arithmetic 0.541, 0.430 %, 19.75×, 33× | CORRECT | closed |
| P05B2-T1T2T6-29 | Q1 (a) "today's precision"; hidden ℓ_ref premise in the < 1 % bias test; S4 no cell | IMPRECISE | open |
| P05B2-T1T2T6-30 | Q1 (b) omits ≈ 25–26× (family 1 %) and L2-F2 33×; "7× W_max" in old units (≈ 32× of W_max (A)); W1 figure is diffuse share only | IMPRECISE | open |
| P05B2-T1T2T6-31 | Round-1 attribution "Seats 4, 5, 6, 8 rated L2-F1 as keeping Tol-2 cost" (S4, S8 stated no cost premise) | IMPRECISE (superseded by round 2) | closed |
| P05B2-T1T2T6-32 | D-T6 convening: Seat 7 (public wording, "uniform rooms unchanged") not convened | UNDERCONVENED | open |
| P05B2-T1T2T6-33 | D-T6 small room is both-near under D-T1.6 (d_L 0.425, d_E 0.5 m) yet gated at τ | INCONSISTENT | open |
| P05B2-T1T2T6-34 | D-T6 gate N and stage-2 / no-reseed rule unstated (Seat 5 round 1) | IMPRECISE | open |
| P05B2-T1T2T6-35 | D-T6 cells, sums, D6-L1, D6-L2; W1 "before any number" (B6-1 is a relation) | CORRECT / faithful | closed |
| P05B2-T1T2T6-36 | Orchestrator computations (a)–(e) above | requested | open |


Round 2 (on decider round 3, `docs/review/phase-05b2/32-interrogator-round2-T1-T2-T6.md`, 2026-11-10):

| id | item | verdict | status |
|---|---|---|---|
| P05B2-T1T2T6-37 | Corrections 1, 3, 6, 9–14, 17, 18 applied | faithful | closed |
| P05B2-T1T2T6-38 | 70 cases / 560 case-bands, z_FW 4.290; D-T6 72 case-bands, z_FW 3.81; Q1 (b) table; Q2 (A)/(B) against C14 | CORRECT | closed |
| P05B2-T1T2T6-39 | Seat 7 D-T6 cells and conditions (i)–(iii) | faithful | closed |
| P05B2-T1T2T6-40 | C15: 16/16 rows pass Seat 2's pre-registered bounds | CORRECT | closed |
| P05B2-T1T2T6-41 | D-T1.3 map: S2 "?" should be 0/1 (condition met by C15); S4 1/1 (2/2 if n\*_max 8 000) | correction (not folded) | open |
| P05B2-T1T2T6-42 | Seat 4's CI list of pilot-estimate ships not in text or /fix-plan | correction | open |
| P05B2-T1T2T6-43 | D4 block size unpinned; Seat 5's confirmation not sought; overrun bound and 8 000-start disjointness depend on it | open premise (Seat 5 cell unconfirmed) | open |
| P05B2-T1T2T6-44 | "C15 re-run under joint rule" collides with file 31; per-emitter figures as an upper bound on cost are [Inferred] | correction | open |
| P05B2-T1T2T6-45 | "Old error +0.09 / −0.06 dB" at 100 m cubes (builder §3, within estimator SE 0.10–0.11 dB); "the one place the switch adds error"; low-α s = 1 cube omitted | NOT CHECKABLE (unresolved) | open (compute (g)) |
| P05B2-T1T2T6-46 | D-T1.4 "achieved SE lower than the target allows" (inverted); "target met wherever cap does not bind" false at n\*_max ≈ 1 020 (0.124 dB) | IMPRECISE | open |
| P05B2-T1T2T6-47 | D-T1.6 S6 shown 1/1, but Seat 6 rates U as written 2/1; its condition (i) not in the text | TENSION MISREAD (fold-in pending; winner unchanged) | open |
| P05B2-T1T2T6-48 | Seat 6 (ii) (presets: fix placement, not predicate) against the decider's reversal and phase-12 "reported"; (iii) unrecorded | correction | open |
| P05B2-T1T2T6-49 | "Where U fires" omits both-near placements in `club`, `living_room` and W1 at 0.1–0.5 m with good estimates; Seat 6's U′ example also fires under U | INCONSISTENT (with C13 §3) | open (compute (f)) |
| P05B2-T1T2T6-50 | AX text "no such rise next to an absorbing face" | IMPRECISE (R = 1 derivation; reduced for α < 1) | open |
| P05B2-T1T2T6-51 | Q1 (a) "ℓ_ref up to 0.37 % in the gated set" (W1 corner 0.63–0.65 %, CS-NW+) | WRONG | open |
| P05B2-T1T2T6-52 | Q1 (b) precision range omits L2-F2's 0.0145 dB | IMPRECISE | open |
| P05B2-T1T2T6-53 | /fix-plan list missing Seat 6 (i)/(ii), Seat 4's CI list, D4 block size, renamed re-run | correction | open |
| P05B2-T1T2T6-54 | D-T1.1, D-T1.2, D-T1.5, D-T6 round-3 verdicts | SURVIVES | closed |
| P05B2-T1T2T6-55 | D-T1.3, D-T1.4, D-T1.6, D-T2 (Q1), Q2 round-3 verdicts | SURVIVES WITH CORRECTIONS | open until applied |


Round 3, final (on decider round 4 and its addendum, `docs/review/phase-05b2/39-interrogator-round3-final-T1-T2-T6.md`, 2026-11-10):

| id | item | verdict | status |
|---|---|---|---|
| P05B2-T1T2T6-56 | Round-2 corrections 1–14 applied (map S2 0/1, S4 1/1 or 2/2; block 64; C16 as the joint re-run; AX16 resolved; D-T1.4 wording; S6 (i)–(iii); AX α text; ℓ_ref 0.65 %; precision range; /fix-plan) | faithful | closed |
| P05B2-T1T2T6-57 | S5-b: block 64 1/1, conditions (1)–(3) folded | faithful | closed |
| P05B2-T1T2T6-58 | S6-b: U 1/1 at 8 000; 1/1 at 1 024 with union VOV (C16b test met; C16c no change) | faithful | closed |
| P05B2-T1T2T6-59 | Block-64 overrun 0.153 W_scene; realised work ≤ 1.009 W_scene (joint, C16) | CORRECT | closed |
| P05B2-T1T2T6-60 | C16 (g) AX16 − long run (+0.02; +0.06/+0.10; +2.38/+2.39 dB) and the "adds random error" cost line | CORRECT | closed |
| P05B2-T1T2T6-61 | Q1 (a) "target met at 8 000" (uncapped both-near to 0.110 dB); "no seat above 1" (S4 no cell) | IMPRECISE: fix before Maisara | open |
| P05B2-T1T2T6-62 | Q2a (A) layout 4/5 SE "0.29–1.33" (is 0.17–1.33); low-α cube at both n\*_max | IMPRECISE: fix before Maisara | open |
| P05B2-T1T2T6-63 | Cap-hit definition: text "min binds → cap hit" vs C16 "N_need > N_cap" plus `floor_truncated` (68/134 runs); decides U at `dead_booth` listener-wall | INCONSISTENT: exact AX wording via /fix-plan | open |
| P05B2-T1T2T6-64 | D-T1.4 target statement qualifier | IMPRECISE (/fix-plan) | open |
| P05B2-T1T2T6-65 | Final "Where U fires" = addendum (C16b/C16c); main-text list superseded; W1 both_wall_0.3 silenced at 1 024 recorded in S1 debt | correction (/fix-plan) | open |
| P05B2-T1T2T6-66 | Seat 2's C15 check ran on the per-emitter rule; joint-rule cube replicates come with the C++ reported set | note (/fix-plan, §4) | open |
| P05B2-T1T2T6-67 | BRAS report prints MC SE (Seat 9) missing from /fix-plan | correction (/fix-plan) | open |
| P05B2-T1T2T6-68 | Final verdicts: D-T1.1, D-T1.2, D-T1.5, D-T6 SURVIVES; D-T1.3, D-T1.4, D-T1.6 SURVIVES WITH CORRECTIONS (/fix-plan); D-T2/Q1 and Q2 SURVIVES WITH CORRECTIONS (items 1–2 before Maisara) | – | open until applied |


## Phase 05b session 2 — D-T5 and D-T4: interrogator decision mode (2026-11-09)

Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. Rows copied from the interrogator's files (steward round 3 gap).

Round 1 (`docs/review/phase-05b2/8-interrogator-T5-T4-round1.md`):

| id | item | verdict | status |
|---|---|---|---|
| P05B2-T5T4-01 | D-T5.1 D5-L1 target_hybrid composition, 0.08 dB at 500 Hz–2 kHz | CORRECT | closed |
| P05B2-T5T4-02 | D-T5.1 D5-L2 AX16 vs hybrid 3.83 dB in all bands (C2) | CORRECT | closed |
| P05B2-T5T4-03 | D-T5.1 D5-L3 FP-mode split between paths (code) | CORRECT | closed |
| P05B2-T5T4-04 | D-T5.1 citation: Eq. 4.24 (Lambert) + §5.2 for the s(1−α) split | IMPRECISE | open |
| P05B2-T5T4-05 | D-T5.1 condition (i) "bit-identical on three OSes" → per platform; add Seat 5's RAII and denormal-producing test room | IMPRECISE | open |
| P05B2-T5T4-06 | D-T5.1 condition (ii) on band-independent-α layouts tests only air at 4–8 kHz; register "repaid when (ii) passes" overclaims (S1 63 Hz) | IMPRECISE | open |
| P05B2-T5T4-07 | D-T5.2 E10 k inflation ≤ 2× | CORRECT | closed |
| P05B2-T5T4-08 | D-T5.2 D5-L5 t_mix,e fixed before the solve | CORRECT | closed |
| P05B2-T5T4-09 | D-T5.2 debt evidence "Phase 13 i₀ re-derivation" cannot show a k_real over-trigger; per-seat rows (S6) | INCONSISTENT | open |
| P05B2-T5T4-10 | D-T5.3 ordering and map | CORRECT | closed |
| P05B2-T5T4-11 | D-T5.3 D5-L6 shares have no consumer | CORRECT | closed |
| P05B2-T5T4-12 | D-T5.3 D5-L7 F25 (external) | NOT CHECKABLE (not load-bearing) | closed |
| P05B2-T5T4-13 | D-T5.4 D5-L8 C1 levels, MC vs integral within SE, open boxes ≥ 90 dB | CORRECT | closed |
| P05B2-T5T4-14 | D-T5.4 inaudibility at C1 levels (Vorländer §1.5, Fig. 6.2; stated level conditions) | CORRECT with conditions | closed |
| P05B2-T5T4-15 | D-T5.4 D5-L9 Eyring premises | CORRECT | closed |
| P05B2-T5T4-16 | D-T5.4 Phase 12 single-scatter ground check applied to `courtyard` | CONDITIONS VIOLATED | open |
| P05B2-T5T4-17 | D-T5.4 reversal condition fires on courtyard's real reverberation | INCONSISTENT | open |
| P05B2-T5T4-18 | D-T5.4 log-domain check below the float32 normal range under FTZ (precision unstated) | NOT CHECKABLE (software), flagged | open |
| P05B2-T5T4-19 | C1 prose "−152 dB at 1 kHz" (table: −166 dB; −152 is 500 Hz) | INCONSISTENT (source typo; decider unaffected) | open |
| P05B2-T5T4-20 | D-T4a 4a-2G S6 (and S3 unmarked) cells carried without rating; invented register reasons | TENSION MISREAD | open |
| P05B2-T5T4-21 | D-T4a D4-L1/L2 kernel and history sizes, t_cap ≈ 2.1 s (Kuttruff Eq. 4.6) | CORRECT | closed |
| P05B2-T5T4-22 | D-T4a (ii) resident cap must read "additional" (baseline +122.6 MB) | IMPRECISE | open |
| P05B2-T5T4-23 | D-T4a "D-T4c measurements close K8–K10" | INCONSISTENT | open |
| P05B2-T5T4-24 | D-T4a register "Phase 13 multi-instance RSS" (does not exist; scope 3 records the CPU sum) | INCONSISTENT | open |
| P05B2-T5T4-25 | D-T4a working ceiling with K8–K10 declared unknown | legitimate (phase-05b2 §3, phase-13 L45–47); debt 128 MB × K10 + Bitwig to record | open |
| P05B2-T5T4-26 | D-T4b ordering | CORRECT | closed |
| P05B2-T5T4-27 | D-T4b "§9 puts a cache out of scope" (§9: beyond what D-T1 needs) | IMPRECISE | open |
| P05B2-T5T4-28 | D-T4c S2 re-run condition (gated build in the AX22 fallback) not carried | correction (winner unchanged) | open |
| P05B2-T5T4-29 | D-T4c contended-restore and bounce/real-time records (Seats 5 and 8) | to add | open |
| P05B2-T5T4-30 | D-T4c D4-L6 / Challenge 1 arithmetic (2.14 s; 1.51–1.88 s); AQ10 ruling | CORRECT | closed |
| P05B2-T5T4-31 | D-T4c Table 15.1 3 s row used for full rebuilds: state its conditions | IMPRECISE | open |
| P05B2-T5T4-32 | One composed variant per decision id; coupling 4a-2G ↔ 4b-2 ↔ 4c-1C to be recorded | accepted reading | closed |

Round 2 (`docs/review/phase-05b2/12-interrogator-T5-T4-round2.md`):

| id | item | verdict | status |
|---|---|---|---|
| P05B2-T5T4-33 | Corrections 04, 05, 06 (D-T5.1) applied | faithful | closed |
| P05B2-T5T4-34 | D-T5.1 corrected register: S1 63 Hz not repaid; band-varying α has no independent evidence | faithful | closed |
| P05B2-T5T4-35 | Correction 09 (D-T5.2): one row per seat in their words, "no scheduled evidence" | faithful | closed |
| P05B2-T5T4-36 | Corrections 16, 17, 18 (D-T5.4): two-branch Phase 12 check, ghost-tail reversal, double precision (1.19e−41 is a normal double) | CORRECT / faithful | closed |
| P05B2-T5T4-37 | D-T5.4 S6 1/1 on the restated check (re-run 3) | faithful | closed |
| P05B2-T5T4-38 | Correction 19: C1 typo fixed (L32) | fixed | closed |
| P05B2-T5T4-39 | D-T4a 4a-2G++ cells S1 0/1, S7 1/1, S9 1/1 (rated); S3, S4, S6 read from conditions; max 1, sum 17 | faithful | closed |
| P05B2-T5T4-40 | D-T4a S5 cell carried from 4a-2G; FIFO and coalescing terms and Seat 3's hand-off on non-realtime `processBlock` waiting at the gate never rated by Seat 5 | TENSION MISREAD (narrow) | open |
| P05B2-T5T4-41 | D-T4a: the late conditions of Seats 1, 7 and 9 must be written into the text (Seat 9's later is 2 without its conditions) | correction | open |
| P05B2-T5T4-42 | D-T4a (iv): "(position and room size)" dropped in round 3 (Seat 6's condition) | correction | open |
| P05B2-T5T4-43 | D-T4a register: S7 and S9 rows in their re-run words | correction | open |
| P05B2-T5T4-44 | D-T4a /fix-plan list: add the Phase 08 commitments (iv) binaural and (v) item 8 | correction | open |
| P05B2-T5T4-45 | D-T4a Seat 4 arithmetic (24.3 ms, 13.7 ms; Table 15.1 35 ms, "20 ms as printed") and Seat 7 (1.02 GB + 0.98 GB) | CORRECT | closed |
| P05B2-T5T4-46 | Corrections 22–25 (D-T4a): additional resident; K8–K10 closure claim struck; phase-13 multi-instance RSS proposed; 128 MB × K10 + Bitwig debt | faithful | closed |
| P05B2-T5T4-47 | Correction 27 and coupling note (D-T4b) | faithful | closed |
| P05B2-T5T4-48 | Corrections 28, 29, 31 (D-T4c): both 100 m builds, contended restore, bounce ratio, Table 15.1 conditions | faithful | closed |
| P05B2-T5T4-49 | D-T4c: record whether the closed low-α 100 m cube actually avoids the AX22 fallback | minor correction | open |
| P05B2-T5T4-50 | Challenge 1 (AQ10, 100 m restore gate) | NEEDS MAISARA | open |

Round 3 (final) (`docs/review/phase-05b2/15-interrogator-T5-T4-round3.md`):

| id | item | verdict | status |
|---|---|---|---|
| P05B2-T5T4-51 | Row 40 (S5 cell on 4a-2G++ and Seat 3's offline hand-off) answered by Seat 5 re-runs 2 and 3 | faithful | closed |
| P05B2-T5T4-52 | Row 41 (Seats 1, 7, 9 conditions) written into (i), (iii), (iv), (vi) | faithful | closed |
| P05B2-T5T4-53 | Row 42 "(position and room size)" restored | faithful | closed |
| P05B2-T5T4-54 | Row 43 S7 and S9 register rows in the seats' words | faithful | closed |
| P05B2-T5T4-55 | Row 44 Phase 08 (iv) and (v) on the /fix-plan list | faithful | closed |
| P05B2-T5T4-56 | Row 49 `ismFallback` recorded for both 100 m builds; uncovered horizon reported | faithful | closed |
| P05B2-T5T4-57 | D-T4a final map: S3 and S6 read from conditions, S4 and S5 rated; S1, S7, S9 rated on 4a-2G++; S2 and S8 carries accepted; max 1, sum 17 | faithful | closed |
| P05B2-T5T4-58 | Two-class and 4a-2G++ intermediate rows (S5 1/2; S3 and S6 1/2) | faithful | closed |
| P05B2-T5T4-59 | D-T4a synchronous class omits `reset()` (ResetStep3 can build: `ScenePipeline.cpp` L146, L159–164, L209–229) | correction (wording; no cell change) | open (plan-editor) |
| P05B2-T5T4-60 | D-T4a S4 cell now rated by Seat 4 re-run 2 (1/1); update the mark and the strongest objection | correction (wording) | open (plan-editor) |
| P05B2-T5T4-61 | Host threading of freeze/offline and of `reset()` [Hyp] (Seat 5 open check) | NOT CHECKABLE; not load-bearing; route to the researcher before implementing the gate's offline path | researched 2026-11-10 (`docs/review/phase-05h/12-researcher-T5T4-61.md`, NOT READY on the freeze/offline half): `reset()` may arrive on the VST3 processing thread (VST3 `setProcessing` spec; JUCE 8.0.17 wrapper maps `setProcessing(false)` to `reset()` and calls `setNonRealtime` from every process call), AU unspecified; the project's `reset()` / `setNonRealtime(true)` block in `quiesceBuilder()` and may build synchronously; no vendor documents the thread of a freeze or offline render (measurement needed). Treatment: phase-05h D-H3 item (e). Ordering miss recorded: the offline path was implemented (session 2) before this answer |
| P05B2-T5T4-62 | S8 carry: alternation can roughly double a live-session freeze; full-project bounce unaffected (builders quiesced); recorded in (iv) | observation | closed |
| P05B2-T5T4-63 | D-T4c additions (correction 49, UI-anchor label) | faithful | closed |
| P05B2-T5T4-64 | D-T4a final verdict | SURVIVES WITH CORRECTIONS (59, 60) | open until applied |
| P05B2-T5T4-65 | D-T4c final verdict | SURVIVES | closed |


## Phase 05b session 2 — Maisara's answers (2026-11-10)

Her words, verbatim: "I accept the board's answer by definition." This was in reply to the board's answers as stated to her:
accept all decisions; Challenge 1 yes; Q1 (a), the bias reading; Q2a (A) now and (C) in a later phase; Q2b (i), n\*_max 1 024.
Packet: `docs/review/phase-05b2/40-packet-for-Maisara.md`.

| id | item | outcome | status |
|---|---|---|---|
| P05B2-M-01 | D-T5.1–5.4, D-T4a–c (files 13, 15) | accepted | closed |
| P05B2-M-02 | D-T1.1–1.6, D-T6, D-T3 not needed (files 34, 37, 39) | accepted | closed |
| P05B2-M-03 | Challenge 1: 100 m, 96 kHz restore gate blocking (AQ10 amended) | yes | closed (apply via /fix-plan) |
| P05B2-M-04 | Q1 / D-T2: AX36 applies to the estimator's bias, checked in CI | (a) | closed (apply via /fix-plan) |
| P05B2-M-05 | Q2a: W_max sized to the restore watchdog (provisional 3.05 M per emitter); async restore (C) in a later phase | (A) + (C) later | closed (apply via /fix-plan) |
| P05B2-M-06 | Q2b: n\*_max = 1 024 (re-derived from C++, ≥ 1 000) | (i) | closed (apply via /fix-plan) |
| P05B2-M-07 | D-T3 "not needed" re-checked against the answers (steward round 3, second gap): holds under Q2a (A) | holds | closed |


## Phase 05b session 2 — /fix-plan diff check (2026-11-10)

Source: `docs/review/phase-05b2/41-interrogator-plan-diff-check.md` on `git diff 3973a5c 19cabdb`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

| id | item | verdict | status |
|---|---|---|---|
| P05B2-FX-01 | Item 3, cap-hit definition (AX41, AX44), word for word | CORRECT | closed |
| P05B2-FX-02 | Item 4, D-T1.4 qualifier and the 1 024 figures (AX42) | CORRECT | closed |
| P05B2-FX-03 | Item 5, final "Where U fires" list from C16b/C16c, main-text list superseded, W1 both_wall_0.3 debt (AX44) | CORRECT | closed |
| P05B2-FX-04 | Item 6, BRAS report MC SE (AX40, phase-05b2 §4) | CORRECT | closed |
| P05B2-FX-05 | Corrections 59 (`reset()`) and 60 (S4 rated) in AX38 | CORRECT | closed |
| P05B2-FX-06 | AX46 bias reading (ℓ_ref 0.65 %, SE ≈ 0.12 % ≈ 0.005 dB) | CORRECT | closed |
| P05B2-FX-07 | W_max 3.05 M / W_scene 6.10 M and n\*_max 1 024 with their re-derivation rules (AX41, AQ10, phase-05b2 §4, phase-13) | CORRECT | closed |
| P05B2-FX-08 | Blocking restore gate (14 × t_restore ≤ 30 s) against W_max sized to the same budget with zero margin and a realised-work ratio up to ≈ 1.05 (prototype 29.98 s; 30.2 s at 1.05) | INCONSISTENT: resolve before the gate is implemented (decider) | open |
| P05B2-FX-09 | AX41 cost line mixes n\*_max 8 000 and 1 024 figures | IMPRECISE | open |
| P05B2-FX-10 | Restore gate's scene(s) not named (AX38 4c, AQ10) | IMPRECISE | open |
| P05B2-FX-11 | B15 "flagged by note U" without U's conditions | IMPRECISE | open |
| P05B2-FX-12 | AX37 "within 0.08 dB" without its conditions | IMPRECISE | open |
| P05B2-FX-13 | AX36 (c) "R1 certified at 2.5 m" without band and position conditions | IMPRECISE | open |
| P05B2-FX-14 | AX16 C16 (g) values not marked 1 kHz | IMPRECISE | open |
| P05B2-FX-15 | AX38 (4b) "AQ10 is unchanged" against the AQ10 amendment | IMPRECISE | open |
| P05B2-FX-16 | Corpus claims in the changed passages (Kuttruff Eqs. 2.49–2.50, 4.24, 4.29, 4.35, §2.7, §5.2, §8.7; Vorländer Table 6.1) | CORRECT ("absent at α = 1" derived from Eq. 2.49's R = 1 premise) | closed |
| P05B2-FX-17 | No contradiction of a settled decision (AX22, phase-05b scope 0, NFR-8, Maisara's answers M-01…07) | CORRECT | closed |


Round 2 of the diff check (`docs/review/phase-05b2/42-interrogator-plan-diff-check-round2.md`, 2026-11-10). P05B2-FX-22 closed by the orchestrator: row 05b set back to `in progress` until the phase-05b PR's CI is green; duplicated sentence removed.

| id | item | verdict | status |
|---|---|---|---|
| P05B2-FX-18 | File-41 corrections 2–8 applied as worded (AX41, AQ10/AX38 4c scenes, B15, AX37, AX36 (c)/B11/phase-05b, AX16, AX38 4b, AX44 derived note) | CORRECT | closed |
| P05B2-FX-19 | D-H1 (phase-05h §3) and its pointers in AQ10, AX38 4c, AX41 faithful to correction 1 | CORRECT | closed (P05B2-FX-08 stays open until D-H1 is decided) |
| P05B2-FX-20 | phase-05h faithful to phase-05b2 §4–§10 and AX37–AX46; atomicity and nightly-green-before-PR kept | CORRECT | closed |
| P05B2-FX-21 | Split bookkeeping: row 05h, §4 entry, phase-08/-13 dependencies with the AX37 (5.3) exception, phase-05b2 header note | CORRECT | closed |
| P05B2-FX-22 | §0 row 05b `done` set without PR link, CI evidence or done date (CLAUDE.md step 6); duplicated session-2 sentence | CONDITIONS VIOLATED (bookkeeping) | open (orchestrator) |
| P05B2-FX-23 | phase-05h §2 item 2 "conditional" escalation, against AX38 4c's unconditional escalation | IMPRECISE | open (/fix-plan) |
| P05B2-FX-24 | phase-05h §4 item 10 re-listening clause not in AX37 (5.3) | IMPRECISE (addition) | open (/fix-plan) |


## Phase 05b session 2 — board answers to Challenge 1, Q2a, Q2b (2026-11-10)

Decider files 43 and 47; ratings 45-seat*-R1-R3; confirmations 48-*; interrogator `docs/review/phase-05b2/49-interrogator-board-answers-C1-Q2.md`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

| id | item | verdict | status |
|---|---|---|---|
| P05B2-C1Q2-01 | 43 Q2b = (i) n\*_max 1 024: cells, sums 19/21, preference handling | SURVIVES | closed |
| P05B2-C1Q2-02 | 43: Challenge 1 / Q2a not decidable on recorded cells; 4c-2 cells not reused | correct process | closed |
| P05B2-C1Q2-03 | R1–R3 convening (9/9) and per-question cells in 47 §2 | faithful | closed |
| P05B2-C1Q2-04 | J5 dropped (bounds, S5 later 3); offline-only (B) not composed | CORRECT | closed |
| P05B2-C1Q2-05 | S3-c (A) 1/1 and S4-c 0/1 folded: J1 19, J2 20 | correction | open |
| P05B2-C1Q2-06 | S1 J1 cell: own composite 1/1 vs (A)-with-(C) 2/1; worse taken against the stated rule | IMPRECISE (state, or ask Seat 1) | open |
| P05B2-C1Q2-07 | S8 J1 cell rests on "U reaches the producer in capped halls"; U silent in capped 100 m cubes (SE ≤ 0.15 dB) | TENSION MISREAD (unmarked †; winner unchanged) | open |
| P05B2-C1Q2-08 | J2 S7 cell read from conditions not in J2 (should be 1/2; J2 21) | TENSION MISREAD (winner unchanged; prevents a tie) | open |
| P05B2-C1Q2-09 | L1, L2, L4, L6 | CORRECT | closed |
| P05B2-C1Q2-10 | L3 stale figures (0.29–1.33 → 0.13–1.33; low-α 0.44–0.50 at 1 024) | IMPRECISE | open |
| P05B2-C1Q2-11 | L5 / For Maisara: "capped class = synthetic s = 1 layouts"; "realistic halls not affected" (100 m cubes capped, SE 0.09–0.15 dB; C18 is four 20 × 30 × 10 m rooms) | INCONSISTENT: fix before the record goes forward | open |
| P05B2-C1Q2-12 | Seat 5's margin arithmetic (≈ 22 % + 5 %) already above Seat 3's 20 % trigger; not registered | debt not registered: fix before the record goes forward | open |
| P05B2-C1Q2-13 | §5 plan list gaps (Seat 6 (a) escalation; (C) forward on any gate failure; research questions of Seats 5 and 7; Seat 1's step-size ruling; phase-10 cross-reference) | correction (/fix-plan) | open |
| P05B2-C1Q2-14 | 47 final verdict: J1 (Challenge 1 yes, Q2a (A) now, (C) scheduled before the first public release) | SURVIVES WITH CORRECTIONS (winner unchanged under every reading) | open until applied |


J1 plan-edit diff check (`docs/review/phase-05b2/52-interrogator-J1-plan-diff-check.md`, 2026-11-10):

| id | item | verdict | status |
|---|---|---|---|
| P05B2-J1FX-01 | AQ10 / AX38 4c J1 conditions (47 §4 (i), 51 §4 item 1, correction 8 (a)/(b)) | CORRECT | closed |
| P05B2-J1FX-02 | AX41 W_max basis and n\*_max as board answers; G1 closed | CORRECT | closed |
| P05B2-J1FX-03 | phase-05h §1, §3 D-H1 (margin rule, 20 % trigger, ≈ 27 %, +17 % SE), §4 seam, §5, §9 | CORRECT | closed |
| P05B2-J1FX-04 | phase-08 scope 10 / AC; phase-11 note to editor; phase-12 re-run under 07c's W_max | CORRECT | closed |
| P05B2-J1FX-05 | phase-07c faithful to 47 §4 (iii) 1–8 and 51 §4 items 4, 9; size M; labels D-C1–D-C3 | CORRECT | closed |
| P05B2-J1FX-06 | "W_max below Seat 1's floor at a gated scene → Maisara" already true at (A) (gated cubes VOV 0.47–0.59, C16) | INCONSISTENT: decider defines the trigger before the gate is implemented | open |
| P05B2-J1FX-07 | phase-12 "hall preset in the capped class reopens J1" against 51 §2 (100 m rooms capped at SE ≤ 0.15 dB) | INCONSISTENT: decider confirms the restatement | open |
| P05B2-J1FX-08 | phase-05h §2 item 1 lists one trigger, §3 another | IMPRECISE (/fix-plan) | open |
| P05B2-J1FX-09 | phase-13 hard dependency on 07c against its versioning fallback | INCONSISTENT (/fix-plan) | open |
| P05B2-J1FX-10 | phase-07c §6 unconditional Phase 12 re-run | CONDITIONS VIOLATED (/fix-plan) | open |
| P05B2-J1FX-11 | phase-07c §4 "researcher questions before D-C1–D-C3" (plan-editor ordering) | IMPRECISE (/fix-plan) | open |
| P05B2-J1FX-12 | phase-10 lacks the pointer to 07c; AQ10 stray punctuation | IMPRECISE (/fix-plan) | open |

J1FX-06 and J1FX-07 closed on decider file 53 (`docs/review/phase-05b2/53-decider-J1-trigger-definitions.md`). The first trigger is Seat 1's floor counted with clauses (a)–(d), with the starting state recorded and escalated once. The second is the phase-12 reopening, which applies only after the placement fix fails; capped presets at SE ≤ 0.33 dB are reported only. Items J1FX-08 to -12 are applied by the plan-editor (2026-11-10).


Round 2 of the J1 diff check and decision mode on file 53 (`docs/review/phase-05b2/54-interrogator-J1-triggers-round2.md`, 2026-11-10):

| id | item | verdict | status |
|---|---|---|---|
| P05B2-J1FX-13 | Trigger 1 copied word for word into AQ10, AX38 4c, phase-05h §3; phase-05h §2 lists both triggers | CORRECT | closed |
| P05B2-J1FX-14 | Trigger 2 copied word for word into phase-12; AX41 cross-reference | CORRECT | closed |
| P05B2-J1FX-15 | 52 items 4–7 applied (phase-13 / 07c dependency with versioning fallback; 07c §6 conditional; 07c §4 ordering note; phase-10 pointer; AQ10 punctuation) | CORRECT | closed (closes J1FX-08…12) |
| P05B2-J1FX-16 | File 53 Trigger 2 against Seats 9, 6 and 8 | SURVIVES | closed (closes J1FX-07) |
| P05B2-J1FX-17 | File 53 Trigger 1: quotes faithful; flutter cube met via (a); closed s = 0.3 cubes met via (d) (C15 p95 ≤ 0.28 dB, per-emitter rule) | SURVIVES WITH CORRECTIONS | open |
| P05B2-J1FX-18 | Gated closed low-α cube's s not pinned; at s = 1 SE 0.44–0.50 dB fails the floor on day one | IMPRECISE (premise): pin in AX38 4c | open |
| P05B2-J1FX-19 | Clause (d) applied to the gated cubes beyond Seat 1's stated scope (layout 5 under (B)); Seat 1's D-T1.3 2/2 counts the cubes' VOV as a failure | needs Seat 1 confirmation | open |
| P05B2-J1FX-20 | "Any further rise" without tolerance; "every reasonable placement" undefined | IMPRECISE | open |

J1FX-19 closed: Seat 1 accepts clause (d) at the gated closed 100 m cubes at s = 0.3 (`docs/review/phase-05b2/55-seat1-confirm-clause-d.md`). Its two conditions are that the replicates run the shipping rule as built, on disjoint, pre-registered streams, and that the check is repeated on the C++ build. "The VOV part in the closed cubes" comes off its D-T1.3 failing list. Its 2/2 under (A) stands on layouts 4/5 at s = 1 and the low-α s = 1 cube.

Closure notes from steward round 5 (2026-11-10):
- P05B2-C1Q2-05…08 and 10…13 are closed. Each is applied in decider file 51 (`51-decider-addendum-J1.md`) and in the plan, commits bf3f5bd and 346ae07.
- P05B2-C1Q2-14 is closed. J1 survives with its corrections applied (files 51, 53, 54).
- P05B2-J1FX-17 is closed, with Trigger 1's clause (d) accepted by Seat 1 (file 55).
- P05B2-J1FX-18 and P05B2-J1FX-20 are carried to phase-05h §3 D-H1 (OPEN premises), AX38 4c and phase-12 ("Hall presets and J1", OPEN), commit 1aa4c4e.


Branch-review fixes diff check (`docs/review/phase-05b2/56-interrogator-branch-review-fixes.md`, 2026-11-10):

| id | item | verdict | status |
|---|---|---|---|
| P05B2-BR-01 | AX16 decided / implemented in 05h / shipped level still AX16 until 05h `done`; breaks column gains 05h (major 1) | CORRECT | closed |
| P05B2-BR-02 | report-phase05b session-2 outcome line and generator `SESSION2`; session-1 line marked (major 2) | CORRECT | closed |
| P05B2-BR-03 | phase-08 scopes 9/10 and criteria conditional on 05h; carried by phase-05h scope 10 and its new §5 criterion (major 4) | CORRECT | closed |
| P05B2-BR-04 | phase-07c §3: comes forward only after 05h; heaviest-mode gate in phase-05h scope 10 if 08 went first | CORRECT | closed |
| P05B2-BR-05 | J1 freeze-point rule (AQ10, AX38 4c) unqualified for the 08-first order; 05h scope 10 states only the SE-tolerance branch | IMPRECISE: /fix-plan, Seat 4 / decider to confirm | open |
| P05B2-BR-06 | phase-05b2 §9 note (minor 4); §6 CLAUDE.md determinism row (minor 1) | CORRECT | closed |

P05B2-BR-05 closed: freeze rule qualified for both orders in AQ10, AX38 4c and phase-05h scope 10 (Seat 4 confirmed, file 57).

## phase-05h (session 2) — D-H1, D-H2 and the answers for Maisara: board decision loop (2026-11-10)

Question `docs/review/phase-05h/3-orchestrator-D-H1-D-H2-question.md`; convening `4-decider-convene-D-H1-D-H2.md` (9/9 seats for D-H1; Seat 6 not required for D-H2, "NOT MY MATTER"); seats `5-seat1…5-seat9-D-H1-D-H2.md` (Seat 6: `5-seat6-D-H1.md`); researcher `5-researcher-RQ-H1-H2.md`; decider `8-decider-decision-D-H1-D-H2.md` (round 1) and `19-decider-decision-D-H1-D-H2-r2.md` (round 2); interrogator `15-interrogator-D-H1-D-H2.md` (round 1) and `21-interrogator-D-H1-D-H2-r2.md` (round 2: file 19 stands, six exact restatements applied by the plan-editor); Seat 5's R-e cell `17-seat5-D-H3.md` L151–158; data files 1, 7, 10. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. Applied to AX38 4c, AQ10 amended (1), AX41, AX43, AX45, AX46, phase-05h §2 item 1 / §3 / §5, phase-07c §0 / §3 / §5 (conditions 7, 9) / §6 / §9, phase-08 scope 10 (/fix-plan, plan-editor, 2026-11-10). D-H3 (AX37 (5.1) (i), AX44, the AX43 pooled clause, AX38 (i)) is a separate round and is not in this block.

| id | decision | convening | seats | researcher | decider | interrogator | outcome | status |
|---|---|---|---|---|---|---|---|---|
| P05H-D-H1-i | D-H1 (i) P-a′: the gated closed low-α cube pinned as `cube100_lowalpha0.05_s0.3` (α 0.05, s 0.3, `ismFallback` false asserted); the s = 1 cube reported with a p95 > 1 dB escalation line; buildable by a user → AX44's U; file-10 starting state recorded (gated cube met via (d), s = 1 cube not met) | file 4 | 5-seat1…9 (max 1, sum 9) | 5-researcher | files 8, 19 | files 15, 21 | SURVIVES | applied (AX38 4c; phase-05h §3) |
| P05H-D-H1-ii | D-H1 (ii) R-e: the starting state is the file-10 record (no golden, no assertion); rises of SE ≥ 0.05 dB or p95 ≥ 0.10 dB recorded in the margin report; the 0.33 dB / 1 dB crossings escalate; constants in the test re-pinned with a CHANGELOG reason at every W_max / n\*_max re-derivation (Seat 5 file 17 L155–158, cell 0 / 1 own) | file 4 | 5-seat1…9, Seat 5 file 17 (max 1, sum 6) | 5-researcher | files 8, 19 | files 15, 21 (SURVIVES WITH CORRECTIONS: restatements 1–4, applied) | SURVIVES | applied (AX38 4c, AQ10, AX41; phase-05h §3) |
| P05H-D-H1-iii | D-H1 (iii) Q-d: realised work / W_scene ≤ 1.02 at each gated scene, pre-registered from the C++ measurements (0.935 / 0.991 / 0.986), not changed afterwards; W_pilot / W_final exact in the D5 golden | file 4 | 5-seat1…9 (max 1, sum 1) | 5-researcher | files 8, 19 | files 15, 21 | SURVIVES | applied (AX41; phase-05h §3, §5) |
| P05H-D-H1-iv | D-H1 (iv): W_max 3.05 M per emitter and n\*_max 1 024 pinned as cross-platform constants (the (A) formula gives no W_max ≥ 0 on macOS; W1 diffuse share ≤ 25 ms); re-derived once under (C), phase-07c condition 3, only after the AX38 4c 3-minute bounce record is in 07c's packet (Seat 8) | file 4 | 5-seat1…9 (W max 2 / sum 17; N-a max 1 / sum 3) | 5-researcher | files 8, 19 | files 15, 21 | SURVIVES | applied (AX41, AQ10; phase-07c §3, §9) |
| P05H-D-H1-v | D-H1 (v) W-x′: the restore gate on all three OSes, strict where the recorded value at the pinned W_max is ≤ 29.1 s, a registered defect with the growth bound (median-of-10 ≤ 1.10 × recorded median) elsewhere; (c) unexpected pass, (d) new failure a defect; register Linux cube 30.27 s (closes 07c), macOS cube 33.40 s (closes 07c condition 9 / 07d or Phase 13); the named finding (unit-decay synthesis 95.5 % of the non-diffuse build) and its remedy, phase-07c §5 condition 9; 07c next after 05h | file 4 | 5-seat1…9 (max 2, sum 17; W-c whole 23 per restatement 6) | 5-researcher | files 8, 19 | files 15, 21 (SURVIVES WITH CORRECTIONS: restatement 6, applied) | SURVIVES | applied (AX38 4c, AQ10; phase-05h §5 "Blocking"; phase-07c §5 conditions 7, 9, §6, §9; phase-08 scope 10) |
| P05H-H1-F1 | H1-F1 (for Maisara): 14 × t_restore ≤ 30 s, i.e. ≤ 2.143 s per synchronous restore, stands as the project's own convention, not pluginval's requirement (watchdog resets per restore); 14 a kept constant; the Catch2 restore test is the evidence. PRD L101, NFR-1, NFR-2, NFR-6. `AMENDS her decision of 2026-11-10` | file 4 | — | 5-researcher F1–F6, F13, F14 | file 19 | file 21 (P05H-20 CORRECT) | SURVIVES; decided for Maisara, open to her veto | applied (AQ10, AX38 4c; phase-07c §0) |
| P05H-H1-F2 | H1-F2 (for Maisara): the restore block as a strict check with a plan-text defect register, the 29.1 s OS rule, the remedy ladder extended to the unit-decay synthesis (phase-07c §5 condition 9 / 07d); strict on all three OSes at Phase 13. PRD L101, NFR-1, NFR-2, NFR-6, NFR-8, FR-SIM-6, L20, L55. `AMENDS her decision of 2026-11-10` | file 4 | — | 5-researcher | file 19 | file 21 (P05H-21, -22, -23 CORRECT) | SURVIVES; decided for Maisara, open to her veto | applied (AX38 4c, AQ10; phase-05h §5; phase-07c §0, §5, §9; phase-08 scope 10) |
| P05H-H1-F3 | H1-F3 (for Maisara): Raise item 1 does not fire at the pinned W_max; the s = 1 cube's starting-state floor failure (SE 0.381 / 0.384 dB, p95 0.701 / 0.810 dB) recorded once beside item 1 as a finding of the reported set, buildable by a user (FR-3D-4, AQ3, AX6), AX44's U; item 1 fires later only on (ii)'s lines. NFR-1, L49. reasoning line 3 not reproduced in the plan; restatement 5 stands against file 19's text. No AMENDS (reads AX38 4c's scope) | file 4 | — | — | file 19 | file 21 (P05H-24 CORRECT with restatement 5) | SURVIVES; decided for Maisara, open to her veto | applied (phase-05h §2 item 1, §3; AX38 4c starting state) |
| P05H-D-H2-a | D-H2 (a) G-a: a case-band is gated when the agreement golden holds a two-rung reference with the finer-rung change < 1 % (ℓ_ref recorded); the rest reported, not gated (reference pending), listed in the golden (`--extend` only); z_FW unchanged; '<gated> of 560' / '<gated> of 72' printed (274 / 560, 40 / 72 at the time of writing); listening README, Phase 08 CHANGELOG mark, M-2 per band, CI budget ≤ 10 min per OS | file 4 | 5-seat1–5, 7–9 (max 1, sum 16) | 5-researcher | files 8, 19 | files 15, 21 | SURVIVES | applied (AX43, AX45; phase-05h §5; phase-08 scope 10) |
| P05H-D-H2-b | D-H2 (b) U-a: single-rung references printed, never asserted, with the fixed label `uncertified rung, no ℓ_ref, not pass/fail`; a gross-error detector | file 4 | (max 1, sum 2) | 5-researcher | files 8, 19 | files 15, 21 | SURVIVES | applied (AX43; phase-05h §5) |
| P05H-D-H2-c | D-H2 (c) M-e: references produced offline by `hybrid_fast.py` at two rungs, committed with provenance, in the priority order (1)–(5); phase-05i gates what is certified by then, the rest keeps a named owner phase; the 16 GB-runner artifact job and M-d (Maisara's action) as routes for the 15 GB class | file 4 | (max 1, sum 9) | 5-researcher F17–F20 | files 8, 19 | files 15, 21 (P05H-26 sums corrected) | SURVIVES | applied (AX43, AX45); phase-05i items carried by the orchestrator |
| P05H-D-H2-d | D-H2 (d) B-a: AX46 runs now per band and per class on every class with ≥ 1 certified case; 'not evaluated (reference pending)' otherwise; the 100 m class is the tracer comparison, labelled 'not evaluated at 1 % (compute limit)', never a pass; the pooled figure labelled 'pooled over <n> of 5 classes' | file 4 | (max 1, sum 5) | 5-researcher | files 8, 19 | files 15, 21 | SURVIVES | applied (AX46; phase-05h §5) |
| P05H-H2-F1 | H2-F1 (for Maisara): AX43 / AX45 / AX46 run now on the certified subset; the rest listed and gated in phase-05i or a named owner phase; no case-band dropped, no tolerance widened, no accuracy claim counts a reported case-band. NFR-1. `AMENDS her decision of 2026-11-10` | file 4 | — | — | file 19 | file 21 | SURVIVES; decided for Maisara, open to her veto | applied (AX43, AX45, AX46 scope lines) |

## phase-05h (session 2) — D-H3 (a)–(e), H3-F1…F6 and the phase-05h split: board decision loop (2026-11-10)

Question `docs/review/phase-05h/11-orchestrator-D-H3-question.md` (with the data files 13, 14, 18); convening `16-decider-convene-D-H3.md`; seats `17-seat1…17-seat9-D-H3.md` (round-2 and round-3 cells appended in place; Seat 3 `NOT MY MATTER` on (a); Seats 4, 6, 8 not required on (a)); researchers `17-researcher-RQ-H3-1.md` and `17-researcher-RQ-H3-3.md` (and `12-researcher-T5T4-61.md` for (e)); decider `20-decider-decision-D-H3.md` (round 1), `25-decider-decision-D-H3-r2.md` (round 2, with the G6 / H3-F6 addendum) and `27-decider-decision-D-H3-r3.md` (round 3, with the H3-F6 addendum: (a) revised to (f9); (b)–(e) stand with file 26's restatements); interrogator `22-interrogator-D-H3.md` (round 1), `26-interrogator-D-H3-r2.md` (round 2: TENSION MISREAD on (a) narrowly, the (f9) ask; the rest SURVIVES / WITH CORRECTIONS) and `28-interrogator-D-H3-r3.md` (round 3: everything SURVIVES; (a) and H3-F6 WITH CORRECTIONS, six exact restatements applied by the plan-editor). Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. Applied to AX36 (note), AX38 (i) and 4c, AX41, AX43, AX44, §0 rows 05h and 05i, §4 entry 05i, §6 rows; phase-05h §2, §5, §8; phase-07c §0, §5 (conditions 10, 11), §6; phase-11 scope 8; phase-12 scope 7; phase-13 scopes 6, 8, 13; new `docs/phases/phase-05i.md` (/fix-plan, plan-editor, 2026-11-10). NEEDS MAISARA: none (no case (a), (b) or (c); no 3 overridden; nothing contested after three rounds).

| id | decision | convening | seats | researcher | decider | interrogator | outcome | status |
|---|---|---|---|---|---|---|---|---|
| P05H-D-H3-a | D-H3 (a) (f9): AX43's pooled bias check is the additive bound \|mean (C++ − ref) dB\| ≤ 3·SE_pool + mean ℓ_ref per band (one reading of ℓ_ref throughout the row; the catch printed per band, restated at each golden round, never pinned, a board return above 0.02 dB; no count in the clause); the as-written, per-class, pooled z′ and per-room z′ (the script's `room` column) printed as records with the > 3 label (its reach ≈ 0.023 dB at dead_booth's SE / ℓ_ref stated) and the sign count; the constant 3, τ, z_FW, N and the case list unchanged; applied only after the pre-registered application run (`agree_full5.log`: all eight bands within, 0.0046–0.0047 dB against 0.0096–0.0099 dB at bands 0–2/6/7, 0.0000–0.0002 against 0.0077–0.0078 dB at bands 3–5) | file 16 | 17-seat1, 2, 5, 7, 9 (round-3 (f9) cells: S1 0/1, S2 0/1, S5 0/1, S7 1/1, S9 1/1; max 1, sum 7; (e′) 9, (a) 9, (e) 10; (b)/(c)/(d) dropped) | 17-researcher-RQ-H3-1 (F1, F4–F8) | files 20, 25, 27 | files 22, 26 (TENSION MISREAD narrowly, the (f9) ask), 28 (SURVIVES WITH CORRECTIONS: restatements 1–5, applied) | SURVIVES | applied (AX43; phase-05h §5, §0; phase-13 scope 13) |
| P05H-H3-F1 | H3-F1 (for Maisara): AX43's pooled clause reads ℓ_ref one way throughout the row (the additive bound); the catch about 0.008–0.010 dB on the application run, printed and bounded at 0.02 dB; nothing else in the rule moved. NFR-1; the verification culture; AX42 / AX43 per-case form; AX46. `AMENDS her decision of 2026-11-10` (AX43's pooled clause). Also the AX36 caveat (dead_booth's ladder, ratio 1.50–1.63; note only): `AMENDS her decision of 2026-11-09` (AX36) | file 16 | — | 17-researcher-RQ-H3-1 | files 25, 27 | files 26 (P05H-84), 28 (P05H-121 CORRECT, P05H-122 corrected) | SURVIVES; decided for Maisara, open to her veto | applied (AX43 rationale, AX36 rationale) |
| P05H-D-H3-b | D-H3 (b) (d): 'valid fixture' in AX44 Seat 6 (ii) and the reversal = a user-reachable room or Phase 12 preset; `edge_values` and `open_field` are contract-limits fixtures, U true there (cap), named by the golden's pinned U, the cause line printing the cause; the golden is the list (U and the five AX41 flags pinned per fixture in the D5 golden); the reversal not triggered; the display rule keyed on AX37 (5.4)'s kept check (−85 dB at `open_field`, 25 dB below the line; −30 / −16 dB at `edge_values`; +7 dB at `medium_room`; C1's '> 44 dB' a different quantity, no margin moved); the CI report (cause, movability, tail level) | file 16 | 17-seat1…9 (max 1, sum 9; (c) dropped) | — | files 20, 25, 27 | files 22, 26 (P05H-86, -87 corrected), 28 (P05H-123) | SURVIVES | applied (AX44, AX43 CI-report line; phase-05h §5, §8; phase-11 scope 8; phase-12 scope 7) |
| P05H-H3-F2 | H3-F2 (for Maisara): the AX44 (ii) reading and the display rule above; the J1 trigger's cause clause does not cover a capped near-zero total below the −60 dB line; `courtyard` tested as a room. NFR-8 / FR-SIM-2, FR-3D-3, FR-3D-5, NFR-1. `AMENDS her decision of 2026-11-10` (AX44 Seat 6 (ii) and reversal; AX41 J1 clause) | file 16 | — | — | files 20, 25, 27 | files 22, 26, 28 | SURVIVES; decided for Maisara, open to her veto | applied (AX44, AX41; phase-12 scope 7; phase-11 scope 8) |
| P05H-D-H3-c | D-H3 (c) (g): the `[pipeline]` FTZ test asserts the denormal on the named scene (dead_booth geometry, α 0.01 at 63 Hz / 0.999 above, s 0.5: the near-rigid 63 Hz band's long tail against the 8.6 ms fast bands) per architecture with calibration and `ThreadPool(1)`; the `[probe-denormals-detector]` probe standing in `ci.yml` on three OSes; every pool share under the FTZ/DAZ guard, re-probed in the same CI run before the PR (D5 hashes identical, cross-OS E_target within 1e-7), else (f) the caller-only form with the scene named; MSVC ARM64 SKIP (Phase 13 note) | file 16 | 17-seat2, 3, 5, 7 (own (g) cells; max 1, sum 3; (f) 5, (d) 6) | — | files 20, 25, 27 | files 22, 26 (P05H-92 corrected), 28 (P05H-124) | SURVIVES (conditional on the same-run re-probe) | applied (phase-05h §5, §0; phase-13 scope 8); AX37 (5.1) (i) text unchanged |
| P05H-H3-F3 | H3-F3 (for Maisara): AX37 (5.1) (i) is met literally on the named scene; no text change; no AMENDS. NFR-6 / AX5, NFR-8, the verification culture | file 16 | — | — | files 20, 25, 27 | files 22, 26 (P05H-94 CORRECT), 28 | SURVIVES; decided for Maisara, open to her veto | recorded (phase-05h §5; §6 row) |
| P05H-D-H3-d | D-H3 (d) (e5): `layout4_s1/both_corner` asserts the cap flag (N_need ≫ N_cap); W1 both_corner asserts U (both-near ∧ VOV_union ≥ 0.1; SE 1.122 dB, VOV_union 0.567) with its flags (n\* 1 024, N 1 024, N_cap 1 088, cap hit 0, floor truncated 0) pinned as constants in the records test with the file-13 provenance, re-pinned with a CHANGELOG reason at each W_max / n\*_max change; the five flag fields of every valid fixture pinned in the D5 golden; the Q-3 work-count difference recorded once | file 16 | 17-seat1, 2, 5 (max 1, sum 3; tie with (d) through step 6, Seat 5's own form chosen) | — | files 20, 25, 27 | files 22, 26 (P05H-95), 28 (P05H-125) | SURVIVES | applied (AX44 cap-flag clause; phase-05h §5) |
| P05H-H3-F4 | H3-F4 (for Maisara): the reading of AX44's "W1 both_corner asserts the cap flag" above. NFR-1; NFR-6 / AX5; the verification culture. `AMENDS her decision of 2026-11-10` (AX44's cap-flag clause) | file 16 | — | — | files 20, 25, 27 | files 22, 26, 28 | SURVIVES; decided for Maisara, open to her veto | applied (AX44) |
| P05H-D-H3-e | D-H3 (e) (e-x′): AX38 (i) class (1)'s premise corrected (`reset()` / `setNonRealtime` may arrive on the VST3 processing thread; AU unspecified); the open check in two halves: (1) closed by specification for `reset()` with the register entry (worst quiesce wait 2 664 ms, cancel points only in the diffuse solve, stale rebuild ≈ 3.6 s, up to ≈ 6.3 s; the `[diffuse-quiesce]` growth print; the test-build counter), the remedy phase-07c condition 10 and the release rule "no build reaches a producer outside the team (beta included) while the entry is open"; (2) freeze / offline measured per host by the `SPATIAL_HOST_TRACE` trace build (phase-07c condition 11), a person's action, results to Phase 13; phase-07c §5 conditions 10 and 11; AX38 4c gains the K-e12 finding (a restore arriving mid-build waits up to 2.66 s before its ≈ 2.14 s build, ≈ 4.8 s per restore, 14 such ≈ 67 s [Hyp]; measured with the builder idle, `test_diffuse_records.cpp` L422; a record task in 05h or 05i; remedy 07c conditions 9 and 10; H1-F1 not widened) | file 16 (the (e) addendum) | 17-seat1…9 (max 2, Seat 3 2/1; sum 13; (e-c) ≥ 20 after Seat 8's condition failed on K-e6) | 12-researcher-T5T4-61 (F1, F2, F6, F9, F20) | files 20, 25, 27 | files 22, 26 (P05H-96…99 corrected), 28 (P05H-126) | SURVIVES | applied (AX38 (i), AX38 4c; phase-07c §0, §5 conditions 10–11, §6; phase-05h §5; phase-13 scope 6; phase-05i scope 2) |
| P05H-H3-F5 | H3-F5 (for Maisara): AX38 (i) class (1) read with the corrected premise and the two-halves open check; AX38 4c's finding recorded, no rule change. NFR-2 (L101), NFR-4, NFR-6 / AX5, NFR-8, L55; NFR-3 / FR-SIM-6 for the stale-after-automation case only. `AMENDS her decision of 2026-11-10` (AX38 (i) class (1), correction T5T4-59 kept; AX38 4c note) | file 16 | — | 12-researcher-T5T4-61 | files 20, 25, 27 | files 22, 26 (P05H-97, -98), 28 | SURVIVES; decided for Maisara, open to her veto | applied (AX38 (i), AX38 4c) |
| P05H-H3-F6 | H3-F6 (for Maisara; a `FOR MAISARA` outside a board round, steps 5–8a): the agreement golden's reference for dead_booth, living_room, classroom and club (both emitters, 8 bands) is the 0.625 m rung, ℓ_ref = the 1.25 → 0.625 m change (dead_booth 0.28 %, up from 0.17 %: the rule's value; the ladder's ratio 1.50–1.63 carries the AX36 caveat to that rung), through `update_goldens.py` with the reason; the D-T6 small room stays ungated; no CHECK changes colour (at 500 Hz–2 kHz the move lowers the pooled mean deviation and the bound alike; at bands 0–2, 6, 7 the mean moves −0.0042 → −0.0047 dB while the bound falls 0.0118 → 0.0099 dB, margin 2.8× → 2.1×); the G6 golden round preceded the check. NFR-1; the verification culture. `AMENDS her decision of 2026-11-10` (AX43: a record of application, no rule change) | — | the seats' earlier words quoted exactly (Seat 1 L31, Seat 2 L27, Seat 9 L76; Seats 5, 7 met) | — | file 25 (addendum), file 27 (addendum, P05H-103) | files 26 (P05H-103 SURVIVES WITH CORRECTIONS: restatements 7–8), 28 (P05H-127 WITH CORRECTIONS: the ratio 1.50–1.63, the per-band interplay; applied) | SURVIVES; decided for Maisara, open to her veto | applied (AX43 rationale, AX36 rationale; `tests/golden/CHANGELOG.md` G6 entry already in the tree) |
| P05H-split-05i | Phase 05h split under CLAUDE.md's two-session rule (orchestrator; not a board decision): `docs/phases/phase-05i.md` created with the carries (D-H2 (c)'s remaining references and their gating; the AX38 (iv) records not produced and the K-e12 record; the growth-bound baselines; phase-05h §2 items 2 and 3 on the CI records; the AX41 lists); §0 row 05i `not started`, depends on 05h; §0 row 05h's session-2 note rewritten from the session's facts; phase-07c follows 05i where the gate and records land there (phase-07c §3, pre-existing) | — | — | — | — | P05H-99 (file 26) and file 28 noted the missing 05i row as pre-existing | n/a (bookkeeping) | applied (BUILD_PLAN §0, §4, §6; phase-05h header, §2, §8; phase-05i) |

## phase-05h (session 2) — Raise items 2 and 3 answered for Maisara (2026-11-10)

Questions phase-05h §2 items 2 and 3 ("Raise with Maisara": the AX38 4c records against the 1 / 3 / 10 s anchors; the AX38 (iv) 8-instance 100 m load against the 10 s line), on CI run 42909003931 (`31-orchestrator-local-records.md`, CI section); decider `33-decider-raise-items-2-3.md` (round 1) and `36-decider-raise-items-2-3-r2.md` (round 2, with the addendum settling R3's notes clause on Seat 7's cells); seat `35-seat7-raise-item-3-notes-clause.md` (Seat 7, convened on R3's notes clause only); interrogator `34-interrogator-raise-items-2-3-r1.md` (round 1: R2 PRD MISREAD, R3 UNDERCONVENED) and `37-interrogator-raise-items-2-3-r2.md` (round 2: both SURVIVES WITH CORRECTIONS, the corrections applied by the plan-editor with the records). Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. Applied to AX38 4c and (iv), §0 rows 05h and 05i, §6 row; phase-05i §3 scope 4 (/fix-plan, plan-editor, 2026-11-10). NEEDS MAISARA: none (no case (a), (b) or (c); no 3 overridden; nothing contested after three rounds).

| id | decision | convening | seats | researcher | decider | interrogator | outcome | status |
|---|---|---|---|---|---|---|---|---|
| P05H-R2 | R2 (for Maisara; phase-05h §2 item 2): against AX38 4c's whole Records list on CI run 42909003931 no single-instance record exceeds 3 s; two findings named with the scheduled remedy, F-a (the contended restore of the reported-set 100 m cube `cube100_lowalpha0.05_s1` on Linux, worst 4.079 s of 3 runs) and F-b (multi-instance load and joint-rebuild staleness, about linear in instance count), remedy phase-07c conditions 9 (or 07d) and 10, re-measured by 07c condition 7; no W_max cut, range change or seam. PRD L101, NFR-2, NFR-3, FR-3D-1, L42. `AMENDS her decision of 2026-11-10` (AX38 4c: recorded findings F-a, F-b, no rule change) | no seat (file 36 §3: readings of her row against records) | — | — | files 33 → 36 (§2, R2 revised: PRD MISREAD accepted, findings named) | 34 PRD MISREAD → 37 SURVIVES WITH CORRECTIONS (applied) | SURVIVES; decided for Maisara, open to her veto | applied (AX38 4c record line; §0 rows 05h and 05i; §6 row; phase-05i scope 4) |
| P05H-R3 | R3 (for Maisara; phase-05h §2 item 3): the 10 s line fired (8 × 100 m / 96 kHz load 20.4–25.6 s); recorded under AX38 (iv) as a finding of a build that never reaches a producer; remedy phase-07c conditions 9 (or 07d if 07c cannot carry it) and 10; re-measured after 07c (condition 7) with two times per instance (until audible at the interim level, until the final tail has settled); Phase 13 Raise item 3 applies the 10 s line to the former on the release machines and names the latter as a finding if above 10 s; the notes clause stripped (option (A) on Seat 7's cells, by reversibility after the 1 / 1 tie); premise P1 on the register. PRD L101, NFR-2, NFR-1, NFR-6, L42. `AMENDS her decision of 2026-11-10` (AX38 (iv)) | Seat 7 on the notes clause only (file 36 addendum CONVENE row; file 35) | 35-seat7 ((A) 0/1, (B) 1/2, (C) 0/1; (B) out on worst-off; (A) and (C) tie, (A) cheaper to undo) | — | files 33 → 36 (§3 and the addendum, R3 revised: clause stripped, corrections and the P1 row applied) | 34 UNDERCONVENED → 37 SURVIVES WITH CORRECTIONS (applied) | SURVIVES; decided for Maisara, open to her veto | applied (AX38 (iv) record; §0 rows 05h and 05i; §6 row; phase-05i scope 4) |

## phase-05h (session 2) — review file 39's readings (2026-11-11)

Questions `docs/review/phase-05h/40-orchestrator-review-39-questions.md` (from `/review-phase-pr` file 39 on head a9d8313: blocker 1, AX37 (5.4)'s open_field check at bands where the estimator's SE is not small against τ; major 1, the BRAS pairs in no AX46 class; major 2, the near-wall class unevaluable under the empirical class SE), with the evidence appended (the near-wall class SE in both forms, the BRAS record lines, the 2^23-history open_field runs, the floor integral's quadrature ladder); decider `42-decider-review-39-readings.md` (round 1 + the addendum on the 2^23 result) and `44-decider-review-39-readings-r2.md` (round 2: corrections accepted, the nightly-move clause withdrawn); interrogator `43-interrogator-review-39-readings-r1.md` (SURVIVES WITH CORRECTIONS; the nightly-move clause UNDERCONVENED, Seat 5) and `45-interrogator-review-39-readings-r2.md` (SURVIVES WITH CORRECTIONS: wording A, B, C). Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. Applied to AX37 (5.4), AX46, the §6 D-H2 row's quote, phase-05h §5 criteria 3 and 9, three §6 rows; the tests in commit b8b3c6d (/fix-plan, plan-editor; the ledger block by the orchestrator, 2026-11-11). NEEDS MAISARA: none (no case (a), (b) or (c); no 3 overridden; nothing contested after two rounds).

| id | decision | convening | seats | researcher | decider | interrogator | outcome | status |
|---|---|---|---|---|---|---|---|---|
| P05H-QA | QA (for Maisara; AX37 (5.4)): the open_field finite-floor check runs at a validation N of 2^23 histories, both s values and emitters, asserting per band 3·SE ≤ τ (the plan's N-rule form with AX46's constant 3, no ℓ_ref term) and \|dev\| ≤ τ, τ alone; the shipping-N render a labelled smoke test (τ + 3·SE as a gross-error detector), never the check; a band outside τ at 3·SE ≤ τ is reported, never loosened (NFR-8); an OS with 3·SE > τ → N 2^24 with a §6 row; the two renders adding > 10 min to the python job on any OS → a board return with Seat 5 (the pre-authorised nightly move struck). Record: 2^23 within −0.020…+0.005 dB in every band, 3·SE ≤ 0.229 dB; the 2^20 +0.29 / +0.37 dB at 4–8 kHz noise (z ≤ 1.7); the integral's quadrature ladder ≤ 0.009 dB. PRD NFR-1, NFR-8; AX37 (5.4), AX42. `AMENDS her decision of 2026-11-10` (AX37 (5.4), ledger P05B2-M-01: the validation-N sentence, the smoke-test sentence and the 2^23 record added) | no seat (an additive reading; the conditional CONVENE of Seats 2, 9, 1, 5 for an offset above τ lapsed on the 2^23 result; Seat 5 convened only on the > 10 min return) | — | — | files 42 (+ addendum), 44 | 43 SURVIVES WITH CORRECTIONS (nightly clause UNDERCONVENED) → 45 SURVIVES WITH CORRECTIONS (applied) | SURVIVES; decided for Maisara, open to her veto | applied (AX37 (5.4); phase-05h §5 criterion 9; §6 row; `test_tail.py` in b8b3c6d) |
| P05H-QB | QB (for Maisara; AX46): the 30 BRAS pairs are AX46's sixth class, printed and checked on their own line per band; 'pooled over <n> of 6 classes'; bands without a gated BRAS case-band 'not evaluated (reference pending)'; no class folded or excluded. PRD NFR-1 ("measured in real spaces"); D-H2 (d). `AMENDS her decision of 2026-11-10` (AX46's class list: six classes; D-H2 (d)'s "of 5 classes" as quoted in AX46 → 6) | no seat (additive) | — | — | files 42, 44 | 43 → 45 SURVIVES WITH CORRECTIONS (applied) | SURVIVES; decided for Maisara, open to her veto | applied (AX46; phase-05h §5 criterion 3; §6 row; `test_diffuse_agreement.cpp` in b8b3c6d) |
| P05H-QC | QC (for Maisara; AX46): SE_class = √(mean SE_i² / n) from the per-case estimator SEs (the quantity N controls), ℓ_ref once as the class mean (D-H3 (a)'s reading); evaluated at n ≥ 1 when 3·SE_class ≤ 1 % − mean ℓ_ref, then \|mean deviation\| ≤ 1 %; the empirical SE (n ≥ 2; 1 d.o.f. at n = 2) and the max ℓ_ref printed as records; \|mean\| + 3·SE_emp > 1 % with the CHECK green labelled (heterogeneity watch, a board return). The near-wall line conditioned on the c4 cross-check, recorded passing in file 6 (2026-11-11). Record: near-wall evaluated in all eight bands (SE_prop 0.072–0.078 %, means −0.14…−0.22 %); BRAS +0.110…+0.117 % at 500 Hz–2 kHz; 'pooled over 4 of 6 classes'. PRD NFR-1; AX46, D-H3 (a). `AMENDS her decision of 2026-11-10` (AX46's N sentence made explicit; D-H2 (d)'s "(3·SE ≤ 1 % − ℓ_ref)" as quoted in AX46) | no seat (a reading of AX46's sentence in D-H3 (a)'s form) | — | — | files 42, 44 | 43 → 45 SURVIVES WITH CORRECTIONS (applied) | SURVIVES; decided for Maisara, open to her veto | applied (AX46; phase-05h §5 criterion 3; §6 row; `test_diffuse_agreement.cpp` in b8b3c6d) |
| P05H-QA-T | P05H-QA-T and P05H-QA-T-A (for Maisara; AX37 (5.4)): the QA board-return trigger fired (CI run 42935789745: the two 2^23 open_field renders took 12.9 / 7.9 / 8.8 min on Linux / macOS / Windows inside the python job); option (f): the 2^23 cases carry the registered marker `open_field_validation` and run in their own three-OS PR CI job `open-field-validation` (`timeout-minutes` 45, `--durations=10`, in `ci-ok`'s needs), the python job deselects them (back to ≈ 10–11 min) and is bounded at 45 min; both s values, both emitters, τ alone, three OSes unchanged; the trigger now "the longest job of a green run, across all jobs and OSes" → a board return with Seat 5. (b)/(c) fell at step 1 (her recorded "both s values"); (a) 2/2 on Seat 5's cell; (a′) 1/2 read from conditions. PRD NFR-1 (served equally by every survivor keeping τ); AX37 (5.4). `AMENDS her decision of 2026-11-10` (AX37 (5.4), ledger P05B2-M-01: the trigger sentence only) | Seat 5 convened (the clause's own term); Seats 2/9 not required ((b)/(c) not chosen); Seat 7 not required (public repository, runner minutes unbilled) | 49-seat5 ((f) 1 / 0–1; (b), (c) 1/1; (a) 2/2 → 1 now with three conditions; (d) measure first) | — | file 50 (+ addendum: C1–C6 accepted, the FOR MAISARA block, Q1–Q4) | 51 SURVIVES WITH CORRECTIONS (winner unchanged; applied in the addendum) | SURVIVES; decided for Maisara, open to her veto | applied (CI change cb7effb: `.github/workflows/ci.yml`, `tools/acoustics/tests/conftest.py`, `test_tail.py`; AX37 (5.4) sentence and §6 row by the plan-editor; verified by CI run 42942694523) |

## phase-05h (session 2) — DECISION RG-1: the restore gate on shared runners (2026-11-11)

Question `56-orchestrator-restore-gate-runner-variance.md` (the AX38 4c blocking restore gate red on CI runs 42942694523 and 42949252041 by shared-runner speed on identical code; the five-run table; the measured flutter split timer); convening `59-decider-convene-restore-gate-runner-variance.md` (rounds 1–2); seats `57-seat5-…` (+ B5, round 2), `58-seat3-…` (+ rounds 2–4), `60-seat7-…` (+ round 2), `61-seat6-…`, `62-seat2-…`; researcher `63-researcher-RQ-RG.md`; decider `64-decider-decision-RG-1.md`, `66-…-r2.md`, `68-…-r3.md`, `70-…-r4.md`; interrogator `65-interrogator-RG-1-r1.md` (FALLS on the ns/evaluation CHECK), `67-…-r2.md` (TENSION MISREAD on the macOS OVER30S trigger), `69-…-r3.md` (Seats 5/6's cells; (c) must not re-arm the strict branch), `71-…-r4.md` (SURVIVES WITH CORRECTIONS: Seat 6's cell marked read; rule (d)'s remedy split). Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. Applied to AQ10 (1), AX38 4c, AX41, phase-05h §5 "Blocking", phase-05i scope 3, phase-07c condition 9, phase-13, a §6 row; the tests and `ci.yml` in commit 67f13f3. NEEDS MAISARA: none.

| id | decision | convening | seats | researcher | decider | interrogator | outcome | status |
|---|---|---|---|---|---|---|---|---|
| P05H-RG-1 | RG-F1 (for Maisara; D-H1 (v)(a)–(b) / AX38 4c / AQ10 (1) amended): on GitHub-hosted runners the restore gate asserts what is runner-independent and prints what is not. Asserted every run: the exact W_pilot / W_final pins and the AX41 ratio; per gated scene the unit-decay length and the synthesis FFT size n (exact); the flutter scene's 14 × worst ≤ 30 s on every OS; on Linux and Windows the low-α median ≤ 1.10 × the mean in-window baseline (2 068 / 2 028 ms) when the run's flutter median is within ±5 % of its reference (701 / 737 ms), else `not-evaluated(runner)`. Printed with WARNING, never asserted: the low-α/flutter ratio above 1.20 × its mean (3.05 / 2.83 / 3.75), the per-scene solve median and ns per evaluation (a bound after ≥ 3 runs), 14 × worst vs 30 s, macOS's growth (baseline 1 817 ms, print only until Phase 13); on macOS two consecutive runs with the low-α median above 2 172 ms (1.15 × the mean of the four measured macOS medians) are a (d) defect, remedy named; an entry that passes 30 s leaves the register without re-arming the strict branch on shared runners (the strict 30 s is the flutter scene's, and the low-α scene's only on the release machines). (d) a broken assertion or the macOS trigger is a defect: a timing entry → phase-07c conditions 9–10; a work-pin entry → the code change named, re-pinned only with a CHANGELOG reason (file 71). One GATE line per OS/scene; the §0 counts; `if: always()` on pluginval/auval; the strict 30 s and 1.10 growth re-enforced on all three OSes on Phase 13's release machines (bought once); phase-07c condition 9's packet repeats the split timer on a named box. Baselines = means of the measured runs on file (Windows also 42942694523; macOS three runs), re-pinned only when the restore path changes (one run PROVISIONAL, ≥ 3 runs with a CHANGELOG reason). (a) kept as it was: veto-grade (Seat 5: 3 now; each red masked pluginval/auval). PRD L101 / NFR-2, NFR-4, NFR-1, NFR-6, L20. `AMENDS her decision of 2026-11-10` (AQ10 (1), AX38 4c, D-H1 (v)(a)–(b)) | Seats 2, 3, 5, 6, 7 convened (file 59); 1, 4, 8, 9 not required (no option moves the restore, the audio, the delivery or a room) | 57 (x′ 0/1; B5; round 3: 0/1 with the trigger at 2 172 ms), 58 (1/1 through round 5), 60 (1/1, window ±5 %), 61 (round 2: later 1 on the 1 999 form, read as 0/1 at 2 172: same 'buys nothing' reason, lower exposure), 62 (1/1 with the work pin) | 63 (RQ-RG-1–3: no documentary statement on hosted-runner timing; Laaber's single-instance figures; EPA/NIST bounds) | 64 → 66 → 68 → 70 (the ns/eval CHECK struck; the macOS trigger GROWTH-only, then armed at 2 172 ms; macOS baselines from three runs; max 1, sum 9) | 65 FALLS (one component) → 67 TENSION MISREAD (one clause) → 69 (two items) → 71 SURVIVES WITH CORRECTIONS (applied) | SURVIVES; decided for Maisara, open to her veto | applied (67f13f3: `test_diffuse_records.cpp` `kGateRegister` and the GATE lines, `ci.yml`, CHANGELOG; the plan texts by the plan-editor, e87a47f; diff check file 72 SURVIVES WITH CORRECTIONS: C1 the AX38 register paragraph's pre-RG-1 baselines, C2 phase-13 Raise item 5, applied 814264c; re-check file 73 SURVIVES) |

## Phases 07c, 08, 10, 11, 12, 13 split into sub-phases (2026-11-10; /fix-plan with the board loop; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Maisara, 2026-11-10: "split each of the remaining phases 7 onwards into the smallest buildable sub phases that ship
value while keeping the session's attention focused on one subject matter that deserves it". Session brief
`docs/sessions/2026-11-10-phase-split.md`; round files `docs/review/phase-split/` (maps, 1 convening, 2 seats 1–7,
3 decision, 4 interrogator r1, 5 decision r2 + addendum, 5b Seat 2 r2, 6 interrogator r2, 7 apply brief, 8 coverage,
9 diff check).

Convening tables: one combined nine-row table (`1-decider-convening.md` §2): Seats 1–7 convened, 8 and 9 not required
(interrogator: faithful).

| id | item | verdict | status |
|---|---|---|---|
| PSPLIT-01 | Size ruling: two-session limit applies per sub-phase (08-c5, 11-c2, 13-c3 NOT A DECISION) | SURVIVES | closed |
| PSPLIT-02 | Convening-round NOT A DECISION classifications (07c-c1..c3, 08-c2, 08-c4, 09-c1, 10-c1..c3, 11-c3, 13-c2, 13-c4) | SURVIVES | closed |
| PSPLIT-03 | D-PS1 (08-c1): AX37 (5.3) conditions attached per sub-phase; 08-2 reads t_mix,e via `planEmitter`/`TailMatch` (code-checked) | r1 PRD MISREAD (acceptance check) → r2 SURVIVES | closed |
| PSPLIT-04 | D-PS2 (08-c3): grouping rule in 08-4 after the benchmark; L1/L3/L4/L5 provisional in 08-3, conditional re-listen | r1 PRD MISREAD (acceptance check) → r2 SURVIVES | closed |
| PSPLIT-05 | D-PS3 (11-c1): shell first, Seat 6 conditions (i), (ii) | r1 PRD MISREAD → r2 SURVIVES | closed |
| PSPLIT-06 | D-PS4 (13-c1): r1 four-way, step 4 FALLS (C2 clause split) → r2 five-way (13-1..13-5), Seat 2 rated in its own words | r2 SURVIVES WITH CORRECTIONS (applied) | closed |
| PSPLIT-07 | FM-1: Phase 11 must be split (her 2026-11-10 instruction; PRD neutral) | r1 PRD MISREAD → r2 SURVIVES | closed |
| PSPLIT-08 | Corrections: 07c Raise in both; 12-1 drops AC2 share; 13 Raise in 13-1 and 13-5; debt ids land | SURVIVES (WITH CORRECTIONS on ids, applied) | closed |
| PSPLIT-09 | Finished diff: coverage, values, G2 clause splits, decisions applied | CORRECT with fixes 4b, 4c (applied) | closed |

Follow-ups (not in this change): phase-05h scope 10 and line 286 wording aligned to D-PS1 step 6; record 05h as a
dependency of 11-3 (11-c3); Apple-silicon hardware for 13-2/13-3 and starting K1–K3 enrolment (Maisara's actions);
review-skill drift (DF-EQ "switchable" vs phase-08 scope 3 "always applied"; map-10 note); "13b" in phase-06b now
means `13-1b`; map-13's references table uses the superseded four-way numbering (the phase-13 umbrella's coverage
table is authoritative).

## phase-05i — the 05i records, the Raise items, the restore-gate register, the solve bound, gate scope G-1 (2026-11-11; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d from round 2 on)

Questions `docs/review/phase-05i/4-orchestrator-questions.md` (Q1–Q5, on CI run 43007183782's records, file 3); code facts
file 7 (its first bullet corrected after P05I-47: the gate is held for the whole room-IR build). Round 1 (files 5, 6) ran
without the corpus (the private repository was attached later in the session, file 10 re-checked its corpus items: no
finding changed). Interrogator ledger rows P05I-00…P05I-95 are in files 6, 10 and 14; the diff check in file 16.

| id | decision | convening | seats | researcher | decider | interrogator | outcome | status |
|---|---|---|---|---|---|---|---|---|
| P05I-Q1 | FOR MAISARA: the AX38 4c Linux and Windows low-α register entries close under (c) on 05i's runs (43007183782 plus the PR's run of record); macOS stays listed; `listed` false (print only) | none (reading of her AX38 4c (c)) | — | — | files 5, 9 | 6 (WITH CORRECTIONS) → 10 SURVIVES | applied in code (52fc283) and CHANGELOG; plan text after the run of record | open until the run of record |
| P05I-Q2 | FOR MAISARA: Raise item 1 not re-opened; the K-e12 record (worst 3.28 / 2.65 / 3.23 s; median above 2.143 s on Linux and Windows) written into AX38 4c as a finding, remedy 07c conditions 9–10 | none | — | — | files 5, 9 | 6 (WITH CORRECTIONS) → 10 SURVIVES | applied (e168fb5) | closed |
| P05I-Q3 | FOR MAISARA: Raise item 2 (R3) stands; F-b extended; F-c withdrawn into G-1; following strained against Table 15.1's 700 ms row from 1 instance at 100 m and at the AQ10 room from 4 at 96 kHz; artifacts not measured | none (records against her rules) | — | — | files 5, 9, 11 | 6 PRD MISREAD → 10 FALLS (gate scope, P05I-47) → 14 SURVIVES WITH CORRECTIONS | applied with file 14's corrections (e168fb5) | closed |
| P05I-Q4 | Raise item 3 (M-d) did not arise | none | — | — | file 5 | 6, 10 SURVIVES | recorded | closed |
| P05I-DQ5 | DECISION: `SOLVE` printed when the solve median exceeds `kSolveWarn` 1.20 × the in-window baseline (PROVISIONAL, n = 1–2), never asserted | Seat 5 (after 6 UNDERCONVENED) | 8 | — | files 5, 9 | 6 FALLS (out-of-window baseline) → 10 SURVIVES | applied in code (52fc283), CHANGELOG, plan (e168fb5) | closed |
| P05I-DG1 | DECISION A′: AX38 (i) register entry G-1 (gate held for the whole build) with its own release rule; remedy phase-07c-1 condition 12 and A12 (10 → 12 → 9); 05i gate-wait poller (printed) | Seats 1, 2, 3, 5 (lead), 6, 7, 8; 4, 9 not required | 12-seat1/2/3/5/6/7/8 | 12-researcher-RQ-G1 (K-g7 NOT READY, not load-bearing) | files 11, 13 | 14 SURVIVES WITH CORRECTIONS | applied (poller in code; plan e168fb5) | closed (G-1 open until 07c-1 A12) |
| P05I-G1C1 | FOR MAISARA: AX38 (iii) "settling" on every instance whose latest change is not yet audible (queued, building, crossfading); the crossfade exposure and "going live" left to phase-10-2 scope 3 | Seat 6 (C1) | 12-seat6 | — | file 13 | 14 SURVIVES WITH CORRECTIONS | applied (e168fb5) | closed |
| P05I-BK | Bookkeeping: AX43 560 / 560, AX45 72 / 72, catch ≈ 0.008 dB in all eight bands, 26 rooms; §6 rows | — | — | — | — | file 16 (diff check) | applied (e168fb5) | see file 16 |

Decided for Maisara (open to her veto): Q1, Q2, Q3, Q4, D-Q5 (no AMENDS), D-G1 and G1-C1 (both AMENDS her decision of
2026-11-10, "I accept the board's answer by definition"). NEEDS MAISARA: none.
| P05I-Q1-ROR | Q1 on the run of record 43031773338 (decider file 9's drop rule): Linux closed; Windows stays listed (46.63 s OVER30S, slow runner), its records-test flag back to true in the contractor's review push; macOS listed | none | — | — | file 9 | file 22 (diff check) faithful; minor wording P05I-114 applied | applied (70ed68b and the §0 commit) | closed (code item owed to the review push) |
| P05I-S0 | §0 rows 05i (`done`) and 05h | — | — | — | — | file 22 faithful; P05I-122, -125, -126 applied | applied | closed |

## phase-05i follow-up — Windows low-α `listed` flag restored; plan wording names PR #31 (2026-11-12; /fix-plan, no board loop; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

| id | item | outcome | evidence |
|---|---|---|---|
| P05I-120 | the Windows low-α records-test `listed` flag owed to PR #30's contractor review push (decider file 9 answer 4) | **closed**: set to true in PR #31 (commit 6d38d4e); PR #30 merged before any review push | CI run 43173536470 (all jobs green; Windows "LISTED defect", macOS "LISTED defect", Linux "register entry closed"); brief `docs/sessions/2026-11-12-05i-windows-listed.md` |
| P05I-Q1-ROR | ledger row's "owed to the review push" | superseded by P05I-120 above | — |
| DC31-1, DC31-2 | BUILD_PLAN L28 / L158 wording: "the contractor's review push" → PR #31 | CORRECT (interrogator diff check) | `docs/review/phase-05i-followup/1-plan-editor.md`, `2-interrogator-diff-check.md` |
| DC31-3 | L158 cites answer 4 for the PR #31 vehicle | minor, optional, not applied | same |
| DC31-4 | PASSES30S for Windows / macOS low-α on 43173536470 | a 07c-1 data point (conditions 9–10); not a (c) trigger under decider file 9's "on 05i's runs" reading | PR #31 follow-ups |

## phase-07c-1 (decision loop, 2026-11-12; D-C1, D-C2, D-C3, D-C9; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Files under `docs/review/phase-07c-1/`: 1 (orchestrator, the decisions and code facts), 2 (decider convening: one table
for the four matters, all nine seats convened), 3-seat1…9 (positions), 4 (researcher R1–R5, verdict NOT READY from
documentation; R1/R2/R3/R5 close only with the condition 11 trace, R4 has no within-stream study), 5 (decider round 1),
6-seat*-r2, 7 (interrogator round 1, P07C1-01…30), 8 (orchestrator: measured provisional cost K15, local condition 10/12
records, TSan), 9 (decider round 2), 10-seat*-r3, 11 (interrogator round 2, P07C1-31…58), 12 (decider round 3, final),
13 (interrogator final check, P07C1-59…86), 14 (Seat 3 settles row 59), 15 (plan-editor apply), 16 (interrogator diff
check).

| id | decision | convening | outcome | status |
|---|---|---|---|---|
| D-C1 | AX47 C5‴: interim-to-final step ≤ 1 dB per band over the tail window; classes (a) by construction and (b) the AX49 provisional (tested) in 07c-1; statistical sources only from 07c-2 after the AX47 ABX | all nine (2, 4, 8 NOT MY MATTER) | max 2, sum 10, tie with C3 broken by phase-07c-1 L40 / NFR-1 via Q9 and AQ9; file 13 SURVIVES WITH CORRECTIONS (rows 64, 74, 75, 79) | applied (AX47) |
| D-C2 | AX48 B4-G′: edits / reset / prepare hold the previous E_b (B1′); keyless loads with no IrSet current run the stage-1 solve synchronously, served in class (1) | all nine | max 1, sum 13; SURVIVES WITH CORRECTIONS (row 82) | applied (AX48) |
| D-C3 | AX48 A1′ + Π: state v2 saves `bandsDiffuse` with a five-part key (P, S, E_prec, E_model, Π); interim only, the solve always confirms | all nine | max 1, sum 11; SURVIVES WITH CORRECTIONS (row 79); row 47 closed | applied (AX48) |
| D-C9 | AX49 D3*‴: provisional tail L_f = t_mix,e,max + 0.312·T60_max, built synchronously where no valid IrSet is current (exact tail where L_p ≥ L); D5 bridge on T60 edits; parallel emitters; long-T60 gate corner to phase-07d | all nine (2 NOT MY MATTER) | max 2, sum 23; row 59 TENSION MISREAD settled by Seat 3 in its own words (file 14: D3*″'s edit path 3/3), so D3*‴ stands, no NEEDS MAISARA; rest SURVIVES WITH CORRECTIONS (rows 62 [the S5/S7 cells hold at T60_max ≲ 8.3 s: the rated corner], 63, 68, 69, 70, 85) | applied (AX49, phase-07d.md) |
| FM-1 | AX18: same-scene interim steps equal-gain | — | SURVIVES WITH CORRECTIONS (row 83) | applied; AMENDS her decision of 2026-11-08 |
| FM-2′ | restore gate counts the AX49 interim tail; prepare with an fs change builds it; long-T60 corner to 07d (condition 9's split clause) | — | SURVIVES WITH CORRECTIONS (rows 69, 73); 07d reading CORRECT (row 72) | applied; AMENDS her decision of 2026-11-10 |
| FM-3′ | synchronous stage-1 solve at keyless loads only | — | SURVIVES (row 84) | applied; AMENDS her decision of 2026-11-10 |
| FM-4′ | AX47 at 1 dB, not 0.5 dB | — | SURVIVES WITH CORRECTIONS (rows 74, 75) | applied |
| P07C1-01…30 | interrogator round 1 on file 5 | — | D-C1, D-C2(B), D-C9 FALL (TENSION / PRD MISREADs); D-C3 one clause FALLS; AX18 missing AMENDS | all answered in file 9 |
| P07C1-31…58 | interrogator round 2 on file 9 | — | D-C9 D3*′ FALLS (row 38: gated cube T60_max 50.5 s); D-C1 C5″ FALLS; FM-2, FM-4 FALL | all closed in file 12 / row 86 |
| P07C1-59…86 | interrogator final check on file 12 | — | corrections 1–13 applied (10 as a report note; 11 in AX49's reversal text and the D-C9 row); row 59 settled by file 14 | closed |
| P07C1-PE-D1…D3 | plan-editor DECISIONS NEEDED (file 15) | — | D1: the AX47 ABX criterion is set in 07c-2's loop before the run (procedural deferral; L4's ≥ 12/16 recorded as precedent); D2: record (g) prints the ISM latency on T60 edits (Seat 3's own bridge condition, file 14); D3: the restore gate prints each gated scene's L_p (a record) | file 16: D1 and D3 SURVIVE WITH CORRECTIONS (DC-06, DC-07, applied: 07c-2 scope 9 clause; record (h) prints each gated scene's L_p); D2 INCONSISTENT (DC-01: the print moved from record (g) to record (h), taken after condition 9) → fixed |

| P07C1-DC-01…14 | interrogator diff check (file 16) | — | DC-01 (major: bridged ISM latency in record (h), not (g)), DC-03 (δ ≥ 8.97), DC-05 (rated corner defined in AX49, ledger label), DC-06, DC-07, DC-08 (phase-07c-1 lead sentence), DC-09, DC-10 (phase-07d), DC-11, DC-12 (ledger) all applied; DC-02, DC-04, DC-13, DC-14 CORRECT | closed |
| P07C1-F-01…30 | interrogator confirmation (file 18): D-C9 → AX49 SURVIVES WITH CORRECTIONS (row 59 closed by file 14); DC fixes confirmed; ee15c56 conforms (file 17) | — | F-23 (hook under the gate), F-25 (no free in reset; stale comments) fixed in code; F-29 (SPSC wording) to /fix-plan; F-20, F-21 fixed here; F-30 local evidence in file 17 | closed |
Decided for Maisara (open to her veto): AX47, AX48 (the "Decided" line with the synchronous tail synthesis included,
file 13 correction 10), AX49, FM-1 (AMENDS 2026-11-08), FM-2′ and FM-3′ (AMENDS 2026-11-10), FM-4′. NEEDS MAISARA: none.

### phase-07c-1 session 2 (2026-11-12; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

G2 (steward): AX38 (i) register entries closed through `/fix-plan` on three-OS evidence (records files 19, 20).

| id | item | verdict (interrogator diff check, G2) | status |
|---|---|---|---|
| P07C1-G2-01 | cond 10 worst setNonRealtime(true) 0.27/0.92, 2.22/2.50, 0.61/1.21 ms | CORRECT | closed |
| P07C1-G2-02 | cond 12 (d) 8-build quiesce 160/577/344 ms | CORRECT | closed |
| P07C1-G2-03 | cond 12 (b) class (1) queue | IMPRECISE → corrected to 153/78/94 ms over 3 runs (109/45/45 in the worst-call run) | closed (C1 applied) |
| P07C1-G2-04 | "was" figures 2 664 ms / ≈3.6 / ≈6.3 s; 1 870 ms | CORRECT | closed |
| P07C1-G2-05 | closure scope: (e) and G-1 only; half (2), interim sentence kept; boxes unticked | CORRECT | closed |
| P07C1-G2-06 | AX38 (iv) stale "(AX38 (i) release rule)" pointer | corrected (C2): the 10 s line stays with phase-13 Raise item 3 | closed |
| P07C1-G2-07 | 4c pointer to the 05i contended waits | corrected (C3): "was:" clause kept in the G-1 note | closed |
| P07C1-G2-08 | condition 12 (c) p99.9 rise with 8 builders (1 178/4 245/1 137 µs vs 195/1 674/404 µs) | recorded (C4); a finding for the board, carried to phase-07c-1b | open (07c-1b) |
| P07C1-G2-09 | run/commit attribution | corrected (C5) | closed |
| P07C1-G2-10 | AMENDS markers kept; no threshold, AX/AQ value or golden changed | CORRECT | closed |

Final status G2: SURVIVES WITH CORRECTIONS (C1–C5 applied). Files: 19, 20 (records), interrogator diff check (this row set).
