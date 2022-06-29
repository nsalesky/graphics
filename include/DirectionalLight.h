//
// Created by nicks on 6/3/2022.
//

#ifndef GRAPHICS_DIRECTIONALLIGHT_H
#define GRAPHICS_DIRECTIONALLIGHT_H

#include "SceneNode.h"
#include "LightInfo.h"

/**
 * A Directional Light that projects light rays to every fragment in the scene at a given direction.
 */
class DirectionalLight : public SceneNode {
public:
    /**
     * Constructs a new directional light.
     * @param dir the direction that light rays will travel in
     * @param color the light's RGB color, with each channel in the range [0, 255]
     * @param ambientStrength the light's ambient strength, in the range [0, 1]
     * @param specularStrength the light's specular strength, in the range [0, 1]
     */
    DirectionalLight(glm::vec3 dir, glm::vec3 color, float ambientStrength, float specularStrength);
    ~DirectionalLight();

protected:
    void Input(SDL_Event& event) override {}
    void Update(float deltaTime) override {}
    void Render() override {};
private:
    DirectionalLightInfo m_info;

    unsigned int m_dirLightID;
};


#endif //GRAPHICS_DIRECTIONALLIGHT_H
