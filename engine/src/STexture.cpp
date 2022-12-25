#include "STexture.h"

namespace engine {
STexture::STexture(GLenum target) : m_target(target) {
    glCreateTextures(target, 1, &m_id);
}

STexture::~STexture() {
    glDeleteTextures(1, &m_id);
}

GLenum STexture::target() {
    return m_target;
}

unsigned int STexture::id() {
    return m_id;
}

void STexture::parameter(GLenum pname, GLint param) {
    glTextureParameteri(m_id, pname, param);
}

void STexture::parameter(GLenum pname, GLfloat param) {
    glTextureParameteri(m_id, pname, param);
}

STexture2D::STexture2D() : STexture(GL_TEXTURE_2D) {
    glTextureParameteri(id(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(id(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

STexture2D::STexture2D(GLsizei width, GLsizei height, GLsizei levels,
                       GLenum internalformat)
    : STexture(GL_TEXTURE_2D) {
    glTextureStorage2D(id(), levels, internalformat, width, height);
    glTextureParameteri(id(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(id(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void STexture2D::storage(GLsizei width, GLsizei height, GLsizei levels,
                         GLenum internalformat) {
    glTextureStorage2D(id(), levels, internalformat, width, height);
}

void STexture2D::image(GLint level, GLsizei width, GLsizei height,
                       GLenum format, GLenum type, const void *pixels) {
    glTextureSubImage2D(id(), level, 0, 0, width, height, format, type, pixels);
}

void STexture2D::subImage(GLint level, GLsizei xoffset, GLsizei yoffset,
                          GLsizei width, GLsizei height, GLenum format,
                          GLenum type, const void *pixels) {
    glTextureSubImage2D(id(), level, xoffset, yoffset, width, height, format,
                        type, pixels);
}
} // namespace engine