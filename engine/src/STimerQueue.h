#pragma once
#include "SAbstractTimer.h"
#include <queue>

namespace engine {
class STimerQueue : public std::deque<SAbstractTimer *> {
protected:
    typedef std::deque<SAbstractTimer *> Container;

private:
    STimerQueue();

public:
    ~STimerQueue();

public:
    static STimerQueue &getInstance();
};
} // namespace engine