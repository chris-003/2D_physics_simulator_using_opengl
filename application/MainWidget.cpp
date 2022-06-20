#include "MainWidget.h"
#include "Global.h"
#include "World.h"
#include "CCircleBuffer.h"
#include "CNormalDistBuffer.h"

MainWidget::MainWidget(MainWindow *parent) : engine::Widget(parent) {
    ::World::getInstance()->SetDebugDraw(this);
    b2Draw::SetFlags(e_shapeBit | e_jointBit | e_aabbBit | e_pairBit | e_centerOfMassBit);
    matrix[0][0] = 2.0f / 800;
    matrix[1][1] = 2.0f / 600;
    matrix[2][2] = 1;
    matrix[3][3] = 1;

    {
        vbo1.reset(new engine::VertexBuffer);
        vao1.reset(new engine::VertexArray);
        vao1->bind();
        vbo1->bind();
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        vao1->unbind();
        vbo1->unbind();
    }
    {
        vbo_blurScreen.reset(new engine::VertexBuffer);
        vao_blurScreen.reset(new engine::VertexArray);
        vao_blurScreen->bind();
        vbo_blurScreen->bind();
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        vao_blurScreen->unbind();
        {
            struct Point {
                float x, y, tx, ty;
            } points[4] = {{1, 1, 1, 1}, {-1, 1, 0, 1}, {-1, -1, 0, 0}, {1, -1, 1, 0}};
            vbo_blurScreen->write(sizeof(points), points, GL_STATIC_DRAW);
        }
        vbo_blurScreen->unbind();
    }
}

MainWidget::~MainWidget() {}

void MainWidget::updateFramebuffer(int width, int height) {
	auto updateFbo = [&](std::unique_ptr<engine::Framebuffer> &fbo) {
		fbo.reset(new engine::Framebuffer(width, height));
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
        MainWindow *parent = (MainWindow *)this->parent();

		fbo1->bind();
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		::World::getInstance()->DebugDraw();

		fbo2->bind();
		glClear(GL_COLOR_BUFFER_BIT);
		parent->program_blurN_pingpong_h->bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fbo1->texture());
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		vbo_blurScreen->bind();
		vao_blurScreen->bind();
		static const glm::mat4x4 identity(1);
		glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
		glUniform1i(3, 24);
		glUniform1fv(4, 24 * sizeof(float), CNormalDistBuffer<24>::getInstance().buffer());
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		vao_blurScreen->unbind();

		// glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// defaultFbo->bind();
		// fbo1->bind();
		bgfbo->bind();
		glClear(GL_COLOR_BUFFER_BIT);
		parent->program_blurN_pingpong_v->bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fbo2->texture());
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		vbo_blurScreen->bind();
		vao_blurScreen->bind();
		// static const glm::mat4x4 identity(1);
		glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
		glUniform1i(3, 24);
		glUniform1fv(4, 24 * sizeof(float), CNormalDistBuffer<24>::getInstance().buffer());
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		vao_blurScreen->unbind();
}

void MainWidget::render() {
    MainWindow *parent = (MainWindow *)this->parent();
    // glfwMakeContextCurrent(window);
    // defaultFbo->bind();

    Global &global = Global::getInstance();
    switch (global.stage) {
    default:
    case Global::Stage::Running: {
        glClear(GL_COLOR_BUFFER_BIT);
        ::World::getInstance()->DebugDraw();
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
        // glUniform1fv(4, 24 * sizeof(float), CNormalDistBuffer<24>::getInstance().buffer());
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
        // glUniform1fv(4, 24 * sizeof(float), CNormalDistBuffer<24>::getInstance().buffer());
        // glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        // vao_blurScreen->unbind();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // glClear(GL_COLOR_BUFFER_BIT);
        parent->program_copy_texture->bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, bgfbo->texture());
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        vbo_blurScreen->bind();
        vao_blurScreen->bind();
        // glUniform4f(1, 0, 0, 0, 0.6);
        glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        vao_blurScreen->unbind();

        // glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // glClear(GL_COLOR_BUFFER_BIT);
        parent->program_basic->bind();
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, fbo1->texture());
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        vbo_blurScreen->bind();
        vao_blurScreen->bind();
        glUniform4f(1, 0, 0, 0, 0.6);
        glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        vao_blurScreen->unbind();

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

void MainWidget::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    MainWindow *parent = (MainWindow *)this->parent();
    auto &program = parent->program_basic;
    program->bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    vbo1->bind();
    vbo1->write(vertexCount * sizeof(b2Vec2), (void *)vertices);
    glUniform4f(1, color.r, color.g, color.b, color.a);
    glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&matrix);
    vao1->bind();
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    vao1->unbind();
}

