#pragma once
#include <compare>
#include <tuple>
#include <type_traits>

namespace engine {
class uint128_t;
} // namespace engine

namespace std {
template<>
struct __is_integral_helper<engine::uint128_t> : public true_type {};
} // namespace std

namespace engine {
class uint128_t {
public:
    uint128_t(unsigned long long low = 0, unsigned long long high = 0);
    std::strong_ordering operator<=>(const uint128_t &b) const;

public:
    uint128_t &operator=(const T &b);
    uint128_t  operator+(const uint128_t &b) const;
    uint128_t  operator-(const uint128_t &b) const;
    uint128_t  operator*(const uint128_t &b) const;
    uint128_t  operator/(const uint128_t &b) const;
    uint128_t  operator%(const uint128_t &b) const;

    std::tuple<uint128_t, uint128_t> dividedBy(const uint128_t &b) const;

    uint128_t operator&(const uint128_t &b) const;
    uint128_t operator|(const uint128_t &b) const;
    uint128_t operator~() const;
    uint128_t operator^(const uint128_t &b) const;

protected:
    unsigned long long low, high;
};
} // namespace engine