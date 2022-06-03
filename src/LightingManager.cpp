//
// Created by nicks on 5/16/2022.
//

#include "LightingManager.h"
#include "Constants.h"
#include <stdexcept>

void LightingManager::BindUniforms(Shader &shader) {
    // Bind point lights
    shader.SetInt("lighting.numPointLights", m_pointLights.size());
    for (unsigned int i = 0; i < m_pointLights.size(); i += 1) {
        PointLightInfo& info = m_pointLights[i];

        std::string baseName = "lighting.pointLights[" + std::to_string(i) + "].";

        shader.SetVector3(baseName + "lightPos", info.lightPos);
        shader.SetVector3(baseName + "lightColor", info.lightColor);
        shader.SetFloat(baseName + "ambientStrength", info.ambientStrength);
        shader.SetFloat(baseName + "specularStrength", info.specularStrength);
        shader.SetFloat(baseName + "constantFactor", info.constantFactor);
        shader.SetFloat(baseName + "linearFactor", info.linearFactor);
        shader.SetFloat(baseName + "quadraticFactor", info.quadraticFactor);
    }

    // Bind directional lights
    shader.SetInt("lighting.numDirLights", m_dirLights.size());
    for (unsigned int i = 0; i < m_dirLights.size(); i += 1) {
        DirectionalLightInfo& info = m_dirLights[i];

        std::string baseName = "lighting.dirLights[" + std::to_string(i) + "].";

        shader.SetVector3(baseName + "lightDir", info.lightDir);
        shader.SetVector3(baseName + "lightColor", info.lightColor);
        shader.SetFloat(baseName + "ambientStrength", info.ambientStrength);
        shader.SetFloat(baseName + "specularStrength", info.specularStrength);
    }
}

void LightingManager::RebuildLights() {
    m_pointLights.clear();
    m_pointLights.reserve(m_dynamicPointLights.size());

    m_dirLights.clear();
    m_dirLights.reserve(m_dynamicDirLights.size());

    for (auto& pointLight : m_dynamicPointLights) {
        m_pointLights.push_back(pointLight.second());
    }

    for (auto& dirLight : m_dynamicDirLights) {
        m_dirLights.push_back(dirLight.second());
    }

}

unsigned int LightingManager::RegisterPointLight(const std::function<PointLightInfo()>& infoFunc) {
    // Find the lowest possible ID and insert the function at that key
    for (unsigned int i = 0; i < MAX_POINT_LIGHTS; i += 1) {
        if (!m_dynamicPointLights.contains(i)) {
            // Use this index
            m_dynamicPointLights.insert(std::make_pair(i, infoFunc));
            return i;
        }
    }

    throw std::range_error("Already at maximum number of point lights!");
}

unsigned int LightingManager::RegisterDirectionalLight(const std::function<DirectionalLightInfo()> &infoFunc) {
    // Find the lowest possible ID and insert the function at that key
    for (unsigned int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i += 1) {
        if (!m_dynamicDirLights.contains(i)) {
            // Use this index
            m_dynamicDirLights.insert(std::make_pair(i, infoFunc));
            return i;
        }
    }

    throw std::range_error("Already at maximum number of directional lights!");
}

void LightingManager::UnregisterPointLight(unsigned int id) {
    if (m_dynamicPointLights.contains(id)) {
        m_dynamicPointLights.erase(id);
    } else {
        throw std::invalid_argument("No point light exists with the given ID");
    }
}
void LightingManager::UnregisterDirectionalLight(unsigned int id) {
    if (m_dynamicDirLights.contains(id)) {
        m_dynamicDirLights.erase(id);
    } else {
        throw std::invalid_argument("No directional light exists with the given ID");
    }
}
