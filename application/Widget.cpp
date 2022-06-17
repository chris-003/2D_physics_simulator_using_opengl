#include "Widget.h"
#include "Window.h"

Widget::Widget(Window *parent, const glm::vec4 &geometry, bool visible) {
    this->_parent = nullptr;
    setParent(parent);
    geo = geometry;
    this->_visible = visible;
}

void Widget::render() {}

Window *Widget::parent() {
    return _parent;
}

void Widget::setParent(Window *parent) {
    if (parent == this->_parent) {
        return;
    }
    // else
    Window *p = this->_parent;
    this->_parent = nullptr;
    if (p != nullptr) {
        p->removeWidget(this);
    }
    this->_parent = parent;
    if (parent != nullptr) {
        parent->addWidget(this);
    }
}

bool Widget::visible() {
    return _visible;
}

void Widget::setVisible(bool visible) {
    _visible = visible;
}

glm::vec2 Widget::pos() {
    return glm::vec2(geo.x, geo.y);
}

void Widget::move(const glm::vec2 &pos) {
    geo.x = pos.x;
    geo.y = pos.y;
}

int Widget::x() {
    return geo.x;
}

void Widget::setX(int x) {
    geo.x = x;
}

int Widget::y() {
    return geo.y;
}

void Widget::setY(int y) {
    geo.y = y;
}

glm::vec2 Widget::size() {
    return glm::vec2(geo.z - geo.x, geo.w - geo.y);
}

void Widget::resize(const glm::vec2 &size) {
    geo.z = geo.x + size.x;
    geo.w = geo.y + size.y;
}

int Widget::width() {
    return geo.z - geo.x;
}

void Widget::setWidth(int width) {
    geo.z = geo.x + width;
}

int Widget::height() {
    return geo.w - geo.y;
}

void Widget::setHeight(int height) {
    geo.w = geo.y + height;
}

glm::vec2 Widget::rightBottomPos() {
    return glm::vec2(geo.z, geo.w);
}

void Widget::setRightBottomPos(const glm::vec2 &size) {
    geo.z = size.x;
    geo.w = size.y;
}

int Widget::rightBottomX() {
    return geo.z;
}

void Widget::setRightBottomX(int rightBottomX) {
    geo.z = rightBottomX;
}

int Widget::rightBottomY() {
    return geo.w;
}

void Widget::setRightBottomY(int rightBottomY) {
    geo.w = rightBottomY;
}
