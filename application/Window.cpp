#include "Window.h"
#include "engine/engine.h"
#include "Resource.h"
#include <array>
#include "CCircleBuffer.h"
#include <iostream>
#include "Global.h"
#include "CNormalDistBuffer.h"
#include "stb_image"
#include "World.h"
#include <iostream>

using engine::Shader;
using engine::ShaderProgram;
using engine::VertexBuffer;
using engine::VertexArray;
using engine::Framebuffer;
using std::cout;
using std::endl;

Window::Window() : defaultFbo(nullptr), fbo1(nullptr), fbo2(nullptr), engine::Window(glm::vec2(800, 600), "Simulator") {
	init();

}

void Window::addWidget(Widget *widget) {
	if (widget == nullptr) {
		return;
	}
	// else
	widgets.push_back(widget);
	widget->setParent(this);
}
void Window::removeWidget(Widget *widget) {
	if (widget == nullptr) {
		return;
	}
	// else
	widgets.erase(std::find(widgets.begin(), widgets.end(), widget));
	widget->setParent(nullptr);
}

void Window::init() {
	glfwMakeContextCurrent(window);
	matrix[0][0] = 2.0f / 800;
	matrix[1][1] = 2.0f / 600;
	matrix[2][2] = 1;
	matrix[3][3] = 1;
	LBDown = false;
	RBDown = false;
	::World::getInstance()->SetDebugDraw(this);

	b2Draw::SetFlags(e_shapeBit | e_jointBit | e_aabbBit | e_pairBit | e_centerOfMassBit);
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	auto &resource = Resource::getInstance();
	program_basic = new ShaderProgram(resource.basic_vert(), resource.basic_frag());
	program_blur7_pingpong_h = new ShaderProgram(resource.blur7_pingpong_h_vert(), resource.blur7_pingpong_h_frag());
	program_blur7_pingpong_v = new ShaderProgram(resource.blur7_pingpong_v_vert(), resource.blur7_pingpong_v_frag());
	program_blurN_pingpong_h = new ShaderProgram(resource.blurN_pingpong_h_vert(), resource.blurN_pingpong_h_frag());
	program_blurN_pingpong_v = new ShaderProgram(resource.blurN_pingpong_v_vert(), resource.blurN_pingpong_v_frag());
	program_copy_texture = new ShaderProgram(resource.copy_texutre_vert(), resource.copy_texture_frag());

	vbo1 = new VertexBuffer;
	vao1 = new VertexArray;
	vao1->bind();
	vbo1->bind();
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	vao1->unbind();
	vbo1->unbind();

	vbo_blurScreen = new VertexBuffer;
	vao_blurScreen = new VertexArray;
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
	
	vbo_button_1 = new VertexBuffer;
	vao_button_1 = new VertexArray;
	vao_button_1->bind();
	vbo_button_1->bind();
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	vao_button_1->unbind();
	{
		struct Point {
			float x, y, tx, ty;
		} points[4] = {{1, 1, 1, 1}, {0, 1, 0.5, 1}, {0, 0, 0.5, 0.5}, {1, 0, 1, 0.5}};
		vbo_button_1->write(sizeof(points), points, GL_STATIC_DRAW);
	}
	vbo_button_1->unbind();
	// {
	// 	unsigned int &texture = m_texture;
	// 	glGenTextures(1, &texture);
	// 	glBindTexture(GL_TEXTURE_2D, texture);
	// 	// 为当前绑定的纹理对象设置环绕、过滤方式
	// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
	// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 	// 加载并生成纹理
	// 	int width, height, nrChannels;
	// 	unsigned char *data = stbi_load("image.jpeg", &width, &height, &nrChannels, 0);
	// 	if (data)
	// 	{
	// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	// 		glGenerateMipmap(GL_TEXTURE_2D);
	// 	}
	// 	else
	// 	{
	// 		std::cout << "Failed to load texture" << std::endl;
	// 	}
	// 	stbi_image_free(data);
	// }
}

Window::~Window() {
	delete vao_button_1;
	delete vbo_button_1;
	delete vao_blurScreen;
	delete vbo_blurScreen;
	delete vao1;
	delete vbo1;
	delete program_copy_texture;
	delete program_blurN_pingpong_v;
	delete program_blurN_pingpong_h;
	delete program_blur7_pingpong_v;
	delete program_blur7_pingpong_h;
	delete program_basic;
}

void Window::setMatrix(const glm::mat4x4 *m) {
	matrix = *m;
}

