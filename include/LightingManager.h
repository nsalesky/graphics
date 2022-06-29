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

    // TODO: potentially clean up this abstraction with generic `LightInfo` objects

    /**
     * Attempts to register the given point light to an available slot.
     * @param infoFunc a function that returns the point light's current information when called
     * @return the unique ID for the point light slot registered to
     * @throws std::range_error if there are already `MAX_POINT_LIGHTS` point lights registered
     */
    unsigned int RegisterPointLight(const std::function<PointLightInfo()>& infoFunc);

    /**
     * Attempts to register the given directional light to an available slot.
     * @param infoFunc a function that returns the directional light's current information when called
     * @return the unique ID for the directional light slot registered to
     * @throws std::range_error if there are already `MAX_DIRECTIONAL_LIGHTS` directional lights registered
     */
    unsigned int RegisterDirectionalLight(const std::function<DirectionalLightInfo()>& infoFunc);

    /**
     * Attempts to register the given spot light to an available slot.
     * @param infoFunc a function that returns the spot light's current information when called
     * @return the unique ID for the spot light slot registered to
     * @throws std::range_error if there are already `MAX_SPOT_LIGHT` spot lights registered
     */
    unsigned int RegisterSpotLight(const std::function<SpotLightInfo()>& infoFunc);

    /**
     * Attempts to unregister the point light with the given ID.
     * @param id the point light's unique ID returned by the register function
     * @throws std::invalid_argument if no point light is currently registered to that ID
     */
    void UnregisterPointLight(unsigned int id);

    /**
     * Attempts to unregister the directional light with the given ID.
     * @param id the directional light's unique ID returned by the register function
     * @throws std::invalid_argument if no directional light is currently registered to that ID
     */
    void UnregisterDirectionalLight(unsigned int id);

    /**
     * Attempts to unregister the spot light with the given ID.
     * @param id the spot light's unique ID returned by the register function
     * @throws std::invalid_argument if no spot light is currently registered to that ID
     */
    void UnregisterSpotLight(unsigned int id);

    LightingManager(const LightingManager& other) = delete;
    void operator=(LightingManager& other) = delete;
private:
    // the cached results of calling the below functions
    std::vector<PointLightInfo> m_pointLights;
    std::vector<DirectionalLightInfo> m_dirLights;
    std::vector<SpotLightInfo> m_spotLights;

    // The collections of functions to query lighting info
    std::unordered_map<unsigned int, std::function<PointLightInfo()>> m_dynamicPointLights;
    std::unordered_map<unsigned int, std::function<DirectionalLightInfo()>> m_dynamicDirLights;
    std::unordered_map<unsigned int, std::function<SpotLightInfo()>> m_dynamicSpotLights;

    /**
     * Initializes the lighting manager.
     */
     LightingManager() = default;
};


#endif //GRAPHICS_LIGHTINGMANAGER_H
