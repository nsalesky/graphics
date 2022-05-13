//
// Created by nicks on 5/12/2022.
//

#ifndef GRAPHICS_CAMERAMANAGER_H
#define GRAPHICS_CAMERAMANAGER_H

#include <vector>
#include <memory>
#include "Camera.h"

#define NUM_CAMERAS 1

/**
 * A static class managing all of the cameras for the application.
 */
class CameraManager {
public:
    /**
     * Returns a reference to the global camera manager instance.
     * @return the single camera manager
     */
    static CameraManager& GetInstance() {
        static CameraManager instance;
        return instance;
    }

    /**
     * Updates the main camera index
     * @param cameraIndex the index for the new main camera
     * @throws std::invalid_argument if cameraIndex is invalid
     */
    void SetMainCamera(unsigned int cameraIndex);

    /**
     * Gets the camera with the specified index.
     * @param cameraIndex the camera's index
     * @return a reference to the specified camera
     * @throws std::invalid_argument if cameraIndex is invalid
     */
    std::unique_ptr<Camera>& GetCamera(unsigned int cameraIndex);

    /**
     * Gets the main camera instance.
     * @return a reference to the main camera
     */
    std::unique_ptr<Camera>& GetMainCamera();

    CameraManager(const CameraManager& other) = delete;
    void operator=(CameraManager& other) = delete;
private:
    /**
     * Initializes the camera manager.
     */
    CameraManager();

    std::unique_ptr<Camera> m_cameras[NUM_CAMERAS]; // the array of cameras for the application
    unsigned int m_mainCamera; // the index of the currently active camera
};


#endif //GRAPHICS_CAMERAMANAGER_H
