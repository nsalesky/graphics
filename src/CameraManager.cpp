//
// Created by nicks on 5/12/2022.
//

#include "CameraManager.h"
#include <stdexcept>

CameraManager::CameraManager() : m_mainCamera(0) {
    // Initialize each of the cameras
    for (unsigned int i = 0; i < NUM_CAMERAS; i += 1) {
        m_cameras[i] = std::make_unique<Camera>(glm::vec3(0,0,0), glm::vec3(0,0,1));
    }
}

void CameraManager::SetMainCamera(unsigned int cameraIndex) {
    if (cameraIndex >= NUM_CAMERAS) {
        throw std::invalid_argument("Invalid cameraIndex value!");
    }

    m_mainCamera = cameraIndex;
}

std::unique_ptr<Camera>& CameraManager::GetCamera(unsigned int cameraIndex) {
    if (cameraIndex >= NUM_CAMERAS) {
        throw std::invalid_argument("Invalid cameraIndex value!");
    }

    return m_cameras[cameraIndex];
}

std::unique_ptr<Camera>& CameraManager::GetMainCamera() {
    return m_cameras[m_mainCamera];
}