# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /home/ishan/.local/lib/python3.10/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/ishan/.local/lib/python3.10/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/build"

# Include any dependencies generated for this target.
include CMakeFiles/project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project.dir/flags.make

CMakeFiles/project.dir/src/main.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/src/main.cpp.o: /home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/src/main.cpp
CMakeFiles/project.dir/src/main.cpp.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/project.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project.dir/src/main.cpp.o -MF CMakeFiles/project.dir/src/main.cpp.o.d -o CMakeFiles/project.dir/src/main.cpp.o -c "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/src/main.cpp"

CMakeFiles/project.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/src/main.cpp" > CMakeFiles/project.dir/src/main.cpp.i

CMakeFiles/project.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/src/main.cpp" -o CMakeFiles/project.dir/src/main.cpp.s

CMakeFiles/project.dir/src/utils.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/src/utils.cpp.o: /home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/src/utils.cpp
CMakeFiles/project.dir/src/utils.cpp.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/project.dir/src/utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project.dir/src/utils.cpp.o -MF CMakeFiles/project.dir/src/utils.cpp.o.d -o CMakeFiles/project.dir/src/utils.cpp.o -c "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/src/utils.cpp"

CMakeFiles/project.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/src/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/src/utils.cpp" > CMakeFiles/project.dir/src/utils.cpp.i

CMakeFiles/project.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/src/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/src/utils.cpp" -o CMakeFiles/project.dir/src/utils.cpp.s

CMakeFiles/project.dir/depends/imgui/imgui_impl_glfw.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/depends/imgui/imgui_impl_glfw.cpp.o: /home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_impl_glfw.cpp
CMakeFiles/project.dir/depends/imgui/imgui_impl_glfw.cpp.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/project.dir/depends/imgui/imgui_impl_glfw.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project.dir/depends/imgui/imgui_impl_glfw.cpp.o -MF CMakeFiles/project.dir/depends/imgui/imgui_impl_glfw.cpp.o.d -o CMakeFiles/project.dir/depends/imgui/imgui_impl_glfw.cpp.o -c "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_impl_glfw.cpp"

CMakeFiles/project.dir/depends/imgui/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/depends/imgui/imgui_impl_glfw.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_impl_glfw.cpp" > CMakeFiles/project.dir/depends/imgui/imgui_impl_glfw.cpp.i

CMakeFiles/project.dir/depends/imgui/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/depends/imgui/imgui_impl_glfw.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_impl_glfw.cpp" -o CMakeFiles/project.dir/depends/imgui/imgui_impl_glfw.cpp.s

CMakeFiles/project.dir/depends/imgui/imgui_impl_opengl3.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/depends/imgui/imgui_impl_opengl3.cpp.o: /home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_impl_opengl3.cpp
CMakeFiles/project.dir/depends/imgui/imgui_impl_opengl3.cpp.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/project.dir/depends/imgui/imgui_impl_opengl3.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project.dir/depends/imgui/imgui_impl_opengl3.cpp.o -MF CMakeFiles/project.dir/depends/imgui/imgui_impl_opengl3.cpp.o.d -o CMakeFiles/project.dir/depends/imgui/imgui_impl_opengl3.cpp.o -c "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_impl_opengl3.cpp"

CMakeFiles/project.dir/depends/imgui/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/depends/imgui/imgui_impl_opengl3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_impl_opengl3.cpp" > CMakeFiles/project.dir/depends/imgui/imgui_impl_opengl3.cpp.i

CMakeFiles/project.dir/depends/imgui/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/depends/imgui/imgui_impl_opengl3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_impl_opengl3.cpp" -o CMakeFiles/project.dir/depends/imgui/imgui_impl_opengl3.cpp.s

CMakeFiles/project.dir/depends/imgui/imgui.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/depends/imgui/imgui.cpp.o: /home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/depends/imgui/imgui.cpp
CMakeFiles/project.dir/depends/imgui/imgui.cpp.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/project.dir/depends/imgui/imgui.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project.dir/depends/imgui/imgui.cpp.o -MF CMakeFiles/project.dir/depends/imgui/imgui.cpp.o.d -o CMakeFiles/project.dir/depends/imgui/imgui.cpp.o -c "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui.cpp"

CMakeFiles/project.dir/depends/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/depends/imgui/imgui.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui.cpp" > CMakeFiles/project.dir/depends/imgui/imgui.cpp.i

CMakeFiles/project.dir/depends/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/depends/imgui/imgui.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui.cpp" -o CMakeFiles/project.dir/depends/imgui/imgui.cpp.s

CMakeFiles/project.dir/depends/imgui/imgui_demo.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/depends/imgui/imgui_demo.cpp.o: /home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_demo.cpp
CMakeFiles/project.dir/depends/imgui/imgui_demo.cpp.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/project.dir/depends/imgui/imgui_demo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project.dir/depends/imgui/imgui_demo.cpp.o -MF CMakeFiles/project.dir/depends/imgui/imgui_demo.cpp.o.d -o CMakeFiles/project.dir/depends/imgui/imgui_demo.cpp.o -c "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_demo.cpp"

