#include "Button_1.h"
#include "MainWindow.h"
#include "engine/engine.h"

Button_1::Button_1(MainWindow *parent) : Widget(parent) {
    setGeometry(glm::vec4(400, 0, 800, 300));

    vbo_button_1.reset(new engine::VertexBuffer);
    vao_button_1.reset(new engine::VertexArray);
    vao_button_1->bind();
    vbo_button_1->bind();
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    vao_button_1->unbind();
    {
        struct Point {
            float x, y, tx, ty;
        } points[4] = {
            {1, 1, 1, 1}, {0, 1, 0.5, 1}, {0, 0, 0.5, 0.5}, {1, 0, 1, 0.5}};
        vbo_button_1->write(sizeof(points), points, GL_STATIC_DRAW);
    }
    vbo_button_1->unbind();
}

Button_1::~Button_1() {
    // delete vao_button_1;
    // delete vbo_button_1;
}

void Button_1::render() {
    auto  &program_basic = ((MainWindow *)parent())->program_basic;
    double x, y;
    glfwGetCursorPos(parent()->window(), &x, &y);
    // glfwGetCursorPos(parent()->window(), &parent()->x, &parent()->y);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    program_basic->bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    vao_button_1->bind();
    vbo_button_1->bind();
    if (400 <= x && x <= 800 && 0 <= y && y <= 300) {
        glUniform4f(1, 0.8, 0.8, 0.8, 0.2);
    }
    else {
        glUniform4f(1, 0, 0, 0, 0.6);
    }
    glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    vao_button_1->unbind();
}