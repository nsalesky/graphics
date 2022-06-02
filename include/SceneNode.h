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
 * A tag that can be used to mark a node as special in some way for the first-phase scene tree traversal. I plan to
 * use this for dynamic lights, so that lights can be a part of the scene tree, but still be located in a first-phase
 * traversal.
 */
enum NodeTag {
    NO_TAG, // a normal untagged node
    POINT_LIGHT, // a point light
};

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
    void AddChild(std::unique_ptr<SceneNode> child);

//    /**
//     * Finds all nodes in this node's hierarchy with the given tag.
//     * @param queryTag the tag to query for
//     * @return all nodes in this hierarchy with that tag
//     */
//    std::vector<std::reference_wrapper<SceneNode>> FindAllTaggedNodes(NodeTag queryTag);

    /**
     * Gets this node's tag, allowing nodes to be identified in a scene tree traversal.
     * @return this node's tag
     */
    NodeTag GetTag();
protected:
    Transform m_localTransform;
    Transform m_worldTransform;

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

    NodeTag m_tag = NodeTag::NO_TAG; // default to no tag, makes sense
private:
   std::vector<std::unique_ptr<SceneNode>> m_children;

};


#endif //GRAPHICS_SCENENODE_H
