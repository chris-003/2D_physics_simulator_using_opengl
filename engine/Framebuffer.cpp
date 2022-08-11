#include "Framebuffer.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace engine {
Framebuffer::Framebuffer(int width, int height) {
    glCreateFramebuffers(1, &m_fbo);
    // glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    // glGenTextures(1, &m_texture);
    // glBindTexture(GL_TEXTURE_2D, m_texture);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
    //              GL_UNSIGNED_BYTE, NULL);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glBindTexture(GL_TEXTURE_2D, 0);
    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
    // GL_TEXTURE_2D,
    //                        m_texture, 0);
    {
        auto ptr = std::shared_ptr<Texture2D>(new Texture2D(width, height));
        attach(ptr);
    }

    // glGenRenderbuffers(1, &m_rbo);
    // glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width,
    // height); glBindRenderbuffer(GL_RENDERBUFFER, 0);
    // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
    //                           GL_RENDERBUFFER, m_rbo);
    {
        auto ptr =
            std::shared_ptr<Renderbuffer>(new Renderbuffer(width, height));
        attach(ptr);
    }
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::~Framebuffer() {
    glDeleteTextures(1, &m_fbo);
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int Framebuffer::texture() {
    return m_texture->id();
}

void Framebuffer::bindTexture(int index) {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, texture());
}

void Framebuffer::attach(std::shared_ptr<Texture2D> &texture) {
    glNamedFramebufferTexture(m_fbo, GL_COLOR_ATTACHMENT0, texture->id(), 0);
    m_texture = texture;
}

void Framebuffer::attach(std::shared_ptr<Renderbuffer> &renderbuffer) {
    glNamedFramebufferRenderbuffer(m_fbo, GL_DEPTH_STENCIL_ATTACHMENT,
                                   GL_RENDERBUFFER, renderbuffer->id());
    m_renderbuffer = renderbuffer;
}
} // namespace engine