//
// Created by nicks on 5/11/2022.
//

#ifndef GRAPHICS_EMPTYNODE_H
#define GRAPHICS_EMPTYNODE_H

#include "SceneNode.h"
#include <SDL2/SDL.h>

/**
 * An empty node that can be used to anchor child nodes around a common transform.
 */
class EmptyNode : public SceneNode {
    void Input(SDL_Event& e) override {}
    void Update(float deltaTime) override {}
    void Render() override {}
};


#endif //GRAPHICS_EMPTYNODE_H
