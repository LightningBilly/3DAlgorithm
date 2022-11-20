cmake_minimum_required(VERSION 3.1)

project(DIJKSTRA_TEST)

add_subdirectory(../../CBB3DAlgorithm ./CBB3DAlgorithm) # 添加依赖库

# 设置依赖的头文件
include_directories(../../CBB3DAlgorithm)
include_directories(../../commonFunc/BasicTools)

# 设置依赖库lib文件
set(CBB3DAlgorithm_so ${PROJECT_BINARY_DIR}/CBB3DAlgorithm/Dijkstra/Release/Dijkstra.lib)
set(BasicTools_so ${PROJECT_BINARY_DIR}/CBB3DAlgorithm/BasicTools/Release/BasicTools.lib)

add_executable(main main.cpp) # 编译可执行文件

target_link_libraries(main ${CBB3DAlgorithm_so} ${BasicTools_so}) # 链接可执行文件

# add_subdirectory(dijkstra)