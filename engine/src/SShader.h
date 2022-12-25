#pragma once
#include "Opengl.h"
#include <string>

namespace engine {
class SShader {
public:
    enum class Type { Geomotry, Vertex, Fragment };
    SShader(const Type        &type,
            const std::string &source); // where "source" is souce code
    ~SShader();
    SShader(const SShader &b) = delete;
    SShader(SShader &&b);
    unsigned int shader() const;
    Type         type() const;

protected:
    unsigned int m_shader;
    Type         m_type;
    bool         created;
};
} // namespace engine