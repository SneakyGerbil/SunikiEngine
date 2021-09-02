#Add camera class as library target
add_library(
    camera
    camera.hpp
    camera.cpp
)

#Add shader directory to the include directory of the shader library target
target_include_directories(shader PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")