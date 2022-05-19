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

void Model::Render() {
    glm::mat4 modelMatrix = m_localTransform.GetInternalMatrix();
    glm::mat4 viewMatrix = CameraManager::GetInstance().GetMainCamera()->GetViewMatrix();
    glm::mat4 projectionMatrix = Util::CalculateProjectionMatrix();

    m_shader->SetMatrix4("modelMatrix", modelMatrix);
    m_shader->SetMatrix4("viewMatrix", viewMatrix);
    m_shader->SetMatrix4("projectionMatrix", projectionMatrix);

    for (Mesh& mesh : m_meshes) {
        mesh.Draw(m_shader);
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
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        // 1. diffuse maps
        std::vector<std::shared_ptr<Texture>> diffuseMaps = LoadMaterialTextures(material,
                                                                aiTextureType_DIFFUSE,
                                                                TextureType::DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        // 2. specular maps
        std::vector<std::shared_ptr<Texture>> specularMaps = LoadMaterialTextures(material,
                                                                 aiTextureType_SPECULAR,
                                                                 TextureType::SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        // 3. normal maps
        std::vector<std::shared_ptr<Texture>> normalMaps = LoadMaterialTextures(material,
                                                               aiTextureType_HEIGHT, // TODO: make sure this is right
                                                               TextureType::NORMAL);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        // 4. height maps
        std::vector<std::shared_ptr<Texture>> heightMaps = LoadMaterialTextures(material,
                                                               aiTextureType_AMBIENT,
                                                               TextureType::HEIGHT);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    }

    return {vertices, indices, textures};
}

std::vector<std::shared_ptr<Texture>> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureType ourType) {
    std::vector<std::shared_ptr<Texture>> textures;

    // Load all the textures referenced by this material of the given type
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i += 1) {
        aiString str;
        mat->GetTexture(type, i, &str);

        // This texture's full filename with the directory
        std::string fullFilename = m_directory + "/" + str.C_Str();

        // Check if we've already loaded a texture for this image filename. If so, just reuse it
        bool skip = false;
        for (unsigned int j = 0; j < m_texturesLoaded.size(); j += 1) {
            if (std::strcmp(m_texturesLoaded[j]->GetFilename().data(), fullFilename.data()) == 0) {
                textures.push_back(m_texturesLoaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip) {
            // We haven't loaded this image before, so we'll make a new texture for it and remember it in case we see it again

            std::shared_ptr<Texture> texture = std::make_shared<Texture>(fullFilename, ourType);

            textures.push_back(texture);
            m_texturesLoaded.push_back(texture);
        }
    }

    return textures;
}
