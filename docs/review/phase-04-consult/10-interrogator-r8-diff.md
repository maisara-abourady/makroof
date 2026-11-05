Science check of /tmp/claude-0/-home-user-makroof/05ae2e1f-dec9-587c-bb0d-7484bc818a46/scratchpad/fixplan-diff-r8.patch, with decider report /home/user/makroof/docs/review/phase-04-consult/8-decider-open-items-c1b171f.md (corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d). Nothing in the plan text is WRONG. The main finding is that "f ≤ 0.41" for the Phase 10 dip gate only holds when the two segments have equal power (FR-01). For DN-1, rendering option (c) is wrong for audio; the rest stays OPEN.

## 1. Part A, DN-1 (phase-05b scope 1)

| choice | option | verdict and evidence | classification |
|---|---|---|---|
| Rendering | (a) seeded Gaussian noise per band under the envelope | Valid for omni, with a condition. Vorländer Eq. 11.51 asks for a fine structure of equivalent reflections whose density n_j matches the actual reflection statistics (Heinz). Vorländer §15.2 says the density grows with t², and Fig. 15.5 uses a Poisson pulse process. Plain Gaussian noise means unlimited density, which is wrong for the sparse part before t_mix. It also leaves no directions for Phase 08, so 08 would have to assume a diffuse field. It is deterministic (AX5). With a fixed seed and an envelope that varies smoothly with position, consecutive IRs stay correlated, so AX18's equal-gain premise holds (NFR-3). | OPEN, acceptable |
| | (b) per-patch band-filtered bursts at their delays | Kuttruff §4.5 (Eqs. 4.24–4.29) treats each patch as a secondary source with its own delay and direction. That is what the per-reflection HRTF of Vorländer Eq. 11.50 and the 10×10° directional groups of Fig. 15.5 need in Phase 08. Seeding each patch by its index keeps small moves correlated (NFR-3) and keeps AX5. The cost is patches × bands. | OPEN, **lean (b)**, with burst density per Eq. 11.51 |
| | (c) envelope only | Not a pressure IR. Vorländer §15.2 and Eq. 11.51 say the fine structure "must be created" for convolution. Adding the envelope to the squared band IR is valid only for the Phase 05 metrics, not for audio. | VERIFIED: reject (c) |
| Patches and step | (a) converge per scene on every rebuild | The halving depth can change at some source position. The patch layout then jumps, the noise per patch decorrelates, and the position crossfade loses its equal-gain premise (the AX22-type dip). This breaks NFR-3. Its cost is also unbounded against AQ10. | reject |
| | (b) frozen patch size from the Phase 05 convergence | Continuous in position, deterministic, and identical offline and in realtime. Condition: one size, the finest that Phase 05's BRAS rooms and the (A) cases need, confirmed by gate (A). The 1 ms step is Kuttruff §9.8's typical class width. | OPEN, **lean (b)** |
| | (c) patch size set by the W1 budget | Lets CPU decide accuracy, which reverses NFR-1's priority over NFR-2. Acceptable only if gate (A) passes at that size. | fallback only |

One point the options miss: Vorländer Table 15.1 gives the scattering part 3 s per move > 1 m, against 700 ms per 0.25 m for the specular part. So the diffuse part could legitimately be updated less often than the specular part. That is a cache option, not a requirement.

## 2. Part B findings that are not CORRECT

