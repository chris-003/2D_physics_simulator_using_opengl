#include "MainWindow.h"
// #include "Button_1.h"
#include "CCircleBuffer.h"
#include "CNormalDistBuffer.h"
#include "Global.h"
// #include "Resource.h"
#include "World.h"
#include "stb_image"
#include <QFile>
#include <array>
#include <iostream>

using engine::SFramebuffer;
using engine::SShader;
using engine::SShaderProgram;
using engine::SVertexArray;
using engine::SVertexBuffer;
using std::cout;
using std::endl;

MainWindow::MainWindow() : engine::SWindow(glm::vec2(800, 600), "Simulator") {
    init();
    mainWidget.reset(new MainWidget(this));
    mainWidget->setGeometry(glm::vec4(0, 0, 800, 600));
    button_1.reset(new engine::SButton(this));
    button_1->setGeometry(glm::vec4(400, 0, 800, 300));
    button_1->setVisible(false);
    button_1->connect(engine::SObject::Signal(0), []() {
        static unsigned int                          cnt = 0;
        static std::chrono::steady_clock::time_point prev =
            std::chrono::steady_clock::now();
        cout << "button clicked the " << ++cnt << " times!";
        if (cnt != 1) {
            auto now      = std::chrono::steady_clock::now();
            auto duration = now - prev;
            auto mscnt =
                std::chrono::duration_cast<std::chrono::milliseconds>(duration)
                    .count();
            cout << " " << (1000.0f / mscnt) << " cps.";
            prev = now;
        }
        cout << endl;
    });
}

void MainWindow::init() {
    glfwMakeContextCurrent(window());

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    // auto &resource = Resource::getInstance();
    // program_basic.reset(
    //     new SShaderProgram(resource.basic_vert(), resource.basic_frag()));
    // program_blur7_pingpong_h.reset(new SShaderProgram(
    //     resource.blur7_pingpong_h_vert(), resource.blur7_pingpong_h_frag()));
    // program_blur7_pingpong_v.reset(new SShaderProgram(
    //     resource.blur7_pingpong_v_vert(), resource.blur7_pingpong_v_frag()));
    // program_blurN_pingpong_h.reset(new SShaderProgram(
    //     resource.blurN_pingpong_h_vert(), resource.blurN_pingpong_h_frag()));
    // program_blurN_pingpong_v.reset(new SShaderProgram(
    //     resource.blurN_pingpong_v_vert(), resource.blurN_pingpong_v_frag()));
    // program_copy_texture.reset(new SShaderProgram(
    //     resource.copy_texutre_vert(), resource.copy_texture_frag()));
    program_basic.reset(
        new SShaderProgram(QFile(":/Shaders/basic.vert").readAll().data(),
                           QFile(":/Shaders/basic.frag").readAll().data()));
    program_blur7_pingpong_h.reset(new SShaderProgram(
        QFile(":/Shaders/blur7_pingpong_h.vert").readAll().data(),
        QFile(":/Shaders/blur7_pingpong_h.frag").readAll().data()));
    program_blur7_pingpong_v.reset(new SShaderProgram(
        QFile(":/Shaders/blur7_pingpong_v.vert").readAll().data(),
        QFile(":/Shaders/blur7_pingpong_v.frag").readAll().data()));
    program_blurN_pingpong_h.reset(new SShaderProgram(
        QFile(":/Shaders/blurN_pingpong_h.vert").readAll().data(),
        QFile(":/Shaders/blurN_pingpong_h.frag").readAll().data()));
    program_blurN_pingpong_v.reset(new SShaderProgram(
        QFile(":/Shaders/blurN_pingpong_v.vert").readAll().data(),
        QFile(":/Shaders/blurN_pingpong_v.frag").readAll().data()));
    program_copy_texture.reset(new SShaderProgram(
        QFile(":/Shaders/copy_texture.vert").readAll().data(),
        QFile(":/Shaders/copy_texture.frag").readAll().data()));

    {
        vbo_button_1.reset(new SVertexBuffer);
        vao_button_1.reset(new SVertexArray);
        auto vao = engine::make_SBindHelper(vao_button_1);
        auto vbo = engine::make_SBindHelper(vbo_button_1);
        vao->enable(0, 2, 0);
        vao->enable(1, 2, 2 * sizeof(float));
        vao->bindingPoint(0, 0);
        vao->bindingPoint(1, 0);
        vao->bindVBO(0, *vbo, 0, 4 * sizeof(float));
        {
            struct Point {
                float x, y, tx, ty;
            } points[4] = {
                {1, 1, 1, 1}, {0, 1, 0.5, 1}, {0, 0, 0.5, 0.5}, {1, 0, 1, 0.5}};
            vbo->write(sizeof(points), points, GL_STATIC_DRAW);
        }
    }
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
    // 	int            width, height, nrChannels;
    // 	unsigned char *data =
    // 		stbi_load("image.jpeg", &width, &height, &nrChannels, 0);
    // 	if (data) {
    // 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
    // 						GL_UNSIGNED_BYTE, data);
    // 		glGenerateMipmap(GL_TEXTURE_2D);
    // 	}
    // 	else {
    // 		std::cout << "Failed to load texture" << std::endl;
    // 	}
    // 	stbi_image_free(data);
    // }
}

