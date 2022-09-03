#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace engine {
class VertexArray;

class VertexBuffer {
    friend class VertexArray;

public:
    VertexBuffer();
    ~VertexBuffer();
    const unsigned int vbo() const;
    void               bind() const;
    void               unbind();
    void write(int size, void *data, GLenum usage = GL_DYNAMIC_DRAW);

protected:
    unsigned int m_vbo;
};
} // namespace engine