# Phase-07 decisions D1–D9: interrogator option check (/fix-plan step 3, 2026-11-08; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Source rows: ledger section "docs/phases/phase-07.md — interrogation (2026-11-08)". Decisions as returned by the
plan-editor (DECISIONS NEEDED): D1 = P07-5, D2 = P07-7, D3 = P07-8, D4 = P07-3 (headroom), D5 = P07-11,
D6 = P07-12, D7 = P07-13, D8 = P07-19, D9 = P07-22.

## Summary
- **D1 (P07-5):** NEEDS DECISION LOOP. A and C both give a valid scene; B as described does not. Corpus silent.
- **D2 (P07-7):** NEEDS DECISION LOOP. Both valid; product choice. Corpus says what each does to level and DRR.
- **D3 (P07-8):** NEEDS DECISION LOOP. (a) and (b) valid; (c) only works for the default materials. T60max = 8 s at ≈ 13.2 m cube, or medium_room ×3.04 = 24.3 × 36.5 × 12.2 m.
- **D4 (P07-3):** NEEDS DECISION LOOP. A's premise wrong as stated; B product choice; C conflicts with AX2 if hidden.
- **D5 (P07-11):** VERIFIED (A). Raising the minimum does not remove the modal limit unless ≳ 10.5 m, which would exclude the default room.
- **D6 (P07-12):** NEEDS DECISION LOOP. Both meanings meet AQ4 and Vorländer Table 15.1; AQ4 records recommendation (A).
- **D7 (P07-13):** NEEDS DECISION LOOP. No option valid under every condition; new objection against AX18's premise.
- **D8 (P07-19):** NEEDS DECISION LOOP. Product choice; corpus silent apart from the PDC condition on B.
- **D9 (P07-22):** NEEDS DECISION LOOP. Product choice; corpus leans to relative (log-like) steps; A's "log-like" imprecise.

## Ledger

