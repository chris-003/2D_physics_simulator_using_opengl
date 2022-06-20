#include "Application.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Window.h"

namespace engine {
    Application::Application() : gladLoaded(false) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void Application::loadGlad() {
        if (!gladLoaded) {
            gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            gladLoaded = true;
        }
    }

    Application::~Application() {}

    Application &Application::getInstance() {
        static Application instance;
        return instance;
    }

    void Application::run() {
        while (!windowQueue.empty()) {
            for (auto iter = windowQueue.begin(); iter != windowQueue.end(); ++iter) {
                if (glfwWindowShouldClose((*iter)->window())) {
                    (*iter)->terminate();
                    --iter;
                }
                else {
                    glfwMakeContextCurrent((*iter)->window());
                    (*iter)->render();
                    glfwSwapBuffers((*iter)->window());
                }
            }
            glfwWaitEvents();
        }
    }

    void Application::windowHint(int hint, int value) {
        glfwWindowHint(hint, value);
    }
}