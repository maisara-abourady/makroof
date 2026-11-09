# Seat 2 (engine architect) — positions on D-T5 and D-T4

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

Persona assumption that no longer holds: my §0 put the room classes at booth to mid-size hall. AX6 (1.5–100 m per side) and FR-3D-3 (which includes outdoor scenes) put the 100 m room and `open_field` in scope, so I rate them below. Corpus is present (c1b171f).

---

# SEAT 2 POSITION — D-T5

**1. Reading.** Once the AX16 scattered entries stop setting the tail level, this decides four things: what E_target is built from, what k_real counts, what the axis shares describe, and what `open_field` gets. Cues from my §4 that it triggers:
- cue 5: tone colour versus decay level;
- cue 3: geometry class (concentrated absorption, open faces);
- S6 / P3: the non-circular validation configuration;
- W1: scattering is a model, not a knob.

**2. Ranking.**
- **(1)** 5.1-A *prefer*. 5.1-C *cannot live with*.
- **(2)** 5.2-A *prefer*. 5.2-B and 5.2-C: not rated (out of bounds).
- **(3)** 5.3-D *prefer*. 5.3-A *can live with*. 5.3-B *can live with* under conditions. 5.3-C *can live with* only under conditions.
- **(4)** 5.4-A *prefer*. 5.4-B *can live with* only if its criterion is exact zero.

**3 and 4. Tension now and later.**

| opt | now | why (now) | later | debt and the evidence that could overturn it |
|---|---|---|---|---|
| 5.1-A | 1 | Same equations in all 8 bands (E1). The tracer agreement (≤ 0.08 dB) and the ℓ certification (AX36 (a)) exist only for 500 Hz–2 kHz, with band-flat α and s (E2, E3). | 1 | If an outer band fails, the fix is a finer ℓ there (a D-T2 rung, a parameter change), never AX16. Evidence: the ℓ ladder and the D-T1 agreement test extended to 63–250 Hz and 4–8 kHz. |
| 5.1-C | **3** | AX16's bias comes from geometry and does not depend on band: s is broadband (AX17), and layout 4 has α = 1 in every band. The tail would be corrected at 500 Hz–2 kHz but stay +3.87 dB (layout 4, s = 1) in the five outer bands. That builds a ≈ 3.9 dB tone-colour step at the 250/500 Hz and 2/4 kHz boundaries, in exactly the rooms the switch exists for. Tone colour carries the largest perceptual weight (E5). | 2 | Two energy models stay in `src/sim`. A second switch later means a second golden churn and agreement tests split by band. |
| 5.2-A | 1 | The fallback protects the specular lattice structure (sparse arrivals, flutter, E6), and the switch does not change that structure. Keeping 5.2-A keeps t_mix,e at the configuration the window check validated. Residual, already present today: AX16 entries sit at lattice times, so in parallel-wall rooms with high s, k_real treats scattered energy as periodic and the fallback may over-trigger (E10). | 1 | The AX16 list survives only for this decision; it is as long as the image list and cheap. Candidate (d) stays linear. Only an AX22 change could fix the over-trigger, and nothing forces one now. Evidence that could: Phase 13's i₀ re-derivation, or a listening result on a high-s flutter scene. |
| 5.3-D | 0 | D-T1 owes one scalar per emitter and band; the label is honest. | 0 | — |
| 5.3-A | 1 | The diagnostic describes a retired model. AX16 puts scattered energy at specular directions, which is physically wrong (Eq. 4.29 gathers along dS′→P). | 1 | Little extra cost, since 5.2-A keeps the list anyway. |
| 5.3-B | 2 | Needs 4 window functionals per emitter and band instead of 1. These are free at a forward gather and in (f), but cost ≈ 4 backward solves per emitter in (d) and ≈ 4× in (e), so the requirement tilts D-T1. No consumer reads them. | 2 | `ref_hybrid` has no direction tallies, so a new reference and test would be needed for a quantity no blind test reads (my §17: "a feature no blind test would change"). |
| 5.3-C | 2 | As 5.3-B, but the window's directions (t ≤ t_mix,e) are not the late field's. With concentrated absorption each direction decays at its own rate (E6b, E7), so the distribution drifts after t_mix,e. Phase 08 would receive a quantity from the wrong time segment, never validated, with no audibility evidence (RQ6). | 2 | Phase 08's scope changes and it gains a dependency on 05b/05h. |
| 5.4-A | 1 | The physics is in E11. Gain: this is the only scene in the set where injection and gather have an independent, exact single-generation reference (`ground_scatter.py`). The second check (energy later than 50 ms) is weak: it passes by roughly 60 dB or more [Inferred]. | 1 | If C1 contradicts my bound, a rule like 5.4-B (a parameter-level change). |
| 5.4-B | 2 (threshold) / 1 (exact zero) | A threshold is a number the validated model does not contain. It would exist to protect a test outcome, and it puts a step under automation. | 2 / 1 | Every scene near the threshold would carry a test. |

