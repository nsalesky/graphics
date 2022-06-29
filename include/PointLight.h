//
// Created by nicks on 5/16/2022.
//

#ifndef GRAPHICS_POINTLIGHT_H
#define GRAPHICS_POINTLIGHT_H

#include "SceneNode.h"
#include "LightInfo.h"
#include "Mesh.h"

class PointLight : public SceneNode {
public:
    /**
     * Constructs a new point light with the given lighting parameters.
     * @param color the light's color, with each channel in the standard range [0, 255]
     * @param ambientStrength the light's ambient strength from [0, 1]
     * @param specularStrength the light's specular strength from [0, 1]
     * @param debugDraw whether or not a small symbol should be rendered for debugging the light's position in space
     */
    PointLight(glm::vec3 color, float ambientStrength, float specularStrength, bool debugDraw = false);
    ~PointLight();

protected:
    void Input(SDL_Event& event) override {}
    void Update(float deltaTime) override;
    void Render() override {};

private:
   PointLightInfo m_info;

   unsigned int m_pointLightID;
};


#endif //GRAPHICS_POINTLIGHT_H
