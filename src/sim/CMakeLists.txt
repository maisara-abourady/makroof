# spatial_sim: the Simulator (ISM, tail, HRTF, IR builder, convolver). Depends on spatial_contract
# only. Never include anything from src/module3d or JUCE here (CLAUDE.md "contract boundary").
add_library(spatial_sim STATIC
            Simulator.h
            Simulator.cpp
            Engine.h
            Engine.cpp
            OfflineRender.h
            OfflineRender.cpp
            AirAbsorption.h
            AirAbsorption.cpp
            Rng.h
            Fft.h
            Fft.cpp
            tail/Decay.h
            tail/Decay.cpp
            tail/MixingTime.h
            tail/MixingTime.cpp
            tail/NoiseTail.h
            tail/NoiseTail.cpp
            ism/ImageSources.h
            ism/ImageSources.cpp
            ism/BandRenderer.h
            ism/BandRenderer.cpp
            RealtimeEngine.h
            RealtimeEngine.cpp
            conv/Fft.h
            conv/Fft.cpp
            conv/Denormals.h
            conv/PartitionedConvolver.h
            conv/PartitionedConvolver.cpp
            conv/CrossfadingConvolver.h
            conv/CrossfadingConvolver.cpp
            diffuse/Sampling.h
            diffuse/FaceLists.h
            diffuse/FaceLists.cpp
            diffuse/ThreadPool.h
            diffuse/ThreadPool.cpp
            diffuse/DiffuseEstimator.h
            diffuse/DiffuseEstimator.cpp)
add_library(spatial::sim ALIAS spatial_sim)

target_include_directories(spatial_sim PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")
target_compile_features(spatial_sim PUBLIC cxx_std_20)
target_link_libraries(spatial_sim
                      PUBLIC spatial::contract
                      PRIVATE spatial::pffft
                              spatial::warnings)

# AX39 D2: the diffuse estimator's paths and sums must not depend on FMA contraction or fast-math
# (tools/ci/test_diffuse_sources.py checks this block).
set(SPATIAL_DIFFUSE_SOURCES diffuse/FaceLists.cpp diffuse/ThreadPool.cpp diffuse/DiffuseEstimator.cpp)
if(MSVC)
    set_source_files_properties(${SPATIAL_DIFFUSE_SOURCES} PROPERTIES COMPILE_OPTIONS "/fp:precise")
else()
    set_source_files_properties(${SPATIAL_DIFFUSE_SOURCES} PROPERTIES COMPILE_OPTIONS
                                "-ffp-contract=off;-fno-fast-math")
endif()
find_package(Threads REQUIRED)
target_link_libraries(spatial_sim PRIVATE Threads::Threads)
