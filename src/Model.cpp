//
// Created by nicks on 5/13/2022.
//

#include "Model.h"
#include <iostream>
#include "Util.h"
#include "CameraManager.h"
#include "Camera.h"
#include "Texture.h"

Model::Model(const std::string &filename, std::shared_ptr<Shader> shader) {
    m_shader = std::move(shader);

    LoadModel(filename);
}

Model::Model(const std::string &filename, std::shared_ptr<Material> material, std::shared_ptr<Shader> shader) {
    m_materialOverride = std::move(material);
    m_shader = std::move(shader);

    LoadModel(filename);
}

void Model::Render() {
    for (Mesh& mesh : m_meshes) {
        mesh.Draw(*m_shader);
    }
}

void Model::LoadModel(const std::string &filename) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename,
                                             aiProcess_Triangulate |
                                             aiProcess_FlipUVs |
                                             aiProcess_GenSmoothNormals |
                                             aiProcess_CalcTangentSpace);

    // Check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Failed to import Assimp model: " << importer.GetErrorString() << std::endl;
        return;
    }

    m_directory = filename.substr(0, filename.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene) {
    // process all of the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i += 1) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(ProcessMesh(mesh, scene));
    }

    // then do the same recursively for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i += 1) {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    // process vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i += 1) {
        Vertex vertex;

        glm::vec3 vector;

        // position
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        // normal
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;

        // texture coordinates
        if (mesh->mTextureCoords[0]) {
            vertex.texCoords = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};

            // tangent
            vector = {mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z};
            vertex.tangent = vector;

            // bitangent
            vector = {mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z};
            vertex.bitangent = vector;

        } else {
            vertex.texCoords = {0.0f, 0.0f};
        }

        vertices.push_back(vertex);
    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i += 1) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j += 1) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // process material
    if (m_materialOverride) {
        // use the override material instead of whatever was included with the model
        return {vertices, indices, m_materialOverride};
    } else if (mesh->mMaterialIndex >= 0) {
        // use the material included with the model

        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::shared_ptr<Texture> diffuseTexture = LoadMaterialTexture(material,
                                                                      aiTextureType_DIFFUSE,
                                                                      TextureType::DIFFUSE);
        std::shared_ptr<Texture> specularTexture = LoadMaterialTexture(material,
                                                                       aiTextureType_SPECULAR,
                                                                       TextureType::SPECULAR);

        return {vertices, indices, std::make_shared<Material>(diffuseTexture, specularTexture)};
    } else {
        // no material was specified, and nothing was loaded from the model

        std::cerr << "The loaded model had no material and no material was manually specified!" << std::endl;
        throw std::runtime_error("The loaded model had no material and no material was manually specified");
    }
}

std::shared_ptr<Texture> Model::LoadMaterialTexture(aiMaterial *mat, aiTextureType type, TextureType ourType) {
    // Load all the textures referenced by this material of the given type
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i += 1) {
        aiString str;
        mat->GetTexture(type, i, &str);

        // This texture's full filename with the directory
        std::string fullFilename = m_directory + "/" + str.C_Str();

        // Check if we've already loaded a texture for this image filename. If so, just reuse it
        for (unsigned int j = 0; j < m_texturesLoaded.size(); j += 1) {
            if (std::strcmp(m_texturesLoaded[j]->GetFilename().data(), fullFilename.data()) == 0) {
                return m_texturesLoaded[j];
            }
        }

        // We haven't loaded this image before, so we'll make a new texture for it and remember it in case we see it again

        std::shared_ptr<Texture> texture = std::make_shared<Texture>(fullFilename, ourType);

        m_texturesLoaded.push_back(texture);
        return texture;
    }

    std::cerr << "No texture of the given type was included in the Model!" << std::endl;
    throw std::runtime_error("no texture of the given type was included in the model");
}
