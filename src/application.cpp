//
// Created by nicks on 5/10/2022.
//

#include "../include/application.h"
#include <iostream>
#include <glad/glad.h>

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

}

void Application::Loop() {
    bool running = true;
    SDL_Event event;

    while (running) {
        //Input
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Update

        // Render
        glEnable(GL_TEXTURE_2D);

        glViewport(0, 0, m_width, m_height);

        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_Delay(25);

        // Swap buffers
        SDL_GL_SwapWindow(m_window);
    }
}