#pragma once

class Global {
private:
    Global();

public:
    ~Global();
    static Global &getInstance();

public:
    enum class Stage { Running, Paused } stage;
};