//
// Created by nicks on 5/15/2022.
//

#ifndef GRAPHICS_LIGHTINFO_H
#define GRAPHICS_LIGHTINFO_H

#include "glm/glm.hpp"


/**
 * A single combined struct containing all of the possible lighting information fields. Which fields are actually
 * important depends on the "type" field of the light. I use this ugly design as a compromise to maximize the number
 * of different types of lights I have available in a scene on the GPU in GLSL shaders. With the lighting information
 * combined, I can have all point lights or all spotlights for instance, without having a separate cap for each. I wish
 * there was a better way to accomplish this, but I haven't come across anything better yet.
 */
struct LightInfo {
    /**
     * The different possible built-in light types.
     */
    enum LightType {
        POINT_LIGHT,
        DIRECTIONAL_LIGHT,
        SPOT_LIGHT,
    } type;

    glm::vec3 pos; // the position of the light in world space (used by point and spotlights)
    glm::vec3 color; // the light's RGB color, with each channel in the range [0, 1]

    glm::vec3 dir; // the direction that the light rays travel in (used by directional and spotlights)
    float innerCutoffAngle; // the cutoff angle (as a cosine of radians) around the direction. We take the cosine value, so we can compare it with the dot product of the directions (used by spotlights)
    float outerCutoffAngle; // the cutoff angle (same as the previous units) that sets the ultimate outer edge of the cone. Fragments between the two cutoffs will be smoothly interpolated (used by spotlights)

    float ambientStrength; // the light's ambient strength from [0, 1]
    float specularStrength; // the light's specular strength from [0, 1]

    // Attenuation, magic parameters
    float constantFactor = 1.0f;
    float linearFactor = 0.09f;
    float quadraticFactor = 0.032f;
};

#endif //GRAPHICS_LIGHTINFO_H
