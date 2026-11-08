# Third-party dependencies, all pinned. Every entry here must have a row in docs/THIRD_PARTY.md.
include(FetchContent)

set(FETCHCONTENT_QUIET OFF)

# JUCE 8 — pinned release tag. Change it only together with docs/THIRD_PARTY.md.
set(SPATIAL_JUCE_TAG "8.0.17-security")
# Catch2 v3 — pinned release tag.
set(SPATIAL_CATCH2_TAG "v3.16.1")
# nlohmann/json — pinned release tag. Header-only; used by spatial_contract (always built).
set(SPATIAL_NLOHMANN_JSON_TAG "v3.12.0")
# dr_wav (dr_libs) — single header, pinned to the commit of tag wav-0.14.5 and checked by SHA-256.
# Used by render_cli only (WAV I/O without JUCE).
set(SPATIAL_DR_WAV_COMMIT "fa931f3285ced10ace628f7f1ac951e1951e7ea6")
set(SPATIAL_DR_WAV_SHA256 "c69816d0e0ac6cab3df8bf2f42df451d4531c2bfa34f7d7a69e959e6ed399038")
# PFFFT (marton78/pffft) — pinned to the commit of release tag v1.1.0 (immutable, unlike a tag).
# Real FFT of the real-time convolver (src/sim/conv, Phase 06). Only the single-precision sources are
# compiled, into spatial_pffft below; the repository's own CMakeLists is not used.
set(SPATIAL_PFFFT_COMMIT "1fdcb508e5082052ab406d560b7c4622b8b4b0dd") # tag v1.1.0

FetchContent_Declare(nlohmann_json
                     GIT_REPOSITORY https://github.com/nlohmann/json.git
                     GIT_TAG ${SPATIAL_NLOHMANN_JSON_TAG}
                     GIT_SHALLOW TRUE
                     SYSTEM)
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(dr_wav
                     URL https://raw.githubusercontent.com/mackron/dr_libs/${SPATIAL_DR_WAV_COMMIT}/dr_wav.h
                     URL_HASH SHA256=${SPATIAL_DR_WAV_SHA256}
                     DOWNLOAD_NO_EXTRACT TRUE)
FetchContent_MakeAvailable(dr_wav)

FetchContent_Declare(pffft
                     GIT_REPOSITORY https://github.com/marton78/pffft.git
                     GIT_TAG ${SPATIAL_PFFFT_COMMIT}
                     # A directory that doesn't exist, so MakeAvailable only downloads (no add_subdirectory).
                     SOURCE_SUBDIR spatial-no-cmake)
FetchContent_MakeAvailable(pffft)
# Static, C, float only: pffft.c (SIMD: SSE1 on x86-64, NEON on arm64) and pffft_common.c (aligned
# malloc). Linked PRIVATE by spatial_sim; its header is SYSTEM so its warnings are not ours.
add_library(spatial_pffft STATIC "${pffft_SOURCE_DIR}/src/pffft.c" "${pffft_SOURCE_DIR}/src/pffft_common.c")
add_library(spatial::pffft ALIAS spatial_pffft)
target_include_directories(spatial_pffft SYSTEM PUBLIC "${pffft_SOURCE_DIR}/include/pffft")
target_compile_definitions(spatial_pffft PUBLIC PFFFT_STATIC_DEFINE)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm64|aarch64|ARM64)$" OR CMAKE_OSX_ARCHITECTURES MATCHES "arm64")
    target_compile_definitions(spatial_pffft PRIVATE PFFFT_ENABLE_NEON)
endif()
if(NOT MSVC)
    target_link_libraries(spatial_pffft PRIVATE m)
endif()
# Header-only; the implementation is compiled once in src/cli/WavIO.cpp. SYSTEM keeps its warnings out.
add_library(spatial_dr_wav INTERFACE)
add_library(spatial::dr_wav ALIAS spatial_dr_wav)
target_include_directories(spatial_dr_wav SYSTEM INTERFACE "${dr_wav_SOURCE_DIR}")

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
    # Phase 06b scope 5 (fail fast after a crash): Catch2's fatal-signal handler reports through
    # stdout and the heap, which are not async-signal-safe. A crash while another thread holds one of
    # their locks (or after heap corruption) then blocks the test binary until the 600 s ctest timeout.
    # Without the handler a SIGABRT/SIGSEGV ends the process at once; ctest runs every test case as
    # its own process (catch_discover_tests), so it still reports which test crashed.
    set(CATCH_CONFIG_NO_POSIX_SIGNALS ON CACHE BOOL "Catch2: no POSIX fatal-signal handler (phase 06b)" FORCE)
    FetchContent_Declare(Catch2
                         GIT_REPOSITORY https://github.com/catchorg/Catch2.git
                         GIT_TAG ${SPATIAL_CATCH2_TAG}
                         GIT_SHALLOW TRUE
                         SYSTEM)
    FetchContent_MakeAvailable(Catch2)
    list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
endif()
