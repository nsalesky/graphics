//
// Created by nicks on 5/10/2022.
//

#ifndef GRAPHICS_TRANSFORM_H
#define GRAPHICS_TRANSFORM_H

#include "glm/glm.hpp"
#include <glad/glad.h>

/**
 * A Transform that can, well, transform an object to a given position, rotation, scale, etc in 3D OpenGL space.
 */
class Transform {
public:
    /**
     * Constructs a new identity transform.
     */
    Transform();

    /**
     * Translates this transform to the given coordinates.
     * @param x the x-coordinate
     * @param y the y-coordinate
     * @param z the z-coordinate
     */
    void Translate(float x, float y, float z);

    /**
     * Scales this transform by the given amounts.
     * @param scale_x the scaling factor for the x-dimension
     * @param scale_y the scaling factor for the y-dimension
     * @param scale_z the scaling factor for the z-dimension
     */
    void Scale(float scale_x, float scale_y, float scale_z);

    /**
     * Rotates this transform by the given amount on the given vector
     * @param radians the amount to rotate in radians
     * @param x the x-coordinate of the rotation vector
     * @param y the y-coordinate of the rotation vector
     * @param z the z-coordinate of the rotation vector
     */
    void Rotate(float radians, float x, float y, float z);

    /**
     * Copies the internal matrix of the given transform to this transform.
     * @param other the transform to copy
     * @return this modified transform
     */
    Transform& operator=(const Transform& other);

    /**
     * Multiplies two transforms together.
     * @param lhs the left-hand transform
     * @param rhs the right-hand transform
     * @return the multiplied transform
     */
    friend Transform operator*(const Transform& lhs, const Transform& rhs);

    /**
     * Copies this transform's internal model matrix.
     * @return a copy of this transform's model matrix
     */
    glm::mat4 GetInternalMatrix() const;

    /**
     * Copies this transform's internal model matrix in a format usable by OpenGL.
     * @return the matrix of raw float values
     */
    GLfloat* GetOpenGLMatrix();
private:
    glm::mat4 m_modelMatrix;
};

#endif //GRAPHICS_TRANSFORM_H
