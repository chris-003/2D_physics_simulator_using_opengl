#pragma once
#include "SRenderbuffer.h"
#include "STexture.h"
#include <memory>

namespace engine {
class SFramebuffer {
public:
    // create a framebuffer WITH a texture and a renderbuffer of the default
    // type
    SFramebuffer(int width, int height);
    // create a framebuffer WITH the specific texture and renderbuffer
    // note: the texture or renderbuffer is ignored if the pointer is pointed to
    // null(nullptr)
    SFramebuffer(int width, int height, std::shared_ptr<STexture2D> &texture,
                 std::shared_ptr<SRenderbuffer> &renderbuffer);
    ~SFramebuffer();

public:
    unsigned int         id();
    virtual void         bind();
    virtual void         unbind();
    virtual unsigned int texture();
    virtual void         bindTexture(int index = 0);
    void                 attach(std::shared_ptr<STexture2D> &texture);
    void                 attach(std::shared_ptr<SRenderbuffer> &renderbuffer);

protected:
    unsigned int                   m_fbo;
    std::shared_ptr<STexture2D>    m_texture;
    std::shared_ptr<SRenderbuffer> m_renderbuffer;
};
} // namespace engine