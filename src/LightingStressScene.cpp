//
// Created by nicks on 6/1/2022.
//

#include "LightingStressScene.h"
#include "Texture.h"
#include "Material.h"
#include "ShaderManager.h"
#include "CameraManager.h"
#include "DirectionalLight.h"

LightingStressScene::LightingStressScene() {
    m_shader = ShaderManager::GetInstance().GetShader("main");
    m_manuallyRenderChildren = true;

    // Create a plane
    std::vector<Vertex> planeVert = {
            {glm::vec3(10.0f, 0.0f, 10.0f),   glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1, 0)},
            {glm::vec3(10.0f, 0.0f, -10.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1, 1)},
            {glm::vec3(-10.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0, 1)},
            {glm::vec3(-10.0f, 0.0f, 10.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0, 0)},
    };

    std::vector<unsigned int> planeIndices = {0, 1, 3,
                                              1, 2, 3};

    std::shared_ptr<Texture> white = std::make_shared<Texture>(glm::vec3(255.0f, 255.0f, 255.0f));
    std::shared_ptr<Texture> black = std::make_shared<Texture>(glm::vec3(0.0f, 0.0f, 0.0f));

    std::shared_ptr<Material> planeMat = std::make_shared<Material>(white, black);

    m_planeMesh = std::make_unique<Mesh>(planeVert, planeIndices, planeMat);

    // Create the framebuffer
    m_framebuffer = std::make_unique<Framebuffer>();
    std::shared_ptr<Material> quadMat = std::make_shared<Material>(m_framebuffer->GetColorTexture(), black);

    // Create the screen quad
//    std::vector<Vertex> screenVert = {
//            {glm::vec3(-1.0, -1.0f, 0.0f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0, 0)},
//            {glm::vec3(-1.0f, 1.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0, 1)},
//            {glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1, 0)},
//            {glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1, 1)},
//    };
    std::vector<Vertex> screenVert = {
            {glm::vec3(-0.9f, 0.4f, 0.0f),   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0, 0)},
            {glm::vec3(-0.9f, 0.9f, 0.0f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0, 1)},
            {glm::vec3(-0.4f, 0.4f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1, 0)},
            {glm::vec3(-0.4f, 0.9f, 0.0f),  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1, 1)},
    };


    std::vector<unsigned int> screenIndices = {3, 1, 0,
                                               3, 0, 2};

    m_screenQuad = std::make_unique<Mesh>(screenVert, screenIndices, quadMat);
    m_screenShader = std::make_unique<Shader>("shaders/postprocess.vert", "shaders/postprocess.frag", true);

    // ================= Set up the lights ============================

    m_lightpivot = std::make_shared<EmptyNode>();
    m_lightpivot->GetTransform().Translate(2.0f, 1.0f, 3.0f);
    AddChild(m_lightpivot);

    // Create two lights
    m_pointlight1 = std::make_shared<PointLight>(
            glm::vec3(255.0f, 0.0f, 0.0f),
            0.5,
            0.5,
            true
    );
    m_pointlight1->GetTransform().Translate(3.0f, 0.0f, 0.0f);
    m_lightpivot->AddChild(m_pointlight1);

    m_pointlight2 = std::make_shared<PointLight>(
            glm::vec3(0.0f, 255.0f, 255.0f),
            0.5,
            0.5,
            true
    );
    m_pointlight2->GetTransform().Translate(5.0f, 1.0f, 2.0f);
    AddChild(m_pointlight2);

//    AddChild(std::make_shared<DirectionalLight>(
//            glm::vec3(0.0f, -0.5f, 0.0f),
//            glm::vec3(0.0f, 255.0f, 0.0f),
//            0.05,
//            0.05));

    m_spotLight = std::make_shared<SpotLight>(
                    glm::vec3(2.4f, -1.0f, 0.0f),
                    20.0f,
                    24.0f,
                    glm::vec3(255.0f, 0.0f, 0.0f),
                    0.1,
                    0.5,
                    true);

    m_spotLight->GetTransform().Translate(4.0f, 1.0f, 2.0f);
    m_spotLight->GetTransform().Scale(0.3f, 0.3f, 0.3f);
    AddChild(m_spotLight);

    m_spotLight2 = std::make_shared<SpotLight>(
            glm::vec3(-2.4f, -1.0f, 0.0f),
            20.0f,
            24.0f,
            glm::vec3(0.0f, 0.0f, 255.0f),
            0.1,
            0.5,
            true);

    m_spotLight2->GetTransform().Translate(8.0f, 1.0f, 2.0f);
    m_spotLight2->GetTransform().Scale(0.3f, 0.3f, 0.3f);
    AddChild(m_spotLight2);

    m_counter = 0.0f;
}

void LightingStressScene::Update(float deltaTime) {
    m_lightpivot->GetTransform().Rotate(deltaTime * 0.001f, 0.0f, 1.0f, 0.0f);

    m_counter += deltaTime * 0.001;

    m_pointlight2->GetTransform().SetPosition(5.0f, 1.5f + sin(m_counter), 2.0f);
}

void LightingStressScene::Render() {
    auto& mainCam = CameraManager::GetInstance().GetMainCamera();

    // Rotate 180 degrees and update the shader
    glm::vec3 originalViewDir = mainCam->GetViewDir();
    mainCam->SetViewDir(-originalViewDir);
    glm::mat4 viewMatrix = CameraManager::GetInstance().GetMainCamera()->GetViewMatrix();
    m_shader->SetMatrix4("viewMatrix", viewMatrix);

    // Render the scene into the framebuffer
    m_framebuffer->Bind();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_planeMesh->Draw(*m_shader);
    m_pointlight1->RenderTree();
    m_pointlight2->RenderTree();
    m_lightpivot->RenderTree();
    m_spotLight->RenderTree();
    m_spotLight2->RenderTree();

    m_framebuffer->Unbind();

    // Restore the camera
    m_shader->Bind();
    mainCam->SetViewDir(originalViewDir);
    viewMatrix = CameraManager::GetInstance().GetMainCamera()->GetViewMatrix();
    m_shader->SetMatrix4("viewMatrix", viewMatrix);

    // Draw the scene normally to the screen
    m_planeMesh->Draw(*m_shader);
    m_pointlight1->RenderTree();
    m_pointlight2->RenderTree();
    m_lightpivot->RenderTree();
    m_spotLight->RenderTree();
    m_spotLight2->RenderTree();

    // Draw the rear-view overlay

//    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
//
//    // Render the quad with the framebuffer information
    m_screenShader->Bind();
    m_screenQuad->Draw(*m_screenShader);
    m_shader->Bind(); // rebind the normal shader
    glEnable(GL_DEPTH_TEST);
}