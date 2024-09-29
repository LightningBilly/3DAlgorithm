cmake_minimum_required(VERSION 3.1)

project(basicTest)

set(CMAKE_CXX_STANDARD 11)


# 添加这两行
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message("conan path: ${CONAN_LIBS}")



add_subdirectory(../../commonFunc/BasicTools ./BasicTools)

# 共公库lib路径
message(${PROJECT_BINARY_DIR}/BasicTools/lib/BasicTools.lib)
set(BasicTools_so ${PROJECT_BINARY_DIR}/BasicTools/lib/BasicTools.lib)
message("88 ${BasicTools_so}")

add_subdirectory(project)
add_subdirectory(IOTypeTest)
add_subdirectory(SimplexTest)

# build tips
# conan install D:\selfad\alg_and_graph\3DAlgorithm\commonFunc\BasicTools --build missing
# cmake build