project(Dijkstra)
# message("${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}")

set(BasicTools_so ${PROJECT_BINARY_DIR}/BasicTools/Release/BasicTools.lib) # 设置所需要的lib
include_directories(../../commonFunc/BasicTools) # 包含Lib对应的头文件

# 找出所需要的cpp
file(GLOB_RECURSE CPP_FILES 
${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

message("cpp_files: ${CPP_FILES}")

add_library(${PROJECT_NAME} STATIC ${CPP_FILES}) # 生成lib
link_directories(${BasicTools_so}) # 用来链接lib库 与target_link_library 的区别

set_target_properties(${PROJECT_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_include_directories(${PROJECT_NAME} PUBLIC .) # 发布lib

