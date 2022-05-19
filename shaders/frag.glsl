#version 460 core

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_diffuse3;
    sampler2D texture_diffuse4;
    sampler2D texture_diffuse5;

    sampler2D texture_specular1;
    sampler2D texture_specular2;
    sampler2D texture_specular3;
    sampler2D texture_specular4;
    sampler2D texture_specular5;

    sampler2D texture_normal1;
    sampler2D texture_normal2;
    sampler2D texture_normal3;
    sampler2D texture_normal4;
    sampler2D texture_normal5;
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

vec3 CalcPointLight(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(pointLight.lightPos - fragPos);

    // ambient component
    vec3 ambient = pointLight.ambientStrength * pointLight.lightColor;

    // diffuse component
    float diffImpact = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diffImpact * pointLight.lightColor;

    // specular component
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = pointLight.specularStrength * spec * pointLight.lightColor;

    // attenuation
    float distance = length(pointLight.lightPos - fragPos);
    float attenuation = 1.0 / (pointLight.constantFactor +
                               pointLight.linearFactor * distance +
                               pointLight.quadraticFactor * distance * distance);
    // combine
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

void main() {
    vec3 norm = normalize(Normal);

    vec3 diffuseColor = texture(material.texture_diffuse1, TexCoords).rgb;

    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 totalLighting = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < lighting.numPointLights; i += 1) {
        totalLighting += CalcPointLight(lighting.pointLights[i], norm, FragPos, viewDir);
    }

    FragColor = vec4(diffuseColor * totalLighting, 1.0);
}