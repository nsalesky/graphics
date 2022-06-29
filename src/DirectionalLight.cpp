//
// Created by nicks on 6/3/2022.
//

#include "DirectionalLight.h"
#include "LightingManager.h"

DirectionalLight::DirectionalLight(glm::vec3 dir, glm::vec3 color, float ambientStrength, float specularStrength) {
    m_info.type = LightInfo::DIRECTIONAL_LIGHT;
    m_info.dir = dir;
    m_info.color = color / 255.0f;
    m_info.ambientStrength = ambientStrength;
    m_info.specularStrength = specularStrength;

    m_lightID = LightingManager::GetInstance().RegisterLight(
            [this]() -> LightInfo {
                return this->m_info;
            });
}

DirectionalLight::~DirectionalLight() {
    LightingManager::GetInstance().UnregisterLight(m_lightID);
}
