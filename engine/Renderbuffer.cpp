#include "Renderbuffer.h"

namespace engine {
Renderbuffer::Renderbuffer() {
    glCreateRenderbuffers(1, &m_id);
}

Renderbuffer::Renderbuffer(int width, int height, GLenum internalformat) {
    glCreateRenderbuffers(1, &m_id);
    glNamedRenderbufferStorage(m_id, internalformat, width, height);
}

Renderbuffer::~Renderbuffer() {
    glDeleteRenderbuffers(1, &m_id);
}

unsigned int Renderbuffer::id() {
    return m_id;
}

void Renderbuffer::storage(int width, int height, GLenum internalformat) {
    glNamedRenderbufferStorage(m_id, internalformat, width, height);
}
} // namespace engine