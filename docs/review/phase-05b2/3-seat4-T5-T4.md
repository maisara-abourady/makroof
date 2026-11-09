# Seat 4 (chain keeper) — positions on D-T5 and D-T4

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 4 POSITION — D-T5 (tail-level switch: interaction with the matching)

Corpus present (14 files, c1b171f). One persona assumption no longer holds: head tracking is out of scope (PRD; phase-08 "Out of scope"). That means my 60 ms tracker budget does not apply. The time limit that matters for delivery in v1 is phase-08 item 8: the head-rotation row of Vorländer Table 15.1 (35 ms, "new HRTF"), which bites when the AX3 yaw follows the emitter centroid.

**1. Reading.** The question is which E_b and t_mix,e reach the binaural chain, and whether the late tail needs directions. It triggers four of my cues:
- level and tone parity (the ±1 dB check between omni and binaural);
- spectral mismatch (the band split in 5.1-C);
- over-resolved periphery (directions in the diffuse segment);
- model violated (a direction distribution measured in the window, applied to the whole tail).

**2–3–4. Ranking and tension (now / later)**

(1) What E_target is built from
- **5.1-A: prefer. Now 0, later 1.** Omni and binaural read the same E_b, so the parity check does not move. Later 1: the model was validated only at 500 Hz–2 kHz (decider K2).
- **5.1-C: can live with. Now 2, later 2.**
  - In layout 4 at s = 1 it would put a step of up to 3.87 dB in the late-field spectrum between 2 and 4 kHz (report-phase05b §5). Whether α is equal across that band edge is [Hyp].
  - 4–8 kHz carries the headphone spectral cues. Phase 08 holds the DF-EQ to 0.1 dB and its pin-time check to 1 dB (phase-08 scope 3). This error is about 39 times the 0.1 dB.
  - No relative gate would see it: both modes share E_b, so parity passes.
  - Later: binaural goldens frozen on a split tail would have to be redone when the other five bands switch.

(2) What the AX22 realised-k test counts
- **5.2-A: prefer. Now 0, later 1.** t_mix,e stays where it is. So do the early/late boundary in binaural and the per-image HRIR workload, which in W2 is up to N_cap = 1 560 images per emitter.
  - Later 1 is existing debt, not new. At the AX22 jump point the segment swaps HRIR-rendered images for diffuse-coherence noise, which changes interaural coherence as well as band energy. Phase 10's gate measures band energy only (AX22).
- **5.2-B, 5.2-C:** not rated (out of bounds).

(3) `bandsAxisShares` and what Phase 08 receives
- **5.3-D: prefer. Now 0, later 0.** Phase 08 receives exactly what item 5 reads (E_b and t_mix,e), and the diagnostic carries an honest label.
- **5.3-A: can live with. Now 0, later 1.** The diagnostic would describe a model that no longer sets the level. If kept, label it "AX16 entries, not the level model".
- **5.3-B: can live with. Now 1, later 1.** No effect on Phase 08. The cost falls on D-T1 (Seat 2 and Seat 5). It does keep the data needed for a later study of anisotropy.
- **5.3-C: cannot live with, as scoped. Now 2, later 3.**
  - It adopts a directional delivery feature on a formula alone, with no listening evidence (RQ6 is uninformed). That breaks my criterion 2.
  - The distribution describes the window [t_dir,e + 2.5 ms, t_mix,e], not the tail after it. Its validity beyond t_mix,e is [Hyp]; Seat 2 owns it.
  - Once shipped, NFR-6 fixes the tail of every saved project. Undoing it would mean a second, versioned tail path, on the AX35 pattern.

**Is the diffuse-coherence tail of phase-08 item 5 enough?** Yes, for v1.
- A binaural diffuse field is fully described for two ears by a 2×2 covariance: the two diffuse-field ear sensitivities and the interaural cross-correlation (corpus: Zotter–Frank, MagLS covariance constraint after Vilkamo).
- After about 140 ms, receiver-specific reverberation can be replaced by a statistical decay (corpus: Vorländer ch. 15, after Meesawat and Hammershøi).
- Against this: the angular distribution of the reverberant sound "had the largest effect" on listener envelopment (LEV) (corpus: Kuttruff §7.7, Bradley and Soulodre). But that was a loudspeaker field, not headphones with a non-individual HRTF. The same study found overall level also strong, and level is what the switch fixes, validated to 0.08 dB.
- From the code (NoiseTail.cpp L236–238): the axis shares are second moments (u_x² and so on). They cannot carry a left/right asymmetry, which is exactly what layouts 5 and 6 have.
- If a directional tail is ever justified, Phase 08 needs only a per-band, direction-weighted 2×2 ear covariance, not a list of directions.

