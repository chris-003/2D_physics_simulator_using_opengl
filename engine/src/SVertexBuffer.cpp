#include "SVertexBuffer.h"
#include "Opengl.h"

namespace engine {
SVertexBuffer::SVertexBuffer() {
    glCreateBuffers(1, &m_vbo);
}

SVertexBuffer::~SVertexBuffer() {
    glDeleteBuffers(1, &m_vbo);
}

const unsigned int SVertexBuffer::vbo() const {
    return m_vbo;
}

void SVertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void SVertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SVertexBuffer::write(int size, void *data, GLenum usage) {
    glNamedBufferData(m_vbo, size, data, usage);
}
} // namespace engine