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
#include "Texture.h"
#include "SceneNode.h"

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
     * Constructs a new mesh from the given vertices, indices, and textures.
     * @param vertices the vertices to use for geometry information
     * @param indices the indices to determine how to compose triangles
     * @param textures the list of textures to use for per-pixel detail
     */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<Texture>> textures);

    /**
     * Draws this mesh with OpenGL.
     * @param shader the shader to bind to
     */
    void Draw(std::shared_ptr<Shader>& shader);
private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<std::shared_ptr<Texture>> m_textures;

    unsigned int m_VAO, m_VBO, m_EBO;

    /**
     * Sets up the OpenGL buffers for this mesh.
     */
    void SetupMesh();
};


#endif //GRAPHICS_MESH_H
