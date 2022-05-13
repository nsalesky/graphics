//
// Created by nicks on 5/12/2022.
//

#ifndef GRAPHICS_CUBENODE_H
#define GRAPHICS_CUBENODE_H

#include "SceneNode.h"
#include "Geometry.h"
#include "Shader.h"
#include <memory>

/**
 * This is an object for testing
 */
class CubeNode : public SceneNode {
public:
    CubeNode();

    void Input(SDL_Event& event) override;
    void Update(float deltaTime) override;
    void Render() override;
private:
    std::unique_ptr<Geometry> m_geometry;
};


#endif //GRAPHICS_CUBENODE_H
