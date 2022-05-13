//
// Created by nicks on 5/12/2022.
//

#include "FreeFlyCamera.h"
#include "Camera.h"
#include "CameraManager.h"
#include <iostream>

void FreeFlyCamera::Input(SDL_Event &event) {
    std::unique_ptr<Camera>& mainCamera = CameraManager::GetInstance().GetMainCamera();

    if (event.type == SDL_KEYDOWN) {
        // Key pressed, set the corresponding axis to the necessary value
        switch (event.key.keysym.sym) {
            case SDLK_w:
                m_keyboardAxis.y = 1;
                break;
            case SDLK_s:
                m_keyboardAxis.y = -1;
                break;
            case SDLK_a:
                m_keyboardAxis.x = 1;
                break;
            case SDLK_d:
                m_keyboardAxis.x = -1;
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        // Key released, reset the corresponding axis
        switch (event.key.keysym.sym) {
            case SDLK_w:
            case SDLK_s:
                m_keyboardAxis.y = 0;
                break;
            case SDLK_a:
            case SDLK_d:
                m_keyboardAxis.x = 0;
                break;
        }
    } else if (event.type == SDL_MOUSEMOTION) {
        mainCamera->MouseLook(-event.motion.xrel, -event.motion.yrel);
    }
}

void FreeFlyCamera::Update(float deltaTime) {
    std::unique_ptr<Camera>& mainCamera = CameraManager::GetInstance().GetMainCamera();

    // Move left and right based on the X axis
    if (m_keyboardAxis.x != 0) {
        mainCamera->MoveLeft(CAMERA_SPEED * deltaTime * m_keyboardAxis.x);
    }

    // Move forward and backward based on the Y axis
    if (m_keyboardAxis.y != 0) {
        mainCamera->MoveForward(CAMERA_SPEED * deltaTime * m_keyboardAxis.y);
    }
}