| decision | option | verdict | evidence | outside-corpus facts |
|---|---|---|---|---|
| D1 | A (builder's 4-step rule) | CORRECT on validity (geometry; corpus silent) | Step 4 always succeeds: box side ≥ 1.3 m, so on every axis the listener has ≥ 0.65 m free on one side; distance 0.3 m within AX9's 1 nm. No contract rule between the two emitters. **Consequence:** discontinuous; can put the emitter on the opposite side. Example: 1.5 m cube, l = (0.25, 0.75, 0.75), e = (0.1, 0.75, 0.75): step 2 → x = −0.05, step 3 clamps to 0.1 (0.15 m), step 4 picks +x → e = (0.55, …), though (0.1, 1.01, 0.75) at 0.300 m existed. A side swap becomes a direction change once Phase 08 renders binaurally. | none acoustic |
| D1 | B (push the listener) | CONDITIONS VIOLATED (single push) | Pushing away from one emitter can bring it within 0.3 m of the other (1.5 m cube, L x = 0.5, R x = 1.0, listener x = 0.7 → 0.8, 0.2 m from R). Also moves the listener when the user edited an emitter. | — |
| D1 | C (nearest valid point) | CORRECT once a tie-break is defined | Nearest point in (box minus open 0.3 m ball) exists; not unique when e = l and in symmetric corner cases. Continuous away from ties; no side flip. | — |
| D2 | A (relative) | PRODUCT MATTER | Uniform scaling by k: r ∝ k, r_c = (A/16π)^½ ∝ k (Kuttruff §5.6 Eq. 5.44), so DRR unchanged; direct and reverberant level fall by 20·log10 k; T ∝ k (Kuttruff Eq. 4.12, no air). Blauert §3.3 (direct/reflected level difference as distance cue), Blauert Ch. 2 (1/r). Holds for uniform scaling, no air; not exactly per axis. | user expectation |
| D2 | B (absolute, clamped) | PRODUCT MATTER | r fixed, r_c ∝ k, so DRR changes by 20·log10 k (Eq. 5.44). Shrinking clamps and can trigger the D1 push; reversible under P07-6. | same |
| D3 | (a) accept and document | CORRECT; "low end is cut" IMPRECISE | Consistent with AX6. 100 m cube, default materials, decay depth at 12 s = 60·12/T: ≈ 11.9 dB (63 Hz), ≈ 18 dB (125 Hz), ≥ 26 dB (250 Hz), ≈ 48 dB (500 Hz), ≈ 66 dB (1 kHz) (Kuttruff Eq. 4.12, Table 6.1). Every band with T > 8 s is cut. | air absorption 63–250 Hz; audibility |
| D3 | (b) end fade | CORRECT as a technique; changes Phase 04 output | Vorländer §9 intro: time windows against discontinuity artefacts. Removes the step, not the missing decay. | audibility |
| D3 | (c) lower room_* maxima | CONDITIONS VIOLATED | Default materials, 63 Hz: ᾱ = 0.0433, T = 0.606·L (Eq. 4.12, no air) → 8 s at L ≈ 13.2 m; medium_room proportions T63 = 2.63 s, k = 3.04 → 24.3 × 36.5 × 12.2 m. Holds only for default materials: AQ3 α = 0.01 everywhere gives T = 2.67·L → 8 s at L ≈ 3.0 m (AX6: room limits don't bound IR length). Also a contract-valid scene above the parameter max can't be restored unchanged if parameters are authoritative (P07-17). | m at 63 Hz (< 1 % effect) |
| D4 | A (keep, document) | CONDITIONS VIOLATED (premise) | Contract allows emitter gainDb up to +12 dB → 16.5 + 12 = +28.5 dB direct. Reverberant field adds: w_r/w_d(1 m) = 16π/A (Kuttruff Eq. 5.44); 1.5 m booth, 63 Hz, A = 0.585 m² → +19.3 dB per emitter; two emitters ≈ +23.3 dB (500 Hz ≈ +20.1 dB). Vorländer §1.7 Table 1.3; float clips only at master/bounce (Izhaki Ch. 11). | input levels; model tail level in a booth |
| D4 | B (widen trim) | PRODUCT MATTER | ≥ 28.5 dB covers the direct worst case; reverberant worst case depends on materials (α = 0.01: +25.7 dB per emitter). | same |
| D4 | C (normalisation) | INCONSISTENT with AX2 if hidden; else PRODUCT MATTER | AX2 "No hidden auto-gain". | — |
| D5 | A (record as limit) | CORRECT | Kuttruff §3.6 Eq. 3.44: 1.5 m cube, default materials, f_s ≈ 1040 / 880 / 590 / 520 Hz at 63 / 125 / 500 / 1k Hz. | perceptual weight |
| D5 | B (raise minimum) | CONDITIONS VIOLATED | f_s ∝ 1/L for a cube; f_s ≤ 125 Hz needs L ≥ 10.5 m (63 Hz: 24.7 m); medium_room itself has f_s ≈ 166 / 138 Hz. Also leaves the contract's 1.5 m (P07-17). | Expert's limit |
| D6 | A (spacing between build starts) | CORRECT; not separable | Matches AQ4's recommendation; isolated update at rebuild + 2P (W1 41.9 ms at P = 512) then 30 ms fade; far inside Vorländer §15 Table 15.1 (700 ms). 35 ms rows don't apply in 07 (AQ8; AX31). | full rebuild time at max room / 96 kHz |
| D6 | B (delay to next 20 ms slot) | CORRECT; not separable | Worst case ≤ 61.9 ms, below 700 ms; AQ4 wording allows it; same steady-state spacing. | same |
| D7 | A (EP recall/size, EG positions) | CONDITIONS VIOLATED | Criterion: constant power in the overlap (Vorländer §9.2.1); cross term 2·p1·p2·cos(ωΔx/c) (Vorländer §4.3 Eq. 4.15). Mid-fade power (1+ρ)/2 for EG, (1+ρ) for EP; break-even ρ = 0.414. Same tailSeed resize: AX1 shifts the tail by Δr_nearest/c (`Engine.cpp`); band ρ_b ≈ cos(2π·1.06f_c·τ)·sinc(0.707f_c·τ) (signal theory, flat in-band). Default scene, 10 % resize, τ = 1.78 ms: 63 Hz ρ ≈ 0.73 (EP +2.4 dB), 1 kHz ρ ≈ −0.14 (EG −3.6 dB). Recall into the same scene ρ ≈ 1 (EP +3 dB). | programme correlation; audibility |
| D7 | B (EG everywhere) | CONDITIONS VIOLATED | Unrelated IRs ρ ≈ 0 → −3.0 dB (Vorländer §1.7 Eq. 1.37; AX18). | same |
| D7 | C (EP everywhere) | CONDITIONS VIOLATED | Correlated swaps ρ ≈ 1 → +3.0 dB (Eq. 4.15). | same |
| D7 | against AX18's premise | CONDITIONS VIOLATED | "Position updates → highly correlated" fails for the tail whenever the nearest emitter's distance changes (AX1 shifts the shared tail): Δr = 0.47·c/f_c (16 cm at 1 kHz) gives ρ_1k ≈ −0.83 → tail band −10.6 dB mid-fade (EG), −7.6 dB (EP). ρ ≈ 1 only for Δr ≪ λ/4 (≈ 1 cm at 8 kHz). Vorländer §15.1: fading optimised against colouration. | same |
| D8 | A (silence + flag, P+32) | PRODUCT MATTER; consistent with RealtimeEngine | corpus silent | host / pluginval behaviour |
| D8 | B (dry pass-through) | PRODUCT MATTER, condition | If latency stays P+32 the dry path must be delayed by P+32, else PDC shifts the track early (Izhaki Ch. 11). | same |
| D8 | C (internal resampling) | NOT CHECKABLE; out of 07 scope | — | resampler quality |
| D9 | A (skew, 10 m centre) | PRODUCT MATTER; "log-like" IMPRECISE | v = 1.5 + 98.5·x^p, v(0.5) = 10 → p = 3.535; d ln v/dx 0.66 (x = 0.1), 6.0 (0.5), 3.5 (1) vs constant 4.20 for log; bottom 20 % spans 1.5–1.83 m. | JUCE skew; user expectation |
| D9 | B (linear) | PRODUCT MATTER | 1 % travel = 0.985 m (+66 % at 1.5 m, 1 % at 100 m). | same |
| D9 | C (log) | PRODUCT MATTER (corpus leans this way) | T jnd ≈ 4 % (Kuttruff §7.6), EDT jnd 5 % (Vorländer Table 6.1); T ∝ L (Eq. 4.12); log gives +4.3 % per 1 % travel ≈ one jnd; centre √(1.5·100) = 12.25 m. | same |
