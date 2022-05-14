//
// Created by nicks on 5/12/2022.
//

#include "CubeNode.h"
#include "Util.h"
#include "ShaderManager.h"
#include "CameraManager.h"
#include "Camera.h"

#include <iostream>

CubeNode::CubeNode() {
    m_shader = ShaderManager::GetInstance().GetShader("main");

    std::vector<Vertex> vertices = {
            {glm::vec3(1.5f, 1.5f, 0.0f), glm::vec3(), glm::vec2(1, 0)},
            {glm::vec3(1.5f, -1.5f, 0.0f), glm::vec3(), glm::vec2(1, 1)},
            {glm::vec3(-1.5f, -1.5f, 0.0f), glm::vec3(), glm::vec2(0, 1)},
            {glm::vec3(-1.5f, 1.5f, 0.0f), glm::vec3(), glm::vec2(0, 0)},
    };

    std::vector<unsigned int> indices = {0, 1, 3,
                                         1, 2, 3};

    std::vector<std::shared_ptr<Texture>> textures = {
            std::make_shared<Texture>("assets/cat.png")
    };

    m_mesh = std::make_unique<Mesh>(vertices, indices, textures);

    m_localTransform.Translate(0, 0, 5.0f);
}

void CubeNode::Input(SDL_Event &event) {
}

void CubeNode::Update(float deltaTime) {
}

void CubeNode::Render() {
    glm::mat4 modelMatrix = m_localTransform.GetInternalMatrix();
    glm::mat4 viewMatrix = CameraManager::GetInstance().GetMainCamera()->GetViewMatrix();
    glm::mat4 projectionMatrix = Util::CalculateProjectionMatrix();

    m_shader->SetMatrix("modelMatrix", modelMatrix);
    m_shader->SetMatrix("viewMatrix", viewMatrix);
    m_shader->SetMatrix("projectionMatrix", projectionMatrix);

    m_mesh->Draw(m_shader);
}