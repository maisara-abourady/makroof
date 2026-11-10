# Seat 3 (reverb renderer) — positions on D-T5 and D-T4

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 3 POSITION

Corpus present (`docs/corpus/`, revision c1b171f). Files read: the convening file, phase-05b2, AX16/20/21/22/33/36, AQ4/AQ10, `NoiseTail.cpp`, `Engine.cpp` L47–51 and L115–151, `ref_hybrid.py` L480–533, the `open_field` scene and golden, report-phase05b §5/§5b, phase-10 scope 2 and its acceptance gates, Vorländer §15.2–15.3.

# Decision D-T5

**1. Reading.** Which energy sets the tail level, which list decides the fallback, what the direction diagnostic describes, and what `open_field` becomes. Cues from my §4: "tail level against the computed room" (decay and level accuracy); "jump point under automation" (state discontinuity); channel spreading (spatial correlation).

**2–4. Ranking and tension (now / later).**

*(1) What E_target is built from*
- **5.1-A: prefer. Now 1, later 1.**
  - Now: at the seam the tail moves by −ΔL_b. That is −3.84 dB in layout 4 at s = 1, +1.13/+1.14 dB in layouts 5/6 at s = 1, and −0.11…−0.43 dB in the uniform cases (report §5). The seam mechanism does not change: still a 5 ms equal-power fade between uncorrelated parts (AX18).
  - The AX21 envelope step at t_mix,e (measured −1.8…+9.8 dB in Phase 04) moves by −ΔL_b in each case. It shrinks where AX16 over-predicted and grows by about 1.1 dB in layouts 5/6. The EDC seam gate cannot see this step (AX21), so it has to be reported again on the switched IRs.
  - Later: Phases 08, 09 and 10 inherit E_b. 63–250 Hz and 4–8 kHz are not validated (D5-K2), but AX16 is not validated there either. Undo cost: one golden round.
- **5.1-C: can live with. Now 2, later 2.**
  - Now: two models in adjacent bands. In layout 4 at s = 1 the band ratio is wrong by up to 3.84 dB at the 250/500 Hz and 2/4 kHz crossovers. That is a shelf-shaped colouring of the tail that no room produces (my criteria 2 and 3).
  - Later: two energy models stay in the level path for good. Undo cost: a golden round plus agreement tests in five more bands.

*(2) What the AX22 realised-k test counts*
- **5.2-A: prefer. Now 1, later 1.** The jump point stays where it is in position space. On how Phase 10 is affected, see the addendum answer below.
- **5.2-B and 5.2-C: not rated (out of bounds).**

*(3) What `bandsAxisShares` describes, and what Phase 08 receives*
- **5.3-A: prefer. Now 0, later 1.** Under 5.2-A, k_real, σ and the axis shares, which AX22 reports together, all describe the one list that decides the fallback, so the diagnostic set stays consistent. The debt is that someone may read the shares as the tail's directions; a label fixes that.
- **5.3-D: can live with. Now 0, later 1.** It is honest, but it changes a reported number and breaks that consistency with k_real.
- **5.3-B: can live with. Now 1, later 2.** It makes D-T1 produce per-direction window energies for a diagnostic nobody reads.
- **5.3-C: can live with. Now 2, later 2.**
  - No evidence yet that the anisotropy is audible (RQ6).
  - It adds direction-dependent noise synthesis to the build work of every instance.
  - Phase 08 would then depend on 05b/05h. Undo cost: Phase 08 rework.

*(4) `open_field`*
- **5.4-A: prefer. Now 1, later 2.**
  - The IR becomes: direct sound, the floor reflection, digital silence until about 1.40 s, a 5 ms fade-in of noise at E_b, then decay at the nominal Eyring rate until about 1.80 s (86 549 samples).
  - My arithmetic [Hyp, C1 will give the real numbers]:
    - The farthest floor path (source, floor corner, listener) is about 146 m, so the diffuse energy ends at about 0.43 s.
    - Referring it to 1.404 s along Eyring costs about −53 dB at 63 Hz (11.1 /s), about −104 dB at 1 kHz and about −260 dB at 4 kHz.
    - Normalising to 10 ms over a half-window of about 0.67 s costs about −18 dB more.
    - So the onset is about −95 to −100 dB re the direct sound at 63–125 Hz and below −140 dB above 500 Hz.
  - What it does to the render:
    - CPU is unchanged: the IR length is 1.5 × max T60 whatever E_b is (from the code, `tailLengthS`).
    - No click, because the tail fades in from zero.
    - Values that underflow at 4–8 kHz are flushed to 0 (Engine.cpp L47–51).
    - No new jump point: E_b and t_cap are continuous in position.
  - The shape (silence, then a tail) has no physical basis. Here it does no harm only because of its level.
  - Later 2: smaller generic open boxes give a shorter t_cap (V = 9 000 m³ gives t_cap ≈ 0.44 s by Eq. 4.6 integrated), so the referral is milder and this "ghost tail" could be audible in FR-3D-3 outdoor presets.
