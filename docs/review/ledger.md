# Interrogation ledger

Adversarial reviews of the PRD, BUILD_PLAN and phase files against the reference corpus
(`docs/corpus/`, local only). Each section is one run of `/interrogate`. Status values:
`open` · `resolved` · `disputed`. Changes to the target documents are Maisara's decision;
this file only records findings and the builder's answers.

Citation rule: section, equation and figure numbers are the corpus files' own; where a file has
none for a passage, its nearest heading is given in quotes. No quotation exceeds 25 words.

---

## docs/BUILD_PLAN.md — 2026-11-05

Corpus: 13 files (Zotter & Frank *Ambisonics*; Begault *3-D Sound*; Roginska & Geluso *Immersive
Sound*; Izhaki *Mixing Audio*; Toole *Sound Reproduction*; Gibson *The Art of Mixing*; Rumsey
*Spatial Audio*; Vorländer *Auralization*; Blauert *Spatial Hearing* ch. 1–5). Blauert's
convention: φ = 90° is **left**.

### Issue ledger

| id | claim | evidence | severity | question | status |
|---|---|---|---|---|---|
| I1 | Phase 03 summary: "scattering removing (1−s) of specular energy" | CONTRADICTED [Auralization §3.3.2, Eq. 3.23–3.24, Fig. 3.10]: s = 1 − E_spec/E_total, so the specular path keeps (1−α)(1−s) and (1−α)s is scattered. The executable `phase-03.md` is correct; only the BUILD_PLAN summary is inverted. | ~~blocker~~ minor (round 1) | Q1 | resolved |
| I2 | AQ2: "ISM is exact for specular shoebox reflections" | OUTSIDE MODEL VALIDITY [Auralization §11.3.3]: exact only for \|R\| = 1; for absorbing walls a good approximation away from grazing incidence; small/medium rooms below 200 Hz are at the limits of geometrical acoustics. | major | Q2 | open |
| I3 | AX6: emitter ≥ 0.1 m from any surface | OUTSIDE MODEL VALIDITY [Auralization §11.3.3]: at source/receiver–wall distance ≤ λ the plane-wave reflection error is audible (> 1 dB). 0.1 m < λ up to ≈ 3.4 kHz. | major | Q2 | open |
| I4 | AX6: emitter ≥ 0.3 m from listener, rendered with one far-field HRTF | OUTSIDE MODEL VALIDITY [Immersive Sound "Appendix: Near Field"; HRTF sets usually measured at ≥ 1 m, Immersive Sound HRTF measurement section]: near-field (< 1 m) HRTFs differ significantly. | major | Q2 | open |
| I5 | AQ1/AQ3: one broadband scattering coefficient per surface | OUTSIDE MODEL VALIDITY [Auralization §3.3.2 Fig. 3.11; §11.1]: measured s is strongly frequency-dependent; modelling rule is specular below ≈ 700 Hz, scattering above. | major | — | open |
| I6 | Shoebox ISM + Eyring tail for small presets (living room, car cabin) and 63/125 Hz; preset T30 bands | OUTSIDE MODEL VALIDITY [Auralization §4.2.1 Eq. 4.13; §11.3.3]: geometrical acoustics valid above the Schroeder frequency. Preset T30 bands UNSOURCED. | major | — | open |
| I7 | Per-band Eyring T60 with air absorption; "Eyring inaccurate for uneven absorption" | SUPPORTED [Auralization §4.4.1 Eq. 4.28, 4.32; Sound Reproduction §4.1]. | minor | — | resolved |
| I8 | F3/Phase 12: "open field" = 5 surfaces α = 1 through ISM + tail | OUTSIDE MODEL VALIDITY [Auralization §4.4 diffuse-field premise; §11.3.3 grazing incidence]: a diffuse tail has no basis outdoors; the ground image is near grazing. | major | — | open |
| I9 | Statistical tail is "the standard companion" to ISM | SUPPORTED [Spatial Audio §3.2.9; Auralization §11.7; Begault "Physical Aspects of Reverberation"]. | minor | — | resolved |
| I10 | Tail energy-matched at an estimated mixing time | UNSOURCED estimator [Auralization §11.7: no simple rule for the transition time; Begault "Physical Aspects of Reverberation": 80 ms cut-off largely arbitrary]. | minor | — | open |
| I11 | Reflection factor √(1−α); 1/r; α = 1 → direct only; reflectivity = 1−α | SUPPORTED [Auralization §11.3.2 Eq. 11.36–11.37]. | minor | — | resolved |
| I12 | α ∈ [0.01, 1.0], s ∈ [0, 1] are the published-table quantities; 63 Hz band | Partly CONTRADICTED [Auralization Annex absorption tables: audience rows exceed 1; Fig. 3.11: s slightly above 1]. Annex tables start at 125 Hz, so 63 Hz values UNSOURCED. | minor | — | open |
| I13 | AQ9: T30/EDT ±10 % (≈2 JND), C80 ±2 dB (≈2 JND), 500 Hz–2 kHz | SUPPORTED for EDT (5 %) and C80 (1 dB) [Auralization §6.4.4 Table 6.1] and 1–2 JND round-robin result [§11.5]. No T30 JND in Table 6.1; its range is 500–1000 Hz. | minor | — | open |
| I14 | AQ9/AX11: T30 within ±5 % of Eyring on a seed ensemble | Self-consistency check, not accuracy. Scatter model UNSOURCED. Single-realisation scatter (4–7 % at 250 Hz) ≈ EDT JND [Table 6.1]. | minor | — | open |
| I15 | ISM ±1 sample / ±0.5 dB vs pyroomacoustics | Tolerance UNSOURCED; below the 1 dB JND [Auralization Table 6.1]. | minor | — | open |
| I16 | ITD 0.6–0.75 ms at ±90° | SUPPORTED [Blauert §2.2.2 Fig. 2.30; Spatial Audio §2.1.1; Immersive Sound Fig. 1.5]. Sign of "+90°" must be defined (Phase 08 file already requires it). | minor | — | resolved |
| I17 | Positive ILD above 2 kHz at ±90° | SUPPORTED [Immersive Sound "Sound Localization in the Horizontal Dimension"; Blauert §2.2.2 Fig. 2.24]. | minor | — | resolved |
| I18 | Phase 08: frontal median-plane source gives \|ITD\| < 20 µs | CONTRADICTED [Blauert §4.3: real heads asymmetric, median-plane interaural differences partly above threshold; Immersive Sound Fig. 1.5: measured ≈ +30 µs at 0°]. 20 µs < one sample at 48 kHz. | major | Q3 | open |
| I19 | Tail interaural coherence within ±0.1 of the diffuse-field model | Model SUPPORTED [Sound Reproduction §15.10.2 Fig. 15.6]; ±0.1 UNSOURCED; corpus IACC is max over lag [Auralization Eq. 6.13], plan uses signed coherence. | minor | — | open |
| I20 | Binaural diffuse-field energy = omni per band ±1 dB | OUTSIDE MODEL VALIDITY unless the HRTF is diffuse-field equalised [Spatial Audio §3.2.4; Blauert §2.2.3 Fig. 2.33]. | minor | — | open |
| I21 | HRIR interpolation: no step > 1 dB per 1° | Need SUPPORTED [Immersive Sound "Dynamic Source"; Spatial Audio §3.2.4]; 1 dB/1° UNSOURCED but consistent with 1 dB JND [Auralization Table 6.1]. | minor | — | open |
| I22 | Phase 08 listening: ±30° emitters "in front and out of the head" with generic HRTF, no head tracking | Frontal image CONTRADICTED in expectation [Begault "Reversals" Fig. 2.32: ≈ 46–61 % front–back reversals at ±30° with non-individual HRTFs]. Externalisation SUPPORTED with reverberation [Begault "Inside-the-Head Localization" Table 3.2]. | major | — | open |
| I23 | AX3 head faces emitter centroid; F8 "circling source sounds like nothing moves" | AX3 SUPPORTED [Auralization §11.7]. F8 overstated [Immersive Sound "Motion in a Virtual Auditory Environment"]. | minor | — | open |
| I24 | Phase 09: emitter at +55° gives the **maximum** L/R level difference | CONTRADICTED by cardioid 0.5(1+cos ϑ) [Spatial Audio §6.2.1] with ORTF ±55° [Table 6.2]: ≈ 9.7 dB at 55°, ≈ 20 dB at 90°, unbounded at 125° (rear null of the other capsule). | major | Q4 | open |
| I25 | AQ7 rationale (XTC needs sweet spot); mono sum notch ≤ 6 dB; ORTF diffuse coherence | Rationale and ORTF mono compatibility SUPPORTED [Immersive Sound "O.R.T.F"; Spatial Audio §7.2.4]. 6 dB and ORTF-coherence formula UNSOURCED. | minor | — | open |
| I26 | AQ4: IR switch by 30 ms **equal-gain** crossfade | OUTSIDE MODEL VALIDITY [Auralization §9.2.1: signal power in the overlap zone must stay constant]. Equal gain keeps power only for coherent outputs; Phase 10 corner jumps break that. | major | Q5 | open |
| I27 | ≤ 1 rebuild / 20 ms; ≤ 100 ms worst-case staleness | Corpus gives ≈ 50 ms total delay as acceptable [Auralization §15]; 100 ms exceeds it with visual feedback (Phase 11). | minor | — | open |
| I28 | AX4: fixed ISO 9613-1 atmosphere; air absorption matters above ≈ 2 kHz | SUPPORTED [Auralization §3.6 Eq. 3.33–3.35; Sound Reproduction §4.1]. 63 Hz value UNSOURCED. | minor | — | resolved |
| I29 | AX1: 30 m → 87 ms; no Doppler | 87 ms SUPPORTED [Auralization Eq. 1.20]. Omitting Doppler departs from physics [§3.7]; perceptual cost UNSOURCED. | minor | — | open |
| I30 | AX2 1/r; far → more room, less direct | SUPPORTED [Auralization Eq. 11.36; Blauert §3.3; Begault "The R/D ratio and Distance Perception"]. | minor | — | resolved |
| I31 | AX13: DRR window ±2.5 ms (Zahorik 2002) | UNSOURCED in the corpus (reference list only). | minor | — | open |
| I32 | Filterbank without ringing; flutter between parallel walls; reciprocity | SUPPORTED [Auralization §11.7 Fig. 11.41; Mixing Audio §8 "Flutter echo"; Auralization §10.1.1]. | minor | — | resolved |
| I33 | F7: photo-based HRTF is R&D | SUPPORTED in part [Immersive Sound "Customized HRTFs"]. | minor | — | resolved |
| I34 | Click detector −60 dBFS; AX5 −100 dBFS; AX9 "1 nm inaudible"; BS.1770 ±1 dB | UNSOURCED; corpus does not address them. | minor | — | open |
| I35 | Tech stack, CI, JUCE, contract format, AQ5/AQ6/AQ8, AX5/7/8/10/12, convolver accuracy, AQ10 budgets, F1/F2/F4/F9 | OUT OF CORPUS SCOPE (software engineering / product). | minor | — | resolved |

