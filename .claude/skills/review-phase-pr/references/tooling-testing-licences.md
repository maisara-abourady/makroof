# Tooling, testing and licences (K8)

Reference file of the `review-phase-pr` skill. Scope: CMake/FetchContent pinning, GitHub Actions hygiene, sanitizers, Catch2, golden-file discipline, JSON Schema 2020-12, Python pinning, MSVC and macOS specifics, every third-party licence (JUCE tiers, PFFFT, nlohmann/json, dr_wav, Catch2, pluginval, Python packages, HRTF/BRAS data). All phases; especially 00, 01, 02, 08, 12, 13.

How to use it: read the "Reviewer's checklist" section first and apply the questions the diff makes
relevant; use the earlier sections to settle a disagreement with the author or to re-derive a number.
Every fact carries its source URL and the date it was verified (researched live on 2026-11-04).
Facts marked "(unverified, from memory)" must be verified before they are cited in a review; when
you verify one, fix it here. See `knowledge-inventory.md` for which facts go stale and how to
re-check them.

## Contents

- 0. What the repo pins today vs. what is current (2026-11-04)
- 1. Licences
  - 1.1 JUCE 8 / JUCE 9
  - 1.2 PFFFT
  - 1.3 nlohmann/json
  - 1.4 dr_wav (mackron/dr_libs)
  - 1.5 Catch2 v3
  - 1.6 pluginval
  - 1.7 Python packages (PyPI JSON API, 2026-11-04)
  - 1.8 Inno Setup, Apple Developer Program
- 2. CMake FetchContent hygiene
- 3. GitHub Actions hygiene
- 4. Sanitizers in practice
- 5. Catch2 v3 testing facts
- 6. Golden files and numeric DSP regression
- 7. JSON Schema 2020-12 and python-jsonschema; contract versioning
- 8. Python tooling pinning
- 9. Windows / MSVC specifics
- 10. macOS specifics
- 11. Reviewer's checklist (CMake, CI, deps, licences, docs, Python, tests)
- Sources index (all accessed 2026-11-04 unless noted)

---

Researched 2026-11-04. Every fact carries a source URL and the access date; anything not checked live
is marked "(unverified, from memory)". Repo state read from `/home/user/makroof/CLAUDE.md`,
`docs/THIRD_PARTY.md`, `cmake/SpatialDependencies.cmake` and `.github/workflows/ci.yml` on 2026-11-04.
`gh api` to third-party repos is blocked in this session, so tags/dates were taken with
`git ls-remote` and `git clone --bare --depth 1 --branch <tag>` + `git log -1 --format=%cI`.

## 0. What the repo pins today vs. what is current (2026-11-04)

| Dependency / action | Repo pin | Latest seen | Verdict |
|---|---|---|---|
| JUCE | `8.0.17-security` (commit `dabd5ad13cd869cba41046947fffc8e5ce5cd662`, 2026-11-02) | `9.0.5` (2026-11-02, "Latest"); newest 8.x is `8.0.17-security` | Pin is the newest 8.x. JUCE 8 is now a security-patch branch (`security-patches/v8`); JUCE 9 is the mainline. |
| Catch2 | `v3.16.1` (commit `08092139…`, 2026-10-08) | `v3.16.1` | Current. |
| pluginval | `v1.0.4` (2024-12-04, still badged "Latest") | `v2.0.0-beta3` (2026-10-14, pre-release) | Current stable. 2.0 is beta only. |
| actions/checkout | `v7.0.1` (commit `3d3c42e5aac5ba805825da76410c181273ba90b1`, 2026-07-17) | `v7.0.1` | Current; not SHA-pinned. |
| actions/cache | `v6.1.0` (commit `55cc8345863c7cc4c66a329aec7e433d2d1c52a9`, 2026-06-23) | `v6.1.0` | Current; not SHA-pinned. |
| actions/upload-artifact | `v7.0.2` (commit `cf430e030ddbb5b0abf93d22962f4752f3646cd9`, 2026-10-07) | `v7.0.2` | Current; not SHA-pinned. |
| hendrikmuhs/ccache-action | `v1.2.24` (commit `f09c25b45002a07be2955cbe52e8cee55643f89d`, 2026-08-31) | `v1.2.24` | Current; not SHA-pinned. |
| ilammy/msvc-dev-cmd | `v1.13.0` (commit `0b201ec74fa43914dc39ae48a89fd1d8cb592756`, 2024-01-01) | `v1.13.0` | Current (project is slow-moving); not SHA-pinned. |
| nlohmann/json | planned | `v3.12.0` (2025-04-11) | — |
| PFFFT (marton78) | planned | `v1.2.0` (tag commit 2026-11-03) | — |
| dr_wav | planned | `wav-0.14.6` (header "dr_wav - v0.14.6 - 2026-10-31") | — |
| Inno Setup | not yet used | `is-7_1_1` (commit 2026-10-26; 6.7.4 same day) | — |

Sources: `git ls-remote`/shallow clones of each repo on 2026-11-04;
https://github.com/juce-framework/JUCE/releases (2026-11-04);
https://github.com/Tracktion/pluginval/releases (2026-11-04); https://github.com/nlohmann/json/releases (2026-11-04).

Two doc rows in `docs/THIRD_PARTY.md` are stale (see §1.1): "Splash screen left at the JUCE default" — JUCE 8
removed the splash-screen requirement entirely; and the licence link `juce.com/legal/juce-8-licence/` still
resolves, but JUCE's "current" EULA page is now `juce.com/legal/juce-9-licence/`.

---

## 1. Licences

### 1.1 JUCE 8 / JUCE 9

- **Dual licence.** `LICENSE.md` at tag `8.0.17-security`: modules are "dual-licensed under the" AGPLv3 and the
  commercial JUCE licence; if not using AGPLv3 you "agree to the terms of the JUCE 8 End User Licence Agreement".
  Examples are ISC. Bundled third-party code listed there: VST3 SDK (MIT), AudioUnitSDK (Apache 2.0), Oboe
  (Apache 2.0), FLAC/Ogg Vorbis (BSD), GLEW (BSD + Mesa/Khronos MIT), jpeglib (IJG), CHOC + QuickJS (ISC/MIT), LV2
  (ISC), pslextensions (public domain), AAX (proprietary Avid / GPLv3), zlib, pnglib, Box2D (zlib), HarfBuzz
  (Old MIT), SheenBidi (Apache), ASIO (proprietary Steinberg / GPLv3).
  Source: https://raw.githubusercontent.com/juce-framework/JUCE/8.0.17-security/LICENSE.md (2026-11-04).
  `master` LICENSE.md now points to the "JUCE 9 End User Licence Agreement" and an SPDX SBOM `JUCE.spdx.json`.
  Source: https://raw.githubusercontent.com/juce-framework/JUCE/master/LICENSE.md (2026-11-04).
- **Current tiers (identical in the JUCE 8 EULA and the JUCE 9 EULA):**

  | Tier | Annual revenue or funding limit (previous 12 months, USD) | Subscription / user | Perpetual / user |
  |---|---|---|---|
  | Starter | up to $20,000 | — | Free |
  | Indie | up to $300,000 | $40/month (1-month minimum) | $800 |
  | Pro | no limit | $175/month (12-month minimum) | $3,500 |
  | Educational | no limit, non-commercial academic use only (1.2.4) | — | Free |

  Sources: JUCE 8 EULA https://juce.com/legal/juce-8-licence/ (title "The JUCE 8 End User Licence Agreement",
  changelog "7th May 2024 … 2nd June 2025 Added an Educational Licence Type … 17th July 2025 11.2 clarified …
  not transferrable"); JUCE 9 EULA https://juce.com/legal/juce-9-licence/ (changelog "17th June 2026: JUCE 9 EULA
  Published"); pricing table https://juce.com/get-juce/ ; all accessed 2026-11-04.
  Official forum post "JUCE 9: No pricing or EULA changes" (t0m, 2026-06-17): "JUCE 9 will retain the same
  divisions between licensing tiers, and the price for each tier will remain the same … The JUCE 9 End User
  License Agreement is also remaining unchanged from the last iteration of JUCE 8."
  https://forum.juce.com/t/juce-9-no-pricing-or-eula-changes/69000 (2026-11-04).