**E11, the physics of `open_field` (4) [Inferred, my arithmetic from the fixture].**
- **One generation only.** The other five faces have α = 1. The direct field irradiates the whole floor (`ref_hybrid.injection`), each floor patch radiates s(1−α) as Lambert, and the listener gathers it directly.
- **Time span.** t_dir = 60.2 ms, so the window starts at 62.7 ms. The longest source–floor–listener path is 146.2 m, so floor-scatter energy ends at ≈ 426 ms and is exactly zero afterwards. Before that it falls off as a power law, not an exponential.
- **Eyring does not describe this.** Its derivation assumes homogeneous absorption and a diffuse field (Vorländer §4.4.1), and neither holds here. The tail extrapolates, at the nominal Eyring rate, a field that has already ended. That is harmless only because of its size.
- **Upper bound on the tail level.** Three factors bound it:
  - the window normalisation, 10 ms / (0.5 × 1.342 s) = −18.3 dB;
  - the largest referral factor, e^(−rate × 0.978 s): −47.3 dB at 63 Hz (T60 1.242 s) and −92.3 dB at 1 kHz (T60 0.636 s);
  - the late energy from ledger OF: −23.4 dB at 63 Hz and −28.2 dB at 1 kHz (`test_ground_scatter.py` L13).

  So E_b ≤ ≈ −89 dB at 63 Hz and ≤ ≈ −139 dB at 1 kHz per 10 ms at t_mix,e, relative to ledger OF's reference. C1 must confirm this.
- **Float range.** At 8 kHz the referral alone is ≈ −260 dB, close to the float32 denormal range.

**5. Evidence.**
- **E1** [Code] `ref_hybrid.target_hybrid` (L528–533) is the specular entries plus `window_target(diffuse)` per band, on the same plan.
- **E2** [Observed] report-phase05b §5: the 500 Hz, 1 kHz and 2 kHz values are identical within 0.01 dB, so each case is effectively one check.
- **E3** [Plan] AX36 (a), with its per-quantity rule.
- **E4** [Plan] AX17.
- **E5** [Observed, my register, outside the corpus] Brinkmann et al. 2019: tone colour has weight β = 0.29.
- **E6** [Corpus] Kuttruff §4.2: periodic components cause flutter echoes between parallel walls, and hearing is very sensitive to periodic repetition.
- **E6b** [Corpus] Kuttruff §4.2: in a smooth rectangular room each ray decays at its own rate, giving a bent decay.
- **E7** [Corpus] Kuttruff §5.7: with one face fully absorbing, the decay constant deviates from Eyring (−1.57 against −1.38 dB per mean free path).
- **E9** [Code] `NoiseTail.cpp`: k_real = S²/Q over window-weighted, referred entries (L225–241). The axis shares use raw entry energy, not the window weight times the referral (L235–244), so 5.3-B's "energy-weighted in the window" is a new definition.
- **E10** [Inferred] Splitting an image into a specular entry px and a scattered entry (1−p)x lowers Q by p² + (1−p)², which inflates k by up to 2×.
- **E12** [Inferred] 5.2-C would make k depend on the bin width Δt. In `open_field` it would lift k_real far above 19 and remove the fallback.

