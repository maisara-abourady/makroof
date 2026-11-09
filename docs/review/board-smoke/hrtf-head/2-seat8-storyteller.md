# D1 (dry run) — Seat 8, Vantage, the spatial storyteller (2026-11-09)

Method: the registered `seat8-storyteller` agent, briefed with B8 of `1-decider-convene.md`; no dossier yet (dataset facts `[Hyp]`). Verbatim.

---

SEAT 8 POSITION

Whose-ears sentence for the producer the product serves: in v1 her audience hears through one hidden, fixed artificial head, stationary, upright, always facing the emitters' centroid (AQ6, AX3, F8), with the room around it. Target chain: headphones; she will also check it on her monitors.

**1. Reading.** Which artificial head the headphone mode listens through: a recording head built for headphone/loudspeaker compatibility (KU100, options a/d) or a measurement head-and-torso (KEMAR, b/c). Cues triggered: §4 cue 1 (whose ears), cue 10 (where was it judged; the producer will judge the binaural render on speakers), cue 5 (uniform reflections, for option c's grid floor), cue 9 (the maker's detector: Maisara's checklist is one listener).

**2. Ranking.** (a) SADIE II KU100 — *prefer*. (d) TH Köln KU100 — *prefer* (same head; tie-break on licence, grid and EQ state is Seats 4/7/3's). (b) SADIE II KEMAR — *can live with*. (c) MIT KEMAR — *can live with*, with conditions (§6). Dataset-agnostic converter/header — *prefer*, and I rate its absence below. No option of my own: the head is hidden, so no workflow requirement from §8 is decided here except the swap path.

Why KU100: it is the head music engineers have put in front of orchestras for the *front image* (Rumsey §7, Bishop/Telarc), equalised close to Theile's diffuse-field target so it sounds "reasonably natural on loudspeakers" (Rumsey §3.2.4, §6.x; Blauert Ch. 4: IRT tests, timbre largely authentic over stereo loudspeakers). Tone colour is the first thing a producer hears go wrong (Pepper: "bright, digital", GM1). KEMAR's torso reflections are a cue that "differs considerably between individuals: confusing unless matched" (Rumsey §3.2.4) and nobody in the target group asked for; the missing shoulders of KU100 "may weaken elevation cues" (Roginska Ch. 4), and elevation is the cue my seat spends last (anchor, depth and front image come first, §2 criteria 2–3).

**3. Tension now.**
- (a) `0`, (d) `0`: front image for ±30° emitters, natural timbre on both chains, the head recording engineers already trust.
- (b) `1`: torso colouration baked into every render; for my criteria a preference-grade loss, not a story loss.
- (c) `1`: 1994 set, 44.1 kHz, lowest elevation −40° (Begault Ch. 4 as cited in the convening document; not re-read by me). Floor images under AX3 can fall below −40°; a clamp would give every low floor reflection the same HRIR — the "identical clip-clop" nobody's world sounds like (cue 5, `Inf`). Rating of audibility is Seat 3/1's.
- Dataset-agnostic condition: `0` (header fields and a converter flag).

**4. Tension later (the debt).**
- (a)/(d) `1`: any dummy head leaves front/back confusion and weak externalisation for a large share of listeners (Vorländer §16.1.2; phase-08 Risks). The fix is B4 (personal SOFA), not another generic head. Evidence: phase-08 listening checklist, then B9 listening tests. Undo if B4 arrives: a converter rerun and regenerated goldens.
- (b) `2`: the torso cue sits under every binaural render and every B9 comparison until B4; swap cost = converter rerun + goldens + listening-pack re-audit *if* the condition holds, a phase of rework in `src/sim/hrtf` if not. Evidence: phase-08 colouration line, B9.
- (c) `2`: as (b), plus the below-grid policy becomes a renderer rule that a later set with full coverage makes dead code. Evidence: Phase 03 image directions vs grid at phase-08 AC "continuity".
- Without the dataset-agnostic condition: `2` for every option — "whose ears" is frozen at the sim level, and B4 (the one real lever on criterion 1 for headphones) costs a rewrite instead of a file.

**5. Evidence.**
- KU100 designed for loudspeaker/headphone compatibility, EQ near Theile's diffuse-field response: `Doc` Rumsey §3.2.4 (KU100 entry, Fig. 3.11), §6 (dummy heads equalised for natural timbre on loudspeakers), §7 (Bishop's KU100 for the front image); Begault Ch. 4 (KU-100 "Fritz II" diffuse-field equalised); Blauert Ch. 4 (Theile; IRT tests).
- Torso cue individual and confusing unless matched; measurement heads include ear-canal resonance to be equalised out: `Doc` Rumsey §3.2.4. KEMAR = head-and-torso for research/measurement; KU100 missing shoulders may weaken elevation: `Doc` Roginska & Geluso Ch. 4 device types.
- Dummy heads → front/back confusion for a large portion of subjects; head movement essential and out of scope here: `Doc` Vorländer §16.1.2; PRD out-of-scope list.
- Anechoic binaural does not externalise; room reflections are the remedy: `Doc` Zotter & Frank Ch. 4 (RoomEncoder note); consistent with my register GM3, GF2 `SRi, post`. So the room, not the head, carries my criterion 5 on headphones.
- Binaural over loudspeakers: LF too narrow, timbral error unless compromise EQ; Griesinger's spatial EQ keeps the front image but not height or front/back: `Doc` Rumsey §3.2.6. Hence: never let the producer bounce the binaural mode for speakers; Phase 09's speaker mode is the re-make (ST6 rule 3; GM1, WM4 `SRi, post`).
- Forward-facing stationary listener with a centre is what immersion needs: GM2, GM6 `SRg, 1/5, M` — AX3/F8 match this by design.
- Base rate: IEM BinauralDecoder uses KU100 (TH Köln): `Doc` Zotter & Frank Ch. 4. That producers' monitoring plugins have trained their ears to a KU100 flavour: `[Hyp]`.
- Researcher: R5 (is DF-EQ already in the SADIE/Köln KU100 files, so the converter's DF-EQ is not applied twice — Seat 4 owns the consequence, I only need the fact); R8 (any KU100-vs-KEMAR preference/externalisation study with untrained static listeners); R9 (base rate across dearVR, Steam Audio, Apple).

**6. Conditions of acceptance.**
- (b) 2→1 later: dataset-agnostic header so the KEMAR→KU100 or →personal swap is a converter rerun; the phase-08 colouration checklist line explicitly compares binaural against the omni preview *and* the dry track.
- (c) 2→1 later: same header condition, plus a below-grid policy that varies with direction (mirror or extrapolate, Seat 3's call) rather than a single clamped HRIR for all floor images.
- Missing condition 2→0: adopt it.

**7. Hand-offs.**
- Audibility of torso cues, elevation and the −40° clamp for a static listener: Seat 1.
- Interpolation, below-grid policy, truncation: Seat 3.
- EQ state, ear-canal resonance, licence path, B4 commitment: Seat 4.
- Whether the UI names the head and whether switching to speaker mode is made obvious before a bounce (my §8 "Translation view" requirement): Seat 6.
- Naming/trademark exposure: Seat 7 → lawyer.
- Whether Maisara alone hears "inside the head": a naive-listener panel, a human.

Workflow requirement most affected: the Translation view — the producer must never ship the binaural render to speakers; and the swap path to a personal head (B4) is the only v1-reachable answer to "whose ears" on headphones.

**8. Premortem.** If a KEMAR set is chosen and fails, the first complaint is "headphone mode sounds boxy/nasal next to the omni preview and my monitors", Maisara notices it on the checklist's colouration line, and she blames the room preset, not the head.