- **Revenue definition.** For individuals the limit counts "the total revenue or funding generated by that
  individual or entity's use of the Framework from all sources"; for companies and other legal entities it is
  *all* revenue of the entity, not just the plugin's.
  https://forum.juce.com/t/amendments-to-the-juce-end-user-licence-agreement-for-juce-8/61265 (t0m, 2024-05-07;
  accessed 2026-11-04). EULA 1.14: exceed the limit → buy the fitting tier or "stop developing and distributing
  Products immediately". 1.13: Starter/Indie/Pro may not be used simultaneously nor their Products combined.
- **Splash screen.** JUCE 8 announcement: Starter has "the requirement to display a splash screen removed"
  (https://forum.juce.com/t/juce-8-is-available-now/61809, 2024-06-12; and the amendments post above). Neither the
  JUCE 8 nor JUCE 9 EULA text mentions "splash", "Made with JUCE" or `JUCE_DISPLAY_SPLASH_SCREEN` (checked
  2026-11-04). A grep of `modules/juce_gui_basics/juce_gui_basics.h`, `modules/juce_core/juce_core.h` and
  `extras/Build/CMake/JUCEUtils.cmake` at `8.0.17-security` finds no `JUCE_DISPLAY_SPLASH_SCREEN` (2026-11-04).
  → The "Splash screen left at the JUCE default" note in THIRD_PARTY.md is moot; delete it.
- **Attribution.** The EULA sets no attribution requirement; 10.2 lets RMS publicise your use of JUCE (opt out by
  e-mail). Bundled SDK notices (VST3 MIT, AudioUnitSDK Apache 2.0, etc.) still require their copyright notices to
  ship with the binary — keep them in the installer/About box.
- **Closed-source commercial.** EULA 1.9 grants a licence "to Distribute and sell Products where you are the
  Owner"; 2.3 forbids subjecting the Framework to a source-disclosure licence; AGPLv3 is only viable if the whole
  plugin is AGPL. Forum staff (t0m): "It is only the revenue and funding limit that determines the appropriate
  tier" and "The JUCE EULA doesn't distinguish between either the type of project, or how you are selling and
  distributing it." https://forum.juce.com/t/do-i-need-the-starter-or-indie-licence/69021 (2026-11-04).
- **Verdict for this project.** A closed-source paid VST3/AU plugin can ship under **Starter (free)** only while
  the licensee's total revenue+funding over the trailing 12 months is ≤ $20k; above that **Indie** ($40/mo or
  $800 perpetual per developer) up to $300k; **Pro** beyond. For a company the cap is company-wide revenue.
  A JUCE 9 licence also "grants you the right to use all previous versions of JUCE" (get-juce FAQ, 2026-11-04),
  so buying JUCE 9 Indie covers the pinned 8.0.17 build. No splash screen under any tier.
- **Releases.** Tags `8.0.0`…`8.0.15`, `8.0.16-security` (2026-10-13), `8.0.17-security` (2026-11-02,
  commit `dabd5ad1…`, "Fixed ZipFile deleting files outside the target directory through a pre-existing link",
  plus WAV/AIFF/XML/GIF/PNG/OSC/JSON/ValueTree hardening); same fixes in `9.0.5` and `7.0.14-security`.
  Sources: `git ls-remote --tags https://github.com/juce-framework/JUCE.git` (2026-11-04);
  https://github.com/juce-framework/JUCE/releases (2026-11-04);
  https://forum.juce.com/t/juce-9-0-5-8-0-17-security-7-0-14-security/69810 (2026-11-04).
  **`8.0.17-security` exists** (annotated tag `e548e97a…` → commit `dabd5ad1…`).

### 1.2 PFFFT

- **Licence (both jpommier/bitbucket original and marton78/pffft):** FFTPACK-derived, BSD-like, 3 conditions:
  no endorsement using NCAR/UCAR names; source redistributions keep the copyright notices, condition list and
  disclaimer; **binary redistributions must reproduce the copyright notice, conditions and disclaimer "in the
  documentation and/or other materials provided with the distribution"**. Copyright lines: (c) 2013 Julien
  Pommier; (c) 2004 UCAR; marton78 adds (c) 2019 Hayati Ayguen and (c) 2020 Dario Mambro.
  Sources: https://raw.githubusercontent.com/marton78/pffft/master/LICENSE.txt (2026-11-04);
  https://bitbucket.org/jpommier/pffft/raw/master/pffft.c header (2026-11-04).
- Attribution requirement → the installer/About box must carry the PFFFT + FFTPACK/UCAR notice.
- marton78/pffft: tags `v1.0.0`, `v1.1.0`, `v1.2.0` (`v1.2.0` commit `5055b930…`, 2026-11-03); README: SSE1/AVX/
  AVX2, AltiVec, NEON, WASM SIMD, RVV; "There's now CMake support". Original bitbucket repo: single tag `v1.0.0`,
  HEAD `67a4a6a1…`. (`git ls-remote`, 2026-11-04.)

### 1.3 nlohmann/json

- MIT, "Copyright (c) 2013-2026 Niels Lohmann"; notice must be "included in all copies or substantial portions".
  https://raw.githubusercontent.com/nlohmann/json/develop/LICENSE.MIT (2026-11-04).
- Latest tag `v3.12.0` (2025-04-11). https://github.com/nlohmann/json/releases (2026-11-04).

### 1.4 dr_wav (mackron/dr_libs)

- Header: "dr_wav - v0.14.6 - 2026-10-31"; "Choice of public domain or MIT-0" (ALTERNATIVE 1 Public Domain /
  unlicense.org; ALTERNATIVE 2 "MIT No Attribution", Copyright 2023 David Reid). No attribution required.
  https://raw.githubusercontent.com/mackron/dr_libs/master/dr_wav.h (2026-11-04). Tag `wav-0.14.6` (2026-10-31).
  Pin by commit SHA: dr_libs has no releases page content, only tags per library.

### 1.5 Catch2 v3

- Boost Software License 1.0 ("August 17th, 2003"). BSL requires the notice only in *source* redistributions;
  test binaries are never shipped anyway. https://raw.githubusercontent.com/catchorg/Catch2/devel/LICENSE.txt
  (2026-11-04). Latest `v3.16.1` (2026-10-08; `v3.16.0` 2026-08-25). https://github.com/catchorg/Catch2/releases.

### 1.6 pluginval

