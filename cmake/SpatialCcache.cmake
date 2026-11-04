# Uses ccache as a compiler launcher when it is installed and SPATIAL_USE_CCACHE is ON.
# CI installs ccache through hendrikmuhs/ccache-action; local builds pick it up automatically.
if(SPATIAL_USE_CCACHE AND NOT CMAKE_CXX_COMPILER_LAUNCHER)
    find_program(SPATIAL_CCACHE_PROGRAM ccache)
    if(SPATIAL_CCACHE_PROGRAM)
        message(STATUS "SpatialScene: using ccache at ${SPATIAL_CCACHE_PROGRAM}")
        set(CMAKE_C_COMPILER_LAUNCHER "${SPATIAL_CCACHE_PROGRAM}" CACHE FILEPATH "" FORCE)
        set(CMAKE_CXX_COMPILER_LAUNCHER "${SPATIAL_CCACHE_PROGRAM}" CACHE FILEPATH "" FORCE)
    endif()
endif()
