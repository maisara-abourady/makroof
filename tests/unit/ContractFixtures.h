#pragma once

// Helpers shared by the contract tests: locate and read the scene fixtures in tests/scenes/.
// SPATIAL_SCENES_DIR is set by tests/unit/CMakeLists.txt.
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace contract_fixtures {

inline std::filesystem::path scenesDir()
{
    return std::filesystem::path{SPATIAL_SCENES_DIR};
}

// Every *.json in tests/scenes/<subdir>, sorted, skipping sidecars whose name starts with '_'.
inline std::vector<std::filesystem::path> list(const std::string& subdir)
{
    std::vector<std::filesystem::path> files;
    for (const auto& entry : std::filesystem::directory_iterator(scenesDir() / subdir))
    {
        const auto& path = entry.path();
        if (entry.is_regular_file() && path.extension() == ".json"
            && !path.filename().string().starts_with("_"))
            files.push_back(path);
    }
    std::sort(files.begin(), files.end());
    return files;
}

inline std::string read(const std::filesystem::path& path)
{
    std::ifstream in(path, std::ios::binary);
    if (!in)
        throw std::runtime_error("cannot open " + path.string());
    std::ostringstream text;
    text << in.rdbuf();
    return text.str();
}

} // namespace contract_fixtures
