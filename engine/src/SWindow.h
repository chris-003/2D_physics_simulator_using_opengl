#pragma once
#include "Opengl.h"
#include "STree.h"
#include <glm/vec2.hpp>
#include <memory>
#include <string>
#include <vector>

namespace engine {
class SApplication;
class SWidget;

class SWindow {
    friend class SApplication;
    friend class SWidget;

public:
    SWindow();
    ~SWindow();
    void create(const glm::ivec2  &size  = glm::ivec2(800, 600),
                const std::string &title = "Title");
    template<typename T>
    void create(const glm::ivec2  &size  = glm::ivec2(800, 600),
                const std::string &title = "Title");

    // void        create(const glm::ivec2 &size, const std::string &title,
    //                    std::shared_ptr<SWidget> &mainWidget);
    GLFWwindow *window();
    bool        running() const;

public:
    // void      addWidget(SWidget *widget);
    // void      removeWidget(SWidget *widget);
    // bool      isWidget(SWidget *widget);
    // SWidget  *focus();
    // void      setFocus(SWidget *widget);
    glm::vec2 size();
    void      setMainWidget(std::shared_ptr<SWidget> &widget);

public:
    virtual void FramebufferSizeCallback(int width, int height);
    virtual void MouseButtonCallback(int button, int action, int mods);
    virtual void CursorPosCallback(double xpos, double ypos);
    virtual void ScrollCallback(double xoffset, double yoffset);
    virtual void KeyCallback(int key, int scancode, int action, int mods);

public:
    static SWindow *map(GLFWwindow *window);

private:
    static void FramebufferSizeCallbackHelper(GLFWwindow *window, int width,
                                              int height);
    static void MouseButtonCallbackHelper(GLFWwindow *window, int button,
                                          int action, int mods);
    static void CursorPosCallbackHelper(GLFWwindow *window, double xpos,
                                        double ypos);
    static void ScrollCallbackHelper(GLFWwindow *window, double xoffset,
                                     double yoffset);
    static void KeyCallbackHelper(GLFWwindow *window, int key, int scancode,
                                  int action, int mods);

public:
    virtual void render();
    // virtual void init();
    void terminate();

private:
    // void try_changeFocus(SWidget *w);
    // bool m_prevIn;

protected:
    // std::vector<SWidget *> widgetTree;
    GLFWwindow *_window;
    // SWidget    *_focus;
    glm::ivec2               _size;
    std::shared_ptr<SWidget> m_mainWidget;
    bool                     m_running;
};
} // namespace engine

#include "SWindow.hpp"