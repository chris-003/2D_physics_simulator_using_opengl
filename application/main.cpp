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

// bool LBDown, RBDown;
// glm::vec2 prevMousePos;
// glm::mat4x4 matrix;

// glm::vec2 getMousePos(GLFWwindow *window);

// void resizeCallback(GLFWwindow* window, int width, int height);
// void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
// void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
// void wheelCallback(GLFWwindow* window, double xoffset, double yoffset);
// void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
    auto &app = engine::Application::getInstance();
    // glfwInit();
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFWwindow* window = glfwCreateWindow(800, 600, "Simulator", NULL, NULL);
    // glfwMakeContextCurrent(window);
    // glfwSetFramebufferSizeCallback(window, resizeCallback);
    // glfwSetMouseButtonCallback(window, mouseButtonCallback);
    // glfwSetCursorPosCallback(window, mouseMoveCallback);
    // glfwSetScrollCallback(window, wheelCallback);
    // glfwSetKeyCallback(window, keyboardCallback);
    // glfwSetMousePosCallBack... https://www.jianshu.com/p/4672f38f6c1e
    // gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    Global::getInstance().stage = Global::Stage::Running;
    Window window;
    // auto &render = Render::getInstance();
    // render.setMatrix(&matrix);
    // World::getInstance()->SetDebugDraw(&render);
    window.updateFramebuffer(800, 600);

    // bool running = false;
    // boost::interprocess::message_queue mq(boost::interprocess::create_only, "inputThreadMessageQueue", 128, 32);
    // running = true;
    // std::thread logicThread([&running](){
    //     boost::interprocess::message_queue mq(boost::interprocess::open_only, "inputThreadMessageQueue");
    //     while (running) {
    //         char buf[32];
    //         unsigned long recBufSize;
    //         unsigned int priority;
    //         mq.timed_receive(buf, sizeof(buf), recBufSize, priority, std::chrono::steady_clock::now() + std::chrono::milliseconds(1));
    //         // process
    //     }
    // });
    
    // auto repaintTimerCallback = [](const boost::system::error_code &e){};
    // repaintTimerCallback = [&window, &render, &repaintTimer, &repaintTimerCallback](const boost::system::error_code &e){
    //     render(window);
    //     repaintTimer.expires_from_now(std::chrono::seconds(1));
    //     repaintTimer.async_wait(repaintTimerCallback);
    // };
    // repaintTimer.async_wait(repaintTimerCallback);
    // std::thread io_ctx_thread([&io_ctx](){io_ctx.run();});
    // CommonTimerServer repaintTimerServer;
    // Timer repaintTimer(std::chrono::microseconds(100000 / 30), repaintTimerServer);
    // repaintTimer.setCallbackFunc([&window, &render](){
    //     render(window);
    // });
    // repaintTimer.start();
    app.run();
    // while (!glfwWindowShouldClose(window)) {
    //     // glfwMakeContextCurrent(window);
    //     // render
    //     // glClear(GL_COLOR_BUFFER_BIT);
    //     render(window);


    //     // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    //     // -------------------------------------------------------------------------------
    //     glfwWaitEvents();
    //     // glfwPollEvents();
    //     glfwSwapBuffers(window);
    // }

    // repaintTimer.stop();
    glfwTerminate();
    // running = false;
    // logicThread.join();
    return 0;
}

// glm::vec2 getMousePos(GLFWwindow *window) {
//     double xpos, ypos;
//     glfwGetCursorPos(window, &xpos, &ypos);
//     int width, height;
//     glfwGetWindowSize(window, &width, &height);
//     xpos = xpos * 2 / width - 1;
//     ypos = 1 - ypos * 2 / height;
//     return glm::vec2(xpos, ypos);
// }

// void resizeCallback(GLFWwindow* window, int width, int height) {
//     Render &render = Render::getInstance();
//     matrix[0][0] = 2.0f / width;
//     matrix[1][1] = 2.0f / height;
//     glViewport(0, 0, width, height);
//     render.updateFramebuffer(width, height);
//     // render(window);
//     glfwPostEmptyEvent();
// }

// void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
//     switch (action) {
//     case GLFW_PRESS:
//     {
//         switch (button) {
//         case GLFW_MOUSE_BUTTON_LEFT:
//         {
//             switch (Global::getInstance().stage) {
//             default:
//             case Global::Stage::Running:
//             {
//                 prevMousePos = getMousePos(window);
//                 LBDown = true;
//                 break;
//             }
//             case Global::Stage::Paused: 
//             {
//                 break;
//             }
//             }
//             break;
//         }
//         case GLFW_MOUSE_BUTTON_RIGHT:
//         {
//             RBDown = true;
//             break;
//         }
//         default:
//             break;
//         }

//         break;
//     }
//     case GLFW_RELEASE:
//     {
//         switch (button) {
//         case GLFW_MOUSE_BUTTON_LEFT:
//         {
//             LBDown = false;
//             break;
//         }
//         case GLFW_MOUSE_BUTTON_RIGHT:
//         {
//             RBDown = false;
//             break;
//         }
//         default:
//             break;
//         }
        
//         break;
//     }
//     default:
//         break;
//     }
// }

// void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {
//     switch (Global::getInstance().stage) {
//     default:
//     case Global::Stage::Running:
//     {
//         if (LBDown) {
//             glm::vec2 pos = getMousePos(window);
//             glm::vec2 delta = pos - prevMousePos;
//             glm::mat4x4 t(1);
//             t[3][0] = delta.x;
//             t[3][1] = delta.y;
//             matrix = t * matrix;
//             prevMousePos = pos;
//             glfwPostEmptyEvent();
//         }
//         break;
//     }
//     case Global::Stage::Paused:
//     {
//         break;
//     }
//     }
// }

// void wheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
//     switch (Global::getInstance().stage) {
//     defualt:
//     case Global::Stage::Running:
//     {
//         auto pos = getMousePos(window);
//         glm::mat4x4 t(1), rt(1), m(1);
//         t[3][0] = pos.x;
//         t[3][1] = pos.y;
//         rt[3][0] = -pos.x;
//         rt[3][1] = -pos.y;
//         double offset = yoffset != 0 ? yoffset : xoffset;
//         m[3][3] = offset > 0 ? 1.1f : 1.0f / 1.1f;
//         matrix = t * m * rt * matrix;
//         glfwPostEmptyEvent();
//         break;
//     }
//     case Global::Stage::Paused:
//     {
//         break;
//     }
//     }
// }

// void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//     switch (key) {
//     case GLFW_KEY_ESCAPE:
//     {
//         switch (action) {
//         case GLFW_PRESS:
//         {
//             if (Global::getInstance().stage == Global::Stage::Running) {
//                 Global::getInstance().stage = Global::Stage::Paused;
//                 LBDown = false;
//             }
//             else {
//                 Global::getInstance().stage = Global::Stage::Running;
//             }
//             glfwPostEmptyEvent();
//             break;
//         }
//         default:
//             break;
//         }
//         break;
//     }
//     default:
//         break;
//     }
// }