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
    auto depthVert = Util::LoadFile("shaders/vert.glsl");
    auto depthFrag = Util::LoadFile("shaders/depth.frag");
    auto depthShader = std::make_shared<Shader>(depthVert, depthFrag);

    auto cat = std::make_shared<Texture>("assets/cat.png");
    auto brick = std::make_shared<Texture>("assets/brick.jpg");
    auto black = std::make_shared<Texture>(glm::vec3(0.0f, 0.0f, 0.0f));

    auto cubeMat = std::make_shared<Material>(cat, black);
    auto planeMat = std::make_shared<Material>(brick, black);

    auto cube1 = std::make_shared<Model>("assets/cube.obj", cubeMat, depthShader);
    cube1->GetTransform().Translate(1.0f, 0.5f, 4.0f);

    auto cube2 = std::make_shared<Model>("assets/cube.obj", cubeMat, depthShader);
    cube2->GetTransform().Translate(3.0f, 0.5f, 1.0f);

    auto plane = std::make_shared<Model>("assets/plane.obj", planeMat, depthShader);
    plane->GetTransform().Scale(15.0f, 1.0f, 15.0f);

    AddChild(cube1);
    AddChild(cube2);
    AddChild(plane);
}