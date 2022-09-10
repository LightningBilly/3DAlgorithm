cmake_minimum_required(VERSION 3.1)

project(PolyMesh)
message("${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}")

file(GLOB_RECURSE CPP_FILES     
${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)


message("cpp_files: ${CPP_FILES}")

add_library(${PROJECT_NAME} STATIC ${CPP_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_include_directories(${PROJECT_NAME} PUBLIC .)

# set(openmesh_src opentools.cpp)

# include_directories("${PROJECT_SOURCE_DIR}")

# add_library(OpenMeshTool STATIC ${openmesh_src})
