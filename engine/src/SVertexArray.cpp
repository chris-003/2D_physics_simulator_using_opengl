#include "SVertexArray.h"
#include "Opengl.h"
#include "SVertexBuffer.h"

namespace engine {
SVertexArray::SVertexArray() {
    glCreateVertexArrays(1, &m_vao);
}

SVertexArray::~SVertexArray() {
    glDeleteVertexArrays(1, &m_vao);
}

void SVertexArray::bind() {
    glBindVertexArray(m_vao);
}

void SVertexArray::unbind() {
    glBindVertexArray(0);
}

void SVertexArray::enable(int index) {
    glEnableVertexArrayAttrib(m_vao, index);
}

void SVertexArray::enable(int index, int size, int offset, GLenum type,
                          GLboolean normalize) {
    glEnableVertexArrayAttrib(m_vao, index);
    glVertexArrayAttribFormat(m_vao, index, size, type, normalize, offset);
}

void SVertexArray::format(int index, int size, int offset, GLenum type,
                          GLboolean normalize) {
    glVertexArrayAttribFormat(m_vao, index, size, type, normalize, offset);
}

void SVertexArray::bindingPoint(int attributeIndex, int bindingPoint) {
    glVertexArrayAttribBinding(m_vao, attributeIndex, bindingPoint);
}

void SVertexArray::bindVBO(int bindingPoint, SVertexBuffer &vbo, int offset,
                           int stride) {
    glVertexArrayVertexBuffer(m_vao, bindingPoint, vbo.m_vbo, offset, stride);
}
} // namespace engine