**For the researcher:** RQ6. Optionally, measured outdoor impulse responses over ground, to check the order of the late ground-scatter energy.

**6. Conditions of acceptance.**
- **5.1-C → replace with 5.1-A plus an outer-band check (rated 1).** The check: the ℓ ladder for E_target at 63–250 Hz and 4–8 kHz in the 15 (A) cases and in CR2/CR3; and a tracer window check at 125 Hz and 8 kHz in at least 2 cases with α that varies by band. If a band fails, take a finer ℓ for it or badge it; never return to AX16.
- **5.3-B → 1** if it is optional: reported only where D-T1's formulation yields it without an extra solve, and not gated.
- **5.3-C → 1** only if all of these hold: RQ6 shows audibility; the direction quantity is time-resolved for the late field, not taken from the window; it is validated against tracer direction tallies; and it arrives as a Phase 08 AX after 05b.
- **5.4-B → 1** with an exact-zero criterion on the diffuse energy at t_mix,e (the same logic as AX20's exact-zero pruning). An α = 1 face moving to 0.99 then steps the tail by its entire level, which E11 bounds at ≈ −89 dB or lower.

**7. Hand-offs.**
- Seat 1: whether the 5.1-C seam is audible, and whether a −89 dB tail at 1.4 s is.
- Seat 3: IR length if `open_field` gains a tail.
- Seat 4: what Phase 08 receives (from the code it reads only E_b and t_mix,e; the plan text saying the shares feed Phase 08 is wrong).
- Seat 5: compute the referral in double, or flush, so it cannot produce denormals.
- Seats 6 and 9: outdoor presets.

**8. Premortem.** If 5.1-C is chosen and fails, the layout-4 listening-pack scene carries a coloured tail with a ≈ 3.9 dB step at 250/500 Hz and 2/4 kHz, and Maisara hears it first.

---

# SEAT 2 POSITION — D-T4

**1. Reading.** A per-instance memory ceiling at 100 m, the reading of W1/W2, and which misses block. Cues: §4 cue 7 (how cost grows) and P5 (precompute what does not move).

**2. Ranking.**
- **(a)** 4a-2 *prefer*. 4a-3 *can live with*. 4a-1 *can live with* under conditions.
- **(b)** 4b-1 *prefer*, with conditions. 4b-2 *can live with*.
- **(c)** 4c-2 *prefer*, if a sourced limit exists. 4c-1 *can live with*. 4c-3 *can live with*.

**Memory at 100 m per candidate class.** Inputs: N = 9 600 patches at ℓ = 2.5 m; T ≈ 1 035 time bins without the fallback and ≈ 2 100 with it; float32. All figures [Hyp] until D-T1 measures them.

| class | memory at 100 m | fits 128 MB | fits 1 GB | fits 4 GB |
|---|---|---|---|---|
| (a) dense kernel | 381 / 774 GB per band | no | no | no |
| (b) matrix-free, (d) adjoint | per-patch history N·T·4 B = 40 / 81 MB per band per emitter; 161 MB for two emitters; 1.29 GB for all bands and both emitters | only band by band and emitter by emitter, with no resident cache | yes | yes |
| (c) shoebox structure | ~0.3–1.3 GB per band [weak] | no | plausibly | yes |
| (e) transform | dense N×N complex64 is 737 MB per frequency; iterative O(N) | iterative only | yes | yes |
| (f) Monte Carlo | histogram ≈ 0.3 MB plus geometry | yes | yes | yes |

**What this means for the ceilings.**
- No ceiling makes (a) viable at 100 m, and no ceiling rules out every class, so no ceiling forces D-T3 through memory alone.
- 4a-1 effectively pre-decides D-T1 for (f), or for sequential (b)/(d).
- The binding constraint at 100 m is time. Within the fallback horizon there are ≈ 1 560 specular paths per patch pair (Kuttruff Eq. 4.6 integrated, the same arithmetic as AX22's t_cap). That makes ≈ 1.4·10¹¹ kernel terms per generation for (b)/(d), or ≈ 140 s per generation at an assumed 10⁹ terms/s [Hyp].
- The diffuse computation uses 1 ms energy bins, so its memory does not depend on the sample rate (phase-05b scope 0).

**3 and 4. Tension now and later.**

| opt | now | why | later | debt |
|---|---|---|---|---|
| 4a-1 | 2 | Pre-decides D-T1 and rules out any resident cache at 100 m. | 2 | If (f) cannot reach AX11's standard error in time, D-T3 is forced by the ceiling, not by the physics. |
| 4a-2 | 1 | Excludes only what N²T excludes anyway. | 1 | — |
| 4a-3 | 0 | — | 1 | Phase 13 may have to cut it back, which could mean rewriting the formulation. |
| 4b-1 | 1 with conditions / 2 without | Sound only if the cached part is position-independent: the patch-to-patch transport is (geometry, α, s); injection, gather, the window and t_mix,e are not. | 1 / 2 | Without the conditions, W1/W2 and therefore the AQ4 update interval are understated. |
| 4b-2 | 1 | Charges a precompute class for a cache it could build now. | 1 | — |
| 4c-1 | 1 | — | 2 | A formulation within the memory ceiling that rebuilds in minutes at 100 m [Hyp] ships recorded-only; Phase 13 finds it, and fixing it is a phase of rework. |
| 4c-2 | 1 | Needs a sourced limit (RQ4, RQ5) and goes to Maisara as a challenge. | 1 | — |
| 4c-3 | 1 | — | 2 | No stated edge: D-T3 is never triggered. |

**5. Evidence.**
- [Plan] phase-05b2 §0.3 and AX36 (c): the kernel sizes. My arithmetic reproduces the 3 TB figure (381 GB × 8 bands).
- [Plan] Phase 10 scope 2 caches only the unit decay.
- [Plan] W2's horizon is t_cap ≈ 0.38 s, against W1's t_mix,e ≈ 0.12 s (AX22): about 3× longer.
- [Corpus] Kuttruff Eq. 4.6 (the path count above).

**For the researcher:**
- the memory used by shipped acoustics engines in large scenes (Steam Audio baked reverb, Project Acoustics, Wwise Reflect, RAVEN, Odeon radiosity), against patch count;
- published memory scaling of acoustic radiance transfer;
- the variance of next-event estimators in energy-based hybrids.

**6. Conditions of acceptance.**
- **4a-1 → 1:** a ceiling of at least ≈ 2·N·T·4 B (≈ 161 MB, my arithmetic) plus headroom.
- **4b-1 → 1:** all four of these:
  1. the cache is implemented and tested in this session, not borrowed from Phase 10;
  2. its horizon covers every admissible position's t_mix,e, including the fallback, or the invalidation is counted inside W1/W2;
  3. cached and uncached results are bit-identical (AX5);
  4. its resident memory counts inside (a).
- **4c-1 and 4c-3 → 1:** record the full-rebuild time at 100 m against a flagged threshold that goes to Maisara.

**7. Hand-offs.**
- Seats 5 and 7: RAM on customer machines, instances per session.
- Seat 5: concurrent builder threads.
- Seats 6 and 1: delay from an edit to hearing it.
- Seat 4: headroom Phase 08 needs inside the same budget.

**8. Premortem.** If 4a-2 and 4c-1 are chosen and it goes wrong, a formulation that fits in 1 GB takes minutes per full rebuild at 100 m. The Phase 13 benchmark, or a beta user resizing a large hall, finds it first.
