#include "Window.h"
#include "Application.h"
#include <algorithm>

namespace engine {
    Window::Window(const glm::vec2 &size, const std::string &title) {
        create(size, title);
    }

    Window::~Window() {
        terminate();
    }

    void Window::create(const glm::vec2 &size, const std::string &title) {
        window = nullptr;
        window = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
        auto &app = Application::getInstance();
        app.windowQueue.push_back(this);
        glfwMakeContextCurrent(window);
        app.loadGlad();
        glfwSetFramebufferSizeCallback(window, FramebufferSizeCallbackHelper);
        glfwSetMouseButtonCallback(window, MouseButtonCallbackHelper);
        glfwSetCursorPosCallback(window, CursorPosCallbackHelper);
        glfwSetScrollCallback(window, ScrollCallbackHelper);
        glfwSetKeyCallback(window, KeyCallbackHelper);
    }

    void Window::FramebufferSizeCallback(int width, int height) {}

    void Window::MouseButtonCallback(int button, int action, int mods) {}

    void Window::CursorPosCallback(double xpos, double ypos) {}

    void Window::ScrollCallback(double xoffset, double yoffset) {}

    void Window::KeyCallback(int key, int scancode, int action, int mods) {}

    void Window::FramebufferSizeCallbackHelper(GLFWwindow* window, int width, int height) {
        auto &app = Application::getInstance();
        for (auto iter = app.windowQueue.begin(); iter != app.windowQueue.end(); ++iter) {
            if ((*iter)->window == window) {
                glfwMakeContextCurrent(window);
                (*iter)->FramebufferSizeCallback(width, height);
                return;
            }
        }
    }

    void Window::MouseButtonCallbackHelper(GLFWwindow* window, int button, int action, int mods) {
        auto &app = Application::getInstance();
        for (auto iter = app.windowQueue.begin(); iter != app.windowQueue.end(); ++iter) {
            if ((*iter)->window == window) {
                glfwMakeContextCurrent(window);
                (*iter)->MouseButtonCallback(button, action, mods);
                return;
            }
        }
    }

    void Window::CursorPosCallbackHelper(GLFWwindow* window, double xpos, double ypos) {
        auto &app = Application::getInstance();
        for (auto iter = app.windowQueue.begin(); iter != app.windowQueue.end(); ++iter) {
            if ((*iter)->window == window) {
                glfwMakeContextCurrent(window);
                (*iter)->CursorPosCallback(xpos, ypos);
                return;
            }
        }
    }

    void Window::ScrollCallbackHelper(GLFWwindow* window, double xoffset, double yoffset) {
        auto &app = Application::getInstance();
        for (auto iter = app.windowQueue.begin(); iter != app.windowQueue.end(); ++iter) {
            if ((*iter)->window == window) {
                glfwMakeContextCurrent(window);
                (*iter)->ScrollCallback(xoffset, yoffset);
                return;
            }
        }
    }

    void Window::KeyCallbackHelper(GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto &app = Application::getInstance();
        for (auto iter = app.windowQueue.begin(); iter != app.windowQueue.end(); ++iter) {
            if ((*iter)->window == window) {
                glfwMakeContextCurrent(window);
                (*iter)->KeyCallback(key, scancode, action, mods);
                return;
            }
        }
    }

    void Window::render() {}

    // void Window::init() {}

    void Window::terminate() {
        if (window != nullptr) {
            auto &app = Application::getInstance();
            app.windowQueue.erase(std::find(app.windowQueue.begin(), app.windowQueue.end(), this));
            glfwDestroyWindow(window);
            window = nullptr;
        }
    }
}