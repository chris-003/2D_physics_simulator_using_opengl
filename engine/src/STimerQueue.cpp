#include "STimerQueue.h"

namespace engine {
STimerQueue::STimerQueue() {
}

STimerQueue::~STimerQueue() {
}

STimerQueue &STimerQueue::getInstance() {
    static STimerQueue instance;
    return instance;
}
} // namespace engine