#pragma once
#include <memory>

namespace engine {
template<typename pointer_t>
class SBindHelper {
public:
    SBindHelper(pointer_t &p);
    ~SBindHelper();
    pointer_t                                             &operator->();
    typename std::pointer_traits<pointer_t>::element_type &operator*();

protected:
    pointer_t &ptr;
};

template<typename pointer_t>
SBindHelper<pointer_t> make_SBindHelper(pointer_t &p);
} // namespace engine

#include "SBindHelper.hpp"