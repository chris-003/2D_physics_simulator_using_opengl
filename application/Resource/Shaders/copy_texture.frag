#version 440 core
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D inTexture;

void main() {
    FragColor = texture(inTexture, texCoord);
}