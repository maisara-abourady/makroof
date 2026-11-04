#pragma once

// Version of the 3D Module -> Simulator contract (docs/contract/, Phase 01).
// Semver "major.minor": a minor bump is additive, a major bump is breaking.
// "0.0" means the contract has no types yet (Phase 00 scaffolding).
namespace contract {

inline constexpr const char* kContractVersion = "0.0";

// Returns kContractVersion. Exists so the library has a translation unit and so callers that
// cannot see the constexpr (e.g. a C ABI later) can still query it.
const char* contractVersion() noexcept;

} // namespace contract
