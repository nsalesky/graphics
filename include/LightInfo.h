//
// Created by nicks on 5/15/2022.
//

#ifndef GRAPHICS_LIGHTINFO_H
#define GRAPHICS_LIGHTINFO_H

#include "glm/glm.hpp"

/**
 * The information needed to construct a Point Light in the fragment shader, ie a light
 * positioned at a given point that emits equally in all directions.
 */
struct PointLightInfo {
    glm::vec3 pos; // the position of the light in world space
    glm::vec3 color; // the light's RGB color, with each channel in the range [0, 1]

    float ambientStrength; // the light's ambient strength from [0, 1]
    float specularStrength; // the light's specular strength from [0, 1]

    // Attenuation, magic parameters
    float constantFactor = 1.0f;
    float linearFactor = 0.09f;
    float quadraticFactor = 0.032f;
};

/**
 * The information needed to construct a Directional Light in the fragment shader, ie a light
 * without a position that emits light universally in a given direction.
 */
struct DirectionalLightInfo {
    glm::vec3 dir; // the direction that the light rays travel in
    glm::vec3 color; // the light's RGB color, with each channel in the range [0, 1]

    float ambientStrength; // the light's ambient strength from [0, 1]
    float specularStrength; // the light's specular strength from [0, 1]
};

/**
 * The information needed to construct a Spot Light in the fragment shader, ie a light with
 * a position that emits at a given direction and radius like a spotlight.
 */
struct SpotLightInfo {
    glm::vec3 pos; // the position of the light in world space
    glm::vec3 dir; // the direction that the light rays travel in
    float innerCutoffAngle; // the cutoff angle (as a cosine of radians) around the direction. We take the cosine value, so we can compare it with the dot product of the directions
    float outerCutoffAngle; // the cutoff angle (same as the previous units) that sets the ultimate outer edge of the cone. Fragments between the two cutoffs will be smoothly interpolated
    glm::vec3 color; // the light's RGB color, with each channel in the range [0, 1]

    float ambientStrength; // the light's ambient strength from [0, 1]
    float specularStrength; // the light's specular strength from [0, 1]

    // Attenuation, magic parameters
    float constantFactor = 1.0f;
    float linearFactor = 0.09f;
    float quadraticFactor = 0.032f;
};

#endif //GRAPHICS_LIGHTINFO_H
