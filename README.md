# makroof — Spatial Scene VST

A commercial VST3/AU plugin that renders a track as if it were played in a 3D space the user designs.
The user builds the scene (room, materials, listener and source positions); the plugin simulates what
that space does to the sound and renders it at the listener's position.

Two parts joined by a versioned contract: a **3D Module** (scene building) and a **Simulator**
(acoustic simulation and rendering). Built with JUCE 8, C++20 and CMake.

## Documents

- Requirements: [docs/PRD.md](docs/PRD.md)
- Build plan, assumptions and phase status: [docs/BUILD_PLAN.md](docs/BUILD_PLAN.md)
- Per-phase instructions: [docs/phases/](docs/phases/)
- Working rules for sessions and the build commands: [CLAUDE.md](CLAUDE.md)
- Third-party dependencies and licences: [docs/THIRD_PARTY.md](docs/THIRD_PARTY.md)

## Quick start

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

Presets: `debug`, `release`, and on Linux `asan` (ASan + UBSan) and `tsan`. Binaries land in
`build/<preset>/`; the plugin bundles in `build/<preset>/SpatialScene_artefacts/<Config>/`.
On Windows run the commands from an "x64 Native Tools Command Prompt for VS 2022" so that Ninja finds
MSVC. Linux build dependencies are listed in [CLAUDE.md](CLAUDE.md).

## Status

Phases 00 (scaffolding, CI, pluginval, pass-through plugin) and 01 (scene contract v1, spec in
[docs/contract/README.md](docs/contract/README.md)). See the status table in
[docs/BUILD_PLAN.md](docs/BUILD_PLAN.md) §0.
