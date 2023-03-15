cmake_minimum_required(VERSION 3.1)

project(ALG_TEST)

add_subdirectory(../../CBB3DAlgorithm ./CBB3DAlgorithm) # 添加依赖库

# 设置依赖的头文件
include_directories(../../CBB3DAlgorithm)
include_directories(../../commonFunc/BasicTools)

# 设置依赖库lib文件
file(GLOB_RECURSE CBB3DAlgorithm_so     
${PROJECT_BINARY_DIR}/CBB3DAlgorithm/lib/*.lib
${PROJECT_BINARY_DIR}/CBB3DAlgorithm/BasicTools/lib/*.lib
)
message("CBB3DAlgorithm_so=${CBB3DAlgorithm_so}")

# 添加这两行
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(main main.cpp) # 编译可执行文件

target_link_libraries(main ${CBB3DAlgorithm_so} ${CONAN_LIBS}) # 链接可执行文件

# add_subdirectory(dijkstra)