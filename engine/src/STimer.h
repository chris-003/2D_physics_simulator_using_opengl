#pragma once
#include "SAbstractTimer.h"

namespace engine {
template<typename clock_t>
class SBaseTimer : public SAbstractTimer {
public:
    typedef clock_t::time_point time_point_t;
    typedef clock_t::duration   duration_t;

public:
    SBaseTimer(const time_point_t &deadline, bool singleShot = false);
    SBaseTimer(const duration_t &interval, bool singleShot = false);
    ~SBaseTimer();

public:
    const time_point_t &deadline() const;
    void                setDeadline(const time_point_t &deadline);
    void                setDeadline(const duration_t &duration);
    const duration_t   &timeLeft() const;
    const duration_t   &interval() const;
    void                setInterval(const duration_t &interval);

public:
    virtual void start();
    virtual void stop();
    virtual bool isRunning();
    virtual void emitTimeout();

public:
    virtual bool isTimeout();

protected:
protected:
    time_point_t m_deadline;
    duration_t   m_interval;
    bool         m_singleShot;
    bool         m_running;
};

typedef SBaseTimer<std::chrono::steady_clock> STimer;
} // namespace engine

#include "STimer.hpp"
