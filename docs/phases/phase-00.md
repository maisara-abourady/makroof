# Phase 00 — Scaffolding, CI, pluginval, empty plugin

Size: **M** · Depends on: nothing · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §0–§1

## Goal

A stereo **pass-through** plugin (`SpatialScene`) that builds as VST3, AU (macOS) and Standalone
on Linux, macOS and Windows, passes pluginval in CI, and loads in a DAW. This phase lays the
foundation every later phase relies on: the build system, library layout, test runner and CI matrix.

## Context

- Product: a spatial audio plugin (see PRD overview). There's no DSP in this phase.
- Framework: **JUCE 8**, pulled by CMake `FetchContent` at a **pinned release tag** (use the latest
  8.0.x tag available at the time; record it in `docs/THIRD_PARTY.md`).
- Architecture (BUILD_PLAN §1): five targets with a hard boundary between `sim` and `module3d`.

## Scope

1. **CMake project** (`CMakeLists.txt`, `cmake/` helpers), C++20, Ninja.
   - `CMakePresets.json` with configure/build/test presets: `debug`, `release`, `asan` (Linux,
     ASan+UBSan), `tsan` (Linux). The binary dir is `build/<preset>`.
   - Warnings: `-Wall -Wextra -Wpedantic` (Clang/GCC), `/W4` (MSVC); warnings as errors when
     `SPATIAL_WERROR=ON` (CI sets it).
   - JUCE options: `JUCE_WEB_BROWSER=0`, `JUCE_USE_CURL=0`, `JUCE_VST3_CAN_REPLACE_VST2=0`,
     `JUCE_DISPLAY_SPLASH_SCREEN` left at the JUCE default (licence check happens in Phase 13).
2. **Targets (skeletons):**
   - `spatial_contract` — static lib, no JUCE. One placeholder header/source (`contract/Version.h`
     with `constexpr const char* kContractVersion = "0.0";`).
   - `spatial_sim` — static lib, no JUCE, links `spatial_contract` only.
   - `spatial_module3d` — static lib, no JUCE, links `spatial_contract` only.
   - `SpatialScene` — `juce_add_plugin` with formats `VST3 AU Standalone` (AU only on Apple),
     `PLUGIN_MANUFACTURER_CODE Mkrf`, `PLUGIN_CODE Spsc`, `COMPANY_NAME "Makroof"`,
     `BUNDLE_ID com.makroof.spatialscene`, `IS_SYNTH FALSE`, stereo in / stereo out only
     (`isBusesLayoutSupported` accepts only stereo→stereo), `processBlock` copies input to output.
     The generic editor is enough. Links all three libs. (Company name, codes and bundle ID are
     the placeholders recorded as `AX8` in BUILD_PLAN §2.)
   - `render_cli` — console executable, links `spatial_contract` + `spatial_sim`; prints version and
     exits 0 for now.
   - `spatial_tests` — Catch2 v3 (pinned via FetchContent), registered with CTest via
     `catch_discover_tests`.
3. **Tests (Catch2):**
   - `tests/unit/test_smoke.cpp`: contract version string is non-empty.
   - `tests/unit/test_passthrough.cpp`: instantiate the `AudioProcessor` headless
     (`juce::ScopedJuceInitialiser_GUI`), `prepareToPlay(48000, 512)`, process 10 blocks of random
     stereo noise, and assert output == input **exactly** (null test). Repeat at 44.1/96 kHz and
     buffer sizes 1, 64, 2048. This test links the plugin's shared code target (`SpatialScene`
     produces `SpatialScene` shared code lib with JUCE).
4. **Formatting:** `.clang-format` (based on LLVM, 4-space indent, 110 cols) and a CI step that
   fails on unformatted files (`clang-format --dry-run --Werror`).
