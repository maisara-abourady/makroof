# spatial_contract: SceneDescription types, JSON I/O, validation, versioning. No JUCE.
add_library(spatial_contract STATIC
            Version.h
            Version.cpp)
add_library(spatial::contract ALIAS spatial_contract)

target_include_directories(spatial_contract PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")
target_compile_features(spatial_contract PUBLIC cxx_std_20)
target_link_libraries(spatial_contract PRIVATE spatial::warnings)
