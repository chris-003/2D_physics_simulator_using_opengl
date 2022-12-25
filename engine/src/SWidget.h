#pragma once
#include "SFramebuffer.h"
#include "SObject.h"
#include "STree.h"
#include "input.h"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace engine {
class SWindow;

class SWidget : public SObject {
    friend class SWindow;

public:
    enum class Signals {
        Move,        // void (int x, int y);
        Size,        // void (int width, int height);
        MouseMove,   // void (int x, int y);
        MouseButton, // void (int x, int y, enum MouseButton button, enum
                     // ButtonAction action, Modifier mods);
        MouseScroll, // void (int x, int y, double xoffset, double yoffset);
        // MouseIn,     // void ();
        // MouseOut,    // void ();
        Keyboard, // void (enum Key key, int scancode, enum ButtonAction action,
                  // Modifier mods);
        ParentMove, // void (int dx, int dy) emit after parent is moved
        Last = ParentMove
    };

public:
    SWidget(SWidget          *parent   = nullptr,
            const glm::ivec4 &geometry = glm::ivec4(0, 0, 0, 0),
            bool visible = true, bool focusable = true);
    // SWidget(SWindow          *parent,
    //         const glm::ivec4 &geometry = glm::ivec4(0, 0, 0, 0),
    //         bool visible = true, bool focusable = true);
    virtual ~SWidget();

protected:
    // ONLY render *this and ignore the contents of children's
    // if you want to update the widget with its children, please use
    // SWidget::window()->render()
    virtual void render(SFramebuffer &fbo);

    // public:
    //     bool containMouse();

public:
    // virtual void FramebufferSizeCallback(int width, int height);
    // virtual void MouseButtonCallback(int button, int action, int mods);
    // virtual void CursorPosCallback(double xpos, double ypos);
    // virtual void ScrollCallback(double xoffset, double yoffset);
    // virtual void KeyCallback(int key, int scancode, int action, int mods);
    virtual void MouseMoveEvent(int x, int y, bool &blocked);
    virtual void MouseButtonEvent(int x, int y, MouseButton button,
                                  ButtonAction action, Modifier mods,
                                  bool &blocked);
    virtual void MouseScrollEvent(int x, int y, double xoffset, double yoffset,
                                  bool &blocked);
    virtual void KeyboardEvent(Key key, int scancode, ButtonAction action,
                               Modifier mods, bool &blocked);
    virtual void ParentMoveEvent(int dx, int dy);

public:
    SWindow       *window();
    const SWindow *window() const;
    SWidget       *parent() const;
    void           setParent(SWidget *parent = nullptr);
    // void           attachTo(SWindow *window = nullptr);

public:
    glm::ivec2 local2absolute(const glm::ivec2 &pos) const;
    glm::ivec2 absolute2local(const glm::ivec2 &pos) const;

public:
    glm::ivec2 GetLocalMousePos() const;
    glm::ivec2 GetAbsoluteMousePos() const;
    bool       visible() const;
    void       setVisible(bool visible);
    // bool              focusable() const;
    // void              setFocusable(bool focusable);
    glm::ivec4 geometry() const;
    void       setGeometry(const glm::ivec4 &geometry);
    glm::ivec2 pos() const;
    void       move(const glm::ivec2 &pos);
    int        x() const;
    void       setX(int x);
    int        y() const;
    void       setY(int y);
    glm::ivec2 size() const;
    void       resize(const glm::ivec2 &size);
    int        width() const;
    void       setWidth(int width);
    int        height() const;
    void       setHeight(int height);
    glm::ivec2 rightBottomPos() const;
    void       setRightBottomPos(const glm::ivec2 &pos);
    int        rightBottomX() const;
    void       setRightBottomX(int x);
    int        rightBottomY() const;
    void       setRightBottomY(int y);

private:
    // SWindow  *_parent;
    STree<SWidget *> widgetTree;
    glm::ivec4       geo;
    glm::ivec2       absolutePos;
    bool             _visible;
    // bool             _focusable;

private:
    // works only if parent is an instance of SWindow
    SWindow *m_window;
    // always works, if parent is nullptr, m_pWindow -> m_window,
    // if parent is not nullptr, m_pWindow := parent->m_window, which eventually
    // pointed to the root's m_window which pointed to an instance of SWindow
    // (or nullptr if the root does NOT attatched to any SWindow)
    SWindow **m_pWindow;

private:
    // bool m_prevIn;
    // void private_MoveSlot(int x, int y);
    // void private_SizeSlot(int width, int height);
    void private_MouseMoveEvent(int x, int y, bool &blocked);
    void private_MouseButtonEvent(int x, int y, MouseButton button,
                                  ButtonAction action, Modifier mods,
                                  bool &blocked);
    void private_MouseScrollEvent(int x, int y, double xoffset, double yoffset,
                                  bool &blocked);
    void private_KeyboardEvent(Key key, int scancode, ButtonAction action,
                               Modifier mods, bool &blocked);
    void private_ParentMoveEvent(int dx, int dy);
    void private_emit_PrarentMoveEvent(int dx, int dy);
    void private_fullRender(SFramebuffer &fbo);
};
} // namespace engine
