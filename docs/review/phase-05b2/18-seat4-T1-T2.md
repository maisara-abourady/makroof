# Seat 4 (chain keeper) — positions on D-T1 and D-T2

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 4 POSITION — D-T1 (1.1–1.6) and D-T2, phase 05b session 2

Corpus present (rev c1b171fe). My ratings rest on D-T5.3 (Phase 08 gets E_b and t_mix,e only, through `TailMatch`, with no tail directions), D-T4a (v) and D-T4b as they now stand. If D-T5.3 changed, every parity cell below would be asked again.

**Reading.** The question is how the diffuse E_b is computed, and what that does to my chain. My B4 cues:
- **Per-mode rebuild headroom.** AQ10 measures W1/W2 "every output mode from Phase 08". Phase 08 item 8 checks the head-rotation row (35 ms).
- **Level parity across modes and ears.** Phase 08 AC: binaural vs omni per-band energy within ±1 dB.
- **Room-cue loss near walls.** A tail that reads low gives a wrong direct-to-reverberant ratio (DRR), which pushes the image towards the head.

**Shared arithmetic** (numba prototype, one thread; C++ cost is [Hyp]):
- Today's W1 is 20.6 ms (phase-08 item 8, Linux).
- T1-F adds, for 2 emitters: +4.3 ms at SE 0.083 dB, +27.7 ms at SE 0.033 dB, and ≈ +141 ms at SE 0.0145 dB (builder §3; addendum's L2-F2 scaling).
- So W1 per mode ≈ 25 / 48 / 162 ms before Phase 08's own HRIR early-part cost, which is unmeasured.
- An isolated update (rebuild + 2P at P = 512) then takes ≈ 46 / 69 / 183 ms.
- Vorländer Table 15.1 gives head rotation and new HRTF 35 ms, but the scattering part 3 s (moves > 1 m). The diffuse E_b of a point-listener gather does not depend on head yaw (builder §2: omni next-event gather). So D-T4a (v)'s split update holds E_b exactly under rotation in every option, and that keeps my rotate-before-decode item intact everywhere.

### D-T1.1
| option | rank | now | later | reason |
|---|---|---|---|---|
| T1-F | prefer | 1 | 1 (2 under L2-F2) | Leaves ≈ 25 ms of the 50 ms target for the binaural early part; memory < 2 MB |
| T1-B | can live with | 2 | 2 | ≈ 9 s per rebuild in the AQ10 room at 2 ns [Hyp]; minutes to hours at 100 m. Every per-mode W1 record becomes a diffuse-solve record; both 700 ms rows break in binaural |
| T1-A | can live with | 2 | 2 | 5.4 + 0.36 s, plus 9.9 s with no cache credit (D-T4b) per rebuild. Forces D-T3, a contract bump that Phase 08 goldens must not freeze ahead of |

None breaks what I never trade: HRTF provenance, compensation, the rotation stage, the listening test.

**Conditions:**
- **T1-B to 1/1** if the measured C++ W1 diffuse share is ≤ 25 ms (orchestrator C8).
- **T1-A to 1/2** only if Phase 08 freezes no golden before D-T3's contract version is settled.

### D-T1.2 (under T1-F)
- **S-1: prefer, 0/0.** E_b cannot differ between modes or ears, because there is no seed dependence.
- **S-2: can live with, 1/1.** The hazard is in the code: `tailSeedForOutput()` (NoiseTail.cpp L53–55) XORs the seed per output index. If the Monte Carlo key were taken from it, the two ears would get different E_b: a random tail ILD of about √2·SE (≈ 0.12 dB rms at 0.083 dB), and a level change when switching modes.
- **Condition (S-2 to 0/0):** key on the base tailSeed and the emitter index only, never the per-output seed. Add a test that E_b is bit-identical between `--mode omni` and `--mode binaural` and between the two ears.

### D-T1.3
- **N-3: prefer, 0/1.** Avoids the stopping bias towards a low tail (dossier F12).
- **N-2: can live with, 0/1.** Its small low bias leans to a high DRR.
- **N-1: can live with, 1/2.** A tail that silently reads 1–4 dB low near walls (C4: −1.06 dB at the W1 corner, −3.9 dB at the layout 4 edge, at 32 000 paths) is a dry render. In headphone listening that loses externalisation (Begault, corpus L1108: reverberation consistently enhances externalisation).
- **Condition (N-1 to 1/1):** a failed diagnostic (R, VOV or slope) is escalated, not only reported.
- **All three:** N is computed once per scene and is independent of the output mode.

### D-T1.4
- **Tol-2: prefer, 0/0.**
- **Tol-3: can live with, 0/1.** The binaural W1 headroom falls to ≈ 2 ms.
- **Tol-1: can live with, 1/1.** An absolute DRR slack of 1 dB stacks on the ±1 dB mode-parity budget.
- **Interaction with D-T2:** under L2-F2 the Tol choice is moot. The cost is in D-T2's cell.

### D-T1.5
- **CS-2: prefer, 0/0.** The Phase 08 parity AC runs on "all valid fixtures", and its goldens use Phase 04 rooms.
- **CS-3: 0/0 for me.** Its CI time is Seat 5's.
- **CS-1: can live with, 0/1.** Binaural goldens would be built on E_b whose agreement was never checked on those fixtures.
- **CS-NW: prefer it added.** Without it, later 1 rather than 0: the near-wall cases are where E_b errors reach dB.

### D-T1.6
- **NW-3: prefer, 0/1.** Moves the level +0.03 to +0.09 dB, cuts variance 4–7×, and loses no cue my chain renders: the binaural tail is isotropic by D-T5.3, and the half-space limit is already recorded for Phase 08.
- **NW-2: can live with, 0/1.** A 1–3 % bias, with little variance gain at edges and corners.
- **NW-1: can live with, 1/2.** Cap hits ship tails that read low (F11). Near-wall builds take seconds per emitter, in every mode.
- **Condition (NW-1 to 1/1):** the N-3 diagnostics escalate, and the listening pack carries one near-wall binaural render.
- **All three:** layout 4 stays at ≈ 40 s per emitter.

### D-T2
- **L2-F2: can live with, 1/2.** About 160 ms W1 per mode and ≈ 9 s per emitter at the W1 wall (7.1 M paths). It makes the split update mandatory instead of optional.
- **L2-F1: can live with, 1/1.** A certification that is a coin toss is not a measurement.
- **L2-P: 1/1, n/a under T1-F.** Not certified near walls.
- **Condition (L2-F2 to 1/1):**
  - The diffuse solve runs once per scene and is shared across modes.
  - The Phase 10 split-update AX (hold E_b, update the HRTF and specular part) is scheduled before Phase 08 item 8 closes.
  - Per-mode records show the diffuse share (D-T4b).
- **Effect on the rest:** under L2-F2, T1-F's later rating rises from 1 to 2 unless this condition is met.

### §8 rule (Phase 08 first)
Unchanged under T1-F with S-1 or S-2 (as conditioned): (i)–(iv) hold. Under T1-A, add (v): no binaural golden is frozen before D-T3 is settled.

**Evidence:**
- [Corpus] Vorländer Table 15.1 (corpus L3961–3966); Begault, reverberation and externalisation (L1108).
- [From the code] NoiseTail.cpp L53–55.
- [Builder/C4] the cost and bias numbers above.
- [Hyp] the C++ costs; whether a 0.1 dB tail ILD is audible.

**Hand-offs:**
- **Seat 1:** whether 1–4 dB of DRR error near walls, and a 0.03–0.09 dB shift, are audible.
- **Seats 9 and 2:** the physics of the 0.5 m clamp.
- **Seat 5:** C++ timing and the cap-hit gate.
- **Seat 6:** whether the user sees a cap hit.

**Checks for the orchestrator:**
1. N-3's final path range starts at a fixed index, independent of N, so it stays continuous under automation.
2. The C++ T1-F W1 time is measured before Phase 08 sets its per-mode W1 record.

**Premortem:** if S-2 is keyed through the per-output seed, or N-1 ships near-wall cap hits, the binaural mode's tail reads quieter or lopsided while the omni preview does not. Maisara notices first, in the Phase 08 checklist, as an "inside the head" answer on a near-wall scene.
