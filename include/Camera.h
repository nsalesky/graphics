//
// Created by nicks on 5/12/2022.
//

#ifndef GRAPHICS_CAMERA_H
#define GRAPHICS_CAMERA_H

#include "Transform.h"
#include <glm/glm.hpp>

/**
 * A camera in world space that builds a view matrix to transform other objects in the scene to view space.
 */
class Camera {
public:
    /**
     * Constructs a new camera at the specified position facing the given direction.
     * @param pos the camera's position in world space
     * @param lookDir the camera's viewing direction
     */
    Camera(glm::vec3 pos, glm::vec3 viewDir);

    /**
     * Calculates a transformation matrix from world space to view space.
     * @return the view transformation matrix
     */
    glm::mat4 GetViewMatrix();

    /**
     * Moves the camera forward in the view direction by the given amount.
     * @param amount the amount to move
     */
    void MoveForward(float amount);

    /**
     * Moves the camera forward in the opposite view direction by the given amount.
     * @param amount the amount to move
     */
    void MoveBackward(float amount);

    /**
     * Moves the camera left relative to its view direction and up vector by the given amount.
     * @param amount the amount to move
     */
    void MoveLeft(float amount);

    /**
     * Moves the camera right relative to its view direction and up vector by the given amount.
     * @param amount the amount to move
     */
    void MoveRight(float amount);

    /**
     * Moves the camera up in the up direction by the given amount.
     * @param amount the amount to move
     */
    void MoveUp(float amount);

    /**
     * Moves the camera down in the opposite up direction by the given amount.
     * @param amount the amount to move
     */
    void MoveDown(float amount);

    /**
     * Rotates the camera based on the given relative mouse movements.
     * @param mouseRelX the relative x movement
     * @param mouseRelY the relative y movement
     */
    void MouseLook(int mouseRelX, int mouseRelY);

    /**
     * Gets the camera's position in world space
     */
    glm::vec3 GetPosition();

    /**
     * Sets the camera's position to the given value.
     * @param pos the new camera position in world space
     */
    void SetPosition(glm::vec3 pos);

    /**
     * Gets the camera's view direction.
     * @return the camera's current viewing direction
     */
    glm::vec3 GetViewDir();

    /**
     * Sets the camera's view direction to the given vector.
     * @param viewDir the new view direction
     */
    void SetViewDir(glm::vec3 viewDir);
private:
   glm::vec3 m_pos; // the camera's position in world space
   glm::vec3 m_viewDir; // the camera's view direction
   glm::vec3 m_upVector; // the up vector
};


#endif //GRAPHICS_CAMERA_H