**Effect on the ±1 dB omni-to-binaural parity**
- Under 5.3-A, 5.3-B or 5.3-D there is no effect. The 2×2 mix keeps each ear at the diffuse-field power by construction, and the switch moves both modes by the same amount. [Inferred]
- Under 5.3-C, each ear's power becomes the direction-weighted HRTF power. The order of magnitude is Begault's 1.5–2.5 dB diffuse-minus-free-field figure (Begault ch. 4, as cited in phase-08 scope 3). So the gate either fails in rooms with concentrated absorption or has to be redefined. [Inferred]

**May Phase 08 start before the switch lands?** Yes under 5.3-A, 5.3-B or 5.3-D, on four conditions:
- (i) Phase 08 reads E_b and t_mix,e only through `TailMatch`: one E_b per emitter, shared by every mode, with no per-mode re-matching.
- (ii) Parity is checked binaural against omni within the same build.
- (iii) 05h's scope re-renders the binaural goldens through `update_goldens.py`, re-measures binaural W1/W2 (AQ10: "every output mode from Phase 08"), and re-runs phase-08 item 8, because the diffuse computation enters the position-only rebuild.
- (iv) Phase 08 listening items on tail level and envelopment in concentrated-absorption scenes are marked provisional.

Under 5.3-C, Phase 08 has to wait for 05h.

(4) `open_field`
- **5.4-A: prefer. Now 0, later 1.**
  - My arithmetic: energy arriving around 50 ms, referred to 1.404 s at T60 = 0.636 s, falls by about 60 × 1.354 / 0.636 ≈ 128 dB. With the ledger OF estimate of −23 to −43 dB and the Hann weight near the window's start, E_b lands at roughly −150 dB relative to the direct sound or lower. [Inferred; computation C1 to confirm.] Nothing of that reaches the ear.
  - Later 1: an isotropic diffuse-coherence tail is the wrong model for a ground field confined to a half-space. That is harmless here but may not be in semi-open presets. Phase 08 should record it as a limit.
  - Condition: the parity check uses full-BRIR band energy, not a tail-only ratio between near-zero energies.
- **5.4-B: can live with. Now 1, later 1.** It adds an AX with no listening basis and changes nothing at the ear.

**6. Conditions of acceptance**
- **5.1-C (2/2):** none short of 5.1-A. At minimum, all eight bands are switched before the Phase 08 goldens are frozen. That would bring it to 1.
- **5.3-C (2/3):** take it out of Phase 08 and make it a backlog item, entered only after an RQ6 result and a MUSHRA with a hidden reference (a directional against a diffuse tail, layouts 4 and 5 at s = 1, target listeners). That would bring it to 1.

**7. Hand-offs**
- Seat 1: audibility of the 5.1-C spectral seam, and of late-field anisotropy on headphones.
- Seat 2: how the anisotropy evolves after t_mix,e, and 5.3-B's extra cost to D-T1.
- Seat 3: the AX22 jump point in binaural.
- Seat 7: what 5.3-C would cost the schedule.

**Researcher:**
- RQ6, extended: does a horizontally concentrated late field change binaural interaural coherence per band by more than the coherence just-noticeable difference? I need base rates for that JND.

**8. Premortem.** If 5.3-C goes into Phase 08, the parity check fails in absorbent venues and gets redefined so that it passes. Binaural then sounds tonally different from omni, and Maisara notices it first when switching modes on pink noise in the listening pack.

---

SEAT 4 POSITION — D-T4 (cost budget)

**1. Reading.** This sets the per-instance memory and the time reading for the diffuse computation. It triggers two of my cues: over-resolved periphery (budget spent on the least-resolved segment), and the update delay for a new HRTF (phase-08 item 8).

