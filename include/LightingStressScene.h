//
// Created by nicks on 6/1/2022.
//

#ifndef GRAPHICS_LIGHTINGSTRESSSCENE_H
#define GRAPHICS_LIGHTINGSTRESSSCENE_H

#include "SceneNode.h"
#include "Mesh.h"
#include <memory>
#include "PointLight.h"
#include "SpotLight.h"
#include "EmptyNode.h"
#include "Framebuffer.h"

class LightingStressScene : public SceneNode {
public:
    LightingStressScene();

protected:
    void Input(SDL_Event& event) override {}
    void Update(float deltaTime) override;
    void Render() override;

private:
    std::unique_ptr<Mesh> m_planeMesh;

    std::shared_ptr<EmptyNode> m_lightpivot;
    std::shared_ptr<PointLight> m_pointlight1;
    std::shared_ptr<PointLight> m_pointlight2;
    std::shared_ptr<SpotLight> m_spotLight;
    std::shared_ptr<SpotLight> m_spotLight2;

    std::unique_ptr<Mesh> m_screenQuad;
    std::unique_ptr<Shader> m_screenShader;
    std::unique_ptr<Framebuffer> m_framebuffer;

    float m_counter;
};


#endif //GRAPHICS_LIGHTINGSTRESSSCENE_H
