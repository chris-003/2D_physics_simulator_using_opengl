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
    requires std::invocable<slot_t, Args...> Slot connect(const Signal &signal,
                                                          const slot_t &func);
    template<typename... Args, typename slot_t>
    requires std::invocable<slot_t, Args...>
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

namespace engine {
template<typename... Args, typename slot_t>
requires std::invocable<slot_t, Args...> Object::Slot
Object::connect(const Signal &signal, const slot_t &func) {
    // static unsigned int slotIndex = 0;
    connections.insert(std::make_tuple(
        signal, Slot(slotIndex), std::any(std::function<void(Args...)>(func))));

    return Slot(slotIndex++);
}

template<typename... Args, typename slot_t>
requires std::invocable<slot_t, Args...> Object::Slot
Object::connect(Object *sender, const Signal &signal, const slot_t &func) {
    return sender->connect(signal, func);
}

template<typename... Args>
void Object::emit(const Signal &signal, Args... args) {
    auto iter = connections.find(
        std::make_tuple(signal, Slot(0), std::function<void(std::any)>()));
    if (iter == connections.end()) {
        return;
    }
    // else
    for (; iter != connections.end() &&
           std::get<0>(*iter).index() == signal.index();
         ++iter) {
        auto func = (std::get<2>(*iter));
        std::any_cast<const std::function<void(Args...)> &>(std::get<2>(*iter))(
            args...);
    }
}
} // namespace engine