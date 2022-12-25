#pragma once
#include "SBindHelper.h"

namespace engine {
template<typename pointer_t>
SBindHelper<pointer_t>::SBindHelper(pointer_t &p) : ptr(p) {
    ptr->bind();
}

template<typename pointer_t>
SBindHelper<pointer_t>::~SBindHelper() {
    ptr->unbind();
}

template<typename pointer_t>
pointer_t &SBindHelper<pointer_t>::operator->() {
    return ptr;
}

template<typename pointer_t>
SBindHelper<pointer_t> make_SBindHelper(pointer_t &p) {
    return SBindHelper<pointer_t>(p);
}

template<typename pointer_t>
typename std::pointer_traits<pointer_t>::element_type &
SBindHelper<pointer_t>::operator*() {
    return *ptr;
}
} // namespace engine