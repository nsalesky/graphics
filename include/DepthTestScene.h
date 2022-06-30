//
// Created by nicks on 6/30/2022.
//

#ifndef GRAPHICS_DEPTHTESTSCENE_H
#define GRAPHICS_DEPTHTESTSCENE_H

#include "SceneNode.h"

class DepthTestScene : public SceneNode {
public:
    DepthTestScene();


protected:
    void Input(SDL_Event& e) override {}
    void Update(float deltaTime) override {}
    void Render() override {}
};


#endif //GRAPHICS_DEPTHTESTSCENE_H
