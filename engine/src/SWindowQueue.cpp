#include "SWindowQueue.h"

namespace engine {
SWindowQueue::SWindowQueue() {
}

SWindowQueue::~SWindowQueue() {
}

SWindowQueue &SWindowQueue::getInstance() {
    static SWindowQueue instance;
    return instance;
}
} // namespace engine