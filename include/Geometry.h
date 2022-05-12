//
// Created by nicks on 5/12/2022.
//

#ifndef GRAPHICS_GEOMETRY_H
#define GRAPHICS_GEOMETRY_H

#include <vector>
#include "glm/glm.hpp"

/**
 * A Geometry object containing geometry information that can be bound for use in OpenGL rendering calls.
 */
class Geometry {
public:
    /**
     * Constructs a geometry object with the given vertex information that can be bound for OpenGL rendering.
     * @param positionVectors the position vectors to use
     * @param indices the indices to use
     */
    Geometry(const std::vector<glm::vec3>& positionVectors, const std::vector<unsigned int>& indices);
    ~Geometry();

    /**
     * Renders this geometry data.
     */
    void Draw();
private:
    unsigned int m_VAOId; // the VAO making it easy to bind all of our VBO's at once
    unsigned int m_positionVBOId; // the VBO for position data
    unsigned int m_indexVBOId; // the VBO for indices

    unsigned int m_numIndices; // the number of indices to render in each `draw()` call
};


#endif //GRAPHICS_GEOMETRY_H
