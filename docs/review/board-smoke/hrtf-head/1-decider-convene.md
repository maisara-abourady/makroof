# D1 (dry run) — decider, convening round (2026-11-09)

Method: the registered `decider` agent, told to re-read `.claude/agents/decider.md` (rewritten this session) and follow it. Verbatim report follows.

---

# D1 — Generic HRTF `generic-v1`: convening round

Corpus revision: `docs/corpus/SOURCE_COMMIT` = `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d` (14 files, all ten books present, no extra files).

## PRD digest

- **For whom:** music producers and DJs on macOS/Windows, any DAW, who do not understand spatial audio (PRD "Target users"). They describe a space; the plugin translates.
- **Outcome:** a track rendered as if played in the designed space, in binaural (headphones) or stereo-speaker mode (FR-SIM-3); in headphone mode the stereo image of ±30° emitters must sit in front and outside the head (phase-08 listening checklist); automation follows without artifacts (FR-SIM-6).
- **Hard constraints (bounds):** AQ6 one generic HRTF, `hrtfId = "generic-v1"`, no personalisation in v1 (B4 deferred); AX3 yaw-only head facing the emitter centroid; AX5 determinism; AX6 emitter ≥ 0.3 m from the listener; NFR-8 / FR-SIM-2 no scene-specific logic; phase-08 scope 1: licence read on the official site before any data is committed, "Don't ship data under an unclear licence", else `blocked`; contract rules (`hrtfId` is a schema `const`, from `docs/contract/scene-v1.schema.json:81`); CLAUDE.md: third-party data pinned by checksum, originals never committed, every dependency and licence in `docs/THIRD_PARTY.md`; PRD out of scope: head tracking, head orientation control; AQ10 rebuild budget (every output mode from Phase 08); AX31 reversal clause open for phase-08 item 8 (head-rotation row).
- **Settled decisions touching D1:** AQ6 (Maisara: no personalisation); BUILD_PLAN §1 "Generic HRTF" row names SADIE II KU100 or KEMAR with MIT KEMAR as fallback, licence to be verified in Phase 8; F7 (SOFA import is the realistic first personalisation step, B4).
- **Verification culture:** every DSP behaviour automatically checked (phase-08 ACs: converter round-trip −60 dB, ITD 0.6–0.75 ms at ±90°, ILD > 6 dB over 2–8 kHz, 1° continuity ≤ 1 dB / ≤ 30 µs, tail coherence ±0.1, energy ±1 dB); independent references over self-made goldens; goldens never regenerated to pass.
- **PRD silence:** the PRD says nothing about which head, headphone equalisation (ledger P7, context only), or the listener's head size; it asks for a *personalised* profile (FR-SIM-4), which AQ6 defers.

## 1. The matter

**Restatement.** Choose the measured dummy-head dataset that `tools/hrtf/convert_sofa.py` turns into `resources/hrtf/generic-v1.bin`, the one head every binaural render in v1 uses (AQ6). Depends on it: the licence file and `docs/THIRD_PARTY.md` row (AC 1), the converter's resampling/trimming/grid/triangulation and diffuse-field EQ (scope items 2–3), `HrtfSet::query`, the tail-coherence target curve computed from the set (scope 5), the ITD/ILD and continuity gates (ACs 3–4), the listening-pack and goldens for three scenes, and the B4 path (a personalised SOFA later replaces this set through the same converter). From the code: `contract::kHrtfIdGenericV1 = "generic-v1"` (`src/contract/SceneDescription.h:159`), `Validate.cpp:218` rejects any other id (E_HRTF_ID); nothing exists yet under `tools/hrtf/`, `resources/hrtf/` or `src/sim/hrtf/`.

