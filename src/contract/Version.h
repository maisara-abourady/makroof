#pragma once

// Version of the 3D Module -> Simulator contract (docs/contract/README.md).
// "MAJOR.MINOR": a minor bump is additive, a major bump is breaking. The reader accepts the same
// major and any minor; a newer minor loads with a warning (unknown fields ignored), a different
// major is an error.
#include <optional>
#include <string>
#include <string_view>

namespace contract {

struct ContractVersion
{
    int majorVersion = 0;
    int minorVersion = 0;

    friend bool operator==(const ContractVersion&, const ContractVersion&) = default;
};

inline constexpr int kContractVersionMajor = 1;
inline constexpr int kContractVersionMinor = 0;
inline constexpr ContractVersion kCurrentContractVersion{kContractVersionMajor, kContractVersionMinor};
inline constexpr const char* kContractVersion = "1.0";

// Returns kContractVersion. Exists so the library has a translation unit and so callers that
// cannot see the constexpr (e.g. a C ABI later) can still query it.
const char* contractVersion() noexcept;

// Parses "MAJOR.MINOR": two non-negative decimal integers without sign, leading zeros (other than a
// lone "0") or surrounding whitespace, each at most 9 digits. Anything else returns std::nullopt.
std::optional<ContractVersion> parseContractVersion(std::string_view text) noexcept;

// Formats as "MAJOR.MINOR".
std::string toString(ContractVersion version);

} // namespace contract
