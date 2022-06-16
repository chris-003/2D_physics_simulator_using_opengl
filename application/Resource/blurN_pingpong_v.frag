#version 440 core
in vec2 texCoord;

out vec4 FragColor;

layout (location = 3) uniform int N;
layout (location = 4) uniform float kernel[1024];
uniform sampler2D inTexture;

vec2 offset = 1.5f / textureSize(inTexture, 0);

void main()
{
    vec4 col = vec4(0, 0, 0, 0);
    float offsety = 0;
    col = texture(inTexture, texCoord) * kernel[0];
    for (int i = 1; i < N; ++i) {
        col += (texture(inTexture, texCoord + vec2(0, offsety)) + texture(inTexture, texCoord - vec2(0, offsety))) * kernel[i];
        offsety += offset.y;
    }
    FragColor = col;
}