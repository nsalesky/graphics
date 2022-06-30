//
// Created by nicks on 6/30/2022.
//

#ifndef GRAPHICS_DEPTHTESTSCENE_H
#define GRAPHICS_DEPTHTESTSCENE_H

#include "SceneNode.h"
#include <memory>
#include "Model.h"

class DepthTestScene : public SceneNode {
public:
    DepthTestScene();


protected:
    void Input(SDL_Event& e) override {}
    void Update(float deltaTime) override;
    void Render() override;

private:
    std::unique_ptr<Model> m_cube1;
    std::unique_ptr<Model> m_cube2;

    std::unique_ptr<Model> m_cube1Upscaled;
    std::unique_ptr<Model> m_cube2Upscaled;

    std::unique_ptr<Model> m_plane;
};


#endif //GRAPHICS_DEPTHTESTSCENE_H
