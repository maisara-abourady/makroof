# Third-party dependencies, all pinned. Every entry here must have a row in docs/THIRD_PARTY.md.
include(FetchContent)

set(FETCHCONTENT_QUIET OFF)

# JUCE 8 — pinned release tag. Change it only together with docs/THIRD_PARTY.md.
set(SPATIAL_JUCE_TAG "8.0.17-security")
# Catch2 v3 — pinned release tag.
set(SPATIAL_CATCH2_TAG "v3.16.1")
# nlohmann/json — pinned release tag. Header-only; used by spatial_contract (always built).
set(SPATIAL_NLOHMANN_JSON_TAG "v3.12.0")

FetchContent_Declare(nlohmann_json
                     GIT_REPOSITORY https://github.com/nlohmann/json.git
                     GIT_TAG ${SPATIAL_NLOHMANN_JSON_TAG}
                     GIT_SHALLOW TRUE
                     SYSTEM)
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(nlohmann_json)

if(SPATIAL_BUILD_PLUGIN)
    FetchContent_Declare(JUCE
                         GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
                         GIT_TAG ${SPATIAL_JUCE_TAG}
                         GIT_SHALLOW TRUE
                         GIT_PROGRESS TRUE
                         SYSTEM)
    # JUCE builds its own helper tool (juceaide) and example targets; keep the extras off.
    set(JUCE_BUILD_EXTRAS OFF CACHE BOOL "" FORCE)
    set(JUCE_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(JUCE_ENABLE_MODULE_SOURCE_GROUPS ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(JUCE)
endif()

if(SPATIAL_BUILD_TESTS)
    FetchContent_Declare(Catch2
                         GIT_REPOSITORY https://github.com/catchorg/Catch2.git
                         GIT_TAG ${SPATIAL_CATCH2_TAG}
                         GIT_SHALLOW TRUE
                         SYSTEM)
    FetchContent_MakeAvailable(Catch2)
    list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
endif()
