//
// Created by nicks on 5/16/2022.
//

#include "Lighting.h"
#include "Constants.h"
#include <stdexcept>

Lighting::Lighting(std::vector<PointLightInfo> pointLights) {
    if (pointLights.size() > MAX_POINT_LIGHTS) {
        throw std::invalid_argument("Too many point lights! " + std::to_string(pointLights.size()) + " > " + std::to_string(MAX_POINT_LIGHTS));
    }

    m_pointLights = pointLights;
}

void Lighting::BindUniforms(Shader &shader) {
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