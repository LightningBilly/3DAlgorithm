cmake_minimum_required(VERSION 3.1)

project(CBB3DAlgorithm)

add_subdirectory(../commonFunc/BasicTools ./BasicTools) # 包含A库
add_subdirectory(Dijkstra) # 调用生成B库过程