#include "MainWidget.h"
#include "CCircleBuffer.h"
#include "CNormalDistBuffer.h"
#include "Global.h"
#include "MainWindow.h"
#include "SBindHelper.h"
#include "SVertexArray.h"
#include "World.h"

MainWidget::MainWidget(MainWindow *parent)
    : engine::SWidget(parent), matrix(0) {
    ::World::getInstance()->SetDebugDraw(this);
    b2Draw::SetFlags(e_shapeBit | e_jointBit | e_aabbBit | e_pairBit |
                     e_centerOfMassBit);
    matrix[0][0] = 2.0f / 800;
    matrix[1][1] = 2.0f / 600;
    matrix[2][2] = 1;
    matrix[3][3] = 1;
    LBDown       = false;
    RBDown       = false;

    {
        vbo1.reset(new engine::SVertexBuffer);
        vao1.reset(new engine::SVertexArray);
        // auto vbo = engine::make_BindHelper(vbo1);
        auto &vbo = vbo1;
        auto  vao = engine::make_SBindHelper(vao1);
        vao->enable(0, 2, 0);
        vao->bindingPoint(0, 0);
        vao->bindVBO(0, *vbo, 0, 2 * sizeof(float));
    }
    {{vbo_blurScreen.reset(new engine::SVertexBuffer);
    vao_blurScreen.reset(new engine::SVertexArray);
    // auto vbo = engine::make_BindHelper(vbo_blurScreen);
    auto &vbo = vbo_blurScreen;
    auto  vao = engine::make_SBindHelper(vao_blurScreen);
    vao->enable(0, 2, 0);
    vao->bindingPoint(0, 0);
    vao->enable(1, 2, 2 * sizeof(float));
    vao->bindingPoint(1, 0);
    // vao->bindVBO(0, *vbo, 2 * sizeof(float), 4 * sizeof(float));
    vao->bindVBO(0, *vbo, 0, 4 * sizeof(float));
}
{
    // auto vbo = engine::make_BindHelper(vbo_blurScreen);
    auto &vbo = vbo_blurScreen;
    struct Point {
        float x, y, tx, ty;
    } points[4] = {{1, 1, 1, 1}, {-1, 1, 0, 1}, {-1, -1, 0, 0}, {1, -1, 1, 0}};
    vbo->write(sizeof(points), points, GL_STATIC_DRAW);
}
}
{
    // simulatingTimer.setCallbackFunc([]() {
    //     ::World::getInstance().step();
    // });
    // simulatingTimer.start(std::chrono::milliseconds(1000 / 60));
    simulatingTimer.setInterval(1000 / 60.0f);
    simulatingTimer.connect(&simulatingTimer, &QTimer::timeout, []() {
        ::World::getInstance().step();
    });
}
}

MainWidget::~MainWidget() {
}

void MainWidget::updateFramebuffer(int width, int height) {
    auto updateFbo = [&](std::unique_ptr<engine::SFramebuffer> &fbo) {
        fbo.reset(new engine::SFramebuffer(width, height));
    };
    // if (fbo1 != nullptr) {
    // 	delete fbo1;
    // }
    // if (fbo2 != nullptr) {
    // 	delete fbo2;
    // }
    // fbo1 = new Framebuffer(width, height);
    // fbo2 = new Framebuffer(width, height);
    updateFbo(defaultFbo);
    updateFbo(fbo1);
    updateFbo(fbo2);
    updateFbo(bgfbo);
}

