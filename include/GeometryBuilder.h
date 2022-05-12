//
// Created by nicks on 5/12/2022.
//

#ifndef GRAPHICS_GEOMETRYBUILDER_H
#define GRAPHICS_GEOMETRYBUILDER_H

#include <vector>
#include "glm/glm.hpp"
#include "Geometry.h"
#include <memory>

/**
 * A builder for Geometry objects that allows you to build up geometry programmatically before bundling
 * it together.
 */
class GeometryBuilder {
public:
    /**
     * Adds a new vertex to the available building blocks for new triangles.
     * @param position the vertex's position in local space
     */
    void AddVertex(glm::vec3 position);

    /**
     * Creates a new triangle composed of the given vertices by index.
     * @param index1 the index of the first vertex
     * @param index2 the index of the second vertex
     * @param index3 the index of the third vertex
     */
    void MakeTriangle(unsigned int index1, unsigned int index2, unsigned int index3);

    /**
     * Bundle together the Geometry information into an object that can be bound in OpenGL.
     * @return
     */
    std::unique_ptr<Geometry> BuildGeometry();
private:
    std::vector<unsigned int> m_indices;
    std::vector<glm::vec3> m_positionVectors;
};


#endif //GRAPHICS_GEOMETRYBUILDER_H
