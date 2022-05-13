//
// Created by nicks on 5/12/2022.
//

#include "Camera.h"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/fwd.hpp>

Camera::Camera(glm::vec3 pos, glm::vec3 viewDir)
: m_pos(pos), m_viewDir(viewDir), m_upVector({0.0f, 1.0f, 0.0f}){

}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(m_pos,
                       m_pos + m_viewDir,
                       m_upVector);
}

void Camera::MoveForward(float amount) {
    glm::vec3 dir = m_viewDir * amount;
    m_pos += dir;
}

void Camera::MoveBackward(float amount)  {
    glm::vec3 dir = m_viewDir * amount;
    m_pos -= dir;
}

void Camera::MoveLeft(float amount) {
    glm::vec3 rightVector = glm::cross(m_viewDir, m_upVector);
    glm::vec3 dir = glm::vec3(rightVector.x, 0.0, rightVector.z) * amount;
    m_pos -= dir;
}

void Camera::MoveRight(float amount) {
    glm::vec3 rightVector = glm::cross(m_viewDir, m_upVector);
    glm::vec3 dir = glm::vec3(rightVector.x, 0.0, rightVector.z) * amount;
    m_pos += dir;
}

void Camera::MoveUp(float amount) {
    m_pos.y += amount;
}

void Camera::MoveDown(float amount) {
    m_pos.y -= amount;
}

void Camera::MouseLook(int mouseRelX, int mouseRelY) {
    glm::vec2 mouseDelta = {mouseRelX, mouseRelY};
    mouseDelta *= 0.2f; // mouse sensitivity

    // Update the view direction around the up vector
    m_viewDir = glm::rotate(m_viewDir, glm::radians(mouseDelta.x), m_upVector);

    glm::vec3 rightVector = glm::cross(m_viewDir, m_upVector);

    // Update the view direction around the right vector
    m_viewDir = glm::rotate(m_viewDir, glm::radians(mouseDelta.y), rightVector);
}

glm::vec3 Camera::GetPosition() {
    return m_pos;
}

void Camera::SetPosition(glm::vec3 pos) {
    m_pos = pos;
}

void Camera::SetViewDir(glm::vec3 viewDir) {
   m_viewDir = viewDir;
}