#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader{
    public:
        //Shader program ID
        unsigned int ID;

        //Constructor reads and builds the shader
        Shader(const char* vertexFilePath, const char* fragmentFilePath);
        //Set shader as current
        void use(void);
};

#endif
