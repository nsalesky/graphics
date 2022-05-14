//
// Created by nicks on 5/13/2022.
//

#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H

#include "string"
#include "Shader.h"
#include <memory>

/**
 * Determines how a texture should be interpreted, based on which type of texture its being used as.
 */
enum TextureType {
    DIFFUSE,
    SPECULAR,
    NORMAL,
    HEIGHT,
};

/**
 * A texture that can be bound on the GPU and, well, used to texture a given piece of geometry with an arbitrary
 * uniform name.
 */
class Texture {
public:
    /**
     * Constructs a new texture for the given image utilizing the given name as an OpenGL uniform.
     * @param filename the filename of the image to load
     * @param type which type of texture is this
     */
    Texture(const std::string filename, const TextureType type = TextureType::DIFFUSE);
    ~Texture();

    /**
     * Binds this texture to the given texture slot.
     * @param shader the shader to bind to, assumed to be bound already
     * @param uniformName the name of the uniform to bind to
     * @param textureSlot the texture slot to use
     */
    void Bind(std::shared_ptr<Shader>& shader, const std::string& uniformName, unsigned int textureSlot = 0);

    /**
     * Unbinds this texture from the given texture slot.
     * @param shader the shader to unbind from, assumed to be bound already
     * @param textureSlot the texture slot to unbind from
     */
    void Unbind(std::shared_ptr<Shader>& shader, unsigned int textureSlot = 0);

    /**
     * Gets the filename that this texture was loaded from. This is useful when determining if a given image filename
     * has already been loaded, and can be reused instead.
     * @return this texture's original filename
     */
    std::string GetFilename();

    /**
     * Gets this texture's type. This is useful when an object has a bunch of textures in one collection and wants to
     * treat each of them differently based on their type.
     * @return this texture's type
     */
    TextureType GetType();
private:
    unsigned int m_textureID;
    std::string m_filename;
    TextureType m_type;

    /**
     * Loads in the image data from the given file and sets up an OpenGL texture for it.
     */
    void LoadTexture();
};


#endif //GRAPHICS_TEXTURE_H
