//
// Created by nicks on 5/12/2022.
//

#include "GeometryBuilder.h"

void GeometryBuilder::AddVertex(glm::vec3 position) {
    m_positionVectors.push_back(position);
}

void GeometryBuilder::MakeTriangle(unsigned int index1, unsigned int index2, unsigned int index3) {
    m_indices.push_back(index1);
    m_indices.push_back(index2);
    m_indices.push_back(index3);
}

std::unique_ptr<Geometry> GeometryBuilder::BuildGeometry() {
    return std::make_unique<Geometry>(m_positionVectors, m_indices);
}