### Questions (interrogator, highest risk first)

1. **Q1 (I1).** Is each image source's specular energy multiplied by (1−s), with s going to the tail
   (Auralization Eq. 3.24), or by s as "removing (1−s)" reads? Test: α = 0, s = 0.25 on all walls; a
   first-order reflection should be 10·log10(0.75) ≈ −1.25 dB re its unscattered value.
2. **Q2 (I2–I4).** What error is accepted at the AX6 limits: emitter 0.1 m from a wall (below λ up to
   ≈ 3.4 kHz) and 0.3 m from the listener (HRTF near field)? Will Phase 03/08 raise the limits or show
   measured error there against a wave-based or near-field reference?
3. **Q3 (I18).** Does the chosen HRTF set give |ITD| < 20 µs at 0° with a sub-sample estimator at
   44.1 kHz, when measured heads show ≈ ±25–30 µs?
4. **Q4 (I24).** Is the Phase 09 criterion meant to be "level difference at +55° ≈ 9.7 dB with the
   correct sign"? "Maximum at +55°" fails by construction.
5. **Q5 (I26).** For partly decorrelated convolver outputs (Phase 10 corner jumps), does the
   equal-gain crossfade keep output power constant as Auralization §9.2.1 requires? Test: RMS dip in
   the fade window for uncorrelated outputs (≈ 3 dB at the midpoint for equal gain).

