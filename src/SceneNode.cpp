//
// Created by nicks on 5/10/2022.
//

#include "SceneNode.h"
#include "CameraManager.h"
#include "Util.h"
#include "LightingManager.h"

void SceneNode::InputTree(SDL_Event &e) {
    Input(e);

    for (auto &child: m_children) {
        child->InputTree(e);
    }
}

void SceneNode::UpdateTree(float deltaTime, Transform parentWorldTransform) {
    Update(deltaTime);

    // Update our world transform
    m_worldTransform = parentWorldTransform * m_localTransform;

    for (auto &child: m_children) {
        child->UpdateTree(deltaTime, m_worldTransform);
    }
}

void SceneNode::RenderTree() {
    // Bind the shader automatically if it exists
    if (m_shader) {
        m_shader->Bind();

        LightingManager::GetInstance().BindUniforms(*m_shader);

        m_shader->SetVector3("viewPos",
                             CameraManager::GetInstance().GetMainCamera()->GetPosition());


        glm::mat4 modelMatrix = m_worldTransform.GetInternalMatrix();
        glm::mat4 viewMatrix = CameraManager::GetInstance().GetMainCamera()->GetViewMatrix();
        glm::mat4 projectionMatrix = Util::CalculateProjectionMatrix();

        m_shader->SetMatrix4("modelMatrix", modelMatrix);
        m_shader->SetMatrix4("viewMatrix", viewMatrix);
        m_shader->SetMatrix4("projectionMatrix", projectionMatrix);
    }

    Render();

    // Unbind the shader
    if (m_shader) {
        m_shader->Unbind();
    }

    for (auto &child: m_children) {
        child->RenderTree();
    }
}

void SceneNode::AddChild(std::shared_ptr<SceneNode> child) {
    m_children.push_back(std::move(child));
}

Transform &SceneNode::GetTransform() {
    return m_localTransform;
}

//void SceneNode::SetShader(std::shared_ptr<Shader> shader) {
//    m_shader = std::move(shader);
//}