| id | kind | item | verdict | evidence | severity | status |
|---|---|---|---|---|---|---|
| FR-01 | NUMBER | "total dip = 10·log10(1 − 0.5·f) ... holds for f ≤ 0.41" (AX22, phase-04 Risks, phase-10) | CONDITIONS VIOLATED / INCONSISTENT | The formula is the value at mid-fade, or the worst case only when the two segments have equal power. The arithmetic holds: 1 − 0.5f = 10^−0.1 gives f = 0.411. But the same row says the segment's largest dip at 10:1 is 4.4 dB (ratio 0.365, Vorländer Eq. 4.14). The worst total dip is then 10·log10(1 − 0.635f), so the bound is f ≤ 0.32. The time window over which "band-energy dip" is measured (instantaneous or over the 30 ms) is also not stated. | major | open |
| FR-02 | FACT | AQ10: a miss "lowers the update rate, within Vorländer Table 15.1's 700 ms for moves > 0.25 m" | IMPRECISE | This is true only if the W1/W2 rebuild stays ≤ 700 ms, which is not yet measured. Table 15.1's 700 ms covers "binaural processing and specular part". Updates of the scattering part, which phase 05b adds, are listed at 3 s for moves > 1 m. | minor | open |
| FR-03 | NUMBER | B12: "deterministic, so no seed noise"; margin 0.25 working jnd = 1.25 % points | IMPRECISE | 0.25 × 5 % = 1.25 % is right. "Deterministic" is right, but not "error-free". a* is converged only to < 1 % change per patch halving, and γ² sensitivity reaches ≈ 0.4–3.6 % (Kuttruff Eqs. 5.33–5.34). Both are the size of the margin. The 5 % T jnd is a working value from outside the corpus; Vorländer Table 6.1 gives 5 % for EDT, not T. | minor | open |
| FR-04 | NUMBER | 05b scope 4: switch whenever ΔL_b,tr > 1 dB | IMPRECISE | ΔL_b,tr contains the tracer's noise, σ = 4.34/√k ≤ 0.17 dB at k ≥ 684 (Vorländer Eqs. 11.15–11.18). Unlike the FE-01 rules, this switch has no SE ≤ threshold/3 condition, so values near 1 dB can go either way. | minor | open |
| FR-05 | NUMBER | Decider report: "≈ 3 600–5 500 images ↔ ν_r(13)–ν_r(15)" | IMPRECISE | Kuttruff Eq. 9.23 gives ν_r(13) = 3 302, ν_r(14) = 4 088, ν_r(15) = 4 990, ν_r(16) = 6 016. The 3 600–5 500 range is the per-emitter budget from Phase 03's 344–525 ms for 2 × 37 880 images (4.5–6.9 µs per image, 50 ms over 2 emitters). As "the largest i₀ within budget = 13–15", which is what the diff states, it is correct; as an equality it is not. Rebuild time ∝ image count is an assumption, not corpus. | minor | open |

CORRECT, with working:
- **ν_r values (Kuttruff Eq. 9.23):** ν_r(10) = (2/3)(2000 + 300 + 40) = 1 560. This matches the |x| + |y| + |z| ≤ 10 lattice count, 1 561 minus the original source.
- **t_cap (Eq. 4.6 integrated):** t = (N·V/(4π/3))^(1/3)/c. ν_r(10) gives 130.7 m → 0.381 s; ν_r(14) gives 180.3 m → 0.526 s; 37 880 gives 1.104 s. t_mix ≈ 6.8·6000^(1/3) = 124 ms.
- **Vorländer Table 15.1:** 700 ms for moves > 0.25 m and 3 s for > 1 m, as quoted. The phase-10 option (b) uses 700 ms for ISM-only fallback scenes, which matches the table's "specular part".
- **Flutter scene:** Kuttruff §4.2 describes rigid end walls with absorbent other faces as typical of flutter. Hard x-walls 20 m apart give a period of 40/343 = 117 ms, just above the 30–100 ms the corpus lists, which is acceptable.
- **B12 margin:** 1.25 % points = 0.25 × 5 %.
- **Phase-05b anchors:** the s = 0 tracer self-check against the ISM lattice is valid: the image rooms fill space, so the lattice is the exact solution of the specular geometric model (Kuttruff §4.1). The s = 1 check against the Table 5.2 iteration is supported by Kuttruff §5.7, which reports similar results from ray tracing (§9.8).
- **Early diffuse energy:** it depends on positions, so it is rebuilt every time (Eqs. 4.27, 4.29).
- **05b copies of the B11 numbers:** k ≥ 684, N₀ = ⌈254·V⌉ and the mixed s/(1−s) split match the earlier verified B11 text.

## 3. WRONG items

None in the plan text. DN-1 rendering option (c) is a candidate option, not plan text; it is VERIFIED as rejected for audio rendering.