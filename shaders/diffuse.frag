// === DESCRIPTION ===
// This is a fragment shader that only displays the diffuse material, it doesn't care about lighting at all.

#version 460 core

struct Material {
    sampler2D texture_diffuse;
    sampler2D texture_specular;
    sampler2D texture_normal;
};


uniform Material material;
uniform vec3 viewPos;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

void main() {
    vec3 diffuseColor = texture(material.texture_diffuse, TexCoords).rgb;

    FragColor = vec4(diffuseColor, 1.0);
}
