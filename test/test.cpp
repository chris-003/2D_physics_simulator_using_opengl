#if 0
// #include "glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glbinding/Binding.h>
#include <glbinding/gl/gl.h>
// #include <GLFW/glfw3native.h>
#include <chrono>
#include <iostream>
using namespace gl;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;
unsigned int       width(SCR_WIDTH), height(SCR_HEIGHT);
const char        *geometryShaderSource = R"(
#version 450 core
layout (points) in;
layout (triangle_strip, max_vertices = 6) out;

layout (location = 0) out vec2 center;
layout (location = 1) out float radius;

void main() {
    radius = gl_in[0].gl_Position.z;
    center = gl_in[0].gl_Position.xy;
    vec2 r = vec2(radius, radius);
    vec2 c = center;
    gl_Position = vec4(c + r, 0, 1);
    EmitVertex();
    r.x *= -1.0f;
    gl_Position = vec4(c + r, 0, 1);
    EmitVertex();
    r.y *= -1.0f;
    gl_Position = vec4(c + r, 0, 1);
    EmitVertex();

    gl_Position = vec4(c + r, 0, 1);
    EmitVertex();
    r.x *= -1.0f;
    gl_Position = vec4(c + r, 0, 1);
    EmitVertex();
    r.y *= -1.0f;
    gl_Position = vec4(c + r, 0, 1);
    EmitVertex();
    
    EndPrimitive();
})";
const char        *vertexShaderSource   = R"(
#version 450 core
layout (location = 0) in vec2 cen;
layout (location = 1) in float ra;

void main() {
    gl_Position = vec4(cen, ra, 1);
})";
const char        *fragmentShaderSource = R"(
#version 450 core
out vec4 FragColor;
layout (location = 0) in vec2 center;
layout (location = 1) in float radius;
layout (location = 2) uniform vec2 wh;

