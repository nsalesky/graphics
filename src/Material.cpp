//
// Created by nicks on 5/31/2022.
//

#include "Material.h"

#include <utility>

Material::Material(std::shared_ptr<Texture> diffuse, std::shared_ptr<Texture> specular)
: m_diffuseTexture(std::move(diffuse)), m_specularTexture(std::move(specular)) {

}

Material::Material(const std::string &diffuseTexture, const std::string &specularTexture)
: Material(std::make_shared<Texture>(diffuseTexture), std::make_shared<Texture>(specularTexture)){

}

void Material::Bind(Shader &shader) {
    m_diffuseTexture->Bind(shader, "material.texture_diffuse", 0);
    m_specularTexture->Bind(shader, "material.texture_specular", 1);
}

void Material::Unbind(Shader &shader) {
    m_diffuseTexture->Unbind(shader, 0);
    m_specularTexture->Unbind(shader, 1);
}