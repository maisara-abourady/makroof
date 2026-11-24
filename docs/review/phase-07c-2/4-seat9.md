<!-- Saved by the orchestrator from seat 9's report, 2026-11-22. -->

SEAT 9 POSITION, phase 07c-2 round 1, on D-W1 and D-W2. Corpus present (SOURCE_COMMIT c1b171f).

# D-W1: W_max under (C)

**1. Reading.** Which real rooms, or rooms in the FR-3D-3 preset categories, sit in the capped class at each W, and what the raise does to them. Cues triggered: coefficient and estimator provenance at the preset (§4 "honest inputs"), and "late change after commitment" (W1, Philharmonic Hall). A raise re-opens every capped prediction.

**Which fixtures are capped, at the pin (F5, from the D5 golden):**
- **Halls:** `large_hall` (24,300 m³) and `concert_hall_box` are not capped. They stop at n*_max. By F11 their final range is identical at any larger W, so the raise changes nothing there (step 0).
- **Domestic:** `asymmetric_materials` (173 m³) is capped and work-stopped (N_need 703 against N 128). By today's pilot it uncaps at about ×2.5. `medium_room` (384 m³) is floor-truncated and work-stopped (block form ×1.30). Both pilots are re-estimated at a larger W, so these multipliers are estimates, not fixed points (F11).
- **Outdoor:** `open_field` is capped at every option (uncapping needs ×385).
- **Not real rooms:** the 100 m low-α cubes. At α 0.05 the Sabine T60 is about 54 s before air absorption; Kuttruff puts large churches at about 10 s at most (§3, eq. 3.70 text).
- **Stress cases:** layouts 4 and 5 at s = 1 (F4 T3).
- **Missing:** no church-class fixture exists, so the churches half of the "halls, chapels & churches" category is uncovered at every W.

**2–4. Ranking, with now / later ratings (0–3)**

| option | label | now | later | reason |
|---|---|---|---|---|
| W-6 | prefer | 0 | 1 | Accuracy at the rooms is my criterion 2. Later debt: its target set holds no preset-class room (no church), so "floor met" can be shown on stress cubes only. Evidence arrives in 12-2. |
| W-1 | can live with | 1 | 1 | About ×8–11 by my arithmetic: 3 s ÷ 44.7–56 ns per scene evaluation, single thread (F2), on the s = 1 cube, because the gated cubes saturate (F4). That uncaps both domestic fixtures and most of layout 5. |
| W-2, W-3 | can live with | 0 | 1 | No real-room gain over W-1. The cost falls on other seats. |
| W-5 | can live with | 1 | 1 | Holds only if the binding term is not W-4 as written (my condition below). |
| W-4 | can live with | 1 | 2 | The 8 × 100 m / 96 kHz settle is already 9.7–13.3 s at the pin (F6). If W-4 binds, W stays about ×1. Then `asymmetric_materials` stays capped: achieved SE about 0.083·√(703/128) ≈ 0.19 dB, p95 about 0.38 dB [Inf]. That is under the 1 dB G jnd (Vorländer Table 6.1), so now 1. Later 2: in 12-2 it uses about 40 % of a 1 dB G match against a measured reference at a domestic preset, before any model error. |

Undoing any option costs a parameter change plus one golden round. Evidence that could overturn a rating arrives in 07c-2 CI (F3/F4 on three OSes) and 12-2.

**Keyless-load consequence**
- **K-a:** 0 / 0. Time is not my measure.
- **K-b:** 1 now / 2 later. For rooms stopped at n*_max and uncapped, the (A) interim equals the final (F11), so the step is 0. On capped or both-near placements, the F4 band drift ×1 → ×16 is over 1 dB: layout4 both_corner 3.72 dB, layout5 both_wall 2.22 dB, layout5 emitter_wall 1.32 dB, layout4 listener_edge 1.15–1.25 dB. Those are AX47 breaches, and a speaker in a room corner is a real producer placement.
- **K-c:** not rated, nothing on the table.

I accept the sequencing (the value now, the keyless path after the ABX, the golden round after both), on condition 4 below.

**5. Evidence**
- Kuttruff §3 (eq. 3.70 text): T up to 10 s for large churches; most large halls 0.7–2 s. Corpus.
- Vorländer Table 6.1: G jnd 1 dB. Corpus, via researcher R5.
- Kuttruff §5.6 Eq. 5.44: r_c = √(A/16π). Corpus.
- F5, F11 and F4 T3 for the capped lists and drifts.
- All other arithmetic is [Inf].
- [Hyp], for the researcher: the volumes of real large churches. I believe they are about 10⁴–10⁵ m³, well under the 10⁶ m³ cube.

**6. Conditions of acceptance**
1. **W-4 (2 → 1):** state it on the solve share of the settle, not the total. Synthesis dominates at 96 kHz (F7: solve is 1.6–2.3 % of a rebuild).
2. **W-6 later (1 → 0):** add a church-class validation fixture to the reported set before 12-2. Suggested: about 2–5 × 10⁴ m³, T60 6–10 s at mid, stone surfaces α about 0.02, an occupied floor [Hyp; register]. Run W-6 on the preset-class fixtures as well as the cubes.
3. **All options:** the golden round prints, per fixture, cap hit, N_need/N_cap, achieved SE and |ΔE_b| (A → new W) at 500 Hz–2 kHz. This is my AX48 recorded input.
4. **K-b (later 2 → 1):** the class (c) round must treat the over-1 dB drifts above as excluded or bounded, not average them away.

