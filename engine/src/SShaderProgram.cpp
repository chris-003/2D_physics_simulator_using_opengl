#include "SShaderProgram.h"
#include <iostream>

namespace engine {
// SShaderProgram::SShaderProgram(const SShader &shaders...) {
//     m_program = glCreateProgram();
//     attach(shaders);
//     // glAttachShader(m_program, vert.shader());
//     // glAttachShader(m_program, frag.shader());
//     glLinkProgram(m_program);
// }

// SShaderProgram::SShaderProgram(const std::string &vert,
//                                const std::string &frag) {
//     int     success;
//     char    infoLog[512];
//     SShader v(SShader::Type::Vertex, vert), f(SShader::Type::Fragment, frag);
//     m_program = glCreateProgram();
//     glAttachShader(m_program, v.shader());
//     {
//         glGetShaderiv(v.shader(), GL_COMPILE_STATUS, &success);
//         if (!success) {
//             glGetShaderInfoLog(v.shader(), 512, NULL, infoLog);
//             std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
//                       << infoLog << std::endl;
//         }
//     }
//     glAttachShader(m_program, f.shader());
//     {
//         glGetShaderiv(f.shader(), GL_COMPILE_STATUS, &success);
//         if (!success) {
//             glGetShaderInfoLog(f.shader(), 512, NULL, infoLog);
//             std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
//                       << infoLog << std::endl;
//         }
//     }
//     glLinkProgram(m_program);
// }

SShaderProgram::~SShaderProgram() {
    glDeleteProgram(m_program);
}

void SShaderProgram::bind() const {
    glUseProgram(m_program);
}

// void SShaderProgram::attach() {
// }
// void SShaderProgram::attach(const SShader &first) {
//     glAttachShader(m_program, first.shader());
// }
// void SShaderProgram::attach(const SShader &first, const SShader &shaders...)
// {
//     attach(first);
//     attach(shaders);
// }

} // namespace engine