**Options on the table.**
- (a) SADIE II, KU100 subject (University of York), 48 kHz SOFA.
- (b) SADIE II, KEMAR subject.
- (c) MIT KEMAR (Gardner & Martin 1994; the phase file's licence fallback).
- (d) *Mine, minimal variant:* TH Köln KU100 set (named in the corpus as the KU100 HRIR source used by the IEM BinauralDecoder, with optional headphone-EQ curves: Zotter & Frank, abbreviations table rows "KU100", "TH Köln" and the Ch. 4 BinauralDecoder note). Same head as (a), different measurement campaign; its licence and grid are outside the corpus. Added so that "KU100" is not tied to one campaign if (a)'s licence fails.
- Not an option but a **condition seats may rate**: whatever set is chosen, the converter and the `generic-v1.bin` header stay dataset-agnostic (set identity, sample rate, grid, EQ state recorded in the header), so the set can be swapped without touching `src/sim`.

**Bounds check before convening.** No option can be dropped yet: the only hard rule that could exclude one (the licence rule, phase-08 scope 1) depends on facts nobody in the loop has verified (K1–K4 below). Nothing in the corpus shows any option WRONG.

## 2. Convening table (nine rows)

| Seat | Convened / not required | Reason (table item touched) | Brief |
|---|---|---|---|
| 1 Perceptual gatekeeper | **convened** (PRD-priority seat: what the user hears) | "audibility of a detail", "any claim of realism/plausibility", "acceptance tests for other seats": is the head-vs-torso difference (KU100 vs KEMAR) audible to the target listener in a static, untracked, room-included render; which bar (plausibility) applies; are the phase-08 ITD/ILD/continuity gates the right perceptual gates for the chosen head; listening-checklist wording | B1 |
| 2 Engine architect | **convened, narrowly** | "validation against measured rooms (BRAS, round robins)" and "the representation handed to the renderer": does the head choice keep or lose a path to compare binaural renders with measured BRIRs (B9, Q9); does the set's direction grid (lowest elevation, density) cover every image-source direction the ISM produces under AX3 | B2 |
| 3 Reverb renderer | **convened** | "early-reflection rendering", "time variance under motion" (yaw follows the centroid, AX3: interpolation between grid points as azimuth sweeps), "coloration", "per-instance CPU" (HRIR taps × image count in the BRIR build, AQ10) | B3 |
| 4 Chain keeper | **convened** (owner of the matter) | "HRTF dataset choice and licence; headphone compensation; externalisation" | B4 |
| 5 Deadline keeper | **convened** (PRD-priority seat: audio thread, CI gates) | "CI gates" (AC 1 licence script, round-trip gate), "offline equals real-time" (embedded data identical on all platforms, AX5), plugin binary size and load time of the embedded set, "review of real-time code" (HrtfSet lookup must not allocate if ever called near the audio thread) | B5 |
| 6 Canvas designer | **convened, narrowly** (PRD-priority seat: the user's controls) | "presets and profiles" (the head *is* the v1 profile, AQ6; B4 adds a selector later), "names ... defaults" (whether the UI ever names the head), "time-to-first-plausible-scene" on headphones | B6 |
| 7 Founder | **convened** (PRD-priority seat: cost) | "licensing", "public wording and marketing claims" (naming "Neumann KU100"/"KEMAR"), "schedule and complexity cost" of a fallback or a later swap, "what one founder can sustain" (licence compliance, attribution in the product) | B7 |
| 8 Storyteller | **convened** | "whose ears the audience hears through"; translation to the listener's chain (headphones vs the producer's speakers) | B8 |
| 9 Room acoustician | **convened, narrowly** | "preset validation against measured rooms" (are any reference BRIRs of BRAS/Arni/dEchorate measured with one of these heads), "diagnosing complaints" (colouration blamed on the room that comes from the head) | B9 |

All nine are convened; the three narrow ones are cheap `NOT MY MATTER` answers if the seat sees nothing.

## 3. Briefs (to be passed on verbatim)

**Common part (every brief).** Matter: which measured dummy-head set becomes the plugin's one generic HRTF `generic-v1` (AQ6). Options (a) SADIE II KU100 48 kHz SOFA; (b) SADIE II KEMAR; (c) MIT KEMAR; (d) TH Köln KU100 (decider's variant). Condition to rate as well: the converter and the `.bin` header stay dataset-agnostic so the set can be swapped later without touching `src/sim`. Read: `docs/PRD.md` (FR-SIM-3, FR-SIM-4, FR-3D-9, A1, out-of-scope list, NFR-1, NFR-2), `docs/BUILD_PLAN.md` §1 row "Generic HRTF", §2 AQ6, AX3, AX5, AX6, AQ10, §3 F7, F8, §5 B4, B9; `docs/phases/phase-08.md` in full; `docs/THIRD_PARTY.md` "Planned"; the researcher's dossier for D1 when it arrives (licence terms, grid, distance, equalisation state, ITD per set). Corpus passages that bear on the heads: Begault Ch. 4 "Dummy heads for measurement and recording" (KEMAR head-and-torso, Burkhard & Sachs; KU-100 diffuse-field equalised, symmetric pinnae), Begault Ch. 4 MIT KEMAR description (1.4 m, 44.1 kHz, 710 positions, elevations −40° to +90°); Roginska & Geluso Ch. 4 device types (KU-100 head without torso, "missing shoulders may weaken elevation cues"; KEMAR head and torso); Rumsey §3.2.4 (torso reflections differ between individuals, a confusing cue unless matched; KU100 near Theile's diffuse-field response); Blauert Ch. 4 Theile's diffuse-field equalisation of dummy heads; Vorländer §9.5 (standard HRTF distance-independent only beyond 1 m; AX6 allows 0.3 m) and §16.1.2 (dummy heads: front–back confusion for a large portion of subjects; individual filters cut errors mainly above 6 kHz); Blauert Ch. 2 Fig. 2.30 (human onset ITD ≈ 650 µs at 90°); Zotter & Frank Fig. 4.25(b) (KU100 TH Köln arrival-time curve) and the IEM BinauralDecoder note (KU100 data). Rate every option, and the dataset-agnostic condition, for tension now and later (0–3), give conditions of acceptance for any 2 or 3, and name anything you want the researcher to verify. Do not invent dataset facts: if the licence, grid, distance or equalisation state is not in the dossier, say `[Hyp]`.

