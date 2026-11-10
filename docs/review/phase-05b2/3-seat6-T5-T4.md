# Seat 6 (canvas designer) — positions on D-T5 and D-T4

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 6 POSITION: D-T5 (B6-T5)

Corpus present (Kuttruff, Vorländer). One persona assumption no longer holds. My §2 says "hide by physics", but PRD FR-3D-4 exposes per-surface absorption and scattering. So my measure here is narrower: does each physical control do audibly what a real room does, and does it automate without surprises?

1. **Reading.** The switch changes what the user's per-surface α and s controls do to the tail level. Cues from my §4 that it triggers:
   - default and range not at the most real state;
   - one control moving several things (5.1-C);
   - an automatic helper with an invisible trigger (5.4-B);
   - heavy recompute under drags (patch discretisation).

   What the controls do today, from phase-05b2 §0.1:
   - In layout 4 (absorbing floor), AX16's tail error grows from +0.65 to +3.87 dB as s goes from 0.1 to 1. Over the range of the scattering control, its effect on the tail is wrong by about 3.2 dB.
   - In layouts 5 and 6 at s = 1 the sign flips (−1.17 / −1.16 dB). The same control has an error whose sign depends on geometry, so a user cannot learn it.
   - Carpet, seating or an "open side" on one face gives a tail up to 3.9 dB too loud: "reverb pasted on top".
   - Under 5.1-A, all 15 cases are within 0.08 dB of the tracer.

2. **Ranking and ratings** (now / later)

**(1) What E_target is built from**
- **5.1-A: prefer.** Now 1, later 1.
  - Now: the level is right, but the decay stays Eyring (B12). Moving the absorber from a wall to the floor changes level, not decay. That is settled and within my tolerance.
  - Later: patches are 2.5 m. A drag or a room-size sweep crosses patch boundaries and patch-count changes. E_target's ℓ-convergence (≤ 1.27 % ≈ 0.055 dB) suggests the steps are inaudible [Inf]. Evidence arrives in Phase 10 scope 6.
- **5.1-C: can live with.** Now 2, later 2.
  - Now: one broadband s control (AX17) would set the tail level by two different laws, one in 500 Hz–2 kHz and another in the other five bands. In a concentrated-absorption room, automating s becomes a tail EQ move, with seams at 250/500 Hz and 2/4 kHz. No user expects that [Inf; out-of-band size unmeasured, D5-K2].
  - Later: switching the other five bands later means a second golden and listening-pack churn, about a phase of rework.

**(2) What the AX22 realised-k test counts**
- **5.2-A: prefer.** Now 1, later 1.
  - s still steers the fallback through AX16 entries that no longer set the level. That coupling is invisible to the user, but it already exists.
  - It keeps the AX22 jump-point set identical, so Phase 10's continuity scenarios stay valid.
- **5.2-B and 5.2-C:** not rated (out of bounds).

**(3) `bandsAxisShares` and what Phase 08 receives.** From the code, no user-facing control or display reads `bandsAxisShares`.
- **5.3-D: prefer.** 0 / 0. It is labelled for what it is.
- **5.3-A: can live with.** 0 / 1. It describes a model that no longer sets the level. If a later "diffuseness" display reads it, the picture lies.
- **5.3-B: can live with.** 0 / 1. It widens D-T1's output for no user task.
- **5.3-C: can live with.** 2 / 2.
  - It gives an existing control (per-face α) a new audible effect, a directional binaural tail, that we cannot name, test or justify yet (RQ6 open).
  - It is the demo-feature pattern of W4 and widens scope (Strategy G).

**(4) `open_field` and outdoor presets**

My estimate of the `open_field` tail, from the code (`matchTail` refers each window entry to t_mix,e by exp(−rate·Δt)):
- Floor-scattered energy can arrive only while a floor-to-listener path exists. The farthest is the floor corner: 81.4 + 64.1 = 145.5 m, about 0.42 s. After that, diffuse energy is exactly zero, because the other five faces have α = 1.
- Referred to 1.404 s at the nominal 1 kHz rate (60 dB / 0.636 s ≈ 94 dB/s), the window's entries lose about 92–127 dB. The tail would sit roughly 100 dB below the ledger OF level [Inf; C1 must compute it].
- So in `open_field`, 5.4-A and 5.4-B should sound identical. Seat 1 judges.

