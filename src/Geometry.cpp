//
// Created by nicks on 5/12/2022.
//

#include "Geometry.h"
#include "glad/glad.h"

Geometry::Geometry(const std::vector<glm::vec3>& positionVectors, const std::vector<unsigned int>& indices) {
    // Bundle all the vertex data into a single buffer
    std::vector<float> buffer;
    for (glm::vec3 pos : positionVectors) {
        buffer.push_back(pos.x);
        buffer.push_back(pos.y);
        buffer.push_back(pos.z);
    }

    // Remember how many indices there should be
    m_numIndices = indices.size();

    // Set up the VAO
    glGenVertexArrays(1, &m_VAOId);
    glBindVertexArray(m_VAOId);

    // Set up the VBO for position data
    glGenBuffers(1, &m_positionVBOId);
    glBindBuffer(GL_ARRAY_BUFFER, m_positionVBOId);
    glBufferData(GL_ARRAY_BUFFER,
                 buffer.size() * sizeof(float),
                 buffer.data(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
            0, // Attribute 0
            3, // size (Number of components) = 3 for x,y,z
            GL_FLOAT, // data type
            GL_FALSE, // is the data normalized?
            sizeof(float) * 0, // stride, number of bytes between each vertex
            nullptr // pointer to the starting point of our data
            );

    // Set up the VBO for index data
    glGenBuffers(1, &m_indexVBOId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexVBOId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(unsigned int),
                 indices.data(),
                 GL_STATIC_DRAW);

    // Unbind the VAO
    glBindVertexArray(0);
}

#include <iostream>

Geometry::~Geometry() {
    glDeleteBuffers(1, &m_positionVBOId);
    glDeleteBuffers(1, &m_indexVBOId);
    glDeleteVertexArrays(1, &m_VAOId);
}

void Geometry::Draw() {
    glBindVertexArray(m_VAOId);
    glBindBuffer(GL_ARRAY_BUFFER, m_positionVBOId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexVBOId);

    glDrawElements(GL_TRIANGLES,
                   m_numIndices,
                   GL_UNSIGNED_INT,
                   nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}