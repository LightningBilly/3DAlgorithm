cmake_minimum_required(VERSION 3.1)

# 添加这两行
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message("conan path: ${CONAN_LIBS}")

project(BasicTools)
message("${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}")


# 找到需要的cpp代码
file(GLOB_RECURSE CPP_FILES     
${CMAKE_CURRENT_SOURCE_DIR}/PolyMesh/*.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Math/*.cpp
${CMAKE_CURRENT_SOURCE_DIR}/include/Math/*.h
${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h
${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
)

message("cpp_files: ${CPP_FILES}")

add_library(${PROJECT_NAME} STATIC ${CPP_FILES}) # 添加静态库编译

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

set_target_properties(${PROJECT_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_include_directories(${PROJECT_NAME} PUBLIC ./include) # 发布一个库

