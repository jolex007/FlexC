# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.15.5/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.15.5/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jolex007/Documents/programming/FlexC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jolex007/Documents/programming/FlexC/build

# Include any dependencies generated for this target.
include src/CMakeFiles/FlexC_src.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/FlexC_src.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/FlexC_src.dir/flags.make

src/CMakeFiles/FlexC_src.dir/interpreter.cpp.o: src/CMakeFiles/FlexC_src.dir/flags.make
src/CMakeFiles/FlexC_src.dir/interpreter.cpp.o: ../src/interpreter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jolex007/Documents/programming/FlexC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/FlexC_src.dir/interpreter.cpp.o"
	cd /Users/jolex007/Documents/programming/FlexC/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FlexC_src.dir/interpreter.cpp.o -c /Users/jolex007/Documents/programming/FlexC/src/interpreter.cpp

src/CMakeFiles/FlexC_src.dir/interpreter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FlexC_src.dir/interpreter.cpp.i"
	cd /Users/jolex007/Documents/programming/FlexC/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jolex007/Documents/programming/FlexC/src/interpreter.cpp > CMakeFiles/FlexC_src.dir/interpreter.cpp.i

src/CMakeFiles/FlexC_src.dir/interpreter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FlexC_src.dir/interpreter.cpp.s"
	cd /Users/jolex007/Documents/programming/FlexC/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jolex007/Documents/programming/FlexC/src/interpreter.cpp -o CMakeFiles/FlexC_src.dir/interpreter.cpp.s

src/CMakeFiles/FlexC_src.dir/lexical_analyzer.cpp.o: src/CMakeFiles/FlexC_src.dir/flags.make
src/CMakeFiles/FlexC_src.dir/lexical_analyzer.cpp.o: ../src/lexical_analyzer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jolex007/Documents/programming/FlexC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/FlexC_src.dir/lexical_analyzer.cpp.o"
	cd /Users/jolex007/Documents/programming/FlexC/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FlexC_src.dir/lexical_analyzer.cpp.o -c /Users/jolex007/Documents/programming/FlexC/src/lexical_analyzer.cpp

src/CMakeFiles/FlexC_src.dir/lexical_analyzer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FlexC_src.dir/lexical_analyzer.cpp.i"
	cd /Users/jolex007/Documents/programming/FlexC/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jolex007/Documents/programming/FlexC/src/lexical_analyzer.cpp > CMakeFiles/FlexC_src.dir/lexical_analyzer.cpp.i

src/CMakeFiles/FlexC_src.dir/lexical_analyzer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FlexC_src.dir/lexical_analyzer.cpp.s"
	cd /Users/jolex007/Documents/programming/FlexC/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jolex007/Documents/programming/FlexC/src/lexical_analyzer.cpp -o CMakeFiles/FlexC_src.dir/lexical_analyzer.cpp.s

src/CMakeFiles/FlexC_src.dir/parser.cpp.o: src/CMakeFiles/FlexC_src.dir/flags.make
src/CMakeFiles/FlexC_src.dir/parser.cpp.o: ../src/parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jolex007/Documents/programming/FlexC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/FlexC_src.dir/parser.cpp.o"
	cd /Users/jolex007/Documents/programming/FlexC/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FlexC_src.dir/parser.cpp.o -c /Users/jolex007/Documents/programming/FlexC/src/parser.cpp

src/CMakeFiles/FlexC_src.dir/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FlexC_src.dir/parser.cpp.i"
	cd /Users/jolex007/Documents/programming/FlexC/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jolex007/Documents/programming/FlexC/src/parser.cpp > CMakeFiles/FlexC_src.dir/parser.cpp.i

src/CMakeFiles/FlexC_src.dir/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FlexC_src.dir/parser.cpp.s"
	cd /Users/jolex007/Documents/programming/FlexC/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jolex007/Documents/programming/FlexC/src/parser.cpp -o CMakeFiles/FlexC_src.dir/parser.cpp.s

# Object files for target FlexC_src
FlexC_src_OBJECTS = \
"CMakeFiles/FlexC_src.dir/interpreter.cpp.o" \
"CMakeFiles/FlexC_src.dir/lexical_analyzer.cpp.o" \
"CMakeFiles/FlexC_src.dir/parser.cpp.o"

# External object files for target FlexC_src
FlexC_src_EXTERNAL_OBJECTS =

../lib/libFlexC_src.dylib: src/CMakeFiles/FlexC_src.dir/interpreter.cpp.o
../lib/libFlexC_src.dylib: src/CMakeFiles/FlexC_src.dir/lexical_analyzer.cpp.o
../lib/libFlexC_src.dylib: src/CMakeFiles/FlexC_src.dir/parser.cpp.o
../lib/libFlexC_src.dylib: src/CMakeFiles/FlexC_src.dir/build.make
../lib/libFlexC_src.dylib: src/CMakeFiles/FlexC_src.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jolex007/Documents/programming/FlexC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library ../../lib/libFlexC_src.dylib"
	cd /Users/jolex007/Documents/programming/FlexC/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FlexC_src.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/FlexC_src.dir/build: ../lib/libFlexC_src.dylib

.PHONY : src/CMakeFiles/FlexC_src.dir/build

src/CMakeFiles/FlexC_src.dir/clean:
	cd /Users/jolex007/Documents/programming/FlexC/build/src && $(CMAKE_COMMAND) -P CMakeFiles/FlexC_src.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/FlexC_src.dir/clean

src/CMakeFiles/FlexC_src.dir/depend:
	cd /Users/jolex007/Documents/programming/FlexC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jolex007/Documents/programming/FlexC /Users/jolex007/Documents/programming/FlexC/src /Users/jolex007/Documents/programming/FlexC/build /Users/jolex007/Documents/programming/FlexC/build/src /Users/jolex007/Documents/programming/FlexC/build/src/CMakeFiles/FlexC_src.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/FlexC_src.dir/depend
