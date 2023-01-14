cmake_minimum_required(VERSION 3.1)

project(basicTest)

set(CMAKE_CXX_STANDARD 11)

# 添加这两行
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message("conan path: ${CONAN_LIBS}")

add_subdirectory(../../commonFunc/BasicTools ./BasicTools)
add_subdirectory(project)
