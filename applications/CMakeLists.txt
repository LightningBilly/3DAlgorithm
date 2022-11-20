cmake_minimum_required(VERSION 3.1)

project(BasicTools)
message("${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}")

# 找到需要的cpp代码
file(GLOB_RECURSE CPP_FILES     
${CMAKE_CURRENT_SOURCE_DIR}/PolyMesh/*.cpp
)


message("cpp_files: ${CPP_FILES}")

add_library(${PROJECT_NAME} STATIC ${CPP_FILES}) # 添加静态库编译

set_target_properties(${PROJECT_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_include_directories(${PROJECT_NAME} PUBLIC ./include) # 发布一个库

