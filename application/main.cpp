#include "Global.h"
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
