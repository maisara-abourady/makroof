# D1 — decider, round 3 of 3 (2026-11-09): answers to the plan-diff check

Method: the registered `decider` agent, answering `9-interrogator-plan-diff-check-1.md` (Q1–Q5, P08D-1 major, four minor). Verbatim. State: D1 stands; its own round-1 item 5 sentence (AC 2 reference = untrimmed resampled source) is withdrawn and replaced; substance accepted by Maisara unchanged.

---

Corpus revision: `docs/corpus/SOURCE_COMMIT` = `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d` (unchanged). PRD digest: unchanged from `4-decider-decision.md`.

Scope of this round. The head choice is accepted by Maisara (2026-11-09) and is not reopened. The interrogator's one major finding, P08D-1 INCONSISTENT, is in my own decision wording (round 1 item 5 and the plan text derived from it), not in a seat's position or an acoustic claim. By §6 of `decider.md` an INCONSISTENT load-bearing claim makes the claim fall: item 5's sentence "AC 2's reference is the pinned-resampler output of the untrimmed resampled source" is **withdrawn** and replaced below. No seat is re-rated, no cell moves, no threshold changes (AC 2 stays −60 dB; the identity test 0.1 dB; the pin-time check ±1 dB; the embed bound ≤ ~32 MB; AC 3's window 0.6–0.75 ms). Every number that is my product judgement is marked **[PJ]**.

The plan sentences quoted as "current" are from `8-plan-diff.patch` as applied to `docs/phases/phase-08.md`.

---

## Q1 (P08D-1, major INCONSISTENT) — what AC 2 compares

**Answer: (a), with one addition.** AC 2 compares the HRIRs decoded from `generic-v1.bin` against a reference built in the test from the pinned source by the converter's own pinned transformation steps with the parameters read from the `.bin` header: pinned resampler → the **stored** DF-EQ curve applied → the **stored** onsets removed → the minimum-phase step if the header says the stored form is minimum-phase. The reference is **not** trimmed and not faded. So AC 2 measures the storage and decoding path (grid subset at its stored directions, float16 or float32 quantisation, serialisation, and the lookup returning a stored direction's own HRIR) **plus the trim and fade**, which is Seat 3's purpose. There is no pre-EQ product path: the pre-EQ data is the fetched source itself, and the test applies the header's curve to it in test code; the converter and `HrtfSet` have no switch (Seat 1 §6 "exactly once", Seat 5: nothing to toggle). The EQ's own correctness is not AC 2's subject; the DF-EQ identity AC (0.1 dB) tests it.

Why the old wording could not hold (checkable arithmetic): the project's null form (`tests/unit/ConvTestUtil.h` `residualDb`, from the code: 10·log10 Σ(y−ref)²/Σref² over the reference length, y = 0 beyond its end) at −60 dB admits an amplitude error of 10⁻³, i.e. a magnitude deviation of 20·log10(1.001) = **0.0087 dB**. A set carrying the scope-3 "confirmed" residual of 1 dB differs from an un-equalised reference by 20·log10(10^(1/20) − 1) = 20·log10(0.1220) = **−18.3 dB** (the interrogator wrote ≈ −19 dB; the verdict is unchanged); even the identity bound of 0.1 dB gives 20·log10(10^(0.1/20) − 1) = 20·log10(0.01158) = **−38.7 dB**. Onset removal and a minimum-phase step change the waveform further (Begault Ch. 4 "Problems with Interpolation Algorithms", lines 1593–1597). So the reference must carry the same transformations; nothing about the size of the EQ can rescue the old sentence.

