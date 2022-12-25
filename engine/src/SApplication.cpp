#include "SApplication.h"
#include "Opengl.h"
#include "SRenderText.h"
#include "SWindow.h"
#include <chrono>
// #include <ft2build.h>
#include "STimerQueue.h"
#include "SWindowQueue.h"
#include <iostream>
#include <thread>
// #include FT_FREETYPE_H

namespace engine {
// SApplication::SApplication() : openGLLoaded(false) /*,
// freeTypeLoaded(false)*/ {
//     // glfwInit();
//     // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//     // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
//     // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// }

void SApplication::loadOpenGL() {
    static bool openGLLoaded = false;
    if (!openGLLoaded) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glbinding::Binding::initialize(nullptr);
        openGLLoaded = true;
        // glfwSwapInterval(1);
    }
}

#if 0
void SApplication::loadFreeType() {
    // #error
    if (!freeTypeLoaded) {
        loadOpengl();
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
#endif

SApplication::~SApplication() {
}

// SApplication &SApplication::getInstance() {
//     static SApplication instance;
//     return instance;
// }

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

void SApplication::run(const std::chrono::steady_clock::duration &interval) {
    bool                  shouldExit = false;
    auto                  prev       = std::chrono::steady_clock::now();
    std::function<void()> wait       = []() {
    };
    if (std::chrono::duration_cast<std::chrono::nanoseconds>(interval)
            .count() != 0) {
        wait = [&interval, &prev]() {
            std::this_thread::sleep_until(prev + interval);
        };
    }
    while (!shouldExit) {
        auto end = std::chrono::steady_clock::now();
        if (!windowPass() && !timerPass()) {
            shouldExit = true;
        }
        wait();
        prev = end;
    }
}

void SApplication::windowHint(int hint, int value) {
    glfwWindowHint(hint, value);
}

bool SApplication::windowPass() {
    static auto &windowQueue = SWindowQueue::getInstance();
    if (windowQueue.empty()) {
        return false;
    }
    for (auto iter = windowQueue.begin(); iter != windowQueue.end(); ++iter) {
        glfwMakeContextCurrent((*iter)->window());
        if (glfwWindowShouldClose((*iter)->window())) {
            (*iter)->terminate();
            --iter;
        }
        else {
            // glfwMakeContextCurrent((*iter)->window());
            (*iter)->render();
            // printFPS();
            glfwSwapBuffers((*iter)->window());
            glfwPollEvents();
        }
    }
    return true;
}

bool SApplication::timerPass() {
    static STimerQueue &timerQueue = STimerQueue::getInstance();
    if (timerQueue.empty()) {
        return false;
    }
    for (auto i = timerQueue.begin(); i != timerQueue.end();) {
        if ((*i)->isTimeout()) {
            i = timerQueue.erase(i);
            (*i)->emitTimeout();
        }
        else {
            ++i;
        }
    }
    return true;
}
} // namespace engine