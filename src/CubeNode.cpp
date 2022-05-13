//
// Created by nicks on 5/12/2022.
//

#include "CubeNode.h"
#include "GeometryBuilder.h"
#include "Util.h"
#include "ShaderManager.h"
#include "CameraManager.h"
#include "Camera.h"
#include "FreeFlyCamera.h"

#include <iostream>

CubeNode::CubeNode() {
    m_shader = ShaderManager::GetInstance().GetShader("main");

    // Add a free-fly camera input
    AddChild(std::move(std::make_unique<FreeFlyCamera>()));

    GeometryBuilder gb;

    gb.AddVertex({0.5f, 0.5f, 0.0f });
    gb.AddVertex({0.5f, -0.5f, 0.0f });
    gb.AddVertex({-0.5f, -0.5f, 0.0f });
    gb.AddVertex({-0.5f, 0.5f, 0.0f });

    gb.MakeTriangle(0, 1, 3);
    gb.MakeTriangle(1, 2, 3);

    m_geometry = std::move(gb.BuildGeometry());
}

void CubeNode::Input(SDL_Event &event) {
}

void CubeNode::Update(float deltaTime) {
    m_shader->Bind();

    glm::mat4 modelMatrix = m_localTransform.GetInternalMatrix();
    glm::mat4 viewMatrix = CameraManager::GetInstance().GetMainCamera()->GetViewMatrix();
    glm::mat4 projectionMatrix = Util::CalculateProjectionMatrix();

    m_shader->SetMatrix("modelMatrix", modelMatrix);
    m_shader->SetMatrix("viewMatrix", viewMatrix);
    m_shader->SetMatrix("projectionMatrix", projectionMatrix);

    m_shader->Unbind();
}

void CubeNode::Render() {
    m_geometry->Draw();
}