5. **CI** — `.github/workflows/ci.yml`, triggered on push and PR:
   - Matrix `ubuntu-24.04`, `macos-14`, `windows-2022`; preset `release` for the build used by pluginval,
     plus `debug` for the tests.
   - Linux installs the apt deps listed in `CLAUDE.md`; Windows uses MSVC via
     `ilammy/msvc-dev-cmd` (pin a version) + Ninja.
   - Cache FetchContent downloads (`actions/cache` on `build/_deps` keyed on `CMakeLists.txt` hash)
     and use `ccache`/`sccache` if it's simple to set up.
   - Steps: configure → build → `ctest --output-on-failure` → **pluginval** → upload artifacts
     (VST3 and AU bundles, Standalone) named `SpatialScene-<os>`.
   - pluginval: `tools/ci/run_pluginval.sh` (bash, used on all OSes via Git Bash on Windows)
     downloads a **pinned** pluginval release from `github.com/Tracktion/pluginval/releases` for the
     OS, then runs `--strictness-level 10 --validate-in-process --output-dir <dir> <plugin>`. On
     Linux, wrap in `xvfb-run -a`. Upload the pluginval log as an artifact.
   - macOS AU: copy `SpatialScene.component` to `~/Library/Audio/Plug-Ins/Components/`, run
     `killall -9 AudioComponentRegistrar || true`, then `auval -v aufx Spsc Mkrf`. Fail the job if
     auval fails.
   - Separate Linux job running the `asan` preset tests.
   - Separate job: `clang-format` check.
6. **Docs:** `docs/THIRD_PARTY.md` (JUCE, Catch2, pluginval with versions and licences);
   confirm the build commands in `CLAUDE.md` and fix them if they differ; replace the one-line
   `README.md` with a short project description and links to PRD/BUILD_PLAN/CLAUDE.md.
7. `.gitignore` for `build/`, `.venv/`, IDE folders, `*.wav` outside `tests/golden/`.

## Out of scope

Contract types, DSP, custom UI, signing or notarization, installers.

## Deliverables

`CMakeLists.txt`, `CMakePresets.json`, `cmake/*`, `src/{contract,sim,module3d,plugin,cli}/`,
`tests/unit/*`, `.clang-format`, `.github/workflows/ci.yml`, `tools/ci/run_pluginval.sh`,
`docs/THIRD_PARTY.md`, updated `README.md`, `.gitignore`.

## Acceptance criteria — automated (all must be green in CI)

- [ ] Build succeeds on all 3 OSes with warnings as errors.
- [ ] `ctest` passes on all 3 OSes, including the exact pass-through null test at all listed
      rates and buffer sizes.
- [ ] pluginval **strictness 10** exits 0 for VST3 on Linux, macOS and Windows, and for AU on macOS.
- [ ] `auval -v aufx Spsc Mkrf` reports `AU VALIDATION SUCCEEDED`.
- [ ] ASan/UBSan job passes.
- [ ] clang-format check passes.
- [ ] CI artifacts contain VST3 (all OSes), AU and Standalone (macOS).

## Listening / manual checklist (Maisara)

Download the `SpatialScene-macos` and `SpatialScene-windows` artifacts. Builds are unsigned, so on
macOS run `xattr -dr com.apple.quarantine <bundle>` after copying them to
`~/Library/Audio/Plug-Ins/VST3/` and `~/Library/Audio/Plug-Ins/Components/`.

- [ ] Logic Pro: the plugin shows up under Audio FX → Makroof → SpatialScene and loads on a stereo track.
- [ ] Ableton or Reaper (macOS, VST3): loads on a stereo track.
- [ ] Windows DAW (VST3, copy to `C:\Program Files\Common Files\VST3\`): loads.
- [ ] In each: audio plays through unchanged (toggle bypass, which should make no audible difference).
- [ ] Save the project, close and reopen it, and the plugin is still there with no error.

## Contractor review focus

CMake structure and target boundaries; JUCE version pin; CI caching; that the pass-through test
really exercises `processBlock` through the same code path the host uses.

## Risks

- AU registration on CI runners can be flaky. Keep the `killall AudioComponentRegistrar` step and
  retry auval once.
- pluginval on Windows/Linux may need specific flags for in-process validation. Read its `--help`
  output for the pinned version.
- If the Windows MSVC + Ninja setup gets fiddly, the Visual Studio generator for the Windows preset is
  acceptable. Document it.

## Definition of done

All automated criteria are green. `docs/BUILD_PLAN.md` status row 00 is set to `done` with the PR link
and date. The PR description contains the listening checklist.
