#version 440 core
layout (location = 0) in vec2 VerexPosition;
layout (location = 2) uniform mat4 matrix;

void main()
{
    gl_Position = matrix * vec4(VerexPosition, 0, 1);
}