- GPLv3 ("Version 3, 29 June 2007"). https://raw.githubusercontent.com/Tracktion/pluginval/develop/LICENSE
  (2026-11-04). Fine for a closed-source product because the GPL's copyleft attaches to *distribution of the
  program or derivative works*; running an unmodified GPL tool in CI over your binary creates no derivative and
  nothing GPL is linked or shipped (GPLv3 §0/§2: "You may make, run and propagate covered works that you do not
  convey"; FSF FAQ "GPLOutput": output of a GPL program is not covered unless the program copies itself into it —
  (unverified, from memory; https://www.gnu.org/licenses/gpl-faq.html#GPLOutput)).
- Latest stable `v1.0.4` (2024-12-04, badged Latest); `v2.0.0-beta1..3` (2026-10-13/14, pre-release).
  https://github.com/Tracktion/pluginval/releases (2026-11-04).

### 1.7 Python packages (PyPI JSON API, 2026-11-04)

| Package | Latest | Uploaded | Licence | Wheels for cp312 |
|---|---|---|---|---|
| pyroomacoustics | 0.10.1 | 2026-05-01 | MIT (Copyright 2014-2017/2021 EPFL-LCAV) | cp39–cp314: manylinux_2_27 x86_64, manylinux_2_26 aarch64 (cp311+), macosx universal2, win_amd64; sdist. `requires_python >=3.9`. |
| numpy | 2.5.4 | 2026-10-10 | BSD-3-Clause AND 0BSD AND MIT AND Zlib AND CC0-1.0 | linux x86_64/aarch64/musl, macOS x86_64/arm64, win32/win_amd64 |
| scipy | 1.18.1 | 2026-08-21 | BSD-3-Clause | linux, macOS, win_amd64, win_arm64 |
| soundfile | 0.14.0 | 2026-06-06 | BSD-3-Clause (bundles libsndfile LGPL-2.1 in wheels — (unverified, from memory)) | py2.py3 wheels for all OSes incl. win_arm64 |
| pytest | 9.2.0 | 2026-10-27 | MIT | pure |
| jsonschema | 4.26.0 | 2026-01-07 | MIT | pure |
| pyloudnorm | 0.2.0 | 2026-01-04 | MIT | pure |
| sofar | 1.3.0 | 2026-08-27 | MIT (pyfar developers) | pure |
| matplotlib | 3.11.2 | 2026-09-11 | PSF-based "matplotlib license" (BSD-compatible) | linux, macOS, win_amd64, win_arm64 |

Source: `https://pypi.org/pypi/<name>/json` (2026-11-04). None of these ship in the plugin; they only need
licence rows in THIRD_PARTY.md if the project policy covers tooling (it does: "Record every dependency").

### 1.8 Inno Setup, Apple Developer Program

- **Inno Setup licence** (`license.txt`, jrsoftware/issrc main, 2026-11-04): "Permission is granted to anyone to
  use this software for any purpose, including commercial applications"; conditions: keep copyright notices in
  source; binary redistributions keep the copyright notice and web-site addresses (e.g. About boxes); do not
  misrepresent origin; modified versions plainly marked. Acknowledgment in docs "would be appreciated but is not
  required". Site: "All commercial users of Inno Setup are requested to purchase a commercial license" — a request,
  not a condition of LICENSE.TXT. https://raw.githubusercontent.com/jrsoftware/issrc/main/license.txt and
  https://jrsoftware.org/isinfo.php (2026-11-04). The generated installer carries Inno's notice automatically.
  Latest: Inno Setup 7.1.1 and 6.7.4 (tags `is-7_1_1`, `is-6_7_4`, 2026-10-26/28).
- **notarytool / Developer ID** (Apple docs via developer.apple.com data JSON, 2026-11-04): notarization needs a
  **Developer ID Application** certificate (installer packages: Developer ID Installer), a valid signature
  (`codesign -vvv --deep --strict`), a secure timestamp (`--timestamp`; "macOS accepts only one secure timestamp
  server"), and no `com.apple.security.get-task-allow` entitlement. Developer ID certificates are only issued
  to paid **Apple Developer Program** members (team agent) — (unverified, from memory; see
  https://developer.apple.com/support/developer-id/). Sequence in §10.

---

## 2. CMake FetchContent hygiene

- **Hash vs tag.** CMake docs: "it is advisable to use a hash for `GIT_TAG` rather than a branch or tag name";
  a commit hash "is more secure and helps to confirm that the downloaded contents are what you expected". Tags
  can be moved/deleted (GitHub's own actions guidance says the same for action tags). Repo uses tag names
  (`8.0.17-security`, `v3.16.1`). https://cmake.org/cmake/help/latest/module/FetchContent.html (2026-11-04).
- **GIT_SHALLOW caveat.** ExternalProject docs: with `GIT_SHALLOW`, "`GIT_TAG` works only with branch names and
  tags. A commit hash is not allowed." So moving to SHA pins means dropping `GIT_SHALLOW TRUE` (slower clone;
  mitigate with the `_deps` cache the CI already has) or keep tag + verify the SHA after populate, e.g.
  `execute_process(git rev-parse HEAD)` compared to a recorded SHA. (Technique: from memory.)
  https://cmake.org/cmake/help/latest/module/ExternalProject.html (2026-11-04).
- **Strongest pin = `URL` + `URL_HASH SHA256=…`** of a release tarball: content-addressed, no git, "Specifying
  this option is strongly recommended for URL downloads", and CMake skips the network when a cached file matches.
  GitHub auto-generated archives are *not* guaranteed byte-stable across time (git version changes have altered
  them) — prefer release-attached assets or record the hash and expect to re-verify (unverified, from memory).
- **`SYSTEM`** keyword on `FetchContent_Declare` (CMake ≥ 3.25) marks the added subdirectory as SYSTEM so its
  targets' include dirs become `-isystem` and third-party warnings don't trip `SPATIAL_WERROR`. Repo already uses it
  for JUCE and Catch2. Needs `cmake_minimum_required(VERSION 3.25)` or it is silently ignored → check the minimum.
- **`FetchContent_MakeAvailable` vs `FetchContent_Populate`.** Single-arg `FetchContent_Populate(<name>)` was
  deprecated in 3.30 (policy CMP0169); docs: "projects should be updated to use FetchContent_MakeAvailable()"
  and Populate "is rarely the right command to use". Pattern `if(NOT x_POPULATED) FetchContent_Populate(x)
  add_subdirectory(...)` is legacy; `EXCLUDE_FROM_ALL`/`SYSTEM` on Declare replace it.
- **Overrides to know in review:** `FETCHCONTENT_SOURCE_DIR_<NAME>` (local checkout, no download),
  `FETCHCONTENT_FULLY_DISCONNECTED` ("not appropriate for blocking network access on the first run"),
  `FETCHCONTENT_UPDATES_DISCONNECTED` (no update step), `FETCHCONTENT_QUIET OFF` (repo sets it: verbose logs).
- **No vendoring.** Grep for `third_party/`, `external/`, `*.tar.gz`, large `*.h` with foreign copyright, and
  `_deps/` committed by accident (`git ls-files | grep _deps`). Every dependency must come through
  `SpatialDependencies.cmake` + a THIRD_PARTY.md row (CLAUDE.md rule). Single-header libs (dr_wav, nlohmann)
  are tempting to copy in; still fetch them by `URL`+`URL_HASH` so the pin is auditable.
- **Catch2 `catch_discover_tests`** (docs, 2026-11-04): `DISCOVERY_MODE POST_BUILD` (default) runs the test
  binary at build time to list tests; `PRE_TEST` "is delayed until just prior to test execution (useful e.g. in
  cross-compilation environments)" and avoids the Xcode-on-Apple-Silicon failure "Result: Subprocess killed".
  Also `REPORTER` → `--reporter`, `EXTRA_ARGS`, `OUTPUT_DIR` ("should be used instead of `EXTRA_ARGS --out foo` to
  avoid race conditions"), `TEST_SPEC`. Global default: `CMAKE_CATCH_DISCOVER_TESTS_DISCOVERY_MODE`. Link
  `Catch2::Catch2WithMain` "and only the latter" unless you need a custom `main`.
  https://raw.githubusercontent.com/catchorg/Catch2/devel/docs/cmake-integration.md.
  Why PRE_TEST for this repo: the test binary initialises the JUCE GUI runtime (pass-through test) and under
  POST_BUILD discovery runs during `cmake --build` on a headless Linux box *outside* `xvfb-run` → discovery can
  fail/hang; with PRE_TEST the `--list-test-names-only` run happens inside `xvfb-run -a ctest`.

---

## 3. GitHub Actions hygiene

- **Pin by full SHA.** GitHub: "Pin references to actions to a commit SHA in your workflow files … If you'd like
  to specify a tag, then be sure that you trust the action's creators … a tag can be moved or deleted if a bad
  actor gains access to the repository storing the action." Lockfiles (newer) "supersede SHA pinning for
  repositories that adopt it".
  https://docs.github.com/en/actions/security-for-github-actions/security-guides/security-hardening-for-github-actions (2026-11-04).
  Form: `uses: actions/checkout@3d3c42e5aac5ba805825da76410c181273ba90b1 # v7.0.1`. SHAs for the repo's current
  tags are in §0 (peeled commit SHAs, 2026-11-04). Dependabot/Renovate can keep the comment and SHA in sync.
- **Latest majors (2026-11-04):** `actions/checkout` v7 (v7.0.1 2026-07-17; v7.0.0 "block checking out fork pr for
  pull_request_target and workflow_run", ESM; backports v2.8.0/v3.7.0/v4.4.0/v5.1.0 same day flagged
  `[BREAKING] allow-unsafe-pr-checkout`), `actions/cache` v6 (v6.1.0 2026-06-23; v5+ needs runner ≥ 2.327.1,
  Node 24), `actions/upload-artifact` v7 (v7.0.2 2026-10-07; `archive: false` direct-upload mode fails on multi-file
  globs), `hendrikmuhs/ccache-action` v1.2.24 (2026-08-31), `ilammy/msvc-dev-cmd` v1.13.0 (2024-01-01).
  Sources: each repo's `/releases` page + tag clones (2026-11-04).
- **Concurrency.** "Any existing pending job or workflow in the same concurrency group, if it exists, will be
  canceled and the new queued job or workflow will take its place"; `cancel-in-progress: true` also cancels the
  running one; the value may be an expression so that release branches are never cancelled.
  https://docs.github.com/en/actions/using-jobs/using-concurrency (2026-11-04). Repo:
  `ci-${{ github.workflow }}-${{ github.ref }}` with cancel — fine for PRs; a release workflow must *not* cancel.
- **`fail-fast: false`** keeps the other OS legs running when one fails so a PR shows all platform failures at
  once (repo already does this). Without it the first failure cancels siblings and hides OS-specific bugs.
- **Artifact retention.** Default 90 days; `retention-days:` on `upload-artifact` (1–90 on github.com, up to 400
  on enterprise-configured orgs; cannot exceed repo/org limit). Listening packs and plugin bundles are large →
  set `retention-days` (e.g. 14) and `if-no-files-found: error` (repo does the latter).
  https://docs.github.com/en/actions/guides/storing-workflow-data-as-artifacts (2026-11-04).
- **Secrets in release workflows.** Never store plaintext in workflow files; mask derived values with
  `::add-mask::`; check logs are not "explicitly being printed"; put signing/notarisation secrets in an
  **environment** with required reviewers ("A workflow job cannot access environment secrets until approval is
  granted by a reviewer"). Avoid `pull_request_target`/`workflow_run` with untrusted PR code; pass untrusted
  context (`github.event.pull_request.title`, branch names) through `env:` not inline `${{ }}` in `run:`.
  (Same hardening page, 2026-11-04.) Apple creds: `xcrun notarytool store-credentials` from secrets into a
  temporary keychain, delete the keychain in an `if: always()` step.
- **Schedules.** "Scheduled workflows will only run on the default branch", can be delayed under load, minimum
  interval 5 minutes, and in public repos are "automatically disabled when no repository activity has occurred
  in 60 days". Add `workflow_dispatch:` alongside `schedule:` so the job can be exercised from a PR branch/UI.
  https://docs.github.com/en/actions/writing-workflows/choosing-when-your-workflow-runs/events-that-trigger-workflows (2026-11-04).
- **Minimum `permissions:`** block (`contents: read`) at workflow top; release jobs add `contents: write` only —
  (unverified, from memory; same hardening page).

---

## 4. Sanitizers in practice

- **Flags.** ASan: `-fsanitize=address -fno-omit-frame-pointer -O1 -g` (docs example; "disable inlining and tail
  call elimination" for perfect traces). UBSan: `-fsanitize=undefined`; the `undefined` group *excludes*
  `float-divide-by-zero` ("Clang defines the result as infinity or NaN"), `unsigned-integer-overflow`,
  `implicit-conversion`, `local-bounds`, `nullability-*` → add `-fsanitize=float-divide-by-zero` explicitly for DSP.
  `-fno-sanitize-recover=all` → "print a verbose error report and exit" instead of continuing (turns UB reports
  into failures; without it CI passes with red logs). `UBSAN_OPTIONS=print_stacktrace=1` plus `-g`,
  `-fno-sanitize-merge`, `-fno-omit-frame-pointer`, `llvm-symbolizer` on PATH. TSan: `-fsanitize=thread -O1 -g`.
  Sources: https://clang.llvm.org/docs/AddressSanitizer.html, …/UndefinedBehaviorSanitizer.html,
  …/ThreadSanitizer.html (2026-11-04).
- **Leak detection.** On by default on Linux; macOS needs `ASAN_OPTIONS=detect_leaks=1` and is "not yet
  supported on other platforms" (Windows). LSan suppressions: `LSAN_OPTIONS=suppressions=lsan.supp` with lines
  `leak:<pattern>` (pattern matched against function/module names) or `__lsan_default_suppressions()`. ASan
  suppressions (`interceptor_via_fun`, `interceptor_via_lib`, `odr_violation`, `alloc_dealloc_mismatch`) "should
  only be used for suppressing issues in external code". Typical JUCE/X11/fontconfig one-time allocations
  (`leak:libfontconfig`, `leak:libX11`, `leak:_dl_init`) belong in a checked-in suppression file with a comment
  per line — (patterns: from memory).
- **TSan platforms.** Supported: Linux (x86_64, aarch64, ppc64), Darwin (arm64, x86_64), Android, FreeBSD,
  NetBSD; **Windows is not listed** and MSVC has no TSan (MSVC has ASan only) — (MSVC part: unverified, from
  memory; https://learn.microsoft.com/en-us/cpp/sanitizers/asan). macOS arm64 is supported by clang and Xcode
  (LLVM commit "Allow TSan in the Clang driver for Apple Silicon Macs", 2020); iOS device targets are not. Known
  caveats on Apple Silicon: ~5× memory, no static libc, PIE required, occasional runtime CHECK failures on Xcode
  betas (https://developer.apple.com/forums/thread/711932, 2026-11-04). Keep the TSan preset Linux-only (as
  CLAUDE.md does) and run it under `xvfb-run -a`.
- **TSan false positives with lock-free code.** TSan understands `std::atomic` with their memory orders; a race
  report on data published via a `release` store / `acquire` load is a *real* bug (wrong order, or
  `memory_order_relaxed` used where acquire/release is needed). Genuine false positives arise only with
  (a) synchronisation TSan can't see (OS primitives it does not intercept, custom fences `std::atomic_thread_fence`
  — TSan does not model standalone fences), (b) uninstrumented libraries ("Uninstrumented modules can cause
  missed races or false positives"), (c) JUCE's own un-annotated SPSC paths. Annotate with
  `<sanitizer/tsan_interface.h>`: `__tsan_acquire(addr)` / `__tsan_release(addr)` around the custom barrier,
  guarded by `#if defined(__has_feature) && __has_feature(thread_sanitizer)`; or replace the fence with an
  atomic RMW the tool sees. Function-level `__attribute__((no_sanitize("thread")))` stops instrumentation of
  that function's plain loads/stores but keeps the function "instrumented to avoid false positives";
  `disable_sanitizer_instrumentation` disables all and can itself create false positives. Suppressions:
  `TSAN_OPTIONS=suppressions=tsan.supp` with `race:<pattern>`, `race_top:`, `mutex:`, `thread:`, `signal:`,
  `deadlock:`, `called_from_lib:<lib>` (use `called_from_lib:libX11` / `libfontconfig` / `libasound` for
  noisy system libs). Sources: ThreadSanitizer page (2026-11-04); annotation API: from memory.
- **TSan + std::atomic memory order review rule.** Producer: write payload, then `store(ptr, release)`.
  Consumer: `load(acquire)`, then read payload. `relaxed` is only correct for counters whose value nothing else
  depends on. An "atomic pointer swap" that frees the old object needs a hand-back path (SPSC queue of retired
  objects) — TSan will flag use-after-free otherwise. `std::atomic<float>` ops are lock-free on all three
  compilers for 32/64-bit types; verify `is_always_lock_free` in a static_assert. (From memory.)
- **GUI under xvfb.** `xvfb-run -a ctest --preset …` (repo does it); for pluginval `run_pluginval.sh` adds it
  when `$DISPLAY` is empty. ASan + JUCE GUI: set `ASAN_OPTIONS=detect_leaks=1:...` only after a suppression file
  exists, else X11/freetype leaks fail the job.

---

## 5. Catch2 v3 testing facts

- **GENERATE.** "The 'Generators' TEST_CASE will be entered 3 times"; multiple GENERATEs form a cartesian product
  and each acts as an implicit SECTION. Generators: `value`, `values`, `table`, `range`, `from_range`, adapters
  `filter`, `take`, `repeat`, `map`, `chunk`, `cat`; `random(a,b)`; `GENERATE_COPY`/`GENERATE_REF` for captured
  variables. "Given the same seed, the output from the integral generators is fully reproducible across different
  platforms" (floating `random` is *not* guaranteed identical across platforms).
  https://raw.githubusercontent.com/catchorg/Catch2/devel/docs/generators.md (2026-11-04).
- **Logging.** `INFO` "only reported with next assertions that are logged" (shown on failure); `CAPTURE(x)`
  prints "that variable/expression and its value"; `UNSCOPED_INFO` lives until the next assertion; `WARN`
  "always reported but does not fail the test". A `GENERATE` without `CAPTURE(value)` yields a failure line
  with no indication *which* generated value failed → smell.
  https://raw.githubusercontent.com/catchorg/Catch2/devel/docs/logging.md (2026-11-04).
- **Float matchers.** `WithinAbs(target, margin)` (|diff| ≤ margin), `WithinRel(target, eps)` (default eps =
  `numeric_limits<T>::epsilon()*100`), `WithinULP(target, maxUlpDiff)`. Combine: `WithinRel(expected, 0.001) ||
  WithinAbs(0, 1e-6)` for values that may be ~0. "We strongly recommend against using `Approx` when writing new
  code" (deprecated). https://raw.githubusercontent.com/catchorg/Catch2/devel/docs/comparing-floating-point-numbers.md (2026-11-04).
- **BENCHMARK.** `BENCHMARK("name") { return work(); };` (semicolon required, `return` prevents DCE;
  `BENCHMARK_ADVANCED` + `Catch::Benchmark::Chronometer meter; meter.measure(...)` for setup separation).
  In v3 benchmarking is compiled in; the v2 `CATCH_CONFIG_ENABLE_BENCHMARKING` macro no longer appears in
  configuration.md (only `CATCH_CONFIG_USE_ASYNC`) — (removal: from memory, consistent with docs read 2026-11-04).
  Results print as a table (samples/iterations/estimated run time/mean/std dev with low/high bounds) in the
  console reporter and are included in the XML/JUnit reporters. CLI: `--benchmark-samples` (default 100),
  `--benchmark-no-analysis`, `--benchmark-warmup-time`, `--skip-benchmarks` (skips BENCHMARK blocks, not
  `[!benchmark]`-tagged tests). CI pattern: tag benchmark tests `[!benchmark]` (hidden by default), run them in a
  separate step `spatial_tests "[!benchmark]" --reporter console::out=bench.txt --benchmark-samples 20` and
  upload the file; never gate CI on timings from shared runners.
  https://raw.githubusercontent.com/catchorg/Catch2/devel/docs/benchmarks.md and …/command-line.md (2026-11-04).
- **Seeds and order.** `--rng-seed <n|time|random-device>`; default seed source is `std::random_device`,
  default test order is `rand`. Print the seed in CI logs (console reporter does: "Randomness seeded to: …") so a
  failure can be replayed with `--rng-seed N`. For determinism tests, seed from scene data, not from Catch's RNG.
- **Tags/filters.** `[a][b]` = both, `[a],[b]` = either (comma binds looser), `~[a]` = exclude; hidden tags
  `[.]`, `[!benchmark]`, `[!mayfail]`, `[!shouldfail]`. `--reporter` repeatable, `::out=file`, `::key=value`.
- **Reporter in ctest.** `catch_discover_tests(spatial_tests REPORTER junit OUTPUT_DIR ${CMAKE_BINARY_DIR}/junit
  EXTRA_ARGS --rng-seed 1234 --warn NoAssertions DISCOVERY_MODE PRE_TEST)`; `--warn NoAssertions` makes a test
  with zero assertions fail (catches tautological "tests" that only call code).
- **Tautological test.** The test computes the expected value with the *same formula/code path* as the unit
  under test (e.g. expected RT60 via the same Sabine helper, expected IR via the same ISM function with the
  same parameters, or comparing `render()` against `render()` run twice). It can only fail on nondeterminism.
  Fix: analytic closed form, hand-computed constants, an independent implementation (pyroomacoustics, direct
  O(N²) convolution vs FFT convolver), or a property (energy conservation, symmetry, linearity, time-invariance).
- **Smells list.** Tolerance widened in the same PR that changes DSP; golden regenerated without a §6 change-log
  row; `#if !JUCE_WINDOWS` / `if (SKIP_ON_MAC)` around an assertion; `GENERATE` without `CAPTURE`; `REQUIRE(true)`
  or no assertion; `WithinAbs` with margin comparable to the signal (e.g. 0.1 on a unit-gain value) or
  `WithinRel` on values near zero; `Approx`; sleeping/timing-based assertions; tests reading files by relative
  path (cwd-dependent); random inputs without printed seed; `[!mayfail]` added to silence a flake; expected
  values copied from the first run's output (self-golden) with no derivation comment.

---

## 6. Golden files and numeric DSP regression

- **Store metrics with tolerances, not raw audio**, as `tests/golden/*.json` (e.g. per-band RT60 ±5 %, C50 ±1 dB,
  DRR ±0.5 dB, peak/RMS ±0.1 dB, IR arrival sample ±1). Keep small reference WAVs only where a metric can't
  capture the behaviour (click detection, crossfade) and compare by residual energy, not sample equality.
- **Why not bit-exact across platforms:** float32 arithmetic differs by compiler/arch through FMA contraction
  (MSVC `/fp:precise` no longer contracts by default since VS 2022, GCC/Clang contract by default on
  AArch64/with `-ffp-contract=fast`), SIMD lane order in reductions (PFFFT SSE vs NEON), `std::sin`/`std::exp`
  libm implementations (glibc vs MSVC UCRT vs Apple libm differ in last-ULP), and denormal handling (FTZ/DAZ set
  by JUCE's `ScopedNoDenormals`). Sources: MSVC /fp page (2026-11-04); rest from memory.
- **Normal residual levels.** After normalising two renders of the same scene from different platforms, the
  residual (difference) RMS relative to the signal is typically −120 … −140 dBFS for float32 pipelines dominated
  by FFT convolution (~1e-6 … 1e-7 relative), and −100 … −110 dB when long recursive filters/IIR tails or
  transcendental-heavy ISM accumulate rounding. A residual above ≈ −90 dB is a real behavioural difference
  (different reflection count, different seed, different crossfade), not drift. Bit-identity is only expected
  *within* a platform and build config (CLAUDE.md "Determinism"). (Ranges: engineering experience, from memory.)
- **Independent references first:** analytic (image-source for a rectangular room: arrival times
  `d/c`, 1/r gains; Sabine/Eyring RT60; free-field ILD/ITD from HRTF geometry), a second implementation
  (pyroomacoustics ISM with the same `max_order`, direct time-domain convolution vs the partitioned FFT convolver),
  measured data (BRAS). Self-generated goldens guard *only* against unintended change and must say so in a
  `"source": "self, phase-05, reason: …"` field.
- **Updating goldens:** only via `tools/ci/update_goldens.py`, with the reason in the PR and a `BUILD_PLAN.md`
  §6 row (CLAUDE.md). Reviewer checks: did the metric move in the direction the PR claims; did *unrelated*
  goldens move too (→ accidental global change); did tolerances widen instead of values changing.
- **Drift budget per metric:** keep tolerance ≥ 3× observed cross-platform spread recorded at golden creation
  (store the three CI platforms' values in the JSON so the spread is visible), but never wider than the
  perceptual JND the PRD cites (e.g. RT60 ±5 %, level ±0.5 dB).

---

## 7. JSON Schema 2020-12 and python-jsonschema; contract versioning

- **Current draft**: "The current version is 2020-12! The previous version was 2019-09."
  `$schema: "https://json-schema.org/draft/2020-12/schema"`. https://json-schema.org/specification (2026-11-04).
- **Validator class**: `jsonschema.Draft202012Validator` (also Draft201909/7/6/4/3). `validate(instance, schema)`
  picks the class from `$schema` "if the schema has a $schema keyword containing a known meta-schema", else the
  latest draft; it also "will first verify that the provided schema is itself valid". Use
  `Draft202012Validator.check_schema(schema)` in a test so a malformed schema fails loudly, and
  `Draft202012Validator(schema, format_checker=Draft202012Validator.FORMAT_CHECKER)` because "By default, as per
  the specification, no validation is enforced" for `format`; a missing optional dependency makes format checks
  silently pass. Latest docs 4.26.0. https://python-jsonschema.readthedocs.io/en/stable/validate/ (2026-11-04).
  Use `iter_errors()` to report *all* violations in a fixture test, not just the first.
- **`additionalProperties: false` vs `unevaluatedProperties`**: "additionalProperties only recognizes properties
  declared in the same subschema as itself" — combined with `allOf`/`$ref` it rejects properties declared in
  the other subschema; `unevaluatedProperties: false` "can recognize properties declared in subschemas" (2019-09+).
  For the SceneDescription contract: closed objects (`additionalProperties: false` on leaf objects, or
  `unevaluatedProperties: false` where `$ref`+`allOf` composition is used) so typos are rejected and unknown
  future keys force a `contractVersion` bump. https://json-schema.org/understanding-json-schema/reference/object (2026-11-04).
- **Numbers**: `type: number|integer`, `minimum`/`maximum`, `exclusiveMinimum`/`exclusiveMaximum` (numeric
  values in 2020-12, not booleans), `multipleOf`. **Arrays**: `minItems`/`maxItems`, `items` (2020-12 replaces
  tuple `items` with `prefixItems` + `items`), `uniqueItems`, `contains`/`minContains`. `enum` for closed string
  sets (materials, source types); `const` for `contractVersion` major. `required` arrays; `null` does not count as
  absent. (Keyword facts: from memory, consistent with the page above.)
- **Limits**: JSON Schema cannot express geometry (listener inside room, non-self-intersecting polygon, source
  not on a wall, absorption ≤ 1 per band *and* band array length == `kOctaveBandsHz` size can be done with
  `minItems/maxItems`+`maximum`, but cross-field relations like `x < room.width` cannot) → those live in
  `src/contract` validation with their own fixtures under `tests/scenes/invalid/`. Schema and C++ validator must
  agree: a fixture rejected by one and accepted by the other is a bug.
- **"MAJOR.MINOR" contract semver**: MINOR = additive, backward-compatible (new optional field with a default,
  new enum value only if old readers tolerate unknown → otherwise MAJOR); MAJOR = anything that makes an old
  file invalid or changes a field's meaning/units/axes (AQ1). Readers accept `major == theirs && minor <= theirs`,
  writers emit their own version; migration tests per MAJOR bump (CLAUDE.md rule). semver.org §7/§8 define MINOR
  "backward compatible" and MAJOR "incompatible API changes" — https://semver.org/ (unverified, from memory).

---

## 8. Python tooling pinning

- **requirements.txt** with `==` pins for every direct *and* transitive package (`pip freeze` or `pip-compile`
  output), one file per purpose (`requirements.txt` vs `requirements-dev.txt`). Pip hash-checking mode: add
  `--hash=sha256:…` per requirement; "Specifying `--hash` against *any* requirement will activate this mode
  globally", after which every requirement and dependency needs a hash or pip errors; force with
  `pip install --require-hashes -r …`; all requirements must be `==` pinned; sha256 recommended, md5/sha1 rejected.
  Generate with `pip-compile --generate-hashes` (pip-tools) or `pip hash`. Multi-platform wheels need one hash
  line per wheel (pip-compile emits all). https://pip.pypa.io/en/stable/topics/secure-installs/ (2026-11-04).
- **`python -I`** (isolated mode): ignores `PYTHONPATH`/`PYTHON*` env vars, the user site-packages, and does not
  prepend the script's directory to `sys.path` — use it when running analysis over downloaded/untrusted
  directories (a planted `json.py` can't shadow stdlib). (Semantics: from memory;
  https://docs.python.org/3/using/cmdline.html#cmdoption-I.)
- **pytest config**: put `[tool.pytest.ini_options]` in `tools/acoustics/pyproject.toml`: `testpaths`,
  `addopts = "-ra -q --strict-markers --import-mode=importlib"`, `filterwarnings = ["error"]` (turn DeprecationWarnings
  from numpy/scipy into failures early), `markers` for `slow`/`needs_bras`. Pin pytest major (9.x as of
  2026-10-27). (From memory.)
- **pyroomacoustics compilation.** The accelerated simulator (`libroom`, a pybind11 C++ extension) is compiled at
  install; README: minimal deps numpy, scipy, Cython, pybind11; without a compiler it "still installs but falls
  back to the slower pure Python implementation" (the README's "Windows wheels for Python 3.5 and 3.6" text is
  stale). PyPI 0.10.1 (2026-05-01) ships **binary wheels for cp39–cp314: manylinux_2_27 x86_64 (all),
  manylinux_2_26 aarch64 (cp311+), macosx universal2 (10.9/10.13/10.15 minimum), win_amd64** → on GitHub's
  ubuntu-24.04/macos-14/windows-2022 runners with Python 3.12 no compiler is needed. Pin the Python minor in
  `setup-python` so the wheel resolves; if a new Python has no wheel pip silently builds the sdist (needs a C++17
  compiler, ~4 GB RAM) or falls back to pure Python (10–100× slower, different numerics in corner cases).
  Sources: https://pypi.org/pypi/pyroomacoustics/json (2026-11-04); https://github.com/LCAV/pyroomacoustics (2026-11-04).
- **Reproducibility**: `PYTHONHASHSEED=0`, fixed numpy seeds (`np.random.default_rng(seed)`), and pin numpy major
  (2.5.x) because `np.random` legacy and float printing changed across 1.x→2.x. soundfile wheels bundle
  libsndfile — a libsndfile version change can alter float↔int dither/clipping of written WAVs (write float32).

---

## 9. Windows / MSVC specifics

- **`/fp:precise` is the default**; VS 2022: "Floating-point contractions aren't generated by default under
  `/fp:precise`" (earlier versions contracted by default); `/fp:fast` reassociates, ignores NaN semantics, enables
  `/fp:contract`; `/fp:strict` adds `fenv_access`. Never set `/fp:fast` (or `-ffast-math`) on `src/sim`: it breaks
  `x != x` NaN checks and reproducibility. If GCC/Clang legs use `-ffp-contract=off`, add `/fp:contract-`-style
  parity by leaving MSVC default; document the choice.
  https://learn.microsoft.com/en-us/cpp/build/reference/fp-specify-floating-point-behavior?view=msvc-170 (2026-11-04).
- **`/arch`**: x64 default is SSE2; `/arch:AVX2` changes codegen for *all* TUs and will crash on older CPUs; PFFFT
  picks SSE at compile time, so a plugin shipping to arbitrary x64 hosts should stay at `/arch:SSE2`
  (or dispatch at runtime). (From memory; https://learn.microsoft.com/en-us/cpp/build/reference/arch-x64.)
- **`M_PI`**: "Standard C and C++ don't define these math constants. To use them, define `_USE_MATH_DEFINES` and
  include `<cmath>`"; with `/Zc:cmath` it has no effect → include `<corecrt_math_defines.h>`. Prefer C++20
  `std::numbers::pi` / `pi_v<float>` from `<numbers>` everywhere; grep the diff for `M_PI`.
  https://learn.microsoft.com/en-us/cpp/c-runtime-library/math-constants?view=msvc-170 (2026-11-04).
- **`/Zc:__cplusplus`**: "By default, Visual Studio always returns the value `199711L`"; `/permissive-` does
  *not* enable it; with it and `/std:c++20` → `202002L`; `_MSVC_LANG` always reports the real level. JUCE's CMake
  adds `/Zc:__cplusplus`? — not verified; check `JUCEUtils.cmake` or set it in `SpatialCompilerFlags`. Any
  `#if __cplusplus >= 202002L` in `src/` silently fails on MSVC without it.
  https://learn.microsoft.com/en-us/cpp/build/reference/zc-cplusplus?view=msvc-170 (2026-11-04).
- **`/permissive-`** (strict conformance: two-phase lookup, no MS extensions) — JUCE builds with it; enable
  globally so code that compiles on GCC/Clang also compiles on MSVC. `/W4 /WX` for warnings-as-errors; `/EHsc`;
  `/utf-8` so string literals with non-ASCII are not mangled. (From memory.)
- **Long paths**: Windows MAX_PATH 260 bites FetchContent (`build/release/_deps/juce-src/modules/...`) and
  JUCE's artefact folders; CI mitigations: short build dir (`build/` not `out/build/x64-Release/`), git
  `core.longpaths true`, enable long paths in the registry on self-hosted runners. (From memory.)
- **Ninja + MSVC env**: `cl.exe` is only on PATH inside a VS developer shell; CI uses `ilammy/msvc-dev-cmd` with
  `arch: x64` before `cmake --preset`; the preset must not hard-code `CMAKE_CXX_COMPILER=cl` with a path. Set
  `CMAKE_MSVC_RUNTIME_LIBRARY` explicitly (JUCE plugins use static `/MT` by default via `JUCE_...`? — verify in
  the CMake; mismatched CRT across libs = link errors or two heaps).
- **`std::aligned_alloc` is absent on MSVC** (C11 `aligned_alloc` is not provided because MSVC's `free` cannot
  release aligned memory): use `_aligned_malloc(size, alignment)` + `_aligned_free`
  ("Don't use `free`, which doesn't reclaim the aligned memory correctly"), or portable C++17
  `::operator new(size, std::align_val_t{64})` / `std::align_val_t` delete, or JUCE `juce::dsp::SIMDRegister`
  aligned containers. PFFFT needs 16-byte (SSE) / 32-byte (AVX) alignment → wrap `pffft_aligned_malloc`.
  https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/aligned-malloc?view=msvc-170 (2026-11-04);
  MSVC omission: (unverified, from memory; MS STL conformance notes list `aligned_alloc` as not implemented).
- **`std::mt19937` is bit-exact across implementations; distributions are not**: `std::uniform_real_distribution`,
  `std::normal_distribution`, `std::uniform_int_distribution` are implementation-defined (libstdc++, libc++ and
  MSVC STL use different algorithms) → a `tailSeed`-driven tail that uses `std::normal_distribution` gives
  different noise on each platform. Use the raw engine output with your own fixed mapping (e.g. `(x >> 8) *
  2^-24`, Box–Muller written in-repo) so renders match across OSes within float tolerance. (From memory.)
- **CRLF / clang-format**: set `.gitattributes` `* text=auto eol=lf` (and `*.sh text eol=lf`, `*.bat eol=crlf`)
  so Windows checkouts don't produce CRLF diffs; `check_format.sh` under Git Bash must call `clang-format
  --style=file` and compare with `--dry-run --Werror`; clang-format 18 pinned in CI (repo), so local runs with a
  different major can disagree — print the version in the script. (From memory.)
- MSVC has ASan (`/fsanitize=address`, VS 2019 16.9+) but no UBSan/TSan; the repo's asan/tsan presets are Linux-only
  for that reason. (ASan on MSVC: unverified, from memory.)

---

## 10. macOS specifics

- **Universal binaries**: `CMAKE_OSX_ARCHITECTURES="arm64;x86_64"` at configure time (must be set *before*
  `project()`/first `FetchContent` so JUCE and PFFFT get both slices; PFFFT's SSE vs NEON paths compile per
  slice). `CMAKE_OSX_DEPLOYMENT_TARGET` ≥ 10.13 for JUCE 8 (verify in JUCE's `CMakeLists`). Test the x86_64 slice
  on Apple Silicon with `arch -x86_64 ./spatial_tests` and `arch -x86_64 pluginval …` (Rosetta); `lipo -info` and
  `file` to assert both slices in CI. (From memory.)
- **Codesign with hardened runtime and timestamp**:
  `codesign --force --deep --options runtime --timestamp --sign "Developer ID Application: <Name> (<TEAMID>)"
  SpatialScene.vst3` (and `.component`, `.app`); verify `codesign -vvv --deep --strict` and `codesign -dvv`
  shows a `Timestamp=` line ("macOS accepts only one secure timestamp server"; generating one "requires internet
  access"). No `get-task-allow` entitlement in release builds. Apple:
  https://developer.apple.com/documentation/security/resolving-common-notarization-issues (data JSON read 2026-11-04).
- **Notarisation sequence** (Apple "Customizing the notarization workflow", 2026-11-04):
  1. `xcrun notarytool store-credentials "notarytool-password" --apple-id … --team-id … --password <app-specific>`
     (App Store Connect requires 2FA → app-specific password).
  2. `ditto -c -k --keepParent bundle.vst3 bundle.zip` then
     `xcrun notarytool submit bundle.zip --keychain-profile "notarytool-password" --wait` ("exit only after the
     Notary service finishes"); save the submission id.
  3. `xcrun notarytool log <id> --keychain-profile … developer_log.json` — "Always check the log file, even if
     notarization succeeds".
  4. `xcrun stapler staple bundle.vst3` (works on apps, bundles, dmg, flat pkg; "doesn't work on ZIP archives" —
     staple each item, then re-zip).
  5. Verify: `xcrun stapler validate bundle.vst3`; Gatekeeper: `spctl -a -vv -t install bundle.vst3` (plug-in
     bundles are assessed as "install" type, expect `accepted … source=Notarized Developer ID`);
     `spctl -vvv --assess --type exec App.app` for the standalone. (spctl forms: from memory + Apple page.)
  For an installer: Developer ID *Installer* cert, `productbuild --sign`, `pkgutil --check-signature`.
- **AU registration on CI/dev machines**: copy to `~/Library/Audio/Plug-Ins/Components/`, then
  `killall -9 AudioComponentRegistrar` to flush the cache, then `auval -v aufx Spsc Mkrf` (type/subtype/manu
  from the repo); retry once after a sleep because registration lags on fresh runners (repo's ci.yml does this).
  `auval -a` lists registered components; `-strict` adds extra checks (unverified, from memory).
- **AU in Logic/GarageBand**: AUv2 bundles need no sandbox entitlement of their own; the host carries
  `com.apple.security.cs.disable-library-validation` to load third-party code, and GarageBand/Logic may host
  AUv2 out-of-process via `AUHostingService` (sandboxed XPC), so the plugin must not rely on the host process's
  file access, must be signed with hardened runtime, and must avoid `MAP_JIT`/dyld-env tricks unless the matching
  `com.apple.security.cs.*` entitlement is added. AUv3 (app extension) *requires* `com.apple.security.app-sandbox`.
  Sources: Apple QA1483 (2012) https://developer.apple.com/library/mac/qa/qa1483/_index.html and forum threads
  (2026-11-04); Logic-specific behaviour (unverified, from memory).
- **Runner note**: `macos-14` is Apple Silicon; x86_64 slices only run through Rosetta there, and TSan/ASan on
  Rosetta-translated binaries is unsupported → run sanitizer legs natively (Linux) only.

---

## 11. Reviewer's checklist (CMake, CI, deps, licences, docs, Python, tests)

CMake / dependencies
1. Does every `FetchContent_Declare` pin an immutable ref (commit SHA, or `URL`+`URL_HASH SHA256`)? *Catches tag
   moves/deletions and supply-chain swaps.*
2. If `GIT_SHALLOW TRUE` is present, is `GIT_TAG` a tag/branch (hashes are rejected)? *Catches a configure-time
   clone failure that only appears on a clean machine.*
3. Is `SYSTEM` on each third-party Declare and is `cmake_minimum_required ≥ 3.25`? *Catches `-Werror` breaking on
   warnings inside JUCE/Catch2 after a compiler upgrade.*
4. Any new `FetchContent_Populate(name)` single-arg call? *Deprecated (3.30, CMP0169); use MakeAvailable.*
5. Does the dependency change also touch `docs/THIRD_PARTY.md` (version, licence, pull-in method)? *Repo rule;
   catches undocumented licence obligations.*
6. Did a pin change update the CI cache key inputs (`hashFiles('cmake/**')` already covers it)? *Catches stale
   `_deps` restored over a new tag.*
7. Any vendored third-party source under `src/`, `resources/`, or a committed `_deps/`? *Catches unpinned,
   unlicensed copies.*
8. Are compiler flags (`/fp`, `-ffast-math`, `/arch`, `-march=native`) unchanged for `src/sim`? *Catches
   reproducibility loss and crashes on older CPUs.*
9. Does any C++ use `M_PI`, `aligned_alloc`, `__cplusplus` checks, VLAs, `#pragma once` + MSVC extensions?
   *Catches Windows build breaks hidden by Linux-only local builds.*
10. Does `src/sim` or `src/module3d` include the other, or JUCE? *Boundary rule (`check_boundaries.py`).*

CI / GitHub Actions
11. Are actions pinned by full SHA with a `# vX.Y.Z` comment, and are versions current (checkout v7, cache v6,
    upload-artifact v7)? *Catches mutable-tag supply chain risk and deprecated Node runtimes.*
12. Does a new workflow set top-level `permissions:` to least privilege? *Catches token over-scoping.*
13. Does `concurrency.cancel-in-progress` apply to release/tag workflows? *Catches a cancelled signing run mid-way.*
14. Is `fail-fast: false` kept on the OS matrix? *Catches hidden per-OS failures.*
15. Do `run:` steps interpolate untrusted context (`${{ github.event.* }}`) directly? *Script injection.*
16. Are secrets only used in `env:`/`with:`, never echoed, and does release use an `environment:` with
    reviewers? *Catches leaked notarisation/signing credentials.*
17. Does any `schedule:` workflow also have `workflow_dispatch:`? *Otherwise untestable until it fires on main.*
18. Do big artifacts set `retention-days` and `if-no-files-found: error`? *Quota and silent-empty uploads.*
19. Are Linux test/pluginval steps wrapped in `xvfb-run -a` (and does `ctest` for asan/tsan presets too)?
    *JUCE GUI init without a display aborts.*
20. Does the sanitizer job use `-fno-sanitize-recover=all` (or `halt_on_error`) so UB fails the job? *Catches
    green CI with red logs.*

Licences / docs
21. Does the PR add a dependency whose licence requires binary attribution (PFFFT/FFTPACK, VST3 SDK MIT,
    AudioUnitSDK Apache 2.0, Inno Setup notice) and is the About/installer notice list updated? *Catches
    shipping without required notices.*
22. Any GPL/AGPL/LGPL code linked into the plugin (not just run as a tool)? *Copyleft contamination of a
    closed-source product.*
23. Is the JUCE tier statement in THIRD_PARTY.md consistent with the EULA in force (Starter ≤ $20k trailing
    12-month revenue/funding, company-wide for entities; no splash screen)? *Catches stale "splash screen" and
    wrong-threshold notes.*
24. Does the docs change keep CLAUDE.md "Build and test" commands runnable (presets, script names)? *Rule in
    CLAUDE.md.*
25. Contract change: `contractVersion` bumped, `scene-v1.schema.json` + `docs/contract/README.md` updated,
    valid/invalid fixtures added, migration test if MAJOR? *Repo hard rule.*

Python tooling
26. Is every requirement `==`-pinned (and hashed if hash mode is adopted), incl. transitive? *Non-reproducible
    analysis numbers.*
27. Does the Python minor in CI have binary wheels for pyroomacoustics/numpy/scipy (cp312 today)? *Silent
    source builds or pure-Python fallback.*
28. Are downloaded datasets verified by checksum and never committed (BRAS, SOFA)? *Repo rule and licence risk.*
29. Are scripts that read downloaded data run with `python -I` and from outside the download dir? *Module
    shadowing.*
30. Does `pytest` config enable `--strict-markers` and `filterwarnings=error`, and are random seeds fixed? *Flaky
    or silently deprecated analysis code.*
31. Does the schema validator use `Draft202012Validator` + `check_schema` + `FORMAT_CHECKER`, and does
    `$schema` name 2020-12? *Format checks silently disabled; wrong draft semantics for `items`/`exclusiveMinimum`.*

Tests / goldens
32. Does each new DSP behaviour have an automated check against an independent reference (analytic, second
    implementation, measured)? *Tautological tests.*
33. Did any tolerance widen, golden regenerate, or `[!mayfail]`/`SKIP` appear — and is there a §6 change-log
    row plus `update_goldens.py` usage in the PR? *Hidden regressions.*
34. Are float comparisons `WithinAbs`/`WithinRel`/`WithinULP` with justified margins, never `==` or `Approx`?
    *Platform drift flakes or meaningless passes.*
35. Does every `GENERATE` have a `CAPTURE`, and is the RNG seed printed/fixed? *Unreproducible failures.*
36. Do tests avoid cwd-relative paths, sleeps, wall-clock, and shared mutable state across sections? *CI-only
    failures.*
37. Is the test discovery `PRE_TEST` (or build-time discovery wrapped in xvfb) and is the JUnit reporter uploaded?
    *Headless discovery crash; invisible failures.*
38. Does the golden JSON record source (analytic/pyroomacoustics/self), per-platform observed values and the
    tolerance rationale? *Unexplained numbers nobody can re-derive.*
39. Does a benchmark gate CI on timing from shared runners? *Noise-driven flakes; report instead.*
40. Does the test touch `processBlock` paths with allocation tracking enabled (Phase 06 test) when audio-thread
    code changed? *Real-time safety regressions.*

---

## Sources index (all accessed 2026-11-04 unless noted)

- JUCE: https://juce.com/legal/juce-8-licence/ · https://juce.com/legal/juce-9-licence/ · https://juce.com/get-juce/ ·
  https://github.com/juce-framework/JUCE/releases · https://raw.githubusercontent.com/juce-framework/JUCE/8.0.17-security/LICENSE.md ·
  https://forum.juce.com/t/juce-8-is-available-now/61809 · https://forum.juce.com/t/amendments-to-the-juce-end-user-licence-agreement-for-juce-8/61265 ·
  https://forum.juce.com/t/juce-9-no-pricing-or-eula-changes/69000 · https://forum.juce.com/t/juce-9-0-5-8-0-17-security-7-0-14-security/69810 ·
  https://forum.juce.com/t/do-i-need-the-starter-or-indie-licence/69021
- PFFFT: https://raw.githubusercontent.com/marton78/pffft/master/LICENSE.txt · https://bitbucket.org/jpommier/pffft/raw/master/pffft.c · https://github.com/marton78/pffft
- nlohmann/json: https://raw.githubusercontent.com/nlohmann/json/develop/LICENSE.MIT · https://github.com/nlohmann/json/releases
- dr_wav: https://raw.githubusercontent.com/mackron/dr_libs/master/dr_wav.h
- Catch2: https://raw.githubusercontent.com/catchorg/Catch2/devel/LICENSE.txt · docs/cmake-integration.md · docs/command-line.md ·
  docs/comparing-floating-point-numbers.md · docs/benchmarks.md · docs/generators.md · docs/logging.md · docs/configuration.md
- pluginval: https://raw.githubusercontent.com/Tracktion/pluginval/develop/LICENSE · https://github.com/Tracktion/pluginval/releases
- PyPI JSON: https://pypi.org/pypi/{pyroomacoustics,numpy,scipy,soundfile,pytest,jsonschema,pyloudnorm,sofar,matplotlib}/json · https://github.com/LCAV/pyroomacoustics
- Inno Setup: https://raw.githubusercontent.com/jrsoftware/issrc/main/license.txt · https://jrsoftware.org/isinfo.php · https://github.com/jrsoftware/issrc/releases
- CMake: https://cmake.org/cmake/help/latest/module/FetchContent.html · https://cmake.org/cmake/help/latest/module/ExternalProject.html
- GitHub: https://docs.github.com/en/actions/security-for-github-actions/security-guides/security-hardening-for-github-actions ·
  https://docs.github.com/en/actions/using-jobs/using-concurrency · https://docs.github.com/en/actions/guides/storing-workflow-data-as-artifacts ·
  https://docs.github.com/en/actions/writing-workflows/choosing-when-your-workflow-runs/events-that-trigger-workflows ·
  https://github.com/{actions/checkout,actions/cache,actions/upload-artifact,hendrikmuhs/ccache-action,ilammy/msvc-dev-cmd}/releases
- Sanitizers: https://clang.llvm.org/docs/AddressSanitizer.html · https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html · https://clang.llvm.org/docs/ThreadSanitizer.html
- JSON Schema: https://json-schema.org/specification · https://json-schema.org/understanding-json-schema/reference/object · https://python-jsonschema.readthedocs.io/en/stable/validate/
- pip: https://pip.pypa.io/en/stable/topics/secure-installs/
- MSVC: https://learn.microsoft.com/en-us/cpp/build/reference/fp-specify-floating-point-behavior?view=msvc-170 ·
  https://learn.microsoft.com/en-us/cpp/c-runtime-library/math-constants?view=msvc-170 · https://learn.microsoft.com/en-us/cpp/build/reference/zc-cplusplus?view=msvc-170 ·
  https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/aligned-malloc?view=msvc-170
- Apple: https://developer.apple.com/documentation/security/customizing-the-notarization-workflow ·
  https://developer.apple.com/documentation/security/resolving-common-notarization-issues · https://developer.apple.com/library/mac/qa/qa1483/_index.html
