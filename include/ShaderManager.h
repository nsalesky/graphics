//
// Created by nicks on 5/12/2022.
//

#ifndef GRAPHICS_SHADERMANAGER_H
#define GRAPHICS_SHADERMANAGER_H

#include <unordered_map>
#include <string>
#include <memory>
#include "Shader.h"

/**
 * A singleton managing shader objects by name to make it easier for objects to share shaders by name.
 */
class ShaderManager {
public:
    /**
     * Returns the single static ShaderManager instance.
     * @return the single global ShaderManager instance
     */
    static ShaderManager& GetInstance() {
        static ShaderManager instance;
        return instance;
    }

    /**
     * Adds the given shader to the manager under the given name.
     * @param name the shader's unique identifier
     * @param shader the actual shader object itself
     * @throws std::invalid_argument if a shader with that name already exists
     */
    void AddShader(const std::string name, std::shared_ptr<Shader> shader);

    /**
     * Finds the shader with the given name.
     * @param name the shader's unique identifier
     * @return the corresponding shader
     * @throws std::invalid_argument if no such shader exists
     */
    std::shared_ptr<Shader> GetShader(const std::string name);

    ShaderManager(const ShaderManager& other) = delete;
    void operator=(ShaderManager& other) = delete;
private:
    ShaderManager() = default;

    // The mapping from a string name to a shader
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaderMap;
};


#endif //GRAPHICS_SHADERMANAGER_H