MainWindow::~MainWindow() {
}

void MainWindow::updateFramebuffer(int width, int height) {
    auto updateFbo = [&](std::unique_ptr<SFramebuffer> &fbo) {
        fbo.reset(new SFramebuffer(width, height));
    };
}

void MainWindow::FramebufferSizeCallback(int width, int height) {
    mainWidget->resize(glm::vec2(width, height));
    // glfwPostEmptyEvent();
    engine::SWindow::FramebufferSizeCallback(width, height);
}

void MainWindow::MouseButtonCallback(int button, int action, int mods) {
    // switch (action) {
    // case GLFW_PRESS: {
    // 	switch (button) {
    // 	case GLFW_MOUSE_BUTTON_LEFT: {
    // 		switch (Global::getInstance().stage) {
    // 		default:
    // 		case Global::Stage::Running: {
    // 			prevMousePos = getMousePos();
    // 			LBDown       = true;
    // 			break;
    // 		}
    // 		case Global::Stage::Paused: {
    // 			break;
    // 		}
    // 		}
    // 		break;
    // 	}
    // 	case GLFW_MOUSE_BUTTON_RIGHT: {
    // 		RBDown = true;
    // 		break;
    // 	}
    // 	default:
    // 		break;
    // 	}

    // 	break;
    // }
    // case GLFW_RELEASE: {
    // 	switch (button) {
    // 	case GLFW_MOUSE_BUTTON_LEFT: {
    // 		LBDown = false;
    // 		break;
    // 	}
    // 	case GLFW_MOUSE_BUTTON_RIGHT: {
    // 		RBDown = false;
    // 		break;
    // 	}
    // 	default:
    // 		break;
    // 	}

    // 	break;
    // }
    // default:
    // 	break;
    // }
    engine::SWindow::MouseButtonCallback(button, action, mods);
}

void MainWindow::CursorPosCallback(double xpos, double ypos) {
    // switch (Global::getInstance().stage) {
    // default:
    // case Global::Stage::Running: {
    // 	if (LBDown) {
    // 		glm::vec2   pos   = getMousePos();
    // 		glm::vec2   delta = pos - prevMousePos;
    // 		glm::mat4x4 t(1);
    // 		t[3][0]      = delta.x;
    // 		t[3][1]      = delta.y;
    // 		matrix       = t * matrix;
    // 		prevMousePos = pos;
    // 		glfwPostEmptyEvent();
    // 	}
    // 	break;
    // }
    // case Global::Stage::Paused: {
    // 	break;
    // }
    // }
    engine::SWindow::CursorPosCallback(xpos, ypos);
}

void MainWindow::ScrollCallback(double xoffset, double yoffset) {
    // switch (Global::getInstance().stage) {
    // defualt:
    // case Global::Stage::Running: {
    // 	auto        pos = getMousePos();
    // 	glm::mat4x4 t(1), rt(1), m(1);
    // 	t[3][0]       = pos.x;
    // 	t[3][1]       = pos.y;
    // 	rt[3][0]      = -pos.x;
    // 	rt[3][1]      = -pos.y;
    // 	double offset = yoffset != 0 ? yoffset : xoffset;
    // 	m[3][3]       = offset > 0 ? 1.1f : 1.0f / 1.1f;
    // 	matrix        = t * m * rt * matrix;
    // 	glfwPostEmptyEvent();
    // 	break;
    // }
    // case Global::Stage::Paused: {
    // 	break;
    // }
    // }
    engine::SWindow::ScrollCallback(xoffset, yoffset);
}

void MainWindow::KeyCallback(int key, int scancode, int action, int mods) {
    // switch (key) {
    // case GLFW_KEY_ESCAPE: {
    // 	switch (action) {
    // 	case GLFW_PRESS: {
    // 		if (Global::getInstance().stage == Global::Stage::Running) {
    // 			Global::getInstance().stage = Global::Stage::Paused;
    // 			LBDown                      = false;
    // 			updateBackgroundFbo();
    // 		}
    // 		else {
    // 			Global::getInstance().stage = Global::Stage::Running;
    // 		}
    // 		glfwPostEmptyEvent();
    // 		break;
    // 	}
    // 	default:
    // 		break;
    // 	}
    // 	break;
    // }
    // default:
    // 	break;
    // }
    engine::SWindow::KeyCallback(key, scancode, action, mods);
}
