#pragma once
#include "engine/engine.h"
#include "MainWindow.h"
#include <box2d/box2d.h>
#include <glm/mat4x4.hpp>

class MainWidget : public engine::Widget, public b2Draw {
public:
    MainWidget(MainWindow *parent);
    ~MainWidget();
public:
    void updateFramebuffer(int width, int height);
    void updateBackgroundFbo();
public:
    void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
    void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
    void DrawCircle(const b2Vec2 &center, float radius, const b2Color &color);
    void DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color);
    void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color);
    void DrawTransform(const b2Transform &xf);
    void DrawPoint(const b2Vec2 &p, float size, const b2Color &color);
public:
    virtual void render();
protected:
    glm::mat4x4 matrix;
    std::unique_ptr<engine::Framebuffer> defaultFbo, fbo1, fbo2, bgfbo;
    std::unique_ptr<engine::VertexBuffer> vbo1, vbo_blurScreen;
    std::unique_ptr<engine::VertexArray> vao1, vao_blurScreen;
};