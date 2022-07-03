#pragma once
#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <thread>

namespace engine {
class BasicTimerServer {
public:
    BasicTimerServer() {
    }
    ~BasicTimerServer() {
    }

public:
    virtual boost::asio::io_service &io_service() = 0;
    virtual void                     add()        = 0;
    virtual void                     remove()     = 0;
};

class CommonTimerServer : public BasicTimerServer {
public:
    CommonTimerServer() {
        count     = 0;
        io_thread = nullptr;
    }
    ~CommonTimerServer() {
    }
    boost::asio::io_service &io_service() {
        return ios;
    }
    void add() {
        if (count == 0) {
            io_thread = new std::thread([this]() {
                this->ios.run();
            });
            io_thread->detach();
        }
        ++count;
    }
    void remove() {
        --count;
        if (count == 0) {
            delete io_thread;
        }
    }

protected:
    boost::asio::io_service ios;
    int                     count;
    std::thread            *io_thread;
};

class DefaultTimerServer : public CommonTimerServer {
private:
    DefaultTimerServer() {
        count     = 0;
        io_thread = nullptr;
    }

public:
    ~DefaultTimerServer() {
    }
    static DefaultTimerServer &getInstance() {
        static DefaultTimerServer instance;
        return instance;
    }
};

class Timer {
    typedef std::chrono::steady_clock::duration duration_type;

public:
    Timer(const duration_type &duration    = std::chrono::seconds(1),
          BasicTimerServer    &timerServer = DefaultTimerServer::getInstance());
    ~Timer();
    void                setDuration(const duration_type &duration);
    const duration_type duration();
    void        setCallbackFunc(const std::function<void(void)> &callbackFunc);
    void        start();
    void        start(const duration_type &duration);
    void        stop();
    static void handler(const boost::system::error_code &e, Timer *which);

protected:
    boost::asio::steady_timer timer;
    duration_type             m_duration;
    bool                      running;
    std::function<void(void)> callbackFunc;
    BasicTimerServer         &timerserver;
};
} // namespace engine