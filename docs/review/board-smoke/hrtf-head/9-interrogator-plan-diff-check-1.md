# D1 applied — interrogator, document mode on the plan diff, check 1 (2026-11-09)

Method: the registered `interrogator` agent, document mode on `8-plan-diff.patch` (phase-08, BUILD_PLAN §1/§2 AX35/§5 B14/§6, THIRD_PARTY). Headline: **one major, P08D-1 INCONSISTENT** (AC 2's −60 dB round-trip is referenced to the un-equalised resampled source while scope 3 makes the converter's DF-EQ always applied); P08D-3, -6, -15, -21, -22 minor IMPRECISE; everything else CORRECT or NOT CHECKABLE (dataset facts scheduled for pin time). Five questions Q1–Q5 → decider round 3. Ledger table verbatim below.

---

| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| P08D-1 | NUMBER/FACT | AC 2: decoded HRIRs match "the pinned-resampler output of the untrimmed resampled SOFA source within −60 dB" **while** scope 3 now says the converter "applies its own weighted diffuse-field curve to every set it converts", "always applied", "Nothing in the rule switches the application off", and scope 2 removes the onset and stores "minimum-phase or raw" HRIRs | **INCONSISTENT** (document contradicts itself) | A stored set carrying an EQ residual of up to 1 dB (the scope-3 "confirmed" band) differs from the un-equalised source by ≈ 20·log10(10^(1/20)−1) ≈ −19 dB, not −60 dB; a minimum-phase conversion or onset removal changes the waveform further (Begault Ch. 4 "Problems with Interpolation Algorithms", lines 1593–1597: the delay is removed and re-inserted separately). The pre-patch text kept the EQ "stored as an EQ filter … switchable in code for tests", which made AC 2 runnable; the patch deletes that path without re-referencing AC 2. | **major** (a test gate) | Q1 | open |
| P08D-2 | NUMBER | ≈ 104 MB for the full 8802-direction grid, four-rate float32 | CORRECT (arithmetic); inputs NOT CHECKABLE | taps 256·(44.1+48+88.2+96)/48 ≈ 235+256+470+512 = 1473; ×2 ears ×4 B = 11 784 B/direction; ×8802 = 103.7 MB. 8802 directions and 256 taps @ 48 kHz are dataset/plan inputs (dossier F11/F12; Armstrong et al. 2018 PDF at pin time). | none | — | open |
| P08D-3 | NUMBER | "≤ ~32 MB … a grid subset of ≤ ~3000 directions … and/or float16" | IMPRECISE | 3000 × 11 784 B = 35.4 MB in float32, above the bound; ≤ 32 MB in float32 needs ≤ ~2715 directions (the decision's own 2702 → 31.8 MB figure); float16 at 3000 → 17.7 MB. Same wording as decision item 4. | minor | Q3 | open |
| P08D-4 | NUMBER | −81° lowest measured elevation, +90° highest, −90° interpolated by York; 1.2 m; 512 samples @ 96 kHz with fades | NOT CHECKABLE (dataset); arithmetic CORRECT | 512 × 48/96 = 256 taps @ 48 kHz ✓. Settled at pin time (scope 1). | none | — | open |
| P08D-5 | NUMBER | AC 3 window 0.6–0.75 ms at ±90° (value unchanged; estimator to be named) | CORRECT under the onset-estimator condition, now stated | Blauert Ch. 2 §2.2.2 line 237 (Fig. 2.30) ≈ 650 µs; line 233 ΔS = (D/2)(φ+sin φ), D = 17.5 cm (line 222): 0.2249 m → 0.656 ms; Roginska & Geluso Ch. 1 line 959 ≈ 650 µs; Zotter & Frank Fig. 4.25a model 0.65 ms. | none | Q4 | open |
| P08D-6 | FACT | "a low-frequency/cross-correlation ITD exceeds an onset ITD, Roginska & Geluso Ch. 1" | IMPRECISE | Roginska & Geluso line 959: ≈ 650 µs, "750 µs for low-frequency sounds (Kuhn, 1977), depending on stimulus and measurement technique"; Blauert Ch. 2 line 226 phase/group delay "up to about 0.6–0.8 ms". The corpus nowhere states that a *cross-correlation* estimator exceeds an onset estimator. Restate: "a low-frequency ITD (≈ 750 µs) exceeds the broadband onset ITD (≈ 650 µs); the value depends on stimulus and measurement technique". | minor | Q4 | open |
| P08D-7 | NUMBER | York's D1 ITD plots ≈ 0.85 ms by an unstated method (dossier F21) | NOT CHECKABLE (dossier) | Settled by the pin-time measurement with the named estimator. | none | — | open |
| P08D-8 | NUMBER | ITD continuity slope 8.9 µs/° (D1-L13; not in the changed passages) | CORRECT | Zotter & Frank Eq. (4.51), R = 0.0875 m: dITD/dφ at 0 = 2R/c = 0.510 ms/rad = 8.90 µs/°. | none | — | open |
| P08D-9 | NUMBER | 1 dB provenance wording (Vorländer general jnd; Table 6.1 is G at 500–1000 Hz; by extension) | CORRECT | Vorländer abbreviations line 496; line 3167; Table 6.1 line 2060; B11 "applied by extension". | none | — | open |
| P08D-10 | FACT | One-third-octave bands for the diffuse-field average | CORRECT | Rumsey §3.2.4 line 954; Begault line 1489. | none | — | open |
| P08D-11 | NUMBER | Begault's ±1.5–2.5 dB is not a tolerance | CORRECT | Begault line 1489. | none | — | open |
| P08D-12 | NUMBER | 200 Hz lower edge; LF modelled below ~200 Hz; `--diagnostics` curve below 400 Hz | NOT CHECKABLE (dataset); internally consistent | Dossier F18/F26; pin time. | none | — | open |
| P08D-13 | NUMBER | 8 kHz upper edge; 0.1 dB = one tenth of 1 dB | CORRECT (document-internal) | CLAUDE.md band set; AC 3 band. | none | — | open |
| P08D-14 | FACT | DF-EQ = average over all directions = 1; Voronoi weights w_i = Ω_i/4π, Σ w_i = 1 | CORRECT (derived); Voronoi method NOT CHECKABLE in corpus | Blauert Ch. 4 line 525; Begault line 1489; Vorländer §16.1.1 line 4004. | none | — | open |
| P08D-15 | FACT | "weighted one-third-octave average … 0 dB within 0.1 dB" — averaged quantity not stated (power vs dB magnitude) | IMPRECISE (says less than the decision) | Decision D1-L15 writes Σ w_i\|H_i\|² (power); Begault line 1489 averages random-incidence noise levels (energy). | minor | Q2 | open |
| P08D-16 | FACT | Tail-coherence target solid-angle weighted | CORRECT (derived) | Vorländer Eqs. (6.12)–(6.13); line 4004. | none | — | open |
| P08D-17 | FACT | Voronoi cells dual to the stored Delaunay triangulation | NOT CHECKABLE (geometry) | — | none | — | open |
| P08D-18 | FACT | Head shadow is not a low-frequency effect | CORRECT | Rumsey §2.1.2 line 664; Blauert Ch. 2 line 225. | none | — | open |
| P08D-19 | FACT | Rectangular windowing may lose LF | CORRECT | Begault line 1539. | none | — | open |
| P08D-20 | FACT | Prefer onset-removed/minimum-phase interpolation | CORRECT | Begault lines 1593–1597. | none | — | open |
| P08D-21 | FACT | Checklist: generic HRTFs heard "inside" or "above" by some | IMPRECISE ("above") | Vorländer §6.3.2 line 1967 (front–back, median-plane uncertainty); Begault Ch. 3 line 1109 (IHL 25 % → 3 %); an upward bias for dummy heads is not in the corpus. | minor | — | open |
| P08D-22 | FACT | Risks: "The converted output is the same either way" | IMPRECISE | The *state* is the same (weighted average = 0 dB), not the *signal*; the rebuttal's own residual objection. | minor | Q5 | open |
| P08D-23 | FACT | MIT KEMAR fallback: unmeasured zone below −40° | CORRECT | Begault line 2137. | none | — | open |
| P08D-24 | FACT | Plan ↔ decision: scope 7 phases (12, 13, B9) | CONSISTENT with restatement 1 | `7-interrogator-round2.md`; phase-12 line 61; phase-13 line 128. | none | — | open |
| P08D-25 | FACT | Plan ↔ decision: fallback conditions + IEM confound | CONSISTENT | Seat 4 §6. | none | — | open |
| P08D-26 | FACT | Plan ↔ decision: R6, R9, AX35 window, checklist, header fields, fade-out, no grouping, THIRD_PARTY note | CONSISTENT | sentence-by-sentence against `6-decider-rebuttal.md`, `4-decider-decision.md`. | none | — | open |
| P08D-27 | DECISION | SADIE II D1 head-only KU100, DF-equalised | CONSEQUENCE | Vorländer §6.3.2; Rumsey §3.2.4 lines 952, 957. | minor | — | open |
| P08D-28 | DECISION | DF-EQ always applied; no headphone compensation scheduled (B14) | CONSEQUENCE | Blauert Ch. 4 line 528; Begault lines 1488–1489; Vorländer line 4018. | minor | — | open |
| P08D-29 | DECISION | Grid subset ≤ ~3000 and/or float16 | CONSEQUENCE | Begault line 1595 (Wenzel & Foster 1993). | minor | — | open |
| P08D-30 | DECISION | Anechoic direct-only render beside every room render | CONSEQUENCE | Begault Ch. 3 line 1109 / Table 3.2. | minor | — | open |
| P08D-31 | DECISION | No 2° grouping until the benchmark; MIT fallback DF-EQ on by default | CONSEQUENCE | Rumsey §3.2.4 line 953; Begault line 1481. | none | — | open |

## Questions

1. **(P08D-1)** What does AC 2's −60 dB compare? (a) the stored HRIRs — after the converter's always-applied DF-EQ, onset removal and any minimum-phase step — against the resampled source **with the same pinned transformations applied**, or (b) pre-EQ data? As written, the reference is the un-equalised resampled source, and a set carrying even the "confirmed" ≤ 1 dB residual differs from it by ≈ −19 dB, so AC 2 and scope 3 cannot both hold. Which is meant, and where does the pre-EQ path live now that "switchable in code for tests" is deleted?
2. **(P08D-15)** Is the weighted one-third-octave diffuse-field average a **power** average Σ w_i|H_i|² per band or a **dB-magnitude** average?
3. **(P08D-3)** Is the float32 direction bound ≤ ~3000 (≈ 35 MB) or ≤ ~2700 (≈ 32 MB)? If 3000 is kept, is float16 mandatory rather than "and/or"?
4. **(P08D-5/6)** Is the AC 3 estimator an **onset/pulse** estimator? And should the clause read "a low-frequency ITD exceeds the onset ITD" since the corpus does not name cross-correlation as the larger-valued method?
5. **(P08D-22)** In "The converted output is the same either way", is "the same" the *state* or the *signal*?
