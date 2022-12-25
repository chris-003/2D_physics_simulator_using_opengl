#pragma once
#if 0
#include "SBindHelper.h"
#include "SFramebuffer.h"
#include "SObject.h"
#include "SVertexArray.h"
#include "SVertexBuffer.h"
#include "SWidget.h"
#include "SWindow.h"
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
class SButton : public SWidget {
public:
    SButton(SWidget *parent);
    ~SButton();

public:
    void             setColor(unsigned int index, const glm::vec4 &Color);
    const glm::vec4 &color(unsigned int index);

public:
    virtual void render(SFramebuffer &fbo) override;
    virtual void MouseButtonEvent(int x, int y, MouseButton button,
                                  ButtonAction action, Modifier mods,
                                  bool &blocked);

private:
    bool                           pushed;
    glm::vec4                      colors[3];
    std::unique_ptr<SVertexArray>  vao;
    std::unique_ptr<SVertexBuffer> vbo;
};
} // namespace engine
#endif