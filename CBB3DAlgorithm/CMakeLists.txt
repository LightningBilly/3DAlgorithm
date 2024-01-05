cmake_minimum_required(VERSION 3.1)

project(CBB3DAlgorithm)

add_definitions(-DFILE_A="ABC")


set(ALGORITHM_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
message("mulu: ${CMAKE_CURRENT_SOURCE_DIR}")

# 添加这两行
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message("conan path: ${CONAN_LIBS}")

add_subdirectory(../commonFunc/BasicTools ./BasicTools) # 包含A库
add_subdirectory(Dijkstra) # 调用生成B库过程
add_subdirectory(ARAPDeformation) # 调用生成B库过程
add_subdirectory(MVCParameterization) # 调用生成B库过程
add_subdirectory(coordinate)
add_subdirectory(Fitting)



# conan install D:\selfad\3DAlgorithm\CBB3DAlgorithm --build missing