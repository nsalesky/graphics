//
// Created by nicks on 5/13/2022.
//

#include "Texture.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string filename, const TextureType type)
: m_filename(filename), m_type(type) {

    LoadTexture();
}

Texture::~Texture() {
    glDeleteTextures(1, &m_textureID);
}

void Texture::LoadTexture() {
    glGenTextures(1, &m_textureID);

    // Load the image data
    int width, height, numComponents;
    unsigned char* data = stbi_load(m_filename.c_str(), &width, &height, &numComponents, 0);

    // Check if it was successful
    if (data) {
        // Figure out the right format for whatever image we just loaded
        GLenum format;
        if (numComponents == 1) {
            // Single channel image
            format = GL_RED;
        } else if (numComponents == 3) {
            // RGB image
            format = GL_RGB;
        } else if (numComponents == 4) {
            format = GL_RGBA;
        }

        // Bind the texture and load in the image data
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Set the basic texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        // Error, image failed to load for some reason
        std::cerr << "Texture failed to load from: " << m_filename << std::endl;
        stbi_image_free(data);
    }
}

void Texture::Bind(Shader& shader, const std::string& uniformName, unsigned int textureSlot) {
    // Make sure we bind to the right slot
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    shader.SetInt(uniformName, textureSlot);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glActiveTexture(GL_TEXTURE0);
}

void Texture::Unbind(Shader& shader, unsigned int textureSlot) {
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
}

std::string Texture::GetFilename() {
    return m_filename;
}

TextureType Texture::GetType() {
    return m_type;
}