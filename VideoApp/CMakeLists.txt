# CMakeList.txt : CMake project for VideoApp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.17)

project (VideoApp C CXX)

set(CMAKE_CXX_STANDARD 14)

set(SHADERS
    shaders/vertex/default.vs
    shaders/fragment/default.fs
)

add_subdirectory(lib/glfw)

# Add the given directories to those the compiler uses to search for include files.
# Relative paths are interpreted as relative to the current source directory.
include_directories(AFTER "include")

find_package(OpenGL REQUIRED)

# Add source to this project's executable.
add_executable (VideoApp "src/hello_rectangle.cpp" "include/Shader.h" "include/VideoApp.h" "src/VideoApp.cpp" "src/glad.c" "src/hello_rectangle.cpp" "include/Shader.h" )



target_link_libraries(VideoApp 
	glfw 
	${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
)


file (GLOB_RECURSE resources "src/shaders/*.*")
foreach(resource ${resources})
 get_filename_component(filename ${resource} NAME)
 get_filename_component(dir ${resource} DIRECTORY)
 get_filename_component(dirname ${dir} NAME)
 
 set (output "")
 
 while(NOT ${dirname} STREQUAL shaders)
  get_filename_component(path_component ${dir} NAME)
  set (output "${path_component}/${output}")
  get_filename_component(dir ${dir} DIRECTORY)
  get_filename_component(dirname ${dir} NAME)
 endwhile()
 
 set(output "${CMAKE_CURRENT_BINARY_DIR}/shaders/${output}/${filename}")
 
 add_custom_command(
  COMMENT "Moving updated resource-file '${filename}'"
  OUTPUT ${output}
  DEPENDS ${resource}
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${resource}
  ${output}
 )
 add_custom_target(${filename} ALL DEPENDS ${resource} ${output})
 
endforeach()