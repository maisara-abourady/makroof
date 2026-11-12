# spatial_plugin_core: the plugin's scene -> IR -> convolution pipeline (Phase 07), JUCE-free so it is
# built and tested also with SPATIAL_BUILD_PLUGIN=OFF (the TSan job). Depends on contract, sim and
# module3d; it is the one place (with the JUCE adapter) where the 3D Module and the Simulator meet,
# through contract::SceneDescription only.
set(SPATIAL_DEFAULT_SCENE_FILE "${PROJECT_SOURCE_DIR}/tests/scenes/valid/medium_room.json")
file(READ "${SPATIAL_DEFAULT_SCENE_FILE}" SPATIAL_DEFAULT_SCENE_JSON)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${SPATIAL_DEFAULT_SCENE_FILE}")
configure_file(DefaultSceneJson.h.in "${CMAKE_CURRENT_BINARY_DIR}/generated/plugin/core/DefaultSceneJson.h" @ONLY)

add_library(spatial_plugin_core STATIC
            DiffuseSolveGate.h
            DiffuseSolveGate.cpp
            HostTrace.h
            HostTrace.cpp
            IrBuilderThread.h
            IrBuilderThread.cpp
            ScenePipeline.h
            ScenePipeline.cpp
            "${CMAKE_CURRENT_BINARY_DIR}/generated/plugin/core/DefaultSceneJson.h")
add_library(spatial::plugin_core ALIAS spatial_plugin_core)

target_include_directories(spatial_plugin_core
                           PUBLIC "${PROJECT_SOURCE_DIR}/src"
                           PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated")
target_compile_features(spatial_plugin_core PUBLIC cxx_std_20)
find_package(Threads REQUIRED)
target_link_libraries(spatial_plugin_core
                      PUBLIC spatial::contract
                             spatial::sim
                             spatial::module3d
                             Threads::Threads
                      PRIVATE spatial::warnings)
