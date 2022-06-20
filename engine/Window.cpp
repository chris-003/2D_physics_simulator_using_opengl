#include "Window.h"
#include "Application.h"
#include <algorithm>
#include "Widget.h"

namespace engine {
    Window::Window(const glm::vec2 &size, const std::string &title) {
        create(size, title);
        _focus = nullptr;
    }

    Window::~Window() {
        terminate();
    }

    void Window::create(const glm::vec2 &size, const std::string &title) {
        _window = nullptr;
        _window = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
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
        return std::find(widgets.begin(), widgets.end(), widget) == widgets.end();
    }

    Widget *Window::focus() {
        return _focus;
    }

    void Window::setFocus(Widget *widget) {
        if (widget == nullptr) {
            _focus = nullptr;
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

    void Window::FramebufferSizeCallback(int width, int height) {}

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
                    _focus = iter;
                }
            }
        }
    }

    void Window::CursorPosCallback(double xpos, double ypos) {
        glm::vec2 pos(xpos, ypos);
        for (Widget *iter : widgets) {
            if (iter->visible()) {
                auto in = [&xpos, &ypos](const glm::vec4 &geo) -> bool {
                    return geo.x <= xpos && xpos <= geo.z && geo.y <= ypos && ypos <= geo.w;
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

    void Window::FramebufferSizeCallbackHelper(GLFWwindow *window, int width, int height) {
        Window *w = map(window);
        if (w != nullptr) {
            glfwMakeContextCurrent(window);
            w->FramebufferSizeCallback(width, height);
        }
    }

    void Window::MouseButtonCallbackHelper(GLFWwindow *window, int button, int action, int mods) {
        Window *w = map(window);
        if (w != nullptr) {
            glfwMakeContextCurrent(window);
            w->MouseButtonCallback(button, action, mods);
        }
    }

    void Window::CursorPosCallbackHelper(GLFWwindow *window, double xpos, double ypos) {
         Window *w = map(window);
        if (w != nullptr) {
            glfwMakeContextCurrent(window);
            w->CursorPosCallback(xpos, ypos);
        }
    }

    void Window::ScrollCallbackHelper(GLFWwindow *window, double xoffset, double yoffset) {
        Window *w = map(window);
        if (w != nullptr) {
            glfwMakeContextCurrent(window);
            w->ScrollCallback(xoffset, yoffset);
        }
    }

    void Window::KeyCallbackHelper(GLFWwindow *window, int key, int scancode, int action, int mods) {
        Window *w = map(window);
        if (w != nullptr) {
            glfwMakeContextCurrent(window);
            w->KeyCallback(key, scancode, action, mods);
        }
    }

    void Window::render() {
        for (Widget *iter : widgets) {
            if (iter->visible()) {
                iter->render();
            }
        }
    }

    // void Window::init() {}

    void Window::terminate() {
        if (_window != nullptr) {
            auto &app = Application::getInstance();
            app.windowQueue.erase(std::find(app.windowQueue.begin(), app.windowQueue.end(), this));
            glfwDestroyWindow(_window);
            _window = nullptr;
        }
    }
}