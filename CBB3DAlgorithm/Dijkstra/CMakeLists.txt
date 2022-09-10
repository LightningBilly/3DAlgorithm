project(Dijkstra)
# message("${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}")

set(BasicTools_so ${PROJECT_BINARY_DIR}/BasicTools/Release/BasicTools.lib)
include_directories(../../commonFunc/BasicTools)

file(GLOB_RECURSE CPP_FILES 
${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

message("cpp_files: ${CPP_FILES}")

add_library(${PROJECT_NAME} STATIC ${CPP_FILES})
link_directories(${BasicTools_so}) # 用来链接lib库 与target_link_library 的区别

set_target_properties(${PROJECT_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_include_directories(${PROJECT_NAME} PUBLIC .)

