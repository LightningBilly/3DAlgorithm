cmake_minimum_required(VERSION 3.1)

project(coordinate)


add_definitions(-DFILE_ROOT="${ALGORITHM_ROOT_DIR}/coordinate")

# 设置依赖库lib文件
set(BasicTools_so ${PROJECT_BINARY_DIR}/BasicTools/Release/BasicTools.lib) # 设置所需要的lib
include_directories(../../commonFunc/BasicTools) # 包含Lib对应的头文件

# 找到需要的cpp代码
file(GLOB_RECURSE CPP_FILES     
${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

message("cpp_files: ${CPP_FILES}")

add_library(${PROJECT_NAME} STATIC ${CPP_FILES}) # 生成lib
link_directories(${BasicTools_so} ${CONAN_LIBS}) # 用来链接lib库 与target_link_library 的区别



set_target_properties(${PROJECT_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_include_directories(${PROJECT_NAME} PUBLIC .) # 发布lib

# conan install .. --build missing