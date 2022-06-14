#include "ShaderProgram.h"
#include <iostream>

namespace engine {
    ShaderProgram::ShaderProgram(const Shader &vert, const Shader &frag) {
        m_program = glCreateProgram();
        glAttachShader(m_program, vert.shader());
        glAttachShader(m_program, frag.shader());
        glLinkProgram(m_program);
    }

    ShaderProgram::ShaderProgram(const std::string &vert, const std::string &frag) {
        int  success;
        char infoLog[512];
        Shader v(Shader::Type::Vertex, vert), f(Shader::Type::Fragment, frag);
        m_program = glCreateProgram();
        glAttachShader(m_program, v.shader());
        {
            glGetShaderiv(v.shader(), GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(v.shader(), 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        }
        glAttachShader(m_program, f.shader());
        {
            glGetShaderiv(f.shader(), GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(f.shader(), 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        }
        glLinkProgram(m_program);
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(m_program);
    }

    void ShaderProgram::bind() const {
        glUseProgram(m_program);
    }
}