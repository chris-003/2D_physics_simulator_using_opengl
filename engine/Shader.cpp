#include "Shader.h"
#include <iostream>

namespace engine {
Shader::Shader(const Shader::Type &type, const std::string &source) {
    unsigned t;
    switch (type) {
    default:
    case Shader::Type::Vertex: {
        t = GL_VERTEX_SHADER;
        break;
    }
    case Shader::Type::Fragment: {
        t = GL_FRAGMENT_SHADER;
        break;
    }
    }
    m_shader        = glCreateShader(t);
    const char *str = source.c_str();
    glShaderSource(m_shader, 1, &str, NULL);
    glCompileShader(m_shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(m_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
}

Shader::~Shader() {
    glDeleteShader(m_shader);
}

unsigned int Shader::shader() const {
    return m_shader;
}
} // namespace engine