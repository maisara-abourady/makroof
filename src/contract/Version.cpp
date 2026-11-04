#include "contract/Version.h"

#include <cstddef>

namespace contract {

const char* contractVersion() noexcept
{
    return kContractVersion;
}

namespace {

// Parses one version component. Returns -1 when the text is not a valid component.
int parseComponent(std::string_view text) noexcept
{
    constexpr std::size_t kMaxDigits = 9; // fits in int on every platform
    if (text.empty() || text.size() > kMaxDigits)
        return -1;
    if (text.size() > 1 && text.front() == '0')
        return -1;
    int value = 0;
    for (const char c : text)
    {
        if (c < '0' || c > '9')
            return -1;
        value = value * 10 + (c - '0');
    }
    return value;
}

} // namespace

std::optional<ContractVersion> parseContractVersion(std::string_view text) noexcept
{
    const auto dot = text.find('.');
    if (dot == std::string_view::npos)
        return std::nullopt;
    const int majorPart = parseComponent(text.substr(0, dot));
    const int minorPart = parseComponent(text.substr(dot + 1));
    if (majorPart < 0 || minorPart < 0)
        return std::nullopt;
    return ContractVersion{majorPart, minorPart};
}

std::string toString(ContractVersion version)
{
    return std::to_string(version.majorVersion) + "." + std::to_string(version.minorVersion);
}

} // namespace contract