- **5.4-A: prefer, conditionally.** Now 1, later 2. It becomes 3 if C1 shows an audible tail: a field that blooms 1.4 s after the music is a veto-grade failure of trust.
  - Now: no new rule. Floor s and α, and source or listener drags, move the inaudible tail continuously.
  - Later: in semi-open outdoor presets (FR-3D-3 festivals with a stage shell, mountains with a cliff), diffuse energy can reach t_mix,e. A noise tail at Eyring's nominal rate would then continue after the real energy has ended. The proposed upper-bound check covers `open_field` only.
- **5.4-B: can live with.** Now 1, later 2.
  - An exact-zero criterion (no propagated diffuse energy in the last part of the window) is honest and free of steps.
  - Any threshold version is an automatic helper that fires on unrelated edits (W4, Natural Volume). Dragging the listener, the floor's s, or a reflecting wall across the threshold flips the tail, and Phase 10 gains a new jump point to gate (FR-SIM-6).

3. **Evidence**
- AX16 vs tracer table: phase-05b2 §0.1; report-phase05b §5.
- ≤ 0.43 dB uniform-α residual: report-phase05 §6a.
- 1 dB G jnd: Vorländer Table 6.1, extended beyond 500–1000 Hz.
- Eyring not valid outdoors: Vorländer §4.4.1, cited in phase-04.md L62–70.
- `matchTail` referral: from the code, NoiseTail.cpp L230.
- Distances and referral losses: my arithmetic on `open_field.json`.
- Incidents: W2 (couplings), W4 (helper firing on unrelated edits), §4 cues.
- T60_b is exposed "for UI display" (phase-04.md L71).

4. **Conditions of acceptance**
- **5.1-C to 1:** show that |ΔL_b| (AX16 vs hybrid) at 63–250 Hz and 4–8 kHz stays within the accepted uniform-α residual (≤ 0.43 dB) on the Phase 04 rooms, the BRAS pairs and layouts 4–6, and Seat 1 hears no seam. Otherwise, commit to switching all 8 bands before presets are built.
- **5.3-C to 1:** adopt only after RQ6 shows the effect is audible with a generic HRTF and Seat 8 names a producer task. It would be its own AX, not now.
- **5.4-A later to 1:** the late-energy upper bound (an independent single-scatter ground estimate) becomes a check on every outdoor preset when presets are built.
- **5.4-B later to 1:** the criterion is exact-zero with no threshold, and Phase 10 gets a scenario that drags across it.

5. **Hand-offs**
- Seat 1: audibility of the C1 tail, of 5.1-C's seam, and of patch-boundary steps.
- Seat 2: E_target continuity under position and room-size automation (patch-count changes); out-of-band ΔL.
- Seat 9: semi-open outdoor presets.
- Seat 4: 5.3-C.
- Seat 7: keeping two energy models alive under 5.2-A.
- UI phase: do not display the Eyring T60 (0.636 s) as the reverb time of an open field.
- Researcher: RQ6.

6. **Premortem.** If 5.1-C is chosen, a producer automates the club floor's scattering, hears the tail's mids move against its lows and highs, and calls the scattering knob "an EQ". Maisara notices first at preset listening, or a beta forum thread does.

---

SEAT 6 POSITION: D-T4 (B6-T4)

1. **Reading.** How long the user waits between an edit and hearing it. Preset loads, room-size drags and material edits are all full rebuilds, and they are the edits of the first minute. Cues: positions that recompute heavily; Strategy D (drop-and-settle, S3).

   What we already know, before any diffuse cost:
   - **Full rebuild at the largest room:** 603–802 ms at 48 kHz and 1509–1884 ms at 96 kHz (§0 row 07).
   - **Update interval:** under AQ4 it is max(20 ms, 30 ms, rebuild time).
   - **Room-size sweep:** Phase 10's "sweep the room size over 4 bars: smooth" (phase-10 L137) is already a staircase of about 4 crossfaded IRs over 8 s at 120 bpm at 96 kHz in the largest room.
   - **No corpus interval for these edits:** Vorländer Table 15.1 (re-read) lists translational movement only (700 ms for moves > 0.25 m; 3 s for moves > 1 m). It has no interval for room-geometry or material edits.
   - **Offline bounce:** synchronous rebuilds per block (Phase 10 scope 1) at 48 kHz / 512 mean about 94 rebuilds per second of audio. At 0.6–0.8 s each, that is about 56–75 s of bounce per second of sweep (arithmetic).
   - **Exemplar anchor:** Audio Ease redesigned Altiverb because an IR switch took an unpredictable 50–200 ms `{SRi; ASFX16; pre}`.

