#version 440 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texturePos;

out vec2 texturePosition;

void main() {
    gl_Position = vec4(vertex.xy, 0.0, 1.0);
    texturePosition = texturePos;
}