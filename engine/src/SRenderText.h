#pragma once
#if 0
#include <ft2build.h>
#include FT_FREETYPE_H
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <map>

namespace engine {
namespace renderText {
struct Character {
    GLuint     TextureID; // 字形纹理的ID
    glm::ivec2 Size;      // 字形大小
    glm::ivec2 Bearing;   // 从基准线到字形左部/顶部的偏移值
    GLuint     Advance;   // 原点距下一个字形原点的距离
};

typedef std::map<GLchar, Character> Characters;

export Characters defaultCharacters;

} // namespace renderText
} // namespace engine
#endif