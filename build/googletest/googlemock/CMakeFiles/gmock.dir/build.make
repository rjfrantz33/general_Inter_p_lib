# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/s0001480/Documents/Cpp_src/general_Inter_p_lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/s0001480/Documents/Cpp_src/general_Inter_p_lib/build

# Include any dependencies generated for this target.
include googletest/googlemock/CMakeFiles/gmock.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include googletest/googlemock/CMakeFiles/gmock.dir/compiler_depend.make

# Include the progress variables for this target.
include googletest/googlemock/CMakeFiles/gmock.dir/progress.make

# Include the compile flags for this target's objects.
include googletest/googlemock/CMakeFiles/gmock.dir/flags.make

googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o: googletest/googlemock/CMakeFiles/gmock.dir/flags.make
googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o: ../googletest/googlemock/src/gmock-all.cc
googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o: googletest/googlemock/CMakeFiles/gmock.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/s0001480/Documents/Cpp_src/general_Inter_p_lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o"
	cd /home/s0001480/Documents/Cpp_src/general_Inter_p_lib/build/googletest/googlemock && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o -MF CMakeFiles/gmock.dir/src/gmock-all.cc.o.d -o CMakeFiles/gmock.dir/src/gmock-all.cc.o -c /home/s0001480/Documents/Cpp_src/general_Inter_p_lib/googletest/googlemock/src/gmock-all.cc

googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock.dir/src/gmock-all.cc.i"
	cd /home/s0001480/Documents/Cpp_src/general_Inter_p_lib/build/googletest/googlemock && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/s0001480/Documents/Cpp_src/general_Inter_p_lib/googletest/googlemock/src/gmock-all.cc > CMakeFiles/gmock.dir/src/gmock-all.cc.i

googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock.dir/src/gmock-all.cc.s"
	cd /home/s0001480/Documents/Cpp_src/general_Inter_p_lib/build/googletest/googlemock && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/s0001480/Documents/Cpp_src/general_Inter_p_lib/googletest/googlemock/src/gmock-all.cc -o CMakeFiles/gmock.dir/src/gmock-all.cc.s

# Object files for target gmock
gmock_OBJECTS = \
"CMakeFiles/gmock.dir/src/gmock-all.cc.o"

# External object files for target gmock
gmock_EXTERNAL_OBJECTS =

lib/libgmock.a: googletest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
lib/libgmock.a: googletest/googlemock/CMakeFiles/gmock.dir/build.make
lib/libgmock.a: googletest/googlemock/CMakeFiles/gmock.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/s0001480/Documents/Cpp_src/general_Inter_p_lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../lib/libgmock.a"
	cd /home/s0001480/Documents/Cpp_src/general_Inter_p_lib/build/googletest/googlemock && $(CMAKE_COMMAND) -P CMakeFiles/gmock.dir/cmake_clean_target.cmake
	cd /home/s0001480/Documents/Cpp_src/general_Inter_p_lib/build/googletest/googlemock && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gmock.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
googletest/googlemock/CMakeFiles/gmock.dir/build: lib/libgmock.a
.PHONY : googletest/googlemock/CMakeFiles/gmock.dir/build

googletest/googlemock/CMakeFiles/gmock.dir/clean:
	cd /home/s0001480/Documents/Cpp_src/general_Inter_p_lib/build/googletest/googlemock && $(CMAKE_COMMAND) -P CMakeFiles/gmock.dir/cmake_clean.cmake
.PHONY : googletest/googlemock/CMakeFiles/gmock.dir/clean

googletest/googlemock/CMakeFiles/gmock.dir/depend:
	cd /home/s0001480/Documents/Cpp_src/general_Inter_p_lib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/s0001480/Documents/Cpp_src/general_Inter_p_lib /home/s0001480/Documents/Cpp_src/general_Inter_p_lib/googletest/googlemock /home/s0001480/Documents/Cpp_src/general_Inter_p_lib/build /home/s0001480/Documents/Cpp_src/general_Inter_p_lib/build/googletest/googlemock /home/s0001480/Documents/Cpp_src/general_Inter_p_lib/build/googletest/googlemock/CMakeFiles/gmock.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : googletest/googlemock/CMakeFiles/gmock.dir/depend

