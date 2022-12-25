#version 440 core
layout (location = 1) uniform vec4 Color;

out vec4 FragColor;

void main() {
    FragColor = Color;
}