void MainWidget::updateBackgroundFbo() {
    MainWindow              *parent = (MainWindow *)this->parent();
    static const glm::mat4x4 identity(1);

    fbo1->bind();
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ::World::getInstance()->DebugDraw();

    {
        fbo2->bind();
        glClear(GL_COLOR_BUFFER_BIT);
        parent->program_blurN_pingpong_h->bind();
        fbo1->bindTexture(0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // auto vbo = engine::make_BindHelper(vbo_blurScreen);
        auto vao = engine::make_SBindHelper(vao_blurScreen);
        glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
        glUniform1i(3, 24);
        glUniform1fv(4, 24 * sizeof(float),
                     CNormalDistBuffer<24>::getInstance().buffer());
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
    {
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // defaultFbo->bind();
        // fbo1->bind();
        bgfbo->bind();
        glClear(GL_COLOR_BUFFER_BIT);
        parent->program_blurN_pingpong_v->bind();
        fbo2->bindTexture(0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // auto vbo = engine::make_BindHelper(vbo_blurScreen);
        auto vao = engine::make_SBindHelper(vao_blurScreen);
        glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
        glUniform1i(3, 24);
        glUniform1fv(4, 24 * sizeof(float),
                     CNormalDistBuffer<24>::getInstance().buffer());
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
}

glm::vec2 MainWidget::getMousePos() {
    double x, y;
    glfwGetCursorPos(parent()->window(), &x, &y);
    return glm::vec2(x, y);
}

// glm::vec2 MainWidget::getMousePos() {
// 	double xpos, ypos;
// 	glfwGetCursorPos(parent()->window(), &xpos, &ypos);
// 	int width, height;
// 	glfwGetWindowSize(parent()->window(), &width, &height);
// 	xpos = xpos * 2 / width - 1;
// 	ypos = 1 - ypos * 2 / height;
// 	return glm::vec2(xpos, ypos);
// }

void MainWidget::render(engine::SFramebuffer &fbo_1) {
    fbo_1.bind();
    MainWindow *parent = (MainWindow *)this->parent();
    // glfwMakeContextCurrent(window);
    // defaultFbo->bind();

    Global &global = Global::getInstance();
    switch (global.stage) {
    default:
    case Global::Stage::Running: {
        glClear(GL_COLOR_BUFFER_BIT);
        ::World::getInstance()->DebugDraw();
        b2Vec2 vertexes[4] = {{0, 0}, {0, 1}, {1, 1}, {1, 0}};
        // this->DrawSolidCircle(b2Vec2(0, 0), 10, b2Vec2(0, 0), b2Color(1, 0,
        // 0)); program_copy_texture->bind(); glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, m_texture);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // vbo_blurScreen->bind();
        // vao_blurScreen->bind();
        // static const glm::mat4x4 identity(1);
        // glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
        // glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        // vao_blurScreen->unbind();
        break;
    }
    case Global::Stage::Paused: {
        // fbo1->bind();
        // glClear(GL_COLOR_BUFFER_BIT);
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // ::World::getInstance()->DebugDraw();

        // program_copy_texture->bind();
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, m_texture);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // vbo_blurScreen->bind();
        // vao_blurScreen->bind();
        // static const glm::mat4x4 identity(1);
        // glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
        // glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        // vao_blurScreen->unbind();

#if 0
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        program_blur7_pingpong_h->bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, fbo1->texture());
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        vbo_blurScreen->bind();
        vao_blurScreen->bind();
        static const glm::mat4x4 identity(1);
        glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        vao_blurScreen->unbind();
#else
        // fbo2->bind();
        // glClear(GL_COLOR_BUFFER_BIT);
        // program_blurN_pingpong_h->bind();
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, fbo1->texture());
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // vbo_blurScreen->bind();
        // vao_blurScreen->bind();
        static const glm::mat4x4 identity(1);
        // glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
        // glUniform1i(3, 24);
        // glUniform1fv(4, 24 * sizeof(float),
        // CNormalDistBuffer<24>::getInstance().buffer());
        // glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        // vao_blurScreen->unbind();

        // glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // // defaultFbo->bind();
        // // fbo1->bind();
        // glClear(GL_COLOR_BUFFER_BIT);
        // program_blurN_pingpong_v->bind();
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, fbo2->texture());
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // vbo_blurScreen->bind();
        // vao_blurScreen->bind();
        // // static const glm::mat4x4 identity(1);
        // glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
        // glUniform1i(3, 24);
        // glUniform1fv(4, 24 * sizeof(float),
        // CNormalDistBuffer<24>::getInstance().buffer());
        // glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        // vao_blurScreen->unbind();
        {
            // glBindFramebuffer(GL_FRAMEBUFFER, 0);
            fbo_1.bind();
            // glClear(GL_COLOR_BUFFER_BIT);
            parent->program_copy_texture->bind();
            bgfbo->bindTexture(0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            // auto vbo = engine::make_BindHelper(vbo_blurScreen);
            auto vao = engine::make_SBindHelper(vao_blurScreen);
            // glUniform4f(1, 0, 0, 0, 0.6);
            glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        }
        {
            // glBindFramebuffer(GL_FRAMEBUFFER, 0);
            // glClear(GL_COLOR_BUFFER_BIT);
            parent->program_basic->bind();
            // glActiveTexture(GL_TEXTURE0);
            // glBindTexture(GL_TEXTURE_2D, fbo1->texture());
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            // auto vbo = engine::make_BindHelper(vbo_blurScreen);
            auto vao = engine::make_SBindHelper(vao_blurScreen);
            glUniform4f(1, 0, 0, 0, 0.6);
            glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        }

        // glfwGetCursorPos(window, &x, &y);
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // program_basic->bind();
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // vao_button_1->bind();
        // vbo_button_1->bind();
        // if (400 <= x && x <= 800 && 0 <= y && y <= 300) {
        // 	glUniform4f(1, 0.8, 0.8, 0.8, 0.2);
        // }
        // else {
        // 	glUniform4f(1, 0, 0, 0, 0.6);
        // }
        // glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
        // glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        // vao_button_1->unbind();

#endif
        break;
    }
    }
    // glfwSwapBuffers(window);
}

void MainWidget::FramebufferSizeCallback(int width, int height) {
    matrix[0][0] = 2.0f / width;
    matrix[1][1] = 2.0f / height;
    updateFramebuffer(width, height);
    if (Global::getInstance().stage == Global::Stage::Paused) {
        updateBackgroundFbo();
    }
    engine::SWidget::FramebufferSizeCallback(width, height);
}

void MainWidget::MouseButtonCallback(int button, int action, int mods) {
    switch (action) {
    case GLFW_PRESS: {
        switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT: {
            switch (Global::getInstance().stage) {
            default:
            case Global::Stage::Running: {
                prevMousePos = getMousePos();
                LBDown       = true;
                break;
            }
            case Global::Stage::Paused: {
                break;
            }
            }
            break;
        }
        case GLFW_MOUSE_BUTTON_RIGHT: {
            RBDown = true;
            break;
        }
        default:
            break;
        }

        break;
    }
    case GLFW_RELEASE: {
        switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT: {
            LBDown = false;
            break;
        }
        case GLFW_MOUSE_BUTTON_RIGHT: {
            RBDown = false;
            break;
        }
        default:
            break;
        }

        break;
    }
    default:
        break;
    }
    engine::SWidget::MouseButtonCallback(button, action, mods);
}

