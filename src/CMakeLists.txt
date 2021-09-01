#Add the executable
add_executable("${PROJECT_NAME}" engine/engine.cpp)

#Set final executable location to build dir
set_target_properties("${PROJECT_NAME}"
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/SunikiEngine"
    )

#Link OpenGL libraries GLAD and GLFW to every target in directory
link_libraries(
    glad
    glfw
    glm
    )

#Link needed librariies to every target in directory
link_libraries(
    stb_image
    )

#Add shader directory
add_subdirectory(renderer/shader)

#Link shader library to engine
target_link_libraries(
    "${PROJECT_NAME}"
    PRIVATE shader
    )