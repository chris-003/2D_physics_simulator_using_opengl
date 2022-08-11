#pragma once
#include "BindHelper.h"
#include "Framebuffer.h"
#include "Object.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Widget.h"
#include "Window.h"
#include <glm/vec4.hpp>
#include <memory>

namespace engine {
// class Button
//     Signal(0): emited when it was clicked
//            void slot();
//     Signal(1): emited when mouse button left was pushed
//            void slot();
//     Signal(2): emited when mouse button left was released
//            void slot();
//     Color:  0 -> when mouse was NOT on it
//     Color:  1 -> when mouse was on it
//     Color:  2 -> when mouse button left was pushed
class Button : public Widget, public Object {
public:
    Button(Window *parent);
    ~Button();

public:
    void             setColor(unsigned int index, const glm::vec4 &Color);
    const glm::vec4 &color(unsigned int index);

public:
    virtual void render(Framebuffer &fbo) override;
    virtual void MouseButtonCallback(int button, int action, int mods) override;

private:
    bool                          pushed;
    glm::vec4                     colors[3];
    std::unique_ptr<VertexArray>  vao;
    std::unique_ptr<VertexBuffer> vbo;
};
} // namespace engine