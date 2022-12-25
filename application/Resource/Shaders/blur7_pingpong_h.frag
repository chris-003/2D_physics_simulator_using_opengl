#version 440 core
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D inTexture;

vec2 offset = 1.5f / textureSize(inTexture, 0);

void main()
{
    float kernel[4] = float[](
           0.398942, 0.241971, 0.053991, 0.004432
    );
    vec4 col = vec4(0, 0, 0, 0);
    float offsetx = 0;
    col = texture(inTexture, texCoord) * kernel[0];
    for (int i = 1; i < 4; ++i) {
        col += (texture(inTexture, texCoord + vec2(offsetx, 0)) + texture(inTexture, texCoord - vec2(offsetx, 0))) * kernel[i];
        offsetx += offset.x;
    }
    FragColor = col;
}