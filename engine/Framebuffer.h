#pragma once

namespace engine {
class Framebuffer {
public:
    Framebuffer(int width, int height);
    ~Framebuffer();

public:
    virtual void         bind();
    virtual void         unbind();
    virtual unsigned int texture();
    virtual void         bindTexture(int index = 0);

protected:
    unsigned int m_fbo, m_texture, m_rbo;
};
} // namespace engine