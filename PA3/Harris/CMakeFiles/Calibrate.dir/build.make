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
CMAKE_SOURCE_DIR = /home/marco/Desktop/CV/PA3/Harris

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marco/Desktop/CV/PA3/Harris

# Include any dependencies generated for this target.
include CMakeFiles/Calibrate.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Calibrate.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Calibrate.dir/flags.make

CMakeFiles/Calibrate.dir/main.cpp.o: CMakeFiles/Calibrate.dir/flags.make
CMakeFiles/Calibrate.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marco/Desktop/CV/PA3/Harris/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Calibrate.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Calibrate.dir/main.cpp.o -c /home/marco/Desktop/CV/PA3/Harris/main.cpp

CMakeFiles/Calibrate.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Calibrate.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marco/Desktop/CV/PA3/Harris/main.cpp > CMakeFiles/Calibrate.dir/main.cpp.i

CMakeFiles/Calibrate.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Calibrate.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marco/Desktop/CV/PA3/Harris/main.cpp -o CMakeFiles/Calibrate.dir/main.cpp.s

CMakeFiles/Calibrate.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Calibrate.dir/main.cpp.o.requires

CMakeFiles/Calibrate.dir/main.cpp.o.provides: CMakeFiles/Calibrate.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Calibrate.dir/build.make CMakeFiles/Calibrate.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Calibrate.dir/main.cpp.o.provides

CMakeFiles/Calibrate.dir/main.cpp.o.provides.build: CMakeFiles/Calibrate.dir/main.cpp.o


# Object files for target Calibrate
Calibrate_OBJECTS = \
"CMakeFiles/Calibrate.dir/main.cpp.o"

# External object files for target Calibrate
Calibrate_EXTERNAL_OBJECTS =

Calibrate: CMakeFiles/Calibrate.dir/main.cpp.o
Calibrate: CMakeFiles/Calibrate.dir/build.make
Calibrate: /usr/local/lib/libopencv_videostab.so.2.4.13
Calibrate: /usr/local/lib/libopencv_ts.a
Calibrate: /usr/local/lib/libopencv_superres.so.2.4.13
Calibrate: /usr/local/lib/libopencv_stitching.so.2.4.13
Calibrate: /usr/local/lib/libopencv_contrib.so.2.4.13
Calibrate: /usr/local/lib/libopencv_nonfree.so.2.4.13
Calibrate: /usr/local/lib/libopencv_ocl.so.2.4.13
Calibrate: /usr/local/lib/libopencv_gpu.so.2.4.13
Calibrate: /usr/local/lib/libopencv_photo.so.2.4.13
Calibrate: /usr/local/lib/libopencv_objdetect.so.2.4.13
Calibrate: /usr/local/lib/libopencv_legacy.so.2.4.13
Calibrate: /usr/local/lib/libopencv_video.so.2.4.13
Calibrate: /usr/local/lib/libopencv_ml.so.2.4.13
Calibrate: /usr/local/lib/libopencv_calib3d.so.2.4.13
Calibrate: /usr/local/lib/libopencv_features2d.so.2.4.13
Calibrate: /usr/local/lib/libopencv_highgui.so.2.4.13
Calibrate: /usr/local/lib/libopencv_imgproc.so.2.4.13
Calibrate: /usr/local/lib/libopencv_flann.so.2.4.13
Calibrate: /usr/local/lib/libopencv_core.so.2.4.13
Calibrate: CMakeFiles/Calibrate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marco/Desktop/CV/PA3/Harris/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Calibrate"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Calibrate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Calibrate.dir/build: Calibrate

.PHONY : CMakeFiles/Calibrate.dir/build

CMakeFiles/Calibrate.dir/requires: CMakeFiles/Calibrate.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Calibrate.dir/requires

CMakeFiles/Calibrate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Calibrate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Calibrate.dir/clean

CMakeFiles/Calibrate.dir/depend:
	cd /home/marco/Desktop/CV/PA3/Harris && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marco/Desktop/CV/PA3/Harris /home/marco/Desktop/CV/PA3/Harris /home/marco/Desktop/CV/PA3/Harris /home/marco/Desktop/CV/PA3/Harris /home/marco/Desktop/CV/PA3/Harris/CMakeFiles/Calibrate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Calibrate.dir/depend