### Builder answers — round 1

**A1 (I1).** The executable spec already uses the corpus definition. `docs/phases/phase-03.md`
(Scope 1) sets the per-band pressure amplitude to the product of √(1−α) and √(1−s) per hit, i.e. the
specular *energy* keeps (1−α)(1−s), and it outputs the removed scattered energy as a separate list
that `phase-04.md` feeds into the tail onset. Its review focus states "(1−s) on energy". That is
Auralization §3.3.2 Eq. 3.23–3.24 and Fig. 3.10 (total reflected (1−α) splits into scattered
(1−α)s and specular (1−α)(1−s)). Only the one-line summary in BUILD_PLAN §4 Phase 03 is inverted.
Proposed (for Maisara): reword it to "specular energy keeps (1−s) of the reflected energy; the
scattered part s feeds the tail", and add the interrogator's test (α = 0, s = 0.25, first-order
reflection −1.25 dB ± 0.01 dB; scattered list carries 0.25 of the reflected energy) to Phase 03
acceptance. → resolved (round 1 re-check below); plan wording edit pending Maisara.

**A2 (I2–I4).** Conceded in substance. The AX6 limits are numerical guards (against 1/r blow-up),
not validity limits, and the plan conflates the two. The corpus puts audible (> 1 dB) image-source
errors at source/receiver–wall distances ≤ λ and at grazing incidence (Auralization §11.3.3), and
treats < 1 m from the head as an HRTF near field that far-field sets don't represent
(Immersive Sound "Appendix: Near Field"). v1 has no wave-based or near-field reference in its stack,
so Phase 03/08 cannot show the error at those limits. Builder proposal, needing a new AX row and
Maisara's decision: keep AX6 as hard validation limits, add a documented *validity envelope*
(emitter–listener ≥ 1 m; emitter–surface ≥ λ at 500 Hz ≈ 0.69 m) outside which renders are labelled
approximate in docs/UI, and record the limitation for the Expert. → open (decision).

