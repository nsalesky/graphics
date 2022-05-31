//
// Created by nicks on 5/31/2022.
//

#ifndef GRAPHICS_MATERIAL_H
#define GRAPHICS_MATERIAL_H

#include "Texture.h"
#include <memory>
#include <string>
#include "Shader.h"

/**
 * A Material that stores all the information necessary to represent the physical properties for how a surface should
 * interact with light.
 */
class Material {
public:
    /**
     * Constructs a new material with the given textures.
     * @param diffuse the material's diffuse texture governing how it interacts with diffuse lighting
     * @param specular the material's specular texture governing how it interacts with specular lighting
     */
    Material(std::shared_ptr<Texture> diffuse, std::shared_ptr<Texture> specular);

    /**
     * Constructs a new material with the given textures.
     * @param diffuse the filename of the material's diffuse texture governing how it interacts with diffuse lighting
     * @param specular the filename of the material's specular texture governing how it interacts with specular lighting
     */
    Material(const std::string& diffuseTexture, const std::string& specularTexture);

    /**
     * Binds this material to the given shader.
     * @param shader the shader to bind
     */
    void Bind(Shader& shader);

    /**
     * Unbinds this material from the given shader.
     * @param shader the shader to bind
     */
    void Unbind(Shader& shader);
private:
   std::shared_ptr<Texture> m_diffuseTexture;
   std::shared_ptr<Texture> m_specularTexture;
};


#endif //GRAPHICS_MATERIAL_H
