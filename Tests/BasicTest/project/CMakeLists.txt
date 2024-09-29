include_directories(../../../commonFunc/BasicTools)
add_executable(main main.cpp rigidrt.h rigidrt.cpp)
target_link_libraries(main ${BasicTools_so} ${CONAN_LIBS})