#include "Resource.h"

namespace engine {
namespace Resource {
ShaderProgram &ShaderProgram_copy() {
    static ShaderProgram program(
        R"(#version 440 core
layout (location = 0) in vec2 VerexPosition;
layout (location = 1) in vec2 TexCoord;

out vec2 texCoord;

void main()
{
    gl_Position = vec4(VerexPosition, 0, 1);
    texCoord = TexCoord;
})",
        R"(#version 440 core
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D inTexture;

void main() {
    FragColor = texture(inTexture, texCoord);
})");
    return program;
}

ShaderProgram &ShaderProgram_mix_color() {
    static ShaderProgram program(
        R"(#version 440 core
layout (location = 0) in vec2 VerexPosition;
layout (location = 1) in vec2 TexCoord;

out vec2 texCoord;

void main()
{
    gl_Position = vec4(VerexPosition, 0, 1);
    texCoord = TexCoord;
})",
        R"(#version 440 core
in vec2 texCoord;
layout (location = 2) in vec4 Color;

out vec4 FragColor;

uniform sampler2D inTexture;

void main() {
    FragColor = vec4(mix(vec3(texture(inTexture, texCoord)), vec3(Color), Color.a), 1);
})");
    return program;
}

ShaderProgram &ShaderProgram_color() {
    static ShaderProgram program(
        R"(#version 440 core
layout (location = 0) in vec2 VerexPosition;

void main()
{
    gl_Position = vec4(VerexPosition, 0, 1);
})",
        R"(#version 440 core
layout (location = 1) uniform vec4 Color;

out vec4 FragColor;

void main() {
    FragColor = Color;
})");
    return program;
}
namespace renderText {
ShaderProgram &shaderProgram() {
    static ShaderProgram program(
        R"(#version 440 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texturePos;

out vec2 texturePosition;

void main() {
    gl_Position = vec4(vertex.xy, 0.0, 1.0);
    texturePosition = texturePos;
})",
        R"(#version 440 core
in vec2 texturePosition;
out vec4 color;

uniform sampler2D textTexture;
layout (location = 2) uniform vec4 textColor;

void main() {
    color = textColor * vec4(1.0, 1.0, 1.0, texture(textTexture, texturePosition));
})");
    return program;
}
} // namespace renderText
} // namespace Resource
} // namespace engine