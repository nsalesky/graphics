//
// Created by nicks on 5/10/2022.
//

#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"

Transform::Transform() {
    m_modelMatrix = glm::mat4(1.0f);
}

void Transform::Translate(float x, float y, float z) {
    m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(x, y, z));
}

void Transform::Scale(float scale_x, float scale_y, float scale_z) {
    m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(scale_x, scale_y, scale_z));
}

void Transform::Rotate(float radians, float x, float y, float z) {
    m_modelMatrix = glm::rotate(m_modelMatrix, radians, glm::vec3(x, y, z));
}

Transform& Transform::operator=(const Transform &other) {
    m_modelMatrix = other.m_modelMatrix;
    return *this;
}

Transform operator*(const Transform& lhs, const Transform& rhs) {
    Transform result;
    result.m_modelMatrix = lhs.m_modelMatrix * rhs.m_modelMatrix;
    return result;
}

glm::mat4 Transform::GetInternalMatrix() const {
    return m_modelMatrix;
}

GLfloat* Transform::GetOpenGLMatrix() {
    return &m_modelMatrix[0][0];
}
