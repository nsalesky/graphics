//
// Created by nicks on 5/13/2022.
//

#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::shared_ptr<Material> material)
: m_vertices(vertices), m_indices(indices), m_material(material) {

    SetupMesh();
}

void Mesh::SetupMesh() {
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    // Set up VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 m_vertices.size() * sizeof(Vertex),
                 &m_vertices[0],
                 GL_STATIC_DRAW);

    // Set up EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 m_indices.size() * sizeof(unsigned int),
                 &m_indices[0],
                 GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

    // Unbind VAO
    glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader) {
    m_material->Bind(shader);

    // Draw the mesh
    glBindVertexArray(m_VAO);

    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    m_material->Unbind(shader);
}