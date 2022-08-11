#include "Button.h"
#include "Resource.h"

namespace engine {
Button::Button(Window *parent) : Widget(parent), pushed(false) {
    colors[0] = glm::vec4(0.00, 0.00, 0.00, 0.3);
    colors[1] = glm::vec4(0.20, 0.20, 0.20, 0.3);
    colors[2] = glm::vec4(0.50, 0.50, 0.50, 0.3);
    {
        vao.reset(new VertexArray);
        vbo.reset(new VertexBuffer);
        {
            auto vao = make_BindHelper(this->vao);
            vao->enable(0, 2, 0);
            // vao->enable(1);
            vao->bindingPoint(0, 0);
            vao->bindVBO(0, *vbo, 0, 2 * sizeof(float));
        }
        {
            auto vbo = make_BindHelper(this->vbo);
            struct {
                float x, y;
            } points[4] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
            vbo->write(sizeof(points), points);
        }
    }
    setFocusable(false);
}

Button::~Button() {
}

void Button::render(Framebuffer &fbo) {
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
    Resource::ShaderProgram_color().bind();
    glUniform4f(1, color->r, color->g, color->b, color->a);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    auto vao = make_BindHelper(this->vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Button::MouseButtonCallback(int button, int action, int mods) {
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