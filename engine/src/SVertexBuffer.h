#pragma once
#include "Opengl.h"

namespace engine {
class SVertexArray;

class SVertexBuffer {
    friend class SVertexArray;

public:
    SVertexBuffer();
    ~SVertexBuffer();
    const unsigned int vbo() const;
    void               bind() const;
    void               unbind();
    void write(int size, void *data, GLenum usage = GL_DYNAMIC_DRAW);

protected:
    unsigned int m_vbo;
};
} // namespace engine