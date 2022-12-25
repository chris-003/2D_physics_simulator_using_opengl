#pragma once
#include "SApplication.h"
#include "SWidget.h"
#include "SWindow.h"
#include "SWindowQueue.h"

namespace engine {
template<typename T>
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

    m_mainWidget = std::make_shared<T>(nullptr);
    m_running    = true;
    m_mainWidget->resize(size);
}
} // namespace engine