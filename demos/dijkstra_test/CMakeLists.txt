cmake_minimum_required(VERSION 3.1)

project(DIJKSTRA_TEST)

add_subdirectory(../../CBB3DAlgorithm ./CBB3DAlgorithm)

include_directories(../../CBB3DAlgorithm)
include_directories(../../commonFunc/BasicTools)

set(CBB3DAlgorithm_so ${PROJECT_BINARY_DIR}/CBB3DAlgorithm/Dijkstra/Release/Dijkstra.lib)
set(BasicTools_so ${PROJECT_BINARY_DIR}/CBB3DAlgorithm/BasicTools/Release/BasicTools.lib)

add_executable(main main.cpp)

target_link_libraries(main ${CBB3DAlgorithm_so} ${BasicTools_so})

# add_subdirectory(dijkstra)