- **5.4-B: can live with. Now 2, later 2.**
  - Any rule of the form "the diffuse energy has vanished" is a new switch point. Example: automating a wall from α = 1 to 0.999 takes E_b from 0 to the full single-generation level in one step (FR-SIM-6, my criterion 1).
  - Phase 10 would have to gate a second switch point.

**Addendum answers.**
- **Seam at t_mix,e:** as under 5.1-A above. The level is a window functional; the per-bin envelope at t_mix,e was never validated (gate A not evaluated, AX36 (b)).
- **Does 5.2-A leave Phase 10's continuity work unchanged?** In method, yes:
  - the switch point stays in the same place in position space;
  - the AX22 gate stays (≤ 1 dB dip, f ≤ 0.21) and so does its fallback (a time-segment-split crossfade);
  - its inputs change: ρ and f now come from the switched E_b. Phase 10 measures after 05b, so this happens by itself.
  - 5.2-A also keeps t_mix,e independent of the diffuse energy. That is what lets Phase 10 later update the diffuse part on Table 15.1's 3 s / 1 m interval without moving the handover (see D-T4).
- **Does the renderer need tail directions?** No, not for omni or stereo. My S6 is one late field per room, fanned out by decorrelated outputs. Two further points:
  - `bandsAxisShares` is u², so it cannot tell which side the energy comes from (floor vs ceiling); it could not drive a directional tail even under 5.3-C.
  - Binaural is Seat 4's question.

**5. Evidence.**
- Late field after about 140 ms can be a statistical decay [Observed]: Vorländer §15.3, citing Meesawat and Hammershøi.
- Envelopes in 10°×10° directional sections are "sufficient for late reverberation" [Observed]: Vorländer §15.2, Fig. 15.5. That is a representation that works, not proof that direction is audible.
- Dip law: Vorländer Eq. 4.14 (via AX22).
- ΔL_b values: report-phase05b §5.
- `open_field` levels: my arithmetic [Hyp].

**6. Conditions of acceptance.**
- 5.1-C → its only lower-tension form is 5.1-A.
- 5.3-C → 1 if it is deferred to a Phase 08 AX that only triggers when RQ6 shows audibility.
- 5.4-A (later) → 1 if C1 also computes one smaller generic open box and Seat 1 judges both onsets inaudible.
- 5.4-B → 1 only if the rule is proven continuous: no threshold where E_b steps by more than Seat 1's bound.

**7. Hand-offs.**
- Seat 2 / D-T1: a check of E_b continuity in position (patch and 1 ms bin crossings), maximum step per 1 cm.
- Seat 1: audibility of the ghost tail and of 5.1-C's band seam.
- Seat 4: whether binaural needs directions.
- Researcher: RQ6. Orchestrator: C1, plus the small open box.

**8. Premortem.** Under 5.1-C, a club preset's tail sounds hollow at 250/500 Hz, and Maisara hears it first in the listening pack.

# Decision D-T4

**1. Reading.** The cost envelope of the diffuse computation. Cues from my §4: cost (memory, update time), and update interval under automation, which feeds state discontinuity.

**Facts that bound my seat.**
- Audio-thread cost per instance does not change: IR length and partitioning are unchanged (from the code).
- The energy-domain bins are Δt = 1 ms, so the diffuse memory should not scale with sample rate [Hyp].
- The AQ4 chain (AQ4, AX31, AX33; my derivations [Hyp], Phase 10 measures):
  - An isolated update arrives after R + 2P (2P = 21.3 ms at P = 512, 48 kHz), then a 30 ms fade.
  - Under continuous automation the worst-case staleness is about 2R + 2P (a change arriving just after a build starts).
  - Phase 10's ≤ 100 ms staleness gate therefore needs R ≤ 39 ms. Today: Linux W2 is 28.5 ms, giving about 78 ms; Windows W2 is 41.6 ms, giving about 105 ms.
  - Table 15.1 (700 ms) needs R ≤ 339 ms.
