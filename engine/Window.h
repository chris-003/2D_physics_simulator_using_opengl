#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <string>
#include <vector>

namespace engine {
class Application;
class Widget;

class Window {
    friend class Application;

public:
    Window(const glm::vec2   &size  = glm::vec2(800, 600),
           const std::string &title = "Title");
    ~Window();
    void        create(const glm::vec2   &size  = glm::vec2(800, 600),
                       const std::string &title = "Title");
    GLFWwindow *window();

public:
    void      addWidget(Widget *widget);
    void      removeWidget(Widget *widget);
    bool      isWidget(Widget *widget);
    Widget   *focus();
    void      setFocus(Widget *widget);
    glm::vec2 size();

public:
    virtual void FramebufferSizeCallback(int width, int height);
    virtual void MouseButtonCallback(int button, int action, int mods);
    virtual void CursorPosCallback(double xpos, double ypos);
    virtual void ScrollCallback(double xoffset, double yoffset);
    virtual void KeyCallback(int key, int scancode, int action, int mods);

public:
    static Window *map(GLFWwindow *window);

private:
    static void FramebufferSizeCallbackHelper(GLFWwindow *window, int width,
                                              int height);
    static void MouseButtonCallbackHelper(GLFWwindow *window, int button,
                                          int action, int mods);
    static void CursorPosCallbackHelper(GLFWwindow *window, double xpos,
                                        double ypos);
    static void ScrollCallbackHelper(GLFWwindow *window, double xoffset,
                                     double yoffset);
    static void KeyCallbackHelper(GLFWwindow *window, int key, int scancode,
                                  int action, int mods);

public:
    virtual void render();
    // virtual void init();
    void terminate();

protected:
    GLFWwindow           *_window;
    std::vector<Widget *> widgets;
    Widget               *_focus;
    glm::vec2             _size;
};
} // namespace engine