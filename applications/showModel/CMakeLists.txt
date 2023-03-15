cmake_minimum_required(VERSION 3.15)
set(ProName ShowModel)
project(${ProName})

message("${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}")
# 添加这两行
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message("conan path: ${CONAN_LIBS}")

add_subdirectory(../../commonFunc/BasicTools ./BasicTools)
include_directories(../../commonFunc/BasicTools)
message(${PROJECT_BINARY_DIR}/BasicTools/lib/BasicTools.lib)
set(BasicTools_so ${PROJECT_BINARY_DIR}/BasicTools/lib/BasicTools.lib)
message("88 ${BasicTools_so}")

add_executable(${ProName} main.cpp model.cpp model.h BSpline.h BSpline.cpp PolyMesh.h PolyMesh.cpp IOManager.h IOManager.cpp common.h common.cpp)

target_link_libraries(${ProName} ${CONAN_LIBS} ${BasicTools_so})