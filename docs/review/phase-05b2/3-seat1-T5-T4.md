# Seat 1 (perceptual gatekeeper) — positions on D-T5 and D-T4

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 1 POSITION: D-T5 (the tail-level switch and the matching)

Corpus present (c1b171f). One of my persona's assumptions no longer holds: v1 has no head tracking (AQ4, AX31) and uses one generic HRTF (AQ6). My T1 and T2 motion thresholds therefore do not apply, and neither does my Lübeck 2022 row, which was measured head-tracked.

**1. Reading.** The question is how the switched tail level is composed and tested, what Phase 08 receives, and what `open_field` gets. It triggers these cues: tone-colour (5.1-C); late-field detail (5.3); a threshold borrowed from another method (the G jnd applied to a tail-only error); sparse signals expose faults (B2).

Answers to B1-T5:
- **The G jnd is the wrong yardstick on its own.** A tail-only error ΔL moves G by ΔG = 10·log10(1 + f·(10^(ΔL/10) − 1)), where f is the tail's share of the total energy. Redone:
  - +3.87 dB needs f ≥ 0.18 to reach ΔG = 1 dB.
  - −1.18 dB needs f ≥ 0.87.
  - Illustration, not a measurement [Inferred]: layout 4 has t_mix,e = 380 ms. With a rough Eyring T ≈ 1.4 s, f ≈ e^(−13.8·0.38/1.4) ≈ 0.02, so ΔG ≈ 0.14 dB.
- **Where the error does show is the envelope step at t_mix,e and in T30.** After a click the decay jumps at the seam, and the T30 range (−5 to −35 dB) spans it. The corpus has no jnd for a step inside a decay [Hyp].
  - I predict trained listeners detect +3.9 dB in ABX on clicks and pink bursts, and that ±1.2 dB is uncertain.
  - In layout 4 the switch lowers the tail by 3.87 dB. That shrinks the AX21 seam step, which today is already up to 8.7 dB at s = 0.4.
  - In layouts 5 and 6 at s = 1 the switch raises the tail by about 1.17 dB and enlarges the step slightly.
- **CR3 at −1.18 dB, 2 kHz** is below the G jnd by the arithmetic above. It is also outside the jnd's stated range of 500–1000 Hz.
- **The uniform-α residual (≤ 0.43 dB)** is below 0.5 jnd before the ΔG reduction is even applied. I treat it as safe to change [Inferred; Vorländer Table 6.1].

**2. Ranking**
- (1) Prefer **5.1-A**; can live with **5.1-C**.
- (2) Prefer **5.2-A**. 5.2-B and 5.2-C: not rated (out of bounds).
- (3) Prefer **5.3-D**; can live with **5.3-B** and **5.3-A**; **5.3-C** rated 2.
- (4) Prefer **5.4-A**, conditional on C1; can live with **5.4-B**.

**3–4. Tension (now / later)**

| option | now | later | reason |
|---|---|---|---|
| 5.1-A | 1 | 1 | Validated only at 500 Hz–2 kHz. The model is geometric and frequency-independent except for α and air, so extending it to other bands is mild. 63 Hz is wrong under any geometric method (T6). |
| 5.1-C | 2 | 2 | See below. |
| 5.2-A | 0 | 1 | The flutter fallback decision is unchanged, so no audible change. Later, k_real rests on a level model known to be wrong (AX16). |
| 5.3-D | 0 | 0 | Honest and labelled. |
| 5.3-B | 0 | 1 | It would measure anisotropy, but that can be done offline in `ref_hybrid` at no cost to src/sim. |
| 5.3-A | 1 | 1 | A stale diagnostic of a model that no longer sets anything invites a future claim. |
| 5.3-C | 2 | 2 | See below. |
| 5.4-A | 1 | 1 | See below. |
| 5.4-B | 1 | 2 | See below. |

- **5.1-C.** In uniform-α layout 4 at s = 1 it leaves +3.87 dB at 63–250 Hz and 4–8 kHz, against a corrected 500 Hz–2 kHz. That is a 3.9 dB mid-band scoop in the tail: a tone-colour fault, which is the dominant residual class (T4). It also ships a second level change later, when the outer bands get validated.
- **5.3-C.** It spends Phase 08 scope and adds a dependency on a detail with no audibility evidence.
  - The default for late-field detail is to cut it to a low-resolution diffuse field.
  - Vorländer §15.3, citing Meesawat and Hammershøi: after 140 ms the receiver-specific reverberation can be replaced statistically.
  - The anisotropy that concentrated floor absorption produces is mostly vertical. Elevation is what a generic HRTF renders worst [Hyp].
  - The bar is **plausibility**: there is no real reference in a DAW (T3, T6). Lübeck 2022's order 4–5 for the late part was an authenticity test, head-tracked, so it does not transfer.
