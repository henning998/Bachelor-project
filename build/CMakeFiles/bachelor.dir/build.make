# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/pi/HenningCasper/Bachelor-project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/HenningCasper/Bachelor-project/build

# Include any dependencies generated for this target.
include CMakeFiles/bachelor.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bachelor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bachelor.dir/flags.make

CMakeFiles/bachelor.dir/main.cpp.o: CMakeFiles/bachelor.dir/flags.make
CMakeFiles/bachelor.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/HenningCasper/Bachelor-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bachelor.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bachelor.dir/main.cpp.o -c /home/pi/HenningCasper/Bachelor-project/main.cpp

CMakeFiles/bachelor.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bachelor.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/HenningCasper/Bachelor-project/main.cpp > CMakeFiles/bachelor.dir/main.cpp.i

CMakeFiles/bachelor.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bachelor.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/HenningCasper/Bachelor-project/main.cpp -o CMakeFiles/bachelor.dir/main.cpp.s

CMakeFiles/bachelor.dir/controller.cpp.o: CMakeFiles/bachelor.dir/flags.make
CMakeFiles/bachelor.dir/controller.cpp.o: ../controller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/HenningCasper/Bachelor-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/bachelor.dir/controller.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bachelor.dir/controller.cpp.o -c /home/pi/HenningCasper/Bachelor-project/controller.cpp

CMakeFiles/bachelor.dir/controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bachelor.dir/controller.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/HenningCasper/Bachelor-project/controller.cpp > CMakeFiles/bachelor.dir/controller.cpp.i

CMakeFiles/bachelor.dir/controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bachelor.dir/controller.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/HenningCasper/Bachelor-project/controller.cpp -o CMakeFiles/bachelor.dir/controller.cpp.s

CMakeFiles/bachelor.dir/Braitenberg.cpp.o: CMakeFiles/bachelor.dir/flags.make
CMakeFiles/bachelor.dir/Braitenberg.cpp.o: ../Braitenberg.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/HenningCasper/Bachelor-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/bachelor.dir/Braitenberg.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bachelor.dir/Braitenberg.cpp.o -c /home/pi/HenningCasper/Bachelor-project/Braitenberg.cpp

CMakeFiles/bachelor.dir/Braitenberg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bachelor.dir/Braitenberg.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/HenningCasper/Bachelor-project/Braitenberg.cpp > CMakeFiles/bachelor.dir/Braitenberg.cpp.i

CMakeFiles/bachelor.dir/Braitenberg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bachelor.dir/Braitenberg.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/HenningCasper/Bachelor-project/Braitenberg.cpp -o CMakeFiles/bachelor.dir/Braitenberg.cpp.s

# Object files for target bachelor
bachelor_OBJECTS = \
"CMakeFiles/bachelor.dir/main.cpp.o" \
"CMakeFiles/bachelor.dir/controller.cpp.o" \
"CMakeFiles/bachelor.dir/Braitenberg.cpp.o"

# External object files for target bachelor
bachelor_EXTERNAL_OBJECTS =

bachelor: CMakeFiles/bachelor.dir/main.cpp.o
bachelor: CMakeFiles/bachelor.dir/controller.cpp.o
bachelor: CMakeFiles/bachelor.dir/Braitenberg.cpp.o
bachelor: CMakeFiles/bachelor.dir/build.make
bachelor: CMakeFiles/bachelor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/HenningCasper/Bachelor-project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable bachelor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bachelor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bachelor.dir/build: bachelor

.PHONY : CMakeFiles/bachelor.dir/build

CMakeFiles/bachelor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bachelor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bachelor.dir/clean

CMakeFiles/bachelor.dir/depend:
	cd /home/pi/HenningCasper/Bachelor-project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/HenningCasper/Bachelor-project /home/pi/HenningCasper/Bachelor-project /home/pi/HenningCasper/Bachelor-project/build /home/pi/HenningCasper/Bachelor-project/build /home/pi/HenningCasper/Bachelor-project/build/CMakeFiles/bachelor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bachelor.dir/depend

