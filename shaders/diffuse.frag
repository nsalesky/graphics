// === DESCRIPTION ===
// This is a fragment shader that only displays the diffuse material, it doesn't care about lighting at all.

#version 460 core

struct Material {
    sampler2D texture_diffuse;
    sampler2D texture_specular;
    sampler2D texture_normal;
};

struct PointLight {
    vec3 lightPos;
    vec3 lightColor;

    float ambientStrength;
    float specularStrength;

    float constantFactor;
    float linearFactor;
    float quadraticFactor;
};

struct Lighting {
    int numPointLights;
    PointLight pointLights[10];
};

uniform Material material;
uniform Lighting lighting;
uniform vec3 viewPos;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

void main() {
    vec3 diffuseColor = texture(material.texture_diffuse, TexCoords).rgb;

    FragColor = vec4(diffuseColor, 1.0);
}
