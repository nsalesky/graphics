//
// Created by nicks on 5/12/2022.
//

#include "CubeNode.h"
#include "GeometryBuilder.h"
#include "Util.h"
#include "ShaderManager.h"

#include <iostream>

CubeNode::CubeNode() {
    m_shader = ShaderManager::GetInstance().GetShader("main");

    GeometryBuilder gb;

    gb.AddVertex({0.5f, 0.5f, 0.0f });
    gb.AddVertex({0.5f, -0.5f, 0.0f });
    gb.AddVertex({-0.5f, -0.5f, 0.0f });
    gb.AddVertex({-0.5f, 0.5f, 0.0f });

    gb.MakeTriangle(0, 1, 3);
    gb.MakeTriangle(1, 2, 3);

    m_geometry = std::move(gb.BuildGeometry());
}

void CubeNode::Update(float deltaTime) {

}

void CubeNode::Render() {
    m_geometry->Draw();
}