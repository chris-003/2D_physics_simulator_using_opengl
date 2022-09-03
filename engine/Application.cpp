#include "Application.h"
#include "RenderText.h"
#include "Window.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <chrono>
#include <ft2build.h>
#include <iostream>
#include FT_FREETYPE_H

namespace engine {
Application::Application() : gladLoaded(false), freeTypeLoaded(false) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Application::loadGlad() {
    if (!gladLoaded) {
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        gladLoaded = true;
        glfwSwapInterval(1);
    }
}

void Application::loadFreeType() {
    #error
    if (!freeTypeLoaded) {
        loadGlad();
        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library"
                      << std::endl;
        }

        FT_Face face;
        if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face)) {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        }

        FT_Set_Pixel_Sizes(face, 0, 48);

        if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //禁用字节对齐限制
        for (GLubyte c = 0; c < 128; c++) {
            // 加载字符的字形
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph"
                          << std::endl;
                continue;
            }
            // 生成纹理
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                         face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                         face->glyph->bitmap.buffer);
            // 设置纹理选项
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // 储存字符供之后使用
            renderText::Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x};
            renderText::defaultCharacters.emplace(c, character);
            // renderText::defaultCharacters.insert(
            //     std::pair<GLchar, renderText::Character>(c, character));
        }
        // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        freeTypeLoaded = true;
    }
}

Application::~Application() {
}

Application &Application::getInstance() {
    static Application instance;
    return instance;
}

void printFPS() {
    static bool theFirst = true;
    static auto prev     = std::chrono::steady_clock::now();
    if (theFirst) {
        theFirst = false;
        return;
    }
    // else
    auto now = std::chrono::steady_clock::now();
    auto mscnt =
        std::chrono::duration_cast<std::chrono::microseconds>(now - prev)
            .count();
    std::cout << "    " << (1000000.0f / mscnt) << '\n';
    prev = now;
}

void Application::run() {
    while (!windowQueue.empty()) {
        for (auto iter = windowQueue.begin(); iter != windowQueue.end();
             ++iter) {
            if (glfwWindowShouldClose((*iter)->window())) {
                (*iter)->terminate();
                --iter;
            }
            else {
                glfwMakeContextCurrent((*iter)->window());
                (*iter)->render();
                // printFPS();
                glfwSwapBuffers((*iter)->window());
            }
        }
        glfwPollEvents();
    }
}

void Application::windowHint(int hint, int value) {
    glfwWindowHint(hint, value);
}
} // namespace engine