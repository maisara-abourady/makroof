# Seat 9 (room acoustician) — positions on D-T5 and D-T4

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 9 POSITION (two blocks: D-T5, then D-T4). The corpus is present (14 files). None of my persona's assumptions conflicts with the PRD or the settled rows.

---

## D-T5: how the switch interacts with the matching

**1. Reading.** Once the AX16 entries stop setting the tail level, this decision defines four things: E_target, the k_real basis, the axis shares and the `open_field` outcome.
- Cues it triggers: coefficient provenance and concentrated absorption (S2); occupancy (people as a material); and "late change after commitment" (W1).
- There is no incident for outdoor fields without reflectors (§18), so every outdoor claim below is `[Hyp]`.

**2. Ranking**
- (1) 5.1-A *prefer* · 5.1-C *can live with* only under the condition in §6 below.
- (2) 5.2-A *can live with*. 5.2-B and 5.2-C: not rated (out of bounds).
- (3) 5.3-D *prefer* · 5.3-B *can live with* · 5.3-A *can live with* · 5.3-C *can live with* only under the condition in §6.
- (4) 5.4-A *prefer* · 5.4-B *can live with*.

**3–4. Tension now / later (0–3)**

| option | now | later | reason, in my measures |
|---|---|---|---|
| 5.1-A | 1 | 1 | The model is the same physics in every band; only its inputs (α, s, air m) change. It is validated only at 500 Hz–2 kHz (D5-K2). If a 4–8 kHz check fails, the fix is a tolerance or parameter change, not a rewrite. |
| 5.1-C | 2 | 2 | It keeps AX16's known error exactly where seating and carpet contrast is highest (see §5). Two energy models then meet at the 2→4 kHz seam, so the tail's treble balance can carry the whole AX16 error. Undoing it later means a second golden regeneration and a second switch. |
| 5.2-A | 1 | 1 | k_real is a density ratio (S²/Q), so it is insensitive to a uniform level error. AX16's mis-weighting in concentrated-absorption rooms barely moves it. In real scattering rooms the field is denser than the AX16 list shows, so this may over-trigger the fallback. That is a later AX22 matter. |
| 5.3-A | 1 | 1 | It keeps reporting the directions of a model this phase declares wrong. The output needs to be labelled, nothing more. |
| 5.3-B | 1 | 1 | It is the most physical diagnostic, but nothing consumes it. Its cost falls on Seats 2 and 7. |
| 5.3-C | 2 | 2 | It spends engine and Phase 08 budget on late-field anisotropy that has no JND-crossing case (§2 criterion 1). It also adds the 05b/05h dependency to Phase 08. |
| 5.3-D | 0 | 0 | It is honest and cheap. Flutter, which the AX22 shares exist to detect, is a specular phenomenon. |
| 5.4-A | 1 | 1 | The outdoor tail is an artefact: physical ground scatter arriving 0–0.37 s after the direct sound reappears at 1.4 s, but far below audibility (estimate in §5). The check it adds is against an independent integral. |
| 5.4-B | 1 | 2 | It needs a new rule whose only effect is to preserve one fixture's old golden, which comes close to "tuning for a scene". If it uses a relative threshold, that threshold is an invented number and a new discontinuity to carry into Phase 10 and D-T3. |

**5. Evidence**

*Real venues with concentrated absorption*
- Seating against the residual surfaces, from the corpus tables:
  - Unoccupied seating α is 0.36–0.70 at 125 Hz and 0.60–0.84 at 2 kHz (Kuttruff §6.7, Table 6.4).
  - α at 4 kHz is 0.60–0.81, essentially the same as at 2 kHz (Table 6.4).
  - The residual walls are 0.08 at 1–4 kHz and 0.12–0.16 at 125 Hz (Table 6.5).
  - So the contrast is about 8–11:1 at 2–4 kHz and about 3–5:1 at 125 Hz (my arithmetic). `[corpus]`