- **5.4-A.** C1 has not yet computed the tail level. My estimate [Inferred]:
  - Every Lambert arrival ends by about 0.425 s (farthest floor corner: path ≈ 145 m).
  - Referring it to 1.404 s at the nominal T60 attenuates it by at least 47 dB at 63 Hz (T60 1.24 s) and at least 92 dB at 1 kHz.
  - Add the total Lambert energy (−15 to −43 dB) and normalisation to 10 ms (−18 dB).
  - Result: E_target is at or below about −80 dB re direct at 63 Hz, and far lower above. That is inaudible at any plausible monitoring level [Hyp: ISO 226 thresholds, outside the corpus].
  - Weakness: the proposed "≤ Lambert estimate" check is a consistency check, not an audibility test.
- **5.4-B.** It adds a threshold rule that buys nothing audible if C1 confirms my estimate. If the criterion allows any tolerance (not exact zero), the step at the threshold becomes non-trivial in semi-open scenes such as a stage with one wall plus ground.

**5. Evidence**
- [corpus] Vorländer Table 6.1: G jnd 1 dB, 500–1000 Hz.
- [corpus] Vorländer §4.4: fields with concentrated absorption are not diffuse.
- [corpus] Vorländer §15.2.3: late reverberation is sufficient as 10 ms envelopes in 10×10° sections.
- [corpus] Vorländer §15.3: Meesawat and Hammershøi, the 140 ms finding above.
- [corpus] Zotter and Frank, §5 (reverberation in Ambisonics): envelopment needs consistently low interaural correlation. Phase-08 item 5 supplies that.
- [Observed] `docs/validation/report-phase05b.md` §5 and AX16 numbers; golden `phase04_open_field_omni` T60 values; `matchTail` uses a full sin² window (from the code).
- [Hyp] Directional-tail audibility: RQ6. Researcher also to verify:
  - octave-band level-step discrimination in broadband reverberant noise (bears on 5.1-C);
  - ISO 226 thresholds at 63–125 Hz.

**6. Conditions of acceptance**
- **5.1-C, 2→1:** only if the outer five bands' AX16 error is shown to be within 0.5 dB of the 500 Hz–2 kHz correction in every listed case. Otherwise use 5.1-A.
- **5.1-A, 1→0:** a tracer comparison at 125 Hz and 4 kHz in layout 4 and layout 5 at s = 1.
- **5.3-C, 2→1:** adopt only after a blind test passes:
  - phase 08 binaural, generic HRTF, no tracking;
  - directional tail computed offline from `ref_hybrid` against the diffuse-coherence tail, level-matched;
  - layouts 4 and 5 at s = 1; pink bursts and a cappella voice;
  - 16 trials, 12 or more correct counts as detected;
  - one trained listener first, then naive listeners (the asymmetry rule).
- **5.4-A, 1→0:** C1 reports the per-band level at t_mix,e re direct, and a test asserts it stays at or below an audibility floor. I propose −80 dB [Hyp].
- **5.4-B, later 2→1:** an exact-zero criterion only, plus a continuity test at the threshold.

Acceptance tests for every option:
- Before/after ΔG, ΔC80, ΔEDT, ΔT30 and the seam step at t_mix,e, in jnd units, for the listening-pack scenes. Automated and reported.
- A self-ABX by Maisara on layout 4 at s = 1 and on CR3 ls1_mp2:
  - signals: clicks, pink bursts and voice, with one dense mix as control;
  - not level-matched;
  - 16 trials per signal, per-signal results reported.
  - This is not a gate. It is evidence for any public "audibly corrected" wording.

**7. Hand-offs**
- How ΔL converts to ΔG and the physics per band: Seat 2.
- Seam behaviour: Seat 3.
- Phase 08 input and the ±1 dB omni-to-binaural parity: Seat 4.
- Test gating: Seat 5.
- Public wording: Seat 7.
- `open_field`'s missing ground-scatter early energy (−23 to −43 dB, in 60–425 ms) is the audible outdoor deficit, and neither option touches it (AX21): Seats 2 and 9.

**8. Premortem.** If 5.1-C ships, a mixer A/B-ing absorbent-floor venue presets on headphones hears a mid-scooped, hollow tail. That complaint comes first, before any level complaint.

---

SEAT 1 POSITION: D-T4 (cost budget)

**1. Reading.** The decision sets a memory ceiling, how rebuild time is read, and what blocks. It triggers these cues: a borrowed threshold carries its method (Table 15.1); time-variance under motion (S7); the scene is seen as well as heard (the 3D canvas). As instructed, I make no audibility claim about memory.

