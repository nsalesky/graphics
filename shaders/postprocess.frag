#version 460 core

struct Material {
    sampler2D texture_diffuse;
    sampler2D texture_specular;
    sampler2D texture_normal;
};

uniform Material material;

in vec2 TexCoords;

out vec4 FragColor;

const float offset = 1.0 / 300.0;

void main() {
    // === Greyscale ===
//    FragColor = texture(material.texture_diffuse, TexCoords);
//    float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
//    FragColor = vec4(average, average, average, 1.0);

//    vec2 offsets[9] = vec2[](
//        vec2(-offset, offset),
//        vec2(0.0f, offset),
//        vec2(offset, offset),
//        vec2(-offset, 0.0f),
//        vec2(0.0f, 0.0f),
//        vec2(offset, 0.0f),
//        vec2(-offset, -offset),
//        vec2(0.0f, -offset),
//        vec2(offset, -offset)
//    );
//
//    float edgeKernel[9] = float[](
//        1, 1,  1,
//        1, -8, 1,
//        1, 1,  1
//    );
//
//    float blurKernel[9] = float[](
//        1.0 / 16, 2.0 / 16, 1.0 / 16,
//        2.0 / 16, 4.0 / 16, 2.0 / 16,
//        1.0 / 16, 2.0 / 16, 1.0 / 16
//    );
//
//    float sharpenKernel[9] = float[](
//        2, 2, 2,
//        2, -15, 2,
//        2, 2, 2
//    );
//
//    vec3 totalColor = vec3(0.0f);
//    for (int i = 0; i < 9; i += 1) {
//        vec3 samplePoint = vec3(texture(material.texture_diffuse, TexCoords.st + offsets[i]));
//        totalColor += samplePoint * sharpenKernel[i];
//    }
//
//    FragColor = vec4(totalColor, 1.0);

    FragColor = texture(material.texture_diffuse, TexCoords);

}
