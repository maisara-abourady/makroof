# D1 (dry run) — Seat 5, the deadline keeper (2026-11-09)

Method: the registered `seat5-deadline-keeper` agent, briefed with B5 of `1-decider-convene.md`; no dossier yet (dataset facts `[Hyp]`). Verbatim.

---

SEAT 5 POSITION

**1. Reading.** Which dummy-head set becomes `generic-v1`, judged for what it does to CI gates, binary size/load/memory, determinism (AX5) and the thread the lookup runs on. Cues (§4.1/§4.5): "which clock is this on, what crosses, who owns the memory"; §4.4 "a test that only exercises the happy path"; §10.2 "find the worst case (grid × taps × rates) before the common case". The head itself (KU100 vs KEMAR) is not my measure; the dataset's *shape* and *hosting* are.

**2. Ranking.**
1. (d) TH Köln KU100 `HRIR_L2702.sofa` — *prefer* (SOFA-native, 2702 directions known from the corpus, mid-size).
2. (c) MIT KEMAR — *can live with* (smallest; but 44.1 kHz source, not SOFA-native `[Hyp]`, 1994-era hosting `[Hyp]`).
3. (a) = (b) SADIE II KU100 / KEMAR — *can live with*, conditioned on grid size (unknown, `[Hyp]` dense) and storage format.
4. Dataset-agnostic converter + `.bin` header — *prefer*, rate 0 now; it is my criterion 5 (reversibility) and the B4 seam. I add to it: header carries set id, source-SOFA SHA-256, converter version, per-rate tap count, direction count, EQ-applied flag, ITD convention, fixed little-endian; the AC 1 script matches `LICENSE-<id>.txt` *to the header's id*, not to a filename.
Nothing is veto-grade: the lookup never touches the audio thread (see 5), so criterion 1 is untouched by any option.

**3. Tension now.**
- (a)/(b): **2**. Size unknown. Arithmetic I can stand behind: phase-08 scope 2 fixes 256 taps at 48 kHz, scaled → ≈235/256/470/512 taps at 44.1/48/88.2/96 kHz = 1473 taps × 2 ears × 4 B ≈ 11.8 kB per direction for the four-rate embed. 710 directions → 8.4 MB; 2702 → 31.8 MB; a dense grid of order 8–9 k directions `[Hyp]` → ~100 MB, × 3 formats in the installer. A 100 MB generated C++ byte array is a compile-time and MSVC-memory risk on the Windows CI job `[Inferred]`, no incident id). Also 48 kHz SOFA assumed by the phase while the corpus only shows SADIE's 44.1 kHz 16-bit WAV set (Zotter & Frank Fig. 1.14) `[Hyp]` that a 48 kHz SOFA exists.
- (c): **1**. 8.4 MB; but `convert_sofa.py` then needs a non-SOFA reader or a third-party SOFA conversion whose provenance must itself be pinned (criterion 4, one more thing to maintain). Round-trip reference at 44.1 kHz → 48 kHz resampled before compare: fine offline.
- (d): **1**. 31.8 MB four-rate (≈ 95 MB over three formats); SOFA-native; hosted on sofacoustics.org `[Hyp]` on availability.
- AC 1 licence script: **0** for every set — a file-presence check is deterministic.
- Round-trip gate (−60 dB): **1** for every set, two flakiness sources independent of head: (i) it needs the SOFA source in CI → a network download in a test; (ii) "match the SOFA source (resampled)" must be defined as *resampled and trimmed* with the same pinned resampler, else the 256-tap truncation of a longer HRIR fails the gate deterministically (energy beyond 256 taps is Seat 3's question).
- Header condition: **0**.

**4. Tension later (debt).**
- (a)/(b) dense `[Hyp]`: **2**. Commits every CI build on three OSes to compiling/linking ~100 MB; every install to ~300 MB; every HrtfSet copy per instance to 100 MB unless process-shared. Undo = re-run the converter with decimation or float16 (a parameter change, cheap) *if* the header is dataset-agnostic; a rewrite of the embed step if it was a C++ array. Evidence arrives in the phase-08 session's first macOS/Windows CI run and in Seat 7's download-size figure.
- (c): **1**. Debt is the extra reader path and dependence on a 30-year-old host site for the round-trip gate; mitigated by a private mirror (the `fetch_corpus.sh` pattern). Elevation floor −40° (Begault Ch. 4) is Seat 2's debt, not mine.
- (d): **1**. Same hosting debt, smaller.
- Header condition: **0**; it *removes* debt: swapping the set (licence failure, B4 personal SOFA) touches `tools/hrtf/` and `resources/`, never `src/sim`.

**5. Evidence.**
- Lookup thread: from the code, `sim::buildRoomIR` is called only from `ScenePipeline::decide`, which runs on `plugin::IrBuilderThread` (std::thread, AX33) or synchronously on non-audio callers (prepare, restore, offline); `processBlock` never reaches it. So `HrtfSet::query` allocation is a build-budget cost (AQ10 ≤ 50 ms rebuild), not a deadline risk. Still: zero allocation in `query` is cheap to enforce with the existing `AllocationTracker` (`tests/unit/test_realtime_engine.cpp`, `[alloc]`), and per-image-source allocation × thousands of images is the Bencina "1000-times spike" on the builder (§4.1 `[Self-report: general]`).
- MIT KEMAR: 1.4 m, 44.1 kHz, 710 positions, elevations −40…+90° — corpus, Begault Ch. 4 "KEMAR HRTF measurements … MIT's Media Lab".
- TH Köln: `HRIR_L2702.sofa`, 2702 directions, sofacoustics.org — corpus, Zotter & Frank §4 (Fig. 4.29 note) and abbreviations "TH Köln".
- SADIE: subject 1 = KU100, 44.1 kHz 16-bit WAV named in corpus (Zotter & Frank Fig. 1.14); 48 kHz SOFA, grid size, HRIR length: `[Hyp]`, researcher R3.
- AX5 across platforms: the committed `.bin` is identical bytes everywhere by construction; only the *converter* needs reproducibility, and `tools/ci/pin_hashes.py` already hash-pins Python deps (from the code).
- Large generated-array compile risk on MSVC: `[Inferred]`, no incident in my register.
- For the researcher: R3 (direction count, HRIR length, native rate, SOFA version, file SHA-256 per set); hosting stability/mirror permission per set; whether MIT KEMAR exists as an official SOFA.

**6. Conditions of acceptance.**
- (a)/(b) 2 → 1: either the grid is ≤ ~3000 directions, or the converter decimates/stores float16 with the round-trip gate still −60 dB; *and* the embed is a build-step object (`add_custom_command` → object/`.incbin`-style), not a generated C++ array.
- Round-trip gate 1 → 0: SOFA fetched by checksum into a git-ignored dir via a script like `fetch_corpus.sh`; test skips with a marker when absent unless `SPATIAL_REQUIRE_HRTF_SOURCE=1` (the `render_cli` pattern); reference = pinned-resampler output, trimmed identically.
- All options: `HrtfSet` is one immutable process-wide object (not per instance), built off the audio thread, with the stored triangulation plus an O(1) direction→triangle index so `query` cost does not scale with grid size; `[alloc]` test on `query` and on the BRIR build.

**7. Hand-offs.** Energy beyond 256 taps and grid density vs the continuity gate → Seat 3. Elevation floor coverage → Seat 2. Installer size and download cost → Seat 7. Licence terms → human/lawyer via Seat 7.

**8. Premortem.** A dense set lands as a generated byte array; the Windows CI job runs out of time or memory compiling it, and the phase-08 session is the first to notice when its only CI run fails on one platform.
