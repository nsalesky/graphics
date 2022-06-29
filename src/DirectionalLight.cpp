//
// Created by nicks on 6/3/2022.
//

#include "DirectionalLight.h"
#include "LightingManager.h"

DirectionalLight::DirectionalLight(glm::vec3 dir, glm::vec3 color, float ambientStrength, float specularStrength) {
    m_info = {dir, color / 255.0f, ambientStrength, specularStrength};

    m_dirLightID = LightingManager::GetInstance().RegisterDirectionalLight(
            [this]() -> DirectionalLightInfo {
                return this->m_info;
            });
}

DirectionalLight::~DirectionalLight() {
    LightingManager::GetInstance().UnregisterDirectionalLight(m_dirLightID);
}
