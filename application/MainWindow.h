#pragma once
#include "engine/engine.h"
#include <box2d/box2d.h>
#include <glm/mat4x4.hpp>
// #include "Widget.h"
// #include "Button_1.h"
#include "MainWidget.h"
#include <memory>
#include <vector>

class MainWindow : public engine::Window {
    friend class MainWidget;
    friend class Button_1;

public:
    MainWindow();
    ~MainWindow();

public:
    void init();
    void updateFramebuffer(int width, int height);

public:
    virtual void FramebufferSizeCallback(int width, int height);
    virtual void MouseButtonCallback(int button, int action, int mods);
    virtual void CursorPosCallback(double xpos, double ypos);
    virtual void ScrollCallback(double xoffset, double yoffset);
    virtual void KeyCallback(int key, int scancode, int action, int mods);

protected:
    std::unique_ptr<engine::ShaderProgram> program_basic,
        program_blur7_pingpong_h, program_blur7_pingpong_v,
        program_blurN_pingpong_h, program_blurN_pingpong_v,
        program_copy_texture;
    std::unique_ptr<engine::VertexBuffer> vbo_button_1, vbo_button_2;
    std::unique_ptr<engine::VertexArray>  vao_button_1;
    std::unique_ptr<MainWidget>           mainWidget;
    // std::unique_ptr<Button_1>             button_1;
    std::unique_ptr<engine::Button> button_1;
};