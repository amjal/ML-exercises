# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /home/amir/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/212.4746.93/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/amir/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/212.4746.93/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/amir/ML-exercises

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amir/ML-exercises/cmake-build-debug

# Include any dependencies generated for this target.
include libfile/CMakeFiles/libfile.dir/depend.make
# Include the progress variables for this target.
include libfile/CMakeFiles/libfile.dir/progress.make

# Include the compile flags for this target's objects.
include libfile/CMakeFiles/libfile.dir/flags.make

libfile/CMakeFiles/libfile.dir/libfile.cpp.o: libfile/CMakeFiles/libfile.dir/flags.make
libfile/CMakeFiles/libfile.dir/libfile.cpp.o: ../libfile/libfile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amir/ML-exercises/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libfile/CMakeFiles/libfile.dir/libfile.cpp.o"
	cd /home/amir/ML-exercises/cmake-build-debug/libfile && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libfile.dir/libfile.cpp.o -c /home/amir/ML-exercises/libfile/libfile.cpp

libfile/CMakeFiles/libfile.dir/libfile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libfile.dir/libfile.cpp.i"
	cd /home/amir/ML-exercises/cmake-build-debug/libfile && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amir/ML-exercises/libfile/libfile.cpp > CMakeFiles/libfile.dir/libfile.cpp.i

libfile/CMakeFiles/libfile.dir/libfile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libfile.dir/libfile.cpp.s"
	cd /home/amir/ML-exercises/cmake-build-debug/libfile && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amir/ML-exercises/libfile/libfile.cpp -o CMakeFiles/libfile.dir/libfile.cpp.s

# Object files for target libfile
libfile_OBJECTS = \
"CMakeFiles/libfile.dir/libfile.cpp.o"

# External object files for target libfile
libfile_EXTERNAL_OBJECTS =

libfile/liblibfile.a: libfile/CMakeFiles/libfile.dir/libfile.cpp.o
libfile/liblibfile.a: libfile/CMakeFiles/libfile.dir/build.make
libfile/liblibfile.a: libfile/CMakeFiles/libfile.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/amir/ML-exercises/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblibfile.a"
	cd /home/amir/ML-exercises/cmake-build-debug/libfile && $(CMAKE_COMMAND) -P CMakeFiles/libfile.dir/cmake_clean_target.cmake
	cd /home/amir/ML-exercises/cmake-build-debug/libfile && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libfile.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libfile/CMakeFiles/libfile.dir/build: libfile/liblibfile.a
.PHONY : libfile/CMakeFiles/libfile.dir/build

libfile/CMakeFiles/libfile.dir/clean:
	cd /home/amir/ML-exercises/cmake-build-debug/libfile && $(CMAKE_COMMAND) -P CMakeFiles/libfile.dir/cmake_clean.cmake
.PHONY : libfile/CMakeFiles/libfile.dir/clean

libfile/CMakeFiles/libfile.dir/depend:
	cd /home/amir/ML-exercises/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/amir/ML-exercises /home/amir/ML-exercises/libfile /home/amir/ML-exercises/cmake-build-debug /home/amir/ML-exercises/cmake-build-debug/libfile /home/amir/ML-exercises/cmake-build-debug/libfile/CMakeFiles/libfile.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libfile/CMakeFiles/libfile.dir/depend
