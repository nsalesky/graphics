//
// Created by nicks on 6/1/2022.
//

#ifndef GRAPHICS_LIGHTINGSTRESSSCENE_H
#define GRAPHICS_LIGHTINGSTRESSSCENE_H

#include "SceneNode.h"
#include "Mesh.h"
#include <memory>

class LightingStressScene : public SceneNode {
public:
    LightingStressScene();

protected:
    void Input(SDL_Event& event) override {}
    void Update(float deltaTime) override {}
    void Render() override;

private:
    std::unique_ptr<Mesh> m_planeMesh;
};


#endif //GRAPHICS_LIGHTINGSTRESSSCENE_H
