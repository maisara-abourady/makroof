// render_cli — offline renderer. Phase 00: prints the version and exits 0.
// Phase 02 adds: --scene <json> --in <wav> --out <wav>, and --ir <wav>.
#include "contract/Version.h"
#include "sim/Simulator.h"

#include <cstdio>

int main()
{
    std::printf("render_cli (SpatialScene) contract %s, simulator supports contract %s\n",
                contract::contractVersion(), sim::supportedContractVersion());
    return 0;
}
