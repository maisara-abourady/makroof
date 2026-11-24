# 29-seat9: Seat 9 on M3-H (brief B9)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 9 POSITION (M3-H re-run, brief B9; read-only; for `/home/user/makroof/docs/review/phase-07c-2b/29-seat9.md`)

**1. Reading.** Where and when the board rules the cause of findings (a) both_corner −6.2 dB, (b) both_wall onset 0.165 / 0.380 s and (c) s0.7 −1.23 dB. For my seat, the question is whether that ruling comes before phase 12-2 builds the presets. Cues: §4 "late change after commitment" (a ruling after the presets are built reopens them, as W1 did); §6 S2 (the s0.7 room is non-diffuse, with all absorption on the floor); §6 S8 (the 1 kHz "physics" offered to excuse (a) has to be checked before it is trusted).

**2. Ranking**
- **Prefer: H4+G, H4, H3+G, H3, H2-cg.** All five rule before 12-2. Under H4 the chain is 12-2 → 11 → 09 → 08 → 08-4 → 07e (file 20). 07d precedes 08-4 (phase-07d L79–80), so the same holds for H2-cg. My row cannot separate these five. G1–G3 are Seat 5's matter.
- **Can live with: H2-c.**
- **Can live with, at a major later cost: H1.** It is not veto-grade, because no measured reference is traded away.

**3. Tension now.** All seven options: **0**. My seat does none of the work. The only cost is one hand-off answer to 07e's loop on (c) and the presets.

**4. Tension later**
- **H1: 2.** 12-2's 8 presets would be built, checked against their T30 ranges (12-2 AC4) and listened to by Maisara in both modes on an engine whose corner tail has not been ruled. `car_cabin_box` is a box near the minimum size. In it the speakers almost certainly sit within 0.5 m of 2–3 faces, and the listener within 0.7 m of a face. A fix found at 13-2 means re-checking the presets, re-listening (8 presets × 2 modes) and possibly moving placements. That is about one sub-phase of rework, and the evidence arrives at 13-2.
- **H2-c: 1.** The ruling still comes before 12-2. But 08-3 item 15's F3/F4 stimuli can be sealed under the labels I confirm while the cause is unknown. If the S-W scene falls back to both_corner (third in the fallback order), its SPREAD clause states a −6.2 dB spread nobody has attributed. If a fix is later ruled, I confirm the labels again and M3-8 rebuilds the stimuli. That is one label round per scene.
- **H2-cg, H3, H3+G, H4, H4+G: 0.** The ruling precedes both the F3/F4 seal and 12-2.

**5. Evidence. 12-2 placements, and what a real room does at a boundary**
- **12-2 presets [Inf; car: Hyp, no incident, §18].**
  - From the fixtures: in `living_room` the emitters are 1.0 m from the rear wall and 1.0 m above the floor; in `club` they are 2 m from the front wall. Neither is within 0.5 m of a face.
  - Real practice pulls three presets closer: speakers 0.2–0.5 m from the front wall in living rooms, PA tops near the stage's back wall in clubs (one face), and door and dash speakers in cars (two to three faces).
  - Halls and chapels: no.
  - AX44 Seat 6 (ii) bars U at preset defaults, not near-face placement.
- **What a real room does (lead, not fact).** Toole §12.1 (corpus, L1611–1621):
  - At low frequency the radiated power of a small monopole rises +3, +6 and +9 dB for 1, 2 and 3 adjacent rigid faces (SPL +6, +12 and +18 dB).
  - This holds only when the wavelength is long compared with the separation. Fig. 12.2 shows interference dips in the 3-face case near 250 Hz and 800 Hz (L1627).
  - At 1 kHz and 0.1 m, kd = 1.83. That is outside the long-wavelength limit, so the "+9 dB, more power" reading does not apply.
- **My arithmetic.** It rests on the image-sum formula P/P₀ = 1 + Σ sin(kr_i)/(kr_i) (Waterhouse 1958). Toole cites that paper, but the formula is not in the corpus, so it is [Hyp] and the researcher should verify it under R-H1. Rigid faces and 7 images (3 at 0.2 m, 3 at 0.283 m, 1 at 0.346 m) give:

