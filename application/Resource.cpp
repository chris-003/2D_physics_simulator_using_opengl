#include "Resource.h"

Resource::Resource() {
    m_basic_vert = 
R"(#version 440 core
layout (location = 0) in vec2 VerexPosition;
layout (location = 2) uniform mat4 matrix;

void main()
{
    gl_Position = matrix * vec4(VerexPosition, 0, 1);
}
)";
    m_basic_frag = 
R"(#version 440 core
layout (location = 1) uniform vec4 VertexColor;
out vec4 FragColor;

void main()
{
    FragColor = VertexColor;
}
)";
    m_copy_texutre_vert = 
R"(#version 440 core
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
)";
    m_copy_texture_frag = 
R"(#version 440 core
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D inTexture;

void main() {
    FragColor = texture(inTexture, texCoord);
}
)";
    m_blur7_pingpong_h_vert = 
R"(#version 440 core
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
)";
    m_blur7_pingpong_h_frag = 
R"(#version 440 core
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D inTexture;

vec2 offset = 1.5f / textureSize(inTexture, 0);

void main()
{
    float kernel[4] = float[](
           0.398942, 0.241971, 0.053991, 0.004432
    );
    vec4 col = vec4(0, 0, 0, 0);
    float offsetx = 0;
    col = texture(inTexture, texCoord) * kernel[0];
    for (int i = 1; i < 4; ++i) {
        col += (texture(inTexture, texCoord + vec2(offsetx, 0)) + texture(inTexture, texCoord - vec2(offsetx, 0))) * kernel[i];
        offsetx += offset.x;
    }
    FragColor = col;
}
)";
    m_blur7_pingpong_v_vert = 
R"(#version 440 core
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
)";
    m_blur7_pingpong_v_frag = 
R"(#version 440 core
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D inTexture;

vec2 offset = 1.5f / textureSize(inTexture, 0);

void main()
{
    float kernel[4] = float[](
           0.398942, 0.241971, 0.053991, 0.004432
    );
    vec4 col = vec4(0, 0, 0, 0);
    float offsety = 0;
    col = texture(inTexture, texCoord) * kernel[0];
    for (int i = 1; i < 4; ++i) {
        col += (texture(inTexture, texCoord + vec2(0, offsety)) + texture(inTexture, texCoord - vec2(0, offsety))) * kernel[i];
        offsety += offset.y;
    }
    FragColor = col;
}
)";
    m_blurN_pingpong_h_vert = 
R"(#version 440 core
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
)";
    m_blurN_pingpong_h_frag = 
R"(#version 440 core
in vec2 texCoord;

out vec4 FragColor;

layout (location = 3) uniform int N;
layout (location = 4) uniform float kernel[1024];
uniform sampler2D inTexture;

vec2 offset = 1.5f / textureSize(inTexture, 0);

void main()
{
    vec4 col = vec4(0, 0, 0, 0);
    float offsetx = 0;
    col = texture(inTexture, texCoord) * kernel[0];
    for (int i = 1; i < N; ++i) {
        col += (texture(inTexture, texCoord + vec2(offsetx, 0)) + texture(inTexture, texCoord - vec2(offsetx, 0))) * kernel[i];
        offsetx += offset.x;
    }
    FragColor = col;
}
)";
//
    m_blurN_pingpong_v_vert = 
R"(#version 440 core
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
)";
    m_blurN_pingpong_v_frag = 
R"(#version 440 core
in vec2 texCoord;

out vec4 FragColor;

layout (location = 3) uniform int N;
layout (location = 4) uniform float kernel[1024];
uniform sampler2D inTexture;

vec2 offset = 1.5f / textureSize(inTexture, 0);

void main()
{
    vec4 col = vec4(0, 0, 0, 0);
    float offsety = 0;
    col = texture(inTexture, texCoord) * kernel[0];
    for (int i = 1; i < N; ++i) {
        col += (texture(inTexture, texCoord + vec2(0, offsety)) + texture(inTexture, texCoord - vec2(0, offsety))) * kernel[i];
        offsety += offset.y;
    }
    FragColor = col;
}
)";
}

Resource::~Resource() {
}

Resource &Resource::getInstance() {
    static Resource instance;
    return instance;
}