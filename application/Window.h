#pragma once
#include "engine/engine.h"
#include <box2d/box2d.h>
#include <glm/mat4x4.hpp>

class Window : public engine::Window, public b2Draw {
public:
    Window();
    ~Window();
public:
    void init();
    void setMatrix(const glm::mat4x4 *m);
    void updateFramebuffer(int width, int height);
    void render();
public:
	void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
	void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
	void DrawCircle(const b2Vec2 &center, float radius, const b2Color &color);
	void DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color);
	void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color);
	void DrawTransform(const b2Transform &xf);
	void DrawPoint(const b2Vec2 &p, float size, const b2Color &color);
public:
    glm::vec2 getMousePos();
    void FramebufferSizeCallback(int width, int height);
    void MouseButtonCallback(int button, int action, int mods);
    void CursorPosCallback(double xpos, double ypos);
    void ScrollCallback(double xoffset, double yoffset);
    void KeyCallback(int key, int scancode, int action, int mods);
protected:
    engine::ShaderProgram *program_basic, *program_blur7_pingpong_h, *program_blur7_pingpong_v, *program_blurN_pingpong_h, *program_blurN_pingpong_v, *program_copy_texture;
    engine::VertexBuffer *vbo1, *vbo_blurScreen;
    engine::VertexArray *vao1, *vao_blurScreen;
    glm::mat4x4 matrix;
    bool LBDown, RBDown;
    glm::vec2 prevMousePos;
    engine::Framebuffer *defaultFbo, *fbo1, *fbo2;
};