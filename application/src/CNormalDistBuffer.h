#pragma once
#include <array>
#include <cmath>
#include <iostream>

template<int N>
class CNormalDistBuffer {
private:
    CNormalDistBuffer();

public:
    ~CNormalDistBuffer();
    static CNormalDistBuffer<N> &getInstance();
    const float                 *buffer() const;

protected:
    std::array<float, N> buf;
};

template<int N>
CNormalDistBuffer<N>::CNormalDistBuffer() {
    float step = 3.0f / (N - 1);
    float x    = 0;
    float sum  = 0;
    for (int i = 0; i < N; ++i) {
        buf[i] = 1.0f * expf(-(x * x / 2.0f)) / sqrtf(2 * M_PI);
        sum += 2 * buf[i];
        x += step;
    }
    sum = sum - buf[0];
    for (int i = 0; i < N; ++i) {
        buf[i] = buf[i] / sum;
    }
}

template<int N>
CNormalDistBuffer<N>::~CNormalDistBuffer() {
}

template<int N>
CNormalDistBuffer<N> &CNormalDistBuffer<N>::getInstance() {
    static CNormalDistBuffer<N> instance;
    return instance;
}

template<int N>
const float *CNormalDistBuffer<N>::buffer() const {
    return buf.data();
}