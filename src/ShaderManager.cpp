//
// Created by nicks on 5/12/2022.
//

#include "../include/ShaderManager.h"
#include <stdexcept>

void ShaderManager::AddShader(const std::string name, std::shared_ptr<Shader> shader) {
    if (m_shaderMap.find(name) == m_shaderMap.end()) {
        // Name is not already present
        m_shaderMap.insert({name, shader});
    } else {
        throw std::invalid_argument("Shader with the given name already exists!");
    }
}

std::shared_ptr<Shader> ShaderManager::GetShader(const std::string name) {
    try {
        return m_shaderMap.at(name);
    } catch (const std::out_of_range& e) {
        throw std::invalid_argument("No shader exists with the given name!");
    }
}