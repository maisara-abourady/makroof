# Phase 13 — v1 hardening: performance, DAW matrix, signing

Size: **M** (L if notarization or optimization fights back; split into 13b) · Depends on: 00–12, including 05b, 05h, 07c (`done`, or the versioning fallback of scope 13 recorded), 05d, 05e and 05f (05f `done` or Maisara's recorded acceptance of the two-room label; 05d `done` or `blocked (reason)`, decider report 15, accepted by Maisara, 2026-11-05; with 05c, if it exists, `blocked` only on Maisara's recorded decision) · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` (all of §2–§3), PRD NFR-2, NFR-4, NFR-6

## Raise with Maisara (she does not track these herself)

The session raises each item in its **first message** and again before the beta decision.

1. **Commissioning decision (BUILD_PLAN §3 F2).** Check BUILD_PLAN §6 for Maisara's answer, recorded by
   phase 05d. If it is missing or "deferred", put the question to her again with the Phase 05/05d
   numbers before the beta decision.
2. **DELTA panel report.** Check whether `docs/phases/phase-05d.md`'s PR recorded an answer. If not,
   remind her that the request (`docs/review/drafts/delta-report-request.md`) is still outstanding, and
   keep the Arni provenance label as is in the beta wording.
3. **Load time with 8 instances (AX38 (iv), phase 05b).** If the recorded time until the last of 8
   instances is audible at project load at 100 m exceeds 10 s, it goes to Maisara before the first
   release.
4. **Phase 07c not landed (conditional).** If the asynchronous diffuse solve (phase-07c) would land after
   the first release without the estimator parameters versioned in saved state, Seat 7's condition fails
   and the item returns to Maisara (decider file 47 §4, strongest objection).

## Goal

Turn the vertical slice into a **private-beta build**: meet the performance budget, survive real-world
host behaviour, install cleanly on macOS and Windows, and get every licence in order. (Licensing and
subscriptions are deliberately not in v1; see BUILD_PLAN F9 and B1.)

## Assumptions in force

- **AQ10** budget (partition P ≤ 512 samples at 48 kHz; reported latency P + 32 = 544 samples (11.3 ms)
  at the default P = 512 (phase-06b D1); ≤ 15% of one core per instance for a 3 s tail;
  IR rebuild ≤ 50 ms for the AQ10 workloads W1 and W2 (position-only), in every output mode
  (decider report 8, accepted by Maisara, 2026-11-05)). **AX5**: the definition of "exactly as saved" across machines.

## Scope

1. **Profiling and optimization** against AQ10 on macOS arm64 and Windows x64 (profile with Instruments /
   VTune or Superluminal; record findings in `docs/perf/v1.md`). Allowed optimizations: SIMD in
   accumulation loops, image-source grouping parameters, tail-cache hit rate, partition size choice. Not
   allowed without a new AX entry: anything that changes the acoustic output beyond −100 dB, and
   non-uniform partitioning (if needed, make it 13b). Measured motivation (Phase 06, PR #14, CI run
   42355829013; 2×2, 48 kHz, host buffer 512, mean % of the real-time budget, steady / crossfading):
   12 s IR at P = 512: macOS 7.3 / 14.0, Linux 11.7 / 26.0, Windows 9.1 / 26.2; 12 s IR at P = 256: up
   to 59 % while crossfading (Linux/Windows). AQ10 budgets only a 3 s IR (P = 512: 1.6–2.1 % steady,
   3.3–4.1 % crossfading), so no current criterion needs it; Maisara chose to plan it, not build it
   (2026-11-07). Further inputs (Phase 07 follow-up, PR #23, CI run 42465826545, release build, best of
   3): full rebuild (scene → `buildRoomIR` → `IrSet`, tail noise generation included), default / maximum
   room (100 × 100 × 100 m), at 48 kHz: Linux 183.6 / 752.1 ms, macOS 132.7 / 801.9 ms, Windows
   141.8 / 603.0 ms; at 96 kHz: Linux 392.4 / 1883.7 ms, macOS 278.6 / 1832.1 ms, Windows
   295.2 / 1509.1 ms. RSS per instance at 96 kHz, maximum room: +122.6 MB (Linux only; the pipeline
   keeps the last built and the last submitted `RoomIR`/`IrSet`). Measure memory per instance on all
   three OSes and report it in `docs/perf/v1.md`; any memory budget is a decision for this phase (no
   number is set here). Input since phase 05b: AX38's working ceiling for the diffuse computation (≤ 1 GB
   transient per solve, one solve per process; ≤ 128 MB additional resident per instance) and its records.
2. **macOS universal binary** (arm64 + x86_64) via `CMAKE_OSX_ARCHITECTURES`. Test both slices in CI (the
   x86_64 slice runs through Rosetta on the arm64 runner).
3. **Robustness tests** (Catch2 + pluginval options):
   - 10 instances in one process, all processing; the CPU sum is recorded. Multi-instance RSS is recorded
     on three OSes, including Bitwig's per-plugin sandbox, where the AX38 transient counts per instance.
   - Sample-rate change at runtime (44.1 ↔ 96 kHz) and buffer-size change without re-instantiation.
   - `processBlock` with 0-sample and 1-sample buffers, and with silence for 60 s (CPU must not spike;
     denormals off).
   - Bypass (`processBlockBypassed`) keeps the latency constant and outputs a delayed dry signal.
   - Load every state fixture from Phases 07–12 (`tests/state/`).
   - Cross-architecture determinism (AX5): render the reference projects on arm64 and x86_64; the
     residual is ≤ −100 dBFS (compare CI artifacts in a final job).
4. **Release packaging** (`.github/workflows/release.yml`, on tags `v*`):
   - macOS: codesign with Developer ID Application (hardened runtime), build a signed `.pkg` installer
     (VST3 + AU), **notarize** with `notarytool`, and staple. Secrets: `APPLE_DEV_ID_CERT_P12`,
     `APPLE_DEV_ID_CERT_PASSWORD`, `APPLE_NOTARY_KEY_ID`, `APPLE_NOTARY_ISSUER`,
     `APPLE_NOTARY_KEY_P8`, set by Maisara in GitHub repository secrets. The workflow skips signing with a
     clear message if they're absent.
   - Windows: Inno Setup installer for the VST3. Code signing is optional (secret-gated); document the
     SmartScreen warning if unsigned.
   - Version number from the git tag, embedded in the plugin (`JucePlugin_VersionString`) and shown in the UI.
5. **Licences and attribution:** `docs/THIRD_PARTY.md` complete (JUCE tier and terms, PFFFT,
   nlohmann/json, dr_wav, Catch2 (test only), HRTF dataset, material sources, BRAS, Arni and dEchorate (validation only,
   not shipped)). The installer includes `THIRD_PARTY_NOTICES.txt`. **Confirm the JUCE licence tier
   that will apply at commercial launch**, and the splash-screen and revenue-cap rules for that tier,
   recording it in BUILD_PLAN §6.
6. **DAW compatibility matrix:** `docs/compat/v1.md` table: rows = DAW + OS + format (Logic/AU, Ableton
   macOS VST3, Reaper macOS VST3, Windows DAW(s) VST3); columns = load, play, automate, editor drag-record,
   offline bounce, reopen project, sample-rate change, 10 instances. Maisara fills it in. The public
   compatibility notes state the Bitwig sandbox gap (AX38 (i)) until scope 3 has measured it. **The
   matrix also receives the per-host trace results of phase-07c §5 condition 11** (D-H3 (e), AX38 (i)
   half (2): the thread that serves `reset()`, `setNonRealtime` and freeze / offline render, per host and
   situation, from the `SPATIAL_HOST_TRACE` build run as a person's action); they are evidence for the
   compatibility notes, never a per-host code path (NFR-8). Until measured, the notes carry AX38 (i)'s
   interim sentence (no host named, no stall figure as a product promise, not in launch copy).
7. Placeholder identity (`AX8`: company name, plugin/manufacturer codes, bundle ID) confirmed or changed
   **before** the first beta, since changing it later breaks users' projects.
8. **Flush-to-zero guard for MSVC on ARM64** (Windows on Arm): `sim/conv/Denormals.h` is a no-op there;
   implement with `_ReadStatusReg`/`_WriteStatusReg` (FPCR.FZ) together with an ARM64 Windows CI runner
   that can test it (Phase 06 follow-up). Until then **Windows-on-ARM runs unguarded**: the guard is a
   no-op on MSVC ARM64, so the AX37 (5.1) (i) guard and the phase-05h pool-worker guard do not apply there
   and the `[pipeline]` FTZ test SKIPs (D-H3 (c), decider files 20, 25; the public compatibility notes say
   so until this scope lands).
9. **Small-buffer callback timing on real macOS hardware** (Phase 06 follow-up, brief
   `docs/sessions/2026-11-07-phase-06-followups.md` O3(b)): with the Phase 06 work spreading (AX31), the
   worst callback at host buffer 64, 12 s IR, P = 512, while crossfading must stay under its real-time
   budget (p99.9 < 100 %). CI measured it below the target on Linux (wall 66.6 %, thread-CPU 65.9 %, run
   42397114233) and Windows (wall 32.2 %, same run), but could not show it on the shared macOS runner:
   wall p99.9 75.5 % (run 42390056623), 609 % (42392204088), 161.8 % (42394370942) and 657.4 %
   (42397114233), with thread-CPU p99.9 109.9 % in 42397114233 (most of the wall overshoot is the runner
   taking the thread off the CPU). Measure it on an Apple-silicon Mac with the `[benchmark]` test (it
   prints wall and thread-CPU p99.9 per case); if it misses, the remedy is non-uniform partitioning
   (new AX entry, 13b, per scope 1) or another scope 1 optimisation that leaves the output unchanged
   within −100 dB (e.g. SIMD in the accumulation loops), not P = 256 (it raises convolution work per
   sample 1.5–2.1×, run 42397114233, host 512) and not a change to the target (phase-06b D1).
10. **End treatment at the 12 s cap** (Phase 07 D3). Answer first: (Q1) audibility threshold of a
    rectangular cut at a given remaining decay depth, per band, for music; (Q2) fade length that removes
    cut artefacts without shortening the perceived decay; (Q3) CPU and memory of a 20–30 s cap at
    96 kHz. Then choose: keep the cut; an end fade (new AX, goldens via update_goldens.py, §6 row); or a
    longer cap.
11. **AX34:** decide whether to add internal resampling for unsupported rates (quality verifiable),
    replacing the bypass-like fallback (Phase 07 D8).
12. **Cache the pinned pluginval release in CI** (`actions/cache`, keyed on the pinned version and its
    checksum) so that a GitHub Releases outage cannot fail CI (Phase 07 follow-up: CI run 42465826545
    attempt 1 failed only at the pluginval download, HTTP 504 on all three runners). May be pulled
    forward as a standalone tooling change before Phase 13.
13. **Diffuse-estimator work limits and the restore (AX41, AQ10 amended 2026-11-10, phase 05b):**
    re-check W_max (provisional 3.05 M image evaluations per emitter, sized to pluginval's restore
    watchdog less D-H1's margin; re-derived once under phase-07c; board answer, decider files 43, 47, 51) and n\*_max (1 024, sized to 25 ms of the W1 target) on the release machines; any change is
    an output change (golden round, §6 row) and must be fixed before the first release. Q2a (C), moving the
    diffuse solve off the synchronous restore, prepare and `reset()`, is its own phase,
    [`phase-07c.md`](phase-07c.md) (board answer, decider files 47 §4 (iii), 51 §4 items 4 and 8): **it is a
    prerequisite for the beta**; if it has not landed, the estimator parameters are versioned in saved
    state before release.
    **Accuracy wording (AX43, D-H3 (a) / H3-F1, 2026-11-10; decider file 27, interrogator file 28; Seat
    7's (f9) sentence):** the copy is written from the agreement suite's printed lines and quotes the
    per-case line (τ, the max |C++ − ref|) and the CHECKed pooled figure in this form: "Across the N
    certified test cases the average offset from the reference is <mean signed deviation> dB (<x> %),
    inside the references' own resolution (about <mean ℓ_ref> dB) plus three standard errors", with N
    from the '<gated> of 560' line and the printed bound; never the as-written or per-room numbers as a
    pass/fail, never "no bias" bare, never "validated" (AX39, AX43). Where its tail level is only
    reported (reference pending), a room is not counted.

## Out of scope

Licensing/trial (B1), auto-update, anything listed in BUILD_PLAN §5.

## Acceptance criteria — automated

- [ ] Full CI matrix green; nightly validation green (no regression).
- [ ] Benchmarks: AQ10 met on the macOS runner and Windows runner, or the miss is quantified in the status
      notes, with the effective update interval max(30 ms, rebuild) and the worst staleness, together
      with a proposal that does not change the output beyond −100 dB. Raising N_cap with time freed by
      optimisation is an intended output change, proposed through /fix-plan (decider report 8, accepted by Maisara, 2026-11-05). Re-derive the
      AX22 i₀ after optimisation if AX22 records 'cap limits accuracy'.
- [ ] Robustness tests above pass, including cross-architecture ≤ −100 dBFS residual.
- [ ] pluginval strictness 10 on the **release** build, 3 OSes (both macOS slices). auval passes.
- [ ] Release workflow on a test tag produces: notarized and stapled pkg (`spctl -a -vv -t install` says
      accepted), Windows installer, notices file. (If secrets are missing, the workflow produces unsigned
      builds and the phase status notes say `signing pending secrets`.)

## Listening / manual checklist (Maisara)

- [ ] Install from the macOS pkg on a clean-ish Mac: no Gatekeeper warnings; Logic finds the AU.
- [ ] Install on Windows: the DAW finds the VST3.
- [ ] Fill in `docs/compat/v1.md` completely.
- [ ] A final listening pass through all presets in both modes on the Adam monitors and headphones,
      plus a real session with 10 instances on stems. Note CPU in your DAW's meter.
- [ ] Decide: is this build good enough to give to 3–5 beta users? The decision lists 'AQ9 met in x/y'
      and every recorded known deficit (AX16, AX21, AX22, AQ10 misses) (decider report 8, accepted by Maisara, 2026-11-05). It also
      states (BUILD_PLAN §3 F2; decider report 15, accepted by Maisara, 2026-11-05): "Second measured
      source: Arni (202 m³) and dEchorate (86 m³), CC BY 4.0, used in phase 05d. No open dataset has
      measured α for all surfaces; all measured comparisons (BRAS, Arni, dEchorate) are evidence, not
      validation of NFR-1. Input-matched distribution test: [result]. Coverage: domestic small room (one
      treated empty cuboid, dEchorate 86 m³), mid rooms 145 m³ (BRAS CR2) and 202 m³ (Arni), halls
      2 350/8 650 m³ (BRAS); none for outdoor, cars or furnished living rooms." The coverage sentence is
      corrected by decider report 16 (`docs/review/phase-04-consult/18-decider-05d-choices.md`), accepted
      by Maisara, 2026-11-05. Your decision goes in BUILD_PLAN §6.

## Contractor review focus

Optimization diffs (no acoustic changes beyond −100 dB), threading under multi-instance load, the release
pipeline's secret handling, and licence compliance.

## Risks

Apple developer account and notarization logistics; JUCE licence tier cost at launch; Windows signing cost.

## Definition of done

All automated criteria green (or signing explicitly pending secrets); compat matrix filled in; status row
13 `done`; the v1 beta decision is recorded.
