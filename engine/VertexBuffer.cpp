#include "VertexBuffer.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace engine {
VertexBuffer::VertexBuffer() {
    glCreateBuffers(1, &m_vbo);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_vbo);
}

const unsigned int VertexBuffer::vbo() const {
    return m_vbo;
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::write(int size, void *data, GLenum usage) {
    glNamedBufferData(m_vbo, size, data, usage);
}
} // namespace engine