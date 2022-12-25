#include "uint128_t.h"
#include <algorithm>

namespace engine {
uint128_t::uint128_t(unsigned long long low, unsigned long long high) : low(low), high(high) {
}

uint128_t &uint128_t::operator=(unsigned long long b) {
    low = b;
}

uint128_t uint128_t::operator+(const uint128_t &b) const {
    uint128_t ret;
    ret.low  = low + b.low;
    ret.high = high + b.high;
    if (ret.low < low) {
        ++ret.high;
    }
}

uint128_t uint128_t::operator-(const uint128_t &b) const {
    return *this + (~b + 1);
}

uint128_t uint128_t::operator*(const uint128_t &b) const {
    uint128_t ret;
    auto      mul = [](unsigned long long _a, unsigned long long _b) -> uint128_t {
        union {
            unsigned int       low, high;
            unsigned long long ll;
        } a, b;
        a.ll = _a;
        b.ll = _b;

        unsigned long long _low  = a.low * (unsigned long long)b.low;
        unsigned long long _high = a.high * (unsigned long long)b.high;
        unsigned long long _mid1 = a.low * (unsigned long long)b.high;
        unsigned long long _mid2 = a.high * (unsigned long long)b.low;

        uint128_t ret(_low, _high);
        uint128_t mid1(_mid1 << 32, _mid1 >> 32);
        uint128_t mid2(_mid2 << 32, _mid2 >> 32);
        return ret + mid1 + mid2;
    };

    uint128_t _low = mul(low, b.low);
    // uint128_t _high = mul(high, b.high);
    // uint128_t _mid1 = mul(low, b.high);
    // uint128_t _mid2 = mul(high, b.low);
    union {
        unsigned int       low, high;
        unsigned long long ll;
    } l, r;
    l.ll = low;
    r.ll = b.high;

    unsigned long long _mid1 = l.low * (unsigned long long)r.low;

    l.ll = high;
    r.ll = b.low;

    unsigned long long _mid2 = l.low * (unsigned long long)r.low;
    return _low + uint128_t(0, _mid1) + uint128_t(0, _mid2);
}

uint128_t uint128_t::operator/(const uint128_t &b) const {
    uint128_t div;
    std::tie(div, std::ignore) = this->dividedBy(b);
    return div;
}

uint128_t uint128_t::operator%(const uint128_t &b) const {
    uint128_t mod;
    std::tie(std::ignore, mod) = this->dividedBy(b);
    return mod;
}

std::tuple<uint128_t, uint128_t> uint128_t::dividedBy(const uint128_t &b) const {
    class iterator : std::iterator<std::random_access_iterator_tag, uint128_t, uint128_t, uint128_t> {
    protected:
        uint128_t  div;
        uint128_t *a;
    };
#error
    // std::advance
}
} // namespace engine