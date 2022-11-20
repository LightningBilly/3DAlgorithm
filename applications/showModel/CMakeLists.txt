cmake_minimum_required(VERSION 3.15)
set(ProName ShowModel)
project(${ProName})

message("${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}")
# 添加这两行
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message("conan path: ${CONAN_LIBS}")

#设置一些OpenGL头文件所在目录的宏
set(GLEW_H /Library/Developer/CommandLineTools/usr/include/glew/2.2.0_1/include/GL)
set(GLFW_H /Library/Developer/CommandLineTools/usr/include/glfw/3.3.4/include/GLFW)
set(GLAD_H /Library/Developer/CommandLineTools/usr/include)
set(GLAD_H /Library/Developer/CommandLineTools/usr/include/glad)
set(KH_H /Library/Developer/CommandLineTools/usr/include/KHR)
#包含上述头文件所在目录
#include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H} ${KH_H})
#include_directories( "/usr/local/include/eigen3" )

#设置OpenGL库所在位置，并链接
#set(GLEW_LINK /Library/Developer/CommandLineTools/usr/include/glew/2.2.0_1/lib/libGLEW.2.2.0.dylib)
#set(GLFW_LINK /Library/Developer/CommandLineTools/usr/include/glfw/3.3.4/lib/libglfw.3.3.dylib)
# link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

#设置要编译的c/cpp文件到可执行文件中，该exe包含两个文件glad.c,main.cpp,${ProName}
set(SOURCE_FILES "glad.c" "main.cpp")

add_executable(${ProName} main.cpp model.cpp model.h BSpline.h BSpline.cpp PolyMesh.h PolyMesh.cpp IOManager.h IOManager.cpp)

target_link_libraries(${ProName} ${CONAN_LIBS})