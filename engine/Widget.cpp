#include "Widget.h"
#include "Window.h"

namespace engine {
    Widget::Widget(Window *parent, const glm::vec4 &geometry, bool visible) {
        this->_parent = nullptr;
        setParent(parent);
        geo = geometry;
        this->_visible = visible;
    }

    Widget::~Widget() {
        parent()->removeWidget(this);
    }

    void Widget::render() {}

    void Widget::FramebufferSizeCallback(int width, int height) {
        glViewport(0, 0, width, height);
    }

    void Widget::MouseButtonCallback(int button, int action, int mods) {}

    void Widget::CursorPosCallback(double xpos, double ypos) {}

    void Widget::ScrollCallback(double xoffset, double yoffset) {}

    void Widget::KeyCallback(int key, int scancode, int action, int mods) {}


    Window *Widget::parent() {
        return _parent;
    }

    void Widget::setParent(Window *parent) {
        if (parent == this->_parent) {
            return;
        }
        // else
        if (parent != nullptr) {
            if (parent->isWidget(this)) {
                return;
            }
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

    glm::vec4 Widget::geometry() {
        return geo;
    }

    void Widget::setGeometry(const glm::vec4 &geometry) {
        if (geo == geometry) {
            return;
        }
        // else
        FramebufferSizeCallback(geometry.z - geometry.x, geometry.w - geometry.y);
        geo = geometry;
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
        if (geo.x == x) {
            return;
        }
        // else
        FramebufferSizeCallback(geo.z - x, geo.w - geo.y);
        geo.x = x;
    }

    int Widget::y() {
        return geo.y;
    }

    void Widget::setY(int y) {
        if (geo.y == y) {
            return;
        }
        // else
        FramebufferSizeCallback(geo.z - geo.x, geo.w - y);
        geo.y = y;
    }

    glm::vec2 Widget::size() {
        return glm::vec2(geo.z - geo.x, geo.w - geo.y);
    }

    void Widget::resize(const glm::vec2 &size) {
        if (this->size() == size) {
            return;
        }
        // else
        FramebufferSizeCallback(size.x, size.y);
        geo.z = geo.x + size.x;
        geo.w = geo.y + size.y;
    }

    int Widget::width() {
        return geo.z - geo.x;
    }

    void Widget::setWidth(int width) {
        if (this->width() == width) {
            return;
        }
        // else
        FramebufferSizeCallback(width, geo.w - geo.y);
        geo.z = geo.x + width;
    }

    int Widget::height() {
        return geo.w - geo.y;
    }

    void Widget::setHeight(int height) {
        if (this->height() == height) {
            return;
        }
        // else
        FramebufferSizeCallback(geo.z - geo.x, height);
        geo.w = geo.y + height;
    }

    glm::vec2 Widget::rightBottomPos() {
        return glm::vec2(geo.z, geo.w);
    }

    void Widget::setRightBottomPos(const glm::vec2 &pos) {
        if (this->rightBottomPos() == pos) {
            return;
        }
        // else
        FramebufferSizeCallback(pos.x - geo.x, pos.y - geo.y);
        geo.z = pos.x;
        geo.w = pos.y;
    }

    int Widget::rightBottomX() {
        return geo.z;
    }

    void Widget::setRightBottomX(int x) {
        if (geo.z == x) {
            return;
        }
        // else
        FramebufferSizeCallback(x - geo.x, geo.w - geo.y);
        geo.z = x;
    }

    int Widget::rightBottomY() {
        return geo.w;
    }

    void Widget::setRightBottomY(int y) {
        if (geo.w == y) {
            return;
        }
        // else
        FramebufferSizeCallback(geo.z - geo.x, y - geo.y);
        geo.w = y;
    }
}
