#include "Texture.h"

namespace engine {
Texture::Texture(GLenum target) : m_target(target) {
    glCreateTextures(target, 1, &m_id);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_id);
}

GLenum Texture::target() {
    return m_target;
}

unsigned int Texture::id() {
    return m_id;
}

void Texture::parameter(GLenum pname, GLint param) {
    glTextureParameteri(m_id, pname, param);
}

void Texture::parameter(GLenum pname, GLfloat param) {
    glTextureParameteri(m_id, pname, param);
}

Texture2D::Texture2D() : Texture(GL_TEXTURE_2D) {
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture2D::Texture2D(GLsizei width, GLsizei height, GLsizei levels,
                     GLenum internalformat)
    : Texture(GL_TEXTURE_2D) {
    glTextureStorage2D(id(), levels, internalformat, width, height);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture2D::storage(GLsizei width, GLsizei height, GLsizei levels,
                        GLenum internalformat) {
    glTextureStorage2D(id(), levels, internalformat, width, height);
}

void Texture2D::image(GLint level, GLsizei width, GLsizei height, GLenum format,
                      GLenum type, const void *pixels) {
    glTextureSubImage2D(id(), level, 0, 0, width, height, format, type, pixels);
}

void Texture2D::subImage(GLint level, GLsizei xoffset, GLenum yoffset,
                         GLsizei width, GLsizei height, GLenum format,
                         GLenum type, const void *pixels) {
    glTextureSubImage2D(id(), level, xoffset, yoffset, width, height, format,
                        type, pixels);
}
} // namespace engine