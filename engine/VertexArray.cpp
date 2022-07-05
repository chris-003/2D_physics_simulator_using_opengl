#include "VertexArray.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace engine {
VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_vao);
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

void VertexArray::enable(int index, int size, int stride, int offset,
                         GLenum type, GLboolean normalize) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, normalize, stride, (void *)offset);
}
} // namespace engine