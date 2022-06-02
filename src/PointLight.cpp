//
// Created by nicks on 5/16/2022.
//

#include "PointLight.h"
#include "Model.h"
#include "ShaderManager.h"
#include "LightingManager.h"

PointLight::PointLight(glm::vec3 lightPos, glm::vec3 lightColor, float ambientStrength, float specularStrength, bool debugDraw) {
    // I leave the lightPos parameter uninitialized for m_info, because it updates automatically in Update()
    m_localTransform.Translate(lightPos.x, lightPos.y, lightPos.z);
    m_info.lightColor = lightColor / 255.0f; // convert from [0, 255] to [0, 1]
    m_info.ambientStrength = ambientStrength;
    m_info.specularStrength = specularStrength;

    // Make sure this node gets picked up in lighting passes
    m_tag = NodeTag::POINT_LIGHT;

    // Register this light with the global lighting manager TODO I have no idea if this actually works, it seems very janky to me lol
    m_pointLightID = LightingManager::GetInstance().RegisterDynamicPointLight(
            [this]() -> PointLightInfo {return this->GetInfo();}
            );

    // Set up debug mesh if necessary
    if (debugDraw) {
        std::shared_ptr<Texture> diffuse = std::make_shared<Texture>(lightColor);
        std::shared_ptr<Texture> specular = std::make_shared<Texture>(glm::vec3(0.0f, 0.0f, 0.0f), TextureType::SPECULAR);

        std::shared_ptr<Material> mat = std::make_shared<Material>(diffuse, specular);

        std::shared_ptr<Shader> diffuseShader = ShaderManager::GetInstance().GetShader("diffuse");

        AddChild(std::make_unique<Model>("assets/point-light.obj", mat, std::move(diffuseShader)));
    }
}

PointLight::~PointLight() {
    LightingManager::GetInstance().UnregisterPointLight(m_pointLightID);
}

void PointLight::Update(float deltaTime) {
    // TODO: No idea if this will work
    m_info.lightPos = m_worldTransform.GetInternalMatrix() * glm::vec4(0, 0, 0, 1);
}

PointLightInfo PointLight::GetInfo() {
    return m_info;
}