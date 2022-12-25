#include "SRenderbuffer.h"

namespace engine {
SRenderbuffer::SRenderbuffer() {
    glCreateRenderbuffers(1, &m_id);
}

SRenderbuffer::SRenderbuffer(int width, int height, GLenum internalformat) {
    glCreateRenderbuffers(1, &m_id);
    glNamedRenderbufferStorage(m_id, internalformat, width, height);
}

SRenderbuffer::~SRenderbuffer() {
    glDeleteRenderbuffers(1, &m_id);
}

unsigned int SRenderbuffer::id() {
    return m_id;
}

void SRenderbuffer::storage(int width, int height, GLenum internalformat) {
    glNamedRenderbufferStorage(m_id, internalformat, width, height);
}
} // namespace engine