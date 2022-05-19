//
// Created by nicks on 5/15/2022.
//

#ifndef GRAPHICS_LIGHTINFO_H
#define GRAPHICS_LIGHTINFO_H

#include "glm/glm.hpp"

/**
 * The information needed to construct a Point Light in the fragment shader.
 */
struct PointLightInfo {
    glm::vec3 lightPos; // the position of the light in world space
    glm::vec3 lightColor; // the light's color, with each channel in the range [0, 1]

    float ambientStrength; // the light's ambient strength from [0, 1]
    float specularStrength; // the light's specular strength from [0, 1]

    // Attenuation, magic parameters
    float constantFactor = 1.0f;
    float linearFactor = 0.09f;
    float quadraticFactor = 0.032f;
};

#endif //GRAPHICS_LIGHTINFO_H
