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
include CMakeFiles/swaper.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/swaper.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/swaper.dir/flags.make

CMakeFiles/swaper.dir/swaper.cc.o: CMakeFiles/swaper.dir/flags.make
CMakeFiles/swaper.dir/swaper.cc.o: ../swaper.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/swaper.dir/swaper.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/swaper.dir/swaper.cc.o -c /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/swaper.cc

CMakeFiles/swaper.dir/swaper.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/swaper.dir/swaper.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/swaper.cc > CMakeFiles/swaper.dir/swaper.cc.i

CMakeFiles/swaper.dir/swaper.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/swaper.dir/swaper.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/swaper.cc -o CMakeFiles/swaper.dir/swaper.cc.s

CMakeFiles/swaper.dir/swaper.cc.o.requires:

.PHONY : CMakeFiles/swaper.dir/swaper.cc.o.requires

CMakeFiles/swaper.dir/swaper.cc.o.provides: CMakeFiles/swaper.dir/swaper.cc.o.requires
	$(MAKE) -f CMakeFiles/swaper.dir/build.make CMakeFiles/swaper.dir/swaper.cc.o.provides.build
.PHONY : CMakeFiles/swaper.dir/swaper.cc.o.provides

CMakeFiles/swaper.dir/swaper.cc.o.provides.build: CMakeFiles/swaper.dir/swaper.cc.o


# Object files for target swaper
swaper_OBJECTS = \
"CMakeFiles/swaper.dir/swaper.cc.o"

# External object files for target swaper
swaper_EXTERNAL_OBJECTS =

swaper: CMakeFiles/swaper.dir/swaper.cc.o
swaper: CMakeFiles/swaper.dir/build.make
swaper: CMakeFiles/swaper.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable swaper"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/swaper.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/swaper.dir/build: swaper

.PHONY : CMakeFiles/swaper.dir/build

CMakeFiles/swaper.dir/requires: CMakeFiles/swaper.dir/swaper.cc.o.requires

.PHONY : CMakeFiles/swaper.dir/requires

CMakeFiles/swaper.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/swaper.dir/cmake_clean.cmake
.PHONY : CMakeFiles/swaper.dir/clean

CMakeFiles/swaper.dir/depend:
	cd /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/build /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/build /home/konstantin/Dropbox/projects/c_cpp/linux_labs/lab_9_shm/build/CMakeFiles/swaper.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/swaper.dir/depend
