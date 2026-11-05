# Third-party dependencies

Every dependency is pinned to a tag or commit and pulled in by CMake `FetchContent` or downloaded by
checksum in a script. Python requirements are pinned by version and SHA-256 (`tools/ci/pin_hashes.py`). Add a row here whenever a pin changes or a dependency is added (CLAUDE.md
"Code conventions").

## Linked into the product

| Dependency | Version / pin | Licence | How it is pulled in | Notes |
|---|---|---|---|---|
| [JUCE](https://github.com/juce-framework/JUCE) | tag `8.0.17-security` (JUCE 8.0.17, security-fix release of 2026-11-02) | Dual: [AGPLv3](https://www.gnu.org/licenses/agpl-3.0.en.html) or the [JUCE 8 commercial licence](https://juce.com/legal/juce-8-licence/) | `cmake/SpatialDependencies.cmake`, `FetchContent` | Plugin framework (VST3, AU, Standalone wrappers). JUCE bundles the VST3 SDK (MIT), AudioUnitSDK (Apache 2.0) and others, see its `LICENSE.md`. **The licence tier and revenue cap must be checked before the first paid release (Phase 13).** Splash screen left at the JUCE default until then. |
| [nlohmann/json](https://github.com/nlohmann/json) | tag `v3.12.0` | [MIT](https://github.com/nlohmann/json/blob/develop/LICENSE.MIT) | `cmake/SpatialDependencies.cmake`, `FetchContent` | Header-only JSON library. PRIVATE dependency of `spatial_contract` (scene JSON I/O); not visible in the contract's public headers. MIT requires the copyright notice in distributions: add it to the product's licence notices before release (Phase 13). |
| [dr_wav](https://github.com/mackron/dr_libs) (dr_libs) | `dr_wav.h` v0.14.5 at commit `fa931f3285ced10ace628f7f1ac951e1951e7ea6` (tag `wav-0.14.5`), SHA-256 `c69816d0e0ac6cab3df8bf2f42df451d4531c2bfa34f7d7a69e959e6ed399038` | Public domain ([Unlicense](https://unlicense.org/)) or [MIT-0](https://github.com/aws/mit-0), at the user's choice | `cmake/SpatialDependencies.cmake`, `FetchContent` (URL + hash of the single header) | WAV read/write for `render_cli` only (`src/cli/WavIO.cpp`); not linked into the plugin. Neither licence requires attribution. |

## Used in tests and tooling only (not shipped)

| Dependency | Version / pin | Licence | How it is pulled in | Notes |
|---|---|---|---|---|
| [Catch2](https://github.com/catchorg/Catch2) | tag `v3.16.1` | [BSL-1.0](https://www.boost.org/LICENSE_1_0.txt) | `cmake/SpatialDependencies.cmake`, `FetchContent` | C++ unit-test framework, linked into `spatial_tests` only. |
| [jsonschema](https://github.com/python-jsonschema/jsonschema) | `4.26.0` (PyPI, pinned in `tools/ci/requirements.txt` with its dependencies `jsonschema-specifications`, `referencing`, `rpds-py`, `attrs`) | [MIT](https://github.com/python-jsonschema/jsonschema/blob/main/COPYING) | `pip install -r tools/ci/requirements.txt` | Validates the scene fixtures against `docs/contract/scene-v1.schema.json` in `tools/ci/test_schema_agreement.py`. `typing_extensions` 4.16.0 (PSF-2.0) is pinned for `referencing` on Python < 3.13. |
| [pytest](https://github.com/pytest-dev/pytest) | `9.2.0` (PyPI, pinned in `tools/ci/requirements.txt` and `tools/acoustics/requirements.txt` with `iniconfig`, `packaging`, `pluggy`, `Pygments`, and `colorama` 0.4.6 (BSD-3-Clause) on Windows) | [MIT](https://github.com/pytest-dev/pytest/blob/main/LICENSE) | `pip install -r tools/ci/requirements.txt` | Runs the Python tests in `tools/ci/` and `tools/acoustics/`. |
| [NumPy](https://github.com/numpy/numpy) | `2.5.4` (PyPI, `tools/acoustics/requirements.txt`) | [BSD-3-Clause](https://github.com/numpy/numpy/blob/main/LICENSE.txt) | `pip install -r tools/acoustics/requirements.txt` | Arrays for the analysis tooling (`tools/acoustics`). |
| [SciPy](https://github.com/scipy/scipy) | `1.18.1` | [BSD-3-Clause](https://github.com/scipy/scipy/blob/main/LICENSE.txt) | same | Butterworth filterbank, `sosfiltfilt`, correlation. |
| [python-soundfile](https://github.com/bastibe/python-soundfile) | `0.14.0` (with `cffi` 2.1.1 MIT, `pycparser` 3.12 BSD-3-Clause, `typing_extensions` 4.16.0 PSF-2.0) | [BSD-3-Clause](https://github.com/bastibe/python-soundfile/blob/master/LICENSE); its wheels bundle [libsndfile](https://github.com/libsndfile/libsndfile) (LGPL-2.1) | same | WAV I/O in the Python tooling and the listening pack. Tooling only, never shipped, so LGPL has no effect on the product. |
| [pyroomacoustics](https://github.com/LCAV/pyroomacoustics) | `0.10.1` (with `Cython` 3.3.1, Apache-2.0) | [MIT](https://github.com/LCAV/pyroomacoustics/blob/master/LICENSE) | same | Independent second opinion: `experimental.measure_rt60` cross-checks our T30 (Phase 02); its image-source model is the ISM reference from Phase 03. |
| [pluginval](https://github.com/Tracktion/pluginval) | release `v1.0.4` (zips verified by SHA-256 in `tools/ci/run_pluginval.sh`) | [GPLv3](https://github.com/Tracktion/pluginval/blob/develop/LICENSE) | Downloaded by `tools/ci/run_pluginval.sh` | Plugin validator run at strictness 10 in CI. Never linked. Its 1.0.x CLI always validates in-process (the `--validate-in-process` flag of 0.x no longer exists). |

## CI actions (GitHub Actions, pinned by version tag)

| Action | Version | Purpose |
|---|---|---|
| `actions/checkout` | v7.0.1 | Check out the repository |
| `actions/cache` | v6.1.0 | Cache `build/<preset>/_deps` (FetchContent sources and juceaide) |
| `actions/upload-artifact` | v7.0.2 | Upload plugin bundles, pluginval logs and the `listening-pack` |
| `ilammy/msvc-dev-cmd` | v1.13.0 | MSVC x64 environment for Ninja on Windows |
| `hendrikmuhs/ccache-action` | v1.2.24 | ccache on all three OSes |
| `actions/setup-python` | v7.1.0 | Python 3.12 for the `contract-tools` job (boundary check, `pytest tools/ci`) and the `python` job (`pytest tools`, listening pack) |

## Planned (not yet added)

PFFFT (FFT), an HRTF dataset and the BRAS measured-IR dataset arrive
in later phases. Add their rows when they are pinned.

Validation datasets for phase 05d (decider report 15, accepted by Maisara, 2026-11-05; facts from
researcher reports 13/14, external). The 05d session pins them, confirms the licence on the live record
and stores it in the manifest:

| Dataset | Version / pin | Licence | How it is pulled in | Notes |
|---|---|---|---|---|
| Arni (Aalto variable-acoustics room): Prawda, Schlecht, Välimäki, "Calibrating the Sabine and Eyring formulas", JASA 152(2):1158–1169 (2022), DOI [10.1121/10.0013575](https://doi.org/10.1121/10.0013575) | Zenodo [10.5281/zenodo.6985104](https://doi.org/10.5281/zenodo.6985104) (omni LS01 campaign); SHA-256 manifest set in phase 05d | CC BY 4.0, validation only, not shipped, not committed, changes: shoebox mapping. **Licence to be confirmed on the live record by the 05d session.** | `tools/validation/fetch_arni.py`, by checksum, cache `~/.cache/makroof/arni` | Each committed report derived from it carries the same attribution. |
| dEchorate: Di Carlo et al., "dEchorate: a calibrated room impulse response dataset for echo-aware signal processing", EURASIP J. Audio Speech Music Process. 2021, DOI [10.1186/s13636-021-00229-0](https://doi.org/10.1186/s13636-021-00229-0) | Zenodo [10.5281/zenodo.6576203](https://doi.org/10.5281/zenodo.6576203) v2.0 (omni sources only, AQ8); SHA-256 manifest set in phase 05d | CC BY 4.0, validation only, not shipped, not committed, changes: shoebox mapping. **Licence to be confirmed on the live record by the 05d session.** | `tools/validation/fetch_dechorate.py`, by checksum, cache `~/.cache/makroof/dechorate` | Each committed report derived from it carries the same attribution. |
