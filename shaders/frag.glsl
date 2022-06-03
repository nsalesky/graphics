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

struct DirectionalLight {
    vec3 lightDir;
    vec3 lightColor;

    float ambientStrength;
    float specularStrength;
};

struct Lighting {
    int numPointLights;
    PointLight pointLights[10];

    int numDirLights;
    DirectionalLight dirLights[10];
};

uniform Material material;
uniform Lighting lighting;
uniform vec3 viewPos;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

vec3 CalcLight(vec3 normal, vec3 viewDir, vec3 lightDir, vec3 lightColor, float ambientStrength, float specularStrength) {
    // ambient component
    vec3 ambient = ambientStrength * lightColor;

    // diffuse component
    float diffImpact = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diffImpact * lightColor;

    // specular component
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor * vec3(texture(material.texture_specular, TexCoords));

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(pointLight.lightPos - fragPos);

    // Calculate the lighting without any attenuation
    vec3 baseLighting = CalcLight(normal, viewDir, lightDir, pointLight.lightColor, pointLight.ambientStrength, pointLight.specularStrength);

    // attenuation
    float distance = length(pointLight.lightPos - fragPos);
    float attenuation = 1.0 / (pointLight.constantFactor +
                               pointLight.linearFactor * distance +
                               pointLight.quadraticFactor * distance * distance);

    return baseLighting * attenuation;
}

vec3 CalcDirLight(DirectionalLight dirLight, vec3 normal, vec3 viewDir) {
    vec3 actualDir = normalize(-dirLight.lightDir);

    return CalcLight(normal, viewDir, actualDir, dirLight.lightColor, dirLight.ambientStrength, dirLight.specularStrength);
}

void main() {
    vec3 norm = normalize(Normal);

    vec3 diffuseColor = texture(material.texture_diffuse, TexCoords).rgb;

    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 totalLighting = vec3(0.0, 0.0, 0.0);

    // Point lights
    for (int i = 0; i < lighting.numPointLights; i += 1) {
        totalLighting += CalcPointLight(lighting.pointLights[i], norm, FragPos, viewDir);
    }

    // Directional lights
    for (int i = 0; i < lighting.numDirLights; i += 1) {
        totalLighting += CalcDirLight(lighting.dirLights[i], norm, viewDir);
    }

    FragColor = vec4(diffuseColor * totalLighting, 1.0);
}