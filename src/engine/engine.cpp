#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>
#include <shader.hpp>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


int main(){
    //====================//
    // Initialize Window  //
    //====================//

    //Initialize GLFW
    if(!glfwInit()){ //Check for errors
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    //Set OpenGL version 3 core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    //Set window invisible until everything is set up
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    //Create a window and its context
    GLFWwindow* window = glfwCreateWindow(800, 800, "Suniki Engine", NULL, NULL);
    if(window == NULL){ //Check for errors
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //Set created window as current
    glfwMakeContextCurrent(window);
    
    //Set GLAD loader for the current context
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //====================//
    //   Configuration    //
    //====================//

    //Set window resize callback (Called whenever window gets resized)
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);







    //Vertex data
    float vertices[] = {
            // positions         // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
           -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
           -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    //Generate Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    //Generate Element Buffer Object
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    //Generate Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    
    //Bind VAO
    glBindVertexArray(VAO);

    //Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Set vertex shader attributes
        //Vertex position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        //Vertex color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //Vertex texture coordinates
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

    //Bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Unbind VAO
    glBindVertexArray(0);









    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    //Set texture wrapping and filtering options (for currently bound texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Load first image and its info (width, height and number of color channels)
    int width, height, nrChannels;
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    if(data){ //If data was successfully fetched
        //Generate texture from image data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        //Free image memory
        stbi_image_free(data);
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
    }

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    //Set texture wrapping and filtering options (for currently bound texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Load second image and its info (width, height and number of color channels)
    data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
    if(data){ //If data was successfully fetched
        //Generate texture from image data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        //Free image memory
        stbi_image_free(data);
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
    }





    //Show window after all config is done
    glfwShowWindow(window);

    //====================//
    //     Main Loop      //
    //====================//

    //Load and set shader
    Shader shader("./testShaders/vertexShader.glsl", "./testShaders/fragmentShader.glsl");
    shader.use();
    glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shader.ID, "texture2"), 1);

    //Set textures for the shader
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    //Bind VAO
    glBindVertexArray(VAO);

    while(!glfwWindowShouldClose(window)){
        //Process input
        processInput(window);

        //Clear screen
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
                
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        //Swap front and back buffers and process events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //====================//
    //   Close Program    //
    //====================//

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    std::cout << "Window has been resized to " << width << "x" << height << std::endl;
    glViewport(0, 0, width, height);
    return;
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}