#version 440 core
layout (location = 0) in vec2 VerexPosition;

void main()
{
    gl_Position = vec4(VerexPosition, 0, 1);
}