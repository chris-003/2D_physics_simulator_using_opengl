#pragma once
#include "SObject.h"
#include <algorithm>

namespace engine {
template<typename... Args, typename T, typename slot_func_t>
requires std::is_invocable_v<slot_func_t, Args...>
int SObject::connect(const T &_signal, const slot_func_t &func) {
    int signal = (int)_signal;
    // static unsigned int slotIndex = 0;
    connections.insert(std::make_tuple(
        signal, slotIndex, std::any(std::function<void(Args...)>(func))));

    return slotIndex++;
}

template<typename... Args, typename T>
int SObject::connect(SObject *sender, const T &_signal,
                     const std::function<Args...> &func) {
    int signal = (int)_signal;
    return sender->connect(signal, func);
}

template<typename... Args, typename T>
void SObject::emit(const T &_signal, Args... args) {
    int  signal = (int)_signal;
    auto iter   = connections.find(
          std::make_tuple(signal, 0, std::function<void(std::any)>()));
    if (iter == connections.end()) {
        return;
    }
    // else
    for (; iter != connections.end() && std::get<0>(*iter) == signal; ++iter) {
        auto func = (std::get<2>(*iter));
        std::any_cast<const std::function<void(Args...)> &>(std::get<2>(*iter))(
            args...);
    }
}
} // namespace engine