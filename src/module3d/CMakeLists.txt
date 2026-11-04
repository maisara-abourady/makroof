# spatial_module3d: the 3D Module (editable scene model, params <-> scene, presets). Depends on
# spatial_contract only. Never include anything from src/sim here (CLAUDE.md "contract boundary").
add_library(spatial_module3d STATIC
            SceneModel.h
            SceneModel.cpp)
add_library(spatial::module3d ALIAS spatial_module3d)

target_include_directories(spatial_module3d PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")
target_compile_features(spatial_module3d PUBLIC cxx_std_20)
target_link_libraries(spatial_module3d
                      PUBLIC spatial::contract
                      PRIVATE spatial::warnings)
