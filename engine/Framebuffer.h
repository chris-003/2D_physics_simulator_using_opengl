#pragma once

namespace engine {
    class Framebuffer {
    public:
        Framebuffer(int width, int height);
        ~Framebuffer();
    public:
        void bind();
        void unbind();
        unsigned int texture();
    protected:
        unsigned int m_fbo, m_texture, m_rbo;
    };
}