void main() {
    vec2 coord = gl_FragCoord.xy;
    coord.x /= wh.x / 2.0f;
    coord.y /= wh.y / 2.0f;
    coord -= vec2(1, 1);
    if (length(coord - center) <= radius) {
        FragColor = vec4(1, 1, 1, 1);
    }
    else {
        FragColor = vec4(0, 0, 0, 1);
    }
}
)";

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window =
        glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    // {
    //     std::cout << "Failed to initialize GLAD" << std::endl;
    //     return -1;
    // }
    glbinding::Binding::initialize(nullptr);

    auto check = [](GLuint shader) -> void {
        int  success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << "ERROR: Shader Compilation failed.\n"
                      << infoLog << std::endl;
        }
    };
    unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &geometryShaderSource, nullptr);
    glCompileShader(geometryShader);
    check(geometryShader);
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    check(vertexShader);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    check(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, geometryShader);
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR: ShaderProgram Link failed.\n"
                  << infoLog << std::endl;
    }

    unsigned int vbo;
    glCreateBuffers(1, &vbo);
    unsigned int vao;
    glCreateVertexArrays(1, &vao);
    glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribFormat(vao, 1, 1, GL_FLOAT, GL_FALSE, 2 * sizeof(float));
    glVertexArrayAttribBinding(vao, 0, 0);
    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribBinding(vao, 1, 0);
    glEnableVertexArrayAttrib(vao, 1);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3 * sizeof(float));
    struct Data {
        float x, y, r;
    } data[1] = {{0, 0, 1}};
    glNamedBufferData(vbo, sizeof(data), data, GL_STATIC_DRAW);

    GLuint fbo1, fbo2;
    glCreateFramebuffers(1, &fbo1);
    glCreateFramebuffers(1, &fbo2);
    GLuint texture1, texture2;
    glCreateTextures(GL_TEXTURE_2D, 1, &texture1);
    glCreateTextures(GL_TEXTURE_2D, 1, &texture2);
    glTextureStorage2D(texture1, 1, GL_RGB8, width, height);
    glTextureStorage2D(texture2, 1, GL_RGB8, width, height);
    glTextureParameteri(texture1, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(texture1, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(texture2, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(texture2, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glNamedFramebufferTexture(fbo1, GL_COLOR_ATTACHMENT0, texture1, 0);
    glNamedFramebufferTexture(fbo2, GL_COLOR_ATTACHMENT0, texture2, 0);
    GLuint rbo1, rbo2;
    glCreateRenderbuffers(1, &fbo1);
    glCreateRenderbuffers(1, &fbo2);
    glNamedRenderbufferStorage(rbo1, GL_DEPTH24_STENCIL8, width, height);
    glNamedRenderbufferStorage(rbo2, GL_DEPTH24_STENCIL8, width, height);
    glNamedFramebufferRenderbuffer(fbo1, GL_DEPTH_STENCIL_ATTACHMENT,
                                   GL_RENDERBUFFER, rbo1);
    glNamedFramebufferRenderbuffer(fbo2, GL_DEPTH_STENCIL_ATTACHMENT,
                                   GL_RENDERBUFFER, rbo2);

    auto         start  = std::chrono::steady_clock::now();
    unsigned int frames = 0;
    glfwSwapInterval(1);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glUniform2f(2, width, height);
        glBindBuffer(GL_BUFFER, vbo);
        glBindVertexArray(vao);
        glDrawArrays(GL_POINTS, 0, 1);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse
        // moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        {
            ++frames;
            auto end = std::chrono::steady_clock::now();
            auto duration =
                std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                      start);
            if (duration.count() >= 1000) {
                printf("fps: %.2f", frames * 1000.0f / (float)duration.count());
                std::cout << std::endl;
                frames = 0;
                start  = end;
            }
        }
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width
    // and height will be significantly larger than specified on retina
    // displays.
    ::width  = width;
    ::height = height;
    glViewport(0, 0, width, height);
}
#endif
#if 0

#include "Opengl.h"
#include "SApplication.h"
#include "SWindow.h"
#include <iostream>
#include <memory>

// class B {
// public:
//     B() {
//         static int id = 0;
//         m_id          = id;
//         std::cout << " B()! id = " << id++ << std::endl;
//     }
//     ~B() {
//         std::cout << " ~B()! id = " << m_id << std::endl;
//     }
//     int m_id;
// };

// class A {
// public:
//     A() {
//         static int id = 0;
//         m_id          = id;
//         std::cout << " A()! id = " << id++ << std::endl;
//         {
//             auto ptr = std::shared_ptr<B>(new B);
//             attach(ptr);
//         }
//     }
//     ~A() {
//         std::cout << " ~B()! id = " << m_id << std::endl;
//     }
//     void attach(std::shared_ptr<B> &p) {
//         pB = p;
//     }
//     std::shared_ptr<B> pB;
//     int                m_id;
// };

#include "SShaderProgram.h"
#include "SVertexArray.h"
#include "SVertexBuffer.h"
#include "SWidget.h"

const char *geometryShaderSource = R"(
#version 450 core
layout (points) in;
layout (triangle_strip, max_vertices = 6) out;

layout (location = 0) out vec2 center;
layout (location = 1) out float radius;

void main() {
    radius = gl_in[0].gl_Position.z;
    center = gl_in[0].gl_Position.xy;
    vec2 r = vec2(radius, radius);
    vec2 c = center;
    gl_Position = vec4(c + r, 0, 1);
    EmitVertex();
    r.x *= -1.0f;
    gl_Position = vec4(c + r, 0, 1);
    EmitVertex();
    r.y *= -1.0f;
    gl_Position = vec4(c + r, 0, 1);
    EmitVertex();

    gl_Position = vec4(c + r, 0, 1);
    EmitVertex();
    r.x *= -1.0f;
    gl_Position = vec4(c + r, 0, 1);
    EmitVertex();
    r.y *= -1.0f;
    gl_Position = vec4(c + r, 0, 1);
    EmitVertex();
    
    EndPrimitive();
})";
const char *vertexShaderSource   = R"(
#version 450 core
layout (location = 0) in vec2 cen;
layout (location = 1) in float ra;

