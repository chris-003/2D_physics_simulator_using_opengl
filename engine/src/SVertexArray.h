#pragma once
#include "Opengl.h"
#include "SBindHelper.h"

namespace engine {
class SVertexBuffer;

class SVertexArray {
public:
    SVertexArray();
    ~SVertexArray();
    void bind();
    void unbind();
    void enable(int index);
    void enable(int index, int size, int offset, GLenum type = GL_FLOAT,
                GLboolean normalize = GL_FALSE);
    void format(int index, int size, int offset, GLenum type = GL_FLOAT,
                GLboolean normalize = GL_FALSE);
    void bindingPoint(int attributeIndex, int bindingPoint);
    void bindVBO(int bindingPoint, SVertexBuffer &vbo, int offset, int stride);

protected:
    unsigned m_vao;
};
} // namespace engine