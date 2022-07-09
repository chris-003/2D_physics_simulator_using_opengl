#pragma once
#include "BindHelper.h"

namespace engine {
template<typename pointer_t>
BindHelper<pointer_t>::BindHelper(pointer_t &p) : ptr(p) {
    ptr->bind();
}

template<typename pointer_t>
BindHelper<pointer_t>::~BindHelper() {
    ptr->unbind();
}

template<typename pointer_t>
pointer_t &BindHelper<pointer_t>::operator->() {
    return ptr;
}

template<typename pointer_t>
BindHelper<pointer_t> make_BindHelper(pointer_t &p) {
    return BindHelper<pointer_t>(p);
}

template<typename pointer_t>
typename std::pointer_traits<pointer_t>::element_type &
BindHelper<pointer_t>::operator*() {
    return *ptr;
}
} // namespace engine