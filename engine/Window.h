#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include <glm/vec2.hpp>

namespace engine {
    class Application;

    class Window {
        friend class Application;
    public:
        Window(const glm::vec2 &size = glm::vec2(800, 600), const std::string &title = "Title");
        ~Window();
        void create(const glm::vec2 &size = glm::vec2(800, 600), const std::string &title = "Title");
    public:
        virtual void FramebufferSizeCallback(int width, int height);
        virtual void MouseButtonCallback(int button, int action, int mods);
        virtual void CursorPosCallback(double xpos, double ypos);
        virtual void ScrollCallback(double xoffset, double yoffset);
        virtual void KeyCallback(int key, int scancode, int action, int mods);
    private:
        static void FramebufferSizeCallbackHelper(GLFWwindow *window, int width, int height);
        static void MouseButtonCallbackHelper(GLFWwindow *window, int button, int action, int mods);
        static void CursorPosCallbackHelper(GLFWwindow *window, double xpos, double ypos);
        static void ScrollCallbackHelper(GLFWwindow *window, double xoffset, double yoffset);
        static void KeyCallbackHelper(GLFWwindow *window, int key, int scancode, int action, int mods);
    public:
        virtual void render();
        // virtual void init();
        void terminate();
    protected:
        GLFWwindow *window;
    };
}