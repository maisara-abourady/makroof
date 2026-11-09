# D1 (dry run) — Seat 9, the audible room (2026-11-09)

Method: the registered `seat9-room-acoustician` agent, briefed with B9 of `1-decider-convene.md`; no dossier yet (dataset facts `[Hyp]`). Verbatim.

---

SEAT 9 POSITION

**1. Reading.** Which dummy head becomes `generic-v1`; my narrow part: does any room reference the project uses or plans hold BRIRs with one of these heads (a B9 comparison path), and how a head's colouration would surface in a preset complaint and be separated from the room. Cues triggered (§4): *coefficient provenance* (a dataset is an input with provenance and uncertainty, like α), *complaint timing and source* (S6/C5), *late change after commitment* (a head swap after presets are blind-validated).

**2. Ranking.**
1. Dataset-agnostic converter/header (the condition) — *prefer*. It is the only thing on the table that protects my criterion 2 (presets true to a measured reference) against a later swap.
2. (d) TH Köln KU100 — *can live with*, ranked first among heads only on a `[Hyp]` lead: if the same campaign published BRIRs of documented real rooms with the same head, it is the one option with a same-head HRTF+BRIR pair, which is what a B9 comparison needs to isolate the room from the head. Researcher must confirm.
3. (a) SADIE II KU100 — *can live with*. Head-only, mics at the ear-canal entrance, head DF-equalised (Begault Ch. 4; Roginska Ch. 4 "KU-100 ... ear-canal entrances"): least head colouration to disentangle from the room.
4. (b) SADIE II KEMAR — *can live with*. Torso cues "a confusing cue unless matched" (Rumsey §3.2.4); a public KEMAR BRIR set exists (Roginska Ch. 4 names Wierstorf et al. 2011, TU Berlin), but a different campaign and pinnae `[Hyp]`.
5. (c) MIT KEMAR — *can live with, conditions below*. Lowest elevation −40° (Begault Ch. 4) and eardrum-position mic (Zwislocki simulator, Begault Ch. 4) both bear on what I measure at the seat.

Finding on the comparison path (project documents, read): BRAS CR2–CR4 as the project uses them were measured with a B&K 4134 diffuse-field (omni) microphone (researcher report 9, F8); Arni with G.R.A.S. 46AF free-field mics plus em32/Zylia SRIRs (report 13, D1); dEchorate with AKG CK32 arrays (report 13, D3). **None holds a KU100 or KEMAR BRIR, so no option keeps or loses a measured binaural comparison through the project's current references.** The full BRAS release may contain BRIRs with TU Berlin's own head-and-torso simulator (RR19 reports "spectral BRIR differences", report 9 F13) — head identity `[Hyp]`, and if so it matches no option equally. The only project-referenced binaural set, AIR (report 13, D13), is "binaural only, no geometry", head unknown `[Hyp]`.

**3. Tension now.**
- Condition: 0.
- (a), (d): 1. A head-only set lacks torso cues; for a static listener who always faces the emitters (AX3) the elevation loss sits in a cue I have no incident on (small-room, headphones) → `[Hyp]`, hand to Seat 1.
- (b): 1. Torso comb is scene-independent and will be read as "room" by a producer; separable by the protocol in §6.
- (c): 2. Two early-structure costs at the seat. (i) Floor-reflection direction: ears 1.2 m high, emitter 2 m away at ear height → floor image elevation = −atan(2.4/2) = −50°; at 3 m, −39°. Producer-room presets therefore put the first or second strongest reflection below the grid; clamping to −40° renders it from the wrong direction and spectrum (criterion 3). The renderer's remedy is Seat 2's (B2 ii); the audible consequence is mine. (ii) Ear-canal resonance in the data must be equalised out (Rumsey §3.2.4) or every dry preset reads "harsh" and the complaint lands on the room.

**4. Tension later (debt).**
- Condition: 0. Swap cost = re-run the converter and the blind A/B logs (days), not a rewrite.
- Any head without the condition: 3. The preset library is validated by blind A/B at a stated head (C3); a head swap after validation reopens every log (W1 rule: a late change re-opens every prediction). Undoing = a phase of re-listening. Evidence arrives in phase-08's checklist and in B9 (alongside 15).
- (a)/(d) vs (b)/(c): 1 either way for me; the head-only vs torso evidence arrives at B9 and B4, both reversible through the converter.
- (c): 2. The −40° floor commits presets for rooms under ~3 m ceiling to an extrapolation whose error is never measured against a reference; evidence would arrive only when a KEMAR BRIR of a small room is compared (none planned).

**5. Evidence.**
- Receivers of BRAS/Arni/dEchorate: `docs/review/phase-04-consult/9-researcher-measurements.md` F8; `13-researcher-second-dataset.md` D1, D3, D13 `[Peer; H, read]`.
- KU100 DF-equalised, symmetric pinnae; KEMAR torso, Zwislocki canal; MIT 1.4 m, 44.1 kHz, 710 positions, −40°…+90°: Begault Ch. 4 `[corpus]`.
- Torso cues individual; measurement heads include canal resonance to be equalised out: Rumsey §3.2.4 `[corpus]`.
- KU100 mics at ear-canal entrances: Roginska Ch. 4 (two-loudspeaker measurement note) `[corpus]`.
- KEMAR BRIRs, TU Berlin (Wierstorf 2011): Roginska Ch. 4 `[corpus, named only]`.
- Dummy heads: front–back confusion for a large share of listeners: Vorländer §16.1.2; Blauert Ch. 4 "Commercial failure" `[corpus]`.
- Floor-image geometry: my arithmetic above `[Inf; H]`.
- A head cannot make a render "thin": head shadow is small below ~500 Hz, so weak 125–250 Hz is room (bass ratio, S3) or headphone, not head `[Inf; H]`; interrogator may check against Blauert Ch. 2.
- Researcher: (R10) BRAS binaural part and head; (new) does TH Köln publish BRIRs of documented rooms with its KU100, and does Wierstorf 2011 give room geometry and materials — either would create the only same-head B9 path.

**6. Conditions of acceptance.**
- (c) 2→1 now: DF-EQ computed from the set's own diffuse-field average (removes the canal resonance), plus a documented below-grid rule tested on a scene whose floor image lies at −50°, with the resulting reflection spectrum compared to the omni IR's.
- Any head 3→0 later: adopt the dataset-agnostic condition and record the head id in every preset's validation log.

**7. Hand-offs.** Licence and naming: Seat 7 and a human. Grid coverage/extrapolation: Seat 2. Audibility of torso and elevation cues for static listeners, and whether the ITD/ILD gates are perceptual: Seat 1. Canal-position EQ and DF-EQ order: Seat 4. UI naming of the head: Seat 6. Running the blind tests: a human.

**Complaint protocol (for C5, any option).** Head colouration is scene-independent: render the anechoic direct-only scene (phase-08 AC 3 fixture) and the omni preview beside the preset. A "boxy/harsh" that persists in the anechoic render is head or EQ; one that changes between presets is room. "Boxy" at 150–300 Hz spacing in a desk-height preset is the floor comb (path difference ≈ 1.1 m, first notch ≈ 150 Hz), not the head. "Thin" is never the head.

**8. Premortem.** If (c) ships without the two conditions, small-room presets render the floor reflection from −40° with canal resonance left in; Maisara notices first at the checklist line "colouration vs omni preview", and the complaint is filed under the room.
