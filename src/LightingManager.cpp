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
}

void LightingManager::RebuildLights() {
    m_pointLights.clear();

    for (auto pointLight : m_staticPointLights) {
        m_pointLights.push_back(pointLight.second);
    }

    for (const auto& pointLight : m_dynamicPointLights) {
        m_pointLights.push_back(pointLight.second());
    }
}

unsigned int LightingManager::RegisterStaticPointLight(PointLightInfo info) {
    int possibleID = FindLowestAvailablePointLightID();

    if (possibleID == -1) {
        throw std::range_error("Already at maximum number of point lights!");
    }

    m_staticPointLights.insert(std::make_pair(possibleID, info));
}

unsigned int LightingManager::RegisterDynamicPointLight(const std::function<PointLightInfo()>& infoFunc) {
    int possibleID = FindLowestAvailablePointLightID();

    if (possibleID == -1) {
        throw std::range_error("Already at maximum number of point lights!");
    }

    m_dynamicPointLights.insert(std::make_pair(possibleID, infoFunc));
}

void LightingManager::UnregisterPointLight(unsigned int id) {
    if (m_staticPointLights.contains(id)) {
        m_staticPointLights.erase(id);
    } else if (m_dynamicPointLights.contains(id)) {
        m_dynamicPointLights.erase(id);
    } else {
        throw std::invalid_argument("No point light exists with the given ID");
    }
}

int LightingManager::FindLowestAvailablePointLightID() {
    for (int i = 0; i < MAX_POINT_LIGHTS; i += 1) {
        if (!m_staticPointLights.contains(i) && !m_dynamicPointLights.contains(i)) {
            return i;
        }
    }

    return -1;
}