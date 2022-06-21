#pragma once
#include "engine/engine.h"
#include <box2d/box2d.h>
#include <glm/mat4x4.hpp>
// #include "Widget.h"
#include <vector>
#include <memory>
#include "MainWidget.h"
#include "Button_1.h"

class MainWindow : public engine::Window {
    friend class MainWidget;
    friend class Buton_1;
public:
    MainWindow();
    ~MainWindow();
    // void addWidget(Widget *widget);
    // void removeWidget(Widget *widget);
    // bool isWidget(Widget *widget);
public:
    void init();
    // void setMatrix(const glm::mat4x4 *m);
    void updateFramebuffer(int width, int height);
    // void render();
    // void updateBackgroundFbo();
public:
	// void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
	// void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
	// void DrawCircle(const b2Vec2 &center, float radius, const b2Color &color);
	// void DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color);
	// void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color);
	// void DrawTransform(const b2Transform &xf);
	// void DrawPoint(const b2Vec2 &p, float size, const b2Color &color);
public:
    glm::vec2 getMousePos();
    virtual void FramebufferSizeCallback(int width, int height);
    virtual void MouseButtonCallback(int button, int action, int mods);
    virtual void CursorPosCallback(double xpos, double ypos);
    virtual void ScrollCallback(double xoffset, double yoffset);
    virtual void KeyCallback(int key, int scancode, int action, int mods);
protected:
    // std::vector<Widget *> widgets;
    std::unique_ptr<engine::ShaderProgram> program_basic, program_blur7_pingpong_h, program_blur7_pingpong_v, program_blurN_pingpong_h, program_blurN_pingpong_v, program_copy_texture;
    std::unique_ptr<engine::VertexBuffer> /*vbo1, vbo_blurScreen,*/ vbo_button_1, vbo_button_2;
    std::unique_ptr<engine::VertexArray> /*vao1, vao_blurScreen,*/ vao_button_1;
    // glm::mat4x4 matrix;
    bool LBDown, RBDown;
    glm::vec2 prevMousePos;
    // std::unique_ptr<engine::Framebuffer> defaultFbo, fbo1, fbo2/*, bgfbo*/;
    double x, y;
    std::unique_ptr<MainWidget> mainWidget;
    std::unique_ptr<Button_1> button_1;
};