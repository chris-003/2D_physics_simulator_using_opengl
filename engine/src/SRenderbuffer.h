#pragma once
#include "Opengl.h"

namespace engine {
class SRenderbuffer {
public:
    SRenderbuffer();
    SRenderbuffer(int width, int height,
                  GLenum internalformat = GL_DEPTH24_STENCIL8);
    ~SRenderbuffer();
    unsigned int id();
    void         storage(int width, int height,
                         GLenum internalformat = GL_DEPTH24_STENCIL8);

protected:
    unsigned int m_id;
};
} // namespace engine