//
// Created by nicks on 5/16/2022.
//

#include "PointLight.h"
#include "Model.h"
#include "ShaderManager.h"
#include "LightingManager.h"

PointLight::PointLight(glm::vec3 color, float ambientStrength, float specularStrength, bool debugDraw) {
    // I leave the pos parameter uninitialized for m_info, because it updates automatically in Update()
    m_info.type = LightInfo::POINT_LIGHT;
    m_info.color = color / 255.0f; // convert from [0, 255] to [0, 1]
    m_info.ambientStrength = ambientStrength;
    m_info.specularStrength = specularStrength;

    // Register this light with the global lighting manager
    m_lightID = LightingManager::GetInstance().RegisterLight(
            [this]() -> LightInfo {
                return this->m_info;
            });

    // Set up debug mesh if necessary
    if (debugDraw) {
        std::shared_ptr<Texture> diffuse = std::make_shared<Texture>(color);
        std::shared_ptr<Texture> specular = std::make_shared<Texture>(glm::vec3(0.0f, 0.0f, 0.0f), TextureType::SPECULAR);

        std::shared_ptr<Material> mat = std::make_shared<Material>(diffuse, specular);

        std::shared_ptr<Shader> diffuseShader = ShaderManager::GetInstance().GetShader("diffuse");

        AddChild(std::make_shared<Model>("assets/point-light.obj", mat, std::move(diffuseShader)));
    }
}

PointLight::~PointLight() {
    LightingManager::GetInstance().UnregisterLight(m_lightID);
}

void PointLight::Update(float deltaTime) {
    m_info.pos = m_worldTransform.GetInternalMatrix() * glm::vec4(0, 0, 0, 1);
}
