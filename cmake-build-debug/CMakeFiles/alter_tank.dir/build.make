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
CMAKE_COMMAND = /opt/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ali/Documents/fop/project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ali/Documents/fop/project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/alter_tank.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/alter_tank.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/alter_tank.dir/flags.make

CMakeFiles/alter_tank.dir/src/bullet.c.o: CMakeFiles/alter_tank.dir/flags.make
CMakeFiles/alter_tank.dir/src/bullet.c.o: ../src/bullet.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ali/Documents/fop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/alter_tank.dir/src/bullet.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/alter_tank.dir/src/bullet.c.o   -c /home/ali/Documents/fop/project/src/bullet.c

CMakeFiles/alter_tank.dir/src/bullet.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/alter_tank.dir/src/bullet.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ali/Documents/fop/project/src/bullet.c > CMakeFiles/alter_tank.dir/src/bullet.c.i

CMakeFiles/alter_tank.dir/src/bullet.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/alter_tank.dir/src/bullet.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ali/Documents/fop/project/src/bullet.c -o CMakeFiles/alter_tank.dir/src/bullet.c.s

CMakeFiles/alter_tank.dir/src/colors.c.o: CMakeFiles/alter_tank.dir/flags.make
CMakeFiles/alter_tank.dir/src/colors.c.o: ../src/colors.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ali/Documents/fop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/alter_tank.dir/src/colors.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/alter_tank.dir/src/colors.c.o   -c /home/ali/Documents/fop/project/src/colors.c

CMakeFiles/alter_tank.dir/src/colors.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/alter_tank.dir/src/colors.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ali/Documents/fop/project/src/colors.c > CMakeFiles/alter_tank.dir/src/colors.c.i

CMakeFiles/alter_tank.dir/src/colors.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/alter_tank.dir/src/colors.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ali/Documents/fop/project/src/colors.c -o CMakeFiles/alter_tank.dir/src/colors.c.s

CMakeFiles/alter_tank.dir/src/graphics.c.o: CMakeFiles/alter_tank.dir/flags.make
CMakeFiles/alter_tank.dir/src/graphics.c.o: ../src/graphics.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ali/Documents/fop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/alter_tank.dir/src/graphics.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/alter_tank.dir/src/graphics.c.o   -c /home/ali/Documents/fop/project/src/graphics.c

CMakeFiles/alter_tank.dir/src/graphics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/alter_tank.dir/src/graphics.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ali/Documents/fop/project/src/graphics.c > CMakeFiles/alter_tank.dir/src/graphics.c.i

CMakeFiles/alter_tank.dir/src/graphics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/alter_tank.dir/src/graphics.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ali/Documents/fop/project/src/graphics.c -o CMakeFiles/alter_tank.dir/src/graphics.c.s

CMakeFiles/alter_tank.dir/src/keyboard_handler.c.o: CMakeFiles/alter_tank.dir/flags.make
CMakeFiles/alter_tank.dir/src/keyboard_handler.c.o: ../src/keyboard_handler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ali/Documents/fop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/alter_tank.dir/src/keyboard_handler.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/alter_tank.dir/src/keyboard_handler.c.o   -c /home/ali/Documents/fop/project/src/keyboard_handler.c

CMakeFiles/alter_tank.dir/src/keyboard_handler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/alter_tank.dir/src/keyboard_handler.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ali/Documents/fop/project/src/keyboard_handler.c > CMakeFiles/alter_tank.dir/src/keyboard_handler.c.i

CMakeFiles/alter_tank.dir/src/keyboard_handler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/alter_tank.dir/src/keyboard_handler.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ali/Documents/fop/project/src/keyboard_handler.c -o CMakeFiles/alter_tank.dir/src/keyboard_handler.c.s

CMakeFiles/alter_tank.dir/src/main.c.o: CMakeFiles/alter_tank.dir/flags.make
CMakeFiles/alter_tank.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ali/Documents/fop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/alter_tank.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/alter_tank.dir/src/main.c.o   -c /home/ali/Documents/fop/project/src/main.c

