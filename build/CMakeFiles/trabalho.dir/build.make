# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP/build

# Include any dependencies generated for this target.
include CMakeFiles/trabalho.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/trabalho.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/trabalho.dir/flags.make

CMakeFiles/trabalho.dir/main.c.o: CMakeFiles/trabalho.dir/flags.make
CMakeFiles/trabalho.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/trabalho.dir/main.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/trabalho.dir/main.c.o   -c /mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP/main.c

CMakeFiles/trabalho.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/trabalho.dir/main.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP/main.c > CMakeFiles/trabalho.dir/main.c.i

CMakeFiles/trabalho.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/trabalho.dir/main.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP/main.c -o CMakeFiles/trabalho.dir/main.c.s

CMakeFiles/trabalho.dir/aux.c.o: CMakeFiles/trabalho.dir/flags.make
CMakeFiles/trabalho.dir/aux.c.o: ../aux.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/trabalho.dir/aux.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/trabalho.dir/aux.c.o   -c /mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP/aux.c

CMakeFiles/trabalho.dir/aux.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/trabalho.dir/aux.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP/aux.c > CMakeFiles/trabalho.dir/aux.c.i

CMakeFiles/trabalho.dir/aux.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/trabalho.dir/aux.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP/aux.c -o CMakeFiles/trabalho.dir/aux.c.s

# Object files for target trabalho
trabalho_OBJECTS = \
"CMakeFiles/trabalho.dir/main.c.o" \
"CMakeFiles/trabalho.dir/aux.c.o"

# External object files for target trabalho
trabalho_EXTERNAL_OBJECTS =

trabalho: CMakeFiles/trabalho.dir/main.c.o
trabalho: CMakeFiles/trabalho.dir/aux.c.o
trabalho: CMakeFiles/trabalho.dir/build.make
trabalho: CMakeFiles/trabalho.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable trabalho"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/trabalho.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/trabalho.dir/build: trabalho

.PHONY : CMakeFiles/trabalho.dir/build

CMakeFiles/trabalho.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/trabalho.dir/cmake_clean.cmake
.PHONY : CMakeFiles/trabalho.dir/clean

CMakeFiles/trabalho.dir/depend:
	cd /mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP /mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP /mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP/build /mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP/build /mnt/c/Users/Utilizador/Documents/GitHub/Trabalho_PPP/build/CMakeFiles/trabalho.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/trabalho.dir/depend
