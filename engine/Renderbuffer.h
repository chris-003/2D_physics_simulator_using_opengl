#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace engine {
class Renderbuffer {
public:
    Renderbuffer();
    Renderbuffer(int width, int height,
                 GLenum internalformat = GL_DEPTH24_STENCIL8);
    ~Renderbuffer();
    unsigned int id();
    void         storage(int width, int height,
                         GLenum internalformat = GL_DEPTH24_STENCIL8);

protected:
    unsigned int m_id;
};
} // namespace engine