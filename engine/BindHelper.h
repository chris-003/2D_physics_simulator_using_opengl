#pragma once
#include <memory>

namespace engine {
template<typename pointer_t>
class BindHelper {
public:
    BindHelper(pointer_t &p);
    ~BindHelper();
    pointer_t &operator->();

protected:
    pointer_t &ptr;
};

template<typename pointer_t>
BindHelper<pointer_t> make_BindHelper(pointer_t &p);
} // namespace engine

#include "BindHelper.cpp"