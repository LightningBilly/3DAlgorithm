project(DIJKSTRA)

include_directories(../../CBB3DAlgorithm)

set(CBB3DAlgorithm_so ${PROJECT_BINARY_DIR}/CBB3DAlgorithm/Release/CBB3DAlgorithm.lib)

add_executable(main main.cpp)

target_link_libraries(main ${CBB3DAlgorithm})