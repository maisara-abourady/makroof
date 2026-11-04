# spatial_tests: Catch2 v3 unit tests, one file per source unit, discovered by CTest.
include(Catch)

add_executable(spatial_tests
               test_smoke.cpp)

target_link_libraries(spatial_tests
                      PRIVATE Catch2::Catch2WithMain
                              spatial::contract
                              spatial::sim
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