**A3 (I18).** Conceded. Measured heads give ≈ +30 µs at 0° (Immersive Sound Fig. 1.5), and real
heads are asymmetric (Blauert §4.3); a dummy head such as the KU100 may be closer to symmetric, but
the corpus does not establish that. Lateralisation blur near centre is of order 10 µs
(Blauert §2.4.1 Table 2.3), so 20 µs is not a perceptual bound either. Proposal: before fixing the
Phase 08 gate, measure the 0° ITD of the converted dataset with the same sub-sample estimator; gate
on "|ITD(0°) − ITD_dataset(0°)| ≤ 5 µs" (renderer reproduces the dataset) plus "|ITD| ≤ 30 µs"
(the Phase 08 file's own per-step limit) as a sanity bound. → resolved; phase-08 edit pending Maisara.

**A4 (I24).** Conceded. With g(ϑ) = 0.5(1 + cos ϑ) (Spatial Audio §6.2.1) and capsules at ±55°
(Table 6.2), L−R is 9.66 dB at +55°, 20.0 dB at +90°, and unbounded at +125°, where the right
capsule's null lies. The maximum is not at +55°. Proposed criterion: L−R at ±55° equals the
analytic 9.66 dB within ±0.1 dB with the correct sign, mirrored; L−R increases monotonically from
0° to 90°; centre |L−R| < 0.1 dB (unchanged). → resolved; phase-09 and BUILD_PLAN edit pending Maisara.

**A5 (I26).** Conceded in part. `phase-06.md` justifies equal gain because consecutive IRs are
correlated. That holds for small moves at ≤ 20 ms update spacing, and the tail is cached and
identical when only positions change (AQ4), so the tail part stays coherent. It fails for Phase 10's
corner-to-corner jumps, where the early parts are decorrelated and power dips toward 3 dB at the
fade midpoint, against Auralization §9.2.1. Proposal: add the interrogator's measurement to Phase 10
(RMS in the fade window, corner-jump scenario, pass if dip ≤ 1 dB, the level JND of
Auralization Table 6.1). If it fails, switch to an equal-power or correlation-adaptive fade, which is
an AQ4 change and Maisara's decision. → open (decision).

**Notes on majors without a question (no change proposed by the builder; for Maisara/Expert):**
I5 and I6 are known v1 limitations of shoebox ISM + Eyring and belong in the Phase 05 report;
per-band scattering is an additive contract change (minor version) if wanted. I8: the open-field
preset should get no diffuse tail (tail level forced to zero when the room is not closed); this is
preset/engine behaviour that needs an AX row. I22: the Phase 08 listening item expects reliable
frontal images that the corpus says a generic HRTF won't deliver; the checklist should record
front–back reversals as expected rather than as a failure.

### Interrogator re-check — round 1 (open blockers only)

- **I1 → resolved; severity lowered from blocker to minor.** `phase-03.md` applies √(1−α)·√(1−s)
  to pressure per hit and exports the removed scattered energy, which `phase-04.md` feeds into the
  tail onset. That matches Auralization §3.3.2 Eq. 3.23–3.24 and Fig. 3.10. The remaining risk is a
  reader of the BUILD_PLAN summary taking "removing (1−s)" literally. Fully closed by two doc edits
  (Maisara's decision): reword the §4 Phase 03 line, and add the α = 0, s = 0.25 → −1.25 dB check to
  Phase 03 acceptance.
- **Carried to the Phase 04 review (not part of I1):** the scattered energy entering the tail per hit
  must be (1−α)·s of the incident energy (Eq. 3.23, Fig. 3.10), not s alone. The interrogator checked
  only that the list is fed in, not the bookkeeping.

No open blockers remain after round 1, so no further rounds were run.

### Unresolved after round 1

| id | severity | what is needed | owner |
|---|---|---|---|
| I2, I3, I4 | major | Decide whether to add a validity envelope (new AX row) beside the AX6 guards; v1 has no wave-based or near-field reference to measure the error at the limits. | Maisara / Expert |
| I26 | major | Add the crossfade power-dip measurement to Phase 10; if it fails, an AQ4 change (equal-power or adaptive fade). | Maisara |
| I5, I6, I8, I22 | major | No question asked this round; builder notes above. Need decisions: per-band scattering, small-room/low-band validity, open-field tail, Phase 08 frontal-image expectation. | Maisara / Expert |
| I18, I24 | major | Answered (criteria are wrong as written); replacement criteria proposed in A3/A4, awaiting edits to `phase-08.md`, `phase-09.md` and BUILD_PLAN. | Maisara |
| I1 | minor | BUILD_PLAN §4 Phase 03 wording and the added acceptance test. | Maisara |
| I10, I12–I15, I19–I21, I23, I25, I27, I29, I31, I34 | minor | Unsourced or partly contradicted tolerances; not addressed this round. | — |
