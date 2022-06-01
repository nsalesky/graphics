//
// Created by nicks on 5/12/2022.
//

#include "CubeNode.h"
#include "Util.h"
#include "ShaderManager.h"
#include "CameraManager.h"
#include "Camera.h"

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

//    std::shared_ptr<Texture> cat = std::make_shared<Texture>("assets/cat.png");
    std::shared_ptr<Texture> cat = std::make_shared<Texture>(glm::vec3(255.0f, 255.0f, 255.0f));
    std::shared_ptr<Material> material = std::make_shared<Material>(cat, cat);

    m_mesh = std::make_unique<Mesh>(vertices, indices, material);

    m_localTransform.Translate(2.0, 2.0, 1.0f);
}

void CubeNode::Input(SDL_Event &event) {
}

void CubeNode::Update(float deltaTime) {
}

void CubeNode::Render() {
    m_mesh->Draw(*m_shader);
}