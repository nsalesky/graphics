//
// Created by nicks on 5/10/2022.
//

#ifndef GRAPHICS_APPLICATION_H
#define GRAPHICS_APPLICATION_H

#include <SDL2/SDL.h>

/**
 * An overall application encompassing the entire program's data and execution.
 */
class Application {
public:
    /**
     * Constructs the application.
     * @param width the screen width in pixels
     * @param height the screen height in pixels
     */
    Application(unsigned int width, unsigned int height);
    ~Application();

    /**
     * Executes the main input-update-render loop, and doesn't return until the user requests to quit.
     */
    void Loop();
private:
    unsigned int m_width; // the window width in pixels
    unsigned int m_height; // the window height in pixels

    SDL_Window* m_window; // the window buffer
    SDL_GLContext m_openglContext; // the OpenGL context for the window

    /**
     * Initializes SDL2 and the OpenGL context, and exits the process if any errors occur.
     */
    void Init();
};

#endif //GRAPHICS_APPLICATION_H
