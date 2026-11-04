# render_cli: offline renders for tests and listening packs. JUCE-free: contract + sim + dr_wav.
#
# The command-line logic lives in the spatial_cli library (runCli()), so the Catch2 tests can run it
# in-process on every OS; main.cpp only forwards argv.
add_library(spatial_cli STATIC
            Cli.h
            Cli.cpp
            WavIO.h
            WavIO.cpp)
add_library(spatial::cli ALIAS spatial_cli)
target_include_directories(spatial_cli PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")
target_compile_features(spatial_cli PUBLIC cxx_std_20)
target_link_libraries(spatial_cli
                      PUBLIC spatial::contract
                             spatial::sim
                      PRIVATE spatial::dr_wav
                              spatial::warnings)

add_executable(render_cli main.cpp)
target_link_libraries(render_cli
                      PRIVATE spatial::cli
                              spatial::warnings)
# At the top of the binary dir, as documented in CLAUDE.md: build/<preset>/render_cli[.exe].
set_target_properties(render_cli PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
