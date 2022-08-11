#pragma once
#include <any>
#include <concepts>
#include <functional>
#include <set>
#include <tuple>

namespace engine {
class Object {
public:
    class Signal {
    public:
        Signal(unsigned int index = -1) : _index(index) {
        }
        unsigned int index() const {
            return _index;
        }
        std::strong_ordering operator<=>(const Signal &b) const {
            return index() <=> b.index();
        }

    protected:
        unsigned int _index;
    };
    class Slot {
    public:
        Slot(unsigned int index = -1) : _index(index) {
        }
        unsigned int index() const {
            return _index;
        }
        std::strong_ordering operator<=>(const Slot &b) const {
            return index() <=> b.index();
        }

    protected:
        unsigned int _index;
    };
    Object();
    ~Object();
    template<typename... Args, typename slot_t>
    requires std::is_invocable_v<slot_t, Args...>
        Slot connect(const Signal &signal, const slot_t &func);
    template<typename... Args, typename slot_t>
    requires std::is_invocable_v<slot_t, Args...>
    static Slot connect(Object *sender, const Signal &signal,
                        const slot_t &func);
    void        disconnect(const Slot &slot);
    static void disconnect(Object *sender, const Slot &slot);
    // void emit(const Signal &signal);
    template<typename... Args>
    void emit(const Signal &signal, Args... args);

private:
    struct Cmp {
        template<typename T>
        bool operator()(const T &a, const T &b) const {
            return std::get<0>(a).index() < std::get<0>(b).index();
        }
    };
    std::multiset<std::tuple<Signal, Slot, std::any>, Cmp> connections;
    unsigned int                                           slotIndex;
};
} // namespace engine