#pragma once
#include <chrono>

namespace engine {
class SWindow;

class SApplication {
    // friend class SWindow;

private:
    SApplication() = delete;
    // bool openGLLoaded;
#if 0
    bool freeTypeLoaded;
    void loadFreeType();
#endif

public:
    ~SApplication();
    static void          loadOpenGL();
    static SApplication &getInstance();
    static void run(const std::chrono::steady_clock::duration &interval =
                        std::chrono::milliseconds(1));
    static void windowHint(int hint, int value);

protected:
    static bool windowPass();
    static bool timerPass();

protected:
};
} // namespace engine