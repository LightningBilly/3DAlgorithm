cmake_minimum_required(VERSION 3.10)

# set the project name
project(Tutorial)
message("${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}")
# 添加这两行
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message("conan path: ${CONAN_LIBS}")

# add the executable
add_executable(Tutorial tutorial.cpp)
target_link_libraries(Tutorial ${CONAN_LIBS})