**Both seats' intents, literally.** Seat 3 §6(iv): "compares against the untrimmed resampled source, else truncation loss is invisible." Seat 5 §3/§6: "resampled and trimmed with the same pinned resampler, else the 256-tap truncation of a longer HRIR fails the gate deterministically"; "reference = pinned-resampler output, trimmed identically." AC 2 therefore reports **two residuals, both gated at −60 dB**: the **storage term** (reference trimmed and faded identically — Seat 5's gate; it cannot fail from truncation) and the **total term** (reference untrimmed — Seat 3's gate; with `residualDb` the decoded HRIR's missing tail counts as error, so truncation is visible). If the total fails while the storage term passes, the cause is truncation (trim length or the scope-2 fade), reported as such; the response is a converter change or a challenge through the interrogator, never a loosened gate. For SADIE II the truncation term is expected near zero because the source is already 512 samples at 96 kHz = 256 at 48 kHz with 10-sample fades (dossier F12, D1-L4); that expectation is measured, not assumed. Seat 5's and Seat 3's (rfc) cells are unchanged.

**Plan wording.**

Scope 2, current:
> "AC 2's reference is the pinned-resampler output of the **untrimmed** resampled source (for SADIE II this equals the trimmed one: York already trimmed to 512 samples at 96 kHz with fades)."

Replace with:
> "**AC 2 measures the storage and decoding path plus the trim**, not the converter's transformations: its reference is built in the test from the pinned source by the converter's own pinned steps with the parameters read from the `.bin` header (pinned resampler; the **stored** DF-EQ curve applied; the **stored** `onset_left`/`onset_right` removed; the minimum-phase step if the header says the stored form is minimum-phase). Two residuals in the `residualDb` form (10·log10 Σ(decoded − reference)² / Σ reference² over the reference length, decoded = 0 beyond its end), per ear, stored direction and rate, both gated at −60 dB: the **storage term**, against that reference trimmed and faded identically (it cannot fail from truncation), and the **total term**, against the same reference left **untrimmed and unfaded**, so the energy the trim and fade remove counts as error. A total failure with the storage term passing is a truncation finding (trim length or fade), reported and handled through the interrogator, never by loosening a gate. For SADIE II the truncation term is expected near zero (York trimmed to 512 samples at 96 kHz = 256 at 48 kHz, with fades; dossier F12) and is measured, not assumed. The EQ's correctness is the DF-EQ identity AC's subject, not AC 2's; the pre-EQ data exists only as the fetched source and inside the test, and no product code path switches the EQ off."

AC 2, current:
> "- [ ] Converter round-trip: HRIRs decoded from `generic-v1.bin` match the pinned-resampler output of the untrimmed resampled SOFA source within −60 dB at every stored (measured) direction. The source is fetched by checksum (scope 1); the test skips with a marker when it is absent unless `SPATIAL_REQUIRE_HRTF_SOURCE=1` (CI)."

Replace with:
> "- [ ] **Converter round-trip (storage and decoding):** at every stored direction, each ear and each of the four rates, the HRIR decoded from `generic-v1.bin` is within −60 dB (`residualDb`) of the reference built in the test from the pinned SOFA source by the converter's pinned steps with the header's parameters (pinned resampler, stored DF-EQ curve, stored onsets, minimum-phase step if recorded) — **both** against that reference trimmed and faded identically (storage term) **and** against it untrimmed and unfaded (total term; truncation loss counts). The test prints both terms' worst values per rate. The source is fetched by checksum (scope 1); the test skips with a marker when it is absent unless `SPATIAL_REQUIRE_HRTF_SOURCE=1` (CI). The DF-EQ curve's correctness is tested by the DF-EQ identity AC, the onset estimator by AC 3, the interpolation by AC 4; AC 2 tests none of them."

Contractor review focus, current "the Voronoi-weighted DF-EQ / coherence averages with the identity test," → "the Voronoi-weighted DF-EQ / coherence averages with the identity test, the two-term AC 2 reference (header parameters, untrimmed total term),".

---

## Q2 (P08D-15) — power or dB-magnitude average

