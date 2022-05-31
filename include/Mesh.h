//
// Created by nicks on 5/13/2022.
//

#ifndef GRAPHICS_MESH_H
#define GRAPHICS_MESH_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>
#include "Shader.h"
#include "SceneNode.h"
#include "Material.h"

/**
 * A vertex used for creating a mesh, containing each of the necessary vectors.
 */
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

/**
 * An individual mesh composed of textured vertices and organized by index that can be rendered.
 */
class Mesh {
public:
    /**
     * Constructs a new mesh from the given vertices and indices.
     * @param vertices the vertices to use for geometry information
     * @param indices the indices to determine how to compose triangles
     * @param material this mesh's material
     */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::shared_ptr<Material> material);

    /**
     * Draws this mesh with OpenGL, assuming that the shader has already been bound.
     * @param shader the shader to bind to
     */
    void Draw(Shader& shader);
private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    std::shared_ptr<Material> m_material;

    unsigned int m_VAO, m_VBO, m_EBO;

    /**
     * Sets up the OpenGL buffers for this mesh.
     */
    void SetupMesh();
};


#endif //GRAPHICS_MESH_H
