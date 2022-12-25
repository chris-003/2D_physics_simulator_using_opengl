#pragma once
#include "STimer.h"
#include "STimerQueue.h"

namespace engine {
template<typename clock_t>
SBaseTimer<clock_t>::SBaseTimer(const time_point_t &deadline, bool singleShot)
    : m_deadline(deadline), m_interval(deadline - clock_t::now()),
      m_singleShot(singleShot), m_running(false) {
}

template<typename clock_t>
SBaseTimer<clock_t>::SBaseTimer(const duration_t &interval, bool singleShot)
    : m_deadline(clock_t::now() + interval), m_interval(interval),
      m_singleShot(singleShot), m_running(false) {
}

template<typename clock_t>
SBaseTimer<clock_t>::~SBaseTimer() {
    if (isRunning()) {
        stop();
    }
}

template<typename clock_t>
const SBaseTimer<clock_t>::time_point_t &SBaseTimer<clock_t>::deadline() const {
    return m_deadline;
}

template<typename clock_t>
void SBaseTimer<clock_t>::setDeadline(const time_point_t &deadline) {
    m_deadline = deadline;
}
template<typename clock_t>
void SBaseTimer<clock_t>::setDeadline(const duration_t &duration) {
    m_deadline = clock_t::now() + duration;
}

template<typename clock_t>
const SBaseTimer<clock_t>::duration_t &SBaseTimer<clock_t>::timeLeft() const {
    if (m_deadline < clock_t::now()) {
        return m_deadline - m_deadline;
    }
    // else
    return m_deadline - clock_t::now();
}

template<typename clock_t>
const SBaseTimer<clock_t>::duration_t &SBaseTimer<clock_t>::interval() const {
    return m_interval;
}

template<typename clock_t>
void SBaseTimer<clock_t>::setInterval(const duration_t &interval) {
    m_interval = interval;
}

template<typename clock_t>
void SBaseTimer<clock_t>::start() {
    if (!m_running) {
        static STimerQueue &timerQueue = STimerQueue::getInstance();
        timerQueue.push_back(this);
        m_running = true;
    }
}

template<typename clock_t>
void SBaseTimer<clock_t>::stop() {
    if (m_running) {
        static STimerQueue &timerQueue = STimerQueue::getInstance();
        for (auto i = timerQueue.begin(); i != timerQueue.end(); ++i) {
            if (*i == this) {
                timerQueue.erase(i--);
            }
        }
        m_running = false;
    }
}

template<typename clock_t>
bool SBaseTimer<clock_t>::isRunning() {
    return m_running;
}

template<typename clock_t>
void SBaseTimer<clock_t>::emitTimeout() {
    emit(Signal(0));
    if (!m_singleShot) {
        m_deadline                     = clock_t::now() + m_interval;
        static STimerQueue &timerQueue = STimerQueue::getInstance();
        timerQueue.push_back(this);
    }
}

template<typename clock_t>
bool SBaseTimer<clock_t>::isTimeout() {
    return m_deadline <= clock_t::now();
}
} // namespace engine
