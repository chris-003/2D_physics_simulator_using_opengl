#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace engine {
class Texture {
public:
    Texture(GLenum target);
    ~Texture();
    GLenum       target();
    unsigned int id();
    void         parameter(GLenum pname, GLint param);
    void         parameter(GLenum pname, GLfloat param);

protected:
    GLenum       m_target;
    unsigned int m_id;
};

class Texture2D : public Texture {
public:
    Texture2D();
    Texture2D(GLsizei width, GLsizei height, GLsizei levels = 0,
              GLenum internalformat = GL_RGB);
    // ~Texture2D();
    void storage(GLsizei width, GLsizei height, GLsizei levels = 0,
                 GLenum internalformat = GL_RGB);
    void image(GLint level, GLsizei width, GLsizei height, GLenum format,
               GLenum type, const void *pixels);
    void subImage(GLint level, GLsizei xoffset, GLenum yoffset, GLsizei width,
                  GLsizei height, GLenum format, GLenum type,
                  const void *pixels);
};
} // namespace engine