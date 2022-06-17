#pragma once
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

class Window;

class Widget {
public:
    Widget(Window *parent = nullptr, const glm::vec4 &geometry = glm::vec4(0, 0, 0, 0), bool visible = true);
    ~Widget();
public:
    virtual void render();
    Window *parent();
    void setParent(Window *parent);
    bool visible();
    void setVisible(bool visible);
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
    void setRightBottomPos(const glm::vec2 &size);
    int rightBottomX();
    void setRightBottomX(int rightBottomX);
    int rightBottomY();
    void setRightBottomY(int rightBottomY);
protected:
    Window *_parent;
    glm::vec4 geo;
    bool _visible;
};
