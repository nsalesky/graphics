//
// Created by nicks on 5/12/2022.
//

#include "Shader.h"
#include <iostream>

Shader::Shader(const std::string &vertShaderSource, const std::string &fragShaderSource) {
    // Load the shaders
   unsigned int vertShader = CreateShader(GL_VERTEX_SHADER, vertShaderSource);
   unsigned int fragShader = CreateShader(GL_FRAGMENT_SHADER, fragShaderSource);

   // Check for errors
   if (vertShader == 0 || fragShader == 0) {
       // TODO: might need to do something more sophisticated here, maybe quit the program?
       std::cerr << "Could not create shader!" << std::endl;
       return;
   }

   // Create the program and link together the individual shaders
   m_programID = glCreateProgram();
   glAttachShader(m_programID, vertShader);
   glAttachShader(m_programID, fragShader);
   glLinkProgram(m_programID);

   // Check for linking errors
   int success;
   glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
   if (!success) {
       char infoLog[512];
       glGetProgramInfoLog(m_programID, 512, nullptr, infoLog);
       std::cerr << "Error linking program: " << infoLog << std::endl;
   }

   // delete the individual shaders once they're linked into the program, as they are no longer needed
   glDeleteShader(vertShader);
   glDeleteShader(fragShader);
}

Shader::~Shader() {
    glDeleteProgram(m_programID);
}

void Shader::Bind() {
    glUseProgram(m_programID);
}

void Shader::Unbind() {
    glUseProgram(0);
}

void Shader::SetBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::SetMatrix4(const std::string &name, glm::mat4 value) const {
    glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetVector3(const std::string &name, glm::vec3 value) const {
    glUniform3f(glGetUniformLocation(m_programID, name.c_str()), value.x, value.y, value.z);
}

unsigned int Shader::CreateShader(unsigned int shaderType, const std::string &shaderSource) {
    // Allocate the shader on the GPU
    unsigned int shader = glCreateShader(shaderType);

    const char* shaderSource_c = shaderSource.c_str();

    // Load in the source code to the GPU for that shader
    glShaderSource(shader, 1, &shaderSource_c, nullptr);

    // Compile the source code
    glCompileShader(shader);

    // Check for compilation errors
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Error compiling shader: " << infoLog << std::endl;

        return 0;
    }

    return shader;
}