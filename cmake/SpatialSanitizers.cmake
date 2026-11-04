# Sanitizer support for the asan/tsan presets (Linux). SPATIAL_SANITIZER is a comma-separated list
# understood by -fsanitize=, e.g. "address,undefined" or "thread". Applied project-wide so that
# JUCE module code compiled into the plugin is instrumented too.
if(SPATIAL_SANITIZER)
    if(MSVC)
        message(FATAL_ERROR "SPATIAL_SANITIZER is only supported with GCC/Clang")
    endif()
    message(STATUS "SpatialScene: sanitizers enabled: ${SPATIAL_SANITIZER}")
    add_compile_options(-fsanitize=${SPATIAL_SANITIZER} -fno-omit-frame-pointer -fno-sanitize-recover=all)
    add_link_options(-fsanitize=${SPATIAL_SANITIZER})
endif()
