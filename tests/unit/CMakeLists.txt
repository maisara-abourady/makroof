# spatial_tests: Catch2 v3 unit tests, one file per source unit, discovered by CTest.
include(Catch)

add_executable(spatial_tests
               test_smoke.cpp
               ContractFixtures.h
               test_contract_roundtrip.cpp
               test_contract_validation.cpp
               test_contract_version.cpp
               test_engine.cpp
               IsmTestUtil.h
               test_air_absorption.cpp
               test_image_sources.cpp
               test_band_renderer.cpp
               test_offline_render.cpp
               test_cli.cpp
               test_rng.cpp
               test_fft.cpp
               test_tail_decay.cpp
               test_mixing_time.cpp
               test_noise_tail.cpp
               test_hybrid_ir.cpp
               ConvTestUtil.h
               ../support/AllocationTracker.h
               ../support/AllocationTracker.cpp
               ../support/FailFast.cpp
               test_fail_fast.cpp
               test_partitioned_convolver.cpp
               test_crossfading_convolver.cpp
               test_realtime_engine.cpp)

# tests/support: the AllocationTracker replaces the global operator new / delete of this binary
# (Phase 06, zero-allocation checks of the real-time convolver).
target_include_directories(spatial_tests PRIVATE "${PROJECT_SOURCE_DIR}/tests/support")

# The contract tests read the fixtures in tests/scenes/ (valid/ and invalid/).
target_compile_definitions(spatial_tests PRIVATE SPATIAL_SCENES_DIR="${PROJECT_SOURCE_DIR}/tests/scenes")

target_link_libraries(spatial_tests
                      PRIVATE Catch2::Catch2WithMain
                              spatial::contract
                              spatial::sim
                              spatial::cli
                              spatial::module3d
                              spatial::warnings)

if(SPATIAL_BUILD_PLUGIN)
    # The pass-through null test links the plugin's shared-code target, so it exercises the same
    # AudioProcessor the VST3/AU/Standalone wrappers call.
    target_sources(spatial_tests PRIVATE test_passthrough.cpp)
    target_link_libraries(spatial_tests PRIVATE SpatialScene)
    # Same trick JUCE uses for its format wrappers: see the module headers and the plugin's
    # compile definitions (JucePlugin_*, module config) without compiling the modules a second time.
    target_include_directories(spatial_tests PRIVATE $<TARGET_PROPERTY:SpatialScene,INCLUDE_DIRECTORIES>)
    target_compile_definitions(spatial_tests PRIVATE
                               $<TARGET_GENEX_EVAL:SpatialScene,$<TARGET_PROPERTY:SpatialScene,COMPILE_DEFINITIONS>>)
endif()

catch_discover_tests(spatial_tests
                     DISCOVERY_MODE PRE_TEST
                     REPORTER console)

# Phase 06b scope 5: a crashing test must end the binary promptly. The hidden crash probe
# (test_fail_fast.cpp) aborts while another thread holds the stdout lock; run_crash_probe.cmake passes
# when it ends abnormally within 30 s and prints the time it took (a hang fails at the limit).
add_test(NAME fail_fast_crash_probe
         COMMAND ${CMAKE_COMMAND} -DPROBE=$<TARGET_FILE:spatial_tests> -DLIMIT=30 -P
                 "${CMAKE_CURRENT_SOURCE_DIR}/run_crash_probe.cmake")
set_tests_properties(fail_fast_crash_probe PROPERTIES TIMEOUT 60)
