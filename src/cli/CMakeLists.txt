# render_cli: offline renders for tests and listening packs (Phase 02). Prints the version for now.
add_executable(render_cli main.cpp)

target_link_libraries(render_cli
                      PRIVATE spatial::contract
                              spatial::sim
                              spatial::warnings)
