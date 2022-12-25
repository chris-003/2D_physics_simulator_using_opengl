#include "SShader.h"
#include <iostream>

namespace engine {
SShader::SShader(const SShader::Type &type, const std::string &source) {
    GLenum t;
    m_type = type;
    switch (type) {
    default:
    case SShader::Type::Geomotry: {
        t = GL_GEOMETRY_SHADER;
        break;
    }
    case SShader::Type::Vertex: {
        t = GL_VERTEX_SHADER;
        break;
    }
    case SShader::Type::Fragment: {
        t = GL_FRAGMENT_SHADER;
        break;
    }
    }
    m_shader        = glCreateShader(t);
    const char *str = source.c_str();
    glShaderSource(m_shader, 1, &str, NULL);
    glCompileShader(m_shader);
    created = true;

    int  success;
    char infoLog[512];
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(m_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::";
        switch (m_type) {
        case Type::Vertex: {
            std::cout << "VERTEX";
            break;
        }
        case Type::Fragment: {
            std::cout << "FRAGMENT";
            break;
        }
        case Type::Geomotry: {
            std::cout << "GEOMETRY";
            break;
        }
        }
        std::cout << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        created = false;
    }
}

SShader::~SShader() {
    if (created) {
        glDeleteShader(m_shader);
    }
}

SShader::SShader(SShader &&b) {
    this->m_type   = b.m_type;
    this->created  = b.created;
    this->m_shader = b.m_shader;
    b.created      = false;
}

unsigned int SShader::shader() const {
    return m_shader;
}

engine::SShader::Type SShader::type() const {
    return m_type;
}
} // namespace engine