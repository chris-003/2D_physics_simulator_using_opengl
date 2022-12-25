#pragma once
#include <vector>

namespace engine {
class SWindow;
class SWindowQueue : public std::vector<SWindow *> {
private:
    SWindowQueue();

public:
    ~SWindowQueue();

public:
    static SWindowQueue &getInstance();
};
} // namespace engine