#Create stb_image library target
add_library(
    stb_image
    stb_image.h
    stb_image.cpp
    )

#Add stb_image directory to the include directory of the stb_image library target
target_include_directories(stb_image PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")