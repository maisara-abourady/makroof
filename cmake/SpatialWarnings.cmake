# Warning flags for the project's own targets. Third-party code pulled in by FetchContent is
# declared SYSTEM, so warnings inside its headers are not reported.
#
# Usage: target_link_libraries(<target> PRIVATE spatial::warnings)
add_library(spatial_warnings INTERFACE)
add_library(spatial::warnings ALIAS spatial_warnings)

if(MSVC)
    target_compile_options(spatial_warnings INTERFACE /W4 /permissive- /Zc:__cplusplus)
    if(SPATIAL_WERROR)
        target_compile_options(spatial_warnings INTERFACE /WX)
    endif()
else()
    target_compile_options(spatial_warnings INTERFACE -Wall -Wextra -Wpedantic -Wshadow)
    if(SPATIAL_WERROR)
        target_compile_options(spatial_warnings INTERFACE -Werror)
    endif()
endif()
