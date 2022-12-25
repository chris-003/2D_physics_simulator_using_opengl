#pragma once
#include "SObject.h"
#include <chrono>

namespace engine {

// Signal(0) for void timeout();
class SAbstractTimer : public SObject {
public:
    SAbstractTimer();
    ~SAbstractTimer();

public:
    virtual void start()       = 0;
    virtual void stop()        = 0;
    virtual bool isRunning()   = 0;
    virtual void emitTimeout() = 0;

public:
    virtual bool isTimeout() = 0;
};
} // namespace engine