| frequency | radiated power vs free field |
|---|---|
| 125 Hz | +8.8 dB |
| 250 Hz | +8.1 dB |
| 500 Hz | +5.0 dB |
| 1 kHz pure tone | −10.7 dB (a notch) |
| 1 kHz octave, 8-point average | ≈ −3 dB |
| 2 kHz | ≈ +0.5 dB |
| 4 kHz and up | ≈ 0 dB |

- **What this means for (a).**
  - At 1 kHz real physics points down, not up, so Seat 2's "wrong way" [Hyp] does not hold at this frequency.
  - But the size (≈3 dB, not 6.2) and the strong frequency dependence do not match (a).
  - The engine is geometric and incoherent. AX44's "GA limit" clause already says the near-wall effect is not modelled ("GA-true, not room-true").
  - So boundary physics cannot be what the engine is showing.
  - **Falsifiable claim:** if (a)'s deficit is within ±1 dB of flat from 125 Hz to 4 kHz, it is an engine effect, not boundary physics. Real rooms would show ≈ +9 dB below 250 Hz.
  - A real loudspeaker's box (Toole: 0.43 m) cannot have its acoustic centre 0.1 m from three faces, so the finding's geometry is a point-source idealisation.
- **(c)'s attribution needs:**
  - an independent reference for the late level at equal times in that non-diffuse room, for example the AX37 (5.4) seeded tracer, not Eq. 5.42, with an uncertainty under 0.5 dB, since 1.2 dB is about 1 JND of G;
  - a diffuse control: the same room with the absorption spread to the same ᾱ.
  - If the spread survives in the control, the engine causes it. If only the reference reproduces it, the room does.
  - Every report-only home can provide this. The file 17 §3 skeleton's scope 3 lacks both.

**6. Conditions of acceptance**
- **H1, 2 → 1:** the cause ruling (no fix) precedes 12-2's preset build. Alternatively, no preset default places an emitter within 0.5 m of two or more faces until the ruling, and `car_cabin_box` is labelled "stylised, unvalidated at near-face placements".
- **Every home (does not change any rating):** 07e scope 3 adds three things:
  - the band-wise deficit for (a), 63 Hz–8 kHz;
  - an indicative rigid-boundary column, printed and never used to explain a deficit away;
  - for (c), the diffuse control and the independent reference.
- The verdict for (a) is judged against the GA-internal equal level. The skeleton's "if 12-2 has started" becomes "which planned 12-2 presets place a source within 0.5 m of a face" (file 20 marked the old clause IMPRECISE).

**7. Hand-offs**
- Seat 2: the band-flatness test. Also put AX44's w-blend (w depends on d_E, which is 0.1 m for L) on (a)'s candidate list [Inf].
- Seat 1: whether (a) and (b) are audible.
- Seat 8: how often producers place sources at walls.
- Seat 6: whether a drag stops at exactly 0.1 m.
- Researcher: verify the Waterhouse formula and the ≈ −3 dB octave-band average.

**8. Premortem.** Under H1, `car_cabin_box` ships built on a tail later found wrong at corners. The first to notice is Maisara at 13-2's re-listening, when the car preset changes character.

Files read: 28-decider-m3h.md, 5-builder-tail-spread.md (L1–40), 17-decider-m3-r4.md, 20-interrogator-on-file17.md, 14-seat2.md, 14-seat7.md, 22-seat2.md, 22-seat5.md, 14-seat9.md; PRD L40–179; BUILD_PLAN §0 (07d, 08-x, 11, 12-x), AX5, AX6, AX44; phase-07d L75–103, phase-08-3 L1–87, phase-08-4 L20–27, phase-12-2 (full); tests/scenes/valid/living_room.json, club.json; corpus Toole L170–177 and L1598–1677, Kuttruff L3978–3987 (all under /home/user/makroof/).
