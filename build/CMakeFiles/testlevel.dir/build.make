# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3/build

# Include any dependencies generated for this target.
include CMakeFiles/testlevel.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testlevel.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testlevel.dir/flags.make

CMakeFiles/testlevel.dir/src/level.cpp.o: CMakeFiles/testlevel.dir/flags.make
CMakeFiles/testlevel.dir/src/level.cpp.o: ../src/level.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testlevel.dir/src/level.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testlevel.dir/src/level.cpp.o -c /mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3/src/level.cpp

CMakeFiles/testlevel.dir/src/level.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testlevel.dir/src/level.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3/src/level.cpp > CMakeFiles/testlevel.dir/src/level.cpp.i

CMakeFiles/testlevel.dir/src/level.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testlevel.dir/src/level.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3/src/level.cpp -o CMakeFiles/testlevel.dir/src/level.cpp.s

CMakeFiles/testlevel.dir/src/leveltesting.cpp.o: CMakeFiles/testlevel.dir/flags.make
CMakeFiles/testlevel.dir/src/leveltesting.cpp.o: ../src/leveltesting.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/testlevel.dir/src/leveltesting.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testlevel.dir/src/leveltesting.cpp.o -c /mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3/src/leveltesting.cpp

CMakeFiles/testlevel.dir/src/leveltesting.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testlevel.dir/src/leveltesting.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3/src/leveltesting.cpp > CMakeFiles/testlevel.dir/src/leveltesting.cpp.i

CMakeFiles/testlevel.dir/src/leveltesting.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testlevel.dir/src/leveltesting.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3/src/leveltesting.cpp -o CMakeFiles/testlevel.dir/src/leveltesting.cpp.s

# Object files for target testlevel
testlevel_OBJECTS = \
"CMakeFiles/testlevel.dir/src/level.cpp.o" \
"CMakeFiles/testlevel.dir/src/leveltesting.cpp.o"

# External object files for target testlevel
testlevel_EXTERNAL_OBJECTS =

testlevel: CMakeFiles/testlevel.dir/src/level.cpp.o
testlevel: CMakeFiles/testlevel.dir/src/leveltesting.cpp.o
testlevel: CMakeFiles/testlevel.dir/build.make
testlevel: CMakeFiles/testlevel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable testlevel"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testlevel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testlevel.dir/build: testlevel

.PHONY : CMakeFiles/testlevel.dir/build

CMakeFiles/testlevel.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testlevel.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testlevel.dir/clean

CMakeFiles/testlevel.dir/depend:
	cd /mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3 /mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3 /mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3/build /mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3/build /mnt/c/Users/tuoma/Documents/Programming/CPP/angry-birds-2020-3/build/CMakeFiles/testlevel.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testlevel.dir/depend