void MainWidget::CursorPosCallback(double xpos, double ypos) {
    switch (Global::getInstance().stage) {
    default:
    case Global::Stage::Running: {
        if (LBDown) {
            glm::vec2   pos   = getMousePos();
            glm::vec2   delta = pos - prevMousePos;
            glm::mat4x4 t(1);
            t[3][0]      = matrix[0][0] * delta.x;
            t[3][1]      = -matrix[1][1] * delta.y;
            matrix       = t * matrix;
            prevMousePos = pos;
            glfwPostEmptyEvent();
        }
        break;
    }
    case Global::Stage::Paused: {
        break;
    }
    }
    engine::SWidget::CursorPosCallback(xpos, ypos);
}

void MainWidget::ScrollCallback(double xoffset, double yoffset) {
    switch (Global::getInstance().stage) {
    defualt:
    case Global::Stage::Running: {
        auto        pos = getMousePos();
        glm::mat4x4 t(1), rt(1), m(1);
        t[3][0]       = pos.x * matrix[0][0] - 1;
        t[3][1]       = 1 - pos.y * matrix[1][1];
        rt[3][0]      = -t[3][0];
        rt[3][1]      = -t[3][1];
        double offset = yoffset != 0 ? yoffset : xoffset;
        m[3][3]       = offset > 0 ? 1.1f : 1.0f / 1.1f;
        matrix        = t * m * rt * matrix;
        // glfwPostEmptyEvent();
        break;
    }
    case Global::Stage::Paused: {
        break;
    }
    }
    engine::SWidget::ScrollCallback(xoffset, yoffset);
}

