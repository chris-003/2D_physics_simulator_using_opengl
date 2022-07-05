#pragma once
#include "BindHelper.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace engine {
class VertexArray {
public:
    VertexArray();
    ~VertexArray();
    void bind();
    void unbind();
    void enable(int index, int size, int stride, int offset,
                GLenum type = GL_FLOAT, GLboolean normalize = GL_FALSE);

protected:
    unsigned m_vao;
};
} // namespace engine