Standing of 700 ms and 3 s:
- Vorländer Table 15.1 is labelled a "proposal" (after Lentz et al. 2007).
- §15.3 derives the movement speeds from VR user behaviour: 30–50 cm/s translation. 0.25 m in 700 ms is about 36 cm/s; 1 m in 3 s is about 33 cm/s. §6.4.5 gives a spatial resolution of the order of 1 m.
- So each interval is a speed times a spatial step. It is a derived budget, not a measured lag threshold: no paradigm, listeners or signal are stated. Confidence: medium-low.
- Two of its premises fail here:
  - DAW automation speed is unbounded (AX18 states none). At 5 m/s, 700 ms is 3.5 m per update.
  - Room-size changes appear in no row.
- So Table 15.1 does not certify a longer rebuild as inaudible in this product.

Is a longer rebuild heard as an artefact or as lag?
- **No clicks** (every update crossfades, AQ4).
- **Stepping.** A longer interval means larger IR steps, so lower ρ and deeper equal-gain mid-fade dips. AX18's arithmetic: Δr = 16 cm gives −10.7 dB at 1 kHz.
- **Lag.** Real-time output trails the automation by slot wait + rebuild + 2P + 30 ms, while the offline bounce rebuilds synchronously (AQ4). What is monitored is therefore not what is bounced. At the largest room that gap is about 1.5–1.9 s at 96 kHz today, before the diffuse part is added.
- **The canvas** moves in sync with the playhead, so the lag becomes audio-visual. I have no incident for non-onset, continuous spatial changes [Hyp]. T1's 52–108 ms is sensorimotor and does not transfer.

**2. Ranking.**
- (a) Prefer 4a-3; can live with 4a-2 and 4a-1. This ranking rests only on the D-T3 risk below.
- (b) Prefer 4b-1; can live with 4b-2.
- (c) Prefer 4c-1; can live with 4c-2 and 4c-3.

**3–4. Tension (now / later)**

| option | now | later | reason |
|---|---|---|---|
| 4a-1 | 0 | 2 | If it forces D-T3, a formulation threshold puts an AX16-vs-hybrid level step (up to 3.87 dB synthetic; open faces in arenas and festivals) into room-size automation. |
| 4a-2 | 0 | 1 | Same risk [Hyp], depending on D-T1. |
| 4a-3 | 0 | 0 | |
| 4b-1 | 0 | 1 | It reads the interval the listener actually experiences. Later, a stale cache would be heard as a wrong tail level. |
| 4b-2 | 0 | 1 | It overstates the interval, so the 3 s scattering-update remedy triggers early. |
| 4c-1 | 1 | 1 | The full-rebuild lag under room-size automation is unbounded, but it is recorded. |
| 4c-2 | 1 | 1 | Its limit would come from UI response-time literature (RQ5), a different method from audio lag. |
| 4c-3 | 1 | 2 | Nothing can say no to multi-second stepping and a monitor-versus-bounce divergence except a sighted checklist. |

Whether a ceiling rules out every candidate class at 100 m is Seat 2's ground. The dense kernel (3–6 TB) exceeds all three ceilings.

**5. Evidence**
- [corpus] Vorländer Table 15.1, §15.3, §6.4.5, Eq. 4.15 (via AX18).
- [Observed] AQ4, AQ10, AX18, AX31 and §0 row 07 times.
- [Hyp] Lag audibility.
- Researcher:
  - Lentz et al. 2007's actual basis: a listening test, or a derivation?
  - Detection of audio-visual asynchrony for continuous, non-onset spatial changes.
  - Any study measuring how late a room-response update can be under source movement before it is noticed.

**6. Conditions of acceptance**
- **4a-1, later 2→1:** any D-T3 threshold is gated by a computed step (ΔG, ΔC80, ΔT30/EDT, seam) of ≤ 1 jnd at the threshold, in rooms with open faces.
- **4c-3, later 2→1** (also strengthens 4c-1): report beside W1/W2, at the largest room and at 48 and 96 kHz:
  - the effective update interval;
  - the band-energy divergence over time, in dB, between a real-time-emulated render and the synchronous offline render, under a room-size ramp and under a position ramp (Phase 10's harness).
- **For any 3 s remedy:** an offline measurement of E_target change per metre of emitter and listener movement in layouts 4 and 5 at s = 1 and in CR3. The remedy is perceptually supported only where this is below 1 dB per metre, and only at 33 cm/s or slower.

**7. Hand-offs**
- Memory values and customer hardware: Seats 5 and 7.
- Viability of candidates at 100 m: Seat 2.
- Edit-to-hear workflow: Seat 6.
- The AQ10 amendment under 4c-2: Maisara.

**8. Premortem.** Under 4c-3, a producer automates room size on a drop and monitors a sweep that arrives about 2 s late with audible stepping, and the bounce differs from what was monitored. Beta users notice first, through the Phase 10 listening checklist.