- Kuttruff calls the absorbing-floor case 4 a "crude model of most auditoria" and says real halls are less dramatic (§5.7). `[corpus]`
- The error each option leaves:
  - **5.1-A**: ≤ 0.08 dB at 500 Hz–2 kHz (report §5); unverified elsewhere.
  - **5.1-C**: AX16's full error at 4 kHz. That error is likely the same order as at 2 kHz (BRAS CR3 −1.18 dB, −1.47 dB with per-band s), because the contrast is the same. `[Inf]`
  - In large halls, air absorption at 4–8 kHz is volume absorption. It spreads the absorption more evenly and should shrink AX16's error at 8 kHz. `[Inf]`
- A tail-level error moves G by less than ΔL. Comparing it with G's 1 dB JND is an extension (Vorländer Table 6.1, as AQ9 does).

*Outdoor, `open_field` (my arithmetic, `[Inf]`; C1 must confirm)*
- The last single-scatter floor path is 68.1 + 78.1 = 146 m, arriving at 0.43 s. The direct sound arrives at 0.06 s.
- Referral from ≤ 0.43 s to the 1.404 s handover uses the nominal Eyring rate of 13.8/T60. That is ≥ 92 dB down at 1 kHz (T60 0.636 s) and ≥ 47 dB down at 63 Hz (T60 1.24 s).
- The normalisation 10 ms/(L/2) with L/2 ≈ 0.67 s takes off another 18 dB.
- The tail therefore starts at least 65 dB (63 Hz) and 110 dB (1 kHz) below the ledger OF ground-scatter estimate (−23 to −43 dB per band).
- No real outdoor response I can cite shows a smooth tail starting about 1 s after the last ground arrival. Distant reflectors give discrete echoes. `[Hyp; no incident coverage]`

*Honest preset validation (FR-3D-3)*
- 5.4-A checks against an exact Lambert integral, which is an independent reference.
- 5.4-B protects a self-generated E_b = 0.

*Researcher and orchestrator items*
- (a) Measured open-field and festival-ground IRs: the level and timing of late energy over grass.
- (b) ΔL_b (AX16 against the hybrid) at 125 Hz, 250 Hz, 4 kHz and 8 kHz for CR2 and CR3, and the tracer at 4 kHz and 8 kHz on 2–3 (A) cases. This is orchestrator compute at the cost of the existing runs.

**6. Conditions of acceptance**
- **5.1-C** drops to 1 if item (b) shows |ΔL_b| ≤ 0.3 dB in every band outside 500 Hz–2 kHz in BRAS and the six Phase 04 rooms. Otherwise it stays at 2.
- **5.1-A** stays at 1 provided item (b)'s 4–8 kHz tracer check is run and reported before the goldens are frozen.
- **5.3-C** drops to 1 only if RQ6 finds a JND-crossing case of late anisotropy with a generic HRTF. Otherwise put it in the post-v1 backlog with a test plan.
- **5.4-B** drops to 1 only with an exact-zero criterion (no threshold), following the AX20/AX22 zero-pruning precedent.
- **5.4-A** stays at 1 if C1 shows the rendered energy after 0.5 s is ≥ 60 dB below the direct sound in every band. If it is within 60 dB, it rises to 2 and I would prefer 5.4-B. The 60 dB line is the convention for the end of a decay, applied here by extension. `[Inf]`

**7. Hand-offs**
- Seat 1: is the 4 kHz seam audible?
- Seat 4: whether a diffuse-coherence tail is wrong in anisotropic real rooms.
- Seat 2: AX21 means the −23 to −43 dB of real ground scatter is missing from the early part under both 5.4 options. This is the larger outdoor error, and it is not D-T5's.
- AX17: broadband s overstates ground scatter at low frequencies (ledger OF).

**8. Premortem.** If 5.1-C is chosen, a hall preset with upholstered seating matches its measured reference at 2 kHz but carries a tail 1–1.5 dB off at 4 kHz. Phase 12's preset validation finds it first, after the goldens are frozen.

---

## D-T4: cost budget

**1. Reading.** This sets the memory ceiling and the blocking rules at the 100 m room.
- Cue: "late change after commitment" (W1, Philharmonic Hall). If the room range is cut after the FR-3D-3 presets exist, every prediction about them reopens.
- Cue: the largest room class is also the class most like Kuttruff case 4.

