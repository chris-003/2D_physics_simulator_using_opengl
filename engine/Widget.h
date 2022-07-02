#pragma once
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include "Framebuffer.h"

namespace engine {
    class Window;

    class Widget {
    public:
        Widget(Window *parent = nullptr, const glm::vec4 &geometry = glm::vec4(0, 0, 0, 0), bool visible = true);
        ~Widget();
    public:
        virtual void render(Framebuffer &fbo);
    public:
        virtual void FramebufferSizeCallback(int width, int height);
        virtual void MouseButtonCallback(int button, int action, int mods);
        virtual void CursorPosCallback(double xpos, double ypos);
        virtual void ScrollCallback(double xoffset, double yoffset);
        virtual void KeyCallback(int key, int scancode, int action, int mods);
    public:
        Window *parent();
        void setParent(Window *parent);
        bool visible();
        void setVisible(bool visible);
        glm::vec4 geometry();
        void setGeometry(const glm::vec4 &geometry);
        glm::vec2 pos();
        void move(const glm::vec2 &pos);
        int x();
        void setX(int x);
        int y();
        void setY(int y);
        glm::vec2 size();
        void resize(const glm::vec2 &size);
        int width();
        void setWidth(int width);
        int height();
        void setHeight(int height);
        glm::vec2 rightBottomPos();
        void setRightBottomPos(const glm::vec2 &pos);
        int rightBottomX();
        void setRightBottomX(int x);
        int rightBottomY();
        void setRightBottomY(int y);
    protected:
        Window *_parent;
        glm::vec4 geo;
        bool _visible;
    };
}
