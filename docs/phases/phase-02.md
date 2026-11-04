# Phase 02 — Offline render CLI + acoustic analysis harness

Size: **M** · Depends on: 01 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ9), PRD NFR-1, `docs/contract/README.md`

## Goal

Build the **measuring instruments before the DSP**. After this phase, every later phase can prove its
behaviour with an offline render plus an automatic measurement: room metrics, IR comparison, click
detection and golden comparison. It also produces a downloadable listening pack. Maisara can't verify
DSP by reading code, so these tools are the main way the project gets verified.

## Assumptions in force

- **AQ9**: the accuracy thresholds the tools will later check. This phase only builds and self-tests
  the tools. It doesn't apply thresholds to the engine.

## Scope

### C++: `render_cli` and the engine interface

1. `src/sim/Engine.h` — the stable offline API later phases implement:
   ```cpp
   namespace sim {
   struct RoomIR { double sampleRate; int numEmitters; int numOutputs; // v1: 2 x 2
                   std::vector<std::vector<float>> taps; /* [emitter*numOutputs+out] */ };
   struct BuildOptions { double sampleRate; enum class Kind { Omni, Binaural, StereoSpeakers } kind; };
   RoomIR buildRoomIR(const contract::SceneDescription&, const BuildOptions&);
   }
   ```
   In this phase `buildRoomIR` is a **stub**: emitter L → output 0 and emitter R → output 1, each a unit
   delta at t=0 (dry pass-through). Document it as a stub.
2. `src/sim/OfflineRender.h/.cpp` — direct (time-domain or simple FFT) convolution of an input
   buffer with a `RoomIR`. Correctness over speed: this is the **reference renderer** that the
   real-time convolver (Phase 06) is compared against.
3. `src/cli/main.cpp` — `render_cli`:
   - `--scene <json> --in <wav> --out <wav> [--rate <hz>] [--mode omni|binaural|stereoSpeakers]`
   - `--scene <json> --ir <wav>` writes the IR (channels = emitter×output, float32 WAV).
   - `--automation <json>` (accepted but rejected with "not implemented until Phase 10" for now).
   - Exit codes: 0 ok, 2 invalid scene (prints validation errors), 3 I/O error.
   - WAV I/O: use `dr_wav` (public domain/MIT-0, single header, pinned) so the CLI stays JUCE-free.
4. Catch2 test: stub render of random stereo input is bit-identical to the input.

### Python: `tools/acoustics/` package (pytest)

Pin versions in `tools/acoustics/requirements.txt` (numpy, scipy, soundfile, pyroomacoustics, pytest).

1. `signals.py` — generators: pink-noise bursts, single-sample clicks, exponential sine sweep +
   inverse filter (Farina), sustained tones (sum of 110, 220, 330 Hz sines at −12 dBFS), and synthetic
   decays (white noise × exp envelope with known per-band T60).
2. `bands.py` — octave-band filterbank (zero-phase Butterworth, order 6, centres 63 Hz–8 kHz,
   matching `contract::kOctaveBandsHz`).
3. `metrics.py` — ISO 3382-1: Schroeder backward integration (with noise-floor compensation per
   Lundeby's method), EDT, T20, T30 (linear regression on EDC), C50, C80, D50, DRR, all per band.
   Returns JSON-serialisable dicts.
4. `compare.py` — compare two IRs: arrival-time detection of the first N peaks (matched-filter peak
   picking), per-peak amplitude difference in dB, per-band energy difference, metric deltas.
5. `clicks.py` — click/discontinuity detector for **sustained-tone** inputs: high-pass the output at
   2 kHz (8th-order Butterworth, zero-phase), compute RMS in 2 ms frames, flag frames whose HF energy
   exceeds the stationary baseline (median of all frames) by more than `threshold_db` (default 20 dB)
   and above an absolute floor of −90 dBFS. Returns event times. Document why it works: an LTI or
   slowly varying system driven by low tones produces no HF energy, while a click is broadband.
6. `golden.py` — compare a metrics dict against `tests/golden/<name>.json` with per-metric tolerances
   stored in the golden file; update mode is only via `tools/ci/update_goldens.py --reason "<text>"`,
   which appends the reason to `tests/golden/CHANGELOG.md`.
7. `cli.py` — `python -m tools.acoustics metrics ir.wav`, `... compare a.wav b.wav`, `... clicks out.wav`.

### Listening pack

`tools/ci/listening_pack.py` — renders a fixed set of test signals (pink bursts, clicks, sweeps, tones)
and any user-supplied WAV in `tools/ci/listening_inputs/` (gitignored) through each scene in
`tests/scenes/valid/` using `render_cli`. Writes to `build/listening-pack/<phase>/` with a
`README.txt` explaining what each file should sound like. CI uploads it as artifact `listening-pack`.

### CI

Add a `python` job (Linux) that installs requirements, runs `pytest tools`, then builds `render_cli`
and produces the listening pack. The C++ tests remain in the matrix jobs.

## Out of scope

Any real acoustics: ISM is Phase 03, tail is Phase 04. Real-time convolution is Phase 06.

## Deliverables

`src/sim/Engine.*`, `src/sim/OfflineRender.*`, `src/cli/main.cpp`, `tools/acoustics/**`,
`tools/ci/listening_pack.py`, `tools/ci/update_goldens.py`, `tests/golden/CHANGELOG.md`, CI job.

## Acceptance criteria — automated

- [ ] `metrics.py` recovers T30 of synthetic decays (T60 = 0.3, 1.0, 2.5, 6.0 s, 48 kHz) within
      **±2%** in every band 125 Hz–8 kHz, and within ±5% at 63 Hz.
- [ ] `metrics.py` agrees with `pyroomacoustics.experimental.measure_rt60` within ±5% on the same
      synthetic decays (second opinion).
- [ ] C80 of a synthetic delta-plus-decay matches the analytic value within ±0.2 dB.
- [ ] `clicks.py` flags **100%** of 200 randomly placed single-sample discontinuities (step sizes
      −60…−6 dBFS) injected into the sustained tone, and gives **0** false positives on 60 s of the
      clean tone and on the tone with a slow 0.5 Hz ±6 dB amplitude modulation.
- [ ] `compare.py` detects the arrival times of a synthetic 20-spike IR to ±0 samples.
- [ ] `render_cli` stub render is bit-identical to the input (Catch2 and a pytest end-to-end test).
- [ ] `render_cli` returns exit code 2 with readable errors for every invalid fixture.
- [ ] Listening-pack artifact is produced in CI.

## Listening / manual checklist (Maisara)

Download the `listening-pack` artifact from the PR's CI run.
- [ ] Files play; each test signal matches its description in `README.txt` (bursts, clicks, sweep, low hum).
- [ ] Rendered files sound **identical** to the dry signals (this phase's engine is a stub).

## Contractor review focus

Correctness of the ISO 3382 implementation (Lundeby truncation, regression ranges), click-detector
thresholds and its blind spots, and whether the reference renderer is truly independent of the
future real-time path.

## Risks

- Metric bugs would make every later gate meaningless. That's why they're tested against known
  analytic answers and against pyroomacoustics.
- Low-band (63 Hz) estimates are noisy in short decays. Tolerances there are looser on purpose.

## Definition of done

All automated criteria green; status row 02 `done`; PR includes the checklist and artifact link.
