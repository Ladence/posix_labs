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
CMAKE_SOURCE_DIR = /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/build

# Include any dependencies generated for this target.
include CMakeFiles/cncr_wrtr_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cncr_wrtr_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cncr_wrtr_1.dir/flags.make

CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.o: CMakeFiles/cncr_wrtr_1.dir/flags.make
CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.o: ../concurrent_writers.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.o -c /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/concurrent_writers.cc

CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/concurrent_writers.cc > CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.i

CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/concurrent_writers.cc -o CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.s

CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.o.requires:

.PHONY : CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.o.requires

CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.o.provides: CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.o.requires
	$(MAKE) -f CMakeFiles/cncr_wrtr_1.dir/build.make CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.o.provides.build
.PHONY : CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.o.provides

CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.o.provides.build: CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.o


# Object files for target cncr_wrtr_1
cncr_wrtr_1_OBJECTS = \
"CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.o"

# External object files for target cncr_wrtr_1
cncr_wrtr_1_EXTERNAL_OBJECTS =

cncr_wrtr_1: CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.o
cncr_wrtr_1: CMakeFiles/cncr_wrtr_1.dir/build.make
cncr_wrtr_1: CMakeFiles/cncr_wrtr_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cncr_wrtr_1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cncr_wrtr_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cncr_wrtr_1.dir/build: cncr_wrtr_1

.PHONY : CMakeFiles/cncr_wrtr_1.dir/build

CMakeFiles/cncr_wrtr_1.dir/requires: CMakeFiles/cncr_wrtr_1.dir/concurrent_writers.cc.o.requires

.PHONY : CMakeFiles/cncr_wrtr_1.dir/requires

CMakeFiles/cncr_wrtr_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cncr_wrtr_1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cncr_wrtr_1.dir/clean

CMakeFiles/cncr_wrtr_1.dir/depend:
	cd /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/build /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/build /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/build/CMakeFiles/cncr_wrtr_1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cncr_wrtr_1.dir/depend

