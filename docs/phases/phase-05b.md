# Phase 05b — Early scattered energy (B11)

Size: **M** (L if gate (A) or the tracer fights back; split the remainder into a further b-phase) · Depends on: 04, 05 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ2, AQ4, AQ9, AQ10, AX5, AX16, AX18, AX20, AX21, AX22) and §5 B11, `docs/phases/phase-05.md` scope 6, PRD NFR-1, NFR-3, NFR-8, FR-SIM-6

Created by decider report 8, accepted by Maisara, 2026-11-05: B11 is a v1 phase, after 05 and before 08.

## Goal

Remove the AX21 deficit if the evidence supports it. The Phase 04 hybrid IR is specular-only before
t_mix,e. This phase promotes the Phase 05 reference hybrid's early Lambert-scattered energy into
`src/sim`, but only if it passes the B11 promotion rule (A) and (B). Otherwise the phase closes as
"not promoted" with the reason recorded, and Phase 08 builds on the specular-only early part.

## Assumptions in force

- **AX21**: the Phase 04 hybrid IR is specular-only before t_mix,e (known deficit). Maisara decided on
  2026-11-05 that the early part should contain scattered energy.
- **AX16**: AX16's per-path scattered entries set the tail level. Phase 05's ΔL_b and this phase's
  ΔL_b,tr decide whether tail-level matching switches to the hybrid's propagated diffuse energy.
- **AX22**: the realised-k switch and the image-count cap N_cap are unchanged.
- **AQ10**: position-only rebuild workloads W1/W2. Rebuild time is measured and recorded; it does not
  block promotion.
- **AX5**: the tracer and any noise are seeded; offline renders stay bit-identical run to run.
- The early diffuse energy depends on positions, so it is rebuilt on every rebuild and is not part of
  the Phase 10 tail cache.

## Scope

0. **Patch size and time step (DN-1; set before any gate result is seen)** (decider report 11, accepted by Maisara, 2026-11-05; corrections from the interrogator pre-check, report 12). Patches are
   defined by one absolute edge length ℓ in metres: each face is split into ⌈L/ℓ⌉ equal strips per
   edge. ℓ is a constant in `src/sim`, changed only as an intended output change, like N_cap. The time
   step Δt is 1 ms, also frozen. ℓ is the coarsest value at which, in every selected BRAS room and every
   (A) case, halving ℓ changes all of these by < 1 %: a*, the window energy E_target per band from
   500 Hz to 2 kHz, and each bin that (A) gates. Halving stops at ℓ = c·Δt = 0.343 m, because a finer
   patch is not resolved by the 1 ms step; if that floor is reached, the residual is recorded. ℓ is
   absolute, not relative to room size (with a relative split, a 100 m room's patches would smear
   delays by tens of ms). The Table 15.1 option (the scattering part updated every 3 s or 1 m) is not
   adopted; if W1 with the diffuse part goes above 700 ms, it is the first remedy Phase 10 may propose
   as an AX. A coarser ℓ is not a remedy.
1. **Port the reference hybrid into `src/sim`** (generic, NFR-8). At each specular hit, s(1−α) of the
   incident energy goes into the Lambert boundary patch hit, at the hit time (Kuttruff Eq. 4.24). It is
   propagated with the mixed specular/diffuse form: at each later hit, s is re-radiated per Lambert and
   1−s continues specularly (Joyce's reflection matrix, Kuttruff §4.6 Eq. 4.35, with the §5.2 split
   s(1−α) / (1−s)(1−α); Gilbert, §4.6, splits the boundary into specular and non-specular portions).
   The diffuse part is gathered at the listener (Eq. 4.29) and added before t_mix,e, on the scope 0
   patches and time step.
   **Rendering (DN-1, variant (d): equivalent-reflection pulses under the gathered envelope)**
   (decider report 11, accepted by Maisara, 2026-11-05; corrections from the interrogator pre-check, report 12). Per emitter and per 1 ms step k on the emission time axis, the gathered diffuse
   energy E_k,b (all patches, Eq. 4.29, each with its own delay R′/c) is rendered as
   n_k = max(1, ⌈ν(t_k)·Δt⌉) pulses, ν(t) = 4πc³t²/V (Kuttruff Eq. 4.6; Blauert Ch. 3 §3.3), Δt = 1 ms
   (Kuttruff §9.8 class width): equivalent reflections with density n_j matching the reflection
   statistics (Vorländer Eq. 11.51). Below t_floor = √(V/(4πc³Δt)) (≈ 109 ms at 6 000 m³, ≈ 17 ms at
   145 m³) n_k exceeds Eq. 4.6; up to t_mix in 6 000 m³ the count is ≈ 2.6× the diffuse-field count (≈ 139 pulses against ≈ 54 by Kuttruff Eq. 4.6).
   This is a departure from Eq. 4.6, low confidence. Pulse offsets within the step and signs come from
   a counter-based RNG keyed by (tailSeed, emitter, step, pulse), independent of positions and patch
   layout (AX5). Each pulse is a broadband equivalent reflection with per-band amplitude √(E_k,b/n_k),
   rendered through the Phase 03 filterbank path like an image source, so the per-band tap energy per
   step equals E_k,b exactly (the ISM-equivalent tap domain). In the rendered band IR it holds in
   expectation over the random signs: band-filter ringing (AX15), band overlap (AX14) and coherent
   addition of pulses closer than a filter length (Vorländer §1.7) move energy between steps and bands.
   Per step, the per-patch contributions are kept so that Phase 08 can assign directions (Kuttruff
   §4.5; Vorländer Fig. 15.5); how it does so is Phase 08's decision. Diffuse pulses inside the
   ISM→tail crossfade take the ISM window (AX18).
