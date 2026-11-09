# D1 (dry run) — Seat 4, the chain keeper (2026-11-09)

Method: the registered `seat4-chain-keeper` agent, briefed with B4 of `1-decider-convene.md` (owner of the matter); no dossier yet (dataset facts `[Hyp]`). Verbatim.

---

SEAT 4 POSITION

**Reading.** Which measured dummy-head set becomes `generic-v1`, the one head every v1 binaural render listens through, with licence, EQ state, distance and the B4 swap path attached. Cues triggered (§4): *measurement doubt* (two KU100 campaigns on the table: the Club Fritz doubt applies literally), *spectral mismatch* (EQ state of the stored data; no headphone compensation anywhere in the PRD or phase-08), and the *chain description file* (§14). Persona assumption that fell: "head tracking optional, designed in from the start" is out of scope by PRD; AX3's yaw-to-centroid (`ListenerFrame`) is the per-path rotation stage of my §9, and that is all v1 has. The head is therefore the third lever (after room cues, which Phase 03/04 supply, and compensation, which nothing supplies), so no option moves my primary measures much in a static render.

**Ranking.**
1. (d) TH Köln KU100: *prefer*, conditional on R1/K3.
2. (a) SADIE II KU100: *can live with*; becomes prefer if (d) fails on licence.
3. (b) SADIE II KEMAR: *can live with*.
4. (c) MIT KEMAR: *can live with* as the licence fallback only, under the conditions in §6.
Dataset-agnostic converter/header: *prefer*, and I ask it to be widened (below). Any option whose licence reads "no" or "unclear" at R1 becomes *cannot live with*: documented provenance and licence is a never-trade-away (§2), and phase-08 scope 1 says the same.

**Tension now.**
- (d) 1. Same campaign as the free baseline the product must beat blind (IEM BinauralDecoder uses the Cologne KU100 set and, optionally, its headphone-EQ curves: Zotter & Frank §4.12.3). An A/B against IEM RoomEncoder+BinauralDecoder in one host then isolates the renderer, not the head. KU100 pinnae and ear placement are left-right symmetric (Begault Ch. 4), so the AC 3 mirror check tests the code, not the head's asymmetry. Grid 2702 directions (Zotter & Frank §4.11.1, HRIR_L2702). Licence, distance, lowest elevation, EQ state: `[Hyp]`.
- (a) 1. Same head, different lab: Club Fritz measured the same KU100 at ten labs and found magnitude spreads up to 12.5 dB below 6 kHz, 23 dB above, ITD spreads up to 235 µs (register row "Club Fritz"). So (a) and (d) are not interchangeable, and a baseline A/B against IEM carries the head as a confound. Zotter & Frank's own Pd examples use SADIE subject 1 (§1.4.2), so it is a second baseline's head. Headphone data: `[Hyp]`.
- (b) 1. Head-and-torso. The corpus splits: missing shoulders "may weaken elevation cues" (Roginska Ch. 4) versus torso reflections "differ considerably between individuals: a confusing cue unless matched" (Rumsey §3.2.4). No controlled KU100-vs-KEMAR result in the corpus or my register; R8. Microphone position: KEMAR couples laboratory microphones to a Zwislocki ear-canal simulator (Begault Ch. 4), so an eardrum-position set carries an ear-canal resonance of roughly +11 dB near 4 kHz (Begault Fig. 2.10) that must not be reproduced twice (Begault: remove it to avoid a "double resonance"). Whether SADIE's KEMAR was measured at the eardrum or the blocked entrance: `[Hyp]`.
- (c) 2. Corpus facts: 1.4 m, 44.1 kHz, 710 positions, elevations −40° to +90°, ML sequences, plus "several headphones on the KEMAR" (Begault Ch. 4 appendix). 1.4 m clears Vorländer §9.5's 1 m. Costs to my seat: one 1994 campaign with no modern re-measurement; headphone measurements of 1994 headphones, so any later compensation comes from another KEMAR, which is the "same head, different lab" doubt again; no current free baseline uses this file (SPARTA's default is a KEMAR *simulation*, register row 444), so the baseline A/B carries a head confound.
- Dataset-agnostic condition: 1 (converter work), and it is where my chain description file lives.

Shared and not this matter: ~29% front-back reversals for speech through non-individual static HRTFs (Wenzel 1993, register) against 6–11% with own HRTFs; externalisation will lean on the room cues of Phase 03/04, which is the right lever (Begault/Wenzel/Anderson 2001: reflections externalised, individualisation no main effect for speech).

**Tension later (debt).**
- (d) 1. Commits the headphone-compensation path (whenever it comes) to HpTFs from the same campaign, which exist per corpus. Swap to a personal set is the B4 path. Evidence arrives: R1 (licence), phase-08 AC 3 on the real file (R6).
- (a) 2. If SADIE II has no HpTFs on its KU100 (`[Hyp]`), compensation must come from another lab's KU100, violating "compensation from the head that measured the HRTFs" (Lindau and Brinkmann 2012, register). Lowers to 1 if R3/R5 show HpTFs in the record. Undo cost with the agnostic header: converter re-run, three goldens, tail-coherence target, one rating round (about a day plus a listening round `[Inferred]`); without it, a phase of rework.
- (b) 2. Same HpTF question, plus the torso cue is baked into the only v1 head while B4 later replaces it with torso-less personal sets for most users: a v1-to-B4 switch that changes elevation/colouration character, not just individual detail. Lowers to 1 under R8 evidence that torso cues do not hurt untrained static listeners.
- (c) 2. The −40° floor forces an extrapolation/clamp policy into `src/sim` that then governs every later set (Seat 2/3 decide the policy; I rate the debt). 44.1 kHz source resampled to all four rates: fine for cues, but a 1994 provenance sits under a paid product indefinitely. Overturn evidence: continuity gate and listening checklist in phase-08.
- Agnostic header: 0. It also caps the undo cost of every option above.
- Independent of set: AX6 allows 0.3 m while standard HRTFs are distance-independent only beyond 1 m, with ILD growing strongly below it (Vorländer §9.5, Fig. 9.7). Debt 1 for all options; the near-field follow-up needs the measurement distance recorded in the header.

