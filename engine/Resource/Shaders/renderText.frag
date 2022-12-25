#version 440 core
in vec2 texturePosition;
out vec4 color;

uniform sampler2D textTexture;
layout (location = 2) uniform vec4 textColor;

void main() {
    color = textColor * vec4(1.0, 1.0, 1.0, texture(textTexture, texturePosition));
}