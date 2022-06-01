//
// Created by nicks on 5/13/2022.
//

#ifndef GRAPHICS_MODEL_H
#define GRAPHICS_MODEL_H

#include "SceneNode.h"
#include "Mesh.h"
#include "Texture.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

/**
 * A model loaded from an image file that acts as an object in the scene.
 */
class Model : public SceneNode {
public:
    /**
     * Constructs a new model from the given model file and using the given shader.
     * @param filename the filename of the model to load
     * @param shader the shader to use for rendering
     */
    Model(const std::string& filename, std::shared_ptr<Shader> shader);

    /**
     * Constructs a new model from the given model file, but ignoring any material that the model includes and using the
     * given material instead.
     * @param filename the filename of the model to load
     * @param material the material to use for rendering, instead of the material included with the model
     * @param shader the shader to use for rendering
     */
    Model(const std::string& filename, std::shared_ptr<Material> material, std::shared_ptr<Shader> shader);

    void Input(SDL_Event& event) override {}
    void Update(float deltaTime) override {}
    void Render() override;
private:
    std::vector<Mesh> m_meshes;
    std::vector<std::shared_ptr<Texture>> m_texturesLoaded;
    std::string m_directory;

    // A material that, if present (non-null), will be used instead of any materials specified by the loaded meshes
    std::shared_ptr<Material> m_materialOverride;

    /**
     * Loads the given model file and sets up the necessary Meshes and Textures
     * @param filename the filename of the model to load
     */
    void LoadModel(const std::string& filename);

    /**
     * Recursively processes the given Assimp node to create its meshes and then processes its child nodes in turn.
     * @param node the node to process
     * @param scene the scene in which the node exists
     */
    void ProcessNode(aiNode* node, const aiScene* scene);

    /**
     * Processes the given Assimp mesh to produce our Mesh instance that can be rendered with OpenGL.
     * @param mesh the mesh to process
     * @param scene the scene in which the mesh exists
     * @return the corresponding Mesh
     */
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

    /**
     * Loads the first texture from the image files referenced by the given material with the given type and type name.
     * @param mat the material to load
     * @param type the type of texture to load, in the context of Assimp
     * @param ourType the type to use internally for the new texture objects
     * @return the corresponding texture
     */
    std::shared_ptr<Texture> LoadMaterialTexture(aiMaterial* mat, aiTextureType type, TextureType ourType);
};

#endif //GRAPHICS_MODEL_H
