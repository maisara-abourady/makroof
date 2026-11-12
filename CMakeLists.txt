# Spatial Scene VST — top-level build.
#
# Targets (see docs/BUILD_PLAN.md §1 and CLAUDE.md "Repository layout"):
#   spatial_contract  static lib, no JUCE
#   spatial_sim       static lib, no JUCE, depends on spatial_contract only
#   spatial_module3d  static lib, no JUCE, depends on spatial_contract only
#   spatial_plugin_core  static lib, no JUCE: the plugin's scene -> IR pipeline (contract, sim, module3d)
#   SpatialScene      JUCE plugin (VST3, AU on Apple, Standalone)
#   render_cli        console executable (offline renders)
#   spatial_tests     Catch2 unit tests, registered with CTest
cmake_minimum_required(VERSION 3.25)

project(SpatialScene
        VERSION 0.0.1
        DESCRIPTION "Renders a track as if it were played in a 3D space the user designs"
        LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(SPATIAL_WERROR "Treat compiler warnings as errors (CI sets this ON)" OFF)
option(SPATIAL_BUILD_PLUGIN "Build the JUCE plugin and the tests that depend on it" ON)
option(SPATIAL_BUILD_TESTS "Build the Catch2 unit tests" ON)
# Phase-07c-1 condition 11: the host-trace diagnostic build (src/plugin/core/HostTrace.h). Never ON in a
# release artefact (tools/ci/test_host_trace.py checks the presets and the workflows).
option(SPATIAL_HOST_TRACE "Diagnostic build: log every host entry point of the plugin (never released)" OFF)
option(SPATIAL_USE_CCACHE "Use ccache as the compiler launcher when it is available" ON)
set(SPATIAL_SANITIZER "" CACHE STRING "Sanitizers to enable: empty, 'address,undefined' or 'thread'")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# Embedded (/Z7) debug info on MSVC so that ccache can cache object files. CMP0141 is NEW from 3.25.
set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug,RelWithDebInfo>:Embedded>")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

include(SpatialCcache)
include(SpatialWarnings)
include(SpatialSanitizers)
include(SpatialDependencies)

if(SPATIAL_BUILD_TESTS)
    enable_testing()
endif()

add_subdirectory(src/contract)
add_subdirectory(src/sim)
add_subdirectory(src/module3d)
add_subdirectory(src/cli)
add_subdirectory(src/plugin/core)

if(SPATIAL_BUILD_PLUGIN)
    # Included (not add_subdirectory) so that JUCE puts the bundles in build/<preset>/SpatialScene_artefacts/.
    include(src/plugin/CMakeLists.txt)
endif()

if(SPATIAL_BUILD_TESTS)
    add_subdirectory(tests/unit)
endif()
