#include "Window.h"
#include "Application.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Widget.h"
#include <algorithm>
#include <glm/mat4x4.hpp>
#include <memory>

namespace engine {
Window::Window(const glm::vec2 &size, const std::string &title) {
    create(size, title);
    _focus = nullptr;
}

Window::~Window() {
    terminate();
}

void Window::create(const glm::vec2 &size, const std::string &title) {
    _size     = size;
    _window   = nullptr;
    _window   = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
    auto &app = Application::getInstance();
    app.windowQueue.push_back(this);
    glfwMakeContextCurrent(_window);
    app.loadGlad();
    glfwSetFramebufferSizeCallback(_window, FramebufferSizeCallbackHelper);
    glfwSetMouseButtonCallback(_window, MouseButtonCallbackHelper);
    glfwSetCursorPosCallback(_window, CursorPosCallbackHelper);
    glfwSetScrollCallback(_window, ScrollCallbackHelper);
    glfwSetKeyCallback(_window, KeyCallbackHelper);
}

GLFWwindow *Window::window() {
    return _window;
}

void Window::addWidget(Widget *widget) {
    if (widget == nullptr) {
        return;
    }
    // else
    if (isWidget(widget)) {
        return;
    }
    // else
    widgets.push_back(widget);
    widget->setParent(this);
}
void Window::removeWidget(Widget *widget) {
    if (widget == nullptr) {
        return;
    }
    // else
    auto iter = std::find(widgets.begin(), widgets.end(), widget);
    if (iter != widgets.end()) {
        if ((*iter) == _focus) {
            _focus = nullptr;
        }
        widgets.erase(iter);
        widget->setParent(nullptr);
    }
}

bool Window::isWidget(Widget *widget) {
    return std::find(widgets.begin(), widgets.end(), widget) != widgets.end();
}

Widget *Window::focus() {
    return _focus;
}

void Window::setFocus(Widget *widget) {
    if (widget == nullptr) {
        _focus = nullptr;
        return;
    }
    if (!widget->focusable()) {
        return;
    }
    // else
    auto iter = std::find(widgets.begin(), widgets.end(), widget);
    if (iter != widgets.end()) {
        if ((*iter) == _focus) {
            _focus = widget;
        }
    }
}

glm::vec2 Window::size() {
    return _size;
}

void Window::FramebufferSizeCallback(int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::MouseButtonCallback(int button, int action, int mods) {
    double x, y;
    glfwGetCursorPos(window(), &x, &y);
    glm::vec2 pos(x, y);
    for (Widget *iter : widgets) {
        if (iter->visible()) {
            auto in = [&x, &y](const glm::vec4 &geo) -> bool {
                return geo.x <= x && x <= geo.z && geo.y <= y && y <= geo.w;
            };
            if (in(iter->geometry())) {
                iter->MouseButtonCallback(button, action, mods);
                // _focus = iter;
                try_changeFocus(iter);
            }
        }
    }
}

void Window::CursorPosCallback(double xpos, double ypos) {
    glm::vec2 pos(xpos, ypos);
    for (Widget *iter : widgets) {
        if (iter->visible()) {
            auto in = [&xpos, &ypos](const glm::vec4 &geo) -> bool {
                return geo.x <= xpos && xpos <= geo.z && geo.y <= ypos &&
                       ypos <= geo.w;
            };
            if (in(iter->geometry())) {
                iter->CursorPosCallback(xpos, ypos);
            }
        }
    }
}

void Window::ScrollCallback(double xoffset, double yoffset) {
    double x, y;
    glfwGetCursorPos(window(), &x, &y);
    glm::vec2 pos(x, y);
    for (Widget *iter : widgets) {
        if (iter->visible()) {
            auto in = [&x, &y](const glm::vec4 &geo) -> bool {
                return geo.x <= x && x <= geo.z && geo.y <= y && y <= geo.w;
            };
            if (in(iter->geometry())) {
                iter->ScrollCallback(xoffset, yoffset);
            }
        }
    }
}

void Window::KeyCallback(int key, int scancode, int action, int mods) {
    if (_focus != nullptr) {
        _focus->KeyCallback(key, scancode, action, mods);
    }
}

Window *Window::map(GLFWwindow *window) {
    auto &app = Application::getInstance();
    for (Window *iter : app.windowQueue) {
        if (iter->_window == window) {
            return iter;
        }
    }
    return nullptr;
}

void Window::FramebufferSizeCallbackHelper(GLFWwindow *window, int width,
                                           int height) {
    Window *w = map(window);
    if (w != nullptr) {
        glfwMakeContextCurrent(window);
        w->_size = glm::vec2(width, height);
        w->FramebufferSizeCallback(width, height);
    }
}

void Window::MouseButtonCallbackHelper(GLFWwindow *window, int button,
                                       int action, int mods) {
    Window *w = map(window);
    if (w != nullptr) {
        glfwMakeContextCurrent(window);
        w->MouseButtonCallback(button, action, mods);
    }
}

void Window::CursorPosCallbackHelper(GLFWwindow *window, double xpos,
                                     double ypos) {
    Window *w = map(window);
    if (w != nullptr) {
        glfwMakeContextCurrent(window);
        w->CursorPosCallback(xpos, ypos);
    }
}

void Window::ScrollCallbackHelper(GLFWwindow *window, double xoffset,
                                  double yoffset) {
    Window *w = map(window);
    if (w != nullptr) {
        glfwMakeContextCurrent(window);
        w->ScrollCallback(xoffset, yoffset);
    }
}

void Window::KeyCallbackHelper(GLFWwindow *window, int key, int scancode,
                               int action, int mods) {
    Window *w = map(window);
    if (w != nullptr) {
        glfwMakeContextCurrent(window);
        w->KeyCallback(key, scancode, action, mods);
    }
}

void Window::render() {
    // Framebuffer fbo1(size().x, size().y);
    Framebuffer fbo1(800, 600);
    static class Dummy {
    public:
        Dummy() {
            program.reset(new ShaderProgram(
                R"(#version 440 core
layout (location = 0) in vec2 VerexPosition;
layout (location = 1) in vec2 TexCoord;

out vec2 texCoord;

void main()
{
    gl_Position = vec4(VerexPosition, 0, 1);
    texCoord = TexCoord;
})",
                R"(#version 440 core
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D inTexture;

void main() {
    FragColor = texture(inTexture, texCoord);
})"));
            program->bind();
            vbo.reset(new VertexBuffer);
            vao.reset(new VertexArray);
            auto _vao = make_BindHelper(vao);
            auto _vbo = make_BindHelper(vbo);
            _vao->enable(0, 2, 0);
            _vao->bindingPoint(0, 0);
            _vao->enable(1, 2, 2 * sizeof(float));
            _vao->bindingPoint(1, 0);
            // _vao->bindVBO(0, *vbo, 2 * sizeof(float), 4 * sizeof(float));
            _vao->bindVBO(0, *vbo, 0, 4 * sizeof(float));
        }

    public:
        std::unique_ptr<ShaderProgram> program;
        std::unique_ptr<VertexBuffer>  vbo;
        std::unique_ptr<VertexArray>   vao;
    } dummy;
    for (auto iter = widgets.begin(); iter != widgets.end(); ++iter) {
        if ((*iter)->visible()) {
            // Framebuffer fbo(size().x, size().y);
            Framebuffer fbo(800, 600);
            glm::vec4   points[4];
            // calculate the layout from fbo1(screen) to fbo(widget)
            {
                Widget   *w    = *iter;
                glm::vec4 geo  = w->geometry();
                glm::vec2 size = this->size();
                geo /= glm::vec4(size.x, size.y, size.x, size.y);
                geo.y     = 1 - geo.y;
                geo.w     = 1 - geo.w;
                points[0] = {-1, 1, geo.x, geo.y};
                points[1] = {1, 1, geo.z, geo.y};
                points[2] = {1, -1, geo.z, geo.w};
                points[3] = {-1, -1, geo.x, geo.w};
                // auto vbo  = make_BindHelper(dummy.vbo);
                auto &vbo = dummy.vbo;
                vbo->write(sizeof(points), points, GL_STATIC_DRAW);
            }
            // copy the contents from fbo1(screen) to fbo(widget) (as
            // background)
            {
                fbo.bind();
                dummy.program->bind();
                // glActiveTexture(GL_TEXTURE0);
                // glBindTexture(GL_TEXTURE_2D, fbo1.texture());
                fbo1.bindTexture(0);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                auto vao = make_BindHelper(dummy.vao);
                // auto vbo = make_BindHelper(dummy.vbo);
                glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            }
            // actual render process
            fbo.bind();
            (*iter)->render(fbo);
            // calculate the layout from fbo(widget) to fbo1(screen)
            {
                Widget   *w    = *iter;
                glm::vec4 geo  = w->geometry();
                glm::vec2 size = this->size();
                geo /=
                    glm::vec4(size.x / 2, size.y / 2, size.x / 2, size.y / 2);
                geo.x -= 1;
                geo.y = 1 - geo.y;
                geo.z -= 1;
                geo.w     = 1 - geo.w;
                points[0] = {geo.x, geo.y, 0, 1};
                points[1] = {geo.z, geo.y, 1, 1};
                points[2] = {geo.z, geo.w, 1, 0};
                points[3] = {geo.x, geo.w, 0, 0};
                // auto vbo  = make_BindHelper(dummy.vbo);
                auto &vbo = dummy.vbo;
                vbo->write(sizeof(points), points, GL_STATIC_DRAW);
            }
            {
                fbo1.bind();
                dummy.program->bind();
                // glActiveTexture(GL_TEXTURE0);
                // glBindTexture(GL_TEXTURE_2D, fbo.texture());
                fbo.bindTexture(0);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                auto vao = make_BindHelper(dummy.vao);
                // auto vbo = make_BindHelper(dummy.vbo);
                glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            }
            // /////////////////////////////////////////////////////
            // {
            //     glBindFramebuffer(GL_FRAMEBUFFER, 0);
            //     dummy.program->bind();
            //     // glActiveTexture(GL_TEXTURE0);
            //     // glBindTexture(GL_TEXTURE_2D, fbo.texture());
            //     fbo.bindTexture(0);
            //     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            //     auto vao = make_BindHelper(dummy.vao);
            //     auto vbo = make_BindHelper(dummy.vbo);
            //     glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            //     glfwSwapBuffers(window());
            //     glfwSwapBuffers(window());
            // }
        }
    }
    {
        glm::vec4 points[4] = {
            {-1, 1, 0, 1}, {1, 1, 1, 1}, {1, -1, 1, 0}, {-1, -1, 0, 0}};
        // auto vbo  = make_BindHelper(dummy.vbo);
        auto &vbo = dummy.vbo;
        vbo->write(sizeof(points), points, GL_STATIC_DRAW);
    }
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        dummy.program->bind();
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, fbo1.texture());
        fbo1.bindTexture(0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        auto vao = make_BindHelper(dummy.vao);
        // auto vbo = make_BindHelper(dummy.vbo);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
}

// void Window::init() {}

void Window::terminate() {
    if (_window != nullptr) {
        auto &app = Application::getInstance();
        app.windowQueue.erase(
            std::find(app.windowQueue.begin(), app.windowQueue.end(), this));
        glfwDestroyWindow(_window);
        _window = nullptr;
    }
}

void Window::try_changeFocus(Widget *w) {
    if (w->focusable()) {
        _focus = w;
    }
}
} // namespace engine