void MainWidget::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    MainWindow *parent = (MainWindow *)this->parent();
    auto &program = parent->program_basic;
    program->bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    vbo1->bind();
    vbo1->write(vertexCount * sizeof(b2Vec2), (void *)vertices);
    glUniform4f(1, color.r, color.g, color.b, color.a);
    glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&matrix);
    vao1->bind();
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    vao1->unbind();
}

void MainWidget::DrawCircle(const b2Vec2 &center, float radius, const b2Color &color) {
    MainWindow *parent = (MainWindow *)this->parent();
    auto &program = parent->program_basic;
    program->bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    vbo1->bind();
    const int N = 256;
    std::array<b2Vec2, N> buf;
    auto &circleBuffer = CCircleBuffer<N>::getInstance();
    for (int i = 0; i < N; ++i) {
        buf[i].x = center.x + radius * circleBuffer[i].x;
        buf[i].y = center.y + radius * circleBuffer[i].y;
    }
    vbo1->write(N * sizeof(b2Vec2), buf.data());
    glUniform4f(1, color.r, color.g, color.b, color.a);
    glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&matrix);
    vao1->bind();
    glDrawArrays(GL_TRIANGLE_FAN, 0, N);
    vao1->unbind();
}

void MainWidget::DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color) {
    MainWindow *parent = (MainWindow *)this->parent();
    auto &program = parent->program_basic;
    program->bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    vbo1->bind();
    const int N = 256;
    std::array<b2Vec2, N> buf;
    auto &circleBuffer = CCircleBuffer<N>::getInstance();
    for (int i = 0; i < N; ++i) {
        buf[i].x = center.x + radius * circleBuffer[i].x;
        buf[i].y = center.y + radius * circleBuffer[i].y;
    }
    vbo1->write(N * sizeof(b2Vec2), buf.data());
    glUniform4f(1, color.r, color.g, color.b, color.a);
    glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&matrix);
    vao1->bind();
    glDrawArrays(GL_TRIANGLE_FAN, 0, N);
    vao1->unbind();
}

void MainWidget::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {
    MainWindow *parent = (MainWindow *)this->parent();
    auto &program = parent->program_basic;
    program->bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    vbo1->bind();
    b2Vec2 pos[2];
    pos[0] = p1;
    pos[1] = p2;
    vbo1->write(2 * sizeof(b2Vec2), pos);
    glUniform4f(1, color.r, color.g, color.b, color.a);
    glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&matrix);
    vao1->bind();
    glDrawArrays(GL_LINE, 0, 2);
    vao1->unbind();
}

void MainWidget::DrawTransform(const b2Transform &xf) {
    DrawSegment(xf.p, xf.p + matrix[3][3] * 100 * b2Vec2(xf.q.c, xf.q.s), b2Color(0, 0, 0, 1));
    DrawSegment(xf.p, xf.p + matrix[3][3] * 100 * b2Vec2(-xf.q.s, xf.q.c), b2Color(0, 0, 0, 1));
}

void MainWidget::DrawPoint(const b2Vec2 &p, float size, const b2Color &color) {
    DrawSolidCircle(p, size * matrix[3][3], b2Vec2(0, 0), color);
}
