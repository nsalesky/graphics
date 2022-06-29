//
// Created by nicks on 5/16/2022.
//

#include "LightingManager.h"
#include "Constants.h"
#include <stdexcept>

void LightingManager::BindUniforms(Shader &shader) {
    // Bind point lights
    shader.SetInt("lighting.numLights", m_lights.size());
    for (unsigned int i = 0; i < m_lights.size(); i += 1) {
        LightInfo& info = m_lights[i];

        // Set the uniforms for this light

        std::string baseName = "lighting.lights[" + std::to_string(i) + "].";

        shader.SetInt(baseName + "type", info.type);

        shader.SetVector3(baseName + "pos", info.pos);
        shader.SetVector3(baseName + "color", info.color);

        shader.SetVector3(baseName + "dir", info.dir);

        shader.SetFloat(baseName + "innerCutoffAngle", info.innerCutoffAngle);
        shader.SetFloat(baseName + "outerCutoffAngle", info.outerCutoffAngle);

        shader.SetFloat(baseName + "ambientStrength", info.ambientStrength);
        shader.SetFloat(baseName + "specularStrength", info.specularStrength);

        shader.SetFloat(baseName + "constantFactor", info.constantFactor);
        shader.SetFloat(baseName + "linearFactor", info.linearFactor);
        shader.SetFloat(baseName + "quadraticFactor", info.quadraticFactor);
    }
}

void LightingManager::RebuildLights() {
    // Clear the cached lighting information
    m_lights.clear();
    m_lights.reserve(m_dynamicLights.size());

    for (auto& light : m_dynamicLights) {
        m_lights.push_back(light.second());
    }
}

unsigned int LightingManager::RegisterLight(const std::function<LightInfo()>& infoFunc) {
    // Find the lowest possible ID and insert the function at that key
    for (unsigned int i = 0; i < MAX_LIGHTS; i += 1) {
        if (!m_dynamicLights.contains(i)) {
            // Use this index
            m_dynamicLights.insert(std::make_pair(i, infoFunc));
            return i;
        }
    }

    throw std::range_error("Already at maximum number of lights!");
}

void LightingManager::UnregisterLight(unsigned int id) {
    if (m_dynamicLights.contains(id)) {
        m_dynamicLights.erase(id);
    } else {
        throw std::invalid_argument("No light exists with the given ID");
    }
}