**Evidence.**
- Non-individual static: ~29% reversals, speech [Observed] register row Wenzel 1993.
- Tracking halves reversals, reflections externalise, individual HRTFs no main effect (speech) [Observed] register row Begault, Wenzel, Anderson 2001.
- Club Fritz spreads [Observed] register row Andreopoulou, Begault, Katz 2015.
- Compensation from the measurement head [Observed] register rows Lindau and Brinkmann 2012; Engel et al. 2019.
- IEM BinauralDecoder: MagLS with Cologne KU100 and its headphone EQ curves [corpus] Zotter & Frank §4.12.3, abbreviations "KU100", "TH Köln"; 2702-direction set §4.11.1.
- SADIE subject 1 = KU100 in the book's examples [corpus] Zotter & Frank §1.4.2.
- KU100 diffuse-field equalised, symmetric pinnae; KEMAR Zwislocki coupler; ear-canal resonance ≈ +11 dB near 4 kHz; remove to avoid double resonance; MIT set facts [corpus] Begault Ch. 4.
- Torso cues individual/confusing; recording heads at the canal entrance, measurement heads at the canal end [corpus] Rumsey §3.2.4; missing shoulders may weaken elevation [corpus] Roginska Ch. 4.
- Diffuse-field equalisation rationale [corpus] Blauert Ch. 4 (Theile), Begault "Equalization of HRTFs".
- Distance > 1 m condition [corpus] Vorländer §9.5.
- Human onset ITD ≈ 650 µs at 90° [corpus] Blauert Ch. 2 Fig. 2.30. Zotter & Frank Fig. 4.25(b) shows the Cologne KU100 single-ear arrival earliest near 90° and latest ≈ 0.6 ms near −100°; the earliest value is not printed, so I cannot redo the ITD arithmetic: if the earliest is near the model's −0.25 ms the onset ITD is ≈ 0.85 ms, outside AC 3's 0.6–0.75 ms; if the plot's zero is the earliest arrival it is ≈ 0.6 ms, inside. R6 is load-bearing for every option; the gate is challenged on evidence, never loosened to pass.
- `[Hyp]`, for the researcher: licences (R1), SADIE/TH Köln distance and lowest elevation (R3/R4), EQ state and mic position per set (R5), HpTF availability per campaign (add to R5), onset ITD per set (R6), head-only vs torso evidence (R8), base rate (R9).

**Conditions of acceptance.**
- (a) 2→1: R5 confirms HpTFs on the SADIE KU100; otherwise record in `THIRD_PARTY.md` that compensation, when added, will be cross-campaign and must pass a colouration listening check.
- (b) 2→1: R8 evidence as above, plus R5 confirming blocked-entrance measurement or the converter's DF-EQ on by default (not merely switchable) so the ear-canal resonance is removed.
- (c) now 2→1 and later 2→1: DF-EQ on by default (removes the coupler resonance, Begault Ch. 4); the below-grid policy stored as data in the header, not as a constant in `src/sim`; the header records "44.1 kHz source, resampled"; and the phase file records that the baseline A/B against IEM carries a head confound.
- Agnostic condition, widened to my chain description file: header and `LICENSE-generic-v1.txt` carry set identity, lab and campaign, record version/DOI, SHA-256, sample rate, grid and lowest elevation, measurement distance, microphone position, EQ state before and after the converter, ITD method. A later swap is a §6 change-log row plus a listening round, never a silent re-run of goldens.
- All options: the converter's DF-EQ is computed from the set itself (as scope 3 says), which is self-correcting for already-equalised sets and removes direction-independent resonances; `HrtfSet` must assume no left-right symmetry (a personal set in B4 breaks it); AC 3's mirror check stays a data test.

**Hand-offs.** Licence reading: a human (lawyer), on R1. Trademark exposure of "Neumann/KU100/KEMAR/SADIE" and swap cost in euros: Seat 7. Whether the head is ever named in the UI and how "generic" sits beside a personal profile: Seat 6. Whether a torso cue or a 1 dB colouration is audible to the target listener, and the plausibility bar: Seat 1 (my amendment stands: plausibility, not authenticity, on headphones). Below-grid extrapolation and continuity under 2° grouping: Seats 2 and 3. Maisara's checklist listening is a labelled developer test, not validation (§8 G).

**Premortem.** If the board picks by provenance and licence alone and skips the rating round, the first producer who A/Bs the plugin against the free IEM chain on the same scene hears a tonal and lateral difference and blames the room model; Seat 9 gets the complaint first, and the fix is a head swap that the untested goldens then have to be regenerated for.
