# Phase 13 — v1 hardening: performance, DAW matrix, signing

Size: **M** (L if notarization or optimization fights back; split into 13b) · Depends on: 00–12, including 05b (with 05c, if it exists, `blocked` only on Maisara's recorded decision) · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` (all of §2–§3), PRD NFR-2, NFR-4, NFR-6

## Goal

Turn the vertical slice into a **private-beta build**: meet the performance budget, survive real-world
host behaviour, install cleanly on macOS and Windows, and get every licence in order. (Licensing and
subscriptions are deliberately not in v1; see BUILD_PLAN F9 and B1.)

## Assumptions in force

- **AQ10** budget (latency ≤ 512 samples at 48 kHz; ≤ 15% of one core per instance for a 3 s tail;
  IR rebuild ≤ 50 ms for the AQ10 workloads W1 and W2 (position-only), in every output mode
  (decider report 8, accepted by Maisara, 2026-11-05)). **AX5**: the definition of "exactly as saved" across machines.

## Scope

1. **Profiling and optimization** against AQ10 on macOS arm64 and Windows x64 (profile with Instruments /
   VTune or Superluminal; record findings in `docs/perf/v1.md`). Allowed optimizations: SIMD in
   accumulation loops, image-source grouping parameters, tail-cache hit rate, partition size choice. Not
   allowed without a new AX entry: anything that changes the acoustic output beyond −100 dB, and
   non-uniform partitioning (if needed, make it 13b).
2. **macOS universal binary** (arm64 + x86_64) via `CMAKE_OSX_ARCHITECTURES`. Test both slices in CI (the
   x86_64 slice runs through Rosetta on the arm64 runner).
3. **Robustness tests** (Catch2 + pluginval options):
   - 10 instances in one process, all processing; the CPU sum is recorded.
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
   nlohmann/json, dr_wav, Catch2 (test only), HRTF dataset, material sources, BRAS (validation only,
   not shipped)). The installer includes `THIRD_PARTY_NOTICES.txt`. **Confirm the JUCE licence tier
   that will apply at commercial launch**, and the splash-screen and revenue-cap rules for that tier,
   recording it in BUILD_PLAN §6.
6. **DAW compatibility matrix:** `docs/compat/v1.md` table: rows = DAW + OS + format (Logic/AU, Ableton
   macOS VST3, Reaper macOS VST3, Windows DAW(s) VST3); columns = load, play, automate, editor drag-record,
   offline bounce, reopen project, sample-rate change, 10 instances. Maisara fills it in.
7. Placeholder identity (`AX8`: company name, plugin/manufacturer codes, bundle ID) confirmed or changed
   **before** the first beta, since changing it later breaks users' projects.

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
      states whether a second measured dataset beyond BRAS was found and used (BUILD_PLAN §3 F2; BRAS
      results are evidence, not validation) (decider report 11, accepted by Maisara, 2026-11-05). Your decision goes in BUILD_PLAN §6.

## Contractor review focus

Optimization diffs (no acoustic changes beyond −100 dB), threading under multi-instance load, the release
pipeline's secret handling, and licence compliance.

## Risks

Apple developer account and notarization logistics; JUCE licence tier cost at launch; Windows signing cost.

## Definition of done

All automated criteria green (or signing explicitly pending secrets); compat matrix filled in; status row
13 `done`; the v1 beta decision is recorded.