void MainWidget::KeyCallback(int key, int scancode, int action, int mods) {
    switch (key) {
    case GLFW_KEY_ESCAPE: {
        switch (action) {
        case GLFW_PRESS: {
            if (Global::getInstance().stage == Global::Stage::Running) {
                Global::getInstance().stage = Global::Stage::Paused;
                LBDown                      = false;
                simulatingTimer.stop();
                updateBackgroundFbo();
                ((MainWindow *)parent())->button_1->setVisible(true);
            }
            else {
                Global::getInstance().stage = Global::Stage::Running;
                simulatingTimer.start();
                ((MainWindow *)parent())->button_1->setVisible(false);
            }
            // glfwPostEmptyEvent();
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
    engine::SWidget::KeyCallback(key, scancode, action, mods);
}

void MainWidget::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount,
                             const b2Color &color) {
    MainWindow *parent  = (MainWindow *)this->parent();
    auto       &program = parent->program_basic;
    program->bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // auto vbo = engine::make_BindHelper(vbo1);
    auto &vbo = vbo1;
    vbo->write(vertexCount * sizeof(b2Vec2), (void *)vertices);
    glUniform4f(1, color.r, color.g, color.b, color.a);
    glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&matrix);
    auto vao = engine::make_SBindHelper(vao1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
}

void MainWidget::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount,
                                  const b2Color &color) {
    MainWindow *parent  = (MainWindow *)this->parent();
    auto       &program = parent->program_basic;
    program->bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // auto vbo = engine::make_BindHelper(vbo1);
    auto &vbo = vbo1;
    vbo->write(vertexCount * sizeof(b2Vec2), (void *)vertices);
    glUniform4f(1, color.r, color.g, color.b, color.a);
    glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&matrix);
    auto vao = engine::make_SBindHelper(vao1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
}

void MainWidget::DrawCircle(const b2Vec2 &center, float radius,
                            const b2Color &color) {
    MainWindow *parent  = (MainWindow *)this->parent();
    auto       &program = parent->program_basic;
    program->bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // auto vbo = engine::make_BindHelper(vbo1);
    auto                 &vbo = vbo1;
    const int             N   = 256;
    std::array<b2Vec2, N> buf;
    auto                 &circleBuffer = CCircleBuffer<N>::getInstance();
    for (int i = 0; i < N; ++i) {
        buf[i].x = center.x + radius * circleBuffer[i].x;
        buf[i].y = center.y + radius * circleBuffer[i].y;
    }
    vbo->write(N * sizeof(b2Vec2), buf.data());
    glUniform4f(1, color.r, color.g, color.b, color.a);
    glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&matrix);
    auto vao = engine::make_SBindHelper(vao1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, N);
}

void MainWidget::DrawSolidCircle(const b2Vec2 &center, float radius,
                                 const b2Vec2 &axis, const b2Color &color) {
    MainWindow *parent  = (MainWindow *)this->parent();
    auto       &program = parent->program_basic;
    program->bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // auto vbo = engine::make_BindHelper(vbo1);
    auto                 &vbo = vbo1;
    const int             N   = 256;
    std::array<b2Vec2, N> buf;
    auto                 &circleBuffer = CCircleBuffer<N>::getInstance();
    for (int i = 0; i < N; ++i) {
        buf[i].x = center.x + radius * circleBuffer[i].x;
        buf[i].y = center.y + radius * circleBuffer[i].y;
    }
    vbo->write(N * sizeof(b2Vec2), buf.data());
    glUniform4f(1, color.r, color.g, color.b, color.a);
    glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&matrix);
    auto vao = engine::make_SBindHelper(vao1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, N);
}

void MainWidget::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                             const b2Color &color) {
    MainWindow *parent  = (MainWindow *)this->parent();
    auto       &program = parent->program_basic;
    program->bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // auto vbo = engine::make_BindHelper(vbo1);
    auto  &vbo = vbo1;
    b2Vec2 pos[2];
    pos[0] = p1;
    pos[1] = p2;
    vbo->write(2 * sizeof(b2Vec2), pos);
    glUniform4f(1, color.r, color.g, color.b, color.a);
    glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&matrix);
    auto vao = engine::make_SBindHelper(vao1);
    glDrawArrays(GL_LINE, 0, 2);
}

void MainWidget::DrawTransform(const b2Transform &xf) {
    DrawSegment(xf.p, xf.p + matrix[3][3] * 100 * b2Vec2(xf.q.c, xf.q.s),
                b2Color(0, 0, 0, 1));
    DrawSegment(xf.p, xf.p + matrix[3][3] * 100 * b2Vec2(-xf.q.s, xf.q.c),
                b2Color(0, 0, 0, 1));
}

void MainWidget::DrawPoint(const b2Vec2 &p, float size, const b2Color &color) {
    DrawSolidCircle(p, size * matrix[3][3], b2Vec2(0, 0), color);
}
