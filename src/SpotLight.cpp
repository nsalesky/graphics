//
// Created by nicks on 6/28/2022.
//

#include "SpotLight.h"
#include "LightingManager.h"
#include "Texture.h"
#include "Material.h"
#include "ShaderManager.h"
#include "Model.h"
#include "Constants.h"

SpotLight::SpotLight(glm::vec3 dir, float innerCutoffAngle, float outerCutoffAngle, glm::vec3 color, float ambientStrength, float specularStrength, bool debugDraw) {
    // I leave the pos parameter uninitialized for m_info, because it updates automatically in Update()
    m_info.type = LightInfo::SPOT_LIGHT;
    m_info.color = color / 255.0f; // convert from [0, 255] to [0, 1]
    m_info.dir = dir;
    m_info.innerCutoffAngle = cos(glm::radians(innerCutoffAngle)); // convert the angle to radians, and then take the cosine value
    m_info.outerCutoffAngle = cos(glm::radians(outerCutoffAngle));
    m_info.ambientStrength = ambientStrength;
    m_info.specularStrength = specularStrength;

    // Register this light with the global lighting manager
    m_lightId = LightingManager::GetInstance().RegisterLight(
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

SpotLight::~SpotLight() {
    LightingManager::GetInstance().UnregisterLight(m_lightId);
}

void SpotLight::Update(float deltaTime) {
    m_info.pos = m_worldTransform.GetInternalMatrix() * glm::vec4(0, 0, 0, 1);
}