**Venue classes near 100 m per side** (all `[Hyp]`; for the researcher to verify)
- Large cathedrals: nave about 100–150 m long, 30–45 m high, floor of pews or people and stone everywhere else. This is the closest real analogue to layout 4, which has AX16's largest error (+1.5 to +3.9 dB, a tail that is too loud).
- Arenas of 15–20k seats: about 100 × 80 × 30 m.
- Large warehouses: 50–100 m long.
- Festival grounds and fields: unbounded. The contract represents them by open faces.
- Concert halls: mostly ≤ ~50–60 m per side. TOC is 15,300 m³ (persona register).

**Would a ceiling force D-T3?** For the only measured formulation, the dense kernel: 4a-1 already fails at the AQ10 room (0.47 GB), 4a-2 fails at CR4 (2.5 GB), and all three fail at 100 m by about three orders of magnitude. Whether a scaling candidate fits is Seat 2's call.

One physics point, formulation-neutral: open-face outdoor rooms have no transport beyond the first generation. The cost-worst case at 100 m is the closed, reverberant cathedral-like box, not the festival box. So any D-T3 edge expressed as side length would cut outdoor presets for no physical reason.

**2–4. Ranking and tension (now / later)**

| option | rank | now | later | reason |
|---|---|---|---|---|
| 4a-1 (128 MB) | can live with only under the condition in §6 | 2 | 2 | Most likely to force D-T3 for cathedrals and arenas, the class with the largest AX16 error. Halls, chapels and churches lose their most characteristic member. Undoing it means a contract change (narrowing AX6) or a second formulation. |
| 4a-2 (1 GB) | can live with | 1 | 1 | Excludes the dense kernel from CR4-size rooms (a real 42 m auditorium) up. The D-T3 risk depends on D-T1. |
| 4a-3 (4 GB) | prefer (my seat only) | 0 | 1 | Least pressure on the room range. The memory cost belongs to Seats 5 and 7. |
| 4b-1 | can live with | 0 | 0 | Table 15.1's slower scattering-part update (3 s per 1 m) is consistent with diffuse energy varying slowly with position (Vorländer Table 15.1, as AQ10 states it). Otherwise this is not my matter. |
| 4b-2 | can live with | 0 | 0 | Not my matter beyond the above. |
| 4c-1 | prefer | 0 | 1 | The range question surfaces now, before Phase 12 presets, with numbers in front of Maisara. |
| 4c-2 | can live with | 1 | 2 | It could cut the largest-error room class on a usability limit that is not yet sourced (RQ4, RQ5). |
| 4c-3 | can live with | 0 | 2 | It defers the cut to Phase 13, after the presets are built and validated: a late change to the room palette (W1). |

**5. Evidence**
- The dense-kernel sizes come from phase-05b2 §0.3. `[plan]`
- Case 4 as "crude model of most auditoria": Kuttruff §5.7. `[corpus]`
- Seating contrast: Kuttruff Tables 6.4 and 6.5. `[corpus]`
- Venue dimensions: `[Hyp]`. Researcher: verify them, citing Beranek's hall data, cathedral acoustic surveys and arena dimensions. Also find which public IR databases hold cathedral or arena IRs usable as FR-3D-3 references.

**6. Conditions of acceptance**
- **4a-1** drops to 1 if D-T1 shows a candidate within 128 MB in a closed 100 m box at α ≈ 0.05. It rises to 3 if the D-T3 outcome ships cathedral or arena presets labelled as matching a measured reference while they carry the AX16 tail error.
- **4c-2** drops to 1 if the time limit rests on sourced base rates and the D-T3 packet lists the venue classes it cuts.
- **4c-3** drops to 1 if the threshold is evaluated and reported to Maisara before Phase 12 starts.

**7. Hand-offs**
- Seat 2: whether any candidate scales to 100 m.
- Seats 5 and 7: RAM base rates (RQ1–RQ3).
- Seats 1 and 3: the FR-SIM-6 step at any D-T3 edge.
- Maisara: narrowing AX6.

**8. Premortem.** 4a-1 and 4c-1 force a size cap. Cathedral presets then ship either shrunk, or full-size with AX16's too-loud tail, and Phase 12's reference A/B is the first to hear it.