**Answer: a power average**, in every place the plan says "weighted one-third-octave average": per ear and band b, L_b = 10·log10(Σ_i w_i · P_{i,b}), with P_{i,b} the mean of |H_i(f)|² over the bins of one-third-octave band b and w_i = Ω_i/4π. Basis: D1-L15: Begault line 1489 averages "random" incidence noise levels in third-octave bands (energy); Vorländer line 4004, random incidence of incoherent waves (incoherent superposition adds power); dossier F19 (MIT's diffuse set: "power-spectrum average over all directions") is the same construction. The DF-EQ curve is C_b = L_b of the source; the converter applies −C_b (its filter realisation, zero- or minimum-phase, is recorded in the header). No dB-magnitude averaging anywhere. The identity AC then holds in **every band of the converter's curve** by construction (D1-L16), so the band set is recorded in the header and the AC runs over all of it.

**Plan wording.**

Scope 3, current:
> "per ear (DF curve) / per band (coherence target) in one-third-octave bands, stored in the `.bin` header"

Replace with:
> "per ear (DF curve) / per band (coherence target), **as power averages** in one-third-octave bands — L_b = 10·log10(Σ_i w_i · P_{i,b}), P_{i,b} the band-b mean of |H_i(f)|² (Begault Ch. 4 'Equalization of HRTFs': random-incidence noise levels in third-octave bands; Vorländer §16.1.1: incoherent waves) — the DF-EQ curve being C_b of the source and the converter applying −C_b (filter realisation recorded in the header; the band set recorded in the header), stored in the `.bin` header"

Scope 3 (iii), current:
> "(iii) the post-EQ check: the weighted one-third-octave average of the converted set is 0 dB within 0.1 dB in every band (automated test, the DF-EQ identity AC; a numerical identity bound, one tenth of the level jnd)."

Replace with:
> "(iii) the post-EQ check: the weighted one-third-octave **power** average L_b of the converted set (per ear) is 0 dB within 0.1 dB in every band of the converter's curve (automated test, the DF-EQ identity AC; a numerical identity bound, one tenth of the level jnd)."

Scope 3 pin-time check, current "if the computed curve on the pinned `D1_HRIR_SOFA.zip` lies within ±1 dB" → "if the computed curve C_b on the pinned `D1_HRIR_SOFA.zip` lies within ±1 dB".

DF-EQ identity AC, current:
> "- [ ] **DF-EQ identity:** the solid-angle-weighted one-third-octave average of the converted set is 0 dB within 0.1 dB in every band (scope 3)."

Replace with:
> "- [ ] **DF-EQ identity:** the solid-angle-weighted one-third-octave **power** average of the converted set, L_b = 10·log10(Σ_i w_i P_{i,b}) per ear (scope 3), is 0 dB within 0.1 dB in every band of the converter's curve."

---

## Q3 (P08D-3) — one arithmetically consistent bound

**Working** (decimal MB, 1 MB = 10⁶ B, the unit the patch's "≈ 104 MB" already uses: 11 784 B × 8802 = 103 722 768 B). Per direction, four-rate float32: taps 235 + 256 + 470 + 512 = 1473, × 2 ears × 4 B = **11 784 B**; float16: **5 892 B**. Payload ceiling at 32 MB: 32·10⁶ / 11 784 = 2715 directions in float32; / 5 892 = 5431 in float16. 2700 × 11 784 = 31 816 800 B = **31.8 MB**; 3000 × 11 784 = **35.4 MB** (over); 3000 × 5 892 = **17.7 MB**. Non-payload parts at V = 2700 are of the order of 0.1 MB (a sphere triangulation has 2V − 4 = 5396 triangles × 3 indices × 4 B = 65 kB; weights 11 kB; onsets 22 kB; curves a few kB), which is what the "~" covers; hence ≤ ~2700, not 2715.

**Answer:** the float32 direction bound is **≤ ~2700**, not 3000; "and/or" becomes "either … or". The 3000 figure survives only as the **float16** subset size, and that count is a product choice **[PJ]** (of the order of a 2702-node full-sphere grid, the size Seat 5 §3 rated 1 for option (d)); the bound itself is bytes. Seat 5's condition (≤ ~3000 directions, or decimate/float16 with −60 dB held) is met by either route; its cell (rfc) is unchanged.

**Plan wording.** Scope 2, current:
> "The committed four-rate `.bin` is ≤ ~32 MB (the full 8802-direction grid in four-rate float32 would be ≈ 104 MB): a grid subset of ≤ ~3000 directions that keeps the lowest measured elevation row (−81°) and the 0°-elevation ring, and/or float16 storage, chosen in this phase so that AC 2 (−60 dB) and AC 4 (continuity) hold on the real file."

Replace with:
> "The committed four-rate `.bin` is ≤ ~32 MB (32·10⁶ B, whole file; the full 8802-direction grid in four-rate float32 would be ≈ 104 MB). Four-rate float32 costs 11 784 B per direction (1473 taps × 2 ears × 4 B), float16 5 892 B, so the bound holds for **either** a float32 grid subset of **≤ ~2700 directions** (31.8 MB; 3000 would be 35.4 MB) **or** a float16 grid subset of **≤ ~3000 directions** (17.7 MB; the count is a product choice near a 2702-node full-sphere grid, the bound is the bytes). Either subset keeps the lowest measured elevation row (−81°) and the 0°-elevation ring; the route is chosen in this phase so that AC 2 (−60 dB, both terms) and AC 4 (continuity) hold on the real file."

(The round-1 decision text's item 4 "≤ ~3000 directions … and/or float16" is superseded by this wording; the decision records are not edited.)

---

## Q4 (P08D-5/6) — does the AC 3 window presuppose an onset estimator; the low-frequency sentence

**Answer: yes.** The window 0.6–0.75 ms is sized to the onset ITD: Blauert Ch. 2 §2.2.2 line 237, Fig. 2.30 — onset-ITD of brief rectangular pulses ≈ 650 µs at 90°; line 233, far-source ΔS = (D/2)(φ + sin φ) with D = 17.5 cm (line 222): 0.0875 × 2.5708 = 0.2249 m → 0.656 ms at 343 m/s. Other estimator classes read higher: Blauert line 226 (sphere model) interaural phase and group delay "up to about 0.6–0.8 ms"; Roginska & Geluso Ch. 1 line 959: ≈ 650 µs, "750 µs for low-frequency sounds (Kuhn, 1977), depending on stimulus and measurement technique". The corpus nowhere names cross-correlation as the larger-valued method; the word goes. So the estimator the loop names must be of the **onset (pulse-arrival) class** — the converter's per-ear onset detection that yields `onset_left`/`onset_right`, run on the resampled HRIRs before any EQ or onset removal **[PJ: ordering, so that the stored onsets are a property of the measurement and the EQ filter's own delay does not enter]**, and the same criterion applied by the test to the rendered anechoic output — with its threshold relative to the ear's peak and the sign convention still to be named before the first measurement (as the plan says; I do not name the threshold now, no source gives one). If the loop chose another class (phase delay, cross-correlation), the window would have to be derived for it from the corpus before measuring, never this one widened.

**Plan wording.** AC 3, current:
> "The onset/ITD estimator (and the sign convention) is named in this AC by the decision loop **before the first measurement**; if the pinned file measures outside 0.6–0.75 ms, the window is challenged on that evidence through the interrogator, never widened to pass (decider challenge C-1: York's own ITD plots read ≈ 0.85 ms for D1 by an unstated method, dossier F21; a low-frequency/cross-correlation ITD exceeds an onset ITD, Roginska & Geluso Ch. 1). Not a head reversal."

Replace with:
> "The window 0.6–0.75 ms **presupposes an onset (pulse-arrival) estimator**: it is sized to the onset ITD of brief pulses, ≈ 650 µs at 90° (Blauert Ch. 2 §2.2.2, Fig. 2.30), and to the far-source path difference (D/2)(φ + sin φ) = 0.656 ms for D = 17.5 cm. The estimator is therefore of the onset class — the converter's per-ear onset detection that yields `onset_left`/`onset_right`, run on the resampled HRIRs before EQ and onset removal, and the same criterion applied by the test to the rendered anechoic output — and its exact criterion (threshold relative to the ear's peak) and the sign convention are named in this AC by the decision loop **before the first measurement**. A low-frequency ITD (≈ 750 µs for an average human head) exceeds the broadband onset ITD (≈ 650 µs); the value depends on stimulus and measurement technique (Roginska & Geluso Ch. 1; Blauert Ch. 2 §2.2.2: the sphere model's interaural phase and group delay reach about 0.6–0.8 ms), so an estimator of another class would need its own window derived from the corpus before measuring — never this one widened. If the pinned file measures outside 0.6–0.75 ms with the named onset criterion, the window is challenged on that evidence through the interrogator, never widened to pass (decider challenge C-1: York's own ITD plots read ≈ 0.85 ms for D1 by an unstated method, dossier F21). Not a head reversal."

Risks, current:
> "- AC 3's ITD window may fail as worded on the SADIE heads (York's plots read ≈ 0.85 ms by an unstated method). Not a head reversal: name the estimator first, then challenge the window through the interrogator on the measurement (C-1)."

Replace with:
> "- AC 3's ITD window may fail on the SADIE heads (York's plots read ≈ 0.85 ms by an unstated method; a low-frequency estimator reads higher than an onset estimator). Not a head reversal: name the onset criterion first, then challenge the window through the interrogator on the measurement (C-1)."

---

## Q5 (P08D-22) — "the same either way": state, not signal

**Answer: the state.** By D1-L16 the converted set's weighted band averages are 0 dB in every band whatever direction-independent equalisation the source carried (Blauert Ch. 4 line 519: an equaliser is H₂(f)), so the *state* the identity AC checks is the same either way. The *signal* is not the publisher's: the converter's weighted normalisation replaces, band by band, whatever equalisation York applied, and the independence from York's curve holds in the band-averaged sense only (fine structure within a band is not removed). A "not confirmed" result therefore means the shipped set departs from York's published equalisation by the reported curve, which is exactly why the rebuttal routes it to Maisara and the interrogator before any golden is frozen.

**Plan wording.** Risks, current:
> "The converted output is the same either way (the set's own weighted curve is always applied)."

Replace with:
> "The converted set's **state** is the same either way — weighted one-third-octave power average 0 dB in every band, by construction (the DF-EQ identity AC) — but not its **signal**: the converter's weighted normalisation replaces, band by band, whatever direction-independent equalisation the source carried, so a 'not confirmed' result means the shipped set differs from York's published equalisation by the reported curve. That is why it is raised before any golden is frozen."

---

## P08D-21 (minor, no question) — "above"

The corpus supports in-head localisation (Begault Ch. 3 line 1109: IHL 25 % → ~3 % with reverberation) and front–back confusion with median-plane uncertainty for dummy heads (Vorländer §6.3.2 line 1967); an upward bias for dummy heads is not in it. Checklist, current:
> "(Generic HRTFs are heard "inside" or "above" by some people. Note what you hear; that's what B4 is for.)"

Replace with:
> "(Generic HRTFs are heard inside the head, or reversed front/back, by some people, and height on the median plane is uncertain (Begault Ch. 3; Vorländer §6.3.2). Note what you hear; that's what B4 is for.)"

The forced-choice answer set keeps "above" as an answer option; that is a category for the listener, not a claim.

---

## Bookkeeping for the plan-editor

- `docs/BUILD_PLAN.md` §6: add a row (2026-11-09): "D1 plan-diff check corrections (interrogator `9-interrogator-plan-diff-check-1.md`, decider round 3): phase-08 AC 2 redefined as a two-term storage/decoding round-trip (reference built from the header's parameters; storage term trimmed identically, total term untrimmed; both −60 dB); scope 2 embed bound restated as float32 ≤ ~2700 or float16 ≤ ~3000 directions (11 784 / 5 892 B per direction); DF-EQ averages stated as power averages; AC 3 window stated to presuppose an onset estimator, 'cross-correlation' removed; Risks 'same either way' → state, not signal; checklist 'above' restated. No threshold, golden or contract changed." The existing 2026-11-09 D1 row is history and is not edited.
- `docs/THIRD_PARTY.md`, the BUILD_PLAN §1 "Generic HRTF" row and AX35: no change.
- The decision records `4-decider-decision.md` and `6-decider-rebuttal.md` are not edited; items 4 and 5 of round 1 are superseded by the wording above.

## Load-bearing claims added or amended this round

| id | claim | kind | source / working |
|---|---|---|---|
| D1-L18 | At −60 dB the `residualDb` null admits an amplitude error of 10⁻³ (0.0087 dB of magnitude); a 1 dB magnitude difference reads −18.3 dB, 0.1 dB reads −38.7 dB; hence AC 2's reference must carry the stored EQ, onsets and minimum-phase step. | derived (arithmetic) + code | `tests/unit/ConvTestUtil.h` `residualDb` (from the code); 20·log10(10^(x/20) − 1) for x = 1, 0.1 |
| D1-L19 | Four-rate float32 = 11 784 B/direction, float16 = 5 892 B; 32·10⁶ B holds ≤ 2715 (float32) / 5431 (float16); 2700 → 31.8 MB, 3000 → 35.4 MB (float32), 17.7 MB (float16); non-payload ≈ 0.1 MB at V = 2700 (2V − 4 triangles). | derived | phase-08 scope 2 (256 taps at 48 kHz, scaled); D1-L5 redone; Euler for the triangulation |
| D1-L20 | The AC 3 window is sized to the onset ITD (≈ 650 µs; 0.656 ms for D = 17.5 cm); a low-frequency ITD is ≈ 750 µs and the sphere model's phase/group delay reaches 0.6–0.8 ms; the corpus does not name cross-correlation as the larger-valued method. | corpus + derived | `blauert-ch2-one-sound-source.md` lines 222, 226, 233, 237 (Fig. 2.30); `roginska-geluso-immersive-sound.md` line 959 |
| D1-L21 | The diffuse-field average is a power average Σ w_i P_{i,b} per one-third-octave band. | corpus (D1-L15 restated) | Begault line 1489; Vorländer line 4004; dossier F19 |
| D1-L22 | "Same either way" holds for the converted set's state (band averages = 0 dB) for any direction-independent source EQ, in the band-averaged sense; not for the signal. | derived from D1-L16 | Blauert Ch. 4 line 519; interrogator round 2 §5 condition |
| D1-L23 | For SADIE II the truncation term is expected near zero (source already 512 samples at 96 kHz with fades); measured, not assumed. | verified source (proxy) | dossier F12; D1-L4 |

Product judgements this round **[PJ]**: the float16 subset count ~3000; the onset estimator running before EQ and onset removal; both AC 2 terms gated (rather than one gated, one reported). None changes which head wins or any seat's cell.

## Tension map and ordering

No option cell changes. Seat 3's (rfc) cell rests on §6(iv) (untrimmed reference) — met by the total term; Seat 5's (rfc) cell rests on §6 (pinned resampler, trimmed identically; fetch by checksum; skip marker) — met by the storage term and scope 1; Seat 1's cell on §6 ("records the set's equalisation state … applies DF-EQ exactly once") — met: no switch, one application, identity AC. (a′) stays max 1 / sum 16; (d) out at bounds; no veto.

## State

**D1 stands; wording revised.** The INCONSISTENT item (my round-1 item 5 / the AC 2 reference sentence) is withdrawn and replaced; the four IMPRECISE items are restated as above. Nothing Maisara accepted changes in substance: same head, same licence, same AX35, same gates and thresholds (−60 dB, 0.1 dB, ±1 dB, ≤ ~32 MB, 0.6–0.75 ms). For Maisara, if wanted: "The plan's test for the stored headphone data now compares like with like (the file's own stored corrections applied to the reference, with the trimmed-off tail still counted), and the size target is stated so that the arithmetic adds up; nothing you accepted changes."
