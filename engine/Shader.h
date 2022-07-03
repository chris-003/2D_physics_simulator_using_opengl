#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>

namespace engine {
class Shader {
public:
    enum class Type { Vertex, Fragment };
    Shader(const Type        &type,
           const std::string &source); // where "source" is souce code
    ~Shader();
    unsigned int shader() const;

protected:
    unsigned int m_shader;
};
} // namespace engine