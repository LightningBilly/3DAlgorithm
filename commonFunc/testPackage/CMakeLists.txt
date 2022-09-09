cmake_minimum_required(VERSION 3.1)

project(testPackage)

set(libpackage_src funcs.cpp)

include_directories("${PROJECT_SOURCE_DIR}")

add_library(libpackage_shared STATIC ${libpackage_src})
# add_library(hello_static STATIC ${libhello_src})

# set_target_properties(hello_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(libpackage_shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)

target_include_directories(libpackage_shared PUBLIC .)