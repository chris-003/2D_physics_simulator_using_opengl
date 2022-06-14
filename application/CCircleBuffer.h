#pragma once
#include <array>
#include <box2d/box2d.h>

template<int N = 256>
class CCircleBuffer {
private:
	CCircleBuffer();
public:
	~CCircleBuffer();
	static CCircleBuffer<N> &getInstance();
public:
	const b2Vec2 &operator[](int ind);
protected:
	std::array<b2Vec2, N> buf;
};

template<int N>
inline CCircleBuffer<N>::CCircleBuffer() {
	const float pi = 3.1415926536f;
	for (int i = 0; i < N; ++i) {
		float theta = pi * 2 * i / N;
		buf[i].x = cos(theta);
		buf[i].y = sin(theta);
	}
}

template<int N>
inline CCircleBuffer<N>::~CCircleBuffer() {
}

template<int N>
inline CCircleBuffer<N> &CCircleBuffer<N>::getInstance() {
	static CCircleBuffer<N> instance;
	return instance;
}

template<int N>
inline const b2Vec2 &CCircleBuffer<N>::operator[](int ind) {
	return buf[ind];
}
