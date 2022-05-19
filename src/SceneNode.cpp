//
// Created by nicks on 5/10/2022.
//

#include "SceneNode.h"
#include "CameraManager.h"

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

void SceneNode::RenderTree(Lighting& lighting) {
    // Bind the shader automatically if it exists
    if (m_shader) {
       m_shader->Bind();
       lighting.BindUniforms(*m_shader);
       m_shader->SetVector3("viewPos",
                            CameraManager::GetInstance().GetMainCamera()->GetPosition());
    }

    Render();

    // Unbind the shader
    if (m_shader) {
        m_shader->Unbind();
    }

    for (std::unique_ptr<SceneNode>& child : m_children) {
        child->RenderTree(lighting);
    }
}

void SceneNode::AddChild(std::unique_ptr<SceneNode> child) {
    m_children.push_back(std::move(child));
}

std::vector<std::reference_wrapper<SceneNode>> SceneNode::FindAllTaggedNodes(NodeTag queryTag) {
   std::vector<std::reference_wrapper<SceneNode>> nodes;

   if (m_tag == queryTag) {
       nodes.emplace_back(*this);
   }

   for (auto& child : m_children) {
       std::vector<std::reference_wrapper<SceneNode>> childTaggedNodes = child->FindAllTaggedNodes(queryTag);
       for (auto& childTaggedNode : childTaggedNodes) {
           nodes.emplace_back(childTaggedNode);
       }
   }

   return nodes;
}

NodeTag SceneNode::GetTag() {
    return m_tag;
}
