#include "Button_1.h"
#include "MainWindow.h"
#include "engine/engine.h"

Button_1::Button_1(MainWindow *parent) : engine::Widget(parent) {
    setGeometry(glm::vec4(400, 0, 800, 300));
    setFocusable(false);
    {
        {
            vbo_button_1.reset(new engine::VertexBuffer);
            vao_button_1.reset(new engine::VertexArray);
            auto &vbo = vbo_button_1;
            auto  vao = engine::make_BindHelper(vao_button_1);
            // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 *
            // sizeof(float),
            //                       (void *)0);
            // glEnableVertexAttribArray(0);
            // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 *
            // sizeof(float),
            //                       (void *)(2 * sizeof(float)));
            // glEnableVertexAttribArray(1);
            vao->enable(0, 2, 0);
            vao->bindingPoint(0, 0);
            vao->bindVBO(0, *vbo, 0, 2 * sizeof(float));
        }
        // vao_button_1->unbind();
        {
            struct Point {
                float x, y;
            } points[4] = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
            vbo_button_1->write(sizeof(points), points, GL_STATIC_DRAW);
        }
        // vbo_button_1->unbind();
    }
}

Button_1::~Button_1() {
    // delete vao_button_1;
    // delete vbo_button_1;
}

void Button_1::render(engine::Framebuffer &fbo) {
    static glm::mat4x4 identity;
    class Dummy {
    public:
        Dummy() {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    identity[i][j] = (i == j ? 1 : 0);
                }
            }
        }
    } dummy;
    fbo.bind();
    auto  &program_basic = ((MainWindow *)parent())->program_basic;
    double x, y;
    glfwGetCursorPos(parent()->window(), &x, &y);
    // glfwGetCursorPos(parent()->window(), &parent()->x, &parent()->y);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
    program_basic->bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // vao_button_1->bind();
    auto vao = engine::make_BindHelper(vao_button_1);
    // vbo_button_1->bind();
    if (this->x() <= x && x <= this->rightBottomX() && this->y() <= y &&
        y <= this->rightBottomY()) {
        glUniform4f(1, 0.8, 0.8, 0.8, 0.2);
    }
    else {
        glUniform4f(1, 0, 0, 0, 0.6);
    }
    glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    // vao_button_1->unbind();
}