#include "SWidget.h"
#include "SApplication.h"
#include "SResourceData.h"
#include "SShaderProgram.h"
#include "SVertexArray.h"
#include "SVertexBuffer.h"
#include "SWindow.h"
#include <algorithm>

namespace engine {
SWidget::SWidget(SWidget *parent, const glm::ivec4 &geometry, bool visible,
                 bool focusable)
/*: m_prevIn(false)*/ {
    SApplication::loadOpenGL();

    // this->_parent = nullptr;
    // setParent(parent);

    // connect<int, int>(Signals::Move, [this](int x, int y) {
    //     this->private_MoveSlot(x, y);
    // });
    // connect<int, int>(Signals::Size, [this](int width, int height) {
    //     this->private_SizeSlot(width, height);
    // });
    // connect<int, int>(Signals::MouseMove, [this](int x, int y) {
    //     this->private_MouseMoveEvent(x, y);
    // });
    // connect<int, int>(Signals::MouseButton, [this]())

    geo            = geometry;
    this->_visible = visible;
    // this->_focusable = focusable;
    widgetTree.setData(this);
    if (parent == nullptr) {
        m_window  = nullptr;
        m_pWindow = &m_window;
        widgetTree.setParent(nullptr);
    }
    else {
        m_window  = nullptr;
        m_pWindow = parent->m_pWindow;
        widgetTree.setParent(&parent->widgetTree);
    }
}

// SWidget::SWidget(SWindow *parent, const glm::ivec4 &geometry, bool visible,
//                  bool focusable) {
//     geo            = geometry;
//     this->_visible = visible;
//     // this->_focusable = focusable;

//     if (parent == nullptr) {
//         m_window  = nullptr;
//         m_pWindow = &m_window;
//         widgetTree.setParent(nullptr);
//     }
//     else {
//         m_window  = parent;
//         m_pWindow = &m_window;
//         widgetTree.setParent(&parent->widgetTree);
//     }
// }

SWidget::~SWidget() {
    // parent()->removeWidget(this);
}

void SWidget::render(SFramebuffer &fbo) {
}

// bool SWidget::containMouse() {
//     double   x, y;
//     SWindow *window = nullptr;
//     if (m_window == nullptr) {
//         window = *m_pWindow;
//     }
//     else {
//         window = m_window;
//     }

//     if (window = nullptr) {
//         return false;
//     }
//     else {
//         glfwGetCursorPos(window->window(), &x, &y);
//         return geo.x <= x && x <= geo.z && geo.y <= y && y <= geo.w;
//     }
// }

void SWidget::MouseMoveEvent(int x, int y, bool &blocked) {
}

void SWidget::MouseButtonEvent(int x, int y, MouseButton button,
                               ButtonAction action, Modifier mods,
                               bool &blocked) {
}

void SWidget::MouseScrollEvent(int x, int y, double xoffset, double yoffset,
                               bool &blocked) {
}

void SWidget::KeyboardEvent(Key key, int scancode, ButtonAction action,
                            Modifier mods, bool &blocked) {
}

void SWidget::ParentMoveEvent(int dx, int dy) {
}

SWindow *SWidget::window() {
    return *m_pWindow;
}
const SWindow *SWidget::window() const {
    return *m_pWindow;
}

SWidget *SWidget::parent() const {
    return widgetTree.parent()->data();
}

void SWidget::setParent(SWidget *parent) {
    if (parent == nullptr) {
        widgetTree.setParent(nullptr);
        m_window  = nullptr;
        m_pWindow = &m_window;
    }
    else {
        widgetTree.setParent(&parent->widgetTree);
        m_window  = nullptr;
        m_pWindow = parent->m_pWindow;
    }
}

// void SWidget::attachTo(SWindow *window) {
//     // if (window = nullptr) {
//     //     widgetTree.setParent(nullptr);
//     //     m_window  = nullptr;
//     //     m_pWindow = &m_window;
//     // }
//     // else {
//     //     widgetTree.setParent(&window->widgetTree);
//     //     m_window  = window;
//     //     m_pWindow = &m_window;
//     // }
//     setParent(window->mainWidget);
// }
// void SWidget::setParent(SWindow *parent) {
//     if (parent == this->_parent) {
//         return;
//     }
//     // else
//     if (parent != nullptr) {
//         if (parent->isWidget(this)) {
//             return;
//         }
//     }
//     // else
//     SWindow *p    = this->_parent;
//     this->_parent = nullptr;
//     if (p != nullptr) {
//         p->removeWidget(this);
//     }
//     this->_parent = parent;
//     if (parent != nullptr) {
//         parent->addWidget(this);
//     }
// }

glm::ivec2 SWidget::local2absolute(const glm::ivec2 &pos) const {
    return pos + absolutePos;
}

glm::ivec2 SWidget::absolute2local(const glm::ivec2 &pos) const {
    return pos - absolutePos;
}

glm::ivec2 SWidget::GetLocalMousePos() const {
    if (*m_pWindow != nullptr) {
        return absolute2local(GetAbsoluteMousePos());
    }
    return glm::ivec2(0, 0);
}

glm::ivec2 SWidget::GetAbsoluteMousePos() const {
    glm::ivec2 pos(0, 0);
    if (*m_pWindow != nullptr) {
        double x, y;
        glfwGetCursorPos((*m_pWindow)->window(), &x, &y);
        pos.x = x;
        pos.y = y;
    }
    return pos;
}

bool SWidget::visible() const {
    return _visible;
}

void SWidget::setVisible(bool visible) {
    _visible = visible;
}

// bool SWidget::focusable() const {
//     return _focusable;
// }

// void SWidget::setFocusable(bool focusable) {
//     _focusable = focusable;
// }

glm::ivec4 SWidget::geometry() const {
    return geo;
}

void SWidget::setGeometry(const glm::ivec4 &geometry) {
    if (geo == geometry) {
        return;
    }
    // else
    auto prev = geo;
    geo.x     = geometry.x;
    geo.y     = geometry.y;
    geo.z     = std::max(geo.x, geometry.z);
    geo.w     = std::max(geo.y, geometry.w);
    if (!(prev.z - prev.x == geo.z - geo.x &&
          prev.w - prev.y == geo.w - geo.y)) {
        emit<int, int>(Signals::Size, geo.z - geo.x, geo.w - geo.y);
    }
    if (!(prev.x == geo.x && prev.y == geo.y)) {
        emit<int, int>(Signals::Move, geo.x, geo.y);
    }
    int dx = geo.x - prev.x;
    int dy = geo.y - prev.y;
    absolutePos.x += dx;
    absolutePos.y += dy;
    private_emit_PrarentMoveEvent(dx, dy);
    // FramebufferSizeCallback(geometry.z - geometry.x, geometry.w -
    // geometry.y);
}

glm::ivec2 SWidget::pos() const {
    return glm::vec2(geo.x, geo.y);
}

void SWidget::move(const glm::ivec2 &pos) {
    // geo.x = pos.x + geo.z - geo.x;
    // geo.x = pos.x;
    // geo.w = pos.y + geo.w - geo.y;
    // geo.y = pos.y;
    int dx = pos.x - geo.x;
    int dy = pos.y - geo.y;
    geo.z += dx;
    geo.w += dy;
    geo.x = pos.x;
    geo.y = pos.y;
    emit<int, int>(Signals::Move, geo.x, geo.y);
    absolutePos.x += dx;
    absolutePos.y += dy;
    private_emit_PrarentMoveEvent(dx, dy);
}

int SWidget::x() const {
    return geo.x;
}

void SWidget::setX(int x) {
    if (geo.x == x) {
        return;
    }
    // else
    int dx = x - geo.x;
    geo.z += dx;
    geo.x = x;
    emit<int, int>(Signals::Move, geo.x, geo.y);
    private_emit_PrarentMoveEvent(dx, 0);
    // FramebufferSizeCallback(geo.z - x, geo.w - geo.y);
}

int SWidget::y() const {
    return geo.y;
}

void SWidget::setY(int y) {
    if (geo.y == y) {
        return;
    }
    // else
    int dy = y - geo.y;
    geo.w += dy;
    geo.y = y;
    emit<int, int>(Signals::Move, geo.x, geo.y);
    private_emit_PrarentMoveEvent(0, dy);
    // geo.y = y;
    // FramebufferSizeCallback(geo.z - geo.x, geo.w - y);
}

glm::ivec2 SWidget::size() const {
    return glm::vec2(geo.z - geo.x, geo.w - geo.y);
}

void SWidget::resize(const glm::ivec2 &size) {
    if (this->size() == size) {
        return;
    }
    // else
    geo.z = geo.x + std::max(0, size.x);
    geo.w = geo.y + std::max(0, size.y);
    emit<int, int>(Signals::Size, geo.z - geo.x, geo.w - geo.y);
}

int SWidget::width() const {
    return geo.z - geo.x;
}

void SWidget::setWidth(int width) {
    if (this->width() == width) {
        return;
    }
    // else
    geo.z = geo.x + std::max(0, width);
    emit<int, int>(Signals::Size, geo.z - geo.x, geo.w - geo.y);
    // geo.z = geo.x + width;
}

int SWidget::height() const {
    return geo.w - geo.y;
}

void SWidget::setHeight(int height) {
    if (this->height() == height) {
        return;
    }
    // else
    geo.w = geo.y + std::max(0, height);
    emit<int, int>(Signals::Size, geo.z - geo.x, geo.w - geo.y);
    // geo.w = geo.y + height;
}

glm::ivec2 SWidget::rightBottomPos() const {
    return glm::vec2(geo.z, geo.w);
}

void SWidget::setRightBottomPos(const glm::ivec2 &pos) {
    if (this->rightBottomPos() == pos) {
        return;
    }
    // else
    // FramebufferSizeCallback(pos.x - geo.x, pos.y - geo.y);
    // geo.z = pos.x;
    // geo.w = pos.y;
    geo.z = std::max(pos.x, geo.x);
    geo.w = std::max(pos.y, geo.y);
    emit<int, int>(Signals::Size, geo.z - geo.x, geo.w - geo.y);
}

int SWidget::rightBottomX() const {
    return geo.z;
}

void SWidget::setRightBottomX(int x) {
    if (geo.z == x) {
        return;
    }
    // else
    // FramebufferSizeCallback(x - geo.x, geo.w - geo.y);
    // geo.z = x;
    // if (geo.x <= x) {
    //     geo.z = geo.x;
    // }
    // else {
    //     geo.z = x;
    // }
    geo.z = std::max(x, geo.x);
    emit<int, int>(Signals::Size, geo.z - geo.x, geo.w - geo.y);
}

int SWidget::rightBottomY() const {
    return geo.w;
}

void SWidget::setRightBottomY(int y) {
    if (geo.w == y) {
        return;
    }
    // else
    // if (y <= geo.y) {
    //     geo.w = geo.y;
    // }
    // else {
    //     geo.w = y;
    // }
    geo.w = std::max(y, geo.y);
    emit<int, int>(Signals::Size, geo.z - geo.x, geo.w - geo.y);
    // #error ""
    // private_FramebufferSizeCallback(geo.z - geo.x, y - geo.y);
}

void SWidget::private_MouseMoveEvent(int x, int y, bool &blocked) {
    auto in = [](const glm::ivec2 &pos, const glm::ivec4 geo) -> bool {
        return geo.x <= pos.x && pos.x <= geo.z && geo.y <= pos.y &&
               pos.y <= geo.y;
    };
    bool       block = true;
    glm::ivec2 local(x, y);
    for (auto i : widgetTree) {
        SWidget *w = i->data();
        if (in(local, w->geometry())) {
            // if (!w->m_prevIn) {
            //     w->emit<>(Signals::MouseIn);
            //     w->m_prevIn = true;
            // }
            glm::ivec2 childlocal = local - w->pos();
            w->private_MouseMoveEvent(childlocal.x, childlocal.y, block);
            if (block) {
                break;
            }
        }
        // else if (w->m_prevIn) {
        //     w->emit<>(Signals::MouseOut);
        //     w->m_prevIn = false;
        // }
    }
    if (!block) {
        this->MouseMoveEvent(x, y, blocked);
        emit<int, int>(Signals::MouseMove, x, y);
    }
}
void SWidget::private_MouseButtonEvent(int x, int y, MouseButton button,
                                       ButtonAction action, Modifier mods,
                                       bool &blocked) {
    auto in = [](const glm::ivec2 &pos, const glm::ivec4 geo) -> bool {
        return geo.x <= pos.x && pos.x <= geo.z && geo.y <= pos.y &&
               pos.y <= geo.y;
    };
    bool       block = true;
    glm::ivec2 local(x, y);
    for (auto i : widgetTree) {
        SWidget *w = i->data();
        if (in(local, w->geometry())) {
            glm::ivec2 childlocal = local - w->pos();
            w->private_MouseButtonEvent(childlocal.x, childlocal.y, button,
                                        action, mods, block);
            if (block) {
                break;
            }
        }
    }
    if (!block) {
        this->MouseButtonEvent(x, y, button, action, mods, blocked);
        emit<int, int, MouseButton, ButtonAction, Modifier>(
            Signals::MouseButton, x, y, button, action, mods);
    }
}

void SWidget::private_MouseScrollEvent(int x, int y, double xoffset,
                                       double yoffset, bool &blocked) {
    auto in = [](const glm::ivec2 &pos, const glm::ivec4 geo) -> bool {
        return geo.x <= pos.x && pos.x <= geo.z && geo.y <= pos.y &&
               pos.y <= geo.y;
    };
    bool       block = true;
    glm::ivec2 local(x, y);
    for (auto i : widgetTree) {
        SWidget *w = i->data();
        if (in(local, w->geometry())) {
            glm::ivec2 childlocal = local - w->pos();
            w->private_MouseScrollEvent(childlocal.x, childlocal.y, xoffset,
                                        yoffset, block);
            if (block) {
                break;
            }
        }
    }
    if (!block) {
        this->MouseScrollEvent(x, y, xoffset, yoffset, blocked);
        emit<int, int, double, double>(Signals::MouseScroll, x, y, xoffset,
                                       yoffset);
    }
}

void SWidget::private_KeyboardEvent(Key key, int scancode, ButtonAction action,
                                    Modifier mods, bool &blocked) {
    bool block = true;
    for (auto i : widgetTree) {
        SWidget *w = i->data();
        w->KeyboardEvent(key, scancode, action, mods, block);
        if (block) {
            break;
        }
    }
    if (!block) {
        this->KeyboardEvent(key, scancode, action, mods, blocked);
    }
}

void SWidget::private_ParentMoveEvent(int dx, int dy) {
    absolutePos += glm::vec2(dx, dy);
    private_emit_PrarentMoveEvent(dx, dy);
    emit<int, int>(Signals::ParentMove, dx, dy);
}

void SWidget::private_emit_PrarentMoveEvent(int dx, int dy) {
    for (auto &i : widgetTree) {
        SWidget *w = i->data();
        w->private_ParentMoveEvent(dx, dy);
    }
}

void SWidget::private_fullRender(SFramebuffer &fbo) {
    static class StaticData {
    public:
        StaticData(SWidget *_this) {
            width    = _this->width();
            height   = _this->height();
            resource = SResourceData::get_resource("engine");
            program  = new SShaderProgram(
                 SShader(
                     SShader::Type::Vertex,
                     SResourceData::get(resource, ":/Shaders/copy.vert").first),
                 SShader(
                     SShader::Type::Fragment,
                     SResourceData::get(resource, ":/Shaders/copy.frag").first));
            vao = new SVertexArray;
            vbo = new SVertexBuffer;

            vao->bindingPoint(0, 0);
            vao->enable(0, 2, 0);
            vao->enable(1, 2, 2 * sizeof(float));
            vao->bindingPoint(1, 0);
            vao->bindVBO(0, *vbo, 0, 4 * sizeof(float));
        }
        ~StaticData() {
            delete vbo;
            delete vao;
            delete program;
        }
        int                       width, height;
        SVertexArray             *vao;
        SVertexBuffer            *vbo;
        SShaderProgram           *program;
        SResourceData::resource_t resource;
    } staticData(this);
    int  width  = this->width();
    int  height = this->height();
    auto toVertexPosition =
        [&width, &height](const glm::ivec2 &pos) -> std::tuple<float, float> {
        float x = pos.x, y = pos.y;
        x = x * 2.0f / width - 1.0f;
        y = 1.0f - y * 2.0f / height;
        return std::make_tuple(x, y);
    };
    auto toTexCoord =
        [&width, &height](const glm::ivec2 &pos) -> std::tuple<float, float> {
        float x = pos.x, y = pos.y;
        x = x / width;
        y = 1.0f - y / height;
        return std::make_tuple(x, y);
    };
    auto copyBackground2Child =
        [&fbo, &width, &height, &toVertexPosition, &toTexCoord](
            SFramebuffer &childFbo, const glm::ivec4 &childGeo) -> void {
        struct {
            float x, y, tx, ty;
        } points[4];
        {
            points[0].x = -1.0f;
            points[0].y = 1.0f;
            std::tie(points[0].tx, points[0].ty) =
                toTexCoord(glm::ivec2(childGeo.x, childGeo.y));
            points[1].x = 1.0f;
            points[1].y = 1.0f;
            std::tie(points[1].tx, points[1].ty) =
                toTexCoord(glm::ivec2(childGeo.z, childGeo.y));
            points[2].x = 1.0f;
            points[2].y = -1.0f;
            std::tie(points[2].tx, points[2].ty) =
                toTexCoord(glm::ivec2(childGeo.z, childGeo.w));
            points[3].x = -1.0f;
            points[3].y = -1.0f;
            std::tie(points[3].tx, points[3].ty) =
                toTexCoord(glm::ivec2(childGeo.x, childGeo.w));
        }
        staticData.vbo->write(sizeof(points), points, GL_STATIC_DRAW);
        staticData.program->bind();
        staticData.vao->bind();
        childFbo.bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, fbo.texture());
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    };
    auto copyChild2Background =
        [&fbo, &width, &height, &toVertexPosition, &toTexCoord](
            SFramebuffer &childFbo, const glm::ivec4 &childGeo) -> void {
        struct {
            float x, y, tx, ty;
        } points[4];
        {
            std::tie(points[0].x, points[0].y) =
                toVertexPosition(glm::ivec2(childGeo.x, childGeo.y));
            points[0].tx = 0.0f;
            points[0].ty = 1.0f;
            std::tie(points[1].x, points[1].y) =
                toVertexPosition(glm::ivec2(childGeo.z, childGeo.y));
            points[0].tx = 1.0f;
            points[0].ty = 1.0f;
            std::tie(points[2].x, points[2].y) =
                toVertexPosition(glm::ivec2(childGeo.z, childGeo.w));
            points[0].tx = 1.0f;
            points[0].ty = 0.0f;
            std::tie(points[0].x, points[0].y) =
                toVertexPosition(glm::ivec2(childGeo.x, childGeo.w));
            points[0].tx = 0.0f;
            points[0].ty = 0.0f;
        }
        staticData.vbo->write(sizeof(points), points, GL_STATIC_DRAW);
        staticData.program->bind();
        staticData.vao->bind();
        fbo.bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, childFbo.texture());
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    };
    fbo.bind();
    this->render(fbo);
    for (auto i : widgetTree) {
        SWidget *w = i->data();
        if (w->visible()) {
            SFramebuffer childFbo(w->width(), w->height());
            copyBackground2Child(childFbo, w->geometry());
            childFbo.bind();
            w->render(childFbo);
            copyChild2Background(childFbo, w->geometry());
        }
    }
}

} // namespace engine
