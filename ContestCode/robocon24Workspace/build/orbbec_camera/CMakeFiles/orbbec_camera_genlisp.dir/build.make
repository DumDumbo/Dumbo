# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dragon/robocon24Workspace/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dragon/robocon24Workspace/build

# Utility rule file for orbbec_camera_genlisp.

# Include the progress variables for this target.
include orbbec_camera/CMakeFiles/orbbec_camera_genlisp.dir/progress.make

orbbec_camera_genlisp: orbbec_camera/CMakeFiles/orbbec_camera_genlisp.dir/build.make

.PHONY : orbbec_camera_genlisp

# Rule to build all files generated by this target.
orbbec_camera/CMakeFiles/orbbec_camera_genlisp.dir/build: orbbec_camera_genlisp

.PHONY : orbbec_camera/CMakeFiles/orbbec_camera_genlisp.dir/build

orbbec_camera/CMakeFiles/orbbec_camera_genlisp.dir/clean:
	cd /home/dragon/robocon24Workspace/build/orbbec_camera && $(CMAKE_COMMAND) -P CMakeFiles/orbbec_camera_genlisp.dir/cmake_clean.cmake
.PHONY : orbbec_camera/CMakeFiles/orbbec_camera_genlisp.dir/clean

orbbec_camera/CMakeFiles/orbbec_camera_genlisp.dir/depend:
	cd /home/dragon/robocon24Workspace/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dragon/robocon24Workspace/src /home/dragon/robocon24Workspace/src/orbbec_camera /home/dragon/robocon24Workspace/build /home/dragon/robocon24Workspace/build/orbbec_camera /home/dragon/robocon24Workspace/build/orbbec_camera/CMakeFiles/orbbec_camera_genlisp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : orbbec_camera/CMakeFiles/orbbec_camera_genlisp.dir/depend

