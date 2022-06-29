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
     * Binds the necessary lighting uniforms in the GLSL "LightingManager" struct
     * @param shader the shader to bind the lighting information to
     */
    void BindUniforms(Shader& shader);

    /**
     * Rebuilds the lighting information from all of the registered lights to prepare for
     * `BindUniforms()` to be called. This should be called only once per frame.
     */
    void RebuildLights();

    // TODO: potentially clean up this abstraction with generic `LightInfo` objects

    /**
     * Attempts to register the given light to an available slot.
     * @param infoFunc a function that returns the light's current information when called
     * @return the unique ID for the light slot registered to
     * @throws std::range_error if there are already `MAX_LIGHTS` lights registered
     */
    unsigned int RegisterLight(const std::function<LightInfo()>& infoFunc);

    /**
     * Attempts to unregister the light with the given ID.
     * @param id the light's unique ID returned by the register function
     * @throws std::invalid_argument if no light is currently registered to that ID
     */
    void UnregisterLight(unsigned int id);

    LightingManager(const LightingManager& other) = delete;
    void operator=(LightingManager& other) = delete;
private:
    // the cached results of querying the current light info
    std::vector<LightInfo> m_lights;

    // The collection of functions to query lighting info
    std::unordered_map<unsigned int, std::function<LightInfo()>> m_dynamicLights;

    /**
     * Initializes the lighting manager.
     */
     LightingManager() = default;
};


#endif //GRAPHICS_LIGHTINGMANAGER_H
