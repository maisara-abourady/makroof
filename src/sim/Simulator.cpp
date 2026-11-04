#include "sim/Simulator.h"

#include "contract/Version.h"

namespace sim {

const char* supportedContractVersion() noexcept
{
    return contract::contractVersion();
}

} // namespace sim
