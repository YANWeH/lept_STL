# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/PROJECTS/lept_STL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/PROJECTS/lept_STL/build

# Include any dependencies generated for this target.
include test/CMakeFiles/leptstl_test.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/leptstl_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/leptstl_test.dir/flags.make

test/CMakeFiles/leptstl_test.dir/lept_test.cpp.o: test/CMakeFiles/leptstl_test.dir/flags.make
test/CMakeFiles/leptstl_test.dir/lept_test.cpp.o: ../test/lept_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/PROJECTS/lept_STL/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/leptstl_test.dir/lept_test.cpp.o"
	cd /root/PROJECTS/lept_STL/build/test && /opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/leptstl_test.dir/lept_test.cpp.o -c /root/PROJECTS/lept_STL/test/lept_test.cpp

test/CMakeFiles/leptstl_test.dir/lept_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/leptstl_test.dir/lept_test.cpp.i"
	cd /root/PROJECTS/lept_STL/build/test && /opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/PROJECTS/lept_STL/test/lept_test.cpp > CMakeFiles/leptstl_test.dir/lept_test.cpp.i

test/CMakeFiles/leptstl_test.dir/lept_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/leptstl_test.dir/lept_test.cpp.s"
	cd /root/PROJECTS/lept_STL/build/test && /opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/PROJECTS/lept_STL/test/lept_test.cpp -o CMakeFiles/leptstl_test.dir/lept_test.cpp.s

test/CMakeFiles/leptstl_test.dir/lept_test.cpp.o.requires:
.PHONY : test/CMakeFiles/leptstl_test.dir/lept_test.cpp.o.requires

test/CMakeFiles/leptstl_test.dir/lept_test.cpp.o.provides: test/CMakeFiles/leptstl_test.dir/lept_test.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/leptstl_test.dir/build.make test/CMakeFiles/leptstl_test.dir/lept_test.cpp.o.provides.build
.PHONY : test/CMakeFiles/leptstl_test.dir/lept_test.cpp.o.provides

test/CMakeFiles/leptstl_test.dir/lept_test.cpp.o.provides.build: test/CMakeFiles/leptstl_test.dir/lept_test.cpp.o

# Object files for target leptstl_test
leptstl_test_OBJECTS = \
"CMakeFiles/leptstl_test.dir/lept_test.cpp.o"

# External object files for target leptstl_test
leptstl_test_EXTERNAL_OBJECTS =

../bin/leptstl_test: test/CMakeFiles/leptstl_test.dir/lept_test.cpp.o
../bin/leptstl_test: test/CMakeFiles/leptstl_test.dir/build.make
../bin/leptstl_test: test/CMakeFiles/leptstl_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/leptstl_test"
	cd /root/PROJECTS/lept_STL/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/leptstl_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/leptstl_test.dir/build: ../bin/leptstl_test
.PHONY : test/CMakeFiles/leptstl_test.dir/build

test/CMakeFiles/leptstl_test.dir/requires: test/CMakeFiles/leptstl_test.dir/lept_test.cpp.o.requires
.PHONY : test/CMakeFiles/leptstl_test.dir/requires

test/CMakeFiles/leptstl_test.dir/clean:
	cd /root/PROJECTS/lept_STL/build/test && $(CMAKE_COMMAND) -P CMakeFiles/leptstl_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/leptstl_test.dir/clean

test/CMakeFiles/leptstl_test.dir/depend:
	cd /root/PROJECTS/lept_STL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/PROJECTS/lept_STL /root/PROJECTS/lept_STL/test /root/PROJECTS/lept_STL/build /root/PROJECTS/lept_STL/build/test /root/PROJECTS/lept_STL/build/test/CMakeFiles/leptstl_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/leptstl_test.dir/depend

