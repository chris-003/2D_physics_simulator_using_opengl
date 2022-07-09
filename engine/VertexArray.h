#pragma once
#include "BindHelper.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace engine {
class VertexBuffer;

class VertexArray {
public:
    VertexArray();
    ~VertexArray();
    void bind();
    void unbind();
    void enable(int index, int size, int offset, GLenum type = GL_FLOAT,
                GLboolean normalize = GL_FALSE);
    void bindingPoint(int attributeIndex, int bindingPoint);
    void bindVBO(int bindingPoint, VertexBuffer &vbo, int offset, int stride);

protected:
    unsigned m_vao;
};
} // namespace engine