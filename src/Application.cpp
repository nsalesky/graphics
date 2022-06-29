//
// Created by nicks on 5/10/2022.
//

#include "Application.h"
#include <iostream>
#include <glad/glad.h>
#include <memory>
#include "ShaderManager.h"
#include "Shader.h"
#include "Util.h"
#include "FreeFlyCamera.h"
#include "LightingManager.h"
#include "LightingStressScene.h"

Application::Application(unsigned int width, unsigned int height)
: m_width(width), m_height(height) {
    Init();

}

Application::~Application() {
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
    SDL_Quit();
}

void Application::Init() {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to initialize SDL! SDL error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Set OpenGL version information
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // Request a double buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create the window
    m_window = SDL_CreateWindow(
            "Graphics Demo",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            m_width,
            m_height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
            );
    if (m_window == NULL) {
        std::cerr << "Failed to create window! SDL error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create an OpenGL graphics context
    m_openglContext = SDL_GL_CreateContext(m_window);
    if (m_openglContext == NULL) {
        std::cerr << "Failed to create OpenGL context! SDL error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Initialize GLAD
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    const std::string vertShaderSrc = Util::LoadFile("shaders/vert.glsl");
    const std::string fragShaderSrc = Util::LoadFile("shaders/frag.glsl");
    std::shared_ptr<Shader> mainShader = std::make_shared<Shader>(vertShaderSrc, fragShaderSrc);

    const std::string diffuseFragShaderSrc = Util::LoadFile("shaders/diffuse.frag");
    std::shared_ptr<Shader> diffuseShader = std::make_shared<Shader>(vertShaderSrc, diffuseFragShaderSrc);

    // Set up the important shaders
    ShaderManager::GetInstance().AddShader("main", std::move(mainShader));
    ShaderManager::GetInstance().AddShader("diffuse", std::move(diffuseShader));

    m_rootNode.AddChild(std::make_shared<LightingStressScene>());

    m_rootNode.AddChild(std::make_shared<FreeFlyCamera>());
}

void Application::Loop() {
    bool running = true;
    SDL_Event event;

    // Set up the mouse in relative mode
    SDL_SetRelativeMouseMode(SDL_TRUE);

    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;

    while (running) {
        // Calculate deltaTime
        last = now;
        now = SDL_GetPerformanceCounter();
        float deltaTime = ((now - last)*1000 / (float)SDL_GetPerformanceFrequency());

        // Calculate and display the framerate
        const float fps = 1000.0f / deltaTime;
        const std::string title = "Graphics Demo [" + std::to_string(fps) + " fps]";
        SDL_SetWindowTitle(m_window, title.c_str());

        //Input
        while(SDL_PollEvent(&event)) {
            // Two different ways to quit the program, either by clicking the quit button or by pressing "Q"
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)) {
                running = false;
            } else {
                // Handle this event anywhere it is needed
                m_rootNode.InputTree(event);
            }
        }

        // Update the scene tree
        m_rootNode.UpdateTree(deltaTime, Transform());

        Render();

//        SDL_Delay(2); // TODO: potentially remove this arbitrary delay, or introduce VSync or something

        // Swap buffers
        SDL_GL_SwapWindow(m_window);
    }
}

void Application::Render() {
    // Rebuild the lighting information
    LightingManager::GetInstance().RebuildLights();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glViewport(0, 0, m_width, m_height);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render the scene tree
    m_rootNode.RenderTree();
}