CMakeFiles/project.dir/depends/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/depends/imgui/imgui_demo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_demo.cpp" > CMakeFiles/project.dir/depends/imgui/imgui_demo.cpp.i

CMakeFiles/project.dir/depends/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/depends/imgui/imgui_demo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_demo.cpp" -o CMakeFiles/project.dir/depends/imgui/imgui_demo.cpp.s

CMakeFiles/project.dir/depends/imgui/imgui_draw.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/depends/imgui/imgui_draw.cpp.o: /home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_draw.cpp
CMakeFiles/project.dir/depends/imgui/imgui_draw.cpp.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/project.dir/depends/imgui/imgui_draw.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project.dir/depends/imgui/imgui_draw.cpp.o -MF CMakeFiles/project.dir/depends/imgui/imgui_draw.cpp.o.d -o CMakeFiles/project.dir/depends/imgui/imgui_draw.cpp.o -c "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_draw.cpp"

CMakeFiles/project.dir/depends/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/depends/imgui/imgui_draw.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_draw.cpp" > CMakeFiles/project.dir/depends/imgui/imgui_draw.cpp.i

CMakeFiles/project.dir/depends/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/depends/imgui/imgui_draw.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_draw.cpp" -o CMakeFiles/project.dir/depends/imgui/imgui_draw.cpp.s

CMakeFiles/project.dir/depends/imgui/imgui_widgets.cpp.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/depends/imgui/imgui_widgets.cpp.o: /home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_widgets.cpp
CMakeFiles/project.dir/depends/imgui/imgui_widgets.cpp.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/project.dir/depends/imgui/imgui_widgets.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/project.dir/depends/imgui/imgui_widgets.cpp.o -MF CMakeFiles/project.dir/depends/imgui/imgui_widgets.cpp.o.d -o CMakeFiles/project.dir/depends/imgui/imgui_widgets.cpp.o -c "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_widgets.cpp"

CMakeFiles/project.dir/depends/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project.dir/depends/imgui/imgui_widgets.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_widgets.cpp" > CMakeFiles/project.dir/depends/imgui/imgui_widgets.cpp.i

CMakeFiles/project.dir/depends/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project.dir/depends/imgui/imgui_widgets.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/depends/imgui/imgui_widgets.cpp" -o CMakeFiles/project.dir/depends/imgui/imgui_widgets.cpp.s

# Object files for target project
project_OBJECTS = \
"CMakeFiles/project.dir/src/main.cpp.o" \
"CMakeFiles/project.dir/src/utils.cpp.o" \
"CMakeFiles/project.dir/depends/imgui/imgui_impl_glfw.cpp.o" \
"CMakeFiles/project.dir/depends/imgui/imgui_impl_opengl3.cpp.o" \
"CMakeFiles/project.dir/depends/imgui/imgui.cpp.o" \
"CMakeFiles/project.dir/depends/imgui/imgui_demo.cpp.o" \
"CMakeFiles/project.dir/depends/imgui/imgui_draw.cpp.o" \
"CMakeFiles/project.dir/depends/imgui/imgui_widgets.cpp.o"

# External object files for target project
project_EXTERNAL_OBJECTS =

/home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/project: CMakeFiles/project.dir/src/main.cpp.o
/home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/project: CMakeFiles/project.dir/src/utils.cpp.o
/home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/project: CMakeFiles/project.dir/depends/imgui/imgui_impl_glfw.cpp.o
/home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/project: CMakeFiles/project.dir/depends/imgui/imgui_impl_opengl3.cpp.o
/home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/project: CMakeFiles/project.dir/depends/imgui/imgui.cpp.o
/home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/project: CMakeFiles/project.dir/depends/imgui/imgui_demo.cpp.o
/home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/project: CMakeFiles/project.dir/depends/imgui/imgui_draw.cpp.o
/home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/project: CMakeFiles/project.dir/depends/imgui/imgui_widgets.cpp.o
/home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/project: CMakeFiles/project.dir/build.make
/home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/project: /usr/lib/x86_64-linux-gnu/libGL.so
/home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/project: /usr/lib/x86_64-linux-gnu/libGLU.so
/home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/project: /usr/lib/x86_64-linux-gnu/libglfw.so.3.3
/home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/project: /usr/lib/x86_64-linux-gnu/libGLEW.so
/home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/project: CMakeFiles/project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable \"/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/project\""
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project.dir/build: /home/ishan/Documents/Computer\ Graphics/Assignments/project/codes/code_3/project
.PHONY : CMakeFiles/project.dir/build

CMakeFiles/project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/project.dir/clean

CMakeFiles/project.dir/depend:
	cd "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3" "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3" "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/build" "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/build" "/home/ishan/Documents/Computer Graphics/Assignments/project/codes/code_3/build/CMakeFiles/project.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/project.dir/depend

