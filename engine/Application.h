#pragma once
#include <vector>

namespace engine {
class Window;

class Application {
    friend class Window;

private:
    Application();
    bool gladLoaded;
    void loadGlad();
    bool freeTypeLoaded;
    void loadFreeType();

public:
    ~Application();
    static Application &getInstance();
    void                run();
    void                windowHint(int hint, int value);

protected:
    std::vector<Window *> windowQueue;
};
} // namespace engine