void main() {
    gl_Position = vec4(cen, ra, 1);
})";
const char *fragmentShaderSource = R"(
#version 450 core
out vec4 FragColor;
layout (location = 0) in vec2 center;
layout (location = 1) in float radius;
layout (location = 2) in vec4 color;
layout (location = 3) uniform vec2 wh;

void main() {
    vec2 coord = gl_FragCoord.xy;
    coord.x /= wh.x / 2.0f;
    coord.y /= wh.y / 2.0f;
    coord -= vec2(1, 1);
    if (length(coord - center) <= radius) {
        FragColor = color;
    }
    else {
        FragColor = vec4(0, 0, 0, 0);
    }
}
)";

class Widget : public engine::SWidget {
public:
    Widget(engine::SWidget *parent = nullptr) : engine::SWidget(parent) {
        program = std::make_shared<engine::SShaderProgram>(
            engine::SShader(engine::SShader::Type::Geomotry,
                            geometryShaderSource),
            engine::SShader(engine::SShader::Type::Vertex, vertexShaderSource),
            engine::SShader(engine::SShader::Type::Fragment,
                            fragmentShaderSource));
        vao = std::make_shared<engine::SVertexArray>();
        vbo = std::make_shared<engine::SVertexBuffer>();
        // vao->format(0, 2, 0);
        vao->enable(0, 2, 0);
        vao->bindingPoint(0, 0);
        // vao->format(1, 1, 2 * sizeof(float));
        vao->enable(1, 1, 2 * sizeof(float));
        vao->bindingPoint(1, 0);
        vao->enable(2, 4, 3 * sizeof(float));
        vao->bindingPoint(2, 0);
        struct Data {
            float x, y, radius;
            float r, g, b, a;
        } data[2] = {{0.5, 0.5, 0.5, 1, 1, 1, 0.5}, {0, 0, 0.5, 1, 1, 1, 0.5}};
        vbo->write(sizeof(data), data, GL_STATIC_DRAW);
        vao->bindVBO(0, *vbo, 0, 7 * sizeof(float));
    }
    virtual void render(engine::SFramebuffer &fbo) override {
        // static std::chrono::steady_clock::time_point prev =
        //     std::chrono::steady_clock::now();
        // decltype(prev) end = std::chrono::steady_clock::now();
        // if (std::chrono::duration_cast<std::chrono::nanoseconds>(end - prev)
        //         .count() != 0) {
        //     static int frameCnt = 0;
        //     ++frameCnt;
        //     if (frameCnt == 100) {
        //         frameCnt = 0;
        //         auto nano =
        //             std::chrono::duration_cast<std::chrono::nanoseconds>(end
        //             -
        //                                                                  prev)
        //                 .count();
        //         std::cout << "fps: " << (1000000000) / nano << "\n";
        //     }
        // }
        // prev = end;
        fbo.bind();
        glClearColor(1.0f, 0, 0, 1);
        glClear(ClearBufferMask::GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // glClear(ClearBufferMask::GL_COLOR_BUFFER_BIT);
        vbo->bind();
        vao->bind();
        program->bind();
        // glUniform2f(2, width(), height());
        program->setUniform<float>(3, width(), height());
        glDrawArrays(GL_POINTS, 0, 2);
    }

public:
    std::shared_ptr<engine::SShaderProgram> program;
    std::shared_ptr<engine::SVertexArray>   vao;
    std::shared_ptr<engine::SVertexBuffer>  vbo;
};

int main(int argc, const char *argv[]) {
#if 1
    {
        // engine::SApplication &app = engine::SApplication::getInstance();
        engine::SApplication::loadOpenGL();
        engine::SWindow window;
        window.create<Widget>(glm::ivec2(800, 600), "Title");
        // std::shared_ptr<engine::SWidget> pw = std::make_shared<Widget>();
        // window.setMainWidget(pw);
        engine::SApplication::run();
    }
    // sleep(100);
#endif
    // for (int i = 0; i < 10; ++i) {
    //     std::cout << "Loop Begin with i = " << i << std::endl;
    //     A a;
    //     std::cout << "Loop End with i = " << i << std::endl;
    // }
    return 0;
}
#endif

#include <any>
#include <iostream>

int main() {
    // __int12
    return 0;
}