void Window::updateFramebuffer(int width, int height) {
	auto updateFbo = [&](Framebuffer *&fbo) {
		if (fbo != nullptr) {
			delete fbo;
		}
		fbo = new Framebuffer(width, height);
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
}

// void Window::repaint(GLFWwindow *window) {
// 	static const glm::mat4x4 identity(1);

// 	glfwMakeContextCurrent(window);
// 	glBindFramebuffer(GL_FRAMEBUFFER, 0);
// 	glActiveTexture(GL_TEXTURE0);
// 	program_copy_texture->bind();
// 	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
// 	vbo_blurScreen->bind();
// 	vao_blurScreen->bind();
// 	glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
// 	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
// 	// vao_blurScreen->unbind();
// }

void Window::render() {
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
		fbo1->bind();
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
		fbo2->bind();
		glClear(GL_COLOR_BUFFER_BIT);
		program_blurN_pingpong_h->bind();
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

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// defaultFbo->bind();
		// fbo1->bind();
		glClear(GL_COLOR_BUFFER_BIT);
		program_blurN_pingpong_v->bind();
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

		// glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// glClear(GL_COLOR_BUFFER_BIT);
		program_basic->bind();
		// glActiveTexture(GL_TEXTURE0);
		// glBindTexture(GL_TEXTURE_2D, fbo1->texture());
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		vbo_blurScreen->bind();
		vao_blurScreen->bind();
		glUniform4f(1, 0, 0, 0, 0.6);
		glUniformMatrix4fv(2, 1, GL_FALSE, (GLfloat *)&identity);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		vao_blurScreen->unbind();

		glfwGetCursorPos(window, &x, &y);
		// cout << "x: " << x << ", y: " << y << endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		program_basic->bind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// vbo_blurScreen->bind();
		// #error
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

#endif
		break;
	}
	}
	// glfwSwapBuffers(window);
}

void Window::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
	auto *program = program_basic;
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

void Window::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
	auto *program = program_basic;
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

void Window::DrawCircle(const b2Vec2 &center, float radius, const b2Color &color) {
	auto *program = program_basic;
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

void Window::DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color) {
	auto *program = program_basic;
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

void Window::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {
	auto *program = program_basic;
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

void Window::DrawTransform(const b2Transform &xf) {
	DrawSegment(xf.p, xf.p + matrix[3][3] * 100 * b2Vec2(xf.q.c, xf.q.s), b2Color(0, 0, 0, 1));
	DrawSegment(xf.p, xf.p + matrix[3][3] * 100 * b2Vec2(-xf.q.s, xf.q.c), b2Color(0, 0, 0, 1));
}

void Window::DrawPoint(const b2Vec2 &p, float size, const b2Color &color) {
	DrawSolidCircle(p, size * matrix[3][3], b2Vec2(0, 0), color);
}

glm::vec2 Window::getMousePos() {
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	xpos = xpos * 2 / width - 1;
	ypos = 1 - ypos * 2 / height;
	return glm::vec2(xpos, ypos);
}

void Window::FramebufferSizeCallback(int width, int height) {
	matrix[0][0] = 2.0f / width;
	matrix[1][1] = 2.0f / height;
	glViewport(0, 0, width, height);
	updateFramebuffer(width, height);
	// render(window);
	glfwPostEmptyEvent();
}

void Window::MouseButtonCallback(int button, int action, int mods) {
	switch (action) {
	case GLFW_PRESS: {
		switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT: {
			switch (Global::getInstance().stage) {
			default:
			case Global::Stage::Running: {
				prevMousePos = getMousePos();
				LBDown = true;
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
}

void Window::CursorPosCallback(double xpos, double ypos) {
	switch (Global::getInstance().stage) {
	default:
	case Global::Stage::Running: {
		if (LBDown) {
			glm::vec2 pos = getMousePos();
			glm::vec2 delta = pos - prevMousePos;
			glm::mat4x4 t(1);
			t[3][0] = delta.x;
			t[3][1] = delta.y;
			matrix = t * matrix;
			prevMousePos = pos;
			glfwPostEmptyEvent();
		}
		break;
	}
	case Global::Stage::Paused: {
		break;
	}
	}
}

void Window::ScrollCallback(double xoffset, double yoffset) {
	switch (Global::getInstance().stage) {
	defualt:
	case Global::Stage::Running: {
		auto pos = getMousePos();
		glm::mat4x4 t(1), rt(1), m(1);
		t[3][0] = pos.x;
		t[3][1] = pos.y;
		rt[3][0] = -pos.x;
		rt[3][1] = -pos.y;
		double offset = yoffset != 0 ? yoffset : xoffset;
		m[3][3] = offset > 0 ? 1.1f : 1.0f / 1.1f;
		matrix = t * m * rt * matrix;
		glfwPostEmptyEvent();
		break;
	}
	case Global::Stage::Paused: {
		break;
	}
	}
}

void Window::KeyCallback(int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_ESCAPE: {
		switch (action) {
		case GLFW_PRESS: {
			if (Global::getInstance().stage == Global::Stage::Running) {
				Global::getInstance().stage = Global::Stage::Paused;
				LBDown = false;
			}
			else {
				Global::getInstance().stage = Global::Stage::Running;
			}
			glfwPostEmptyEvent();
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
}
