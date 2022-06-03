//
// Created by nicks on 5/16/2022.
//

#ifndef GRAPHICS_LIGHTINGMANAGER_H
#define GRAPHICS_LIGHTINGMANAGER_H

#include "LightInfo.h"
#include <vector>
#include "Shader.h"
#include <memory>
#include <map>
#include <functional>

/**
 * A singleton object that manages lighting information. Lights can be registered/unregistered with a unique ID, and then
 * once per frame, this manager queries all registered lights to bundle up the lighting information to be sent to the GPU.
 */
class LightingManager {
public:
    /**
     * Returns the single instance of the lighting manager.
     * @return the lighting manager instance
     */
    static LightingManager& GetInstance() {
        static LightingManager instance;
        return instance;
    }

    /**
     * Binds the necessary lighting uniforms in the GLSL "LightingManager" struct, including an array of "PointLight's", etc.
     * @param shader the shader to bind the lighting information to
     */
    void BindUniforms(Shader& shader);

    /**
     * Rebuilds the lighting information from all of the registered lights to prepare for
     * `BindUniforms()` to be called. This should be called only once per frame.
     */
    void RebuildLights();

    /**
     * Attempts to register the given point light to an available slot.
     * @param infoFunc a function that returns the point light's current information when called
     * @return the unique ID for the point light slot registered to
     * @throws std::range_error if there are already `MAX_POINT_LIGHTS` point lights registered
     */
    unsigned int RegisterPointLight(const std::function<PointLightInfo()>& infoFunc);

    /**
     * Attempts to unregister the point light with the given ID.
     * @param id the point light's unique ID returned by the register function
     * @throws std::invalid_argument if no point light is currently registered to that ID
     */
    void UnregisterPointLight(unsigned int id);

    LightingManager(const LightingManager& other) = delete;
    void operator=(LightingManager& other) = delete;
private:
    std::vector<PointLightInfo> m_pointLights;

    std::unordered_map<unsigned int, std::function<PointLightInfo()>> m_dynamicPointLights;

    /**
     * Determines the lowest point light ID not currently being used by any point lights.
     * @return the lowest ID, or -1 if all slots are full
     */
    int FindLowestAvailablePointLightID();

    /**
     * Initializes the lighting manager.
     */
     LightingManager() = default;
};


#endif //GRAPHICS_LIGHTINGMANAGER_H
