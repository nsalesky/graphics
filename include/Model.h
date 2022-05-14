//
// Created by nicks on 5/13/2022.
//

#ifndef GRAPHICS_MODEL_H
#define GRAPHICS_MODEL_H

#include "SceneNode.h"
#include "Mesh.h"
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
     * @param shader the shader to use
     */
    Model(const std::string& filename, std::shared_ptr<Shader> shader);

    void Input(SDL_Event& event) override {}
    void Update(float deltaTime) override {}
    void Render() override;
private:
    std::vector<Mesh> m_meshes;
    std::vector<std::shared_ptr<Texture>> m_texturesLoaded;
    std::string m_directory;

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
     * Loads the textures from the image files referenced by the given material with the given type and type name.
     * @param mat the material to load
     * @param type the type of texture to load, in the context of Assimp
     * @param ourType the type to use internally for the new texture objects
     * @return
     */
    std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType ourType);
};

#endif //GRAPHICS_MODEL_H