**B1 (Seat 1).** Rate: whether a listener of the target group, static, no head tracking (PRD out of scope), room included, hears a difference between a head-only set (KU100) and a head-and-torso set (KEMAR) in (i) front/back and elevation confusion, (ii) externalisation, (iii) colouration; under which bar (plausibility vs authenticity) the v1 headphone render is judged; whether the phase-08 gates (ITD 0.6–0.75 ms at ±90°, ILD > 6 dB over 2–8 kHz, 1° steps ≤ 1 dB / ≤ 30 µs) are perceptual gates or only sanity checks for the chosen head, and whether any depends on the head's size (Begault Ch. 4: head size "probably a major factor"); what listening-checklist wording lets Maisara report what she hears without blaming the room. Hand-offs: which controls (6); listening panel (a human).

**B2 (Seat 2).** Rate narrowly: (i) whether the choice keeps or loses a comparison path between the binaural render and measured BRIRs (B9; which head, if any, the project's reference datasets use is a researcher fact); (ii) whether each set's grid covers the image-source directions the ISM produces under AX3 (upright head; floor images can lie far below the horizon: elevation → −90° as the horizontal distance to the floor image shrinks), given MIT KEMAR stops at −40° (corpus) and SADIE's lowest elevation is unknown; what the renderer must do below the grid (extrapolate, clamp, mirror) and what that does to a physical-accuracy claim. Otherwise `NOT MY MATTER`.

**B3 (Seat 3).** Rate: grid density and HRIR length per set against the continuity gate (1° azimuth steps ≤ 1 dB, ≤ 30 µs) under barycentric interpolation of onset-removed HRIRs with ITD re-applied as a fractional delay (phase-08 scope 3); truncation to 256 taps at 48 kHz (scope 2) against each set's HRIR length (loss, LF ringing); colouration of the chosen head after diffuse-field EQ; BRIR build cost per image source and the 2° grouping rule above order 3 against AQ10 (W1/W2 in every output mode from Phase 08); any time-variance risk when yaw follows the centroid (AX3) and the set changes. Hand-offs: externalisation/HRTF licence (4); thread topology (5).

**B4 (Seat 4).** This is your matter. Rate each option for: binaural architecture fit (raw vs equalised data, microphone position: ear-canal entrance vs ear-canal end, which decides whether ear-canal resonance must be equalised out, Rumsey §3.2.4); diffuse-field equalisation computed in the converter (phase-08 scope 3) vs equalisation already in the set; externalisation and front/back expectations for a static render; measurement distance against AX6's 0.3 m minimum (Vorländer §9.5: standard HRTF valid beyond 1 m; near-field correction is a phase-08 follow-up); the licence path (commercial redistribution of *derived* data, attribution text in `resources/hrtf/LICENSE-generic-v1.txt` and `docs/THIRD_PARTY.md`); what the choice commits B4 (personalised SOFA import) to, and what a later swap costs. Give the conditions under which (c) is acceptable if (a)/(b) fail on licence. Hand-offs: licence law (a human); pricing (7); controls (6); audibility (1).

**B5 (Seat 5).** Rate: AC 1's CI script (`.bin` without matching `LICENSE-*.txt` fails) and the round-trip gate (−60 dB) as non-flaky gates per set; embedded binary size per set at four sample rates (grid × taps × rates) and its effect on plugin load time, memory and the installer; determinism (AX5: the embedded set is identical on all platforms; the converter's resampler must be pinned and reproducible); whether `HrtfSet::query` can be kept allocation-free and off the audio thread (BRIR build is on the IR-builder thread, AX33). Hand-offs: DSP design (3); pricing (7).

