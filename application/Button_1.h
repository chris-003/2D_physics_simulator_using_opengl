#pragma once
#include "engine/engine.h"
#include <glm/mat4x4.hpp>
#include <memory>

class MainWindow;

class Button_1 : public engine::Widget {
public:
    Button_1(MainWindow *parent);
    ~Button_1();

public:
    void render();

protected:
    std::unique_ptr<engine::VertexBuffer> vbo_button_1;
    std::unique_ptr<engine::VertexArray>  vao_button_1;
    glm::mat4x4                           identity;
};