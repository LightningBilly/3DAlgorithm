
include_directories(../../../commonFunc/BasicTools)

# 添加公共cmake函数库路径
list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../cmake")

set (directories .)

include (ACGCommon)
add_source_files (headers "*.h" ${directories})
add_source_files (sources "*.cpp" ${directories})


include (CreateFilter)
create_filter_by_dir(${CMAKE_CURRENT_SOURCE_DIR} ${sources} ${headers})

add_executable(IOTypeTest ${sources} ${headers})
target_link_libraries(IOTypeTest ${BasicTools_so} ${CONAN_LIBS})

# conan install D:\selfad\alg_and_graph\3DAlgorithm\commonFunc\BasicTools --build missing