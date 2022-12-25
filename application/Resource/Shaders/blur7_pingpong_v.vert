#version 440 core
layout (location = 0) in vec2 VerexPosition;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) uniform mat4 matrix;

out vec2 texCoord;

void main()
{
    gl_Position = matrix * vec4(VerexPosition, 0, 1);
    texCoord = TexCoord;
    // texCoord = vec2((gl_Position[0] + 1) / 2, (gl_Position[1] + 1) / 2);
}