**Headroom Phase 08/09 need**
- **HRTF memory:** at most 32·10⁶ B embedded, held as one immutable object for the whole process (phase-08 scope 2–3). It is paid once per process, not per instance. That rises to about 35 MB if a float16 file is decoded to float32 (17.7 MB × 2). [Inferred]
- **Per instance:** the tap count stays 2×2 in binaural (from the code: Engine.h L33–36). The builder adds a second noise tail per emitter (item 5), and Phase 10 caches per output (phase-10 scope 2). So the tail-noise share of the +122.6 MB baseline can roughly double. [Hyp: that share has never been measured.] Phase 09 (ORTF) has the same profile.
- **Build time:** binaural adds per-image HRIR work over the AX20 list and the second noise tail. Unmeasured. [Hyp]
- **Requirement on any option:** the diffuse computation is computed once per emitter and rebuild, whatever the output mode. That holds under 5.3-A, 5.3-B and 5.3-D, and not under 5.3-C.
- **Time-critical point:** if Table 15.1's head-rotation row (35 ms, "new HRTF") applies, phase-08 item 8 needs the rebuild to be at most 24.3 ms (13.7 ms with AX31's extra partition) at P = 512 (corpus: Vorländer Table 15.1; AX31). W1 is already 20.6 ms. Any diffuse work inside a position-only rebuild pushes binaural W1 out of that row, and no ceiling fixes this.

**2–4. Ranking and tension (now / later)**

(a) Memory ceiling
- **4a-2: prefer. Now 0, later 1.**
- **4a-1: can live with. Now 1, later 1.** A matrix-free formulation that keeps a bounded history needs about 9 600 × 2 100 × 4 B ≈ 81 MB per band and emitter at 100 m. It fits only if bands and emitters are solved one after another, which lengthens W1 in every output mode. [Inferred; Seat 2 owns.]
- **4a-3: can live with. Now 1, later 2.** It admits formulations whose time grows as N²·T·G. Binaural W1 would then be the first number past 700 ms.

Would a ceiling rule out every candidate class at 100 m? No ceiling forces D-T3 by my arithmetic:
- The dense kernel (3–6 TB) fails all three ceilings.
- Bounded-history matrix-free (≈ 0.65 GB for all bands) fits 1 GB.
- Monte Carlo needs memory of order bins × bands. [Hyp]

(b) Time reading
- **4b-1: prefer. Now 0, later 1.** It measures what ships, provided resident memory counts inside (a).
- **4b-2: can live with. Now 1, later 1.** Conservative, but if the formulation does cache, it measures something that does not ship.

(c) What blocks and what is recorded
- **4c-1: prefer. Now 0, later 1.**
- **4c-2: can live with. Now 1, later 1.** This is not my ground. It amends AQ10, so it goes to Maisara.
- **4c-3: can live with. Now 1, later 2.** With nothing blocking, the cost lands silently in Phase 08's per-mode measurements.

**6. Conditions of acceptance**
- **4a-3 (later 2) and 4c-3 (later 2)** each come down to 1 if two things hold:
  - W1/W2 are recorded per output mode from Phase 08, with the diffuse share reported separately, at 48 and 96 kHz.
  - Phase 08 re-measures them, and re-runs item 8, once the diffuse computation is in.

**7. Hand-offs**
- Seat 2: the memory arithmetic for each candidate class.
- Seat 5: whether the HRTF is held per process or per instance, and concurrent builders.
- Seat 1: which limit item 8 applies (35 ms or 20 ms).

**Researcher:**
- RQ2, extended: per-instance memory of binaural room renderers (dearVR PRO, Anaglyph, IEM BinauralDecoder), and whether they hold HRTF data per process.
- A base rate for BRIR build time.

**8. Premortem.** If 4a-3 or 4c-3 lets a slow formulation through, binaural W1 is the first number past 700 ms and misses item 8's 35 ms row by a wide margin. Seat 5's CI benchmark catches it in Phase 08, not in 05b.

Files read: `/home/user/makroof/docs/review/phase-05b2/1-decider-convene-T5-T4.md`, `/home/user/makroof/docs/phases/phase-05b2.md`, `/home/user/makroof/docs/phases/phase-08.md`, `/home/user/makroof/docs/phases/phase-10.md`, `/home/user/makroof/docs/phases/phase-13.md`, `/home/user/makroof/docs/BUILD_PLAN.md`, `/home/user/makroof/docs/validation/report-phase05b.md`, `/home/user/makroof/src/sim/tail/NoiseTail.cpp`, `/home/user/makroof/src/sim/Engine.cpp`, `/home/user/makroof/src/sim/Engine.h`, `/home/user/makroof/tools/acoustics/ref_hybrid.py`, `/home/user/makroof/docs/corpus/` (Kuttruff §7.7, Vorländer ch. 15, Zotter–Frank, Blauert ch. 3–4).
