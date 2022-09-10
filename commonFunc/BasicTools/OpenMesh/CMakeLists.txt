cmake_minimum_required(VERSION 3.10)

project(OpenMesh)
message("${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}")
# 添加这两行
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message("conan path: ${CONAN_LIBS}")


set(openmesh_src opentools.cpp)

include_directories("${PROJECT_SOURCE_DIR}")

add_library(OpenMeshTool STATIC ${openmesh_src})

set_target_properties(OpenMeshTool PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_include_directories(OpenMeshTool PUBLIC .)