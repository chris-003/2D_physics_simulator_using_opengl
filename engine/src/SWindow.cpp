#include "SWindow.h"
#include "SApplication.h"
#include "SResourceData.h"
#include "SShaderProgram.h"
#include "SVertexArray.h"
#include "SVertexBuffer.h"
#include "SWidget.h"
#include "SWindowQueue.h"
#include <algorithm>
#include <glm/mat4x4.hpp>
#include <memory>

namespace engine {
SWindow::SWindow() : m_running(false) /*, m_prevIn(false)*/ {
    SApplication::loadOpenGL();
    m_mainWidget = std::make_shared<SWidget>(nullptr);
    // create(size, title);
    // _focus = nullptr;
}

SWindow::~SWindow() {
    if (running()) {
        terminate();
    }
}

void SWindow::create(const glm::ivec2 &size, const std::string &title) {
    if (running()) {
        terminate();
    }
    _size   = size;
    _window = nullptr;
    _window = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
    // auto &app = SApplication::getInstance();
    SWindowQueue::getInstance().push_back(this);
    glfwMakeContextCurrent(_window);
    // app.loadOpenGL();
    glfwSetFramebufferSizeCallback(_window, FramebufferSizeCallbackHelper);
    glfwSetMouseButtonCallback(_window, MouseButtonCallbackHelper);
    glfwSetCursorPosCallback(_window, CursorPosCallbackHelper);
    glfwSetScrollCallback(_window, ScrollCallbackHelper);
    glfwSetKeyCallback(_window, KeyCallbackHelper);

    m_mainWidget = std::make_shared<SWidget>(nullptr);
    m_running    = true;
    m_mainWidget->resize(size);
}

bool SWindow::running() const {
    return m_running;
}

// void SWindow::create(const glm::ivec2 &size, const std::string &title,
//                      std::shared_ptr<SWidget> &mainWidget) {
//     create(size, title);

//     std::shared_ptr<SWidget> widget = mainWidget;
//     if (widget.get() == nullptr) {
//         widget.reset(new SWidget);
//     }
//     else {
//         widget->setParent(nullptr);
//     }
//     m_mainWidget            = widget;
//     m_mainWidget->m_window  = this;
//     m_mainWidget->m_pWindow = &m_mainWidget->m_window;
// }

GLFWwindow *SWindow::window() {
    return _window;
}

// void SWindow::addWidget(SWidget *widget) {
//     if (widget == nullptr) {
//         return;
//     }
//     // else
//     if (isWidget(widget)) {
//         return;
//     }
//     // else
//     widgetTree.addChild(&widget->widgetTree);
//     // widgetTree.push_back(widget);
//     // widget->setParent(this);
// }

// void SWindow::removeWidget(SWidget *widget) {
//     if (widget == nullptr) {
//         return;
//     }
//     // else
//     // auto iter = std::find(widgetTree.begin(), widgetTree.end(), widget);
//     // if (iter != widgetTree.end()) {
//     //     if ((*iter) == _focus) {
//     //         _focus = nullptr;
//     //     }
//     //     widgetTree.erase(iter);
//     //     widget->setParent(nullptr);
//     // }
//     auto pos =
//         std::find(widgetTree.begin(), widgetTree.end(), &widget->widgetTree);
//     if (pos == widgetTree.end()) {
//         return;
//     }
//     // else
//     if (_focus == (*pos)->data()) {
//         _focus = nullptr;
//     }
//     widgetTree.erase(pos);
// }

// bool SWindow::isWidget(SWidget *widget) {
//     return std::find(widgetTree.begin(), widgetTree.end(),
//                      &widget->widgetTree) != widgetTree.end();
// }

// SWidget *SWindow::focus() {
//     return _focus;
// }

// void SWindow::setFocus(SWidget *widget) {
//     if (widget == nullptr) {
//         _focus = nullptr;
//         return;
//     }
//     if (!widget->focusable()) {
//         return;
//     }
//     // else
//     auto iter =
//         std::find(widgetTree.begin(), widgetTree.end(), &widget->widgetTree);
//     if (iter != widgetTree.end()) {
//         if ((*iter)->data() == _focus) {
//             _focus = widget;
//         }
//     }
// }

glm::vec2 SWindow::size() {
    return _size;
}

void SWindow::setMainWidget(std::shared_ptr<SWidget> &widget) {
    if (!running()) {
        create();
    }
    m_mainWidget->m_window     = nullptr;
    std::shared_ptr<SWidget> w = widget;
    if (w.get() == nullptr) {
        w.reset(new SWidget);
    }
    else {
        w->setParent(nullptr);
    }
    m_mainWidget            = w;
    m_mainWidget->m_window  = this;
    m_mainWidget->m_pWindow = &m_mainWidget->m_window;
    widget->resize(size());
}

void SWindow::FramebufferSizeCallback(int width, int height) {
    glViewport(0, 0, width, height);
    m_mainWidget->resize(glm::ivec2(width, height));
}

void SWindow::MouseButtonCallback(int button, int action, int mods) {
    // m_prevIn = true;
    double x, y;
    glfwGetCursorPos(window(), &x, &y);
    glm::vec2 pos(x, y);
    // for (STree<SWidget *> *&i : widgetTree) {
    //     auto &iter = i->data();
    //     if (iter->visible()) {
    //         auto in = [&x, &y](const glm::vec4 &geo) -> bool {
    //             return geo.x <= x && x <= geo.z && geo.y <= y && y <= geo.w;
    //         };
    //         if (in(iter->geometry())) {
    //             iter->MouseButtonCallback(button, action, mods);
    //             // _focus = iter;
    //             try_changeFocus(iter);
    //         }
    //     }
    // }
    bool blocked = true;
    m_mainWidget->private_MouseButtonEvent(
        x, y, glfw2input<MouseButton>(button), glfw2input<ButtonAction>(action),
        Modifier(mods), blocked);
}

void SWindow::CursorPosCallback(double xpos, double ypos) {
    // m_prevIn = true;
    glm::vec2 pos(xpos, ypos);
    // for (STree<SWidget *> *&i : widgetTree) {
    //     auto &iter = i->data();
    //     if (iter->visible()) {
    //         auto in = [&xpos, &ypos](const glm::vec4 &geo) -> bool {
    //             return geo.x <= xpos && xpos <= geo.z && geo.y <= ypos &&
    //                    ypos <= geo.w;
    //         };
    //         if (in(iter->geometry())) {
    //             iter->CursorPosCallback(xpos, ypos);
    //         }
    //     }
    // }
    bool blocked = true;
    m_mainWidget->private_MouseMoveEvent(xpos, ypos, blocked);
}

void SWindow::ScrollCallback(double xoffset, double yoffset) {
    // m_prevIn = true;
    double x, y;
    glfwGetCursorPos(window(), &x, &y);
    glm::vec2 pos(x, y);
    // for (STree<SWidget *> *&i : widgetTree) {
    //     auto &iter = i->data();
    //     if (iter->visible()) {
    //         auto in = [&x, &y](const glm::vec4 &geo) -> bool {
    //             return geo.x <= x && x <= geo.z && geo.y <= y && y <= geo.w;
    //         };
    //         if (in(iter->geometry())) {
    //             iter->ScrollCallback(xoffset, yoffset);
    //         }
    //     }
    // }
    bool blocked = true;
    m_mainWidget->private_MouseScrollEvent(pos.x, pos.y, xoffset, yoffset,
                                           blocked);
}

void SWindow::KeyCallback(int key, int scancode, int action, int mods) {
    // if (_focus != nullptr) {
    //     _focus->KeyCallback(key, scancode, action, mods);
    // }
    bool blocked = true;
    m_mainWidget->private_KeyboardEvent(glfw2input<Key>(key), scancode,
                                        glfw2input<ButtonAction>(action),
                                        Modifier(mods), blocked);
}

SWindow *SWindow::map(GLFWwindow *window) {
    for (SWindow *iter : SWindowQueue::getInstance()) {
        if (iter->_window == window) {
            return iter;
        }
    }
    return nullptr;
}

void SWindow::FramebufferSizeCallbackHelper(GLFWwindow *window, int width,
                                            int height) {
    SWindow *w = map(window);
    if (w != nullptr) {
        glfwMakeContextCurrent(window);
        w->_size = glm::ivec2(width, height);
        w->FramebufferSizeCallback(width, height);
    }
}

void SWindow::MouseButtonCallbackHelper(GLFWwindow *window, int button,
                                        int action, int mods) {
    SWindow *w = map(window);
    if (w != nullptr) {
        glfwMakeContextCurrent(window);
        w->MouseButtonCallback(button, action, mods);
    }
}

void SWindow::CursorPosCallbackHelper(GLFWwindow *window, double xpos,
                                      double ypos) {
    SWindow *w = map(window);
    if (w != nullptr) {
        glfwMakeContextCurrent(window);
        w->CursorPosCallback(xpos, ypos);
    }
}

void SWindow::ScrollCallbackHelper(GLFWwindow *window, double xoffset,
                                   double yoffset) {
    SWindow *w = map(window);
    if (w != nullptr) {
        glfwMakeContextCurrent(window);
        w->ScrollCallback(xoffset, yoffset);
    }
}

void SWindow::KeyCallbackHelper(GLFWwindow *window, int key, int scancode,
                                int action, int mods) {
    SWindow *w = map(window);
    if (w != nullptr) {
        glfwMakeContextCurrent(window);
        w->KeyCallback(key, scancode, action, mods);
    }
}

void SWindow::render() {
    SFramebuffer fbo1(size().x, size().y);
    // SFramebuffer fbo1(800, 600);
    static class Dummy {
    public:
        Dummy() {
            const auto &resource = SResourceData::get_resource("engine");
            program              = new SShaderProgram(
                             SShader(
                                 SShader::Type::Vertex,
                                 SResourceData::get(resource, ":/Shaders/copy.vert").first),
                             SShader(
                                 SShader::Type::Fragment,
                                 SResourceData::get(resource, ":/Shaders/copy.frag").first));
            program->bind();
            vbo = new SVertexBuffer;
            vao = new SVertexArray;
            vao->enable(0, 2, 0);
            vao->bindingPoint(0, 0);
            vao->enable(1, 2, 2 * sizeof(float));
            vao->bindingPoint(1, 0);
            // _vao->bindVBO(0, *vbo, 2 * sizeof(float), 4 * sizeof(float));
            vao->bindVBO(0, *vbo, 0, 4 * sizeof(float));
        }

    public:
        // std::unique_ptr<ShaderProgram> program;
        SShaderProgram *program;
        SVertexBuffer  *vbo;
        SVertexArray   *vao;
    } staticData;
    if (m_mainWidget.get() == nullptr) {
        return;
    }
    // else
    fbo1.bind();
    m_mainWidget->private_fullRender(fbo1);
    {

        struct {
            float x, y, tx, ty;
        } points[4];
        {
            points[0].x  = -1.0f;
            points[0].y  = 1.0f;
            points[0].tx = 0.0f;
            points[0].ty = 1.0f;
            points[1].x  = 1.0f;
            points[1].y  = 1.0f;
            points[1].tx = 1.0f;
            points[1].ty = 1.0f;
            points[2].x  = 1.0f;
            points[2].y  = -1.0f;
            points[2].tx = 1.0f;
            points[2].ty = 0.0f;
            points[3].x  = -1.0f;
            points[3].y  = -1.0f;
            points[3].tx = 0.0f;
            points[3].ty = 0.0f;
        }
        staticData.vbo->write(sizeof(points), points, GL_STATIC_DRAW);
        staticData.program->bind();
        staticData.vao->bind();
        // fbo.bind();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, fbo1.texture());
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
    // for (auto iter = widgetTree.begin(); iter != widgetTree.end(); ++iter) {
    //     if ((*iter)->data()->visible()) {
    //         SFramebuffer fbo((*iter)->data()->size().x,
    //                          (*iter)->data()->size().y);
    //         // SFramebuffer fbo(800, 600);
    //         glm::vec4 points[4];
    //         // calculate the layout from fbo1(screen) to fbo(widget)
    //         {
    //             SWidget  *w    = (*iter)->data();
    //             glm::vec4 geo  = w->geometry();
    //             glm::vec2 size = this->size();
    //             geo /= glm::vec4(size.x, size.y, size.x, size.y);
    //             geo.y     = 1 - geo.y;
    //             geo.w     = 1 - geo.w;
    //             points[0] = {-1, 1, geo.x, geo.y};
    //             points[1] = {1, 1, geo.z, geo.y};
    //             points[2] = {1, -1, geo.z, geo.w};
    //             points[3] = {-1, -1, geo.x, geo.w};
    //             // auto vbo  = make_BindHelper(dummy.vbo);
    //             auto &vbo = dummy.vbo;
    //             vbo->write(sizeof(points), points, GL_STATIC_DRAW);
    //         }
    //         // copy the contents from fbo1(screen) to fbo(widget) (as
    //         // background)
    //         {
    //             fbo.bind();
    //             dummy.program->bind();
    //             // glActiveTexture(GL_TEXTURE0);
    //             // glBindTexture(GL_TEXTURE_2D, fbo1.texture());
    //             fbo1.bindTexture(0);
    //             glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //             auto vao = make_SBindHelper(dummy.vao);
    //             // auto vbo = make_BindHelper(dummy.vbo);
    //             glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    //         }
    //         // actual render process
    //         fbo.bind();
    //         (*iter)->data()->render(fbo);
    //         // calculate the layout from fbo(widget) to fbo1(screen)
    //         {
    //             SWidget  *w    = (*iter)->data();
    //             glm::vec4 geo  = w->geometry();
    //             glm::vec2 size = this->size();
    //             geo /=
    //                 glm::vec4(size.x / 2, size.y / 2, size.x / 2, size.y /
    //                 2);
    //             geo.x -= 1;
    //             geo.y = 1 - geo.y;
    //             geo.z -= 1;
    //             geo.w     = 1 - geo.w;
    //             points[0] = {geo.x, geo.y, 0, 1};
    //             points[1] = {geo.z, geo.y, 1, 1};
    //             points[2] = {geo.z, geo.w, 1, 0};
    //             points[3] = {geo.x, geo.w, 0, 0};
    //             // auto vbo  = make_BindHelper(dummy.vbo);
    //             auto &vbo = dummy.vbo;
    //             vbo->write(sizeof(points), points, GL_STATIC_DRAW);
    //         }
    //         {
    //             fbo1.bind();
    //             dummy.program->bind();
    //             // glActiveTexture(GL_TEXTURE0);
    //             // glBindTexture(GL_TEXTURE_2D, fbo.texture());
    //             fbo.bindTexture(0);
    //             glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //             auto vao = make_SBindHelper(dummy.vao);
    //             // auto vbo = make_BindHelper(dummy.vbo);
    //             glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    //         }
    //         // /////////////////////////////////////////////////////
    //         // {
    //         //     glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //         //     dummy.program->bind();
    //         //     // glActiveTexture(GL_TEXTURE0);
    //         //     // glBindTexture(GL_TEXTURE_2D, fbo.texture());
    //         //     fbo.bindTexture(0);
    //         //     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //         //     auto vao = make_BindHelper(dummy.vao);
    //         //     auto vbo = make_BindHelper(dummy.vbo);
    //         //     glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    //         //     glfwSwapBuffers(window());
    //         //     glfwSwapBuffers(window());
    //         // }
    //     }
    // }
    // {
    //     glm::vec4 points[4] = {
    //         {-1, 1, 0, 1}, {1, 1, 1, 1}, {1, -1, 1, 0}, {-1, -1, 0, 0}};
    //     // auto vbo  = make_BindHelper(dummy.vbo);
    //     auto &vbo = dummy.vbo;
    //     vbo->write(sizeof(points), points, GL_STATIC_DRAW);
    // }
    // {
    //     glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //     dummy.program->bind();
    //     // glActiveTexture(GL_TEXTURE0);
    //     // glBindTexture(GL_TEXTURE_2D, fbo1.texture());
    //     fbo1.bindTexture(0);
    //     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //     auto vao = make_SBindHelper(dummy.vao);
    //     // auto vbo = make_BindHelper(dummy.vbo);
    //     glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    // }
}

// void Window::init() {}

void SWindow::terminate() {
    if (!running()) {
        return;
    }
    // else
    if (_window != nullptr) {
        // auto &app = SApplication::getInstance();
        auto &windowQueue = SWindowQueue::getInstance();
        windowQueue.erase(
            std::find(windowQueue.begin(), windowQueue.end(), this));
        glfwDestroyWindow(_window);
        _window = nullptr;
        if (m_mainWidget.get() != nullptr) {
            m_mainWidget->m_window  = nullptr;
            m_mainWidget->m_pWindow = &m_mainWidget->m_window;
            m_mainWidget            = std::make_shared<SWidget>(nullptr);
        }
    }
    m_running = false;
    // m_prevIn  = false;
}

// void SWindow::try_changeFocus(SWidget *w) {
//     if (w->focusable()) {
//         _focus = w;
//     }
// }
} // namespace engine