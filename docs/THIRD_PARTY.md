# Third-party dependencies

Every dependency is pinned to a tag or commit and pulled in by CMake `FetchContent` or downloaded by
checksum in a script. Add a row here whenever a pin changes or a dependency is added (CLAUDE.md
"Code conventions").

## Linked into the product

| Dependency | Version / pin | Licence | How it is pulled in | Notes |
|---|---|---|---|---|
| [JUCE](https://github.com/juce-framework/JUCE) | tag `8.0.17-security` (JUCE 8.0.17, security-fix release of 2026-11-02) | Dual: [AGPLv3](https://www.gnu.org/licenses/agpl-3.0.en.html) or the [JUCE 8 commercial licence](https://juce.com/legal/juce-8-licence/) | `cmake/SpatialDependencies.cmake`, `FetchContent` | Plugin framework (VST3, AU, Standalone wrappers). JUCE bundles the VST3 SDK (MIT), AudioUnitSDK (Apache 2.0) and others, see its `LICENSE.md`. **The licence tier and revenue cap must be checked before the first paid release (Phase 13).** Splash screen left at the JUCE default until then. |

## Used in tests and tooling only (not shipped)

| Dependency | Version / pin | Licence | How it is pulled in | Notes |
|---|---|---|---|---|
| [Catch2](https://github.com/catchorg/Catch2) | tag `v3.16.1` | [BSL-1.0](https://www.boost.org/LICENSE_1_0.txt) | `cmake/SpatialDependencies.cmake`, `FetchContent` | C++ unit-test framework, linked into `spatial_tests` only. |
| [pluginval](https://github.com/Tracktion/pluginval) | release `v1.0.4` (zips verified by SHA-256 in `tools/ci/run_pluginval.sh`) | [GPLv3](https://github.com/Tracktion/pluginval/blob/develop/LICENSE) | Downloaded by `tools/ci/run_pluginval.sh` | Plugin validator run at strictness 10 in CI. Never linked. Its 1.0.x CLI always validates in-process (the `--validate-in-process` flag of 0.x no longer exists). |

## CI actions (GitHub Actions, pinned by version tag)

| Action | Version | Purpose |
|---|---|---|
| `actions/checkout` | v7.0.1 | Check out the repository |
| `actions/cache` | v6.1.0 | Cache `build/<preset>/_deps` (FetchContent sources and juceaide) |
| `actions/upload-artifact` | v7.0.2 | Upload plugin bundles and pluginval logs |
| `ilammy/msvc-dev-cmd` | v1.13.0 | MSVC x64 environment for Ninja on Windows |
| `hendrikmuhs/ccache-action` | v1.2.24 | ccache on all three OSes |

## Planned (not yet added)

PFFFT (FFT), nlohmann/json (contract JSON), an HRTF dataset and the BRAS measured-IR dataset arrive
in later phases. Add their rows when they are pinned.
