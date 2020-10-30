# CMakeList.txt : CMake project for VideoApp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)

project (VideoApp C CXX)

set(CMAKE_CXX_STANDARD 14)


add_subdirectory(lib/glfw)

# Add the given directories to those the compiler uses to search for include files.
# Relative paths are interpreted as relative to the current source directory.
include_directories(AFTER "include")

find_package(OpenGL REQUIRED)


# Add source to this project's executable.
add_executable (VideoApp "src/main.cpp" "include/VideoApp.h" "src/VideoApp.cpp" "src/glad.c")


target_link_libraries(VideoApp 
	glfw 
	${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
)