**Companion items**
- **(b), (c), (e), (g):** NOT MY MATTER (Seats 2, 3 and 5).
- **(d):** confirmed from my side. The work-stopped class includes two domestic fixtures, so the golden round re-derives them and must not assume the prefix.
- **(f):** I confirm that Phase 12 runs at 07c's W, on condition that 12-2's preset records print cap status and SE per preset.

**7. Hand-offs**
- Whether both-near cases are solvable by W at all: Seat 2. VOV does not improve with W (F4 finding 5).
- Floor clauses: Seat 1.
- Time bases: Seats 5 and 6.

**8. Premortem.** If W-4 binds near ×1, a domestic preset ships capped and eats part of 12-2's 1 dB match budget unseen. I notice first, in 12-2.

# D-W2: scene plausibility for the ABX

**1. Reading.** Do the capped layout-4 scene and L4's T60 8 s room stand for real rooms or presets, so that the ABX result transfers? Cues triggered: D/R at the listener; shape and occupancy; the source's own room.

**Layout 4 (20 × 30 × 10 m, 6,000 m³):**
- **Reverberation time:** A = 600·1 + 1,600·0.01 = 616 m², so Sabine T = 0.161 × 6000 / 616 = 1.57 s. Eyring (mean α 0.28) gives 1.34 s.
- **What it stands for:** a fully occupied mid-size hall in the halls category. Kuttruff §3.1: the audience dominates absorption in occupied halls.
- **Where it is unreal:** walls at α 0.01 are harder than any real finish. The floor at α 1 is flat across 63 Hz–8 kHz, where a real audience falls at low frequencies. s = 1 everywhere. It is a stress envelope, not a preset.
- **Default placement:** r ≈ 12.4 m and r_c = √(616/16π) ≈ 3.5 m, so r/r_c ≈ 3.5 and D/R ≈ −11 dB (diffuse-field estimate; the absorbing floor makes it non-diffuse) [Inf]. A 1 dB tail step then moves the total by about 0.93 dB. That is the conservative, tail-dominated seat a producer uses.

**L4 room:**
- **Decay:** T60 8 s is church-class (Kuttruff: up to 10 s), so the late decay transfers.
- **Volume:** 10⁶ m³ is not a real room [Hyp: 10–100 × a large church]. Uniform α of about 0.3 is unlike a church's hard walls and absorbing pews.
- **Why it still transfers:** the cut point scales with T60 (L_f includes 0.312·T60, AX49), so the decay depth at the cut is the same at any T60.

**2–3. Options X-1 to X-5:** the paradigm and the family are Seat 1's ground. From my seat:
- **X-1:** can live with, 1/1. It says nothing at 0.5 dB, and that is the reversal bound. Zotter & Frank §4.8 (researcher R8) report differences under 0.5 dB audible in noise.
- **X-3 or X-5 with sizes reaching 0.5 dB:** prefer, 0/0.
- **X-2:** can live with, 0/1.
- **X-4:** NOT MY MATTER.

**4. Debt.** If the scene is presented as a preset, the class (c) admission and 13's public wording claim "inaudible in halls" from a stress room. Undoing it costs re-running the ABX, which is a person's time. The evidence arrives at 12-2 preset validation.

**6. Conditions (my sub-items)**
- **(i) Layout-4 placement:** use `default`, not both_corner. Its variance is pathological (F4) and it is not the typical seat. Print r/r_c and D/R at the listener in the record, so the result transfers to presets by D/R.
- **(ii) The step:** apply it equally in all 8 bands. A broadband step is the worst case for loudness.
- **(iii) The record names what each scene stands for:** "occupied mid-size hall envelope, T about 1.4 s" and "church-class T60, volume not a real room". It also states that no preset was validated.
- **(iv) The recorded speech must be anechoic or close-miked dry,** with that property documented. A source carrying its own room adds its own reverb to the rendered one (Begault, corpus: auditorium-simulator flaw). That would mask the tail step and bias the result toward "not detected". Read-audiobook corpora such as LibriSpeech need checking on this point. For the researcher: verify which candidate source is anechoic.

**7. Hand-offs**
- Output mode, headphones or speakers, level matching: Seat 4. Note that omni drops binaural loudness cues.
- Crossfade law: Seat 3.
- Licence: Seat 7.
- Direction and family: Seat 1.

**8. Premortem.** If the test runs on both_corner with reverberant speech and comes out "not detected", the 1 dB bound stands on a masked stimulus. A listener hears a step in a church preset after release, and Seat 1 or I notice first, at 12-2.

Files: the briefs are in `/home/user/makroof/docs/review/phase-07c-2/1-decider-convening.md`; the facts are from `/home/user/makroof/docs/review/phase-07c-2/2-fact-sheet-part1.md`, `/home/user/makroof/docs/review/phase-07c-2/2-fact-sheet-part2-wsweep.md` and `/home/user/makroof/docs/review/phase-07c-2/3-researcher-RQ-W1-W2.md`; the scene files are in `/home/user/makroof/tests/scenes/valid/`.
