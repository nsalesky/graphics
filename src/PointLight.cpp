//
// Created by nicks on 5/16/2022.
//

#include "PointLight.h"

PointLight::PointLight(glm::vec3 lightPos, glm::vec3 lightColor, float ambientStrength, float specularStrength) {
    // I leave the lightPos parameter uninitialized for m_info, because it updates automatically in Update()
    m_localTransform.Translate(lightPos.x, lightPos.y, lightPos.z);
    m_info.lightColor = lightColor / 255.0f; // convert from [0, 255] to [0, 1]
    m_info.ambientStrength = ambientStrength;
    m_info.specularStrength = specularStrength;

    // Make sure this node gets picked up in lighting passes
    m_tag = NodeTag::POINT_LIGHT;
}

void PointLight::Update(float deltaTime) {
    // TODO: No idea if this will work
    m_info.lightPos = m_worldTransform.GetInternalMatrix() * glm::vec4(0, 0, 0, 1);
}

PointLightInfo PointLight::GetInfo() {
    return m_info;
}