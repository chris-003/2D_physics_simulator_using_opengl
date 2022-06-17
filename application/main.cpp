#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Resource.h"
// #include "Render.h"
#include <glm/vec2.hpp>
#include "Global.h"
#include <iostream>
#include <boost/interprocess/ipc/message_queue.hpp>
#include "engine/engine.h"
#include "Window.h"

int main() {
    auto &app = engine::Application::getInstance();

    Global::getInstance().stage = Global::Stage::Running;
    Window window;
    window.updateFramebuffer(800, 600);

    app.run();
    glfwTerminate();
    return 0;
}
