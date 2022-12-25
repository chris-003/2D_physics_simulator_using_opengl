#pragma once
#include "Opengl.h"

namespace engine {
class STexture {
public:
    STexture(GLenum target);
    ~STexture();
    GLenum       target();
    unsigned int id();
    void         parameter(GLenum pname, GLint param);
    void         parameter(GLenum pname, GLfloat param);

protected:
    GLenum       m_target;
    unsigned int m_id;
};

class STexture2D : public STexture {
public:
    STexture2D();
    STexture2D(GLsizei width, GLsizei height, GLsizei levels = 1,
               GLenum internalformat = GL_RGB8);
    // ~Texture2D();
    void storage(GLsizei width, GLsizei height, GLsizei levels = 1,
                 GLenum internalformat = GL_RGB8);
    void image(GLint level, GLsizei width, GLsizei height, GLenum format,
               GLenum type, const void *pixels);
    void subImage(GLint level, GLsizei xoffset, GLsizei yoffset, GLsizei width,
                  GLsizei height, GLenum format, GLenum type,
                  const void *pixels);
};
} // namespace engine