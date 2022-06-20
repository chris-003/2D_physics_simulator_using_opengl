#include "Global.h"
#include "engine/engine.h"
#include "MainWindow.h"

int main() {
    auto &app = engine::Application::getInstance();

    Global::getInstance().stage = Global::Stage::Running;
    MainWindow window;
    window.updateFramebuffer(800, 600);

    app.run();
    
    glfwTerminate();
    return 0;
}