2. **Independent reference** in `tools/acoustics`: a seeded Kuttruff §9.8 partially diffuse ray
   tracer, energy multiplication (§9.8 step 3a; Vorländer Eqs. 11.14–11.18), with its seed independent
   of the rendered side. Receiver radius r_d = 0.5 m, N₀ = ⌈254·V⌉, doubling and cap as in B11.
   Engineering note, not from the corpus: each detection is time-stamped at the ray's closest approach
   to the receiver point.
3. **Gate (A)**, exactly as stated in BUILD_PLAN §5 B11:
   - per-bin envelope check, ±1 dB per 10 ms bin up to t_mix,e, all 8 bands, bins with k ≥ 684, at
     least 3 gated bins per case or the case fails;
   - cases: s = 0.1, 0.25, 0.4 with α = 0.15 uniform, 20×30×10 m, AX4 air absorption on both sides;
     Table 5.2 layouts 4, 5, 6 (10×20×30 m) at s = 0.1, 0.25, 0.4 plus the s = 1 anchor, solver called
     directly.
4. **Window-level check and branches** (BUILD_PLAN §5 B11, decider report 8, item 2d). Per case and per
   band 500 Hz–2 kHz, ΔL_b,tr = 10·log10(E_target(AX16)/E_target(tracer)), and the hybrid's E_target
   against the tracer's within ±1 dB, in the same Hann window, with tracer k ≥ 684 over the window.
   - (i) If the hybrid's window level passes, tail-level matching switches to the hybrid whenever
     |ΔL_b,tr| > 1 dB anywhere, even if the per-bin render gate fails and early rendering is not promoted.
   - (ii) If it fails, nothing switches: AX16 records ΔL_b,tr per case as a known deficit, and the
     diagnosis goes to Maisara.
   - (iii) If Phase 05 accepted X-b (≤ 1 dB) but |ΔL_b,tr| > 1 dB anywhere, the acceptance is reversed and
     (i)/(ii) apply.
   - The switch is valid only with SE(ΔL_b,tr) = 4.34/√k_tr ≤ 1/3 dB (threshold/3, AX11); k ≥ 684 gives ≤ 0.17 dB. Realised k and SE are printed. The tracer seed is fixed, so the decision reproduces on re-run. Near 1 dB either branch leaves the level error within about 1 dB + 3·SE (decider report 11, FR-04; the trigger uses |ΔL_b,tr|, C1, accepted by Maisara, 2026-11-05).
   - Independently of these, if Phase 05's |ΔL_b| exceeded 1 dB anywhere, tail-level matching switches
     to the hybrid's propagated diffuse energy (AX16), under the same validation.
5. **Tracer-bias diagnosis** (BUILD_PLAN §5 B11, decider report 8, item 2e). If the per-bin difference
   converges to a bias above 0.3 dB, diagnose with two tracer self-checks against independent anchors:
   - s = 0 against the ISM image energies in 10 ms bins (the lattice is exact, Kuttruff §4.1);
   - s = 1 against the Table 5.2 iteration T.

   Fix whichever side fails. Then halve the hybrid's time step and patches until the change is < 1 %.
   A remaining bias ≤ 0.5 dB is within the stated systematic budget: the gate is unchanged and the bias
   is recorded. A bias > 0.5 dB in any gated bin means (A) fails. N (beyond the pre-stated doubling
   rule), seeds and bins are never changed after results are seen.
6. **Gate (B)** on the Phase 05 numbers, as in B11: not worse by more than δ = 0.25 jnd room-averaged,
   no room's Δ̂ above +1 jnd, each with SE ≤ threshold/3, from seed-paired ensembles sized per phase-05
   "Paired comparisons". Follow the no-minimum-count and no-evaluable-pair branches of B11.
7. **`open_field`:** re-derive the Phase 04 consistency check (energy later than 50 ms after the direct
   sound) against the Lambert estimate (−23 to −43 dB per band, ledger OF).
