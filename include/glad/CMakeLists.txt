#Create glad library target
add_library(
    glad
    include/glad/glad.h
    src/glad.c
    )

#Add glad directory to the include directory of the glad library target
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")