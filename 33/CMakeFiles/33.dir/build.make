# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/piotr/DesignPatterns/33

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/piotr/DesignPatterns/33

# Include any dependencies generated for this target.
include CMakeFiles/33.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/33.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/33.dir/flags.make

CMakeFiles/33.dir/main.cpp.o: CMakeFiles/33.dir/flags.make
CMakeFiles/33.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/piotr/DesignPatterns/33/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/33.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/33.dir/main.cpp.o -c /home/piotr/DesignPatterns/33/main.cpp

CMakeFiles/33.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/33.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/piotr/DesignPatterns/33/main.cpp > CMakeFiles/33.dir/main.cpp.i

CMakeFiles/33.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/33.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/piotr/DesignPatterns/33/main.cpp -o CMakeFiles/33.dir/main.cpp.s

CMakeFiles/33.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/33.dir/main.cpp.o.requires

CMakeFiles/33.dir/main.cpp.o.provides: CMakeFiles/33.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/33.dir/build.make CMakeFiles/33.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/33.dir/main.cpp.o.provides

CMakeFiles/33.dir/main.cpp.o.provides.build: CMakeFiles/33.dir/main.cpp.o


# Object files for target 33
33_OBJECTS = \
"CMakeFiles/33.dir/main.cpp.o"

# External object files for target 33
33_EXTERNAL_OBJECTS =

33: CMakeFiles/33.dir/main.cpp.o
33: CMakeFiles/33.dir/build.make
33: CMakeFiles/33.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/piotr/DesignPatterns/33/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 33"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/33.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/33.dir/build: 33

.PHONY : CMakeFiles/33.dir/build

CMakeFiles/33.dir/requires: CMakeFiles/33.dir/main.cpp.o.requires

.PHONY : CMakeFiles/33.dir/requires

CMakeFiles/33.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/33.dir/cmake_clean.cmake
.PHONY : CMakeFiles/33.dir/clean

CMakeFiles/33.dir/depend:
	cd /home/piotr/DesignPatterns/33 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/piotr/DesignPatterns/33 /home/piotr/DesignPatterns/33 /home/piotr/DesignPatterns/33 /home/piotr/DesignPatterns/33 /home/piotr/DesignPatterns/33/CMakeFiles/33.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/33.dir/depend