CMakeFiles/alter_tank.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/alter_tank.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ali/Documents/fop/project/src/main.c > CMakeFiles/alter_tank.dir/src/main.c.i

CMakeFiles/alter_tank.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/alter_tank.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ali/Documents/fop/project/src/main.c -o CMakeFiles/alter_tank.dir/src/main.c.s

CMakeFiles/alter_tank.dir/src/manager.c.o: CMakeFiles/alter_tank.dir/flags.make
CMakeFiles/alter_tank.dir/src/manager.c.o: ../src/manager.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ali/Documents/fop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/alter_tank.dir/src/manager.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/alter_tank.dir/src/manager.c.o   -c /home/ali/Documents/fop/project/src/manager.c

CMakeFiles/alter_tank.dir/src/manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/alter_tank.dir/src/manager.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ali/Documents/fop/project/src/manager.c > CMakeFiles/alter_tank.dir/src/manager.c.i

CMakeFiles/alter_tank.dir/src/manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/alter_tank.dir/src/manager.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ali/Documents/fop/project/src/manager.c -o CMakeFiles/alter_tank.dir/src/manager.c.s

CMakeFiles/alter_tank.dir/src/map.c.o: CMakeFiles/alter_tank.dir/flags.make
CMakeFiles/alter_tank.dir/src/map.c.o: ../src/map.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ali/Documents/fop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/alter_tank.dir/src/map.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/alter_tank.dir/src/map.c.o   -c /home/ali/Documents/fop/project/src/map.c

CMakeFiles/alter_tank.dir/src/map.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/alter_tank.dir/src/map.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ali/Documents/fop/project/src/map.c > CMakeFiles/alter_tank.dir/src/map.c.i

CMakeFiles/alter_tank.dir/src/map.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/alter_tank.dir/src/map.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ali/Documents/fop/project/src/map.c -o CMakeFiles/alter_tank.dir/src/map.c.s

CMakeFiles/alter_tank.dir/src/particle.c.o: CMakeFiles/alter_tank.dir/flags.make
CMakeFiles/alter_tank.dir/src/particle.c.o: ../src/particle.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ali/Documents/fop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/alter_tank.dir/src/particle.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/alter_tank.dir/src/particle.c.o   -c /home/ali/Documents/fop/project/src/particle.c

CMakeFiles/alter_tank.dir/src/particle.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/alter_tank.dir/src/particle.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ali/Documents/fop/project/src/particle.c > CMakeFiles/alter_tank.dir/src/particle.c.i

CMakeFiles/alter_tank.dir/src/particle.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/alter_tank.dir/src/particle.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ali/Documents/fop/project/src/particle.c -o CMakeFiles/alter_tank.dir/src/particle.c.s

CMakeFiles/alter_tank.dir/src/physics.c.o: CMakeFiles/alter_tank.dir/flags.make
CMakeFiles/alter_tank.dir/src/physics.c.o: ../src/physics.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ali/Documents/fop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/alter_tank.dir/src/physics.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/alter_tank.dir/src/physics.c.o   -c /home/ali/Documents/fop/project/src/physics.c

CMakeFiles/alter_tank.dir/src/physics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/alter_tank.dir/src/physics.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ali/Documents/fop/project/src/physics.c > CMakeFiles/alter_tank.dir/src/physics.c.i

CMakeFiles/alter_tank.dir/src/physics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/alter_tank.dir/src/physics.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ali/Documents/fop/project/src/physics.c -o CMakeFiles/alter_tank.dir/src/physics.c.s

CMakeFiles/alter_tank.dir/src/structs.c.o: CMakeFiles/alter_tank.dir/flags.make
CMakeFiles/alter_tank.dir/src/structs.c.o: ../src/structs.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ali/Documents/fop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/alter_tank.dir/src/structs.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/alter_tank.dir/src/structs.c.o   -c /home/ali/Documents/fop/project/src/structs.c

