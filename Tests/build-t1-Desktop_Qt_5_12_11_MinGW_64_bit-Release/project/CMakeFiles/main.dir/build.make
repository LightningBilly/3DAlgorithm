# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\selfad\3DAlgorithm\Tests\t1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\selfad\3DAlgorithm\Tests\build-t1-Desktop_Qt_5_12_11_MinGW_64_bit-Release

# Include any dependencies generated for this target.
include project/CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include project/CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include project/CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include project/CMakeFiles/main.dir/flags.make

project/CMakeFiles/main.dir/main.cpp.obj: project/CMakeFiles/main.dir/flags.make
project/CMakeFiles/main.dir/main.cpp.obj: project/CMakeFiles/main.dir/includes_CXX.rsp
project/CMakeFiles/main.dir/main.cpp.obj: D:/selfad/3DAlgorithm/Tests/t1/project/main.cpp
project/CMakeFiles/main.dir/main.cpp.obj: project/CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\selfad\3DAlgorithm\Tests\build-t1-Desktop_Qt_5_12_11_MinGW_64_bit-Release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object project/CMakeFiles/main.dir/main.cpp.obj"
	cd /d D:\selfad\3DAlgorithm\Tests\build-t1-Desktop_Qt_5_12_11_MinGW_64_bit-Release\project && C:\Qt\Qt5.12.11\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT project/CMakeFiles/main.dir/main.cpp.obj -MF CMakeFiles\main.dir\main.cpp.obj.d -o CMakeFiles\main.dir\main.cpp.obj -c D:\selfad\3DAlgorithm\Tests\t1\project\main.cpp

project/CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	cd /d D:\selfad\3DAlgorithm\Tests\build-t1-Desktop_Qt_5_12_11_MinGW_64_bit-Release\project && C:\Qt\Qt5.12.11\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\selfad\3DAlgorithm\Tests\t1\project\main.cpp > CMakeFiles\main.dir\main.cpp.i

project/CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	cd /d D:\selfad\3DAlgorithm\Tests\build-t1-Desktop_Qt_5_12_11_MinGW_64_bit-Release\project && C:\Qt\Qt5.12.11\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\selfad\3DAlgorithm\Tests\t1\project\main.cpp -o CMakeFiles\main.dir\main.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.obj"

# External object files for target main
main_EXTERNAL_OBJECTS =

project/main.exe: project/CMakeFiles/main.dir/main.cpp.obj
project/main.exe: project/CMakeFiles/main.dir/build.make
project/main.exe: BasicTools/Release/BasicTools.lib
project/main.exe: project/CMakeFiles/main.dir/linklibs.rsp
project/main.exe: project/CMakeFiles/main.dir/objects1.rsp
project/main.exe: project/CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\selfad\3DAlgorithm\Tests\build-t1-Desktop_Qt_5_12_11_MinGW_64_bit-Release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable main.exe"
	cd /d D:\selfad\3DAlgorithm\Tests\build-t1-Desktop_Qt_5_12_11_MinGW_64_bit-Release\project && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\main.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
project/CMakeFiles/main.dir/build: project/main.exe
.PHONY : project/CMakeFiles/main.dir/build

project/CMakeFiles/main.dir/clean:
	cd /d D:\selfad\3DAlgorithm\Tests\build-t1-Desktop_Qt_5_12_11_MinGW_64_bit-Release\project && $(CMAKE_COMMAND) -P CMakeFiles\main.dir\cmake_clean.cmake
.PHONY : project/CMakeFiles/main.dir/clean

project/CMakeFiles/main.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\selfad\3DAlgorithm\Tests\t1 D:\selfad\3DAlgorithm\Tests\t1\project D:\selfad\3DAlgorithm\Tests\build-t1-Desktop_Qt_5_12_11_MinGW_64_bit-Release D:\selfad\3DAlgorithm\Tests\build-t1-Desktop_Qt_5_12_11_MinGW_64_bit-Release\project D:\selfad\3DAlgorithm\Tests\build-t1-Desktop_Qt_5_12_11_MinGW_64_bit-Release\project\CMakeFiles\main.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : project/CMakeFiles/main.dir/depend

