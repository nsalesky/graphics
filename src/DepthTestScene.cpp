//
// Created by nicks on 6/30/2022.
//

#include "DepthTestScene.h"
#include "Model.h"
#include <memory>
#include "Texture.h"
#include "ShaderManager.h"
#include "Util.h"

DepthTestScene::DepthTestScene() {
    auto vertSrc = Util::LoadFile("shaders/vert.glsl");
    auto diffuseFragSrc = Util::LoadFile("shaders/diffuse.frag");
    auto singleColorFragSrc = Util::LoadFile("shaders/single-color.frag");

    auto diffuse = std::make_shared<Shader>(vertSrc, diffuseFragSrc);
    auto singleColor = std::make_shared<Shader>(vertSrc, singleColorFragSrc);

    auto cat = std::make_shared<Texture>("assets/cat.png");
    auto brick = std::make_shared<Texture>("assets/brick.jpg");
    auto black = std::make_shared<Texture>(glm::vec3(0.0f, 0.0f, 0.0f));

    auto cubeMat = std::make_shared<Material>(cat, black);
    auto planeMat = std::make_shared<Material>(brick, black);

    m_cube1 = std::make_unique<Model>("assets/cube.obj", cubeMat, diffuse);
    m_cube1->GetTransform().Translate(1.0f, 1.0f, 4.0f);

    m_cube2 = std::make_unique<Model>("assets/cube.obj", cubeMat, diffuse);
    m_cube2->GetTransform().Translate(3.0f, 1.0f, 1.0f);

    m_cube1Upscaled = std::make_unique<Model>("assets/cube.obj", cubeMat, singleColor);
    m_cube1Upscaled->GetTransform().Translate(1.0f, 1.0f, 4.0f);
    m_cube1Upscaled->GetTransform().Scale(1.05f, 1.05f, 1.05f);

    m_cube2Upscaled = std::make_unique<Model>("assets/cube.obj", cubeMat, singleColor);
    m_cube2Upscaled->GetTransform().Translate(3.0f, 1.0f, 1.0f);
    m_cube2Upscaled->GetTransform().Scale(1.05f, 1.05f, 1.05f);

    m_plane = std::make_unique<Model>("assets/plane.obj", planeMat, diffuse);
    m_plane->GetTransform().Scale(15.0f, 1.0f, 15.0f);
}

void DepthTestScene::Update(float deltaTime) {
    m_plane->UpdateTree(deltaTime, Transform());
    m_cube1->UpdateTree(deltaTime, Transform());
    m_cube2->UpdateTree(deltaTime, Transform());
    m_cube1Upscaled->UpdateTree(deltaTime, Transform());
    m_cube2Upscaled->UpdateTree(deltaTime, Transform());
}

void DepthTestScene::Render() {
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // replace the stencil buffer value with reference value when both tests succeed

    glStencilMask(0x00); // don't update stencil buffer when drawing the floor
    m_plane->RenderTree();

    glStencilFunc(GL_ALWAYS, 1, 0xFF);         // all fragments should pass the stencil test
    glStencilMask(0xFF);                      // enable writing to the stencil buffer
    m_cube1->RenderTree();
    m_cube2->RenderTree();

    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00); // disable writing to the stencil buffer
    glDisable(GL_DEPTH_TEST);
    m_cube1Upscaled->RenderTree();
    m_cube2Upscaled->RenderTree();
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glEnable(GL_DEPTH_TEST);
}