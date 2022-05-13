//
// Created by nicks on 5/12/2022.
//

#ifndef GRAPHICS_FREEFLYCAMERA_H
#define GRAPHICS_FREEFLYCAMERA_H

#include "SceneNode.h"
#include <glm/glm.hpp>

#define CAMERA_SPEED 0.002f

/**
 * A node (more like a "component" cause it doesn't matter where it is in the scene hierarchy) that implements
 * a free-flying camera input system for the main camera. Ideally, you should only have one of these in the scene
 * tree at a time, otherwise input events might be duplicated.
 */
class FreeFlyCamera : public SceneNode {
public:
    void Input(SDL_Event& event) override;
    void Update(float deltaTime) override;
    void Render() override {}
private:
    glm::vec2 m_keyboardAxis; // Represents which directions in X and Y space on the keyboard are currently being pressed
};


#endif //GRAPHICS_FREEFLYCAMERA_H
