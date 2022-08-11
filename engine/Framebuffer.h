#pragma once
#include "Renderbuffer.h"
#include "Texture.h"
#include <memory>

namespace engine {
class Framebuffer {
public:
    // create a framebuffer WITH a texture and a renderbuffer of the default
    // type
    Framebuffer(int width, int height);
    // create a framebuffer WITH the specific texture and renderbuffer
    // note: the texture or renderbuffer is ignored if the pointer is pointed to
    // null(nullptr)
    Framebuffer(int width, int height, std::shared_ptr<Texture2D> &texture,
                std::shared_ptr<Renderbuffer> &renderbuffer);
    ~Framebuffer();

public:
    unsigned int         id();
    virtual void         bind();
    virtual void         unbind();
    virtual unsigned int texture();
    virtual void         bindTexture(int index = 0);
    void                 attach(std::shared_ptr<Texture2D> &texture);
    void                 attach(std::shared_ptr<Renderbuffer> &renderbuffer);

protected:
    unsigned int                  m_fbo;
    std::shared_ptr<Texture2D>    m_texture;
    std::shared_ptr<Renderbuffer> m_renderbuffer;
};
} // namespace engine