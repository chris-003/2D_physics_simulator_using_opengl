#pragma once
#include "Shader.h"
#include <string>

namespace engine {
class ShaderProgram {
public:
    ShaderProgram(const Shader &vert, const Shader &frag);
    ShaderProgram(const std::string &vert, const std::string &frag);
    ~ShaderProgram();
    void bind() const;

public:
    unsigned int m_program;
};
} // namespace engine