**B6 (Seat 6).** Rate narrowly: whether the chosen head should ever be named in the UI or stay hidden (AQ6: one set, no control); whether headphone mode needs a default-experience note (front/back confusion expected, phase-08 checklist) and how B4's later profile selector would present "generic" beside a personal profile; time-to-first-plausible-scene on headphones. Otherwise `NOT MY MATTER`. Hand-offs: audibility (1); what sells (7).

**B7 (Seat 7).** Rate: licence risk and compliance cost per option (commercial redistribution of converted data; attribution obligations shipped in a paid plugin; share-alike or non-commercial clauses would be stops); use of the names "Neumann", "KU100", "KEMAR", "SADIE" in marketing or the UI (trademark: hand to a lawyer, but rate the exposure); schedule cost of the fallback path (phase-08 scope 1: if neither is clearly allowed, the phase blocks) and of a later swap; whether any option creates a recurring obligation one founder cannot sustain. Hand-offs: licence text (lawyer); realism claims (1).

**B8 (Seat 8).** Rate: through whose ears a producer's audience should hear the scene in v1 (a recording-oriented head designed for loudspeaker/headphone compatibility, KU100, vs a measurement-oriented head-and-torso, KEMAR); what each does to depth, anchor and front image for a static listener who always faces the emitters (AX3, F8); translation when the producer checks the binaural render on speakers; whether the choice affects any workflow (it is hidden, AQ6). Hand-offs: thresholds (1); rendering (3); delivery (4).

**B9 (Seat 9).** Rate narrowly: whether any room reference the project uses or plans (BRAS CR2–CR4, Arni, dEchorate, B9) holds BRIRs measured with one of these heads, so that one option keeps a measured binaural comparison and the others lose it (a researcher fact; mark `[Hyp]` if unknown); how a head's colouration would show up in a complaint about a preset ("boxy", "thin") and how to separate it from the room. Otherwise `NOT MY MATTER`.

## 4. Knowledge inventory, first pass

