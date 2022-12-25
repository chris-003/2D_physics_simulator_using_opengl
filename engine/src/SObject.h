#pragma once
#include <any>
#include <concepts>
#include <functional>
#include <set>
#include <tuple>

namespace engine {
class SObject {
    // protected:
    //     class Index {
    //     public:
    //         Index(unsigned int index = -1);
    //         unsigned int         index() const;
    //         std::strong_ordering operator<=>(const Index &b) const;

    //     protected:
    //         unsigned int m_index;
    //     };

    // public:
    //     class Signal : public Index {
    //     public:
    //         Signal(unsigned int index = -1) : Index(index) {
    //         }
    //     };
    //     class Slot : public Index {
    //     public:
    //         Slot(unsigned int index = -1) : Index(index) {
    //         }
    //     };
public:
    SObject();
    ~SObject();
    template<typename... Args, typename T, typename slot_func_t>
    requires std::is_invocable_v<slot_func_t, Args...>
    int connect(const T &_signal, const slot_func_t &func);
    template<typename... Args, typename T>
    static int  connect(SObject *sender, const T &_signal,
                        const std::function<Args...> &func);
    void        disconnect(int slot);
    static void disconnect(SObject *sender, int slot);
    // void emit(const Signal &signal);
protected:
    template<typename... Args, typename T>
    void emit(const T &_signal, Args... args);

private:
    struct Cmp {
        template<typename T>
        bool operator()(const T &a, const T &b) const {
            if (std::get<0>(a) == std::get<0>(b)) {
                return std::get<1>(a) < std::get<1>(b);
            }
            return std::get<0>(a) < std::get<0>(b);
        }
    };
    std::multiset<std::tuple<int, int, std::any>, Cmp> connections;
    unsigned int                                       slotIndex;
};
} // namespace engine

#include "SObject.hpp"