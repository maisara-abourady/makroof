// render_cli: offline renders for tests and listening packs. All logic is in Cli.cpp (runCli());
// run `render_cli --help` for usage and exit codes.
#include "cli/Cli.h"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    try
    {
        const std::vector<std::string> args(argv + 1, argv + argc);
        return cli::runCli(args, std::cout, std::cerr);
    }
    catch (const std::exception& e)
    {
        std::cerr << "render_cli: internal error: " << e.what() << "\n";
        return 1;
    }
}
