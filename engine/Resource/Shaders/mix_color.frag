#version 440 core
in vec2 texCoord;
layout (location = 2) in vec4 Color;

out vec4 FragColor;

uniform sampler2D inTexture;

void main() {
    FragColor = vec4(mix(vec3(texture(inTexture, texCoord)), vec3(Color), Color.a), 1);
}