//
// Created by nicks on 5/10/2022.
//

#ifndef GRAPHICS_SCENENODE_H
#define GRAPHICS_SCENENODE_H

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "Transform.h"
#include "Shader.h"

/**
 * An individual node in the scene which can contain multiple child nodes, all transformed relative to this parent.
 */
class SceneNode {
public:
    /**
     * Handles the given input event for the entire scene tree.
     * @param e the input event
     */
    void InputTree(SDL_Event& e);

    /**
     * Updates the entire scene tree, making sure that objects' transforms are relative to their parents' transforms.
     * @param deltaTime the amount of time since the last update in milliseconds
     * @param parentWorldTransform the parent's world transform
     */
    void UpdateTree(float deltaTime, Transform parentWorldTransform);

    /**
     * Renders the entire scene tree.
     */
    void RenderTree();

    /**
     * Adds the given node as a child to this node and updates its transform relative to this parent node.
     * @param child the child to add
     */
    void AddChild(std::shared_ptr<SceneNode> child);

//    /**
//     * Finds all nodes in this node's hierarchy with the given tag.
//     * @param queryTag the tag to query for
//     * @return all nodes in this hierarchy with that tag
//     */
//    std::vector<std::reference_wrapper<SceneNode>> FindAllTaggedNodes(NodeTag queryTag);

    /**
     * Gets a reference to this node's local transform.
     * @return this node's local transform
     */
    Transform& GetTransform();

//    /**
//     * Overwrites this node's current shader with the given shader for future rendering calls. Note: this method
//     * probably isn't the best idea, and it really only makes sense for nodes utilizing the single shared `m_shader`
//     * field as their only shader. I'm just using it to simplify writing small experiments.
//     * @param shader the new shader to use
//     */
//    void SetShader(std::shared_ptr<Shader> shader);

protected:
    Transform m_localTransform; // this node's local transform. This is the transform that should be modified manually
    Transform m_worldTransform; // this node's world transform. This transform is overwritten every update method relative to its parent

    // if false, RenderTree() will automatically recursively render all of the children.
    // if true, RenderTree() will not render the children, and leaves that up to the implementation of Render() to decicde
    // this is useful when you want to use a framebuffer/stencil buffer or something, and need to render the children
    // in a particular order with steps in between
    bool m_manuallyRenderChildren = false;

    std::shared_ptr<Shader> m_shader;

    /**
     * Handles the given input event.
     * @param e the input event
     */
    virtual void Input(SDL_Event& e) = 0;

    /**
     * Updates this object.
     * @param deltaTime the amount of time since the last update in milliseconds
     */
    virtual void Update(float deltaTime) = 0;

    /**
     * Renders this object.
     */
    virtual void Render() = 0;

private:
   std::vector<std::shared_ptr<SceneNode>> m_children;

};


#endif //GRAPHICS_SCENENODE_H
