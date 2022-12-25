#if 0
#include "SButton.h"
#include "SResourceData.h"
#include "SShaderProgram.h"

namespace engine {
SButton::SButton(SWindow *parent) : SWidget(parent), pushed(false) {
    colors[0] = glm::vec4(0.00, 0.00, 0.00, 0.3);
    colors[1] = glm::vec4(0.20, 0.20, 0.20, 0.3);
    colors[2] = glm::vec4(0.50, 0.50, 0.50, 0.3);
    {
        vao.reset(new SVertexArray);
        vbo.reset(new SVertexBuffer);
        {
            auto vao = make_SBindHelper(this->vao);
            vao->enable(0, 2, 0);
            // vao->enable(1);
            vao->bindingPoint(0, 0);
            vao->bindVBO(0, *vbo, 0, 2 * sizeof(float));
        }
        {
            auto vbo = make_SBindHelper(this->vbo);
            struct {
                float x, y;
            } points[4] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
            vbo->write(sizeof(points), points);
        }
    }
    setFocusable(false);
}

SButton::~SButton() {
}

void SButton::render(SFramebuffer &fbo) {
    fbo.bind();
    glm::vec4 *color;
    if (containMouse()) {
        if (pushed) {
            color = &colors[2];
        }
        else {
            color = &colors[1];
        }
    }
    else {
        color = &colors[0];
    }
    // static SShaderProgram *program = new SShaderProgram(
    //     QFile(":/Engine/Shaders/color.vert").readAll().data(),
    //     QFile(":/Engine/Shaders/color.frag").readAll().data());
    static const auto     &resource = SResourceData::get_resource("engine");
    static SShaderProgram *program  = new SShaderProgram(
         SResourceData::get(resource, ":/Shaders/color.vert").first,
         SResourceData::get(resource, ":/Shaders/color.frag").first);
    program->bind();
    glUniform4f(1, color->r, color->g, color->b, color->a);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    auto vao = make_SBindHelper(this->vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void SButton::MouseButtonCallback(int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        switch (action) {
        case GLFW_PRESS: {
            pushed = true;
            emit<>(Signal(1));
            break;
        }
        case GLFW_RELEASE: {
            emit<>(Signal(2));
            if (pushed) {
                emit<>(Signal(0));
            }
            pushed = false;
            break;
        }
        }
    }
}
} // namespace engine
#endif