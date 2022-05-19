//
// Created by nicks on 5/16/2022.
//

#ifndef GRAPHICS_POINTLIGHT_H
#define GRAPHICS_POINTLIGHT_H

#include "SceneNode.h"
#include "LightInfo.h"

class PointLight : public SceneNode {
public:
    /**
     * Constructs a new point light with the given lighting parameters.
     * @param lightPos the position of the light in local space.
     * @param lightColor the light's color, with each channel in the standard range [0, 255]
     * @param ambientStrength the light's ambient strength from [0, 1]
     * @param specularStrength the light's specular strength from [0, 1]
     */
    PointLight(glm::vec3 lightPos, glm::vec3 lightColor, float ambientStrength, float specularStrength);

    void Input(SDL_Event& event) override {}
    void Update(float deltaTime) override;
    void Render() override {}

    /**
     * Gets the information necessary to process this point light on the GPU
     * @return this point light's information
     */
    PointLightInfo GetInfo();
private:
   PointLightInfo m_info;
};


#endif //GRAPHICS_POINTLIGHT_H
