#include "Timer.h"
#include <boost/bind.hpp>

namespace engine {
    Timer::Timer(const duration_type &duration, BasicTimerServer &timerServer) : timer(timerServer.io_service(), duration), timerserver(timerServer) {
        m_duration = duration;
        running = false;
    }

    Timer::~Timer() {
        timer.cancel();
    }

    void Timer::setDuration(const duration_type &duration) {
        m_duration = duration;
        timer.expires_after(duration);
    }

    const Timer::duration_type Timer::duration() {
        return m_duration;
    }

    void Timer::setCallbackFunc(const std::function<void(void)> &callbackFunc) {
        this->callbackFunc = callbackFunc;
    }

    void Timer::start() {
        // if (running) {
        //     stop();
        // }
        // running = true;
        // timer.expires_from_now(m_duration);
        // timer.async_wait(boost::bind(handler, boost::placeholders::_1, this));
        start(m_duration);
    }

    void Timer::start(const duration_type &duration) {
        if (running) {
            stop();
        }
        m_duration = duration;
        running = true;
        timer.expires_from_now(m_duration);
        timer.async_wait(boost::bind(handler, boost::placeholders::_1, this));
        // if (count == 0) {
        //     io_thread = new std::thread([&ios](){
        //         ios.run();
        //     });
        //     io_thread->detach();
        // }
        // ++count;
        timerserver.add();
        // if (io_thread == nullptr) {
        //     io_thread = new std::thread([&ios](){
        //         while (true) {
        //             ios.run();
        //         }
        //     });
        // }
    }

    void Timer::stop() {
        running = false;
        timer.cancel();
        // --count;
        // if (count == 0) {
        //     delete io_thread;
        // }
        timerserver.remove();
    }

    void Timer::handler(const boost::system::error_code &e, Timer *which) {
        if(!e.failed()) {
            which->callbackFunc();
            if (which->running) {
                which->timer.expires_from_now(which->m_duration);
                which->timer.async_wait(boost::bind(handler, boost::placeholders::_1, which));
            }
        }
    }
}