- Room-size automation is a full rebuild on every update. Today that is 0.60–0.80 s at 48 kHz and 1.5–1.9 s at 96 kHz at the largest room. A size sweep is therefore heard as steps, each a 30 ms crossfade between nearly uncorrelated IRs: a 3 dB mid-fade dip under equal-gain (AX18). Whatever diffuse time the switch adds lengthens each step.

**2–4. Ranking and tension (now / later).**

*(a) Memory ceiling*
- **4a-2 (≤ 1 GB): prefer. Now 1, later 1.**
- **4a-1 (≤ 128 MB): can live with. Now 1, later 2.**
  - The tight cap pushes toward recomputing instead of storing, which lengthens R and therefore every update interval.
  - It raises the risk of D-T3, whose size threshold would be a jump point under room-size automation.
- **4a-3 (≤ 4 GB): can live with. Now 2, later 2.**
  - Ten instances at their peak need about 40 GB; this fails my "cost scales" criterion.
  - Peaks coincide at project load.
- **Does any ceiling force D-T3 at 100 m?** None of the three rules out every candidate class [Hyp, Seat 2's ground]:
  - The dense kernel is out under all three (3–6 TB).
  - State proportional to N·T: 9 600 × 2 100 × 4 B ≈ 81 MB per band, about 645 MB for 8 bands. It fits 1 GB, and 128 MB only if bands are processed one at a time.
  - A Monte-Carlo tally is proportional to T only.
  - Time, not memory, is the likely forcing factor.

*(b) How W1/W2 are read*
- **4b-1: prefer. Now 1, later 1.** It measures the update rate the user will hear, provided the cache is real.
- **4b-2: can live with. Now 1, later 1.** It is conservative, but it may lead Phase 10 to pursue the Table 15.1 slow-update remedy when it is not needed.

*(c) What blocks and what is recorded*
- **4c-2: prefer (as a protection, not for its yardstick). Now 1, later 1.** It is the only option that bounds the step size of room-size automation in large rooms. The right yardstick is the update interval against Table 15.1 (700 ms / 3 s), not the HCI response-time base rates of RQ5.
- **4c-1: can live with. Now 1, later 2.** The full rebuild at large rooms can grow without limit, which turns room-size automation into multi-second jumps. This borrows from Phase 10's position-fade and staleness gates. Undo cost: rework of D-T1.
- **4c-3: can live with. Now 2, later 2.** If a build fails or stalls past the ceiling, the room stops following automation and then jumps [Hyp].

**5. Evidence.**
- Table 15.1 [Observed]: Vorländer §15.3, after Lentz et al. 2007. 700 ms for moves > 0.25 m (specular part); 3 s for moves > 1 m (scattering part); translational movement 30–50 cm/s.
- Rebuild times: §0 row 07. W1/W2: AX22.
- The staleness formula and the memory arithmetic: [Hyp].

**6. Conditions of acceptance.**
- 4a-1 → 1 if Seat 2 marks a class that plausibly fits at 100 m, and any D-T3 threshold carries a continuity test under room-size automation.
- 4a-3 → 1 if resident memory stays ≤ 1 GB and only transient peaks reach 4 GB, with builds serialised across instances (Seat 5).
- 4b-1 is acceptable only if this session implements and tests the cache (equal to a full rebuild within −120 dB) and its key is complete (room, materials, sample rate).
- 4c-1 → 1 if the record also states the implied AQ4 intervals (2R + 2P; full rebuild + 2P) at 48 and 96 kHz against 100 ms, 700 ms and 3 s, and a full rebuild above 3 s at 100 m goes to Maisara with the numbers.
- 4c-3 → 1 under 4c-1's condition plus a defined, no-step behaviour when a build fails.

**7. Hand-offs.**
- Seat 5: concurrent builders and their peaks; behaviour when a build fails.
- Seat 6: how fast users automate room size.
- Researcher: RQ2 and RQ3; whether room-size automation is common at all.
- Phase 10: checking the 2R + 2P staleness formula. Windows W2 may already be at about 105 ms.

**8. Premortem.** Under 4c-3 with 4b-2, the diffuse part takes R into the hundreds of milliseconds, Phase 10's 100 ms staleness gate fails with no listed remedy, and the contracted engineer finds it at Phase 10.
