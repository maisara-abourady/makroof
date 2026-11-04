#include "module3d/SceneModel.h"

#include "contract/Version.h"

namespace module3d {

const char* producedContractVersion() noexcept
{
    return contract::contractVersion();
}

} // namespace module3d
