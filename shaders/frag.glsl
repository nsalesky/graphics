#version 460 core

struct Material {
    sampler2D texture_diffuse;
    sampler2D texture_specular;
    sampler2D texture_normal;
};

const int POINT_LIGHT = 0;
const int DIRECTIONAL_LIGHT = 1;
const int SPOT_LIGHT = 2;

struct Light {
    int type;
    vec3 pos;
    vec3 color;
    vec3 dir;
    float innerCutoffAngle; // note: this is a cosine value
    float outerCutoffAngle; // note: this is a cosine value
    float ambientStrength;
    float specularStrength;
    float constantFactor;
    float linearFactor;
    float quadraticFactor;
};

struct Lighting {
    int numLights;
    Light lights[30];
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

vec3 CalcPointLight(Light pointLight, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(pointLight.pos - fragPos); // direction from the fragment to light

    // Calculate the lighting without any attenuation
    vec3 baseLighting = CalcLight(normal, viewDir, lightDir, pointLight.color, pointLight.ambientStrength, pointLight.specularStrength);

    // attenuation
    float distance = length(pointLight.pos - fragPos);
    float attenuation = 1.0 / (pointLight.constantFactor +
                               pointLight.linearFactor * distance +
                               pointLight.quadraticFactor * distance * distance);

    return baseLighting * attenuation;
}

vec3 CalcDirLight(Light dirLight, vec3 normal, vec3 viewDir) {
    vec3 actualDir = normalize(-dirLight.dir); // reverse direction from light to fragment to instead be direction from fragment to light

    return CalcLight(normal, viewDir, actualDir, dirLight.color, dirLight.ambientStrength, dirLight.specularStrength);
}

vec3 CalcSpotLight(Light spotLight, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(spotLight.pos - fragPos); // direction from fragment to light

    float theta = dot(lightDir, normalize(-spotLight.dir));
    float epsilon = spotLight.innerCutoffAngle - spotLight.outerCutoffAngle;
    float intensity = clamp((theta - spotLight.outerCutoffAngle) / epsilon, 0.0, 1.0);

    // base lighting
    vec3 baseLightingNoAmbient = CalcLight(normal, viewDir, lightDir, spotLight.color, 0.0, spotLight.specularStrength);
    vec3 ambient = spotLight.ambientStrength * spotLight.color;

    // attenuation
    float distance = length(spotLight.pos - fragPos);
    float attenuation = 1.0 / (spotLight.constantFactor +
                               spotLight.linearFactor * distance +
                               spotLight.quadraticFactor * distance * distance);

    // don't attenuate the ambient component and don't consider intensity for it
    // otherwise, the light would be darker inside the spotlight than outside at large distances
    // this makes sure we always have some ambient light
    return (intensity * baseLightingNoAmbient * attenuation) + ambient;
}

void main() {
    vec3 norm = normalize(Normal);

    vec3 diffuseColor = texture(material.texture_diffuse, TexCoords).rgb;

    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 totalLighting = vec3(0.0, 0.0, 0.0);

    // calculate lights
    for (int i = 0; i < lighting.numLights; i += 1) {
        if (lighting.lights[i].type == POINT_LIGHT) {
            totalLighting += CalcPointLight(lighting.lights[i], norm, FragPos, viewDir);
        } else if (lighting.lights[i].type == DIRECTIONAL_LIGHT) {
            totalLighting += CalcDirLight(lighting.lights[i], norm, viewDir);
        } else if (lighting.lights[i].type == SPOT_LIGHT) {
            totalLighting += CalcSpotLight(lighting.lights[i], norm, FragPos, viewDir);
        }
    }

    FragColor = vec4(diffuseColor * totalLighting, 1.0);
}