| K | What must be known | Source | Status |
|---|---|---|---|
| K1 | SADIE II licence: exact terms for commercial redistribution of *derived* (converted, resampled) data; attribution text; whether KU100 and KEMAR subjects share one licence; record version/DOI | researcher (outside corpus); phase-08 scope 1 names the rule | **uninformed** |
| K2 | MIT KEMAR licence terms, same questions | researcher; Begault Ch. 4 gives the dataset's description and address but no licence | **uninformed** |
| K3 | TH Köln KU100 set licence and attribution (variant d) | researcher; corpus names the set only (Zotter & Frank) | **uninformed** |
| K4 | Whether "Neumann", "KU100", "KEMAR", "SADIE" may be named in product/marketing text | researcher → lawyer (seat 7 hands off) | **uninformed** |
| K5 | Per set: sample rate, HRIR length, number of directions, grid type, lowest elevation, left–right symmetry, SOFA convention, file size and checksum | MIT KEMAR partly in corpus: 1.4 m, 44.1 kHz, 710 positions, elevations −40° to +90°, ML sequences (Begault Ch. 4 "KEMAR HRTF measurements ... MIT's Media Lab"); SADIE II / TH Köln: researcher | **under-informed** (one option partly known) |
| K6 | Per set: measurement distance, against Vorländer §9.5 (standard HRTF valid beyond 1 m) and AX6 (0.3 m allowed) | corpus for the condition; MIT 1.4 m from corpus; SADIE / TH Köln distance: researcher | **under-informed** |
| K7 | Per set: equalisation state of the stored HRIRs (raw at the microphone, diffuse-field, free-field, headphone-compensated) and microphone position (ear-canal entrance vs ear-canal end) | Begault Ch. 4 and Rumsey §3.2.4 say the KU100 *as a recording head* is diffuse-field equalised and measurement heads include ear-canal resonance; whether the SOFA files store raw or equalised data is a dataset fact: researcher | **under-informed** |
| K8 | Per set: onset ITD at ±90°, 0° elevation, by the onset method the phase will use, against the AC window 0.6–0.75 ms | Blauert Ch. 2 Fig. 2.30: human ≈ 650 µs at 90°; Zotter & Frank Fig. 4.25(b): KU100 single-ear arrival spans ≈ −0.25 … 0.6 ms over azimuth (not an ITD at one azimuth); per-set value: researcher or measured in the phase | **under-informed** |
| K9 | Per set: documented data-quality issues (errata, LF noise, reflections, ITD removed or kept, minimum-phase processing) | researcher | **uninformed** |
| K10 | Perceptual evidence on head-only vs head-and-torso generic sets (localisation, externalisation, preference), static, untracked, with room | corpus split: Roginska Ch. 4 (missing shoulders may weaken elevation), Rumsey §3.2.4 (torso cues individual, confusing unless matched), Begault Ch. 4 (head size a major factor), Vorländer §16.1.2 (dummy heads: front–back confusion common); controlled KU100-vs-KEMAR comparison: researcher | **under-informed** |
| K11 | Which generic set comparable tools ship (base rate) | Zotter & Frank: IEM BinauralDecoder uses KU100 (TH Köln); others: researcher | **under-informed** |
| K12 | Whether any project reference dataset (BRAS CR2–CR4, Arni, dEchorate) has BRIRs measured with one of these heads | researcher (outside corpus) | **uninformed** |
| K13 | Diffuse-field EQ rationale and its interplay with headphone EQ (the PRD is silent on headphone EQ) | Blauert Ch. 4 (Theile), Begault Ch. 4 "Equalization of HRTFs", Rumsey §3.2.3–3.2.4 | known (corpus) |
| K14 | Product rule: one generic set, `hrtfId` const `"generic-v1"`, licence first, fallback MIT KEMAR, block if unclear | AQ6; phase-08 scope 1; BUILD_PLAN §1; schema const (from the code: `contract::kHrtfIdGenericV1`, `Validate.cpp` E_HRTF_ID) | known |
| K15 | Converter targets: 44.1/48/88.2/96 kHz, 256 taps at 48 kHz scaled, onset removed, ITD separate, triangulated grid, DF-EQ stored | phase-08 scope 2–3 | known |
| K16 | Rebuild budget applies to every output mode from Phase 08 | AQ10 | known |

