//
// Created by nicks on 6/1/2022.
//

#include "LightingStressScene.h"
#include "Texture.h"
#include "Material.h"
#include "ShaderManager.h"
#include "PointLight.h"
#include "FreeFlyCamera.h"
#include "CameraManager.h"
#include "Util.h"

#include <iostream>

LightingStressScene::LightingStressScene() {
    m_shader = ShaderManager::GetInstance().GetShader("main");

    // Create a plane
    std::vector<Vertex> planeVert = {
            {glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(), glm::vec2(1, 0)},
            {glm::vec3(10.0f, 0.0f, -10.0f), glm::vec3(), glm::vec2(1, 1)},
            {glm::vec3(-10.0f, 0.0f, -10.0f), glm::vec3(), glm::vec2(0, 1)},
            {glm::vec3(-10.0f, 0.0f, 10.0f), glm::vec3(), glm::vec2(0, 0)},
    };

    std::vector<unsigned int> planeIndices = {0, 1, 3,
                                         1, 2, 3};

    std::shared_ptr<Texture> white = std::make_shared<Texture>(glm::vec3(255.0f, 255.0f, 255.0f));
    std::shared_ptr<Texture> black = std::make_shared<Texture>(glm::vec3(0.0f, 0.0f, 0.0f));

    std::shared_ptr<Material> planeMat = std::make_shared<Material>(white, black);

    m_planeMesh = std::make_unique<Mesh>(planeVert, planeIndices, planeMat);

    // Create two lights
    AddChild(std::make_unique<PointLight>(
            glm::vec3(2.0f, 1.0f, -2.0f),
            glm::vec3(255.0f, 0.0f, 255.0f),
            0.5,
            0.5
            ));

    AddChild(std::make_unique<PointLight>(
            glm::vec3(5.0f, 1.0f, 2.0f),
            glm::vec3(0.0f, 255.0f, 255.0f),
            0.5,
            0.5
    ));
}

void LightingStressScene::Render() {
    m_planeMesh->Draw(*m_shader);
}