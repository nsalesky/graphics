//
// Created by nicks on 5/10/2022.
//

#include "SceneNode.h"

void SceneNode::AddChild(std::unique_ptr<SceneNode> child) {
    m_children.push_back(std::move(child));
}

void SceneNode::InputTree(SDL_Event &e) {
    Input(e);

    for (std::unique_ptr<SceneNode>& child : m_children) {
        child->InputTree(e);
    }
}

void SceneNode::UpdateTree(float deltaTime, Transform parentWorldTransform) {
    Update(deltaTime);

    // Update our world transform
    m_worldTransform = parentWorldTransform * m_localTransform;

    for (std::unique_ptr<SceneNode>& child : m_children) {
        child->UpdateTree(deltaTime, m_worldTransform);
    }
}

void SceneNode::RenderTree() {
    // Bind the shader automatically if it exists
    if (m_shader) {
       m_shader->Bind();
    }

    Render();

    // Unbind the shader
    if (m_shader) {
        m_shader->Unbind();
    }

    for (std::unique_ptr<SceneNode>& child : m_children) {
        child->RenderTree();
    }
}