Load-bearing and not known: K1–K3 (licence decides validity), K5–K8 (grid coverage, distance, EQ state, ITD decide whether the phase's gates and the AX3 geometry can be met), K10 (the audible difference between the two heads, if any). This decision cannot be made in the next round without the dossier.

## 5. RESEARCH NEEDED (questions for the researcher, to run alongside the seats)

R1 (K1–K3). For each of SADIE II (York), MIT KEMAR and TH Köln KU100: the licence text on the official record (URL, record version/DOI, date read), whether it permits commercial redistribution of derived data (converted, resampled, equalised HRIRs embedded in a paid plugin), what attribution it requires, and whether any clause is share-alike or non-commercial. *A "no" or "unclear" removes that option (phase-08 scope 1); the attribution text goes into `LICENSE-generic-v1.txt`.*

R2 (K4). Any stated trademark or naming restriction on "SADIE", "KU100"/"Neumann", "KEMAR"/"GRAS" in the dataset terms. *Affects seat 7's rating only, not validity.*

R3 (K5). Per set: sample rate(s) offered, HRIR length in samples, number of measured directions, grid type, lowest and highest elevation, azimuth spacing at 0° elevation, left–right symmetry, SOFA convention and version, file size, SHA-256 of the file to be pinned. *Lowest elevation decides whether the renderer must extrapolate for floor images (seats 2/3); spacing decides the continuity gate (seat 3).*

R4 (K6). Per set: loudspeaker-to-head distance, and whether the set is documented as far-field. *Vorländer §9.5 holds beyond 1 m; a set measured below 1 m would be CONDITIONS VIOLATED for the far-field use the phase assumes.*

R5 (K7). Per set: whether the stored HRIRs are raw (at the microphone), free-field or diffuse-field equalised, or headphone-compensated; microphone position (blocked ear-canal entrance vs ear-canal end / eardrum simulator); whether any post-processing (minimum-phase, ITD removal, LF extension) was applied. *Decides whether the converter's DF-EQ (scope 3) is applied once or twice and whether ear-canal resonance must be removed (Rumsey §3.2.4).*

R6 (K8). Per set: the onset ITD at ±90° azimuth, 0° elevation, as documented or as computed from the files by a stated onset criterion. *If a head's lateral ITD lies outside 0.6–0.75 ms, the phase's AC 3 fails for that head as written; the gate would then be challenged on evidence, not loosened to pass.*

R7 (K9). Per set: documented errata, known artefacts, and the publication describing the measurement. *Data quality enters seats 3 and 4's ratings.*

R8 (K10). Any controlled study comparing KU100 and KEMAR (or head-only vs head-and-torso) as non-individual HRTFs: paradigm, listeners, signal, static vs tracked, headphone EQ, results on front/back confusion, elevation, externalisation, preference. *If torso cues measurably help or hurt untrained static listeners, that moves seat 1's cells between (a)/(d) and (b)/(c).*

R9 (K11). Which generic set the following ship or recommend, with source: IEM BinauralDecoder (corpus says KU100; confirm the campaign), SPARTA/COMPASS, Dear Reality dearVR, Steam Audio, Resonance Audio, Apple/Dolby renderers where documented. *Base rate for seats 4 and 7; not an acoustic fact.*

R10 (K12). Whether BRAS (CR2–CR4), Arni or dEchorate include BRIRs, and with which head. *Decides seats 2 and 9's "later" cells (a measured binaural comparison path for B9).*

Mark each finding read or unverified; unverified findings are leads and will not carry a cell.

## 6. Summary table

| id | decision (exact value/wording) | state | worst-off seat (cell) | sum | confidence | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| D1 | `generic-v1` dataset: (a) SADIE II KU100 / (b) SADIE II KEMAR / (c) MIT KEMAR / (d) TH Köln KU100 — not yet chosen | convening + research needed (R1–R10) | — | — | — | AQ6, phase-08 scope 1, AX3, AX6, AQ10, NFR-8 | Begault Ch. 4; Roginska Ch. 4; Rumsey §3.2.4; Blauert Ch. 4 (Theile), Ch. 2 Fig. 2.30; Vorländer §9.5, §16.1.2; Zotter & Frank Fig. 4.25, BinauralDecoder note | to be set in the decision round (expected: licence outcome; Phase 08 ITD/continuity gates on the real files; B4 listening evidence) |

## 7. Challenges to settled decisions

None raised at this stage. Two notes for the decision round, not challenges yet: (i) the phase-08 AC 3 window 0.6–0.75 ms is stated for a human-like head (Blauert Ch. 2 Fig. 2.30 ≈ 650 µs); whether each dummy head lies inside it is R6 — if not, the gate's basis is challenged separately, never loosened to pass; (ii) `docs/board/board.md` §1's "physical detail admitted only when audible" and PRD NFR-1's accuracy-first do not conflict on D1, since the head is chosen for what the listener hears either way.

## 8. For Maisara

D1: the board is being asked which measured artificial head the headphone mode listens through (York's KU100, York's KEMAR, MIT's KEMAR, or Cologne's KU100). Nothing is chosen yet: the licences and the datasets' own properties are not in any document we hold, so the researcher is asked ten precise questions while the nine seats state their positions. No veto-grade override is in view.

**CONVENE**
