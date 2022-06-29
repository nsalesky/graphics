//
// Created by nicks on 6/1/2022.
//

#include "LightingStressScene.h"
#include "Texture.h"
#include "Material.h"
#include "ShaderManager.h"
#include "CameraManager.h"
#include "DirectionalLight.h"

LightingStressScene::LightingStressScene() {
    m_shader = ShaderManager::GetInstance().GetShader("main");

    // Create a plane
    std::vector<Vertex> planeVert = {
            {glm::vec3(10.0f, 0.0f, 10.0f),   glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1, 0)},
            {glm::vec3(10.0f, 0.0f, -10.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1, 1)},
            {glm::vec3(-10.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0, 1)},
            {glm::vec3(-10.0f, 0.0f, 10.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0, 0)},
    };

    std::vector<unsigned int> planeIndices = {0, 1, 3,
                                              1, 2, 3};

    std::shared_ptr<Texture> white = std::make_shared<Texture>(glm::vec3(255.0f, 255.0f, 255.0f));
    std::shared_ptr<Texture> black = std::make_shared<Texture>(glm::vec3(0.0f, 0.0f, 0.0f));

    std::shared_ptr<Material> planeMat = std::make_shared<Material>(white, black);

    m_planeMesh = std::make_unique<Mesh>(planeVert, planeIndices, planeMat);

//    m_lightpivot = std::make_shared<EmptyNode>();
//    m_lightpivot->GetTransform().Translate(2.0f, 1.0f, 3.0f);
//    AddChild(m_lightpivot);
//
//    // Create two lights
//    m_pointlight1 = std::make_shared<PointLight>(
//            glm::vec3(255.0f, 0.0f, 0.0f),
//            0.5,
//            0.5,
//            true
//    );
//    m_pointlight1->GetTransform().Translate(3.0f, 0.0f, 0.0f);
//    m_lightpivot->AddChild(m_pointlight1);
//
//    m_pointlight2 = std::make_shared<PointLight>(
//            glm::vec3(0.0f, 255.0f, 255.0f),
//            0.5,
//            0.5,
//            true
//    );
//    m_pointlight2->GetTransform().Translate(5.0f, 1.0f, 2.0f);
//    AddChild(m_pointlight2);

//    AddChild(std::make_shared<DirectionalLight>(
//            glm::vec3(0.0f, -0.5f, 0.0f),
//            glm::vec3(0.0f, 255.0f, 0.0f),
//            0.5,
//            0.5));

    m_spotLight = std::make_shared<SpotLight>(
                    glm::vec3(2.4f, -1.0f, 0.0f),
                    20.0f,
                    24.0f,
                    glm::vec3(255.0f, 0.0f, 0.0f),
                    0.1,
                    0.5,
                    true);

    m_spotLight->GetTransform().Translate(4.0f, 1.0f, 2.0f);
    m_spotLight->GetTransform().Scale(0.3f, 0.3f, 0.3f);
    AddChild(m_spotLight);

    m_spotLight2 = std::make_shared<SpotLight>(
            glm::vec3(-2.4f, -1.0f, 0.0f),
            20.0f,
            24.0f,
            glm::vec3(0.0f, 0.0f, 255.0f),
            0.1,
            0.5,
            true);

    m_spotLight2->GetTransform().Translate(8.0f, 1.0f, 2.0f);
    m_spotLight2->GetTransform().Scale(0.3f, 0.3f, 0.3f);
    AddChild(m_spotLight2);

    m_counter = 0.0f;
}

void LightingStressScene::Update(float deltaTime) {
//    m_lightpivot->GetTransform().Rotate(deltaTime * 0.001f, 0.0f, 1.0f, 0.0f);
//
//    m_counter += deltaTime * 0.001;
//
//    m_pointlight2->GetTransform().SetPosition(5.0f, 1.5f + sin(m_counter), 2.0f);
}

void LightingStressScene::Render() {
    m_planeMesh->Draw(*m_shader);
}