#pragma once

namespace engine {
class VertexArray {
public:
    VertexArray();
    ~VertexArray();
    void bind();
    void unbind();

protected:
    unsigned m_vao;
};
} // namespace engine