CMakeFiles/alter_tank.dir/src/structs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/alter_tank.dir/src/structs.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ali/Documents/fop/project/src/structs.c > CMakeFiles/alter_tank.dir/src/structs.c.i

CMakeFiles/alter_tank.dir/src/structs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/alter_tank.dir/src/structs.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ali/Documents/fop/project/src/structs.c -o CMakeFiles/alter_tank.dir/src/structs.c.s

CMakeFiles/alter_tank.dir/src/tank.c.o: CMakeFiles/alter_tank.dir/flags.make
CMakeFiles/alter_tank.dir/src/tank.c.o: ../src/tank.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ali/Documents/fop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/alter_tank.dir/src/tank.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/alter_tank.dir/src/tank.c.o   -c /home/ali/Documents/fop/project/src/tank.c

CMakeFiles/alter_tank.dir/src/tank.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/alter_tank.dir/src/tank.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ali/Documents/fop/project/src/tank.c > CMakeFiles/alter_tank.dir/src/tank.c.i

CMakeFiles/alter_tank.dir/src/tank.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/alter_tank.dir/src/tank.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ali/Documents/fop/project/src/tank.c -o CMakeFiles/alter_tank.dir/src/tank.c.s

# Object files for target alter_tank
alter_tank_OBJECTS = \
"CMakeFiles/alter_tank.dir/src/bullet.c.o" \
"CMakeFiles/alter_tank.dir/src/colors.c.o" \
"CMakeFiles/alter_tank.dir/src/graphics.c.o" \
"CMakeFiles/alter_tank.dir/src/keyboard_handler.c.o" \
"CMakeFiles/alter_tank.dir/src/main.c.o" \
"CMakeFiles/alter_tank.dir/src/manager.c.o" \
"CMakeFiles/alter_tank.dir/src/map.c.o" \
"CMakeFiles/alter_tank.dir/src/particle.c.o" \
"CMakeFiles/alter_tank.dir/src/physics.c.o" \
"CMakeFiles/alter_tank.dir/src/structs.c.o" \
"CMakeFiles/alter_tank.dir/src/tank.c.o"

# External object files for target alter_tank
alter_tank_EXTERNAL_OBJECTS =

alter_tank: CMakeFiles/alter_tank.dir/src/bullet.c.o
alter_tank: CMakeFiles/alter_tank.dir/src/colors.c.o
alter_tank: CMakeFiles/alter_tank.dir/src/graphics.c.o
alter_tank: CMakeFiles/alter_tank.dir/src/keyboard_handler.c.o
alter_tank: CMakeFiles/alter_tank.dir/src/main.c.o
alter_tank: CMakeFiles/alter_tank.dir/src/manager.c.o
alter_tank: CMakeFiles/alter_tank.dir/src/map.c.o
alter_tank: CMakeFiles/alter_tank.dir/src/particle.c.o
alter_tank: CMakeFiles/alter_tank.dir/src/physics.c.o
alter_tank: CMakeFiles/alter_tank.dir/src/structs.c.o
alter_tank: CMakeFiles/alter_tank.dir/src/tank.c.o
alter_tank: CMakeFiles/alter_tank.dir/build.make
alter_tank: CMakeFiles/alter_tank.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ali/Documents/fop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking C executable alter_tank"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/alter_tank.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/alter_tank.dir/build: alter_tank

.PHONY : CMakeFiles/alter_tank.dir/build

CMakeFiles/alter_tank.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/alter_tank.dir/cmake_clean.cmake
.PHONY : CMakeFiles/alter_tank.dir/clean

CMakeFiles/alter_tank.dir/depend:
	cd /home/ali/Documents/fop/project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ali/Documents/fop/project /home/ali/Documents/fop/project /home/ali/Documents/fop/project/cmake-build-debug /home/ali/Documents/fop/project/cmake-build-debug /home/ali/Documents/fop/project/cmake-build-debug/CMakeFiles/alter_tank.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/alter_tank.dir/depend