8. **AQ10:** measure W1 and W2 with the promoted early part and record them in §0 (not a blocker).
9. If promoted: update goldens as an intended change (`update_goldens.py --reason "phase 05b adds early
   scattered energy"`), update AX16 and AX21, and add a §6 row.

## Out of scope

Directions of the scattered energy for binaural rendering (08); per-band scattering (B10); the tail
decay source (B12); changes to the mixing-time rule, AX22 or N_cap; any per-scene tuning (NFR-8).

## Acceptance criteria — automated

- [ ] Gate (A) passes on every case listed in scope 3 (or the outcome is "not promoted").
- [ ] **Rendering checks (DN-1), deterministic** (decider report 11, accepted by Maisara, 2026-11-05; corrections from the interrogator pre-check, report 12):
      - (i) taps: the rendered tap energy per step and band equals E_k,b within 1e-9 relative;
      - (ii) continuity: per band from 500 Hz to 2 kHz, the normalised cross-energy of the diffuse
        parts is ≥ 0.59 for a source move of 50 cm/s (Vorländer §15.3) × the AQ4 update interval
        max(30 ms, measured rebuild time), i.e. 1.5 cm at 30 ms, and for a 1 cm room-dimension change
        that crosses a patch boundary; so the equal-gain mid-fade dip of that part alone is
        ≤ 10·log10((1+0.59)/2) = −1.0 dB (Vorländer Eq. 4.14), the Phase 10 bound;
      - (iii) Rendered domain: render the diffuse part alone and measure its per-band energy with the
        AX14 half-octave meter, calibrated so that a single tap reads its tap energy. Measure over the
        whole early part [t_dir,e − maxHalfLength, t_mix,e + 2.5 ms + maxHalfLength] (padded by the
        band filter's half-length, AX15, so no energy rings out of the window). Compare it with
        Σ E_k,b over all steps, each weighted by its crossfade window (AX18). The equality holds in
        expectation over the random signs. The band energy is a quadratic form in the signs, with
        relative SD σ_rel = √(2·Σ_{i≠j} R_ij²)/Σ R_ii, where R_ij is the band-filtered pulse
        cross-energy. It is computed exactly from the seeded pulse times and the band filter (derived,
        not corpus; ≈ 1/√(B·T_w) when pulses overlap, ≈ 0 when resolved). Tolerance: ±3·4.34·σ_rel dB
        (the AX11 3σ convention). The check is gated in bands where 3·4.34·σ_rel ≤ 1 dB and reported
        in the others (for example 63 Hz, where 3σ ≈ 6 dB). The window is verified by the
        interrogator; the tolerance rule is the interrogator's proposal, adopted by Maisara on
        2026-11-05.
- [ ] The window-level check of scope 4 is run and its branch is recorded.
- [ ] Any tracer bias above 0.3 dB is diagnosed as in scope 5, and the result is recorded.
- [ ] Gate (B) is evaluated on the Phase 05 numbers, and Δ̂, SE, R and pass/fail are printed per
      comparison.
- [ ] The `open_field` check is re-derived and its new form is tested.
- [ ] Same scene + same seed gives a bit-identical IR on the same platform; no NaN, Inf or denormals.
- [ ] W1/W2 rebuild times recorded (AQ10).
- [ ] If promoted: goldens updated with the reason in `tests/golden/CHANGELOG.md`.

**Outcome.** `done` (promoted) when (A) and (B) both pass. `done (not promoted)` when (A) or (B) fails,
with the reason recorded in §0. With no evaluable EDT/C80 pair, promotion needs Maisara's explicit
sign-off on (A) alone.

## Listening / manual checklist (Maisara)

Listening pack: clicks and pink bursts through the six Phase 04 test rooms, Phase 04 IR against the
05b IR (if promoted).
- [ ] The early part sounds less sparse or "dry-then-reverb"; no audible jump into the tail.
- [ ] No new graininess or colouration in the first ~100 ms (if it fails, DN-1's rendering is revisited:
      decider report 11 reversal condition).
- [ ] `open_field` still sounds nearly dry with a ground reflection.

## Contractor review focus

Independence of the tracer from `src/sim` (separate code, separate seed); the mixed specular/diffuse
energy accounting; the gate statistics (k ≥ 684, doubling rule, no post-hoc changes); the AX16 switch
logic; determinism; rebuild cost.

## Risks

- (A) fails, or the tracer is biased: the scope 4 and 5 branches apply and the phase may close as "not
  promoted".
- Too few uneven-α or low-s BRAS rooms: no minimum count; the limitation is recorded in the Phase 05
  report and `bras_mapping.md` (F2).
- Rebuild time grows (patch propagation per rebuild): recorded against AQ10, not a blocker.

## Definition of done

All automated criteria evaluated; status row 05b `done` or `done (not promoted)` with the reason; listening
checklist in the PR.
