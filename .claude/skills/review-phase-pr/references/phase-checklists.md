# Per-phase review checklists

For each phase: what the diff must contain, which acceptance criteria to verify with CI evidence,
the contractor review focus from the phase file, and the traps a reviewer looks for beyond the
phase text. Always read the actual `docs/phases/phase-XX.md` too; this file adds the reviewer's
angle, it does not replace the phase file. Domain facts behind the traps live in the other
reference files (named per phase).

Status at writing (2026-11-04): Phase 00 done (PR #2). Phases 01–13 not started.

---

## Phase 00 — Scaffolding, CI, pluginval, empty plugin (done)

Reference: `tooling-testing-licences.md`, `realtime-audio-juce.md`.
- Pass-through must be exact (memcmp) through the same `AudioProcessor` the wrappers use, at
  44.1/48/96 kHz and blocks 1/64/512/2048. Trap: a test that calls a private helper instead of
  `processBlock`, or that only checks one channel.
- JUCE pinned at a tag, `SYSTEM` FetchContent, THIRD_PARTY rows. pluginval pinned by checksum.
- CI: 3 OSes, release build for pluginval, debug for tests, ASan job, clang-format job.
- Follow-up PRs touching CI: pins only move together with `docs/THIRD_PARTY.md`.

## Phase 01 — Scene contract v1

Reference: `tooling-testing-licences.md` (JSON Schema, semver), `process-rules.md` §4.
Must contain: `SceneDescription.h`, `Version.h` (1.0), `Json`, `Validate`, `Parse`, schema
`docs/contract/scene-v1.schema.json`, `docs/contract/README.md`, ≥ 5 valid and ≥ 15 invalid fixtures,
`tools/ci/check_boundaries.py` + self-test, THIRD_PARTY rows (nlohmann/json, jsonschema).
Verify:
- Field names and semantics exactly as the phase spec (`xMin`…`ceiling`, `[W,D,H]`, 8 absorption
  values, ranges AQ3, limits AX6, exactly two emitters AX7, `extensions` preserved, `hrtfId` only
  `generic-v1`). These freeze at release; a deviation is a design decision needing an AX row.
- Version rules: same major + higher minor loads with a *warning* and ignores unknown fields; a
  different major is an error; unknown fields at a known minor are an error. Test all four.
- Round trip byte-identical on the second serialization (floats with round-trip precision, key
  order stable). Trap: `nlohmann::json` default object ordering is alphabetical (`std::map`); if
  the spec needs insertion order, `ordered_json` must be used consistently.
- Validator never throws out of the library; every error has a JSON path and a stable code; invalid
  fixture filename = expected code and the test asserts *exactly* that code (not "any error").
- Schema and C++ validator agree on every fixture; geometric rules listed as C++-only in the schema
  description and the `_cppOnly` sidecar.
- Boundary script: fails on `sim`→`module3d`, `module3d`→`sim`, either→`plugin`, and
  `contract`/`sim`→`juce_`. Self-test with a temp tree proves it fails, not only that it passes.
Traps: `double` vs `float` positions (contract should be double for round-trip exactness);
validation of NaN/Inf in JSON numbers; emitters sharing a channel; absorption exactly 0.01 and 1.0
accepted; `tailSeed` as unsigned 32-bit (JSON parsers may hand back a signed or 64-bit value).

## Phase 02 — Offline render CLI + acoustic analysis harness

Reference: `metrics-and-validation-data.md`, `tooling-testing-licences.md`.
Must contain: `sim/Engine.h` stub, `sim/OfflineRender` (direct convolution reference),
`render_cli` with the documented flags and exit codes (0/2/3), `tools/acoustics/` package
(`signals`, `bands`, `metrics`, `compare`, `clicks`, `golden`, `cli`), `tools/ci/listening_pack.py`,
`tools/ci/update_goldens.py`, `tests/golden/CHANGELOG.md`, pinned `requirements.txt`, CI python job,
dr_wav row in THIRD_PARTY.
Verify:
- `metrics.py`: Schroeder backward integration on squared pressure, Lundeby or documented
  truncation, T20/T30 regression ranges (−5…−25, −5…−35 dB) and ×3/×2 extrapolation, EDT 0…−10 dB
  ×6, C50/C80/D50 boundaries, per-band via `bands.py` matching `kOctaveBandsHz`.
- Synthetic decay test recovers T60 within ±2% (125 Hz–8 kHz) and ±5% at 63 Hz; pyroomacoustics
  `measure_rt60` agreement ±5%; C80 analytic ±0.2 dB.
- Click detector: 100% of 200 injected steps (−60…−6 dBFS) flagged, 0 false positives on the clean
  and the slowly modulated tone. Trap: the detector's baseline being computed *including* the
  clicks (median is robust; mean is not); frames at file edges; the HF filter's zero-phase pre-ring
  moving a click earlier than its true frame.
- `compare.py` arrival detection ±0 samples on a synthetic spike train. Trap: band-pass filtering
  before peak picking shifts peaks (don't filter for arrival detection).
- `OfflineRender` must be independent of the future real-time path (no shared partition code):
  time-domain or plain FFT convolution written separately; it is the reference for Phase 06.
- Stub render bit-identical to input, in Catch2 and pytest end-to-end; exit code 2 with readable
  errors for every invalid fixture.
Traps: WAV I/O float32 vs int16 changing bit-exactness; `render_cli` writing IR channels in a
different order than documented (`emitter*numOutputs+out`); pinned but un-hashed Python deps;
the listening pack README promising sounds the stub cannot make.

## Phase 03 — Early reflections: shoebox ISM (omni)

Reference: `room-acoustics.md` (K4), `metrics-and-validation-data.md`.
Must contain: `sim/ism/ImageSources`, `sim/ism/BandRenderer`, `sim/AirAbsorption`, wiring into
`buildRoomIR(Kind::Omni)`, `render_cli --mode omni`, benchmark, pytest cross-check vs
pyroomacoustics, goldens for 3 fixtures at order 10, listening pack entries.
Verify (each is an automated criterion; demand the CI evidence):
- Enumeration: images via lattice indices and parity; arrival time = ‖image − listener‖/c within
  1e-9 s for 200 random scenes; reflection counts per surface derived from indices. Trap: parity
  applied to the wrong axis sign; counting a surface hit for the wrong wall (xMin vs xMax).
- Amplitude: `(1/r) · Π(√(1−α_b) · √(1−s))^{hits} · air_b(r)`; direct path at 1 m = 1.0 (AX2).
  Classic bug: `(1−α)` on pressure instead of `√(1−α)`; scattering applied as pressure instead of
  energy; air absorption applied per hit instead of per path length; `c` not 343.0 named constant.
- Cross-check vs pyroomacoustics: first 50 reflections ±0.5 dB and ±1 sample for 10 random rooms
  with frequency-independent α, s = 0, no air absorption. Traps (details in `room-acoustics.md`
  §3): the returned RIR carries a global delay of `frac_delay_length // 2` = 40 samples that must be
  subtracted or aligned away; pure ISM in pyroomacoustics ignores scattering entirely (it applies
  √(1−s) only in hybrid mode), so the test must keep s = 0; its defaults are fs = 8000,
  max_order = 1, air_absorption = False, and a 10 Hz zero-phase high-pass (`rir_hpf_enable`) that
  must be disabled; indexing is `rir[mic][src]`; spreading is 1/r with no 4π.
- Reciprocity ≤ −120 dB residual; symmetry gives mirror-identical image sets; α = 1 and order 0
  give direct path only.
- Filterbank: linear-phase, flat bands sum to a delta within −100 dB; single-band isolation
  ≥ 20 dB; group delay removed so peaks land at true times. Fractional-delay kernel: length 33,
  Kaiser β = 8, its (L−1)/2 offset compensated.
- AX1: pre-roll `kAlignPreRollSamples`; earliest direct arrival at that sample; relative delays kept.
- AX4: ISO 9613-1 at 20 °C/50% RH; unit test vs table values ±5%.
- Directivity hook returns 1.0 (AQ8); direction-of-arrival and scattered-energy lists are output
  (Phases 04, 08, 09 depend on them).
- Benchmark printed in CI (order 30, 20×30×10 m, 48 kHz).
Traps: per-band levels test (α = 0.9 above 1 kHz, 0.1 below) within ±1 dB for orders 1–3;
truncation after last image + kernel length; O(N³) image count at order 60 not guarded.

## Phase 04 — Late tail + hybrid room IR

Reference: `room-acoustics.md`, `metrics-and-validation-data.md`.
Must contain: `sim/tail/Decay`, `MixingTime`, `NoiseTail`, `sim/Rng.h` (PCG32 or xoshiro, not
`std::mt19937` distributions), updated `buildRoomIR`, 6 new test rooms, goldens updated via
`update_goldens.py --reason`, CHANGELOG and §6 rows.
Verify:
- Eyring per band: `T60_b = 0.161·V / (−S·ln(1−ᾱ_b) + 4·m_b·V)`, ᾱ area-weighted, ᾱ clamped
  ≤ 0.999. **Units trap written into the phase file itself:** the `4mV` term needs the *energy*
  attenuation coefficient `m = a_dB/m / 4.343` (= 2 × the amplitude value in nepers/m). The phase
  text says "nepers/m", and converting with 1/8.686 halves the air term and lengthens HF T60.
  Check which one the code uses and that the T30-vs-Eyring test would see the difference (it only
  does at 4–8 kHz in large rooms, so make sure `concert_hall_box`/`stone_box` are in the test set).
  See `room-acoustics.md` §4.
- Envelope: amplitude envelope `exp(−6.91·t/T60)` (energy then decays 60 dB in T60). Classic bug:
  using 6.91 on energy or 13.8 on amplitude, which halves or doubles the measured T30.
- Mixing time `max(20 ms, √V ms)` clamped to the ISM's covered time; cite the source (Lindau,
  Kosanke, Weinzierl 2012 gives the regressions; √V ms is the Cremer/Müller echo-density rule).
- Energy matching at `t_mix` in a 10 ms window using the ISM band energy over
  `[t_mix − 10 ms, t_mix]` plus scattered energy; IR length to −90 dB in the slowest band, cap 12 s.
- Crossfade ISM → tail over 5 ms: the two signals are **uncorrelated**, so the amplitude gains
  must be power-complementary (cos θ / sin θ, i.e. cos² and sin² as *power* weights). Amplitude
  gains of cos²/sin² (a literal reading of the phase text) give a −3 dB energy dip at mid-fade, which
  the seam test (no EDC step > 1 dB) should catch only if its window is centred on `t_mix`.
  See `room-acoustics.md` §7.
- Determinism: same seed bit-identical twice in one test; different seed changes noise not T30
  (±2%); seed per emitter and per-output hook `seed ^ (outputIndex · 0x9E3779B9)`.
- Metrics: T30 within ±5% of Eyring (250 Hz–4 kHz), ±10% at 125 Hz and 8 kHz, 6 rooms; EDC
  monotonic with no step > 1 dB at the seam; 44.1 vs 96 kHz metrics within ±2%; open_field no tail;
  no NaN/Inf/denormal in any IR.
Traps: Gaussian noise generated with a library distribution (non-portable); filterbank not the
Phase 03 one; tail started at t = 0 and masked, versus started at t_mix (energy matching window
differs); envelope per band applied before the filterbank (then band leakage changes decay).

## Phase 05 — Validation against measured IRs

Reference: `metrics-and-validation-data.md` (BRAS section).
Must contain: `tools/validation/fetch_bras.py` with SHA-256 manifest and cache, mapping doc
`docs/validation/bras_mapping.md` written *before* code, validation scenes, `run_validation.py`,
generated `docs/validation/report-phase05.md` with EDC plots, `tests/golden/validation_baseline.json`,
nightly workflow (`schedule` + `workflow_dispatch`), A/B listening pack with `key.txt`.
Verify:
- Shoebox reduction rule is generic (match volume and surface area; area-weighted materials) and
  the same for every room; "as-documented" absorption is the primary run; fitted data is a
  secondary labelled run. Any per-room tweak is a blocker (NFR-8).
- Checksum test with a tampered file; report reproducible across two runs; the `MAKROOF_TEST_BIAS_T60`
  hook exists only in debug builds and makes the nightly fail.
- AQ9 pass/fail per scene printed; failing AQ9 does not fail CI but the reviewer states the
  result and checks that the status note says "AQ9 met in x/y scenes".
- No BRAS data committed; THIRD_PARTY attribution; licence terms respected (share-alike applies to
  derived data if redistributed, so nothing derived from BRAS ships in the plugin).
Traps: comparing simulated to measured without time alignment and level normalisation;
measurement noise floor shortening measured T30 (Lundeby); metrics averaged over the wrong bands
(AQ9 says 500 Hz–2 kHz); conclusions in the report not following from the table.

## Phase 06 — Real-time partitioned convolution + latency

Reference: `convolution-and-movement.md`, `realtime-audio-juce.md`.
Must contain: `sim/conv/Fft` (PFFFT wrapper), `PartitionedConvolver` (UPOLS, FDL), `IrSet`
built off-thread, `CrossfadingConvolver` with single-slot atomic mailbox and deferred release,
`RealtimeEngine` façade, denormal guard (x86 MXCSR, ARM FPCR), `tests/support/AllocationTracker`,
`render_cli --realtime-emulation --block <n|random>`, benchmark, PFFFT THIRD_PARTY row.
Verify:
- Null vs `OfflineRender` ≤ −120 dB for IR lengths 1, P−1, P, P+1, 48000, 144000 and host blocks
  1, 37, 64, 512, 2048 and random; latency exactly P + pre-roll measured with an impulse.
- Crossfade equals `(1−g)·(x*A) + g·(x*B)` within −100 dB with g a 30 ms linear ramp from the block
  boundary where the swap is picked up; latest-wins mailbox under 100 requests/s; no leak (ASan).
- Zero heap allocations in `process` for all block sizes including during crossfades; TSan clean
  with two threads hammering `requestIr`.
- PFFFT contract respected: N = 2^a·3^b·5^c with a ≥ 5 for real transforms, 16-byte aligned
  buffers from `pffft_aligned_malloc`, unordered layout only with `pffft_zconvolve_accumulate`,
  no built-in scaling (backward(forward(x)) = N·x). The marton78 fork has no release tags, so the
  pin must be a commit hash (and `GIT_SHALLOW` must then be dropped). Details and the fork's
  licence text requirement in `convolution-and-movement.md` §3 and `tooling-testing-licences.md`.
- The −120 dB residual criterion is only achievable if the reference (`OfflineRender`) and the
  convolver's MAC accumulate in double or pairwise: a 144 000-tap float32 direct convolution is
  itself only about −95 dB accurate, and float32 accumulation over ~280 partitions lands near
  −120 dB (`convolution-and-movement.md` §7). If the test passes with float32 everywhere, ask
  how, and check the residual measure (energy ratio over the whole signal vs. peak error).
- Both convolver states (A and B) must share the input FDL; otherwise the analytic crossfade null
  fails with a tail dropout. The ramp is time-domain, sample-accurate across host callbacks, and
  starts at the internal P-block boundary. With a 20 ms cadence and a 30 ms fade the engine is
  fading almost continuously under automation, so the benchmark must include the fading state
  (2× steady-state cost).
Traps: freeing an `IrSet` on the audio thread when the mailbox is overwritten; crossfade state
shared input history not reset; block accumulation adding latency that `latencySamples()` omits;
denormal guard restoring the wrong MXCSR / FPCR (x86 FTZ|DAZ = 0x8040; AArch64 FPCR bit 24);
one NaN in an input block poisons the output for the whole IR length (the NaN spectrum stays in
the FDL); allocation tracker counting Catch2's own allocations or not skipping under ASan/TSan;
benchmark run only in Debug or only with host block = P.

## Phase 07 — Plugin integration: parameters, state, scene → IR

Reference: `realtime-audio-juce.md`, `process-rules.md` §6.
Must contain: `module3d/SceneModel` (clamping setters, `toContract`), `module3d/ParameterMap`
(frozen IDs, normalized-in-room positions, skewed room ranges), APVTS, `IrBuilderThread`
(coalescing, ≤ 1 build / 20 ms), non-realtime synchronous path, `setLatencySamples` in
`prepareToPlay`, smoothed output trim, versioned state with full scene JSON and
`pluginStateVersion`, state fixtures `tests/state/v1_*.bin`, parameter freeze file
`tests/state/parameter_ids_v1.json`, default scene embedded.
Verify:
- Parameter IDs exactly the documented list; no `dry_wet`; `ParameterID` carries a version hint;
  ranges and skews documented; freeze test fails on any change.
- State: round trip gives bit-identical render; corrupt-state fuzz (1000 blobs) never crashes and
  ends in a valid scene with a warning flag; `setStateInformation` before `prepareToPlay` handled
  (Logic); sample-rate change without re-instantiation handled.
- Threading: who owns the scene; audio thread never waits; builder allocates, audio thread does not;
  non-realtime mode rebuilds synchronously *before* processing the block; TSan test present.
- Latency: first peak at exactly `getLatencySamples()` (emitter at minimum distance, α = 1);
  latency constant per sample rate.
- Boundary check still passes: `module3d` and `sim` meet only in `src/plugin`.
Traps: parameter listener doing work on the audio thread (APVTS callbacks can arrive from the
audio thread during automation); `juce::String`/`Logger` in `processBlock`; `std::shared_ptr`
copies on the audio thread; emitter push-away rule (0.3 m) not documented; room resize changing
absolute positions instead of keeping normalized ones (documented behaviour).

## Phase 08 — Binaural output with a generic HRTF (L)

Reference: `binaural-and-stereo.md`, `room-acoustics.md`.
Must contain: licence check first (`resources/hrtf/LICENSE-generic-v1.txt`, THIRD_PARTY row, CI
script failing if a `.bin` exists without it), `tools/hrtf/convert_sofa.py` (pinned deps,
checksum download, never commit SOFA), `resources/hrtf/generic-v1.bin`, `sim/hrtf/HrtfSet`
(barycentric interpolation on a stored spherical triangulation, onset-aligned HRIRs, separate ITD,
diffuse-field EQ switchable), `sim/binaural/ListenerFrame` (AX3), `BrirBuilder` (grouping above
order 3 only; two seeded tails mixed to target coherence), `buildRoomIR(Kind::Binaural)`,
`render_cli --mode binaural`, goldens, listening pack.
Verify:
- Licence verdict is explicit in the PR, quoting the dataset's terms; if unclear, the phase is
  `blocked`, not shipped. Verified 2026-11-04 (`binaural-and-stereo.md` §2): SADIE II is Apache
  2.0 with a citation requirement, so commercial redistribution of the converted binary is allowed
  with attribution; MIT KEMAR is "without any usage restrictions", citation requested; TH Köln
  KU100 is share-alike (avoid). The PR must still quote the licence text it read.
- Coordinate mapping SOFA (x front, y left, z up; azimuth counter-clockwise, 0° front, 90° left)
  ↔ project (x right, y forward, z up): `sofa = (y_p, −x_p, z_p)`, head-relative azimuth
  `atan2(−x_rel, y_rel)`, yaw applied as `R_z(−ψ)`. Stated once in code and docs; the azimuth sign
  convention is tested with +90° giving left-ear lead. Receiver 0 is left only if its
  `ReceiverPosition` y is positive: read it, do not assume the index. MIT KEMAR's raw azimuth is
  clockwise (90° = right), the opposite of SOFA.
- ITD 0.6–0.75 ms and ILD > 6 dB (2–8 kHz) at ±90°, mirrored; |ITD| < 20 µs and |ILD| < 1 dB ahead.
- Interpolation continuity: ≤ 1 dB level and ≤ 30 µs ITD per 1° step.
- Coherence within ±0.1 of the target per band; mixing `a = √((1+IC)/2)`, `b = √((1−IC)/2)`.
- Energy: binaural per-band energy (ear average, DFE'd) = omni ±1 dB; T30 per ear ±5% of omni.
- Converter round trip ≤ −60 dB; onset removal keeps ITD as a separate fractional value.
Traps: ITD applied twice (in the HRIR and as a delay); ears swapped (receiver index 0 is not
guaranteed left; check `ReceiverPosition`); DFE applied to the tail but not the early part;
grouping touching the direct path or orders 1–3; `Data.Delay` ignored; resampling changing the
tap count across sample rates inconsistently.

## Phase 09 — Stereo-speaker output mode

Reference: `binaural-and-stereo.md`.
Must contain: `sim/stereo/VirtualMicPair` (cardioid `0.5(1+cos θ)` in 3D, ±8.5 cm capsule delay via
the Phase 03 kernel), early accumulation reusing the Phase 08 structure, tail mixed to the analytic
ORTF diffuse coherence (formula documented), fixed loudness constant from the pair's diffuse-field
gain (not per-scene), `output_mode` parameter switching `Kind` through the crossfade, `render_cli
--mode stereoSpeakers`, goldens, listening pack, `pyloudnorm` pinned.
Verify: +55° gives max L−R with correct sign and mirror; centre emitter |L−R| < 0.1 dB and 0-sample
delay; 90° inter-channel delay = 17 cm / c = 0.496 ms ≈ 23.8 samples at 48 kHz (±1 sample);
coherence ±0.1 of the analytic target (closed form in `binaural-and-stereo.md` §8: the ORTF
diffuse-field coherence tends to 0.664 at low frequency, not 1.0, so a test expecting 1.0 at
63 Hz is wrong); LUFS difference ≤ 1 dB for 4 fixtures with the level constant derived from the
cardioid random-energy efficiency of 1/3 (−4.77 dB); mono sum notch ≤ 6 dB below 2 kHz; 10 mode
switches with 0 clicks.
Traps: capsule delay sign reversed (left capsule should lead for a left source); cardioid evaluated
with azimuth only (phase file says full 3D direction); per-scene auto-gain sneaking in as "level
match" (AX2 forbids); loudness test on a signal shorter than BS.1770 gating needs.

## Phase 10 — Artifact-free movement under automation

Reference: `convolution-and-movement.md`, `realtime-audio-juce.md`, `metrics-and-validation-data.md`.
Must contain: `render_cli --automation` in `--offline` and `--realtime-sim` (simulated clock),
tail cache keyed by (dimensions, materials, mode, seed, sample rate), coalescing scheduler with
staleness metric, `MAKROOF_TEST_HARD_SWITCH` negative control (test builds only), 20 scenarios in
`tests/automation/`, CI job `automation` on 3 OSes.
Verify: 0 click events over 20 scenarios × 2 modes × 2 timing modes; negative control flagged in
≥ 18/20; offline bit-identical across runs; static scene offline vs realtime-sim ≤ −120 dB; tail
cache equals full rebuild ≤ −120 dB; worst staleness ≤ 100 ms at order 20 and the job fails
otherwise; no allocation in `processBlock` during scenarios; pluginval passes.
Traps: cache key missing an input that affects the tail (sample rate, per-band materials and
scattering, air-absorption constant, reflection order / crossover time, tail length cap, seed and
per-output offset, output mode and HRTF set, contract version; compared bit-exactly, and energy
matching never cached with the tail); negative control bypassing the same code path (it must
replace only the fade); realtime-sim clock derived from wall time (non-reproducible); staleness
budget arithmetic (cadence wait ≤ 20 + build + pickup ≤ P/fs + fade queue ≤ 30 ms leaves ~40 ms
for the build against the 100 ms criterion, see `convolution-and-movement.md` §5); comb-filter
colouration during fades grows with the change in relative path length, so a scenario with a
large corner-to-corner jump is the one most likely to show artefacts the click detector cannot
see; 40 Hz tone scenario and low-band detector variant noted if added.

## Phase 11 — Minimal placement UI

Reference: `realtime-audio-juce.md` (message-thread rules, gestures).
Must contain: `src/plugin/ui/` components (top and side views, drag with
`beginChangeGesture`/`endChangeGesture`, room panel, surfaces panel with material dropdown and
advanced α/s table, output panel, status strip), `EditorController` (only pixel↔metre converter,
headless-testable), `sim::describeScene` as the only sim access, resizable editor with remembered
size, generic editor removed.
Verify: drag tests ±1e-4 normalized in both views; clamping equals `SceneModel`; gestures begin and
end exactly once per drag; out-of-range α rejected with the validator's message; undo/redo restores
identical JSON; snapshot renders at 3 sizes non-blank; off-message-thread mutation trips an
assertion in a test; pluginval with editor tests on 3 OSes; state round trip still bit-identical
with editor size restored.
Traps: UI code including `src/sim` headers beyond `describeScene`; parameter writes without
gestures (breaks automation recording); material edits as host parameters (phase says no); DPI
scaling on Windows; `AudioProcessorEditor` holding references to processor state read off the
message thread.

## Phase 12 — Material library + starter presets

Reference: `room-acoustics.md` (material data), `process-rules.md` §4 (NFR-8).
Must contain: `resources/materials.json` (25–40 entries, 8-band α, s, category, citation, header
documenting the 63 Hz/8 kHz extrapolation rule), `module3d/MaterialLibrary`, 8 presets as full
valid scenes with `extensions.preset`, preset browser (undoable), `resources/presets/README.md`
with expected T30 ranges, THIRD_PARTY rows for data sources.
Verify: every preset validates (C++ and schema) and renders both modes without NaN/Inf; grep test
finds no preset name, material ID or `preset` in `src/sim/`; preset through UI path renders
bit-identically to the same JSON with `extensions` stripped; T30 (500 Hz–1 kHz) inside each
documented range; every material has a citation and in-range values; preset load undoable; state
round trip bit-identical.
Traps: scenes storing material IDs instead of numbers (contract must be self-contained); α values
copied from tables that give energy absorption at 125 Hz–4 kHz only, extrapolated silently;
`open_air` surfaces with α = 1 but non-zero scattering; a wholesale copy of a database with
restrictive terms.

## Phase 13 — v1 hardening: performance, DAW matrix, signing

Reference: `realtime-audio-juce.md`, `tooling-testing-licences.md`.
Must contain: profiling notes `docs/perf/v1.md`, universal macOS binary with both slices tested,
robustness tests (10 instances, sample-rate/buffer change, 0- and 1-sample blocks, 60 s silence,
bypass latency, all state fixtures, cross-architecture residual ≤ −100 dBFS), `release.yml`
(secret-gated signing and notarization, Inno Setup, version from tag), complete THIRD_PARTY and
`THIRD_PARTY_NOTICES.txt`, JUCE tier confirmed in §6, `docs/compat/v1.md` skeleton, AX8 identity
confirmed.
Verify: AQ10 met or quantified; optimizations change acoustic output by ≤ −100 dB (null test
against pre-optimization renders); pluginval on the release build, both macOS slices; notarization
`spctl -a -vv -t install` accepted on a test tag or "signing pending secrets" recorded.
Traps: an optimization that changes summation order and silently breaks AX5 determinism;
`-ffast-math`/`/fp:fast` enabled globally; secrets echoed in logs; splash-screen setting changed
without the licence tier recorded; identity codes changed after state fixtures exist.
