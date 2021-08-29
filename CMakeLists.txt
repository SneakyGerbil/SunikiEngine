#Set CMake min version and project name
cmake_minimum_required(VERSION 3.10)
project(SunikiEngine VERSION 1.0.0)

add_subdirectory(include/glad)
add_subdirectory(include/glfw)
add_subdirectory(include/stb_image)
add_subdirectory(src)