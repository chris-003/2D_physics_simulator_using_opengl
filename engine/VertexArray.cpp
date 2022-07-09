#include "VertexArray.h"
#include "VertexBuffer.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace engine {
VertexArray::VertexArray() {
    glCreateVertexArrays(1, &m_vao);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_vao);
}

void VertexArray::bind() {
    glBindVertexArray(m_vao);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

void VertexArray::enable(int index, int size, int offset, GLenum type,
                         GLboolean normalize) {
    glEnableVertexAttribArray(index);
    glVertexAttribFormat(index, size, type, normalize, offset);
}

void VertexArray::bindingPoint(int attributeIndex, int bindingPoint) {
    glVertexArrayAttribBinding(m_vao, attributeIndex, bindingPoint);
}

void VertexArray::bindVBO(int bindingPoint, VertexBuffer &vbo, int offset,
                          int stride) {
    glVertexArrayVertexBuffer(m_vao, bindingPoint, vbo.m_vbo, offset, stride);
}
} // namespace engine