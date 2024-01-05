cmake_minimum_required(VERSION 3.1)

project(Fitting)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../cmake")

add_definitions(-DFILE_ROOT="${ALGORITHM_ROOT_DIR}/Fitting")

# 设置依赖库lib文件
set(BasicTools_so ${PROJECT_BINARY_DIR}/BasicTools/Release/BasicTools.lib) # 设置所需要的lib
include_directories(../../commonFunc/BasicTools) # 包含Lib对应的头文件

set (directories . gauss chebyshev)

include (ACGCommon)
add_source_files (headers "*.h" ${directories})
add_source_files (sources "*.cpp" ${directories})


message("source : ${sources}")

include (CreateFilter)
create_filter_by_dir(${CMAKE_CURRENT_SOURCE_DIR} ${sources} ${headers})


# 找到需要的cpp代码
#file(GLOB_RECURSE CPP_FILES     
#${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
#)

#message("cpp_files: ${CPP_FILES}")

add_library(${PROJECT_NAME} STATIC ${sources} ${headers}) # 生成lib
link_directories(${BasicTools_so} ${CONAN_LIBS}) # 用来链接lib库 与target_link_library 的区别



set_target_properties(${PROJECT_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_include_directories(${PROJECT_NAME} PUBLIC .) # 发布lib

# conan install .. --build missing