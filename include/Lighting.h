//
// Created by nicks on 5/16/2022.
//

#ifndef GRAPHICS_LIGHTING_H
#define GRAPHICS_LIGHTING_H

#include <LightInfo.h>
#include <vector>
#include <Shader.h>
#include <memory>

/**
 * An immutable mechanism that handles passing all the necessary lighting information over to OpenGL. An instance can be created
 * per-frame, or once per-program, depending on how dynamic the lighting needs to be.
 */
class Lighting {
public:
    /**
     * Constructs a new lighting instance for the given point lights.
     * @param pointLights the point lights to use for rendering, cannot be greater than MAX_POINT_LIGHTS
     * @throws std::invalid_argument if the number of point lights is greater than MAX_POINT_LIGHTS
     */
    Lighting(std::vector<PointLightInfo> pointLights);

    /**
     * Binds the necessary lighting uniforms in the GLSL "Lighting" struct, including an array of "PointLight's", etc.
     * @param shader the shader to bind the lighting information to
     */
    void BindUniforms(Shader& shader);
private:
    std::vector<PointLightInfo> m_pointLights;
};


#endif //GRAPHICS_LIGHTING_H
