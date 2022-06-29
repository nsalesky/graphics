//
// Created by nicks on 6/28/2022.
//

#ifndef GRAPHICS_SPOTLIGHT_H
#define GRAPHICS_SPOTLIGHT_H

#include "SceneNode.h"
#include "LightInfo.h"

/**
 * A Spot Light that emits rays in a given direction from the node's position with a given angle cutoff to create,
 * well, a spotlight!
 */
class SpotLight : public SceneNode {
public:
    /**
     * Constructs a new spot light.
     * @param dir the direction that light rays will be emitted in
     * @param cutoffAngle the cutoff angle in degrees for the "spot"
     * @param color the light's RGB color, with each channel in the range [0, 255]
     * @param ambientStrength the light's ambient strength, in the range [0, 1]
     * @param specularStrength the light's specular strength, in the range [0, 1]
     * @param debugDraw whether or not a small symbol should be rendered for debugging the light's position in space
     */
    SpotLight(glm::vec3 dir, float cutoffAngle, glm::vec3 color, float ambientStrength, float specularStrength, bool debugDraw = false);
    ~SpotLight();

protected:
    void Input(SDL_Event& e) override {}
    void Update(float deltaTime) override;
    void Render() override {}

private:
    SpotLightInfo m_info;

    unsigned int m_spotLightId;
};


#endif //GRAPHICS_SPOTLIGHT_H
