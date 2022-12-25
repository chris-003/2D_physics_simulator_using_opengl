#version 440 core
layout (location = 0) in vec2 VertexPosition;
layout (location = 1) in vec2 TexCoord;

out vec2 texCoord;

void main()
{
    gl_Position = vec4(VertexPosition, 0, 1);
    texCoord = TexCoord;
}