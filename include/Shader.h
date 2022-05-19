//
// Created by nicks on 5/12/2022.
//

#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H

#include "glad/glad.h"
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    /**
     * Constructs a new shader with the given source code.
     * @param vertShaderSource the vertex shader source code
     * @param fragShaderSource the fragment shader source code
     */
    Shader(const std::string& vertShaderSource, const std::string& fragShaderSource);
    ~Shader();

    /**
     * Binds this shader in the OpenGL rendering pipeline.
     */
    void Bind();

    /**
     * Unbinds this shader in the OpenGL rendering pipeline.
     */
    void Unbind();

    // === UNIFORMS ===

    /**
     * Sets the value for a boolean uniform variable in this shader.
     * @param name the uniform's name
     * @param value the new value to set
     */
    void SetBool(const std::string& name, bool value) const;

    /**
     * Sets the value for an integer uniform variable in this shader.
     * @param name the uniform's name
     * @param value the new value to set
     */
    void SetInt(const std::string& name, int value) const;

    /**
     * Sets the value for a floating-point uniform variable in this shader.
     * @param name the uniform's name
     * @param value the new value to set
     */
    void SetFloat(const std::string& name, float value) const;

    /**
     * Sets the value for a 4x4 matrix uniform variable in this shader.
     * @param name the uniform's name
     * @param value the new value to set
     */
    void SetMatrix4(const std::string& name, glm::mat4 value) const;

    /**
     * Sets the value for a 3D vector uniform variable in this shader.
     * @param name the uniform's name
     * @param value the new value to set
     */
    void SetVector3(const std::string& name, glm::vec3 value) const;
private:
    unsigned int m_programID; // the OpenGL program ID

    /**
     * Loads and compiles a new shader of the given type with the given source code.
     * @param shaderType the type of shader to load in OpenGL, ie GL_VERTEX_SHADER
     * @param shaderSource the shader's source code
     * @return either the positive shader id, or 0 if an error occurred
     */
    unsigned int CreateShader(unsigned int shaderType, const std::string& shaderSource);
};


#endif //GRAPHICS_SHADER_H