2. **Ranking and ratings** (now / later)

**(a) Memory ceiling.** None of the three rules out every candidate class at 100 m.
- The dense kernel is out under all three.
- A per-patch time history is 9 600 patches × about 2 100 bins × 4 B ≈ 81 MB per band, ≈ 645 MB for 8 bands. It fits 1 GB and 4 GB, and 128 MB only band by band [Inf; Seat 2 owns this].

Options:
- **4a-2: prefer.** 1 / 1.
- **4a-1: can live with.** 1 / 2. It is the most likely of the three to force D-T3, which means either a narrower room-size range (outdoor presets lose their size) or a formulation switch at a size threshold, i.e. a new seam in the room-size control.
- **4a-3: can live with.** 1 / 2. It permits formulations whose fill time at 100 m lands in preset load and room edits [Hyp].

**(b) Time reading**
- **4b-1: prefer.** 0 / 1. It measures the drag the user actually runs, provided the credited parts are kept by shipped code.
- **4b-2: can live with.** 0 / 1. It may overstate W1 and trigger the 3 s Table 15.1 remedy, so the tail level would lag a source move when a cache would have avoided it.

**(c) What blocks and what is recorded**
- **My added option, 4c-1E: prefer.** 1 / 1. It is 4c-1 plus three things:
  - record full-rebuild times at 48 and 96 kHz for the six Phase 04 rooms as well as the AQ10 room, CR4 and 100 m;
  - when a full rebuild exceeds a usability limit taken from RQ5, it goes to Maisara as information, not as a block (AQ10 stays unchanged);
  - hand the UI and Phase 10 a requirement: room-size and material controls show a visible "settling" state while a long rebuild is pending, and room-size automation at large rooms is documented as stepwise.
- **4c-2: can live with.** 1 / 2. It protects the delay between an edit and hearing it, but blocking on time can force D-T3, and it amends an AQ10 rule Maisara accepted.
- **4c-1: can live with.** 2 / 2.
  - Now: nothing bounds or escalates the delay on the first-minute edits.
  - Later: if D-T1 lands at full rebuilds of several seconds, Phase 10's smooth-sweep item fails at large rooms, and drop-and-settle has to be retrofitted into the UI.
- **4c-3: can live with.** 2 / 2. If over-ceiling memory never blocks, a session with several instances can fail at insert or preset load, the worst first-minute failure [Hyp; Seats 5 and 7 measure this].

3. **Evidence**
- Rebuild times: §0 row 07; AQ10.
- Update intervals: Vorländer Table 15.1, corpus re-read.
- Bounce behaviour: phase-10 scope 1, scope 6 and L137.
- Kernel and history sizes: phase-05b2 §0.3.
- Altiverb anchor: W1 (ASFX16).
- My estimates of response-time tolerance: [Hyp] until RQ5 reports.

4. **Conditions of acceptance**
- **4a-1 to 1:** a D-T3 caused only by the ceiling goes to Maisara with the 4a-2 numbers before any range is narrowed.
- **4a-3 to 1:** paired with the recording and escalation of 4c-1E.
- **4c-1 to 1:** add 4c-1E's three items.
- **4c-2 to 1:** the limit is set on typical preset rooms, and the 100 m room is escalated rather than blocked.
- **4c-3 to 1:** the reporting threshold becomes a Phase 13 gate before beta, signed off by Maisara.
- **4b (either option):** also record W1 on the first position edit after a room or material edit (cache miss).

5. **Hand-offs**
- Seat 8 and Seat 5: bounce time of room-size sweeps.
- Seat 2: memory fit per class.
- Seat 1: whether a slower room update is heard as lag.
- Me, later: keep the default scene and the first-screen presets in typical-size rooms, so time-to-first-plausible-scene does not depend on the 100 m case.
- Researcher: RQ5, with its task conditions, and whether those limits hold when the result is heard rather than seen; plus any published delay between a room edit and hearing it in room-simulation plugins (Spat Revolution, dearVR, Indoor).

6. **Premortem.** If 4c-1 is chosen and D-T1 lands with a 100 m full rebuild of several seconds, the room-size sweep becomes a staircase. Maisara notices first at Phase 10's "sweep the room size over 4 bars: smooth", or a beta user who drags a festival preset's size does.
